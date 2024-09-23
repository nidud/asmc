include d3dx9.inc
ifndef __D3DX9SHADER_INC
define __D3DX9SHADER_INC

D3DXSHADER_DEBUG	equ 0x1
D3DXSHADER_SKIPVALIDATION equ 0x2
D3DXSHADER_SKIPOPTIMIZATION equ 0x4
D3DXSHADER_PACKMATRIX_ROWMAJOR equ 0x8
D3DXSHADER_PACKMATRIX_COLUMNMAJOR equ 0x10
D3DXSHADER_PARTIALPRECISION equ 0x20
D3DXSHADER_FORCE_VS_SOFTWARE_NOOPT equ 0x40
D3DXSHADER_FORCE_PS_SOFTWARE_NOOPT equ 0x80
D3DXSHADER_NO_PRESHADER equ 0x100
D3DXSHADER_AVOID_FLOW_CONTROL equ 0x200
D3DXSHADER_PREFER_FLOW_CONTROL equ 0x400
D3DXSHADER_ENABLE_BACKWARDS_COMPATIBILITY equ 0x1000
D3DXSHADER_IEEE_STRICTNESS equ 0x2000

D3DXSHADER_OPTIMIZATION_LEVEL0 equ 0x4000
D3DXSHADER_OPTIMIZATION_LEVEL1 equ 0x0
D3DXSHADER_OPTIMIZATION_LEVEL2 equ 0xC000
D3DXSHADER_OPTIMIZATION_LEVEL3 equ 0x8000

D3DXSHADER_USE_LEGACY_D3DX9_31_DLL equ 0x10000

D3DXCONSTTABLE_LARGEADDRESSAWARE equ 0x20000

D3DXHANDLE		typedef LPSTR
LPD3DXHANDLE		typedef ptr D3DXHANDLE

D3DXREGISTER_SET	typedef SDWORD
D3DXRS_BOOL		equ 0
D3DXRS_INT4		equ 1
D3DXRS_FLOAT4		equ 2
D3DXRS_SAMPLER		equ 3
D3DXRS_FORCE_DWORD	equ 0x7fffffff

D3DXPARAMETER_CLASS	typedef SDWORD
D3DXPC_SCALAR		equ 0
D3DXPC_VECTOR		equ 1
D3DXPC_MATRIX_ROWS	equ 2
D3DXPC_MATRIX_COLUMNS	equ 3
D3DXPC_OBJECT		equ 4
D3DXPC_STRUCT		equ 5
D3DXPC_FORCE_DWORD	equ 0x7fffffff

D3DXPARAMETER_TYPE	typedef SDWORD
D3DXPT_VOID		equ 0
D3DXPT_BOOL		equ 1
D3DXPT_INT		equ 2
D3DXPT_FLOAT		equ 3
D3DXPT_STRING		equ 4
D3DXPT_TEXTURE		equ 5
D3DXPT_TEXTURE1D	equ 6
D3DXPT_TEXTURE2D	equ 7
D3DXPT_TEXTURE3D	equ 8
D3DXPT_TEXTURECUBE	equ 9
D3DXPT_SAMPLER		equ 10
D3DXPT_SAMPLER1D	equ 11
D3DXPT_SAMPLER2D	equ 12
D3DXPT_SAMPLER3D	equ 13
D3DXPT_SAMPLERCUBE	equ 14
D3DXPT_PIXELSHADER	equ 15
D3DXPT_VERTEXSHADER	equ 16
D3DXPT_PIXELFRAGMENT	equ 17
D3DXPT_VERTEXFRAGMENT	equ 18
D3DXPT_UNSUPPORTED	equ 19
D3DXPT_FORCE_DWORD	equ 0x7fffffff

D3DXCONSTANTTABLE_DESC	STRUC
Creator			LPSTR ?
Version			dd ?
Constants		UINT ?
D3DXCONSTANTTABLE_DESC	ENDS
LPD3DXCONSTANTTABLE_DESC typedef ptr D3DXCONSTANTTABLE_DESC

