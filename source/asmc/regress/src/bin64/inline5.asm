
    ; 2.32.16

ifndef __ASMC64__
    .x64
    .model flat, fastcall
endif

    option casemap:none
    option win64:auto

inline proto a:ptr, b:abs=<2>, c:abs=<3> {
    mov rdx,a
    mov eax,b
    mov ecx,c
    }

    .code

foo proc p:ptr

    inline()
    inline(1)
    inline(4,5,6)
    ret

foo endp

    end
