
include CApplication.inc

define CLASS_NAME   <"MainWindowClass">
define WINDOW_NAME  <"Windows samples">
define ID_TIMER     1

    .code

BoundRand proc b:uint_t

    mov eax,ecx
    neg eax
    xor edx,edx
    div ecx
    .while 1
        rdrand eax
        .break .if ( eax >= edx )
    .endw
    xor edx,edx
    div ecx
    mov eax,edx
    ret

BoundRand endp

RangeRand proc b:uint_t, m:uint_t

    .whiled ( BoundRand(ecx) <= m )
    .endw
    ret

RangeRand endp

RandRGB proc

    mov r8d,BoundRand(0xFF)
    shl r8d,8
    BoundRand(0xFF)
    mov r8b,al
    shl r8d,8
    BoundRand(0xFF)
    or  eax,r8d
    or  eax,0xFF000000
    ret

RandRGB endp

; -- CGFont --

   assume rbx:ptr CGFont

CGFont::Release proc uses rbx

    mov rbx,rcx
    .if ( [rbx].m_font )
        GdipDeleteFont([rbx].m_font)
    .endif
    .if ( [rbx].m_family )
        GdipDeleteFontFamily([rbx].m_family)
    .endif
    .if ( [rbx].m_format )
        GdipDeleteStringFormat([rbx].m_format)
    .endif
    .if ( [rbx].m_gp )
        GdipDeleteGraphics([rbx].m_gp)
    .endif
    .if ( [rbx].m_file )
        RemoveFontResource([rbx].m_file)
        this.m_dwFormat.Release()
    .endif
    CoTaskMemFree(rbx)
    ret

CGFont::Release endp

CGFont::SetFamily proc uses rbx family:ptr wchar_t

    mov rbx,this;rcx
    .if ( [rbx].m_family )
        GdipDeleteFontFamily([rbx].m_family)
    .endif
    GdipCreateFontFamilyFromName(family, NULL, &[rbx].m_family)
    ret

CGFont::SetFamily endp

CGFont::SetColor proc color:ARGB

    mov [rcx].CGFont.m_color,edx
    mov eax,Ok
    ret

CGFont::SetColor endp

CGFont::SetSize proc uses rbx size:int_t

    mov rbx,this;rcx
    .if ( [rbx].m_font )
        GdipDeleteFont([rbx].m_font)
    .endif
    cvtsi2ss xmm1,size
    GdipCreateFont([rbx].m_family, xmm1, [rbx].m_style, [rbx].m_unit, &[rbx].m_font)
    ret

CGFont::SetSize endp

CGFont::SetFont proc name:ptr wchar_t, size:int_t, color:ARGB

mov rax,this
    mov [rcx].CGFont.m_color,r9d
    this.SetFamily(rdx)
    this.SetSize(size)
    ret

CGFont::SetFont endp

CGFont::SetFormat proc FormatFlags:StringFormatFlags

    .if ( [rcx].CGFont.m_format == NULL )
        GdipCreateStringFormat(FormatFlags, LANG_NEUTRAL, &[rcx].CGFont.m_format)
    .else
        GdipSetStringFormatFlags([rcx].CGFont.m_format, FormatFlags)
    .endif
    ret

CGFont::SetFormat endp

CGFont::SetAlignment proc uses rbx Alignment:StringAlignment

    mov rbx,rcx
    .if ( [rbx].m_format == NULL )
        GdipCreateStringFormat(0, LANG_NEUTRAL, &[rbx].m_format)
    .endif
    GdipSetStringFormatAlign([rbx].m_format, Alignment)
    ret

CGFont::SetAlignment endp

CGFont::SetGDI proc uses rbx hdc:HDC, width:int_t, height:int_t

    mov rbx,rcx
    mov [rbx].m_width,r8d
    mov [rbx].m_height,r9d

    .if ( [rbx].m_gp )
        GdipDeleteGraphics([rbx].m_gp)
        mov [rbx].m_gp,NULL
    .endif
    GdipCreateFromHDC(hdc, &[rbx].m_gp)
    mov rax,[rbx].m_gp
    ret

CGFont::SetGDI endp

CGFont::GetGDI proc

    mov rax,[rcx].CGFont.m_gp
    ret

CGFont::GetGDI endp

