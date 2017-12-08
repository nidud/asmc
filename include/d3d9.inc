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

IDirect3D9		STRUC
;;** IUnknown methods **
STDMETHOD QueryInterface, :REFIID, :ptr
STDMETHOD AddRef
STDMETHOD Release
;;** IDirect3D9 methods **
STDMETHOD RegisterSoftwareDevice, :ptr
STDMETHOD GetAdapterCount
STDMETHOD GetAdapterIdentifier, :UINT, :DWORD, :ptr
STDMETHOD GetAdapterModeCount, :UINT, :D3DFORMAT
STDMETHOD EnumAdapterModes, :UINT, :D3DFORMAT, :UINT, :ptr
STDMETHOD GetAdapterDisplayMode, :UINT, :ptr
STDMETHOD CheckDeviceType, :UINT, :D3DDEVTYPE, :D3DFORMAT, :D3DFORMAT, :BOOL
STDMETHOD CheckDeviceFormat, :UINT, :D3DDEVTYPE, :D3DFORMAT, :DWORD, :D3DRESOURCETYPE, :D3DFORMAT
STDMETHOD CheckDeviceMultiSampleType, :UINT, :D3DDEVTYPE, :D3DFORMAT, :BOOL, :D3DMULTISAMPLE_TYPE, :ptr
STDMETHOD CheckDepthStencilMatch, :UINT, :D3DDEVTYPE, :D3DFORMAT, :D3DFORMAT, :D3DFORMAT
STDMETHOD CheckDeviceFormatConversion, :UINT, :D3DDEVTYPE, :D3DFORMAT, :D3DFORMAT
STDMETHOD GetDeviceCaps, :UINT, :D3DDEVTYPE, :ptr
STDMETHOD GetAdapterMonitor, :UINT
STDMETHOD CreateDevice, :UINT, :D3DDEVTYPE, :HWND, :DWORD, :ptr, :ptr
IDirect3D9		ENDS
LPDIRECT3D9		typedef ptr IDirect3D9
PDIRECT3D9		typedef ptr IDirect3D9

;; SwapChain

