; _STRLWR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include string.inc
include ctype.inc

    .code

if WINVER GE 0x0600

_strlwr proc frame uses rsi string:string_t

    .for ( rsi = rcx : byte ptr [rsi] : rsi++ )

	movzx ecx,byte ptr [rsi]
	tolower(ecx)
	mov [rsi],al
    .endf

    mov rax,string

else

    option win64:rsp nosave noauto

_strlwr proc string:string_t

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

endif

    ret

_strlwr endp

    end
