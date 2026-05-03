ifndef _WINAPIFAMILY_
include winapifamily.inc
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

include IMessageDispatcher.inc

PMessageDispatcher typedef ptr IMessageDispatcher
if (NTDDI_VERSION GE NTDDI_WIN8)
CoSetMessageDispatcher proto WINAPI :PMessageDispatcher
CoHandlePriorityEventsFromMessagePump proto WINAPI
endif

endif
