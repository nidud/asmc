ifndef IP_TYPES_INCLUDED
define IP_TYPES_INCLUDED

include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

include time.inc
include ifdef.inc
include nldef.inc

define MAX_ADAPTER_DESCRIPTION_LENGTH  128
define MAX_ADAPTER_NAME_LENGTH         256
define MAX_ADAPTER_ADDRESS_LENGTH      8
define DEFAULT_MINIMUM_ENTITIES        32
define MAX_HOSTNAME_LEN                128
define MAX_DOMAIN_NAME_LEN             128
define MAX_SCOPE_ID_LEN                256
define MAX_DHCPV6_DUID_LENGTH          130
define MAX_DNS_SUFFIX_STRING_LENGTH    256

define BROADCAST_NODETYPE              1
define PEER_TO_PEER_NODETYPE           2
define MIXED_NODETYPE                  4
define HYBRID_NODETYPE                 8

IP_ADDRESS_STRING       struct
String                  sbyte 4 * 4 dup(?)
IP_ADDRESS_STRING       ends
PIP_ADDRESS_STRING      typedef ptr IP_ADDRESS_STRING
IP_MASK_STRING          typedef IP_ADDRESS_STRING
PIP_MASK_STRING         typedef ptr IP_ADDRESS_STRING

_IP_ADDR_STRING         struct
Next                    ptr _IP_ADDR_STRING ?
IpAddress               IP_ADDRESS_STRING <>
IpMask                  IP_MASK_STRING <>
Context                 DWORD ?
_IP_ADDR_STRING         ends
IP_ADDR_STRING          typedef _IP_ADDR_STRING
PIP_ADDR_STRING         typedef ptr _IP_ADDR_STRING

_IP_ADAPTER_INFO        struct
Next                    ptr _IP_ADAPTER_INFO ?
ComboIndex              DWORD ?
AdapterName             sbyte MAX_ADAPTER_NAME_LENGTH + 4 dup(?)
Description             sbyte MAX_ADAPTER_DESCRIPTION_LENGTH + 4 dup(?)
AddressLength           UINT ?
Address                 BYTE MAX_ADAPTER_ADDRESS_LENGTH dup(?)
Index                   DWORD ?
Type                    UINT ?
DhcpEnabled             UINT ?
CurrentIpAddress        PIP_ADDR_STRING ?
IpAddressList           IP_ADDR_STRING <>
GatewayList             IP_ADDR_STRING <>
DhcpServer              IP_ADDR_STRING <>
HaveWins                BOOL ?
PrimaryWinsServer       IP_ADDR_STRING <>
SecondaryWinsServer     IP_ADDR_STRING <>
LeaseObtained           time_t ?
LeaseExpires            time_t ?
_IP_ADAPTER_INFO        ends
IP_ADAPTER_INFO         typedef _IP_ADAPTER_INFO
PIP_ADAPTER_INFO        typedef ptr _IP_ADAPTER_INFO

ifdef _WINSOCK2API_

IP_PREFIX_ORIGIN        typedef NL_PREFIX_ORIGIN
IP_SUFFIX_ORIGIN        typedef NL_SUFFIX_ORIGIN
IP_DAD_STATE            typedef NL_DAD_STATE

_IP_ADAPTER_UNICAST_ADDRESS_LH struct
union
 Alignment              ULONGLONG ?
 struct
  Length                ULONG ?
  Flags                 DWORD ?
 ends
ends
Next                    ptr _IP_ADAPTER_UNICAST_ADDRESS_LH ?
Address                 SOCKET_ADDRESS <>
PrefixOrigin            IP_PREFIX_ORIGIN ?
SuffixOrigin            IP_SUFFIX_ORIGIN ?
DadState                IP_DAD_STATE ?
ValidLifetime           ULONG ?
PreferredLifetime       ULONG ?
LeaseLifetime           ULONG ?
OnLinkPrefixLength      UINT8 ?
_IP_ADAPTER_UNICAST_ADDRESS_LH ends
IP_ADAPTER_UNICAST_ADDRESS_LH typedef _IP_ADAPTER_UNICAST_ADDRESS_LH
PIP_ADAPTER_UNICAST_ADDRESS_LH typedef ptr _IP_ADAPTER_UNICAST_ADDRESS_LH

