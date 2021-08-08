ifndef __REQUIRED_RPCNDR_H_VERSION__
define __REQUIRED_RPCNDR_H_VERSION__ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
define __REQUIRED_RPCSAL_H_VERSION__ 100
endif

include rpc.inc
include rpcndr.inc

ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr.inc>
endif

ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif

ifndef __netfw_h__
define __netfw_h__

include icftypes.inc
include oaidl.inc
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

;HRESULT
NetworkIsolationSetupAppContainerBinaries proto WINAPI \
applicationContainerSid: PSID,
       packageFullName: LPCWSTR,
	 packageFolder: LPCWSTR,
	   displayName: LPCWSTR,
bBinariesFullyComputed: BOOL,
	      binaries: ptr LPCWSTR,
	 binariesCount: DWORD

ifndef __NET_ISOLATION_TYPES__
define __NET_ISOLATION_TYPES__

.enum NETISO_FLAG {
    NETISO_FLAG_FORCE_COMPUTE_BINARIES = 0x1,
    NETISO_FLAG_MAX = 0x2
    }

.enum INET_FIREWALL_AC_CREATION_TYPE {
    INET_FIREWALL_AC_NONE		= 0x00,
    INET_FIREWALL_AC_PACKAGE_ID_ONLY	= 0x01,
    INET_FIREWALL_AC_BINARY		= 0x02,
    INET_FIREWALL_AC_MAX		= 0x04
    }

.enum INET_FIREWALL_AC_CHANGE_TYPE {
    INET_FIREWALL_AC_CHANGE_INVALID	= 0,
    INET_FIREWALL_AC_CHANGE_CREATE	= 1,
    INET_FIREWALL_AC_CHANGE_DELETE	= 2,
    INET_FIREWALL_AC_CHANGE_MAX		= 3
    }


INET_FIREWALL_AC_CAPABILITIES STRUC
count			dd ?
capabilities		ptr SID_AND_ATTRIBUTES ?
INET_FIREWALL_AC_CAPABILITIES ENDS
PINET_FIREWALL_AC_CAPABILITIES typedef ptr INET_FIREWALL_AC_CAPABILITIES


INET_FIREWALL_AC_BINARIES STRUC
count			dd ?
binaries		ptr LPWSTR ?
INET_FIREWALL_AC_BINARIES ENDS
PINET_FIREWALL_AC_BINARIES typedef ptr INET_FIREWALL_AC_BINARIES


INET_FIREWALL_AC_CHANGE STRUC
changeType		INET_FIREWALL_AC_CHANGE_TYPE ?
createType		INET_FIREWALL_AC_CREATION_TYPE ?
appContainerSid		ptr SID ?
userSid			ptr SID ?
displayName		LPWSTR ?
UNION
 capabilities		INET_FIREWALL_AC_CAPABILITIES <>
 binaries		INET_FIREWALL_AC_BINARIES <>
ENDS
INET_FIREWALL_AC_CHANGE ENDS
PINET_FIREWALL_AC_CHANGE typedef ptr INET_FIREWALL_AC_CHANGE

INET_FIREWALL_APP_CONTAINER STRUC
appContainerSid		ptr SID ?
userSid			ptr SID ?
appContainerName	LPWSTR ?
displayName		LPWSTR ?
description		LPWSTR ?
capabilities		INET_FIREWALL_AC_CAPABILITIES <>
binaries		INET_FIREWALL_AC_BINARIES <>
workingDirectory	LPWSTR ?
packageFullName		LPWSTR ?
INET_FIREWALL_APP_CONTAINER ENDS
PINET_FIREWALL_APP_CONTAINER typedef ptr INET_FIREWALL_APP_CONTAINER

endif ; __NET_ISOLATION_TYPES__

CALLBACK(PAC_CHANGES_CALLBACK_FN, :ptr, :ptr)
;DWORD
NetworkIsolationRegisterForAppContainerChanges proto WINAPI \
		 flags: DWORD,
	      callback: PAC_CHANGES_CALLBACK_FN,
	       context: PVOID,
    registrationObject: ptr HANDLE

