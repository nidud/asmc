; SETJMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include setjmp.inc

    .code

    option stackbase:esp

    assume eax:jmp_buf

_setjmp3::

setjmp proc buf:jmp_buf
setjmp endp

_setjmp proc buf:jmp_buf

    mov eax,[esp+4]
    mov [eax]._Ebp,ebp
    mov [eax]._Ebx,ebx
    mov [eax]._Edi,edi
    mov [eax]._Esi,esi
    mov [eax]._Esp,esp
    mov ecx,[esp]
    mov [eax]._Eip,ecx
    xor eax,eax
    ret

_setjmp endp

    assume edx:jmp_buf

longjmp proc c buf:jmp_buf, retval:int_t

    mov edx,[esp+4]
    mov eax,[esp+8]
    mov ebp,[edx]._Ebp
    mov ebx,[edx]._Ebx
    mov edi,[edx]._Edi
    mov esi,[edx]._Esi
    mov esp,[edx]._Esp
    mov ecx,[edx]._Eip
    mov [esp],ecx
    ret

longjmp endp

    end
