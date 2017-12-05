ifndef _D3D9_H_
_D3D9_H_ equ <>
.xlist
ifndef DIRECT3D_VERSION
DIRECT3D_VERSION equ 0x0900
endif  ;;DIRECT3D_VERSION

;; include this file content only if compiling for DX9 interfaces
if (DIRECT3D_VERSION GE 0x0900)

;; This identifier is passed to Direct3DCreate9 in order to ensure that an
;; application was built against the correct header files. This number is
;; incremented whenever a header (or other) change would require applications
;; to be rebuilt. If the version doesn't match, Direct3DCreate9 will fail.
;; (The number itself has no meaning.)

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

D3DAPI			equ <WINAPI>

;;
;; Interface IID's
;;
if defined( _WIN32 ) AND NOT defined( _NO_COM)

;; IID_IDirect3D9
;; {81BDCBCA-64D4-426d-AE8D-AD0147F4275C}
DEFINE_GUID(IID_IDirect3D9, 0x81bdcbca, 0x64d4, 0x426d, 0xae, 0x8d, 0xad, 0x1, 0x47, 0xf4, 0x27, 0x5c);

;; IID_IDirect3DDevice9
;; {D0223B96-BF7A-43fd-92BD-A43B0D82B9EB}
DEFINE_GUID(IID_IDirect3DDevice9, 0xd0223b96, 0xbf7a, 0x43fd, 0x92, 0xbd, 0xa4, 0x3b, 0xd, 0x82, 0xb9, 0xeb);

;; IID_IDirect3DResource9
;; {05EEC05D-8F7D-4362-B999-D1BAF357C704}
DEFINE_GUID(IID_IDirect3DResource9, 0x5eec05d, 0x8f7d, 0x4362, 0xb9, 0x99, 0xd1, 0xba, 0xf3, 0x57, 0xc7, 0x4);

;; IID_IDirect3DBaseTexture9
;; {580CA87E-1D3C-4d54-991D-B7D3E3C298CE}
DEFINE_GUID(IID_IDirect3DBaseTexture9, 0x580ca87e, 0x1d3c, 0x4d54, 0x99, 0x1d, 0xb7, 0xd3, 0xe3, 0xc2, 0x98, 0xce);

;; IID_IDirect3DTexture9
;; {85C31227-3DE5-4f00-9B3A-F11AC38C18B5}
DEFINE_GUID(IID_IDirect3DTexture9, 0x85c31227, 0x3de5, 0x4f00, 0x9b, 0x3a, 0xf1, 0x1a, 0xc3, 0x8c, 0x18, 0xb5);

;; IID_IDirect3DCubeTexture9
;; {FFF32F81-D953-473a-9223-93D652ABA93F}
DEFINE_GUID(IID_IDirect3DCubeTexture9, 0xfff32f81, 0xd953, 0x473a, 0x92, 0x23, 0x93, 0xd6, 0x52, 0xab, 0xa9, 0x3f);

;; IID_IDirect3DVolumeTexture9
;; {2518526C-E789-4111-A7B9-47EF328D13E6}
DEFINE_GUID(IID_IDirect3DVolumeTexture9, 0x2518526c, 0xe789, 0x4111, 0xa7, 0xb9, 0x47, 0xef, 0x32, 0x8d, 0x13, 0xe6);

;; IID_IDirect3DVertexBuffer9
;; {B64BB1B5-FD70-4df6-BF91-19D0A12455E3}
DEFINE_GUID(IID_IDirect3DVertexBuffer9, 0xb64bb1b5, 0xfd70, 0x4df6, 0xbf, 0x91, 0x19, 0xd0, 0xa1, 0x24, 0x55, 0xe3);

;; IID_IDirect3DIndexBuffer9
;; {7C9DD65E-D3F7-4529-ACEE-785830ACDE35}
DEFINE_GUID(IID_IDirect3DIndexBuffer9, 0x7c9dd65e, 0xd3f7, 0x4529, 0xac, 0xee, 0x78, 0x58, 0x30, 0xac, 0xde, 0x35);

;; IID_IDirect3DSurface9
;; {0CFBAF3A-9FF6-429a-99B3-A2796AF8B89B}
DEFINE_GUID(IID_IDirect3DSurface9, 0xcfbaf3a, 0x9ff6, 0x429a, 0x99, 0xb3, 0xa2, 0x79, 0x6a, 0xf8, 0xb8, 0x9b);

;; IID_IDirect3DVolume9
;; {24F416E6-1F67-4aa7-B88E-D33F6F3128A1}
DEFINE_GUID(IID_IDirect3DVolume9, 0x24f416e6, 0x1f67, 0x4aa7, 0xb8, 0x8e, 0xd3, 0x3f, 0x6f, 0x31, 0x28, 0xa1);

;; IID_IDirect3DSwapChain9
;; {794950F2-ADFC-458a-905E-10A10B0B503B}
DEFINE_GUID(IID_IDirect3DSwapChain9, 0x794950f2, 0xadfc, 0x458a, 0x90, 0x5e, 0x10, 0xa1, 0xb, 0xb, 0x50, 0x3b);

;; IID_IDirect3DVertexDeclaration9
;; {DD13C59C-36FA-4098-A8FB-C7ED39DC8546}
DEFINE_GUID(IID_IDirect3DVertexDeclaration9, 0xdd13c59c, 0x36fa, 0x4098, 0xa8, 0xfb, 0xc7, 0xed, 0x39, 0xdc, 0x85, 0x46);

;; IID_IDirect3DVertexShader9
;; {EFC5557E-6265-4613-8A94-43857889EB36}
DEFINE_GUID(IID_IDirect3DVertexShader9, 0xefc5557e, 0x6265, 0x4613, 0x8a, 0x94, 0x43, 0x85, 0x78, 0x89, 0xeb, 0x36);

;; IID_IDirect3DPixelShader9
;; {6D3BDBDC-5B02-4415-B852-CE5E8BCCB289}
DEFINE_GUID(IID_IDirect3DPixelShader9, 0x6d3bdbdc, 0x5b02, 0x4415, 0xb8, 0x52, 0xce, 0x5e, 0x8b, 0xcc, 0xb2, 0x89);

;; IID_IDirect3DStateBlock9
;; {B07C4FE5-310D-4ba8-A23C-4F0F206F218B}
DEFINE_GUID(IID_IDirect3DStateBlock9, 0xb07c4fe5, 0x310d, 0x4ba8, 0xa2, 0x3c, 0x4f, 0xf, 0x20, 0x6f, 0x21, 0x8b);

;; IID_IDirect3DQuery9
;; {d9771460-a695-4f26-bbd3-27b840b541cc}
DEFINE_GUID(IID_IDirect3DQuery9, 0xd9771460, 0xa695, 0x4f26, 0xbb, 0xd3, 0x27, 0xb8, 0x40, 0xb5, 0x41, 0xcc);


;; IID_HelperName
;; {E4A36723-FDFE-4b22-B146-3C04C07F4CC8}
DEFINE_GUID(IID_HelperName, 0xe4a36723, 0xfdfe, 0x4b22, 0xb1, 0x46, 0x3c, 0x4, 0xc0, 0x7f, 0x4c, 0xc8);

;; D3D9Ex only --
ifndef D3D_DISABLE_9EX

;; IID_IDirect3D9Ex
;; {02177241-69FC-400C-8FF1-93A44DF6861D}
DEFINE_GUID(IID_IDirect3D9Ex, 0x02177241, 0x69FC, 0x400C, 0x8F, 0xF1, 0x93, 0xA4, 0x4D, 0xF6, 0x86, 0x1D);

;; IID_IDirect3DDevice9Ex
;; {B18B10CE-2649-405a-870F-95F777D4313A}
DEFINE_GUID(IID_IDirect3DDevice9Ex, 0xb18b10ce, 0x2649, 0x405a, 0x87, 0xf, 0x95, 0xf7, 0x77, 0xd4, 0x31, 0x3a);

;; IID_IDirect3DSwapChain9Ex
;; {91886CAF-1C3D-4d2e-A0AB-3E4C7D8D3303}
DEFINE_GUID(IID_IDirect3DSwapChain9Ex, 0x91886caf, 0x1c3d, 0x4d2e, 0xa0, 0xab, 0x3e, 0x4c, 0x7d, 0x8d, 0x33, 0x3);

;; IID_IDirect3D9ExOverlayExtension
;; {187aeb13-aaf5-4c59-876d-e059088c0df8}
DEFINE_GUID(IID_IDirect3D9ExOverlayExtension, 0x187aeb13, 0xaaf5, 0x4c59, 0x87, 0x6d, 0xe0, 0x59, 0x8, 0x8c, 0xd, 0xf8);

;; IID_IDirect3DDevice9Video
;; {26DC4561-A1EE-4ae7-96DA-118A36C0EC95}
DEFINE_GUID(IID_IDirect3DDevice9Video, 0x26dc4561, 0xa1ee, 0x4ae7, 0x96, 0xda, 0x11, 0x8a, 0x36, 0xc0, 0xec, 0x95);

;; IID_IDirect3D9AuthenticatedChannel
;; {FF24BEEE-DA21-4beb-98B5-D2F899F98AF9}
DEFINE_GUID(IID_IDirect3DAuthenticatedChannel9, 0xff24beee, 0xda21, 0x4beb, 0x98, 0xb5, 0xd2, 0xf8, 0x99, 0xf9, 0x8a, 0xf9);

;; IID_IDirect3DCryptoSession9
;; {FA0AB799-7A9C-48ca-8C5B-237E71A54434}
DEFINE_GUID(IID_IDirect3DCryptoSession9, 0xfa0ab799, 0x7a9c, 0x48ca, 0x8c, 0x5b, 0x23, 0x7e, 0x71, 0xa5, 0x44, 0x34);

endif ;; NOT D3D_DISABLE_9EX
;; -- D3D9Ex only
endif ;; defined( _WIN32 ) AND NOT defined( _NO_COM)

include <d3d9types.inc>
include <d3d9caps.inc>
.xlist
;;
;; DLL Function for creating a Direct3D9 object. This object supports
;; enumeration and allows the creation of Direct3DDevice9 objects.
;; Pass the value of the constant D3D_SDK_VERSION to this function, so
;; that the run-time can validate that your application was compiled
;; against the right headers.
;;
ifdef __PE__
option	dllimport:<d3d9>
else
includelib d3d9.lib
endif

;IDirect3D9 *
Direct3DCreate9 proto WINAPI SDKVersion:UINT

;;
;; Stubs for graphics profiling.
;;

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

;;
;; Direct3D interfaces
;;

D3D90T typedef proto WINAPI :ptr
D3D91T typedef proto WINAPI :ptr, :ptr
D3D92T typedef proto WINAPI :ptr, :ptr, :ptr
D3D93T typedef proto WINAPI :ptr, :ptr, :ptr, :ptr
D3D94T typedef proto WINAPI :ptr, :ptr, :ptr, :ptr, :ptr
D3D95T typedef proto WINAPI :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
D3D96T typedef proto WINAPI :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr

D3D90 typedef ptr D3D90T
D3D91 typedef ptr D3D91T
D3D92 typedef ptr D3D92T
D3D93 typedef ptr D3D93T
D3D94 typedef ptr D3D94T
D3D95 typedef ptr D3D95T
D3D96 typedef ptr D3D96T

IDirect3D9		STRUC
;;** IUnknown methods **
QueryInterface		D3D90 ?
AddRef			D3D90 ?
Release			D3D90 ?
;;** IDirect3D9 methods **
RegisterSoftwareDevice	PVOID ?
GetAdapterCount		PVOID ?
GetAdapterIdentifier	PVOID ?
GetAdapterModeCount	PVOID ?
EnumAdapterModes	PVOID ?
GetAdapterDisplayMode	PVOID ?
CheckDeviceType		PVOID ?
CheckDeviceFormat	PVOID ?
CheckDeviceMultiSampleType PVOID ?
CheckDepthStencilMatch	PVOID ?
CheckDeviceFormatConversion PVOID ?
GetDeviceCaps		PVOID ?
GetAdapterMonitor	PVOID ?
CreateDevice		D3D96 ?
ifdef D3D_DEBUG_INFO
Version			LPCWSTR ?
endif
IDirect3D9		ENDS
LPDIRECT3D9		typedef ptr IDirect3D9
PDIRECT3D9		typedef ptr IDirect3D9

IDirect3D9_QueryInterface macro p,a,b
	exitm<[p].QueryInterface(p,a,b)>
	endm
IDirect3D9_AddRef macro p
	exitm<[p].AddRef(p)>
	endm
IDirect3D9_Release macro p
	exitm<[p].Release(p)>
	endm
IDirect3D9_RegisterSoftwareDevice macro p,a
	exitm<[p].RegisterSoftwareDevice(p,a)>
	endm
IDirect3D9_GetAdapterCount macro p
	exitm<[p].GetAdapterCount(p)>
	endm
IDirect3D9_GetAdapterIdentifier macro p,a,b,c
	exitm<[p].GetAdapterIdentifier(p,a,b,c)>
	endm
IDirect3D9_GetAdapterModeCount macro p,a,b
	exitm<[p].GetAdapterModeCount(p,a,b)>
	endm
IDirect3D9_EnumAdapterModes macro p,a,b,c,d
	exitm<[p].EnumAdapterModes(p,a,b,c,d)>
	endm
IDirect3D9_GetAdapterDisplayMode macro p,a,b
	exitm<[p].GetAdapterDisplayMode(p,a,b)>
	endm
IDirect3D9_CheckDeviceType macro p,a,b,c,d,e
	exitm<[p].CheckDeviceType(p,a,b,c,d,e)>
	endm
IDirect3D9_CheckDeviceFormat macro p,a,b,c,d,e,f
	exitm<[p].CheckDeviceFormat(p,a,b,c,d,e,f)>
	endm
IDirect3D9_CheckDeviceMultiSampleType macro p,a,b,c,d,e,f
	exitm<[p].CheckDeviceMultiSampleType(p,a,b,c,d,e,f)>
	endm
IDirect3D9_CheckDepthStencilMatch macro p,a,b,c,d,e
	exitm<[p].CheckDepthStencilMatch(p,a,b,c,d,e)>
	endm
IDirect3D9_CheckDeviceFormatConversion macro p,a,b,c,d
	exitm<[p].CheckDeviceFormatConversion(p,a,b,c,d)>
	endm
IDirect3D9_GetDeviceCaps macro p,a,b,c
	exitm<[p].GetDeviceCaps(p,a,b,c)>
	endm
IDirect3D9_GetAdapterMonitor macro p,a
	exitm<[p].GetAdapterMonitor(p,a)>
	endm
IDirect3D9_CreateDevice macro p,a,b,c,d,e,f
	exitm<[p].CreateDevice(p,a,b,c,d,e,f)>
	endm

;; SwapChain

