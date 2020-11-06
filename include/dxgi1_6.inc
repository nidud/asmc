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

ifndef __dxgi1_6_h__
__dxgi1_6_h__ equ <>

ifndef __IDXGIAdapter4_FWD_DEFINED__
__IDXGIAdapter4_FWD_DEFINED__ equ 1
endif
ifndef __IDXGIOutput6_FWD_DEFINED__
__IDXGIOutput6_FWD_DEFINED__ equ 1
endif
ifndef __IDXGIFactory6_FWD_DEFINED__
__IDXGIFactory6_FWD_DEFINED__ equ 1
endif
ifndef __IDXGIFactory7_FWD_DEFINED__
__IDXGIFactory7_FWD_DEFINED__ equ 1
endif

include dxgi1_5.inc

DXGIDeclareAdapterRemovalSupport proto WINAPI

.enum DXGI_ADAPTER_FLAG3 {
    DXGI_ADAPTER_FLAG3_NONE	= 0,
    DXGI_ADAPTER_FLAG3_REMOTE	= 1,
    DXGI_ADAPTER_FLAG3_SOFTWARE = 2,
    DXGI_ADAPTER_FLAG3_ACG_COMPATIBLE	= 4,
    DXGI_ADAPTER_FLAG3_SUPPORT_MONITORED_FENCES = 8,
    DXGI_ADAPTER_FLAG3_SUPPORT_NON_MONITORED_FENCES	= 0x10,
    DXGI_ADAPTER_FLAG3_KEYED_MUTEX_CONFORMANCE	= 0x20,
    DXGI_ADAPTER_FLAG3_FORCE_DWORD	= 0xffffffff
    }

DXGI_ADAPTER_DESC3	STRUC
Description		WCHAR 128 dup(?)
VendorId		UINT ?
DeviceId		UINT ?
SubSysId		UINT ?
Revision		UINT ?
DedicatedVideoMemory	SIZE_T ?
DedicatedSystemMemory	SIZE_T ?
SharedSystemMemory	SIZE_T ?
AdapterLuid		LUID <>
Flags			DXGI_ADAPTER_FLAG3 ?
GraphicsPreemptionGranularity DXGI_GRAPHICS_PREEMPTION_GRANULARITY ?
ComputePreemptionGranularity DXGI_COMPUTE_PREEMPTION_GRANULARITY ?
DXGI_ADAPTER_DESC3	ENDS

ifndef __IDXGIAdapter4_INTERFACE_DEFINED__
__IDXGIAdapter4_INTERFACE_DEFINED__ equ 1

.comdef IDXGIAdapter4 : public IDXGIAdapter3

    GetDesc3		proc :ptr
    .ends

endif

DXGI_OUTPUT_DESC1	STRUC
DeviceName		WCHAR  32  dup(?)
DesktopCoordinates	RECT <>
AttachedToDesktop	BOOL ?
Rotation		DXGI_MODE_ROTATION ?
_Monitor		HMONITOR ?
BitsPerColor		UINT ?
ColorSpace		DXGI_COLOR_SPACE_TYPE ?
RedPrimary		FLOAT  2  dup(?)
GreenPrimary		FLOAT  2  dup(?)
BluePrimary		FLOAT  2  dup(?)
WhitePoint		FLOAT  2  dup(?)
MinLuminance		FLOAT ?
MaxLuminance		FLOAT ?
MaxFullFrameLuminance	FLOAT ?
DXGI_OUTPUT_DESC1	ENDS

.enum DXGI_HARDWARE_COMPOSITION_SUPPORT_FLAGS {
    DXGI_HARDWARE_COMPOSITION_SUPPORT_FLAG_FULLSCREEN	= 1,
    DXGI_HARDWARE_COMPOSITION_SUPPORT_FLAG_WINDOWED	= 2,
    DXGI_HARDWARE_COMPOSITION_SUPPORT_FLAG_CURSOR_STRETCHED	= 4
    }

ifndef __IDXGIOutput6_INTERFACE_DEFINED__
__IDXGIOutput6_INTERFACE_DEFINED__ equ 1

.comdef IDXGIOutput6 : public IDXGIOutput5

    GetDesc1		proc :ptr
    CheckHardwareCompositionSupport proc :ptr
    .ends

endif

.enum DXGI_GPU_PREFERENCE {
    DXGI_GPU_PREFERENCE_UNSPECIFIED	= 0,
    DXGI_GPU_PREFERENCE_MINIMUM_POWER	= ( DXGI_GPU_PREFERENCE_UNSPECIFIED + 1 ) ,
    DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE	= ( DXGI_GPU_PREFERENCE_MINIMUM_POWER + 1 )
    }

ifndef __IDXGIFactory6_INTERFACE_DEFINED__
__IDXGIFactory6_INTERFACE_DEFINED__ equ 1

.comdef IDXGIFactory6 : public IDXGIFactory5

    EnumAdapterByGpuPreference proc :UINT, :DXGI_GPU_PREFERENCE, :REFIID, :ptr
    .ends

endif


ifndef __IDXGIFactory7_INTERFACE_DEFINED__
__IDXGIFactory7_INTERFACE_DEFINED__ equ 1

.comdef IDXGIFactory7 : public IDXGIFactory6
    RegisterAdaptersChangedEvent proc :HANDLE, :ptr
    UnregisterAdaptersChangedEvent proc :DWORD
    .ends

endif

DEFINE_GUID(IID_IDXGIAdapter4,0x3c8d99d1,0x4fbf,0x4181,0xa8,0x2c,0xaf,0x66,0xbf,0x7b,0xd2,0x4e)
DEFINE_GUID(IID_IDXGIOutput6,0x068346e8,0xaaec,0x4b84,0xad,0xd7,0x13,0x7f,0x51,0x3f,0x77,0xa1)
DEFINE_GUID(IID_IDXGIFactory6,0xc1b6694f,0xff09,0x44a9,0xb0,0x3c,0x77,0x90,0x0a,0x0a,0x1d,0x17)
DEFINE_GUID(IID_IDXGIFactory7,0xa4966eed,0x76db,0x44da,0x84,0xc1,0xee,0x9a,0x7a,0xfb,0x20,0xa8)

endif
