
    ; 2.31.38 - typeid( expression )

ifndef __ASMC64__
    .x64
    .model flat, fastcall
endif

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

types proto args:vararg {
    for arg,<args>
        mov eax,typeid(T_, arg)
        endm
        }

    ostream typedef ptr
    cout    equ <ostream::>

.template ostream

    .inline PSBYTE :ptr sbyte {
        mov rax,_1
        }
    .inline PWORD :ptr word {
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
