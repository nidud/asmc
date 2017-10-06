include stdio.inc
include stdlib.inc
include winternl.inc

.code

main proc
    local SBI:SYSTEM_BASIC_INFORMATION
    local retlen:qword

    xor r10,r10
    mov retlen,r10
    lea r9,retlen
    mov r8,sizeof(SBI)
    lea rdx,SBI
    mov eax,0x33 ; Windows 7=0x0033, Windows 10 until redstone2=0x0036

    syscall

    movzx edx,SBI.NumberOfProcessors
    printf("Number of processors: %d retlen: 0x%x retval: 0x%x\n", edx, retlen, eax)
    exit(0)

main endp

    end main