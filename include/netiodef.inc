ifndef _NETIODEF_
_NETIODEF_ equ <>

include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

include ws2def.inc
include ws2ipdef.inc
include mswsockdef.inc
include mstcpip.inc
include nldef.inc

IS_POWER_OF_TWO macro x
	exitm<(((x) NE 0) AND (((x) AND ((x) - 1)) EQ 0))>
	endm

if defined(_NTDDK_) OR defined(_NTRTL_)

IS_VALID_IPV4_MASK macro x
	exitm<((x.S_un.S_addr == -1) OR IS_POWER_OF_TWO(not RtlUlongByteSwap(x.S_un.S_addr)+1))>
	endm
endif

ifndef BYTE_ORDER
_LITTLE_ENDIAN		equ 1234
_BIG_ENDIAN		equ 4321
_PDP_ENDIAN		equ 3412
BYTE_ORDER		equ _LITTLE_ENDIAN
endif

PHANDLE8		typedef ptr BYTE
PHANDLE16		typedef ptr WORD
PHANDLE32		typedef ptr DWORD
PHANDLE64		typedef ptr QWORD


MAKE_DD_DEVICE_NAME macro x
	exitm<(L"\\Device\\" x)>
	endm
MAKE_WIN_DEVICE_NAME macro x
	exitm<(L"\\\\.\\" x)>
	endm


include ifdef.inc

DL_ADDRESS_LENGTH_MAXIMUM equ IF_MAX_PHYS_ADDRESS_LENGTH
DL_HEADER_LENGTH_MAXIMUM equ 64

DL_ETHERNET_HEADER_LENGTH_MAXIMUM equ (sizeof(ETHERNET_HEADER) + sizeof(SNAP_HEADER))
if (sizeof(IPV4_HEADER) gt sizeof(IPV6_HEADER))
DL_TUNNEL_HEADER_LENGTH_MAXIMUM equ sizeof(IPV4_HEADER)
else
DL_TUNNEL_HEADER_LENGTH_MAXIMUM equ sizeof(IPV6_HEADER)
endif

ifndef _DEFINE_DL_ADDRESS_TYPE_
_DEFINE_DL_ADDRESS_TYPE_ equ 1
DlUnicast		equ 0
DlMulticast		equ 1
DlBroadcast		equ 2
endif

DL_OUI			UNION
_Byte			db 3 dup(?)
DL_OUI			ENDS
PDL_OUI			typedef ptr DL_OUI

DL_EI48			UNION
_Byte			db 3 dup(?)
DL_EI48			ENDS
PDL_EI48		typedef ptr DL_EI48

DL_EUI48		UNION
_Byte			db 6 dup(?)
STRUC
 Oui			DL_OUI <>
 Ei48			DL_EI48 <>
ENDS
DL_EUI48		ENDS
PDL_EUI48		typedef ptr DL_EUI48

if (DL_ADDRESS_LENGTH_MAXIMUM LT sizeof(DL_EUI48))
    .err<sizeof(DL_EUI48)>
endif

EUI48_BROADCAST_INIT	equ <{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff }>
externdef		eui48_broadcast:DL_EUI48

DL_EI64			UNION
_Byte			db 5 dup(?)
DL_EI64			ENDS
PDL_EI64		typedef ptr DL_EI64

DL_EUI64		UNION
_Byte			db 8 dup(?)
Value			UINT64 ?
STRUC
 Oui			DL_OUI <>
 UNION
  Ei64			DL_EI64 <>
  STRUC
   _Type		db ?
   Tse			db ?
   Ei48			DL_EI48 <>
  ENDS
 ENDS
ENDS
DL_EUI64		ENDS
PDL_EUI64		typedef ptr DL_EUI64

SNAP_HEADER		STRUC
Dsap			UINT8 ?
Ssap			UINT8 ?
Control			UINT8 ?
Oui			UINT8 3 dup(?)
_Type			UINT16 ?
SNAP_HEADER		ENDS
PSNAP_HEADER		typedef ptr SNAP_HEADER

SNAP_DSAP		equ 0xaa
SNAP_SSAP		equ 0xaa
SNAP_CONTROL		equ 0x03
SNAP_OUI		equ 0x00

SNAP_TYPE_ARP		equ ETHERNET_TYPE_ARP
SNAP_TYPE_IPV4		equ ETHERNET_TYPE_IPV4
SNAP_TYPE_IPV6		equ ETHERNET_TYPE_IPV6

ETHERNET_HEADER		STRUC
Destination		DL_EUI48 <>
Source			DL_EUI48 <>
UNION
 _Type			UINT16 ?
 _Length		UINT16 ?
ENDS
ETHERNET_HEADER		ENDS
PETHERNET_HEADER	typedef ptr ETHERNET_HEADER

ETH_LENGTH_OF_HEADER	equ 14
ETH_LENGTH_OF_VLAN_HEADER equ 4
ETH_LENGTH_OF_SNAP_HEADER equ 8

if (ETH_LENGTH_OF_HEADER NE sizeof(ETHERNET_HEADER))
    .err<ETHERNET_HEADER>
endif
if (ETH_LENGTH_OF_SNAP_HEADER NE sizeof(SNAP_HEADER))
    .err<SNAP_HEADER>
endif

ETHERNET_TYPE_MINIMUM	equ 0x0600
ETHERNET_TYPE_IPV4	equ 0x0800
ETHERNET_TYPE_ARP	equ 0x0806
ETHERNET_TYPE_IPV6	equ 0x86dd
ETHERNET_TYPE_802_1Q	equ 0x8100

VLAN_TAG		STRUC
UNION
 Tag			UINT16 ?
ENDS
_Type			UINT16 ?
VLAN_TAG		ENDS

if (ETH_LENGTH_OF_VLAN_HEADER NE sizeof(VLAN_TAG))
    .err<VLAN_TAG>
endif


