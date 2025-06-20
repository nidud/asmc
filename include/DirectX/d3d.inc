ifndef _D3D_H_
define _D3D_H_

ifndef DIRECT3D_VERSION
DIRECT3D_VERSION	equ 0x0700
endif

if(DIRECT3D_VERSION LT 0x0800)

include stdlib.inc

COM_NO_WINDOWS_H equ 1
include objbase.inc

if defined( _WIN32 ) AND NOT defined( _NO_COM)
DEFINE_GUID( IID_IDirect3D,		0x3BBA0080,0x2421,0x11CF,0xA3,0x1A,0x00,0xAA,0x00,0xB9,0x33,0x56 );
if(DIRECT3D_VERSION GE 0x0500)
DEFINE_GUID( IID_IDirect3D2,		0x6aae1ec1,0x662a,0x11d0,0x88,0x9d,0x00,0xaa,0x00,0xbb,0xb7,0x6a);
endif
if(DIRECT3D_VERSION GE 0x0600)
DEFINE_GUID( IID_IDirect3D3,		0xbb223240,0xe72b,0x11d0,0xa9,0xb4,0x00,0xaa,0x00,0xc0,0x99,0x3e);
endif
if(DIRECT3D_VERSION GE 0x0700)
DEFINE_GUID( IID_IDirect3D7,		0xf5049e77,0x4861,0x11d2,0xa4,0x7,0x0,0xa0,0xc9,0x6,0x29,0xa8);
endif

if(DIRECT3D_VERSION GE 0x0500)
DEFINE_GUID( IID_IDirect3DRampDevice,	0xF2086B20,0x259F,0x11CF,0xA3,0x1A,0x00,0xAA,0x00,0xB9,0x33,0x56 );
DEFINE_GUID( IID_IDirect3DRGBDevice,	0xA4665C60,0x2673,0x11CF,0xA3,0x1A,0x00,0xAA,0x00,0xB9,0x33,0x56 );
DEFINE_GUID( IID_IDirect3DHALDevice,	0x84E63dE0,0x46AA,0x11CF,0x81,0x6F,0x00,0x00,0xC0,0x20,0x15,0x6E );
DEFINE_GUID( IID_IDirect3DMMXDevice,	0x881949a1,0xd6f3,0x11d0,0x89,0xab,0x00,0xa0,0xc9,0x05,0x41,0x29 );
endif

if(DIRECT3D_VERSION GE 0x0600)
DEFINE_GUID( IID_IDirect3DRefDevice,	0x50936643, 0x13e9, 0x11d1, 0x89, 0xaa, 0x0, 0xa0, 0xc9, 0x5, 0x41, 0x29);
DEFINE_GUID( IID_IDirect3DNullDevice, 0x8767df22, 0xbacc, 0x11d1, 0x89, 0x69, 0x0, 0xa0, 0xc9, 0x6, 0x29, 0xa8);
endif
if(DIRECT3D_VERSION GE 0x0700)
DEFINE_GUID( IID_IDirect3DTnLHalDevice, 0xf5049e78, 0x4861, 0x11d2, 0xa4, 0x7, 0x0, 0xa0, 0xc9, 0x6, 0x29, 0xa8);
endif


DEFINE_GUID( IID_IDirect3DDevice,	0x64108800,0x957d,0X11d0,0x89,0xab,0x00,0xa0,0xc9,0x05,0x41,0x29 );
if(DIRECT3D_VERSION GE 0x0500)
DEFINE_GUID( IID_IDirect3DDevice2,  0x93281501, 0x8cf8, 0x11d0, 0x89, 0xab, 0x0, 0xa0, 0xc9, 0x5, 0x41, 0x29);
endif
if(DIRECT3D_VERSION GE 0x0600)
DEFINE_GUID( IID_IDirect3DDevice3,  0xb0ab3b60, 0x33d7, 0x11d1, 0xa9, 0x81, 0x0, 0xc0, 0x4f, 0xd7, 0xb1, 0x74);
endif
if(DIRECT3D_VERSION GE 0x0700)
DEFINE_GUID( IID_IDirect3DDevice7,  0xf5049e79, 0x4861, 0x11d2, 0xa4, 0x7, 0x0, 0xa0, 0xc9, 0x6, 0x29, 0xa8);
endif

DEFINE_GUID( IID_IDirect3DTexture,	0x2CDCD9E0,0x25A0,0x11CF,0xA3,0x1A,0x00,0xAA,0x00,0xB9,0x33,0x56 );
if(DIRECT3D_VERSION GE 0x0500)
DEFINE_GUID( IID_IDirect3DTexture2, 0x93281502, 0x8cf8, 0x11d0, 0x89, 0xab, 0x0, 0xa0, 0xc9, 0x5, 0x41, 0x29);
endif

DEFINE_GUID( IID_IDirect3DLight,	0x4417C142,0x33AD,0x11CF,0x81,0x6F,0x00,0x00,0xC0,0x20,0x15,0x6E );

