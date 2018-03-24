ifndef _D3D9_H_
_D3D9_H_ equ <>
.xlist

ifndef DIRECT3D_VERSION
DIRECT3D_VERSION equ 0x0900
endif

if (DIRECT3D_VERSION GE 0x0900)

ifdef D3D_DEBUG_INFO
D3D_SDK_VERSION		equ (32 OR 0x80000000)
D3D9b_SDK_VERSION	equ (31 OR 0x80000000)
else
D3D_SDK_VERSION		equ 32
D3D9b_SDK_VERSION	equ 31
endif

include stdlib.inc
COM_NO_WINDOWS_H equ 1
include objbase.inc
include windows.inc
.xlist

if NOT defined(HMONITOR_DECLARED) AND (WINVER LT 0x0500)
HMONITOR_DECLARED equ 1
endif

D3DAPI	equ <WINAPI>

if defined( _WIN32 ) AND NOT defined( _NO_COM)

DEFINE_GUID(IID_IDirect3D9, 0x81bdcbca, 0x64d4, 0x426d, 0xae, 0x8d, 0xad, 0x1, 0x47, 0xf4, 0x27, 0x5c);
DEFINE_GUID(IID_IDirect3DDevice9, 0xd0223b96, 0xbf7a, 0x43fd, 0x92, 0xbd, 0xa4, 0x3b, 0xd, 0x82, 0xb9, 0xeb);
DEFINE_GUID(IID_IDirect3DResource9, 0x5eec05d, 0x8f7d, 0x4362, 0xb9, 0x99, 0xd1, 0xba, 0xf3, 0x57, 0xc7, 0x4);
DEFINE_GUID(IID_IDirect3DBaseTexture9, 0x580ca87e, 0x1d3c, 0x4d54, 0x99, 0x1d, 0xb7, 0xd3, 0xe3, 0xc2, 0x98, 0xce);
DEFINE_GUID(IID_IDirect3DTexture9, 0x85c31227, 0x3de5, 0x4f00, 0x9b, 0x3a, 0xf1, 0x1a, 0xc3, 0x8c, 0x18, 0xb5);
DEFINE_GUID(IID_IDirect3DCubeTexture9, 0xfff32f81, 0xd953, 0x473a, 0x92, 0x23, 0x93, 0xd6, 0x52, 0xab, 0xa9, 0x3f);
DEFINE_GUID(IID_IDirect3DVolumeTexture9, 0x2518526c, 0xe789, 0x4111, 0xa7, 0xb9, 0x47, 0xef, 0x32, 0x8d, 0x13, 0xe6);
DEFINE_GUID(IID_IDirect3DVertexBuffer9, 0xb64bb1b5, 0xfd70, 0x4df6, 0xbf, 0x91, 0x19, 0xd0, 0xa1, 0x24, 0x55, 0xe3);
DEFINE_GUID(IID_IDirect3DIndexBuffer9, 0x7c9dd65e, 0xd3f7, 0x4529, 0xac, 0xee, 0x78, 0x58, 0x30, 0xac, 0xde, 0x35);
DEFINE_GUID(IID_IDirect3DSurface9, 0xcfbaf3a, 0x9ff6, 0x429a, 0x99, 0xb3, 0xa2, 0x79, 0x6a, 0xf8, 0xb8, 0x9b);
DEFINE_GUID(IID_IDirect3DVolume9, 0x24f416e6, 0x1f67, 0x4aa7, 0xb8, 0x8e, 0xd3, 0x3f, 0x6f, 0x31, 0x28, 0xa1);
DEFINE_GUID(IID_IDirect3DSwapChain9, 0x794950f2, 0xadfc, 0x458a, 0x90, 0x5e, 0x10, 0xa1, 0xb, 0xb, 0x50, 0x3b);
DEFINE_GUID(IID_IDirect3DVertexDeclaration9, 0xdd13c59c, 0x36fa, 0x4098, 0xa8, 0xfb, 0xc7, 0xed, 0x39, 0xdc, 0x85, 0x46);
DEFINE_GUID(IID_IDirect3DVertexShader9, 0xefc5557e, 0x6265, 0x4613, 0x8a, 0x94, 0x43, 0x85, 0x78, 0x89, 0xeb, 0x36);
DEFINE_GUID(IID_IDirect3DPixelShader9, 0x6d3bdbdc, 0x5b02, 0x4415, 0xb8, 0x52, 0xce, 0x5e, 0x8b, 0xcc, 0xb2, 0x89);
DEFINE_GUID(IID_IDirect3DStateBlock9, 0xb07c4fe5, 0x310d, 0x4ba8, 0xa2, 0x3c, 0x4f, 0xf, 0x20, 0x6f, 0x21, 0x8b);
DEFINE_GUID(IID_IDirect3DQuery9, 0xd9771460, 0xa695, 0x4f26, 0xbb, 0xd3, 0x27, 0xb8, 0x40, 0xb5, 0x41, 0xcc);
DEFINE_GUID(IID_HelperName, 0xe4a36723, 0xfdfe, 0x4b22, 0xb1, 0x46, 0x3c, 0x4, 0xc0, 0x7f, 0x4c, 0xc8);

ifndef D3D_DISABLE_9EX

DEFINE_GUID(IID_IDirect3D9Ex, 0x02177241, 0x69FC, 0x400C, 0x8F, 0xF1, 0x93, 0xA4, 0x4D, 0xF6, 0x86, 0x1D);
DEFINE_GUID(IID_IDirect3DDevice9Ex, 0xb18b10ce, 0x2649, 0x405a, 0x87, 0xf, 0x95, 0xf7, 0x77, 0xd4, 0x31, 0x3a);
DEFINE_GUID(IID_IDirect3DSwapChain9Ex, 0x91886caf, 0x1c3d, 0x4d2e, 0xa0, 0xab, 0x3e, 0x4c, 0x7d, 0x8d, 0x33, 0x3);
DEFINE_GUID(IID_IDirect3D9ExOverlayExtension, 0x187aeb13, 0xaaf5, 0x4c59, 0x87, 0x6d, 0xe0, 0x59, 0x8, 0x8c, 0xd, 0xf8);
DEFINE_GUID(IID_IDirect3DDevice9Video, 0x26dc4561, 0xa1ee, 0x4ae7, 0x96, 0xda, 0x11, 0x8a, 0x36, 0xc0, 0xec, 0x95);
DEFINE_GUID(IID_IDirect3DAuthenticatedChannel9, 0xff24beee, 0xda21, 0x4beb, 0x98, 0xb5, 0xd2, 0xf8, 0x99, 0xf9, 0x8a, 0xf9);
DEFINE_GUID(IID_IDirect3DCryptoSession9, 0xfa0ab799, 0x7a9c, 0x48ca, 0x8c, 0x5b, 0x23, 0x7e, 0x71, 0xa5, 0x44, 0x34);

endif
endif

include <d3d9types.inc>
include <d3d9caps.inc>
.xlist
ifdef __PE__
option	dllimport:<d3d9>
else
includelib d3d9.lib
endif

;IDirect3D9 *
Direct3DCreate9 proto WINAPI SDKVersion:UINT


;int
D3DPERF_BeginEvent proto WINAPI \
		   col: D3DCOLOR,
	       wszName: LPCWSTR

