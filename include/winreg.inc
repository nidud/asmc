ifndef _WINREG_
_WINREG_ equ <>
;.xlist

ifdef _MAC
include macwin32.inc
endif

ifdef __PE__
option dllimport:<advapi32>
else
includelib advapi32.lib
endif

ifndef WINVER
WINVER equ 0x0500
endif

RRF_RT_REG_NONE		equ 0x00000001
RRF_RT_REG_SZ		equ 0x00000002
RRF_RT_REG_EXPAND_SZ	equ 0x00000004
RRF_RT_REG_BINARY	equ 0x00000008
RRF_RT_REG_DWORD	equ 0x00000010
RRF_RT_REG_MULTI_SZ	equ 0x00000020
RRF_RT_REG_QWORD	equ 0x00000040

RRF_RT_DWORD		equ (RRF_RT_REG_BINARY OR RRF_RT_REG_DWORD)
RRF_RT_QWORD		equ (RRF_RT_REG_BINARY OR RRF_RT_REG_QWORD)
RRF_RT_ANY		equ 0x0000ffff

RRF_NOEXPAND		equ 0x10000000
RRF_ZEROONFAILURE	equ 0x20000000
REG_PROCESS_APPKEY	equ 0x00000001
REG_MUI_STRING_TRUNCATE equ 0x00000001

REGSAM			typedef ACCESS_MASK
HKEY			typedef HANDLE

HKEY_CLASSES_ROOT	equ 0x80000000
HKEY_CURRENT_USER	equ 0x80000001
HKEY_LOCAL_MACHINE	equ 0x80000002
HKEY_USERS		equ 0x80000003
HKEY_PERFORMANCE_DATA	equ 0x80000004
HKEY_PERFORMANCE_TEXT	equ 0x80000050
HKEY_PERFORMANCE_NLSTEXT equ 0x80000060
if(WINVER GE 0x0400)
HKEY_CURRENT_CONFIG	equ 0x80000005
HKEY_DYN_DATA		equ 0x80000006
HKEY_CURRENT_USER_LOCAL_SETTINGS equ 0x80000007

REG_SECURE_CONNECTION	equ 1

ifndef _PROVIDER_STRUCTS_DEFINED
_PROVIDER_STRUCTS_DEFINED equ <>

PROVIDER_KEEPS_VALUE_LENGTH equ 0x1
val_context		STRUC
valuelen		SINT ?
value_context		PVOID ?
val_buff_ptr		PVOID ?
val_context		ENDS

PVALCONTEXT		typedef ptr val_context

PVALUEA			STRUC
pv_valuename		LPSTR ?
pv_valuelen		SINT ?
pv_value_context	PVOID ?
pv_type			dd ?
PVALUEA			ENDS
PPVALUEA		typedef ptr PVALUEA
PVALUEW			STRUC
pv_valuename		LPWSTR ?	;; The value name pointer
pv_valuelen		SINT ?
pv_value_context	PVOID ?
pv_type			dd ?
PVALUEW			ENDS
PPVALUEW		typedef ptr PVALUEW
ifdef _UNICODE
PVALUE			typedef PVALUEW
PPVALUE			typedef PPVALUEW
else
PVALUE			typedef PVALUEA
PPVALUE			typedef PPVALUEA
endif

CALLBACK(PQUERYHANDLER, :PVOID, :PVALCONTEXT, :DWORD, :PVOID, :DWORD)

REG_PROVIDER		STRUC
pi_R0_1val		PQUERYHANDLER ?
pi_R0_allvals		PQUERYHANDLER ?
pi_R3_1val		PQUERYHANDLER ?
pi_R3_allvals		PQUERYHANDLER ?
pi_flags		dd ?
pi_key_context		PVOID ?
REG_PROVIDER		ENDS
PPROVIDER		typedef ptr REG_PROVIDER

