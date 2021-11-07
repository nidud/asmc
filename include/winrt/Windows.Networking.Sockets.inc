ifndef __REQUIRED_RPCNDR_H_VERSION__
define __REQUIRED_RPCNDR_H_VERSION__ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
define __REQUIRED_RPCSAL_H_VERSION__ 100
endif

include rpc.inc
include rpcndr.inc
ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr.h>
endif
ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif

ifndef __windows2Enetworking2Esockets_h__
define __windows2Enetworking2Esockets_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include Windows.ApplicationModel.Background.inc
include Windows.Networking.inc
include Windows.Security.Credentials.inc
include Windows.Security.Cryptography.Certificates.inc
include Windows.Web.inc
include windows.foundation.collections.inc

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CNetworking__CSockets__CStreamSocket_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CNetworking__CSockets__CStreamSocket_INTERFACE_DEFINED__

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CNetworking__CSockets__CStreamSocket : public IUnknown
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CNetworking__CSockets__CStreamSocket, "71b5d99e-3854-5e9a-b4dc-d1b58bf198fc")

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CNetworking__CSockets__CStreamSocket_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CNetworking__CSockets__CStreamSocket_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CNetworking__CSockets__CStreamSocket, "fb3e3d3c-6fe5-5e27-a132-902247e2a93e")

.comdef __FIAsyncOperation_1_Windows__CNetworking__CSockets__CStreamSocket : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CNetworking__CSockets__CDatagramSocket_Windows__CNetworking__CSockets__CDatagramSocketMessageReceivedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CNetworking__CSockets__CDatagramSocket_Windows__CNetworking__CSockets__CDatagramSocketMessageReceivedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CNetworking__CSockets__CDatagramSocket_Windows__CNetworking__CSockets__CDatagramSocketMessageReceivedEventArgs, "4482e19b-2389-5767-9b0b-8d7a8ef55743")

.comdef __FITypedEventHandler_2_Windows__CNetworking__CSockets__CDatagramSocket_Windows__CNetworking__CSockets__CDatagramSocketMessageReceivedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CNetworking__CSockets__CIWebSocket_Windows__CNetworking__CSockets__CWebSocketClosedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CNetworking__CSockets__CIWebSocket_Windows__CNetworking__CSockets__CWebSocketClosedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CNetworking__CSockets__CIWebSocket_Windows__CNetworking__CSockets__CWebSocketClosedEventArgs, "03cf8f90-1669-5f4d-9404-2b784678e6dd")

.comdef __FITypedEventHandler_2_Windows__CNetworking__CSockets__CIWebSocket_Windows__CNetworking__CSockets__CWebSocketClosedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CNetworking__CSockets__CMessageWebSocket_Windows__CNetworking__CSockets__CMessageWebSocketMessageReceivedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CNetworking__CSockets__CMessageWebSocket_Windows__CNetworking__CSockets__CMessageWebSocketMessageReceivedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CNetworking__CSockets__CMessageWebSocket_Windows__CNetworking__CSockets__CMessageWebSocketMessageReceivedEventArgs, "de980538-6dcd-52b0-802f-4b6cf59a01ab")

.comdef __FITypedEventHandler_2_Windows__CNetworking__CSockets__CMessageWebSocket_Windows__CNetworking__CSockets__CMessageWebSocketMessageReceivedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CNetworking__CSockets__CStreamSocketListener_Windows__CNetworking__CSockets__CStreamSocketListenerConnectionReceivedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CNetworking__CSockets__CStreamSocketListener_Windows__CNetworking__CSockets__CStreamSocketListenerConnectionReceivedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CNetworking__CSockets__CStreamSocketListener_Windows__CNetworking__CSockets__CStreamSocketListenerConnectionReceivedEventArgs, "33d00d41-c94f-5a61-9ab7-280dcefa0b08")

.comdef __FITypedEventHandler_2_Windows__CNetworking__CSockets__CStreamSocketListener_Windows__CNetworking__CSockets__CStreamSocketListenerConnectionReceivedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

.namespace Windows
.namespace Networking
.namespace Sockets

.enum ControlChannelTriggerStatus {
    ControlChannelTriggerStatus_HardwareSlotRequested	= 0,
    ControlChannelTriggerStatus_SoftwareSlotAllocated	= 1,
    ControlChannelTriggerStatus_HardwareSlotAllocated	= 2,
    ControlChannelTriggerStatus_PolicyError	= 3,
    ControlChannelTriggerStatus_SystemError	= 4,
    ControlChannelTriggerStatus_TransportDisconnected	= 5,
    ControlChannelTriggerStatus_ServiceUnavailable	= 6
    }

.enum ControlChannelTriggerResourceType {
    ControlChannelTriggerResourceType_RequestSoftwareSlot	= 0,
    ControlChannelTriggerResourceType_RequestHardwareSlot	= 1
    }

