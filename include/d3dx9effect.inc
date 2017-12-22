include d3dx9.inc
ifndef __D3DX9EFFECT_H__
__D3DX9EFFECT_H__ equ <>
.xlist

D3DXFX_DONOTSAVESTATE	equ (1 SHL 0)
D3DXFX_DONOTSAVESHADERSTATE equ (1 SHL 1)
D3DXFX_DONOTSAVESAMPLERSTATE equ (1 SHL 2)
D3DXFX_NOT_CLONEABLE	equ (1 SHL 11)
D3DXFX_LARGEADDRESSAWARE equ (1 SHL 17)

D3DX_PARAMETER_SHARED	equ 1
D3DX_PARAMETER_LITERAL	equ 2
D3DX_PARAMETER_ANNOTATION equ 4

D3DXEFFECT_DESC		STRUC
Creator			LPSTR ?
Parameters		UINT ?
Techniques		UINT ?
Functions		UINT ?
D3DXEFFECT_DESC		ENDS

D3DXPARAMETER_DESC	STRUC
_Name			LPSTR ?
Semantic		LPSTR ?
Class			D3DXPARAMETER_CLASS ?
_Type			D3DXPARAMETER_TYPE ?
Rows			UINT ?
Columns			UINT ?
Elements		UINT ?
Annotations		UINT ?
StructMembers		UINT ?
Flags			dd ?
Bytes			UINT ?
D3DXPARAMETER_DESC	ENDS

D3DXTECHNIQUE_DESC	STRUC
_Name			LPSTR ?
Passes			UINT ?
Annotations		UINT ?
D3DXTECHNIQUE_DESC	ENDS

D3DXPASS_DESC		STRUC
_Name			LPSTR ?
Annotations		UINT ?
pVertexShaderFunction	LPDWORD ?
pPixelShaderFunction	LPDWORD ?
D3DXPASS_DESC		ENDS

D3DXFUNCTION_DESC	STRUC
_Name			LPSTR ?
Annotations		UINT ?
D3DXFUNCTION_DESC	ENDS

LPD3DXEFFECTPOOL	typedef ptr ID3DXEffectPool

DEFINE_GUID(IID_ID3DXEffectPool, 0x9537ab04, 0x3250, 0x412e, 0x82, 0x13, 0xfc, 0xd2, 0xf8, 0x67, 0x79, 0x33);

ID3DXEffectPool		STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
ID3DXEffectPool		ENDS

LPD3DXBASEEFFECT	typedef ptr ID3DXBaseEffect

DEFINE_GUID(IID_ID3DXBaseEffect, 0x17c18ac, 0x103f, 0x4417, 0x8c, 0x51, 0x6b, 0xf6, 0xef, 0x1e, 0x56, 0xbe);

