include malloc.inc
include string.inc
include wsub.inc

    .code

fballoc proc uses ebx fname:LPSTR, ftime:dword, fsize:qword, flag:dword


    add strlen(fname),SIZE S_FBLK
    .if malloc(eax)

        mov ebx,eax
        add eax,S_FBLK.fb_name
        strcpy(eax, fname)
        mov eax,flag
        mov [ebx].S_FBLK.fb_flag,eax
        mov eax,ftime
        mov [ebx].S_FBLK.fb_time,eax
        mov eax,dword ptr fsize[0]
        mov dword ptr [ebx].S_FBLK.fb_size,eax
        mov eax,dword ptr fsize[4]
        mov dword ptr [ebx].S_FBLK.fb_size[4],eax
        mov eax,ebx
    .endif
    ret

fballoc endp

    END
