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

ifndef __windows2Enetworking2Enetworkoperators_h__
define __windows2Enetworking2Enetworkoperators_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include Windows.Data.Xml.Dom.inc
include Windows.Devices.Sms.inc
include Windows.Networking.Connectivity.inc
include windows.foundation.collections.inc

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CNetworking__CNetworkOperators__CHotspotCredentialsAuthenticationResult_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CNetworking__CNetworkOperators__CHotspotCredentialsAuthenticationResult_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CNetworking__CNetworkOperators__CHotspotCredentialsAuthenticationResult, "7f254beb-471f-5000-94ce-102cc333055f")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CNetworking__CNetworkOperators__CHotspotCredentialsAuthenticationResult : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CNetworking__CNetworkOperators__CHotspotCredentialsAuthenticationResult_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CNetworking__CNetworkOperators__CHotspotCredentialsAuthenticationResult_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CNetworking__CNetworkOperators__CHotspotCredentialsAuthenticationResult, "522781d8-29c8-5d89-8937-1d1c2032f0c8")

.comdef __FIAsyncOperation_1_Windows__CNetworking__CNetworkOperators__CHotspotCredentialsAuthenticationResult : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CNetworking__CNetworkOperators__CNetworkOperatorTetheringOperationResult_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CNetworking__CNetworkOperators__CNetworkOperatorTetheringOperationResult_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CNetworking__CNetworkOperators__CNetworkOperatorTetheringOperationResult, "a936b927-7537-59c6-89de-33f36a9725ab")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CNetworking__CNetworkOperators__CNetworkOperatorTetheringOperationResult : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CNetworking__CNetworkOperators__CNetworkOperatorTetheringOperationResult_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CNetworking__CNetworkOperators__CNetworkOperatorTetheringOperationResult_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CNetworking__CNetworkOperators__CNetworkOperatorTetheringOperationResult, "601b30ed-9b7f-54b6-b61b-24a09bc56304")

.comdef __FIAsyncOperation_1_Windows__CNetworking__CNetworkOperators__CNetworkOperatorTetheringOperationResult : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CNetworking__CNetworkOperators__CProvisionFromXmlDocumentResults_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CNetworking__CNetworkOperators__CProvisionFromXmlDocumentResults_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CNetworking__CNetworkOperators__CProvisionFromXmlDocumentResults, "7a7eee1b-17f9-5a41-861b-c30ea127d0f1")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CNetworking__CNetworkOperators__CProvisionFromXmlDocumentResults : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CNetworking__CNetworkOperators__CProvisionFromXmlDocumentResults_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CNetworking__CNetworkOperators__CProvisionFromXmlDocumentResults_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CNetworking__CNetworkOperators__CProvisionFromXmlDocumentResults, "9f8fe338-c6b1-5614-a14f-8977a77e17f2")

.comdef __FIAsyncOperation_1_Windows__CNetworking__CNetworkOperators__CProvisionFromXmlDocumentResults : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CNetworking__CNetworkOperators__CUssdReply_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CNetworking__CNetworkOperators__CUssdReply_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CNetworking__CNetworkOperators__CUssdReply, "9385bd8f-5e14-557a-a7f1-63f33d9ecacf")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CNetworking__CNetworkOperators__CUssdReply : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CNetworking__CNetworkOperators__CUssdReply_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CNetworking__CNetworkOperators__CUssdReply_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CNetworking__CNetworkOperators__CUssdReply, "9dd0a063-6153-5afd-8288-8770ddcff2db")

.comdef __FIAsyncOperation_1_Windows__CNetworking__CNetworkOperators__CUssdReply : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CNetworking__CNetworkOperators__CMobileBroadbandAccountWatcher_IInspectable_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CNetworking__CNetworkOperators__CMobileBroadbandAccountWatcher_IInspectable_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CNetworking__CNetworkOperators__CMobileBroadbandAccountWatcher_IInspectable, "e4dc9cfc-f462-5afd-856d-04ace229d00e")

.comdef __FITypedEventHandler_2_Windows__CNetworking__CNetworkOperators__CMobileBroadbandAccountWatcher_IInspectable : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CNetworking__CNetworkOperators__CMobileBroadbandAccountWatcher_Windows__CNetworking__CNetworkOperators__CMobileBroadbandAccountEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CNetworking__CNetworkOperators__CMobileBroadbandAccountWatcher_Windows__CNetworking__CNetworkOperators__CMobileBroadbandAccountEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CNetworking__CNetworkOperators__CMobileBroadbandAccountWatcher_Windows__CNetworking__CNetworkOperators__CMobileBroadbandAccountEventArgs, "423cc41e-fe8c-5a7d-9fee-aae04ef85700")

