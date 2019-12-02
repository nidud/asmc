; __WPUTS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc

    .code

__wputs proc

    push esi
    push edi
    push ebx
    mov  ebx,edi

    .if !cl
        dec cl
    .endif

    .while 1

        lodsb
        .switch al
          .case 0
            .break
          .case 10
            add ebx,edx
            mov edi,ebx
            .continue
          .case 9
            add edi,8
            .continue
          .case '&'
            .if ch
                mov [edi+1],ch
                .continue
            .endif
            stosb
            inc edi
            .endc
          .default
            .if ah
                stosw
            .else
                stosb
                inc edi
            .endif
            .endc
        .endsw
        dec cl
        .break .ifz
    .endw
    mov eax,esi
    pop ebx
    pop edi
    pop esi
    sub eax,esi
    ret

__wputs endp

    END
