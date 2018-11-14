; __WARGV.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include crtl.inc
include winbase.inc

.data
__wargv	 dd 0
_wpgmptr dd 0

.code

Install:
    mov __wargv,setwargv( addr __argc, GetCommandLineW() )
    mov eax,[eax]
    mov _wpgmptr,eax
    ret

.pragma(init(Install, 4))

    end
