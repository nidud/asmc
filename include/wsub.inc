; WSUB.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
ifndef __WSUB_INC
define __WSUB_INC

include io.inc
ifdef __UNIX__
include sys/stat.inc
endif

define WMAXPATH     2048    ; the max length is 0x8000

define _W_MALLOC    0x0001  ; malloc(WSUB+WMAXPATH)
define _W_SORTNAME  0x0010
define _W_SORTTYPE  0x0020
define _W_SORTDATE  0x0040
define _W_SORTSIZE  0x0080
define _W_SORTSUB   0x0100

ifdef __UNIX__
define _F_SUBDIR    _S_IFDIR
else
define _F_SUBDIR    _A_SUBDIR
endif

.template FBLKW
    attr        uint_t ?
    time        uint_t ?
    size        uint64_t ?
    name        wstring_t ?
    nbuf        wchar_t 1 dup(?)
   .ends
    PFBLKW      typedef ptr FBLKW

.template FBLKA
    attr        uint_t ?
    time        uint_t ?
    size        uint64_t ?
    name        string_t ?
    nbuf        char_t 1 dup(?)
   .ends
    PFBLKA      typedef ptr FBLKA

.template WSUBW
    flags       uint_t ?
    count       uint_t ?
    path        wstring_t ?
    mask        wstring_t ?
    fcb         PFBLKW ?
   .ends
    PWSUBW      typedef ptr WSUBW

.template WSUBA
    flags       uint_t ?
    count       uint_t ?
    path        string_t ?
    mask        string_t ?
    fcb         PFBLKA ?
   .ends
    PWSUBA      typedef ptr WSUBA

ifdef _UNICODE
FBLK typedef FBLKW
WSUB typedef WSUBW
else
FBLK typedef FBLKA
WSUB typedef WSUBA
endif
PFBLK typedef ptr FBLK
PWSUB typedef ptr WSUB

_wsnewW         proto __cdecl
_wsnewA         proto __cdecl
_wsopenW        proto __cdecl :PWSUBW
_wsopenA        proto __cdecl :PWSUBA
_wsreadW        proto __cdecl :PWSUBW
_wsreadA        proto __cdecl :PWSUBA
_wssortW        proto __cdecl :PWSUBW
_wssortA        proto __cdecl :PWSUBA
_wspathW        proto __cdecl :PWSUBW, :LPWSTR
_wspathA        proto __cdecl :PWSUBA, :LPSTR

_wsmask         proto __cdecl :PWSUB, :LPTSTR
_wsflag         proto __cdecl :PWSUB, :UINT
_wsfree         proto __cdecl :PWSUB
_wsclose        proto __cdecl :PWSUB

ifdef _UNICODE
define _wsnew   <_wsnewW>
define _twsopen <_wsopenW>
define _wsread  <_wsreadW>
define _wssort  <_wssortW>
define _wspath  <_wspathW>
else
define _wsnew   <_wsnewA>
define _twsopen <_wsopenA>
define _wsread  <_wsreadA>
define _wssort  <_wssortA>
define _wspath  <_wspathA>
endif

endif