CGFont::DrawString proc uses rbx rc:ptr RECT, string:ptr wchar_t, size:int_t

 local rect:RectF
 local brush:ptr

    mov      rbx,rcx
    cvtsi2ss xmm0,[rdx].RECT.left
    movss    rect.X,xmm0
    cvtsi2ss xmm0,[rdx].RECT.top
    movss    rect.Y,xmm0
    mov      eax,[rdx].RECT.right
    sub      eax,[rdx].RECT.left
    cvtsi2ss xmm0,eax
    movss    rect.Width,xmm0
    mov      eax,[rdx].RECT.bottom
    sub      eax,[rdx].RECT.top
    cvtsi2ss xmm0,eax
    movss    rect.Height,xmm0

    GdipCreateSolidFill([rbx].m_color, &brush)
    GdipDrawString([rbx].m_gp, string, size, [rbx].m_font, &rect, [rbx].m_format, brush)
    GdipDeleteBrush(brush)
    ret

CGFont::DrawString endp

CGFont::Draw proc uses rbx x:int_t, y:int_t, format:ptr wchar_t, argptr:vararg

 local buffer[512]:wchar_t
 local rc:RECT

    mov rbx,rcx
    mov rc.left,edx
    mov rc.top,r8d
    mov rc.right,[rbx].m_width
    mov rc.bottom,[rbx].m_height

    vswprintf(&buffer, format, &argptr)
    [rbx].DrawString(&rc, &buffer, -1)
    ret

CGFont::Draw endp

CGFont::LoadFont proc uses rbx file:ptr wchar_t, size:int_t

   .new hr:HRESULT
   .new dwriteFactory3:ptr IDWriteFactory3

    mov rbx,rcx
    mov hr,DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, &IID_IDWriteFactory3, &dwriteFactory3)
    .if (SUCCEEDED(hr))

       .new m_dwFactory:ptr IDWriteFactory5
        mov hr,dwriteFactory3.QueryInterface(&IID_IDWriteFactory5, &m_dwFactory)

        .if (SUCCEEDED(hr) && AddFontResource(file))

           .new m_dwFontColl:ptr IDWriteFontCollection1
            mov hr,m_dwFactory.GetSystemFontCollection(0, &m_dwFontColl, FALSE)

            .if (SUCCEEDED(hr))

                mov hr,m_dwFactory.CreateTextFormat(
                    IDS_FONT2,
                    m_dwFontColl,
                    DWRITE_FONT_WEIGHT_NORMAL,
                    DWRITE_FONT_STYLE_ITALIC,
                    DWRITE_FONT_STRETCH_NORMAL,
                    14.0,
                    "",
                    &[rbx].m_dwFormat)

                .if (SUCCEEDED(hr))
                    [rbx].SetFamily(IDS_FONT2)
                    ;[rbx].SetFont(IDS_FONT2, size, Gray)
                    mov [rbx].m_file,file
                .endif
                m_dwFontColl.Release()
            .endif
            m_dwFactory.Release()
        .endif
        dwriteFactory3.Release()
    .endif
    .return hr

CGFont::LoadFont endp

CGFont::CGFont proc uses rdi rbx family:ptr wchar_t, file:ptr wchar_t, Format:StringFormatFlags

   .return .if !CoTaskMemAlloc(CGFont + CGFontVtbl)

    mov rbx,rax
    mov rdi,rax
    xor eax,eax
    mov ecx,CGFont
    rep stosb

    mov [rbx].m_style,FontStyleRegular
    mov [rbx].m_unit,UnitPoint
    mov [rbx].m_color,Gray

    lea rdx,[rbx+CGFont]
    mov [rbx],rdx

    for q,<Release,SetFamily,SetColor,SetSize,SetFont,SetFormat,SetGDI,
           GetGDI,Draw,DrawString,SetAlignment>
        lea rcx,CGFont_&q
        mov [rdx].CGFontVtbl.&q,rcx
        endm

    .if ( file )

       .new hr:HRESULT
       .new dwriteFactory3:ptr IDWriteFactory3
        mov hr,DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, &IID_IDWriteFactory3, &dwriteFactory3)

        .if (SUCCEEDED(hr))

           .new m_dwFactory:ptr IDWriteFactory5
            mov hr,dwriteFactory3.QueryInterface(&IID_IDWriteFactory5, &m_dwFactory)

            .if (SUCCEEDED(hr))

                .if ( AddFontResource(file) )

                   .new m_dwFontColl:ptr IDWriteFontCollection1
                    mov hr,m_dwFactory.GetSystemFontCollection(0, &m_dwFontColl, FALSE)

                    .if (SUCCEEDED(hr))

                        mov hr,m_dwFactory.CreateTextFormat(
                            family,
                            m_dwFontColl,
                            DWRITE_FONT_WEIGHT_NORMAL,
                            DWRITE_FONT_STYLE_ITALIC,
                            DWRITE_FONT_STRETCH_NORMAL,
                            14.0,
                            "",
                            &[rbx].m_dwFormat)

                        .if (SUCCEEDED(hr))

                            mov [rbx].m_file,file
                            [rbx].SetFamily(family)
                        .endif
                        m_dwFontColl.Release()
                    .endif
                    m_dwFactory.Release()
                .endif
                dwriteFactory3.Release()
            .endif
        .endif
    .elseif ( family )
        [rbx].SetFamily(family)
    .endif
    .if ( Format )
        [rbx].SetFormat(Format)
    .endif
    mov rax,rbx
    ret

