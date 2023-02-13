ifndef _APISECUREBASE_
define _APISECUREBASE_

include apiset.inc
include apisetcconv.inc
include minwindef.inc
include minwinbase.inc

AccessCheck proto WINAPI :PSECURITY_DESCRIPTOR, :HANDLE, :DWORD, :PGENERIC_MAPPING, :PPRIVILEGE_SET, :LPDWORD, :LPDWORD, :LPBOOL
AccessCheckAndAuditAlarmW proto WINAPI :LPCWSTR, :LPVOID, :LPWSTR, :LPWSTR, :PSECURITY_DESCRIPTOR, :DWORD, :PGENERIC_MAPPING, :BOOL, :LPDWORD, :LPBOOL, :LPBOOL
ifdef _UNICODE
define AccessCheckAndAuditAlarm  <AccessCheckAndAuditAlarmW>
endif

AccessCheckByType proto WINAPI :PSECURITY_DESCRIPTOR, :PSID, :HANDLE, :DWORD, :POBJECT_TYPE_LIST, :DWORD, :PGENERIC_MAPPING, :PPRIVILEGE_SET, :LPDWORD, :LPDWORD, :LPBOOL
AccessCheckByTypeResultList proto WINAPI :PSECURITY_DESCRIPTOR, :PSID, :HANDLE, :DWORD, :POBJECT_TYPE_LIST, :DWORD, :PGENERIC_MAPPING, :PPRIVILEGE_SET, :LPDWORD, :LPDWORD, :LPDWORD
AccessCheckByTypeAndAuditAlarmW proto WINAPI :LPCWSTR, :LPVOID, :LPCWSTR, :LPCWSTR, :PSECURITY_DESCRIPTOR, :PSID, :DWORD, :AUDIT_EVENT_TYPE, :DWORD, :POBJECT_TYPE_LIST, :DWORD, :PGENERIC_MAPPING, :BOOL, :LPDWORD, :LPBOOL, :LPBOOL
ifdef _UNICODE
define AccessCheckByTypeAndAuditAlarm  <AccessCheckByTypeAndAuditAlarmW>
endif

AccessCheckByTypeResultListAndAuditAlarmW proto WINAPI :LPCWSTR, :LPVOID, :LPCWSTR, :LPCWSTR, :PSECURITY_DESCRIPTOR, :PSID, :DWORD, :AUDIT_EVENT_TYPE, :DWORD, :POBJECT_TYPE_LIST, :DWORD, :PGENERIC_MAPPING, :BOOL, :LPDWORD, :LPDWORD, :LPBOOL
ifdef _UNICODE
define AccessCheckByTypeResultListAndAuditAlarm  <AccessCheckByTypeResultListAndAuditAlarmW>
endif

AccessCheckByTypeResultListAndAuditAlarmByHandleW proto WINAPI :LPCWSTR, :LPVOID, :HANDLE, :LPCWSTR, :LPCWSTR, :PSECURITY_DESCRIPTOR, :PSID, :DWORD, :AUDIT_EVENT_TYPE, :DWORD, :POBJECT_TYPE_LIST, :DWORD, :PGENERIC_MAPPING, :BOOL, :LPDWORD, :LPDWORD, :LPBOOL
ifdef _UNICODE
define AccessCheckByTypeResultListAndAuditAlarmByHandle  <AccessCheckByTypeResultListAndAuditAlarmByHandleW>
endif

AddAccessAllowedAce proto WINAPI :PACL, :DWORD, :DWORD, :PSID
AddAccessAllowedAceEx proto WINAPI :PACL, :DWORD, :DWORD, :DWORD, :PSID

AddAccessAllowedObjectAce proto WINAPI :PACL, :DWORD, :DWORD, :DWORD, :ptr, :ptr, :PSID
AddAccessDeniedAce proto WINAPI :PACL, :DWORD, :DWORD, :PSID
AddAccessDeniedAceEx proto WINAPI :PACL, :DWORD, :DWORD, :DWORD, :PSID
AddAccessDeniedObjectAce proto WINAPI :PACL, :DWORD, :DWORD, :DWORD, :ptr, :ptr, :PSID

AddAce proto WINAPI :PACL, :DWORD, :DWORD, :LPVOID, :DWORD

