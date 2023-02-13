
include OutputManager.inc

    .code

    assume rsi:ptr OUTPUTMANAGER

;
; Constructor NULLs out all pointers & sets appropriate var vals
;
OUTPUTMANAGER::OUTPUTMANAGER proc

    @ComAlloc(OUTPUTMANAGER)
    ret

OUTPUTMANAGER::OUTPUTMANAGER endp

;
; Destructor which calls CleanRefs to release all references and memory.
;
OUTPUTMANAGER::Release proc

    this.CleanRefs()
    free(this)
    ret

OUTPUTMANAGER::Release endp

OUTPUTMANAGER::InitGeometry proc
    ret
OUTPUTMANAGER::InitGeometry endp

;
; Indicates that window has been resized.
;
OUTPUTMANAGER::WindowResize proc

    mov [rcx].OUTPUTMANAGER.m_NeedsResize,true
    ret

OUTPUTMANAGER::WindowResize endp

;
; Initialize all state
;
OUTPUTMANAGER::InitOutput proc uses rsi rdi rbx Window:HWND, SingleOutput:SINT,
        OutCount:ptr UINT, DeskBounds:ptr RECT

    mov rsi,rcx

   .new hr:HRESULT

    ; Store window handle

    mov [rsi].m_WindowHandle,rdx ; Window

    ; Driver types supported

    .new DriverTypes[3]:D3D_DRIVER_TYPE = {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE,
        }
    .new NumDriverTypes:UINT = ARRAYSIZE(DriverTypes)

    ; Feature levels supported

    .new FeatureLevels[4]:D3D_FEATURE_LEVEL = {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
        D3D_FEATURE_LEVEL_9_1
        }
    .new NumFeatureLevels:UINT = ARRAYSIZE(FeatureLevels)
    .new FeatureLevel:D3D_FEATURE_LEVEL

    ; Create device

    .for ( ebx = 0: ebx < NumDriverTypes: ++ebx )

        mov hr,D3D11CreateDevice(nullptr, DriverTypes[rbx*4], nullptr, 0, &FeatureLevels,
                NumFeatureLevels, D3D11_SDK_VERSION, &[rsi].m_Device, &FeatureLevel,
                &[rsi].m_DeviceContext)

        .if (SUCCEEDED(hr))

            ; Device creation succeeded, no need to loop anymore

            .break
        .endif
    .endf

    .if (FAILED(hr))

        .return ProcessFailure([rsi].m_Device,
                L"Device creation in OUTPUTMANAGER failed",
                L"Error", hr, &SystemTransitionsExpectedErrors)
    .endif

    ; Get DXGI factory

   .new DxgiDevice:ptr IDXGIDevice = nullptr
    mov hr,this.m_Device.QueryInterface(&IID_IDXGIDevice, &DxgiDevice)
    .if (FAILED(hr))

        .return ProcessFailure(nullptr,
                L"Failed to QI for DXGI Device", L"Error", hr, nullptr)
    .endif

   .new DxgiAdapter:ptr IDXGIAdapter = nullptr
    mov hr,DxgiDevice.GetParent(&IID_IDXGIAdapter, &DxgiAdapter)
    DxgiDevice.Release()
    mov DxgiDevice,nullptr
    .if (FAILED(hr))

        .return ProcessFailure([rsi].m_Device,
                L"Failed to get parent DXGI Adapter",
                L"Error", hr, &SystemTransitionsExpectedErrors)
    .endif

    mov hr,DxgiAdapter.GetParent(&IID_IDXGIFactory2, &[rsi].m_Factory)
    DxgiAdapter.Release()
    mov DxgiAdapter,nullptr
    .if (FAILED(hr))

        .return ProcessFailure([rsi].m_Device,
                L"Failed to get parent DXGI Factory",
                L"Error", hr, &SystemTransitionsExpectedErrors)
    .endif

    ; Register for occlusion status windows message

    mov hr,this.m_Factory.RegisterOcclusionStatusWindow(
            Window, OCCLUSION_STATUS_MSG, &[rsi].m_OcclusionCookie)
    .if (FAILED(hr))

        .return ProcessFailure([rsi].m_Device,
                L"Failed to register for occlusion message",
                L"Error", hr, &SystemTransitionsExpectedErrors)
    .endif

    ; Get window size

   .new WindowRect:RECT
    GetClientRect([rsi].m_WindowHandle, &WindowRect)
    mov eax,WindowRect.right
    sub eax,WindowRect.left
    mov ecx,WindowRect.bottom
    sub ecx,WindowRect.top
   .new Width:UINT = eax
   .new Height:UINT = ecx

    ; Create swapchain for window

   .new SwapChainDesc:DXGI_SWAP_CHAIN_DESC1 = {0}
    mov SwapChainDesc.SwapEffect,DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL
    mov SwapChainDesc.BufferCount,2
    mov SwapChainDesc.Width,Width
    mov SwapChainDesc.Height,Height
    mov SwapChainDesc.Format,DXGI_FORMAT_B8G8R8A8_UNORM
    mov SwapChainDesc.BufferUsage,DXGI_USAGE_RENDER_TARGET_OUTPUT
    mov SwapChainDesc.SampleDesc.Count,1
    mov SwapChainDesc.SampleDesc.Quality,0
    mov hr,this.m_Factory.CreateSwapChainForHwnd([rsi].m_Device, Window,
            &SwapChainDesc, nullptr, nullptr, &[rsi].m_SwapChain)
    .if (FAILED(hr))

        .return ProcessFailure([rsi].m_Device,
                L"Failed to create window swapchain",
                L"Error", hr, &SystemTransitionsExpectedErrors)
    .endif

    ; Disable the ALT-ENTER shortcut for entering full-screen mode

    mov hr,this.m_Factory.MakeWindowAssociation(Window, DXGI_MWA_NO_ALT_ENTER)
    .if (FAILED(hr))

        .return ProcessFailure([rsi].m_Device,
                L"Failed to make window association",
                L"Error", hr, &SystemTransitionsExpectedErrors)
    .endif

    ; Create shared texture

    .new Return:DUPL_RETURN = this.CreateSharedSurf(SingleOutput, OutCount, DeskBounds)
    .if (Return != DUPL_RETURN_SUCCESS)

        .return Return
    .endif

    ; Make new render target view

    mov Return,this.MakeRTV()
    .if ( Return != DUPL_RETURN_SUCCESS )

        .return Return
    .endif

    ; Set view port

    this.SetViewPort(Width, Height)

    ; Create the sample state

   .new SampDesc:D3D11_SAMPLER_DESC = {0}
    mov SampDesc.Filter,D3D11_FILTER_MIN_MAG_MIP_LINEAR
    mov SampDesc.AddressU,D3D11_TEXTURE_ADDRESS_CLAMP
    mov SampDesc.AddressV,D3D11_TEXTURE_ADDRESS_CLAMP
    mov SampDesc.AddressW,D3D11_TEXTURE_ADDRESS_CLAMP
    mov SampDesc.ComparisonFunc,D3D11_COMPARISON_NEVER
    mov SampDesc.MaxLOD,D3D11_FLOAT32_MAX

    mov hr,this.m_Device.CreateSamplerState(&SampDesc, &[rsi].m_SamplerLinear)
    .if (FAILED(hr))

        .return ProcessFailure([rsi].m_Device,
                L"Failed to create sampler state in OUTPUTMANAGER",
                L"Error", hr, &SystemTransitionsExpectedErrors)
    .endif

    ; Create the blend state

   .new BlendStateDesc:D3D11_BLEND_DESC
    mov BlendStateDesc.AlphaToCoverageEnable,FALSE
    mov BlendStateDesc.IndependentBlendEnable,FALSE
    mov BlendStateDesc.RenderTarget[0].BlendEnable,TRUE
    mov BlendStateDesc.RenderTarget[0].SrcBlend,D3D11_BLEND_SRC_ALPHA
    mov BlendStateDesc.RenderTarget[0].DestBlend,D3D11_BLEND_INV_SRC_ALPHA
    mov BlendStateDesc.RenderTarget[0].BlendOp,D3D11_BLEND_OP_ADD
    mov BlendStateDesc.RenderTarget[0].SrcBlendAlpha,D3D11_BLEND_ONE
    mov BlendStateDesc.RenderTarget[0].DestBlendAlpha,D3D11_BLEND_ZERO
    mov BlendStateDesc.RenderTarget[0].BlendOpAlpha,D3D11_BLEND_OP_ADD
    mov BlendStateDesc.RenderTarget[0].RenderTargetWriteMask,D3D11_COLOR_WRITE_ENABLE_ALL

    mov hr,this.m_Device.CreateBlendState(&BlendStateDesc, &[rsi].m_BlendState)
    .if (FAILED(hr))

        .return ProcessFailure([rsi].m_Device,
                L"Failed to create blend state in OUTPUTMANAGER",
                L"Error", hr, &SystemTransitionsExpectedErrors)
    .endif

    ; Initialize shaders

    mov Return,this.InitShaders()
    .if (Return != DUPL_RETURN_SUCCESS)

        .return Return
    .endif

    GetWindowRect([rsi].m_WindowHandle, &WindowRect)

    mov rax,DeskBounds
    mov ecx,[rax].RECT.right
    sub ecx,[rax].RECT.left
    shr ecx,1
    mov edx,[rax].RECT.bottom
    sub edx,[rax].RECT.top
    shr edx,1
    MoveWindow([rsi].m_WindowHandle, WindowRect.left, WindowRect.top, ecx, edx, TRUE)

   .return Return

