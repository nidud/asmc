
include DisplayManager.inc

    .code

    assume class:rbx
;
; Constructor NULLs out vars
;
DISPLAYMANAGER::DISPLAYMANAGER proc

    @ComAlloc(DISPLAYMANAGER)
    ret

DISPLAYMANAGER::DISPLAYMANAGER endp

;
; Destructor calls CleanRefs to destroy everything
;
DISPLAYMANAGER::Release proc

    CleanRefs()

    .if ( m_DirtyVertexBufferAlloc )

        free(m_DirtyVertexBufferAlloc)
        mov m_DirtyVertexBufferAlloc,nullptr
    .endif
    free(rbx)
    ret

DISPLAYMANAGER::Release endp

;
; Initialize D3D variables
;
DISPLAYMANAGER::InitD3D proc Data:ptr DX_RESOURCES

    ldr rdx,Data

    mov m_Device,         [rdx].DX_RESOURCES.Device
    mov m_DeviceContext,  [rdx].DX_RESOURCES.Context
    mov m_VertexShader,   [rdx].DX_RESOURCES.VertexShader
    mov m_PixelShader,    [rdx].DX_RESOURCES.PixelShader
    mov m_InputLayout,    [rdx].DX_RESOURCES.InputLayout
    mov m_SamplerLinear,  [rdx].DX_RESOURCES.SamplerLinear

    m_Device.AddRef()
    m_DeviceContext.AddRef()
    m_VertexShader.AddRef()
    m_PixelShader.AddRef()
    m_InputLayout.AddRef()
    m_SamplerLinear.AddRef()
    ret

DISPLAYMANAGER::InitD3D endp

;
; Process a given frame and its metadata
;
DISPLAYMANAGER::ProcessFrame proc uses rsi rdi Data:ptr FRAME_DATA,
        SharedSurf:ptr ID3D11Texture2D, OffsetX:SINT, OffsetY:SINT,
        DeskDesc:ptr DXGI_OUTPUT_DESC

   .new retval:DUPL_RETURN = DUPL_RETURN_SUCCESS

    ; Process dirties and moves

    ldr rdi,Data

    assume rdi:ptr FRAME_DATA

    .if ( [rdi].FrameInfo.TotalMetadataBufferSize )

       .new Desc:D3D11_TEXTURE2D_DESC
        Data.tFrame.GetDesc(&Desc)

        .if ( [rdi].MoveCount )

            mov retval,CopyMove(SharedSurf, [rdi].MetaData, [rdi].MoveCount,
                    OffsetX, OffsetY, DeskDesc, Desc.Width, Desc.Height)

            .if ( retval != DUPL_RETURN_SUCCESS )

                .return retval
            .endif
        .endif

        .if ( [rdi].DirtyCount )

            imul ecx,[rdi].MoveCount,sizeof(DXGI_OUTDUPL_MOVE_RECT)
            add rcx,[rdi].MetaData
            mov retval,CopyDirty([rdi].tFrame, SharedSurf, rcx,
                    [rdi].DirtyCount, OffsetX, OffsetY, DeskDesc)
        .endif
    .endif
    .return retval

DISPLAYMANAGER::ProcessFrame endp

;
; returns D3D device being used
;
DISPLAYMANAGER::GetDevice proc

    .return( m_Device )

DISPLAYMANAGER::GetDevice endp

