
include MyGestureEngine.inc

    .code

    assume rcx:ptr CMyGestureEngine
    assume rdx:ptr CMyGestureEngineVtbl

CMyGestureEngine::CMyGestureEngine proc uses rsi rdi pcRect:ptr CDrawingObject

    mov rsi,rcx
    mov rdi,rdx

    .return .if !malloc( CMyGestureEngine + CMyGestureEngineVtbl )

    mov rcx,rax
    add rax,CMyGestureEngine
    mov rdx,rax
    mov [rcx].lpVtbl,rax


    mov [rdx].Release,              &CMyGestureEngine_Release
    mov [rdx].WndProc,              &CMyGestureEngine_WndProc
    mov [rdx].ProcessPressAndTap,   &CMyGestureEngine_ProcessPressAndTap
    mov [rdx].ProcessTwoFingerTap,  &CMyGestureEngine_ProcessTwoFingerTap
    mov [rdx].ProcessMove,          &CMyGestureEngine_ProcessMove
    mov [rdx].ProcessZoom,          &CMyGestureEngine_ProcessZoom
    mov [rdx].ProcessRotate,        &CMyGestureEngine_ProcessRotate

    .if rsi
        mov [rsi],rcx
    .endif
    mov rsi,rcx
    CDrawingObject_CDrawingObject(rdi)

    mov rcx,rsi
    mov [rcx]._pcRect,rax
    mov rax,rsi
    ret

CMyGestureEngine::CMyGestureEngine endp

    assume r10:ptr CDrawingObject

CMyGestureEngine::Release proc

    mov r10,[rcx]._pcRect
    .if (r10)

        [r10].Release()
    .endif
    free(this)
    ret

CMyGestureEngine::Release endp

LODWORD macro ull
    mov rax,ull
    exitm<eax>
    endm

    assume rsi:ptr CMyGestureEngine