AddAuditAccessAce proto WINAPI :PACL, :DWORD, :DWORD, :PSID, :BOOL, :BOOL
AddAuditAccessAceEx proto WINAPI :PACL, :DWORD, :DWORD, :DWORD, :PSID, :BOOL, :BOOL
AddAuditAccessObjectAce proto WINAPI :PACL, :DWORD, :DWORD, :DWORD, :ptr, :ptr, :PSID, :BOOL, :BOOL

if (_WIN32_WINNT ge 0x0600)
AddMandatoryAce proto WINAPI :PACL, :DWORD, :DWORD, :DWORD, :PSID
endif

if (_WIN32_WINNT ge _WIN32_WINNT_WIN8)
AddResourceAttributeAce proto WINAPI :PACL, :DWORD, :DWORD, :DWORD, :PSID, :PCLAIM_SECURITY_ATTRIBUTES_INFORMATION, :PDWORD
AddScopedPolicyIDAce proto WINAPI :PACL, :DWORD, :DWORD, :DWORD, :PSID
endif

AdjustTokenGroups proto WINAPI :HANDLE, :BOOL, :PTOKEN_GROUPS, :DWORD, :PTOKEN_GROUPS, :PDWORD

AdjustTokenPrivileges proto WINAPI :HANDLE, :BOOL, :PTOKEN_PRIVILEGES, :DWORD, :PTOKEN_PRIVILEGES, :PDWORD

AllocateAndInitializeSid proto WINAPI :PSID_IDENTIFIER_AUTHORITY, :BYTE, :DWORD, :DWORD, :DWORD, :DWORD, :DWORD, :DWORD, :DWORD, :DWORD, :ptr
AllocateLocallyUniqueId proto WINAPI :PLUID

AreAllAccessesGranted proto WINAPI :DWORD, :DWORD
AreAnyAccessesGranted proto WINAPI :DWORD, :DWORD

CheckTokenMembership proto WINAPI :HANDLE, :PSID, :PBOOL

if (_WIN32_WINNT ge _WIN32_WINNT_WIN8)

CheckTokenCapability proto WINAPI :HANDLE, :PSID, :PBOOL
GetAppContainerAce proto WINAPI :PACL, :DWORD, :ptr, :ptr

CheckTokenMembershipEx proto WINAPI :HANDLE, :PSID, :DWORD, :PBOOL

endif

ConvertToAutoInheritPrivateObjectSecurity proto WINAPI :PSECURITY_DESCRIPTOR, :PSECURITY_DESCRIPTOR, :ptr, :ptr, :BOOLEAN, :PGENERIC_MAPPING

CopySid proto WINAPI :DWORD, :PSID, :PSID

CreatePrivateObjectSecurity proto WINAPI :PSECURITY_DESCRIPTOR, :PSECURITY_DESCRIPTOR, :ptr, :BOOL, :HANDLE, :PGENERIC_MAPPING
CreatePrivateObjectSecurityEx proto WINAPI :PSECURITY_DESCRIPTOR, :PSECURITY_DESCRIPTOR, :ptr, :ptr, :BOOL, :ULONG, :HANDLE, :PGENERIC_MAPPING
CreatePrivateObjectSecurityWithMultipleInheritance proto WINAPI :PSECURITY_DESCRIPTOR, :PSECURITY_DESCRIPTOR, :ptr, :ptr ptr, :ULONG, :BOOL, :ULONG, :HANDLE, :PGENERIC_MAPPING
CreateRestrictedToken proto WINAPI :HANDLE, :DWORD, :DWORD, :PSID_AND_ATTRIBUTES, :DWORD, :PLUID_AND_ATTRIBUTES, :DWORD, :PSID_AND_ATTRIBUTES, :PHANDLE

if (_WIN32_WINNT ge 0x0501)
CreateWellKnownSid proto WINAPI :WELL_KNOWN_SID_TYPE, :PSID, :PSID, :ptr
EqualDomainSid proto WINAPI :PSID, :PSID, :ptr
endif

DeleteAce proto WINAPI :PACL, :DWORD

DestroyPrivateObjectSecurity proto WINAPI :ptr

DuplicateToken proto WINAPI :HANDLE, :SECURITY_IMPERSONATION_LEVEL, :PHANDLE
DuplicateTokenEx proto WINAPI :HANDLE, :DWORD, :LPSECURITY_ATTRIBUTES, :SECURITY_IMPERSONATION_LEVEL, :TOKEN_TYPE, :PHANDLE

