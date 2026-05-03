include d3dx9.inc
ifndef __D3DX9EFFECT_INC
define __D3DX9EFFECT_INC

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
Name			LPSTR ?
Semantic		LPSTR ?
Class			D3DXPARAMETER_CLASS ?
Type			D3DXPARAMETER_TYPE ?
Rows			UINT ?
Columns			UINT ?
Elements		UINT ?
Annotations		UINT ?
StructMembers		UINT ?
Flags			dd ?
Bytes			UINT ?
D3DXPARAMETER_DESC	ENDS

D3DXTECHNIQUE_DESC	STRUC
Name			LPSTR ?
Passes			UINT ?
Annotations		UINT ?
D3DXTECHNIQUE_DESC	ENDS

D3DXPASS_DESC		STRUC
Name			LPSTR ?
Annotations		UINT ?
pVertexShaderFunction	LPDWORD ?
pPixelShaderFunction	LPDWORD ?
D3DXPASS_DESC		ENDS

D3DXFUNCTION_DESC	STRUC
Name			LPSTR ?
Annotations		UINT ?
D3DXFUNCTION_DESC	ENDS

.comdef ID3DXEffectPool : public IUnknown
    .ends
    LPD3DXEFFECTPOOL	typedef ptr ID3DXEffectPool

DEFINE_GUID(IID_ID3DXEffectPool,0x9537ab04,0x3250,0x412e,0x82,0x13,0xfc,0xd2,0xf8,0x67,0x79,0x33)

.comdef ID3DXBaseEffect : public IUnknown

    GetDesc		proc :ptr
    GetParameterDesc	proc :D3DXHANDLE, :ptr
    GetTechniqueDesc	proc :D3DXHANDLE, :ptr
    GetPassDesc		proc :D3DXHANDLE, :ptr
    GetFunctionDesc	proc :D3DXHANDLE, :ptr
    GetParameter	proc :D3DXHANDLE, :UINT
    GetParameterByName	proc :D3DXHANDLE, :LPSTR
    GetParameterBySemantic proc :D3DXHANDLE, :LPSTR
    GetParameterElement proc :D3DXHANDLE, :UINT
    GetTechnique	proc :UINT
    GetTechniqueByName	proc :LPSTR
    GetPass		proc :D3DXHANDLE, :UINT
    GetPassByName	proc :D3DXHANDLE, :LPSTR
    GetFunction		proc :UINT
    GetFunctionByName	proc :LPSTR
    GetAnnotation	proc :D3DXHANDLE, :UINT
    GetAnnotationByName proc :D3DXHANDLE, :LPSTR
    SetValue		proc :D3DXHANDLE, :ptr, :UINT
    GetValue		proc :D3DXHANDLE, :ptr, :UINT
    SetBool		proc :D3DXHANDLE, :BOOL
    GetBool		proc :D3DXHANDLE, :ptr
    SetBoolArray	proc :D3DXHANDLE, :ptr, :UINT
    GetBoolArray	proc :D3DXHANDLE, :ptr, :UINT
    SetInt		proc :D3DXHANDLE, :SINT
    GetInt		proc :D3DXHANDLE, :ptr
    SetIntArray		proc :D3DXHANDLE, :ptr, :UINT
    GetIntArray		proc :D3DXHANDLE, :ptr, :UINT
    SetFloat		proc :D3DXHANDLE, :FLOAT
    GetFloat		proc :D3DXHANDLE, :ptr
    SetFloatArray	proc :D3DXHANDLE, :ptr, :UINT
    GetFloatArray	proc :D3DXHANDLE, :ptr, :UINT
    SetVector		proc :D3DXHANDLE, :ptr
    GetVector		proc :D3DXHANDLE, :ptr
    SetVectorArray	proc :D3DXHANDLE, :ptr, :UINT
    GetVectorArray	proc :D3DXHANDLE, :ptr, :UINT
    SetMatrix		proc :D3DXHANDLE, :ptr
    GetMatrix		proc :D3DXHANDLE, :ptr
    SetMatrixArray	proc :D3DXHANDLE, :ptr, :UINT
    GetMatrixArray	proc :D3DXHANDLE, :ptr, :UINT
    SetMatrixPointerArray proc :D3DXHANDLE, :ptr, :UINT
    GetMatrixPointerArray proc :D3DXHANDLE, :ptr, :UINT
    SetMatrixTranspose	proc :D3DXHANDLE, :ptr
    GetMatrixTranspose	proc :D3DXHANDLE, :ptr
    SetMatrixTransposeArray proc :D3DXHANDLE, :ptr
    GetMatrixTransposeArray proc :D3DXHANDLE, :ptr, :UINT
    SetMatrixTransposePointerArray proc :D3DXHANDLE, :ptr, :UINT
    GetMatrixTransposePointerArray proc :D3DXHANDLE, :ptr, :UINT
    SetString		proc :D3DXHANDLE, :ptr
    GetString		proc :D3DXHANDLE, :ptr
    SetTexture		proc :D3DXHANDLE, :ptr
    GetTexture		proc :D3DXHANDLE, :ptr
    GetPixelShader	proc :D3DXHANDLE, :ptr
    GetVertexShader	proc :D3DXHANDLE, :ptr
    SetArrayRange	proc :D3DXHANDLE, :UINT, :UINT
   .ends
    LPD3DXBASEEFFECT	typedef ptr ID3DXBaseEffect

