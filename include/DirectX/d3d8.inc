ifndef _D3D8_H_
define _D3D8_H_

ifndef DIRECT3D_VERSION
DIRECT3D_VERSION	equ 0x0800
endif

if(DIRECT3D_VERSION GE 0x0800)

D3D_SDK_VERSION		equ 220

include stdlib.inc

COM_NO_WINDOWS_H equ 1
include objbase.inc
include windows.inc

if NOT defined(HMONITOR_DECLARED) AND (WINVER LT 0x0500)
HMONITOR_DECLARED equ 1
endif

if defined(_WIN32) AND NOT defined(_NO_COM)
DEFINE_GUID(IID_IDirect3D8, 0x1dd9e8da, 0x1c77, 0x4d40, 0xb0, 0xcf, 0x98, 0xfe, 0xfd, 0xff, 0x95, 0x12);
DEFINE_GUID(IID_IDirect3DDevice8, 0x7385e5df, 0x8fe8, 0x41d5, 0x86, 0xb6, 0xd7, 0xb4, 0x85, 0x47, 0xb6, 0xcf);
DEFINE_GUID(IID_IDirect3DResource8, 0x1b36bb7b, 0x9b7, 0x410a, 0xb4, 0x45, 0x7d, 0x14, 0x30, 0xd7, 0xb3, 0x3f);
DEFINE_GUID(IID_IDirect3DBaseTexture8, 0xb4211cfa, 0x51b9, 0x4a9f, 0xab, 0x78, 0xdb, 0x99, 0xb2, 0xbb, 0x67, 0x8e);
DEFINE_GUID(IID_IDirect3DTexture8, 0xe4cdd575, 0x2866, 0x4f01, 0xb1, 0x2e, 0x7e, 0xec, 0xe1, 0xec, 0x93, 0x58);
DEFINE_GUID(IID_IDirect3DCubeTexture8, 0x3ee5b968, 0x2aca, 0x4c34, 0x8b, 0xb5, 0x7e, 0x0c, 0x3d, 0x19, 0xb7, 0x50);
DEFINE_GUID(IID_IDirect3DVolumeTexture8, 0x4b8aaafa, 0x140f, 0x42ba, 0x91, 0x31, 0x59, 0x7e, 0xaf, 0xaa, 0x2e, 0xad);
DEFINE_GUID(IID_IDirect3DVertexBuffer8, 0x8aeeeac7, 0x05f9, 0x44d4, 0xb5, 0x91, 0x00, 0x0b, 0x0d, 0xf1, 0xcb, 0x95);
DEFINE_GUID(IID_IDirect3DIndexBuffer8, 0x0e689c9a, 0x053d, 0x44a0, 0x9d, 0x92, 0xdb, 0x0e, 0x3d, 0x75, 0x0f, 0x86);
DEFINE_GUID(IID_IDirect3DSurface8, 0xb96eebca, 0xb326, 0x4ea5, 0x88, 0x2f, 0x2f, 0xf5, 0xba, 0xe0, 0x21, 0xdd);
DEFINE_GUID(IID_IDirect3DVolume8, 0xbd7349f5, 0x14f1, 0x42e4, 0x9c, 0x79, 0x97, 0x23, 0x80, 0xdb, 0x40, 0xc0);
DEFINE_GUID(IID_IDirect3DSwapChain8, 0x928c088b, 0x76b9, 0x4c6b, 0xa5, 0x36, 0xa5, 0x90, 0x85, 0x38, 0x76, 0xcd);
endif

include d3d8types.inc
include d3d8caps.inc

Direct3DCreate8 proto WINAPI SDKVersion:UINT

