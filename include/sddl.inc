ifndef __SDDL_H__
define __SDDL_H__

include apiset.inc
include apisetcconv.inc

ifdef _CONTRACT_GEN
include minwindef.inc
endif

ifndef _APISET_SDDL_VER
ifdef _APISET_MINWIN_VERSION
if _APISET_MINWIN_VERSION GE 0x0100
define _APISET_SDDL_VER 0x0100
endif
endif
endif

.pragma comment(lib, advapi32)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

SDDL_REVISION_1         equ 1
SDDL_REVISION           equ SDDL_REVISION_1

SDDL_OWNER              equ <"O">
SDDL_GROUP              equ <"G">
SDDL_DACL               equ <"D">
SDDL_SACL               equ <"S">

SDDL_PROTECTED          equ <"P">
SDDL_AUTO_INHERIT_REQ   equ <"AR">
SDDL_AUTO_INHERITED     equ <"AI">
SDDL_NULL_ACL           equ <"NO_ACCESS_CONTROL">

SDDL_ACCESS_ALLOWED     equ <"A">
SDDL_ACCESS_DENIED      equ <"D">
SDDL_OBJECT_ACCESS_ALLOWED equ <"OA">
SDDL_OBJECT_ACCESS_DENIED equ <"OD">
SDDL_AUDIT              equ <"AU">
SDDL_ALARM              equ <"AL">
SDDL_OBJECT_AUDIT       equ <"OU">
SDDL_OBJECT_ALARM       equ <"OL">
SDDL_MANDATORY_LABEL    equ <"ML">
SDDL_PROCESS_TRUST_LABEL equ <"TL">
SDDL_CALLBACK_ACCESS_ALLOWED equ <"XA">
SDDL_CALLBACK_ACCESS_DENIED equ <"XD">
SDDL_RESOURCE_ATTRIBUTE equ <"RA">
SDDL_SCOPED_POLICY_ID   equ <"SP">
SDDL_CALLBACK_AUDIT     equ <"XU">
SDDL_CALLBACK_OBJECT_ACCESS_ALLOWED equ <"ZA">


SDDL_INT                equ <"TI">
SDDL_UINT               equ <"TU">
SDDL_WSTRING            equ <"TS">
SDDL_SID                equ <"TD">
SDDL_BLOB               equ <"TX">
SDDL_BOOLEAN            equ <"TB">


SDDL_CONTAINER_INHERIT  equ <"CI">
SDDL_OBJECT_INHERIT     equ <"OI">
SDDL_NO_PROPAGATE       equ <"NP">
SDDL_INHERIT_ONLY       equ <"IO">
SDDL_INHERITED          equ <"ID">
SDDL_AUDIT_SUCCESS      equ <"SA">
SDDL_AUDIT_FAILURE      equ <"FA">


SDDL_READ_PROPERTY      equ <"RP">
SDDL_WRITE_PROPERTY     equ <"WP">
SDDL_CREATE_CHILD       equ <"CC">
SDDL_DELETE_CHILD       equ <"DC">
SDDL_LIST_CHILDREN      equ <"LC">
SDDL_SELF_WRITE         equ <"SW">
SDDL_LIST_OBJECT        equ <"LO">
SDDL_DELETE_TREE        equ <"DT">
SDDL_CONTROL_ACCESS     equ <"CR">
SDDL_READ_CONTROL       equ <"RC">
SDDL_WRITE_DAC          equ <"WD">
SDDL_WRITE_OWNER        equ <"WO">
SDDL_STANDARD_DELETE    equ <"SD">
SDDL_GENERIC_ALL        equ <"GA">
SDDL_GENERIC_READ       equ <"GR">
SDDL_GENERIC_WRITE      equ <"GW">
SDDL_GENERIC_EXECUTE    equ <"GX">
SDDL_FILE_ALL           equ <"FA">
SDDL_FILE_READ          equ <"FR">
SDDL_FILE_WRITE         equ <"FW">
SDDL_FILE_EXECUTE       equ <"FX">
SDDL_KEY_ALL            equ <"KA">
SDDL_KEY_READ           equ <"KR">
SDDL_KEY_WRITE          equ <"KW">
SDDL_KEY_EXECUTE        equ <"KX">
SDDL_NO_WRITE_UP        equ <"NW">
SDDL_NO_READ_UP         equ <"NR">
SDDL_NO_EXECUTE_UP      equ <"NX">


SDDL_ALIAS_SIZE         equ 2

