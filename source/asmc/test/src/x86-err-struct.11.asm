
;--- an undefined member in a critical expression must emit an error in pass one

	.386
	.model flat, stdcall

	.code

S1 struct
f1 db ?
S1 ends

myvar S1 <>
nostruct db ?

	if TYPEOF(nostruct.foo) eq BYTE
		db 0
	elseif TYPEOF(nostruct.foo[ecx]) eq BYTE
		db 1
	else
		db 2
	endif

	if TYPEOF(myvar.f2) eq BYTE
		db 0
	elseif TYPEOF(myvar.f2[ecx]) eq BYTE
		db 1
	else
		db 2
	endif

end
