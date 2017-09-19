include consx.inc

    .data

frametypes label byte
    db 'ÚÄ¿³ÀÙ'
    db 'ÉÍ»ºÈ¼'
    db 'ÂÄÂ³ÁÁ'
    db 'ÃÄ´³Ã´'

    .code

rcframe proc uses esi edi ebx ecx edx rc, wstr:PVOID, lsize, ftype

  local tmp[16]:byte

    mov eax,ftype       ; AL = Type [0,6,12,18]
    and eax,00FFh       ; AH = Attrib
    add eax,offset frametypes
    mov esi,eax     ;------------------------
    lodsw           ; [BP-2] UL 'Ú'
    mov [ebp-2],ax  ; [BP-1] HL 'Ä'
    lodsw           ; [BP-4] UR '¿'
    mov [ebp-4],ax  ; [BP-3] VL '³'
    lodsw           ; [BP-6] LL 'À'
    mov [ebp-6],ax  ; [BP-5] LR 'Ù'
    mov eax,lsize   ;------------------------
    mov ecx,eax     ; line size - 80 on screen
    add eax,eax
    movzx edx,rc.S_RECT.rc_y
    mul edx
    movzx edx,rc.S_RECT.rc_x
    add eax,edx
    add eax,edx
    mov edi,wstr
    add edi,eax
    movzx eax,rc.S_RECT.rc_col
    sub al,2
    mov ch,al
    add eax,eax
    mov [ebp-10],eax
    mov eax,ftype
    mov dl,rc.S_RECT.rc_row
    mov esi,edx
    mov dl,cl
    add edx,edx
    mov ebx,edi
    mov cl,1

    mov al,[ebp-2]  ; Upper Left 'Ú'
    rcstosw()
    mov al,[ebp-1]  ; Horizontal Line 'Ä'
    mov cl,ch
    rcstosw()
    inc cl
    mov al,[ebp-4]  ; Upper Right '¿'
    rcstosw()

    .if esi > 1
        .if esi != 2
            sub esi,2
            .repeat
                add ebx,edx
                mov edi,ebx
                inc cl
                mov al,[ebp-3] ; Vertical Line '³'
                rcstosw()
                add edi,[ebp-10]
                inc cl
                rcstosw()
                dec esi
            .until !esi
        .endif
        add ebx,edx
        mov edi,ebx
        mov cl,1
        mov al,[ebp-6] ; Lower Left 'À'
        rcstosw()
        mov al,[ebp-1] ; Horizontal Line 'Ä'
        mov cl,ch
        rcstosw()
        inc cl
        mov al,[ebp-5] ; Lower Right 'Ù'
        rcstosw()
    .endif
    ret

rcstosw:
    .repeat
        .if ah
            stosw
        .else
            stosb
            inc edi
        .endif
        dec cl
    .untilz
    retn

rcframe endp

    END
