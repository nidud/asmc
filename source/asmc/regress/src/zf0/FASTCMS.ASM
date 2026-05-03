
;--- FASTCALL MS variant (-Gr and -zf0)
;--- the decoration of the public symbol names are checked here.
;--- caused a GPF before v2.18 if a non-proc symbol was declared public.

	.386
	.model flat

	public  dwPub1, dwPub2

	.data

dwPub1	dd 1
dwPub2	dd 2

	.code

fproc1 proc a1:dword
	mov eax,a1
	add eax,dwPub1
	add eax,dwPub2
	ret
fproc1 endp

_start:
	invoke fproc1, 1
	mov ah,4Ch
	int 21h

end _start
