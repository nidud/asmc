ifndef __unknwn_h__
__unknwn_h__ equ <>

ifndef __REQUIRED_RPCNDR_H_VERSION__
__REQUIRED_RPCNDR_H_VERSION__ equ 440
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

include wtypes.inc

.pragma comment(lib, rpcrt4)

ifndef __IUnknown_INTERFACE_DEFINED__
__IUnknown_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IUnknown, "00000000-0000-0000-C000-000000000046")

.comdef IUnknown

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc

    .ends

LPUNKNOWN		typedef ptr IUnknown

endif

ifndef __IClassFactory_INTERFACE_DEFINED__
__IClassFactory_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IClassFactory, "00000001-0000-0000-C000-000000000046")

.comdef IClassFactory : public IUnknown

    CreateInstance	proc :ptr, :REFIID, :ptr
    LockServer		proc :BOOL

    .ends

LPCLASSFACTORY		typedef ptr IClassFactory

endif

endif