IDirect3DDevice9	STRUC
;;** IUnknown methods **
STDMETHOD QueryInterface, :REFIID, :ptr
STDMETHOD AddRef
STDMETHOD Release
;;** IDirect3DDevice9 methods **
STDMETHOD TestCooperativeLevel
STDMETHOD GetAvailableTextureMem
STDMETHOD EvictManagedResources
STDMETHOD GetDirect3D, :ptr
STDMETHOD GetDeviceCaps, :ptr
STDMETHOD GetDisplayMode, :UINT, :ptr
STDMETHOD GetCreationParameters, :ptr
STDMETHOD SetCursorProperties, :UINT, :UINT, :ptr
STDMETHOD SetCursorPosition, :SINT, :SINT, :DWORD
STDMETHOD ShowCursor, :BOOL
STDMETHOD CreateAdditionalSwapChain, :ptr, :ptr
STDMETHOD GetSwapChain, :UINT, :ptr
STDMETHOD GetNumberOfSwapChains
STDMETHOD Reset, :ptr
STDMETHOD Present, :ptr, :ptr, :HWND, :ptr
STDMETHOD GetBackBuffer, :UINT, :UINT, :D3DBACKBUFFER_TYPE, :ptr
STDMETHOD GetRasterStatus, :UINT, :ptr
STDMETHOD SetDialogBoxMode, :BOOL
STDMETHOD SetGammaRamp, :UINT, :DWORD, :ptr
STDMETHOD GetGammaRamp, :UINT, :ptr
STDMETHOD CreateTexture, :UINT, :UINT, :UINT, :DWORD, :D3DFORMAT, :D3DPOOL, :ptr, :ptr
STDMETHOD CreateVolumeTexture, :UINT, :UINT, :UINT, :UINT, :DWORD, :D3DFORMAT, :D3DPOOL, :ptr, :ptr
STDMETHOD CreateCubeTexture, :UINT, :UINT, :DWORD, :D3DFORMAT, :D3DPOOL, :ptr, :ptr
STDMETHOD CreateVertexBuffer, :UINT, :DWORD, :DWORD, :D3DPOOL, :ptr, :ptr
STDMETHOD CreateIndexBuffer, :UINT, :DWORD, :D3DFORMAT, :D3DPOOL, :ptr, :ptr
STDMETHOD CreateRenderTarget, :UINT, :UINT, :D3DFORMAT, :D3DMULTISAMPLE_TYPE, :DWORD, :BOOL, :ptr, :ptr
STDMETHOD CreateDepthStencilSurface, :UINT, :UINT, :D3DFORMAT, :D3DMULTISAMPLE_TYPE, :DWORD, :BOOL, :ptr, :ptr
STDMETHOD UpdateSurface, :ptr, :ptr, :ptr, :ptr
STDMETHOD UpdateTexture, :ptr, :ptr
STDMETHOD GetRenderTargetData, :ptr, :ptr
STDMETHOD GetFrontBufferData, :UINT, :ptr
STDMETHOD StretchRect, :ptr, :ptr, :ptr, :ptr, :D3DTEXTUREFILTERTYPE
STDMETHOD ColorFill, :ptr, :ptr, :D3DCOLOR
STDMETHOD CreateOffscreenPlainSurface, :UINT, :UINT, :D3DFORMAT, :D3DPOOL, :ptr, :ptr
STDMETHOD SetRenderTarget, :DWORD, :ptr
STDMETHOD GetRenderTarget, :DWORD, :ptr
STDMETHOD SetDepthStencilSurface, :ptr
STDMETHOD GetDepthStencilSurface, :ptr
STDMETHOD BeginScene
STDMETHOD EndScene
STDMETHOD Clear, :DWORD, :ptr, :DWORD, :D3DCOLOR, :FLOAT, :DWORD
STDMETHOD SetTransform, :D3DTRANSFORMSTATETYPE, :ptr
STDMETHOD GetTransform, :D3DTRANSFORMSTATETYPE, :ptr
STDMETHOD MultiplyTransform, :D3DTRANSFORMSTATETYPE, :ptr
STDMETHOD SetViewport, :ptr
STDMETHOD GetViewport, :ptr
STDMETHOD SetMaterial, :ptr
STDMETHOD GetMaterial, :ptr
STDMETHOD SetLight, :DWORD, :ptr
STDMETHOD GetLight, :DWORD, :ptr
STDMETHOD LightEnable, :DWORD, :BOOL
STDMETHOD GetLightEnable, :DWORD, :ptr
STDMETHOD SetClipPlane, :DWORD, :ptr
STDMETHOD GetClipPlane, :DWORD, :ptr
STDMETHOD SetRenderState, :D3DRENDERSTATETYPE, :DWORD
STDMETHOD GetRenderState, :D3DRENDERSTATETYPE, :ptr
STDMETHOD CreateStateBlock, :D3DSTATEBLOCKTYPE, :ptr
STDMETHOD BeginStateBlock
STDMETHOD EndStateBlock, :ptr
STDMETHOD SetClipStatus, :ptr
STDMETHOD GetClipStatus, :ptr
STDMETHOD GetTexture, :DWORD, :ptr
STDMETHOD SetTexture, :DWORD, :ptr
STDMETHOD GetTextureStageState, :DWORD, :D3DTEXTURESTAGESTATETYPE, :ptr
STDMETHOD SetTextureStageState, :DWORD, :D3DTEXTURESTAGESTATETYPE, :DWORD
STDMETHOD GetSamplerState, :DWORD, :D3DSAMPLERSTATETYPE, :ptr
STDMETHOD SetSamplerState, :DWORD, :D3DSAMPLERSTATETYPE, :DWORD
STDMETHOD ValidateDevice, :ptr
STDMETHOD SetPaletteEntries, :UINT, :ptr
STDMETHOD GetPaletteEntries, :UINT, :ptr
STDMETHOD SetCurrentTexturePalette, :UINT
STDMETHOD GetCurrentTexturePalette, :ptr
STDMETHOD SetScissorRect, :ptr
STDMETHOD GetScissorRect, :ptr
STDMETHOD SetSoftwareVertexProcessing, :BOOL
STDMETHOD GetSoftwareVertexProcessing
STDMETHOD SetNPatchMode, :FLOAT
STDMETHOD GetNPatchMode
STDMETHOD DrawPrimitive, :D3DPRIMITIVETYPE, :UINT, :UINT
STDMETHOD DrawIndexedPrimitive, :D3DPRIMITIVETYPE, :SINT, :UINT, :UINT, :UINT, :UINT
STDMETHOD DrawPrimitiveUP, :D3DPRIMITIVETYPE, :UINT, :ptr, :UINT
STDMETHOD DrawIndexedPrimitiveUP, :D3DPRIMITIVETYPE, :UINT, :UINT, :UINT, :ptr, :D3DFORMAT, :ptr, :UINT
STDMETHOD ProcessVertices, :UINT, :UINT, :UINT, :ptr, :ptr, :DWORD
STDMETHOD CreateVertexDeclaration, :ptr, :ptr
STDMETHOD SetVertexDeclaration, :ptr
STDMETHOD GetVertexDeclaration, :ptr
STDMETHOD SetFVF, :DWORD
STDMETHOD GetFVF, :ptr
STDMETHOD CreateVertexShader, :ptr, :ptr
STDMETHOD SetVertexShader, :ptr
STDMETHOD GetVertexShader, :ptr
STDMETHOD SetVertexShaderConstantF, :UINT, :ptr, :UINT
STDMETHOD GetVertexShaderConstantF, :UINT, :ptr, :UINT
STDMETHOD SetVertexShaderConstantI, :UINT, :ptr, :UINT
STDMETHOD GetVertexShaderConstantI, :UINT, :ptr, :UINT
STDMETHOD SetVertexShaderConstantB, :UINT, :ptr, :UINT
STDMETHOD GetVertexShaderConstantB, :UINT, :ptr, :UINT
STDMETHOD SetStreamSource, :UINT, :ptr, :UINT, :UINT
STDMETHOD GetStreamSource, :UINT, :ptr, :ptr, :ptr
STDMETHOD SetStreamSourceFreq, :UINT, :UINT
STDMETHOD GetStreamSourceFreq, :UINT, :ptr
STDMETHOD SetIndices, :ptr
STDMETHOD GetIndices, :ptr
STDMETHOD CreatePixelShader, :ptr, :ptr
STDMETHOD SetPixelShader, :ptr
STDMETHOD GetPixelShader, :ptr
STDMETHOD SetPixelShaderConstantF, :UINT, :ptr, :UINT
STDMETHOD GetPixelShaderConstantF, :UINT, :ptr, :UINT
STDMETHOD SetPixelShaderConstantI, :UINT, :ptr, :UINT
STDMETHOD GetPixelShaderConstantI, :UINT, :ptr, :UINT
STDMETHOD SetPixelShaderConstantB, :UINT, :ptr, :UINT
STDMETHOD GetPixelShaderConstantB, :UINT, :ptr, :UINT
STDMETHOD DrawRectPatch, :UINT, :ptr, :ptr
STDMETHOD DrawTriPatch, :UINT, :ptr, :ptr
STDMETHOD DeletePatch, :UINT
STDMETHOD CreateQuery, :D3DQUERYTYPE, :ptr
IDirect3DDevice9	ENDS
LPDIRECT3DDEVICE9	typedef ptr IDirect3DDevice9
PDIRECT3DDEVICE9	typedef ptr IDirect3DDevice9

