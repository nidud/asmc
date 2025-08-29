ifndef __REQUIRED_RPCNDR_H_VERSION__
define __REQUIRED_RPCNDR_H_VERSION__ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
define __REQUIRED_RPCSAL_H_VERSION__ 100
endif

include rpc.inc
include rpcndr.inc

ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr>
endif

ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif

ifndef __tsgpolicyengine_h__
define __tsgpolicyengine_h__

include oaidl.inc
include ocidl.inc
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

.enum AAAuthSchemes {
	AA_AUTH_MIN,
	AA_AUTH_BASIC,
	AA_AUTH_NTLM,
	AA_AUTH_SC,
	AA_AUTH_LOGGEDONCREDENTIALS,
	AA_AUTH_NEGOTIATE,
	AA_AUTH_ANY,
	AA_AUTH_COOKIE,
	AA_AUTH_DIGEST,
	AA_AUTH_ORGID,
	AA_AUTH_CONID,
	AA_AUTH_SSPI_NTLM,
	AA_AUTH_MAX
	}

.enum AAAccountingDataType {
	AA_MAIN_SESSION_CREATION,
	AA_SUB_SESSION_CREATION,
	AA_SUB_SESSION_CLOSED,
	AA_MAIN_SESSION_CLOSED
	}

AAAccountingData	struct
userName		BSTR ?
clientName		BSTR ?
authType		AAAuthSchemes ?
resourceName		BSTR ?
portNumber		sdword ?
protocolName		BSTR ?
numberOfBytesReceived	sdword ?
numberOfBytesTransfered sdword ?
reasonForDisconnect	BSTR ?
mainSessionId		GUID <>
subSessionId		sdword ?
AAAccountingData	ends


.enum SESSION_TIMEOUT_ACTION_TYPE {
	SESSION_TIMEOUT_ACTION_DISCONNECT,
	SESSION_TIMEOUT_ACTION_SILENT_REAUTH
	}

.enum PolicyAttributeType {
	EnableAllRedirections,
	DisableAllRedirections,
	DriveRedirectionDisabled,
	PrinterRedirectionDisabled,
	PortRedirectionDisabled,
	ClipboardRedirectionDisabled,
	PnpRedirectionDisabled,
	AllowOnlySDRServers
	}

define MAX_POLICY_ATTRIBUTES 20

PolicyAttributes	struct
			dd 20 dup(?)
PolicyAttributes	ends

.enum AATrustClassID {
	AA_UNTRUSTED,
	AA_TRUSTEDUSER_UNTRUSTEDCLIENT,
	AA_TRUSTEDUSER_TRUSTEDCLIENT
	}

ifndef __ITSGAuthorizeConnectionSink_INTERFACE_DEFINED__
define __ITSGAuthorizeConnectionSink_INTERFACE_DEFINED__

DEFINE_IIDX(ITSGAuthorizeConnectionSink, "c27ece33-7781-4318-98ef-1cf2da7b7005")

.comdef ITSGAuthorizeConnectionSink : public IUnknown
    OnConnectionAuthorized proc :HRESULT, :ptr, :ULONG, :ptr, :ULONG, :ULONG, :SESSION_TIMEOUT_ACTION_TYPE, :AATrustClassID, :ptr
   .ends

endif

ifndef __ITSGAuthorizeResourceSink_INTERFACE_DEFINED__
define __ITSGAuthorizeResourceSink_INTERFACE_DEFINED__

DEFINE_IIDX(ITSGAuthorizeResourceSink, "feddfcd4-fa12-4435-ae55-7ad1a9779af7")

.comdef ITSGAuthorizeResourceSink : public IUnknown
    OnChannelAuthorized proc :HRESULT, :ptr GUID, :int_t, :ptr, :ULONG, :ptr, :ULONG
   .ends

endif

ifndef __ITSGPolicyEngine_INTERFACE_DEFINED__
define __ITSGPolicyEngine_INTERFACE_DEFINED__

DEFINE_IIDX(ITSGPolicyEngine, "8bc24f08-6223-42f4-a5b4-8e37cd135bbd")

.comdef ITSGPolicyEngine : public IUnknown
    AuthorizeConnection proc :ptr, :BSTR, :AAAuthSchemes, :BSTR, :BSTR, :ptr, :ULONG, :ptr, :ULONG, :HANDLE_PTR, :ptr
    AuthorizeResource	proc :ptr, :int_t, :BSTR, :ptr, :ULONG, :ptr, :ULONG, :ULONG, :BSTR, :ptr, :ULONG, :ptr
    Refresh		proc
    IsQuarantineEnabled proc :ptr
   .ends

endif

ifndef __ITSGAccountingEngine_INTERFACE_DEFINED__
define __ITSGAccountingEngine_INTERFACE_DEFINED__

DEFINE_IIDX(ITSGAccountingEngine, "4ce2a0c9-e874-4f1a-86f4-06bbb9115338")

.comdef ITSGAccountingEngine : public IUnknown
    DoAccounting	proc :AAAccountingDataType, :ptr
   .ends

endif

endif

endif
