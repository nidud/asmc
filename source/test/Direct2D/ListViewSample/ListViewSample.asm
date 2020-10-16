
include ListViewSample.inc

;/******************************************************************
;*                                                                 *
;*  WinMain                                                        *
;*                                                                 *
;*  Application entrypoint                                         *
;*                                                                 *
;******************************************************************/

.code

wWinMain proc hInstance:HINSTANCE, hPrevInstance:HINSTANCE, lpCmdLine:LPWSTR, nCmdShow:SINT

    ;; Ignore the return value because we want to run the program even in the
    ;; unlikely event that HeapSetInformation fails.

    HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0)

    CoInitialize(NULL)
    .if (SUCCEEDED(eax))

       .new app:ptr ListViewApp()

        app.Initialize()
        .if (SUCCEEDED(eax))

            app.RunMessageLoop()
        .endif
        app.Release()

        CoUninitialize()
    .endif

    .return 0

wWinMain endp

;/******************************************************************
;*                                                                 *
;*  ListViewApp::ListViewApp constructor                           *
;*                                                                 *
;*  Initialize member data                                         *
;*                                                                 *
;******************************************************************/

ListViewApp::ListViewApp proc uses rdi

    .return .if !malloc(ListViewApp + ListViewAppVtbl)

    lea rdx,[rax+ListViewApp]
    mov [rax].ListViewApp.lpVtbl,rdx
    lea rdi,[rax+8]
    mov r8,rax
    xor eax,eax
    mov ecx,(ListViewApp - 8) / 8
    rep stosq

    for q,<Release,
           Initialize,
           RunMessageLoop,
           CreateDeviceIndependentResources,
           CreateDeviceResources,
           DiscardDeviceResources,
           OnRender,
           OnResize,
           OnChar,
           OnVScroll,
           OnMouseWheel,
           OnLeftButtonDown,
           CalculateD2DWindowSize,
           LoadDirectory,
           GetAnimatingItemInterpolationFactor,
           GetAnimatingScrollInterpolationFactor,
           GetInterpolatedScrollPosition,
           GetScrolledDIPositionFromPixelPosition>
        lea rax,ListViewApp_&q
        mov [rdx].ListViewAppVtbl.&q,rax
        endm
    mov rax,r8
    ret

ListViewApp::ListViewApp endp


    assume rsi:ptr ListViewApp

;/******************************************************************
;*                                                                 *
;*  ListViewApp::~ListViewApp destructor                           *
;*                                                                 *
;*  Tear down resources                                            *
;*                                                                 *
;******************************************************************/

ListViewApp::Release proc uses rsi

    mov rsi,rcx
    SafeRelease(&[rsi].m_pD2DFactory,     ID2D1Factory)
    SafeRelease(&[rsi].m_pWICFactory,     IWICImagingFactory)
    SafeRelease(&[rsi].m_pDWriteFactory,  IDWriteFactory)
    SafeRelease(&[rsi].m_pRT,             ID2D1HwndRenderTarget)
    SafeRelease(&[rsi].m_pTextFormat,     IDWriteTextFormat)
    SafeRelease(&[rsi].m_pBlackBrush,     ID2D1SolidColorBrush)
    SafeRelease(&[rsi].m_pBindContext,    IBindCtx)
    SafeRelease(&[rsi].m_pBitmapAtlas,    ID2D1Bitmap)
    free(rsi)
    ret

ListViewApp::Release endp


;/******************************************************************
;*                                                                 *
;*  ListViewApp::Initialize                                        *
;*                                                                 *
;*  Create application window and device-independent resources.    *
;*                                                                 *
;******************************************************************/

ListViewApp::Initialize proc uses rsi

    mov rsi,rcx

    .if !this.CreateDeviceIndependentResources()

        ;; Create parent window

        ;;register window class

       .new wcex:WNDCLASSEX

        mov wcex.cbSize,        WNDCLASSEX
        mov wcex.style,         CS_HREDRAW or CS_VREDRAW
        mov wcex.lpfnWndProc,   &ParentWndProc
        mov wcex.cbClsExtra,    0
        mov wcex.cbWndExtra,    sizeof(LONG_PTR)
        mov wcex.hInstance,     HINST_THISCOMPONENT
        mov wcex.hIcon,         NULL
        mov wcex.hIconSm,       NULL
        mov wcex.hbrBackground, NULL
        mov wcex.lpszMenuName,  NULL
        mov wcex.hCursor,       LoadCursor(NULL, IDC_ARROW)
        mov wcex.lpszClassName, &@CStr(L"DemoAppWindow")

        RegisterClassEx(&wcex)

        ;; Create the application window.
        ;;
        ;; Because the CreateWindow function takes its size in pixels, we
        ;; obtain the system DPI and use it to scale the window size.

       .new dpiX:FLOAT
       .new dpiY:FLOAT

        this.m_pD2DFactory.GetDesktopDpi(&dpiX, &dpiY)

        movss       xmm0,dpiX
        mulss       xmm0,512.0
        divss       xmm0,96.0
        movd        eax,xmm0
        xor         eax,-0.0
        movd        xmm0,eax
        shr         eax,31
        cvttss2si   ecx,xmm0
        sub         ecx,eax
        neg         ecx

        movss       xmm0,dpiY
        mulss       xmm0,512.0
        divss       xmm0,96.0
        movd        eax,xmm0
        xor         eax,-0.0
        movd        xmm0,eax
        shr         eax,31
        cvttss2si   edx,xmm0
        sub         edx,eax
        neg         edx

        .if CreateWindowEx(
                0,
                L"DemoAppWindow",
                L"D2D ListView",
                WS_OVERLAPPEDWINDOW or WS_VSCROLL,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                ecx,
                edx,
                NULL,
                NULL,
                HINST_THISCOMPONENT,
                this)

            mov [rsi].m_parentHwnd,rax
            ShowWindow([rsi].m_parentHwnd, SW_SHOWNORMAL)
            UpdateWindow([rsi].m_parentHwnd)
        .endif


        ;; Create child window (for D2D content)

        ;;register window class

       .new wc:WNDCLASSEX

        mov wc.cbSize,        WNDCLASSEX
        mov wc.style,         CS_HREDRAW or CS_VREDRAW
        mov wc.lpfnWndProc,   &ChildWndProc
        mov wc.cbClsExtra,    0
        mov wc.cbWndExtra,    sizeof(LONG_PTR)
        mov wc.hInstance,     HINST_THISCOMPONENT
        mov wc.hIcon,         NULL
        mov wc.hIconSm,       NULL
        mov wc.hbrBackground, NULL
        mov wc.lpszMenuName,  NULL
        mov wc.hCursor,       LoadCursor(NULL, IDC_ARROW)
        mov wc.lpszClassName, &@CStr(L"D2DListViewApp")

        RegisterClassEx(&wc)

       .new d2dWindowSize:D2D1_SIZE_U

        this.CalculateD2DWindowSize(&d2dWindowSize)

        ;;create window

        .if CreateWindowEx(
                0,
                L"D2DListViewApp",
                L"",
                WS_CHILDWINDOW or WS_VISIBLE,
                0,
                0,
                d2dWindowSize.width,
                d2dWindowSize.height,
                [rsi].m_parentHwnd,
                NULL,
                HINST_THISCOMPONENT,
                this
                )

            mov [rsi].m_d2dHwnd,rax
            mov eax,S_OK
        .else
            mov eax,E_FAIL
        .endif
    .endif
    ret

