ifndef __REQUIRED_RPCNDR_H_VERSION__
__REQUIRED_RPCNDR_H_VERSION__ equ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
__REQUIRED_RPCSAL_H_VERSION__ equ 100
endif

include rpc.inc
include rpcndr.inc

ifndef __RPCNDR_H_VERSION__
.err<this stub requires an updated version of rpcndr.inc>
endif

ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif

ifndef __alg_h__
__alg_h__ equ <>

ifndef __IAdapterInfo_FWD_DEFINED__
__IAdapterInfo_FWD_DEFINED__ equ 1
endif
ifndef __IPendingProxyConnection_FWD_DEFINED__
__IPendingProxyConnection_FWD_DEFINED__ equ 1
endif
ifndef __IDataChannel_FWD_DEFINED__
__IDataChannel_FWD_DEFINED__ equ 1
endif
ifndef __IPersistentDataChannel_FWD_DEFINED__
__IPersistentDataChannel_FWD_DEFINED__ equ 1
endif
ifndef __IPrimaryControlChannel_FWD_DEFINED__
__IPrimaryControlChannel_FWD_DEFINED__ equ 1
endif
ifndef __ISecondaryControlChannel_FWD_DEFINED__
__ISecondaryControlChannel_FWD_DEFINED__ equ 1
endif
ifndef __IEnumAdapterInfo_FWD_DEFINED__
__IEnumAdapterInfo_FWD_DEFINED__ equ 1
endif
ifndef __IAdapterNotificationSink_FWD_DEFINED__
__IAdapterNotificationSink_FWD_DEFINED__ equ 1
endif
ifndef __IApplicationGatewayServices_FWD_DEFINED__
__IApplicationGatewayServices_FWD_DEFINED__ equ 1
endif
ifndef __IApplicationGateway_FWD_DEFINED__
__IApplicationGateway_FWD_DEFINED__ equ 1
endif
ifndef __ApplicationGatewayServices_FWD_DEFINED__
__ApplicationGatewayServices_FWD_DEFINED__ equ 1
endif
ifndef __PrimaryControlChannel_FWD_DEFINED__
__PrimaryControlChannel_FWD_DEFINED__ equ 1
endif
ifndef __SecondaryControlChannel_FWD_DEFINED__
__SecondaryControlChannel_FWD_DEFINED__ equ 1
endif
ifndef __AdapterInfo_FWD_DEFINED__
__AdapterInfo_FWD_DEFINED__ equ 1
endif
ifndef __EnumAdapterInfo_FWD_DEFINED__
__EnumAdapterInfo_FWD_DEFINED__ equ 1
endif
ifndef __PendingProxyConnection_FWD_DEFINED__
__PendingProxyConnection_FWD_DEFINED__ equ 1
endif
ifndef __DataChannel_FWD_DEFINED__
__DataChannel_FWD_DEFINED__ equ 1
endif
ifndef __PersistentDataChannel_FWD_DEFINED__
__PersistentDataChannel_FWD_DEFINED__ equ 1
endif

include oaidl.inc
include ocidl.inc

include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ALG_MAXIMUM_PORT_RANGE_SIZE equ ( 10 )

ALG_PROTOCOL		typedef SDWORD
eALG_TCP		equ 0x1
eALG_UDP		equ 0x2

ALG_CAPTURE		typedef SDWORD
eALG_SOURCE_CAPTURE	equ 0x1
eALG_DESTINATION_CAPTURE equ 0x2

ALG_DIRECTION		typedef SDWORD
eALG_INBOUND		equ 0x1
eALG_OUTBOUND		equ 0x2
eALG_BOTH		equ 0x3

ALG_ADAPTER_TYPE	typedef SDWORD
eALG_PRIVATE		equ 0x1
eALG_BOUNDARY		equ 0x2
eALG_FIREWALLED		equ 0x4

ALG_NOTIFICATION	typedef SDWORD
eALG_NONE		equ 0
eALG_SESSION_CREATION	equ 0x1
eALG_SESSION_DELETION	equ 0x2
eALG_SESSION_BOTH	equ 0x3