IDirect3DDevice9	STRUC
;;** IUnknown methods **
QueryInterface		D3D90 ?
AddRef			D3D90 ?
Release			D3D90 ?
;;** IDirect3DDevice9 methods **
TestCooperativeLevel	PVOID ?
GetAvailableTextureMem	PVOID ?
EvictManagedResources	PVOID ?
GetDirect3D		PVOID ?
GetDeviceCaps		PVOID ?
GetDisplayMode		PVOID ?
GetCreationParameters	PVOID ?
SetCursorProperties	PVOID ?
SetCursorPosition	PVOID ?
ShowCursor		PVOID ?
CreateAdditionalSwapChain PVOID ?
GetSwapChain		PVOID ?
GetNumberOfSwapChains	PVOID ?
Reset			PVOID ?
Present			D3D94 ?
GetBackBuffer		PVOID ?
GetRasterStatus		PVOID ?
SetDialogBoxMode	PVOID ?
SetGammaRamp		PVOID ?
GetGammaRamp		PVOID ?
CreateTexture		PVOID ?
CreateVolumeTexture	PVOID ?
CreateCubeTexture	PVOID ?
CreateVertexBuffer	PVOID ?
CreateIndexBuffer	PVOID ?
CreateRenderTarget	PVOID ?
CreateDepthStencilSurface PVOID ?
UpdateSurface		PVOID ?
UpdateTexture		PVOID ?
GetRenderTargetData	PVOID ?
GetFrontBufferData	PVOID ?
StretchRect		PVOID ?
ColorFill		PVOID ?
CreateOffscreenPlainSurface PVOID ?
SetRenderTarget		PVOID ?
GetRenderTarget		PVOID ?
SetDepthStencilSurface	PVOID ?
GetDepthStencilSurface	PVOID ?
BeginScene		D3D90 ?
EndScene		D3D90 ?
Clear			D3D96 ?
SetTransform		PVOID ?
GetTransform		PVOID ?
MultiplyTransform	PVOID ?
SetViewport		PVOID ?
GetViewport		PVOID ?
SetMaterial		PVOID ?
GetMaterial		PVOID ?
SetLight		PVOID ?
GetLight		PVOID ?
LightEnable		PVOID ?
GetLightEnable		PVOID ?
SetClipPlane		PVOID ?
GetClipPlane		PVOID ?
SetRenderState		PVOID ?
GetRenderState		PVOID ?
CreateStateBlock	PVOID ?
BeginStateBlock		PVOID ?
EndStateBlock		PVOID ?
SetClipStatus		PVOID ?
GetClipStatus		PVOID ?
GetTexture		PVOID ?
SetTexture		PVOID ?
GetTextureStageState	PVOID ?
SetTextureStageState	PVOID ?
GetSamplerState		PVOID ?
SetSamplerState		PVOID ?
ValidateDevice		PVOID ?
SetPaletteEntries	PVOID ?
GetPaletteEntries	PVOID ?
SetCurrentTexturePalette PVOID ?
GetCurrentTexturePalette PVOID ?
SetScissorRect		PVOID ?
GetScissorRect		PVOID ?
SetSoftwareVertexProcessing PVOID ?
GetSoftwareVertexProcessing PVOID ?
SetNPatchMode		PVOID ?
GetNPatchMode		PVOID ?
DrawPrimitive		PVOID ?
DrawIndexedPrimitive	PVOID ?
DrawPrimitiveUP		PVOID ?
DrawIndexedPrimitiveUP	PVOID ?
ProcessVertices		PVOID ?
CreateVertexDeclaration PVOID ?
SetVertexDeclaration	PVOID ?
GetVertexDeclaration	PVOID ?
SetFVF			PVOID ?
GetFVF			PVOID ?
CreateVertexShader	PVOID ?
SetVertexShader		PVOID ?
GetVertexShader		PVOID ?
SetVertexShaderConstantF PVOID ?
GetVertexShaderConstantF PVOID ?
SetVertexShaderConstantI PVOID ?
GetVertexShaderConstantI PVOID ?
SetVertexShaderConstantB PVOID ?
GetVertexShaderConstantB PVOID ?
SetStreamSource		PVOID ?
GetStreamSource		PVOID ?
SetStreamSourceFreq	PVOID ?
GetStreamSourceFreq	PVOID ?
SetIndices		PVOID ?
GetIndices		PVOID ?
CreatePixelShader	PVOID ?
SetPixelShader		PVOID ?
GetPixelShader		PVOID ?
SetPixelShaderConstantF PVOID ?
GetPixelShaderConstantF PVOID ?
SetPixelShaderConstantI PVOID ?
GetPixelShaderConstantI PVOID ?
SetPixelShaderConstantB PVOID ?
GetPixelShaderConstantB PVOID ?
DrawRectPatch		PVOID ?
DrawTriPatch		PVOID ?
DeletePatch		PVOID ?
CreateQuery		PVOID ?
ifdef D3D_DEBUG_INFO
CreationParameters	D3DDEVICE_CREATION_PARAMETERS ?
PresentParameters	D3DPRESENT_PARAMETERS ?
DisplayMode		D3DDISPLAYMODE ?
Caps			D3DCAPS9 ?
AvailableTextureMem	UINT ?
SwapChains		UINT ?
Textures		UINT ?
VertexBuffers		UINT ?
IndexBuffers		UINT ?
VertexShaders		UINT ?
PixelShaders		UINT ?
Viewport		D3DVIEWPORT9 ?
ProjectionMatrix	D3DMATRIX ?
ViewMatrix		D3DMATRIX ?
WorldMatrix		D3DMATRIX ?
TextureMatrices		D3DMATRIX 8 dup(?)
FVF			dd ?
VertexSize		UINT ?
VertexShaderVersion	dd ?
PixelShaderVersion	dd ?
SoftwareVertexProcessing BOOL ?
Material		D3DMATERIAL9 ?
Lights			D3DLIGHT9 16 dup(?)
LightsEnabled		BOOL 16 dup(?)
GammaRamp		D3DGAMMARAMP ?
ScissorRect		RECT ?
DialogBoxMode		BOOL ?
endif
IDirect3DDevice9	ENDS
LPDIRECT3DDEVICE9	typedef ptr IDirect3DDevice9
PDIRECT3DDEVICE9	typedef ptr IDirect3DDevice9

IDirect3DDevice9_QueryInterface macro p,a,b
	exitm<[p].QueryInterface(p,a,b)>
	endm
IDirect3DDevice9_AddRef macro p
	exitm<[p].AddRef(p)>
	endm
IDirect3DDevice9_Release macro p
	exitm<[p].Release(p)>
	endm
IDirect3DDevice9_TestCooperativeLevel macro p
	exitm<[p].TestCooperativeevel(p)>
	endm
IDirect3DDevice9_GetAvailableTextureMem macro p
	exitm<[p].GetAvailableTextureMem(p)>
	endm
IDirect3DDevice9_EvictManagedResources macro p
	exitm<[p].EvictManagedResources(p)>
	endm
IDirect3DDevice9_GetDirect3D macro p,a
	exitm<[p].GetDirect3D(p,a)>
	endm
IDirect3DDevice9_GetDeviceCaps macro p,a
	exitm<[p].GetDeviceCaps(p,a)>
	endm
IDirect3DDevice9_GetDisplayMode macro p,a,b
	exitm<[p].GetDisplayMode(p,a,b)>
	endm
IDirect3DDevice9_GetCreationParameters macro p,a
	exitm<[p].GetCreationParameters(p,a)>
	endm
IDirect3DDevice9_SetCursorProperties macro p,a,b,c
	exitm<[p].SetCursorProperties(p,a,b,c)>
	endm
IDirect3DDevice9_SetCursorPosition macro p,a,b,c
	exitm<[p].SetCursorPosition(p,a,b,c)>
	endm
IDirect3DDevice9_ShowCursor macro p,a
	exitm<[p].ShowCursor(p,a)>
	endm
IDirect3DDevice9_CreateAdditionalSwapChain macro p,a,b
	exitm<[p].CreateAdditionalSwapChain(p,a,b)>
	endm
IDirect3DDevice9_GetSwapChain macro p,a,b
	exitm<[p].GetSwapChain(p,a,b)>
	endm
IDirect3DDevice9_GetNumberOfSwapChains macro p
	exitm<[p].GetNumberOfSwapChains(p)>
	endm
IDirect3DDevice9_Reset macro p,a
	exitm<[p].Reset(p,a)>
	endm
IDirect3DDevice9_Present macro p,a,b,c,d
	exitm<[p].Present(p,a,b,c,d)>
	endm
IDirect3DDevice9_GetBackBuffer macro p,a,b,c,d
	exitm<[p].GetBackBuffer(p,a,b,c,d)>
	endm
IDirect3DDevice9_GetRasterStatus macro p,a,b
	exitm<[p].GetRasterStatus(p,a,b)>
	endm
IDirect3DDevice9_SetDialogBoxMode macro p,a
	exitm<[p].SetDialogBoxMode(p,a)>
	endm
IDirect3DDevice9_SetGammaRamp macro p,a,b,c
	exitm<[p].SetGammaRamp(p,a,b,c)>
	endm
IDirect3DDevice9_GetGammaRamp macro p,a,b
	exitm<[p].GetGammaRamp(p,a,b)>
	endm
IDirect3DDevice9_CreateTexture macro p,a,b,c,d,e,f,g,h
	exitm<[p].CreateTexture(p,a,b,c,d,e,f,g,h)>
	endm
IDirect3DDevice9_CreateVolumeTexture macro p,a,b,c,d,e,f,g,h,i
	exitm<[p].CreateVolumeTexture(p,a,b,c,d,e,f,g,h,i)>
	endm
IDirect3DDevice9_CreateCubeTexture macro p,a,b,c,d,e,f,g
	exitm<[p].CreateCubeTexture(p,a,b,c,d,e,f,g)>
	endm
IDirect3DDevice9_CreateVertexBuffer macro p,a,b,c,d,e,f
	exitm<[p].CreateVertexBuffer(p,a,b,c,d,e,f)>
	endm
IDirect3DDevice9_CreateIndexBuffer macro p,a,b,c,d,e,f
	exitm<[p].CreateIndexBuffer(p,a,b,c,d,e,f)>
	endm
IDirect3DDevice9_CreateRenderTarget macro p,a,b,c,d,e,f,g,h
	exitm<[p].CreateRenderTarget(p,a,b,c,d,e,f,g,h)>
	endm
IDirect3DDevice9_CreateDepthStencilSurface macro p,a,b,c,d,e,f,g,h
	exitm<[p].CreateDepthStencilSurface(p,a,b,c,d,e,f,g,h)>
	endm
IDirect3DDevice9_UpdateSurface macro p,a,b,c,d
	exitm<[p].UpdateSurface(p,a,b,c,d)>
	endm
IDirect3DDevice9_UpdateTexture macro p,a,b
	exitm<[p].UpdateTexture(p,a,b)>
	endm
IDirect3DDevice9_GetRenderTargetData macro p,a,b
	exitm<[p].GetRenderTargetData(p,a,b)>
	endm
IDirect3DDevice9_GetFrontBufferData macro p,a,b
	exitm<[p].GetFrontBufferData(p,a,b)>
	endm
IDirect3DDevice9_StretchRect macro p,a,b,c,d,e
	exitm<[p].StretchRect(p,a,b,c,d,e)>
	endm
IDirect3DDevice9_ColorFill macro p,a,b,c
	exitm<[p].ColorFill(p,a,b,c)>
	endm
IDirect3DDevice9_CreateOffscreenPlainSurface macro p,a,b,c,d,e,f
	exitm<[p].CreateOffscreenPlainSurface(p,a,b,c,d,e,f)>
	endm
IDirect3DDevice9_SetRenderTarget macro p,a,b
	exitm<[p].SetRenderTarget(p,a,b)>
	endm
IDirect3DDevice9_GetRenderTarget macro p,a,b
	exitm<[p].GetRenderTarget(p,a,b)>
	endm
IDirect3DDevice9_SetDepthStencilSurface macro p,a
	exitm<[p].SetDepthStencilSurface(p,a)>
	endm
IDirect3DDevice9_GetDepthStencilSurface macro p,a
	exitm<[p].GetDepthStencilSurface(p,a)>
	endm
IDirect3DDevice9_BeginScene macro p
	exitm<[p].BeginScene(p)>
	endm
IDirect3DDevice9_EndScene macro p
	exitm<[p].EndScene(p)>
	endm
IDirect3DDevice9_Clear macro p,a,b,c,d,e,f
	exitm<[p].Clear(p,a,b,c,d,e,f)>
	endm
IDirect3DDevice9_SetTransform macro p,a,b
	exitm<[p].SetTransform(p,a,b)>
	endm
IDirect3DDevice9_GetTransform macro p,a,b
	exitm<[p].GetTransform(p,a,b)>
	endm
IDirect3DDevice9_MultiplyTransform macro p,a,b
	exitm<[p].MultiplyTransform(p,a,b)>
	endm
IDirect3DDevice9_SetViewport macro p,a
	exitm<[p].SetViewport(p,a)>
	endm
IDirect3DDevice9_GetViewport macro p,a
	exitm<[p].GetViewport(p,a)>
	endm
IDirect3DDevice9_SetMaterial macro p,a
	exitm<[p].SetMaterial(p,a)>
	endm
IDirect3DDevice9_GetMaterial macro p,a
	exitm<[p].GetMaterial(p,a)>
	endm
IDirect3DDevice9_SetLight macro p,a,b
	exitm<[p].SetLight(p,a,b)>
	endm
IDirect3DDevice9_GetLight macro p,a,b
	exitm<[p].GetLight(p,a,b)>
	endm
IDirect3DDevice9_LightEnable macro p,a,b
	exitm<[p].LightEnable(p,a,b)>
	endm
IDirect3DDevice9_GetLightEnable macro p,a,b
	exitm<[p].GetLightEnable(p,a,b)>
	endm
IDirect3DDevice9_SetClipPlane macro p,a,b
	exitm<[p].SetClipPlane(p,a,b)>
	endm
IDirect3DDevice9_GetClipPlane macro p,a,b
	exitm<[p].GetClipPlane(p,a,b)>
	endm
IDirect3DDevice9_SetRenderState macro p,a,b
	exitm<[p].SetRenderState(p,a,b)>
	endm
IDirect3DDevice9_GetRenderState macro p,a,b
	exitm<[p].GetRenderState(p,a,b)>
	endm
IDirect3DDevice9_CreateStateBlock macro p,a,b
	exitm<[p].CreateStateBlock(p,a,b)>
	endm
IDirect3DDevice9_BeginStateBlock macro p
	exitm<[p].BeginStateBlock(p)>
	endm
IDirect3DDevice9_EndStateBlock macro p,a
	exitm<[p].EndStateBlock(p,a)>
	endm
IDirect3DDevice9_SetClipStatus macro p,a
	exitm<[p].SetClipStatus(p,a)>
	endm
IDirect3DDevice9_GetClipStatus macro p,a
	exitm<[p].GetClipStatus(p,a)>
	endm
IDirect3DDevice9_GetTexture macro p,a,b
	exitm<[p].GetTexture(p,a,b)>
	endm
IDirect3DDevice9_SetTexture macro p,a,b
	exitm<[p].SetTexture(p,a,b)>
	endm
IDirect3DDevice9_GetTextureStageState macro p,a,b,c
	exitm<[p].GetTextureStageState(p,a,b,c)>
	endm
IDirect3DDevice9_SetTextureStageState macro p,a,b,c
	exitm<[p].SetTextureStageState(p,a,b,c)>
	endm
IDirect3DDevice9_GetSamplerState macro p,a,b,c
	exitm<[p].GetSamplerState(p,a,b,c)>
	endm