ID3DXBaseEffect		STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetDesc, :ptr
	STDMETHOD	GetParameterDesc, :D3DXHANDLE, :ptr
	STDMETHOD	GetTechniqueDesc, :D3DXHANDLE, :ptr
	STDMETHOD	GetPassDesc, :D3DXHANDLE, :ptr
	STDMETHOD	GetFunctionDesc, :D3DXHANDLE, :ptr
	STDMETHOD	GetParameter, :D3DXHANDLE, :UINT
	STDMETHOD	GetParameterByName, :D3DXHANDLE, :LPSTR
	STDMETHOD	GetParameterBySemantic, :D3DXHANDLE, :LPSTR
	STDMETHOD	GetParameterElement, :D3DXHANDLE, :UINT
	STDMETHOD	GetTechnique, :UINT
	STDMETHOD	GetTechniqueByName, :LPSTR
	STDMETHOD	GetPass, :D3DXHANDLE, :UINT
	STDMETHOD	GetPassByName, :D3DXHANDLE, :LPSTR
	STDMETHOD	GetFunction, :UINT
	STDMETHOD	GetFunctionByName, :LPSTR
	STDMETHOD	GetAnnotation, :D3DXHANDLE, :UINT
	STDMETHOD	GetAnnotationByName, :D3DXHANDLE, :LPSTR
	STDMETHOD	SetValue, :D3DXHANDLE, :ptr, :UINT
	STDMETHOD	GetValue, :D3DXHANDLE, :ptr, :UINT
	STDMETHOD	SetBool, :D3DXHANDLE, :BOOL
	STDMETHOD	GetBool, :D3DXHANDLE, :ptr
	STDMETHOD	SetBoolArray, :D3DXHANDLE, :ptr, :UINT
	STDMETHOD	GetBoolArray, :D3DXHANDLE, :ptr, :UINT
	STDMETHOD	SetInt, :D3DXHANDLE, :SINT
	STDMETHOD	GetInt, :D3DXHANDLE, :ptr
	STDMETHOD	SetIntArray, :D3DXHANDLE, :ptr, :UINT
	STDMETHOD	GetIntArray, :D3DXHANDLE, :ptr, :UINT
	STDMETHOD	SetFloat, :D3DXHANDLE, :FLOAT
	STDMETHOD	GetFloat, :D3DXHANDLE, :ptr
	STDMETHOD	SetFloatArray, :D3DXHANDLE, :ptr, :UINT
	STDMETHOD	GetFloatArray, :D3DXHANDLE, :ptr, :UINT
	STDMETHOD	SetVector, :D3DXHANDLE, :ptr
	STDMETHOD	GetVector, :D3DXHANDLE, :ptr
	STDMETHOD	SetVectorArray, :D3DXHANDLE, :ptr, :UINT
	STDMETHOD	GetVectorArray, :D3DXHANDLE, :ptr, :UINT
	STDMETHOD	SetMatrix, :D3DXHANDLE, :ptr
	STDMETHOD	GetMatrix, :D3DXHANDLE, :ptr
	STDMETHOD	SetMatrixArray, :D3DXHANDLE, :ptr, :UINT
	STDMETHOD	GetMatrixArray, :D3DXHANDLE, :ptr, :UINT
	STDMETHOD	SetMatrixPointerArray, :D3DXHANDLE, :ptr, :UINT
	STDMETHOD	GetMatrixPointerArray, :D3DXHANDLE, :ptr, :UINT
	STDMETHOD	SetMatrixTranspose, :D3DXHANDLE, :ptr
	STDMETHOD	GetMatrixTranspose, :D3DXHANDLE, :ptr
	STDMETHOD	SetMatrixTransposeArray, :D3DXHANDLE, :ptr
	STDMETHOD	GetMatrixTransposeArray, :D3DXHANDLE, :ptr, :UINT
	STDMETHOD	SetMatrixTransposePointerArray, :D3DXHANDLE, :ptr, :UINT
	STDMETHOD	GetMatrixTransposePointerArray, :D3DXHANDLE, :ptr, :UINT
	STDMETHOD	SetString, :D3DXHANDLE, :ptr
	STDMETHOD	GetString, :D3DXHANDLE, :ptr
	STDMETHOD	SetTexture, :D3DXHANDLE, :ptr
	STDMETHOD	GetTexture, :D3DXHANDLE, :ptr
	STDMETHOD	GetPixelShader, :D3DXHANDLE, :ptr
	STDMETHOD	GetVertexShader, :D3DXHANDLE, :ptr
	STDMETHOD	SetArrayRange, :D3DXHANDLE, :UINT, :UINT
ID3DXBaseEffect		ENDS

LPD3DXEFFECTSTATEMANAGER typedef ptr ID3DXEffectStateManager

DEFINE_GUID(IID_ID3DXEffectStateManager, 0x79aab587, 0x6dbc, 0x4fa7, 0x82, 0xde, 0x37, 0xfa, 0x17, 0x81, 0xc5, 0xce);

