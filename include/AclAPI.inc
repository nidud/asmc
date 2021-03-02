ifndef __ACCESS_CONTROL_API__
__ACCESS_CONTROL_API__ equ <>
include windows.inc
include accctrl.inc
.pragma list(push, 0)
.pragma comment(lib, advapi32)

;VOID
CALLBACK(FN_PROGRESS, :LPWSTR, :DWORD, :PPROG_INVOKE_SETTING, :PVOID, :BOOL)

;DWORD
SetEntriesInAclA proto WINAPI \
cCountOfExplicitEntries: ULONG,
pListOfExplicitEntries: PEXPLICIT_ACCESS_A,
                OldAcl: PACL,
                NewAcl: ptr PACL
SetEntriesInAclW proto WINAPI \
cCountOfExplicitEntries: ULONG,
pListOfExplicitEntries: PEXPLICIT_ACCESS_W,
                OldAcl: PACL,
                NewAcl: ptr PACL
ifdef _UNICODE
SetEntriesInAcl         equ <SetEntriesInAclW>
else
SetEntriesInAcl         equ <SetEntriesInAclA>
endif

;DWORD
GetExplicitEntriesFromAclA proto WINAPI \
                  pacl: PACL,
pcCountOfExplicitEntries: PULONG,
pListOfExplicitEntries: ptr PEXPLICIT_ACCESS_A
GetExplicitEntriesFromAclW proto WINAPI \
                  pacl: PACL,
pcCountOfExplicitEntries: PULONG,
pListOfExplicitEntries: ptr PEXPLICIT_ACCESS_W
ifdef _UNICODE
GetExplicitEntriesFromAcl equ <GetExplicitEntriesFromAclW>
else
GetExplicitEntriesFromAcl equ <GetExplicitEntriesFromAclA>
endif

;DWORD
GetEffectiveRightsFromAclA proto WINAPI \
                  pacl: PACL,
              pTrustee: PTRUSTEE_A,
         pAccessRights: PACCESS_MASK
GetEffectiveRightsFromAclW proto WINAPI \
                  pacl: PACL,
              pTrustee: PTRUSTEE_W,
         pAccessRights: PACCESS_MASK
ifdef _UNICODE
GetEffectiveRightsFromAcl equ <GetEffectiveRightsFromAclW>
else
GetEffectiveRightsFromAcl equ <GetEffectiveRightsFromAclA>
endif

;DWORD
GetAuditedPermissionsFromAclA proto WINAPI \
                  pacl: PACL,
              pTrustee: PTRUSTEE_A,
pSuccessfulAuditedRights: PACCESS_MASK,
    pFailedAuditRights: PACCESS_MASK
GetAuditedPermissionsFromAclW proto WINAPI \
                  pacl: PACL,
              pTrustee: PTRUSTEE_W,
pSuccessfulAuditedRights: PACCESS_MASK,
    pFailedAuditRights: PACCESS_MASK
ifdef _UNICODE
GetAuditedPermissionsFromAcl equ <GetAuditedPermissionsFromAclW>
else
GetAuditedPermissionsFromAcl equ <GetAuditedPermissionsFromAclA>
endif

;DWORD
GetNamedSecurityInfoA proto WINAPI \
           pObjectName: LPCSTR,
            ObjectType: SE_OBJECT_TYPE,
          SecurityInfo: SECURITY_INFORMATION,
            ppsidOwner: ptr PSID,
            ppsidGroup: ptr PSID,
                ppDacl: ptr PACL,
                ppSacl: ptr PACL,
  ppSecurityDescriptor: ptr PSECURITY_DESCRIPTOR
GetNamedSecurityInfoW proto WINAPI \
           pObjectName: LPCWSTR,
            ObjectType: SE_OBJECT_TYPE,
          SecurityInfo: SECURITY_INFORMATION,
            ppsidOwner: ptr PSID,
            ppsidGroup: ptr PSID,
                ppDacl: ptr PACL,
                ppSacl: ptr PACL,
  ppSecurityDescriptor: ptr PSECURITY_DESCRIPTOR
