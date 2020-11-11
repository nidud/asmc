
    ; typeid( expression )

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

types proto args:vararg {
    for arg,<args>
        mov eax,typeid(arg)
        endm
        }

    ostream typedef ptr
    cout    equ <ostream::>

.template ostream

    .operator ptr_sbyte :ptr sbyte {
        mov rax,_1
        }
    .operator ptr_word :ptr word {
        mov rax,_1
        }
    .operator << :abs {
        cout typeid(_1)(_1)
        }
    .ends

    .code

main proc

    local ma:byte
    local mb:sbyte
    local mc:word
    local md:sword
    local me:real2
    local mf:dword
    local mg:sdword
    local mh:real4
    local mi:fword
    local mj:qword
    local mk:sqword
    local ml:real8
    local mm:tbyte
    local mn:real10
    local mo:oword
    local mp:real16
    local mq:yword
    local mr:zword
    local ms:proc
    local mt:near
    local mu:far
    local mv:ptr

    local pa:ptr byte
    local pb:ptr sbyte
    local pc:ptr word
    local pd:ptr sword
    local pe:ptr real2
    local pf:ptr dword
    local pg:ptr sdword
    local ph:ptr real4
    local pi:ptr fword
    local pj:ptr qword
    local pk:ptr sqword
    local pl:ptr real8
    local pm:ptr tbyte
    local pn:ptr real10
    local po:ptr oword
    local pp:ptr real16
    local pq:ptr yword
    local pr:ptr zword
    local ps:ptr proc
    local pt:ptr near
    local pu:ptr far
    local pv:ptr ptr

    types( ma, mb, mc, md, me, mf, mg, mh, mi, mj, mk, ml, mm, mn, mo, mp, mq, mr, ms, mt, mu, mv )
    types( pa, pb, pc, pd, pe, pf, pg, ph, pi, pj, pk, pl, pm, pn, po, pp, pq, pr, ps, pt, pu, pv )
    types( main, addr main )

    cout << pb << pc
    cout << "Ascii string" << ( L"Unicode string" )
    ret

main endp

    end
