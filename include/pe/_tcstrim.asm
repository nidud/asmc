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

_tcstrim proc uses rdi rbx string:LPTSTR

    ldr rbx,string

    .for ( rdi = &[rbx+_tcslen(rbx)*TCHAR-TCHAR], rcx = _pctype : eax : eax--, rdi-=TCHAR )

        movzx edx,TCHAR ptr [rdi]
ifdef _UNICODE
       .break .if ( edx > ' ' )
endif
       .break .if !( byte ptr [rcx+rdx*2] & _SPACE )
        mov TCHAR ptr [rdi],0
    .endf
    mov rcx,rbx
    ret

_tcstrim endp
