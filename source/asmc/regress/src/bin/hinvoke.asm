;
; v2.22 -- invoke pointers in HLL
;
	.486
	.model	flat, stdcall
	.code

PROTO_T TYPEDEF PROTO STDCALL :DWORD, :DWORD
PROTO_P TYPEDEF PTR PROTO_T

	.data
	data_p	PROTO_P 0

	.code

	invoke	data_p,1,2	; works

	.if	data_p(1,2)	; failed..

		nop
	.endif

foo	proc stack_p:PROTO_P

	invoke	stack_p,1,2	; works

	.if	stack_p(1,2)	; failed..

		nop
	.endif

foo	endp

	END
