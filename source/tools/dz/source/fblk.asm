include malloc.inc
include string.inc
include io.inc
include time.inc
include wsub.inc
include winbase.inc
include strlib.inc
include cfini.inc
include crtl.inc

    .code

fballoc proc uses ebx fname:LPSTR, ftime:dword, fsize:qword, flag:dword

    .if malloc(&[strlen(fname)+S_FBLK])

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

    assume  ebx: ptr WIN32_FIND_DATA

fballocwf proc uses esi ebx wfblk:PVOID, flag

    mov ebx,wfblk
    mov ecx,[ebx]
    lea eax,[ebx].ftLastWriteTime

    .if cl & _A_SUBDIR

        lea eax,[ebx].ftCreationTime
    .endif

    __FTToTime(eax)
    and ecx,_A_FATTRIB
    or  ecx,flag
    lea edx,[ebx].cFileName
    mov esi,[ebx].nFileSizeHigh
    mov ebx,[ebx].nFileSizeLow

    .if fballoc(edx, eax, esi::ebx, ecx)

        .if cl & _A_SUBDIR && \
            word ptr [eax].S_FBLK.fb_name == '..' && \
            byte ptr [eax].S_FBLK.fb_name[2] == 0

            or [eax].S_FBLK.fb_flag,_FB_UPDIR
        .endif
    .endif
    ret

fballocwf endp

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

fbinvert proc fblk:ptr S_FBLK

    mov eax,fblk
    .if ![eax].S_FBLK.fb_flag & _FB_UPDIR

        xor [eax].S_FBLK.fb_flag,_FB_SELECTED
    .else

        xor eax,eax
    .endif
    ret

fbinvert endp

fbselect proc fblk:ptr S_FBLK

    mov eax,fblk
    .if !([eax].S_FBLK.fb_flag & _FB_UPDIR)

        or  [eax].S_FBLK.fb_flag,_FB_SELECTED
    .else

        xor eax,eax
    .endif
    ret

fbselect endp

fbupdir proc flag

    clock()
    mov ecx,flag
    or  ecx,_FB_UPDIR or _A_SUBDIR
    fballoc(addr cp_dotdot, eax, 0, ecx)
    ret

fbupdir endp

fbcolor proc uses esi edi edx ecx fp:ptr S_FBLK

    mov esi,fp

    .while  1

        .if !([esi].S_FBLK.fb_flag & _A_SUBDIR)

            lea edi,[esi].S_FBLK.fb_name
            .if strext(edi)

                lea edi,[eax+1]
            .endif

            .if CFGetSection("FileColor")

                .if INIGetEntry(eax, edi)

                    .if strtolx(eax) <= 15

                        shl eax,4
                        .if al != at_background[B_Panel]

                            shr eax,4
                            .break
                        .endif
                    .endif
                .endif
            .endif
        .endif

        mov eax,[esi].S_FBLK.fb_flag
        .switch
          .case eax & _FB_SELECTED
            mov al,at_foreground[F_Panel]
            .break
          .case eax & _FB_UPDIR
            mov al,7
            .break
          .case eax & _FB_ROOTDIR
          .case eax & _A_SYSTEM
            mov al,at_foreground[F_System]
            .break
          .case eax & _A_HIDDEN
            mov al,at_foreground[F_Hidden]
            .break
          .case eax & _A_SUBDIR
            mov al,at_foreground[F_Subdir]
            .break
          .default
            mov al,at_foreground[F_Files]
            .break
        .endsw
    .endw
    or  al,at_background[B_Panel]
    movzx   eax,al
    ret

fbcolor endp

    END
