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


.comdef IDirect3D9
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    RegisterSoftwareDevice proc :ptr
    GetAdapterCount	proc
    GetAdapterIdentifier proc :UINT, :DWORD, :ptr
    GetAdapterModeCount proc :UINT, :D3DFORMAT
    EnumAdapterModes	proc :UINT, :D3DFORMAT, :UINT, :ptr
    GetAdapterDisplayMode proc :UINT, :ptr
    CheckDeviceType	proc :UINT, :D3DDEVTYPE, :D3DFORMAT, :D3DFORMAT, :BOOL
    CheckDeviceFormat	proc :UINT, :D3DDEVTYPE, :D3DFORMAT, :DWORD, :D3DRESOURCETYPE, :D3DFORMAT
    CheckDeviceMultiSampleType proc :UINT, :D3DDEVTYPE, :D3DFORMAT, :BOOL, :D3DMULTISAMPLE_TYPE, :ptr
    CheckDepthStencilMatch proc :UINT, :D3DDEVTYPE, :D3DFORMAT, :D3DFORMAT, :D3DFORMAT
    CheckDeviceFormatConversion proc :UINT, :D3DDEVTYPE, :D3DFORMAT, :D3DFORMAT
    GetDeviceCaps	proc :UINT, :D3DDEVTYPE, :ptr
    GetAdapterMonitor	proc :UINT
    CreateDevice	proc :UINT, :D3DDEVTYPE, :HWND, :DWORD, :ptr, :ptr
    .ends
LPDIRECT3D9		typedef ptr IDirect3D9
PDIRECT3D9		typedef ptr IDirect3D9

