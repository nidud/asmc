
    ; 2.31.38 - typeid( expression )

ifndef __ASMC64__
    .x64
    .model flat, fastcall
endif

    option casemap:none
    option win64:auto

.enum type_identifier {

    T_imm,
    T_flt,

    T_byte,
    T_sbyte,
    T_word,
    T_sword,
    T_real2,
    T_dword,
    T_sdword,
    T_real4,
    T_fword,
    T_qword,
    T_sqword,
    T_real8,
    T_tbyte,
    T_real10,
    T_oword,
    T_real16,
    T_yword,
    T_zword,
    T_proc,
    T_near,
    T_far,
    T_ptr,

    T_ptrbyte,
    T_ptrsbyte,
    T_ptrword,
    T_ptrsword,
    T_ptrreal2,
    T_ptrdword,
    T_ptrsdword,
    T_ptrreal4,
    T_ptrfword,
    T_ptrqword,
    T_ptrsqword,
    T_ptrreal8,
    T_ptrtbyte,
    T_ptrreal10,
    T_ptroword,
    T_ptrreal16,
    T_ptryword,
    T_ptrzword,
    T_ptrproc,
    T_ptrnear,
    T_ptrfar,
    T_ptrptr,
    T_R,
    T_ptrptrR
    }

types proto args:vararg {
    for arg,<args>
        mov eax,typeid(T_, arg)
        endm
        }

.template R
    x dd ?
    y dd ?
   .ends
   PR typedef ptr ptr R

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
    local r:R
    local ppr:PR

    types( 1, 1.0, al, ax, eax, rax, xmm0, ymm0, zmm0, [rax], r, ppr )
    types( ma, mb, mc, md, me, mf, mg, mh, mi, mj, mk, ml, mm, mn, mo, mp, mq, mr, ms, mt, mu, mv )
    types( pa, pb, pc, pd, pe, pf, pg, ph, pi, pj, pk, pl, pm, pn, po, pp, pq, pr, ps, pt, pu, pv )
    types( main, addr main )
    ret

main endp

    end
