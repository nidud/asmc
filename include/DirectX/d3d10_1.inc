.pragma list(push, 0)
ifndef __REQUIRED_RPCNDR_H_VERSION__
define __REQUIRED_RPCNDR_H_VERSION__ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
define __REQUIRED_RPCSAL_H_VERSION__ 100
endif

include rpc.inc
include rpcndr.inc
ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr.inc>
endif

ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif

ifndef __d3d10_1_h__
define __d3d10_1_h__

include oaidl.inc
include ocidl.inc

if defined( __d3d10_h__ ) AND NOT defined( D3D10_ARBITRARY_HEADER_ORDERING )
.err <d3d10.inc is included before d3d10_1.h, and it will confuse tools that honor SAL annotations>
endif

ifndef _D3D10_1_CONSTANTS
define _D3D10_1_CONSTANTS
D3D10_1_DEFAULT_SAMPLE_MASK equ ( 0xffffffff )

D3D10_1_FLOAT16_FUSED_TOLERANCE_IN_ULP equ ( 0.6 )
D3D10_1_FLOAT32_TO_INTEGER_TOLERANCE_IN_ULP equ ( 0.6f )
D3D10_1_GS_INPUT_REGISTER_COUNT equ ( 32 )

D3D10_1_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT equ ( 32 )
D3D10_1_IA_VERTEX_INPUT_STRUCTURE_ELEMENTS_COMPONENTS equ ( 128 )
D3D10_1_IA_VERTEX_INPUT_STRUCTURE_ELEMENT_COUNT equ ( 32 )
D3D10_1_PS_OUTPUT_MASK_REGISTER_COMPONENTS equ ( 1 )
D3D10_1_PS_OUTPUT_MASK_REGISTER_COMPONENT_BIT_COUNT equ ( 32 )
D3D10_1_PS_OUTPUT_MASK_REGISTER_COUNT equ ( 1 )
D3D10_1_SHADER_MAJOR_VERSION equ ( 4 )
D3D10_1_SHADER_MINOR_VERSION equ ( 1 )
D3D10_1_SO_BUFFER_MAX_STRIDE_IN_BYTES equ ( 2048 )
D3D10_1_SO_BUFFER_MAX_WRITE_WINDOW_IN_BYTES equ ( 256 )
D3D10_1_SO_BUFFER_SLOT_COUNT equ ( 4 )
D3D10_1_SO_MULTIPLE_BUFFER_ELEMENTS_PER_BUFFER equ ( 1 )
D3D10_1_SO_SINGLE_BUFFER_COMPONENT_LIMIT equ ( 64 )
D3D10_1_STANDARD_VERTEX_ELEMENT_COUNT equ ( 32 )
D3D10_1_SUBPIXEL_FRACTIONAL_BIT_COUNT equ ( 8 )
D3D10_1_VS_INPUT_REGISTER_COUNT equ ( 32 )
D3D10_1_VS_OUTPUT_REGISTER_COUNT equ ( 32 )
endif

include d3d10.inc

D3D10_FEATURE_LEVEL1	typedef SDWORD
D3D10_FEATURE_LEVEL_10_0 equ 0xa000
D3D10_FEATURE_LEVEL_10_1 equ 0xa100
D3D10_FEATURE_LEVEL_9_1 equ 0x9100
D3D10_FEATURE_LEVEL_9_2 equ 0x9200
D3D10_FEATURE_LEVEL_9_3 equ 0x9300

D3D10_RENDER_TARGET_BLEND_DESC1 STRUC
BlendEnable		BOOL ?
SrcBlend		D3D10_BLEND ?
DestBlend		D3D10_BLEND ?
BlendOp			D3D10_BLEND_OP ?
SrcBlendAlpha		D3D10_BLEND ?
DestBlendAlpha		D3D10_BLEND ?
BlendOpAlpha		D3D10_BLEND_OP ?
RenderTargetWriteMask	UINT8 ?
D3D10_RENDER_TARGET_BLEND_DESC1 ENDS

