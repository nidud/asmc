.pragma list(push, 0)

ifndef __REQUIRED_RPCNDR_H_VERSION__
__REQUIRED_RPCNDR_H_VERSION__ equ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
__REQUIRED_RPCSAL_H_VERSION__ equ 100
endif
include rpc.inc
include rpcndr.inc
ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr.inc>
endif
ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif
ifndef __dxgi_h__
__dxgi_h__ equ <>

ifndef __IDXGIObject_FWD_DEFINED__
__IDXGIObject_FWD_DEFINED__ equ 1
endif
ifndef __IDXGIDeviceSubObject_FWD_DEFINED__
__IDXGIDeviceSubObject_FWD_DEFINED__ equ 1
endif
ifndef __IDXGIResource_FWD_DEFINED__
__IDXGIResource_FWD_DEFINED__ equ 1
endif
ifndef __IDXGIKeyedMutex_FWD_DEFINED__
__IDXGIKeyedMutex_FWD_DEFINED__ equ 1
endif
ifndef __IDXGISurface_FWD_DEFINED__
__IDXGISurface_FWD_DEFINED__ equ 1
endif
ifndef __IDXGISurface1_FWD_DEFINED__
__IDXGISurface1_FWD_DEFINED__ equ 1
endif
ifndef __IDXGIAdapter_FWD_DEFINED__
__IDXGIAdapter_FWD_DEFINED__ equ 1
endif
ifndef __IDXGIOutput_FWD_DEFINED__
__IDXGIOutput_FWD_DEFINED__ equ 1
endif
ifndef __IDXGISwapChain_FWD_DEFINED__
__IDXGISwapChain_FWD_DEFINED__ equ 1
endif
ifndef __IDXGIFactory_FWD_DEFINED__
__IDXGIFactory_FWD_DEFINED__ equ 1
endif
ifndef __IDXGIDevice_FWD_DEFINED__
__IDXGIDevice_FWD_DEFINED__ equ 1
endif
ifndef __IDXGIFactory1_FWD_DEFINED__
__IDXGIFactory1_FWD_DEFINED__ equ 1
endif
ifndef __IDXGIAdapter1_FWD_DEFINED__
__IDXGIAdapter1_FWD_DEFINED__ equ 1
endif
ifndef __IDXGIDevice1_FWD_DEFINED__
__IDXGIDevice1_FWD_DEFINED__ equ 1
endif

include oaidl.inc
include ocidl.inc
include dxgitype.inc

DXGI_CPU_ACCESS_NONE	equ 0
DXGI_CPU_ACCESS_DYNAMIC equ 1
DXGI_CPU_ACCESS_READ_WRITE equ 2
DXGI_CPU_ACCESS_SCRATCH equ 3
DXGI_CPU_ACCESS_FIELD	equ 15
DXGI_USAGE_SHADER_INPUT equ ( 1 SHL (0 + 4) )
DXGI_USAGE_RENDER_TARGET_OUTPUT equ ( 1 SHL (1 + 4) )
DXGI_USAGE_BACK_BUFFER	equ ( 1 SHL (2 + 4) )
DXGI_USAGE_SHARED	equ ( 1 SHL (3 + 4) )
DXGI_USAGE_READ_ONLY	equ ( 1 SHL (4 + 4) )
DXGI_USAGE_DISCARD_ON_PRESENT equ ( 1 SHL (5 + 4) )
DXGI_USAGE_UNORDERED_ACCESS equ ( 1 SHL (6 + 4) )
DXGI_USAGE		typedef UINT

DXGI_FRAME_STATISTICS	STRUC
PresentCount		UINT ?
PresentRefreshCount	UINT ?
SyncRefreshCount	UINT ?
SyncQPCTime		LARGE_INTEGER <>
SyncGPUTime		LARGE_INTEGER <>
DXGI_FRAME_STATISTICS	ENDS

DXGI_MAPPED_RECT	STRUC
Pitch			SINT ?
pBits			LPBYTE ?
DXGI_MAPPED_RECT	ENDS

ifdef __midl
LUID			STRUC
LowPart			dd ?
HighPart		LONG ?
LUID			ENDS
PLUID			typedef ptr LUID
endif

DXGI_ADAPTER_DESC	STRUC
Description		WCHAR  128  dup(?)
VendorId		UINT ?
DeviceId		UINT ?
SubSysId		UINT ?
Revision		UINT ?
DedicatedVideoMemory	SIZE_T ?
DedicatedSystemMemory	SIZE_T ?
SharedSystemMemory	SIZE_T ?
AdapterLuid		LUID <>
DXGI_ADAPTER_DESC	ENDS

