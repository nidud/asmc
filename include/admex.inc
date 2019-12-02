ifndef __REQUIRED_RPCNDR_H_VERSION__
__REQUIRED_RPCNDR_H_VERSION__ equ 475
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
ifndef __admex_h__
__admex_h__ equ <>
.pragma list(push, 0)

ifndef __IMSAdminReplication_FWD_DEFINED__
__IMSAdminReplication_FWD_DEFINED__ equ 1
endif
ifndef __IMSAdminCryptoCapabilities_FWD_DEFINED__
__IMSAdminCryptoCapabilities_FWD_DEFINED__ equ 1
endif
include unknwn.inc
include objidl.inc
include ocidl.inc

MIDL_user_allocate proto WINAPI :SIZE_T
MIDL_user_free proto WINAPI :PVOID

ifndef _ADMEX_IADM_
_ADMEX_IADM_ equ <>

DEFINE_GUID(IID_IMSAdminReplication, 0xc804d980, 0xebec, 0x11d0, 0xa6, 0xa0, 0x0,0xa0, 0xc9, 0x22, 0xe7, 0x52)
DEFINE_GUID(IID_IMSAdminCryptoCapabilities, 0x78b64540, 0xf26d, 0x11d0, 0xa6, 0xa3, 0x0,0xa0, 0xc9, 0x22, 0xe7, 0x52)
DEFINE_GUID(CLSID_MSCryptoAdmEx, 0x9f0bd3a0, 0xec01, 0x11d0, 0xa6, 0xa0, 0x0,0xa0, 0xc9, 0x22, 0xe7, 0x52)

ifndef __IMSAdminReplication_INTERFACE_DEFINED__
__IMSAdminReplication_INTERFACE_DEFINED__ equ 1

.comdef IMSAdminReplication : public IUnknown

    GetSignature	proc :DWORD, :ptr, :ptr
    Propagate		proc :DWORD, :ptr
    Propagate2		proc :DWORD, :ptr, :DWORD
    Serialize		proc :DWORD, :ptr, :ptr
    DeSerialize		proc :DWORD, :ptr

    .ends

endif

ifndef __IMSAdminCryptoCapabilities_INTERFACE_DEFINED__
__IMSAdminCryptoCapabilities_INTERFACE_DEFINED__ equ 1

.comdef IMSAdminCryptoCapabilities : public IUnknown

    GetProtocols	proc :DWORD, :ptr, :ptr
    GetMaximumCipherStrength proc :LPDWORD
    GetRootCertificates proc :DWORD, :ptr, :ptr
    GetSupportedAlgs	proc :DWORD, :ptr, :ptr
    SetCAList		proc :DWORD, :ptr

    .ends

endif
endif

.pragma list(pop)
endif