VALENTA			STRUC
ve_valuename		LPSTR ?
ve_valuelen		dd ?
ve_valueptr		dd ?
ve_type			dd ?
VALENTA			ENDS
PVALENTA		typedef ptr VALENTA
VALENTW			STRUC
ve_valuename		LPWSTR ?
ve_valuelen		dd ?
ve_valueptr		dd ?
ve_type			dd ?
VALENTW			ENDS
PVALENTW		typedef ptr VALENTW
ifdef _UNICODE
VALENT			typedef VALENTW
PVALENT			typedef PVALENTW
else
VALENT			typedef VALENTA
PVALENT			typedef PVALENTA
endif ;; _UNICODE
endif ;; not(_PROVIDER_STRUCTS_DEFINED)
endif ;; WINVER GE 0x0400

WIN31_CLASS		equ NULL

;WINADVAPI
;LSTATUS		equ __success(return==ERROR_SUCCESS)
;APIENTRY
PHKEY			typedef ptr HKEY

RegCloseKey proto WINAPI \
		  hKey: HKEY

RegOverridePredefKey proto WINAPI \
		  hKey: HKEY,
	      hNewHKey: HKEY

RegOpenUserClassesRoot proto WINAPI \
		hToken: HANDLE,
	     dwOptions: DWORD,
	    samDesired: REGSAM,
	     phkResult: PHKEY

RegOpenCurrentUser proto WINAPI \
	    samDesired: REGSAM,
	     phkResult: PHKEY

RegDisablePredefinedCache proto WINAPI
RegDisablePredefinedCacheEx proto WINAPI

RegConnectRegistryA proto WINAPI \
	 lpMachineName: LPCSTR,
		  hKey: HKEY,
	     phkResult: PHKEY
RegConnectRegistryW proto WINAPI \
	 lpMachineName: LPCWSTR,
		  hKey: HKEY,
	     phkResult: PHKEY
ifdef _UNICODE
RegConnectRegistry	equ <RegConnectRegistryW>
else
RegConnectRegistry	equ <RegConnectRegistryA>
endif

RegConnectRegistryExA proto WINAPI \
	 lpMachineName: LPCSTR,
		  hKey: HKEY,
		 Flags: ULONG,
	     phkResult: PHKEY
RegConnectRegistryExW proto WINAPI \
	 lpMachineName: LPCWSTR,
		  hKey: HKEY,
		 Flags: ULONG,
	     phkResult: PHKEY
ifdef _UNICODE
RegConnectRegistryEx	equ <RegConnectRegistryExW>
else
RegConnectRegistryEx	equ <RegConnectRegistryExA>
endif

RegCreateKeyA proto WINAPI \
		  hKey: HKEY,
	      lpSubKey: LPCSTR,
	     phkResult: PHKEY
RegCreateKeyW proto WINAPI \
		  hKey: HKEY,
	      lpSubKey: LPCWSTR,
	     phkResult: PHKEY
ifdef _UNICODE
RegCreateKey		equ <RegCreateKeyW>
else
RegCreateKey		equ <RegCreateKeyA>
endif

RegCreateKeyExA proto WINAPI \
		  hKey: HKEY,
	      lpSubKey: LPCSTR,
	      Reserved: DWORD,
	       lpClass: LPSTR,
	     dwOptions: DWORD,
	    samDesired: REGSAM,
  lpSecurityAttributes: LPSECURITY_ATTRIBUTES,
	     phkResult: PHKEY,
       lpdwDisposition: LPDWORD
RegCreateKeyExW proto WINAPI \
		  hKey: HKEY,
	      lpSubKey: LPCWSTR,
	      Reserved: DWORD,
	       lpClass: LPWSTR,
	     dwOptions: DWORD,
	    samDesired: REGSAM,
  lpSecurityAttributes: LPSECURITY_ATTRIBUTES,
	     phkResult: PHKEY,
       lpdwDisposition: LPDWORD
ifdef _UNICODE
RegCreateKeyEx		equ <RegCreateKeyExW>
else
RegCreateKeyEx		equ <RegCreateKeyExA>
endif

RegCreateKeyTransactedA proto WINAPI \
		  hKey: HKEY,
	      lpSubKey: LPCSTR,
	      Reserved: DWORD,
	       lpClass: LPSTR,
	     dwOptions: DWORD,
	    samDesired: REGSAM,
  lpSecurityAttributes: LPSECURITY_ATTRIBUTES,
	     phkResult: PHKEY,
       lpdwDisposition: LPDWORD,
	  hTransaction: HANDLE,
    pExtendedParemeter: PVOID