D3D10_BLEND_DESC1	STRUC
AlphaToCoverageEnable	BOOL ?
IndependentBlendEnable	BOOL ?
RenderTarget		D3D10_RENDER_TARGET_BLEND_DESC1 8 dup(<>)
D3D10_BLEND_DESC1	ENDS

ifndef __ID3D10BlendState1_INTERFACE_DEFINED__
define __ID3D10BlendState1_INTERFACE_DEFINED__

.comdef ID3D10BlendState1 : public IUnknown

    GetDevice			proc :ptr
    GetPrivateData		proc :REFGUID, :ptr, :ptr
    SetPrivateData		proc :REFGUID, :UINT, :ptr
    SetPrivateDataInterface	proc :REFGUID, :ptr
    GetDesc			proc :ptr
    GetDesc1			proc :ptr
   .ends

endif

D3D10_TEXCUBE_ARRAY_SRV1 STRUC
MostDetailedMip		UINT ?
MipLevels		UINT ?
First2DArrayFace	UINT ?
NumCubes		UINT ?
D3D10_TEXCUBE_ARRAY_SRV1 ENDS

D3D10_SRV_DIMENSION1	typedef SDWORD
D3D10_1_SRV_DIMENSION_UNKNOWN equ 0
D3D10_1_SRV_DIMENSION_BUFFER equ 1
D3D10_1_SRV_DIMENSION_TEXTURE1D equ 2
D3D10_1_SRV_DIMENSION_TEXTURE1DARRAY equ 3
D3D10_1_SRV_DIMENSION_TEXTURE2D equ 4
D3D10_1_SRV_DIMENSION_TEXTURE2DARRAY equ 5
D3D10_1_SRV_DIMENSION_TEXTURE2DMS equ 6
D3D10_1_SRV_DIMENSION_TEXTURE2DMSARRAY equ 7
D3D10_1_SRV_DIMENSION_TEXTURE3D equ 8
D3D10_1_SRV_DIMENSION_TEXTURECUBE equ 9
D3D10_1_SRV_DIMENSION_TEXTURECUBEARRAY equ 10

D3D10_SHADER_RESOURCE_VIEW_DESC1 STRUC
Format			DXGI_FORMAT ?
ViewDimension		D3D10_SRV_DIMENSION1 ?
UNION
 Buffer			 D3D10_BUFFER_SRV <>
 Texture1D		 D3D10_TEX1D_SRV <>
 Texture1DArray		 D3D10_TEX1D_ARRAY_SRV <>
 Texture2D		 D3D10_TEX2D_SRV <>
 Texture2DArray		 D3D10_TEX2D_ARRAY_SRV <>
 Texture2DMS		 D3D10_TEX2DMS_SRV <>
 Texture2DMSArray	 D3D10_TEX2DMS_ARRAY_SRV <>
 Texture3D		 D3D10_TEX3D_SRV <>
 TextureCube		 D3D10_TEXCUBE_SRV <>
 TextureCubeArray	 D3D10_TEXCUBE_ARRAY_SRV1 <>
ENDS
D3D10_SHADER_RESOURCE_VIEW_DESC1 ENDS

ifndef __ID3D10ShaderResourceView1_INTERFACE_DEFINED__
define __ID3D10ShaderResourceView1_INTERFACE_DEFINED__

.comdef ID3D10ShaderResourceView1 : public IUnknown

    GetDevice			proc :ptr
    GetPrivateData		proc :REFGUID, :ptr, :ptr
    SetPrivateData		proc :REFGUID, :UINT, :ptr
    SetPrivateDataInterface	proc :REFGUID, :ptr
    GetResource			proc :ptr
    GetDesc			proc :ptr
    GetDesc1			proc :ptr
   .ends

endif

D3D10_STANDARD_MULTISAMPLE_QUALITY_LEVELS typedef SDWORD
D3D10_STANDARD_MULTISAMPLE_PATTERN equ 0xffffffff
D3D10_CENTER_MULTISAMPLE_PATTERN equ 0xfffffffe

ifndef __ID3D10Device1_INTERFACE_DEFINED__
define __ID3D10Device1_INTERFACE_DEFINED__

