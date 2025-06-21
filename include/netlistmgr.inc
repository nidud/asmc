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

ifndef __netlistmgr_h__
define __netlistmgr_h__

ifndef __INetworkListManager_FWD_DEFINED__
define __INetworkListManager_FWD_DEFINED__
endif
ifndef __INetworkListManagerEvents_FWD_DEFINED__
define __INetworkListManagerEvents_FWD_DEFINED__
endif
ifndef __INetwork_FWD_DEFINED__
define __INetwork_FWD_DEFINED__
endif
ifndef __IEnumNetworks_FWD_DEFINED__
define __IEnumNetworks_FWD_DEFINED__
endif
ifndef __INetworkEvents_FWD_DEFINED__
define __INetworkEvents_FWD_DEFINED__
endif
ifndef __INetworkConnection_FWD_DEFINED__
define __INetworkConnection_FWD_DEFINED__
endif
ifndef __IEnumNetworkConnections_FWD_DEFINED__
define __IEnumNetworkConnections_FWD_DEFINED__
endif
ifndef __INetworkConnectionEvents_FWD_DEFINED__
define __INetworkConnectionEvents_FWD_DEFINED__
endif
ifndef __INetworkCostManager_FWD_DEFINED__
define __INetworkCostManager_FWD_DEFINED__
endif
ifndef __INetworkCostManagerEvents_FWD_DEFINED__
define __INetworkCostManagerEvents_FWD_DEFINED__
endif
ifndef __INetworkConnectionCost_FWD_DEFINED__
define __INetworkConnectionCost_FWD_DEFINED__
endif
ifndef __INetworkConnectionCostEvents_FWD_DEFINED__
define __INetworkConnectionCostEvents_FWD_DEFINED__
endif
ifndef __INetworkConnectionCost_FWD_DEFINED__
define __INetworkConnectionCost_FWD_DEFINED__
endif
ifndef __NetworkListManager_FWD_DEFINED__
define __NetworkListManager_FWD_DEFINED__
endif

include unknwn.inc
include objidl.inc
include oaidl.inc
include ocidl.inc

include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

define NA_DomainAuthenticationFailed  <L"NA_DomainAuthenticationFailed">
define NA_NetworkClass	<L"NA_NetworkClass">
define NA_NameSetByPolicy  <L"NA_NameSetByPolicy">
define NA_IconSetByPolicy  <L"NA_IconSetByPolicy">
define NA_DescriptionSetByPolicy  <L"NA_DescriptionSetByPolicy">
define NA_CategorySetByPolicy  <L"NA_CategorySetByPolicy">
define NA_NameReadOnly	<L"NA_NameReadOnly">
define NA_IconReadOnly	<L"NA_IconReadOnly">
define NA_DescriptionReadOnly  <L"NA_DescriptionReadOnly">
define NA_CategoryReadOnly  <L"NA_CategoryReadOnly">
define NA_AllowMerge  <L"NA_AllowMerge">
define NA_InternetConnectivityV4 <L"NA_InternetConnectivityV4">
define NA_InternetConnectivityV6 <L"NA_InternetConnectivityV6">
define	NLM_MAX_ADDRESS_LIST_SIZE	( 10 )

define	NLM_UNKNOWN_DATAPLAN_STATUS	( 0xffffffff )

.enum NLM_CONNECTION_COST {
	NLM_CONNECTION_COST_UNKNOWN	= 0,
	NLM_CONNECTION_COST_UNRESTRICTED	= 0x1,
	NLM_CONNECTION_COST_FIXED	= 0x2,
	NLM_CONNECTION_COST_VARIABLE	= 0x4,
	NLM_CONNECTION_COST_OVERDATALIMIT	= 0x10000,
	NLM_CONNECTION_COST_CONGESTED	= 0x20000,
	NLM_CONNECTION_COST_ROAMING	= 0x40000,
	NLM_CONNECTION_COST_APPROACHINGDATALIMIT	= 0x80000
    }

