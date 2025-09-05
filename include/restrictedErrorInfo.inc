ifndef _RPCNDR500_
include rpcndr500.inc
endif

ifndef __restrictederrorinfo_h__
define __restrictederrorinfo_h__

ifndef __oaidl_h__
include oaidl.inc
endif
ifndef _WINAPIFAMILY_
include winapifamily.inc
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

ifndef __IRestrictedErrorInfo_INTERFACE_DEFINED__
define __IRestrictedErrorInfo_INTERFACE_DEFINED__

DEFINE_IIDX(IRestrictedErrorInfo, "82BA7092-4C88-427D-A7BC-16DD93FEB67E")

.comdef IRestrictedErrorInfo : public IUnknown

    GetErrorDetails     proc :ptr, :ptr, :ptr, :ptr
    GetReference        proc :ptr
   .ends

endif

ifndef __ILanguageExceptionErrorInfo_INTERFACE_DEFINED__
define __ILanguageExceptionErrorInfo_INTERFACE_DEFINED__

DEFINE_IIDX(ILanguageExceptionErrorInfo, "04a2dbf3-df83-116c-0946-0812abf6e07d")

.comdef ILanguageExceptionErrorInfo : public IUnknown

    GetLanguageException proc :ptr
   .ends

endif
endif
endif
