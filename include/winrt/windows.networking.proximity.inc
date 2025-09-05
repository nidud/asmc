ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Enetworking2Eproximity_h__
define __windows2Enetworking2Eproximity_h__
ifndef __windows2Efoundation_h__
include Windows.Foundation.inc
endif
include Windows.Networking.Sockets.inc

ifndef ____FIIterator_1_Windows__CNetworking__CProximity__CPeerInformation_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CNetworking__CProximity__CPeerInformation_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CNetworking__CProximity__CPeerInformation, "eb6fe2c2-d6cd-5df0-a295-74c56ec58aab")

.comdef __FIIterator_1_Windows__CNetworking__CProximity__CPeerInformation : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CNetworking__CProximity__CPeerInformation_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CNetworking__CProximity__CPeerInformation_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CNetworking__CProximity__CPeerInformation, "917e1105-0647-5793-9d50-befe225f0f2f")

.comdef __FIIterable_1_Windows__CNetworking__CProximity__CPeerInformation : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CNetworking__CProximity__CPeerInformation_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CNetworking__CProximity__CPeerInformation_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CNetworking__CProximity__CPeerInformation, "948f92bc-2a05-5c80-95f2-96fe345852cc")

.comdef __FIVectorView_1_Windows__CNetworking__CProximity__CPeerInformation : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CNetworking__CProximity__CPeerInformation_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CNetworking__CProximity__CPeerInformation_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CNetworking__CProximity__CPeerInformation, "ecf90f2c-e3f4-5b62-a066-8b9c818fd41a")

.comdef __FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CNetworking__CProximity__CPeerInformation : public IInspectable

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1___FIVectorView_1_Windows__CNetworking__CProximity__CPeerInformation_INTERFACE_DEFINED__
define ____FIAsyncOperation_1___FIVectorView_1_Windows__CNetworking__CProximity__CPeerInformation_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1___FIVectorView_1_Windows__CNetworking__CProximity__CPeerInformation, "a36ec4bc-607a-5180-a785-4042f8795c8b")

.comdef __FIAsyncOperation_1___FIVectorView_1_Windows__CNetworking__CProximity__CPeerInformation : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_IInspectable_Windows__CNetworking__CProximity__CConnectionRequestedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_IInspectable_Windows__CNetworking__CProximity__CConnectionRequestedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_IInspectable_Windows__CNetworking__CProximity__CConnectionRequestedEventArgs, "512c383c-8b29-5079-953e-8dee8f8a8224")

.comdef __FITypedEventHandler_2_IInspectable_Windows__CNetworking__CProximity__CConnectionRequestedEventArgs : public IInspectable

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_IInspectable_Windows__CNetworking__CProximity__CTriggeredConnectionStateChangedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_IInspectable_Windows__CNetworking__CProximity__CTriggeredConnectionStateChangedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_IInspectable_Windows__CNetworking__CProximity__CTriggeredConnectionStateChangedEventArgs, "2e5ad6fa-3ca6-5518-bd4d-fefc4535580e")

.comdef __FITypedEventHandler_2_IInspectable_Windows__CNetworking__CProximity__CTriggeredConnectionStateChangedEventArgs : public IInspectable

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CNetworking__CProximity__CPeerWatcher_IInspectable_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CNetworking__CProximity__CPeerWatcher_IInspectable_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CNetworking__CProximity__CPeerWatcher_IInspectable, "f4979ea1-7e06-50a8-88dc-3f29524e4fdb")

.comdef __FITypedEventHandler_2_Windows__CNetworking__CProximity__CPeerWatcher_IInspectable : public IInspectable

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CNetworking__CProximity__CPeerWatcher_Windows__CNetworking__CProximity__CPeerInformation_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CNetworking__CProximity__CPeerWatcher_Windows__CNetworking__CProximity__CPeerInformation_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CNetworking__CProximity__CPeerWatcher_Windows__CNetworking__CProximity__CPeerInformation, "ad674bbf-6281-5943-9772-e0fd7664d4e1")

