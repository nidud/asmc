;; Modify the following defines if you have to target a platform prior to the ones specified below.
;; Refer to MSDN for the latest info on corresponding values for different platforms.

ifndef WINVER                   ;; Allow use of features specific to Windows XP or later.
WINVER equ 0x0501               ;; Change this to the appropriate value to target other versions of Windows.
endif

ifndef _WIN32_WINNT             ;; Allow use of features specific to Windows XP or later.
_WIN32_WINNT equ 0x0501         ;; Change this to the appropriate value to target other versions of Windows.
endif

ifndef _WIN32_WINDOWS           ;; Allow use of features specific to Windows 98 or later.
_WIN32_WINDOWS equ 0x0410       ;; Change this to the appropriate value to target Windows Me or later.
endif

ifndef _WIN32_IE                ;; Allow use of features specific to IE 6.0 or later.
_WIN32_IE equ 0x0600            ;; Change this to the appropriate value to target other versions of IE.
endif

WIN32_LEAN_AND_MEAN equ 1       ;; Exclude rarely-used stuff from Windows headers

include windows.inc
include wincodec.inc
include commdlg.inc
include gdiplus.inc
include winres.inc
include tchar.inc
include WICViewerGDIPlus.inc

.data

     vtable DemoAppVtbl {
        DemoApp_Release,
        DemoApp_Initialize,
        DemoApp_CreateDIBFromFile,
        DemoApp_LocateImageFile,
        DemoApp_ConvertBitmapSource,
        DemoApp_CreateDIBSectionFromBitmapSource,
        DemoApp_DeleteBufferAndBmp,
        DemoApp_WndProc,
        DemoApp_OnPaint
        }

.code

;
;  Initialize member data
;

DemoApp::DemoApp proc

    mov [rcx].DemoApp.lpVtbl,&vtable
    xor eax,eax
    mov [rcx].DemoApp.m_pIWICFactory,rax
    mov [rcx].DemoApp.m_pOriginalBitmapSource,rax
    mov [rcx].DemoApp.m_pGdiPlusBitmap.nativeImage,rax
    mov [rcx].DemoApp.m_pbBuffer,rax
    ret

DemoApp::DemoApp endp


wWinMain proc WINAPI hInstance:HINSTANCE, hPrevInstance:HINSTANCE, pszCmdLine:LPWSTR, nCmdShow:SINT

    local hr:HRESULT

    HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0)
    mov hr,CoInitializeEx(NULL, COINIT_APARTMENTTHREADED or COINIT_DISABLE_OLE1DDE)

    .if (SUCCEEDED(hr))

        ;; Initialize GDI+.
        .new gdiplus:GdiPlus()

        ;; Checking return status from GdiplusStartup

        .if (eax == Ok)

            .new app:DemoApp()

            app.Initialize(hInstance)

            .if (SUCCEEDED(eax))

                .new msg:MSG

                ;; Main message loop:

                .while GetMessage(&msg, NULL, 0, 0)

                    .break .if (eax == -1)

                    TranslateMessage(&msg)
                    DispatchMessage(&msg)
                .endw
            .endif
            gdiplus.Release()
        .endif
        CoUninitialize()
    .endif
    xor eax,eax
    ret

wWinMain endp

    assume rsi:ptr DemoApp

;
;  Tear down resources
;

DemoApp::Release proc uses rsi

    mov rsi,rcx
    SafeRelease(&[rsi].m_pIWICFactory, IWICImagingFactory)
    SafeRelease(&[rsi].m_pOriginalBitmapSource, IWICBitmapSource)
    this.DeleteBufferAndBmp()
    ret

DemoApp::Release endp

;
;  Create application window and resources
;

