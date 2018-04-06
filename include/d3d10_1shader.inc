ifndef __D3D10_1SHADER_H__
__D3D10_1SHADER_H__ equ 1
include d3d10shader.inc
.xlist

D3D10_SHADER_DEBUG_REGTYPE typedef SDWORD
D3D10_SHADER_DEBUG_REG_INPUT equ 0
D3D10_SHADER_DEBUG_REG_OUTPUT equ 1
D3D10_SHADER_DEBUG_REG_CBUFFER equ 2
D3D10_SHADER_DEBUG_REG_TBUFFER equ 3
D3D10_SHADER_DEBUG_REG_TEMP equ 4
D3D10_SHADER_DEBUG_REG_TEMPARRAY equ 5
D3D10_SHADER_DEBUG_REG_TEXTURE equ 6
D3D10_SHADER_DEBUG_REG_SAMPLER equ 7
D3D10_SHADER_DEBUG_REG_IMMEDIATECBUFFER equ 8
D3D10_SHADER_DEBUG_REG_LITERAL equ 9
D3D10_SHADER_DEBUG_REG_UNUSED equ 10
D3D11_SHADER_DEBUG_REG_INTERFACE_POINTERS equ 11
D3D10_SHADER_DEBUG_REG_FORCE_DWORD equ 0x7fffffff

D3D10_SHADER_DEBUG_SCOPETYPE typedef SDWORD
D3D10_SHADER_DEBUG_SCOPE_GLOBAL equ 0
D3D10_SHADER_DEBUG_SCOPE_BLOCK equ 1
D3D10_SHADER_DEBUG_SCOPE_FORLOOP equ 2
D3D10_SHADER_DEBUG_SCOPE_STRUCT equ 3
D3D10_SHADER_DEBUG_SCOPE_FUNC_PARAMS equ 4
D3D10_SHADER_DEBUG_SCOPE_STATEBLOCK equ 5
D3D10_SHADER_DEBUG_SCOPE_NAMESPACE equ 6
D3D10_SHADER_DEBUG_SCOPE_ANNOTATION equ 7
D3D10_SHADER_DEBUG_SCOPE_FORCE_DWORD equ 0x7fffffff

D3D10_SHADER_DEBUG_VARTYPE typedef SDWORD
D3D10_SHADER_DEBUG_VAR_VARIABLE equ 0
D3D10_SHADER_DEBUG_VAR_FUNCTION equ 1
D3D10_SHADER_DEBUG_VAR_FORCE_DWORD equ 0x7fffffff

D3D10_SHADER_DEBUG_TOKEN_INFO STRUC
File			UINT ?
Line			UINT ?
Column			UINT ?
TokenLength		UINT ?
TokenId			UINT ?
D3D10_SHADER_DEBUG_TOKEN_INFO ENDS

D3D10_SHADER_DEBUG_VAR_INFO STRUC
TokenId			UINT ?
_Type			D3D10_SHADER_VARIABLE_TYPE ?
Register		UINT ?
Component		UINT ?
ScopeVar		UINT ?
ScopeVarOffset		UINT ?
D3D10_SHADER_DEBUG_VAR_INFO ENDS

D3D10_SHADER_DEBUG_INPUT_INFO STRUC
Var			UINT ?
InitialRegisterSet	D3D10_SHADER_DEBUG_REGTYPE ?
InitialBank		UINT ?
InitialRegister		UINT ?
InitialComponent	UINT ?
InitialValue		UINT ?
D3D10_SHADER_DEBUG_INPUT_INFO ENDS

D3D10_SHADER_DEBUG_SCOPEVAR_INFO STRUC
TokenId			UINT ?
VarType			D3D10_SHADER_DEBUG_VARTYPE ?
Class			D3D10_SHADER_VARIABLE_CLASS ?
Rows			UINT ?
Columns			UINT ?
StructMemberScope	UINT ?
uArrayIndices		UINT ?
ArrayElements		UINT ?
ArrayStrides		UINT ?
uVariables		UINT ?
uFirstVariable		UINT ?
D3D10_SHADER_DEBUG_SCOPEVAR_INFO ENDS

