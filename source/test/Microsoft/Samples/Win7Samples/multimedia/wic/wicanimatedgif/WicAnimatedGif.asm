ifndef WINVER
define WINVER 0x0501
endif
ifndef _WIN32_WINNT
define _WIN32_WINNT 0x0501
endif
ifndef _WIN32_WINDOWS
define _WIN32_WINDOWS 0x0410
endif
ifndef _WIN32_IE
define _WIN32_IE 0x0600
endif
define WIN32_LEAN_AND_MEAN

include windows.inc
include wincodec.inc
include commdlg.inc
include d2d1.inc
include winres.inc
include tchar.inc

include WICAnimatedGif.inc

define DELAY_TIMER_ID 1  ; Global ID for the timer, only one timer is used

    .code

;
;  DemoApp::DemoApp constructor
;
;  Initializes member data
;

DemoApp::DemoApp proc

    @ComAlloc(DemoApp)
    ret

DemoApp::DemoApp endp

;
;  WinMain
;
;  Application entrypoint
;

wWinMain proc hInstance:HINSTANCE, hPrevInstance:HINSTANCE, pszCmdLine:LPWSTR, nCmdShow:SINT

    HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0)

    .ifd CoInitializeEx(NULL,
            COINIT_APARTMENTTHREADED or COINIT_DISABLE_OLE1DDE) == S_OK

        .new app:ptr DemoApp()
        .ifd app.Initialize(hInstance) == S_OK

            .new msg:MSG

            ;; Main message loop:

            .while GetMessage(&msg, NULL, 0, 0)

                .break .if (eax == -1)

                TranslateMessage(&msg)
                DispatchMessage(&msg)
            .endw
        .endif
        app.Release()
        CoUninitialize()
    .endif
    .return 0

wWinMain endp


    assume rsi:ptr DemoApp

;
;  DemoApp::~DemoApp destructor
;
;  Tears down resources
;

DemoApp::Release proc uses rsi

    mov rsi,rcx
    SafeRelease([rsi].m_pD2DFactory)
    SafeRelease([rsi].m_pHwndRT)
    SafeRelease([rsi].m_pFrameComposeRT)
    SafeRelease([rsi].m_pRawFrame)
    SafeRelease([rsi].m_pSavedFrame)
    SafeRelease([rsi].m_pIWICFactory)
    SafeRelease([rsi].m_pDecoder)
    free(rsi)
    ret

DemoApp::Release endp


;
;  DemoApp::Initialize
;
;  Creates application window and device-independent resources
;

DemoApp::Initialize proc uses rsi rdi hInstance:HINSTANCE

    local hr:HRESULT
    local wcex:WNDCLASSEX

    mov rsi,rcx
    mov rdi,rdx

    ; Register window class

    mov wcex.cbSize,        WNDCLASSEX
    mov wcex.style,         CS_HREDRAW or CS_VREDRAW
    mov wcex.lpfnWndProc,   &s_WndProc
    mov wcex.cbClsExtra,    0
    mov wcex.cbWndExtra,    sizeof(LONG_PTR)
    mov wcex.hInstance,     rdi
    mov wcex.hIcon,         NULL
    mov wcex.hCursor,       LoadCursor(NULL, IDC_ARROW)
    mov wcex.hbrBackground, COLOR_ACTIVEBORDER
    mov wcex.lpszMenuName,  MAKEINTRESOURCE(IDR_WICANIMATEDGIF)
    mov wcex.lpszClassName, &@CStr(L"WICANIMATEDGIF")
    mov wcex.hIconSm,       NULL

    mov hr,E_FAIL
    .ifd RegisterClassEx(&wcex)
        mov hr,S_OK
    .endif

    .if (SUCCEEDED(hr))

        ;; Create D2D factory
        mov hr,D2D1CreateFactory(
            D2D1_FACTORY_TYPE_SINGLE_THREADED,
            &IID_ID2D1Factory,
            NULL,
            &[rsi].m_pD2DFactory)
    .endif

    .if (SUCCEEDED(hr))

        ;; Create WIC factory
        mov hr,CoCreateInstance(
            &CLSID_WICImagingFactory,
            NULL,
            CLSCTX_INPROC_SERVER,
            &IID_IWICImagingFactory,
            &[rsi].m_pIWICFactory)
    .endif

    .if (SUCCEEDED(hr))

        ;; Create window
        mov [rsi].m_hWnd,CreateWindowEx(
            0,
            L"WICANIMATEDGIF",
            L"WIC Animated Gif Sample",
            WS_OVERLAPPEDWINDOW or WS_VISIBLE,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            NULL, NULL, rdi, rsi)

        mov hr,E_FAIL
        .if rax
            mov hr,S_OK
        .endif
    .endif

    .if (SUCCEEDED(hr))

        mov hr,[rsi].SelectAndDisplayGif()
        .if (FAILED(hr))

            DestroyWindow([rsi].m_hWnd)
        .endif
    .endif

    .return hr

DemoApp::Initialize endp


;
; DemoApp::CreateDeviceResources
;
; Creates a D2D hwnd render target for displaying gif frames
; to users and a D2D bitmap render for composing frames.
;

