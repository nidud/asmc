; FPUTC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

    .code

fputc proc c:int_t, fp: LPFILE

    ldr ecx,c
    ldr rdx,fp
    dec [rdx]._iobuf._cnt
    .ifl
	_flsbuf( ecx, rdx )
    .else
	mov eax,ecx
	mov rcx,[rdx]._iobuf._ptr
	inc [rdx]._iobuf._ptr
	mov [rcx],al
    .endif
    ret

fputc endp

    end