.comdef __FITypedEventHandler_2_Windows__CNetworking__CNetworkOperators__CMobileBroadbandAccountWatcher_Windows__CNetworking__CNetworkOperators__CMobileBroadbandAccountEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CNetworking__CNetworkOperators__CMobileBroadbandAccountWatcher_Windows__CNetworking__CNetworkOperators__CMobileBroadbandAccountUpdatedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CNetworking__CNetworkOperators__CMobileBroadbandAccountWatcher_Windows__CNetworking__CNetworkOperators__CMobileBroadbandAccountUpdatedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CNetworking__CNetworkOperators__CMobileBroadbandAccountWatcher_Windows__CNetworking__CNetworkOperators__CMobileBroadbandAccountUpdatedEventArgs, "0e865096-1ffa-5792-8d4f-8623e3c77f56")

.comdef __FITypedEventHandler_2_Windows__CNetworking__CNetworkOperators__CMobileBroadbandAccountWatcher_Windows__CNetworking__CNetworkOperators__CMobileBroadbandAccountUpdatedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

.namespace Windows
.namespace Networking
.namespace NetworkOperators

.enum DataClasses {
    DataClasses_None	= 0,
    DataClasses_Gprs	= 0x1,
    DataClasses_Edge	= 0x2,
    DataClasses_Umts	= 0x4,
    DataClasses_Hsdpa	= 0x8,
    DataClasses_Hsupa	= 0x10,
    DataClasses_LteAdvanced	= 0x20,
    DataClasses_Cdma1xRtt	= 0x10000,
    DataClasses_Cdma1xEvdo	= 0x20000,
    DataClasses_Cdma1xEvdoRevA	= 0x40000,
    DataClasses_Cdma1xEvdv	= 0x80000,
    DataClasses_Cdma3xRtt	= 0x100000,
    DataClasses_Cdma1xEvdoRevB	= 0x200000,
    DataClasses_CdmaUmb = 0x400000,
    DataClasses_Custom	= 0x80000000
    }

.enum MobileBroadbandDeviceType {
    MobileBroadbandDeviceType_Unknown	= 0,
    MobileBroadbandDeviceType_Embedded	= 1,
    MobileBroadbandDeviceType_Removable = 2,
    MobileBroadbandDeviceType_Remote	= 3
    }

.enum NetworkDeviceStatus {
    NetworkDeviceStatus_DeviceNotReady	= 0,
    NetworkDeviceStatus_DeviceReady	= 1,
    NetworkDeviceStatus_SimNotInserted	= 2,
    NetworkDeviceStatus_BadSim	= 3,
    NetworkDeviceStatus_DeviceHardwareFailure	= 4,
    NetworkDeviceStatus_AccountNotActivated	= 5,
    NetworkDeviceStatus_DeviceLocked	= 6,
    NetworkDeviceStatus_DeviceBlocked	= 7
    }

.enum NetworkRegistrationState {
    NetworkRegistrationState_None	= 0,
    NetworkRegistrationState_Deregistered	= 1,
    NetworkRegistrationState_Searching	= 2,
    NetworkRegistrationState_Home	= 3,
    NetworkRegistrationState_Roaming	= 4,
    NetworkRegistrationState_Partner	= 5,
    NetworkRegistrationState_Denied	= 6
    }

.enum MobileBroadbandRadioState {
    MobileBroadbandRadioState_Off	= 0,
    MobileBroadbandRadioState_On	= 1
    }

.enum NetworkOperatorEventMessageType {
    NetworkOperatorEventMessageType_Gsm = 0,
    NetworkOperatorEventMessageType_Cdma	= 1,
    NetworkOperatorEventMessageType_Ussd	= 2,
    NetworkOperatorEventMessageType_DataPlanThresholdReached	= 3,
    NetworkOperatorEventMessageType_DataPlanReset	= 4,
    NetworkOperatorEventMessageType_DataPlanDeleted	= 5,
    NetworkOperatorEventMessageType_ProfileConnected	= 6,
    NetworkOperatorEventMessageType_ProfileDisconnected = 7,
    NetworkOperatorEventMessageType_RegisteredRoaming	= 8,
    NetworkOperatorEventMessageType_RegisteredHome	= 9,
    NetworkOperatorEventMessageType_TetheringEntitlementCheck	= 10,
    NetworkOperatorEventMessageType_TetheringOperationalStateChanged	= 11,
    NetworkOperatorEventMessageType_TetheringNumberOfClientsChanged	= 12
    }

.enum MobileBroadbandAccountWatcherStatus {
    MobileBroadbandAccountWatcherStatus_Created = 0,
    MobileBroadbandAccountWatcherStatus_Started = 1,
    MobileBroadbandAccountWatcherStatus_EnumerationCompleted	= 2,
    MobileBroadbandAccountWatcherStatus_Stopped = 3,
    MobileBroadbandAccountWatcherStatus_Aborted = 4
    }

.enum TetheringOperationalState {
    TetheringOperationalState_Unknown	= 0,
    TetheringOperationalState_On	= 1,
    TetheringOperationalState_Off	= 2,
    TetheringOperationalState_InTransition	= 3
    }

