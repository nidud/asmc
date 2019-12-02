; WCZIP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc


    .code

wczip proc uses esi edi ebx dest:ptr, src:ptr, count, dflag

    mov edx,dflag
    mov ecx,count
    mov edi,dest
    mov esi,src
    add edi,3
    lea ebx,[edi+ecx]

    .repeat

        mov ax,[esi]
        .if !al
            mov al,' '
        .endif
        mov [ebx],al

        mov al,ah
        mov [edi],al

        .if edx & _D_RESAT

            and ax,0x0FF0

            .if edx & _D_MENUS

                mov al,B_Menus shl 4
                .if ah == at_foreground[F_MenusKey]
                    mov ah,F_MenusKey
                .elseif ah != 8
                    mov ah,F_Menus
                .endif

            .elseif al == at_background[B_Dialog]

                .if ah == at_foreground[F_DialogKey]
                    mov ah,F_DialogKey
                .elseif ah == at_foreground[F_Dialog]
                    mov ah,F_Dialog
                .endif

                mov al,[esi]
                .if al == 'Ü' || al == 'ß'
                    mov ah,F_PBShade
                .endif

                mov al,B_Dialog shl 4

            .elseif al == at_background[B_Title]

                mov al,B_Title shl 4
                .if ah == at_foreground[F_TitleKey]
                    mov ah,F_TitleKey
                .elseif ah != 8
                    mov ah,F_Title
                .endif

            .elseif al == at_background[B_PushButt]

                mov al,B_PushButt shl 4
                .if ah == at_foreground[F_TitleKey]
                    mov ah,F_TitleKey
                .elseif ah != 8
                    mov ah,F_Title
                .endif
            .endif

            or  al,ah
            mov [edi],al

        .endif

        inc ebx
        inc edi
        add esi,2

    .untilcxz

    option dotname

    mov esi,dest
    mov edi,esi
    add esi,3
    mov ecx,count

    .compress()

    mov ecx,count

    .compress()

    mov eax,edi
    sub eax,dest
    shr eax,1
    inc eax
    ret

.compress:

    lodsb
    mov     dl,al
    mov     dh,al
    and     dh,0xF0
    cmp     al,[esi]
    jnz     .1
    mov     ebx,0xF001
    jmp     .3
.1:
    cmp     dh,0xF0
    jnz     .7
    mov     eax,0x01F0
    jmp     .6
.2:
    inc     ebx
    lodsb
    cmp     al,[esi]
    jne     .4
.3:
    dec     ecx
    jnz     .2
.4:
    mov     eax,ebx
    cmp     ebx,0xF002
    jnz     .5
    cmp     dh,0xF0
    jz      .5
    mov     al,dl
    stosb
    jmp     .7
.5:
    xchg    ah,al
.6:
    stosw
    mov     al,dl
.7:
    stosb
    test    ecx,ecx
    jz      .8
    dec     ecx
    jnz     .compress
.8:
    retn

wczip endp

    END
