; SYSTEM.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include process.inc
include string.inc
include malloc.inc
include direct.inc
include winbase.inc

    .code

    option win64:nosave

system proc uses rdi rsi rbx r12 r13 string:LPSTR

    local arg0[_MAX_PATH]:BYTE

    mov rdi,rcx
    mov r12,rcx
    mov rbx,alloca(0x8000)
    strcpy(rbx, "cmd.exe")
    .if !GetEnvironmentVariable("Comspec", rbx, 0x8000)
        SearchPath(rax, "cmd.exe", rax, 0x8000, rbx, rax)
    .endif
    strcat(rbx, " /C ")

    mov r13d,' '
    .if BYTE PTR [rdi] == '"'
        inc rdi
        mov r13d,'"'
    .endif
    xor rsi,rsi
    .if strchr(rdi, r13d)
        mov BYTE PTR [rax],0
        mov rsi,rax
    .endif
    strncpy(&arg0, rdi, _MAX_PATH-1)
    .if rsi
        mov [rsi],r13b
        .if r13b == '"'
            inc rsi
        .endif
    .else
        strlen(r12)
        add rax,r12
        mov rsi,rax
    .endif
    mov rdi,rsi
    lea rsi,arg0
    lea r12,@CStr( "\"" )
    .if strchr(rsi, ' ')
        strcat(strcat(strcat(rbx, r12), rsi), r12)
    .else
        strcat(rbx, rsi)
    .endif
    process(0, strcat(rbx, rdi), 0)
    ret

system endp

    END