NLM_USAGE_DATA		struct
UsageInMegabytes	DWORD ?
LastSyncTime		FILETIME <>
NLM_USAGE_DATA		ends

NLM_DATAPLAN_STATUS	struct
InterfaceGuid		GUID <>
UsageData		NLM_USAGE_DATA <>
DataLimitInMegabytes	DWORD ?
InboundBandwidthInKbps	DWORD ?
OutboundBandwidthInKbps DWORD ?
NextBillingCycle	FILETIME <>
MaxTransferSizeInMegabytes DWORD ?
Reserved		DWORD ?
NLM_DATAPLAN_STATUS	ends

NLM_SOCKADDR		struct
data			BYTE 128 dup(?)
NLM_SOCKADDR		ends

.enum NLM_NETWORK_CLASS {
	NLM_NETWORK_IDENTIFYING = 0x1,
	NLM_NETWORK_IDENTIFIED	= 0x2,
	NLM_NETWORK_UNIDENTIFIED	= 0x3
    }

NLM_SIMULATED_PROFILE_INFO struct
ProfileName		WCHAR 256 dup(?)
cost			NLM_CONNECTION_COST ?
UsageInMegabytes	DWORD ?
DataLimitInMegabytes	DWORD ?
NLM_SIMULATED_PROFILE_INFO ends

.enum NLM_INTERNET_CONNECTIVITY {
	NLM_INTERNET_CONNECTIVITY_WEBHIJACK	= 0x1,
	NLM_INTERNET_CONNECTIVITY_PROXIED	= 0x2,
	NLM_INTERNET_CONNECTIVITY_CORPORATE	= 0x4
    }

.enum NLM_CONNECTIVITY {
	NLM_CONNECTIVITY_DISCONNECTED	= 0,
	NLM_CONNECTIVITY_IPV4_NOTRAFFIC = 0x1,
	NLM_CONNECTIVITY_IPV6_NOTRAFFIC = 0x2,
	NLM_CONNECTIVITY_IPV4_SUBNET	= 0x10,
	NLM_CONNECTIVITY_IPV4_LOCALNETWORK	= 0x20,
	NLM_CONNECTIVITY_IPV4_INTERNET	= 0x40,
	NLM_CONNECTIVITY_IPV6_SUBNET	= 0x100,
	NLM_CONNECTIVITY_IPV6_LOCALNETWORK	= 0x200,
	NLM_CONNECTIVITY_IPV6_INTERNET	= 0x400
    }

.enum NLM_DOMAIN_TYPE {
	NLM_DOMAIN_TYPE_NON_DOMAIN_NETWORK	= 0,
	NLM_DOMAIN_TYPE_DOMAIN_NETWORK	= 0x1,
	NLM_DOMAIN_TYPE_DOMAIN_AUTHENTICATED	= 0x2
    }

ifndef __INetworkListManager_INTERFACE_DEFINED__
define __INetworkListManager_INTERFACE_DEFINED__

.enum NLM_ENUM_NETWORK {
	NLM_ENUM_NETWORK_CONNECTED	= 0x1,
	NLM_ENUM_NETWORK_DISCONNECTED	= 0x2,
	NLM_ENUM_NETWORK_ALL	= 0x3
    }

DEFINE_IIDX(INetworkListManager, "DCB00000-570F-4A9B-8D69-199FDBA5723B")

.comdef INetworkListManager : public IDispatch
    GetNetworks		proc :NLM_ENUM_NETWORK, :ptr
    GetNetwork		proc :ptr, :ptr
    GetNetworkConnections proc :ptr
    GetNetworkConnection proc :ptr, :ptr
    get_IsConnectedToInternet proc :ptr
    get_IsConnected	proc :ptr
    GetConnectivity	proc :ptr
    SetSimulatedProfileInfo proc :ptr
    ClearSimulatedProfileInfo proc
   .ends

endif