.enum ControlChannelTriggerResetReason {
    ControlChannelTriggerResetReason_FastUserSwitched	= 0,
    ControlChannelTriggerResetReason_LowPowerExit	= 1,
    ControlChannelTriggerResetReason_QuietHoursExit	= 2,
    ControlChannelTriggerResetReason_ApplicationRestart = 3
    }

.enum SocketMessageType {
    SocketMessageType_Binary	= 0,
    SocketMessageType_Utf8	= 1
    }

.enum SocketProtectionLevel {
    SocketProtectionLevel_PlainSocket	= 0,
    SocketProtectionLevel_Ssl	= 1,
    SocketProtectionLevel_SslAllowNullEncryption	= 2,
    SocketProtectionLevel_BluetoothEncryptionAllowNullAuthentication	= 3,
    SocketProtectionLevel_BluetoothEncryptionWithAuthentication = 4,
    SocketProtectionLevel_Ssl3AllowWeakEncryption	= 5,
    SocketProtectionLevel_Tls10 = 6,
    SocketProtectionLevel_Tls11 = 7,
    SocketProtectionLevel_Tls12 = 8
    }

.enum SocketQualityOfService {
    SocketQualityOfService_Normal	= 0,
    SocketQualityOfService_LowLatency	= 1
    }

.enum SocketErrorStatus {
    SocketErrorStatus_Unknown	= 0,
    SocketErrorStatus_OperationAborted	= 1,
    SocketErrorStatus_HttpInvalidServerResponse = 2,
    SocketErrorStatus_ConnectionTimedOut	= 3,
    SocketErrorStatus_AddressFamilyNotSupported = 4,
    SocketErrorStatus_SocketTypeNotSupported	= 5,
    SocketErrorStatus_HostNotFound	= 6,
    SocketErrorStatus_NoDataRecordOfRequestedType	= 7,
    SocketErrorStatus_NonAuthoritativeHostNotFound	= 8,
    SocketErrorStatus_ClassTypeNotFound = 9,
    SocketErrorStatus_AddressAlreadyInUse	= 10,
    SocketErrorStatus_CannotAssignRequestedAddress	= 11,
    SocketErrorStatus_ConnectionRefused = 12,
    SocketErrorStatus_NetworkIsUnreachable	= 13,
    SocketErrorStatus_UnreachableHost	= 14,
    SocketErrorStatus_NetworkIsDown	= 15,
    SocketErrorStatus_NetworkDroppedConnectionOnReset	= 16,
    SocketErrorStatus_SoftwareCausedConnectionAbort	= 17,
    SocketErrorStatus_ConnectionResetByPeer	= 18,
    SocketErrorStatus_HostIsDown	= 19,
    SocketErrorStatus_NoAddressesFound	= 20,
    SocketErrorStatus_TooManyOpenFiles	= 21,
    SocketErrorStatus_MessageTooLong	= 22,
    SocketErrorStatus_CertificateExpired	= 23,
    SocketErrorStatus_CertificateUntrustedRoot	= 24,
    SocketErrorStatus_CertificateCommonNameIsIncorrect	= 25,
    SocketErrorStatus_CertificateWrongUsage	= 26,
    SocketErrorStatus_CertificateRevoked	= 27,
    SocketErrorStatus_CertificateNoRevocationCheck	= 28,
    SocketErrorStatus_CertificateRevocationServerOffline	= 29,
    SocketErrorStatus_CertificateIsInvalid	= 30
    }

.enum SocketSslErrorSeverity {
    SocketSslErrorSeverity_None = 0,
    SocketSslErrorSeverity_Ignorable	= 1,
    SocketSslErrorSeverity_Fatal	= 2
    }

.template RoundTripTimeStatistics
    Variance		UINT32 ?
    Max			UINT32 ?
    Min			UINT32 ?
    Sum			UINT32 ?
   .ends

.template BandwidthStatistics
    OutboundBitsPerSecond UINT64 ?
    InboundBitsPerSecond UINT64 ?
    OutboundBitsPerSecondInstability UINT64 ?
    InboundBitsPerSecondInstability UINT64 ?
    OutboundBandwidthPeaked boolean ?
    InboundBandwidthPeaked boolean ?
   .ends

ifndef ____x_ABI_CWindows_CNetworking_CSockets_CIControlChannelTrigger_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CSockets_CIControlChannelTrigger_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Sockets_IControlChannelTrigger <L"Windows.Networking.Sockets.IControlChannelTrigger">
DEFINE_IIDX(IControlChannelTrigger, "7D1431A7-EE96-40E8-A199-8703CD969EC3")

