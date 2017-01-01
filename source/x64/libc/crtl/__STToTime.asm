; unsigned SystemTimeToTime(SYSTEMTIME *lpSystemTime);
;
; Return:
;
;    edx - <date> yyyyyyymmmmddddd
;    ecx - <time> hhhhhmmmmmmsssss
;    eax - <date>:<time>
;
include time.inc

	.code

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

__STToTime PROC lpSystemTime:LPSYSTEMTIME
	movzx	eax,[rcx].SYSTEMTIME.wYear
	sub	eax,DT_BASEYEAR
	shl	eax,9
	movzx	edx,[rcx].SYSTEMTIME.wMonth
	shl	edx,5
	or	eax,edx
	or	ax,[rcx].SYSTEMTIME.wDay
	shl	eax,16
	mov	r8d,eax
	movzx	eax,[rcx].SYSTEMTIME.wSecond
	shr	eax,1
	mov	edx,eax ; second/2
	mov	al,byte ptr [rcx].SYSTEMTIME.wHour
	movzx	ecx,byte ptr [rcx].SYSTEMTIME.wMinute
	shl	ecx,5
	shl	eax,11
	or	eax,ecx
	or	eax,edx
	mov	edx,r8d ; <date> yyyyyyymmmmddddd
	mov	ecx,eax ; <time> hhhhhmmmmmmsssss
	or	eax,edx ; <date>:<time>
	shr	edx,16
	ret
__STToTime ENDP

	END