OUTPUTMANAGER::InitOutput endp

;
; Recreate shared texture
;
OUTPUTMANAGER::CreateSharedSurf proc uses rsi rdi rbx SingleOutput:SINT,
        OutCount:ptr UINT, DeskBounds:ptr RECT

    mov rsi,rcx
    mov rdi,r9

    ; Get DXGI resources

   .new hr:HRESULT
   .new DxgiDevice:ptr IDXGIDevice = nullptr
    mov hr,this.m_Device.QueryInterface(&IID_IDXGIDevice, &DxgiDevice)
    .if (FAILED(hr))

        .return ProcessFailure(nullptr,
                L"Failed to QI for DXGI Device", L"Error", hr, nullptr)
    .endif

   .new DxgiAdapter:ptr IDXGIAdapter = nullptr
    mov hr,DxgiDevice.GetParent(&IID_IDXGIAdapter, &DxgiAdapter)
    DxgiDevice.Release()
    mov DxgiDevice,nullptr
    .if (FAILED(hr))

        .return ProcessFailure([rsi].m_Device,
                L"Failed to get parent DXGI Adapter",
                L"Error", hr, &SystemTransitionsExpectedErrors)
    .endif

    ; Set initial values so that we always catch the right coordinates

    assume rdi:ptr RECT

    mov [rdi].left,INT_MAX
    mov [rdi].right,INT_MIN
    mov [rdi].top,INT_MAX
    mov [rdi].bottom,INT_MIN

    .new DxgiOutput:ptr IDXGIOutput = nullptr

    ; Figure out right dimensions for full size desktop texture and # of
    ; outputs to duplicate

    .if ( SingleOutput < 0 )

        mov hr,S_OK
        .for ( ebx = 0: SUCCEEDED(hr): ++ebx )

            SafeRelease(DxgiOutput)
            mov hr,DxgiAdapter.EnumOutputs(ebx, &DxgiOutput)
            .if ( DxgiOutput && ( hr != DXGI_ERROR_NOT_FOUND ) )

               .new DesktopDesc:DXGI_OUTPUT_DESC
                DxgiOutput.GetDesc(&DesktopDesc)

                .if ( [rdi].left > DesktopDesc.DesktopCoordinates.left )
                    mov [rdi].left,eax
                .endif
                .if ( [rdi].top > DesktopDesc.DesktopCoordinates.top )
                    mov [rdi].top,eax
                .endif
                .if ( [rdi].right < DesktopDesc.DesktopCoordinates.right )
                    mov [rdi].right,eax
                .endif
                .if ( [rdi].bottom < DesktopDesc.DesktopCoordinates.bottom )
                    mov [rdi].bottom,eax
                .endif
            .endif
        .endf

        dec ebx

    .else

        mov hr,DxgiAdapter.EnumOutputs(SingleOutput, &DxgiOutput)
        .if (FAILED(hr))

            SafeRelease(DxgiAdapter)
           .return ProcessFailure([rsi].m_Device,
                    L"Output specified to be duplicated does not exist",
                    L"Error", hr, nullptr)
        .endif

       .new DesktopDesc:DXGI_OUTPUT_DESC
        DxgiOutput.GetDesc(&DesktopDesc)
        mov [rdi],DesktopDesc.DesktopCoordinates

        SafeRelease(DxgiOutput)
        mov ebx,1
    .endif

    SafeRelease(DxgiAdapter)

    ; Set passed in output count variable

    mov rcx,OutCount
    mov [rcx],ebx

    .if ( ebx == 0 )

        ; We could not find any outputs, the system must be in a transition so
        ; return expected error so we will attempt to recreate

        .return DUPL_RETURN_ERROR_EXPECTED
    .endif

    ; Create shared texture for all duplication threads to draw into

   .new DeskTexD:D3D11_TEXTURE2D_DESC = {0}
    mov eax,[rdi].right
    sub eax,[rdi].left
    mov DeskTexD.Width,eax
    mov eax,[rdi].bottom
    sub eax,[rdi].top
    mov DeskTexD.Height,eax
    mov DeskTexD.MipLevels,1
    mov DeskTexD.ArraySize,1
    mov DeskTexD.Format,DXGI_FORMAT_B8G8R8A8_UNORM
    mov DeskTexD.SampleDesc.Count,1
    mov DeskTexD.Usage,D3D11_USAGE_DEFAULT
    mov DeskTexD.BindFlags,D3D11_BIND_RENDER_TARGET or D3D11_BIND_SHADER_RESOURCE
    mov DeskTexD.CPUAccessFlags,0
    mov DeskTexD.MiscFlags,D3D11_RESOURCE_MISC_SHARED_KEYEDMUTEX

    mov hr,this.m_Device.CreateTexture2D(&DeskTexD, nullptr, &[rsi].m_SharedSurf)
    .if (FAILED(hr))

        .if ( ebx != 1 )

            ; If we are duplicating the complete desktop we try to create a single texture to hold the
            ; complete desktop image and blit updates from the per output DDA interface.  The GPU can
            ; always support a texture size of the maximum resolution of any single output but there is no
            ; guarantee that it can support a texture size of the desktop.
            ; The sample only use this large texture to display the desktop image in a single window using DX
            ; we could revert back to using GDI to update the window in this failure case.

            .return ProcessFailure([rsi].m_Device,
                    L"Failed to create DirectX shared texture -" \
                    " we are attempting to create a texture the size of the" \
                    " complete desktop and this may be larger than the maximum" \
                    " texture size of your GPU.  Please try again using the" \
                    " -output command line parameter to duplicate only 1 monitor" \
                    " or configure your computer to a single monitor configuration",
                    L"Error", hr, &SystemTransitionsExpectedErrors)

        .else

            .return ProcessFailure([rsi].m_Device,
                    L"Failed to create shared texture",
                    L"Error", hr, &SystemTransitionsExpectedErrors)
        .endif
    .endif

    ; Get keyed mutex

    mov hr,this.m_SharedSurf.QueryInterface(&IID_IDXGIKeyedMutex, &[rsi].m_KeyMutex)
    .if (FAILED(hr))

        .return ProcessFailure([rsi].m_Device,
                L"Failed to query for keyed mutex in OUTPUTMANAGER",
                L"Error", hr, nullptr)
    .endif
    .return DUPL_RETURN_SUCCESS

