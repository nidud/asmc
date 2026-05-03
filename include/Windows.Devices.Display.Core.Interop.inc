ifndef _RPCNDR500_
include rpcndr500.inc
endif

ifndef __windows2Edevices2Edisplay2Ecore2Einterop_h__
define __windows2Edevices2Edisplay2Ecore2Einterop_h__

ifndef __oaidl_h__
include oaidl.inc
endif
ifndef __ocidl_h__
include ocidl.inc
endif
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

ifndef _WINAPIFAMILY_
include winapifamily.inc
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

ifndef __IDisplayDeviceInterop_INTERFACE_DEFINED__
define __IDisplayDeviceInterop_INTERFACE_DEFINED__

DEFINE_IIDX(IDisplayDeviceInterop, "64338358-366A-471B-BD56-DD8EF48E439B")

.comdef IDisplayDeviceInterop : public IUnknown
    CreateSharedHandle  proc :ptr, :ptr, :DWORD, :HSTRING, :ptr
    OpenSharedHandle    proc :HANDLE, :IID, :ptr
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