.comdef IDirect3DDevice9
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    TestCooperativeLevel proc
    GetAvailableTextureMem proc
    EvictManagedResources proc
    GetDirect3D		proc :ptr
    GetDeviceCaps	proc :ptr
    GetDisplayMode	proc :UINT, :ptr
    GetCreationParameters proc :ptr
    SetCursorProperties proc :UINT, :UINT, :ptr
    SetCursorPosition	proc :SINT, :SINT, :DWORD
    ShowCursor		proc :BOOL
    CreateAdditionalSwapChain proc :ptr, :ptr
    GetSwapChain	proc :UINT, :ptr
    GetNumberOfSwapChains proc
    Reset		proc :ptr
    Present		proc :ptr, :ptr, :HWND, :ptr
    GetBackBuffer	proc :UINT, :UINT, :D3DBACKBUFFER_TYPE, :ptr
    GetRasterStatus	proc :UINT, :ptr
    SetDialogBoxMode	proc :BOOL
    SetGammaRamp	proc :UINT, :DWORD, :ptr
    GetGammaRamp	proc :UINT, :ptr
    CreateTexture	proc :UINT, :UINT, :UINT, :DWORD, :D3DFORMAT, :D3DPOOL, :ptr, :ptr
    CreateVolumeTexture proc :UINT, :UINT, :UINT, :UINT, :DWORD, :D3DFORMAT, :D3DPOOL, :ptr, :ptr
    CreateCubeTexture	proc :UINT, :UINT, :DWORD, :D3DFORMAT, :D3DPOOL, :ptr, :ptr
    CreateVertexBuffer	proc :UINT, :DWORD, :DWORD, :D3DPOOL, :ptr, :ptr
    CreateIndexBuffer	proc :UINT, :DWORD, :D3DFORMAT, :D3DPOOL, :ptr, :ptr
    CreateRenderTarget	proc :UINT, :UINT, :D3DFORMAT, :D3DMULTISAMPLE_TYPE, :DWORD, :BOOL, :ptr, :ptr
    CreateDepthStencilSurface proc :UINT, :UINT, :D3DFORMAT, :D3DMULTISAMPLE_TYPE, :DWORD, :BOOL, :ptr, :ptr
    UpdateSurface	proc :ptr, :ptr, :ptr, :ptr
    UpdateTexture	proc :ptr, :ptr
    GetRenderTargetData proc :ptr, :ptr
    GetFrontBufferData	proc :UINT, :ptr
    StretchRect		proc :ptr, :ptr, :ptr, :ptr, :D3DTEXTUREFILTERTYPE
    ColorFill		proc :ptr, :ptr, :D3DCOLOR
    CreateOffscreenPlainSurface proc :UINT, :UINT, :D3DFORMAT, :D3DPOOL, :ptr, :ptr
    SetRenderTarget	proc :DWORD, :ptr
    GetRenderTarget	proc :DWORD, :ptr
    SetDepthStencilSurface proc :ptr
    GetDepthStencilSurface proc :ptr
    BeginScene		proc
    EndScene		proc
    Clear		proc :DWORD, :ptr, :DWORD, :D3DCOLOR, :FLOAT, :DWORD
    SetTransform	proc :D3DTRANSFORMSTATETYPE, :ptr
    GetTransform	proc :D3DTRANSFORMSTATETYPE, :ptr
    MultiplyTransform	proc :D3DTRANSFORMSTATETYPE, :ptr
    SetViewport		proc :ptr
    GetViewport		proc :ptr
    SetMaterial		proc :ptr
    GetMaterial		proc :ptr
    SetLight		proc :DWORD, :ptr
    GetLight		proc :DWORD, :ptr
    LightEnable		proc :DWORD, :BOOL
    GetLightEnable	proc :DWORD, :ptr
    SetClipPlane	proc :DWORD, :ptr
    GetClipPlane	proc :DWORD, :ptr
    SetRenderState	proc :D3DRENDERSTATETYPE, :DWORD
    GetRenderState	proc :D3DRENDERSTATETYPE, :ptr
    CreateStateBlock	proc :D3DSTATEBLOCKTYPE, :ptr
    BeginStateBlock	proc
    EndStateBlock	proc :ptr
    SetClipStatus	proc :ptr
    GetClipStatus	proc :ptr
    GetTexture		proc :DWORD, :ptr
    SetTexture		proc :DWORD, :ptr
    GetTextureStageState proc :DWORD, :D3DTEXTURESTAGESTATETYPE, :ptr
    SetTextureStageState proc :DWORD, :D3DTEXTURESTAGESTATETYPE, :DWORD
    GetSamplerState	proc :DWORD, :D3DSAMPLERSTATETYPE, :ptr
    SetSamplerState	proc :DWORD, :D3DSAMPLERSTATETYPE, :DWORD
    ValidateDevice	proc :ptr
    SetPaletteEntries	proc :UINT, :ptr
    GetPaletteEntries	proc :UINT, :ptr
    SetCurrentTexturePalette proc :UINT
    GetCurrentTexturePalette proc :ptr
    SetScissorRect	proc :ptr
    GetScissorRect	proc :ptr
    SetSoftwareVertexProcessing proc :BOOL
    GetSoftwareVertexProcessing proc
    SetNPatchMode	proc :FLOAT
    GetNPatchMode	proc
    DrawPrimitive	proc :D3DPRIMITIVETYPE, :UINT, :UINT
    DrawIndexedPrimitive proc :D3DPRIMITIVETYPE, :SINT, :UINT, :UINT, :UINT, :UINT
    DrawPrimitiveUP	proc :D3DPRIMITIVETYPE, :UINT, :ptr, :UINT
    DrawIndexedPrimitiveUP proc :D3DPRIMITIVETYPE, :UINT, :UINT, :UINT, :ptr, :D3DFORMAT, :ptr, :UINT
    ProcessVertices	proc :UINT, :UINT, :UINT, :ptr, :ptr, :DWORD
    CreateVertexDeclaration proc :ptr, :ptr
    SetVertexDeclaration proc :ptr
    GetVertexDeclaration proc :ptr
    SetFVF		proc :DWORD
    GetFVF		proc :ptr
    CreateVertexShader	proc :ptr, :ptr
    SetVertexShader	proc :ptr
    GetVertexShader	proc :ptr
    SetVertexShaderConstantF proc :UINT, :ptr, :UINT
    GetVertexShaderConstantF proc :UINT, :ptr, :UINT
    SetVertexShaderConstantI proc :UINT, :ptr, :UINT
    GetVertexShaderConstantI proc :UINT, :ptr, :UINT
    SetVertexShaderConstantB proc :UINT, :ptr, :UINT
    GetVertexShaderConstantB proc :UINT, :ptr, :UINT
    SetStreamSource	proc :UINT, :ptr, :UINT, :UINT
    GetStreamSource	proc :UINT, :ptr, :ptr, :ptr
    SetStreamSourceFreq proc :UINT, :UINT
    GetStreamSourceFreq proc :UINT, :ptr
    SetIndices		proc :ptr
    GetIndices		proc :ptr
    CreatePixelShader	proc :ptr, :ptr
    SetPixelShader	proc :ptr
    GetPixelShader	proc :ptr
    SetPixelShaderConstantF proc :UINT, :ptr, :UINT
    GetPixelShaderConstantF proc :UINT, :ptr, :UINT
    SetPixelShaderConstantI proc :UINT, :ptr, :UINT
    GetPixelShaderConstantI proc :UINT, :ptr, :UINT
    SetPixelShaderConstantB proc :UINT, :ptr, :UINT
    GetPixelShaderConstantB proc :UINT, :ptr, :UINT
    DrawRectPatch	proc :UINT, :ptr, :ptr
    DrawTriPatch	proc :UINT, :ptr, :ptr
    DeletePatch		proc :UINT
    CreateQuery		proc :D3DQUERYTYPE, :ptr
    .ends
