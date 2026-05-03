ifndef __ACCESS_CONTROL__
define __ACCESS_CONTROL__
include wtypes.inc
ifndef _WINAPIFAMILY_
include winapifamily.inc
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM)

define AccFree <LocalFree>

.enum SE_OBJECT_TYPE {
    SE_UNKNOWN_OBJECT_TYPE = 0,
    SE_FILE_OBJECT,
    SE_SERVICE,
    SE_PRINTER,
    SE_REGISTRY_KEY,
    SE_LMSHARE,
    SE_KERNEL_OBJECT,
    SE_WINDOW_OBJECT,
    SE_DS_OBJECT,
    SE_DS_OBJECT_ALL,
    SE_PROVIDER_DEFINED_OBJECT,
    SE_WMIGUID_OBJECT,
    SE_REGISTRY_WOW64_32KEY,
    SE_REGISTRY_WOW64_64KEY,
    }

.enum TRUSTEE_TYPE {
    TRUSTEE_IS_UNKNOWN,
    TRUSTEE_IS_USER,
    TRUSTEE_IS_GROUP,
    TRUSTEE_IS_DOMAIN,
    TRUSTEE_IS_ALIAS,
    TRUSTEE_IS_WELL_KNOWN_GROUP,
    TRUSTEE_IS_DELETED,
    TRUSTEE_IS_INVALID,
    TRUSTEE_IS_COMPUTER
    }

.enum TRUSTEE_FORM {
    TRUSTEE_IS_SID,
    TRUSTEE_IS_NAME,
    TRUSTEE_BAD_FORM,
    TRUSTEE_IS_OBJECTS_AND_SID,
    TRUSTEE_IS_OBJECTS_AND_NAME
    }

.enum MULTIPLE_TRUSTEE_OPERATION {
    NO_MULTIPLE_TRUSTEE,
    TRUSTEE_IS_IMPERSONATE,
    }

OBJECTS_AND_SID         struct
ObjectsPresent          DWORD ?
ObjectTypeGuid          GUID <>
InheritedObjectTypeGuid GUID <>
pSid                    PISID ?
OBJECTS_AND_SID         ends
POBJECTS_AND_SID        typedef ptr OBJECTS_AND_SID

OBJECTS_AND_NAME_A      struct
ObjectsPresent          DWORD ?
ObjectType              SE_OBJECT_TYPE ?
ObjectTypeName          LPSTR ?
InheritedObjectTypeName LPSTR ?
ptstrName               LPSTR ?
OBJECTS_AND_NAME_A      ends
POBJECTS_AND_NAME_A     typedef ptr OBJECTS_AND_NAME_A
OBJECTS_AND_NAME_W      struct
ObjectsPresent          DWORD ?
ObjectType              SE_OBJECT_TYPE ?
ObjectTypeName          LPWSTR ?
InheritedObjectTypeName LPWSTR ?
ptstrName               LPWSTR ?
OBJECTS_AND_NAME_W      ends
POBJECTS_AND_NAME_W     typedef ptr OBJECTS_AND_NAME_W
ifdef _UNICODE
OBJECTS_AND_NAME_       typedef OBJECTS_AND_NAME_W
POBJECTS_AND_NAME_      typedef POBJECTS_AND_NAME_W
else
OBJECTS_AND_NAME_       typedef OBJECTS_AND_NAME_A
POBJECTS_AND_NAME_      typedef POBJECTS_AND_NAME_A
endif

TRUSTEE_A               struct
pMultipleTrustee        PVOID ?
MultipleTrusteeOperation MULTIPLE_TRUSTEE_OPERATION ?
TrusteeForm             TRUSTEE_FORM ?
TrusteeType             TRUSTEE_TYPE ?
ptstrName               LPCH ?
TRUSTEE_A               ends
PTRUSTEE_A              typedef ptr TRUSTEE_A
TRUSTEEA                typedef TRUSTEE_A
PTRUSTEEA               typedef ptr TRUSTEE_A
TRUSTEE_W               struct
pMultipleTrustee        PVOID ?
MultipleTrusteeOperation MULTIPLE_TRUSTEE_OPERATION ?
TrusteeForm             TRUSTEE_FORM ?
TrusteeType             TRUSTEE_TYPE ?
ptstrName               LPWCH ?
TRUSTEE_W               ends
PTRUSTEE_W              typedef ptr TRUSTEE_W
TRUSTEEW                typedef TRUSTEE_W
PTRUSTEEW               typedef ptr TRUSTEE_W
ifdef _UNICODE
TRUSTEE_                typedef TRUSTEE_W
PTRUSTEE_               typedef PTRUSTEE_W
TRUSTEE                 typedef TRUSTEEW
PTRUSTEE                typedef PTRUSTEEW
else
TRUSTEE_                typedef TRUSTEE_A
PTRUSTEE_               typedef PTRUSTEE_A
TRUSTEE                 typedef TRUSTEEA
PTRUSTEE                typedef PTRUSTEEA
endif