ifndef __INetworkListManagerEvents_INTERFACE_DEFINED__
define __INetworkListManagerEvents_INTERFACE_DEFINED__

DEFINE_IIDX(INetworkListManagerEvents, "DCB00001-570F-4A9B-8D69-199FDBA5723B")

.comdef INetworkListManagerEvents : public IUnknown
    ConnectivityChanged proc :NLM_CONNECTIVITY
   .ends

endif

ifndef __INetwork_INTERFACE_DEFINED__
define __INetwork_INTERFACE_DEFINED__

.enum NLM_NETWORK_CATEGORY {
	NLM_NETWORK_CATEGORY_PUBLIC	= 0,
	NLM_NETWORK_CATEGORY_PRIVATE	= 0x1,
	NLM_NETWORK_CATEGORY_DOMAIN_AUTHENTICATED	= 0x2
    }

DEFINE_IIDX(INetwork, "DCB00002-570F-4A9B-8D69-199FDBA5723B")

.comdef INetwork : public IDispatch
    GetName		proc :ptr
    SetName		proc :BSTR
    GetDescription	proc :ptr
    SetDescription	proc :BSTR
    GetNetworkId	proc :ptr
    GetDomainType	proc :ptr
    GetNetworkConnections proc :ptr
    GetTimeCreatedAndConnected proc :ptr, :ptr, :ptr, :ptr
    get_IsConnectedToInternet proc :ptr
    get_IsConnected	proc :ptr
    GetConnectivity	proc :ptr
    GetCategory		proc :ptr
    SetCategory		proc :NLM_NETWORK_CATEGORY
   .ends

endif

ifndef __IEnumNetworks_INTERFACE_DEFINED__
define __IEnumNetworks_INTERFACE_DEFINED__

DEFINE_IIDX(IEnumNetworks, "DCB00003-570F-4A9B-8D69-199FDBA5723B")

.comdef IEnumNetworks : public IDispatch
    get__NewEnum	proc :ptr
    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
   .ends

endif

ifndef __INetworkEvents_INTERFACE_DEFINED__
define __INetworkEvents_INTERFACE_DEFINED__

.enum NLM_NETWORK_PROPERTY_CHANGE {
	NLM_NETWORK_PROPERTY_CHANGE_CONNECTION	= 0x1,
	NLM_NETWORK_PROPERTY_CHANGE_DESCRIPTION = 0x2,
	NLM_NETWORK_PROPERTY_CHANGE_NAME	= 0x4,
	NLM_NETWORK_PROPERTY_CHANGE_ICON	= 0x8,
	NLM_NETWORK_PROPERTY_CHANGE_CATEGORY_VALUE	= 0x10
    }

DEFINE_IIDX(INetworkEvents, "DCB00004-570F-4A9B-8D69-199FDBA5723B")

.comdef INetworkEvents : public IUnknown
    NetworkAdded	proc :ptr
    NetworkDeleted	proc :ptr
    NetworkConnectivityChanged proc :ptr, :NLM_CONNECTIVITY
    NetworkPropertyChanged proc :ptr, :NLM_NETWORK_PROPERTY_CHANGE
   .ends

endif

ifndef __INetworkConnection_INTERFACE_DEFINED__
define __INetworkConnection_INTERFACE_DEFINED__

DEFINE_IIDX(INetworkConnection, "DCB00005-570F-4A9B-8D69-199FDBA5723B")

.comdef INetworkConnection : public IDispatch
    GetNetwork		proc :ptr
    get_IsConnectedToInternet proc :ptr
    get_IsConnected	proc :ptr
    GetConnectivity	proc :ptr
    GetConnectionId	proc :ptr
    GetAdapterId	proc :ptr
    GetDomainType	proc :ptr
   .ends

endif

ifndef __IEnumNetworkConnections_INTERFACE_DEFINED__
define __IEnumNetworkConnections_INTERFACE_DEFINED__