OUTPUTMANAGER::CreateSharedSurf endp

;
; Present to the application window
;
OUTPUTMANAGER::UpdateApplicationWindow proc uses rsi PointerInfo:ptr PTR_INFO, Occluded:ptr bool

    mov rsi,rcx

    ; In a typical desktop duplication application there would be an application
    ; running on one system collecting the desktop images and another
    ; application running on a different system that receives the desktop images
    ; via a network and display the image. This sample contains both these
    ; aspects into a single application. This routine is the part of the sample
    ; that displays the desktop image onto the display

    ; Try and acquire sync on common display buffer

    .new hr:HRESULT = this.m_KeyMutex.AcquireSync(1, 100)

    .if ( hr == WAIT_TIMEOUT )

        ; Another thread has the keyed mutex so try again later

        .return DUPL_RETURN_SUCCESS

    .elseif (FAILED(hr))

        .return ProcessFailure([rsi].m_Device,
                L"Failed to acquire Keyed mutex in OUTPUTMANAGER",
                L"Error", hr, &SystemTransitionsExpectedErrors)
    .endif

    ; Got mutex, so draw

    .new retval:DUPL_RETURN = this.DrawFrame()
    .if ( retval == DUPL_RETURN_SUCCESS )

        ; We have keyed mutex so we can access the mouse info

        mov rdx,PointerInfo
        .if ( [rdx].PTR_INFO.Visible )

            ; Draw mouse into texture

            mov retval,this.DrawMouse(rdx)
        .endif
    .endif

    ; Release keyed mutex

    mov hr,this.m_KeyMutex.ReleaseSync(0)
    .if (FAILED(hr))

        .return ProcessFailure([rsi].m_Device,
                L"Failed to Release Keyed mutex in OUTPUTMANAGER",
                L"Error", hr, &SystemTransitionsExpectedErrors)
    .endif

    ; Present to window if all worked

    .if ( retval == DUPL_RETURN_SUCCESS )

        ; Present to window

        mov hr,this.m_SwapChain.Present(1, 0)
        .if (FAILED(hr))

            .return ProcessFailure([rsi].m_Device,
                    L"Failed to present",
                    L"Error", hr, &SystemTransitionsExpectedErrors)

        .elseif ( hr == DXGI_STATUS_OCCLUDED )

            mov rcx,Occluded
            mov bool ptr [rcx],true
        .endif
    .endif

    .return retval