ICMP_HEADER		STRUC
_Type			db ?
Code			db ?
Checksum		dw ?
ICMP_HEADER		ENDS
PICMP_HEADER		typedef ptr ICMP_HEADER

ICMP_MESSAGE		STRUC
Header			ICMP_HEADER <>
UNION
 Data32			dd 1 dup(?)
 Data16			dw 2 dup(?)
 Data8			db 4 dup(?)
ENDS ;Data
ICMP_MESSAGE		ENDS
PICMP_MESSAGE		typedef ptr ICMP_MESSAGE


IPV4_HEADER		STRUC
UNION
VersionAndHeaderLength	db ?
ENDS
UNION
TypeOfServiceAndEcnField db ?
ENDS
TotalLength		dw ?
Identification		dw ?
UNION
FlagsAndOffset		dw ?
ENDS
TimeToLive		db ?
Protocol		db ?
HeaderChecksum		dw ?
SourceAddress		IN_ADDR <>
DestinationAddress	IN_ADDR <>
IPV4_HEADER		ENDS
PIPV4_HEADER		typedef ptr IPV4_HEADER

ip4_hdr			equ _IPV4_HEADER
ip4_ver_hlen		equ VersionAndHeaderLength
ip4_ver			equ Version
ip4_hlen		equ HeaderLength
ip4_tos			equ TypeOfService
ip4_len			equ TotalLength
ip4_id			equ Identification
ip4_flags_offset	equ FlagsAndOffset
ip4_flags		equ Flags
ip4_offset		equ FragmentOffset
ip4_ttl			equ TimeToLive
ip4_protocol		equ Protocol
ip4_xsum		equ HeaderChecksum
ip4_src			equ SourceAddress
ip4_dest		equ DestinationAddress

if (sizeof(IPV4_HEADER) NE 20)
   .err<IPV4_HEADER>
endif

IP_VER_MASK		equ 0xF0
IPV4_VERSION		equ 4
IPV4_DEFAULT_VERHLEN	equ ((IPV4_VERSION SHL 4) OR (sizeof(IPV4_HEADER) / sizeof(DWORD)))
IPV4_TOS_MASK		equ 0xFC

MAX_IPV4_PACKET		equ 65535
MAX_IPV4_PAYLOAD	equ (MAX_IPV4_PACKET - sizeof(IPV4_HEADER))

MAX_IPV4_HLEN		equ 60

IPV4_MINIMUM_MTU	equ 576
IPV4_MINIMUM_ULMTU	equ (IPV4_MINIMUM_MTU - sizeof(IPV4_HEADER))

IPV4_MIN_MINIMUM_MTU	equ 352
IPV4_MAX_MINIMUM_MTU	equ 576

MAX_IP_OPTIONS_LENGTH	equ ((0xF * sizeof(UINT32)) - sizeof(IPV4_HEADER))

SIZEOF_IP_OPT_ROUTING_HEADER equ 3

SIZEOF_IP_OPT_TIMESTAMP_HEADER equ 4

SIZEOF_IP_OPT_SECURITY	equ 11
SIZEOF_IP_OPT_STREAMIDENTIFIER equ 4
SIZEOF_IP_OPT_ROUTERALERT equ 4

IP4_OFF_MASK		equ 0xff1f

if defined(_NTDDK_) OR defined(_NTRTL_)

endif

IPV4_OPTION_HEADER	STRUC
UNION
 OptionType		db ?
ENDS
OptionLength		db ?
IPV4_OPTION_HEADER	ENDS
PIPV4_OPTION_HEADER	typedef ptr IPV4_OPTION_HEADER

if (sizeof(IPV4_OPTION_HEADER) NE 2)
   .err<IPV4_OPTION_HEADER>
endif

ifndef IP_EXPORT_INCLUDED
IP_OPT_EOL		equ 0x00
IP_OPT_NOP		equ 0x01
IP_OPT_SECURITY		equ 0x82
IP_OPT_LSRR		equ 0x83
IP_OPT_TS		equ 0x44
IP_OPT_RR		equ 0x07
IP_OPT_SSRR		equ 0x89
IP_OPT_SID		equ 0x88
IP_OPT_ROUTER_ALERT	equ 0x94
IP_OPT_MULTIDEST	equ 0x95
else
IPV4_OPTION_TYPE	typedef ULONG
endif

IPV4_TIMESTAMP_OPTION	STRUC
Pointer			db ?
UNION
 FlagsOverflow		db ?
ENDS
IPV4_TIMESTAMP_OPTION	ENDS
PIPV4_TIMESTAMP_OPTION	typedef ptr IPV4_TIMESTAMP_OPTION

IP_OPTION_TIMESTAMP_ONLY equ 0
IP_OPTION_TIMESTAMP_ADDRESS equ 1
IP_OPTION_TIMESTAMP_SPECIFIC_ADDRESS equ 3

IPV4_ROUTING_HEADER	STRUC
Pointer			db ?
IPV4_ROUTING_HEADER	ENDS
PIPV4_ROUTING_HEADER	typedef ptr IPV4_ROUTING_HEADER

ICMPV4_HEADER		typedef ICMP_HEADER
PICMPV4_HEADER		typedef ptr ICMP_HEADER
ICMPV4_MESSAGE		typedef ICMP_MESSAGE
PICMPV4_MESSAGE		typedef ptr ICMP_MESSAGE

icmp4_hdr		equ <_ICMPV4_MESSAGE>
icmp4_type		equ <Header._Type>
icmp4_code		equ <Header._Code>
icmp4_cksum		equ <Header.Checksum>
icmp4_un_data32		equ <Data32>
icmp4_un_data16		equ <Data16>
icmp4_un_data8		equ <Data8>
icmp4_dataun		equ <_Data>

