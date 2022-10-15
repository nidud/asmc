ifndef _IPMIB_
define _IPMIB_

include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

ifndef ANY_SIZE
define ANY_SIZE 1
endif

include ifmib.inc
include nldef.inc

ifdef _MSC_VER

define MIB_IPADDR_PRIMARY      0x0001
define MIB_IPADDR_DYNAMIC      0x0004
define MIB_IPADDR_DISCONNECTED 0x0008
define MIB_IPADDR_DELETED      0x0040
define MIB_IPADDR_TRANSIENT    0x0080
define MIB_IPADDR_DNS_ELIGIBLE 0

_MIB_IPADDRROW_XP       struct
dwAddr                  DWORD ?
dwIndex                 IF_INDEX ?
dwMask                  DWORD ?
dwBCastAddr             DWORD ?
dwReasmSize             DWORD ?
unused1                 word ?
wType                   word ?
_MIB_IPADDRROW_XP       ends
MIB_IPADDRROW_XP        typedef _MIB_IPADDRROW_XP
PMIB_IPADDRROW_XP       typedef ptr _MIB_IPADDRROW_XP

_MIB_IPADDRROW_W2K      struct
dwAddr                  DWORD ?
dwIndex                 DWORD ?
dwMask                  DWORD ?
dwBCastAddr             DWORD ?
dwReasmSize             DWORD ?
unused1                 word ?
unused2                 word ?
_MIB_IPADDRROW_W2K      ends
MIB_IPADDRROW_W2K       typedef _MIB_IPADDRROW_W2K
PMIB_IPADDRROW_W2K      typedef ptr _MIB_IPADDRROW_W2K

if (NTDDI_VERSION ge NTDDI_WINXP)
MIB_IPADDRROW           typedef MIB_IPADDRROW_XP
PMIB_IPADDRROW          typedef ptr MIB_IPADDRROW_XP
elseif (NTDDI_VERSION ge NTDDI_WIN2K)
MIB_IPADDRROW           typedef MIB_IPADDRROW_W2K
PMIB_IPADDRROW          typedef ptr MIB_IPADDRROW_W2K
else
MIB_IPADDRROW           typedef MIB_IPADDRROW_XP
PMIB_IPADDRROW          typedef ptr MIB_IPADDRROW_XP
endif

_MIB_IPADDRTABLE        struct
dwNumEntries            DWORD ?
table                   MIB_IPADDRROW ANY_SIZE dup(<>)
_MIB_IPADDRTABLE        ends
MIB_IPADDRTABLE         typedef _MIB_IPADDRTABLE
PMIB_IPADDRTABLE        typedef ptr _MIB_IPADDRTABLE

SIZEOF_IPADDRTABLE macro X
  exitm<(FIELD_OFFSET(MIB_IPADDRTABLE,table) + ((X) * sizeof(MIB_IPADDRROW)) + ALIGN_SIZE)>
  endm

_MIB_IPFORWARDNUMBER    struct
dwValue                 DWORD ?
_MIB_IPFORWARDNUMBER    ends
MIB_IPFORWARDNUMBER     typedef _MIB_IPFORWARDNUMBER
PMIB_IPFORWARDNUMBER    typedef ptr _MIB_IPFORWARDNUMBER

MIB_IPFORWARD_PROTO     typedef NL_ROUTE_PROTOCOL

.enum MIB_IPFORWARD_TYPE {
    MIB_IPROUTE_TYPE_OTHER    = 1,
    MIB_IPROUTE_TYPE_INVALID  = 2,
    MIB_IPROUTE_TYPE_DIRECT   = 3,
    MIB_IPROUTE_TYPE_INDIRECT = 4,
    }

_MIB_IPFORWARDROW       struct
dwForwardDest           DWORD ?
dwForwardMask           DWORD ?
dwForwardPolicy         DWORD ?
dwForwardNextHop        DWORD ?
dwForwardIfIndex        IF_INDEX ?
union
 dwForwardType          DWORD ?
 ForwardType            MIB_IPFORWARD_TYPE ?
