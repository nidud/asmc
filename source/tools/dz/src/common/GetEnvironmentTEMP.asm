include stdlib.inc
include malloc.inc
include string.inc
include crtl.inc
include winbase.inc
include dzlib.inc

PUBLIC  cp_temp
PUBLIC  envtemp
EXTERN  _pgmpath:dword

    .data
    envtemp dd 0
    cp_temp db "TEMP",0

    .code

GetEnvironmentTEMP proc
    free(envtemp)
    getenvp(&cp_temp)
    mov envtemp,eax
    .if !eax
        mov eax,_pgmpath
        .if eax
            mov envtemp,_strdup(eax)
            SetEnvironmentVariable(&cp_temp, eax)
            mov eax,envtemp
        .endif
    .endif
    ret
GetEnvironmentTEMP endp

pragma_init GetEnvironmentTEMP, 102

    END
