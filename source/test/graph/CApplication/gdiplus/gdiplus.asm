
define WINVER 0x0700
define _WIN32_WINNT 0x0700

include windows.inc
include gdiplus.inc
include tchar.inc

define IDS_FONT_TYPEFACE <"Segoe UI Light">
define IDS_FONT_HEIGHT_LOGO 0
define IDS_FONT_HEIGHT_TITLE 50
define IDS_FONT_HEIGHT_DESCRIPTION 22
define MAXOBJ 3

.template object
    m_pos           POINT <>
    m_mov           POINT <>
    m_radius        uint_t ?
    m_color         ARGB ?
   .ends

.class CApplication

    m_hInstance     HINSTANCE ?
    m_hwnd          HWND ?
    m_width         int_t ?
    m_height        int_t ?
    m_bitmap        HBITMAP ?
    m_rc            RECT <>
    m_obj           object MAXOBJ dup(<>)

    CApplication    proc :HINSTANCE
    Run             proc
    OnKeyDown       proc :WPARAM
    OnClose         proc
    OnDestroy       proc
    OnPaint         proc
    OnTimer         proc
    OnSize          proc :LPARAM

    BeforeEnteringMessageLoop   proc
    EnterMessageLoop            proc
    AfterLeavingMessageLoop     proc

    CreateApplicationWindow     proc
    ShowApplicationWindow       proc
    DestroyApplicationWindow    proc
   .ends

define CLASS_NAME   <"MainWindowClass">
define WINDOW_NAME  <"Windows samples">
define ID_TIMER     1

   .code

    assume class:rbx

; Runs the application

CApplication::Run proc

    .new result:int_t = 0
    .new gdiplus:GdiPlus()
    .if SUCCEEDED(BeforeEnteringMessageLoop())
        mov result,EnterMessageLoop()
    .else
        MessageBox(NULL, "An error occuring when running the sample", NULL, MB_OK)
    .endif
    AfterLeavingMessageLoop()
    mov eax,result
    ret
    endp


; Creates the application window, the d3d device and DirectComposition device and visual tree
; before entering the message loop.

CApplication::BeforeEnteringMessageLoop proc
    CreateApplicationWindow()
    ret
    endp


; Message loop

CApplication::EnterMessageLoop proc

    .new result:int_t = 0

    .if ShowApplicationWindow()

        .new msg:MSG
        .while ( GetMessage( &msg, NULL, 0, 0 ) )

            TranslateMessage( &msg )
            DispatchMessage( &msg )
        .endw
        mov result,msg.wParam
    .endif
    .return( result )
    endp


; Destroys the application window, DirectComposition device and visual tree.

CApplication::AfterLeavingMessageLoop proc
    DestroyApplicationWindow()
    ret
    endp


; Shows the application window

CApplication::ShowApplicationWindow proc

    .new bSucceeded:BOOL = TRUE

    .if ( m_hwnd == NULL )
        mov bSucceeded,FALSE
    .endif
    .if ( bSucceeded )
        ShowWindow(m_hwnd, SW_SHOW)
        UpdateWindow(m_hwnd)
        SetTimer(m_hwnd, ID_TIMER, 20, NULL)
    .endif
    .return bSucceeded

    endp


; Destroys the applicaiton window

CApplication::DestroyApplicationWindow proc

    .if ( m_hwnd != NULL )

        .if ( m_bitmap )
            DeleteObject( m_bitmap )
        .endif
        KillTimer( m_hwnd, ID_TIMER )
        DestroyWindow( m_hwnd )
        mov m_hwnd,NULL
    .endif
    ret
    endp


    assume rsi:ptr object

CApplication::OnSize proc uses rsi rdi lParam:LPARAM

    mov     rdx,lParam
    movzx   eax,dx
    shr     edx,16
    mov     m_width,eax
    mov     m_height,edx
    mov     ecx,eax
    cmp     eax,edx
    cmova   ecx,edx
    shr     ecx,3
    mov     edx,ColorAlpha(Green, 180)
    mov     eax,ColorAlpha(Blue, 180)

    .for ( rsi = &m_obj, edi = 1 : edi < MAXOBJ+1 : edi++, rsi += sizeof(object) )

        mov [rsi].m_mov.x,edi
        mov [rsi].m_mov.y,edi
        mov [rsi].m_pos.x,ecx
        mov [rsi].m_pos.y,ecx
        mov [rsi].m_radius,ecx
        mov [rsi].m_color,eax
        mov eax,edx
        mov edx,ColorAlpha(Red, 180)
    .endf

    .if ( m_bitmap )

        DeleteObject(m_bitmap)
        mov m_bitmap,NULL
    .endif
    .return 1

    endp


