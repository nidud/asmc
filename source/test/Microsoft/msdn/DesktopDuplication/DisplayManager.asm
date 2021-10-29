
include DisplayManager.inc

    .code

    assume rsi:ptr DISPLAYMANAGER
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
DISPLAYMANAGER::Release proc uses rsi

    mov rsi,rcx
    [rsi].CleanRefs()

    .if ( [rsi].m_DirtyVertexBufferAlloc )

        free([rsi].m_DirtyVertexBufferAlloc)
        mov [rsi].m_DirtyVertexBufferAlloc,nullptr
    .endif
    free(rsi)
    ret

DISPLAYMANAGER::Release endp

;
; Initialize D3D variables
;
DISPLAYMANAGER::InitD3D proc Data:ptr DX_RESOURCES

    mov [rcx].DISPLAYMANAGER.m_Device,         [rdx].DX_RESOURCES.Device
    mov [rcx].DISPLAYMANAGER.m_DeviceContext,  [rdx].DX_RESOURCES.Context
    mov [rcx].DISPLAYMANAGER.m_VertexShader,   [rdx].DX_RESOURCES.VertexShader
    mov [rcx].DISPLAYMANAGER.m_PixelShader,    [rdx].DX_RESOURCES.PixelShader
    mov [rcx].DISPLAYMANAGER.m_InputLayout,    [rdx].DX_RESOURCES.InputLayout
    mov [rcx].DISPLAYMANAGER.m_SamplerLinear,  [rdx].DX_RESOURCES.SamplerLinear

    this.m_Device.AddRef()
    this.m_DeviceContext.AddRef()
    this.m_VertexShader.AddRef()
    this.m_PixelShader.AddRef()
    this.m_InputLayout.AddRef()
    this.m_SamplerLinear.AddRef()
    ret

DISPLAYMANAGER::InitD3D endp

;
; Process a given frame and its metadata
;
DISPLAYMANAGER::ProcessFrame proc uses rsi rdi rbx Data:ptr FRAME_DATA,
        SharedSurf:ptr ID3D11Texture2D, OffsetX:SINT, OffsetY:SINT,
        DeskDesc:ptr DXGI_OUTPUT_DESC

   .new retval:DUPL_RETURN = DUPL_RETURN_SUCCESS

    ; Process dirties and moves

    mov rsi,rcx
    mov rdi,rdx

    assume rdi:ptr FRAME_DATA

    .if ( [rdi].FrameInfo.TotalMetadataBufferSize )

       .new Desc:D3D11_TEXTURE2D_DESC
        Data.tFrame.GetDesc(&Desc)

        .if ( [rdi].MoveCount )

            mov retval,[rsi].CopyMove(SharedSurf, [rdi].MetaData, [rdi].MoveCount,
                    OffsetX, OffsetY, DeskDesc, Desc.Width, Desc.Height)

            .if ( retval != DUPL_RETURN_SUCCESS )

                .return retval
            .endif
        .endif

        .if ( [rdi].DirtyCount )

            imul r8d,[rdi].MoveCount,sizeof(DXGI_OUTDUPL_MOVE_RECT)
            add r8,[rdi].MetaData
            mov retval,[rsi].CopyDirty([rdi].tFrame, SharedSurf, r8,
                    [rdi].DirtyCount, OffsetX, OffsetY, DeskDesc)
        .endif
    .endif
    .return retval

DISPLAYMANAGER::ProcessFrame endp

;
; returns D3D device being used
;
DISPLAYMANAGER::GetDevice proc

    .return [rcx].DISPLAYMANAGER.m_Device

DISPLAYMANAGER::GetDevice endp

