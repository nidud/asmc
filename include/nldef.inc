ifndef _NLDEF_
define _NLDEF_

include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

.enum NL_PREFIX_ORIGIN {
    IpPrefixOriginOther = 0,
    IpPrefixOriginManual,
    IpPrefixOriginWellKnown,
    IpPrefixOriginDhcp,
    IpPrefixOriginRouterAdvertisement,
    IpPrefixOriginUnchanged = 1 shl 4
    }

define NlpoOther	       <IpPrefixOriginOther>
define NlpoManual	       <IpPrefixOriginManual>
define NlpoWellKnown	       <IpPrefixOriginWellKnown>
define NlpoDhcp		       <IpPrefixOriginDhcp>
define NlpoRouterAdvertisement <IpPrefixOriginRouterAdvertisement>

.enum NL_SUFFIX_ORIGIN {
    NlsoOther = 0,
    NlsoManual,
    NlsoWellKnown,
    NlsoDhcp,
    NlsoLinkLayerAddress,
    NlsoRandom,

    IpSuffixOriginOther = 0,
    IpSuffixOriginManual = 7,
    IpSuffixOriginWellKnown = 8,
    IpSuffixOriginDhcp = 9,
    IpSuffixOriginLinkLayerAddress = 10,
    IpSuffixOriginRandom = 11,
    IpSuffixOriginUnchanged = 1 shl 4
    }

.enum NL_DAD_STATE {
    NldsInvalid,
    NldsTentative,
    NldsDuplicate,
    NldsDeprecated,
    NldsPreferred,

    IpDadStateInvalid = 0,
    IpDadStateTentative = 6,
    IpDadStateDuplicate = 7,
    IpDadStateDeprecated = 8,
    IpDadStatePreferred = 9
    }


define NL_MAX_METRIC_COMPONENT ((1 shl 31) - 1)

MAKE_ROUTE_PROTOCOL macro suffix, value
    exitm<MIB_IPPROTO_&suffix& = value, PROTO_IP_&suffix& = value>
    endm

.enum NL_ROUTE_PROTOCOL {
    RouteProtocolOther	 = 1,
    RouteProtocolLocal	 = 2,
    RouteProtocolNetMgmt = 3,
    RouteProtocolIcmp	 = 4,
    RouteProtocolEgp	 = 5,
    RouteProtocolGgp	 = 6,
    RouteProtocolHello	 = 7,
    RouteProtocolRip	 = 8,
    RouteProtocolIsIs	 = 9,
    RouteProtocolEsIs	 = 10,
    RouteProtocolCisco	 = 11,
    RouteProtocolBbn	 = 12,
    RouteProtocolOspf	 = 13,
    RouteProtocolBgp	 = 14,
    RouteProtocolIdpr	 = 15,
    RouteProtocolEigrp	 = 16,
    RouteProtocolDvmrp	 = 17,
    RouteProtocolRpl	 = 18,
    RouteProtocolDhcp	 = 19,

    MAKE_ROUTE_PROTOCOL(OTHER,	 1),
    MAKE_ROUTE_PROTOCOL(LOCAL,	 2),
    MAKE_ROUTE_PROTOCOL(NETMGMT, 3),
    MAKE_ROUTE_PROTOCOL(ICMP,	 4),
    MAKE_ROUTE_PROTOCOL(EGP,	 5),
    MAKE_ROUTE_PROTOCOL(GGP,	 6),
    MAKE_ROUTE_PROTOCOL(HELLO,	 7),
    MAKE_ROUTE_PROTOCOL(RIP,	 8),
    MAKE_ROUTE_PROTOCOL(IS_IS,	 9),
    MAKE_ROUTE_PROTOCOL(ES_IS,	10),
    MAKE_ROUTE_PROTOCOL(CISCO,	11),
    MAKE_ROUTE_PROTOCOL(BBN,	12),
    MAKE_ROUTE_PROTOCOL(OSPF,	13),
    MAKE_ROUTE_PROTOCOL(BGP,	14),
    MAKE_ROUTE_PROTOCOL(IDPR,	15),
    MAKE_ROUTE_PROTOCOL(EIGRP,	16),
    MAKE_ROUTE_PROTOCOL(DVMRP,	17),
    MAKE_ROUTE_PROTOCOL(RPL,	18),
    MAKE_ROUTE_PROTOCOL(DHCP,	19),

    MAKE_ROUTE_PROTOCOL(NT_AUTOSTATIC,	   10002),
    MAKE_ROUTE_PROTOCOL(NT_STATIC,	   10006),
    MAKE_ROUTE_PROTOCOL(NT_STATIC_NON_DOD, 10007)
    }
PNL_ROUTE_PROTOCOL typedef ptr NL_ROUTE_PROTOCOL

endif

.enum NL_ADDRESS_TYPE {
    NlatUnspecified,
    NlatUnicast,
    NlatAnycast,
    NlatMulticast,
    NlatBroadcast,
    NlatInvalid
    }

PNL_ADDRESS_TYPE typedef ptr NL_ADDRESS_TYPE


if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