ListViewApp::Initialize endp


;/******************************************************************
;*                                                                 *
;*  ListViewApp::CalculateD2DWindowSize                            *
;*                                                                 *
;*  Determine the size of the D2D child window.                    *
;*                                                                 *
;******************************************************************/

ListViewApp::CalculateD2DWindowSize proc size:ptr D2D1_SIZE_U

    local rc:RECT

    GetClientRect([rcx].ListViewApp.m_parentHwnd, &rc)

    mov rdx,size
    mov [rdx].D2D1_SIZE_U.width,rc.right
    mov [rdx].D2D1_SIZE_U.height,rc.bottom

    .return rdx

ListViewApp::CalculateD2DWindowSize endp


;/******************************************************************
;*                                                                 *
;*  ListViewApp::CreateDeviceIndependentResources                  *
;*                                                                 *
;*  This method is used to create resources which are not bound    *
;*  to any device. Their lifetime effectively extends for the      *
;*  duration of the app. These resources include the D2D,          *
;*  DWrite, and WIC factories; and a DWrite Text Format object     *
;*  (used for identifying particular font characteristics) and     *
;*  a D2D geometry.                                                *
;*                                                                 *
;******************************************************************/

ListViewApp::CreateDeviceIndependentResources proc uses rsi

    msc_fontName equ <L"Calibri">
    msc_fontSize equ 20.0

    local hr:HRESULT

    ;;create D2D factory
    mov hr,D2D1CreateFactory(
        D2D1_FACTORY_TYPE_SINGLE_THREADED,
        &IID_ID2D1Factory,
        NULL,
        &[rsi].m_pD2DFactory
        )
    .if (SUCCEEDED(hr))

        ;;create WIC factory
        mov hr,CoCreateInstance(
            &CLSID_WICImagingFactory,
            NULL,
            CLSCTX_INPROC_SERVER,
            &IID_IWICImagingFactory,
            &[rsi].m_pWICFactory
            )
    .endif
    .if (SUCCEEDED(hr))

        ;;create DWrite factory
        mov hr,DWriteCreateFactory(
            DWRITE_FACTORY_TYPE_SHARED,
            &IID_IDWriteFactory,
            &[rsi].m_pDWriteFactory
            )
    .endif
    .if (SUCCEEDED(hr))

        ;;create DWrite text format object
        mov hr,this.m_pDWriteFactory.CreateTextFormat(
            msc_fontName,
            NULL,
            DWRITE_FONT_WEIGHT_THIN,
            DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL,
            msc_fontSize,
            L"", ;;locale
            &[rsi].m_pTextFormat
            )
    .endif

    .if (SUCCEEDED(hr))

        ;;center the text both horizontally and vertically.
        this.m_pTextFormat.SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING)
        this.m_pTextFormat.SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER)

       .new pEllipsis:ptr IDWriteInlineObject

        mov hr,this.m_pDWriteFactory.CreateEllipsisTrimmingSign([rsi].m_pTextFormat, &pEllipsis)

        .if (SUCCEEDED(hr))

            .data
            sc_trimming DWRITE_TRIMMING {
                DWRITE_TRIMMING_GRANULARITY_CHARACTER,
                0,
                0
                }
            .code

            ;; Set the trimming back on the trimming format object.
            mov hr,this.m_pTextFormat.SetTrimming(&sc_trimming, pEllipsis)

            pEllipsis.Release()
        .endif
    .endif

    .if (SUCCEEDED(hr))

        ;; Set the text format not to allow word wrapping.
        mov hr,this.m_pTextFormat.SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP)
    .endif

    .return hr

ListViewApp::CreateDeviceIndependentResources endp


;/******************************************************************
;*                                                                 *
;*  ListViewApp::CreateDeviceResources                             *
;*                                                                 *
;*  This method creates resources which are bound to a particular  *
;*  D3D device. It's all centralized here, in case the resources   *
;*  need to be recreated in case of D3D device loss (eg. display   *
;*  change, remoting, removal of video card, etc).                 *
;*                                                                 *
;******************************************************************/

ListViewApp::CreateDeviceResources proc uses rsi

  local hr:HRESULT

    mov rsi,rcx
    mov hr,S_OK

    .if [rsi].m_pRT == NULL

       .new rc:RECT

        GetClientRect([rsi].m_d2dHwnd, &rc)

       .new renderTargetProperties:D2D1_RENDER_TARGET_PROPERTIES
        mov renderTargetProperties.type,D2D1_RENDER_TARGET_TYPE_DEFAULT
        mov renderTargetProperties.dpiX,0.0
        mov renderTargetProperties.dpiY,0.0
        mov renderTargetProperties.usage,D2D1_RENDER_TARGET_USAGE_NONE
        mov renderTargetProperties.minLevel,D2D1_FEATURE_LEVEL_DEFAULT
        mov renderTargetProperties.pixelFormat.format,DXGI_FORMAT_UNKNOWN
        mov renderTargetProperties.pixelFormat.alphaMode,D2D1_ALPHA_MODE_UNKNOWN

       .new hwndRenderTargetProperties:D2D1_HWND_RENDER_TARGET_PROPERTIES
        mov hwndRenderTargetProperties.hwnd,[rsi].m_d2dHwnd
        mov eax,rc.bottom
        sub eax,rc.top
        mov hwndRenderTargetProperties.pixelSize.height,eax
        mov eax,rc.right
        sub eax,rc.left
        mov hwndRenderTargetProperties.pixelSize.width,eax
        mov hwndRenderTargetProperties.presentOptions,D2D1_PRESENT_OPTIONS_NONE

        ;;create a D2D render target

        mov hr,this.m_pD2DFactory.CreateHwndRenderTarget(
            &renderTargetProperties,
            &hwndRenderTargetProperties,
            &[rsi].m_pRT
            )

        .if (SUCCEEDED(hr))

            ;;create a black brush

           .new color:D3DCOLORVALUE(Black, 1.0)

            mov hr,this.m_pRT.CreateSolidColorBrush(
                &color,
                NULL,
                &[rsi].m_pBlackBrush
                )
        .endif

        .if (SUCCEEDED(hr))

           .new size:D2D1_SIZE_U
            mov size.width, msc_atlasWidth
            mov size.height,msc_atlasHeight

           .new bitmapProperties:D2D1_BITMAP_PROPERTIES
            mov bitmapProperties.pixelFormat.format,DXGI_FORMAT_B8G8R8A8_UNORM
            mov bitmapProperties.pixelFormat.alphaMode,D2D1_ALPHA_MODE_PREMULTIPLIED
            mov bitmapProperties.dpiX,96.0
            mov bitmapProperties.dpiY,96.0
            mov hr,this.m_pRT.CreateBitmap(
                size,
                NULL,
                0,
                &bitmapProperties,
                &[rsi].m_pBitmapAtlas
                )
        .endif
        .if (SUCCEEDED(hr))

            mov hr,CreateBindCtx(0, &[rsi].m_pBindContext)
        .endif
        .if (SUCCEEDED(hr))

            mov hr,this.LoadDirectory()
        .endif
    .endif

    .return hr

