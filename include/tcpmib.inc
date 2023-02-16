ifndef _TCPMIB_
define _TCPMIB_

include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

ifndef ANY_SIZE
define ANY_SIZE 1
endif

define TCPIP_OWNING_MODULE_SIZE 16

.enum MIB_TCP_STATE {
    MIB_TCP_STATE_CLOSED     =  1,
    MIB_TCP_STATE_LISTEN     =  2,
    MIB_TCP_STATE_SYN_SENT   =  3,
    MIB_TCP_STATE_SYN_RCVD   =  4,
    MIB_TCP_STATE_ESTAB      =  5,
    MIB_TCP_STATE_FIN_WAIT1  =  6,
    MIB_TCP_STATE_FIN_WAIT2  =  7,
    MIB_TCP_STATE_CLOSE_WAIT =  8,
    MIB_TCP_STATE_CLOSING    =  9,
    MIB_TCP_STATE_LAST_ACK   = 10,
    MIB_TCP_STATE_TIME_WAIT  = 11,
    MIB_TCP_STATE_DELETE_TCB = 12,
    MIB_TCP_STATE_RESERVED   = 100
    }

.enum TCP_CONNECTION_OFFLOAD_STATE {
    TcpConnectionOffloadStateInHost,
    TcpConnectionOffloadStateOffloading,
    TcpConnectionOffloadStateOffloaded,
    TcpConnectionOffloadStateUploading,
    TcpConnectionOffloadStateMax
    }

_MIB_TCPROW_LH          struct
union
 dwState                DWORD ?
 State                  MIB_TCP_STATE ?
ends
dwLocalAddr             DWORD ?
dwLocalPort             DWORD ?
dwRemoteAddr            DWORD ?
dwRemotePort            DWORD ?
_MIB_TCPROW_LH          ends
MIB_TCPROW_LH           typedef _MIB_TCPROW_LH
PMIB_TCPROW_LH          typedef ptr _MIB_TCPROW_LH

_MIB_TCPROW_W2K         struct
dwState                 DWORD ?
dwLocalAddr             DWORD ?
dwLocalPort             DWORD ?
dwRemoteAddr            DWORD ?
dwRemotePort            DWORD ?
_MIB_TCPROW_W2K         ends
MIB_TCPROW_W2K          typedef _MIB_TCPROW_W2K
PMIB_TCPROW_W2K         typedef ptr _MIB_TCPROW_W2K

if (NTDDI_VERSION ge NTDDI_VISTA)
MIB_TCPROW              typedef MIB_TCPROW_LH
PMIB_TCPROW             typedef ptr MIB_TCPROW_LH
elseif (NTDDI_VERSION ge NTDDI_WIN2K)
MIB_TCPROW              typedef MIB_TCPROW_W2K
PMIB_TCPROW             typedef ptr MIB_TCPROW_W2K
else
MIB_TCPROW              typedef MIB_TCPROW_LH
PMIB_TCPROW             typedef ptr MIB_TCPROW_LH
endif

_MIB_TCPTABLE           struct
dwNumEntries            DWORD ?
table                   MIB_TCPROW ANY_SIZE dup(<>)
_MIB_TCPTABLE           ends
MIB_TCPTABLE            typedef _MIB_TCPTABLE
PMIB_TCPTABLE           typedef ptr _MIB_TCPTABLE

SIZEOF_TCPTABLE macro X
  exitm<(FIELD_OFFSET(MIB_TCPTABLE,table) + ((X) * sizeof(MIB_TCPROW)) + ALIGN_SIZE)>
  endm

_MIB_TCPROW2            struct
dwState                 DWORD ?
dwLocalAddr             DWORD ?
dwLocalPort             DWORD ?
dwRemoteAddr            DWORD ?
dwRemotePort            DWORD ?
dwOwningPid             DWORD ?
dwOffloadState          TCP_CONNECTION_OFFLOAD_STATE ?
_MIB_TCPROW2            ends
MIB_TCPROW2             typedef _MIB_TCPROW2
PMIB_TCPROW2            typedef ptr _MIB_TCPROW2

_MIB_TCPTABLE2          struct
dwNumEntries            DWORD ?
table                   MIB_TCPROW2 ANY_SIZE dup(<>)
_MIB_TCPTABLE2          ends
MIB_TCPTABLE2           typedef _MIB_TCPTABLE2
PMIB_TCPTABLE2          typedef ptr _MIB_TCPTABLE2