SDDL_DOMAIN_ADMINISTRATORS equ <"DA">
SDDL_DOMAIN_GUESTS      equ <"DG">
SDDL_DOMAIN_USERS       equ <"DU">
SDDL_ENTERPRISE_DOMAIN_CONTROLLERS equ <"ED">
SDDL_DOMAIN_DOMAIN_CONTROLLERS equ <"DD">
SDDL_DOMAIN_COMPUTERS   equ <"DC">
SDDL_BUILTIN_ADMINISTRATORS equ <"BA">
SDDL_BUILTIN_GUESTS     equ <"BG">
SDDL_BUILTIN_USERS      equ <"BU">
SDDL_LOCAL_ADMIN        equ <"LA">
SDDL_LOCAL_GUEST        equ <"LG">
SDDL_ACCOUNT_OPERATORS  equ <"AO">
SDDL_BACKUP_OPERATORS   equ <"BO">
SDDL_PRINTER_OPERATORS  equ <"PO">
SDDL_SERVER_OPERATORS   equ <"SO">
SDDL_AUTHENTICATED_USERS equ <"AU">
SDDL_PERSONAL_SELF      equ <"PS">
SDDL_CREATOR_OWNER      equ <"CO">
SDDL_CREATOR_GROUP      equ <"CG">
SDDL_LOCAL_SYSTEM       equ <"SY">
SDDL_POWER_USERS        equ <"PU">
SDDL_EVERYONE           equ <"WD">
SDDL_REPLICATOR         equ <"RE">
SDDL_INTERACTIVE        equ <"IU">
SDDL_NETWORK            equ <"NU">
SDDL_SERVICE            equ <"SU">
SDDL_RESTRICTED_CODE    equ <"RC">
SDDL_WRITE_RESTRICTED_CODE equ <"WR">
SDDL_ANONYMOUS          equ <"AN">
SDDL_SCHEMA_ADMINISTRATORS equ <"SA">
SDDL_CERT_SERV_ADMINISTRATORS equ <"CA">
SDDL_RAS_SERVERS        equ <"RS">
SDDL_ENTERPRISE_ADMINS  equ <"EA">
SDDL_GROUP_POLICY_ADMINS equ <"PA">
SDDL_ALIAS_PREW2KCOMPACC equ <"RU">
SDDL_LOCAL_SERVICE      equ <"LS">
SDDL_NETWORK_SERVICE    equ <"NS">
SDDL_REMOTE_DESKTOP     equ <"RD">
SDDL_NETWORK_CONFIGURATION_OPS equ <"NO">
SDDL_PERFMON_USERS      equ <"MU">
SDDL_PERFLOG_USERS      equ <"LU">
SDDL_IIS_USERS          equ <"IS">
SDDL_CRYPTO_OPERATORS   equ <"CY">
SDDL_OWNER_RIGHTS       equ <"OW">
SDDL_EVENT_LOG_READERS  equ <"ER">
SDDL_ENTERPRISE_RO_DCs  equ <"RO">
SDDL_CERTSVC_DCOM_ACCESS equ <"CD">
SDDL_ALL_APP_PACKAGES   equ <"AC">
SDDL_RDS_REMOTE_ACCESS_SERVERS equ <"RA">
SDDL_RDS_ENDPOINT_SERVERS equ <"ES">
SDDL_RDS_MANAGEMENT_SERVERS equ <"MS">
SDDL_USER_MODE_DRIVERS  equ <"UD">
SDDL_HYPER_V_ADMINS     equ <"HA">
SDDL_CLONEABLE_CONTROLLERS equ <"CN">
SDDL_ACCESS_CONTROL_ASSISTANCE_OPS equ <"AA">
SDDL_REMOTE_MANAGEMENT_USERS equ <"RM">
SDDL_AUTHORITY_ASSERTED equ <"AS">
SDDL_SERVICE_ASSERTED   equ <"SS">
SDDL_PROTECTED_USERS    equ <"AP">

SDDL_ML_LOW             equ <"LW">
SDDL_ML_MEDIUM          equ <"ME">
SDDL_ML_MEDIUM_PLUS     equ <"MP">
SDDL_ML_HIGH            equ <"HI">
SDDL_ML_SYSTEM          equ <"SI">

