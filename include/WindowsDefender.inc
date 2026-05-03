ifndef _WINAPIFAMILY_
include winapifamily.inc
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
WDStatus proto WINAPI :ptr BOOL
WDEnable proto WINAPI :BOOL
endif