.enum TetheringCapability {
    TetheringCapability_Enabled = 0,
    TetheringCapability_DisabledByGroupPolicy	= 1,
    TetheringCapability_DisabledByHardwareLimitation	= 2,
    TetheringCapability_DisabledByOperator	= 3,
    TetheringCapability_DisabledBySku	= 4,
    TetheringCapability_DisabledByRequiredAppNotInstalled	= 5,
    TetheringCapability_DisabledDueToUnknownCause	= 6
    }

.enum TetheringOperationStatus {
    TetheringOperationStatus_Success	= 0,
    TetheringOperationStatus_Unknown	= 1,
    TetheringOperationStatus_MobileBroadbandDeviceOff	= 2,
    TetheringOperationStatus_WiFiDeviceOff	= 3,
    TetheringOperationStatus_EntitlementCheckTimeout	= 4,
    TetheringOperationStatus_EntitlementCheckFailure	= 5,
    TetheringOperationStatus_OperationInProgress	= 6
    }

.enum HotspotAuthenticationResponseCode {
    HotspotAuthenticationResponseCode_NoError	= 0,
    HotspotAuthenticationResponseCode_LoginSucceeded	= 50,
    HotspotAuthenticationResponseCode_LoginFailed	= 100,
    HotspotAuthenticationResponseCode_RadiusServerError = 102,
    HotspotAuthenticationResponseCode_NetworkAdministratorError = 105,
    HotspotAuthenticationResponseCode_LoginAborted	= 151,
    HotspotAuthenticationResponseCode_AccessGatewayInternalError	= 255
    }

.enum ProfileMediaType {
    ProfileMediaType_Wlan	= 0,
    ProfileMediaType_Wwan	= 1
    }

.enum UssdResultCode {
    UssdResultCode_NoActionRequired	= 0,
    UssdResultCode_ActionRequired	= 1,
    UssdResultCode_Terminated	= 2,
    UssdResultCode_OtherLocalClient	= 3,
    UssdResultCode_OperationNotSupported	= 4,
    UssdResultCode_NetworkTimeout	= 5
    }

.template ProfileUsage
    UsageInMegabytes	UINT32 ?
    LastSyncTime	Windows::Foundation::DateTime <>
   .ends

ifndef ____x_ABI_CWindows_CNetworking_CNetworkOperators_CIMobileBroadbandAccountStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CNetworkOperators_CIMobileBroadbandAccountStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_NetworkOperators_IMobileBroadbandAccountStatics <L"Windows.Networking.NetworkOperators.IMobileBroadbandAccountStatics">
DEFINE_IIDX(IMobileBroadbandAccountStatics, "AA7F4D24-AFC1-4FC8-AE9A-A9175310FAAD")

.comdef IMobileBroadbandAccountStatics : public IInspectable

    get_AvailableNetworkAccountIds proc :ptr
    CreateFromNetworkAccountId proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CNetworkOperators_CIMobileBroadbandAccount_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CNetworkOperators_CIMobileBroadbandAccount_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_NetworkOperators_IMobileBroadbandAccount <L"Windows.Networking.NetworkOperators.IMobileBroadbandAccount">
DEFINE_IIDX(IMobileBroadbandAccount, "36C24CCD-CEE2-43E0-A603-EE86A36D6570")

.comdef IMobileBroadbandAccount : public IInspectable

    get_NetworkAccountId proc :ptr
    get_ServiceProviderGuid proc :ptr
    get_ServiceProviderName proc :ptr
    get_CurrentNetwork	proc :ptr
    get_CurrentDeviceInformation proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CNetworkOperators_CIMobileBroadbandAccount2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CNetworkOperators_CIMobileBroadbandAccount2_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_NetworkOperators_IMobileBroadbandAccount2 <L"Windows.Networking.NetworkOperators.IMobileBroadbandAccount2">
DEFINE_IIDX(IMobileBroadbandAccount2, "38F52F1C-1136-4257-959F-B658A352B6D4")

.comdef IMobileBroadbandAccount2 : public IInspectable

    GetConnectionProfiles proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CNetworkOperators_CIMobileBroadbandDeviceInformation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CNetworkOperators_CIMobileBroadbandDeviceInformation_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_NetworkOperators_IMobileBroadbandDeviceInformation <L"Windows.Networking.NetworkOperators.IMobileBroadbandDeviceInformation">
DEFINE_IIDX(IMobileBroadbandDeviceInformation, "E6D08168-E381-4C6E-9BE8-FE156969A446")