EqualPrefixSid proto WINAPI :PSID, :PSID
EqualSid proto WINAPI :PSID, :PSID
FindFirstFreeAce proto WINAPI :PACL, :ptr

FreeSid proto WINAPI :PSID
GetAce proto WINAPI :PACL, :DWORD, :ptr
GetAclInformation proto WINAPI :PACL, :LPVOID, :DWORD, :ACL_INFORMATION_CLASS

GetFileSecurityW proto WINAPI :LPCWSTR, :SECURITY_INFORMATION, :PSECURITY_DESCRIPTOR, :DWORD, :LPDWORD
ifdef _UNICODE
define GetFileSecurity  <GetFileSecurityW>
endif

GetKernelObjectSecurity proto WINAPI :HANDLE, :SECURITY_INFORMATION, :PSECURITY_DESCRIPTOR, :DWORD, :LPDWORD
GetLengthSid proto WINAPI :PSID

GetPrivateObjectSecurity proto WINAPI :PSECURITY_DESCRIPTOR, :SECURITY_INFORMATION, :PSECURITY_DESCRIPTOR, :DWORD, :PDWORD

GetSecurityDescriptorControl proto WINAPI :PSECURITY_DESCRIPTOR, :PSECURITY_DESCRIPTOR_CONTROL, :LPDWORD
GetSecurityDescriptorDacl proto WINAPI :PSECURITY_DESCRIPTOR, :LPBOOL, :ptr, :LPBOOL
GetSecurityDescriptorGroup proto WINAPI :PSECURITY_DESCRIPTOR, :ptr, :LPBOOL
GetSecurityDescriptorLength proto WINAPI :PSECURITY_DESCRIPTOR
GetSecurityDescriptorOwner proto WINAPI :PSECURITY_DESCRIPTOR, :ptr, :LPBOOL
GetSecurityDescriptorRMControl proto WINAPI :PSECURITY_DESCRIPTOR, :PUCHAR
GetSecurityDescriptorSacl proto WINAPI :PSECURITY_DESCRIPTOR, :LPBOOL, :ptr, :LPBOOL
GetSidIdentifierAuthority proto WINAPI :PSID
GetSidLengthRequired proto WINAPI :UCHAR
GetSidSubAuthority proto WINAPI :PSID, :DWORD
GetSidSubAuthorityCount proto WINAPI :PSID
GetTokenInformation proto WINAPI :HANDLE, :TOKEN_INFORMATION_CLASS, :LPVOID, :DWORD, :PDWORD

if (_WIN32_WINNT ge 0x0501)
GetWindowsAccountDomainSid proto WINAPI :PSID, :PSID, :ptr
endif

ImpersonateAnonymousToken proto WINAPI :HANDLE
ImpersonateLoggedOnUser proto WINAPI :HANDLE
ImpersonateSelf proto WINAPI :SECURITY_IMPERSONATION_LEVEL

InitializeAcl proto WINAPI :PACL, :DWORD, :DWORD
InitializeSecurityDescriptor proto WINAPI :PSECURITY_DESCRIPTOR, :DWORD
InitializeSid proto WINAPI :PSID, :PSID_IDENTIFIER_AUTHORITY, :BYTE

IsTokenRestricted proto WINAPI :HANDLE

IsValidAcl proto WINAPI :PACL
IsValidSecurityDescriptor proto WINAPI :PSECURITY_DESCRIPTOR
IsValidSid proto WINAPI :PSID

if (_WIN32_WINNT ge 0x0501)
IsWellKnownSid proto WINAPI :PSID, :WELL_KNOWN_SID_TYPE
endif

MakeAbsoluteSD proto WINAPI :PSECURITY_DESCRIPTOR, :PSECURITY_DESCRIPTOR, :LPDWORD, :PACL, :LPDWORD, :PACL, :LPDWORD, :PSID, :LPDWORD, :PSID, :LPDWORD
MakeSelfRelativeSD proto WINAPI :PSECURITY_DESCRIPTOR, :PSECURITY_DESCRIPTOR, :LPDWORD

MapGenericMask proto WINAPI :PDWORD, :PGENERIC_MAPPING
ObjectCloseAuditAlarmW proto WINAPI :LPCWSTR, :LPVOID, :BOOL
ifdef _UNICODE
define ObjectCloseAuditAlarm  <ObjectCloseAuditAlarmW>
endif

