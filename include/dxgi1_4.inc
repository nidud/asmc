ifndef __REQUIRED_RPCNDR_H_VERSION__
__REQUIRED_RPCNDR_H_VERSION__ equ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
__REQUIRED_RPCSAL_H_VERSION__ equ 100
endif

include rpc.inc
include rpcndr.inc

ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr.h>
endif

ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif

ifndef __dxgi1_4_h__
__dxgi1_4_h__ equ <>

ifndef __IDXGISwapChain3_FWD_DEFINED__
__IDXGISwapChain3_FWD_DEFINED__ equ 1
endif
ifndef __IDXGIOutput4_FWD_DEFINED__
__IDXGIOutput4_FWD_DEFINED__ equ 1
endif
ifndef __IDXGIFactory4_FWD_DEFINED__
__IDXGIFactory4_FWD_DEFINED__ equ 1
endif
ifndef __IDXGIAdapter3_FWD_DEFINED__
__IDXGIAdapter3_FWD_DEFINED__ equ 1
endif

include dxgi1_3.inc

.enum DXGI_SWAP_CHAIN_COLOR_SPACE_SUPPORT_FLAG {
    DXGI_SWAP_CHAIN_COLOR_SPACE_SUPPORT_FLAG_PRESENT	= 0x1,
    DXGI_SWAP_CHAIN_COLOR_SPACE_SUPPORT_FLAG_OVERLAY_PRESENT	= 0x2
    }

ifndef __IDXGISwapChain3_INTERFACE_DEFINED__
__IDXGISwapChain3_INTERFACE_DEFINED__ equ 1

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
__IDXGIOutput4_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDXGIOutput4, "dc7dca35-2196-414d-9F53-617884032a60")

.comdef IDXGIOutput4 : public IDXGIOutput3

    CheckOverlayColorSpaceSupport proc :DXGI_FORMAT, :DXGI_COLOR_SPACE_TYPE, :ptr, :ptr

    .ends

endif

ifndef __IDXGIFactory4_INTERFACE_DEFINED__
__IDXGIFactory4_INTERFACE_DEFINED__ equ 1

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
__IDXGIAdapter3_INTERFACE_DEFINED__ equ 1

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
