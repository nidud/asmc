ifndef __D3D10SHADER_H__
define __D3D10SHADER_H__

include d3d10.inc

D3D10_TX_VERSION macro _Major,_Minor
	exitm<(('T' SHL 24) OR ('X' SHL 16) OR ((_Major) SHL 8) OR (_Minor))>
	endm

D3D10_SHADER_DEBUG	equ (1 SHL 0)
D3D10_SHADER_SKIP_VALIDATION equ (1 SHL 1)
D3D10_SHADER_SKIP_OPTIMIZATION equ (1 SHL 2)
D3D10_SHADER_PACK_MATRIX_ROW_MAJOR equ (1 SHL 3)
D3D10_SHADER_PACK_MATRIX_COLUMN_MAJOR equ (1 SHL 4)
D3D10_SHADER_PARTIAL_PRECISION equ (1 SHL 5)
D3D10_SHADER_FORCE_VS_SOFTWARE_NO_OPT equ (1 SHL 6)
D3D10_SHADER_FORCE_PS_SOFTWARE_NO_OPT equ (1 SHL 7)
D3D10_SHADER_NO_PRESHADER equ (1 SHL 8)
D3D10_SHADER_AVOID_FLOW_CONTROL equ (1 SHL 9)
D3D10_SHADER_PREFER_FLOW_CONTROL equ (1 SHL 10)
D3D10_SHADER_ENABLE_STRICTNESS equ (1 SHL 11)
D3D10_SHADER_ENABLE_BACKWARDS_COMPATIBILITY equ (1 SHL 12)
D3D10_SHADER_IEEE_STRICTNESS equ (1 SHL 13)
D3D10_SHADER_WARNINGS_ARE_ERRORS equ (1 SHL 18)

D3D10_SHADER_OPTIMIZATION_LEVEL0 equ (1 SHL 14)
D3D10_SHADER_OPTIMIZATION_LEVEL1 equ 0
D3D10_SHADER_OPTIMIZATION_LEVEL2 equ ((1 SHL 14) OR (1 SHL 15))
D3D10_SHADER_OPTIMIZATION_LEVEL3 equ (1 SHL 15)

D3D10_SHADER_MACRO	STRUC
Name			LPCSTR ?
Definition		LPCSTR ?
D3D10_SHADER_MACRO	ENDS
LPD3D10_SHADER_MACRO	typedef ptr D3D10_SHADER_MACRO

D3D10_SHADER_VARIABLE_CLASS typedef SDWORD
D3D10_SVC_SCALAR	equ 0
D3D10_SVC_VECTOR	equ 1
D3D10_SVC_MATRIX_ROWS	equ 2
D3D10_SVC_MATRIX_COLUMNS equ 3
D3D10_SVC_OBJECT	equ 4
D3D10_SVC_STRUCT	equ 5
D3D11_SVC_INTERFACE_CLASS equ 6
D3D11_SVC_INTERFACE_POINTER equ 7
D3D10_SVC_FORCE_DWORD	equ 0x7fffffff

D3D10_SHADER_VARIABLE_FLAGS typedef SDWORD
D3D10_SVF_USERPACKED	equ 1
D3D10_SVF_USED		equ 2
D3D11_SVF_INTERFACE_POINTER equ 4
D3D10_SVF_FORCE_DWORD	equ 0x7fffffff

D3D10_SHADER_VARIABLE_TYPE typedef SDWORD
D3D10_SVT_VOID		equ 0
D3D10_SVT_BOOL		equ 1
D3D10_SVT_INT		equ 2
D3D10_SVT_FLOAT		equ 3
D3D10_SVT_STRING	equ 4
D3D10_SVT_TEXTURE	equ 5
D3D10_SVT_TEXTURE1D	equ 6
D3D10_SVT_TEXTURE2D	equ 7
D3D10_SVT_TEXTURE3D	equ 8
D3D10_SVT_TEXTURECUBE	equ 9
D3D10_SVT_SAMPLER	equ 10
D3D10_SVT_PIXELSHADER	equ 15
D3D10_SVT_VERTEXSHADER	equ 16
D3D10_SVT_UINT		equ 19
D3D10_SVT_UINT8		equ 20
D3D10_SVT_GEOMETRYSHADER equ 21
D3D10_SVT_RASTERIZER	equ 22
D3D10_SVT_DEPTHSTENCIL	equ 23
D3D10_SVT_BLEND		equ 24
D3D10_SVT_BUFFER	equ 25
D3D10_SVT_CBUFFER	equ 26
D3D10_SVT_TBUFFER	equ 27
D3D10_SVT_TEXTURE1DARRAY equ 28
D3D10_SVT_TEXTURE2DARRAY equ 29
D3D10_SVT_RENDERTARGETVIEW equ 30
D3D10_SVT_DEPTHSTENCILVIEW equ 31
D3D10_SVT_TEXTURE2DMS	equ 32
D3D10_SVT_TEXTURE2DMSARRAY equ 33
D3D10_SVT_TEXTURECUBEARRAY equ 34
D3D11_SVT_HULLSHADER	equ 35
D3D11_SVT_DOMAINSHADER	equ 36
D3D11_SVT_INTERFACE_POINTER equ 37
D3D11_SVT_COMPUTESHADER equ 38
D3D11_SVT_DOUBLE	equ 39
D3D10_SVT_FORCE_DWORD	equ 0x7fffffff

