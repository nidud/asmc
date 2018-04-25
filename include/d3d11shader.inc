ifndef __D3D11SHADER_H__
__D3D11SHADER_H__ equ <>
.pragma list(push, 0)

include d3dcommon.inc

D3D11_CBUFFER_TYPE	typedef D3D_CBUFFER_TYPE
D3D11_RESOURCE_RETURN_TYPE typedef D3D_RESOURCE_RETURN_TYPE
D3D11_TESSELLATOR_DOMAIN typedef D3D_TESSELLATOR_DOMAIN
D3D11_TESSELLATOR_PARTITIONING typedef D3D_TESSELLATOR_PARTITIONING
D3D11_TESSELLATOR_OUTPUT_PRIMITIVE typedef D3D_TESSELLATOR_OUTPUT_PRIMITIVE

D3D11_SHADER_DESC	STRUC
Version			UINT ?
Creator			LPSTR ?
Flags			UINT ?
ConstantBuffers		UINT ?
BoundResources		UINT ?
InputParameters		UINT ?
OutputParameters	UINT ?
InstructionCount	UINT ?
TempRegisterCount	UINT ?
TempArrayCount		UINT ?
DefCount		UINT ?
DclCount		UINT ?
TextureNormalInstructions UINT ?
TextureLoadInstructions UINT ?
TextureCompInstructions UINT ?
TextureBiasInstructions UINT ?
TextureGradientInstructions UINT ?
FloatInstructionCount	UINT ?
IntInstructionCount	UINT ?
UintInstructionCount	UINT ?
StaticFlowControlCount	UINT ?
DynamicFlowControlCount UINT ?
MacroInstructionCount	UINT ?
ArrayInstructionCount	UINT ?
CutInstructionCount	UINT ?
EmitInstructionCount	UINT ?
GSOutputTopology	D3D_PRIMITIVE_TOPOLOGY ?
GSMaxOutputVertexCount	UINT ?
InputPrimitive		D3D_PRIMITIVE ?
PatchConstantParameters UINT ?
cGSInstanceCount	UINT ?
cControlPoints		UINT ?
HSOutputPrimitive	D3D_TESSELLATOR_OUTPUT_PRIMITIVE ?
HSPartitioning		D3D_TESSELLATOR_PARTITIONING ?
TessellatorDomain	D3D_TESSELLATOR_DOMAIN ?
cBarrierInstructions	UINT ?
cInterlockedInstructions UINT ?
cTextureStoreInstructions UINT ?
D3D11_SHADER_DESC	ENDS

D3D11_SHADER_VARIABLE_DESC STRUC
_Name			LPSTR ?
StartOffset		UINT ?
_Size			UINT ?
uFlags			UINT ?
DefaultValue		PVOID ?
StartTexture		UINT ?
TextureSize		UINT ?
StartSampler		UINT ?
SamplerSize		UINT ?
D3D11_SHADER_VARIABLE_DESC ENDS

D3D11_SHADER_TYPE_DESC	STRUC
Class			D3D_SHADER_VARIABLE_CLASS ?
_Type			D3D_SHADER_VARIABLE_TYPE ?
Rows			UINT ?
Columns			UINT ?
Elements		UINT ?
Members			UINT ?
_Offset			UINT ?
_Name			LPSTR ?
D3D11_SHADER_TYPE_DESC	ENDS

D3D11_SHADER_BUFFER_DESC STRUC
_Name			LPSTR ?
_Type			D3D_CBUFFER_TYPE ?
Variables		UINT ?
_Size			UINT ?
uFlags			UINT ?
D3D11_SHADER_BUFFER_DESC ENDS

D3D11_SHADER_INPUT_BIND_DESC STRUC
_Name			LPSTR ?
_Type			D3D_SHADER_INPUT_TYPE ?
BindPoint		UINT ?
BindCount		UINT ?
uFlags			UINT ?
ReturnType		D3D_RESOURCE_RETURN_TYPE ?
Dimension		D3D_SRV_DIMENSION ?
NumSamples		UINT ?
D3D11_SHADER_INPUT_BIND_DESC ENDS

D3D11_SIGNATURE_PARAMETER_DESC STRUC
SemanticName		LPSTR ?
SemanticIndex		UINT ?
Register		UINT ?
SystemValueType		D3D_NAME ?
ComponentType		D3D_REGISTER_COMPONENT_TYPE ?
_Mask			db ?
ReadWriteMask		db ?
Stream			UINT ?
D3D11_SIGNATURE_PARAMETER_DESC ENDS

DEFINE_GUID(IID_ID3D11ShaderReflectionType, 0x6e6ffa6a, 0x9bae, 0x4613, 0xa5, 0x1e, 0x91, 0x65, 0x2d, 0x50, 0x8c, 0x21);

.comdef ID3D11ShaderReflectionType
    GetDesc		proc :ptr
    GetMemberTypeByIndex proc :UINT
    GetMemberTypeByName proc :LPSTR
    GetMemberTypeName	proc :UINT
    IsEqual		proc :ptr
    GetSubType		proc
    GetBaseClass	proc
    GetNumInterfaces	proc
    GetInterfaceByIndex proc :UINT
    IsOfType		proc :ptr
    ImplementsInterface proc :ptr
    .ends

DEFINE_GUID(IID_ID3D11ShaderReflectionVariable, 0x51f23923, 0xf3e5, 0x4bd1, 0x91, 0xcb, 0x60, 0x61, 0x77, 0xd8, 0xdb, 0x4c);

.comdef ID3D11ShaderReflectionVariable
    GetDesc		proc :ptr
    GetType		proc
    GetBuffer		proc
    GetInterfaceSlot	proc :UINT
    .ends

DEFINE_GUID(IID_ID3D11ShaderReflectionConstantBuffer, 0xeb62d63d, 0x93dd, 0x4318, 0x8a, 0xe8, 0xc6, 0xf8, 0x3a, 0xd3, 0x71, 0xb8);

.comdef ID3D11ShaderReflectionConstantBuffer
    GetDesc		proc :ptr
    GetVariableByIndex	proc :UINT
    GetVariableByName	proc :LPSTR
    .ends

DEFINE_GUID(IID_ID3D11ShaderReflection, 0x0a233719, 0x3960, 0x4578, 0x9d, 0x7c, 0x20, 0x3b, 0x8b, 0x1d, 0x9c, 0xc1);

.comdef ID3D11ShaderReflection
    QueryInterface	proc :REFIID, :ptr PVOID
    AddRef		proc
    Release		proc
    GetDesc		proc :ptr
    GetConstantBufferByIndex proc :UINT
    GetConstantBufferByName proc :LPSTR
    GetResourceBindingDesc proc :UINT, :ptr
    GetInputParameterDesc proc :UINT, :ptr
    GetOutputParameterDesc proc :UINT, :ptr
    GetPatchConstantParameterDesc proc :UINT, :ptr
    GetVariableByName	proc :LPSTR
    GetResourceBindingDescByName proc :LPSTR, :ptr
    GetMovInstructionCount proc
    GetMovcInstructionCount proc
    GetConversionInstructionCount proc
    GetBitwiseInstructionCount proc
    GetGSInputPrimitive proc
    IsSampleFrequencyShader proc
    GetNumInterfaceSlots proc
    GetMinFeatureLevel	proc :ptr
    GetThreadGroupSize	proc :ptr, :ptr, :ptr
    .ends

.pragma list(pop)
endif