DemoApp::Initialize proc uses rsi rdi hInstance:HINSTANCE

    local hr:HRESULT
    local wcex:WNDCLASSEX

    mov rsi,rcx
    mov rdi,rdx

    ;; Create WIC factory
    CoCreateInstance(&CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER,
        &IID_IWICImagingFactory, &[rsi].m_pIWICFactory)

    ;; Register window class

    .if (SUCCEEDED(eax))

        mov wcex.cbSize,        sizeof(WNDCLASSEX)
        mov wcex.style,         CS_HREDRAW or CS_VREDRAW
        mov wcex.lpfnWndProc,   &s_WndProc
        mov wcex.cbClsExtra,    0
        mov wcex.cbWndExtra,    sizeof(LONG_PTR)
        mov wcex.hInstance,     rdi
        mov wcex.hIcon,         NULL
        mov wcex.hCursor,       LoadCursor(NULL, IDC_ARROW)
        mov wcex.hbrBackground, COLOR_ACTIVEBORDER
        mov wcex.lpszMenuName,  MAKEINTRESOURCE(IDR_MAINMENU)
        mov wcex.lpszClassName, &@CStr(L"WICViewerGDIPlus")
        mov wcex.hIconSm,       NULL

        mov [rsi].m_hInst,rdi
        .ifd RegisterClassEx(&wcex)
            mov eax,S_OK
        .else
            mov eax,E_FAIL
        .endif
    .endif

    .if (SUCCEEDED(eax))

        ;; Create window
        CreateWindowEx(0, L"WICViewerGDIPlus", L"WIC Viewer GDI Plus Sample",
            WS_OVERLAPPEDWINDOW or WS_VISIBLE,
            CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, NULL, NULL, rdi, rsi)

        .if rax
            mov eax,S_OK
        .else
            mov eax,E_FAIL
        .endif
    .endif
    ret

DemoApp::Initialize endp

;
;  Load an image file and create an DIB Section
;
DemoApp::CreateDIBFromFile proc uses rsi hWnd:HWND

    local hr:HRESULT
    local szFileName[MAX_PATH]:WCHAR

    mov hr,S_OK
    mov rsi,rcx

    ;; Step 1: Create the open dialog box and locate the image file

    .if this.LocateImageFile(hWnd, &szFileName, ARRAYSIZE(szFileName))

        ;; Step 2: Decode the source image to IWICBitmapSource

        ;; Create a decoder
        .new pDecoder:ptr IWICBitmapDecoder

        mov pDecoder,NULL
        mov rcx,[rsi].m_pIWICFactory

        [rcx].IWICImagingFactory.CreateDecoderFromFilename(
            &szFileName,                     ;; Image to be decoded
            NULL,                            ;; Do not prefer a particular vendor
            GENERIC_READ,                    ;; Desired read access to the file
            WICDecodeMetadataCacheOnDemand,  ;; Cache metadata when needed
            &pDecoder                        ;; Pointer to the decoder
            )

        ;; Retrieve the first frame of the image from the decoder
        .new pFrame:ptr IWICBitmapFrameDecode

        mov hr,eax
        mov pFrame,NULL

        .if (SUCCEEDED(eax))

            mov hr,pDecoder.GetFrame(0, &pFrame)
        .endif

        ;; Retrieve IWICBitmapSource from the frame
        ;; m_pOriginalBitmapSource contains the original bitmap and acts as an intermediate

        .if (SUCCEEDED(hr))

            SafeRelease(&[rsi].m_pOriginalBitmapSource, IWICBitmapSource)
            mov hr,pFrame.QueryInterface(&IID_IWICBitmapSource,
                &[rsi].m_pOriginalBitmapSource)
        .endif

        ;; Step 3: Scale the original IWICBitmapSource to the client rect size
        ;; and convert the pixel format
        .new pToRenderBitmapSource:ptr IWICBitmapSource

        mov pToRenderBitmapSource,NULL

        .if (SUCCEEDED(hr))

            mov hr,this.ConvertBitmapSource(hWnd, &pToRenderBitmapSource)
        .endif

        ;; Step 4: Create a DIB from the converted IWICBitmapSource
        .if (SUCCEEDED(hr))

            mov hr,this.CreateDIBSectionFromBitmapSource(pToRenderBitmapSource)
        .endif

        SafeRelease(&pToRenderBitmapSource, IWICBitmapSource)
        SafeRelease(&pDecoder, IWICBitmapDecoder)
        SafeRelease(&pFrame, IWICBitmapFrameDecode)
    .endif

    .return hr