if NOT defined(HMONITOR_DECLARED) AND NOT defined(HMONITOR) AND (WINVER LT 0x0500)
HMONITOR_DECLARED equ 1
if 0
HMONITOR		typedef HANDLE
endif
DECLARE_HANDLE(HMONITOR)
endif
DXGI_OUTPUT_DESC	STRUC
DeviceName		WCHAR  32  dup(?)
DesktopCoordinates	RECT <>
AttachedToDesktop	BOOL ?
Rotation		DXGI_MODE_ROTATION ?
_Monitor		HMONITOR ?
DXGI_OUTPUT_DESC	ENDS

DXGI_SHARED_RESOURCE	STRUC
Handle			HANDLE ?
DXGI_SHARED_RESOURCE	ENDS

DXGI_RESOURCE_PRIORITY_MINIMUM equ ( 0x28000000 )
DXGI_RESOURCE_PRIORITY_LOW equ ( 0x50000000 )
DXGI_RESOURCE_PRIORITY_NORMAL equ ( 0x78000000 )
DXGI_RESOURCE_PRIORITY_HIGH equ ( 0xa0000000 )
DXGI_RESOURCE_PRIORITY_MAXIMUM equ ( 0xc8000000 )

DXGI_RESIDENCY		typedef SDWORD
DXGI_RESIDENCY_FULLY_RESIDENT equ 1
DXGI_RESIDENCY_RESIDENT_IN_SHARED_MEMORY equ 2
DXGI_RESIDENCY_EVICTED_TO_DISK equ 3

DXGI_SURFACE_DESC	STRUC
Width			UINT ?
Height			UINT ?
Format			DXGI_FORMAT ?
SampleDesc		DXGI_SAMPLE_DESC <>
DXGI_SURFACE_DESC	ENDS

DXGI_SWAP_EFFECT	typedef SDWORD
DXGI_SWAP_EFFECT_DISCARD equ 0
DXGI_SWAP_EFFECT_SEQUENTIAL equ 1

DXGI_SWAP_CHAIN_FLAG	typedef SDWORD
DXGI_SWAP_CHAIN_FLAG_NONPREROTATED equ 1
DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH equ 2
DXGI_SWAP_CHAIN_FLAG_GDI_COMPATIBLE equ 4

DXGI_SWAP_CHAIN_DESC	STRUC
BufferDesc		DXGI_MODE_DESC <>
SampleDesc		DXGI_SAMPLE_DESC <>
BufferUsage		DXGI_USAGE ?
BufferCount		UINT ?
OutputWindow		HWND ?
Windowed		BOOL ?
SwapEffect		DXGI_SWAP_EFFECT ?
Flags			UINT ?
DXGI_SWAP_CHAIN_DESC	ENDS

ifndef __IDXGIObject_INTERFACE_DEFINED__
__IDXGIObject_INTERFACE_DEFINED__ equ 1

.comdef IDXGIObject

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetPrivateData	proc :REFGUID, :UINT, :ptr
    SetPrivateDataInterface proc :REFGUID, :ptr
    GetPrivateData	proc :REFGUID, :ptr, :ptr
    _GetParent		proc :REFIID, :ptr
    .ends
endif

ifndef __IDXGIDeviceSubObject_INTERFACE_DEFINED__
__IDXGIDeviceSubObject_INTERFACE_DEFINED__ equ 1

.comdef IDXGIDeviceSubObject

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetPrivateData	proc :REFGUID, :UINT, :ptr
    SetPrivateDataInterface proc :REFGUID, :ptr
    GetPrivateData	proc :REFGUID, :ptr, :ptr
    _GetParent		proc :REFIID, :ptr
    GetDevice		proc :REFIID, :ptr
    .ends
endif

ifndef __IDXGIResource_INTERFACE_DEFINED__
__IDXGIResource_INTERFACE_DEFINED__ equ 1

.comdef IDXGIResource

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetPrivateData	proc :REFGUID, :UINT, :ptr
    SetPrivateDataInterface proc :REFGUID, :ptr
    GetPrivateData	proc :REFGUID, :ptr, :ptr
    _GetParent		proc :REFIID, :ptr
    GetDevice		proc :REFIID, :ptr
    GetSharedHandle	proc :ptr
    GetUsage		proc :ptr
    SetEvictionPriority proc :UINT
    GetEvictionPriority proc :ptr
    .ends
endif

ifndef __IDXGIKeyedMutex_INTERFACE_DEFINED__
__IDXGIKeyedMutex_INTERFACE_DEFINED__ equ 1

