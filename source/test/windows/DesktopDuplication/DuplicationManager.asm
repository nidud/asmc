
include DuplicationManager.inc

.code

; Constructor sets up references / variables

DUPLICATIONMANAGER::DUPLICATIONMANAGER proc
    @ComAlloc(DUPLICATIONMANAGER)
    ret
    endp

    assume class:rsi
;
; Destructor simply calls CleanRefs to destroy everything
;
DUPLICATIONMANAGER::Release proc

    SafeRelease(m_DeskDupl)
    SafeRelease(m_AcquiredDesktopImage)
    .if ( m_MetaDataBuffer )
        free(m_MetaDataBuffer)
        mov m_MetaDataBuffer,nullptr
    .endif
    SafeRelease(m_Device)
    free(rsi)
    ret
    endp

;
; Initialize duplication interfaces
;
DUPLICATIONMANAGER::InitDupl proc Device:ptr ID3D11Device, Output:UINT

    ldr rdx,Device
    ldr eax,Output

    mov m_OutputNumber,eax

    ; Take a reference on the device

    mov m_Device,rdx
    Device.AddRef()

    ; Get DXGI device

    .new DxgiDevice:ptr IDXGIDevice = nullptr
    .new hr:HRESULT = Device.QueryInterface(&IID_IDXGIDevice, &DxgiDevice)
    .if (FAILED(hr))

        .return ProcessFailure(nullptr,
                L"Failed to QI for DXGI Device",
                L"Error", hr, nullptr)
    .endif

    ; Get DXGI adapter

   .new DxgiAdapter:ptr IDXGIAdapter = nullptr
    mov hr,DxgiDevice.GetParent(&IID_IDXGIAdapter, &DxgiAdapter)
    DxgiDevice.Release()
    mov DxgiDevice,nullptr
    .if (FAILED(hr))

        .return ProcessFailure(Device,
                L"Failed to get parent DXGI Adapter",
                L"Error", hr, &SystemTransitionsExpectedErrors)
    .endif

    ; Get output

   .new DxgiOutput:ptr IDXGIOutput = nullptr
    mov hr,DxgiAdapter.EnumOutputs(Output, &DxgiOutput)
    DxgiAdapter.Release()
    mov DxgiAdapter,nullptr
    .if (FAILED(hr))

        .return ProcessFailure(Device,
                L"Failed to get specified output in DUPLICATIONMANAGER",
                L"Error", hr, &EnumOutputsExpectedErrors)
    .endif

    DxgiOutput.GetDesc(&m_OutputDesc)

    ; QI for Output 1

   .new DxgiOutput1:ptr IDXGIOutput1 = nullptr
    mov hr,DxgiOutput.QueryInterface(&IID_IDXGIOutput1, &DxgiOutput1)
    DxgiOutput.Release()
    mov DxgiOutput,nullptr
    .if (FAILED(hr))

        .return ProcessFailure(nullptr,
                L"Failed to QI for DxgiOutput1 in DUPLICATIONMANAGER",
                L"Error", hr, nullptr)
    .endif

    ; Create desktop duplication

    mov hr,DxgiOutput1.DuplicateOutput(Device, &m_DeskDupl)
    DxgiOutput1.Release()
    mov DxgiOutput1,nullptr
    .if (FAILED(hr))

        .if ( hr == DXGI_ERROR_NOT_CURRENTLY_AVAILABLE )

            MessageBoxW(nullptr,
                    L"There is already the maximum number of applications using" \
                    " the Desktop Duplication API running, please close one of" \
                    " those applications and then try again.",
                    L"Error", MB_OK)
            .return DUPL_RETURN_ERROR_UNEXPECTED
        .endif
        .return ProcessFailure(Device,
                L"Failed to get duplicate output in DUPLICATIONMANAGER",
                L"Error", hr, &CreateDuplicationExpectedErrors)
    .endif
    .return DUPL_RETURN_SUCCESS
    endp

;
; Retrieves mouse info and write it into PtrInfo
;
DUPLICATIONMANAGER::GetMouse proc uses rdi rbx \
        PtrInfo     : ptr PTR_INFO,
        FrameInfo   : ptr DXGI_OUTDUPL_FRAME_INFO,
        OffsetX     : SINT,
        OffsetY     : SINT

    ldr rdi,PtrInfo
    ldr rbx,FrameInfo

    assume rdi:ptr PTR_INFO
    assume rbx:ptr DXGI_OUTDUPL_FRAME_INFO

    ; A non-zero mouse update timestamp indicates that there is a mouse position
    ; update and optionally a shape change