ends
union
 dwForwardProto         DWORD ?
 ForwardProto           MIB_IPFORWARD_PROTO ?
ends
dwForwardAge            DWORD ?
dwForwardNextHopAS      DWORD ?
dwForwardMetric1        DWORD ?
dwForwardMetric2        DWORD ?
dwForwardMetric3        DWORD ?
dwForwardMetric4        DWORD ?
dwForwardMetric5        DWORD ?
_MIB_IPFORWARDROW       ends
MIB_IPFORWARDROW        typedef _MIB_IPFORWARDROW
PMIB_IPFORWARDROW       typedef ptr _MIB_IPFORWARDROW

define MIB_IPROUTE_TYPE_OTHER    1
define MIB_IPROUTE_TYPE_INVALID  2
define MIB_IPROUTE_TYPE_DIRECT   3
define MIB_IPROUTE_TYPE_INDIRECT 4

define MIB_IPROUTE_METRIC_UNUSED    -1

_MIB_IPFORWARDTABLE     struct
dwNumEntries            DWORD ?
table                   MIB_IPFORWARDROW ANY_SIZE dup(<>)
_MIB_IPFORWARDTABLE     ends
MIB_IPFORWARDTABLE      typedef _MIB_IPFORWARDTABLE
PMIB_IPFORWARDTABLE     typedef ptr _MIB_IPFORWARDTABLE

SIZEOF_IPFORWARDTABLE macro X
    (FIELD_OFFSET(MIB_IPFORWARDTABLE,table[0]) +
    ((X) * sizeof(MIB_IPFORWARDROW)) + ALIGN_SIZE)
  exitm<>
  endm

.enum MIB_IPNET_TYPE {
    MIB_IPNET_TYPE_OTHER   = 1,
    MIB_IPNET_TYPE_INVALID = 2,
    MIB_IPNET_TYPE_DYNAMIC = 3,
    MIB_IPNET_TYPE_STATIC  = 4,
    }

_MIB_IPNETROW_LH        struct
dwIndex                 IF_INDEX ?
dwPhysAddrLen           DWORD ?
bPhysAddr               UCHAR MAXLEN_PHYSADDR dup(?)
dwAddr                  DWORD ?
union
 dwType                 DWORD ?
 Type                   MIB_IPNET_TYPE ?
ends
_MIB_IPNETROW_LH        ends
MIB_IPNETROW_LH         typedef _MIB_IPNETROW_LH
PMIB_IPNETROW_LH        typedef ptr _MIB_IPNETROW_LH

_MIB_IPNETROW_W2K       struct
dwIndex                 IF_INDEX ?
dwPhysAddrLen           DWORD ?
bPhysAddr               UCHAR MAXLEN_PHYSADDR dup(?)
dwAddr                  DWORD ?
dwType                  DWORD ?
_MIB_IPNETROW_W2K       ends
MIB_IPNETROW_W2K        typedef _MIB_IPNETROW_W2K
PMIB_IPNETROW_W2K       typedef ptr _MIB_IPNETROW_W2K

if (NTDDI_VERSION ge NTDDI_VISTA)
MIB_IPNETROW            typedef MIB_IPNETROW_LH
PMIB_IPNETROW           typedef ptr MIB_IPNETROW_LH
elseif (NTDDI_VERSION ge NTDDI_WIN2K)
MIB_IPNETROW            typedef MIB_IPNETROW_W2K
PMIB_IPNETROW           typedef ptr MIB_IPNETROW_W2K
else
MIB_IPNETROW            typedef MIB_IPNETROW_LH
PMIB_IPNETROW           typedef ptr MIB_IPNETROW_LH
endif

_MIB_IPNETTABLE         struct
dwNumEntries            DWORD ?
table                   MIB_IPNETROW ANY_SIZE dup(<>)
_MIB_IPNETTABLE         ends
MIB_IPNETTABLE          typedef _MIB_IPNETTABLE
PMIB_IPNETTABLE         typedef ptr _MIB_IPNETTABLE

SIZEOF_IPNETTABLE macro X
  exitm<(FIELD_OFFSET(MIB_IPNETTABLE, table) + ((X) * sizeof(MIB_IPNETROW)) + ALIGN_SIZE)>
  endm

