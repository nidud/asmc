ifndef _WINREG_
define _WINREG_

ifndef _WINAPIFAMILY_
include winapifamily.inc
endif

include apiset.inc
include apisetcconv.inc
include minwindef.inc
include minwinbase.inc

ifdef _MAC
include macwin32.inc
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)

ifndef WINVER
define WINVER 0x0500
endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)
LSTATUS typedef LONG
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)

define RRF_RT_REG_NONE        0x00000001
define RRF_RT_REG_SZ          0x00000002
define RRF_RT_REG_EXPAND_SZ   0x00000004
define RRF_RT_REG_BINARY      0x00000008
define RRF_RT_REG_DWORD       0x00000010
define RRF_RT_REG_MULTI_SZ    0x00000020
define RRF_RT_REG_QWORD       0x00000040

define RRF_RT_DWORD           (RRF_RT_REG_BINARY or RRF_RT_REG_DWORD)
define RRF_RT_QWORD           (RRF_RT_REG_BINARY or RRF_RT_REG_QWORD)
define RRF_RT_ANY             0x0000ffff

if (_WIN32_WINNT ge _WIN32_WINNT_WINTHRESHOLD)
define RRF_SUBKEY_WOW6464KEY  0x00010000
define RRF_SUBKEY_WOW6432KEY  0x00020000
define RRF_WOW64_MASK         0x00030000
endif

define RRF_NOEXPAND           0x10000000
define RRF_ZEROONFAILURE      0x20000000

define REG_PROCESS_APPKEY     0x00000001

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

REGSAM typedef ACCESS_MASK

define HKEY_CLASSES_ROOT                   0x80000000
define HKEY_CURRENT_USER                   0x80000001
define HKEY_LOCAL_MACHINE                  0x80000002
define HKEY_USERS                          0x80000003
define HKEY_PERFORMANCE_DATA               0x80000004
define HKEY_PERFORMANCE_TEXT               0x80000050
define HKEY_PERFORMANCE_NLSTEXT            0x80000060
if(WINVER ge 0x0400)
define HKEY_CURRENT_CONFIG                 0x80000005
define HKEY_DYN_DATA                       0x80000006
define HKEY_CURRENT_USER_LOCAL_SETTINGS    0x80000007

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)

ifndef _PROVIDER_STRUCTS_DEFINED
define _PROVIDER_STRUCTS_DEFINED

define PROVIDER_KEEPS_VALUE_LENGTH 0x1
val_context             struct
valuelen                sdword ?
value_context           LPVOID ?
val_buff_ptr            LPVOID ?
val_context             ends
PVALCONTEXT             typedef ptr val_context

pvalueA                 struct
pv_valuename            LPSTR ?
pv_valuelen             sdword ?
pv_value_context        LPVOID ?
pv_type                 DWORD ?
pvalueA                 ends
PVALUEA                 typedef pvalueA
PPVALUEA                typedef ptr pvalueA
pvalueW                 struct
pv_valuename            LPWSTR ?
pv_valuelen             sdword ?
pv_value_context        LPVOID ?
pv_type                 DWORD ?
pvalueW                 ends
PVALUEW                 typedef pvalueW
PPVALUEW                typedef ptr pvalueW
ifdef _UNICODE
PVALUE                  typedef PVALUEW
PPVALUE                 typedef PPVALUEW
else
PVALUE                  typedef PVALUEA
PPVALUE                 typedef PPVALUEA
endif

CALLBACKC(QUERYHANDLER, :ptr, :PVALCONTEXT, :DWORD, :ptr, :ptr, :DWORD)

PQUERYHANDLER           typedef ptr QUERYHANDLER

provider_info           struct
pi_R0_1val              PQUERYHANDLER ?
pi_R0_allvals           PQUERYHANDLER ?
pi_R3_1val              PQUERYHANDLER ?
pi_R3_allvals           PQUERYHANDLER ?
pi_flags                DWORD ?
pi_key_context          LPVOID ?
provider_info           ends
REG_PROVIDER            typedef provider_info
PPROVIDER               typedef ptr provider_info

