include stdlib.inc
include string.inc
include stdio.inc

    .code

mkbstring proc uses esi edi buf:LPSTR, qw:qword

local tmp[32]:byte

    sprintf(&tmp, "%I64u", qw)
    _strrev(&tmp)

    mov esi,eax
    mov edi,buf
    xor edx,edx
    mov ah,' '
    .while 1
	lodsb
	stosb
	.break .if !al
	inc dl
	.if dl == 3
	mov al,ah
	stosb
	xor dl,dl
	.endif
    .endw
    .if [edi-2] == ah
	mov [edi-2],dh
    .endif
    _strrev(buf)
    mov eax,dword ptr qw
    mov ecx,dword ptr qw+4
    xor edx,edx
    .while  ecx || eax > 1024*10
	shrd eax,ecx,10
	shr ecx,10
	inc edx
    .endw
    ret
mkbstring endp

    END