ifdef _UNICODE
GetNamedSecurityInfo    equ <GetNamedSecurityInfoW>
else
GetNamedSecurityInfo    equ <GetNamedSecurityInfoA>
endif

;DWORD
GetSecurityInfo proto WINAPI \
                handle: HANDLE,
            ObjectType: SE_OBJECT_TYPE,
          SecurityInfo: SECURITY_INFORMATION,
            ppsidOwner: ptr PSID,
            ppsidGroup: ptr PSID,
                ppDacl: ptr PACL,
                ppSacl: ptr PACL,
  ppSecurityDescriptor: ptr PSECURITY_DESCRIPTOR


;DWORD
SetNamedSecurityInfoA proto WINAPI \
           pObjectName: LPSTR,
            ObjectType: SE_OBJECT_TYPE,
          SecurityInfo: SECURITY_INFORMATION,
             psidOwner: PSID,
             psidGroup: PSID,
                 pDacl: PACL,
                 pSacl: PACL
SetNamedSecurityInfoW proto WINAPI \
           pObjectName: LPWSTR,
            ObjectType: SE_OBJECT_TYPE,
          SecurityInfo: SECURITY_INFORMATION,
             psidOwner: PSID,
             psidGroup: PSID,
                 pDacl: PACL,
                 pSacl: PACL
ifdef _UNICODE
SetNamedSecurityInfo    equ <SetNamedSecurityInfoW>
else
SetNamedSecurityInfo    equ <SetNamedSecurityInfoA>
endif

;DWORD
SetSecurityInfo proto WINAPI \
                handle: HANDLE,
            ObjectType: SE_OBJECT_TYPE,
          SecurityInfo: SECURITY_INFORMATION,
             psidOwner: PSID,
             psidGroup: PSID,
                 pDacl: PACL,
                 pSacl: PACL


;DWORD
GetInheritanceSourceA proto WINAPI \
           pObjectName: LPSTR,
            ObjectType: SE_OBJECT_TYPE,
          SecurityInfo: SECURITY_INFORMATION,
             Container: BOOL,
     pObjectClassGuids: ptr GUID,
             GuidCount: DWORD,
                  pAcl: PACL,
              pfnArray: PFN_OBJECT_MGR_FUNCTS,
       pGenericMapping: PGENERIC_MAPPING,
         pInheritArray: PINHERITED_FROMA
GetInheritanceSourceW proto WINAPI \
           pObjectName: LPWSTR,
            ObjectType: SE_OBJECT_TYPE,
          SecurityInfo: SECURITY_INFORMATION,
             Container: BOOL,
     pObjectClassGuids: ptr GUID,
             GuidCount: DWORD,
                  pAcl: PACL,
              pfnArray: PFN_OBJECT_MGR_FUNCTS,
       pGenericMapping: PGENERIC_MAPPING,
         pInheritArray: PINHERITED_FROMW
ifdef _UNICODE
GetInheritanceSource    equ <GetInheritanceSourceW>
else
GetInheritanceSource    equ <GetInheritanceSourceA>
endif

;DWORD
FreeInheritedFromArray proto WINAPI \
         pInheritArray: PINHERITED_FROMW,
                AceCnt: USHORT,
     pfnArray OPTIONAL: PFN_OBJECT_MGR_FUNCTS


;DWORD
TreeResetNamedSecurityInfoA proto WINAPI \
           pObjectName: LPSTR,
            ObjectType: SE_OBJECT_TYPE,
          SecurityInfo: SECURITY_INFORMATION,
                pOwner: PSID,
                pGroup: PSID,
                 pDacl: PACL,
                 pSacl: PACL,
          KeepExplicit: BOOL,
            fnProgress: FN_PROGRESS,
 ProgressInvokeSetting: PROG_INVOKE_SETTING,
                  Args: PVOID
