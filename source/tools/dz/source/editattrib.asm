include consx.inc
include string.inc

    .data

externdef   IDD_EditColor:dword

dialog      dd 0
format_X    db "%X",0
Background  db B_Title, B_Panel, B_Panel,B_Panel,B_Panel,B_Dialog,B_Dialog,B_Desktop
            db B_Dialog,B_Dialog,B_Panel,B_Panel,B_Menus,B_Title, B_Dialog,B_Menus
Foreground  db F_Desktop,F_Panel,F_Dialog,F_Menus,F_Dialog,F_Title,F_Panel,F_Dialog
            db F_Title,F_Files,F_Dialog,F_Dialog,F_TextView,F_TextEdit,F_TextView,F_TextEdit

    .code

editattrib proc
    local tmp:S_COLOR
    .if rsopen(IDD_EditColor)
        mov dialog,eax
        memcpy(&tmp, &at_foreground, sizeof(S_COLOR))
        dlshow(dialog)
        putinfo()
        mov edx,dialog
        add edx,16+S_TOBJ.to_proc
        mov eax,editat
        mov ecx,16+16
        .repeat
            mov [edx],eax
            add edx,sizeof(S_TOBJ)
        .untilcxz
        rsevent(IDD_EditColor, dialog)
        dlclose(dialog)
        .if edx
            mov eax,1
        .else
        memcpy(&at_foreground, &tmp, sizeof(S_COLOR))
            xor eax,eax
        .endif
    .endif
    ret
editat:
    push esi
    push edi
    lea edi,at_foreground
    lea esi,[edi+16]
    putinfo()
    dlxcellevent()
    sub edx,edx
    mov ecx,tdialog
    movzx ecx,[ecx].S_DOBJ.dl_index

    .if eax == KEY_MOUSEUP
        mov eax,KEY_UP
    .elseif eax == KEY_MOUSEDN
        mov eax,KEY_DOWN
    .endif
    .if eax == KEY_PGUP
        .if ecx < 16
            .if byte ptr [edi+ecx] < 0Fh
                inc edx
                inc byte ptr [edi+ecx]
            .endif
        .elseif ecx < 30
            .if byte ptr [esi+ecx-16] < 0F0h
                inc edx
                add byte ptr [esi+ecx-16],10h
            .endif
        .elseif ecx < 32
            .if byte ptr [edi+ecx] < 0Fh
                inc edx
                inc byte ptr [edi+ecx]
            .endif
        .endif
    .elseif eax == KEY_PGDN
        .if ecx < 16
            .if byte ptr [edi+ecx]
                inc edx
                dec byte ptr [edi+ecx]
            .endif
        .elseif ecx < 30
            .if byte ptr [esi+ecx-16] >= 10h
                inc edx
                sub byte ptr [esi+ecx-16],10h
            .endif
        .elseif ecx < 32
            .if byte ptr [edi+ecx]
                inc edx
                dec byte ptr [edi+ecx]
            .endif
        .endif
    .endif
    .if edx
        push eax
        rsreload(IDD_EditColor, tdialog)
        putinfo()
        pop eax
    .endif
    pop edi
    pop esi
    retn
putinfo:
    push esi
    push edi
    push ebx
    lea esi,at_foreground
    mov ebx,dialog
    mov ax,[ebx+4+16]
    add ax,[ebx+4]
    add al,2
    mov edx,eax
    mov cl,ah
    xor edi,edi
    .repeat
        movzx eax,byte ptr [esi+edi]
    scputf(edx, ecx, 0, 3, &format_X, eax)
        add dl,5
        movzx eax,Background[edi]
        mov al,[esi+eax+16]
        or  al,[esi+edi]
        scputa(edx, ecx, 13, eax)
        add dl,42
        mov al,[esi+B_Dialog+16]
        or  eax,edi
        scputa(edx, ecx, 1, eax)
        sub dl,47
        inc ecx
        inc edi
    .until edi == 16
    mov ax,[ebx+4+16*17]
    add ax,[ebx+4]
    mov bl,al
    add bl,7
    add al,2
    mov edx,eax
    mov cl,ah
    xor edi,edi
    .repeat
        movzx eax,byte ptr [esi+edi+16]
        shr al,4
    scputf(edx, ecx, 0, 3, &format_X, eax)
        movzx eax,Foreground[edi]
        mov al,[esi+eax]
        or  al,[esi+edi+16]
        scputa(ebx, ecx, 13, eax)
        inc ecx
        inc edi
    .until edi == 14
    movzx eax,byte ptr [esi+edi+16]
    scputf(edx, ecx, 0, 3, &format_X, eax)
    mov al,Foreground[edi]
    mov al,[esi+eax]
    or  al,[esi+B_TextView+16]
    scputa(ebx, ecx, 13, eax)
    inc ecx
    inc edi
    movzx eax,byte ptr [esi+edi+16]
    scputf(edx, ecx, 0, 3, &format_X, eax)
    mov al,Foreground[edi]
    mov al,[esi+eax]
    or  al,[esi+B_TextEdit+16]
    scputa(ebx, ecx, 13, eax)
    sub eax,eax
    pop ebx
    pop edi
    pop esi
    retn
editattrib endp

    END
