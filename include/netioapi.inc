ifndef _NETIOAPI_H_
define _NETIOAPI_H_

ifndef _WINAPIFAMILY_
include winapifamily.inc
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

ifndef ANY_SIZE
define ANY_SIZE 1
endif

ifdef __IPHLPAPI_H__

define NETIO_STATUS DWORD
NETIO_SUCCESS macro x
  exitm<((x) eq NO_ERROR)>
  endm

else

include ws2def.inc
include ws2ipdef.inc
include ifdef.inc
include nldef.inc

define NETIO_STATUS NTSTATUS
NETIO_SUCCESS macro x
  exitm<NT_SUCCESS(x)>
  endm
define _NETIOAPI_SUCCESS_

endif ; __IPHLPAPI_H__

.enum MIB_NOTIFICATION_TYPE {
    MibParameterNotification,
    MibAddInstance,
    MibDeleteInstance,
    MibInitialNotification,
    }

endif

.pragma comment(lib, iphlpapi)

ifdef _WS2IPDEF_

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

include ntddndis.inc

MIB_IF_ROW2		struct
InterfaceLuid		NET_LUID <>
InterfaceIndex		NET_IFINDEX ?
InterfaceGuid		GUID <>
_Alias			WCHAR IF_MAX_STRING_SIZE + 1 dup(?)
Description		WCHAR IF_MAX_STRING_SIZE + 1 dup(?)
PhysicalAddressLength	ULONG ?
PhysicalAddress		UCHAR IF_MAX_PHYS_ADDRESS_LENGTH dup(?)
PermanentPhysicalAddress UCHAR IF_MAX_PHYS_ADDRESS_LENGTH dup(?)
Mtu			ULONG ?
Type			IFTYPE ?
TunnelType		TUNNEL_TYPE ?
MediaType		NDIS_MEDIUM ?
PhysicalMediumType	NDIS_PHYSICAL_MEDIUM ?
AccessType		NET_IF_ACCESS_TYPE ?
DirectionType		NET_IF_DIRECTION_TYPE ?
struct InterfaceAndOperStatusFlags
 record
  HardwareInterface	BOOLEAN :  1 ?
  FilterInterface	BOOLEAN :  1 ?
  ConnectorPresent	BOOLEAN :  1 ?
  NotAuthenticated	BOOLEAN :  1 ?
  NotMediaConnected	BOOLEAN :  1 ?
  Paused		BOOLEAN :  1 ?
  LowPower		BOOLEAN :  1 ?
  EndPointInterface	BOOLEAN :  1 ?
 ends
ends
OperStatus		IF_OPER_STATUS ?
AdminStatus		NET_IF_ADMIN_STATUS ?
MediaConnectState	NET_IF_MEDIA_CONNECT_STATE ?
NetworkGuid		NET_IF_NETWORK_GUID <>
ConnectionType		NET_IF_CONNECTION_TYPE ?
TransmitLinkSpeed	ULONG64 ?
ReceiveLinkSpeed	ULONG64 ?
InOctets		ULONG64 ?
InUcastPkts		ULONG64 ?
InNUcastPkts		ULONG64 ?
InDiscards		ULONG64 ?
InErrors		ULONG64 ?
InUnknownProtos		ULONG64 ?
InUcastOctets		ULONG64 ?
InMulticastOctets	ULONG64 ?
InBroadcastOctets	ULONG64 ?
OutOctets		ULONG64 ?
OutUcastPkts		ULONG64 ?
OutNUcastPkts		ULONG64 ?
OutDiscards		ULONG64 ?
OutErrors		ULONG64 ?
OutUcastOctets		ULONG64 ?
OutMulticastOctets	ULONG64 ?
OutBroadcastOctets	ULONG64 ?
OutQLen			ULONG64 ?
MIB_IF_ROW2		ends
PMIB_IF_ROW2		typedef ptr MIB_IF_ROW2

MIB_IF_TABLE2		struct
NumEntries		ULONG ?
Table			MIB_IF_ROW2 ANY_SIZE dup(<?>)
MIB_IF_TABLE2		ends
PMIB_IF_TABLE2		typedef ptr MIB_IF_TABLE2

GetIfEntry2 proto :PMIB_IF_ROW2

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

if (NTDDI_VERSION ge NTDDI_WIN10_RS2)

