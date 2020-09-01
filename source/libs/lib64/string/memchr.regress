include string.inc
include stdio.inc
include malloc.inc
include winbase.inc

    .data

s0  db 0
s1  db "xxxxxxxxxxxxxxxxabcxxxx",0
s2  db "xxxxxxxxxxxxxxaabcdxxx",0
s3  db "xxxxxxxxxxxxx  abc",0
s4  db "xxxxxxxxxxx..a.abc",0

table label qword
    dq  1,'x',s0,0
    dq  1, 0 ,s0,s0
    dq 24, 0 ,s1,s1+23
    dq 24,'x',s1,s1
    dq 24,'a',s1,s1+16
    dq 24,'b',s1,s1+17
    dq 24,'c',s1,s1+18
    dq 23,'d',s2,s2+18
    dq 19,' ',s3,s3+13
    dq 19,'.',s4,s4+11
    dq 0

nerror dq 0

    .code

overlapped proc uses rsi rdi rbx r12

    .if VirtualAlloc(0, 4096, MEM_COMMIT, PAGE_READWRITE)

        mov r12,rax
        mov rbx,rax
        mov rdi,rax
        mov rcx,4096
        mov rax,'x'
        rep stosb
        mov rdi,4096
        mov byte ptr [rbx+4096-1],0
        lea rax,[rbx+15]
        memchr(rbx, 'y', 4096)
        memchr(rbx, 'x', 4096)
        memchr(rbx, 0, 4096)
        .repeat
            dec rdi
            inc rbx
            memchr(rbx, 0, rdi)
        .until rdi == 4096 - 33
        VirtualFree(r12, 0, MEM_RELEASE)
    .endif
    ret

overlapped endp

regress proc uses rsi rdi rbx

    xor rdi,rdi
    lea rsi,table

    .repeat
        mov rcx,[rsi+16]
        mov rdx,[rsi+8]
        mov r8,[rsi]
        memchr(rcx, edx, r8)
        mov rdx,rax
        mov rcx,[rsi]
        mov rbx,[rsi+16]
        mov rax,[rsi+24]
        add rsi,32
        .if rax != rdx
            mov rsi,[rsi-24]
            printf("\n\ntable %d: eax = %X (%X) memchr(%s, %c, %d)\n",
                rdi, rdx, rax, rbx, rsi, rcx)
            inc nerror
            mov rax,-1
            .break
        .endif
        inc rdi
        mov rax,[rsi]
    .until !rax
    mov rax,nerror
    ret

regress endp

main proc

    .ifd !regress()
        overlapped()
    .endif

    mov rax,nerror
    ret

main endp

    END