;
; Set appropriate source and destination rects for move rects
;
DISPLAYMANAGER::SetMoveRect proc uses rsi \
        SrcRect   : ptr RECT,
        DestRect  : ptr RECT,
        DeskDesc  : ptr DXGI_OUTPUT_DESC,
        MoveRect  : ptr DXGI_OUTDUPL_MOVE_RECT,
        TexWidth  : SINT,
        TexHeight : SINT

    ldr rdx,SrcRect
    ldr rcx,DestRect
    ldr rax,DeskDesc

    mov rsi,MoveRect

    assume rsi:ptr DXGI_OUTDUPL_MOVE_RECT

    .switch ( [rax].DXGI_OUTPUT_DESC.Rotation )

    .case DXGI_MODE_ROTATION_UNSPECIFIED
    .case DXGI_MODE_ROTATION_IDENTITY

        mov [rdx].RECT.left,[rsi].SourcePoint.x
        add eax,[rsi].DestinationRect.right
        sub eax,[rsi].DestinationRect.left
        mov [rdx].RECT.right,eax
        mov [rdx].RECT.top,[rsi].SourcePoint.y
        add eax,[rsi].DestinationRect.bottom
        sub eax,[rsi].DestinationRect.top
        mov [rdx].RECT.bottom,eax
        mov [rcx],[rsi].DestinationRect
       .endc

    .case DXGI_MODE_ROTATION_ROTATE90

        mov eax,TexHeight
        sub eax,[rsi].SourcePoint.y
        sub eax,[rsi].DestinationRect.bottom
        add eax,[rsi].DestinationRect.top
        mov [rdx].RECT.left,eax
        mov eax,TexHeight
        sub eax,[rsi].SourcePoint.y
        mov [rdx].RECT.right,eax
        mov [rdx].RECT.top,[rsi].SourcePoint.x
        add eax,[rsi].DestinationRect.right
        sub eax,[rsi].DestinationRect.left
        mov [rdx].RECT.bottom,eax

        mov eax,TexHeight
        sub eax,[rsi].DestinationRect.bottom
        mov [rcx].RECT.left,eax
        mov [rcx].RECT.top,[rsi].DestinationRect.left
        mov eax,TexHeight
        sub eax,[rsi].DestinationRect.top
        mov [rcx].RECT.right,eax
        mov [rcx].RECT.bottom,[rsi].DestinationRect.right
       .endc

    .case DXGI_MODE_ROTATION_ROTATE180

        mov eax,TexWidth
        sub eax,[rsi].SourcePoint.x
        sub eax,[rsi].DestinationRect.right
        add eax,[rsi].DestinationRect.left
        mov [rdx].RECT.left,eax
        mov eax,TexHeight
        sub eax,[rsi].SourcePoint.y
        sub eax,[rsi].DestinationRect.bottom
        add eax,[rsi].DestinationRect.top
        mov [rdx].RECT.top,eax
        mov eax,TexWidth
        sub eax,[rsi].SourcePoint.x
        mov [rdx].RECT.right,eax
        mov eax,TexHeight
        sub eax,[rsi].SourcePoint.y
        mov [rdx].RECT.bottom,eax

        mov eax,TexWidth
        sub eax,[rsi].DestinationRect.right
        mov [rcx].RECT.left,eax
        mov eax,TexHeight
        sub eax,[rsi].DestinationRect.bottom
        mov [rcx].RECT.top,eax
        mov eax,TexWidth
        sub eax,[rsi].DestinationRect.left
        mov [rcx].RECT.right,eax
        mov eax,TexHeight
        sub eax,[rsi].DestinationRect.top
        mov [rcx].RECT.bottom,eax
       .endc

    .case DXGI_MODE_ROTATION_ROTATE270

        mov [rdx].RECT.left,[rsi].SourcePoint.x
        mov eax,TexWidth
        sub eax,[rsi].DestinationRect.right
        add eax,[rsi].DestinationRect.left
        mov [rdx].RECT.top,eax
        mov eax,[rsi].SourcePoint.y
        add eax,[rsi].DestinationRect.bottom
        sub eax,[rsi].DestinationRect.top
        mov [rdx].RECT.right,eax
        mov eax,TexWidth
        sub eax,[rsi].SourcePoint.x
        mov [rdx].RECT.bottom,eax

        mov [rcx].RECT.left,[rsi].DestinationRect.top
        mov eax,TexWidth
        sub eax,[rsi].DestinationRect.right
        mov [rcx].RECT.top,eax
        mov [rcx].RECT.right,[rsi].DestinationRect.bottom
        mov eax,TexWidth
        sub eax,[rsi].DestinationRect.left
        mov [rcx].RECT.bottom,eax
       .endc

    .default
        xor eax,eax
        mov [rcx],rax
        mov [rcx+8],rax
        mov [rdx],rax
        mov [rdx+8],rax