;
; Set appropriate source and destination rects for move rects
;
DISPLAYMANAGER::SetMoveRect proc \
        SrcRect   : ptr RECT,
        DestRect  : ptr RECT,
        DeskDesc  : ptr DXGI_OUTPUT_DESC,
        MoveRect  : ptr DXGI_OUTDUPL_MOVE_RECT,
        TexWidth  : SINT,
        TexHeight : SINT

    assume r10:ptr DXGI_OUTDUPL_MOVE_RECT
    mov r10,MoveRect

    .switch ( [r9].DXGI_OUTPUT_DESC.Rotation )

    .case DXGI_MODE_ROTATION_UNSPECIFIED
    .case DXGI_MODE_ROTATION_IDENTITY

        mov [rdx].RECT.left,[r10].SourcePoint.x
        add eax,[r10].DestinationRect.right
        sub eax,[r10].DestinationRect.left
        mov [rdx].RECT.right,eax
        mov [rdx].RECT.top,[r10].SourcePoint.y
        add eax,[r10].DestinationRect.bottom
        sub eax,[r10].DestinationRect.top
        mov [rdx].RECT.bottom,eax
        mov [r8],[r10].DestinationRect
       .endc

    .case DXGI_MODE_ROTATION_ROTATE90

        mov eax,TexHeight
        mov ecx,[r10].SourcePoint.y
        add ecx,[r10].DestinationRect.bottom
        sub ecx,[r10].DestinationRect.top
        sub eax,ecx
        mov [rdx].RECT.left,eax
        mov eax,TexHeight
        sub eax,[r10].SourcePoint.y
        mov [rdx].RECT.right,eax
        mov [rdx].RECT.top,[r10].SourcePoint.x
        add eax,[r10].DestinationRect.right
        sub eax,[r10].DestinationRect.left
        mov [rdx].RECT.bottom,eax

        mov eax,TexHeight
        sub eax,[r10].DestinationRect.bottom
        mov [r8].RECT.left,eax
        mov [r8].RECT.top,[r10].DestinationRect.left
        mov eax,TexHeight
        sub eax,[r10].DestinationRect.top
        mov [r8].RECT.right,eax
        mov [r8].RECT.bottom,[r10].DestinationRect.right
       .endc

    .case DXGI_MODE_ROTATION_ROTATE180

        mov ecx,[r10].SourcePoint.x
        add ecx,[r10].DestinationRect.right
        sub ecx,[r10].DestinationRect.left
        mov eax,TexWidth
        sub eax,ecx
        mov [rdx].RECT.left,eax
        mov ecx,[r10].SourcePoint.y
        add ecx,[r10].DestinationRect.bottom
        sub ecx,[r10].DestinationRect.top
        mov eax,TexHeight
        sub eax,ecx
        mov [rdx].RECT.top,eax
        mov eax,TexWidth
        sub eax,[r10].SourcePoint.x
        mov [rdx].RECT.right,eax
        mov eax,TexHeight
        sub eax,[r10].SourcePoint.y
        mov [rdx].RECT.bottom,eax

        mov eax,TexWidth
        sub eax,[r10].DestinationRect.right
        mov [r8].RECT.left,eax
        mov eax,TexHeight
        sub eax,[r10].DestinationRect.bottom
        mov [r8].RECT.top,eax
        mov eax,TexWidth
        sub eax,[r10].DestinationRect.left
        mov [r8].RECT.right,eax
        mov eax,TexHeight
        sub eax,[r10].DestinationRect.top
        mov [r8].RECT.bottom,eax
       .endc

    .case DXGI_MODE_ROTATION_ROTATE270

        mov [rdx].RECT.left,[r10].SourcePoint.x
        mov ecx,TexWidth
        add eax,[r10].DestinationRect.right
        sub eax,[r10].DestinationRect.left
        sub ecx,eax
        mov [rdx].RECT.top,ecx
        mov eax,[r10].SourcePoint.y
        add eax,[r10].DestinationRect.bottom
        sub eax,[r10].DestinationRect.top
        mov [rdx].RECT.right,eax
        mov eax,TexWidth
        sub eax,[r10].SourcePoint.x
        mov [rdx].RECT.bottom,eax

        mov [r8].RECT.left,[r10].DestinationRect.top
        mov eax,TexWidth
        sub eax,[r10].DestinationRect.right
        mov [r8].RECT.top,eax
        mov [r8].RECT.right,[r10].DestinationRect.bottom
        mov eax,TexWidth
        sub eax,[r10].DestinationRect.left
        mov [r8].RECT.bottom,eax
       .endc

    .default
        xor eax,eax
        mov [r8],rax
        mov [r8+8],rax
        mov [rdx],rax
        mov [rdx+8],rax
       .endc
    .endsw
    ret