D3DXCONSTANT_DESC	STRUC
Name			LPSTR ?
RegisterSet		D3DXREGISTER_SET ?
RegisterIndex		UINT ?
RegisterCount		UINT ?
Class			D3DXPARAMETER_CLASS ?
Type			D3DXPARAMETER_TYPE ?
Rows			UINT ?
Columns			UINT ?
Elements		UINT ?
StructMembers		UINT ?
Bytes			UINT ?
DefaultValue		PVOID ?
D3DXCONSTANT_DESC	ENDS
LPD3DXCONSTANT_DESC	typedef ptr D3DXCONSTANT_DESC

if D3DX_SDK_VERSION LT 43
DEFINE_GUID(IID_ID3DXConstantTable, 0x9dca3190, 0x38b9, 0x4fc3, 0x92, 0xe3, 0x39, 0xc6, 0xdd, 0xfb, 0x35, 0x8b)
else
DEFINE_GUID(IID_ID3DXConstantTable, 0xab3c758f, 0x093e, 0x4356, 0xb7, 0x62, 0x4d, 0xb1, 0x8f, 0x1b, 0x3a, 0x01)
endif

.comdef ID3DXConstantTable : public ID3DXBuffer

    GetDesc		proc :ptr
    GetConstantDesc	proc :D3DXHANDLE, :ptr, :ptr
    GetSamplerIndex	proc :D3DXHANDLE
    GetConstant		proc :D3DXHANDLE, :UINT
    GetConstantByName	proc :D3DXHANDLE, :ptr
    GetConstantElement	proc :D3DXHANDLE, :UINT
    SetDefaults		proc :ptr
    SetValue		proc :ptr, :D3DXHANDLE, :ptr, :UINT
    SetBool		proc :ptr, :D3DXHANDLE, :BOOL
    SetBoolArray	proc :ptr, :D3DXHANDLE, :ptr, :UINT
    SetInt		proc :ptr, :D3DXHANDLE, :SINT
    SetIntArray		proc :ptr, :D3DXHANDLE, :ptr, :UINT
    SetFloat		proc :ptr, :D3DXHANDLE, :float
    SetFloatArray	proc :ptr, :D3DXHANDLE, :ptr, :UINT
    SetVector		proc :ptr, :D3DXHANDLE, :ptr
    SetVectorArray	proc :ptr, :D3DXHANDLE, :ptr, :UINT
    SetMatrix		proc :ptr, :D3DXHANDLE, :ptr
    SetMatrixArray	proc :ptr, :D3DXHANDLE, :ptr, :UINT
    SetMatrixPointerArray proc :ptr, :D3DXHANDLE, :ptr, :UINT
    SetMatrixTranspose	proc :ptr, :D3DXHANDLE, :ptr
    SetMatrixTransposeArray proc :ptr, :D3DXHANDLE, :ptr, :UINT
    SetMatrixTransposePointerArray proc :ptr, :D3DXHANDLE, :ptr, :UINT
   .ends

DEFINE_GUID(IID_ID3DXTextureShader, 0x3e3d67f8, 0xaa7a, 0x405d, 0xa8, 0x57, 0xba, 0x1, 0xd4, 0x75, 0x84, 0x26);

.comdef ID3DXTextureShader : public IUnknown

    GetFunction		proc :ptr
    GetConstantBuffer	proc :ptr
    GetDesc		proc :ptr
    GetConstantDesc	proc :D3DXHANDLE, :ptr, :ptr
    GetConstant		proc :D3DXHANDLE, :UINT
    GetConstantByName	proc :D3DXHANDLE, :ptr
    GetConstantElement	proc :D3DXHANDLE, :UINT
    SetDefaults		proc
    SetValue		proc :D3DXHANDLE, :ptr, :UINT
    SetBool		proc :D3DXHANDLE, :BOOL
    SetBoolArray	proc :D3DXHANDLE, :ptr, :UINT
    SetInt		proc :D3DXHANDLE, :SINT
    SetIntArray		proc :D3DXHANDLE, :ptr, :UINT
    SetFloat		proc :D3DXHANDLE, :FLOAT
    SetFloatArray	proc :D3DXHANDLE, :ptr, :UINT
    SetVector		proc :D3DXHANDLE, :ptr
    SetVectorArray	proc :D3DXHANDLE, :ptr, :UINT
    SetMatrix		proc :D3DXHANDLE, :ptr
    SetMatrixArray	proc :D3DXHANDLE, :ptr, :UINT
    SetMatrixPointerArray proc :D3DXHANDLE, :ptr, :UINT
    SetMatrixTranspose	proc :D3DXHANDLE, :ptr
    SetMatrixTransposeArray proc :D3DXHANDLE, :ptr, :UINT
    SetMatrixTransposePointerArray proc :D3DXHANDLE, :ptr, :UINT
   .ends

