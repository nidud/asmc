; FPUTS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include string.inc

    .code

fputs proc uses rsi rdi rbx string:LPSTR, fp:LPFILE

    ldr rbx,string
    ldr rdx,fp

    mov edi,_stbuf( rdx )
    mov esi,strlen( rbx )
    mov ebx,fwrite( rbx, 1, eax, fp )

    _ftbuf(edi, fp)

    mov ecx,esi
    xor eax,eax

    .if ( ebx )
	dec rax
    .endif
    ret

fputs endp

    end
