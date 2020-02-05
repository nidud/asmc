; CMPWARG.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include strlib.inc
include string.inc

    .code

cmpwarg PROC uses esi path:LPSTR, wild:LPSTR

    mov esi,path
    mov ecx,wild
    xor eax,eax

    .while 1

        lodsb
        mov ah,[ecx]
        inc ecx

        .if ah == '*'

            .while 1
                mov ah,[ecx]
                .if !ah
                    mov eax,1
                    .break(1)
                .endif
                inc ecx
                .continue .if ah != '.'
                xor edx,edx
                .while al
                    .if al == ah
                        mov edx,esi
                    .endif
                    lodsb
                .endw
                mov esi,edx
                .continue(1) .if edx
                mov ah,[ecx]
                inc ecx
                .continue .if ah == '*'
                test eax,eax
                mov  ah,0
                setz al
                .break(1)
            .endw

        .endif

        mov edx,eax
        xor eax,eax
        .if !dl
            .break .if edx
            inc eax
            .break
        .endif
        .break .if !dh
        .continue .if dh == '?'
        .if dh == '.'
            .continue .if dl == '.'
            .break
        .endif
        .break .if dl == '.'
        or edx,0x2020
        .break .if dl != dh
    .endw
    test eax,eax
    ret

cmpwarg ENDP

cmpwargs PROC uses edi path:LPSTR, wild:LPSTR
    mov edi,wild
    .repeat
        .if strchr(edi, ' ')
            mov edi,eax
            mov byte ptr [edi],0
            cmpwarg(path, eax)
            mov byte ptr [edi],' '
            inc edi
        .else
            cmpwarg(path, edi)
            .break
        .endif
    .until eax
    ret
cmpwargs ENDP

    END