DISPLAYMANAGER::SetMoveRect endp

;
; Copy move rectangles
;
DISPLAYMANAGER::CopyMove proc uses rsi rdi rbx \
        SharedSurf  : ptr ID3D11Texture2D,
        MoveBuffer  : ptr DXGI_OUTDUPL_MOVE_RECT,
        MoveCount   : UINT,
        OffsetX     : SINT,
        OffsetY     : SINT,
        DeskDesc    : ptr DXGI_OUTPUT_DESC,
        TexWidth    : SINT,
        TexHeight   : SINT

    mov rsi,rcx
    mov rdi,DeskDesc
    assume rdi:ptr DXGI_OUTPUT_DESC

   .new FullDesc:D3D11_TEXTURE2D_DESC
    SharedSurf.GetDesc(&FullDesc)

    ; Make new intermediate surface to copy into for moving

    .if ( ![rsi].m_MoveSurf )

       .new MoveDesc:D3D11_TEXTURE2D_DESC = FullDesc

        mov eax,[rdi].DesktopCoordinates.right
        sub eax,[rdi].DesktopCoordinates.left
        mov MoveDesc.Width,eax
        mov eax,[rdi].DesktopCoordinates.bottom
        sub eax,[rdi].DesktopCoordinates.top
        mov MoveDesc.Height,eax
        mov MoveDesc.BindFlags,D3D11_BIND_RENDER_TARGET
        mov MoveDesc.MiscFlags,0

        .new hr:HRESULT = this.m_Device.CreateTexture2D(&MoveDesc, nullptr, &[rsi].m_MoveSurf)
        .if (FAILED(hr))

            .return ProcessFailure([rsi].m_Device,
                    L"Failed to create staging texture for move rects",
                    L"Error", hr, &SystemTransitionsExpectedErrors)
        .endif
    .endif

    .for ( ebx = 0: ebx < MoveCount: ++ebx )

       .new SrcRect:RECT
       .new DestRect:RECT

        imul ecx,ebx,DXGI_OUTDUPL_MOVE_RECT
        add rcx,MoveBuffer
        this.SetMoveRect(&SrcRect, &DestRect, DeskDesc, rcx, TexWidth, TexHeight)

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

        this.m_DeviceContext.CopySubresourceRegion([rsi].m_MoveSurf, 0,
                SrcRect.left, SrcRect.top, 0, SharedSurf, 0, &Box)

        ; Copy back to shared surface

        mov Box.left,SrcRect.left
        mov Box.top,SrcRect.top
        mov Box.front,0
        mov Box.right,SrcRect.right
        mov Box.bottom,SrcRect.bottom
        mov Box.back,1

        mov r9d,DestRect.left
        add r9d,[rdi].DesktopCoordinates.left
        sub r9d,OffsetX
        mov ecx,DestRect.top
        add ecx,[rdi].DesktopCoordinates.top
        sub ecx,OffsetY
        this.m_DeviceContext.CopySubresourceRegion(
                SharedSurf, 0, r9d, ecx, 0, [rsi].m_MoveSurf, 0, &Box)
    .endf
    .return DUPL_RETURN_SUCCESS

DISPLAYMANAGER::CopyMove endp

