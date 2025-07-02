; _TCSTRIM.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; int strtrim(char *);
; int _wstrtrim(wchar_t *);
;
; Return EAX char count, RCX string, and edx last char
;
include string.inc
include ctype.inc
include tchar.inc

    .code

_tcstrim proc uses rdi rbx string:tstring_t

    ldr rbx,string

    .for ( rdi = &[rbx+_tcslen(rbx)*tchar_t-tchar_t], rcx = _pctype : eax : eax--, rdi-=tchar_t )

        movzx edx,tchar_t ptr [rdi]
ifdef _UNICODE
       .break .if ( edx > ' ' )
endif
       .break .if !( byte ptr [rcx+rdx*2] & _SPACE )
        mov tchar_t ptr [rdi],0
    .endf
    mov rcx,rbx
    ret

_tcstrim endp

    END
