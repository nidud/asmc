ifndef __ACCESS_CONTROL_API__
define __ACCESS_CONTROL_API__

include winapifamily.inc

include windows.inc
include accctrl.inc

.pragma comment(lib, advapi32)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM)

CALLBACK(FN_PROGRESS, :LPWSTR, :DWORD, :ptr, :ptr, :BOOL)

SetEntriesInAclA proto WINAPI :ULONG, :PEXPLICIT_ACCESS_A, :PACL, :ptr
SetEntriesInAclW proto WINAPI :ULONG, :PEXPLICIT_ACCESS_W, :PACL, :ptr
ifdef _UNICODE
define SetEntriesInAcl  <SetEntriesInAclW>
else
define SetEntriesInAcl  <SetEntriesInAclA>
endif

GetExplicitEntriesFromAclA proto WINAPI :PACL, :PULONG, :ptr
GetExplicitEntriesFromAclW proto WINAPI :PACL, :PULONG, :ptr
ifdef _UNICODE
define GetExplicitEntriesFromAcl  <GetExplicitEntriesFromAclW>
else
define GetExplicitEntriesFromAcl  <GetExplicitEntriesFromAclA>
endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

GetEffectiveRightsFromAclA proto WINAPI :PACL, :PTRUSTEE_A, :PACCESS_MASK
GetEffectiveRightsFromAclW proto WINAPI :PACL, :PTRUSTEE_W, :PACCESS_MASK
ifdef _UNICODE
define GetEffectiveRightsFromAcl  <GetEffectiveRightsFromAclW>
else
define GetEffectiveRightsFromAcl  <GetEffectiveRightsFromAclA>
endif

GetAuditedPermissionsFromAclA proto WINAPI :PACL, :PTRUSTEE_A, :PACCESS_MASK, :PACCESS_MASK
GetAuditedPermissionsFromAclW proto WINAPI :PACL, :PTRUSTEE_W, :PACCESS_MASK, :PACCESS_MASK
ifdef _UNICODE
define GetAuditedPermissionsFromAcl  <GetAuditedPermissionsFromAclW>
else
define GetAuditedPermissionsFromAcl  <GetAuditedPermissionsFromAclA>
endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM)

GetNamedSecurityInfoA proto WINAPI :LPCSTR, :SE_OBJECT_TYPE, :SECURITY_INFORMATION, :ptr, :ptr, :ptr, :ptr, :ptr
GetNamedSecurityInfoW proto WINAPI :LPCWSTR, :SE_OBJECT_TYPE, :SECURITY_INFORMATION, :ptr, :ptr, :ptr, :ptr, :ptr
ifdef _UNICODE
define GetNamedSecurityInfo  <GetNamedSecurityInfoW>
else
define GetNamedSecurityInfo  <GetNamedSecurityInfoA>
endif

GetSecurityInfo proto WINAPI :HANDLE, :SE_OBJECT_TYPE, :SECURITY_INFORMATION, :ptr, :ptr, :ptr, :ptr, :ptr

SetNamedSecurityInfoA proto WINAPI :LPSTR, :SE_OBJECT_TYPE, :SECURITY_INFORMATION, :PSID, :PSID, :PACL, :PACL
SetNamedSecurityInfoW proto WINAPI :LPWSTR, :SE_OBJECT_TYPE, :SECURITY_INFORMATION, :PSID, :PSID, :PACL, :PACL
ifdef _UNICODE
define SetNamedSecurityInfo  <SetNamedSecurityInfoW>
else
define SetNamedSecurityInfo  <SetNamedSecurityInfoA>
endif

SetSecurityInfo proto WINAPI :HANDLE, :SE_OBJECT_TYPE, :SECURITY_INFORMATION, :PSID, :PSID, :PACL, :PACL

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

GetInheritanceSourceA proto WINAPI :LPSTR, :SE_OBJECT_TYPE, :SECURITY_INFORMATION, :BOOL, :ptr ptr, :DWORD, :PACL, :PFN_OBJECT_MGR_FUNCTS, :PGENERIC_MAPPING, :PINHERITED_FROMA
GetInheritanceSourceW proto WINAPI :LPWSTR, :SE_OBJECT_TYPE, :SECURITY_INFORMATION, :BOOL, :ptr ptr, :DWORD, :PACL, :PFN_OBJECT_MGR_FUNCTS, :PGENERIC_MAPPING, :PINHERITED_FROMW
ifdef _UNICODE
define GetInheritanceSource  <GetInheritanceSourceW>
else
define GetInheritanceSource  <GetInheritanceSourceA>
endif

