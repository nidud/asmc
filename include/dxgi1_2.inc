.pragma list(push, 0)
ifndef __REQUIRED_RPCNDR_H_VERSION__
__REQUIRED_RPCNDR_H_VERSION__ equ 475
endif
include rpc.inc
include rpcndr.inc
ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif
ifndef __dxgi1_2_h__
__dxgi1_2_h__ equ <>

ifndef __IDXGIDevice2_FWD_DEFINED__
__IDXGIDevice2_FWD_DEFINED__ equ 1
endif
ifndef __IDXGISwapChain1_FWD_DEFINED__
__IDXGISwapChain1_FWD_DEFINED__ equ 1
endif
ifndef __IDXGIFactory2_FWD_DEFINED__
__IDXGIFactory2_FWD_DEFINED__ equ 1
endif
ifndef __IDXGIAdapter2_FWD_DEFINED__
__IDXGIAdapter2_FWD_DEFINED__ equ 1
endif
include dxgi.inc

DXGI_OFFER_RESOURCE_PRIORITY typedef SDWORD
DXGI_OFFER_RESOURCE_PRIORITY_LOW equ 1
DXGI_OFFER_RESOURCE_PRIORITY_NORMAL equ 2
DXGI_OFFER_RESOURCE_PRIORITY_HIGH equ 3
DXGI_ALPHA_MODE		typedef SDWORD
DXGI_ALPHA_MODE_UNSPECIFIED equ 0
DXGI_ALPHA_MODE_PREMULTIPLIED equ 1
DXGI_ALPHA_MODE_STRAIGHT equ 2
DXGI_ALPHA_MODE_IGNORE	equ 3
DXGI_ALPHA_MODE_FORCE_DWORD equ 0xffffffff

ifndef __IDXGIDevice2_INTERFACE_DEFINED__
__IDXGIDevice2_INTERFACE_DEFINED__ equ 1

DEFINE_GUID(IID_IDXGIDevice2, 0x05008617, 0xfbfd, 0x4051, 0xa7,0x90, 0x14,0x48,0x84,0xb4,0xf6,0xa9);
.comdef IDXGIDevice2

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetPrivateData	proc :REFGUID, :UINT, :ptr
    SetPrivateDataInterface proc :REFGUID, :ptr
    GetPrivateData	proc :REFGUID, :ptr, :ptr
    GetParent		proc :REFIID, :ptr
    GetAdapter		proc :ptr
    CreateSurface	proc :ptr, :UINT, :DXGI_USAGE, :ptr, :ptr
    QueryResourceResidency proc :ptr, :ptr, :UINT
    SetGPUThreadPriority proc :SINT
    GetGPUThreadPriority proc :ptr
    SetMaximumFrameLatency proc :UINT
    GetMaximumFrameLatency proc :ptr
    OfferResources	proc :UINT, :ptr, :DXGI_OFFER_RESOURCE_PRIORITY
    ReclaimResources	proc :UINT, :ptr, :ptr
    EnqueueSetEvent	proc :HANDLE
    .ends

endif

DXGI_SCALING		typedef SDWORD
DXGI_SCALING_STRETCH	equ 0
DXGI_SCALING_NONE	equ 1

DXGI_SWAP_CHAIN_DESC1	STRUC
_Width			UINT ?
Height			UINT ?
Format			DXGI_FORMAT ?
Stereo			BOOL ?
SampleDesc		DXGI_SAMPLE_DESC <>
BufferUsage		DXGI_USAGE ?
BufferCount		UINT ?
Scaling			DXGI_SCALING ?
SwapEffect		DXGI_SWAP_EFFECT ?
AlphaMode		DXGI_ALPHA_MODE ?
Flags			UINT ?
DXGI_SWAP_CHAIN_DESC1	ENDS
DXGI_SWAP_CHAIN_FULLSCREEN_DESC	 STRUC
RefreshRate		DXGI_RATIONAL <>
ScanlineOrdering	DXGI_MODE_SCANLINE_ORDER ?
Scaling			DXGI_MODE_SCALING ?
Windowed		BOOL ?
DXGI_SWAP_CHAIN_FULLSCREEN_DESC ENDS

DXGI_PRESENT_PARAMETERS	 STRUC
DirtyRectsCount		UINT ?
pDirtyRects		LPRECT ?
pScrollRect		LPRECT ?
pScrollOffset		LPPOINT ?
DXGI_PRESENT_PARAMETERS ENDS

ifndef __IDXGISwapChain1_INTERFACE_DEFINED__
__IDXGISwapChain1_INTERFACE_DEFINED__ equ 1

DEFINE_GUID(IID_IDXGISwapChain1, 0x790a45f7, 0x0d42, 0x4876, 0x98,0x3a, 0x0a,0x55,0xcf,0xe6,0xf4,0xaa);
.comdef IDXGISwapChain1

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetPrivateData	proc :REFGUID, :UINT, :ptr
    SetPrivateDataInterface proc :REFGUID, :ptr
    GetPrivateData	proc :REFGUID, :ptr, :ptr
    GetParent		proc :REFIID, :ptr
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
    GetDesc1		proc :ptr
    GetFullscreenDesc	proc :ptr
    GetHwnd		proc :ptr
    GetCoreWindow	proc :REFIID, :ptr
    Present1		proc :UINT, :UINT, :ptr
    IsTemporaryMonoSupported proc
    GetRestrictToOutput proc :ptr
    SetBackgroundColor	proc :ptr
    GetBackgroundColor	proc :ptr
    SetRotation		proc :DXGI_MODE_ROTATION
    GetRotation		proc :ptr
    .ends

