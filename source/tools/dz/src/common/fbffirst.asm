include wsub.inc

    .code

fbffirst proc fcb:PVOID, count

    xor edx,edx
    xor eax,eax
    .while edx < count

        mov eax,fcb
        mov eax,[eax+edx*4]
        mov ecx,[eax].S_FBLK.fb_flag
        .break  .if ecx & _FB_SELECTED
        inc edx
        xor eax,eax
    .endw
    ret

fbffirst endp

    END
