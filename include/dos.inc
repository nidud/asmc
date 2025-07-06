ifndef __LIBC_INC
include libc.inc
endif

ifndef __DOS_INC
define __DOS_INC

ifndef _SIZE_T_DEFINED
define _SIZE_T_DEFINED
size_t  typedef word
ssize_t typedef sword
endif

if @DataSize
define ldsl     <lds>
define lesl     <les>
define esl      <es:>
define movl     <mov>
define pushl    <push>
define popl     <pop>
else
define ldsl     <mov>
define lesl     <mov>
define esl      <>
movl    macro args:vararg
        endm
pushl   macro args:vararg
        endm
popl    macro args:vararg
        endm
endif

ifndef _DISKFREE_T_DEFINED
define _DISKFREE_T_DEFINED
_diskfree_t             struct
total_clusters          dd ?
avail_clusters          dd ?
sectors_per_cluster     dd ?
bytes_per_sector        dd ?
_diskfree_t             ends
diskfree_t typedef _diskfree_t
endif

externdef _dosversion:word
externdef _dosminor:byte
externdef _dosmajor:byte

externdef _psp:word
externdef _envseg:word
externdef _envlen:word
externdef _envsize:word
externdef _heaptop:word
externdef _heapbase:word
externdef _heapfree:word
externdef _brklvl:word
externdef _stklen:word
externdef _ifsmgr:byte

define _A_NORMAL    0x00
define _A_RDONLY    0x01
define _A_HIDDEN    0x02
define _A_SYSTEM    0x04
define _A_VOLID     0x08
define _A_SUBDIR    0x10
define _A_ARCH      0x20

ifndef _GETDISKFREE_DEFINED
define _GETDISKFREE_DEFINED
_getdiskfree proto __cdecl :word, :ptr _diskfree_t
endif

ifdef _M_IX86
_disable proto fastcall {
    cli
    }
_enable proto fastcall {
    sti
    }
endif

_dos_time       proto __cdecl
_dos_date       proto __cdecl
_dos_year       proto __cdecl
_dos_month      proto __cdecl
_dos_day        proto __cdecl
_dos_hour       proto __cdecl
_dos_minute     proto __cdecl
_dos_second     proto __cdecl

option proc:public, language:__Ctype, dotname

endif