OUTPUTMANAGER::UpdateApplicationWindow endp

;
; Returns shared handle
;
OUTPUTMANAGER::GetSharedHandle proc

    ; QI IDXGIResource interface to synchronized shared surface.

    .new Hnd:HANDLE = nullptr
    .new DXGIResource:ptr IDXGIResource = nullptr
    .new hr:HRESULT = this.m_SharedSurf.QueryInterface(&IID_IDXGIResource, &DXGIResource)
    .if (SUCCEEDED(hr))

        ; Obtain handle to IDXGIResource object.

        DXGIResource.GetSharedHandle(&Hnd)
        SafeRelease(DXGIResource)
    .endif
    .return Hnd

OUTPUTMANAGER::GetSharedHandle endp

;
; Draw frame into backbuffer
;
OUTPUTMANAGER::DrawFrame proc uses rsi rbx

    mov rsi,rcx
   .new hr:HRESULT

    ; If window was resized, resize swapchain

    .if ( [rsi].m_NeedsResize )

        .new retval:DUPL_RETURN = this.ResizeSwapChain()
        .if ( retval != DUPL_RETURN_SUCCESS )

            .return retval
        .endif
        mov [rsi].m_NeedsResize,false
    .endif

    ; Vertices for drawing whole texture

   .new Vertices[NUMVERTICES]:VERTEX = {
        { { -1.0, -1.0, 0.0 }, { 0.0, 1.0 } },
        { { -1.0,  1.0, 0.0 }, { 0.0, 0.0 } },
        { {  1.0, -1.0, 0.0 }, { 1.0, 1.0 } },
        { {  1.0, -1.0, 0.0 }, { 1.0, 1.0 } },
        { { -1.0,  1.0, 0.0 }, { 0.0, 0.0 } },
        { {  1.0,  1.0, 0.0 }, { 1.0, 0.0 } }
        }

   .new FrameDesc:D3D11_TEXTURE2D_DESC
    this.m_SharedSurf.GetDesc(&FrameDesc)

   .new ShaderDesc:D3D11_SHADER_RESOURCE_VIEW_DESC
    mov ShaderDesc.Format,FrameDesc.Format
    mov ShaderDesc.ViewDimension,D3D11_SRV_DIMENSION_TEXTURE2D
    mov ShaderDesc.Texture2D.MipLevels,FrameDesc.MipLevels
    dec eax
    mov ShaderDesc.Texture2D.MostDetailedMip,eax

    ; Create new shader resource view

   .new ShaderResource:ptr ID3D11ShaderResourceView = nullptr
    mov hr,this.m_Device.CreateShaderResourceView(
            [rsi].m_SharedSurf, &ShaderDesc, &ShaderResource)
    .if (FAILED(hr))

        .return ProcessFailure([rsi].m_Device,
                L"Failed to create shader resource when drawing a frame",
                L"Error", hr, &SystemTransitionsExpectedErrors)
    .endif

    ; Set resources

   .new Stride:UINT = sizeof(VERTEX)
   .new Offs:UINT = 0
   .new blendFactor[4]:FLOAT = { 0.0, 0.0, 0.0, 0.0 }

    assume rbx:ptr ID3D11DeviceContext

    mov rbx,[rsi].m_DeviceContext

    [rbx].OMSetBlendState(nullptr, &blendFactor, 0xffffffff)
    [rbx].OMSetRenderTargets(1, &[rsi].m_RTV, nullptr)
    [rbx].VSSetShader([rsi].m_VertexShader, nullptr, 0)
    [rbx].PSSetShader([rsi].m_PixelShader, nullptr, 0)
    [rbx].PSSetShaderResources(0, 1, &ShaderResource)
    [rbx].PSSetSamplers(0, 1, &[rsi].m_SamplerLinear)
    [rbx].IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)

   .new BufferDesc:D3D11_BUFFER_DESC = {0}
    mov BufferDesc.Usage,D3D11_USAGE_DEFAULT
    mov BufferDesc.ByteWidth,sizeof(VERTEX) * NUMVERTICES
    mov BufferDesc.BindFlags,D3D11_BIND_VERTEX_BUFFER
    mov BufferDesc.CPUAccessFlags,0

   .new InitData:D3D11_SUBRESOURCE_DATA = {0}
    mov InitData.pSysMem,&Vertices

   .new VertexBuffer:ptr ID3D11Buffer = nullptr

    ; Create vertex buffer

    mov hr,this.m_Device.CreateBuffer(&BufferDesc, &InitData, &VertexBuffer)
    .if (FAILED(hr))

        SafeRelease(ShaderResource)
       .return ProcessFailure([rsi].m_Device,
                L"Failed to create vertex buffer when drawing a frame",
                L"Error", hr, &SystemTransitionsExpectedErrors)
    .endif
    [rbx].IASetVertexBuffers(0, 1, &VertexBuffer, &Stride, &Offs)

    ; Draw textured quad onto render target

    [rbx].Draw(NUMVERTICES, 0)

    assume rbx:nothing

    SafeRelease(VertexBuffer)
    SafeRelease(ShaderResource)

   .return DUPL_RETURN_SUCCESS

OUTPUTMANAGER::DrawFrame endp

