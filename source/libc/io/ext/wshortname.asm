include io.inc
include string.inc
include wsub.inc

	.data
	shortname db 14 dup(0)
	.code

wshortname PROC path:LPSTR
local	wblk:S_WFBLK
	.if	wfindfirst( path, addr wblk, 00FFh ) == -1
		mov	eax,path
	.else
		wcloseff( eax )
		mov	eax,path
		.if	wblk.wf_shortname
			mov shortname[12],0
			memcpy( addr shortname, addr wblk.wf_shortname, 12 )
		.endif
	.endif
	ret
wshortname ENDP

	END
