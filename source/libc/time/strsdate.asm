include time.inc
include stdio.inc

	.code

strsdate PROC USES ecx edx string:LPSTR, t:PTR SYSTEMTIME

	mov	eax,t
	movzx	ecx,[eax].SYSTEMTIME.wDay
	movzx	edx,[eax].SYSTEMTIME.wMonth
	movzx	eax,[eax].SYSTEMTIME.wYear
	sprintf( string, "%02d.%02d.%d", ecx, edx, eax )
	mov	eax,string
	ret

strsdate ENDP

	END
