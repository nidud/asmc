ifndef __XMMMACROS_INC
__XMMMACROS_INC equ <>

FLT4 macro value
  local string
    string textequ <FLT4@>
    forc q,<value>
        ifidn <q>,<->
            string CatStr string, <M>
        elseifidn <q>,<+>
            string CatStr string, <P>
        elseifidn <q>,< >
            string CatStr string, <_>
        elseifidn <q>,<*>
            string CatStr string, <x>
        elseifidn <q>,</>
            string CatStr string, <d>
        elseifidn <q>,<.>
            string CatStr string, <_>
        else
            string CatStr string, <q>
        endif
        endm
%   ifndef string
        .data
        align 4
        string label REAL4
            dd value
        .code
    endif
    exitm<string>
    endm

FLT8 macro value
  local string
    string textequ <FLT8@>
    forc q,<value>
        ifidn <q>,<->
            string CatStr string, <M>
        elseifidn <q>,<+>
            string CatStr string, <P>
        elseifidn <q>,< >
            string CatStr string, <_>
        elseifidn <q>,<*>
            string CatStr string, <x>
        elseifidn <q>,</>
            string CatStr string, <d>
        elseifidn <q>,<.>
            string CatStr string, <_>
        elseifidn <q>,<(>
            exitm
        else
            string CatStr string, <q>
        endif
        endm
%   ifndef string
        .data
        align 8
        string label REAL8
            dq value
        .code
    endif
    exitm<string>
    endm

_MM_ISXMM macro op
    if (typeof op) eq 16 and (opattr op) eq 48
        exitm<1>
    else
        exitm<0>
    endif
    endm

_MM_MREG macro op
    if (opattr op) eq 48 and (typeof op) ne 16
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
    elseifidn <sx>,<sd>
        move equ <movsd>
    else
        move equ <mova&sx&>
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
  local retval
    if _MM_ISXMM(a)
        retval equ <a>
    else
        retval equ <xmm0>
        movaps retval,_MM_MREG(a)
    endif
    shuf&sx& retval,b,imm
    retm<retval>
    endm

_mm_loadreg macro reg, arg
    ifidn @SubStr(arg,1,1),<&>
        lea reg,@SubStr(arg,2)
    elseifdif <arg>,<reg>
        mov reg,arg
    endif
    retm<reg>
    endm

_mm_storereg macro lp, reg, tmp:=<rcx>
    ifidn @SubStr(lp,1,1),<&>
        mov @SubStr(lp,2),reg
    elseif (opattr lp) eq 48
        mov [lp],reg
    else
        mov tmp,lp
        mov [tmp],reg
    endif
    retm<>
    endm

_mm_getptr macro arg, reg:=<rax>
    ifidn @SubStr(arg,1,1),<&>
        lea reg,@SubStr(arg,2)
        exitm<[reg]>
    elseifidn @SubStr(arg,1,1),<[>
        exitm<arg>
    elseif (opattr arg) eq 48
        exitm<[arg]>
    endif
    exitm<arg>
    endm

endif
