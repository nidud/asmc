#ifndef __INC_PROCESS
#define __INC_PROCESS
#if !defined(__INC_DEFS)
 #include <defs.h>
#endif
#ifdef __cplusplus
 extern "C" {
#endif

int _CType spawn(char *__program, char *__command);
int _CType spawnf(char *__program, char *__command, char *__file);

#ifdef __cplusplus
 }
#endif /* __cplusplus */
#endif /* __INC_PROCESS */

