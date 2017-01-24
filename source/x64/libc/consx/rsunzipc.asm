include consx.inc
include alloc.inc

	.code

	OPTION	WIN64:0, STACKBASE:rsp

rsunzipch PROC USES rbx
	.repeat
		lodsb
		mov	dl,al
		and	dl,0F0h
		.if	dl == 0F0h
			mov	ah,al
			lodsb
			and	eax,0FFFh
			mov	ebx,eax
			lodsb
			.repeat
				stosb
				inc	rdi
				dec	ebx
				.break .if ZERO?
			.untilcxz
			.break .if !ecx
		.else
			stosb
			inc	rdi
		.endif
	.untilcxz
	ret
rsunzipch ENDP

	END
