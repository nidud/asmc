include d3dx9.inc
ifndef _D3DX9CORE_H
define _D3DX9CORE_H

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

.comdef ID3DXBuffer : public IUnknown

    GetBufferPointer	proc
    GetBufferSize	proc
   .ends

D3DXFONT_DESCA		STRUC
Height			SINT ?
Width			UINT ?
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
Width			UINT ?
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

.comdef ID3DXFont : public IUnknown

    GetDevice		proc :ptr
    GetDescA		proc :ptr
    GetDescW		proc :ptr
    GetTextMetricsA	proc :ptr
    GetTextMetricsW	proc :ptr
    GetDC		proc
    GetGlyphData	proc :UINT, :ptr, :ptr, :ptr
    PreloadCharacters	proc :UINT, :UINT
    PreloadGlyphs	proc :UINT, :UINT
    PreloadTextA	proc :ptr, :SINT
    PreloadTextW	proc :ptr, :SINT
    DrawTextA		proc :ptr, :ptr, :SINT, :ptr, :DWORD, :D3DCOLOR
    DrawTextW		proc :ptr, :ptr, :SINT, :ptr, :DWORD, :D3DCOLOR
    OnLostDevice	proc
    OnResetDevice	proc

    .ends

.comdef ID3DXLine : public IUnknown

    GetDevice		proc :ptr
    Begin		proc
    Draw		proc :ptr, :DWORD, :D3DCOLOR
    DrawTransform	proc :ptr, :DWORD, :ptr, :D3DCOLOR
    SetPattern		proc :DWORD
    GetPattern		proc
    SetPatternScale	proc :FLOAT
    GetPatternScale	proc
    SetWidth		proc :FLOAT
    GetWidth		proc
    SetAntialias	proc :BOOL
    GetAntialias	proc
    SetGLLines		proc :BOOL
    GetGLLines		proc
    _End		proc
    OnLostDevice	proc
    OnResetDevice	proc

    .ends

D3DXRTE_DESC		STRUC
Size			UINT ?
MipLevels		UINT ?
Format			D3DFORMAT ?
DepthStencil		BOOL ?
DepthStencilFormat	D3DFORMAT ?
D3DXRTE_DESC		ENDS

.comdef ID3DXRenderToEnvMap : public IUnknown

    GetDevice		proc :ptr
    GetDesc		proc :ptr
    BeginCube		proc :ptr
    BeginSphere		proc :ptr
    BeginHemisphere	proc :ptr, :ptr
    BeginParabolic	proc :ptr, :ptr
    Face		proc :D3DCUBEMAP_FACES, :DWORD
    _End		proc :DWORD
    OnLostDevice	proc
    OnResetDevice	proc

    .ends

D3DXRTS_DESC		STRUC
Width			UINT ?
Height			UINT ?
Format			D3DFORMAT ?
DepthStencil		BOOL ?
DepthStencilFormat	D3DFORMAT ?
D3DXRTS_DESC		ENDS

.comdef ID3DXRenderToSurface : public IUnknown

    GetDevice		proc :ptr
    GetDesc		proc :ptr
    BeginScene		proc :ptr, :ptr
    EndScene		proc :DWORD
    OnLostDevice	proc
    OnResetDevice	proc
   .ends

.comdef ID3DXSprite : public IUnknown

    GetDevice		proc :ptr
    GetTransform	proc :ptr
    SetTransform	proc :ptr
    SetWorldViewRH	proc :ptr, :ptr
    SetWorldViewLH	proc :ptr, :ptr
    Begin		proc :DWORD
    Draw		proc :ptr, :ptr, :ptr, :ptr, :D3DCOLOR
    Flush		proc
    _End		proc
    OnLostDevice	proc
    OnResetDevice	proc
   .ends

D3DXCheckVersion proto WINAPI :UINT, :UINT
D3DXCreateFontA proto WINAPI :ptr, :SINT, :UINT, :UINT, :UINT, :BOOL, :DWORD, :DWORD, :DWORD, :DWORD, :ptr, :ptr
D3DXCreateFontW proto WINAPI :ptr, :SINT, :UINT, :UINT, :UINT, :BOOL, :DWORD, :DWORD, :DWORD, :DWORD, :ptr, :ptr
D3DXCreateFontIndirectA proto WINAPI :ptr, :ptr, :ptr
D3DXCreateFontIndirectW proto WINAPI :ptr, :ptr, :ptr
D3DXCreateLine proto WINAPI :ptr, :ptr
D3DXCreateRenderToEnvMap proto WINAPI :ptr, :UINT, :UINT, :D3DFORMAT, :BOOL, :D3DFORMAT, :ptr
D3DXCreateRenderToSurface proto WINAPI :ptr, :UINT, :UINT, :D3DFORMAT, :BOOL, :D3DFORMAT, :ptr
D3DXCreateSprite proto WINAPI :ptr, :ptr
D3DXDebugMute proto WINAPI :BOOL
D3DXGetDriverLevel proto WINAPI :ptr

endif
