ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __dxgi1_4_h__
define __dxgi1_4_h__

include dxgi1_3.inc

.enum DXGI_SWAP_CHAIN_COLOR_SPACE_SUPPORT_FLAG {
    DXGI_SWAP_CHAIN_COLOR_SPACE_SUPPORT_FLAG_PRESENT	= 0x1,
    DXGI_SWAP_CHAIN_COLOR_SPACE_SUPPORT_FLAG_OVERLAY_PRESENT	= 0x2
    }

ifndef __IDXGISwapChain3_INTERFACE_DEFINED__
define __IDXGISwapChain3_INTERFACE_DEFINED__

DEFINE_IIDX(IDXGISwapChain3, "94d99bdb-f1f8-4ab0-b236-7da0170edab1")

.comdef IDXGISwapChain3 : public IDXGISwapChain2

    GetCurrentBackBufferIndex proc
    CheckColorSpaceSupport proc :DXGI_COLOR_SPACE_TYPE, :ptr
    SetColorSpace1	proc :DXGI_COLOR_SPACE_TYPE
    ResizeBuffers1	proc :UINT, :UINT, :UINT, :DXGI_FORMAT, :UINT, :ptr
   .ends

endif

.enum DXGI_OVERLAY_COLOR_SPACE_SUPPORT_FLAG {
    DXGI_OVERLAY_COLOR_SPACE_SUPPORT_FLAG_PRESENT	= 0x1
    }

ifndef __IDXGIOutput4_INTERFACE_DEFINED__
define __IDXGIOutput4_INTERFACE_DEFINED__

DEFINE_IIDX(IDXGIOutput4, "dc7dca35-2196-414d-9F53-617884032a60")

.comdef IDXGIOutput4 : public IDXGIOutput3

    CheckOverlayColorSpaceSupport proc :DXGI_FORMAT, :DXGI_COLOR_SPACE_TYPE, :ptr, :ptr
   .ends

endif

ifndef __IDXGIFactory4_INTERFACE_DEFINED__
define __IDXGIFactory4_INTERFACE_DEFINED__

DEFINE_IIDX(IDXGIFactory4, "1bc6ea02-ef36-464f-bf0c-21ca39e5168a")

.comdef IDXGIFactory4 : public IDXGIFactory3

    EnumAdapterByLuid	proc :LUID, :REFIID, :ptr
    EnumWarpAdapter	proc :REFIID, :ptr
   .ends

endif

.enum DXGI_MEMORY_SEGMENT_GROUP {
    DXGI_MEMORY_SEGMENT_GROUP_LOCAL	= 0,
    DXGI_MEMORY_SEGMENT_GROUP_NON_LOCAL = 1
    }

DXGI_QUERY_VIDEO_MEMORY_INFO STRUC
Budget			UINT64 ?
CurrentUsage		UINT64 ?
AvailableForReservation UINT64 ?
CurrentReservation	UINT64 ?
DXGI_QUERY_VIDEO_MEMORY_INFO ENDS

ifndef __IDXGIAdapter3_INTERFACE_DEFINED__
define __IDXGIAdapter3_INTERFACE_DEFINED__

DEFINE_IIDX(IDXGIAdapter3, "645967A4-1392-4310-A798-8053CE3E93FD")

.comdef IDXGIAdapter3 : public IDXGIAdapter2

    RegisterHardwareContentProtectionTeardownStatusEvent proc :HANDLE, :ptr
    UnregisterHardwareContentProtectionTeardownStatus proc :DWORD
    QueryVideoMemoryInfo proc :UINT, :DXGI_MEMORY_SEGMENT_GROUP, :ptr
    SetVideoMemoryReservation proc :UINT, :DXGI_MEMORY_SEGMENT_GROUP, :UINT64
    RegisterVideoMemoryBudgetChangeNotificationEvent proc :HANDLE, :ptr
    UnregisterVideoMemoryBudgetChangeNotification proc :DWORD
   .ends

endif

endif
