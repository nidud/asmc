ifndef __REQUIRED_RPCNDR_H_VERSION__
__REQUIRED_RPCNDR_H_VERSION__ equ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
__REQUIRED_RPCSAL_H_VERSION__ equ 100
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
__activation_h__ equ <>

ifndef __IActivationFactory_FWD_DEFINED__
__IActivationFactory_FWD_DEFINED__ equ 1
endif

include inspectable.inc

ifndef __IActivationFactory_INTERFACE_DEFINED__
__IActivationFactory_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IActivationFactory, "00000035-0000-0000-C000-000000000046")

.comdef IActivationFactory : public IInspectable

    ActivateInstance	proc :ptr
    .ends

    PACTIVATIONFACTORY	typedef ptr IActivationFactory

endif

endif