.enum MIB_IPSTATS_FORWARDING {
    MIB_IP_FORWARDING     = 1,
    MIB_IP_NOT_FORWARDING = 2,
    }

define MIB_USE_CURRENT_TTL         (-1)
define MIB_USE_CURRENT_FORWARDING  (-1)

_MIB_IPSTATS_LH         struct
union
 dwForwarding           DWORD ?
 Forwarding             MIB_IPSTATS_FORWARDING ?
ends
dwDefaultTTL            DWORD ?
dwInReceives            DWORD ?
dwInHdrErrors           DWORD ?
dwInAddrErrors          DWORD ?
dwForwDatagrams         DWORD ?
dwInUnknownProtos       DWORD ?
dwInDiscards            DWORD ?
dwInDelivers            DWORD ?
dwOutRequests           DWORD ?
dwRoutingDiscards       DWORD ?
dwOutDiscards           DWORD ?
dwOutNoRoutes           DWORD ?
dwReasmTimeout          DWORD ?
dwReasmReqds            DWORD ?
dwReasmOks              DWORD ?
dwReasmFails            DWORD ?
dwFragOks               DWORD ?
dwFragFails             DWORD ?
dwFragCreates           DWORD ?
dwNumIf                 DWORD ?
dwNumAddr               DWORD ?
dwNumRoutes             DWORD ?
_MIB_IPSTATS_LH         ends
MIB_IPSTATS_LH          typedef _MIB_IPSTATS_LH
PMIB_IPSTATS_LH         typedef ptr _MIB_IPSTATS_LH

_MIB_IPSTATS_W2K        struct
dwForwarding            DWORD ?
dwDefaultTTL            DWORD ?
dwInReceives            DWORD ?
dwInHdrErrors           DWORD ?
dwInAddrErrors          DWORD ?
dwForwDatagrams         DWORD ?
dwInUnknownProtos       DWORD ?
dwInDiscards            DWORD ?
dwInDelivers            DWORD ?
dwOutRequests           DWORD ?
dwRoutingDiscards       DWORD ?
dwOutDiscards           DWORD ?
dwOutNoRoutes           DWORD ?
dwReasmTimeout          DWORD ?
dwReasmReqds            DWORD ?
dwReasmOks              DWORD ?
dwReasmFails            DWORD ?
dwFragOks               DWORD ?
dwFragFails             DWORD ?
dwFragCreates           DWORD ?
dwNumIf                 DWORD ?
dwNumAddr               DWORD ?
dwNumRoutes             DWORD ?
_MIB_IPSTATS_W2K        ends
MIB_IPSTATS_W2K         typedef _MIB_IPSTATS_W2K
PMIB_IPSTATS_W2K        typedef ptr _MIB_IPSTATS_W2K

if (NTDDI_VERSION ge NTDDI_VISTA)
MIB_IPSTATS             typedef MIB_IPSTATS_LH
PMIB_IPSTATS            typedef ptr MIB_IPSTATS_LH
elseif (NTDDI_VERSION ge NTDDI_WIN2K)
MIB_IPSTATS             typedef MIB_IPSTATS_W2K
PMIB_IPSTATS            typedef ptr MIB_IPSTATS_W2K
endif

_MIBICMPSTATS           struct
dwMsgs                  DWORD ?
dwErrors                DWORD ?
dwDestUnreachs          DWORD ?
dwTimeExcds             DWORD ?
dwParmProbs             DWORD ?
dwSrcQuenchs            DWORD ?
dwRedirects             DWORD ?
dwEchos                 DWORD ?
dwEchoReps              DWORD ?
dwTimestamps            DWORD ?
dwTimestampReps         DWORD ?
dwAddrMasks             DWORD ?
dwAddrMaskReps          DWORD ?
_MIBICMPSTATS           ends
MIBICMPSTATS            typedef _MIBICMPSTATS
PMIBICMPSTATS           typedef ptr _MIBICMPSTATS

