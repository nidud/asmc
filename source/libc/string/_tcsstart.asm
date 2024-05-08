; _TCSSTART.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; char *strstart(char *);
; wchar_t *_wstrstart(wchar_t *);
;
; Return:
;   rax - start (or end) of string
;   ecx - first char of string (or 0)
;   rdx - _pctype
;
include string.inc
include ctype.inc
include tchar.inc

    .code

_tcsstart proc string:LPTSTR

    ldr rax,string

    .for ( rdx = _pctype : : rax+=TCHAR )

        movzx ecx,TCHAR ptr [rax]
ifdef _UNICODE
       .break .if ( ecx > ' ' )
endif
       .break .if !( byte ptr [rdx+rcx*2] & _SPACE )
    .endf
    ret

_tcsstart endp

    end
