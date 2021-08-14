
include CApplication.inc

define _gridSize 100.0

.data

IID_ID2D1Factory        GUID {0x06152247,0x6f50,0x465a,{0x92,0x45,0x11,0x8b,0xfd,0x3b,0x60,0x07}}
IID_IDXGIDevice         GUID {0x54ec77fa,0x1377,0x44e6,{0x8c,0x32,0x88,0xfd,0x5f,0x44,0xc8,0x4c}}
IID_IDCompositionDevice GUID {0xC37EA93A,0xE7AA,0x450D,{0xB1,0x6F,0x97,0x46,0xCB,0x04,0x07,0xF3}}
IID_IDXGISurface        GUID {0xcafcb56c,0x6ac3,0x4889,{0xbf,0x47,0x9e,0x23,0xbb,0xd2,0x60,0xec}}

.code

;; Runs the application

CApplication::Run proc

    .new result:int_t = 0

    this.BeforeEnteringMessageLoop()

    .if (SUCCEEDED(eax))

        mov result,this.EnterMessageLoop()
    .else

        MessageBoxW(NULL, L"An error occuring when running the sample", NULL, MB_OK)
    .endif

    this.AfterLeavingMessageLoop()

    .return result

CApplication::Run endp


;; Creates the application window, the d3d device and DirectComposition device and visual tree
;; before entering the message loop.

CApplication::BeforeEnteringMessageLoop proc

    .new hr:HRESULT = this.CreateApplicationWindow()

    .if (SUCCEEDED(hr))

        mov hr,this.CreateD3D11Device()
    .endif

    .if (SUCCEEDED(hr))

        mov hr,this.CreateD2D1Factory()
    .endif

    .if (SUCCEEDED(hr))

        mov hr,this.CreateD2D1Device()
    .endif

    .if (SUCCEEDED(hr))

        mov hr,this.CreateDCompositionDevice()
    .endif

    .if (SUCCEEDED(hr))

        mov hr,this.CreateDCompositionVisualTree()
    .endif

    .return hr

CApplication::BeforeEnteringMessageLoop endp


;; Message loop

CApplication::EnterMessageLoop proc

    .new result:int_t = 0

    .if (this.ShowApplicationWindow())

        .new msg:MSG

        .while (GetMessage(&msg, NULL, 0, 0))

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        .endw

        mov result, msg.wParam
    .endif

    .return result;

CApplication::EnterMessageLoop endp


;; Destroys the application window, DirectComposition device and visual tree.

CApplication::AfterLeavingMessageLoop proc

    this.DestroyDCompositionVisualTree()
    this.DestroyDCompositionDevice()
    this.DestroyD2D1Device()
    this.DestroyD2D1Factory()
    this.DestroyD3D11Device()
    this.DestroyApplicationWindow()
    ret

CApplication::AfterLeavingMessageLoop endp


        assume rcx:ptr CApplication

;;---Code calling DirectComposition APIs------------------------------------------------------------


;; Creates D2D Factory

CApplication::CreateD2D1Factory proc

    .return D2D1CreateFactory(
            D2D1_FACTORY_TYPE_SINGLE_THREADED,
            &IID_ID2D1Factory,
            NULL,
            &[rcx]._d2d1Factory
            )

CApplication::CreateD2D1Factory endp


;; Creates D2D Device

CApplication::CreateD2D1Device proc

    .new hr:HRESULT = S_OK

    .if [rcx]._d3d11Device == NULL || [rcx]._d2d1Factory == NULL
        mov hr,E_UNEXPECTED
    .endif

    .new dxgiDevice:ptr IDXGIDevice

    .if (SUCCEEDED(hr))

        mov hr,this._d3d11Device.QueryInterface(&IID_IDXGIDevice, &dxgiDevice)
    .endif

    .if (SUCCEEDED(hr))

        mov rcx,this
        mov hr,this._d2d1Factory.CreateDevice(dxgiDevice, &[rcx]._d2d1Device)
    .endif

    .if (SUCCEEDED(hr))

        mov rcx,this
        mov hr,this._d2d1Device.CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, &[rcx]._d2d1DeviceContext)
    .endif

    .return hr

CApplication::CreateD2D1Device endp


;; Creates D3D device

CApplication::CreateD3D11Device proc uses rbx

    .new hr:HRESULT = S_OK
    .new driverTypes[2]:D3D_DRIVER_TYPE = { D3D_DRIVER_TYPE_HARDWARE, D3D_DRIVER_TYPE_WARP }
    .new featureLevelSupported:D3D_FEATURE_LEVEL

    .for (ebx = 0: ebx < sizeof(driverTypes) / sizeof(D3D_DRIVER_TYPE): ++ebx)

        .new d3d11Device:ptr ID3D11Device
        .new d3d11DeviceContext:ptr ID3D11DeviceContext

        mov edx,driverTypes[rbx*4]
        mov hr,D3D11CreateDevice(
            NULL,
            edx,
            NULL,
            D3D11_CREATE_DEVICE_BGRA_SUPPORT,
            NULL,
            0,
            D3D11_SDK_VERSION,
            &d3d11Device,
            &featureLevelSupported,
            &d3d11DeviceContext)

        .if (SUCCEEDED(hr))

            mov rcx,this
            mov [rcx]._d3d11Device,d3d11Device
            mov [rcx]._d3d11DeviceContext,d3d11DeviceContext
            .break
        .endif
    .endf

    .return hr

CApplication::CreateD3D11Device endp


;; Initializes DirectComposition

CApplication::CreateDCompositionDevice proc

    .new hr:HRESULT = S_OK

    .if ([rcx]._d3d11Device == NULL)
        mov hr,E_UNEXPECTED
    .endif

    .new dxgiDevice:ptr IDXGIDevice

    .if (SUCCEEDED(hr))

        mov hr,this._d3d11Device.QueryInterface(&IID_IDXGIDevice, &dxgiDevice)
    .endif

    .if (SUCCEEDED(hr))

        mov rcx,this
        mov hr,DCompositionCreateDevice(dxgiDevice, &IID_IDCompositionDevice, &[rcx]._device)
    .endif

    .return hr