D3DXMACRO		STRUC
Name			LPSTR ?
Definition		LPSTR ?
D3DXMACRO		ENDS
LPD3DXMACRO		typedef ptr D3DXMACRO

D3DXSEMANTIC		STRUC
Usage			UINT ?
UsageIndex		UINT ?
D3DXSEMANTIC		ENDS
LPD3DXSEMANTIC		typedef ptr D3DXSEMANTIC

D3DXINCLUDE_TYPE	typedef SDWORD
D3DXINC_LOCAL		equ 0
D3DXINC_SYSTEM		equ 1
D3DXINC_FORCE_DWORD	equ 0x7fffffff

ID3DXInclude		STRUC
Open			PVOID ?
Close			PVOID ?
ID3DXInclude		ENDS

LPD3DXINCLUDE		typedef ptr ID3DXInclude

D3DXFRAGMENT_DESC	STRUC
Name			LPSTR ?
Target			dd ?
D3DXFRAGMENT_DESC	ENDS
LPD3DXFRAGMENT_DESC	typedef ptr D3DXFRAGMENT_DESC

DEFINE_GUID(IID_ID3DXFragmentLinker, 0x1a2c0cc2, 0xe5b6, 0x4ebc, 0x9e, 0x8d, 0x39, 0xe, 0x5, 0x78, 0x11, 0xb6);

.comdef ID3DXFragmentLinker : public IUnknown

    GetDevice		proc :ptr
    GetNumberOfFragments proc
    GetFragmentHandleByIndex proc :UINT
    GetFragmentHandleByName proc :ptr
    GetFragmentDesc	proc :D3DXHANDLE, :ptr
    AddFragments	proc :ptr
    GetAllFragments	proc :ptr
    GetFragment		proc :D3DXHANDLE, :ptr
    LinkShader		proc :ptr, :DWORD, :ptr, :UINT, :ptr, :ptr
    LinkVertexShader	proc :ptr, :DWORD, :ptr, :UINT, :ptr, :ptr
    LinkPixelShader	proc :ptr, :DWORD, :ptr, :UINT, :ptr, :ptr
    ClearCache		proc
   .ends

