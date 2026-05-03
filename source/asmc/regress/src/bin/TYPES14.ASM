
;--- regression in v2.10
;--- fixed in v2.10a
ifdef __ASMC__
option masm:on
endif

	.386
	.model flat

S1 STRUCT
f1   db ?,?
S1 ENDS

	.code

v1 S1 <>

	if (TYPE v1.f1[ecx]) eq BYTE
		dw -1
	else
		dw 0
	endif

end
