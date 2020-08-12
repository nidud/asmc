ifndef __REQUIRED_RPCNDR_H_VERSION__
__REQUIRED_RPCNDR_H_VERSION__ equ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
__REQUIRED_RPCSAL_H_VERSION__ equ 100
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
__regbag_h__ equ <>

ifndef __ICreatePropBagOnRegKey_FWD_DEFINED__
__ICreatePropBagOnRegKey_FWD_DEFINED__ equ 1
endif

include objidl.inc
include oaidl.inc
include ocidl.inc

include winapifamily.inc
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef __ICreatePropBagOnRegKey_INTERFACE_DEFINED__
__ICreatePropBagOnRegKey_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ICreatePropBagOnRegKey, "8A674B48-1F63-11d3-B64C-00C04F79498E")

.comdef ICreatePropBagOnRegKey : public IUnknown

    Create		proc :HKEY, :LPCOLESTR, :DWORD, :DWORD, :REFIID, :ptr
    .ends

endif
endif
endif
