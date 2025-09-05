.pragma list(push, 0)

ifndef _RPCNDR500_
include rpcndr500.inc
endif

ifndef __d3d11_1_h__
define __d3d11_1_h__

ifndef __dxgicommon_h__
include dxgicommon.inc
endif
ifndef __oaidl_h__
include oaidl.inc
endif
ifndef __ocidl_h__
include ocidl.inc
endif
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
define __ID3D11BlendState1_INTERFACE_DEFINED__

DEFINE_GUID(IID_ID3D11BlendState1, 0xcc86fabe, 0xda55, 0x401d, 0x85,0xe7, 0xe3,0xc9,0xde,0x28,0x77,0xe9)

.comdef ID3D11BlendState1 : public ID3D11BlendState

    GetDesc1		proc :ptr
   .ends

endif

ifndef __ID3DDeviceContextState_INTERFACE_DEFINED__
define __ID3DDeviceContextState_INTERFACE_DEFINED__

DEFINE_GUID(IID_ID3DDeviceContextState, 0x5c1e0d8a, 0x7c23, 0x48f9, 0x8c,0x59, 0xa9,0x29,0x58,0xce,0xff,0x11);

.comdef ID3DDeviceContextState : public ID3D11DeviceChild

    .ends

endif

ifndef __ID3D11DeviceContext1_INTERFACE_DEFINED__
define __ID3D11DeviceContext1_INTERFACE_DEFINED__

DEFINE_GUID(IID_ID3D11DeviceContext1, 0xbb2c6faa, 0xb5fb, 0x4082, 0x8e,0x6b, 0x38,0x8b,0x8c,0xfa,0x90,0xe1)

.comdef ID3D11DeviceContext1 : public ID3D11DeviceContext

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
    ClearView		proc :ptr, :real4, :ptr, :UINT
    DiscardView1	proc :ptr, :ptr, :UINT
   .ends

LPID3D11DeviceContext1	typedef ptr ID3D11DeviceContext1
endif

ifndef __ID3D11VideoContext1_INTERFACE_DEFINED__
define __ID3D11VideoContext1_INTERFACE_DEFINED__

DEFINE_IIDX(ID3D11VideoContext1, "A7F026DA-A5F8-4487-A564-15E34357651E")

.comdef ID3D11VideoContext1 : public ID3D11VideoContext

    SubmitDecoderBuffers1 proc :ptr, :UINT, :ptr
    GetDataForNewHardwareKey proc :ptr, :UINT, :ptr, :ptr
    CheckCryptoSessionStatus proc :ptr, :ptr
    DecoderEnableDownsampling proc :ptr, :DXGI_COLOR_SPACE_TYPE, :ptr, :UINT
    DecoderUpdateDownsampling proc :ptr, :ptr
    VideoProcessorSetOutputColorSpace1 proc :ptr, :DXGI_COLOR_SPACE_TYPE
    VideoProcessorSetOutputShaderUsage proc :ptr, :BOOL
    VideoProcessorGetOutputColorSpace1 proc :ptr, :ptr
    VideoProcessorGetOutputShaderUsage proc :ptr, :ptr
    VideoProcessorSetStreamColorSpace1 proc :ptr, :UINT, :DXGI_COLOR_SPACE_TYPE
    VideoProcessorSetStreamMirror proc :ptr, :UINT, :BOOL, :BOOL, :BOOL
    VideoProcessorGetStreamColorSpace1 proc :ptr, :UINT, :ptr
    VideoProcessorGetStreamMirror proc :ptr, :UINT, :ptr, :ptr, :ptr
    VideoProcessorGetBehaviorHints proc :ptr, :UINT, :UINT, :DXGI_FORMAT, :UINT, :ptr, :ptr
   .ends

endif

ifndef __ID3D11VideoDevice1_INTERFACE_DEFINED__
define __ID3D11VideoDevice1_INTERFACE_DEFINED__

DEFINE_IIDX(ID3D11VideoDevice1, "29DA1D51-1321-4454-804B-F5FC9F861F0F")

.comdef ID3D11VideoDevice1 : public ID3D11VideoDevice

    GetCryptoSessionPrivateDataSize proc :ptr, :ptr, :ptr, :ptr, :ptr
    GetVideoDecoderCaps proc :ptr, :UINT, :UINT, :ptr, :UINT, :ptr, :ptr
    CheckVideoDecoderDownsampling proc :ptr, :DXGI_COLOR_SPACE_TYPE, :ptr, :ptr, :ptr, :ptr, :ptr
    RecommendVideoDecoderDownsampleParameters proc :ptr, :DXGI_COLOR_SPACE_TYPE, :ptr, :ptr, :ptr
   .ends

endif

ifndef __ID3D11VideoProcessorEnumerator1_INTERFACE_DEFINED__
define __ID3D11VideoProcessorEnumerator1_INTERFACE_DEFINED__

DEFINE_IIDX(ID3D11VideoProcessorEnumerator1, "465217F2-5568-43CF-B5B9-F61D54531CA1")

.comdef ID3D11VideoProcessorEnumerator1 : public ID3D11VideoProcessorEnumerator

    CheckVideoProcessorFormatConversion proc :DXGI_FORMAT, :DXGI_COLOR_SPACE_TYPE, :DXGI_FORMAT, :DXGI_COLOR_SPACE_TYPE, :ptr
   .ends

endif

ifndef __ID3DUserDefinedAnnotation_INTERFACE_DEFINED__
define __ID3DUserDefinedAnnotation_INTERFACE_DEFINED__

DEFINE_GUID(IID_ID3DUserDefinedAnnotation, 0xb2daad8b, 0x03d4, 0x4dbf, 0x95,0xeb, 0x32,0xab,0x4b,0x63,0xd0,0xab)

.comdef ID3DUserDefinedAnnotation : public IUnknown

    BeginEvent		proc :LPCWSTR
    EndEvent		proc
    SetMarker		proc :LPCWSTR
    GetStatus		proc
   .ends
endif

ifndef __ID3D11RasterizerState1_INTERFACE_DEFINED__
define __ID3D11RasterizerState1_INTERFACE_DEFINED__

DEFINE_GUID(IID_ID3D11RasterizerState1, 0x1217d7a6, 0x5039, 0x418c, 0xb0,0x42, 0x9c,0xbe,0x25,0x6a,0xfd,0x6e)

.comdef ID3D11RasterizerState1 : public ID3D11RasterizerState

    GetDesc1		proc :ptr
   .ends

endif

ifndef __ID3D11Device1_INTERFACE_DEFINED__
define __ID3D11Device1_INTERFACE_DEFINED__

DEFINE_GUID(IID_ID3D11Device1, 0xa04bfb29, 0x08ef, 0x43d6, 0xa4,0x9c, 0xa9,0xbd,0xbd,0xcb,0xe6,0x86)

.comdef ID3D11Device1 : public ID3D11Device

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
