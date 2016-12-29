#ifndef __INC_FLTINTRN
#define __INC_FLTINTRN
#if !defined(__INC_DEFS)
 #include <defs.h>
#endif

#ifdef __cplusplus
 extern "C" {
#endif

typedef struct _strflt {
	int	sign;
	int	decpt;
	int	flag;
	char *	mantissa;
      } *STRFLT;

STRFLT	_CType _strtoflt(char *);

#ifdef __cplusplus
 }
#endif /* __cplusplus */
#endif /* __INC_FLTINTRN */
