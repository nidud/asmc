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

ifndef __windows2Esecurity2Eisolation2Eisolatedenvironmentinterop_h__
define __windows2Esecurity2Eisolation2Eisolatedenvironmentinterop_h__

include oaidl.inc
include ocidl.inc

include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef __IIsolatedEnvironmentInterop_INTERFACE_DEFINED__
define __IIsolatedEnvironmentInterop_INTERFACE_DEFINED__

DEFINE_IIDX(IIsolatedEnvironmentInterop, "85713C2E-8E62-46C5-8DE2-C647E1D54636")

.comdef IIsolatedEnvironmentInterop : public IUnknown
    GetHostHwndInterop  proc :HWND, :ptr
   .ends

endif

endif

HWND_UserSize proto WINAPI :ptr, :dword, :ptr
HWND_UserMarshal proto WINAPI :ptr, :ptr, :ptr
HWND_UserUnmarshal proto WINAPI :ptr, :ptr, :ptr
HWND_UserFree proto WINAPI :ptr, :ptr

HWND_UserSize64 proto WINAPI :ptr, :dword, :ptr
HWND_UserMarshal64 proto WINAPI :ptr, :ptr, :ptr
HWND_UserUnmarshal64 proto WINAPI :ptr, :ptr, :ptr
HWND_UserFree64 proto WINAPI :ptr, :ptr

endif
