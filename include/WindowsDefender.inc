include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

WDStatus proto WINAPI :ptr BOOL
WDEnable proto WINAPI :BOOL

endif

