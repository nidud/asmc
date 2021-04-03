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

ifndef __restrictederrorinfo_h__
__restrictederrorinfo_h__ equ 1

ifndef __IRestrictedErrorInfo_FWD_DEFINED__
__IRestrictedErrorInfo_FWD_DEFINED__ equ 1
endif
ifndef __ILanguageExceptionErrorInfo_FWD_DEFINED__
__ILanguageExceptionErrorInfo_FWD_DEFINED__ equ 1
endif

include oaidl.inc
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

ifndef __IRestrictedErrorInfo_INTERFACE_DEFINED__
__IRestrictedErrorInfo_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IRestrictedErrorInfo, "82BA7092-4C88-427D-A7BC-16DD93FEB67E")

.comdef IRestrictedErrorInfo : public IUnknown

    GetErrorDetails     proc :ptr, :ptr, :ptr, :ptr
    GetReference        proc :ptr
    .ends

endif

ifndef __ILanguageExceptionErrorInfo_INTERFACE_DEFINED__
__ILanguageExceptionErrorInfo_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ILanguageExceptionErrorInfo, "04a2dbf3-df83-116c-0946-0812abf6e07d")

.comdef ILanguageExceptionErrorInfo : public IUnknown

    GetLanguageException proc :ptr
    .ends

endif

endif

endif

