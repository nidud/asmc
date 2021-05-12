
;--- check direct memorory references fit in 64-bit
ifndef __ASMC64__
	.x64
	.model flat
endif
	.code

	mov rax,flat:[123456789ABCDEF01h]
    end