CGFont::CGFont endp

    assume rbx:nothing

; -- CApplication --

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

    mov rdi,rcx
    .if ( [rdi].m_hwnd == NULL )

        mov bSucceeded,FALSE
    .endif

    .if ( bSucceeded )

        mov [rdi].m_f1,CGFont(IDS_FONT, NULL, StringFormatFlagsNoWrap)
        mov [rdi].m_f3,CGFont(IDS_FONT, NULL, StringFormatFlagsNoWrap)
        mov [rdi].m_f2,CGFont(IDS_FONT2, "Caudex-Italic.ttf", StringFormatFlagsNoWrap)
        this.m_f2.SetAlignment(StringAlignmentCenter)
        ShowWindow([rdi].m_hwnd, SW_SHOW)
        UpdateWindow([rdi].m_hwnd)
        SetTimer([rdi].m_hwnd, ID_TIMER, [rdi].m_timer, NULL)
        GetWindowRect([rdi].m_hwnd, &[rdi].m_rect)
        this.GoPartialScreen()
    .endif

    .return bSucceeded

CApplication::ShowApplicationWindow endp


; Destroys the applicaiton window

CApplication::DestroyApplicationWindow proc uses rdi

    mov rdi,rcx
    .if ( [rdi].m_hwnd != NULL )

        .if ( [rdi].m_f1 )
            this.m_f1.Release()
        .endif
        .if ( [rdi].m_f2 )
            this.m_f2.Release()
        .endif
        .if ( [rdi].m_f3 )
            this.m_f2.Release()
        .endif
        .if ( [rdi].m_mem )
            DeleteDC([rdi].m_mem)
        .endif
        .if ( [rdi].m_hdc )
            ReleaseDC([rdi].m_hwnd, [rdi].m_hdc)
        .endif
        .if ( [rdi].m_bitmap )
            DeleteObject( [rdi].m_bitmap )
        .endif
        KillTimer( [rdi].m_hwnd, ID_TIMER )
        DestroyWindow( [rdi].m_hwnd )
        mov [rdi].m_hwnd,NULL
    .endif
    ret

CApplication::DestroyApplicationWindow endp


