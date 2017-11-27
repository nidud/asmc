include io.inc
include errno.inc
include malloc.inc
include winbase.inc
ifdef _WIN95
include conio.inc
endif

WMAXPATH equ 2048

    .code

    option cstack:on

_osopenA proc USES esi edi ebx lpFileName:LPSTR, dwAccess:SIZE_T, dwShareMode:SIZE_T,
    lpSecurity:PVOID, dwCreation:SIZE_T, dwAttributes:SIZE_T

    xor eax,eax
    .while _osfile[eax] & FH_OPEN
        inc eax
        .if eax == _nfile
            xor eax,eax
            mov oserrno,eax ; no OS error
            mov errno,EBADF
            dec eax
            jmp toend
        .endif
    .endw
    mov ebx,eax

    CreateFileA(lpFileName, dwAccess, dwShareMode, lpSecurity, dwCreation, dwAttributes, 0)
    mov edx,eax
    inc eax
    jz  error
done:
    mov eax,ebx
    mov _osfhnd[eax*4],edx
    or  _osfile[eax],FH_OPEN
toend:
    ret
error:
    osmaperr()

 ifdef  _WIN95
    test console,CON_WIN95
    jnz toend
 endif
    cmp edx,ERROR_FILENAME_EXCED_RANGE
    jne toend
    alloca(WMAXPATH)
    mov edx,eax
    mov edi,eax
    mov esi,lpFileName
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
    .until  !al
    CreateFileW(edx, dwAccess, dwShareMode, lpSecurity, dwCreation, dwAttributes, 0)
    mov esp,ebp
    mov edx,eax
    inc eax
    jnz done
    osmaperr()
    jmp toend
_osopenA ENDP

    END