.comdef IDXGIKeyedMutex

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetPrivateData	proc :REFGUID, :UINT, :ptr
    SetPrivateDataInterface proc :REFGUID, :ptr
    GetPrivateData	proc :REFGUID, :ptr, :ptr
    _GetParent		proc :REFIID, :ptr
    GetDevice		proc :REFIID, :ptr
    AcquireSync		proc :UINT64, :DWORD
    ReleaseSync		proc :UINT64
    .ends
endif

DXGI_MAP_READ		equ 1
DXGI_MAP_WRITE		equ 2
DXGI_MAP_DISCARD	equ 4

ifndef __IDXGISurface_INTERFACE_DEFINED__
__IDXGISurface_INTERFACE_DEFINED__ equ 1

.comdef IDXGISurface

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetPrivateData	proc :REFGUID, :UINT, :ptr
    SetPrivateDataInterface proc :REFGUID, :ptr
    GetPrivateData	proc :REFGUID, :ptr, :ptr
    _GetParent		proc :REFIID, :ptr
    GetDevice		proc :REFIID, :ptr
    GetDesc		proc :ptr
    Map			proc :ptr, :UINT
    Unmap		proc
    .ends
endif

ifndef __IDXGISurface1_INTERFACE_DEFINED__
__IDXGISurface1_INTERFACE_DEFINED__ equ 1

.comdef IDXGISurface1

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetPrivateData	proc :REFGUID, :UINT, :ptr
    SetPrivateDataInterface proc :REFGUID, :ptr
    GetPrivateData	proc :REFGUID, :ptr, :ptr
    _GetParent		proc :REFIID, :ptr
    GetDevice		proc :REFIID, :ptr
    GetDesc		proc :ptr
    Map			proc :ptr, :UINT
    Unmap		proc
    GetDC		proc :BOOL, :ptr
    ReleaseDC		proc :ptr
    .ends
endif

ifndef __IDXGIAdapter_INTERFACE_DEFINED__
__IDXGIAdapter_INTERFACE_DEFINED__ equ 1

.comdef IDXGIAdapter

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetPrivateData	proc :REFGUID, :UINT, :ptr
    SetPrivateDataInterface proc :REFGUID, :ptr
    GetPrivateData	proc :REFGUID, :ptr, :ptr
    _GetParent		proc :REFIID, :ptr
    EnumOutputs		proc :UINT, :ptr
    GetDesc		proc :ptr
    CheckInterfaceSupport proc :REFGUID, :ptr
    .ends

LPIDXGIAdapter		typedef ptr IDXGIAdapter
endif

DXGI_ENUM_MODES_INTERLACED equ 1
DXGI_ENUM_MODES_SCALING equ 2

ifndef __IDXGIOutput_INTERFACE_DEFINED__
__IDXGIOutput_INTERFACE_DEFINED__ equ 1

.comdef IDXGIOutput

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetPrivateData	proc :REFGUID, :UINT, :ptr
    SetPrivateDataInterface proc :REFGUID, :ptr
    GetPrivateData	proc :REFGUID, :ptr, :ptr
    _GetParent		proc :REFIID, :ptr
    GetDesc		proc :ptr
    GetDisplayModeList	proc :DXGI_FORMAT, :UINT, :ptr, :ptr
    FindClosestMatchingMode proc :ptr, :ptr, :ptr
    WaitForVBlank	proc
    TakeOwnership	proc :ptr, :BOOL
    ReleaseOwnership	proc
    GetGammaControlCapabilities proc :ptr
    SetGammaControl	proc :ptr
    GetGammaControl	proc :ptr
    SetDisplaySurface	proc :ptr
    GetDisplaySurfaceData proc :ptr
    GetFrameStatistics	proc :ptr
    .ends
endif

DXGI_MAX_SWAP_CHAIN_BUFFERS equ ( 16 )
DXGI_PRESENT_TEST	equ 0x00000001UL
DXGI_PRESENT_DO_NOT_SEQUENCE equ 0x00000002UL
DXGI_PRESENT_RESTART	equ 0x00000004UL

ifndef __IDXGISwapChain_INTERFACE_DEFINED__
__IDXGISwapChain_INTERFACE_DEFINED__ equ 1

