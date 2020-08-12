include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifdef MANAGED_ENUMS

ifndef _MANAGED
.err <"you can only generate managed enums when compiling managed code">
endif

ifdef USING_EHRECVR_NAMESPACE
else
endif

else

ifdef __midl
else
endif
endif
endif

