
;--- type expressions with EQ/NE operator

	.386
	.model flat

UINT typedef DWORD
PUINT typedef ptr DWORD
PVOID typedef ptr

	.code

	db (typeof(dword ptr [edx])) eq DWORD
	db (typeof(dword ptr [edx])) eq REAL4
	db (typeof(byte ptr [edx]))  eq BYTE
	db (typeof(byte ptr [edx]))  eq SBYTE
	db (typeof(sword ptr [edx])) eq SWORD
	db (typeof(sword ptr [edx])) eq WORD
	db (typeof(real4 ptr [edx])) ne REAL8
	db (typeof(qword ptr [edx])) ne qword
	db (typeof(UINT ptr [edx]))  eq UINT
	db (typeof(DWORD ptr [edx])) eq UINT	;exp: TRUE
	db (typeof(SDWORD ptr [edx])) eq UINT
	db (typeof(PUINT ptr [edx])) eq PUINT
	db (typeof(PVOID ptr [edx])) eq PVOID
	db (typeof(PVOID ptr [edx])) eq PUINT	;exp: FALSE

	end