_MIBICMPINFO            struct
icmpInStats             MIBICMPSTATS <>
icmpOutStats            MIBICMPSTATS <>
_MIBICMPINFO            ends
MIBICMPINFO             typedef _MIBICMPINFO

_MIB_ICMP               struct
stats                   MIBICMPINFO <>
_MIB_ICMP               ends
MIB_ICMP                typedef _MIB_ICMP
PMIB_ICMP               typedef ptr _MIB_ICMP

_MIBICMPSTATS_EX_XPSP1  struct
dwMsgs                  DWORD ?
dwErrors                DWORD ?
rgdwTypeCount           DWORD 256 dup(?)
_MIBICMPSTATS_EX_XPSP1  ends
MIBICMPSTATS_EX_XPSP1   typedef _MIBICMPSTATS_EX_XPSP1
PMIBICMPSTATS_EX_XPSP1  typedef ptr _MIBICMPSTATS_EX_XPSP1

MIBICMPSTATS_EX         typedef MIBICMPSTATS_EX_XPSP1
PMIBICMPSTATS_EX        typedef ptr MIBICMPSTATS_EX_XPSP1

_MIB_ICMP_EX_XPSP1      struct
icmpInStats             MIBICMPSTATS_EX <>
icmpOutStats            MIBICMPSTATS_EX <>
_MIB_ICMP_EX_XPSP1      ends
MIB_ICMP_EX_XPSP1       typedef _MIB_ICMP_EX_XPSP1
PMIB_ICMP_EX_XPSP1      typedef ptr _MIB_ICMP_EX_XPSP1

MIB_ICMP_EX             typedef MIB_ICMP_EX_XPSP1
PMIB_ICMP_EX            typedef ptr MIB_ICMP_EX_XPSP1

.enum ICMP6_TYPE {
    ICMP6_DST_UNREACH          =   1,
    ICMP6_PACKET_TOO_BIG       =   2,
    ICMP6_TIME_EXCEEDED        =   3,
    ICMP6_PARAM_PROB           =   4,
    ICMP6_ECHO_REQUEST         = 128,
    ICMP6_ECHO_REPLY           = 129,
    ICMP6_MEMBERSHIP_QUERY     = 130,
    ICMP6_MEMBERSHIP_REPORT    = 131,
    ICMP6_MEMBERSHIP_REDUCTION = 132,
    ND_ROUTER_SOLICIT          = 133,
    ND_ROUTER_ADVERT           = 134,
    ND_NEIGHBOR_SOLICIT        = 135,
    ND_NEIGHBOR_ADVERT         = 136,
    ND_REDIRECT                = 137,
    ICMP6_V2_MEMBERSHIP_REPORT = 143,
}

define ICMP6_INFOMSG_MASK 0x80
ICMP6_ISTYPEINFORMATIONAL macro Type
  exitm<(((Type) and ICMP6_INFOMSG_MASK) ne 0)>
  endm
ICMP6_ISTYPEERROR macro Type
  exitm<( not ICMP6_ISTYPEINFORMATIONAL(Type))>
  endm

.enum ICMP4_TYPE {
    ICMP4_ECHO_REPLY        =  0,
    ICMP4_DST_UNREACH       =  3,
    ICMP4_SOURCE_QUENCH     =  4,
    ICMP4_REDIRECT          =  5,
    ICMP4_ECHO_REQUEST      =  8,
    ICMP4_ROUTER_ADVERT     =  9,
    ICMP4_ROUTER_SOLICIT    = 10,
    ICMP4_TIME_EXCEEDED     = 11,
    ICMP4_PARAM_PROB        = 12,
    ICMP4_TIMESTAMP_REQUEST = 13,
    ICMP4_TIMESTAMP_REPLY   = 14,
    ICMP4_MASK_REQUEST      = 17,
    ICMP4_MASK_REPLY        = 18,
    }

ICMP4_ISTYPEERROR macro Type
  exitm<(((Type) eq ICMP4_DST_UNREACH) or \
         ((Type) eq ICMP4_SOURCE_QUENCH) or \
         ((Type) eq ICMP4_REDIRECT) or \
         ((Type) eq ICMP4_PARAM_PROB) or \
         ((Type) eq ICMP4_TIME_EXCEEDED))>
  endm

