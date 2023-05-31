; FPUTWC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include stdio.inc

    .code

fputwc proc wc:wint_t, fp:LPFILE

    ldr cx,wc
    ldr rdx,fp
    movzx ecx,cx
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

    end
