ifndef _RPCNDR500_
include rpcndr500.inc
endif

ifndef __admex_h__
define __admex_h__

.pragma list(push, 0)

ifndef __unknwn_h__
include unknwn.inc
endif
include objidl.inc
include ocidl.inc

MIDL_user_allocate proto WINAPI :size_t
MIDL_user_free proto WINAPI :ptr

ifndef _ADMEX_IADM_
define _ADMEX_IADM_

DEFINE_GUID(IID_IMSAdminReplication, 0xc804d980, 0xebec, 0x11d0, 0xa6, 0xa0, 0x0,0xa0, 0xc9, 0x22, 0xe7, 0x52)
DEFINE_GUID(IID_IMSAdminCryptoCapabilities, 0x78b64540, 0xf26d, 0x11d0, 0xa6, 0xa3, 0x0,0xa0, 0xc9, 0x22, 0xe7, 0x52)
DEFINE_GUID(CLSID_MSCryptoAdmEx, 0x9f0bd3a0, 0xec01, 0x11d0, 0xa6, 0xa0, 0x0,0xa0, 0xc9, 0x22, 0xe7, 0x52)

ifndef __IMSAdminReplication_INTERFACE_DEFINED__
define __IMSAdminReplication_INTERFACE_DEFINED__

.comdef IMSAdminReplication : public IUnknown

    GetSignature	proc :DWORD, :ptr, :ptr
    Propagate		proc :DWORD, :ptr
    Propagate2		proc :DWORD, :ptr, :DWORD
    Serialize		proc :DWORD, :ptr, :ptr
    DeSerialize		proc :DWORD, :ptr
   .ends

endif

ifndef __IMSAdminCryptoCapabilities_INTERFACE_DEFINED__
define __IMSAdminCryptoCapabilities_INTERFACE_DEFINED__

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
