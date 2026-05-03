ifndef _RPCNDR500_
include rpcndr500.inc
endif

ifndef __filtereg_h__
define __filtereg_h__

ifndef __oaidl_h__
include oaidl.inc
endif
ifndef __ocidl_h__
include ocidl.inc
endif
include filter.inc
ifndef _WINAPIFAMILY_
include winapifamily.inc
endif

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