_IP_ADAPTER_UNICAST_ADDRESS_XP struct
union
 Alignment              ULONGLONG ?
 struct
  Length                ULONG ?
  Flags                 DWORD ?
 ends
ends
Next                    ptr _IP_ADAPTER_UNICAST_ADDRESS_XP ?
Address                 SOCKET_ADDRESS <>
PrefixOrigin            IP_PREFIX_ORIGIN ?
SuffixOrigin            IP_SUFFIX_ORIGIN ?
DadState                IP_DAD_STATE ?
ValidLifetime           ULONG ?
PreferredLifetime       ULONG ?
LeaseLifetime           ULONG ?
_IP_ADAPTER_UNICAST_ADDRESS_XP ends
IP_ADAPTER_UNICAST_ADDRESS_XP typedef _IP_ADAPTER_UNICAST_ADDRESS_XP
PIP_ADAPTER_UNICAST_ADDRESS_XP typedef ptr _IP_ADAPTER_UNICAST_ADDRESS_XP

if (NTDDI_VERSION ge NTDDI_VISTA)
IP_ADAPTER_UNICAST_ADDRESS typedef IP_ADAPTER_UNICAST_ADDRESS_LH
PIP_ADAPTER_UNICAST_ADDRESS typedef ptr IP_ADAPTER_UNICAST_ADDRESS_LH
elseif (NTDDI_VERSION ge NTDDI_WINXP)
IP_ADAPTER_UNICAST_ADDRESS typedef IP_ADAPTER_UNICAST_ADDRESS_XP
PIP_ADAPTER_UNICAST_ADDRESS typedef ptr IP_ADAPTER_UNICAST_ADDRESS_XP
endif

define IP_ADAPTER_ADDRESS_DNS_ELIGIBLE 0x01
define IP_ADAPTER_ADDRESS_TRANSIENT    0x02

_IP_ADAPTER_ANYCAST_ADDRESS_XP struct
union
 Alignment              ULONGLONG ?
 struct
  Length                ULONG ?
  Flags                 DWORD ?
 ends
ends
Next                    ptr _IP_ADAPTER_ANYCAST_ADDRESS_XP ?
Address                 SOCKET_ADDRESS <>
_IP_ADAPTER_ANYCAST_ADDRESS_XP ends
IP_ADAPTER_ANYCAST_ADDRESS_XP typedef _IP_ADAPTER_ANYCAST_ADDRESS_XP
PIP_ADAPTER_ANYCAST_ADDRESS_XP typedef ptr _IP_ADAPTER_ANYCAST_ADDRESS_XP
if (NTDDI_VERSION ge NTDDI_WINXP)
IP_ADAPTER_ANYCAST_ADDRESS typedef IP_ADAPTER_ANYCAST_ADDRESS_XP
PIP_ADAPTER_ANYCAST_ADDRESS typedef ptr IP_ADAPTER_ANYCAST_ADDRESS_XP
endif

_IP_ADAPTER_MULTICAST_ADDRESS_XP struct
union
 Alignment              ULONGLONG ?
 struct
  Length                ULONG ?
  Flags                 DWORD ?
 ends
ends
Next                    ptr _IP_ADAPTER_MULTICAST_ADDRESS_XP ?
Address                 SOCKET_ADDRESS <>
_IP_ADAPTER_MULTICAST_ADDRESS_XP ends
IP_ADAPTER_MULTICAST_ADDRESS_XP typedef _IP_ADAPTER_MULTICAST_ADDRESS_XP
PIP_ADAPTER_MULTICAST_ADDRESS_XP typedef ptr _IP_ADAPTER_MULTICAST_ADDRESS_XP
if (NTDDI_VERSION ge NTDDI_WINXP)
IP_ADAPTER_MULTICAST_ADDRESS typedef IP_ADAPTER_MULTICAST_ADDRESS_XP
PIP_ADAPTER_MULTICAST_ADDRESS typedef ptr IP_ADAPTER_MULTICAST_ADDRESS_XP
endif

