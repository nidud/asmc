#ifndef __INC_MD5
#define __INC_MD5
#if !defined(__INC_DEFS)
 #include <defs.h>
#endif
#pragma comment(lib, "ntdll.lib")

typedef struct {
    unsigned int state[4];
    unsigned int count[2];
    unsigned char buffer[64];
    unsigned char digest[16];
    } MD5_CTX;

extern void WINAPI MD5Init(MD5_CTX *);
extern void WINAPI MD5Update(MD5_CTX *, unsigned char *, unsigned int);
extern void WINAPI MD5Final(MD5_CTX *);

#endif
