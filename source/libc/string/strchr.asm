; STRCHR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

    option dotname

strchr proc string:string_t, chr:int_t

    ldr     rax,string
    ldr     ecx,chr
    movzx   ecx,cl
.3:
    cmp     cl,[rax]
    je      .0
    cmp     ch,[rax]
    je      .4
    cmp     cl,[rax+1]
    je      .1
    cmp     ch,[rax+1]
    je      .4
    cmp     cl,[rax+2]
    je      .2
    cmp     ch,[rax+2]
    je      .4
    add     rax,3
    jmp     .3
.4:
    xor     eax,eax
    jmp     .0
.2:
    inc     rax
.1:
    inc     rax
.0:
    ret

strchr endp

    end
