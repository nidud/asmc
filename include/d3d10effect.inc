ifndef __D3D10EFFECT_H__
__D3D10EFFECT_H__ equ <>
include d3d10.inc

D3D10_DEVICE_STATE_TYPES typedef SDWORD
D3D10_DST_SO_BUFFERS	equ 1
D3D10_DST_OM_RENDER_TARGETS equ 1
D3D10_DST_OM_DEPTH_STENCIL_STATE equ 2
D3D10_DST_OM_BLEND_STATE equ 3
D3D10_DST_VS		equ 4
D3D10_DST_VS_SAMPLERS	equ 5
D3D10_DST_VS_SHADER_RESOURCES equ 6
D3D10_DST_VS_CONSTANT_BUFFERS equ 7
D3D10_DST_GS		equ 8
D3D10_DST_GS_SAMPLERS	equ 9
D3D10_DST_GS_SHADER_RESOURCES equ 10
D3D10_DST_GS_CONSTANT_BUFFERS equ 11
D3D10_DST_PS		equ 12
D3D10_DST_PS_SAMPLERS	equ 13
D3D10_DST_PS_SHADER_RESOURCES equ 14
D3D10_DST_PS_CONSTANT_BUFFERS equ 15
D3D10_DST_IA_VERTEX_BUFFERS equ 16
D3D10_DST_IA_INDEX_BUFFER equ 17
D3D10_DST_IA_INPUT_LAYOUT equ 18
D3D10_DST_IA_PRIMITIVE_TOPOLOGY equ 19
D3D10_DST_RS_VIEWPORTS	equ 20
D3D10_DST_RS_SCISSOR_RECTS equ 21
D3D10_DST_RS_RASTERIZER_STATE equ 22
D3D10_DST_PREDICATION	equ 23

ifndef D3D10_BYTES_FROM_BITS
D3D10_BYTES_FROM_BITS macro x
	exitm<(((x) + 7) / 8)>
	endm
endif

D3D10_STATE_BLOCK_MASK	STRUC
VS			db ?
VSSamplers		db D3D10_BYTES_FROM_BITS(D3D10_COMMONSHADER_SAMPLER_SLOT_COUNT) dup(?)
VSShaderResources	db D3D10_BYTES_FROM_BITS(D3D10_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT) dup(?)
VSConstantBuffers	db D3D10_BYTES_FROM_BITS(D3D10_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT) dup(?)
_GS			db ?
GSSamplers		db D3D10_BYTES_FROM_BITS(D3D10_COMMONSHADER_SAMPLER_SLOT_COUNT) dup(?)
GSShaderResources	db D3D10_BYTES_FROM_BITS(D3D10_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT) dup(?)
GSConstantBuffers	db D3D10_BYTES_FROM_BITS(D3D10_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT) dup(?)
PS			db ?
PSSamplers		db D3D10_BYTES_FROM_BITS(D3D10_COMMONSHADER_SAMPLER_SLOT_COUNT) dup(?)
PSShaderResources	db D3D10_BYTES_FROM_BITS(D3D10_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT) dup(?)
PSConstantBuffers	db D3D10_BYTES_FROM_BITS(D3D10_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT) dup(?)
IAVertexBuffers		db D3D10_BYTES_FROM_BITS(D3D10_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT) dup(?)
IAIndexBuffer		db ?
IAInputLayout		db ?
IAPrimitiveTopology	db ?
OMRenderTargets		db ?
OMDepthStencilState	db ?
OMBlendState		db ?
RSViewports		db ?
RSScissorRects		db ?
RSRasterizerState	db ?
SOBuffers		db ?
Predication		db ?
D3D10_STATE_BLOCK_MASK	ENDS

;; {0803425A-57F5-4dd6-9465-A87570834A08}
DEFINE_GUID(IID_ID3D10StateBlock,0x803425a, 0x57f5, 0x4dd6, 0x94, 0x65, 0xa8, 0x75, 0x70, 0x83, 0x4a, 0x8);

.comdef ID3D10StateBlock
    QueryInterface	proc :REFIID, :PVOID
    AddRef		proc
    Release		proc
    Capture		proc
    Apply		proc
    ReleaseAllDeviceObjects proc
    GetDevice		proc :ptr ptr ID3D10Device
    .ends

;HRESULT
D3D10StateBlockMaskUnion proto WINAPI \
		    pA: ptr D3D10_STATE_BLOCK_MASK,
		    pB: ptr D3D10_STATE_BLOCK_MASK,
	       pResult: ptr D3D10_STATE_BLOCK_MASK

;HRESULT
D3D10StateBlockMaskIntersect proto WINAPI \
		    pA: ptr D3D10_STATE_BLOCK_MASK,
		    pB: ptr D3D10_STATE_BLOCK_MASK,
	       pResult: ptr D3D10_STATE_BLOCK_MASK

