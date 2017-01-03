; FILEXIST.ASM--
; Copyright (C) 2015 Doszip Developers

include dos.inc

	.code

filexist PROC _CType PUBLIC file:DWORD
	invoke	getfattr,file
	inc	ax
	jz	@F
	dec	ax		; 1 = file
	and	ax,_A_SUBDIR	; 2 = subdir
	shr	ax,4
	inc	ax
      @@:
	ret
filexist ENDP

	END

