ifndef __REQUIRED_RPCNDR_H_VERSION__
__REQUIRED_RPCNDR_H_VERSION__ equ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
__REQUIRED_RPCSAL_H_VERSION__ equ 100
endif

include rpc.inc
include rpcndr.inc

ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr>
endif

ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif

ifndef __netcon_h__
__netcon_h__ equ 1
.xlist

ifndef __IEnumNetConnection_FWD_DEFINED__
__IEnumNetConnection_FWD_DEFINED__ equ 1
endif
ifndef __INetConnection_FWD_DEFINED__
__INetConnection_FWD_DEFINED__ equ 1
endif
ifndef __INetConnectionManager_FWD_DEFINED__
__INetConnectionManager_FWD_DEFINED__ equ 1
endif
ifndef __INetConnectionConnectUi_FWD_DEFINED__
__INetConnectionConnectUi_FWD_DEFINED__ equ 1
endif
ifndef __IEnumNetSharingPortMapping_FWD_DEFINED__
__IEnumNetSharingPortMapping_FWD_DEFINED__ equ 1
endif
ifndef __INetSharingPortMappingProps_FWD_DEFINED__
__INetSharingPortMappingProps_FWD_DEFINED__ equ 1
endif
ifndef __INetSharingPortMapping_FWD_DEFINED__
__INetSharingPortMapping_FWD_DEFINED__ equ 1
endif
ifndef __IEnumNetSharingEveryConnection_FWD_DEFINED__
__IEnumNetSharingEveryConnection_FWD_DEFINED__ equ 1
endif
ifndef __IEnumNetSharingPublicConnection_FWD_DEFINED__
__IEnumNetSharingPublicConnection_FWD_DEFINED__ equ 1
endif
ifndef __IEnumNetSharingPrivateConnection_FWD_DEFINED__
__IEnumNetSharingPrivateConnection_FWD_DEFINED__ equ 1
endif
ifndef __INetSharingPortMappingCollection_FWD_DEFINED__
__INetSharingPortMappingCollection_FWD_DEFINED__ equ 1
endif
ifndef __INetConnectionProps_FWD_DEFINED__
__INetConnectionProps_FWD_DEFINED__ equ 1
endif
ifndef __INetSharingConfiguration_FWD_DEFINED__
__INetSharingConfiguration_FWD_DEFINED__ equ 1
endif
ifndef __INetSharingEveryConnectionCollection_FWD_DEFINED__
__INetSharingEveryConnectionCollection_FWD_DEFINED__ equ 1
endif
ifndef __INetSharingPublicConnectionCollection_FWD_DEFINED__
__INetSharingPublicConnectionCollection_FWD_DEFINED__ equ 1
endif
ifndef __INetSharingPrivateConnectionCollection_FWD_DEFINED__
__INetSharingPrivateConnectionCollection_FWD_DEFINED__ equ 1
endif
ifndef __INetSharingManager_FWD_DEFINED__
__INetSharingManager_FWD_DEFINED__ equ 1
endif

ifndef __NetSharingManager_FWD_DEFINED__
__NetSharingManager_FWD_DEFINED__ equ 1
NetSharingManager	typedef NetSharingManager
endif

include oaidl.inc
include prsht.inc
.xlist

externdef		CLSID_ConnectionManager:CLSID
externdef		CLSID_NetSharingManager:CLSID

NETCON_MAX_NAME_LEN	equ 256

externdef		__MIDL_itf_netcon_0000_0000_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_netcon_0000_0000_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IEnumNetConnection_INTERFACE_DEFINED__
__IEnumNetConnection_INTERFACE_DEFINED__ equ 1

externdef		IID_IEnumNetConnection:IID
IEnumNetConnectionVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Next, :ULONG, :ptr, :ptr
	STDMETHOD	Skip, :ULONG
	STDMETHOD	Reset
	STDMETHOD	Clone, :ptr
IEnumNetConnectionVtbl ends
IEnumNetConnection struct
	lpVtbl		PVOID ?
IEnumNetConnection ends
endif

ifndef __INetConnection_INTERFACE_DEFINED__
__INetConnection_INTERFACE_DEFINED__ equ 1