;
; Process both masked and monochrome pointers
;
OUTPUTMANAGER::ProcessMonoMask proc uses rsi rdi rbx r12 r13 r14 r15 \
        IsMono      : bool,
        PtrInfo     : ptr PTR_INFO,
        PtrWidth    : ptr SINT,
        PtrHeight   : ptr SINT,
        PtrLeft     : ptr SINT,
        PtrTop      : ptr SINT,
        InitBuffer  : ptr ptr BYTE,
        Box         : ptr D3D11_BOX

    mov rsi,rcx
    mov rdi,r8

    assume rdi:ptr PTR_INFO

    ; Desktop dimensions

   .new FullDesc:D3D11_TEXTURE2D_DESC
    this.m_SharedSurf.GetDesc(&FullDesc)

   .new DesktopWidth:SINT = FullDesc.Width
   .new DesktopHeight:SINT = FullDesc.Height

    ; Pointer position

   .new GivenTop:SINT = [rdi].Position.y
   .new GivenLeft:SINT = [rdi].Position.x

    ; Figure out if any adjustment is needed for out of bound positions

    add eax,[rdi].ShapeInfo.Width
    mov rcx,PtrWidth
    .if ( GivenLeft < 0 )
    .elseifs ( eax > DesktopWidth )
        mov eax,DesktopWidth
        sub eax,GivenLeft
    .else
        mov eax,[rdi].ShapeInfo.Width
    .endif
    mov [rcx],eax


    mov edx,[rdi].ShapeInfo.Height
    .if ( IsMono )
        shr edx,1
    .endif
    mov eax,GivenTop
    add eax,edx
    mov rcx,PtrHeight
    .if ( GivenTop < 0 )
    .elseifs ( eax > DesktopHeight )
        mov eax,DesktopHeight
        sub eax,GivenTop
    .else
        mov eax,edx
    .endif
    mov [rcx],eax

    .if ( IsMono )
        shl edx,1
    .endif
    mov [rdi].ShapeInfo.Height,edx

    xor edx,edx
    mov rcx,PtrLeft
    mov eax,GivenLeft
    cmp eax,edx
    cmovl eax,edx
    mov [rcx],eax
    mov rcx,PtrTop
    mov eax,GivenTop
    cmp eax,edx
    cmovl eax,edx
    mov [rcx],eax

    ; Staging buffer/texture

    mov rcx,PtrWidth
    mov rdx,PtrHeight
    mov eax,[rcx]
    mov edx,[rdx]

   .new CopyBufferDesc:D3D11_TEXTURE2D_DESC
    mov CopyBufferDesc.Width,eax
    mov CopyBufferDesc.Height,edx
    mov CopyBufferDesc.MipLevels,1
    mov CopyBufferDesc.ArraySize,1
    mov CopyBufferDesc.Format,DXGI_FORMAT_B8G8R8A8_UNORM
    mov CopyBufferDesc.SampleDesc.Count,1
    mov CopyBufferDesc.SampleDesc.Quality,0
    mov CopyBufferDesc.Usage,D3D11_USAGE_STAGING
    mov CopyBufferDesc.BindFlags,0
    mov CopyBufferDesc.CPUAccessFlags,D3D11_CPU_ACCESS_READ
    mov CopyBufferDesc.MiscFlags,0

    .new CopyBuffer:ptr ID3D11Texture2D = nullptr
    .new hr:HRESULT = this.m_Device.CreateTexture2D(
            &CopyBufferDesc, nullptr, &CopyBuffer)
    .if (FAILED(hr))

        .return ProcessFailure([rsi].m_Device,
                L"Failed creating staging texture for pointer",
                L"Error", hr, &SystemTransitionsExpectedErrors)
    .endif

    ; Copy needed part of desktop image

    mov rbx,Box
    mov rcx,PtrLeft
    mov rdx,PtrTop
    mov ecx,[rcx]
    mov edx,[rdx]
    mov [rbx].D3D11_BOX.left,ecx
    mov [rbx].D3D11_BOX.top,edx
    mov rax,PtrWidth
    add ecx,[rax]
    mov [rbx].D3D11_BOX.right,ecx
    mov rax,PtrHeight
    add edx,[rax]
    mov [rbx].D3D11_BOX.bottom,edx

    this.m_DeviceContext.CopySubresourceRegion(
            CopyBuffer, 0, 0, 0, 0, [rsi].m_SharedSurf, 0, rbx)

    ; QI for IDXGISurface

   .new CopySurface:ptr IDXGISurface = nullptr
    mov hr,CopyBuffer.QueryInterface(&IID_IDXGISurface, &CopySurface)

    SafeRelease(CopyBuffer)

    .if (FAILED(hr))

        .return ProcessFailure(nullptr,
                L"Failed to QI staging texture into IDXGISurface for pointer",
                L"Error", hr, &SystemTransitionsExpectedErrors)
    .endif

    ; Map pixels

   .new MappedSurface:DXGI_MAPPED_RECT
    mov hr,CopySurface.Map(&MappedSurface, DXGI_MAP_READ)
    .if (FAILED(hr))

        SafeRelease(CopySurface)
       .return ProcessFailure([rsi].m_Device,
                L"Failed to map surface for pointer",
                L"Error", hr, &SystemTransitionsExpectedErrors)
    .endif

    ; New mouseshape buffer

    mov rcx,PtrWidth
    mov rdx,PtrHeight
    mov r11d,[rcx]
    mov eax,[rdx]
    mov r12d,eax
    mul r11d
    mov ecx,BPP
    mul ecx
    mov r15,malloc(rax)
    mov rbx,InitBuffer
    mov [rbx],rax

    .if ( !rax )

        .return ProcessFailure(nullptr,
                L"Failed to allocate memory for new mouse shape buffer.",
                L"Error", E_OUTOFMEMORY, nullptr)
    .endif


    mov r10,MappedSurface.pBits
    mov eax,MappedSurface.Pitch
    shr eax,2
   .new DesktopPitchInPixels:UINT = eax

    ; What to skip (pixel offset)

    xor eax,eax
    xor ecx,ecx
    .if ( GivenLeft < 0 )
        neg eax
    .endif
    .if ( GivenTop < 0 )
        neg ecx
    .endif

   .new SkipX:UINT = eax
   .new SkipY:UINT = ecx

    .if ( IsMono )

        .fors ( r13d = 0: r13d < r12d: ++r13d )

            ; Set mask

            mov eax,0x80
            mov ecx,SkipX
            and ecx,7
            shr eax,cl
            mov ecx,eax

            .fors ( r14d = 0: r14d < r11d: ++r14d )

                ; Get masks using appropriate offsets

                mov eax,r13d
                add eax,SkipY
                mul [rdi].ShapeInfo.Pitch
                mov edx,r14d
                add edx,SkipX
                shr edx,3
                add edx,eax
                add rdx,[rdi].PtrShapeBuffer
                test [rdx],cl
                mov r8d,0xFFFFFFFF
                mov eax,0xFF000000
                cmovz r8d,eax

                mov eax,[rdi].ShapeInfo.Height
                shr eax,1
                add eax,r13d
                add eax,SkipY
                mul [rdi].ShapeInfo.Pitch
                mov edx,r14d
                add edx,SkipX
                shr edx,3
                add edx,eax
                add rdx,[rdi].PtrShapeBuffer
                xor r9d,r9d
                test [rdx],cl
                mov eax,0x00FFFFFF
                cmovnz r8d,eax

                ; Set new pixel

                mov eax,r13d
                mul DesktopPitchInPixels
                add eax,r14d
                mov eax,[r10+rax*4]
                and r8d,eax
                xor r8d,r9d
                mov eax,r11d
                mul r13d
                add eax,r14d
                mov [r15+rax*4],r8d

                ; Adjust mask

                .if ( ecx == 0x01 )
                    mov ecx,0x80
                .else
                    shr ecx,1
                .endif
            .endf
        .endf

    .else

        ; Iterate through pixels

        mov r9,[rdi].PtrShapeBuffer
        mov ecx,[rdi].ShapeInfo.Pitch

        .fors ( r13d = 0: r13d < r12d: ++r13d )


            .fors ( r14d = 0: r14d < r11d: ++r14d )

                ; Set up mask

                mov eax,r13d
                add eax,SkipY
                mov edx,ecx
                shr edx,2
                mul edx
                mov edx,r14d
                add edx,SkipX
                add edx,eax
                shl edx,2
                add rdx,r9
                mov r8d,[rdx]

                .if ( r8d & 0xFF000000 )

                    ; Mask was 0xFF

                    mov eax,r13d
                    mul DesktopPitchInPixels
                    add eax,r14d
                    xor r8d,[r10+rax*4]
                .endif
                or  r8d,0xFF000000
                mov eax,r11d
                mul r13d
                add eax,r14d
                mov [r15+rax*4],r8d
            .endf
        .endf
    .endif

    ; Done with resource

    mov hr,CopySurface.Unmap()
    SafeRelease(CopySurface)

    .if (FAILED(hr))

        .return ProcessFailure([rsi].m_Device,
                L"Failed to unmap surface for pointer",
                L"Error", hr, &SystemTransitionsExpectedErrors)
    .endif
    .return DUPL_RETURN_SUCCESS