.comdef ID3D10Device1 : public IUnknown

    VSSetConstantBuffers	proc :UINT, :UINT, :ptr
    PSSetShaderResources	proc :UINT, :UINT, :ptr
    PSSetShader			proc :ptr
    PSSetSamplers		proc :UINT, :UINT, :ptr
    VSSetShader			proc :ptr
    DrawIndexed			proc :UINT, :UINT, :SINT
    Draw			proc :UINT, :UINT
    PSSetConstantBuffers	proc :UINT, :UINT, :ptr
    IASetInputLayout		proc :ptr
    IASetVertexBuffers		proc :UINT, :UINT, :ptr, :ptr
    IASetIndexBuffer		proc :ptr, :DXGI_FORMAT, :UINT
    DrawIndexedInstanced	proc :UINT, :UINT, :UINT, :SINT, :UINT
    DrawInstanced		proc :UINT, :UINT, :UINT, :UINT
    GSSetConstantBuffers	proc :UINT, :UINT, :ptr
    GSSetShader			proc :ptr
    IASetPrimitiveTopology	proc :D3D10_PRIMITIVE_TOPOLOGY
    VSSetShaderResources	proc :UINT, :UINT, :ptr
    VSSetSamplers		proc :UINT, :UINT, :ptr
    SetPredication		proc :ptr, :BOOL
    GSSetShaderResources	proc :UINT, :UINT, :ptr
    GSSetSamplers		proc :UINT, :UINT, :ptr
    OMSetRenderTargets		proc :UINT
    OMSetBlendState		proc :ptr, :ptr, :UINT
    OMSetDepthStencilState	proc :ptr, :UINT
    SOSetTargets		proc :UINT, :ptr
    DrawAuto			proc
    RSSetState			proc :ptr
    RSSetViewports		proc :UINT, :ptr
    RSSetScissorRects		proc :UINT, :ptr
    CopySubresourceRegion	proc :ptr, :UINT, :UINT, :UINT, :UINT, :ptr, :UINT, :ptr
    CopyResource		proc :ptr, :ptr
    UpdateSubresource		proc :ptr, :UINT, :ptr, :ptr, :UINT, :UINT
    ClearRenderTargetView	proc :ptr, :ptr
    ClearDepthStencilView	proc :ptr, :UINT, :FLOAT, :UINT8
    GenerateMips		proc :ptr
    ResolveSubresource		proc :ptr, :UINT, :ptr, :UINT, :DXGI_FORMAT
    VSGetConstantBuffers	proc :UINT, :UINT, :ptr
    PSGetShaderResources	proc :UINT, :UINT, :ptr
    PSGetShader			proc :ptr
    PSGetSamplers		proc :UINT, :UINT, :ptr
    VSGetShader			proc :ptr
    PSGetConstantBuffers	proc :UINT, :UINT, :ptr
    IAGetInputLayout		proc :ptr
    IAGetVertexBuffers		proc :UINT, :UINT, :ptr, :ptr
    IAGetIndexBuffer		proc :ptr, :ptr, :ptr
    GSGetConstantBuffers	proc :UINT, :UINT, :ptr
    GSGetShader			proc :ptr
    IAGetPrimitiveTopology	proc :ptr
    VSGetShaderResources	proc :UINT, :UINT, :ptr
    VSGetSamplers		proc :UINT, :UINT, :ptr
    GetPredication		proc :ptr, :ptr
    GSGetShaderResources	proc :UINT, :UINT, :ptr
    GSGetSamplers		proc :UINT, :UINT, :ptr
    OMGetRenderTargets		proc :UINT
    OMGetBlendState		proc :ptr, :FLOAT, :ptr
    OMGetDepthStencilState	proc :ptr, :ptr
    SOGetTargets		proc :UINT, :ptr
    RSGetState			proc :ptr
    RSGetViewports		proc :ptr, :ptr
    RSGetScissorRects		proc :ptr, :ptr
    GetDeviceRemovedReason	proc
    SetExceptionMode		proc :UINT
    GetExceptionMode		proc
    GetPrivateData		proc :REFGUID, :ptr, :ptr
    SetPrivateData		proc :REFGUID, :UINT, :ptr
    SetPrivateDataInterface	proc :REFGUID, :ptr
    ClearState			proc
    Flush			proc
    CreateBuffer		proc :ptr, :ptr, :ptr
    CreateTexture1D		proc :ptr
    CreateTexture2D		proc :ptr
    CreateTexture3D		proc :ptr
    CreateShaderResourceView	proc :ptr, :ptr, :ptr
    CreateRenderTargetView	proc :ptr, :ptr, :ptr
    CreateDepthStencilView	proc :ptr, :ptr, :ptr
    CreateInputLayout		proc :UINT, :ptr, :SIZE_T, :ptr
    CreateVertexShader		proc :ptr, :SIZE_T, :ptr
    CreateGeometryShader	proc :ptr, :SIZE_T, :ptr
    CreateGeometryShaderWithStreamOutput proc :ptr, :SIZE_T, :UINT, :UINT, :ptr
    CreatePixelShader		proc :ptr, :SIZE_T, :ptr
    CreateBlendState		proc :ptr, :ptr
    CreateDepthStencilState	proc :ptr, :ptr
    CreateRasterizerState	proc :ptr, :ptr
    CreateSamplerState		proc :ptr, :ptr
    CreateQuery			proc :ptr, :ptr
    CreatePredicate		proc :ptr, :ptr
    CreateCounter		proc :ptr, :ptr
    CheckFormatSupport		proc :DXGI_FORMAT, :ptr
    CheckMultisampleQualityLevels proc :DXGI_FORMAT, :UINT, :ptr
    CheckCounterInfo		proc :ptr
    CheckCounter		proc :ptr, :ptr, :ptr, :LPSTR, :ptr
    GetCreationFlags		proc
    OpenSharedResource		proc :HANDLE, :REFIID, :ptr
    SetTextFilterSize		proc :UINT, :UINT
    GetTextFilterSize		proc :ptr, :ptr
    CreateShaderResourceView1	proc :ptr, :ptr, :ptr
    CreateBlendState1		proc :ptr, :ptr
    GetFeatureLevel		proc
   .ends

