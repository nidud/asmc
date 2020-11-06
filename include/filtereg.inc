ifndef __REQUIRED_RPCNDR_H_VERSION__
__REQUIRED_RPCNDR_H_VERSION__ equ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
__REQUIRED_RPCSAL_H_VERSION__ equ 100
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

ifndef __filtereg_h__
__filtereg_h__ equ <>

ifndef __ILoadFilter_FWD_DEFINED__
__ILoadFilter_FWD_DEFINED__ equ 1
endif

include oaidl.inc
include ocidl.inc
include filter.inc

include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

externdef CLSID_FilterRegistration:CLSID

ifndef __ILoadFilter_INTERFACE_DEFINED__
__ILoadFilter_INTERFACE_DEFINED__ equ 1

FILTERED_DATA_SOURCES	STRUC
pwcsExtension		LPWSTR ?
pwcsMime		LPWSTR ?
pClsid			LPCLSID ?
pwcsOverride		LPWSTR ?
FILTERED_DATA_SOURCES	ENDS

DEFINE_IIDX(ILoadFilter, "c7310722-ac80-11d1-8df3-00c04fb6ef4f")

.comdef ILoadFilter : public IUnknown

    LoadIFilter		proc :LPCWSTR, :ptr, :ptr, :BOOL, :ptr, :ptr, :ptr, :ptr
    LoadIFilterFromStorage proc :ptr, :ptr, :LPCWSTR, :BOOL, :ptr, :ptr, :ptr, :ptr
    LoadIFilterFromStream proc :ptr, :ptr, :ptr, :BOOL, :ptr, :ptr, :ptr, :ptr
    .ends

endif

endif
endif