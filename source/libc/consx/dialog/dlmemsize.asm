include consx.inc

    .code

    option stackbase:esp

dlmemsize proc dobj
    mov edx,dobj
    movzx ecx,[edx].S_DOBJ.dl_count
    mov edx,[edx].S_DOBJ.dl_object
    xor eax,eax
    .while ecx
        add al,[edx].S_TOBJ.to_count
        add edx,sizeof(S_TOBJ)
        dec ecx
    .endw
    mov edx,dobj
    inc ecx
    add cl,[edx].S_DOBJ.dl_count
    add eax,ecx
    shl eax,4
    push eax
    rcmemsize(dword ptr [edx].S_DOBJ.dl_rect, [edx].S_DOBJ.dl_flag)
    pop edx
    add eax,edx
    ret
dlmemsize endp

    END