CApplication::OnTimer proc uses rsi rdi

   .return 0 .if ( m_bitmap == NULL )

   .new hdc:HDC = GetDC(m_hwnd)
   .new mem:HDC = CreateCompatibleDC(hdc)

    SelectObject(mem, m_bitmap)

   .new g:Graphics(mem)
    g.SetSmoothingMode(SmoothingModeHighQuality)
    g.Clear(ColorAlpha(Black, 230))

   .new i:SINT
   .new count:SINT = 1
   .new FullTranslucent:ARGB = ColorAlpha(Black, 230)

    .for ( rsi = &m_obj, i = 0: i < MAXOBJ: i++, rsi += sizeof(object) )

       .new p:GraphicsPath()
        mov edi,[rsi].m_radius
        mov edx,[rsi].m_pos.x
        sub edx,edi
        mov eax,[rsi].m_pos.y
        sub eax,edi
        add edi,edi
        p.AddEllipse(edx, eax, edi, edi)

       .new b:PathGradientBrush(&p)
        b.SetCenterColor([rsi].m_color)
        b.SetSurroundColors(&FullTranslucent, &count)

        mov edi,[rsi].m_radius
        mov edx,[rsi].m_pos.x
        sub edx,edi
        mov eax,[rsi].m_pos.y
        sub eax,edi
        add edi,edi
        g.FillEllipse(&b, edx, eax, edi, edi)
        b.Release()
        p.Release()
    .endf

    g.Release()

    mov ecx,m_rc.right
    sub ecx,m_rc.left
    mov edx,m_rc.bottom
    sub edx,m_rc.top
    BitBlt(hdc, m_rc.left, m_rc.top, ecx, edx, mem, 0, 0, SRCCOPY)
    ReleaseDC(m_hwnd, hdc)
    DeleteDC(mem)

   .for ( rsi = &m_obj, edi = 0: edi < MAXOBJ: edi++, rsi += sizeof(object) )

        add [rsi].m_pos.x,[rsi].m_mov.x
        add [rsi].m_pos.y,[rsi].m_mov.y

        mov eax,m_rc.right
        sub eax,m_rc.left
        mov ecx,[rsi].m_pos.x
        add ecx,[rsi].m_radius
        .if ( ecx >= eax || [rsi].m_pos.x <= [rsi].m_radius )
            neg [rsi].m_mov.x
        .endif
        mov eax,m_rc.bottom
        sub eax,m_rc.top
        mov ecx,[rsi].m_pos.y
        add ecx,[rsi].m_radius
        .if ( ecx >= eax || [rsi].m_pos.y <= [rsi].m_radius )
            neg [rsi].m_mov.y
        .endif
    .endf
    .return 1

    endp


; Handles the WM_KEYDOWN message

CApplication::OnKeyDown proc wParam:WPARAM

    ldr rdx,wParam
    .switch edx
    .case VK_DOWN
        .endc .if ( m_obj.m_mov.x == 1 || m_obj.m_mov.x == -1 )
        .for ( rdx = &m_obj, ecx = 0: ecx < MAXOBJ: ecx++, rdx += sizeof(object) )
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
        .endc .if ( m_obj.m_mov.x == 30 || m_obj.m_mov.x == -30 )
        .for ( rdx = &m_obj, ecx = 0: ecx < MAXOBJ: ecx++, rdx += sizeof(object) )
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

    endp


; Handles the WM_CLOSE message

CApplication::OnClose proc

    .if ( m_hwnd != NULL )

        DestroyWindow( m_hwnd )
        mov m_hwnd,NULL
    .endif
    .return 0

    endp


; Handles the WM_DESTROY message

CApplication::OnDestroy proc

    PostQuitMessage(0)

    .return 0

    endp


; Handles the WM_PAINT message

