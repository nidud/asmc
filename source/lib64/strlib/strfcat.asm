; STRFCAT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

    .code

strfcat::

    mov rax,rcx

    .if rdx
        .for ( : byte ptr [rdx] : r9b=[rdx], [rcx]=r9b, rdx++, rcx++ )

        .endf
    .else
        .for ( : byte ptr [rcx] : rcx++ )

        .endf
    .endif

    lea rdx,[rcx-1]
    .if rdx > rax

        mov dl,[rdx]

        .if !( dl == '\' || dl == '/' )

            mov dl,'\'
            mov [rcx],dl
            inc rcx
        .endif
    .endif

    .for ( dl=[r8] : dl : [rcx]=dl, r8++, rcx++, dl=[r8] )

    .endf
    mov [rcx],dl
    ret

    end
