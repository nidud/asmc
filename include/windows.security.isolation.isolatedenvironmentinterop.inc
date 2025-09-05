ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Esecurity2Eisolation2Eisolatedenvironmentinterop_h__
define __windows2Esecurity2Eisolation2Eisolatedenvironmentinterop_h__

ifndef __oaidl_h__
include oaidl.inc
endif
ifndef __ocidl_h__
include ocidl.inc
endif
ifndef _WINAPIFAMILY_
include winapifamily.inc
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
ifndef __IIsolatedEnvironmentInterop_INTERFACE_DEFINED__
define __IIsolatedEnvironmentInterop_INTERFACE_DEFINED__

DEFINE_IIDX(IIsolatedEnvironmentInterop, "85713C2E-8E62-46C5-8DE2-C647E1D54636")

.comdef IIsolatedEnvironmentInterop : public IUnknown
    GetHostHwndInterop  proc :HWND, :ptr
   .ends

endif
endif

endif
