include d3dx9.inc
ifndef _D3DX9CORE_H
_D3DX9CORE_H equ <>
.xlist

D3DX_VERSION		equ 0x0902
ifndef D3DX_SDK_VERSION
D3DX_SDK_VERSION	equ 36
endif
D3DXSPRITE_DONOTSAVESTATE equ 0x00000001
D3DXSPRITE_DONOTMODIFY_RENDERSTATE equ 0x00000002
D3DXSPRITE_OBJECTSPACE	equ 0x00000004
D3DXSPRITE_BILLBOARD	equ 0x00000008
D3DXSPRITE_ALPHABLEND	equ 0x00000010
D3DXSPRITE_SORT_TEXTURE equ 0x00000020
D3DXSPRITE_SORT_DEPTH_FRONTTOBACK equ 0x00000040
D3DXSPRITE_SORT_DEPTH_BACKTOFRONT equ 0x00000080
D3DXSPRITE_DO_NOT_ADDREF_TEXTURE equ 0x00000100

DEFINE_GUID(IID_ID3DXBuffer, 0x8ba5fb08, 0x5195, 0x40e2, 0xac, 0x58, 0xd, 0x98, 0x9c, 0x3a, 0x1, 0x2)
DEFINE_GUID(IID_ID3DXFont, 0xd79dbb70, 0x5f21, 0x4d36, 0xbb, 0xc2, 0xff, 0x52, 0x5c, 0x21, 0x3c, 0xdc)
DEFINE_GUID(IID_ID3DXLine, 0xd379ba7f, 0x9042, 0x4ac4, 0x9f, 0x5e, 0x58, 0x19, 0x2a, 0x4c, 0x6b, 0xd8)
DEFINE_GUID(IID_ID3DXRenderToEnvMap, 0x313f1b4b, 0xc7b0, 0x4fa2, 0x9d, 0x9d, 0x8d, 0x38, 0xb, 0x64, 0x38, 0x5e)
DEFINE_GUID(IID_ID3DXRenderToSurface, 0x6985f346, 0x2c3d, 0x43b3, 0xbe, 0x8b, 0xda, 0xae, 0x8a, 0x3, 0xd8, 0x94)
DEFINE_GUID(IID_ID3DXSprite, 0xba0b762d, 0x7d28, 0x43ec, 0xb9, 0xdc, 0x2f, 0x84, 0x44, 0x3b, 0x6, 0x14)

LPD3DXBUFFER		typedef ptr ID3DXBuffer
LPD3DXFONT		typedef ptr ID3DXFont
LPD3DXLINE		typedef ptr ID3DXLine
LPD3DXRenderToEnvMap	typedef ptr ID3DXRenderToEnvMap
LPD3DXRENDERTOSURFACE	typedef ptr ID3DXRenderToSurface
LPD3DXSPRITE		typedef ptr ID3DXSprite

ID3DXBuffer		STRUC
;;** IUnknown methods **
QueryInterface		PVOID ?
AddRef			PVOID ?
Release			PVOID ?
;;** ID3DXBuffer methods **
GetBufferPointer	PVOID ?
GetBufferSize		PVOID ?
ID3DXBuffer		ENDS

D3DXFONT_DESCA		STRUC
Height			SINT ?
_Width			UINT ?
Weight			UINT ?
MipLevels		UINT ?
Italic			BOOL ?
CharSet			db ?
OutputPrecision		db ?
Quality			db ?
PitchAndFamily		db ?
FaceName		db LF_FACESIZE dup(?)
D3DXFONT_DESCA		ENDS
LPD3DXFONT_DESCA	typedef ptr D3DXFONT_DESCA

D3DXFONT_DESCW		STRUC
Height			SINT ?
_Width			UINT ?
Weight			UINT ?
MipLevels		UINT ?
Italic			BOOL ?
CharSet			db ?
OutputPrecision		db ?
Quality			db ?
PitchAndFamily		db ?
FaceName		WCHAR LF_FACESIZE dup(?)
D3DXFONT_DESCW		ENDS
LPD3DXFONT_DESCW	typedef ptr D3DXFONT_DESCW

ID3DXFont		STRUC
STDMETHOD QueryInterface, :REFIID, :ptr
STDMETHOD AddRef
STDMETHOD Release
STDMETHOD GetDevice, :ptr
STDMETHOD GetDescA, :ptr
STDMETHOD GetDescW, :ptr
STDMETHOD GetTextMetricsA, :ptr
STDMETHOD GetTextMetricsW, :ptr
STDMETHOD GetDC
STDMETHOD GetGlyphData, :UINT, :ptr, :ptr, :ptr
STDMETHOD PreloadCharacters, :UINT, :UINT
STDMETHOD PreloadGlyphs, :UINT, :UINT
STDMETHOD PreloadTextA, :ptr, :SINT
STDMETHOD PreloadTextW, :ptr, :SINT
STDMETHOD DrawTextA, :ptr, :ptr, :SINT, :ptr, :DWORD, :D3DCOLOR
STDMETHOD DrawTextW, :ptr, :ptr, :SINT, :ptr, :DWORD, :D3DCOLOR
STDMETHOD OnLostDevice
STDMETHOD OnResetDevice
ID3DXFont		ENDS

