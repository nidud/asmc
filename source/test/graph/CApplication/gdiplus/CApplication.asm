
include CApplication.inc

define CLASS_NAME   <"MainWindowClass">
define WINDOW_NAME  <"Windows samples">
define ID_TIMER     1

    .code

; Runs the application

CApplication::Run proc

   .new result:int_t = 0
   .new gdiplus:GdiPlus()

    this.BeforeEnteringMessageLoop()

    .if (SUCCEEDED(eax))

        mov result,this.EnterMessageLoop()
    .else

        MessageBox(NULL, "An error occuring when running the sample", NULL, MB_OK)
    .endif

    this.AfterLeavingMessageLoop()

    .return result

CApplication::Run endp


; Creates the application window, the d3d device and DirectComposition device and visual tree
; before entering the message loop.

CApplication::BeforeEnteringMessageLoop proc

    .new hr:HRESULT = this.CreateApplicationWindow()

    .return hr

CApplication::BeforeEnteringMessageLoop endp


; Message loop

CApplication::EnterMessageLoop proc

    .new result:int_t = 0

    .if ( this.ShowApplicationWindow() )

        .new msg:MSG

        .while ( GetMessage( &msg, NULL, 0, 0 ) )

            TranslateMessage( &msg )
            DispatchMessage( &msg )
        .endw

        mov result, msg.wParam
    .endif

    .return result

CApplication::EnterMessageLoop endp


; Destroys the application window, DirectComposition device and visual tree.

CApplication::AfterLeavingMessageLoop proc

    this.DestroyApplicationWindow()
    ret

CApplication::AfterLeavingMessageLoop endp


; Shows the application window

    assume rdi:ptr CApplication

CApplication::ShowApplicationWindow proc uses rdi

   .new bSucceeded:BOOL = TRUE

    mov rdi,this
    .if ( [rdi].m_hwnd == NULL )

        mov bSucceeded,FALSE
    .endif

    .if ( bSucceeded )

        ShowWindow([rdi].m_hwnd, SW_SHOW)
        UpdateWindow([rdi].m_hwnd)
        SetTimer([rdi].m_hwnd, ID_TIMER, 20, NULL)
    .endif

    .return bSucceeded

CApplication::ShowApplicationWindow endp


; Destroys the applicaiton window

CApplication::DestroyApplicationWindow proc uses rdi

    mov rdi,this
    .if ( [rdi].m_hwnd != NULL )

        .if ( [rdi].m_bitmap )
            DeleteObject( [rdi].m_bitmap )
        .endif
        KillTimer( [rdi].m_hwnd, ID_TIMER )
        DestroyWindow( [rdi].m_hwnd )
        mov [rdi].m_hwnd,NULL
    .endif
    ret

CApplication::DestroyApplicationWindow endp


CApplication::OnSize proc uses rsi rdi rbx lParam:LPARAM

    mov     rdi,this
    mov     rdx,lParam
    movzx   eax,dx
    shr     edx,16
    mov     [rdi].m_width,eax
    mov     [rdi].m_height,edx

    mov     ecx,eax
    cmp     eax,edx
    cmova   ecx,edx
    shr     ecx,3
    mov     edx,ColorAlpha(Green, 180)
    mov     eax,ColorAlpha(Blue, 180)

    .for ( rsi = &[rdi].m_obj, ebx = 1: ebx < MAXOBJ+1: ebx++, rsi += sizeof(object) )

        mov [rsi].object.m_mov.x,ebx
        mov [rsi].object.m_mov.y,ebx
        mov [rsi].object.m_pos.x,ecx
        mov [rsi].object.m_pos.y,ecx
        mov [rsi].object.m_radius,ecx
        mov [rsi].object.m_color,eax
        mov eax,edx
        mov edx,ColorAlpha(Red, 180)
    .endf

    .if ( [rdi].m_bitmap )

        DeleteObject([rdi].m_bitmap)
        mov [rdi].m_bitmap,NULL
    .endif
    .return 1

CApplication::OnSize endp


    assume rsi:ptr object

