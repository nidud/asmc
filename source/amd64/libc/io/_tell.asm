include io.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp

_tell	proc handle:SINT
	_lseek( ecx, 0, SEEK_CUR )
	ret
_tell	endp

	end