DemoApp::CreateDIBFromFile endp

;
; Creates an open file dialog box and locate the image to decode.
;

DemoApp::LocateImageFile proc hWnd:HWND, pszFileName:LPWSTR, cchFileName:DWORD

    local ofn:OPENFILENAME

    mov word ptr [r8],0
    ZeroMemory(&ofn, sizeof(ofn))

    mov ofn.lStructSize,  sizeof(ofn)
    mov ofn.hwndOwner,    hWnd
    mov ofn.lpstrFilter,  &@CStr(
        L"All Image Files\0"               L"*.bmp;*.dib;*.wdp;*.mdp;*.hdp;*.gif;*.png;*.jpg;*.jpeg;*.tif;*.ico\0"
        L"Windows Bitmap\0"                L"*.bmp;*.dib\0"
        L"High Definition Photo\0"         L"*.wdp;*.mdp;*.hdp\0"
        L"Graphics Interchange Format\0"   L"*.gif\0"
        L"Portable Network Graphics\0"     L"*.png\0"
        L"JPEG File Interchange Format\0"  L"*.jpg;*.jpeg\0"
        L"Tiff File\0"                     L"*.tif\0"
        L"Icon\0"                          L"*.ico\0"
        L"All Files\0"                     L"*.*\0" )
    mov ofn.lpstrFile,    pszFileName
    mov ofn.nMaxFile,     cchFileName
    mov ofn.lpstrTitle,   &@CStr(L"Open Image")
    mov ofn.Flags,        OFN_FILEMUSTEXIST or OFN_PATHMUSTEXIST

    ;; Display the Open dialog box.
    GetOpenFileName(&ofn)
    ret

DemoApp::LocateImageFile endp


;
;  Scales original IWICBitmapSource to the client rect size  and convert
;  the pixel format. Store the converted bitmap as *ppToRenderBitmapSource
;

DemoApp::ConvertBitmapSource proc uses rsi hWnd:HWND, ppToRenderBitmapSource:ptr ptr IWICBitmapSource

    local hr:HRESULT
    local rcClient:RECT

    mov rsi,rcx
    mov qword ptr [r8],NULL

    ;; Get the client Rect
    mov hr,E_FAIL
    .if rcClient.GetClient(rdx)
        mov hr,S_OK
    .endif

    .if (SUCCEEDED(hr))

        ;; Create a BitmapScaler
        .new pScaler:ptr IWICBitmapScaler

        mov pScaler,NULL
        mov rcx,[rsi].m_pIWICFactory
        mov hr,[rcx].IWICImagingFactory.CreateBitmapScaler(&pScaler)

        ;; Initialize the bitmap scaler from the original bitmap map bits
        .if (SUCCEEDED(hr))

            rcClient.Width(r8d)
            rcClient.Height(r9d)
            mov hr,pScaler.Initialize([rsi].m_pOriginalBitmapSource, r8d, r9d,
                WICBitmapInterpolationModeFant)
        .endif

        ;; Format convert the bitmap into 32bppBGR, a convenient
        ;; pixel format for GDI+ rendering
        .if (SUCCEEDED(hr))

            .new pConverter:ptr IWICFormatConverter

            mov pConverter,NULL
            mov rcx,[rsi].m_pIWICFactory
            mov hr,[rcx].IWICImagingFactory.CreateFormatConverter(&pConverter)

            ;; Format convert to 32bppBGR
            .if (SUCCEEDED(hr))

                mov hr,pConverter.Initialize(
                    pScaler,                         ;; Input bitmap to convert
                    &GUID_WICPixelFormat32bppBGR,    ;; Destination pixel format
                    WICBitmapDitherTypeNone,         ;; Specified dither patterm
                    NULL,                            ;; Specify a particular palette
                    0.0,                             ;; Alpha threshold
                    WICBitmapPaletteTypeCustom       ;; Palette translation type
                    )

                ;; Store the converted bitmap as ppToRenderBitmapSource
                .if (SUCCEEDED(hr))

                    mov hr,pConverter.QueryInterface(
                        &IID_IWICBitmapSource, ppToRenderBitmapSource)
                .endif
            .endif

            SafeRelease(&pConverter, IWICFormatConverter)
        .endif

        SafeRelease(&pScaler, IWICBitmapScaler)
    .endif

    .return hr