IDirect3DStateBlock9	STRUC
STDMETHOD QueryInterface, :REFIID, :ptr
STDMETHOD AddRef
STDMETHOD Release
STDMETHOD GetDevice, :ptr
STDMETHOD Capture
STDMETHOD Apply
IDirect3DStateBlock9	ENDS
LPDIRECT3DSTATEBLOCK9	typedef ptr IDirect3DStateBlock9
PDIRECT3DSTATEBLOCK9	typedef ptr IDirect3DStateBlock9

IDirect3DSwapChain9	STRUC
STDMETHOD QueryInterface, :REFIID, :ptr
STDMETHOD AddRef
STDMETHOD Release
STDMETHOD Present, :ptr, :ptr, :HWND, :ptr, :DWORD
STDMETHOD GetFrontBufferData, :ptr
STDMETHOD GetBackBuffer, :UINT, :D3DBACKBUFFER_TYPE, :ptr
STDMETHOD GetRasterStatus, :ptr
STDMETHOD GetDisplayMode, :ptr
STDMETHOD GetDevice, :ptr
STDMETHOD GetPresentParameters, :ptr
IDirect3DSwapChain9	ENDS
LPDIRECT3DSWAPCHAIN9	typedef ptr IDirect3DSwapChain9
PDIRECT3DSWAPCHAIN9	typedef ptr IDirect3DSwapChain9

IDirect3DResource9	STRUC
STDMETHOD QueryInterface, :REFIID, :ptr
STDMETHOD AddRef
STDMETHOD Release
STDMETHOD GetDevice, :ptr
STDMETHOD SetPrivateData, :REFGUID, :ptr, :DWORD, :DWORD
STDMETHOD GetPrivateData, :REFGUID, :ptr, :ptr
STDMETHOD FreePrivateData, :REFGUID
STDMETHOD SetPriority, :DWORD
STDMETHOD GetPriority
STDMETHOD PreLoad
STDMETHOD GetType
IDirect3DResource9	ENDS
LPDIRECT3DRESOURCE9	typedef ptr IDirect3DResource9
PDIRECT3DRESOURCE9	typedef ptr IDirect3DResource9

IDirect3DVertexDeclaration9 STRUC
STDMETHOD QueryInterface, :REFIID, :ptr
STDMETHOD AddRef
STDMETHOD Release
STDMETHOD GetDevice, :ptr
STDMETHOD GetDeclaration, :ptr, :ptr
IDirect3DVertexDeclaration9 ENDS
LPDIRECT3DVERTEXDECLARATION9 typedef ptr IDirect3DVertexDeclaration9
PDIRECT3DVERTEXDECLARATION9 typedef ptr IDirect3DVertexDeclaration9

IDirect3DVertexShader9	STRUC
STDMETHOD QueryInterface, :REFIID, :ptr
STDMETHOD AddRef
STDMETHOD Release
STDMETHOD GetDevice, :ptr
STDMETHOD GetFunction, :ptr, :ptr
IDirect3DVertexShader9	ENDS
LPDIRECT3DVERTEXSHADER9 typedef ptr IDirect3DVertexShader9
PDIRECT3DVERTEXSHADER9	typedef ptr IDirect3DVertexShader9

IDirect3DPixelShader9	STRUC
STDMETHOD QueryInterface, :REFIID, :ptr
STDMETHOD AddRef
STDMETHOD Release
STDMETHOD GetDevice, :ptr
STDMETHOD GetFunction, :ptr, :ptr
IDirect3DPixelShader9	ENDS
LPDIRECT3DPIXELSHADER9	typedef ptr IDirect3DPixelShader9
PDIRECT3DPIXELSHADER9	typedef ptr IDirect3DPixelShader9

IDirect3DBaseTexture9	STRUC
STDMETHOD QueryInterface, :REFIID, :ptr
STDMETHOD AddRef
STDMETHOD Release
STDMETHOD GetDevice, :ptr
STDMETHOD SetPrivateData, :REFGUID, :ptr, :DWORD, :DWORD
STDMETHOD GetPrivateData, :REFGUID, :ptr, :ptr
STDMETHOD FreePrivateData, :REFGUID
STDMETHOD SetPriority, :DWORD
STDMETHOD GetPriority
STDMETHOD PreLoad
STDMETHOD GetType
STDMETHOD SetLOD, :DWORD
STDMETHOD GetLOD
STDMETHOD GetLevelCount
STDMETHOD SetAutoGenFilterType, :D3DTEXTUREFILTERTYPE
STDMETHOD GetAutoGenFilterType
STDMETHOD GenerateMipSubLevels
IDirect3DBaseTexture9	ENDS
LPDIRECT3DBASETEXTURE9	typedef ptr IDirect3DBaseTexture9
PDIRECT3DBASETEXTURE9	typedef ptr IDirect3DBaseTexture9

