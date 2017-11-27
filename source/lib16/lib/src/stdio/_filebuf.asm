; _FILEBUF.ASM--
; Copyright (C) 2015 Doszip Developers

include stdio.inc
include io.inc

	.code

_filebuf PROC _CType PUBLIC USES si di fp:DWORD
	mov si,WORD PTR fp
	mov di,[si].S_FILE.iob_flag
	.if (di & _IOREAD or _IOWRT or _IORW) && !(di & _IOSTRG)
	    .if di & _IOWRT
		or di,_IOERR
		mov [si].S_FILE.iob_flag,di
	    .else
		or di,_IOREAD
		.if !(di & _IOMYBUF or _IONBF or _IOYOURBUF)
		    invoke _getbuf,fp
		.else
		    movmx [si].S_FILE.iob_bp,[si].S_FILE.iob_base
		.endif
		invoke read,[si].S_FILE.iob_file,[si].S_FILE.iob_base,[si].S_FILE.iob_bufsize
		mov [si].S_FILE.iob_cnt,ax
		.if !ax || ax == 1 || ax == -1
		    test ax,ax
		    mov ax,_IOERR
		    .if ZERO?
			mov ax,_IOEOF
		    .endif
		    or [si].S_FILE.iob_flag,ax
		    xor ax,ax
		    mov [si].S_FILE.iob_cnt,ax
		    jmp @F
		.endif
		.if !(di & _IOWRT or _IORW)
		    mov ax,offset _osfile
		    add ax,[si].S_FILE.iob_file
		    xchg ax,bx
		    mov bl,[bx]
		    xchg ax,bx
		    and al,FH_TEXT or FH_EOF
		    .if al == FH_TEXT or FH_EOF
			or [si].S_FILE.iob_flag,_IOCTRLZ
		    .endif
		.endif
		mov ax,[si].S_FILE.iob_bufsize
		.if ax == _MINIOBUF
		    .if (di & _IOMYBUF) && !(di & _IOSETVBUF)
			mov [si].S_FILE.iob_bufsize,_INTIOBUF
		    .endif
		.endif
		dec [si].S_FILE.iob_cnt
		inc WORD PTR [si].S_FILE.iob_bp
		les si,[si].S_FILE.iob_bp
		dec si
		mov al,es:[si]
		mov ah,0
	    .endif
	.else
	@@:
	    mov ax,-1
	.endif
	ret
_filebuf ENDP

	END
