; FPUTWC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

    .code

fputwc proc wc:wint_t, fp:LPFILE

ifndef _WIN64
    movzx ecx,wc
    mov edx,fp
endif
    sub [rdx]._iobuf._cnt,2
    .ifl
	_flswbuf( ecx, rdx )
    .else
	mov rax,[rdx]._iobuf._ptr
	add [rdx]._iobuf._ptr,2
	mov [rax],cx
    .endif
    ret

fputwc endp

    END
