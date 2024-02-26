; _TFPUTS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include stdio.inc
include string.inc
ifdef _UNICODE
include conio.inc
endif
include tchar.inc

    .code

_fputts proc uses rbx string:LPTSTR, fp:LPFILE

   .new length:int_t

    ldr rbx,string
    mov length,_tcslen( rbx )

ifdef _UNICODE
    .new retval:int_t = 0
    .for ( : length : length--, rbx+=2 )

        .if ( fputwc([rbx], fp) == WEOF )

            mov retval,-1
           .break
        .endif
    .endf
    mov eax,retval
else
   .new buffing:int_t = _stbuf( fp )
    mov ebx,fwrite( rbx, 1, length, fp )
    _ftbuf(buffing, fp)
    mov ecx,length
    xor eax,eax
    .if ( ebx != ecx )
        dec rax
    .endif
endif
    ret

_fputts endp

    end