DEFINE_GUID(IID_ID3DXBaseEffect,0x17c18ac,0x103f,0x4417,0x8c,0x51,0x6b,0xf6,0xef,0x1e,0x56,0xbe);

.comdef ID3DXEffectStateManager : public IUnknown

    SetTransform	proc :D3DTRANSFORMSTATETYPE, :ptr
    SetMaterial		proc :ptr
    SetLight		proc :DWORD, :ptr
    LightEnable		proc :DWORD, :BOOL
    SetRenderState	proc :D3DRENDERSTATETYPE, :DWORD
    SetTexture		proc :DWORD, :ptr
    SetTextureStageState proc :DWORD, :D3DTEXTURESTAGESTATETYPE, :DWORD
    SetSamplerState	proc :DWORD, :D3DSAMPLERSTATETYPE, :DWORD
    SetNPatchMode	proc :FLOAT
    SetFVF		proc :DWORD
    SetVertexShader	proc :ptr
    SetVertexShaderConstantF proc :UINT, :ptr, :UINT
    SetVertexShaderConstantI proc :UINT, :ptr, :UINT
    SetVertexShaderConstantB proc :UINT, :ptr, :UINT
    SetPixelShader	proc :ptr
    SetPixelShaderConstantF proc :UINT, :ptr, :UINT
    SetPixelShaderConstantI proc :UINT, :ptr, :UINT
    SetPixelShaderConstantB proc :UINT, :ptr, :UINT
   .ends
    LPD3DXEFFECTSTATEMANAGER typedef ptr ID3DXEffectStateManager

DEFINE_GUID(IID_ID3DXEffectStateManager,0x79aab587,0x6dbc,0x4fa7,0x82,0xde,0x37,0xfa,0x17,0x81,0xc5,0xce)

.comdef ID3DXEffect : public ID3DXBaseEffect

    GetPool		proc :ptr
    SetTechnique	proc :D3DXHANDLE
    GetCurrentTechnique proc
    ValidateTechnique	proc :D3DXHANDLE
    FindNextValidTechnique proc :D3DXHANDLE, :ptr
    IsParameterUsed	proc :D3DXHANDLE, :D3DXHANDLE
    Begin		proc :ptr, :DWORD
    BeginPass		proc :UINT
    CommitChanges	proc
    EndPass		proc
    _End		proc
    GetDevice		proc :ptr
    OnLostDevice	proc
    OnResetDevice	proc
    SetStateManager	proc :ptr
    GetStateManager	proc :ptr
    BeginParameterBlock proc
    EndParameterBlock	proc
    ApplyParameterBlock proc :D3DXHANDLE
    DeleteParameterBlock proc :D3DXHANDLE
    CloneEffect		proc :ptr, :ptr
    SetRawValue		proc :D3DXHANDLE, :ptr, :UINT, :UINT
   .ends
    LPD3DXEFFECT	typedef ptr ID3DXEffect