;int
D3DPERF_EndEvent proto WINAPI
;void
D3DPERF_SetMarker proto WINAPI \
		   col: D3DCOLOR,
	       wszName: LPCWSTR

;void
D3DPERF_SetRegion proto WINAPI \
		   col: D3DCOLOR,
	       wszName: LPCWSTR

;BOOL
D3DPERF_QueryRepeatFrame proto WINAPI

;void
D3DPERF_SetOptions proto WINAPI \
	     dwOptions: DWORD

;DWORD
D3DPERF_GetStatus proto WINAPI


IDirect3D9Vtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	RegisterSoftwareDevice, :ptr
	STDMETHOD	GetAdapterCount
	STDMETHOD	GetAdapterIdentifier, :UINT, :DWORD, :ptr
	STDMETHOD	GetAdapterModeCount, :UINT, :D3DFORMAT
	STDMETHOD	EnumAdapterModes, :UINT, :D3DFORMAT, :UINT, :ptr
	STDMETHOD	GetAdapterDisplayMode, :UINT, :ptr
	STDMETHOD	CheckDeviceType, :UINT, :D3DDEVTYPE, :D3DFORMAT, :D3DFORMAT, :BOOL
	STDMETHOD	CheckDeviceFormat, :UINT, :D3DDEVTYPE, :D3DFORMAT, :DWORD, :D3DRESOURCETYPE, :D3DFORMAT
	STDMETHOD	CheckDeviceMultiSampleType, :UINT, :D3DDEVTYPE, :D3DFORMAT, :BOOL, :D3DMULTISAMPLE_TYPE, :ptr
	STDMETHOD	CheckDepthStencilMatch, :UINT, :D3DDEVTYPE, :D3DFORMAT, :D3DFORMAT, :D3DFORMAT
	STDMETHOD	CheckDeviceFormatConversion, :UINT, :D3DDEVTYPE, :D3DFORMAT, :D3DFORMAT
	STDMETHOD	GetDeviceCaps, :UINT, :D3DDEVTYPE, :ptr
	STDMETHOD	GetAdapterMonitor, :UINT
	STDMETHOD	CreateDevice, :UINT, :D3DDEVTYPE, :HWND, :DWORD, :ptr, :ptr
IDirect3D9Vtbl ends
IDirect3D9 struct
	lpVtbl		PVOID ?
IDirect3D9 ends
LPDIRECT3D9		typedef ptr IDirect3D9
PDIRECT3D9		typedef ptr IDirect3D9

IDirect3DDevice9Vtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	TestCooperativeLevel
	STDMETHOD	GetAvailableTextureMem
	STDMETHOD	EvictManagedResources
	STDMETHOD	GetDirect3D, :ptr
	STDMETHOD	GetDeviceCaps, :ptr
	STDMETHOD	GetDisplayMode, :UINT, :ptr
	STDMETHOD	GetCreationParameters, :ptr
	STDMETHOD	SetCursorProperties, :UINT, :UINT, :ptr
	STDMETHOD	SetCursorPosition, :SINT, :SINT, :DWORD
	STDMETHOD	ShowCursor, :BOOL
	STDMETHOD	CreateAdditionalSwapChain, :ptr, :ptr
	STDMETHOD	GetSwapChain, :UINT, :ptr
	STDMETHOD	GetNumberOfSwapChains
	STDMETHOD	Reset, :ptr
	STDMETHOD	Present, :ptr, :ptr, :HWND, :ptr
	STDMETHOD	GetBackBuffer, :UINT, :UINT, :D3DBACKBUFFER_TYPE, :ptr
	STDMETHOD	GetRasterStatus, :UINT, :ptr
	STDMETHOD	SetDialogBoxMode, :BOOL
	STDMETHOD	SetGammaRamp, :UINT, :DWORD, :ptr
	STDMETHOD	GetGammaRamp, :UINT, :ptr
	STDMETHOD	CreateTexture, :UINT, :UINT, :UINT, :DWORD, :D3DFORMAT, :D3DPOOL, :ptr, :ptr
	STDMETHOD	CreateVolumeTexture, :UINT, :UINT, :UINT, :UINT, :DWORD, :D3DFORMAT, :D3DPOOL, :ptr, :ptr
	STDMETHOD	CreateCubeTexture, :UINT, :UINT, :DWORD, :D3DFORMAT, :D3DPOOL, :ptr, :ptr
	STDMETHOD	CreateVertexBuffer, :UINT, :DWORD, :DWORD, :D3DPOOL, :ptr, :ptr
	STDMETHOD	CreateIndexBuffer, :UINT, :DWORD, :D3DFORMAT, :D3DPOOL, :ptr, :ptr
	STDMETHOD	CreateRenderTarget, :UINT, :UINT, :D3DFORMAT, :D3DMULTISAMPLE_TYPE, :DWORD, :BOOL, :ptr, :ptr
	STDMETHOD	CreateDepthStencilSurface, :UINT, :UINT, :D3DFORMAT, :D3DMULTISAMPLE_TYPE, :DWORD, :BOOL, :ptr, :ptr
	STDMETHOD	UpdateSurface, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	UpdateTexture, :ptr, :ptr
	STDMETHOD	GetRenderTargetData, :ptr, :ptr
	STDMETHOD	GetFrontBufferData, :UINT, :ptr
	STDMETHOD	StretchRect, :ptr, :ptr, :ptr, :ptr, :D3DTEXTUREFILTERTYPE
	STDMETHOD	ColorFill, :ptr, :ptr, :D3DCOLOR
	STDMETHOD	CreateOffscreenPlainSurface, :UINT, :UINT, :D3DFORMAT, :D3DPOOL, :ptr, :ptr
	STDMETHOD	SetRenderTarget, :DWORD, :ptr
	STDMETHOD	GetRenderTarget, :DWORD, :ptr
	STDMETHOD	SetDepthStencilSurface, :ptr
	STDMETHOD	GetDepthStencilSurface, :ptr
	STDMETHOD	BeginScene
	STDMETHOD	EndScene
	STDMETHOD	Clear, :DWORD, :ptr, :DWORD, :D3DCOLOR, :FLOAT, :DWORD
	STDMETHOD	SetTransform, :D3DTRANSFORMSTATETYPE, :ptr
	STDMETHOD	GetTransform, :D3DTRANSFORMSTATETYPE, :ptr
	STDMETHOD	MultiplyTransform, :D3DTRANSFORMSTATETYPE, :ptr
	STDMETHOD	SetViewport, :ptr
	STDMETHOD	GetViewport, :ptr
	STDMETHOD	SetMaterial, :ptr
	STDMETHOD	GetMaterial, :ptr
	STDMETHOD	SetLight, :DWORD, :ptr
	STDMETHOD	GetLight, :DWORD, :ptr
	STDMETHOD	LightEnable, :DWORD, :BOOL
	STDMETHOD	GetLightEnable, :DWORD, :ptr
	STDMETHOD	SetClipPlane, :DWORD, :ptr
	STDMETHOD	GetClipPlane, :DWORD, :ptr
	STDMETHOD	SetRenderState, :D3DRENDERSTATETYPE, :DWORD
	STDMETHOD	GetRenderState, :D3DRENDERSTATETYPE, :ptr
	STDMETHOD	CreateStateBlock, :D3DSTATEBLOCKTYPE, :ptr
	STDMETHOD	BeginStateBlock
	STDMETHOD	EndStateBlock, :ptr
	STDMETHOD	SetClipStatus, :ptr
	STDMETHOD	GetClipStatus, :ptr
	STDMETHOD	GetTexture, :DWORD, :ptr
	STDMETHOD	SetTexture, :DWORD, :ptr
	STDMETHOD	GetTextureStageState, :DWORD, :D3DTEXTURESTAGESTATETYPE, :ptr
	STDMETHOD	SetTextureStageState, :DWORD, :D3DTEXTURESTAGESTATETYPE, :DWORD
	STDMETHOD	GetSamplerState, :DWORD, :D3DSAMPLERSTATETYPE, :ptr
	STDMETHOD	SetSamplerState, :DWORD, :D3DSAMPLERSTATETYPE, :DWORD
	STDMETHOD	ValidateDevice, :ptr
	STDMETHOD	SetPaletteEntries, :UINT, :ptr
	STDMETHOD	GetPaletteEntries, :UINT, :ptr
	STDMETHOD	SetCurrentTexturePalette, :UINT
	STDMETHOD	GetCurrentTexturePalette, :ptr
	STDMETHOD	SetScissorRect, :ptr
	STDMETHOD	GetScissorRect, :ptr
	STDMETHOD	SetSoftwareVertexProcessing, :BOOL
	STDMETHOD	GetSoftwareVertexProcessing
	STDMETHOD	SetNPatchMode, :FLOAT
	STDMETHOD	GetNPatchMode
	STDMETHOD	DrawPrimitive, :D3DPRIMITIVETYPE, :UINT, :UINT
	STDMETHOD	DrawIndexedPrimitive, :D3DPRIMITIVETYPE, :SINT, :UINT, :UINT, :UINT, :UINT
	STDMETHOD	DrawPrimitiveUP, :D3DPRIMITIVETYPE, :UINT, :ptr, :UINT
	STDMETHOD	DrawIndexedPrimitiveUP, :D3DPRIMITIVETYPE, :UINT, :UINT, :UINT, :ptr, :D3DFORMAT, :ptr, :UINT
	STDMETHOD	ProcessVertices, :UINT, :UINT, :UINT, :ptr, :ptr, :DWORD
	STDMETHOD	CreateVertexDeclaration, :ptr, :ptr
	STDMETHOD	SetVertexDeclaration, :ptr
	STDMETHOD	GetVertexDeclaration, :ptr
	STDMETHOD	SetFVF, :DWORD
	STDMETHOD	GetFVF, :ptr
	STDMETHOD	CreateVertexShader, :ptr, :ptr
	STDMETHOD	SetVertexShader, :ptr
	STDMETHOD	GetVertexShader, :ptr
	STDMETHOD	SetVertexShaderConstantF, :UINT, :ptr, :UINT
	STDMETHOD	GetVertexShaderConstantF, :UINT, :ptr, :UINT
	STDMETHOD	SetVertexShaderConstantI, :UINT, :ptr, :UINT
	STDMETHOD	GetVertexShaderConstantI, :UINT, :ptr, :UINT
	STDMETHOD	SetVertexShaderConstantB, :UINT, :ptr, :UINT
	STDMETHOD	GetVertexShaderConstantB, :UINT, :ptr, :UINT
	STDMETHOD	SetStreamSource, :UINT, :ptr, :UINT, :UINT
	STDMETHOD	GetStreamSource, :UINT, :ptr, :ptr, :ptr
	STDMETHOD	SetStreamSourceFreq, :UINT, :UINT
	STDMETHOD	GetStreamSourceFreq, :UINT, :ptr
	STDMETHOD	SetIndices, :ptr
	STDMETHOD	GetIndices, :ptr
	STDMETHOD	CreatePixelShader, :ptr, :ptr
	STDMETHOD	SetPixelShader, :ptr
	STDMETHOD	GetPixelShader, :ptr
	STDMETHOD	SetPixelShaderConstantF, :UINT, :ptr, :UINT
	STDMETHOD	GetPixelShaderConstantF, :UINT, :ptr, :UINT
	STDMETHOD	SetPixelShaderConstantI, :UINT, :ptr, :UINT
	STDMETHOD	GetPixelShaderConstantI, :UINT, :ptr, :UINT
	STDMETHOD	SetPixelShaderConstantB, :UINT, :ptr, :UINT
	STDMETHOD	GetPixelShaderConstantB, :UINT, :ptr, :UINT
	STDMETHOD	DrawRectPatch, :UINT, :ptr, :ptr
	STDMETHOD	DrawTriPatch, :UINT, :ptr, :ptr
	STDMETHOD	DeletePatch, :UINT
	STDMETHOD	CreateQuery, :D3DQUERYTYPE, :ptr
