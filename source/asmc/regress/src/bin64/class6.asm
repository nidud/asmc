
    ; 2.31.53 - inline resolved in first pass

ifndef __ASMC64__
    .x64
    .model flat, fastcall
endif

.class Base
    Attribute proc
    .ends

.class Memory : public Base
    ;
    ; Memory_Attribute equ <Base_Attribute>
    ;
    .ends

    .code

Base::Attribute proc
    ret
Base::Attribute endp

    ; - error A2005: symbol redefinition : Memory_Attribute

Memory::Attribute proc
    ret
Memory::Attribute endp

    end
