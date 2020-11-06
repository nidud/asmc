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
ifndef __dxgicommon_h__
include dxgicommon.inc
endif
ifndef __ID3D11BlendState1_FWD_DEFINED__
__ID3D11BlendState1_FWD_DEFINED__ equ 1
endif
ifndef __ID3DDeviceContextState_FWD_DEFINED__
__ID3DDeviceContextState_FWD_DEFINED__ equ 1
endif
ifndef __ID3D11DeviceContext1_FWD_DEFINED__
__ID3D11DeviceContext1_FWD_DEFINED__ equ 1
endif
ifndef __ID3D11VideoContext1_FWD_DEFINED__
__ID3D11VideoContext1_FWD_DEFINED__ equ 1
endif
ifndef __ID3D11VideoDevice1_FWD_DEFINED__
__ID3D11VideoDevice1_FWD_DEFINED__ equ 1
endif
ifndef __ID3D11VideoProcessorEnumerator1_FWD_DEFINED__
__ID3D11VideoProcessorEnumerator1_FWD_DEFINED__ equ 1
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

.comdef ID3D11BlendState1 : public ID3D11BlendState

    GetDesc1		proc :ptr

    .ends

endif

ifndef __ID3DDeviceContextState_INTERFACE_DEFINED__
__ID3DDeviceContextState_INTERFACE_DEFINED__ equ 1

DEFINE_GUID(IID_ID3DDeviceContextState, 0x5c1e0d8a, 0x7c23, 0x48f9, 0x8c,0x59, 0xa9,0x29,0x58,0xce,0xff,0x11);

.comdef ID3DDeviceContextState : public ID3D11DeviceChild

    .ends

endif

ifndef __ID3D11DeviceContext1_INTERFACE_DEFINED__
__ID3D11DeviceContext1_INTERFACE_DEFINED__ equ 1

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
__ID3D11VideoContext1_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ID3D11VideoContext1, "A7F026DA-A5F8-4487-A564-15E34357651E")

.comdef ID3D11VideoContext1 : public ID3D11VideoContext

    SubmitDecoderBuffers1 proc :ptr ID3D11VideoDecoder, :UINT, :ptr D3D11_VIDEO_DECODER_BUFFER_DESC1
    GetDataForNewHardwareKey proc :ptr ID3D11CryptoSession, :UINT, :ptr, :ptr UINT64
    CheckCryptoSessionStatus proc :ptr ID3D11CryptoSession, :ptr D3D11_CRYPTO_SESSION_STATUS
    DecoderEnableDownsampling proc :ptr ID3D11VideoDecoder, :DXGI_COLOR_SPACE_TYPE, :ptr D3D11_VIDEO_SAMPLE_DESC, :UINT
    DecoderUpdateDownsampling proc :ptr ID3D11VideoDecode, :ptr D3D11_VIDEO_SAMPLE_DESC
    VideoProcessorSetOutputColorSpace1 proc :ptr ID3D11VideoProcessor, :DXGI_COLOR_SPACE_TYPE
    VideoProcessorSetOutputShaderUsage proc :ptr ID3D11VideoProcessor, :BOOL
    VideoProcessorGetOutputColorSpace1 proc :ptr ID3D11VideoProcessor, :ptr DXGI_COLOR_SPACE_TYPE
    VideoProcessorGetOutputShaderUsage proc :ptr ID3D11VideoProcessor, :ptr BOOL
    VideoProcessorSetStreamColorSpace1 proc :ptr ID3D11VideoProcessor, :UINT, :DXGI_COLOR_SPACE_TYPE
    VideoProcessorSetStreamMirror proc :ptr ID3D11VideoProcessor, :UINT, :BOOL, :BOOL, :BOOL
    VideoProcessorGetStreamColorSpace1 proc :ptr ID3D11VideoProcessor, :UINT, :ptr DXGI_COLOR_SPACE_TYPE
    VideoProcessorGetStreamMirror proc :ptr ID3D11VideoProcessor, :UINT, :ptr BOOL, :ptr BOOL, :ptr BOOL
    VideoProcessorGetBehaviorHints proc :ptr ID3D11VideoProcessor, :UINT, :UINT, :DXGI_FORMAT, :UINT, :ptr D3D11_VIDEO_PROCESSOR_STREAM_BEHAVIOR_HINT, :ptr UINT

    .ends

endif

ifndef __ID3D11VideoDevice1_INTERFACE_DEFINED__
__ID3D11VideoDevice1_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ID3D11VideoDevice1, "29DA1D51-1321-4454-804B-F5FC9F861F0F")

.comdef ID3D11VideoDevice1 : public ID3D11VideoDevice

    GetCryptoSessionPrivateDataSize proc :ptr GUID, :ptr GUID, :ptr GUID, :ptr UINT, :ptr UINT
    GetVideoDecoderCaps proc :ptr GUID, :UINT, :UINT, :ptr DXGI_RATIONAL, :UINT, :ptr GUID, :ptr UINT
    CheckVideoDecoderDownsampling proc :ptr D3D11_VIDEO_DECODER_DESC, :DXGI_COLOR_SPACE_TYPE, :ptr D3D11_VIDEO_DECODER_CONFIG, :ptr DXGI_RATIONAL, :ptr D3D11_VIDEO_SAMPLE_DESC, :ptr BOOL, :ptr BOOL
    RecommendVideoDecoderDownsampleParameters proc :ptr D3D11_VIDEO_DECODER_DESC, :DXGI_COLOR_SPACE_TYPE, :ptr D3D11_VIDEO_DECODER_CONFIG, :ptr DXGI_RATIONAL, :ptr D3D11_VIDEO_SAMPLE_DESC

    .ends

endif

ifndef __ID3D11VideoProcessorEnumerator1_INTERFACE_DEFINED__
__ID3D11VideoProcessorEnumerator1_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ID3D11VideoProcessorEnumerator1, "465217F2-5568-43CF-B5B9-F61D54531CA1")

.comdef ID3D11VideoProcessorEnumerator1 : public ID3D11VideoProcessorEnumerator

    CheckVideoProcessorFormatConversion proc :DXGI_FORMAT, :DXGI_COLOR_SPACE_TYPE, :DXGI_FORMAT, :DXGI_COLOR_SPACE_TYPE, :ptr BOOL

    .ends

endif

ifndef __ID3DUserDefinedAnnotation_INTERFACE_DEFINED__
__ID3DUserDefinedAnnotation_INTERFACE_DEFINED__ equ 1

DEFINE_GUID(IID_ID3DUserDefinedAnnotation, 0xb2daad8b, 0x03d4, 0x4dbf, 0x95,0xeb, 0x32,0xab,0x4b,0x63,0xd0,0xab)

.comdef ID3DUserDefinedAnnotation : public IUnknown

    BeginEvent		proc :LPCWSTR
    EndEvent		proc
    SetMarker		proc :LPCWSTR
    GetStatus		proc

    .ends
endif

ifndef __ID3D11RasterizerState1_INTERFACE_DEFINED__
__ID3D11RasterizerState1_INTERFACE_DEFINED__ equ 1

DEFINE_GUID(IID_ID3D11RasterizerState1, 0x1217d7a6, 0x5039, 0x418c, 0xb0,0x42, 0x9c,0xbe,0x25,0x6a,0xfd,0x6e)

.comdef ID3D11RasterizerState1 : public ID3D11RasterizerState

    GetDesc1		proc :ptr

    .ends

endif

ifndef __ID3D11Device1_INTERFACE_DEFINED__
__ID3D11Device1_INTERFACE_DEFINED__ equ 1

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
