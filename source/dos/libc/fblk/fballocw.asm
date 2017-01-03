; FBALLOCW.ASM--
; Copyright (C) 2015 Doszip Developers

include fblk.inc
include dos.inc

	.code

fballocwf PROC _CType PUBLIC USES di bx wfblk:DWORD, flag:size_t
	les bx,wfblk
	mov  di,bx
	mov  ax,flag
	or   al,es:[bx]
	and  al,_A_FATTRIB
	mov  cx,ax
	add  bx,S_WFBLK.wf_name
	lodm es:[di].S_WFBLK.wf_time
	.if cl & _A_SUBDIR
	    lodm es:[di].S_WFBLK.wf_timecreate
	.endif
	.if fballoc(es::bx,dx::ax,es:[di].S_WFBLK.wf_sizeax,cx)
	    .if cl & _A_SUBDIR && \
		WORD PTR es:[bx].S_FBLK.fb_name == '..' && \
		BYTE PTR es:[bx].S_FBLK.fb_name[2] == 0
		or es:[bx].S_FBLK.fb_flag,_A_UPDIR
	    .endif
	.endif
	ret
fballocwf ENDP

	END
