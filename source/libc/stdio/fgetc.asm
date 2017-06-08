include stdio.inc

	.code

	option stackbase:esp

fgetc	PROC fp:LPFILE
	mov eax,fp
	dec [eax]._iobuf._cnt
	jl  fbuf
	add [eax]._iobuf._ptr,1
	mov eax,[eax]._iobuf._ptr
	movzx eax,byte ptr [eax-1]
toend:
	ret
fbuf:
	_filbuf( eax )
	jmp toend
fgetc	ENDP

	END
