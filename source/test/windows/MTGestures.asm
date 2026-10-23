include windows.inc
include math.inc
include tchar.inc

define MAX_COLORS 5

.class CDrawingObject

    s_colors        COLORREF MAX_COLORS dup(?)
    _iCx            long_t ?
    _iCy            long_t ?
    _iWidth         int_t ?
    _iHeight        int_t ?
    _dScalingFactor double ?
    _dRotationAngle double ?
    _bDrawDiagonals BOOL ?
    _iColorIndex    int_t ?

    CDrawingObject      proc
    Release             proc
    ResetObject         proc :int_t, :int_t
    Paint               proc :HDC
    Move                proc :long_t, :long_t
    ToggleDrawDiagonals proc
    Zoom                proc :double, :long_t, :long_t
    Rotate              proc :double, :long_t, :long_t
    ShiftColor          proc
   .ends

.class CMyGestureEngine

    _pcRect             ptr CDrawingObject ?
    _ptFirst            POINT <>
    _ptSecond           POINT <>
    _dwArguments        DWORD ?

    CMyGestureEngine    proc :ptr CDrawingObject
    Release             proc
    WndProc             proc :HWND, :WPARAM, :LPARAM
    ProcessPressAndTap  proc
    ProcessTwoFingerTap proc
    ProcessMove         proc :long_t, :long_t
    ProcessZoom         proc :double, :long_t, :long_t
    ProcessRotate       proc :double, :long_t, :long_t
   .ends


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

IDM_EXIT                equ 105
IDC_MTGESTURES          equ <"MTGESTURES">
IDS_APP_TITLE           equ <"MTGestures">
MAX_LOADSTRING          equ 100

    .data
    g_cRect             ptr CDrawingObject 0
    g_cGestureEngine    ptr CMyGestureEngine 0
    g_hInst             HINSTANCE 0

    .code

MyRegisterClass proc hInstance:HINSTANCE

  local wcex:WNDCLASSEX

    mov wcex.cbSize,        WNDCLASSEX
    mov wcex.style,         CS_HREDRAW or CS_VREDRAW
    mov wcex.lpfnWndProc,   &WndProc
    mov wcex.cbClsExtra,    0
    mov wcex.cbWndExtra,    0
    mov wcex.hInstance,     ldr(hInstance)
    mov wcex.hIcon,         LoadIcon(0, IDI_APPLICATION)
    mov wcex.hIconSm,       rax
    mov wcex.hCursor,       LoadCursor(NULL, IDC_ARROW)
    mov wcex.hbrBackground, COLOR_WINDOW+1
    mov wcex.lpszMenuName,  NULL
    mov wcex.lpszClassName, &@CStr(IDC_MTGESTURES)
    RegisterClassEx(&wcex)
    ret
    endp

InitInstance proc hInstance:HINSTANCE, nCmdShow:int_t
  local hWnd:HWND
    mov g_hInst,ldr(hInstance)
    .if CreateWindowEx(0, IDC_MTGESTURES, IDS_APP_TITLE, WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, ldr(hInstance), NULL)
        mov hWnd,rax
        ShowWindow(hWnd, nCmdShow)
        UpdateWindow(hWnd)
        mov eax,TRUE
    .endif
    ret
    endp


WndProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM
  local wmId:int_t
  local ps:PAINTSTRUCT
  local hdc:HDC
  local gc:GESTURECONFIG
    .switch ldr(message)
    .case WM_GESTURENOTIFY
        mov gc.dwID,0
        mov gc.dwWant,GC_ALLGESTURES
        mov gc.dwBlock,0
        .ifd !SetGestureConfig(ldr(hWnd), 0, 1, &gc, sizeof(GESTURECONFIG))
            .assert("Error in execution of SetGestureConfig" && 0)
        .endif
        .endc
    .case WM_GESTURE
        g_cGestureEngine.WndProc(ldr(hWnd), ldr(wParam), ldr(lParam))
       .return
    .case WM_SIZE
        ldr rax,lParam
        movzx edx,ax
        shr eax,16
        g_cRect.ResetObject(edx, eax)
       .endc
    .case WM_COMMAND
        ldr rax,wParam
        movzx eax,ax
        .switch eax
        .case IDM_EXIT
            DestroyWindow(ldr(hWnd))
            .endc
        .default
            .return DefWindowProc(ldr(hWnd), ldr(message), ldr(wParam), ldr(lParam))
        .endsw
        .endc
    .case WM_PAINT
        mov hdc,BeginPaint(ldr(hWnd), &ps)
        g_cRect.Paint(hdc)
        EndPaint(hWnd, &ps)
       .endc
    .case WM_DESTROY
        PostQuitMessage(0)
       .endc
    .default
        .return DefWindowProc(ldr(hWnd), ldr(message), ldr(wParam), ldr(lParam))
    .endsw
    xor eax,eax
    ret
    endp

_tWinMain proc WINAPI hInstance:HINSTANCE, hPrevInstance:HINSTANCE, lpCmdLine:LPTSTR, nCmdShow:int_t
  local msg:MSG
    mov g_cGestureEngine,CMyGestureEngine(&g_cRect)
    MyRegisterClass(hInstance)
    .repeat
        .break .if !InitInstance(hInstance, nCmdShow)
        .whiled GetMessage(&msg, NULL, 0, 0)
            .ifd !TranslateAccelerator(msg.hwnd, NULL, &msg)
                TranslateMessage(&msg)
                DispatchMessage(&msg)
            .endif
        .endw
        mov rax,msg.wParam
    .until 1
    ret
    endp

    end _tstart