ListViewApp::CreateDeviceResources endp


;/******************************************************************
;*                                                                 *
;*  ListViewApp::DiscardDeviceResources                            *
;*                                                                 *
;*  Discard device-specific resources which need to be recreated   *
;*  when a D3D device is lost                                      *
;*                                                                 *
;******************************************************************/

ListViewApp::DiscardDeviceResources proc uses rsi

    mov rsi,rcx
    SafeRelease(&[rsi].m_pRT,           ID2D1HwndRenderTarget)
    SafeRelease(&[rsi].m_pBitmapAtlas,  ID2D1Bitmap)
    SafeRelease(&[rsi].m_pBlackBrush,   ID2D1SolidColorBrush)
    ret

ListViewApp::DiscardDeviceResources endp


;/******************************************************************
;*                                                                 *
;*  ListViewApp::RunMessageLoop                                    *
;*                                                                 *
;*  Main window message loop                                       *
;*                                                                 *
;******************************************************************/

ListViewApp::RunMessageLoop proc

  local msg:MSG

    .while (GetMessage(&msg, NULL, 0, 0))

        TranslateMessage(&msg)
        DispatchMessage(&msg)
    .endw
    ret

ListViewApp::RunMessageLoop endp


;/******************************************************************
;*                                                                 *
;*  ListViewApp::LoadDirectory                                     *
;*                                                                 *
;*  Load item info from files in the current directory.            *
;*  Thumbnails/Icons are also loaded into the atlas and their      *
;*  location is stored within each ItemInfo object.                *
;*                                                                 *
;******************************************************************/

ListViewApp::LoadDirectory proc uses rsi rdi rbx

    local hr:HRESULT

    ;; Locals that need to be cleaned up before we exit

    local memoryDC:HDC
    local iconImage:HBITMAP
    local wszAbsolutePath:ptr WCHAR
    local pBits:ptr BYTE
    local directoryTraversalHandle:HANDLE
    local pShellItemImageFactory:ptr IShellItemImageFactory

    ;; Other locals
    local absolutePathArraySize:UINT
    local currentX:UINT
    local currentY:UINT
    local i:UINT

    ;; 4 bytes per pixel in BGRA format.
    sc_bitsArraySize equ msc_iconSize * msc_iconSize * 4

    mov rsi,rcx
    xor ebx,ebx
    mov hr,ebx
    mov memoryDC,CreateCompatibleDC(NULL)
    mov iconImage,rbx
    mov wszAbsolutePath,rbx
    mov pBits,rbx
    mov directoryTraversalHandle,INVALID_HANDLE_VALUE
    mov pShellItemImageFactory,rbx
    mov absolutePathArraySize,ebx
    mov currentX,ebx
    mov currentY,ebx
    mov i,ebx

    .if (SUCCEEDED(hr))

        mov pBits,malloc(sc_bitsArraySize)
        mov hr,S_OK
        .if rax == NULL
            mov hr,E_OUTOFMEMORY
        .endif
    .endif

    .if (SUCCEEDED(hr))

        ;; We have a static array of ItemInfo objects, so we can only load
        ;; msc_maxItemInfos ItemInfos.

        .while (i < msc_maxItemInfos)


            ;; We always load files from the current directory. We do navigation
            ;; by changing the current directory. The first time through the
            ;; while loop directoryTraversalHandle will be equal to
            ;; INVALID_HANDLE_VALUE and so we'll call FindFirstFile. On
            ;; subsequent interations we'll call FindNextFile to find other
            ;; items in the current directory.

            .new findFileData:WIN32_FIND_DATA
            .if (directoryTraversalHandle == INVALID_HANDLE_VALUE)

                mov directoryTraversalHandle,FindFirstFile(L".\\*", &findFileData)

                .if (directoryTraversalHandle == INVALID_HANDLE_VALUE)

                    .if (GetLastError() != ERROR_FILE_NOT_FOUND)

                        mov hr,E_FAIL
                    .endif

                    .break
                .endif

            .else

                .if (!FindNextFile(directoryTraversalHandle, &findFileData))

                    .if (GetLastError() != ERROR_NO_MORE_FILES)

                        mov hr,E_FAIL
                    .endif

                    .break
                .endif
            .endif

            mov [rsi].m_pFiles[rbx].placement.left,currentX
            mov [rsi].m_pFiles[rbx].placement.top,currentY

            ;;
            ;; Increment bitmap atlas position here so that we notice if we
            ;; don't have enough room for any more icons.
            ;;
            add currentX,msc_iconSize
            mov eax,currentX
            add eax,msc_iconSize

            .if (eax > msc_atlasWidth)

                mov currentX,0
                add currentY,msc_iconSize
            .endif

            mov eax,currentY
            add eax,msc_iconSize
            .if (eax > msc_atlasHeight)

                ;; Exceeded atlas size
                ;; We break without any error so that the contents up until this
                ;; point will be shown.
                .break
            .endif

            ;;
            ;; Determine the size of array needed to store the full path name.
            ;; We need the full path name to call SHCreateItemFromParsingName.
            ;;
           .new requiredLength:UINT

            mov requiredLength,GetFullPathName(&findFileData.cFileName, 0, NULL, NULL)
            .if (requiredLength == 0)

                mov hr,E_FAIL
                .break
            .endif

            ;;
            ;; Allocate a bigger buffer if necessary.
            ;;
            .if (requiredLength > absolutePathArraySize)

                free(wszAbsolutePath)
                mov ecx,requiredLength
                shl ecx,1
                mov wszAbsolutePath,malloc(rcx)
                .if rax == NULL

                    mov hr,E_FAIL
                    .break
                .endif
                mov absolutePathArraySize,requiredLength
            .endif

            .if (!GetFullPathName(&findFileData.cFileName, requiredLength, wszAbsolutePath, NULL))

                mov hr,E_FAIL
                .break
            .endif

            ;; Create an IShellItemImageFactory for the current directory item
            ;; so that we can get a icon/thumbnail for it.
            SafeRelease(&pShellItemImageFactory, IShellItemImageFactory)

            mov hr,SHCreateItemFromParsingName(
                    wszAbsolutePath,
                    [rsi].m_pBindContext,
                    &IID_IShellItemImageFactory,
                    &pShellItemImageFactory
                    )

            .break .if (FAILED(hr))

           .new iconSize:POINT
            mov iconSize.x,msc_iconSize
            mov iconSize.y,msc_iconSize

            ;; If iconImage isn't NULL that means we're looping around. We call
            ;; DeleteObject to avoid leaking the HBITMAP.
            .if (iconImage != NULL)

                DeleteObject(iconImage)
                mov iconImage,NULL
            .endif

            ;; Get the icon/thumbnail for the current directory item in HBITMAP
            ;; form.
            ;; In the interests of brevity, this sample calls GetImage from the
            ;; UI thread. However this function can be time consuming, so a real
            ;; application should call GetImage from a separate thread, showing
            ;; a placeholder icon until the icon has been loaded.

            mov hr,pShellItemImageFactory.GetImage(iconSize, 0x0, &iconImage)
            .break .if (FAILED(hr))

           .new bi:BITMAPINFO
            lea rdi,bi
            xor eax,eax
            mov ecx,BITMAPINFO
            rep stosb
            mov bi.bmiHeader.biSize,BITMAPINFOHEADER

            ;; Get the bitmap info header.
            .if !GetDIBits(
                    memoryDC,   ;; hdc
                    iconImage,  ;; hbmp
                    0,          ;; uStartScan
                    0,          ;; cScanLines
                    NULL,       ;; lpvBits
                    &bi,
                    DIB_RGB_COLORS
                    )
                mov hr,E_FAIL
                .break
            .endif

            ;; Positive bitmap info header height means bottom-up bitmaps. We
            ;; always use top-down bitmaps, so we set the height negative.

            .if (bi.bmiHeader.biHeight > 0)

                neg bi.bmiHeader.biHeight
            .endif

            mov eax,bi.bmiHeader.biHeight
            neg eax

            ;; If we happen to find an icon that's too big, skip over this item.

            .ifs ((eax > msc_iconSize) \
                || (bi.bmiHeader.biWidth > msc_iconSize) \
                || (bi.bmiHeader.biSizeImage > sc_bitsArraySize))

                .continue
            .endif

            xor eax,eax
            test findFileData.dwFileAttributes,FILE_ATTRIBUTE_DIRECTORY
            setnz al
            mov [rsi].m_pFiles[rbx].isDirectory,eax

            ;; Now that we know the size of the icon/thumbnail we can initialize
            ;; the rest of placement rectangle. We avoid using currentX/currentY
            ;; since we've already incremented those values in anticipation of
            ;; the next iteration of the loop.

            mov eax,[rsi].m_pFiles[rbx].placement.left
            add eax,bi.bmiHeader.biWidth
            mov [rsi].m_pFiles[rbx].placement.right,eax
            mov eax,[rsi].m_pFiles[rbx].placement.top
            mov ecx,bi.bmiHeader.biHeight
            neg ecx
            add eax,ecx
            mov [rsi].m_pFiles[rbx].placement.bottom,eax

            ;; Now we copy the bitmap bits into a buffer.
            .if !GetDIBits(
                    memoryDC,
                    iconImage,
                    0,
                    ecx,
                    pBits,
                    &bi,
                    DIB_RGB_COLORS)
                mov hr,E_FAIL
                .break
            .endif

            ;; Now we copy the buffer into video memory.

            mov  eax,bi.bmiHeader.biSizeImage
            mov  ecx,bi.bmiHeader.biHeight
            neg  ecx
            xor  edx,edx
            idiv ecx

            mov hr,this.m_pBitmapAtlas.CopyFromMemory(
                    &[rsi].m_pFiles[rbx].placement,
                    pBits,
                    eax
                    )

            .break .if (FAILED(hr))

