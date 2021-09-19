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

ifndef __activation_h__
define __activation_h__

include inspectable.inc

ifndef __IActivationFactory_INTERFACE_DEFINED__
define __IActivationFactory_INTERFACE_DEFINED__

DEFINE_IIDX(IActivationFactory, "00000035-0000-0000-C000-000000000046")

.comdef IActivationFactory : public IInspectable

    ActivateInstance	proc :ptr
   .ends
    PACTIVATIONFACTORY	typedef ptr IActivationFactory

endif
endif