D3D10_SHADER_INPUT_FLAGS typedef SDWORD
D3D10_SIF_USERPACKED	equ 1
D3D10_SIF_COMPARISON_SAMPLER equ 2
D3D10_SIF_TEXTURE_COMPONENT_0 equ 4
D3D10_SIF_TEXTURE_COMPONENT_1 equ 8
D3D10_SIF_TEXTURE_COMPONENTS equ 12
D3D10_SIF_FORCE_DWORD	equ 0x7fffffff

D3D10_SHADER_INPUT_TYPE typedef SDWORD
D3D10_SIT_CBUFFER	equ 0
D3D10_SIT_TBUFFER	equ 1
D3D10_SIT_TEXTURE	equ 2
D3D10_SIT_SAMPLER	equ 3
D3D11_SIT_UAV_RWTYPED	equ 4
D3D11_SIT_STRUCTURED	equ 5
D3D11_SIT_UAV_RWSTRUCTURED equ 6
D3D11_SIT_BYTEADDRESS	equ 7
D3D11_SIT_UAV_RWBYTEADDRESS equ 8
D3D11_SIT_UAV_APPEND_STRUCTURED equ 9
D3D11_SIT_UAV_CONSUME_STRUCTURED equ 10
D3D11_SIT_UAV_RWSTRUCTURED_WITH_COUNTER equ 11

D3D10_SHADER_CBUFFER_FLAGS typedef SDWORD
D3D10_CBF_USERPACKED	equ 1
D3D10_CBF_FORCE_DWORD	equ 0x7fffffff

D3D10_CBUFFER_TYPE	typedef SDWORD
D3D10_CT_CBUFFER	equ 0
D3D10_CT_TBUFFER	equ 1

D3D10_NAME		typedef SDWORD
D3D10_NAME_UNDEFINED	equ 0
D3D10_NAME_POSITION	equ 1
D3D10_NAME_CLIP_DISTANCE equ 2
D3D10_NAME_CULL_DISTANCE equ 3
D3D10_NAME_RENDER_TARGET_ARRAY_INDEX equ 4
D3D10_NAME_VIEWPORT_ARRAY_INDEX equ 5
D3D10_NAME_VERTEX_ID	equ 6
D3D10_NAME_PRIMITIVE_ID equ 7
D3D10_NAME_INSTANCE_ID	equ 8
D3D10_NAME_IS_FRONT_FACE equ 9
D3D10_NAME_SAMPLE_INDEX equ 10
D3D11_NAME_FINAL_QUAD_EDGE_TESSFACTOR equ 11
D3D11_NAME_FINAL_QUAD_INSIDE_TESSFACTOR equ 12
D3D11_NAME_FINAL_TRI_EDGE_TESSFACTOR equ 13
D3D11_NAME_FINAL_TRI_INSIDE_TESSFACTOR equ 14
D3D11_NAME_FINAL_LINE_DETAIL_TESSFACTOR equ 15
D3D11_NAME_FINAL_LINE_DENSITY_TESSFACTOR equ 16
D3D10_NAME_TARGET	equ 64
D3D10_NAME_DEPTH	equ 65
D3D10_NAME_COVERAGE	equ 66
D3D11_NAME_DEPTH_GREATER_EQUAL equ 67
D3D11_NAME_DEPTH_LESS_EQUAL equ 68

D3D10_RESOURCE_RETURN_TYPE typedef SDWORD
D3D10_RETURN_TYPE_UNORM equ 1
D3D10_RETURN_TYPE_SNORM equ 2
D3D10_RETURN_TYPE_SINT	equ 3
D3D10_RETURN_TYPE_UINT	equ 4
D3D10_RETURN_TYPE_FLOAT equ 5
D3D10_RETURN_TYPE_MIXED equ 6

D3D10_REGISTER_COMPONENT_TYPE typedef SDWORD
D3D10_REGISTER_COMPONENT_UNKNOWN equ 0
D3D10_REGISTER_COMPONENT_UINT32 equ 1
D3D10_REGISTER_COMPONENT_SINT32 equ 2
D3D10_REGISTER_COMPONENT_FLOAT32 equ 3

D3D10_INCLUDE_TYPE	typedef SDWORD
D3D10_INCLUDE_LOCAL	equ 0
D3D10_INCLUDE_SYSTEM	equ 1
D3D10_INCLUDE_FORCE_DWORD equ 0x7fffffff

.comdef ID3D10Include

    Open	proc :D3D10_INCLUDE_TYPE, :LPCSTR, :ptr, :ptr, :LPUINT
    Close	proc :ptr
   .ends

D3D10_SHADER_DESC	STRUC
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
GSOutputTopology	D3D10_PRIMITIVE_TOPOLOGY ?
GSMaxOutputVertexCount	UINT ?
D3D10_SHADER_DESC	ENDS

