ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Enetworking2Econnectivity_h__
define __windows2Enetworking2Econnectivity_h__
ifndef __windows2Efoundation_h__
include Windows.Foundation.inc
endif
ifndef __windows2Enetworking_h__
include Windows.Networking.inc
endif

ifndef ____FIIterator_1_Windows__CNetworking__CConnectivity__CConnectionProfile_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CNetworking__CConnectivity__CConnectionProfile_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CNetworking__CConnectivity__CConnectionProfile, "89913732-a08b-5cb2-af16-bbbb2223839e")

.comdef __FIIterator_1_Windows__CNetworking__CConnectivity__CConnectionProfile : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CNetworking__CConnectivity__CConnectionProfile_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CNetworking__CConnectivity__CConnectionProfile_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CNetworking__CConnectivity__CConnectionProfile, "34dabef9-87d0-5b1c-a7ac-9d290adeb0c8")

.comdef __FIIterable_1_Windows__CNetworking__CConnectivity__CConnectionProfile : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CNetworking__CConnectivity__CConnectivityInterval_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CNetworking__CConnectivity__CConnectivityInterval_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CNetworking__CConnectivity__CConnectivityInterval, "741cea48-651c-5fd9-931e-4f91b521e182")

.comdef __FIIterator_1_Windows__CNetworking__CConnectivity__CConnectivityInterval : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CNetworking__CConnectivity__CConnectivityInterval_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CNetworking__CConnectivity__CConnectivityInterval_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CNetworking__CConnectivity__CConnectivityInterval, "58051a8b-b259-5414-9b9a-caa0789e833e")

.comdef __FIIterable_1_Windows__CNetworking__CConnectivity__CConnectivityInterval : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CNetworking__CConnectivity__CLanIdentifier_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CNetworking__CConnectivity__CLanIdentifier_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CNetworking__CConnectivity__CLanIdentifier, "2c5d2f7e-ce9c-5253-a0f4-01e5bdc11988")

.comdef __FIIterator_1_Windows__CNetworking__CConnectivity__CLanIdentifier : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CNetworking__CConnectivity__CLanIdentifier_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CNetworking__CConnectivity__CLanIdentifier_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CNetworking__CConnectivity__CLanIdentifier, "accef3cd-5d92-5c01-8ac4-79fe74cd733e")

.comdef __FIIterable_1_Windows__CNetworking__CConnectivity__CLanIdentifier : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CNetworking__CConnectivity__CNetworkUsage_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CNetworking__CConnectivity__CNetworkUsage_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CNetworking__CConnectivity__CNetworkUsage, "5fafb57b-9c82-50a1-9970-69f9cb069695")

.comdef __FIIterator_1_Windows__CNetworking__CConnectivity__CNetworkUsage : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CNetworking__CConnectivity__CNetworkUsage_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CNetworking__CConnectivity__CNetworkUsage_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CNetworking__CConnectivity__CNetworkUsage, "dd2656b1-8360-5772-b272-c47f7f0fc7a6")

.comdef __FIIterable_1_Windows__CNetworking__CConnectivity__CNetworkUsage : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CNetworking__CConnectivity__CConnectionProfile_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CNetworking__CConnectivity__CConnectionProfile_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CNetworking__CConnectivity__CConnectionProfile, "6db1b492-3852-5df8-a29d-6944002f58d4")

.comdef __FIVectorView_1_Windows__CNetworking__CConnectivity__CConnectionProfile : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CNetworking__CConnectivity__CConnectivityInterval_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CNetworking__CConnectivity__CConnectivityInterval_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CNetworking__CConnectivity__CConnectivityInterval, "a3d0d117-9e21-5919-b7a0-c8190bd55ac5")

.comdef __FIVectorView_1_Windows__CNetworking__CConnectivity__CConnectivityInterval : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CNetworking__CConnectivity__CLanIdentifier_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CNetworking__CConnectivity__CLanIdentifier_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CNetworking__CConnectivity__CLanIdentifier, "41286159-b91d-5736-ad8b-e16fcf8aced0")

.comdef __FIVectorView_1_Windows__CNetworking__CConnectivity__CLanIdentifier : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CNetworking__CConnectivity__CNetworkUsage_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CNetworking__CConnectivity__CNetworkUsage_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CNetworking__CConnectivity__CNetworkUsage, "b3853391-40b6-5cf5-8f46-4882691d1ff7")

.comdef __FIVectorView_1_Windows__CNetworking__CConnectivity__CNetworkUsage : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CNetworking__CConnectivity__CConnectionProfile_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CNetworking__CConnectivity__CConnectionProfile_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CNetworking__CConnectivity__CConnectionProfile, "c523d9dd-4ea6-5115-80e9-4e7ad4769798")