ifdef _WIN64
    .if ( [rbx].LastMouseUpdateTime.QuadPart == 0 )
else
    .if ( dword ptr [rbx].LastMouseUpdateTime.QuadPart == 0 )
endif
        .return DUPL_RETURN_SUCCESS
    .endif

    .new UpdatePosition:bool = true

    ; Make sure we don't update pointer position wrongly
    ; If pointer is invisible, make sure we did not get an update from another
    ; output that the last time that said pointer was visible, if so, don't set
    ; it to invisible or update.

    .if ( ![rbx].PointerPosition.Visible &&
         ( [rdi].WhoUpdatedPositionLast != m_OutputNumber ) )

        mov UpdatePosition,false
    .endif

    ; If two outputs both say they have a visible,
    ; only update if new update has newer timestamp

    .if ( [rbx].PointerPosition.Visible && [rdi].Visible &&
          ( [rdi].WhoUpdatedPositionLast != m_OutputNumber ) &&
          ( [rdi].LastTimeStamp.QuadPart > [rbx].LastMouseUpdateTime.QuadPart ) )

        mov UpdatePosition,false
    .endif

    ; Update position

    .if ( UpdatePosition )

        mov eax,[rbx].PointerPosition.Position.x
        add eax,m_OutputDesc.DesktopCoordinates.left
        sub eax,OffsetX
        mov [rdi].Position.x,eax
        mov eax,[rbx].PointerPosition.Position.y
        add eax,m_OutputDesc.DesktopCoordinates.top
        sub eax,OffsetY
        mov [rdi].Position.y,eax
        mov [rdi].WhoUpdatedPositionLast,m_OutputNumber
        mov [rdi].LastTimeStamp,[rbx].LastMouseUpdateTime
        xor eax,eax
        .if ( [rbx].PointerPosition.Visible != 0 )
            inc eax
        .endif
        mov [rdi].Visible,eax
    .endif

    ; No new shape

    .if ( [rbx].PointerShapeBufferSize == 0 )

        .return DUPL_RETURN_SUCCESS
    .endif

    ; Old buffer too small

    .if ( [rbx].PointerShapeBufferSize > [rdi].BufferSize )

        .if ( [rdi].PtrShapeBuffer )

            free([rdi].PtrShapeBuffer)
            mov [rdi].PtrShapeBuffer,nullptr
        .endif
        mov [rdi].PtrShapeBuffer,malloc([rbx].PointerShapeBufferSize)

        .if ( !rax )

            mov [rdi].BufferSize,eax
            .return ProcessFailure(nullptr,
                    L"Failed to allocate memory for pointer shape in DUPLICATIONMANAGER",
                    L"Error", E_OUTOFMEMORY, nullptr)
        .endif

        ; Update buffer size

        mov [rdi].BufferSize,[rbx].PointerShapeBufferSize
    .endif

    ; Get shape

    .new BufferSizeRequired:UINT
    .new hr:HRESULT = m_DeskDupl.GetFramePointerShape(
            [rbx].PointerShapeBufferSize, [rdi].PtrShapeBuffer,
            &BufferSizeRequired, &[rdi].ShapeInfo)

    .if (FAILED(hr))

        free([rdi].PtrShapeBuffer)

        mov [rdi].PtrShapeBuffer,nullptr
        mov [rdi].BufferSize,0

        .return ProcessFailure(m_Device,
            L"Failed to get frame pointer shape in DUPLICATIONMANAGER",
            L"Error", hr, &FrameInfoExpectedErrors)
    .endif
    .return DUPL_RETURN_SUCCESS
    endp


;
; Get next frame and write it into Data
;