.comdef IDirect3D8 : public IUnknown

    RegisterSoftwareDevice	proc :ptr
    GetAdapterCount		proc
    GetAdapterIdentifier	proc :UINT, :DWORD, :ptr
    GetAdapterModeCount		proc :UINT
    EnumAdapterModes		proc :UINT, :UINT, :ptr
    GetAdapterDisplayMode	proc :UINT, :ptr
    CheckDeviceType		proc :UINT, :D3DDEVTYPE, :D3DFORMAT, :D3DFORMAT, :BOOL
    CheckDeviceFormat		proc :UINT, :D3DDEVTYPE, :D3DFORMAT, :DWORD, :D3DRESOURCETYPE, :D3DFORMAT
    CheckDeviceMultiSampleType	proc :UINT, :D3DDEVTYPE, :D3DFORMAT, :BOOL, :D3DMULTISAMPLE_TYPE
    CheckDepthStencilMatch	proc :UINT, :D3DDEVTYPE, :D3DFORMAT, :D3DFORMAT, :D3DFORMAT
    GetDeviceCaps		proc :UINT, :D3DDEVTYPE, :ptr
    GetAdapterMonitor		proc :UINT
    CreateDevice		proc :UINT, :D3DDEVTYPE, :HWND, :DWORD, :ptr, :ptr

    .ends

PDIRECT3D8	typedef ptr IDirect3D8
LPDIRECT3D8	typedef ptr IDirect3D8

