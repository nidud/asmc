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

externdef		__MIDL_itf_admex_0000_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_admex_0000_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IMSAdminReplication_INTERFACE_DEFINED__
__IMSAdminReplication_INTERFACE_DEFINED__ equ 1

.comdef IMSAdminReplication

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetSignature	proc :DWORD, :ptr, :ptr
    Propagate		proc :DWORD, :ptr
    Propagate2		proc :DWORD, :ptr, :DWORD
    Serialize		proc :DWORD, :ptr, :ptr
    DeSerialize		proc :DWORD, :ptr
    .ends

;HRESULT
IMSAdminReplication_GetSignature_Proxy proto WINAPI \
		 _This: ptr,
	  dwBufferSize: DWORD,
	      pbBuffer: ptr char,
pdwMDRequiredBufferSize: ptr DWORD

;void
IMSAdminReplication_GetSignature_Stub proto WINAPI \
		 _This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

;HRESULT
IMSAdminReplication_Propagate_Proxy proto WINAPI \
		 _This: ptr,
	  dwBufferSize: DWORD,
	     pszBuffer: ptr char


;void
IMSAdminReplication_Propagate_Stub proto WINAPI \
		 _This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD


;HRESULT
IMSAdminReplication_Propagate2_Proxy proto WINAPI \
		 _This: ptr,
	  dwBufferSize: DWORD,
	     pszBuffer: ptr char,
   dwSignatureMismatch: DWORD

;void
IMSAdminReplication_Propagate2_Stub proto WINAPI \
		 _This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

;HRESULT
IMSAdminReplication_Serialize_Proxy proto WINAPI \
		 _This: ptr,
	  dwBufferSize: DWORD,
	      pbBuffer: ptr char,
pdwMDRequiredBufferSize: ptr DWORD

;void
IMSAdminReplication_Serialize_Stub proto WINAPI \
		 _This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

;HRESULT
IMSAdminReplication_DeSerialize_Proxy proto WINAPI \
		 _This: ptr,
	  dwBufferSize: DWORD,
	      pbBuffer: ptr char

;void
IMSAdminReplication_DeSerialize_Stub proto WINAPI \
		 _This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

endif

externdef		__MIDL_itf_admex_0255_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_admex_0255_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IMSAdminCryptoCapabilities_INTERFACE_DEFINED__
__IMSAdminCryptoCapabilities_INTERFACE_DEFINED__ equ 1

.comdef IMSAdminCryptoCapabilities

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetProtocols	proc :DWORD, :ptr, :ptr
    GetMaximumCipherStrength proc :LPDWORD
    GetRootCertificates proc :DWORD, :ptr, :ptr
    GetSupportedAlgs	proc :DWORD, :ptr, :ptr
    SetCAList		proc :DWORD, :ptr
    .ends

;HRESULT
IMSAdminCryptoCapabilities_GetProtocols_Proxy proto WINAPI \
		 _This: ptr,
	  dwBufferSize: DWORD,
	      pbBuffer: ptr char,
pdwMDRequiredBufferSize: ptr DWORD

;void
IMSAdminCryptoCapabilities_GetProtocols_Stub proto WINAPI \
		 _This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

;HRESULT
IMSAdminCryptoCapabilities_GetMaximumCipherStrength_Proxy proto WINAPI \
		 _This: ptr,
pdwMaximumCipherStrength: LPDWORD

;void
IMSAdminCryptoCapabilities_GetMaximumCipherStrength_Stub proto WINAPI \
		 _This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

;HRESULT
IMSAdminCryptoCapabilities_GetRootCertificates_Proxy proto WINAPI \
		 _This: ptr,
	  dwBufferSize: DWORD,
	      pbBuffer: ptr char,
pdwMDRequiredBufferSize: ptr DWORD

;void
IMSAdminCryptoCapabilities_GetRootCertificates_Stub proto WINAPI \
		 _This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

;HRESULT
IMSAdminCryptoCapabilities_GetSupportedAlgs_Proxy proto WINAPI \
		 _This: ptr,
	  dwBufferSize: DWORD,
	      pbBuffer: ptr DWORD,
pdwMDRequiredBufferSize: ptr DWORD

;void
IMSAdminCryptoCapabilities_GetSupportedAlgs_Stub proto WINAPI \
		 _This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

;HRESULT
IMSAdminCryptoCapabilities_SetCAList_Proxy proto WINAPI \
		 _This: ptr,
	  dwBufferSize: DWORD,
	      pbBuffer: ptr

;void
IMSAdminCryptoCapabilities_SetCAList_Stub proto WINAPI \
		 _This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

endif
endif

externdef __MIDL_itf_admex_0256_v0_0_c_ifspec:RPC_IF_HANDLE
externdef __MIDL_itf_admex_0256_v0_0_s_ifspec:RPC_IF_HANDLE

.pragma list(pop)
endif