DemoApp::CreateDeviceResources proc uses rsi

    local hr:HRESULT
    local rcClient:RECT
    local size:D2D1_SIZE_U

    mov hr,S_OK
    mov rsi,rcx

    .if !GetClientRect([rsi].m_hWnd, &rcClient)

        mov hr,HRESULT_FROM_WIN32R(GetLastError())
    .endif

    .if (SUCCEEDED(hr))

        .if [rsi].m_pHwndRT == NULL

            ;; Create a D2D hwnd render target

           .new renderTargetProperties:D2D1_RENDER_TARGET_PROPERTIES()

            ;; Set the DPI to be the default system DPI to allow direct mapping
            ;; between image pixels and desktop pixels in different system DPI
            ;; settings

            mov renderTargetProperties.dpiX,DEFAULT_DPI
            mov renderTargetProperties.dpiY,DEFAULT_DPI

            rcClient.Width(r8d)
            rcClient.Height(r9d)
           .new hwndRenderTragetproperties:D2D1_HWND_RENDER_TARGET_PROPERTIES([rsi].m_hWnd, r8d, r9d)

            mov hr,this.m_pD2DFactory.CreateHwndRenderTarget(
                &renderTargetProperties,
                &hwndRenderTragetproperties,
                &[rsi].m_pHwndRT)

        .else

            ;; We already have a hwnd render target, resize it to the window size

            mov size.width,rcClient.Width()
            mov size.height,rcClient.Height()

            mov hr,this.m_pHwndRT.Resize(&size)
        .endif
    .endif

    .if (SUCCEEDED(hr))

        ; Create a bitmap render target used to compose frames. Bitmap render
        ; targets cannot be resized, so we always recreate it.

        SafeRelease([rsi].m_pFrameComposeRT)

        cvtsi2ss xmm0,[rsi].m_cxGifImage
        cvtsi2ss xmm1,[rsi].m_cyGifImage
        movss size.width,xmm0
        movss size.height,xmm1
        mov hr,this.m_pHwndRT.CreateCompatibleRenderTarget(
            &size,
            NULL,
            NULL,
            D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS_NONE,
            &[rsi].m_pFrameComposeRT)
    .endif

    .return hr

DemoApp::CreateDeviceResources endp


;;
;; DemoApp::OnRender
;;
;; Called whenever the application needs to display the client
;; window.
;;
;; Renders the pre-composed frame by drawing it onto the hwnd
;; render target.
;;

DemoApp::OnRender proc

  local hr:HRESULT
  local pFrameToRender:ptr ID2D1Bitmap
  local pRT:ptr ID2D1HwndRenderTarget

    mov hr,S_OK
    mov pFrameToRender,NULL
    mov pRT,[rcx].DemoApp.m_pHwndRT

    ;; Check to see if the render targets are initialized

    .if (pRT && [rcx].DemoApp.m_pFrameComposeRT)

        .if (SUCCEEDED(hr))

            ;; Only render when the window is not occluded

            pRT.CheckWindowState()

            .if !( eax & D2D1_WINDOW_STATE_OCCLUDED )

               .new drawRect:D2D1_RECT_F
                mov hr,this.CalculateDrawRectangle(&drawRect)

                .if (SUCCEEDED(hr))

                    ;; Get the bitmap to draw on the hwnd render target

                    mov hr,this.m_pFrameComposeRT.GetBitmap(&pFrameToRender)
                .endif

                .if (SUCCEEDED(hr))

                    ;; Draw the bitmap onto the calculated rectangle

                   .new color:D3DCOLORVALUE(Black, 0.0)
                    pRT.BeginDraw()
                    pRT.Clear(&color)
                    pRT.DrawBitmap(
                        pFrameToRender, &drawRect,
                        1.0,
                        D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
                        NULL)
                    pRT.EndDraw(NULL, NULL)
                    mov hr,eax
                .endif
            .endif
        .endif
    .endif

    SafeRelease(pFrameToRender)
   .return hr

DemoApp::OnRender endp

;
; DemoApp::GetFileOpen
;
; Creates an open file dialog box and returns the filename
; of the file selected(if any).
;

DemoApp::GetFileOpen proc pszFileName:ptr WCHAR, cchFileName:DWORD

    local ofn:OPENFILENAME

    mov WCHAR ptr [rdx],0
    RtlZeroMemory(&ofn, sizeof(ofn))

    mov rcx,this
    mov ofn.lStructSize,     sizeof(ofn)
    mov ofn.hwndOwner,       [rcx].DemoApp.m_hWnd
    mov ofn.lpstrFilter,     &@CStr(L"*Gif Files\0*.gif\0")
    mov ofn.lpstrFile,       pszFileName
    mov ofn.nMaxFile,        cchFileName
    mov ofn.lpstrTitle,      &@CStr(L"Select an image to display...")
    mov ofn.Flags,           OFN_FILEMUSTEXIST or OFN_PATHMUSTEXIST

    ;; Display the Open dialog box.
    GetOpenFileName(&ofn)
    ret

DemoApp::GetFileOpen endp

;;
;; DemoApp::OnResize
;;
;; If the application receives a WM_SIZE message, this method
;; will resize the render target appropriately.
;;

DemoApp::OnResize proc uWidth:UINT, uHeight:UINT

    mov eax,S_OK

    .if [rcx].DemoApp.m_pHwndRT

       .new size:D2D1_SIZE_U
        mov size.width,edx
        mov size.height,r8d

        this.m_pHwndRT.Resize(&size)
    .endif
    ret

DemoApp::OnResize endp

;;
;; DemoApp::s_WndProc
;;
;; Static window message handler used to initialize the
;; application object and call the object's member WndProc
;;

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

;;
;; DemoApp::WndProc
;;
;; Window message handler
;;

