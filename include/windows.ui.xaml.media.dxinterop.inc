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

ifndef __windows2Eui2Examl2Emedia2Edxinterop_h__
define __windows2Eui2Examl2Emedia2Edxinterop_h__

include oaidl.inc
include dxgi.inc

if (NTDDI_VERSION ge NTDDI_WIN8)

ifndef REFRECT
REFRECT typedef ptr RECT
endif

ifndef __ISurfaceImageSourceNative_INTERFACE_DEFINED__
define __ISurfaceImageSourceNative_INTERFACE_DEFINED__

DEFINE_IIDX(ISurfaceImageSourceNative, "f2e9edc1-d307-4525-9886-0fafaa44163c")

.comdef ISurfaceImageSourceNative : public IUnknown
    SetDevice           proc :ptr
    BeginDraw           proc :ptr, :ptr, :ptr
    EndDraw             proc
   .ends

endif

ifndef __IVirtualSurfaceUpdatesCallbackNative_INTERFACE_DEFINED__
define __IVirtualSurfaceUpdatesCallbackNative_INTERFACE_DEFINED__

DEFINE_IIDX(IVirtualSurfaceUpdatesCallbackNative, "dbf2e947-8e6c-4254-9eee-7738f71386c9")

.comdef IVirtualSurfaceUpdatesCallbackNative : public IUnknown
    UpdatesNeeded       proc
   .ends

endif

ifndef __IVirtualSurfaceImageSourceNative_INTERFACE_DEFINED__
define __IVirtualSurfaceImageSourceNative_INTERFACE_DEFINED__

DEFINE_IIDX(IVirtualSurfaceImageSourceNative, "e9550983-360b-4f53-b391-afd695078691")

.comdef IVirtualSurfaceImageSourceNative : public ISurfaceImageSourceNative
    Invalidate          proc :RECT
    GetUpdateRectCount  proc :ptr
    GetUpdateRects      proc :ptr, :DWORD
    GetVisibleBounds    proc :ptr
    RegisterForUpdatesNeeded proc :ptr
    Resize              proc :SINT, :SINT
   .ends

endif

ifndef __ISwapChainBackgroundPanelNative_INTERFACE_DEFINED__
define __ISwapChainBackgroundPanelNative_INTERFACE_DEFINED__

DEFINE_IIDX(ISwapChainBackgroundPanelNative, "43bebd4e-add5-4035-8f85-5608d08e9dc9")

.comdef ISwapChainBackgroundPanelNative : public IUnknown
    SetSwapChain        proc :ptr
   .ends

endif

endif

if (NTDDI_VERSION ge NTDDI_WINBLUE)
define E_SURFACE_CONTENTS_LOST 0x802b0020

ifndef __ISurfaceImageSourceManagerNative_INTERFACE_DEFINED__
define __ISurfaceImageSourceManagerNative_INTERFACE_DEFINED__

DEFINE_IIDX(ISurfaceImageSourceManagerNative, "4C8798B7-1D88-4A0F-B59B-B93F600DE8C8")

.comdef ISurfaceImageSourceManagerNative : public IUnknown
    FlushAllSurfacesWithDevice proc :ptr
   .ends

endif

ifndef __ISurfaceImageSourceNativeWithD2D_INTERFACE_DEFINED__
define __ISurfaceImageSourceNativeWithD2D_INTERFACE_DEFINED__

DEFINE_IIDX(ISurfaceImageSourceNativeWithD2D, "54298223-41e1-4a41-9c08-02e8256864a1")

.comdef ISurfaceImageSourceNativeWithD2D : public IUnknown
    SetDevice           proc :ptr
    BeginDraw           proc :REFRECT, :REFIID, :ptr, :ptr
    EndDraw             proc
    SuspendDraw         proc
    ResumeDraw          proc
   .ends

endif

ifndef __ISwapChainPanelNative_INTERFACE_DEFINED__
define __ISwapChainPanelNative_INTERFACE_DEFINED__

DEFINE_IIDX(ISwapChainPanelNative, "F92F19D2-3ADE-45A6-A20C-F6F1EA90554B")

.comdef ISwapChainPanelNative : public IUnknown
    SetSwapChain        proc :ptr
   .ends

endif

endif

if (NTDDI_VERSION ge NTDDI_WINTHRESHOLD)

ifndef __ISwapChainPanelNative2_INTERFACE_DEFINED__
define __ISwapChainPanelNative2_INTERFACE_DEFINED__

DEFINE_IIDX(ISwapChainPanelNative2, "D5A2F60C-37B2-44A2-937B-8D8EB9726821")

.comdef ISwapChainPanelNative2 : public ISwapChainPanelNative
    SetSwapChainHandle  proc :HANDLE
   .ends

endif

endif

endif
