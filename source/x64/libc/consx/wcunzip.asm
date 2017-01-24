include consx.inc

rsunzipch PROTO
rsunzipat PROTO

	.code

	OPTION	WIN64:2, STACKBASE:rsp

wcunzip PROC USES rsi rdi rbx rbp dest:PVOID, src:PVOID, wcount
	mov	rdi,rcx;dest
	mov	rbp,rcx
	inc	rdi
	mov	rsi,rdx;src
	mov	rbx,r8
	mov	eax,r8d;wcount
	and	ebx,07FFh
	and	eax,8000h
	mov	ecx,ebx
	.if	!ZERO?
		call	rsunzipat
	.else
		call	rsunzipch
	.endif
	mov	rdi,rbp
	mov	ecx,ebx
	call	rsunzipch
	ret
wcunzip ENDP

	END
