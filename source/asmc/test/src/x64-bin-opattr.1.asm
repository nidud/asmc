
;--- 64-bit opattr specifics

	.data

	dw opattr [rsp]
	dw opattr [rbp]
	dw opattr [esp]
	dw opattr [ebp]
	dw opattr [sp]
	dw opattr [bp]	;ml64 returns 0, jwasm returns 62h

END
