;
; v2.33.56 - .enum { a = '}', b = '{' }
;
ifndef __ASMC64__
    .x64
    .model flat
endif
    .code
    option casemap:none

    .enum {
        a = '}',
        b = '{'
        }

    mov al,a
    mov al,b

    end