ifdef _MSVCRT
            wcsncpy(&[rsi].m_pFiles[rbx].szFilename, &findFileData.cFileName, MAX_PATH)
else
            StringCchCopy(&[rsi].m_pFiles[rbx].szFilename, MAX_PATH, &findFileData.cFileName)
endif

            ;; Set the previous position to 0 so that the items animate
            ;; downwards when they are first shown.

            mov [rsi].m_pFiles[rbx].previousPosition,0.0
            imul eax,i,msc_iconSize + msc_lineSpacing
            cvtsi2ss xmm0,eax
            movss [rsi].m_pFiles[rbx].currentPosition,xmm0

            inc i
            add ebx,ItemInfo
        .endw
    .endif

    .if (SUCCEEDED(hr))

        mov [rsi].m_numItemInfos,i

        ;;
        ;; The total size of our document.
        ;;
        lea rdx,[rax-1]
        imul eax,eax,msc_iconSize
        imul ecx,edx,msc_lineSpacing
        add eax,ecx
        mov [rsi].m_scrollRange,eax

       .new size:D2D1_SIZE_F
       .new s:SCROLLINFO
        mov s.cbSize,SCROLLINFO
        mov s.fMask,SIF_DISABLENOSCROLL or SIF_PAGE or SIF_POS or SIF_RANGE
        mov s.nMin,0
        mov s.nMax,[rsi].m_scrollRange

        this.m_pRT.GetSize(&size)
        cvtss2si eax,size.height
        mov s.nPage,eax
        mov s.nPos,0

        SetScrollInfo([rsi].m_parentHwnd, SB_VERT, &s, TRUE)

        ;;
        ;; Animate the item positions into place.
        ;;
        mov [rsi].m_animatingItems,msc_totalAnimatingItemFrames

        ;;
        ;; Set the scroll to zero, don't animate.
        ;;
        mov [rsi].m_animatingScroll,0
        mov [rsi].m_currentScrollPos,0
        mov [rsi].m_previousScrollPos,0
    .endif


    ;;
    ;; Clean up locals.
    ;;

    SafeRelease(&pShellItemImageFactory, IShellItemImageFactory)

    free(pBits)
    free(wszAbsolutePath)

    .if (directoryTraversalHandle != INVALID_HANDLE_VALUE)

        FindClose(directoryTraversalHandle)
    .endif

    .if (memoryDC != NULL)

        DeleteDC(memoryDC)
    .endif

    .if (iconImage != NULL)

        DeleteObject(iconImage)
    .endif

    .return hr

ListViewApp::LoadDirectory endp

;/******************************************************************
;*                                                                 *
;*  ListViewApp::OnRender                                          *
;*                                                                 *
;*  Called whenever the application needs to display the client    *
;*  window.                                                        *
;*                                                                 *
;*  Note that this function will not render anything if the window *
;*  is occluded (e.g. when the screen is locked).                  *
;*  Also, this function will automatically discard device-specific *
;*  resources if the D3D device disappears during function         *
;*  invocation, and will recreate the resources the next time it's *
;*  invoked.                                                       *
;*                                                                 *
;******************************************************************/