CApplication::CreateDCompositionDevice endp


;; Creates DirectComposition visual tree

    assume rdi:ptr CApplication

CApplication::CreateDCompositionVisualTree proc uses rsi rdi rbx

    .new hr:HRESULT = S_OK

    .if (([rcx]._device == NULL) || ([rcx]._hwnd == NULL))
        mov hr,E_UNEXPECTED
    .endif

    mov rdi,rcx
    .if (SUCCEEDED(hr))

        mov hr,this._device.CreateVisual(&[rcx]._visual)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,this._device.CreateVisual(&[rdi]._visualLeft)
    .endif

    .new surfaceLeft:ptr IDCompositionSurface

    .if (SUCCEEDED(hr))

        mov hr,[rdi].CreateSurface([rdi]._tileSize, 1.0, 0.0, 0.0, &surfaceLeft)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,this._visualLeft.SetContent(surfaceLeft)
    .endif

    .for (ebx = 0: ebx < 4 && SUCCEEDED(hr): ++ebx)

        .if (SUCCEEDED(hr))

            mov hr,this._device.CreateVisual(&[rdi]._visualLeftChild[rbx*8])
        .endif

        .if (SUCCEEDED(hr))

            lea rcx,[rdi]._surfaceLeftChild[rbx*8]
            mov edx,[rdi]._tileSize
            .switch pascal rbx
            .case 0: [rdi].CreateSurface(edx, 0.0, 1.0, 0.0, rcx)
            .case 1: [rdi].CreateSurface(edx, 0.5, 0.0, 0.5, rcx)
            .case 2: [rdi].CreateSurface(edx, 0.5, 0.5, 0.0, rcx)
            .case 3: [rdi].CreateSurface(edx, 0.0, 0.0, 1.0, rcx)
            .endsw
            mov hr,eax
        .endif

        .if (SUCCEEDED(hr))

            mov rsi,[rdi]._visualLeftChild[rbx*8]
            mov hr,[rsi].IDCompositionVisual.SetContent([rdi]._surfaceLeftChild[rbx*8])
        .endif
    .endf

    .if (SUCCEEDED(hr))

        mov hr,this._device.CreateVisual(&[rdi]._visualRight)
    .endif

    .if (SUCCEEDED(hr))

        mov eax,[rdi]._currentVisual
        mov hr,this._visualRight.SetContent([rdi]._surfaceLeftChild[rax*8])
    .endif

    .if (SUCCEEDED(hr))

        mov hr,this._visual.AddVisual([rdi]._visualLeft, TRUE, NULL)
    .endif

    .if (SUCCEEDED(hr))

        .for (ebx = 0: ebx < 4 && SUCCEEDED(hr): ++ebx)

            mov hr,this._visualLeft.AddVisual([rdi]._visualLeftChild[rbx*8], FALSE, NULL)
        .endf
    .endif

    .if (SUCCEEDED(hr))

        mov hr,this._visual.AddVisual([rdi]._visualRight, TRUE, [rdi]._visualLeft)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,this.SetEffectOnVisuals()
    .endif

    .if (SUCCEEDED(hr))

        mov hr,this._device.CreateTargetForHwnd([rdi]._hwnd, TRUE, &[rdi]._target)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,this._target.SetRoot([rdi]._visual)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,this._device.Commit()
    .endif

    .return hr

CApplication::CreateDCompositionVisualTree endp


;; Creates surface

CApplication::CreateSurface proc size:int_t, red:float, green:float, blue:float, surface:ptr ptr IDCompositionSurface

    xor eax,eax

    .new hr:HRESULT = eax

    .if (surface == rax)
        mov hr,E_POINTER
    .endif

    .if (SUCCEEDED(hr))

        .if (([rcx]._device == rax) || ([rcx]._d2d1Factory == rax) || ([rcx]._d2d1DeviceContext == rax))
            mov hr,E_UNEXPECTED
        .endif

        mov rdx,surface
        mov [rdx],rax
    .endif

    .new surfaceTile:ptr IDCompositionSurface

    .if (SUCCEEDED(hr))

        mov hr,this._device.CreateSurface(size, size, DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ALPHA_MODE_IGNORE, &surfaceTile)
    .endif

    .new dxgiSurface:ptr IDXGISurface
    .new offs:POINT

    .if (SUCCEEDED(hr))

        .new rect:RECT = { 0, 0, size, size }

        mov hr,surfaceTile.BeginDraw(&rect, &IID_IDXGISurface, &dxgiSurface, &offs)
    .endif

    .new d2d1Bitmap:ptr ID2D1Bitmap1

    .if (SUCCEEDED(hr))

        .new dpiX:FLOAT = 0.0
        .new dpiY:FLOAT = 0.0

        this._d2d1Factory.GetDesktopDpi(&dpiX, &dpiY)

        .new bitmapProperties:D2D1_BITMAP_PROPERTIES1 = {
                { DXGI_FORMAT_R8G8B8A8_UNORM, D2D1_ALPHA_MODE_IGNORE },
                dpiX,
                dpiY,
                D2D1_BITMAP_OPTIONS_TARGET or D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
                NULL
            }

        mov hr,this._d2d1DeviceContext.CreateBitmapFromDxgiSurface(dxgiSurface, &bitmapProperties, &d2d1Bitmap)

        .if (SUCCEEDED(hr))

            this._d2d1DeviceContext.SetTarget(d2d1Bitmap)
        .endif

        .new d2d1Brush:ptr ID2D1SolidColorBrush

        .if (SUCCEEDED(hr))

            .new Color:D3DCOLORVALUE = { red, green, blue, 1.0 }

            mov hr,this._d2d1DeviceContext.CreateSolidColorBrush(&Color, NULL, &d2d1Brush)
        .endif

        .if (SUCCEEDED(hr))

            this._d2d1DeviceContext.BeginDraw()

            .new rc:D2D1_RECT_F

            cvtsi2ss xmm0,offs.x
            cvtsi2ss xmm1,offs.y
            cvtsi2ss xmm2,size
            movss rc.left,xmm0
            movss rc.top,xmm1
            addss xmm0,xmm2
            movss rc.right,xmm0
            addss xmm1,xmm2
            movss rc.bottom,xmm1

            this._d2d1DeviceContext.FillRectangle(&rc, d2d1Brush)
            mov hr,this._d2d1DeviceContext.EndDraw(NULL, NULL)
        .endif

        surfaceTile.EndDraw()
    .endif

    .if (SUCCEEDED(hr))

        mov rdx,surface
        mov rax,surfaceTile
        mov [rdx],rax
    .endif

    .return hr