icmp4_data32		equ <icmp4_dataun.icmp4_un_data32>
icmp4_data16		equ <icmp4_dataun.icmp4_un_data16>
icmp4_data8		equ <icmp4_dataun.icmp4_un_data8>
icmp4_pptr		equ <icmp4_data32[0]>
icmp4_mtu		equ <icmp4_data32[0]>
icmp4_id		equ <icmp4_data16[0]>
icmp4_seq		equ <icmp4_data16[1]>
icmp4_maxdelay		equ <icmp4_data16[0]>

ICMP4_UNREACH_NET	equ 0
ICMP4_UNREACH_HOST	equ 1
ICMP4_UNREACH_PROTOCOL	equ 2
ICMP4_UNREACH_PORT	equ 3
ICMP4_UNREACH_FRAG_NEEDED equ 4
ICMP4_UNREACH_SOURCEROUTE_FAILED equ 5
ICMP4_UNREACH_NET_UNKNOWN equ 6
ICMP4_UNREACH_HOST_UNKNOWN equ 7
ICMP4_UNREACH_ISOLATED	equ 8
ICMP4_UNREACH_NET_ADMIN equ 9
ICMP4_UNREACH_HOST_ADMIN equ 10
ICMP4_UNREACH_NET_TOS	equ 11
ICMP4_UNREACH_HOST_TOS	equ 12
ICMP4_UNREACH_ADMIN	equ 13

ICMP4_TIME_EXCEED_TRANSIT equ 0
ICMP4_TIME_EXCEED_REASSEMBLY equ 1

ICMPV4_ROUTER_SOLICIT	STRUC
RsHeader		ICMPV4_MESSAGE <>
ICMPV4_ROUTER_SOLICIT	ENDS
PICMPV4_ROUTER_SOLICIT	typedef ptr ICMPV4_ROUTER_SOLICIT

RsType			equ <RsHeader.icmp4_type>
RsCode			equ <RsHeader.icmp4_code>
RsCksum			equ <RsHeader.icmp4_cksum>
RsReserved		equ <RsHeader.icmp4_data32[0]>

ICMPV4_ROUTER_ADVERT_HEADER  STRUC
RaHeader		ICMPV4_MESSAGE <>
ICMPV4_ROUTER_ADVERT_HEADER ENDS
PICMPV4_ROUTER_ADVERT_HEADER typedef ptr ICMPV4_ROUTER_ADVERT_HEADER

RaType			equ <RaHeader.icmp4_type>
RaCode			equ <RaHeader.icmp4_code>
RaCksum			equ <RaHeader.icmp4_cksum>
RaNumAddr		equ <RaHeader.icmp4_data8[0]>
RaAddrEntrySize		equ <RaHeader.icmp4_data8[1]>
RaAddrLifetime		equ <RaHeader.icmp4_data16[1]>

ICMPV4_ROUTER_ADVERT_ENTRY  STRUC
RouterAdvertAddr	IN_ADDR <>
PreferenceLevel		LONG ?
ICMPV4_ROUTER_ADVERT_ENTRY ENDS
PICMPV4_ROUTER_ADVERT_ENTRY typedef ptr ICMPV4_ROUTER_ADVERT_ENTRY

ICMPV4_INVALID_PREFERENCE_LEVEL equ 0x80000000

ICMPV4_TIMESTAMP_MESSAGE  STRUC
Header			ICMPV4_MESSAGE <>
OriginateTimestamp	UINT32 ?
ReceiveTimestamp	UINT32 ?
TransmitTimestamp	UINT32 ?
ICMPV4_TIMESTAMP_MESSAGE ENDS
PICMPV4_TIMESTAMP_MESSAGE typedef ptr ICMPV4_TIMESTAMP_MESSAGE

ICMPV4_ADDRESS_MASK_MESSAGE  STRUC
Header			ICMPV4_MESSAGE <>
AddressMask		UINT32 ?
ICMPV4_ADDRESS_MASK_MESSAGE ENDS
PICMPV4_ADDRESS_MASK_MESSAGE typedef ptr ICMPV4_ADDRESS_MASK_MESSAGE

icmp4_ts_type		equ <Header.icmp4_type>
icmp4_ts_code		equ <Header.icmp4_code>
icmp4_ts_cksum		equ <Header.icmp4_cksum>
icmp4_ts_id		equ <Header.icmp4_id>
icmp4_ts_seq		equ <Header.icmp4_seq>
icmp4_ts_originate	equ <OriginateTimestamp>
icmp4_ts_receive	equ <ReceiveTimestamp>
icmp4_ts_transmit	equ <TransmitTimestamp>

ARP_HEADER		STRUC
HardwareAddressSpace	dw ?
ProtocolAddressSpace	dw ?
HardwareAddressLength	db ?
ProtocolAddressLength	db ?
Opcode			dw ?
SenderHardwareAddress	db 0 dup(?)
ARP_HEADER		ENDS
PARP_HEADER		typedef ptr ARP_HEADER

ARP_REQUEST		equ 1
ARP_RESPONSE		equ 2

ARP_HW_ENET		equ 1
ARP_HW_802		equ 6

IGMP_QUERY_TYPE		equ 0x11
IGMP_VERSION1_REPORT_TYPE equ 0x12
IGMP_VERSION2_REPORT_TYPE equ 0x16
IGMP_LEAVE_GROUP_TYPE	equ 0x17
IGMP_VERSION3_REPORT_TYPE equ 0x22

IGMP_HEADER		STRUC
UNION
 VersionType		db ?
ENDS
UNION
 Reserved		db ?
 MaxRespTime		db ?
 _Code			db ?
ENDS
Checksum		dw ?
MulticastAddress	IN_ADDR <>
IGMP_HEADER		ENDS
PIGMP_HEADER		typedef ptr IGMP_HEADER

IGMP_MAX_RESP_CODE_TYPE_NORMAL equ 0
IGMP_MAX_RESP_CODE_TYPE_FLOAT equ 1

IGMPV3_QUERY_HEADER	STRUC
_Type			db ?
UNION
 MaxRespCode		db ?