.comdef IDXGISwapChain

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetPrivateData	proc :REFGUID, :UINT, :ptr
    SetPrivateDataInterface proc :REFGUID, :ptr
    GetPrivateData	proc :REFGUID, :ptr, :ptr
    _GetParent		proc :REFIID, :ptr
    GetDevice		proc :REFIID, :ptr
    Present		proc :UINT, :UINT
    GetBuffer		proc :UINT, :REFIID, :ptr
    SetFullscreenState	proc :BOOL, :ptr
    GetFullscreenState	proc :ptr, :ptr
    GetDesc		proc :ptr
    ResizeBuffers	proc :UINT, :UINT, :UINT, :DXGI_FORMAT, :UINT
    ResizeTarget	proc :ptr
    GetContainingOutput proc :ptr
    GetFrameStatistics	proc :ptr
    GetLastPresentCount proc :ptr
    .ends

LPIDXGISwapChain	typedef ptr IDXGISwapChain
endif

DXGI_MWA_NO_WINDOW_CHANGES equ ( 1 SHL 0 )
DXGI_MWA_NO_ALT_ENTER	equ ( 1 SHL 1 )
DXGI_MWA_NO_PRINT_SCREEN equ ( 1 SHL 2 )
DXGI_MWA_VALID		equ ( 0x7 )

ifndef __IDXGIFactory_INTERFACE_DEFINED__
__IDXGIFactory_INTERFACE_DEFINED__ equ 1

.comdef IDXGIFactory

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetPrivateData	proc :REFGUID, :UINT, :ptr
    SetPrivateDataInterface proc :REFGUID, :ptr
    GetPrivateData	proc :REFGUID, :ptr, :ptr
    _GetParent		proc :REFIID, :ptr
    EnumAdapters	proc :UINT, :ptr
    MakeWindowAssociation proc :HWND, :UINT
    GetWindowAssociation proc :ptr
    CreateSwapChain	proc :ptr, :ptr, :ptr
    CreateSoftwareAdapter proc :HMODULE, :ptr
    .ends
endif

;HRESULT
CreateDXGIFactory proto WINAPI \
		  riid: REFIID,
	     ppFactory: PVOID

;HRESULT
CreateDXGIFactory1 proto WINAPI \
		  riid: REFIID,
	     ppFactory: PVOID

ifndef __IDXGIDevice_INTERFACE_DEFINED__
__IDXGIDevice_INTERFACE_DEFINED__ equ 1

.comdef IDXGIDevice

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetPrivateData	proc :REFGUID, :UINT, :ptr
    SetPrivateDataInterface proc :REFGUID, :ptr
    GetPrivateData	proc :REFGUID, :ptr, :ptr
    _GetParent		proc :REFIID, :ptr
    GetAdapter		proc :ptr
    CreateSurface	proc :ptr, :UINT, :DXGI_USAGE, :ptr, :ptr
    QueryResourceResidency proc :ptr, :ptr, :UINT
    SetGPUThreadPriority proc :SINT
    GetGPUThreadPriority proc :ptr
    .ends

LPIDXGIDevice		typedef ptr IDXGIDevice
endif

DXGI_ADAPTER_FLAG	typedef SDWORD
DXGI_ADAPTER_FLAG_NONE	equ 0
DXGI_ADAPTER_FLAG_REMOTE equ 1
DXGI_ADAPTER_FLAG_FORCE_DWORD equ 0xffffffff

DXGI_ADAPTER_DESC1	STRUC
Description		WCHAR  128  dup(?)
VendorId		UINT ?
DeviceId		UINT ?
SubSysId		UINT ?
Revision		UINT ?
DedicatedVideoMemory	SIZE_T ?
DedicatedSystemMemory	SIZE_T ?
SharedSystemMemory	SIZE_T ?
AdapterLuid		LUID <>
Flags			UINT ?
DXGI_ADAPTER_DESC1	ENDS

DXGI_DISPLAY_COLOR_SPACE STRUC
PrimaryCoordinates	FLOAT  8  dup(?)
WhitePoints		FLOAT  16  dup(?)
DXGI_DISPLAY_COLOR_SPACE ENDS

ifndef __IDXGIFactory1_INTERFACE_DEFINED__
__IDXGIFactory1_INTERFACE_DEFINED__ equ 1

.comdef IDXGIFactory1

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetPrivateData	proc :REFGUID, :UINT, :ptr
    SetPrivateDataInterface proc :REFGUID, :ptr
    GetPrivateData	proc :REFGUID, :ptr, :ptr
    _GetParent		proc :REFIID, :ptr
    EnumAdapters	proc :UINT, :ptr
    MakeWindowAssociation proc :HWND, :UINT
    GetWindowAssociation proc :ptr
    CreateSwapChain	proc :ptr, :ptr, :ptr
    CreateSoftwareAdapter proc :HMODULE, :ptr
    EnumAdapters1	proc :UINT, :ptr
    IsCurrent		proc
    .ends