.comdef IControlChannelTrigger : public IInspectable

    get_ControlChannelTriggerId proc :ptr
    get_ServerKeepAliveIntervalInMinutes proc :ptr
    put_ServerKeepAliveIntervalInMinutes proc :UINT32
    get_CurrentKeepAliveIntervalInMinutes proc :ptr
    get_TransportObject proc :ptr
    get_KeepAliveTrigger proc :ptr
    get_PushNotificationTrigger proc :ptr
    UsingTransport	proc :ptr
    WaitForPushEnabled	proc :ptr
    DecreaseNetworkKeepAliveInterval proc
    FlushTransport	proc
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CSockets_CIControlChannelTriggerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CSockets_CIControlChannelTriggerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Sockets_IControlChannelTriggerFactory <L"Windows.Networking.Sockets.IControlChannelTriggerFactory">
DEFINE_IIDX(IControlChannelTriggerFactory, "DA4B7CF0-8D71-446F-88C3-B95184A2D6CD")

.comdef IControlChannelTriggerFactory : public IInspectable

    CreateControlChannelTrigger proc :HSTRING, :UINT32, :ptr
    CreateControlChannelTriggerEx proc :HSTRING, :UINT32, :Windows::Networking::Sockets::ControlChannelTriggerResourceType, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CSockets_CIControlChannelTriggerEventDetails_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CSockets_CIControlChannelTriggerEventDetails_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Sockets_IControlChannelTriggerEventDetails <L"Windows.Networking.Sockets.IControlChannelTriggerEventDetails">
DEFINE_IIDX(IControlChannelTriggerEventDetails, "1B36E047-89BB-4236-96AC-71D012BB4869")

.comdef IControlChannelTriggerEventDetails : public IInspectable

    get_ControlChannelTrigger proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CSockets_CIControlChannelTriggerResetEventDetails_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CSockets_CIControlChannelTriggerResetEventDetails_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Sockets_IControlChannelTriggerResetEventDetails <L"Windows.Networking.Sockets.IControlChannelTriggerResetEventDetails">
DEFINE_IIDX(IControlChannelTriggerResetEventDetails, "6851038E-8EC4-42FE-9BB2-21E91B7BFCB1")

.comdef IControlChannelTriggerResetEventDetails : public IInspectable

    get_ResetReason	proc :ptr
    get_HardwareSlotReset proc :ptr
    get_SoftwareSlotReset proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CSockets_CIDatagramSocketMessageReceivedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CSockets_CIDatagramSocketMessageReceivedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Sockets_IDatagramSocketMessageReceivedEventArgs <L"Windows.Networking.Sockets.IDatagramSocketMessageReceivedEventArgs">
DEFINE_IIDX(IDatagramSocketMessageReceivedEventArgs, "9E2DDCA2-1712-4CE4-B179-8C652C6D107E")

.comdef IDatagramSocketMessageReceivedEventArgs : public IInspectable

    get_RemoteAddress	proc :ptr
    get_RemotePort	proc :ptr
    get_LocalAddress	proc :ptr
    GetDataReader	proc :ptr
    GetDataStream	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CSockets_CIMessageWebSocketMessageReceivedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CSockets_CIMessageWebSocketMessageReceivedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Sockets_IMessageWebSocketMessageReceivedEventArgs <L"Windows.Networking.Sockets.IMessageWebSocketMessageReceivedEventArgs">
DEFINE_IIDX(IMessageWebSocketMessageReceivedEventArgs, "478C22AC-4C4B-42ED-9ED7-1EF9F94FA3D5")

.comdef IMessageWebSocketMessageReceivedEventArgs : public IInspectable

    get_MessageType	proc :ptr
    GetDataReader	proc :ptr
    GetDataStream	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CSockets_CIWebSocketClosedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CSockets_CIWebSocketClosedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Sockets_IWebSocketClosedEventArgs <L"Windows.Networking.Sockets.IWebSocketClosedEventArgs">
DEFINE_IIDX(IWebSocketClosedEventArgs, "CEB78D07-D0A8-4703-A091-C8C2C0915BC3")

.comdef IWebSocketClosedEventArgs : public IInspectable

    get_Code		proc :ptr
    get_Reason		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CSockets_CIDatagramSocketInformation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CSockets_CIDatagramSocketInformation_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Sockets_IDatagramSocketInformation <L"Windows.Networking.Sockets.IDatagramSocketInformation">
DEFINE_IIDX(IDatagramSocketInformation, "5F1A569A-55FB-48CD-9706-7A974F7B1585")

.comdef IDatagramSocketInformation : public IInspectable

    get_LocalAddress	proc :ptr
    get_LocalPort	proc :ptr
    get_RemoteAddress	proc :ptr
    get_RemotePort	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CSockets_CIDatagramSocketControl_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CSockets_CIDatagramSocketControl_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Sockets_IDatagramSocketControl <L"Windows.Networking.Sockets.IDatagramSocketControl">
