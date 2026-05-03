ifndef _RPCNDR500_
include rpcndr500.inc
endif

ifndef __imessagedispatcher_h__
define __imessagedispatcher_h__

include Inspectable.inc

ifndef _WINAPIFAMILY_
include winapifamily.inc
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef __IMessageDispatcher_INTERFACE_DEFINED__
define __IMessageDispatcher_INTERFACE_DEFINED__

DEFINE_IIDX(IMessageDispatcher, "F5F84C8F-CFD0-4CD6-B66B-C5D26FF1689D")

.comdef IMessageDispatcher : public IInspectable

    PumpMessages	proc
   .ends

endif
endif

endif


