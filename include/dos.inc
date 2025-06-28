ifndef _INC_DOS
define _INC_DOS

include libc.inc

.pragma pack(push, size_t)

ifndef _DISKFREE_T_DEFINED
define _DISKFREE_T_DEFINED
_diskfree_t             struct
total_clusters          dd ?
avail_clusters          dd ?
sectors_per_cluster     dd ?
bytes_per_sector        dd ?
_diskfree_t             ends
endif
if (__STDC__ eq 0)
diskfree_t typedef _diskfree_t
endif

externdef _dosversion:word
externdef _dosminor:byte
externdef _dosmajor:byte

externdef _psp:ushort_t
externdef _envseg:ushort_t
externdef _envlen:ushort_t
externdef _envsize:ushort_t
externdef _heaptop:ushort_t
externdef _heapbase:ushort_t
externdef _heapfree:ushort_t
externdef _brklvl:ushort_t
externdef _stklen:uint_t
externdef _ifsmgr:char_t

define _A_NORMAL    0x00
define _A_RDONLY    0x01
define _A_HIDDEN    0x02
define _A_SYSTEM    0x04
define _A_SUBDIR    0x10
define _A_ARCH      0x20

ifndef _GETDISKFREE_DEFINED
define _GETDISKFREE_DEFINED
_getdiskfree proto __cdecl :uint_t, :ptr _diskfree_t
endif

ifdef _M_IX86
_disable proto fastcall {
    cli
    }
_enable proto fastcall {
    sti
    }
endif

.pragma pack(pop)

endif