DEFINE_IIDX(IDatagramSocketControl, "52AC3F2E-349A-4135-BB58-B79B2647D390")

.comdef IDatagramSocketControl : public IInspectable

    get_QualityOfService proc :ptr
    put_QualityOfService proc :Windows::Networking::Sockets::SocketQualityOfService
    get_OutboundUnicastHopLimit proc :ptr
    put_OutboundUnicastHopLimit proc :BYTE
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CSockets_CIDatagramSocketControl2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CSockets_CIDatagramSocketControl2_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Sockets_IDatagramSocketControl2 <L"Windows.Networking.Sockets.IDatagramSocketControl2">
DEFINE_IIDX(IDatagramSocketControl2, "33EAD5C2-979C-4415-82A1-3CFAF646C192")

.comdef IDatagramSocketControl2 : public IInspectable

    get_InboundBufferSizeInBytes proc :ptr
    put_InboundBufferSizeInBytes proc :UINT32
    get_DontFragment	proc :ptr
    put_DontFragment	proc :boolean
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CSockets_CIDatagramSocketStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CSockets_CIDatagramSocketStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Sockets_IDatagramSocketStatics <L"Windows.Networking.Sockets.IDatagramSocketStatics">
DEFINE_IIDX(IDatagramSocketStatics, "E9C62AEE-1494-4A21-BB7E-8589FC751D9D")

.comdef IDatagramSocketStatics : public IInspectable

    GetEndpointPairsAsync proc :ptr, :HSTRING, :ptr
    GetEndpointPairsWithSortOptionsAsync proc :ptr, :HSTRING, :Windows::Networking::HostNameSortOptions, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CSockets_CIDatagramSocket_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CSockets_CIDatagramSocket_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Sockets_IDatagramSocket <L"Windows.Networking.Sockets.IDatagramSocket">
DEFINE_IIDX(IDatagramSocket, "7FE25BBB-C3BC-4677-8446-CA28A465A3AF")

.comdef IDatagramSocket : public IInspectable

    get_Control		proc :ptr
    get_Information	proc :ptr
    get_OutputStream	proc :ptr
    ConnectAsync	proc :ptr, :HSTRING, :ptr
    ConnectWithEndpointPairAsync proc :ptr, :ptr
    BindServiceNameAsync proc :HSTRING, :ptr
    BindEndpointAsync	proc :ptr, :HSTRING, :ptr
    JoinMulticastGroup	proc :ptr
    GetOutputStreamAsync proc :ptr, :HSTRING, :ptr
    GetOutputStreamWithEndpointPairAsync proc :ptr, :ptr
    add_MessageReceived proc :ptr, :ptr
    remove_MessageReceived proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CSockets_CIDatagramSocket2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CSockets_CIDatagramSocket2_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Sockets_IDatagramSocket2 <L"Windows.Networking.Sockets.IDatagramSocket2">
DEFINE_IIDX(IDatagramSocket2, "D83BA354-9A9D-4185-A20A-1424C9C2A7CD")

.comdef IDatagramSocket2 : public IInspectable

    BindServiceNameAndAdapterAsync proc :HSTRING, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CSockets_CIStreamSocketInformation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CSockets_CIStreamSocketInformation_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Sockets_IStreamSocketInformation <L"Windows.Networking.Sockets.IStreamSocketInformation">
DEFINE_IIDX(IStreamSocketInformation, "3B80AE30-5E68-4205-88F0-DC85D2E25DED")

.comdef IStreamSocketInformation : public IInspectable

    get_LocalAddress	proc :ptr
    get_LocalPort	proc :ptr
    get_RemoteHostName	proc :ptr
    get_RemoteAddress	proc :ptr
    get_RemoteServiceName proc :ptr
    get_RemotePort	proc :ptr
    get_RoundTripTimeStatistics proc :ptr
    get_BandwidthStatistics proc :ptr
    get_ProtectionLevel proc :ptr
    get_SessionKey	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CSockets_CIStreamSocketInformation2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CSockets_CIStreamSocketInformation2_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Sockets_IStreamSocketInformation2 <L"Windows.Networking.Sockets.IStreamSocketInformation2">
DEFINE_IIDX(IStreamSocketInformation2, "12C28452-4BDC-4EE4-976A-CF130E9D92E3")

.comdef IStreamSocketInformation2 : public IInspectable

    get_ServerCertificateErrorSeverity proc :ptr
    get_ServerCertificateErrors proc :ptr
    get_ServerCertificate proc :ptr
    get_ServerIntermediateCertificates proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CSockets_CIStreamSocketControl_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CSockets_CIStreamSocketControl_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Sockets_IStreamSocketControl <L"Windows.Networking.Sockets.IStreamSocketControl">
