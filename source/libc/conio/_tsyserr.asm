; _TSYSERR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include syserr.inc

.code

_syserr proc en:uint_t, title:tstring_t

ifdef _UNICODE
   .new buffer[_SYS_MSGMAX]:wchar_t
endif

    ldr ecx,en
    mov rcx,_sys_err_msg(ecx)

ifdef _UNICODE
    movzx eax,char_t ptr [rcx]
    .for ( edx = 0 : eax && edx < _SYS_MSGMAX : edx++ )

        mov al,[rcx+rdx]
        mov buffer[rdx*2],ax
    .endf
    xor eax,eax
    mov buffer[rdx*2],ax
    lea rcx,buffer
endif
    _msgbox(MB_ICONERROR, title, rcx)
    xor eax,eax
    ret

_syserr endp

    end
