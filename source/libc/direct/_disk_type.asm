;
; 0 Unknown media type
; 1 No such root directory exists
; 2 Drive can be removed
; 3 Drive cannot be removed
; 4 Network disk drive
; 5 CD-ROM disk drive
; 6 RAM disk drive
;
include winbase.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

_disk_type PROC disk
	push	edx
	push	ecx
	mov	eax,'\: '
	mov	al,[esp+4+8]
	add	al,'A' - 1
	push	eax
	mov	eax,esp
	push	eax
	call	GetDriveType
	pop	ecx
	test	eax,eax
	pop	ecx
	pop	edx
	ret	4
_disk_type ENDP

	END
