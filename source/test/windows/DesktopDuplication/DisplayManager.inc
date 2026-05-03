
ifndef _DISPLAYMANAGER_H_
define _DISPLAYMANAGER_H_

include CommonTypes.inc

; Handles the task of processing frames

.class DISPLAYMANAGER

    m_Device            ptr ID3D11Device ?
    m_DeviceContext     ptr ID3D11DeviceContext ?
    m_MoveSurf          ptr ID3D11Texture2D ?
    m_VertexShader      ptr ID3D11VertexShader ?
    m_PixelShader       ptr ID3D11PixelShader ?
    m_InputLayout       ptr ID3D11InputLayout ?
    m_RTV               ptr ID3D11RenderTargetView ?
    m_SamplerLinear     ptr ID3D11SamplerState ?
    m_DirtyVertexBufferAlloc ptr BYTE ?
    m_DirtyVertexBufferAllocSize UINT ?

    DISPLAYMANAGER      proc
    Release             proc

    InitD3D             proc :ptr DX_RESOURCES
    GetDevice           proc
    ProcessFrame        proc :ptr FRAME_DATA, :ptr ID3D11Texture2D, :SINT, :SINT, :ptr DXGI_OUTPUT_DESC
    CleanRefs           proc

    CopyDirty           proc :ID3D11Texture2D, : ptr ID3D11Texture2D, :ptr RECT, :UINT, :SINT, :SINT, :ptr DXGI_OUTPUT_DESC
    CopyMove            proc :ID3D11Texture2D, :ptr DXGI_OUTDUPL_MOVE_RECT, :UINT, :SINT, :SINT, : ptr DXGI_OUTPUT_DESC, :SINT, :SINT
    SetDirtyVert        proc :ptr VERTEX, :ptr RECT, :SINT, :SINT, :ptr DXGI_OUTPUT_DESC, :ptr D3D11_TEXTURE2D_DESC, :ptr D3D11_TEXTURE2D_DESC
    SetMoveRect         proc :ptr RECT, :ptr RECT, :ptr DXGI_OUTPUT_DESC, :ptr DXGI_OUTDUPL_MOVE_RECT, :SINT, :SINT
   .ends

endif
