include time.inc
include stdio.inc

	.code

SystemTimeToString PROC USES ecx edx string:LPSTR, t:LPSYSTEMTIME
	mov	eax,t
	movzx	ecx,[eax].SYSTEMTIME.wSecond
	movzx	edx,[eax].SYSTEMTIME.wMinute
	movzx	eax,[eax].SYSTEMTIME.wHour
	sprintf( string, "%02d:%02d:%02d", eax, edx, ecx )
	mov	eax,string
	ret
SystemTimeToString ENDP

	END