.comdef __FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CNetworking__CConnectivity__CConnectionProfile : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1___FIVectorView_1_Windows__CNetworking__CConnectivity__CConnectionProfile_INTERFACE_DEFINED__
define ____FIAsyncOperation_1___FIVectorView_1_Windows__CNetworking__CConnectivity__CConnectionProfile_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1___FIVectorView_1_Windows__CNetworking__CConnectivity__CConnectionProfile, "c0023294-c2cb-52f0-a9f4-21916032f69d")

.comdef __FIAsyncOperation_1___FIVectorView_1_Windows__CNetworking__CConnectivity__CConnectionProfile : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CNetworking__CConnectivity__CConnectivityInterval_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CNetworking__CConnectivity__CConnectivityInterval_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CNetworking__CConnectivity__CConnectivityInterval, "b475014c-95f1-5310-b5d1-c2309d944440")

.comdef __FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CNetworking__CConnectivity__CConnectivityInterval : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1___FIVectorView_1_Windows__CNetworking__CConnectivity__CConnectivityInterval_INTERFACE_DEFINED__
define ____FIAsyncOperation_1___FIVectorView_1_Windows__CNetworking__CConnectivity__CConnectivityInterval_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1___FIVectorView_1_Windows__CNetworking__CConnectivity__CConnectivityInterval, "af96d70b-41c7-5dc6-9895-ea043a885d8d")

.comdef __FIAsyncOperation_1___FIVectorView_1_Windows__CNetworking__CConnectivity__CConnectivityInterval : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CNetworking__CConnectivity__CNetworkUsage_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CNetworking__CConnectivity__CNetworkUsage_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CNetworking__CConnectivity__CNetworkUsage, "e31d7e7e-4173-5c71-b04b-a09658002590")

.comdef __FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CNetworking__CConnectivity__CNetworkUsage : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1___FIVectorView_1_Windows__CNetworking__CConnectivity__CNetworkUsage_INTERFACE_DEFINED__
define ____FIAsyncOperation_1___FIVectorView_1_Windows__CNetworking__CConnectivity__CNetworkUsage_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1___FIVectorView_1_Windows__CNetworking__CConnectivity__CNetworkUsage, "05c9e081-6229-5049-8eea-a498407c00d5")

.comdef __FIAsyncOperation_1___FIVectorView_1_Windows__CNetworking__CConnectivity__CNetworkUsage : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CNetworking__CConnectivity__CConnectionProfile_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CNetworking__CConnectivity__CConnectionProfile_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CNetworking__CConnectivity__CConnectionProfile, "e4f0c96a-0571-59f4-a9a9-afac3e61caa0")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CNetworking__CConnectivity__CConnectionProfile : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CNetworking__CConnectivity__CConnectionProfile_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CNetworking__CConnectivity__CConnectionProfile_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CNetworking__CConnectivity__CConnectionProfile, "5bf519ca-8adb-5ab5-abb8-ff1bbe5d2de8")

.comdef __FIAsyncOperation_1_Windows__CNetworking__CConnectivity__CConnectionProfile : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CNetworking__CConnectivity__CConnectionSession_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CNetworking__CConnectivity__CConnectionSession_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CNetworking__CConnectivity__CConnectionSession, "3bc680d8-9e83-5086-8f49-7a29bfb1c7e1")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CNetworking__CConnectivity__CConnectionSession : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CNetworking__CConnectivity__CConnectionSession_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CNetworking__CConnectivity__CConnectionSession_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CNetworking__CConnectivity__CConnectionSession, "94fc6211-4702-5d24-81bf-170ca7818995")

.comdef __FIAsyncOperation_1_Windows__CNetworking__CConnectivity__CConnectionSession : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CNetworking__CConnectivity__CProxyConfiguration_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CNetworking__CConnectivity__CProxyConfiguration_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CNetworking__CConnectivity__CProxyConfiguration, "035b2567-efb9-5bc3-b609-f9a8c20b7001")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CNetworking__CConnectivity__CProxyConfiguration : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CNetworking__CConnectivity__CProxyConfiguration_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CNetworking__CConnectivity__CProxyConfiguration_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CNetworking__CConnectivity__CProxyConfiguration, "1e7651f6-6562-59c7-9af3-8756636eeee2")

.comdef __FIAsyncOperation_1_Windows__CNetworking__CConnectivity__CProxyConfiguration : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

.namespace Windows
.namespace Networking
.namespace Connectivity

.enum NetworkCostType {
    NetworkCostType_Unknown	= 0,
    NetworkCostType_Unrestricted	= 1,
    NetworkCostType_Fixed	= 2,
    NetworkCostType_Variable	= 3
    }

.enum NetworkConnectivityLevel {
    NetworkConnectivityLevel_None	= 0,
    NetworkConnectivityLevel_LocalAccess	= 1,
    NetworkConnectivityLevel_ConstrainedInternetAccess	= 2,
    NetworkConnectivityLevel_InternetAccess	= 3
    }

