;; Implements a simple custom control that supports UI Automation.

include Control.inc

;; Forward declarations.

ControlWndProc proto :HWND, :UINT, :WPARAM, :LPARAM

;; **** CustomButton methods ***

    .code

    assume rcx:ptr CustomButton

CustomButton::Release proc

    .if ([rcx].m_provider != NULL)

        this.m_provider.Release()
        mov rcx,this
        mov [rcx].m_provider,NULL
    .endif
    ret

CustomButton::Release endp

CustomButton::GetUIAutomationProvider proc hwnd:HWND

    .if ([rcx].m_provider == NULL)

        Provider(rdx)
        mov rcx,this
        mov [rcx].m_provider,rax
    .endif
    .return [rcx].m_provider

CustomButton::GetUIAutomationProvider endp


;; Handle button click or invoke.

CustomButton::InvokeButton proc hwnd:HWND

    xor [rcx].m_buttonOn,1; = ! m_buttonOn;
    SetFocus(rcx)

    .if UiaClientsAreListening()

        ;; Raise an event.
        this.GetUIAutomationProvider(hwnd)
        mov rcx,this
        UiaRaiseAutomationEvent(rax, [rcx].m_InvokedEventId)
    .endif
    InvalidateRect(hwnd, NULL, TRUE)
    ret

CustomButton::InvokeButton endp

;; Ascertain whether button is in the "on" state.

CustomButton::IsButtonOn proc

    .return [rcx].m_buttonOn

CustomButton::IsButtonOn endp

CustomButton::CustomButton proc

    .if HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, CustomButton + CustomButtonVtbl)

        mov this,rax
        lea rdx,[rax+CustomButton]
        mov [rax],rdx
        for q,<Release,GetUIAutomationProvider,IsButtonOn,InvokeButton>
            lea rax,CustomButton_&q
            mov [rdx].CustomButtonVtbl.&q,rax
            endm
        UiaLookupId(AutomationIdentifierType_Event, &Invoke_Invoked_Event_GUID)
        mov rcx,this
        mov [rcx].CustomButton.m_InvokedEventId,eax
        mov rax,rcx
    .endif
    ret

CustomButton::CustomButton endp

;; Control window procedure.

ControlWndProc proc hwnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

    .switch edx

    .case WM_CREATE

        .new pControl:ptr CustomButton()

        .if (rax == NULL)

            PostQuitMessage(-1)
        .endif

        ;; Save the class instance as extra window data so that members can be accessed
        ;;  from within this function.
        SetWindowLongPtr(hwnd, GWLP_USERDATA, rax)
        .endc


    .case WM_DESTROY

       .new pControl:ptr CustomButton
        mov pControl,GetWindowLongPtr(rcx, GWLP_USERDATA)
        pControl.Release()
        .endc

        ;; Register with UI Automation.
    .case WM_GETOBJECT

        ;; If the lParam matches the RootObjectId, send back the RawElementProvider
        .if (r9d == (UiaRootObjectId))

           .new pRootProvider:ptr IRawElementProviderSimple
           .new pControl:ptr CustomButton
            mov pControl,GetWindowLongPtr(rcx, GWLP_USERDATA)
            mov pRootProvider,pControl.GetUIAutomationProvider(hwnd)
           .return UiaReturnRawElementProvider(hwnd, wParam, lParam, pRootProvider)
        .endif
        .return 0

    .case WM_PAINT

       .new pControl:ptr CustomButton
        mov pControl,GetWindowLongPtr(rcx, GWLP_USERDATA)
       .new color:COLORREF

        .if (pControl.IsButtonOn())
            mov color,RGB(128, 0, 0)
        .else
            mov color,RGB(0, 128, 0)
        .endif

       .new paintStruct:PAINTSTRUCT
       .new hdc:HDC
        mov hdc,BeginPaint(hwnd, &paintStruct)
       .new clientRect:RECT
        GetClientRect(hwnd, &clientRect)

        ;; Shrink the colored rectangle so the focus rectangle will be outside it.
        InflateRect(&clientRect, -4, -4)

        ;; Paint the rectangle.
       .new brush:HBRUSH
        mov brush,CreateSolidBrush(color)
        .if (brush != NULL)
            FillRect(hdc, &clientRect, brush)
            DeleteObject(brush)
        .endif
        EndPaint(hwnd, &paintStruct)
        .endc

    .case WM_SETFOCUS

       .new hdc:HDC
       .new clientRect:RECT
        mov hdc,GetDC(hwnd)
        GetClientRect(hwnd, &clientRect)
        DrawFocusRect(hdc, &clientRect)
        ReleaseDC(hwnd, hdc)
        .endc

    .case WM_KILLFOCUS

       .new hdc:HDC
       .new clientRect:RECT
        mov hdc,GetDC(hwnd)
        GetClientRect(hwnd, &clientRect)
        DrawFocusRect(hdc, &clientRect) ;; Erases focus rect if there's one there.
        ReleaseDC(hwnd, hdc)
        .endc

    .case WM_LBUTTONDOWN

       .new pControl:ptr CustomButton
        mov pControl,GetWindowLongPtr(rcx, GWLP_USERDATA)
        pControl.InvokeButton(hwnd)
        .endc

    .case WM_KEYDOWN

        .switch r8d
        .case VK_SPACE
           .new pControl:ptr CustomButton
            mov pControl,GetWindowLongPtr(rcx, GWLP_USERDATA)
            pControl.InvokeButton(hwnd)
            .endc
        .endsw
        .endc
    .endsw

    .return DefWindowProc(hwnd, message, wParam, lParam)

ControlWndProc endp

;; Register the control class.

CustomButton_RegisterControl proc hInstance:HINSTANCE

  local wc:WNDCLASS

    memset(&wc, 0, WNDCLASS)

    mov wc.style,            CS_HREDRAW or CS_VREDRAW
    mov wc.lpfnWndProc,      &ControlWndProc
    mov wc.hInstance,        hInstance
    mov wc.hCursor,          LoadCursor(NULL, IDC_ARROW)
    mov wc.lpszClassName,    &@CStr(L"COLORBUTTON")

    RegisterClass(&wc)
    ret

CustomButton_RegisterControl endp

    end