ENDS
Checksum		dw ?
MulticastAddress	IN_ADDR <>
QuerierRobustnessVariable db ? ; : 3
;SuppressRouterSideProcessing : 1 UINT8 ?
;Reserved : 4		UINT8 ?
UNION
 QueriersQueryInterfaceCode db ?
ENDS
SourceCount		dw ?
IGMPV3_QUERY_HEADER	ENDS
PIGMPV3_QUERY_HEADER	typedef ptr IGMPV3_QUERY_HEADER

IGMPV3_REPORT_RECORD_HEADER  STRUC
_Type			db ?
AuxillaryDataLength	db ?
SourceCount		dw ?
MulticastAddress	IN_ADDR <>
IGMPV3_REPORT_RECORD_HEADER ENDS
PIGMPV3_REPORT_RECORD_HEADER typedef ptr IGMPV3_REPORT_RECORD_HEADER

IGMPV3_REPORT_HEADER	STRUC
_Type			UINT8 ?
Reserved		UINT8 ?
Checksum		UINT16 ?
Reserved2		UINT16 ?
RecordCount		UINT16 ?
IGMPV3_REPORT_HEADER	ENDS
PIGMPV3_REPORT_HEADER	typedef ptr IGMPV3_REPORT_HEADER

IPV6_HEADER		STRUC
VersionClassFlow	dd ?
PayloadLength		dw ?
NextHeader		db ?
HopLimit		db ?
SourceAddress		IN6_ADDR <>
DestinationAddress	IN6_ADDR <>
IPV6_HEADER		ENDS
PIPV6_HEADER		typedef ptr IPV6_HEADER

ip6_hdr			equ <_IPV6_HEADER>
ip6_flow		equ <VersionClassFlow>
ip6_plen		equ <PayloadLength>
ip6_nxt			equ <NextHeader>
ip6_hops		equ <HopLimit>
ip6_hlim		equ <HopLimit>
ip6_src			equ <SourceAddress>
ip6_dst			equ <DestinationAddress>

IP_VER_MASK		equ 0xF0
IPV6_VERSION		equ 0x60

IPV6_TRAFFIC_CLASS_MASK equ 0x0000C00F
IPV6_ECN_MASK		equ 0x00003000
IPV6_FLOW_LABEL_MASK	equ 0xFFFF0F00
MAX_IPV6_PAYLOAD	equ 65535
MAX_IPV6_PACKET		equ (MAX_IPV6_PAYLOAD + sizeof(IPV6_HEADER))

IPV6_ECN_SHIFT		equ 12

IPV6_MINIMUM_MTU	equ 1280
IPV6_MINIMUM_ULMTU	equ (IPV6_MINIMUM_MTU - sizeof(IPV6_HEADER))

IPV6_TRAFFIC_CLASS macro VersionClassFlow
	exitm<(((((VersionClassFlow) and IPV6_TRAFFIC_CLASS_MASK) shr 12) + (((VersionClassFlow) and IPV6_TRAFFIC_CLASS_MASK) shl 4)))>
	endm

IPV6_FRAGMENT_HEADER	STRUC
NextHeader		db ?
Reserved		db ?
UNION
 OffsetAndFlags		dw ?
ENDS
Id			dd ?
IPV6_FRAGMENT_HEADER	ENDS
PIPV6_FRAGMENT_HEADER	typedef ptr IPV6_FRAGMENT_HEADER

if (sizeof(IPV6_FRAGMENT_HEADER) NE 8)
    .err<IPV6_FRAGMENT_HEADER>
endif

ip6_frag		equ <_IPV6_FRAGMENT_HEADER>
ip6f_nxt		equ <NextHeader>
ip6f_reserved		equ <Reserved>
ip6f_offlg		equ <OffsetAndFlags>
ip6f_ident		equ <Id>

IP6F_OFF_MASK		equ 0xf8ff
IP6F_RESERVED_MASK	equ 0x0600
IP6F_MORE_FRAG		equ 0x0100

if defined(_NTDDK_) OR defined(_NTRTL_)

endif

IPV6_EXTENSION_HEADER	STRUC
NextHeader		db ?
_Length			db ?
IPV6_EXTENSION_HEADER	ENDS
PIPV6_EXTENSION_HEADER	typedef ptr IPV6_EXTENSION_HEADER

EXT_LEN_UNIT		equ 8

IPV6_EXTENSION_HEADER_LENGTH macro Blocks
	exitm<((Blocks + 1) * EXT_LEN_UNIT)>
	endm
MAX_IPV6_EXTENSION_HEADER_LENGTH equ IPV6_EXTENSION_HEADER_LENGTH(0xFF)
IPV6_EXTENSION_HEADER_BLOCKS macro L
	exitm<((L / EXT_LEN_UNIT) - 1)>
	endm
IP_AUTHENTICATION_HEADER_LENGTH macro Blocks
	exitm<((Blocks + 2) * 4)>
	endm
IP_AUTHENTICATION_HEADER_BLOCKS macro L
	exitm<(((L + sizeof(AUTHENTICATION_HEADER)) / 4) - 2)>
	endm

IPV6_ROUTER_ALERT_LENGTH equ IPV6_EXTENSION_HEADER_LENGTH(0)

ip6_hbh			equ <_IPV6_EXTENSION_HEADER>
ip6h_nxt		equ <NextHeader>
ip6h_len		equ <_Length>
ip6_dest		equ <_IPV6_EXTENSION_HEADER>
ip6d_nxt		equ <NextHeader>
ip6d_len		equ <_Length>

IPV6_OPTION_HEADER	STRUC
_Type			db ?
DataLength		db ?
IPV6_OPTION_HEADER	ENDS
PIPV6_OPTION_HEADER	typedef ptr IPV6_OPTION_HEADER

