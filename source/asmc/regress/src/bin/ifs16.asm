;
; v2.22 -- added Signed Compare for .IFS, .IFSB, .IFSW, and .IFSD
;
	.186
	.model	small, c
	.code

	proto_t typedef proto :ptr, :ptr
	proto_p typedef ptr proto_t

	.code
	data_p	proto_p 0

	.ifs	ax > dx
		nop
	.endif
	.ifs	data_p(1,2) > 0
		nop
	.endif
	.ifsb	data_p(1,2) > 0
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