D3D10_SHADER_DEBUG_SCOPE_INFO STRUC
ScopeType		D3D10_SHADER_DEBUG_SCOPETYPE ?
_Name			UINT ?
uNameLen		UINT ?
uVariables		UINT ?
VariableData		UINT ?
D3D10_SHADER_DEBUG_SCOPE_INFO ENDS

D3D10_SHADER_DEBUG_OUTPUTVAR STRUC
Var			UINT ?
uValueMin		UINT ?
uValueMax		UINT ?
iValueMin		SINT ?
iValueMax		SINT ?
fValueMin		FLOAT ?
fValueMax		FLOAT ?
bNaNPossible		BOOL ?
bInfPossible		BOOL ?
D3D10_SHADER_DEBUG_OUTPUTVAR ENDS

D3D10_SHADER_DEBUG_OUTPUTREG_INFO STRUC
OutputRegisterSet	D3D10_SHADER_DEBUG_REGTYPE ?
OutputReg		UINT ?
TempArrayReg		UINT ?
OutputComponents	UINT 4 dup(?)
OutputVars		D3D10_SHADER_DEBUG_OUTPUTVAR 4 dup(<>)
IndexReg		UINT ?
IndexComp		UINT ?
D3D10_SHADER_DEBUG_OUTPUTREG_INFO ENDS

D3D10_SHADER_DEBUG_INST_INFO STRUC
Id			UINT ?
Opcode			UINT ?
uOutputs		UINT ?
pOutputs		D3D10_SHADER_DEBUG_OUTPUTREG_INFO 2 dup(<>)
TokenId			UINT ?
NestingLevel		UINT ?
Scopes			UINT ?
ScopeInfo		UINT ?
AccessedVars		UINT ?
AccessedVarsInfo	UINT ?
D3D10_SHADER_DEBUG_INST_INFO ENDS

D3D10_SHADER_DEBUG_FILE_INFO STRUC
FileName		UINT ?
FileNameLen		UINT ?
FileData		UINT ?
FileLen			UINT ?
D3D10_SHADER_DEBUG_FILE_INFO ENDS

D3D10_SHADER_DEBUG_INFO STRUC
_Size			UINT ?
Creator			UINT ?
EntrypointName		UINT ?
ShaderTarget		UINT ?
CompileFlags		UINT ?
Files			UINT ?
FileInfo		UINT ?
Instructions		UINT ?
InstructionInfo		UINT ?
Variables		UINT ?
VariableInfo		UINT ?
InputVariables		UINT ?
InputVariableInfo	UINT ?
Tokens			UINT ?
TokenInfo		UINT ?
Scopes			UINT ?
ScopeInfo		UINT ?
ScopeVariables		UINT ?
ScopeVariableInfo	UINT ?
UintOffset		UINT ?
StringOffset		UINT ?
D3D10_SHADER_DEBUG_INFO ENDS

DEFINE_GUID(IID_ID3D10ShaderReflection1, 0xc3457783, 0xa846, 0x47ce, 0x95, 0x20, 0xce, 0xa6, 0xf6, 0x6e, 0x74, 0x47);

.comdef ID3D10ShaderReflection1
    QueryInterface		proc :REFIID, :ptr
    AddRef			proc
    Release			proc
    GetDesc			proc :ptr
    GetConstantBufferByIndex	proc :UINT
    GetConstantBufferByName	proc :LPCSTR
    GetResourceBindingDesc	proc :UINT, :ptr
    GetInputParameterDesc	proc :UINT, :ptr
    GetOutputParameterDesc	proc :UINT, :ptr
    GetVariableByName		proc :LPCSTR
    GetResourceBindingDescByName proc :LPCSTR, :ptr
    GetMovInstructionCount	proc :ptr
    GetMovcInstructionCount	proc :ptr
    GetConversionInstructionCount proc :ptr
    GetBitwiseInstructionCount	proc :ptr
    GetGSInputPrimitive		proc :ptr
    IsLevel9Shader		proc :ptr
    IsSampleFrequencyShader	proc :ptr
    .ends

.list
endif