.comdef IMobileBroadbandDeviceInformation : public IInspectable

    get_NetworkDeviceStatus proc :ptr
    get_Manufacturer	proc :ptr
    get_Model		proc :ptr
    get_FirmwareInformation proc :ptr
    get_CellularClass	proc :ptr
    get_DataClasses	proc :ptr
    get_CustomDataClass proc :ptr
    get_MobileEquipmentId proc :ptr
    get_TelephoneNumbers proc :ptr
    get_SubscriberId	proc :ptr
    get_SimIccId	proc :ptr
    get_DeviceType	proc :ptr
    get_DeviceId	proc :ptr
    get_CurrentRadioState proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CNetworkOperators_CIMobileBroadbandNetwork_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CNetworkOperators_CIMobileBroadbandNetwork_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_NetworkOperators_IMobileBroadbandNetwork <L"Windows.Networking.NetworkOperators.IMobileBroadbandNetwork">
DEFINE_IIDX(IMobileBroadbandNetwork, "CB63928C-0309-4CB6-A8C1-6A5A3C8E1FF6")

.comdef IMobileBroadbandNetwork : public IInspectable

    get_NetworkAdapter	proc :ptr
    get_NetworkRegistrationState proc :ptr
    get_RegistrationNetworkError proc :ptr
    get_PacketAttachNetworkError proc :ptr
    get_ActivationNetworkError proc :ptr
    get_AccessPointName proc :ptr
    get_RegisteredDataClass proc :ptr
    get_RegisteredProviderId proc :ptr
    get_RegisteredProviderName proc :ptr
    ShowConnectionUI	proc
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CNetworkOperators_CINetworkOperatorNotificationEventDetails_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CNetworkOperators_CINetworkOperatorNotificationEventDetails_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_NetworkOperators_INetworkOperatorNotificationEventDetails <L"Windows.Networking.NetworkOperators.INetworkOperatorNotificationEventDetails">
DEFINE_IIDX(INetworkOperatorNotificationEventDetails, "BC68A9D1-82E1-4488-9F2C-1276C2468FAC")

.comdef INetworkOperatorNotificationEventDetails : public IInspectable

    get_NotificationType proc :ptr
    get_NetworkAccountId proc :ptr
    get_EncodingType	proc :ptr
    get_Message		proc :ptr
    get_RuleId		proc :ptr
    get_SmsMessage	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CNetworkOperators_CINetworkOperatorTetheringEntitlementCheck_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CNetworkOperators_CINetworkOperatorTetheringEntitlementCheck_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_NetworkOperators_INetworkOperatorTetheringEntitlementCheck <L"Windows.Networking.NetworkOperators.INetworkOperatorTetheringEntitlementCheck">
DEFINE_IIDX(INetworkOperatorTetheringEntitlementCheck, "0108916D-9E9A-4AF6-8DA3-60493B19C204")

.comdef INetworkOperatorTetheringEntitlementCheck : public IInspectable

    AuthorizeTethering	proc :boolean, :HSTRING
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CNetworkOperators_CINetworkOperatorTetheringAccessPointConfiguration_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CNetworkOperators_CINetworkOperatorTetheringAccessPointConfiguration_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_NetworkOperators_INetworkOperatorTetheringAccessPointConfiguration <L"Windows.Networking.NetworkOperators.INetworkOperatorTetheringAccessPointConfiguration">
DEFINE_IIDX(INetworkOperatorTetheringAccessPointConfiguration, "0BCC0284-412E-403D-ACC6-B757E34774A4")

.comdef INetworkOperatorTetheringAccessPointConfiguration : public IInspectable

    get_Ssid		proc :ptr
    put_Ssid		proc :HSTRING
    get_Passphrase	proc :ptr
    put_Passphrase	proc :HSTRING
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CNetworkOperators_CINetworkOperatorTetheringOperationResult_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CNetworkOperators_CINetworkOperatorTetheringOperationResult_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_NetworkOperators_INetworkOperatorTetheringOperationResult <L"Windows.Networking.NetworkOperators.INetworkOperatorTetheringOperationResult">
DEFINE_IIDX(INetworkOperatorTetheringOperationResult, "EBD203A1-01BA-476D-B4B3-BF3D12C8F80C")

.comdef INetworkOperatorTetheringOperationResult : public IInspectable

    get_Status		proc :ptr
    get_AdditionalErrorMessage proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CNetworkOperators_CINetworkOperatorTetheringManagerStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CNetworkOperators_CINetworkOperatorTetheringManagerStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_NetworkOperators_INetworkOperatorTetheringManagerStatics <L"Windows.Networking.NetworkOperators.INetworkOperatorTetheringManagerStatics">
DEFINE_IIDX(INetworkOperatorTetheringManagerStatics, "3EBCBACC-F8C3-405C-9964-70A1EEABE194")

.comdef INetworkOperatorTetheringManagerStatics : public IInspectable

    GetTetheringCapability proc :HSTRING, :ptr
    CreateFromNetworkAccountId proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CNetworkOperators_CINetworkOperatorTetheringManager_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CNetworkOperators_CINetworkOperatorTetheringManager_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_NetworkOperators_INetworkOperatorTetheringManager <L"Windows.Networking.NetworkOperators.INetworkOperatorTetheringManager">
