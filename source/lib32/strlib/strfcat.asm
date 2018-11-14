; STRFCAT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include strlib.inc

    .code

strfcat proc uses esi edi ecx edx buffer:LPSTR, path:LPSTR, file:LPSTR

    mov edx,buffer
    mov esi,path
    xor eax,eax
    lea ecx,[eax-1]

    .if esi
        mov edi,esi ; overwrite buffer
        repne scasb
        mov edi,edx
        not ecx
        rep movsb
    .else
        mov edi,edx ; length of buffer
        repne scasb
    .endif

    dec edi
    .if edi != edx      ; add slash if missing

        mov al,[edi-1]
        .if !( al == '\' || al == '/' )

            mov al,'\'
            stosb
        .endif
    .endif

    mov esi,file        ; add file name
    .repeat
        lodsb
        stosb
    .until !eax

    mov eax,edx
    ret
strfcat endp

    END
