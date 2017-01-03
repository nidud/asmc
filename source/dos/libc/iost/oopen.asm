; OOPEN.ASM--
; Copyright (C) 2015 Doszip Developers

include iost.inc
include io.inc
include errno.inc
include conio.inc

extrn	CP_ENOMEM:BYTE

	.code

oopen	PROC _CType PUBLIC USES si file:DWORD, mode:size_t
	.if mode
	    invoke ogetouth,file
	    mov si,offset STDO
	.else
	    invoke openfile,file,M_RDONLY,A_OPEN
	    mov si,offset STDI
	.endif
	cmp ax,1	; -1 or 0 (error/cancel)
	jl  @F
	mov [si].S_IOST.ios_file,ax
	invoke oinitst,ds::si,[si].S_IOST.ios_size
	.if ZERO?
	    invoke close,[si].S_IOST.ios_file
	    invoke ermsg,0,addr CP_ENOMEM
	    dec ax
	.else
	    mov ax,[si].S_IOST.ios_file
	.endif
      @@:
	ret
oopen	ENDP

	END