IDirect3DDevice9Vtbl ends
IDirect3DDevice9 struct
	lpVtbl		PVOID ?
IDirect3DDevice9 ends
LPDIRECT3DDEVICE9	typedef ptr IDirect3DDevice9
PDIRECT3DDEVICE9	typedef ptr IDirect3DDevice9

IDirect3DStateBlock9Vtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetDevice, :ptr
	STDMETHOD	Capture
	STDMETHOD	Apply
IDirect3DStateBlock9Vtbl ends
IDirect3DStateBlock9 struct
	lpVtbl		PVOID ?
IDirect3DStateBlock9 ends
LPDIRECT3DSTATEBLOCK9	typedef ptr IDirect3DStateBlock9
PDIRECT3DSTATEBLOCK9	typedef ptr IDirect3DStateBlock9

IDirect3DSwapChain9Vtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Present, :ptr, :ptr, :HWND, :ptr, :DWORD
	STDMETHOD	GetFrontBufferData, :ptr
	STDMETHOD	GetBackBuffer, :UINT, :D3DBACKBUFFER_TYPE, :ptr
	STDMETHOD	GetRasterStatus, :ptr
	STDMETHOD	GetDisplayMode, :ptr
	STDMETHOD	GetDevice, :ptr
	STDMETHOD	GetPresentParameters, :ptr
IDirect3DSwapChain9Vtbl ends
IDirect3DSwapChain9 struct
	lpVtbl		PVOID ?
IDirect3DSwapChain9 ends
LPDIRECT3DSWAPCHAIN9	typedef ptr IDirect3DSwapChain9
PDIRECT3DSWAPCHAIN9	typedef ptr IDirect3DSwapChain9

IDirect3DResource9Vtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetDevice, :ptr
	STDMETHOD	SetPrivateData, :REFGUID, :ptr, :DWORD, :DWORD
	STDMETHOD	GetPrivateData, :REFGUID, :ptr, :ptr
	STDMETHOD	FreePrivateData, :REFGUID
	STDMETHOD	SetPriority, :DWORD
	STDMETHOD	GetPriority
	STDMETHOD	PreLoad
	STDMETHOD	GetType
IDirect3DResource9Vtbl ends
IDirect3DResource9 struct
	lpVtbl		PVOID ?
IDirect3DResource9 ends
LPDIRECT3DRESOURCE9	typedef ptr IDirect3DResource9
PDIRECT3DRESOURCE9	typedef ptr IDirect3DResource9

IDirect3DVertexDeclaration9Vtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetDevice, :ptr
	STDMETHOD	GetDeclaration, :ptr, :ptr
IDirect3DVertexDeclaration9Vtbl ends
IDirect3DVertexDeclaration9 struct
	lpVtbl		PVOID ?
