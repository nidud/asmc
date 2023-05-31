; _FTBUF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

    .code

    assume rbx:LPFILE

_ftbuf proc uses rbx flag:int_t, fp:LPFILE

    ldr ecx,flag
    ldr rbx,fp
    mov edx,[rbx]._flag

    .if ( ecx )

	.if ( edx & _IOFLRTN )

	    fflush( rbx )

	    and [rbx]._flag,not (_IOYOURBUF or _IOFLRTN)
	    xor eax,eax
	    mov [rbx]._ptr,rax
	    mov [rbx]._base,rax
	    mov [rbx]._bufsiz,eax
	.endif
    .else
	and edx,_IOFLRTN
	.ifnz
	    fflush( rbx )
	.endif
    .endif
    ret

_ftbuf endp

    end