IDirect3DTexture9	STRUC
STDMETHOD QueryInterface, :REFIID, :ptr
STDMETHOD AddRef
STDMETHOD Release
STDMETHOD GetDevice, :ptr
STDMETHOD SetPrivateData, :REFGUID, :ptr, :DWORD, :DWORD
STDMETHOD GetPrivateData, :REFGUID, :ptr, :ptr
STDMETHOD FreePrivateData, :REFGUID
STDMETHOD SetPriority, :DWORD
STDMETHOD GetPriority
STDMETHOD PreLoad
STDMETHOD GetType
STDMETHOD SetLOD, :DWORD
STDMETHOD GetLOD
STDMETHOD GetLevelCount
STDMETHOD SetAutoGenFilterType, :D3DTEXTUREFILTERTYPE
STDMETHOD GetAutoGenFilterType
STDMETHOD GenerateMipSubLevels
STDMETHOD GetLevelDesc, :UINT, :ptr
STDMETHOD GetSurfaceLevel, :UINT, :ptr
STDMETHOD LockRect, :UINT, :ptr, :ptr, :DWORD
STDMETHOD UnlockRect, :UINT
STDMETHOD AddDirtyRect, :ptr
IDirect3DTexture9	ENDS
LPDIRECT3DTEXTURE9	typedef ptr IDirect3DTexture9
PDIRECT3DTEXTURE9	typedef ptr IDirect3DTexture9

IDirect3DVolumeTexture9 STRUC
STDMETHOD QueryInterface, :REFIID, :ptr
STDMETHOD AddRef
STDMETHOD Release
STDMETHOD GetDevice, :ptr
STDMETHOD SetPrivateData, :REFGUID, :ptr, :DWORD, :DWORD
STDMETHOD GetPrivateData, :REFGUID, :ptr, :ptr
STDMETHOD FreePrivateData, :REFGUID
STDMETHOD SetPriority, :DWORD
STDMETHOD GetPriority
STDMETHOD PreLoad
STDMETHOD GetType
STDMETHOD SetLOD, :DWORD
STDMETHOD GetLOD
STDMETHOD GetLevelCount
STDMETHOD SetAutoGenFilterType, :D3DTEXTUREFILTERTYPE
STDMETHOD GetAutoGenFilterType
STDMETHOD GenerateMipSubLevels
STDMETHOD GetLevelDesc, :UINT, :ptr
STDMETHOD GetVolumeLevel, :UINT, :ptr
STDMETHOD LockBox, :UINT, :ptr, :ptr, :DWORD
STDMETHOD UnlockBox, :UINT
STDMETHOD AddDirtyBox, :ptr
IDirect3DVolumeTexture9 ENDS
LPDIRECT3DVOLUMETEXTURE9 typedef ptr IDirect3DVolumeTexture9
PDIRECT3DVOLUMETEXTURE9 typedef ptr IDirect3DVolumeTexture9

IDirect3DCubeTexture9	STRUC
STDMETHOD QueryInterface, :REFIID, :ptr
STDMETHOD AddRef
STDMETHOD Release
STDMETHOD GetDevice, :ptr
STDMETHOD SetPrivateData, :REFGUID, :ptr, :DWORD, :DWORD
STDMETHOD GetPrivateData, :REFGUID, :ptr, :ptr
STDMETHOD FreePrivateData, :REFGUID
STDMETHOD SetPriority, :DWORD
STDMETHOD GetPriority
STDMETHOD PreLoad
STDMETHOD GetType
STDMETHOD SetLOD, :DWORD
STDMETHOD GetLOD
STDMETHOD GetLevelCount
STDMETHOD SetAutoGenFilterType, :D3DTEXTUREFILTERTYPE
STDMETHOD GetAutoGenFilterType
STDMETHOD GenerateMipSubLevels
STDMETHOD GetLevelDesc, :UINT, :ptr
STDMETHOD GetCubeMapSurface, :D3DCUBEMAP_FACES, :UINT, :ptr
STDMETHOD LockRect, :D3DCUBEMAP_FACES, :UINT, :ptr, :ptr, :DWORD
STDMETHOD UnlockRect, :D3DCUBEMAP_FACES, :UINT
STDMETHOD AddDirtyRect, :D3DCUBEMAP_FACES, :ptr
IDirect3DCubeTexture9	ENDS
LPDIRECT3DCUBETEXTURE9	typedef ptr IDirect3DCubeTexture9
PDIRECT3DCUBETEXTURE9	typedef ptr IDirect3DCubeTexture9

IDirect3DVertexBuffer9	STRUC
STDMETHOD QueryInterface, :REFIID, :ptr
STDMETHOD AddRef
STDMETHOD Release
STDMETHOD GetDevice, :ptr
STDMETHOD SetPrivateData, :REFGUID, :ptr, :DWORD, :DWORD
STDMETHOD GetPrivateData, :REFGUID, :ptr, :ptr
STDMETHOD FreePrivateData, :REFGUID
STDMETHOD SetPriority, :DWORD
STDMETHOD GetPriority
STDMETHOD PreLoad
STDMETHOD GetType
STDMETHOD _Lock, :UINT, :UINT, :ptr, :DWORD
STDMETHOD Unlock
STDMETHOD GetDesc, :ptr
IDirect3DVertexBuffer9	ENDS
LPDIRECT3DVERTEXBUFFER9 typedef ptr IDirect3DVertexBuffer9
PDIRECT3DVERTEXBUFFER9	typedef ptr IDirect3DVertexBuffer9