D3D10_SHADER_BUFFER_DESC STRUC
Name			LPCSTR ?
Type			D3D10_CBUFFER_TYPE ?
Variables		UINT ?
Size			UINT ?
uFlags			UINT ?
D3D10_SHADER_BUFFER_DESC ENDS

D3D10_SHADER_VARIABLE_DESC STRUC
Name			LPCSTR ?
StartOffset		UINT ?
Size			UINT ?
uFlags			UINT ?
DefaultValue		LPVOID ?
D3D10_SHADER_VARIABLE_DESC ENDS

D3D10_SHADER_TYPE_DESC	STRUC
Class			D3D10_SHADER_VARIABLE_CLASS ?
Type			D3D10_SHADER_VARIABLE_TYPE ?
Rows			UINT ?
Columns			UINT ?
Elements		UINT ?
Members			UINT ?
_Offset			UINT ?
D3D10_SHADER_TYPE_DESC	ENDS

D3D10_SHADER_INPUT_BIND_DESC STRUC
Name			LPCSTR ?
Type			D3D10_SHADER_INPUT_TYPE ?
BindPoint		UINT ?
BindCount		UINT ?
uFlags			UINT ?
ReturnType		D3D10_RESOURCE_RETURN_TYPE ?
Dimension		D3D10_SRV_DIMENSION ?
NumSamples		UINT ?
D3D10_SHADER_INPUT_BIND_DESC ENDS

D3D10_SIGNATURE_PARAMETER_DESC STRUC
SemanticName		LPCSTR ?
SemanticIndex		UINT ?
Register		UINT ?
SystemValueType		D3D10_NAME ?
ComponentType		D3D10_REGISTER_COMPONENT_TYPE ?
Mask			db ?
ReadWriteMask		db ?
D3D10_SIGNATURE_PARAMETER_DESC ENDS

DEFINE_GUID(IID_ID3D10ShaderReflectionType, 0xc530ad7d, 0x9b16, 0x4395, 0xa9, 0x79, 0xba, 0x2e, 0xcf, 0xf8, 0x3a, 0xdd)

.comdef ID3D10ShaderReflectionType

    GetDesc		proc :D3D10_SHADER_TYPE_DESC
    GetMemberTypeByIndex proc :UINT
    GetMemberTypeByName proc :LPCSTR
    GetMemberTypeName	proc :UINT
   .ends

DEFINE_GUID(IID_ID3D10ShaderReflectionVariable, 0x1bf63c95, 0x2650, 0x405d, 0x99, 0xc1, 0x36, 0x36, 0xbd, 0x1d, 0xa0, 0xa1);

.comdef ID3D10ShaderReflectionVariable

    GetDesc		proc :ptr
    GetType		proc
   .ends

DEFINE_GUID(IID_ID3D10ShaderReflectionConstantBuffer,0x66c66a94, 0xdddd, 0x4b62, 0xa6, 0x6a, 0xf0, 0xda, 0x33, 0xc2, 0xb4, 0xd0);

.comdef ID3D10ShaderReflectionConstantBuffer

    GetDesc		proc :ptr
    GetVariableByIndex	proc :UINT
    GetVariableByName	proc :LPCSTR
   .ends

DEFINE_GUID(IID_ID3D10ShaderReflection,0xd40e20b6, 0xf8f7, 0x42ad, 0xab, 0x20, 0x4b, 0xaf, 0x8f, 0x15, 0xdf, 0xaa);

.comdef ID3D10ShaderReflection : public IUnknown

    GetDesc		proc :ptr
    GetConstantBufferByIndex proc :UINT
    GetConstantBufferByName proc :LPCSTR
    GetResourceBindingDesc proc :UINT, :ptr
    GetInputParameterDesc proc :UINT, :ptr
    GetOutputParameterDesc proc :UINT, :ptr
   .ends

D3D10CompileShader proto WINAPI :LPCSTR, :size_t, :LPCSTR, :ptr, :ptr, :LPCSTR, :LPCSTR, :UINT, :ptr, :ptr
D3D10DisassembleShader proto WINAPI :ptr, :size_t, :BOOL, :LPCSTR, :ptr
D3D10GetPixelShaderProfile proto WINAPI :ptr
D3D10GetVertexShaderProfile proto WINAPI :ptr
D3D10GetGeometryShaderProfile proto WINAPI :ptr
D3D10ReflectShader proto WINAPI :ptr, :size_t, :ptr
D3D10PreprocessShader proto WINAPI :LPCSTR, :size_t, :LPCSTR, :ptr, :ptr, :ptr, :ptr
D3D10GetInputSignatureBlob proto WINAPI :ptr, :size_t, :ptr
D3D10GetOutputSignatureBlob proto WINAPI :ptr, :size_t, :ptr
D3D10GetInputAndOutputSignatureBlob proto WINAPI :ptr, :size_t, :ptr
D3D10GetShaderDebugInfo proto WINAPI :ptr, :size_t, :ptr

endif
