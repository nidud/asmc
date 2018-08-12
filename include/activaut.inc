ifndef __REQUIRED_RPCNDR_H_VERSION__
__REQUIRED_RPCNDR_H_VERSION__ equ 475
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
ifndef __activaut_h__
__activaut_h__ equ <>
.pragma list(push, 0)

ifndef __IScriptNode_FWD_DEFINED__
__IScriptNode_FWD_DEFINED__ equ 1
endif
ifndef __IScriptEntry_FWD_DEFINED__
__IScriptEntry_FWD_DEFINED__ equ 1
endif
ifndef __IScriptScriptlet_FWD_DEFINED__
__IScriptScriptlet_FWD_DEFINED__ equ 1
endif
ifndef __IActiveScriptAuthor_FWD_DEFINED__
__IActiveScriptAuthor_FWD_DEFINED__ equ 1
endif
ifndef __IActiveScriptAuthorProcedure_FWD_DEFINED__
__IActiveScriptAuthorProcedure_FWD_DEFINED__ equ 1
endif
include ocidl.inc

ifndef __ActivAut_h
__ActivAut_h equ 1

ifndef _NO_AUTHOR_GUIDS
DEFINE_GUID(CATID_ActiveScriptAuthor, 0xaee2a92, 0xbcbb, 0x11d0, 0x8c, 0x72, 0x0, 0xc0, 0x4f, 0xc2, 0xb0, 0x85)
DEFINE_GUID(IID_IActiveScriptAuthor, 0x9c109da0, 0x7006, 0x11d1, 0xb3, 0x6c, 0x00, 0xa0, 0xc9, 0x11, 0xe8, 0xb2)
DEFINE_GUID(IID_IScriptNode, 0xaee2a94, 0xbcbb, 0x11d0, 0x8c, 0x72, 0x0, 0xc0, 0x4f, 0xc2, 0xb0, 0x85)
DEFINE_GUID(IID_IScriptEntry, 0xaee2a95, 0xbcbb, 0x11d0, 0x8c, 0x72, 0x0, 0xc0, 0x4f, 0xc2, 0xb0, 0x85)
DEFINE_GUID(IID_IScriptScriptlet, 0xaee2a96, 0xbcbb, 0x11d0, 0x8c, 0x72, 0x0, 0xc0, 0x4f, 0xc2, 0xb0, 0x85)
DEFINE_GUID(IID_IActiveScriptAuthorProcedure, 0x7e2d4b70, 0xbd9a, 0x11d0, 0x93, 0x36, 0x0, 0xa0, 0xc9, 0xd, 0xca, 0xa9)
endif

fasaPreferInternalHandler	equ 0x0001
fasaSupportInternalHandler	equ 0x0002
fasaCaseSensitive		equ 0x0004

SCRIPT_CMPL_NOLIST		equ 0x0000
SCRIPT_CMPL_MEMBERLIST		equ 0x0001
SCRIPT_CMPL_ENUMLIST		equ 0x0002
SCRIPT_CMPL_PARAMTIP		equ 0x0004
SCRIPT_CMPL_GLOBALLIST		equ 0x0008
SCRIPT_CMPL_ENUM_TRIGGER	equ 0x0001
SCRIPT_CMPL_MEMBER_TRIGGER	equ 0x0002
SCRIPT_CMPL_PARAM_TRIGGER	equ 0x0003
SCRIPT_CMPL_COMMIT		equ 0x0004

GETATTRTYPE_NORMAL		equ 0x0000
GETATTRTYPE_DEPSCAN		equ 0x0001
GETATTRFLAG_THIS		equ 0x0100
GETATTRFLAG_HUMANTEXT		equ 0x8000

SOURCETEXT_ATTR_HUMANTEXT	equ 0x8000
SOURCETEXT_ATTR_IDENTIFIER	equ 0x0100
SOURCETEXT_ATTR_MEMBERLOOKUP	equ 0x0200
SOURCETEXT_ATTR_THIS		equ 0x0400

SOURCE_TEXT_ATTR	typedef WORD

externdef		__MIDL_itf_activaut_0000_0000_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_activaut_0000_0000_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IScriptNode_INTERFACE_DEFINED__
__IScriptNode_INTERFACE_DEFINED__ equ 1

externdef		IID_IScriptNode:IID

.comdef IScriptNode

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Alive		proc
    Delete		proc
    GetParent		proc :ptr
    GetIndexInParent	proc :ptr
    GetCookie		proc :ptr
    GetNumberOfChildren proc :ptr
    GetChild		proc :ULONG, :ptr
    GetLanguage		proc :ptr
    CreateChildEntry	proc :ULONG, :DWORD, :LPCOLESTR, :ptr
    CreateChildHandler	proc :LPCOLESTR
    .ends

endif

ifndef __IScriptEntry_INTERFACE_DEFINED__
__IScriptEntry_INTERFACE_DEFINED__ equ 1

externdef		IID_IScriptEntry:IID

