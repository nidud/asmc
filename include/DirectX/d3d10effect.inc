ifndef __D3D10EFFECT_H__
define __D3D10EFFECT_H__
include d3d10.inc

.enum D3D10_DEVICE_STATE_TYPES {

    D3D10_DST_SO_BUFFERS = 1,
    D3D10_DST_OM_RENDER_TARGETS,
    D3D10_DST_OM_DEPTH_STENCIL_STATE,
    D3D10_DST_OM_BLEND_STATE,

    D3D10_DST_VS,
    D3D10_DST_VS_SAMPLERS,
    D3D10_DST_VS_SHADER_RESOURCES,
    D3D10_DST_VS_CONSTANT_BUFFERS,

    D3D10_DST_GS,
    D3D10_DST_GS_SAMPLERS,
    D3D10_DST_GS_SHADER_RESOURCES,
    D3D10_DST_GS_CONSTANT_BUFFERS,

    D3D10_DST_PS,
    D3D10_DST_PS_SAMPLERS,
    D3D10_DST_PS_SHADER_RESOURCES,
    D3D10_DST_PS_CONSTANT_BUFFERS,

    D3D10_DST_IA_VERTEX_BUFFERS,
    D3D10_DST_IA_INDEX_BUFFER,
    D3D10_DST_IA_INPUT_LAYOUT,
    D3D10_DST_IA_PRIMITIVE_TOPOLOGY,

    D3D10_DST_RS_VIEWPORTS,
    D3D10_DST_RS_SCISSOR_RECTS,
    D3D10_DST_RS_RASTERIZER_STATE,
    D3D10_DST_PREDICATION
    }

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


DEFINE_GUID(IID_ID3D10StateBlock,0x803425a,0x57f5,0x4dd6,0x94,0x65,0xa8,0x75,0x70,0x83,0x4a,0x8)

.comdef ID3D10StateBlock : public IUnknown

    Capture		proc
    Apply		proc
    ReleaseAllDeviceObjects proc
    GetDevice		proc :ptr
   .ends

D3D10StateBlockMaskUnion proto WINAPI :ptr, :ptr, :ptr
D3D10StateBlockMaskIntersect proto WINAPI :ptr, :ptr, :ptr
D3D10StateBlockMaskDifference proto WINAPI :ptr, :ptr, :ptr
D3D10StateBlockMaskEnableCapture proto WINAPI :ptr, :D3D10_DEVICE_STATE_TYPES, :UINT, :UINT
D3D10StateBlockMaskDisableCapture proto WINAPI :ptr, :D3D10_DEVICE_STATE_TYPES, :UINT, :UINT
D3D10StateBlockMaskEnableAll proto WINAPI :ptr
D3D10StateBlockMaskDisableAll proto WINAPI :ptr
D3D10StateBlockMaskGetSetting proto WINAPI :ptr, :D3D10_DEVICE_STATE_TYPES, :UINT
D3D10CreateStateBlock proto WINAPI :ptr, :ptr, :ptr

D3D10_EFFECT_COMPILE_CHILD_EFFECT equ (1 SHL 0)
D3D10_EFFECT_COMPILE_ALLOW_SLOW_OPS equ (1 SHL 1)
D3D10_EFFECT_SINGLE_THREADED equ (1 SHL 3)

D3D10_EFFECT_VARIABLE_POOLED equ (1 SHL 0)
D3D10_EFFECT_VARIABLE_ANNOTATION equ (1 SHL 1)
D3D10_EFFECT_VARIABLE_EXPLICIT_BIND_POINT equ (1 SHL 2)

D3D10_EFFECT_TYPE_DESC	STRUC
TypeName		LPCSTR ?
Class			D3D10_SHADER_VARIABLE_CLASS ?
Type			D3D10_SHADER_VARIABLE_TYPE ?
Elements		UINT ?
Members			UINT ?
Rows			UINT ?
Columns			UINT ?
BackedSize		UINT ?
UnpackedSize		UINT ?
Stride			UINT ?
D3D10_EFFECT_TYPE_DESC	ENDS

DEFINE_GUID(IID_ID3D10EffectType,0x4e9e1ddc,0xcd9d,0x4772,0xa8,0x37,0x0,0x18,0xb,0x9b,0x88,0xfd);

.comdef ID3D10EffectType

    IsValid			proc
    GetDesc			proc :ptr
    GetMemberTypeByIndex	proc :UINT
    GetMemberTypeByName		proc :LPCSTR
    GetMemberTypeBySemantic	proc :LPCSTR
    GetMemberName		proc :UINT
    GetMemberSemantic		proc :UINT
   .ends

D3D10_EFFECT_VARIABLE_DESC	STRUC
Name				LPCSTR ?
Semantic			LPCSTR ?
Flags				UINT ?
Annotations			UINT ?
BufferOffset			UINT ?
ExplicitBindPoint		UINT ?
D3D10_EFFECT_VARIABLE_DESC	ENDS

DEFINE_GUID(IID_ID3D10EffectVariable,0xae897105,0xe6,0x45bf,0xbb,0x8e,0x28,0x1d,0xd6,0xdb,0x8e,0x1b)