IDirect3DIndexBuffer9	STRUC
STDMETHOD QueryInterface, :REFIID, :ptr
STDMETHOD AddRef
STDMETHOD Release
STDMETHOD GetDevice, :ptr
STDMETHOD SetPrivateData, :REFGUID, :ptr, :DWORD, :DWORD
STDMETHOD GetPrivateData, :REFGUID, :ptr, :ptr
STDMETHOD FreePrivateData, :REFGUID
STDMETHOD SetPriority, :DWORD
STDMETHOD GetPriority
STDMETHOD PreLoad
STDMETHOD GetType
STDMETHOD _Lock, :UINT, :UINT, :ptr, :DWORD
STDMETHOD Unlock
STDMETHOD GetDesc, :ptr
IDirect3DIndexBuffer9	ENDS
LPDIRECT3DINDEXBUFFER9	typedef ptr IDirect3DIndexBuffer9
PDIRECT3DINDEXBUFFER9	typedef ptr IDirect3DIndexBuffer9

IDirect3DSurface9	STRUC
STDMETHOD QueryInterface, :REFIID, :ptr
STDMETHOD AddRef
STDMETHOD Release
STDMETHOD GetDevice, :ptr
STDMETHOD SetPrivateData, :REFGUID, :ptr, :DWORD, :DWORD
STDMETHOD GetPrivateData, :REFGUID, :ptr, :ptr
STDMETHOD FreePrivateData, :REFGUID
STDMETHOD SetPriority, :DWORD
STDMETHOD GetPriority
STDMETHOD PreLoad
STDMETHOD GetType
STDMETHOD GetContainer, :REFIID, :ptr
STDMETHOD GetDesc, :ptr
STDMETHOD LockRect, :ptr, :ptr, :DWORD
STDMETHOD UnlockRect
STDMETHOD GetDC, :ptr
STDMETHOD ReleaseDC, :HDC
IDirect3DSurface9	ENDS
LPDIRECT3DSURFACE9	typedef ptr IDirect3DSurface9
PDIRECT3DSURFACE9	typedef ptr IDirect3DSurface9

IDirect3DVolume9	STRUC
STDMETHOD QueryInterface, :REFIID, :ptr
STDMETHOD AddRef
STDMETHOD Release
STDMETHOD GetDevice, :ptr
STDMETHOD SetPrivateData, :REFGUID, :ptr, :DWORD, :DWORD
STDMETHOD GetPrivateData, :REFGUID, :ptr, :ptr
STDMETHOD FreePrivateData, :REFGUID
STDMETHOD GetContainer, :REFIID, :ptr
STDMETHOD GetDesc, :ptr
STDMETHOD LockBox, :ptr, :ptr, :DWORD
STDMETHOD UnlockBox
IDirect3DVolume9	ENDS
LPDIRECT3DVOLUME9	typedef ptr IDirect3DVolume9
PDIRECT3DVOLUME9	typedef ptr IDirect3DVolume9

IDirect3DQuery9		STRUC
STDMETHOD QueryInterface, :REFIID, :ptr
STDMETHOD AddRef
STDMETHOD Release
STDMETHOD GetDevice, :ptr
STDMETHOD GetType
STDMETHOD GetDataSize
STDMETHOD Issue, :DWORD
STDMETHOD GetData, :ptr, :DWORD, :DWORD
IDirect3DQuery9		ENDS
LPDIRECT3DQUERY9	typedef ptr IDirect3DQuery9
PDIRECT3DQUERY9		typedef ptr IDirect3DQuery9

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
STDMETHOD QueryInterface, :REFIID, :ptr
STDMETHOD AddRef
STDMETHOD Release
STDMETHOD GetAdapterCount
STDMETHOD GetAdapterIdentifier, :UINT, :DWORD, :ptr
STDMETHOD GetAdapterModeCount, :UINT, :D3DFORMAT
STDMETHOD EnumAdapterModes, :UINT, :D3DFORMAT, :UINT, :ptr
STDMETHOD GetAdapterDisplayMode, :UINT, :ptr
STDMETHOD CheckDeviceType, :UINT, :D3DDEVTYPE, :D3DFORMAT, :D3DFORMAT, :BOOL
STDMETHOD CheckDeviceFormat, :UINT, :D3DDEVTYPE, :D3DFORMAT, :DWORD, :D3DRESOURCETYPE, :D3DFORMAT
STDMETHOD CheckDeviceMultiSampleType, :UINT, :D3DDEVTYPE, :D3DFORMAT, :BOOL, :D3DMULTISAMPLE_TYPE, :ptr
STDMETHOD CheckDepthStencilMatch, :UINT, :D3DDEVTYPE, :D3DFORMAT, :D3DFORMAT, :D3DFORMAT
STDMETHOD CheckDeviceFormatConversion, :UINT, :D3DDEVTYPE, :D3DFORMAT, :D3DFORMAT
STDMETHOD GetDeviceCaps, :UINT, :D3DDEVTYPE, :ptr
STDMETHOD GetAdapterMonitor, :UINT
STDMETHOD CreateDevice, :UINT, :D3DDEVTYPE, :HWND, :DWORD, :ptr, :ptr
STDMETHOD GetAdapterModeCountEx, :UINT, :ptr
STDMETHOD EnumAdapterModesEx, :UINT, :ptr, :UINT, :ptr
STDMETHOD GetAdapterDisplayModeEx, :UINT, :ptr, :ptr
STDMETHOD CreateDeviceEx, :UINT, :D3DDEVTYPE, :HWND, :DWORD, :ptr, :ptr, :ptr
STDMETHOD GetAdapterLUID, :UINT, :ptr
IDirect3D9Ex		ENDS
LPDIRECT3D9EX		typedef ptr IDirect3D9Ex
PDIRECT3D9EX		typedef ptr IDirect3D9Ex

