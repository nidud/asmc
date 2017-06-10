#ifndef _INC_TYPES
#define _INC_TYPES

#ifndef _TIME_T_DEFINED
typedef long time_t;
#define _TIME_T_DEFINED
#endif

#ifndef _INO_T_DEFINED
typedef unsigned short _ino_t;
#if !__STDC__
typedef unsigned short ino_t;
#endif
#define _INO_T_DEFINED
#endif

#ifndef _DEV_T_DEFINED
typedef unsigned int _dev_t;
#if !__STDC__
typedef unsigned int dev_t;
#endif
#define _DEV_T_DEFINED
#endif

#ifndef _OFF_T_DEFINED
typedef long _off_t;
#if !__STDC__
typedef long off_t;
#endif
#define _OFF_T_DEFINED
#endif

#endif
