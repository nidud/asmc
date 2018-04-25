.pragma list(push, 0)
ifndef __REQUIRED_RPCNDR_H_VERSION__
__REQUIRED_RPCNDR_H_VERSION__ equ 475
endif
include rpc.inc
include rpcndr.inc
ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif
ifndef __d3d11_1_h__
__d3d11_1_h__ equ <>
ifndef __ID3D11BlendState1_FWD_DEFINED__
__ID3D11BlendState1_FWD_DEFINED__ equ 1
endif
ifndef __ID3DDeviceContextState_FWD_DEFINED__
__ID3DDeviceContextState_FWD_DEFINED__ equ 1
endif
ifndef __ID3D11DeviceContext1_FWD_DEFINED__
__ID3D11DeviceContext1_FWD_DEFINED__ equ 1
endif
ifndef __ID3DUserDefinedAnnotation_FWD_DEFINED__
__ID3DUserDefinedAnnotation_FWD_DEFINED__ equ 1
endif
ifndef __ID3D11RasterizerState1_FWD_DEFINED__
__ID3D11RasterizerState1_FWD_DEFINED__ equ 1
endif
ifndef __ID3D11Device1_FWD_DEFINED__
__ID3D11Device1_FWD_DEFINED__ equ 1
endif
include oaidl.inc
include ocidl.inc
include dxgi1_2.inc
include d3dcommon.inc
include d3d11.inc

D3D11_LOGIC_OP		typedef SDWORD
D3D11_LOGIC_OP_CLEAR	equ 0
D3D11_LOGIC_OP_SET	equ 1
D3D11_LOGIC_OP_COPY	equ 2
D3D11_LOGIC_OP_COPY_INVERTED equ 3
D3D11_LOGIC_OP_NOOP	equ 4
D3D11_LOGIC_OP_INVERT	equ 5
D3D11_LOGIC_OP_AND	equ 6
D3D11_LOGIC_OP_NAND	equ 7
D3D11_LOGIC_OP_OR	equ 8
D3D11_LOGIC_OP_NOR	equ 9
D3D11_LOGIC_OP_XOR	equ 10
D3D11_LOGIC_OP_EQUIV	equ 11
D3D11_LOGIC_OP_AND_REVERSE equ 12
D3D11_LOGIC_OP_AND_INVERTED equ 13
D3D11_LOGIC_OP_OR_REVERSE equ 14
D3D11_LOGIC_OP_OR_INVERTED equ 15

D3D11_RENDER_TARGET_BLEND_DESC1	 STRUC
BlendEnable		BOOL ?
LogicOpEnable		BOOL ?
SrcBlend		D3D11_BLEND ?
DestBlend		D3D11_BLEND ?
BlendOp			D3D11_BLEND_OP ?
SrcBlendAlpha		D3D11_BLEND ?
DestBlendAlpha		D3D11_BLEND ?
BlendOpAlpha		D3D11_BLEND_OP ?
LogicOp			D3D11_LOGIC_OP ?
RenderTargetWriteMask	UINT8 ?
D3D11_RENDER_TARGET_BLEND_DESC1 ENDS

D3D11_BLEND_DESC1	STRUC
AlphaToCoverageEnable	BOOL ?
IndependentBlendEnable	BOOL ?
RenderTarget		D3D11_RENDER_TARGET_BLEND_DESC1 8 dup(<>)
D3D11_BLEND_DESC1	ENDS
D3D11_RASTERIZER_DESC1	STRUC
FillMode		D3D11_FILL_MODE ?
CullMode		D3D11_CULL_MODE ?
FrontCounterClockwise	BOOL ?
DepthBias		SINT ?
DepthBiasClamp		FLOAT ?
SlopeScaledDepthBias	FLOAT ?
DepthClipEnable		BOOL ?
ScissorEnable		BOOL ?
MultisampleEnable	BOOL ?
AntialiasedLineEnable	BOOL ?
ForcedSampleCount	UINT ?
D3D11_RASTERIZER_DESC1	ENDS

ifndef __ID3D11BlendState1_INTERFACE_DEFINED__
__ID3D11BlendState1_INTERFACE_DEFINED__ equ 1