IDirect3DDevice9Ex	STRUC
STDMETHOD QueryInterface, :REFIID, :ptr
STDMETHOD AddRef
STDMETHOD Release
STDMETHOD TestCooperativeLevel
STDMETHOD GetAvailableTextureMem
STDMETHOD EvictManagedResources
STDMETHOD GetDirect3D, :ptr
STDMETHOD GetDeviceCaps, :ptr
STDMETHOD GetDisplayMode, :UINT, :ptr
STDMETHOD GetCreationParameters, :ptr
STDMETHOD SetCursorProperties, :UINT, :UINT, :ptr
STDMETHOD SetCursorPosition, :SINT, :SINT, :DWORD
STDMETHOD ShowCursor, :BOOL
STDMETHOD CreateAdditionalSwapChain, :ptr, :ptr
STDMETHOD GetSwapChain, :UINT, :ptr
STDMETHOD GetNumberOfSwapChains
STDMETHOD Reset, :ptr
STDMETHOD Present, :ptr, :ptr, :HWND, :ptr
STDMETHOD GetBackBuffer, :UINT, :UINT, :D3DBACKBUFFER_TYPE, :ptr
STDMETHOD GetRasterStatus, :UINT, :ptr
STDMETHOD SetDialogBoxMode, :BOOL
STDMETHOD SetGammaRamp, :UINT, :DWORD, :ptr
STDMETHOD GetGammaRamp, :UINT, :ptr
STDMETHOD CreateTexture, :UINT, :UINT, :UINT, :DWORD, :D3DFORMAT, :D3DPOOL, :ptr, :ptr
STDMETHOD CreateVolumeTexture, :UINT, :UINT, :UINT, :UINT, :DWORD, :D3DFORMAT, :D3DPOOL, :ptr, :ptr
STDMETHOD CreateCubeTexture, :UINT, :UINT, :DWORD, :D3DFORMAT, :D3DPOOL, :ptr, :ptr
STDMETHOD CreateVertexBuffer, :UINT, :DWORD, :DWORD, :D3DPOOL, :ptr, :ptr
STDMETHOD CreateIndexBuffer, :UINT, :DWORD, :D3DFORMAT, :D3DPOOL, :ptr, :ptr
STDMETHOD CreateRenderTarget, :UINT, :UINT, :D3DFORMAT, :D3DMULTISAMPLE_TYPE, :DWORD, :BOOL, :ptr, :ptr
STDMETHOD CreateDepthStencilSurface, :UINT, :UINT, :D3DFORMAT, :D3DMULTISAMPLE_TYPE, :DWORD, :BOOL, :ptr, :ptr
STDMETHOD UpdateSurface, :ptr, :ptr, :ptr, :ptr
STDMETHOD UpdateTexture, :ptr, :ptr
STDMETHOD GetRenderTargetData, :ptr, :ptr
STDMETHOD GetFrontBufferData, :UINT, :ptr
STDMETHOD StretchRect, :ptr, :ptr, :ptr, :ptr, :D3DTEXTUREFILTERTYPE
STDMETHOD ColorFill, :ptr, :ptr, :D3DCOLOR
STDMETHOD CreateOffscreenPlainSurface, :UINT, :UINT, :D3DFORMAT, :D3DPOOL, :ptr, :ptr
STDMETHOD SetRenderTarget, :DWORD, :ptr
STDMETHOD GetRenderTarget, :DWORD, :ptr
STDMETHOD SetDepthStencilSurface, :ptr
STDMETHOD GetDepthStencilSurface, :ptr
STDMETHOD BeginScene
STDMETHOD EndScene
STDMETHOD Clear, :DWORD, :ptr, :DWORD, :D3DCOLOR, :FLOAT, :DWORD
STDMETHOD SetTransform, :D3DTRANSFORMSTATETYPE, :ptr
STDMETHOD GetTransform, :D3DTRANSFORMSTATETYPE, :ptr
STDMETHOD MultiplyTransform, :D3DTRANSFORMSTATETYPE, :ptr
STDMETHOD SetViewport, :ptr
STDMETHOD GetViewport, :ptr
STDMETHOD SetMaterial, :ptr
STDMETHOD GetMaterial, :ptr
STDMETHOD SetLight, :DWORD, :ptr
STDMETHOD GetLight, :DWORD, :ptr
STDMETHOD LightEnable, :DWORD, :BOOL
STDMETHOD GetLightEnable, :DWORD, :ptr
STDMETHOD SetClipPlane, :DWORD, :ptr
STDMETHOD GetClipPlane, :DWORD, :ptr
STDMETHOD SetRenderState, :D3DRENDERSTATETYPE, :DWORD
STDMETHOD GetRenderState, :D3DRENDERSTATETYPE, :ptr
STDMETHOD CreateStateBlock, :D3DSTATEBLOCKTYPE, :ptr
STDMETHOD BeginStateBlock
STDMETHOD EndStateBlock, :ptr
STDMETHOD SetClipStatus, :ptr
STDMETHOD GetClipStatus, :ptr
STDMETHOD GetTexture, :DWORD, :ptr
STDMETHOD SetTexture, :DWORD, :ptr
STDMETHOD GetTextureStageState, :DWORD, :D3DTEXTURESTAGESTATETYPE, :ptr
STDMETHOD SetTextureStageState, :DWORD, :D3DTEXTURESTAGESTATETYPE, :DWORD
STDMETHOD GetSamplerState, :DWORD, :D3DSAMPLERSTATETYPE, :ptr
STDMETHOD SetSamplerState, :DWORD, :D3DSAMPLERSTATETYPE, :DWORD
STDMETHOD ValidateDevice, :ptr
STDMETHOD SetPaletteEntries, :UINT, :ptr
STDMETHOD GetPaletteEntries, :UINT, :ptr
STDMETHOD SetCurrentTexturePalette, :UINT
STDMETHOD GetCurrentTexturePalette, :ptr
STDMETHOD SetScissorRect, :ptr
STDMETHOD GetScissorRect, :ptr
STDMETHOD SetSoftwareVertexProcessing, :BOOL
STDMETHOD GetSoftwareVertexProcessing
STDMETHOD SetNPatchMode, :FLOAT
STDMETHOD GetNPatchMode
STDMETHOD DrawPrimitive, :D3DPRIMITIVETYPE, :UINT, :UINT
STDMETHOD DrawIndexedPrimitive, :D3DPRIMITIVETYPE, :SINT, :UINT, :UINT, :UINT, :UINT
STDMETHOD DrawPrimitiveUP, :D3DPRIMITIVETYPE, :UINT, :ptr, :UINT
STDMETHOD DrawIndexedPrimitiveUP, :D3DPRIMITIVETYPE, :UINT, :UINT, :UINT, :ptr, :D3DFORMAT, :ptr, :UINT
STDMETHOD ProcessVertices, :UINT, :UINT, :UINT, :ptr, :ptr, :DWORD
STDMETHOD CreateVertexDeclaration, :ptr, :ptr
STDMETHOD SetVertexDeclaration, :ptr
STDMETHOD GetVertexDeclaration, :ptr
STDMETHOD SetFVF, :DWORD
STDMETHOD GetFVF, :ptr
STDMETHOD CreateVertexShader, :ptr, :ptr
STDMETHOD SetVertexShader, :ptr
STDMETHOD GetVertexShader, :ptr
STDMETHOD SetVertexShaderConstantF, :UINT, :ptr, :UINT
STDMETHOD GetVertexShaderConstantF, :UINT, :ptr, :UINT
STDMETHOD SetVertexShaderConstantI, :UINT, :ptr, :UINT
STDMETHOD GetVertexShaderConstantI, :UINT, :ptr, :UINT
STDMETHOD SetVertexShaderConstantB, :UINT, :ptr, :UINT
STDMETHOD GetVertexShaderConstantB, :UINT, :ptr, :UINT
STDMETHOD SetStreamSource, :UINT, :ptr, :UINT, :UINT
STDMETHOD GetStreamSource, :UINT, :ptr, :ptr, :ptr
STDMETHOD SetStreamSourceFreq, :UINT, :UINT
STDMETHOD GetStreamSourceFreq, :UINT, :ptr
STDMETHOD SetIndices, :ptr
STDMETHOD GetIndices, :ptr
STDMETHOD CreatePixelShader, :ptr, :ptr
STDMETHOD SetPixelShader, :ptr
STDMETHOD GetPixelShader, :ptr
STDMETHOD SetPixelShaderConstantF, :UINT, :ptr, :UINT
STDMETHOD GetPixelShaderConstantF, :UINT, :ptr, :UINT
STDMETHOD SetPixelShaderConstantI, :UINT, :ptr, :UINT
STDMETHOD GetPixelShaderConstantI, :UINT, :ptr, :UINT
STDMETHOD SetPixelShaderConstantB, :UINT, :ptr, :UINT
STDMETHOD GetPixelShaderConstantB, :UINT, :ptr, :UINT
STDMETHOD DrawRectPatch, :UINT, :ptr, :ptr
STDMETHOD DrawTriPatch, :UINT, :ptr, :ptr
STDMETHOD DeletePatch, :UINT
STDMETHOD CreateQuery, :D3DQUERYTYPE, :ptr
STDMETHOD SetConvolutionMonoKernel, :UINT, :UINT, :ptr, :ptr
STDMETHOD ComposeRects, :ptr, :ptr, :ptr, :UINT, :ptr, :D3DCOMPOSERECTSOP, :SINT, :SINT
STDMETHOD PresentEx, :ptr, :ptr, :HWND, :ptr, :DWORD
STDMETHOD GetGPUThreadPriority, :ptr
STDMETHOD SetGPUThreadPriority, :SINT
STDMETHOD WaitForVBlank, :UINT
STDMETHOD CheckResourceResidency, :ptr, :UINT
STDMETHOD SetMaximumFrameLatency, :UINT
STDMETHOD GetMaximumFrameLatency, :ptr
STDMETHOD CheckDeviceState, :HWND
STDMETHOD CreateRenderTargetEx, :UINT, :UINT, :D3DFORMAT, :D3DMULTISAMPLE_TYPE, :DWORD, :BOOL, :ptr, :ptr, :DWORD
STDMETHOD CreateOffscreenPlainSurfaceEx, :UINT, :UINT, :D3DFORMAT, :D3DPOOL, :ptr, :ptr, :DWORD
STDMETHOD CreateDepthStencilSurfaceEx, :UINT, :UINT, :D3DFORMAT, :D3DMULTISAMPLE_TYPE, :DWORD, :ptr, :ptr, :DWORD
STDMETHOD ResetEx, :ptr, :ptr
STDMETHOD GetDisplayModeEx, :UINT, :ptr, :ptr
IDirect3DDevice9Ex	ENDS
LPDIRECT3DDEVICE9EX	typedef ptr IDirect3DDevice9Ex
PDIRECT3DDEVICE9EX	typedef ptr IDirect3DDevice9Ex

