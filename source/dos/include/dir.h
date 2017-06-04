#ifndef __INC_DIR
#define __INC_DIR
#if !defined(__INC__DOS)
 #include <dos.h>
#endif

#define MAXDRIVE	3
#define MAXEXT		5
#define MAXFILE		9
#define MAXDIR		66
#define MAXPATH		80

#define MAXDRIVES	32

#define WMAXPATH	260
#define WMAXDRIVE	3
#define WMAXDIR		256
#define WMAXFILE	256
#define WMAXEXT		256
#define _MAX_PATH	260

#define _A_STDFILES	(_A_ARCH|_A_RDONLY|_A_SYSTEM|_A_SUBDIR)
#define _A_ALLFILES	(_A_STDFILES|_A_HIDDEN)

#ifdef __cplusplus
 extern "C" {
#endif

int _CType getdrv(void);
int _CType chdrv(int);
int _CType chdir(char *);
int _CType mkdir(char *);
int _CType rmdir(char *);
char * _CType getcwdd(char *, int __drv);
char * _CType fullpath(char *, int __drv);
char * _CType searchp(char *__file);

extern int (*fp_directory)(char *);
extern int (*fp_fileblock)(char *, wfblk *);
extern char *fp_maskp;

extern char scan_curpath[]; // & = [900] byte
extern char scan_curfile[];
extern wfblk scan_fblock;

int _CType scansub(char *__path, char *__mask, int __flag);
int _CType scan_files(char *__path);
int _CType scan_directory(int __flag, char *__path);

int _CType recursive(char *__file, char *__path, char *__dest);

//extern char far * _CType envpath;
//extern char far * _CType envtemp;

#ifdef __cplusplus
}
#endif
#endif
