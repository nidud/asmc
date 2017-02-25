;
; Header file for the Service Control Manager
;
ifndef __LIBC_INC
 include libc.inc
endif
ifndef _WINDEF_
 include windef.inc
endif

.xlist
ifndef _WINSVC_
_WINSVC_ equ 1

;;
;; Define API decoration for direct importing of DLL references.
;;

ifdef __PE__
option dllimport:<advapi32>
endif

;;
;; Constants
;;

;;
;; Service database names
;;

SERVICES_ACTIVE_DATABASE equ <"ServicesActive">
SERVICES_FAILED_DATABASE equ <"ServicesFailed">

;;
;; Character to designate that a name is a group
;;

SC_GROUP_IDENTIFIER	equ '+'

;;
;; Value to indicate no change to an optional parameter
;;
SERVICE_NO_CHANGE	equ 0xffffffff

;;
;; Service State -- for Enum Requests (Bit Mask)
;;
SERVICE_ACTIVE		equ 0x00000001
SERVICE_INACTIVE	equ 0x00000002
SERVICE_STATE_ALL	equ SERVICE_ACTIVE OR SERVICE_INACTIVE

;;
;; Controls
;;
SERVICE_CONTROL_STOP		equ 0x00000001
SERVICE_CONTROL_PAUSE		equ 0x00000002
SERVICE_CONTROL_CONTINUE	equ 0x00000003
SERVICE_CONTROL_INTERROGATE	equ 0x00000004
SERVICE_CONTROL_SHUTDOWN	equ 0x00000005
SERVICE_CONTROL_PARAMCHANGE	equ 0x00000006
SERVICE_CONTROL_NETBINDADD	equ 0x00000007
SERVICE_CONTROL_NETBINDREMOVE	equ 0x00000008
SERVICE_CONTROL_NETBINDENABLE	equ 0x00000009
SERVICE_CONTROL_NETBINDDISABLE	equ 0x0000000A

;;
;; Service State -- for CurrentState
;;
SERVICE_STOPPED			equ 0x00000001
SERVICE_START_PENDING		equ 0x00000002
SERVICE_STOP_PENDING		equ 0x00000003
SERVICE_RUNNING			equ 0x00000004
SERVICE_CONTINUE_PENDING	equ 0x00000005
SERVICE_PAUSE_PENDING		equ 0x00000006
SERVICE_PAUSED			equ 0x00000007

;;
;; Controls Accepted  (Bit Mask)
;;
SERVICE_ACCEPT_STOP		equ 0x00000001
SERVICE_ACCEPT_PAUSE_CONTINUE	equ 0x00000002
SERVICE_ACCEPT_SHUTDOWN		equ 0x00000004
SERVICE_ACCEPT_PARAMCHANGE	equ 0x00000008
SERVICE_ACCEPT_NETBINDCHANGE	equ 0x00000010

;;
;; Service Control Manager object specific access types
;;
SC_MANAGER_CONNECT		equ 0x0001
SC_MANAGER_CREATE_SERVICE	equ 0x0002
SC_MANAGER_ENUMERATE_SERVICE	equ 0x0004
SC_MANAGER_LOCK			equ 0x0008
SC_MANAGER_QUERY_LOCK_STATUS	equ 0x0010
SC_MANAGER_MODIFY_BOOT_CONFIG	equ 0x0020

SC_MANAGER_ALL_ACCESS		equ STANDARD_RIGHTS_REQUIRED OR \
				SC_MANAGER_CONNECT OR \
				SC_MANAGER_CREATE_SERVICE OR \
				SC_MANAGER_ENUMERATE_SERVICE OR \
				SC_MANAGER_LOCK OR \
				SC_MANAGER_QUERY_LOCK_STATUS OR \
				SC_MANAGER_MODIFY_BOOT_CONFIG