DEFINE_GUID( IID_IDirect3DMaterial,	0x4417C144,0x33AD,0x11CF,0x81,0x6F,0x00,0x00,0xC0,0x20,0x15,0x6E );
if(DIRECT3D_VERSION GE 0x0500)
DEFINE_GUID( IID_IDirect3DMaterial2,	0x93281503, 0x8cf8, 0x11d0, 0x89, 0xab, 0x0, 0xa0, 0xc9, 0x5, 0x41, 0x29);
endif
if(DIRECT3D_VERSION GE 0x0600)
DEFINE_GUID( IID_IDirect3DMaterial3,	0xca9c46f4, 0xd3c5, 0x11d1, 0xb7, 0x5a, 0x0, 0x60, 0x8, 0x52, 0xb3, 0x12);
endif

DEFINE_GUID( IID_IDirect3DExecuteBuffer,0x4417C145,0x33AD,0x11CF,0x81,0x6F,0x00,0x00,0xC0,0x20,0x15,0x6E );
DEFINE_GUID( IID_IDirect3DViewport,	0x4417C146,0x33AD,0x11CF,0x81,0x6F,0x00,0x00,0xC0,0x20,0x15,0x6E );
if(DIRECT3D_VERSION GE 0x0500)
DEFINE_GUID( IID_IDirect3DViewport2,	0x93281500, 0x8cf8, 0x11d0, 0x89, 0xab, 0x0, 0xa0, 0xc9, 0x5, 0x41, 0x29);
endif
if(DIRECT3D_VERSION GE 0x0600)
DEFINE_GUID( IID_IDirect3DViewport3,	0xb0ab3b61, 0x33d7, 0x11d1, 0xa9, 0x81, 0x0, 0xc0, 0x4f, 0xd7, 0xb1, 0x74);
endif
if(DIRECT3D_VERSION GE 0x0600)
DEFINE_GUID( IID_IDirect3DVertexBuffer, 0x7a503555, 0x4a83, 0x11d1, 0xa5, 0xdb, 0x0, 0xa0, 0xc9, 0x3, 0x67, 0xf8);
endif
if(DIRECT3D_VERSION GE 0x0700)
DEFINE_GUID( IID_IDirect3DVertexBuffer7, 0xf5049e7d, 0x4861, 0x11d2, 0xa4, 0x7, 0x0, 0xa0, 0xc9, 0x6, 0x29, 0xa8);
endif
endif

LPDIRECT3D		typedef ptr IDirect3D
LPDIRECT3DDEVICE	typedef ptr IDirect3DDevice
LPDIRECT3DEXECUTEBUFFER typedef ptr IDirect3DExecuteBuffer
LPDIRECT3DLIGHT		typedef ptr IDirect3DLight
LPDIRECT3DMATERIAL	typedef ptr IDirect3DMaterial
LPDIRECT3DTEXTURE	typedef ptr IDirect3DTexture
LPDIRECT3DVIEWPORT	typedef ptr IDirect3DViewport

if(DIRECT3D_VERSION GE 0x0500)
LPDIRECT3D2		typedef ptr IDirect3D2
LPDIRECT3DDEVICE2	typedef ptr IDirect3DDevice2
LPDIRECT3DMATERIAL2	typedef ptr IDirect3DMaterial2
LPDIRECT3DTEXTURE2	typedef ptr IDirect3DTexture2
LPDIRECT3DVIEWPORT2	typedef ptr IDirect3DViewport2
endif

if(DIRECT3D_VERSION GE 0x0600)
LPDIRECT3D3		typedef ptr IDirect3D3
LPDIRECT3DDEVICE3	typedef ptr IDirect3DDevice3
LPDIRECT3DMATERIAL3	typedef ptr IDirect3DMaterial3
LPDIRECT3DVIEWPORT3	typedef ptr IDirect3DViewport3
LPDIRECT3DVERTEXBUFFER	typedef ptr IDirect3DVertexBuffer
endif

if(DIRECT3D_VERSION GE 0x0700)
LPDIRECT3D7		typedef ptr IDirect3D7
LPDIRECT3DDEVICE7	typedef ptr IDirect3DDevice7
LPDIRECT3DVERTEXBUFFER7 typedef ptr IDirect3DVertexBuffer7
endif

include d3dtypes.inc
include d3dcaps.inc

.comdef IDirect3D : public IUnknown

    Initialize		proc :REFCLSID
    EnumDevices		proc :LPD3DENUMDEVICESCALLBACK, :LPVOID
    CreateLight		proc :ptr, :ptr
    CreateMaterial	proc :ptr, :ptr
    CreateViewport	proc :ptr, :ptr
    FindDevice		proc :LPD3DFINDDEVICESEARCH, :LPD3DFINDDEVICERESULT

    .ends

LPDIRECT3D		typedef ptr IDirect3D

if(DIRECT3D_VERSION GE 0x0500)

.comdef IDirect3D2 : public IUnknown

    EnumDevices		proc :LPD3DENUMDEVICESCALLBACK, :LPVOID
    CreateLight		proc :ptr, :ptr
    CreateMaterial	proc :ptr, :ptr
    CreateViewport	proc :ptr, :ptr
    FindDevice		proc :LPD3DFINDDEVICESEARCH, :LPD3DFINDDEVICERESULT
    CreateDevice	proc :REFCLSID, :LPDIRECTDRAWSURFACE, :ptr

    .ends