_MIB_IPMCAST_OIF_XP     struct
dwOutIfIndex            DWORD ?
dwNextHopAddr           DWORD ?
dwReserved              DWORD ?
dwReserved1             DWORD ?
_MIB_IPMCAST_OIF_XP     ends
MIB_IPMCAST_OIF_XP      typedef _MIB_IPMCAST_OIF_XP
PMIB_IPMCAST_OIF_XP     typedef ptr _MIB_IPMCAST_OIF_XP

_MIB_IPMCAST_OIF_W2K    struct
dwOutIfIndex            DWORD ?
dwNextHopAddr           DWORD ?
pvReserved              PVOID ?
dwReserved              DWORD ?
_MIB_IPMCAST_OIF_W2K    ends
MIB_IPMCAST_OIF_W2K     typedef _MIB_IPMCAST_OIF_W2K
PMIB_IPMCAST_OIF_W2K    typedef ptr _MIB_IPMCAST_OIF_W2K

if (NTDDI_VERSION ge NTDDI_WINXP)
MIB_IPMCAST_OIF         typedef MIB_IPMCAST_OIF_XP
PMIB_IPMCAST_OIF        typedef ptr MIB_IPMCAST_OIF_XP
elseif (NTDDI_VERSION ge NTDDI_WIN2K)
MIB_IPMCAST_OIF         typedef MIB_IPMCAST_OIF_W2K
PMIB_IPMCAST_OIF        typedef ptr MIB_IPMCAST_OIF_W2K
else
MIB_IPMCAST_OIF         typedef MIB_IPMCAST_OIF_XP
PMIB_IPMCAST_OIF        typedef ptr MIB_IPMCAST_OIF_XP
endif

_MIB_IPMCAST_MFE        struct
dwGroup                 DWORD ?
dwSource                DWORD ?
dwSrcMask               DWORD ?
dwUpStrmNgbr            DWORD ?
dwInIfIndex             DWORD ?
dwInIfProtocol          DWORD ?
dwRouteProtocol         DWORD ?
dwRouteNetwork          DWORD ?
dwRouteMask             DWORD ?
ulUpTime                ULONG ?
ulExpiryTime            ULONG ?
ulTimeOut               ULONG ?
ulNumOutIf              ULONG ?
fFlags                  DWORD ?
dwReserved              DWORD ?
rgmioOutInfo            MIB_IPMCAST_OIF ANY_SIZE dup(<>)
_MIB_IPMCAST_MFE        ends
MIB_IPMCAST_MFE         typedef _MIB_IPMCAST_MFE
PMIB_IPMCAST_MFE        typedef ptr _MIB_IPMCAST_MFE

_MIB_MFE_TABLE          struct
dwNumEntries            DWORD ?
table                   MIB_IPMCAST_MFE ANY_SIZE dup(<>)
_MIB_MFE_TABLE          ends
MIB_MFE_TABLE           typedef _MIB_MFE_TABLE
PMIB_MFE_TABLE          typedef ptr _MIB_MFE_TABLE

define SIZEOF_BASIC_MIB_MFE (ULONG)(FIELD_OFFSET(MIB_IPMCAST_MFE, rgmioOutInfo[0]))

SIZEOF_MIB_MFE macro X
  exitm<SIZEOF_BASIC_MIB_MFE + ((X) * sizeof(MIB_IPMCAST_OIF))>
  endm

_MIB_IPMCAST_OIF_STATS_LH struct
dwOutIfIndex            DWORD ?
dwNextHopAddr           DWORD ?
dwDialContext           DWORD ?
ulTtlTooLow             ULONG ?
ulFragNeeded            ULONG ?
ulOutPackets            ULONG ?
ulOutDiscards           ULONG ?
_MIB_IPMCAST_OIF_STATS_LH ends
MIB_IPMCAST_OIF_STATS_LH typedef _MIB_IPMCAST_OIF_STATS_LH
PMIB_IPMCAST_OIF_STATS_LH typedef ptr _MIB_IPMCAST_OIF_STATS_LH