;;
;; Service object specific access type
;;
SERVICE_QUERY_CONFIG		equ 0x0001
SERVICE_CHANGE_CONFIG		equ 0x0002
SERVICE_QUERY_STATUS		equ 0x0004
SERVICE_ENUMERATE_DEPENDENTS	equ 0x0008
SERVICE_START			equ 0x0010
SERVICE_STOP			equ 0x0020
SERVICE_PAUSE_CONTINUE		equ 0x0040
SERVICE_INTERROGATE		equ 0x0080
SERVICE_USER_DEFINED_CONTROL	equ 0x0100

SERVICE_ALL_ACCESS		equ STANDARD_RIGHTS_REQUIRED OR \
				SERVICE_QUERY_CONFIG OR \
				SERVICE_CHANGE_CONFIG OR \
				SERVICE_QUERY_STATUS OR \
				SERVICE_ENUMERATE_DEPENDENTS OR \
				SERVICE_START OR \
				SERVICE_STOP OR \
				SERVICE_PAUSE_CONTINUE OR \
				SERVICE_INTERROGATE OR \
				SERVICE_USER_DEFINED_CONTROL


;;
;; Info levels for ChangeServiceConfig2 and QueryServiceConfig2
;;
SERVICE_CONFIG_DESCRIPTION	equ 1
SERVICE_CONFIG_FAILURE_ACTIONS	equ 2

;;
;; Service description string
;;
SERVICE_DESCRIPTIONA	STRUC
lpDescription		LPSTR ?
SERVICE_DESCRIPTIONA	ENDS
LPSERVICE_DESCRIPTIONA	typedef ptr SERVICE_DESCRIPTIONA
;;
;; Service description string
;;
SERVICE_DESCRIPTIONW	STRUC
lpDescription		LPWSTR ?
SERVICE_DESCRIPTIONW	ENDS
LPSERVICE_DESCRIPTIONW	typedef ptr SERVICE_DESCRIPTIONW
ifdef _UNICODE
SERVICE_DESCRIPTION	typedef SERVICE_DESCRIPTIONW
LPSERVICE_DESCRIPTION	typedef LPSERVICE_DESCRIPTIONW
else
SERVICE_DESCRIPTION	typedef SERVICE_DESCRIPTIONA
LPSERVICE_DESCRIPTION	typedef LPSERVICE_DESCRIPTIONA
endif ;; UNICODE

;;
;; Actions to take on service failure
;;

SC_ACTION_NONE		equ 0
SC_ACTION_RESTART	equ 1
SC_ACTION_REBOOT	equ 2
SC_ACTION_RUN_COMMAND	equ 3
SC_ACTION_TYPE		typedef DWORD

SC_ACTION		STRUC
_Type			SC_ACTION_TYPE ?
Delay			dd ?
SC_ACTION		ENDS
LPSC_ACTION		typedef ptr SC_ACTION

SERVICE_FAILURE_ACTIONSA STRUC
dwResetPeriod		dd ?
lpRebootMsg		LPSTR ?
lpCommand		LPSTR ?
cActions		dd ?
lpsaActions		LPSC_ACTION ?
SERVICE_FAILURE_ACTIONSA ENDS
LPSERVICE_FAILURE_ACTIONSA typedef ptr SERVICE_FAILURE_ACTIONSA
SERVICE_FAILURE_ACTIONSW STRUC
dwResetPeriod		dd ?
lpRebootMsg		LPWSTR ?
lpCommand		LPWSTR ?
cActions		dd ?
lpsaActions		LPSC_ACTION ?
SERVICE_FAILURE_ACTIONSW ENDS
LPSERVICE_FAILURE_ACTIONSW typedef ptr SERVICE_FAILURE_ACTIONSW
ifdef _UNICODE
SERVICE_FAILURE_ACTIONS typedef SERVICE_FAILURE_ACTIONSW
LPSERVICE_FAILURE_ACTIONS typedef LPSERVICE_FAILURE_ACTIONSW
else
SERVICE_FAILURE_ACTIONS typedef SERVICE_FAILURE_ACTIONSA
LPSERVICE_FAILURE_ACTIONS typedef LPSERVICE_FAILURE_ACTIONSA
endif ;; UNICODE