DEFINE_IIDX(INetworkOperatorTetheringManager, "D45A8DA0-0E86-4D98-8BA4-DD70D4B764D3")

.comdef INetworkOperatorTetheringManager : public IInspectable

    get_MaxClientCount	proc :ptr
    get_ClientCount	proc :ptr
    get_TetheringOperationalState proc :ptr
    GetCurrentAccessPointConfiguration proc :ptr
    ConfigureAccessPointAsync proc :ptr, :ptr
    StartTetheringAsync proc :ptr
    StopTetheringAsync	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CNetworkOperators_CIMobileBroadbandAccountEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CNetworkOperators_CIMobileBroadbandAccountEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_NetworkOperators_IMobileBroadbandAccountEventArgs <L"Windows.Networking.NetworkOperators.IMobileBroadbandAccountEventArgs">
DEFINE_IIDX(IMobileBroadbandAccountEventArgs, "3853C880-77DE-4C04-BEAD-A123B08C9F59")

.comdef IMobileBroadbandAccountEventArgs : public IInspectable

    get_NetworkAccountId proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CNetworkOperators_CIMobileBroadbandAccountUpdatedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CNetworkOperators_CIMobileBroadbandAccountUpdatedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_NetworkOperators_IMobileBroadbandAccountUpdatedEventArgs <L"Windows.Networking.NetworkOperators.IMobileBroadbandAccountUpdatedEventArgs">
DEFINE_IIDX(IMobileBroadbandAccountUpdatedEventArgs, "7BC31D88-A6BD-49E1-80AB-6B91354A57D4")

.comdef IMobileBroadbandAccountUpdatedEventArgs : public IInspectable

    get_NetworkAccountId proc :ptr
    get_HasDeviceInformationChanged proc :ptr
    get_HasNetworkChanged proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CNetworkOperators_CIMobileBroadbandAccountWatcher_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CNetworkOperators_CIMobileBroadbandAccountWatcher_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_NetworkOperators_IMobileBroadbandAccountWatcher <L"Windows.Networking.NetworkOperators.IMobileBroadbandAccountWatcher">
DEFINE_IIDX(IMobileBroadbandAccountWatcher, "6BF3335E-23B5-449F-928D-5E0D3E04471D")

.comdef IMobileBroadbandAccountWatcher : public IInspectable

    add_AccountAdded	proc :ptr, :ptr
    remove_AccountAdded proc :EventRegistrationToken
    add_AccountUpdated	proc :ptr, :ptr
    remove_AccountUpdated proc :EventRegistrationToken
    add_AccountRemoved	proc :ptr, :ptr
    remove_AccountRemoved proc :EventRegistrationToken
    add_EnumerationCompleted proc :ptr, :ptr
    remove_EnumerationCompleted proc :EventRegistrationToken
    add_Stopped		proc :ptr, :ptr
    remove_Stopped	proc :EventRegistrationToken
    get_Status		proc :ptr
    Start		proc
    Stop		proc
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CNetworkOperators_CIHotspotAuthenticationEventDetails_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CNetworkOperators_CIHotspotAuthenticationEventDetails_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_NetworkOperators_IHotspotAuthenticationEventDetails <L"Windows.Networking.NetworkOperators.IHotspotAuthenticationEventDetails">
DEFINE_IIDX(IHotspotAuthenticationEventDetails, "E756C791-1001-4DE5-83C7-DE61D88831D0")

.comdef IHotspotAuthenticationEventDetails : public IInspectable

    get_EventToken	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CNetworkOperators_CIHotspotAuthenticationContextStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CNetworkOperators_CIHotspotAuthenticationContextStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_NetworkOperators_IHotspotAuthenticationContextStatics <L"Windows.Networking.NetworkOperators.IHotspotAuthenticationContextStatics">
DEFINE_IIDX(IHotspotAuthenticationContextStatics, "E756C791-1002-4DE5-83C7-DE61D88831D0")

.comdef IHotspotAuthenticationContextStatics : public IInspectable

    TryGetAuthenticationContext proc :HSTRING, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CNetworkOperators_CIHotspotAuthenticationContext_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CNetworkOperators_CIHotspotAuthenticationContext_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_NetworkOperators_IHotspotAuthenticationContext <L"Windows.Networking.NetworkOperators.IHotspotAuthenticationContext">
DEFINE_IIDX(IHotspotAuthenticationContext, "E756C791-1003-4DE5-83C7-DE61D88831D0")