ifndef _WIN64
        mov [ecx+4],eax
        mov [ecx+12],eax
        mov [edx+4],eax
        mov [edx+12],eax
endif
       .endc
    .endsw
    ret

DISPLAYMANAGER::SetMoveRect endp

;
; Copy move rectangles
;
DISPLAYMANAGER::CopyMove proc uses rsi rdi \
        SharedSurf  : ptr ID3D11Texture2D,
        MoveBuffer  : ptr DXGI_OUTDUPL_MOVE_RECT,
        MoveCount   : UINT,
        OffsetX     : SINT,
        OffsetY     : SINT,
        DeskDesc    : ptr DXGI_OUTPUT_DESC,
        TexWidth    : SINT,
        TexHeight   : SINT

    mov rdi,DeskDesc
    assume rdi:ptr DXGI_OUTPUT_DESC

   .new FullDesc:D3D11_TEXTURE2D_DESC
    SharedSurf.GetDesc(&FullDesc)

    ; Make new intermediate surface to copy into for moving

    .if ( !m_MoveSurf )

       .new MoveDesc:D3D11_TEXTURE2D_DESC = FullDesc

        mov eax,[rdi].DesktopCoordinates.right
        sub eax,[rdi].DesktopCoordinates.left
        mov MoveDesc.Width,eax
        mov eax,[rdi].DesktopCoordinates.bottom
        sub eax,[rdi].DesktopCoordinates.top
        mov MoveDesc.Height,eax
        mov MoveDesc.BindFlags,D3D11_BIND_RENDER_TARGET
        mov MoveDesc.MiscFlags,0

        .new hr:HRESULT = m_Device.CreateTexture2D(&MoveDesc, nullptr, &m_MoveSurf)
        .if (FAILED(hr))

            .return ProcessFailure(m_Device,
                    L"Failed to create staging texture for move rects",
                    L"Error", hr, &SystemTransitionsExpectedErrors)
        .endif
    .endif

    .for ( esi = 0: esi < MoveCount: ++esi )

       .new SrcRect:RECT
       .new DestRect:RECT

        imul ecx,esi,DXGI_OUTDUPL_MOVE_RECT
        add rcx,MoveBuffer
        SetMoveRect(&SrcRect, &DestRect, DeskDesc, rcx, TexWidth, TexHeight)

        ; Copy rect out of shared surface

       .new Box:D3D11_BOX

        mov eax,SrcRect.left
        add eax,[rdi].DesktopCoordinates.left
        sub eax,OffsetX
        mov Box.left,eax
        mov eax,SrcRect.top
        add eax,[rdi].DesktopCoordinates.top
        sub eax,OffsetY
        mov Box.top,eax
        mov Box.front,0
        mov eax,SrcRect.right
        add eax,[rdi].DesktopCoordinates.left
        sub eax,OffsetX
        mov Box.right,eax
        mov eax,SrcRect.bottom
        add eax,[rdi].DesktopCoordinates.top
        sub eax,OffsetY
        mov Box.bottom,eax
        mov Box.back,1

        m_DeviceContext.CopySubresourceRegion(m_MoveSurf, 0,
                SrcRect.left, SrcRect.top, 0, SharedSurf, 0, &Box)

        ; Copy back to shared surface

        mov Box.left,SrcRect.left
        mov Box.top,SrcRect.top
        mov Box.front,0
        mov Box.right,SrcRect.right
        mov Box.bottom,SrcRect.bottom
        mov Box.back,1

        mov edx,DestRect.left
        add edx,[rdi].DesktopCoordinates.left
        sub edx,OffsetX
        mov ecx,DestRect.top
        add ecx,[rdi].DesktopCoordinates.top
        sub ecx,OffsetY
        m_DeviceContext.CopySubresourceRegion(
                SharedSurf, 0, edx, ecx, 0, m_MoveSurf, 0, &Box)
    .endf
    .return DUPL_RETURN_SUCCESS

DISPLAYMANAGER::CopyMove endp

