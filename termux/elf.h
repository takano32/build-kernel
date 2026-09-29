/*
 * Bionic's <elf.h> is a thin layer over <linux/elf.h>, which defines
 * ELF32_ST_TYPE(x) as ELF_ST_TYPE(x) and so on and has no *_ST_VISIBILITY.
 * The kernel's host tools expect glibc's self-contained <elf.h>:
 * arch/x86/tools/relocs_{32,64}.c define ELF_ST_TYPE(o) as ELF32_ST_TYPE(o),
 * the two macros then refer to each other, and clang reports the result as
 * calls to undeclared functions. Redefine the class-specific forms as glibc
 * does. HOSTCFLAGS in termux/Dockerfile puts this directory first.
 */
#include_next <elf.h>

#undef ELF32_ST_BIND
#undef ELF32_ST_TYPE
#undef ELF64_ST_BIND
#undef ELF64_ST_TYPE
#define ELF32_ST_BIND(val)	(((unsigned char) (val)) >> 4)
#define ELF32_ST_TYPE(val)	((val) & 0xf)
#define ELF64_ST_BIND(val)	ELF32_ST_BIND (val)
#define ELF64_ST_TYPE(val)	ELF32_ST_TYPE (val)

#ifndef ELF32_ST_VISIBILITY
#define ELF32_ST_VISIBILITY(o)	((o) & 0x03)
#endif
#ifndef ELF64_ST_VISIBILITY
#define ELF64_ST_VISIBILITY(o)	ELF32_ST_VISIBILITY (o)
#endif
