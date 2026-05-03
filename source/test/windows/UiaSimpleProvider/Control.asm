;
; Implements a simple custom control that supports UI Automation.
;
include Control.inc


; Forward declarations.
ControlWndProc proto :HWND, :UINT, :WPARAM, :LPARAM

; CustomButton methods

.code

CustomButton::CustomButton proc
    @ComAlloc(CustomButton)
    ret
    endp

    assume class:rbx

CustomButton::Release proc

    mov rax,m_provider
    .if ( rax && [rax].Provider.m_refCount )

        m_provider.Release()
        mov m_provider,NULL
    .endif
    free(rbx)
    xor eax,eax
    ret
    endp

CustomButton::GetUIAutomationProvider proc hwnd:HWND

    mov rax,m_provider
    .if ( rax == NULL )
        mov m_provider,Provider(ldr(hwnd))
    .endif
    ret
    endp


; Handle button click or invoke.

CustomButton::InvokeButton proc hwnd:HWND

    xor m_buttonOn,1
    SetFocus(hwnd)

    .if ( UiaClientsAreListening() )

        ; Raise an event.
        UiaRaiseAutomationEvent(GetUIAutomationProvider(hwnd), UIA_Invoke_InvokedEventId)
    .endif
    InvalidateRect(hwnd, NULL, true)
    ret
    endp

; Ascertain whether button is in the "on" state.

CustomButton::IsButtonOn proc
    .return m_buttonOn
    endp


; Register the control class.

CustomButton_RegisterControl proc hInstance:HINSTANCE

    .new wc:WNDCLASS = {
        CS_HREDRAW or CS_VREDRAW,   ; .style
        &ControlWndProc,            ; .lpfnWndProc
        0,                          ; .cbClsExtra
        0,                          ; .cbWndExtra
        hInstance,                  ; .hInstance
        NULL,                       ; .hIcon
        LoadCursor(NULL, IDC_ARROW),; .hCursor
        NULL,                       ; .hbrBackground
        NULL,                       ; .lpszMenuName
        "COLORBUTTON"               ; .lpszClassName
        }

    RegisterClass(&wc)
    ret
    endp

; Control window procedure.

ControlWndProc proc hwnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

    .switch ( message )

    .case WM_CREATE
        .new pControl:ptr CustomButton()
        .if (pControl == NULL)
            PostQuitMessage(-1)
        .endif
        ;
        ; Save the class instance as extra window data so that members can be accessed
        ;  from within this function.
        ;
        SetWindowLongPtr(hwnd, GWLP_USERDATA, pControl)
       .endc

    .case WM_DESTROY
        .new pControl:ptr CustomButton = GetWindowLongPtr(hwnd, GWLP_USERDATA)
         pControl.Release()
        .endc

        ;
        ; Register with UI Automation.
        ;
    .case WM_GETOBJECT
        ;
        ; If the lParam matches the RootObjectId, send back the RawElementProvider
        ;
        .if ( dword ptr lParam == UiaRootObjectId )
            .new pControl:ptr CustomButton = GetWindowLongPtr(hwnd, GWLP_USERDATA)
            .new pRootProvider:ptr IRawElementProviderSimple = pControl.GetUIAutomationProvider(hwnd)
            .return UiaReturnRawElementProvider(hwnd, wParam, lParam, pRootProvider)
        .endif
        .return 0

    .case WM_PAINT
        .new pControl:ptr CustomButton = GetWindowLongPtr(hwnd, GWLP_USERDATA)
        .new color:COLORREF
        .if ( pControl.IsButtonOn() )
            mov color,RGB(128, 0, 0)
        .else
            mov color,RGB(0, 128, 0)
        .endif
        .new paintStruct:PAINTSTRUCT
        .new hdc:HDC = BeginPaint(hwnd, &paintStruct)
        .new clientRect:RECT
        GetClientRect(hwnd, &clientRect)

        ; Shrink the colored rectangle so the focus rectangle will be outside it.
        InflateRect(&clientRect, -4, -4)

        ; Paint the rectangle.
        .new brush:HBRUSH = CreateSolidBrush(color)
        .if (brush != NULL)

            FillRect(hdc, &clientRect, brush)
            DeleteObject(brush)
        .endif
        EndPaint(hwnd, &paintStruct)
        .endc

    .case WM_SETFOCUS
        .new hdc:HDC = GetDC(hwnd)
        .new clientRect:RECT
         GetClientRect(hwnd, &clientRect)
         DrawFocusRect(hdc, &clientRect)
         ReleaseDC(hwnd, hdc)
        .endc

    .case WM_KILLFOCUS
        .new hdc:HDC = GetDC(hwnd)
        .new clientRect:RECT
         GetClientRect(hwnd, &clientRect)
         DrawFocusRect(hdc, &clientRect) ; Erases focus rect if there's one there.
         ReleaseDC(hwnd, hdc)
        .endc

    .case WM_LBUTTONDOWN
        .new pControl:ptr CustomButton = GetWindowLongPtr(hwnd, GWLP_USERDATA)
         pControl.InvokeButton(hwnd)
        .endc

    .case WM_KEYDOWN
        .switch (wParam)
        .case VK_SPACE
            .new pControl:ptr CustomButton = GetWindowLongPtr(hwnd, GWLP_USERDATA)
             pControl.InvokeButton(hwnd)
            .endc
        .endsw
        .endc
    .default
        .return DefWindowProc(hwnd, message, wParam, lParam)
    .endsw
    ret
    endp

    end
