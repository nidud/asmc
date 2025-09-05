ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __wtypes_h__
include wtypes.inc
endif

ifndef __unknwn_h__
define __unknwn_h__

ifndef __SAFE_RELEASE
define __SAFE_RELEASE
SafeRelease proto fastcall p:abs {
    mov rax,p
    .if rax
	mov p,NULL
	[rax].@SubStr(typeid(p), 4).Release()
    .endif
    }
SafeReplace proto fastcall :ptr ptr, :ptr {
   .new prev_ptr:ptr
    mov rax,[rcx]
    mov [rcx],rdx
    mov prev_ptr,rcx
    .if rax
	[rax].IUnknown.Release()
	mov rcx,prev_ptr
    .endif
    mov rax,[rcx]
    .if rax
	[rax].IUnknown.AddRef()
    .endif
    }
endif

.pragma comment(lib, rpcrt4)

ifndef __IUnknown_INTERFACE_DEFINED__
define __IUnknown_INTERFACE_DEFINED__

DEFINE_IIDX(IUnknown, "00000000-0000-0000-C000-000000000046")

.comdef IUnknown

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
   .ends

LPUNKNOWN		typedef ptr IUnknown

endif

ifndef __IClassFactory_INTERFACE_DEFINED__
define __IClassFactory_INTERFACE_DEFINED__

DEFINE_IIDX(IClassFactory, "00000001-0000-0000-C000-000000000046")

.comdef IClassFactory : public IUnknown

    CreateInstance	proc :ptr, :REFIID, :ptr
    LockServer		proc :BOOL
   .ends

LPCLASSFACTORY		typedef ptr IClassFactory

endif

endif