.enum NetworkTypes {
    NetworkTypes_None	= 0,
    NetworkTypes_Internet	= 0x1,
    NetworkTypes_PrivateNetwork = 0x2
    }

.enum RoamingStates {
    RoamingStates_None	= 0,
    RoamingStates_NotRoaming	= 0x1,
    RoamingStates_Roaming	= 0x2
    }

.enum NetworkAuthenticationType {
    NetworkAuthenticationType_None	= 0,
    NetworkAuthenticationType_Unknown	= 1,
    NetworkAuthenticationType_Open80211 = 2,
    NetworkAuthenticationType_SharedKey80211	= 3,
    NetworkAuthenticationType_Wpa	= 4,
    NetworkAuthenticationType_WpaPsk	= 5,
    NetworkAuthenticationType_WpaNone	= 6,
    NetworkAuthenticationType_Rsna	= 7,
    NetworkAuthenticationType_RsnaPsk	= 8,
    NetworkAuthenticationType_Ihv	= 9
    }

.enum NetworkEncryptionType {
    NetworkEncryptionType_None	= 0,
    NetworkEncryptionType_Unknown	= 1,
    NetworkEncryptionType_Wep	= 2,
    NetworkEncryptionType_Wep40 = 3,
    NetworkEncryptionType_Wep104	= 4,
    NetworkEncryptionType_Tkip	= 5,
    NetworkEncryptionType_Ccmp	= 6,
    NetworkEncryptionType_WpaUseGroup	= 7,
    NetworkEncryptionType_RsnUseGroup	= 8,
    NetworkEncryptionType_Ihv	= 9
    }

.enum DomainConnectivityLevel {
    DomainConnectivityLevel_None	= 0,
    DomainConnectivityLevel_Unauthenticated	= 1,
    DomainConnectivityLevel_Authenticated	= 2
    }

.enum WwanNetworkRegistrationState {
    WwanNetworkRegistrationState_None	= 0,
    WwanNetworkRegistrationState_Deregistered	= 1,
    WwanNetworkRegistrationState_Searching	= 2,
    WwanNetworkRegistrationState_Home	= 3,
    WwanNetworkRegistrationState_Roaming	= 4,
    WwanNetworkRegistrationState_Partner	= 5,
    WwanNetworkRegistrationState_Denied = 6
    }

.enum DataUsageGranularity {
    DataUsageGranularity_PerMinute	= 0,
    DataUsageGranularity_PerHour	= 1,
    DataUsageGranularity_PerDay = 2,
    DataUsageGranularity_Total	= 3
    }

.enum CellularApnAuthenticationType {
    CellularApnAuthenticationType_None	= 0,
    CellularApnAuthenticationType_Pap	= 1,
    CellularApnAuthenticationType_Chap	= 2,
    CellularApnAuthenticationType_Mschapv2	= 3
    }

.enum WwanDataClass {
    WwanDataClass_None	= 0,
    WwanDataClass_Gprs	= 0x1,
    WwanDataClass_Edge	= 0x2,
    WwanDataClass_Umts	= 0x4,
    WwanDataClass_Hsdpa = 0x8,
    WwanDataClass_Hsupa = 0x10,
    WwanDataClass_LteAdvanced	= 0x20,
    WwanDataClass_Cdma1xRtt	= 0x10000,
    WwanDataClass_Cdma1xEvdo	= 0x20000,
    WwanDataClass_Cdma1xEvdoRevA	= 0x40000,
    WwanDataClass_Cdma1xEvdv	= 0x80000,
    WwanDataClass_Cdma3xRtt	= 0x100000,
    WwanDataClass_Cdma1xEvdoRevB	= 0x200000,
    WwanDataClass_CdmaUmb	= 0x400000,
    WwanDataClass_Custom	= 0x80000000
    }

.enum TriStates {
    TriStates_DoNotCare = 0,
    TriStates_No	= 1,
    TriStates_Yes	= 2
    }


.template NetworkUsageStates
    Roaming		Windows::Networking::Connectivity::TriStates ?
    Shared		Windows::Networking::Connectivity::TriStates ?
   .ends

ifndef ____x_ABI_CWindows_CNetworking_CConnectivity_CINetworkStatusChangedEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CConnectivity_CINetworkStatusChangedEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(INetworkStatusChangedEventHandler, "71BA143F-598E-49D0-84EB-8FEBAEDCC195")

.comdef INetworkStatusChangedEventHandler : public IUnknown

    _Invoke		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CConnectivity_CIDataUsage_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CConnectivity_CIDataUsage_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Connectivity_IDataUsage <L"Windows.Networking.Connectivity.IDataUsage">