.comdef ID3D10EffectVariable

    IsValid			proc
    GetType			proc
    GetDesc			proc :ptr
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

DEFINE_GUID(IID_ID3D10EffectScalarVariable,0xe48f7b,0xd2c8,0x49e8,0xa8,0x6c,0x2,0x2d,0xee,0x53,0x43,0x1f)

.comdef ID3D10EffectScalarVariable : public ID3D10EffectVariable

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

DEFINE_GUID(IID_ID3D10EffectVectorVariable,0x62b98c44,0x1f82,0x4c67,0xbc,0xd0,0x72,0xcf,0x8f,0x21,0x7e,0x81);

.comdef ID3D10EffectVectorVariable : public ID3D10EffectVariable

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

DEFINE_GUID(IID_ID3D10EffectMatrixVariable,0x50666c24,0xb82f,0x4eed,0xa1,0x72,0x5b,0x6e,0x7e,0x85,0x22,0xe0)

.comdef ID3D10EffectMatrixVariable : public ID3D10EffectVariable

    SetMatrix			proc :ptr
    GetMatrix			proc :ptr
    SetMatrixArray		proc :ptr, :UINT, :UINT
    GetMatrixArray		proc :ptr, :UINT, :UINT
    SetMatrixTranspose		proc :ptr
    GetMatrixTranspose		proc :ptr
    SetMatrixTransposeArray	proc :ptr, :UINT, :UINT
    GetMatrixTransposeArray	proc :ptr, :UINT, :UINT
   .ends

DEFINE_GUID(IID_ID3D10EffectStringVariable,0x71417501,0x8df9,0x4e0a,0xa7,0x8a,0x25,0x5f,0x97,0x56,0xba,0xff)

.comdef ID3D10EffectStringVariable : public ID3D10EffectVariable

    GetString			proc :LPCSTR
    GetStringArray		proc :LPCSTR, :UINT, :UINT
   .ends

DEFINE_GUID(IID_ID3D10EffectShaderResourceVariable,0xc0a7157b,0xd872,0x4b1d,0x80,0x73,0xef,0xc2,0xac,0xd4,0xb1,0xfc)

.comdef ID3D10EffectShaderResourceVariable : public ID3D10EffectVariable

    SetResource			proc :ptr
    GetResource			proc :ptr
    SetResourceArray		proc :ptr, :UINT, :UINT
    GetResourceArray		proc :ptr, :UINT, :UINT
   .ends

DEFINE_GUID(IID_ID3D10EffectRenderTargetViewVariable,0x28ca0cc3,0xc2c9,0x40bb,0xb5,0x7f,0x67,0xb7,0x37,0x12,0x2b,0x17)

.comdef ID3D10EffectRenderTargetViewVariable : public ID3D10EffectVariable

    SetRenderTarget		proc :ptr
    GetRenderTarget		proc :ptr
    SetRenderTargetArray	proc :ptr, :UINT, :UINT
    GetRenderTargetArray	proc :ptr, :UINT, :UINT
   .ends

DEFINE_GUID(IID_ID3D10EffectDepthStencilViewVariable,0x3e02c918,0xcc79,0x4985,0xb6,0x22,0x2d,0x92,0xad,0x70,0x16,0x23)

.comdef ID3D10EffectDepthStencilViewVariable : public ID3D10EffectVariable

    SetDepthStencil		proc :ptr
    GetDepthStencil		proc :ptr
    SetDepthStencilArray	proc :ptr, :UINT, :UINT
    GetDepthStencilArray	proc :ptr, :UINT, :UINT
   .ends

DEFINE_GUID(IID_ID3D10EffectConstantBuffer,0x56648f4d,0xcc8b,0x4444,0xa5,0xad,0xb5,0xa3,0xd7,0x6e,0x91,0xb3)

.comdef ID3D10EffectConstantBuffer : public ID3D10EffectVariable

    SetConstantBuffer		proc :ptr
    GetConstantBuffer		proc :ptr
    SetTextureBuffer		proc :ptr
    GetTextureBuffer		proc :ptr
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

DEFINE_GUID(IID_ID3D10EffectShaderVariable,0x80849279,0xc799,0x4797,0x8c,0x33,0x4,0x7,0xa0,0x7d,0x9e,0x6)

.comdef ID3D10EffectShaderVariable : public ID3D10EffectVariable

    GetShaderDesc		proc :UINT, :ptr
    GetVertexShader		proc :UINT, :ptr
    GetGeometryShader		proc :UINT, :ptr
    GetPixelShader		proc :UINT, :ptr
    GetInputSignatureElementDesc proc :UINT, :UINT, :ptr
    GetOutputSignatureElementDesc proc :UINT, :UINT, :ptr
   .ends

DEFINE_GUID(IID_ID3D10EffectBlendVariable,0x1fcd2294,0xdf6d,0x4eae,0x86,0xb3,0xe,0x91,0x60,0xcf,0xb0,0x7b)