;
; Sets up vertices for dirty rects for rotated desktops
;
DISPLAYMANAGER::SetDirtyVert proc uses rsi rdi \
        Vertices    : ptr VERTEX,
        Dirty       : ptr RECT,
        OffsetX     : SINT,
        OffsetY     : SINT,
        DeskDesc    : ptr DXGI_OUTPUT_DESC,
        FullDesc    : ptr D3D11_TEXTURE2D_DESC,
        ThisDesc    : ptr D3D11_TEXTURE2D_DESC

    ldr rdx,Vertices
    mov rsi,FullDesc
    mov rdi,DeskDesc
    assume rsi:ptr D3D11_TEXTURE2D_DESC

    mov eax,[rsi].Width
    mov ecx,[rsi].Height
    shr eax,1
    shr ecx,1
   .new CenterX:SINT = eax
   .new CenterY:SINT = ecx

    mov eax,[rdi].DesktopCoordinates.right
    sub eax,[rdi].DesktopCoordinates.left
    mov ecx,[rdi].DesktopCoordinates.bottom
    sub ecx,[rdi].DesktopCoordinates.top
   .new Width:SINT = eax
   .new Height:SINT = ecx

    ; Rotation compensated destination rect

    ldr rcx,Dirty
   .new DestDirty:RECT = [rcx]

    ; Set appropriate coordinates compensated for rotation

    mov rsi,ThisDesc
    cvtsi2ss xmm4,[rsi].D3D11_TEXTURE2D_DESC.Width
    cvtsi2ss xmm5,[rsi].D3D11_TEXTURE2D_DESC.Height
    cvtsi2ss xmm0,[rcx].RECT.left
    cvtsi2ss xmm1,[rcx].RECT.right
    cvtsi2ss xmm2,[rcx].RECT.top
    cvtsi2ss xmm3,[rcx].RECT.bottom
    divss xmm0,xmm4 ; left / Width
    divss xmm1,xmm4 ; right / Width
    divss xmm2,xmm5 ; top / Height
    divss xmm3,xmm5 ; bottom / Height

    .switch ( [rdi].Rotation )

    .case DXGI_MODE_ROTATION_ROTATE90

        mov eax,Width
        sub eax,[rcx].RECT.bottom
        mov DestDirty.left,eax
        mov DestDirty.top,[rcx].RECT.left
        mov eax,Width
        sub eax,[rcx].RECT.top
        mov DestDirty.right,eax
        mov DestDirty.bottom,[rcx].RECT.right

        movss [rdx+VERTEX*0].VERTEX.TexCoord.x,xmm1 ; right / Width
        movss [rdx+VERTEX*0].VERTEX.TexCoord.y,xmm3 ; bottom / Height
        movss [rdx+VERTEX*1].VERTEX.TexCoord.x,xmm0 ; left / Width
        movss [rdx+VERTEX*1].VERTEX.TexCoord.y,xmm3 ; bottom / Height
        movss [rdx+VERTEX*2].VERTEX.TexCoord.x,xmm1 ; right / Width
        movss [rdx+VERTEX*2].VERTEX.TexCoord.y,xmm2 ; top / Height
        movss [rdx+VERTEX*5].VERTEX.TexCoord.x,xmm0 ; left / Width
        movss [rdx+VERTEX*5].VERTEX.TexCoord.y,xmm2 ; top / Height
       .endc

    .case DXGI_MODE_ROTATION_ROTATE180

        mov eax,Width
        sub eax,[rcx].RECT.right
        mov DestDirty.left,eax
        mov eax,Height
        sub eax,[rcx].RECT.bottom
        mov DestDirty.top,eax
        mov eax,Width
        sub eax,[rcx].RECT.left
        mov DestDirty.right,eax
        mov eax,Height
        sub eax,[rcx].RECT.top
        mov DestDirty.bottom,eax

        movss [rdx+VERTEX*0].VERTEX.TexCoord.x,xmm1 ; right / Width
        movss [rdx+VERTEX*0].VERTEX.TexCoord.y,xmm2 ; top / Height
        movss [rdx+VERTEX*1].VERTEX.TexCoord.x,xmm1 ; right / Width
        movss [rdx+VERTEX*1].VERTEX.TexCoord.y,xmm3 ; bottom / Height
        movss [rdx+VERTEX*2].VERTEX.TexCoord.x,xmm0 ; left / Width
        movss [rdx+VERTEX*2].VERTEX.TexCoord.y,xmm2 ; top / Height
        movss [rdx+VERTEX*5].VERTEX.TexCoord.x,xmm0 ; left / Width
        movss [rdx+VERTEX*5].VERTEX.TexCoord.y,xmm3 ; bottom / Height
       .endc

    .case DXGI_MODE_ROTATION_ROTATE270

        mov DestDirty.left,[rcx].RECT.top
        mov eax,Height
        sub eax,[rcx].RECT.right
        mov DestDirty.top,eax
        mov DestDirty.right,[rcx].RECT.bottom
        mov eax,Height
        sub eax,[rcx].RECT.left
        mov DestDirty.bottom,eax

        movss [rdx+VERTEX*0].VERTEX.TexCoord.x,xmm0 ; left / Width
        movss [rdx+VERTEX*0].VERTEX.TexCoord.y,xmm2 ; top / Height
        movss [rdx+VERTEX*1].VERTEX.TexCoord.x,xmm1 ; right / Width
        movss [rdx+VERTEX*1].VERTEX.TexCoord.y,xmm2 ; top / Height
        movss [rdx+VERTEX*2].VERTEX.TexCoord.x,xmm0 ; left / Width
        movss [rdx+VERTEX*2].VERTEX.TexCoord.y,xmm3 ; bottom / Height
        movss [rdx+VERTEX*5].VERTEX.TexCoord.x,xmm1 ; right / Width
        movss [rdx+VERTEX*5].VERTEX.TexCoord.y,xmm3 ; bottom / Height
       .endc

    .default
            ;assert(false); ; drop through
    .case DXGI_MODE_ROTATION_UNSPECIFIED
    .case DXGI_MODE_ROTATION_IDENTITY

        movss [rdx+VERTEX*0].VERTEX.TexCoord.x,xmm0 ; left / Width
        movss [rdx+VERTEX*0].VERTEX.TexCoord.y,xmm3 ; bottom / Height
        movss [rdx+VERTEX*1].VERTEX.TexCoord.x,xmm0 ; left / Width
        movss [rdx+VERTEX*1].VERTEX.TexCoord.y,xmm2 ; top / Height
        movss [rdx+VERTEX*2].VERTEX.TexCoord.x,xmm1 ; right / Width
        movss [rdx+VERTEX*2].VERTEX.TexCoord.y,xmm3 ; bottom / Height
        movss [rdx+VERTEX*5].VERTEX.TexCoord.x,xmm1 ; right / Width
        movss [rdx+VERTEX*5].VERTEX.TexCoord.y,xmm2 ; top / Height
       .endc
    .endsw

    ; Set positions

    cvtsi2ss    xmm0,DestDirty.left
    cvtsi2ss    xmm1,OffsetX
    cvtsi2ss    xmm2,CenterX
    cvtsi2ss    xmm3,[rdi].DesktopCoordinates.left
    addss       xmm0,xmm3
    subss       xmm0,xmm1
    subss       xmm0,xmm2
    divss       xmm0,xmm2
    movss       [rdx+VERTEX*0].VERTEX.Pos.x,xmm0
    movss       [rdx+VERTEX*1].VERTEX.Pos.x,xmm0
    cvtsi2ss    xmm0,DestDirty.right
    addss       xmm0,xmm3
    subss       xmm0,xmm1
    subss       xmm0,xmm2
    divss       xmm0,xmm2
    movss       [rdx+VERTEX*2].VERTEX.Pos.x,xmm0
    movss       [rdx+VERTEX*5].VERTEX.Pos.x,xmm0

    cvtsi2ss    xmm0,DestDirty.bottom
    cvtsi2ss    xmm1,OffsetY
    cvtsi2ss    xmm2,CenterY
    cvtsi2ss    xmm3,[rdi].DesktopCoordinates.top
    addss       xmm0,xmm3
    subss       xmm0,xmm1
    subss       xmm0,xmm2
    divss       xmm0,xmm2
    mulss       xmm0,-1.0
    movss       [rdx+VERTEX*0].VERTEX.Pos.y,xmm0
    movss       [rdx+VERTEX*2].VERTEX.Pos.y,xmm0
    cvtsi2ss    xmm0,DestDirty.top
    addss       xmm0,xmm3
    subss       xmm0,xmm1
    subss       xmm0,xmm2
    divss       xmm0,xmm2
    mulss       xmm0,-1.0
    movss       [rdx+VERTEX*1].VERTEX.Pos.y,xmm0
    movss       [rdx+VERTEX*5].VERTEX.Pos.y,xmm0

    mov         [rdx+VERTEX*0].VERTEX.Pos.z,0
    mov         [rdx+VERTEX*1].VERTEX.Pos.z,0
    mov         [rdx+VERTEX*2].VERTEX.Pos.z,0
    mov         [rdx+VERTEX*5].VERTEX.Pos.z,0
    mov         [rdx+VERTEX*3].VERTEX.Pos,[rdx+VERTEX*2].VERTEX.Pos
    mov         [rdx+VERTEX*4].VERTEX.Pos,[rdx+VERTEX*1].VERTEX.Pos
    mov         [rdx+VERTEX*3].VERTEX.TexCoord,[rdx+VERTEX*2].VERTEX.TexCoord
    mov         [rdx+VERTEX*4].VERTEX.TexCoord,[rdx+VERTEX*1].VERTEX.TexCoord
    ret

