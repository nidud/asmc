include consx.inc
include winbase.inc

	.code

tinocando PROC
	test console,CON_UBEEP
	jz @F
	Beep(9, 1)
@@:
	mov eax,_TE_CMFAILED ; operation fail (end of line/buffer)
	ret
tinocando ENDP

	END
