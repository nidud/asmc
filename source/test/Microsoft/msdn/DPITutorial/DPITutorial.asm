
; DPITutorial.cpp : Defines the entry point for the application.

include stdafx.inc
include DPITutorial.inc

; Global Variables

.data
g_Dpi CDPI { 0, 0, PROCESS_DPI_UNAWARE } ; Helper class for scaling
g_szTitle TCHAR MAX_LOADSTRING dup(0)
g_szWindowClass TCHAR MAX_LOADSTRING dup(0)
g_pszString wchar_t MAX_LOADSTRING dup(0)
g_bRescaleOnDpiChanged bool true
g_nFontHeight UINT BUTTON_FONT_HEIGHT
g_hBmp HBITMAP 4 dup(0)
g_hButtonFont HFONT 0
g_hTextFont HFONT 0
rcNewScale RECT <>

.code
;
;  WinMain - Checks for S or P in command line, and sets the DPI awareness as specified
;
wWinMain proc hInstance:HINSTANCE, hPrevInstance:HINSTANCE, lpCmdLine:LPTSTR, nCmdShow:int_t

    .new msg:MSG
    .new hAccelTable:HACCEL

    ; Read command line and set awareness level if specified:
    ;        default = DPI unaware (0)
    ;   cmd line + S = System DPI aware (1)
    ;   cmd line + P = Per-monitor DPI aware (2)
    ;
    ; To provide a command-line parameter from within Visual Studio, press Alt+F7 to open the project Property Pages dialog
    ; then select the Debugging option in the left pane and add the argument to the Command Arguments field.

    .if (FindStringOrdinal(FIND_FROMSTART, lpCmdLine, -1, "p", -1, TRUE) >= 0)

        g_Dpi.SetAwareness(PROCESS_PER_MONITOR_DPI_AWARE)

    .elseif (FindStringOrdinal(FIND_FROMSTART, lpCmdLine, -1, "s", -1, TRUE) >= 0)

        g_Dpi.SetAwareness(PROCESS_SYSTEM_DPI_AWARE)
    .endif

    ; Initialize global strings
    wsprintf(&g_szTitle, "DPI Awareness Tutorial")
    wsprintf(&g_szWindowClass, "DPITUTORIAL")

    MyRegisterClass(hInstance)

    ; Perform application initialization:
    .if (!InitInstance(hInstance, nCmdShow))

        .return FALSE
    .endif

    mov hAccelTable,LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DPITUTORIAL))

    ; Main message loop:
    .while (GetMessage(&msg, NULL, 0, 0))

        .if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))

            TranslateMessage(&msg)
            DispatchMessage(&msg)
        .endif
    .endw

    .return msg.wParam
wWinMain endp

;
;  MyRegisterClass - registers the window class
;
MyRegisterClass proc hInstance:HINSTANCE

    local wcex:WNDCLASSEX

    mov wcex.cbSize,sizeof(WNDCLASSEX)

    mov wcex.style,CS_HREDRAW or CS_VREDRAW
    mov wcex.lpfnWndProc,&WndProc
    mov wcex.cbClsExtra,0
    mov wcex.cbWndExtra,0
    mov wcex.hInstance,hInstance
    mov wcex.hIcon,LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DPITUTORIAL))
    mov wcex.hCursor,LoadCursor(NULL, IDC_ARROW)
    mov wcex.hbrBackground,GetStockObject(COLOR_WINDOW + 1)
    mov wcex.lpszMenuName,MAKEINTRESOURCE(IDC_DPITUTORIAL)
    mov wcex.lpszClassName,&g_szWindowClass
    mov wcex.hIconSm,LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL))

    .return RegisterClassEx(&wcex)

MyRegisterClass endp