FreeInheritedFromArray proto WINAPI :PINHERITED_FROMW, :USHORT, :PFN_OBJECT_MGR_FUNCTS

TreeResetNamedSecurityInfoA proto WINAPI :LPSTR, :SE_OBJECT_TYPE, :SECURITY_INFORMATION, :PSID, :PSID, :PACL, :PACL, :BOOL, :FN_PROGRESS, :PROG_INVOKE_SETTING, :PVOID
TreeResetNamedSecurityInfoW proto WINAPI :LPWSTR, :SE_OBJECT_TYPE, :SECURITY_INFORMATION, :PSID, :PSID, :PACL, :PACL, :BOOL, :FN_PROGRESS, :PROG_INVOKE_SETTING, :PVOID
ifdef _UNICODE
define TreeResetNamedSecurityInfo  <TreeResetNamedSecurityInfoW>
else
define TreeResetNamedSecurityInfo  <TreeResetNamedSecurityInfoA>
endif

if (NTDDI_VERSION ge NTDDI_VISTA)
TreeSetNamedSecurityInfoA proto WINAPI :LPSTR, :SE_OBJECT_TYPE, :SECURITY_INFORMATION, :PSID, :PSID, :PACL, :PACL, :DWORD, :FN_PROGRESS, :PROG_INVOKE_SETTING, :PVOID
TreeSetNamedSecurityInfoW proto WINAPI :LPWSTR, :SE_OBJECT_TYPE, :SECURITY_INFORMATION, :PSID, :PSID, :PACL, :PACL, :DWORD, :FN_PROGRESS, :PROG_INVOKE_SETTING, :PVOID
ifdef _UNICODE
define TreeSetNamedSecurityInfo  <TreeSetNamedSecurityInfoW>
else
define TreeSetNamedSecurityInfo  <TreeSetNamedSecurityInfoA>
endif

endif

BuildSecurityDescriptorA proto WINAPI :PTRUSTEE_A, :PTRUSTEE_A, :ULONG, :PEXPLICIT_ACCESS_A, :ULONG, :PEXPLICIT_ACCESS_A, :PSECURITY_DESCRIPTOR, :PULONG, :ptr
BuildSecurityDescriptorW proto WINAPI :PTRUSTEE_W, :PTRUSTEE_W, :ULONG, :PEXPLICIT_ACCESS_W, :ULONG, :PEXPLICIT_ACCESS_W, :PSECURITY_DESCRIPTOR, :PULONG, :ptr
ifdef _UNICODE
define BuildSecurityDescriptor  <BuildSecurityDescriptorW>
else
define BuildSecurityDescriptor  <BuildSecurityDescriptorA>
endif

LookupSecurityDescriptorPartsA proto WINAPI :ptr, :ptr, :PULONG, :ptr, :PULONG, :ptr, :PSECURITY_DESCRIPTOR
LookupSecurityDescriptorPartsW proto WINAPI :ptr, :ptr, :PULONG, :ptr, :PULONG, :ptr, :PSECURITY_DESCRIPTOR
ifdef _UNICODE
define LookupSecurityDescriptorParts  <LookupSecurityDescriptorPartsW>
else
define LookupSecurityDescriptorParts  <LookupSecurityDescriptorPartsA>
endif

BuildExplicitAccessWithNameA proto WINAPI :PEXPLICIT_ACCESS_A, :LPSTR, :DWORD, :ACCESS_MODE, :DWORD
BuildExplicitAccessWithNameW proto WINAPI :PEXPLICIT_ACCESS_W, :LPWSTR, :DWORD, :ACCESS_MODE, :DWORD
ifdef _UNICODE
define BuildExplicitAccessWithName  <BuildExplicitAccessWithNameW>
else
define BuildExplicitAccessWithName  <BuildExplicitAccessWithNameA>
endif

BuildImpersonateExplicitAccessWithNameA proto WINAPI :PEXPLICIT_ACCESS_A, :LPSTR, :PTRUSTEE_A, :DWORD, :ACCESS_MODE, :DWORD
BuildImpersonateExplicitAccessWithNameW proto WINAPI :PEXPLICIT_ACCESS_W, :LPWSTR, :PTRUSTEE_W, :DWORD, :ACCESS_MODE, :DWORD
ifdef _UNICODE
define BuildImpersonateExplicitAccessWithName  <BuildImpersonateExplicitAccessWithNameW>
else
define BuildImpersonateExplicitAccessWithName  <BuildImpersonateExplicitAccessWithNameA>
endif