DemoApp::WndProc proc hWnd:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM

    local hr:HRESULT

    mov hr,S_OK

    .switch r8d
    .case WM_COMMAND

        ;; Parse the menu selections:

        .switch r9w
        .case IDM_FILE

            mov hr,this.SelectAndDisplayGif()
            .if (FAILED(eax))

                MessageBox(hWnd, L"Load gif file failed. Exiting application.", L"Error", MB_OK)
                PostQuitMessage(1)
                .return 1
            .endif
            .endc

        .case IDM_EXIT
            PostMessage(hWnd, WM_CLOSE, 0, 0)
            .endc
        .endsw
        .endc

    .case WM_SIZE

        movzx edx,word ptr lParam
        movzx r8d,word ptr lParam[2]
        mov hr,this.OnResize(edx, r8d)
        .endc

    .case WM_PAINT

        mov hr,this.OnRender()
        ValidateRect(hWnd, NULL)
        .endc

    .case WM_DISPLAYCHANGE

        InvalidateRect(hWnd, NULL, FALSE)
        .endc

    .case WM_DESTROY
        PostQuitMessage(0);
        .return 0

    .case WM_CHAR
        .gotosw(WM_DESTROY) .if r9d == VK_ESCAPE
        .endc

    .case WM_TIMER

        ;; Timer expired, display the next frame and set a new timer
        ;; if needed

        mov hr,this.ComposeNextFrame()
        InvalidateRect(hWnd, NULL, FALSE)
        .endc

    .default
        .return DefWindowProc(hWnd, uMsg, wParam, lParam)
    .endsw

    ;; In case of a device loss, recreate all the resources and start playing
    ;; gif from the beginning
    ;;
    ;; In case of other errors from resize, paint, and timer event, we will
    ;; try our best to continue displaying the animation

    .if (hr == D2DERR_RECREATE_TARGET)

        mov hr,this.RecoverDeviceResources()
        .if (FAILED(hr))

            MessageBox(hWnd, L"Device loss recovery failed. Exiting application.", L"Error", MB_OK);
            PostQuitMessage(1);
        .endif
    .endif

    .return 0

DemoApp::WndProc endp

;;
;; DemoApp::GetGlobalMetadata()
;;
;; Retrieves global metadata which pertains to the entire image.
;;

DemoApp::GetGlobalMetadata proc uses rsi

  local hr:HRESULT
  local propValue:PROPVARIANT
  local pMetadataQueryReader:ptr IWICMetadataQueryReader

    mov rsi,rcx
    mov pMetadataQueryReader,NULL
    PropVariantInit(&propValue)

    ;; Get the frame count

    mov hr,this.m_pDecoder.GetFrameCount(&[rsi].m_cFrames)

    .if (SUCCEEDED(hr))

        ;; Create a MetadataQueryReader from the decoder

        mov hr,this.m_pDecoder.GetMetadataQueryReader(
            &pMetadataQueryReader)
    .endif

    .if (SUCCEEDED(hr))

        ;; Get background color

        this.GetBackgroundColor(pMetadataQueryReader)

        .if(FAILED(eax))

            ;; Default to transparent if failed to get the color

            lea rcx,[rsi].m_backgroundColor
            [rcx].D3DCOLORVALUE.Init(0, 0.0)
        .endif
    .endif

    ;; Get global frame size

    .if (SUCCEEDED(hr))

        ;; Get width

        mov hr,pMetadataQueryReader.GetMetadataByName(L"/logscrdesc/Width", &propValue)

        .if (SUCCEEDED(hr))

            mov hr,E_FAIL
            .if propValue.vt == VT_UI2
                mov hr,S_OK
            .endif

            .if (SUCCEEDED(hr))

                mov [rsi].m_cxGifImage,propValue.uiVal
            .endif
            PropVariantClear(&propValue)
        .endif
    .endif

    .if (SUCCEEDED(hr))

        ;; Get height

        mov hr,pMetadataQueryReader.GetMetadataByName(L"/logscrdesc/Height", &propValue)
        .if (SUCCEEDED(hr))

            mov hr,E_FAIL
            .if propValue.vt == VT_UI2
                mov hr,S_OK
            .endif

            .if (SUCCEEDED(hr))

                mov [rsi].m_cyGifImage,propValue.uiVal
            .endif
            PropVariantClear(&propValue)
        .endif
    .endif

    .if (SUCCEEDED(hr))

        ;; Get pixel aspect ratio

        mov hr,pMetadataQueryReader.GetMetadataByName(L"/logscrdesc/PixelAspectRatio", &propValue)
        .if (SUCCEEDED(hr))

            mov hr,E_FAIL
            .if propValue.vt == VT_UI1
                mov hr,S_OK
            .endif

            .if (SUCCEEDED(hr))

                .new uPixelAspRatio:UINT
                 mov uPixelAspRatio,propValue.bVal

                .if uPixelAspRatio != 0

                    ;; Need to calculate the ratio. The value in uPixelAspRatio
                    ;; allows specifying widest pixel 4:1 to the tallest pixel of
                    ;; 1:4 in increments of 1/64th

                    .new pixelAspRatio:FLOAT

                    cvtsi2ss xmm0,uPixelAspRatio
                    addss xmm0,15.0
                    divss xmm0,64.0

                    ;; Calculate the image width and height in pixel based on the
                    ;; pixel aspect ratio. Only shrink the image.

                    comiss xmm0,1.0
                    .ifa

                        cvtsi2ss xmm1,[rsi].m_cyGifImage
                        divss xmm1,xmm0
                        cvtss2si eax,xmm1
                        mov [rsi].m_cyGifImagePixel,eax
                        mov [rsi].m_cxGifImagePixel,[rsi].m_cxGifImage

                    .else
                        cvtsi2ss xmm1,[rsi].m_cxGifImage
                        mulss xmm0,xmm1
                        cvtss2si eax,xmm0
                        mov [rsi].m_cxGifImagePixel,eax
                        mov [rsi].m_cyGifImagePixel,[rsi].m_cyGifImage
                    .endif

                .else

                    ;; The value is 0, so its ratio is 1
                    mov [rsi].m_cxGifImagePixel,[rsi].m_cxGifImage
                    mov [rsi].m_cyGifImagePixel,[rsi].m_cyGifImage
                .endif
            .endif
            PropVariantClear(&propValue)
        .endif
    .endif

    ;; Get looping information

    .if (SUCCEEDED(hr))

        ;; First check to see if the application block in the Application Extension
        ;; contains "NETSCAPE2.0" and "ANIMEXTS1.0", which indicates the gif animation
        ;; has looping information associated with it.
        ;;
        ;; If we fail to get the looping information, loop the animation infinitely.

        pMetadataQueryReader.GetMetadataByName(L"/appext/application", &propValue)

        .if !eax && ( propValue.vt == (VT_UI1 or VT_VECTOR) ) && \
            propValue.caub.cElems == 11 ;; Length of the application block

            .ifd memcmp(propValue.caub.pElems, "NETSCAPE2.0", 11)
                 memcmp(propValue.caub.pElems, "ANIMEXTS1.0", 11)
            .endif

            .if (SUCCEEDED(eax))

                PropVariantClear(&propValue)

                mov hr,pMetadataQueryReader.GetMetadataByName(L"/appext/data", &propValue)
                .if (SUCCEEDED(hr))

                    ;;  The data is in the following format:
                    ;;  byte 0: extsize (must be > 1)
                    ;;  byte 1: loopType (1 == animated gif)
                    ;;  byte 2: loop count (least significant byte)
                    ;;  byte 3: loop count (most significant byte)
                    ;;  byte 4: set to zero
                    mov rdx,propValue.caub.pElems
                    .if (propValue.vt == (VT_UI1 or VT_VECTOR) && \
                        propValue.caub.cElems >= 4 && \
                        byte ptr [rdx][0] > 0 && \
                        byte ptr [rdx][1] == 1)

                        movzx eax,byte ptr [rdx][2]
                        mov ah,byte ptr [rdx][3]
                        mov [rsi].m_uTotalLoopCount,eax

                        ;; If the total loop count is not zero, we then have a loop count
                        ;; If it is 0, then we repeat infinitely

                        .if eax

                            mov [rsi].m_fHasLoop,TRUE
                        .endif
                    .endif
                .endif
            .endif
        .endif
    .endif

    PropVariantClear(&propValue)
    SafeRelease(pMetadataQueryReader)
   .return hr