DEFINE_GUID(IID_ID3DXEffect,0xf6ceb4b3,0x4e4c,0x40dd,0xb8,0x83,0x8d,0x8d,0xe5,0xea,0xc,0xd5)


.comdef ID3DXEffectCompiler : public ID3DXBaseEffect

    SetLiteral		proc :D3DXHANDLE, :BOOL
    GetLiteral		proc :D3DXHANDLE, :ptr
    CompileEffect	proc :DWORD, :ptr, :ptr
    CompileShader	proc :D3DXHANDLE, :ptr, :DWORD, :ptr, :ptr, :ptr
   .ends
    LPD3DXEFFECTCOMPILER typedef ptr ID3DXEffectCompiler

DEFINE_GUID(IID_ID3DXEffectCompiler,0x51b8a949,0x1a31,0x47e6,0xbe,0xa0,0x4b,0x30,0xdb,0x53,0xf1,0xe0)

D3DXCreateEffectPool proto WINAPI :ptr
D3DXCreateEffect proto WINAPI :ptr, :ptr, :UINT, :ptr, :ptr, :DWORD, :ptr, :ptr, :ptr
D3DXCreateEffectEx proto WINAPI :ptr, :ptr, :UINT, :ptr, :ptr, :LPSTR, :DWORD, :ptr, :ptr, :ptr
D3DXCreateEffectCompiler proto WINAPI :LPSTR, :UINT, :ptr, :ptr, :DWORD, :ptr, :ptr
D3DXCreateEffectFromFileExA proto WINAPI :ptr, :LPSTR, :ptr, :ptr, :LPSTR, :DWORD, :ptr, :ptr, :ptr
D3DXCreateEffectFromFileExW proto WINAPI :ptr, :LPWSTR, :ptr, :ptr, :LPSTR, :DWORD, :ptr, :ptr, :ptr
ifdef _UNICODE
D3DXCreateEffectFromFileEx equ <D3DXCreateEffectFromFileExW>
else
D3DXCreateEffectFromFileEx equ <D3DXCreateEffectFromFileExA>
endif

D3DXCreateEffectFromFileA proto WINAPI :ptr, :LPSTR, :ptr, :ptr, :DWORD, :ptr, :ptr, :ptr
D3DXCreateEffectFromFileW proto WINAPI :ptr, :LPWSTR, :ptr, :ptr, :DWORD, :ptr, :ptr, :ptr
ifdef _UNICODE
D3DXCreateEffectFromFile equ <D3DXCreateEffectFromFileW>
else
D3DXCreateEffectFromFile equ <D3DXCreateEffectFromFileA>
endif
D3DXCreateEffectFromResourceExA proto WINAPI :ptr, :HMODULE, :LPSTR, :ptr, :ptr, :LPSTR, :DWORD, :ptr, :ptr, :ptr
D3DXCreateEffectFromResourceExW proto WINAPI :ptr, :HMODULE, :LPWSTR, :ptr, :ptr, :LPSTR, :DWORD, :ptr, :ptr, :ptr
D3DXCreateEffectFromResourceA proto WINAPI :ptr, :HMODULE, :LPSTR, :ptr, :ptr, :DWORD, :ptr, :ptr, :ptr
D3DXCreateEffectFromResourceW proto WINAPI :ptr, :HMODULE, :LPWSTR, :ptr, :ptr, :DWORD, :ptr, :ptr, :ptr
D3DXCreateEffectCompilerFromFileA proto WINAPI :LPSTR, :ptr, :ptr, :DWORD, :ptr, :ptr
D3DXCreateEffectCompilerFromFileW proto WINAPI :LPWSTR, :ptr, :ptr, :DWORD, :ptr, :ptr
D3DXCreateEffectCompilerFromResourceA proto WINAPI :HMODULE, :LPSTR, :ptr, :ptr, :DWORD, :ptr, :ptr
D3DXCreateEffectCompilerFromResourceW proto WINAPI :HMODULE, :LPWSTR, :ptr, :ptr, :DWORD, :ptr, :ptr
D3DXDisassembleEffect proto WINAPI :ptr, :BOOL, :ptr

endif