value_entA              struct
ve_valuename            LPSTR ?
ve_valuelen             DWORD ?
ve_valueptr             DWORD_PTR ?
ve_type                 DWORD ?
value_entA              ends
VALENTA                 typedef value_entA
PVALENTA                typedef ptr value_entA
value_entW              struct
ve_valuename            LPWSTR ?
ve_valuelen             DWORD ?
ve_valueptr             DWORD_PTR ?
ve_type                 DWORD ?
value_entW              ends
VALENTW                 typedef value_entW
PVALENTW                typedef ptr value_entW
ifdef _UNICODE
VALENT                  typedef VALENTW
PVALENT                 typedef PVALENTW
else
VALENT                  typedef VALENTA
PVALENT                 typedef PVALENTA
endif

endif

endif

define WIN31_CLASS NULL

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)

define REG_MUI_STRING_TRUNCATE 0x00000001

if(WINVER ge 0x0400)
define REG_SECURE_CONNECTION 1
endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)
RegCloseKey proto WINAPI :HKEY
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)

RegOverridePredefKey proto WINAPI :HKEY, :HKEY
RegOpenUserClassesRoot proto WINAPI :HANDLE, :DWORD, :REGSAM, :PHKEY
RegOpenCurrentUser proto WINAPI :REGSAM, :PHKEY
RegDisablePredefinedCache proto WINAPI
RegDisablePredefinedCacheEx proto WINAPI

RegConnectRegistryA proto WINAPI :LPCSTR, :HKEY, :PHKEY
RegConnectRegistryW proto WINAPI :LPCWSTR, :HKEY, :PHKEY
ifdef _UNICODE
define RegConnectRegistry  <RegConnectRegistryW>
else
define RegConnectRegistry  <RegConnectRegistryA>
endif

RegConnectRegistryExA proto WINAPI :LPCSTR, :HKEY, :ULONG, :PHKEY
RegConnectRegistryExW proto WINAPI :LPCWSTR, :HKEY, :ULONG, :PHKEY
ifdef _UNICODE
define RegConnectRegistryEx  <RegConnectRegistryExW>
else
define RegConnectRegistryEx  <RegConnectRegistryExA>
endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

RegCreateKeyA proto WINAPI :HKEY, :LPCSTR, :PHKEY
RegCreateKeyW proto WINAPI :HKEY, :LPCWSTR, :PHKEY
ifdef _UNICODE
define RegCreateKey  <RegCreateKeyW>
else
define RegCreateKey  <RegCreateKeyA>
endif

RegCreateKeyExA proto WINAPI :HKEY, :LPCSTR, :DWORD, :LPSTR, :DWORD, :REGSAM, :LPSECURITY_ATTRIBUTES, :PHKEY, :LPDWORD
RegCreateKeyExW proto WINAPI :HKEY, :LPCWSTR, :DWORD, :LPWSTR, :DWORD, :REGSAM, :LPSECURITY_ATTRIBUTES, :PHKEY, :LPDWORD
ifdef _UNICODE
define RegCreateKeyEx  <RegCreateKeyExW>
else
define RegCreateKeyEx  <RegCreateKeyExA>
endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)

RegCreateKeyTransactedA proto WINAPI :HKEY, :LPCSTR, :DWORD, :LPSTR, :DWORD, :REGSAM, :LPSECURITY_ATTRIBUTES, :PHKEY, :LPDWORD, :HANDLE, :PVOID
RegCreateKeyTransactedW proto WINAPI :HKEY, :LPCWSTR, :DWORD, :LPWSTR, :DWORD, :REGSAM, :LPSECURITY_ATTRIBUTES, :PHKEY, :LPDWORD, :HANDLE, :PVOID
ifdef _UNICODE
define RegCreateKeyTransacted  <RegCreateKeyTransactedW>
else
define RegCreateKeyTransacted  <RegCreateKeyTransactedA>
endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

RegDeleteKeyA proto WINAPI :HKEY, :LPCSTR
RegDeleteKeyW proto WINAPI :HKEY, :LPCWSTR
ifdef _UNICODE
define RegDeleteKey  <RegDeleteKeyW>
else
define RegDeleteKey  <RegDeleteKeyA>
endif