NETCON_CHARACTERISTIC_FLAGS typedef SDWORD
NCCF_NONE		equ 0
NCCF_ALL_USERS		equ 0x1
NCCF_ALLOW_DUPLICATION	equ 0x2
NCCF_ALLOW_REMOVAL	equ 0x4
NCCF_ALLOW_RENAME	equ 0x8
NCCF_INCOMING_ONLY	equ 0x20
NCCF_OUTGOING_ONLY	equ 0x40
NCCF_BRANDED		equ 0x80
NCCF_SHARED		equ 0x100
NCCF_BRIDGED		equ 0x200
NCCF_FIREWALLED		equ 0x400
NCCF_DEFAULT		equ 0x800
NCCF_HOMENET_CAPABLE	equ 0x1000
NCCF_SHARED_PRIVATE	equ 0x2000
NCCF_QUARANTINED	equ 0x4000
NCCF_RESERVED		equ 0x8000
NCCF_HOSTED_NETWORK	equ 0x10000
NCCF_VIRTUAL_STATION	equ 0x20000
NCCF_BLUETOOTH_MASK	equ 0xf0000
NCCF_LAN_MASK		equ 0xf00000

NETCON_STATUS		typedef SDWORD
NCS_DISCONNECTED	equ 0
NCS_CONNECTING		equ ( NCS_DISCONNECTED + 1 )
NCS_CONNECTED		equ ( NCS_CONNECTING + 1 )
NCS_DISCONNECTING	equ ( NCS_CONNECTED + 1 )
NCS_HARDWARE_NOT_PRESENT equ ( NCS_DISCONNECTING + 1 )
NCS_HARDWARE_DISABLED	equ ( NCS_HARDWARE_NOT_PRESENT + 1 )
NCS_HARDWARE_MALFUNCTION equ ( NCS_HARDWARE_DISABLED + 1 )
NCS_MEDIA_DISCONNECTED	equ ( NCS_HARDWARE_MALFUNCTION + 1 )
NCS_AUTHENTICATING	equ ( NCS_MEDIA_DISCONNECTED + 1 )
NCS_AUTHENTICATION_SUCCEEDED equ ( NCS_AUTHENTICATING + 1 )
NCS_AUTHENTICATION_FAILED equ ( NCS_AUTHENTICATION_SUCCEEDED + 1 )
NCS_INVALID_ADDRESS	equ ( NCS_AUTHENTICATION_FAILED + 1 )
NCS_CREDENTIALS_REQUIRED equ ( NCS_INVALID_ADDRESS + 1 )

NETCON_TYPE		typedef SDWORD
NCT_DIRECT_CONNECT	equ 0
NCT_INBOUND		equ 1
NCT_INTERNET		equ ( NCT_INBOUND + 1 )
NCT_LAN			equ ( NCT_INTERNET + 1 )
NCT_PHONE		equ ( NCT_LAN + 1 )
NCT_TUNNEL		equ ( NCT_PHONE + 1 )
NCT_BRIDGE		equ ( NCT_TUNNEL + 1 )

NETCON_MEDIATYPE	typedef SDWORD
NCM_NONE		equ 0
NCM_DIRECT		equ ( NCM_NONE + 1 )
NCM_ISDN		equ 2
NCM_LAN			equ ( NCM_ISDN + 1 )
NCM_PHONE		equ ( NCM_LAN + 1 )
NCM_TUNNEL		equ ( NCM_PHONE + 1 )
NCM_PPPOE		equ ( NCM_TUNNEL + 1 )
NCM_BRIDGE		equ ( NCM_PPPOE + 1 )
NCM_SHAREDACCESSHOST_LAN equ ( NCM_BRIDGE + 1 )
NCM_SHAREDACCESSHOST_RAS equ ( NCM_SHAREDACCESSHOST_LAN + 1 )

NETCON_PROPERTIES	STRUC
guidId			GUID <>
pszwName		LPWSTR ?
pszwDeviceName		LPWSTR ?
Status			NETCON_STATUS ?
MediaType		NETCON_MEDIATYPE ?
dwCharacter		dd ?
clsidThisObject		CLSID <>
clsidUiObject		CLSID <>
NETCON_PROPERTIES	ENDS

S_OBJECT_NO_LONGER_VALID equ (0x00000002)

externdef		IID_INetConnection:IID
INetConnectionVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Connect
	STDMETHOD	Disconnect
	STDMETHOD	Delete
	STDMETHOD	Duplicate, :LPCWSTR, :ptr
	STDMETHOD	GetProperties, :ptr
	STDMETHOD	GetUiObjectClassId, :ptr
	STDMETHOD	Rename, :LPCWSTR
INetConnectionVtbl ends
INetConnection struct
	lpVtbl		PVOID ?
INetConnection ends
endif

;STDAPI_(VOID)
NcFreeNetconProperties proto WINAPI \
		pProps: ptr NETCON_PROPERTIES

