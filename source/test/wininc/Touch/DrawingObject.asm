
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

    assume rdi:ptr CDrawingObject

CDrawingObject::CDrawingObject proc uses rsi rdi

    mov rsi,rcx

    .repeat

        .break .if !malloc( sizeof(CDrawingObject) + sizeof(CDrawingObjectVtbl) )
        mov rdi,rax

        add rax,sizeof(CDrawingObject)
        mov [rdi].lpVtbl,rax

        mov [rdi].s_colors[0x00],RGB(0, 0, 0)     ;; black
        mov [rdi].s_colors[0x04],RGB(255, 255, 0) ;; yellow
        mov [rdi].s_colors[0x08],RGB(255, 0, 0)   ;; red
        mov [rdi].s_colors[0x0C],RGB(0, 255, 0)   ;; green
        mov [rdi].s_colors[0x10],RGB(0, 0, 255)   ;; blue

        mov rcx,rax
        lea rax,CDrawingObject_Release
        mov [rcx+0x00],rax
        lea rax,CDrawingObject_ResetObject
        mov [rcx+0x08],rax
        lea rax,CDrawingObject_Paint
        mov [rcx+0x10],rax
        lea rax,CDrawingObject_Move
        mov [rcx+0x18],rax
        lea rax,CDrawingObject_ToggleDrawDiagonals
        mov [rcx+0x20],rax
        lea rax,CDrawingObject_Zoom
        mov [rcx+0x28],rax
        lea rax,CDrawingObject_Rotate
        mov [rcx+0x30],rax
        lea rax,CDrawingObject_ShiftColor
        mov [rcx+0x38],rax

        mov rax,rdi
        mov rcx,rdi
        .if rsi
            mov [rsi],rax
        .endif
    .until 1
    ret

CDrawingObject::CDrawingObject endp

CDrawingObject::Release proc

    free(rcx)
    ret

CDrawingObject::Release endp

    assume rcx:ptr CDrawingObject

CDrawingObject::ToggleDrawDiagonals proc

    mov eax,[rcx]._bDrawDiagonals
    not eax
    mov [rcx]._bDrawDiagonals,eax
    ret

CDrawingObject::ToggleDrawDiagonals endp

CDrawingObject::ShiftColor proc

    inc [rcx]._iColorIndex
    .if ([rcx]._iColorIndex == MAX_COLORS)
        mov [rcx]._iColorIndex,0
    .endif
    ret

CDrawingObject::ShiftColor endp

CDrawingObject::ResetObject proc cxClient:int_t, cyClient:int_t

    shr edx,1
    shr r8d,1
    mov [rcx]._iCx,edx
    mov [rcx]._iCy,r8d
    mov [rcx]._iWidth,edx
    mov [rcx]._iHeight,r8d

    mov rax,1.0
    mov [rcx]._dScalingFactor,rax

    mov [rcx]._dRotationAngle,0.0
    mov [rcx]._bDrawDiagonals,FALSE
    mov [rcx]._iColorIndex,0
    ret

CDrawingObject::ResetObject endp