IDirect3DDevice9_SetSamplerState macro p,a,b,c
	exitm<[p].SetSamplerState(p,a,b,c)>
	endm
IDirect3DDevice9_ValidateDevice macro p,a
	exitm<[p].ValidateDevice(p,a)>
	endm
IDirect3DDevice9_SetPaletteEntries macro p,a,b
	exitm<[p].SetPaletteEntries(p,a,b)>
	endm
IDirect3DDevice9_GetPaletteEntries macro p,a,b
	exitm<[p].GetPaletteEntries(p,a,b)>
	endm
IDirect3DDevice9_SetCurrentTexturePalette macro p,a
	exitm<[p].SetCurrentTexturePalette(p,a)>
	endm
IDirect3DDevice9_GetCurrentTexturePalette macro p,a
	exitm<[p].GetCurrentTexturePalette(p,a)>
	endm
IDirect3DDevice9_SetScissorRect macro p,a
	exitm<[p].SetScissorRect(p,a)>
	endm
IDirect3DDevice9_GetScissorRect macro p,a
	exitm<[p].GetScissorRect(p,a)>
	endm
IDirect3DDevice9_SetSoftwareVertexProcessing macro p,a
	exitm<[p].SetSoftwareVertexProcessing(p,a)>
	endm
IDirect3DDevice9_GetSoftwareVertexProcessing macro p
	exitm<[p].GetSoftwareVertexProcessing(p)>
	endm
IDirect3DDevice9_SetNPatchMode macro p,a
	exitm<[p].SetNPatchMode(p,a)>
	endm
IDirect3DDevice9_GetNPatchMode macro p
	exitm<[p].GetNPatchMode(p)>
	endm
IDirect3DDevice9_DrawPrimitive macro p,a,b,c
	exitm<[p].DrawPrimitive(p,a,b,c)>
	endm
IDirect3DDevice9_DrawIndexedPrimitive macro p,a,b,c,d,e,f
	exitm<[p].DrawIndexedPrimitive(p,a,b,c,d,e,f)>
	endm
IDirect3DDevice9_DrawPrimitiveUP macro p,a,b,c,d
	exitm<[p].DrawPrimitiveUP(p,a,b,c,d)>
	endm
IDirect3DDevice9_DrawIndexedPrimitiveUP macro p,a,b,c,d,e,f,g,h
	exitm<[p].DrawIndexedPrimitiveUP(p,a,b,c,d,e,f,g,h)>
	endm
IDirect3DDevice9_ProcessVertices macro p,a,b,c,d,e,f
	exitm<[p].ProcessVertices(p,a,b,c,d,e,f)>
	endm
IDirect3DDevice9_CreateVertexDeclaration macro p,a,b
	exitm<[p].CreateVertexDeclaration(p,a,b)>
	endm
IDirect3DDevice9_SetVertexDeclaration macro p,a
	exitm<[p].SetVertexDeclaration(p,a)>
	endm
IDirect3DDevice9_GetVertexDeclaration macro p,a
	exitm<[p].GetVertexDeclaration(p,a)>
	endm
IDirect3DDevice9_SetFVF macro p,a
	exitm<[p].SetFVF(p,a)>
	endm
IDirect3DDevice9_GetFVF macro p,a
	exitm<[p].GetFVF(p,a)>
	endm
IDirect3DDevice9_CreateVertexShader macro p,a,b
	exitm<[p].CreateVertexShader(p,a,b)>
	endm
IDirect3DDevice9_SetVertexShader macro p,a
	exitm<[p].SetVertexShader(p,a)>
	endm
IDirect3DDevice9_GetVertexShader macro p,a
	exitm<[p].GetVertexShader(p,a)>
	endm
IDirect3DDevice9_SetVertexShaderConstantF macro p,a,b,c
	exitm<[p].SetVertexShaderConstantF(p,a,b,c)>
	endm
IDirect3DDevice9_GetVertexShaderConstantF macro p,a,b,c
	exitm<[p].GetVertexShaderConstantF(p,a,b,c)>
	endm
IDirect3DDevice9_SetVertexShaderConstantI macro p,a,b,c
	exitm<[p].SetVertexShaderConstantI(p,a,b,c)>
	endm
IDirect3DDevice9_GetVertexShaderConstantI macro p,a,b,c
	exitm<[p].GetVertexShaderConstantI(p,a,b,c)>
	endm
IDirect3DDevice9_SetVertexShaderConstantB macro p,a,b,c
	exitm<[p].SetVertexShaderConstantB(p,a,b,c)>
	endm
IDirect3DDevice9_GetVertexShaderConstantB macro p,a,b,c
	exitm<[p].GetVertexShaderConstantB(p,a,b,c)>
	endm
IDirect3DDevice9_SetStreamSource macro p,a,b,c,d
	exitm<[p].SetStreamSource(p,a,b,c,d)>
	endm
IDirect3DDevice9_GetStreamSource macro p,a,b,c,d
	exitm<[p].GetStreamSource(p,a,b,c,d)>
	endm
IDirect3DDevice9_SetStreamSourceFreq macro p,a,b
	exitm<[p].SetStreamSourceFreq(p,a,b)>
	endm
IDirect3DDevice9_GetStreamSourceFreq macro p,a,b
	exitm<[p].GetStreamSourceFreq(p,a,b)>
	endm
IDirect3DDevice9_SetIndices macro p,a
	exitm<[p].SetIndices(p,a)>
	endm
IDirect3DDevice9_GetIndices macro p,a
	exitm<[p].GetIndices(p,a)>
	endm
IDirect3DDevice9_CreatePixelShader macro p,a,b
	exitm<[p].CreatePixelShader(p,a,b)>
	endm
IDirect3DDevice9_SetPixelShader macro p,a
	exitm<[p].SetPixelShader(p,a)>
	endm
IDirect3DDevice9_GetPixelShader macro p,a
	exitm<[p].GetPixelShader(p,a)>
	endm
IDirect3DDevice9_SetPixelShaderConstantF macro p,a,b,c
	exitm<[p].SetPixelShaderConstantF(p,a,b,c)>
	endm
IDirect3DDevice9_GetPixelShaderConstantF macro p,a,b,c
	exitm<[p].GetPixelShaderConstantF(p,a,b,c)>
	endm
IDirect3DDevice9_SetPixelShaderConstantI macro p,a,b,c
	exitm<[p].SetPixelShaderConstantI(p,a,b,c)>
	endm
IDirect3DDevice9_GetPixelShaderConstantI macro p,a,b,c
	exitm<[p].GetPixelShaderConstantI(p,a,b,c)>
	endm
IDirect3DDevice9_SetPixelShaderConstantB macro p,a,b,c
	exitm<[p].SetPixelShaderConstantB(p,a,b,c)>
	endm
IDirect3DDevice9_GetPixelShaderConstantB macro p,a,b,c
	exitm<[p].GetPixelShaderConstantB(p,a,b,c)>
	endm
IDirect3DDevice9_DrawRectPatch macro p,a,b,c
	exitm<[p].DrawRectPatch(p,a,b,c)>
	endm
IDirect3DDevice9_DrawTriPatch macro p,a,b,c
	exitm<[p].DrawTriPatch(p,a,b,c)>
	endm
IDirect3DDevice9_DeletePatch macro p,a
	exitm<[p].DeletePatch(p,a)>
	endm
IDirect3DDevice9_CreateQuery macro p,a,b
	exitm<[p].CreateQuery(p,a,b)>
	endm

IDirect3DStateBlock9	STRUC
;;** IUnknown methods **
QueryInterface		PVOID ?
AddRef			PVOID ?
Release			PVOID ?
;;** IDirect3DStateBlock9 methods **
GetDevice		PVOID ?
Capture			PVOID ?
Apply			PVOID ?
ifdef D3D_DEBUG_INFO
CreationCallStack	LPCWSTR ?
endif
IDirect3DStateBlock9	ENDS
LPDIRECT3DSTATEBLOCK9	typedef ptr IDirect3DStateBlock9
PDIRECT3DSTATEBLOCK9	typedef ptr IDirect3DStateBlock9

IDirect3DStateBlock9_QueryInterface macro p,a,b
	exitm<[p].QueryInterface(p,a,b)>
	endm
IDirect3DStateBlock9_AddRef macro p
	exitm<[p].AddRef(p)>
	endm
IDirect3DStateBlock9_Release macro p
	exitm<[p].Release(p)>
	endm
IDirect3DStateBlock9_GetDevice macro p,a
	exitm<[p].GetDevice(p,a)>
	endm
IDirect3DStateBlock9_Capture macro p
	exitm<[p].Capture(p)>
	endm
IDirect3DStateBlock9_Apply macro p
	exitm<[p].Apply(p)>
	endm

IDirect3DSwapChain9	STRUC
;;** IUnknown methods **
QueryInterface		PVOID ?
AddRef			PVOID ?
Release			PVOID ?
;;** IDirect3DSwapChain9 methods **
Present			PVOID ?
GetFrontBufferData	PVOID ?
GetBackBuffer		PVOID ?
GetRasterStatus		PVOID ?
GetDisplayMode		PVOID ?
GetDevice		PVOID ?
GetPresentParameters	PVOID ?
ifdef D3D_DEBUG_INFO
PresentParameters	D3DPRESENT_PARAMETERS ?
DisplayMode		D3DDISPLAYMODE ?
CreationCallStack	LPCWSTR ?
endif
IDirect3DSwapChain9	ENDS
LPDIRECT3DSWAPCHAIN9	typedef ptr IDirect3DSwapChain9
PDIRECT3DSWAPCHAIN9	typedef ptr IDirect3DSwapChain9

IDirect3DSwapChain9_QueryInterface macro p,a,b
	exitm<[p].QueryInterface(p,a,b)>
	endm
IDirect3DSwapChain9_AddRef macro p
	exitm<[p].AddRef(p)>
	endm
IDirect3DSwapChain9_Release macro p
	exitm<[p].Release(p)>
	endm
IDirect3DSwapChain9_Present macro p,a,b,c,d,e
	exitm<[p].Present(p,a,b,c,d,e)>
	endm
IDirect3DSwapChain9_GetFrontBufferData macro p,a
	exitm<[p].GetFrontBufferData(p,a)>
	endm
IDirect3DSwapChain9_GetBackBuffer macro p,a,b,c
	exitm<[p].GetBackBuffer(p,a,b,c)>
	endm
IDirect3DSwapChain9_GetRasterStatus macro p,a
	exitm<[p].GetRasterStatus(p,a)>
	endm
IDirect3DSwapChain9_GetDisplayMode macro p,a
	exitm<[p].GetDisplayMode(p,a)>
	endm
IDirect3DSwapChain9_GetDevice macro p,a
	exitm<[p].GetDevice(p,a)>
	endm
IDirect3DSwapChain9_GetPresentParameters macro p,a
	exitm<[p].GetPresentParameters(p,a)>
	endm


IDirect3DResource9	STRUC
;;** IUnknown methods **
QueryInterface		PVOID ?
AddRef			PVOID ?
Release			PVOID ?
;;** IDirect3DResource9 methods **
GetDevice		PVOID ?
SetPrivateData		PVOID ?
GetPrivateData		PVOID ?
FreePrivateData		PVOID ?
SetPriority		PVOID ?
GetPriority		PVOID ?
PreLoad			PVOID ?
GetType			PVOID ?
IDirect3DResource9	ENDS
LPDIRECT3DRESOURCE9	typedef ptr IDirect3DResource9
PDIRECT3DRESOURCE9	typedef ptr IDirect3DResource9

IDirect3DResource9_QueryInterface macro p,a,b
	exitm<[p].QueryInterface(p,a,b)>
	endm
IDirect3DResource9_AddRef macro p
	exitm<[p].AddRef(p)>
	endm
IDirect3DResource9_Release macro p
	exitm<[p].Release(p)>
	endm
IDirect3DResource9_GetDevice macro p,a
	exitm<[p].GetDevice(p,a)>
	endm
IDirect3DResource9_SetPrivateData macro p,a,b,c,d
	exitm<[p].SetPrivateData(p,a,b,c,d)>
	endm
IDirect3DResource9_GetPrivateData macro p,a,b,c
	exitm<[p].GetPrivateData(p,a,b,c)>
	endm
IDirect3DResource9_FreePrivateData macro p,a
	exitm<[p].FreePrivateData(p,a)>
	endm
IDirect3DResource9_SetPriority macro p,a
	exitm<[p].SetPriority(p,a)>
	endm
IDirect3DResource9_GetPriority macro p
	exitm<[p].GetPriority(p)>
	endm
IDirect3DResource9_PreLoad macro p
	exitm<[p].Preoad(p)>
	endm
IDirect3DResource9_GetType macro p
	exitm<[p].GetType(p)>
	endm

IDirect3DVertexDeclaration9 STRUC
;;** IUnknown methods **
QueryInterface		PVOID ?
AddRef			PVOID ?
Release			PVOID ?
;;** IDirect3DVertexDeclaration9 methods **
GetDevice		PVOID ?
GetDeclaration		PVOID ?
ifdef D3D_DEBUG_INFO
CreationCallStack	LPCWSTR ?
endif
IDirect3DVertexDeclaration9 ENDS
LPDIRECT3DVERTEXDECLARATION9 typedef ptr IDirect3DVertexDeclaration9
PDIRECT3DVERTEXDECLARATION9 typedef ptr IDirect3DVertexDeclaration9

IDirect3DVertexDeclaration9_QueryInterface macro p,a,b
	exitm<[p].QueryInterface(p,a,b)>
	endm
IDirect3DVertexDeclaration9_AddRef macro p
	exitm<[p].AddRef(p)>
	endm
IDirect3DVertexDeclaration9_Release macro p
	exitm<[p].Release(p)>
	endm
IDirect3DVertexDeclaration9_GetDevice macro p,a
	exitm<[p].GetDevice(p,a)>
	endm
IDirect3DVertexDeclaration9_GetDeclaration macro p,a,b
	exitm<[p].GetDeclaration(p,a,b)>
	endm

IDirect3DVertexShader9	STRUC
;;** IUnknown methods **
QueryInterface		PVOID ?
AddRef			PVOID ?
Release			PVOID ?
;;** IDirect3DVertexShader9 methods **
GetDevice		PVOID ?
GetFunction		PVOID ?
ifdef D3D_DEBUG_INFO
Version			dd ?
CreationCallStack	LPCWSTR ?
endif
IDirect3DVertexShader9	ENDS
LPDIRECT3DVERTEXSHADER9 typedef ptr IDirect3DVertexShader9
PDIRECT3DVERTEXSHADER9	typedef ptr IDirect3DVertexShader9

IDirect3DVertexShader9_QueryInterface macro p,a,b
	exitm<[p].QueryInterface(p,a,b)>
	endm
IDirect3DVertexShader9_AddRef macro p
	exitm<[p].AddRef(p)>
	endm
IDirect3DVertexShader9_Release macro p
	exitm<[p].Release(p)>
	endm
IDirect3DVertexShader9_GetDevice macro p,a
	exitm<[p].GetDevice(p,a)>
	endm
IDirect3DVertexShader9_GetFunction macro p,a,b
	exitm<[p].GetFunction(p,a,b)>
	endm


