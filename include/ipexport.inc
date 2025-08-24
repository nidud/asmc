ifndef IP_EXPORT_INCLUDED
define IP_EXPORT_INCLUDED 1

include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)


IPAddr	    typedef ULONG
IPMask	    typedef ULONG
IP_STATUS   typedef ULONG

include in6addr.inc

IPv6Addr typedef in6_addr

include inaddr.inc


ip_option_information	struct
Ttl			UCHAR ?
Tos			UCHAR ?
Flags			UCHAR ?
OptionsSize		UCHAR ?
OptionsData		PUCHAR ?
ip_option_information	ends
IP_OPTION_INFORMATION	typedef ip_option_information
PIP_OPTION_INFORMATION	typedef ptr ip_option_information

ifdef _WIN64

ip_option_information32 struct
Ttl			UCHAR ?
Tos			UCHAR ?
Flags			UCHAR ?
OptionsSize		UCHAR ?
OptionsData		ptr UCHAR ?
ip_option_information32 ends
IP_OPTION_INFORMATION32 typedef ip_option_information32
PIP_OPTION_INFORMATION32 typedef ptr ip_option_information32

endif

icmp_echo_reply		struct
Address			IPAddr ?
Status			ULONG ?
RoundTripTime		ULONG ?
DataSize		USHORT ?
Reserved		USHORT ?
Data			PVOID ?
Options			ip_option_information <>
icmp_echo_reply		ends
ICMP_ECHO_REPLY		typedef icmp_echo_reply
PICMP_ECHO_REPLY	typedef ptr icmp_echo_reply

ifdef _WIN64

icmp_echo_reply32	struct
Address			IPAddr ?
Status			ULONG ?
RoundTripTime		ULONG ?
DataSize		USHORT ?
Reserved		USHORT ?
Data			ptr ?
Options			ip_option_information32 <>
icmp_echo_reply32	ends
ICMP_ECHO_REPLY32	typedef icmp_echo_reply32
PICMP_ECHO_REPLY32	typedef ptr icmp_echo_reply32

endif

if (NTDDI_VERSION ge NTDDI_WINXP)

IPV6_ADDRESS_EX		struct
sin6_port		USHORT ?
sin6_flowinfo		ULONG ?
sin6_addr		USHORT 8 dup(?)
sin6_scope_id		ULONG ?
IPV6_ADDRESS_EX		ends
PIPV6_ADDRESS_EX	typedef ptr IPV6_ADDRESS_EX

icmpv6_echo_reply_lh	struct
Address			IPV6_ADDRESS_EX <>
Status			ULONG ?
RoundTripTime		dword ?
icmpv6_echo_reply_lh	ends
ICMPV6_ECHO_REPLY_LH	typedef icmpv6_echo_reply_lh
PICMPV6_ECHO_REPLY_LH	typedef ptr icmpv6_echo_reply_lh

ICMPV6_ECHO_REPLY	typedef ICMPV6_ECHO_REPLY_LH
PICMPV6_ECHO_REPLY	typedef ptr ICMPV6_ECHO_REPLY_LH

endif

arp_send_reply		struct
DestAddress		IPAddr ?
SrcAddress		IPAddr ?
arp_send_reply		ends
ARP_SEND_REPLY		typedef arp_send_reply
PARP_SEND_REPLY		typedef ptr arp_send_reply

tcp_reserve_port_range	struct
UpperRange		USHORT ?
LowerRange		USHORT ?
tcp_reserve_port_range	ends
TCP_RESERVE_PORT_RANGE	typedef tcp_reserve_port_range
PTCP_RESERVE_PORT_RANGE typedef ptr tcp_reserve_port_range

define MAX_ADAPTER_NAME 128

IP_ADAPTER_INDEX_MAP	struct
Index			ULONG ?
Name			WCHAR MAX_ADAPTER_NAME dup(?)
IP_ADAPTER_INDEX_MAP	ends
PIP_ADAPTER_INDEX_MAP	typedef ptr IP_ADAPTER_INDEX_MAP

IP_INTERFACE_INFO	struct
NumAdapters		LONG ?
Adapter			IP_ADAPTER_INDEX_MAP 1 dup(<>)
IP_INTERFACE_INFO	ends
PIP_INTERFACE_INFO	typedef ptr IP_INTERFACE_INFO

IP_UNIDIRECTIONAL_ADAPTER_ADDRESS struct
NumAdapters		ULONG ?
Address			IPAddr 1 dup(?)
IP_UNIDIRECTIONAL_ADAPTER_ADDRESS ends
PIP_UNIDIRECTIONAL_ADAPTER_ADDRESS typedef ptr IP_UNIDIRECTIONAL_ADAPTER_ADDRESS

IP_ADAPTER_ORDER_MAP	struct
NumAdapters		ULONG ?
AdapterOrder		ULONG 1 dup(?)
IP_ADAPTER_ORDER_MAP	ends
PIP_ADAPTER_ORDER_MAP	typedef ptr IP_ADAPTER_ORDER_MAP

IP_MCAST_COUNTER_INFO	struct
InMcastOctets		ULONG64 ?
OutMcastOctets		ULONG64 ?
InMcastPkts		ULONG64 ?
OutMcastPkts		ULONG64 ?
IP_MCAST_COUNTER_INFO	ends
PIP_MCAST_COUNTER_INFO	typedef ptr IP_MCAST_COUNTER_INFO

define IP_STATUS_BASE		   11000