;HRESULT
D3D10StateBlockMaskDifference proto WINAPI \
		    pA: ptr D3D10_STATE_BLOCK_MASK,
		    pB: ptr D3D10_STATE_BLOCK_MASK,
	       pResult: ptr D3D10_STATE_BLOCK_MASK

;HRESULT
D3D10StateBlockMaskEnableCapture proto WINAPI \
		 pMask: ptr D3D10_STATE_BLOCK_MASK,
	     StateType: D3D10_DEVICE_STATE_TYPES,
	    RangeStart: UINT,
	   RangeLength: UINT

;HRESULT
D3D10StateBlockMaskDisableCapture proto WINAPI \
		 pMask: ptr D3D10_STATE_BLOCK_MASK,
	     StateType: D3D10_DEVICE_STATE_TYPES,
	    RangeStart: UINT,
	   RangeLength: UINT

;HRESULT
D3D10StateBlockMaskEnableAll proto WINAPI \
		 pMask: ptr D3D10_STATE_BLOCK_MASK

;HRESULT
D3D10StateBlockMaskDisableAll proto WINAPI \
		 pMask: ptr D3D10_STATE_BLOCK_MASK

;BOOL
D3D10StateBlockMaskGetSetting proto WINAPI \
		 pMask: ptr D3D10_STATE_BLOCK_MASK,
	     StateType: D3D10_DEVICE_STATE_TYPES,
		 Entry: UINT


;HRESULT
D3D10CreateStateBlock proto WINAPI \
	       pDevice: ptr ID3D10Device,
       pStateBlockMask: ptr D3D10_STATE_BLOCK_MASK,
	  ppStateBlock: ptr ID3D10StateBlock


D3D10_EFFECT_COMPILE_CHILD_EFFECT equ (1 SHL 0)
D3D10_EFFECT_COMPILE_ALLOW_SLOW_OPS equ (1 SHL 1)
D3D10_EFFECT_SINGLE_THREADED equ (1 SHL 3)

D3D10_EFFECT_VARIABLE_POOLED equ (1 SHL 0)
D3D10_EFFECT_VARIABLE_ANNOTATION equ (1 SHL 1)
D3D10_EFFECT_VARIABLE_EXPLICIT_BIND_POINT equ (1 SHL 2)

D3D10_EFFECT_TYPE_DESC	STRUC
TypeName		LPCSTR ?
Class			D3D10_SHADER_VARIABLE_CLASS ?
_Type			D3D10_SHADER_VARIABLE_TYPE ?
Elements		UINT ?
Members			UINT ?
Rows			UINT ?
Columns			UINT ?
BackedSize		UINT ?
UnpackedSize		UINT ?
Stride			UINT ?
D3D10_EFFECT_TYPE_DESC	ENDS


;; {4E9E1DDC-CD9D-4772-A837-00180B9B88FD}
DEFINE_GUID(IID_ID3D10EffectType,0x4e9e1ddc, 0xcd9d, 0x4772, 0xa8, 0x37, 0x0, 0x18, 0xb, 0x9b, 0x88, 0xfd);

.comdef ID3D10EffectType
    IsValid			proc
    GetDesc			proc :ptr D3D10_EFFECT_TYPE_DESC
    GetMemberTypeByIndex	proc :UINT
    GetMemberTypeByName		proc :LPCSTR
    GetMemberTypeBySemantic	proc :LPCSTR
    GetMemberName		proc :UINT
    GetMemberSemantic		proc :UINT
    .ends


D3D10_EFFECT_VARIABLE_DESC	STRUC
_Name				LPCSTR ?
Semantic			LPCSTR ?
Flags				UINT ?
Annotations			UINT ?
BufferOffset			UINT ?
ExplicitBindPoint		UINT ?
;D3D10_EFFECT_VARIABLE_EXPLICIT_BIND_POINT
D3D10_EFFECT_VARIABLE_DESC	ENDS


;; {AE897105-00E6-45bf-BB8E-281DD6DB8E1B}
DEFINE_GUID(IID_ID3D10EffectVariable,0xae897105, 0xe6, 0x45bf, 0xbb, 0x8e, 0x28, 0x1d, 0xd6, 0xdb, 0x8e, 0x1b);

