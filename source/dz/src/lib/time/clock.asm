include time.inc
include winbase.inc

	.code

clock	PROC
  local t:SYSTEMTIME
	mov	edx,edi
	xor	eax,eax
	mov	ecx,SIZE SYSTEMTIME
	lea	edi,t
	rep	stosb
	mov	edi,edx
	GetLocalTime( addr t )
	__STToTime( addr t )
	ret
clock	ENDP

	END
