; STRCHRI.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

    .code

strchri::

    mov r8,rcx
    movzx eax,dl

    sub al,'A'
    cmp al,'Z'-'A'+1
    sbb cl,cl
    and cl,'a'-'A'
    add cl,al
    add cl,'A'

    .repeat

	mov al,[r8]
	.break .if !al

	inc r8
	sub al,'A'
	cmp al,'Z'-'A'+1
	sbb ch,ch
	and ch,'a'-'A'
	add al,ch
	add al,'A'
	.continue(0) .if al != cl
	lea rax,[r8-1]
    .until 1
    ret

    end
