; ALLOCA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc

    .code

    option stackbase:esp

alloca proc byte_count:UINT

    mov     ecx,[esp]   ; return address
    mov     eax,[esp+4] ; size to probe
    add     esp,8
@@:
    cmp     eax,_PAGESIZE_
    jb      @F
    sub     esp,_PAGESIZE_
    test    [esp],eax
    sub     eax,_PAGESIZE_
    jmp     @B
@@:
    sub     esp,eax
    and     esp,-16     ; align 16
    mov     eax,esp
    sub     esp,4
    test    [esp],eax   ; probe page
    jmp     ecx

alloca endp

    end
