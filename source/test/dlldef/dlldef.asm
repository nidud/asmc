include string.inc
include stdio.inc
include stdlib.inc
include winbase.inc
include tchar.inc

    .code

main proc
    mov rsi,rdx
    .if rcx == 2
        mov rdi,[rsi+8]
        .if LoadLibrary(rdi)
            mov r12,rax
            mov rbx,strcpy(strrchr(rdi,'.'),".def")
            .if fopen(rdi,"wt")
                mov r13,rax
                mov byte ptr [rbx],0
                fprintf(r13,"LIBRARY %s\nEXPORTS\n",rdi)
                mov rdi,r12
                add edi,[rdi+0x3C]
                mov edi,[rdi].IMAGE_NT_HEADERS.OptionalHeader.DataDirectory.VirtualAddress
                add rdi,r12
                mov ebx,[rdi+0x18]
                mov esi,[rdi+0x20]
                add rsi,r12
                .while ebx
                    lodsd
                    add rax,r12
                    fprintf(r13,"\"%s\"\n",rax)
                    dec ebx
                .endw
                fclose(r13)
            .endif
            FreeLibrary(r12)
        .endif
    .else
        printf("\nUsage: DLLDEF <dllname>.dll\n\n")
    .endif
    xor eax,eax
    ret
main endp

    end _tstart
