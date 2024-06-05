
include ThreadManager.inc

DDProc proto :ptr

    .code

    assume rsi:ptr THREADMANAGER

THREADMANAGER::THREADMANAGER proc

    @ComAlloc(THREADMANAGER)
    ret

THREADMANAGER::THREADMANAGER endp


THREADMANAGER::Release proc

    this.Clean()
    free(this)
    ret

THREADMANAGER::Release endp

;
; Clean up resources
;
THREADMANAGER::Clean proc uses rsi rdi rbx

    ldr rsi,this
    .if ( [rsi].m_PtrInfo.PtrShapeBuffer )

        free([rsi].m_PtrInfo.PtrShapeBuffer)
        mov [rsi].m_PtrInfo.PtrShapeBuffer,nullptr
    .endif

    RtlZeroMemory(&[rsi].m_PtrInfo, sizeof(PTR_INFO))

    mov rdi,[rsi].m_ThreadHandles

    .if ( rdi )

        .for ( ebx = 0: ebx < [rsi].m_ThreadCount: ++ebx, rdi += HANDLE )

            mov rcx,[rdi]
            .if ( rcx )

                CloseHandle(rcx)
            .endif
        .endf

        free([rsi].m_ThreadHandles)
        mov [rsi].m_ThreadHandles,nullptr
    .endif

    assume rdi:ptr THREAD_DATA
    .if ( [rsi].m_ThreadData )

        mov rdi,[rsi].m_ThreadData
        .for ( ebx = 0: ebx < [rsi].m_ThreadCount: ++ebx, rdi += THREAD_DATA )

            this.CleanDx(&[rdi].DxRes)
        .endf

        free([rsi].m_ThreadData)
        mov [rsi].m_ThreadData,nullptr
    .endif
    mov [rsi].m_ThreadCount,0
    ret

THREADMANAGER::Clean endp

;
; Clean up DX_RESOURCES
;
    assume rdi:ptr DX_RESOURCES

THREADMANAGER::CleanDx proc uses rdi Data:ptr DX_RESOURCES

    ldr rdi,Data
    SafeRelease([rdi].Device)
    SafeRelease([rdi].Context)
    SafeRelease([rdi].VertexShader)
    SafeRelease([rdi].PixelShader)
    SafeRelease([rdi].InputLayout)
    SafeRelease([rdi].SamplerLinear)
    ret

THREADMANAGER::CleanDx endp

    assume rdi:nothing

;
; Start up threads for DDA
;
THREADMANAGER::Initialize proc uses rsi rdi rbx SingleOutput:SINT, OutputCount:UINT,
        UnexpectedErrorEvent:HANDLE, ExpectedErrorEvent:HANDLE,
        TerminateThreadsEvent:HANDLE, SharedHandle:HANDLE, DesktopDim:ptr RECT

    ldr rsi,this
    ldr ecx,OutputCount

    mov [rsi].m_ThreadCount,ecx ; OutputCount

    imul ecx,ecx,HANDLE
    mov [rsi].m_ThreadHandles,malloc(rcx)

    imul ecx,[rsi].m_ThreadCount,THREAD_DATA
    mov [rsi].m_ThreadData,malloc(rcx)

    .if ( ![rsi].m_ThreadHandles || ![rsi].m_ThreadData )

        .return ProcessFailure(nullptr, L"Failed to allocate array for threads",
                L"Error", E_OUTOFMEMORY, nullptr)
    .endif

    ; Create appropriate # of threads for duplication

   .new retval:DUPL_RETURN = DUPL_RETURN_SUCCESS

    assume rdi:ptr THREAD_DATA

    mov rdi,[rsi].m_ThreadData

    .for ( ebx = 0: ebx < [rsi].m_ThreadCount: ++ebx, rdi += THREAD_DATA )

        mov [rdi].UnexpectedErrorEvent,UnexpectedErrorEvent
        mov [rdi].ExpectedErrorEvent,ExpectedErrorEvent
        mov [rdi].TerminateThreadsEvent,TerminateThreadsEvent

        mov eax,SingleOutput
        .ifs ( eax < 0 )
            mov eax,ebx
        .endif
        mov [rdi].Output,eax
        mov [rdi].TexSharedHandle,SharedHandle
        mov rcx,DesktopDim
        mov [rdi].OffsetX,[rcx].RECT.left
        mov [rdi].OffsetY,[rcx].RECT.top
        mov [rdi].PtrInfo,&[rsi].m_PtrInfo

        RtlZeroMemory(&[rdi].DxRes, sizeof(DX_RESOURCES))
        mov retval,this.InitializeDx(&[rdi].DxRes)

        .if ( retval != DUPL_RETURN_SUCCESS )

            .return retval
        .endif

       .new ThreadId:DWORD

        CreateThread(nullptr, 0, &DDProc, rdi, 0, &ThreadId)

        mov rcx,[rsi].m_ThreadHandles
        mov [rcx+rbx*HANDLE],rax

        .if ( rax == nullptr )

            .return ProcessFailure(nullptr, L"Failed to create thread",
                    L"Error", E_FAIL, nullptr)
        .endif
    .endf
    .return retval

