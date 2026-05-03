.pragma list(push, 0)
ifndef _GUIDDEF_H_
define _GUIDDEF_H_

ifndef GUID_DEFINED
define GUID_DEFINED
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

ifndef __PE__
includelib uuid.lib
endif

ifndef __LPGUID_DEFINED__
define __LPGUID_DEFINED__
LPGUID	typedef ptr GUID
endif

ifndef __LPCGUID_DEFINED__
define __LPCGUID_DEFINED__
LPCGUID typedef ptr GUID
endif

ifndef __IID_DEFINED__
define __IID_DEFINED__
IID	typedef GUID
LPIID	typedef ptr IID
define	IID_NULL <GUID_NULL>
IsEqualIID macro riid1, riid2
	exitm<IsEqualGUID(riid1, riid2)>
	endm
CLSID	typedef GUID
LPCLSID typedef ptr CLSID
define	CLSID_NULL <GUID_NULL>
IsEqualCLSID macro rclsid1, rclsid2
	exitm<IsEqualGUID(rclsid1, rclsid2)>
	endm
FMTID	typedef GUID
LPFMTID typedef ptr FMTID
define	FMTID_NULL <GUID_NULL>
IsEqualFMTID macro rfmtid1, rfmtid2
	exitm<IsEqualGUID(rfmtid1, rfmtid2)>
	endm

ifndef _REFGUID_DEFINED
define _REFGUID_DEFINED
REFGUID typedef ptr IIDGUID
endif

ifndef _REFIID_DEFINED
define _REFIID_DEFINED
REFIID	typedef ptr IID
endif

ifndef _REFCLSID_DEFINED
define _REFCLSID_DEFINED
REFCLSID typedef ptr IID
endif

ifndef _REFFMTID_DEFINED
define _REFFMTID_DEFINED
REFFMTID typedef ptr IID
endif

endif

ifndef _SYS_GUID_OPERATORS_
define _SYS_GUID_OPERATORS_
IsEqualGUID proto fastcall :ptr, :ptr {
	mov rax,[rcx]
	sub rax,[rdx]
ifndef _WIN64
	add eax,[rcx+4]
	sub eax,[rdx+4]
	add eax,[rcx+12]
	sub eax,[rdx+12]
endif
	add rax,[rcx+8]
	sub rax,[rdx+8]
	mov eax,0
	setz al
	retm<eax>
	}

IsEqualIID macro riid1, riid2
	exitm<IsEqualGUID(riid1, riid2)>
	endm
IsEqualCLSID macro rclsid1, rclsid2
	exitm<IsEqualGUID(rclsid1, rclsid2)>
	endm
endif
endif
.pragma list(pop)
