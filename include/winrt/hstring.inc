ifndef __REQUIRED_RPCNDR_H_VERSION__
__REQUIRED_RPCNDR_H_VERSION__ equ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
__REQUIRED_RPCSAL_H_VERSION__ equ 100
endif

include rpc.inc
include rpcndr.inc

ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr.inc>
endif

ifndef __hstring_h__
define __hstring_h__

include wtypes.inc

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