RegDeleteKeyExA proto WINAPI :HKEY, :LPCSTR, :REGSAM, :DWORD
RegDeleteKeyExW proto WINAPI :HKEY, :LPCWSTR, :REGSAM, :DWORD
ifdef _UNICODE
define RegDeleteKeyEx  <RegDeleteKeyExW>
else
define RegDeleteKeyEx  <RegDeleteKeyExA>
endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)

RegDeleteKeyTransactedA proto WINAPI :HKEY, :LPCSTR, :REGSAM, :DWORD, :HANDLE, :PVOID
RegDeleteKeyTransactedW proto WINAPI :HKEY, :LPCWSTR, :REGSAM, :DWORD, :HANDLE, :PVOID
ifdef _UNICODE
define RegDeleteKeyTransacted  <RegDeleteKeyTransactedW>
else
define RegDeleteKeyTransacted  <RegDeleteKeyTransactedA>
endif

RegDisableReflectionKey proto WINAPI :HKEY
RegEnableReflectionKey proto WINAPI :HKEY
RegQueryReflectionKey proto WINAPI :HKEY, :ptr

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

RegDeleteValueA proto WINAPI :HKEY, :LPCSTR
RegDeleteValueW proto WINAPI :HKEY, :LPCWSTR
ifdef _UNICODE
define RegDeleteValue  <RegDeleteValueW>
else
define RegDeleteValue  <RegDeleteValueA>
endif

RegEnumKeyA proto WINAPI :HKEY, :DWORD, :LPSTR, :DWORD
RegEnumKeyW proto WINAPI :HKEY, :DWORD, :LPWSTR, :DWORD
ifdef _UNICODE
define RegEnumKey  <RegEnumKeyW>
else
define RegEnumKey  <RegEnumKeyA>
endif

RegEnumKeyExA proto WINAPI :HKEY, :DWORD, :LPSTR, :LPDWORD, :LPDWORD, :LPSTR, :LPDWORD, :PFILETIME
RegEnumKeyExW proto WINAPI :HKEY, :DWORD, :LPWSTR, :LPDWORD, :LPDWORD, :LPWSTR, :LPDWORD, :PFILETIME
ifdef _UNICODE
define RegEnumKeyEx  <RegEnumKeyExW>
else
define RegEnumKeyEx  <RegEnumKeyExA>
endif

RegEnumValueA proto WINAPI :HKEY, :DWORD, :LPSTR, :LPDWORD, :LPDWORD, :LPDWORD, :LPBYTE, :LPDWORD
RegEnumValueW proto WINAPI :HKEY, :DWORD, :LPWSTR, :LPDWORD, :LPDWORD, :LPDWORD, :LPBYTE, :LPDWORD
ifdef _UNICODE
define RegEnumValue  <RegEnumValueW>
else
define RegEnumValue  <RegEnumValueA>
endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)

RegFlushKey proto WINAPI :HKEY
RegGetKeySecurity proto WINAPI :HKEY, :SECURITY_INFORMATION, :PSECURITY_DESCRIPTOR, :LPDWORD
RegLoadKeyA proto WINAPI :HKEY, :LPCSTR, :LPCSTR
RegLoadKeyW proto WINAPI :HKEY, :LPCWSTR, :LPCWSTR
ifdef _UNICODE
define RegLoadKey  <RegLoadKeyW>
else
define RegLoadKey  <RegLoadKeyA>
endif

RegNotifyChangeKeyValue proto WINAPI :HKEY, :BOOL, :DWORD, :HANDLE, :BOOL

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

RegOpenKeyA proto WINAPI :HKEY, :LPCSTR, :PHKEY
RegOpenKeyW proto WINAPI :HKEY, :LPCWSTR, :PHKEY
ifdef _UNICODE
define RegOpenKey  <RegOpenKeyW>
else
define RegOpenKey  <RegOpenKeyA>
endif

RegOpenKeyExA proto WINAPI :HKEY, :LPCSTR, :DWORD, :REGSAM, :PHKEY
RegOpenKeyExW proto WINAPI :HKEY, :LPCWSTR, :DWORD, :REGSAM, :PHKEY
ifdef _UNICODE
define RegOpenKeyEx  <RegOpenKeyExW>
else
define RegOpenKeyEx  <RegOpenKeyExA>
endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)