ListViewApp::OnRender proc uses rsi rdi rbx

    local hr:HRESULT
    local pRT:ptr ID2D1HwndRenderTarget

    mov rsi,rcx
    mov hr,this.CreateDeviceResources()
    mov pRT,[rsi].m_pRT

    .if SUCCEEDED(hr)
    .if !pRT.CheckWindowState() & D2D1_WINDOW_STATE_OCCLUDED

        ;; We animate scrolling to achieve a smooth scrolling effect.
        ;; GetInterpolatedScrollPosition() returns the scroll position
        ;; for the current frame.

       .new interpolatedScroll:FLOAT
        movss interpolatedScroll,this.GetInterpolatedScrollPosition()

        pRT.BeginDraw()

        ;; Displaying the correctly scrolled view is as simple as setting the
        ;; transform to translate by the current scroll amount.

       .new matrix:Matrix3x2F

        movss xmm1,-0.0
        movss xmm2,interpolatedScroll
        xorps xmm2,xmm1

        matrix.Translation(0.0, xmm2)
        pRT.SetTransform(&matrix)
        pRT.Clear(D3DCOLORVALUE(White, 1.0))

       .new rtSize:D2D1_SIZE_F
        pRT.GetSize(&rtSize)

       .new interpolationFactor:FLOAT
        movss interpolationFactor,this.GetAnimatingItemInterpolationFactor()

       .new i:UINT

        .for (ebx = 0, i = 0: i < [rsi].m_numItemInfos: i++, ebx += ItemInfo)

            .Assert(m_pFiles[i].szFilename[0] != L'\0');

            ;; We animate item position changes. The interpolation factor is the
            ;; a ratio between 0 and 1 used to interpolate between the previous
            ;; position and the current position. The position that we draw for
            ;; this frame is somewhere between the two.
           .new interpolatedPosition:FLOAT

            movss interpolatedPosition,GetFancyAccelerationInterpolatedValue(
                interpolationFactor,
                [rsi].m_pFiles[rbx].previousPosition,
                [rsi].m_pFiles[rbx].currentPosition
                )


            ;; We do a quick check to see if the items we are drawing will be in
            ;; the visible region. If they are not, we don't bother issues the
            ;; draw commands. This is a substantial perf win.
           .new topOfIcon:FLOAT
           .new bottomOfIcon:FLOAT
           .new size:D2D1_SIZE_F

            movss xmm0,interpolatedPosition
            movss topOfIcon,xmm0
            addss xmm0,@CatStr(%msc_iconSize, <.0>)
            movss bottomOfIcon,xmm0

            ;; Some further items could be in the visible region. Continue
            ;; the loop so that they will be drawn.

            comiss xmm0,interpolatedScroll
            .continue .ifb

            pRT.GetSize(&size)

            movss xmm0,interpolatedScroll
            addss xmm0,size.height
            movss xmm1,topOfIcon
            comiss xmm1,xmm0
            .continue .ifa

            ;; When the items change position we draw them mostly transparent
            ;; and then gradually make them more opaque as they get closer to
            ;; their final positions. This function was chosen after a bit of
            ;; experimentation and I thought it looked nice.

           .new opacity:FLOAT
            movss xmm0,interpolationFactor
            mulss xmm0,xmm0
            movss xmm1,0.2
            maxss xmm0,xmm1
            movss opacity,xmm0

           .new r1:D2D_RECT_F
           .new r2:D2D_RECT_F

            mov      r1.left,0.0
            mov      r1.top,interpolatedPosition
            mov      r1.right,@CatStr(%msc_iconSize, <.0>)
            movss    xmm0,interpolatedPosition
            addss    xmm0,r1.right
            movss    r1.bottom,xmm0
            cvtsi2ss xmm0,[rsi].m_pFiles[rbx].placement.left
            cvtsi2ss xmm1,[rsi].m_pFiles[rbx].placement.top
            cvtsi2ss xmm2,[rsi].m_pFiles[rbx].placement.right
            cvtsi2ss xmm3,[rsi].m_pFiles[rbx].placement.bottom
            movss    r2.left,  xmm0
            movss    r2.top,   xmm1
            movss    r2.right, xmm2
            movss    r2.bottom,xmm3

            ;; The icon is stored in the image atlas. We reference it's position
            ;; in the atlas and it's destination on the screen.

            pRT.DrawBitmap(
                [rsi].m_pBitmapAtlas,
                &r1,
                opacity,
                D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
                &r2
                )

            ;; Draw the filename. For brevity we just use DrawText. A real
            ;; application should consider caching the TextLayout object during
            ;; animations to reduce CPU cost.

            this.m_pBlackBrush.SetOpacity(opacity)

            mov r8,wcsnlen(&[rsi].m_pFiles[rbx].szFilename, ARRAYSIZE(ItemInfo.szFilename))
            mov r1.left,@CatStr(%msc_iconSize + msc_lineSpacing, <.0>)
            mov r1.top,interpolatedPosition
            mov r1.right,rtSize.width
            movss xmm0,interpolatedPosition
            addss xmm0,@CatStr(%msc_iconSize, <.0>)
            movss r1.bottom,xmm0
            pRT.DrawText(
                &[rsi].m_pFiles[rbx].szFilename,
                r8d,
                [rsi].m_pTextFormat,
                &r1,
                [rsi].m_pBlackBrush,
                D2D1_DRAW_TEXT_OPTIONS_NONE,
                DWRITE_MEASURING_MODE_NATURAL
                )
        .endf

        mov hr,pRT.EndDraw(NULL, NULL)
        .if (hr == D2DERR_RECREATE_TARGET)

            this.DiscardDeviceResources()
            mov hr,S_OK
        .endif
    .endif
    .endif

    ;; Advance the position of the current item animation.

    .if ([rsi].m_animatingItems > 0)

        dec [rsi].m_animatingItems
        .ifz ;[rsi].m_animatingItems == 0

            .for (ecx = 0: ecx < [rsi].m_numItemInfos: ecx++)

                imul edx,ecx,ItemInfo
                mov [rsi].m_pFiles[rdx].previousPosition,[rsi].m_pFiles[rdx].currentPosition
            .endf
        .endif

        InvalidateRect([rsi].m_d2dHwnd, NULL, FALSE)
    .endif

    ;; Advance the position of the current scroll animation

    .if ([rsi].m_animatingScroll > 0)

        dec [rsi].m_animatingScroll
        .ifz ;([rsi].m_animatingScroll == 0)

            mov [rsi].m_previousScrollPos,[rsi].m_currentScrollPos
        .endif

        InvalidateRect([rsi].m_d2dHwnd, NULL, FALSE)
    .endif

    .return hr

ListViewApp::OnRender endp


;/******************************************************************
;*                                                                 *
;*  ListViewApp::GetFancyAccelerationInterpolatedValue             *
;*                                                                 *
;*  Do a fancy interpolation between two points.                   *
;*                                                                 *
;******************************************************************/