DUPLICATIONMANAGER::GetFrame proc uses rdi Data:ptr FRAME_DATA, Timeout:ptr bool

    ldr rdi,Data

    assume rdi:ptr FRAME_DATA

    .new DesktopResource:ptr IDXGIResource = nullptr
    .new FrameInfo:DXGI_OUTDUPL_FRAME_INFO

    ; Get new frame

    .new hr:HRESULT = m_DeskDupl.AcquireNextFrame(
            500, &FrameInfo, &DesktopResource)

    mov rcx,Timeout
    .if ( hr == DXGI_ERROR_WAIT_TIMEOUT )

        mov bool ptr [rcx],true
       .return DUPL_RETURN_SUCCESS
    .endif
    mov bool ptr [rcx],false

    .if (FAILED(hr))

        .return ProcessFailure(m_Device,
                L"Failed to acquire next frame in DUPLICATIONMANAGER",
                L"Error", hr, &FrameInfoExpectedErrors)
    .endif

    ; If still holding old frame, destroy it

    SafeRelease(m_AcquiredDesktopImage)

    ; QI for IDXGIResource

    mov hr,DesktopResource.QueryInterface(&IID_ID3D11Texture2D, &m_AcquiredDesktopImage)
    SafeRelease(DesktopResource)
    .if (FAILED(hr))

        .return ProcessFailure(nullptr,
                L"Failed to QI for ID3D11Texture2D from acquired IDXGIResource in DUPLICATIONMANAGER",
                L"Error", hr, nullptr)
    .endif

    ; Get metadata

    .if ( FrameInfo.TotalMetadataBufferSize )

        ; Old buffer too small

        .if ( FrameInfo.TotalMetadataBufferSize > m_MetaDataSize )

            .if ( m_MetaDataBuffer )

                free(m_MetaDataBuffer)
                mov m_MetaDataBuffer,nullptr
            .endif

            mov m_MetaDataBuffer,malloc(FrameInfo.TotalMetadataBufferSize)

            .if ( !rax )

                mov m_MetaDataSize,eax
                mov [rdi].MoveCount,eax
                mov [rdi].DirtyCount,eax

                .return ProcessFailure(nullptr,
                        L"Failed to allocate memory for metadata in DUPLICATIONMANAGER",
                        L"Error", E_OUTOFMEMORY, nullptr)
            .endif
            mov m_MetaDataSize,FrameInfo.TotalMetadataBufferSize
        .endif

        .new BufSize:UINT = FrameInfo.TotalMetadataBufferSize

        ; Get move rectangles

        mov hr,m_DeskDupl.GetFrameMoveRects(BufSize, m_MetaDataBuffer, &BufSize)
        .if (FAILED(hr))

            mov [rdi].MoveCount,0
            mov [rdi].DirtyCount,0

            .return ProcessFailure(nullptr,
                    L"Failed to get frame move rects in DUPLICATIONMANAGER",
                    L"Error", hr, &FrameInfoExpectedErrors)
        .endif

        mov eax,BufSize
        mov ecx,sizeof(DXGI_OUTDUPL_MOVE_RECT)
        xor edx,edx
        div ecx
        mov [rdi].MoveCount,eax

        mov eax,BufSize
        add rax,m_MetaDataBuffer
       .new DirtyRects:ptr BYTE = rax

        mov eax,FrameInfo.TotalMetadataBufferSize
        sub eax,BufSize
        mov BufSize,eax

        ; Get dirty rectangles

        mov hr,m_DeskDupl.GetFrameDirtyRects(BufSize, DirtyRects, &BufSize)
        .if (FAILED(hr))

            mov [rdi].MoveCount,0
            mov [rdi].DirtyCount,0

            .return ProcessFailure(nullptr,
                    L"Failed to get frame dirty rects in DUPLICATIONMANAGER",
                    L"Error", hr, &FrameInfoExpectedErrors)
        .endif
        mov eax,BufSize
        shr eax,4
        mov [rdi].DirtyCount,eax
        mov [rdi].MetaData,m_MetaDataBuffer
    .endif
    mov [rdi].tFrame,m_AcquiredDesktopImage
    mov [rdi].FrameInfo,FrameInfo
    .return DUPL_RETURN_SUCCESS
    endp


; Release frame

DUPLICATIONMANAGER::DoneWithFrame proc

    .new hr:HRESULT = m_DeskDupl.ReleaseFrame()
    .if (FAILED(hr))

        .return ProcessFailure(m_Device,
                L"Failed to release frame in DUPLICATIONMANAGER",
                L"Error", hr, &FrameInfoExpectedErrors)
    .endif

    SafeRelease(m_AcquiredDesktopImage)
    .return DUPL_RETURN_SUCCESS
    endp


; Gets output desc into DescPtr

DUPLICATIONMANAGER::GetOutputDesc proc uses rdi DescPtr:ptr DXGI_OUTPUT_DESC

    ldr rdi,DescPtr
    lea rsi,m_OutputDesc
    mov ecx,DXGI_OUTPUT_DESC
    rep movsb
    ret
    endp

    end