.comdef IHotspotAuthenticationContext : public IInspectable

    get_WirelessNetworkId proc :ptr, :ptr
    get_NetworkAdapter	proc :ptr
    get_RedirectMessageUrl proc :ptr
    get_RedirectMessageXml proc :ptr
    get_AuthenticationUrl proc :ptr
    IssueCredentials	proc :HSTRING, :HSTRING, :HSTRING, :boolean
    AbortAuthentication proc :boolean
    SkipAuthentication	proc
    TriggerAttentionRequired proc :HSTRING, :HSTRING
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CNetworkOperators_CIHotspotCredentialsAuthenticationResult_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CNetworkOperators_CIHotspotCredentialsAuthenticationResult_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_NetworkOperators_IHotspotCredentialsAuthenticationResult <L"Windows.Networking.NetworkOperators.IHotspotCredentialsAuthenticationResult">
DEFINE_IIDX(IHotspotCredentialsAuthenticationResult, "E756C791-1005-4DE5-83C7-DE61D88831D0")

.comdef IHotspotCredentialsAuthenticationResult : public IInspectable

    get_HasNetworkErrorOccurred proc :ptr
    get_ResponseCode	proc :ptr
    get_LogoffUrl	proc :ptr
    get_AuthenticationReplyXml proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CNetworkOperators_CIHotspotAuthenticationContext2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CNetworkOperators_CIHotspotAuthenticationContext2_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_NetworkOperators_IHotspotAuthenticationContext2 <L"Windows.Networking.NetworkOperators.IHotspotAuthenticationContext2">
DEFINE_IIDX(IHotspotAuthenticationContext2, "E756C791-1004-4DE5-83C7-DE61D88831D0")

.comdef IHotspotAuthenticationContext2 : public IInspectable

    IssueCredentialsAsync proc :HSTRING, :HSTRING, :HSTRING, :boolean, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CNetworkOperators_CIProvisionFromXmlDocumentResults_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CNetworkOperators_CIProvisionFromXmlDocumentResults_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_NetworkOperators_IProvisionFromXmlDocumentResults <L"Windows.Networking.NetworkOperators.IProvisionFromXmlDocumentResults">
DEFINE_IIDX(IProvisionFromXmlDocumentResults, "217700E0-8203-11DF-ADB9-F4CE462D9137")

.comdef IProvisionFromXmlDocumentResults : public IInspectable

    get_AllElementsProvisioned proc :ptr
    get_ProvisionResultsXml proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CNetworkOperators_CIProvisionedProfile_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CNetworkOperators_CIProvisionedProfile_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_NetworkOperators_IProvisionedProfile <L"Windows.Networking.NetworkOperators.IProvisionedProfile">
DEFINE_IIDX(IProvisionedProfile, "217700E0-8202-11DF-ADB9-F4CE462D9137")

.comdef IProvisionedProfile : public IInspectable

    UpdateCost		proc :Windows::Networking::Connectivity::NetworkCostType
    UpdateUsage		proc :Windows::Networking::NetworkOperators::ProfileUsage
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CNetworkOperators_CIProvisioningAgent_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CNetworkOperators_CIProvisioningAgent_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_NetworkOperators_IProvisioningAgent <L"Windows.Networking.NetworkOperators.IProvisioningAgent">
DEFINE_IIDX(IProvisioningAgent, "217700E0-8201-11DF-ADB9-F4CE462D9137")

.comdef IProvisioningAgent : public IInspectable

    ProvisionFromXmlDocumentAsync proc :HSTRING, :ptr
    GetProvisionedProfile proc :Windows::Networking::NetworkOperators::ProfileMediaType, :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CNetworkOperators_CIProvisioningAgentStaticMethods_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CNetworkOperators_CIProvisioningAgentStaticMethods_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_NetworkOperators_IProvisioningAgentStaticMethods <L"Windows.Networking.NetworkOperators.IProvisioningAgentStaticMethods">
DEFINE_IIDX(IProvisioningAgentStaticMethods, "217700E0-8101-11DF-ADB9-F4CE462D9137")

.comdef IProvisioningAgentStaticMethods : public IInspectable

    CreateFromNetworkAccountId proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CNetworkOperators_CIUssdMessage_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CNetworkOperators_CIUssdMessage_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_NetworkOperators_IUssdMessage <L"Windows.Networking.NetworkOperators.IUssdMessage">
DEFINE_IIDX(IUssdMessage, "2F9ACF82-2004-4D5D-BF81-2ABA1B4BE4A8")

.comdef IUssdMessage : public IInspectable

    get_DataCodingScheme proc :ptr
    put_DataCodingScheme proc :BYTE
    GetPayload		proc :ptr, :ptr
    SetPayload		proc :UINT32, :ptr
    get_PayloadAsText	proc :ptr
    put_PayloadAsText	proc :HSTRING
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CNetworkOperators_CIUssdMessageFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CNetworkOperators_CIUssdMessageFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_NetworkOperators_IUssdMessageFactory <L"Windows.Networking.NetworkOperators.IUssdMessageFactory">
DEFINE_IIDX(IUssdMessageFactory, "2F9ACF82-1003-4D5D-BF81-2ABA1B4BE4A8")