TreeResetNamedSecurityInfoW proto WINAPI \
           pObjectName: LPWSTR,
            ObjectType: SE_OBJECT_TYPE,
          SecurityInfo: SECURITY_INFORMATION,
                pOwner: PSID,
                pGroup: PSID,
                 pDacl: PACL,
                 pSacl: PACL,
          KeepExplicit: BOOL,
            fnProgress: FN_PROGRESS,
 ProgressInvokeSetting: PROG_INVOKE_SETTING,
                  Args: PVOID
ifdef _UNICODE
TreeResetNamedSecurityInfo equ <TreeResetNamedSecurityInfoW>
else
TreeResetNamedSecurityInfo equ <TreeResetNamedSecurityInfoA>
endif

if (NTDDI_VERSION GE NTDDI_VISTA)
;DWORD
TreeSetNamedSecurityInfoA proto WINAPI \
           pObjectName: LPSTR,
            ObjectType: SE_OBJECT_TYPE,
          SecurityInfo: SECURITY_INFORMATION,
                pOwner: PSID,
                pGroup: PSID,
                 pDacl: PACL,
                 pSacl: PACL,
              dwAction: DWORD,
            fnProgress: FN_PROGRESS,
 ProgressInvokeSetting: PROG_INVOKE_SETTING,
                  Args: PVOID
TreeSetNamedSecurityInfoW proto WINAPI \
           pObjectName: LPWSTR,
            ObjectType: SE_OBJECT_TYPE,
          SecurityInfo: SECURITY_INFORMATION,
                pOwner: PSID,
                pGroup: PSID,
                 pDacl: PACL,
                 pSacl: PACL,
              dwAction: DWORD,
            fnProgress: FN_PROGRESS,
 ProgressInvokeSetting: PROG_INVOKE_SETTING,
                  Args: PVOID
ifdef _UNICODE
TreeSetNamedSecurityInfo equ <TreeSetNamedSecurityInfoW>
else
TreeSetNamedSecurityInfo equ <TreeSetNamedSecurityInfoA>
endif

endif ;; (NTDDI_VERSION GE NTDDI_VISTA)

;DWORD
BuildSecurityDescriptorA proto WINAPI \
                pOwner: PTRUSTEE_A,
                pGroup: PTRUSTEE_A,
 cCountOfAccessEntries: ULONG,
  pListOfAccessEntries: PEXPLICIT_ACCESS_A,
  cCountOfAuditEntries: ULONG,
   pListOfAuditEntries: PEXPLICIT_ACCESS_A,
                pOldSD: PSECURITY_DESCRIPTOR,
            pSizeNewSD: PULONG,
                pNewSD: PSECURITY_DESCRIPTOR
BuildSecurityDescriptorW proto WINAPI \
                pOwner: PTRUSTEE_W,
                pGroup: PTRUSTEE_W,
 cCountOfAccessEntries: ULONG,
  pListOfAccessEntries: PEXPLICIT_ACCESS_W,
  cCountOfAuditEntries: ULONG,
   pListOfAuditEntries: PEXPLICIT_ACCESS_W,
                pOldSD: PSECURITY_DESCRIPTOR,
            pSizeNewSD: PULONG,
                pNewSD: PSECURITY_DESCRIPTOR
ifdef _UNICODE
BuildSecurityDescriptor equ <BuildSecurityDescriptorW>
else
BuildSecurityDescriptor equ <BuildSecurityDescriptorA>
endif

;DWORD
LookupSecurityDescriptorPartsA proto WINAPI \
               ppOwner: ptr PTRUSTEE_A,
               ppGroup: ptr PTRUSTEE_A,
pcCountOfAccessEntries: PULONG,
 ppListOfAccessEntries: ptr PEXPLICIT_ACCESS_A,
 pcCountOfAuditEntries: PULONG,
  ppListOfAuditEntries: ptr PEXPLICIT_ACCESS_A,
                   pSD: PSECURITY_DESCRIPTOR
