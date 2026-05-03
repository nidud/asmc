ifndef _RPCNDR500_
include rpcndr500.inc
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