;
; Sets up vertices for dirty rects for rotated desktops
;
DISPLAYMANAGER::SetDirtyVert proc uses rsi rdi rbx \
        Vertices    : ptr VERTEX,
        Dirty       : ptr RECT,
        OffsetX     : SINT,
        OffsetY     : SINT,
        DeskDesc    : ptr DXGI_OUTPUT_DESC,
        FullDesc    : ptr D3D11_TEXTURE2D_DESC,
        ThisDesc    : ptr D3D11_TEXTURE2D_DESC

    mov rsi,rcx
    mov r10,FullDesc
    mov rdi,DeskDesc
    assume r10:ptr D3D11_TEXTURE2D_DESC

    mov eax,[r10].Width
    mov ecx,[r10].Height
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

    .new DestDirty:RECT = [r8]

    ; Set appropriate coordinates compensated for rotation

    mov r10,ThisDesc
    cvtsi2ss xmm4,[r10].D3D11_TEXTURE2D_DESC.Width
    cvtsi2ss xmm5,[r10].D3D11_TEXTURE2D_DESC.Height
    cvtsi2ss xmm0,[r8].RECT.left
    cvtsi2ss xmm1,[r8].RECT.right
    cvtsi2ss xmm2,[r8].RECT.top
    cvtsi2ss xmm3,[r8].RECT.bottom
    divss xmm0,xmm4 ; left / Width
    divss xmm1,xmm4 ; right / Width
    divss xmm2,xmm5 ; top / Height
    divss xmm3,xmm5 ; bottom / Height

    .switch ( [rdi].Rotation )

    .case DXGI_MODE_ROTATION_ROTATE90

        mov eax,Width
        sub eax,[r8].RECT.bottom
        mov DestDirty.left,eax
        mov DestDirty.top,[r8].RECT.left
        mov eax,Width
        sub eax,[r8].RECT.top
        mov DestDirty.right,eax
        mov DestDirty.bottom,[r8].RECT.right

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
        sub eax,[r8].RECT.right
        mov DestDirty.left,eax
        mov eax,Height
        sub eax,[r8].RECT.bottom
        mov DestDirty.top,eax
        mov eax,Width
        sub eax,[r8].RECT.left
        mov DestDirty.right,eax
        mov eax,Height
        sub eax,[r8].RECT.top
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

        mov DestDirty.left,[r8].RECT.top
        mov eax,Height
        sub eax,[r8].RECT.right
        mov DestDirty.top,eax
        mov DestDirty.right,[r8].RECT.bottom
        mov eax,Height
        sub eax,[r8].RECT.left
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
DISPLAYMANAGER::CopyDirty proc uses rsi rdi rbx \
        SrcSurface  : ptr ID3D11Texture2D,
        SharedSurf  : ptr ID3D11Texture2D,
        DirtyBuffer : ptr RECT,
        DirtyCount  : UINT,
        OffsetX     : SINT,
        OffsetY     : SINT,
        DeskDesc    : ptr DXGI_OUTPUT_DESC

    mov rsi,rcx

   .new hr:HRESULT
   .new FullDesc:D3D11_TEXTURE2D_DESC
    SharedSurf.GetDesc(&FullDesc)

   .new ThisDesc:D3D11_TEXTURE2D_DESC
    SrcSurface.GetDesc(&ThisDesc)

    .if ( ![rsi].m_RTV )

        mov hr,this.m_Device.CreateRenderTargetView(
                SharedSurf, nullptr, &[rsi].m_RTV)
        .if (FAILED(hr))

            .return ProcessFailure([rsi].m_Device,
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
    mov hr,this.m_Device.CreateShaderResourceView(
            SrcSurface, &ShaderDesc, &ShaderResource)
    .if (FAILED(hr))

        .return ProcessFailure([rsi].m_Device,
                L"Failed to create shader resource view for dirty rects",
                L"Error", hr, &SystemTransitionsExpectedErrors)
    .endif

   .new BlendFactor[4]:FLOAT = { 0.0, 0.0, 0.0, 0.0 }

    assume rbx:ptr ID3D11DeviceContext

    mov rbx,[rsi].m_DeviceContext

    [rbx].OMSetBlendState(nullptr, &BlendFactor, 0xFFFFFFFF)
    [rbx].OMSetRenderTargets(1, &[rsi].m_RTV, nullptr)
    [rbx].VSSetShader([rsi].m_VertexShader, nullptr, 0)
    [rbx].PSSetShader([rsi].m_PixelShader, nullptr, 0)
    [rbx].PSSetShaderResources(0, 1, &ShaderResource)
    [rbx].PSSetSamplers(0, 1, &[rsi].m_SamplerLinear)
    [rbx].IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)

    assume rbx:nothing

    ; Create space for vertices for the dirty rects if the current space isn't large enough

    imul eax,DirtyCount,VERTEX * NUMVERTICES
   .new BytesNeeded:UINT = eax

    .if ( eax > [rsi].m_DirtyVertexBufferAllocSize )

        .if ( [rsi].m_DirtyVertexBufferAlloc )

            free([rsi].m_DirtyVertexBufferAlloc)
        .endif

        mov [rsi].m_DirtyVertexBufferAlloc,malloc(BytesNeeded)
        .if ( !rax )

            mov [rsi].m_DirtyVertexBufferAllocSize,eax
            .return ProcessFailure(nullptr,
                    L"Failed to allocate memory for dirty vertex buffer.",
                    L"Error", E_OUTOFMEMORY, nullptr)
        .endif

        mov [rsi].m_DirtyVertexBufferAllocSize,BytesNeeded
    .endif

    ; Fill them in

    mov rdi,[rsi].m_DirtyVertexBufferAlloc
    .for ( ebx = 0: ebx < DirtyCount: ++ebx, rdi += (NUMVERTICES*VERTEX) )

        imul edx,ebx,RECT
        add rdx,DirtyBuffer
        this.SetDirtyVert(rdi, rdx, OffsetX, OffsetY, DeskDesc, &FullDesc, &ThisDesc)
    .endf

    ; Create vertex buffer

   .new BufferDesc:D3D11_BUFFER_DESC = {0}
    mov BufferDesc.Usage,D3D11_USAGE_DEFAULT
    mov BufferDesc.ByteWidth,BytesNeeded
    mov BufferDesc.BindFlags,D3D11_BIND_VERTEX_BUFFER
    mov BufferDesc.CPUAccessFlags,0

   .new InitData:D3D11_SUBRESOURCE_DATA = {0}
    mov InitData.pSysMem,[rsi].m_DirtyVertexBufferAlloc

   .new VertBuf:ptr ID3D11Buffer = nullptr
    mov hr,this.m_Device.CreateBuffer(&BufferDesc, &InitData, &VertBuf)
    .if (FAILED(hr))

        .return ProcessFailure([rsi].m_Device,
                L"Failed to create vertex buffer in dirty rect processing",
                L"Error", hr, &SystemTransitionsExpectedErrors)
    .endif

   .new Stride:UINT = sizeof(VERTEX)
   .new bOffset:UINT = 0
    this.m_DeviceContext.IASetVertexBuffers(0, 1, &VertBuf, &Stride, &bOffset)

   .new VP:D3D11_VIEWPORT
    cvtsi2ss xmm0,FullDesc.Width
    cvtsi2ss xmm1,FullDesc.Height
    movss VP.Width,xmm0
    movss VP.Height,xmm1
    mov VP.MinDepth,0.0
    mov VP.MaxDepth,1.0
    mov VP.TopLeftX,0.0
    mov VP.TopLeftY,0.0
    this.m_DeviceContext.RSSetViewports(1, &VP)

    imul edx,DirtyCount,NUMVERTICES
    this.m_DeviceContext.Draw(edx, 0)

    SafeRelease(VertBuf)
    SafeRelease(ShaderResource)
   .return DUPL_RETURN_SUCCESS

DISPLAYMANAGER::CopyDirty endp

;
; Clean all references
;
DISPLAYMANAGER::CleanRefs proc uses rsi

    mov rsi,rcx
    SafeRelease([rsi].m_DeviceContext)
    SafeRelease([rsi].m_Device)
    SafeRelease([rsi].m_MoveSurf)
    SafeRelease([rsi].m_VertexShader)
    SafeRelease([rsi].m_PixelShader)
    SafeRelease([rsi].m_InputLayout)
    SafeRelease([rsi].m_SamplerLinear)
    SafeRelease([rsi].m_RTV)
    ret

DISPLAYMANAGER::CleanRefs endp

    end