IP6OPT_PAD1		equ 0x00
IP6OPT_PADN		equ 0x01
IP6OPT_TUNNEL_LIMIT	equ 0x04
IP6OPT_ROUTER_ALERT	equ 0x05
IP6OPT_JUMBO		equ 0xc2
IP6OPT_NSAP_ADDR	equ 0xc3

IP6OPT_TYPE macro T
	exitm<((T) AND 0xc0)>
	endm
IP6OPT_TYPE_SKIP	equ 0x00
IP6OPT_TYPE_DISCARD	equ 0x40
IP6OPT_TYPE_FORCEICMP	equ 0x80
IP6OPT_TYPE_ICMP	equ 0xc0

IP6OPT_MUTABLE		equ 0x20
IP6OPT_ISMUTABLE macro T
	exitm<(((T) AND IP6OPT_MUTABLE) NE 0)>
	endm

IPV6_OPTION_JUMBOGRAM	STRUC
Header			IPV6_OPTION_HEADER <>
JumbogramLength		db 4 dup(?)
IPV6_OPTION_JUMBOGRAM	ENDS
PIPV6_OPTION_JUMBOGRAM	typedef ptr IPV6_OPTION_JUMBOGRAM

ip6_opt_jumbo		equ <_IPV6_OPTION_JUMBOGRAM>
ip6oj_type		equ <Header._Type>
ip6oj_len		equ <Header.DataLength>
ip6oj_jumbo_len		equ <JumbogramLength>


IPV6_OPTION_ROUTER_ALERT  STRUC
Header			IPV6_OPTION_HEADER <>
Value			db 2 dup(?)
IPV6_OPTION_ROUTER_ALERT ENDS
PIPV6_OPTION_ROUTER_ALERT typedef ptr IPV6_OPTION_ROUTER_ALERT

ip6_opt_router		equ <_IPV6_OPTION_ROUTER_ALERT>
ip6or_type		equ <Header._Type>
ip6or_len		equ <Header.DataLength>
ip6or_value		equ <Value>

SIZEOF_IPV6_ROUTERALERT equ IPV6_EXTENSION_HEADER_LENGTH(0)

IPV6_ROUTING_HEADER	STRUC
NextHeader		db ?
_Length			db ?
RoutingType		db ?
SegmentsLeft		db ?
Reserved		db 4 dup(?)
IPV6_ROUTING_HEADER	ENDS
PIPV6_ROUTING_HEADER	typedef ptr IPV6_ROUTING_HEADER

ip6_rthdr		equ <_IPV6_ROUTING_HEADER>
ip6r_nxt		equ <NextHeader>
ip6r_len		equ <_Length>
ip6r_type		equ <RoutingType>
ip6r_segleft		equ <SegmentsLeft>

ICMPV6_HEADER		typedef ICMP_HEADER
PICMPV6_HEADER		typedef ptr ICMP_HEADER

ICMPV6_MESSAGE		typedef ICMP_MESSAGE
PICMPV6_MESSAGE		typedef ptr ICMP_MESSAGE

icmp6_hdr		equ <_ICMPV6_MESSAGE>
icmp6_type		equ <Header._Type>
icmp6_code		equ <Header._Code>
icmp6_cksum		equ <Header.Checksum>
icmp6_un_data32		equ <Data32>
icmp6_un_data16		equ <Data16>
icmp6_un_data8		equ <Data8>
icmp6_dataun		equ <_Data>

icmp6_data32		equ <icmp6_dataun.icmp6_un_data32>
icmp6_data16		equ <icmp6_dataun.icmp6_un_data16>
icmp6_data8		equ <icmp6_dataun.icmp6_un_data8>
icmp6_pptr		equ <icmp6_data32[0]>
icmp6_mtu		equ <icmp6_data32[0]>
icmp6_id		equ <icmp6_data16[0]>
icmp6_seq		equ <icmp6_data16[1]>
icmp6_maxdelay		equ <icmp6_data16[0]>

ICMP6_INFOMSG_MASK	equ 0x80

ICMP6_DST_UNREACH_NOROUTE equ 0
ICMP6_DST_UNREACH_ADMIN equ 1

ICMP6_DST_UNREACH_BEYONDSCOPE equ 2
ICMP6_DST_UNREACH_ADDR	equ 3
ICMP6_DST_UNREACH_NOPORT equ 4

ICMP6_TIME_EXCEED_TRANSIT equ 0
ICMP6_TIME_EXCEED_REASSEMBLY equ 1

ICMP6_PARAMPROB_HEADER	equ 0
ICMP6_PARAMPROB_NEXTHEADER equ 1
ICMP6_PARAMPROB_OPTION	equ 2

ICMPV6_ECHO_REQUEST_FLAG_REVERSE equ 0x1

ND_ROUTER_SOLICIT_HEADER STRUC
nd_rs_hdr		ICMPV6_MESSAGE <>
ND_ROUTER_SOLICIT_HEADER ENDS
PND_ROUTER_SOLICIT_HEADER typedef ptr ND_ROUTER_SOLICIT_HEADER

nd_rs_type		equ <nd_rs_hdr.icmp6_type>
nd_rs_code		equ <nd_rs_hdr.icmp6_code>
nd_rs_cksum		equ <nd_rs_hdr.icmp6_cksum>
nd_rs_reserved		equ <nd_rs_hdr.icmp6_data32[0]>

ND_ROUTER_ADVERT_HEADER STRUC
nd_ra_hdr		ICMPV6_MESSAGE <>
nd_ra_reachable		UINT32 ?
nd_ra_retransmit	UINT32 ?
ND_ROUTER_ADVERT_HEADER ENDS
PND_ROUTER_ADVERT_HEADER typedef ptr ND_ROUTER_ADVERT_HEADER

