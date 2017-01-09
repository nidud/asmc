include wsub.inc

	.code

fbffirst PROC fcb:PVOID, count

	xor	edx,edx
	.while	edx < count

		mov	eax,fcb
		mov	eax,[eax+edx*4]
		mov	ecx,[eax].S_FBLK.fb_flag
		.break	.if ecx & _FB_SELECTED
		inc	edx
		xor	eax,eax
	.endw
	ret

fbffirst ENDP

	END
