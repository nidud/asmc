ifndef __ROUTING_IPRTRMIB_H__
define __ROUTING_IPRTRMIB_H__

include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

include mprapidef.inc
include ipifcons.inc

define IPRTRMGR_PID 10000

ifndef ANY_SIZE
define ANY_SIZE 1
endif

define IF_NUMBER           0
define IF_TABLE            (IF_NUMBER          + 1)
define IF_ROW              (IF_TABLE           + 1)
define IP_STATS            (IF_ROW             + 1)
define IP_ADDRTABLE        (IP_STATS           + 1)
define IP_ADDRROW          (IP_ADDRTABLE       + 1)
define IP_FORWARDNUMBER    (IP_ADDRROW         + 1)
define IP_FORWARDTABLE     (IP_FORWARDNUMBER   + 1)
define IP_FORWARDROW       (IP_FORWARDTABLE    + 1)
define IP_NETTABLE         (IP_FORWARDROW      + 1)
define IP_NETROW           (IP_NETTABLE        + 1)
define ICMP_STATS          (IP_NETROW          + 1)
define TCP_STATS           (ICMP_STATS         + 1)
define TCP_TABLE           (TCP_STATS          + 1)
define TCP_ROW             (TCP_TABLE          + 1)
define UDP_STATS           (TCP_ROW            + 1)
define UDP_TABLE           (UDP_STATS          + 1)
define UDP_ROW             (UDP_TABLE          + 1)
define MCAST_MFE           (UDP_ROW            + 1)
define MCAST_MFE_STATS     (MCAST_MFE          + 1)
define BEST_IF             (MCAST_MFE_STATS    + 1)
define BEST_ROUTE          (BEST_IF            + 1)
define PROXY_ARP           (BEST_ROUTE         + 1)
define MCAST_IF_ENTRY      (PROXY_ARP          + 1)
define MCAST_GLOBAL        (MCAST_IF_ENTRY     + 1)
define IF_STATUS           (MCAST_GLOBAL       + 1)
define MCAST_BOUNDARY      (IF_STATUS          + 1)
define MCAST_SCOPE         (MCAST_BOUNDARY     + 1)
define DEST_MATCHING       (MCAST_SCOPE        + 1)
define DEST_LONGER         (DEST_MATCHING      + 1)
define DEST_SHORTER        (DEST_LONGER        + 1)
define ROUTE_MATCHING      (DEST_SHORTER       + 1)
define ROUTE_LONGER        (ROUTE_MATCHING     + 1)
define ROUTE_SHORTER       (ROUTE_LONGER       + 1)
define ROUTE_STATE         (ROUTE_SHORTER      + 1)
define MCAST_MFE_STATS_EX  (ROUTE_STATE        + 1)
define IP6_STATS           (MCAST_MFE_STATS_EX + 1)
define UDP6_STATS          (IP6_STATS          + 1)
define TCP6_STATS          (UDP6_STATS         + 1)

if (NTDDI_VERSION ge NTDDI_VISTA)
define NUMBER_OF_EXPORTED_VARIABLES    (TCP6_STATS + 1)
else
define NUMBER_OF_EXPORTED_VARIABLES    (ROUTE_STATE + 1)
endif

_MIB_OPAQUE_QUERY       struct
dwVarId                 DWORD ?
rgdwVarIndex            DWORD ANY_SIZE dup(?)
_MIB_OPAQUE_QUERY       ends
MIB_OPAQUE_QUERY        typedef _MIB_OPAQUE_QUERY
PMIB_OPAQUE_QUERY       typedef ptr _MIB_OPAQUE_QUERY

include ipmib.inc
include tcpmib.inc
include udpmib.inc

.enum TCP_TABLE_CLASS {
    TCP_TABLE_BASIC_LISTENER,
    TCP_TABLE_BASIC_CONNECTIONS,
    TCP_TABLE_BASIC_ALL,
    TCP_TABLE_OWNER_PID_LISTENER,
    TCP_TABLE_OWNER_PID_CONNECTIONS,
    TCP_TABLE_OWNER_PID_ALL,
    TCP_TABLE_OWNER_MODULE_LISTENER,
    TCP_TABLE_OWNER_MODULE_CONNECTIONS,
    TCP_TABLE_OWNER_MODULE_ALL
    }

.enum UDP_TABLE_CLASS {
    UDP_TABLE_BASIC,
    UDP_TABLE_OWNER_PID,
    UDP_TABLE_OWNER_MODULE
    }

.enum TCPIP_OWNER_MODULE_INFO_CLASS {
    TCPIP_OWNER_MODULE_INFO_BASIC
    }

_TCPIP_OWNER_MODULE_BASIC_INFO struct
pModuleName             PWCHAR ?
pModulePath             PWCHAR ?
_TCPIP_OWNER_MODULE_BASIC_INFO ends
TCPIP_OWNER_MODULE_BASIC_INFO typedef _TCPIP_OWNER_MODULE_BASIC_INFO
PTCPIP_OWNER_MODULE_BASIC_INFO typedef ptr _TCPIP_OWNER_MODULE_BASIC_INFO

_MIB_IPMCAST_BOUNDARY   struct
dwIfIndex               DWORD ?
dwGroupAddress          DWORD ?
dwGroupMask             DWORD ?
dwStatus                DWORD ?
_MIB_IPMCAST_BOUNDARY   ends
MIB_IPMCAST_BOUNDARY    typedef _MIB_IPMCAST_BOUNDARY
PMIB_IPMCAST_BOUNDARY   typedef ptr _MIB_IPMCAST_BOUNDARY