DemoApp::GetGlobalMetadata endp

;
; DemoApp::GetRawFrame()
;
; Decodes the current raw frame, retrieves its timing
; information, disposal method, and frame dimension for
; rendering.  Raw frame is the frame read directly from the gif
; file without composing.
;

DemoApp::GetRawFrame proc uses rsi uFrameIndex:UINT

  local hr:HRESULT
  local pConverter:ptr IWICFormatConverter
  local pWicFrame:ptr IWICBitmapFrameDecode
  local pFrameMetadataQueryReader:ptr IWICMetadataQueryReader
  local propValue:PROPVARIANT

    mov rsi,rcx
    mov pConverter,NULL
    mov pWicFrame,NULL
    mov pFrameMetadataQueryReader,NULL

    PropVariantInit(&propValue)

    ;; Retrieve the current frame

    mov hr,this.m_pDecoder.GetFrame(uFrameIndex, &pWicFrame)

    .if (SUCCEEDED(hr))

        ;; Format convert to 32bppPBGRA which D2D expects

        mov hr,this.m_pIWICFactory.CreateFormatConverter(&pConverter)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,pConverter.Initialize(
            pWicFrame,
            &GUID_WICPixelFormat32bppPBGRA,
            WICBitmapDitherTypeNone,
            NULL,
            0.0,
            WICBitmapPaletteTypeCustom)
    .endif

    .if (SUCCEEDED(hr))

        ; Create a D2DBitmap from IWICBitmapSource

        SafeRelease([rsi].m_pRawFrame)

        mov hr,this.m_pHwndRT.CreateBitmapFromWicBitmap(
            pConverter,
            NULL,
            &[rsi].m_pRawFrame)
    .endif

    .if (SUCCEEDED(hr))

        ; Get Metadata Query Reader from the frame
        mov hr,pWicFrame.GetMetadataQueryReader(&pFrameMetadataQueryReader)
    .endif

    ; Get the Metadata for the current frame
    .if (SUCCEEDED(hr))

        mov hr,pFrameMetadataQueryReader.GetMetadataByName(L"/imgdesc/Left", &propValue)
        .if (SUCCEEDED(hr))

            mov hr,E_FAIL
            .if propValue.vt == VT_UI2
                mov hr,S_OK
            .endif

            .if (SUCCEEDED(hr))

                movzx eax,propValue.uiVal
                cvtsi2ss xmm0,eax
                movss [rsi].m_framePosition.left,xmm0
            .endif
            PropVariantClear(&propValue);
        .endif
    .endif

    .if (SUCCEEDED(hr))

        mov hr,pFrameMetadataQueryReader.GetMetadataByName(L"/imgdesc/Top", &propValue)
        .if (SUCCEEDED(hr))

            mov hr,E_FAIL
            .if propValue.vt == VT_UI2
                mov hr,S_OK
            .endif

            .if (SUCCEEDED(hr))

                movzx eax,propValue.uiVal
                cvtsi2ss xmm0,eax
                movss [rsi].m_framePosition.top,xmm0
            .endif
            PropVariantClear(&propValue)
        .endif
    .endif

    .if (SUCCEEDED(hr))

        mov hr,pFrameMetadataQueryReader.GetMetadataByName(L"/imgdesc/Width", &propValue)
        .if (SUCCEEDED(hr))

            mov hr,E_FAIL
            .if propValue.vt == VT_UI2
                mov hr,S_OK
            .endif

            .if (SUCCEEDED(hr))

                movzx eax,propValue.uiVal
                cvtsi2ss xmm0,eax
                addss xmm0,[rsi].m_framePosition.left
                movss [rsi].m_framePosition.right,xmm0
            .endif
            PropVariantClear(&propValue)
        .endif
    .endif

    .if (SUCCEEDED(hr))

        mov hr,pFrameMetadataQueryReader.GetMetadataByName(L"/imgdesc/Height", &propValue)
        .if (SUCCEEDED(hr))

            mov hr,E_FAIL
            .if propValue.vt == VT_UI2
                mov hr,S_OK
            .endif

            .if (SUCCEEDED(hr))

                movzx eax,propValue.uiVal
                cvtsi2ss xmm0,eax
                addss xmm0,[rsi].m_framePosition.top
                movss [rsi].m_framePosition.bottom,xmm0
            .endif
            PropVariantClear(&propValue)
        .endif
    .endif

    .if (SUCCEEDED(hr))

        ;; Get delay from the optional Graphic Control Extension

        pFrameMetadataQueryReader.GetMetadataByName(L"/grctlext/Delay", &propValue)
        .if (SUCCEEDED(eax))

            mov hr,E_FAIL
            .if propValue.vt == VT_UI2
                mov hr,S_OK
            .endif

            .if (SUCCEEDED(hr))

                ;; Convert the delay retrieved in 10 ms units to a delay in 1 ms units

                mov hr,UIntMult(propValue.uiVal, 10, &[rsi].m_uFrameDelay)
            .endif
            PropVariantClear(&propValue)

        .else

            ;; Failed to get delay from graphic control extension. Possibly a
            ;; single frame image (non-animated gif)

            mov [rsi].m_uFrameDelay,0
        .endif

        .if (SUCCEEDED(hr))

            ;; Insert an artificial delay to ensure rendering for gif with very small
            ;; or 0 delay.  This delay number is picked to match with most browsers'
            ;; gif display speed.
            ;;
            ;; This will defeat the purpose of using zero delay intermediate frames in
            ;; order to preserve compatibility. If this is removed, the zero delay
            ;; intermediate frames will not be visible.

            .if [rsi].m_uFrameDelay < 90

                mov [rsi].m_uFrameDelay,90
            .endif
        .endif
    .endif

    .if (SUCCEEDED(hr))

        pFrameMetadataQueryReader.GetMetadataByName(L"/grctlext/Disposal", &propValue)
        .if (SUCCEEDED(eax))

            mov hr,E_FAIL
            .if propValue.vt == VT_UI1
                mov hr,S_OK
            .endif

            .if (SUCCEEDED(hr))

                mov [rsi].m_uFrameDisposal,propValue.bVal
            .endif

        .else

            ;; Failed to get the disposal method, use default. Possibly a
            ;; non-animated gif.

            mov [rsi].m_uFrameDisposal,DM_UNDEFINED
        .endif
    .endif

    PropVariantClear(&propValue)

    SafeRelease(pConverter)
    SafeRelease(pWicFrame)
    SafeRelease(pFrameMetadataQueryReader)
   .return hr

