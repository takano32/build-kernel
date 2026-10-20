#!/bin/bash
# Stream the runner's memory, disk and pressure numbers to ntfy.sh every 60 seconds.
#
# Why this exists: a job whose runner dies ("The hosted runner lost communication
# with the server") leaves no log at all -- GET /actions/jobs/<id>/logs answers
# 404 / BlobNotFound, for the 10-05, 10-08 and 10-20 gentoo jobs alike. So the
# only evidence that survives such a death is what was already sent off the
# runner. Started in the background next to the build step, this keeps posting
# until the runner goes away; the last line on the topic is the state it died in.
#
# SAMPLE_TOPIC  ntfy.sh topic name (default: build-kernel-lost-runner)
# SAMPLE_LABEL  which stage this is, e.g. image:gentoo-llvm
# SAMPLE_TOKEN  ntfy access token. When set every post is authenticated, so a
#               topic with an ACL still accepts the samples; unset publishes
#               anonymously, which only works on a public topic.
set -u

topic=${SAMPLE_TOPIC:-build-kernel-lost-runner}
label=${SAMPLE_LABEL:-build}
url=${SAMPLE_URL:-https://ntfy.sh/$topic}

sample() {
    local ts mem load disk dockerd psi_mem psi_io msg code
    ts=$(date -u +%H:%M:%SZ)
    mem=$(free -m | awk '/^Mem:/{printf "%d/%dMB", $3, $2}')
    load=$(cut -d' ' -f1 /proc/loadavg)
    disk=$(df -h / | awk 'NR==2{printf "%s/%s %s", $3, $2, $5}')
    dockerd=$(ps -eo rss=,comm= | awk '$2=="dockerd"{s+=$1} END{printf "%.0fMB", s/1024}')
    # PSI says how much everyone waited on memory and IO; an OOM-bound runner
    # shows this climbing long before `free` looks dramatic.
    # /proc/pressure/memory line: "some avg10=0.45 avg60=0.22 avg300=0.49 total=..."
    psi_mem=$(awk '/^some/{printf "%s %s %s", $2, $3, $4}' /proc/pressure/memory 2>/dev/null)
    psi_io=$(awk '/^some/{printf "%s %s %s", $2, $3, $4}' /proc/pressure/io 2>/dev/null)

    msg="$label $ts mem=$mem load=$load disk=$disk dockerd=$dockerd"
    [ -n "$psi_mem" ] && msg="$msg psi_mem($psi_mem)"
    [ -n "$psi_io" ] && msg="$msg psi_io($psi_io)"

    # Keep the POST status in the log: a silent 401/403 would otherwise look
    # exactly like a runner that simply stopped sampling. GitHub masks the
    # token itself in the Actions log.
    if [ -n "${SAMPLE_TOKEN:-}" ]; then
        code=$(curl -sS -o /dev/null -w '%{http_code}' --max-time 10 \
            -H "Authorization: Bearer $SAMPLE_TOKEN" -d "$msg" "$url" 2>/dev/null) || code=000
    else
        code=$(curl -sS -o /dev/null -w '%{http_code}' --max-time 10 \
            -d "$msg" "$url" 2>/dev/null) || code=000
    fi

    echo "[sample] post=$code $msg"
}

echo "[sample] runner nproc=$(nproc) $(free -m | awk '/^Mem:/{printf "mem=%dMB", $2}') $(df -h / | awk 'NR==2{printf "disk-free=%s of %s", $4, $2}') auth=$([ -n "${SAMPLE_TOKEN:-}" ] && echo token || echo anonymous)"
sample
while :; do
    sleep 60
    sample
done