LPDIRECT3D2		typedef ptr IDirect3D2

endif

if(DIRECT3D_VERSION GE 0x0600)

.comdef IDirect3D3 : public IUnknown

    EnumDevices		proc :LPD3DENUMDEVICESCALLBACK, :LPVOID
    CreateLight		proc :ptr, :LPUNKNOWN
    CreateMaterial	proc :ptr, :LPUNKNOWN
    CreateViewport	proc :ptr, :LPUNKNOWN
    FindDevice		proc :LPD3DFINDDEVICESEARCH, :LPD3DFINDDEVICERESULT
    CreateDevice	proc :REFCLSID, :LPDIRECTDRAWSURFACE4, :ptr, :LPUNKNOWN
    CreateVertexBuffer	proc :LPD3DVERTEXBUFFERDESC, :ptr, :DWORD, :LPUNKNOWN
    EnumZBufferFormats	proc :REFCLSID, :LPD3DENUMPIXELFORMATSCALLBACK, :LPVOID
    EvictManagedTextures proc

    .ends

LPDIRECT3D3		typedef ptr IDirect3D3

endif

if(DIRECT3D_VERSION GE 0x0700)

.comdef IDirect3D7 : public IUnknown

    EnumDevices		proc :LPD3DENUMDEVICESCALLBACK7, :LPVOID
    CreateDevice	proc :REFCLSID, :LPDIRECTDRAWSURFACE7, :ptr
    CreateVertexBuffer	proc :LPD3DVERTEXBUFFERDESC, :ptr, :DWORD
    EnumZBufferFormats	proc :REFCLSID, :LPD3DENUMPIXELFORMATSCALLBACK, :LPVOID
    EvictManagedTexture proc

    .ends

LPDIRECT3D7		typedef ptr IDirect3D7

endif

.comdef IDirect3DDevice : public IUnknown

    Initialize		proc :LPDIRECT3D, :LPGUID, :LPD3DDEVICEDESC
    GetCaps		proc :LPD3DDEVICEDESC, :LPD3DDEVICEDESC
    SwapTextureHandles	proc :LPDIRECT3DTEXTURE, :LPDIRECT3DTEXTURE
    CreateExecuteBuffer proc :LPD3DEXECUTEBUFFERDESC, :ptr, :ptr
    GetStats		proc :LPD3DSTATS
    Execute		proc :LPDIRECT3DEXECUTEBUFFER, :LPDIRECT3DVIEWPORT, :DWORD
    AddViewport		proc :LPDIRECT3DVIEWPORT
    DeleteViewport	proc :LPDIRECT3DVIEWPORT
    NextViewport	proc :LPDIRECT3DVIEWPORT, :ptr, :DWORD
    Pick		proc :LPDIRECT3DEXECUTEBUFFER, :LPDIRECT3DVIEWPORT, :DWORD, :LPD3DRECT
    GetPickRecords	proc :LPDWORD, :LPD3DPICKRECORD
    EnumTextureFormats	proc :LPD3DENUMTEXTUREFORMATSCALLBACK, :LPVOID
    CreateMatrix	proc :LPD3DMATRIXHANDLE
    SetMatrix		proc :D3DMATRIXHANDLE, :LPD3DMATRIX
    GetMatrix		proc :D3DMATRIXHANDLE, :LPD3DMATRIX
    DeleteMatrix	proc :D3DMATRIXHANDLE
    BeginScene		proc
    EndScene		proc
    GetDirect3D		proc :ptr

    .ends

LPDIRECT3DDEVICE	typedef ptr IDirect3DDevice

if(DIRECT3D_VERSION GE 0x0500)

