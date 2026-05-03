
include DrawingObject.inc

ROUND_DOUBLE_TO_LONG macro x
    mov       rax,0.5
    movq      xmm0,rax
    addsd     xmm0,x
    movq      r10,xmm0
    shr       r10,63
    cvttsd2si rax,xmm0
    sub       rax,r10
    exitm<eax>
    endm

    .code

    assume class:rcx

CDrawingObject::CDrawingObject proc

    .if @ComAlloc(CDrawingObject)

        mov rcx,rax
        mov s_colors[0x00],RGB(0, 0, 0)     ;; black
        mov s_colors[0x04],RGB(255, 255, 0) ;; yellow
        mov s_colors[0x08],RGB(255, 0, 0)   ;; red
        mov s_colors[0x0C],RGB(0, 255, 0)   ;; green
        mov s_colors[0x10],RGB(0, 0, 255)   ;; blue
    .endif
    ret
    endp

CDrawingObject::Release proc
    free(rcx)
    ret
    endp

CDrawingObject::ToggleDrawDiagonals proc
    mov eax,_bDrawDiagonals
    not eax
    mov _bDrawDiagonals,eax
    ret
    endp

CDrawingObject::ShiftColor proc
    inc _iColorIndex
    .if ( _iColorIndex == MAX_COLORS )
        mov _iColorIndex,0
    .endif
    ret
    endp

CDrawingObject::ResetObject proc cxClient:int_t, cyClient:int_t

    ldr edx,cxClient
    ldr eax,cyClient

    shr edx,1
    shr eax,1
    mov _iCx,edx
    mov _iCy,eax
    mov _iWidth,edx
    mov _iHeight,eax
    mov rax,1.0
    mov _dScalingFactor,rax
    mov _dRotationAngle,0.0
    mov _bDrawDiagonals,FALSE
    mov _iColorIndex,0
    ret
    endp

    assume class:rbx

CDrawingObject::Paint proc hdc:HDC

  local hPen:HPEN
  local hPenOld:HGDIOBJ
  local ptRect[5]:POINT

    mov         eax,_iColorIndex
    mov         ecx,s_colors[rax*4]
    mov         hPen,CreatePen(PS_SOLID, 1, ecx)
    mov         hPenOld,SelectObject(hdc, hPen)

    mov         eax,_iWidth
    shr         eax,1
    cvtsi2sd    xmm0,eax
    mulsd       xmm0,_dScalingFactor
    cvtsd2si    eax,xmm0
    mov         ptRect[1*8].x,eax
    mov         ptRect[2*8].x,eax
    neg         eax
    mov         ptRect[0*8].x,eax
    mov         ptRect[3*8].x,eax
    mov         eax,_iHeight
    shr         eax,1
    cvtsi2sd    xmm0,rax
    mulsd       xmm0,_dScalingFactor
    cvtsd2si    rax,xmm0
    mov         ptRect[2*8].y,eax
    mov         ptRect[3*8].y,eax
    neg         eax
    mov         ptRect[0*8].y,eax
    mov         ptRect[1*8].y,eax
    mov         rax,ptRect[0*8]
    mov         ptRect[4*8],rax
    movsd       xmm4,cos(_dRotationAngle)
    movsd       xmm5,sin(_dRotationAngle)

    .for ( ecx = 0 : ecx < 5 : ecx++ )

        mov         eax,ptRect[rcx*8].x
        cvtsi2sd    xmm0,rax
        mov         eax,ptRect[rcx*8].y
        cvtsi2sd    xmm1,rax
        movsd       xmm2,xmm0
        movsd       xmm3,xmm1
        mulsd       xmm2,xmm4
        mulsd       xmm3,xmm5
        addsd       xmm2,xmm3
        cvtsd2si    rax,xmm2
        mov         ptRect[rcx*8].x,eax
        mulsd       xmm1,xmm4
        mulsd       xmm0,xmm5
        subsd       xmm1,xmm0
        cvtsd2si    rax,xmm1
        mov         ptRect[rcx*8].y,eax
    .endf
    .for ( eax = _iCx, edx = _iCy, ecx = 0 : ecx < 5 : ecx++ )
        add ptRect[rcx*8].x,eax
        add ptRect[rcx*8].y,edx
    .endf
    Polyline(hdc, &ptRect, 5)
    .if ( _bDrawDiagonals )
        MoveToEx(hdc, ptRect[0*8].x, ptRect[0*8].y, NULL)
        LineTo  (hdc, ptRect[2*8].x, ptRect[2*8].y)
        MoveToEx(hdc, ptRect[1*8].x, ptRect[1*8].y, NULL)
        LineTo  (hdc, ptRect[3*8].x, ptRect[3*8].y)
    .endif
    SelectObject(hdc, hPenOld)
    DeleteObject(hPen)
    ret
    endp

    assume class:rcx

CDrawingObject::Move proc ldx:long_t, ldy:long_t
    add _iCx,ldr(ldx)
    add _iCy,ldr(ldy)
    ret
    endp

CDrawingObject::Zoom proc dZoomFactor:double, iZx:long_t, iZy:long_t

    mov         rax,1.0
    movq        xmm0,rax
    subsd       xmm0,xmm1
    cvtsi2sd    xmm2,ldr(iZx)
    cvtsi2sd    xmm3,ldr(iZy)
    mov         eax,_iCx
    cvtsi2sd    xmm4,rax
    mov         eax,_iCy
    cvtsi2sd    xmm5,rax
    mulsd       xmm4,xmm1
    mulsd       xmm5,xmm1
    mulsd       xmm2,xmm0
    mulsd       xmm3,xmm0
    addsd       xmm2,xmm4
    addsd       xmm3,xmm5
    mulsd       xmm0,_dScalingFactor
    movsd       _dScalingFactor,xmm0
    mov         _iCx,ROUND_DOUBLE_TO_LONG(xmm2)
    mov         _iCy,ROUND_DOUBLE_TO_LONG(xmm3)
    ret
    endp

    assume class:rbx

CDrawingObject::Rotate proc dAngle:double, iOx:long_t, iOy:long_t

    movsd       xmm0,_dRotationAngle
    addsd       xmm0,xmm1
    movsd       _dRotationAngle,xmm0

    movsd       xmm5,xmm1
    movsd       xmm4,cos(xmm1)
    movsd       xmm5,sin(xmm5)

    mov         eax,_iCx
    sub         eax,iOx
    cvtsi2sd    xmm1,rax
    mov         eax,_iCy
    sub         eax,iOy
    cvtsi2sd    xmm2,rax
    movsd       xmm0,xmm1
    mulsd       xmm0,xmm4
    movsd       xmm3,xmm2
    mulsd       xmm3,xmm5
    addsd       xmm3,xmm0
    add         ROUND_DOUBLE_TO_LONG(xmm3),iOx
    mov         _iCx,eax

    mulsd       xmm2,xmm4
    mulsd       xmm1,xmm5
    subsd       xmm2,xmm1
    add         ROUND_DOUBLE_TO_LONG(xmm2),iOy
    mov         _iCy,eax
    ret
    endp

    end
