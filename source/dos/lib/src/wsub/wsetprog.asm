; WSETPROG.ASM--
; Copyright (C) 2015 Doszip Developers

include wsub.inc
include conio.inc
include string.inc
include progress.inc

	.code

wsetprogress PROC _CType PUBLIC USES di
	mov	di,ax
	invoke	strfn,addr __srcfile
	invoke	progress_set,dx::ax,addr __outpath,ss::di
	ret
wsetprogress ENDP

	END
