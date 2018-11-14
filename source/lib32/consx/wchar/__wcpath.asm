; __WCPATH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc
include string.inc

    .code

__wcpath proc uses ebx b:PVOID, l:dword, p:LPSTR

    mov ecx,strlen( p )
    mov edx,p
    mov eax,b

    .repeat

        .break .if ecx <= l

        mov ebx,[edx]
        add edx,ecx
        mov ecx,l
        sub edx,ecx
        add edx,4
        .if bh == ':'
            mov [eax],bl
            mov [eax+2],bh
            shr ebx,8
            mov bl,'.'
            add eax,4
            add edx,2
            sub ecx,2
        .else
            mov bx,'/.'
        .endif

        mov [eax],bh
        mov [eax+2],bl
        mov [eax+4],bl
        mov [eax+6],bh
        add eax,8
        sub ecx,4
    .until 1
    ret

__wcpath endp

    END