LPDIRECT3DDEVICE9	typedef ptr IDirect3DDevice9
PDIRECT3DDEVICE9	typedef ptr IDirect3DDevice9

.comdef IDirect3DStateBlock9
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetDevice		proc :ptr
    Capture		proc
    Apply		proc
    .ends
LPDIRECT3DSTATEBLOCK9	typedef ptr IDirect3DStateBlock9
PDIRECT3DSTATEBLOCK9	typedef ptr IDirect3DStateBlock9

.comdef IDirect3DSwapChain9
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Present		proc :ptr, :ptr, :HWND, :ptr, :DWORD
    GetFrontBufferData	proc :ptr
    GetBackBuffer	proc :UINT, :D3DBACKBUFFER_TYPE, :ptr
    GetRasterStatus	proc :ptr
    GetDisplayMode	proc :ptr
    GetDevice		proc :ptr
    GetPresentParameters proc :ptr
    .ends
LPDIRECT3DSWAPCHAIN9	typedef ptr IDirect3DSwapChain9
PDIRECT3DSWAPCHAIN9	typedef ptr IDirect3DSwapChain9

.comdef IDirect3DResource9
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetDevice		proc :ptr
    SetPrivateData	proc :REFGUID, :ptr, :DWORD, :DWORD
    GetPrivateData	proc :REFGUID, :ptr, :ptr
    FreePrivateData	proc :REFGUID
    SetPriority		proc :DWORD
    GetPriority		proc
    PreLoad		proc
    GetType		proc
    .ends
LPDIRECT3DRESOURCE9	typedef ptr IDirect3DResource9
PDIRECT3DRESOURCE9	typedef ptr IDirect3DResource9

.comdef IDirect3DVertexDeclaration9
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetDevice		proc :ptr
    GetDeclaration	proc :ptr, :ptr
    .ends
LPDIRECT3DVERTEXDECLARATION9 typedef ptr IDirect3DVertexDeclaration9
PDIRECT3DVERTEXDECLARATION9 typedef ptr IDirect3DVertexDeclaration9

.comdef IDirect3DVertexShader9
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetDevice		proc :ptr
    GetFunction		proc :ptr, :ptr
    .ends
LPDIRECT3DVERTEXSHADER9 typedef ptr IDirect3DVertexShader9
PDIRECT3DVERTEXSHADER9	typedef ptr IDirect3DVertexShader9

.comdef IDirect3DPixelShader9
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetDevice		proc :ptr
    GetFunction		proc :ptr, :ptr
    .ends
LPDIRECT3DPIXELSHADER9	typedef ptr IDirect3DPixelShader9
PDIRECT3DPIXELSHADER9	typedef ptr IDirect3DPixelShader9

.comdef IDirect3DBaseTexture9
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetDevice		proc :ptr
    SetPrivateData	proc :REFGUID, :ptr, :DWORD, :DWORD
    GetPrivateData	proc :REFGUID, :ptr, :ptr
    FreePrivateData	proc :REFGUID
    SetPriority		proc :DWORD
    GetPriority		proc
    PreLoad		proc
    GetType		proc
    SetLOD		proc :DWORD
    GetLOD		proc
    GetLevelCount	proc
    SetAutoGenFilterType proc :D3DTEXTUREFILTERTYPE
    GetAutoGenFilterType proc
    GenerateMipSubLevels proc
    .ends