DemoApp::ConvertBitmapSource endp


;
;  Creates a DIB Section from the converted IWICBitmapSource
;

DemoApp::CreateDIBSectionFromBitmapSource proc uses rsi pToRenderBitmapSource:ptr IWICBitmapSource

    local hr:HRESULT
    local width:UINT
    local height:UINT
    local pixelFormat:WICPixelFormatGUID

    mov width,0
    mov height,0
    mov rsi,rcx

    ;; Check BitmapSource format

    mov hr,pToRenderBitmapSource.GetPixelFormat(&pixelFormat)

    .if (SUCCEEDED(eax))

        mov hr,E_FAIL
        mov rax,qword ptr pixelFormat
        .if rax == qword ptr GUID_WICPixelFormat32bppBGR
            mov hr,S_OK
        .endif
    .endif

    .if (SUCCEEDED(hr))

        mov hr,pToRenderBitmapSource.GetSize(&width, &height)
    .endif

    .new cbStride:UINT
     mov cbStride,0

    .if (SUCCEEDED(hr))

        ;; Size of a scan line represented in bytes: 4 bytes each pixel
        mov hr,UIntMult(width, sizeof(ARGB), &cbStride)
    .endif

    .new cbBufferSize:UINT
     mov cbBufferSize,0

    .if (SUCCEEDED(hr))

        ;; Size of the image, represented in bytes
        mov hr,UIntMult(cbStride, height, &cbBufferSize)
    .endif

    .if (SUCCEEDED(hr))

        ;; Make sure to free previously allocated buffer and bitmap

        this.DeleteBufferAndBmp()
        mov hr,E_FAIL
        .if GdipAlloc(cbBufferSize)
            mov hr,S_OK
        .endif
        mov [rsi].DemoApp.m_pbBuffer,rax

        .if (SUCCEEDED(hr))

            .new rc:WICRect(0, 0, width, height)

            ;; Extract the image into the GDI+ Bitmap
            mov hr,pToRenderBitmapSource.CopyPixels(
                &rc,
                cbStride,
                cbBufferSize,
                [rsi].DemoApp.m_pbBuffer
                )

            .if (SUCCEEDED(hr))

                .new bm:Bitmap(
                    width,
                    height,
                    cbStride,
                    PixelFormat32bppRGB,
                    [rsi].DemoApp.m_pbBuffer
                    )

                mov hr,E_FAIL
                .if bm.lastResult == S_OK
                    mov [rsi].DemoApp.m_pGdiPlusBitmap,bm
                    mov hr,S_OK
                .endif
            .endif

            .if (FAILED(hr))

                this.DeleteBufferAndBmp()
            .endif
        .endif
    .endif

    .return hr

DemoApp::CreateDIBSectionFromBitmapSource endp

;
;  Clean up Bitmap resources
;

DemoApp::DeleteBufferAndBmp proc uses rsi

    mov rsi,rcx
    Image_Release([rsi].m_pGdiPlusBitmap)

    GdipFree([rsi].m_pbBuffer)
    mov [rsi].m_pbBuffer,NULL
    ret

DemoApp::DeleteBufferAndBmp endp