GetFancyAccelerationInterpolatedValue proc linearFactor:FLOAT, p1:FLOAT, p2:FLOAT

  local apex:FLOAT

    .Assert(linearFactor >= 0.0 && linearFactor <= 1.0)

    ;; Don't overshoot by more than the icon size.

    mov     apex,0.0
    movss   xmm0,xmm2
    subss   xmm0,xmm3
    pcmpeqw xmm1,xmm1
    psrld   xmm1,1
    andps   xmm0,xmm1
    comiss  xmm0,0.01
    .ifa
        movss xmm1,xmm0
        mulss xmm1,0.10
        movss xmm2,@CatStr(%msc_iconSize, <.0>)
        minss xmm1,xmm2
        divss xmm1,xmm0
        movss apex,xmm1
    .endif

    ;; Stretch so that the initial overshoot (occurring 33% of the way along) is
    ;; 70% of the animation.

   .new rearrangedDomain:FLOAT
    mov rearrangedDomain,0.0

    movss xmm0,linearFactor
    comiss xmm0,0.7
    .ifb
        divss xmm0,0.7
        divss xmm0,3.0
        movss rearrangedDomain,xmm0
    .else
        subss xmm0,0.7
        divss xmm0,0.3
        mulss xmm0,2.0 / 3.0
        addss xmm0,1.0 / 3.0
        movss rearrangedDomain,xmm0
    .endif

    ;;
    ;; We will use sin to approximate the curve. Since we want to start at a
    ;; minimum value, we start at -PI/2. Since we want to finish at the second
    ;; max. We stretch the interval [0..1] to [-PI/2 .. 5PI/2].
    ;;

   .new stretchedDomain:FLOAT

    mulss xmm0,3.0 * M_PI
    movss stretchedDomain,xmm0

   .new translatedDomain:FLOAT

    subss xmm0,M_PI_2
    movss translatedDomain,xmm0

   .new fancyFactor:FLOAT

    cvtss2sd xmm0,xmm0
    sin(xmm0)
    cvtsd2ss xmm0,xmm0

    addss xmm0,1.0 ;; Now between 0 and 2
    movss fancyFactor,xmm0

    ;;
    ;; Before the first max, we want the bounds to go from 0 to 1+apex
    ;;
    movss xmm1,translatedDomain
    comiss xmm1,M_PI_2
    .ifb

        movss xmm1,1.0
        addss xmm1,apex
        mulss xmm0,xmm1
        divss xmm0,2.0 ;; Now between 0 and 1+apex
        movss fancyFactor,xmm0

    ;;
    ;; After the first max, we want to ease the bounds down so that when
    ;; translatedDomain is 5PI/2, fancyFactor is 1.0f. We also want the bounce
    ;; to be small, so we reduce the magnitude of the oscillation.
    ;;

    .else

        ;;
        ;; When we want the bounce (the undershoot after reaching the apex), to
        ;; be reach 1.0f - apex / 2.0f at a minimum.
        ;;

       .new oscillationMin:FLOAT
        movss xmm0,1.0
        movss xmm1,apex
        divss xmm1,2.0
        subss xmm0,xmm1
        movss oscillationMin,xmm0

        ;;
        ;; We want the max to start out at 1.0f + apex (so that we are
        ;; continuous) and finish at 1.0f (the final position). We square our
        ;; interpolation factor to stretch the bounce and compress the
        ;; correction. Since the correction is a smaller distance, this looks
        ;; better. Another benefit is that it prevents us from overshooting 1.0f
        ;; during the correction phase.
        ;;

       .new interpolationFactor:FLOAT
        movss xmm0,translatedDomain
        subss xmm0,M_PI_2
        divss xmm0,2.0 * M_PI
        mulss xmm0,xmm0
        movss interpolationFactor,xmm0

       .new oscillationMax:FLOAT
        movss xmm1,1.0
        movss xmm2,xmm1
        subss xmm1,xmm0
        addss xmm2,apex
        mulss xmm1,xmm2
        mulss xmm0,1.0
        addss xmm0,xmm1
        movss oscillationMax,xmm0

       .Assert(oscillationMax >= oscillationMin)

       .new oscillationMidPoint:FLOAT
        addss xmm0,oscillationMin
        divss xmm0,2.0
        movss oscillationMidPoint,xmm0

       .new oscillationMagnitude:FLOAT
        movss xmm0,oscillationMax
        subss xmm0,oscillationMin
        movss oscillationMagnitude,xmm0

        ;; Oscillate around the midpoint

        movss xmm1,fancyFactor
        divss xmm1,2.0
        subss xmm1,0.5
        mulss xmm0,xmm1
        addss xmm0,oscillationMidPoint
        movss fancyFactor,xmm0
    .endif

    movss xmm0,p2
    mulss xmm0,fancyFactor
    movss xmm1,1.0
    subss xmm1,fancyFactor
    mulss xmm1,p1
    addss xmm0,xmm1
    ret

GetFancyAccelerationInterpolatedValue endp


;/******************************************************************
;*                                                                 *
;*  ListViewApp::GetAnimatingItemInterpolationFactor               *
;*                                                                 *
;*  Return the interpolation factor for a linear interpolation     *
;*  for the current item animation for the the current frame       *
;*                                                                 *
;******************************************************************/

ListViewApp::GetAnimatingItemInterpolationFactor proc

    cvtsi2ss xmm1,[rcx].ListViewApp.m_animatingItems
    movss xmm0,@CatStr(%msc_totalAnimatingItemFrames, <.0>)
    subss xmm0,xmm1
    divss xmm0,@CatStr(%msc_totalAnimatingItemFrames, <.0>)
    ret

ListViewApp::GetAnimatingItemInterpolationFactor endp


;/******************************************************************
;*                                                                 *
;*  ListViewApp::GetAnimatingScrollInterpolationFactor             *
;*                                                                 *
;*  Return the interpolation factor for a linear interpolation     *
;*  for the current scroll animation for the the current frame     *
;*                                                                 *
;******************************************************************/

ListViewApp::GetAnimatingScrollInterpolationFactor proc

    cvtsi2ss xmm1,[rcx].ListViewApp.m_animatingScroll
    movss xmm0,@CatStr(%msc_totalAnimatingScrollFrames, <.0>)
    subss xmm0,xmm1
    divss xmm0,@CatStr(%msc_totalAnimatingScrollFrames, <.0>)
    ret

ListViewApp::GetAnimatingScrollInterpolationFactor endp

;/******************************************************************
;*                                                                 *
;*  ListViewApp::GetInterpolatedScrollPosition                     *
;*                                                                 *
;*  Return the scroll position for the current frame               *
;*                                                                 *
;******************************************************************/

ListViewApp::GetInterpolatedScrollPosition proc

    this.GetAnimatingScrollInterpolationFactor()

    movss xmm2,1.0
    subss xmm2,xmm0
    cvtsi2ss xmm1,[rcx].ListViewApp.m_currentScrollPos
    mulss xmm0,xmm1
    cvtsi2ss xmm1,[rcx].ListViewApp.m_previousScrollPos
    mulss xmm1,xmm2
    addss xmm0,xmm1
    ret

ListViewApp::GetInterpolatedScrollPosition endp


;/******************************************************************
;*                                                                 *
;*  ListViewApp::OnResize                                          *
;*                                                                 *
;*  If the application receives a WM_SIZE message, this method     *
;*  resizes the render target appropriately.                       *
;*                                                                 *
;******************************************************************/

ListViewApp::OnResize proc uses rsi

    mov rsi,rcx
    .if [rsi].m_pRT

       .new size:D2D1_SIZE_U

        this.CalculateD2DWindowSize(&size)
        MoveWindow([rsi].m_d2dHwnd, 0, 0, size.width, size.height, FALSE)

        ;; Note: This method can fail, but it's okay to ignore the
        ;; error here -- it will be repeated on the next call to
        ;; EndDraw.

        this.m_pRT.Resize(&size)

        imul eax,[rsi].m_numItemInfos,msc_lineSpacing + msc_iconSize
        sub  eax,msc_lineSpacing
        mov  [rsi].m_scrollRange,eax

       .new s:SCROLLINFO
        mov s.cbSize,SCROLLINFO
        mov s.fMask,SIF_DISABLENOSCROLL or SIF_PAGE or SIF_RANGE
        mov s.nMin,0
        mov s.nMax,[rsi].m_scrollRange
        mov s.nPage,size.height

        SetScrollInfo([rsi].m_parentHwnd, SB_VERT, &s, TRUE)
        InvalidateRect([rsi].m_d2dHwnd, NULL, FALSE)
    .endif
    ret