IDirect3DVertexDeclaration9 ends
LPDIRECT3DVERTEXDECLARATION9 typedef ptr IDirect3DVertexDeclaration9
PDIRECT3DVERTEXDECLARATION9 typedef ptr IDirect3DVertexDeclaration9

IDirect3DVertexShader9Vtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetDevice, :ptr
	STDMETHOD	GetFunction, :ptr, :ptr
IDirect3DVertexShader9Vtbl ends
IDirect3DVertexShader9 struct
	lpVtbl		PVOID ?
IDirect3DVertexShader9 ends
LPDIRECT3DVERTEXSHADER9 typedef ptr IDirect3DVertexShader9
PDIRECT3DVERTEXSHADER9	typedef ptr IDirect3DVertexShader9

IDirect3DPixelShader9Vtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetDevice, :ptr
	STDMETHOD	GetFunction, :ptr, :ptr
IDirect3DPixelShader9Vtbl ends
IDirect3DPixelShader9 struct
	lpVtbl		PVOID ?
IDirect3DPixelShader9 ends
LPDIRECT3DPIXELSHADER9	typedef ptr IDirect3DPixelShader9
PDIRECT3DPIXELSHADER9	typedef ptr IDirect3DPixelShader9

IDirect3DBaseTexture9Vtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetDevice, :ptr
	STDMETHOD	SetPrivateData, :REFGUID, :ptr, :DWORD, :DWORD
	STDMETHOD	GetPrivateData, :REFGUID, :ptr, :ptr
	STDMETHOD	FreePrivateData, :REFGUID
	STDMETHOD	SetPriority, :DWORD
	STDMETHOD	GetPriority
	STDMETHOD	PreLoad
	STDMETHOD	GetType
	STDMETHOD	SetLOD, :DWORD
	STDMETHOD	GetLOD
	STDMETHOD	GetLevelCount
	STDMETHOD	SetAutoGenFilterType, :D3DTEXTUREFILTERTYPE
	STDMETHOD	GetAutoGenFilterType
	STDMETHOD	GenerateMipSubLevels
IDirect3DBaseTexture9Vtbl ends
IDirect3DBaseTexture9 struct
	lpVtbl		PVOID ?
IDirect3DBaseTexture9 ends
LPDIRECT3DBASETEXTURE9	typedef ptr IDirect3DBaseTexture9
PDIRECT3DBASETEXTURE9	typedef ptr IDirect3DBaseTexture9

IDirect3DTexture9Vtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetDevice, :ptr
	STDMETHOD	SetPrivateData, :REFGUID, :ptr, :DWORD, :DWORD
	STDMETHOD	GetPrivateData, :REFGUID, :ptr, :ptr
	STDMETHOD	FreePrivateData, :REFGUID
	STDMETHOD	SetPriority, :DWORD
	STDMETHOD	GetPriority
	STDMETHOD	PreLoad
	STDMETHOD	GetType
	STDMETHOD	SetLOD, :DWORD
	STDMETHOD	GetLOD
	STDMETHOD	GetLevelCount
	STDMETHOD	SetAutoGenFilterType, :D3DTEXTUREFILTERTYPE
	STDMETHOD	GetAutoGenFilterType
	STDMETHOD	GenerateMipSubLevels
	STDMETHOD	GetLevelDesc, :UINT, :ptr
	STDMETHOD	GetSurfaceLevel, :UINT, :ptr
	STDMETHOD	LockRect, :UINT, :ptr, :ptr, :DWORD
	STDMETHOD	UnlockRect, :UINT
	STDMETHOD	AddDirtyRect, :ptr
IDirect3DTexture9Vtbl ends
IDirect3DTexture9 struct
	lpVtbl		PVOID ?
IDirect3DTexture9 ends
LPDIRECT3DTEXTURE9	typedef ptr IDirect3DTexture9
PDIRECT3DTEXTURE9	typedef ptr IDirect3DTexture9

IDirect3DVolumeTexture9Vtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetDevice, :ptr
	STDMETHOD	SetPrivateData, :REFGUID, :ptr, :DWORD, :DWORD
	STDMETHOD	GetPrivateData, :REFGUID, :ptr, :ptr
	STDMETHOD	FreePrivateData, :REFGUID
	STDMETHOD	SetPriority, :DWORD
	STDMETHOD	GetPriority
	STDMETHOD	PreLoad
	STDMETHOD	GetType
	STDMETHOD	SetLOD, :DWORD
	STDMETHOD	GetLOD
	STDMETHOD	GetLevelCount
	STDMETHOD	SetAutoGenFilterType, :D3DTEXTUREFILTERTYPE
	STDMETHOD	GetAutoGenFilterType
	STDMETHOD	GenerateMipSubLevels
	STDMETHOD	GetLevelDesc, :UINT, :ptr
	STDMETHOD	GetVolumeLevel, :UINT, :ptr
	STDMETHOD	LockBox, :UINT, :ptr, :ptr, :DWORD
	STDMETHOD	UnlockBox, :UINT
	STDMETHOD	AddDirtyBox, :ptr
IDirect3DVolumeTexture9Vtbl ends
IDirect3DVolumeTexture9 struct
	lpVtbl		PVOID ?
IDirect3DVolumeTexture9 ends
LPDIRECT3DVOLUMETEXTURE9 typedef ptr IDirect3DVolumeTexture9
PDIRECT3DVOLUMETEXTURE9 typedef ptr IDirect3DVolumeTexture9

IDirect3DCubeTexture9Vtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetDevice, :ptr
	STDMETHOD	SetPrivateData, :REFGUID, :ptr, :DWORD, :DWORD
	STDMETHOD	GetPrivateData, :REFGUID, :ptr, :ptr
	STDMETHOD	FreePrivateData, :REFGUID
	STDMETHOD	SetPriority, :DWORD
	STDMETHOD	GetPriority
	STDMETHOD	PreLoad
	STDMETHOD	GetType
	STDMETHOD	SetLOD, :DWORD
	STDMETHOD	GetLOD
	STDMETHOD	GetLevelCount
	STDMETHOD	SetAutoGenFilterType, :D3DTEXTUREFILTERTYPE
	STDMETHOD	GetAutoGenFilterType
	STDMETHOD	GenerateMipSubLevels
	STDMETHOD	GetLevelDesc, :UINT, :ptr
	STDMETHOD	GetCubeMapSurface, :D3DCUBEMAP_FACES, :UINT, :ptr
	STDMETHOD	LockRect, :D3DCUBEMAP_FACES, :UINT, :ptr, :ptr, :DWORD
	STDMETHOD	UnlockRect, :D3DCUBEMAP_FACES, :UINT
	STDMETHOD	AddDirtyRect, :D3DCUBEMAP_FACES, :ptr
IDirect3DCubeTexture9Vtbl ends
IDirect3DCubeTexture9 struct
	lpVtbl		PVOID ?
IDirect3DCubeTexture9 ends
LPDIRECT3DCUBETEXTURE9	typedef ptr IDirect3DCubeTexture9
PDIRECT3DCUBETEXTURE9	typedef ptr IDirect3DCubeTexture9

