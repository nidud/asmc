include conio.inc

.code

_cgets proc uses esi edi ebx string:LPSTR

    mov eax,string

    .repeat

        .break .if !eax

        xor esi,esi                 ; len
        movzx ebx,byte ptr [eax]    ; maxlen
        lea edi,[eax+2]

        dec ebx
        .while esi < ebx

            _getch()

            .if al == 8             ; '\b'

                .ifs esi > 0

                    _cputs("\b \b") ; go back, clear char on screen with space
                    dec esi
                    mov byte ptr [edi+esi],0
                .endif

            .elseif al == 13        ; '\r'

                mov byte ptr [edi+esi],0
                .break

            .elseif !al

                mov byte ptr [edi+esi],0
                _ungetch(0)
                .break

            .else

                _putch(eax)
                mov [edi+esi],al
                inc esi
            .endif
        .endw

        mov byte ptr [edi+ebx],0
        mov eax,edi
        mov ecx,esi
        mov [eax+1],cl
    .until 1
    ret

_cgets endp

    end
