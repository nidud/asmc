ifndef __REQUIRED_RPCNDR_H_VERSION__
define __REQUIRED_RPCNDR_H_VERSION__ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
define __REQUIRED_RPCSAL_H_VERSION__ 100
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

ifndef __dxgi1_3_h__
define __dxgi1_3_h__

include dxgi1_2.inc

DXGI_CREATE_FACTORY_DEBUG equ 0x1

CreateDXGIFactory2 proto WINAPI \
		 Flags: UINT,
		  riid: REFIID,
	     ppFactory: ptr

DXGIGetDebugInterface1 proto WINAPI \
		 Flags: UINT,
		  riid: REFIID,
		pDebug: ptr


ifndef __IDXGIDevice3_INTERFACE_DEFINED__
define __IDXGIDevice3_INTERFACE_DEFINED__

DEFINE_IIDX(IDXGIDevice3, "6007896c-3244-4afd-bf18-a6d3beda5023")

.comdef IDXGIDevice3 : public IDXGIDevice2

    Trim		proc
   .ends

endif

DXGI_MATRIX_3X2_F	STRUC
_11			real4 ?
_12			real4 ?
_21			real4 ?
_22			real4 ?
_31			real4 ?
_32			real4 ?
DXGI_MATRIX_3X2_F	ENDS

ifndef __IDXGISwapChain2_INTERFACE_DEFINED__
define __IDXGISwapChain2_INTERFACE_DEFINED__

DEFINE_IIDX(IDXGISwapChain2, "a8be2ac4-199f-4946-b331-79599fb98de7")

.comdef IDXGISwapChain2 : public IDXGISwapChain1

    SetSourceSize	proc :UINT, :UINT
    GetSourceSize	proc :ptr, :ptr
    SetMaximumFrameLatency proc :UINT
    GetMaximumFrameLatency proc :ptr
    GetFrameLatencyWaitableObject proc
    SetMatrixTransform	proc :ptr
    GetMatrixTransform	proc :ptr
   .ends

endif


ifndef __IDXGIOutput2_INTERFACE_DEFINED__
define __IDXGIOutput2_INTERFACE_DEFINED__

DEFINE_IIDX(IDXGIOutput2, "595e39d1-2724-4663-99b1-da969de28364")

.comdef IDXGIOutput2 : public IDXGIOutput1

    SupportsOverlays	proc
   .ends

endif

ifndef __IDXGIFactory3_INTERFACE_DEFINED__
define __IDXGIFactory3_INTERFACE_DEFINED__

DEFINE_IIDX(IDXGIFactory3, "25483823-cd46-4c7d-86ca-47aa95b837bd")

.comdef IDXGIFactory3 : public IDXGIFactory2

    GetCreationFlags	proc
   .ends

endif

DXGI_DECODE_SWAP_CHAIN_DESC STRUC
Flags			UINT ?
DXGI_DECODE_SWAP_CHAIN_DESC ENDS

.enum DXGI_MULTIPLANE_OVERLAY_YCbCr_FLAGS {
    DXGI_MULTIPLANE_OVERLAY_YCbCr_FLAG_NOMINAL_RANGE	= 0x1,
    DXGI_MULTIPLANE_OVERLAY_YCbCr_FLAG_BT709	= 0x2,
    DXGI_MULTIPLANE_OVERLAY_YCbCr_FLAG_xvYCC	= 0x4
    }

ifndef __IDXGIDecodeSwapChain_INTERFACE_DEFINED__
define __IDXGIDecodeSwapChain_INTERFACE_DEFINED__

DEFINE_IIDX(IDXGIDecodeSwapChain, "2633066b-4514-4c7a-8fd8-12ea98059d18")

.comdef IDXGIDecodeSwapChain : public IUnknown

    PresentBuffer	proc :UINT, :UINT, :UINT
    SetSourceRect	proc :ptr
    SetTargetRect	proc :ptr
    SetDestSize		proc :UINT, :UINT
    GetSourceRect	proc :ptr
    GetTargetRect	proc :ptr
    GetDestSize		proc :ptr, :ptr
    SetColorSpace	proc :DXGI_MULTIPLANE_OVERLAY_YCbCr_FLAGS
    GetColorSpace	proc
   .ends

endif

ifndef __IDXGIFactoryMedia_INTERFACE_DEFINED__
define __IDXGIFactoryMedia_INTERFACE_DEFINED__

DEFINE_IIDX(IDXGIFactoryMedia, "41e7d1f2-a591-4f7b-a2e5-fa9c843e1c12")

.comdef IDXGIFactoryMedia : public IUnknown

    CreateSwapChainForCompositionSurfaceHandle proc :ptr, :HANDLE, :ptr, :ptr, :ptr
    CreateDecodeSwapChainForCompositionSurfaceHandle proc :ptr, :HANDLE, :ptr, :ptr, :ptr, :ptr
   .ends

endif

.enum DXGI_FRAME_PRESENTATION_MODE {
    DXGI_FRAME_PRESENTATION_MODE_COMPOSED	= 0,
    DXGI_FRAME_PRESENTATION_MODE_OVERLAY	= 1,
    DXGI_FRAME_PRESENTATION_MODE_NONE	= 2,
    DXGI_FRAME_PRESENTATION_MODE_COMPOSITION_FAILURE	= 3
    }

DXGI_FRAME_STATISTICS_MEDIA STRUC
PresentCount		UINT ?
PresentRefreshCount	UINT ?
SyncRefreshCount	UINT ?
SyncQPCTime		LARGE_INTEGER <>
SyncGPUTime		LARGE_INTEGER <>
CompositionMode		DXGI_FRAME_PRESENTATION_MODE ?
ApprovedPresentDuration UINT ?
DXGI_FRAME_STATISTICS_MEDIA ENDS

ifndef __IDXGISwapChainMedia_INTERFACE_DEFINED__
define __IDXGISwapChainMedia_INTERFACE_DEFINED__

DEFINE_IIDX(IDXGISwapChainMedia, "dd95b90b-f05f-4f6a-bd65-25bfb264bd84")

.comdef IDXGISwapChainMedia : public IUnknown

    GetFrameStatisticsMedia proc :ptr
    SetPresentDuration	proc :UINT
    CheckPresentDurationSupport proc :UINT, :ptr, :ptr
   .ends

endif

.enum DXGI_OVERLAY_SUPPORT_FLAG {
    DXGI_OVERLAY_SUPPORT_FLAG_DIRECT	= 0x1,
    DXGI_OVERLAY_SUPPORT_FLAG_SCALING	= 0x2
    }

ifndef __IDXGIOutput3_INTERFACE_DEFINED__
define __IDXGIOutput3_INTERFACE_DEFINED__

DEFINE_IIDX(IDXGIOutput3, "8a6bb301-7e7e-41F4-a8e0-5b32f7f99b18")

.comdef IDXGIOutput3 : public IDXGIOutput2

    CheckOverlaySupport proc :DXGI_FORMAT, :ptr, :ptr
   .ends

endif

endif
