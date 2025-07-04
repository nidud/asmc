.pragma list(push, 0)

ifndef __REQUIRED_RPCNDR_H_VERSION__
define __REQUIRED_RPCNDR_H_VERSION__ 475
endif

include rpc.inc
include rpcndr.inc
ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif

ifndef __dxgi1_2_h__
define __dxgi1_2_h__

include dxgi.inc

ifndef __IDXGIDisplayControl_INTERFACE_DEFINED__
define __IDXGIDisplayControl_INTERFACE_DEFINED__

DEFINE_IIDX(IDXGIDisplayControl, "ea9dbf1a-c88e-4486-854a-98aa0138f30c")

.comdef IDXGIDisplayControl : public IUnknown

    IsStereoEnabled	proc
    SetStereoEnabled	proc :BOOL
   .ends

endif

DXGI_OUTDUPL_MOVE_RECT	STRUC
SourcePoint		POINT <>
DestinationRect		RECT <>
DXGI_OUTDUPL_MOVE_RECT	ENDS

DXGI_OUTDUPL_DESC	STRUC
ModeDesc		DXGI_MODE_DESC <>
Rotation		DXGI_MODE_ROTATION ?
DesktopImageInSystemMemory BOOL ?
DXGI_OUTDUPL_DESC	ENDS

DXGI_OUTDUPL_POINTER_POSITION STRUC
Position		POINT <>
Visible			BOOL ?
DXGI_OUTDUPL_POINTER_POSITION ENDS

.enum DXGI_OUTDUPL_POINTER_SHAPE_TYPE {
    DXGI_OUTDUPL_POINTER_SHAPE_TYPE_MONOCHROME	= 0x1,
    DXGI_OUTDUPL_POINTER_SHAPE_TYPE_COLOR	= 0x2,
    DXGI_OUTDUPL_POINTER_SHAPE_TYPE_MASKED_COLOR = 0x4
    }

DXGI_OUTDUPL_POINTER_SHAPE_INFO STRUC
Type			UINT ?
Width			UINT ?
Height			UINT ?
Pitch			UINT ?
HotSpot			POINT <>
DXGI_OUTDUPL_POINTER_SHAPE_INFO ENDS

DXGI_OUTDUPL_FRAME_INFO STRUC
LastPresentTime		LARGE_INTEGER <>
LastMouseUpdateTime	LARGE_INTEGER <>
AccumulatedFrames	UINT ?
RectsCoalesced		BOOL ?
ProtectedContentMaskedOut BOOL ?
PointerPosition		DXGI_OUTDUPL_POINTER_POSITION <>
TotalMetadataBufferSize UINT ?
PointerShapeBufferSize	UINT ?
DXGI_OUTDUPL_FRAME_INFO ENDS

ifndef __IDXGIOutputDuplication_INTERFACE_DEFINED__
define __IDXGIOutputDuplication_INTERFACE_DEFINED__

DEFINE_IIDX(IDXGIOutputDuplication, "191cfac3-a341-470d-b26e-a864f428319c")

.comdef IDXGIOutputDuplication : public IDXGIObject

    GetDesc		proc :ptr
    AcquireNextFrame	proc :UINT, :ptr, :ptr
    GetFrameDirtyRects	proc :UINT, :ptr, :ptr
    GetFrameMoveRects	proc :UINT, :ptr, :ptr
    GetFramePointerShape proc :UINT, :ptr, :ptr, :ptr
    MapDesktopSurface	proc :ptr
    UnMapDesktopSurface proc
    ReleaseFrame	proc
   .ends

endif

.enum DXGI_OFFER_RESOURCE_PRIORITY {
    DXGI_OFFER_RESOURCE_PRIORITY_LOW = 1,
    DXGI_OFFER_RESOURCE_PRIORITY_NORMAL = 2,
    DXGI_OFFER_RESOURCE_PRIORITY_HIGH = 3
}

.enum DXGI_ALPHA_MODE {
    DXGI_ALPHA_MODE_UNSPECIFIED = 0,
    DXGI_ALPHA_MODE_PREMULTIPLIED = 1,
    DXGI_ALPHA_MODE_STRAIGHT = 2,
    DXGI_ALPHA_MODE_IGNORE = 3,
    DXGI_ALPHA_MODE_FORCE_DWORD = 0xffffffff
}


ifndef __IDXGISurface2_INTERFACE_DEFINED__
define __IDXGISurface2_INTERFACE_DEFINED__

DEFINE_IIDX(IDXGISurface2, "aba496dd-b617-4cb8-a866-bc44d7eb1fa2")

.comdef IDXGISurface2 : public IDXGISurface1

    GetResource		proc :REFIID, :ptr, :ptr
   .ends

endif

ifndef __IDXGIResource1_INTERFACE_DEFINED__
define __IDXGIResource1_INTERFACE_DEFINED__

DEFINE_IIDX(IDXGIResource1, "30961379-4609-4a41-998e-54fe567ee0c1")

.comdef IDXGIResource1 : public IDXGIResource

    CreateSubresourceSurface proc :UINT, :ptr
    CreateSharedHandle	proc :ptr, :DWORD, :LPCWSTR, :ptr
   .ends

endif