_MIB_IPMCAST_OIF_STATS_W2K struct
dwOutIfIndex            DWORD ?
dwNextHopAddr           DWORD ?
pvDialContext           PVOID ?
ulTtlTooLow             ULONG ?
ulFragNeeded            ULONG ?
ulOutPackets            ULONG ?
ulOutDiscards           ULONG ?
_MIB_IPMCAST_OIF_STATS_W2K ends
MIB_IPMCAST_OIF_STATS_W2K typedef _MIB_IPMCAST_OIF_STATS_W2K
PMIB_IPMCAST_OIF_STATS_W2K typedef ptr _MIB_IPMCAST_OIF_STATS_W2K

if (NTDDI_VERSION ge NTDDI_VISTA)
MIB_IPMCAST_OIF_STATS   typedef MIB_IPMCAST_OIF_STATS_LH
PMIB_IPMCAST_OIF_STATS  typedef ptr MIB_IPMCAST_OIF_STATS_LH
elseif (NTDDI_VERSION ge NTDDI_WIN2K)
MIB_IPMCAST_OIF_STATS   typedef MIB_IPMCAST_OIF_STATS_W2K
PMIB_IPMCAST_OIF_STATS  typedef ptr MIB_IPMCAST_OIF_STATS_W2K
else
MIB_IPMCAST_OIF_STATS   typedef MIB_IPMCAST_OIF_STATS_LH
PMIB_IPMCAST_OIF_STATS  typedef ptr MIB_IPMCAST_OIF_STATS_LH
endif

_MIB_IPMCAST_MFE_STATS  struct
dwGroup                 DWORD ?
dwSource                DWORD ?
dwSrcMask               DWORD ?
dwUpStrmNgbr            DWORD ?
dwInIfIndex             DWORD ?
dwInIfProtocol          DWORD ?
dwRouteProtocol         DWORD ?
dwRouteNetwork          DWORD ?
dwRouteMask             DWORD ?
ulUpTime                ULONG ?
ulExpiryTime            ULONG ?
ulNumOutIf              ULONG ?
ulInPkts                ULONG ?
ulInOctets              ULONG ?
ulPktsDifferentIf       ULONG ?
ulQueueOverflow         ULONG ?
rgmiosOutStats          MIB_IPMCAST_OIF_STATS ANY_SIZE dup(<>)
_MIB_IPMCAST_MFE_STATS  ends
MIB_IPMCAST_MFE_STATS   typedef _MIB_IPMCAST_MFE_STATS
PMIB_IPMCAST_MFE_STATS  typedef ptr _MIB_IPMCAST_MFE_STATS

_MIB_MFE_STATS_TABLE    struct
dwNumEntries            DWORD ?
table                   MIB_IPMCAST_MFE_STATS ANY_SIZE dup(<>)
_MIB_MFE_STATS_TABLE    ends
MIB_MFE_STATS_TABLE     typedef _MIB_MFE_STATS_TABLE
PMIB_MFE_STATS_TABLE    typedef ptr _MIB_MFE_STATS_TABLE

define SIZEOF_BASIC_MIB_MFE_STATS (ULONG)(FIELD_OFFSET(MIB_IPMCAST_MFE_STATS, rgmiosOutStats[0]))

SIZEOF_MIB_MFE_STATS macro X
  exitm<SIZEOF_BASIC_MIB_MFE_STATS + ((X) * sizeof(MIB_IPMCAST_OIF_STATS))>
  endm