;;
;; Handle Types
;;

SC_HANDLE		typedef HANDLE
LPSC_HANDLE		typedef ptr SC_HANDLE

SERVICE_STATUS_HANDLE	typedef DWORD

;;
;; Service Status Structure
;;

SERVICE_STATUS		STRUC
dwServiceType		dd ?
dwCurrentState		dd ?
dwControlsAccepted	dd ?
dwWin32ExitCode		dd ?
dwServiceSpecificExitCode dd ?
dwCheckPoint		dd ?
dwWaitHint		dd ?
SERVICE_STATUS		ENDS
LPSERVICE_STATUS	typedef ptr SERVICE_STATUS



;;
;; Service Status Enumeration Structure
;;

ENUM_SERVICE_STATUSA	STRUC
lpServiceName		LPSTR ?
lpDisplayName		LPSTR ?
ServiceStatus		SERVICE_STATUS <>
ENUM_SERVICE_STATUSA	ENDS
LPENUM_SERVICE_STATUSA	typedef ptr ENUM_SERVICE_STATUSA
ENUM_SERVICE_STATUSW	STRUC
lpServiceName		LPWSTR ?
lpDisplayName		LPWSTR ?
ServiceStatus		SERVICE_STATUS <>
ENUM_SERVICE_STATUSW	ENDS
LPENUM_SERVICE_STATUSW	typedef ptr ENUM_SERVICE_STATUSW
ifdef _UNICODE
ENUM_SERVICE_STATUS	typedef ENUM_SERVICE_STATUSW
LPENUM_SERVICE_STATUS	typedef LPENUM_SERVICE_STATUSW
else
ENUM_SERVICE_STATUS	typedef ENUM_SERVICE_STATUSA
LPENUM_SERVICE_STATUS	typedef LPENUM_SERVICE_STATUSA
endif ;; UNICODE


;;
;; Structures for the Lock API functions
;;

SC_LOCK			typedef PVOID

QUERY_SERVICE_LOCK_STATUSA STRUC
fIsLocked		dd ?
lpLockOwner		LPSTR ?
dwLockDuration		dd ?
QUERY_SERVICE_LOCK_STATUSA ENDS
LPQUERY_SERVICE_LOCK_STATUSA typedef ptr QUERY_SERVICE_LOCK_STATUSA
QUERY_SERVICE_LOCK_STATUSW STRUC
fIsLocked		dd ?
lpLockOwner		LPWSTR ?
dwLockDuration		dd ?
QUERY_SERVICE_LOCK_STATUSW ENDS
LPQUERY_SERVICE_LOCK_STATUSW typedef ptr QUERY_SERVICE_LOCK_STATUSW
ifdef _UNICODE
QUERY_SERVICE_LOCK_STATUS typedef QUERY_SERVICE_LOCK_STATUSW
LPQUERY_SERVICE_LOCK_STATUS typedef LPQUERY_SERVICE_LOCK_STATUSW
else
QUERY_SERVICE_LOCK_STATUS typedef QUERY_SERVICE_LOCK_STATUSA
LPQUERY_SERVICE_LOCK_STATUS typedef LPQUERY_SERVICE_LOCK_STATUSA
endif ;; UNICODE



;;
;; Query Service Configuration Structure
;;

