ifndef _IImgCtxObjects_H_
define _IImgCtxObjects_H_

include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

CALLBACK(PFNIMGCTXCALLBACK, :ptr, :ptr)

IMGCHG_SIZE		equ 0x0001
IMGCHG_VIEW		equ 0x0002
IMGCHG_COMPLETE		equ 0x0004
IMGCHG_ANIMATE		equ 0x0008
IMGCHG_MASK		equ 0x000F

IMGLOAD_NOTLOADED	equ 0x00100000
IMGLOAD_LOADING		equ 0x00200000
IMGLOAD_STOPPED		equ 0x00400000
IMGLOAD_ERROR		equ 0x00800000
IMGLOAD_COMPLETE	equ 0x01000000
IMGLOAD_MASK		equ 0x01F00000

IMGBITS_NONE		equ 0x02000000
IMGBITS_PARTIAL		equ 0x04000000
IMGBITS_TOTAL		equ 0x08000000
IMGBITS_MASK		equ 0x0E000000

IMGANIM_ANIMATED	equ 0x10000000
IMGANIM_MASK		equ 0x10000000

IMGTRANS_OPAQUE		equ 0x20000000
IMGTRANS_MASK		equ 0x20000000

DWN_COLORMODE		equ 0x0000003F
DWN_DOWNLOADONLY	equ 0x00000040
DWN_FORCEDITHER		equ 0x00000080
DWN_RAWIMAGE		equ 0x00000100
DWN_MIRRORIMAGE		equ 0x00000200

DEFINE_GUID(IID_IImgCtx, 0x3050f3d7, 0x98b5, 0x11cf, 0xbb, 0x82, 0x00, 0xaa, 0x00, 0xbd, 0xce, 0x0b)

.comdef IImgCtx
ifndef NO_BASEINTERFACE_FUNCS
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
endif
    Load		proc :LPCWSTR, :DWORD
    SelectChanges	proc :ULONG, :ULONG, :BOOL
    SetCallback		proc :PFNIMGCTXCALLBACK, :ptr
    Disconnect		proc
    GetUpdateRects	proc :ptr, :ptr, :ptr
    GetStateInfo	proc :ptr, :ptr, :BOOL
    GetPalette		proc :ptr
    Draw		proc :HDC, :ptr
    Tile		proc :HDC, :ptr, :ptr, :ptr
    StretchBlt		proc :HDC, :int_t, :int_t, :int_t, :int_t, :int_t, :int_t, :int_t, :int_t, :DWORD
    .ends

DEFINE_GUID(CLSID_IImgCtx, 0x3050f3d6, 0x98b5, 0x11cf, 0xbb, 0x82, 0x00, 0xaa, 0x00, 0xbd, 0xce, 0x0b)

endif

endif