LPIDXGISwapChain1	typedef ptr IDXGISwapChain1
endif

ifndef __IDXGIFactory2_INTERFACE_DEFINED__
__IDXGIFactory2_INTERFACE_DEFINED__ equ 1

DEFINE_GUID(IID_IDXGIFactory2, 0x50c83a1c, 0xe072, 0x4c48, 0x87,0xb0, 0x36,0x30,0xfa,0x36,0xa6,0xd0);
.comdef IDXGIFactory2

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetPrivateData	proc :REFGUID, :UINT, :ptr
    SetPrivateDataInterface proc :REFGUID, :ptr
    GetPrivateData	proc :REFGUID, :ptr, :ptr
    GetParent		proc :REFIID, :ptr
    EnumAdapters	proc :UINT, :ptr
    MakeWindowAssociation proc :HWND, :UINT
    GetWindowAssociation proc :ptr
    CreateSwapChain	proc :ptr, :ptr, :ptr
    CreateSoftwareAdapter proc :HMODULE, :ptr
    EnumAdapters1	proc :UINT, :ptr
    IsCurrent		proc
    IsWindowedStereoEnabled proc
    CreateSwapChainForHwnd proc :ptr, :HWND, :ptr, :ptr, :ptr, :ptr
    CreateSwapChainForCoreWindow proc :ptr, :ptr, :ptr, :ptr, :ptr
    GetSharedResourceAdapterLuid proc :HANDLE, :ptr
    RegisterOcclusionStatusWindow proc :HWND, :UINT, :ptr
    RegisterStereoStatusEvent proc :HANDLE, :ptr
    UnregisterStereoStatus proc :DWORD
    RegisterStereoStatusWindow proc :HWND, :UINT, :ptr
    RegisterOcclusionStatusEvent proc :HANDLE, :ptr
    UnregisterOcclusionStatus proc :DWORD
    CreateSwapChainForComposition proc :ptr, :ptr, :ptr, :ptr
    .ends

endif

DXGI_GRAPHICS_PREEMPTION_GRANULARITY typedef SDWORD
DXGI_GRAPHICS_PREEMPTION_DMA_BUFFER_BOUNDARY equ 0
DXGI_GRAPHICS_PREEMPTION_PRIMITIVE_BOUNDARY equ 1
DXGI_GRAPHICS_PREEMPTION_TRIANGLE_BOUNDARY equ 2
DXGI_GRAPHICS_PREEMPTION_PIXEL_BOUNDARY equ 3
DXGI_GRAPHICS_PREEMPTION_INSTRUCTION_BOUNDARY equ 4
DXGI_COMPUTE_PREEMPTION_GRANULARITY typedef SDWORD
DXGI_COMPUTE_PREEMPTION_DMA_BUFFER_BOUNDARY equ 0
DXGI_COMPUTE_PREEMPTION_DISPATCH_BOUNDARY equ 1
DXGI_COMPUTE_PREEMPTION_THREAD_GROUP_BOUNDARY equ 2
DXGI_COMPUTE_PREEMPTION_THREAD_BOUNDARY equ 3
DXGI_COMPUTE_PREEMPTION_INSTRUCTION_BOUNDARY equ 4

DXGI_ADAPTER_DESC2	STRUC
Description		WCHAR 128 dup(?)
VendorId		UINT ?
DeviceId		UINT ?
SubSysId		UINT ?
Revision		UINT ?
DedicatedVideoMemory	SIZE_T ?
DedicatedSystemMemory	SIZE_T ?
SharedSystemMemory	SIZE_T ?
AdapterLuid		LUID <>
Flags			UINT ?
GraphicsPreemptionGranularity DXGI_GRAPHICS_PREEMPTION_GRANULARITY ?
ComputePreemptionGranularity DXGI_COMPUTE_PREEMPTION_GRANULARITY ?
DXGI_ADAPTER_DESC2	ENDS

ifndef __IDXGIAdapter2_INTERFACE_DEFINED__
__IDXGIAdapter2_INTERFACE_DEFINED__ equ 1

DEFINE_GUID(IID_IDXGIAdapter2, 0x0aa1ae0a, 0xfa0e, 0x4b84, 0x86,0x44, 0xe0,0x5f,0xf8,0xe5,0xac,0xb5);
.comdef IDXGIAdapter2

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetPrivateData	proc :REFGUID, :UINT, :ptr
    SetPrivateDataInterface proc :REFGUID, :ptr
    GetPrivateData	proc :REFGUID, :ptr, :ptr
    GetParent		proc :REFIID, :ptr
    EnumOutputs		proc :UINT, :ptr
    GetDesc		proc :ptr
    CheckInterfaceSupport proc :REFGUID, :ptr
    GetDesc1		proc :ptr
    GetDesc2		proc :ptr
    .ends

endif
endif
.pragma list(pop)