IDirect3DPixelShader9	STRUC
;;** IUnknown methods **
QueryInterface		PVOID ?
AddRef			PVOID ?
Release			PVOID ?
;;** IDirect3DPixelShader9 methods **
GetDevice		PVOID ?
GetFunction		PVOID ?
ifdef D3D_DEBUG_INFO
Version			dd ?
CreationCallStack	LPCWSTR ?
endif
IDirect3DPixelShader9	ENDS
LPDIRECT3DPIXELSHADER9	typedef ptr IDirect3DPixelShader9
PDIRECT3DPIXELSHADER9	typedef ptr IDirect3DPixelShader9

IDirect3DPixelShader9_QueryInterface macro p,a,b
	exitm<[p].QueryInterface(p,a,b)>
	endm
IDirect3DPixelShader9_AddRef macro p
	exitm<[p].AddRef(p)>
	endm
IDirect3DPixelShader9_Release macro p
	exitm<[p].Release(p)>
	endm
IDirect3DPixelShader9_GetDevice macro p,a
	exitm<[p].GetDevice(p,a)>
	endm
IDirect3DPixelShader9_GetFunction macro p,a,b
	exitm<[p].GetFunction(p,a,b)>
	endm

IDirect3DBaseTexture9	STRUC
;;** IUnknown methods **
QueryInterface		PVOID ?
AddRef			PVOID ?
Release			PVOID ?
;;** IDirect3DResource9 methods **
GetDevice		PVOID ?
SetPrivateData		PVOID ?
GetPrivateData		PVOID ?
FreePrivateData		PVOID ?
SetPriority		PVOID ?
GetPriority		PVOID ?
PreLoad			PVOID ?
GetType			PVOID ?
SetLOD			PVOID ?
GetLOD			PVOID ?
GetLevelCount		PVOID ?
SetAutoGenFilterType	PVOID ?
GetAutoGenFilterType	PVOID ?
GenerateMipSubLevels	PVOID ?
IDirect3DBaseTexture9	ENDS
LPDIRECT3DBASETEXTURE9	typedef ptr IDirect3DBaseTexture9
PDIRECT3DBASETEXTURE9	typedef ptr IDirect3DBaseTexture9

IDirect3DBaseTexture9_QueryInterface macro p,a,b
	exitm<[p].QueryInterface(p,a,b)>
	endm
IDirect3DBaseTexture9_AddRef macro p
	exitm<[p].AddRef(p)>
	endm
IDirect3DBaseTexture9_Release macro p
	exitm<[p].Release(p)>
	endm
IDirect3DBaseTexture9_GetDevice macro p,a
	exitm<[p].GetDevice(p,a)>
	endm
IDirect3DBaseTexture9_SetPrivateData macro p,a,b,c,d
	exitm<[p].SetPrivateData(p,a,b,c,d)>
	endm
IDirect3DBaseTexture9_GetPrivateData macro p,a,b,c
	exitm<[p].GetPrivateData(p,a,b,c)>
	endm
IDirect3DBaseTexture9_FreePrivateData macro p,a
	exitm<[p].FreePrivateData(p,a)>
	endm
IDirect3DBaseTexture9_SetPriority macro p,a
	exitm<[p].SetPriority(p,a)>
	endm
IDirect3DBaseTexture9_GetPriority macro p
	exitm<[p].GetPriority(p)>
	endm
IDirect3DBaseTexture9_PreLoad macro p
	exitm<[p].Preoad(p)>
	endm
IDirect3DBaseTexture9_GetType macro p
	exitm<[p].GetType(p)>
	endm
IDirect3DBaseTexture9_SetLOD macro p,a
	exitm<[p].SetLOD(p,a)>
	endm
IDirect3DBaseTexture9_GetLOD macro p
	exitm<[p].GetLOD(p)>
	endm
IDirect3DBaseTexture9_GetLevelCount macro p
	exitm<[p].GetLevelCount(p)>
	endm
IDirect3DBaseTexture9_SetAutoGenFilterType macro p,a
	exitm<[p].SetAutoGenFilterType(p,a)>
	endm
IDirect3DBaseTexture9_GetAutoGenFilterType macro p
	exitm<[p].GetAutoGenFilterType(p)>
	endm
IDirect3DBaseTexture9_GenerateMipSubLevels macro p
	exitm<[p].GenerateMipSubevels(p)>
	endm

IDirect3DTexture9	STRUC
;;** IUnknown methods **
QueryInterface		PVOID ?
AddRef			PVOID ?
Release			PVOID ?
;;** IDirect3DBaseTexture9 methods **
GetDevice		PVOID ?
SetPrivateData		PVOID ?
GetPrivateData		PVOID ?
FreePrivateData		PVOID ?
SetPriority		PVOID ?
GetPriority		PVOID ?
PreLoad			PVOID ?
GetType			PVOID ?
SetLOD			PVOID ?
GetLOD			PVOID ?
GetLevelCount		PVOID ?
SetAutoGenFilterType	PVOID ?
GetAutoGenFilterType	PVOID ?
GenerateMipSubLevels	PVOID ?
GetLevelDesc		PVOID ?
GetSurfaceLevel		PVOID ?
LockRect		PVOID ?
UnlockRect		PVOID ?
AddDirtyRect		PVOID ?
ifdef D3D_DEBUG_INFO
_Name			LPCWSTR ?
Width			UINT ?
Height			UINT ?
Levels			UINT ?
Usage			dd ?
Format			D3DFORMAT ?
Pool			D3DPOOL ?
Priority		dd ?
LOD			dd ?
FilterType		D3DTEXTUREFILTERTYPE ?
LockCount		UINT ?
CreationCallStack	LPCWSTR ?
endif
IDirect3DTexture9	ENDS
LPDIRECT3DTEXTURE9	typedef ptr IDirect3DTexture9
PDIRECT3DTEXTURE9	typedef ptr IDirect3DTexture9

IDirect3DTexture9_QueryInterface macro p,a,b
	exitm<[p].QueryInterface(p,a,b)>
	endm
IDirect3DTexture9_AddRef macro p
	exitm<[p].AddRef(p)>
	endm
IDirect3DTexture9_Release macro p
	exitm<[p].Release(p)>
	endm
IDirect3DTexture9_GetDevice macro p,a
	exitm<[p].GetDevice(p,a)>
	endm
IDirect3DTexture9_SetPrivateData macro p,a,b,c,d
	exitm<[p].SetPrivateData(p,a,b,c,d)>
	endm
IDirect3DTexture9_GetPrivateData macro p,a,b,c
	exitm<[p].GetPrivateData(p,a,b,c)>
	endm
IDirect3DTexture9_FreePrivateData macro p,a
	exitm<[p].FreePrivateData(p,a)>
	endm
IDirect3DTexture9_SetPriority macro p,a
	exitm<[p].SetPriority(p,a)>
	endm
IDirect3DTexture9_GetPriority macro p
	exitm<[p].GetPriority(p)>
	endm
IDirect3DTexture9_PreLoad macro p
	exitm<[p].Preoad(p)>
	endm
IDirect3DTexture9_GetType macro p
	exitm<[p].GetType(p)>
	endm
IDirect3DTexture9_SetLOD macro p,a
	exitm<[p].SetLOD(p,a)>
	endm
IDirect3DTexture9_GetLOD macro p
	exitm<[p].GetLOD(p)>
	endm
IDirect3DTexture9_GetLevelCount macro p
	exitm<[p].GetLevelCount(p)>
	endm
IDirect3DTexture9_SetAutoGenFilterType macro p,a
	exitm<[p].SetAutoGenFilterType(p,a)>
	endm
IDirect3DTexture9_GetAutoGenFilterType macro p
	exitm<[p].GetAutoGenFilterType(p)>
	endm
IDirect3DTexture9_GenerateMipSubLevels macro p
	exitm<[p].GenerateMipSubevels(p)>
	endm
IDirect3DTexture9_GetLevelDesc macro p,a,b
	exitm<[p].GetLevelDesc(p,a,b)>
	endm
IDirect3DTexture9_GetSurfaceLevel macro p,a,b
	exitm<[p].GetSurfaceevel(p,a,b)>
	endm
IDirect3DTexture9_LockRect macro p,a,b,c,d
	exitm<[p].LockRect(p,a,b,c,d)>
	endm
IDirect3DTexture9_UnlockRect macro p,a
	exitm<[p].UnlockRect(p,a)>
	endm
IDirect3DTexture9_AddDirtyRect macro p,a
	exitm<[p].AddDirtyRect(p,a)>
	endm

IDirect3DVolumeTexture9 STRUC
;;** IUnknown methods **
QueryInterface		PVOID ?
AddRef			PVOID ?
Release			PVOID ?
;;** IDirect3DBaseTexture9 methods **
GetDevice		PVOID ?
SetPrivateData		PVOID ?
GetPrivateData		PVOID ?
FreePrivateData		PVOID ?
SetPriority		PVOID ?
GetPriority		PVOID ?
PreLoad			PVOID ?
GetType			PVOID ?
SetLOD			PVOID ?
GetLOD			PVOID ?
GetLevelCount		PVOID ?
SetAutoGenFilterType	PVOID ?
GetAutoGenFilterType	PVOID ?
GenerateMipSubLevels	PVOID ?
GetLevelDesc		PVOID ?
GetVolumeLevel		PVOID ?
LockBox			PVOID ?
UnlockBox		PVOID ?
AddDirtyBox		PVOID ?
ifdef D3D_DEBUG_INFO
_Name			LPCWSTR ?
Width			UINT ?
Height			UINT ?
Depth			UINT ?
Levels			UINT ?
Usage			dd ?
Format			D3DFORMAT ?
Pool			D3DPOOL ?
Priority		dd ?
LOD			dd ?
FilterType		D3DTEXTUREFILTERTYPE ?
LockCount		UINT ?
CreationCallStack	LPCWSTR ?
endif
IDirect3DVolumeTexture9 ENDS
LPDIRECT3DVOLUMETEXTURE9 typedef ptr IDirect3DVolumeTexture9
PDIRECT3DVOLUMETEXTURE9 typedef ptr IDirect3DVolumeTexture9

IDirect3DVolumeTexture9_QueryInterface macro p,a,b
	exitm<[p].QueryInterface(p,a,b)>
	endm
IDirect3DVolumeTexture9_AddRef macro p
	exitm<[p].AddRef(p)>
	endm
IDirect3DVolumeTexture9_Release macro p
	exitm<[p].Release(p)>
	endm
IDirect3DVolumeTexture9_GetDevice macro p,a
	exitm<[p].GetDevice(p,a)>
	endm
IDirect3DVolumeTexture9_SetPrivateData macro p,a,b,c,d
	exitm<[p].SetPrivateData(p,a,b,c,d)>
	endm
IDirect3DVolumeTexture9_GetPrivateData macro p,a,b,c
	exitm<[p].GetPrivateData(p,a,b,c)>
	endm
IDirect3DVolumeTexture9_FreePrivateData macro p,a
	exitm<[p].FreePrivateData(p,a)>
	endm
IDirect3DVolumeTexture9_SetPriority macro p,a
	exitm<[p].SetPriority(p,a)>
	endm
IDirect3DVolumeTexture9_GetPriority macro p
	exitm<[p].GetPriority(p)>
	endm
IDirect3DVolumeTexture9_PreLoad macro p
	exitm<[p].Preoad(p)>
	endm
IDirect3DVolumeTexture9_GetType macro p
	exitm<[p].GetType(p)>
	endm
IDirect3DVolumeTexture9_SetLOD macro p,a
	exitm<[p].SetLOD(p,a)>
	endm
IDirect3DVolumeTexture9_GetLOD macro p
	exitm<[p].GetLOD(p)>
	endm
IDirect3DVolumeTexture9_GetLevelCount macro p
	exitm<[p].GetLevelCount(p)>
	endm
IDirect3DVolumeTexture9_SetAutoGenFilterType macro p,a
	exitm<[p].SetAutoGenFilterType(p,a)>
	endm
IDirect3DVolumeTexture9_GetAutoGenFilterType macro p
	exitm<[p].GetAutoGenFilterType(p)>
	endm
IDirect3DVolumeTexture9_GenerateMipSubLevels macro p
	exitm<[p].GenerateMipSubevels(p)>
	endm
IDirect3DVolumeTexture9_GetLevelDesc macro p,a,b
	exitm<[p].GetLevelDesc(p,a,b)>
	endm
IDirect3DVolumeTexture9_GetVolumeLevel macro p,a,b
	exitm<[p].GetVolumeevel(p,a,b)>
	endm
IDirect3DVolumeTexture9_LockBox macro p,a,b,c,d
	exitm<[p].LockBox(p,a,b,c,d)>
	endm
IDirect3DVolumeTexture9_UnlockBox macro p,a
	exitm<[p].UnlockBox(p,a)>
	endm
IDirect3DVolumeTexture9_AddDirtyBox macro p,a
	exitm<[p].AddDirtyBox(p,a)>
	endm


IDirect3DCubeTexture9	STRUC
;;** IUnknown methods **
QueryInterface		PVOID ?
AddRef			PVOID ?
Release			PVOID ?
;;** IDirect3DBaseTexture9 methods **
GetDevice		PVOID ?
SetPrivateData		PVOID ?
GetPrivateData		PVOID ?
FreePrivateData		PVOID ?
SetPriority		PVOID ?
GetPriority		PVOID ?
PreLoad			PVOID ?
GetType			PVOID ?
SetLOD			PVOID ?
GetLOD			PVOID ?
GetLevelCount		PVOID ?
SetAutoGenFilterType	PVOID ?
GetAutoGenFilterType	PVOID ?
GenerateMipSubLevels	PVOID ?
GetLevelDesc		PVOID ?
GetCubeMapSurface	PVOID ?
LockRect		PVOID ?
UnlockRect		PVOID ?
AddDirtyRect		PVOID ?
ifdef D3D_DEBUG_INFO
_Name			LPCWSTR ?
Width			UINT ?
Height			UINT ?
Levels			UINT ?
Usage			dd ?
Format			D3DFORMAT ?
Pool			D3DPOOL ?
Priority		dd ?
LOD			dd ?
FilterType		D3DTEXTUREFILTERTYPE ?
LockCount		UINT ?
CreationCallStack	LPCWSTR ?
endif
IDirect3DCubeTexture9	ENDS
LPDIRECT3DCUBETEXTURE9	typedef ptr IDirect3DCubeTexture9
PDIRECT3DCUBETEXTURE9	typedef ptr IDirect3DCubeTexture9

IDirect3DCubeTexture9_QueryInterface macro p,a,b
	exitm<[p].QueryInterface(p,a,b)>
	endm
IDirect3DCubeTexture9_AddRef macro p
	exitm<[p].AddRef(p)>
	endm
IDirect3DCubeTexture9_Release macro p
	exitm<[p].Release(p)>
	endm
IDirect3DCubeTexture9_GetDevice macro p,a
	exitm<[p].GetDevice(p,a)>
	endm
IDirect3DCubeTexture9_SetPrivateData macro p,a,b,c,d
	exitm<[p].SetPrivateData(p,a,b,c,d)>
	endm
IDirect3DCubeTexture9_GetPrivateData macro p,a,b,c
	exitm<[p].GetPrivateData(p,a,b,c)>
	endm
IDirect3DCubeTexture9_FreePrivateData macro p,a
	exitm<[p].FreePrivateData(p,a)>
	endm