.comdef ID3D10EffectVariable
    IsValid			proc
    GetType			proc
    GetDesc			proc :ptr D3D10_EFFECT_VARIABLE_DESC
    GetAnnotationByIndex	proc :UINT
    GetAnnotationByName		proc :LPCSTR
    GetMemberByIndex		proc :UINT
    GetMemberByName		proc :LPCSTR
    GetMemberBySemantic		proc :LPCSTR
    GetElement			proc :UINT
    GetParentConstantBuffer	proc
    AsScalar			proc
    AsVector			proc
    AsMatrix			proc
    AsString			proc
    AsShaderResource		proc
    AsRenderTargetView		proc
    AsDepthStencilView		proc
    AsConstantBuffer		proc
    AsShader			proc
    AsBlend			proc
    AsDepthStencil		proc
    AsRasterizer		proc
    AsSampler			proc
    SetRawValue			proc :PVOID, :UINT, :UINT
    GetRawValue			proc :PVOID, :UINT, :UINT
    .ends

;; {00E48F7B-D2C8-49e8-A86C-022DEE53431F}
DEFINE_GUID(IID_ID3D10EffectScalarVariable,0xe48f7b, 0xd2c8, 0x49e8, 0xa8, 0x6c, 0x2, 0x2d, 0xee, 0x53, 0x43, 0x1f);

.comdef ID3D10EffectScalarVariable
    IsValid			proc
    GetType			proc
    GetDesc			proc :ptr D3D10_EFFECT_VARIABLE_DESC
    GetAnnotationByIndex	proc :UINT
    GetAnnotationByName		proc :LPCSTR
    GetMemberByIndex		proc :UINT
    GetMemberByName		proc :LPCSTR
    GetMemberBySemantic		proc :LPCSTR
    GetElement			proc :UINT
    GetParentConstantBuffer	proc
    AsScalar			proc
    AsVector			proc
    AsMatrix			proc
    AsString			proc
    AsShaderResource		proc
    AsRenderTargetView		proc
    AsDepthStencilView		proc
    AsConstantBuffer		proc
    AsShader			proc
    AsBlend			proc
    AsDepthStencil		proc
    AsRasterizer		proc
    AsSampler			proc
    SetRawValue			proc :PVOID, :UINT, :UINT
    GetRawValue			proc :PVOID, :UINT, :UINT
    SetFloat			proc :REAL4
    GetFloat			proc :ptr
    SetFloatArray		proc :ptr, :UINT, :UINT
    GetFloatArray		proc :ptr, :UINT, :UINT
    SetInt			proc :SINT
    GetInt			proc :ptr
    SetIntArray			proc :ptr, :UINT, :UINT
    GetIntArray			proc :ptr, :UINT, :UINT
    SetBool			proc :BOOL
    GetBool			proc :ptr
    SetBoolArray		proc :ptr, :UINT, :UINT
    GetBoolArray		proc :ptr, :UINT, :UINT
    .ends

;; {62B98C44-1F82-4c67-BCD0-72CF8F217E81}
DEFINE_GUID(IID_ID3D10EffectVectorVariable,0x62b98c44, 0x1f82, 0x4c67, 0xbc, 0xd0, 0x72, 0xcf, 0x8f, 0x21, 0x7e, 0x81);

.comdef ID3D10EffectVectorVariable
    IsValid			proc
    GetType			proc
    GetDesc			proc :ptr D3D10_EFFECT_VARIABLE_DESC
    GetAnnotationByIndex	proc :UINT
    GetAnnotationByName		proc :LPCSTR
    GetMemberByIndex		proc :UINT
    GetMemberByName		proc :LPCSTR
    GetMemberBySemantic		proc :LPCSTR
    GetElement			proc :UINT
    GetParentConstantBuffer	proc
    AsScalar			proc
    AsVector			proc
    AsMatrix			proc
    AsString			proc
    AsShaderResource		proc
    AsRenderTargetView		proc
    AsDepthStencilView		proc
    AsConstantBuffer		proc
    AsShader			proc
    AsBlend			proc
    AsDepthStencil		proc
    AsRasterizer		proc
    AsSampler			proc
    SetRawValue			proc :PVOID, :UINT, :UINT
    GetRawValue			proc :PVOID, :UINT, :UINT
    SetBoolVector		proc :ptr
    SetIntVector		proc :ptr
    SetFloatVector		proc :ptr
    GetBoolVector		proc :ptr
    GetIntVector		proc :ptr
    GetFloatVector		proc :ptr
    SetBoolVectorArray		proc :ptr, :UINT, :UINT
    SetIntVectorArray		proc :ptr, :UINT, :UINT
    SetFloatVectorArray		proc :ptr, :UINT, :UINT
    GetBoolVectorArray		proc :ptr, :UINT, :UINT
    GetIntVectorArray		proc :ptr, :UINT, :UINT
    GetFloatVectorArray		proc :ptr, :UINT, :UINT
    .ends


;; {50666C24-B82F-4eed-A172-5B6E7E8522E0}
DEFINE_GUID(IID_ID3D10EffectMatrixVariable,0x50666c24, 0xb82f, 0x4eed, 0xa1, 0x72, 0x5b, 0x6e, 0x7e, 0x85, 0x22, 0xe0);