DEFINE_IIDX(IDataUsage, "C1431DD3-B146-4D39-B959-0C69B096C512")

.comdef IDataUsage : public IInspectable

    get_BytesSent	proc :ptr
    get_BytesReceived	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CConnectivity_CIDataPlanUsage_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CConnectivity_CIDataPlanUsage_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Connectivity_IDataPlanUsage <L"Windows.Networking.Connectivity.IDataPlanUsage">
DEFINE_IIDX(IDataPlanUsage, "B921492D-3B44-47FF-B361-BE59E69ED1B0")

.comdef IDataPlanUsage : public IInspectable

    get_MegabytesUsed	proc :ptr
    get_LastSyncTime	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CConnectivity_CIDataPlanStatus_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CConnectivity_CIDataPlanStatus_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Connectivity_IDataPlanStatus <L"Windows.Networking.Connectivity.IDataPlanStatus">
DEFINE_IIDX(IDataPlanStatus, "977A8B8C-3885-40F3-8851-42CD2BD568BB")

.comdef IDataPlanStatus : public IInspectable

    get_DataPlanUsage	proc :ptr
    get_DataLimitInMegabytes proc :ptr
    get_InboundBitsPerSecond proc :ptr
    get_OutboundBitsPerSecond proc :ptr
    get_NextBillingCycle proc :ptr
    get_MaxTransferSizeInMegabytes proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CConnectivity_CIConnectionCost_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CConnectivity_CIConnectionCost_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Connectivity_IConnectionCost <L"Windows.Networking.Connectivity.IConnectionCost">
DEFINE_IIDX(IConnectionCost, "BAD7D829-3416-4B10-A202-BAC0B075BDAE")

.comdef IConnectionCost : public IInspectable

    get_NetworkCostType proc :ptr
    get_Roaming		proc :ptr
    get_OverDataLimit	proc :ptr
    get_ApproachingDataLimit proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CConnectivity_CINetworkSecuritySettings_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CConnectivity_CINetworkSecuritySettings_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Connectivity_INetworkSecuritySettings <L"Windows.Networking.Connectivity.INetworkSecuritySettings">
DEFINE_IIDX(INetworkSecuritySettings, "7CA07E8D-917B-4B5F-B84D-28F7A5AC5402")

.comdef INetworkSecuritySettings : public IInspectable

    get_NetworkAuthenticationType proc :ptr
    get_NetworkEncryptionType proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CConnectivity_CIConnectionProfile_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CConnectivity_CIConnectionProfile_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Connectivity_IConnectionProfile <L"Windows.Networking.Connectivity.IConnectionProfile">
DEFINE_IIDX(IConnectionProfile, "71BA143C-598E-49D0-84EB-8FEBAEDCC195")

.comdef IConnectionProfile : public IInspectable

    get_ProfileName	proc :ptr
    GetNetworkConnectivityLevel proc :ptr
    GetNetworkNames	proc :ptr
    GetConnectionCost	proc :ptr
    GetDataPlanStatus	proc :ptr
    get_NetworkAdapter	proc :ptr
    GetLocalUsage	proc :Windows::Foundation::DateTime, :Windows::Foundation::DateTime, :ptr
    GetLocalUsagePerRoamingStates proc :Windows::Foundation::DateTime, :Windows::Foundation::DateTime, :Windows::Networking::Connectivity::RoamingStates, :ptr
    get_NetworkSecuritySettings proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CConnectivity_CIWwanConnectionProfileDetails_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CConnectivity_CIWwanConnectionProfileDetails_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Connectivity_IWwanConnectionProfileDetails <L"Windows.Networking.Connectivity.IWwanConnectionProfileDetails">
DEFINE_IIDX(IWwanConnectionProfileDetails, "0E4DA8FE-835F-4DF3-82FD-DF556EBC09EF")

.comdef IWwanConnectionProfileDetails : public IInspectable

    get_HomeProviderId	proc :ptr
    get_AccessPointName proc :ptr
    GetNetworkRegistrationState proc :ptr
    GetCurrentDataClass proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CConnectivity_CIWlanConnectionProfileDetails_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CConnectivity_CIWlanConnectionProfileDetails_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Connectivity_IWlanConnectionProfileDetails <L"Windows.Networking.Connectivity.IWlanConnectionProfileDetails">
DEFINE_IIDX(IWlanConnectionProfileDetails, "562098CB-B35A-4BF1-A884-B7557E88FF86")

.comdef IWlanConnectionProfileDetails : public IInspectable

    GetConnectedSsid	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CConnectivity_CIConnectivityInterval_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CConnectivity_CIConnectivityInterval_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Connectivity_IConnectivityInterval <L"Windows.Networking.Connectivity.IConnectivityInterval">
DEFINE_IIDX(IConnectivityInterval, "4FAA3FFF-6746-4824-A964-EED8E87F8709")

