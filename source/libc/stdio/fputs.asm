; FPUTS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include string.inc

    .code

fputs proc uses rbx string:LPSTR, fp:LPFILE

   .new buf:int_t
   .new len:int_t

    ldr rbx,string
    mov buf,_stbuf( fp )
    mov len,strlen( rbx )
    mov ebx,fwrite( rbx, 1, eax, fp )
    _ftbuf(buf, fp)
    mov ecx,len
    xor eax,eax
    .if ( ebx )
	dec rax
    .endif
    ret

fputs endp

    end
