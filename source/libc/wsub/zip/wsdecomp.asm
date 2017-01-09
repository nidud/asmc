include wsub.inc
include errno.inc

	.code

wsdecomp PROC wsub, fblk, out_path
	mov	eax,fblk
	test	[eax].S_FBLK.fb_flag,_FB_ARCHIVE
	jz	error
	wzipcopy( wsub, fblk, out_path )
toend:
	ret
error:
	call	notsup
	mov	eax,-1
	jmp	toend
wsdecomp ENDP

	END