.comdef ID3D10EffectMatrixVariable
    IsValid			proc
    GetType			proc
    GetDesc			proc :ptr D3D10_EFFECT_VARIABLE_DESC
    GetAnnotationByIndex	proc :UINT
    GetAnnotationByName		proc :LPCSTR
    GetMemberByIndex		proc :UINT
    GetMemberByName		proc :LPCSTR
    GetMemberBySemantic		proc :LPCSTR
    GetElement			proc :UINT
    GetParentConstantBuffer	proc
    AsScalar			proc
    AsVector			proc
    AsMatrix			proc
    AsString			proc
    AsShaderResource		proc
    AsRenderTargetView		proc
    AsDepthStencilView		proc
    AsConstantBuffer		proc
    AsShader			proc
    AsBlend			proc
    AsDepthStencil		proc
    AsRasterizer		proc
    AsSampler			proc
    SetRawValue			proc :PVOID, :UINT, :UINT
    GetRawValue			proc :PVOID, :UINT, :UINT
    SetMatrix			proc :ptr
    GetMatrix			proc :ptr
    SetMatrixArray		proc :ptr, :UINT, :UINT
    GetMatrixArray		proc :ptr, :UINT, :UINT
    SetMatrixTranspose		proc :ptr
    GetMatrixTranspose		proc :ptr
    SetMatrixTransposeArray	proc :ptr, :UINT, :UINT
    GetMatrixTransposeArray	proc :ptr, :UINT, :UINT
    .ends

;; {71417501-8DF9-4e0a-A78A-255F9756BAFF}
DEFINE_GUID(IID_ID3D10EffectStringVariable,0x71417501, 0x8df9, 0x4e0a, 0xa7, 0x8a, 0x25, 0x5f, 0x97, 0x56, 0xba, 0xff);

.comdef ID3D10EffectStringVariable
    IsValid			proc
    GetType			proc
    GetDesc			proc :ptr D3D10_EFFECT_VARIABLE_DESC
    GetAnnotationByIndex	proc :UINT
    GetAnnotationByName		proc :LPCSTR
    GetMemberByIndex		proc :UINT
    GetMemberByName		proc :LPCSTR
    GetMemberBySemantic		proc :LPCSTR
    GetElement			proc :UINT
    GetParentConstantBuffer	proc
    AsScalar			proc
    AsVector			proc
    AsMatrix			proc
    AsString			proc
    AsShaderResource		proc
    AsRenderTargetView		proc
    AsDepthStencilView		proc
    AsConstantBuffer		proc
    AsShader			proc
    AsBlend			proc
    AsDepthStencil		proc
    AsRasterizer		proc
    AsSampler			proc
    SetRawValue			proc :PVOID, :UINT, :UINT
    GetRawValue			proc :PVOID, :UINT, :UINT
    GetString			proc :LPCSTR
    GetStringArray		proc :LPCSTR, :UINT, :UINT
    .ends

;; {C0A7157B-D872-4b1d-8073-EFC2ACD4B1FC}
DEFINE_GUID(IID_ID3D10EffectShaderResourceVariable,0xc0a7157b, 0xd872, 0x4b1d, 0x80, 0x73, 0xef, 0xc2, 0xac, 0xd4, 0xb1, 0xfc);

.comdef ID3D10EffectShaderResourceVariable
    IsValid			proc
    GetType			proc
    GetDesc			proc :ptr D3D10_EFFECT_VARIABLE_DESC
    GetAnnotationByIndex	proc :UINT
    GetAnnotationByName		proc :LPCSTR
    GetMemberByIndex		proc :UINT
    GetMemberByName		proc :LPCSTR
    GetMemberBySemantic		proc :LPCSTR
    GetElement			proc :UINT
    GetParentConstantBuffer	proc
    AsScalar			proc
    AsVector			proc
    AsMatrix			proc
    AsString			proc
    AsShaderResource		proc
    AsRenderTargetView		proc
    AsDepthStencilView		proc
    AsConstantBuffer		proc
    AsShader			proc
    AsBlend			proc
    AsDepthStencil		proc
    AsRasterizer		proc
    AsSampler			proc
    SetRawValue			proc :PVOID, :UINT, :UINT
    GetRawValue			proc :PVOID, :UINT, :UINT
    SetResource			proc :ptr ID3D10ShaderResourceView
    GetResource			proc :ptr ptr ID3D10ShaderResourceView
    SetResourceArray		proc :ptr ptr ID3D10ShaderResourceView, :UINT, :UINT
    GetResourceArray		proc :ptr ptr ID3D10ShaderResourceView, :UINT, :UINT
    .ends

