ifndef _ACLUI_H_
define _ACLUI_H_
include objbase.inc
include commctrl.inc
include accctrl.inc
.pragma list(push, 0)
.pragma comment(lib, aclui)

SI_OBJECT_INFO		STRUC
dwFlags			dd ?
hInstance		HINSTANCE ?
pszServerName		LPWSTR ?
pszObjectName		LPWSTR ?
pszPageTitle		LPWSTR ?
guidObjectType		GUID <>
SI_OBJECT_INFO		ENDS
PSI_OBJECT_INFO		typedef ptr SI_OBJECT_INFO

SI_EDIT_PERMS		equ 0x00000000
SI_EDIT_OWNER		equ 0x00000001
SI_EDIT_AUDITS		equ 0x00000002
SI_CONTAINER		equ 0x00000004
SI_READONLY		equ 0x00000008
SI_ADVANCED		equ 0x00000010
SI_RESET		equ 0x00000020
SI_OWNER_READONLY	equ 0x00000040
SI_EDIT_PROPERTIES	equ 0x00000080
SI_OWNER_RECURSE	equ 0x00000100
SI_NO_ACL_PROTECT	equ 0x00000200
SI_NO_TREE_APPLY	equ 0x00000400
SI_PAGE_TITLE		equ 0x00000800
SI_SERVER_IS_DC		equ 0x00001000
SI_RESET_DACL_TREE	equ 0x00004000
SI_RESET_SACL_TREE	equ 0x00008000
SI_OBJECT_GUID		equ 0x00010000
SI_EDIT_EFFECTIVE	equ 0x00020000
SI_RESET_DACL		equ 0x00040000
SI_RESET_SACL		equ 0x00080000
SI_RESET_OWNER		equ 0x00100000
SI_NO_ADDITIONAL_PERMISSION equ 0x00200000
if (NTDDI_VERSION GE NTDDI_VISTA)
SI_VIEW_ONLY		equ 0x00400000
SI_PERMS_ELEVATION_REQUIRED equ 0x01000000
SI_AUDITS_ELEVATION_REQUIRED equ 0x02000000
SI_OWNER_ELEVATION_REQUIRED equ 0x04000000
endif
SI_MAY_WRITE		equ 0x10000000
SI_EDIT_ALL		equ (SI_EDIT_PERMS OR SI_EDIT_OWNER OR SI_EDIT_AUDITS)

SI_ACCESS		STRUC
pguid			LPGUID ?
mask			ACCESS_MASK ?
pszName			LPCWSTR ?
dwFlags			dd ?
SI_ACCESS		ENDS
PSI_ACCESS		typedef ptr SI_ACCESS

SI_ACCESS_SPECIFIC	equ 0x00010000
SI_ACCESS_GENERAL	equ 0x00020000
SI_ACCESS_CONTAINER	equ 0x00040000
SI_ACCESS_PROPERTY	equ 0x00080000

SI_INHERIT_TYPE		STRUC
pguid			LPGUID ?
dwFlags			ULONG ?
pszName			LPCWSTR ?
SI_INHERIT_TYPE		ENDS
PSI_INHERIT_TYPE	typedef ptr SI_INHERIT_TYPE

.enum SI_PAGE_TYPE {
    SI_PAGE_PERM=0,
    SI_PAGE_ADVPERM,
    SI_PAGE_AUDIT,
    SI_PAGE_OWNER,
    SI_PAGE_EFFECTIVE,
if (NTDDI_VERSION GE NTDDI_VISTA)
    SI_PAGE_TAKEOWNERSHIP,
endif
}

PSPCB_SI_INITDIALOG	equ (WM_USER + 1)
DEFINE_IIDX(ISecurityInformation, "965FC360-16FF-11d0-91CB-00AA00BBB723")

.comdef ISecurityInformation : public IUnknown

    GetObjectInformation proc :PSI_OBJECT_INFO
    GetSecurity		proc :SECURITY_INFORMATION, :ptr PSECURITY_DESCRIPTOR, :BOOL
    SetSecurity		proc :SECURITY_INFORMATION, :PSECURITY_DESCRIPTOR
    GetAccessRights	proc :ptr GUID, :DWORD, :ptr PSI_ACCESS, :ptr, :ptr
    MapGeneric		proc :ptr GUID, :ptr UCHAR, :ptr ACCESS_MASK
    GetInheritTypes	proc :PSI_INHERIT_TYPE, :ULONG
    PropertySheetPageCallback proc :HWND, :UINT, :SI_PAGE_TYPE

    .ends