CApplication::OnSize proc uses rdi lParam:LPARAM

  local width:int_t
  local height:int_t

    mov rdi,rcx
    movzx eax,dx
    shr edx,16
    mov width,eax
    mov height,edx
    mov [rdi].m_rc.top,0
    mov [rdi].m_rc.left,0
    mov [rdi].m_rc.right,eax
    mov [rdi].m_rc.bottom,edx

    .if ( [rdi].m_isFullScreen == FALSE )
        mov [rdi].m_rc.top,130
        mov [rdi].m_rc.left,50
        sub [rdi].m_rc.right,50
        sub [rdi].m_rc.bottom,100
    .endif
    mov eax,[rdi].m_rc.bottom
    sub eax,[rdi].m_rc.top
    shr eax,1
    mov [rdi].m_texty,eax
    .if ( [rdi].m_mem )
        DeleteDC([rdi].m_mem)
    .endif
    .if ( [rdi].m_hdc )
        ReleaseDC([rdi].m_hwnd, [rdi].m_hdc)
    .endif
    .if ( [rdi].m_bitmap )
        DeleteObject([rdi].m_bitmap)
        mov [rdi].m_bitmap,NULL
    .endif
    mov [rdi].m_hdc,GetDC([rdi].m_hwnd)
    mov [rdi].m_mem,CreateCompatibleDC(rax)
    mov [rdi].m_g1,this.m_f1.SetGDI([rdi].m_hdc, width, height)
    mov edx,[rdi].m_rc.bottom
    sub edx,[rdi].m_rc.top
    .ifs ( edx > 100 )
        mov ecx,[rdi].m_rc.right
        sub ecx,[rdi].m_rc.left
        .ifs ( ecx > 100 )
            mov [rdi].m_bitmap,CreateCompatibleBitmap([rdi].m_hdc, ecx, edx)
            [rdi].InitObjects()
            SelectObject([rdi].m_mem, [rdi].m_bitmap)
            this.m_f3.SetGDI([rdi].m_mem, [rdi].m_rc.right, [rdi].m_rc.bottom)
            mov ecx,[rdi].m_rc.right
            sub ecx,[rdi].m_rc.left
            mov [rdi].m_g2,this.m_f2.SetGDI([rdi].m_mem, ecx, [rdi].m_rc.bottom)
            GdipSetSmoothingMode(rax, SmoothingModeHighQuality)
            this.m_f2.SetSize(48)
            this.m_f3.SetSize(12)
        .endif
    .endif
    .return 1

CApplication::OnSize endp


    assume rsi:ptr object

CApplication::OnTimer proc uses rsi rdi rbx

    mov rdi,rcx
   .return 0 .if ( [rdi].m_bitmap == NULL )

    GdipGraphicsClear([rdi].m_g2, ColorAlpha(Black, 230))

   .new count:SINT = 1
   .new FullTranslucent:ARGB = ColorAlpha(Black, 230)
   .new p:ptr
   .new b:ptr

    GdipCreatePath(FillModeAlternate, &p)

    .for ( rsi = &[rdi].m_obj, ebx = 0: ebx < [rdi].m_count: ebx++, rsi += sizeof(object) )

        mov ecx,[rsi].m_radius
        mov edx,[rsi].m_pos.x
        sub edx,ecx
        mov r8d,[rsi].m_pos.y
        sub r8d,ecx
        add ecx,ecx
        GdipAddPathEllipseI(p, edx, r8d, ecx, ecx)
        GdipCreatePathGradientFromPath(p, &b)
        GdipSetPathGradientCenterColor(b, [rsi].m_color)
        GdipSetPathGradientSurroundColorsWithCount(b, &FullTranslucent, &count)
        mov ecx,[rsi].m_radius
        mov r8d,[rsi].m_pos.x
        sub r8d,ecx
        mov r9d,[rsi].m_pos.y
        sub r9d,ecx
        add r8d,2
        add r9d,2
        add ecx,ecx
        sub ecx,4
        GdipFillEllipseI([rdi].m_g2, b, r8d, r9d, ecx, ecx)
        GdipDeleteBrush(b)
        GdipResetPath(p)
    .endf
    GdipDeletePath(p)

    this.m_f2.Draw(0, [rdi].m_texty,
        "Caudex Version 1.01\n"
        "TrueType Font\n\n"
        "Loaded from disk file\n"
        "Caudex-Italic.ttf")

    mov ecx,[rdi].m_rc.right
    sub ecx,[rdi].m_rc.left
    shr ecx,4
    mov edx,[rdi].m_rc.bottom
    sub edx,[rdi].m_rc.top
    sub edx,52
    this.m_f3.Draw(ecx, edx, "Timer: %d\nObjects: %d", [rdi].m_timer, [rdi].m_count)

    sub [rdi].m_texty,2
    .if ( [rdi].m_texty < -350 )
        mov eax,[rdi].m_rc.bottom
        sub eax,[rdi].m_rc.top
        mov [rdi].m_texty,eax
    .endif

    mov ecx,[rdi].m_rc.right
    sub ecx,[rdi].m_rc.left
    mov edx,[rdi].m_rc.bottom
    sub edx,[rdi].m_rc.top
    BitBlt([rdi].m_hdc, [rdi].m_rc.left, [rdi].m_rc.top, ecx, edx, [rdi].m_mem, 0, 0, SRCCOPY)

    .for ( rsi = &[rdi].m_obj, ebx = 0: ebx < [rdi].m_count: ebx++, rsi += sizeof(object) )

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

    .switch edx
    .case VK_DOWN
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
        .for ( rdx = &[rcx].m_obj, ecx = 0: ecx < MAXOBJ: ecx++, rdx += sizeof(object) )
            .if ( [rdx].object.m_mov.x < 30 && [rdx].object.m_mov.x > -30 )
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
            .endif
        .endf
        .endc
    .case VK_RETURN
        this.InitObjects()
        .endc
    .case VK_NEXT
        .if ( [rcx].m_timer > 10 )
            dec [rcx].m_timer
            SetTimer([rcx].m_hwnd, ID_TIMER, [rcx].m_timer, NULL)
        .endif
        .endc
    .case VK_PRIOR
        inc [rcx].m_timer
        SetTimer([rcx].m_hwnd, ID_TIMER, [rcx].m_timer, NULL)
        .endc
    .case VK_F11
        .if ( [rcx].m_isFullScreen )
            this.GoPartialScreen()
        .else
            this.GoFullScreen()
        .endif
        .endc
    .endsw
    .return 0