IDirect3DCubeTexture9_SetPriority macro p,a
	exitm<[p].SetPriority(p,a)>
	endm
IDirect3DCubeTexture9_GetPriority macro p
	exitm<[p].GetPriority(p)>
	endm
IDirect3DCubeTexture9_PreLoad macro p
	exitm<[p].Preoad(p)>
	endm
IDirect3DCubeTexture9_GetType macro p
	exitm<[p].GetType(p)>
	endm
IDirect3DCubeTexture9_SetLOD macro p,a
	exitm<[p].SetLOD(p,a)>
	endm
IDirect3DCubeTexture9_GetLOD macro p
	exitm<[p].GetLOD(p)>
	endm
IDirect3DCubeTexture9_GetLevelCount macro p
	exitm<[p].GetLevelCount(p)>
	endm
IDirect3DCubeTexture9_SetAutoGenFilterType macro p,a
	exitm<[p].SetAutoGenFilterType(p,a)>
	endm
IDirect3DCubeTexture9_GetAutoGenFilterType macro p
	exitm<[p].GetAutoGenFilterType(p)>
	endm
IDirect3DCubeTexture9_GenerateMipSubLevels macro p
	exitm<[p].GenerateMipSubevels(p)>
	endm
IDirect3DCubeTexture9_GetLevelDesc macro p,a,b
	exitm<[p].GetLevelDesc(p,a,b)>
	endm
IDirect3DCubeTexture9_GetCubeMapSurface macro p,a,b,c
	exitm<[p].GetCubeMapSurface(p,a,b,c)>
	endm
IDirect3DCubeTexture9_LockRect macro p,a,b,c,d,e
	exitm<[p].LockRect(p,a,b,c,d,e)>
	endm
IDirect3DCubeTexture9_UnlockRect macro p,a,b
	exitm<[p].UnlockRect(p,a,b)>
	endm
IDirect3DCubeTexture9_AddDirtyRect macro p,a,b
	exitm<[p].AddDirtyRect(p,a,b)>
	endm


IDirect3DVertexBuffer9	STRUC
;;** IUnknown methods **
QueryInterface		PVOID ?
AddRef			PVOID ?
Release			PVOID ?
;;** IDirect3DResource9 methods **
GetDevice		PVOID ?
SetPrivateData		PVOID ?
GetPrivateData		PVOID ?
FreePrivateData		PVOID ?
SetPriority		PVOID ?
GetPriority		PVOID ?
PreLoad			PVOID ?
GetType			PVOID ?
_Lock			PVOID ?
Unlock			PVOID ?
GetDesc			PVOID ?
ifdef D3D_DEBUG_INFO
Name			LPCWSTR ?
Length			UINT ?
Usage			dd ?
FVF			dd ?
Pool			D3DPOOL ?
Priority		dd ?
LockCount		UINT ?
CreationCallStack	LPCWSTR ?
endif
IDirect3DVertexBuffer9	ENDS
LPDIRECT3DVERTEXBUFFER9 typedef ptr IDirect3DVertexBuffer9
PDIRECT3DVERTEXBUFFER9	typedef ptr IDirect3DVertexBuffer9

IDirect3DVertexBuffer9_QueryInterface macro p,a,b
	exitm<[p].QueryInterface(p,a,b)>
	endm
IDirect3DVertexBuffer9_AddRef macro p
	exitm<[p].AddRef(p)>
	endm
IDirect3DVertexBuffer9_Release macro p
	exitm<[p].Release(p)>
	endm
IDirect3DVertexBuffer9_GetDevice macro p,a
	exitm<[p].GetDevice(p,a)>
	endm
IDirect3DVertexBuffer9_SetPrivateData macro p,a,b,c,d
	exitm<[p].SetPrivateData(p,a,b,c,d)>
	endm
IDirect3DVertexBuffer9_GetPrivateData macro p,a,b,c
	exitm<[p].GetPrivateData(p,a,b,c)>
	endm
IDirect3DVertexBuffer9_FreePrivateData macro p,a
	exitm<[p].FreePrivateData(p,a)>
	endm
IDirect3DVertexBuffer9_SetPriority macro p,a
	exitm<[p].SetPriority(p,a)>
	endm
IDirect3DVertexBuffer9_GetPriority macro p
	exitm<[p].GetPriority(p)>
	endm
IDirect3DVertexBuffer9_PreLoad macro p
	exitm<[p].Preoad(p)>
	endm
IDirect3DVertexBuffer9_GetType macro p
	exitm<[p].GetType(p)>
	endm
IDirect3DVertexBuffer9_Lock macro p,a,b,c,d
	exitm<[p]._Lock(p,a,b,c,d)>
	endm
IDirect3DVertexBuffer9_Unlock macro p
	exitm<[p].Unlock(p)>
	endm
IDirect3DVertexBuffer9_GetDesc macro p,a
	exitm<[p].GetDesc(p,a)>
	endm

IDirect3DIndexBuffer9	STRUC
;;** IUnknown methods **
QueryInterface		PVOID ?
AddRef			PVOID ?
Release			PVOID ?
;;** IDirect3DResource9 methods **
GetDevice		PVOID ?
SetPrivateData		PVOID ?
GetPrivateData		PVOID ?
FreePrivateData		PVOID ?
SetPriority		PVOID ?
GetPriority		PVOID ?
PreLoad			PVOID ?
GetType			PVOID ?
_Lock			PVOID ?
Unlock			PVOID ?
GetDesc			PVOID ?
ifdef D3D_DEBUG_INFO
Name			LPCWSTR ?
Length			UINT ?
Usage			dd ?
Format			D3DFORMAT ?
Pool			D3DPOOL ?
Priority		dd ?
LockCount		UINT ?
CreationCallStack	LPCWSTR ?
endif
IDirect3DIndexBuffer9	ENDS
LPDIRECT3DINDEXBUFFER9	typedef ptr IDirect3DIndexBuffer9
PDIRECT3DINDEXBUFFER9	typedef ptr IDirect3DIndexBuffer9

IDirect3DIndexBuffer9_QueryInterface macro p,a,b
	exitm<[p].QueryInterface(p,a,b)>
	endm
IDirect3DIndexBuffer9_AddRef macro p
	exitm<[p].AddRef(p)>
	endm
IDirect3DIndexBuffer9_Release macro p
	exitm<[p].Release(p)>
	endm
IDirect3DIndexBuffer9_GetDevice macro p,a
	exitm<[p].GetDevice(p,a)>
	endm
IDirect3DIndexBuffer9_SetPrivateData macro p,a,b,c,d
	exitm<[p].SetPrivateData(p,a,b,c,d)>
	endm
IDirect3DIndexBuffer9_GetPrivateData macro p,a,b,c
	exitm<[p].GetPrivateData(p,a,b,c)>
	endm
IDirect3DIndexBuffer9_FreePrivateData macro p,a
	exitm<[p].FreePrivateData(p,a)>
	endm
IDirect3DIndexBuffer9_SetPriority macro p,a
	exitm<[p].SetPriority(p,a)>
	endm
IDirect3DIndexBuffer9_GetPriority macro p
	exitm<[p].GetPriority(p)>
	endm
IDirect3DIndexBuffer9_PreLoad macro p
	exitm<[p].Preoad(p)>
	endm
IDirect3DIndexBuffer9_GetType macro p
	exitm<[p].GetType(p)>
	endm
IDirect3DIndexBuffer9_Lock macro p,a,b,c,d
	exitm<[p]._Lock(p,a,b,c,d)>
	endm
IDirect3DIndexBuffer9_Unlock macro p
	exitm<[p].Unlock(p)>
	endm
IDirect3DIndexBuffer9_GetDesc macro p,a
	exitm<[p].GetDesc(p,a)>
	endm

IDirect3DSurface9	STRUC
;;** IUnknown methods **
QueryInterface		PVOID ?
AddRef			PVOID ?
Release			PVOID ?
;;** IDirect3DResource9 methods **
GetDevice		PVOID ?
SetPrivateData		PVOID ?
GetPrivateData		PVOID ?
FreePrivateData		PVOID ?
SetPriority		PVOID ?
GetPriority		PVOID ?
PreLoad			PVOID ?
GetType			PVOID ?
GetContainer		PVOID ?
GetDesc			PVOID ?
LockRect		PVOID ?
UnlockRect		PVOID ?
GetDC			PVOID ?
ReleaseDC		PVOID ?
ifdef D3D_DEBUG_INFO
Name			LPCWSTR ?
Width			UINT ?
Height			UINT ?
Usage			dd ?
Format			D3DFORMAT ?
Pool			D3DPOOL ?
MultiSampleType		D3DMULTISAMPLE_TYPE ?
MultiSampleQuality	dd ?
Priority		dd ?
LockCount		UINT ?
DCCount			UINT ?
CreationCallStack	LPCWSTR ?
endif
IDirect3DSurface9	ENDS
LPDIRECT3DSURFACE9	typedef ptr IDirect3DSurface9
PDIRECT3DSURFACE9	typedef ptr IDirect3DSurface9

IDirect3DSurface9_QueryInterface macro p,a,b
	exitm<[p].QueryInterface(p,a,b)>
	endm
IDirect3DSurface9_AddRef macro p
	exitm<[p].AddRef(p)>
	endm
IDirect3DSurface9_Release macro p
	exitm<[p].Release(p)>
	endm
IDirect3DSurface9_GetDevice macro p,a
	exitm<[p].GetDevice(p,a)>
	endm
IDirect3DSurface9_SetPrivateData macro p,a,b,c,d
	exitm<[p].SetPrivateData(p,a,b,c,d)>
	endm
IDirect3DSurface9_GetPrivateData macro p,a,b,c
	exitm<[p].GetPrivateData(p,a,b,c)>
	endm
IDirect3DSurface9_FreePrivateData macro p,a
	exitm<[p].FreePrivateData(p,a)>
	endm
IDirect3DSurface9_SetPriority macro p,a
	exitm<[p].SetPriority(p,a)>
	endm
IDirect3DSurface9_GetPriority macro p
	exitm<[p].GetPriority(p)>
	endm
IDirect3DSurface9_PreLoad macro p
	exitm<[p].Preoad(p)>
	endm
IDirect3DSurface9_GetType macro p
	exitm<[p].GetType(p)>
	endm
IDirect3DSurface9_GetContainer macro p,a,b
	exitm<[p].GetContainer(p,a,b)>
	endm
IDirect3DSurface9_GetDesc macro p,a
	exitm<[p].GetDesc(p,a)>
	endm
IDirect3DSurface9_LockRect macro p,a,b,c
	exitm<[p].LockRect(p,a,b,c)>
	endm
IDirect3DSurface9_UnlockRect macro p
	exitm<[p].UnlockRect(p)>
	endm
IDirect3DSurface9_GetDC macro p,a
	exitm<[p].GetDC(p,a)>
	endm
IDirect3DSurface9_ReleaseDC macro p,a
	exitm<[p].ReleaseDC(p,a)>
	endm


IDirect3DVolume9	STRUC
;;** IUnknown methods **
QueryInterface		PVOID ?
AddRef			PVOID ?
Release			PVOID ?
;;** IDirect3DVolume9 methods **
GetDevice		PVOID ?
SetPrivateData		PVOID ?
GetPrivateData		PVOID ?
FreePrivateData		PVOID ?
GetContainer		PVOID ?
GetDesc			PVOID ?
LockBox			PVOID ?
UnlockBox		PVOID ?
ifdef D3D_DEBUG_INFO
_Name			LPCWSTR ?
Width			UINT ?
Height			UINT ?
Depth			UINT ?
Usage			dd ?
Format			D3DFORMAT ?
Pool			D3DPOOL ?
LockCount		UINT ?
CreationCallStack	LPCWSTR ?
endif
IDirect3DVolume9	ENDS
LPDIRECT3DVOLUME9	typedef ptr IDirect3DVolume9
PDIRECT3DVOLUME9	typedef ptr IDirect3DVolume9

IDirect3DVolume9_QueryInterface macro p,a,b
	exitm<[p].QueryInterface(p,a,b)>
	endm
IDirect3DVolume9_AddRef macro p
	exitm<[p].AddRef(p)>
	endm
IDirect3DVolume9_Release macro p
	exitm<[p].Release(p)>
	endm
IDirect3DVolume9_GetDevice macro p,a
	exitm<[p].GetDevice(p,a)>
	endm
IDirect3DVolume9_SetPrivateData macro p,a,b,c,d
	exitm<[p].SetPrivateData(p,a,b,c,d)>
	endm
IDirect3DVolume9_GetPrivateData macro p,a,b,c
	exitm<[p].GetPrivateData(p,a,b,c)>
	endm
IDirect3DVolume9_FreePrivateData macro p,a
	exitm<[p].FreePrivateData(p,a)>
	endm
IDirect3DVolume9_GetContainer macro p,a,b
	exitm<[p].GetContainer(p,a,b)>
	endm
IDirect3DVolume9_GetDesc macro p,a
	exitm<[p].GetDesc(p,a)>
	endm
IDirect3DVolume9_LockBox macro p,a,b,c
	exitm<[p].LockBox(p,a,b,c)>
	endm
IDirect3DVolume9_UnlockBox macro p
	exitm<[p].UnlockBox(p)>
	endm

IDirect3DQuery9		STRUC
;;** IUnknown methods **
QueryInterface		PVOID ?
AddRef			PVOID ?
Release			PVOID ?
;;** IDirect3DQuery9 methods **
GetDevice		PVOID ?
GetType			PVOID ?
GetDataSize		PVOID ?
Issue			PVOID ?
GetData			PVOID ?
ifdef D3D_DEBUG_INFO
_Type			D3DQUERYTYPE ?
DataSize		dd ?
CreationCallStack	LPCWSTR ?
endif
IDirect3DQuery9		ENDS
LPDIRECT3DQUERY9	typedef ptr IDirect3DQuery9
PDIRECT3DQUERY9		typedef ptr IDirect3DQuery9

IDirect3DQuery9_QueryInterface macro p,a,b
	exitm<[p].QueryInterface(p,a,b)>
	endm
IDirect3DQuery9_AddRef macro p
	exitm<[p].AddRef(p)>
	endm
IDirect3DQuery9_Release macro p
	exitm<[p].Release(p)>
	endm
IDirect3DQuery9_GetDevice macro p,a
	exitm<[p].GetDevice(p,a)>
	endm
IDirect3DQuery9_GetType macro p
	exitm<[p].GetType(p)>
	endm
IDirect3DQuery9_GetDataSize macro p
	exitm<[p].GetDataSize(p)>
	endm
IDirect3DQuery9_Issue macro p,a
	exitm<[p].Issue(p,a)>
	endm
IDirect3DQuery9_GetData macro p,a,b,c
	exitm<[p].GetData(p,a,b,c)>
	endm


;;***************************************************************************
;; Flags for SetPrivateData method on all D3D9 interfaces
;;
;; The passed pointer is an IUnknown ptr. The SizeOfData argument to SetPrivateData
;; must be set to sizeof(IUnknown*). Direct3D will call AddRef through this
;; pointer and Release when the private data is destroyed. The data will be
;; destroyed when another SetPrivateData with the same GUID is set, when
;; FreePrivateData is called, or when the D3D9 object is freed.
;;**************************************************************************
D3DSPD_IUNKNOWN		equ 0x00000001

