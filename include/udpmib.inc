ifndef _UDPMIB_
define _UDPMIB_

include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

ifndef ANY_SIZE
define ANY_SIZE 1
endif

define TCPIP_OWNING_MODULE_SIZE 16

_MIB_UDPROW             struct
dwLocalAddr             DWORD ?
dwLocalPort             DWORD ?
_MIB_UDPROW             ends
MIB_UDPROW              typedef _MIB_UDPROW
PMIB_UDPROW             typedef ptr _MIB_UDPROW

_MIB_UDPTABLE           struct
dwNumEntries            DWORD ?
table                   MIB_UDPROW ANY_SIZE dup(<>)
_MIB_UDPTABLE           ends
MIB_UDPTABLE            typedef _MIB_UDPTABLE
PMIB_UDPTABLE           typedef ptr _MIB_UDPTABLE

SIZEOF_UDPTABLE macro X
  exitm<(FIELD_OFFSET(MIB_UDPTABLE, table) + ((X) * sizeof(MIB_UDPROW)) + ALIGN_SIZE)>
  endm

_MIB_UDPROW_OWNER_PID   struct
dwLocalAddr             DWORD ?
dwLocalPort             DWORD ?
dwOwningPid             DWORD ?
_MIB_UDPROW_OWNER_PID   ends
MIB_UDPROW_OWNER_PID    typedef _MIB_UDPROW_OWNER_PID
PMIB_UDPROW_OWNER_PID   typedef ptr _MIB_UDPROW_OWNER_PID

_MIB_UDPTABLE_OWNER_PID struct
dwNumEntries            DWORD ?
table                   MIB_UDPROW_OWNER_PID ANY_SIZE dup(<>)
_MIB_UDPTABLE_OWNER_PID ends
MIB_UDPTABLE_OWNER_PID  typedef _MIB_UDPTABLE_OWNER_PID
PMIB_UDPTABLE_OWNER_PID typedef ptr _MIB_UDPTABLE_OWNER_PID

SIZEOF_UDPTABLE_OWNER_PID macro X
  exitm<(FIELD_OFFSET(MIB_UDPTABLE_OWNER_PID, table) + ((X) * sizeof(MIB_UDPROW_OWNER_PID)) + ALIGN_SIZE)>
  endm

_MIB_UDPROW_OWNER_MODULE struct
dwLocalAddr             DWORD ?
dwLocalPort             DWORD ?
dwOwningPid             DWORD ?
liCreateTimestamp       LARGE_INTEGER <>
union
 struct
  record
   SpecificPortBind     sdword : 1 ?
  ends
 ends
 dwFlags                sdword ?
ends
OwningModuleInfo        ULONGLONG TCPIP_OWNING_MODULE_SIZE dup(?)
_MIB_UDPROW_OWNER_MODULE ends
MIB_UDPROW_OWNER_MODULE typedef _MIB_UDPROW_OWNER_MODULE
PMIB_UDPROW_OWNER_MODULE typedef ptr _MIB_UDPROW_OWNER_MODULE

_MIB_UDPTABLE_OWNER_MODULE struct
dwNumEntries            DWORD ?
table                   MIB_UDPROW_OWNER_MODULE ANY_SIZE dup(<>)
_MIB_UDPTABLE_OWNER_MODULE ends
MIB_UDPTABLE_OWNER_MODULE typedef _MIB_UDPTABLE_OWNER_MODULE
PMIB_UDPTABLE_OWNER_MODULE typedef ptr _MIB_UDPTABLE_OWNER_MODULE

SIZEOF_UDPTABLE_OWNER_MODULE macro X
  exitm<(FIELD_OFFSET(MIB_UDPTABLE_OWNER_MODULE, table) + ((X) * sizeof(MIB_UDPROW_OWNER_MODULE)) + ALIGN_SIZE)>
  endm

ifdef _WS2IPDEF_

_MIB_UDP6ROW            struct
dwLocalAddr             IN6_ADDR <>
dwLocalScopeId          DWORD ?
dwLocalPort             DWORD ?
_MIB_UDP6ROW            ends
MIB_UDP6ROW             typedef _MIB_UDP6ROW
PMIB_UDP6ROW            typedef ptr _MIB_UDP6ROW

