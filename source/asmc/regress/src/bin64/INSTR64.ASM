
;--- test 64bit specific instructions

ifndef __ASMC64__
    .x64
    .model flat
endif

	.code

main proc

	CWDE
	CDQE
	CDQ
	CQO
	IRETQ
	CMPSQ
	LODSQ
	MOVSQ
	SCASQ
	STOSQ
	SWAPGS
	bswap eax
	bswap rax
	ret

main endp

    END
