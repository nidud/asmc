; _STRLWR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

    .code

_strlwr::

    mov r10,rcx
    .while 1
	mov al,[rcx]
	.break .if !al
	sub al,'A'
	cmp al,'Z' - 'A' + 1
	sbb al,al
	and al,'a' - 'A'
	xor [rcx],al
	inc rcx
    .endw
    mov rax,r10
    ret

    end
