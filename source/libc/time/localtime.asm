include time.inc
include limits.inc

	.code

localtime PROC USES esi edi ptime: LPTIME
  local ptm, ltime
	mov	eax,ptime
	mov	eax,[eax]
	cmp	eax,0
	jl	error
	mov	esi,eax
	call	_tzset
	cmp	esi,3 * _DAY_SEC
	jna	@F
	cmp	esi,LONG_MAX - 3 * _DAY_SEC
	jnb	@F
	mov	eax,esi
	sub	eax,_timezone
	mov	ltime,eax
	gmtime( addr ltime )
	mov	ptm,eax
	cmp	_daylight,0
	je	done
	_isindst( ptm )
	test	eax,eax
	jz	done
	add	ltime,3600
	gmtime( addr ltime )
	mov	ptm,eax
	mov	[eax].tm.tm_isdst,1
	jmp	done
@@:
	gmtime( ptime )
	mov	ptm,eax
	mov	esi,eax
	mov	eax,[eax].tm.tm_sec
	sub	eax,_timezone
	mov	edi,eax
	xor	edx,edx
	mov	ecx,60
	idiv	ecx
	cmp	edx,0
	jnl	@F
	add	edx,ecx
	sub	edi,ecx
@@:
	mov	[esi].tm.tm_sec,edx
	mov	eax,edi
	xor	edx,edx
	idiv	ecx
	add	eax,[esi].tm.tm_min
	mov	edi,eax
	xor	edx,edx
	idiv	ecx
	cmp	edx,0
	jnl	@F
	add	edx,ecx
	sub	edi,ecx
@@:
	mov	[esi].tm.tm_min,edx
	mov	eax,edi
	xor	edx,edx
	idiv	ecx
	add	eax,[esi].tm.tm_hour
	mov	edi,eax
	xor	edx,edx
	mov	ecx,24
	idiv	ecx
	cmp	edx,0
	jnl	@F
	add	edx,ecx
	sub	edi,ecx
@@:
	mov	[esi].tm.tm_hour,edx
	mov	eax,edi
	xor	edx,edx
	idiv	ecx
	mov	edi,eax
	cmp	eax,0
	jng	@F
	mov	eax,[esi].tm.tm_wday
	add	eax,edi
	mov	ecx,7
	xor	edx,edx
	idiv	ecx
	mov	[esi].tm.tm_wday,edx
	add	[esi].tm.tm_mday,edi
	add	[esi].tm.tm_yday,edi
	jmp	done
@@:
	jnl	done
	mov	eax,[esi].tm.tm_wday
	add	eax,edi
	mov	ecx,7
	add	eax,ecx
	xor	edx,edx
	idiv	ecx
	mov	[esi].tm.tm_wday,edx
	add	[esi].tm.tm_mday,edi
	mov	eax,[esi].tm.tm_mday
	cmp	eax,0
	jg	@F
	add	[esi].tm.tm_mday,32
	mov	[esi].tm.tm_yday,365
	mov	[esi].tm.tm_mon,11
	dec	[esi].tm.tm_year
	jmp	done
@@:
	add	[esi].tm.tm_yday,edi
done:
	mov	eax,ptm
toend:
	ret
error:
	xor	eax,eax
	jmp	toend
localtime ENDP

	END
