/*
 * Bionic's <elf.h> is a thin layer over <linux/elf.h>, but the kernel's host
 * tools are written against glibc's self-contained <elf.h>:
 *
 * - <linux/elf.h> defines ELF32_ST_TYPE(x) as ELF_ST_TYPE(x) and so on, while
 *   arch/x86/tools/relocs_{32,64}.c define ELF_ST_TYPE(o) as ELF32_ST_TYPE(o);
 *   the macros then refer to each other and clang sees undeclared functions.
 * - scripts/mod/modpost.c needs the R_ARM_* relocations and other constants
 *   that Bionic does not have.
 *
 * So redefine the ST macros as glibc and musl do, then add every macro of musl
 * 1.2.5's <elf.h> (MIT, https://musl.libc.org/) that Bionic leaves undefined.
 * HOSTCFLAGS in termux/Dockerfile puts this directory first. The list below
 * was generated with
 *
 *   awk '/^#define [A-Za-z0-9_]+/ { n = $2; sub(/[(].*$/, "", n);
 *        print "#ifndef " n; print; print "#endif" }' musl/include/elf.h
 *
 * minus musl's own _ELF_H include guard.
 */
#ifndef TERMUX_COMPAT_ELF_H
#define TERMUX_COMPAT_ELF_H

/* glibc's and musl's <elf.h> both pull this in, and modpost.c relies on it. */
#include <stdint.h>
#include_next <elf.h>

#undef ELF32_ST_BIND
#undef ELF32_ST_TYPE
#undef ELF64_ST_BIND
#undef ELF64_ST_TYPE

