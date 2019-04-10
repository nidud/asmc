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
ifndef __bits2_5_h__
__bits2_5_h__ equ <>

ifndef __IBackgroundCopyJobHttpOptions_FWD_DEFINED__
__IBackgroundCopyJobHttpOptions_FWD_DEFINED__ equ 1
endif
ifndef __BackgroundCopyManager2_5_FWD_DEFINED__
__BackgroundCopyManager2_5_FWD_DEFINED__ equ 1
;BackgroundCopyManager2_5 typedef BackgroundCopyManager2_5
endif
ifndef __IBackgroundCopyJobHttpOptions_FWD_DEFINED__
__IBackgroundCopyJobHttpOptions_FWD_DEFINED__ equ 1
endif

include bits.inc
include bits1_5.inc
include bits2_0.inc

ifndef __IBackgroundCopyJobHttpOptions_INTERFACE_DEFINED__
__IBackgroundCopyJobHttpOptions_INTERFACE_DEFINED__ equ 1

BG_CERT_STORE_LOCATION typedef SDWORD
BG_CERT_STORE_LOCATION_CURRENT_USER equ 0
BG_CERT_STORE_LOCATION_LOCAL_MACHINE equ ( BG_CERT_STORE_LOCATION_CURRENT_USER + 1 )
BG_CERT_STORE_LOCATION_CURRENT_SERVICE equ ( BG_CERT_STORE_LOCATION_LOCAL_MACHINE + 1 )
BG_CERT_STORE_LOCATION_SERVICES equ ( BG_CERT_STORE_LOCATION_CURRENT_SERVICE + 1 )
BG_CERT_STORE_LOCATION_USERS equ ( BG_CERT_STORE_LOCATION_SERVICES + 1 )
BG_CERT_STORE_LOCATION_CURRENT_USER_GROUP_POLICY equ ( BG_CERT_STORE_LOCATION_USERS + 1 )
BG_CERT_STORE_LOCATION_LOCAL_MACHINE_GROUP_POLICY equ ( BG_CERT_STORE_LOCATION_CURRENT_USER_GROUP_POLICY + 1 )
BG_CERT_STORE_LOCATION_LOCAL_MACHINE_ENTERPRISE equ ( BG_CERT_STORE_LOCATION_LOCAL_MACHINE_GROUP_POLICY + 1 )

DEFINE_IIDX(IBackgroundCopyJobHttpOptions, "f1bd1079-9f01-4bdc-8036-f09b70095066")

.comdef IBackgroundCopyJobHttpOptions

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetClientCertificateByID proc :BG_CERT_STORE_LOCATION, :LPCWSTR, :ptr
    SetClientCertificateByName proc :BG_CERT_STORE_LOCATION, :LPCWSTR, :LPCWSTR
    RemoveClientCertificate proc
    GetClientCertificate proc :ptr, :ptr
    SetCustomHeaders	proc :LPCWSTR
    GetCustomHeaders	proc :ptr
    SetSecurityFlags	proc :ULONG
    GetSecurityFlags	proc :ptr
    .ends

endif

ifndef __BackgroundCopyManager2_5_LIBRARY_DEFINED__
__BackgroundCopyManager2_5_LIBRARY_DEFINED__ equ 1

DEFINE_GUIDS(LIBID_BackgroundCopyManager2_5, "03ca98d6-ff5d-49b8-abc6-03dd84127020")
DEFINE_GUIDS(CLSID_BackgroundCopyManager2_5, "03ca98d6-ff5d-49b8-abc6-03dd84127020")
endif
endif

BG_SSL_ENABLE_CRL_CHECK equ 0x0001
BG_SSL_IGNORE_CERT_CN_INVALID equ 0x0002
BG_SSL_IGNORE_CERT_DATE_INVALID equ 0x0004
BG_SSL_IGNORE_UNKNOWN_CA equ 0x0008
BG_SSL_IGNORE_CERT_WRONG_USAGE equ 0x0010
BG_HTTP_REDIRECT_POLICY_MASK equ 0x0700
BG_HTTP_REDIRECT_POLICY_ALLOW_SILENT equ 0x0000
BG_HTTP_REDIRECT_POLICY_ALLOW_REPORT equ 0x0100
BG_HTTP_REDIRECT_POLICY_DISALLOW equ 0x0200
BG_HTTP_REDIRECT_POLICY_ALLOW_HTTPS_TO_HTTP equ 0x0800
include bits3_0.inc

endif