.enum MIB_IF_ENTRY_LEVEL {
    MibIfEntryNormal = 0,
    MibIfEntryNormalWithoutStatistics = 2
    }

GetIfEntry2Ex proto :MIB_IF_ENTRY_LEVEL, :PMIB_IF_ROW2

endif

GetIfTable2 proto :ptr

.enum MIB_IF_TABLE_LEVEL {
    MibIfTableNormal,
    MibIfTableRaw,
if (NTDDI_VERSION ge NTDDI_WIN10_RS2)
    MibIfTableNormalWithoutStatistics
endif
}

GetIfTable2Ex proto :MIB_IF_TABLE_LEVEL, :ptr

MIB_IPINTERFACE_ROW	struct
Family			ADDRESS_FAMILY ?
InterfaceLuid		NET_LUID <>
InterfaceIndex		NET_IFINDEX ?
MaxReassemblySize	ULONG ?
InterfaceIdentifier	ULONG64 ?
MinRouterAdvertisementInterval ULONG ?
MaxRouterAdvertisementInterval ULONG ?
AdvertisingEnabled	BOOLEAN ?
ForwardingEnabled	BOOLEAN ?
WeakHostSend		BOOLEAN ?
WeakHostReceive		BOOLEAN ?
UseAutomaticMetric	BOOLEAN ?
UseNeighborUnreachabilityDetection BOOLEAN ?
ManagedAddressConfigurationSupported BOOLEAN ?
OtherStatefulConfigurationSupported BOOLEAN ?
AdvertiseDefaultRoute	BOOLEAN ?
RouterDiscoveryBehavior NL_ROUTER_DISCOVERY_BEHAVIOR ?
DadTransmits		ULONG ?
BaseReachableTime	ULONG ?
RetransmitTime		ULONG ?
PathMtuDiscoveryTimeout ULONG ?
LinkLocalAddressBehavior NL_LINK_LOCAL_ADDRESS_BEHAVIOR ?
LinkLocalAddressTimeout ULONG ?
ZoneIndices		ULONG ScopeLevelCount dup(?)
SitePrefixLength	ULONG ?
Metric			ULONG ?
NlMtu			ULONG ?
Connected		BOOLEAN ?
SupportsWakeUpPatterns	BOOLEAN ?
SupportsNeighborDiscovery BOOLEAN ?
SupportsRouterDiscovery BOOLEAN ?
ReachableTime		ULONG ?
TransmitOffload		NL_INTERFACE_OFFLOAD_ROD <>
ReceiveOffload		NL_INTERFACE_OFFLOAD_ROD <>
DisableDefaultRoutes	BOOLEAN ?
MIB_IPINTERFACE_ROW	ends
PMIB_IPINTERFACE_ROW	typedef ptr MIB_IPINTERFACE_ROW

MIB_IPINTERFACE_TABLE	struct
NumEntries		ULONG ?
Table			MIB_IPINTERFACE_ROW ANY_SIZE dup(<?>)
MIB_IPINTERFACE_TABLE	ends
PMIB_IPINTERFACE_TABLE	typedef ptr MIB_IPINTERFACE_TABLE

MIB_IFSTACK_ROW		struct
HigherLayerInterfaceIndex NET_IFINDEX ?
LowerLayerInterfaceIndex NET_IFINDEX ?
MIB_IFSTACK_ROW		ends
PMIB_IFSTACK_ROW	typedef ptr MIB_IFSTACK_ROW

MIB_INVERTEDIFSTACK_ROW struct
LowerLayerInterfaceIndex NET_IFINDEX ?
HigherLayerInterfaceIndex NET_IFINDEX ?
MIB_INVERTEDIFSTACK_ROW ends
PMIB_INVERTEDIFSTACK_ROW typedef ptr MIB_INVERTEDIFSTACK_ROW

MIB_IFSTACK_TABLE	struct
NumEntries		ULONG ?
Table			MIB_IFSTACK_ROW ANY_SIZE dup(<?>)
MIB_IFSTACK_TABLE	ends
PMIB_IFSTACK_TABLE	typedef ptr MIB_IFSTACK_TABLE

MIB_INVERTEDIFSTACK_TABLE struct
NumEntries		ULONG ?
Table			MIB_INVERTEDIFSTACK_ROW ANY_SIZE dup(<?>)
MIB_INVERTEDIFSTACK_TABLE ends
PMIB_INVERTEDIFSTACK_TABLE typedef ptr MIB_INVERTEDIFSTACK_TABLE

