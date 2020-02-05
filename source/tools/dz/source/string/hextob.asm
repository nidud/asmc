; HEXTOB.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include string.inc

.code

hextob proc string:LPSTR

    mov edx,string
    mov ecx,edx

    .while 1

	mov ax,[ecx]
	inc ecx
	.continue .if al == ' '

	inc ecx
	.break .if !al

	sub al,'0'
	.if al > 9
	    sub al,7
	.endif

	shl al,4
	.if !ah
	    mov [edx],al
	    inc edx
	    .break
	.endif

	sub ah,'0'
	.if ah > 9
	    sub ah,7
	.endif

	or  al,ah
	mov [edx],al
	inc edx
    .endw

    mov byte ptr [edx],0
    mov eax,string
    mov ecx,edx
    sub ecx,eax
    ret

hextob endp

    end
