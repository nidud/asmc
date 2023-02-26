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

ifndef __windows2Emedia2Ecore2Einterop_h__
define __windows2Emedia2Ecore2Einterop_h__

include Inspectable.inc
include mfobjects.inc

include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

ifndef __IAudioFrameNative_INTERFACE_DEFINED__
define __IAudioFrameNative_INTERFACE_DEFINED__

DEFINE_IIDX(IAudioFrameNative, "20BE1E2E-930F-4746-9335-3C332F255093")

.comdef IAudioFrameNative : public IInspectable
    GetData             proc :REFIID, :ptr
   .ends

endif

ifndef __IVideoFrameNative_INTERFACE_DEFINED__
define __IVideoFrameNative_INTERFACE_DEFINED__

DEFINE_IIDX(IVideoFrameNative, "26BA702B-314A-4620-AAF6-7A51AA58FA18")

.comdef IVideoFrameNative : public IInspectable
    GetData             proc :REFIID, :ptr
    GetDevice           proc :REFIID, :ptr
   .ends

endif

ifndef __IAudioFrameNativeFactory_INTERFACE_DEFINED__
define __IAudioFrameNativeFactory_INTERFACE_DEFINED__

DEFINE_IIDX(IAudioFrameNativeFactory, "7BD67CF8-BF7D-43E6-AF8D-B170EE0C0110")

.comdef IAudioFrameNativeFactory : public IInspectable
    CreateFromMFSample  proc :ptr, :BOOL, :REFIID, :ptr
   .ends

endif

ifndef __IVideoFrameNativeFactory_INTERFACE_DEFINED__
define __IVideoFrameNativeFactory_INTERFACE_DEFINED__

DEFINE_IIDX(IVideoFrameNativeFactory, "69E3693E-8E1E-4E63-AC4C-7FDC21D9731D")

.comdef IVideoFrameNativeFactory : public IInspectable
    CreateFromMFSample  proc :ptr, :REFGUID, :UINT32, :UINT32, :BOOL, :ptr, :ptr, :REFIID, :ptr
   .ends

endif

endif

endif
