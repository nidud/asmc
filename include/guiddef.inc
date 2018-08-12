.pragma list(push, 0)
ifndef GUID_DEFINED
GUID_DEFINED equ <>
GUID	STRUC
Data1	dd ?
Data2	dw ?
Data3	dw ?
Data4	db 8 dup(?)
GUID	ENDS
endif

ifndef DEFINE_GUID
DEFINE_GUID macro name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8
ifdef __PE__
_&name& equ <{l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}>
elseifdef INITGUID
echo name GUID {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}
else
externdef name:GUID
endif
    exitm<>
    endm
endif

DEFINE_OLEGUID macro name, l, w1, w2
    exitm<DEFINE_GUID(name, l, w1, w2, 0xC0,0,0,0,0,0,0,0x46)>
    endm

ifndef _GUIDDEF_H_
_GUIDDEF_H_ equ <>
ifndef __PE__
includelib uuid.lib
endif

ifndef __LPGUID_DEFINED__
__LPGUID_DEFINED__	equ 1
LPGUID			typedef ptr GUID
endif

ifndef __LPCGUID_DEFINED__
__LPCGUID_DEFINED__	equ 1
LPCGUID			typedef ptr GUID
endif

ifndef __IID_DEFINED__
__IID_DEFINED__		equ 1
IID			typedef GUID
LPIID			typedef ptr IID
IID_NULL		equ <GUID_NULL>
IsEqualIID macro riid1, riid2
	exitm<IsEqualGUID(riid1, riid2)>
	endm
CLSID			typedef GUID
LPCLSID			typedef ptr CLSID
CLSID_NULL		equ <GUID_NULL>
IsEqualCLSID macro rclsid1, rclsid2
	exitm<IsEqualGUID(rclsid1, rclsid2)>
	endm
FMTID			typedef GUID
LPFMTID			typedef ptr FMTID
FMTID_NULL		equ <GUID_NULL>
IsEqualFMTID macro rfmtid1, rfmtid2
	exitm<IsEqualGUID(rfmtid1, rfmtid2)>
	endm

if 0
ifdef __midl_proxy
__MIDL_CONST		equ <>
else
__MIDL_CONST		equ <>
endif
endif

ifndef _REFGUID_DEFINED
_REFGUID_DEFINED	equ <>
REFGUID			equ <LPGUID>
endif

ifndef _REFIID_DEFINED
_REFIID_DEFINED		equ <>
REFIID			equ <LPIID>
endif

ifndef _REFCLSID_DEFINED
_REFCLSID_DEFINED	equ <>
REFCLSID		equ <LPIID>
endif

ifndef _REFFMTID_DEFINED
_REFFMTID_DEFINED	equ <>
REFFMTID		equ <LPIID>
endif

endif

ifndef __midl
ifndef _SYS_GUID_OPERATORS_
_SYS_GUID_OPERATORS_	equ <>
include string.inc

InlineIsEqualGUID macro rguid1, rguid2
	.if !memcmp(rguid1, rguid2, sizeof(GUID))
	    inc eax
	.else
	    xor eax,eax
	.endif
	exitm<eax>
	endm
IsEqualGUID macro rguid1, rguid2
	exitm<InlineIsEqualGUID(rguid1, rguid2)>
	endm


IsEqualIID macro riid1, riid2
	exitm<IsEqualGUID(riid1, riid2)>
	endm
IsEqualCLSID macro rclsid1, rclsid2
	exitm<IsEqualGUID(rclsid1, rclsid2)>
	endm

endif
endif
endif
.pragma list(pop)