DEFINE_GUID(IID_ID3D11BlendState1, 0xcc86fabe, 0xda55, 0x401d, 0x85,0xe7, 0xe3,0xc9,0xde,0x28,0x77,0xe9)
.comdef ID3D11BlendState1

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetDevice		proc :ptr
    GetPrivateData	proc :REFGUID, :ptr, :ptr
    SetPrivateData	proc :REFGUID, :UINT, :ptr
    SetPrivateDataInterface proc :REFGUID, :ptr
    GetDesc		proc :ptr
    GetDesc1		proc :ptr
    .ends

endif

ifndef __ID3DDeviceContextState_INTERFACE_DEFINED__
__ID3DDeviceContextState_INTERFACE_DEFINED__ equ 1

DEFINE_GUID(IID_ID3DDeviceContextState, 0x5c1e0d8a, 0x7c23, 0x48f9, 0x8c,0x59, 0xa9,0x29,0x58,0xce,0xff,0x11);
.comdef ID3DDeviceContextState

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetDevice		proc :ptr
    GetPrivateData	proc :REFGUID, :ptr, :ptr
    SetPrivateData	proc :REFGUID, :UINT, :ptr
    SetPrivateDataInterface proc :REFGUID, :ptr
    .ends

endif

ifndef __ID3D11DeviceContext1_INTERFACE_DEFINED__
__ID3D11DeviceContext1_INTERFACE_DEFINED__ equ 1