#ifndef EI_NIDENT
#define EI_NIDENT (16)
#endif
#ifndef EI_MAG0
#define EI_MAG0		0
#endif
#ifndef ELFMAG0
#define ELFMAG0		0x7f
#endif
#ifndef EI_MAG1
#define EI_MAG1		1
#endif
#ifndef ELFMAG1
#define ELFMAG1		'E'
#endif
#ifndef EI_MAG2
#define EI_MAG2		2
#endif
#ifndef ELFMAG2
#define ELFMAG2		'L'
#endif
#ifndef EI_MAG3
#define EI_MAG3		3
#endif
#ifndef ELFMAG3
#define ELFMAG3		'F'
#endif
#ifndef EI_CLASS
#define EI_CLASS	4
#endif
#ifndef ELFCLASSNONE
#define ELFCLASSNONE	0
#endif
#ifndef ELFCLASS32
#define ELFCLASS32	1
#endif
#ifndef ELFCLASS64
#define ELFCLASS64	2
#endif
#ifndef ELFCLASSNUM
#define ELFCLASSNUM	3
#endif
#ifndef EI_DATA
#define EI_DATA		5
#endif
#ifndef ELFDATANONE
#define ELFDATANONE	0
#endif
#ifndef ELFDATA2LSB
#define ELFDATA2LSB	1
#endif
#ifndef ELFDATA2MSB
#define ELFDATA2MSB	2
#endif
#ifndef ELFDATANUM
#define ELFDATANUM	3
#endif
#ifndef EI_VERSION
#define EI_VERSION	6
#endif
#ifndef EI_OSABI
#define EI_OSABI	7
#endif
#ifndef ELFOSABI_NONE
#define ELFOSABI_NONE		0
#endif
#ifndef ELFOSABI_SYSV
#define ELFOSABI_SYSV		0
#endif
#ifndef ELFOSABI_HPUX
#define ELFOSABI_HPUX		1
#endif
#ifndef ELFOSABI_NETBSD
#define ELFOSABI_NETBSD		2
#endif
#ifndef ELFOSABI_LINUX
#define ELFOSABI_LINUX		3
#endif
#ifndef ELFOSABI_GNU
#define ELFOSABI_GNU		3
#endif
#ifndef ELFOSABI_SOLARIS
#define ELFOSABI_SOLARIS	6
#endif
#ifndef ELFOSABI_AIX
#define ELFOSABI_AIX		7
#endif
#ifndef ELFOSABI_IRIX
#define ELFOSABI_IRIX		8
#endif
#ifndef ELFOSABI_FREEBSD
#define ELFOSABI_FREEBSD	9
#endif
#ifndef ELFOSABI_TRU64
#define ELFOSABI_TRU64		10
#endif
#ifndef ELFOSABI_MODESTO
#define ELFOSABI_MODESTO	11
#endif
#ifndef ELFOSABI_OPENBSD
#define ELFOSABI_OPENBSD	12
#endif
#ifndef ELFOSABI_ARM
#define ELFOSABI_ARM		97
#endif
#ifndef ELFOSABI_STANDALONE
#define ELFOSABI_STANDALONE	255
#endif
#ifndef EI_ABIVERSION
#define EI_ABIVERSION	8
#endif
#ifndef EI_PAD
#define EI_PAD		9
#endif
#ifndef ET_NONE
#define ET_NONE		0
#endif
#ifndef ET_REL
#define ET_REL		1
#endif
#ifndef ET_EXEC
#define ET_EXEC		2
#endif
#ifndef ET_DYN
#define ET_DYN		3
#endif
#ifndef ET_CORE
#define ET_CORE		4
#endif
#ifndef ET_LOOS
#define ET_LOOS		0xfe00
#endif
#ifndef ET_HIOS
#define ET_HIOS		0xfeff
#endif
#ifndef ET_LOPROC
#define ET_LOPROC	0xff00
#endif
#ifndef ET_HIPROC
#define ET_HIPROC	0xffff
#endif
#ifndef EM_NONE
#define EM_NONE		 0
#endif
#ifndef EM_M32
#define EM_M32		 1
#endif
#ifndef EM_SPARC
#define EM_SPARC	 2
#endif
#ifndef EM_386
#define EM_386		 3
#endif
#ifndef EM_68K
#define EM_68K		 4
#endif
#ifndef EM_88K
#define EM_88K		 5
#endif
#ifndef EM_860
#define EM_860		 7
#endif
#ifndef EM_MIPS
#define EM_MIPS		 8
#endif
#ifndef EM_S370
#define EM_S370		 9
#endif
#ifndef EM_MIPS_RS3_LE
#define EM_MIPS_RS3_LE	10
#endif
#ifndef EM_PARISC
#define EM_PARISC	15
#endif
#ifndef EM_VPP500
#define EM_VPP500	17
#endif
#ifndef EM_SPARC32PLUS
#define EM_SPARC32PLUS	18
#endif
#ifndef EM_960
#define EM_960		19
#endif
#ifndef EM_PPC
#define EM_PPC		20
#endif
#ifndef EM_PPC64
#define EM_PPC64	21
#endif
#ifndef EM_S390
#define EM_S390		22
#endif
#ifndef EM_V800
#define EM_V800		36
#endif
#ifndef EM_FR20
#define EM_FR20		37
#endif
#ifndef EM_RH32
#define EM_RH32		38
#endif
#ifndef EM_RCE
#define EM_RCE		39
#endif
#ifndef EM_ARM
#define EM_ARM		40
#endif
#ifndef EM_FAKE_ALPHA
#define EM_FAKE_ALPHA	41
#endif
#ifndef EM_SH
#define EM_SH		42
#endif
#ifndef EM_SPARCV9
#define EM_SPARCV9	43
#endif
#ifndef EM_TRICORE
#define EM_TRICORE	44
#endif
#ifndef EM_ARC
#define EM_ARC		45
#endif
#ifndef EM_H8_300
#define EM_H8_300	46
#endif
#ifndef EM_H8_300H
#define EM_H8_300H	47
#endif
#ifndef EM_H8S
#define EM_H8S		48
#endif
#ifndef EM_H8_500
#define EM_H8_500	49
#endif
#ifndef EM_IA_64
#define EM_IA_64	50
#endif
#ifndef EM_MIPS_X
#define EM_MIPS_X	51
#endif
#ifndef EM_COLDFIRE
#define EM_COLDFIRE	52
#endif
#ifndef EM_68HC12
#define EM_68HC12	53
#endif
#ifndef EM_MMA
#define EM_MMA		54
#endif
#ifndef EM_PCP
#define EM_PCP		55
#endif
#ifndef EM_NCPU
#define EM_NCPU		56
#endif
#ifndef EM_NDR1
#define EM_NDR1		57
#endif
#ifndef EM_STARCORE
#define EM_STARCORE	58
#endif
#ifndef EM_ME16
#define EM_ME16		59
#endif
#ifndef EM_ST100
#define EM_ST100	60
#endif
#ifndef EM_TINYJ
#define EM_TINYJ	61
#endif
#ifndef EM_X86_64
#define EM_X86_64	62
#endif
#ifndef EM_PDSP
#define EM_PDSP		63
#endif
#ifndef EM_FX66
#define EM_FX66		66
#endif
#ifndef EM_ST9PLUS
#define EM_ST9PLUS	67
#endif
#ifndef EM_ST7
#define EM_ST7		68
#endif
#ifndef EM_68HC16
#define EM_68HC16	69
#endif
#ifndef EM_68HC11
#define EM_68HC11	70
#endif
#ifndef EM_68HC08
#define EM_68HC08	71
#endif
#ifndef EM_68HC05
#define EM_68HC05	72
#endif
#ifndef EM_SVX
#define EM_SVX		73
#endif
#ifndef EM_ST19
#define EM_ST19		74
#endif
#ifndef EM_VAX
#define EM_VAX		75
#endif
#ifndef EM_CRIS
#define EM_CRIS		76
#endif
#ifndef EM_JAVELIN
#define EM_JAVELIN	77
#endif
#ifndef EM_FIREPATH
#define EM_FIREPATH	78
#endif
#ifndef EM_ZSP
#define EM_ZSP		79
#endif
#ifndef EM_MMIX
#define EM_MMIX		80
#endif
#ifndef EM_HUANY
#define EM_HUANY	81
#endif
#ifndef EM_PRISM
#define EM_PRISM	82
#endif
#ifndef EM_AVR
#define EM_AVR		83
#endif
#ifndef EM_FR30
#define EM_FR30		84
#endif
#ifndef EM_D10V
#define EM_D10V		85
#endif
#ifndef EM_D30V
#define EM_D30V		86
#endif
#ifndef EM_V850
#define EM_V850		87
#endif
#ifndef EM_M32R
#define EM_M32R		88
#endif
#ifndef EM_MN10300
#define EM_MN10300	89
#endif
#ifndef EM_MN10200
#define EM_MN10200	90
#endif
#ifndef EM_PJ
#define EM_PJ		91
#endif
#ifndef EM_OR1K
#define EM_OR1K		92
#endif
#ifndef EM_OPENRISC
#define EM_OPENRISC	92
#endif
#ifndef EM_ARC_A5
#define EM_ARC_A5	93
#endif
#ifndef EM_ARC_COMPACT
#define EM_ARC_COMPACT	93
#endif
#ifndef EM_XTENSA
#define EM_XTENSA	94
#endif
#ifndef EM_VIDEOCORE
#define EM_VIDEOCORE	95
#endif
#ifndef EM_TMM_GPP
#define EM_TMM_GPP	96
#endif
#ifndef EM_NS32K
#define EM_NS32K	97
#endif
#ifndef EM_TPC
#define EM_TPC		98
#endif
#ifndef EM_SNP1K
#define EM_SNP1K	99
#endif
#ifndef EM_ST200
#define EM_ST200	100
#endif
#ifndef EM_IP2K
#define EM_IP2K		101
#endif
#ifndef EM_MAX
#define EM_MAX		102
#endif
#ifndef EM_CR
#define EM_CR		103
#endif
#ifndef EM_F2MC16
#define EM_F2MC16	104
#endif
#ifndef EM_MSP430
#define EM_MSP430	105
#endif
#ifndef EM_BLACKFIN
#define EM_BLACKFIN	106
#endif
#ifndef EM_SE_C33
#define EM_SE_C33	107
#endif
#ifndef EM_SEP
#define EM_SEP		108
#endif
#ifndef EM_ARCA
#define EM_ARCA		109
#endif
#ifndef EM_UNICORE
#define EM_UNICORE	110
#endif
#ifndef EM_EXCESS
#define EM_EXCESS	111
#endif
#ifndef EM_DXP
#define EM_DXP		112
#endif
#ifndef EM_ALTERA_NIOS2
#define EM_ALTERA_NIOS2 113
#endif
#ifndef EM_CRX
#define EM_CRX		114
#endif
#ifndef EM_XGATE
#define EM_XGATE	115
#endif
#ifndef EM_C166
#define EM_C166		116
#endif
#ifndef EM_M16C
#define EM_M16C		117
#endif
#ifndef EM_DSPIC30F
#define EM_DSPIC30F	118
#endif
#ifndef EM_CE
#define EM_CE		119
#endif
#ifndef EM_M32C
#define EM_M32C		120
#endif
#ifndef EM_TSK3000
#define EM_TSK3000	131
#endif
#ifndef EM_RS08
#define EM_RS08		132
#endif
#ifndef EM_SHARC
#define EM_SHARC	133
#endif
#ifndef EM_ECOG2
#define EM_ECOG2	134
#endif
#ifndef EM_SCORE7
#define EM_SCORE7	135
#endif
#ifndef EM_DSP24
#define EM_DSP24	136
#endif
#ifndef EM_VIDEOCORE3
#define EM_VIDEOCORE3	137
#endif
#ifndef EM_LATTICEMICO32
#define EM_LATTICEMICO32 138
#endif
#ifndef EM_SE_C17
#define EM_SE_C17	139
#endif
#ifndef EM_TI_C6000
#define EM_TI_C6000	140
#endif
#ifndef EM_TI_C2000
#define EM_TI_C2000	141
#endif
#ifndef EM_TI_C5500
#define EM_TI_C5500	142
#endif
#ifndef EM_TI_ARP32
#define EM_TI_ARP32	143
#endif
#ifndef EM_TI_PRU
#define EM_TI_PRU	144
#endif
#ifndef EM_MMDSP_PLUS
#define EM_MMDSP_PLUS	160
#endif
#ifndef EM_CYPRESS_M8C
#define EM_CYPRESS_M8C	161
#endif
#ifndef EM_R32C
#define EM_R32C		162
#endif
#ifndef EM_TRIMEDIA
#define EM_TRIMEDIA	163
#endif
#ifndef EM_QDSP6
#define EM_QDSP6	164
#endif
#ifndef EM_8051
#define EM_8051		165
#endif
#ifndef EM_STXP7X
#define EM_STXP7X	166
#endif
#ifndef EM_NDS32
#define EM_NDS32	167
#endif
#ifndef EM_ECOG1X
#define EM_ECOG1X	168
#endif
#ifndef EM_MAXQ30
#define EM_MAXQ30	169
#endif
#ifndef EM_XIMO16
#define EM_XIMO16	170
#endif
#ifndef EM_MANIK
#define EM_MANIK	171
#endif
#ifndef EM_CRAYNV2
#define EM_CRAYNV2	172
#endif
#ifndef EM_RX
#define EM_RX		173
#endif
#ifndef EM_METAG
#define EM_METAG	174
#endif
#ifndef EM_MCST_ELBRUS
#define EM_MCST_ELBRUS	175
#endif
#ifndef EM_ECOG16
#define EM_ECOG16	176
#endif
#ifndef EM_CR16
#define EM_CR16		177
#endif
#ifndef EM_ETPU
#define EM_ETPU		178
#endif
#ifndef EM_SLE9X
#define EM_SLE9X	179
#endif
#ifndef EM_L10M
#define EM_L10M		180
#endif
#ifndef EM_K10M
#define EM_K10M		181
#endif
#ifndef EM_AARCH64
#define EM_AARCH64	183
#endif
#ifndef EM_AVR32
#define EM_AVR32	185
#endif
#ifndef EM_STM8
#define EM_STM8		186
#endif
#ifndef EM_TILE64
#define EM_TILE64	187
#endif
#ifndef EM_TILEPRO
#define EM_TILEPRO	188
#endif
#ifndef EM_MICROBLAZE
#define EM_MICROBLAZE	189
#endif
#ifndef EM_CUDA
#define EM_CUDA		190
#endif
#ifndef EM_TILEGX
#define EM_TILEGX	191
#endif
#ifndef EM_CLOUDSHIELD
#define EM_CLOUDSHIELD	192
#endif
#ifndef EM_COREA_1ST
#define EM_COREA_1ST	193
#endif
#ifndef EM_COREA_2ND
#define EM_COREA_2ND	194
#endif
#ifndef EM_ARC_COMPACT2
#define EM_ARC_COMPACT2	195
#endif
#ifndef EM_OPEN8
#define EM_OPEN8	196
#endif
#ifndef EM_RL78
#define EM_RL78		197
#endif
#ifndef EM_VIDEOCORE5
#define EM_VIDEOCORE5	198
#endif
#ifndef EM_78KOR
#define EM_78KOR	199
#endif
#ifndef EM_56800EX
#define EM_56800EX	200
#endif
#ifndef EM_BA1
#define EM_BA1		201
#endif
#ifndef EM_BA2
#define EM_BA2		202
#endif
#ifndef EM_XCORE
#define EM_XCORE	203
#endif
#ifndef EM_MCHP_PIC
#define EM_MCHP_PIC	204
#endif
#ifndef EM_KM32
#define EM_KM32		210
#endif
#ifndef EM_KMX32
#define EM_KMX32	211
#endif
#ifndef EM_EMX16
#define EM_EMX16	212
#endif
#ifndef EM_EMX8
#define EM_EMX8		213
#endif
#ifndef EM_KVARC
#define EM_KVARC	214
#endif
#ifndef EM_CDP
#define EM_CDP		215
#endif
#ifndef EM_COGE
#define EM_COGE		216
#endif
#ifndef EM_COOL
#define EM_COOL		217
#endif
#ifndef EM_NORC
#define EM_NORC		218
#endif
#ifndef EM_CSR_KALIMBA
#define EM_CSR_KALIMBA	219
#endif
#ifndef EM_Z80
#define EM_Z80		220
#endif
#ifndef EM_VISIUM
#define EM_VISIUM	221
#endif
#ifndef EM_FT32
#define EM_FT32		222
#endif
#ifndef EM_MOXIE
#define EM_MOXIE	223
#endif
#ifndef EM_AMDGPU
#define EM_AMDGPU	224
#endif
#ifndef EM_RISCV
#define EM_RISCV	243
#endif
#ifndef EM_BPF
#define EM_BPF		247
#endif
#ifndef EM_CSKY
#define EM_CSKY		252
#endif
#ifndef EM_LOONGARCH
#define EM_LOONGARCH	258
#endif
#ifndef EM_NUM
#define EM_NUM		259
#endif
#ifndef EM_ALPHA
#define EM_ALPHA	0x9026
#endif
#ifndef EV_NONE
#define EV_NONE		0
#endif
#ifndef EV_CURRENT
#define EV_CURRENT	1
#endif
#ifndef EV_NUM
#define EV_NUM		2
#endif
#ifndef SHN_UNDEF
#define SHN_UNDEF	0
#endif
#ifndef SHN_LORESERVE
#define SHN_LORESERVE	0xff00
#endif
#ifndef SHN_LOPROC
#define SHN_LOPROC	0xff00
#endif
#ifndef SHN_BEFORE
#define SHN_BEFORE	0xff00
#endif
#ifndef SHN_AFTER
#define SHN_AFTER	0xff01
#endif
#ifndef SHN_HIPROC
#define SHN_HIPROC	0xff1f
#endif
#ifndef SHN_LOOS
#define SHN_LOOS	0xff20
#endif
#ifndef SHN_HIOS
#define SHN_HIOS	0xff3f
#endif
#ifndef SHN_ABS
#define SHN_ABS		0xfff1
#endif
#ifndef SHN_COMMON
#define SHN_COMMON	0xfff2
#endif
#ifndef SHN_XINDEX
#define SHN_XINDEX	0xffff
#endif
#ifndef SHN_HIRESERVE
#define SHN_HIRESERVE	0xffff
#endif
#ifndef SHT_NULL
#define SHT_NULL	  0
#endif
#ifndef SHT_PROGBITS
#define SHT_PROGBITS	  1
#endif
#ifndef SHT_SYMTAB
#define SHT_SYMTAB	  2
#endif
#ifndef SHT_STRTAB
#define SHT_STRTAB	  3
#endif
#ifndef SHT_RELA
#define SHT_RELA	  4
#endif
#ifndef SHT_HASH
#define SHT_HASH	  5
#endif
#ifndef SHT_DYNAMIC
#define SHT_DYNAMIC	  6
#endif
#ifndef SHT_NOTE
#define SHT_NOTE	  7
#endif
#ifndef SHT_NOBITS
#define SHT_NOBITS	  8
#endif
#ifndef SHT_REL
#define SHT_REL		  9
#endif
#ifndef SHT_SHLIB
#define SHT_SHLIB	  10
#endif
#ifndef SHT_DYNSYM
#define SHT_DYNSYM	  11
#endif
#ifndef SHT_INIT_ARRAY
#define SHT_INIT_ARRAY	  14
#endif
#ifndef SHT_FINI_ARRAY
#define SHT_FINI_ARRAY	  15
#endif
#ifndef SHT_PREINIT_ARRAY
#define SHT_PREINIT_ARRAY 16
#endif
#ifndef SHT_GROUP
#define SHT_GROUP	  17
#endif
#ifndef SHT_SYMTAB_SHNDX
#define SHT_SYMTAB_SHNDX  18
#endif
#ifndef SHT_RELR
#define SHT_RELR	  19
#endif
#ifndef SHT_LOOS
#define SHT_LOOS	  0x60000000
#endif
#ifndef SHT_GNU_ATTRIBUTES
#define SHT_GNU_ATTRIBUTES 0x6ffffff5
#endif
#ifndef SHT_GNU_HASH
#define SHT_GNU_HASH	  0x6ffffff6
#endif
#ifndef SHT_GNU_LIBLIST
#define SHT_GNU_LIBLIST	  0x6ffffff7
#endif
#ifndef SHT_CHECKSUM
#define SHT_CHECKSUM	  0x6ffffff8
#endif
#ifndef SHT_LOSUNW
#define SHT_LOSUNW	  0x6ffffffa
#endif
#ifndef SHT_SUNW_move
#define SHT_SUNW_move	  0x6ffffffa
#endif
#ifndef SHT_SUNW_COMDAT
#define SHT_SUNW_COMDAT   0x6ffffffb
#endif
#ifndef SHT_SUNW_syminfo
#define SHT_SUNW_syminfo  0x6ffffffc
#endif
#ifndef SHT_GNU_verdef
#define SHT_GNU_verdef	  0x6ffffffd
#endif
#ifndef SHT_GNU_verneed
#define SHT_GNU_verneed	  0x6ffffffe
#endif
#ifndef SHT_GNU_versym
#define SHT_GNU_versym	  0x6fffffff
#endif
#ifndef SHT_HISUNW
#define SHT_HISUNW	  0x6fffffff
#endif
#ifndef SHT_HIOS
#define SHT_HIOS	  0x6fffffff
#endif
#ifndef SHT_LOPROC
#define SHT_LOPROC	  0x70000000
#endif
#ifndef SHT_HIPROC
#define SHT_HIPROC	  0x7fffffff
#endif
#ifndef SHT_LOUSER
#define SHT_LOUSER	  0x80000000
#endif
#ifndef SHT_HIUSER
#define SHT_HIUSER	  0x8fffffff
#endif
#ifndef SHF_WRITE
#define SHF_WRITE	     (1 << 0)
#endif
#ifndef SHF_ALLOC
#define SHF_ALLOC	     (1 << 1)
#endif
#ifndef SHF_EXECINSTR
#define SHF_EXECINSTR	     (1 << 2)
#endif
#ifndef SHF_MERGE
#define SHF_MERGE	     (1 << 4)
#endif
#ifndef SHF_STRINGS
#define SHF_STRINGS	     (1 << 5)
#endif
#ifndef SHF_INFO_LINK
#define SHF_INFO_LINK	     (1 << 6)
#endif
#ifndef SHF_LINK_ORDER
#define SHF_LINK_ORDER	     (1 << 7)
#endif
#ifndef SHF_OS_NONCONFORMING
#define SHF_OS_NONCONFORMING (1 << 8)
#endif
#ifndef SHF_GROUP
#define SHF_GROUP	     (1 << 9)
#endif
#ifndef SHF_TLS
#define SHF_TLS		     (1 << 10)
#endif
#ifndef SHF_COMPRESSED
#define SHF_COMPRESSED	     (1 << 11)
#endif
#ifndef SHF_MASKOS
#define SHF_MASKOS	     0x0ff00000
#endif
#ifndef SHF_MASKPROC
#define SHF_MASKPROC	     0xf0000000
#endif
#ifndef SHF_ORDERED
#define SHF_ORDERED	     (1 << 30)
#endif
#ifndef SHF_EXCLUDE
#define SHF_EXCLUDE	     (1U << 31)
#endif
#ifndef ELFCOMPRESS_ZLIB
#define ELFCOMPRESS_ZLIB	1
#endif
#ifndef ELFCOMPRESS_ZSTD
#define ELFCOMPRESS_ZSTD	2
#endif
#ifndef ELFCOMPRESS_LOOS
#define ELFCOMPRESS_LOOS	0x60000000
#endif
#ifndef ELFCOMPRESS_HIOS
#define ELFCOMPRESS_HIOS	0x6fffffff
#endif
#ifndef ELFCOMPRESS_LOPROC
#define ELFCOMPRESS_LOPROC	0x70000000
#endif
#ifndef ELFCOMPRESS_HIPROC
#define ELFCOMPRESS_HIPROC	0x7fffffff
#endif
#ifndef GRP_COMDAT
#define GRP_COMDAT	0x1
#endif
#ifndef SYMINFO_BT_SELF
#define SYMINFO_BT_SELF		0xffff
#endif
#ifndef SYMINFO_BT_PARENT
#define SYMINFO_BT_PARENT	0xfffe
#endif
#ifndef SYMINFO_BT_LOWRESERVE
#define SYMINFO_BT_LOWRESERVE	0xff00
#endif
#ifndef SYMINFO_FLG_DIRECT
#define SYMINFO_FLG_DIRECT	0x0001
#endif
#ifndef SYMINFO_FLG_PASSTHRU
#define SYMINFO_FLG_PASSTHRU	0x0002
#endif
#ifndef SYMINFO_FLG_COPY
#define SYMINFO_FLG_COPY	0x0004
#endif
#ifndef SYMINFO_FLG_LAZYLOAD
#define SYMINFO_FLG_LAZYLOAD	0x0008
#endif
#ifndef SYMINFO_NONE
#define SYMINFO_NONE		0
#endif
#ifndef SYMINFO_CURRENT
#define SYMINFO_CURRENT		1
#endif
#ifndef SYMINFO_NUM
#define SYMINFO_NUM		2
#endif
#ifndef ELF32_ST_BIND
#define ELF32_ST_BIND(val)		(((unsigned char) (val)) >> 4)
#endif
#ifndef ELF32_ST_TYPE
#define ELF32_ST_TYPE(val)		((val) & 0xf)
#endif
#ifndef ELF32_ST_INFO
#define ELF32_ST_INFO(bind, type)	(((bind) << 4) + ((type) & 0xf))
#endif
#ifndef ELF64_ST_BIND
#define ELF64_ST_BIND(val)		ELF32_ST_BIND (val)
#endif
#ifndef ELF64_ST_TYPE
#define ELF64_ST_TYPE(val)		ELF32_ST_TYPE (val)
#endif
#ifndef ELF64_ST_INFO
#define ELF64_ST_INFO(bind, type)	ELF32_ST_INFO ((bind), (type))
#endif
#ifndef STB_LOCAL
#define STB_LOCAL	0
#endif
#ifndef STB_GLOBAL
#define STB_GLOBAL	1
#endif
#ifndef STB_WEAK
#define STB_WEAK	2
#endif
#ifndef STB_LOOS
#define STB_LOOS	10
#endif
#ifndef STB_GNU_UNIQUE
#define STB_GNU_UNIQUE	10
#endif
#ifndef STB_HIOS
#define STB_HIOS	12
#endif
#ifndef STB_LOPROC
#define STB_LOPROC	13
#endif
#ifndef STB_HIPROC
#define STB_HIPROC	15
#endif
#ifndef STT_NOTYPE
#define STT_NOTYPE	0
#endif
#ifndef STT_OBJECT
#define STT_OBJECT	1
#endif
#ifndef STT_FUNC
#define STT_FUNC	2
#endif
#ifndef STT_SECTION
#define STT_SECTION	3
#endif
#ifndef STT_FILE
#define STT_FILE	4
#endif
#ifndef STT_COMMON
#define STT_COMMON	5
#endif
#ifndef STT_TLS
#define STT_TLS		6
#endif
#ifndef STT_LOOS
#define STT_LOOS	10
#endif
#ifndef STT_GNU_IFUNC
#define STT_GNU_IFUNC	10
#endif
#ifndef STT_HIOS
#define STT_HIOS	12
#endif
#ifndef STT_LOPROC
#define STT_LOPROC	13
#endif
#ifndef STT_HIPROC
#define STT_HIPROC	15
#endif
#ifndef STN_UNDEF
#define STN_UNDEF	0
#endif
#ifndef ELF32_ST_VISIBILITY
#define ELF32_ST_VISIBILITY(o)	((o) & 0x03)
#endif
#ifndef ELF64_ST_VISIBILITY
#define ELF64_ST_VISIBILITY(o)	ELF32_ST_VISIBILITY (o)
#endif
#ifndef STV_DEFAULT
#define STV_DEFAULT	0
#endif
#ifndef STV_INTERNAL
#define STV_INTERNAL	1
#endif
#ifndef STV_HIDDEN
#define STV_HIDDEN	2
#endif
#ifndef STV_PROTECTED
#define STV_PROTECTED	3
#endif
#ifndef ELF32_R_SYM
#define ELF32_R_SYM(val)		((val) >> 8)
#endif
#ifndef ELF32_R_TYPE
#define ELF32_R_TYPE(val)		((val) & 0xff)
#endif
#ifndef ELF32_R_INFO
#define ELF32_R_INFO(sym, type)		(((sym) << 8) + ((type) & 0xff))
#endif
#ifndef ELF64_R_SYM
#define ELF64_R_SYM(i)			((i) >> 32)
#endif
#ifndef ELF64_R_TYPE
#define ELF64_R_TYPE(i)			((i) & 0xffffffff)
#endif
#ifndef ELF64_R_INFO
#define ELF64_R_INFO(sym,type)		((((Elf64_Xword) (sym)) << 32) + (type))
#endif
#ifndef PT_LOAD
#define PT_LOAD		1
#endif
#ifndef PT_DYNAMIC
#define PT_DYNAMIC	2
#endif
#ifndef PT_INTERP
#define PT_INTERP	3
#endif
#ifndef PT_NOTE
#define PT_NOTE		4
#endif
#ifndef PT_SHLIB
#define PT_SHLIB	5
#endif
#ifndef PT_PHDR
#define PT_PHDR		6
#endif
#ifndef PT_TLS
#define PT_TLS		7
#endif
#ifndef PT_LOOS
#define PT_LOOS		0x60000000
#endif
#ifndef PT_GNU_EH_FRAME
#define PT_GNU_EH_FRAME	0x6474e550
#endif
#ifndef PT_GNU_STACK
#define PT_GNU_STACK	0x6474e551
#endif
#ifndef PT_GNU_RELRO
#define PT_GNU_RELRO	0x6474e552
#endif
#ifndef PT_GNU_PROPERTY
#define PT_GNU_PROPERTY	0x6474e553
#endif
#ifndef PT_LOSUNW
#define PT_LOSUNW	0x6ffffffa
#endif
#ifndef PT_SUNWBSS
#define PT_SUNWBSS	0x6ffffffa
#endif
#ifndef PT_SUNWSTACK
#define PT_SUNWSTACK	0x6ffffffb
#endif
#ifndef PT_HISUNW
#define PT_HISUNW	0x6fffffff
#endif
#ifndef PT_HIOS
#define PT_HIOS		0x6fffffff
#endif
#ifndef PT_LOPROC
#define PT_LOPROC	0x70000000
#endif
#ifndef PT_HIPROC
#define PT_HIPROC	0x7fffffff
#endif
#ifndef PN_XNUM
#define PN_XNUM 0xffff
#endif
#ifndef PF_X
#define PF_X		(1 << 0)
#endif
#ifndef PF_W
#define PF_W		(1 << 1)
#endif
#ifndef PF_R
#define PF_R		(1 << 2)
#endif
#ifndef PF_MASKOS
#define PF_MASKOS	0x0ff00000
#endif
#ifndef PF_MASKPROC
#define PF_MASKPROC	0xf0000000
#endif
#ifndef NT_PRSTATUS
#define NT_PRSTATUS	1
#endif
#ifndef NT_PRFPREG
#define NT_PRFPREG	2
#endif
#ifndef NT_FPREGSET
#define NT_FPREGSET	2
#endif
#ifndef NT_PRPSINFO
#define NT_PRPSINFO	3
#endif
#ifndef NT_PRXREG
#define NT_PRXREG	4
#endif
#ifndef NT_TASKSTRUCT
#define NT_TASKSTRUCT	4
#endif
#ifndef NT_PLATFORM
#define NT_PLATFORM	5
#endif
#ifndef NT_AUXV
#define NT_AUXV		6
#endif
#ifndef NT_GWINDOWS
#define NT_GWINDOWS	7
#endif
#ifndef NT_ASRS
#define NT_ASRS		8
#endif
#ifndef NT_PSTATUS
#define NT_PSTATUS	10
#endif
#ifndef NT_PSINFO
#define NT_PSINFO	13
#endif
#ifndef NT_PRCRED
#define NT_PRCRED	14
#endif
#ifndef NT_UTSNAME
#define NT_UTSNAME	15
#endif
#ifndef NT_LWPSTATUS
#define NT_LWPSTATUS	16
#endif
#ifndef NT_LWPSINFO
#define NT_LWPSINFO	17
#endif
#ifndef NT_PRFPXREG
#define NT_PRFPXREG	20
#endif
#ifndef NT_SIGINFO
#define NT_SIGINFO	0x53494749
#endif
#ifndef NT_FILE
#define NT_FILE		0x46494c45
#endif
#ifndef NT_PRXFPREG
#define NT_PRXFPREG	0x46e62b7f
#endif
#ifndef NT_PPC_VMX
#define NT_PPC_VMX	0x100
#endif
#ifndef NT_PPC_SPE
#define NT_PPC_SPE	0x101
#endif
#ifndef NT_PPC_VSX
#define NT_PPC_VSX	0x102
#endif
#ifndef NT_PPC_TAR
#define NT_PPC_TAR	0x103
#endif
#ifndef NT_PPC_PPR
#define NT_PPC_PPR	0x104
#endif
#ifndef NT_PPC_DSCR
#define NT_PPC_DSCR	0x105
#endif
#ifndef NT_PPC_EBB
#define NT_PPC_EBB	0x106
#endif
#ifndef NT_PPC_PMU
#define NT_PPC_PMU	0x107
#endif
#ifndef NT_PPC_TM_CGPR
#define NT_PPC_TM_CGPR	0x108
#endif
#ifndef NT_PPC_TM_CFPR
#define NT_PPC_TM_CFPR	0x109
#endif
#ifndef NT_PPC_TM_CVMX
#define NT_PPC_TM_CVMX	0x10a
#endif
#ifndef NT_PPC_TM_CVSX
#define NT_PPC_TM_CVSX	0x10b
#endif
#ifndef NT_PPC_TM_SPR
#define NT_PPC_TM_SPR	0x10c
#endif
#ifndef NT_PPC_TM_CTAR
#define NT_PPC_TM_CTAR	0x10d
#endif
#ifndef NT_PPC_TM_CPPR
#define NT_PPC_TM_CPPR	0x10e
#endif
#ifndef NT_PPC_TM_CDSCR
#define NT_PPC_TM_CDSCR	0x10f
#endif
#ifndef NT_386_TLS
#define NT_386_TLS	0x200
#endif
#ifndef NT_386_IOPERM
#define NT_386_IOPERM	0x201
#endif
#ifndef NT_X86_XSTATE
#define NT_X86_XSTATE	0x202
#endif
#ifndef NT_S390_HIGH_GPRS
#define NT_S390_HIGH_GPRS	0x300
#endif
#ifndef NT_S390_TIMER
#define NT_S390_TIMER	0x301
#endif
#ifndef NT_S390_TODCMP
#define NT_S390_TODCMP	0x302
#endif
#ifndef NT_S390_TODPREG
#define NT_S390_TODPREG	0x303
#endif
#ifndef NT_S390_CTRS
#define NT_S390_CTRS	0x304
#endif
#ifndef NT_S390_PREFIX
#define NT_S390_PREFIX	0x305
#endif
#ifndef NT_S390_LAST_BREAK
#define NT_S390_LAST_BREAK	0x306
#endif
#ifndef NT_S390_SYSTEM_CALL
#define NT_S390_SYSTEM_CALL	0x307
#endif
#ifndef NT_S390_TDB
#define NT_S390_TDB	0x308
#endif
#ifndef NT_S390_VXRS_LOW
#define NT_S390_VXRS_LOW	0x309
#endif
#ifndef NT_S390_VXRS_HIGH
#define NT_S390_VXRS_HIGH	0x30a
#endif
#ifndef NT_S390_GS_CB
#define NT_S390_GS_CB	0x30b
#endif
#ifndef NT_S390_GS_BC
#define NT_S390_GS_BC	0x30c
#endif
#ifndef NT_S390_RI_CB
#define NT_S390_RI_CB	0x30d
#endif
#ifndef NT_ARM_VFP
#define NT_ARM_VFP	0x400
#endif
#ifndef NT_ARM_TLS
#define NT_ARM_TLS	0x401
#endif
#ifndef NT_ARM_HW_BREAK
#define NT_ARM_HW_BREAK	0x402
#endif
#ifndef NT_ARM_HW_WATCH
#define NT_ARM_HW_WATCH	0x403
#endif
#ifndef NT_ARM_SYSTEM_CALL
#define NT_ARM_SYSTEM_CALL	0x404
#endif
#ifndef NT_ARM_SVE
#define NT_ARM_SVE	0x405
#endif
#ifndef NT_ARM_PAC_MASK
#define NT_ARM_PAC_MASK	0x406
#endif
#ifndef NT_ARM_PACA_KEYS
#define NT_ARM_PACA_KEYS	0x407
#endif
#ifndef NT_ARM_PACG_KEYS
#define NT_ARM_PACG_KEYS	0x408
#endif
#ifndef NT_ARM_TAGGED_ADDR_CTRL
#define NT_ARM_TAGGED_ADDR_CTRL	0x409
#endif
#ifndef NT_ARM_PAC_ENABLED_KEYS
#define NT_ARM_PAC_ENABLED_KEYS	0x40a
#endif
#ifndef NT_METAG_CBUF
#define NT_METAG_CBUF	0x500
#endif
#ifndef NT_METAG_RPIPE
#define NT_METAG_RPIPE	0x501
#endif
#ifndef NT_METAG_TLS
#define NT_METAG_TLS	0x502
#endif
#ifndef NT_ARC_V2
#define NT_ARC_V2	0x600
#endif
#ifndef NT_VMCOREDD
#define NT_VMCOREDD	0x700
#endif
#ifndef NT_MIPS_DSP
#define NT_MIPS_DSP	0x800
#endif
#ifndef NT_MIPS_FP_MODE
#define NT_MIPS_FP_MODE	0x801
#endif
#ifndef NT_MIPS_MSA
#define NT_MIPS_MSA	0x802
#endif
#ifndef NT_RISCV_CSR
#define NT_RISCV_CSR	0x900
#endif
#ifndef NT_RISCV_VECTOR
#define NT_RISCV_VECTOR	0x901
#endif
#ifndef NT_VERSION
#define NT_VERSION	1
#endif
#ifndef NT_LOONGARCH_CPUCFG
#define NT_LOONGARCH_CPUCFG	0xa00
#endif
#ifndef NT_LOONGARCH_CSR
#define NT_LOONGARCH_CSR	0xa01
#endif
#ifndef NT_LOONGARCH_LSX
#define NT_LOONGARCH_LSX	0xa02
#endif
#ifndef NT_LOONGARCH_LASX
#define NT_LOONGARCH_LASX	0xa03
#endif
#ifndef NT_LOONGARCH_LBT
#define NT_LOONGARCH_LBT	0xa04
#endif
#ifndef DT_NULL
#define DT_NULL		0
#endif
#ifndef DT_NEEDED
#define DT_NEEDED	1
#endif
#ifndef DT_PLTRELSZ
#define DT_PLTRELSZ	2
#endif
#ifndef DT_PLTGOT
#define DT_PLTGOT	3
#endif
#ifndef DT_HASH
#define DT_HASH		4
#endif
#ifndef DT_STRTAB
#define DT_STRTAB	5
#endif
#ifndef DT_SYMTAB
#define DT_SYMTAB	6
#endif
#ifndef DT_RELA
#define DT_RELA		7
#endif
#ifndef DT_RELASZ
#define DT_RELASZ	8
#endif
#ifndef DT_RELAENT
#define DT_RELAENT	9
#endif
#ifndef DT_STRSZ
#define DT_STRSZ	10
#endif
#ifndef DT_SYMENT
#define DT_SYMENT	11
#endif
#ifndef DT_INIT
#define DT_INIT		12
#endif
#ifndef DT_FINI
#define DT_FINI		13
#endif
#ifndef DT_SONAME
#define DT_SONAME	14
#endif
#ifndef DT_RPATH
#define DT_RPATH	15
#endif
#ifndef DT_SYMBOLIC
#define DT_SYMBOLIC	16
#endif
#ifndef DT_REL
#define DT_REL		17
#endif
#ifndef DT_RELSZ
#define DT_RELSZ	18
#endif
#ifndef DT_RELENT
#define DT_RELENT	19
#endif
#ifndef DT_PLTREL
#define DT_PLTREL	20
#endif
#ifndef DT_DEBUG
#define DT_DEBUG	21
#endif
#ifndef DT_TEXTREL
#define DT_TEXTREL	22
#endif
#ifndef DT_JMPREL
#define DT_JMPREL	23
#endif
#ifndef DT_RUNPATH
#define DT_RUNPATH	29
#endif
#ifndef DT_FLAGS
#define DT_FLAGS	30
#endif
#ifndef DT_ENCODING
#define DT_ENCODING	32
#endif
#ifndef DT_PREINIT_ARRAY
#define DT_PREINIT_ARRAY 32
#endif
#ifndef DT_PREINIT_ARRAYSZ
#define DT_PREINIT_ARRAYSZ 33
#endif
#ifndef DT_SYMTAB_SHNDX
#define DT_SYMTAB_SHNDX	34
#endif
#ifndef DT_RELRSZ
#define DT_RELRSZ	35
#endif
#ifndef DT_RELR
#define DT_RELR		36
#endif
#ifndef DT_RELRENT
#define DT_RELRENT	37
#endif
#ifndef DT_LOOS
#define DT_LOOS		0x6000000d
#endif
#ifndef DT_HIOS
#define DT_HIOS		0x6ffff000
#endif
#ifndef DT_LOPROC
#define DT_LOPROC	0x70000000
#endif
#ifndef DT_HIPROC
#define DT_HIPROC	0x7fffffff
#endif
#ifndef DT_VALRNGLO
#define DT_VALRNGLO	0x6ffffd00
#endif
#ifndef DT_GNU_PRELINKED
#define DT_GNU_PRELINKED 0x6ffffdf5
#endif
#ifndef DT_GNU_CONFLICTSZ
#define DT_GNU_CONFLICTSZ 0x6ffffdf6
#endif
#ifndef DT_GNU_LIBLISTSZ
#define DT_GNU_LIBLISTSZ 0x6ffffdf7
#endif
#ifndef DT_CHECKSUM
#define DT_CHECKSUM	0x6ffffdf8
#endif
#ifndef DT_PLTPADSZ
#define DT_PLTPADSZ	0x6ffffdf9
#endif
#ifndef DT_MOVEENT
#define DT_MOVEENT	0x6ffffdfa
#endif
#ifndef DT_MOVESZ
#define DT_MOVESZ	0x6ffffdfb
#endif
#ifndef DT_FEATURE_1
#define DT_FEATURE_1	0x6ffffdfc
#endif
#ifndef DT_POSFLAG_1
#define DT_POSFLAG_1	0x6ffffdfd
#endif
#ifndef DT_SYMINSZ
#define DT_SYMINSZ	0x6ffffdfe
#endif
#ifndef DT_SYMINENT
#define DT_SYMINENT	0x6ffffdff
#endif
#ifndef DT_VALRNGHI
#define DT_VALRNGHI	0x6ffffdff
#endif
#ifndef DT_VALTAGIDX
#define DT_VALTAGIDX(tag)	(DT_VALRNGHI - (tag))
#endif
#ifndef DT_VALNUM
#define DT_VALNUM 12
#endif
#ifndef DT_ADDRRNGLO
#define DT_ADDRRNGLO	0x6ffffe00
#endif
#ifndef DT_GNU_HASH
#define DT_GNU_HASH	0x6ffffef5
#endif
#ifndef DT_TLSDESC_PLT
#define DT_TLSDESC_PLT	0x6ffffef6
#endif
#ifndef DT_TLSDESC_GOT
#define DT_TLSDESC_GOT	0x6ffffef7
#endif
#ifndef DT_GNU_CONFLICT
#define DT_GNU_CONFLICT	0x6ffffef8
#endif
#ifndef DT_GNU_LIBLIST
#define DT_GNU_LIBLIST	0x6ffffef9
#endif
#ifndef DT_CONFIG
#define DT_CONFIG	0x6ffffefa
#endif
#ifndef DT_DEPAUDIT
#define DT_DEPAUDIT	0x6ffffefb
#endif
#ifndef DT_AUDIT
#define DT_AUDIT	0x6ffffefc
#endif
#ifndef DT_SYMINFO
#define DT_SYMINFO	0x6ffffeff
#endif
#ifndef DT_ADDRRNGHI
#define DT_ADDRRNGHI	0x6ffffeff
#endif
#ifndef DT_ADDRTAGIDX
#define DT_ADDRTAGIDX(tag)	(DT_ADDRRNGHI - (tag))
#endif
#ifndef DT_ADDRNUM
#define DT_ADDRNUM 11
#endif
#ifndef DT_VERSYM
#define DT_VERSYM	0x6ffffff0
#endif
#ifndef DT_RELACOUNT
#define DT_RELACOUNT	0x6ffffff9
#endif
#ifndef DT_RELCOUNT
#define DT_RELCOUNT	0x6ffffffa
#endif
#ifndef DT_FLAGS_1
#define DT_FLAGS_1	0x6ffffffb
#endif
#ifndef DT_VERSIONTAGIDX
#define DT_VERSIONTAGIDX(tag)	(DT_VERNEEDNUM - (tag))
#endif
#ifndef DT_VERSIONTAGNUM
#define DT_VERSIONTAGNUM 16
#endif
#ifndef DT_AUXILIARY
#define DT_AUXILIARY    0x7ffffffd
#endif
#ifndef DT_FILTER
#define DT_FILTER       0x7fffffff
#endif
#ifndef DT_EXTRATAGIDX
#define DT_EXTRATAGIDX(tag)	((Elf32_Word)-((Elf32_Sword) (tag) <<1>>1)-1)
#endif
#ifndef DT_EXTRANUM
#define DT_EXTRANUM	3
#endif
#ifndef DF_ORIGIN
#define DF_ORIGIN	0x00000001
#endif
#ifndef DF_SYMBOLIC
#define DF_SYMBOLIC	0x00000002
#endif
#ifndef DF_TEXTREL
#define DF_TEXTREL	0x00000004
#endif
#ifndef DF_BIND_NOW
#define DF_BIND_NOW	0x00000008
#endif
#ifndef DF_STATIC_TLS
#define DF_STATIC_TLS	0x00000010
#endif
#ifndef DF_1_NOW
#define DF_1_NOW	0x00000001
#endif
#ifndef DF_1_GLOBAL
#define DF_1_GLOBAL	0x00000002
#endif
#ifndef DF_1_GROUP
#define DF_1_GROUP	0x00000004
#endif
#ifndef DF_1_NODELETE
#define DF_1_NODELETE	0x00000008
#endif
#ifndef DF_1_LOADFLTR
#define DF_1_LOADFLTR	0x00000010
#endif
#ifndef DF_1_INITFIRST
#define DF_1_INITFIRST	0x00000020
#endif
#ifndef DF_1_NOOPEN
#define DF_1_NOOPEN	0x00000040
#endif
#ifndef DF_1_ORIGIN
#define DF_1_ORIGIN	0x00000080
#endif
#ifndef DF_1_DIRECT
#define DF_1_DIRECT	0x00000100
#endif
#ifndef DF_1_TRANS
#define DF_1_TRANS	0x00000200
#endif
#ifndef DF_1_INTERPOSE
#define DF_1_INTERPOSE	0x00000400
#endif
#ifndef DF_1_NODEFLIB
#define DF_1_NODEFLIB	0x00000800
#endif
#ifndef DF_1_NODUMP
#define DF_1_NODUMP	0x00001000
#endif
#ifndef DF_1_CONFALT
#define DF_1_CONFALT	0x00002000
#endif
#ifndef DF_1_ENDFILTEE
#define DF_1_ENDFILTEE	0x00004000
#endif
#ifndef DTF_1_PARINIT
#define DTF_1_PARINIT	0x00000001
#endif
#ifndef DTF_1_CONFEXP
#define DTF_1_CONFEXP	0x00000002
#endif
#ifndef DF_P1_LAZYLOAD
#define DF_P1_LAZYLOAD	0x00000001
#endif
#ifndef DF_P1_GROUPPERM
#define DF_P1_GROUPPERM	0x00000002
#endif
#ifndef VER_DEF_NONE
#define VER_DEF_NONE	0
#endif
#ifndef VER_DEF_CURRENT
#define VER_DEF_CURRENT	1
#endif
#ifndef VER_DEF_NUM
#define VER_DEF_NUM	2
#endif
#ifndef VER_FLG_BASE
#define VER_FLG_BASE	0x1
#endif
#ifndef VER_FLG_WEAK
#define VER_FLG_WEAK	0x2
#endif
#ifndef VER_NEED_NONE
#define VER_NEED_NONE	 0
#endif
#ifndef VER_NEED_CURRENT
#define VER_NEED_CURRENT 1
#endif
#ifndef VER_NEED_NUM
#define VER_NEED_NUM	 2
#endif
#ifndef VER_FLG_WEAK
#define VER_FLG_WEAK	0x2
#endif
#ifndef AT_NULL
#define AT_NULL		0
#endif
#ifndef AT_IGNORE
#define AT_IGNORE	1
#endif
#ifndef AT_EXECFD
#define AT_EXECFD	2
#endif
#ifndef AT_PHDR
#define AT_PHDR		3
#endif
#ifndef AT_PHENT
#define AT_PHENT	4
#endif
#ifndef AT_PHNUM
#define AT_PHNUM	5
#endif
#ifndef AT_PAGESZ
#define AT_PAGESZ	6
#endif
#ifndef AT_BASE
#define AT_BASE		7
#endif
#ifndef AT_FLAGS
#define AT_FLAGS	8
#endif
#ifndef AT_ENTRY
#define AT_ENTRY	9
#endif
#ifndef AT_NOTELF
#define AT_NOTELF	10
#endif
#ifndef AT_UID
#define AT_UID		11
#endif
#ifndef AT_EUID
#define AT_EUID		12
#endif
#ifndef AT_GID
#define AT_GID		13
#endif
#ifndef AT_EGID
#define AT_EGID		14
#endif
#ifndef AT_CLKTCK
#define AT_CLKTCK	17
#endif
#ifndef AT_PLATFORM
#define AT_PLATFORM	15
#endif
#ifndef AT_HWCAP
#define AT_HWCAP	16
#endif
#ifndef AT_FPUCW
#define AT_FPUCW	18
#endif
#ifndef AT_DCACHEBSIZE
#define AT_DCACHEBSIZE	19
#endif
#ifndef AT_ICACHEBSIZE
#define AT_ICACHEBSIZE	20
#endif
#ifndef AT_UCACHEBSIZE
#define AT_UCACHEBSIZE	21
#endif
#ifndef AT_IGNOREPPC
#define AT_IGNOREPPC	22
#endif
#ifndef AT_BASE_PLATFORM
#define AT_BASE_PLATFORM 24
#endif
#ifndef AT_RANDOM
#define AT_RANDOM	25
#endif
#ifndef AT_HWCAP2
#define AT_HWCAP2	26
#endif
#ifndef AT_EXECFN
#define AT_EXECFN	31
#endif
#ifndef AT_SYSINFO
#define AT_SYSINFO	32
#endif
#ifndef AT_SYSINFO_EHDR
#define AT_SYSINFO_EHDR	33
#endif
#ifndef AT_L1I_CACHESHAPE
#define AT_L1I_CACHESHAPE	34
#endif
#ifndef AT_L1D_CACHESHAPE
#define AT_L1D_CACHESHAPE	35
#endif
#ifndef AT_L2_CACHESHAPE
#define AT_L2_CACHESHAPE	36
#endif
#ifndef AT_L3_CACHESHAPE
#define AT_L3_CACHESHAPE	37
#endif
#ifndef AT_L1I_CACHESIZE
#define AT_L1I_CACHESIZE	40
#endif
#ifndef AT_L1I_CACHEGEOMETRY
#define AT_L1I_CACHEGEOMETRY	41
#endif
#ifndef AT_L1D_CACHESIZE
#define AT_L1D_CACHESIZE	42
#endif
#ifndef AT_L1D_CACHEGEOMETRY
#define AT_L1D_CACHEGEOMETRY	43
#endif
#ifndef AT_L2_CACHESIZE
#define AT_L2_CACHESIZE		44
#endif
#ifndef AT_L2_CACHEGEOMETRY
#define AT_L2_CACHEGEOMETRY	45
#endif
#ifndef AT_L3_CACHESIZE
#define AT_L3_CACHESIZE		46
#endif
#ifndef AT_L3_CACHEGEOMETRY
#define AT_L3_CACHEGEOMETRY	47
#endif
#ifndef AT_MINSIGSTKSZ
#define AT_MINSIGSTKSZ		51
#endif
#ifndef ELF_NOTE_SOLARIS
#define ELF_NOTE_SOLARIS	"SUNW Solaris"
#endif
#ifndef ELF_NOTE_GNU
#define ELF_NOTE_GNU		"GNU"
#endif
#ifndef ELF_NOTE_PAGESIZE_HINT
#define ELF_NOTE_PAGESIZE_HINT	1
#endif
#ifndef NT_GNU_ABI_TAG
#define NT_GNU_ABI_TAG	1
#endif
#ifndef ELF_NOTE_ABI
#define ELF_NOTE_ABI	NT_GNU_ABI_TAG
#endif
#ifndef ELF_NOTE_OS_LINUX
#define ELF_NOTE_OS_LINUX	0
#endif
#ifndef ELF_NOTE_OS_GNU
#define ELF_NOTE_OS_GNU		1
#endif
#ifndef ELF_NOTE_OS_SOLARIS2
#define ELF_NOTE_OS_SOLARIS2	2
#endif
#ifndef ELF_NOTE_OS_FREEBSD
#define ELF_NOTE_OS_FREEBSD	3
#endif
#ifndef NT_GNU_BUILD_ID
#define NT_GNU_BUILD_ID	3
#endif
#ifndef NT_GNU_GOLD_VERSION
#define NT_GNU_GOLD_VERSION	4
#endif
#ifndef NT_GNU_PROPERTY_TYPE_0
#define NT_GNU_PROPERTY_TYPE_0	5
#endif
#ifndef ELF32_M_SYM
#define ELF32_M_SYM(info)	((info) >> 8)
#endif
#ifndef ELF32_M_SIZE
#define ELF32_M_SIZE(info)	((unsigned char) (info))
#endif
#ifndef ELF32_M_INFO
#define ELF32_M_INFO(sym, size)	(((sym) << 8) + (unsigned char) (size))
#endif
#ifndef ELF64_M_SYM
#define ELF64_M_SYM(info)	ELF32_M_SYM (info)
#endif
#ifndef ELF64_M_SIZE
#define ELF64_M_SIZE(info)	ELF32_M_SIZE (info)
#endif
#ifndef ELF64_M_INFO
#define ELF64_M_INFO(sym, size)	ELF32_M_INFO (sym, size)
#endif
#ifndef EF_CPU32
#define EF_CPU32	0x00810000
#endif
#ifndef R_68K_NONE
#define R_68K_NONE	0
#endif
#ifndef R_68K_32
#define R_68K_32	1
#endif
#ifndef R_68K_16
#define R_68K_16	2
#endif
#ifndef R_68K_8
#define R_68K_8		3
#endif
#ifndef R_68K_PC32
#define R_68K_PC32	4
#endif
#ifndef R_68K_PC16
#define R_68K_PC16	5
#endif
#ifndef R_68K_PC8
#define R_68K_PC8	6
#endif
#ifndef R_68K_GOT32
#define R_68K_GOT32	7
#endif
#ifndef R_68K_GOT16
#define R_68K_GOT16	8
#endif
#ifndef R_68K_GOT8
#define R_68K_GOT8	9
#endif
#ifndef R_68K_GOT32O
#define R_68K_GOT32O	10
#endif
#ifndef R_68K_GOT16O
#define R_68K_GOT16O	11
#endif
#ifndef R_68K_GOT8O
#define R_68K_GOT8O	12
#endif
#ifndef R_68K_PLT32
#define R_68K_PLT32	13
#endif
#ifndef R_68K_PLT16
#define R_68K_PLT16	14
#endif
#ifndef R_68K_PLT8
#define R_68K_PLT8	15
#endif
#ifndef R_68K_PLT32O
#define R_68K_PLT32O	16
#endif
#ifndef R_68K_PLT16O
#define R_68K_PLT16O	17
#endif
#ifndef R_68K_PLT8O
#define R_68K_PLT8O	18
#endif
#ifndef R_68K_COPY
#define R_68K_COPY	19
#endif
#ifndef R_68K_GLOB_DAT
#define R_68K_GLOB_DAT	20
#endif
#ifndef R_68K_JMP_SLOT
#define R_68K_JMP_SLOT	21
#endif
#ifndef R_68K_RELATIVE
#define R_68K_RELATIVE	22
#endif
#ifndef R_68K_TLS_GD32
#define R_68K_TLS_GD32	25
#endif
#ifndef R_68K_TLS_GD16
#define R_68K_TLS_GD16	26
#endif
#ifndef R_68K_TLS_GD8
#define R_68K_TLS_GD8	27
#endif
#ifndef R_68K_TLS_LDM32
#define R_68K_TLS_LDM32	28
#endif
#ifndef R_68K_TLS_LDM16
#define R_68K_TLS_LDM16	29
#endif
#ifndef R_68K_TLS_LDM8
#define R_68K_TLS_LDM8	30
#endif
#ifndef R_68K_TLS_LDO32
#define R_68K_TLS_LDO32	31
#endif
#ifndef R_68K_TLS_LDO16
#define R_68K_TLS_LDO16	32
#endif
#ifndef R_68K_TLS_LDO8
#define R_68K_TLS_LDO8	33
#endif
#ifndef R_68K_TLS_IE32
#define R_68K_TLS_IE32	34
#endif
#ifndef R_68K_TLS_IE16
#define R_68K_TLS_IE16	35
#endif
#ifndef R_68K_TLS_IE8
#define R_68K_TLS_IE8	36
#endif
#ifndef R_68K_TLS_LE32
#define R_68K_TLS_LE32	37
#endif
#ifndef R_68K_TLS_LE16
#define R_68K_TLS_LE16	38
#endif
#ifndef R_68K_TLS_LE8
#define R_68K_TLS_LE8	39
#endif
#ifndef R_68K_TLS_DTPMOD32
#define R_68K_TLS_DTPMOD32	40
#endif
#ifndef R_68K_TLS_DTPREL32
#define R_68K_TLS_DTPREL32	41
#endif
#ifndef R_68K_TLS_TPREL32
#define R_68K_TLS_TPREL32	42
#endif
#ifndef R_68K_NUM
#define R_68K_NUM	43
#endif
#ifndef R_386_NONE
#define R_386_NONE	   0
#endif
#ifndef R_386_32
#define R_386_32	   1
#endif
#ifndef R_386_PC32
#define R_386_PC32	   2
#endif
#ifndef R_386_GOT32
#define R_386_GOT32	   3
#endif
#ifndef R_386_PLT32
#define R_386_PLT32	   4
#endif
#ifndef R_386_COPY
#define R_386_COPY	   5
#endif
#ifndef R_386_GLOB_DAT
#define R_386_GLOB_DAT	   6
#endif
#ifndef R_386_JMP_SLOT
#define R_386_JMP_SLOT	   7
#endif
#ifndef R_386_RELATIVE
#define R_386_RELATIVE	   8
#endif
#ifndef R_386_GOTOFF
#define R_386_GOTOFF	   9
#endif
#ifndef R_386_GOTPC
#define R_386_GOTPC	   10
#endif
#ifndef R_386_32PLT
#define R_386_32PLT	   11
#endif
#ifndef R_386_TLS_TPOFF
#define R_386_TLS_TPOFF	   14
#endif
#ifndef R_386_TLS_IE
#define R_386_TLS_IE	   15
#endif
#ifndef R_386_TLS_GOTIE
#define R_386_TLS_GOTIE	   16
#endif
#ifndef R_386_TLS_LE
#define R_386_TLS_LE	   17
#endif
#ifndef R_386_TLS_GD
#define R_386_TLS_GD	   18
#endif
#ifndef R_386_TLS_LDM
#define R_386_TLS_LDM	   19
#endif
#ifndef R_386_16
#define R_386_16	   20
#endif
#ifndef R_386_PC16
#define R_386_PC16	   21
#endif
#ifndef R_386_8
#define R_386_8		   22
#endif
#ifndef R_386_PC8
#define R_386_PC8	   23
#endif
#ifndef R_386_TLS_GD_32
#define R_386_TLS_GD_32	   24
#endif
#ifndef R_386_TLS_GD_PUSH
#define R_386_TLS_GD_PUSH  25
#endif
#ifndef R_386_TLS_GD_CALL
#define R_386_TLS_GD_CALL  26
#endif
#ifndef R_386_TLS_GD_POP
#define R_386_TLS_GD_POP   27
#endif
#ifndef R_386_TLS_LDM_32
#define R_386_TLS_LDM_32   28
#endif
#ifndef R_386_TLS_LDM_PUSH
#define R_386_TLS_LDM_PUSH 29
#endif
#ifndef R_386_TLS_LDM_CALL
#define R_386_TLS_LDM_CALL 30
#endif
#ifndef R_386_TLS_LDM_POP
#define R_386_TLS_LDM_POP  31
#endif
#ifndef R_386_TLS_LDO_32
#define R_386_TLS_LDO_32   32
#endif
#ifndef R_386_TLS_IE_32
#define R_386_TLS_IE_32	   33
#endif
#ifndef R_386_TLS_LE_32
#define R_386_TLS_LE_32	   34
#endif
#ifndef R_386_TLS_DTPMOD32
#define R_386_TLS_DTPMOD32 35
#endif
#ifndef R_386_TLS_DTPOFF32
#define R_386_TLS_DTPOFF32 36
#endif
#ifndef R_386_TLS_TPOFF32
#define R_386_TLS_TPOFF32  37
#endif
#ifndef R_386_SIZE32
#define R_386_SIZE32       38
#endif
#ifndef R_386_TLS_GOTDESC
#define R_386_TLS_GOTDESC  39
#endif
#ifndef R_386_TLS_DESC_CALL
#define R_386_TLS_DESC_CALL 40
#endif
#ifndef R_386_TLS_DESC
#define R_386_TLS_DESC     41
#endif
#ifndef R_386_IRELATIVE
#define R_386_IRELATIVE	   42
#endif
#ifndef R_386_GOT32X
#define R_386_GOT32X	   43
#endif
#ifndef R_386_NUM
#define R_386_NUM	   44
#endif
#ifndef STT_SPARC_REGISTER
#define STT_SPARC_REGISTER	13
#endif
#ifndef EF_SPARCV9_MM
#define EF_SPARCV9_MM		3
#endif
#ifndef EF_SPARCV9_TSO
#define EF_SPARCV9_TSO		0
#endif
#ifndef EF_SPARCV9_PSO
#define EF_SPARCV9_PSO		1
#endif
#ifndef EF_SPARCV9_RMO
#define EF_SPARCV9_RMO		2
#endif
#ifndef EF_SPARC_LEDATA
#define EF_SPARC_LEDATA		0x800000
#endif
#ifndef EF_SPARC_EXT_MASK
#define EF_SPARC_EXT_MASK	0xFFFF00
#endif
#ifndef EF_SPARC_32PLUS
#define EF_SPARC_32PLUS		0x000100
#endif
#ifndef EF_SPARC_SUN_US1
#define EF_SPARC_SUN_US1	0x000200
#endif
#ifndef EF_SPARC_HAL_R1
#define EF_SPARC_HAL_R1		0x000400
#endif
#ifndef EF_SPARC_SUN_US3
#define EF_SPARC_SUN_US3	0x000800
#endif
#ifndef R_SPARC_NONE
#define R_SPARC_NONE		0
#endif
#ifndef R_SPARC_8
#define R_SPARC_8		1
#endif
#ifndef R_SPARC_16
#define R_SPARC_16		2
#endif
#ifndef R_SPARC_32
#define R_SPARC_32		3
#endif
#ifndef R_SPARC_DISP8
#define R_SPARC_DISP8		4
#endif
#ifndef R_SPARC_DISP16
#define R_SPARC_DISP16		5
#endif
#ifndef R_SPARC_DISP32
#define R_SPARC_DISP32		6
#endif
#ifndef R_SPARC_WDISP30
#define R_SPARC_WDISP30		7
#endif
#ifndef R_SPARC_WDISP22
#define R_SPARC_WDISP22		8
#endif
#ifndef R_SPARC_HI22
#define R_SPARC_HI22		9
#endif
#ifndef R_SPARC_22
#define R_SPARC_22		10
#endif
#ifndef R_SPARC_13
#define R_SPARC_13		11
#endif
#ifndef R_SPARC_LO10
#define R_SPARC_LO10		12
#endif
#ifndef R_SPARC_GOT10
#define R_SPARC_GOT10		13
#endif
#ifndef R_SPARC_GOT13
#define R_SPARC_GOT13		14
#endif
#ifndef R_SPARC_GOT22
#define R_SPARC_GOT22		15
#endif
#ifndef R_SPARC_PC10
#define R_SPARC_PC10		16
#endif
#ifndef R_SPARC_PC22
#define R_SPARC_PC22		17
#endif
#ifndef R_SPARC_WPLT30
#define R_SPARC_WPLT30		18
#endif
#ifndef R_SPARC_COPY
#define R_SPARC_COPY		19
#endif
#ifndef R_SPARC_GLOB_DAT
#define R_SPARC_GLOB_DAT	20
#endif
#ifndef R_SPARC_JMP_SLOT
#define R_SPARC_JMP_SLOT	21
#endif
#ifndef R_SPARC_RELATIVE
#define R_SPARC_RELATIVE	22
#endif
#ifndef R_SPARC_UA32
#define R_SPARC_UA32		23
#endif
#ifndef R_SPARC_PLT32
#define R_SPARC_PLT32		24
#endif
#ifndef R_SPARC_HIPLT22
#define R_SPARC_HIPLT22		25
#endif
#ifndef R_SPARC_LOPLT10
#define R_SPARC_LOPLT10		26
#endif
#ifndef R_SPARC_PCPLT32
#define R_SPARC_PCPLT32		27
#endif
#ifndef R_SPARC_PCPLT22
#define R_SPARC_PCPLT22		28
#endif
#ifndef R_SPARC_PCPLT10
#define R_SPARC_PCPLT10		29
#endif
#ifndef R_SPARC_10
#define R_SPARC_10		30
#endif
#ifndef R_SPARC_11
#define R_SPARC_11		31
#endif
#ifndef R_SPARC_64
#define R_SPARC_64		32
#endif
#ifndef R_SPARC_OLO10
#define R_SPARC_OLO10		33
#endif
#ifndef R_SPARC_HH22
#define R_SPARC_HH22		34
#endif
#ifndef R_SPARC_HM10
#define R_SPARC_HM10		35
#endif
#ifndef R_SPARC_LM22
#define R_SPARC_LM22		36
#endif
#ifndef R_SPARC_PC_HH22
#define R_SPARC_PC_HH22		37
#endif
#ifndef R_SPARC_PC_HM10
#define R_SPARC_PC_HM10		38
#endif
#ifndef R_SPARC_PC_LM22
#define R_SPARC_PC_LM22		39
#endif
#ifndef R_SPARC_WDISP16
#define R_SPARC_WDISP16		40
#endif
#ifndef R_SPARC_WDISP19
#define R_SPARC_WDISP19		41
#endif
#ifndef R_SPARC_GLOB_JMP
#define R_SPARC_GLOB_JMP	42
#endif
#ifndef R_SPARC_7
#define R_SPARC_7		43
#endif
#ifndef R_SPARC_5
#define R_SPARC_5		44
#endif
#ifndef R_SPARC_6
#define R_SPARC_6		45
#endif
#ifndef R_SPARC_DISP64
#define R_SPARC_DISP64		46
#endif
#ifndef R_SPARC_PLT64
#define R_SPARC_PLT64		47
#endif
#ifndef R_SPARC_HIX22
#define R_SPARC_HIX22		48
#endif
#ifndef R_SPARC_LOX10
#define R_SPARC_LOX10		49
#endif
#ifndef R_SPARC_H44
#define R_SPARC_H44		50
#endif
#ifndef R_SPARC_M44
#define R_SPARC_M44		51
#endif
#ifndef R_SPARC_L44
#define R_SPARC_L44		52
#endif
#ifndef R_SPARC_REGISTER
#define R_SPARC_REGISTER	53
#endif
#ifndef R_SPARC_UA64
#define R_SPARC_UA64		54
#endif
#ifndef R_SPARC_UA16
#define R_SPARC_UA16		55
#endif
#ifndef R_SPARC_TLS_GD_HI22
#define R_SPARC_TLS_GD_HI22	56
#endif
#ifndef R_SPARC_TLS_GD_LO10
#define R_SPARC_TLS_GD_LO10	57
#endif
#ifndef R_SPARC_TLS_GD_ADD
#define R_SPARC_TLS_GD_ADD	58
#endif
#ifndef R_SPARC_TLS_GD_CALL
#define R_SPARC_TLS_GD_CALL	59
#endif
#ifndef R_SPARC_TLS_LDM_HI22
#define R_SPARC_TLS_LDM_HI22	60
#endif
#ifndef R_SPARC_TLS_LDM_LO10
#define R_SPARC_TLS_LDM_LO10	61
#endif
#ifndef R_SPARC_TLS_LDM_ADD
#define R_SPARC_TLS_LDM_ADD	62
#endif
#ifndef R_SPARC_TLS_LDM_CALL
#define R_SPARC_TLS_LDM_CALL	63
#endif
#ifndef R_SPARC_TLS_LDO_HIX22
#define R_SPARC_TLS_LDO_HIX22	64
#endif
#ifndef R_SPARC_TLS_LDO_LOX10
#define R_SPARC_TLS_LDO_LOX10	65
#endif
#ifndef R_SPARC_TLS_LDO_ADD
#define R_SPARC_TLS_LDO_ADD	66
#endif
#ifndef R_SPARC_TLS_IE_HI22
#define R_SPARC_TLS_IE_HI22	67
#endif
#ifndef R_SPARC_TLS_IE_LO10
#define R_SPARC_TLS_IE_LO10	68
#endif
#ifndef R_SPARC_TLS_IE_LD
#define R_SPARC_TLS_IE_LD	69
#endif
#ifndef R_SPARC_TLS_IE_LDX
#define R_SPARC_TLS_IE_LDX	70
#endif
#ifndef R_SPARC_TLS_IE_ADD
#define R_SPARC_TLS_IE_ADD	71
#endif
#ifndef R_SPARC_TLS_LE_HIX22
#define R_SPARC_TLS_LE_HIX22	72
#endif
#ifndef R_SPARC_TLS_LE_LOX10
#define R_SPARC_TLS_LE_LOX10	73
#endif
#ifndef R_SPARC_TLS_DTPMOD32
#define R_SPARC_TLS_DTPMOD32	74
#endif
#ifndef R_SPARC_TLS_DTPMOD64
#define R_SPARC_TLS_DTPMOD64	75
#endif
#ifndef R_SPARC_TLS_DTPOFF32
#define R_SPARC_TLS_DTPOFF32	76
#endif
#ifndef R_SPARC_TLS_DTPOFF64
#define R_SPARC_TLS_DTPOFF64	77
#endif
#ifndef R_SPARC_TLS_TPOFF32
#define R_SPARC_TLS_TPOFF32	78
#endif
#ifndef R_SPARC_TLS_TPOFF64
#define R_SPARC_TLS_TPOFF64	79
#endif
#ifndef R_SPARC_GOTDATA_HIX22
#define R_SPARC_GOTDATA_HIX22	80
#endif
#ifndef R_SPARC_GOTDATA_LOX10
#define R_SPARC_GOTDATA_LOX10	81
#endif
#ifndef R_SPARC_GOTDATA_OP_HIX22
#define R_SPARC_GOTDATA_OP_HIX22	82
#endif
#ifndef R_SPARC_GOTDATA_OP_LOX10
#define R_SPARC_GOTDATA_OP_LOX10	83
#endif
#ifndef R_SPARC_GOTDATA_OP
#define R_SPARC_GOTDATA_OP	84
#endif
#ifndef R_SPARC_H34
#define R_SPARC_H34		85
#endif
#ifndef R_SPARC_SIZE32
#define R_SPARC_SIZE32		86
#endif
#ifndef R_SPARC_SIZE64
#define R_SPARC_SIZE64		87
#endif
#ifndef R_SPARC_GNU_VTINHERIT
#define R_SPARC_GNU_VTINHERIT	250
#endif
#ifndef R_SPARC_GNU_VTENTRY
#define R_SPARC_GNU_VTENTRY	251
#endif
#ifndef R_SPARC_REV32
#define R_SPARC_REV32		252
#endif
#ifndef R_SPARC_NUM
#define R_SPARC_NUM		253
#endif
#ifndef DT_SPARC_REGISTER
#define DT_SPARC_REGISTER 0x70000001
#endif
#ifndef DT_SPARC_NUM
#define DT_SPARC_NUM	2
#endif
#ifndef EF_MIPS_NOREORDER
#define EF_MIPS_NOREORDER   1
#endif
#ifndef EF_MIPS_PIC
#define EF_MIPS_PIC	    2
#endif
#ifndef EF_MIPS_CPIC
#define EF_MIPS_CPIC	    4
#endif
#ifndef EF_MIPS_XGOT
#define EF_MIPS_XGOT	    8
#endif
#ifndef EF_MIPS_64BIT_WHIRL
#define EF_MIPS_64BIT_WHIRL 16
#endif
#ifndef EF_MIPS_ABI2
#define EF_MIPS_ABI2	    32
#endif
#ifndef EF_MIPS_ABI_ON32
#define EF_MIPS_ABI_ON32    64
#endif
#ifndef EF_MIPS_FP64
#define EF_MIPS_FP64	    512
#endif
#ifndef EF_MIPS_NAN2008
#define EF_MIPS_NAN2008     1024
#endif
#ifndef EF_MIPS_ARCH
#define EF_MIPS_ARCH	    0xf0000000
#endif
#ifndef EF_MIPS_ARCH_1
#define EF_MIPS_ARCH_1	    0x00000000
#endif
#ifndef EF_MIPS_ARCH_2
#define EF_MIPS_ARCH_2	    0x10000000
#endif
#ifndef EF_MIPS_ARCH_3
#define EF_MIPS_ARCH_3	    0x20000000
#endif
#ifndef EF_MIPS_ARCH_4
#define EF_MIPS_ARCH_4	    0x30000000
#endif
#ifndef EF_MIPS_ARCH_5
#define EF_MIPS_ARCH_5	    0x40000000
#endif
#ifndef EF_MIPS_ARCH_32
#define EF_MIPS_ARCH_32     0x50000000
#endif
#ifndef EF_MIPS_ARCH_64
#define EF_MIPS_ARCH_64     0x60000000
#endif
#ifndef EF_MIPS_ARCH_32R2
#define EF_MIPS_ARCH_32R2   0x70000000
#endif
#ifndef EF_MIPS_ARCH_64R2
#define EF_MIPS_ARCH_64R2   0x80000000
#endif
#ifndef E_MIPS_ARCH_1
#define E_MIPS_ARCH_1	  0x00000000
#endif
#ifndef E_MIPS_ARCH_2
#define E_MIPS_ARCH_2	  0x10000000
#endif
#ifndef E_MIPS_ARCH_3
#define E_MIPS_ARCH_3	  0x20000000
#endif
#ifndef E_MIPS_ARCH_4
#define E_MIPS_ARCH_4	  0x30000000
#endif
#ifndef E_MIPS_ARCH_5
#define E_MIPS_ARCH_5	  0x40000000
#endif
#ifndef E_MIPS_ARCH_32
#define E_MIPS_ARCH_32	  0x50000000
#endif
#ifndef E_MIPS_ARCH_64
#define E_MIPS_ARCH_64	  0x60000000
#endif
#ifndef SHN_MIPS_ACOMMON
#define SHN_MIPS_ACOMMON    0xff00
#endif
#ifndef SHN_MIPS_TEXT
#define SHN_MIPS_TEXT	    0xff01
#endif
#ifndef SHN_MIPS_DATA
#define SHN_MIPS_DATA	    0xff02
#endif
#ifndef SHN_MIPS_SCOMMON
#define SHN_MIPS_SCOMMON    0xff03
#endif
#ifndef SHN_MIPS_SUNDEFINED
#define SHN_MIPS_SUNDEFINED 0xff04
#endif
#ifndef SHT_MIPS_LIBLIST
#define SHT_MIPS_LIBLIST       0x70000000
#endif
#ifndef SHT_MIPS_MSYM
#define SHT_MIPS_MSYM	       0x70000001
#endif
#ifndef SHT_MIPS_CONFLICT
#define SHT_MIPS_CONFLICT      0x70000002
#endif
#ifndef SHT_MIPS_GPTAB
#define SHT_MIPS_GPTAB	       0x70000003
#endif
#ifndef SHT_MIPS_UCODE
#define SHT_MIPS_UCODE	       0x70000004
#endif
#ifndef SHT_MIPS_DEBUG
#define SHT_MIPS_DEBUG	       0x70000005
#endif
#ifndef SHT_MIPS_REGINFO
#define SHT_MIPS_REGINFO       0x70000006
#endif
#ifndef SHT_MIPS_PACKAGE
#define SHT_MIPS_PACKAGE       0x70000007
#endif
#ifndef SHT_MIPS_PACKSYM
#define SHT_MIPS_PACKSYM       0x70000008
#endif
#ifndef SHT_MIPS_RELD
#define SHT_MIPS_RELD	       0x70000009
#endif
#ifndef SHT_MIPS_IFACE
#define SHT_MIPS_IFACE         0x7000000b
#endif
#ifndef SHT_MIPS_CONTENT
#define SHT_MIPS_CONTENT       0x7000000c
#endif
#ifndef SHT_MIPS_OPTIONS
#define SHT_MIPS_OPTIONS       0x7000000d
#endif
#ifndef SHT_MIPS_SHDR
#define SHT_MIPS_SHDR	       0x70000010
#endif
#ifndef SHT_MIPS_FDESC
#define SHT_MIPS_FDESC	       0x70000011
#endif
#ifndef SHT_MIPS_EXTSYM
#define SHT_MIPS_EXTSYM	       0x70000012
#endif
#ifndef SHT_MIPS_DENSE
#define SHT_MIPS_DENSE	       0x70000013
#endif
#ifndef SHT_MIPS_PDESC
#define SHT_MIPS_PDESC	       0x70000014
#endif
#ifndef SHT_MIPS_LOCSYM
#define SHT_MIPS_LOCSYM	       0x70000015
#endif
#ifndef SHT_MIPS_AUXSYM
#define SHT_MIPS_AUXSYM	       0x70000016
#endif
#ifndef SHT_MIPS_OPTSYM
#define SHT_MIPS_OPTSYM	       0x70000017
#endif
#ifndef SHT_MIPS_LOCSTR
#define SHT_MIPS_LOCSTR	       0x70000018
#endif
#ifndef SHT_MIPS_LINE
#define SHT_MIPS_LINE	       0x70000019
#endif
#ifndef SHT_MIPS_RFDESC
#define SHT_MIPS_RFDESC	       0x7000001a
#endif
#ifndef SHT_MIPS_DELTASYM
#define SHT_MIPS_DELTASYM      0x7000001b
#endif
#ifndef SHT_MIPS_DELTAINST
#define SHT_MIPS_DELTAINST     0x7000001c
#endif
#ifndef SHT_MIPS_DELTACLASS
#define SHT_MIPS_DELTACLASS    0x7000001d
#endif
#ifndef SHT_MIPS_DWARF
#define SHT_MIPS_DWARF         0x7000001e
#endif
#ifndef SHT_MIPS_DELTADECL
#define SHT_MIPS_DELTADECL     0x7000001f
#endif
#ifndef SHT_MIPS_SYMBOL_LIB
#define SHT_MIPS_SYMBOL_LIB    0x70000020
#endif
#ifndef SHT_MIPS_EVENTS
#define SHT_MIPS_EVENTS	       0x70000021
#endif
#ifndef SHT_MIPS_TRANSLATE
#define SHT_MIPS_TRANSLATE     0x70000022
#endif
#ifndef SHT_MIPS_PIXIE
#define SHT_MIPS_PIXIE	       0x70000023
#endif
#ifndef SHT_MIPS_XLATE
#define SHT_MIPS_XLATE	       0x70000024
#endif
#ifndef SHT_MIPS_XLATE_DEBUG
#define SHT_MIPS_XLATE_DEBUG   0x70000025
#endif
#ifndef SHT_MIPS_WHIRL
#define SHT_MIPS_WHIRL	       0x70000026
#endif
#ifndef SHT_MIPS_EH_REGION
#define SHT_MIPS_EH_REGION     0x70000027
#endif
#ifndef SHT_MIPS_XLATE_OLD
#define SHT_MIPS_XLATE_OLD     0x70000028
#endif
#ifndef SHT_MIPS_PDR_EXCEPTION
#define SHT_MIPS_PDR_EXCEPTION 0x70000029
#endif
#ifndef SHF_MIPS_GPREL
#define SHF_MIPS_GPREL	 0x10000000
#endif
#ifndef SHF_MIPS_MERGE
#define SHF_MIPS_MERGE	 0x20000000
#endif
#ifndef SHF_MIPS_ADDR
#define SHF_MIPS_ADDR	 0x40000000
#endif
#ifndef SHF_MIPS_STRINGS
#define SHF_MIPS_STRINGS 0x80000000
#endif
#ifndef SHF_MIPS_NOSTRIP
#define SHF_MIPS_NOSTRIP 0x08000000
#endif
#ifndef SHF_MIPS_LOCAL
#define SHF_MIPS_LOCAL	 0x04000000
#endif
#ifndef SHF_MIPS_NAMES
#define SHF_MIPS_NAMES	 0x02000000
#endif
#ifndef SHF_MIPS_NODUPE
#define SHF_MIPS_NODUPE	 0x01000000
#endif
#ifndef STO_MIPS_DEFAULT
#define STO_MIPS_DEFAULT		0x0
#endif
#ifndef STO_MIPS_INTERNAL
#define STO_MIPS_INTERNAL		0x1
#endif
#ifndef STO_MIPS_HIDDEN
#define STO_MIPS_HIDDEN			0x2
#endif
#ifndef STO_MIPS_PROTECTED
#define STO_MIPS_PROTECTED		0x3
#endif
#ifndef STO_MIPS_PLT
#define STO_MIPS_PLT			0x8
#endif
#ifndef STO_MIPS_SC_ALIGN_UNUSED
#define STO_MIPS_SC_ALIGN_UNUSED	0xff
#endif
#ifndef STB_MIPS_SPLIT_COMMON
#define STB_MIPS_SPLIT_COMMON		13
#endif
#ifndef ODK_NULL
#define ODK_NULL	0
#endif
#ifndef ODK_REGINFO
#define ODK_REGINFO	1
#endif
#ifndef ODK_EXCEPTIONS
#define ODK_EXCEPTIONS	2
#endif
#ifndef ODK_PAD
#define ODK_PAD		3
#endif
#ifndef ODK_HWPATCH
#define ODK_HWPATCH	4
#endif
#ifndef ODK_FILL
#define ODK_FILL	5
#endif
#ifndef ODK_TAGS
#define ODK_TAGS	6
#endif
#ifndef ODK_HWAND
#define ODK_HWAND	7
#endif
#ifndef ODK_HWOR
#define ODK_HWOR	8
#endif
#ifndef OEX_FPU_MIN
#define OEX_FPU_MIN	0x1f
#endif
#ifndef OEX_FPU_MAX
#define OEX_FPU_MAX	0x1f00
#endif
#ifndef OEX_PAGE0
#define OEX_PAGE0	0x10000
#endif
#ifndef OEX_SMM
#define OEX_SMM		0x20000
#endif
#ifndef OEX_FPDBUG
#define OEX_FPDBUG	0x40000
#endif
#ifndef OEX_PRECISEFP
#define OEX_PRECISEFP	OEX_FPDBUG
#endif
#ifndef OEX_DISMISS
#define OEX_DISMISS	0x80000
#endif
#ifndef OEX_FPU_INVAL
#define OEX_FPU_INVAL	0x10
#endif
#ifndef OEX_FPU_DIV0
#define OEX_FPU_DIV0	0x08
#endif
#ifndef OEX_FPU_OFLO
#define OEX_FPU_OFLO	0x04
#endif
#ifndef OEX_FPU_UFLO
#define OEX_FPU_UFLO	0x02
#endif
#ifndef OEX_FPU_INEX
#define OEX_FPU_INEX	0x01
#endif
#ifndef OHW_R4KEOP
#define OHW_R4KEOP	0x1
#endif
#ifndef OHW_R8KPFETCH
#define OHW_R8KPFETCH	0x2
#endif
#ifndef OHW_R5KEOP
#define OHW_R5KEOP	0x4
#endif
#ifndef OHW_R5KCVTL
#define OHW_R5KCVTL	0x8
#endif
#ifndef OPAD_PREFIX
#define OPAD_PREFIX	0x1
#endif
#ifndef OPAD_POSTFIX
#define OPAD_POSTFIX	0x2
#endif
#ifndef OPAD_SYMBOL
#define OPAD_SYMBOL	0x4
#endif
#ifndef OHWA0_R4KEOP_CHECKED
#define OHWA0_R4KEOP_CHECKED	0x00000001
#endif
#ifndef OHWA1_R4KEOP_CLEAN
#define OHWA1_R4KEOP_CLEAN	0x00000002
#endif
#ifndef R_MIPS_NONE
#define R_MIPS_NONE		0
#endif
#ifndef R_MIPS_16
#define R_MIPS_16		1
#endif
#ifndef R_MIPS_32
#define R_MIPS_32		2
#endif
#ifndef R_MIPS_REL32
#define R_MIPS_REL32		3
#endif
#ifndef R_MIPS_26
#define R_MIPS_26		4
#endif
#ifndef R_MIPS_HI16
#define R_MIPS_HI16		5
#endif
#ifndef R_MIPS_LO16
#define R_MIPS_LO16		6
#endif
#ifndef R_MIPS_GPREL16
#define R_MIPS_GPREL16		7
#endif
#ifndef R_MIPS_LITERAL
#define R_MIPS_LITERAL		8
#endif
#ifndef R_MIPS_GOT16
#define R_MIPS_GOT16		9
#endif
#ifndef R_MIPS_PC16
#define R_MIPS_PC16		10
#endif
#ifndef R_MIPS_CALL16
#define R_MIPS_CALL16		11
#endif
#ifndef R_MIPS_GPREL32
#define R_MIPS_GPREL32		12
#endif
#ifndef R_MIPS_SHIFT5
#define R_MIPS_SHIFT5		16
#endif
#ifndef R_MIPS_SHIFT6
#define R_MIPS_SHIFT6		17
#endif
#ifndef R_MIPS_64
#define R_MIPS_64		18
#endif
#ifndef R_MIPS_GOT_DISP
#define R_MIPS_GOT_DISP		19
#endif
#ifndef R_MIPS_GOT_PAGE
#define R_MIPS_GOT_PAGE		20
#endif
#ifndef R_MIPS_GOT_OFST
#define R_MIPS_GOT_OFST		21
#endif
#ifndef R_MIPS_GOT_HI16
#define R_MIPS_GOT_HI16		22
#endif
#ifndef R_MIPS_GOT_LO16
#define R_MIPS_GOT_LO16		23
#endif
#ifndef R_MIPS_SUB
#define R_MIPS_SUB		24
#endif
#ifndef R_MIPS_INSERT_A
#define R_MIPS_INSERT_A		25
#endif
#ifndef R_MIPS_INSERT_B
#define R_MIPS_INSERT_B		26
#endif
#ifndef R_MIPS_DELETE
#define R_MIPS_DELETE		27
#endif
#ifndef R_MIPS_HIGHER
#define R_MIPS_HIGHER		28
#endif
#ifndef R_MIPS_HIGHEST
#define R_MIPS_HIGHEST		29
#endif
#ifndef R_MIPS_CALL_HI16
#define R_MIPS_CALL_HI16	30
#endif
#ifndef R_MIPS_CALL_LO16
#define R_MIPS_CALL_LO16	31
#endif
#ifndef R_MIPS_SCN_DISP
#define R_MIPS_SCN_DISP		32
#endif
#ifndef R_MIPS_REL16
#define R_MIPS_REL16		33
#endif
#ifndef R_MIPS_ADD_IMMEDIATE
#define R_MIPS_ADD_IMMEDIATE	34
#endif
#ifndef R_MIPS_PJUMP
#define R_MIPS_PJUMP		35
#endif
#ifndef R_MIPS_RELGOT
#define R_MIPS_RELGOT		36
#endif
#ifndef R_MIPS_JALR
#define R_MIPS_JALR		37
#endif
#ifndef R_MIPS_TLS_DTPMOD32
#define R_MIPS_TLS_DTPMOD32	38
#endif
#ifndef R_MIPS_TLS_DTPREL32
#define R_MIPS_TLS_DTPREL32	39
#endif
#ifndef R_MIPS_TLS_DTPMOD64
#define R_MIPS_TLS_DTPMOD64	40
#endif
#ifndef R_MIPS_TLS_DTPREL64
#define R_MIPS_TLS_DTPREL64	41
#endif
#ifndef R_MIPS_TLS_GD
#define R_MIPS_TLS_GD		42
#endif
#ifndef R_MIPS_TLS_LDM
#define R_MIPS_TLS_LDM		43
#endif
#ifndef R_MIPS_TLS_DTPREL_HI16
#define R_MIPS_TLS_DTPREL_HI16	44
#endif
#ifndef R_MIPS_TLS_DTPREL_LO16
#define R_MIPS_TLS_DTPREL_LO16	45
#endif
#ifndef R_MIPS_TLS_GOTTPREL
#define R_MIPS_TLS_GOTTPREL	46
#endif
#ifndef R_MIPS_TLS_TPREL32
#define R_MIPS_TLS_TPREL32	47
#endif
#ifndef R_MIPS_TLS_TPREL64
#define R_MIPS_TLS_TPREL64	48
#endif
#ifndef R_MIPS_TLS_TPREL_HI16
#define R_MIPS_TLS_TPREL_HI16	49
#endif
#ifndef R_MIPS_TLS_TPREL_LO16
#define R_MIPS_TLS_TPREL_LO16	50
#endif
#ifndef R_MIPS_GLOB_DAT
#define R_MIPS_GLOB_DAT		51
#endif
#ifndef R_MIPS_COPY
#define R_MIPS_COPY		126
#endif
#ifndef R_MIPS_JUMP_SLOT
#define R_MIPS_JUMP_SLOT        127
#endif
#ifndef R_MIPS_NUM
#define R_MIPS_NUM		128
#endif
#ifndef PT_MIPS_REGINFO
#define PT_MIPS_REGINFO	0x70000000
#endif
#ifndef PT_MIPS_RTPROC
#define PT_MIPS_RTPROC  0x70000001
#endif
#ifndef PT_MIPS_OPTIONS
#define PT_MIPS_OPTIONS 0x70000002
#endif
#ifndef PT_MIPS_ABIFLAGS
#define PT_MIPS_ABIFLAGS 0x70000003
#endif
#ifndef PF_MIPS_LOCAL
#define PF_MIPS_LOCAL	0x10000000
#endif
#ifndef DT_MIPS_RLD_VERSION
#define DT_MIPS_RLD_VERSION  0x70000001
#endif
#ifndef DT_MIPS_TIME_STAMP
#define DT_MIPS_TIME_STAMP   0x70000002
#endif
#ifndef DT_MIPS_ICHECKSUM
#define DT_MIPS_ICHECKSUM    0x70000003
#endif
#ifndef DT_MIPS_IVERSION
#define DT_MIPS_IVERSION     0x70000004
#endif
#ifndef DT_MIPS_FLAGS
#define DT_MIPS_FLAGS	     0x70000005
#endif
#ifndef DT_MIPS_BASE_ADDRESS
#define DT_MIPS_BASE_ADDRESS 0x70000006
#endif
#ifndef DT_MIPS_MSYM
#define DT_MIPS_MSYM	     0x70000007
#endif
#ifndef DT_MIPS_CONFLICT
#define DT_MIPS_CONFLICT     0x70000008
#endif
#ifndef DT_MIPS_LIBLIST
#define DT_MIPS_LIBLIST	     0x70000009
#endif
#ifndef DT_MIPS_LOCAL_GOTNO
#define DT_MIPS_LOCAL_GOTNO  0x7000000a
#endif
#ifndef DT_MIPS_CONFLICTNO
#define DT_MIPS_CONFLICTNO   0x7000000b
#endif
#ifndef DT_MIPS_LIBLISTNO
#define DT_MIPS_LIBLISTNO    0x70000010
#endif
#ifndef DT_MIPS_SYMTABNO
#define DT_MIPS_SYMTABNO     0x70000011
#endif
#ifndef DT_MIPS_UNREFEXTNO
#define DT_MIPS_UNREFEXTNO   0x70000012
#endif
#ifndef DT_MIPS_GOTSYM
#define DT_MIPS_GOTSYM	     0x70000013
#endif
#ifndef DT_MIPS_HIPAGENO
#define DT_MIPS_HIPAGENO     0x70000014
#endif
#ifndef DT_MIPS_RLD_MAP
#define DT_MIPS_RLD_MAP	     0x70000016
#endif
#ifndef DT_MIPS_DELTA_CLASS
#define DT_MIPS_DELTA_CLASS  0x70000017
#endif
#ifndef DT_MIPS_DELTA_CLASS_NO
#define DT_MIPS_DELTA_CLASS_NO    0x70000018
#endif
#ifndef DT_MIPS_DELTA_INSTANCE
#define DT_MIPS_DELTA_INSTANCE    0x70000019
#endif
#ifndef DT_MIPS_DELTA_INSTANCE_NO
#define DT_MIPS_DELTA_INSTANCE_NO 0x7000001a
#endif
#ifndef DT_MIPS_DELTA_RELOC
#define DT_MIPS_DELTA_RELOC  0x7000001b
#endif
#ifndef DT_MIPS_DELTA_RELOC_NO
#define DT_MIPS_DELTA_RELOC_NO 0x7000001c
#endif
#ifndef DT_MIPS_DELTA_SYM
#define DT_MIPS_DELTA_SYM    0x7000001d
#endif
#ifndef DT_MIPS_DELTA_SYM_NO
#define DT_MIPS_DELTA_SYM_NO 0x7000001e
#endif
#ifndef DT_MIPS_DELTA_CLASSSYM
#define DT_MIPS_DELTA_CLASSSYM 0x70000020
#endif
#ifndef DT_MIPS_DELTA_CLASSSYM_NO
#define DT_MIPS_DELTA_CLASSSYM_NO 0x70000021
#endif
#ifndef DT_MIPS_CXX_FLAGS
#define DT_MIPS_CXX_FLAGS    0x70000022
#endif
#ifndef DT_MIPS_PIXIE_INIT
#define DT_MIPS_PIXIE_INIT   0x70000023
#endif
#ifndef DT_MIPS_SYMBOL_LIB
#define DT_MIPS_SYMBOL_LIB   0x70000024
#endif
#ifndef DT_MIPS_LOCALPAGE_GOTIDX
#define DT_MIPS_LOCALPAGE_GOTIDX 0x70000025
#endif
#ifndef DT_MIPS_LOCAL_GOTIDX
#define DT_MIPS_LOCAL_GOTIDX 0x70000026
#endif
#ifndef DT_MIPS_HIDDEN_GOTIDX
#define DT_MIPS_HIDDEN_GOTIDX 0x70000027
#endif
#ifndef DT_MIPS_PROTECTED_GOTIDX
#define DT_MIPS_PROTECTED_GOTIDX 0x70000028
#endif
#ifndef DT_MIPS_OPTIONS
#define DT_MIPS_OPTIONS	     0x70000029
#endif
#ifndef DT_MIPS_INTERFACE
#define DT_MIPS_INTERFACE    0x7000002a
#endif
#ifndef DT_MIPS_DYNSTR_ALIGN
#define DT_MIPS_DYNSTR_ALIGN 0x7000002b
#endif
#ifndef DT_MIPS_INTERFACE_SIZE
#define DT_MIPS_INTERFACE_SIZE 0x7000002c
#endif
#ifndef DT_MIPS_RLD_TEXT_RESOLVE_ADDR
#define DT_MIPS_RLD_TEXT_RESOLVE_ADDR 0x7000002d
#endif
#ifndef DT_MIPS_PERF_SUFFIX
#define DT_MIPS_PERF_SUFFIX  0x7000002e
#endif
#ifndef DT_MIPS_COMPACT_SIZE
#define DT_MIPS_COMPACT_SIZE 0x7000002f
#endif
#ifndef DT_MIPS_GP_VALUE
#define DT_MIPS_GP_VALUE     0x70000030
#endif
#ifndef DT_MIPS_AUX_DYNAMIC
#define DT_MIPS_AUX_DYNAMIC  0x70000031
#endif
#ifndef DT_MIPS_PLTGOT
#define DT_MIPS_PLTGOT	     0x70000032
#endif
#ifndef DT_MIPS_RWPLT
#define DT_MIPS_RWPLT        0x70000034
#endif
#ifndef DT_MIPS_RLD_MAP_REL
#define DT_MIPS_RLD_MAP_REL  0x70000035
#endif
#ifndef DT_MIPS_NUM
#define DT_MIPS_NUM	     0x36
#endif
#ifndef RHF_NONE
#define RHF_NONE		   0
#endif
#ifndef RHF_QUICKSTART
#define RHF_QUICKSTART		   (1 << 0)
#endif
#ifndef RHF_NOTPOT
#define RHF_NOTPOT		   (1 << 1)
#endif
#ifndef RHF_NO_LIBRARY_REPLACEMENT
#define RHF_NO_LIBRARY_REPLACEMENT (1 << 2)
#endif
#ifndef RHF_NO_MOVE
#define RHF_NO_MOVE		   (1 << 3)
#endif
#ifndef RHF_SGI_ONLY
#define RHF_SGI_ONLY		   (1 << 4)
#endif
#ifndef RHF_GUARANTEE_INIT
#define RHF_GUARANTEE_INIT	   (1 << 5)
#endif
#ifndef RHF_DELTA_C_PLUS_PLUS
#define RHF_DELTA_C_PLUS_PLUS	   (1 << 6)
#endif
#ifndef RHF_GUARANTEE_START_INIT
#define RHF_GUARANTEE_START_INIT   (1 << 7)
#endif
#ifndef RHF_PIXIE
#define RHF_PIXIE		   (1 << 8)
#endif
#ifndef RHF_DEFAULT_DELAY_LOAD
#define RHF_DEFAULT_DELAY_LOAD	   (1 << 9)
#endif
#ifndef RHF_REQUICKSTART
#define RHF_REQUICKSTART	   (1 << 10)
#endif
#ifndef RHF_REQUICKSTARTED
#define RHF_REQUICKSTARTED	   (1 << 11)
#endif
#ifndef RHF_CORD
#define RHF_CORD		   (1 << 12)
#endif
#ifndef RHF_NO_UNRES_UNDEF
#define RHF_NO_UNRES_UNDEF	   (1 << 13)
#endif
#ifndef RHF_RLD_ORDER_SAFE
#define RHF_RLD_ORDER_SAFE	   (1 << 14)
#endif
#ifndef LL_NONE
#define LL_NONE		  0
#endif
#ifndef LL_EXACT_MATCH
#define LL_EXACT_MATCH	  (1 << 0)
#endif
#ifndef LL_IGNORE_INT_VER
#define LL_IGNORE_INT_VER (1 << 1)
#endif
#ifndef LL_REQUIRE_MINOR
#define LL_REQUIRE_MINOR  (1 << 2)
#endif
#ifndef LL_EXPORTS
#define LL_EXPORTS	  (1 << 3)
#endif
#ifndef LL_DELAY_LOAD
#define LL_DELAY_LOAD	  (1 << 4)
#endif
#ifndef LL_DELTA
#define LL_DELTA	  (1 << 5)
#endif
#ifndef MIPS_AFL_REG_NONE
#define MIPS_AFL_REG_NONE	0x00
#endif
#ifndef MIPS_AFL_REG_32
#define MIPS_AFL_REG_32		0x01
#endif
#ifndef MIPS_AFL_REG_64
#define MIPS_AFL_REG_64		0x02
#endif
#ifndef MIPS_AFL_REG_128
#define MIPS_AFL_REG_128	0x03
#endif
#ifndef MIPS_AFL_ASE_DSP
#define MIPS_AFL_ASE_DSP	0x00000001
#endif
#ifndef MIPS_AFL_ASE_DSPR2
#define MIPS_AFL_ASE_DSPR2	0x00000002
#endif
#ifndef MIPS_AFL_ASE_EVA
#define MIPS_AFL_ASE_EVA	0x00000004
#endif
#ifndef MIPS_AFL_ASE_MCU
#define MIPS_AFL_ASE_MCU	0x00000008
#endif
#ifndef MIPS_AFL_ASE_MDMX
#define MIPS_AFL_ASE_MDMX	0x00000010
#endif
#ifndef MIPS_AFL_ASE_MIPS3D
#define MIPS_AFL_ASE_MIPS3D	0x00000020
#endif
#ifndef MIPS_AFL_ASE_MT
#define MIPS_AFL_ASE_MT		0x00000040
#endif
#ifndef MIPS_AFL_ASE_SMARTMIPS
#define MIPS_AFL_ASE_SMARTMIPS	0x00000080
#endif
#ifndef MIPS_AFL_ASE_VIRT
#define MIPS_AFL_ASE_VIRT	0x00000100
#endif
#ifndef MIPS_AFL_ASE_MSA
#define MIPS_AFL_ASE_MSA	0x00000200
#endif
#ifndef MIPS_AFL_ASE_MIPS16
#define MIPS_AFL_ASE_MIPS16	0x00000400
#endif
#ifndef MIPS_AFL_ASE_MICROMIPS
#define MIPS_AFL_ASE_MICROMIPS	0x00000800
#endif
#ifndef MIPS_AFL_ASE_XPA
#define MIPS_AFL_ASE_XPA	0x00001000
#endif
#ifndef MIPS_AFL_ASE_MASK
#define MIPS_AFL_ASE_MASK	0x00001fff
#endif
#ifndef MIPS_AFL_EXT_XLR
#define MIPS_AFL_EXT_XLR	  1
#endif
#ifndef MIPS_AFL_EXT_OCTEON2
#define MIPS_AFL_EXT_OCTEON2	  2
#endif
#ifndef MIPS_AFL_EXT_OCTEONP
#define MIPS_AFL_EXT_OCTEONP	  3
#endif
#ifndef MIPS_AFL_EXT_LOONGSON_3A
#define MIPS_AFL_EXT_LOONGSON_3A  4
#endif
#ifndef MIPS_AFL_EXT_OCTEON
#define MIPS_AFL_EXT_OCTEON	  5
#endif
#ifndef MIPS_AFL_EXT_5900
#define MIPS_AFL_EXT_5900	  6
#endif
#ifndef MIPS_AFL_EXT_4650
#define MIPS_AFL_EXT_4650	  7
#endif
#ifndef MIPS_AFL_EXT_4010
#define MIPS_AFL_EXT_4010	  8
#endif
#ifndef MIPS_AFL_EXT_4100
#define MIPS_AFL_EXT_4100	  9
#endif
#ifndef MIPS_AFL_EXT_3900
#define MIPS_AFL_EXT_3900	  10
#endif
#ifndef MIPS_AFL_EXT_10000
#define MIPS_AFL_EXT_10000	  11
#endif
#ifndef MIPS_AFL_EXT_SB1
#define MIPS_AFL_EXT_SB1	  12
#endif
#ifndef MIPS_AFL_EXT_4111
#define MIPS_AFL_EXT_4111	  13
#endif
#ifndef MIPS_AFL_EXT_4120
#define MIPS_AFL_EXT_4120	  14
#endif
#ifndef MIPS_AFL_EXT_5400
#define MIPS_AFL_EXT_5400	  15
#endif
#ifndef MIPS_AFL_EXT_5500
#define MIPS_AFL_EXT_5500	  16
#endif
#ifndef MIPS_AFL_EXT_LOONGSON_2E
#define MIPS_AFL_EXT_LOONGSON_2E  17
#endif
#ifndef MIPS_AFL_EXT_LOONGSON_2F
#define MIPS_AFL_EXT_LOONGSON_2F  18
#endif
#ifndef MIPS_AFL_FLAGS1_ODDSPREG
#define MIPS_AFL_FLAGS1_ODDSPREG  1
#endif
#ifndef EF_PARISC_TRAPNIL
#define EF_PARISC_TRAPNIL	0x00010000
#endif
#ifndef EF_PARISC_EXT
#define EF_PARISC_EXT		0x00020000
#endif
#ifndef EF_PARISC_LSB
#define EF_PARISC_LSB		0x00040000
#endif
#ifndef EF_PARISC_WIDE
#define EF_PARISC_WIDE		0x00080000
#endif
#ifndef EF_PARISC_NO_KABP
#define EF_PARISC_NO_KABP	0x00100000
#endif
#ifndef EF_PARISC_LAZYSWAP
#define EF_PARISC_LAZYSWAP	0x00400000
#endif
#ifndef EF_PARISC_ARCH
#define EF_PARISC_ARCH		0x0000ffff
#endif
#ifndef EFA_PARISC_1_0
#define EFA_PARISC_1_0		    0x020b
#endif
#ifndef EFA_PARISC_1_1
#define EFA_PARISC_1_1		    0x0210
#endif
#ifndef EFA_PARISC_2_0
#define EFA_PARISC_2_0		    0x0214
#endif
#ifndef SHN_PARISC_ANSI_COMMON
#define SHN_PARISC_ANSI_COMMON	0xff00
#endif
#ifndef SHN_PARISC_HUGE_COMMON
#define SHN_PARISC_HUGE_COMMON	0xff01
#endif
#ifndef SHT_PARISC_EXT
#define SHT_PARISC_EXT		0x70000000
#endif
#ifndef SHT_PARISC_UNWIND
#define SHT_PARISC_UNWIND	0x70000001
#endif
#ifndef SHT_PARISC_DOC
#define SHT_PARISC_DOC		0x70000002
#endif
#ifndef SHF_PARISC_SHORT
#define SHF_PARISC_SHORT	0x20000000
#endif
#ifndef SHF_PARISC_HUGE
#define SHF_PARISC_HUGE		0x40000000
#endif
#ifndef SHF_PARISC_SBP
#define SHF_PARISC_SBP		0x80000000
#endif
#ifndef STT_PARISC_MILLICODE
#define STT_PARISC_MILLICODE	13
#endif
#ifndef STT_HP_OPAQUE
#define STT_HP_OPAQUE		(STT_LOOS + 0x1)
#endif
#ifndef STT_HP_STUB
#define STT_HP_STUB		(STT_LOOS + 0x2)
#endif
#ifndef R_PARISC_NONE
#define R_PARISC_NONE		0
#endif
#ifndef R_PARISC_DIR32
#define R_PARISC_DIR32		1
#endif
#ifndef R_PARISC_DIR21L
#define R_PARISC_DIR21L		2
#endif
#ifndef R_PARISC_DIR17R
#define R_PARISC_DIR17R		3
#endif
#ifndef R_PARISC_DIR17F
#define R_PARISC_DIR17F		4
#endif
#ifndef R_PARISC_DIR14R
#define R_PARISC_DIR14R		6
#endif
#ifndef R_PARISC_PCREL32
#define R_PARISC_PCREL32	9
#endif
#ifndef R_PARISC_PCREL21L
#define R_PARISC_PCREL21L	10
#endif
#ifndef R_PARISC_PCREL17R
#define R_PARISC_PCREL17R	11
#endif
#ifndef R_PARISC_PCREL17F
#define R_PARISC_PCREL17F	12
#endif
#ifndef R_PARISC_PCREL14R
#define R_PARISC_PCREL14R	14
#endif
#ifndef R_PARISC_DPREL21L
#define R_PARISC_DPREL21L	18
#endif
#ifndef R_PARISC_DPREL14R
#define R_PARISC_DPREL14R	22
#endif
#ifndef R_PARISC_GPREL21L
#define R_PARISC_GPREL21L	26
#endif
#ifndef R_PARISC_GPREL14R
#define R_PARISC_GPREL14R	30
#endif
#ifndef R_PARISC_LTOFF21L
#define R_PARISC_LTOFF21L	34
#endif
#ifndef R_PARISC_LTOFF14R
#define R_PARISC_LTOFF14R	38
#endif
#ifndef R_PARISC_SECREL32
#define R_PARISC_SECREL32	41
#endif
#ifndef R_PARISC_SEGBASE
#define R_PARISC_SEGBASE	48
#endif
#ifndef R_PARISC_SEGREL32
#define R_PARISC_SEGREL32	49
#endif
#ifndef R_PARISC_PLTOFF21L
#define R_PARISC_PLTOFF21L	50
#endif
#ifndef R_PARISC_PLTOFF14R
#define R_PARISC_PLTOFF14R	54
#endif
#ifndef R_PARISC_LTOFF_FPTR32
#define R_PARISC_LTOFF_FPTR32	57
#endif
#ifndef R_PARISC_LTOFF_FPTR21L
#define R_PARISC_LTOFF_FPTR21L	58
#endif
#ifndef R_PARISC_LTOFF_FPTR14R
#define R_PARISC_LTOFF_FPTR14R	62
#endif
#ifndef R_PARISC_FPTR64
#define R_PARISC_FPTR64		64
#endif
#ifndef R_PARISC_PLABEL32
#define R_PARISC_PLABEL32	65
#endif
#ifndef R_PARISC_PLABEL21L
#define R_PARISC_PLABEL21L	66
#endif
#ifndef R_PARISC_PLABEL14R
#define R_PARISC_PLABEL14R	70
#endif
#ifndef R_PARISC_PCREL64
#define R_PARISC_PCREL64	72
#endif
#ifndef R_PARISC_PCREL22F
#define R_PARISC_PCREL22F	74
#endif
#ifndef R_PARISC_PCREL14WR
#define R_PARISC_PCREL14WR	75
#endif
#ifndef R_PARISC_PCREL14DR
#define R_PARISC_PCREL14DR	76
#endif
#ifndef R_PARISC_PCREL16F
#define R_PARISC_PCREL16F	77
#endif
#ifndef R_PARISC_PCREL16WF
#define R_PARISC_PCREL16WF	78
#endif
#ifndef R_PARISC_PCREL16DF
#define R_PARISC_PCREL16DF	79
#endif
#ifndef R_PARISC_DIR64
#define R_PARISC_DIR64		80
#endif
#ifndef R_PARISC_DIR14WR
#define R_PARISC_DIR14WR	83
#endif
#ifndef R_PARISC_DIR14DR
#define R_PARISC_DIR14DR	84
#endif
#ifndef R_PARISC_DIR16F
#define R_PARISC_DIR16F		85
#endif
#ifndef R_PARISC_DIR16WF
#define R_PARISC_DIR16WF	86
#endif
#ifndef R_PARISC_DIR16DF
#define R_PARISC_DIR16DF	87
#endif
#ifndef R_PARISC_GPREL64
#define R_PARISC_GPREL64	88
#endif
#ifndef R_PARISC_GPREL14WR
#define R_PARISC_GPREL14WR	91
#endif
#ifndef R_PARISC_GPREL14DR
#define R_PARISC_GPREL14DR	92
#endif
#ifndef R_PARISC_GPREL16F
#define R_PARISC_GPREL16F	93
#endif
#ifndef R_PARISC_GPREL16WF
#define R_PARISC_GPREL16WF	94
#endif
#ifndef R_PARISC_GPREL16DF
#define R_PARISC_GPREL16DF	95
#endif
#ifndef R_PARISC_LTOFF64
#define R_PARISC_LTOFF64	96
#endif
#ifndef R_PARISC_LTOFF14WR
#define R_PARISC_LTOFF14WR	99
#endif
#ifndef R_PARISC_LTOFF14DR
#define R_PARISC_LTOFF14DR	100
#endif
#ifndef R_PARISC_LTOFF16F
#define R_PARISC_LTOFF16F	101
#endif
#ifndef R_PARISC_LTOFF16WF
#define R_PARISC_LTOFF16WF	102
#endif
#ifndef R_PARISC_LTOFF16DF
#define R_PARISC_LTOFF16DF	103
#endif
#ifndef R_PARISC_SECREL64
#define R_PARISC_SECREL64	104
#endif
#ifndef R_PARISC_SEGREL64
#define R_PARISC_SEGREL64	112
#endif
#ifndef R_PARISC_PLTOFF14WR
#define R_PARISC_PLTOFF14WR	115
#endif
#ifndef R_PARISC_PLTOFF14DR
#define R_PARISC_PLTOFF14DR	116
#endif
#ifndef R_PARISC_PLTOFF16F
#define R_PARISC_PLTOFF16F	117
#endif
#ifndef R_PARISC_PLTOFF16WF
#define R_PARISC_PLTOFF16WF	118
#endif
#ifndef R_PARISC_PLTOFF16DF
#define R_PARISC_PLTOFF16DF	119
#endif
#ifndef R_PARISC_LTOFF_FPTR64
#define R_PARISC_LTOFF_FPTR64	120
#endif
#ifndef R_PARISC_LTOFF_FPTR14WR
#define R_PARISC_LTOFF_FPTR14WR	123
#endif
#ifndef R_PARISC_LTOFF_FPTR14DR
#define R_PARISC_LTOFF_FPTR14DR	124
#endif
#ifndef R_PARISC_LTOFF_FPTR16F
#define R_PARISC_LTOFF_FPTR16F	125
#endif
#ifndef R_PARISC_LTOFF_FPTR16WF
#define R_PARISC_LTOFF_FPTR16WF	126
#endif
#ifndef R_PARISC_LTOFF_FPTR16DF
#define R_PARISC_LTOFF_FPTR16DF	127
#endif
#ifndef R_PARISC_LORESERVE
#define R_PARISC_LORESERVE	128
#endif
#ifndef R_PARISC_COPY
#define R_PARISC_COPY		128
#endif
#ifndef R_PARISC_IPLT
#define R_PARISC_IPLT		129
#endif
#ifndef R_PARISC_EPLT
#define R_PARISC_EPLT		130
#endif
#ifndef R_PARISC_TPREL32
#define R_PARISC_TPREL32	153
#endif
#ifndef R_PARISC_TPREL21L
#define R_PARISC_TPREL21L	154
#endif
#ifndef R_PARISC_TPREL14R
#define R_PARISC_TPREL14R	158
#endif
#ifndef R_PARISC_LTOFF_TP21L
#define R_PARISC_LTOFF_TP21L	162
#endif
#ifndef R_PARISC_LTOFF_TP14R
#define R_PARISC_LTOFF_TP14R	166
#endif
#ifndef R_PARISC_LTOFF_TP14F
#define R_PARISC_LTOFF_TP14F	167
#endif
#ifndef R_PARISC_TPREL64
#define R_PARISC_TPREL64	216
#endif
#ifndef R_PARISC_TPREL14WR
#define R_PARISC_TPREL14WR	219
#endif
#ifndef R_PARISC_TPREL14DR
#define R_PARISC_TPREL14DR	220
#endif
#ifndef R_PARISC_TPREL16F
#define R_PARISC_TPREL16F	221
#endif
#ifndef R_PARISC_TPREL16WF
#define R_PARISC_TPREL16WF	222
#endif
#ifndef R_PARISC_TPREL16DF
#define R_PARISC_TPREL16DF	223
#endif
#ifndef R_PARISC_LTOFF_TP64
#define R_PARISC_LTOFF_TP64	224
#endif
#ifndef R_PARISC_LTOFF_TP14WR
#define R_PARISC_LTOFF_TP14WR	227
#endif
#ifndef R_PARISC_LTOFF_TP14DR
#define R_PARISC_LTOFF_TP14DR	228
#endif
#ifndef R_PARISC_LTOFF_TP16F
#define R_PARISC_LTOFF_TP16F	229
#endif
#ifndef R_PARISC_LTOFF_TP16WF
#define R_PARISC_LTOFF_TP16WF	230
#endif
#ifndef R_PARISC_LTOFF_TP16DF
#define R_PARISC_LTOFF_TP16DF	231
#endif
#ifndef R_PARISC_GNU_VTENTRY
#define R_PARISC_GNU_VTENTRY	232
#endif
#ifndef R_PARISC_GNU_VTINHERIT
#define R_PARISC_GNU_VTINHERIT	233
#endif
#ifndef R_PARISC_TLS_GD21L
#define R_PARISC_TLS_GD21L	234
#endif
#ifndef R_PARISC_TLS_GD14R
#define R_PARISC_TLS_GD14R	235
#endif
#ifndef R_PARISC_TLS_GDCALL
#define R_PARISC_TLS_GDCALL	236
#endif
#ifndef R_PARISC_TLS_LDM21L
#define R_PARISC_TLS_LDM21L	237
#endif
#ifndef R_PARISC_TLS_LDM14R
#define R_PARISC_TLS_LDM14R	238
#endif
#ifndef R_PARISC_TLS_LDMCALL
#define R_PARISC_TLS_LDMCALL	239
#endif
#ifndef R_PARISC_TLS_LDO21L
#define R_PARISC_TLS_LDO21L	240
#endif
#ifndef R_PARISC_TLS_LDO14R
#define R_PARISC_TLS_LDO14R	241
#endif
#ifndef R_PARISC_TLS_DTPMOD32
#define R_PARISC_TLS_DTPMOD32	242
#endif
#ifndef R_PARISC_TLS_DTPMOD64
#define R_PARISC_TLS_DTPMOD64	243
#endif
#ifndef R_PARISC_TLS_DTPOFF32
#define R_PARISC_TLS_DTPOFF32	244
#endif
#ifndef R_PARISC_TLS_DTPOFF64
#define R_PARISC_TLS_DTPOFF64	245
#endif
#ifndef R_PARISC_TLS_LE21L
#define R_PARISC_TLS_LE21L	R_PARISC_TPREL21L
#endif
#ifndef R_PARISC_TLS_LE14R
#define R_PARISC_TLS_LE14R	R_PARISC_TPREL14R
#endif
#ifndef R_PARISC_TLS_IE21L
#define R_PARISC_TLS_IE21L	R_PARISC_LTOFF_TP21L
#endif
#ifndef R_PARISC_TLS_IE14R
#define R_PARISC_TLS_IE14R	R_PARISC_LTOFF_TP14R
#endif
#ifndef R_PARISC_TLS_TPREL32
#define R_PARISC_TLS_TPREL32	R_PARISC_TPREL32
#endif
#ifndef R_PARISC_TLS_TPREL64
#define R_PARISC_TLS_TPREL64	R_PARISC_TPREL64
#endif
#ifndef R_PARISC_HIRESERVE
#define R_PARISC_HIRESERVE	255
#endif
#ifndef PT_HP_TLS
#define PT_HP_TLS		(PT_LOOS + 0x0)
#endif
#ifndef PT_HP_CORE_NONE
#define PT_HP_CORE_NONE		(PT_LOOS + 0x1)
#endif
#ifndef PT_HP_CORE_VERSION
#define PT_HP_CORE_VERSION	(PT_LOOS + 0x2)
#endif
#ifndef PT_HP_CORE_KERNEL
#define PT_HP_CORE_KERNEL	(PT_LOOS + 0x3)
#endif
#ifndef PT_HP_CORE_COMM
#define PT_HP_CORE_COMM		(PT_LOOS + 0x4)
#endif
#ifndef PT_HP_CORE_PROC
#define PT_HP_CORE_PROC		(PT_LOOS + 0x5)
#endif
#ifndef PT_HP_CORE_LOADABLE
#define PT_HP_CORE_LOADABLE	(PT_LOOS + 0x6)
#endif
#ifndef PT_HP_CORE_STACK
#define PT_HP_CORE_STACK	(PT_LOOS + 0x7)
#endif
#ifndef PT_HP_CORE_SHM
#define PT_HP_CORE_SHM		(PT_LOOS + 0x8)
#endif
#ifndef PT_HP_CORE_MMF
#define PT_HP_CORE_MMF		(PT_LOOS + 0x9)
#endif
#ifndef PT_HP_PARALLEL
#define PT_HP_PARALLEL		(PT_LOOS + 0x10)
#endif
#ifndef PT_HP_FASTBIND
#define PT_HP_FASTBIND		(PT_LOOS + 0x11)
#endif
#ifndef PT_HP_OPT_ANNOT
#define PT_HP_OPT_ANNOT		(PT_LOOS + 0x12)
#endif
#ifndef PT_HP_HSL_ANNOT
#define PT_HP_HSL_ANNOT		(PT_LOOS + 0x13)
#endif
#ifndef PT_HP_STACK
#define PT_HP_STACK		(PT_LOOS + 0x14)
#endif
#ifndef PT_PARISC_ARCHEXT
#define PT_PARISC_ARCHEXT	0x70000000
#endif
#ifndef PT_PARISC_UNWIND
#define PT_PARISC_UNWIND	0x70000001
#endif
#ifndef PF_PARISC_SBP
#define PF_PARISC_SBP		0x08000000
#endif
#ifndef PF_HP_PAGE_SIZE
#define PF_HP_PAGE_SIZE		0x00100000
#endif
#ifndef PF_HP_FAR_SHARED
#define PF_HP_FAR_SHARED	0x00200000
#endif
#ifndef PF_HP_NEAR_SHARED
#define PF_HP_NEAR_SHARED	0x00400000
#endif
#ifndef PF_HP_CODE
#define PF_HP_CODE		0x01000000
#endif
#ifndef PF_HP_MODIFY
#define PF_HP_MODIFY		0x02000000
#endif
#ifndef PF_HP_LAZYSWAP
#define PF_HP_LAZYSWAP		0x04000000
#endif
#ifndef PF_HP_SBP
#define PF_HP_SBP		0x08000000
#endif
#ifndef EF_ALPHA_32BIT
#define EF_ALPHA_32BIT		1
#endif
#ifndef EF_ALPHA_CANRELAX
#define EF_ALPHA_CANRELAX	2
#endif
#ifndef SHT_ALPHA_DEBUG
#define SHT_ALPHA_DEBUG		0x70000001
#endif
#ifndef SHT_ALPHA_REGINFO
#define SHT_ALPHA_REGINFO	0x70000002
#endif
#ifndef SHF_ALPHA_GPREL
#define SHF_ALPHA_GPREL		0x10000000
#endif
#ifndef STO_ALPHA_NOPV
#define STO_ALPHA_NOPV		0x80
#endif
#ifndef STO_ALPHA_STD_GPLOAD
#define STO_ALPHA_STD_GPLOAD	0x88
#endif
#ifndef R_ALPHA_NONE
#define R_ALPHA_NONE		0
#endif
#ifndef R_ALPHA_REFLONG
#define R_ALPHA_REFLONG		1
#endif
#ifndef R_ALPHA_REFQUAD
#define R_ALPHA_REFQUAD		2
#endif
#ifndef R_ALPHA_GPREL32
#define R_ALPHA_GPREL32		3
#endif
#ifndef R_ALPHA_LITERAL
#define R_ALPHA_LITERAL		4
#endif
#ifndef R_ALPHA_LITUSE
#define R_ALPHA_LITUSE		5
#endif
#ifndef R_ALPHA_GPDISP
#define R_ALPHA_GPDISP		6
#endif
#ifndef R_ALPHA_BRADDR
#define R_ALPHA_BRADDR		7
#endif
#ifndef R_ALPHA_HINT
#define R_ALPHA_HINT		8
#endif
#ifndef R_ALPHA_SREL16
#define R_ALPHA_SREL16		9
#endif
#ifndef R_ALPHA_SREL32
#define R_ALPHA_SREL32		10
#endif
#ifndef R_ALPHA_SREL64
#define R_ALPHA_SREL64		11
#endif
#ifndef R_ALPHA_GPRELHIGH
#define R_ALPHA_GPRELHIGH	17
#endif
#ifndef R_ALPHA_GPRELLOW
#define R_ALPHA_GPRELLOW	18
#endif
#ifndef R_ALPHA_GPREL16
#define R_ALPHA_GPREL16		19
#endif
#ifndef R_ALPHA_COPY
#define R_ALPHA_COPY		24
#endif
#ifndef R_ALPHA_GLOB_DAT
#define R_ALPHA_GLOB_DAT	25
#endif
#ifndef R_ALPHA_JMP_SLOT
#define R_ALPHA_JMP_SLOT	26
#endif
#ifndef R_ALPHA_RELATIVE
#define R_ALPHA_RELATIVE	27
#endif
#ifndef R_ALPHA_TLS_GD_HI
#define R_ALPHA_TLS_GD_HI	28
#endif
#ifndef R_ALPHA_TLSGD
#define R_ALPHA_TLSGD		29
#endif
#ifndef R_ALPHA_TLS_LDM
#define R_ALPHA_TLS_LDM		30
#endif
#ifndef R_ALPHA_DTPMOD64
#define R_ALPHA_DTPMOD64	31
#endif
#ifndef R_ALPHA_GOTDTPREL
#define R_ALPHA_GOTDTPREL	32
#endif
#ifndef R_ALPHA_DTPREL64
#define R_ALPHA_DTPREL64	33
#endif
#ifndef R_ALPHA_DTPRELHI
#define R_ALPHA_DTPRELHI	34
#endif
#ifndef R_ALPHA_DTPRELLO
#define R_ALPHA_DTPRELLO	35
#endif
#ifndef R_ALPHA_DTPREL16
#define R_ALPHA_DTPREL16	36
#endif
#ifndef R_ALPHA_GOTTPREL
#define R_ALPHA_GOTTPREL	37
#endif
#ifndef R_ALPHA_TPREL64
#define R_ALPHA_TPREL64		38
#endif
#ifndef R_ALPHA_TPRELHI
#define R_ALPHA_TPRELHI		39
#endif
#ifndef R_ALPHA_TPRELLO
#define R_ALPHA_TPRELLO		40
#endif
#ifndef R_ALPHA_TPREL16
#define R_ALPHA_TPREL16		41
#endif
#ifndef R_ALPHA_NUM
#define R_ALPHA_NUM		46
#endif
#ifndef LITUSE_ALPHA_ADDR
#define LITUSE_ALPHA_ADDR	0
#endif
#ifndef LITUSE_ALPHA_BASE
#define LITUSE_ALPHA_BASE	1
#endif
#ifndef LITUSE_ALPHA_BYTOFF
#define LITUSE_ALPHA_BYTOFF	2
#endif
#ifndef LITUSE_ALPHA_JSR
#define LITUSE_ALPHA_JSR	3
#endif
#ifndef LITUSE_ALPHA_TLS_GD
#define LITUSE_ALPHA_TLS_GD	4
#endif
#ifndef LITUSE_ALPHA_TLS_LDM
#define LITUSE_ALPHA_TLS_LDM	5
#endif
#ifndef DT_ALPHA_PLTRO
#define DT_ALPHA_PLTRO		(DT_LOPROC + 0)
#endif
#ifndef DT_ALPHA_NUM
#define DT_ALPHA_NUM		1
#endif
#ifndef EF_PPC_EMB
#define EF_PPC_EMB		0x80000000
#endif
#ifndef EF_PPC_RELOCATABLE
#define EF_PPC_RELOCATABLE	0x00010000
#endif
#ifndef EF_PPC_RELOCATABLE_LIB
#define EF_PPC_RELOCATABLE_LIB	0x00008000
#endif
#ifndef R_PPC_NONE
#define R_PPC_NONE		0
#endif
#ifndef R_PPC_ADDR32
#define R_PPC_ADDR32		1
#endif
#ifndef R_PPC_ADDR24
#define R_PPC_ADDR24		2
#endif
#ifndef R_PPC_ADDR16
#define R_PPC_ADDR16		3
#endif
#ifndef R_PPC_ADDR16_LO
#define R_PPC_ADDR16_LO		4
#endif
#ifndef R_PPC_ADDR16_HI
#define R_PPC_ADDR16_HI		5
#endif
#ifndef R_PPC_ADDR16_HA
#define R_PPC_ADDR16_HA		6
#endif
#ifndef R_PPC_ADDR14
#define R_PPC_ADDR14		7
#endif
#ifndef R_PPC_ADDR14_BRTAKEN
#define R_PPC_ADDR14_BRTAKEN	8
#endif
#ifndef R_PPC_ADDR14_BRNTAKEN
#define R_PPC_ADDR14_BRNTAKEN	9
#endif
#ifndef R_PPC_REL24
#define R_PPC_REL24		10
#endif
#ifndef R_PPC_REL14
#define R_PPC_REL14		11
#endif
#ifndef R_PPC_REL14_BRTAKEN
#define R_PPC_REL14_BRTAKEN	12
#endif
#ifndef R_PPC_REL14_BRNTAKEN
#define R_PPC_REL14_BRNTAKEN	13
#endif
#ifndef R_PPC_GOT16
#define R_PPC_GOT16		14
#endif
#ifndef R_PPC_GOT16_LO
#define R_PPC_GOT16_LO		15
#endif
#ifndef R_PPC_GOT16_HI
#define R_PPC_GOT16_HI		16
#endif
#ifndef R_PPC_GOT16_HA
#define R_PPC_GOT16_HA		17
#endif
#ifndef R_PPC_PLTREL24
#define R_PPC_PLTREL24		18
#endif
#ifndef R_PPC_COPY
#define R_PPC_COPY		19
#endif
#ifndef R_PPC_GLOB_DAT
#define R_PPC_GLOB_DAT		20
#endif
#ifndef R_PPC_JMP_SLOT
#define R_PPC_JMP_SLOT		21
#endif
#ifndef R_PPC_RELATIVE
#define R_PPC_RELATIVE		22
#endif
#ifndef R_PPC_LOCAL24PC
#define R_PPC_LOCAL24PC		23
#endif
#ifndef R_PPC_UADDR32
#define R_PPC_UADDR32		24
#endif
#ifndef R_PPC_UADDR16
#define R_PPC_UADDR16		25
#endif
#ifndef R_PPC_REL32
#define R_PPC_REL32		26
#endif
#ifndef R_PPC_PLT32
#define R_PPC_PLT32		27
#endif
#ifndef R_PPC_PLTREL32
#define R_PPC_PLTREL32		28
#endif
#ifndef R_PPC_PLT16_LO
#define R_PPC_PLT16_LO		29
#endif
#ifndef R_PPC_PLT16_HI
#define R_PPC_PLT16_HI		30
#endif
#ifndef R_PPC_PLT16_HA
#define R_PPC_PLT16_HA		31
#endif
#ifndef R_PPC_SDAREL16
#define R_PPC_SDAREL16		32
#endif
#ifndef R_PPC_SECTOFF
#define R_PPC_SECTOFF		33
#endif
#ifndef R_PPC_SECTOFF_LO
#define R_PPC_SECTOFF_LO	34
#endif
#ifndef R_PPC_SECTOFF_HI
#define R_PPC_SECTOFF_HI	35
#endif
#ifndef R_PPC_SECTOFF_HA
#define R_PPC_SECTOFF_HA	36
#endif
#ifndef R_PPC_TLS
#define R_PPC_TLS		67
#endif
#ifndef R_PPC_DTPMOD32
#define R_PPC_DTPMOD32		68
#endif
#ifndef R_PPC_TPREL16
#define R_PPC_TPREL16		69
#endif
#ifndef R_PPC_TPREL16_LO
#define R_PPC_TPREL16_LO	70
#endif
#ifndef R_PPC_TPREL16_HI
#define R_PPC_TPREL16_HI	71
#endif
#ifndef R_PPC_TPREL16_HA
#define R_PPC_TPREL16_HA	72
#endif
#ifndef R_PPC_TPREL32
#define R_PPC_TPREL32		73
#endif
#ifndef R_PPC_DTPREL16
#define R_PPC_DTPREL16		74
#endif
#ifndef R_PPC_DTPREL16_LO
#define R_PPC_DTPREL16_LO	75
#endif
#ifndef R_PPC_DTPREL16_HI
#define R_PPC_DTPREL16_HI	76
#endif
#ifndef R_PPC_DTPREL16_HA
#define R_PPC_DTPREL16_HA	77
#endif
#ifndef R_PPC_DTPREL32
#define R_PPC_DTPREL32		78
#endif
#ifndef R_PPC_GOT_TLSGD16
#define R_PPC_GOT_TLSGD16	79
#endif
#ifndef R_PPC_GOT_TLSGD16_LO
#define R_PPC_GOT_TLSGD16_LO	80
#endif
#ifndef R_PPC_GOT_TLSGD16_HI
#define R_PPC_GOT_TLSGD16_HI	81
#endif
#ifndef R_PPC_GOT_TLSGD16_HA
#define R_PPC_GOT_TLSGD16_HA	82
#endif
#ifndef R_PPC_GOT_TLSLD16
#define R_PPC_GOT_TLSLD16	83
#endif
#ifndef R_PPC_GOT_TLSLD16_LO
#define R_PPC_GOT_TLSLD16_LO	84
#endif
#ifndef R_PPC_GOT_TLSLD16_HI
#define R_PPC_GOT_TLSLD16_HI	85
#endif
#ifndef R_PPC_GOT_TLSLD16_HA
#define R_PPC_GOT_TLSLD16_HA	86
#endif
#ifndef R_PPC_GOT_TPREL16
#define R_PPC_GOT_TPREL16	87
#endif
#ifndef R_PPC_GOT_TPREL16_LO
#define R_PPC_GOT_TPREL16_LO	88
#endif
#ifndef R_PPC_GOT_TPREL16_HI
#define R_PPC_GOT_TPREL16_HI	89
#endif
#ifndef R_PPC_GOT_TPREL16_HA
#define R_PPC_GOT_TPREL16_HA	90
#endif
#ifndef R_PPC_GOT_DTPREL16
#define R_PPC_GOT_DTPREL16	91
#endif
#ifndef R_PPC_GOT_DTPREL16_LO
#define R_PPC_GOT_DTPREL16_LO	92
#endif
#ifndef R_PPC_GOT_DTPREL16_HI
#define R_PPC_GOT_DTPREL16_HI	93
#endif
#ifndef R_PPC_GOT_DTPREL16_HA
#define R_PPC_GOT_DTPREL16_HA	94
#endif
#ifndef R_PPC_TLSGD
#define R_PPC_TLSGD		95
#endif
#ifndef R_PPC_TLSLD
#define R_PPC_TLSLD		96
#endif
#ifndef R_PPC_EMB_NADDR32
#define R_PPC_EMB_NADDR32	101
#endif
#ifndef R_PPC_EMB_NADDR16
#define R_PPC_EMB_NADDR16	102
#endif
#ifndef R_PPC_EMB_NADDR16_LO
#define R_PPC_EMB_NADDR16_LO	103
#endif
#ifndef R_PPC_EMB_NADDR16_HI
#define R_PPC_EMB_NADDR16_HI	104
#endif
#ifndef R_PPC_EMB_NADDR16_HA
#define R_PPC_EMB_NADDR16_HA	105
#endif
#ifndef R_PPC_EMB_SDAI16
#define R_PPC_EMB_SDAI16	106
#endif
#ifndef R_PPC_EMB_SDA2I16
#define R_PPC_EMB_SDA2I16	107
#endif
#ifndef R_PPC_EMB_SDA2REL
#define R_PPC_EMB_SDA2REL	108
#endif
#ifndef R_PPC_EMB_SDA21
#define R_PPC_EMB_SDA21		109
#endif
#ifndef R_PPC_EMB_MRKREF
#define R_PPC_EMB_MRKREF	110
#endif
#ifndef R_PPC_EMB_RELSEC16
#define R_PPC_EMB_RELSEC16	111
#endif
#ifndef R_PPC_EMB_RELST_LO
#define R_PPC_EMB_RELST_LO	112
#endif
#ifndef R_PPC_EMB_RELST_HI
#define R_PPC_EMB_RELST_HI	113
#endif
#ifndef R_PPC_EMB_RELST_HA
#define R_PPC_EMB_RELST_HA	114
#endif
#ifndef R_PPC_EMB_BIT_FLD
#define R_PPC_EMB_BIT_FLD	115
#endif
#ifndef R_PPC_EMB_RELSDA
#define R_PPC_EMB_RELSDA	116
#endif
#ifndef R_PPC_DIAB_SDA21_LO
#define R_PPC_DIAB_SDA21_LO	180
#endif
#ifndef R_PPC_DIAB_SDA21_HI
#define R_PPC_DIAB_SDA21_HI	181
#endif
#ifndef R_PPC_DIAB_SDA21_HA
#define R_PPC_DIAB_SDA21_HA	182
#endif
#ifndef R_PPC_DIAB_RELSDA_LO
#define R_PPC_DIAB_RELSDA_LO	183
#endif
#ifndef R_PPC_DIAB_RELSDA_HI
#define R_PPC_DIAB_RELSDA_HI	184
#endif
#ifndef R_PPC_DIAB_RELSDA_HA
#define R_PPC_DIAB_RELSDA_HA	185
#endif
#ifndef R_PPC_IRELATIVE
#define R_PPC_IRELATIVE		248
#endif
#ifndef R_PPC_REL16
#define R_PPC_REL16		249
#endif
#ifndef R_PPC_REL16_LO
#define R_PPC_REL16_LO		250
#endif
#ifndef R_PPC_REL16_HI
#define R_PPC_REL16_HI		251
#endif
#ifndef R_PPC_REL16_HA
#define R_PPC_REL16_HA		252
#endif
#ifndef R_PPC_TOC16
#define R_PPC_TOC16		255
#endif
#ifndef DT_PPC_GOT
#define DT_PPC_GOT		(DT_LOPROC + 0)
#endif
#ifndef DT_PPC_OPT
#define DT_PPC_OPT		(DT_LOPROC + 1)
#endif
#ifndef DT_PPC_NUM
#define DT_PPC_NUM		2
#endif
#ifndef PPC_OPT_TLS
#define PPC_OPT_TLS		1
#endif
#ifndef R_PPC64_NONE
#define R_PPC64_NONE		R_PPC_NONE
#endif
#ifndef R_PPC64_ADDR32
#define R_PPC64_ADDR32		R_PPC_ADDR32
#endif
#ifndef R_PPC64_ADDR24
#define R_PPC64_ADDR24		R_PPC_ADDR24
#endif
#ifndef R_PPC64_ADDR16
#define R_PPC64_ADDR16		R_PPC_ADDR16
#endif
#ifndef R_PPC64_ADDR16_LO
#define R_PPC64_ADDR16_LO	R_PPC_ADDR16_LO
#endif
#ifndef R_PPC64_ADDR16_HI
#define R_PPC64_ADDR16_HI	R_PPC_ADDR16_HI
#endif
#ifndef R_PPC64_ADDR16_HA
#define R_PPC64_ADDR16_HA	R_PPC_ADDR16_HA
#endif
#ifndef R_PPC64_ADDR14
#define R_PPC64_ADDR14		R_PPC_ADDR14
#endif
#ifndef R_PPC64_ADDR14_BRTAKEN
#define R_PPC64_ADDR14_BRTAKEN	R_PPC_ADDR14_BRTAKEN
#endif
#ifndef R_PPC64_ADDR14_BRNTAKEN
#define R_PPC64_ADDR14_BRNTAKEN	R_PPC_ADDR14_BRNTAKEN
#endif
#ifndef R_PPC64_REL24
#define R_PPC64_REL24		R_PPC_REL24
#endif
#ifndef R_PPC64_REL14
#define R_PPC64_REL14		R_PPC_REL14
#endif
#ifndef R_PPC64_REL14_BRTAKEN
#define R_PPC64_REL14_BRTAKEN	R_PPC_REL14_BRTAKEN
#endif
#ifndef R_PPC64_REL14_BRNTAKEN
#define R_PPC64_REL14_BRNTAKEN	R_PPC_REL14_BRNTAKEN
#endif
#ifndef R_PPC64_GOT16
#define R_PPC64_GOT16		R_PPC_GOT16
#endif
#ifndef R_PPC64_GOT16_LO
#define R_PPC64_GOT16_LO	R_PPC_GOT16_LO
#endif
#ifndef R_PPC64_GOT16_HI
#define R_PPC64_GOT16_HI	R_PPC_GOT16_HI
#endif
#ifndef R_PPC64_GOT16_HA
#define R_PPC64_GOT16_HA	R_PPC_GOT16_HA
#endif
#ifndef R_PPC64_COPY
#define R_PPC64_COPY		R_PPC_COPY
#endif
#ifndef R_PPC64_GLOB_DAT
#define R_PPC64_GLOB_DAT	R_PPC_GLOB_DAT
#endif
#ifndef R_PPC64_JMP_SLOT
#define R_PPC64_JMP_SLOT	R_PPC_JMP_SLOT
#endif
#ifndef R_PPC64_RELATIVE
#define R_PPC64_RELATIVE	R_PPC_RELATIVE
#endif
#ifndef R_PPC64_UADDR32
#define R_PPC64_UADDR32		R_PPC_UADDR32
#endif
#ifndef R_PPC64_UADDR16
#define R_PPC64_UADDR16		R_PPC_UADDR16
#endif
#ifndef R_PPC64_REL32
#define R_PPC64_REL32		R_PPC_REL32
#endif
#ifndef R_PPC64_PLT32
#define R_PPC64_PLT32		R_PPC_PLT32
#endif
#ifndef R_PPC64_PLTREL32
#define R_PPC64_PLTREL32	R_PPC_PLTREL32
#endif
#ifndef R_PPC64_PLT16_LO
#define R_PPC64_PLT16_LO	R_PPC_PLT16_LO
#endif
#ifndef R_PPC64_PLT16_HI
#define R_PPC64_PLT16_HI	R_PPC_PLT16_HI
#endif
#ifndef R_PPC64_PLT16_HA
#define R_PPC64_PLT16_HA	R_PPC_PLT16_HA
#endif
#ifndef R_PPC64_SECTOFF
#define R_PPC64_SECTOFF		R_PPC_SECTOFF
#endif
#ifndef R_PPC64_SECTOFF_LO
#define R_PPC64_SECTOFF_LO	R_PPC_SECTOFF_LO
#endif
#ifndef R_PPC64_SECTOFF_HI
#define R_PPC64_SECTOFF_HI	R_PPC_SECTOFF_HI
#endif
#ifndef R_PPC64_SECTOFF_HA
#define R_PPC64_SECTOFF_HA	R_PPC_SECTOFF_HA
#endif
#ifndef R_PPC64_ADDR30
#define R_PPC64_ADDR30		37
#endif
#ifndef R_PPC64_ADDR64
#define R_PPC64_ADDR64		38
#endif
#ifndef R_PPC64_ADDR16_HIGHER
#define R_PPC64_ADDR16_HIGHER	39
#endif
#ifndef R_PPC64_ADDR16_HIGHERA
#define R_PPC64_ADDR16_HIGHERA	40
#endif
#ifndef R_PPC64_ADDR16_HIGHEST
#define R_PPC64_ADDR16_HIGHEST	41
#endif
#ifndef R_PPC64_ADDR16_HIGHESTA
#define R_PPC64_ADDR16_HIGHESTA	42
#endif
#ifndef R_PPC64_UADDR64
#define R_PPC64_UADDR64		43
#endif
#ifndef R_PPC64_REL64
#define R_PPC64_REL64		44
#endif
#ifndef R_PPC64_PLT64
#define R_PPC64_PLT64		45
#endif
#ifndef R_PPC64_PLTREL64
#define R_PPC64_PLTREL64	46
#endif
#ifndef R_PPC64_TOC16
#define R_PPC64_TOC16		47
#endif
#ifndef R_PPC64_TOC16_LO
#define R_PPC64_TOC16_LO	48
#endif
#ifndef R_PPC64_TOC16_HI
#define R_PPC64_TOC16_HI	49
#endif
#ifndef R_PPC64_TOC16_HA
#define R_PPC64_TOC16_HA	50
#endif
#ifndef R_PPC64_TOC
#define R_PPC64_TOC		51
#endif
#ifndef R_PPC64_PLTGOT16
#define R_PPC64_PLTGOT16	52
#endif
#ifndef R_PPC64_PLTGOT16_LO
#define R_PPC64_PLTGOT16_LO	53
#endif
#ifndef R_PPC64_PLTGOT16_HI
#define R_PPC64_PLTGOT16_HI	54
#endif
#ifndef R_PPC64_PLTGOT16_HA
#define R_PPC64_PLTGOT16_HA	55
#endif
#ifndef R_PPC64_ADDR16_DS
#define R_PPC64_ADDR16_DS	56
#endif
#ifndef R_PPC64_ADDR16_LO_DS
#define R_PPC64_ADDR16_LO_DS	57
#endif
#ifndef R_PPC64_GOT16_DS
#define R_PPC64_GOT16_DS	58
#endif
#ifndef R_PPC64_GOT16_LO_DS
#define R_PPC64_GOT16_LO_DS	59
#endif
#ifndef R_PPC64_PLT16_LO_DS
#define R_PPC64_PLT16_LO_DS	60
#endif
#ifndef R_PPC64_SECTOFF_DS
#define R_PPC64_SECTOFF_DS	61
#endif
#ifndef R_PPC64_SECTOFF_LO_DS
#define R_PPC64_SECTOFF_LO_DS	62
#endif
#ifndef R_PPC64_TOC16_DS
#define R_PPC64_TOC16_DS	63
#endif
#ifndef R_PPC64_TOC16_LO_DS
#define R_PPC64_TOC16_LO_DS	64
#endif
#ifndef R_PPC64_PLTGOT16_DS
#define R_PPC64_PLTGOT16_DS	65
#endif
#ifndef R_PPC64_PLTGOT16_LO_DS
#define R_PPC64_PLTGOT16_LO_DS	66
#endif
#ifndef R_PPC64_TLS
#define R_PPC64_TLS		67
#endif
#ifndef R_PPC64_DTPMOD64
#define R_PPC64_DTPMOD64	68
#endif
#ifndef R_PPC64_TPREL16
#define R_PPC64_TPREL16		69
#endif
#ifndef R_PPC64_TPREL16_LO
#define R_PPC64_TPREL16_LO	70
#endif
#ifndef R_PPC64_TPREL16_HI
#define R_PPC64_TPREL16_HI	71
#endif
#ifndef R_PPC64_TPREL16_HA
#define R_PPC64_TPREL16_HA	72
#endif
#ifndef R_PPC64_TPREL64
#define R_PPC64_TPREL64		73
#endif
#ifndef R_PPC64_DTPREL16
#define R_PPC64_DTPREL16	74
#endif
#ifndef R_PPC64_DTPREL16_LO
#define R_PPC64_DTPREL16_LO	75
#endif
#ifndef R_PPC64_DTPREL16_HI
#define R_PPC64_DTPREL16_HI	76
#endif
#ifndef R_PPC64_DTPREL16_HA
#define R_PPC64_DTPREL16_HA	77
#endif
#ifndef R_PPC64_DTPREL64
#define R_PPC64_DTPREL64	78
#endif
#ifndef R_PPC64_GOT_TLSGD16
#define R_PPC64_GOT_TLSGD16	79
#endif
#ifndef R_PPC64_GOT_TLSGD16_LO
#define R_PPC64_GOT_TLSGD16_LO	80
#endif
#ifndef R_PPC64_GOT_TLSGD16_HI
#define R_PPC64_GOT_TLSGD16_HI	81
#endif
#ifndef R_PPC64_GOT_TLSGD16_HA
#define R_PPC64_GOT_TLSGD16_HA	82
#endif
#ifndef R_PPC64_GOT_TLSLD16
#define R_PPC64_GOT_TLSLD16	83
#endif
#ifndef R_PPC64_GOT_TLSLD16_LO
#define R_PPC64_GOT_TLSLD16_LO	84
#endif
#ifndef R_PPC64_GOT_TLSLD16_HI
#define R_PPC64_GOT_TLSLD16_HI	85
#endif
#ifndef R_PPC64_GOT_TLSLD16_HA
#define R_PPC64_GOT_TLSLD16_HA	86
#endif
#ifndef R_PPC64_GOT_TPREL16_DS
#define R_PPC64_GOT_TPREL16_DS	87
#endif
#ifndef R_PPC64_GOT_TPREL16_LO_DS
#define R_PPC64_GOT_TPREL16_LO_DS 88
#endif
#ifndef R_PPC64_GOT_TPREL16_HI
#define R_PPC64_GOT_TPREL16_HI	89
#endif
#ifndef R_PPC64_GOT_TPREL16_HA
#define R_PPC64_GOT_TPREL16_HA	90
#endif
#ifndef R_PPC64_GOT_DTPREL16_DS
#define R_PPC64_GOT_DTPREL16_DS	91
#endif
#ifndef R_PPC64_GOT_DTPREL16_LO_DS
#define R_PPC64_GOT_DTPREL16_LO_DS 92
#endif
#ifndef R_PPC64_GOT_DTPREL16_HI
#define R_PPC64_GOT_DTPREL16_HI	93
#endif
#ifndef R_PPC64_GOT_DTPREL16_HA
#define R_PPC64_GOT_DTPREL16_HA	94
#endif
#ifndef R_PPC64_TPREL16_DS
#define R_PPC64_TPREL16_DS	95
#endif
#ifndef R_PPC64_TPREL16_LO_DS
#define R_PPC64_TPREL16_LO_DS	96
#endif
#ifndef R_PPC64_TPREL16_HIGHER
#define R_PPC64_TPREL16_HIGHER	97
#endif
#ifndef R_PPC64_TPREL16_HIGHERA
#define R_PPC64_TPREL16_HIGHERA	98
#endif
#ifndef R_PPC64_TPREL16_HIGHEST
#define R_PPC64_TPREL16_HIGHEST	99
#endif
#ifndef R_PPC64_TPREL16_HIGHESTA
#define R_PPC64_TPREL16_HIGHESTA 100
#endif
#ifndef R_PPC64_DTPREL16_DS
#define R_PPC64_DTPREL16_DS	101
#endif
#ifndef R_PPC64_DTPREL16_LO_DS
#define R_PPC64_DTPREL16_LO_DS	102
#endif
#ifndef R_PPC64_DTPREL16_HIGHER
#define R_PPC64_DTPREL16_HIGHER	103
#endif
#ifndef R_PPC64_DTPREL16_HIGHERA
#define R_PPC64_DTPREL16_HIGHERA 104
#endif
#ifndef R_PPC64_DTPREL16_HIGHEST
#define R_PPC64_DTPREL16_HIGHEST 105
#endif
#ifndef R_PPC64_DTPREL16_HIGHESTA
#define R_PPC64_DTPREL16_HIGHESTA 106
#endif
#ifndef R_PPC64_TLSGD
#define R_PPC64_TLSGD		107
#endif
#ifndef R_PPC64_TLSLD
#define R_PPC64_TLSLD		108
#endif
#ifndef R_PPC64_TOCSAVE
#define R_PPC64_TOCSAVE		109
#endif
#ifndef R_PPC64_ADDR16_HIGH
#define R_PPC64_ADDR16_HIGH	110
#endif
#ifndef R_PPC64_ADDR16_HIGHA
#define R_PPC64_ADDR16_HIGHA	111
#endif
#ifndef R_PPC64_TPREL16_HIGH
#define R_PPC64_TPREL16_HIGH	112
#endif
#ifndef R_PPC64_TPREL16_HIGHA
#define R_PPC64_TPREL16_HIGHA	113
#endif
#ifndef R_PPC64_DTPREL16_HIGH
#define R_PPC64_DTPREL16_HIGH	114
#endif
#ifndef R_PPC64_DTPREL16_HIGHA
#define R_PPC64_DTPREL16_HIGHA	115
#endif
#ifndef R_PPC64_JMP_IREL
#define R_PPC64_JMP_IREL	247
#endif
#ifndef R_PPC64_IRELATIVE
#define R_PPC64_IRELATIVE	248
#endif
#ifndef R_PPC64_REL16
#define R_PPC64_REL16		249
#endif
#ifndef R_PPC64_REL16_LO
#define R_PPC64_REL16_LO	250
#endif
#ifndef R_PPC64_REL16_HI
#define R_PPC64_REL16_HI	251
#endif
#ifndef R_PPC64_REL16_HA
#define R_PPC64_REL16_HA	252
#endif
#ifndef EF_PPC64_ABI
#define EF_PPC64_ABI	3
#endif
#ifndef DT_PPC64_GLINK
#define DT_PPC64_GLINK  (DT_LOPROC + 0)
#endif
#ifndef DT_PPC64_OPD
#define DT_PPC64_OPD	(DT_LOPROC + 1)
#endif
#ifndef DT_PPC64_OPDSZ
#define DT_PPC64_OPDSZ	(DT_LOPROC + 2)
#endif
#ifndef DT_PPC64_OPT
#define DT_PPC64_OPT	(DT_LOPROC + 3)
#endif
#ifndef DT_PPC64_NUM
#define DT_PPC64_NUM	4
#endif
#ifndef PPC64_OPT_TLS
#define PPC64_OPT_TLS		1
#endif
#ifndef PPC64_OPT_MULTI_TOC
#define PPC64_OPT_MULTI_TOC	2
#endif
#ifndef PPC64_OPT_LOCALENTRY
#define PPC64_OPT_LOCALENTRY	4
#endif
#ifndef STO_PPC64_LOCAL_BIT
#define STO_PPC64_LOCAL_BIT	5
#endif
#ifndef STO_PPC64_LOCAL_MASK
#define STO_PPC64_LOCAL_MASK	0xe0
#endif
#ifndef PPC64_LOCAL_ENTRY_OFFSET
#define PPC64_LOCAL_ENTRY_OFFSET(x) (1 << (((x)&0xe0)>>5) & 0xfc)
#endif
#ifndef EF_ARM_RELEXEC
#define EF_ARM_RELEXEC		0x01
#endif
#ifndef EF_ARM_HASENTRY
#define EF_ARM_HASENTRY		0x02
#endif
#ifndef EF_ARM_INTERWORK
#define EF_ARM_INTERWORK	0x04
#endif
#ifndef EF_ARM_APCS_26
#define EF_ARM_APCS_26		0x08
#endif
#ifndef EF_ARM_APCS_FLOAT
#define EF_ARM_APCS_FLOAT	0x10
#endif
#ifndef EF_ARM_PIC
#define EF_ARM_PIC		0x20
#endif
#ifndef EF_ARM_ALIGN8
#define EF_ARM_ALIGN8		0x40
#endif
#ifndef EF_ARM_NEW_ABI
#define EF_ARM_NEW_ABI		0x80
#endif
#ifndef EF_ARM_OLD_ABI
#define EF_ARM_OLD_ABI		0x100
#endif
#ifndef EF_ARM_SOFT_FLOAT
#define EF_ARM_SOFT_FLOAT	0x200
#endif
#ifndef EF_ARM_VFP_FLOAT
#define EF_ARM_VFP_FLOAT	0x400
#endif
#ifndef EF_ARM_MAVERICK_FLOAT
#define EF_ARM_MAVERICK_FLOAT	0x800
#endif
#ifndef EF_ARM_ABI_FLOAT_SOFT
#define EF_ARM_ABI_FLOAT_SOFT	0x200
#endif
#ifndef EF_ARM_ABI_FLOAT_HARD
#define EF_ARM_ABI_FLOAT_HARD	0x400
#endif
#ifndef EF_ARM_SYMSARESORTED
#define EF_ARM_SYMSARESORTED	0x04
#endif
#ifndef EF_ARM_DYNSYMSUSESEGIDX
#define EF_ARM_DYNSYMSUSESEGIDX	0x08
#endif
#ifndef EF_ARM_MAPSYMSFIRST
#define EF_ARM_MAPSYMSFIRST	0x10
#endif
#ifndef EF_ARM_EABIMASK
#define EF_ARM_EABIMASK		0XFF000000
#endif
#ifndef EF_ARM_BE8
#define EF_ARM_BE8	    0x00800000
#endif
#ifndef EF_ARM_LE8
#define EF_ARM_LE8	    0x00400000
#endif
#ifndef EF_ARM_EABI_VERSION
#define EF_ARM_EABI_VERSION(flags)	((flags) & EF_ARM_EABIMASK)
#endif
#ifndef EF_ARM_EABI_UNKNOWN
#define EF_ARM_EABI_UNKNOWN	0x00000000
#endif
#ifndef EF_ARM_EABI_VER1
#define EF_ARM_EABI_VER1	0x01000000
#endif
#ifndef EF_ARM_EABI_VER2
#define EF_ARM_EABI_VER2	0x02000000
#endif
#ifndef EF_ARM_EABI_VER3
#define EF_ARM_EABI_VER3	0x03000000
#endif
#ifndef EF_ARM_EABI_VER4
#define EF_ARM_EABI_VER4	0x04000000
#endif
#ifndef EF_ARM_EABI_VER5
#define EF_ARM_EABI_VER5	0x05000000
#endif
#ifndef STT_ARM_TFUNC
#define STT_ARM_TFUNC		STT_LOPROC
#endif
#ifndef STT_ARM_16BIT
#define STT_ARM_16BIT		STT_HIPROC
#endif
#ifndef SHF_ARM_ENTRYSECT
#define SHF_ARM_ENTRYSECT	0x10000000
#endif
#ifndef SHF_ARM_COMDEF
#define SHF_ARM_COMDEF		0x80000000
#endif
#ifndef PF_ARM_SB
#define PF_ARM_SB		0x10000000
#endif
#ifndef PF_ARM_PI
#define PF_ARM_PI		0x20000000
#endif
#ifndef PF_ARM_ABS
#define PF_ARM_ABS		0x40000000
#endif
#ifndef PT_ARM_EXIDX
#define PT_ARM_EXIDX		(PT_LOPROC + 1)
#endif
#ifndef SHT_ARM_EXIDX
#define SHT_ARM_EXIDX		(SHT_LOPROC + 1)
#endif
#ifndef SHT_ARM_PREEMPTMAP
#define SHT_ARM_PREEMPTMAP	(SHT_LOPROC + 2)
#endif
#ifndef SHT_ARM_ATTRIBUTES
#define SHT_ARM_ATTRIBUTES	(SHT_LOPROC + 3)
#endif
#ifndef R_AARCH64_NONE
#define R_AARCH64_NONE            0
#endif
#ifndef R_AARCH64_P32_ABS32
#define R_AARCH64_P32_ABS32	1
#endif
#ifndef R_AARCH64_P32_COPY
#define R_AARCH64_P32_COPY	180
#endif
#ifndef R_AARCH64_P32_GLOB_DAT
#define R_AARCH64_P32_GLOB_DAT	181
#endif
#ifndef R_AARCH64_P32_JUMP_SLOT
#define R_AARCH64_P32_JUMP_SLOT	182
#endif
#ifndef R_AARCH64_P32_RELATIVE
#define R_AARCH64_P32_RELATIVE	183
#endif
#ifndef R_AARCH64_P32_TLS_DTPMOD
#define R_AARCH64_P32_TLS_DTPMOD 184
#endif
#ifndef R_AARCH64_P32_TLS_DTPREL
#define R_AARCH64_P32_TLS_DTPREL 185
#endif
#ifndef R_AARCH64_P32_TLS_TPREL
#define R_AARCH64_P32_TLS_TPREL	186
#endif
#ifndef R_AARCH64_P32_TLSDESC
#define R_AARCH64_P32_TLSDESC	187
#endif
#ifndef R_AARCH64_P32_IRELATIVE
#define R_AARCH64_P32_IRELATIVE	188
#endif
#ifndef R_AARCH64_ABS64
#define R_AARCH64_ABS64         257
#endif
#ifndef R_AARCH64_ABS32
#define R_AARCH64_ABS32         258
#endif
#ifndef R_AARCH64_ABS16
#define R_AARCH64_ABS16		259
#endif
#ifndef R_AARCH64_PREL64
#define R_AARCH64_PREL64	260
#endif
#ifndef R_AARCH64_PREL32
#define R_AARCH64_PREL32	261
#endif
#ifndef R_AARCH64_PREL16
#define R_AARCH64_PREL16	262
#endif
#ifndef R_AARCH64_MOVW_UABS_G0
#define R_AARCH64_MOVW_UABS_G0	263
#endif
#ifndef R_AARCH64_MOVW_UABS_G0_NC
#define R_AARCH64_MOVW_UABS_G0_NC 264
#endif
#ifndef R_AARCH64_MOVW_UABS_G1
#define R_AARCH64_MOVW_UABS_G1	265
#endif
#ifndef R_AARCH64_MOVW_UABS_G1_NC
#define R_AARCH64_MOVW_UABS_G1_NC 266
#endif
#ifndef R_AARCH64_MOVW_UABS_G2
#define R_AARCH64_MOVW_UABS_G2	267
#endif
#ifndef R_AARCH64_MOVW_UABS_G2_NC
#define R_AARCH64_MOVW_UABS_G2_NC 268
#endif
#ifndef R_AARCH64_MOVW_UABS_G3
#define R_AARCH64_MOVW_UABS_G3	269
#endif
#ifndef R_AARCH64_MOVW_SABS_G0
#define R_AARCH64_MOVW_SABS_G0	270
#endif
#ifndef R_AARCH64_MOVW_SABS_G1
#define R_AARCH64_MOVW_SABS_G1	271
#endif
#ifndef R_AARCH64_MOVW_SABS_G2
#define R_AARCH64_MOVW_SABS_G2	272
#endif
#ifndef R_AARCH64_LD_PREL_LO19
#define R_AARCH64_LD_PREL_LO19	273
#endif
#ifndef R_AARCH64_ADR_PREL_LO21
#define R_AARCH64_ADR_PREL_LO21	274
#endif
#ifndef R_AARCH64_ADR_PREL_PG_HI21
#define R_AARCH64_ADR_PREL_PG_HI21 275
#endif
#ifndef R_AARCH64_ADR_PREL_PG_HI21_NC
#define R_AARCH64_ADR_PREL_PG_HI21_NC 276
#endif
#ifndef R_AARCH64_ADD_ABS_LO12_NC
#define R_AARCH64_ADD_ABS_LO12_NC 277
#endif
#ifndef R_AARCH64_LDST8_ABS_LO12_NC
#define R_AARCH64_LDST8_ABS_LO12_NC 278
#endif
#ifndef R_AARCH64_TSTBR14
#define R_AARCH64_TSTBR14	279
#endif
#ifndef R_AARCH64_CONDBR19
#define R_AARCH64_CONDBR19	280
#endif
#ifndef R_AARCH64_JUMP26
#define R_AARCH64_JUMP26	282
#endif
#ifndef R_AARCH64_CALL26
#define R_AARCH64_CALL26	283
#endif
#ifndef R_AARCH64_LDST16_ABS_LO12_NC
#define R_AARCH64_LDST16_ABS_LO12_NC 284
#endif
#ifndef R_AARCH64_LDST32_ABS_LO12_NC
#define R_AARCH64_LDST32_ABS_LO12_NC 285
#endif
#ifndef R_AARCH64_LDST64_ABS_LO12_NC
#define R_AARCH64_LDST64_ABS_LO12_NC 286
#endif
#ifndef R_AARCH64_MOVW_PREL_G0
#define R_AARCH64_MOVW_PREL_G0	287
#endif
#ifndef R_AARCH64_MOVW_PREL_G0_NC
#define R_AARCH64_MOVW_PREL_G0_NC 288
#endif
#ifndef R_AARCH64_MOVW_PREL_G1
#define R_AARCH64_MOVW_PREL_G1	289
#endif
#ifndef R_AARCH64_MOVW_PREL_G1_NC
#define R_AARCH64_MOVW_PREL_G1_NC 290
#endif
#ifndef R_AARCH64_MOVW_PREL_G2
#define R_AARCH64_MOVW_PREL_G2	291
#endif
#ifndef R_AARCH64_MOVW_PREL_G2_NC
#define R_AARCH64_MOVW_PREL_G2_NC 292
#endif
#ifndef R_AARCH64_MOVW_PREL_G3
#define R_AARCH64_MOVW_PREL_G3	293
#endif
#ifndef R_AARCH64_LDST128_ABS_LO12_NC
#define R_AARCH64_LDST128_ABS_LO12_NC 299
#endif
#ifndef R_AARCH64_MOVW_GOTOFF_G0
#define R_AARCH64_MOVW_GOTOFF_G0 300
#endif
#ifndef R_AARCH64_MOVW_GOTOFF_G0_NC
#define R_AARCH64_MOVW_GOTOFF_G0_NC 301
#endif
#ifndef R_AARCH64_MOVW_GOTOFF_G1
#define R_AARCH64_MOVW_GOTOFF_G1 302
#endif
#ifndef R_AARCH64_MOVW_GOTOFF_G1_NC
#define R_AARCH64_MOVW_GOTOFF_G1_NC 303
#endif
#ifndef R_AARCH64_MOVW_GOTOFF_G2
#define R_AARCH64_MOVW_GOTOFF_G2 304
#endif
#ifndef R_AARCH64_MOVW_GOTOFF_G2_NC
#define R_AARCH64_MOVW_GOTOFF_G2_NC 305
#endif
#ifndef R_AARCH64_MOVW_GOTOFF_G3
#define R_AARCH64_MOVW_GOTOFF_G3 306
#endif
#ifndef R_AARCH64_GOTREL64
#define R_AARCH64_GOTREL64	307
#endif
#ifndef R_AARCH64_GOTREL32
#define R_AARCH64_GOTREL32	308
#endif
#ifndef R_AARCH64_GOT_LD_PREL19
#define R_AARCH64_GOT_LD_PREL19	309
#endif
#ifndef R_AARCH64_LD64_GOTOFF_LO15
#define R_AARCH64_LD64_GOTOFF_LO15 310
#endif
#ifndef R_AARCH64_ADR_GOT_PAGE
#define R_AARCH64_ADR_GOT_PAGE	311
#endif
#ifndef R_AARCH64_LD64_GOT_LO12_NC
#define R_AARCH64_LD64_GOT_LO12_NC 312
#endif
#ifndef R_AARCH64_LD64_GOTPAGE_LO15
#define R_AARCH64_LD64_GOTPAGE_LO15 313
#endif
#ifndef R_AARCH64_TLSGD_ADR_PREL21
#define R_AARCH64_TLSGD_ADR_PREL21 512
#endif
#ifndef R_AARCH64_TLSGD_ADR_PAGE21
#define R_AARCH64_TLSGD_ADR_PAGE21 513
#endif
#ifndef R_AARCH64_TLSGD_ADD_LO12_NC
#define R_AARCH64_TLSGD_ADD_LO12_NC 514
#endif
#ifndef R_AARCH64_TLSGD_MOVW_G1
#define R_AARCH64_TLSGD_MOVW_G1	515
#endif
#ifndef R_AARCH64_TLSGD_MOVW_G0_NC
#define R_AARCH64_TLSGD_MOVW_G0_NC 516
#endif
#ifndef R_AARCH64_TLSLD_ADR_PREL21
#define R_AARCH64_TLSLD_ADR_PREL21 517
#endif
#ifndef R_AARCH64_TLSLD_ADR_PAGE21
#define R_AARCH64_TLSLD_ADR_PAGE21 518
#endif
#ifndef R_AARCH64_TLSLD_ADD_LO12_NC
#define R_AARCH64_TLSLD_ADD_LO12_NC 519
#endif
#ifndef R_AARCH64_TLSLD_MOVW_G1
#define R_AARCH64_TLSLD_MOVW_G1	520
#endif
#ifndef R_AARCH64_TLSLD_MOVW_G0_NC
#define R_AARCH64_TLSLD_MOVW_G0_NC 521
#endif
#ifndef R_AARCH64_TLSLD_LD_PREL19
#define R_AARCH64_TLSLD_LD_PREL19 522
#endif
#ifndef R_AARCH64_TLSLD_MOVW_DTPREL_G2
#define R_AARCH64_TLSLD_MOVW_DTPREL_G2 523
#endif
#ifndef R_AARCH64_TLSLD_MOVW_DTPREL_G1
#define R_AARCH64_TLSLD_MOVW_DTPREL_G1 524
#endif
#ifndef R_AARCH64_TLSLD_MOVW_DTPREL_G1_NC
#define R_AARCH64_TLSLD_MOVW_DTPREL_G1_NC 525
#endif
#ifndef R_AARCH64_TLSLD_MOVW_DTPREL_G0
#define R_AARCH64_TLSLD_MOVW_DTPREL_G0 526
#endif
#ifndef R_AARCH64_TLSLD_MOVW_DTPREL_G0_NC
#define R_AARCH64_TLSLD_MOVW_DTPREL_G0_NC 527
#endif
#ifndef R_AARCH64_TLSLD_ADD_DTPREL_HI12
#define R_AARCH64_TLSLD_ADD_DTPREL_HI12 528
#endif
#ifndef R_AARCH64_TLSLD_ADD_DTPREL_LO12
#define R_AARCH64_TLSLD_ADD_DTPREL_LO12 529
#endif
#ifndef R_AARCH64_TLSLD_ADD_DTPREL_LO12_NC
#define R_AARCH64_TLSLD_ADD_DTPREL_LO12_NC 530
#endif
#ifndef R_AARCH64_TLSLD_LDST8_DTPREL_LO12
#define R_AARCH64_TLSLD_LDST8_DTPREL_LO12 531
#endif
#ifndef R_AARCH64_TLSLD_LDST8_DTPREL_LO12_NC
#define R_AARCH64_TLSLD_LDST8_DTPREL_LO12_NC 532
#endif
#ifndef R_AARCH64_TLSLD_LDST16_DTPREL_LO12
#define R_AARCH64_TLSLD_LDST16_DTPREL_LO12 533
#endif
#ifndef R_AARCH64_TLSLD_LDST16_DTPREL_LO12_NC
#define R_AARCH64_TLSLD_LDST16_DTPREL_LO12_NC 534
#endif
#ifndef R_AARCH64_TLSLD_LDST32_DTPREL_LO12
#define R_AARCH64_TLSLD_LDST32_DTPREL_LO12 535
#endif
#ifndef R_AARCH64_TLSLD_LDST32_DTPREL_LO12_NC
#define R_AARCH64_TLSLD_LDST32_DTPREL_LO12_NC 536
#endif
#ifndef R_AARCH64_TLSLD_LDST64_DTPREL_LO12
#define R_AARCH64_TLSLD_LDST64_DTPREL_LO12 537
#endif
#ifndef R_AARCH64_TLSLD_LDST64_DTPREL_LO12_NC
#define R_AARCH64_TLSLD_LDST64_DTPREL_LO12_NC 538
#endif
#ifndef R_AARCH64_TLSIE_MOVW_GOTTPREL_G1
#define R_AARCH64_TLSIE_MOVW_GOTTPREL_G1 539
#endif
#ifndef R_AARCH64_TLSIE_MOVW_GOTTPREL_G0_NC
#define R_AARCH64_TLSIE_MOVW_GOTTPREL_G0_NC 540
#endif
#ifndef R_AARCH64_TLSIE_ADR_GOTTPREL_PAGE21
#define R_AARCH64_TLSIE_ADR_GOTTPREL_PAGE21 541
#endif
#ifndef R_AARCH64_TLSIE_LD64_GOTTPREL_LO12_NC
#define R_AARCH64_TLSIE_LD64_GOTTPREL_LO12_NC 542
#endif
#ifndef R_AARCH64_TLSIE_LD_GOTTPREL_PREL19
#define R_AARCH64_TLSIE_LD_GOTTPREL_PREL19 543
#endif
#ifndef R_AARCH64_TLSLE_MOVW_TPREL_G2
#define R_AARCH64_TLSLE_MOVW_TPREL_G2 544
#endif
#ifndef R_AARCH64_TLSLE_MOVW_TPREL_G1
#define R_AARCH64_TLSLE_MOVW_TPREL_G1 545
#endif
#ifndef R_AARCH64_TLSLE_MOVW_TPREL_G1_NC
#define R_AARCH64_TLSLE_MOVW_TPREL_G1_NC 546
#endif
#ifndef R_AARCH64_TLSLE_MOVW_TPREL_G0
#define R_AARCH64_TLSLE_MOVW_TPREL_G0 547
#endif
#ifndef R_AARCH64_TLSLE_MOVW_TPREL_G0_NC
#define R_AARCH64_TLSLE_MOVW_TPREL_G0_NC 548
#endif
#ifndef R_AARCH64_TLSLE_ADD_TPREL_HI12
#define R_AARCH64_TLSLE_ADD_TPREL_HI12 549
#endif
#ifndef R_AARCH64_TLSLE_ADD_TPREL_LO12
#define R_AARCH64_TLSLE_ADD_TPREL_LO12 550
#endif
#ifndef R_AARCH64_TLSLE_ADD_TPREL_LO12_NC
#define R_AARCH64_TLSLE_ADD_TPREL_LO12_NC 551
#endif
#ifndef R_AARCH64_TLSLE_LDST8_TPREL_LO12
#define R_AARCH64_TLSLE_LDST8_TPREL_LO12 552
#endif
#ifndef R_AARCH64_TLSLE_LDST8_TPREL_LO12_NC
#define R_AARCH64_TLSLE_LDST8_TPREL_LO12_NC 553
#endif
#ifndef R_AARCH64_TLSLE_LDST16_TPREL_LO12
#define R_AARCH64_TLSLE_LDST16_TPREL_LO12 554
#endif
#ifndef R_AARCH64_TLSLE_LDST16_TPREL_LO12_NC
#define R_AARCH64_TLSLE_LDST16_TPREL_LO12_NC 555
#endif
#ifndef R_AARCH64_TLSLE_LDST32_TPREL_LO12
#define R_AARCH64_TLSLE_LDST32_TPREL_LO12 556
#endif
#ifndef R_AARCH64_TLSLE_LDST32_TPREL_LO12_NC
#define R_AARCH64_TLSLE_LDST32_TPREL_LO12_NC 557
#endif
#ifndef R_AARCH64_TLSLE_LDST64_TPREL_LO12
#define R_AARCH64_TLSLE_LDST64_TPREL_LO12 558
#endif
#ifndef R_AARCH64_TLSLE_LDST64_TPREL_LO12_NC
#define R_AARCH64_TLSLE_LDST64_TPREL_LO12_NC 559
#endif
#ifndef R_AARCH64_TLSDESC_LD_PREL19
#define R_AARCH64_TLSDESC_LD_PREL19 560
#endif
#ifndef R_AARCH64_TLSDESC_ADR_PREL21
#define R_AARCH64_TLSDESC_ADR_PREL21 561
#endif
#ifndef R_AARCH64_TLSDESC_ADR_PAGE21
#define R_AARCH64_TLSDESC_ADR_PAGE21 562
#endif
#ifndef R_AARCH64_TLSDESC_LD64_LO12
#define R_AARCH64_TLSDESC_LD64_LO12 563
#endif
#ifndef R_AARCH64_TLSDESC_ADD_LO12
#define R_AARCH64_TLSDESC_ADD_LO12 564
#endif
#ifndef R_AARCH64_TLSDESC_OFF_G1
#define R_AARCH64_TLSDESC_OFF_G1 565
#endif
#ifndef R_AARCH64_TLSDESC_OFF_G0_NC
#define R_AARCH64_TLSDESC_OFF_G0_NC 566
#endif
#ifndef R_AARCH64_TLSDESC_LDR
#define R_AARCH64_TLSDESC_LDR	567
#endif
#ifndef R_AARCH64_TLSDESC_ADD
#define R_AARCH64_TLSDESC_ADD	568
#endif
#ifndef R_AARCH64_TLSDESC_CALL
#define R_AARCH64_TLSDESC_CALL	569
#endif
#ifndef R_AARCH64_TLSLE_LDST128_TPREL_LO12
#define R_AARCH64_TLSLE_LDST128_TPREL_LO12 570
#endif
#ifndef R_AARCH64_TLSLE_LDST128_TPREL_LO12_NC
#define R_AARCH64_TLSLE_LDST128_TPREL_LO12_NC 571
#endif
#ifndef R_AARCH64_TLSLD_LDST128_DTPREL_LO12
#define R_AARCH64_TLSLD_LDST128_DTPREL_LO12 572
#endif
#ifndef R_AARCH64_TLSLD_LDST128_DTPREL_LO12_NC
#define R_AARCH64_TLSLD_LDST128_DTPREL_LO12_NC 573
#endif
#ifndef R_AARCH64_COPY
#define R_AARCH64_COPY         1024
#endif
#ifndef R_AARCH64_GLOB_DAT
#define R_AARCH64_GLOB_DAT     1025
#endif
#ifndef R_AARCH64_JUMP_SLOT
#define R_AARCH64_JUMP_SLOT    1026
#endif
#ifndef R_AARCH64_RELATIVE
#define R_AARCH64_RELATIVE     1027
#endif
#ifndef R_AARCH64_TLS_DTPMOD
#define R_AARCH64_TLS_DTPMOD   1028
#endif
#ifndef R_AARCH64_TLS_DTPMOD64
#define R_AARCH64_TLS_DTPMOD64 1028
#endif
#ifndef R_AARCH64_TLS_DTPREL
#define R_AARCH64_TLS_DTPREL   1029
#endif
#ifndef R_AARCH64_TLS_DTPREL64
#define R_AARCH64_TLS_DTPREL64 1029
#endif
#ifndef R_AARCH64_TLS_TPREL
#define R_AARCH64_TLS_TPREL    1030
#endif
#ifndef R_AARCH64_TLS_TPREL64
#define R_AARCH64_TLS_TPREL64  1030
#endif
#ifndef R_AARCH64_TLSDESC
#define R_AARCH64_TLSDESC      1031
#endif
#ifndef R_ARM_NONE
#define R_ARM_NONE		0
#endif
#ifndef R_ARM_PC24
#define R_ARM_PC24		1
#endif
#ifndef R_ARM_ABS32
#define R_ARM_ABS32		2
#endif
#ifndef R_ARM_REL32
#define R_ARM_REL32		3
#endif
#ifndef R_ARM_PC13
#define R_ARM_PC13		4
#endif
#ifndef R_ARM_ABS16
#define R_ARM_ABS16		5
#endif
#ifndef R_ARM_ABS12
#define R_ARM_ABS12		6
#endif
#ifndef R_ARM_THM_ABS5
#define R_ARM_THM_ABS5		7
#endif
#ifndef R_ARM_ABS8
#define R_ARM_ABS8		8
#endif
#ifndef R_ARM_SBREL32
#define R_ARM_SBREL32		9
#endif
#ifndef R_ARM_THM_PC22
#define R_ARM_THM_PC22		10
#endif
#ifndef R_ARM_THM_PC8
#define R_ARM_THM_PC8		11
#endif
#ifndef R_ARM_AMP_VCALL9
#define R_ARM_AMP_VCALL9	12
#endif
#ifndef R_ARM_TLS_DESC
#define R_ARM_TLS_DESC		13
#endif
#ifndef R_ARM_THM_SWI8
#define R_ARM_THM_SWI8		14
#endif
#ifndef R_ARM_XPC25
#define R_ARM_XPC25		15
#endif
#ifndef R_ARM_THM_XPC22
#define R_ARM_THM_XPC22		16
#endif
#ifndef R_ARM_TLS_DTPMOD32
#define R_ARM_TLS_DTPMOD32	17
#endif
#ifndef R_ARM_TLS_DTPOFF32
#define R_ARM_TLS_DTPOFF32	18
#endif
#ifndef R_ARM_TLS_TPOFF32
#define R_ARM_TLS_TPOFF32	19
#endif
#ifndef R_ARM_COPY
#define R_ARM_COPY		20
#endif
#ifndef R_ARM_GLOB_DAT
#define R_ARM_GLOB_DAT		21
#endif
#ifndef R_ARM_JUMP_SLOT
#define R_ARM_JUMP_SLOT		22
#endif
#ifndef R_ARM_RELATIVE
#define R_ARM_RELATIVE		23
#endif
#ifndef R_ARM_GOTOFF
#define R_ARM_GOTOFF		24
#endif
#ifndef R_ARM_GOTPC
#define R_ARM_GOTPC		25
#endif
#ifndef R_ARM_GOT32
#define R_ARM_GOT32		26
#endif
#ifndef R_ARM_PLT32
#define R_ARM_PLT32		27
#endif
#ifndef R_ARM_CALL
#define R_ARM_CALL		28
#endif
#ifndef R_ARM_JUMP24
#define R_ARM_JUMP24		29
#endif
#ifndef R_ARM_THM_JUMP24
#define R_ARM_THM_JUMP24	30
#endif
#ifndef R_ARM_BASE_ABS
#define R_ARM_BASE_ABS		31
#endif
#ifndef R_ARM_ALU_PCREL_7_0
#define R_ARM_ALU_PCREL_7_0	32
#endif
#ifndef R_ARM_ALU_PCREL_15_8
#define R_ARM_ALU_PCREL_15_8	33
#endif
#ifndef R_ARM_ALU_PCREL_23_15
#define R_ARM_ALU_PCREL_23_15	34
#endif
#ifndef R_ARM_LDR_SBREL_11_0
#define R_ARM_LDR_SBREL_11_0	35
#endif
#ifndef R_ARM_ALU_SBREL_19_12
#define R_ARM_ALU_SBREL_19_12	36
#endif
#ifndef R_ARM_ALU_SBREL_27_20
#define R_ARM_ALU_SBREL_27_20	37
#endif
#ifndef R_ARM_TARGET1
#define R_ARM_TARGET1		38
#endif
#ifndef R_ARM_SBREL31
#define R_ARM_SBREL31		39
#endif
#ifndef R_ARM_V4BX
#define R_ARM_V4BX		40
#endif
#ifndef R_ARM_TARGET2
#define R_ARM_TARGET2		41
#endif
#ifndef R_ARM_PREL31
#define R_ARM_PREL31		42
#endif
#ifndef R_ARM_MOVW_ABS_NC
#define R_ARM_MOVW_ABS_NC	43
#endif
#ifndef R_ARM_MOVT_ABS
#define R_ARM_MOVT_ABS		44
#endif
#ifndef R_ARM_MOVW_PREL_NC
#define R_ARM_MOVW_PREL_NC	45
#endif
#ifndef R_ARM_MOVT_PREL
#define R_ARM_MOVT_PREL		46
#endif
#ifndef R_ARM_THM_MOVW_ABS_NC
#define R_ARM_THM_MOVW_ABS_NC	47
#endif
#ifndef R_ARM_THM_MOVT_ABS
#define R_ARM_THM_MOVT_ABS	48
#endif
#ifndef R_ARM_THM_MOVW_PREL_NC
#define R_ARM_THM_MOVW_PREL_NC	49
#endif
#ifndef R_ARM_THM_MOVT_PREL
#define R_ARM_THM_MOVT_PREL	50
#endif
#ifndef R_ARM_THM_JUMP19
#define R_ARM_THM_JUMP19	51
#endif
#ifndef R_ARM_THM_JUMP6
#define R_ARM_THM_JUMP6		52
#endif
#ifndef R_ARM_THM_ALU_PREL_11_0
#define R_ARM_THM_ALU_PREL_11_0	53
#endif
#ifndef R_ARM_THM_PC12
#define R_ARM_THM_PC12		54
#endif
#ifndef R_ARM_ABS32_NOI
#define R_ARM_ABS32_NOI		55
#endif
#ifndef R_ARM_REL32_NOI
#define R_ARM_REL32_NOI		56
#endif
#ifndef R_ARM_ALU_PC_G0_NC
#define R_ARM_ALU_PC_G0_NC	57
#endif
#ifndef R_ARM_ALU_PC_G0
#define R_ARM_ALU_PC_G0		58
#endif
#ifndef R_ARM_ALU_PC_G1_NC
#define R_ARM_ALU_PC_G1_NC	59
#endif
#ifndef R_ARM_ALU_PC_G1
#define R_ARM_ALU_PC_G1		60
#endif
#ifndef R_ARM_ALU_PC_G2
#define R_ARM_ALU_PC_G2		61
#endif
#ifndef R_ARM_LDR_PC_G1
#define R_ARM_LDR_PC_G1		62
#endif
#ifndef R_ARM_LDR_PC_G2
#define R_ARM_LDR_PC_G2		63
#endif
#ifndef R_ARM_LDRS_PC_G0
#define R_ARM_LDRS_PC_G0	64
#endif
#ifndef R_ARM_LDRS_PC_G1
#define R_ARM_LDRS_PC_G1	65
#endif
#ifndef R_ARM_LDRS_PC_G2
#define R_ARM_LDRS_PC_G2	66
#endif
#ifndef R_ARM_LDC_PC_G0
#define R_ARM_LDC_PC_G0		67
#endif
#ifndef R_ARM_LDC_PC_G1
#define R_ARM_LDC_PC_G1		68
#endif
#ifndef R_ARM_LDC_PC_G2
#define R_ARM_LDC_PC_G2		69
#endif
#ifndef R_ARM_ALU_SB_G0_NC
#define R_ARM_ALU_SB_G0_NC	70
#endif
#ifndef R_ARM_ALU_SB_G0
#define R_ARM_ALU_SB_G0		71
#endif
#ifndef R_ARM_ALU_SB_G1_NC
#define R_ARM_ALU_SB_G1_NC	72
#endif
#ifndef R_ARM_ALU_SB_G1
#define R_ARM_ALU_SB_G1		73
#endif
#ifndef R_ARM_ALU_SB_G2
#define R_ARM_ALU_SB_G2		74
#endif
#ifndef R_ARM_LDR_SB_G0
#define R_ARM_LDR_SB_G0		75
#endif
#ifndef R_ARM_LDR_SB_G1
#define R_ARM_LDR_SB_G1		76
#endif
#ifndef R_ARM_LDR_SB_G2
#define R_ARM_LDR_SB_G2		77
#endif
#ifndef R_ARM_LDRS_SB_G0
#define R_ARM_LDRS_SB_G0	78
#endif
#ifndef R_ARM_LDRS_SB_G1
#define R_ARM_LDRS_SB_G1	79
#endif
#ifndef R_ARM_LDRS_SB_G2
#define R_ARM_LDRS_SB_G2	80
#endif
#ifndef R_ARM_LDC_SB_G0
#define R_ARM_LDC_SB_G0		81
#endif
#ifndef R_ARM_LDC_SB_G1
#define R_ARM_LDC_SB_G1		82
#endif
#ifndef R_ARM_LDC_SB_G2
#define R_ARM_LDC_SB_G2		83
#endif
#ifndef R_ARM_MOVW_BREL_NC
#define R_ARM_MOVW_BREL_NC	84
#endif
#ifndef R_ARM_MOVT_BREL
#define R_ARM_MOVT_BREL		85
#endif
#ifndef R_ARM_MOVW_BREL
#define R_ARM_MOVW_BREL		86
#endif
#ifndef R_ARM_THM_MOVW_BREL_NC
#define R_ARM_THM_MOVW_BREL_NC	87
#endif
#ifndef R_ARM_THM_MOVT_BREL
#define R_ARM_THM_MOVT_BREL	88
#endif
#ifndef R_ARM_THM_MOVW_BREL
#define R_ARM_THM_MOVW_BREL	89
#endif
#ifndef R_ARM_TLS_GOTDESC
#define R_ARM_TLS_GOTDESC	90
#endif
#ifndef R_ARM_TLS_CALL
#define R_ARM_TLS_CALL		91
#endif
#ifndef R_ARM_TLS_DESCSEQ
#define R_ARM_TLS_DESCSEQ	92
#endif
#ifndef R_ARM_THM_TLS_CALL
#define R_ARM_THM_TLS_CALL	93
#endif
#ifndef R_ARM_PLT32_ABS
#define R_ARM_PLT32_ABS		94
#endif
#ifndef R_ARM_GOT_ABS
#define R_ARM_GOT_ABS		95
#endif
#ifndef R_ARM_GOT_PREL
#define R_ARM_GOT_PREL		96
#endif
#ifndef R_ARM_GOT_BREL12
#define R_ARM_GOT_BREL12	97
#endif
#ifndef R_ARM_GOTOFF12
#define R_ARM_GOTOFF12		98
#endif
#ifndef R_ARM_GOTRELAX
#define R_ARM_GOTRELAX		99
#endif
#ifndef R_ARM_GNU_VTENTRY
#define R_ARM_GNU_VTENTRY	100
#endif
#ifndef R_ARM_GNU_VTINHERIT
#define R_ARM_GNU_VTINHERIT	101
#endif
#ifndef R_ARM_THM_PC11
#define R_ARM_THM_PC11		102
#endif
#ifndef R_ARM_THM_PC9
#define R_ARM_THM_PC9		103
#endif
#ifndef R_ARM_TLS_GD32
#define R_ARM_TLS_GD32		104
#endif
#ifndef R_ARM_TLS_LDM32
#define R_ARM_TLS_LDM32		105
#endif
#ifndef R_ARM_TLS_LDO32
#define R_ARM_TLS_LDO32		106
#endif
#ifndef R_ARM_TLS_IE32
#define R_ARM_TLS_IE32		107
#endif
#ifndef R_ARM_TLS_LE32
#define R_ARM_TLS_LE32		108
#endif
#ifndef R_ARM_TLS_LDO12
#define R_ARM_TLS_LDO12		109
#endif
#ifndef R_ARM_TLS_LE12
#define R_ARM_TLS_LE12		110
#endif
#ifndef R_ARM_TLS_IE12GP
#define R_ARM_TLS_IE12GP	111
#endif
#ifndef R_ARM_ME_TOO
#define R_ARM_ME_TOO		128
#endif
#ifndef R_ARM_THM_TLS_DESCSEQ
#define R_ARM_THM_TLS_DESCSEQ	129
#endif
#ifndef R_ARM_THM_TLS_DESCSEQ16
#define R_ARM_THM_TLS_DESCSEQ16	129
#endif
#ifndef R_ARM_THM_TLS_DESCSEQ32
#define R_ARM_THM_TLS_DESCSEQ32	130
#endif
#ifndef R_ARM_THM_GOT_BREL12
#define R_ARM_THM_GOT_BREL12	131
#endif
#ifndef R_ARM_IRELATIVE
#define R_ARM_IRELATIVE		160
#endif
#ifndef R_ARM_RXPC25
#define R_ARM_RXPC25		249
#endif
#ifndef R_ARM_RSBREL32
#define R_ARM_RSBREL32		250
#endif
#ifndef R_ARM_THM_RPC22
#define R_ARM_THM_RPC22		251
#endif
#ifndef R_ARM_RREL32
#define R_ARM_RREL32		252
#endif
#ifndef R_ARM_RABS22
#define R_ARM_RABS22		253
#endif
#ifndef R_ARM_RPC24
#define R_ARM_RPC24		254
#endif
#ifndef R_ARM_RBASE
#define R_ARM_RBASE		255
#endif
#ifndef R_ARM_NUM
#define R_ARM_NUM		256
#endif
#ifndef R_CKCORE_NONE
#define R_CKCORE_NONE               0
#endif
#ifndef R_CKCORE_ADDR32
#define R_CKCORE_ADDR32             1
#endif
#ifndef R_CKCORE_PCRELIMM8BY4
#define R_CKCORE_PCRELIMM8BY4       2
#endif
#ifndef R_CKCORE_PCRELIMM11BY2
#define R_CKCORE_PCRELIMM11BY2      3
#endif
#ifndef R_CKCORE_PCREL32
#define R_CKCORE_PCREL32            5
#endif
#ifndef R_CKCORE_PCRELJSR_IMM11BY2
#define R_CKCORE_PCRELJSR_IMM11BY2  6
#endif
#ifndef R_CKCORE_RELATIVE
#define R_CKCORE_RELATIVE           9
#endif
#ifndef R_CKCORE_COPY
#define R_CKCORE_COPY               10
#endif
#ifndef R_CKCORE_GLOB_DAT
#define R_CKCORE_GLOB_DAT           11
#endif
#ifndef R_CKCORE_JUMP_SLOT
#define R_CKCORE_JUMP_SLOT          12
#endif
#ifndef R_CKCORE_GOTOFF
#define R_CKCORE_GOTOFF             13
#endif
#ifndef R_CKCORE_GOTPC
#define R_CKCORE_GOTPC              14
#endif
#ifndef R_CKCORE_GOT32
#define R_CKCORE_GOT32              15
#endif
#ifndef R_CKCORE_PLT32
#define R_CKCORE_PLT32              16
#endif
#ifndef R_CKCORE_ADDRGOT
#define R_CKCORE_ADDRGOT            17
#endif
#ifndef R_CKCORE_ADDRPLT
#define R_CKCORE_ADDRPLT            18
#endif
#ifndef R_CKCORE_PCREL_IMM26BY2
#define R_CKCORE_PCREL_IMM26BY2     19
#endif
#ifndef R_CKCORE_PCREL_IMM16BY2
#define R_CKCORE_PCREL_IMM16BY2     20
#endif
#ifndef R_CKCORE_PCREL_IMM16BY4
#define R_CKCORE_PCREL_IMM16BY4     21
#endif
#ifndef R_CKCORE_PCREL_IMM10BY2
#define R_CKCORE_PCREL_IMM10BY2     22
#endif
#ifndef R_CKCORE_PCREL_IMM10BY4
#define R_CKCORE_PCREL_IMM10BY4     23
#endif
#ifndef R_CKCORE_ADDR_HI16
#define R_CKCORE_ADDR_HI16          24
#endif
#ifndef R_CKCORE_ADDR_LO16
#define R_CKCORE_ADDR_LO16          25
#endif
#ifndef R_CKCORE_GOTPC_HI16
#define R_CKCORE_GOTPC_HI16         26
#endif
#ifndef R_CKCORE_GOTPC_LO16
#define R_CKCORE_GOTPC_LO16         27
#endif
#ifndef R_CKCORE_GOTOFF_HI16
#define R_CKCORE_GOTOFF_HI16        28
#endif
#ifndef R_CKCORE_GOTOFF_LO16
#define R_CKCORE_GOTOFF_LO16        29
#endif
#ifndef R_CKCORE_GOT12
#define R_CKCORE_GOT12              30
#endif
#ifndef R_CKCORE_GOT_HI16
#define R_CKCORE_GOT_HI16           31
#endif
#ifndef R_CKCORE_GOT_LO16
#define R_CKCORE_GOT_LO16           32
#endif
#ifndef R_CKCORE_PLT12
#define R_CKCORE_PLT12              33
#endif
#ifndef R_CKCORE_PLT_HI16
#define R_CKCORE_PLT_HI16           34
#endif
#ifndef R_CKCORE_PLT_LO16
#define R_CKCORE_PLT_LO16           35
#endif
#ifndef R_CKCORE_ADDRGOT_HI16
#define R_CKCORE_ADDRGOT_HI16       36
#endif
#ifndef R_CKCORE_ADDRGOT_LO16
#define R_CKCORE_ADDRGOT_LO16       37
#endif
#ifndef R_CKCORE_ADDRPLT_HI16
#define R_CKCORE_ADDRPLT_HI16       38
#endif
#ifndef R_CKCORE_ADDRPLT_LO16
#define R_CKCORE_ADDRPLT_LO16       39
#endif
#ifndef R_CKCORE_PCREL_JSR_IMM26BY2
#define R_CKCORE_PCREL_JSR_IMM26BY2 40
#endif
#ifndef R_CKCORE_TOFFSET_LO16
#define R_CKCORE_TOFFSET_LO16       41
#endif
#ifndef R_CKCORE_DOFFSET_LO16
#define R_CKCORE_DOFFSET_LO16       42
#endif
#ifndef R_CKCORE_PCREL_IMM18BY2
#define R_CKCORE_PCREL_IMM18BY2     43
#endif
#ifndef R_CKCORE_DOFFSET_IMM18
#define R_CKCORE_DOFFSET_IMM18      44
#endif
#ifndef R_CKCORE_DOFFSET_IMM18BY2
#define R_CKCORE_DOFFSET_IMM18BY2   45
#endif
#ifndef R_CKCORE_DOFFSET_IMM18BY4
#define R_CKCORE_DOFFSET_IMM18BY4   46
#endif
#ifndef R_CKCORE_GOT_IMM18BY4
#define R_CKCORE_GOT_IMM18BY4       48
#endif
#ifndef R_CKCORE_PLT_IMM18BY4
#define R_CKCORE_PLT_IMM18BY4       49
#endif
#ifndef R_CKCORE_PCREL_IMM7BY4
#define R_CKCORE_PCREL_IMM7BY4      50
#endif
#ifndef R_CKCORE_TLS_LE32
#define R_CKCORE_TLS_LE32           51
#endif
#ifndef R_CKCORE_TLS_IE32
#define R_CKCORE_TLS_IE32           52
#endif
#ifndef R_CKCORE_TLS_GD32
#define R_CKCORE_TLS_GD32           53
#endif
#ifndef R_CKCORE_TLS_LDM32
#define R_CKCORE_TLS_LDM32          54
#endif
#ifndef R_CKCORE_TLS_LDO32
#define R_CKCORE_TLS_LDO32          55
#endif
#ifndef R_CKCORE_TLS_DTPMOD32
#define R_CKCORE_TLS_DTPMOD32       56
#endif
#ifndef R_CKCORE_TLS_DTPOFF32
#define R_CKCORE_TLS_DTPOFF32       57
#endif
#ifndef R_CKCORE_TLS_TPOFF32
#define R_CKCORE_TLS_TPOFF32        58
#endif
#ifndef EF_IA_64_MASKOS
#define EF_IA_64_MASKOS		0x0000000f
#endif
#ifndef EF_IA_64_ABI64
#define EF_IA_64_ABI64		0x00000010
#endif
#ifndef EF_IA_64_ARCH
#define EF_IA_64_ARCH		0xff000000
#endif
#ifndef PT_IA_64_ARCHEXT
#define PT_IA_64_ARCHEXT	(PT_LOPROC + 0)
#endif
#ifndef PT_IA_64_UNWIND
#define PT_IA_64_UNWIND		(PT_LOPROC + 1)
#endif
#ifndef PT_IA_64_HP_OPT_ANOT
#define PT_IA_64_HP_OPT_ANOT	(PT_LOOS + 0x12)
#endif
#ifndef PT_IA_64_HP_HSL_ANOT
#define PT_IA_64_HP_HSL_ANOT	(PT_LOOS + 0x13)
#endif
#ifndef PT_IA_64_HP_STACK
#define PT_IA_64_HP_STACK	(PT_LOOS + 0x14)
#endif
#ifndef PF_IA_64_NORECOV
#define PF_IA_64_NORECOV	0x80000000
#endif
#ifndef SHT_IA_64_EXT
#define SHT_IA_64_EXT		(SHT_LOPROC + 0)
#endif
#ifndef SHT_IA_64_UNWIND
#define SHT_IA_64_UNWIND	(SHT_LOPROC + 1)
#endif
#ifndef SHF_IA_64_SHORT
#define SHF_IA_64_SHORT		0x10000000
#endif
#ifndef SHF_IA_64_NORECOV
#define SHF_IA_64_NORECOV	0x20000000
#endif
#ifndef DT_IA_64_PLT_RESERVE
#define DT_IA_64_PLT_RESERVE	(DT_LOPROC + 0)
#endif
#ifndef DT_IA_64_NUM
#define DT_IA_64_NUM		1
#endif
#ifndef R_IA64_NONE
#define R_IA64_NONE		0x00
#endif
#ifndef R_IA64_IMM14
#define R_IA64_IMM14		0x21
#endif
#ifndef R_IA64_IMM22
#define R_IA64_IMM22		0x22
#endif
#ifndef R_IA64_IMM64
#define R_IA64_IMM64		0x23
#endif
#ifndef R_IA64_DIR32MSB
#define R_IA64_DIR32MSB		0x24
#endif
#ifndef R_IA64_DIR32LSB
#define R_IA64_DIR32LSB		0x25
#endif
#ifndef R_IA64_DIR64MSB
#define R_IA64_DIR64MSB		0x26
#endif
#ifndef R_IA64_DIR64LSB
#define R_IA64_DIR64LSB		0x27
#endif
#ifndef R_IA64_GPREL22
#define R_IA64_GPREL22		0x2a
#endif
#ifndef R_IA64_GPREL64I
#define R_IA64_GPREL64I		0x2b
#endif
#ifndef R_IA64_GPREL32MSB
#define R_IA64_GPREL32MSB	0x2c
#endif
#ifndef R_IA64_GPREL32LSB
#define R_IA64_GPREL32LSB	0x2d
#endif
#ifndef R_IA64_GPREL64MSB
#define R_IA64_GPREL64MSB	0x2e
#endif
#ifndef R_IA64_GPREL64LSB
#define R_IA64_GPREL64LSB	0x2f
#endif
#ifndef R_IA64_LTOFF22
#define R_IA64_LTOFF22		0x32
#endif
#ifndef R_IA64_LTOFF64I
#define R_IA64_LTOFF64I		0x33
#endif
#ifndef R_IA64_PLTOFF22
#define R_IA64_PLTOFF22		0x3a
#endif
#ifndef R_IA64_PLTOFF64I
#define R_IA64_PLTOFF64I	0x3b
#endif
#ifndef R_IA64_PLTOFF64MSB
#define R_IA64_PLTOFF64MSB	0x3e
#endif
#ifndef R_IA64_PLTOFF64LSB
#define R_IA64_PLTOFF64LSB	0x3f
#endif
#ifndef R_IA64_FPTR64I
#define R_IA64_FPTR64I		0x43
#endif
#ifndef R_IA64_FPTR32MSB
#define R_IA64_FPTR32MSB	0x44
#endif
#ifndef R_IA64_FPTR32LSB
#define R_IA64_FPTR32LSB	0x45
#endif
#ifndef R_IA64_FPTR64MSB
#define R_IA64_FPTR64MSB	0x46
#endif
#ifndef R_IA64_FPTR64LSB
#define R_IA64_FPTR64LSB	0x47
#endif
#ifndef R_IA64_PCREL60B
#define R_IA64_PCREL60B		0x48
#endif
#ifndef R_IA64_PCREL21B
#define R_IA64_PCREL21B		0x49
#endif
#ifndef R_IA64_PCREL21M
#define R_IA64_PCREL21M		0x4a
#endif
#ifndef R_IA64_PCREL21F
#define R_IA64_PCREL21F		0x4b
#endif
#ifndef R_IA64_PCREL32MSB
#define R_IA64_PCREL32MSB	0x4c
#endif
#ifndef R_IA64_PCREL32LSB
#define R_IA64_PCREL32LSB	0x4d
#endif
#ifndef R_IA64_PCREL64MSB
#define R_IA64_PCREL64MSB	0x4e
#endif
#ifndef R_IA64_PCREL64LSB
#define R_IA64_PCREL64LSB	0x4f
#endif
#ifndef R_IA64_LTOFF_FPTR22
#define R_IA64_LTOFF_FPTR22	0x52
#endif
#ifndef R_IA64_LTOFF_FPTR64I
#define R_IA64_LTOFF_FPTR64I	0x53
#endif
#ifndef R_IA64_LTOFF_FPTR32MSB
#define R_IA64_LTOFF_FPTR32MSB	0x54
#endif
#ifndef R_IA64_LTOFF_FPTR32LSB
#define R_IA64_LTOFF_FPTR32LSB	0x55
#endif
#ifndef R_IA64_LTOFF_FPTR64MSB
#define R_IA64_LTOFF_FPTR64MSB	0x56
#endif
#ifndef R_IA64_LTOFF_FPTR64LSB
#define R_IA64_LTOFF_FPTR64LSB	0x57
#endif
#ifndef R_IA64_SEGREL32MSB
#define R_IA64_SEGREL32MSB	0x5c
#endif
#ifndef R_IA64_SEGREL32LSB
#define R_IA64_SEGREL32LSB	0x5d
#endif
#ifndef R_IA64_SEGREL64MSB
#define R_IA64_SEGREL64MSB	0x5e
#endif
#ifndef R_IA64_SEGREL64LSB
#define R_IA64_SEGREL64LSB	0x5f
#endif
#ifndef R_IA64_SECREL32MSB
#define R_IA64_SECREL32MSB	0x64
#endif
#ifndef R_IA64_SECREL32LSB
#define R_IA64_SECREL32LSB	0x65
#endif
#ifndef R_IA64_SECREL64MSB
#define R_IA64_SECREL64MSB	0x66
#endif
#ifndef R_IA64_SECREL64LSB
#define R_IA64_SECREL64LSB	0x67
#endif
#ifndef R_IA64_REL32MSB
#define R_IA64_REL32MSB		0x6c
#endif
#ifndef R_IA64_REL32LSB
#define R_IA64_REL32LSB		0x6d
#endif
#ifndef R_IA64_REL64MSB
#define R_IA64_REL64MSB		0x6e
#endif
#ifndef R_IA64_REL64LSB
#define R_IA64_REL64LSB		0x6f
#endif
#ifndef R_IA64_LTV32MSB
#define R_IA64_LTV32MSB		0x74
#endif
#ifndef R_IA64_LTV32LSB
#define R_IA64_LTV32LSB		0x75
#endif
#ifndef R_IA64_LTV64MSB
#define R_IA64_LTV64MSB		0x76
#endif
#ifndef R_IA64_LTV64LSB
#define R_IA64_LTV64LSB		0x77
#endif
#ifndef R_IA64_PCREL21BI
#define R_IA64_PCREL21BI	0x79
#endif
#ifndef R_IA64_PCREL22
#define R_IA64_PCREL22		0x7a
#endif
#ifndef R_IA64_PCREL64I
#define R_IA64_PCREL64I		0x7b
#endif
#ifndef R_IA64_IPLTMSB
#define R_IA64_IPLTMSB		0x80
#endif
#ifndef R_IA64_IPLTLSB
#define R_IA64_IPLTLSB		0x81
#endif
#ifndef R_IA64_COPY
#define R_IA64_COPY		0x84
#endif
#ifndef R_IA64_SUB
#define R_IA64_SUB		0x85
#endif
#ifndef R_IA64_LTOFF22X
#define R_IA64_LTOFF22X		0x86
#endif
#ifndef R_IA64_LDXMOV
#define R_IA64_LDXMOV		0x87
#endif
#ifndef R_IA64_TPREL14
#define R_IA64_TPREL14		0x91
#endif
#ifndef R_IA64_TPREL22
#define R_IA64_TPREL22		0x92
#endif
#ifndef R_IA64_TPREL64I
#define R_IA64_TPREL64I		0x93
#endif
#ifndef R_IA64_TPREL64MSB
#define R_IA64_TPREL64MSB	0x96
#endif
#ifndef R_IA64_TPREL64LSB
#define R_IA64_TPREL64LSB	0x97
#endif
#ifndef R_IA64_LTOFF_TPREL22
#define R_IA64_LTOFF_TPREL22	0x9a
#endif
#ifndef R_IA64_DTPMOD64MSB
#define R_IA64_DTPMOD64MSB	0xa6
#endif
#ifndef R_IA64_DTPMOD64LSB
#define R_IA64_DTPMOD64LSB	0xa7
#endif
#ifndef R_IA64_LTOFF_DTPMOD22
#define R_IA64_LTOFF_DTPMOD22	0xaa
#endif
#ifndef R_IA64_DTPREL14
#define R_IA64_DTPREL14		0xb1
#endif
#ifndef R_IA64_DTPREL22
#define R_IA64_DTPREL22		0xb2
#endif
#ifndef R_IA64_DTPREL64I
#define R_IA64_DTPREL64I	0xb3
#endif
#ifndef R_IA64_DTPREL32MSB
#define R_IA64_DTPREL32MSB	0xb4
#endif
#ifndef R_IA64_DTPREL32LSB
#define R_IA64_DTPREL32LSB	0xb5
#endif
#ifndef R_IA64_DTPREL64MSB
#define R_IA64_DTPREL64MSB	0xb6
#endif
#ifndef R_IA64_DTPREL64LSB
#define R_IA64_DTPREL64LSB	0xb7
#endif
#ifndef R_IA64_LTOFF_DTPREL22
#define R_IA64_LTOFF_DTPREL22	0xba
#endif
#ifndef EF_SH_MACH_MASK
#define EF_SH_MACH_MASK		0x1f
#endif
#ifndef EF_SH_UNKNOWN
#define EF_SH_UNKNOWN		0x0
#endif
#ifndef EF_SH1
#define EF_SH1			0x1
#endif
#ifndef EF_SH2
#define EF_SH2			0x2
#endif
#ifndef EF_SH3
#define EF_SH3			0x3
#endif
#ifndef EF_SH_DSP
#define EF_SH_DSP		0x4
#endif
#ifndef EF_SH3_DSP
#define EF_SH3_DSP		0x5
#endif
#ifndef EF_SH4AL_DSP
#define EF_SH4AL_DSP		0x6
#endif
#ifndef EF_SH3E
#define EF_SH3E			0x8
#endif
#ifndef EF_SH4
#define EF_SH4			0x9
#endif
#ifndef EF_SH2E
#define EF_SH2E			0xb
#endif
#ifndef EF_SH4A
#define EF_SH4A			0xc
#endif
#ifndef EF_SH2A
#define EF_SH2A			0xd
#endif
#ifndef EF_SH4_NOFPU
#define EF_SH4_NOFPU		0x10
#endif
#ifndef EF_SH4A_NOFPU
#define EF_SH4A_NOFPU		0x11
#endif
#ifndef EF_SH4_NOMMU_NOFPU
#define EF_SH4_NOMMU_NOFPU	0x12
#endif
#ifndef EF_SH2A_NOFPU
#define EF_SH2A_NOFPU		0x13
#endif
#ifndef EF_SH3_NOMMU
#define EF_SH3_NOMMU		0x14
#endif
#ifndef EF_SH2A_SH4_NOFPU
#define EF_SH2A_SH4_NOFPU	0x15
#endif
#ifndef EF_SH2A_SH3_NOFPU
#define EF_SH2A_SH3_NOFPU	0x16
#endif
#ifndef EF_SH2A_SH4
#define EF_SH2A_SH4		0x17
#endif
#ifndef EF_SH2A_SH3E
#define EF_SH2A_SH3E		0x18
#endif
#ifndef R_390_NONE
#define R_390_NONE		0
#endif
#ifndef R_390_8
#define R_390_8			1
#endif
#ifndef R_390_12
#define R_390_12		2
#endif
#ifndef R_390_16
#define R_390_16		3
#endif
#ifndef R_390_32
#define R_390_32		4
#endif
#ifndef R_390_PC32
#define R_390_PC32		5
#endif
#ifndef R_390_GOT12
#define R_390_GOT12		6
#endif
#ifndef R_390_GOT32
#define R_390_GOT32		7
#endif
#ifndef R_390_PLT32
#define R_390_PLT32		8
#endif
#ifndef R_390_COPY
#define R_390_COPY		9
#endif
#ifndef R_390_GLOB_DAT
#define R_390_GLOB_DAT		10
#endif
#ifndef R_390_JMP_SLOT
#define R_390_JMP_SLOT		11
#endif
#ifndef R_390_RELATIVE
#define R_390_RELATIVE		12
#endif
#ifndef R_390_GOTOFF32
#define R_390_GOTOFF32		13
#endif
#ifndef R_390_GOTPC
#define R_390_GOTPC		14
#endif
#ifndef R_390_GOT16
#define R_390_GOT16		15
#endif
#ifndef R_390_PC16
#define R_390_PC16		16
#endif
#ifndef R_390_PC16DBL
#define R_390_PC16DBL		17
#endif
#ifndef R_390_PLT16DBL
#define R_390_PLT16DBL		18
#endif
#ifndef R_390_PC32DBL
#define R_390_PC32DBL		19
#endif
#ifndef R_390_PLT32DBL
#define R_390_PLT32DBL		20
#endif
#ifndef R_390_GOTPCDBL
#define R_390_GOTPCDBL		21
#endif
#ifndef R_390_64
#define R_390_64		22
#endif
#ifndef R_390_PC64
#define R_390_PC64		23
#endif
#ifndef R_390_GOT64
#define R_390_GOT64		24
#endif
#ifndef R_390_PLT64
#define R_390_PLT64		25
#endif
#ifndef R_390_GOTENT
#define R_390_GOTENT		26
#endif
#ifndef R_390_GOTOFF16
#define R_390_GOTOFF16		27
#endif
#ifndef R_390_GOTOFF64
#define R_390_GOTOFF64		28
#endif
#ifndef R_390_GOTPLT12
#define R_390_GOTPLT12		29
#endif
#ifndef R_390_GOTPLT16
#define R_390_GOTPLT16		30
#endif
#ifndef R_390_GOTPLT32
#define R_390_GOTPLT32		31
#endif
#ifndef R_390_GOTPLT64
#define R_390_GOTPLT64		32
#endif
#ifndef R_390_GOTPLTENT
#define R_390_GOTPLTENT		33
#endif
#ifndef R_390_PLTOFF16
#define R_390_PLTOFF16		34
#endif
#ifndef R_390_PLTOFF32
#define R_390_PLTOFF32		35
#endif
#ifndef R_390_PLTOFF64
#define R_390_PLTOFF64		36
#endif
#ifndef R_390_TLS_LOAD
#define R_390_TLS_LOAD		37
#endif
#ifndef R_390_TLS_GDCALL
#define R_390_TLS_GDCALL	38
#endif
#ifndef R_390_TLS_LDCALL
#define R_390_TLS_LDCALL	39
#endif
#ifndef R_390_TLS_GD32
#define R_390_TLS_GD32		40
#endif
#ifndef R_390_TLS_GD64
#define R_390_TLS_GD64		41
#endif
#ifndef R_390_TLS_GOTIE12
#define R_390_TLS_GOTIE12	42
#endif
#ifndef R_390_TLS_GOTIE32
#define R_390_TLS_GOTIE32	43
#endif
#ifndef R_390_TLS_GOTIE64
#define R_390_TLS_GOTIE64	44
#endif
#ifndef R_390_TLS_LDM32
#define R_390_TLS_LDM32		45
#endif
#ifndef R_390_TLS_LDM64
#define R_390_TLS_LDM64		46
#endif
#ifndef R_390_TLS_IE32
#define R_390_TLS_IE32		47
#endif
#ifndef R_390_TLS_IE64
#define R_390_TLS_IE64		48
#endif
#ifndef R_390_TLS_IEENT
#define R_390_TLS_IEENT		49
#endif
#ifndef R_390_TLS_LE32
#define R_390_TLS_LE32		50
#endif
#ifndef R_390_TLS_LE64
#define R_390_TLS_LE64		51
#endif
#ifndef R_390_TLS_LDO32
#define R_390_TLS_LDO32		52
#endif
#ifndef R_390_TLS_LDO64
#define R_390_TLS_LDO64		53
#endif
#ifndef R_390_TLS_DTPMOD
#define R_390_TLS_DTPMOD	54
#endif
#ifndef R_390_TLS_DTPOFF
#define R_390_TLS_DTPOFF	55
#endif
#ifndef R_390_TLS_TPOFF
#define R_390_TLS_TPOFF		56
#endif
#ifndef R_390_20
#define R_390_20		57
#endif
#ifndef R_390_GOT20
#define R_390_GOT20		58
#endif
#ifndef R_390_GOTPLT20
#define R_390_GOTPLT20		59
#endif
#ifndef R_390_TLS_GOTIE20
#define R_390_TLS_GOTIE20	60
#endif
#ifndef R_390_NUM
#define R_390_NUM		61
#endif
#ifndef R_CRIS_NONE
#define R_CRIS_NONE		0
#endif
#ifndef R_CRIS_8
#define R_CRIS_8		1
#endif
#ifndef R_CRIS_16
#define R_CRIS_16		2
#endif
#ifndef R_CRIS_32
#define R_CRIS_32		3
#endif
#ifndef R_CRIS_8_PCREL
#define R_CRIS_8_PCREL		4
#endif
#ifndef R_CRIS_16_PCREL
#define R_CRIS_16_PCREL		5
#endif
#ifndef R_CRIS_32_PCREL
#define R_CRIS_32_PCREL		6
#endif
#ifndef R_CRIS_GNU_VTINHERIT
#define R_CRIS_GNU_VTINHERIT	7
#endif
#ifndef R_CRIS_GNU_VTENTRY
#define R_CRIS_GNU_VTENTRY	8
#endif
#ifndef R_CRIS_COPY
#define R_CRIS_COPY		9
#endif
#ifndef R_CRIS_GLOB_DAT
#define R_CRIS_GLOB_DAT		10
#endif
#ifndef R_CRIS_JUMP_SLOT
#define R_CRIS_JUMP_SLOT	11
#endif
#ifndef R_CRIS_RELATIVE
#define R_CRIS_RELATIVE		12
#endif
#ifndef R_CRIS_16_GOT
#define R_CRIS_16_GOT		13
#endif
#ifndef R_CRIS_32_GOT
#define R_CRIS_32_GOT		14
#endif
#ifndef R_CRIS_16_GOTPLT
#define R_CRIS_16_GOTPLT	15
#endif
#ifndef R_CRIS_32_GOTPLT
#define R_CRIS_32_GOTPLT	16
#endif
#ifndef R_CRIS_32_GOTREL
#define R_CRIS_32_GOTREL	17
#endif
#ifndef R_CRIS_32_PLT_GOTREL
#define R_CRIS_32_PLT_GOTREL	18
#endif
#ifndef R_CRIS_32_PLT_PCREL
#define R_CRIS_32_PLT_PCREL	19
#endif
#ifndef R_CRIS_NUM
#define R_CRIS_NUM		20
#endif
#ifndef R_X86_64_NONE
#define R_X86_64_NONE		0
#endif
#ifndef R_X86_64_64
#define R_X86_64_64		1
#endif
#ifndef R_X86_64_PC32
#define R_X86_64_PC32		2
#endif
#ifndef R_X86_64_GOT32
#define R_X86_64_GOT32		3
#endif
#ifndef R_X86_64_PLT32
#define R_X86_64_PLT32		4
#endif
#ifndef R_X86_64_COPY
#define R_X86_64_COPY		5
#endif
#ifndef R_X86_64_GLOB_DAT
#define R_X86_64_GLOB_DAT	6
#endif
#ifndef R_X86_64_JUMP_SLOT
#define R_X86_64_JUMP_SLOT	7
#endif
#ifndef R_X86_64_RELATIVE
#define R_X86_64_RELATIVE	8
#endif
#ifndef R_X86_64_GOTPCREL
#define R_X86_64_GOTPCREL	9
#endif
#ifndef R_X86_64_32
#define R_X86_64_32		10
#endif
#ifndef R_X86_64_32S
#define R_X86_64_32S		11
#endif
#ifndef R_X86_64_16
#define R_X86_64_16		12
#endif
#ifndef R_X86_64_PC16
#define R_X86_64_PC16		13
#endif
#ifndef R_X86_64_8
#define R_X86_64_8		14
#endif
#ifndef R_X86_64_PC8
#define R_X86_64_PC8		15
#endif
#ifndef R_X86_64_DTPMOD64
#define R_X86_64_DTPMOD64	16
#endif
#ifndef R_X86_64_DTPOFF64
#define R_X86_64_DTPOFF64	17
#endif
#ifndef R_X86_64_TPOFF64
#define R_X86_64_TPOFF64	18
#endif
#ifndef R_X86_64_TLSGD
#define R_X86_64_TLSGD		19
#endif
#ifndef R_X86_64_TLSLD
#define R_X86_64_TLSLD		20
#endif
#ifndef R_X86_64_DTPOFF32
#define R_X86_64_DTPOFF32	21
#endif
#ifndef R_X86_64_GOTTPOFF
#define R_X86_64_GOTTPOFF	22
#endif
#ifndef R_X86_64_TPOFF32
#define R_X86_64_TPOFF32	23
#endif
#ifndef R_X86_64_PC64
#define R_X86_64_PC64		24
#endif
#ifndef R_X86_64_GOTOFF64
#define R_X86_64_GOTOFF64	25
#endif
#ifndef R_X86_64_GOTPC32
#define R_X86_64_GOTPC32	26
#endif
#ifndef R_X86_64_GOT64
#define R_X86_64_GOT64		27
#endif
#ifndef R_X86_64_GOTPCREL64
#define R_X86_64_GOTPCREL64	28
#endif
#ifndef R_X86_64_GOTPC64
#define R_X86_64_GOTPC64	29
#endif
#ifndef R_X86_64_GOTPLT64
#define R_X86_64_GOTPLT64	30
#endif
#ifndef R_X86_64_PLTOFF64
#define R_X86_64_PLTOFF64	31
#endif
#ifndef R_X86_64_SIZE32
#define R_X86_64_SIZE32		32
#endif
#ifndef R_X86_64_SIZE64
#define R_X86_64_SIZE64		33
#endif
#ifndef R_X86_64_GOTPC32_TLSDESC
#define R_X86_64_GOTPC32_TLSDESC 34
#endif
#ifndef R_X86_64_TLSDESC_CALL
#define R_X86_64_TLSDESC_CALL   35
#endif
#ifndef R_X86_64_TLSDESC
#define R_X86_64_TLSDESC        36
#endif
#ifndef R_X86_64_IRELATIVE
#define R_X86_64_IRELATIVE	37
#endif
#ifndef R_X86_64_RELATIVE64
#define R_X86_64_RELATIVE64	38
#endif
#ifndef R_X86_64_GOTPCRELX
#define R_X86_64_GOTPCRELX	41
#endif
#ifndef R_X86_64_REX_GOTPCRELX
#define R_X86_64_REX_GOTPCRELX	42
#endif
#ifndef R_X86_64_NUM
#define R_X86_64_NUM		43
#endif
#ifndef R_MN10300_NONE
#define R_MN10300_NONE		0
#endif
#ifndef R_MN10300_32
#define R_MN10300_32		1
#endif
#ifndef R_MN10300_16
#define R_MN10300_16		2
#endif
#ifndef R_MN10300_8
#define R_MN10300_8		3
#endif
#ifndef R_MN10300_PCREL32
#define R_MN10300_PCREL32	4
#endif
#ifndef R_MN10300_PCREL16
#define R_MN10300_PCREL16	5
#endif
#ifndef R_MN10300_PCREL8
#define R_MN10300_PCREL8	6
#endif
#ifndef R_MN10300_GNU_VTINHERIT
#define R_MN10300_GNU_VTINHERIT	7
#endif
#ifndef R_MN10300_GNU_VTENTRY
#define R_MN10300_GNU_VTENTRY	8
#endif
#ifndef R_MN10300_24
#define R_MN10300_24		9
#endif
#ifndef R_MN10300_GOTPC32
#define R_MN10300_GOTPC32	10
#endif
#ifndef R_MN10300_GOTPC16
#define R_MN10300_GOTPC16	11
#endif
#ifndef R_MN10300_GOTOFF32
#define R_MN10300_GOTOFF32	12
#endif
#ifndef R_MN10300_GOTOFF24
#define R_MN10300_GOTOFF24	13
#endif
#ifndef R_MN10300_GOTOFF16
#define R_MN10300_GOTOFF16	14
#endif
#ifndef R_MN10300_PLT32
#define R_MN10300_PLT32		15
#endif
#ifndef R_MN10300_PLT16
#define R_MN10300_PLT16		16
#endif
#ifndef R_MN10300_GOT32
#define R_MN10300_GOT32		17
#endif
#ifndef R_MN10300_GOT24
#define R_MN10300_GOT24		18
#endif
#ifndef R_MN10300_GOT16
#define R_MN10300_GOT16		19
#endif
#ifndef R_MN10300_COPY
#define R_MN10300_COPY		20
#endif
#ifndef R_MN10300_GLOB_DAT
#define R_MN10300_GLOB_DAT	21
#endif
#ifndef R_MN10300_JMP_SLOT
#define R_MN10300_JMP_SLOT	22
#endif
#ifndef R_MN10300_RELATIVE
#define R_MN10300_RELATIVE	23
#endif
#ifndef R_MN10300_NUM
#define R_MN10300_NUM		24
#endif
#ifndef R_M32R_NONE
#define R_M32R_NONE		0
#endif
#ifndef R_M32R_16
#define R_M32R_16		1
#endif
#ifndef R_M32R_32
#define R_M32R_32		2
#endif
#ifndef R_M32R_24
#define R_M32R_24		3
#endif
#ifndef R_M32R_10_PCREL
#define R_M32R_10_PCREL		4
#endif
#ifndef R_M32R_18_PCREL
#define R_M32R_18_PCREL		5
#endif
#ifndef R_M32R_26_PCREL
#define R_M32R_26_PCREL		6
#endif
#ifndef R_M32R_HI16_ULO
#define R_M32R_HI16_ULO		7
#endif
#ifndef R_M32R_HI16_SLO
#define R_M32R_HI16_SLO		8
#endif
#ifndef R_M32R_LO16
#define R_M32R_LO16		9
#endif
#ifndef R_M32R_SDA16
#define R_M32R_SDA16		10
#endif
#ifndef R_M32R_GNU_VTINHERIT
#define R_M32R_GNU_VTINHERIT	11
#endif
#ifndef R_M32R_GNU_VTENTRY
#define R_M32R_GNU_VTENTRY	12
#endif
#ifndef R_M32R_16_RELA
#define R_M32R_16_RELA		33
#endif
#ifndef R_M32R_32_RELA
#define R_M32R_32_RELA		34
#endif
#ifndef R_M32R_24_RELA
#define R_M32R_24_RELA		35
#endif
#ifndef R_M32R_10_PCREL_RELA
#define R_M32R_10_PCREL_RELA	36
#endif
#ifndef R_M32R_18_PCREL_RELA
#define R_M32R_18_PCREL_RELA	37
#endif
#ifndef R_M32R_26_PCREL_RELA
#define R_M32R_26_PCREL_RELA	38
#endif
#ifndef R_M32R_HI16_ULO_RELA
#define R_M32R_HI16_ULO_RELA	39
#endif
#ifndef R_M32R_HI16_SLO_RELA
#define R_M32R_HI16_SLO_RELA	40
#endif
#ifndef R_M32R_LO16_RELA
#define R_M32R_LO16_RELA	41
#endif
#ifndef R_M32R_SDA16_RELA
#define R_M32R_SDA16_RELA	42
#endif
#ifndef R_M32R_RELA_GNU_VTINHERIT
#define R_M32R_RELA_GNU_VTINHERIT	43
#endif
#ifndef R_M32R_RELA_GNU_VTENTRY
#define R_M32R_RELA_GNU_VTENTRY	44
#endif
#ifndef R_M32R_REL32
#define R_M32R_REL32		45
#endif
#ifndef R_M32R_GOT24
#define R_M32R_GOT24		48
#endif
#ifndef R_M32R_26_PLTREL
#define R_M32R_26_PLTREL	49
#endif
#ifndef R_M32R_COPY
#define R_M32R_COPY		50
#endif
#ifndef R_M32R_GLOB_DAT
#define R_M32R_GLOB_DAT		51
#endif
#ifndef R_M32R_JMP_SLOT
#define R_M32R_JMP_SLOT		52
#endif
#ifndef R_M32R_RELATIVE
#define R_M32R_RELATIVE		53
#endif
#ifndef R_M32R_GOTOFF
#define R_M32R_GOTOFF		54
#endif
#ifndef R_M32R_GOTPC24
#define R_M32R_GOTPC24		55
#endif
#ifndef R_M32R_GOT16_HI_ULO
#define R_M32R_GOT16_HI_ULO	56
#endif
#ifndef R_M32R_GOT16_HI_SLO
#define R_M32R_GOT16_HI_SLO	57
#endif
#ifndef R_M32R_GOT16_LO
#define R_M32R_GOT16_LO		58
#endif
#ifndef R_M32R_GOTPC_HI_ULO
#define R_M32R_GOTPC_HI_ULO	59
#endif
#ifndef R_M32R_GOTPC_HI_SLO
#define R_M32R_GOTPC_HI_SLO	60
#endif
#ifndef R_M32R_GOTPC_LO
#define R_M32R_GOTPC_LO		61
#endif
#ifndef R_M32R_GOTOFF_HI_ULO
#define R_M32R_GOTOFF_HI_ULO	62
#endif
#ifndef R_M32R_GOTOFF_HI_SLO
#define R_M32R_GOTOFF_HI_SLO	63
#endif
#ifndef R_M32R_GOTOFF_LO
#define R_M32R_GOTOFF_LO	64
#endif
#ifndef R_M32R_NUM
#define R_M32R_NUM		256
#endif
#ifndef R_MICROBLAZE_NONE
#define R_MICROBLAZE_NONE 0
#endif
#ifndef R_MICROBLAZE_32
#define R_MICROBLAZE_32 1
#endif
#ifndef R_MICROBLAZE_32_PCREL
#define R_MICROBLAZE_32_PCREL 2
#endif
#ifndef R_MICROBLAZE_64_PCREL
#define R_MICROBLAZE_64_PCREL 3
#endif
#ifndef R_MICROBLAZE_32_PCREL_LO
#define R_MICROBLAZE_32_PCREL_LO 4
#endif
#ifndef R_MICROBLAZE_64
#define R_MICROBLAZE_64 5
#endif
#ifndef R_MICROBLAZE_32_LO
#define R_MICROBLAZE_32_LO 6
#endif
#ifndef R_MICROBLAZE_SRO32
#define R_MICROBLAZE_SRO32 7
#endif
#ifndef R_MICROBLAZE_SRW32
#define R_MICROBLAZE_SRW32 8
#endif
#ifndef R_MICROBLAZE_64_NONE
#define R_MICROBLAZE_64_NONE 9
#endif
#ifndef R_MICROBLAZE_32_SYM_OP_SYM
#define R_MICROBLAZE_32_SYM_OP_SYM 10
#endif
#ifndef R_MICROBLAZE_GNU_VTINHERIT
#define R_MICROBLAZE_GNU_VTINHERIT 11
#endif
#ifndef R_MICROBLAZE_GNU_VTENTRY
#define R_MICROBLAZE_GNU_VTENTRY 12
#endif
#ifndef R_MICROBLAZE_GOTPC_64
#define R_MICROBLAZE_GOTPC_64 13
#endif
#ifndef R_MICROBLAZE_GOT_64
#define R_MICROBLAZE_GOT_64 14
#endif
#ifndef R_MICROBLAZE_PLT_64
#define R_MICROBLAZE_PLT_64 15
#endif
#ifndef R_MICROBLAZE_REL
#define R_MICROBLAZE_REL 16
#endif
#ifndef R_MICROBLAZE_JUMP_SLOT
#define R_MICROBLAZE_JUMP_SLOT 17
#endif
#ifndef R_MICROBLAZE_GLOB_DAT
#define R_MICROBLAZE_GLOB_DAT 18
#endif
#ifndef R_MICROBLAZE_GOTOFF_64
#define R_MICROBLAZE_GOTOFF_64 19
#endif
#ifndef R_MICROBLAZE_GOTOFF_32
#define R_MICROBLAZE_GOTOFF_32 20
#endif
#ifndef R_MICROBLAZE_COPY
#define R_MICROBLAZE_COPY 21
#endif
#ifndef R_MICROBLAZE_TLS
#define R_MICROBLAZE_TLS 22
#endif
#ifndef R_MICROBLAZE_TLSGD
#define R_MICROBLAZE_TLSGD 23
#endif
#ifndef R_MICROBLAZE_TLSLD
#define R_MICROBLAZE_TLSLD 24
#endif
#ifndef R_MICROBLAZE_TLSDTPMOD32
#define R_MICROBLAZE_TLSDTPMOD32 25
#endif
#ifndef R_MICROBLAZE_TLSDTPREL32
#define R_MICROBLAZE_TLSDTPREL32 26
#endif
#ifndef R_MICROBLAZE_TLSDTPREL64
#define R_MICROBLAZE_TLSDTPREL64 27
#endif
#ifndef R_MICROBLAZE_TLSGOTTPREL32
#define R_MICROBLAZE_TLSGOTTPREL32 28
#endif
#ifndef R_MICROBLAZE_TLSTPREL32
#define R_MICROBLAZE_TLSTPREL32	 29
#endif
#ifndef DT_NIOS2_GP
#define DT_NIOS2_GP             0x70000002
#endif
#ifndef R_NIOS2_NONE
#define R_NIOS2_NONE		0
#endif
#ifndef R_NIOS2_S16
#define R_NIOS2_S16		1
#endif
#ifndef R_NIOS2_U16
#define R_NIOS2_U16		2
#endif
#ifndef R_NIOS2_PCREL16
#define R_NIOS2_PCREL16		3
#endif
#ifndef R_NIOS2_CALL26
#define R_NIOS2_CALL26		4
#endif
#ifndef R_NIOS2_IMM5
#define R_NIOS2_IMM5		5
#endif
#ifndef R_NIOS2_CACHE_OPX
#define R_NIOS2_CACHE_OPX	6
#endif
#ifndef R_NIOS2_IMM6
#define R_NIOS2_IMM6		7
#endif
#ifndef R_NIOS2_IMM8
#define R_NIOS2_IMM8		8
#endif
#ifndef R_NIOS2_HI16
#define R_NIOS2_HI16		9
#endif
#ifndef R_NIOS2_LO16
#define R_NIOS2_LO16		10
#endif
#ifndef R_NIOS2_HIADJ16
#define R_NIOS2_HIADJ16		11
#endif
#ifndef R_NIOS2_BFD_RELOC_32
#define R_NIOS2_BFD_RELOC_32	12
#endif
#ifndef R_NIOS2_BFD_RELOC_16
#define R_NIOS2_BFD_RELOC_16	13
#endif
#ifndef R_NIOS2_BFD_RELOC_8
#define R_NIOS2_BFD_RELOC_8	14
#endif
#ifndef R_NIOS2_GPREL
#define R_NIOS2_GPREL		15
#endif
#ifndef R_NIOS2_GNU_VTINHERIT
#define R_NIOS2_GNU_VTINHERIT	16
#endif
#ifndef R_NIOS2_GNU_VTENTRY
#define R_NIOS2_GNU_VTENTRY	17
#endif
#ifndef R_NIOS2_UJMP
#define R_NIOS2_UJMP		18
#endif
#ifndef R_NIOS2_CJMP
#define R_NIOS2_CJMP		19
#endif
#ifndef R_NIOS2_CALLR
#define R_NIOS2_CALLR		20
#endif
#ifndef R_NIOS2_ALIGN
#define R_NIOS2_ALIGN		21
#endif
#ifndef R_NIOS2_GOT16
#define R_NIOS2_GOT16		22
#endif
#ifndef R_NIOS2_CALL16
#define R_NIOS2_CALL16		23
#endif
#ifndef R_NIOS2_GOTOFF_LO
#define R_NIOS2_GOTOFF_LO	24
#endif
#ifndef R_NIOS2_GOTOFF_HA
#define R_NIOS2_GOTOFF_HA	25
#endif
#ifndef R_NIOS2_PCREL_LO
#define R_NIOS2_PCREL_LO	26
#endif
#ifndef R_NIOS2_PCREL_HA
#define R_NIOS2_PCREL_HA	27
#endif
#ifndef R_NIOS2_TLS_GD16
#define R_NIOS2_TLS_GD16	28
#endif
#ifndef R_NIOS2_TLS_LDM16
#define R_NIOS2_TLS_LDM16	29
#endif
#ifndef R_NIOS2_TLS_LDO16
#define R_NIOS2_TLS_LDO16	30
#endif
#ifndef R_NIOS2_TLS_IE16
#define R_NIOS2_TLS_IE16	31
#endif
#ifndef R_NIOS2_TLS_LE16
#define R_NIOS2_TLS_LE16	32
#endif
#ifndef R_NIOS2_TLS_DTPMOD
#define R_NIOS2_TLS_DTPMOD	33
#endif
#ifndef R_NIOS2_TLS_DTPREL
#define R_NIOS2_TLS_DTPREL	34
#endif
#ifndef R_NIOS2_TLS_TPREL
#define R_NIOS2_TLS_TPREL	35
#endif
#ifndef R_NIOS2_COPY
#define R_NIOS2_COPY		36
#endif
#ifndef R_NIOS2_GLOB_DAT
#define R_NIOS2_GLOB_DAT	37
#endif
#ifndef R_NIOS2_JUMP_SLOT
#define R_NIOS2_JUMP_SLOT	38
#endif
#ifndef R_NIOS2_RELATIVE
#define R_NIOS2_RELATIVE	39
#endif
#ifndef R_NIOS2_GOTOFF
#define R_NIOS2_GOTOFF		40
#endif
#ifndef R_NIOS2_CALL26_NOAT
#define R_NIOS2_CALL26_NOAT	41
#endif
#ifndef R_NIOS2_GOT_LO
#define R_NIOS2_GOT_LO		42
#endif
#ifndef R_NIOS2_GOT_HA
#define R_NIOS2_GOT_HA		43
#endif
#ifndef R_NIOS2_CALL_LO
#define R_NIOS2_CALL_LO		44
#endif
#ifndef R_NIOS2_CALL_HA
#define R_NIOS2_CALL_HA		45
#endif
#ifndef R_OR1K_NONE
#define R_OR1K_NONE		0
#endif
#ifndef R_OR1K_32
#define R_OR1K_32		1
#endif
#ifndef R_OR1K_16
#define R_OR1K_16		2
#endif
#ifndef R_OR1K_8
#define R_OR1K_8		3
#endif
#ifndef R_OR1K_LO_16_IN_INSN
#define R_OR1K_LO_16_IN_INSN	4
#endif
#ifndef R_OR1K_HI_16_IN_INSN
#define R_OR1K_HI_16_IN_INSN	5
#endif
#ifndef R_OR1K_INSN_REL_26
#define R_OR1K_INSN_REL_26	6
#endif
#ifndef R_OR1K_GNU_VTENTRY
#define R_OR1K_GNU_VTENTRY	7
#endif
#ifndef R_OR1K_GNU_VTINHERIT
#define R_OR1K_GNU_VTINHERIT	8
#endif
#ifndef R_OR1K_32_PCREL
#define R_OR1K_32_PCREL		9
#endif
#ifndef R_OR1K_16_PCREL
#define R_OR1K_16_PCREL		10
#endif
#ifndef R_OR1K_8_PCREL
#define R_OR1K_8_PCREL		11
#endif
#ifndef R_OR1K_GOTPC_HI16
#define R_OR1K_GOTPC_HI16	12
#endif
#ifndef R_OR1K_GOTPC_LO16
#define R_OR1K_GOTPC_LO16	13
#endif
#ifndef R_OR1K_GOT16
#define R_OR1K_GOT16		14
#endif
#ifndef R_OR1K_PLT26
#define R_OR1K_PLT26		15
#endif
#ifndef R_OR1K_GOTOFF_HI16
#define R_OR1K_GOTOFF_HI16	16
#endif
#ifndef R_OR1K_GOTOFF_LO16
#define R_OR1K_GOTOFF_LO16	17
#endif
#ifndef R_OR1K_COPY
#define R_OR1K_COPY		18
#endif
#ifndef R_OR1K_GLOB_DAT
#define R_OR1K_GLOB_DAT		19
#endif
#ifndef R_OR1K_JMP_SLOT
#define R_OR1K_JMP_SLOT		20
#endif
#ifndef R_OR1K_RELATIVE
#define R_OR1K_RELATIVE		21
#endif
#ifndef R_OR1K_TLS_GD_HI16
#define R_OR1K_TLS_GD_HI16	22
#endif
#ifndef R_OR1K_TLS_GD_LO16
#define R_OR1K_TLS_GD_LO16	23
#endif
#ifndef R_OR1K_TLS_LDM_HI16
#define R_OR1K_TLS_LDM_HI16	24
#endif
#ifndef R_OR1K_TLS_LDM_LO16
#define R_OR1K_TLS_LDM_LO16	25
#endif
#ifndef R_OR1K_TLS_LDO_HI16
#define R_OR1K_TLS_LDO_HI16	26
#endif
#ifndef R_OR1K_TLS_LDO_LO16
#define R_OR1K_TLS_LDO_LO16	27
#endif
#ifndef R_OR1K_TLS_IE_HI16
#define R_OR1K_TLS_IE_HI16	28
#endif
#ifndef R_OR1K_TLS_IE_LO16
#define R_OR1K_TLS_IE_LO16	29
#endif
#ifndef R_OR1K_TLS_LE_HI16
#define R_OR1K_TLS_LE_HI16	30
#endif
#ifndef R_OR1K_TLS_LE_LO16
#define R_OR1K_TLS_LE_LO16	31
#endif
#ifndef R_OR1K_TLS_TPOFF
#define R_OR1K_TLS_TPOFF	32
#endif
#ifndef R_OR1K_TLS_DTPOFF
#define R_OR1K_TLS_DTPOFF	33
#endif
#ifndef R_OR1K_TLS_DTPMOD
#define R_OR1K_TLS_DTPMOD	34
#endif
#ifndef R_BPF_NONE
#define R_BPF_NONE		0
#endif
#ifndef R_BPF_MAP_FD
#define R_BPF_MAP_FD		1
#endif
#ifndef R_RISCV_NONE
#define R_RISCV_NONE            0
#endif
#ifndef R_RISCV_32
#define R_RISCV_32              1
#endif
#ifndef R_RISCV_64
#define R_RISCV_64              2
#endif
#ifndef R_RISCV_RELATIVE
#define R_RISCV_RELATIVE        3
#endif
#ifndef R_RISCV_COPY
#define R_RISCV_COPY            4
#endif
#ifndef R_RISCV_JUMP_SLOT
#define R_RISCV_JUMP_SLOT       5
#endif
#ifndef R_RISCV_TLS_DTPMOD32
#define R_RISCV_TLS_DTPMOD32    6
#endif
#ifndef R_RISCV_TLS_DTPMOD64
#define R_RISCV_TLS_DTPMOD64    7
#endif
#ifndef R_RISCV_TLS_DTPREL32
#define R_RISCV_TLS_DTPREL32    8
#endif
#ifndef R_RISCV_TLS_DTPREL64
#define R_RISCV_TLS_DTPREL64    9
#endif
#ifndef R_RISCV_TLS_TPREL32
#define R_RISCV_TLS_TPREL32     10
#endif
#ifndef R_RISCV_TLS_TPREL64
#define R_RISCV_TLS_TPREL64     11
#endif
#ifndef R_RISCV_TLSDESC
#define R_RISCV_TLSDESC         12
#endif
#ifndef R_RISCV_BRANCH
#define R_RISCV_BRANCH          16
#endif
#ifndef R_RISCV_JAL
#define R_RISCV_JAL             17
#endif
#ifndef R_RISCV_CALL
#define R_RISCV_CALL            18
#endif
#ifndef R_RISCV_CALL_PLT
#define R_RISCV_CALL_PLT        19
#endif
#ifndef R_RISCV_GOT_HI20
#define R_RISCV_GOT_HI20        20
#endif
#ifndef R_RISCV_TLS_GOT_HI20
#define R_RISCV_TLS_GOT_HI20    21
#endif
#ifndef R_RISCV_TLS_GD_HI20
#define R_RISCV_TLS_GD_HI20     22
#endif
#ifndef R_RISCV_PCREL_HI20
#define R_RISCV_PCREL_HI20      23
#endif
#ifndef R_RISCV_PCREL_LO12_I
#define R_RISCV_PCREL_LO12_I    24
#endif
#ifndef R_RISCV_PCREL_LO12_S
#define R_RISCV_PCREL_LO12_S    25
#endif
#ifndef R_RISCV_HI20
#define R_RISCV_HI20            26
#endif
#ifndef R_RISCV_LO12_I
#define R_RISCV_LO12_I          27
#endif
#ifndef R_RISCV_LO12_S
#define R_RISCV_LO12_S          28
#endif
#ifndef R_RISCV_TPREL_HI20
#define R_RISCV_TPREL_HI20      29
#endif
#ifndef R_RISCV_TPREL_LO12_I
#define R_RISCV_TPREL_LO12_I    30
#endif
#ifndef R_RISCV_TPREL_LO12_S
#define R_RISCV_TPREL_LO12_S    31
#endif
#ifndef R_RISCV_TPREL_ADD
#define R_RISCV_TPREL_ADD       32
#endif
#ifndef R_RISCV_ADD8
#define R_RISCV_ADD8            33
#endif
#ifndef R_RISCV_ADD16
#define R_RISCV_ADD16           34
#endif
#ifndef R_RISCV_ADD32
#define R_RISCV_ADD32           35
#endif
#ifndef R_RISCV_ADD64
#define R_RISCV_ADD64           36
#endif
#ifndef R_RISCV_SUB8
#define R_RISCV_SUB8            37
#endif
#ifndef R_RISCV_SUB16
#define R_RISCV_SUB16           38
#endif
#ifndef R_RISCV_SUB32
#define R_RISCV_SUB32           39
#endif
#ifndef R_RISCV_SUB64
#define R_RISCV_SUB64           40
#endif
#ifndef R_RISCV_GOT32_PCREL
#define R_RISCV_GOT32_PCREL     41
#endif
#ifndef R_RISCV_ALIGN
#define R_RISCV_ALIGN           43
#endif
#ifndef R_RISCV_RVC_BRANCH
#define R_RISCV_RVC_BRANCH      44
#endif
#ifndef R_RISCV_RVC_JUMP
#define R_RISCV_RVC_JUMP        45
#endif
#ifndef R_RISCV_RVC_LUI
#define R_RISCV_RVC_LUI         46
#endif
#ifndef R_RISCV_RELAX
#define R_RISCV_RELAX           51
#endif
#ifndef R_RISCV_SUB6
#define R_RISCV_SUB6            52
#endif
#ifndef R_RISCV_SET6
#define R_RISCV_SET6            53
#endif
#ifndef R_RISCV_SET8
#define R_RISCV_SET8            54
#endif
#ifndef R_RISCV_SET16
#define R_RISCV_SET16           55
#endif
#ifndef R_RISCV_SET32
#define R_RISCV_SET32           56
#endif
#ifndef R_RISCV_32_PCREL
#define R_RISCV_32_PCREL        57
#endif
#ifndef R_RISCV_IRELATIVE
#define R_RISCV_IRELATIVE       58
#endif
#ifndef R_RISCV_PLT32
#define R_RISCV_PLT32           59
#endif
#ifndef R_RISCV_SET_ULEB128
#define R_RISCV_SET_ULEB128     60
#endif
#ifndef R_RISCV_SUB_ULEB128
#define R_RISCV_SUB_ULEB128     61
#endif
#ifndef R_RISCV_TLSDESC_HI20
#define R_RISCV_TLSDESC_HI20    62
#endif
#ifndef R_RISCV_TLSDESC_LOAD_LO12
#define R_RISCV_TLSDESC_LOAD_LO12 63
#endif
#ifndef R_RISCV_TLSDESC_ADD_LO12
#define R_RISCV_TLSDESC_ADD_LO12  64
#endif
#ifndef R_RISCV_TLSDESC_CALL
#define R_RISCV_TLSDESC_CALL    65
#endif
#ifndef EF_LARCH_ABI_MODIFIER_MASK
#define EF_LARCH_ABI_MODIFIER_MASK    0x07
#endif
#ifndef EF_LARCH_ABI_SOFT_FLOAT
#define EF_LARCH_ABI_SOFT_FLOAT       0x01
#endif
#ifndef EF_LARCH_ABI_SINGLE_FLOAT
#define EF_LARCH_ABI_SINGLE_FLOAT     0x02
#endif
#ifndef EF_LARCH_ABI_DOUBLE_FLOAT
#define EF_LARCH_ABI_DOUBLE_FLOAT     0x03
#endif
#ifndef EF_LARCH_OBJABI_V1
#define EF_LARCH_OBJABI_V1            0x40
#endif
#ifndef R_LARCH_NONE
#define R_LARCH_NONE                        0
#endif
#ifndef R_LARCH_32
#define R_LARCH_32                          1
#endif
#ifndef R_LARCH_64
#define R_LARCH_64                          2
#endif
#ifndef R_LARCH_RELATIVE
#define R_LARCH_RELATIVE                    3
#endif
#ifndef R_LARCH_COPY
#define R_LARCH_COPY                        4
#endif
#ifndef R_LARCH_JUMP_SLOT
#define R_LARCH_JUMP_SLOT                   5
#endif
#ifndef R_LARCH_TLS_DTPMOD32
#define R_LARCH_TLS_DTPMOD32                6
#endif
#ifndef R_LARCH_TLS_DTPMOD64
#define R_LARCH_TLS_DTPMOD64                7
#endif
#ifndef R_LARCH_TLS_DTPREL32
#define R_LARCH_TLS_DTPREL32                8
#endif
#ifndef R_LARCH_TLS_DTPREL64
#define R_LARCH_TLS_DTPREL64                9
#endif
#ifndef R_LARCH_TLS_TPREL32
#define R_LARCH_TLS_TPREL32                 10
#endif
#ifndef R_LARCH_TLS_TPREL64
#define R_LARCH_TLS_TPREL64                 11
#endif
#ifndef R_LARCH_IRELATIVE
#define R_LARCH_IRELATIVE                   12
#endif
#ifndef R_LARCH_MARK_LA
#define R_LARCH_MARK_LA                     20
#endif
#ifndef R_LARCH_MARK_PCREL
#define R_LARCH_MARK_PCREL                  21
#endif
#ifndef R_LARCH_SOP_PUSH_PCREL
#define R_LARCH_SOP_PUSH_PCREL              22
#endif
#ifndef R_LARCH_SOP_PUSH_ABSOLUTE
#define R_LARCH_SOP_PUSH_ABSOLUTE           23
#endif
#ifndef R_LARCH_SOP_PUSH_DUP
#define R_LARCH_SOP_PUSH_DUP                24
#endif
#ifndef R_LARCH_SOP_PUSH_GPREL
#define R_LARCH_SOP_PUSH_GPREL              25
#endif
#ifndef R_LARCH_SOP_PUSH_TLS_TPREL
#define R_LARCH_SOP_PUSH_TLS_TPREL          26
#endif
#ifndef R_LARCH_SOP_PUSH_TLS_GOT
#define R_LARCH_SOP_PUSH_TLS_GOT            27
#endif
#ifndef R_LARCH_SOP_PUSH_TLS_GD
#define R_LARCH_SOP_PUSH_TLS_GD             28
#endif
#ifndef R_LARCH_SOP_PUSH_PLT_PCREL
#define R_LARCH_SOP_PUSH_PLT_PCREL          29
#endif
#ifndef R_LARCH_SOP_ASSERT
#define R_LARCH_SOP_ASSERT                  30
#endif
#ifndef R_LARCH_SOP_NOT
#define R_LARCH_SOP_NOT                     31
#endif
#ifndef R_LARCH_SOP_SUB
#define R_LARCH_SOP_SUB                     32
#endif
#ifndef R_LARCH_SOP_SL
#define R_LARCH_SOP_SL                      33
#endif
#ifndef R_LARCH_SOP_SR
#define R_LARCH_SOP_SR                      34
#endif
#ifndef R_LARCH_SOP_ADD
#define R_LARCH_SOP_ADD                     35
#endif
#ifndef R_LARCH_SOP_AND
#define R_LARCH_SOP_AND                     36
#endif
#ifndef R_LARCH_SOP_IF_ELSE
#define R_LARCH_SOP_IF_ELSE                 37
#endif
#ifndef R_LARCH_SOP_POP_32_S_10_5
#define R_LARCH_SOP_POP_32_S_10_5           38
#endif
#ifndef R_LARCH_SOP_POP_32_U_10_12
#define R_LARCH_SOP_POP_32_U_10_12          39
#endif
#ifndef R_LARCH_SOP_POP_32_S_10_12
#define R_LARCH_SOP_POP_32_S_10_12          40
#endif
#ifndef R_LARCH_SOP_POP_32_S_10_16
#define R_LARCH_SOP_POP_32_S_10_16          41
#endif
#ifndef R_LARCH_SOP_POP_32_S_10_16_S2
#define R_LARCH_SOP_POP_32_S_10_16_S2       42
#endif
#ifndef R_LARCH_SOP_POP_32_S_5_20
#define R_LARCH_SOP_POP_32_S_5_20           43
#endif
#ifndef R_LARCH_SOP_POP_32_S_0_5_10_16_S2
#define R_LARCH_SOP_POP_32_S_0_5_10_16_S2   44
#endif
#ifndef R_LARCH_SOP_POP_32_S_0_10_10_16_S2
#define R_LARCH_SOP_POP_32_S_0_10_10_16_S2  45
#endif
#ifndef R_LARCH_SOP_POP_32_U
#define R_LARCH_SOP_POP_32_U                46
#endif
#ifndef R_LARCH_ADD8
#define R_LARCH_ADD8                        47
#endif
#ifndef R_LARCH_ADD16
#define R_LARCH_ADD16                       48
#endif
#ifndef R_LARCH_ADD24
#define R_LARCH_ADD24                       49
#endif
#ifndef R_LARCH_ADD32
#define R_LARCH_ADD32                       50
#endif
#ifndef R_LARCH_ADD64
#define R_LARCH_ADD64                       51
#endif
#ifndef R_LARCH_SUB8
#define R_LARCH_SUB8                        52
#endif
#ifndef R_LARCH_SUB16
#define R_LARCH_SUB16                       53
#endif
#ifndef R_LARCH_SUB24
#define R_LARCH_SUB24                       54
#endif
#ifndef R_LARCH_SUB32
#define R_LARCH_SUB32                       55
#endif
#ifndef R_LARCH_SUB64
#define R_LARCH_SUB64                       56
#endif
#ifndef R_LARCH_GNU_VTINHERIT
#define R_LARCH_GNU_VTINHERIT               57
#endif
#ifndef R_LARCH_GNU_VTENTRY
#define R_LARCH_GNU_VTENTRY                 58
#endif
#ifndef R_LARCH_B16
#define R_LARCH_B16                         64
#endif
#ifndef R_LARCH_B21
#define R_LARCH_B21                         65
#endif
#ifndef R_LARCH_B26
#define R_LARCH_B26                         66
#endif
#ifndef R_LARCH_ABS_HI20
#define R_LARCH_ABS_HI20                    67
#endif
#ifndef R_LARCH_ABS_LO12
#define R_LARCH_ABS_LO12                    68
#endif
#ifndef R_LARCH_ABS64_LO20
#define R_LARCH_ABS64_LO20                  69
#endif
#ifndef R_LARCH_ABS64_HI12
#define R_LARCH_ABS64_HI12                  70
#endif
#ifndef R_LARCH_PCALA_HI20
#define R_LARCH_PCALA_HI20                  71
#endif
#ifndef R_LARCH_PCALA_LO12
#define R_LARCH_PCALA_LO12                  72
#endif
#ifndef R_LARCH_PCALA64_LO20
#define R_LARCH_PCALA64_LO20                73
#endif
#ifndef R_LARCH_PCALA64_HI12
#define R_LARCH_PCALA64_HI12                74
#endif
#ifndef R_LARCH_GOT_PC_HI20
#define R_LARCH_GOT_PC_HI20                 75
#endif
#ifndef R_LARCH_GOT_PC_LO12
#define R_LARCH_GOT_PC_LO12                 76
#endif
#ifndef R_LARCH_GOT64_PC_LO20
#define R_LARCH_GOT64_PC_LO20               77
#endif
#ifndef R_LARCH_GOT64_PC_HI12
#define R_LARCH_GOT64_PC_HI12               78
#endif
#ifndef R_LARCH_GOT_HI20
#define R_LARCH_GOT_HI20                    79
#endif
#ifndef R_LARCH_GOT_LO12
#define R_LARCH_GOT_LO12                    80
#endif
#ifndef R_LARCH_GOT64_LO20
#define R_LARCH_GOT64_LO20                  81
#endif
#ifndef R_LARCH_GOT64_HI12
#define R_LARCH_GOT64_HI12                  82
#endif
#ifndef R_LARCH_TLS_LE_HI20
#define R_LARCH_TLS_LE_HI20                 83
#endif
#ifndef R_LARCH_TLS_LE_LO12
#define R_LARCH_TLS_LE_LO12                 84
#endif
#ifndef R_LARCH_TLS_LE64_LO20
#define R_LARCH_TLS_LE64_LO20               85
#endif
#ifndef R_LARCH_TLS_LE64_HI12
#define R_LARCH_TLS_LE64_HI12               86
#endif
#ifndef R_LARCH_TLS_IE_PC_HI20
#define R_LARCH_TLS_IE_PC_HI20              87
#endif
#ifndef R_LARCH_TLS_IE_PC_LO12
#define R_LARCH_TLS_IE_PC_LO12              88
#endif
#ifndef R_LARCH_TLS_IE64_PC_LO20
#define R_LARCH_TLS_IE64_PC_LO20            89
#endif
#ifndef R_LARCH_TLS_IE64_PC_HI12
#define R_LARCH_TLS_IE64_PC_HI12            90
#endif
#ifndef R_LARCH_TLS_IE_HI20
#define R_LARCH_TLS_IE_HI20                 91
#endif
#ifndef R_LARCH_TLS_IE_LO12
#define R_LARCH_TLS_IE_LO12                 92
#endif
#ifndef R_LARCH_TLS_IE64_LO20
#define R_LARCH_TLS_IE64_LO20               93
#endif
#ifndef R_LARCH_TLS_IE64_HI12
#define R_LARCH_TLS_IE64_HI12               94
#endif
#ifndef R_LARCH_TLS_LD_PC_HI20
#define R_LARCH_TLS_LD_PC_HI20              95
#endif
#ifndef R_LARCH_TLS_LD_HI20
#define R_LARCH_TLS_LD_HI20                 96
#endif
#ifndef R_LARCH_TLS_GD_PC_HI20
#define R_LARCH_TLS_GD_PC_HI20              97
#endif
#ifndef R_LARCH_TLS_GD_HI20
#define R_LARCH_TLS_GD_HI20                 98
#endif
#ifndef R_LARCH_32_PCREL
#define R_LARCH_32_PCREL                    99
#endif
#ifndef R_LARCH_RELAX
#define R_LARCH_RELAX                       100
#endif

#endif /* TERMUX_COMPAT_ELF_H */