.comdef IDirect3DDevice8 : public IUnknown

    TestCooperativeLevel	proc
    GetAvailableTextureMem	proc
    ResourceManagerDiscardBytes proc :DWORD
    GetDirect3D			proc :ptr
    GetDeviceCaps		proc :ptr
    GetDisplayMode		proc :ptr
    GetCreationParameters	proc :ptr
    SetCursorProperties		proc :UINT, :UINT, :ptr
    SetCursorPosition		proc :SINT, :SINT, :DWORD
    ShowCursor			proc :BOOL
    CreateAdditionalSwapChain	proc :ptr, :ptr
    Reset			proc :ptr
    Present			proc :ptr, :ptr, :HWND, :ptr
    GetBackBuffer		proc :UINT, D3DBACKBUFFER_TYPE, :ptr
    GetRasterStatus		proc :ptr
    SetGammaRamp		proc :DWORD, :ptr
    GetGammaRamp		proc :ptr
    CreateTexture		proc :UINT, :UINT, :UINT, :DWORD, :D3DFORMAT, :D3DPOOL, :ptr
    CreateVolumeTexture		proc :UINT, :UINT, :UINT, :UINT, :DWORD, :D3DFORMAT, :D3DPOOL, :ptr
    CreateCubeTexture		proc :UINT, :UINT, :DWORD, :D3DFORMAT, :D3DPOOL Pool, :ptr
    CreateVertexBuffer		proc :UINT, :DWORD, :DWORD, :D3DPOOL, :ptr
    CreateIndexBuffer		proc :UINT, :DWORD, :D3DFORMAT, :D3DPOOL, :ptr
    CreateRenderTarget		proc :UINT, :UINT, :D3DFORMAT, :D3DMULTISAMPLE_TYPE, :BOOL, :ptr
    CreateDepthStencilSurface	proc :UINT, :UINT, :D3DFORMAT, :D3DMULTISAMPLE_TYPE, :ptr
    CreateImageSurface		proc :UINT, :UINT, :D3DFORMAT, :ptr
    CopyRects			proc :ptr, :ptr, :UINT, :ptr, :ptr
    UpdateTexture		proc :ptr, :ptr
    GetFrontBuffer		proc :ptr
    SetRenderTarget		proc :ptr, :ptr
    GetRenderTarget		proc :ptr
    GetDepthStencilSurface	proc :ptr
    BeginScene			proc
    EndScene			proc
    Clear			proc :DWORD Count,CONST D3DRECT* pRects,DWORD Flags,D3DCOLOR Color,float Z,DWORD Stencil
    SetTransform		proc :D3DTRANSFORMSTATETYPE State,CONST D3DMATRIX* pMatrix
    GetTransform		proc :D3DTRANSFORMSTATETYPE State,D3DMATRIX* pMatrix
    MultiplyTransform		proc :D3DTRANSFORMSTATETYPE,CONST D3DMATRIX*
    SetViewport			proc :CONST D3DVIEWPORT8* pViewport
    GetViewport			proc :D3DVIEWPORT8* pViewport
    SetMaterial			proc :D3DMATERIAL8* pMaterial
    GetMaterial			proc :D3DMATERIAL8* pMaterial
    SetLight			proc :DWORD Index,CONST D3DLIGHT8*
    GetLight			proc :DWORD Index,D3DLIGHT8*
    LightEnable			proc :DWORD Index,BOOL Enable
    GetLightEnable		proc :DWORD Index,BOOL* pEnable
    SetClipPlane		proc :DWORD Index,CONST float* pPlane
    GetClipPlane		proc :DWORD Index,float* pPlane
    SetRenderState		proc :D3DRENDERSTATETYPE State,DWORD Value
    GetRenderState		proc :D3DRENDERSTATETYPE State,DWORD* pValue
    BeginStateBlock		proc
    EndStateBlock		proc :DWORD* pToken
    ApplyStateBlock		proc :DWORD Token
    CaptureStateBlock		proc :DWORD Token
    DeleteStateBlock		proc :DWORD Token
    CreateStateBlock		proc :D3DSTATEBLOCKTYPE Type,DWORD* pToken
    SetClipStatus		proc :D3DCLIPSTATUS8* pClipStatus
    GetClipStatus		proc :D3DCLIPSTATUS8* pClipStatus
    GetTexture			proc :DWORD Stage,IDirect3DBaseTexture8** ppTexture
    SetTexture			proc :DWORD Stage,IDirect3DBaseTexture8* pTexture
    GetTextureStageState	proc :DWORD Stage,D3DTEXTURESTAGESTATETYPE Type,DWORD* pValue
    SetTextureStageState	proc :DWORD Stage,D3DTEXTURESTAGESTATETYPE Type,DWORD Value
    ValidateDevice		proc :ptr
    GetInfo			proc :DWORD, :ptr, :DWORD
    SetPaletteEntries		proc :UINT, :ptr
    GetPaletteEntries		proc :UINT, :ptr
    SetCurrentTexturePalette	proc :UINT
    GetCurrentTexturePalette	proc :ptr
    DrawPrimitive		proc :D3DPRIMITIVETYPE, :UINT, :UINT
    DrawIndexedPrimitive	proc :D3DPRIMITIVETYPE, :UINT, :UINT, :UINT, :UINT
    DrawPrimitiveUP		proc :D3DPRIMITIVETYPE, :UINT, :ptr, :UINT
    DrawIndexedPrimitiveUP	proc :D3DPRIMITIVETYPE, :UINT, :UINT, :UINT, :ptr, :D3DFORMAT, :ptr, :UINT
    ProcessVertices		proc :UINT, :UINT, :UINT, :ptr, :DWORD
    CreateVertexShader		proc :ptr, :ptr, :ptr, :DWORD
    SetVertexShader		proc :DWORD
    GetVertexShader		proc :ptr
    DeleteVertexShader		proc :DWORD
    SetVertexShaderConstant	proc :DWORD, :ptr, :DWORD
    GetVertexShaderConstant	proc :DWORD, :ptr, :DWORD
    GetVertexShaderDeclaration	proc :DWORD, :ptr, :ptr
    GetVertexShaderFunction	proc :DWORD, :ptr, :ptr
    SetStreamSource		proc :UINT, :ptr, :UINT
    GetStreamSource		proc :UINT, :ptr, :ptr
    SetIndices			proc :ptr, :UINT
    GetIndices			proc :ptr, :ptr
    CreatePixelShader		proc :ptr, :ptr
    SetPixelShader		proc :DWORD
    GetPixelShader		proc :ptr
    DeletePixelShader		proc :DWORD
    SetPixelShaderConstant	proc :DWORD, :ptr, :DWORD
    GetPixelShaderConstant	proc :DWORD, :ptr, :DWORD
    GetPixelShaderFunction	proc :DWORD, :ptr, :ptr
    DrawRectPatch		proc :UINT, :ptr, :ptr
    DrawTriPatch		proc :UINT, :ptr, :ptr
    DeletePatch			proc :UINT

    .ends

LPDIRECT3DDEVICE8	typedef ptr IDirect3DDevice8
PDIRECT3DDEVICE8	typedef ptr IDirect3DDevice8

.comdef IDirect3DSwapChain8 : public IUnknown


    Present		proc :ptr, :ptr, :HWND, :ptr
    GetBackBuffer	proc :UINT, :D3DBACKBUFFER_TYPE, :ptr
    .ENDS

LPDIRECT3DSWAPCHAIN8	typedef ptr IDirect3DSwapChain8
PDIRECT3DSWAPCHAIN8	typedef ptr IDirect3DSwapChain8