;STDAPI_(BOOL)
NcIsValidConnectionName proto WINAPI \
	      pszwName: PCWSTR

externdef		__MIDL_itf_netcon_0000_0002_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_netcon_0000_0002_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __INetConnectionManager_INTERFACE_DEFINED__
__INetConnectionManager_INTERFACE_DEFINED__ equ 1


NETCONMGR_ENUM_FLAGS	typedef SDWORD
NCME_DEFAULT		equ 0
NCME_HIDDEN		equ 0x1

externdef		IID_INetConnectionManager:IID
INetConnectionManagerVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	EnumConnections, :NETCONMGR_ENUM_FLAGS, :ptr
INetConnectionManagerVtbl ends
INetConnectionManager struct
	lpVtbl		PVOID ?
INetConnectionManager ends
endif

ifndef __INetConnectionConnectUi_INTERFACE_DEFINED__
__INetConnectionConnectUi_INTERFACE_DEFINED__ equ 1

NETCONUI_CONNECT_FLAGS	typedef SDWORD
NCUC_DEFAULT		equ 0
NCUC_NO_UI		equ 0x1
NCUC_ENABLE_DISABLE	equ 0x2

externdef		IID_INetConnectionConnectUi:IID

INetConnectionConnectUiVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	SetConnection, :ptr
	STDMETHOD	Connect, :HWND, :DWORD
	STDMETHOD	Disconnect, :HWND, :DWORD
INetConnectionConnectUiVtbl ends
INetConnectionConnectUi struct
	lpVtbl		PVOID ?
INetConnectionConnectUi ends
endif

ifndef __IEnumNetSharingPortMapping_INTERFACE_DEFINED__
__IEnumNetSharingPortMapping_INTERFACE_DEFINED__ equ 1

externdef		IID_IEnumNetSharingPortMapping:IID
IEnumNetSharingPortMappingVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Next, :ULONG, :ptr, :ptr
	STDMETHOD	Skip, :ULONG
	STDMETHOD	Reset
	STDMETHOD	Clone, :ptr
IEnumNetSharingPortMappingVtbl ends
IEnumNetSharingPortMapping struct
	lpVtbl		PVOID ?
IEnumNetSharingPortMapping ends
endif

ifndef __INetSharingPortMappingProps_INTERFACE_DEFINED__
__INetSharingPortMappingProps_INTERFACE_DEFINED__ equ 1

externdef		IID_INetSharingPortMappingProps:IID
INetSharingPortMappingPropsVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	get_Name, :ptr
	STDMETHOD	get_IPProtocol, :ptr
	STDMETHOD	get_ExternalPort, :ptr
	STDMETHOD	get_InternalPort, :ptr
	STDMETHOD	get_Options, :ptr
	STDMETHOD	get_TargetName, :ptr
	STDMETHOD	get_TargetIPAddress, :ptr
	STDMETHOD	get_Enabled, :ptr
INetSharingPortMappingPropsVtbl ends
INetSharingPortMappingProps struct
	lpVtbl		PVOID ?
INetSharingPortMappingProps ends
endif

ifndef __INetSharingPortMapping_INTERFACE_DEFINED__
__INetSharingPortMapping_INTERFACE_DEFINED__ equ 1

externdef		IID_INetSharingPortMapping:IID
INetSharingPortMappingVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	Disable
	STDMETHOD	Enable
	STDMETHOD	get_Properties, :ptr
	STDMETHOD	Delete
INetSharingPortMappingVtbl ends
INetSharingPortMapping struct
	lpVtbl		PVOID ?
INetSharingPortMapping ends
endif

ifndef __IEnumNetSharingEveryConnection_INTERFACE_DEFINED__
__IEnumNetSharingEveryConnection_INTERFACE_DEFINED__ equ 1

externdef		IID_IEnumNetSharingEveryConnection:IID
IEnumNetSharingEveryConnectionVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Next, :ULONG, :ptr, :ptr
	STDMETHOD	Skip, :ULONG
	STDMETHOD	Reset
	STDMETHOD	Clone, :ptr
IEnumNetSharingEveryConnectionVtbl ends
IEnumNetSharingEveryConnection struct
	lpVtbl		PVOID ?
IEnumNetSharingEveryConnection ends
endif

ifndef __IEnumNetSharingPublicConnection_INTERFACE_DEFINED__
__IEnumNetSharingPublicConnection_INTERFACE_DEFINED__ equ 1

