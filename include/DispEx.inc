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

ifndef __dispex_h__
__dispex_h__ equ <>

ifndef __IDispatchEx_FWD_DEFINED__
__IDispatchEx_FWD_DEFINED__ equ 1
endif
ifndef __IDispError_FWD_DEFINED__
__IDispError_FWD_DEFINED__ equ 1
endif
ifndef __IVariantChangeType_FWD_DEFINED__
__IVariantChangeType_FWD_DEFINED__ equ 1
endif
ifndef __IObjectIdentity_FWD_DEFINED__
__IObjectIdentity_FWD_DEFINED__ equ 1
endif
ifndef __ICanHandleException_FWD_DEFINED__
__ICanHandleException_FWD_DEFINED__ equ 1
endif
ifndef __IProvideRuntimeContext_FWD_DEFINED__
__IProvideRuntimeContext_FWD_DEFINED__ equ 1
endif

include ocidl.inc

.pragma comment(lib, uuid)

ifndef DISPEX_H_
DISPEX_H_ equ <>

include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

include servprov.inc

ifndef _NO_DISPATCHEX_GUIDS

DEFINE_GUID(IID_IDispatchEx, 0xa6ef9860, 0xc720, 0x11d0, 0x93, 0x37, 0x0, 0xa0, 0xc9, 0xd, 0xca, 0xa9);
DEFINE_GUID(IID_IDispError, 0xa6ef9861, 0xc720, 0x11d0, 0x93, 0x37, 0x0, 0xa0, 0xc9, 0xd, 0xca, 0xa9);
DEFINE_GUID(IID_IVariantChangeType, 0xa6ef9862, 0xc720, 0x11d0, 0x93, 0x37, 0x0, 0xa0, 0xc9, 0xd, 0xca, 0xa9);
DEFINE_GUID(SID_VariantConversion, 0x1f101481, 0xbccd, 0x11d0, 0x93, 0x36, 0x0, 0xa0, 0xc9, 0xd, 0xca, 0xa9);
DEFINE_GUID(SID_GetCaller, 0x4717cc40, 0xbcb9, 0x11d0, 0x93, 0x36, 0x0, 0xa0, 0xc9, 0xd, 0xca, 0xa9);
DEFINE_GUID(SID_ProvideRuntimeContext, 0x74a5040c, 0xdd0c, 0x48f0, 0xac, 0x85, 0x19, 0x4c, 0x32, 0x59, 0x18, 0xa);
DEFINE_GUID(IID_IProvideRuntimeContext, 0x10e2414a, 0xec59, 0x49d2, 0xbc, 0x51, 0x5a, 0xdd, 0x2c, 0x36, 0xfe, 0xbc);
DEFINE_GUID(IID_IObjectIdentity, 0xca04b7e6, 0xd21, 0x11d1, 0x8c, 0xc5, 0x0, 0xc0, 0x4f, 0xc2, 0xb0, 0x85);
DEFINE_GUID(IID_ICanHandleException, 0xc5598e60, 0xb307, 0x11d1, 0xb2, 0x7d, 0x0, 0x60, 0x08, 0xc3, 0xfb, 0xfb);
SID_GetScriptSite equ <IID_IActiveScriptSite>

endif


ifndef _NO_DISPATCHEX_CONSTS

fdexNameCaseSensitive	equ 0x00000001
fdexNameEnsure		equ 0x00000002
fdexNameImplicit	equ 0x00000004
fdexNameCaseInsensitive equ 0x00000008
fdexNameInternal	equ 0x00000010
fdexNameNoDynamicProperties equ 0x00000020

