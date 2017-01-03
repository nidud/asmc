; _STDINIT.ASM--
; Copyright (C) 2015 Doszip Developers

include stdio.inc

PUBLIC	__STDIO
extrn	output_flush:size_p

	.code

__STDIO:
  ifdef __l__
	mov ax,cs
	mov WORD PTR output_flush+2,ax
	mov ax,offset _flsbuf
	mov WORD PTR output_flush,ax
  else
	mov ax,_flsbuf
	mov output_flush,ax
  endif
	ret

pragma_init __STDIO, 2

	END
