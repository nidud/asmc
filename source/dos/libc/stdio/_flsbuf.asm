; _FLSBUF.ASM--
; Copyright (C) 2015 Doszip Developers

include stdio.inc
include io.inc
include dir.inc

extrn	__STDIO:near

	.code

_flsbuf PROC _CType PUBLIC USES bx di si char:size_t, fp:DWORD
	mov si,WORD PTR fp
	mov di,[si].S_FILE.iob_flag
	.if !(di & _IOREAD or _IOWRT or _IORW) || di & _IOSTRG
	    jmp @@error
	.endif
	.if di & _IOREAD
	    sub ax,ax
	    mov [si].S_FILE.iob_cnt,ax
	    .if !(di & _IOEOF)
		jmp @@error
	    .endif
	    movmx [si].S_FILE.iob_bp,[si].S_FILE.iob_base
	    and di,not _IOREAD
	.endif
	or  di,_IOWRT
	and di,not _IOEOF
	mov [si].S_FILE.iob_flag,di
	sub ax,ax
	mov [si].S_FILE.iob_cnt,ax
	.if !(di & _IOMYBUF or _IONBF or _IOYOURBUF)
	    .if isatty([si].S_FILE.iob_file)
		.if si == offset stdout || si == offset stderr
		    invoke _getbuf,ds::si
		.endif
	    .endif
	.endif
	mov ax,di
	sub di,di
	mov [si].S_FILE.iob_cnt,di
	.if ax & _IOMYBUF or _IOYOURBUF
	    mov ax,WORD PTR [si].S_FILE.iob_base
	    mov di,WORD PTR [si].S_FILE.iob_bp
	    sub di,ax
	    inc ax
	    mov WORD PTR [si].S_FILE.iob_bp,ax
	    mov ax,[si].S_FILE.iob_bufsize
	    dec ax
	    mov [si].S_FILE.iob_cnt,ax
	    sub ax,ax
	    .if SWORD PTR di > 0
		invoke write,[si].S_FILE.iob_file,[si].S_FILE.iob_base,di
	    .else
		mov bx,[si].S_FILE.iob_file
		.if SWORD PTR bx > 0 && _osfile[bx] & FH_APPEND
		    push ax
		    invoke lseek,[si].S_FILE.iob_file,0,SEEK_END
		    pop ax
		.endif
	    .endif
	    mov dx,char
	    les bx,[si].S_FILE.iob_base
	    mov es:[bx],dl
	.else
	    inc di
	    invoke write,[si].S_FILE.iob_file,addr char,di
	.endif
	cmp ax,di
	jne @@error
	mov al,BYTE PTR char
	mov ah,0
      @@:
	ret
@@error:
	or  di,_IOERR
	mov [si].S_FILE.iob_flag,di
	mov ax,-1
	jmp @B
_flsbuf ENDP

	END
