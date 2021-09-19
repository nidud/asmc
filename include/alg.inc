ifndef __REQUIRED_RPCNDR_H_VERSION__
define __REQUIRED_RPCNDR_H_VERSION__ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
define __REQUIRED_RPCSAL_H_VERSION__ 100
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
define __alg_h__

include oaidl.inc
include ocidl.inc

include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ALG_MAXIMUM_PORT_RANGE_SIZE equ ( 10 )

.enum ALG_PROTOCOL {
    eALG_TCP	= 0x1,
    eALG_UDP	= 0x2
    }
.enum ALG_CAPTURE {
    eALG_SOURCE_CAPTURE = 0x1,
    eALG_DESTINATION_CAPTURE = 0x2
    }
.enum ALG_DIRECTION {
    eALG_INBOUND	= 0x1,
    eALG_OUTBOUND	= 0x2,
    eALG_BOTH	= 0x3
    }
.enum ALG_ADAPTER_TYPE {
    eALG_PRIVATE	= 0x1,
    eALG_BOUNDARY	= 0x2,
    eALG_FIREWALLED = 0x4
    }
.enum ALG_NOTIFICATION {
    eALG_NONE	= 0,
    eALG_SESSION_CREATION = 0x1,
    eALG_SESSION_DELETION = 0x2,
    eALG_SESSION_BOTH = 0x3
    }

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

ifndef __IAdapterInfo_INTERFACE_DEFINED__
define __IAdapterInfo_INTERFACE_DEFINED__

DEFINE_IIDX(IAdapterInfo, "480BF94A-09FD-4F8A-A3E0-B0700282D84D")

.comdef IAdapterInfo : public IUnknown

    GetAdapterIndex	proc :ptr
    GetAdapterType	proc :ptr
    GetAdapterAddresses proc :ptr, :ptr
   .ends

endif

ifndef __IPendingProxyConnection_INTERFACE_DEFINED__
define __IPendingProxyConnection_INTERFACE_DEFINED__

DEFINE_IIDX(IPendingProxyConnection, "B68E5043-3E3D-4CC2-B9C1-5F8F88FEE81C")

.comdef IPendingProxyConnection : public IUnknown

    Cancel		proc
   .ends

endif

ifndef __IDataChannel_INTERFACE_DEFINED__
define __IDataChannel_INTERFACE_DEFINED__

DEFINE_IIDX(IDataChannel, "AD42D12A-4AD0-4856-919E-E854C91D1856")

.comdef IDataChannel : public IUnknown

    Cancel		proc
    GetChannelProperties proc :ptr
    GetSessionCreationEventHandle proc :ptr
    GetSessionDeletionEventHandle proc :ptr
   .ends

endif

ifndef __IPersistentDataChannel_INTERFACE_DEFINED__
define __IPersistentDataChannel_INTERFACE_DEFINED__

DEFINE_IIDX(IPersistentDataChannel, "A180E934-D92A-415D-9144-759F8054E8F6")

.comdef IPersistentDataChannel : public IUnknown

    Cancel		proc
    GetChannelProperties proc :ptr
   .ends

endif

ifndef __IPrimaryControlChannel_INTERFACE_DEFINED__
define __IPrimaryControlChannel_INTERFACE_DEFINED__

DEFINE_IIDX(IPrimaryControlChannel, "1A2E8B62-9012-4BE6-84AE-32BD66BA657A")

.comdef IPrimaryControlChannel : public IUnknown

    Cancel		proc
    GetChannelProperties proc :ptr
    GetOriginalDestinationInformation proc :ULONG, :USHORT, :ptr, :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef __ISecondaryControlChannel_INTERFACE_DEFINED__
define __ISecondaryControlChannel_INTERFACE_DEFINED__

DEFINE_IIDX(ISecondaryControlChannel, "A23F9D10-714C-41FE-8471-FFB19BC28454")

.comdef ISecondaryControlChannel : public IUnknown

    Cancel		proc
    GetChannelProperties proc :ptr
    GetOriginalDestinationInformation proc :ULONG, :USHORT, :ptr, :ptr, :ptr
   .ends

endif

ifndef __IEnumAdapterInfo_INTERFACE_DEFINED__
define __IEnumAdapterInfo_INTERFACE_DEFINED__

DEFINE_IIDX(IEnumAdapterInfo, "A23F9D11-714C-41FE-8471-FFB19BC28454")

.comdef IEnumAdapterInfo : public IUnknown

    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
   .ends

endif

ifndef __IAdapterNotificationSink_INTERFACE_DEFINED__
define __IAdapterNotificationSink_INTERFACE_DEFINED__

DEFINE_IIDX(IAdapterNotificationSink, "44AB2DC3-23B2-47DE-8228-2E1CCEEB9911")

.comdef IAdapterNotificationSink : public IUnknown

    AdapterAdded	proc :ptr
    AdapterRemoved	proc :ptr
    AdapterModified	proc :ptr
    AdapterUpdatePortMapping proc :ptr
   .ends

endif

ifndef __IApplicationGatewayServices_INTERFACE_DEFINED__
define __IApplicationGatewayServices_INTERFACE_DEFINED__

DEFINE_IIDX(IApplicationGatewayServices, "5134842A-FDCE-485D-93CD-DE1640643BBE")

.comdef IApplicationGatewayServices : public IUnknown

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
define __IApplicationGateway_INTERFACE_DEFINED__

DEFINE_IIDX(IApplicationGateway, "5134842B-FDCE-485D-93CD-DE1640643BBE")

.comdef IApplicationGateway : public IUnknown

    Initialize		proc :ptr
    Stop		proc
   .ends

endif

ifndef __ALGLib_LIBRARY_DEFINED__
define __ALGLib_LIBRARY_DEFINED__

externdef LIBID_ALGLib:IID
DEFINE_GUIDS(CLSID_ApplicationGatewayServices, "F8ADE1D3-49DF-4B75-9005-EF9508E6A337")
DEFINE_GUIDS(CLSID_PrimaryControlChannel, "3CEB5509-C1CD-432F-9D8F-65D1E286AA80")
DEFINE_GUIDS(CLSID_SecondaryControlChannel, "7B3181A0-C92F-4567-B0FA-CD9A10ECD7D1")
DEFINE_GUIDS(CLSID_AdapterInfo, "6F9942C9-C1B1-4AB5-93DA-6058991DC8F3")
DEFINE_GUIDS(CLSID_EnumAdapterInfo, "6F9942CA-C1B1-4AB5-93DA-6058991DC8F3")
DEFINE_GUIDS(CLSID_PendingProxyConnection, "D8A68E5E-2B37-426C-A329-C117C14C429E")
DEFINE_GUIDS(CLSID_DataChannel, "BBB36F15-408D-4056-8C27-920843D40BE5")
DEFINE_GUIDS(CLSID_PersistentDataChannel, "BC9B54AB-7883-4C13-909F-033D03267990")

endif

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

endif
