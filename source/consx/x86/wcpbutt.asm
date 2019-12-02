; WCPBUTT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc

    .code

wcpbutt proc uses esi edi ebx wp:PVOID, l, x, string:LPSTR

    mov ecx,x
    mov ah,at_background[B_PushButt]
    or  ah,at_foreground[F_Title]
    mov al,' '
    mov edi,wp
    mov ebx,edi
    mov edx,edi
    rep stosw

    mov eax,[edi]
    mov al,'Ü'
    and ah,11110000B
    or  ah,at_foreground[F_PBShade]
    stosw

    add edx,l
    add edx,l
    add edx,2
    mov edi,edx
    mov ecx,x
    mov al,'ß'
    rep stosw

    mov esi,string
    mov edi,ebx
    add edi,4

    mov ah,at_background[B_PushButt]
    or  ah,at_foreground[F_TitleKey]

    .while 1

        lodsb
        .break .if !al

        .if al != '&'

            stosb
            inc edi
            .continue(0)
        .else
            lodsb
            .break .if !al
            stosw
        .endif
    .endw

    mov eax,wp
    ret

wcpbutt endp

    END
