ifndef __ICONFIG_INC
__ICONFIG_INC equ <>
include libc.inc

_I_BASE     equ 0x01
_I_SECTION  equ 0x02
_I_ENTRY    equ 0x04
_I_COMMENT  equ 0x08

.classdef IConfig

    flags           UINT ?
    _name           LPSTR ?
    union
      value         LPSTR ?
      _list         LPICONFIG ?
    ends
    _next           LPICONFIG ?
    Compare         proc local :LPSTR, :LPSTR

    Read            proc :LPSTR
    Write           proc :LPSTR
    Find            proc :LPSTR
    Create          proc :LPSTR, :VARARG
    Delete          proc :LPSTR
    GetValue        proc :LPSTR, :LPSTR
    Unlink          proc :LPICONFIG

    .ends

endif
