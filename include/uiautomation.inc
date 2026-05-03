ifndef _WINAPIFAMILY_
include winapifamily.inc
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

include uiautomationcore.inc
include uiautomationclient.inc
include uiautomationCoreapi.inc

endif