;
;   InitInstance:
;     Initializes the DPI
;     Creates the main window
;     Loads the bitmap resources
;
InitInstance proc hInstance:HINSTANCE, nCmdShow:int_t

    .new hWnd:HWND, hWndButton:HWND
    .new hMonitor:HMONITOR
    .new pt:POINT = { 1, 1 }
    .new dpix:UINT = 0
    .new dpiy:UINT = 0
    .new hr:HRESULT = E_FAIL

    ; Get the DPI for the main monitor, and set the scaling factor
    mov hMonitor,MonitorFromPoint(pt, MONITOR_DEFAULTTONEAREST)
    mov hr,GetDpiForMonitor(hMonitor, MDT_EFFECTIVE_DPI, &dpix, &dpiy)

    .if (hr != S_OK)

        MessageBox(NULL, "GetDpiForMonitor failed", "Notification", MB_OK)
       .return FALSE
    .endif
    g_Dpi.SetScale(dpix)

    ; Create main window and pushbutton window

    .new x:int_t = g_Dpi.Scale(100)
    .new y:int_t = g_Dpi.Scale(100)
    .new width:int_t = g_Dpi.Scale(WINDOW_WIDTH)
    .new height:int_t = g_Dpi.Scale(WINDOW_HEIGHT)

    mov hWnd,CreateWindowEx(0, &g_szWindowClass, &g_szTitle, WS_OVERLAPPEDWINDOW,
              x, y, width, height, NULL, NULL, hInstance, NULL)

    .if (!hWnd)

        .return FALSE
    .endif

    mov hWndButton,CreateWindowEx(0, "BUTTON", "&Rescale",
            WS_VISIBLE or WS_CHILD or BS_PUSHBUTTON, 0, 0, 0, 0, hWnd, IDM_RESCALE_NOW, hInstance, NULL)

    ; Load bitmaps for each scaling factor
    mov g_hBmp[0*HBITMAP],LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP100))
    mov g_hBmp[1*HBITMAP],LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP125))
    mov g_hBmp[2*HBITMAP],LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP150))
    mov g_hBmp[3*HBITMAP],LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP200))

    ; Create fonts for button and window text output
    CreateFonts(hWnd)

    ShowWindow(hWnd, nCmdShow)
    UpdateWindow(hWnd)
   .return TRUE
InitInstance endp

;
;  CreateScaledFont - Create a font close to the specified height
;
CreateScaledFont proc Height:int_t

    .new lf:LOGFONT = {0}
    .new hFont:HFONT

    mov lf.lfQuality,CLEARTYPE_QUALITY
    neg ecx
    mov lf.lfHeight,ecx

    .return CreateFontIndirect(&lf)

CreateScaledFont endp

;
;  CreateFonts creates fonts for button and window text output, appropriate for the DPI
;
CreateFonts proc hWnd:HWND

    .if (g_hButtonFont != NULL)

        DeleteObject(g_hButtonFont)
        mov g_hButtonFont,NULL
    .endif

    mov g_hButtonFont,CreateScaledFont(g_Dpi.Scale(BUTTON_FONT_HEIGHT))
    .if (g_hButtonFont == NULL)

        MessageBox(hWnd, "Failed to create scaled font for button", "Notification", MB_OK)
    .endif

    .if (g_hTextFont != NULL)

        DeleteObject(g_hTextFont)
        mov g_hTextFont,NULL
    .endif

    mov g_hTextFont,CreateScaledFont(g_Dpi.Scale(g_nFontHeight))
    .if (g_hTextFont == NULL)

        MessageBox(hWnd, "Failed to create scaled font for text", "Notification", MB_OK)
    .endif
    ret

CreateFonts endp

