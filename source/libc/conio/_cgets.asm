; _CGETS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

    assume rbx:string_t

_cgets proc uses rbx string:LPSTR

   .new len:byte = 0
   .new maxlen:byte

    ldr rbx,string
    .if ( rbx == NULL )
        .return( NULL )
    .endif

    mov al,[rbx]
    mov maxlen,al
    lea rbx,[rbx+2]
    dec maxlen

    .while ( len < maxlen )

        _getch()

        movzx ecx,len
        .switch
        .case al == 8 ; '\b'
            .ifs ( len > 0 )
                _cputs( "\b \b" ) ; go back, clear char on screen with space
                dec len
                mov [rbx+rcx-1],0
            .endif
            .endc
ifdef __UNIX__
        .case al == 10 ; '\n'
else
        .case al == 13 ; '\r'
endif
            mov [rbx+rcx],0
           .break
        .case al == 0
            mov [rbx+rcx],0
            _ungetch(0)
           .break
        .default
            mov [rbx+rcx],al
            inc len
            _putch( eax )
        .endsw
    .endw

    movzx ecx,maxlen
    mov [rbx+rcx],0
    mov rax,rbx
    mov cl,len
    mov [rax-1],cl
    ret

_cgets endp

    end