IDirect3DSwapChain9Ex	STRUC
STDMETHOD QueryInterface, :REFIID, :ptr
STDMETHOD AddRef
STDMETHOD Release
STDMETHOD Present, :ptr, :ptr, :HWND, :ptr, :DWORD
STDMETHOD GetFrontBufferData, :ptr
STDMETHOD GetBackBuffer, :UINT, :D3DBACKBUFFER_TYPE, :ptr
STDMETHOD GetRasterStatus, :ptr
STDMETHOD GetDisplayMode, :ptr
STDMETHOD GetDevice, :ptr
STDMETHOD GetPresentParameters, :ptr
STDMETHOD GetLastPresentCount, :ptr
STDMETHOD GetPresentStats, :ptr
STDMETHOD GetDisplayModeEx, :ptr, :ptr
IDirect3DSwapChain9Ex	ENDS
LPDIRECT3DSWAPCHAIN9EX	typedef ptr IDirect3DSwapChain9Ex
PDIRECT3DSWAPCHAIN9EX	typedef ptr IDirect3DSwapChain9Ex

endif ;; NOT D3D_DISABLE_9EX
;; -- D3D9Ex only


IDirect3D9ExOverlayExtension STRUC
STDMETHOD QueryInterface, :REFIID, :ptr
STDMETHOD AddRef
STDMETHOD Release
STDMETHOD CheckDeviceOverlayType, :UINT, :D3DDEVTYPE, :UINT, :UINT, :D3DFORMAT, :ptr, :D3DDISPLAYROTATION, :ptr
IDirect3D9ExOverlayExtension ENDS
LPDIRECT3D9EXOVERLAYEXTENSION typedef ptr IDirect3D9ExOverlayExtension
PDIRECT3D9EXOVERLAYEXTENSION  typedef ptr IDirect3D9ExOverlayExtension

