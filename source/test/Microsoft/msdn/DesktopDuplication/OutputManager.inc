
ifndef _OUTPUTMANAGER_H_
define _OUTPUTMANAGER_H_

include stdio.inc

include CommonTypes.inc
include warning.inc

;
; Handles the task of drawing into a window.
; Has the functionality to draw the mouse given a mouse shape buffer and position
;
.class OUTPUTMANAGER

    m_SwapChain         ptr IDXGISwapChain1 ?
    m_Device            ptr ID3D11Device ?
    m_Factory           ptr IDXGIFactory2 ?
    m_DeviceContext     ptr ID3D11DeviceContext ?
    m_RTV               ptr ID3D11RenderTargetView ?
    m_SamplerLinear     ptr ID3D11SamplerState ?
    m_BlendState        ptr ID3D11BlendState ?
    m_VertexShader      ptr ID3D11VertexShader ?
    m_PixelShader       ptr ID3D11PixelShader ?
    m_InputLayout       ptr ID3D11InputLayout ?
    m_SharedSurf        ptr ID3D11Texture2D ?
    m_KeyMutex          ptr IDXGIKeyedMutex ?
    m_WindowHandle      HWND ?
    m_NeedsResize       bool ?
    m_OcclusionCookie   DWORD ?

    OUTPUTMANAGER       proc
    Release             proc

    InitOutput          proc :HWND, :SINT, :ptr UINT, :ptr RECT
    UpdateApplicationWindow proc :ptr PTR_INFO, :ptr bool
    CleanRefs           proc
    GetSharedHandle     proc
    WindowResize        proc

    ProcessMonoMask     proc :bool, :ptr PTR_INFO, :ptr SINT, :ptr SINT, :ptr SINT, :ptr SINT, :ptr ptr BYTE, :ptr D3D11_BOX
    MakeRTV             proc
    SetViewPort         proc :UINT, :UINT
    InitShaders         proc
    InitGeometry        proc
    CreateSharedSurf    proc :SINT, :ptr UINT, :ptr RECT
    DrawFrame           proc
    DrawMouse           proc :ptr PTR_INFO
    ResizeSwapChain     proc
   .ends

endif