ID3DXLine		STRUC
STDMETHOD QueryInterface, :REFIID, :ptr
STDMETHOD AddRef
STDMETHOD Release
STDMETHOD GetDevice, :ptr
STDMETHOD Begin
STDMETHOD Draw, :ptr, :DWORD, :D3DCOLOR
STDMETHOD DrawTransform, :ptr, :DWORD, :ptr, :D3DCOLOR
STDMETHOD SetPattern, :DWORD
STDMETHOD GetPattern
STDMETHOD SetPatternScale, :FLOAT
STDMETHOD GetPatternScale
STDMETHOD SetWidth, :FLOAT
STDMETHOD GetWidth
STDMETHOD SetAntialias, :BOOL
STDMETHOD GetAntialias
STDMETHOD SetGLLines, :BOOL
STDMETHOD GetGLLines
STDMETHOD _End
STDMETHOD OnLostDevice
STDMETHOD OnResetDevice
ID3DXLine		ENDS

D3DXRTE_DESC		STRUC
_Size			UINT ?
MipLevels		UINT ?
Format			D3DFORMAT ?
DepthStencil		BOOL ?
DepthStencilFormat	D3DFORMAT ?
D3DXRTE_DESC		ENDS

ID3DXRenderToEnvMap	STRUC
STDMETHOD QueryInterface, :REFIID, :ptr
STDMETHOD AddRef
STDMETHOD Release
STDMETHOD GetDevice, :ptr
STDMETHOD GetDesc, :ptr
STDMETHOD BeginCube, :ptr
STDMETHOD BeginSphere, :ptr
STDMETHOD BeginHemisphere, :ptr, :ptr
STDMETHOD BeginParabolic, :ptr, :ptr
STDMETHOD Face, :D3DCUBEMAP_FACES, :DWORD
STDMETHOD _End, :DWORD
STDMETHOD OnLostDevice
STDMETHOD OnResetDevice
ID3DXRenderToEnvMap	ENDS

D3DXRTS_DESC		STRUC
_Width			UINT ?
Height			UINT ?
Format			D3DFORMAT ?
DepthStencil		BOOL ?
DepthStencilFormat	D3DFORMAT ?
D3DXRTS_DESC		ENDS

ID3DXRenderToSurface	STRUC
STDMETHOD QueryInterface, :REFIID, :ptr
STDMETHOD AddRef
STDMETHOD Release
STDMETHOD GetDevice, :ptr
STDMETHOD GetDesc, :ptr
STDMETHOD BeginScene, :ptr, :ptr
STDMETHOD EndScene, :DWORD
STDMETHOD OnLostDevice
STDMETHOD OnResetDevice
ID3DXRenderToSurface	ENDS

ID3DXSprite		STRUC
STDMETHOD QueryInterface, :REFIID, :ptr
STDMETHOD AddRef
STDMETHOD Release
STDMETHOD GetDevice, :ptr
STDMETHOD GetTransform, :ptr
STDMETHOD SetTransform, :ptr
STDMETHOD SetWorldViewRH, :ptr, :ptr
STDMETHOD SetWorldViewLH, :ptr, :ptr
STDMETHOD Begin, :DWORD
STDMETHOD Draw, :ptr, :ptr, :ptr, :ptr, :D3DCOLOR
STDMETHOD Flush
STDMETHOD _End
STDMETHOD OnLostDevice
STDMETHOD OnResetDevice
ID3DXSprite		ENDS


;BOOL
D3DXCheckVersion proto WINAPI \
	    d3dsdkvers: UINT,
	   d3dxsdkvers: UINT

;HRESULT
D3DXCreateFontA proto WINAPI \
		device: ptr IDirect3DDevice9,
		height: SINT,
		_width: UINT,
		weight: UINT,
	     miplevels: UINT,
		italic: BOOL,
	       charset: DWORD,
	     precision: DWORD,
	       quality: DWORD,
	pitchandfamily: DWORD,
	      facename: ptr char,
		  font: ptr ID3DXFont

;HRESULT
D3DXCreateFontW proto WINAPI \
		device: ptr IDirect3DDevice9,
		height: SINT,
		_width: UINT,
		weight: UINT,
	     miplevels: UINT,
		italic: BOOL,
	       charset: DWORD,
	     precision: DWORD,
	       quality: DWORD,
	pitchandfamily: DWORD,
	      facename: ptr WCHAR,
		  font: ptr ID3DXFont

;HRESULT
D3DXCreateFontIndirectA proto WINAPI \
		device: ptr IDirect3DDevice9,
		  desc: ptr D3DXFONT_DESCA,
		  font: ptr ID3DXFont

;HRESULT
D3DXCreateFontIndirectW proto WINAPI \
		device: ptr IDirect3DDevice9,
		  desc: ptr D3DXFONT_DESCW,
		  font: ptr ID3DXFont

;HRESULT
D3DXCreateLine proto WINAPI \
		device: ptr IDirect3DDevice9,
		  line: ptr ID3DXLine

;HRESULT
D3DXCreateRenderToEnvMap proto WINAPI \
		device: ptr IDirect3DDevice9,
		 _size: UINT,
	     miplevels: UINT,
		format: D3DFORMAT,
	       stencil: BOOL,
	stencil_format: D3DFORMAT,
		  rtem: ptr ID3DXRenderToEnvMap

;HRESULT
D3DXCreateRenderToSurface proto WINAPI \
		device: ptr IDirect3DDevice9,
		_width: UINT,
		height: UINT,
		format: D3DFORMAT,
	       stencil: BOOL,
	stencil_format: D3DFORMAT,
		   rts: ptr ID3DXRenderToSurface

;HRESULT
D3DXCreateSprite proto WINAPI \
		device: ptr IDirect3DDevice9,
		sprite: ptr ID3DXSprite

;BOOL
D3DXDebugMute proto WINAPI \
		  mute: BOOL

;UINT
D3DXGetDriverLevel proto WINAPI \
		device: ptr IDirect3DDevice9
.list
endif ;; _D3DX9CORE_H