.comdef IConnectivityInterval : public IInspectable

    get_StartTime	proc :ptr
    get_ConnectionDuration proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CConnectivity_CINetworkUsage_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CConnectivity_CINetworkUsage_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Connectivity_INetworkUsage <L"Windows.Networking.Connectivity.INetworkUsage">
DEFINE_IIDX(INetworkUsage, "49DA8FCE-9985-4927-BF5B-072B5C65F8D9")

.comdef INetworkUsage : public IInspectable

    get_BytesSent	proc :ptr
    get_BytesReceived	proc :ptr
    get_ConnectionDuration proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CConnectivity_CIConnectionProfile2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CConnectivity_CIConnectionProfile2_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Connectivity_IConnectionProfile2 <L"Windows.Networking.Connectivity.IConnectionProfile2">
DEFINE_IIDX(IConnectionProfile2, "E2045145-4C9F-400C-9150-7EC7D6E2888A")

.comdef IConnectionProfile2 : public IInspectable

    get_IsWwanConnectionProfile proc :ptr
    get_IsWlanConnectionProfile proc :ptr
    get_WwanConnectionProfileDetails proc :ptr
    get_WlanConnectionProfileDetails proc :ptr
    get_ServiceProviderGuid proc :ptr
    GetSignalBars	proc :ptr
    GetDomainConnectivityLevel proc :ptr
    GetNetworkUsageAsync proc :Windows::Foundation::DateTime, :Windows::Foundation::DateTime, :Windows::Networking::Connectivity::DataUsageGranularity, :Windows::Networking::Connectivity::NetworkUsageStates, :ptr
    GetConnectivityIntervalsAsync proc :Windows::Foundation::DateTime, :Windows::Foundation::DateTime, :Windows::Networking::Connectivity::NetworkUsageStates, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CConnectivity_CILanIdentifierData_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CConnectivity_CILanIdentifierData_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Connectivity_ILanIdentifierData <L"Windows.Networking.Connectivity.ILanIdentifierData">
DEFINE_IIDX(ILanIdentifierData, "A74E83C3-D639-45BE-A36A-C4E4AEAF6D9B")

.comdef ILanIdentifierData : public IInspectable

    get_Type		proc :ptr
    get_Value		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CConnectivity_CILanIdentifier_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CConnectivity_CILanIdentifier_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Connectivity_ILanIdentifier <L"Windows.Networking.Connectivity.ILanIdentifier">
DEFINE_IIDX(ILanIdentifier, "48AA53AA-1108-4546-A6CB-9A74DA4B7BA0")

.comdef ILanIdentifier : public IInspectable

    get_InfrastructureId proc :ptr
    get_PortId		proc :ptr
    get_NetworkAdapterId proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CConnectivity_CINetworkInformationStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CConnectivity_CINetworkInformationStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Connectivity_INetworkInformationStatics <L"Windows.Networking.Connectivity.INetworkInformationStatics">
DEFINE_IIDX(INetworkInformationStatics, "5074F851-950D-4165-9C15-365619481EEA")

.comdef INetworkInformationStatics : public IInspectable

    GetConnectionProfiles proc :ptr
    GetInternetConnectionProfile proc :ptr
    GetLanIdentifiers	proc :ptr
    GetHostNames	proc :ptr
    GetProxyConfigurationAsync proc :ptr, :ptr
    GetSortedEndpointPairs proc :ptr, :Windows::Networking::HostNameSortOptions, :ptr
    add_NetworkStatusChanged proc :ptr, :ptr
    remove_NetworkStatusChanged proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CConnectivity_CIConnectionProfileFilter_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CConnectivity_CIConnectionProfileFilter_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Connectivity_IConnectionProfileFilter <L"Windows.Networking.Connectivity.IConnectionProfileFilter">
DEFINE_IIDX(IConnectionProfileFilter, "204C7CC8-BD2D-4E8D-A4B3-455EC337388A")

.comdef IConnectionProfileFilter : public IInspectable

    put_IsConnected	proc :boolean
    get_IsConnected	proc :ptr
    put_IsWwanConnectionProfile proc :boolean
    get_IsWwanConnectionProfile proc :ptr
    put_IsWlanConnectionProfile proc :boolean
    get_IsWlanConnectionProfile proc :ptr
    put_NetworkCostType proc :Windows::Networking::Connectivity::NetworkCostType
    get_NetworkCostType proc :ptr
    put_ServiceProviderGuid proc :ptr
    get_ServiceProviderGuid proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CConnectivity_CINetworkInformationStatics2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CConnectivity_CINetworkInformationStatics2_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Connectivity_INetworkInformationStatics2 <L"Windows.Networking.Connectivity.INetworkInformationStatics2">