;; {28CA0CC3-C2C9-40bb-B57F-67B737122B17}
DEFINE_GUID(IID_ID3D10EffectRenderTargetViewVariable,0x28ca0cc3, 0xc2c9, 0x40bb, 0xb5, 0x7f, 0x67, 0xb7, 0x37, 0x12, 0x2b, 0x17);

.comdef ID3D10EffectRenderTargetViewVariable
    IsValid			proc
    GetType			proc
    GetDesc			proc :ptr D3D10_EFFECT_VARIABLE_DESC
    GetAnnotationByIndex	proc :UINT
    GetAnnotationByName		proc :LPCSTR
    GetMemberByIndex		proc :UINT
    GetMemberByName		proc :LPCSTR
    GetMemberBySemantic		proc :LPCSTR
    GetElement			proc :UINT
    GetParentConstantBuffer	proc
    AsScalar			proc
    AsVector			proc
    AsMatrix			proc
    AsString			proc
    AsShaderResource		proc
    AsRenderTargetView		proc
    AsDepthStencilView		proc
    AsConstantBuffer		proc
    AsShader			proc
    AsBlend			proc
    AsDepthStencil		proc
    AsRasterizer		proc
    AsSampler			proc
    SetRawValue			proc :PVOID, :UINT, :UINT
    GetRawValue			proc :PVOID, :UINT, :UINT
    SetRenderTarget		proc :ptr ID3D10RenderTargetView
    GetRenderTarget		proc :ptr ptr ID3D10RenderTargetView
    SetRenderTargetArray	proc :ptr ptr ID3D10RenderTargetView, :UINT, :UINT
    GetRenderTargetArray	proc :ptr ptr ID3D10RenderTargetView, :UINT, :UINT
    .ends

;; {3E02C918-CC79-4985-B622-2D92AD701623}
DEFINE_GUID(IID_ID3D10EffectDepthStencilViewVariable,0x3e02c918, 0xcc79, 0x4985, 0xb6, 0x22, 0x2d, 0x92, 0xad, 0x70, 0x16, 0x23);

.comdef ID3D10EffectDepthStencilViewVariable
    IsValid			proc
    GetType			proc
    GetDesc			proc :ptr D3D10_EFFECT_VARIABLE_DESC
    GetAnnotationByIndex	proc :UINT
    GetAnnotationByName		proc :LPCSTR
    GetMemberByIndex		proc :UINT
    GetMemberByName		proc :LPCSTR
    GetMemberBySemantic		proc :LPCSTR
    GetElement			proc :UINT
    GetParentConstantBuffer	proc
    AsScalar			proc
    AsVector			proc
    AsMatrix			proc
    AsString			proc
    AsShaderResource		proc
    AsRenderTargetView		proc
    AsDepthStencilView		proc
    AsConstantBuffer		proc
    AsShader			proc
    AsBlend			proc
    AsDepthStencil		proc
    AsRasterizer		proc
    AsSampler			proc
    SetRawValue			proc :PVOID, :UINT, :UINT
    GetRawValue			proc :PVOID, :UINT, :UINT
    SetDepthStencil		proc :ptr ID3D10DepthStencilView
    GetDepthStencil		proc :ptr ptr ID3D10DepthStencilView
    SetDepthStencilArray	proc :ptr ptr ID3D10DepthStencilView, :UINT, :UINT
    GetDepthStencilArray	proc :ptr ptr ID3D10DepthStencilView, :UINT, :UINT
    .ends

;; {56648F4D-CC8B-4444-A5AD-B5A3D76E91B3}
DEFINE_GUID(IID_ID3D10EffectConstantBuffer,0x56648f4d, 0xcc8b, 0x4444, 0xa5, 0xad, 0xb5, 0xa3, 0xd7, 0x6e, 0x91, 0xb3);

.comdef ID3D10EffectConstantBuffer
    GetType			proc
    GetDesc			proc :ptr D3D10_EFFECT_VARIABLE_DESC
    GetAnnotationByIndex	proc :UINT
    GetAnnotationByName		proc :LPCSTR
    GetMemberByIndex		proc :UINT
    GetMemberByName		proc :LPCSTR
    GetMemberBySemantic		proc :LPCSTR
    GetElement			proc :UINT
    GetParentConstantBuffer	proc
    AsScalar			proc
    AsVector			proc
    AsMatrix			proc
    AsString			proc
    AsShaderResource		proc
    AsRenderTargetView		proc
    AsDepthStencilView		proc
    AsConstantBuffer		proc
    AsShader			proc
    AsBlend			proc
    AsDepthStencil		proc
    AsRasterizer		proc
    AsSampler			proc
    SetRawValue			proc :PVOID, :UINT, :UINT
    GetRawValue			proc :PVOID, :UINT, :UINT
    SetConstantBuffer		proc :ptr ID3D10Buffer
    GetConstantBuffer		proc :ptr ptr ID3D10Buffer
    SetTextureBuffer		proc :ptr ID3D10ShaderResourceView
    GetTextureBuffer		proc :ptr ptr ID3D10ShaderResourceView
    .ends

