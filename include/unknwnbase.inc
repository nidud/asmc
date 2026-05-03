ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __unknwnbase_h__
define __unknwnbase_h__
ifndef __wtypesbase_h__
include wtypesbase.inc
endif

ifndef __IUnknown_INTERFACE_DEFINED__
define __IUnknown_INTERFACE_DEFINED__

DEFINE_IIDX(IUnknown, "00000000-0000-0000-C000-000000000046")

.comdef IUnknown

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
   .ends

    LPUNKNOWN typedef ptr IUnknown

endif

ifndef __AsyncIUnknown_INTERFACE_DEFINED__
define __AsyncIUnknown_INTERFACE_DEFINED__

DEFINE_IIDX(AsyncIUnknown, "000e0000-0000-0000-C000-000000000046")

.comdef AsyncIUnknown : public IUnknown

    Begin_QueryInterface proc :REFIID
    Finish_QueryInterface proc :ptr
    Begin_AddRef	proc
    Finish_AddRef	proc
    Begin_Release	proc
    Finish_Release	proc
   .ends

endif

ifndef __IClassFactory_INTERFACE_DEFINED__
define __IClassFactory_INTERFACE_DEFINED__

DEFINE_IIDX(IClassFactory, "00000001-0000-0000-C000-000000000046")

.comdef IClassFactory : public IUnknown

    CreateInstance	proc :ptr, :REFIID, :ptr
    LockServer		proc :BOOL
   .ends

    LPCLASSFACTORY typedef ptr IClassFactory

endif

endif