DEFINE_IIDX(IStreamSocketControl, "FE25ADF1-92AB-4AF3-9992-0F4C85E36CC4")

.comdef IStreamSocketControl : public IInspectable

    get_NoDelay		proc :ptr
    put_NoDelay		proc :boolean
    get_KeepAlive	proc :ptr
    put_KeepAlive	proc :boolean
    get_OutboundBufferSizeInBytes proc :ptr
    put_OutboundBufferSizeInBytes proc :UINT32
    get_QualityOfService proc :ptr
    put_QualityOfService proc :Windows::Networking::Sockets::SocketQualityOfService
    get_OutboundUnicastHopLimit proc :ptr
    put_OutboundUnicastHopLimit proc :BYTE
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CSockets_CIStreamSocketControl2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CSockets_CIStreamSocketControl2_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Sockets_IStreamSocketControl2 <L"Windows.Networking.Sockets.IStreamSocketControl2">
DEFINE_IIDX(IStreamSocketControl2, "C2D09A56-060F-44C1-B8E2-1FBF60BD62C5")

.comdef IStreamSocketControl2 : public IInspectable

    get_IgnorableServerCertificateErrors proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CSockets_CIStreamSocket_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CSockets_CIStreamSocket_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Sockets_IStreamSocket <L"Windows.Networking.Sockets.IStreamSocket">
DEFINE_IIDX(IStreamSocket, "69A22CF3-FC7B-4857-AF38-F6E7DE6A5B49")

.comdef IStreamSocket : public IInspectable

    get_Control		proc :ptr
    get_Information	proc :ptr
    get_InputStream	proc :ptr
    get_OutputStream	proc :ptr
    ConnectWithEndpointPairAsync proc :ptr, :ptr
    ConnectAsync	proc :ptr, :HSTRING, :ptr
    ConnectWithEndpointPairAndProtectionLevelAsync proc :ptr, :Windows::Networking::Sockets::SocketProtectionLevel, :ptr
    ConnectWithProtectionLevelAsync proc :ptr, :HSTRING, :Windows::Networking::Sockets::SocketProtectionLevel, :ptr
    UpgradeToSslAsync	proc :Windows::Networking::Sockets::SocketProtectionLevel, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CSockets_CIStreamSocket2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CSockets_CIStreamSocket2_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Sockets_IStreamSocket2 <L"Windows.Networking.Sockets.IStreamSocket2">
DEFINE_IIDX(IStreamSocket2, "29D0E575-F314-4D09-ADF0-0FBD967FBD9F")

.comdef IStreamSocket2 : public IInspectable

    ConnectWithProtectionLevelAndAdapterAsync proc :ptr, :HSTRING, :Windows::Networking::Sockets::SocketProtectionLevel, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CSockets_CIStreamSocketListenerControl_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CSockets_CIStreamSocketListenerControl_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Sockets_IStreamSocketListenerControl <L"Windows.Networking.Sockets.IStreamSocketListenerControl">
DEFINE_IIDX(IStreamSocketListenerControl, "20D8C576-8D8A-4DBA-9722-A16C4D984980")

.comdef IStreamSocketListenerControl : public IInspectable

    get_QualityOfService proc :ptr
    put_QualityOfService proc :Windows::Networking::Sockets::SocketQualityOfService
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CSockets_CIStreamSocketListenerInformation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CSockets_CIStreamSocketListenerInformation_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Sockets_IStreamSocketListenerInformation <L"Windows.Networking.Sockets.IStreamSocketListenerInformation">
DEFINE_IIDX(IStreamSocketListenerInformation, "E62BA82F-A63A-430B-BF62-29E93E5633B4")

.comdef IStreamSocketListenerInformation : public IInspectable

    get_LocalPort	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CSockets_CIStreamSocketListenerConnectionReceivedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CSockets_CIStreamSocketListenerConnectionReceivedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Sockets_IStreamSocketListenerConnectionReceivedEventArgs <L"Windows.Networking.Sockets.IStreamSocketListenerConnectionReceivedEventArgs">
DEFINE_IIDX(IStreamSocketListenerConnectionReceivedEventArgs, "0C472EA9-373F-447B-85B1-DDD4548803BA")

.comdef IStreamSocketListenerConnectionReceivedEventArgs : public IInspectable

    get_Socket		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CSockets_CIStreamSocketListener_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CSockets_CIStreamSocketListener_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Sockets_IStreamSocketListener <L"Windows.Networking.Sockets.IStreamSocketListener">
DEFINE_IIDX(IStreamSocketListener, "FF513437-DF9F-4DF0-BF82-0EC5D7B35AAE")

