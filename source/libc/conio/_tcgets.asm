; _TCGETS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include tchar.inc

    .code

    assume rbx:tstring_t

_cgetts proc uses rbx string:tstring_t

   .new len:tchar_t = 0
   .new maxlen:tchar_t

    ldr rbx,string
    .if ( rbx == NULL )
        .return( NULL )
    .endif

    mov maxlen,[rbx]
    lea rbx,[rbx+2*tchar_t]
    dec maxlen

    .while ( len < maxlen )

        _gettch()

        movzx ecx,len
        .switch
        .case eax == 8 ; '\b'
            .ifs ( len > 0 )
                _cputts( "\b \b" ) ; go back, clear char on screen with space
                dec len
                mov [rbx+rcx*tchar_t-tchar_t],0
            .endif
            .endc
ifdef __UNIX__
        .case eax == 10 ; '\n'
else
        .case eax == 13 ; '\r'
endif
            mov [rbx+rcx*tchar_t],0
           .break
        .case eax == 0
            mov [rbx+rcx*tchar_t],0
            _ungetch(0)
           .break
        .default
ifdef _UNICODE
            mov [rbx+rcx*tchar_t],ax
else
            mov [rbx+rcx],al
endif
            inc len
            _puttch( eax )
        .endsw
    .endw

    movzx ecx,maxlen
    mov [rbx+rcx*tchar_t],0
    movzx ecx,len
ifdef _UNICODE
    mov [rbx-tchar_t],cx
else
    mov [rbx-tchar_t],cl
endif
    mov rax,rbx
    ret

_cgetts endp

    end