ifndef __IDXGIDevice2_INTERFACE_DEFINED__
define __IDXGIDevice2_INTERFACE_DEFINED__

DEFINE_GUID(IID_IDXGIDevice2, 0x05008617,0xfbfd,0x4051,0xa7,0x90,0x14,0x48,0x84,0xb4,0xf6,0xa9)

.comdef IDXGIDevice2 : public IDXGIDevice1

    OfferResources	proc :UINT, :ptr, :DXGI_OFFER_RESOURCE_PRIORITY
    ReclaimResources	proc :UINT, :ptr, :ptr
    EnqueueSetEvent	proc :HANDLE
   .ends

endif

DXGI_MODE_DESC1		STRUC
Width			UINT ?
Height			UINT ?
RefreshRate		DXGI_RATIONAL <>
Format			DXGI_FORMAT ?
ScanlineOrdering	DXGI_MODE_SCANLINE_ORDER ?
Scaling			DXGI_MODE_SCALING ?
Stereo			BOOL ?
DXGI_MODE_DESC1		ENDS

.enum DXGI_SCALING {
    DXGI_SCALING_STRETCH = 0,
    DXGI_SCALING_NONE = 1
    }

DXGI_SWAP_CHAIN_DESC1	STRUC
Width			UINT ?
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

DXGI_SWAP_CHAIN_FULLSCREEN_DESC STRUC
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
define __IDXGISwapChain1_INTERFACE_DEFINED__

DEFINE_GUID(IID_IDXGISwapChain1, 0x790a45f7, 0x0d42, 0x4876, 0x98,0x3a, 0x0a,0x55,0xcf,0xe6,0xf4,0xaa)

.comdef IDXGISwapChain1 : public IDXGISwapChain

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
define __IDXGIFactory2_INTERFACE_DEFINED__

DEFINE_GUID(IID_IDXGIFactory2, 0x50c83a1c, 0xe072, 0x4c48, 0x87,0xb0, 0x36,0x30,0xfa,0x36,0xa6,0xd0)

.comdef IDXGIFactory2 : public IDXGIFactory1

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
    LPIDXGIFactory2 typedef ptr IDXGIFactory2
endif

.enum DXGI_GRAPHICS_PREEMPTION_GRANULARITY {
    DXGI_GRAPHICS_PREEMPTION_DMA_BUFFER_BOUNDARY = 0,
    DXGI_GRAPHICS_PREEMPTION_PRIMITIVE_BOUNDARY = 1,
    DXGI_GRAPHICS_PREEMPTION_TRIANGLE_BOUNDARY = 2,
    DXGI_GRAPHICS_PREEMPTION_PIXEL_BOUNDARY = 3,
    DXGI_GRAPHICS_PREEMPTION_INSTRUCTION_BOUNDARY = 4
    }

.enum DXGI_COMPUTE_PREEMPTION_GRANULARITY {
    DXGI_COMPUTE_PREEMPTION_DMA_BUFFER_BOUNDARY = 0,
    DXGI_COMPUTE_PREEMPTION_DISPATCH_BOUNDARY = 1,
    DXGI_COMPUTE_PREEMPTION_THREAD_GROUP_BOUNDARY = 2,
    DXGI_COMPUTE_PREEMPTION_THREAD_BOUNDARY = 3,
    DXGI_COMPUTE_PREEMPTION_INSTRUCTION_BOUNDARY = 4
    }

DXGI_ADAPTER_DESC2	STRUC
Description		WCHAR 128 dup(?)
VendorId		UINT ?
DeviceId		UINT ?
SubSysId		UINT ?
Revision		UINT ?
DedicatedVideoMemory	size_t ?
DedicatedSystemMemory	size_t ?
SharedSystemMemory	size_t ?
AdapterLuid		LUID <>
Flags			UINT ?
GraphicsPreemptionGranularity DXGI_GRAPHICS_PREEMPTION_GRANULARITY ?
ComputePreemptionGranularity DXGI_COMPUTE_PREEMPTION_GRANULARITY ?
DXGI_ADAPTER_DESC2	ENDS

ifndef __IDXGIAdapter2_INTERFACE_DEFINED__
define __IDXGIAdapter2_INTERFACE_DEFINED__

DEFINE_GUID(IID_IDXGIAdapter2, 0x0aa1ae0a, 0xfa0e, 0x4b84, 0x86,0x44, 0xe0,0x5f,0xf8,0xe5,0xac,0xb5)

.comdef IDXGIAdapter2 : public IDXGIAdapter1

    GetDesc2		proc :ptr
   .ends

endif

ifndef __IDXGIOutput1_INTERFACE_DEFINED__
define __IDXGIOutput1_INTERFACE_DEFINED__

DEFINE_IIDX(IDXGIOutput1, "00cddea8-939b-4b83-a340-a685226666cc")

.comdef IDXGIOutput1 : public IDXGIOutput

    GetDisplayModeList1 proc :DXGI_FORMAT, :UINT, :ptr, :ptr
    FindClosestMatchingMode1 proc :ptr, :ptr, :ptr
    GetDisplaySurfaceData1 proc :ptr
    DuplicateOutput	proc :ptr, :ptr
   .ends

endif

endif

.pragma list(pop)
