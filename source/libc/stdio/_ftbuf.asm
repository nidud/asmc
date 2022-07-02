; _FTBUF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

    .code

_ftbuf proc uses rsi rdi flag:int_t, fp:LPFILE

ifndef _WIN64
    mov ecx,flag
    mov edx,fp
endif
    mov rsi,rdx
    mov edi,[rsi]._iobuf._flag

    .if ( ecx )

	.if ( edi & _IOFLRTN )

	    fflush( rsi )

	    and edi,not (_IOYOURBUF or _IOFLRTN)
	    mov [rsi]._iobuf._flag,edi
	    xor eax,eax
	    mov [rsi]._iobuf._ptr,rax
	    mov [rsi]._iobuf._base,rax
	    mov [rsi]._iobuf._bufsiz,eax
	.endif

    .else

	and edi,_IOFLRTN
	.ifnz
	    fflush( rsi )
	.endif
    .endif
    ret

_ftbuf endp

    end
