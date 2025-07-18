include d3dx10.inc

ifndef __D3DX10CORE_H__
define __D3DX10CORE_H__

D3DX10_DLL_W		equ <L"d3dx10_43.dll">
D3DX10_DLL_A		equ <"d3dx10_43.dll">

ifdef _UNICODE
D3DX10_DLL		equ <D3DX10_DLL_W>
else
D3DX10_DLL		equ <D3DX10_DLL_A>
endif

D3DX10_SDK_VERSION	equ 43

D3DX10CreateDevice proto WINAPI :ptr, :D3D10_DRIVER_TYPE, :HMODULE, :UINT, :ptr
D3DX10CreateDeviceAndSwapChain proto WINAPI :ptr, :D3D10_DRIVER_TYPE, :HMODULE, :UINT, :ptr, :ptr, :ptr
D3DX10GetFeatureLevel1 proto WINAPI :ptr, :ptr
ifdef D3D_DIAG_DLL
D3DX10DebugMute proto WINAPI :BOOL
endif
D3DX10CheckVersion proto WINAPI :UINT, :UINT

.enum D3DX10_SPRITE_FLAG {
    D3DX10_SPRITE_SORT_TEXTURE		    = 0x01,
    D3DX10_SPRITE_SORT_DEPTH_BACK_TO_FRONT  = 0x02,
    D3DX10_SPRITE_SORT_DEPTH_FRONT_TO_BACK  = 0x04,
    D3DX10_SPRITE_SAVE_STATE		    = 0x08,
    D3DX10_SPRITE_ADDREF_TEXTURES	    = 0x10,
    }

D3DX10_SPRITE		STRUC
matWorld		D3DXMATRIX <>
TexCoord		D3DXVECTOR2 <>
TexSize			D3DXVECTOR2 <>
ColorModulate		D3DXCOLOR <>
pTexture		PVOID ? ; LPID3D10ShaderResourceView
TextureIndex		UINT ?
D3DX10_SPRITE		ENDS


DEFINE_GUID(IID_ID3DX10Sprite, 0xba0b762d, 0x8d28, 0x43ec, 0xb9, 0xdc, 0x2f, 0x84, 0x44, 0x3b, 0x6, 0x14);

.comdef ID3DX10Sprite : public IUnknown

    Begin		proc :UINT
    DrawSpritesBuffered proc :ptr, :UINT
    Flush		proc
    DrawSpritesImmediate proc :ptr, :UINT, :UINT, :UINT
    _End		proc
    GetViewTransform	proc :ptr
    SetViewTransform	proc :ptr
    GetProjectionTransform proc :ptr
    SetProjectionTransform proc :ptr
    GetDevice		proc :ptr
   .ENDS


D3DX10CreateSprite proto WINAPI :ptr, :UINT, :ptr

.comdef ID3DX10DataLoader

    Load		proc
    Decompress		proc :ptr, :ptr
    Destroy		proc
   .ENDS

.comdef ID3DX10DataProcessor

    Process		proc :ptr, :size_t
    CreateDeviceObject	proc :ptr
    Destroy		proc
   .ENDS

DEFINE_GUID(IID_ID3DX10ThreadPump, 0xc93fecfa, 0x6967, 0x478a, 0xab, 0xbc, 0x40, 0x2d, 0x90, 0x62, 0x1f, 0xcb)

.comdef ID3DX10ThreadPump : public IUnknown

    AddWorkItem		proc :ptr, :ptr, :ptr, :ptr
    GetWorkItemCount	proc
    WaitForAllItems	proc
    ProcessDeviceWorkItems proc :UINT
    PurgeAllItems	proc
    GetQueueStatus	proc :ptr, :ptr, :ptr
   .ENDS

D3DX10CreateThreadPump proto WINAPI :UINT, :UINT, :ptr