CApplication::OnTimer proc uses rsi rdi rbx

    mov rdi,this
   .return 0 .if ( [rdi].m_bitmap == NULL )

   .new hdc:HDC = GetDC([rdi].m_hwnd)
   .new mem:HDC = CreateCompatibleDC(hdc)

    SelectObject(mem, [rdi].m_bitmap)

   .new g:Graphics(mem)
    g.SetSmoothingMode(SmoothingModeHighQuality)
    g.Clear(ColorAlpha(Black, 230))

   .new i:SINT
   .new count:SINT = 1
   .new FullTranslucent:ARGB = ColorAlpha(Black, 230)

    .for ( rsi = &[rdi].m_obj, i = 0: i < MAXOBJ: i++, rsi += sizeof(object) )

       .new p:GraphicsPath()
        mov ebx,[rsi].m_radius
        mov edx,[rsi].m_pos.x
        sub edx,ebx
        mov eax,[rsi].m_pos.y
        sub eax,ebx
        add ebx,ebx
        p.AddEllipse(edx, eax, ebx, ebx)

       .new b:PathGradientBrush(&p)
        b.SetCenterColor([rsi].m_color)
        b.SetSurroundColors(&FullTranslucent, &count)

        mov ebx,[rsi].m_radius
        mov edx,[rsi].m_pos.x
        sub edx,ebx
        mov eax,[rsi].m_pos.y
        sub eax,ebx
        add ebx,ebx
        g.FillEllipse(&b, edx, eax, ebx, ebx)
        b.Release()
        p.Release()
    .endf

    g.Release()

    mov ecx,[rdi].m_rc.right
    sub ecx,[rdi].m_rc.left
    mov edx,[rdi].m_rc.bottom
    sub edx,[rdi].m_rc.top
    BitBlt(hdc, [rdi].m_rc.left, [rdi].m_rc.top, ecx, edx, mem, 0, 0, SRCCOPY)
    ReleaseDC([rdi].m_hwnd, hdc)
    DeleteDC(mem)

   .for ( rsi = &[rdi].m_obj, ebx = 0: ebx < MAXOBJ: ebx++, rsi += sizeof(object) )

        add [rsi].m_pos.x,[rsi].m_mov.x
        add [rsi].m_pos.y,[rsi].m_mov.y

        mov eax,[rdi].m_rc.right
        sub eax,[rdi].m_rc.left
        mov ecx,[rsi].m_pos.x
        add ecx,[rsi].m_radius
        .if ( ecx >= eax || [rsi].m_pos.x <= [rsi].m_radius )
            neg [rsi].m_mov.x
        .endif
        mov eax,[rdi].m_rc.bottom
        sub eax,[rdi].m_rc.top
        mov ecx,[rsi].m_pos.y
        add ecx,[rsi].m_radius
        .if ( ecx >= eax || [rsi].m_pos.y <= [rsi].m_radius )
            neg [rsi].m_mov.y
        .endif
    .endf
    .return 1

CApplication::OnTimer endp


; Handles the WM_KEYDOWN message

    assume rcx:ptr CApplication

CApplication::OnKeyDown proc wParam:WPARAM

    mov rcx,this
    mov rdx,wParam
    .switch edx
    .case VK_DOWN
        .endc .if ( [rcx].m_obj.m_mov.x == 1 || [rcx].m_obj.m_mov.x == -1 )
        .for ( rdx = &[rcx].m_obj, ecx = 0: ecx < MAXOBJ: ecx++, rdx += sizeof(object) )
            mov eax,[rdx].object.m_mov.x
            .ifs ( eax > 1 || eax < -1 )
                .if ( [rdx].object.m_mov.x < 0 )
                    inc [rdx].object.m_mov.x
                .else
                    dec [rdx].object.m_mov.x
                .endif
                .if ( [rdx].object.m_mov.y < 0 )
                    inc [rdx].object.m_mov.y
                .else
                    dec [rdx].object.m_mov.y
                .endif
            .endif
        .endf
        .endc
    .case VK_UP
        .endc .if ( [rcx].m_obj.m_mov.x == 30 || [rcx].m_obj.m_mov.x == -30 )
        .for ( rdx = &[rcx].m_obj, ecx = 0: ecx < MAXOBJ: ecx++, rdx += sizeof(object) )
            .if ( [rdx].object.m_mov.x < 0 )
                dec [rdx].object.m_mov.x
            .else
                inc [rdx].object.m_mov.x
            .endif
            .if ( [rdx].object.m_mov.y < 0 )
                dec [rdx].object.m_mov.y
            .else
                inc [rdx].object.m_mov.y
            .endif
        .endf
        .endc
    .endsw
    .return 0

CApplication::OnKeyDown endp


; Handles the WM_CLOSE message