.enum NL_ROUTE_ORIGIN {
    NlroManual,
    NlroWellKnown,
    NlroDHCP,
    NlroRouterAdvertisement,
    Nlro6to4,
    }

PNL_ROUTE_ORIGIN	typedef ptr NL_ROUTE_ORIGIN

.enum NL_NEIGHBOR_STATE {
    NlnsUnreachable,
    NlnsIncomplete,
    NlnsProbe,
    NlnsDelay,
    NlnsStale,
    NlnsReachable,
    NlnsPermanent,
    NlnsMaximum,
    }
PNL_NEIGHBOR_STATE	typedef ptr NL_NEIGHBOR_STATE


.enum NL_LINK_LOCAL_ADDRESS_BEHAVIOR {
    LinkLocalAlwaysOff = 0,
    LinkLocalDelayed,
    LinkLocalAlwaysOn,
    LinkLocalUnchanged = -1
    }


NL_INTERFACE_OFFLOAD_ROD STRUC
RECORD
 NlChecksumSupported		BOOLEAN : 1 ?
 NlOptionsSupported		BOOLEAN : 1 ?
 TlDatagramChecksumSupported	BOOLEAN : 1 ?
 TlStreamChecksumSupported	BOOLEAN : 1 ?
 TlStreamOptionsSupported	BOOLEAN : 1 ?
 FastPathCompatible		BOOLEAN : 1 ?
 TlLargeSendOffloadSupported	BOOLEAN : 1 ?
 TlGiantSendOffloadSupported	BOOLEAN : 1 ?
ENDS
NL_INTERFACE_OFFLOAD_ROD ENDS
PNL_INTERFACE_OFFLOAD_ROD typedef ptr NL_INTERFACE_OFFLOAD_ROD

.enum NL_ROUTER_DISCOVERY_BEHAVIOR {
    RouterDiscoveryDisabled = 0,
    RouterDiscoveryEnabled,
    RouterDiscoveryDhcp,
    RouterDiscoveryUnchanged = -1
    }

.enum NL_BANDWIDTH_FLAG {
    NlbwDisabled = 0,
    NlbwEnabled,
    NlbwUnchanged = -1
    }
PNL_BANDWIDTH_FLAG	typedef ptr NL_BANDWIDTH_FLAG


NL_PATH_BANDWIDTH_ROD	STRUC
Bandwidth		ULONG64 ?
Instability		ULONG64 ?
BandwidthPeaked		BOOLEAN ?
NL_PATH_BANDWIDTH_ROD	ENDS
PNL_PATH_BANDWIDTH_ROD	typedef ptr NL_PATH_BANDWIDTH_ROD

.enum NL_NETWORK_CATEGORY {
    NetworkCategoryPublic,
    NetworkCategoryPrivate,
    NetworkCategoryDomainAuthenticated,
    NetworkCategoryUnchanged = -1,
    NetworkCategoryUnknown = -1
    }
PNL_NETWORK_CATEGORY	typedef ptr NL_NETWORK_CATEGORY

.enum NL_INTERFACE_NETWORK_CATEGORY_STATE {
    NlincCategoryUnknown = 0,
    NlincPublic = 1,
    NlincPrivate = 2,
    NlincDomainAuthenticated = 3,
    NlincCategoryStateMax
    }
PNL_INTERFACE_NETWORK_CATEGORY_STATE typedef ptr NL_INTERFACE_NETWORK_CATEGORY_STATE

.enum NL_NETWORK_CONNECTIVITY_LEVEL_HINT {
    NetworkConnectivityLevelHintUnknown = 0,
    NetworkConnectivityLevelHintNone,
    NetworkConnectivityLevelHintLocalAccess,
    NetworkConnectivityLevelHintInternetAccess,
    NetworkConnectivityLevelHintConstrainedInternetAccess,
    NetworkConnectivityLevelHintHidden,
    }

.enum NL_NETWORK_CONNECTIVITY_COST_HINT {
    NetworkConnectivityCostHintUnknown = 0,
    NetworkConnectivityCostHintUnrestricted,
    NetworkConnectivityCostHintFixed,
    NetworkConnectivityCostHintVariable,
    }

NL_NETWORK_CONNECTIVITY_HINT STRUC
ConnectivityLevel	NL_NETWORK_CONNECTIVITY_LEVEL_HINT ?
ConnectivityCost	NL_NETWORK_CONNECTIVITY_COST_HINT ?
ApproachingDataLimit	BOOLEAN ?
OverDataLimit		BOOLEAN ?
Roaming			BOOLEAN ?
NL_NETWORK_CONNECTIVITY_HINT ENDS

define NET_IF_CURRENT_SESSION (-1)

NL_BANDWIDTH_INFORMATION STRUC
Bandwidth		ULONG64 ?
Instability		ULONG64 ?
BandwidthPeaked		BOOLEAN ?
NL_BANDWIDTH_INFORMATION ENDS
PNL_BANDWIDTH_INFORMATION typedef ptr NL_BANDWIDTH_INFORMATION

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

endif ;; _NLDEF_