DEFINE_IIDX(IEnumNetworkConnections, "DCB00006-570F-4A9B-8D69-199FDBA5723B")

.comdef IEnumNetworkConnections : public IDispatch
    get__NewEnum	proc :ptr
    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
   .ends

endif

ifndef __INetworkConnectionEvents_INTERFACE_DEFINED__
define __INetworkConnectionEvents_INTERFACE_DEFINED__

.enum NLM_CONNECTION_PROPERTY_CHANGE {
	NLM_CONNECTION_PROPERTY_CHANGE_AUTHENTICATION	= 0x1
    }

DEFINE_IIDX(INetworkConnectionEvents, "DCB00007-570F-4A9B-8D69-199FDBA5723B")

.comdef INetworkConnectionEvents : public IUnknown
    NetworkConnectionConnectivityChanged proc :ptr, :NLM_CONNECTIVITY
    NetworkConnectionPropertyChanged proc :ptr, :NLM_CONNECTION_PROPERTY_CHANGE
   .ends

endif

ifndef __INetworkCostManager_INTERFACE_DEFINED__
define __INetworkCostManager_INTERFACE_DEFINED__

DEFINE_IIDX(INetworkCostManager, "DCB00008-570F-4A9B-8D69-199FDBA5723B")

.comdef INetworkCostManager : public IUnknown
    GetCost		proc :ptr, :ptr
    GetDataPlanStatus	proc :ptr, :ptr
    SetDestinationAddresses proc :UINT32, :ptr, :VARIANT_BOOL
   .ends

endif

ifndef __INetworkCostManagerEvents_INTERFACE_DEFINED__
define __INetworkCostManagerEvents_INTERFACE_DEFINED__

DEFINE_IIDX(INetworkCostManagerEvents, "DCB00009-570F-4A9B-8D69-199FDBA5723B")

.comdef INetworkCostManagerEvents : public IUnknown
    CostChanged		proc :DWORD, :ptr
    DataPlanStatusChanged proc :ptr
   .ends

endif

ifndef __INetworkConnectionCost_INTERFACE_DEFINED__
define __INetworkConnectionCost_INTERFACE_DEFINED__

DEFINE_IIDX(INetworkConnectionCost, "DCB0000a-570F-4A9B-8D69-199FDBA5723B")

.comdef INetworkConnectionCost : public IUnknown
    GetCost		proc :ptr
    GetDataPlanStatus	proc :ptr
   .ends

endif

ifndef __INetworkConnectionCostEvents_INTERFACE_DEFINED__
define __INetworkConnectionCostEvents_INTERFACE_DEFINED__

DEFINE_IIDX(INetworkConnectionCostEvents, "DCB0000b-570F-4A9B-8D69-199FDBA5723B")

.comdef INetworkConnectionCostEvents : public IUnknown
    ConnectionCostChanged proc :ptr, :DWORD
    ConnectionDataPlanStatusChanged proc :ptr
   .ends

endif

ifndef __NETWORKLIST_LIBRARY_DEFINED__
define __NETWORKLIST_LIBRARY_DEFINED__

externdef LIBID_NETWORKLIST:IID

DEFINE_GUIDS(CLSID_NetworkListManager, "DCB00C01-570F-4A9B-8D69-199FDBA5723B")

endif

endif

BSTR_UserSize proto WINAPI :ptr, :dword, :ptr
BSTR_UserMarshal proto WINAPI :ptr, :ptr, :ptr
BSTR_UserUnmarshal proto WINAPI :ptr, :ptr, :ptr
BSTR_UserFree proto WINAPI :ptr, :ptr

BSTR_UserSize64 proto WINAPI :ptr, :dword, :ptr
BSTR_UserMarshal64 proto WINAPI :ptr, :ptr, :ptr
BSTR_UserUnmarshal64 proto WINAPI :ptr, :ptr, :ptr
BSTR_UserFree64 proto WINAPI :ptr, :ptr

endif