;;***************************************************************************
;;
;; Flags for IDirect3D9::CreateDevice's BehaviorFlags
;;
;;**************************************************************************

D3DCREATE_FPU_PRESERVE	equ 0x00000002
D3DCREATE_MULTITHREADED equ 0x00000004

D3DCREATE_PUREDEVICE	equ 0x00000010
D3DCREATE_SOFTWARE_VERTEXPROCESSING equ 0x00000020
D3DCREATE_HARDWARE_VERTEXPROCESSING equ 0x00000040
D3DCREATE_MIXED_VERTEXPROCESSING equ 0x00000080

D3DCREATE_DISABLE_DRIVER_MANAGEMENT equ 0x00000100
D3DCREATE_ADAPTERGROUP_DEVICE equ 0x00000200
D3DCREATE_DISABLE_DRIVER_MANAGEMENT_EX equ 0x00000400

;; This flag causes the D3D runtime not to alter the focus
;; window in any way. Use with caution- the burden of supporting
;; focus management events (alt-tab, etc.) falls on the
;; application, and appropriate responses (switching display
;; mode, etc.) should be coded.
D3DCREATE_NOWINDOWCHANGES equ 0x00000800

;; D3D9Ex only --
ifndef D3D_DISABLE_9EX

;; Disable multithreading for software vertex processing
D3DCREATE_DISABLE_PSGP_THREADING equ 0x00002000
;; This flag enables present statistics on device.
D3DCREATE_ENABLE_PRESENTSTATS equ 0x00004000
;; This flag disables printscreen support in the runtime for this device
D3DCREATE_DISABLE_PRINTSCREEN equ 0x00008000

D3DCREATE_SCREENSAVER	equ 0x10000000


endif ;; NOT D3D_DISABLE_9EX
;; -- D3D9Ex only



;;***************************************************************************
;;
;; Parameter for IDirect3D9::CreateDevice's Adapter argument
;;
;;**************************************************************************

D3DADAPTER_DEFAULT	equ 0

;;***************************************************************************
;;
;; Flags for IDirect3D9::EnumAdapters
;;
;;**************************************************************************

;;
;; The D3DENUM_WHQL_LEVEL value has been retired for 9Ex and future versions,
;; but it needs to be defined here for compatibility with DX9 and earlier versions.
;; See the DirectX SDK for sample code on discovering driver signatures.
;;
D3DENUM_WHQL_LEVEL	equ 0x00000002

;; D3D9Ex only --
ifndef D3D_DISABLE_9EX

;; NO_DRIVERVERSION will not fill out the DriverVersion field, nor will the
;; DriverVersion be incorporated into the DeviceIdentifier GUID. WINNT only
D3DENUM_NO_DRIVERVERSION equ 0x00000004

endif ;; NOT D3D_DISABLE_9EX
;; -- D3D9Ex only


;;***************************************************************************
;;
;; Maximum number of back-buffers supported in DX9
;;
;;**************************************************************************

D3DPRESENT_BACK_BUFFERS_MAX equ 3

;; D3D9Ex only --
ifndef D3D_DISABLE_9EX

;;***************************************************************************
;;
;; Maximum number of back-buffers supported when apps use CreateDeviceEx
;;
;;**************************************************************************

D3DPRESENT_BACK_BUFFERS_MAX_EX equ 30

endif ;; NOT D3D_DISABLE_9EX
;; -- D3D9Ex only

;;***************************************************************************
;;
;; Flags for IDirect3DDevice9::SetGammaRamp
;;
;;**************************************************************************

D3DSGR_NO_CALIBRATION	equ 0x00000000
D3DSGR_CALIBRATE	equ 0x00000001

;;***************************************************************************
;;
;; Flags for IDirect3DDevice9::SetCursorPosition
;;
;;**************************************************************************

D3DCURSOR_IMMEDIATE_UPDATE equ 0x00000001

;;***************************************************************************
;;
;; Flags for IDirect3DSwapChain9::Present
;;
;;**************************************************************************

D3DPRESENT_DONOTWAIT	equ 0x00000001
D3DPRESENT_LINEAR_CONTENT equ 0x00000002

;; D3D9Ex only --
ifndef D3D_DISABLE_9EX

D3DPRESENT_DONOTFLIP		equ 0x00000004
D3DPRESENT_FLIPRESTART		equ 0x00000008
D3DPRESENT_VIDEO_RESTRICT_TO_MONITOR equ 0x00000010
D3DPRESENT_UPDATEOVERLAYONLY	equ 0x00000020
D3DPRESENT_HIDEOVERLAY		equ 0x00000040
D3DPRESENT_UPDATECOLORKEY	equ 0x00000080
D3DPRESENT_FORCEIMMEDIATE	equ 0x00000100

endif ;; NOT D3D_DISABLE_9EX
;; -- D3D9Ex only


;;***************************************************************************
;;
;; Flags for DrawPrimitive/DrawIndexedPrimitive
;;   Also valid for Begin/BeginIndexed
;;   Also valid for VertexBuffer::CreateVertexBuffer
;;**************************************************************************


;;
;;  DirectDraw error codes
;;
_FACD3D			equ 0x876
MAKE_D3DHRESULT macro code
	exitm<MAKE_HRESULT( 1, _FACD3D, code )>
	endm
MAKE_D3DSTATUS macro code
	exitm<MAKE_HRESULT( 0, _FACD3D, code )>
	endm

;;
;; Direct3D Errors
;;
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

;; D3D9Ex only --
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


;;********************
;; D3D9Ex interfaces
;;*******************

;HRESULT
Direct3DCreate9Ex proto WINAPI \
	    SDKVersion: UINT,
		      : ptr ptr IDirect3D9Ex


IDirect3D9Ex		STRUC
;;** IUnknown methods **
QueryInterface		PVOID ?
AddRef			PVOID ?
Release			PVOID ?
;;** IDirect3D9 methods **
GetAdapterCount		PVOID ?
GetAdapterIdentifier	PVOID ?
GetAdapterModeCount	PVOID ?
EnumAdapterModes	PVOID ?
GetAdapterDisplayMode	PVOID ?
CheckDeviceType		PVOID ?
CheckDeviceFormat	PVOID ?
CheckDeviceMultiSampleType PVOID ?
CheckDepthStencilMatch	PVOID ?
CheckDeviceFormatConversion PVOID ?
GetDeviceCaps		PVOID ?
GetAdapterMonitor	PVOID ?
CreateDevice		PVOID ?
GetAdapterModeCountEx	PVOID ?
EnumAdapterModesEx	PVOID ?
GetAdapterDisplayModeEx PVOID ?
CreateDeviceEx		PVOID ?
GetAdapterLUID		PVOID ?
IDirect3D9Ex		ENDS
LPDIRECT3D9EX		typedef ptr IDirect3D9Ex
PDIRECT3D9EX		typedef ptr IDirect3D9Ex

IDirect3D9Ex_QueryInterface macro p,a,b
	exitm<[p].QueryInterface(p,a,b)>
	endm
IDirect3D9Ex_AddRef macro p
	exitm<[p].AddRef(p)>
	endm
IDirect3D9Ex_Release macro p
	exitm<[p].Release(p)>
	endm
IDirect3D9Ex_GetAdapterCount macro p
	exitm<[p].GetAdapterCount(p)>
	endm
IDirect3D9Ex_GetAdapterIdentifier macro p,a,b,c
	exitm<[p].GetAdapterIdentifier(p,a,b,c)>
	endm
IDirect3D9Ex_GetAdapterModeCount macro p,a,b
	exitm<[p].GetAdapterModeCount(p,a,b)>
	endm
IDirect3D9Ex_EnumAdapterModes macro p,a,b,c,d
	exitm<[p].EnumAdapterModes(p,a,b,c,d)>
	endm
IDirect3D9Ex_GetAdapterDisplayMode macro p,a,b
	exitm<[p].GetAdapterDisplayMode(p,a,b)>
	endm
IDirect3D9Ex_CheckDeviceType macro p,a,b,c,d,e
	exitm<[p].CheckDeviceType(p,a,b,c,d,e)>
	endm
IDirect3D9Ex_CheckDeviceFormat macro p,a,b,c,d,e,f
	exitm<[p].CheckDeviceFormat(p,a,b,c,d,e,f)>
	endm
IDirect3D9Ex_CheckDeviceMultiSampleType macro p,a,b,c,d,e,f
	exitm<[p].CheckDeviceMultiSampleType(p,a,b,c,d,e,f)>
	endm
IDirect3D9Ex_CheckDepthStencilMatch macro p,a,b,c,d,e
	exitm<[p].CheckDepthStencilMatch(p,a,b,c,d,e)>
	endm
IDirect3D9Ex_CheckDeviceFormatConversion macro p,a,b,c,d
	exitm<[p].CheckDeviceFormatConversion(p,a,b,c,d)>
	endm
IDirect3D9Ex_GetDeviceCaps macro p,a,b,c
	exitm<[p].GetDeviceCaps(p,a,b,c)>
	endm
IDirect3D9Ex_GetAdapterMonitor macro p,a
	exitm<[p].GetAdapterMonitor(p,a)>
	endm
IDirect3D9Ex_CreateDevice macro p,a,b,c,d,e,f
	exitm<[p].CreateDevice(p,a,b,c,d,e,f)>
	endm
IDirect3D9Ex_GetAdapterModeCountEx macro p,a,b
	exitm<[p].GetAdapterModeCountEx(p,a,b)>
	endm
IDirect3D9Ex_EnumAdapterModesEx macro p,a,b,c,d
	exitm<[p].EnumAdapterModesEx(p,a,b,c,d)>
	endm
IDirect3D9Ex_GetAdapterDisplayModeEx macro p,a,b,c
	exitm<[p].GetAdapterDisplayModeEx(p,a,b,c)>
	endm
IDirect3D9Ex_CreateDeviceEx macro p,a,b,c,d,e,f,g
	exitm<[p].CreateDeviceEx(p,a,b,c,d,e,f,g)>
	endm
IDirect3D9Ex_GetAdapterLUID macro p,a,b
	exitm<[p].GetAdapterLUID(p,a,b)>
	endm


IDirect3DDevice9Ex	STRUC
;;** IUnknown methods **
QueryInterface		PVOID ?
AddRef			PVOID ?
Release			PVOID ?
;;** IDirect3DDevice9 methods **
TestCooperativeLevel	PVOID ?
GetAvailableTextureMem	PVOID ?
EvictManagedResources	PVOID ?
GetDirect3D		PVOID ?
GetDeviceCaps		PVOID ?
GetDisplayMode		PVOID ?
GetCreationParameters	PVOID ?
SetCursorProperties	PVOID ?
SetCursorPosition	PVOID ?
ShowCursor		PVOID ?
CreateAdditionalSwapChain PVOID ?
GetSwapChain		PVOID ?
GetNumberOfSwapChains	PVOID ?
Reset			PVOID ?
Present			PVOID ?
GetBackBuffer		PVOID ?
GetRasterStatus		PVOID ?
SetDialogBoxMode	PVOID ?
SetGammaRamp		PVOID ?
GetGammaRamp		PVOID ?
CreateTexture		PVOID ?
CreateVolumeTexture	PVOID ?
CreateCubeTexture	PVOID ?
CreateVertexBuffer	PVOID ?
CreateIndexBuffer	PVOID ?
CreateRenderTarget	PVOID ?
CreateDepthStencilSurface PVOID ?
UpdateSurface		PVOID ?
UpdateTexture		PVOID ?
GetRenderTargetData	PVOID ?
GetFrontBufferData	PVOID ?
StretchRect		PVOID ?
ColorFill		PVOID ?
CreateOffscreenPlainSurface PVOID ?
SetRenderTarget		PVOID ?
GetRenderTarget		PVOID ?
SetDepthStencilSurface	PVOID ?
GetDepthStencilSurface	PVOID ?
BeginScene		PVOID ?
EndScene		PVOID ?
Clear			PVOID ?
SetTransform		PVOID ?
GetTransform		PVOID ?
MultiplyTransform	PVOID ?
SetViewport		PVOID ?
GetViewport		PVOID ?
SetMaterial		PVOID ?
GetMaterial		PVOID ?
SetLight		PVOID ?
GetLight		PVOID ?
LightEnable		PVOID ?
GetLightEnable		PVOID ?
SetClipPlane		PVOID ?
GetClipPlane		PVOID ?
SetRenderState		PVOID ?
GetRenderState		PVOID ?
CreateStateBlock	PVOID ?
BeginStateBlock		PVOID ?
EndStateBlock		PVOID ?
SetClipStatus		PVOID ?
GetClipStatus		PVOID ?
GetTexture		PVOID ?
SetTexture		PVOID ?
GetTextureStageState	PVOID ?
SetTextureStageState	PVOID ?
GetSamplerState		PVOID ?
SetSamplerState		PVOID ?
ValidateDevice		PVOID ?
SetPaletteEntries	PVOID ?
GetPaletteEntries	PVOID ?
SetCurrentTexturePalette PVOID ?
GetCurrentTexturePalette PVOID ?
SetScissorRect		PVOID ?
GetScissorRect		PVOID ?
SetSoftwareVertexProcessing PVOID ?
GetSoftwareVertexProcessing PVOID ?
SetNPatchMode		PVOID ?
GetNPatchMode		PVOID ?
DrawPrimitive		PVOID ?
DrawIndexedPrimitive	PVOID ?
DrawPrimitiveUP		PVOID ?
DrawIndexedPrimitiveUP	PVOID ?
ProcessVertices		PVOID ?
CreateVertexDeclaration PVOID ?
SetVertexDeclaration	PVOID ?
GetVertexDeclaration	PVOID ?
SetFVF			PVOID ?
GetFVF			PVOID ?
CreateVertexShader	PVOID ?
SetVertexShader		PVOID ?
GetVertexShader		PVOID ?
SetVertexShaderConstantF PVOID ?
GetVertexShaderConstantF PVOID ?
SetVertexShaderConstantI PVOID ?
GetVertexShaderConstantI PVOID ?
SetVertexShaderConstantB PVOID ?
GetVertexShaderConstantB PVOID ?
SetStreamSource		PVOID ?
GetStreamSource		PVOID ?
SetStreamSourceFreq	PVOID ?
GetStreamSourceFreq	PVOID ?
SetIndices		PVOID ?
GetIndices		PVOID ?
CreatePixelShader	PVOID ?
SetPixelShader		PVOID ?
GetPixelShader		PVOID ?
SetPixelShaderConstantF PVOID ?
GetPixelShaderConstantF PVOID ?
SetPixelShaderConstantI PVOID ?
GetPixelShaderConstantI PVOID ?
SetPixelShaderConstantB PVOID ?
GetPixelShaderConstantB PVOID ?
DrawRectPatch		PVOID ?
DrawTriPatch		PVOID ?
DeletePatch		PVOID ?
CreateQuery		PVOID ?
SetConvolutionMonoKernel PVOID ?
ComposeRects		PVOID ?
PresentEx		PVOID ?
GetGPUThreadPriority	PVOID ?
SetGPUThreadPriority	PVOID ?
WaitForVBlank		PVOID ?
CheckResourceResidency	PVOID ?
SetMaximumFrameLatency	PVOID ?
GetMaximumFrameLatency	PVOID ?
CheckDeviceState	PVOID ?
CreateRenderTargetEx	PVOID ?
CreateOffscreenPlainSurfaceEx PVOID ?
CreateDepthStencilSurfaceEx PVOID ?
ResetEx			PVOID ?
GetDisplayModeEx	PVOID ?
IDirect3DDevice9Ex	ENDS
LPDIRECT3DDEVICE9EX	typedef ptr IDirect3DDevice9Ex
PDIRECT3DDEVICE9EX	typedef ptr IDirect3DDevice9Ex