.comdef IUssdMessageFactory : public IInspectable

    CreateMessage	proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CNetworkOperators_CIUssdReply_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CNetworkOperators_CIUssdReply_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_NetworkOperators_IUssdReply <L"Windows.Networking.NetworkOperators.IUssdReply">
DEFINE_IIDX(IUssdReply, "2F9ACF82-2005-4D5D-BF81-2ABA1B4BE4A8")

.comdef IUssdReply : public IInspectable

    get_ResultCode	proc :ptr
    get_Message		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CNetworkOperators_CIUssdSession_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CNetworkOperators_CIUssdSession_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_NetworkOperators_IUssdSession <L"Windows.Networking.NetworkOperators.IUssdSession">
DEFINE_IIDX(IUssdSession, "2F9ACF82-2002-4D5D-BF81-2ABA1B4BE4A8")

.comdef IUssdSession : public IInspectable

    SendMessageAndGetReplyAsync proc :ptr, :ptr
    Close		proc
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CNetworkOperators_CIUssdSessionStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CNetworkOperators_CIUssdSessionStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_NetworkOperators_IUssdSessionStatics <L"Windows.Networking.NetworkOperators.IUssdSessionStatics">
DEFINE_IIDX(IUssdSessionStatics, "2F9ACF82-1001-4D5D-BF81-2ABA1B4BE4A8")

