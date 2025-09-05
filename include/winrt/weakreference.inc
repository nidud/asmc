ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __weakreference_h__
define __weakreference_h__

include inspectable.inc

ifndef __IWeakReference_INTERFACE_DEFINED__
define __IWeakReference_INTERFACE_DEFINED__

DEFINE_IIDX(IWeakReference, "00000037-0000-0000-C000-000000000046")

.comdef IWeakReference : public IUnknown

    Resolve proc :REFIID, :ptr
   .ends

endif

ifndef __IWeakReferenceSource_INTERFACE_DEFINED__
define __IWeakReferenceSource_INTERFACE_DEFINED__

DEFINE_IIDX(IWeakReferenceSource, "00000038-0000-0000-C000-000000000046")

.comdef IWeakReferenceSource : public IUnknown

    GetWeakReference proc :ptr
   .ends

endif
endif