RegCreateKeyTransactedW proto WINAPI \
		  hKey: HKEY,
	      lpSubKey: LPCWSTR,
	      Reserved: DWORD,
	       lpClass: LPWSTR,
	     dwOptions: DWORD,
	    samDesired: REGSAM,
  lpSecurityAttributes: LPSECURITY_ATTRIBUTES,
	     phkResult: PHKEY,
       lpdwDisposition: LPDWORD,
	  hTransaction: HANDLE,
    pExtendedParemeter: PVOID
ifdef _UNICODE
RegCreateKeyTransacted	equ <RegCreateKeyTransactedW>
else
RegCreateKeyTransacted	equ <RegCreateKeyTransactedA>
endif

RegDeleteKeyA proto WINAPI \
		  hKey: HKEY,
	      lpSubKey: LPCSTR
RegDeleteKeyW proto WINAPI \
		  hKey: HKEY,
	      lpSubKey: LPCWSTR
ifdef _UNICODE
RegDeleteKey		equ <RegDeleteKeyW>
else
RegDeleteKey		equ <RegDeleteKeyA>
endif

RegDeleteKeyExA proto WINAPI \
		  hKey: HKEY,
	      lpSubKey: LPCSTR,
	    samDesired: REGSAM,
	      Reserved: DWORD
RegDeleteKeyExW proto WINAPI \
		  hKey: HKEY,
	      lpSubKey: LPCWSTR,
	    samDesired: REGSAM,
	      Reserved: DWORD
ifdef _UNICODE
RegDeleteKeyEx		equ <RegDeleteKeyExW>
else
RegDeleteKeyEx		equ <RegDeleteKeyExA>
endif

RegDeleteKeyTransactedA proto WINAPI \
		  hKey: HKEY,
	      lpSubKey: LPCSTR,
	    samDesired: REGSAM,
	      Reserved: DWORD,
	  hTransaction: HANDLE,
    pExtendedParameter: PVOID
RegDeleteKeyTransactedW proto WINAPI \
		  hKey: HKEY,
	      lpSubKey: LPCWSTR,
	    samDesired: REGSAM,
	      Reserved: DWORD,
	  hTransaction: HANDLE,
    pExtendedParameter: PVOID
ifdef _UNICODE
RegDeleteKeyTransacted	equ <RegDeleteKeyTransactedW>
else
RegDeleteKeyTransacted	equ <RegDeleteKeyTransactedA>
endif

RegDisableReflectionKey proto WINAPI \
		 hBase: HKEY
RegEnableReflectionKey proto WINAPI \
		 hBase: HKEY
RegQueryReflectionKey proto WINAPI \
		 hBase: HKEY,
 bIsReflectionDisabled: ptr BOOL


RegDeleteValueA proto WINAPI \
		  hKey: HKEY,
	   lpValueName: LPCSTR
RegDeleteValueW proto WINAPI \
		  hKey: HKEY,
	   lpValueName: LPCWSTR
ifdef _UNICODE
RegDeleteValue		equ <RegDeleteValueW>
else
RegDeleteValue		equ <RegDeleteValueA>
endif

RegEnumKeyA proto WINAPI \
		  hKey: HKEY,
	       dwIndex: DWORD,
		lpName: LPSTR,
	       cchName: DWORD
RegEnumKeyW proto WINAPI \
		  hKey: HKEY,
	       dwIndex: DWORD,
		lpName: LPWSTR,
	       cchName: DWORD
ifdef _UNICODE
RegEnumKey		equ <RegEnumKeyW>
else
RegEnumKey		equ <RegEnumKeyA>
endif

RegEnumKeyExA proto WINAPI \
		  hKey: HKEY,
	       dwIndex: DWORD,
		lpName: LPSTR,
	     lpcchName: LPDWORD,
	    lpReserved: LPDWORD,
	       lpClass: LPSTR,
	    lpcchClass: LPDWORD,
     lpftLastWriteTime: PFILETIME
