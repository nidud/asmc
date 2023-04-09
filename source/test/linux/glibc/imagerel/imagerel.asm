
include stdio.inc

.code

main proc

    lea rsi,main
    mov rdx,rsi
    mov rax,imagerel main
    sub rsi,rax
    lea rcx,printf

    printf(
	"module: %p\n"
	"main:   %p\n"
	"printf: %p\n", rsi, rdx, rcx )

   .return(0)

main endp

    end
