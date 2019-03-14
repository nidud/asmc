ifndef _INC_DOS
_INC_DOS equ <>

include crtdefs.inc

.pragma pack(push, _CRT_PACKING)

ifndef _DISKFREE_T_DEFINED
_DISKFREE_T_DEFINED equ <>
_diskfree_t             struct
total_clusters          dd ?
avail_clusters          dd ?
sectors_per_cluster     dd ?
bytes_per_sector        dd ?
_diskfree_t             ends
endif

_A_NORMAL               equ 0x00
_A_RDONLY               equ 0x01
_A_HIDDEN               equ 0x02
_A_SYSTEM               equ 0x04
_A_SUBDIR               equ 0x10
_A_ARCH                 equ 0x20

ifdef _CRT_USE_WINAPI_FAMILY_DESKTOP_APP

ifndef _GETDISKFREE_DEFINED
_GETDISKFREE_DEFINED equ <>
_getdiskfree proto __cdecl :uint_t, :ptr _diskfree_t
endif
endif

ifdef _M_IX86
_disable proto __cdecl
_enable  proto __cdecl
endif

if (__STDC__ eq 0)
diskfree_t  equ _diskfree_t
endif

.pragma pack(pop)

endif
