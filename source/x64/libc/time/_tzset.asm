include time.inc

	.code

	OPTION	WIN64:3, STACKBASE:rsp

_tzset	PROC uses rsi
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
	lea	r8,_tzname
	mov	rcx,[r8]
	mov	[rcx],al
	mov	rcx,[r8+8]
	mov	[rcx],al
toend:
	ret
_tzset	ENDP

_isindst PROC USES rsi rdi rbx tb:PTR S_TM
	mov	rsi,tb
	xor	eax,eax
	mov	ecx,[rsi].S_TM.tm_mon
	mov	edx,[rsi].S_TM.tm_year
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
	lea	r8,_days
	mov	edi,edx
	mov	ebx,[r8+rcx*4+4]
	cmp	edx,86
	jna	@F
	cmp	ecx,3
	jne	@F
	mov	ebx,[r8+rcx*4]
	add	ebx,7
@@:
	test	edx,3
	jnz	@F
	inc	ebx
@@:
	lea	rax,[rbx+365]
	lea	rcx,[rdx-70]
	mul	ecx
	lea	rax,[rax+rdi-1]
	shr	eax,2
	sub	eax,_LEAP_YEAR_ADJUST + _BASE_DOW
	xor	edx,edx
	mov	ecx,7
	idiv	ecx
	mov	eax,1
	cmp	[rsi].S_TM.tm_mon,3
	jne	@F
	cmp	[rsi].S_TM.tm_yday,edx
	ja	toend
	jne	false
	cmp	[rsi].S_TM.tm_hour,2
	jae	toend
	jmp	false
@@:
	cmp	[rsi].S_TM.tm_yday,edx
	jb	toend
	jne	false
	cmp	[rsi].S_TM.tm_hour,1
	jae	false
toend:
	ret
false:
	xor	eax,eax
	jmp	toend
_isindst ENDP

	END