ID3DXEffectStateManager STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	SetTransform, :D3DTRANSFORMSTATETYPE, :ptr
	STDMETHOD	SetMaterial, :ptr
	STDMETHOD	SetLight, :DWORD, :ptr
	STDMETHOD	LightEnable, :DWORD, :BOOL
	STDMETHOD	SetRenderState, :D3DRENDERSTATETYPE, :DWORD
	STDMETHOD	SetTexture, :DWORD, :ptr
	STDMETHOD	SetTextureStageState, :DWORD, :D3DTEXTURESTAGESTATETYPE, :DWORD
	STDMETHOD	SetSamplerState, :DWORD, :D3DSAMPLERSTATETYPE, :DWORD
	STDMETHOD	SetNPatchMode, :FLOAT
	STDMETHOD	SetFVF, :DWORD
	STDMETHOD	SetVertexShader, :ptr
	STDMETHOD	SetVertexShaderConstantF, :UINT, :ptr, :UINT
	STDMETHOD	SetVertexShaderConstantI, :UINT, :ptr, :UINT
	STDMETHOD	SetVertexShaderConstantB, :UINT, :ptr, :UINT
	STDMETHOD	SetPixelShader, :ptr
	STDMETHOD	SetPixelShaderConstantF, :UINT, :ptr, :UINT
	STDMETHOD	SetPixelShaderConstantI, :UINT, :ptr, :UINT
	STDMETHOD	SetPixelShaderConstantB, :UINT, :ptr, :UINT
ID3DXEffectStateManager ENDS

LPD3DXEFFECT		typedef ptr ID3DXEffect

DEFINE_GUID(IID_ID3DXEffect, 0xf6ceb4b3, 0x4e4c, 0x40dd, 0xb8, 0x83, 0x8d, 0x8d, 0xe5, 0xea, 0xc, 0xd5);