SIZEOF_TCPTABLE2 macro X
  exitm<(FIELD_OFFSET(MIB_TCPTABLE2,table) + ((X) * sizeof(MIB_TCPROW2)) + ALIGN_SIZE)>
  endm

_MIB_TCPROW_OWNER_PID   struct
dwState                 DWORD ?
dwLocalAddr             DWORD ?
dwLocalPort             DWORD ?
dwRemoteAddr            DWORD ?
dwRemotePort            DWORD ?
dwOwningPid             DWORD ?
_MIB_TCPROW_OWNER_PID   ends
MIB_TCPROW_OWNER_PID    typedef _MIB_TCPROW_OWNER_PID
PMIB_TCPROW_OWNER_PID   typedef ptr _MIB_TCPROW_OWNER_PID

_MIB_TCPTABLE_OWNER_PID struct
dwNumEntries            DWORD ?
table                   MIB_TCPROW_OWNER_PID ANY_SIZE dup(<>)
_MIB_TCPTABLE_OWNER_PID ends
MIB_TCPTABLE_OWNER_PID  typedef _MIB_TCPTABLE_OWNER_PID
PMIB_TCPTABLE_OWNER_PID typedef ptr _MIB_TCPTABLE_OWNER_PID

SIZEOF_TCPTABLE_OWNER_PID macro X
  exitm<(FIELD_OFFSET(MIB_TCPTABLE_OWNER_PID, table) + ((X) * sizeof(MIB_TCPROW_OWNER_PID)) + ALIGN_SIZE)>
  endm

_MIB_TCPROW_OWNER_MODULE struct
dwState                 DWORD ?
dwLocalAddr             DWORD ?
dwLocalPort             DWORD ?
dwRemoteAddr            DWORD ?
dwRemotePort            DWORD ?
dwOwningPid             DWORD ?
liCreateTimestamp       LARGE_INTEGER <>
OwningModuleInfo        ULONGLONG TCPIP_OWNING_MODULE_SIZE dup(?)
_MIB_TCPROW_OWNER_MODULE ends
MIB_TCPROW_OWNER_MODULE typedef _MIB_TCPROW_OWNER_MODULE
PMIB_TCPROW_OWNER_MODULE typedef ptr _MIB_TCPROW_OWNER_MODULE

_MIB_TCPTABLE_OWNER_MODULE struct
dwNumEntries            DWORD ?
table                   MIB_TCPROW_OWNER_MODULE ANY_SIZE dup(<>)
_MIB_TCPTABLE_OWNER_MODULE ends
MIB_TCPTABLE_OWNER_MODULE typedef _MIB_TCPTABLE_OWNER_MODULE
PMIB_TCPTABLE_OWNER_MODULE typedef ptr _MIB_TCPTABLE_OWNER_MODULE

SIZEOF_TCPTABLE_OWNER_MODULE macro X
  exitm<(FIELD_OFFSET(MIB_TCPTABLE_OWNER_MODULE, table) + ((X) * sizeof(MIB_TCPROW_OWNER_MODULE)) + ALIGN_SIZE)>
  endm

ifdef _WS2IPDEF_

_MIB_TCP6ROW            struct
State                   MIB_TCP_STATE ?
LocalAddr               IN6_ADDR <>
dwLocalScopeId          DWORD ?
dwLocalPort             DWORD ?
RemoteAddr              IN6_ADDR <>
dwRemoteScopeId         DWORD ?
dwRemotePort            DWORD ?
_MIB_TCP6ROW            ends
MIB_TCP6ROW             typedef _MIB_TCP6ROW
PMIB_TCP6ROW            typedef ptr _MIB_TCP6ROW

_MIB_TCP6TABLE          struct
dwNumEntries            DWORD ?
table                   MIB_TCP6ROW ANY_SIZE dup(<?>)
_MIB_TCP6TABLE          ends
MIB_TCP6TABLE           typedef _MIB_TCP6TABLE
PMIB_TCP6TABLE          typedef ptr _MIB_TCP6TABLE