DemoApp::GetRawFrame endp

;
; DemoApp::GetBackgroundColor()
;
; Reads and stores the background color for gif.
;

DemoApp::GetBackgroundColor proc uses rsi pMetadataQueryReader:ptr IWICMetadataQueryReader

    local hr:HRESULT
    local dwBGColor:DWORD
    local backgroundIndex:BYTE
    local rgColors[256]:WICColor
    local cColorsCopied:UINT
    local propVariant:PROPVARIANT
    local pWicPalette:ptr IWICPalette

    mov rsi,rcx
    mov backgroundIndex,0
    mov cColorsCopied,0
    mov pWicPalette,NULL

    PropVariantInit(&propVariant)

    ; If we have a global palette, get the palette and background color

    mov hr,pMetadataQueryReader.GetMetadataByName("/logscrdesc/GlobalColorTableFlag", &propVariant)
    .if (SUCCEEDED(hr))

        mov hr,S_OK
        .if (propVariant.vt != VT_BOOL || !propVariant.boolVal)
            mov hr,E_FAIL
        .endif

        PropVariantClear(&propVariant)
    .endif

    .if (SUCCEEDED(hr))

        ; Background color index

        mov hr,pMetadataQueryReader.GetMetadataByName("/logscrdesc/BackgroundColorIndex", &propVariant)
        .if (SUCCEEDED(hr))

            mov hr,S_OK
            .if propVariant.vt != VT_UI1
                mov hr,E_FAIL
            .endif

            .if (SUCCEEDED(hr))

                mov backgroundIndex,propVariant.bVal
            .endif
            PropVariantClear(&propVariant)
        .endif
    .endif

    ; Get the color from the palette

    .if (SUCCEEDED(hr))

        mov hr,this.m_pIWICFactory.CreatePalette(&pWicPalette)
    .endif

    .if (SUCCEEDED(hr))

        ; Get the global palette

        mov hr,this.m_pDecoder.CopyPalette(pWicPalette)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,pWicPalette.GetColors(ARRAYSIZE(rgColors),  &rgColors, &cColorsCopied)
    .endif

    .if (SUCCEEDED(hr))

        ; Check whether background color is outside range

        mov hr,S_OK
        .if (backgroundIndex >= cColorsCopied)
            mov hr,E_FAIL
        .endif
    .endif

    .if (SUCCEEDED(hr))

        ; Get the color in ARGB format

        movzx ecx,backgroundIndex
        mov dwBGColor,rgColors[rcx*4]

        ; The background color is in ARGB format, and we want to
        ; extract the alpha value and convert it in FLOAT

        .new alpha:FLOAT

        shr eax,24
        cvtsi2ss xmm0,eax
        divss xmm0,255.0
        movss alpha,xmm0

        lea rcx,[rsi].m_backgroundColor
        [rcx].D3DCOLORVALUE.Init(dwBGColor, alpha)

    .endif

    SafeRelease(pWicPalette)
    .return hr

