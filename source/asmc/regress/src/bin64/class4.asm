
; v2.30.33 - : public class

ifndef __ASMC64__
    .x64
    .model flat, fastcall
endif

    option win64:2
    option casemap:none

.class template_c

    c byte ?

    .ends

.class C : public template_c

    c proc :byte

    .ends

    .data
    c C { { 0, 'C' } }

    .code

foo proc ptr_c: ptr C

    mov c.c,C

    c.c(c.c)
    ptr_c.c(c.c)
    ret

foo endp

    end