SIZEOF_TCP6TABLE macro X
  exitm<(FIELD_OFFSET(MIB_TCP6TABLE,table) + ((X) * sizeof(MIB_TCP6ROW)) + ALIGN_SIZE)>
  endm

_MIB_TCP6ROW2           struct
LocalAddr               IN6_ADDR <>
dwLocalScopeId          DWORD ?
dwLocalPort             DWORD ?
RemoteAddr              IN6_ADDR <>
dwRemoteScopeId         DWORD ?
dwRemotePort            DWORD ?
State                   MIB_TCP_STATE ?
dwOwningPid             DWORD ?
dwOffloadState          TCP_CONNECTION_OFFLOAD_STATE ?
_MIB_TCP6ROW2           ends
MIB_TCP6ROW2            typedef _MIB_TCP6ROW2
PMIB_TCP6ROW2           typedef ptr _MIB_TCP6ROW2

_MIB_TCP6TABLE2         struct
dwNumEntries            DWORD ?
table                   MIB_TCP6ROW2 ANY_SIZE dup(<?>)
_MIB_TCP6TABLE2         ends
MIB_TCP6TABLE2          typedef _MIB_TCP6TABLE2
PMIB_TCP6TABLE2         typedef ptr _MIB_TCP6TABLE2

SIZEOF_TCP6TABLE2 macro X
  exitm<(FIELD_OFFSET(MIB_TCP6TABLE2,table) + ((X) * sizeof(MIB_TCP6ROW2)) + ALIGN_SIZE)>
  endm

_MIB_TCP6ROW_OWNER_PID  struct
ucLocalAddr             UCHAR 16 dup(?)
dwLocalScopeId          DWORD ?
dwLocalPort             DWORD ?
ucRemoteAddr            UCHAR 16 dup(?)
dwRemoteScopeId         DWORD ?
dwRemotePort            DWORD ?
dwState                 DWORD ?
dwOwningPid             DWORD ?
_MIB_TCP6ROW_OWNER_PID  ends
MIB_TCP6ROW_OWNER_PID   typedef _MIB_TCP6ROW_OWNER_PID
PMIB_TCP6ROW_OWNER_PID  typedef ptr _MIB_TCP6ROW_OWNER_PID

_MIB_TCP6TABLE_OWNER_PID struct
dwNumEntries            DWORD ?
table                   MIB_TCP6ROW_OWNER_PID ANY_SIZE dup(<?>)
_MIB_TCP6TABLE_OWNER_PID ends
MIB_TCP6TABLE_OWNER_PID typedef _MIB_TCP6TABLE_OWNER_PID
PMIB_TCP6TABLE_OWNER_PID typedef ptr _MIB_TCP6TABLE_OWNER_PID

SIZEOF_TCP6TABLE_OWNER_PID macro X
  exitm<(FIELD_OFFSET(MIB_TCP6TABLE_OWNER_PID, table) + ((X) * sizeof(MIB_TCP6ROW_OWNER_PID)) + ALIGN_SIZE)>
  endm

_MIB_TCP6ROW_OWNER_MODULE struct
ucLocalAddr             UCHAR 16 dup(?)
dwLocalScopeId          DWORD ?
dwLocalPort             DWORD ?
ucRemoteAddr            UCHAR 16 dup(?)
dwRemoteScopeId         DWORD ?
dwRemotePort            DWORD ?
dwState                 DWORD ?
dwOwningPid             DWORD ?
liCreateTimestamp       LARGE_INTEGER <>
OwningModuleInfo        ULONGLONG TCPIP_OWNING_MODULE_SIZE dup(?)
_MIB_TCP6ROW_OWNER_MODULE ends
MIB_TCP6ROW_OWNER_MODULE typedef _MIB_TCP6ROW_OWNER_MODULE
PMIB_TCP6ROW_OWNER_MODULE typedef ptr _MIB_TCP6ROW_OWNER_MODULE

_MIB_TCP6TABLE_OWNER_MODULE struct
dwNumEntries            DWORD ?
table                   MIB_TCP6ROW_OWNER_MODULE ANY_SIZE dup(<?>)
_MIB_TCP6TABLE_OWNER_MODULE ends
MIB_TCP6TABLE_OWNER_MODULE typedef _MIB_TCP6TABLE_OWNER_MODULE
PMIB_TCP6TABLE_OWNER_MODULE typedef ptr _MIB_TCP6TABLE_OWNER_MODULE

