; WCSCHR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

    option dotname

wcschr proc string:ptr wchar_t, wc:wchar_t

    ldr     rax,string
    ldr     cx,wc
.3:
    cmp     cx,[rax]
    je      .0
    cmp     wchar_t ptr [rax],0
    je      .4
    cmp     cx,[rax+2]
    je      .1
    cmp     wchar_t ptr [rax+2],0
    je      .4
    cmp     cx,[rax+4]
    je      .2
    cmp     wchar_t ptr [rax+4],0
    je      .4
    add     rax,6
    jmp     .3
.4:
    xor     eax,eax
    jmp     .0
.2:
    add     rax,2
.1:
    add     rax,2
.0:
    ret

wcschr endp

    end
