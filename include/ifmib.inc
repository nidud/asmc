ifndef _IFMIB_
define _IFMIB_

include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

include ifdef.inc

ifndef ANY_SIZE
define ANY_SIZE 1
endif

_MIB_IFNUMBER           struct
dwValue                 DWORD ?
_MIB_IFNUMBER           ends
MIB_IFNUMBER            typedef _MIB_IFNUMBER
PMIB_IFNUMBER           typedef ptr _MIB_IFNUMBER

define MAXLEN_PHYSADDR 8
define MAXLEN_IFDESCR 256
define MAX_INTERFACE_NAME_LEN 256

_MIB_IFROW              struct
wszName                 WCHAR MAX_INTERFACE_NAME_LEN dup(?)
dwIndex                 IF_INDEX ?
dwType                  IFTYPE ?
dwMtu                   DWORD ?
dwSpeed                 DWORD ?
dwPhysAddrLen           DWORD ?
bPhysAddr               UCHAR MAXLEN_PHYSADDR dup(?)
dwAdminStatus           DWORD ?
dwOperStatus            INTERNAL_IF_OPER_STATUS ?
dwLastChange            DWORD ?
dwInOctets              DWORD ?
dwInUcastPkts           DWORD ?
dwInNUcastPkts          DWORD ?
dwInDiscards            DWORD ?
dwInErrors              DWORD ?
dwInUnknownProtos       DWORD ?
dwOutOctets             DWORD ?
dwOutUcastPkts          DWORD ?
dwOutNUcastPkts         DWORD ?
dwOutDiscards           DWORD ?
dwOutErrors             DWORD ?
dwOutQLen               DWORD ?
dwDescrLen              DWORD ?
bDescr                  UCHAR MAXLEN_IFDESCR dup(?)
_MIB_IFROW              ends
MIB_IFROW               typedef _MIB_IFROW
PMIB_IFROW              typedef ptr _MIB_IFROW

_MIB_IFTABLE            struct
dwNumEntries            DWORD ?
table                   MIB_IFROW ANY_SIZE dup(<>)
_MIB_IFTABLE            ends
MIB_IFTABLE             typedef _MIB_IFTABLE
PMIB_IFTABLE            typedef ptr _MIB_IFTABLE

SIZEOF_IFTABLE macro X
  exitm<(FIELD_OFFSET(MIB_IFTABLE,table) + ((X) * sizeof(MIB_IFROW)) + ALIGN_SIZE)>
  endm

endif

endif