.comdef IDirect3DDevice2 : public IUnknown

    GetCaps		proc :LPD3DDEVICEDESC, :LPD3DDEVICEDESC
    SwapTextureHandles	proc :LPDIRECT3DTEXTURE2, :LPDIRECT3DTEXTURE2
    GetStats		proc :LPD3DSTATS
    AddViewport		proc :LPDIRECT3DVIEWPORT2
    DeleteViewport	proc :LPDIRECT3DVIEWPORT2
    NextViewport	proc :LPDIRECT3DVIEWPORT2, :ptr, :DWORD
    EnumTextureFormats	proc :LPD3DENUMTEXTUREFORMATSCALLBACK, :LPVOID
    BeginScene		proc
    EndScene		proc
    GetDirect3D		proc :ptr
    SetCurrentViewport	proc :LPDIRECT3DVIEWPORT2
    GetCurrentViewport	proc :ptr
    SetRenderTarget	proc :LPDIRECTDRAWSURFACE, :DWORD
    GetRenderTarget	proc :ptr
    Begin		proc :D3DPRIMITIVETYPE, :D3DVERTEXTYPE, :DWORD
    BeginIndexed	proc :D3DPRIMITIVETYPE, :D3DVERTEXTYPE, :LPVOID, :DWORD, :DWORD
    Vertex		proc :LPVOID
    Index		proc :WORD
    _End		proc :DWORD
    GetRenderState	proc :D3DRENDERSTATETYPE, :LPDWORD
    SetRenderState	proc :D3DRENDERSTATETYPE, :DWORD
    GetLightState	proc :D3DLIGHTSTATETYPE, :LPDWORD
    SetLightState	proc :D3DLIGHTSTATETYPE, :DWORD
    SetTransform	proc :D3DTRANSFORMSTATETYPE, :LPD3DMATRIX
    GetTransform	proc :D3DTRANSFORMSTATETYPE, :LPD3DMATRIX
    MultiplyTransform	proc :D3DTRANSFORMSTATETYPE, :LPD3DMATRIX
    DrawPrimitive	proc :D3DPRIMITIVETYPE, :D3DVERTEXTYPE, :LPVOID, :DWORD, :DWORD
    DrawIndexedPrimitive proc :D3DPRIMITIVETYPE, :D3DVERTEXTYPE, :LPVOID, :DWORD, :LPWORD, :DWORD, :DWORD
    SetClipStatus	proc :LPD3DCLIPSTATUS
    GetClipStatus	proc :LPD3DCLIPSTATUS

    .ends

LPDIRECT3DDEVICE2	typedef ptr IDirect3DDevice2

endif

if(DIRECT3D_VERSION GE 0x0600)

.comdef IDirect3DDevice3 : public IUnknown

    GetCaps		proc :LPD3DDEVICEDESC, :LPD3DDEVICEDESC
    GetStats		proc :LPD3DSTATS
    AddViewport		proc :LPDIRECT3DVIEWPORT3
    DeleteViewport	proc :LPDIRECT3DVIEWPORT3
    NextViewport	proc :LPDIRECT3DVIEWPORT3, :ptr, :DWORD
    EnumTextureFormats	proc :LPD3DENUMPIXELFORMATSCALLBACK, :LPVOID
    BeginScene		proc
    EndScene		proc
    GetDirect3D		proc :ptr
    SetCurrentViewport	proc :LPDIRECT3DVIEWPORT3
    GetCurrentViewport	proc :ptr
    SetRenderTarget	proc :LPDIRECTDRAWSURFACE4, :DWORD
    GetRenderTarget	proc :ptr
    Begin		proc :D3DPRIMITIVETYPE, :DWORD, :DWORD
    BeginIndexed	proc :D3DPRIMITIVETYPE, :DWORD, :LPVOID, :DWORD, :DWORD
    Vertex		proc :LPVOID
    Index		proc :WORD
    _End		proc :DWORD
    GetRenderState	proc :D3DRENDERSTATETYPE, :LPDWORD
    SetRenderState	proc :D3DRENDERSTATETYPE, :DWORD
    GetLightState	proc :D3DLIGHTSTATETYPE, :LPDWORD
    SetLightState	proc :D3DLIGHTSTATETYPE, :DWORD
    SetTransform	proc :D3DTRANSFORMSTATETYPE, :LPD3DMATRIX
    GetTransform	proc :D3DTRANSFORMSTATETYPE, :LPD3DMATRIX
    MultiplyTransform	proc :D3DTRANSFORMSTATETYPE, :LPD3DMATRIX
    DrawPrimitive	proc :D3DPRIMITIVETYPE, :DWORD, :LPVOID, :DWORD, :DWORD
    DrawIndexedPrimitive proc :D3DPRIMITIVETYPE, :DWORD, :LPVOID, :DWORD, :LPWORD, :DWORD, :DWORD
    SetClipStatus	proc :LPD3DCLIPSTATUS
    GetClipStatus	proc :LPD3DCLIPSTATUS
    DrawPrimitiveStrided proc :D3DPRIMITIVETYPE, :DWORD, :LPD3DDRAWPRIMITIVESTRIDEDDATA, :DWORD, :DWORD
    DrawIndexedPrimitiveStrided proc :D3DPRIMITIVETYPE, :DWORD, :LPD3DDRAWPRIMITIVESTRIDEDDATA, :DWORD, :LPWORD, :DWORD, :DWORD
    DrawPrimitiveVB	proc :D3DPRIMITIVETYPE, :LPDIRECT3DVERTEXBUFFER, :DWORD, :DWORD, :DWORD
    DrawIndexedPrimitiveVB proc :D3DPRIMITIVETYPE, :LPDIRECT3DVERTEXBUFFER, :LPWORD, :DWORD, :DWORD
    ComputeSphereVisibility proc :LPD3DVECTOR, :LPD3DVALUE, :DWORD, :DWORD, :LPDWORD
    GetTexture		proc :DWORD, :ptr
    SetTexture		proc :DWORD, :LPDIRECT3DTEXTURE2
    GetTextureStageState proc :DWORD, :D3DTEXTURESTAGESTATETYPE, :LPDWORD
    SetTextureStageState proc :DWORD, :D3DTEXTURESTAGESTATETYPE, :DWORD
    ValidateDevice	proc :LPDWORD

    .ends