_MIB_UDP6TABLE          struct
dwNumEntries            DWORD ?
table                   MIB_UDP6ROW ANY_SIZE dup(<?>)
_MIB_UDP6TABLE          ends
MIB_UDP6TABLE           typedef _MIB_UDP6TABLE
PMIB_UDP6TABLE          typedef ptr _MIB_UDP6TABLE

SIZEOF_UDP6TABLE macro X
  exitm<(FIELD_OFFSET(MIB_UDP6TABLE, table) + ((X) * sizeof(MIB_UDP6ROW)) + ALIGN_SIZE)>
  endm

_MIB_UDP6ROW_OWNER_PID  struct
ucLocalAddr             UCHAR 16 dup(?)
dwLocalScopeId          DWORD ?
dwLocalPort             DWORD ?
dwOwningPid             DWORD ?
_MIB_UDP6ROW_OWNER_PID  ends
MIB_UDP6ROW_OWNER_PID   typedef _MIB_UDP6ROW_OWNER_PID
PMIB_UDP6ROW_OWNER_PID  typedef ptr _MIB_UDP6ROW_OWNER_PID

_MIB_UDP6TABLE_OWNER_PID struct
dwNumEntries            DWORD ?
table                   MIB_UDP6ROW_OWNER_PID ANY_SIZE dup(<?>)
_MIB_UDP6TABLE_OWNER_PID ends
MIB_UDP6TABLE_OWNER_PID typedef _MIB_UDP6TABLE_OWNER_PID
PMIB_UDP6TABLE_OWNER_PID typedef ptr _MIB_UDP6TABLE_OWNER_PID

SIZEOF_UDP6TABLE_OWNER_PID macro X
  exitm<(FIELD_OFFSET(MIB_UDP6TABLE_OWNER_PID, table) + ((X) * sizeof(MIB_UDP6ROW_OWNER_PID)) + ALIGN_SIZE)>
  endm

_MIB_UDP6ROW_OWNER_MODULE struct
ucLocalAddr             UCHAR 16 dup(?)
dwLocalScopeId          DWORD ?
dwLocalPort             DWORD ?
dwOwningPid             DWORD ?
liCreateTimestamp       LARGE_INTEGER <>
union
 struct
  record
   SpecificPortBind     sdword :  1 ?
  ends
 ends
 dwFlags                sdword ?
ends
OwningModuleInfo        ULONGLONG TCPIP_OWNING_MODULE_SIZE dup(?)
_MIB_UDP6ROW_OWNER_MODULE ends
MIB_UDP6ROW_OWNER_MODULE typedef _MIB_UDP6ROW_OWNER_MODULE
PMIB_UDP6ROW_OWNER_MODULE typedef ptr _MIB_UDP6ROW_OWNER_MODULE

_MIB_UDP6TABLE_OWNER_MODULE struct
dwNumEntries            DWORD ?
table                   MIB_UDP6ROW_OWNER_MODULE ANY_SIZE dup(<?>)
_MIB_UDP6TABLE_OWNER_MODULE ends
MIB_UDP6TABLE_OWNER_MODULE typedef _MIB_UDP6TABLE_OWNER_MODULE
PMIB_UDP6TABLE_OWNER_MODULE typedef ptr _MIB_UDP6TABLE_OWNER_MODULE

SIZEOF_UDP6TABLE_OWNER_MODULE macro X
  exitm<(FIELD_OFFSET(MIB_UDP6TABLE_OWNER_MODULE, table) + ((X) * sizeof(MIB_UDP6ROW_OWNER_MODULE)) + ALIGN_SIZE)>
  endm

endif

_MIB_UDPSTATS           struct
dwInDatagrams           DWORD ?
dwNoPorts               DWORD ?
dwInErrors              DWORD ?
dwOutDatagrams          DWORD ?
dwNumAddrs              DWORD ?
_MIB_UDPSTATS           ends
MIB_UDPSTATS            typedef _MIB_UDPSTATS
PMIB_UDPSTATS           typedef ptr _MIB_UDPSTATS

if (NTDDI_VERSION ge NTDDI_WIN10_RS3)
_MIB_UDPSTATS2          struct
dw64InDatagrams         DWORD64 ?
dwNoPorts               DWORD ?
dwInErrors              DWORD ?
dw64OutDatagrams        DWORD64 ?
dwNumAddrs              DWORD ?
_MIB_UDPSTATS2          ends
MIB_UDPSTATS2           typedef _MIB_UDPSTATS2
PMIB_UDPSTATS2          typedef ptr _MIB_UDPSTATS2
endif

endif

endif
