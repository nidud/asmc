ifndef _NLDEF_
define _NLDEF_

include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

NL_MAX_METRIC_COMPONENT equ ((1 SHL 31) - 1)

IpPrefixOriginOther	equ 0
IpPrefixOriginManual	equ 1
IpPrefixOriginWellKnown equ 2
IpPrefixOriginDhcp	equ 3
IpPrefixOriginRouterAdvertisement equ 4
IpPrefixOriginUnchanged equ 1 shl 4

NlpoOther		equ <IpPrefixOriginOther>
NlpoManual		equ <IpPrefixOriginManual>
NlpoWellKnown		equ <IpPrefixOriginWellKnown>
NlpoDhcp		equ <IpPrefixOriginDhcp>
NlpoRouterAdvertisement equ <IpPrefixOriginRouterAdvertisement>

NlsoOther		equ 0
NlsoManual		equ 1
NlsoWellKnown		equ 2
NlsoDhcp		equ 3
NlsoLinkLayerAddress	equ 4
NlsoRandom		equ 5
IpSuffixOriginOther	equ 0
IpSuffixOriginManual	equ 7
IpSuffixOriginWellKnown equ 8
IpSuffixOriginDhcp	equ 9
IpSuffixOriginLinkLayerAddress equ 10
IpSuffixOriginRandom	equ 11
IpSuffixOriginUnchanged equ 1 shl 4

NldsInvalid		equ 0
NldsTentative		equ 1
NldsDuplicate		equ 2
NldsDeprecated		equ 3
NldsPreferred		equ 4
IpDadStateInvalid	equ 0
IpDadStateTentative	equ 6
IpDadStateDuplicate	equ 7
IpDadStateDeprecated	equ 8
IpDadStatePreferred	equ 9

MAKE_ROUTE_PROTOCOL macro suffix, value
    MIB_IPPROTO_&suffix& equ value
    PROTO_IP_&suffix&	 equ value
    exitm<>
    endm

RouteProtocolOther	equ 1
RouteProtocolLocal	equ 2
RouteProtocolNetMgmt	equ 3
RouteProtocolIcmp	equ 4
RouteProtocolEgp	equ 5
RouteProtocolGgp	equ 6
RouteProtocolHello	equ 7
RouteProtocolRip	equ 8
RouteProtocolIsIs	equ 9
RouteProtocolEsIs	equ 10
RouteProtocolCisco	equ 11
RouteProtocolBbn	equ 12
RouteProtocolOspf	equ 13
RouteProtocolBgp	equ 14
RouteProtocolIdpr	equ 15
RouteProtocolEigrp	equ 16
RouteProtocolDvmrp	equ 17
RouteProtocolRpl	equ 18
RouteProtocolDhcp	equ 19
MAKE_ROUTE_PROTOCOL(OTHER, 19)
MAKE_ROUTE_PROTOCOL(LOCAL, 20)
MAKE_ROUTE_PROTOCOL(NETMGMT, 21)
MAKE_ROUTE_PROTOCOL(ICMP, 22)
MAKE_ROUTE_PROTOCOL(EGP, 23)
MAKE_ROUTE_PROTOCOL(GGP, 24)
MAKE_ROUTE_PROTOCOL(HELLO, 25)
MAKE_ROUTE_PROTOCOL(RIP, 26)
MAKE_ROUTE_PROTOCOL(IS_IS, 27)
MAKE_ROUTE_PROTOCOL(ES_IS, 28)
MAKE_ROUTE_PROTOCOL(CISCO, 29)
MAKE_ROUTE_PROTOCOL(BBN, 30)
MAKE_ROUTE_PROTOCOL(OSPF, 31)
MAKE_ROUTE_PROTOCOL(BGP, 32)
MAKE_ROUTE_PROTOCOL(IDPR, 33)
MAKE_ROUTE_PROTOCOL(EIGRP, 34)
MAKE_ROUTE_PROTOCOL(DVMRP, 35)
MAKE_ROUTE_PROTOCOL(RPL, 36)
MAKE_ROUTE_PROTOCOL(DHCP, 37)
MAKE_ROUTE_PROTOCOL(NT_AUTOSTATIC, 38)
MAKE_ROUTE_PROTOCOL(NT_STATIC, 39)
MAKE_ROUTE_PROTOCOL(NT_STATIC_NON_DOD, 40)

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)