RegEnumKeyExW proto WINAPI \
		  hKey: HKEY,
	       dwIndex: DWORD,
		lpName: LPWSTR,
	     lpcchName: LPDWORD,
	    lpReserved: LPDWORD,
	       lpClass: LPWSTR,
	    lpcchClass: LPDWORD,
     lpftLastWriteTime: PFILETIME
ifdef _UNICODE
RegEnumKeyEx		equ <RegEnumKeyExW>
else
RegEnumKeyEx		equ <RegEnumKeyExA>
endif

RegEnumValueA proto WINAPI \
		  hKey: HKEY,
	       dwIndex: DWORD,
	   lpValueName: LPSTR,
	lpcchValueName: LPDWORD,
	    lpReserved: LPDWORD,
		lpType: LPDWORD,
		lpData: LPBYTE,
	      lpcbData: LPDWORD
RegEnumValueW proto WINAPI \
		  hKey: HKEY,
	       dwIndex: DWORD,
	   lpValueName: LPWSTR,
	lpcchValueName: LPDWORD,
	    lpReserved: LPDWORD,
		lpType: LPDWORD,
		lpData: LPBYTE,
	      lpcbData: LPDWORD
ifdef _UNICODE
RegEnumValue		equ <RegEnumValueW>
else
RegEnumValue		equ <RegEnumValueA>
endif

RegFlushKey proto WINAPI  \
		  hKey: HKEY

RegGetKeySecurity proto WINAPI \
		  hKey: HKEY,
   SecurityInformation: SECURITY_INFORMATION,
   pSecurityDescriptor: PSECURITY_DESCRIPTOR,
lpcbSecurityDescriptor: LPDWORD

RegLoadKeyA proto WINAPI \
		  hKey: HKEY,
	      lpSubKey: LPCSTR,
		lpFile: LPCSTR
RegLoadKeyW proto WINAPI \
		  hKey: HKEY,
	      lpSubKey: LPCWSTR,
		lpFile: LPCWSTR
ifdef _UNICODE
RegLoadKey		equ <RegLoadKeyW>
else
RegLoadKey		equ <RegLoadKeyA>
endif

RegNotifyChangeKeyValue proto WINAPI \
		  hKey: HKEY,
	 bWatchSubtree: BOOL,
	dwNotifyFilter: DWORD,
		hEvent: HANDLE,
	 fAsynchronous: BOOL

RegOpenKeyA proto WINAPI \
		  hKey: HKEY,
	      lpSubKey: LPCSTR,
	     phkResult: PHKEY
RegOpenKeyW proto WINAPI \
		  hKey: HKEY,
	      lpSubKey: LPCWSTR,
	     phkResult: PHKEY
ifdef _UNICODE
RegOpenKey		equ <RegOpenKeyW>
else
RegOpenKey		equ <RegOpenKeyA>
endif

RegOpenKeyExA proto WINAPI \
		  hKey: HKEY,
	      lpSubKey: LPCSTR,
	     ulOptions: DWORD,
	    samDesired: REGSAM,
	     phkResult: PHKEY
RegOpenKeyExW proto WINAPI \
		  hKey: HKEY,
	      lpSubKey: LPCWSTR,
	     ulOptions: DWORD,
	    samDesired: REGSAM,
	     phkResult: PHKEY
ifdef _UNICODE
RegOpenKeyEx		equ <RegOpenKeyExW>
else
RegOpenKeyEx		equ <RegOpenKeyExA>
endif

RegOpenKeyTransactedA proto WINAPI \
		  hKey: HKEY,
	      lpSubKey: LPCSTR,
	     ulOptions: DWORD,
	    samDesired: REGSAM,
	     phkResult: PHKEY,
	  hTransaction: HANDLE,
    pExtendedParemeter: PVOID
RegOpenKeyTransactedW proto WINAPI \
		  hKey: HKEY,
	      lpSubKey: LPCWSTR,
	     ulOptions: DWORD,
	    samDesired: REGSAM,
	     phkResult: PHKEY,
	  hTransaction: HANDLE,
    pExtendedParemeter: PVOID
