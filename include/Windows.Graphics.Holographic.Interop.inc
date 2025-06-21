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

ifndef __windows2Egraphics2Eholographic2Einterop_h__
define __windows2Egraphics2Eholographic2Einterop_h__

include inspectable.inc
include d3d12.inc
include winapifamily.inc

if (NTDDI_VERSION ge NTDDI_WIN10_RS2)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

ifndef __IHolographicCameraInterop_INTERFACE_DEFINED__
define __IHolographicCameraInterop_INTERFACE_DEFINED__

DEFINE_IIDX(IHolographicCameraInterop, "7cc1f9c5-6d02-41fa-9500-e1809eb48eec")

.comdef IHolographicCameraInterop : public IInspectable
    CreateDirect3D12BackBufferResource proc :ptr, :ptr, :ptr
    CreateDirect3D12HardwareProtectedBackBufferResource proc :ptr, :ptr, :ptr, :ptr
    AcquireDirect3D12BufferResource proc :ptr, :ptr
    AcquireDirect3D12BufferResourceWithTimeout proc :ptr, :ptr, :UINT64
    UnacquireDirect3D12BufferResource proc :ptr
   .ends

endif

ifndef __IHolographicCameraRenderingParametersInterop_INTERFACE_DEFINED__
define __IHolographicCameraRenderingParametersInterop_INTERFACE_DEFINED__

DEFINE_IIDX(IHolographicCameraRenderingParametersInterop, "f75b68d6-d1fd-4707-aafd-fa6f4c0e3bf4")

.comdef IHolographicCameraRenderingParametersInterop : public IInspectable
    CommitDirect3D12Resource proc :ptr, :ptr, :UINT64
    CommitDirect3D12ResourceWithDepthData proc :ptr, :ptr, :UINT64, :ptr, :ptr, :UINT64
   .ends

endif

ifndef __IHolographicQuadLayerInterop_INTERFACE_DEFINED__
define __IHolographicQuadLayerInterop_INTERFACE_DEFINED__

DEFINE_IIDX(IHolographicQuadLayerInterop, "cfa688f0-639e-4a47-83d7-6b7f5ebf7fed")

.comdef IHolographicQuadLayerInterop : public IInspectable
    CreateDirect3D12ContentBufferResource proc :ptr, :ptr, :ptr
    CreateDirect3D12HardwareProtectedContentBufferResource proc :ptr, :ptr, :ptr, :ptr
    AcquireDirect3D12BufferResource proc :ptr, :ptr
    AcquireDirect3D12BufferResourceWithTimeout proc :ptr, :ptr, :UINT64
    UnacquireDirect3D12BufferResource proc :ptr
   .ends

endif

ifndef __IHolographicQuadLayerUpdateParametersInterop_INTERFACE_DEFINED__
define __IHolographicQuadLayerUpdateParametersInterop_INTERFACE_DEFINED__

DEFINE_IIDX(IHolographicQuadLayerUpdateParametersInterop, "e5f549cd-c909-444f-8809-7cc18a9c8920")

.comdef IHolographicQuadLayerUpdateParametersInterop : public IInspectable
    CommitDirect3D12Resource proc :ptr, :ptr, :UINT64
   .ends

endif

endif

endif

endif