ListViewApp::OnResize endp


;/******************************************************************
;*                                                                 *
;*  ListViewApp::CompareAToZ (static)                              *
;*                                                                 *
;*  A comparator function for sorting ItemInfos alphabetically     *
;*                                                                 *
;******************************************************************/

CompareAToZ proc a:ptr, b:ptr

    wcscmp(&[rcx].ItemInfo.szFilename, &[rdx].ItemInfo.szFilename)
    ret

CompareAToZ endp


;/******************************************************************
;*                                                                 *
;*  ListViewApp::CompareZToA (static)                              *
;*                                                                 *
;*  A comparator function for sorting ItemInfos in reverse         *
;*  alphabetical order.                                            *
;*                                                                 *
;******************************************************************/

CompareZToA proc a:ptr, b:ptr

    mov r8,rdx
    wcscmp(&[r8].ItemInfo.szFilename, &[rcx].ItemInfo.szFilename)
    ret

CompareZToA endp


;/******************************************************************
;*                                                                 *
;*  ListViewApp::CompareDirFirstAToZ (static)                      *
;*                                                                 *
;*  A comparator function for sorting ItemInfos in alphabetical    *
;*  order, with all directories before all other files.            *
;*                                                                 *
;******************************************************************/

CompareDirFirstAToZ proc a:ptr, b:ptr

    .if ([rcx].ItemInfo.isDirectory && ![rdx].ItemInfo.isDirectory)
        mov eax,-1
    .elseif (![rcx].ItemInfo.isDirectory && [rdx].ItemInfo.isDirectory)
        mov eax,1
    .else
        wcscmp(&[rcx].ItemInfo.szFilename, &[rdx].ItemInfo.szFilename)
    .endif
    ret

CompareDirFirstAToZ endp


;/******************************************************************
;*                                                                 *
;*  ListViewApp::OnChar                                            *
;*                                                                 *
;*  Called when the app receives a WM_CHAR message (which happens  *
;*  when a key is pressed).                                        *
;*                                                                 *
;******************************************************************/

ListViewApp::OnChar proc uses rsi rdi rbx aChar:SWORD

    ;; We only do stuff for 'a', 'z', or 'd'

    .if (dl == 'a' || dl == 'z' || dl == 'd')

        Comparator typedef proto :ptr, :ptr
       .new comparator:ptr Comparator

        ;; 'a' means alphabetical sort
        .if (dl == 'a')

            mov comparator,&CompareAToZ

        ;; 'z' means reverse alphabetical sort
        .elseif (dl == 'z')

            mov comparator,&CompareZToA

        ;; 'd' means alphabetical sort, directories first
        .else

            mov comparator,&CompareDirFirstAToZ
        .endif

        ;; Freeze file position to the current interpolated position so that
        ;; when we animate to the new positions, the items don't jump back to
        ;; their previous position momentarily.

        mov rsi,rcx

        .for (edi = 0, ebx = 0: edi < [rsi].m_numItemInfos: edi++, ebx += ItemInfo)

           .new interpolationFactor:FLOAT
            movss interpolationFactor,this.GetAnimatingItemInterpolationFactor()
            GetFancyAccelerationInterpolatedValue(
                interpolationFactor,
                [rsi].m_pFiles[rbx].previousPosition,
                [rsi].m_pFiles[rbx].currentPosition
                )
            movss [rsi].m_pFiles[rbx].previousPosition,xmm0
        .endf

        ;; Apply the new sort.
        qsort(&[rsi].m_pFiles, [rsi].m_numItemInfos, sizeof(ItemInfo), comparator)

        ;; Set the new positions based up on the position of each item within
        ;; the sorted array.

        .for (edi = 0, ebx = 0: edi < [rsi].m_numItemInfos: edi++, ebx += ItemInfo)

            imul eax,edi,msc_iconSize + msc_lineSpacing
            cvtsi2ss xmm0,eax
            movss [rsi].m_pFiles[rbx].currentPosition,xmm0
        .endf

        ;; Animate the items to their new positions.

        mov [rsi].m_animatingItems,msc_totalAnimatingItemFrames
        InvalidateRect([rsi].m_d2dHwnd, NULL, FALSE)

    .endif
    ret

ListViewApp::OnChar endp


;/******************************************************************
;*                                                                 *
;*  ListViewApp::GetScrolledDIPositionFromPixelPosition            *
;*                                                                 *
;*  Translate a pixel position to a position within our document,  *
;*  taking scrolling into account.                                 *
;*                                                                 *
;******************************************************************/

ListViewApp::GetScrolledDIPositionFromPixelPosition proc pixelPosition:D2D1_POINT_2U

  local dpi:D2D1_POINT_2F

    this.m_pRT.GetDpi(&dpi.x, &dpi.y)
    this.GetInterpolatedScrollPosition()

    cvtsi2ss xmm1,pixelPosition.x
    mulss xmm1,96.0
    divss xmm1,dpi.x
    movss dpi.x,xmm1
    cvtsi2ss xmm1,pixelPosition.y
    mulss xmm1,96.0
    divss xmm1,dpi.y
    addss xmm0,xmm1
    movss dpi.y,xmm0
    mov rax,dpi
    ret

ListViewApp::GetScrolledDIPositionFromPixelPosition endp


;/******************************************************************
;*                                                                 *
;*  ListViewApp::ParentWndProc                                     *
;*                                                                 *
;*  Window message handler                                         *
;*                                                                 *
;******************************************************************/

ParentWndProc proc hwnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

  local result:LRESULT
  local wasHandled:BOOL
  local pListViewApp:ptr ListViewApp

    mov result,0

    .if edx == WM_CREATE

        SetWindowLongPtrW(rcx, GWLP_USERDATA, [r9].CREATESTRUCT.lpCreateParams)
        mov result,1

    .else

        mov pListViewApp,GetWindowLongPtrW(rcx, GWLP_USERDATA)
        mov wasHandled,FALSE

        .if rax

            .switch(message)

            .case WM_SIZE

                pListViewApp.OnResize()

                mov result,0
                mov wasHandled,TRUE
                .endc

            .case WM_VSCROLL

                pListViewApp.OnVScroll(wParam, lParam)

                mov result,0
                mov wasHandled,TRUE
                .endc

            .case WM_MOUSEWHEEL

                pListViewApp.OnMouseWheel(wParam, lParam)

                mov result,0
                mov wasHandled,TRUE
                .endc

            .case WM_CHAR

                mov rdx,wParam
                .if edx != VK_ESCAPE

                    pListViewApp.OnChar(dx)

                    mov result,0
                    mov wasHandled,TRUE
                    .endc
                .endif

            .case WM_DESTROY

                PostQuitMessage(0)
                mov result,1
                mov wasHandled,TRUE
                .endc
            .endsw
        .endif

        .if (!wasHandled)

            mov result,DefWindowProc(hwnd, message, wParam, lParam)
        .endif
    .endif

    .return result

ParentWndProc endp


