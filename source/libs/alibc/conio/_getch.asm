; _GETCH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include conio.inc
include string.inc

define EOF (-1)

.data
 inbuf dq 0
 count dd 0

;
; This is the one character push-back buffer used by _getch(), _getche()
; and _ungetch().
;
chbuf dd EOF

.code

_getch proc

    .if ( chbuf != EOF )

        movzx eax,byte ptr chbuf
        mov chbuf,EOF
       .return
    .endif

    .if ( count == 0 )

        .if ( _coninpfh == -1 )

            .return( EOF )
        .endif

        mov count,read(_coninpfh, &inbuf, 8)

        .if ( eax == 0 )

            .return( EOF )
        .endif
    .endif

    dec count
    mov rcx,inbuf
    movzx eax,cl
    shr rcx,8
    mov inbuf,rcx
    ret

_getch endp


_ungetch proc c:int_t

    ; Fail if the char is EOF or the pushback buffer is non-empty

    .if ( ( edi == EOF ) || ( chbuf != EOF ) )
        .return EOF
    .endif
    mov eax,edi
    mov chbuf,eax
    ret

_ungetch endp


_kbhit proc

    ; Fail if the buffer is empty

    mov eax,count
    .if ( eax )
        mov al,byte ptr inbuf
    .endif
    ret

_kbhit endp

_kbflush proc

    xor     eax,eax     ; return content in RCX
    mov     ecx,count   ; and char count in EAX
    mov     count,eax
    dec     rax
    shl     ecx,3
    shl     rax,cl
    shr     ecx,3
    not     rax
    and     rax,inbuf
    xchg    rax,rcx
    ret

_kbflush endp

    end
