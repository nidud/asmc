include direct.inc
include string.inc
include errno.inc
include alloc.inc
include winbase.inc

    .code

    option cstack:on

_getdcwd proc uses rsi rdi rbx r12 r13 drive:SINT, buffer:LPSTR, maxlen:SINT
local PathName:QWORD

    lea r13,PathName
    mov ebx,ecx
    mov r12,rdx
    mov rsi,r8
    mov rdi,alloca(r8d)

    .if !ebx
        GetCurrentDirectory( esi, rdi )
    .else
        GetLogicalDrives()
        mov ecx,ebx
        dec ecx
        shr eax,cl
        sbb eax,eax
        and eax,1
        .if ZERO?
            mov oserrno,ERROR_INVALID_DRIVE
            mov errno,EACCES
            jmp toend
        .endif
        mov al,'A' - 1
        add al,bl
        add eax,002E3A00h
        mov [r13],eax
        GetFullPathName( r13, esi, rdi, 0 )
    .endif

    .if rax > rsi

        mov errno,ERANGE
        xor eax,eax
        jmp toend

    .elseif eax

        .if !r12

            malloc(&[rax+1])
            test rax,rax
            mov r12,rax
            jz toend

        .endif

        strcpy(r12, rdi)
    .endif
toend:
    ret
_getdcwd ENDP

    END