OUTPUTMANAGER::ProcessMonoMask endp

;
; Draw mouse provided in buffer to backbuffer
;
OUTPUTMANAGER::DrawMouse proc uses rsi rdi rbx PtrInfo:ptr PTR_INFO

    mov rsi,rcx
    mov rdi,rdx

    ; Vars to be used

   .new MouseTex:ptr ID3D11Texture2D = nullptr
   .new ShaderRes:ptr ID3D11ShaderResourceView = nullptr
   .new VertexBufferMouse:ptr ID3D11Buffer = nullptr
   .new InitData:D3D11_SUBRESOURCE_DATA
   .new Desc:D3D11_TEXTURE2D_DESC
   .new SDesc:D3D11_SHADER_RESOURCE_VIEW_DESC

    ; Position will be changed based on mouse position

   .new Vertices[NUMVERTICES]:VERTEX = {
        { { -1.0, -1.0, 0.0 }, { 0.0, 1.0 } },
        { { -1.0,  1.0, 0.0 }, { 0.0, 0.0 } },
        { {  1.0, -1.0, 0.0 }, { 1.0, 1.0 } },
        { {  1.0, -1.0, 0.0 }, { 1.0, 1.0 } },
        { { -1.0,  1.0, 0.0 }, { 0.0, 0.0 } },
        { {  1.0,  1.0, 0.0 }, { 1.0, 0.0 } }
        }

   .new FullDesc:D3D11_TEXTURE2D_DESC
    this.m_SharedSurf.GetDesc(&FullDesc)

   .new DesktopWidth:SINT = FullDesc.Width
   .new DesktopHeight:SINT = FullDesc.Height

    ; Center of desktop dimensions

    mov eax,DesktopWidth
    mov ecx,DesktopHeight
    shr eax,1
    shr ecx,1
   .new CenterX:SINT = eax
   .new CenterY:SINT = ecx

    ; Clipping adjusted coordinates / dimensions

   .new PtrWidth:SINT = 0
   .new PtrHeight:SINT = 0
   .new PtrLeft:SINT = 0
   .new PtrTop:SINT = 0

    ; Buffer used if necessary (in case of monochrome or masked pointer)

   .new InitBuffer:ptr BYTE = nullptr

    ; Used for copying pixels

   .new Box:D3D11_BOX
    mov Box.front,0
    mov Box.back,1

    mov Desc.MipLevels,1
    mov Desc.ArraySize,1
    mov Desc.Format,DXGI_FORMAT_B8G8R8A8_UNORM
    mov Desc.SampleDesc.Count,1
    mov Desc.SampleDesc.Quality,0
    mov Desc.Usage,D3D11_USAGE_DEFAULT
    mov Desc.BindFlags,D3D11_BIND_SHADER_RESOURCE
    mov Desc.CPUAccessFlags,0
    mov Desc.MiscFlags,0

    ; Set shader resource properties

    mov SDesc.Format,Desc.Format
    mov SDesc.ViewDimension,D3D11_SRV_DIMENSION_TEXTURE2D
    mov SDesc.Texture2D.MipLevels,Desc.MipLevels
    dec eax
    mov SDesc.Texture2D.MostDetailedMip,eax

    .switch ( [rdi].ShapeInfo.Type )

    .case DXGI_OUTDUPL_POINTER_SHAPE_TYPE_COLOR

        mov PtrLeft,    [rdi].Position.x
        mov PtrTop,     [rdi].Position.y
        mov PtrWidth,   [rdi].ShapeInfo.Width
        mov PtrHeight,  [rdi].ShapeInfo.Height
       .endc

    .case DXGI_OUTDUPL_POINTER_SHAPE_TYPE_MONOCHROME

        this.ProcessMonoMask(true, PtrInfo, &PtrWidth,
                &PtrHeight, &PtrLeft, &PtrTop, &InitBuffer, &Box)
       .endc

    .case DXGI_OUTDUPL_POINTER_SHAPE_TYPE_MASKED_COLOR

        this.ProcessMonoMask(false, PtrInfo, &PtrWidth,
                &PtrHeight, &PtrLeft, &PtrTop, &InitBuffer, &Box)
       .endc
    .endsw

    ; VERTEX creation

    cvtsi2ss    xmm0,PtrLeft
    cvtsi2ss    xmm4,CenterX
    subss       xmm0,xmm4
    divss       xmm0,xmm4
    movss       Vertices[VERTEX*0].Pos.x,xmm0
    movss       Vertices[VERTEX*1].Pos.x,xmm0
    cvtsi2ss    xmm0,PtrTop
    cvtsi2ss    xmm1,PtrHeight
    cvtsi2ss    xmm2,CenterY
    movss       xmm3,xmm0
    addss       xmm0,xmm1
    subss       xmm0,xmm2
    divss       xmm0,xmm2
    mulss       xmm0,-1.0
    movss       Vertices[VERTEX*0].Pos.y,xmm0
    movss       Vertices[VERTEX*2].Pos.y,xmm0
    subss       xmm3,xmm2
    divss       xmm3,xmm2
    mulss       xmm3,-1.0
    movss       Vertices[VERTEX*1].Pos.y,xmm3
    movss       Vertices[VERTEX*5].Pos.y,xmm3
    cvtsi2ss    xmm0,PtrLeft
    cvtsi2ss    xmm1,PtrWidth
    addss       xmm0,xmm1
    subss       xmm0,xmm4
    divss       xmm0,xmm4
    movss       Vertices[VERTEX*2].Pos.x,xmm0
    movss       Vertices[VERTEX*5].Pos.x,xmm0
    mov         Vertices[VERTEX*3].Pos.x,Vertices[VERTEX*2].Pos.x
    mov         Vertices[VERTEX*3].Pos.y,Vertices[VERTEX*2].Pos.y
    mov         Vertices[VERTEX*4].Pos.x,Vertices[VERTEX*1].Pos.x
    mov         Vertices[VERTEX*4].Pos.y,Vertices[VERTEX*1].Pos.y

    ; Set texture properties

    mov Desc.Width,PtrWidth
    mov Desc.Height,PtrHeight

    ; Set up init data

    mov rax,InitBuffer
    .if ( [rdi].ShapeInfo.Type == DXGI_OUTDUPL_POINTER_SHAPE_TYPE_COLOR )
        mov rax,[rdi].PtrShapeBuffer
    .endif
    mov InitData.pSysMem,rax

    imul eax,PtrWidth,BPP
    .if ( [rdi].ShapeInfo.Type == DXGI_OUTDUPL_POINTER_SHAPE_TYPE_COLOR )
        mov eax,[rdi].ShapeInfo.Pitch
    .endif
    mov InitData.SysMemPitch,eax
    mov InitData.SysMemSlicePitch,0

    ; Create mouseshape as texture

    .new hr:HRESULT = this.m_Device.CreateTexture2D(&Desc, &InitData, &MouseTex)
    .if (FAILED(hr))

        .return ProcessFailure([rsi].m_Device,
                L"Failed to create mouse pointer texture",
                L"Error", hr, &SystemTransitionsExpectedErrors)
    .endif

    ; Create shader resource from texture

    mov hr,this.m_Device.CreateShaderResourceView(MouseTex, &SDesc, &ShaderRes)
    .if (FAILED(hr))

        SafeRelease(MouseTex)

       .return ProcessFailure([rsi].m_Device,
                L"Failed to create shader resource from mouse pointer texture",
                L"Error", hr, &SystemTransitionsExpectedErrors)
    .endif

   .new BDesc:D3D11_BUFFER_DESC = {0}
    mov BDesc.Usage,D3D11_USAGE_DEFAULT
    mov BDesc.ByteWidth,sizeof(VERTEX) * NUMVERTICES
    mov BDesc.BindFlags,D3D11_BIND_VERTEX_BUFFER
    mov BDesc.CPUAccessFlags,0

    ZeroMemory(&InitData, sizeof(D3D11_SUBRESOURCE_DATA))
    mov InitData.pSysMem,&Vertices

    ; Create vertex buffer

    mov hr,this.m_Device.CreateBuffer(&BDesc, &InitData, &VertexBufferMouse)
    .if (FAILED(hr))

        SafeRelease(ShaderRes)
        SafeRelease(MouseTex)

       .return ProcessFailure([rsi].m_Device,
                L"Failed to create mouse pointer vertex buffer in OutputManager",
                L"Error", hr, &SystemTransitionsExpectedErrors)
    .endif

    ; Set resources

   .new BlendFactor[4]:FLOAT = { 0.0, 0.0, 0.0, 0.0 }
   .new Stride:UINT = sizeof(VERTEX)
   .new Offs:UINT = 0

    this.m_DeviceContext.IASetVertexBuffers(0, 1, &VertexBufferMouse, &Stride, &Offs)
    this.m_DeviceContext.OMSetBlendState([rsi].m_BlendState, &BlendFactor, 0xFFFFFFFF)
    this.m_DeviceContext.OMSetRenderTargets(1, &[rsi].m_RTV, nullptr)
    this.m_DeviceContext.VSSetShader([rsi].m_VertexShader, nullptr, 0)
    this.m_DeviceContext.PSSetShader([rsi].m_PixelShader, nullptr, 0)
    this.m_DeviceContext.PSSetShaderResources(0, 1, &ShaderRes)
    this.m_DeviceContext.PSSetSamplers(0, 1, &[rsi].m_SamplerLinear)

    ; Draw

    this.m_DeviceContext.Draw(NUMVERTICES, 0)

    ; Clean

    SafeRelease(VertexBufferMouse)
    SafeRelease(ShaderRes)
    SafeRelease(MouseTex)
    .if ( InitBuffer )
        free(InitBuffer)
        mov InitBuffer,nullptr
    .endif
   .return DUPL_RETURN_SUCCESS