SDDL_SEPERATORC         equ ';'
SDDL_DELIMINATORC       equ ':'
SDDL_ACE_BEGINC         equ '('
SDDL_ACE_ENDC           equ ')'
SDDL_SPACEC             equ ' '
SDDL_ACE_COND_BEGINC    equ '('
SDDL_ACE_COND_ENDC      equ ')'
SDDL_ACE_COND_STRING_BEGINC equ '"'
SDDL_ACE_COND_STRING_ENDC equ '"'
SDDL_ACE_COND_COMPOSITEVALUE_BEGINC equ '{'
SDDL_ACE_COND_COMPOSITEVALUE_ENDC equ '}'
SDDL_ACE_COND_COMPOSITEVALUE_SEPERATORC equ ','
SDDL_ACE_COND_BLOB_PREFIXC equ '#'
SDDL_ACE_COND_SID_BEGINC equ '('
SDDL_ACE_COND_SID_ENDC  equ ')'

SDDL_SEPERATOR          equ <";">
SDDL_DELIMINATOR        equ <":">
SDDL_ACE_BEGIN          equ <"(">
SDDL_ACE_END            equ <")">
SDDL_ACE_COND_BEGIN     equ <"(">
SDDL_ACE_COND_END       equ <")">
SDDL_SPACE              equ <" ">
SDDL_ACE_COND_BLOB_PREFIX equ <"#">
SDDL_ACE_COND_SID_PREFIX equ <"SID">
SDDL_ACE_COND_ATTRIBUTE_PREFIX equ <"@">
SDDL_ACE_COND_USER_ATTRIBUTE_PREFIX equ <"@USER.">
SDDL_ACE_COND_RESOURCE_ATTRIBUTE_PREFIX equ <"@RESOURCE.">
SDDL_ACE_COND_DEVICE_ATTRIBUTE_PREFIX equ <"@DEVICE.">


if NOT defined(_NTDDK_)

if (_WIN32_WINNT GE 0x0500)

;BOOL
ConvertSidToStringSidA proto WINAPI \
                   Sid: PSID,
             StringSid: ptr LPSTR

ConvertSidToStringSidW proto WINAPI \
                   Sid: PSID,
             StringSid: ptr LPWSTR

ifdef _UNICODE
ConvertSidToStringSid   equ <ConvertSidToStringSidW>
else
ConvertSidToStringSid   equ <ConvertSidToStringSidA>
endif

;BOOL
ConvertStringSidToSidA proto WINAPI \
             StringSid: LPCSTR,
                   Sid: ptr PSID

ConvertStringSidToSidW proto WINAPI \
             StringSid: LPCWSTR,
                   Sid: ptr PSID

ifdef _UNICODE
ConvertStringSidToSid   equ <ConvertStringSidToSidW>
else
ConvertStringSidToSid   equ <ConvertStringSidToSidA>
endif

;BOOL
ConvertStringSecurityDescriptorToSecurityDescriptorA proto WINAPI \
StringSecurityDescriptor: LPCSTR,
      StringSDRevision: DWORD,
    SecurityDescriptor: ptr PSECURITY_DESCRIPTOR,
SecurityDescriptorSize: PULONG

ConvertStringSecurityDescriptorToSecurityDescriptorW proto WINAPI \
StringSecurityDescriptor: LPCWSTR,
      StringSDRevision: DWORD,
    SecurityDescriptor: ptr PSECURITY_DESCRIPTOR,
SecurityDescriptorSize: PULONG

ifdef _UNICODE
ConvertStringSecurityDescriptorToSecurityDescriptor equ <ConvertStringSecurityDescriptorToSecurityDescriptorW>
else
ConvertStringSecurityDescriptorToSecurityDescriptor equ <ConvertStringSecurityDescriptorToSecurityDescriptorA>
endif


;BOOL
ConvertSecurityDescriptorToStringSecurityDescriptorA proto WINAPI \
    SecurityDescriptor: PSECURITY_DESCRIPTOR,
RequestedStringSDRevision: DWORD,
   SecurityInformation: SECURITY_INFORMATION,
StringSecurityDescriptor: ptr LPSTR,
StringSecurityDescriptorLen: PULONG

ConvertSecurityDescriptorToStringSecurityDescriptorW proto WINAPI \
    SecurityDescriptor: PSECURITY_DESCRIPTOR,
RequestedStringSDRevision: DWORD,
   SecurityInformation: SECURITY_INFORMATION,
 StringSecurityDescriptor: ptr LPWSTR,
StringSecurityDescriptorLen: PULONG

ifdef _UNICODE
ConvertSecurityDescriptorToStringSecurityDescriptor equ <ConvertSecurityDescriptorToStringSecurityDescriptorW>
else
ConvertSecurityDescriptorToStringSecurityDescriptor equ <ConvertSecurityDescriptorToStringSecurityDescriptorA>
endif

endif
endif
endif
endif
