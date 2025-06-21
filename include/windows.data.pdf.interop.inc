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

ifndef __windows2Edata2Epdf2Einterop_h__
define __windows2Edata2Epdf2Einterop_h__

include oaidl.inc
include dxgi.inc
include d2dbasetypes.inc

if (NTDDI_VERSION ge NTDDI_WINBLUE)

if 0
ID2D1DeviceContext      typedef ptr DWORD
D2D_RECT_F              typedef ptr DWORD
D2D_COLOR_F             typedef ptr DWORD
endif

CALLBACK(PFN_PDF_CREATE_RENDERER, :ptr, :ptr ptr)

PdfCreateRenderer proto WINAPI :ptr, :ptr ptr

PDF_RENDER_PARAMS       struct
SourceRect              D2D_RECT_F ?
DestinationWidth        UINT32 ?
DestinationHeight       UINT32 ?
BackgroundColor         D2D_COLOR_F ?
IgnoreHighContrast      BOOLEAN ?
PDF_RENDER_PARAMS       ends


ifndef __IPdfRendererNative_INTERFACE_DEFINED__
define __IPdfRendererNative_INTERFACE_DEFINED__

DEFINE_IIDX(IPdfRendererNative, "7d9dcd91-d277-4947-8527-07a0daeda94a")

.comdef IPdfRendererNative : public IUnknown

    RenderPageToSurface proc :ptr, :ptr, :POINT, :ptr
    RenderPageToDeviceContext proc :ptr, :ptr, :ptr
   .ends

endif

endif

endif