_MIB_IPMCAST_MFE_STATS_EX_XP struct
dwGroup                 DWORD ?
dwSource                DWORD ?
dwSrcMask               DWORD ?
dwUpStrmNgbr            DWORD ?
dwInIfIndex             DWORD ?
dwInIfProtocol          DWORD ?
dwRouteProtocol         DWORD ?
dwRouteNetwork          DWORD ?
dwRouteMask             DWORD ?
ulUpTime                ULONG ?
ulExpiryTime            ULONG ?
ulNumOutIf              ULONG ?
ulInPkts                ULONG ?
ulInOctets              ULONG ?
ulPktsDifferentIf       ULONG ?
ulQueueOverflow         ULONG ?
ulUninitMfe             ULONG ?
ulNegativeMfe           ULONG ?
ulInDiscards            ULONG ?
ulInHdrErrors           ULONG ?
ulTotalOutPackets       ULONG ?
rgmiosOutStats          MIB_IPMCAST_OIF_STATS ANY_SIZE dup(<>)
_MIB_IPMCAST_MFE_STATS_EX_XP ends
MIB_IPMCAST_MFE_STATS_EX_XP typedef _MIB_IPMCAST_MFE_STATS_EX_XP
PMIB_IPMCAST_MFE_STATS_EX_XP typedef ptr _MIB_IPMCAST_MFE_STATS_EX_XP
if (NTDDI_VERSION ge NTDDI_WINXP)
MIB_IPMCAST_MFE_STATS_EX typedef MIB_IPMCAST_MFE_STATS_EX_XP
PMIB_IPMCAST_MFE_STATS_EX typedef ptr MIB_IPMCAST_MFE_STATS_EX_XP
endif

_MIB_MFE_STATS_TABLE_EX_XP struct
dwNumEntries            DWORD ?
table                   PMIB_IPMCAST_MFE_STATS_EX_XP ANY_SIZE dup(?)
_MIB_MFE_STATS_TABLE_EX_XP ends
MIB_MFE_STATS_TABLE_EX_XP typedef _MIB_MFE_STATS_TABLE_EX_XP
PMIB_MFE_STATS_TABLE_EX_XP typedef ptr _MIB_MFE_STATS_TABLE_EX_XP
if (NTDDI_VERSION ge NTDDI_WINXP)
MIB_MFE_STATS_TABLE_EX  typedef MIB_MFE_STATS_TABLE_EX_XP
PMIB_MFE_STATS_TABLE_EX typedef ptr MIB_MFE_STATS_TABLE_EX_XP

define SIZEOF_BASIC_MIB_MFE_STATS_EX (ULONG)(FIELD_OFFSET(MIB_IPMCAST_MFE_STATS_EX, rgmiosOutStats[0]))

SIZEOF_MIB_MFE_STATS_EX macro X
  exitm<SIZEOF_BASIC_MIB_MFE_STATS_EX + ((X) * sizeof(MIB_IPMCAST_OIF_STATS))>
  endm
endif

_MIB_IPMCAST_GLOBAL     struct
dwEnable                DWORD ?
_MIB_IPMCAST_GLOBAL     ends
MIB_IPMCAST_GLOBAL      typedef _MIB_IPMCAST_GLOBAL
PMIB_IPMCAST_GLOBAL     typedef ptr _MIB_IPMCAST_GLOBAL

_MIB_IPMCAST_IF_ENTRY   struct
dwIfIndex               DWORD ?
dwTtl                   DWORD ?
dwProtocol              DWORD ?
dwRateLimit             DWORD ?
ulInMcastOctets         ULONG ?
ulOutMcastOctets        ULONG ?
_MIB_IPMCAST_IF_ENTRY   ends
MIB_IPMCAST_IF_ENTRY    typedef _MIB_IPMCAST_IF_ENTRY
PMIB_IPMCAST_IF_ENTRY   typedef ptr _MIB_IPMCAST_IF_ENTRY

_MIB_IPMCAST_IF_TABLE   struct
dwNumEntries            DWORD ?
table                   MIB_IPMCAST_IF_ENTRY ANY_SIZE dup(<>)
_MIB_IPMCAST_IF_TABLE   ends
MIB_IPMCAST_IF_TABLE    typedef _MIB_IPMCAST_IF_TABLE
PMIB_IPMCAST_IF_TABLE   typedef ptr _MIB_IPMCAST_IF_TABLE

SIZEOF_MCAST_IF_TABLE macro X
  exitm<(FIELD_OFFSET(MIB_IPMCAST_IF_TABLE, table) + ((X) * sizeof(MIB_IPMCAST_IF_ENTRY)) + ALIGN_SIZE)>
  endm

endif

endif

endif ; _IPMIB_
