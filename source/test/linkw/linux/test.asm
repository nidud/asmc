
    .386
    .model flat
    .code

main proc

    mov ecx, offset @CStr( "Hello world!\n" )
    mov edx, sizeof @CStr( "Hello world!\n" )
    mov ebx, 0x0001 ; stdout
    mov eax, 0x0004 ; write()
    int 0x80
    mov eax, 0x0001 ; exit()
    int 0x80

main endp

    end