define IP_SUCCESS		   0
define IP_BUF_TOO_SMALL		   (IP_STATUS_BASE + 1)
define IP_DEST_NET_UNREACHABLE	   (IP_STATUS_BASE + 2)
define IP_DEST_HOST_UNREACHABLE	   (IP_STATUS_BASE + 3)
define IP_DEST_PROT_UNREACHABLE	   (IP_STATUS_BASE + 4)
define IP_DEST_PORT_UNREACHABLE	   (IP_STATUS_BASE + 5)
define IP_NO_RESOURCES		   (IP_STATUS_BASE + 6)
define IP_BAD_OPTION		   (IP_STATUS_BASE + 7)
define IP_HW_ERROR		   (IP_STATUS_BASE + 8)
define IP_PACKET_TOO_BIG	   (IP_STATUS_BASE + 9)
define IP_REQ_TIMED_OUT		   (IP_STATUS_BASE + 10)
define IP_BAD_REQ		   (IP_STATUS_BASE + 11)
define IP_BAD_ROUTE		   (IP_STATUS_BASE + 12)
define IP_TTL_EXPIRED_TRANSIT	   (IP_STATUS_BASE + 13)
define IP_TTL_EXPIRED_REASSEM	   (IP_STATUS_BASE + 14)
define IP_PARAM_PROBLEM		   (IP_STATUS_BASE + 15)
define IP_SOURCE_QUENCH		   (IP_STATUS_BASE + 16)
define IP_OPTION_TOO_BIG	   (IP_STATUS_BASE + 17)
define IP_BAD_DESTINATION	   (IP_STATUS_BASE + 18)

define IP_DEST_NO_ROUTE		   (IP_STATUS_BASE + 2)
define IP_DEST_ADDR_UNREACHABLE	   (IP_STATUS_BASE + 3)
define IP_DEST_PROHIBITED	   (IP_STATUS_BASE + 4)
define IP_DEST_PORT_UNREACHABLE	   (IP_STATUS_BASE + 5)
define IP_HOP_LIMIT_EXCEEDED	   (IP_STATUS_BASE + 13)
define IP_REASSEMBLY_TIME_EXCEEDED (IP_STATUS_BASE + 14)
define IP_PARAMETER_PROBLEM	   (IP_STATUS_BASE + 15)

define IP_DEST_UNREACHABLE	   (IP_STATUS_BASE + 40)
define IP_TIME_EXCEEDED		   (IP_STATUS_BASE + 41)
define IP_BAD_HEADER		   (IP_STATUS_BASE + 42)
define IP_UNRECOGNIZED_NEXT_HEADER (IP_STATUS_BASE + 43)
define IP_ICMP_ERROR		   (IP_STATUS_BASE + 44)
define IP_DEST_SCOPE_MISMATCH	   (IP_STATUS_BASE + 45)

define IP_ADDR_DELETED		   (IP_STATUS_BASE + 19)
define IP_SPEC_MTU_CHANGE	   (IP_STATUS_BASE + 20)
define IP_MTU_CHANGE		   (IP_STATUS_BASE + 21)
define IP_UNLOAD		   (IP_STATUS_BASE + 22)
define IP_ADDR_ADDED		   (IP_STATUS_BASE + 23)
define IP_MEDIA_CONNECT		   (IP_STATUS_BASE + 24)
define IP_MEDIA_DISCONNECT	   (IP_STATUS_BASE + 25)
define IP_BIND_ADAPTER		   (IP_STATUS_BASE + 26)
define IP_UNBIND_ADAPTER	   (IP_STATUS_BASE + 27)
define IP_DEVICE_DOES_NOT_EXIST	   (IP_STATUS_BASE + 28)
define IP_DUPLICATE_ADDRESS	   (IP_STATUS_BASE + 29)
define IP_INTERFACE_METRIC_CHANGE  (IP_STATUS_BASE + 30)
define IP_RECONFIG_SECFLTR	   (IP_STATUS_BASE + 31)
define IP_NEGOTIATING_IPSEC	   (IP_STATUS_BASE + 32)
define IP_INTERFACE_WOL_CAPABILITY_CHANGE  (IP_STATUS_BASE + 33)
define IP_DUPLICATE_IPADD	   (IP_STATUS_BASE + 34)

define IP_GENERAL_FAILURE	   (IP_STATUS_BASE + 50)
define MAX_IP_STATUS		   IP_GENERAL_FAILURE
define IP_PENDING		   (IP_STATUS_BASE + 255)

define IP_FLAG_REVERSE 0x1
define IP_FLAG_DF      0x2

define IP_OPT_EOL      0
define IP_OPT_NOP      1
define IP_OPT_SECURITY 0x82
define IP_OPT_LSRR     0x83
define IP_OPT_SSRR     0x89
define IP_OPT_RR       0x7
define IP_OPT_TS       0x44
define IP_OPT_SID      0x88
define IP_OPT_ROUTER_ALERT 0x94

define MAX_OPT_SIZE    40

ifdef CHICAGO

define IOCTL_IP_RTCHANGE_NOTIFY_REQUEST	  101
define IOCTL_IP_ADDCHANGE_NOTIFY_REQUEST  102
define IOCTL_ARP_SEND_REQUEST		  103
define IOCTL_IP_INTERFACE_INFO		  104
define IOCTL_IP_GET_BEST_INTERFACE	  105
define IOCTL_IP_UNIDIRECTIONAL_ADAPTER_ADDRESS	      106

endif

endif

endif