IDirect3DDevice9Video	STRUC
STDMETHOD QueryInterface, :REFIID, :ptr
STDMETHOD AddRef
STDMETHOD Release
STDMETHOD GetContentProtectionCaps, :ptr, :ptr, :ptr
STDMETHOD CreateAuthenticatedChannel, :D3DAUTHENTICATEDCHANNELTYPE, :ptr, :ptr
STDMETHOD CreateCryptoSession, :ptr, :ptr, :ptr, :ptr
IDirect3DDevice9Video	ENDS
LPDIRECT3DDEVICE9VIDEO	typedef ptr IDirect3DDevice9Video
PDIRECT3DDEVICE9VIDEO	typedef ptr IDirect3DDevice9Video

IDirect3DAuthenticatedChannel9 STRUC
STDMETHOD QueryInterface, :REFIID, :ptr
STDMETHOD AddRef
STDMETHOD Release
STDMETHOD GetCertificateSize, :ptr
STDMETHOD GetCertificate, :UINT, :ptr
STDMETHOD NegotiateKeyExchange, :UINT, :ptr
STDMETHOD Query, :UINT, :ptr, :UINT, :ptr
STDMETHOD Configure, :UINT, :ptr, :ptr
IDirect3DAuthenticatedChannel9	ENDS
LPDIRECT3DAUTHENTICATEDCHANNEL9 typedef ptr IDirect3DAuthenticatedChannel9
PDIRECT3DAUTHENTICATEDCHANNEL9	typedef ptr IDirect3DAuthenticatedChannel9


IDirect3DCryptoSession9 STRUC
STDMETHOD QueryInterface, :REFIID, :ptr
STDMETHOD AddRef
STDMETHOD Release
STDMETHOD GetCertificateSize, :ptr
STDMETHOD GetCertificate, :UINT, :ptr
STDMETHOD NegotiateKeyExchange, :UINT, :ptr
STDMETHOD EncryptionBlt, :ptr, :ptr, :UINT, :ptr
STDMETHOD DecryptionBlt, :ptr, :ptr, :UINT, :ptr, :ptr, :ptr
STDMETHOD GetSurfacePitch, :ptr, :ptr
STDMETHOD StartSessionKeyRefresh, :ptr, :UINT
STDMETHOD FinishSessionKeyRefresh
STDMETHOD GetEncryptionBltKey, :ptr, :UINT
IDirect3DCryptoSession9 ENDS
LPDIRECT3DCRYPTOSESSION9 typedef ptr IDirect3DCryptoSession9
PDIRECT3DCRYPTOSESSION9 typedef ptr IDirect3DCryptoSession9

endif ;; (DIRECT3D_VERSION GE 0x0900)
.list
endif ;; _D3D_H_
