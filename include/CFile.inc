; CFILE.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
ifndef __CFILE_INC
__CFILE_INC equ <>

include io.inc
include stdint.inc
include twindow.inc
include iconfig.inc

_A_MASK         equ 0x0000FFFF
_A_SELECTED     equ 0x00010000
_A_ROOTDIR      equ 0x00020000
_A_UPDIR        equ 0x00040000
_A_CDROOM       equ 0x00080000
_A_ARCHZIP      equ 0x00100000
_A_ARCHEXT      equ 0x00200000
_A_ZENCRYPTED   equ 0x00400000 ; if _A_ARCHZIP
_A_ZEXTLOCHD    equ 0x00800000 ; if _A_ARCHZIP
_A_ARCHIVE      equ _A_ARCHEXT or _A_ARCHZIP

.class CFile

    flag        uint32_t ?
    time        uint32_t ? ; date:time
    size        uint64_t ?
    name        string_t ?

    Release     proc
    Invert      proc
    Select      proc
    Color       proc :window_t, :config_t

    .ends
    cfile_t     typedef ptr CFile

endif
