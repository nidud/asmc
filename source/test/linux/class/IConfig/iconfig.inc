ifndef __ICONFIG_INC
define __ICONFIG_INC
include libc.inc

define _I_BASE     0x01
define _I_SECTION  0x02
define _I_ENTRY    0x04
define _I_COMMENT  0x08

.class IConfig

    flags           UINT ?
    _name           LPSTR ?
    union
      value         LPSTR ?
      _list         ptr IConfig ?
    ends
    _next           ptr IConfig ?
    Compare         proc local :LPSTR, :LPSTR

    IConfig         proc
    Release         proc
    Read            proc :LPSTR
    Write           proc :LPSTR
    Find            proc :LPSTR
    Create          proc :LPSTR, :VARARG
    Delete          proc :LPSTR
    GetValue        proc :LPSTR, :LPSTR
    Unlink          proc :ptr IConfig
   .ends

endif