CApplication::OnKeyDown endp


; Handles the WM_CLOSE message

CApplication::OnClose proc

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

    assume rcx:nothing

CApplication::OnPaint proc uses rdi

  local ps:PAINTSTRUCT

    mov rdi,rcx
    BeginPaint([rdi].m_hwnd, &ps)

    .if ( [rdi].m_isFullScreen == FALSE )

       .new font:ptr CGFont = [rdi].m_f1
        font.SetSize(20)
        font.Draw(50, 32, "CApplication RDRAND")
        font.SetSize(12)
        font.Draw(50, 10, "Windows samples")
        font.Draw(50, 73,
                "This sample use the CApplication class and GDI+\n"
                "Random Count, Speed, Color, and Size")
        mov ecx,[rdi].m_rc.bottom
        add ecx,8
        mov edx,[rdi].m_rc.right
        shr edx,1
        font.Draw(edx, ecx,
                "Use keys UP or DOWN to adjust the speed.\n"
                "Use keys PGUP or PGDN to adjust the timer.\n"
                "Use Enter to reset and F11 to toggle full screen.")
    .endif
    EndPaint([rdi].m_hwnd, &ps)
   .return 1

CApplication::OnPaint endp


CApplication::InitObjects proc uses rsi rdi rbx

    mov rdi,rcx
    mov [rdi].m_count,RangeRand(MAXOBJ, 1)

    .for ( rsi = &[rdi].m_obj, ebx = 0: ebx < [rdi].m_count: ebx++, rsi += sizeof(object) )

        mov ecx,[rdi].m_rc.right
        mov edx,[rdi].m_rc.bottom
        cmp ecx,edx
        cmova ecx,edx
        shr ecx,3
        mov [rsi].m_radius,RangeRand(ecx, 8)
        mov [rsi].m_mov.x,RangeRand(10, 1)
        mov [rsi].m_mov.y,RangeRand(10, 1)
        mov [rsi].m_color,RandRGB()
        mov ecx,[rdi].m_rc.right
        sub ecx,[rdi].m_rc.left
        sub ecx,[rsi].m_radius
        mov [rsi].m_pos.x,RangeRand(ecx, [rsi].object.m_radius)
        mov ecx,[rdi].m_rc.bottom
        sub ecx,[rdi].m_rc.top
        sub ecx,[rsi].m_radius
        mov [rsi].m_pos.y,RangeRand(ecx, [rsi].object.m_radius)
    .endf
    ret

CApplication::InitObjects endp


; Makes the host window full-screen by placing non-client elements outside the display.