D3DXGetPixelShaderProfile proto WINAPI :ptr
D3DXGetShaderSize proto WINAPI :ptr
D3DXGetShaderVersion proto WINAPI :ptr
D3DXGetVertexShaderProfile proto WINAPI :ptr
D3DXFindShaderComment proto WINAPI :ptr, :DWORD, :ptr, :ptr
D3DXGetShaderSamplers proto WINAPI :ptr, :ptr, :ptr
D3DXAssembleShaderFromFileA proto WINAPI :LPSTR, :ptr, :ptr, :DWORD, :ptr, :ptr
D3DXAssembleShaderFromFileW proto WINAPI :LPWSTR, :ptr, :ptr, :DWORD, :ptr, :ptr
D3DXAssembleShaderFromResourceA proto WINAPI :HMODULE, :LPSTR, :ptr, :ptr, :DWORD, :ptr, :ptr
D3DXAssembleShaderFromResourceW proto WINAPI :HMODULE, :LPWSTR, :ptr, :ptr, :DWORD, :ptr, :ptr
D3DXAssembleShader proto WINAPI :LPSTR, :UINT, :ptr, :ptr, :DWORD, :ptr, :ptr
D3DXCompileShader proto WINAPI :LPSTR, :UINT, :ptr, :ptr, :LPSTR, :LPSTR, :DWORD, :ptr, :ptr, :ptr
D3DXDisassembleShader proto WINAPI :ptr, :BOOL, :LPSTR, :ptr
D3DXCompileShaderFromFileA proto WINAPI :LPSTR, :ptr, :ptr, :LPSTR, :LPSTR, :DWORD, :ptr, :ptr, :ptr
D3DXCompileShaderFromFileW proto WINAPI :LPWSTR, :ptr, :ptr, :LPSTR, :LPSTR, :DWORD, :ptr, :ptr, :ptr
D3DXCompileShaderFromResourceA proto WINAPI :HMODULE, :LPSTR, :ptr, :ptr, :LPSTR, :LPSTR, :DWORD, :ptr, :ptr, :ptr
D3DXCompileShaderFromResourceW proto WINAPI :HMODULE, :LPWSTR, :ptr, :ptr, :LPSTR, :LPSTR, :DWORD, :ptr, :ptr, :ptr
D3DXPreprocessShader proto WINAPI :LPSTR, :UINT, :ptr, :ptr, :ptr, :ptr
D3DXPreprocessShaderFromFileA proto WINAPI :LPSTR, :ptr, :ptr, :ptr, :ptr
D3DXPreprocessShaderFromFileW proto WINAPI :LPWSTR, :ptr, :ptr, :ptr, :ptr
D3DXPreprocessShaderFromResourceA proto WINAPI :HMODULE, :LPSTR, :ptr, :ptr, :ptr, :ptr
D3DXPreprocessShaderFromResourceW proto WINAPI :HMODULE, :LPWSTR, :ptr, :ptr, :ptr, :ptr
D3DXGetShaderConstantTableEx proto WINAPI :ptr, :DWORD, :ptr
D3DXGetShaderConstantTable proto WINAPI :ptr, :ptr
D3DXGetShaderInputSemantics proto WINAPI :ptr, :ptr, :ptr
D3DXGetShaderOutputSemantics proto WINAPI :ptr, :ptr, :ptr
D3DXCreateTextureShader proto WINAPI :ptr, :ptr
D3DXCreateFragmentLinker proto WINAPI :ptr, :UINT, :ptr
D3DXCreateFragmentLinkerEx proto WINAPI :ptr, :UINT, :DWORD, :ptr

D3DXSHADER_CONSTANTTABLE STRUC
Size			dd ?
Creator			dd ?
Version			dd ?
Constants		dd ?
ConstantInfo		dd ?
Flags			dd ?
Target			dd ?
D3DXSHADER_CONSTANTTABLE ENDS
LPD3DXSHADER_CONSTANTTABLE typedef ptr D3DXSHADER_CONSTANTTABLE

D3DXSHADER_CONSTANTINFO STRUC
Name			dd ?
RegisterSet		dw ?
RegisterIndex		dw ?
RegisterCount		dw ?
Reserved		dw ?
TypeInfo		dd ?
DefaultValue		dd ?
D3DXSHADER_CONSTANTINFO ENDS
LPD3DXSHADER_CONSTANTINFO typedef ptr D3DXSHADER_CONSTANTINFO

D3DXSHADER_TYPEINFO	STRUC
Class			dw ?
Type			dw ?
Rows			dw ?
Columns			dw ?
Elements		dw ?
StructMembers		dw ?
StructMemberInfo	dd ?
D3DXSHADER_TYPEINFO	ENDS
LPD3DXSHADER_TYPEINFO	typedef ptr D3DXSHADER_TYPEINFO

D3DXSHADER_STRUCTMEMBERINFO STRUC
Name			dd ?
TypeInfo		dd ?
D3DXSHADER_STRUCTMEMBERINFO ENDS
LPD3DXSHADER_STRUCTMEMBERINFO typedef ptr D3DXSHADER_STRUCTMEMBERINFO

endif