;DWORD
NetworkIsolationUnregisterForAppContainerChanges proto WINAPI \
    registrationObject: HANDLE

;HRESULT
NetworkIsolationEnumerateAppContainerRules proto WINAPI \
	       newEnum: ptr IEnumVARIANT


;DWORD
NetworkIsolationFreeAppContainers proto WINAPI \
	  pPublicAppCs: PINET_FIREWALL_APP_CONTAINER


;DWORD
NetworkIsolationEnumAppContainers proto WINAPI \
		 Flags: DWORD,
     pdwNumPublicAppCs: ptr DWORD,
	 ppPublicAppCs: ptr PINET_FIREWALL_APP_CONTAINER

;DWORD
NetworkIsolationGetAppContainerConfig proto WINAPI \
     pdwNumPublicAppCs: ptr DWORD,
      appContainerSids: ptr PSID_AND_ATTRIBUTES

;DWORD
NetworkIsolationSetAppContainerConfig proto WINAPI \
      dwNumPublicAppCs: DWORD,
      appContainerSids: PSID_AND_ATTRIBUTES

ifndef __NET_ISOLATION_DIAG_TYPES__
define __NET_ISOLATION_DIAG_TYPES__
.enum NETISO_ERROR_TYPE {
    NETISO_ERROR_TYPE_NONE			= 0x00,
    NETISO_ERROR_TYPE_PRIVATE_NETWORK		= 0x01,
    NETISO_ERROR_TYPE_INTERNET_CLIENT		= 0x02,
    NETISO_ERROR_TYPE_INTERNET_CLIENT_SERVER	= 0x03,
    NETISO_ERROR_TYPE_MAX			= 0x04
    }
endif

;DWORD
NetworkIsolationDiagnoseConnectFailureAndGetInfo proto WINAPI \
	 wszServerName: LPCWSTR,
	   netIsoError: ptr NETISO_ERROR_TYPE

ifndef __INetFwRemoteAdminSettings_INTERFACE_DEFINED__
define __INetFwRemoteAdminSettings_INTERFACE_DEFINED__

DEFINE_IIDX(INetFwRemoteAdminSettings, "D4BECDDF-6F73-4A83-B832-9C66874CD20E")

.comdef INetFwRemoteAdminSettings : public IDispatch

    get_IpVersion	proc :ptr
    put_IpVersion	proc :NET_FW_IP_VERSION
    get_Scope		proc :ptr
    put_Scope		proc :NET_FW_SCOPE
    get_RemoteAddresses proc :ptr
    put_RemoteAddresses proc :BSTR
    get_Enabled		proc :ptr
    put_Enabled		proc :VARIANT_BOOL
   .ends

endif

ifndef __INetFwIcmpSettings_INTERFACE_DEFINED__
define __INetFwIcmpSettings_INTERFACE_DEFINED__

DEFINE_IIDX(INetFwIcmpSettings, "A6207B2E-7CDD-426A-951E-5E1CBC5AFEAD")

.comdef INetFwIcmpSettings : public IDispatch

    get_AllowOutboundDestinationUnreachable proc :ptr
    put_AllowOutboundDestinationUnreachable proc :VARIANT_BOOL
    get_AllowRedirect	proc :ptr
    put_AllowRedirect	proc :VARIANT_BOOL
    get_AllowInboundEchoRequest proc :ptr
    put_AllowInboundEchoRequest proc :VARIANT_BOOL
    get_AllowOutboundTimeExceeded proc :ptr
    put_AllowOutboundTimeExceeded proc :VARIANT_BOOL
    get_AllowOutboundParameterProblem proc :ptr
    put_AllowOutboundParameterProblem proc :VARIANT_BOOL
    get_AllowOutboundSourceQuench proc :ptr
    put_AllowOutboundSourceQuench proc :VARIANT_BOOL
    get_AllowInboundRouterRequest proc :ptr
    put_AllowInboundRouterRequest proc :VARIANT_BOOL
    get_AllowInboundTimestampRequest proc :ptr
    put_AllowInboundTimestampRequest proc :VARIANT_BOOL
    get_AllowInboundMaskRequest proc :ptr
    put_AllowInboundMaskRequest proc :VARIANT_BOOL
    get_AllowOutboundPacketTooBig proc :ptr
    put_AllowOutboundPacketTooBig proc :VARIANT_BOOL
   .ends