CApplication::CreateSurface endp


;; Sets effects on both the left and the right visuals.

CApplication::SetEffectOnVisuals proc

    .new hr:HRESULT = this.SetEffectOnVisualLeft()

    .if (SUCCEEDED(hr))

        mov hr,this.SetEffectOnVisualLeftChildren()
    .endif

    .if (SUCCEEDED(hr))

        mov hr,this.SetEffectOnVisualRight()
    .endif

    .return hr;

CApplication::SetEffectOnVisuals endp


;; Sets effect on the left visual.

CApplication::SetEffectOnVisualLeft proc uses rdi

    .new hr:HRESULT = S_OK
    .new beginOffsetX:float = 0.5
    .new endOffsetX:float = 3.0
    .new offsetY:float = 1.5
    .new beginAngle:float = 30.0
    .new endAngle:float = 0.0
    .new translateTransform:ptr IDCompositionTranslateTransform3D

    mov rdi,rcx
    .if ([rcx]._actionType == ZOOMOUT)

        mov beginOffsetX,3.0
        mov endOffsetX,0.5
        mov beginAngle,0.0
        mov endAngle,30.0
    .endif

    .if ([rcx]._visualLeft == NULL)
        mov hr,E_UNEXPECTED
    .endif

    .if (SUCCEEDED(hr))

        movss xmm5,_gridSize
        movss xmm1,beginOffsetX
        mulss xmm1,xmm5
        movss xmm2,offsetY
        mulss xmm2,xmm5
        movss xmm3,endOffsetX
        mulss xmm3,xmm5
        mov hr,this.CreateTranslateTransform2(xmm1, xmm2, 0.0, xmm3, xmm2, 0.0, 0.25, 1.25, &translateTransform)
    .endif

    .new rotateTransform:ptr IDCompositionRotateTransform3D

    .if (SUCCEEDED(hr))

        movss xmm3,_gridSize
        movss xmm1,xmm3
        movss xmm2,xmm3
        mulss xmm1,3.5
        mulss xmm2,1.5
        mulss xmm3,0.0

        mov hr,this.CreateRotateTransform2(xmm1, xmm2, xmm3, 0.0, 1.0, 0.0, beginAngle,
                endAngle, 0.25, 1.25, &rotateTransform)
    .endif

    .new perspectiveTransform:ptr IDCompositionMatrixTransform3D

    .if (SUCCEEDED(hr))

        movss xmm0,_gridSize
        movss xmm3,-1.0
        mulss xmm0,9.0
        divss xmm3,xmm0

        mov hr,this.CreatePerspectiveTransform(0.0, 0.0, xmm3, &perspectiveTransform)
    .endif

    .new transforms[3]:ptr IDCompositionTransform3D = {
        translateTransform, rotateTransform, perspectiveTransform
        }
    .new transformGroup:ptr IDCompositionTransform3D

    .if (SUCCEEDED(hr))

        mov hr,this._device.CreateTransform3DGroup(&transforms, 3, &transformGroup)
    .endif

    .if (SUCCEEDED(hr))

        mov [rdi]._effectGroupLeft,NULL
        mov hr,this._device.CreateEffectGroup(&[rdi]._effectGroupLeft)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,this._effectGroupLeft.SetTransform3D(transformGroup)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,this._visualLeft.SetEffect([rdi]._effectGroupLeft)
    .endif

    .return hr

CApplication::SetEffectOnVisualLeft endp


CApplication::SetEffectOnVisualLeftChildren proc uses rsi rdi rbx

    .new hr:HRESULT = S_OK

    mov rdi,rcx
    .for (ebx = 0: ebx < 4 && SUCCEEDED(hr): ++ebx)

        .new r:int_t
        .new c:int_t

        xor edx,edx
        mov eax,ebx
        mov ecx,2
        div ecx
        mov r,eax
        mov c,edx

        .new scale:ptr IDCompositionScaleTransform3D

        .if (SUCCEEDED(hr))

            mov hr,this.CreateScaleTransform(0.0, 0.0, 0.0, 1.0 / 3.0, 1.0 / 3.0, 1.0, &scale)
        .endif

        .new translate:ptr IDCompositionTranslateTransform3D

        .if (SUCCEEDED(hr))

            movss xmm0,_gridSize
            cvtsi2ss xmm1,c
            cvtsi2ss xmm2,r

            mulss xmm1,1.5
            mulss xmm2,1.5
            addss xmm1,0.25
            addss xmm2,0.25
            mulss xmm1,xmm0
            mulss xmm2,xmm0
            mov hr,this.CreateTranslateTransform(xmm1, xmm2, 0.0, &translate)
        .endif

        .new transforms[2]:ptr IDCompositionTransform3D = { scale, translate }
        .new transformGroup:ptr IDCompositionTransform3D

        .if (SUCCEEDED(hr))

            mov hr,this._device.CreateTransform3DGroup(&transforms, 2, &transformGroup)
        .endif

        .if (SUCCEEDED(hr))

            mov [rdi]._effectGroupLeftChild[rbx*8],NULL
            mov hr,this._device.CreateEffectGroup(&[rdi]._effectGroupLeftChild[rbx*8])
        .endif

        .if (SUCCEEDED(hr))

            mov rsi,[rdi]._effectGroupLeftChild[rbx*8]
            mov hr,[rsi].IDCompositionEffectGroup.SetTransform3D(transformGroup)
        .endif

        .if (SUCCEEDED(hr) && ebx == [rdi]._currentVisual)

            .new opacityAnimation:ptr IDCompositionAnimation

            .new beginOpacity:float = 1.0
            .new endOpacity:float = 0.0

            .if [rdi]._actionType == ZOOMOUT

                mov beginOpacity,0.0
                mov endOpacity,1.0
            .endif

            mov hr,this.CreateLinearAnimation(beginOpacity, endOpacity, 0.25, 1.25, &opacityAnimation)

            .if (SUCCEEDED(hr))

                mov hr,[rsi].IDCompositionEffectGroup.SetOpacity?p(opacityAnimation)
            .endif
        .endif

        .if (SUCCEEDED(hr))

            mov r8,[rdi]._visualLeftChild[rbx*8]
            mov hr,[r8].IDCompositionVisual.SetEffect(rsi)
        .endif
    .endf

    .return hr