fdexPropCanGet		equ 0x00000001
fdexPropCannotGet	equ 0x00000002
fdexPropCanPut		equ 0x00000004
fdexPropCannotPut	equ 0x00000008
fdexPropCanPutRef	equ 0x00000010
fdexPropCannotPutRef	equ 0x00000020
fdexPropNoSideEffects	equ 0x00000040
fdexPropDynamicType	equ 0x00000080
fdexPropCanCall		equ 0x00000100
fdexPropCannotCall	equ 0x00000200
fdexPropCanConstruct	equ 0x00000400
fdexPropCannotConstruct equ 0x00000800
fdexPropCanSourceEvents equ 0x00001000
fdexPropCannotSourceEvents equ 0x00002000

grfdexPropCanAll equ (fdexPropCanGet or fdexPropCanPut or fdexPropCanPutRef or \
	fdexPropCanCall or fdexPropCanConstruct or fdexPropCanSourceEvents)
grfdexPropCannotAll equ (fdexPropCannotGet or fdexPropCannotPut or fdexPropCannotPutRef | \
	fdexPropCannotCall or fdexPropCannotConstruct or fdexPropCannotSourceEvents)
grfdexPropExtraAll equ (fdexPropNoSideEffects or fdexPropDynamicType)
grfdexPropAll equ (grfdexPropCanAll or grfdexPropCannotAll or grfdexPropExtraAll)

fdexEnumDefault		equ 0x00000001
fdexEnumAll		equ 0x00000002

DISPATCH_CONSTRUCT	equ 0x4000

DISPID_THIS		equ (-613)
DISPID_STARTENUM	equ <DISPID_UNKNOWN>

endif

ifndef __IDispatchEx_INTERFACE_DEFINED__
__IDispatchEx_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDispatchEx, "A6EF9860-C720-11d0-9337-00A0C90DCAA9")

.comdef IDispatchEx : public IDispatch

    GetDispID		proc :BSTR, :DWORD, :ptr
    InvokeEx		proc :DISPID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    DeleteMemberByName	proc :BSTR, :DWORD
    DeleteMemberByDispID proc :DISPID
    GetMemberProperties proc :DISPID, :DWORD, :ptr
    GetMemberName	proc :DISPID, :ptr
    GetNextDispID	proc :DWORD, :DISPID, :ptr
    GetNameSpaceParent	proc :ptr
    .ends

endif

ifndef __IDispError_INTERFACE_DEFINED__
__IDispError_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDispError, "A6EF9861-C720-11d0-9337-00A0C90DCAA9")

.comdef IDispError : public IUnknown

    QueryErrorInfo	proc :GUID, :ptr
    GetNext		proc :ptr
    GetHresult		proc :ptr
    GetSource		proc :ptr
    GetHelpInfo		proc :ptr, :ptr
    GetDescription	proc :ptr
    .ends

endif

ifndef __IVariantChangeType_INTERFACE_DEFINED__
__IVariantChangeType_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IVariantChangeType, "A6EF9862-C720-11d0-9337-00A0C90DCAA9")

.comdef IVariantChangeType : public IUnknown

    ChangeType		proc :ptr, :ptr, :LCID, :VARTYPE
    .ends

endif

ifndef __IObjectIdentity_INTERFACE_DEFINED__
__IObjectIdentity_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IObjectIdentity, "CA04B7E6-0D21-11d1-8CC5-00C04FC2B085")

.comdef IObjectIdentity : public IUnknown

    IsEqualObject	proc :ptr
    .ends

endif

ifndef __ICanHandleException_INTERFACE_DEFINED__
__ICanHandleException_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ICanHandleException, "c5598e60-b307-11d1-b27d-006008c3fbfb")

.comdef ICanHandleException : public IUnknown

    CanHandleException	proc :ptr, :ptr
    .ends

endif

ifndef __IProvideRuntimeContext_INTERFACE_DEFINED__
__IProvideRuntimeContext_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IProvideRuntimeContext, "10E2414A-EC59-49d2-BC51-5ADD2C36FEBC")

.comdef IProvideRuntimeContext : public IUnknown

    GetCurrentSourceContext proc :ptr, :ptr
    .ends

endif

endif
endif
endif