LPDIRECT3DBASETEXTURE9	typedef ptr IDirect3DBaseTexture9
PDIRECT3DBASETEXTURE9	typedef ptr IDirect3DBaseTexture9

.comdef IDirect3DTexture9
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetDevice		proc :ptr
    SetPrivateData	proc :REFGUID, :ptr, :DWORD, :DWORD
    GetPrivateData	proc :REFGUID, :ptr, :ptr
    FreePrivateData	proc :REFGUID
    SetPriority		proc :DWORD
    GetPriority		proc
    PreLoad		proc
    GetType		proc
    SetLOD		proc :DWORD
    GetLOD		proc
    GetLevelCount	proc
    SetAutoGenFilterType proc :D3DTEXTUREFILTERTYPE
    GetAutoGenFilterType proc
    GenerateMipSubLevels proc
    GetLevelDesc	proc :UINT, :ptr
    GetSurfaceLevel	proc :UINT, :ptr
    LockRect		proc :UINT, :ptr, :ptr, :DWORD
    UnlockRect		proc :UINT
    AddDirtyRect	proc :ptr
    .ends
LPDIRECT3DTEXTURE9	typedef ptr IDirect3DTexture9
PDIRECT3DTEXTURE9	typedef ptr IDirect3DTexture9

.comdef IDirect3DVolumeTexture9
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetDevice		proc :ptr
    SetPrivateData	proc :REFGUID, :ptr, :DWORD, :DWORD
    GetPrivateData	proc :REFGUID, :ptr, :ptr
    FreePrivateData	proc :REFGUID
    SetPriority		proc :DWORD
    GetPriority		proc
    PreLoad		proc
    GetType		proc
    SetLOD		proc :DWORD
    GetLOD		proc
    GetLevelCount	proc
    SetAutoGenFilterType proc :D3DTEXTUREFILTERTYPE
    GetAutoGenFilterType proc
    GenerateMipSubLevels proc
    GetLevelDesc	proc :UINT, :ptr
    GetVolumeLevel	proc :UINT, :ptr
    LockBox		proc :UINT, :ptr, :ptr, :DWORD
    UnlockBox		proc :UINT
    AddDirtyBox		proc :ptr
    .ends
LPDIRECT3DVOLUMETEXTURE9 typedef ptr IDirect3DVolumeTexture9
PDIRECT3DVOLUMETEXTURE9 typedef ptr IDirect3DVolumeTexture9

.comdef IDirect3DCubeTexture9
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetDevice		proc :ptr
    SetPrivateData	proc :REFGUID, :ptr, :DWORD, :DWORD
    GetPrivateData	proc :REFGUID, :ptr, :ptr
    FreePrivateData	proc :REFGUID
    SetPriority		proc :DWORD
    GetPriority		proc
    PreLoad		proc
    GetType		proc
    SetLOD		proc :DWORD
    GetLOD		proc
    GetLevelCount	proc
    SetAutoGenFilterType proc :D3DTEXTUREFILTERTYPE
    GetAutoGenFilterType proc
    GenerateMipSubLevels proc
    GetLevelDesc	proc :UINT, :ptr
    GetCubeMapSurface	proc :D3DCUBEMAP_FACES, :UINT, :ptr
    LockRect		proc :D3DCUBEMAP_FACES, :UINT, :ptr, :ptr, :DWORD
    UnlockRect		proc :D3DCUBEMAP_FACES, :UINT
    AddDirtyRect	proc :D3DCUBEMAP_FACES, :ptr
    .ends
LPDIRECT3DCUBETEXTURE9	typedef ptr IDirect3DCubeTexture9
PDIRECT3DCUBETEXTURE9	typedef ptr IDirect3DCubeTexture9

.comdef IDirect3DVertexBuffer9
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetDevice		proc :ptr
    SetPrivateData	proc :REFGUID, :ptr, :DWORD, :DWORD
    GetPrivateData	proc :REFGUID, :ptr, :ptr
    FreePrivateData	proc :REFGUID
    SetPriority		proc :DWORD
    GetPriority		proc
    PreLoad		proc
    GetType		proc
    _Lock		proc :UINT, :UINT, :ptr, :DWORD
    Unlock		proc
    GetDesc		proc :ptr
    .ends
LPDIRECT3DVERTEXBUFFER9 typedef ptr IDirect3DVertexBuffer9
PDIRECT3DVERTEXBUFFER9	typedef ptr IDirect3DVertexBuffer9