CApplication::OnClose proc

    mov rcx,this
    .if ( [rcx].m_hwnd != NULL )

        DestroyWindow( [rcx].m_hwnd )

        mov rcx,this
        mov [rcx].m_hwnd,NULL
    .endif
    .return 0

CApplication::OnClose endp


; Handles the WM_DESTROY message

CApplication::OnDestroy proc

    PostQuitMessage(0)

    .return 0

CApplication::OnDestroy endp


; Handles the WM_PAINT message

CApplication::OnPaint proc uses rdi

   .new rcClient:RECT
   .new ps:PAINTSTRUCT
   .new height:int_t = 0

    mov rdi,this

   .new hdc:HDC = BeginPaint([rdi].m_hwnd, &ps)

    ; get the dimensions of the main window.

    GetClientRect([rdi].m_hwnd, &rcClient)

    mov [rdi].m_rc.left,50
    mov eax,[rdi].m_width
    sub eax,50
    mov [rdi].m_rc.right,eax

    ; Logo

    xor ecx,ecx
    .new hlogo:HFONT = CreateFont(IDS_FONT_HEIGHT_LOGO, ecx, ecx, ecx, ecx, ecx, ecx,
            ecx, ecx, ecx, ecx, ecx, ecx, IDS_FONT_TYPEFACE) ; Logo Font and Size

    .if ( hlogo != NULL )

       .new hOldFont:HFONT = SelectObject(hdc, hlogo)

        SetTextColor(hdc, GetSysColor(COLOR_GRAYTEXT))
        SetBkMode(hdc, TRANSPARENT)

        mov rcClient.top,10
        mov rcClient.left,50
        mov height,DrawText(hdc, "Windows samples", -1, &rcClient, DT_WORDBREAK)
        SelectObject(hdc, hOldFont)
        DeleteObject(hlogo)
    .endif

    ; Title

    xor ecx,ecx
   .new htitle:HFONT = CreateFont(IDS_FONT_HEIGHT_TITLE, ecx, ecx, ecx, ecx, ecx,
            ecx, ecx, ecx, ecx, ecx, ecx, ecx, IDS_FONT_TYPEFACE) ; Title Font and Size

    .if (htitle != NULL)

       .new hOldFont:HFONT = SelectObject(hdc, htitle)

        mov eax,height
        add eax,10
        mov rcClient.top,eax
        mov rcClient.left,50

        mov height,DrawText(hdc, "CApplication Class", -1, &rcClient, DT_WORDBREAK)
        SelectObject(hdc, hOldFont)
        DeleteObject(htitle)
    .endif

    ; Description

   .new hdescription:HFONT

    xor ecx,ecx
    mov hdescription,CreateFont(IDS_FONT_HEIGHT_DESCRIPTION, ecx, ecx, ecx,
            ecx, ecx, ecx, ecx, ecx, ecx, ecx, ecx, ecx,
            IDS_FONT_TYPEFACE) ; Description Font and Size

    .if (hdescription != NULL)

       .new hOldFont:HFONT = SelectObject(hdc, hdescription)

        mov eax,height
        add eax,40
        mov rcClient.top,eax
        mov rcClient.left,50

        DrawText(hdc,
            "This sample use the CApplication class and GDI+",
            -1, &rcClient, DT_WORDBREAK)

        add eax,rcClient.top
        add eax,6
        mov [rdi].m_rc.top,eax
        mov eax,[rdi].m_height
        sub eax,100
        mov rcClient.top,eax
        sub eax,16
        mov [rdi].m_rc.bottom,eax
        mov eax,[rdi].m_width
        shr eax,1
        mov rcClient.left,eax

        DrawText(hdc,
            "A) Use keys UP or DOWN to adjust the speed.\n"
            "B) Escape to exit the application.", -1, &rcClient,
            DT_WORDBREAK)
        SelectObject(hdc, hOldFont)
        DeleteObject(hdescription)
    .endif
    EndPaint([rdi].m_hwnd, &ps)

    mov edx,[rdi].m_rc.bottom
    sub edx,[rdi].m_rc.top
    .ifs ( edx > 100 )
        mov ecx,[rdi].m_rc.right
        sub ecx,[rdi].m_rc.left
        .ifs ( ecx > 100 )

            mov hdc,GetDC([rdi].m_hwnd)
            mov ecx,[rdi].m_rc.right
            sub ecx,[rdi].m_rc.left
            mov edx,[rdi].m_rc.bottom
            sub edx,[rdi].m_rc.top
            mov [rdi].m_bitmap,CreateCompatibleBitmap(hdc, ecx, edx)
            ReleaseDC([rdi].m_hwnd, hdc)

            mov eax,[rdi].m_rc.right
            sub eax,[rdi].m_rc.left
            shr eax,1
            mov ecx,[rdi].m_rc.bottom
            sub ecx,[rdi].m_rc.top
            shr ecx,1
            .new i:int_t
            .for ( rdx = &[rdi].m_obj, i = 0: i < MAXOBJ: i++, rdx += sizeof(object) )
                mov [rdx].object.m_pos.x,eax
                mov [rdx].object.m_pos.y,ecx
            .endf
        .endif
    .endif
   .return 1

