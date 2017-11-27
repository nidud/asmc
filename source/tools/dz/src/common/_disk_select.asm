include direct.inc
include consx.inc
include errno.inc
include dzlib.inc

    .data
    push_button db "&A",0

    .code

_disk_select proc uses esi edi ebx msg:LPSTR

  local dobj:S_DOBJ
  local tobj[MAXDRIVES]:S_TOBJ

    mov ebx,_getdrive()
    _disk_read()
    mov dword ptr dobj.dl_flag,_D_STDDLG
    mov dobj.dl_rect,0x003F0908
    lea edi,tobj
    mov dobj.dl_object,edi
    mov esi,1

    .repeat

        .if _disk_exist(esi)

            movzx eax,dobj.dl_count
            inc dobj.dl_count
            mov [edi].S_TOBJ.to_flag,_O_PBKEY
            mov ecx,eax
            .if esi == ebx

                mov al,dobj.dl_count
                dec al
                mov dobj.dl_index,al
            .endif

            mov eax,esi
            add al,'@'
            mov [edi].S_TOBJ.to_ascii,al
            mov eax,0x01050000
            mov al,cl
            shr al,3
            shl al,1
            add al,2
            mov ah,al
            and cl,7
            mov al,cl
            shl al,3
            sub al,cl
            add al,4
            mov [edi].S_TOBJ.to_rect,eax
            add edi,16
        .endif

        inc esi

    .until esi > MAXDRIVES

    movzx eax,dobj.dl_count
    dec eax
    mov ebx,eax
    shr eax,3
    shl eax,1
    add al,5
    mov dobj.dl_rect.rc_row,al
    mov eax,ebx

    .if eax <= 7
        shl eax,3
        sub eax,ebx
        add eax,14
        mov dobj.dl_rect.rc_col,al
        mov cl,byte ptr _scrcol
        sub cl,al
        shr cl,1
        mov dobj.dl_rect.rc_x,cl
    .endif

    xor edi,edi
    mov bl,at_foreground[F_Dialog]
    or  bl,at_background[B_Dialog]

    .if dlopen(&dobj, ebx, msg)

        lea esi,tobj
        mov bl,[esi].S_TOBJ.to_rect.rc_col

        .while 1

            movzx eax,dobj.dl_count
            .break .if edi >= eax
            mov al,[esi].S_TOBJ.to_ascii
            mov push_button[1],al
            mov al,dobj.dl_rect.rc_col
            rcbprc([esi].S_TOBJ.to_rect, dobj.dl_wp, eax)
            movzx ecx,dobj.dl_rect.rc_col
            wcpbutt(eax, ecx, ebx, &push_button)
            inc edi
            add esi,sizeof(S_TOBJ)
        .endw

        mov edi,dlmodal(&dobj)
    .endif

    xor eax,eax
    .if edi
        or  al,dobj.dl_index
        shl eax,4
        add eax,dobj.dl_object
        movzx eax,[eax].S_TOBJ.to_ascii
        sub al,'@'
    .endif
    ret

_disk_select endp

    END