endif

ifndef __INetFwOpenPort_INTERFACE_DEFINED__
define __INetFwOpenPort_INTERFACE_DEFINED__

DEFINE_IIDX(INetFwOpenPort, "E0483BA0-47FF-4D9C-A6D6-7741D0B195F7")

.comdef INetFwOpenPort : public IDispatch

    get_Name		proc :ptr
    put_Name		proc :BSTR
    get_IpVersion	proc :ptr
    put_IpVersion	proc :NET_FW_IP_VERSION
    get_Protocol	proc :ptr
    put_Protocol	proc :NET_FW_IP_PROTOCOL
    get_Port		proc :ptr
    put_Port		proc :LONG
    get_Scope		proc :ptr
    put_Scope		proc :NET_FW_SCOPE
    get_RemoteAddresses proc :ptr
    put_RemoteAddresses proc :BSTR
    get_Enabled		proc :ptr
    put_Enabled		proc :VARIANT_BOOL
    get_BuiltIn		proc :ptr
   .ends

endif

ifndef __INetFwOpenPorts_INTERFACE_DEFINED__
define __INetFwOpenPorts_INTERFACE_DEFINED__

DEFINE_IIDX(INetFwOpenPorts, "C0E9D7FA-E07E-430A-B19A-090CE82D92E2")

.comdef INetFwOpenPorts : public IDispatch

    get_Count		proc :ptr
    _Add		proc :ptr
    Remove		proc :LONG, :NET_FW_IP_PROTOCOL
    Item		proc :LONG, :NET_FW_IP_PROTOCOL, :ptr
    get__NewEnum	proc :ptr
   .ends

endif

ifndef __INetFwService_INTERFACE_DEFINED__
define __INetFwService_INTERFACE_DEFINED__

DEFINE_IIDX(INetFwService, "79FD57C8-908E-4A36-9888-D5B3F0A444CF")

.comdef INetFwService : public IDispatch

    get_Name		proc :ptr
    get_Type		proc :ptr
    get_Customized	proc :ptr
    get_IpVersion	proc :ptr
    put_IpVersion	proc :NET_FW_IP_VERSION
    get_Scope		proc :ptr
    put_Scope		proc :NET_FW_SCOPE
    get_RemoteAddresses proc :ptr
    put_RemoteAddresses proc :BSTR
    get_Enabled		proc :ptr
    put_Enabled		proc :VARIANT_BOOL
    get_GloballyOpenPorts proc :ptr
   .ends

endif

ifndef __INetFwServices_INTERFACE_DEFINED__
define __INetFwServices_INTERFACE_DEFINED__

DEFINE_IIDX(INetFwServices, "79649BB4-903E-421B-94C9-79848E79F6EE")

.comdef INetFwServices : public IDispatch

    get_Count		proc :ptr
    Item		proc :NET_FW_SERVICE_TYPE, :ptr
    get__NewEnum	proc :ptr
   .ends

endif

ifndef __INetFwAuthorizedApplication_INTERFACE_DEFINED__
define __INetFwAuthorizedApplication_INTERFACE_DEFINED__

DEFINE_IIDX(INetFwAuthorizedApplication, "B5E64FFA-C2C5-444E-A301-FB5E00018050")

.comdef INetFwAuthorizedApplication : public IDispatch

    get_Name		proc :ptr
    put_Name		proc :BSTR
    get_ProcessImageFileName proc :ptr
    put_ProcessImageFileName proc :BSTR
    get_IpVersion	proc :ptr
    put_IpVersion	proc :NET_FW_IP_VERSION
    get_Scope		proc :ptr
    put_Scope		proc :NET_FW_SCOPE
    get_RemoteAddresses proc :ptr
    put_RemoteAddresses proc :BSTR
    get_Enabled		proc :ptr
    put_Enabled		proc :VARIANT_BOOL
   .ends

