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

ifndef __filtereg_h__
define __filtereg_h__

include oaidl.inc
include ocidl.inc
include filter.inc

include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

externdef CLSID_FilterRegistration:CLSID

ifndef __ILoadFilter_INTERFACE_DEFINED__
define __ILoadFilter_INTERFACE_DEFINED__

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
