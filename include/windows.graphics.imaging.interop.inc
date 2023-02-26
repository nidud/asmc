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

ifndef __windows2Egraphics2Eimaging2Einterop_h__
define __windows2Egraphics2Eimaging2Einterop_h__

include Inspectable.inc
include mfobjects.inc
include Wincodec.inc
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

ifndef __ISoftwareBitmapNative_INTERFACE_DEFINED__
define __ISoftwareBitmapNative_INTERFACE_DEFINED__

DEFINE_IIDX(ISoftwareBitmapNative, "94BC8415-04EA-4B2E-AF13-4DE95AA898EB")

.comdef ISoftwareBitmapNative : public IInspectable
    GetData             proc :REFIID, :ptr
   .ends

endif

ifndef __ISoftwareBitmapNativeFactory_INTERFACE_DEFINED__
define __ISoftwareBitmapNativeFactory_INTERFACE_DEFINED__

DEFINE_IIDX(ISoftwareBitmapNativeFactory, "C3C181EC-2914-4791-AF02-02D224A10B43")

.comdef ISoftwareBitmapNativeFactory : public IInspectable
    CreateFromWICBitmap proc :ptr, :BOOL, :REFIID, :ptr
    CreateFromMF2DBuffer2 proc :ptr, :REFGUID, :UINT32, :UINT32, :BOOL, :ptr, :REFIID, :ptr
   .ends

endif

endif

endif
