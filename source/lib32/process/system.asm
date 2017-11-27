include stdlib.inc
include process.inc
include string.inc
include malloc.inc
include direct.inc
include winbase.inc

MAXCMDL equ 0x8000

    .data
    cp_quote db '"',0

    .code

    option cstack:on

system proc uses edi esi ebx string:LPSTR

local arg0[_MAX_PATH]:sbyte

    mov ebx,alloca(MAXCMDL)
    strcpy(ebx, "cmd.exe")
    .if !GetEnvironmentVariable("Comspec", ebx, MAXCMDL)
        SearchPath(eax, "cmd.exe", eax, MAXCMDL, ebx, eax)
    .endif
    strcat(ebx, " /C ")

    mov edi,string
    mov edx,' '
    .if byte ptr [edi] == '"'
        inc edi
        mov edx,'"'
    .endif
    xor esi,esi
    .if strchr( edi, edx )
        mov byte ptr [eax],0
        mov esi,eax
    .endif
    strncpy( addr arg0, edi, _MAX_PATH-1 )
    .if esi
        mov [esi],dl
        .if dl == '"'
        inc esi
        .endif
    .else
        strlen(string)
        add eax,string
        mov esi,eax
    .endif
    mov edi,esi
    lea esi,arg0
    lea edx,cp_quote
    .if strchr(esi, ' ')
        strcat(strcat(strcat(ebx, edx), esi), edx)
    .else
        strcat(ebx, esi)
    .endif
    process(0, strcat(ebx, edi), 0)
    ret

system endp

    END