QUERY_SERVICE_CONFIGA	STRUC
dwServiceType		dd ?
dwStartType		dd ?
dwErrorControl		dd ?
lpBinaryPathName	LPSTR ?
lpLoadOrderGroup	LPSTR ?
dwTagId			dd ?
lpDependencies		LPSTR ?
lpServiceStartName	LPSTR ?
lpDisplayName		LPSTR ?
QUERY_SERVICE_CONFIGA	ENDS
LPQUERY_SERVICE_CONFIGA typedef ptr QUERY_SERVICE_CONFIGA
QUERY_SERVICE_CONFIGW	STRUC
dwServiceType		dd ?
dwStartType		dd ?
dwErrorControl		dd ?
lpBinaryPathName	LPWSTR ?
lpLoadOrderGroup	LPWSTR ?
dwTagId			dd ?
lpDependencies		LPWSTR ?
lpServiceStartName	LPWSTR ?
lpDisplayName		LPWSTR ?
QUERY_SERVICE_CONFIGW	ENDS
LPQUERY_SERVICE_CONFIGW typedef ptr QUERY_SERVICE_CONFIGW
ifdef _UNICODE
QUERY_SERVICE_CONFIG	typedef QUERY_SERVICE_CONFIGW
LPQUERY_SERVICE_CONFIG	typedef LPQUERY_SERVICE_CONFIGW
else
QUERY_SERVICE_CONFIG	typedef QUERY_SERVICE_CONFIGA
LPQUERY_SERVICE_CONFIG	typedef LPQUERY_SERVICE_CONFIGA
endif ;; UNICODE



;;
;; Function Prototype for the Service Main Function
;;

SERVICE_MAIN_FUNCTIONW_T typedef proto _CType \
     dwNumServicesArgs: DWORD,
   lpServiceArgVectors: LPWSTR
LPSERVICE_MAIN_FUNCTIONW typedef ptr SERVICE_MAIN_FUNCTIONW_T

SERVICE_MAIN_FUNCTIONA_T typedef proto _CType \
     dwNumServicesArgs: DWORD,
   lpServiceArgVectors: LPSTR
LPSERVICE_MAIN_FUNCTIONA typedef ptr SERVICE_MAIN_FUNCTIONA_T

ifdef _UNICODE
LPSERVICE_MAIN_FUNCTION equ LPSERVICE_MAIN_FUNCTIONW
else
LPSERVICE_MAIN_FUNCTION equ LPSERVICE_MAIN_FUNCTIONA
endif ;;UNICODE


;;
;; Service Start Table
;;

SERVICE_TABLE_ENTRYA	STRUC
lpServiceName		LPSTR ?
lpServiceProc		LPSERVICE_MAIN_FUNCTIONA ?
SERVICE_TABLE_ENTRYA	ENDS
LPSERVICE_TABLE_ENTRYA	typedef ptr SERVICE_TABLE_ENTRYA
SERVICE_TABLE_ENTRYW	STRUC
lpServiceName		LPWSTR ?
lpServiceProc		LPSERVICE_MAIN_FUNCTIONW ?
SERVICE_TABLE_ENTRYW	ENDS
LPSERVICE_TABLE_ENTRYW	typedef ptr SERVICE_TABLE_ENTRYW
ifdef _UNICODE
SERVICE_TABLE_ENTRY	typedef SERVICE_TABLE_ENTRYW
LPSERVICE_TABLE_ENTRY	typedef LPSERVICE_TABLE_ENTRYW
else
SERVICE_TABLE_ENTRY	typedef SERVICE_TABLE_ENTRYA
LPSERVICE_TABLE_ENTRY	typedef LPSERVICE_TABLE_ENTRYA
endif ;; UNICODE

;;
;; Prototype for the Service Control Handler Function
;;

HANDLER_FUNCTION_T typedef proto _CType dwControl: DWORD
LPHANDLER_FUNCTION typedef ptr HANDLER_FUNCTION_T


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; API Function Prototypes
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;BOOL
ChangeServiceConfigA proto _CType \
	      hService: SC_HANDLE,
	 dwServiceType: DWORD,
	   dwStartType: DWORD,
	dwErrorControl: DWORD,
      lpBinaryPathName: LPCSTR,
      lpLoadOrderGroup: LPCSTR,
	     lpdwTagId: LPDWORD,
	lpDependencies: LPCSTR,
    lpServiceStartName: LPCSTR,
	    lpPassword: LPCSTR,
	 lpDisplayName: LPCSTR
ChangeServiceConfigW proto _CType \
	      hService: SC_HANDLE,
	 dwServiceType: DWORD,
	   dwStartType: DWORD,
	dwErrorControl: DWORD,
      lpBinaryPathName: LPCWSTR,
      lpLoadOrderGroup: LPCWSTR,
	     lpdwTagId: LPDWORD,
	lpDependencies: LPCWSTR,
    lpServiceStartName: LPCWSTR,
	    lpPassword: LPCWSTR,
	 lpDisplayName: LPCWSTR
