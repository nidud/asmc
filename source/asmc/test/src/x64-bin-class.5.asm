
    ; 2.31.53 - inline resolved in first pass

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
    endp

    ; - error A2005: symbol redefinition : Memory_Attribute

Memory::Attribute proc
    ret
    endp

    end