ifdef _UNICODE
RegOpenKeyTransacted	equ <RegOpenKeyTransactedW>
else
RegOpenKeyTransacted	equ <RegOpenKeyTransactedA>
endif

RegQueryInfoKeyA proto WINAPI \
		  hKey: HKEY,
	       lpClass: LPSTR,
	    lpcchClass: LPDWORD,
	    lpReserved: LPDWORD,
	    lpcSubKeys: LPDWORD,
      lpcbMaxSubKeyLen: LPDWORD,
       lpcbMaxClassLen: LPDWORD,
	     lpcValues: LPDWORD,
   lpcbMaxValueNameLen: LPDWORD,
       lpcbMaxValueLen: LPDWORD,
lpcbSecurityDescriptor: LPDWORD,
     lpftLastWriteTime: PFILETIME
RegQueryInfoKeyW proto WINAPI \
		  hKey: HKEY,
	       lpClass: LPWSTR,
	    lpcchClass: LPDWORD,
	    lpReserved: LPDWORD,
	    lpcSubKeys: LPDWORD,
      lpcbMaxSubKeyLen: LPDWORD,
       lpcbMaxClassLen: LPDWORD,
	     lpcValues: LPDWORD,
   lpcbMaxValueNameLen: LPDWORD,
       lpcbMaxValueLen: LPDWORD,
lpcbSecurityDescriptor: LPDWORD,
     lpftLastWriteTime: PFILETIME
ifdef _UNICODE
RegQueryInfoKey		equ <RegQueryInfoKeyW>
else
RegQueryInfoKey		equ <RegQueryInfoKeyA>
endif

RegQueryValueA proto WINAPI \
		  hKey: HKEY,
	      lpSubKey: LPCSTR,
		lpData: LPSTR,
	      lpcbData: PLONG
RegQueryValueW proto WINAPI \
		  hKey: HKEY,
	      lpSubKey: LPCWSTR,
		lpData: LPWSTR,
	      lpcbData: PLONG
ifdef _UNICODE
RegQueryValue		equ <RegQueryValueW>
else
RegQueryValue		equ <RegQueryValueA>
endif

if(WINVER GE 0x0400)

RegQueryMultipleValuesA proto WINAPI \
		  hKey: HKEY,
	      val_list: PVALENTA,
	      num_vals: DWORD,
	    lpValueBuf: LPSTR,
	    ldwTotsize: LPDWORD
RegQueryMultipleValuesW proto WINAPI \
		  hKey: HKEY,
	      val_list: PVALENTA,
	      num_vals: DWORD,
	    lpValueBuf: LPWSTR,
	    ldwTotsize: LPDWORD
ifdef _UNICODE
RegQueryMultipleValues	equ <RegQueryMultipleValuesW>
else
RegQueryMultipleValues	equ <RegQueryMultipleValuesA>
endif

endif ;; WINVER GE 0x0400

RegQueryValueExA proto WINAPI \
		  hKey: HKEY,
	   lpValueName: LPCSTR,
	    lpReserved: LPDWORD,
		lpType: LPDWORD,
		lpData: LPBYTE,
	      lpcbData: LPDWORD
RegQueryValueExW proto WINAPI \
		  hKey: HKEY,
	   lpValueName: LPCWSTR,
	    lpReserved: LPDWORD,
		lpType: LPDWORD,
		lpData: LPBYTE,
	      lpcbData: LPDWORD
ifdef _UNICODE
RegQueryValueEx		equ <RegQueryValueExW>
else
RegQueryValueEx		equ <RegQueryValueExA>
endif

RegReplaceKeyA proto WINAPI \
		  hKey: HKEY,
	      lpSubKey: LPCSTR,
	     lpNewFile: LPCSTR,
	     lpOldFile: LPCSTR
RegReplaceKeyW proto WINAPI \
		  hKey: HKEY,
	      lpSubKey: LPCWSTR,
	     lpNewFile: LPCWSTR,
	     lpOldFile: LPCWSTR
ifdef _UNICODE
RegReplaceKey		equ <RegReplaceKeyW>
else
RegReplaceKey		equ <RegReplaceKeyA>
endif