CDrawingObject::Paint proc uses rsi rdi hdc:HDC

  local hPen:HPEN
  local hPenOld:HGDIOBJ
  local ptRect[5]:POINT

    mov rdi,rcx
    mov eax,[rcx]._iColorIndex
    mov r8d,[rcx].s_colors[rax*4]
    mov hPen,CreatePen(PS_SOLID, 1, r8d)
    mov hPenOld,SelectObject(hdc, hPen)

    mov eax,[rdi]._iWidth
    shr eax,1
    cvtsi2sd xmm0,eax
    mulsd xmm0,[rdi]._dScalingFactor
    cvtsd2si eax,xmm0
    mov ptRect[1*8].x,eax
    mov ptRect[2*8].x,eax
    neg eax
    mov ptRect[0*8].x,eax
    mov ptRect[3*8].x,eax
    mov eax,[rdi]._iHeight
    shr eax,1
    cvtsi2sd xmm0,rax
    mulsd xmm0,[rdi]._dScalingFactor
    cvtsd2si rax,xmm0
    mov ptRect[2*8].y,eax
    mov ptRect[3*8].y,eax
    neg eax
    mov ptRect[0*8].y,eax
    mov ptRect[1*8].y,eax
    mov rax,ptRect[0*8]
    mov ptRect[4*8],rax

    movsd xmm4,cos([rdi]._dRotationAngle)
    movsd xmm5,sin([rdi]._dRotationAngle)

    .for (esi = 0: esi < 5: esi++)

        mov eax,ptRect[rsi*8].x
        cvtsi2sd xmm0,rax
        mov eax,ptRect[rsi*8].y
        cvtsi2sd xmm1,rax
        movsd xmm2,xmm0
        movsd xmm3,xmm1
        mulsd xmm2,xmm4
        mulsd xmm3,xmm5
        addsd xmm2,xmm3
        cvtsd2si rax,xmm2
        mov ptRect[rsi*8].x,eax

        mulsd xmm1,xmm4
        mulsd xmm0,xmm5
        subsd xmm1,xmm0
        cvtsd2si rax,xmm1
        mov ptRect[rsi*8].y,eax
    .endf

    .for (esi = 0: esi < 5: esi++)

        mov eax,[rdi]._iCx
        add ptRect[rsi*8].x,eax
        mov eax,[rdi]._iCy
        add ptRect[rsi*8].y,eax
    .endf

    Polyline(hdc, &ptRect, 5)

    .if ([rdi]._bDrawDiagonals)

        MoveToEx(hdc, ptRect[0*8].x, ptRect[0*8].y, NULL)
        LineTo  (hdc, ptRect[2*8].x, ptRect[2*8].y)
        MoveToEx(hdc, ptRect[1*8].x, ptRect[1*8].y, NULL)
        LineTo  (hdc, ptRect[3*8].x, ptRect[3*8].y)
    .endif

    SelectObject(hdc, hPenOld)
    DeleteObject(hPen)
    ret

CDrawingObject::Paint endp

CDrawingObject::Move proc ldx:long_t, ldy:long_t

    add [rcx]._iCx,edx
    add [rcx]._iCy,r8d
    ret

CDrawingObject::Move endp

CDrawingObject::Zoom proc dZoomFactor:double, iZx:long_t, iZy:long_t

    mov    rax,1.0
    movq   xmm0,rax
    subsd  xmm0,xmm1
    cvtsi2sd xmm2,r8
    cvtsi2sd xmm3,r9
    mov    eax,[rcx]._iCx
    cvtsi2sd xmm4,rax
    mov    eax,[rcx]._iCy
    cvtsi2sd xmm5,rax
    mulsd  xmm4,xmm1
    mulsd  xmm5,xmm1
    mulsd  xmm2,xmm0
    mulsd  xmm3,xmm0
    addsd  xmm2,xmm4
    addsd  xmm3,xmm5
    mulsd  xmm0,[rcx]._dScalingFactor
    movsd  [rcx]._dScalingFactor,xmm0
    mov    [rcx]._iCx,ROUND_DOUBLE_TO_LONG(xmm2)
    mov    [rcx]._iCy,ROUND_DOUBLE_TO_LONG(xmm3)
    ret

CDrawingObject::Zoom endp

CDrawingObject::Rotate proc dAngle:double, iOx:long_t, iOy:long_t

    movsd  xmm0,[rcx]._dRotationAngle
    addsd  xmm0,xmm1
    movsd  [rcx]._dRotationAngle,xmm0

    movsd  xmm5,xmm1
    movsd  xmm4,cos(xmm1)
    movsd  xmm5,sin(xmm5)

    mov    rcx,_this
    mov    eax,[rcx]._iCx
    sub    eax,iOx
    cvtsi2sd xmm1,rax
    mov    eax,[rcx]._iCy
    sub    eax,iOy
    cvtsi2sd xmm2,rax
    movsd  xmm0,xmm1
    mulsd  xmm0,xmm4
    movsd  xmm3,xmm2
    mulsd  xmm3,xmm5
    addsd  xmm3,xmm0
    add    ROUND_DOUBLE_TO_LONG(xmm3),iOx
    mov    [rcx]._iCx,eax

    mulsd  xmm2,xmm4
    mulsd  xmm1,xmm5
    subsd  xmm2,xmm1
    add    ROUND_DOUBLE_TO_LONG(xmm2),iOy
    mov    [rcx]._iCy,eax
    ret

CDrawingObject::Rotate endp

    end