LPDIRECT3DDEVICE3	typedef ptr IDirect3DDevice3

endif

if(DIRECT3D_VERSION GE 0x0700)

.comdef IDirect3DDevice7 : public IUnknown

    GetCaps		proc :LPD3DDEVICEDESC7
    EnumTextureFormats	proc :LPD3DENUMPIXELFORMATSCALLBACK, :LPVOID
    BeginScene		proc
    EndScene		proc
    GetDirect3D		proc :ptr
    SetRenderTarget	proc :LPDIRECTDRAWSURFACE7, :DWORD
    GetRenderTarget	proc :ptr
    Clear		proc :DWORD, :LPD3DRECT, :DWORD, :D3DCOLOR, :D3DVALUE, :DWORD
    SetTransform	proc :D3DTRANSFORMSTATETYPE, :LPD3DMATRIX
    GetTransform	proc :D3DTRANSFORMSTATETYPE, :LPD3DMATRIX
    SetViewport		proc :LPD3DVIEWPORT7
    MultiplyTransform	proc :D3DTRANSFORMSTATETYPE, :LPD3DMATRIX
    GetViewport		proc :LPD3DVIEWPORT7
    SetMaterial		proc :LPD3DMATERIAL7
    GetMaterial		proc :LPD3DMATERIAL7
    SetLight		proc :DWORD, :LPD3DLIGHT7
    GetLight		proc :DWORD, :LPD3DLIGHT7
    SetRenderState	proc :D3DRENDERSTATETYPE, :DWORD
    GetRenderState	proc :D3DRENDERSTATETYPE, :LPDWORD
    BeginStateBlock	proc
    EndStateBlock	proc :LPDWORD
    PreLoad		proc :LPDIRECTDRAWSURFACE7
    DrawPrimitive	proc :D3DPRIMITIVETYPE, :DWORD, :LPVOID, :DWORD, :DWORD
    DrawIndexedPrimitive proc :D3DPRIMITIVETYPE, :DWORD, :LPVOID, :DWORD, :LPWORD, :DWORD, :DWORD
    SetClipStatus	proc :LPD3DCLIPSTATUS
    GetClipStatus	proc :LPD3DCLIPSTATUS
    DrawPrimitiveStrided proc :D3DPRIMITIVETYPE, :DWORD, :LPD3DDRAWPRIMITIVESTRIDEDDATA, :DWORD, :DWORD
    DrawIndexedPrimitiveStrided proc :D3DPRIMITIVETYPE, :DWORD, :LPD3DDRAWPRIMITIVESTRIDEDDATA, :DWORD, :LPWORD, :DWORD, :DWORD
    DrawPrimitiveVB	proc :D3DPRIMITIVETYPE, :LPDIRECT3DVERTEXBUFFER7, :DWORD, :DWORD, :DWORD
    DrawIndexedPrimitiveVB proc :D3DPRIMITIVETYPE, :LPDIRECT3DVERTEXBUFFER7, :DWORD, :DWORD, :LPWORD, :DWORD, :DWORD
    ComputeSphereVisibility proc :LPD3DVECTOR, :LPD3DVALUE, :DWORD, :DWORD, :LPDWORD
    GetTexture		proc :DWORD, :ptr
    SetTexture		proc :DWORD, :LPDIRECTDRAWSURFACE7
    GetTextureStageState proc :DWORD, :D3DTEXTURESTAGESTATETYPE, :LPDWORD
    SetTextureStageState proc :DWORD, :D3DTEXTURESTAGESTATETYPE, :DWORD
    ValidateDevice	proc :LPDWORD
    ApplyStateBlock	proc :DWORD
    CaptureStateBlock	proc :DWORD
    DeleteStateBlock	proc :DWORD
    CreateStateBlock	proc :D3DSTATEBLOCKTYPE, :LPDWORD
    Load		proc :LPDIRECTDRAWSURFACE7, :LPPOINT, :LPDIRECTDRAWSURFACE7, :LPRECT, :DWORD
    LightEnable		proc :DWORD, :BOOL
    GetLightEnable	proc :DWORD, :ptr
    SetClipPlane	proc :DWORD, :ptr
    GetClipPlane	proc :DWORD, :ptr
    GetInfo		proc :DWORD, :LPVOID, :DWORD

    .ends

LPDIRECT3DDEVICE7	typedef ptr IDirect3DDevice7

endif

.comdef IDirect3DExecuteBuffer : public IUnknown

    Initialize		proc :LPDIRECT3DDEVICE, :LPD3DEXECUTEBUFFERDESC
    _Lock		proc :LPD3DEXECUTEBUFFERDESC
    Unlock		proc
    SetExecuteData	proc :LPD3DEXECUTEDATA
    GetExecuteData	proc :LPD3DEXECUTEDATA
    Validate		proc :LPDWORD, :LPD3DVALIDATECALLBACK, :LPVOID, :DWORD
    Optimize		proc :DWORD

    .ends

LPDIRECT3DEXECUTEBUFFER typedef ptr IDirect3DExecuteBuffer


