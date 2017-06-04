#ifndef __INC_STAT
#define __INC_STAT

#define S_IFMT		0xF000
#define S_IFDIR		0x4000
#define S_IFIFO		0x1000
#define S_IFCHR		0x2000
#define S_IFBLK		0x3000
#define S_IFREG		0x8000
#define S_IREAD		0x0100
#define S_IWRITE	0x0080
#define S_IEXEC		0x0040

#endif
