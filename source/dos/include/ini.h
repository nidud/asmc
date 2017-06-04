#ifndef __INC_INI
#define __INC_INI
#include <defs.h>
#ifdef __cplusplus
 extern "C" {
#endif

char *_CType inientry(char *__section, char *__entry, char *__inifile);
char *_CType inientryid(char *__section, int __entry);

#ifdef __cplusplus
 }
#endif
#endif