CApplication::OnPaint proc

   .new rcClient:RECT
   .new ps:PAINTSTRUCT
   .new height:int_t = 0

   .new hdc:HDC = BeginPaint(m_hwnd, &ps)

    ; get the dimensions of the main window.

    GetClientRect(m_hwnd, &rcClient)

    mov m_rc.left,50
    mov eax,m_width
    sub eax,50
    mov m_rc.right,eax

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

    .if ( htitle != NULL )

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

    .if ( hdescription != NULL )

       .new hOldFont:HFONT = SelectObject(hdc, hdescription)

        mov eax,height
        add eax,40
        mov rcClient.top,eax
        mov rcClient.left,50

        DrawText(hdc, "This sample use the CApplication class and GDI+", -1, &rcClient, DT_WORDBREAK)

        add eax,rcClient.top
        add eax,6
        mov m_rc.top,eax
        mov eax,m_height
        sub eax,100
        mov rcClient.top,eax
        sub eax,16
        mov m_rc.bottom,eax
        mov eax,m_width
        shr eax,1
        mov rcClient.left,eax

        DrawText(hdc,
            "A) Use keys UP or DOWN to adjust the speed.\n"
            "B) Escape to exit the application.", -1, &rcClient, DT_WORDBREAK)
        SelectObject(hdc, hOldFont)
        DeleteObject(hdescription)
    .endif
    EndPaint(m_hwnd, &ps)

    mov edx,m_rc.bottom
    sub edx,m_rc.top
    .ifs ( edx > 100 )
        mov ecx,m_rc.right
        sub ecx,m_rc.left
        .ifs ( ecx > 100 )

            mov hdc,GetDC(m_hwnd)
            mov ecx,m_rc.right
            sub ecx,m_rc.left
            mov edx,m_rc.bottom
            sub edx,m_rc.top
            mov m_bitmap,CreateCompatibleBitmap(hdc, ecx, edx)
            ReleaseDC(m_hwnd, hdc)

            mov eax,m_rc.right
            sub eax,m_rc.left
            shr eax,1
            mov ecx,m_rc.bottom
            sub ecx,m_rc.top
            shr ecx,1
            .new i:int_t
            .for ( rdx = &m_obj, i = 0: i < MAXOBJ: i++, rdx += sizeof(object) )
                mov [rdx].object.m_pos.x,eax
                mov [rdx].object.m_pos.y,ecx
            .endf
        .endif
    .endif
   .return 1

    endp


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

    endp


; Creates the application window

CApplication::CreateApplicationWindow proc

    .new wc:WNDCLASSEX = {
        WNDCLASSEX,                     ; .cbSize
        CS_HREDRAW or CS_VREDRAW,       ; .style
        &WindowProc,                    ; .lpfnWndProc
        0,                              ; .cbClsExtra
        sizeof(LONG_PTR),               ; .cbWndExtra
        m_hInstance,                    ; .hInstance
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

    .new rect:RECT = { 0, 0, m_width, m_height }

    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW or WS_CAPTION or WS_SYSMENU or WS_MINIMIZEBOX, FALSE)

    mov eax,rect.right
    sub eax,rect.left
    mov m_width,eax

    mov eax,rect.bottom
    sub eax,rect.top
    mov m_height,eax
    mov m_hwnd,CreateWindowEx(0, CLASS_NAME, WINDOW_NAME, WS_OVERLAPPEDWINDOW or WS_CAPTION or WS_SYSMENU or WS_MINIMIZEBOX,
           CW_USEDEFAULT, CW_USEDEFAULT, m_width, m_height, NULL, NULL, m_hInstance, rbx)
    test rax,rax
    mov eax,S_OK
    .ifz
        mov eax,E_UNEXPECTED
    .endif
    ret
    endp


; Provides the entry point to the application

CApplication::CApplication proc instance:HINSTANCE

    @ComAlloc(CApplication)

    mov rcx,instance
    mov [rax].CApplication.m_hInstance,rcx
    mov [rax].CApplication.m_width,900
    mov [rax].CApplication.m_height,600
    ret

    endp


_tWinMain proc WINAPI hInstance:HINSTANCE, hPrevInstance:HINSTANCE, pszCmdLine:LPTSTR, iCmdShow:int_t

    .new app:ptr CApplication(hInstance)
    .return app.Run()

    endp

    end _tstart