OUTPUTMANAGER::DrawMouse endp

;
; Initialize shaders for drawing to screen
;
OUTPUTMANAGER::InitShaders proc uses rsi

    mov rsi,rcx

   .new hr:HRESULT
   .new Size:size_t = g_VS_size
    mov hr,this.m_Device.CreateVertexShader(&g_VS, Size, nullptr, &[rsi].m_VertexShader)
    .if (FAILED(hr))

        .return ProcessFailure([rsi].m_Device,
                L"Failed to create vertex shader in OUTPUTMANAGER",
                L"Error", hr, &SystemTransitionsExpectedErrors)
    .endif

   .new Layout[2]:D3D11_INPUT_ELEMENT_DESC = {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
        }
   .new NumElements:UINT = ARRAYSIZE(Layout)
    mov hr,this.m_Device.CreateInputLayout(&Layout, NumElements, &g_VS, Size, &[rsi].m_InputLayout)
    .if (FAILED(hr))

        .return ProcessFailure([rsi].m_Device,
                L"Failed to create input layout in OUTPUTMANAGER",
                L"Error", hr, &SystemTransitionsExpectedErrors)
    .endif
    this.m_DeviceContext.IASetInputLayout([rsi].m_InputLayout)

    mov Size,g_PS_size
    mov hr,this.m_Device.CreatePixelShader(&g_PS, Size, nullptr, &[rsi].m_PixelShader)
    .if (FAILED(hr))

        .return ProcessFailure([rsi].m_Device,
                L"Failed to create pixel shader in OUTPUTMANAGER",
                L"Error", hr, &SystemTransitionsExpectedErrors)
    .endif

    .return DUPL_RETURN_SUCCESS