DEFINE_IIDX(INetworkInformationStatics2, "459CED14-2832-49B6-BA6E-E265F04786A8")

.comdef INetworkInformationStatics2 : public IInspectable

    FindConnectionProfilesAsync proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CConnectivity_CINetworkItem_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CConnectivity_CINetworkItem_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Connectivity_INetworkItem <L"Windows.Networking.Connectivity.INetworkItem">
DEFINE_IIDX(INetworkItem, "01BC4D39-F5E0-4567-A28C-42080C831B2B")

.comdef INetworkItem : public IInspectable

    get_NetworkId	proc :ptr
    GetNetworkTypes	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CConnectivity_CINetworkAdapter_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CConnectivity_CINetworkAdapter_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Connectivity_INetworkAdapter <L"Windows.Networking.Connectivity.INetworkAdapter">
DEFINE_IIDX(INetworkAdapter, "3B542E03-5388-496C-A8A3-AFFD39AEC2E6")

.comdef INetworkAdapter : public IInspectable

    get_OutboundMaxBitsPerSecond proc :ptr
    get_InboundMaxBitsPerSecond proc :ptr
    get_IanaInterfaceType proc :ptr
    get_NetworkItem	proc :ptr
    get_NetworkAdapterId proc :ptr
    GetConnectedProfileAsync proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CConnectivity_CIIPInformation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CConnectivity_CIIPInformation_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Connectivity_IIPInformation <L"Windows.Networking.Connectivity.IIPInformation">
DEFINE_IIDX(IIPInformation, "D85145E0-138F-47D7-9B3A-36BB488CEF33")

.comdef IIPInformation : public IInspectable

    get_NetworkAdapter	proc :ptr
    get_PrefixLength	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CConnectivity_CIProxyConfiguration_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CConnectivity_CIProxyConfiguration_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Connectivity_IProxyConfiguration <L"Windows.Networking.Connectivity.IProxyConfiguration">
DEFINE_IIDX(IProxyConfiguration, "EF3A60B4-9004-4DD6-B7D8-B3E502F4AAD0")

.comdef IProxyConfiguration : public IInspectable

    get_ProxyUris	proc :ptr
    get_CanConnectDirectly proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CConnectivity_CIConnectionSession_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CConnectivity_CIConnectionSession_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Connectivity_IConnectionSession <L"Windows.Networking.Connectivity.IConnectionSession">
DEFINE_IIDX(IConnectionSession, "FF905D4C-F83B-41B0-8A0C-1462D9C56B73")

.comdef IConnectionSession : public IInspectable

    get_ConnectionProfile proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CConnectivity_CIRoutePolicy_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CConnectivity_CIRoutePolicy_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Connectivity_IRoutePolicy <L"Windows.Networking.Connectivity.IRoutePolicy">
DEFINE_IIDX(IRoutePolicy, "11ABC4AC-0FC7-42E4-8742-569923B1CA11")

.comdef IRoutePolicy : public IInspectable

    get_ConnectionProfile proc :ptr
    get_HostName	proc :ptr
    get_HostNameType	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CConnectivity_CIRoutePolicyFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CConnectivity_CIRoutePolicyFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Connectivity_IRoutePolicyFactory <L"Windows.Networking.Connectivity.IRoutePolicyFactory">
DEFINE_IIDX(IRoutePolicyFactory, "36027933-A18E-4DB5-A697-F58FA7364E44")

.comdef IRoutePolicyFactory : public IInspectable

    CreateRoutePolicy	proc :ptr, :ptr, :Windows::Networking::DomainNameType, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CConnectivity_CICellularApnContext_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CConnectivity_CICellularApnContext_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Connectivity_ICellularApnContext <L"Windows.Networking.Connectivity.ICellularApnContext">
DEFINE_IIDX(ICellularApnContext, "6FA529F4-EFFD-4542-9AB2-705BBF94943A")

.comdef ICellularApnContext : public IInspectable

    get_ProviderId	proc :ptr
    put_ProviderId	proc :HSTRING
    get_AccessPointName proc :ptr
    put_AccessPointName proc :HSTRING
    get_UserName	proc :ptr
    put_UserName	proc :HSTRING
    get_Password	proc :ptr
    put_Password	proc :HSTRING
    get_IsCompressionEnabled proc :ptr
    put_IsCompressionEnabled proc :boolean
    get_AuthenticationType proc :ptr
    put_AuthenticationType proc :Windows::Networking::Connectivity::CellularApnAuthenticationType
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CConnectivity_CIConnectivityManagerStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CConnectivity_CIConnectivityManagerStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Connectivity_IConnectivityManagerStatics <L"Windows.Networking.Connectivity.IConnectivityManagerStatics">
DEFINE_IIDX(IConnectivityManagerStatics, "5120D4B1-4FB1-48B0-AFC9-42E0092A8164")

