/*
 * Bionic's SIGSTKSZ is a fixed 8192, but on CPUs with AMX (Sapphire and
 * Emerald Rapids, which some GitHub runners are) the kernel's minimum signal
 * stack is larger, so objtool's sigaltstack(SIGSTKSZ) can fail with ENOMEM
 * ("Out of memory"); alpine hit exactly that with musl's equally fixed value.
 * glibc 2.34+ defines SIGSTKSZ as sysconf(_SC_SIGSTKSZ), but Bionic's sysconf
 * has no _SC_SIGSTKSZ, so compute it the way musl's sysconf does: the kernel's
 * AT_MINSIGSTKSZ (at least MINSIGSTKSZ) plus SIGSTKSZ - MINSIGSTKSZ of room.
 * objtool's tools/objtool/signal.c is the only host program that uses
 * SIGSTKSZ, and only at run time. HOSTCFLAGS in termux/Dockerfile puts this
 * directory first.
 */
#ifndef TERMUX_COMPAT_SIGNAL_H
#define TERMUX_COMPAT_SIGNAL_H

#include_next <signal.h>

#include <sys/auxv.h>

#ifndef AT_MINSIGSTKSZ
#define AT_MINSIGSTKSZ 51
#endif

/* Bionic's values, captured before SIGSTKSZ is redefined below. */
enum {
	termux_sigstksz_ = SIGSTKSZ,
	termux_minsigstksz_ = MINSIGSTKSZ,
};

static inline long termux_sigstksz(void)
{
	long min = (long)getauxval(AT_MINSIGSTKSZ);

	if (min < termux_minsigstksz_)
		min = termux_minsigstksz_;
	return min + termux_sigstksz_ - termux_minsigstksz_;
}

#undef SIGSTKSZ
#define SIGSTKSZ termux_sigstksz()

#endif /* TERMUX_COMPAT_SIGNAL_H */
