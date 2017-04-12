include time.inc
include limits.inc

	.code

	OPTION	WIN64:3, STACKBASE:rsp

localtime PROC USES rsi rdi ptime: LPTIME

  local ptm:qword, ltime

	mov	eax,[rcx]
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
	mov	ptm,rax
	cmp	_daylight,0
	je	done
	_isindst( ptm )
	test	eax,eax
	jz	done
	add	ltime,3600
	gmtime( addr ltime )
	mov	ptm,rax
	mov	[rax].tm.tm_isdst,1
	jmp	done
@@:
	gmtime( ptime )
	mov	ptm,rax
	mov	rsi,rax
	mov	eax,[rax].tm.tm_sec
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
	mov	[rsi].tm.tm_sec,edx
	mov	eax,edi
	xor	edx,edx
	idiv	ecx
	add	eax,[rsi].tm.tm_min
	mov	edi,eax
	xor	edx,edx
	idiv	ecx
	cmp	edx,0
	jnl	@F
	add	edx,ecx
	sub	edi,ecx
@@:
	mov	[rsi].tm.tm_min,edx
	mov	eax,edi
	xor	edx,edx
	idiv	ecx
	add	eax,[rsi].tm.tm_hour
	mov	edi,eax
	xor	edx,edx
	mov	ecx,24
	idiv	ecx
	cmp	edx,0
	jnl	@F
	add	edx,ecx
	sub	edi,ecx
@@:
	mov	[rsi].tm.tm_hour,edx
	mov	eax,edi
	xor	edx,edx
	idiv	ecx
	mov	edi,eax
	cmp	eax,0
	jng	@F
	mov	eax,[rsi].tm.tm_wday
	add	eax,edi
	mov	ecx,7
	xor	edx,edx
	idiv	ecx
	mov	[rsi].tm.tm_wday,edx
	add	[rsi].tm.tm_mday,edi
	add	[rsi].tm.tm_yday,edi
	jmp	done
@@:
	jnl	done
	mov	eax,[rsi].tm.tm_wday
	add	eax,edi
	mov	ecx,7
	add	eax,ecx
	xor	edx,edx
	idiv	ecx
	mov	[rsi].tm.tm_wday,edx
	add	[rsi].tm.tm_mday,edi
	mov	eax,[esi].tm.tm_mday
	cmp	eax,0
	jg	@F
	add	[rsi].tm.tm_mday,32
	mov	[rsi].tm.tm_yday,365
	mov	[rsi].tm.tm_mon,11
	dec	[rsi].tm.tm_year
	jmp	done
@@:
	add	[rsi].tm.tm_yday,edi
done:
	mov	rax,ptm
toend:
	ret
error:
	xor	eax,eax
	jmp	toend
localtime ENDP

	END
