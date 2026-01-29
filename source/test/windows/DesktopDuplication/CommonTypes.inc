
ifndef _COMMONTYPES_H_
define _COMMONTYPES_H_

include windows.inc
include d3d11.inc
include dxgi1_2.inc
include sal.inc
include new.inc
include warning.inc
include DirectXMath.inc

define NUMVERTICES 6
define BPP         4

define OCCLUSION_STATUS_MSG WM_USER

externdef SystemTransitionsExpectedErrors:HRESULT
externdef CreateDuplicationExpectedErrors:HRESULT
externdef FrameInfoExpectedErrors:HRESULT
externdef AcquireFrameExpectedError:HRESULT
externdef EnumOutputsExpectedErrors:HRESULT

externdef g_PS:byte
externdef g_VS:byte
externdef g_PS_size:size_t
externdef g_VS_size:size_t

.enum DUPL_RETURN {
    DUPL_RETURN_SUCCESS             = 0,
    DUPL_RETURN_ERROR_EXPECTED      = 1,
    DUPL_RETURN_ERROR_UNEXPECTED    = 2
    }

ProcessFailure proto :ptr ID3D11Device, :LPCWSTR, :LPCWSTR, :HRESULT, :ptr HRESULT
DisplayMsg proto :LPCWSTR, :LPCWSTR, :HRESULT

; Holds info about the pointer/cursor

.template PTR_INFO
    PtrShapeBuffer      ptr BYTE ?
    ShapeInfo           DXGI_OUTDUPL_POINTER_SHAPE_INFO <>
    Position            POINT <>
    Visible             bool ?
    BufferSize          UINT ?
    WhoUpdatedPositionLast UINT ?
    LastTimeStamp       LARGE_INTEGER <>
   .ends

; Structure that holds D3D resources not directly tied to any one thread

.template DX_RESOURCES
    Device              ptr ID3D11Device ?
    Context             ptr ID3D11DeviceContext ?
    VertexShader        ptr ID3D11VertexShader ?
    PixelShader         ptr ID3D11PixelShader ?
    InputLayout         ptr ID3D11InputLayout ?
    SamplerLinear       ptr ID3D11SamplerState ?
   .ends

; Structure to pass to a new thread

.template THREAD_DATA

    ; Used to indicate abnormal error condition

    UnexpectedErrorEvent HANDLE ?

    ; Used to indicate a transition event occurred e.g. PnpStop, PnpStart,
    ; mode change, TDR, desktop switch and the application needs to recreate
    ; the duplication interface

    ExpectedErrorEvent  HANDLE ?

    ; Used by WinProc to signal to threads to exit

    TerminateThreadsEvent HANDLE ?

    TexSharedHandle     HANDLE ?
    Output              UINT ?
    OffsetX             SINT ?
    OffsetY             SINT ?
    PtrInfo             ptr PTR_INFO ?
    DxRes               DX_RESOURCES <>
   .ends

; FRAME_DATA holds information about an acquired frame

.template FRAME_DATA
    tFrame              ptr ID3D11Texture2D ?
    FrameInfo           DXGI_OUTDUPL_FRAME_INFO <>
    MetaData            ptr BYTE ?
    DirtyCount          UINT ?
    MoveCount           UINT ?
   .ends

; A vertex with a position and texture coordinate

.template VERTEX
    Pos                 XMFLOAT3 <>
    TexCoord            XMFLOAT2 <>
   .ends

endif