DemoApp::GetBackgroundColor endp

;
; DemoApp::CalculateDrawRectangle()
;
; Calculates a specific rectangular area of the hwnd
; render target to draw a bitmap containing the current
; composed frame.
;

    assume rbx:ptr D2D1_RECT_F

DemoApp::CalculateDrawRectangle proc uses rsi rbx drawRect:ptr D2D1_RECT_F

    local hr:HRESULT
    local rcClient:RECT

    mov hr,S_OK
    mov rsi,rcx
    mov rbx,rdx

    ; Top and left of the client rectangle are both 0
    .if !GetClientRect([rsi].m_hWnd, &rcClient)

        mov hr,HRESULT_FROM_WIN32R(GetLastError())
    .endif

    .if (SUCCEEDED(hr))

        ; Calculate the area to display the image
        ; Center the image if the client rectangle is larger

        cvtsi2ss xmm1,[rsi].m_cxGifImagePixel
        cvtsi2ss xmm2,[rsi].m_cyGifImagePixel
        cvtsi2ss xmm0,rcClient.right
        subss xmm0,xmm1
        divss xmm0,2.0
        movss [rbx].left,xmm0
        cvtsi2ss xmm0,rcClient.bottom
        subss xmm0,xmm2
        divss xmm0,2.0
        movss [rbx].top,xmm0
        addss xmm1,[rbx].left
        movss [rbx].right,xmm1
        addss xmm0,xmm2
        movss [rbx].bottom,xmm0


        ; If the client area is resized to be smaller than the image size, scale
        ; the image, and preserve the aspect ratio

        cvtsi2ss xmm1,[rsi].m_cxGifImagePixel
        divss    xmm1,xmm2
        movss    xmm0,[rbx].left
        comiss   xmm0,0.0
        .ifb
            mov [rbx].left,0.0
            cvtsi2ss xmm0,rcClient.right
            movss [rbx].right,xmm0
            divss xmm0,xmm1
            cvtsi2ss xmm2,rcClient.bottom
            subss xmm2,xmm0
            divss xmm2,2.0
            movss [rbx].top,xmm2
            addss xmm2,xmm0
            movss [rbx].bottom,xmm2
        .endif

        movss xmm0,[rbx].top
        comiss xmm0,0.0
        .ifb
            cvtsi2ss xmm0,rcClient.bottom
            mov [rbx].top,0.0
            movss [rbx].bottom,xmm0
            mulss xmm0,xmm1
            cvtsi2ss xmm1,rcClient.right
            subss xmm1,xmm0
            divss xmm1,2.0
            movss [rbx].left,xmm1
            addss xmm0,xmm1
            movss [rbx].right,xmm0
        .endif
    .endif

    .return hr

DemoApp::CalculateDrawRectangle endp

    assume rbx:nothing

;
; DemoApp::RestoreSavedFrame()
;
; Copys the saved frame to the frame in the bitmap render
; target.
;

    assume rcx:ptr DemoApp

DemoApp::RestoreSavedFrame proc

  local hr:HRESULT
  local pFrameToCopyTo:ptr ID2D1Bitmap

    mov pFrameToCopyTo,NULL
    mov eax,E_FAIL
    .if [rcx].m_pSavedFrame
        this.m_pFrameComposeRT.GetBitmap(&pFrameToCopyTo)
    .endif
    .if eax == S_OK

        ;; Copy the whole bitmap
        mov rcx,this
        pFrameToCopyTo.CopyFromBitmap(NULL, [rcx].m_pSavedFrame, NULL)
    .endif
    mov hr,eax
    SafeRelease(pFrameToCopyTo)
    mov eax,hr
    ret

DemoApp::RestoreSavedFrame endp

;
; DemoApp::ClearCurrentFrameArea()
;
; Clears a rectangular area equal to the area overlaid by the
; current raw frame in the bitmap render target with background
; color.
;

