; _GETDRIVE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc
ifndef __UNIX__
include winbase.inc
endif
    .code

_getdrive proc
ifdef __UNIX__
    _set_errno( ENOSYS )
    xor eax,eax
else

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
endif
    ret

_getdrive endp

    end