endif

D3D10_1_SDK_VERSION	equ ( ( 0 + 0x20 )  )

include d3d10_1shader.inc

CALLBACK(PFN_D3D10_CREATE_DEVICE1, :ptr, :D3D10_DRIVER_TYPE, :HMODULE, :UINT, :D3D10_FEATURE_LEVEL1, :UINT, :ptr)
CALLBACK(PFN_D3D10_CREATE_DEVICE_AND_SWAP_CHAIN1, :ptr, :D3D10_DRIVER_TYPE, :HMODULE, :UINT, :D3D10_FEATURE_LEVEL1, :UINT, :ptr, :ptr, :ptr)

D3D10CreateDevice1 proto WINAPI :ptr, :D3D10_DRIVER_TYPE, :HMODULE, :UINT, :D3D10_FEATURE_LEVEL1, :UINT, :ptr
D3D10CreateDeviceAndSwapChain1 proto WINAPI :ptr, :D3D10_DRIVER_TYPE, :HMODULE, :UINT, :D3D10_FEATURE_LEVEL1, :UINT, :ptr, :ptr, :ptr

DEFINE_GUID(IID_ID3D10BlendState1,0xEDAD8D99,0x8A35,0x4d6d,0x85,0x66,0x2E,0xA2,0x76,0xCD,0xE1,0x61)
DEFINE_GUID(IID_ID3D10ShaderResourceView1,0x9B7E4C87,0x342C,0x4106,0xA1,0x9F,0x4F,0x27,0x04,0xF6,0x89,0xF0)
DEFINE_GUID(IID_ID3D10Device1,0x9B7E4C8F,0x342C,0x4106,0xA1,0x9F,0x4F,0x27,0x04,0xF6,0x89,0xF0)

endif
.pragma list(pop)