LookupSecurityDescriptorPartsW proto WINAPI \
               ppOwner: ptr PTRUSTEE_W,
               ppGroup: ptr PTRUSTEE_W,
pcCountOfAccessEntries: PULONG,
 ppListOfAccessEntries: ptr PEXPLICIT_ACCESS_W,
 pcCountOfAuditEntries: PULONG,
  ppListOfAuditEntries: ptr PEXPLICIT_ACCESS_W,
                   pSD: PSECURITY_DESCRIPTOR
ifdef _UNICODE
LookupSecurityDescriptorParts equ <LookupSecurityDescriptorPartsW>
else
LookupSecurityDescriptorParts equ <LookupSecurityDescriptorPartsA>
endif

;VOID
BuildExplicitAccessWithNameA proto WINAPI \
       pExplicitAccess: PEXPLICIT_ACCESS_A,
          pTrusteeName: LPSTR,
     AccessPermissions: DWORD,
            AccessMode: ACCESS_MODE,
           Inheritance: DWORD
BuildExplicitAccessWithNameW proto WINAPI \
       pExplicitAccess: PEXPLICIT_ACCESS_W,
          pTrusteeName: LPWSTR,
     AccessPermissions: DWORD,
            AccessMode: ACCESS_MODE,
           Inheritance: DWORD
ifdef _UNICODE
BuildExplicitAccessWithName equ <BuildExplicitAccessWithNameW>
else
BuildExplicitAccessWithName equ <BuildExplicitAccessWithNameA>
endif

;VOID
BuildImpersonateExplicitAccessWithNameA proto WINAPI \
       pExplicitAccess: PEXPLICIT_ACCESS_A,
          pTrusteeName: LPSTR,
              pTrustee: PTRUSTEE_A,
     AccessPermissions: DWORD,
            AccessMode: ACCESS_MODE,
           Inheritance: DWORD
BuildImpersonateExplicitAccessWithNameW proto WINAPI \
       pExplicitAccess: PEXPLICIT_ACCESS_W,
          pTrusteeName: LPWSTR,
              pTrustee: PTRUSTEE_W,
     AccessPermissions: DWORD,
            AccessMode: ACCESS_MODE,
           Inheritance: DWORD
ifdef _UNICODE
BuildImpersonateExplicitAccessWithName equ <BuildImpersonateExplicitAccessWithNameW>
else
BuildImpersonateExplicitAccessWithName equ <BuildImpersonateExplicitAccessWithNameA>
endif

;VOID
BuildTrusteeWithNameA proto WINAPI \
              pTrustee: PTRUSTEE_A,
                 pName: LPSTR
BuildTrusteeWithNameW proto WINAPI \
              pTrustee: PTRUSTEE_W,
                 pName: LPWSTR
ifdef _UNICODE
BuildTrusteeWithName    equ <BuildTrusteeWithNameW>
else
BuildTrusteeWithName    equ <BuildTrusteeWithNameA>
endif

;VOID
BuildImpersonateTrusteeA proto WINAPI \
              pTrustee: PTRUSTEE_A,
   pImpersonateTrustee: PTRUSTEE_A
BuildImpersonateTrusteeW proto WINAPI \
              pTrustee: PTRUSTEE_W,
   pImpersonateTrustee: PTRUSTEE_W
ifdef _UNICODE
BuildImpersonateTrustee equ <BuildImpersonateTrusteeW>
else
BuildImpersonateTrustee equ <BuildImpersonateTrusteeA>
endif

;VOID
BuildTrusteeWithSidA proto WINAPI \
              pTrustee: PTRUSTEE_A,
                  pSid: PSID
BuildTrusteeWithSidW proto WINAPI \
              pTrustee: PTRUSTEE_W,
                  pSid: PSID