THREADMANAGER::Initialize endp

;
; Get DX_RESOURCES
;
THREADMANAGER::InitializeDx proc uses rsi rdi rbx Data:ptr DX_RESOURCES

    ldr rsi,this
    ldr rdx,Data

    .new hr:HRESULT = S_OK

    ; Driver types supported

    .new DriverTypes[3]:D3D_DRIVER_TYPE = {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE
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

    assume rdi:ptr DX_RESOURCES

    .for ( rdi = rdx, ebx = 0: ebx < NumDriverTypes: ++ebx )

        mov hr,D3D11CreateDevice(
                nullptr,
                DriverTypes[rbx*4],
                nullptr,
                0,
                &FeatureLevels,
                NumFeatureLevels,
                D3D11_SDK_VERSION,
                &[rdi].Device,
                &FeatureLevel,
                &[rdi].Context)

        .if (SUCCEEDED(hr))

            ; Device creation success, no need to loop anymore

            .break
        .endif
    .endf
    .if (FAILED(hr))

        .return ProcessFailure(nullptr,
                L"Failed to create device in InitializeDx",
                L"Error", hr, nullptr)
    .endif

    ; VERTEX shader

   .new pDevice:ptr ID3D11Device = [rdi].Device
    mov hr,pDevice.CreateVertexShader(&g_VS, g_VS_size, nullptr, &[rdi].VertexShader)
    .if (FAILED(hr))

        .return ProcessFailure([rdi].Device,
                L"Failed to create vertex shader in InitializeDx",
                L"Error", hr, &SystemTransitionsExpectedErrors)
    .endif

    ; Input layout

    .new Layout[2]:D3D11_INPUT_ELEMENT_DESC = {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
        }

   .new NumElements:UINT = ARRAYSIZE(Layout)
    mov hr,pDevice.CreateInputLayout(
            &Layout, NumElements, &g_VS, g_VS_size, &[rdi].InputLayout)
    .if (FAILED(hr))

        .return ProcessFailure([rdi].Device,
                L"Failed to create input layout in InitializeDx",
                L"Error", hr, &SystemTransitionsExpectedErrors)
    .endif

   .new pContext:ptr ID3D11DeviceContext = [rdi].Context
    pContext.IASetInputLayout([rdi].InputLayout)

    ; Pixel shader

    mov hr,pDevice.CreatePixelShader(&g_PS, g_PS_size, nullptr, &[rdi].PixelShader)
    .if (FAILED(hr))

        .return ProcessFailure([rdi].Device,
                L"Failed to create pixel shader in InitializeDx",
                L"Error", hr, &SystemTransitionsExpectedErrors)
    .endif

    ; Set up sampler

   .new SampDesc:D3D11_SAMPLER_DESC = {0}
    mov SampDesc.Filter,D3D11_FILTER_MIN_MAG_MIP_LINEAR
    mov SampDesc.AddressU,D3D11_TEXTURE_ADDRESS_CLAMP
    mov SampDesc.AddressV,D3D11_TEXTURE_ADDRESS_CLAMP
    mov SampDesc.AddressW,D3D11_TEXTURE_ADDRESS_CLAMP
    mov SampDesc.ComparisonFunc,D3D11_COMPARISON_NEVER
    mov SampDesc.MinLOD,0
    mov SampDesc.MaxLOD,D3D11_FLOAT32_MAX
    mov hr,pDevice.CreateSamplerState(&SampDesc, &[rdi].SamplerLinear)

    .if (FAILED(hr))

        .return ProcessFailure([rdi].Device,
                L"Failed to create sampler state in InitializeDx",
                L"Error", hr, &SystemTransitionsExpectedErrors)
    .endif
    .return DUPL_RETURN_SUCCESS

THREADMANAGER::InitializeDx endp

;
; Getter for the PTR_INFO structure
;
THREADMANAGER::GetPointerInfo proc

    ldr rcx,this

    .return &[rcx].THREADMANAGER.m_PtrInfo

THREADMANAGER::GetPointerInfo endp

;
; Waits infinitely for all spawned threads to terminate
;
THREADMANAGER::WaitForThreadTermination proc

    ldr rcx,this

    .if ( [rcx].THREADMANAGER.m_ThreadCount != 0 )

        WaitForMultipleObjectsEx(
                [rcx].THREADMANAGER.m_ThreadCount,
                [rcx].THREADMANAGER.m_ThreadHandles,
                TRUE,
                INFINITE,
                FALSE)
    .endif
    ret

THREADMANAGER::WaitForThreadTermination endp

    end