.enum ACCESS_MODE {
    NOT_USED_ACCESS = 0,
    GRANT_ACCESS,
    SET_ACCESS,
    DENY_ACCESS,
    REVOKE_ACCESS,
    SET_AUDIT_SUCCESS,
    SET_AUDIT_FAILURE
    }

define NO_INHERITANCE 0x0
define SUB_OBJECTS_ONLY_INHERIT            0x1
define SUB_CONTAINERS_ONLY_INHERIT         0x2
define SUB_CONTAINERS_AND_OBJECTS_INHERIT  0x3
define INHERIT_NO_PROPAGATE                0x4
define INHERIT_ONLY                        0x8

define INHERITED_ACCESS_ENTRY              0x10

define INHERITED_PARENT                    0x10000000
define INHERITED_GRANDPARENT               0x20000000

EXPLICIT_ACCESS_A       struct
grfAccessPermissions    DWORD ?
grfAccessMode           ACCESS_MODE ?
grfInheritance          DWORD ?
Trustee                 TRUSTEE_A <>
EXPLICIT_ACCESS_A       ends
PEXPLICIT_ACCESS_A      typedef ptr EXPLICIT_ACCESS_A
EXPLICIT_ACCESSA        typedef EXPLICIT_ACCESS_A
PEXPLICIT_ACCESSA       typedef ptr EXPLICIT_ACCESS_A

EXPLICIT_ACCESS_W       struct
grfAccessPermissions    DWORD ?
grfAccessMode           ACCESS_MODE ?
grfInheritance          DWORD ?
Trustee                 TRUSTEE_W <>
EXPLICIT_ACCESS_W       ends
PEXPLICIT_ACCESS_W      typedef ptr EXPLICIT_ACCESS_W
EXPLICIT_ACCESSW        typedef EXPLICIT_ACCESS_W
PEXPLICIT_ACCESSW       typedef ptr EXPLICIT_ACCESS_W
ifdef _UNICODE
EXPLICIT_ACCESS_        typedef EXPLICIT_ACCESS_W
PEXPLICIT_ACCESS_       typedef PEXPLICIT_ACCESS_W
EXPLICIT_ACCESS         typedef EXPLICIT_ACCESSW
PEXPLICIT_ACCESS        typedef PEXPLICIT_ACCESSW
else
EXPLICIT_ACCESS_        typedef EXPLICIT_ACCESS_A
PEXPLICIT_ACCESS_       typedef PEXPLICIT_ACCESS_A
EXPLICIT_ACCESS         typedef EXPLICIT_ACCESSA
PEXPLICIT_ACCESS        typedef PEXPLICIT_ACCESSA
endif

define ACCCTRL_DEFAULT_PROVIDERA   <"Windows NT Access Provider">
define ACCCTRL_DEFAULT_PROVIDERW  <L"Windows NT Access Provider">

ifdef _UNICODE
define ACCCTRL_DEFAULT_PROVIDER <ACCCTRL_DEFAULT_PROVIDERW>
else
define ACCCTRL_DEFAULT_PROVIDER <ACCCTRL_DEFAULT_PROVIDERA>
endif

ACCESS_RIGHTS           typedef ULONG
PACCESS_RIGHTS          typedef ptr ACCESS_RIGHTS
INHERIT_FLAGS           typedef ULONG
PINHERIT_FLAGS          typedef ptr INHERIT_FLAGS