IDirect3DDevice9Ex_QueryInterface macro p,a,b
	exitm<[p].QueryInterface(p,a,b)>
	endm
IDirect3DDevice9Ex_AddRef macro p
	exitm<[p].AddRef(p)>
	endm
IDirect3DDevice9Ex_Release macro p
	exitm<[p].Release(p)>
	endm
IDirect3DDevice9Ex_TestCooperativeLevel macro p
	exitm<[p].TestCooperativeevel(p)>
	endm
IDirect3DDevice9Ex_GetAvailableTextureMem macro p
	exitm<[p].GetAvailableTextureMem(p)>
	endm
IDirect3DDevice9Ex_EvictManagedResources macro p
	exitm<[p].EvictManagedResources(p)>
	endm
IDirect3DDevice9Ex_GetDirect3D macro p,a
	exitm<[p].GetDirect3D(p,a)>
	endm
IDirect3DDevice9Ex_GetDeviceCaps macro p,a
	exitm<[p].GetDeviceCaps(p,a)>
	endm
IDirect3DDevice9Ex_GetDisplayMode macro p,a,b
	exitm<[p].GetDisplayMode(p,a,b)>
	endm
IDirect3DDevice9Ex_GetCreationParameters macro p,a
	exitm<[p].GetCreationParameters(p,a)>
	endm
IDirect3DDevice9Ex_SetCursorProperties macro p,a,b,c
	exitm<[p].SetCursorProperties(p,a,b,c)>
	endm
IDirect3DDevice9Ex_SetCursorPosition macro p,a,b,c
	exitm<[p].SetCursorPosition(p,a,b,c)>
	endm
IDirect3DDevice9Ex_ShowCursor macro p,a
	exitm<[p].ShowCursor(p,a)>
	endm
IDirect3DDevice9Ex_CreateAdditionalSwapChain macro p,a,b
	exitm<[p].CreateAdditionalSwapChain(p,a,b)>
	endm
IDirect3DDevice9Ex_GetSwapChain macro p,a,b
	exitm<[p].GetSwapChain(p,a,b)>
	endm
IDirect3DDevice9Ex_GetNumberOfSwapChains macro p
	exitm<[p].GetNumberOfSwapChains(p)>
	endm
IDirect3DDevice9Ex_Reset macro p,a
	exitm<[p].Reset(p,a)>
	endm
IDirect3DDevice9Ex_Present macro p,a,b,c,d
	exitm<[p].Present(p,a,b,c,d)>
	endm
IDirect3DDevice9Ex_GetBackBuffer macro p,a,b,c,d
	exitm<[p].GetBackBuffer(p,a,b,c,d)>
	endm
IDirect3DDevice9Ex_GetRasterStatus macro p,a,b
	exitm<[p].GetRasterStatus(p,a,b)>
	endm
IDirect3DDevice9Ex_SetDialogBoxMode macro p,a
	exitm<[p].SetDialogBoxMode(p,a)>
	endm
IDirect3DDevice9Ex_SetGammaRamp macro p,a,b,c
	exitm<[p].SetGammaRamp(p,a,b,c)>
	endm
IDirect3DDevice9Ex_GetGammaRamp macro p,a,b
	exitm<[p].GetGammaRamp(p,a,b)>
	endm
IDirect3DDevice9Ex_CreateTexture macro p,a,b,c,d,e,f,g,h
	exitm<[p].CreateTexture(p,a,b,c,d,e,f,g,h)>
	endm
IDirect3DDevice9Ex_CreateVolumeTexture macro p,a,b,c,d,e,f,g,h,i
	exitm<[p].CreateVolumeTexture(p,a,b,c,d,e,f,g,h,i)>
	endm
IDirect3DDevice9Ex_CreateCubeTexture macro p,a,b,c,d,e,f,g
	exitm<[p].CreateCubeTexture(p,a,b,c,d,e,f,g)>
	endm
IDirect3DDevice9Ex_CreateVertexBuffer macro p,a,b,c,d,e,f
	exitm<[p].CreateVertexBuffer(p,a,b,c,d,e,f)>
	endm
IDirect3DDevice9Ex_CreateIndexBuffer macro p,a,b,c,d,e,f
	exitm<[p].CreateIndexBuffer(p,a,b,c,d,e,f)>
	endm
IDirect3DDevice9Ex_CreateRenderTarget macro p,a,b,c,d,e,f,g,h
	exitm<[p].CreateRenderTarget(p,a,b,c,d,e,f,g,h)>
	endm
IDirect3DDevice9Ex_CreateDepthStencilSurface macro p,a,b,c,d,e,f,g,h
	exitm<[p].CreateDepthStencilSurface(p,a,b,c,d,e,f,g,h)>
	endm
IDirect3DDevice9Ex_UpdateSurface macro p,a,b,c,d
	exitm<[p].UpdateSurface(p,a,b,c,d)>
	endm
IDirect3DDevice9Ex_UpdateTexture macro p,a,b
	exitm<[p].UpdateTexture(p,a,b)>
	endm
IDirect3DDevice9Ex_GetRenderTargetData macro p,a,b
	exitm<[p].GetRenderTargetData(p,a,b)>
	endm
IDirect3DDevice9Ex_GetFrontBufferData macro p,a,b
	exitm<[p].GetFrontBufferData(p,a,b)>
	endm
IDirect3DDevice9Ex_StretchRect macro p,a,b,c,d,e
	exitm<[p].StretchRect(p,a,b,c,d,e)>
	endm
IDirect3DDevice9Ex_ColorFill macro p,a,b,c
	exitm<[p].ColorFill(p,a,b,c)>
	endm
IDirect3DDevice9Ex_CreateOffscreenPlainSurface macro p,a,b,c,d,e,f
	exitm<[p].CreateOffscreenPlainSurface(p,a,b,c,d,e,f)>
	endm
IDirect3DDevice9Ex_SetRenderTarget macro p,a,b
	exitm<[p].SetRenderTarget(p,a,b)>
	endm
IDirect3DDevice9Ex_GetRenderTarget macro p,a,b
	exitm<[p].GetRenderTarget(p,a,b)>
	endm
IDirect3DDevice9Ex_SetDepthStencilSurface macro p,a
	exitm<[p].SetDepthStencilSurface(p,a)>
	endm
IDirect3DDevice9Ex_GetDepthStencilSurface macro p,a
	exitm<[p].GetDepthStencilSurface(p,a)>
	endm
IDirect3DDevice9Ex_BeginScene macro p
	exitm<[p].BeginScene(p)>
	endm
IDirect3DDevice9Ex_EndScene macro p
	exitm<[p].EndScene(p)>
	endm
IDirect3DDevice9Ex_Clear macro p,a,b,c,d,e,f
	exitm<[p].Clear(p,a,b,c,d,e,f)>
	endm
IDirect3DDevice9Ex_SetTransform macro p,a,b
	exitm<[p].SetTransform(p,a,b)>
	endm
IDirect3DDevice9Ex_GetTransform macro p,a,b
	exitm<[p].GetTransform(p,a,b)>
	endm
IDirect3DDevice9Ex_MultiplyTransform macro p,a,b
	exitm<[p].MultiplyTransform(p,a,b)>
	endm
IDirect3DDevice9Ex_SetViewport macro p,a
	exitm<[p].SetViewport(p,a)>
	endm
IDirect3DDevice9Ex_GetViewport macro p,a
	exitm<[p].GetViewport(p,a)>
	endm
IDirect3DDevice9Ex_SetMaterial macro p,a
	exitm<[p].SetMaterial(p,a)>
	endm
IDirect3DDevice9Ex_GetMaterial macro p,a
	exitm<[p].GetMaterial(p,a)>
	endm
IDirect3DDevice9Ex_SetLight macro p,a,b
	exitm<[p].SetLight(p,a,b)>
	endm
IDirect3DDevice9Ex_GetLight macro p,a,b
	exitm<[p].GetLight(p,a,b)>
	endm
IDirect3DDevice9Ex_LightEnable macro p,a,b
	exitm<[p].LightEnable(p,a,b)>
	endm
IDirect3DDevice9Ex_GetLightEnable macro p,a,b
	exitm<[p].GetLightEnable(p,a,b)>
	endm
IDirect3DDevice9Ex_SetClipPlane macro p,a,b
	exitm<[p].SetClipPlane(p,a,b)>
	endm
IDirect3DDevice9Ex_GetClipPlane macro p,a,b
	exitm<[p].GetClipPlane(p,a,b)>
	endm
IDirect3DDevice9Ex_SetRenderState macro p,a,b
	exitm<[p].SetRenderState(p,a,b)>
	endm
IDirect3DDevice9Ex_GetRenderState macro p,a,b
	exitm<[p].GetRenderState(p,a,b)>
	endm
IDirect3DDevice9Ex_CreateStateBlock macro p,a,b
	exitm<[p].CreateStateBlock(p,a,b)>
	endm
IDirect3DDevice9Ex_BeginStateBlock macro p
	exitm<[p].BeginStateBlock(p)>
	endm
IDirect3DDevice9Ex_EndStateBlock macro p,a
	exitm<[p].EndStateBlock(p,a)>
	endm
IDirect3DDevice9Ex_SetClipStatus macro p,a
	exitm<[p].SetClipStatus(p,a)>
	endm
IDirect3DDevice9Ex_GetClipStatus macro p,a
	exitm<[p].GetClipStatus(p,a)>
	endm
IDirect3DDevice9Ex_GetTexture macro p,a,b
	exitm<[p].GetTexture(p,a,b)>
	endm
IDirect3DDevice9Ex_SetTexture macro p,a,b
	exitm<[p].SetTexture(p,a,b)>
	endm
IDirect3DDevice9Ex_GetTextureStageState macro p,a,b,c
	exitm<[p].GetTextureStageState(p,a,b,c)>
	endm
IDirect3DDevice9Ex_SetTextureStageState macro p,a,b,c
	exitm<[p].SetTextureStageState(p,a,b,c)>
	endm
IDirect3DDevice9Ex_GetSamplerState macro p,a,b,c
	exitm<[p].GetSamplerState(p,a,b,c)>
	endm
IDirect3DDevice9Ex_SetSamplerState macro p,a,b,c
	exitm<[p].SetSamplerState(p,a,b,c)>
	endm
IDirect3DDevice9Ex_ValidateDevice macro p,a
	exitm<[p].ValidateDevice(p,a)>
	endm
IDirect3DDevice9Ex_SetPaletteEntries macro p,a,b
	exitm<[p].SetPaletteEntries(p,a,b)>
	endm
IDirect3DDevice9Ex_GetPaletteEntries macro p,a,b
	exitm<[p].GetPaletteEntries(p,a,b)>
	endm
IDirect3DDevice9Ex_SetCurrentTexturePalette macro p,a
	exitm<[p].SetCurrentTexturePalette(p,a)>
	endm
IDirect3DDevice9Ex_GetCurrentTexturePalette macro p,a
	exitm<[p].GetCurrentTexturePalette(p,a)>
	endm
IDirect3DDevice9Ex_SetScissorRect macro p,a
	exitm<[p].SetScissorRect(p,a)>
	endm
IDirect3DDevice9Ex_GetScissorRect macro p,a
	exitm<[p].GetScissorRect(p,a)>
	endm
IDirect3DDevice9Ex_SetSoftwareVertexProcessing macro p,a
	exitm<[p].SetSoftwareVertexProcessing(p,a)>
	endm
IDirect3DDevice9Ex_GetSoftwareVertexProcessing macro p
	exitm<[p].GetSoftwareVertexProcessing(p)>
	endm
IDirect3DDevice9Ex_SetNPatchMode macro p,a
	exitm<[p].SetNPatchMode(p,a)>
	endm
IDirect3DDevice9Ex_GetNPatchMode macro p
	exitm<[p].GetNPatchMode(p)>
	endm
IDirect3DDevice9Ex_DrawPrimitive macro p,a,b,c
	exitm<[p].DrawPrimitive(p,a,b,c)>
	endm
IDirect3DDevice9Ex_DrawIndexedPrimitive macro p,a,b,c,d,e,f
	exitm<[p].DrawIndexedPrimitive(p,a,b,c,d,e,f)>
	endm
IDirect3DDevice9Ex_DrawPrimitiveUP macro p,a,b,c,d
	exitm<[p].DrawPrimitiveUP(p,a,b,c,d)>
	endm
IDirect3DDevice9Ex_DrawIndexedPrimitiveUP macro p,a,b,c,d,e,f,g,h
	exitm<[p].DrawIndexedPrimitiveUP(p,a,b,c,d,e,f,g,h)>
	endm
IDirect3DDevice9Ex_ProcessVertices macro p,a,b,c,d,e,f
	exitm<[p].ProcessVertices(p,a,b,c,d,e,f)>
	endm
IDirect3DDevice9Ex_CreateVertexDeclaration macro p,a,b
	exitm<[p].CreateVertexDeclaration(p,a,b)>
	endm
IDirect3DDevice9Ex_SetVertexDeclaration macro p,a
	exitm<[p].SetVertexDeclaration(p,a)>
	endm
IDirect3DDevice9Ex_GetVertexDeclaration macro p,a
	exitm<[p].GetVertexDeclaration(p,a)>
	endm
IDirect3DDevice9Ex_SetFVF macro p,a
	exitm<[p].SetFVF(p,a)>
	endm
IDirect3DDevice9Ex_GetFVF macro p,a
	exitm<[p].GetFVF(p,a)>
	endm
IDirect3DDevice9Ex_CreateVertexShader macro p,a,b
	exitm<[p].CreateVertexShader(p,a,b)>
	endm
IDirect3DDevice9Ex_SetVertexShader macro p,a
	exitm<[p].SetVertexShader(p,a)>
	endm
IDirect3DDevice9Ex_GetVertexShader macro p,a
	exitm<[p].GetVertexShader(p,a)>
	endm
IDirect3DDevice9Ex_SetVertexShaderConstantF macro p,a,b,c
	exitm<[p].SetVertexShaderConstantF(p,a,b,c)>
	endm
IDirect3DDevice9Ex_GetVertexShaderConstantF macro p,a,b,c
	exitm<[p].GetVertexShaderConstantF(p,a,b,c)>
	endm
IDirect3DDevice9Ex_SetVertexShaderConstantI macro p,a,b,c
	exitm<[p].SetVertexShaderConstantI(p,a,b,c)>
	endm
IDirect3DDevice9Ex_GetVertexShaderConstantI macro p,a,b,c
	exitm<[p].GetVertexShaderConstantI(p,a,b,c)>
	endm
IDirect3DDevice9Ex_SetVertexShaderConstantB macro p,a,b,c
	exitm<[p].SetVertexShaderConstantB(p,a,b,c)>
	endm
IDirect3DDevice9Ex_GetVertexShaderConstantB macro p,a,b,c
	exitm<[p].GetVertexShaderConstantB(p,a,b,c)>
	endm