DISPLAYMANAGER::SetDirtyVert endp

;
; Copies dirty rectangles
;
DISPLAYMANAGER::CopyDirty proc uses rsi rdi \
        SrcSurface  : ptr ID3D11Texture2D,
        SharedSurf  : ptr ID3D11Texture2D,
        DirtyBuffer : ptr RECT,
        DirtyCount  : UINT,
        OffsetX     : SINT,
        OffsetY     : SINT,
        DeskDesc    : ptr DXGI_OUTPUT_DESC

   .new hr:HRESULT
   .new FullDesc:D3D11_TEXTURE2D_DESC

    SharedSurf.GetDesc(&FullDesc)

   .new ThisDesc:D3D11_TEXTURE2D_DESC
    SrcSurface.GetDesc(&ThisDesc)

    .if ( !m_RTV )

        mov hr,m_Device.CreateRenderTargetView(
                SharedSurf, nullptr, &m_RTV)
        .if (FAILED(hr))

            .return ProcessFailure(m_Device,
                    L"Failed to create render target view for dirty rects",
                    L"Error", hr, &SystemTransitionsExpectedErrors)
        .endif
    .endif

   .new ShaderDesc:D3D11_SHADER_RESOURCE_VIEW_DESC
    mov ShaderDesc.Format,ThisDesc.Format
    mov ShaderDesc.ViewDimension,D3D11_SRV_DIMENSION_TEXTURE2D
    mov ShaderDesc.Texture2D.MipLevels,ThisDesc.MipLevels
    dec eax
    mov ShaderDesc.Texture2D.MostDetailedMip,eax

    ; Create new shader resource view

   .new ShaderResource:ptr ID3D11ShaderResourceView = nullptr
    mov hr,m_Device.CreateShaderResourceView(
            SrcSurface, &ShaderDesc, &ShaderResource)
    .if (FAILED(hr))

        .return ProcessFailure(m_Device,
                L"Failed to create shader resource view for dirty rects",
                L"Error", hr, &SystemTransitionsExpectedErrors)
    .endif

   .new BlendFactor[4]:FLOAT = { 0.0, 0.0, 0.0, 0.0 }

    assume rsi:ptr ID3D11DeviceContext

    mov rsi,m_DeviceContext

    [rsi].OMSetBlendState(nullptr, &BlendFactor, 0xFFFFFFFF)
    [rsi].OMSetRenderTargets(1, &m_RTV, nullptr)
    [rsi].VSSetShader(m_VertexShader, nullptr, 0)
    [rsi].PSSetShader(m_PixelShader, nullptr, 0)
    [rsi].PSSetShaderResources(0, 1, &ShaderResource)
    [rsi].PSSetSamplers(0, 1, &m_SamplerLinear)
    [rsi].IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)

    assume rsi:nothing

    ; Create space for vertices for the dirty rects if the current space isn't large enough

    imul eax,DirtyCount,VERTEX * NUMVERTICES
   .new BytesNeeded:UINT = eax

    .if ( eax > m_DirtyVertexBufferAllocSize )

        .if ( m_DirtyVertexBufferAlloc )

            free(m_DirtyVertexBufferAlloc)
        .endif

        mov m_DirtyVertexBufferAlloc,malloc(BytesNeeded)
        .if ( !rax )

            mov m_DirtyVertexBufferAllocSize,eax
            .return ProcessFailure(nullptr,
                    L"Failed to allocate memory for dirty vertex buffer.",
                    L"Error", E_OUTOFMEMORY, nullptr)
        .endif

        mov m_DirtyVertexBufferAllocSize,BytesNeeded
    .endif

    ; Fill them in

    mov rdi,m_DirtyVertexBufferAlloc
    .for ( esi = 0: esi < DirtyCount: ++esi, rdi += (NUMVERTICES*VERTEX) )

        imul edx,esi,RECT
        add rdx,DirtyBuffer
        SetDirtyVert(rdi, rdx, OffsetX, OffsetY, DeskDesc, &FullDesc, &ThisDesc)
    .endf

    ; Create vertex buffer

   .new BufferDesc:D3D11_BUFFER_DESC = {0}
    mov BufferDesc.Usage,D3D11_USAGE_DEFAULT
    mov BufferDesc.ByteWidth,BytesNeeded
    mov BufferDesc.BindFlags,D3D11_BIND_VERTEX_BUFFER
    mov BufferDesc.CPUAccessFlags,0

   .new InitData:D3D11_SUBRESOURCE_DATA = {0}
    mov InitData.pSysMem,m_DirtyVertexBufferAlloc

   .new VertBuf:ptr ID3D11Buffer = nullptr
    mov hr,m_Device.CreateBuffer(&BufferDesc, &InitData, &VertBuf)
    .if (FAILED(hr))

        .return ProcessFailure(m_Device,
                L"Failed to create vertex buffer in dirty rect processing",
                L"Error", hr, &SystemTransitionsExpectedErrors)
    .endif

   .new Stride:UINT = sizeof(VERTEX)
   .new bOffset:UINT = 0
    m_DeviceContext.IASetVertexBuffers(0, 1, &VertBuf, &Stride, &bOffset)

   .new VP:D3D11_VIEWPORT
    cvtsi2ss xmm0,FullDesc.Width
    cvtsi2ss xmm1,FullDesc.Height
    movss VP.Width,xmm0
    movss VP.Height,xmm1
    mov VP.MinDepth,0.0
    mov VP.MaxDepth,1.0
    mov VP.TopLeftX,0.0
    mov VP.TopLeftY,0.0
    m_DeviceContext.RSSetViewports(1, &VP)

    imul edx,DirtyCount,NUMVERTICES
    m_DeviceContext.Draw(edx, 0)

    SafeRelease(VertBuf)
    SafeRelease(ShaderResource)
   .return DUPL_RETURN_SUCCESS

DISPLAYMANAGER::CopyDirty endp

;
; Clean all references
;
DISPLAYMANAGER::CleanRefs proc

    SafeRelease(m_DeviceContext)
    SafeRelease(m_Device)
    SafeRelease(m_MoveSurf)
    SafeRelease(m_VertexShader)
    SafeRelease(m_PixelShader)
    SafeRelease(m_InputLayout)
    SafeRelease(m_SamplerLinear)
    SafeRelease(m_RTV)
    ret

DISPLAYMANAGER::CleanRefs endp

    end
