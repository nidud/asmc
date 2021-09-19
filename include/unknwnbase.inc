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

ifndef __unknwnbase_h__
define __unknwnbase_h__

include wtypesbase.inc
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

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

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

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

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
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

endif