RegOpenKeyTransactedA proto WINAPI :HKEY, :LPCSTR, :DWORD, :REGSAM, :PHKEY, :HANDLE, :PVOID
RegOpenKeyTransactedW proto WINAPI :HKEY, :LPCWSTR, :DWORD, :REGSAM, :PHKEY, :HANDLE, :PVOID
ifdef _UNICODE
define RegOpenKeyTransacted  <RegOpenKeyTransactedW>
else
define RegOpenKeyTransacted  <RegOpenKeyTransactedA>
endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

RegQueryInfoKeyA proto WINAPI :HKEY, :LPSTR, :LPDWORD, :LPDWORD, :LPDWORD, :LPDWORD, :LPDWORD, :LPDWORD, :LPDWORD, :LPDWORD, :LPDWORD, :PFILETIME
RegQueryInfoKeyW proto WINAPI :HKEY, :LPWSTR, :LPDWORD, :LPDWORD, :LPDWORD, :LPDWORD, :LPDWORD, :LPDWORD, :LPDWORD, :LPDWORD, :LPDWORD, :PFILETIME
ifdef _UNICODE
define RegQueryInfoKey  <RegQueryInfoKeyW>
else
define RegQueryInfoKey  <RegQueryInfoKeyA>
endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)

RegQueryValueA proto WINAPI :HKEY, :LPCSTR, :LPSTR, :PLONG
RegQueryValueW proto WINAPI :HKEY, :LPCWSTR, :LPWSTR, :PLONG
ifdef _UNICODE
define RegQueryValue  <RegQueryValueW>
else
define RegQueryValue  <RegQueryValueA>
endif

if(WINVER ge 0x0400)

RegQueryMultipleValuesA proto WINAPI :HKEY, :PVALENTA, :DWORD, :LPSTR, :LPDWORD
RegQueryMultipleValuesW proto WINAPI :HKEY, :PVALENTW, :DWORD, :LPWSTR, :LPDWORD
ifdef _UNICODE
define RegQueryMultipleValues  <RegQueryMultipleValuesW>
else
define RegQueryMultipleValues  <RegQueryMultipleValuesA>
endif

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

RegQueryValueExA proto WINAPI :HKEY, :LPCSTR, :LPDWORD, :LPDWORD, :LPBYTE, :LPDWORD
RegQueryValueExW proto WINAPI :HKEY, :LPCWSTR, :LPDWORD, :LPDWORD, :LPBYTE, :LPDWORD
ifdef _UNICODE
define RegQueryValueEx  <RegQueryValueExW>
else
define RegQueryValueEx  <RegQueryValueExA>
endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)

RegReplaceKeyA proto WINAPI :HKEY, :LPCSTR, :LPCSTR, :LPCSTR
RegReplaceKeyW proto WINAPI :HKEY, :LPCWSTR, :LPCWSTR, :LPCWSTR
ifdef _UNICODE
define RegReplaceKey  <RegReplaceKeyW>
else
define RegReplaceKey  <RegReplaceKeyA>
endif

RegRestoreKeyA proto WINAPI :HKEY, :LPCSTR, :DWORD
RegRestoreKeyW proto WINAPI :HKEY, :LPCWSTR, :DWORD
ifdef _UNICODE
define RegRestoreKey  <RegRestoreKeyW>
else
define RegRestoreKey  <RegRestoreKeyA>
endif

if(WINVER ge 0x0600)
RegRenameKey proto WINAPI :HKEY, :LPCWSTR, :LPCWSTR
endif

RegSaveKeyA proto WINAPI :HKEY, :LPCSTR, :LPSECURITY_ATTRIBUTES
RegSaveKeyW proto WINAPI :HKEY, :LPCWSTR, :LPSECURITY_ATTRIBUTES
ifdef _UNICODE
define RegSaveKey  <RegSaveKeyW>
else
define RegSaveKey  <RegSaveKeyA>
endif

RegSetKeySecurity proto WINAPI :HKEY, :SECURITY_INFORMATION, :PSECURITY_DESCRIPTOR

RegSetValueA proto WINAPI :HKEY, :LPCSTR, :DWORD, :LPCSTR, :DWORD
RegSetValueW proto WINAPI :HKEY, :LPCWSTR, :DWORD, :LPCWSTR, :DWORD
ifdef _UNICODE
define RegSetValue  <RegSetValueW>
else
define RegSetValue  <RegSetValueA>
endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

