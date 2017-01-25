;
; v2.22 -- added Signed Compare for .IFS, .IFSB, .IFSW, and .IFSD
;
	.x64
	.model	flat, fastcall
	.code

	proto_t typedef proto :ptr, :ptr
	proto_p typedef ptr proto_t

	.data
	data_p	proto_p 0

	.code

	.ifs	al > dl
		nop
	.endif
	.ifs	ax > dx
		nop
	.endif
	.ifs	eax > edx
		nop
	.endif
	.ifs	rax > rdx
		nop
	.endif

	.ifs	data_p(1,2) > 0
		nop
	.endif
	.ifsb	data_p(1,2) > 0
		nop
	.endif
	.ifsw	data_p(1,2) > 0
		nop
	.endif
	.ifsd	data_p(1,2) > 0
		nop
	.endif

	.while	1
		.break .ifs data_p(1,2) > 0
	.endw
	.while	1
		.continue .ifs data_p(1,2) > 0
		nop
	.endw

	END
