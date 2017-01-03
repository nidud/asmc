; _STBUF.ASM--
; Copyright (C) 2015 Doszip Developers

include stdio.inc
include io.inc
include alloc.inc

extrn	__STDIO:near
extrn	_stdbuf:DWORD

	.code

_stbuf	PROC _CType PUBLIC USES bx fp:DWORD
	les bx,fp
	.if isatty(es:[bx].S_FILE.iob_file)
	    xor ax,ax
	    mov dx,ax
	    .if bx != offset stdout
		.if bx != offset stderr
		    jmp @F
		.endif
		inc dx
	    .endif
	    mov cx,[bx].S_FILE.iob_flag
	    and cx,_IOMYBUF or _IONBF or _IOYOURBUF
	    jnz @F
	    or	cx,_IOWRT or _IOYOURBUF or _IOFLRTN
	    mov [bx].S_FILE.iob_flag,cx
	    shl dx,2
	    add dx,offset _stdbuf
	    mov bx,dx
	    mov ax,[bx]
	    mov dx,[bx+2]
	    mov cx,_INTIOBUF
	    .if !ax
		push bx
		invoke malloc,cx
		pop bx
		mov [bx],ax
		mov [bx+2],dx
		mov cx,_INTIOBUF
		.if ZERO?
		    mov bx,WORD PTR fp
		    mov dx,ds
		    lea ax,[bx].S_FILE.iob_charbuf
		    mov cx,2
		.endif
	    .endif
	    mov bx,WORD PTR fp
	    stom [bx].S_FILE.iob_bp
	    stom [bx].S_FILE.iob_base
	    mov [bx].S_FILE.iob_bufsize,cx
	    mov ax,1
	.endif
      @@:
	ret
_stbuf	ENDP

	END