endif

ifndef __INetFwAuthorizedApplications_INTERFACE_DEFINED__
define __INetFwAuthorizedApplications_INTERFACE_DEFINED__

DEFINE_IIDX(INetFwAuthorizedApplications, "644EFD52-CCF9-486C-97A2-39F352570B30")

.comdef INetFwAuthorizedApplications : public IDispatch

    get_Count		proc :ptr
    _Add		proc :ptr
    Remove		proc :BSTR
    Item		proc :BSTR, :ptr
    get__NewEnum	proc :ptr
   .ends

endif

ifndef __INetFwRule_INTERFACE_DEFINED__
define __INetFwRule_INTERFACE_DEFINED__

DEFINE_IIDX(INetFwRule, "AF230D27-BABA-4E42-ACED-F524F22CFCE2")

.comdef INetFwRule : public IDispatch

    get_Name		proc :ptr
    put_Name		proc :BSTR
    get_Description	proc :ptr
    put_Description	proc :BSTR
    get_ApplicationName proc :ptr
    put_ApplicationName proc :BSTR
    get_ServiceName	proc :ptr
    put_ServiceName	proc :BSTR
    get_Protocol	proc :ptr
    put_Protocol	proc :LONG
    get_LocalPorts	proc :ptr
    put_LocalPorts	proc :BSTR
    get_RemotePorts	proc :ptr
    put_RemotePorts	proc :BSTR
    get_LocalAddresses	proc :ptr
    put_LocalAddresses	proc :BSTR
    get_RemoteAddresses proc :ptr
    put_RemoteAddresses proc :BSTR
    get_IcmpTypesAndCodes proc :ptr
    put_IcmpTypesAndCodes proc :BSTR
    get_Direction	proc :ptr
    put_Direction	proc :NET_FW_RULE_DIRECTION
    get_Interfaces	proc :ptr
    put_Interfaces	proc :VARIANT
    get_InterfaceTypes	proc :ptr
    put_InterfaceTypes	proc :BSTR
    get_Enabled		proc :ptr
    put_Enabled		proc :VARIANT_BOOL
    get_Grouping	proc :ptr
    put_Grouping	proc :BSTR
    get_Profiles	proc :ptr
    put_Profiles	proc :LONG
    get_EdgeTraversal	proc :ptr
    put_EdgeTraversal	proc :VARIANT_BOOL
    get_Action		proc :ptr
    put_Action		proc :NET_FW_ACTION
   .ends

endif

ifndef __INetFwRule2_INTERFACE_DEFINED__
define __INetFwRule2_INTERFACE_DEFINED__

DEFINE_IIDX(INetFwRule2, "9C27C8DA-189B-4DDE-89F7-8B39A316782C")

.comdef INetFwRule2 : public INetFwRule

    get_EdgeTraversalOptions proc :ptr
    put_EdgeTraversalOptions proc :LONG
   .ends

endif

ifndef __INetFwRule3_INTERFACE_DEFINED__
define __INetFwRule3_INTERFACE_DEFINED__

DEFINE_IIDX(INetFwRule3, "B21563FF-D696-4222-AB46-4E89B73AB34A")

.comdef INetFwRule3 : public INetFwRule2

    get_LocalAppPackageId proc :ptr
    put_LocalAppPackageId proc :BSTR
    get_LocalUserOwner	proc :ptr
    put_LocalUserOwner	proc :BSTR
    get_LocalUserAuthorizedList proc :ptr
    put_LocalUserAuthorizedList proc :BSTR
    get_RemoteUserAuthorizedList proc :ptr
    put_RemoteUserAuthorizedList proc :BSTR
    get_RemoteMachineAuthorizedList proc :ptr
    put_RemoteMachineAuthorizedList proc :BSTR
    get_SecureFlags	proc :ptr
    put_SecureFlags	proc :LONG
   .ends