ACTRL_ACCESS_ENTRYA     struct
Trustee                 TRUSTEE_A <>
fAccessFlags            ULONG ?
Access                  ACCESS_RIGHTS ?
ProvSpecificAccess      ACCESS_RIGHTS ?
Inheritance             INHERIT_FLAGS ?
lpInheritProperty       LPSTR ?
ACTRL_ACCESS_ENTRYA     ends
PACTRL_ACCESS_ENTRYA    typedef ptr ACTRL_ACCESS_ENTRYA
ACTRL_ACCESS_ENTRYW     struct
Trustee                 TRUSTEE_W <>
fAccessFlags            ULONG ?
Access                  ACCESS_RIGHTS ?
ProvSpecificAccess      ACCESS_RIGHTS ?
Inheritance             INHERIT_FLAGS ?
lpInheritProperty       LPWSTR ?
ACTRL_ACCESS_ENTRYW     ends
PACTRL_ACCESS_ENTRYW    typedef ptr ACTRL_ACCESS_ENTRYW
ifdef _UNICODE
ACTRL_ACCESS_ENTRY      typedef ACTRL_ACCESS_ENTRYW
PACTRL_ACCESS_ENTRY     typedef PACTRL_ACCESS_ENTRYW
else
ACTRL_ACCESS_ENTRY      typedef ACTRL_ACCESS_ENTRYA
PACTRL_ACCESS_ENTRY     typedef PACTRL_ACCESS_ENTRYA
endif

ACTRL_ACCESS_ENTRY_LISTA struct
cEntries                ULONG ?
pAccessList             PACTRL_ACCESS_ENTRYA ?
ACTRL_ACCESS_ENTRY_LISTA ends
PACTRL_ACCESS_ENTRY_LISTA typedef ptr ACTRL_ACCESS_ENTRY_LISTA

ACTRL_ACCESS_ENTRY_LISTW struct
cEntries                ULONG ?
pAccessList             PACTRL_ACCESS_ENTRYW ?
ACTRL_ACCESS_ENTRY_LISTW ends
PACTRL_ACCESS_ENTRY_LISTW typedef ptr ACTRL_ACCESS_ENTRY_LISTW
ifdef _UNICODE
ACTRL_ACCESS_ENTRY_LIST typedef ACTRL_ACCESS_ENTRY_LISTW
PACTRL_ACCESS_ENTRY_LIST typedef PACTRL_ACCESS_ENTRY_LISTW
else
ACTRL_ACCESS_ENTRY_LIST typedef ACTRL_ACCESS_ENTRY_LISTA
PACTRL_ACCESS_ENTRY_LIST typedef PACTRL_ACCESS_ENTRY_LISTA
endif

ACTRL_PROPERTY_ENTRYA   struct
lpProperty              LPSTR ?
pAccessEntryList        PACTRL_ACCESS_ENTRY_LISTA ?
fListFlags              ULONG ?
ACTRL_PROPERTY_ENTRYA   ends
PACTRL_PROPERTY_ENTRYA  typedef ptr ACTRL_PROPERTY_ENTRYA
ACTRL_PROPERTY_ENTRYW   struct
lpProperty              LPWSTR ?
pAccessEntryList        PACTRL_ACCESS_ENTRY_LISTW ?
fListFlags              ULONG ?
ACTRL_PROPERTY_ENTRYW   ends
PACTRL_PROPERTY_ENTRYW  typedef ptr ACTRL_PROPERTY_ENTRYW
ifdef _UNICODE
ACTRL_PROPERTY_ENTRY    typedef ACTRL_PROPERTY_ENTRYW
PACTRL_PROPERTY_ENTRY   typedef PACTRL_PROPERTY_ENTRYW
else
ACTRL_PROPERTY_ENTRY    typedef ACTRL_PROPERTY_ENTRYA
PACTRL_PROPERTY_ENTRY   typedef PACTRL_PROPERTY_ENTRYA
endif

ACTRL_ALISTA            struct
cEntries                ULONG ?
pPropertyAccessList     PACTRL_PROPERTY_ENTRYA ?
ACTRL_ALISTA            ends
ACTRL_ACCESSA           typedef ACTRL_ALISTA
PACTRL_ACCESSA          typedef ptr ACTRL_ALISTA
ACTRL_AUDITA            typedef ACTRL_ALISTA
PACTRL_AUDITA           typedef ptr ACTRL_ALISTA
ACTRL_ALISTW            struct
cEntries                ULONG ?
pPropertyAccessList     PACTRL_PROPERTY_ENTRYW ?
ACTRL_ALISTW            ends
ACTRL_ACCESSW           typedef ACTRL_ALISTW
PACTRL_ACCESSW          typedef ptr ACTRL_ALISTW
ACTRL_AUDITW            typedef ACTRL_ALISTW
PACTRL_AUDITW           typedef ptr ACTRL_ALISTW
ifdef _UNICODE
ACTRL_ACCESS            typedef ACTRL_ACCESSW
PACTRL_ACCESS           typedef PACTRL_ACCESSW
ACTRL_AUDIT             typedef ACTRL_AUDITW
PACTRL_AUDIT            typedef PACTRL_AUDITW
else
ACTRL_ACCESS            typedef ACTRL_ACCESSA
PACTRL_ACCESS           typedef PACTRL_ACCESSA
ACTRL_AUDIT             typedef ACTRL_AUDITA
PACTRL_AUDIT            typedef PACTRL_AUDITA
endif

