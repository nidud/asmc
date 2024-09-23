ifndef _INC_DOS
define _INC_DOS

include crtdefs.inc

.pragma pack(push, _CRT_PACKING)

ifndef _DISKFREE_T_DEFINED
define _DISKFREE_T_DEFINED
_diskfree_t             struct
total_clusters          dd ?
avail_clusters          dd ?
sectors_per_cluster     dd ?
bytes_per_sector        dd ?
_diskfree_t             ends
endif

define _A_NORMAL    0x00
define _A_RDONLY    0x01
define _A_HIDDEN    0x02
define _A_SYSTEM    0x04
define _A_SUBDIR    0x10
define _A_ARCH      0x20

ifdef _CRT_USE_WINAPI_FAMILY_DESKTOP_APP

ifndef _GETDISKFREE_DEFINED
define _GETDISKFREE_DEFINED
_getdiskfree proto __cdecl :uint_t, :ptr _diskfree_t
endif
endif

ifdef _M_IX86
_disable proto fastcall {
    cli
    }
_enable proto fastcall {
    sti
    }
endif

if (__STDC__ eq 0)
diskfree_t  equ _diskfree_t
endif

.pragma pack(pop)

endif
