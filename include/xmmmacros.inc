ifndef __XMMMACROS_INC
__XMMMACROS_INC equ <>

FLT4 macro value
    local m
    .data
    m REAL4 value
    .code
    exitm<m>
    endm

FLT8 macro value
    local m
    .data
    align 8
    m REAL8 value
    .code
    exitm<m>
    endm

_MM_ISXMM macro op
    if (type op) eq 16 and (opattr op) eq 48
        exitm<1>
    else
        exitm<0>
    endif
    endm

_MM_MREG macro op
    if (opattr op) eq 48 and (type op) ne 16
        exitm<[op]>
    else
        exitm<op>
    endif
    endm

_MM_STORE_SS macro x, f
    if _MM_ISXMM(f)
        ifdif <x>,<f>
            movss x,f
        endif
    else
       movd x,FLT4(f)
    endif
    retm<x>
    endm

_MM_OPCSX2 macro op, sx, a, b
  local retval, source, move
    ifidn <sx>,<ss>
        move equ <movss>
    else
        move equ <movaps>
    endif
    if _MM_ISXMM(a)
        retval equ <a>
        source equ <b>
    else
        ifidn <b>,<xmm0>
            move xmm1,xmm0
            source equ <xmm1>
        else
            source equ <b>
        endif
        retval equ <xmm0>
        move retval,_MM_MREG(a)
    endif
    &op&&sx& retval,source
    retm<retval>
    endm

_MM_SHUFXX macro sx, a, b, imm
  local retval, source
    if _MM_ISXMM(a)
        retval equ <a>
    else
        retval equ <xmm0>
        movaps retval,_MM_MREG(a)
    endif
    ifidn <b>,<a>
        source equ <retval>
    else
        if _MM_ISXMM(b)
            source equ <b>
        else
            source equ <xmm1>
            movaps source,_MM_MREG(b)
        endif
    endif
    shuf&sx& retval,source,imm
    retm<retval>
    endm

endif