CApplication::SetEffectOnVisualLeftChildren endp


;; Sets effect on the right visual

CApplication::SetEffectOnVisualRight proc uses rdi

    .new hr:HRESULT = S_OK
    .new beginOffsetX:float = 3.75
    .new endOffsetX:float = 6.5
    .new offsetY:float = 1.5

    .new translateTransform:ptr IDCompositionTranslateTransform3D

    .if ([rcx]._actionType == ZOOMOUT)

        mov beginOffsetX,6.5
        mov endOffsetX,3.75
    .endif

    mov rdi,rcx
    .if ([rcx]._visualRight == NULL)
        mov hr,E_UNEXPECTED
    .endif

    .if (SUCCEEDED(hr))

        movss xmm0,_gridSize
        movss xmm1,beginOffsetX
        movss xmm2,offsetY
        movss xmm3,endOffsetX
        mulss xmm1,xmm0
        mulss xmm2,xmm0
        mulss xmm3,xmm0

        mov hr,this.CreateTranslateTransform2(xmm1, xmm2, 0.0, xmm3, xmm2, 0.0, 0.25, 1.25, &translateTransform)
    .endif

    .new transforms:ptr IDCompositionTransform3D = translateTransform

    .new transformGroup:ptr IDCompositionTransform3D

    .if (SUCCEEDED(hr))

        mov hr,this._device.CreateTransform3DGroup(&transforms, 1, &transformGroup)
    .endif

    .if (SUCCEEDED(hr))

        mov [rdi]._effectGroupRight,NULL
        mov hr,this._device.CreateEffectGroup(&[rdi]._effectGroupRight)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,this._effectGroupRight.SetTransform3D(transformGroup)
    .endif

    .if (SUCCEEDED(hr))

        .new opacityAnimation:ptr IDCompositionAnimation

        .new beginOpacity:float = 1.0
        .new endOpacity:float = 0.0

        .if ([rdi]._actionType == ZOOMOUT)

            mov beginOpacity,0.0
            mov endOpacity,1.0
        .endif

        mov hr,this.CreateLinearAnimation(beginOpacity, endOpacity, 0.25, 1.25, &opacityAnimation)

        .if (SUCCEEDED(hr))

            mov hr,this._effectGroupRight.SetOpacity?p(opacityAnimation)
        .endif
    .endif

    .if (SUCCEEDED(hr))

        mov hr,this._visualRight.SetEffect([rdi]._effectGroupRight)
    .endif

    .return hr

CApplication::SetEffectOnVisualRight endp


;; Creates Translate transform without animation

CApplication::CreateTranslateTransform proc offsetX:float, offsetY:float,
        offsetZ:float, translateTransform:ptr ptr IDCompositionTranslateTransform3D

    .new hr:HRESULT = S_OK

    .if (translateTransform == NULL)
        mov hr,E_POINTER
    .endif

    .if (SUCCEEDED(hr))

        xor eax,eax
        mov rdx,translateTransform
        mov [rdx],rax
        .if [rcx]._device == NULL
            mov hr,E_UNEXPECTED
        .endif
    .endif

    .new transform:ptr IDCompositionTranslateTransform3D

    .if (SUCCEEDED(hr))

        mov hr,this._device.CreateTranslateTransform3D(&transform)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,transform.SetOffsetX?r(offsetX)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,transform.SetOffsetY?r(offsetY)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,transform.SetOffsetZ?r(offsetZ)
    .endif

    .if (SUCCEEDED(hr))

        mov rdx,translateTransform
        mov rax,transform
        mov [rdx],rax
    .endif

    .return hr

CApplication::CreateTranslateTransform endp


;; Creates Translate transform with animation

CApplication::CreateTranslateTransform2 proc beginOffsetX:float, beginOffsetY:float,
        beginOffsetZ:float, endOffsetX:float, endOffsetY:float, endOffsetZ:float,
        beginTime:float, endTime:float, translateTransform:ptr ptr IDCompositionTranslateTransform3D

    .new hr:HRESULT = S_OK

    mov rdx,translateTransform
    .if (rdx == NULL)
        mov hr,E_POINTER
    .endif

    .if (SUCCEEDED(hr))

        xor eax,eax
        mov [rdx],rax
        .if ([rcx]._device == rax)
            mov hr,E_UNEXPECTED
        .endif
    .endif

    .new transform:ptr IDCompositionTranslateTransform3D

    .if (SUCCEEDED(hr))

        mov hr,this._device.CreateTranslateTransform3D(&transform)
    .endif

    .new offsetXAnimation:ptr IDCompositionAnimation

    .if (SUCCEEDED(hr))

        mov hr,this.CreateLinearAnimation(beginOffsetX, endOffsetX, beginTime, endTime, &offsetXAnimation)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,transform.SetOffsetX?p(offsetXAnimation)
    .endif

    .new offsetYAnimation:ptr IDCompositionAnimation

    .if (SUCCEEDED(hr))

        mov hr,this.CreateLinearAnimation(beginOffsetY, endOffsetY, beginTime, endTime, &offsetYAnimation)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,transform.SetOffsetY?p(offsetYAnimation)
    .endif

    .new offsetZAnimation:ptr IDCompositionAnimation

    .if (SUCCEEDED(hr))

        mov hr,this.CreateLinearAnimation(beginOffsetZ, endOffsetZ, beginTime, endTime, &offsetZAnimation)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,transform.SetOffsetZ?p(offsetZAnimation)
    .endif

    .if (SUCCEEDED(hr))

        mov rdx,translateTransform
        mov rax,transform
        mov [rdx],rax
    .endif

    .return hr

