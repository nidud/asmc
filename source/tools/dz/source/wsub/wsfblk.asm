include wsub.inc

    .code

wsfblk proc wsub:ptr S_WSUB, index
    mov eax,index
    mov edx,wsub
    .ifs [edx].S_WSUB.ws_count <= eax
        xor eax,eax
    .else
        shl eax,2
        add eax,[edx].S_WSUB.ws_fcb     ; EDX wsub
        mov eax,[eax]                   ; EAX fblk
        mov ecx,[eax].S_FBLK.fb_flag    ; ECX fblk.flag
    .endif
    ret
wsfblk endp

    END
