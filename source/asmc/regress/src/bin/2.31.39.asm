
    ; typeid( [id,] expression )

    .x64
    .model flat, fastcall

    option casemap:none
    option win64:auto

.enum type_identifier {

    imm_32,
    imm_64,
    imm_128,
    imm_float,

    reg_8,
    reg_16,
    reg_32,
    reg_64,
    reg_128,
    reg_256,
    reg_512,

    mem_byte,
    mem_sbyte,
    mem_word,
    mem_sword,
    mem_real2,
    mem_dword,
    mem_sdword,
    mem_real4,
    mem_fword,
    mem_qword,
    mem_sqword,
    mem_real8,
    mem_tbyte,
    mem_real10,
    mem_oword,
    mem_real16,
    mem_yword,
    mem_zword,
    mem_proc,
    mem_near,
    mem_far,
    mem_ptr,

    ptr_byte,
    ptr_sbyte,
    ptr_word,
    ptr_sword,
    ptr_real2,
    ptr_dword,
    ptr_sdword,
    ptr_real4,
    ptr_fword,
    ptr_qword,
    ptr_sqword,
    ptr_real8,
    ptr_tbyte,
    ptr_real10,
    ptr_oword,
    ptr_real16,
    ptr_yword,
    ptr_zword,
    ptr_proc,
    ptr_near,
    ptr_far,
    ptr_ptr,
    ptr_void
    }

.template s1

    m1  dq ?
    m2  db ?

    .ends

types proto args:vararg {
    for arg,<args>
        mov eax,typeid(arg)
        endm
        }

    ostream typedef ptr
    cout    equ <ostream::>

.template ostream

    .operator ostream?ps1 :ptr s1 {
        mov rax,[_1].s1.m1
        }
    .operator ostream?psbyte :ptr sbyte {
        mov rax,_1
        }
    .operator ostream?pword :ptr word {
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
