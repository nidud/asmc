; __TIMETOST.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc

	.code

__TimeToST PROC USES edx ecx Time:time_t, lpSystemTime:LPSYSTEMTIME
	mov	ecx,lpSystemTime
	mov	[ecx].SYSTEMTIME.wDayOfWeek,0
	mov	[ecx].SYSTEMTIME.wMilliseconds,0
	movzx	edx,word ptr Time+2
	mov	eax,edx
	shr	eax,9
	add	eax,DT_BASEYEAR
	mov	[ecx].SYSTEMTIME.wYear,ax
	mov	eax,edx
	shr	eax,5
	and	eax,1111B
	mov	[ecx].SYSTEMTIME.wMonth,ax
	mov	eax,edx
	and	eax,11111B
	mov	[ecx].SYSTEMTIME.wDay,ax
	movzx	eax,word ptr Time
	mov	edx,eax
	shr	eax,11
	mov	[ecx].SYSTEMTIME.wHour,ax
	mov	eax,edx
	shr	eax,5
	and	ax,111111B
	mov	[ecx].SYSTEMTIME.wMinute,ax
	mov	eax,edx
	and	eax,11111B
	shl	eax,1
	mov	[ecx].SYSTEMTIME.wSecond,ax
	mov	eax,ecx
	ret
__TimeToST ENDP

	END