D3D10_EFFECT_SHADER_DESC	STRUC
pInputSignature			LPBYTE ?
IsInline			BOOL ?
pBytecode			LPBYTE ?
BytecodeLength			UINT ?
SODecl				LPCSTR ?
NumInputSignatureEntries	UINT ?
NumOutputSignatureEntries	UINT ?
D3D10_EFFECT_SHADER_DESC	ENDS


;; {80849279-C799-4797-8C33-0407A07D9E06}
DEFINE_GUID(IID_ID3D10EffectShaderVariable,0x80849279, 0xc799, 0x4797, 0x8c, 0x33, 0x4, 0x7, 0xa0, 0x7d, 0x9e, 0x6);

.comdef ID3D10EffectShaderVariable
    GetType			proc
    GetDesc			proc :ptr D3D10_EFFECT_VARIABLE_DESC
    GetAnnotationByIndex	proc :UINT
    GetAnnotationByName		proc :LPCSTR
    GetMemberByIndex		proc :UINT
    GetMemberByName		proc :LPCSTR
    GetMemberBySemantic		proc :LPCSTR
    GetElement			proc :UINT
    GetParentConstantBuffer	proc
    AsScalar			proc
    AsVector			proc
    AsMatrix			proc
    AsString			proc
    AsShaderResource		proc
    AsRenderTargetView		proc
    AsDepthStencilView		proc
    AsConstantBuffer		proc
    AsShader			proc
    AsBlend			proc
    AsDepthStencil		proc
    AsRasterizer		proc
    AsSampler			proc
    SetRawValue			proc :PVOID, :UINT, :UINT
    GetRawValue			proc :PVOID, :UINT, :UINT
    GetShaderDesc		proc :UINT, :ptr D3D10_EFFECT_SHADER_DESC
    GetVertexShader		proc :UINT, :ptr ptr ID3D10VertexShader
    GetGeometryShader		proc :UINT, :ptr ptr ID3D10GeometryShader
    GetPixelShader		proc :UINT, :ptr ptr ID3D10PixelShader
    GetInputSignatureElementDesc proc :UINT, :UINT, :ptr D3D10_SIGNATURE_PARAMETER_DESC
    GetOutputSignatureElementDesc proc :UINT, :UINT, :ptr D3D10_SIGNATURE_PARAMETER_DESC
    .ends


;; {1FCD2294-DF6D-4eae-86B3-0E9160CFB07B}
DEFINE_GUID(IID_ID3D10EffectBlendVariable,0x1fcd2294, 0xdf6d, 0x4eae, 0x86, 0xb3, 0xe, 0x91, 0x60, 0xcf, 0xb0, 0x7b);

.comdef ID3D10EffectBlendVariable
    GetType			proc
    GetDesc			proc :ptr D3D10_EFFECT_VARIABLE_DESC
    GetAnnotationByIndex	proc :UINT
    GetAnnotationByName		proc :LPCSTR
    GetMemberByIndex		proc :UINT
    GetMemberByName		proc :LPCSTR
    GetMemberBySemantic		proc :LPCSTR
    GetElement			proc :UINT
    GetParentConstantBuffer	proc
    AsScalar			proc
    AsVector			proc
    AsMatrix			proc
    AsString			proc
    AsShaderResource		proc
    AsRenderTargetView		proc
    AsDepthStencilView		proc
    AsConstantBuffer		proc
    AsShader			proc
    AsBlend			proc
    AsDepthStencil		proc
    AsRasterizer		proc
    AsSampler			proc
    SetRawValue			proc :PVOID, :UINT, :UINT
    GetRawValue			proc :PVOID, :UINT, :UINT
    GetBlendState		proc :UINT, :ptr ptr ID3D10BlendState
    GetBackingStore		proc :UINT, :ptr D3D10_BLEND_DESC
    .ends


;; {AF482368-330A-46a5-9A5C-01C71AF24C8D}
DEFINE_GUID(IID_ID3D10EffectDepthStencilVariable,0xaf482368, 0x330a, 0x46a5, 0x9a, 0x5c, 0x1, 0xc7, 0x1a, 0xf2, 0x4c, 0x8d);