IDirect3DVertexBuffer9Vtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetDevice, :ptr
	STDMETHOD	SetPrivateData, :REFGUID, :ptr, :DWORD, :DWORD
	STDMETHOD	GetPrivateData, :REFGUID, :ptr, :ptr
	STDMETHOD	FreePrivateData, :REFGUID
	STDMETHOD	SetPriority, :DWORD
	STDMETHOD	GetPriority
	STDMETHOD	PreLoad
	STDMETHOD	GetType
	STDMETHOD	_Lock, :UINT, :UINT, :ptr, :DWORD
	STDMETHOD	Unlock
	STDMETHOD	GetDesc, :ptr
IDirect3DVertexBuffer9Vtbl ends
IDirect3DVertexBuffer9 struct
	lpVtbl		PVOID ?
IDirect3DVertexBuffer9 ends
LPDIRECT3DVERTEXBUFFER9 typedef ptr IDirect3DVertexBuffer9
PDIRECT3DVERTEXBUFFER9	typedef ptr IDirect3DVertexBuffer9

IDirect3DIndexBuffer9Vtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetDevice, :ptr
	STDMETHOD	SetPrivateData, :REFGUID, :ptr, :DWORD, :DWORD
	STDMETHOD	GetPrivateData, :REFGUID, :ptr, :ptr
	STDMETHOD	FreePrivateData, :REFGUID
	STDMETHOD	SetPriority, :DWORD
	STDMETHOD	GetPriority
	STDMETHOD	PreLoad
	STDMETHOD	GetType
	STDMETHOD	_Lock, :UINT, :UINT, :ptr, :DWORD
	STDMETHOD	Unlock
	STDMETHOD	GetDesc, :ptr
IDirect3DIndexBuffer9Vtbl ends
IDirect3DIndexBuffer9 struct
	lpVtbl		PVOID ?
IDirect3DIndexBuffer9 ends
LPDIRECT3DINDEXBUFFER9	typedef ptr IDirect3DIndexBuffer9
PDIRECT3DINDEXBUFFER9	typedef ptr IDirect3DIndexBuffer9

IDirect3DSurface9Vtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetDevice, :ptr
	STDMETHOD	SetPrivateData, :REFGUID, :ptr, :DWORD, :DWORD
	STDMETHOD	GetPrivateData, :REFGUID, :ptr, :ptr
	STDMETHOD	FreePrivateData, :REFGUID
	STDMETHOD	SetPriority, :DWORD
	STDMETHOD	GetPriority
	STDMETHOD	PreLoad
	STDMETHOD	GetType
	STDMETHOD	GetContainer, :REFIID, :ptr
	STDMETHOD	GetDesc, :ptr
	STDMETHOD	LockRect, :ptr, :ptr, :DWORD
	STDMETHOD	UnlockRect
	STDMETHOD	GetDC, :ptr
	STDMETHOD	ReleaseDC, :HDC
IDirect3DSurface9Vtbl ends
IDirect3DSurface9 struct
	lpVtbl		PVOID ?
IDirect3DSurface9 ends
LPDIRECT3DSURFACE9	typedef ptr IDirect3DSurface9
PDIRECT3DSURFACE9	typedef ptr IDirect3DSurface9

IDirect3DVolume9Vtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetDevice, :ptr
	STDMETHOD	SetPrivateData, :REFGUID, :ptr, :DWORD, :DWORD
	STDMETHOD	GetPrivateData, :REFGUID, :ptr, :ptr
	STDMETHOD	FreePrivateData, :REFGUID
	STDMETHOD	GetContainer, :REFIID, :ptr
	STDMETHOD	GetDesc, :ptr
	STDMETHOD	LockBox, :ptr, :ptr, :DWORD
	STDMETHOD	UnlockBox
IDirect3DVolume9Vtbl ends
IDirect3DVolume9 struct
	lpVtbl		PVOID ?
IDirect3DVolume9 ends
LPDIRECT3DVOLUME9	typedef ptr IDirect3DVolume9
PDIRECT3DVOLUME9	typedef ptr IDirect3DVolume9

IDirect3DQuery9Vtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetDevice, :ptr
	STDMETHOD	GetType
	STDMETHOD	GetDataSize
	STDMETHOD	Issue, :DWORD
	STDMETHOD	GetData, :ptr, :DWORD, :DWORD
IDirect3DQuery9Vtbl ends
IDirect3DQuery9 struct
	lpVtbl		PVOID ?
IDirect3DQuery9 ends
LPDIRECT3DQUERY9	typedef ptr IDirect3DQuery9
PDIRECT3DQUERY9		typedef ptr IDirect3DQuery9

D3DSPD_IUNKNOWN		equ 0x00000001

D3DCREATE_FPU_PRESERVE	equ 0x00000002
D3DCREATE_MULTITHREADED equ 0x00000004

D3DCREATE_PUREDEVICE	equ 0x00000010
D3DCREATE_SOFTWARE_VERTEXPROCESSING equ 0x00000020
D3DCREATE_HARDWARE_VERTEXPROCESSING equ 0x00000040
D3DCREATE_MIXED_VERTEXPROCESSING equ 0x00000080

D3DCREATE_DISABLE_DRIVER_MANAGEMENT equ 0x00000100
D3DCREATE_ADAPTERGROUP_DEVICE equ 0x00000200
D3DCREATE_DISABLE_DRIVER_MANAGEMENT_EX equ 0x00000400

D3DCREATE_NOWINDOWCHANGES equ 0x00000800

ifndef D3D_DISABLE_9EX
D3DCREATE_DISABLE_PSGP_THREADING equ 0x00002000
D3DCREATE_ENABLE_PRESENTSTATS equ 0x00004000
D3DCREATE_DISABLE_PRINTSCREEN equ 0x00008000
D3DCREATE_SCREENSAVER	equ 0x10000000
endif

D3DADAPTER_DEFAULT	equ 0

D3DENUM_WHQL_LEVEL	equ 0x00000002

ifndef D3D_DISABLE_9EX
D3DENUM_NO_DRIVERVERSION equ 0x00000004
endif

D3DPRESENT_BACK_BUFFERS_MAX equ 3

ifndef D3D_DISABLE_9EX
D3DPRESENT_BACK_BUFFERS_MAX_EX equ 30
endif

D3DSGR_NO_CALIBRATION	equ 0x00000000
D3DSGR_CALIBRATE	equ 0x00000001

D3DCURSOR_IMMEDIATE_UPDATE equ 0x00000001

D3DPRESENT_DONOTWAIT	equ 0x00000001
D3DPRESENT_LINEAR_CONTENT equ 0x00000002

ifndef D3D_DISABLE_9EX

D3DPRESENT_DONOTFLIP		equ 0x00000004
D3DPRESENT_FLIPRESTART		equ 0x00000008
D3DPRESENT_VIDEO_RESTRICT_TO_MONITOR equ 0x00000010
D3DPRESENT_UPDATEOVERLAYONLY	equ 0x00000020
D3DPRESENT_HIDEOVERLAY		equ 0x00000040
D3DPRESENT_UPDATECOLORKEY	equ 0x00000080
D3DPRESENT_FORCEIMMEDIATE	equ 0x00000100

endif

_FACD3D			equ 0x876
MAKE_D3DHRESULT macro code
	exitm<MAKE_HRESULT( 1, _FACD3D, code )>
	endm
MAKE_D3DSTATUS macro code
	exitm<MAKE_HRESULT( 0, _FACD3D, code )>
	endm

D3D_OK			equ S_OK