CALLBACK(PIPINTERFACE_CHANGE_CALLBACK, :PVOID, :PMIB_IPINTERFACE_ROW, :MIB_NOTIFICATION_TYPE)

MIB_IP_NETWORK_CONNECTION_BANDWIDTH_ESTIMATES struct
InboundBandwidthInformation NL_BANDWIDTH_INFORMATION <>
OutboundBandwidthInformation NL_BANDWIDTH_INFORMATION <>
MIB_IP_NETWORK_CONNECTION_BANDWIDTH_ESTIMATES ends
PMIB_IP_NETWORK_CONNECTION_BANDWIDTH_ESTIMATES typedef ptr MIB_IP_NETWORK_CONNECTION_BANDWIDTH_ESTIMATES

GetIfStackTable proto :ptr
GetInvertedIfStackTable proto :ptr
GetIpInterfaceEntry proto :PMIB_IPINTERFACE_ROW
GetIpInterfaceTable proto :ADDRESS_FAMILY, :ptr
InitializeIpInterfaceEntry proto :PMIB_IPINTERFACE_ROW
NotifyIpInterfaceChange proto :ADDRESS_FAMILY, :PIPINTERFACE_CHANGE_CALLBACK, :PVOID, :BOOLEAN, :ptr
SetIpInterfaceEntry proto :PMIB_IPINTERFACE_ROW
GetIpNetworkConnectionBandwidthEstimates proto :NET_IFINDEX, :ADDRESS_FAMILY, :PMIB_IP_NETWORK_CONNECTION_BANDWIDTH_ESTIMATES

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

MIB_UNICASTIPADDRESS_ROW struct
Address			SOCKADDR_INET <>
InterfaceLuid		NET_LUID <>
InterfaceIndex		NET_IFINDEX ?
PrefixOrigin		NL_PREFIX_ORIGIN ?
SuffixOrigin		NL_SUFFIX_ORIGIN ?
ValidLifetime		ULONG ?
PreferredLifetime	ULONG ?
OnLinkPrefixLength	UINT8 ?
SkipAsSource		BOOLEAN ?
DadState		NL_DAD_STATE ?
ScopeId			SCOPE_ID <>
CreationTimeStamp	LARGE_INTEGER <>
MIB_UNICASTIPADDRESS_ROW ends
PMIB_UNICASTIPADDRESS_ROW typedef ptr MIB_UNICASTIPADDRESS_ROW

MIB_UNICASTIPADDRESS_TABLE struct
NumEntries		ULONG ?
Table			MIB_UNICASTIPADDRESS_ROW ANY_SIZE dup(<?>)
MIB_UNICASTIPADDRESS_TABLE ends
PMIB_UNICASTIPADDRESS_TABLE typedef ptr MIB_UNICASTIPADDRESS_TABLE

CALLBACK(PUNICAST_IPADDRESS_CHANGE_CALLBACK, :PVOID, :PMIB_UNICASTIPADDRESS_ROW, :MIB_NOTIFICATION_TYPE)

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

CreateUnicastIpAddressEntry proto :ptr
DeleteUnicastIpAddressEntry proto :ptr
GetUnicastIpAddressEntry proto :PMIB_UNICASTIPADDRESS_ROW

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

GetUnicastIpAddressTable proto :ADDRESS_FAMILY, :ptr

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

InitializeUnicastIpAddressEntry proto :PMIB_UNICASTIPADDRESS_ROW

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

NotifyUnicastIpAddressChange proto :ADDRESS_FAMILY, :PUNICAST_IPADDRESS_CHANGE_CALLBACK, :PVOID, :BOOLEAN, :ptr

CALLBACK(PSTABLE_UNICAST_IPADDRESS_TABLE_CALLBACK, :PVOID, :PMIB_UNICASTIPADDRESS_TABLE)

NotifyStableUnicastIpAddressTable proto :ADDRESS_FAMILY, :ptr, :PSTABLE_UNICAST_IPADDRESS_TABLE_CALLBACK, :PVOID, :ptr

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

SetUnicastIpAddressEntry proto :ptr

MIB_ANYCASTIPADDRESS_ROW struct
Address			SOCKADDR_INET <>
InterfaceLuid		NET_LUID <>
InterfaceIndex		NET_IFINDEX ?
ScopeId			SCOPE_ID <>
MIB_ANYCASTIPADDRESS_ROW ends
PMIB_ANYCASTIPADDRESS_ROW typedef ptr MIB_ANYCASTIPADDRESS_ROW