.comdef IDirect3DIndexBuffer9
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetDevice		proc :ptr
    SetPrivateData	proc :REFGUID, :ptr, :DWORD, :DWORD
    GetPrivateData	proc :REFGUID, :ptr, :ptr
    FreePrivateData	proc :REFGUID
    SetPriority		proc :DWORD
    GetPriority		proc
    PreLoad		proc
    GetType		proc
    _Lock		proc :UINT, :UINT, :ptr, :DWORD
    Unlock		proc
    GetDesc		proc :ptr
    .ends
LPDIRECT3DINDEXBUFFER9	typedef ptr IDirect3DIndexBuffer9
PDIRECT3DINDEXBUFFER9	typedef ptr IDirect3DIndexBuffer9

.comdef IDirect3DSurface9
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetDevice		proc :ptr
    SetPrivateData	proc :REFGUID, :ptr, :DWORD, :DWORD
    GetPrivateData	proc :REFGUID, :ptr, :ptr
    FreePrivateData	proc :REFGUID
    SetPriority		proc :DWORD
    GetPriority		proc
    PreLoad		proc
    GetType		proc
    GetContainer	proc :REFIID, :ptr
    GetDesc		proc :ptr
    LockRect		proc :ptr, :ptr, :DWORD
    UnlockRect		proc
    GetDC		proc :ptr
    ReleaseDC		proc :HDC
    .ends
LPDIRECT3DSURFACE9	typedef ptr IDirect3DSurface9
PDIRECT3DSURFACE9	typedef ptr IDirect3DSurface9

.comdef IDirect3DVolume9
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetDevice		proc :ptr
    SetPrivateData	proc :REFGUID, :ptr, :DWORD, :DWORD
    GetPrivateData	proc :REFGUID, :ptr, :ptr
    FreePrivateData	proc :REFGUID
    GetContainer	proc :REFIID, :ptr
    GetDesc		proc :ptr
    LockBox		proc :ptr, :ptr, :DWORD
    UnlockBox		proc
    .ends
LPDIRECT3DVOLUME9	typedef ptr IDirect3DVolume9
PDIRECT3DVOLUME9	typedef ptr IDirect3DVolume9

.comdef IDirect3DQuery9
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetDevice		proc :ptr
    GetType		proc
    GetDataSize		proc
    Issue		proc :DWORD
    GetData		proc :ptr, :DWORD, :DWORD
    .ends
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


.comdef IDirect3D9Ex
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetAdapterCount	proc
    GetAdapterIdentifier proc :UINT, :DWORD, :ptr
    GetAdapterModeCount proc :UINT, :D3DFORMAT
    EnumAdapterModes	proc :UINT, :D3DFORMAT, :UINT, :ptr
    GetAdapterDisplayMode proc :UINT, :ptr
    CheckDeviceType	proc :UINT, :D3DDEVTYPE, :D3DFORMAT, :D3DFORMAT, :BOOL
    CheckDeviceFormat	proc :UINT, :D3DDEVTYPE, :D3DFORMAT, :DWORD, :D3DRESOURCETYPE, :D3DFORMAT
    CheckDeviceMultiSampleType proc :UINT, :D3DDEVTYPE, :D3DFORMAT, :BOOL, :D3DMULTISAMPLE_TYPE, :ptr
    CheckDepthStencilMatch proc :UINT, :D3DDEVTYPE, :D3DFORMAT, :D3DFORMAT, :D3DFORMAT
    CheckDeviceFormatConversion proc :UINT, :D3DDEVTYPE, :D3DFORMAT, :D3DFORMAT
    GetDeviceCaps	proc :UINT, :D3DDEVTYPE, :ptr
    GetAdapterMonitor	proc :UINT
    CreateDevice	proc :UINT, :D3DDEVTYPE, :HWND, :DWORD, :ptr, :ptr
    GetAdapterModeCountEx proc :UINT, :ptr
    EnumAdapterModesEx	proc :UINT, :ptr, :UINT, :ptr
    GetAdapterDisplayModeEx proc :UINT, :ptr, :ptr
    CreateDeviceEx	proc :UINT, :D3DDEVTYPE, :HWND, :DWORD, :ptr, :ptr, :ptr
    GetAdapterLUID	proc :UINT, :ptr
    .ends