ifdef _UNICODE
ChangeServiceConfig	equ <ChangeServiceConfigW>
else
ChangeServiceConfig	equ <ChangeServiceConfigA>
endif ;; NOT UNICODE

;BOOL
ChangeServiceConfig2A proto _CType \
	      hService: SC_HANDLE,
	   dwInfoLevel: DWORD,
		lpInfo: LPVOID
ChangeServiceConfig2W proto _CType \
	      hService: SC_HANDLE,
	   dwInfoLevel: DWORD,
		lpInfo: LPVOID
ifdef _UNICODE
ChangeServiceConfig2	equ <ChangeServiceConfig2W>
else
ChangeServiceConfig2	equ <ChangeServiceConfig2A>
endif ;; NOT UNICODE

;BOOL
CloseServiceHandle proto _CType \
	     hSCObject: SC_HANDLE

;BOOL
ControlService proto _CType \
	      hService: SC_HANDLE,
	     dwControl: DWORD,
       lpServiceStatus: LPSERVICE_STATUS

;SC_HANDLE
CreateServiceA proto _CType \
	    hSCManager: SC_HANDLE,
	 lpServiceName: LPCSTR,
	 lpDisplayName: LPCSTR,
       dwDesiredAccess: DWORD,
	 dwServiceType: DWORD,
	   dwStartType: DWORD,
	dwErrorControl: DWORD,
      lpBinaryPathName: LPCSTR,
      lpLoadOrderGroup: LPCSTR,
	     lpdwTagId: LPDWORD,
	lpDependencies: LPCSTR,
    lpServiceStartName: LPCSTR,
	    lpPassword: LPCSTR
CreateServiceW proto _CType \
	    hSCManager: SC_HANDLE,
	 lpServiceName: LPCWSTR,
	 lpDisplayName: LPCWSTR,
       dwDesiredAccess: DWORD,
	 dwServiceType: DWORD,
	   dwStartType: DWORD,
	dwErrorControl: DWORD,
      lpBinaryPathName: LPCWSTR,
      lpLoadOrderGroup: LPCWSTR,
	     lpdwTagId: LPDWORD,
	lpDependencies: LPCWSTR,
    lpServiceStartName: LPCWSTR,
	    lpPassword: LPCWSTR
ifdef _UNICODE
CreateService		equ <CreateServiceW>
else
CreateService		equ <CreateServiceA>
endif ;; NOT UNICODE

;BOOL
DeleteService proto _CType \
	      hService: SC_HANDLE

;BOOL
EnumDependentServicesA proto _CType \
	      hService: SC_HANDLE,
	dwServiceState: DWORD,
	    lpServices: LPENUM_SERVICE_STATUSA,
	     cbBufSize: DWORD,
	pcbBytesNeeded: LPDWORD,
    lpServicesReturned: LPDWORD
EnumDependentServicesW proto _CType \
	      hService: SC_HANDLE,
	dwServiceState: DWORD,
	    lpServices: LPENUM_SERVICE_STATUSW,
	     cbBufSize: DWORD,
	pcbBytesNeeded: LPDWORD,
    lpServicesReturned: LPDWORD
ifdef _UNICODE
EnumDependentServices	equ <EnumDependentServicesW>
else
EnumDependentServices	equ <EnumDependentServicesA>
endif ;; NOT UNICODE

;BOOL
EnumServicesStatusA proto _CType \
	    hSCManager: SC_HANDLE,
	 dwServiceType: DWORD,
	dwServiceState: DWORD,
	    lpServices: LPENUM_SERVICE_STATUSA,
	     cbBufSize: DWORD,
	pcbBytesNeeded: LPDWORD,
    lpServicesReturned: LPDWORD,
	lpResumeHandle: LPDWORD