nd_ra_type		equ <nd_ra_hdr.icmp6_type>
nd_ra_code		equ <nd_ra_hdr.icmp6_code>
nd_ra_cksum		equ <nd_ra_hdr.icmp6_cksum>
nd_ra_curhoplimit	equ <nd_ra_hdr.icmp6_data8[0]>
nd_ra_flags_reserved	equ <nd_ra_hdr.icmp6_data8[1]>
ND_RA_FLAG_MANAGED	equ 0x80
ND_RA_FLAG_OTHER	equ 0x40
ND_RA_FLAG_HOME_AGENT	equ 0x20
ND_RA_FLAG_PREFERENCE	equ 0x18
nd_ra_router_lifetime	equ <nd_ra_hdr.icmp6_data16[1]>

IPV6_ROUTER_ADVERTISEMENT_FLAGS UNION
Value			db ?
IPV6_ROUTER_ADVERTISEMENT_FLAGS ENDS
PIPV6_ROUTER_ADVERTISEMENT_FLAGS typedef ptr IPV6_ROUTER_ADVERTISEMENT_FLAGS

ND_NEIGHBOR_SOLICIT_HEADER STRUC
nd_ns_hdr		ICMPV6_MESSAGE <>
nd_ns_target		IN6_ADDR <>
ND_NEIGHBOR_SOLICIT_HEADER ENDS
PND_NEIGHBOR_SOLICIT_HEADER typedef ptr ND_NEIGHBOR_SOLICIT_HEADER

nd_ns_type		equ <nd_ns_hdr.icmp6_type>
nd_ns_code		equ <nd_ns_hdr.icmp6_code>
nd_ns_cksum		equ <nd_ns_hdr.icmp6_cksum>
nd_ns_reserved		equ <nd_ns_hdr.icmp6_data32[0]>

ND_NEIGHBOR_ADVERT_HEADER STRUC
nd_na_hdr		ICMPV6_MESSAGE <>
nd_na_target		IN6_ADDR <>
ND_NEIGHBOR_ADVERT_HEADER ENDS
PND_NEIGHBOR_ADVERT_HEADER typedef ptr ND_NEIGHBOR_ADVERT_HEADER

nd_na_type		equ <nd_na_hdr.icmp6_type>
nd_na_code		equ <nd_na_hdr.icmp6_code>
nd_na_cksum		equ <nd_na_hdr.icmp6_cksum>
nd_na_flags_reserved	equ <nd_na_hdr.icmp6_data32[0]>

if (BYTE_ORDER EQ _BIG_ENDIAN)
ND_NA_FLAG_ROUTER	equ 0x80000000
ND_NA_FLAG_SOLICITED	equ 0x40000000
ND_NA_FLAG_OVERRIDE	equ 0x20000000
else
ND_NA_FLAG_ROUTER	equ 0x00000080
ND_NA_FLAG_SOLICITED	equ 0x00000040
ND_NA_FLAG_OVERRIDE	equ 0x00000020
endif

IPV6_NEIGHBOR_ADVERTISEMENT_FLAGS UNION
Value			UINT32 ?
IPV6_NEIGHBOR_ADVERTISEMENT_FLAGS ENDS
PIPV6_NEIGHBOR_ADVERTISEMENT_FLAGS typedef ptr IPV6_NEIGHBOR_ADVERTISEMENT_FLAGS

ND_REDIRECT_HEADER	STRUC
nd_rd_hdr		ICMPV6_MESSAGE <>
nd_rd_target		IN6_ADDR <>
nd_rd_dst		IN6_ADDR <>
ND_REDIRECT_HEADER	ENDS
PND_REDIRECT_HEADER	typedef ptr ND_REDIRECT_HEADER

nd_rd_type		equ <nd_rd_hdr.icmp6_type>
nd_rd_code		equ <nd_rd_hdr.icmp6_code>
nd_rd_cksum		equ <nd_rd_hdr.icmp6_cksum>
nd_rd_reserved		equ <nd_rd_hdr.icmp6_data32[0]>

ND_OPTION_HDR		STRUC
nd_opt_type		db ?
nd_opt_len		db ?
ND_OPTION_HDR		ENDS
PND_OPTION_HDR		typedef ptr ND_OPTION_HDR

ND_OPT_SOURCE_LINKADDR	equ 1
ND_OPT_TARGET_LINKADDR	equ 2
ND_OPT_PREFIX_INFORMATION equ 3
ND_OPT_REDIRECTED_HEADER equ 4
ND_OPT_MTU		equ 5
ND_OPT_NBMA_SHORTCUT_LIMIT equ 6
ND_OPT_ADVERTISEMENT_INTERVAL equ 7
ND_OPT_HOME_AGENT_INFORMATION equ 8
ND_OPT_SOURCE_ADDR_LIST equ 9
ND_OPT_TARGET_ADDR_LIST equ 10
ND_OPT_ROUTE_INFO	equ 24

ND_OPTION_PREFIX_INFO	STRUC
nd_opt_pi_type		db ?
nd_opt_pi_len		db ?
nd_opt_pi_prefix_len	db ?
UNION
 nd_opt_pi_flags_reserved db ?
ENDS
nd_opt_pi_valid_time	UINT32 ?
nd_opt_pi_preferred_time UINT32 ?
UNION
 nd_opt_pi_reserved2	UINT32 ?
 STRUC
  nd_opt_pi_reserved3	db 3 dup(?)
  nd_opt_pi_site_prefix_len UINT8 ?
 ENDS
ENDS
nd_opt_pi_prefix	IN6_ADDR <>
ND_OPTION_PREFIX_INFO	ENDS
PND_OPTION_PREFIX_INFO	typedef ptr ND_OPTION_PREFIX_INFO

ND_OPT_PI_FLAG_ONLINK	equ 0x80
ND_OPT_PI_FLAG_AUTO	equ 0x40
ND_OPT_PI_FLAG_ROUTER_ADDR equ 0x20
ND_OPT_PI_FLAG_SITE_PREFIX equ 0x10
ND_OPT_PI_FLAG_ROUTE	equ 0x01

