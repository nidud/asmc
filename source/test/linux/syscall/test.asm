.code

main proc

    mov rsi,@CStr( "Hello world!\n" )
    mov edx,sizeof(@CStr( "Hello world!\n" ))
    mov edi,0x0001 ; stdout
    mov eax,0x0001 ; write()
    syscall
    mov eax,0x003C ; exit()
    syscall

main endp

    end