LPIDXGIFactory1		typedef ptr IDXGIFactory1
endif

ifndef __IDXGIAdapter1_INTERFACE_DEFINED__
__IDXGIAdapter1_INTERFACE_DEFINED__ equ 1

.comdef IDXGIAdapter1

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetPrivateData	proc :REFGUID, :UINT, :ptr
    SetPrivateDataInterface proc :REFGUID, :ptr
    GetPrivateData	proc :REFGUID, :ptr, :ptr
    _GetParent		proc :REFIID, :ptr
    EnumOutputs		proc :UINT, :ptr
    GetDesc		proc :ptr
    CheckInterfaceSupport proc :REFGUID, :ptr
    GetDesc1		proc :ptr
    .ends
endif

ifndef __IDXGIDevice1_INTERFACE_DEFINED__
__IDXGIDevice1_INTERFACE_DEFINED__ equ 1

.comdef IDXGIDevice1

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetPrivateData	proc :REFGUID, :UINT, :ptr
    SetPrivateDataInterface proc :REFGUID, :ptr
    GetPrivateData	proc :REFGUID, :ptr, :ptr
    _GetParent		proc :REFIID, :ptr
    GetAdapter		proc :ptr
    CreateSurface	proc :ptr, :UINT, :DXGI_USAGE, :ptr, :ptr
    QueryResourceResidency proc :ptr, :ptr, :UINT
    SetGPUThreadPriority proc :SINT
    GetGPUThreadPriority proc :ptr
    SetMaximumFrameLatency proc :UINT
    GetMaximumFrameLatency proc :ptr
    .ends
endif

DEFINE_GUID(IID_IDXGIObject,		0xaec22fb8,0x76f3,0x4639,0x9b,0xe0,0x28,0xeb,0x43,0xa6,0x7a,0x2e)
DEFINE_GUID(IID_IDXGIDeviceSubObject,	0x3d3e0379,0xf9de,0x4d58,0xbb,0x6c,0x18,0xd6,0x29,0x92,0xf1,0xa6)
DEFINE_GUID(IID_IDXGIResource,		0x035f3ab4,0x482e,0x4e50,0xb4,0x1f,0x8a,0x7f,0x8b,0xd8,0x96,0x0b)
DEFINE_GUID(IID_IDXGIKeyedMutex,	0x9d8e1289,0xd7b3,0x465f,0x81,0x26,0x25,0x0e,0x34,0x9a,0xf8,0x5d)
DEFINE_GUID(IID_IDXGISurface,		0xcafcb56c,0x6ac3,0x4889,0xbf,0x47,0x9e,0x23,0xbb,0xd2,0x60,0xec)
DEFINE_GUID(IID_IDXGISurface1,		0x4AE63092,0x6327,0x4c1b,0x80,0xAE,0xBF,0xE1,0x2E,0xA3,0x2B,0x86)
DEFINE_GUID(IID_IDXGIAdapter,		0x2411e7e1,0x12ac,0x4ccf,0xbd,0x14,0x97,0x98,0xe8,0x53,0x4d,0xc0)
DEFINE_GUID(IID_IDXGIOutput,		0xae02eedb,0xc735,0x4690,0x8d,0x52,0x5a,0x8d,0xc2,0x02,0x13,0xaa)
DEFINE_GUID(IID_IDXGISwapChain,		0x310d36a0,0xd2e7,0x4c0a,0xaa,0x04,0x6a,0x9d,0x23,0xb8,0x88,0x6a)
DEFINE_GUID(IID_IDXGIFactory,		0x7b7166ec,0x21c7,0x44ae,0xb2,0x1a,0xc9,0xae,0x32,0x1a,0xe3,0x69)
DEFINE_GUID(IID_IDXGIDevice,		0x54ec77fa,0x1377,0x44e6,0x8c,0x32,0x88,0xfd,0x5f,0x44,0xc8,0x4c)
DEFINE_GUID(IID_IDXGIFactory1,		0x770aae78,0xf26f,0x4dba,0xa8,0x29,0x25,0x3c,0x83,0xd1,0xb3,0x87)
DEFINE_GUID(IID_IDXGIAdapter1,		0x29038f61,0x3839,0x4626,0x91,0xfd,0x08,0x68,0x79,0x01,0x1a,0x05)
DEFINE_GUID(IID_IDXGIDevice1,		0x77db970f,0x6276,0x48ba,0xba,0x28,0x07,0x01,0x43,0xb4,0x39,0x2c)

endif
.pragma list(pop)
