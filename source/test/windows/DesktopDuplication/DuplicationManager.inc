
ifndef _DUPLICATIONMANAGER_H_
define _DUPLICATIONMANAGER_H_

include CommonTypes.inc

; Handles the task of duplicating an output.

.class DUPLICATIONMANAGER

    m_DeskDupl          ptr IDXGIOutputDuplication ?
    m_AcquiredDesktopImage ptr ID3D11Texture2D ?
    m_MetaDataBuffer    ptr BYTE ?
    m_MetaDataSize      UINT ?
    m_OutputNumber      UINT ?
    m_OutputDesc        DXGI_OUTPUT_DESC <>
    m_Device            ptr ID3D11Device ?

    DUPLICATIONMANAGER  proc
    Release             proc

    GetFrame            proc :ptr FRAME_DATA, :ptr bool
    DoneWithFrame       proc
    InitDupl            proc :ptr ID3D11Device, :UINT
    GetMouse            proc :ptr PTR_INFO, :ptr DXGI_OUTDUPL_FRAME_INFO, :SINT, :SINT
    GetOutputDesc       proc :ptr DXGI_OUTPUT_DESC
   .ends

endif