LPDIRECT3D9EX		typedef ptr IDirect3D9Ex
PDIRECT3D9EX		typedef ptr IDirect3D9Ex

.comdef IDirect3DDevice9Ex
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    TestCooperativeLevel proc
    GetAvailableTextureMem proc
    EvictManagedResources proc
    GetDirect3D		proc :ptr
    GetDeviceCaps	proc :ptr
    GetDisplayMode	proc :UINT, :ptr
    GetCreationParameters proc :ptr
    SetCursorProperties proc :UINT, :UINT, :ptr
    SetCursorPosition	proc :SINT, :SINT, :DWORD
    ShowCursor		proc :BOOL
    CreateAdditionalSwapChain proc :ptr, :ptr
    GetSwapChain	proc :UINT, :ptr
    GetNumberOfSwapChains proc
    Reset		proc :ptr
    Present		proc :ptr, :ptr, :HWND, :ptr
    GetBackBuffer	proc :UINT, :UINT, :D3DBACKBUFFER_TYPE, :ptr
    GetRasterStatus	proc :UINT, :ptr
    SetDialogBoxMode	proc :BOOL
    SetGammaRamp	proc :UINT, :DWORD, :ptr
    GetGammaRamp	proc :UINT, :ptr
    CreateTexture	proc :UINT, :UINT, :UINT, :DWORD, :D3DFORMAT, :D3DPOOL, :ptr, :ptr
    CreateVolumeTexture proc :UINT, :UINT, :UINT, :UINT, :DWORD, :D3DFORMAT, :D3DPOOL, :ptr, :ptr
    CreateCubeTexture	proc :UINT, :UINT, :DWORD, :D3DFORMAT, :D3DPOOL, :ptr, :ptr
    CreateVertexBuffer	proc :UINT, :DWORD, :DWORD, :D3DPOOL, :ptr, :ptr
    CreateIndexBuffer	proc :UINT, :DWORD, :D3DFORMAT, :D3DPOOL, :ptr, :ptr
    CreateRenderTarget	proc :UINT, :UINT, :D3DFORMAT, :D3DMULTISAMPLE_TYPE, :DWORD, :BOOL, :ptr, :ptr
    CreateDepthStencilSurface proc :UINT, :UINT, :D3DFORMAT, :D3DMULTISAMPLE_TYPE, :DWORD, :BOOL, :ptr, :ptr
    UpdateSurface	proc :ptr, :ptr, :ptr, :ptr
    UpdateTexture	proc :ptr, :ptr
    GetRenderTargetData proc :ptr, :ptr
    GetFrontBufferData	proc :UINT, :ptr
    StretchRect		proc :ptr, :ptr, :ptr, :ptr, :D3DTEXTUREFILTERTYPE
    ColorFill		proc :ptr, :ptr, :D3DCOLOR
    CreateOffscreenPlainSurface proc :UINT, :UINT, :D3DFORMAT, :D3DPOOL, :ptr, :ptr
    SetRenderTarget	proc :DWORD, :ptr
    GetRenderTarget	proc :DWORD, :ptr
    SetDepthStencilSurface proc :ptr
    GetDepthStencilSurface proc :ptr
    BeginScene		proc
    EndScene		proc
    Clear		proc :DWORD, :ptr, :DWORD, :D3DCOLOR, :FLOAT, :DWORD
    SetTransform	proc :D3DTRANSFORMSTATETYPE, :ptr
    GetTransform	proc :D3DTRANSFORMSTATETYPE, :ptr
    MultiplyTransform	proc :D3DTRANSFORMSTATETYPE, :ptr
    SetViewport		proc :ptr
    GetViewport		proc :ptr
    SetMaterial		proc :ptr
    GetMaterial		proc :ptr
    SetLight		proc :DWORD, :ptr
    GetLight		proc :DWORD, :ptr
    LightEnable		proc :DWORD, :BOOL
    GetLightEnable	proc :DWORD, :ptr
    SetClipPlane	proc :DWORD, :ptr
    GetClipPlane	proc :DWORD, :ptr
    SetRenderState	proc :D3DRENDERSTATETYPE, :DWORD
    GetRenderState	proc :D3DRENDERSTATETYPE, :ptr
    CreateStateBlock	proc :D3DSTATEBLOCKTYPE, :ptr
    BeginStateBlock	proc
    EndStateBlock	proc :ptr
    SetClipStatus	proc :ptr
    GetClipStatus	proc :ptr
    GetTexture		proc :DWORD, :ptr
    SetTexture		proc :DWORD, :ptr
    GetTextureStageState proc :DWORD, :D3DTEXTURESTAGESTATETYPE, :ptr
    SetTextureStageState proc :DWORD, :D3DTEXTURESTAGESTATETYPE, :DWORD
    GetSamplerState	proc :DWORD, :D3DSAMPLERSTATETYPE, :ptr
    SetSamplerState	proc :DWORD, :D3DSAMPLERSTATETYPE, :DWORD
    ValidateDevice	proc :ptr
    SetPaletteEntries	proc :UINT, :ptr
    GetPaletteEntries	proc :UINT, :ptr
    SetCurrentTexturePalette proc :UINT
    GetCurrentTexturePalette proc :ptr
    SetScissorRect	proc :ptr
    GetScissorRect	proc :ptr
    SetSoftwareVertexProcessing proc :BOOL
    GetSoftwareVertexProcessing proc
    SetNPatchMode	proc :FLOAT
    GetNPatchMode	proc
    DrawPrimitive	proc :D3DPRIMITIVETYPE, :UINT, :UINT
    DrawIndexedPrimitive proc :D3DPRIMITIVETYPE, :SINT, :UINT, :UINT, :UINT, :UINT
    DrawPrimitiveUP	proc :D3DPRIMITIVETYPE, :UINT, :ptr, :UINT
    DrawIndexedPrimitiveUP proc :D3DPRIMITIVETYPE, :UINT, :UINT, :UINT, :ptr, :D3DFORMAT, :ptr, :UINT
    ProcessVertices	proc :UINT, :UINT, :UINT, :ptr, :ptr, :DWORD
    CreateVertexDeclaration proc :ptr, :ptr
    SetVertexDeclaration proc :ptr
    GetVertexDeclaration proc :ptr
    SetFVF		proc :DWORD
    GetFVF		proc :ptr
    CreateVertexShader	proc :ptr, :ptr
    SetVertexShader	proc :ptr
    GetVertexShader	proc :ptr
    SetVertexShaderConstantF proc :UINT, :ptr, :UINT
    GetVertexShaderConstantF proc :UINT, :ptr, :UINT
    SetVertexShaderConstantI proc :UINT, :ptr, :UINT
    GetVertexShaderConstantI proc :UINT, :ptr, :UINT
    SetVertexShaderConstantB proc :UINT, :ptr, :UINT
    GetVertexShaderConstantB proc :UINT, :ptr, :UINT
    SetStreamSource	proc :UINT, :ptr, :UINT, :UINT
    GetStreamSource	proc :UINT, :ptr, :ptr, :ptr
    SetStreamSourceFreq proc :UINT, :UINT
    GetStreamSourceFreq proc :UINT, :ptr
    SetIndices		proc :ptr
    GetIndices		proc :ptr
    CreatePixelShader	proc :ptr, :ptr
    SetPixelShader	proc :ptr
    GetPixelShader	proc :ptr
    SetPixelShaderConstantF proc :UINT, :ptr, :UINT
    GetPixelShaderConstantF proc :UINT, :ptr, :UINT
    SetPixelShaderConstantI proc :UINT, :ptr, :UINT
    GetPixelShaderConstantI proc :UINT, :ptr, :UINT
    SetPixelShaderConstantB proc :UINT, :ptr, :UINT
    GetPixelShaderConstantB proc :UINT, :ptr, :UINT
    DrawRectPatch	proc :UINT, :ptr, :ptr
    DrawTriPatch	proc :UINT, :ptr, :ptr
    DeletePatch		proc :UINT
    CreateQuery		proc :D3DQUERYTYPE, :ptr
    SetConvolutionMonoKernel proc :UINT, :UINT, :ptr, :ptr
    ComposeRects	proc :ptr, :ptr, :ptr, :UINT, :ptr, :D3DCOMPOSERECTSOP, :SINT, :SINT
    PresentEx		proc :ptr, :ptr, :HWND, :ptr, :DWORD
    GetGPUThreadPriority proc :ptr
    SetGPUThreadPriority proc :SINT
    WaitForVBlank	proc :UINT
    CheckResourceResidency proc :ptr, :UINT
    SetMaximumFrameLatency proc :UINT
    GetMaximumFrameLatency proc :ptr
    CheckDeviceState	proc :HWND
    CreateRenderTargetEx proc :UINT, :UINT, :D3DFORMAT, :D3DMULTISAMPLE_TYPE, :DWORD, :BOOL, :ptr, :ptr, :DWORD
    CreateOffscreenPlainSurfaceEx proc :UINT, :UINT, :D3DFORMAT, :D3DPOOL, :ptr, :ptr, :DWORD
    CreateDepthStencilSurfaceEx proc :UINT, :UINT, :D3DFORMAT, :D3DMULTISAMPLE_TYPE, :DWORD, :ptr, :ptr, :DWORD
    ResetEx		proc :ptr, :ptr
    GetDisplayModeEx	proc :UINT, :ptr, :ptr
    .ends