DEFINE_GUID(IID_ID3D11DeviceContext1, 0xbb2c6faa, 0xb5fb, 0x4082, 0x8e,0x6b, 0x38,0x8b,0x8c,0xfa,0x90,0xe1)
.comdef ID3D11DeviceContext1

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetDevice		proc :ptr
    GetPrivateData	proc :REFGUID, :ptr, :ptr
    SetPrivateData	proc :REFGUID, :UINT, :ptr
    SetPrivateDataInterface proc :REFGUID, :ptr
    VSSetConstantBuffers proc :UINT, :UINT, :ptr
    PSSetShaderResources proc :UINT, :UINT, :ptr
    PSSetShader		proc :ptr, :ptr, :UINT
    PSSetSamplers	proc :UINT, :UINT, :ptr
    VSSetShader		proc :ptr, :ptr, :UINT
    DrawIndexed		proc :UINT, :UINT, :SINT
    Draw		proc :UINT, :UINT
    Map			proc :ptr, :UINT, :D3D11_MAP, :UINT, :ptr
    Unmap		proc :ptr, :UINT
    PSSetConstantBuffers proc :UINT, :UINT, :ptr
    IASetInputLayout	proc :ptr
    IASetVertexBuffers	proc :UINT, :UINT, :ptr, :ptr, :ptr
    IASetIndexBuffer	proc :ptr, :DXGI_FORMAT, :UINT
    DrawIndexedInstanced proc :UINT, :UINT, :UINT, :SINT, :UINT
    DrawInstanced	proc :UINT, :UINT, :UINT, :UINT
    GSSetConstantBuffers proc :UINT, :UINT, :ptr
    GSSetShader		proc :ptr, :ptr, :UINT
    IASetPrimitiveTopology proc :D3D11_PRIMITIVE_TOPOLOGY
    VSSetShaderResources proc :UINT, :UINT, :ptr
    VSSetSamplers	proc :UINT, :UINT, :ptr
    Begin		proc :ptr
    _End		proc :ptr
    GetData		proc :ptr, :ptr, :UINT, :UINT
    SetPredication	proc :ptr, :BOOL
    GSSetShaderResources proc :UINT, :UINT, :ptr
    GSSetSamplers	proc :UINT, :UINT, :ptr
    OMSetRenderTargets	proc :UINT, :ptr, :ptr
    OMSetRenderTargetsAndUnorderedAccessViews proc :UINT, :ptr, :ptr, :UINT, :UINT, :ptr, :ptr
    OMSetBlendState	proc :ptr, :FLOAT, :UINT
    OMSetDepthStencilState proc :ptr, :UINT
    SOSetTargets	proc :UINT, :ptr, :ptr
    DrawAuto		proc
    DrawIndexedInstancedIndirect proc :ptr, :UINT
    DrawInstancedIndirect proc :ptr, :UINT
    Dispatch		proc :UINT, :UINT, :UINT
    DispatchIndirect	proc :ptr, :UINT
    RSSetState		proc :ptr
    RSSetViewports	proc :UINT, :ptr
    RSSetScissorRects	proc :UINT, :ptr
    CopySubresourceRegion proc :ptr, :UINT, :UINT, :UINT, :UINT, :ptr, :UINT, :ptr
    CopyResource	proc :ptr, :ptr
    UpdateSubresource	proc :ptr, :UINT, :ptr, :ptr, :UINT, :UINT
    CopyStructureCount	proc :ptr, :UINT, :ptr
    ClearRenderTargetView proc :ptr, :FLOAT
    ClearUnorderedAccessViewUint proc :ptr, :UINT
    ClearUnorderedAccessViewFloat proc :ptr, :FLOAT
    ClearDepthStencilView proc :ptr, :UINT, :FLOAT, :UINT8
    GenerateMips	proc :ptr
    SetResourceMinLOD	proc :ptr, :FLOAT
    GetResourceMinLOD	proc :ptr
    ResolveSubresource	proc :ptr, :UINT, :ptr, :UINT, :DXGI_FORMAT
    ExecuteCommandList	proc :ptr, :BOOL
    HSSetShaderResources proc :UINT, :UINT, :ptr
    HSSetShader		proc :ptr, :ptr, :UINT
    HSSetSamplers	proc :UINT, :UINT, :ptr
    HSSetConstantBuffers proc :UINT, :UINT, :ptr
    DSSetShaderResources proc :UINT, :UINT, :ptr
    DSSetShader		proc :ptr, :ptr, :UINT
    DSSetSamplers	proc :UINT, :UINT, :ptr
    DSSetConstantBuffers proc :UINT, :UINT, :ptr
    CSSetShaderResources proc :UINT, :UINT, :ptr
    CSSetUnorderedAccessViews proc :UINT, :UINT, :ptr, :ptr
    CSSetShader		proc :ptr, :ptr, :UINT
    CSSetSamplers	proc :UINT, :UINT, :ptr
    CSSetConstantBuffers proc :UINT, :UINT, :ptr
    VSGetConstantBuffers proc :UINT, :UINT, :ptr
    PSGetShaderResources proc :UINT, :UINT, :ptr
    PSGetShader		proc :ptr, :ptr, :ptr
    PSGetSamplers	proc :UINT, :UINT, :ptr
    VSGetShader		proc :ptr, :ptr, :ptr
    PSGetConstantBuffers proc :UINT, :UINT, :ptr
    IAGetInputLayout	proc :ptr
    IAGetVertexBuffers	proc :UINT, :UINT, :ptr, :ptr, :ptr
    IAGetIndexBuffer	proc :ptr, :ptr, :ptr
    GSGetConstantBuffers proc :UINT, :UINT, :ptr
    GSGetShader		proc :ptr, :ptr, :ptr
    IAGetPrimitiveTopology proc :ptr
    VSGetShaderResources proc :UINT, :UINT, :ptr
    VSGetSamplers	proc :UINT, :UINT, :ptr
    GetPredication	proc :ptr, :ptr
    GSGetShaderResources proc :UINT, :UINT, :ptr
    GSGetSamplers	proc :UINT, :UINT, :ptr
    OMGetRenderTargets	proc :UINT, :ptr, :ptr
    OMGetRenderTargetsAndUnorderedAccessViews proc :UINT, :ptr, :ptr, :UINT, :UINT, :ptr
    OMGetBlendState	proc :ptr, :FLOAT, :ptr
    OMGetDepthStencilState proc :ptr, :ptr
    SOGetTargets	proc :UINT, :ptr
    RSGetState		proc :ptr
    RSGetViewports	proc :ptr, :ptr
    RSGetScissorRects	proc :ptr, :ptr
    HSGetShaderResources proc :UINT, :UINT, :ptr
    HSGetShader		proc :ptr, :ptr, :ptr
    HSGetSamplers	proc :UINT, :UINT, :ptr
    HSGetConstantBuffers proc :UINT, :UINT, :ptr
    DSGetShaderResources proc :UINT, :UINT, :ptr
    DSGetShader		proc :ptr, :ptr, :ptr
    DSGetSamplers	proc :UINT, :UINT, :ptr
    DSGetConstantBuffers proc :UINT, :UINT, :ptr
    CSGetShaderResources proc :UINT, :UINT, :ptr
    CSGetUnorderedAccessViews proc :UINT, :UINT, :ptr
    CSGetShader		proc :ptr, :ptr, :ptr
    CSGetSamplers	proc :UINT, :UINT, :ptr
    CSGetConstantBuffers proc :UINT, :UINT, :ptr
    ClearState		proc
    Flush		proc
    GetType		proc
    GetContextFlags	proc
    FinishCommandList	proc :BOOL, :ptr
    CopySubresourceRegion1 proc :ptr, :UINT, :UINT, :UINT, :UINT, :ptr, :UINT, :ptr, :UINT
    UpdateSubresource1	proc :ptr, :UINT, :ptr, :ptr, :UINT, :UINT, :UINT
    DiscardResource	proc :ptr
    DiscardView		proc :ptr
    VSSetConstantBuffers1 proc :UINT, :UINT, :ptr, :ptr, :ptr
    HSSetConstantBuffers1 proc :UINT, :UINT, :ptr, :ptr, :ptr
    DSSetConstantBuffers1 proc :UINT, :UINT, :ptr, :ptr, :ptr
    GSSetConstantBuffers1 proc :UINT, :UINT, :ptr, :ptr, :ptr
    PSSetConstantBuffers1 proc :UINT, :UINT, :ptr, :ptr, :ptr
    CSSetConstantBuffers1 proc :UINT, :UINT, :ptr, :ptr, :ptr
    VSGetConstantBuffers1 proc :UINT, :UINT, :ptr, :ptr, :ptr
    HSGetConstantBuffers1 proc :UINT, :UINT, :ptr, :ptr, :ptr
    DSGetConstantBuffers1 proc :UINT, :UINT, :ptr, :ptr, :ptr
    GSGetConstantBuffers1 proc :UINT, :UINT, :ptr, :ptr, :ptr
    PSGetConstantBuffers1 proc :UINT, :UINT, :ptr, :ptr, :ptr
    CSGetConstantBuffers1 proc :UINT, :UINT, :ptr, :ptr, :ptr
    SwapDeviceContextState proc :ptr, :ptr
    ClearView		proc :ptr, :FLOAT, :ptr, :UINT
    DiscardView1	proc :ptr, :ptr, :UINT
    .ends

