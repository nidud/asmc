
    ; constructor not added to class...

    .x64
    .model flat, fastcall

    option casemap:none
    option win64:auto

.template template

    atom        db ?

    template    proc :ptr
    Release     proc

    .ends

.template template1
    atom        db ?
    .operator template1 :ptr {
        nop
        exitm<>
        }
    .ends

.comdef comdef
    atom        db ?
    comdef      proc :ptr
    .ends

.comdef comdef1
    atom        db ?
    .operator comdef1 :ptr {
        nop
        exitm<>
        }
    .ends

.class class
    atom        db ?
    class       proc :ptr
    .ends

.class class1
    atom        db ?
    .operator class1 :ptr {
        nop
        exitm<>
        }
    .ends

    .code

main proc

    .new t:template("template")
    .new c:comdef("comdef")
    .new C:class("class")

    .new t1:template1("template")
    .new c1:comdef1("comdef")
    .new C1:class1("class")

    template("template")
    comdef("comdef")
    class("class")

    template1("template")
    comdef1("comdef")
    class1("class")
    ret

main endp

template::template proc p:ptr
    ret
template::template endp

comdef::comdef proc p:ptr
    ret
comdef::comdef endp

class::class proc p:ptr
    ret
class::class endp

    end