define TRUSTEE_ACCESS_ALLOWED      0x00000001
define TRUSTEE_ACCESS_READ         0x00000002
define TRUSTEE_ACCESS_WRITE        0x00000004

define TRUSTEE_ACCESS_EXPLICIT     0x00000001
define TRUSTEE_ACCESS_READ_WRITE   (TRUSTEE_ACCESS_READ or TRUSTEE_ACCESS_WRITE)

define TRUSTEE_ACCESS_ALL          0xFFFFFFFF

TRUSTEE_ACCESSA         struct
lpProperty              LPSTR ?
Access                  ACCESS_RIGHTS ?
fAccessFlags            ULONG ?
fReturnedAccess         ULONG ?
TRUSTEE_ACCESSA         ends
PTRUSTEE_ACCESSA        typedef ptr TRUSTEE_ACCESSA
TRUSTEE_ACCESSW         struct
lpProperty              LPWSTR ?
Access                  ACCESS_RIGHTS ?
fAccessFlags            ULONG ?
fReturnedAccess         ULONG ?
TRUSTEE_ACCESSW         ends
PTRUSTEE_ACCESSW        typedef ptr TRUSTEE_ACCESSW
ifdef _UNICODE
TRUSTEE_ACCESS          typedef TRUSTEE_ACCESSW
PTRUSTEE_ACCESS         typedef PTRUSTEE_ACCESSW
else
TRUSTEE_ACCESS          typedef TRUSTEE_ACCESSA
PTRUSTEE_ACCESS         typedef PTRUSTEE_ACCESSA
endif

define ACTRL_RESERVED          0x00000000
define ACTRL_PERM_1            0x00000001
define ACTRL_PERM_2            0x00000002
define ACTRL_PERM_3            0x00000004
define ACTRL_PERM_4            0x00000008
define ACTRL_PERM_5            0x00000010
define ACTRL_PERM_6            0x00000020
define ACTRL_PERM_7            0x00000040
define ACTRL_PERM_8            0x00000080
define ACTRL_PERM_9            0x00000100
define ACTRL_PERM_10           0x00000200
define ACTRL_PERM_11           0x00000400
define ACTRL_PERM_12           0x00000800
define ACTRL_PERM_13           0x00001000
define ACTRL_PERM_14           0x00002000
define ACTRL_PERM_15           0x00004000
define ACTRL_PERM_16           0x00008000
define ACTRL_PERM_17           0x00010000
define ACTRL_PERM_18           0x00020000
define ACTRL_PERM_19           0x00040000
define ACTRL_PERM_20           0x00080000

define ACTRL_ACCESS_ALLOWED        0x00000001
define ACTRL_ACCESS_DENIED         0x00000002
define ACTRL_AUDIT_SUCCESS         0x00000004
define ACTRL_AUDIT_FAILURE         0x00000008

define ACTRL_ACCESS_PROTECTED      0x00000001

define ACTRL_SYSTEM_ACCESS         0x04000000
define ACTRL_DELETE                0x08000000
define ACTRL_READ_CONTROL          0x10000000
define ACTRL_CHANGE_ACCESS         0x20000000
define ACTRL_CHANGE_OWNER          0x40000000
define ACTRL_SYNCHRONIZE           0x80000000
define ACTRL_STD_RIGHTS_ALL        0xf8000000
define ACTRL_STD_RIGHT_REQUIRED    ( ACTRL_STD_RIGHTS_ALL and not ACTRL_SYNCHRONIZE )

ifndef _DS_CONTROL_BITS_DEFINED_
define _DS_CONTROL_BITS_DEFINED_
define ACTRL_DS_OPEN                           ACTRL_RESERVED
define ACTRL_DS_CREATE_CHILD                   ACTRL_PERM_1
define ACTRL_DS_DELETE_CHILD                   ACTRL_PERM_2
define ACTRL_DS_LIST                           ACTRL_PERM_3
define ACTRL_DS_SELF                           ACTRL_PERM_4
define ACTRL_DS_READ_PROP                      ACTRL_PERM_5
define ACTRL_DS_WRITE_PROP                     ACTRL_PERM_6
define ACTRL_DS_DELETE_TREE                    ACTRL_PERM_7
define ACTRL_DS_LIST_OBJECT                    ACTRL_PERM_8
define ACTRL_DS_CONTROL_ACCESS                 ACTRL_PERM_9
endif