LPID3D11DeviceContext1	typedef ptr ID3D11DeviceContext1
endif

ifndef __ID3DUserDefinedAnnotation_INTERFACE_DEFINED__
__ID3DUserDefinedAnnotation_INTERFACE_DEFINED__ equ 1

DEFINE_GUID(IID_ID3DUserDefinedAnnotation, 0xb2daad8b, 0x03d4, 0x4dbf, 0x95,0xeb, 0x32,0xab,0x4b,0x63,0xd0,0xab)
.comdef ID3DUserDefinedAnnotation

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    BeginEvent		proc :LPCWSTR
    EndEvent		proc
    SetMarker		proc :LPCWSTR
    GetStatus		proc
    .ends
endif

ifndef __ID3D11RasterizerState1_INTERFACE_DEFINED__
__ID3D11RasterizerState1_INTERFACE_DEFINED__ equ 1

DEFINE_GUID(IID_ID3D11RasterizerState1, 0x1217d7a6, 0x5039, 0x418c, 0xb0,0x42, 0x9c,0xbe,0x25,0x6a,0xfd,0x6e)
.comdef ID3D11RasterizerState1

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetDevice		proc :ptr
    GetPrivateData	proc :REFGUID, :ptr, :ptr
    SetPrivateData	proc :REFGUID, :UINT, :ptr
    SetPrivateDataInterface proc :REFGUID, :ptr
    GetDesc		proc :ptr
    GetDesc1		proc :ptr
    .ends

