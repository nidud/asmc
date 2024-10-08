ifndef _WINSVC_
define _WINSVC_
ifndef _WINDEF_
 include windef.inc
endif

.pragma comment(lib, advapi32)

SERVICES_ACTIVE_DATABASE equ <"ServicesActive">
SERVICES_FAILED_DATABASE equ <"ServicesFailed">

SC_GROUP_IDENTIFIER	equ '+'

SERVICE_NO_CHANGE	equ 0xffffffff
SERVICE_ACTIVE		equ 0x00000001
SERVICE_INACTIVE	equ 0x00000002
SERVICE_STATE_ALL	equ SERVICE_ACTIVE OR SERVICE_INACTIVE

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

SERVICE_STOPPED			equ 0x00000001
SERVICE_START_PENDING		equ 0x00000002
SERVICE_STOP_PENDING		equ 0x00000003
SERVICE_RUNNING			equ 0x00000004
SERVICE_CONTINUE_PENDING	equ 0x00000005
SERVICE_PAUSE_PENDING		equ 0x00000006
SERVICE_PAUSED			equ 0x00000007

SERVICE_ACCEPT_STOP		equ 0x00000001
SERVICE_ACCEPT_PAUSE_CONTINUE	equ 0x00000002
SERVICE_ACCEPT_SHUTDOWN		equ 0x00000004
SERVICE_ACCEPT_PARAMCHANGE	equ 0x00000008
SERVICE_ACCEPT_NETBINDCHANGE	equ 0x00000010

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

SERVICE_CONFIG_DESCRIPTION	equ 1
SERVICE_CONFIG_FAILURE_ACTIONS	equ 2

SERVICE_DESCRIPTIONA	STRUC
lpDescription		LPSTR ?
SERVICE_DESCRIPTIONA	ENDS
LPSERVICE_DESCRIPTIONA	typedef ptr SERVICE_DESCRIPTIONA
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
endif

SC_ACTION_NONE		equ 0
SC_ACTION_RESTART	equ 1
SC_ACTION_REBOOT	equ 2
SC_ACTION_RUN_COMMAND	equ 3
SC_ACTION_TYPE		typedef DWORD

SC_ACTION		STRUC
Type			SC_ACTION_TYPE ?
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
endif

SC_HANDLE		typedef HANDLE
LPSC_HANDLE		typedef ptr SC_HANDLE

SERVICE_STATUS_HANDLE	typedef DWORD

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
endif

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
endif

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
endif


CALLBACK(LPSERVICE_MAIN_FUNCTIONW, :DWORD, :LPWSTR)
CALLBACK(LPSERVICE_MAIN_FUNCTIONA, :DWORD, :LPSTR)

ifdef _UNICODE
LPSERVICE_MAIN_FUNCTION equ LPSERVICE_MAIN_FUNCTIONW
else
LPSERVICE_MAIN_FUNCTION equ LPSERVICE_MAIN_FUNCTIONA
endif


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
endif


CALLBACK(LPHANDLER_FUNCTION, :DWORD)

ChangeServiceConfigA proto WINAPI :SC_HANDLE, :DWORD, :DWORD, :DWORD, :LPCSTR, :LPCSTR, :LPDWORD, :LPCSTR, :LPCSTR, :LPCSTR, :LPCSTR
ChangeServiceConfigW proto WINAPI :SC_HANDLE, :DWORD, :DWORD, :DWORD, :LPCWSTR, :LPCWSTR, :LPDWORD, :LPCWSTR, :LPCWSTR, :LPCWSTR, :LPCWSTR
ifdef _UNICODE
ChangeServiceConfig	equ <ChangeServiceConfigW>
else
ChangeServiceConfig	equ <ChangeServiceConfigA>
endif

ChangeServiceConfig2A proto WINAPI :SC_HANDLE, :DWORD, :ptr
ChangeServiceConfig2W proto WINAPI :SC_HANDLE, :DWORD, :ptr
ifdef _UNICODE
ChangeServiceConfig2	equ <ChangeServiceConfig2W>
else
ChangeServiceConfig2	equ <ChangeServiceConfig2A>
endif

CloseServiceHandle proto WINAPI :SC_HANDLE
ControlService proto WINAPI :SC_HANDLE, :DWORD, :LPSERVICE_STATUS
CreateServiceA proto WINAPI :SC_HANDLE, :LPCSTR, :LPCSTR, :DWORD, :DWORD, :DWORD, :DWORD, :LPCSTR, :LPCSTR, :LPDWORD, :LPCSTR, :LPCSTR, :LPCSTR
CreateServiceW proto WINAPI :SC_HANDLE, :LPCWSTR, :LPCWSTR, :DWORD, :DWORD, :DWORD, :DWORD, :LPCWSTR, :LPCWSTR, :LPDWORD, :LPCWSTR, :LPCWSTR, :LPCWSTR
ifdef _UNICODE
CreateService		equ <CreateServiceW>
else
CreateService		equ <CreateServiceA>
endif

DeleteService proto WINAPI :SC_HANDLE
EnumDependentServicesA proto WINAPI :SC_HANDLE, :DWORD, :LPENUM_SERVICE_STATUSA, :DWORD, :LPDWORD, :LPDWORD
EnumDependentServicesW proto WINAPI :SC_HANDLE, :DWORD, :LPENUM_SERVICE_STATUSW, :DWORD, :LPDWORD, :LPDWORD
ifdef _UNICODE
EnumDependentServices	equ <EnumDependentServicesW>
else
EnumDependentServices	equ <EnumDependentServicesA>
endif

