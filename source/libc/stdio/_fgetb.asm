; _FGETB.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

    .code

    option dotname
    assume rbx:LPFILE

_fgetb proc uses rbx fp:LPFILE, count:int_t

    ldr     rbx,fp
    ldr     ecx,count
.0:
    cmp     ecx,[rbx]._bitcnt
    ja      .2
    mov     eax,[rbx]._charbuf
    sub     [rbx]._bitcnt,ecx   ; dec bit count
    shr     [rbx]._charbuf,cl   ; dump used bits
    mov     edx,1
    shl     edx,cl
    dec     edx
    and     eax,edx
.1:
    ret
.2:
    cmp     ecx,16
    ja      .5
    dec     [rbx]._cnt
    jl      .4
    mov     rdx,[rbx]._ptr
    inc     [rbx]._ptr
    movzx   eax,byte ptr [rdx]
.3:
    mov     ch,cl
    mov     cl,byte ptr [rbx]._bitcnt
    mov     edx,1
    shl     eax,cl
    shl     edx,cl
    dec     edx
    and     [rbx]._charbuf,edx
    or      [rbx]._charbuf,eax
    add     [rbx]._bitcnt,8
    shr     ecx,8
    jmp     .0
.4:
    invoke  _filbuf,rbx
    cmp     eax,-1
    je      .1
    mov     ecx,count
    jmp     .3
.5:
    mov     eax,-1
    jmp     .1

_fgetb endp

    end