.comdef ID3D10EffectBlendVariable : public ID3D10EffectVariable

    GetBlendState		proc :UINT, :ptr
    GetBackingStore		proc :UINT, :ptr
   .ends

DEFINE_GUID(IID_ID3D10EffectDepthStencilVariable,0xaf482368,0x330a,0x46a5,0x9a,0x5c,0x1,0xc7,0x1a,0xf2,0x4c,0x8d)

.comdef ID3D10EffectDepthStencilVariable : public ID3D10EffectVariable

    GetDepthStencilState	proc :UINT, :ptr
    GetBackingStore		proc :UINT, :ptr
   .ends

DEFINE_GUID(IID_ID3D10EffectRasterizerVariable,0x21af9f0e,0x4d94,0x4ea9,0x97,0x85,0x2c,0xb7,0x6b,0x8c,0xb,0x34)

.comdef ID3D10EffectRasterizerVariable : public ID3D10EffectVariable

    GetRasterizerState		proc :UINT, :ptr
    GetBackingStore		proc :UINT, :ptr
   .ends

DEFINE_GUID(IID_ID3D10EffectSamplerVariable,0x6530d5c7,0x7e9,0x4271,0xa4,0x18,0xe7,0xce,0x4b,0xd1,0xe4,0x80)

.comdef ID3D10EffectSamplerVariable : public ID3D10EffectVariable

    GetSampler			proc :UINT, :ptr
    GetBackingStore		proc :UINT, :ptr
   .ends

LPID3D10EffectShaderVariable	typedef ptr ID3D10EffectShaderVariable

D3D10_PASS_DESC		STRUC
Name			LPCSTR ?
Annotations		UINT ?
pIAInputSignature	LPBYTE ?
IAInputSignatureSize	size_t ?
StencilRef		UINT ?
SampleMask		UINT ?
BlendFactor		FLOAT 4 dup(?)
D3D10_PASS_DESC		ENDS

D3D10_PASS_SHADER_DESC	STRUC
pShaderVariable		LPID3D10EffectShaderVariable ?
ShaderIndex		UINT ?
D3D10_PASS_SHADER_DESC	ENDS

DEFINE_GUID(IID_ID3D10EffectPass,0x5cfbeb89,0x1a06,0x46e0,0xb2,0x82,0xe3,0xf9,0xbf,0xa3,0x6a,0x54)

.comdef ID3D10EffectPass

    IsValid			proc
    GetDesc			proc :ptr
    GetVertexShaderDesc		proc :ptr
    GetGeometryShaderDesc	proc :ptr
    GetPixelShaderDesc		proc :ptr
    GetAnnotationByIndex	proc :UINT
    GetAnnotationByName		proc :LPCSTR
    Apply			proc :UINT
    ComputeStateBlockMask	proc :ptr
   .ends

D3D10_TECHNIQUE_DESC	STRUC
Name			LPCSTR ?
Passes			UINT ?
Annotations		UINT ?
D3D10_TECHNIQUE_DESC	ENDS

DEFINE_GUID(IID_ID3D10EffectTechnique,0xdb122ce8,0xd1c9,0x4292,0xb2,0x37,0x24,0xed,0x3d,0xe8,0xb1,0x75)

.comdef ID3D10EffectTechnique

    IsValid			proc
    GetDesc			proc :ptr
    GetAnnotationByIndex	proc :UINT
    GetAnnotationByName		proc :LPCSTR
    GetPassByIndex		proc :UINT
    GetPassByName		proc :LPCSTR
    ComputeStateBlockMask	proc :ptr
   .ends

D3D10_EFFECT_DESC	STRUC
IsChildEffect		BOOL ?
ConstantBuffers		UINT ?
SharedConstantBuffers	UINT ?
GlobalVariables		UINT ?
SharedGlobalVariables	UINT ?
Techniques		UINT ?
D3D10_EFFECT_DESC	ENDS

DEFINE_GUID(IID_ID3D10Effect,0x51b0ca8b,0xec0b,0x4519,0x87,0xd,0x8e,0xe1,0xcb,0x50,0x17,0xc7)

.comdef ID3D10Effect : public IUnknown

    IsValid			proc
    IsPool			proc
    GetDevice			proc :ptr
    GetDesc			proc :ptr
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

DEFINE_GUID(IID_ID3D10EffectPool,0x9537ab04,0x3250,0x412e,0x82,0x13,0xfc,0xd2,0xf8,0x67,0x79,0x33)

.comdef ID3D10EffectPool : public IUnknown

    AsEffect		proc
   .ends

D3D10CompileEffectFromMemory proto WINAPI :ptr, :size_t, :LPCSTR, :ptr, :ptr, :UINT, :UINT, :ptr, :ptr
D3D10CreateEffectFromMemory proto WINAPI :ptr, :size_t, :UINT, :ptr, :ptr, :ptr
D3D10CreateEffectPoolFromMemory proto WINAPI :ptr, :size_t, :UINT, :ptr, :ptr
D3D10DisassembleEffect proto WINAPI :ptr, :BOOL, :ptr

endif
