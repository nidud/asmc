include io.inc
include string.inc
include alloc.inc
include consx.inc
include wsub.inc
include winbase.inc

WMAXPATH    equ 2048
ERROR_NO_MORE_FILES equ 18
MAXFINDHANDLES      equ 20

    .data
    _attrib dd MAXFINDHANDLES dup(0)

    .code

wsfindnext proc ff:ptr, handle:HANDLE
    .repeat
        .while FindNextFileA(handle, ff)
            mov ecx,ff
            xor eax,eax
            mov al,[ecx]
            mov ecx,_attrib
            not cl
            and eax,ecx
            .break(1) .ifz
        .endw
        osmaperr()
    .until 1
    ret
wsfindnext endp

wsfindfirst proc uses esi edi ebx fmask:LPSTR, fblk:ptr, attrib:SIZE_T
    ;
    ; @v3.31 - single file fails in FindFirstFileW
    ;
    xor ebx,ebx
    mov eax,fmask
    mov ax,[eax]

ifdef _WIN95
    .if ah == ':' && !(console & CON_WIN95)
else
    .if ah == ':'
endif
        inc ebx
        mov edx,alloca(WMAXPATH + sizeof(WIN32_FIND_DATAW))
        mov edi,eax
        mov ecx,esi
        mov esi,fmask
        mov eax,'\'
        stosw
        stosw
        mov al,'?'
        stosw
        mov al,'\'
        stosw
        .repeat
            lodsb
            stosw
        .until !al
        lea esi,[edx+WMAXPATH]
        mov [esi].WIN32_FIND_DATAW.cFileName,ax
        mov [esi].WIN32_FIND_DATAW.cAlternateFileName,ax
        FindFirstFileW(edx, esi)
    .else
        FindFirstFileA(fmask, fblk)
    .endif

    .if eax != -1
        push eax
        .if ebx
            mov edi,fblk
            mov ecx,WIN32_FIND_DATA.cFileName / 4
            rep movsd
            lea ecx,[edi+260]
            lea edx,[esi+520]
            .repeat
                lodsw
                stosb
            .until !al
            mov edi,ecx
            mov esi,edx
            .repeat
                lodsw
                stosb
            .until !al
        .endif
        mov ecx,fblk
        memmove(&_attrib + 4, &_attrib, 4 * (MAXFINDHANDLES - 1))
        mov eax,attrib
        mov _attrib,eax
        pop eax
    .else
        osmaperr()
    .endif
    mov esp,ebp
    ret
wsfindfirst endp

wscloseff proc handle:HANDLE
    memcpy(&_attrib, &_attrib + 4, 4 * (MAXFINDHANDLES - 1))
    .if FindClose(handle)
        xor eax,eax
    .else
        osmaperr()
    .endif
    ret
wscloseff endp

    END