.comdef IDirect3DLight : public IUnknown

    Initialize		proc :LPDIRECT3D
    SetLight		proc :LPD3DLIGHT
    GetLight		proc :LPD3DLIGHT

    .ends

LPDIRECT3DLIGHT		typedef ptr IDirect3DLight


.comdef IDirect3DMaterial : public IUnknown

    Initialize		proc :LPDIRECT3D
    SetMaterial		proc :LPD3DMATERIAL
    GetMaterial		proc :LPD3DMATERIAL
    GetHandle		proc :LPDIRECT3DDEVICE, :LPD3DMATERIALHANDLE
    Reserve		proc
    Unreserve		proc

    .ends

LPDIRECT3DMATERIAL	typedef ptr IDirect3DMaterial


if(DIRECT3D_VERSION GE 0x0500)

.comdef IDirect3DMaterial2 : public IUnknown

    SetMaterial		proc :LPD3DMATERIAL
    GetMaterial		proc :LPD3DMATERIAL
    GetHandle		proc :LPDIRECT3DDEVICE2, :LPD3DMATERIALHANDLE

    .ends

LPDIRECT3DMATERIAL2	typedef ptr IDirect3DMaterial2

endif

if(DIRECT3D_VERSION GE 0x0600)

.comdef IDirect3DMaterial3 : public IUnknown

    SetMaterial		proc :LPD3DMATERIAL
    GetMaterial		proc :LPD3DMATERIAL
    GetHandle		proc :LPDIRECT3DDEVICE3, :LPD3DMATERIALHANDLE

    .ends

LPDIRECT3DMATERIAL3	typedef ptr IDirect3DMaterial3

endif

.comdef IDirect3DTexture : public IUnknown

    Initialize		proc :LPDIRECT3DDEVICE, :LPDIRECTDRAWSURFACE
    GetHandle		proc :LPDIRECT3DDEVICE, :LPD3DTEXTUREHANDLE
    PaletteChanged	proc :DWORD, :DWORD
    Load		proc :LPDIRECT3DTEXTURE
    Unload		proc

    .ends

LPDIRECT3DTEXTURE	typedef ptr IDirect3DTexture

if(DIRECT3D_VERSION GE 0x0500)

.comdef IDirect3DTexture2 : public IUnknown

    GetHandle		proc :LPDIRECT3DDEVICE2, :LPD3DTEXTUREHANDLE
    PaletteChanged	proc :DWORD, :DWORD
    Load		proc :LPDIRECT3DTEXTURE2

    .ends

LPDIRECT3DTEXTURE2	typedef ptr IDirect3DTexture2

endif

.comdef IDirect3DViewport : public IUnknown

    Initialize		proc :LPDIRECT3D
    GetViewport		proc :LPD3DVIEWPORT
    SetViewport		proc :LPD3DVIEWPORT
    TransformVertices	proc :DWORD, :LPD3DTRANSFORMDATA, :DWORD, :LPDWORD
    LightElements	proc :DWORD, :LPD3DLIGHTDATA
    SetBackground	proc :D3DMATERIALHANDLE
    GetBackground	proc :LPD3DMATERIALHANDLE, :LPBOOL
    SetBackgroundDepth	proc :LPDIRECTDRAWSURFACE
    GetBackgroundDepth	proc :ptr, :LPBOOL
    Clear		proc :DWORD, :LPD3DRECT, :DWORD
    AddLight		proc :LPDIRECT3DLIGHT
    DeleteLight		proc :LPDIRECT3DLIGHT
    NextLight		proc :LPDIRECT3DLIGHT, :ptr, :DWORD

    .ends

LPDIRECT3DVIEWPORT	typedef ptr IDirect3DViewport

if(DIRECT3D_VERSION GE 0x0500)

.comdef IDirect3DViewport2 : public IDirect3DViewport

    GetViewport2	proc :LPD3DVIEWPORT2
    SetViewport2	proc :LPD3DVIEWPORT2

    .ends

LPDIRECT3DVIEWPORT2	typedef ptr IDirect3DViewport2

endif

if(DIRECT3D_VERSION GE 0x0600)

.comdef IDirect3DViewport3 : public IDirect3DViewport2

    SetBackgroundDepth2 proc :LPDIRECTDRAWSURFACE4
    GetBackgroundDepth2 proc :ptr, :LPBOOL
    Clear2		proc :DWORD, :LPD3DRECT, :DWORD, :D3DCOLOR, :D3DVALUE, :DWORD

    .ends

LPDIRECT3DVIEWPORT3	typedef ptr IDirect3DViewport3

endif

if(DIRECT3D_VERSION GE 0x0600)

.comdef IDirect3DVertexBuffer : public IUnknown

    _Lock		proc :DWORD, :ptr, :LPDWORD
    Unlock		proc
    ProcessVertices	proc :DWORD, :DWORD, :DWORD, :LPDIRECT3DVERTEXBUFFER, :DWORD, :LPDIRECT3DDEVICE3, :DWORD
    GetVertexBufferDesc proc :LPD3DVERTEXBUFFERDESC
    Optimize		proc :LPDIRECT3DDEVICE3, :DWORD

    .ends

