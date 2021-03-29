; TYPEID.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

.enum typeid_types {

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
    T_NEAR,
    T_FAR,

    T_PVOID,
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
    T_PPTR,
    T_PNEAR
    }

RECT STRUC
left dd ?
RECT ENDS

types proto args:vararg {
    for arg,<args>
        %echo typeid(arg)
        endm
        }

    .code

main proc a:ptr

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
    local rc:RECT

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
    local prc:ptr RECT

    types( 1, 1000000000000, 10000000000000000000000000, 1.0 )
    types( al, ax, eax, rax, xmm0, ymm0, zmm0, es )
    types( ma, mb, mc, md, me, mf, mg, mh, mi, mj, mk, ml, mm, mn, mo, mp, mq, mr, ms, mt, mu, mv, rc )
    types( pa, pb, pc, pd, pe, pf, pg, ph, pi, pj, pk, pl, pm, pn, po, pp, pq, pr, ps, pt, pu, pv, prc )
    types( main, addr main )

    ret

main endp

    end