SIZEOF_TCP6TABLE_OWNER_MODULE macro X
    (FIELD_OFFSET(MIB_TCP6TABLE_OWNER_MODULE, table[0]) +
    ((X) * sizeof(MIB_TCP6ROW_OWNER_MODULE)) + ALIGN_SIZE)
  exitm<>
  endm

endif

define MIB_TCP_MAXCONN_DYNAMIC ((ULONG)-1)

.enum TCP_RTO_ALGORITHM {
    TcpRtoAlgorithmOther  = 1,
    TcpRtoAlgorithmConstant,
    TcpRtoAlgorithmRsre,
    TcpRtoAlgorithmVanj,

    MIB_TCP_RTO_OTHER     = 1,
    MIB_TCP_RTO_CONSTANT  = 2,
    MIB_TCP_RTO_RSRE      = 3,
    MIB_TCP_RTO_VANJ      = 4,
    }

_MIB_TCPSTATS_LH        struct
union
 dwRtoAlgorithm         DWORD ?
 RtoAlgorithm           TCP_RTO_ALGORITHM ?
ends
dwRtoMin                DWORD ?
dwRtoMax                DWORD ?
dwMaxConn               DWORD ?
dwActiveOpens           DWORD ?
dwPassiveOpens          DWORD ?
dwAttemptFails          DWORD ?
dwEstabResets           DWORD ?
dwCurrEstab             DWORD ?
dwInSegs                DWORD ?
dwOutSegs               DWORD ?
dwRetransSegs           DWORD ?
dwInErrs                DWORD ?
dwOutRsts               DWORD ?
dwNumConns              DWORD ?
_MIB_TCPSTATS_LH        ends
MIB_TCPSTATS_LH         typedef _MIB_TCPSTATS_LH
PMIB_TCPSTATS_LH        typedef ptr _MIB_TCPSTATS_LH

_MIB_TCPSTATS_W2K       struct
dwRtoAlgorithm          DWORD ?
dwRtoMin                DWORD ?
dwRtoMax                DWORD ?
dwMaxConn               DWORD ?
dwActiveOpens           DWORD ?
dwPassiveOpens          DWORD ?
dwAttemptFails          DWORD ?
dwEstabResets           DWORD ?
dwCurrEstab             DWORD ?
dwInSegs                DWORD ?
dwOutSegs               DWORD ?
dwRetransSegs           DWORD ?
dwInErrs                DWORD ?
dwOutRsts               DWORD ?
dwNumConns              DWORD ?
_MIB_TCPSTATS_W2K       ends
MIB_TCPSTATS_W2K        typedef _MIB_TCPSTATS_W2K
PMIB_TCPSTATS_W2K       typedef ptr _MIB_TCPSTATS_W2K

if (NTDDI_VERSION ge NTDDI_VISTA)
MIB_TCPSTATS            typedef MIB_TCPSTATS_LH
PMIB_TCPSTATS           typedef ptr MIB_TCPSTATS_LH
elseif (NTDDI_VERSION ge NTDDI_WIN2K)
MIB_TCPSTATS            typedef MIB_TCPSTATS_W2K
PMIB_TCPSTATS           typedef ptr MIB_TCPSTATS_W2K
endif

if (NTDDI_VERSION ge NTDDI_WIN10_RS3)
_MIB_TCPSTATS2          struct
RtoAlgorithm            TCP_RTO_ALGORITHM ?
dwRtoMin                DWORD ?
dwRtoMax                DWORD ?
dwMaxConn               DWORD ?
dwActiveOpens           DWORD ?
dwPassiveOpens          DWORD ?
dwAttemptFails          DWORD ?
dwEstabResets           DWORD ?
dwCurrEstab             DWORD ?
dw64InSegs              DWORD64 ?
dw64OutSegs             DWORD64 ?
dwRetransSegs           DWORD ?
dwInErrs                DWORD ?
dwOutRsts               DWORD ?
dwNumConns              DWORD ?
_MIB_TCPSTATS2          ends
MIB_TCPSTATS2           typedef _MIB_TCPSTATS2
PMIB_TCPSTATS2          typedef ptr _MIB_TCPSTATS2
endif

endif

endif