endif

ifndef __INetFwRules_INTERFACE_DEFINED__
define __INetFwRules_INTERFACE_DEFINED__

DEFINE_IIDX(INetFwRules, "9C4C6277-5027-441E-AFAE-CA1F542DA009")

.comdef INetFwRules : public IDispatch

    get_Count		proc :ptr
    _Add		proc :ptr
    Remove		proc :BSTR
    Item		proc :BSTR, :ptr
    get__NewEnum	proc :ptr
   .ends

endif

ifndef __INetFwServiceRestriction_INTERFACE_DEFINED__
define __INetFwServiceRestriction_INTERFACE_DEFINED__

DEFINE_IIDX(INetFwServiceRestriction, "8267BBE3-F890-491C-B7B6-2DB1EF0E5D2B")

.comdef INetFwServiceRestriction : public IDispatch

    RestrictService	proc :BSTR, :BSTR, :VARIANT_BOOL, :VARIANT_BOOL
    ServiceRestricted	proc :BSTR, :BSTR, :ptr
    get_Rules		proc :ptr
   .ends

endif

ifndef __INetFwProfile_INTERFACE_DEFINED__
define __INetFwProfile_INTERFACE_DEFINED__

DEFINE_IIDX(INetFwProfile, "174A0DDA-E9F9-449D-993B-21AB667CA456")

.comdef INetFwProfile : public IDispatch

    get_Type		proc :ptr
    get_FirewallEnabled proc :ptr
    put_FirewallEnabled proc :VARIANT_BOOL
    get_ExceptionsNotAllowed proc :ptr
    put_ExceptionsNotAllowed proc :VARIANT_BOOL
    get_NotificationsDisabled proc :ptr
    put_NotificationsDisabled proc :VARIANT_BOOL
    get_UnicastResponsesToMulticastBroadcastDisabled proc :ptr
    put_UnicastResponsesToMulticastBroadcastDisabled proc :VARIANT_BOOL
    get_RemoteAdminSettings proc :ptr
    get_IcmpSettings	proc :ptr
    get_GloballyOpenPorts proc :ptr
    get_Services	proc :ptr
    get_AuthorizedApplications proc :ptr
   .ends

endif

ifndef __INetFwPolicy_INTERFACE_DEFINED__
define __INetFwPolicy_INTERFACE_DEFINED__

DEFINE_IIDX(INetFwPolicy, "D46D2478-9AC9-4008-9DC7-5563CE5536CC")

.comdef INetFwPolicy : public IDispatch

    get_CurrentProfile	proc :ptr
    GetProfileByType	proc :NET_FW_PROFILE_TYPE, :ptr
   .ends

endif

ifndef __INetFwPolicy2_INTERFACE_DEFINED__
define __INetFwPolicy2_INTERFACE_DEFINED__

DEFINE_IIDX(INetFwPolicy2, "98325047-C671-4174-8D81-DEFCD3F03186")

.comdef INetFwPolicy2 : public IDispatch

    get_CurrentProfileTypes proc :ptr
    get_FirewallEnabled proc :NET_FW_PROFILE_TYPE2, :ptr
    put_FirewallEnabled proc :NET_FW_PROFILE_TYPE2, :VARIANT_BOOL
    get_ExcludedInterfaces proc :NET_FW_PROFILE_TYPE2, :ptr
    put_ExcludedInterfaces proc :NET_FW_PROFILE_TYPE2, :VARIANT
    get_BlockAllInboundTraffic proc :NET_FW_PROFILE_TYPE2, :ptr
    put_BlockAllInboundTraffic proc :NET_FW_PROFILE_TYPE2, :VARIANT_BOOL
    get_NotificationsDisabled proc :NET_FW_PROFILE_TYPE2, :ptr
    put_NotificationsDisabled proc :NET_FW_PROFILE_TYPE2, :VARIANT_BOOL
    get_UnicastResponsesToMulticastBroadcastDisabled proc :NET_FW_PROFILE_TYPE2, :ptr
    put_UnicastResponsesToMulticastBroadcastDisabled proc :NET_FW_PROFILE_TYPE2, :VARIANT_BOOL
    get_Rules		proc :ptr
    get_ServiceRestriction proc :ptr
    EnableRuleGroup	proc :LONG, :BSTR, :VARIANT_BOOL
    IsRuleGroupEnabled	proc :LONG, :BSTR, :ptr
    RestoreLocalFirewallDefaults proc
    get_DefaultInboundAction proc :NET_FW_PROFILE_TYPE2, :ptr
    put_DefaultInboundAction proc :NET_FW_PROFILE_TYPE2, :NET_FW_ACTION
    get_DefaultOutboundAction proc :NET_FW_PROFILE_TYPE2, :ptr
    put_DefaultOutboundAction proc :NET_FW_PROFILE_TYPE2, :NET_FW_ACTION
    get_IsRuleGroupCurrentlyEnabled proc :BSTR, :ptr
    get_LocalPolicyModifyState proc :ptr
   .ends