RegRestoreKeyA proto WINAPI \
		  hKey: HKEY,
		lpFile: LPCSTR,
	       dwFlags: DWORD
RegRestoreKeyW proto WINAPI \
		  hKey: HKEY,
		lpFile: LPCWSTR,
	       dwFlags: DWORD
ifdef _UNICODE
RegRestoreKey		equ <RegRestoreKeyW>
else
RegRestoreKey		equ <RegRestoreKeyA>
endif

if(WINVER GE 0x0600)

RegRenameKey proto WINAPI \
		  hKey: HKEY,
	  lpSubKeyName: LPCWSTR,
	  lpNewKeyName: LPCWSTR

endif ;; WINVER GE 0x0600

RegSaveKeyA proto WINAPI \
		  hKey: HKEY,
		lpFile: LPCSTR,
  lpSecurityAttributes: LPSECURITY_ATTRIBUTES
RegSaveKeyW proto WINAPI \
		  hKey: HKEY,
		lpFile: LPCWSTR,
  lpSecurityAttributes: LPSECURITY_ATTRIBUTES
ifdef _UNICODE
RegSaveKey		equ <RegSaveKeyW>
else
RegSaveKey		equ <RegSaveKeyA>
endif

RegSetKeySecurity proto WINAPI \
		  hKey: HKEY,
   SecurityInformation: SECURITY_INFORMATION,
   pSecurityDescriptor: PSECURITY_DESCRIPTOR

RegSetValueA proto WINAPI \
		  hKey: HKEY,
	      lpSubKey: LPCSTR,
		dwType: DWORD,
		lpData: LPCSTR,
		cbData: DWORD
RegSetValueW proto WINAPI \
		  hKey: HKEY,
	      lpSubKey: LPCWSTR,
		dwType: DWORD,
		lpData: LPCWSTR,
		cbData: DWORD
ifdef _UNICODE
RegSetValue		equ <RegSetValueW>
else
RegSetValue		equ <RegSetValueA>
endif


RegSetValueExA proto WINAPI \
		  hKey: HKEY,
	   lpValueName: LPCSTR,
	      Reserved: DWORD,
		dwType: DWORD,
		lpData: LPBYTE,
		cbData: DWORD
RegSetValueExW proto WINAPI \
		  hKey: HKEY,
	   lpValueName: LPCWSTR,
	      Reserved: DWORD,
		dwType: DWORD,
		lpData: LPBYTE,
		cbData: DWORD
ifdef _UNICODE
RegSetValueEx		equ <RegSetValueExW>
else
RegSetValueEx		equ <RegSetValueExA>
endif

RegUnLoadKeyA proto WINAPI \
		  hKey: HKEY,
	      lpSubKey: LPCSTR
RegUnLoadKeyW proto WINAPI \
		  hKey: HKEY,
	      lpSubKey: LPCWSTR
ifdef _UNICODE
RegUnLoadKey		equ <RegUnLoadKeyW>
else
RegUnLoadKey		equ <RegUnLoadKeyA>
endif

if _WIN32_WINNT GE 0x0600

RegDeleteKeyValueA proto WINAPI \
		  hKey: HKEY,
	      lpSubKey: LPCSTR,
	   lpValueName: LPCSTR
RegDeleteKeyValueW proto WINAPI \
		  hKey: HKEY,
	      lpSubKey: LPCWSTR,
	   lpValueName: LPCWSTR
ifdef _UNICODE
RegDeleteKeyValue	equ <RegDeleteKeyValueW>
else
RegDeleteKeyValue	equ <RegDeleteKeyValueA>
endif

RegSetKeyValueA proto WINAPI \
		  hKey: HKEY,
	      lpSubKey: LPCSTR,
	   lpValueName: LPCSTR,
		dwType: DWORD,
		lpData: LPCVOID,
		cbData: DWORD
RegSetKeyValueW proto WINAPI \
		  hKey: HKEY,
	      lpSubKey: LPCWSTR,
	   lpValueName: LPCWSTR,
		dwType: DWORD,
		lpData: LPCVOID,
		cbData: DWORD
ifdef _UNICODE
RegSetKeyValue		equ <RegSetKeyValueW>
else
RegSetKeyValue		equ <RegSetKeyValueA>
endif

