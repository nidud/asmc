include io.inc
include time.inc
include wsub.inc
include winbase.inc

    .code

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

    END