.comdef __FITypedEventHandler_2_Windows__CNetworking__CProximity__CPeerWatcher_Windows__CNetworking__CProximity__CPeerInformation : public IInspectable

    _Invoke		proc :ptr, :ptr
   .ends

endif

.namespace Windows
.namespace Networking
.namespace Proximity

.enum TriggeredConnectState {
    TriggeredConnectState_PeerFound	= 0,
    TriggeredConnectState_Listening	= 1,
    TriggeredConnectState_Connecting	= 2,
    TriggeredConnectState_Completed	= 3,
    TriggeredConnectState_Canceled	= 4,
    TriggeredConnectState_Failed	= 5
    }

.enum PeerWatcherStatus {
    PeerWatcherStatus_Created	= 0,
    PeerWatcherStatus_Started	= 1,
    PeerWatcherStatus_EnumerationCompleted	= 2,
    PeerWatcherStatus_Stopping	= 3,
    PeerWatcherStatus_Stopped	= 4,
    PeerWatcherStatus_Aborted	= 5
    }

.enum PeerDiscoveryTypes {
    PeerDiscoveryTypes_None	= 0,
    PeerDiscoveryTypes_Browse	= 0x1,
    PeerDiscoveryTypes_Triggered	= 0x2
    }

.enum PeerRole {
    PeerRole_Peer	= 0,
    PeerRole_Host	= 1,
    PeerRole_Client	= 2
    }

ifndef ____x_ABI_CWindows_CNetworking_CProximity_CIMessageReceivedHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CProximity_CIMessageReceivedHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IMessageReceivedHandler, "EFAB0782-F6E2-4675-A045-D8E320C24808")

.comdef IMessageReceivedHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CProximity_CIMessageTransmittedHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CProximity_CIMessageTransmittedHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IMessageTransmittedHandler, "EFAA0B4A-F6E2-4D7D-856C-78FC8EFC021E")

.comdef IMessageTransmittedHandler : public IUnknown

    _Invoke		proc :ptr, :INT64
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CProximity_CIDeviceArrivedEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CProximity_CIDeviceArrivedEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IDeviceArrivedEventHandler, "EFA9DA69-F6E1-49C9-A49E-8E0FC58FB911")

.comdef IDeviceArrivedEventHandler : public IUnknown

    _Invoke		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CProximity_CIDeviceDepartedEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CProximity_CIDeviceDepartedEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IDeviceDepartedEventHandler, "EFA9DA69-F6E2-49C9-A49E-8E0FC58FB911")

.comdef IDeviceDepartedEventHandler : public IUnknown

    _Invoke		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CProximity_CIProximityMessage_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CProximity_CIProximityMessage_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Proximity_IProximityMessage <L"Windows.Networking.Proximity.IProximityMessage">
DEFINE_IIDX(IProximityMessage, "EFAB0782-F6E1-4675-A045-D8E320C24808")

.comdef IProximityMessage : public IInspectable

    get_MessageType	proc :ptr
    get_SubscriptionId	proc :ptr
    get_Data		proc :ptr
    get_DataAsString	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CProximity_CIProximityDevice_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CProximity_CIProximityDevice_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Proximity_IProximityDevice <L"Windows.Networking.Proximity.IProximityDevice">
DEFINE_IIDX(IProximityDevice, "EFA8A552-F6E1-4329-A0FC-AB6B0FD28262")

.comdef IProximityDevice : public IInspectable

    SubscribeForMessage proc :HSTRING, :ptr, :ptr
    PublishMessage	proc :HSTRING, :HSTRING, :ptr
    PublishMessageWithCallback proc :HSTRING, :HSTRING, :ptr, :ptr
    PublishBinaryMessage proc :HSTRING, :ptr, :ptr
    PublishBinaryMessageWithCallback proc :HSTRING, :ptr, :ptr, :ptr
    PublishUriMessage	proc :ptr, :ptr
    PublishUriMessageWithCallback proc :ptr, :ptr, :ptr
    StopSubscribingForMessage proc :INT64
    StopPublishingMessage proc :INT64
    add_DeviceArrived	proc :ptr, :ptr
    remove_DeviceArrived proc :EventRegistrationToken
    add_DeviceDeparted	proc :ptr, :ptr
    remove_DeviceDeparted proc :EventRegistrationToken
    get_MaxMessageBytes proc :ptr
    get_BitsPerSecond	proc :ptr
    get_DeviceId	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CProximity_CIProximityDeviceStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CProximity_CIProximityDeviceStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Proximity_IProximityDeviceStatics <L"Windows.Networking.Proximity.IProximityDeviceStatics">