LPDIRECT3DDEVICE9EX	typedef ptr IDirect3DDevice9Ex
PDIRECT3DDEVICE9EX	typedef ptr IDirect3DDevice9Ex

.comdef IDirect3DSwapChain9Ex
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Present		proc :ptr, :ptr, :HWND, :ptr, :DWORD
    GetFrontBufferData	proc :ptr
    GetBackBuffer	proc :UINT, :D3DBACKBUFFER_TYPE, :ptr
    GetRasterStatus	proc :ptr
    GetDisplayMode	proc :ptr
    GetDevice		proc :ptr
    GetPresentParameters proc :ptr
    GetLastPresentCount proc :ptr
    GetPresentStats	proc :ptr
    GetDisplayModeEx	proc :ptr, :ptr
    .ends
LPDIRECT3DSWAPCHAIN9EX	typedef ptr IDirect3DSwapChain9Ex
PDIRECT3DSWAPCHAIN9EX	typedef ptr IDirect3DSwapChain9Ex

endif ; ifndef D3D_DISABLE_9EX

.comdef IDirect3D9ExOverlayExtension
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    CheckDeviceOverlayType proc :UINT, :D3DDEVTYPE, :UINT, :UINT, :D3DFORMAT, :ptr, :D3DDISPLAYROTATION, :ptr
    .ends