D3DERR_WRONGTEXTUREFORMAT		equ MAKE_D3DHRESULT(2072)
D3DERR_UNSUPPORTEDCOLOROPERATION	equ MAKE_D3DHRESULT(2073)
D3DERR_UNSUPPORTEDCOLORARG		equ MAKE_D3DHRESULT(2074)
D3DERR_UNSUPPORTEDALPHAOPERATION	equ MAKE_D3DHRESULT(2075)
D3DERR_UNSUPPORTEDALPHAARG		equ MAKE_D3DHRESULT(2076)
D3DERR_TOOMANYOPERATIONS		equ MAKE_D3DHRESULT(2077)
D3DERR_CONFLICTINGTEXTUREFILTER		equ MAKE_D3DHRESULT(2078)
D3DERR_UNSUPPORTEDFACTORVALUE		equ MAKE_D3DHRESULT(2079)
D3DERR_CONFLICTINGRENDERSTATE		equ MAKE_D3DHRESULT(2081)
D3DERR_UNSUPPORTEDTEXTUREFILTER		equ MAKE_D3DHRESULT(2082)
D3DERR_CONFLICTINGTEXTUREPALETTE	equ MAKE_D3DHRESULT(2086)
D3DERR_DRIVERINTERNALERROR		equ MAKE_D3DHRESULT(2087)

D3DERR_NOTFOUND				equ MAKE_D3DHRESULT(2150)
D3DERR_MOREDATA				equ MAKE_D3DHRESULT(2151)
D3DERR_DEVICELOST			equ MAKE_D3DHRESULT(2152)
D3DERR_DEVICENOTRESET			equ MAKE_D3DHRESULT(2153)
D3DERR_NOTAVAILABLE			equ MAKE_D3DHRESULT(2154)
D3DERR_OUTOFVIDEOMEMORY			equ MAKE_D3DHRESULT(380)
D3DERR_INVALIDDEVICE			equ MAKE_D3DHRESULT(2155)
D3DERR_INVALIDCALL			equ MAKE_D3DHRESULT(2156)
D3DERR_DRIVERINVALIDCALL		equ MAKE_D3DHRESULT(2157)
D3DERR_WASSTILLDRAWING			equ MAKE_D3DHRESULT(540)
D3DOK_NOAUTOGEN				equ MAKE_D3DSTATUS(2159)

ifndef D3D_DISABLE_9EX


D3DERR_DEVICEREMOVED			equ MAKE_D3DHRESULT(2160)
S_NOT_RESIDENT				equ MAKE_D3DSTATUS(2165)
S_RESIDENT_IN_SHARED_MEMORY		equ MAKE_D3DSTATUS(2166)
S_PRESENT_MODE_CHANGED			equ MAKE_D3DSTATUS(2167)
S_PRESENT_OCCLUDED			equ MAKE_D3DSTATUS(2168)
D3DERR_DEVICEHUNG			equ MAKE_D3DHRESULT(2164)
D3DERR_UNSUPPORTEDOVERLAY		equ MAKE_D3DHRESULT(2171)
D3DERR_UNSUPPORTEDOVERLAYFORMAT		equ MAKE_D3DHRESULT(2172)
D3DERR_CANNOTPROTECTCONTENT		equ MAKE_D3DHRESULT(2173)
D3DERR_UNSUPPORTEDCRYPTO		equ MAKE_D3DHRESULT(2174)
D3DERR_PRESENT_STATISTICS_DISJOINT	equ MAKE_D3DHRESULT(2180)


;HRESULT
Direct3DCreate9Ex proto WINAPI \
	    SDKVersion: UINT,
		      : ptr ptr IDirect3D9Ex


IDirect3D9ExVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetAdapterCount
	STDMETHOD	GetAdapterIdentifier, :UINT, :DWORD, :ptr
	STDMETHOD	GetAdapterModeCount, :UINT, :D3DFORMAT
	STDMETHOD	EnumAdapterModes, :UINT, :D3DFORMAT, :UINT, :ptr
	STDMETHOD	GetAdapterDisplayMode, :UINT, :ptr
	STDMETHOD	CheckDeviceType, :UINT, :D3DDEVTYPE, :D3DFORMAT, :D3DFORMAT, :BOOL
	STDMETHOD	CheckDeviceFormat, :UINT, :D3DDEVTYPE, :D3DFORMAT, :DWORD, :D3DRESOURCETYPE, :D3DFORMAT
	STDMETHOD	CheckDeviceMultiSampleType, :UINT, :D3DDEVTYPE, :D3DFORMAT, :BOOL, :D3DMULTISAMPLE_TYPE, :ptr
	STDMETHOD	CheckDepthStencilMatch, :UINT, :D3DDEVTYPE, :D3DFORMAT, :D3DFORMAT, :D3DFORMAT
	STDMETHOD	CheckDeviceFormatConversion, :UINT, :D3DDEVTYPE, :D3DFORMAT, :D3DFORMAT
	STDMETHOD	GetDeviceCaps, :UINT, :D3DDEVTYPE, :ptr
	STDMETHOD	GetAdapterMonitor, :UINT
	STDMETHOD	CreateDevice, :UINT, :D3DDEVTYPE, :HWND, :DWORD, :ptr, :ptr
	STDMETHOD	GetAdapterModeCountEx, :UINT, :ptr
	STDMETHOD	EnumAdapterModesEx, :UINT, :ptr, :UINT, :ptr
	STDMETHOD	GetAdapterDisplayModeEx, :UINT, :ptr, :ptr
	STDMETHOD	CreateDeviceEx, :UINT, :D3DDEVTYPE, :HWND, :DWORD, :ptr, :ptr, :ptr
	STDMETHOD	GetAdapterLUID, :UINT, :ptr
IDirect3D9ExVtbl ends
IDirect3D9Ex struct
	lpVtbl		PVOID ?
IDirect3D9Ex ends
LPDIRECT3D9EX		typedef ptr IDirect3D9Ex
PDIRECT3D9EX		typedef ptr IDirect3D9Ex

