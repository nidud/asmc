ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __NETCON_INC
define __NETCON_INC

ifndef __oaidl_h__
include oaidl.inc
endif
include prsht.inc

externdef CLSID_ConnectionManager:CLSID
externdef CLSID_NetSharingManager:CLSID

NETCON_MAX_NAME_LEN equ 256

ifndef __IEnumNetConnection_INTERFACE_DEFINED__
define __IEnumNetConnection_INTERFACE_DEFINED__

DEFINE_IIDX(IEnumNetConnection, "C08956A0-1CD3-11D1-B1C5-00805FC1270E")

.comdef IEnumNetConnection : public IUnknown

    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
   .ends
endif

ifndef __INetConnection_INTERFACE_DEFINED__
define __INetConnection_INTERFACE_DEFINED__

.enum NETCON_CHARACTERISTIC_FLAGS {
	NCCF_NONE		= 0,
	NCCF_ALL_USERS		= 0x1,
	NCCF_ALLOW_DUPLICATION	= 0x2,
	NCCF_ALLOW_REMOVAL	= 0x4,
	NCCF_ALLOW_RENAME	= 0x8,
	NCCF_INCOMING_ONLY	= 0x20,
	NCCF_OUTGOING_ONLY	= 0x40,
	NCCF_BRANDED		= 0x80,
	NCCF_SHARED		= 0x100,
	NCCF_BRIDGED		= 0x200,
	NCCF_FIREWALLED		= 0x400,
	NCCF_DEFAULT		= 0x800,
	NCCF_HOMENET_CAPABLE	= 0x1000,
	NCCF_SHARED_PRIVATE	= 0x2000,
	NCCF_QUARANTINED	= 0x4000,
	NCCF_RESERVED		= 0x8000,
	NCCF_HOSTED_NETWORK	= 0x10000,
	NCCF_VIRTUAL_STATION	= 0x20000,
	NCCF_BLUETOOTH_MASK	= 0xf0000,
	NCCF_LAN_MASK		= 0xf00000
    }

.enum NETCON_STATUS {
	NCS_DISCONNECTED,
	NCS_CONNECTING,
	NCS_CONNECTED,
	NCS_DISCONNECTING,
	NCS_HARDWARE_NOT_PRESENT,
	NCS_HARDWARE_DISABLED,
	NCS_HARDWARE_MALFUNCTION,
	NCS_MEDIA_DISCONNECTED,
	NCS_AUTHENTICATING,
	NCS_AUTHENTICATION_SUCCEEDED,
	NCS_AUTHENTICATION_FAILED,
	NCS_INVALID_ADDRESS,
	NCS_CREDENTIALS_REQUIRED
	}

.enum NETCON_TYPE {
	NCT_DIRECT_CONNECT,
	NCT_INBOUND,
	NCT_INTERNET,
	NCT_LAN,
	NCT_PHONE,
	NCT_TUNNEL,
	NCT_BRIDGE
	}

.enum NETCON_MEDIATYPE {
	NCM_NONE,
	NCM_DIRECT,
	NCM_ISDN,
	NCM_LAN,
	NCM_PHONE,
	NCM_TUNNEL,
	NCM_PPPOE,
	NCM_BRIDGE,
	NCM_SHAREDACCESSHOST_LAN,
	NCM_SHAREDACCESSHOST_RAS
	}


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

DEFINE_IIDX(INetConnection, "C08956A1-1CD3-11D1-B1C5-00805FC1270E")

.comdef INetConnection : public IUnknown

    Connect		proc
    Disconnect		proc
    Delete		proc
    Duplicate		proc :LPCWSTR, :ptr
    GetProperties	proc :ptr
    GetUiObjectClassId	proc :ptr
    Rename		proc :LPCWSTR
   .ends
endif

NcFreeNetconProperties proto WINAPI :ptr
NcIsValidConnectionName proto WINAPI :PCWSTR

ifndef __INetConnectionManager_INTERFACE_DEFINED__
define __INetConnectionManager_INTERFACE_DEFINED__


NETCONMGR_ENUM_FLAGS	typedef SDWORD
NCME_DEFAULT		equ 0
NCME_HIDDEN		equ 0x1

DEFINE_IIDX(INetConnectionManager, "C08956A2-1CD3-11D1-B1C5-00805FC1270E")

.comdef INetConnectionManager : public IUnknown

    EnumConnections	proc :NETCONMGR_ENUM_FLAGS, :ptr
   .ends

endif

ifndef __INetConnectionConnectUi_INTERFACE_DEFINED__
define __INetConnectionConnectUi_INTERFACE_DEFINED__

NETCONUI_CONNECT_FLAGS	typedef SDWORD
NCUC_DEFAULT		equ 0
NCUC_NO_UI		equ 0x1
NCUC_ENABLE_DISABLE	equ 0x2

DEFINE_IIDX(INetConnectionConnectUi, "C08956A3-1CD3-11D1-B1C5-00805FC1270E")

.comdef INetConnectionConnectUi : public IUnknown

    SetConnection	proc :ptr
    Connect		proc :HWND, :DWORD
    Disconnect		proc :HWND, :DWORD
   .ends

endif

ifndef __IEnumNetSharingPortMapping_INTERFACE_DEFINED__
define __IEnumNetSharingPortMapping_INTERFACE_DEFINED__

DEFINE_IIDX(IEnumNetSharingPortMapping, "C08956B0-1CD3-11D1-B1C5-00805FC1270E")

.comdef IEnumNetSharingPortMapping : public IUnknown

    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
   .ends

endif