RegDeleteTreeA proto WINAPI \
		  hKey: HKEY,
	      lpSubKey: LPCSTR
RegDeleteTreeW proto WINAPI \
		  hKey: HKEY,
	      lpSubKey: LPCWSTR
ifdef _UNICODE
RegDeleteTree		equ <RegDeleteTreeW>
else
RegDeleteTree		equ <RegDeleteTreeA>
endif

RegCopyTreeA proto WINAPI \
	       hKeySrc: HKEY,
	      lpSubKey: LPCSTR,
	      hKeyDest: HKEY
RegCopyTreeW proto WINAPI \
	       hKeySrc: HKEY,
	      lpSubKey: LPCWSTR,
	      hKeyDest: HKEY
ifdef _UNICODE
RegCopyTree		equ <RegCopyTreeW>
else
RegCopyTree		equ <RegCopyTreeA>
endif

RegGetValueA proto WINAPI \
		  hKey: HKEY,
	      lpSubKey: LPCSTR,
	       lpValue: LPCSTR,
	       dwFlags: DWORD,
	       pdwType: LPDWORD,
		pvData: PVOID,
	       pcbData: LPDWORD
RegGetValueW proto WINAPI \
		  hKey: HKEY,
	      lpSubKey: LPCWSTR,
	       lpValue: LPCWSTR,
	       dwFlags: DWORD,
	       pdwType: LPDWORD,
		pvData: PVOID,
	       pcbData: LPDWORD
ifdef _UNICODE
RegGetValue		equ <RegGetValueW>
else
RegGetValue		equ <RegGetValueA>
endif

RegLoadMUIStringA proto WINAPI \
		  hKey: HKEY,
	      pszValue: LPCSTR,
	     pszOutBuf: LPSTR,
	      cbOutBuf: DWORD,
	       pcbData: LPDWORD,
		 Flags: DWORD,
	  pszDirectory: LPCSTR
RegLoadMUIStringW proto WINAPI \
		  hKey: HKEY,
	      pszValue: LPCWSTR,
	     pszOutBuf: LPWSTR,
	      cbOutBuf: DWORD,
	       pcbData: LPDWORD,
		 Flags: DWORD,
	  pszDirectory: LPCWSTR
ifdef _UNICODE
RegLoadMUIString	equ <RegLoadMUIStringW>
else
RegLoadMUIString	equ <RegLoadMUIStringA>
endif


RegLoadAppKeyA proto WINAPI \
		lpFile: LPCSTR,
	     phkResult: PHKEY,
	    samDesired: REGSAM,
	     dwOptions: DWORD,
	      Reserved: DWORD
RegLoadAppKeyW proto WINAPI \
		lpFile: LPCWSTR,
	     phkResult: PHKEY,
	    samDesired: REGSAM,
	     dwOptions: DWORD,
	      Reserved: DWORD
ifdef _UNICODE
RegLoadAppKey		equ <RegLoadAppKeyW>
else
RegLoadAppKey		equ <RegLoadAppKeyA>
endif

endif ;; _WIN32_WINNT GE 0x0600

;BOOL
InitiateSystemShutdownA proto WINAPI \
	 lpMachineName: LPSTR,
	     lpMessage: LPSTR,
	     dwTimeout: DWORD,
      bForceAppsClosed: BOOL,
  bRebootAfterShutdown: BOOL
InitiateSystemShutdownW proto WINAPI \
	 lpMachineName: LPWSTR,
	     lpMessage: LPWSTR,
	     dwTimeout: DWORD,
      bForceAppsClosed: BOOL,
  bRebootAfterShutdown: BOOL

ifdef _UNICODE
InitiateSystemShutdown	equ <InitiateSystemShutdownW>
else
InitiateSystemShutdown	equ <InitiateSystemShutdownA>
endif

AbortSystemShutdownA proto WINAPI \
	 lpMachineName: LPSTR

AbortSystemShutdownW proto WINAPI \
	 lpMachineName: LPWSTR

ifdef _UNICODE
AbortSystemShutdown	equ <AbortSystemShutdownW>
else
AbortSystemShutdown	equ <AbortSystemShutdownA>
endif