ID3DXEffect		STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetDesc, :ptr
	STDMETHOD	GetParameterDesc, :D3DXHANDLE, :ptr
	STDMETHOD	GetTechniqueDesc, :D3DXHANDLE, :ptr
	STDMETHOD	GetPassDesc, :D3DXHANDLE, :ptr
	STDMETHOD	GetFunctionDesc, :D3DXHANDLE, :ptr
	STDMETHOD	GetParameter, :D3DXHANDLE, :UINT
	STDMETHOD	GetParameterByName, :D3DXHANDLE, :ptr
	STDMETHOD	GetParameterBySemantic, :D3DXHANDLE, :ptr
	STDMETHOD	GetParameterElement, :D3DXHANDLE, :UINT
	STDMETHOD	GetTechnique, :UINT
	STDMETHOD	GetTechniqueByName, :ptr
	STDMETHOD	GetPass, :D3DXHANDLE, :UINT
	STDMETHOD	GetPassByName, :D3DXHANDLE, :ptr
	STDMETHOD	GetFunction, :UINT
	STDMETHOD	GetFunctionByName, :ptr
	STDMETHOD	GetAnnotation, :D3DXHANDLE, :UINT
	STDMETHOD	GetAnnotationByName, :D3DXHANDLE, :ptr
	STDMETHOD	SetValue, :D3DXHANDLE, :ptr, :UINT
	STDMETHOD	GetValue, :D3DXHANDLE, :ptr, :UINT
	STDMETHOD	SetBool, :D3DXHANDLE, :BOOL
	STDMETHOD	GetBool, :D3DXHANDLE, :ptr
	STDMETHOD	SetBoolArray, :D3DXHANDLE, :ptr, :UINT
	STDMETHOD	GetBoolArray, :D3DXHANDLE, :ptr, :UINT
	STDMETHOD	SetInt, :D3DXHANDLE, :SINT
	STDMETHOD	GetInt, :D3DXHANDLE, :ptr
	STDMETHOD	SetIntArray, :D3DXHANDLE, :ptr, :UINT
	STDMETHOD	GetIntArray, :D3DXHANDLE, :ptr, :UINT
	STDMETHOD	SetFloat, :D3DXHANDLE, :FLOAT
	STDMETHOD	GetFloat, :D3DXHANDLE, :ptr
	STDMETHOD	SetFloatArray, :D3DXHANDLE, :ptr, :UINT
	STDMETHOD	GetFloatArray, :D3DXHANDLE, :ptr, :UINT
	STDMETHOD	SetVector, :D3DXHANDLE, :ptr
	STDMETHOD	GetVector, :D3DXHANDLE, :ptr
	STDMETHOD	SetVectorArray, :D3DXHANDLE, :ptr, :UINT
	STDMETHOD	GetVectorArray, :D3DXHANDLE, :ptr, :UINT
	STDMETHOD	SetMatrix, :D3DXHANDLE, :ptr
	STDMETHOD	GetMatrix, :D3DXHANDLE, :ptr
	STDMETHOD	SetMatrixArray, :D3DXHANDLE, :ptr
	STDMETHOD	GetMatrixArray, :D3DXHANDLE, :ptr
	STDMETHOD	SetMatrixPointerArray, :D3DXHANDLE, :ptr
	STDMETHOD	GetMatrixPointerArray, :D3DXHANDLE, :ptr
	STDMETHOD	SetMatrixTranspose, :D3DXHANDLE, :ptr
	STDMETHOD	GetMatrixTranspose, :D3DXHANDLE, :ptr
	STDMETHOD	SetMatrixTransposeArray, :D3DXHANDLE, :ptr
	STDMETHOD	GetMatrixTransposeArray, :D3DXHANDLE, :ptr, :UINT
	STDMETHOD	SetMatrixTransposePointerArray, :D3DXHANDLE, :ptr, :UINT
	STDMETHOD	GetMatrixTransposePointerArray, :D3DXHANDLE, :ptr, :UINT
	STDMETHOD	SetString, :D3DXHANDLE, :ptr
	STDMETHOD	GetString, :D3DXHANDLE, :ptr
	STDMETHOD	SetTexture, :D3DXHANDLE, :ptr
	STDMETHOD	GetTexture, :D3DXHANDLE, :ptr
	STDMETHOD	GetPixelShader, :D3DXHANDLE, :ptr
	STDMETHOD	GetVertexShader, :D3DXHANDLE, :ptr
	STDMETHOD	SetArrayRange, :D3DXHANDLE, :UINT, :UINT

	STDMETHOD	GetPool, :ptr
	STDMETHOD	SetTechnique, :D3DXHANDLE
	STDMETHOD	GetCurrentTechnique
	STDMETHOD	ValidateTechnique, :D3DXHANDLE
	STDMETHOD	FindNextValidTechnique, :D3DXHANDLE, :ptr
	STDMETHOD	IsParameterUsed, :D3DXHANDLE, :D3DXHANDLE
	STDMETHOD	Begin, :ptr, :DWORD
	STDMETHOD	BeginPass, :UINT
	STDMETHOD	CommitChanges
	STDMETHOD	EndPass
	STDMETHOD	_End
	STDMETHOD	GetDevice, :ptr
	STDMETHOD	OnLostDevice
	STDMETHOD	OnResetDevice
	STDMETHOD	SetStateManager, :ptr
	STDMETHOD	GetStateManager, :ptr
	STDMETHOD	BeginParameterBlock
	STDMETHOD	EndParameterBlock
	STDMETHOD	ApplyParameterBlock, :D3DXHANDLE
	STDMETHOD	DeleteParameterBlock, :D3DXHANDLE
	STDMETHOD	CloneEffect, :ptr, :ptr
	STDMETHOD	SetRawValue, :D3DXHANDLE, :ptr, :UINT, :UINT
ID3DXEffect		ENDS

LPD3DXEFFECTCOMPILER	typedef ptr ID3DXEffectCompiler

DEFINE_GUID(IID_ID3DXEffectCompiler, 0x51b8a949, 0x1a31, 0x47e6, 0xbe, 0xa0, 0x4b, 0x30, 0xdb, 0x53, 0xf1, 0xe0);

