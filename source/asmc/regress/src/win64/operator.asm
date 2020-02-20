
; v2.31: .operator

    option win64:3

.template operator

    vector qword ?

    ; Arithmetic Operators

    .operator +     ; radd  - Add
    .operator -     ; rsub  - Subtract
    .operator *     ; rmul  - Multiply
    .operator /     ; rdiv  - Divide
    .operator %     ; rmod  - Modulus
    .operator ++    ; rinc  - Increment
    .operator --    ; rdec  - Decrement

    ; Bitwise Operators

    .operator &     ; rand  - Binary AND Operator
;   .operator |     ; ror   - Binary OR Operator
    .operator ^     ; rxor  - Binary XOR Operator
    .operator ~     ; rnot  - Binary Ones Complement Operator
    .operator &~    ; randn - Binary AND NOT Operator
    .operator <<    ; rshl  - Binary Left Shift Operator
    .operator >>    ; rshr  - Binary Right Shift Operator

    ; Assignment Operators

    .operator =     ; mequ  - Simple assignment operator
    .operator +=    ; madd  - Add AND assignment operator
    .operator -=    ; msub  - Subtract AND assignment operator
    .operator *=    ; mmul  - Multiply AND assignment operator
    .operator /=    ; mdiv  - Divide AND assignment operator
    .operator %=    ; mmod  - Modulus AND assignment operator
    .operator ~=    ; mnot  - Bitwise NOT assignment operator
    .operator <<=   ; mshl  - Left shift AND assignment operator
    .operator >>=   ; mshr  - Right shift AND assignment operator
    .operator &=    ; mand  - Bitwise AND assignment operator
    .operator &~=   ; mandn - Bitwise AND NOT assignment operator
    .operator ^=    ; mxor  - Bitwise exclusive OR and assignment operator
    .operator |=    ; mand  - Bitwise inclusive OR and assignment operator


    .operator = :qword {
        mov [this],_1
        retm<this>
        }

    .operator = :dword, :dword {
        mov dword ptr [this+0],_1
        mov dword ptr [this+4],_2
        retm<this>
        }

    .operator = :word, :word, :word, :word {
        mov word ptr [this+0],_1 ; edx
        mov word ptr [this+2],_2 ; r8w
        mov word ptr [this+4],_3 ; r9w
        mov word ptr [this+6],_4 ; [rsp+4*8]
        retm<this>
        }
    .operator = :abs, :abs, :abs, :abs {
        mov word ptr [this+0],_1 ; 1
        mov word ptr [this+2],_2 ; 2
        mov word ptr [this+4],_3 ; 3
        mov word ptr [this+6],_4 ; 4
        retm<this>
        }

    .ends

    .code

foo proc p:ptr operator

    assume rcx:ptr operator

    [rcx].radd()
    [rcx].rsub()
    [rcx].rmul()
    [rcx].rdiv()
    [rcx].rmod()
    [rcx].rinc()
    [rcx].rdec()

    ; Bitwise Operators

    [rcx].rand()
;   [rcx].ror()
    [rcx].rxor()
    [rcx].rnot()
    [rcx].randn()
    [rcx].rshl()
    [rcx].rshr()

    ; Assignment Operators

    [rcx].mequ()
    [rcx].madd()
    [rcx].msub()
    [rcx].mmul()
    [rcx].mdiv()
    [rcx].mmod()
    [rcx].mnot()
    [rcx].mshl()
    [rcx].mshr()
    [rcx].mand()
    [rcx].mandn()
    [rcx].mxor()
    [rcx].mand()

    [rcx].mequ8(8)
    [rcx].mequ44(4, 4)
    [rcx].mequ222(2, 2, 2, 2)
    [rcx].mequ888(1, 2, 3, 4)
    ret

foo endp

    end
