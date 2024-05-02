
;--- TYPE operator with GPR ASSUME
;--- prior to v2.10, TYPE ignored ASSUMEs for GPRs
;--- (unless the GPR was used inside [])

	.386
	.model flat, stdcall

PREAL8 typedef ptr REAL8

	.data

assume eax:PREAL8

	dw (TYPE eax ) EQ (TYPE DWORD) ;0
	dw (TYPE [eax] ) EQ (TYPE REAL8);-1
	dw (TYPE eax ) EQ (TYPE PREAL8) ;-1

assume eax:nothing

	dw (TYPE eax ) EQ (TYPE DWORD) ;-1
	dw (TYPE eax ) EQ (TYPE PREAL8) ;0

end
