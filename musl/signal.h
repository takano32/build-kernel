/*
 * musl's SIGSTKSZ is a fixed 8192, but on CPUs with AMX (Sapphire and Emerald
 * Rapids, which some GitHub runners are) the kernel's minimum signal stack is
 * larger, so objtool's sigaltstack(SIGSTKSZ) fails with ENOMEM ("Out of
 * memory") and the build dies on whichever object hits it. glibc 2.34+ defines
 * SIGSTKSZ as sysconf(_SC_SIGSTKSZ) under _GNU_SOURCE; musl's sysconf gives the
 * same AT_MINSIGSTKSZ-based answer, so do what glibc does. objtool's
 * tools/objtool/signal.c is the only host program that uses SIGSTKSZ.
 * Used by the musl images, alpine and chimeralinux; HOSTCFLAGS in their
 * Dockerfiles puts this directory first.
 */
#include_next <signal.h>

#include <unistd.h>

#undef SIGSTKSZ
#define SIGSTKSZ sysconf(_SC_SIGSTKSZ)
