
include MyGestureEngine.inc

    .code

    assume class:rbx

CMyGestureEngine::CMyGestureEngine proc uses rsi pcRect:ptr CDrawingObject

    ldr rsi,pcRect
    mov rbx,@ComAlloc(CMyGestureEngine)
    .if ( rax )
        mov _pcRect,CDrawingObject()
        .if ( rsi )
            mov [rsi],rax
        .endif
        mov rax,rbx
    .endif
    ret
    endp

CMyGestureEngine::Release proc
    .if ( _pcRect )
        _pcRect.Release()
    .endif
    free(rbx)
    ret
    endp

LODWORD macro ull
    mov rax,ull
    exitm<eax>
    endm

CMyGestureEngine::WndProc proc hWnd:HWND, wParam:WPARAM, lParam:LPARAM

  local ptZoomCenter:POINT
  local k:double
  local gi:GESTUREINFO
  local bResult:BOOL

    ;; helper variables

    mov gi.cbSize,sizeof(gi)
    mov bResult,GetGestureInfo(lParam, &gi)
    .if ( !eax )
        .assert("Error in execution of GetGestureInfo" && 0)
        .return FALSE
    .endif

    .switch (gi.dwID)
    .case GID_BEGIN
        .endc
    .case GID_END
        .endc
    .case GID_ZOOM
        .switch (gi.dwFlags)
        .case GF_BEGIN
            mov _dwArguments,LODWORD(gi.ullArguments)
            movzx eax,gi.ptsLocation.x
            mov _ptFirst.x,eax
            movzx eax,gi.ptsLocation.y
            mov _ptFirst.y,eax
            ScreenToClient(hWnd, &_ptFirst)
           .endc
        .default
            movzx eax,gi.ptsLocation.x
            mov _ptSecond.x,eax
            movzx eax,gi.ptsLocation.y
            mov _ptSecond.y,eax
            ScreenToClient(hWnd, &_ptSecond)
            mov eax,_ptSecond.x
            add eax,_ptFirst.x
            shr eax,1
            mov ptZoomCenter.x,eax
            mov eax,_ptSecond.y
            add eax,_ptFirst.y
            shr eax,1
            mov ptZoomCenter.y,eax
            mov eax,dword ptr gi.ullArguments
            cvtsi2sd xmm0,rax
            mov eax,_dwArguments
            cvtsi2sd xmm1,rax
            divsd xmm0,xmm1
            ProcessZoom(xmm0, ptZoomCenter.x, ptZoomCenter.y)
            InvalidateRect(hWnd, NULL, TRUE)
            mov rax,_ptSecond
            mov _ptFirst,rax
            mov _dwArguments,LODWORD(gi.ullArguments)
            .endc
        .endsw
        .endc

    .case GID_PAN
        .switch (gi.dwFlags)
        .case GF_BEGIN
            movzx eax,gi.ptsLocation.x
            mov _ptFirst.x,eax
            movzx eax,gi.ptsLocation.y
            mov _ptFirst.y,eax
            ScreenToClient(hWnd, &_ptFirst)
            .endc
        .default
            movzx eax,gi.ptsLocation.x
            mov _ptSecond.x,eax
            movzx eax,gi.ptsLocation.y
            mov _ptSecond.y,eax
            ScreenToClient(hWnd, &_ptSecond)
            mov edx,_ptSecond.x
            sub edx,_ptFirst.x
            mov eax,_ptSecond.y
            sub eax,_ptFirst.y
            ProcessMove(edx, eax)
            InvalidateRect(hWnd, NULL, TRUE)
            mov _ptFirst,_ptSecond
            .endc
        .endsw
        .endc
    .case GID_ROTATE
        .switch (gi.dwFlags)
        .case GF_BEGIN
            mov _dwArguments,0
           .endc
        .default
            movzx eax,gi.ptsLocation.x
            mov _ptFirst.x,eax
            movzx eax,gi.ptsLocation.y
            mov _ptFirst.y,eax
            ScreenToClient(hWnd, &_ptFirst);
            mov eax,dword ptr gi.ullArguments
            cvtsi2sd xmm0,rax
            movsd xmm2,GID_ROTATE_ANGLE_FROM_ARGUMENT(xmm0)
            mov eax,_dwArguments
            cvtsi2sd xmm0,rax
            subsd xmm2,GID_ROTATE_ANGLE_FROM_ARGUMENT(xmm0)
            ProcessRotate(xmm2, _ptFirst.x, _ptFirst.y)
            InvalidateRect(hWnd, NULL, TRUE)
            mov _dwArguments,LODWORD(gi.ullArguments)
            .endc
        .endsw
        .endc
    .case GID_TWOFINGERTAP
        ProcessTwoFingerTap()
        InvalidateRect(hWnd, NULL, TRUE)
        .endc
    .case GID_PRESSANDTAP
        .switch (gi.dwFlags)
        .case GF_BEGIN
            ProcessPressAndTap()
            InvalidateRect(hWnd, NULL, TRUE)
           .endc
        .endsw
        .endc
    .endsw
    CloseGestureInfoHandle(lParam)
    mov eax,TRUE
    ret
    endp

    assume class:rcx

CMyGestureEngine::ProcessPressAndTap proc
    .if ( _pcRect )
        _pcRect.ShiftColor()
    .endif
    ret
    endp

CMyGestureEngine::ProcessTwoFingerTap proc
    .if ( _pcRect )
        _pcRect.ToggleDrawDiagonals()
    .endif
    ret
    endp

CMyGestureEngine::ProcessZoom proc dZoomFactor:double, lZx:long_t, lZy:long_t
    .if ( _pcRect )
        _pcRect.Zoom(ldr(dZoomFactor), ldr(lZx), ldr(lZy))
    .endif
    ret
    endp

CMyGestureEngine::ProcessMove proc ldx:long_t, ldy:long_t
    .if ( _pcRect )
        _pcRect.Move(ldr(ldx), ldr(ldy))
    .endif
    ret
    endp

CMyGestureEngine::ProcessRotate proc dAngle:double, lOx:long_t, lOy:long_t
    .if ( _pcRect )
        _pcRect.Rotate(ldr(dAngle), ldr(lOx), ldr(lOy))
    .endif
    ret
    endp

    end
