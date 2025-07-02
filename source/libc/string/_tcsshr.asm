; _TCSSHR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; char * strshr(char *string, int c);
; wchar_t * _wstrshr(wchar_t *string, int c);
;
; Shift string right by one and insert char at string position
;
include string.inc
include tchar.inc

    .code

    option dotname

_tcsshr proc string:tstring_t, chr:int_t

    ldr     rcx,string
    ldr     eax,chr
.0:
    mov     _tdl,[rcx]
    mov     [rcx],_tal
    add     rcx,tchar_t
    test    _tal,_tal
    mov     eax,edx
    jnz     .0
    mov     rax,string
    ret

_tcsshr endp

    end
