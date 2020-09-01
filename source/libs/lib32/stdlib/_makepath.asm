; _MAKEPATH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include string.inc

.code

_makepath proc __cdecl uses esi edi ebx path:LPSTR, drive:LPSTR, dir:LPSTR, fname:LPSTR, ext:LPSTR

    mov eax,path

    .repeat

        .break .if !eax

        mov edi,eax
        mov esi,drive

        .if (esi && byte ptr [esi])

            movsb
            mov al,':'
            stosb
        .endif

        mov esi,dir
        .if (esi && byte ptr [esi])

            mov ecx,strlen(esi)
            rep movsb

            mov al,[edi-1]
            .if al != '/' && al != '\'

                mov al,'\'
                stosb
            .endif
        .endif

        mov esi,fname
        .if (esi && byte ptr [esi])

            mov ecx,strlen(esi)
            rep movsb
        .endif

        mov esi,ext
        .if (esi && byte ptr [esi])

            mov al,'.'
            .if [esi] != al

                stosb
            .endif
            strcpy(edi, esi)
        .else
            mov byte ptr [edi],0
        .endif

    .until 1
    ret

_makepath endp

    end