.comdef ID3D10EffectDepthStencilVariable
	GetType			proc
	GetDesc			proc :ptr D3D10_EFFECT_VARIABLE_DESC
	GetAnnotationByIndex	proc :UINT
	GetAnnotationByName	proc :LPCSTR
	GetMemberByIndex	proc :UINT
	GetMemberByName		proc :LPCSTR
	GetMemberBySemantic	proc :LPCSTR
	GetElement		proc :UINT
	GetParentConstantBuffer proc
	AsScalar		proc
	AsVector		proc
	AsMatrix		proc
	AsString		proc
	AsShaderResource	proc
	AsRenderTargetView	proc
	AsDepthStencilView	proc
	AsConstantBuffer	proc
	AsShader		proc
	AsBlend			proc
	AsDepthStencil		proc
	AsRasterizer		proc
	AsSampler		proc
	SetRawValue		proc :PVOID, :UINT, :UINT
	GetRawValue		proc :PVOID, :UINT, :UINT
	GetDepthStencilState	proc :UINT, :ptr ptr ID3D10DepthStencilState
	GetBackingStore		proc :UINT, :ptr D3D10_DEPTH_STENCIL_DESC
    .ends

;; {21AF9F0E-4D94-4ea9-9785-2CB76B8C0B34}
DEFINE_GUID(IID_ID3D10EffectRasterizerVariable,0x21af9f0e, 0x4d94, 0x4ea9, 0x97, 0x85, 0x2c, 0xb7, 0x6b, 0x8c, 0xb, 0x34);

.comdef ID3D10EffectRasterizerVariable
	GetType			proc
	GetDesc			proc :ptr D3D10_EFFECT_VARIABLE_DESC
	GetAnnotationByIndex	proc :UINT
	GetAnnotationByName	proc :LPCSTR
	GetMemberByIndex	proc :UINT
	GetMemberByName		proc :LPCSTR
	GetMemberBySemantic	proc :LPCSTR
	GetElement		proc :UINT
	GetParentConstantBuffer proc
	AsScalar		proc
	AsVector		proc
	AsMatrix		proc
	AsString		proc
	AsShaderResource	proc
	AsRenderTargetView	proc
	AsDepthStencilView	proc
	AsConstantBuffer	proc
	AsShader		proc
	AsBlend			proc
	AsDepthStencil		proc
	AsRasterizer		proc
	AsSampler		proc
	SetRawValue		proc :PVOID, :UINT, :UINT
	GetRawValue		proc :PVOID, :UINT, :UINT
	GetRasterizerState	proc :UINT, :ptr ptr ID3D10RasterizerState
	GetBackingStore		proc :UINT, :ptr D3D10_RASTERIZER_DESC
    .ends


;; {6530D5C7-07E9-4271-A418-E7CE4BD1E480}
DEFINE_GUID(IID_ID3D10EffectSamplerVariable, 0x6530d5c7, 0x7e9, 0x4271, 0xa4, 0x18, 0xe7, 0xce, 0x4b, 0xd1, 0xe4, 0x80);

.comdef ID3D10EffectSamplerVariable
	GetType			proc
	GetDesc			proc :ptr D3D10_EFFECT_VARIABLE_DESC
	GetAnnotationByIndex	proc :UINT
	GetAnnotationByName	proc :LPCSTR
	GetMemberByIndex	proc :UINT
	GetMemberByName		proc :LPCSTR
	GetMemberBySemantic	proc :LPCSTR
	GetElement		proc :UINT
	GetParentConstantBuffer proc
	AsScalar		proc
	AsVector		proc
	AsMatrix		proc
	AsString		proc
	AsShaderResource	proc
	AsRenderTargetView	proc
	AsDepthStencilView	proc
	AsConstantBuffer	proc
	AsShader		proc
	AsBlend			proc
	AsDepthStencil		proc
	AsRasterizer		proc
	AsSampler		proc
	SetRawValue		proc :PVOID, :UINT, :UINT
	GetRawValue		proc :PVOID, :UINT, :UINT
	GetSampler		proc :UINT, :ptr ptr ID3D10SamplerState
	GetBackingStore		proc :UINT, :ptr D3D10_SAMPLER_DESC
    .ends

LPID3D10EffectShaderVariable	typedef ptr ID3D10EffectShaderVariable

D3D10_PASS_DESC		STRUC
_Name			LPCSTR ?
Annotations		UINT ?
pIAInputSignature	LPBYTE ?
IAInputSignatureSize	SIZE_T ?
StencilRef		UINT ?
SampleMask		UINT ?
BlendFactor		FLOAT 4 dup(?)
D3D10_PASS_DESC		ENDS

D3D10_PASS_SHADER_DESC	STRUC
pShaderVariable		LPID3D10EffectShaderVariable ?
ShaderIndex		UINT ?
D3D10_PASS_SHADER_DESC	ENDS


;; {5CFBEB89-1A06-46e0-B282-E3F9BFA36A54}
DEFINE_GUID(IID_ID3D10EffectPass,0x5cfbeb89, 0x1a06, 0x46e0, 0xb2, 0x82, 0xe3, 0xf9, 0xbf, 0xa3, 0x6a, 0x54);