RegSetValueExA proto WINAPI :HKEY, :LPCSTR, :DWORD, :DWORD, :ptr, :DWORD
RegSetValueExW proto WINAPI :HKEY, :LPCWSTR, :DWORD, :DWORD, :ptr, :DWORD
ifdef _UNICODE
define RegSetValueEx  <RegSetValueExW>
else
define RegSetValueEx  <RegSetValueExA>
endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)

RegUnLoadKeyA proto WINAPI :HKEY, :LPCSTR
RegUnLoadKeyW proto WINAPI :HKEY, :LPCWSTR
ifdef _UNICODE
define RegUnLoadKey  <RegUnLoadKeyW>
else
define RegUnLoadKey  <RegUnLoadKeyA>
endif

if _WIN32_WINNT ge 0x0600

RegDeleteKeyValueA proto WINAPI :HKEY, :LPCSTR, :LPCSTR
RegDeleteKeyValueW proto WINAPI :HKEY, :LPCWSTR, :LPCWSTR
ifdef _UNICODE
define RegDeleteKeyValue  <RegDeleteKeyValueW>
else
define RegDeleteKeyValue  <RegDeleteKeyValueA>
endif

RegSetKeyValueA proto WINAPI :HKEY, :LPCSTR, :LPCSTR, :DWORD, :LPCVOID, :DWORD
RegSetKeyValueW proto WINAPI :HKEY, :LPCWSTR, :LPCWSTR, :DWORD, :LPCVOID, :DWORD
ifdef _UNICODE
define RegSetKeyValue  <RegSetKeyValueW>
else
define RegSetKeyValue  <RegSetKeyValueA>
endif

RegDeleteTreeA proto WINAPI :HKEY, :LPCSTR
RegDeleteTreeW proto WINAPI :HKEY, :LPCWSTR
ifdef _UNICODE
define RegDeleteTree  <RegDeleteTreeW>
else
define RegDeleteTree  <RegDeleteTreeA>
endif

RegCopyTreeA proto WINAPI :HKEY, :LPCSTR, :HKEY
ifndef _UNICODE
define RegCopyTree  <RegCopyTreeA>
endif

endif

if (_WIN32_WINNT ge 0x0502)

RegGetValueA proto WINAPI :HKEY, :LPCSTR, :LPCSTR, :DWORD, :LPDWORD, :PVOID, :LPDWORD
RegGetValueW proto WINAPI :HKEY, :LPCWSTR, :LPCWSTR, :DWORD, :LPDWORD, :PVOID, :LPDWORD
ifdef _UNICODE
define RegGetValue  <RegGetValueW>
else
define RegGetValue  <RegGetValueA>
endif

endif

if (_WIN32_WINNT ge 0x0600)

RegCopyTreeW proto WINAPI :HKEY, :LPCWSTR, :HKEY
ifdef _UNICODE
define RegCopyTree  <RegCopyTreeW>
endif

RegLoadMUIStringA proto WINAPI :HKEY, :LPCSTR, :LPSTR, :DWORD, :LPDWORD, :DWORD, :LPCSTR
RegLoadMUIStringW proto WINAPI :HKEY, :LPCWSTR, :LPWSTR, :DWORD, :LPDWORD, :DWORD, :LPCWSTR
ifdef _UNICODE
define RegLoadMUIString  <RegLoadMUIStringW>
else
define RegLoadMUIString  <RegLoadMUIStringA>
endif

RegLoadAppKeyA proto WINAPI :LPCSTR, :PHKEY, :REGSAM, :DWORD, :DWORD
RegLoadAppKeyW proto WINAPI :LPCWSTR, :PHKEY, :REGSAM, :DWORD, :DWORD
ifdef _UNICODE
define RegLoadAppKey  <RegLoadAppKeyW>
else
define RegLoadAppKey  <RegLoadAppKeyA>
endif

endif

