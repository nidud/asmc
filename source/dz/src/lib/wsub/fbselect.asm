include wsub.inc

	.code

fbselect PROC fblk:PTR S_FBLK

	mov eax,fblk
	.if !([eax].S_FBLK.fb_flag & _FB_UPDIR)

		or  [eax].S_FBLK.fb_flag,_FB_SELECTED
	.else

		xor eax,eax
	.endif
	ret

fbselect ENDP

	END
