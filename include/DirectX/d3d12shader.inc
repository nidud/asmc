ifndef __D3D12SHADER_H__
define __D3D12SHADER_H__

include d3dcommon.inc

.enum D3D12_SHADER_VERSION_TYPE {
    D3D12_SHVER_PIXEL_SHADER	= 0,
    D3D12_SHVER_VERTEX_SHADER	= 1,
    D3D12_SHVER_GEOMETRY_SHADER = 2,
    D3D12_SHVER_HULL_SHADER	= 3,
    D3D12_SHVER_DOMAIN_SHADER	= 4,
    D3D12_SHVER_COMPUTE_SHADER	= 5,
    D3D12_SHVER_RESERVED0	= 0xFFF0,
    }

D3D12_SHVER_GET_TYPE macro _Version
	exitm<(((_Version) shr 16) and 0xffff)>
	endm

D3D12_SHVER_GET_MAJOR macro _Version
	exitm<(((_Version) shr 4) and 0xf)>
	endm

D3D12_SHVER_GET_MINOR macro _Version
	exitm<(((_Version) shr 0) and 0xf)>
	endm


D3D_RETURN_PARAMETER_INDEX equ (-1)
D3D12_RESOURCE_RETURN_TYPE typedef D3D_RESOURCE_RETURN_TYPE
D3D12_CBUFFER_TYPE	typedef D3D_CBUFFER_TYPE


D3D12_SIGNATURE_PARAMETER_DESC STRUC
SemanticName		LPCSTR ?
SemanticIndex		UINT ?
Register		UINT ?
SystemValueType		D3D_NAME ?
ComponentType		D3D_REGISTER_COMPONENT_TYPE ?
Mask			db ?
ReadWriteMask		db ?
Stream			UINT ?
MinPrecision		D3D_MIN_PRECISION ?
D3D12_SIGNATURE_PARAMETER_DESC ENDS

D3D12_SHADER_BUFFER_DESC STRUC
Name			LPCSTR ?
Type			D3D_CBUFFER_TYPE ?
Variables		UINT ?
Size			UINT ?
uFlags			UINT ?
D3D12_SHADER_BUFFER_DESC ENDS

D3D12_SHADER_VARIABLE_DESC STRUC
Name			LPCSTR ?
StartOffset		UINT ?
Size			UINT ?
uFlags			UINT ?
DefaultValue		LPVOID ?
StartTexture		UINT ?
TextureSize		UINT ?
StartSampler		UINT ?
SamplerSize		UINT ?
D3D12_SHADER_VARIABLE_DESC ENDS

D3D12_SHADER_TYPE_DESC	STRUC
Class			D3D_SHADER_VARIABLE_CLASS ?
Type			D3D_SHADER_VARIABLE_TYPE ?
Rows			UINT ?
Columns			UINT ?
Elements		UINT ?
Members			UINT ?
Offs			UINT ?
Name			LPCSTR ?
D3D12_SHADER_TYPE_DESC	ENDS

D3D12_TESSELLATOR_DOMAIN typedef D3D_TESSELLATOR_DOMAIN

D3D12_TESSELLATOR_PARTITIONING typedef D3D_TESSELLATOR_PARTITIONING

D3D12_TESSELLATOR_OUTPUT_PRIMITIVE typedef D3D_TESSELLATOR_OUTPUT_PRIMITIVE

D3D12_SHADER_DESC	STRUC
Version			UINT ?
Creator			LPCSTR ?
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
D3D12_SHADER_DESC	ENDS

D3D12_SHADER_INPUT_BIND_DESC STRUC
Name			LPCSTR ?
Type			D3D_SHADER_INPUT_TYPE ?
BindPoint		UINT ?
BindCount		UINT ?

uFlags			UINT ?
ReturnType		D3D_RESOURCE_RETURN_TYPE ?
Dimension		D3D_SRV_DIMENSION ?
NumSamples		UINT ?
Space			UINT ?
uID			UINT ?
D3D12_SHADER_INPUT_BIND_DESC ENDS

D3D_SHADER_REQUIRES_DOUBLES equ 0x00000001
D3D_SHADER_REQUIRES_EARLY_DEPTH_STENCIL equ 0x00000002
D3D_SHADER_REQUIRES_UAVS_AT_EVERY_STAGE equ 0x00000004
D3D_SHADER_REQUIRES_64_UAVS equ 0x00000008
D3D_SHADER_REQUIRES_MINIMUM_PRECISION equ 0x00000010
D3D_SHADER_REQUIRES_11_1_DOUBLE_EXTENSIONS equ 0x00000020
D3D_SHADER_REQUIRES_11_1_SHADER_EXTENSIONS equ 0x00000040
D3D_SHADER_REQUIRES_LEVEL_9_COMPARISON_FILTERING equ 0x00000080
D3D_SHADER_REQUIRES_TILED_RESOURCES equ 0x00000100
D3D_SHADER_REQUIRES_STENCIL_REF equ 0x00000200
D3D_SHADER_REQUIRES_INNER_COVERAGE equ 0x00000400
D3D_SHADER_REQUIRES_TYPED_UAV_LOAD_ADDITIONAL_FORMATS equ 0x00000800
D3D_SHADER_REQUIRES_ROVS equ 0x00001000
D3D_SHADER_REQUIRES_VIEWPORT_AND_RT_ARRAY_INDEX_FROM_ANY_SHADER_FEEDING_RASTERIZER equ 0x00002000