BuildTrusteeWithNameA proto WINAPI :PTRUSTEE_A, :LPSTR
BuildTrusteeWithNameW proto WINAPI :PTRUSTEE_W, :LPWSTR
ifdef _UNICODE
define BuildTrusteeWithName  <BuildTrusteeWithNameW>
else
define BuildTrusteeWithName  <BuildTrusteeWithNameA>
endif

BuildImpersonateTrusteeA proto WINAPI :PTRUSTEE_A, :PTRUSTEE_A
BuildImpersonateTrusteeW proto WINAPI :PTRUSTEE_W, :PTRUSTEE_W
ifdef _UNICODE
define BuildImpersonateTrustee  <BuildImpersonateTrusteeW>
else
define BuildImpersonateTrustee  <BuildImpersonateTrusteeA>
endif

BuildTrusteeWithSidA proto WINAPI :PTRUSTEE_A, :PSID
BuildTrusteeWithSidW proto WINAPI :PTRUSTEE_W, :PSID
ifdef _UNICODE
define BuildTrusteeWithSid  <BuildTrusteeWithSidW>
else
define BuildTrusteeWithSid  <BuildTrusteeWithSidA>
endif

BuildTrusteeWithObjectsAndSidA proto WINAPI :PTRUSTEE_A, :POBJECTS_AND_SID, :ptr, :ptr, :PSID
BuildTrusteeWithObjectsAndSidW proto WINAPI :PTRUSTEE_W, :POBJECTS_AND_SID, :ptr, :ptr, :PSID
ifdef _UNICODE
define BuildTrusteeWithObjectsAndSid  <BuildTrusteeWithObjectsAndSidW>
else
define BuildTrusteeWithObjectsAndSid  <BuildTrusteeWithObjectsAndSidA>
endif

BuildTrusteeWithObjectsAndNameA proto WINAPI :PTRUSTEE_A, :POBJECTS_AND_NAME_A, :SE_OBJECT_TYPE, :LPSTR, :LPSTR, :LPSTR
BuildTrusteeWithObjectsAndNameW proto WINAPI :PTRUSTEE_W, :POBJECTS_AND_NAME_W, :SE_OBJECT_TYPE, :LPWSTR, :LPWSTR, :LPWSTR
ifdef _UNICODE
define BuildTrusteeWithObjectsAndName  <BuildTrusteeWithObjectsAndNameW>
else
define BuildTrusteeWithObjectsAndName  <BuildTrusteeWithObjectsAndNameA>
endif

GetTrusteeNameA proto WINAPI :PTRUSTEE_A
GetTrusteeNameW proto WINAPI :PTRUSTEE_W
ifdef _UNICODE
define GetTrusteeName  <GetTrusteeNameW>
else
define GetTrusteeName  <GetTrusteeNameA>
endif

GetTrusteeTypeA proto WINAPI :PTRUSTEE_A
GetTrusteeTypeW proto WINAPI :PTRUSTEE_W
ifdef _UNICODE
define GetTrusteeType  <GetTrusteeTypeW>
else
define GetTrusteeType  <GetTrusteeTypeA>
endif

GetTrusteeFormA proto WINAPI :PTRUSTEE_A
GetTrusteeFormW proto WINAPI :PTRUSTEE_W
ifdef _UNICODE
define GetTrusteeForm  <GetTrusteeFormW>
else
define GetTrusteeForm  <GetTrusteeFormA>
endif

GetMultipleTrusteeOperationA proto WINAPI :PTRUSTEE_A
GetMultipleTrusteeOperationW proto WINAPI :PTRUSTEE_W
ifdef _UNICODE
define GetMultipleTrusteeOperation  <GetMultipleTrusteeOperationW>
else
define GetMultipleTrusteeOperation  <GetMultipleTrusteeOperationA>
endif

GetMultipleTrusteeA proto WINAPI :PTRUSTEE_A
GetMultipleTrusteeW proto WINAPI :PTRUSTEE_W
ifdef _UNICODE
define GetMultipleTrustee  <GetMultipleTrusteeW>
else
define GetMultipleTrustee  <GetMultipleTrusteeA>
endif

endif

endif