EnumServicesStatusA proto WINAPI :SC_HANDLE, :DWORD, :DWORD, :LPENUM_SERVICE_STATUSA, :DWORD, :LPDWORD, :LPDWORD, :LPDWORD
EnumServicesStatusW proto WINAPI :SC_HANDLE, :DWORD, :DWORD, :LPENUM_SERVICE_STATUSW, :DWORD, :LPDWORD, :LPDWORD, :LPDWORD
ifdef _UNICODE
EnumServicesStatus	equ <EnumServicesStatusW>
else
EnumServicesStatus	equ <EnumServicesStatusA>
endif

GetServiceKeyNameA proto WINAPI :SC_HANDLE, :LPCSTR, :LPSTR, :LPDWORD
GetServiceKeyNameW proto WINAPI :SC_HANDLE, :LPCWSTR, :LPWSTR, :LPDWORD
ifdef _UNICODE
GetServiceKeyName	equ <GetServiceKeyNameW>
else
GetServiceKeyName	equ <GetServiceKeyNameA>
endif

GetServiceDisplayNameA proto WINAPI :SC_HANDLE, :LPCSTR, :LPSTR, :LPDWORD
GetServiceDisplayNameW proto WINAPI :SC_HANDLE, :LPCWSTR, :LPWSTR, :LPDWORD
ifdef _UNICODE
GetServiceDisplayName	equ <GetServiceDisplayNameW>
else
GetServiceDisplayName	equ <GetServiceDisplayNameA>
endif

LockServiceDatabase proto WINAPI :SC_HANDLE
NotifyBootConfigStatus proto WINAPI :BOOL
OpenSCManagerA proto WINAPI :LPCSTR, :LPCSTR, :DWORD
OpenSCManagerW proto WINAPI :LPCWSTR, :LPCWSTR, :DWORD
ifdef _UNICODE
OpenSCManager		equ <OpenSCManagerW>
else
OpenSCManager		equ <OpenSCManagerA>
endif

OpenServiceA proto WINAPI :SC_HANDLE, :LPCSTR, :DWORD
OpenServiceW proto WINAPI :SC_HANDLE, :LPCWSTR, :DWORD
ifdef _UNICODE
OpenService		equ <OpenServiceW>
else
OpenService		equ <OpenServiceA>
endif

QueryServiceConfigA proto WINAPI :SC_HANDLE, :LPQUERY_SERVICE_CONFIGA, :DWORD, :LPDWORD
QueryServiceConfigW proto WINAPI :SC_HANDLE, :LPQUERY_SERVICE_CONFIGW, :DWORD, :LPDWORD
ifdef _UNICODE
QueryServiceConfig	equ <QueryServiceConfigW>
else
QueryServiceConfig	equ <QueryServiceConfigA>
endif

QueryServiceConfig2A proto WINAPI :SC_HANDLE, :DWORD, :LPBYTE, :DWORD, :LPDWORD
QueryServiceConfig2W proto WINAPI :SC_HANDLE, :DWORD, :LPBYTE, :DWORD, :LPDWORD
ifdef _UNICODE
QueryServiceConfig2	equ <QueryServiceConfig2W>
else
QueryServiceConfig2	equ <QueryServiceConfig2A>
endif

QueryServiceLockStatusA proto WINAPI :SC_HANDLE, :LPQUERY_SERVICE_LOCK_STATUSA, :DWORD, :LPDWORD
QueryServiceLockStatusW proto WINAPI :SC_HANDLE, :LPQUERY_SERVICE_LOCK_STATUSW, :DWORD, :LPDWORD
ifdef _UNICODE
QueryServiceLockStatus	equ <QueryServiceockStatusW>
else
QueryServiceLockStatus	equ <QueryServiceockStatusA>
endif

QueryServiceObjectSecurity proto WINAPI :SC_HANDLE, :SECURITY_INFORMATION, :PSECURITY_DESCRIPTOR, :DWORD, :LPDWORD
QueryServiceStatus proto WINAPI :SC_HANDLE, :LPSERVICE_STATUS
RegisterServiceCtrlHandlerA proto WINAPI :LPCSTR, :LPHANDLER_FUNCTION
RegisterServiceCtrlHandlerW proto WINAPI :LPCWSTR, :LPHANDLER_FUNCTION
ifdef _UNICODE
RegisterServiceCtrlHandler equ <RegisterServiceCtrlHandlerW>
else
RegisterServiceCtrlHandler equ <RegisterServiceCtrlHandlerA>
endif

SetServiceObjectSecurity proto WINAPI :SC_HANDLE, :SECURITY_INFORMATION, :PSECURITY_DESCRIPTOR
SetServiceStatus proto WINAPI :SERVICE_STATUS_HANDLE, :LPSERVICE_STATUS
StartServiceCtrlDispatcherA proto WINAPI :ptr
StartServiceCtrlDispatcherW proto WINAPI :ptr
ifdef _UNICODE
StartServiceCtrlDispatcher equ <StartServiceCtrlDispatcherW>
else
StartServiceCtrlDispatcher equ <StartServiceCtrlDispatcherA>
endif

StartServiceA proto WINAPI :SC_HANDLE, :DWORD, :LPCSTR
StartServiceW proto WINAPI :SC_HANDLE, :DWORD, :LPCWSTR
ifdef _UNICODE
StartService		equ <StartServiceW>
else
StartService		equ <StartServiceA>
endif

UnlockServiceDatabase proto WINAPI :SC_LOCK

endif