_IP_ADAPTER_DNS_SERVER_ADDRESS_XP struct
union
 Alignment              ULONGLONG ?
 struct
  Length                ULONG ?
  Reserved              DWORD ?
 ends
ends
Next                    ptr _IP_ADAPTER_DNS_SERVER_ADDRESS_XP ?
Address                 SOCKET_ADDRESS <>
_IP_ADAPTER_DNS_SERVER_ADDRESS_XP ends
IP_ADAPTER_DNS_SERVER_ADDRESS_XP typedef _IP_ADAPTER_DNS_SERVER_ADDRESS_XP
PIP_ADAPTER_DNS_SERVER_ADDRESS_XP typedef ptr _IP_ADAPTER_DNS_SERVER_ADDRESS_XP
if (NTDDI_VERSION ge NTDDI_WINXP)
IP_ADAPTER_DNS_SERVER_ADDRESS typedef IP_ADAPTER_DNS_SERVER_ADDRESS_XP
PIP_ADAPTER_DNS_SERVER_ADDRESS typedef ptr IP_ADAPTER_DNS_SERVER_ADDRESS_XP
endif

_IP_ADAPTER_WINS_SERVER_ADDRESS_LH struct
union
 Alignment              ULONGLONG ?
 struct
  Length                ULONG ?
  Reserved              DWORD ?
 ends
ends
Next                    ptr _IP_ADAPTER_WINS_SERVER_ADDRESS_LH ?
Address                 SOCKET_ADDRESS <>
_IP_ADAPTER_WINS_SERVER_ADDRESS_LH ends
IP_ADAPTER_WINS_SERVER_ADDRESS_LH typedef _IP_ADAPTER_WINS_SERVER_ADDRESS_LH
PIP_ADAPTER_WINS_SERVER_ADDRESS_LH typedef ptr _IP_ADAPTER_WINS_SERVER_ADDRESS_LH
if (NTDDI_VERSION ge NTDDI_VISTA)
IP_ADAPTER_WINS_SERVER_ADDRESS typedef IP_ADAPTER_WINS_SERVER_ADDRESS_LH
PIP_ADAPTER_WINS_SERVER_ADDRESS typedef ptr IP_ADAPTER_WINS_SERVER_ADDRESS_LH
endif

_IP_ADAPTER_GATEWAY_ADDRESS_LH struct
union
 Alignment              ULONGLONG ?
 struct
  Length                ULONG ?
  Reserved              DWORD ?
 ends
ends
Next                    ptr _IP_ADAPTER_GATEWAY_ADDRESS_LH ?
Address                 SOCKET_ADDRESS <>
_IP_ADAPTER_GATEWAY_ADDRESS_LH ends
IP_ADAPTER_GATEWAY_ADDRESS_LH typedef _IP_ADAPTER_GATEWAY_ADDRESS_LH
PIP_ADAPTER_GATEWAY_ADDRESS_LH typedef ptr _IP_ADAPTER_GATEWAY_ADDRESS_LH
if (NTDDI_VERSION ge NTDDI_VISTA)
IP_ADAPTER_GATEWAY_ADDRESS typedef IP_ADAPTER_GATEWAY_ADDRESS_LH
PIP_ADAPTER_GATEWAY_ADDRESS typedef ptr IP_ADAPTER_GATEWAY_ADDRESS_LH
endif

_IP_ADAPTER_PREFIX_XP   struct
union
 Alignment              ULONGLONG ?
 struct
  Length                ULONG ?
  Flags                 DWORD ?
 ends