.comdef IDirect3DResource8 : public IUnknown

    GetDevice		proc :ptr
    SetPrivateData	proc :REFGUID, :ptr, :DWORD, :DWORD
    GetPrivateData	proc :REFGUID, :ptr, :ptr
    FreePrivateData	proc :REFGUID
    SetPriority		proc :DWORD
    GetPriority		proc
    PreLoad		proc
    GetType		proc
    .ENDS

LPDIRECT3DRESOURCE8	typedef ptr IDirect3DResource8
PDIRECT3DRESOURCE8	typedef ptr IDirect3DResource8

.comdef IDirect3DBaseTexture8 : public IDirect3DResource8

    SetLOD		proc :DWORD
    GetLOD		proc
    GetLevelCount	proc
    .ENDS

LPDIRECT3DBASETEXTURE8, *PDIRECT3DBASETEXTURE8 typedef ptr IDirect3DBaseTexture8

.comdef IDirect3DTexture8 : public IDirect3DBaseTexture8

    GetLevelDesc	proc :UINT, :ptr
    GetSurfaceLevel	proc :UINT, :ptr
    LockRect		proc :UINT, :ptr, :ptr, :DWORD
    UnlockRect		proc :UINT
    AddDirtyRect	proc :ptr
    .ENDS

LPDIRECT3DTEXTURE8	typedef ptr IDirect3DTexture8
PDIRECT3DTEXTURE8	typedef ptr IDirect3DTexture8

.comdef IDirect3DVolumeTexture8 : public IDirect3DBaseTexture8

    GetLevelDesc	proc :UINT, :ptr
    GetVolumeLevel	proc :UINT, :ptr
    LockBox		proc :UINT, :ptr, :ptr, :DWORD
    UnlockBox		proc :UINT
    AddDirtyBox		proc :ptr
    .ENDS

LPDIRECT3DVOLUMETEXTURE8 typedef ptr IDirect3DVolumeTexture8
PDIRECT3DVOLUMETEXTURE8 typedef ptr IDirect3DVolumeTexture8

.comdef IDirect3DCubeTexture8 : public IDirect3DBaseTexture8

    GetLevelDesc	proc :UINT, :ptr
    GetCubeMapSurface	proc :D3DCUBEMAP_FACES, :UINT, :ptr
    LockRect		proc :D3DCUBEMAP_FACES, :UINT, :ptr, :ptr, :DWORD
    UnlockRect		proc :D3DCUBEMAP_FACES, :UINT
    AddDirtyRect	proc :D3DCUBEMAP_FACES, :ptr
    .ENDS

LPDIRECT3DCUBETEXTURE8	typedef ptr IDirect3DCubeTexture8
PDIRECT3DCUBETEXTURE8	typedef ptr IDirect3DCubeTexture8

.comdef IDirect3DVertexBuffer8 : public IDirect3DResource8

    _Lock		proc:UINT, :UINT, :ptr, :DWORD
    Unlock		proc
    GetDesc		proc :ptr
    .ENDS

LPDIRECT3DVERTEXBUFFER8 typedef ptr IDirect3DVertexBuffer8
PDIRECT3DVERTEXBUFFER8	typedef ptr IDirect3DVertexBuffer8

.comdef IDirect3DIndexBuffer8 : public IDirect3DResource8

    _Lock		proc :UINT, :UINT, :ptr, :DWORD
    Unlock		proc
    GetDesc		proc :ptr
    .ENDS

LPDIRECT3DINDEXBUFFER8	typedef ptr IDirect3DIndexBuffer8
PDIRECT3DINDEXBUFFER8	typedef ptr IDirect3DIndexBuffer8

.comdef IDirect3DSurface8 : public IUnknown

    GetDevice		proc :ptr
    SetPrivateData	proc :REFGUID, :ptr, :DWORD, :DWORD
    GetPrivateData	proc :REFGUID, :ptr, :ptr
    FreePrivateData	proc :REFGUID
    GetContainer	proc :REFIID, :ptr
    GetDesc		proc :ptr
    LockRect		proc :ptr, :ptr, :DWORD
    UnlockRect		proc
    .ENDS

