; PRAGMA.ASM--
; .pragma(init(<proc>, <priority>))
; .pragma(exit(<proc>, <priority>))
; .pragma(pack(push, <alignment>))
; .pragma(pack(pop))

ifndef __ASMC64__
    .x64
    .model flat
endif

TYPE_ALIGNMENT macro t
    local S1
    S1 STRUC
    l1 db ?
    l2 t ?
    S1 ENDS
    exitm<S1.l2>
    endm

ALIGNMENT equ 4

    .code

    mov al,TYPE_ALIGNMENT(OWORD)
.pragma pack push ALIGNMENT
    mov al,TYPE_ALIGNMENT(OWORD)
.pragma(pack(push, 16))
    mov al,TYPE_ALIGNMENT(OWORD)
.pragma(pack(pop))
    mov al,TYPE_ALIGNMENT(OWORD)
.pragma pack pop
    mov al,TYPE_ALIGNMENT(OWORD)

foo:

.pragma init foo 1
.pragma(init(foo, 1))

.pragma exit foo 1
.pragma(exit(foo, 1))


    end