endif

ifndef __INetFwMgr_INTERFACE_DEFINED__
define __INetFwMgr_INTERFACE_DEFINED__

DEFINE_IIDX(INetFwMgr, "F7898AF5-CAC4-4632-A2EC-DA06E5111AF2")

.comdef INetFwMgr : public IDispatch

    get_LocalPolicy	proc :ptr
    get_CurrentProfileType proc :ptr
    RestoreDefaults	proc
    IsPortAllowed	proc :BSTR, :NET_FW_IP_VERSION, :LONG, :BSTR, :NET_FW_IP_PROTOCOL, :ptr, :ptr
    IsIcmpTypeAllowed	proc :NET_FW_IP_VERSION, :BSTR, :BYTE, :ptr, :ptr
   .ends

endif

ifndef __INetFwProduct_INTERFACE_DEFINED__
define __INetFwProduct_INTERFACE_DEFINED__

DEFINE_IIDX(INetFwProduct, "71881699-18f4-458b-b892-3ffce5e07f75")

.comdef INetFwProduct : public IDispatch

    get_RuleCategories	proc :ptr
    put_RuleCategories	proc :VARIANT
    get_DisplayName	proc :ptr
    put_DisplayName	proc :BSTR
    get_PathToSignedProductExe proc :ptr
   .ends

endif

ifndef __INetFwProducts_INTERFACE_DEFINED__
define __INetFwProducts_INTERFACE_DEFINED__

DEFINE_IIDX(INetFwProducts, "39EB36E0-2097-40BD-8AF2-63A13B525362")

.comdef INetFwProducts : public IDispatch

    get_Count		proc :ptr
    Register		proc :ptr, :ptr
    Item		proc :LONG, :ptr
    get__NewEnum	proc :ptr
   .ends

endif

ifndef __NetFwPublicTypeLib_LIBRARY_DEFINED__
define __NetFwPublicTypeLib_LIBRARY_DEFINED__

externdef LIBID_NetFwPublicTypeLib:IID

DEFINE_GUIDS(CLSID_NetFwRule, "2C5BC43E-3369-4C33-AB0C-BE9469677AF4")
DEFINE_GUIDS(CLSID_NetFwOpenPort, "0CA545C6-37AD-4A6C-BF92-9F7610067EF5")
DEFINE_GUIDS(CLSID_NetFwAuthorizedApplication, "EC9846B3-2762-4A6B-A214-6ACB603462D2")
DEFINE_GUIDS(CLSID_NetFwPolicy2, "E2B3C97F-6AE1-41AC-817A-F6F92166D7DD")
DEFINE_GUIDS(CLSID_NetFwProduct, "9D745ED8-C514-4D1D-BF42-751FED2D5AC7")
DEFINE_GUIDS(CLSID_NetFwProducts, "CC19079B-8272-4D73-BB70-CDB533527B61")
DEFINE_GUIDS(CLSID_NetFwMgr, "304CE942-6E39-40D8-943A-B913C40C9CD4")

endif

endif ; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
endif
