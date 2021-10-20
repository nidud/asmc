
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

include UIAutomationCore.inc
include UIAutomationClient.inc
include UIAutomationCoreApi.inc

endif