ends
Next                    ptr _IP_ADAPTER_PREFIX_XP ?
Address                 SOCKET_ADDRESS <>
PrefixLength            ULONG ?
_IP_ADAPTER_PREFIX_XP   ends
IP_ADAPTER_PREFIX_XP    typedef _IP_ADAPTER_PREFIX_XP
PIP_ADAPTER_PREFIX_XP   typedef ptr _IP_ADAPTER_PREFIX_XP
if (NTDDI_VERSION ge NTDDI_WINXP)
IP_ADAPTER_PREFIX       typedef IP_ADAPTER_PREFIX_XP
PIP_ADAPTER_PREFIX      typedef ptr IP_ADAPTER_PREFIX_XP
endif

_IP_ADAPTER_DNS_SUFFIX  struct
Next                    ptr _IP_ADAPTER_DNS_SUFFIX ?
String                  WCHAR MAX_DNS_SUFFIX_STRING_LENGTH dup(?)
_IP_ADAPTER_DNS_SUFFIX  ends
IP_ADAPTER_DNS_SUFFIX   typedef _IP_ADAPTER_DNS_SUFFIX
PIP_ADAPTER_DNS_SUFFIX  typedef ptr _IP_ADAPTER_DNS_SUFFIX

define IP_ADAPTER_DDNS_ENABLED               0x00000001
define IP_ADAPTER_REGISTER_ADAPTER_SUFFIX    0x00000002
define IP_ADAPTER_DHCP_ENABLED               0x00000004
define IP_ADAPTER_RECEIVE_ONLY               0x00000008
define IP_ADAPTER_NO_MULTICAST               0x00000010
define IP_ADAPTER_IPV6_OTHER_STATEFUL_CONFIG 0x00000020
define IP_ADAPTER_NETBIOS_OVER_TCPIP_ENABLED 0x00000040
define IP_ADAPTER_IPV4_ENABLED               0x00000080
define IP_ADAPTER_IPV6_ENABLED               0x00000100
define IP_ADAPTER_IPV6_MANAGE_ADDRESS_CONFIG 0x00000200

_IP_ADAPTER_ADDRESSES_LH struct
union
 Alignment              ULONGLONG ?
 struct
  Length                ULONG ?
  IfIndex               IF_INDEX ?
 ends
ends
Next                    ptr _IP_ADAPTER_ADDRESSES_LH ?
AdapterName             PCHAR ?
FirstUnicastAddress     PIP_ADAPTER_UNICAST_ADDRESS_LH ?
FirstAnycastAddress     PIP_ADAPTER_ANYCAST_ADDRESS_XP ?
FirstMulticastAddress   PIP_ADAPTER_MULTICAST_ADDRESS_XP ?
FirstDnsServerAddress   PIP_ADAPTER_DNS_SERVER_ADDRESS_XP ?
DnsSuffix               PWCHAR ?
Description             PWCHAR ?
FriendlyName            PWCHAR ?
PhysicalAddress         BYTE MAX_ADAPTER_ADDRESS_LENGTH dup(?)
PhysicalAddressLength   ULONG ?
union
 Flags                  ULONG ?
 struct
  record
   DdnsEnabled                              ULONG : 1 ?
   RegisterAdapterSuffix                    ULONG : 1 ?
   Dhcpv4Enabled                            ULONG : 1 ?
   ReceiveOnly                              ULONG : 1 ?
   NoMulticast                              ULONG : 1 ?
   Ipv6OtherStatefulConfig                  ULONG : 1 ?
   NetbiosOverTcpipEnabled                  ULONG : 1 ?
   Ipv4Enabled                              ULONG : 1 ?
   Ipv6Enabled                              ULONG : 1 ?
   Ipv6ManagedAddressConfigurationSupported ULONG : 1 ?
  ends
 ends
