include string.inc
include winbase.inc

.code

main proc argc:SINT, argv:ptr

local lpNumberOfBytesWritten, hStdOut

    mov esi,argv
    mov edi,argc
    mov hStdOut,GetStdHandle(STD_OUTPUT_HANDLE)

    .while edi
        lodsd
        mov ebx,eax
        mov edx,strlen(ebx)
        WriteFile(hStdOut, ebx, edx, addr lpNumberOfBytesWritten, 0)
        WriteFile(hStdOut, "\r\n", 2,addr lpNumberOfBytesWritten, 0)
        dec edi
    .endw

    xor eax,eax
    ret

main endp

    end