DEFINE_IIDX(IProximityDeviceStatics, "914BA01D-F6E1-47C4-A14C-148A1903D0C6")

.comdef IProximityDeviceStatics : public IInspectable

    GetDeviceSelector	proc :ptr
    GetDefault		proc :ptr
    FromId		proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CProximity_CITriggeredConnectionStateChangedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CProximity_CITriggeredConnectionStateChangedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Proximity_ITriggeredConnectionStateChangedEventArgs <L"Windows.Networking.Proximity.ITriggeredConnectionStateChangedEventArgs">
DEFINE_IIDX(ITriggeredConnectionStateChangedEventArgs, "C6A780AD-F6E1-4D54-96E2-33F620BCA88A")

.comdef ITriggeredConnectionStateChangedEventArgs : public IInspectable

    get_State		proc :ptr
    get_Id		proc :ptr
    get_Socket		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CProximity_CIPeerInformation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CProximity_CIPeerInformation_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Proximity_IPeerInformation <L"Windows.Networking.Proximity.IPeerInformation">
DEFINE_IIDX(IPeerInformation, "20024F08-9FFF-45F4-B6E9-408B2EBEF373")

.comdef IPeerInformation : public IInspectable

    get_DisplayName	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CProximity_CIPeerInformation3_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CProximity_CIPeerInformation3_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Proximity_IPeerInformation3 <L"Windows.Networking.Proximity.IPeerInformation3">
DEFINE_IIDX(IPeerInformation3, "B20F612A-DBD0-40F8-95BD-2D4209C7836F")

.comdef IPeerInformation3 : public IInspectable

    get_Id		proc :ptr
    get_DiscoveryData	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CProximity_CIConnectionRequestedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CProximity_CIConnectionRequestedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Proximity_IConnectionRequestedEventArgs <L"Windows.Networking.Proximity.IConnectionRequestedEventArgs">
DEFINE_IIDX(IConnectionRequestedEventArgs, "EB6891AE-4F1E-4C66-BD0D-46924A942E08")

.comdef IConnectionRequestedEventArgs : public IInspectable

    get_PeerInformation proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CProximity_CIPeerWatcher_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CProximity_CIPeerWatcher_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Proximity_IPeerWatcher <L"Windows.Networking.Proximity.IPeerWatcher">
DEFINE_IIDX(IPeerWatcher, "3CEE21F8-2FA6-4679-9691-03C94A420F34")

.comdef IPeerWatcher : public IInspectable

    add_Added		proc :ptr, :ptr
    remove_Added	proc :EventRegistrationToken
    add_Removed		proc :ptr, :ptr
    remove_Removed	proc :EventRegistrationToken
    add_Updated		proc :ptr, :ptr
    remove_Updated	proc :EventRegistrationToken
    add_EnumerationCompleted proc :ptr, :ptr
    remove_EnumerationCompleted proc :EventRegistrationToken
    add_Stopped		proc :ptr, :ptr
    remove_Stopped	proc :EventRegistrationToken
    get_Status		proc :ptr
    Start		proc
    Stop		proc
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CProximity_CIPeerFinderStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CProximity_CIPeerFinderStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Proximity_IPeerFinderStatics <L"Windows.Networking.Proximity.IPeerFinderStatics">
DEFINE_IIDX(IPeerFinderStatics, "914B3B61-F6E1-47C4-A14C-148A1903D0C6")

