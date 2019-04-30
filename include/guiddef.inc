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
DEFINE_GUID macro id, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8
if defined(__PE__) or defined(__GUID__)
_&id& equ <{l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}>
elseifdef INITGUID
echo id GUID {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}
else
externdef id:GUID
endif
    exitm<>
    endm
endif

DEFINE_OLEGUID macro id, l, w1, w2
    exitm<DEFINE_GUID(id, l, w1, w2, 0xC0,0,0,0,0,0,0,0x46)>
    endm

ifndef DEFINE_GUIDS

DEFINE_GUIDS macro id, x
    DEFINE_GUID(id, \
	@CatStr(<0x>, @SubStr(x, 2,8)), \
	@CatStr(<0x>, @SubStr(x,11,4)), \
	@CatStr(<0x>, @SubStr(x,16,4)), \
	@CatStr(<0x>, @SubStr(x,21,2)), \
	@CatStr(<0x>, @SubStr(x,23,2)), \
	@CatStr(<0x>, @SubStr(x,26,2)), \
	@CatStr(<0x>, @SubStr(x,28,2)), \
	@CatStr(<0x>, @SubStr(x,30,2)), \
	@CatStr(<0x>, @SubStr(x,32,2)), \
	@CatStr(<0x>, @SubStr(x,34,2)), \
	@CatStr(<0x>, @SubStr(x,36,2)))
	exitm<>
	endm

DEFINE_IIDX macro name, x
    DEFINE_GUID(IID_&name&, \
	@CatStr(<0x>, @SubStr(x, 2,8)), \
	@CatStr(<0x>, @SubStr(x,11,4)), \
	@CatStr(<0x>, @SubStr(x,16,4)), \
	@CatStr(<0x>, @SubStr(x,21,2)), \
	@CatStr(<0x>, @SubStr(x,23,2)), \
	@CatStr(<0x>, @SubStr(x,26,2)), \
	@CatStr(<0x>, @SubStr(x,28,2)), \
	@CatStr(<0x>, @SubStr(x,30,2)), \
	@CatStr(<0x>, @SubStr(x,32,2)), \
	@CatStr(<0x>, @SubStr(x,34,2)), \
	@CatStr(<0x>, @SubStr(x,36,2)))
	exitm<>
	endm

endif

ifndef _GUIDDEF_H_
_GUIDDEF_H_ equ <>
ifndef __PE__
;includelib uuid.lib
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

ifndef _REFGUID_DEFINED
_REFGUID_DEFINED	equ <>
REFGUID			typedef ptr IIDGUID
endif

ifndef _REFIID_DEFINED
_REFIID_DEFINED		equ <>
REFIID			typedef ptr IID
endif

ifndef _REFCLSID_DEFINED
_REFCLSID_DEFINED	equ <>
REFCLSID		typedef ptr IID
endif

ifndef _REFFMTID_DEFINED
_REFFMTID_DEFINED	equ <>
REFFMTID		typedef ptr IID
endif

endif

ifndef __midl
ifndef _SYS_GUID_OPERATORS_
_SYS_GUID_OPERATORS_	equ <>
include string.inc

InlineIsEqualGUID macro rguid1, rguid2
ifdef _WIN64
	_mm_loadreg(rcx, rguid1)
	_mm_loadreg(rdx, rguid2)
	mov rax,[rcx]
	sub rax,[rdx]
	.ifz
	    mov rax,[rcx+8]
	    sub rax,[rdx+8]
	.endif
	.if rax
else
	.if memcmp(rguid1, rguid2, sizeof(GUID))
endif
	    xor eax,eax
	.else
	    inc eax
	.endif
	retm<eax>
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