D3D12_LIBRARY_DESC	STRUC
Creator			LPCSTR ?
Flags			UINT ?
FunctionCount		UINT ?
D3D12_LIBRARY_DESC	ENDS

D3D12_FUNCTION_DESC	STRUC
Version			UINT ?
Creator			LPCSTR ?
Flags			UINT ?

ConstantBuffers		UINT ?
BoundResources		UINT ?

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
MovInstructionCount	UINT ?
MovcInstructionCount	UINT ?
ConversionInstructionCount UINT ?
BitwiseInstructionCount UINT ?
MinFeatureLevel		D3D_FEATURE_LEVEL ?
RequiredFeatureFlags	UINT64 ?

Name			LPCSTR ?
FunctionParameterCount	int_t ?
HasReturn		BOOL ?
Has10Level9VertexShader BOOL ?
Has10Level9PixelShader	BOOL ?
D3D12_FUNCTION_DESC	ENDS

D3D12_PARAMETER_DESC	STRUC
Name			LPCSTR ?
SemanticName		LPCSTR ?
Type			D3D_SHADER_VARIABLE_TYPE ?
Class			D3D_SHADER_VARIABLE_CLASS ?
Rows			UINT ?
Columns			UINT ?
InterpolationMode	D3D_INTERPOLATION_MODE ?
Flags			D3D_PARAMETER_FLAGS ?

FirstInRegister		UINT ?
FirstInComponent	UINT ?
FirstOutRegister	UINT ?
FirstOutComponent	UINT ?
D3D12_PARAMETER_DESC	ENDS


.comdef ID3D12ShaderReflectionType

    GetDesc		proc :ptr D3D12_SHADER_TYPE_DESC
    GetMemberTypeByIndex proc :UINT
    GetMemberTypeByName proc :LPCSTR
    GetMemberTypeName	proc :UINT
    IsEqual		proc :ptr ID3D12ShaderReflectionType
    GetSubType		proc
    GetBaseClass	proc
    GetNumInterfaces	proc
    GetInterfaceByIndex proc :UINT
    IsOfType		proc :ptr ID3D12ShaderReflectionType
    ImplementsInterface proc :ptr ID3D12ShaderReflectionType
    .ends


.comdef ID3D12ShaderReflectionVariable

    GetDesc		proc :ptr D3D12_SHADER_VARIABLE_DESC
    GetType		proc
    GetBuffer		proc
    GetInterfaceSlot	proc :UINT
    .ends


.comdef ID3D12ShaderReflectionConstantBuffer

    GetDesc		proc :ptr D3D12_SHADER_BUFFER_DESC
    GetVariableByIndex	proc :UINT
    GetVariableByName	proc :LPCSTR
    .ends


.comdef ID3D12ShaderReflection : public IUnknown

    GetDesc		proc :ptr D3D12_PARAMETER_DESC
    GetConstantBufferByIndex proc :UINT
    GetConstantBufferByName proc :LPCSTR
    GetResourceBindingDesc proc :UINT, :ptr D3D12_SHADER_INPUT_BIND_DESC
    GetInputParameterDesc proc :UINT, :ptr D3D12_SIGNATURE_PARAMETER_DESC
    GetOutputParameterDesc proc :UINT, :ptr D3D12_SIGNATURE_PARAMETER_DESC
    GetPatchConstantParameterDesc proc :UINT, :ptr D3D12_SIGNATURE_PARAMETER_DESC
    GetVariableByName	proc :LPCSTR
    GetResourceBindingDescByName proc :LPCSTR, :ptr D3D12_SHADER_INPUT_BIND_DESC
    GetMovInstructionCount proc
    GetMovcInstructionCount proc
    GetConversionInstructionCount proc
    GetBitwiseInstructionCount proc
    GetGSInputPrimitive proc
    IsSampleFrequencyShader proc
    GetNumInterfaceSlots proc
    GetMinFeatureLevel	proc :ptr D3D_FEATURE_LEVEL
    GetThreadGroupSize	proc :ptr UINT, :ptr UINT, :ptr UINT
    GetRequiresFlags	proc
    .ends


.comdef ID3D12LibraryReflection : public IUnknown

    GetDesc		proc :ptr D3D12_PARAMETER_DESC
    GetFunctionByIndex	proc :SINT
    .ends


.comdef ID3D12FunctionReflection

    GetDesc		proc :ptr D3D12_PARAMETER_DESC
    GetConstantBufferByIndex proc :UINT
    GetConstantBufferByName proc :LPCSTR
    GetResourceBindingDesc proc :UINT, :ptr D3D12_SHADER_INPUT_BIND_DESC
    GetVariableByName	proc :LPCSTR
    GetResourceBindingDescByName proc :LPCSTR, :ptr D3D12_SHADER_INPUT_BIND_DESC
    GetFunctionParameter proc :SINT
    .ends


.comdef ID3D12FunctionParameterReflection

    GetDesc		proc :ptr D3D12_PARAMETER_DESC
    .ends

endif