ID3DXEffectCompiler	STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetDesc, :ptr
	STDMETHOD	GetParameterDesc, :D3DXHANDLE, :ptr
	STDMETHOD	GetTechniqueDesc, :D3DXHANDLE, :ptr
	STDMETHOD	GetPassDesc, :D3DXHANDLE, :ptr
	STDMETHOD	GetFunctionDesc, :D3DXHANDLE, :ptr
	STDMETHOD	GetParameter, :D3DXHANDLE, :UINT
	STDMETHOD	GetParameterByName, :D3DXHANDLE, :ptr
	STDMETHOD	GetParameterBySemantic, :D3DXHANDLE, :ptr
	STDMETHOD	GetParameterElement, :D3DXHANDLE, :UINT
	STDMETHOD	GetTechnique, :UINT
	STDMETHOD	GetTechniqueByName, :ptr
	STDMETHOD	GetPass, :D3DXHANDLE, :UINT
	STDMETHOD	GetPassByName, :D3DXHANDLE, :ptr
	STDMETHOD	GetFunction, :UINT
	STDMETHOD	GetFunctionByName, :ptr
	STDMETHOD	GetAnnotation, :D3DXHANDLE, :UINT
	STDMETHOD	GetAnnotationByName, :D3DXHANDLE, :ptr
	STDMETHOD	SetValue, :D3DXHANDLE, :ptr, :UINT
	STDMETHOD	GetValue, :D3DXHANDLE, :ptr, :UINT
	STDMETHOD	SetBool, :D3DXHANDLE, :BOOL
	STDMETHOD	GetBool, :D3DXHANDLE, :ptr
	STDMETHOD	SetBoolArray, :D3DXHANDLE, :ptr, :UINT
	STDMETHOD	GetBoolArray, :D3DXHANDLE, :ptr, :UINT
	STDMETHOD	SetInt, :D3DXHANDLE, :SINT
	STDMETHOD	GetInt, :D3DXHANDLE, :ptr
	STDMETHOD	SetIntArray, :D3DXHANDLE, :ptr, :UINT
	STDMETHOD	GetIntArray, :D3DXHANDLE, :ptr, :UINT
	STDMETHOD	SetFloat, :D3DXHANDLE, :FLOAT
	STDMETHOD	GetFloat, :D3DXHANDLE, :ptr
	STDMETHOD	SetFloatArray, :D3DXHANDLE, :ptr, :UINT
	STDMETHOD	GetFloatArray, :D3DXHANDLE, :ptr, :UINT
	STDMETHOD	SetVector, :D3DXHANDLE, :ptr
	STDMETHOD	GetVector, :D3DXHANDLE, :ptr
	STDMETHOD	SetVectorArray, :D3DXHANDLE, :ptr
	STDMETHOD	GetVectorArray, :D3DXHANDLE, :ptr
	STDMETHOD	SetMatrix, :D3DXHANDLE, :ptr
	STDMETHOD	GetMatrix, :D3DXHANDLE, :ptr
	STDMETHOD	SetMatrixArray, :D3DXHANDLE, :ptr, :UINT
	STDMETHOD	GetMatrixArray, :D3DXHANDLE, :ptr, :UINT
	STDMETHOD	SetMatrixPointerArray, :D3DXHANDLE, :ptr, :UINT
	STDMETHOD	GetMatrixPointerArray, :D3DXHANDLE, :ptr, :UINT
	STDMETHOD	SetMatrixTranspose, :D3DXHANDLE, :ptr
	STDMETHOD	GetMatrixTranspose, :D3DXHANDLE, :ptr
	STDMETHOD	SetMatrixTransposeArray, :D3DXHANDLE, :ptr, :UINT
	STDMETHOD	GetMatrixTransposeArray, :D3DXHANDLE, :ptr, :UINT
	STDMETHOD	SetMatrixTransposePointerArray, :D3DXHANDLE, :ptr, :UINT
	STDMETHOD	GetMatrixTransposePointerArray, :D3DXHANDLE, :ptr, :UINT
	STDMETHOD	SetString, :D3DXHANDLE, :ptr
	STDMETHOD	GetString, :D3DXHANDLE, :ptr
	STDMETHOD	SetTexture, :D3DXHANDLE, :ptr
	STDMETHOD	GetTexture, :D3DXHANDLE, :ptr
	STDMETHOD	GetPixelShader, :D3DXHANDLE, :ptr
	STDMETHOD	GetVertexShader, :D3DXHANDLE, :ptr
	STDMETHOD	SetArrayRange, :D3DXHANDLE, :UINT, :UINT
	STDMETHOD	SetLiteral, :D3DXHANDLE, :BOOL
	STDMETHOD	GetLiteral, :D3DXHANDLE, :ptr
	STDMETHOD	CompileEffect, :DWORD, :ptr, :ptr
	STDMETHOD	CompileShader, :D3DXHANDLE, :ptr, :DWORD, :ptr, :ptr, :ptr
