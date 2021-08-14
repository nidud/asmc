ifndef __UNKNWN_INC
define __UNKNWN_INC

ifndef __REQUIRED_RPCNDR_H_VERSION__
define __REQUIRED_RPCNDR_H_VERSION__ 440
endif

include rpc.inc
include rpcndr.inc

ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr.inc>
endif

ifndef __SAFE_RELEASE
define __SAFE_RELEASE
SafeRelease proto fastcall p:abs {
    mov rax,p
    .if rax
	mov p,NULL
	[rax].@SubStr(typeid(p), 2).Release()
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
ComAlloc proto fastcall class:abs {
    .return .if !HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, class + &class&Vtbl)
    lea rdx,[rax+class]
    mov [rax],rdx
ifdef &class&Type
%   for q,<&class&Type>
      mov [rdx].&class&Vtbl.q,&&class&_&q
      endm
endif
    }
ComFree proto fastcall p:abs {
    HeapFree(GetProcessHeap(), 0, p)
    }
endif

ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif

include wtypes.inc

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