ObjectDeleteAuditAlarmW proto WINAPI :LPCWSTR, :LPVOID, :BOOL
ifdef _UNICODE
define ObjectDeleteAuditAlarm  <ObjectDeleteAuditAlarmW>
endif

ObjectOpenAuditAlarmW proto WINAPI :LPCWSTR, :LPVOID, :LPWSTR, :LPWSTR, :PSECURITY_DESCRIPTOR, :HANDLE, :DWORD, :DWORD, :PPRIVILEGE_SET, :BOOL, :BOOL, :LPBOOL
ifdef _UNICODE
define ObjectOpenAuditAlarm  <ObjectOpenAuditAlarmW>
endif

ObjectPrivilegeAuditAlarmW proto WINAPI :LPCWSTR, :LPVOID, :HANDLE, :DWORD, :PPRIVILEGE_SET, :BOOL
ifdef _UNICODE
define ObjectPrivilegeAuditAlarm  <ObjectPrivilegeAuditAlarmW>
endif

PrivilegeCheck proto WINAPI :HANDLE, :PPRIVILEGE_SET, :LPBOOL
PrivilegedServiceAuditAlarmW proto WINAPI :LPCWSTR, :LPCWSTR, :HANDLE, :PPRIVILEGE_SET, :BOOL
ifdef _UNICODE
define PrivilegedServiceAuditAlarm  <PrivilegedServiceAuditAlarmW>
endif

if (_WIN32_WINNT ge 0x0600)
QuerySecurityAccessMask proto WINAPI :SECURITY_INFORMATION, :LPDWORD
endif

RevertToSelf proto WINAPI
SetAclInformation proto WINAPI :PACL, :LPVOID, :DWORD, :ACL_INFORMATION_CLASS
SetFileSecurityW proto WINAPI :LPCWSTR, :SECURITY_INFORMATION, :PSECURITY_DESCRIPTOR
ifdef _UNICODE
define SetFileSecurity  <SetFileSecurityW>
endif

SetKernelObjectSecurity proto WINAPI :HANDLE, :SECURITY_INFORMATION, :PSECURITY_DESCRIPTOR

SetPrivateObjectSecurity proto WINAPI :SECURITY_INFORMATION, :PSECURITY_DESCRIPTOR, :ptr, :PGENERIC_MAPPING, :HANDLE
SetPrivateObjectSecurityEx proto WINAPI :SECURITY_INFORMATION, :PSECURITY_DESCRIPTOR, :ptr, :ULONG, :PGENERIC_MAPPING, :HANDLE

if (_WIN32_WINNT ge 0x0600)
SetSecurityAccessMask proto WINAPI :SECURITY_INFORMATION, :LPDWORD
endif

SetSecurityDescriptorControl proto WINAPI :PSECURITY_DESCRIPTOR, :SECURITY_DESCRIPTOR_CONTROL, :SECURITY_DESCRIPTOR_CONTROL
SetSecurityDescriptorDacl proto WINAPI :PSECURITY_DESCRIPTOR, :BOOL, :PACL, :BOOL
SetSecurityDescriptorGroup proto WINAPI :PSECURITY_DESCRIPTOR, :PSID, :BOOL
SetSecurityDescriptorOwner proto WINAPI :PSECURITY_DESCRIPTOR, :PSID, :BOOL
SetSecurityDescriptorRMControl proto WINAPI :PSECURITY_DESCRIPTOR, :PUCHAR
SetSecurityDescriptorSacl proto WINAPI :PSECURITY_DESCRIPTOR, :BOOL, :PACL, :BOOL
SetTokenInformation proto WINAPI :HANDLE, :TOKEN_INFORMATION_CLASS, :LPVOID, :DWORD

if (_WIN32_WINNT ge _WIN32_WINNT_WIN8)
SetCachedSigningLevel proto WINAPI :PHANDLE, :ULONG, :ULONG, :HANDLE
GetCachedSigningLevel proto WINAPI :HANDLE, :PULONG, :PULONG, :PUCHAR, :PULONG, :PULONG
endif
if (_WIN32_WINNT ge _WIN32_WINNT_WIN10)
CveEventWrite proto WINAPI :PCWSTR, :PCWSTR
endif
if (_WIN32_WINNT ge _WIN32_WINNT_WIN10)
DeriveCapabilitySidsFromName proto WINAPI :LPCWSTR, :ptr ptr, :ptr, :ptr ptr, :ptr
endif

endif