LPDIRECT3D9EXOVERLAYEXTENSION typedef ptr IDirect3D9ExOverlayExtension
PDIRECT3D9EXOVERLAYEXTENSION  typedef ptr IDirect3D9ExOverlayExtension

.comdef IDirect3DDevice9Video
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetContentProtectionCaps proc :ptr, :ptr, :ptr
    CreateAuthenticatedChannel proc :D3DAUTHENTICATEDCHANNELTYPE, :ptr, :ptr
    CreateCryptoSession proc :ptr, :ptr, :ptr, :ptr
    .ends
LPDIRECT3DDEVICE9VIDEO	typedef ptr IDirect3DDevice9Video
PDIRECT3DDEVICE9VIDEO	typedef ptr IDirect3DDevice9Video

.comdef IDirect3DAuthenticatedChannel9
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetCertificateSize	proc :ptr
    GetCertificate	proc :UINT, :ptr
    NegotiateKeyExchange proc :UINT, :ptr
    Query		proc :UINT, :ptr, :UINT, :ptr
    Configure		proc :UINT, :ptr, :ptr
    .ends
LPDIRECT3DAUTHENTICATEDCHANNEL9 typedef ptr IDirect3DAuthenticatedChannel9
PDIRECT3DAUTHENTICATEDCHANNEL9	typedef ptr IDirect3DAuthenticatedChannel9

.comdef IDirect3DCryptoSession9
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetCertificateSize	proc :ptr
    GetCertificate	proc :UINT, :ptr
    NegotiateKeyExchange proc :UINT, :ptr
    EncryptionBlt	proc :ptr, :ptr, :UINT, :ptr
    DecryptionBlt	proc :ptr, :ptr, :UINT, :ptr, :ptr, :ptr
    GetSurfacePitch	proc :ptr, :ptr
    StartSessionKeyRefresh proc :ptr, :UINT
    FinishSessionKeyRefresh proc
    GetEncryptionBltKey proc :ptr, :UINT
    .ends
LPDIRECT3DCRYPTOSESSION9 typedef ptr IDirect3DCryptoSession9
PDIRECT3DCRYPTOSESSION9 typedef ptr IDirect3DCryptoSession9

endif
.list
endif