ID3DXEffectCompiler	ENDS


;HRESULT
D3DXCreateEffectPool proto WINAPI \
		  pool: ptr ID3DXEffectPool

;HRESULT
D3DXCreateEffect proto WINAPI \
		device: ptr IDirect3DDevice9,
	       srcdata: PVOID,
	    srcdatalen: UINT,
	       defines: ptr D3DXMACRO,
	      _include: ptr ID3DXInclude,
		 flags: DWORD,
		  pool: ptr ID3DXEffectPool,
		effect: ptr ID3DXEffect,
    compilation_errors: ptr ID3DXBuffer

;HRESULT
D3DXCreateEffectEx proto WINAPI \
		device: ptr IDirect3DDevice9,
	       srcdata: PVOID,
	    srcdatalen: UINT,
	       defines: ptr D3DXMACRO,
	      _include: ptr ID3DXInclude,
	skip_constants: LPSTR,
		 flags: DWORD,
		  pool: ptr ID3DXEffectPool,
		effect: ptr ID3DXEffect,
    compilation_errors: ptr ID3DXBuffer

;HRESULT
D3DXCreateEffectCompiler proto WINAPI \
	       srcdata: LPSTR,
	    srcdatalen: UINT,
	       defines: ptr D3DXMACRO,
	      _include: ptr ID3DXInclude,
		 flags: DWORD,
	      compiler: ptr ID3DXEffectCompiler,
	  parse_errors: ptr ID3DXBuffer

;HRESULT
D3DXCreateEffectFromFileExA proto WINAPI \
		device: ptr IDirect3DDevice9,
	       srcfile: LPSTR,
	       defines: ptr D3DXMACRO,
	      _include: ptr ID3DXInclude,
	skip_constants: LPSTR,
		 flags: DWORD,
		  pool: ptr ID3DXEffectPool,
		effect: ptr ID3DXEffect,
    compilation_errors: ptr ID3DXBuffer

;HRESULT
D3DXCreateEffectFromFileExW proto WINAPI \
		device: ptr IDirect3DDevice9,
	       srcfile: LPWSTR,
	       defines: ptr D3DXMACRO,
	      _include: ptr ID3DXInclude,
	skip_constants: LPSTR,
		 flags: DWORD,
		  pool: ptr ID3DXEffectPool,
		effect: ptr ID3DXEffect,
    compilation_errors: ptr ID3DXBuffer

ifdef _UNICODE
D3DXCreateEffectFromFileEx equ <D3DXCreateEffectFromFileExW>
else
D3DXCreateEffectFromFileEx equ <D3DXCreateEffectFromFileExA>
endif

;HRESULT
D3DXCreateEffectFromFileA proto WINAPI \
		device: ptr IDirect3DDevice9,
	       srcfile: LPSTR,
	       defines: ptr D3DXMACRO,
	      _include: ptr ID3DXInclude,
		 flags: DWORD,
		  pool: ptr ID3DXEffectPool,
		effect: ptr ID3DXEffect,
    compilation_errors: ptr ID3DXBuffer

;HRESULT
D3DXCreateEffectFromFileW proto WINAPI \
		device: ptr IDirect3DDevice9,
	       srcfile: LPWSTR,
	       defines: ptr D3DXMACRO,
	      _include: ptr ID3DXInclude,
		 flags: DWORD,
		  pool: ptr ID3DXEffectPool,
		effect: ptr ID3DXEffect,
    compilation_errors: ptr ID3DXBuffer

