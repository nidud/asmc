ifndef __REQUIRED_RPCNDR_H_VERSION__
define __REQUIRED_RPCNDR_H_VERSION__ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
define __REQUIRED_RPCSAL_H_VERSION__ 100
endif

include rpc.inc
include rpcndr.inc
ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr.h>
endif
ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif

ifndef __imessagedispatcher_h__
define __imessagedispatcher_h__

include Inspectable.inc

include winapifamily.inc

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


