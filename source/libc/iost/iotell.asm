include iost.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

iotell	PROC io:PTR S_IOST
	mov	edx,[esp+4]
	mov	eax,dword ptr [edx].S_IOST.ios_total
	add	eax,[edx].S_IOST.ios_i
	mov	edx,dword ptr [edx].S_IOST.ios_total[4]
	adc	edx,0
	ret	4
iotell	ENDP

	END