;/******************************************************************
;*                                                                 *
;*  ListViewApp::ChildWndProc                                      *
;*                                                                 *
;*  Window message handler for the Child D2D window                *
;*                                                                 *
;******************************************************************/

ChildWndProc proc hwnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

  local pListViewApp:ptr ListViewApp

    .if edx == WM_CREATE

        SetWindowLongPtrW(rcx, GWLP_USERDATA, [r9].CREATESTRUCT.lpCreateParams)
        .return 1
    .endif

    mov pListViewApp,GetWindowLongPtrW(rcx, GWLP_USERDATA)

    .if rax

        .switch (message)

        .case WM_PAINT
        .case WM_DISPLAYCHANGE

           .new ps:PAINTSTRUCT
            BeginPaint(hwnd, &ps)
            pListViewApp.OnRender()
            EndPaint(hwnd, &ps)

            .return 0

        .case WM_LBUTTONDOWN

           .new diPosition:D2D1_POINT_2U

            movzx eax,word ptr lParam
            movzx edx,word ptr lParam[2]
            mov diPosition.x,eax
            mov diPosition.y,edx

            pListViewApp.GetScrolledDIPositionFromPixelPosition(diPosition)
            pListViewApp.OnLeftButtonDown(rax)

            .return 0

        .case WM_DESTROY

            PostQuitMessage(0)

            .return 1
        .endsw
    .endif
    .return DefWindowProc(hwnd, message, wParam, lParam)

ChildWndProc endp


;/******************************************************************
;*                                                                 *
;*  ListViewApp::OnLeftButtonDown                                  *
;*                                                                 *
;*  Called when the left mouse button is pressed inside the child  *
;*  D2D window                                                     *
;*                                                                 *
;******************************************************************/

ListViewApp::OnLeftButtonDown proc uses rsi diPosition:D2D1_POINT_2F

    mov rsi,rcx
    cvtss2si eax,diPosition.y
    mov ecx,(msc_iconSize + msc_lineSpacing)
    xor edx,edx
    div ecx

    .ifs eax >= 0 && eax < [rsi].m_numItemInfos

        ;; Only process the click if the item isn't animating

        imul ecx,eax,ItemInfo

        .if ([rsi].m_pFiles[rcx].currentPosition == [rsi].m_pFiles[rcx].previousPosition)

            movss xmm0,diPosition.y
            movss xmm1,[rsi].m_pFiles[rcx].currentPosition
            addss xmm1,@CatStr(%msc_iconSize, <.0>)
            comiss xmm0,xmm1

            .ifb

                .if SetCurrentDirectory(&[rsi].m_pFiles[rcx].szFilename)

                    this.LoadDirectory()
                    .if (SUCCEEDED(eax))

                        InvalidateRect([rsi].m_d2dHwnd, NULL, FALSE)
                    .endif
                .endif
            .endif
        .endif
    .endif
    ret

ListViewApp::OnLeftButtonDown endp

;/******************************************************************
;*                                                                 *
;*  ListViewApp::OnLeftButtonDown                                  *
;*                                                                 *
;*  Called when the mouse wheel is moved.                          *
;*                                                                 *
;******************************************************************/

ListViewApp::OnMouseWheel proc uses rsi rdi wParam:WPARAM, lParam:LPARAM

  local size:D2D1_SIZE_F
  local s:SCROLLINFO

    mov rsi,rcx

    this.m_pRT.GetSize(&size)
    this.GetInterpolatedScrollPosition()

    cvtss2si    eax,xmm0
    mov         [rsi].m_previousScrollPos,eax
    movzx       edx,word ptr wParam[2]
    mov         eax,[rsi].m_currentScrollPos
    sub         eax,edx
    mov         ecx,[rsi].m_scrollRange
    cvtss2si    edx,size.height
    sub         ecx,edx
    cmp         eax,ecx
    cmovg       eax,ecx
    xor         ecx,ecx
    cmp         eax,ecx
    cmovl       eax,ecx
    mov         [rsi].m_currentScrollPos,eax
    lea         rdi,s
    xor         eax,eax
    mov         ecx,SCROLLINFO
    rep         stosb
    mov         s.cbSize,SCROLLINFO
    mov         s.fMask,SIF_PAGE or SIF_POS or SIF_RANGE or SIF_TRACKPOS

    .return .if !GetScrollInfo([rsi].m_parentHwnd, SB_VERT, &s)

    .if [rsi].m_currentScrollPos != s.nPos

        mov s.nPos,[rsi].m_currentScrollPos
        SetScrollInfo([rsi].m_parentHwnd, SB_VERT, &s, TRUE)

        mov [rsi].m_animatingScroll,msc_totalAnimatingScrollFrames
        InvalidateRect([rsi].m_d2dHwnd, NULL, FALSE)
    .endif
    ret

ListViewApp::OnMouseWheel endp


;/******************************************************************
;*                                                                 *
;*  ListViewApp::OnVScroll                                         *
;*                                                                 *
;*  Called when a WM_VSCROLL message is sent.                      *
;*                                                                 *
;******************************************************************/

ListViewApp::OnVScroll proc uses rsi rdi rbx wParam:WPARAM, lParam:LPARAM

  local size:D2D1_SIZE_F

    mov rsi,rcx
    mov ebx,[rsi].m_currentScrollPos

    .switch dx

    .case SB_LINEUP
        dec ebx
        .endc

    .case SB_LINEDOWN
        inc ebx
        .endc

    .case SB_PAGEUP
        this.m_pRT.GetSize(&size)
        cvtss2si eax,size.height
        sub ebx,eax
        .endc

    .case SB_PAGEDOWN
        this.m_pRT.GetSize(&size)
        cvtss2si eax,size.height
        add ebx,eax
        .endc

    .case SB_THUMBTRACK
       .new s:SCROLLINFO
        mov s.fMask,SIF_PAGE or SIF_POS or SIF_RANGE or SIF_TRACKPOS
        .if !GetScrollInfo([rsi].m_parentHwnd, SB_VERT, &s)
            .Assert(eax)
            .return
        .endif
        mov ebx,s.nTrackPos
        .endc
    .endsw
    mov eax,[rsi].m_scrollRange
    .ifs ebx > eax
        mov ebx,eax
    .endif
    .ifs ebx < 0
        xor ebx,ebx
    .endif

    this.GetInterpolatedScrollPosition()
    cvtss2si eax,xmm0
    mov [rsi].m_previousScrollPos,eax
    mov [rsi].m_currentScrollPos,ebx

   .new s:SCROLLINFO
    mov s.fMask,SIF_PAGE or SIF_POS or SIF_RANGE or SIF_TRACKPOS
    .if !GetScrollInfo([rsi].m_parentHwnd, SB_VERT, &s)

        .Assert(eax)
        .return
    .endif

    .if ([rsi].m_currentScrollPos != s.nPos)

        mov s.nPos,[rsi].m_currentScrollPos
        SetScrollInfo([rsi].m_parentHwnd, SB_VERT, &s, TRUE)

        mov [rsi].m_animatingScroll,msc_totalAnimatingScrollFrames
        InvalidateRect([rsi].m_d2dHwnd, NULL, FALSE)
    .endif
    ret

ListViewApp::OnVScroll endp

    end _tstart
