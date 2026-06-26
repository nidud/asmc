
;--- test 64bit specific instructions

.code

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

	end
