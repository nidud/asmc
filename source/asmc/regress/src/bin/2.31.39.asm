
    ; typeid( [id,] expression )

    .x64
    .model flat, fastcall

    option casemap:none
    option win64:auto

.enum type_identifier {

    T_IMM32,
    T_IMM64,
    T_IMM128,
    T_IMMFLT,

    T_REG8,
    T_REG16,
    T_REG32,
    T_REG64,
    T_REG128,
    T_REG256,
    T_REG512,

    T_BYTE,
    T_SBYTE,
    T_WORD,
    T_SWORD,
    T_REAL2,
    T_DWORD,
    T_SDWORD,
    T_REAL4,
    T_FWORD,
    T_QWORD,
    T_SQWORD,
    T_REAL8,
    T_TBYTE,
    T_REAL10,
    T_OWORD,
    T_REAL16,
    T_YWORD,
    T_ZWORD,
    T_PROC,
    T_NEAR,
    T_FAR,
    T_PTR,

    T_PBYTE,
    T_PSBYTE,
    T_PWORD,
    T_PSWORD,
    T_PREAL2,
    T_PDWORD,
    T_PSDWORD,
    T_PREAL4,
    T_PFWORD,
    T_PQWORD,
    T_PSQWORD,
    T_PREAL8,
    T_PTBYTE,
    T_PREAL10,
    T_POWORD,
    T_PREAL16,
    T_PYWORD,
    T_PZWORD,
    T_PPROC,
    T_PNEAR,
    T_PFAR,
    T_PPTR,
    T_PVOID
    }

.template s1

    m1  dq ?
    m2  db ?

    .ends

types proto args:vararg {
    for arg,<args>
        mov eax,typeid(T_, arg)
        endm
        }

    ostream typedef ptr
    cout    equ <ostream::>

.template ostream

    .inline ostreamPs1 :ptr s1 {
        mov rax,[_1].s1.m1
        }
    .inline ostreamPSBYTE :ptr sbyte {
        mov rax,_1
        }
    .inline ostreamPWORD :ptr word {
        mov rax,_1
        }
    .operator << :abs {
        cout typeid(ostream, _1)(_1)
        }
    .ends

    .code

main proc

    local pb:ptr sbyte
    local pc:ptr word
    local s:s1
    local ps:ptr s1

    types( 1, 10000000, 2.0, s.m1, s.m2 )
    types( al, ax, eax, rax, xmm0, ymm0, zmm0 )

    cout << pb << pc << ps
    cout << "Ascii string" << ( L"Unicode string" )
    ret

main endp

    end