externdef		IID_IEnumNetSharingPublicConnection:IID
IEnumNetSharingPublicConnectionVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Next, :ULONG, :ptr, :ptr
	STDMETHOD	Skip, :ULONG
	STDMETHOD	Reset
	STDMETHOD	Clone, :ptr
IEnumNetSharingPublicConnectionVtbl ends
IEnumNetSharingPublicConnection struct
	lpVtbl		PVOID ?
IEnumNetSharingPublicConnection ends
endif

ifndef __IEnumNetSharingPrivateConnection_INTERFACE_DEFINED__
__IEnumNetSharingPrivateConnection_INTERFACE_DEFINED__ equ 1

externdef		IID_IEnumNetSharingPrivateConnection:IID
IEnumNetSharingPrivateConnectionVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Next, :ULONG, :ptr, :ptr
	STDMETHOD	Skip, :ULONG
	STDMETHOD	Reset
	STDMETHOD	Clone, :ptr
IEnumNetSharingPrivateConnectionVtbl ends
IEnumNetSharingPrivateConnection struct
	lpVtbl		PVOID ?
IEnumNetSharingPrivateConnection ends
endif

ifndef __INetSharingPortMappingCollection_INTERFACE_DEFINED__
__INetSharingPortMappingCollection_INTERFACE_DEFINED__ equ 1

externdef		IID_INetSharingPortMappingCollection:IID

INetSharingPortMappingCollectionVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	get__NewEnum, :ptr
	STDMETHOD	get_Count, :ptr
INetSharingPortMappingCollectionVtbl ends
INetSharingPortMappingCollection struct
	lpVtbl		PVOID ?
INetSharingPortMappingCollection ends
endif

externdef		__MIDL_itf_netcon_0000_0011_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_netcon_0000_0011_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __INetConnectionProps_INTERFACE_DEFINED__
__INetConnectionProps_INTERFACE_DEFINED__ equ 1

externdef		IID_INetConnectionProps:IID

INetConnectionPropsVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	get_Guid, :ptr
	STDMETHOD	get_Name, :ptr
	STDMETHOD	get_DeviceName, :ptr
	STDMETHOD	get_Status, :ptr
	STDMETHOD	get_MediaType, :ptr
	STDMETHOD	get_Characteristics, :ptr
INetConnectionPropsVtbl ends
INetConnectionProps struct
	lpVtbl		PVOID ?
INetConnectionProps ends
endif

ifndef __INetSharingConfiguration_INTERFACE_DEFINED__
__INetSharingConfiguration_INTERFACE_DEFINED__ equ 1


SHARINGCONNECTIONTYPE	typedef SDWORD
ICSSHARINGTYPE_PUBLIC	equ 0
ICSSHARINGTYPE_PRIVATE	equ ( ICSSHARINGTYPE_PUBLIC + 1 )

LPSHARINGCONNECTIONTYPE typedef ptr SHARINGCONNECTIONTYPE

SHARINGCONNECTION_ENUM_FLAGS typedef SDWORD
ICSSC_DEFAULT		equ 0
ICSSC_ENABLED		equ ( ICSSC_DEFAULT + 1 )

ICS_TARGETTYPE		typedef SDWORD
ICSTT_NAME		equ 0
ICSTT_IPADDRESS		equ ( ICSTT_NAME + 1 )

externdef		IID_INetSharingConfiguration:IID

INetSharingConfigurationVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	get_SharingEnabled, :ptr
	STDMETHOD	get_SharingConnectionType, :ptr
	STDMETHOD	DisableSharing
	STDMETHOD	EnableSharing, :SHARINGCONNECTIONTYPE
	STDMETHOD	get_InternetFirewallEnabled, :ptr
	STDMETHOD	DisableInternetFirewall
	STDMETHOD	EnableInternetFirewall
	STDMETHOD	get_EnumPortMappings, :SHARINGCONNECTION_ENUM_FLAGS, :ptr
	STDMETHOD	AddPortMapping, :BSTR, :UCHAR, :USHORT, :USHORT, :DWORD, :BSTR, :ICS_TARGETTYPE, :ptr
	STDMETHOD	RemovePortMapping, :ptr
INetSharingConfigurationVtbl ends
INetSharingConfiguration struct
	lpVtbl		PVOID ?
INetSharingConfiguration ends
endif

ifndef __INetSharingEveryConnectionCollection_INTERFACE_DEFINED__
__INetSharingEveryConnectionCollection_INTERFACE_DEFINED__ equ 1

externdef		IID_INetSharingEveryConnectionCollection:IID

INetSharingEveryConnectionCollectionVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	get__NewEnum, :ptr
	STDMETHOD	get_Count, :ptr
INetSharingEveryConnectionCollectionVtbl ends
INetSharingEveryConnectionCollection struct
	lpVtbl		PVOID ?
INetSharingEveryConnectionCollection ends
endif

ifndef __INetSharingPublicConnectionCollection_INTERFACE_DEFINED__
__INetSharingPublicConnectionCollection_INTERFACE_DEFINED__ equ 1

externdef		IID_INetSharingPublicConnectionCollection:IID
INetSharingPublicConnectionCollectionVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	get__NewEnum, :ptr
	STDMETHOD	get_Count, :ptr
INetSharingPublicConnectionCollectionVtbl ends
INetSharingPublicConnectionCollection struct
	lpVtbl		PVOID ?
INetSharingPublicConnectionCollection ends
endif

ifndef __INetSharingPrivateConnectionCollection_INTERFACE_DEFINED__
__INetSharingPrivateConnectionCollection_INTERFACE_DEFINED__ equ 1

externdef		IID_INetSharingPrivateConnectionCollection:IID
INetSharingPrivateConnectionCollectionVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	get__NewEnum, :ptr
	STDMETHOD	get_Count, :ptr
INetSharingPrivateConnectionCollectionVtbl ends
INetSharingPrivateConnectionCollection struct
	lpVtbl		PVOID ?
INetSharingPrivateConnectionCollection ends
endif

ifndef __INetSharingManager_INTERFACE_DEFINED__
__INetSharingManager_INTERFACE_DEFINED__ equ 1

externdef		IID_INetSharingManager:IID
INetSharingManagerVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	get_SharingInstalled, :ptr
	STDMETHOD	get_EnumPublicConnections, :SHARINGCONNECTION_ENUM_FLAGS, :ptr
	STDMETHOD	get_EnumPrivateConnections, :SHARINGCONNECTION_ENUM_FLAGS, :ptr
	STDMETHOD	get_INetSharingConfigurationForINetConnection, :ptr, :ptr
	STDMETHOD	get_EnumEveryConnection, :ptr
	STDMETHOD	get_NetConnectionProps, :ptr, :ptr
INetSharingManagerVtbl ends
INetSharingManager struct
	lpVtbl		PVOID ?
INetSharingManager ends
endif

ifndef __NETCONLib_LIBRARY_DEFINED__
__NETCONLib_LIBRARY_DEFINED__ equ 1

externdef		LIBID_NETCONLib:IID
externdef		CLSID_NetSharingManager:CLSID

ifdef __cplusplus

class DECLSPEC_UUID("5C63C1AD-3956-4FF8-8486-40034758315B")
NetSharingManager;
endif
endif


;DWORD
BSTR_UserSize proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr BSTR

;LPSTR
BSTR_UserMarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr BSTR

;LPSTR
BSTR_UserUnmarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr BSTR

;void
BSTR_UserFree proto WINAPI \
		      : ptr DWORD,
		      : ptr BSTR


;DWORD
HWND_UserSize proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr HWND

;LPSTR
HWND_UserMarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr HWND

;LPSTR
HWND_UserUnmarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr HWND

;void
HWND_UserFree proto WINAPI \
		      : ptr DWORD,
		      : ptr HWND


;DWORD
VARIANT_UserSize proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr VARIANT

;LPSTR
VARIANT_UserMarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr VARIANT

;LPSTR
VARIANT_UserUnmarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr VARIANT

;void
VARIANT_UserFree proto WINAPI \
		      : ptr DWORD,
		      : ptr VARIANT


;DWORD
BSTR_UserSize64 proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr BSTR

;LPSTR
BSTR_UserMarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr BSTR

;LPSTR
BSTR_UserUnmarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr BSTR

;void
BSTR_UserFree64 proto WINAPI \
		      : ptr DWORD,
		      : ptr BSTR


;DWORD
HWND_UserSize64 proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr HWND

;LPSTR
HWND_UserMarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr HWND

;LPSTR
HWND_UserUnmarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr HWND

;void
HWND_UserFree64 proto WINAPI \
		      : ptr DWORD,
		      : ptr HWND


;DWORD
VARIANT_UserSize64 proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr VARIANT

;LPSTR
VARIANT_UserMarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr VARIANT

;LPSTR
VARIANT_UserUnmarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr VARIANT

;void
VARIANT_UserFree64 proto WINAPI \
		      : ptr DWORD,
		      : ptr VARIANT

.list
endif