.comdef IPeerFinderStatics : public IInspectable

    get_AllowBluetooth	proc :ptr
    put_AllowBluetooth	proc :boolean
    get_AllowInfrastructure proc :ptr
    put_AllowInfrastructure proc :boolean
    get_AllowWiFiDirect proc :ptr
    put_AllowWiFiDirect proc :boolean
    get_DisplayName	proc :ptr
    put_DisplayName	proc :HSTRING
    get_SupportedDiscoveryTypes proc :ptr
    get_AlternateIdentities proc :ptr
    Start		proc
    StartWithMessage	proc :HSTRING
    Stop		proc
    add_TriggeredConnectionStateChanged proc :ptr, :ptr
    remove_TriggeredConnectionStateChanged proc :EventRegistrationToken
    add_ConnectionRequested proc :ptr, :ptr
    remove_ConnectionRequested proc :EventRegistrationToken
    FindAllPeersAsync	proc :ptr
    ConnectAsync	proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CProximity_CIPeerFinderStatics2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CProximity_CIPeerFinderStatics2_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Proximity_IPeerFinderStatics2 <L"Windows.Networking.Proximity.IPeerFinderStatics2">
DEFINE_IIDX(IPeerFinderStatics2, "D6E73C65-FDD0-4B0B-9312-866408935D82")

.comdef IPeerFinderStatics2 : public IInspectable

    get_Role		proc :ptr
    put_Role		proc :Windows::Networking::Proximity::PeerRole
    get_DiscoveryData	proc :ptr
    put_DiscoveryData	proc :ptr
    CreateWatcher	proc :ptr
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_Networking_Proximity_ProximityMessage_DEFINED
define RUNTIMECLASS_Windows_Networking_Proximity_ProximityMessage_DEFINED
define RuntimeClass_Windows_Networking_Proximity_ProximityMessage <L"Windows.Networking.Proximity.ProximityMessage">
endif
ifndef RUNTIMECLASS_Windows_Networking_Proximity_ProximityDevice_DEFINED
define RUNTIMECLASS_Windows_Networking_Proximity_ProximityDevice_DEFINED
define RuntimeClass_Windows_Networking_Proximity_ProximityDevice <L"Windows.Networking.Proximity.ProximityDevice">
endif
ifndef RUNTIMECLASS_Windows_Networking_Proximity_TriggeredConnectionStateChangedEventArgs_DEFINED
define RUNTIMECLASS_Windows_Networking_Proximity_TriggeredConnectionStateChangedEventArgs_DEFINED
define RuntimeClass_Windows_Networking_Proximity_TriggeredConnectionStateChangedEventArgs <L"Windows.Networking.Proximity.TriggeredConnectionStateChangedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_Networking_Proximity_PeerInformation_DEFINED
define RUNTIMECLASS_Windows_Networking_Proximity_PeerInformation_DEFINED
define RuntimeClass_Windows_Networking_Proximity_PeerInformation <L"Windows.Networking.Proximity.PeerInformation">
endif
ifndef RUNTIMECLASS_Windows_Networking_Proximity_ConnectionRequestedEventArgs_DEFINED
define RUNTIMECLASS_Windows_Networking_Proximity_ConnectionRequestedEventArgs_DEFINED
define RuntimeClass_Windows_Networking_Proximity_ConnectionRequestedEventArgs <L"Windows.Networking.Proximity.ConnectionRequestedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_Networking_Proximity_PeerWatcher_DEFINED
define RUNTIMECLASS_Windows_Networking_Proximity_PeerWatcher_DEFINED
define RuntimeClass_Windows_Networking_Proximity_PeerWatcher <L"Windows.Networking.Proximity.PeerWatcher">
endif
ifndef RUNTIMECLASS_Windows_Networking_Proximity_PeerFinder_DEFINED
define RUNTIMECLASS_Windows_Networking_Proximity_PeerFinder_DEFINED
define RuntimeClass_Windows_Networking_Proximity_PeerFinder <L"Windows.Networking.Proximity.PeerFinder">
endif

endif

