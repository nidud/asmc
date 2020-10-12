
    ; inline resolved in first pass

    .x64
    .model flat, fastcall

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