.comdef IConnectivityManagerStatics : public IInspectable

    AcquireConnectionAsync proc :ptr, :ptr
    AddHttpRoutePolicy	proc :ptr
    RemoveHttpRoutePolicy proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CConnectivity_CINetworkStateChangeEventDetails_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CConnectivity_CINetworkStateChangeEventDetails_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_Connectivity_INetworkStateChangeEventDetails <L"Windows.Networking.Connectivity.INetworkStateChangeEventDetails">
DEFINE_IIDX(INetworkStateChangeEventDetails, "1F0CF333-D7A6-44DD-A4E9-687C476B903D")

.comdef INetworkStateChangeEventDetails : public IInspectable

    get_HasNewInternetConnectionProfile proc :ptr
    get_HasNewConnectionCost proc :ptr
    get_HasNewNetworkConnectivityLevel proc :ptr
    get_HasNewDomainConnectivityLevel proc :ptr
    get_HasNewHostNameList proc :ptr
    get_HasNewWwanRegistrationState proc :ptr
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_Networking_Connectivity_IPInformation_DEFINED
define RUNTIMECLASS_Windows_Networking_Connectivity_IPInformation_DEFINED
define RuntimeClass_Windows_Networking_Connectivity_IPInformation <L"Windows.Networking.Connectivity.IPInformation">
endif
ifndef RUNTIMECLASS_Windows_Networking_Connectivity_DataPlanUsage_DEFINED
define RUNTIMECLASS_Windows_Networking_Connectivity_DataPlanUsage_DEFINED
define RuntimeClass_Windows_Networking_Connectivity_DataPlanUsage <L"Windows.Networking.Connectivity.DataPlanUsage">
endif
ifndef RUNTIMECLASS_Windows_Networking_Connectivity_ConnectionCost_DEFINED
define RUNTIMECLASS_Windows_Networking_Connectivity_ConnectionCost_DEFINED
define RuntimeClass_Windows_Networking_Connectivity_ConnectionCost <L"Windows.Networking.Connectivity.ConnectionCost">
endif
ifndef RUNTIMECLASS_Windows_Networking_Connectivity_DataPlanStatus_DEFINED
define RUNTIMECLASS_Windows_Networking_Connectivity_DataPlanStatus_DEFINED
define RuntimeClass_Windows_Networking_Connectivity_DataPlanStatus <L"Windows.Networking.Connectivity.DataPlanStatus">
endif
ifndef RUNTIMECLASS_Windows_Networking_Connectivity_NetworkAdapter_DEFINED
define RUNTIMECLASS_Windows_Networking_Connectivity_NetworkAdapter_DEFINED
define RuntimeClass_Windows_Networking_Connectivity_NetworkAdapter <L"Windows.Networking.Connectivity.NetworkAdapter">
endif
ifndef RUNTIMECLASS_Windows_Networking_Connectivity_DataUsage_DEFINED
define RUNTIMECLASS_Windows_Networking_Connectivity_DataUsage_DEFINED
define RuntimeClass_Windows_Networking_Connectivity_DataUsage <L"Windows.Networking.Connectivity.DataUsage">
endif
ifndef RUNTIMECLASS_Windows_Networking_Connectivity_NetworkSecuritySettings_DEFINED
define RUNTIMECLASS_Windows_Networking_Connectivity_NetworkSecuritySettings_DEFINED
define RuntimeClass_Windows_Networking_Connectivity_NetworkSecuritySettings <L"Windows.Networking.Connectivity.NetworkSecuritySettings">
endif
ifndef RUNTIMECLASS_Windows_Networking_Connectivity_WwanConnectionProfileDetails_DEFINED
define RUNTIMECLASS_Windows_Networking_Connectivity_WwanConnectionProfileDetails_DEFINED
define RuntimeClass_Windows_Networking_Connectivity_WwanConnectionProfileDetails <L"Windows.Networking.Connectivity.WwanConnectionProfileDetails">
endif
ifndef RUNTIMECLASS_Windows_Networking_Connectivity_WlanConnectionProfileDetails_DEFINED
define RUNTIMECLASS_Windows_Networking_Connectivity_WlanConnectionProfileDetails_DEFINED
define RuntimeClass_Windows_Networking_Connectivity_WlanConnectionProfileDetails <L"Windows.Networking.Connectivity.WlanConnectionProfileDetails">
endif
ifndef RUNTIMECLASS_Windows_Networking_Connectivity_NetworkUsage_DEFINED
define RUNTIMECLASS_Windows_Networking_Connectivity_NetworkUsage_DEFINED
define RuntimeClass_Windows_Networking_Connectivity_NetworkUsage <L"Windows.Networking.Connectivity.NetworkUsage">
endif
ifndef RUNTIMECLASS_Windows_Networking_Connectivity_ConnectivityInterval_DEFINED
define RUNTIMECLASS_Windows_Networking_Connectivity_ConnectivityInterval_DEFINED
define RuntimeClass_Windows_Networking_Connectivity_ConnectivityInterval <L"Windows.Networking.Connectivity.ConnectivityInterval">
endif
ifndef RUNTIMECLASS_Windows_Networking_Connectivity_LanIdentifierData_DEFINED
define RUNTIMECLASS_Windows_Networking_Connectivity_LanIdentifierData_DEFINED
define RuntimeClass_Windows_Networking_Connectivity_LanIdentifierData <L"Windows.Networking.Connectivity.LanIdentifierData">
endif
ifndef RUNTIMECLASS_Windows_Networking_Connectivity_ConnectionProfile_DEFINED
define RUNTIMECLASS_Windows_Networking_Connectivity_ConnectionProfile_DEFINED
define RuntimeClass_Windows_Networking_Connectivity_ConnectionProfile <L"Windows.Networking.Connectivity.ConnectionProfile">
endif
ifndef RUNTIMECLASS_Windows_Networking_Connectivity_LanIdentifier_DEFINED
define RUNTIMECLASS_Windows_Networking_Connectivity_LanIdentifier_DEFINED
define RuntimeClass_Windows_Networking_Connectivity_LanIdentifier <L"Windows.Networking.Connectivity.LanIdentifier">
endif
ifndef RUNTIMECLASS_Windows_Networking_Connectivity_ProxyConfiguration_DEFINED
define RUNTIMECLASS_Windows_Networking_Connectivity_ProxyConfiguration_DEFINED
define RuntimeClass_Windows_Networking_Connectivity_ProxyConfiguration <L"Windows.Networking.Connectivity.ProxyConfiguration">
endif
ifndef RUNTIMECLASS_Windows_Networking_Connectivity_ConnectionProfileFilter_DEFINED
define RUNTIMECLASS_Windows_Networking_Connectivity_ConnectionProfileFilter_DEFINED
define RuntimeClass_Windows_Networking_Connectivity_ConnectionProfileFilter <L"Windows.Networking.Connectivity.ConnectionProfileFilter">
endif
ifndef RUNTIMECLASS_Windows_Networking_Connectivity_NetworkItem_DEFINED
define RUNTIMECLASS_Windows_Networking_Connectivity_NetworkItem_DEFINED
define RuntimeClass_Windows_Networking_Connectivity_NetworkItem <L"Windows.Networking.Connectivity.NetworkItem">
endif
ifndef RUNTIMECLASS_Windows_Networking_Connectivity_RoutePolicy_DEFINED
define RUNTIMECLASS_Windows_Networking_Connectivity_RoutePolicy_DEFINED
define RuntimeClass_Windows_Networking_Connectivity_RoutePolicy <L"Windows.Networking.Connectivity.RoutePolicy">
endif
ifndef RUNTIMECLASS_Windows_Networking_Connectivity_CellularApnContext_DEFINED
define RUNTIMECLASS_Windows_Networking_Connectivity_CellularApnContext_DEFINED
define RuntimeClass_Windows_Networking_Connectivity_CellularApnContext <L"Windows.Networking.Connectivity.CellularApnContext">
endif
ifndef RUNTIMECLASS_Windows_Networking_Connectivity_ConnectionSession_DEFINED
define RUNTIMECLASS_Windows_Networking_Connectivity_ConnectionSession_DEFINED
define RuntimeClass_Windows_Networking_Connectivity_ConnectionSession <L"Windows.Networking.Connectivity.ConnectionSession">
endif
ifndef RUNTIMECLASS_Windows_Networking_Connectivity_NetworkInformation_DEFINED
define RUNTIMECLASS_Windows_Networking_Connectivity_NetworkInformation_DEFINED
define RuntimeClass_Windows_Networking_Connectivity_NetworkInformation <L"Windows.Networking.Connectivity.NetworkInformation">
endif
ifndef RUNTIMECLASS_Windows_Networking_Connectivity_ConnectivityManager_DEFINED
define RUNTIMECLASS_Windows_Networking_Connectivity_ConnectivityManager_DEFINED
define RuntimeClass_Windows_Networking_Connectivity_ConnectivityManager <L"Windows.Networking.Connectivity.ConnectivityManager">
endif
ifndef RUNTIMECLASS_Windows_Networking_Connectivity_NetworkStateChangeEventDetails_DEFINED
define RUNTIMECLASS_Windows_Networking_Connectivity_NetworkStateChangeEventDetails_DEFINED
define RuntimeClass_Windows_Networking_Connectivity_NetworkStateChangeEventDetails <L"Windows.Networking.Connectivity.NetworkStateChangeEventDetails">
endif

endif