MIB_ANYCASTIPADDRESS_TABLE struct
NumEntries		ULONG ?
Table			MIB_ANYCASTIPADDRESS_ROW ANY_SIZE dup(<?>)
MIB_ANYCASTIPADDRESS_TABLE ends
PMIB_ANYCASTIPADDRESS_TABLE typedef ptr MIB_ANYCASTIPADDRESS_TABLE

CreateAnycastIpAddressEntry proto :ptr
DeleteAnycastIpAddressEntry proto :ptr
GetAnycastIpAddressEntry proto :PMIB_ANYCASTIPADDRESS_ROW
GetAnycastIpAddressTable proto :ADDRESS_FAMILY, :ptr

MIB_MULTICASTIPADDRESS_ROW struct
Address			SOCKADDR_INET <>
InterfaceIndex		NET_IFINDEX ?
InterfaceLuid		NET_LUID <>
ScopeId			SCOPE_ID <>
MIB_MULTICASTIPADDRESS_ROW ends
PMIB_MULTICASTIPADDRESS_ROW typedef ptr MIB_MULTICASTIPADDRESS_ROW

MIB_MULTICASTIPADDRESS_TABLE struct
NumEntries		ULONG ?
Table			MIB_MULTICASTIPADDRESS_ROW ANY_SIZE dup(<?>)
MIB_MULTICASTIPADDRESS_TABLE ends
PMIB_MULTICASTIPADDRESS_TABLE typedef ptr MIB_MULTICASTIPADDRESS_TABLE

GetMulticastIpAddressEntry proto :PMIB_MULTICASTIPADDRESS_ROW
GetMulticastIpAddressTable proto :ADDRESS_FAMILY, :ptr

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

IP_ADDRESS_PREFIX	struct
Prefix			SOCKADDR_INET <>
PrefixLength		UINT8 ?
IP_ADDRESS_PREFIX	ends
PIP_ADDRESS_PREFIX	typedef ptr IP_ADDRESS_PREFIX

MIB_IPFORWARD_ROW2	struct
InterfaceLuid		NET_LUID <>
InterfaceIndex		NET_IFINDEX ?
DestinationPrefix	IP_ADDRESS_PREFIX <>
NextHop			SOCKADDR_INET <>
SitePrefixLength	UCHAR ?
ValidLifetime		ULONG ?
PreferredLifetime	ULONG ?
Metric			ULONG ?
Protocol		NL_ROUTE_PROTOCOL ?
Loopback		BOOLEAN ?
AutoconfigureAddress	BOOLEAN ?
Publish			BOOLEAN ?
Immortal		BOOLEAN ?
Age			ULONG ?
Origin			NL_ROUTE_ORIGIN ?
MIB_IPFORWARD_ROW2	ends
PMIB_IPFORWARD_ROW2	typedef ptr MIB_IPFORWARD_ROW2

MIB_IPFORWARD_TABLE2	struct
NumEntries		ULONG ?
Table			MIB_IPFORWARD_ROW2 ANY_SIZE dup(<?>)
MIB_IPFORWARD_TABLE2	ends
PMIB_IPFORWARD_TABLE2	typedef ptr MIB_IPFORWARD_TABLE2

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

CALLBACK(PIPFORWARD_CHANGE_CALLBACK, :PVOID, :PMIB_IPFORWARD_ROW2, :MIB_NOTIFICATION_TYPE)

CreateIpForwardEntry2 proto :ptr
DeleteIpForwardEntry2 proto :ptr

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

GetBestRoute2 proto :ptr, :NET_IFINDEX, :ptr, :ptr, :ULONG, :PMIB_IPFORWARD_ROW2, :ptr

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

GetIpForwardEntry2 proto :PMIB_IPFORWARD_ROW2

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

GetIpForwardTable2 proto :ADDRESS_FAMILY, :ptr

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

InitializeIpForwardEntry proto :PMIB_IPFORWARD_ROW2
NotifyRouteChange2 proto :ADDRESS_FAMILY, :PIPFORWARD_CHANGE_CALLBACK, :PVOID, :BOOLEAN, :ptr
SetIpForwardEntry2 proto :ptr

