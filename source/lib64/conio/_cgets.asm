; _CGETS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

.code

_cgets proc uses rsi rdi rbx string:LPSTR

    .return .if !rcx

    xor   esi,esi               ; len
    movzx ebx,byte ptr [rcx]    ; maxlen
    lea   rdi,[rcx+2]
    dec   ebx

    .while esi < ebx

        _getch()

        .if al == 8             ; '\b'

            .ifs esi > 0

                _cputs("\b \b") ; go back, clear char on screen with space
                dec esi
                mov byte ptr [rdi+rsi],0
            .endif

        .elseif al == 13        ; '\r'

            mov byte ptr [rdi+rsi],0
            .break

        .elseif !al

            mov byte ptr [rdi+rsi],0
            _ungetch(0)
            .break

        .else

            mov [rdi+rsi],al
            inc esi
            _putch(eax)
        .endif
    .endw

    mov byte ptr [rdi+rbx],0
    mov rax,rdi
    mov ecx,esi
    mov [rax-1],cl
    ret

_cgets endp

    end