NlatUnspecified		equ 0
NlatUnicast		equ 1
NlatAnycast		equ 2
NlatMulticast		equ 3
NlatBroadcast		equ 4
NlatInvalid		equ 5

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

NL_ROUTE_ORIGIN		typedef SDWORD
NlroManual		equ 0
NlroWellKnown		equ 1
NlroDHCP		equ 2
NlroRouterAdvertisement equ 3
Nlro6to4		equ 4

NL_NEIGHBOR_STATE	typedef SDWORD
NlnsUnreachable		equ 0
NlnsIncomplete		equ 1
NlnsProbe		equ 2
NlnsDelay		equ 3
NlnsStale		equ 4
NlnsReachable		equ 5
NlnsPermanent		equ 6
NlnsMaximum		equ 7

NL_LINK_LOCAL_ADDRESS_BEHAVIOR typedef SDWORD
LinkLocalAlwaysOff	equ 0
LinkLocalDelayed	equ 1
LinkLocalAlwaysOn	equ 2
LinkLocalUnchanged	equ -1

NL_INTERFACE_OFFLOAD_ROD  STRUC
flags			BOOLEAN ?
;NlChecksumSupported : 1 BOOLEAN ?
;NlOptionsSupported : 1	 BOOLEAN ?
;TlDatagramChecksumSupported : 1 BOOLEAN ?
;TlStreamChecksumSupported : 1 BOOLEAN ?
;TlStreamOptionsSupported : 1 BOOLEAN ?
;FastPathCompatible : 1	 BOOLEAN ?
;TlLargeSendOffloadSupported : 1 BOOLEAN ?
;TlGiantSendOffloadSupported : 1 BOOLEAN ?
NL_INTERFACE_OFFLOAD_ROD ENDS
PNL_INTERFACE_OFFLOAD_ROD typedef ptr NL_INTERFACE_OFFLOAD_ROD


NL_ROUTER_DISCOVERY_BEHAVIOR typedef SDWORD
RouterDiscoveryDisabled equ 0
RouterDiscoveryEnabled	equ 1
RouterDiscoveryDhcp	equ 2
RouterDiscoveryUnchanged equ -1

NL_BANDWIDTH_FLAG	typedef SDWORD
NlbwDisabled		equ 0
NlbwEnabled		equ 1
NlbwUnchanged		equ -1

NL_PATH_BANDWIDTH_ROD	STRUC
Bandwidth		ULONG64 ?
Instability		ULONG64 ?
BandwidthPeaked		BOOLEAN ?
NL_PATH_BANDWIDTH_ROD	ENDS
PNL_PATH_BANDWIDTH_ROD	typedef ptr NL_PATH_BANDWIDTH_ROD

NL_NETWORK_CATEGORY	typedef SDWORD
NetworkCategoryPublic	equ 0
NetworkCategoryPrivate	equ 1
NetworkCategoryDomainAuthenticated equ 2
NetworkCategoryUnchanged equ -1
NetworkCategoryUnknown	equ -1

NL_INTERFACE_NETWORK_CATEGORY_STATE typedef SDWORD
NlincCategoryUnknown	equ 0
NlincPublic		equ 1
NlincPrivate		equ 2
NlincDomainAuthenticated equ 3
NlincCategoryStateMax	equ 4

NET_IF_CURRENT_SESSION	equ (-1)

NL_BANDWIDTH_INFORMATION  STRUC
Bandwidth		ULONG64 ?
Instability		ULONG64 ?
BandwidthPeaked		BOOLEAN ?
NL_BANDWIDTH_INFORMATION ENDS
PNL_BANDWIDTH_INFORMATION typedef ptr NL_BANDWIDTH_INFORMATION

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

endif ;; _NLDEF_

