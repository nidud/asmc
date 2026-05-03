ifndef _RPCNDR500_
include rpcndr500.inc
endif

ifndef __tssbx_h__
define __tssbx_h__

ifndef __oaidl_h__
include oaidl.inc
endif
ifndef __ocidl_h__
include ocidl.inc
endif
ifndef _WINAPIFAMILY_
include winapifamily.inc
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

define PLUGIN_CAPABILITY_EXTERNAL_REDIRECTION 0x1

ifndef __IWTSSBPlugin_INTERFACE_DEFINED__
define __IWTSSBPlugin_INTERFACE_DEFINED__

define	MaxFQDN_Len	( 256 )
define	MaxNetBiosName_Len	( 16 )
define	MaxNumOfExposed_IPs	( 12 )
define	MaxUserName_Len ( 104 )
define	MaxDomainName_Len	( 256 )
define	MaxFarm_Len	( 256 )
define	MaxAppName_Len	( 256 )

.enum WTSSBX_MACHINE_DRAIN {
	WTSSBX_MACHINE_DRAIN_UNSPEC,
	WTSSBX_MACHINE_DRAIN_OFF,
	WTSSBX_MACHINE_DRAIN_ON
	}

.enum WTSSBX_MACHINE_SESSION_MODE {
	WTSSBX_MACHINE_SESSION_MODE_UNSPEC,
	WTSSBX_MACHINE_SESSION_MODE_SINGLE,
	WTSSBX_MACHINE_SESSION_MODE_MULTIPLE
	}

.enum WTSSBX_ADDRESS_FAMILY {
	WTSSBX_ADDRESS_FAMILY_AF_UNSPEC,
	WTSSBX_ADDRESS_FAMILY_AF_INET,
	WTSSBX_ADDRESS_FAMILY_AF_INET6,
	WTSSBX_ADDRESS_FAMILY_AF_IPX,
	WTSSBX_ADDRESS_FAMILY_AF_NETBIOS
	}

WTSSBX_IP_ADDRESS	struct
AddressFamily		WTSSBX_ADDRESS_FAMILY ?
Address			BYTE 16 dup(?)
PortNumber		word ?
dwScope			DWORD ?
WTSSBX_IP_ADDRESS	ends


.enum WTSSBX_MACHINE_STATE {
	WTSSBX_MACHINE_STATE_UNSPEC,
	WTSSBX_MACHINE_STATE_READY,
	WTSSBX_MACHINE_STATE_SYNCHRONIZING
	}

WTSSBX_MACHINE_CONNECT_INFO struct
wczMachineFQDN		WCHAR 257 dup(?)
wczMachineNetBiosName	WCHAR 17 dup(?)
dwNumOfIPAddr		DWORD ?
IPaddr			WTSSBX_IP_ADDRESS 12 dup(<>)
WTSSBX_MACHINE_CONNECT_INFO ends


WTSSBX_MACHINE_INFO	struct
ClientConnectInfo	WTSSBX_MACHINE_CONNECT_INFO <>
wczFarmName		WCHAR 257 dup(?)
InternalIPAddress	WTSSBX_IP_ADDRESS <>
dwMaxSessionsLimit	DWORD ?
ServerWeight		DWORD ?
SingleSessionMode	WTSSBX_MACHINE_SESSION_MODE ?
InDrain			WTSSBX_MACHINE_DRAIN ?
MachineState		WTSSBX_MACHINE_STATE ?
WTSSBX_MACHINE_INFO	ends


.enum WTSSBX_SESSION_STATE {
	WTSSBX_SESSION_STATE_UNSPEC,
	WTSSBX_SESSION_STATE_ACTIVE,
	WTSSBX_SESSION_STATE_DISCONNECTED
	}

WTSSBX_SESSION_INFO	struct
wszUserName		WCHAR 105 dup(?)
wszDomainName		WCHAR 257 dup(?)
ApplicationType		WCHAR 257 dup(?)
dwSessionId		DWORD ?
CreateTime		FILETIME <>
DisconnectTime		FILETIME <>
SessionState		WTSSBX_SESSION_STATE ?
WTSSBX_SESSION_INFO	ends


.enum WTSSBX_NOTIFICATION_TYPE {
	WTSSBX_NOTIFICATION_REMOVED	= 0x1,
	WTSSBX_NOTIFICATION_CHANGED	= 0x2,
	WTSSBX_NOTIFICATION_ADDED	= 0x4,
	WTSSBX_NOTIFICATION_RESYNC	= 0x8
	}

DEFINE_IIDX(IWTSSBPlugin, "DC44BE78-B18D-4399-B210-641BF67A002C")

.comdef IWTSSBPlugin : public IUnknown
    Initialize		proc :ptr
    WTSSBX_MachineChangeNotification proc :WTSSBX_NOTIFICATION_TYPE, :LONG, :ptr
    WTSSBX_SessionChangeNotification proc :WTSSBX_NOTIFICATION_TYPE, :LONG, :DWORD, :WTSSBX_SESSION_INFO
    WTSSBX_GetMostSuitableServer proc :ptr, :ptr, :ptr, :ptr, :ptr
    Terminated		proc
    WTSSBX_GetUserExternalSession proc :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
   .ends

endif

endif

endif