CApplication::CreateTranslateTransform2 endp


;; Creates scale transform without animation

CApplication::CreateScaleTransform proc centerX:float, centerY:float, centerZ:float,
        scaleX:float, scaleY:float, scaleZ:float,
        scaleTransform:ptr ptr IDCompositionScaleTransform3D

    .new hr:HRESULT = S_OK

    mov rdx,scaleTransform
    .if (rdx == NULL)
        mov hr,E_POINTER
    .endif

    .if (SUCCEEDED(hr))

        xor eax,eax
        mov [rdx],rax
        .if ([rcx]._device == rax)
            mov hr,E_UNEXPECTED
        .endif
    .endif

    .new transform:ptr IDCompositionScaleTransform3D

    .if (SUCCEEDED(hr))

        mov hr,this._device.CreateScaleTransform3D(&transform)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,transform.SetCenterX?r(centerX)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,transform.SetCenterY?r(centerY)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,transform.SetCenterZ?r(centerZ)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,transform.SetScaleX?r(scaleX)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,transform.SetScaleY?r(scaleY)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,transform.SetScaleZ?r(scaleZ)
    .endif

    .if (SUCCEEDED(hr))

        mov rdx,scaleTransform
        mov rax,transform
        mov [rdx],rax
    .endif

    .return hr

CApplication::CreateScaleTransform endp


;; Creates scale transform with animation

CApplication::CreateScaleTransform2 proc centerX:float, centerY:float, centerZ:float,
        beginScaleX:float, beginScaleY:float, beginScaleZ:float, endScaleX:float,
        endScaleY:float, endScaleZ:float, beginTime:float, endTime:float,
        scaleTransform:ptr ptr IDCompositionScaleTransform3D

    .new hr:HRESULT = S_OK

    mov rdx,scaleTransform
    .if (rdx == NULL)
        mov hr,E_POINTER
    .endif

    .if (SUCCEEDED(hr))

        xor eax,eax
        mov [rdx],rax
        .if ([rcx]._device == rax)
            mov hr,E_UNEXPECTED
        .endif
    .endif

    .new transform:ptr IDCompositionScaleTransform3D

    .if (SUCCEEDED(hr))

        mov hr,this._device.CreateScaleTransform3D(&transform)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,transform.SetCenterX?r(centerX)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,transform.SetCenterY?r(centerY)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,transform.SetCenterZ?r(centerZ)
    .endif

    .new scaleXAnimation:ptr IDCompositionAnimation

    .if (SUCCEEDED(hr))

        mov hr,this.CreateLinearAnimation(beginScaleX, endScaleX, beginTime, endTime, &scaleXAnimation)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,transform.SetScaleX?p(scaleXAnimation)
    .endif

    .new scaleYAnimation:ptr IDCompositionAnimation

    .if (SUCCEEDED(hr))

        mov hr,this.CreateLinearAnimation(beginScaleY, endScaleY, beginTime, endTime, &scaleYAnimation)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,transform.SetScaleY?p(scaleYAnimation)
    .endif

    .new scaleZAnimation:ptr IDCompositionAnimation

    .if (SUCCEEDED(hr))

        mov hr,this.CreateLinearAnimation(beginScaleZ, endScaleZ, beginTime, endTime, &scaleZAnimation)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,transform.SetScaleZ?p(scaleZAnimation)
    .endif

    .if (SUCCEEDED(hr))

        mov rdx,scaleTransform
        mov rax,transform
        mov [rdx],rax
    .endif

    .return hr

CApplication::CreateScaleTransform2 endp


;; Creates rotate transform without animation

CApplication::CreateRotateTransform proc centerX:float, centerY:float, centerZ:float,
        axisX:float, axisY:float, axisZ:float, angle:float,
        rotateTransform:ptr ptr IDCompositionRotateTransform3D

    .new hr:HRESULT = S_OK

    mov rdx,rotateTransform
    .if (rdx == NULL)
        mov hr,E_POINTER
    .endif

    .if (SUCCEEDED(hr))

        xor eax,eax
        mov [rdx],rax
        .if ([rcx]._device == rax)
            mov hr,E_UNEXPECTED
        .endif
    .endif

    .new transform:ptr IDCompositionRotateTransform3D

    .if (SUCCEEDED(hr))

        mov hr,this._device.CreateRotateTransform3D(&transform)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,transform.SetCenterX?r(centerX)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,transform.SetCenterY?r(centerY)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,transform.SetCenterZ?r(centerZ)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,transform.SetAxisX?r(axisX)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,transform.SetAxisY?r(axisY)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,transform.SetAxisZ?r(axisZ)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,transform.SetAngle?r(angle)
    .endif

    .if (SUCCEEDED(hr))

        mov rdx,rotateTransform
        mov rax,transform
        mov [rdx],rax
    .endif

    .return hr

CApplication::CreateRotateTransform endp


;; Creates rotate transform with animation