.comdef IStreamSocketListener : public IInspectable

    get_Control		proc :ptr
    get_Information	proc :ptr
    BindServiceNameAsync proc :HSTRING, :ptr
    BindEndpointAsync	proc :ptr, :HSTRING, :ptr
    add_ConnectionReceived proc :ptr, :ptr
    remove_ConnectionReceived proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CSockets_CIStreamSocketListener2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CSockets_CIStreamSocketListener2_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Sockets_IStreamSocketListener2 <L"Windows.Networking.Sockets.IStreamSocketListener2">
DEFINE_IIDX(IStreamSocketListener2, "658DC13E-BB3E-4458-B232-ED1088694B98")

.comdef IStreamSocketListener2 : public IInspectable

    BindServiceNameWithProtectionLevelAsync proc :HSTRING, :Windows::Networking::Sockets::SocketProtectionLevel, :ptr
    BindServiceNameWithProtectionLevelAndAdapterAsync proc :HSTRING, :Windows::Networking::Sockets::SocketProtectionLevel, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CSockets_CIWebSocketControl_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CSockets_CIWebSocketControl_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Sockets_IWebSocketControl <L"Windows.Networking.Sockets.IWebSocketControl">
DEFINE_IIDX(IWebSocketControl, "2EC4BDC3-D9A5-455A-9811-DE24D45337E9")

.comdef IWebSocketControl : public IInspectable

    get_OutboundBufferSizeInBytes proc :ptr
    put_OutboundBufferSizeInBytes proc :UINT32
    get_ServerCredential proc :ptr
    put_ServerCredential proc :ptr
    get_ProxyCredential proc :ptr
    put_ProxyCredential proc :ptr
    get_SupportedProtocols proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CSockets_CIWebSocketInformation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CSockets_CIWebSocketInformation_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Sockets_IWebSocketInformation <L"Windows.Networking.Sockets.IWebSocketInformation">
DEFINE_IIDX(IWebSocketInformation, "5E01E316-C92A-47A5-B25F-07847639D181")

.comdef IWebSocketInformation : public IInspectable

    get_LocalAddress	proc :ptr
    get_BandwidthStatistics proc :ptr
    get_Protocol	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CSockets_CIWebSocket_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CSockets_CIWebSocket_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Sockets_IWebSocket <L"Windows.Networking.Sockets.IWebSocket">
DEFINE_IIDX(IWebSocket, "F877396F-99B1-4E18-BC08-850C9ADF156E")

.comdef IWebSocket : public IInspectable

    get_OutputStream	proc :ptr
    ConnectAsync	proc :ptr, :ptr
    SetRequestHeader	proc :HSTRING, :HSTRING
    add_Closed		proc :ptr, :ptr
    remove_Closed	proc :EventRegistrationToken
    CloseWithStatus	proc :UINT16, :HSTRING
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CSockets_CIMessageWebSocketControl_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CSockets_CIMessageWebSocketControl_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Sockets_IMessageWebSocketControl <L"Windows.Networking.Sockets.IMessageWebSocketControl">
DEFINE_IIDX(IMessageWebSocketControl, "8118388A-C629-4F0A-80FB-81FC05538862")

.comdef IMessageWebSocketControl : public IInspectable

    get_MaxMessageSize	proc :ptr
    put_MaxMessageSize	proc :UINT32
    get_MessageType	proc :ptr
    put_MessageType	proc :Windows::Networking::Sockets::SocketMessageType
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CSockets_CIMessageWebSocket_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CSockets_CIMessageWebSocket_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Sockets_IMessageWebSocket <L"Windows.Networking.Sockets.IMessageWebSocket">
DEFINE_IIDX(IMessageWebSocket, "33727D08-34D5-4746-AD7B-8DDE5BC2EF88")

.comdef IMessageWebSocket : public IInspectable

    get_Control		proc :ptr
    get_Information	proc :ptr
    add_MessageReceived proc :ptr, :ptr
    remove_MessageReceived proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CSockets_CIStreamWebSocketControl_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CSockets_CIStreamWebSocketControl_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Sockets_IStreamWebSocketControl <L"Windows.Networking.Sockets.IStreamWebSocketControl">
DEFINE_IIDX(IStreamWebSocketControl, "B4F478B1-A45A-48DB-953A-645B7D964C07")

.comdef IStreamWebSocketControl : public IInspectable

    get_NoDelay		proc :ptr
    put_NoDelay		proc :boolean
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CSockets_CIStreamWebSocket_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CSockets_CIStreamWebSocket_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Sockets_IStreamWebSocket <L"Windows.Networking.Sockets.IStreamWebSocket">
DEFINE_IIDX(IStreamWebSocket, "BD4A49D8-B289-45BB-97EB-C7525205A843")