ends
Mtu                     ULONG ?
IfType                  IFTYPE ?
OperStatus              IF_OPER_STATUS ?
Ipv6IfIndex             IF_INDEX ?
ZoneIndices             ULONG 16 dup(?)
FirstPrefix             PIP_ADAPTER_PREFIX_XP ?
TransmitLinkSpeed       ULONG64 ?
ReceiveLinkSpeed        ULONG64 ?
FirstWinsServerAddress  PIP_ADAPTER_WINS_SERVER_ADDRESS_LH ?
FirstGatewayAddress     PIP_ADAPTER_GATEWAY_ADDRESS_LH ?
Ipv4Metric              ULONG ?
Ipv6Metric              ULONG ?
Luid                    IF_LUID <>
Dhcpv4Server            SOCKET_ADDRESS <>
CompartmentId           NET_IF_COMPARTMENT_ID ?
NetworkGuid             NET_IF_NETWORK_GUID <>
ConnectionType          NET_IF_CONNECTION_TYPE ?
TunnelType              TUNNEL_TYPE ?
Dhcpv6Server            SOCKET_ADDRESS <>
Dhcpv6ClientDuid        BYTE MAX_DHCPV6_DUID_LENGTH dup(?)
Dhcpv6ClientDuidLength  ULONG ?
Dhcpv6Iaid              ULONG ?
if (NTDDI_VERSION ge NTDDI_VISTASP1)
FirstDnsSuffix          PIP_ADAPTER_DNS_SUFFIX ?
endif
_IP_ADAPTER_ADDRESSES_LH ends
IP_ADAPTER_ADDRESSES_LH typedef _IP_ADAPTER_ADDRESSES_LH
PIP_ADAPTER_ADDRESSES_LH typedef ptr _IP_ADAPTER_ADDRESSES_LH

_IP_ADAPTER_ADDRESSES_XP struct
union
 Alignment              ULONGLONG ?
 struct
  Length                ULONG ?
  IfIndex               DWORD ?
 ends
ends
Next                    ptr _IP_ADAPTER_ADDRESSES_XP ?
AdapterName             PCHAR ?
FirstUnicastAddress     PIP_ADAPTER_UNICAST_ADDRESS_XP ?
FirstAnycastAddress     PIP_ADAPTER_ANYCAST_ADDRESS_XP ?
FirstMulticastAddress   PIP_ADAPTER_MULTICAST_ADDRESS_XP ?
FirstDnsServerAddress   PIP_ADAPTER_DNS_SERVER_ADDRESS_XP ?
DnsSuffix               PWCHAR ?
Description             PWCHAR ?
FriendlyName            PWCHAR ?
PhysicalAddress         BYTE MAX_ADAPTER_ADDRESS_LENGTH dup(?)
PhysicalAddressLength   DWORD ?
Flags                   DWORD ?
Mtu                     DWORD ?
IfType                  DWORD ?
OperStatus              IF_OPER_STATUS ?
Ipv6IfIndex             DWORD ?
ZoneIndices             DWORD 16 dup(?)
FirstPrefix             PIP_ADAPTER_PREFIX_XP ?
_IP_ADAPTER_ADDRESSES_XP ends
IP_ADAPTER_ADDRESSES_XP typedef _IP_ADAPTER_ADDRESSES_XP
PIP_ADAPTER_ADDRESSES_XP typedef ptr _IP_ADAPTER_ADDRESSES_XP

if (NTDDI_VERSION ge NTDDI_VISTA)
IP_ADAPTER_ADDRESSES    typedef IP_ADAPTER_ADDRESSES_LH
PIP_ADAPTER_ADDRESSES   typedef ptr IP_ADAPTER_ADDRESSES_LH
elseif (NTDDI_VERSION ge NTDDI_WINXP)
IP_ADAPTER_ADDRESSES    typedef IP_ADAPTER_ADDRESSES_XP
PIP_ADAPTER_ADDRESSES   typedef ptr IP_ADAPTER_ADDRESSES_XP
else
IP_ADAPTER_ADDRESSES    typedef IP_ADAPTER_ADDRESSES_XP
PIP_ADAPTER_ADDRESSES   typedef ptr IP_ADAPTER_ADDRESSES_XP
endif