define ACTRL_FILE_READ                         ACTRL_PERM_1
define ACTRL_FILE_WRITE                        ACTRL_PERM_2
define ACTRL_FILE_APPEND                       ACTRL_PERM_3
define ACTRL_FILE_READ_PROP                    ACTRL_PERM_4
define ACTRL_FILE_WRITE_PROP                   ACTRL_PERM_5
define ACTRL_FILE_EXECUTE                      ACTRL_PERM_6
define ACTRL_FILE_READ_ATTRIB                  ACTRL_PERM_8
define ACTRL_FILE_WRITE_ATTRIB                 ACTRL_PERM_9
define ACTRL_FILE_CREATE_PIPE                  ACTRL_PERM_10
define ACTRL_DIR_LIST                          ACTRL_PERM_1
define ACTRL_DIR_CREATE_OBJECT                 ACTRL_PERM_2
define ACTRL_DIR_CREATE_CHILD                  ACTRL_PERM_3
define ACTRL_DIR_DELETE_CHILD                  ACTRL_PERM_7
define ACTRL_DIR_TRAVERSE                      ACTRL_PERM_6
define ACTRL_KERNEL_TERMINATE                  ACTRL_PERM_1
define ACTRL_KERNEL_THREAD                     ACTRL_PERM_2
define ACTRL_KERNEL_VM                         ACTRL_PERM_3
define ACTRL_KERNEL_VM_READ                    ACTRL_PERM_4
define ACTRL_KERNEL_VM_WRITE                   ACTRL_PERM_5
define ACTRL_KERNEL_DUP_HANDLE                 ACTRL_PERM_6
define ACTRL_KERNEL_PROCESS                    ACTRL_PERM_7
define ACTRL_KERNEL_SET_INFO                   ACTRL_PERM_8
define ACTRL_KERNEL_GET_INFO                   ACTRL_PERM_9
define ACTRL_KERNEL_CONTROL                    ACTRL_PERM_10
define ACTRL_KERNEL_ALERT                      ACTRL_PERM_11
define ACTRL_KERNEL_GET_CONTEXT                ACTRL_PERM_12
define ACTRL_KERNEL_SET_CONTEXT                ACTRL_PERM_13
define ACTRL_KERNEL_TOKEN                      ACTRL_PERM_14
define ACTRL_KERNEL_IMPERSONATE                ACTRL_PERM_15
define ACTRL_KERNEL_DIMPERSONATE               ACTRL_PERM_16
define ACTRL_PRINT_SADMIN                      ACTRL_PERM_1
define ACTRL_PRINT_SLIST                       ACTRL_PERM_2
define ACTRL_PRINT_PADMIN                      ACTRL_PERM_3
define ACTRL_PRINT_PUSE                        ACTRL_PERM_4
define ACTRL_PRINT_JADMIN                      ACTRL_PERM_5
define ACTRL_SVC_GET_INFO                      ACTRL_PERM_1
define ACTRL_SVC_SET_INFO                      ACTRL_PERM_2
define ACTRL_SVC_STATUS                        ACTRL_PERM_3
define ACTRL_SVC_LIST                          ACTRL_PERM_4
define ACTRL_SVC_START                         ACTRL_PERM_5
define ACTRL_SVC_STOP                          ACTRL_PERM_6
define ACTRL_SVC_PAUSE                         ACTRL_PERM_7
define ACTRL_SVC_INTERROGATE                   ACTRL_PERM_8
define ACTRL_SVC_UCONTROL                      ACTRL_PERM_9
define ACTRL_REG_QUERY                         ACTRL_PERM_1
define ACTRL_REG_SET                           ACTRL_PERM_2
define ACTRL_REG_CREATE_CHILD                  ACTRL_PERM_3
define ACTRL_REG_LIST                          ACTRL_PERM_4
define ACTRL_REG_NOTIFY                        ACTRL_PERM_5
define ACTRL_REG_LINK                          ACTRL_PERM_6
define ACTRL_WIN_CLIPBRD                       ACTRL_PERM_1
define ACTRL_WIN_GLOBAL_ATOMS                  ACTRL_PERM_2
define ACTRL_WIN_CREATE                        ACTRL_PERM_3
define ACTRL_WIN_LIST_DESK                     ACTRL_PERM_4
define ACTRL_WIN_LIST                          ACTRL_PERM_5
define ACTRL_WIN_READ_ATTRIBS                  ACTRL_PERM_6
define ACTRL_WIN_WRITE_ATTRIBS                 ACTRL_PERM_7
define ACTRL_WIN_SCREEN                        ACTRL_PERM_8
define ACTRL_WIN_EXIT                          ACTRL_PERM_9


