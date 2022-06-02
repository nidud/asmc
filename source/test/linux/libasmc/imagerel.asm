
include stdio.inc

extern __ImageBase:size_t

.code

main proc

    mov rsi,__ImageBase
    lea rdx,main
    lea rcx,printf

    printf(
	"module: %p\n"
	"main:   %p\n"
	"printf: %p\n", rsi, rdx, rcx )

   .return(0)

main endp

    end