OUTPUTMANAGER::InitShaders endp

;
; Reset render target view
;
OUTPUTMANAGER::MakeRTV proc uses rsi

    mov rsi,rcx

    ; Get backbuffer

    .new BackBuffer:ptr ID3D11Texture2D = nullptr
    .new hr:HRESULT = this.m_SwapChain.GetBuffer(0, &IID_ID3D11Texture2D, &BackBuffer)
    .if (FAILED(hr))

        .return ProcessFailure([rsi].m_Device,
                L"Failed to get backbuffer for making render target view in OUTPUTMANAGER",
                L"Error", hr, &SystemTransitionsExpectedErrors)
    .endif

    ; Create a render target view

    mov hr,this.m_Device.CreateRenderTargetView(BackBuffer, nullptr, &[rsi].m_RTV)
    BackBuffer.Release()
    .if (FAILED(hr))

        .return ProcessFailure([rsi].m_Device,
                L"Failed to create render target view in OUTPUTMANAGER",
                L"Error", hr, &SystemTransitionsExpectedErrors)
    .endif

    ; Set new render target

    this.m_DeviceContext.OMSetRenderTargets(1, &[rsi].m_RTV, nullptr)

    .return DUPL_RETURN_SUCCESS

OUTPUTMANAGER::MakeRTV endp

;
; Set new viewport
;
OUTPUTMANAGER::SetViewPort proc Width:UINT, Height:UINT

   .new VP:D3D11_VIEWPORT

    cvtsi2ss xmm0,edx
    cvtsi2ss xmm1,r8d
    movss VP.Width,xmm0
    movss VP.Height,xmm1
    mov VP.MinDepth,0.0
    mov VP.MaxDepth,1.0
    mov VP.TopLeftX,0
    mov VP.TopLeftY,0

    this.m_DeviceContext.RSSetViewports(1, &VP)
    ret

OUTPUTMANAGER::SetViewPort endp

;
; Resize swapchain
;
OUTPUTMANAGER::ResizeSwapChain proc uses rsi

    mov rsi,rcx

    SafeRelease([rsi].m_RTV)

   .new WindowRect:RECT
    GetClientRect([rsi].m_WindowHandle, &WindowRect)

    mov eax,WindowRect.right
    sub eax,WindowRect.left
    mov ecx,WindowRect.bottom
    sub ecx,WindowRect.top
   .new Width:UINT = eax
   .new Height:UINT = ecx

    ; Resize swapchain

   .new SwapChainDesc:DXGI_SWAP_CHAIN_DESC
    this.m_SwapChain.GetDesc(&SwapChainDesc)

   .new hr:HRESULT = this.m_SwapChain.ResizeBuffers(
            SwapChainDesc.BufferCount,
            Width,
            Height,
            SwapChainDesc.BufferDesc.Format,
            SwapChainDesc.Flags)

    .if (FAILED(hr))

        .return ProcessFailure([rsi].m_Device,
                L"Failed to resize swapchain buffers in OUTPUTMANAGER",
                L"Error", hr, &SystemTransitionsExpectedErrors)
    .endif

    ; Make new render target view

    .new retval:DUPL_RETURN = this.MakeRTV()
    .if ( retval != DUPL_RETURN_SUCCESS )

        .return retval
    .endif

    ; Set new viewport

    this.SetViewPort(Width, Height)
   .return retval

OUTPUTMANAGER::ResizeSwapChain endp

;
; Releases all references
;
OUTPUTMANAGER::CleanRefs proc uses rsi

    mov rsi,rcx
    SafeRelease([rsi].m_VertexShader)
    SafeRelease([rsi].m_PixelShader)
    SafeRelease([rsi].m_InputLayout)
    SafeRelease([rsi].m_RTV)
    SafeRelease([rsi].m_SamplerLinear)
    SafeRelease([rsi].m_BlendState)
    SafeRelease([rsi].m_DeviceContext)
    SafeRelease([rsi].m_Device)
    SafeRelease([rsi].m_SwapChain)
    SafeRelease([rsi].m_SharedSurf)
    SafeRelease([rsi].m_KeyMutex)
    .if ([rsi].m_Factory)
        .if ([rsi].m_OcclusionCookie)
            this.m_Factory.UnregisterOcclusionStatus([rsi].m_OcclusionCookie)
            mov [rsi].m_OcclusionCookie,0
        .endif
        this.m_Factory.Release()
        mov [rsi].m_Factory,nullptr
    .endif
    ret

OUTPUTMANAGER::CleanRefs endp

    end