DemoApp::ClearCurrentFrameArea proc uses rsi

  local pRT:ptr ID2D1BitmapRenderTarget

    mov rsi,rcx
    mov pRT,[rcx].m_pFrameComposeRT

    pRT.BeginDraw()

    ;; Clip the render target to the size of the raw frame
    pRT.PushAxisAlignedClip(&[rsi].m_framePosition, D2D1_ANTIALIAS_MODE_PER_PRIMITIVE)
    pRT.Clear(&[rsi].m_backgroundColor)

    ;; Remove the clipping
    pRT.PopAxisAlignedClip()
    pRT.EndDraw(NULL, NULL)
    ret

DemoApp::ClearCurrentFrameArea endp

;
; DemoApp::DisposeCurrentFrame()
;
; At the end of each delay, disposes the current frame
; based on the disposal method specified.
;

DemoApp::DisposeCurrentFrame proc

    local hr:HRESULT

    mov hr,S_OK
    .switch [rcx].m_uFrameDisposal
    .case DM_UNDEFINED
    .case DM_NONE
        ;; We simply draw on the previous frames. Do nothing here.
        .endc
    .case DM_BACKGROUND
        ;; Dispose background
        ;; Clear the area covered by the current raw frame with background color
        mov hr,this.ClearCurrentFrameArea()
        .endc
    .case DM_PREVIOUS
        ;; Dispose previous
        ;; We restore the previous composed frame first
        mov hr,this.RestoreSavedFrame()
        .endc
    .default
        ;; Invalid disposal method
        mov hr,E_FAIL
    .endsw
    .return hr

DemoApp::DisposeCurrentFrame endp

;
; DemoApp::OverlayNextFrame()
;
; Loads and draws the next raw frame into the composed frame
; render target. This is called after the current frame is
; disposed.
;

DemoApp::OverlayNextFrame proc uses rsi rbx

  local hr:HRESULT
  local pRT:ptr ID2D1BitmapRenderTarget

    mov rsi,rcx
    mov pRT,[rcx].m_pFrameComposeRT

    ;; Get Frame information

    mov hr,this.GetRawFrame([rsi].m_uNextFrameIndex)

    .if (SUCCEEDED(hr))

        ;; For disposal 3 method, we would want to save a copy of the current
        ;; composed frame

        .if [rsi].m_uFrameDisposal == DM_PREVIOUS

            mov hr,this.SaveComposedFrame()
        .endif
    .endif

    .if (SUCCEEDED(hr))

        ;; Start producing the next bitmap

        pRT.BeginDraw()

        ;; If starting a new animation loop
        .if [rsi].m_uNextFrameIndex == 0

            ;; Draw background and increase loop count

            pRT.Clear(&[rsi].m_backgroundColor)
            inc [rsi].m_uLoopNumber
        .endif

        ;; Produce the next frame

        pRT.DrawBitmap(
            [rsi].m_pRawFrame,
            &[rsi].m_framePosition,
            1.0,
            D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
            NULL)

        mov hr,pRT.EndDraw(NULL, NULL)
    .endif

    ;; To improve performance and avoid decoding/composing this frame in the
    ;; following animation loops, the composed frame can be cached here in system
    ;; or video memory.

    .if (SUCCEEDED(hr))

        ;; Increase the frame index by 1

        inc [rsi].m_uNextFrameIndex
        mov eax,[rsi].m_uNextFrameIndex
        cdq
        div [rsi].m_cFrames
        mov [rsi].m_uNextFrameIndex,edx
    .endif

    .return hr

DemoApp::OverlayNextFrame endp

    assume rcx:nothing
;;
;; DemoApp::SaveComposedFrame()
;;
;; Saves the current composed frame in the bitmap render target
;; into a temporary bitmap. Initializes the temporary bitmap if
;; needed.
;;

DemoApp::SaveComposedFrame proc uses rsi

  local hr:HRESULT
  local pFrameToBeSaved:ptr ID2D1Bitmap

    mov rsi,rcx

    mov pFrameToBeSaved,NULL
    mov hr,this.m_pFrameComposeRT.GetBitmap(&pFrameToBeSaved)

    .if (SUCCEEDED(hr))

        ;; Create the temporary bitmap if it hasn't been created yet

        .if [rsi].m_pSavedFrame == NULL

           .new bitmapSize:D2D1_SIZE_U
           .new bitmapProp:D2D1_BITMAP_PROPERTIES

            pFrameToBeSaved.GetPixelSize(&bitmapSize)
            pFrameToBeSaved.GetDpi(&bitmapProp.dpiX, &bitmapProp.dpiY)
            pFrameToBeSaved.GetPixelFormat(&bitmapProp.pixelFormat)
            mov hr,this.m_pFrameComposeRT.CreateBitmap(
                bitmapSize,
                NULL,
                0,
                &bitmapProp,
                &[rsi].m_pSavedFrame
                )
        .endif
    .endif

    .if (SUCCEEDED(hr))

        ; Copy the whole bitmap

        mov hr,this.m_pSavedFrame.CopyFromBitmap(NULL, pFrameToBeSaved, NULL)
    .endif

    SafeRelease(pFrameToBeSaved)
   .return hr

DemoApp::SaveComposedFrame endp

;
; DemoApp::SelectAndDisplayGif()
;
; Opens a dialog and displays a selected image.
;