.comdef ID3D10EffectPass
    IsValid			proc
    GetDesc			proc :ptr D3D10_PASS_DESC
    GetVertexShaderDesc		proc :ptr D3D10_PASS_SHADER_DESC
    GetGeometryShaderDesc	proc :ptr D3D10_PASS_SHADER_DESC
    GetPixelShaderDesc		proc :ptr D3D10_PASS_SHADER_DESC
    GetAnnotationByIndex	proc :UINT
    GetAnnotationByName		proc :LPCSTR
    Apply			proc :UINT
    ComputeStateBlockMask	proc :ptr D3D10_STATE_BLOCK_MASK
    .ends

D3D10_TECHNIQUE_DESC	STRUC
_Name			LPCSTR ?
Passes			UINT ?
Annotations		UINT ?
D3D10_TECHNIQUE_DESC	ENDS


;; {DB122CE8-D1C9-4292-B237-24ED3DE8B175}
DEFINE_GUID(IID_ID3D10EffectTechnique,0xdb122ce8, 0xd1c9, 0x4292, 0xb2, 0x37, 0x24, 0xed, 0x3d, 0xe8, 0xb1, 0x75);

.comdef ID3D10EffectTechnique
    IsValid			proc
    GetDesc			proc :ptr D3D10_TECHNIQUE_DESC
    GetAnnotationByIndex	proc :UINT
    GetAnnotationByName		proc :LPCSTR
    GetPassByIndex		proc :UINT
    GetPassByName		proc :LPCSTR
    ComputeStateBlockMask	proc :ptr D3D10_STATE_BLOCK_MASK
    .ends


D3D10_EFFECT_DESC	STRUC
IsChildEffect		BOOL ?
ConstantBuffers		UINT ?
SharedConstantBuffers	UINT ?
GlobalVariables		UINT ?
SharedGlobalVariables	UINT ?
Techniques		UINT ?
D3D10_EFFECT_DESC	ENDS


;; {51B0CA8B-EC0B-4519-870D-8EE1CB5017C7}
DEFINE_GUID(IID_ID3D10Effect,0x51b0ca8b, 0xec0b, 0x4519, 0x87, 0xd, 0x8e, 0xe1, 0xcb, 0x50, 0x17, 0xc7);

.comdef ID3D10Effect
    QueryInterface		proc :REFIID, :PVOID
    AddRef			proc
    Release			proc
    IsValid			proc
    IsPool			proc
    GetDevice			proc :ptr ptr ID3D10Device
    GetDesc			proc :ptr D3D10_EFFECT_DESC
    GetConstantBufferByIndex	proc :UINT
    GetConstantBufferByName	proc :LPCSTR
    GetVariableByIndex		proc :UINT
    GetVariableByName		proc :LPCSTR
    GetVariableBySemantic	proc :LPCSTR
    GetTechniqueByIndex		proc :UINT
    GetTechniqueByName		proc :LPCSTR
    Optimize			proc
    IsOptimized			proc
    .ends

;; {9537AB04-3250-412e-8213-FCD2F8677933}
DEFINE_GUID(IID_ID3D10EffectPool,0x9537ab04, 0x3250, 0x412e, 0x82, 0x13, 0xfc, 0xd2, 0xf8, 0x67, 0x79, 0x33);

.comdef ID3D10EffectPool
    QueryInterface	proc :REFIID, :PVOID
    AddRef		proc
    Release		proc
    AsEffect		proc
    .ends


;HRESULT
D3D10CompileEffectFromMemory proto WINAPI \
		 pData: ptr void,
	    DataLength: SIZE_T,
	  pSrcFileName: LPCSTR,
	      pDefines: ptr D3D10_SHADER_MACRO,
	      pInclude: ptr ID3D10Include,
	     HLSLFlags: UINT,
	       FXFlags: UINT,
      ppCompiledEffect: ptr ID3D10Blob,
	      ppErrors: ptr ID3D10Blob


;HRESULT
D3D10CreateEffectFromMemory proto WINAPI \
		 pData: ptr void,
	    DataLength: SIZE_T,
	       FXFlags: UINT,
	       pDevice: ptr ID3D10Device,
	   pEffectPool: ptr ID3D10EffectPool,
	      ppEffect: ptr ID3D10Effect


;HRESULT
D3D10CreateEffectPoolFromMemory proto WINAPI \
		 pData: ptr void,
	    DataLength: SIZE_T,
	       FXFlags: UINT,
	       pDevice: ptr ID3D10Device,
	  ppEffectPool: ptr ID3D10EffectPool


;HRESULT
D3D10DisassembleEffect proto WINAPI \
	       pEffect: ptr ID3D10Effect,
       EnableColorCode: BOOL,
	 ppDisassembly: ptr ID3D10Blob


endif