;
;  Registered window message handler
;

s_WndProc proc hWnd:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM

    local pThis:ptr DemoApp
    local pcs:LPCREATESTRUCT

    xor eax,eax
    .if edx == WM_NCCREATE

        mov r8,[r9].CREATESTRUCT.lpCreateParams
        SetWindowLongPtr(rcx, GWLP_USERDATA, PtrToUlong(r8))
        DefWindowProc(hWnd, uMsg, wParam, lParam)

    .else

        mov pThis,GetWindowLongPtr(rcx, GWLP_USERDATA)
        .if rax
            pThis.WndProc(hWnd, uMsg, wParam, lParam)
        .else
            DefWindowProc(hWnd, uMsg, wParam, lParam)
        .endif
    .endif
    ret

s_WndProc endp

;
;  Internal Window message handler
;

DemoApp::WndProc proc hWnd:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM

    .switch r8d
    .case WM_COMMAND

        ;; Parse the menu selections:

        .switch r9w
        .case IDM_FILE

            this.CreateDIBFromFile(rdx)
            .if (SUCCEEDED(eax))
                InvalidateRect(hWnd, NULL, TRUE)
            .else
                MessageBox(NULL, L"Failed to load image, select another one.", L"Application Error", MB_ICONEXCLAMATION or MB_OK)
            .endif
            .endc

        .case IDM_EXIT
            PostMessage(hWnd, WM_CLOSE, 0, 0)
            .endc
        .endsw
        .endc

    .case WM_SIZE

       .new pToRenderBitmapSource:ptr IWICBitmapSource
        mov pToRenderBitmapSource,NULL
        this.ConvertBitmapSource(hWnd, &pToRenderBitmapSource)
        .if (SUCCEEDED(eax))

            this.CreateDIBSectionFromBitmapSource(pToRenderBitmapSource);
            SafeRelease(&pToRenderBitmapSource, IWICBitmapSource)
        .endif
        .endc

    .case WM_PAINT
        .return this.OnPaint(hWnd)
    .case WM_DESTROY
        PostQuitMessage(0);
        .endc
    .case WM_CHAR
        .gotosw(WM_DESTROY) .if r9d == VK_ESCAPE
        .endc
    .default
        .return DefWindowProc(hWnd, uMsg, wParam, lParam)
    .endsw

    .return 0

DemoApp::WndProc endp

;
; Rendering callback using GDI+
;

DemoApp::OnPaint proc uses rsi hWnd:HWND

    local lRet:LRESULT
    local ps:PAINTSTRUCT
    local hdc:HDC

    mov rsi,rcx
    mov hdc,BeginPaint(hWnd, &ps)
    mov lRet,1

    .if rax

        .if ([rsi].m_pGdiPlusBitmap.nativeImage)

            .new graphics:Graphics(hdc)

            ;; Create rendering area

            .new bm:Bitmap
            .new rcClient:RectF(0.0, 0.0, 0.0, 0.0)
             mov bm,[rsi].m_pGdiPlusBitmap

            bm.GetWidth()
            cvtsi2ss xmm0,eax
            movss rcClient.Width,xmm0
            bm.GetHeight()
            cvtsi2ss xmm0,eax
            movss rcClient.Height,xmm0

            ;; Render the Bitmap
            graphics.DrawImage(&[rsi].m_pGdiPlusBitmap, &rcClient)

            mov lRet,0
        .endif

        EndPaint(hWnd, &ps)
    .endif

    .return lRet

DemoApp::OnPaint endp

RCBEGIN

    RCTYPES 1
    RCENTRY RT_MENU
    RCENUMN 1
    RCENUMX IDR_MAINMENU
    RCLANGX LANGID_US

    MENUBEGIN
      MENUNAME "&File", MF_END
        MENUITEM IDM_FILE, "&Open..."
        MENUITEM IDM_EXIT, "E&xit", MF_END
    MENUEND

RCEND

    end _tstart