_MIB_IPMCAST_BOUNDARY_TABLE struct
dwNumEntries            DWORD ?
table                   MIB_IPMCAST_BOUNDARY ANY_SIZE dup(<>)
_MIB_IPMCAST_BOUNDARY_TABLE ends
MIB_IPMCAST_BOUNDARY_TABLE typedef _MIB_IPMCAST_BOUNDARY_TABLE
PMIB_IPMCAST_BOUNDARY_TABLE typedef ptr _MIB_IPMCAST_BOUNDARY_TABLE

SIZEOF_BOUNDARY_TABLE macro X
  exitm<(FIELD_OFFSET(MIB_IPMCAST_BOUNDARY_TABLE,table) + ((X) * sizeof(MIB_IPMCAST_BOUNDARY)) + ALIGN_SIZE)>
  endm

MIB_BOUNDARYROW         struct
dwGroupAddress          DWORD ?
dwGroupMask             DWORD ?
MIB_BOUNDARYROW         ends
PMIB_BOUNDARYROW        typedef ptr MIB_BOUNDARYROW

MIB_MCAST_LIMIT_ROW     struct
dwTtl                   DWORD ?
dwRateLimit             DWORD ?
MIB_MCAST_LIMIT_ROW     ends
PMIB_MCAST_LIMIT_ROW    typedef ptr MIB_MCAST_LIMIT_ROW

define MAX_SCOPE_NAME_LEN 255

define SN_UNICODE
SN_CHAR                 typedef WCHAR
SCOPE_NAME              typedef ptr WCHAR

_MIB_IPMCAST_SCOPE      struct
dwGroupAddress          DWORD ?
dwGroupMask             DWORD ?
snNameBuffer            WCHAR MAX_SCOPE_NAME_LEN+1 dup(?)
dwStatus                DWORD ?
_MIB_IPMCAST_SCOPE      ends
MIB_IPMCAST_SCOPE       typedef _MIB_IPMCAST_SCOPE
PMIB_IPMCAST_SCOPE      typedef ptr _MIB_IPMCAST_SCOPE

_MIB_IPDESTROW          struct
ForwardRow              MIB_IPFORWARDROW <>
dwForwardPreference     DWORD ?
dwForwardViewSet        DWORD ?
_MIB_IPDESTROW          ends
MIB_IPDESTROW           typedef _MIB_IPDESTROW
PMIB_IPDESTROW          typedef ptr _MIB_IPDESTROW

_MIB_IPDESTTABLE        struct
dwNumEntries            DWORD ?
table                   MIB_IPDESTROW ANY_SIZE dup(<>)
_MIB_IPDESTTABLE        ends
MIB_IPDESTTABLE         typedef _MIB_IPDESTTABLE
PMIB_IPDESTTABLE        typedef ptr _MIB_IPDESTTABLE

_MIB_BEST_IF            struct
dwDestAddr              DWORD ?
dwIfIndex               DWORD ?
_MIB_BEST_IF            ends
MIB_BEST_IF             typedef _MIB_BEST_IF
PMIB_BEST_IF            typedef ptr _MIB_BEST_IF

_MIB_PROXYARP           struct
dwAddress               DWORD ?
dwMask                  DWORD ?
dwIfIndex               DWORD ?
_MIB_PROXYARP           ends
MIB_PROXYARP            typedef _MIB_PROXYARP
PMIB_PROXYARP           typedef ptr _MIB_PROXYARP

_MIB_IFSTATUS           struct
dwIfIndex               DWORD ?
dwAdminStatus           DWORD ?
dwOperationalStatus     DWORD ?
bMHbeatActive           BOOL ?
bMHbeatAlive            BOOL ?
_MIB_IFSTATUS           ends
MIB_IFSTATUS            typedef _MIB_IFSTATUS
PMIB_IFSTATUS           typedef ptr _MIB_IFSTATUS

_MIB_ROUTESTATE         struct
bRoutesSetToStack       BOOL ?
_MIB_ROUTESTATE         ends
MIB_ROUTESTATE          typedef _MIB_ROUTESTATE
PMIB_ROUTESTATE         typedef ptr _MIB_ROUTESTATE

_MIB_OPAQUE_INFO        struct
dwId                    DWORD ?
union
 ullAlign               ULONGLONG ?
 rgbyData               BYTE 1 dup(?)
ends
_MIB_OPAQUE_INFO        ends
MIB_OPAQUE_INFO         typedef _MIB_OPAQUE_INFO
PMIB_OPAQUE_INFO        typedef ptr _MIB_OPAQUE_INFO

define MAX_MIB_OFFSET      8

MIB_INFO_SIZE macro S
  exitm<MAX_MIB_OFFSET + sizeof(S)>
  endm

MIB_INFO_SIZE_IN_DWORDS macro S
  exitm<((MIB_INFO_SIZE(S))/sizeof(DWORD) + 1)>
  endm

DEFINE_MIB_BUFFER macro X,Y,Z
    DWORD        __rgdwBuff[MIB_INFO_SIZE_IN_DWORDS(Y)];
    PMIB_OPAQUE_INFO    X = (PMIB_OPAQUE_INFO)__rgdwBuff;
    Y *                 Z = (Y *)(X.rgbyData)
  exitm<>
  endm

CAST_MIB_INFO macro X,Y,Z
  exitm<Z = (Y)(X.rgbyData)>
  endm

endif

endif