IDirect3DDevice9Ex_SetStreamSource macro p,a,b,c,d
	exitm<[p].SetStreamSource(p,a,b,c,d)>
	endm
IDirect3DDevice9Ex_GetStreamSource macro p,a,b,c,d
	exitm<[p].GetStreamSource(p,a,b,c,d)>
	endm
IDirect3DDevice9Ex_SetStreamSourceFreq macro p,a,b
	exitm<[p].SetStreamSourceFreq(p,a,b)>
	endm
IDirect3DDevice9Ex_GetStreamSourceFreq macro p,a,b
	exitm<[p].GetStreamSourceFreq(p,a,b)>
	endm
IDirect3DDevice9Ex_SetIndices macro p,a
	exitm<[p].SetIndices(p,a)>
	endm
IDirect3DDevice9Ex_GetIndices macro p,a
	exitm<[p].GetIndices(p,a)>
	endm
IDirect3DDevice9Ex_CreatePixelShader macro p,a,b
	exitm<[p].CreatePixelShader(p,a,b)>
	endm
IDirect3DDevice9Ex_SetPixelShader macro p,a
	exitm<[p].SetPixelShader(p,a)>
	endm
IDirect3DDevice9Ex_GetPixelShader macro p,a
	exitm<[p].GetPixelShader(p,a)>
	endm
IDirect3DDevice9Ex_SetPixelShaderConstantF macro p,a,b,c
	exitm<[p].SetPixelShaderConstantF(p,a,b,c)>
	endm
IDirect3DDevice9Ex_GetPixelShaderConstantF macro p,a,b,c
	exitm<[p].GetPixelShaderConstantF(p,a,b,c)>
	endm
IDirect3DDevice9Ex_SetPixelShaderConstantI macro p,a,b,c
	exitm<[p].SetPixelShaderConstantI(p,a,b,c)>
	endm
IDirect3DDevice9Ex_GetPixelShaderConstantI macro p,a,b,c
	exitm<[p].GetPixelShaderConstantI(p,a,b,c)>
	endm
IDirect3DDevice9Ex_SetPixelShaderConstantB macro p,a,b,c
	exitm<[p].SetPixelShaderConstantB(p,a,b,c)>
	endm
IDirect3DDevice9Ex_GetPixelShaderConstantB macro p,a,b,c
	exitm<[p].GetPixelShaderConstantB(p,a,b,c)>
	endm
IDirect3DDevice9Ex_DrawRectPatch macro p,a,b,c
	exitm<[p].DrawRectPatch(p,a,b,c)>
	endm
IDirect3DDevice9Ex_DrawTriPatch macro p,a,b,c
	exitm<[p].DrawTriPatch(p,a,b,c)>
	endm
IDirect3DDevice9Ex_DeletePatch macro p,a
	exitm<[p].DeletePatch(p,a)>
	endm
IDirect3DDevice9Ex_CreateQuery macro p,a,b
	exitm<[p].CreateQuery(p,a,b)>
	endm
IDirect3DDevice9Ex_SetConvolutionMonoKernel macro p,a,b,c,d
	exitm<[p].SetConvolutionMonoKernel(p,a,b,c,d)>
	endm
IDirect3DDevice9Ex_ComposeRects macro p,a,b,c,d,e,f,g,h
	exitm<[p].ComposeRects(p,a,b,c,d,e,f,g,h)>
	endm
IDirect3DDevice9Ex_PresentEx macro p,a,b,c,d,e
	exitm<[p].PresentEx(p,a,b,c,d,e)>
	endm
IDirect3DDevice9Ex_GetGPUThreadPriority macro p,a
	exitm<[p].GetGPUThreadPriority(p,a)>
	endm
IDirect3DDevice9Ex_SetGPUThreadPriority macro p,a
	exitm<[p].SetGPUThreadPriority(p,a)>
	endm
IDirect3DDevice9Ex_WaitForVBlank macro p,a
	exitm<[p].WaitForVBlank(p,a)>
	endm
IDirect3DDevice9Ex_CheckResourceResidency macro p,a,b
	exitm<[p].CheckResourceResidency(p,a,b)>
	endm
IDirect3DDevice9Ex_SetMaximumFrameLatency macro p,a
	exitm<[p].SetMaximumFrameatency(p,a)>
	endm
IDirect3DDevice9Ex_GetMaximumFrameLatency macro p,a
	exitm<[p].GetMaximumFrameatency(p,a)>
	endm
IDirect3DDevice9Ex_CheckDeviceState macro p,a
	exitm<[p].CheckDeviceState(p,a)>
	endm
IDirect3DDevice9Ex_CreateRenderTargetEx macro p,a,b,c,d,e,f,g,h,i
	exitm<[p].CreateRenderTargetEx(p,a,b,c,d,e,f,g,h,i)>
	endm
IDirect3DDevice9Ex_CreateOffscreenPlainSurfaceEx macro p,a,b,c,d,e,f,g
	exitm<[p].CreateOffscreenPlainSurfaceEx(p,a,b,c,d,e,f,g)>
	endm
IDirect3DDevice9Ex_CreateDepthStencilSurfaceEx macro p,a,b,c,d,e,f,g,h,i
	exitm<[p].CreateDepthStencilSurfaceEx(p,a,b,c,d,e,f,g,h,i)>
	endm
IDirect3DDevice9Ex_ResetEx macro p,a,b
	exitm<[p].ResetEx(p,a,b)>
	endm
IDirect3DDevice9Ex_GetDisplayModeEx macro p,a,b,c
	exitm<[p].GetDisplayModeEx(p,a,b,c)>
	endm


IDirect3DSwapChain9Ex	STRUC
;;** IUnknown methods **
QueryInterface		PVOID ?
AddRef			PVOID ?
Release			PVOID ?
;;** IDirect3DSwapChain9 methods **
Present			PVOID ?
GetFrontBufferData	PVOID ?
GetBackBuffer		PVOID ?
GetRasterStatus		PVOID ?
GetDisplayMode		PVOID ?
GetDevice		PVOID ?
GetPresentParameters	PVOID ?
GetLastPresentCount	PVOID ?
GetPresentStats		PVOID ?
GetDisplayModeEx	PVOID ?
IDirect3DSwapChain9Ex	ENDS
LPDIRECT3DSWAPCHAIN9EX	typedef ptr IDirect3DSwapChain9Ex
PDIRECT3DSWAPCHAIN9EX	typedef ptr IDirect3DSwapChain9Ex

IDirect3DSwapChain9Ex_QueryInterface macro p,a,b
	exitm<[p].QueryInterface(p,a,b)>
	endm
IDirect3DSwapChain9Ex_AddRef macro p
	exitm<[p].AddRef(p)>
	endm
IDirect3DSwapChain9Ex_Release macro p
	exitm<[p].Release(p)>
	endm
IDirect3DSwapChain9Ex_Present macro p,a,b,c,d,e
	exitm<[p].Present(p,a,b,c,d,e)>
	endm
IDirect3DSwapChain9Ex_GetFrontBufferData macro p,a
	exitm<[p].GetFrontBufferData(p,a)>
	endm
IDirect3DSwapChain9Ex_GetBackBuffer macro p,a,b,c
	exitm<[p].GetBackBuffer(p,a,b,c)>
	endm
IDirect3DSwapChain9Ex_GetRasterStatus macro p,a
	exitm<[p].GetRasterStatus(p,a)>
	endm
IDirect3DSwapChain9Ex_GetDisplayMode macro p,a
	exitm<[p].GetDisplayMode(p,a)>
	endm
IDirect3DSwapChain9Ex_GetDevice macro p,a
	exitm<[p].GetDevice(p,a)>
	endm
IDirect3DSwapChain9Ex_GetPresentParameters macro p,a
	exitm<[p].GetPresentParameters(p,a)>
	endm
IDirect3DSwapChain9Ex_GetLastPresentCount macro p,a
	exitm<[p].GetLastPresentCount(p,a)>
	endm
IDirect3DSwapChain9Ex_GetPresentStats macro p,a
	exitm<[p].GetPresentStats(p,a)>
	endm
IDirect3DSwapChain9Ex_GetDisplayModeEx macro p,a,b
	exitm<[p].GetDisplayModeEx(p,a,b)>
	endm

endif ;; NOT D3D_DISABLE_9EX
;; -- D3D9Ex only


IDirect3D9ExOverlayExtension STRUC
;;** IUnknown methods **
QueryInterface		PVOID ?
AddRef			PVOID ?
Release			PVOID ?
;;** IDirect3D9ExOverlayExtension methods **
CheckDeviceOverlayType	PVOID ?
IDirect3D9ExOverlayExtension ENDS
LPDIRECT3D9EXOVERLAYEXTENSION typedef ptr IDirect3D9ExOverlayExtension
PDIRECT3D9EXOVERLAYEXTENSION  typedef ptr IDirect3D9ExOverlayExtension

IDirect3D9ExOverlayExtension_QueryInterface macro p,a,b
	exitm<[p].QueryInterface(p,a,b)>
	endm
IDirect3D9ExOverlayExtension_AddRef macro p
	exitm<[p].AddRef(p)>
	endm
IDirect3D9ExOverlayExtension_Release macro p
	exitm<[p].Release(p)>
	endm
IDirect3D9ExOverlayExtension_CheckDeviceOverlayType macro p,a,b,c,d,e,f,g,h
	exitm<[p].CheckDeviceOverlayType(p,a,b,c,d,e,f,g,h)>
	endm


IDirect3DDevice9Video	STRUC
;;** IUnknown methods **
QueryInterface		PVOID ?
AddRef			PVOID ?
Release			PVOID ?
;;** IDirect3DDevice9Video methods **
GetContentProtectionCaps PVOID ?
CreateAuthenticatedChannel PVOID ?
CreateCryptoSession	PVOID ?
IDirect3DDevice9Video	ENDS
LPDIRECT3DDEVICE9VIDEO	typedef ptr IDirect3DDevice9Video
PDIRECT3DDEVICE9VIDEO	typedef ptr IDirect3DDevice9Video

IDirect3DDevice9Video_QueryInterface macro p,a,b
	exitm<[p].QueryInterface(p,a,b)>
	endm
IDirect3DDevice9Video_AddRef macro p
	exitm<[p].AddRef(p)>
	endm
IDirect3DDevice9Video_Release macro p
	exitm<[p].Release(p)>
	endm
IDirect3DDevice9Video_GetContentProtectionCaps macro p,a,b,c
	exitm<[p].GetContentProtectionCaps(p,a,b,c)>
	endm
IDirect3DDevice9Video_CreateAuthenticatedChannel macro p,a,b,c
	exitm<[p].CreateAuthenticatedChannel(p,a,b,c)>
	endm
IDirect3DDevice9Video_CreateCryptoSession macro p,a,b,c,d
	exitm<[p].CreateCryptoSession(p,a,b,c,d)>
	endm


IDirect3DAuthenticatedChannel9 STRUC
;;** IUnknown methods **
QueryInterface		PVOID ?
AddRef			PVOID ?
Release			PVOID ?
;;** IDirect3DAuthenticatedChannel9 methods **
GetCertificateSize	PVOID ?
GetCertificate		PVOID ?
NegotiateKeyExchange	PVOID ?
Query			PVOID ?
Configure		PVOID ?
IDirect3DAuthenticatedChannel9	ENDS
LPDIRECT3DAUTHENTICATEDCHANNEL9 typedef ptr IDirect3DAuthenticatedChannel9
PDIRECT3DAUTHENTICATEDCHANNEL9	typedef ptr IDirect3DAuthenticatedChannel9

IDirect3DAuthenticatedChannel9_QueryInterface macro p,a,b
	exitm<[p].QueryInterface(p,a,b)>
	endm
IDirect3DAuthenticatedChannel9_AddRef macro p
	exitm<[p].AddRef(p)>
	endm
IDirect3DAuthenticatedChannel9_Release macro p
	exitm<[p].Release(p)>
	endm
IDirect3DAuthenticatedChannel9_GetCertificateSize macro p,a
	exitm<[p].GetCertificateSize(p,a)>
	endm
IDirect3DAuthenticatedChannel9_GetCertificate macro p,a,b
	exitm<[p].GetCertificate(p,a,b)>
	endm
IDirect3DAuthenticatedChannel9_NegotiateKeyExchange macro p,a,b
	exitm<[p].NegotiateKeyExchange(p,a,b)>
	endm
IDirect3DAuthenticatedChannel9_Query macro p,a,b,c,d
	exitm<[p].Query(p,a,b,c,d)>
	endm
IDirect3DAuthenticatedChannel9_Configure macro p,a,b,c
	exitm<[p].Configure(p,a,b,c)>
	endm


IDirect3DCryptoSession9 STRUC
;;** IUnknown methods **
QueryInterface		PVOID ?
AddRef			PVOID ?
Release			PVOID ?
;;** IDirect3DCryptoSession9 methods **
GetCertificateSize	PVOID ?
GetCertificate		PVOID ?
NegotiateKeyExchange	PVOID ?
EncryptionBlt		PVOID ?
DecryptionBlt		PVOID ?
GetSurfacePitch		PVOID ?
StartSessionKeyRefresh	PVOID ?
FinishSessionKeyRefresh PVOID ?
GetEncryptionBltKey	PVOID ?
IDirect3DCryptoSession9 ENDS
LPDIRECT3DCRYPTOSESSION9 typedef ptr IDirect3DCryptoSession9
PDIRECT3DCRYPTOSESSION9 typedef ptr IDirect3DCryptoSession9

IDirect3DCryptoSession9_QueryInterface macro p,a,b
	exitm<[p].QueryInterface(p,a,b)>
	endm
IDirect3DCryptoSession9_AddRef macro p
	exitm<[p].AddRef(p)>
	endm
IDirect3DCryptoSession9_Release macro p
	exitm<[p].Release(p)>
	endm
IDirect3DCryptoSession9_GetCertificateSize macro p,a
	exitm<[p].GetCertificateSize(p,a)>
	endm
IDirect3DCryptoSession9_GetCertificate macro p,a,b
	exitm<[p].GetCertificate(p,a,b)>
	endm
IDirect3DCryptoSession9_NegotiateKeyExchange macro p,a,b
	exitm<[p].NegotiateKeyExchange(p,a,b)>
	endm
IDirect3DCryptoSession9_EncryptionBlt macro p,a,b,c,d
	exitm<[p].EncryptionBlt(p,a,b,c,d)>
	endm
IDirect3DCryptoSession9_DecryptionBlt macro p,a,b,c,d,e,f
	exitm<[p].DecryptionBlt(p,a,b,c,d,e,f)>
	endm
IDirect3DCryptoSession9_GetSurfacePitch macro p,a,b
	exitm<[p].GetSurfacePitch(p,a,b)>
	endm
IDirect3DCryptoSession9_StartSessionKeyRefresh macro p,a,b
	exitm<[p].StartSessionKeyRefresh(p,a,b)>
	endm
IDirect3DCryptoSession9_FinishSessionKeyRefresh macro p
	exitm<[p].FinishSessionKeyRefresh(p)>
	endm
IDirect3DCryptoSession9_GetEncryptionBltKey macro p,a,b
	exitm<[p].GetEncryptionBltKey(p,a,b)>
	endm

endif ;; (DIRECT3D_VERSION GE 0x0900)
.list
endif ;; _D3D_H_
