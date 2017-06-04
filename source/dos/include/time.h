#ifndef __INC_TIME
#define __INC_TIME
#if !defined(__INC_DEFS)
 #include <defs.h>
#endif
#ifdef __cplusplus
 extern "C" {
#endif

#define DT_BASEYEAR	1980
#define dwtoday(w)	((w) & 0x001F)
#define dwtomnd(w)	(((w) >> 5) & 0x000F)
#define dwtoyear(w)	(((w) >> 9) + DT_BASEYEAR)

int  _CType getyear(void);
char _CType getmnd(void);
char _CType getday(void);
char _CType gethour(void);
char _CType getmin(void);
char _CType getsec(void);
char _CType getmsec(void);

WORD _CType dostime(void);
WORD _CType dosdate(void);

/* [dd.mm.yy|yyyy] | [mm/dd/yy|yyyy] */
WORD _CType strtodw(char *__date);
WORD _CType strtotw(char *__hh_mm_ss);

char *_CType dwtostr(char *, WORD __dw);  /* 'dd.mm.yy'	  */
char *_CType dwtolstr(char *, WORD __dw); /* 'dd.mm.yyyy' */
char *_CType twtostr(char *, WORD __tw);  /* 'hh:mm:ss'	  */

#ifdef __cplusplus
 }
#endif
#endif