EnumServicesStatusW proto _CType \
	    hSCManager: SC_HANDLE,
	 dwServiceType: DWORD,
	dwServiceState: DWORD,
	    lpServices: LPENUM_SERVICE_STATUSW,
	     cbBufSize: DWORD,
	pcbBytesNeeded: LPDWORD,
    lpServicesReturned: LPDWORD,
	lpResumeHandle: LPDWORD
ifdef _UNICODE
EnumServicesStatus	equ <EnumServicesStatusW>
else
EnumServicesStatus	equ <EnumServicesStatusA>
endif ;; NOT UNICODE

;BOOL
GetServiceKeyNameA proto _CType \
	    hSCManager: SC_HANDLE,
	 lpDisplayName: LPCSTR,
	 lpServiceName: LPSTR,
	   lpcchBuffer: LPDWORD
GetServiceKeyNameW proto _CType \
	    hSCManager: SC_HANDLE,
	 lpDisplayName: LPCWSTR,
	 lpServiceName: LPWSTR,
	   lpcchBuffer: LPDWORD
ifdef _UNICODE
GetServiceKeyName	equ <GetServiceKeyNameW>
else
GetServiceKeyName	equ <GetServiceKeyNameA>
endif ;; NOT UNICODE

;BOOL
GetServiceDisplayNameA proto _CType \
	    hSCManager: SC_HANDLE,
	 lpServiceName: LPCSTR,
	 lpDisplayName: LPSTR,
	   lpcchBuffer: LPDWORD
GetServiceDisplayNameW proto _CType \
	    hSCManager: SC_HANDLE,
	 lpServiceName: LPCWSTR,
	 lpDisplayName: LPWSTR,
	   lpcchBuffer: LPDWORD
ifdef _UNICODE
GetServiceDisplayName	equ <GetServiceDisplayNameW>
else
GetServiceDisplayName	equ <GetServiceDisplayNameA>
endif ;; NOT UNICODE

;SC_LOCK
LockServiceDatabase proto _CType \
	   hSCManager: SC_HANDLE

;BOOL
NotifyBootConfigStatus proto _CType \
	BootAcceptable: BOOL

;SC_HANDLE
OpenSCManagerA proto _CType \
	lpMachineName: LPCSTR,
       lpDatabaseName: LPCSTR,
      dwDesiredAccess: DWORD
OpenSCManagerW proto _CType \
	lpMachineName: LPCWSTR,
       lpDatabaseName: LPCWSTR,
      dwDesiredAccess: DWORD
ifdef _UNICODE
OpenSCManager		equ <OpenSCManagerW>
else
OpenSCManager		equ <OpenSCManagerA>
endif ;; NOT UNICODE

;SC_HANDLE
OpenServiceA proto _CType \
	    hSCManager: SC_HANDLE,
	 lpServiceName: LPCSTR,
       dwDesiredAccess: DWORD
OpenServiceW proto _CType \
	    hSCManager: SC_HANDLE,
	 lpServiceName: LPCWSTR,
       dwDesiredAccess: DWORD
ifdef _UNICODE
OpenService		equ <OpenServiceW>
else
OpenService		equ <OpenServiceA>
endif ;; NOT UNICODE

;BOOL
QueryServiceConfigA proto _CType \
	      hService: SC_HANDLE,
       lpServiceConfig: LPQUERY_SERVICE_CONFIGA,
	     cbBufSize: DWORD,
	pcbBytesNeeded: LPDWORD
QueryServiceConfigW proto _CType \
	      hService: SC_HANDLE,
       lpServiceConfig: LPQUERY_SERVICE_CONFIGW,
	     cbBufSize: DWORD,
	pcbBytesNeeded: LPDWORD
ifdef _UNICODE
QueryServiceConfig	equ <QueryServiceConfigW>
else
QueryServiceConfig	equ <QueryServiceConfigA>
endif ;; NOT UNICODE

;BOOL
QueryServiceConfig2A proto _CType \
	      hService: SC_HANDLE,
	   dwInfoLevel: DWORD,
	      lpBuffer: LPBYTE,
	     cbBufSize: DWORD,
	pcbBytesNeeded: LPDWORD
