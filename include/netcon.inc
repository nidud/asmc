.pragma list(push, 0)

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
__netcon_h__ equ <>

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

externdef		CLSID_ConnectionManager:CLSID
externdef		CLSID_NetSharingManager:CLSID

NETCON_MAX_NAME_LEN	equ 256

externdef		__MIDL_itf_netcon_0000_0000_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_netcon_0000_0000_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IEnumNetConnection_INTERFACE_DEFINED__
__IEnumNetConnection_INTERFACE_DEFINED__ equ 1

externdef		IID_IEnumNetConnection:IID
.comdef IEnumNetConnection
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
    .ends
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
.comdef INetConnection
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Connect		proc
    Disconnect		proc
    Delete		proc
    Duplicate		proc :LPCWSTR, :ptr
    GetProperties	proc :ptr
    GetUiObjectClassId	proc :ptr
    Rename		proc :LPCWSTR
    .ends
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
.comdef INetConnectionManager
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    EnumConnections	proc :NETCONMGR_ENUM_FLAGS, :ptr
    .ends
endif

ifndef __INetConnectionConnectUi_INTERFACE_DEFINED__
__INetConnectionConnectUi_INTERFACE_DEFINED__ equ 1

NETCONUI_CONNECT_FLAGS	typedef SDWORD
NCUC_DEFAULT		equ 0
NCUC_NO_UI		equ 0x1
NCUC_ENABLE_DISABLE	equ 0x2

externdef		IID_INetConnectionConnectUi:IID

.comdef INetConnectionConnectUi
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetConnection	proc :ptr
    Connect		proc :HWND, :DWORD
    Disconnect		proc :HWND, :DWORD
    .ends
endif

ifndef __IEnumNetSharingPortMapping_INTERFACE_DEFINED__
__IEnumNetSharingPortMapping_INTERFACE_DEFINED__ equ 1

externdef		IID_IEnumNetSharingPortMapping:IID
.comdef IEnumNetSharingPortMapping
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
    .ends
endif

ifndef __INetSharingPortMappingProps_INTERFACE_DEFINED__
__INetSharingPortMappingProps_INTERFACE_DEFINED__ equ 1

externdef		IID_INetSharingPortMappingProps:IID
.comdef INetSharingPortMappingProps
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Name		proc :ptr
    get_IPProtocol	proc :ptr
    get_ExternalPort	proc :ptr
    get_InternalPort	proc :ptr
    get_Options		proc :ptr
    get_TargetName	proc :ptr
    get_TargetIPAddress proc :ptr
    get_Enabled		proc :ptr
    .ends
endif

ifndef __INetSharingPortMapping_INTERFACE_DEFINED__
__INetSharingPortMapping_INTERFACE_DEFINED__ equ 1

externdef		IID_INetSharingPortMapping:IID
.comdef INetSharingPortMapping
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    Disable		proc
    Enable		proc
    get_Properties	proc :ptr
    Delete		proc
    .ends
endif

ifndef __IEnumNetSharingEveryConnection_INTERFACE_DEFINED__
__IEnumNetSharingEveryConnection_INTERFACE_DEFINED__ equ 1

externdef		IID_IEnumNetSharingEveryConnection:IID
.comdef IEnumNetSharingEveryConnection
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
    .ends
endif

ifndef __IEnumNetSharingPublicConnection_INTERFACE_DEFINED__
__IEnumNetSharingPublicConnection_INTERFACE_DEFINED__ equ 1

externdef		IID_IEnumNetSharingPublicConnection:IID
.comdef IEnumNetSharingPublicConnection
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
    .ends
endif

ifndef __IEnumNetSharingPrivateConnection_INTERFACE_DEFINED__
__IEnumNetSharingPrivateConnection_INTERFACE_DEFINED__ equ 1

externdef		IID_IEnumNetSharingPrivateConnection:IID
.comdef IEnumNetSharingPrivateConnection
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
    .ends
endif

ifndef __INetSharingPortMappingCollection_INTERFACE_DEFINED__
__INetSharingPortMappingCollection_INTERFACE_DEFINED__ equ 1

externdef		IID_INetSharingPortMappingCollection:IID

.comdef INetSharingPortMappingCollection
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get__NewEnum	proc :ptr
    get_Count		proc :ptr
    .ends
endif

externdef		__MIDL_itf_netcon_0000_0011_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_netcon_0000_0011_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __INetConnectionProps_INTERFACE_DEFINED__
__INetConnectionProps_INTERFACE_DEFINED__ equ 1

externdef		IID_INetConnectionProps:IID

.comdef INetConnectionProps
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Guid		proc :ptr
    get_Name		proc :ptr
    get_DeviceName	proc :ptr
    get_Status		proc :ptr
    get_MediaType	proc :ptr
    get_Characteristics proc :ptr
    .ends
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

.comdef INetSharingConfiguration
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_SharingEnabled	proc :ptr
    get_SharingConnectionType proc :ptr
    DisableSharing	proc
    EnableSharing	proc :SHARINGCONNECTIONTYPE
    get_InternetFirewallEnabled proc :ptr
    DisableInternetFirewall proc
    EnableInternetFirewall proc
    get_EnumPortMappings proc :SHARINGCONNECTION_ENUM_FLAGS, :ptr
    AddPortMapping	proc :BSTR, :UCHAR, :USHORT, :USHORT, :DWORD, :BSTR, :ICS_TARGETTYPE, :ptr
    RemovePortMapping	proc :ptr
    .ends
endif

ifndef __INetSharingEveryConnectionCollection_INTERFACE_DEFINED__
__INetSharingEveryConnectionCollection_INTERFACE_DEFINED__ equ 1

externdef		IID_INetSharingEveryConnectionCollection:IID

.comdef INetSharingEveryConnectionCollection
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get__NewEnum	proc :ptr
    get_Count		proc :ptr
    .ends
endif

ifndef __INetSharingPublicConnectionCollection_INTERFACE_DEFINED__
__INetSharingPublicConnectionCollection_INTERFACE_DEFINED__ equ 1

externdef		IID_INetSharingPublicConnectionCollection:IID
.comdef INetSharingPublicConnectionCollection
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get__NewEnum	proc :ptr
    get_Count		proc :ptr
    .ends
endif

ifndef __INetSharingPrivateConnectionCollection_INTERFACE_DEFINED__
__INetSharingPrivateConnectionCollection_INTERFACE_DEFINED__ equ 1

externdef		IID_INetSharingPrivateConnectionCollection:IID
.comdef INetSharingPrivateConnectionCollection
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get__NewEnum	proc :ptr
    get_Count		proc :ptr
    .ends
endif

ifndef __INetSharingManager_INTERFACE_DEFINED__
__INetSharingManager_INTERFACE_DEFINED__ equ 1

externdef		IID_INetSharingManager:IID
.comdef INetSharingManager
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_SharingInstalled proc :ptr
    get_EnumPublicConnections proc :SHARINGCONNECTION_ENUM_FLAGS, :ptr
    get_EnumPrivateConnections proc :SHARINGCONNECTION_ENUM_FLAGS, :ptr
    get_INetSharingConfigurationForINetConnection proc :ptr, :ptr
    get_EnumEveryConnection proc :ptr
    get_NetConnectionProps proc :ptr, :ptr
    .ends
endif

ifndef __NETCONLib_LIBRARY_DEFINED__
__NETCONLib_LIBRARY_DEFINED__ equ 1

externdef		LIBID_NETCONLib:IID
externdef		CLSID_NetSharingManager:CLSID

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

endif
.pragma list(pop)
