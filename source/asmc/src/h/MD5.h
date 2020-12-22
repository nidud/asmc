#ifndef __INC_MD5
#define __INC_MD5

typedef struct {
    unsigned int state[4];
    unsigned int count[2];
    unsigned char buffer[64];
    unsigned char digest[16];
  } MD5_CTX;

void WINAPI MD5Init(MD5_CTX *);
void WINAPI MD5Update(MD5_CTX *, unsigned char *, unsigned int);
void WINAPI MD5Final(MD5_CTX *);

#endif