;
; RenderWindow - Draw the elements of the window: background color, rectangle (frame for bitmap),
;   bitmap (selected from resources based on DPI), and text (using a font based on the DPI)
;   The GetAwareness return value is used as an index into the string & color arrays
;
RenderWindow proc uses rsi rdi rbx hWnd:HWND

    .new hdc:HDC
    .new hdcMem:HDC
    .new hBrush:HBRUSH
    .new ps:PAINTSTRUCT
    .new rcText:RECT
    .new rcWin:RECT
    .new rcClient:RECT
    .new ptOffset:POINT
    .new awareText[3]:LPCWSTR = { "DPI Unaware", "System DPI Aware", "Per-Monitor DPI Aware" }
    .new colors[3]:COLORREF = { RGB(220, 120, 120), RGB(250, 250, 210), RGB(150, 250, 150) }
    .new bmp:BITMAP
    .new hbmpTemp:HBITMAP
    .new hbmpScaled:HBITMAP
    .new hWndButton:HWND
    .new nPad:UINT

    GetWindowRect(hWnd, &rcWin)
    GetClientRect(hWnd, &rcClient)
    mov nPad,g_Dpi.Scale(PADDING)

    mov hdc,BeginPaint(hWnd, &ps)
    SetBkMode(hdc, TRANSPARENT)

    ; Render client area background
    g_Dpi.GetAwareness()
    mov hBrush,CreateSolidBrush(colors[rax*4])
    FillRect(hdc, &rcClient, hBrush)

    ; Select the appropriate bitmap for the scaling factor and load it into memory
    .if (g_Dpi.GetAwareness() == PROCESS_DPI_UNAWARE)

        mov hbmpScaled,g_hBmp[0*HBITMAP]

    .else

        .switch (g_Dpi.GetScale())

        .case 125
            mov hbmpScaled,g_hBmp[1*HBITMAP]
            .endc

        .case 150
            mov hbmpScaled,g_hBmp[2*HBITMAP]
            .endc

        .case 200
            mov hbmpScaled,g_hBmp[3*HBITMAP]
            .endc

        .default
            mov hbmpScaled,g_hBmp[0*HBITMAP]
            .endc
        .endsw
    .endif
    mov hdcMem,CreateCompatibleDC(NULL)
    mov hbmpTemp,SelectBitmap(hdcMem, hbmpScaled)
    GetObject(hbmpScaled, sizeof(bmp), &bmp)

    ; Render a rectangle to frame the bitmap in the lower-right of the window
    mov edx,rcClient.right
    sub edx,bmp.bmWidth
    sub edx,nPad
    mov ptOffset.x,edx

    mov r8d,rcClient.bottom
    sub r8d,bmp.bmHeight
    sub r8d,nPad
    mov ptOffset.y,r8d

    mov eax,nPad
    shr eax,1
    sub edx,eax
    sub r8d,eax
    mov r9d,rcClient.right
    sub r9d,eax
    mov ecx,rcClient.bottom
    sub ecx,eax

    Rectangle(hdc, edx, r8d, r9d,  ecx)

    ; Render bitmap
    BitBlt(hdc, ptOffset.x, ptOffset.y, bmp.bmWidth, bmp.bmHeight, hdcMem, 0, 0, SRCCOPY)
    SelectBitmap(hdcMem, hbmpTemp)
    DeleteDC(hdcMem)

    ; Render button

    SelectObject(hdc, g_hButtonFont)
    mov hWndButton,GetWindow(hWnd, GW_CHILD)

    mov esi,g_Dpi.Scale(WINDOW_HEIGHT)
    mov edi,g_Dpi.Scale(WINDOW_WIDTH)
    mov r8d,rcClient.left
    add r8d,nPad
    mov r9d,rcClient.bottom
    sub r9d,esi
    sub r9d,nPad
    SetWindowPos(hWndButton, HWND_TOP, r8d, r9d, edi, esi, SWP_SHOWWINDOW)

    SendMessage(hWndButton, WM_SETFONT, g_hButtonFont, TRUE)
    UpdateWindow(hWndButton)

    .if ((g_Dpi.GetAwareness() == PROCESS_PER_MONITOR_DPI_AWARE) && (g_bRescaleOnDpiChanged == false))
        mov edx,TRUE
    .else
        mov edx,FALSE
    .endif
    EnableWindow(hWndButton, edx)

    ; Render Text
    SelectObject(hdc, g_hTextFont)

    mov eax,rcClient.left
    add eax,nPad
    mov rcText.left,eax
    mov eax,rcClient.top
    add eax,nPad
    mov rcText.top,eax

    g_Dpi.GetAwareness()
    mov r8,awareText[rax*LPCWSTR]
    wsprintf(&g_pszString, "%s Window", r8)
    DrawText(hdc, &g_pszString, -1, &rcText, DT_CALCRECT or DT_LEFT or DT_TOP)
    DrawText(hdc, &g_pszString, -1, &rcText, DT_LEFT or DT_TOP)

    mov eax,rcText.bottom
    add eax,nPad
    mov rcText.top,eax

    wsprintf(&g_pszString, "Scaling: %i%%", g_Dpi.GetScale())
    DrawText(hdc, &g_pszString, -1, &rcText, DT_CALCRECT or DT_LEFT or DT_TOP)
    DrawText(hdc, &g_pszString, -1, &rcText, DT_LEFT or DT_TOP)

    mov eax,rcText.bottom
    add eax,nPad
    mov rcText.top,eax

    wsprintf(&g_pszString, "Position: (%i, %i) to (%i, %i)", rcWin.left, rcWin.top, rcWin.right, rcWin.bottom)
    DrawText(hdc, &g_pszString, -1, &rcText, DT_CALCRECT or DT_LEFT or DT_TOP)
    DrawText(hdc, &g_pszString, -1, &rcText, DT_LEFT or DT_TOP)

    mov eax,rcText.bottom
    add eax,nPad
    mov rcText.top,eax

    mov r8d,RectWidth(rcWin)
    mov r9d,RectHeight(rcWin)
    wsprintf(&g_pszString, "Size: %i x %i", r8d, r9d)
    DrawText(hdc, &g_pszString, -1, &rcText, DT_CALCRECT or DT_LEFT or DT_TOP)
    DrawText(hdc, &g_pszString, -1, &rcText, DT_LEFT or DT_TOP)

    mov eax,rcText.bottom
    add eax,nPad
    mov rcText.top,eax

    wsprintf(&g_pszString, "Font height: %i (%i unscaled)", g_Dpi.Scale(g_nFontHeight), g_nFontHeight)
    DrawText(hdc, &g_pszString, -1, &rcText, DT_CALCRECT or DT_LEFT or DT_TOP)
    DrawText(hdc, &g_pszString, -1, &rcText, DT_LEFT or DT_TOP)

    ; Cleanup
    EndPaint(hWnd, &ps)
    DeleteObject(hBrush)
    DeleteDC(hdc)
    ret