CApplication::GoFullScreen proc uses rdi

    mov rdi,rcx
    mov [rdi].m_isFullScreen,TRUE

    ; The window must be styled as layered for proper rendering.
    ; It is styled as transparent so that it does not capture mouse clicks.
    SetWindowLong([rdi].m_hwnd, GWL_EXSTYLE, WS_EX_TOPMOST or WS_EX_LAYERED or WS_EX_TRANSPARENT)

    ; Give the window a system menu so it can be closed on the taskbar.
    SetWindowLong([rdi].m_hwnd, GWL_STYLE,  WS_CAPTION or WS_SYSMENU)

    ; Calculate the span of the display area.
   .new hDC:HDC = GetDC(NULL)
   .new xSpan:int_t = GetSystemMetrics(SM_CXSCREEN)
   .new ySpan:int_t = GetSystemMetrics(SM_CYSCREEN)
    ReleaseDC(NULL, hDC)

    ; Calculate the size of system elements.
   .new xBorder:int_t = GetSystemMetrics(SM_CXFRAME)
   .new yCaption:int_t = GetSystemMetrics(SM_CYCAPTION)
   .new yBorder:int_t = GetSystemMetrics(SM_CYFRAME)

    ; Calculate the window origin and span for full-screen mode.
    mov eax,xBorder
    neg eax
   .new xOrigin:int_t = eax
    mov eax,yBorder
    neg eax
    sub eax,yCaption
   .new yOrigin:int_t = eax
    imul eax,xBorder,2
    add xSpan,eax
    imul eax,yBorder,2
    add eax,yCaption
    add ySpan,eax
    SetWindowPos([rdi].m_hwnd, HWND_TOPMOST, xOrigin, yOrigin, xSpan, ySpan,
        SWP_SHOWWINDOW or SWP_NOZORDER or SWP_NOACTIVATE)
    ret

CApplication::GoFullScreen endp


; Makes the host window resizable and focusable.

CApplication::GoPartialScreen proc uses rdi

    mov rdi,rcx
    mov [rdi].m_isFullScreen,FALSE
    SetWindowLong([rdi].m_hwnd, GWL_EXSTYLE, WS_EX_TOPMOST or WS_EX_LAYERED)
    SetWindowLong([rdi].m_hwnd, GWL_STYLE, WINDOWSTYLES)
    SetWindowPos([rdi].m_hwnd, HWND_TOPMOST, [rdi].m_rect.left, [rdi].m_rect.top,
            [rdi].m_rect.right, [rdi].m_rect.bottom,
            SWP_SHOWWINDOW or SWP_NOZORDER or SWP_NOACTIVATE)
    ret

CApplication::GoPartialScreen endp


; Main Window procedure

WindowProc proc hwnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

    .if ( edx == WM_CREATE )

        SetWindowLongPtr(rcx, GWLP_USERDATA, [r9].CREATESTRUCT.lpCreateParams)
        .return 1
    .endif

    .new Application:ptr CApplication = GetWindowLongPtr(rcx, GWLP_USERDATA)

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

    mov rdi,rcx

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

    .if CreateWindowEx(0, CLASS_NAME, WINDOW_NAME, WINDOWSTYLES,
           CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
           NULL, NULL, [rdi].m_hInstance, rdi) == NULL

        .return E_UNEXPECTED
    .endif
    mov [rdi].m_hwnd,rax
   .return S_OK

CApplication::CreateApplicationWindow endp


; Provides the entry point to the application

CApplication::CApplication proc uses rdi instance:HINSTANCE, vtable:ptr CApplicationVtbl

    mov r9,rcx
    mov rdi,rcx
    xor eax,eaX
    mov ecx,CApplication
    rep stosb
    mov rdi,r9
    mov [rdi].lpVtbl,r8
    mov [rdi].m_hInstance,rdx
    mov [rdi].m_timer,20
    for q,<Run,BeforeEnteringMessageLoop,EnterMessageLoop,AfterLeavingMessageLoop,
        CreateApplicationWindow,ShowApplicationWindow,DestroyApplicationWindow,
        InitObjects,GoFullScreen,GoPartialScreen,OnKeyDown,OnClose,OnDestroy,
        OnPaint,OnSize,OnTimer>
        mov [r8].CApplicationVtbl.q,&CApplication_&q
    endm
    ret

CApplication::CApplication endp

_tWinMain proc hInstance:HINSTANCE, hPrevInstance:HINSTANCE, pszCmdLine:LPTSTR, iCmdShow:int_t

    .new vt:CApplicationVtbl
    .new application:CApplication(hInstance, &vt)
    .return application.Run()

_tWinMain endp

    end _tstart
