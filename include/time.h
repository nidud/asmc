#ifndef __INC_TIME
#define __INC_TIME
#if !defined(__INC_DEFS)
 #include <defs.h>
#endif
#ifdef __cplusplus
 extern "C" {
#endif

#ifndef _TM_DEFINED
struct tm {
	int	tm_sec;	    /* seconds after the minute - [0,59] */
	int	tm_min;	    /* minutes after the hour - [0,59] */
	int	tm_hour;    /* hours since midnight - [0,23] */
	int	tm_mday;    /* day of the month - [1,31] */
	int	tm_mon;	    /* months since January - [0,11] */
	int	tm_year;    /* years since 1900 */
	int	tm_wday;    /* days since Sunday - [0,6] */
	int	tm_yday;    /* days since January 1 - [0,365] */
	int	tm_isdst;   /* daylight savings time flag */
      };
#define _TM_DEFINED
#endif

typedef unsigned long clock_t;

_CRTIMP time_t	_CType _time(time_t *);
_CRTIMP struct tm *_CType localtime(const time_t *);
_CRTIMP struct tm *_CType gmtime(const time_t *);
_CRTIMP clock_t _CType clock(void);

#define time	_time

#ifdef __cplusplus
 }
#endif
#endif