LPDIRECT3DVERTEXBUFFER	typedef ptr IDirect3DVertexBuffer

endif

if(DIRECT3D_VERSION GE 0x0700)

.comdef IDirect3DVertexBuffer7 : public IUnknown

    _Lock		proc :DWORD, :ptr, :LPDWORD
    Unlock		proc
    ProcessVertices	proc :DWORD, :DWORD, :DWORD, :LPDIRECT3DVERTEXBUFFER7, :DWORD, :LPDIRECT3DDEVICE7, :DWORD
    GetVertexBufferDesc proc :LPD3DVERTEXBUFFERDESC
    Optimize		proc :LPDIRECT3DDEVICE7, :DWORD
    ProcessVerticesStrided proc :DWORD, :DWORD, :DWORD, :LPD3DDRAWPRIMITIVESTRIDEDDATA, :DWORD, :LPDIRECT3DDEVICE7, :DWORD

    .ends

LPDIRECT3DVERTEXBUFFER7 typedef ptr IDirect3DVertexBuffer7

endif

if(DIRECT3D_VERSION GE 0x0500)

D3DNEXT_NEXT		equ 0x00000001
D3DNEXT_HEAD		equ 0x00000002
D3DNEXT_TAIL		equ 0x00000004
D3DDP_WAIT		equ 0x00000001
endif

if (DIRECT3D_VERSION EQ 0x0500)
D3DDP_OUTOFORDER	equ 0x00000002
endif

if(DIRECT3D_VERSION GE 0x0500)
D3DDP_DONOTCLIP		equ 0x00000004
D3DDP_DONOTUPDATEEXTENTS equ 0x00000008
endif

if(DIRECT3D_VERSION GE 0x0600)
D3DDP_DONOTLIGHT	equ 0x00000010
endif

D3D_OK			equ DD_OK
D3DERR_BADMAJORVERSION	equ MAKE_DDHRESULT(700)
D3DERR_BADMINORVERSION	equ MAKE_DDHRESULT(701)

if(DIRECT3D_VERSION GE 0x0500)
D3DERR_INVALID_DEVICE	equ MAKE_DDHRESULT(705)
D3DERR_INITFAILED	equ MAKE_DDHRESULT(706)

D3DERR_DEVICEAGGREGATED equ MAKE_DDHRESULT(707)
endif

D3DERR_EXECUTE_CREATE_FAILED equ MAKE_DDHRESULT(710)
D3DERR_EXECUTE_DESTROY_FAILED equ MAKE_DDHRESULT(711)
D3DERR_EXECUTE_LOCK_FAILED equ MAKE_DDHRESULT(712)
D3DERR_EXECUTE_UNLOCK_FAILED equ MAKE_DDHRESULT(713)
D3DERR_EXECUTE_LOCKED	equ MAKE_DDHRESULT(714)
D3DERR_EXECUTE_NOT_LOCKED equ MAKE_DDHRESULT(715)

D3DERR_EXECUTE_FAILED	equ MAKE_DDHRESULT(716)
D3DERR_EXECUTE_CLIPPED_FAILED equ MAKE_DDHRESULT(717)

D3DERR_TEXTURE_NO_SUPPORT equ MAKE_DDHRESULT(720)
D3DERR_TEXTURE_CREATE_FAILED equ MAKE_DDHRESULT(721)
D3DERR_TEXTURE_DESTROY_FAILED equ MAKE_DDHRESULT(722)
D3DERR_TEXTURE_LOCK_FAILED equ MAKE_DDHRESULT(723)
D3DERR_TEXTURE_UNLOCK_FAILED equ MAKE_DDHRESULT(724)
D3DERR_TEXTURE_LOAD_FAILED equ MAKE_DDHRESULT(725)
D3DERR_TEXTURE_SWAP_FAILED equ MAKE_DDHRESULT(726)
D3DERR_TEXTURE_LOCKED	equ MAKE_DDHRESULT(727)
D3DERR_TEXTURE_NOT_LOCKED equ MAKE_DDHRESULT(728)
D3DERR_TEXTURE_GETSURF_FAILED equ MAKE_DDHRESULT(729)

D3DERR_MATRIX_CREATE_FAILED equ MAKE_DDHRESULT(730)
D3DERR_MATRIX_DESTROY_FAILED equ MAKE_DDHRESULT(731)
D3DERR_MATRIX_SETDATA_FAILED equ MAKE_DDHRESULT(732)
D3DERR_MATRIX_GETDATA_FAILED equ MAKE_DDHRESULT(733)
D3DERR_SETVIEWPORTDATA_FAILED equ MAKE_DDHRESULT(734)

if(DIRECT3D_VERSION GE 0x0500)
D3DERR_INVALIDCURRENTVIEWPORT equ MAKE_DDHRESULT(735)
D3DERR_INVALIDPRIMITIVETYPE equ MAKE_DDHRESULT(736)
D3DERR_INVALIDVERTEXTYPE equ MAKE_DDHRESULT(737)
D3DERR_TEXTURE_BADSIZE	equ MAKE_DDHRESULT(738)
D3DERR_INVALIDRAMPTEXTURE equ MAKE_DDHRESULT(739)
endif