DemoApp::SelectAndDisplayGif proc uses rsi

  local hr:HRESULT
  local szFileName[MAX_PATH]:WCHAR
  local rcClient:RECT
  local rcWindow:RECT

    mov hr,S_OK
    mov rsi,rcx

    rcClient.Clear()
    rcWindow.Clear()

    ;; If the user cancels selection, then nothing happens

    .if this.GetFileOpen(&szFileName, ARRAYSIZE(szFileName))

        ;; Reset the states

        mov [rsi].m_uNextFrameIndex,0
        mov [rsi].m_uFrameDisposal,DM_NONE ;; No previous frame, use disposal none
        mov [rsi].m_uLoopNumber,0
        mov [rsi].m_fHasLoop,FALSE

        SafeRelease([rsi].m_pSavedFrame)
        SafeRelease([rsi].m_pDecoder)

        ;; Create a decoder for the gif file

        mov hr,this.m_pIWICFactory.CreateDecoderFromFilename(
            &szFileName,
            NULL,
            GENERIC_READ,
            WICDecodeMetadataCacheOnLoad,
            &[rsi].m_pDecoder
            )

        .if (SUCCEEDED(hr))

            mov hr,this.GetGlobalMetadata()
        .endif

        .if (SUCCEEDED(hr))

            mov rcClient.right,[rsi].m_cxGifImagePixel
            mov rcClient.bottom,[rsi].m_cyGifImagePixel

            .if !AdjustWindowRect(&rcClient, WS_OVERLAPPEDWINDOW, TRUE)

                mov hr,HRESULT_FROM_WIN32R(GetLastError())
            .endif
        .endif

        .if (SUCCEEDED(hr))

            ;; Get the upper left corner of the current window

            .if !GetWindowRect([rsi].m_hWnd, &rcWindow)

                mov hr,HRESULT_FROM_WIN32R(GetLastError())
            .endif
        .endif

        .if (SUCCEEDED(hr))

            ;; Resize the window to fit the gif

            mov r9d,rcClient.right
            sub r9d,rcClient.left
            MoveWindow([rsi].m_hWnd, rcWindow.left, rcWindow.top, r9d, rcClient.Height(), TRUE)

            mov hr,this.CreateDeviceResources()
        .endif

        .if (SUCCEEDED(hr))

            ;; If we have at least one frame, start playing
            ;; the animation from the first frame

            .if [rsi].m_cFrames > 0

                mov hr,this.ComposeNextFrame()
                InvalidateRect([rsi].m_hWnd, NULL, FALSE)
            .endif
        .endif
    .endif

    .return hr

DemoApp::SelectAndDisplayGif endp

;;
;; DemoApp::ComposeNextFrame()
;;
;; Composes the next frame by first disposing the current frame
;; and then overlaying the next frame. More than one frame may
;; be processed in order to produce the next frame to be
;; displayed due to the use of zero delay intermediate frames.
;; Also, sets a timer that is equal to the delay of the frame.
;;

DemoApp::ComposeNextFrame proc uses rsi

  local hr:HRESULT

    mov rsi,rcx
    mov hr,S_OK

    ;; Check to see if the render targets are initialized

    .if [rsi].m_pHwndRT && [rsi].m_pFrameComposeRT

        ;; First, kill the timer since the delay is no longer valid
        KillTimer([rsi].m_hWnd, DELAY_TIMER_ID)

        ;; Compose one frame

        mov hr,this.DisposeCurrentFrame()
        .if (SUCCEEDED(hr))

            mov hr,this.OverlayNextFrame()
        .endif

        ;; Keep composing frames until we see a frame with delay greater than
        ;; 0 (0 delay frames are the invisible intermediate frames), or until
        ;; we have reached the very last frame.

        .while SUCCEEDED(hr) && [rsi].m_uFrameDelay == 0 && !this.IsLastFrame()

            mov hr,this.DisposeCurrentFrame()
            .if (SUCCEEDED(hr))

                mov hr,this.OverlayNextFrame()
            .endif
        .endw

        ;; If we have more frames to play, set the timer according to the delay.
        ;; Set the timer regardless of whether we succeeded in composing a frame
        ;; to try our best to continue displaying the animation.

        .if (!this.EndOfAnimation() && [rsi].m_cFrames > 1)

            ;; Set the timer according to the delay
            SetTimer([rsi].m_hWnd, DELAY_TIMER_ID, [rsi].m_uFrameDelay, NULL)
        .endif
    .endif

    .return hr

DemoApp::ComposeNextFrame endp

;;
;; DemoApp::RecoverDeviceResources
;;
;; Discards device-specific resources and recreates them.
;; Also starts the animation from the beginning.
;;

DemoApp::RecoverDeviceResources proc uses rsi

  local hr:HRESULT

    mov rsi,rcx
    SafeRelease([rsi].m_pHwndRT)
    SafeRelease([rsi].m_pFrameComposeRT)
    SafeRelease([rsi].m_pSavedFrame)

    mov [rsi].m_uNextFrameIndex,0
    mov [rsi].m_uFrameDisposal,DM_NONE ;; No previous frames. Use disposal none.
    mov [rsi].m_uLoopNumber,0

    mov hr,this.CreateDeviceResources()
    .if (SUCCEEDED(hr))

        .if [rsi].m_cFrames > 0

            ; Load the first frame
            mov hr,this.ComposeNextFrame()
            InvalidateRect([rsi].m_hWnd, NULL, FALSE)
        .endif
    .endif
    .return hr

DemoApp::RecoverDeviceResources endp

RCBEGIN

    RCTYPES 1
    RCENTRY RT_MENU
    RCENUMN 1
    RCENUMX IDR_WICANIMATEDGIF
    RCLANGX LANGID_US

    MENUBEGIN
      MENUNAME "&File", MF_END
        MENUITEM IDM_FILE, "&Open..."
        MENUITEM IDM_EXIT, "E&xit", MF_END
    MENUEND

RCEND

    end _tstart
