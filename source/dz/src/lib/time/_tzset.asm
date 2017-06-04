include time.inc
include winbase.inc

	.code

_tzset	PROC uses esi
  local tz:TIME_ZONE_INFORMATION
	GetTimeZoneInformation( addr tz )
	cmp	eax,-1
	je	toend
	mov	ecx,60
	mov	eax,tz.Bias
	mul	ecx
	mov	esi,eax
	cmp	tz.StandardDate.wMonth,0
	je	@F
	mov	eax,tz.StandardBias
	mul	ecx
	add	esi,eax
@@:
	mov	_timezone,esi
	xor	eax,eax
	cmp	tz.DaylightDate.wMonth,ax
	je	@F
	cmp	tz.DaylightBias,eax
	je	@F
	inc	eax
@@:
	mov	_daylight,eax
	xor	eax,eax
	mov	ecx,_tzname
	mov	[ecx],al
	mov	ecx,_tzname[4]
	mov	[ecx],al
toend:
	ret
_tzset	ENDP

_isindst PROC USES esi edi ebx tb:ptr tm
	mov	esi,tb
	xor	eax,eax
	mov	ecx,[esi].tm.tm_mon
	mov	edx,[esi].tm.tm_year
	cmp	edx,67
	jb	toend
	cmp	ecx,3
	jb	toend
	cmp	ecx,9
	ja	toend
	inc	eax
	cmp	ecx,3
	jna	@F
	cmp	ecx,9
	jb	toend
@@:
	mov	edi,edx
	mov	ebx,_days[ecx*4+4]
	cmp	edx,86
	jna	@F
	cmp	ecx,3
	jne	@F
	mov	ebx,_days[ecx*4]
	add	ebx,7
@@:
	test	edx,3
	jnz	@F
	inc	ebx
@@:
	lea	eax,[ebx+365]
	lea	ecx,[edx-70]
	mul	ecx
	lea	eax,[eax+edi-1]
	shr	eax,2
	sub	eax,_LEAP_YEAR_ADJUST + _BASE_DOW
	xor	edx,edx
	mov	ecx,7
	idiv	ecx
	mov	eax,1
	cmp	[esi].tm.tm_mon,3
	jne	@F
	cmp	[esi].tm.tm_yday,edx
	ja	toend
	jne	false
	cmp	[esi].tm.tm_hour,2
	jae	toend
	jmp	false
@@:
	cmp	[esi].tm.tm_yday,edx
	jb	toend
	jne	false
	cmp	[esi].tm.tm_hour,1
	jae	false
toend:
	ret
false:
	xor	eax,eax
	jmp	toend
_isindst ENDP


	END