CApplication::OnPaint endp


; Main Window procedure

WindowProc proc WINAPI hwnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

    .if ( message == WM_CREATE )

        mov rdx,lParam
        SetWindowLongPtr(hwnd, GWLP_USERDATA, [rdx].CREATESTRUCT.lpCreateParams)
        .return 1
    .endif

    .new Application:ptr CApplication = GetWindowLongPtr(hwnd, GWLP_USERDATA)

    .switch ( message )
    .case WM_SIZE
        Application.OnSize(lParam)
        .endc
    .case WM_KEYDOWN
        Application.OnKeyDown(wParam)
        .endc
    .case WM_CLOSE
        Application.OnClose()
        .endc
    .case WM_DESTROY
        Application.OnDestroy()
        .endc
    .case WM_PAINT
        Application.OnPaint()
        .endc
    .case WM_TIMER
        Application.OnTimer()
        .endc
    .case WM_CHAR
        .gotosw(WM_DESTROY) .if wParam == VK_ESCAPE
    .default
        DefWindowProc(hwnd, message, wParam, lParam)
    .endsw
    ret

WindowProc endp


; Creates the application window

CApplication::CreateApplicationWindow proc uses rdi

    mov rdi,this

    .new wc:WNDCLASSEX = {
        WNDCLASSEX,                     ; .cbSize
        CS_HREDRAW or CS_VREDRAW,       ; .style
        &WindowProc,                    ; .lpfnWndProc
        0,                              ; .cbClsExtra
        sizeof(LONG_PTR),               ; .cbWndExtra
        [rdi].m_hInstance,              ; .hInstance
        NULL,                           ; .hIcon
        LoadCursor(NULL, IDC_ARROW),    ; .hCursor
        GetStockObject(BLACK_BRUSH),    ; .hbrBackground
        NULL,                           ; .lpszMenuName
        CLASS_NAME,                     ; .lpszClassName
        NULL                            ; .hIconSm
        }

    .if ( RegisterClassEx( &wc ) == 0 )
        .return E_FAIL
    .endif

    .new rect:RECT = { 0, 0, [rdi].m_width, [rdi].m_height }

    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW or WS_CAPTION or WS_SYSMENU or WS_MINIMIZEBOX, FALSE)

    mov eax,rect.right
    sub eax,rect.left
    mov [rdi].m_width,eax

    mov eax,rect.bottom
    sub eax,rect.top
    mov [rdi].m_height,eax

    .if CreateWindowEx(0, CLASS_NAME, WINDOW_NAME,
           WS_OVERLAPPEDWINDOW or WS_CAPTION or WS_SYSMENU or WS_MINIMIZEBOX,
           CW_USEDEFAULT, CW_USEDEFAULT,
           [rdi].m_width, [rdi].m_height,
           NULL, NULL, [rdi].m_hInstance, rdi) == NULL

        .return E_UNEXPECTED
    .endif
    mov [rdi].m_hwnd,rax
   .return S_OK

CApplication::CreateApplicationWindow endp


; Provides the entry point to the application

CApplication::CApplication proc instance:HINSTANCE

    @ComAlloc(CApplication)

    mov rcx,instance
    mov [rax].CApplication.m_hInstance,rcx
    mov [rax].CApplication.m_width,900
    mov [rax].CApplication.m_height,600
    ret

CApplication::CApplication endp

_tWinMain proc WINAPI hInstance:HINSTANCE, hPrevInstance:HINSTANCE, pszCmdLine:LPTSTR, iCmdShow:int_t

    .new app:ptr CApplication(hInstance)
    .return app.Run()

_tWinMain endp

    end _tstart