include reason.inc

REASON_SWINSTALL	equ (SHTDN_REASON_MAJOR_SOFTWARE OR SHTDN_REASON_MINOR_INSTALLATION)
REASON_HWINSTALL	equ (SHTDN_REASON_MAJOR_HARDWARE OR SHTDN_REASON_MINOR_INSTALLATION)
REASON_SERVICEHANG	equ (SHTDN_REASON_MAJOR_SOFTWARE OR SHTDN_REASON_MINOR_HUNG)
REASON_UNSTABLE		equ (SHTDN_REASON_MAJOR_SYSTEM OR SHTDN_REASON_MINOR_UNSTABLE)
REASON_SWHWRECONF	equ (SHTDN_REASON_MAJOR_SOFTWARE OR SHTDN_REASON_MINOR_RECONFIG)
REASON_OTHER		equ (SHTDN_REASON_MAJOR_OTHER OR SHTDN_REASON_MINOR_OTHER)
REASON_UNKNOWN		equ SHTDN_REASON_UNKNOWN
REASON_LEGACY_API	equ SHTDN_REASON_LEGACY_API
REASON_PLANNED_FLAG	equ SHTDN_REASON_FLAG_PLANNED

MAX_SHUTDOWN_TIMEOUT	equ (10*365*24*60*60)

;BOOL
InitiateSystemShutdownExA proto WINAPI \
	 lpMachineName: LPSTR,
	     lpMessage: LPSTR,
	     dwTimeout: DWORD,
      bForceAppsClosed: BOOL,
  bRebootAfterShutdown: BOOL,
	      dwReason: DWORD
InitiateSystemShutdownExW proto WINAPI \
	 lpMachineName: LPWSTR,
	     lpMessage: LPWSTR,
	     dwTimeout: DWORD,
      bForceAppsClosed: BOOL,
  bRebootAfterShutdown: BOOL,
	      dwReason: DWORD
ifdef _UNICODE
InitiateSystemShutdownEx equ <InitiateSystemShutdownExW>
else
InitiateSystemShutdownEx equ <InitiateSystemShutdownExA>
endif


SHUTDOWN_FORCE_OTHERS	equ 0x00000001
SHUTDOWN_FORCE_SELF	equ 0x00000002
SHUTDOWN_RESTART	equ 0x00000004
SHUTDOWN_POWEROFF	equ 0x00000008
SHUTDOWN_NOREBOOT	equ 0x00000010
SHUTDOWN_GRACE_OVERRIDE equ 0x00000020
SHUTDOWN_INSTALL_UPDATES equ 0x00000040
SHUTDOWN_RESTARTAPPS	equ 0x00000080
SHUTDOWN_SKIP_SVC_PRESHUTDOWN equ 0x00000100


;DWORD
InitiateShutdownA proto WINAPI \
	 lpMachineName: LPSTR,
	     lpMessage: LPSTR,
	 dwGracePeriod: DWORD,
       dwShutdownFlags: DWORD,
	      dwReason: DWORD
InitiateShutdownW proto WINAPI \
	 lpMachineName: LPWSTR,
	     lpMessage: LPWSTR,
	 dwGracePeriod: DWORD,
       dwShutdownFlags: DWORD,
	      dwReason: DWORD
ifdef _UNICODE
InitiateShutdown	equ <InitiateShutdownW>
else
InitiateShutdown	equ <InitiateShutdownA>
endif

RegSaveKeyExA proto WINAPI \
		  hKey: HKEY,
		lpFile: LPCSTR,
  lpSecurityAttributes: LPSECURITY_ATTRIBUTES,
		 Flags: DWORD
RegSaveKeyExW proto WINAPI \
		  hKey: HKEY,
		lpFile: LPCWSTR,
  lpSecurityAttributes: LPSECURITY_ATTRIBUTES,
		 Flags: DWORD
ifdef _UNICODE
RegSaveKeyEx		equ <RegSaveKeyExW>
else
RegSaveKeyEx		equ <RegSaveKeyExA>
endif

 ;.list
endif ;; _WINREG_