LPDIRECT3DSURFACE8	typedef ptr IDirect3DSurface8
PDIRECT3DSURFACE8	typedef ptr IDirect3DSurface8

.comdef IDirect3DVolume8 : public IUnknown

    GetDevice		proc :ptr
    SetPrivateData	proc :REFGUID, :ptr, :DWORD, :DWORD
    GetPrivateData	proc :REFGUID, :ptr, :ptr
    FreePrivateData	proc :REFGUID
    GetContainer	proc :REFIID, :ptr
    GetDesc		proc :ptr
    LockBox		proc :ptr, :ptr, :DWORD
    UnlockBox		proc
    .ENDS

LPDIRECT3DVOLUME8	typedef ptr IDirect3DVolume8
PDIRECT3DVOLUME8	typedef ptr IDirect3DVolume8

D3DSPD_IUNKNOWN		equ 0x00000001
D3DCURRENT_DISPLAY_MODE equ 0x00EFFFFF
D3DCREATE_FPU_PRESERVE	equ 0x00000002
D3DCREATE_MULTITHREADED equ 0x00000004
D3DCREATE_PUREDEVICE	equ 0x00000010
D3DCREATE_SOFTWARE_VERTEXPROCESSING equ 0x00000020
D3DCREATE_HARDWARE_VERTEXPROCESSING equ 0x00000040
D3DCREATE_MIXED_VERTEXPROCESSING equ 0x00000080
D3DCREATE_DISABLE_DRIVER_MANAGEMENT equ 0x00000100

D3DADAPTER_DEFAULT	equ 0
D3DENUM_NO_WHQL_LEVEL	equ 0x00000002
D3DPRESENT_BACK_BUFFERS_MAX equ 3
D3DSGR_NO_CALIBRATION	equ 0x00000000
D3DSGR_CALIBRATE	equ 0x00000001
D3DCURSOR_IMMEDIATE_UPDATE equ 0x00000001

_FACD3D equ 0x876
MAKE_D3DHRESULT macro code
	exitm<MAKE_HRESULT( 1, _FACD3D, code )>
	endm

D3D_OK equ S_OK

D3DERR_WRONGTEXTUREFORMAT equ MAKE_D3DHRESULT(2072)
D3DERR_UNSUPPORTEDCOLOROPERATION equ MAKE_D3DHRESULT(2073)
D3DERR_UNSUPPORTEDCOLORARG equ MAKE_D3DHRESULT(2074)
D3DERR_UNSUPPORTEDALPHAOPERATION equ MAKE_D3DHRESULT(2075)
D3DERR_UNSUPPORTEDALPHAARG equ MAKE_D3DHRESULT(2076)
D3DERR_TOOMANYOPERATIONS equ MAKE_D3DHRESULT(2077)
D3DERR_CONFLICTINGTEXTUREFILTER equ MAKE_D3DHRESULT(2078)
D3DERR_UNSUPPORTEDFACTORVALUE equ MAKE_D3DHRESULT(2079)
D3DERR_CONFLICTINGRENDERSTATE equ MAKE_D3DHRESULT(2081)
D3DERR_UNSUPPORTEDTEXTUREFILTER equ MAKE_D3DHRESULT(2082)
D3DERR_CONFLICTINGTEXTUREPALETTE equ MAKE_D3DHRESULT(2086)
D3DERR_DRIVERINTERNALERROR equ MAKE_D3DHRESULT(2087)

D3DERR_NOTFOUND		equ MAKE_D3DHRESULT(2150)
D3DERR_MOREDATA		equ MAKE_D3DHRESULT(2151)
D3DERR_DEVICELOST	equ MAKE_D3DHRESULT(2152)
D3DERR_DEVICENOTRESET	equ MAKE_D3DHRESULT(2153)
D3DERR_NOTAVAILABLE	equ MAKE_D3DHRESULT(2154)
D3DERR_OUTOFVIDEOMEMORY equ MAKE_D3DHRESULT(380)
D3DERR_INVALIDDEVICE	equ MAKE_D3DHRESULT(2155)
D3DERR_INVALIDCALL	equ MAKE_D3DHRESULT(2156)
D3DERR_DRIVERINVALIDCALL equ MAKE_D3DHRESULT(2157)

endif
endif