MIB_IPPATH_ROW		struct
Source			SOCKADDR_INET <>
Destination		SOCKADDR_INET <>
InterfaceLuid		NET_LUID <>
InterfaceIndex		NET_IFINDEX ?
CurrentNextHop		SOCKADDR_INET <>
PathMtu			ULONG ?
RttMean			ULONG ?
RttDeviation		ULONG ?
union
 LastReachable		ULONG ?
 LastUnreachable	ULONG ?
ends
IsReachable		BOOLEAN ?
LinkTransmitSpeed	ULONG64 ?
LinkReceiveSpeed	ULONG64 ?
MIB_IPPATH_ROW		ends
PMIB_IPPATH_ROW		typedef ptr MIB_IPPATH_ROW

MIB_IPPATH_TABLE	struct
NumEntries		ULONG ?
Table			MIB_IPPATH_ROW ANY_SIZE dup(<?>)
MIB_IPPATH_TABLE	ends
PMIB_IPPATH_TABLE	typedef ptr MIB_IPPATH_TABLE

FlushIpPathTable proto :ADDRESS_FAMILY
GetIpPathEntry proto :PMIB_IPPATH_ROW
GetIpPathTable proto :ADDRESS_FAMILY, :ptr

MIB_IPNET_ROW2		struct
Address			SOCKADDR_INET <>
InterfaceIndex		NET_IFINDEX ?
InterfaceLuid		NET_LUID <>
PhysicalAddress		UCHAR IF_MAX_PHYS_ADDRESS_LENGTH dup(?)
PhysicalAddressLength	ULONG ?
State			NL_NEIGHBOR_STATE ?
union
 struct
  record
   IsRouter		BOOLEAN :  1 ?
   IsUnreachable	BOOLEAN :  1 ?
  ends
 ends
 Flags			UCHAR ?
ends
union ReachabilityTime
 LastReachable		ULONG ?
 LastUnreachable	ULONG ?
ends
MIB_IPNET_ROW2		ends
PMIB_IPNET_ROW2		typedef ptr MIB_IPNET_ROW2

MIB_IPNET_TABLE2	struct
NumEntries		ULONG ?
Table			MIB_IPNET_ROW2 ANY_SIZE dup(<?>)
MIB_IPNET_TABLE2	ends
PMIB_IPNET_TABLE2	typedef ptr MIB_IPNET_TABLE2

CreateIpNetEntry2 proto :ptr
DeleteIpNetEntry2 proto :ptr
FlushIpNetTable2 proto :ADDRESS_FAMILY, :NET_IFINDEX
GetIpNetEntry2 proto :PMIB_IPNET_ROW2
GetIpNetTable2 proto :ADDRESS_FAMILY, :ptr
ResolveIpNetEntry2 proto :PMIB_IPNET_ROW2, :ptr
SetIpNetEntry2 proto :PMIB_IPNET_ROW2

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)

define MIB_INVALID_TEREDO_PORT_NUMBER 0

CALLBACK(PTEREDO_PORT_CHANGE_CALLBACK, :PVOID, :USHORT, :MIB_NOTIFICATION_TYPE)

NotifyTeredoPortChange proto :PTEREDO_PORT_CHANGE_CALLBACK, :PVOID, :BOOLEAN, :ptr
GetTeredoPort proto :ptr

ifndef TEREDO_API_NO_DEPRECATE

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

CancelMibChangeNotify2 proto :HANDLE
FreeMibTable proto :PVOID

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

CreateSortedAddressPairs proto :PSOCKADDR_IN6, :ULONG, :PSOCKADDR_IN6, :ULONG, :ULONG, :ptr, :ptr

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

ConvertCompartmentGuidToId proto :ptr, :PNET_IF_COMPARTMENT_ID
ConvertCompartmentIdToGuid proto :NET_IF_COMPARTMENT_ID, :ptr
ConvertInterfaceNameToLuidA proto :ptr, :ptr
ConvertInterfaceNameToLuidW proto :ptr, :ptr
ConvertInterfaceLuidToNameA proto :ptr, :PSTR, :size_t
ConvertInterfaceLuidToNameW proto :ptr, :PWSTR, :size_t
ConvertInterfaceLuidToIndex proto :ptr, :PNET_IFINDEX
ConvertInterfaceIndexToLuid proto :NET_IFINDEX, :PNET_LUID
ConvertInterfaceLuidToAlias proto :ptr, :PWSTR, :size_t
ConvertInterfaceAliasToLuid proto :ptr, :PNET_LUID
ConvertInterfaceLuidToGuid proto :ptr, :ptr
ConvertInterfaceGuidToLuid proto :ptr, :PNET_LUID

