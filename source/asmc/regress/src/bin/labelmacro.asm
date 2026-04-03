; v2.37.91 - label:macro()
; regression from v2.37.83 - @ramonsala

.486
.model flat, c

TextStr MACRO quoted_text:VARARG
    LOCAL ECvname
.Data
    ECvname DB quoted_text,0
.Code
    EXITM <offset ECvname>
ENDM

.code

foo proc a:ptr
    ret
    endp

bar proc
    foo(TextStr("string"))
@@: foo(TextStr("string"))
    ret
    endp
    end