ifdef _UNICODE
BuildTrusteeWithSid     equ <BuildTrusteeWithSidW>
else
BuildTrusteeWithSid     equ <BuildTrusteeWithSidA>
endif

;VOID
BuildTrusteeWithObjectsAndSidA proto WINAPI \
              pTrustee: PTRUSTEE_A,
               pObjSid: POBJECTS_AND_SID,
           pObjectGuid: ptr GUID,
  pInheritedObjectGuid: ptr GUID,
                  pSid: PSID
BuildTrusteeWithObjectsAndSidW proto WINAPI \
              pTrustee: PTRUSTEE_W,
               pObjSid: POBJECTS_AND_SID,
           pObjectGuid: ptr GUID,
  pInheritedObjectGuid: ptr GUID,
                  pSid: PSID
ifdef _UNICODE
BuildTrusteeWithObjectsAndSid equ <BuildTrusteeWithObjectsAndSidW>
else
BuildTrusteeWithObjectsAndSid equ <BuildTrusteeWithObjectsAndSidA>
endif

;VOID
BuildTrusteeWithObjectsAndNameA proto WINAPI \
              pTrustee: PTRUSTEE_A,
              pObjName: POBJECTS_AND_NAME_A,
            ObjectType: SE_OBJECT_TYPE,
        ObjectTypeName: LPSTR,
InheritedObjectTypeName: LPSTR,
                  Name: LPSTR
BuildTrusteeWithObjectsAndNameW proto WINAPI \
              pTrustee: PTRUSTEE_W,
              pObjName: POBJECTS_AND_NAME_W,
            ObjectType: SE_OBJECT_TYPE,
        ObjectTypeName: LPWSTR,
InheritedObjectTypeName: LPWSTR,
                  Name: LPWSTR
ifdef _UNICODE
BuildTrusteeWithObjectsAndName equ <BuildTrusteeWithObjectsAndNameW>
else
BuildTrusteeWithObjectsAndName equ <BuildTrusteeWithObjectsAndNameA>
endif

;LPSTR
GetTrusteeNameA proto WINAPI \
              pTrustee: PTRUSTEE_A
GetTrusteeNameW proto WINAPI \
              pTrustee: PTRUSTEE_W
ifdef _UNICODE
GetTrusteeName          equ <GetTrusteeNameW>
else
GetTrusteeName          equ <GetTrusteeNameA>
endif

GetTrusteeTypeA proto WINAPI \
              pTrustee: PTRUSTEE_A
GetTrusteeTypeW proto WINAPI \
              pTrustee: PTRUSTEE_W
ifdef _UNICODE
GetTrusteeType          equ <GetTrusteeTypeW>
else
GetTrusteeType          equ <GetTrusteeTypeA>
endif

GetTrusteeFormA proto WINAPI \
              pTrustee: PTRUSTEE_A
GetTrusteeFormW proto WINAPI \
              pTrustee: PTRUSTEE_W
ifdef _UNICODE
GetTrusteeForm          equ <GetTrusteeFormW>
else
GetTrusteeForm          equ <GetTrusteeFormA>
endif

GetMultipleTrusteeOperationA proto WINAPI \
              pTrustee: PTRUSTEE_A
GetMultipleTrusteeOperationW proto WINAPI \
              pTrustee: PTRUSTEE_W
ifdef _UNICODE
GetMultipleTrusteeOperation equ <GetMultipleTrusteeOperationW>
else
GetMultipleTrusteeOperation equ <GetMultipleTrusteeOperationA>
endif

GetMultipleTrusteeA proto WINAPI \
              pTrustee: PTRUSTEE_A
GetMultipleTrusteeW proto WINAPI \
              pTrustee: PTRUSTEE_W
ifdef _UNICODE
GetMultipleTrustee      equ <GetMultipleTrusteeW>
else
GetMultipleTrustee      equ <GetMultipleTrusteeA>
endif

.pragma list(pop)
endif