define IF_NAMESIZE NDIS_IF_MAX_STRING_SIZE

if_nametoindex proto :PCSTR
if_indextoname proto :NET_IFINDEX, :PCHAR
GetCurrentThreadCompartmentId proto
SetCurrentThreadCompartmentId proto :NET_IF_COMPARTMENT_ID
GetCurrentThreadCompartmentScope proto :PNET_IF_COMPARTMENT_SCOPE, :PNET_IF_COMPARTMENT_ID
SetCurrentThreadCompartmentScope proto :NET_IF_COMPARTMENT_SCOPE
GetJobCompartmentId proto :HANDLE
SetJobCompartmentId proto :HANDLE, :NET_IF_COMPARTMENT_ID
GetSessionCompartmentId proto :ULONG
SetSessionCompartmentId proto :ULONG, :NET_IF_COMPARTMENT_ID
GetDefaultCompartmentId proto
GetNetworkInformation proto :ptr, :PNET_IF_COMPARTMENT_ID, :PULONG, :PWCHAR, :ULONG
SetNetworkInformation proto :ptr, :NET_IF_COMPARTMENT_ID, :ptr

ConvertLengthToIpv4Mask proto :ULONG, :PULONG
ConvertIpv4MaskToLength proto :ULONG, :PUINT8

define DNS_SETTINGS_VERSION1			 0x0001
define DNS_INTERFACE_SETTINGS_VERSION1		 0x0001
define DNS_INTERFACE_SETTINGS_VERSION2		 0x0002

define DNS_SETTING_IPV6				 0x0001
define DNS_SETTING_NAMESERVER			 0x0002
define DNS_SETTING_SEARCHLIST			 0x0004
define DNS_SETTING_REGISTRATION_ENABLED		 0x0008
define DNS_SETTING_REGISTER_ADAPTER_NAME	 0x0010
define DNS_SETTING_DOMAIN			 0x0020
define DNS_SETTING_HOSTNAME			 0x0040
define DNS_SETTINGS_ENABLE_LLMNR		 0x0080
define DNS_SETTINGS_QUERY_ADAPTER_NAME		 0x0100
define DNS_SETTING_PROFILE_NAMESERVER		 0x0200
define DNS_SETTING_DISABLE_UNCONSTRAINED_QUERIES 0x0400
define DNS_SETTING_SUPPLEMENTAL_SEARCH_LIST	 0x0800

DNS_SETTINGS		struct
Version			ULONG ?
Flags			ULONG64 ?
Hostname		PWSTR ?
Domain			PWSTR ?
SearchList		PWSTR ?
DNS_SETTINGS		ends

DNS_INTERFACE_SETTINGS	struct
Version			ULONG ?
Flags			ULONG64 ?
Domain			PWSTR ?
NameServer		PWSTR ?
SearchList		PWSTR ?
RegistrationEnabled	ULONG ?
RegisterAdapterName	ULONG ?
EnableLLMNR		ULONG ?
QueryAdapterName	ULONG ?
ProfileNameServer	PWSTR ?
DNS_INTERFACE_SETTINGS	ends

DNS_INTERFACE_SETTINGS_EX struct
SettingsV1		DNS_INTERFACE_SETTINGS <>
DisableUnconstrainedQueries ULONG ?
SupplementalSearchList	PWSTR ?
DNS_INTERFACE_SETTINGS_EX ends

GetDnsSettings proto :ptr
FreeDnsSettings proto :ptr
SetDnsSettings proto :ptr
GetInterfaceDnsSettings proto :GUID, :ptr
FreeInterfaceDnsSettings proto :ptr
SetInterfaceDnsSettings proto :GUID, :ptr
GetNetworkConnectivityHint proto :ptr
GetNetworkConnectivityHintForInterface proto :NET_IFINDEX, :ptr
CALLBACK(PNETWORK_CONNECTIVITY_HINT_CHANGE_CALLBACK, :PVOID, :NL_NETWORK_CONNECTIVITY_HINT)
NotifyNetworkConnectivityHintChange proto :PNETWORK_CONNECTIVITY_HINT_CHANGE_CALLBACK, :PVOID, :BOOLEAN, :PHANDLE

endif

endif
