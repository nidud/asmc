ifndef __REQUIRED_RPCNDR_H_VERSION__
define __REQUIRED_RPCNDR_H_VERSION__ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
define __REQUIRED_RPCSAL_H_VERSION__ 100
endif

include rpc.inc
include rpcndr.inc

ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr.inc>
endif

ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif

ifndef __regbag_h__
define __regbag_h__

include objidl.inc
include oaidl.inc
include ocidl.inc

include winapifamily.inc
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