RenderWindow endp

;
;  WndProc:  Message handler
;
WndProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

    .new lRet:LRESULT = 0
    .new hWndButton:HWND
    .new hMenu:HMENU
    .new mii:MENUITEMINFO
    .new lprcNewScale:LPRECT

    .switch (message)

    .case WM_CREATE
        ; Initialize window rect
        GetWindowRect(hWnd, &rcNewScale)

        ; Initialize menu bar
        mov hMenu,GetMenu(hWnd)

        ; Set the default (selected) state of the menu item
        mov mii.cbSize,sizeof(MENUITEMINFO)
        mov mii.fMask,MIIM_STATE
        mov eax,MFS_UNCHECKED
        .if (g_bRescaleOnDpiChanged == true)
            mov eax,MFS_CHECKED
        .endif
        mov mii.fState,eax
        SetMenuItemInfo(hMenu, IDM_RESCALE_ON_DPICHANGED, FALSE, &mii)

        ; Disable the "Rescale on DPICHANGED" menu item unless the app is DPI Aware
        .if (g_Dpi.GetAwareness() == PROCESS_PER_MONITOR_DPI_AWARE)

            .endc
        .endif

        mov mii.cbSize,sizeof(MENUITEMINFO)
        mov mii.fMask,MIIM_STATE
        mov mii.fState,MFS_DISABLED
        SetMenuItemInfo(hMenu, IDM_RESCALE_ON_DPICHANGED, FALSE, &mii)
        .endc

    .case WM_DPICHANGED
        ; This message tells the program that most of its window is on a monitor with a new DPI.
        ; The wParam contains the new DPI, and the lParam contains a rect which defines the window
        ; rectangle scaled to the new DPI.

        movzx edx,word ptr wParam
        g_Dpi.SetScale(edx) ; Set the new DPI, retrieved from the wParam

        .if (g_Dpi.GetAwareness() != PROCESS_PER_MONITOR_DPI_AWARE)

            .endc
        .endif

        mov lprcNewScale,lParam ; Get the window rectangle scaled for the new DPI, retrieved from the lParam
        CopyRect(&rcNewScale, lprcNewScale) ; Save the rectangle for the on-demand rescale option (IDM_RESCALE_NOW)

        .if (g_bRescaleOnDpiChanged)

            ; For the new DPI: resize the window, select new fonts, and re-render window content

            mov rcx,lprcNewScale
            mov r8d,[rcx].RECT.left
            mov r9d,[rcx].RECT.top
            mov edx,[rcx].RECT.right
            sub edx,r8d
            mov ecx,[rcx].RECT.bottom
            sub ecx,r9d

            SetWindowPos(hWnd, HWND_TOP, r8d, r9d, edx, ecx, SWP_NOZORDER or SWP_NOACTIVATE)
            CreateFonts(hWnd)
            RedrawWindow(hWnd, NULL, NULL, RDW_ERASE or RDW_INVALIDATE)
        .endif
        .endc

    .case WM_PAINT
        RenderWindow(hWnd)
        .endc

    .case WM_EXITSIZEMOVE
        .if (g_bRescaleOnDpiChanged)

            ; Refresh the window to display its new position
            RedrawWindow(hWnd, NULL, NULL, RDW_ERASE or RDW_INVALIDATE)
        .endif
        .endc

    .case WM_COMMAND
        ; Respond to user input from the keyboard or menu options

        movzx edx,word ptr wParam
        .switch ( edx )

        .case IDM_RESCALE_NOW  ; The "Rescale" pushbutton was clicked
            .if (!g_bRescaleOnDpiChanged)

                ; For the new DPI: resize the window, select new fonts, and re-render window content
                mov ecx,RectWidth(rcNewScale)
                SetWindowPos(hWnd,
                            HWND_TOP,
                            0,  ; Position origin ignored (per SWP_NOMOVE)
                            0,  ; Position origin ignored (per SWP_NOMOVE)
                            ecx,
                            RectHeight(rcNewScale),
                            SWP_NOMOVE or SWP_NOZORDER or SWP_NOACTIVATE)
                CreateFonts(hWnd)
                RedrawWindow(hWnd, NULL, NULL, RDW_ERASE or RDW_INVALIDATE)
                SetFocus(hWnd) ; Return focus from pushbutton to main window
            .endif
            .endc

        .case IDM_RESCALE_ON_DPICHANGED  ; The "Rescale on DPICHANGED" menu item was selected
            xor g_bRescaleOnDpiChanged,1; = !g_bRescaleOnDpiChanged;

            mov hMenu,GetMenu(hWnd) ; Toggle the selected/unselected state of the menu item
            mov mii.cbSize,sizeof(MENUITEMINFO)
            mov mii.fMask,MIIM_STATE
            mov eax,MFS_UNCHECKED
            .if (g_bRescaleOnDpiChanged)
                mov eax,MFS_CHECKED
            .endif
            mov mii.fState,eax
            SetMenuItemInfo(hMenu, IDM_RESCALE_ON_DPICHANGED, FALSE, &mii)

            mov hWndButton,GetWindow(hWnd, GW_CHILD) ; Toggle the enabled/disabled state of the pushbutton
            mov edx,FALSE
            .if (g_bRescaleOnDpiChanged == false)
                mov edx,TRUE
            .endif
            EnableWindow(hWndButton, edx)
            RenderWindow(hWnd)
            .endc

        .case IDM_FONT_INCREASE
            add g_nFontHeight,5
            .if (g_nFontHeight > WINDOW_HEIGHT / 5)

                mov g_nFontHeight,WINDOW_HEIGHT / 5
            .endif
            CreateFonts(hWnd)
            RedrawWindow(hWnd, NULL, NULL, RDW_ERASE or RDW_INVALIDATE)
            .endc

        .case IDM_FONT_DECREASE
            sub g_nFontHeight,5
            .if (g_nFontHeight < 10)

                mov g_nFontHeight,10
            .endif
            CreateFonts(hWnd)
            RedrawWindow(hWnd, NULL, NULL, RDW_ERASE or RDW_INVALIDATE)
            .endc

        .case IDM_EXIT
            DestroyWindow(hWnd)
            .endc

        .default
            .return DefWindowProc(hWnd, message, wParam, lParam)
        .endsw
        .endc

    .case WM_DESTROY
        DeleteObject(g_hButtonFont)
        DeleteObject(g_hTextFont)
        PostQuitMessage(0)
        .endc
    .case WM_CHAR
        .gotosw(WM_DESTROY) .if wParam == VK_ESCAPE
        .endc

    .default
        .return DefWindowProc(hWnd, message, wParam, lParam)
    .endsw
    .return lRet

WndProc endp

    end