QueryServiceConfig2W proto _CType \
	      hService: SC_HANDLE,
	   dwInfoLevel: DWORD,
	      lpBuffer: LPBYTE,
	     cbBufSize: DWORD,
	pcbBytesNeeded: LPDWORD
ifdef _UNICODE
QueryServiceConfig2	equ <QueryServiceConfig2W>
else
QueryServiceConfig2	equ <QueryServiceConfig2A>
endif ;; NOT UNICODE

;BOOL
QueryServiceLockStatusA proto _CType \
	    hSCManager: SC_HANDLE,
	  lpLockStatus: LPQUERY_SERVICE_LOCK_STATUSA,
	     cbBufSize: DWORD,
	pcbBytesNeeded: LPDWORD
QueryServiceLockStatusW proto _CType \
	    hSCManager: SC_HANDLE,
	  lpLockStatus: LPQUERY_SERVICE_LOCK_STATUSW,
	     cbBufSize: DWORD,
	pcbBytesNeeded: LPDWORD
ifdef _UNICODE
QueryServiceLockStatus	equ <QueryServiceockStatusW>
else
QueryServiceLockStatus	equ <QueryServiceockStatusA>
endif ;; NOT UNICODE

;BOOL
QueryServiceObjectSecurity proto _CType \
	      hService: SC_HANDLE,
 dwSecurityInformation: SECURITY_INFORMATION,
  lpSecurityDescriptor: PSECURITY_DESCRIPTOR,
	     cbBufSize: DWORD,
	pcbBytesNeeded: LPDWORD

;BOOL
QueryServiceStatus proto _CType \
	      hService: SC_HANDLE,
       lpServiceStatus: LPSERVICE_STATUS

;SERVICE_STATUS_HANDLE
RegisterServiceCtrlHandlerA proto _CType \
	 lpServiceName: LPCSTR,
	 lpHandlerProc: LPHANDLER_FUNCTION
RegisterServiceCtrlHandlerW proto _CType \
	 lpServiceName: LPCWSTR,
	 lpHandlerProc: LPHANDLER_FUNCTION
ifdef _UNICODE
RegisterServiceCtrlHandler equ <RegisterServiceCtrlHandlerW>
else
RegisterServiceCtrlHandler equ <RegisterServiceCtrlHandlerA>
endif ;; NOT UNICODE

;BOOL
SetServiceObjectSecurity proto _CType \
	      hService: SC_HANDLE,
 dwSecurityInformation: SECURITY_INFORMATION,
  lpSecurityDescriptor: PSECURITY_DESCRIPTOR

;BOOL
SetServiceStatus proto _CType \
	hServiceStatus: SERVICE_STATUS_HANDLE,
       lpServiceStatus: LPSERVICE_STATUS

;BOOL
StartServiceCtrlDispatcherA proto _CType \
   lpServiceStartTable: ptr SERVICE_TABLE_ENTRYA
StartServiceCtrlDispatcherW proto _CType \
   lpServiceStartTable: ptr SERVICE_TABLE_ENTRYW
ifdef _UNICODE
StartServiceCtrlDispatcher equ <StartServiceCtrlDispatcherW>
else
StartServiceCtrlDispatcher equ <StartServiceCtrlDispatcherA>
endif ;; NOT UNICODE


;BOOL
StartServiceA proto _CType \
	      hService: SC_HANDLE,
      dwNumServiceArgs: DWORD,
   lpServiceArgVectors: LPCSTR
StartServiceW proto _CType \
	      hService: SC_HANDLE,
      dwNumServiceArgs: DWORD,
   lpServiceArgVectors: LPCWSTR
ifdef _UNICODE
StartService		equ <StartServiceW>
else
StartService		equ <StartServiceA>
endif ;; NOT UNICODE

;BOOL
UnlockServiceDatabase proto _CType \
		ScLock: SC_LOCK


endif ;; _WINSVC_

.list