CMyGestureEngine::WndProc proc uses rsi rdi hWnd:HWND, wParam:WPARAM, lParam:LPARAM

  local ptZoomCenter:POINT
  local k:double
  local gi:GESTUREINFO
  local bResult:BOOL

    ;; helper variables

    mov rsi,rcx

    mov gi.cbSize,sizeof(gi)
    mov bResult,GetGestureInfo(lParam, &gi)

    .if (!bResult)

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
            mov [rsi]._dwArguments,LODWORD(gi.ullArguments)
            movzx eax,gi.ptsLocation.x
            mov [rsi]._ptFirst.x,eax
            movzx eax,gi.ptsLocation.y
            mov [rsi]._ptFirst.y,eax
            ScreenToClient(hWnd, &[rsi]._ptFirst)
            .endc

        .default
            movzx eax,gi.ptsLocation.x
            mov [rsi]._ptSecond.x,eax
            movzx eax,gi.ptsLocation.y
            mov [rsi]._ptSecond.y,eax
            ScreenToClient(hWnd, &[rsi]._ptSecond)

            mov eax,[rsi]._ptSecond.x
            add eax,[rsi]._ptFirst.x
            shr eax,1
            mov ptZoomCenter.x,eax
            mov eax,[rsi]._ptSecond.y
            add eax,[rsi]._ptFirst.y
            shr eax,1
            mov ptZoomCenter.y,eax

            mov eax,dword ptr gi.ullArguments
            cvtsi2sd xmm0,rax
            mov eax,[rsi]._dwArguments
            cvtsi2sd xmm1,rax
            divsd xmm0,xmm1

            [rsi].ProcessZoom(xmm0, ptZoomCenter.x, ptZoomCenter.y)
            InvalidateRect(hWnd, NULL, TRUE)

            mov rax,[rsi]._ptSecond
            mov [rsi]._ptFirst,rax
            mov [rsi]._dwArguments,LODWORD(gi.ullArguments)
            .endc
        .endsw
        .endc

    .case GID_PAN
        .switch (gi.dwFlags)
        .case GF_BEGIN
            movzx eax,gi.ptsLocation.x
            mov [rsi]._ptFirst.x,eax
            movzx eax,gi.ptsLocation.y
            mov [rsi]._ptFirst.y,eax
            ScreenToClient(hWnd, &[rsi]._ptFirst)
            .endc

        .default
            movzx eax,gi.ptsLocation.x
            mov [rsi]._ptSecond.x,eax
            movzx eax,gi.ptsLocation.y
            mov [rsi]._ptSecond.y,eax
            ScreenToClient(hWnd, &[rsi]._ptSecond)

            mov edx,[rsi]._ptSecond.x
            sub edx,[rsi]._ptFirst.x
            mov r8d,[rsi]._ptSecond.y
            sub r8d,[rsi]._ptFirst.y
            [rsi].ProcessMove(edx, r8d)
            InvalidateRect(hWnd, NULL, TRUE)

            mov rax,[rsi]._ptSecond
            mov [rsi]._ptFirst,rax
            .endc
        .endsw
        .endc

    .case GID_ROTATE
        .switch (gi.dwFlags)
        .case GF_BEGIN
            mov [rsi]._dwArguments,0
            .endc
        .default
            movzx eax,gi.ptsLocation.x
            mov [rsi]._ptFirst.x,eax
            movzx eax,gi.ptsLocation.y
            mov [rsi]._ptFirst.y,eax
            ScreenToClient(hWnd, &[rsi]._ptFirst);
            mov eax,dword ptr gi.ullArguments
            cvtsi2sd xmm0,rax
            movsd xmm2,GID_ROTATE_ANGLE_FROM_ARGUMENT(xmm0)
            mov eax,[rsi]._dwArguments
            cvtsi2sd xmm0,rax
            subsd xmm2,GID_ROTATE_ANGLE_FROM_ARGUMENT(xmm0)
            [rsi].ProcessRotate(xmm2, [rsi]._ptFirst.x, [rsi]._ptFirst.y)
            InvalidateRect(hWnd, NULL, TRUE)
            mov [rsi]._dwArguments,LODWORD(gi.ullArguments)
            .endc
        .endsw
        .endc

    .case GID_TWOFINGERTAP
        [rsi].ProcessTwoFingerTap()
        InvalidateRect(hWnd, NULL, TRUE)
        .endc

    .case GID_PRESSANDTAP
        .switch (gi.dwFlags)
        .case GF_BEGIN
            [rsi].ProcessPressAndTap()
            InvalidateRect(hWnd, NULL, TRUE)
            .endc
        .endsw
        .endc
    .endsw

    CloseGestureInfoHandle(lParam)
    mov eax,TRUE
    ret

CMyGestureEngine::WndProc endp

CMyGestureEngine::ProcessPressAndTap proc

    mov r10,[rcx]._pcRect
    .if (r10)

        [r10].ShiftColor()
    .endif
    ret

CMyGestureEngine::ProcessPressAndTap endp

CMyGestureEngine::ProcessTwoFingerTap proc

    mov r10,[rcx]._pcRect
    .if (r10)

        [r10].ToggleDrawDiagonals()
    .endif
    ret

CMyGestureEngine::ProcessTwoFingerTap endp

CMyGestureEngine::ProcessZoom proc dZoomFactor:double, lZx:long_t, lZy:long_t

    mov r10,[rcx]._pcRect
    .if (r10)

        [r10].Zoom(xmm1, r8d, r9d)
    .endif
    ret

CMyGestureEngine::ProcessZoom endp

CMyGestureEngine::ProcessMove proc ldx:long_t, ldy:long_t

    mov r10,[rcx]._pcRect
    .if (r10)

        [r10].Move(edx, r8d)
    .endif
    ret

CMyGestureEngine::ProcessMove endp

CMyGestureEngine::ProcessRotate proc dAngle:double, lOx:long_t, lOy:long_t

    mov r10,[rcx]._pcRect
    .if (r10)

        [r10].Rotate(xmm1, r8d, r9d)
    .endif
    ret

CMyGestureEngine::ProcessRotate endp

    end
