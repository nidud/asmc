ifndef _RPCNDR500_
include rpcndr500.inc
endif

ifndef __d3d11_3_h__
define __d3d11_3_h__

ifndef __oaidl_h__
include oaidl.inc
endif
ifndef __ocidl_h__
include ocidl.inc
endif
include dxgi1_3.inc
include d3dcommon.inc
include d3d11_2.inc

.enum D3D11_CONTEXT_TYPE {
    D3D11_CONTEXT_TYPE_ALL	= 0,
    D3D11_CONTEXT_TYPE_3D	= 1,
    D3D11_CONTEXT_TYPE_COMPUTE	= 2,
    D3D11_CONTEXT_TYPE_COPY	= 3,
    D3D11_CONTEXT_TYPE_VIDEO	= 4
    }

.enum D3D11_TEXTURE_LAYOUT {
    D3D11_TEXTURE_LAYOUT_UNDEFINED	= 0,
    D3D11_TEXTURE_LAYOUT_ROW_MAJOR	= 1,
    D3D11_TEXTURE_LAYOUT_64K_STANDARD_SWIZZLE	= 2
    }

D3D11_TEXTURE2D_DESC1	STRUC
Width			UINT ?
Height			UINT ?
MipLevels		UINT ?
ArraySize		UINT ?
Format			DXGI_FORMAT ?
SampleDesc		DXGI_SAMPLE_DESC <>
Usage			D3D11_USAGE ?
BindFlags		UINT ?
CPUAccessFlags		UINT ?
MiscFlags		UINT ?
TextureLayout		D3D11_TEXTURE_LAYOUT ?
D3D11_TEXTURE2D_DESC1	ENDS

ifndef __ID3D11Texture2D1_INTERFACE_DEFINED__
define __ID3D11Texture2D1_INTERFACE_DEFINED__

DEFINE_IIDX(ID3D11Texture2D1, "51218251-1E33-4617-9CCB-4D3A4367E7BB")

.comdef ID3D11Texture2D1 : public ID3D11Texture2D

    GetDesc1		proc :ptr
   .ends

endif

D3D11_TEXTURE3D_DESC1	STRUC
Width			UINT ?
Height			UINT ?
Depth			UINT ?
MipLevels		UINT ?
Format			DXGI_FORMAT ?
Usage			D3D11_USAGE ?
BindFlags		UINT ?
CPUAccessFlags		UINT ?
MiscFlags		UINT ?
TextureLayout		D3D11_TEXTURE_LAYOUT ?
D3D11_TEXTURE3D_DESC1	ENDS

ifndef __ID3D11Texture3D1_INTERFACE_DEFINED__
define __ID3D11Texture3D1_INTERFACE_DEFINED__

DEFINE_IIDX(ID3D11Texture3D1, "0C711683-2853-4846-9BB0-F3E60639E46A")

.comdef ID3D11Texture3D1 : public ID3D11Texture3D

    GetDesc1		proc :ptr
   .ends

endif

.enum D3D11_CONSERVATIVE_RASTERIZATION_MODE {
    D3D11_CONSERVATIVE_RASTERIZATION_MODE_OFF	= 0,
    D3D11_CONSERVATIVE_RASTERIZATION_MODE_ON	= 1
    }

D3D11_RASTERIZER_DESC2	STRUC
FillMode		D3D11_FILL_MODE ?
CullMode		D3D11_CULL_MODE ?
FrontCounterClockwise	BOOL ?
DepthBias		int_t ?
DepthBiasClamp		FLOAT ?
SlopeScaledDepthBias	FLOAT ?
DepthClipEnable		BOOL ?
ScissorEnable		BOOL ?
MultisampleEnable	BOOL ?
AntialiasedLineEnable	BOOL ?
ForcedSampleCount	UINT ?
ConservativeRaster	D3D11_CONSERVATIVE_RASTERIZATION_MODE ?
D3D11_RASTERIZER_DESC2	ENDS

ifndef __ID3D11RasterizerState2_INTERFACE_DEFINED__
define __ID3D11RasterizerState2_INTERFACE_DEFINED__

DEFINE_IIDX(ID3D11RasterizerState2, "6fbd02fb-209f-46c4-b059-2ed15586a6ac")

.comdef ID3D11RasterizerState2 : public ID3D11RasterizerState1

    GetDesc2		proc :ptr
   .ends

endif

