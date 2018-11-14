; WCZIP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc

    .code

wczip proc uses esi edi ebx dest:PVOID, src:PVOID, count, dflag

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
            and ax,0FF0h
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

    mov esi,dest
    mov edi,esi
    add esi,3
    mov ecx,count
    compress()
    mov ecx,count
    compress()
    mov eax,edi
    sub eax,dest
    shr eax,1
    inc eax
    ret

compress:

    .while 1

        lodsb
        mov dl,al
        mov dh,al
        and dh,0xF0
        .if al == [esi]
            mov ebx,0xF001
            jmp @F
        .endif

        .if dh == 0xF0

            mov eax,0x01F0
            stosw
            mov al,dl
        .else

            .repeat
                inc ebx
                lodsb
                .break .if al != [esi]
        @@:
            .untilcxz

            mov eax,ebx
            .if ebx == 0xF002 && dh != 0xF0
                stosb
            .else
                xchg ah,al
                stosw
                mov al,dl
            .endif
        .endif
        stosb
        .break .if !ecx
        dec ecx
        .break .if !ecx
    .endw
    retn

wczip endp

    END