endif

ifndef __ID3D11Device1_INTERFACE_DEFINED__
__ID3D11Device1_INTERFACE_DEFINED__ equ 1

DEFINE_GUID(IID_ID3D11Device1, 0xa04bfb29, 0x08ef, 0x43d6, 0xa4,0x9c, 0xa9,0xbd,0xbd,0xcb,0xe6,0x86)
.comdef ID3D11Device1

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    CreateBuffer	proc :ptr, :ptr, :ptr
    CreateTexture1D	proc :ptr, :ptr, :ptr
    CreateTexture2D	proc :ptr, :ptr, :ptr
    CreateTexture3D	proc :ptr, :ptr, :ptr
    CreateShaderResourceView proc :ptr, :ptr, :ptr
    CreateUnorderedAccessView proc :ptr, :ptr, :ptr
    CreateRenderTargetView proc :ptr, :ptr, :ptr
    CreateDepthStencilView proc :ptr, :ptr, :ptr
    CreateInputLayout	proc :ptr, :UINT, :ptr, :SIZE_T, :ptr
    CreateVertexShader	proc :ptr, :SIZE_T, :ptr, :ptr
    CreateGeometryShader proc :ptr, :SIZE_T, :ptr, :ptr
    CreateGeometryShaderWithStreamOutput proc :ptr, :SIZE_T, :ptr, :UINT, :ptr, :UINT, :UINT, :ptr, :ptr
    CreatePixelShader	proc :ptr, :SIZE_T, :ptr, :ptr
    CreateHullShader	proc :ptr, :SIZE_T, :ptr, :ptr
    CreateDomainShader	proc :ptr, :SIZE_T, :ptr, :ptr
    CreateComputeShader proc :ptr, :SIZE_T, :ptr, :ptr
    CreateClassLinkage	proc :ptr
    CreateBlendState	proc :ptr, :ptr
    CreateDepthStencilState proc :ptr, :ptr
    CreateRasterizerState proc :ptr, :ptr
    CreateSamplerState	proc :ptr, :ptr
    CreateQuery		proc :ptr, :ptr
    CreatePredicate	proc :ptr, :ptr
    CreateCounter	proc :ptr, :ptr
    CreateDeferredContext proc :UINT, :ptr
    OpenSharedResource	proc :HANDLE, :REFIID, :ptr
    CheckFormatSupport	proc :DXGI_FORMAT, :ptr
    CheckMultisampleQualityLevels proc :DXGI_FORMAT, :UINT, :ptr
    CheckCounterInfo	proc :ptr
    CheckCounter	proc :ptr, :ptr, :ptr, :LPSTR, :ptr, :LPSTR, :ptr, :LPSTR, :ptr
    CheckFeatureSupport proc :D3D11_FEATURE, :ptr, :UINT
    GetPrivateData	proc :REFGUID, :ptr, :ptr
    SetPrivateData	proc :REFGUID, :UINT, :ptr
    SetPrivateDataInterface proc :REFGUID, :ptr
    GetFeatureLevel	proc
    GetCreationFlags	proc
    GetDeviceRemovedReason proc
    GetImmediateContext proc :ptr
    SetExceptionMode	proc :UINT
    GetExceptionMode	proc
    GetImmediateContext1 proc :ptr
    CreateDeferredContext1 proc :UINT, :ptr
    CreateBlendState1	proc :ptr, :ptr
    CreateRasterizerState1 proc :ptr, :ptr
    CreateDeviceContextState proc :UINT, :ptr, :UINT, :UINT, :REFIID, :ptr, :ptr
    OpenSharedResource1 proc :HANDLE, :REFIID, :ptr
    OpenSharedResourceByName proc :LPCWSTR, :DWORD, :REFIID, :ptr
    .ends

LPID3D11Device1		typedef ptr ID3D11Device1
endif

endif
.pragma list(pop)
