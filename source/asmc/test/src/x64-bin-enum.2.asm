;
; v2.33.56 - .enum { a = '}', b = '{' }
;
    .code
    option casemap:none

    .enum {
        a = '}',
        b = '{'
        }

    mov al,a
    mov al,b

    end