ALG_PRIMARY_CHANNEL_PROPERTIES STRUC
eProtocol		ALG_PROTOCOL ?
usCapturePort		USHORT ?
eCaptureType		ALG_CAPTURE ?
fCaptureInbound		BOOL ?
ulListeningAddress	ULONG ?
usListeningPort		USHORT ?
ulAdapterIndex		ULONG ?
ALG_PRIMARY_CHANNEL_PROPERTIES ENDS

ALG_SECONDARY_CHANNEL_PROPERTIES STRUC
eProtocol		ALG_PROTOCOL ?
ulPrivateAddress	ULONG ?
usPrivatePort		USHORT ?
ulPublicAddress		ULONG ?
usPublicPort		USHORT ?
ulRemoteAddress		ULONG ?
usRemotePort		USHORT ?
ulListenAddress		ULONG ?
usListenPort		USHORT ?
eDirection		ALG_DIRECTION ?
fPersistent		BOOL ?
ALG_SECONDARY_CHANNEL_PROPERTIES ENDS

ALG_DATA_CHANNEL_PROPERTIES STRUC
eProtocol		ALG_PROTOCOL ?
ulPrivateAddress	ULONG ?
usPrivatePort		USHORT ?
ulPublicAddress		ULONG ?
usPublicPort		USHORT ?
ulRemoteAddress		ULONG ?
usRemotePort		USHORT ?
eDirection		ALG_DIRECTION ?
eDesiredNotification	ALG_NOTIFICATION ?
ALG_DATA_CHANNEL_PROPERTIES ENDS

ALG_PERSISTENT_DATA_CHANNEL_PROPERTIES STRUC
eProtocol		ALG_PROTOCOL ?
ulPrivateAddress	ULONG ?
usPrivatePort		USHORT ?
ulPublicAddress		ULONG ?
usPublicPort		USHORT ?
ulRemoteAddress		ULONG ?
usRemotePort		USHORT ?
eDirection		ALG_DIRECTION ?
ALG_PERSISTENT_DATA_CHANNEL_PROPERTIES ENDS

externdef		__MIDL_itf_alg_0000_0000_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_alg_0000_0000_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IAdapterInfo_INTERFACE_DEFINED__
__IAdapterInfo_INTERFACE_DEFINED__ equ 1

externdef		IID_IAdapterInfo:IID

.comdef IAdapterInfo

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetAdapterIndex	proc :ptr
    GetAdapterType	proc :ptr
    GetAdapterAddresses proc :ptr, :ptr
    .ends

endif

ifndef __IPendingProxyConnection_INTERFACE_DEFINED__
__IPendingProxyConnection_INTERFACE_DEFINED__ equ 1

externdef		IID_IPendingProxyConnection:IID

.comdef IPendingProxyConnection

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Cancel		proc
    .ends

endif

ifndef __IDataChannel_INTERFACE_DEFINED__
__IDataChannel_INTERFACE_DEFINED__ equ 1

externdef		IID_IDataChannel:IID

.comdef IDataChannel

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Cancel		proc
    GetChannelProperties proc :ptr
    GetSessionCreationEventHandle proc :ptr
    GetSessionDeletionEventHandle proc :ptr
    .ends

endif

ifndef __IPersistentDataChannel_INTERFACE_DEFINED__
__IPersistentDataChannel_INTERFACE_DEFINED__ equ 1

externdef		IID_IPersistentDataChannel:IID

.comdef IPersistentDataChannel

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Cancel		proc
    GetChannelProperties proc :ptr
    .ends

endif

ifndef __IPrimaryControlChannel_INTERFACE_DEFINED__
__IPrimaryControlChannel_INTERFACE_DEFINED__ equ 1

externdef		IID_IPrimaryControlChannel:IID

.comdef IPrimaryControlChannel

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Cancel		proc
    GetChannelProperties proc :ptr
    GetOriginalDestinationInformation proc :ULONG, :USHORT, :ptr, :ptr, :ptr, :ptr, :ptr
    .ends

endif

ifndef __ISecondaryControlChannel_INTERFACE_DEFINED__
__ISecondaryControlChannel_INTERFACE_DEFINED__ equ 1

