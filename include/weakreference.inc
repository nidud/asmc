ifndef __REQUIRED_RPCNDR_H_VERSION__
__REQUIRED_RPCNDR_H_VERSION__ equ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
__REQUIRED_RPCSAL_H_VERSION__ equ 100
endif

include rpc.inc
include rpcndr.inc

ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr.inc>
endif

ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif

ifndef __weakreference_h__
__weakreference_h__ equ <>

ifndef __IWeakReference_FWD_DEFINED__
__IWeakReference_FWD_DEFINED__ equ <>
endif
ifndef __IWeakReferenceSource_FWD_DEFINED__
__IWeakReferenceSource_FWD_DEFINED__ equ <>
endif

include inspectable.inc

ifndef __IWeakReference_INTERFACE_DEFINED__
__IWeakReference_INTERFACE_DEFINED__ equ <>

DEFINE_IIDX(IWeakReference, "00000037-0000-0000-C000-000000000046")

.comdef IWeakReference : public IUnknown

    Resolve proc :REFIID, :ptr ptr IInspectable
    .ends

endif

ifndef __IWeakReferenceSource_INTERFACE_DEFINED__
__IWeakReferenceSource_INTERFACE_DEFINED__ equ <>

DEFINE_IIDX(IWeakReferenceSource, "00000038-0000-0000-C000-000000000046")

.comdef IWeakReferenceSource : public IUnknown

    GetWeakReference proc :ptr ptr IWeakReference
    .ends

endif

endif