IDirect3DDevice9ExVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	TestCooperativeLevel
	STDMETHOD	GetAvailableTextureMem
	STDMETHOD	EvictManagedResources
	STDMETHOD	GetDirect3D, :ptr
	STDMETHOD	GetDeviceCaps, :ptr
	STDMETHOD	GetDisplayMode, :UINT, :ptr
	STDMETHOD	GetCreationParameters, :ptr
	STDMETHOD	SetCursorProperties, :UINT, :UINT, :ptr
	STDMETHOD	SetCursorPosition, :SINT, :SINT, :DWORD
	STDMETHOD	ShowCursor, :BOOL
	STDMETHOD	CreateAdditionalSwapChain, :ptr, :ptr
	STDMETHOD	GetSwapChain, :UINT, :ptr
	STDMETHOD	GetNumberOfSwapChains
	STDMETHOD	Reset, :ptr
	STDMETHOD	Present, :ptr, :ptr, :HWND, :ptr
	STDMETHOD	GetBackBuffer, :UINT, :UINT, :D3DBACKBUFFER_TYPE, :ptr
	STDMETHOD	GetRasterStatus, :UINT, :ptr
	STDMETHOD	SetDialogBoxMode, :BOOL
	STDMETHOD	SetGammaRamp, :UINT, :DWORD, :ptr
	STDMETHOD	GetGammaRamp, :UINT, :ptr
	STDMETHOD	CreateTexture, :UINT, :UINT, :UINT, :DWORD, :D3DFORMAT, :D3DPOOL, :ptr, :ptr
	STDMETHOD	CreateVolumeTexture, :UINT, :UINT, :UINT, :UINT, :DWORD, :D3DFORMAT, :D3DPOOL, :ptr, :ptr
	STDMETHOD	CreateCubeTexture, :UINT, :UINT, :DWORD, :D3DFORMAT, :D3DPOOL, :ptr, :ptr
	STDMETHOD	CreateVertexBuffer, :UINT, :DWORD, :DWORD, :D3DPOOL, :ptr, :ptr
	STDMETHOD	CreateIndexBuffer, :UINT, :DWORD, :D3DFORMAT, :D3DPOOL, :ptr, :ptr
	STDMETHOD	CreateRenderTarget, :UINT, :UINT, :D3DFORMAT, :D3DMULTISAMPLE_TYPE, :DWORD, :BOOL, :ptr, :ptr
	STDMETHOD	CreateDepthStencilSurface, :UINT, :UINT, :D3DFORMAT, :D3DMULTISAMPLE_TYPE, :DWORD, :BOOL, :ptr, :ptr
	STDMETHOD	UpdateSurface, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	UpdateTexture, :ptr, :ptr
	STDMETHOD	GetRenderTargetData, :ptr, :ptr
	STDMETHOD	GetFrontBufferData, :UINT, :ptr
	STDMETHOD	StretchRect, :ptr, :ptr, :ptr, :ptr, :D3DTEXTUREFILTERTYPE
	STDMETHOD	ColorFill, :ptr, :ptr, :D3DCOLOR
	STDMETHOD	CreateOffscreenPlainSurface, :UINT, :UINT, :D3DFORMAT, :D3DPOOL, :ptr, :ptr
	STDMETHOD	SetRenderTarget, :DWORD, :ptr
	STDMETHOD	GetRenderTarget, :DWORD, :ptr
	STDMETHOD	SetDepthStencilSurface, :ptr
	STDMETHOD	GetDepthStencilSurface, :ptr
	STDMETHOD	BeginScene
	STDMETHOD	EndScene
	STDMETHOD	Clear, :DWORD, :ptr, :DWORD, :D3DCOLOR, :FLOAT, :DWORD
	STDMETHOD	SetTransform, :D3DTRANSFORMSTATETYPE, :ptr
	STDMETHOD	GetTransform, :D3DTRANSFORMSTATETYPE, :ptr
	STDMETHOD	MultiplyTransform, :D3DTRANSFORMSTATETYPE, :ptr
	STDMETHOD	SetViewport, :ptr
	STDMETHOD	GetViewport, :ptr
	STDMETHOD	SetMaterial, :ptr
	STDMETHOD	GetMaterial, :ptr
	STDMETHOD	SetLight, :DWORD, :ptr
	STDMETHOD	GetLight, :DWORD, :ptr
	STDMETHOD	LightEnable, :DWORD, :BOOL
	STDMETHOD	GetLightEnable, :DWORD, :ptr
	STDMETHOD	SetClipPlane, :DWORD, :ptr
	STDMETHOD	GetClipPlane, :DWORD, :ptr
	STDMETHOD	SetRenderState, :D3DRENDERSTATETYPE, :DWORD
	STDMETHOD	GetRenderState, :D3DRENDERSTATETYPE, :ptr
	STDMETHOD	CreateStateBlock, :D3DSTATEBLOCKTYPE, :ptr
	STDMETHOD	BeginStateBlock
	STDMETHOD	EndStateBlock, :ptr
	STDMETHOD	SetClipStatus, :ptr
	STDMETHOD	GetClipStatus, :ptr
	STDMETHOD	GetTexture, :DWORD, :ptr
	STDMETHOD	SetTexture, :DWORD, :ptr
	STDMETHOD	GetTextureStageState, :DWORD, :D3DTEXTURESTAGESTATETYPE, :ptr
	STDMETHOD	SetTextureStageState, :DWORD, :D3DTEXTURESTAGESTATETYPE, :DWORD
	STDMETHOD	GetSamplerState, :DWORD, :D3DSAMPLERSTATETYPE, :ptr
	STDMETHOD	SetSamplerState, :DWORD, :D3DSAMPLERSTATETYPE, :DWORD
	STDMETHOD	ValidateDevice, :ptr
	STDMETHOD	SetPaletteEntries, :UINT, :ptr
	STDMETHOD	GetPaletteEntries, :UINT, :ptr
	STDMETHOD	SetCurrentTexturePalette, :UINT
	STDMETHOD	GetCurrentTexturePalette, :ptr
	STDMETHOD	SetScissorRect, :ptr
	STDMETHOD	GetScissorRect, :ptr
	STDMETHOD	SetSoftwareVertexProcessing, :BOOL
	STDMETHOD	GetSoftwareVertexProcessing
	STDMETHOD	SetNPatchMode, :FLOAT
	STDMETHOD	GetNPatchMode
	STDMETHOD	DrawPrimitive, :D3DPRIMITIVETYPE, :UINT, :UINT
	STDMETHOD	DrawIndexedPrimitive, :D3DPRIMITIVETYPE, :SINT, :UINT, :UINT, :UINT, :UINT
	STDMETHOD	DrawPrimitiveUP, :D3DPRIMITIVETYPE, :UINT, :ptr, :UINT
	STDMETHOD	DrawIndexedPrimitiveUP, :D3DPRIMITIVETYPE, :UINT, :UINT, :UINT, :ptr, :D3DFORMAT, :ptr, :UINT
	STDMETHOD	ProcessVertices, :UINT, :UINT, :UINT, :ptr, :ptr, :DWORD
	STDMETHOD	CreateVertexDeclaration, :ptr, :ptr
	STDMETHOD	SetVertexDeclaration, :ptr
	STDMETHOD	GetVertexDeclaration, :ptr
	STDMETHOD	SetFVF, :DWORD
	STDMETHOD	GetFVF, :ptr
	STDMETHOD	CreateVertexShader, :ptr, :ptr
	STDMETHOD	SetVertexShader, :ptr
	STDMETHOD	GetVertexShader, :ptr
	STDMETHOD	SetVertexShaderConstantF, :UINT, :ptr, :UINT
	STDMETHOD	GetVertexShaderConstantF, :UINT, :ptr, :UINT
	STDMETHOD	SetVertexShaderConstantI, :UINT, :ptr, :UINT
	STDMETHOD	GetVertexShaderConstantI, :UINT, :ptr, :UINT
	STDMETHOD	SetVertexShaderConstantB, :UINT, :ptr, :UINT
	STDMETHOD	GetVertexShaderConstantB, :UINT, :ptr, :UINT
	STDMETHOD	SetStreamSource, :UINT, :ptr, :UINT, :UINT
	STDMETHOD	GetStreamSource, :UINT, :ptr, :ptr, :ptr
	STDMETHOD	SetStreamSourceFreq, :UINT, :UINT
	STDMETHOD	GetStreamSourceFreq, :UINT, :ptr
	STDMETHOD	SetIndices, :ptr
	STDMETHOD	GetIndices, :ptr
	STDMETHOD	CreatePixelShader, :ptr, :ptr
	STDMETHOD	SetPixelShader, :ptr
	STDMETHOD	GetPixelShader, :ptr
	STDMETHOD	SetPixelShaderConstantF, :UINT, :ptr, :UINT
	STDMETHOD	GetPixelShaderConstantF, :UINT, :ptr, :UINT
	STDMETHOD	SetPixelShaderConstantI, :UINT, :ptr, :UINT
	STDMETHOD	GetPixelShaderConstantI, :UINT, :ptr, :UINT
	STDMETHOD	SetPixelShaderConstantB, :UINT, :ptr, :UINT
	STDMETHOD	GetPixelShaderConstantB, :UINT, :ptr, :UINT
	STDMETHOD	DrawRectPatch, :UINT, :ptr, :ptr
	STDMETHOD	DrawTriPatch, :UINT, :ptr, :ptr
	STDMETHOD	DeletePatch, :UINT
	STDMETHOD	CreateQuery, :D3DQUERYTYPE, :ptr
	STDMETHOD	SetConvolutionMonoKernel, :UINT, :UINT, :ptr, :ptr
	STDMETHOD	ComposeRects, :ptr, :ptr, :ptr, :UINT, :ptr, :D3DCOMPOSERECTSOP, :SINT, :SINT
	STDMETHOD	PresentEx, :ptr, :ptr, :HWND, :ptr, :DWORD
	STDMETHOD	GetGPUThreadPriority, :ptr
	STDMETHOD	SetGPUThreadPriority, :SINT
	STDMETHOD	WaitForVBlank, :UINT
	STDMETHOD	CheckResourceResidency, :ptr, :UINT
	STDMETHOD	SetMaximumFrameLatency, :UINT
	STDMETHOD	GetMaximumFrameLatency, :ptr
	STDMETHOD	CheckDeviceState, :HWND
	STDMETHOD	CreateRenderTargetEx, :UINT, :UINT, :D3DFORMAT, :D3DMULTISAMPLE_TYPE, :DWORD, :BOOL, :ptr, :ptr, :DWORD
	STDMETHOD	CreateOffscreenPlainSurfaceEx, :UINT, :UINT, :D3DFORMAT, :D3DPOOL, :ptr, :ptr, :DWORD
	STDMETHOD	CreateDepthStencilSurfaceEx, :UINT, :UINT, :D3DFORMAT, :D3DMULTISAMPLE_TYPE, :DWORD, :ptr, :ptr, :DWORD
	STDMETHOD	ResetEx, :ptr, :ptr
	STDMETHOD	GetDisplayModeEx, :UINT, :ptr, :ptr