.comdef IUssdSessionStatics : public IInspectable

    CreateFromNetworkAccountId proc :HSTRING, :ptr
    CreateFromNetworkInterfaceId proc :HSTRING, :ptr
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_Networking_NetworkOperators_MobileBroadbandAccount_DEFINED
define RUNTIMECLASS_Windows_Networking_NetworkOperators_MobileBroadbandAccount_DEFINED
define RuntimeClass_Windows_Networking_NetworkOperators_MobileBroadbandAccount <L"Windows.Networking.NetworkOperators.MobileBroadbandAccount">
endif
ifndef RUNTIMECLASS_Windows_Networking_NetworkOperators_MobileBroadbandNetwork_DEFINED
define RUNTIMECLASS_Windows_Networking_NetworkOperators_MobileBroadbandNetwork_DEFINED
define RuntimeClass_Windows_Networking_NetworkOperators_MobileBroadbandNetwork <L"Windows.Networking.NetworkOperators.MobileBroadbandNetwork">
endif
ifndef RUNTIMECLASS_Windows_Networking_NetworkOperators_MobileBroadbandDeviceInformation_DEFINED
define RUNTIMECLASS_Windows_Networking_NetworkOperators_MobileBroadbandDeviceInformation_DEFINED
define RuntimeClass_Windows_Networking_NetworkOperators_MobileBroadbandDeviceInformation <L"Windows.Networking.NetworkOperators.MobileBroadbandDeviceInformation">
endif
ifndef RUNTIMECLASS_Windows_Networking_NetworkOperators_NetworkOperatorNotificationEventDetails_DEFINED
define RUNTIMECLASS_Windows_Networking_NetworkOperators_NetworkOperatorNotificationEventDetails_DEFINED
define RuntimeClass_Windows_Networking_NetworkOperators_NetworkOperatorNotificationEventDetails <L"Windows.Networking.NetworkOperators.NetworkOperatorNotificationEventDetails">
endif
ifndef RUNTIMECLASS_Windows_Networking_NetworkOperators_NetworkOperatorTetheringAccessPointConfiguration_DEFINED
define RUNTIMECLASS_Windows_Networking_NetworkOperators_NetworkOperatorTetheringAccessPointConfiguration_DEFINED
define RuntimeClass_Windows_Networking_NetworkOperators_NetworkOperatorTetheringAccessPointConfiguration <L"Windows.Networking.NetworkOperators.NetworkOperatorTetheringAccessPointConfiguration">
endif
ifndef RUNTIMECLASS_Windows_Networking_NetworkOperators_NetworkOperatorTetheringOperationResult_DEFINED
define RUNTIMECLASS_Windows_Networking_NetworkOperators_NetworkOperatorTetheringOperationResult_DEFINED
define RuntimeClass_Windows_Networking_NetworkOperators_NetworkOperatorTetheringOperationResult <L"Windows.Networking.NetworkOperators.NetworkOperatorTetheringOperationResult">
endif
ifndef RUNTIMECLASS_Windows_Networking_NetworkOperators_NetworkOperatorTetheringManager_DEFINED
define RUNTIMECLASS_Windows_Networking_NetworkOperators_NetworkOperatorTetheringManager_DEFINED
define RuntimeClass_Windows_Networking_NetworkOperators_NetworkOperatorTetheringManager <L"Windows.Networking.NetworkOperators.NetworkOperatorTetheringManager">
endif
ifndef RUNTIMECLASS_Windows_Networking_NetworkOperators_MobileBroadbandAccountEventArgs_DEFINED
define RUNTIMECLASS_Windows_Networking_NetworkOperators_MobileBroadbandAccountEventArgs_DEFINED
define RuntimeClass_Windows_Networking_NetworkOperators_MobileBroadbandAccountEventArgs <L"Windows.Networking.NetworkOperators.MobileBroadbandAccountEventArgs">
endif
ifndef RUNTIMECLASS_Windows_Networking_NetworkOperators_MobileBroadbandAccountUpdatedEventArgs_DEFINED
define RUNTIMECLASS_Windows_Networking_NetworkOperators_MobileBroadbandAccountUpdatedEventArgs_DEFINED
define RuntimeClass_Windows_Networking_NetworkOperators_MobileBroadbandAccountUpdatedEventArgs <L"Windows.Networking.NetworkOperators.MobileBroadbandAccountUpdatedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_Networking_NetworkOperators_MobileBroadbandAccountWatcher_DEFINED
define RUNTIMECLASS_Windows_Networking_NetworkOperators_MobileBroadbandAccountWatcher_DEFINED
define RuntimeClass_Windows_Networking_NetworkOperators_MobileBroadbandAccountWatcher <L"Windows.Networking.NetworkOperators.MobileBroadbandAccountWatcher">
endif
ifndef RUNTIMECLASS_Windows_Networking_NetworkOperators_HotspotAuthenticationEventDetails_DEFINED
define RUNTIMECLASS_Windows_Networking_NetworkOperators_HotspotAuthenticationEventDetails_DEFINED
define RuntimeClass_Windows_Networking_NetworkOperators_HotspotAuthenticationEventDetails <L"Windows.Networking.NetworkOperators.HotspotAuthenticationEventDetails">
endif
ifndef RUNTIMECLASS_Windows_Networking_NetworkOperators_HotspotAuthenticationContext_DEFINED
define RUNTIMECLASS_Windows_Networking_NetworkOperators_HotspotAuthenticationContext_DEFINED
define RuntimeClass_Windows_Networking_NetworkOperators_HotspotAuthenticationContext <L"Windows.Networking.NetworkOperators.HotspotAuthenticationContext">
endif
ifndef RUNTIMECLASS_Windows_Networking_NetworkOperators_HotspotCredentialsAuthenticationResult_DEFINED
define RUNTIMECLASS_Windows_Networking_NetworkOperators_HotspotCredentialsAuthenticationResult_DEFINED
define RuntimeClass_Windows_Networking_NetworkOperators_HotspotCredentialsAuthenticationResult <L"Windows.Networking.NetworkOperators.HotspotCredentialsAuthenticationResult">
endif
ifndef RUNTIMECLASS_Windows_Networking_NetworkOperators_ProvisionFromXmlDocumentResults_DEFINED
define RUNTIMECLASS_Windows_Networking_NetworkOperators_ProvisionFromXmlDocumentResults_DEFINED
define RuntimeClass_Windows_Networking_NetworkOperators_ProvisionFromXmlDocumentResults <L"Windows.Networking.NetworkOperators.ProvisionFromXmlDocumentResults">
endif
ifndef RUNTIMECLASS_Windows_Networking_NetworkOperators_ProvisionedProfile_DEFINED
define RUNTIMECLASS_Windows_Networking_NetworkOperators_ProvisionedProfile_DEFINED
define RuntimeClass_Windows_Networking_NetworkOperators_ProvisionedProfile <L"Windows.Networking.NetworkOperators.ProvisionedProfile">
endif
ifndef RUNTIMECLASS_Windows_Networking_NetworkOperators_ProvisioningAgent_DEFINED
define RUNTIMECLASS_Windows_Networking_NetworkOperators_ProvisioningAgent_DEFINED
define RuntimeClass_Windows_Networking_NetworkOperators_ProvisioningAgent <L"Windows.Networking.NetworkOperators.ProvisioningAgent">
endif
ifndef RUNTIMECLASS_Windows_Networking_NetworkOperators_UssdMessage_DEFINED
define RUNTIMECLASS_Windows_Networking_NetworkOperators_UssdMessage_DEFINED
define RuntimeClass_Windows_Networking_NetworkOperators_UssdMessage <L"Windows.Networking.NetworkOperators.UssdMessage">
endif
ifndef RUNTIMECLASS_Windows_Networking_NetworkOperators_UssdReply_DEFINED
define RUNTIMECLASS_Windows_Networking_NetworkOperators_UssdReply_DEFINED
define RuntimeClass_Windows_Networking_NetworkOperators_UssdReply <L"Windows.Networking.NetworkOperators.UssdReply">
endif
ifndef RUNTIMECLASS_Windows_Networking_NetworkOperators_UssdSession_DEFINED
define RUNTIMECLASS_Windows_Networking_NetworkOperators_UssdSession_DEFINED
define RuntimeClass_Windows_Networking_NetworkOperators_UssdSession <L"Windows.Networking.NetworkOperators.UssdSession">
endif

endif
