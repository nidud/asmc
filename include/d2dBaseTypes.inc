ifndef _D2DBASETYPES_INCLUDED
_D2DBASETYPES_INCLUDED equ <>

ifndef COM_NO_WINDOWS_H
include windows.inc
endif

ifndef D3DCOLORVALUE_DEFINED
D3DCOLORVALUE_DEFINED equ <>

sc_redShift     equ 16
sc_greenShift   equ 8
sc_blueShift    equ 0

sc_redMask      equ (0xff shl sc_redShift)
sc_greenMask    equ (0xff shl sc_greenShift)
sc_blueMask     equ (0xff shl sc_blueShift)

.template D3DCOLORVALUE

    r real4 ?
    g real4 ?
    b real4 ?
    a real4 ?

    .operator D3DCOLORVALUE :vararg {
        ifidn typeid(?, this),<?D3DCOLORVALUE>
            this.Init(_1)
        else
            [rcx].D3DCOLORVALUE.typeid(D3DCOLORVALUE, this)(_1)
        endif
        }

    .operator D3DCOLORVALUE?i32 :vararg {
      local n
       .new n:D3DCOLORVALUE
        n.Init(_1)
        }

    .operator Init :abs, :abs, :vararg {
        ifidn typeid(?, this),<?D3DCOLORVALUE>
            lea rcx,this
        endif
        ifnb <_2>
            ifidn typeid(?, _2),<?r128>
                movss [rcx].D3DCOLORVALUE.a,_2
            else
                mov [rcx].D3DCOLORVALUE.a,_2
            endif
        endif
        ifnb <_1>
            ifidn typeid(?, _1),<?i32>
               %mov [rcx].D3DCOLORVALUE.r, @CatStr(%((_1 and sc_redMask) shr sc_redShift),     <.0>) / 255.0
               %mov [rcx].D3DCOLORVALUE.g, @CatStr(%((_1 and sc_greenMask) shr sc_greenShift), <.0>) / 255.0
               %mov [rcx].D3DCOLORVALUE.b, @CatStr(%((_1 and sc_blueMask) shr sc_blueShift),   <.0>) / 255.0
            else
                mov      eax,_1
                and      eax,sc_redMask
                shr      eax,sc_redShift
                cvtsi2ss xmm0,eax
                divss    xmm0,255.0
                movss    [rcx].D3DCOLORVALUE.r,xmm0
                mov      eax,_1
                and      eax,sc_greenMask
                shr      eax,sc_greenShift
                cvtsi2ss xmm0,eax
                divss    xmm0,255.0
                movss    [rcx].D3DCOLORVALUE.g,xmm0
                mov      eax,_1
                and      eax,sc_blueMask
                shr      eax,sc_blueShift
                cvtsi2ss xmm0,eax
                divss    xmm0,255.0
                movss    [rcx].D3DCOLORVALUE.b,xmm0
            endif
        endif
        mov rax,rcx
        }
    .ends
endif

D2D_POINT_2U STRUC
    x UINT ?
    y UINT ?
D2D_POINT_2U ENDS

D2D_POINT_2F STRUC
    x real4 ?
    y real4 ?
D2D_POINT_2F ENDS

D2D_RECT_F STRUC
    left   real4 ?
    top    real4 ?
    right  real4 ?
    bottom real4 ?
D2D_RECT_F ENDS

D2D_RECT_U STRUC
    left   UINT ?
    top    UINT ?
    right  UINT ?
    bottom UINT ?
D2D_RECT_U ENDS

D2D_SIZE_F STRUC
    width  real4 ?
    height real4 ?
D2D_SIZE_F ENDS

D2D_SIZE_U STRUC
    width  UINT ?
    height UINT ?
D2D_SIZE_U ENDS

D2D_COLOR_F typedef D3DCOLORVALUE

D2D_MATRIX_3X2_F STRUC
    _11 real4 ?
    _12 real4 ?
    _21 real4 ?
    _22 real4 ?
    _31 real4 ?
    _32 real4 ?
D2D_MATRIX_3X2_F ENDS

endif

