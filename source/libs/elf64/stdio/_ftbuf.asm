; _FTBUF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

    .code

_ftbuf proc uses rbx r12 flag:SINT, fp:LPFILE

    mov r12,rsi
    mov ebx,[r12]._iobuf._flag
    .if edi
	.if ebx & _IOFLRTN

	    fflush(r12)

	    and ebx,not (_IOYOURBUF or _IOFLRTN)
	    mov [r12]._iobuf._flag,ebx
	    xor eax,eax
	    mov [r12]._iobuf._ptr,rax
	    mov [r12]._iobuf._base,rax
	    mov [r12]._iobuf._bufsiz,eax
	.endif
    .else
	and ebx,_IOFLRTN
	.ifnz
	    fflush(r12)
	.endif
    .endif
    ret

_ftbuf endp

    END