CApplication::CreateRotateTransform2 proc centerX:float, centerY:float, centerZ:float,
        axisX:float, axisY:float, axisZ:float, beginAngle:float, endAngle:float,
        beginTime:float, endTime:float, rotateTransform:ptr ptr IDCompositionRotateTransform3D

    .new hr:HRESULT = S_OK

    mov rdx,rotateTransform
    .if (rdx == NULL)
        mov hr,E_POINTER
    .endif

    .if (SUCCEEDED(hr))

        xor eax,eax
        mov [rdx],rax
        .if ([rcx]._device == NULL)
            mov hr,E_UNEXPECTED
        .endif
    .endif

    .new transform:ptr IDCompositionRotateTransform3D

    .if (SUCCEEDED(hr))

        mov hr,this._device.CreateRotateTransform3D(&transform)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,transform.SetCenterX?r(centerX)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,transform.SetCenterY?r(centerY)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,transform.SetCenterZ?r(centerZ)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,transform.SetAxisX?r(axisX)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,transform.SetAxisY?r(axisY)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,transform.SetAxisZ?r(axisZ)
    .endif

    .new angleAnimation:ptr IDCompositionAnimation

    .if (SUCCEEDED(hr))

        mov hr,this.CreateLinearAnimation(beginAngle, endAngle, beginTime, endTime, &angleAnimation)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,transform.SetAngle?p(angleAnimation)
    .endif

    .if (SUCCEEDED(hr))

        mov rdx,rotateTransform
        mov rax,transform
        mov [rdx],rax
    .endif

    .return hr

CApplication::CreateRotateTransform2 endp


CApplication::CreateLinearAnimation proc beginValue:float, endValue:float, beginTime:float,
        endTime:float, linearAnimation:ptr ptr IDCompositionAnimation

    .new hr:HRESULT = S_OK

    mov rdx,linearAnimation
    .if (rdx == NULL)
        mov hr,E_POINTER
    .endif

    .if (SUCCEEDED(hr))

        xor eax,eax
        mov [rdx],rax
        .if ([rcx]._device == NULL)
            mov hr,E_UNEXPECTED
        .endif
    .endif

    .new animation:ptr IDCompositionAnimation

    .if (SUCCEEDED(hr))

        mov hr,this._device.CreateAnimation(&animation)
    .endif

    ;; Ensures animation start value takes effect immediately

    .if (SUCCEEDED(hr))

        movss  xmm0,beginTime
        comiss xmm0,0.0
        .ifa
            mov hr,animation.AddCubic(0.0, beginValue, 0.0, 0.0, 0.0)
        .endif
    .endif

    .if (SUCCEEDED(hr))

        movss xmm3,endValue
        subss xmm3,beginValue
        movss xmm0,endTime
        movss xmm1,beginTime
        subss xmm0,xmm1
        divss xmm3,xmm0
        cvtss2sd xmm1,xmm1
        mov hr,animation.AddCubic(xmm1, beginValue, xmm3, 0.0, 0.0)
    .endif

    .if (SUCCEEDED(hr))

        movss xmm1,endTime
        cvtss2sd xmm1,xmm1
        mov hr,animation._End(xmm1, endValue)
    .endif

    .if (SUCCEEDED(hr))

        mov rdx,linearAnimation
        mov rax,animation
        mov [rdx],rax
    .endif

    .return hr

CApplication::CreateLinearAnimation endp


;; Creates perspective transform

CApplication::CreatePerspectiveTransform proc x:float, y:float, z:float,
        perspectiveTransform:ptr ptr IDCompositionMatrixTransform3D

    .new hr:HRESULT = S_OK

    mov rdx,perspectiveTransform
    .if (rdx == NULL)
        mov hr,E_POINTER
    .endif

    .if (SUCCEEDED(hr))

        xor eax,eax
        mov [rdx],rax
    .endif

    .new matrix:D3DMATRIX = {{{
        1.0, 0.0, 0.0, x,
        0.0, 1.0, 0.0, y,
        0.0, 0.0, 1.0, z,
        0.0, 0.0, 0.0, 1.0
        }}}

    .new transform:ptr IDCompositionMatrixTransform3D

    .if (SUCCEEDED(hr))

        mov hr,this._device.CreateMatrixTransform3D(&transform)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,transform.SetMatrix(&matrix)
    .endif

    .if (SUCCEEDED(hr))

        mov rdx,perspectiveTransform
        mov rax,transform
        mov [rdx],rax
    .endif

    .return hr

CApplication::CreatePerspectiveTransform endp


;; The child visual associated with the pressed key disappears and the previously disappeared one appears again.

CApplication::UpdateVisuals proc currentVisual:int_t, nextVisual:int_t

    .new hr:HRESULT = this._visualRight.SetContent([rcx]._surfaceLeftChild[r8*8])

    .if (SUCCEEDED(hr))

        mov rcx,this
        mov eax,currentVisual
        mov r8,[rcx]._effectGroupLeftChild[rax*8]
        mov hr,[r8].IDCompositionEffectGroup.SetOpacity?r(1.0)
    .endif

    .if (SUCCEEDED(hr))

        mov rcx,this
        mov eax,nextVisual
        mov r8,[rcx]._effectGroupLeftChild[rax*8]
        mov hr,[r8].IDCompositionEffectGroup.SetOpacity?r(0.0)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,this._device.Commit()
    .endif

    mov eax,1
    .if SUCCEEDED(hr)
        xor eax,eax
    .endif
    ret

CApplication::UpdateVisuals endp


;; Destroys D2D Device

CApplication::DestroyD2D1Device proc

    xor eax,eax
    mov [rcx]._d2d1DeviceContext,rax
    mov [rcx]._d2d1Device,rax
    ret

CApplication::DestroyD2D1Device endp


;; Destroys D3D device

CApplication::DestroyD3D11Device proc

    xor eax,eax
    mov [rcx]._d3d11DeviceContext,rax
    mov [rcx]._d3d11Device,rax
    ret

CApplication::DestroyD3D11Device endp


;; Destroy D2D Factory

CApplication::DestroyD2D1Factory proc

    xor eax,eax
    mov [rcx]._d2d1Factory,rax
    ret

CApplication::DestroyD2D1Factory endp


;; Destroys DirectComposition Visual tree