D3D11_TEX2D_SRV1	STRUC
MostDetailedMip		UINT ?
MipLevels		UINT ?
PlaneSlice		UINT ?
D3D11_TEX2D_SRV1	ENDS

D3D11_TEX2D_ARRAY_SRV1	STRUC
MostDetailedMip		UINT ?
MipLevels		UINT ?
FirstArraySlice		UINT ?
ArraySize		UINT ?
PlaneSlice		UINT ?
D3D11_TEX2D_ARRAY_SRV1	ENDS

D3D11_SHADER_RESOURCE_VIEW_DESC1 STRUC
Format			DXGI_FORMAT ?
ViewDimension		D3D11_SRV_DIMENSION ?
UNION
Buffer			D3D11_BUFFER_SRV <>
Texture1D		D3D11_TEX1D_SRV <>
Texture1DArray		D3D11_TEX1D_ARRAY_SRV <>
Texture2D		D3D11_TEX2D_SRV1 <>
Texture2DArray		D3D11_TEX2D_ARRAY_SRV1 <>
Texture2DMS		D3D11_TEX2DMS_SRV <>
Texture2DMSArray	D3D11_TEX2DMS_ARRAY_SRV <>
Texture3D		D3D11_TEX3D_SRV <>
TextureCube		D3D11_TEXCUBE_SRV <>
TextureCubeArray	D3D11_TEXCUBE_ARRAY_SRV <>
BufferEx		D3D11_BUFFEREX_SRV <>
ENDS
D3D11_SHADER_RESOURCE_VIEW_DESC1 ENDS

ifndef __ID3D11ShaderResourceView1_INTERFACE_DEFINED__
define __ID3D11ShaderResourceView1_INTERFACE_DEFINED__

DEFINE_IIDX(ID3D11ShaderResourceView1, "91308b87-9040-411d-8c67-c39253ce3802")

.comdef ID3D11ShaderResourceView1 : public ID3D11ShaderResourceView

    GetDesc1		proc :ptr
   .ends

endif

D3D11_TEX2D_RTV1	STRUC
MipSlice		UINT ?
PlaneSlice		UINT ?
D3D11_TEX2D_RTV1	ENDS

D3D11_TEX2D_ARRAY_RTV1	STRUC
MipSlice		UINT ?
FirstArraySlice		UINT ?
ArraySize		UINT ?
PlaneSlice		UINT ?
D3D11_TEX2D_ARRAY_RTV1	ENDS

D3D11_RENDER_TARGET_VIEW_DESC1 STRUC
Format			DXGI_FORMAT ?
ViewDimension		D3D11_RTV_DIMENSION ?
UNION
Buffer			D3D11_BUFFER_RTV <>
Texture1D		D3D11_TEX1D_RTV <>
Texture1DArray		D3D11_TEX1D_ARRAY_RTV <>
Texture2D		D3D11_TEX2D_RTV1 <>
Texture2DArray		D3D11_TEX2D_ARRAY_RTV1 <>
Texture2DMS		D3D11_TEX2DMS_RTV <>
Texture2DMSArray	D3D11_TEX2DMS_ARRAY_RTV <>
Texture3D		D3D11_TEX3D_RTV <>
ENDS
D3D11_RENDER_TARGET_VIEW_DESC1 ENDS

ifndef __ID3D11RenderTargetView1_INTERFACE_DEFINED__
define __ID3D11RenderTargetView1_INTERFACE_DEFINED__

DEFINE_IIDX(ID3D11RenderTargetView1, "ffbe2e23-f011-418a-ac56-5ceed7c5b94b")

.comdef ID3D11RenderTargetView1 : public ID3D11RenderTargetView

    GetDesc1		proc :ptr
   .ends

endif

D3D11_TEX2D_UAV1	STRUC
MipSlice		UINT ?
PlaneSlice		UINT ?
D3D11_TEX2D_UAV1	ENDS

D3D11_TEX2D_ARRAY_UAV1	STRUC
MipSlice		UINT ?
FirstArraySlice		UINT ?
ArraySize		UINT ?
PlaneSlice		UINT ?
D3D11_TEX2D_ARRAY_UAV1	ENDS

D3D11_UNORDERED_ACCESS_VIEW_DESC1 STRUC
Format			DXGI_FORMAT ?
ViewDimension		D3D11_UAV_DIMENSION ?
UNION
Buffer			D3D11_BUFFER_UAV <>
Texture1D		D3D11_TEX1D_UAV <>
Texture1DArray		D3D11_TEX1D_ARRAY_UAV <>
Texture2D		D3D11_TEX2D_UAV1 <>
Texture2DArray		D3D11_TEX2D_ARRAY_UAV1 <>
Texture3D		D3D11_TEX3D_UAV <>
ENDS
D3D11_UNORDERED_ACCESS_VIEW_DESC1 ENDS