LPSECURITYINFO		typedef ptr ISecurityInformation

DEFINE_IIDX(ISecurityInformation2, "c3ccfdb4-6f88-11d2-a3ce-00c04fb1782a")

.comdef ISecurityInformation2 : public IUnknown

    IsDaclCanonical	proc :PACL
    LookupSids		proc :ULONG, :ptr PSID, :ptr LPDATAOBJECT

    .ends

LPSECURITYINFO2		typedef ptr ISecurityInformation2

CFSTR_ACLUI_SID_INFO_LIST equ TEXT("CFSTR_ACLUI_SID_INFO_LIST")

SID_INFO		STRUC
pSid			PSID ?
pwzCommonName		PWSTR ?
pwzClass		PWSTR ?
pwzUPN			PWSTR ?
SID_INFO		ENDS
PSID_INFO		typedef ptr SID_INFO
SID_INFO_LIST		STRUC
cItems			ULONG ?
aSidInfo		SID_INFO ANYSIZE_ARRAY dup(<>)
SID_INFO_LIST		ENDS
PSID_INFO_LIST		typedef ptr SID_INFO_LIST

DEFINE_IIDX(IEffectivePermission, "3853DC76-9F35-407c-88A1-D19344365FBC")

.comdef IEffectivePermission : public IUnknown

    GetEffectivePermission proc :ptr GUID, :PSID, :LPCWSTR, :PSECURITY_DESCRIPTOR, :ptr POBJECT_TYPE_LIST, :ptr ULONG, :ptr PACCESS_MASK, :ULONG
    .ends
    LPEFFECTIVEPERMISSION typedef ptr IEffectivePermission

DEFINE_IIDX(ISecurityObjectTypeInfo, "FC3066EB-79EF-444b-9111-D18A75EBF2FA")

.comdef ISecurityObjectTypeInfo : public IUnknown

    GetInheritSource proc :SECURITY_INFORMATION, :PACL, :ptr PINHERITED_FROM
    .ends
    LPSecurityObjectTypeInfo typedef ptr ISecurityObjectTypeInfo

if (NTDDI_VERSION GE NTDDI_VISTA)

DEFINE_IIDX(ISecurityInformation3, "E2CDC9CC-31BD-4f8f-8C8B-B641AF516A1A")

.comdef ISecurityInformation3 : public IUnknown

    GetFullResourceName proc :ptr LPWSTR
    OpenElevatedEditor proc :HWND, :SI_PAGE_TYPE

    .ends
    LPSECURITYINFO3 typedef ptr ISecurityInformation3
endif

DEFINE_GUID(IID_ISecurityInformation, 0x965fc360, 0x16ff, 0x11d0, 0x91, 0xcb, 0x0, 0xaa, 0x0, 0xbb, 0xb7, 0x23)
DEFINE_GUID(IID_ISecurityInformation2, 0xc3ccfdb4, 0x6f88, 0x11d2, 0xa3, 0xce, 0x0, 0xc0, 0x4f, 0xb1, 0x78, 0x2a)
DEFINE_GUID(IID_IEffectivePermission, 0x3853dc76, 0x9f35, 0x407c, 0x88, 0xa1, 0xd1, 0x93, 0x44, 0x36, 0x5f, 0xbc)
DEFINE_GUID(IID_ISecurityObjectTypeInfo, 0xfc3066eb, 0x79ef, 0x444b, 0x91, 0x11, 0xd1, 0x8a, 0x75, 0xeb, 0xf2, 0xfa)
if (NTDDI_VERSION GE NTDDI_VISTA)
DEFINE_GUID(IID_ISecurityInformation3, 0xe2cdc9cc, 0x31bd, 0x4f8f, 0x8c, 0x8b, 0xb6, 0x41, 0xaf, 0x51, 0x6a, 0x1a)
endif

;ACLUIAPI
CreateSecurityPage proto WINAPI psi:LPSECURITYINFO
;BOOL
EditSecurity proto WINAPI hwndOwner:HWND, psi:LPSECURITYINFO

if (NTDDI_VERSION GE NTDDI_VISTA)
;HRESULT
EditSecurityAdvanced proto WINAPI hwndOwner:HWND, psi:LPSECURITYINFO, uSIPage:SI_PAGE_TYPE

endif

.pragma list(pop)
endif

