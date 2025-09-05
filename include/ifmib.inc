ifndef _IFMIB_
define _IFMIB_

ifndef _WINAPIFAMILY_
include winapifamily.inc
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

include ifdef.inc

ifndef ANY_SIZE
define ANY_SIZE 1
endif

MIB_IFNUMBER		struct
dwValue			DWORD ?
MIB_IFNUMBER		ends
PMIB_IFNUMBER		typedef ptr MIB_IFNUMBER

define MAXLEN_PHYSADDR 8
define MAXLEN_IFDESCR 256
define MAX_INTERFACE_NAME_LEN 256

MIB_IFROW		struct
wszName			dw MAX_INTERFACE_NAME_LEN dup(?)
dwIndex			IF_INDEX ?
dwType			IFTYPE ?
dwMtu			dd ?
dwSpeed			dd ?
dwPhysAddrLen		dd ?
bPhysAddr		db MAXLEN_PHYSADDR dup(?)
dwAdminStatus		dd ?
dwOperStatus		INTERNAL_IF_OPER_STATUS ?
dwLastChange		dd ?
dwInOctets		dd ?
dwInUcastPkts		dd ?
dwInNUcastPkts		dd ?
dwInDiscards		dd ?
dwInErrors		dd ?
dwInUnknownProtos	dd ?
dwOutOctets		dd ?
dwOutUcastPkts		dd ?
dwOutNUcastPkts		dd ?
dwOutDiscards		dd ?
dwOutErrors		dd ?
dwOutQLen		dd ?
dwDescrLen		dd ?
bDescr			db MAXLEN_IFDESCR dup(?)
MIB_IFROW		ends
PMIB_IFROW		typedef ptr MIB_IFROW

MIB_IFTABLE		struct
dwNumEntries		dd ?
table			MIB_IFROW ANY_SIZE dup(<>)
MIB_IFTABLE		ends
PMIB_IFTABLE		typedef ptr MIB_IFTABLE

SIZEOF_IFTABLE macro X
  exitm<(FIELD_OFFSET(MIB_IFTABLE,table) + ((X) * sizeof(MIB_IFROW)) + ALIGN_SIZE)>
  endm

endif

endif