ND_OPTION_RD_HDR	STRUC
nd_opt_rh_type		db ?
nd_opt_rh_len		db ?
nd_opt_rh_reserved1	UINT16 ?
nd_opt_rh_reserved2	UINT32 ?
ND_OPTION_RD_HDR	ENDS
PND_OPTION_RD_HDR	typedef ptr ND_OPTION_RD_HDR

ND_OPTION_MTU		STRUC
nd_opt_mtu_type		db ?
nd_opt_mtu_len		db ?
nd_opt_mtu_reserved	UINT16 ?
nd_opt_mtu_mtu		UINT32 ?
ND_OPTION_MTU		ENDS
PND_OPTION_MTU		typedef ptr ND_OPTION_MTU

ND_OPTION_ROUTE_INFO	STRUC
nd_opt_ri_type		db ?
nd_opt_ri_len		db ?
nd_opt_ri_prefix_len	db ?
UNION
 nd_opt_ri_flags_reserved db ?
ENDS
nd_opt_ri_route_lifetime UINT32 ?
nd_opt_ri_prefix	IN6_ADDR <>
ND_OPTION_ROUTE_INFO	ENDS
PND_OPTION_ROUTE_INFO	typedef ptr ND_OPTION_ROUTE_INFO

ND_OPT_RI_FLAG_PREFERENCE equ 0x18

MLD_HEADER		STRUC
IcmpHeader		ICMPV6_HEADER <>
MaxRespTime		UINT16 ?
Reserved		UINT16 ?
MulticastAddress	IN6_ADDR <>
MLD_HEADER		ENDS
PMLD_HEADER		typedef ptr MLD_HEADER

mld_type		equ <IcmpHeader._Type>
mld_checksum		equ <IcmpHeader.Checksum>

MLD_MAX_RESP_CODE_TYPE_NORMAL equ 0
MLD_MAX_RESP_CODE_TYPE_FLOAT equ 1

MLDV2_QUERY_HEADER	STRUC
IcmpHeader		ICMPV6_HEADER <>
UNION
 MaxRespCode		UINT16 ?
ENDS
Reserved		UINT16 ?
MulticastAddress	IN6_ADDR <>
QuerierRobustnessVariable db ? ; : 3
;SuppressRouterSideProcessing : 1 UINT8 ?
;QueryReserved : 4	UINT8 ?
UNION
 QueriersQueryInterfaceCode db ?
ENDS
SourceCount		UINT16 ?
MLDV2_QUERY_HEADER	ENDS
PMLDV2_QUERY_HEADER	typedef ptr MLDV2_QUERY_HEADER

MLDV2_REPORT_RECORD_HEADER  STRUC
_Type			db ?
AuxillaryDataLength	db ?
SourceCount		UINT16 ?
MulticastAddress	IN6_ADDR <>
MLDV2_REPORT_RECORD_HEADER ENDS
PMLDV2_REPORT_RECORD_HEADER typedef ptr MLDV2_REPORT_RECORD_HEADER

MLDV2_REPORT_HEADER	STRUC
IcmpHeader		ICMPV6_HEADER <>
Reserved		UINT16 ?
RecordCount		UINT16 ?
MLDV2_REPORT_HEADER	ENDS
PMLDV2_REPORT_HEADER	typedef ptr MLDV2_REPORT_HEADER

if defined(_NTDDK_) OR defined(_NTRTL_)

endif

IN6_EMBEDDEDV4_UOCTET_POSITION equ 8
IN6_EMBEDDEDV4_BITS_IN_BYTE equ 8

SEQ_NUM			typedef UINT32
PSEQ_NUM		typedef ptr UINT32

.pragma pack(push, 1)

TCP_HDR			STRUC
th_sport		UINT16 ?
th_dport		UINT16 ?
th_seq			SEQ_NUM ?
th_ack			SEQ_NUM ?
th_x2			UINT8 ? ;  : 4
;th_len : 4		UINT8 ?
th_flags		UINT8 ?
th_win			UINT16 ?
th_sum			UINT16 ?
th_urp			UINT16 ?
TCP_HDR			ENDS
PTCP_HDR		typedef ptr TCP_HDR

.pragma pack(pop)

TH_MAX_LEN		equ (0x0F SHL 2)

TH_FIN			equ 0x01
TH_SYN			equ 0x02
TH_RST			equ 0x04
TH_PSH			equ 0x08
TH_ACK			equ 0x10
TH_URG			equ 0x20
TH_ECE			equ 0x40
TH_CWR			equ 0x80
TH_ALL			equ (TH_FIN or TH_SYN or TH_RST or TH_PSH or TH_ACK or TH_URG or TH_ECE or TH_CWR)
TH_SYN_ALL		equ (TH_FIN or TH_SYN or TH_RST or TH_ACK)

TH_OPT_EOL		equ 0x00
TH_OPT_NOP		equ 0x01
TH_OPT_MSS		equ 0x02
TH_OPT_WS		equ 0x03
TH_OPT_SACK_PERMITTED	equ 0x04
TH_OPT_SACK		equ 0x05
TH_OPT_TS		equ 0x08

.pragma pack(push, 1)

TCP_OPT_MSS		STRUC
Kind			UINT8 ?
_Length			UINT8 ?
Mss			UINT16 ?
TCP_OPT_MSS		ENDS

TCP_OPT_WS		STRUC
Kind			UINT8 ?
_Length			UINT8 ?
ShiftCnt		UINT8 ?
TCP_OPT_WS		ENDS

TCP_OPT_SACK_PERMITTED	STRUC
Kind			UINT8 ?
_Length			UINT8 ?
TCP_OPT_SACK_PERMITTED	ENDS

TCP_OPT_SACK		STRUC
Kind			UINT8 ?
_Length			UINT8 ?
STRUC Block
 Left			SEQ_NUM ?
 Right			SEQ_NUM ?
ENDS
TCP_OPT_SACK		ENDS