ifdef _UNICODE
D3DXCreateEffectFromFile equ <D3DXCreateEffectFromFileW>
else
D3DXCreateEffectFromFile equ <D3DXCreateEffectFromFileA>
endif

;HRESULT
D3DXCreateEffectFromResourceExA proto WINAPI \
		device: ptr IDirect3DDevice9,
	     srcmodule: HMODULE,
	   srcresource: LPSTR,
	       defines: ptr D3DXMACRO,
	      _include: ptr ID3DXInclude,
	skip_constants: LPSTR,
		 flags: DWORD,
		  pool: ptr ID3DXEffectPool,
		effect: ptr ID3DXEffect,
    compilation_errors: ptr ID3DXBuffer

;HRESULT
D3DXCreateEffectFromResourceExW proto WINAPI \
		device: ptr IDirect3DDevice9,
	     srcmodule: HMODULE,
	   srcresource: LPWSTR,
	       defines: ptr D3DXMACRO,
	      _include: ptr ID3DXInclude,
	skip_constants: LPSTR,
		 flags: DWORD,
		  pool: ptr ID3DXEffectPool,
		effect: ptr ID3DXEffect,
    compilation_errors: ptr ID3DXBuffer

;HRESULT
D3DXCreateEffectFromResourceA proto WINAPI \
		device: ptr IDirect3DDevice9,
	     srcmodule: HMODULE,
	   srcresource: LPSTR,
	       defines: ptr D3DXMACRO,
	      _include: ptr ID3DXInclude,
		 flags: DWORD,
		  pool: ptr ID3DXEffectPool,
		effect: ptr ID3DXEffect,
    compilation_errors: ptr ID3DXBuffer

;HRESULT
D3DXCreateEffectFromResourceW proto WINAPI \
		device: ptr IDirect3DDevice9,
	     srcmodule: HMODULE,
	   srcresource: LPWSTR,
	       defines: ptr D3DXMACRO,
	      _include: ptr ID3DXInclude,
		 flags: DWORD,
		  pool: ptr ID3DXEffectPool,
		effect: ptr ID3DXEffect,
    compilation_errors: ptr ID3DXBuffer

;HRESULT
D3DXCreateEffectCompilerFromFileA proto WINAPI \
	       srcfile: LPSTR,
	       defines: ptr D3DXMACRO,
	      _include: ptr ID3DXInclude,
		 flags: DWORD,
	effectcompiler: ptr ID3DXEffectCompiler,
	   parseerrors: ptr ID3DXBuffer

;HRESULT
D3DXCreateEffectCompilerFromFileW proto WINAPI \
	       srcfile: LPWSTR,
	       defines: ptr D3DXMACRO,
	      _include: ptr ID3DXInclude,
		 flags: DWORD,
	effectcompiler: ptr ID3DXEffectCompiler,
	   parseerrors: ptr ID3DXBuffer

;HRESULT
D3DXCreateEffectCompilerFromResourceA proto WINAPI \
	     srcmodule: HMODULE,
	   srcresource: LPSTR,
	       defines: ptr D3DXMACRO,
	      _include: ptr ID3DXInclude,
		 flags: DWORD,
	effectcompiler: ptr ID3DXEffectCompiler,
	   parseerrors: ptr ID3DXBuffer

;HRESULT
D3DXCreateEffectCompilerFromResourceW proto WINAPI \
	     srcmodule: HMODULE,
	   srcresource: LPWSTR,
	       defines: ptr D3DXMACRO,
	      _include: ptr ID3DXInclude,
		 flags: DWORD,
	effectcompiler: ptr ID3DXEffectCompiler,
	   parseerrors: ptr ID3DXBuffer

;HRESULT
D3DXDisassembleEffect proto WINAPI \
		effect: ptr ID3DXEffect,
     enable_color_code: BOOL,
	   disassembly: ptr ID3DXBuffer

.list
endif ;; __D3DX9EFFECT_H__