IDirect3DDevice9ExVtbl ends
IDirect3DDevice9Ex struct
	lpVtbl		PVOID ?
IDirect3DDevice9Ex ends
LPDIRECT3DDEVICE9EX	typedef ptr IDirect3DDevice9Ex
PDIRECT3DDEVICE9EX	typedef ptr IDirect3DDevice9Ex

IDirect3DSwapChain9ExVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Present, :ptr, :ptr, :HWND, :ptr, :DWORD
	STDMETHOD	GetFrontBufferData, :ptr
	STDMETHOD	GetBackBuffer, :UINT, :D3DBACKBUFFER_TYPE, :ptr
	STDMETHOD	GetRasterStatus, :ptr
	STDMETHOD	GetDisplayMode, :ptr
	STDMETHOD	GetDevice, :ptr
	STDMETHOD	GetPresentParameters, :ptr
	STDMETHOD	GetLastPresentCount, :ptr
	STDMETHOD	GetPresentStats, :ptr
	STDMETHOD	GetDisplayModeEx, :ptr, :ptr
IDirect3DSwapChain9ExVtbl ends
IDirect3DSwapChain9Ex struct
	lpVtbl		PVOID ?
IDirect3DSwapChain9Ex ends
LPDIRECT3DSWAPCHAIN9EX	typedef ptr IDirect3DSwapChain9Ex
PDIRECT3DSWAPCHAIN9EX	typedef ptr IDirect3DSwapChain9Ex

endif ; ifndef D3D_DISABLE_9EX

IDirect3D9ExOverlayExtensionVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	CheckDeviceOverlayType, :UINT, :D3DDEVTYPE, :UINT, :UINT, :D3DFORMAT, :ptr, :D3DDISPLAYROTATION, :ptr
IDirect3D9ExOverlayExtensionVtbl ends
IDirect3D9ExOverlayExtension struct
	lpVtbl		PVOID ?
IDirect3D9ExOverlayExtension ends
LPDIRECT3D9EXOVERLAYEXTENSION typedef ptr IDirect3D9ExOverlayExtension
PDIRECT3D9EXOVERLAYEXTENSION  typedef ptr IDirect3D9ExOverlayExtension

IDirect3DDevice9VideoVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetContentProtectionCaps, :ptr, :ptr, :ptr
	STDMETHOD	CreateAuthenticatedChannel, :D3DAUTHENTICATEDCHANNELTYPE, :ptr, :ptr
	STDMETHOD	CreateCryptoSession, :ptr, :ptr, :ptr, :ptr
IDirect3DDevice9VideoVtbl ends
IDirect3DDevice9Video struct
	lpVtbl		PVOID ?
IDirect3DDevice9Video ends
LPDIRECT3DDEVICE9VIDEO	typedef ptr IDirect3DDevice9Video
PDIRECT3DDEVICE9VIDEO	typedef ptr IDirect3DDevice9Video

IDirect3DAuthenticatedChannel9Vtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetCertificateSize, :ptr
	STDMETHOD	GetCertificate, :UINT, :ptr
	STDMETHOD	NegotiateKeyExchange, :UINT, :ptr
	STDMETHOD	Query, :UINT, :ptr, :UINT, :ptr
	STDMETHOD	Configure, :UINT, :ptr, :ptr
IDirect3DAuthenticatedChannel9Vtbl ends
IDirect3DAuthenticatedChannel9 struct
	lpVtbl		PVOID ?
IDirect3DAuthenticatedChannel9 ends
LPDIRECT3DAUTHENTICATEDCHANNEL9 typedef ptr IDirect3DAuthenticatedChannel9
PDIRECT3DAUTHENTICATEDCHANNEL9	typedef ptr IDirect3DAuthenticatedChannel9


IDirect3DCryptoSession9Vtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetCertificateSize, :ptr
	STDMETHOD	GetCertificate, :UINT, :ptr
	STDMETHOD	NegotiateKeyExchange, :UINT, :ptr
	STDMETHOD	EncryptionBlt, :ptr, :ptr, :UINT, :ptr
	STDMETHOD	DecryptionBlt, :ptr, :ptr, :UINT, :ptr, :ptr, :ptr
	STDMETHOD	GetSurfacePitch, :ptr, :ptr
	STDMETHOD	StartSessionKeyRefresh, :ptr, :UINT
	STDMETHOD	FinishSessionKeyRefresh
	STDMETHOD	GetEncryptionBltKey, :ptr, :UINT
IDirect3DCryptoSession9Vtbl ends
IDirect3DCryptoSession9 struct
	lpVtbl		PVOID ?
IDirect3DCryptoSession9 ends
LPDIRECT3DCRYPTOSESSION9 typedef ptr IDirect3DCryptoSession9
PDIRECT3DCRYPTOSESSION9 typedef ptr IDirect3DCryptoSession9

endif
.list
endif