TCP_OPT_TS		STRUC
Kind			UINT8 ?
_Length			UINT8 ?
Val			UINT32 ?
EcR			UINT32 ?
TCP_OPT_TS		ENDS

TCP_OPT_UNKNOWN		STRUC
Kind			UINT8 ?
_Length			UINT8 ?
TCP_OPT_UNKNOWN		ENDS

.pragma pack(pop)

include ifdef.inc

DL_TUNNEL_ADDRESS	STRUC
CompartmentId		dd ?;? COMPARTMENT_ID ?
ScopeId			SCOPE_ID <>
IpAddress		UCHAR 0 dup(?)
DL_TUNNEL_ADDRESS	ENDS
PDL_TUNNEL_ADDRESS	typedef ptr DL_TUNNEL_ADDRESS

DL_SIZEOF_TUNNEL_ADDRESS macro AddressBytes
	exitm<(FIELD_OFFSET(DL_TUNNEL_ADDRESS, IpAddress) + (AddressBytes))>
	endm

DL_SIZEOF_IPV4_TUNNEL_ADDRESS equ DL_SIZEOF_TUNNEL_ADDRESS(sizeof(IN_ADDR))
DL_SIZEOF_IPV6_TUNNEL_ADDRESS equ DL_SIZEOF_TUNNEL_ADDRESS(sizeof(IN6_ADDR))

if (DL_ADDRESS_LENGTH_MAXIMUM LT DL_SIZEOF_IPV4_TUNNEL_ADDRESS)
    .err<DL_SIZEOF_IPV4_TUNNEL_ADDRESS>
endif
if (DL_ADDRESS_LENGTH_MAXIMUM LT DL_SIZEOF_IPV6_TUNNEL_ADDRESS)
    .err<DL_SIZEOF_IPV6_TUNNEL_ADDRESS>
endif

TUNNEL_SUB_TYPE		typedef SDWORD
TUNNEL_SUB_TYPE_NONE	equ 0
TUNNEL_SUB_TYPE_CP	equ 1
TUNNEL_SUB_TYPE_IPTLS	equ 2
TUNNEL_SUB_TYPE_HA	equ 3

.pragma pack(push, 1)
DL_TEREDO_ADDRESS	STRUC
Reserved		UINT8 6 dup(?)
UNION
 Eui64			DL_EUI64 <>
 STRUC
  Flags			USHORT ?
  MappedPort		USHORT ?
  MappedAddress		IN_ADDR <>
 ENDS
ENDS
DL_TEREDO_ADDRESS	ENDS
PDL_TEREDO_ADDRESS	typedef ptr DL_TEREDO_ADDRESS

DL_TEREDO_ADDRESS_PRV	STRUC
Reserved		UINT8 6 dup(?)
UNION
 Eui64			DL_EUI64 <>
 STRUC
  Flags			USHORT ?
  MappedPort		USHORT ?
  MappedAddress		IN_ADDR <>
  LocalAddress		IN_ADDR <>
  InterfaceIndex	IF_INDEX ?
  LocalPort		USHORT ?
  DlDestination		DL_EUI48 <>
 ENDS
ENDS
DL_TEREDO_ADDRESS_PRV	ENDS
PDL_TEREDO_ADDRESS_PRV	typedef ptr DL_TEREDO_ADDRESS_PRV
.pragma pack(pop)

.pragma pack(push, 1)
IPTLS_METADATA		STRUC
SequenceNumber		ULONGLONG ?
IPTLS_METADATA		ENDS
PIPTLS_METADATA		typedef ptr IPTLS_METADATA
.pragma pack(pop)

if (DL_ADDRESS_LENGTH_MAXIMUM LT sizeof(DL_TEREDO_ADDRESS))
    .err<sizeof(DL_TEREDO_ADDRESS)>
endif

include ifdef.inc

NPI_MODULEID_TYPE	typedef SDWORD
MIT_GUID		equ 1
MIT_IF_LUID		equ 1

NPI_MODULEID		STRUC
_Length			USHORT ?
_Type			NPI_MODULEID_TYPE ?
UNION
 Guid			GUID <>
 IfLuid			LUID <>
ENDS
NPI_MODULEID		ENDS
PNPI_MODULEID		typedef ptr NPI_MODULEID

NPIID			typedef GUID
PNPIID			typedef ptr NPIID

externdef		NPI_MS_NMR_MODULEID:NPI_MODULEID

FL_PACKET_TYPE_FLAGS	equ (NDIS_PACKET_TYPE_ALL_MULTICAST or NDIS_PACKET_TYPE_PROMISCUOUS)

externdef		NPI_FRAMING_LAYER_ID:NPIID

externdef		NPI_MS_TUN_MODULEID:NPI_MODULEID
externdef		NPI_MS_FL48_MODULEID:NPI_MODULEID
externdef		NPI_MS_FL68_MODULEID:NPI_MODULEID
externdef		NPI_MS_FL4L_MODULEID:NPI_MODULEID
externdef		NPI_MS_FL6L_MODULEID:NPI_MODULEID
externdef		NPI_MS_FL4T_MODULEID:NPI_MODULEID
externdef		NPI_MS_FL6T_MODULEID:NPI_MODULEID
externdef		NPI_MS_WANARPV4_MODULEID:NPI_MODULEID
externdef		NPI_MS_WANARPV6_MODULEID:NPI_MODULEID
externdef		NPI_MS_FL_WANARP_MODULEID:NPI_MODULEID
externdef		NPI_MS_FLRDMA_MODULEID:NPI_MODULEID

externdef		NPI_MS_NDIS_MODULEID:NPI_MODULEID

externdef		NPI_NETWORK_LAYER_ID:NPIID

externdef		NPI_MS_IPV6_MODULEID:NPI_MODULEID
externdef		NPI_MS_IPV4_MODULEID:NPI_MODULEID

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

endif ;; _NETIODEF_