define GAA_FLAG_SKIP_UNICAST                   0x0001
define GAA_FLAG_SKIP_ANYCAST                   0x0002
define GAA_FLAG_SKIP_MULTICAST                 0x0004
define GAA_FLAG_SKIP_DNS_SERVER                0x0008
define GAA_FLAG_INCLUDE_PREFIX                 0x0010
define GAA_FLAG_SKIP_FRIENDLY_NAME             0x0020
define GAA_FLAG_INCLUDE_WINS_INFO              0x0040
define GAA_FLAG_INCLUDE_GATEWAYS               0x0080
define GAA_FLAG_INCLUDE_ALL_INTERFACES         0x0100
define GAA_FLAG_INCLUDE_ALL_COMPARTMENTS       0x0200
define GAA_FLAG_INCLUDE_TUNNEL_BINDINGORDER    0x0400
define GAA_FLAG_SKIP_DNS_INFO                  0x0800

endif

_IP_PER_ADAPTER_INFO_W2KSP1 struct
AutoconfigEnabled       UINT ?
AutoconfigActive        UINT ?
CurrentDnsServer        PIP_ADDR_STRING ?
DnsServerList           IP_ADDR_STRING <>
_IP_PER_ADAPTER_INFO_W2KSP1 ends
IP_PER_ADAPTER_INFO_W2KSP1 typedef _IP_PER_ADAPTER_INFO_W2KSP1
PIP_PER_ADAPTER_INFO_W2KSP1 typedef ptr _IP_PER_ADAPTER_INFO_W2KSP1
if (NTDDI_VERSION ge NTDDI_WIN2KSP1)
IP_PER_ADAPTER_INFO     typedef IP_PER_ADAPTER_INFO_W2KSP1
PIP_PER_ADAPTER_INFO    typedef ptr IP_PER_ADAPTER_INFO_W2KSP1
endif

FIXED_INFO_W2KSP1       struct
HostName                sbyte MAX_HOSTNAME_LEN + 4 dup(?)
DomainName              sbyte MAX_DOMAIN_NAME_LEN + 4 dup(?)
CurrentDnsServer        PIP_ADDR_STRING ?
DnsServerList           IP_ADDR_STRING <>
NodeType                UINT ?
ScopeId                 sbyte MAX_SCOPE_ID_LEN + 4 dup(?)
EnableRouting           UINT ?
EnableProxy             UINT ?
EnableDns               UINT ?
FIXED_INFO_W2KSP1       ends
PFIXED_INFO_W2KSP1      typedef ptr FIXED_INFO_W2KSP1
if (NTDDI_VERSION ge NTDDI_WIN2KSP1)
FIXED_INFO              typedef FIXED_INFO_W2KSP1
PFIXED_INFO             typedef ptr FIXED_INFO_W2KSP1
endif

ifndef IP_INTERFACE_NAME_INFO_DEFINED
define IP_INTERFACE_NAME_INFO_DEFINED

ip_interface_name_info_w2ksp1 struct
Index                   ULONG ?
MediaType               ULONG ?
ConnectionType          UCHAR ?
AccessType              UCHAR ?
DeviceGuid              GUID <>
InterfaceGuid           GUID <>
ip_interface_name_info_w2ksp1 ends
IP_INTERFACE_NAME_INFO_W2KSP1 typedef ip_interface_name_info_w2ksp1
PIP_INTERFACE_NAME_INFO_W2KSP1 typedef ptr ip_interface_name_info_w2ksp1

if (NTDDI_VERSION ge NTDDI_WIN2KSP1)
IP_INTERFACE_NAME_INFO  typedef IP_INTERFACE_NAME_INFO_W2KSP1
PIP_INTERFACE_NAME_INFO typedef ptr IP_INTERFACE_NAME_INFO_W2KSP1
endif

endif

endif

endif
