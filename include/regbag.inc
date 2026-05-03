ifndef _RPCNDR500_
include rpcndr500.inc
endif

ifndef __regbag_h__
define __regbag_h__

include objidl.inc
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

ifndef __ICreatePropBagOnRegKey_INTERFACE_DEFINED__
define __ICreatePropBagOnRegKey_INTERFACE_DEFINED__

DEFINE_IIDX(ICreatePropBagOnRegKey, "8A674B48-1F63-11d3-B64C-00C04F79498E")

.comdef ICreatePropBagOnRegKey : public IUnknown

    Create		proc :HKEY, :LPCOLESTR, :DWORD, :DWORD, :REFIID, :ptr
   .ends

endif
endif
endif
