; _GETDRIVE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc
include winbase.inc

    .code

_getdrive proc

  local directory[1024]:char_t

    .if GetCurrentDirectoryA( 1024, &directory )

        mov ax,word ptr directory
        .if ( ah == ':' )

            movzx eax,al
            or    al,0x20
            sub   al,'a' - 1 ; A: == 1
        .else
            xor eax,eax
        .endif
    .else
        _dosmaperr( GetLastError() )
    .endif
    ret

_getdrive endp

    end
