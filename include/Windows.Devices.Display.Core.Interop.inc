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

ifndef __windows2Edevices2Edisplay2Ecore2Einterop_h__
define __windows2Edevices2Edisplay2Ecore2Einterop_h__

include oaidl.inc
include ocidl.inc
include Inspectable.inc

ifdef __midl
ifndef LUID_DEFINED
define LUID_DEFINED 1
__LUID                  struct
LowPart                 DWORD ?
HighPart                LONG ?
__LUID                  ends
LUID                    typedef __LUID
PLUID                   typedef ptr __LUID
endif
endif

include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

ifndef __IDisplayDeviceInterop_INTERFACE_DEFINED__
define __IDisplayDeviceInterop_INTERFACE_DEFINED__

DEFINE_IIDX(IDisplayDeviceInterop, "64338358-366A-471B-BD56-DD8EF48E439B")

.comdef IDisplayDeviceInterop : public IUnknown
    CreateSharedHandle  proc :ptr, :ptr, :DWORD, :HSTRING, :ptr
    OpenSharedHandle    proc :HANDLE, :IID, :ptr ptr
   .ends

endif

ifndef __IDisplayPathInterop_INTERFACE_DEFINED__
define __IDisplayPathInterop_INTERFACE_DEFINED__

DEFINE_IIDX(IDisplayPathInterop, "A6BA4205-E59E-4E71-B25B-4E436D21EE3D")

.comdef IDisplayPathInterop : public IUnknown
    CreateSourcePresentationHandle proc :ptr
    GetSourceId         proc :ptr
   .ends

endif

endif

endif