ACTRL_OVERLAPPED        struct
union
 Provider               PVOID ?
 Reserved1              ULONG ?
ends
Reserved2               ULONG ?
hEvent                  HANDLE ?
ACTRL_OVERLAPPED        ends
PACTRL_OVERLAPPED       typedef ptr ACTRL_OVERLAPPED

ACTRL_ACCESS_INFOA      struct
fAccessPermission       ULONG ?
lpAccessPermissionName  LPSTR ?
ACTRL_ACCESS_INFOA      ends
PACTRL_ACCESS_INFOA     typedef ptr ACTRL_ACCESS_INFOA
ACTRL_ACCESS_INFOW      struct
fAccessPermission       ULONG ?
lpAccessPermissionName  LPWSTR ?
ACTRL_ACCESS_INFOW      ends
PACTRL_ACCESS_INFOW     typedef ptr ACTRL_ACCESS_INFOW
ifdef _UNICODE
ACTRL_ACCESS_INFO       typedef ACTRL_ACCESS_INFOW
PACTRL_ACCESS_INFO      typedef PACTRL_ACCESS_INFOW
else
ACTRL_ACCESS_INFO       typedef ACTRL_ACCESS_INFOA
PACTRL_ACCESS_INFO      typedef PACTRL_ACCESS_INFOA
endif

ACTRL_CONTROL_INFOA     struct
lpControlId             LPSTR ?
lpControlName           LPSTR ?
ACTRL_CONTROL_INFOA     ends
PACTRL_CONTROL_INFOA    typedef ptr ACTRL_CONTROL_INFOA
ACTRL_CONTROL_INFOW     struct
lpControlId             LPWSTR ?
lpControlName           LPWSTR ?
ACTRL_CONTROL_INFOW     ends
PACTRL_CONTROL_INFOW    typedef ptr ACTRL_CONTROL_INFOW
ifdef _UNICODE
ACTRL_CONTROL_INFO      typedef ACTRL_CONTROL_INFOW
PACTRL_CONTROL_INFO     typedef PACTRL_CONTROL_INFOW
else
ACTRL_CONTROL_INFO      typedef ACTRL_CONTROL_INFOA
PACTRL_CONTROL_INFO     typedef PACTRL_CONTROL_INFOA
endif

define ACTRL_ACCESS_NO_OPTIONS                 0x00000000
define ACTRL_ACCESS_SUPPORTS_OBJECT_ENTRIES    0x00000001

if (NTDDI_VERSION ge NTDDI_VISTA)
define TREE_SEC_INFO_SET                   0x00000001
define TREE_SEC_INFO_RESET                 0x00000002
define TREE_SEC_INFO_RESET_KEEP_EXPLICIT   0x00000003
endif

.enum PROG_INVOKE_SETTING {
    ProgressInvokeNever = 1,
    ProgressInvokeEveryObject,
    ProgressInvokeOnError,
    ProgressCancelOperation,
    ProgressRetryOperation,
if (NTDDI_VERSION ge NTDDI_VISTA)
    ProgressInvokePrePostError,
endif
}

FN_OBJECT_MGR_FUNCTIONS struct
Placeholder             ULONG ?
FN_OBJECT_MGR_FUNCTIONS ends
FN_OBJECT_MGR_FUNCTS    typedef FN_OBJECT_MGR_FUNCTIONS
PFN_OBJECT_MGR_FUNCTS   typedef ptr FN_OBJECT_MGR_FUNCTIONS

INHERITED_FROMA         struct
GenerationGap           LONG ?
AncestorName            LPSTR ?
INHERITED_FROMA         ends
PINHERITED_FROMA        typedef ptr INHERITED_FROMA
INHERITED_FROMW         struct
GenerationGap           LONG ?
AncestorName            LPWSTR ?
INHERITED_FROMW         ends
PINHERITED_FROMW        typedef ptr INHERITED_FROMW
ifdef _UNICODE
INHERITED_FROM          typedef INHERITED_FROMW
PINHERITED_FROM         typedef PINHERITED_FROMW
else
INHERITED_FROM          typedef INHERITED_FROMA
PINHERITED_FROM         typedef PINHERITED_FROMA
endif

endif

endif
