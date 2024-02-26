; _TPERROR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include stdio.inc
include string.inc
include syserr.inc
include io.inc
include tchar.inc

    .code

_tperror proc message:LPTSTR

    ldr rcx,message

    .if ( rcx )

ifdef _UNICODE

       .new buffer[512]:char_t

        xor edx,edx
        movzx eax,wchar_t ptr [rcx]

        .while ( eax && edx < 512 )

            mov buffer[rdx],al
            add rcx,2
            add edx,1
            mov al,[rcx]
        .endw
        .if eax
            dec edx
            xor eax,eax
        .endif
        mov buffer[rdx],al
        perror(&buffer)
else
        .if ( byte ptr [rcx] )

            _write( 2, message, strlen( rcx ) )
            _write( 2, ": ", 2 )
        .endif

        mov message,_get_sys_err_msg( _get_errno( 0 ) )
        _write( 2, message, strlen( rax ) )
        _write( 2, "\n", 1 )
endif
    .endif
    ret

_tperror endp

    end
