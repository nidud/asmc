include consx.inc
include alloc.inc

	.code

rcalloc PROC rc:S_RECT, shade:UINT

	malloc( rcmemsize( rc, shade ) )
	ret

rcalloc ENDP

	END