.comdef IStreamWebSocket : public IInspectable

    get_Control		proc :ptr
    get_Information	proc :ptr
    get_InputStream	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CSockets_CISocketErrorStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CSockets_CISocketErrorStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Sockets_ISocketErrorStatics <L"Windows.Networking.Sockets.ISocketErrorStatics">
DEFINE_IIDX(ISocketErrorStatics, "828337F4-7D56-4D8E-B7B4-A07DD7C1BCA9")

.comdef ISocketErrorStatics : public IInspectable

    GetStatus		proc :INT32, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CSockets_CIWebSocketErrorStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CSockets_CIWebSocketErrorStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Sockets_IWebSocketErrorStatics <L"Windows.Networking.Sockets.IWebSocketErrorStatics">
DEFINE_IIDX(IWebSocketErrorStatics, "27CDF35B-1F61-4709-8E02-61283ADA4E9D")

.comdef IWebSocketErrorStatics : public IInspectable

    GetStatus		proc :INT32, :ptr
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_Networking_Sockets_ControlChannelTrigger_DEFINED
define RUNTIMECLASS_Windows_Networking_Sockets_ControlChannelTrigger_DEFINED
define RuntimeClass_Windows_Networking_Sockets_ControlChannelTrigger <L"Windows.Networking.Sockets.ControlChannelTrigger">
endif
ifndef RUNTIMECLASS_Windows_Networking_Sockets_DatagramSocketControl_DEFINED
define RUNTIMECLASS_Windows_Networking_Sockets_DatagramSocketControl_DEFINED
define RuntimeClass_Windows_Networking_Sockets_DatagramSocketControl <L"Windows.Networking.Sockets.DatagramSocketControl">
endif
ifndef RUNTIMECLASS_Windows_Networking_Sockets_DatagramSocketInformation_DEFINED
define RUNTIMECLASS_Windows_Networking_Sockets_DatagramSocketInformation_DEFINED
define RuntimeClass_Windows_Networking_Sockets_DatagramSocketInformation <L"Windows.Networking.Sockets.DatagramSocketInformation">
endif
ifndef RUNTIMECLASS_Windows_Networking_Sockets_DatagramSocket_DEFINED
define RUNTIMECLASS_Windows_Networking_Sockets_DatagramSocket_DEFINED
define RuntimeClass_Windows_Networking_Sockets_DatagramSocket <L"Windows.Networking.Sockets.DatagramSocket">
endif
ifndef RUNTIMECLASS_Windows_Networking_Sockets_DatagramSocketMessageReceivedEventArgs_DEFINED
define RUNTIMECLASS_Windows_Networking_Sockets_DatagramSocketMessageReceivedEventArgs_DEFINED
define RuntimeClass_Windows_Networking_Sockets_DatagramSocketMessageReceivedEventArgs <L"Windows.Networking.Sockets.DatagramSocketMessageReceivedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_Networking_Sockets_StreamSocketControl_DEFINED
define RUNTIMECLASS_Windows_Networking_Sockets_StreamSocketControl_DEFINED
define RuntimeClass_Windows_Networking_Sockets_StreamSocketControl <L"Windows.Networking.Sockets.StreamSocketControl">
endif
ifndef RUNTIMECLASS_Windows_Networking_Sockets_StreamSocketInformation_DEFINED
define RUNTIMECLASS_Windows_Networking_Sockets_StreamSocketInformation_DEFINED
define RuntimeClass_Windows_Networking_Sockets_StreamSocketInformation <L"Windows.Networking.Sockets.StreamSocketInformation">
endif
ifndef RUNTIMECLASS_Windows_Networking_Sockets_StreamSocket_DEFINED
define RUNTIMECLASS_Windows_Networking_Sockets_StreamSocket_DEFINED
define RuntimeClass_Windows_Networking_Sockets_StreamSocket <L"Windows.Networking.Sockets.StreamSocket">
endif
ifndef RUNTIMECLASS_Windows_Networking_Sockets_StreamSocketListenerControl_DEFINED
define RUNTIMECLASS_Windows_Networking_Sockets_StreamSocketListenerControl_DEFINED
define RuntimeClass_Windows_Networking_Sockets_StreamSocketListenerControl <L"Windows.Networking.Sockets.StreamSocketListenerControl">
endif
ifndef RUNTIMECLASS_Windows_Networking_Sockets_StreamSocketListenerInformation_DEFINED
define RUNTIMECLASS_Windows_Networking_Sockets_StreamSocketListenerInformation_DEFINED
define RuntimeClass_Windows_Networking_Sockets_StreamSocketListenerInformation <L"Windows.Networking.Sockets.StreamSocketListenerInformation">
endif
ifndef RUNTIMECLASS_Windows_Networking_Sockets_StreamSocketListener_DEFINED
define RUNTIMECLASS_Windows_Networking_Sockets_StreamSocketListener_DEFINED
define RuntimeClass_Windows_Networking_Sockets_StreamSocketListener <L"Windows.Networking.Sockets.StreamSocketListener">
endif
ifndef RUNTIMECLASS_Windows_Networking_Sockets_StreamSocketListenerConnectionReceivedEventArgs_DEFINED
define RUNTIMECLASS_Windows_Networking_Sockets_StreamSocketListenerConnectionReceivedEventArgs_DEFINED
define RuntimeClass_Windows_Networking_Sockets_StreamSocketListenerConnectionReceivedEventArgs <L"Windows.Networking.Sockets.StreamSocketListenerConnectionReceivedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_Networking_Sockets_WebSocketClosedEventArgs_DEFINED
define RUNTIMECLASS_Windows_Networking_Sockets_WebSocketClosedEventArgs_DEFINED
define RuntimeClass_Windows_Networking_Sockets_WebSocketClosedEventArgs <L"Windows.Networking.Sockets.WebSocketClosedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_Networking_Sockets_MessageWebSocketControl_DEFINED
define RUNTIMECLASS_Windows_Networking_Sockets_MessageWebSocketControl_DEFINED
define RuntimeClass_Windows_Networking_Sockets_MessageWebSocketControl <L"Windows.Networking.Sockets.MessageWebSocketControl">
endif
ifndef RUNTIMECLASS_Windows_Networking_Sockets_MessageWebSocketInformation_DEFINED
define RUNTIMECLASS_Windows_Networking_Sockets_MessageWebSocketInformation_DEFINED
define RuntimeClass_Windows_Networking_Sockets_MessageWebSocketInformation <L"Windows.Networking.Sockets.MessageWebSocketInformation">
endif
ifndef RUNTIMECLASS_Windows_Networking_Sockets_MessageWebSocket_DEFINED
define RUNTIMECLASS_Windows_Networking_Sockets_MessageWebSocket_DEFINED
define RuntimeClass_Windows_Networking_Sockets_MessageWebSocket <L"Windows.Networking.Sockets.MessageWebSocket">
endif
ifndef RUNTIMECLASS_Windows_Networking_Sockets_MessageWebSocketMessageReceivedEventArgs_DEFINED
define RUNTIMECLASS_Windows_Networking_Sockets_MessageWebSocketMessageReceivedEventArgs_DEFINED
define RuntimeClass_Windows_Networking_Sockets_MessageWebSocketMessageReceivedEventArgs <L"Windows.Networking.Sockets.MessageWebSocketMessageReceivedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_Networking_Sockets_StreamWebSocketControl_DEFINED
define RUNTIMECLASS_Windows_Networking_Sockets_StreamWebSocketControl_DEFINED
define RuntimeClass_Windows_Networking_Sockets_StreamWebSocketControl <L"Windows.Networking.Sockets.StreamWebSocketControl">
endif
ifndef RUNTIMECLASS_Windows_Networking_Sockets_StreamWebSocketInformation_DEFINED
define RUNTIMECLASS_Windows_Networking_Sockets_StreamWebSocketInformation_DEFINED
define RuntimeClass_Windows_Networking_Sockets_StreamWebSocketInformation <L"Windows.Networking.Sockets.StreamWebSocketInformation">
endif
ifndef RUNTIMECLASS_Windows_Networking_Sockets_StreamWebSocket_DEFINED
define RUNTIMECLASS_Windows_Networking_Sockets_StreamWebSocket_DEFINED
define RuntimeClass_Windows_Networking_Sockets_StreamWebSocket <L"Windows.Networking.Sockets.StreamWebSocket">
endif
ifndef RUNTIMECLASS_Windows_Networking_Sockets_WebSocketKeepAlive_DEFINED
define RUNTIMECLASS_Windows_Networking_Sockets_WebSocketKeepAlive_DEFINED
define RuntimeClass_Windows_Networking_Sockets_WebSocketKeepAlive <L"Windows.Networking.Sockets.WebSocketKeepAlive">
endif
ifndef RUNTIMECLASS_Windows_Networking_Sockets_SocketError_DEFINED
define RUNTIMECLASS_Windows_Networking_Sockets_SocketError_DEFINED
define RuntimeClass_Windows_Networking_Sockets_SocketError <L"Windows.Networking.Sockets.SocketError">
endif
ifndef RUNTIMECLASS_Windows_Networking_Sockets_WebSocketError_DEFINED
define RUNTIMECLASS_Windows_Networking_Sockets_WebSocketError_DEFINED
define RuntimeClass_Windows_Networking_Sockets_WebSocketError <L"Windows.Networking.Sockets.WebSocketError">
endif

endif

