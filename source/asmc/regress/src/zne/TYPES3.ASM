
;--- type expressions with EQ/NE operator

	.386
	.model flat

UINT typedef DWORD
PUINT typedef ptr DWORD
PVOID typedef ptr

	.code

	db (TYPE(dword ptr [edx])) eq DWORD
	db (TYPE(dword ptr [edx])) eq REAL4
	db (TYPE(byte ptr [edx])) eq BYTE
	db (TYPE(byte ptr [edx])) eq SBYTE
	db (TYPE(sword ptr [edx])) eq SWORD
	db (TYPE(sword ptr [edx])) eq WORD
	db (TYPE(real4 ptr [edx])) ne REAL8
	db (TYPE(qword ptr [edx])) ne qword
	db (TYPE(UINT ptr [edx])) eq UINT
	db (TYPE(DWORD ptr [edx])) eq UINT ;exp: TRUE
	db (TYPE(SDWORD ptr [edx])) eq UINT
	db (TYPE(PUINT ptr [edx])) eq PUINT
	db (TYPE(PVOID ptr [edx])) eq PVOID
	db (TYPE(PVOID ptr [edx])) eq PUINT	;exp: FALSE

	end