ifndef __INetSharingPortMappingProps_INTERFACE_DEFINED__
define __INetSharingPortMappingProps_INTERFACE_DEFINED__

DEFINE_IIDX(INetSharingPortMappingProps, "24B7E9B5-E38F-4685-851B-00892CF5F940")

.comdef INetSharingPortMappingProps : public IDispatch

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
define __INetSharingPortMapping_INTERFACE_DEFINED__

DEFINE_IIDX(INetSharingPortMapping, "C08956B1-1CD3-11D1-B1C5-00805FC1270E")

.comdef INetSharingPortMapping : public IDispatch

    Disable		proc
    Enable		proc
    get_Properties	proc :ptr
    Delete		proc
   .ends

endif

ifndef __IEnumNetSharingEveryConnection_INTERFACE_DEFINED__
define __IEnumNetSharingEveryConnection_INTERFACE_DEFINED__

DEFINE_IIDX(IEnumNetSharingEveryConnection, "C08956B8-1CD3-11D1-B1C5-00805FC1270E")

.comdef IEnumNetSharingEveryConnection : public IUnknown

    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
   .ends

endif

ifndef __IEnumNetSharingPublicConnection_INTERFACE_DEFINED__
define __IEnumNetSharingPublicConnection_INTERFACE_DEFINED__

DEFINE_IIDX(IEnumNetSharingPublicConnection, "C08956B4-1CD3-11D1-B1C5-00805FC1270E")

.comdef IEnumNetSharingPublicConnection : public IUnknown

    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
   .ends

endif

ifndef __IEnumNetSharingPrivateConnection_INTERFACE_DEFINED__
define __IEnumNetSharingPrivateConnection_INTERFACE_DEFINED__

DEFINE_IIDX(IEnumNetSharingPrivateConnection, "C08956B5-1CD3-11D1-B1C5-00805FC1270E")

.comdef IEnumNetSharingPrivateConnection : public IUnknown

    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
   .ends

endif

ifndef __INetSharingPortMappingCollection_INTERFACE_DEFINED__
define __INetSharingPortMappingCollection_INTERFACE_DEFINED__

DEFINE_IIDX(INetSharingPortMappingCollection, "02E4A2DE-DA20-4E34-89C8-AC22275A010B")

.comdef INetSharingPortMappingCollection : public IDispatch

    get__NewEnum	proc :ptr
    get_Count		proc :ptr
   .ends

endif

ifndef __INetConnectionProps_INTERFACE_DEFINED__
define __INetConnectionProps_INTERFACE_DEFINED__

DEFINE_IIDX(INetConnectionProps, "F4277C95-CE5B-463D-8167-5662D9BCAA72")

.comdef INetConnectionProps : public IDispatch

    get_Guid		proc :ptr
    get_Name		proc :ptr
    get_DeviceName	proc :ptr
    get_Status		proc :ptr
    get_MediaType	proc :ptr
    get_Characteristics proc :ptr
   .ends

endif

ifndef __INetSharingConfiguration_INTERFACE_DEFINED__
define __INetSharingConfiguration_INTERFACE_DEFINED__

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

DEFINE_IIDX(INetSharingConfiguration, "C08956B6-1CD3-11D1-B1C5-00805FC1270E")

.comdef INetSharingConfiguration : public IDispatch

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
define __INetSharingEveryConnectionCollection_INTERFACE_DEFINED_

DEFINE_IIDX(INetSharingEveryConnectionCollection, "33C4643C-7811-46FA-A89A-768597BD7223")

.comdef INetSharingEveryConnectionCollection : public IDispatch

    get__NewEnum	proc :ptr
    get_Count		proc :ptr
   .ends

endif

ifndef __INetSharingPublicConnectionCollection_INTERFACE_DEFINED__
define __INetSharingPublicConnectionCollection_INTERFACE_DEFINED__

DEFINE_IIDX(INetSharingPublicConnectionCollection, "7D7A6355-F372-4971-A149-BFC927BE762A")

.comdef INetSharingPublicConnectionCollection : public IDispatch

    get__NewEnum	proc :ptr
    get_Count		proc :ptr
   .ends

endif

ifndef __INetSharingPrivateConnectionCollection_INTERFACE_DEFINED__
define __INetSharingPrivateConnectionCollection_INTERFACE_DEFINED__

DEFINE_IIDX(INetSharingPrivateConnectionCollection, "38AE69E0-4409-402A-A2CB-E965C727F840")

.comdef INetSharingPrivateConnectionCollection : public IDispatch

    get__NewEnum	proc :ptr
    get_Count		proc :ptr
   .ends

endif

ifndef __INetSharingManager_INTERFACE_DEFINED__
define __INetSharingManager_INTERFACE_DEFINED__

DEFINE_IIDX(INetSharingManager, "C08956B7-1CD3-11D1-B1C5-00805FC1270E")

.comdef INetSharingManager : public IDispatch

    get_SharingInstalled proc :ptr
    get_EnumPublicConnections proc :SHARINGCONNECTION_ENUM_FLAGS, :ptr
    get_EnumPrivateConnections proc :SHARINGCONNECTION_ENUM_FLAGS, :ptr
    get_INetSharingConfigurationForINetConnection proc :ptr, :ptr
    get_EnumEveryConnection proc :ptr
    get_NetConnectionProps proc :ptr, :ptr
   .ends

endif

ifndef __NETCONLib_LIBRARY_DEFINED__
define __NETCONLib_LIBRARY_DEFINED__

externdef LIBID_NETCONLib:IID
DEFINE_GUIDS(CLSID_NetSharingManager, "5C63C1AD-3956-4FF8-8486-40034758315B")

endif

endif
