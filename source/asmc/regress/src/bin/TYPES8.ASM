
;--- TYPE operator with GPR ASSUME
;--- prior to v2.10, TYPE ignored ASSUMEs for GPRs
;--- (unless the GPR was used inside [])

	.386
	.model flat, stdcall

PREAL8 typedef ptr REAL8

	.data

assume eax:PREAL8

	dw (typeof eax ) EQ (typeof DWORD)	;0
	dw (typeof [eax] ) EQ (typeof REAL8);-1
	dw (typeof eax ) EQ (typeof PREAL8)	;-1

assume eax:nothing

	dw (typeof eax ) EQ (typeof DWORD)	;-1
	dw (typeof eax ) EQ (typeof PREAL8)	;0

end
