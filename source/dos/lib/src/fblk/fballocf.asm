; FBALLOCF.ASM--
; Copyright (C) 2015 Doszip Developers

include fblk.inc
include dos.inc
include string.inc

	.code

fballocff PROC _CType PUBLIC USES bx ffblk:DWORD, flag:size_t
	les bx,ffblk
	sub cx,cx
	mov cl,BYTE PTR es:[bx].S_FFBLK.ff_attrib
	or  cx,flag
	.if fballoc(addr es:[bx].S_FFBLK.ff_name,DWORD PTR es:[bx].S_FFBLK.ff_ftime,
	    es:[bx].S_FFBLK.ff_fsize,cx)
	    mov bx,ax
	    .if WORD PTR es:[bx].S_FBLK.fb_name == '..' && es:[bx].S_FBLK.fb_name[2] == 0
		or es:[bx].S_FBLK.fb_flag,_A_UPDIR
	    .endif
	    .if !(cl & _A_SUBDIR)
		add ax,S_FBLK.fb_name
		.if cl & _A_SYSTEM or _A_HIDDEN
		    inc ax
		.endif
		invoke strlwr,dx::ax
		mov ax,bx
	    .endif
	.endif
	ret
fballocff ENDP

	END