ifndef __ID3D11UnorderedAccessView1_INTERFACE_DEFINED__
define __ID3D11UnorderedAccessView1_INTERFACE_DEFINED__

DEFINE_IIDX(ID3D11UnorderedAccessView1, "7b3b6153-a886-4544-ab37-6537c8500403")

.comdef ID3D11UnorderedAccessView1 : public ID3D11UnorderedAccessView

    GetDesc1		proc :ptr
   .ends

endif

D3D11_QUERY_DESC1	STRUC
Query			D3D11_QUERY ?
MiscFlags		UINT ?
ContextType		D3D11_CONTEXT_TYPE ?
D3D11_QUERY_DESC1	ENDS

ifndef __ID3D11Query1_INTERFACE_DEFINED__
define __ID3D11Query1_INTERFACE_DEFINED__

DEFINE_IIDX(ID3D11Query1, "631b4766-36dc-461d-8db6-c47e13e60916")

.comdef ID3D11Query1 : public ID3D11Query

    GetDesc1		proc :ptr
   .ends

endif

.enum D3D11_FENCE_FLAG {
    D3D11_FENCE_FLAG_NONE	= 0,
    D3D11_FENCE_FLAG_SHARED	= 0x2,
    D3D11_FENCE_FLAG_SHARED_CROSS_ADAPTER	= 0x4,
    D3D11_FENCE_FLAG_NON_MONITORED	= 0x8
    }

ifndef __ID3D11DeviceContext3_INTERFACE_DEFINED__
define __ID3D11DeviceContext3_INTERFACE_DEFINED__

DEFINE_IIDX(ID3D11DeviceContext3, "b4e3c01d-e79e-4637-91b2-510e9f4c9b8f")

.comdef ID3D11DeviceContext3 : public ID3D11DeviceContext2

    Flush1		proc :D3D11_CONTEXT_TYPE, :HANDLE
    SetHardwareProtectionState proc :BOOL
    GetHardwareProtectionState proc :ptr
   .ends

endif

ifndef __ID3D11Fence_INTERFACE_DEFINED__
define __ID3D11Fence_INTERFACE_DEFINED__

DEFINE_IIDX(ID3D11Fence, "affde9d1-1df7-4bb7-8a34-0f46251dab80")

.comdef ID3D11Fence : public ID3D11DeviceChild

    CreateSharedHandle	proc :ptr, :DWORD, :LPCWSTR, :ptr
    GetCompletedValue	proc
    SetEventOnCompletion proc :UINT64, :HANDLE
   .ends

endif

ifndef __ID3D11DeviceContext4_INTERFACE_DEFINED__
define __ID3D11DeviceContext4_INTERFACE_DEFINED__

DEFINE_IIDX(ID3D11DeviceContext4, "917600da-f58c-4c33-98d8-3e15b390fa24")

.comdef ID3D11DeviceContext4 : public ID3D11DeviceContext3

    Signal		proc :ptr, :UINT64
    _Wait		proc :ptr, :UINT64
   .ends

endif

ifndef __ID3D11Device3_INTERFACE_DEFINED__
define __ID3D11Device3_INTERFACE_DEFINED__

DEFINE_IIDX(ID3D11Device3, "A05C8C37-D2C6-4732-B3A0-9CE0B0DC9AE6")

.comdef ID3D11Device3 : public ID3D11Device2

    CreateTexture2D1	proc :ptr
    CreateTexture3D1	proc :ptr
    CreateRasterizerState2 proc :ptr, :ptr
    CreateShaderResourceView1 proc :ptr, :ptr, :ptr
    CreateUnorderedAccessView1 proc :ptr, :ptr, :ptr
    CreateRenderTargetView1 proc :ptr, :ptr, :ptr
    CreateQuery1	proc :ptr, :ptr
    GetImmediateContext3 proc :ptr
    CreateDeferredContext3 proc :UINT, :ptr
    WriteToSubresource	proc :ptr, :UINT, :ptr, :ptr, :UINT, :UINT
    ReadFromSubresource proc :ptr, :UINT, :UINT, :ptr, :UINT, :ptr
   .ends

endif

endif
