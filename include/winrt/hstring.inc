ifndef _RPC500_
include rpc500.inc
endif
ifndef __hstring_h__
define __hstring_h__
ifndef __wtypes_h__
include wtypes.inc
endif

HSTRING__   STRUC
unused      int_t ?
HSTRING__   ENDS
HSTRING     typedef ptr HSTRING__

HSTRING_HEADER  STRUC
UNION Reserved
Reserved1       PVOID ?
ifdef _WIN64
Reserved2       sbyte 24 dup(?)
else
Reserved2       sbyte 20 dup(?)
endif
ENDS
HSTRING_HEADER  ENDS

DECLARE_HANDLE(HSTRING_BUFFER)

endif
