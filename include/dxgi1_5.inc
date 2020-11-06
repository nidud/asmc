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

ifndef __dxgi1_5_h__
__dxgi1_5_h__ equ <>

ifndef __IDXGIOutput5_FWD_DEFINED__
__IDXGIOutput5_FWD_DEFINED__ equ 1
endif
ifndef __IDXGISwapChain4_FWD_DEFINED__
__IDXGISwapChain4_FWD_DEFINED__ equ 1
endif
ifndef __IDXGIDevice4_FWD_DEFINED__
__IDXGIDevice4_FWD_DEFINED__ equ 1
endif
ifndef __IDXGIFactory5_FWD_DEFINED__
__IDXGIFactory5_FWD_DEFINED__ equ 1
endif

include dxgi1_4.inc

.enum DXGI_OUTDUPL_FLAG {
    DXGI_OUTDUPL_COMPOSITED_UI_CAPTURE_ONLY	= 1
    }


ifndef __IDXGIOutput5_INTERFACE_DEFINED__
__IDXGIOutput5_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDXGIOutput5, "80A07424-AB52-42EB-833C-0C42FD282D98")

.comdef IDXGIOutput5 : public IDXGIOutput4

    DuplicateOutput1	proc :ptr, :UINT, :UINT

    .ends

endif

.enum DXGI_HDR_METADATA_TYPE {
    DXGI_HDR_METADATA_TYPE_NONE = 0,
    DXGI_HDR_METADATA_TYPE_HDR10	= 1,
    DXGI_HDR_METADATA_TYPE_HDR10PLUS	= 2
    }

DXGI_HDR_METADATA_HDR10 STRUC
RedPrimary		UINT16	2  dup(?)
GreenPrimary		UINT16	2  dup(?)
BluePrimary		UINT16	2  dup(?)
WhitePoint		UINT16	2  dup(?)
MaxMasteringLuminance	UINT ?
MinMasteringLuminance	UINT ?
MaxContentLightLevel	UINT16 ?
MaxFrameAverageLightLevel UINT16 ?
DXGI_HDR_METADATA_HDR10 ENDS

DXGI_HDR_METADATA_HDR10PLUS STRUC
Data			db  72	dup(?)
DXGI_HDR_METADATA_HDR10PLUS ENDS

ifndef __IDXGISwapChain4_INTERFACE_DEFINED__
__IDXGISwapChain4_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDXGISwapChain4, "3D585D5A-BD4A-489E-B1F4-3DBCB6452FFB")

.comdef IDXGISwapChain4 : public IDXGISwapChain3

    SetHDRMetaData	proc :DXGI_HDR_METADATA_TYPE, :UINT, :ptr

    .ends

endif

.enum DXGI_OFFER_RESOURCE_FLAGS {
    DXGI_OFFER_RESOURCE_FLAG_ALLOW_DECOMMIT	= 0x1
    }

.enum DXGI_RECLAIM_RESOURCE_RESULTS {
    DXGI_RECLAIM_RESOURCE_RESULT_OK	= 0,
    DXGI_RECLAIM_RESOURCE_RESULT_DISCARDED	= 1,
    DXGI_RECLAIM_RESOURCE_RESULT_NOT_COMMITTED	= 2
    }

ifndef __IDXGIDevice4_INTERFACE_DEFINED__
__IDXGIDevice4_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDXGIDevice4, "95B4F95F-D8DA-4CA4-9EE6-3B76D5968A10")

.comdef IDXGIDevice4 : public IDXGIDevice3

    OfferResources1	proc :UINT
    ReclaimResources1	proc :UINT, :ptr
    .ends

endif

.enum DXGI_FEATURE {
    DXGI_FEATURE_PRESENT_ALLOW_TEARING	= 0
    }

ifndef __IDXGIFactory5_INTERFACE_DEFINED__
__IDXGIFactory5_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDXGIFactory5, "7632e1f5-ee65-4dca-87fd-84cd75f8838d")

.comdef IDXGIFactory5 : public IDXGIFactory4

    CheckFeatureSupport proc :DXGI_FEATURE

    .ends

endif

endif
