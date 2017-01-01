include consx.inc
include alloc.inc

	.code

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

rcalloc PROC rc:S_RECT, shade
	malloc( rcmemsize( ecx, edx ) )
	ret
rcalloc ENDP

	END