InitiateSystemShutdownA proto WINAPI :LPSTR, :LPSTR, :DWORD, :BOOL, :BOOL
InitiateSystemShutdownW proto WINAPI :LPWSTR, :LPWSTR, :DWORD, :BOOL, :BOOL
ifdef _UNICODE
define InitiateSystemShutdown  <InitiateSystemShutdownW>
else
define InitiateSystemShutdown  <InitiateSystemShutdownA>
endif

AbortSystemShutdownA proto WINAPI :LPSTR
AbortSystemShutdownW proto WINAPI :LPWSTR
ifdef _UNICODE
define AbortSystemShutdown  <AbortSystemShutdownW>
else
define AbortSystemShutdown  <AbortSystemShutdownA>
endif

include reason.inc

define REASON_SWINSTALL    (SHTDN_REASON_MAJOR_SOFTWARE or SHTDN_REASON_MINOR_INSTALLATION)
define REASON_HWINSTALL    (SHTDN_REASON_MAJOR_HARDWARE or SHTDN_REASON_MINOR_INSTALLATION)
define REASON_SERVICEHANG  (SHTDN_REASON_MAJOR_SOFTWARE or SHTDN_REASON_MINOR_HUNG)
define REASON_UNSTABLE     (SHTDN_REASON_MAJOR_SYSTEM or SHTDN_REASON_MINOR_UNSTABLE)
define REASON_SWHWRECONF   (SHTDN_REASON_MAJOR_SOFTWARE or SHTDN_REASON_MINOR_RECONFIG)
define REASON_OTHER        (SHTDN_REASON_MAJOR_OTHER or SHTDN_REASON_MINOR_OTHER)
define REASON_UNKNOWN      SHTDN_REASON_UNKNOWN
define REASON_LEGACY_API   SHTDN_REASON_LEGACY_API
define REASON_PLANNED_FLAG SHTDN_REASON_FLAG_PLANNED

define MAX_SHUTDOWN_TIMEOUT (10*365*24*60*60)

InitiateSystemShutdownExA proto WINAPI :LPSTR, :LPSTR, :DWORD, :BOOL, :BOOL, :DWORD
InitiateSystemShutdownExW proto WINAPI :LPWSTR, :LPWSTR, :DWORD, :BOOL, :BOOL, :DWORD
ifdef _UNICODE
define InitiateSystemShutdownEx  <InitiateSystemShutdownExW>
else
define InitiateSystemShutdownEx  <InitiateSystemShutdownExA>
endif

define SHUTDOWN_FORCE_OTHERS           0x00000001
define SHUTDOWN_FORCE_SELF             0x00000002
define SHUTDOWN_RESTART                0x00000004
define SHUTDOWN_POWEROFF               0x00000008
define SHUTDOWN_NOREBOOT               0x00000010
define SHUTDOWN_GRACE_OVERRIDE         0x00000020
define SHUTDOWN_INSTALL_UPDATES        0x00000040
define SHUTDOWN_RESTARTAPPS            0x00000080
define SHUTDOWN_SKIP_SVC_PRESHUTDOWN   0x00000100
define SHUTDOWN_HYBRID                 0x00000200
define SHUTDOWN_RESTART_BOOTOPTIONS    0x00000400
define SHUTDOWN_SOFT_REBOOT            0x00000800
define SHUTDOWN_MOBILE_UI              0x00001000
define SHUTDOWN_ARSO                   0x00002000

InitiateShutdownA proto WINAPI :LPSTR, :LPSTR, :DWORD, :DWORD, :DWORD
InitiateShutdownW proto WINAPI :LPWSTR, :LPWSTR, :DWORD, :DWORD, :DWORD
ifdef _UNICODE
define InitiateShutdown  <InitiateShutdownW>
else
define InitiateShutdown  <InitiateShutdownA>
endif

CheckForHiberboot proto WINAPI :PBOOLEAN, :BOOLEAN

RegSaveKeyExA proto WINAPI :HKEY, :LPCSTR, :LPSECURITY_ATTRIBUTES, :DWORD
RegSaveKeyExW proto WINAPI :HKEY, :LPCWSTR, :LPSECURITY_ATTRIBUTES, :DWORD
ifdef _UNICODE
define RegSaveKeyEx  <RegSaveKeyExW>
else
define RegSaveKeyEx  <RegSaveKeyExA>
endif

endif

endif