externdef		IID_ISecondaryControlChannel:IID

.comdef ISecondaryControlChannel

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Cancel		proc
    GetChannelProperties proc :ptr
    GetOriginalDestinationInformation proc :ULONG, :USHORT, :ptr, :ptr, :ptr
    .ends

endif

ifndef __IEnumAdapterInfo_INTERFACE_DEFINED__
__IEnumAdapterInfo_INTERFACE_DEFINED__ equ 1

externdef		IID_IEnumAdapterInfo:IID

.comdef IEnumAdapterInfo

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
    .ends

endif

ifndef __IAdapterNotificationSink_INTERFACE_DEFINED__
__IAdapterNotificationSink_INTERFACE_DEFINED__ equ 1

externdef		IID_IAdapterNotificationSink:IID

.comdef IAdapterNotificationSink

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    AdapterAdded	proc :ptr
    AdapterRemoved	proc :ptr
    AdapterModified	proc :ptr
    AdapterUpdatePortMapping proc :ptr
    .ends

endif

ifndef __IApplicationGatewayServices_INTERFACE_DEFINED__
__IApplicationGatewayServices_INTERFACE_DEFINED__ equ 1

externdef		IID_IApplicationGatewayServices:IID

.comdef IApplicationGatewayServices

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    CreatePrimaryControlChannel proc :ULONG, :ALG_PROTOCOL, :USHORT, :ALG_CAPTURE, :BOOL, :ULONG, :USHORT, :ptr
    CreateSecondaryControlChannel proc :ALG_PROTOCOL, :ULONG, :USHORT, :ULONG, :USHORT, :ULONG, :USHORT, :ULONG, :USHORT, :ALG_DIRECTION, :BOOL, :ptr
    GetBestSourceAddressForDestinationAddress proc :ULONG, :BOOL, :ptr
    PrepareProxyConnection proc :ALG_PROTOCOL, :ULONG, :USHORT, :ULONG, :USHORT, :BOOL, :ptr
    PrepareSourceModifiedProxyConnection proc :ALG_PROTOCOL, :ULONG, :USHORT, :ULONG, :USHORT, :ULONG, :USHORT, :ptr
    CreateDataChannel	proc :ALG_PROTOCOL, :ULONG, :USHORT, :ULONG, :USHORT, :ULONG, :USHORT, :ALG_DIRECTION, :ALG_NOTIFICATION, :BOOL, :ptr
    CreatePersistentDataChannel proc :ALG_PROTOCOL, :ULONG, :USHORT, :ULONG, :USHORT, :ULONG, :USHORT, :ALG_DIRECTION, :ptr
    ReservePort		proc :USHORT, :ptr
    ReleaseReservedPort proc :USHORT, :USHORT
    EnumerateAdapters	proc :ptr
    StartAdapterNotifications proc :ptr, :ptr
    StopAdapterNotifications proc :DWORD
    LookupAdapterPortMapping proc :ULONG, :UCHAR, :ULONG, :USHORT, :ptr, :ptr
    .ends

endif

ifndef __IApplicationGateway_INTERFACE_DEFINED__
__IApplicationGateway_INTERFACE_DEFINED__ equ 1

externdef		IID_IApplicationGateway:IID

.comdef IApplicationGateway

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Initialize		proc :ptr
    Stop		proc
    .ends

endif

ifndef __ALGLib_LIBRARY_DEFINED__
__ALGLib_LIBRARY_DEFINED__ equ 1

externdef		LIBID_ALGLib:IID
externdef		CLSID_ApplicationGatewayServices:CLSID
externdef		CLSID_PrimaryControlChannel:CLSID
externdef		CLSID_SecondaryControlChannel:CLSID
externdef		CLSID_AdapterInfo:CLSID
externdef		CLSID_EnumAdapterInfo:CLSID
externdef		CLSID_PendingProxyConnection:CLSID
externdef		CLSID_DataChannel:CLSID
externdef		CLSID_PersistentDataChannel:CLSID

endif

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

externdef		__MIDL_itf_alg_0000_0011_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_alg_0000_0011_v0_0_s_ifspec:RPC_IF_HANDLE

endif