.comdef IScriptEntry

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Alive		proc
    Delete		proc
    GetParent		proc :ptr
    GetIndexInParent	proc :ptr
    GetCookie		proc :ptr
    GetNumberOfChildren proc :ptr
    GetChild		proc :ULONG, :ptr
    GetLanguage		proc :ptr
    CreateChildEntry	proc :ULONG, :DWORD, :LPCOLESTR, :ptr
    CreateChildHandler	proc :LPCOLESTR
    GetText		proc :ptr
    SetText		proc :LPCOLESTR
    GetBody		proc :ptr
    SetBody		proc :LPCOLESTR
    GetName		proc :ptr
    SetName		proc :LPCOLESTR
    GetItemName		proc :ptr
    SetItemName		proc :LPCOLESTR
    GetSignature	proc :ptr, :ptr
    SetSignature	proc :ptr, :ULONG
    GetRange		proc :ptr, :ptr
    .ends

endif

ifndef __IScriptScriptlet_INTERFACE_DEFINED__
__IScriptScriptlet_INTERFACE_DEFINED__ equ 1

externdef		IID_IScriptScriptlet:IID

.comdef IScriptScriptlet

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Alive		proc
    Delete		proc
    GetParent		proc :ptr
    GetIndexInParent	proc :ptr
    GetCookie		proc :ptr
    GetNumberOfChildren proc :ptr
    GetChild		proc :ULONG, :ptr
    GetLanguage		proc :ptr
    CreateChildEntry	proc :ULONG, :DWORD, :LPCOLESTR, :ptr
    CreateChildHandler	proc :LPCOLESTR
    GetText		proc :ptr
    SetText		proc :LPCOLESTR
    GetBody		proc :ptr
    SetBody		proc :LPCOLESTR
    GetName		proc :ptr
    SetName		proc :LPCOLESTR
    GetItemName		proc :ptr
    SetItemName		proc :LPCOLESTR
    GetSignature	proc :ptr, :ptr
    SetSignature	proc :ptr, :ULONG
    GetRange		proc :ptr, :ptr
    GetSubItemName	proc :ptr
    SetSubItemName	proc :LPCOLESTR
    GetEventName	proc :ptr
    SetEventName	proc :LPCOLESTR
    GetSimpleEventName	proc :ptr
    SetSimpleEventName	proc :LPCOLESTR
    .ends

endif

ifndef __IActiveScriptAuthor_INTERFACE_DEFINED__
__IActiveScriptAuthor_INTERFACE_DEFINED__ equ 1

externdef		IID_IActiveScriptAuthor:IID

.comdef IActiveScriptAuthor

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    AddNamedItem	proc :LPCOLESTR, :DWORD, :ptr
    AddScriptlet	proc :LPCOLESTR, :LPCOLESTR, :LPCOLESTR, :LPCOLESTR, :LPCOLESTR, :LPCOLESTR, :DWORD, :DWORD
    ParseScriptText	proc :LPCOLESTR, :LPCOLESTR, :LPCOLESTR, :DWORD, :DWORD
    GetScriptTextAttributes proc :ptr
    GetScriptletTextAttributes proc :ptr
    GetRoot		proc :ptr
    GetLanguageFlags	proc :ptr
    GetEventHandler	proc :ptr, :LPCOLESTR, :LPCOLESTR, :LPCOLESTR, :ptr
    RemoveNamedItem	proc :LPCOLESTR
    AddTypeLib		proc :REFGUID, :DWORD, :DWORD, :DWORD
    RemoveTypeLib	proc :REFGUID, :DWORD, :DWORD
    GetChars		proc :DWORD, :ptr
    GetInfoFromContext	proc :LPCOLESTR, :ULONG, :ULONG, :DWORD, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
    IsCommitChar	proc :OLECHAR, :ptr
    .ends

endif

ifndef __IActiveScriptAuthorProcedure_INTERFACE_DEFINED__
__IActiveScriptAuthorProcedure_INTERFACE_DEFINED__ equ 1

externdef		IID_IActiveScriptAuthorProcedure:IID

.comdef IActiveScriptAuthorProcedure

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    ParseProcedureText	proc :LPCOLESTR, :LPCOLESTR, :LPCOLESTR, :LPCOLESTR, :LPCOLESTR, :DWORD, :DWORD, :ptr
    .ends

endif

endif  ;; __ActivAut_h

externdef		__MIDL_itf_activaut_0000_0005_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_activaut_0000_0005_v0_0_s_ifspec:RPC_IF_HANDLE

;DWORD
BSTR_UserSize proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr BSTR

;LPSTR
BSTR_UserMarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr BSTR

;LPSTR
BSTR_UserUnmarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr BSTR

;void
BSTR_UserFree proto WINAPI \
		      : ptr DWORD,
		      : ptr BSTR


;DWORD
BSTR_UserSize64 proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr BSTR

;LPSTR
BSTR_UserMarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr BSTR

;LPSTR
BSTR_UserUnmarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr BSTR

;void
BSTR_UserFree64 proto WINAPI \
		      : ptr DWORD,
		      : ptr BSTR

.pragma list(pop)
endif