CApplication::DestroyDCompositionVisualTree proc

    .for (eax = 0, edx = 0: edx < 4: ++edx)
        mov [rcx]._effectGroupLeftChild[rdx*8],rax
        mov [rcx]._surfaceLeftChild[rdx*8],rax
        mov [rcx]._visualLeftChild[rdx*8],rax
    .endf
    mov [rcx]._effectGroupRight,rax
    mov [rcx]._effectGroupLeft,rax
    mov [rcx]._visualRight,rax
    mov [rcx]._visualLeft,rax
    mov [rcx]._visual,rax
    mov [rcx]._target,rax
    ret

CApplication::DestroyDCompositionVisualTree endp


;; Destroys DirectComposition device

CApplication::DestroyDCompositionDevice proc

    mov [rcx]._device,NULL
    ret

CApplication::DestroyDCompositionDevice endp


;;---End of code calling DirectComposition APIs-------------------------------------------------------


CApplication::Release proc

    ret

CApplication::Release endp


;; Provides the entry point to the application

CApplication::CApplication proc instance:HINSTANCE

    mov rcx,@ComAlloc(CApplication)
    mov [rcx]._hinstance,instance
    mov edx,100;_gridSize
    lea eax,[rdx+rdx*2]
    mov [rcx]._tileSize,eax
    lea eax,[rdx+rdx*8]
    mov [rcx]._windowWidth,eax
    lea eax,[rdx+rdx*4]
    add eax,edx
    mov [rcx]._windowHeight,eax
    mov [rcx]._state,ZOOMEDOUT
    mov [rcx]._actionType,ZOOMOUT
    mov rax,rcx
    ret

CApplication::CApplication endp


; Main Window procedure

WindowProc proc hwnd:HWND, msg:UINT, wParam:WPARAM, lParam:LPARAM

    .if ( edx == WM_CREATE )

        SetWindowLongPtr(rcx, GWLP_USERDATA, [r9].CREATESTRUCT.lpCreateParams)
        .return 1
    .endif

    .new app:ptr CApplication = GetWindowLongPtr(rcx, GWLP_USERDATA)
    .switch ( msg )
    .case WM_LBUTTONUP
        app.OnLeftButton()
        .endc
    .case WM_KEYDOWN
        app.OnKeyDown(wParam)
        .endc
    .case WM_CLOSE
        app.OnClose()
        .endc
    .case WM_DESTROY
        app.OnDestroy()
        .endc
    .case WM_PAINT
        app.OnPaint()
        .endc
    .case WM_CHAR
        .gotosw(WM_DESTROY) .if wParam == VK_ESCAPE
    .default
        DefWindowProc(hwnd, msg, wParam, lParam)
    .endsw
    ret

WindowProc endp


;; Creates the application window

CApplication::CreateApplicationWindow proc uses rdi

    mov rdi,rcx

    .new wc:WNDCLASSEX = {
        WNDCLASSEX,                     ; .cbSize
        CS_HREDRAW or CS_VREDRAW,       ; .style
        &WindowProc,                    ; .lpfnWndProc
        0,                              ; .cbClsExtra
        sizeof(LONG_PTR),               ; .cbWndExtra
        [rdi]._hinstance,               ; .hInstance
        NULL,                           ; .hIcon
        LoadCursor(NULL, IDC_ARROW),    ; .hCursor
        GetStockObject(BLACK_BRUSH),    ; .hbrBackground
        NULL,                           ; .lpszMenuName
        "MainWindowClass",              ; .lpszClassName
        NULL                            ; .hIconSm
        }

    .return E_FAIL .if ( RegisterClassEx( &wc ) == 0 )

    .new rect:RECT( 0, 0, [rdi]._windowWidth, [rdi]._windowHeight )

    AdjustWindowRect(&rect, WS_OVERLAPPED or WS_CAPTION or WS_SYSMENU or WS_MINIMIZEBOX, FALSE)

    mov eax,rect.right
    sub eax,rect.left
    mov [rdi]._windowWidth,eax

    mov eax,rect.bottom
    sub eax,rect.top
    mov [rdi]._windowHeight,eax

    .if CreateWindowEx(0, "MainWindowClass", "DirectComposition Effects Sample",
           WS_OVERLAPPED or WS_CAPTION or WS_SYSMENU or WS_MINIMIZEBOX,
           CW_USEDEFAULT, CW_USEDEFAULT,
           [rdi]._windowWidth, [rdi]._windowHeight,
           NULL, NULL, [rdi]._hinstance, rdi) == NULL

        .return E_UNEXPECTED
    .endif
    mov [rdi]._hwnd,rax

   .return S_OK

CApplication::CreateApplicationWindow endp


;; Shows the application window

CApplication::ShowApplicationWindow proc

    .new bSucceeded:BOOL = TRUE
    .if ([rcx]._hwnd == NULL)
        mov bSucceeded,FALSE
    .endif

    .if (bSucceeded)

        ShowWindow([rcx]._hwnd, SW_SHOW)
        mov rcx,this
        UpdateWindow([rcx]._hwnd)
    .endif

    .return bSucceeded

CApplication::ShowApplicationWindow endp


;; Destroys the applicaiton window

CApplication::DestroyApplicationWindow proc

    .if ([rcx]._hwnd != NULL)

        DestroyWindow([rcx]._hwnd)
        mov rcx,this
        mov [rcx]._hwnd,NULL
    .endif
    ret

CApplication::DestroyApplicationWindow endp


;; Zoom out to have all the picture on sight.

CApplication::ZoomOut proc

    .new hr:HRESULT = S_OK
    .if ([rcx]._state == ZOOMEDOUT)
        mov hr,E_UNEXPECTED
    .endif

    .if (SUCCEEDED(hr))

        mov [rcx]._actionType,ZOOMOUT
        mov hr,this.SetEffectOnVisuals()
    .endif

    .if (SUCCEEDED(hr))

        mov hr,this._device.Commit()
    .endif

    .if (SUCCEEDED(hr))

        mov rcx,this
        mov [rcx]._state,ZOOMEDOUT
    .endif

    .return hr