D3DX10_FONT_DESCA	STRUC
Height			SINT ?
Width			UINT ?
Weight			UINT ?
MipLevels		UINT ?
Italic			BOOL ?
CharSet			db ?
OutputPrecision		db ?
Quality			db ?
PitchAndFamily		db ?
FaceName		SBYTE LF_FACESIZE dup(?)
D3DX10_FONT_DESCA	ENDS
LPD3DX10_FONT_DESCA	typedef ptr D3DX10_FONT_DESCA

D3DX10_FONT_DESCW	STRUC
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
D3DX10_FONT_DESCW	ENDS
LPD3DX10_FONT_DESCW	typedef ptr D3DX10_FONT_DESCW

ifdef _UNICODE
D3DX10_FONT_DESC	typedef D3DX10_FONT_DESCW
LPD3DX10_FONT_DESC	typedef LPD3DX10_FONT_DESCW
else
D3DX10_FONT_DESC	typedef D3DX10_FONT_DESCA
LPD3DX10_FONT_DESC	typedef LPD3DX10_FONT_DESCA
endif

DEFINE_GUID(IID_ID3DX10Font, 0xd79dbb70, 0x5f21, 0x4d36, 0xbb, 0xc2, 0xff, 0x52, 0x5c, 0x21, 0x3c, 0xdc)

.comdef ID3DX10Font : public IUnknown

    GetDevice		proc :ptr
    GetDescA		proc :ptr
    GetDescW		proc :ptr
    GetTextMetricsA	proc :ptr
    GetTextMetricsW	proc :ptr
    GetDC		proc
    GetGlyphData	proc :UINT, :ptr, :ptr, :ptr
    PreloadCharacters	proc :UINT, :UINT
    PreloadGlyphs	proc :UINT, :UINT
    PreloadTextA	proc :LPCSTR, :SINT
    PreloadTextW	proc :LPCWSTR, :SINT
    DrawTextA		proc :LPD3DX10SPRITE, :LPCSTR, :SINT, :LPRECT, :UINT, :D3DXCOLOR
    DrawTextW		proc :LPD3DX10SPRITE, :LPCWSTR, :SINT, :LPRECT, :UINT, :D3DXCOLOR
   .ends

ifndef GetTextMetrics
ifdef _UNICODE
GetTextMetrics		equ <GetTextMetricsW>
else
GetTextMetrics		equ <GetTextMetricsA>
endif
endif

ifndef DrawText
ifdef _UNICODE
DrawText		equ <DrawTextW>
else
DrawText		equ <DrawTextA>
endif
endif

D3DX10CreateFontA proto WINAPI :ptr, :SINT, :UINT, :UINT, :UINT, :BOOL, :UINT, :UINT, :UINT, :UINT, :LPCSTR, ptr
D3DX10CreateFontW proto WINAPI :ptr, :SINT, :UINT, :UINT, :UINT, :BOOL, :UINT, :UINT, :UINT, :UINT, :LPCWSTR, :ptr
ifdef _UNICODE
D3DX10CreateFont	equ <D3DX10CreateFontW>
else
D3DX10CreateFont	equ <D3DX10CreateFontA>
endif

D3DX10CreateFontIndirectA proto WINAPI :ptr, :ptr, :ptr
D3DX10CreateFontIndirectW proto WINAPI :ptr, :ptr, :ptr
ifdef _UNICODE
D3DX10CreateFontIndirect equ <D3DX10CreateFontIndirectW>
else
D3DX10CreateFontIndirect equ <D3DX10CreateFontIndirectA>
endif
D3DX10UnsetAllDeviceObjects proto WINAPI :ptr

_FACD3D equ 0x876
MAKE_D3DHRESULT macro code
	exitm<MAKE_HRESULT( 1, _FACD3D, code )>
	endm
MAKE_D3DSTATUS macro code
	exitm<MAKE_HRESULT( 0, _FACD3D, code )>
	endm

D3DERR_INVALIDCALL	equ MAKE_D3DHRESULT(2156)
D3DERR_WASSTILLDRAWING	equ MAKE_D3DHRESULT(540)

endif
