; v 2.23 - proto fastcall :type

	.386
	.model	flat, stdcall
	.code

S1	struc
l1	dd ?
l2	dd ?
S1	ends

foo	proto fastcall :ptr S1
;
; This fails in ML:	error A2008: syntax error : panel
;	    and JWASM:	Error A2137: Conflicting parameter definition: panel
;		ASMC:	error A2111: conflicting parameter definition : pS1
;
foo	proc fastcall panel:ptr S1

	mov	eax,[panel].S1.l1
	ret
foo	endp

	END
