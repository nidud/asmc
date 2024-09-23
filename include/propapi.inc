include winapifamily.inc

ifndef _PROPAPI_H_
define _PROPAPI_H_

NTPROP typedef ptr

include propidl.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
StgPropertyLengthAsVariant proto WINAPI :ptr, :ULONG, :USHORT, :BYTE
endif
endif