D3DERR_MATERIAL_CREATE_FAILED equ MAKE_DDHRESULT(740)
D3DERR_MATERIAL_DESTROY_FAILED equ MAKE_DDHRESULT(741)
D3DERR_MATERIAL_SETDATA_FAILED equ MAKE_DDHRESULT(742)
D3DERR_MATERIAL_GETDATA_FAILED equ MAKE_DDHRESULT(743)

if(DIRECT3D_VERSION GE 0x0500)
D3DERR_INVALIDPALETTE	equ MAKE_DDHRESULT(744)

D3DERR_ZBUFF_NEEDS_SYSTEMMEMORY equ MAKE_DDHRESULT(745)
D3DERR_ZBUFF_NEEDS_VIDEOMEMORY equ MAKE_DDHRESULT(746)
D3DERR_SURFACENOTINVIDMEM equ MAKE_DDHRESULT(747)
endif

D3DERR_LIGHT_SET_FAILED equ MAKE_DDHRESULT(750)
if(DIRECT3D_VERSION GE 0x0500)
D3DERR_LIGHTHASVIEWPORT equ MAKE_DDHRESULT(751)
D3DERR_LIGHTNOTINTHISVIEWPORT equ MAKE_DDHRESULT(752)
endif

D3DERR_SCENE_IN_SCENE	equ MAKE_DDHRESULT(760)
D3DERR_SCENE_NOT_IN_SCENE equ MAKE_DDHRESULT(761)
D3DERR_SCENE_BEGIN_FAILED equ MAKE_DDHRESULT(762)
D3DERR_SCENE_END_FAILED equ MAKE_DDHRESULT(763)

if(DIRECT3D_VERSION GE 0x0500)
D3DERR_INBEGIN		equ MAKE_DDHRESULT(770)
D3DERR_NOTINBEGIN	equ MAKE_DDHRESULT(771)
D3DERR_NOVIEWPORTS	equ MAKE_DDHRESULT(772)
D3DERR_VIEWPORTDATANOTSET equ MAKE_DDHRESULT(773)
D3DERR_VIEWPORTHASNODEVICE equ MAKE_DDHRESULT(774)
D3DERR_NOCURRENTVIEWPORT equ MAKE_DDHRESULT(775)
endif

if(DIRECT3D_VERSION GE 0x0600)
D3DERR_INVALIDVERTEXFORMAT equ MAKE_DDHRESULT(2048)

D3DERR_COLORKEYATTACHED equ MAKE_DDHRESULT(2050)

D3DERR_VERTEXBUFFEROPTIMIZED equ MAKE_DDHRESULT(2060)
D3DERR_VBUF_CREATE_FAILED equ MAKE_DDHRESULT(2061)
D3DERR_VERTEXBUFFERLOCKED equ MAKE_DDHRESULT(2062)
D3DERR_VERTEXBUFFERUNLOCKFAILED equ MAKE_DDHRESULT(2063)

D3DERR_ZBUFFER_NOTPRESENT equ MAKE_DDHRESULT(2070)
D3DERR_STENCILBUFFER_NOTPRESENT equ MAKE_DDHRESULT(2071)

D3DERR_WRONGTEXTUREFORMAT equ MAKE_DDHRESULT(2072)
D3DERR_UNSUPPORTEDCOLOROPERATION equ MAKE_DDHRESULT(2073)
D3DERR_UNSUPPORTEDCOLORARG equ MAKE_DDHRESULT(2074)
D3DERR_UNSUPPORTEDALPHAOPERATION equ MAKE_DDHRESULT(2075)
D3DERR_UNSUPPORTEDALPHAARG equ MAKE_DDHRESULT(2076)
D3DERR_TOOMANYOPERATIONS equ MAKE_DDHRESULT(2077)
D3DERR_CONFLICTINGTEXTUREFILTER equ MAKE_DDHRESULT(2078)
D3DERR_UNSUPPORTEDFACTORVALUE equ MAKE_DDHRESULT(2079)
D3DERR_CONFLICTINGRENDERSTATE equ MAKE_DDHRESULT(2081)
D3DERR_UNSUPPORTEDTEXTUREFILTER equ MAKE_DDHRESULT(2082)
D3DERR_TOOMANYPRIMITIVES equ MAKE_DDHRESULT(2083)
D3DERR_INVALIDMATRIX	equ MAKE_DDHRESULT(2084)
D3DERR_TOOMANYVERTICES	equ MAKE_DDHRESULT(2085)
D3DERR_CONFLICTINGTEXTUREPALETTE equ MAKE_DDHRESULT(2086)

endif

if(DIRECT3D_VERSION GE 0x0700)
D3DERR_INVALIDSTATEBLOCK equ MAKE_DDHRESULT(2100)
D3DERR_INBEGINSTATEBLOCK equ MAKE_DDHRESULT(2101)
D3DERR_NOTINBEGINSTATEBLOCK equ MAKE_DDHRESULT(2102)
endif

endif
endif
