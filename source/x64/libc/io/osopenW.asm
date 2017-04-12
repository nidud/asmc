include io.inc
include winbase.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE, WIN64:1

osopenW PROC fname:LPWSTR, attrib:UINT, mode:UINT, action:UINT
	mov	r11d,edx
	mov	r10d,r9d
	mov	edx,r8d
ifdef __DZ__
	.if	edx != M_RDONLY
		mov byte ptr _diskflag,1
	.endif
endif
	xor	r9,r9
	xor	r8d,r8d
	.if	edx == M_RDONLY
		mov r8d,FILE_SHARE_READ
	.endif
	_osopenW( rcx, edx, r8d, r9, r10d, r11d )
	ret
osopenW ENDP

	END