CApplication::ZoomOut endp


;; Zoom in to look more closely to the selected pictures

CApplication::ZoomIn proc

    .new hr:HRESULT = S_OK
    .if ([rcx]._state == ZOOMEDIN)
        mov hr,E_UNEXPECTED
    .endif

    .if (SUCCEEDED(hr))

        mov [rcx]._actionType,ZOOMIN
        mov hr,this.SetEffectOnVisuals()
    .endif

    .if (SUCCEEDED(hr))

        mov hr,this._device.Commit()
    .endif

    .if (SUCCEEDED(hr))

        mov rcx,this
        mov [rcx]._state,ZOOMEDIN
    .endif

    .return hr

CApplication::ZoomIn endp


;; Handles the WM_LBUTTONUP message

CApplication::OnLeftButton proc

    .new hr:HRESULT

    .if ([rcx]._state == ZOOMEDOUT)
        mov hr,this.ZoomIn()
    .else
        mov hr,this.ZoomOut()
    .endif

    mov eax,1
    .if SUCCEEDED(hr)
        xor eax,eax
    .endif
    ret

CApplication::OnLeftButton endp


;; Handles the WM_KEYDOWN message

CApplication::OnKeyDown proc wParam:WPARAM

    xor eax,eax

    .if ([rcx]._state == ZOOMEDOUT)

        mov r8d,edx
        mov edx,[rcx]._currentVisual

        .if (r8d == '1' && edx != 0)

            mov [rcx]._currentVisual,0
            [rcx].UpdateVisuals(edx, 0)

        .elseif (r8d == '2' && edx != 1)

            mov [rcx]._currentVisual,1
            [rcx].UpdateVisuals(edx, 1)

        .elseif (r8d == '3' && edx != 2)

            mov [rcx]._currentVisual,2
            [rcx].UpdateVisuals(edx, 2)

        .elseif (r8d == '4' && edx != 3)

            mov [rcx]._currentVisual,3
            [rcx].UpdateVisuals(edx, 3)
        .endif
    .endif
    ret

CApplication::OnKeyDown endp


;; Handles the WM_CLOSE message

CApplication::OnClose proc

    .if ([rcx]._hwnd != NULL)

        DestroyWindow([rcx]._hwnd)
        mov rcx,this
        mov [rcx]._hwnd,NULL
    .endif

    .return 0

CApplication::OnClose endp


;; Handles the WM_DESTROY message

CApplication::OnDestroy proc

    PostQuitMessage(0)

    .return 0

CApplication::OnDestroy endp


;; Handles the WM_PAINT message

CApplication::OnPaint proc uses rdi

    .new rcClient:RECT
    .new ps:PAINTSTRUCT

    mov rdi,rcx
    .new hdc:HDC = BeginPaint([rcx]._hwnd, &ps)

    ; get the dimensions of the main window.

    GetClientRect([rdi]._hwnd, &rcClient)

    ; Logo
    xor ecx,ecx
    .new hlogo:HFONT = CreateFontW(IDS_FONT_HEIGHT_LOGO, ecx, ecx, ecx, ecx, ecx, ecx,
            ecx, ecx, ecx, ecx, ecx, ecx, IDS_FONT_TYPEFACE) ; Logo Font and Size

    .if (hlogo != NULL)

       .new hOldFont:HFONT = SelectObject(hdc, hlogo)
        SetTextColor(hdc, GetSysColor(COLOR_GRAYTEXT))
        SetBkMode(hdc, TRANSPARENT)

        mov rcClient.top,10
        mov rcClient.left,50
        DrawTextW(hdc, "Windows samples", -1, &rcClient, DT_WORDBREAK)
        SelectObject(hdc, hOldFont)
        DeleteObject(hlogo)
    .endif

    ;; Title

    xor ecx,ecx
    .new htitle:HFONT = CreateFontW(IDS_FONT_HEIGHT_TITLE, ecx, ecx, ecx, ecx, ecx,
            ecx, ecx, ecx, ecx, ecx, ecx, ecx, IDS_FONT_TYPEFACE) ; Title Font and Size

    .if (htitle != NULL)

        .new hOldFont:HFONT = SelectObject(hdc, htitle)

        mov rcClient.top,25
        mov rcClient.left,50

        DrawTextW(hdc, "DirectComposition Effects Sample", -1, &rcClient, DT_WORDBREAK)
        SelectObject(hdc, hOldFont)
        DeleteObject(htitle)
    .endif

    ; Description
    .new hdescription:HFONT

    xor ecx,ecx
    mov hdescription,CreateFontW(IDS_FONT_HEIGHT_DESCRIPTION, ecx, ecx, ecx,
            ecx, ecx, ecx, ecx, ecx, ecx, ecx, ecx, ecx,
            IDS_FONT_TYPEFACE) ; Description Font and Size

    .if (hdescription != NULL)

        .new hOldFont:HFONT = SelectObject(hdc, hdescription)

        mov rcClient.top,90
        mov rcClient.left,50

        DrawTextW(hdc,
            L"This sample explains how to use DirectComposition effects: "
            "rotation, scaling, perspective, translation and opacity.",
            -1, &rcClient, DT_WORDBREAK)

        mov rcClient.top,500
        mov rcClient.left,450

        DrawTextW(hdc,
            L"A) Left-click to toggle between single and multiple-panels view.\nB)"
            " Use keys 1-4 to switch the color of the right-panel.", -1, &rcClient,
            DT_WORDBREAK)
        SelectObject(hdc, hOldFont)
        DeleteObject(hdescription)
    .endif
    EndPaint([rdi]._hwnd, &ps)
    .return 0

CApplication::OnPaint endp

wWinMain proc hInstance:HINSTANCE, hPrevInstance:HINSTANCE, pszCmdLine:LPWSTR, iCmdShow:int_t

    .new app:ptr CApplication(hInstance)
    .return app.Run()

wWinMain endp

    end _tstart
