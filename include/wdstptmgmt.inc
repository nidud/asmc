ifndef _RPCNDR500_
include rpcndr500.inc
endif

ifndef __wdstptmgmt_h__
define __wdstptmgmt_h__

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

.enum WDSTRANSPORT_FEATURE_FLAGS {
	WdsTptFeatureAdminPack		= 0x1,
	WdsTptFeatureTransportServer	= 0x2,
	WdsTptFeatureDeploymentServer	= 0x4
	}

PWDSTRANSPORT_FEATURE_FLAGS typedef ptr WDSTRANSPORT_FEATURE_FLAGS

define WDSTRANSPORT_FEATURE_FLAGS_ALL  ( WdsTptFeatureAdminPack or WdsTptFeatureTransportServer or WdsTptFeatureDeploymentServer )

.enum WDSTRANSPORT_PROTOCOL_FLAGS {
	WdsTptProtocolUnicast	= 0x1,
	WdsTptProtocolMulticast = 0x2
	}

PWDSTRANSPORT_PROTOCOL_FLAGS typedef ptr WDSTRANSPORT_PROTOCOL_FLAGS

.enum WDSTRANSPORT_NAMESPACE_TYPE {
	WdsTptNamespaceTypeUnknown,
	WdsTptNamespaceTypeAutoCast,
	WdsTptNamespaceTypeScheduledCastManualStart,
	WdsTptNamespaceTypeScheduledCastAutoStart
	}

PWDSTRANSPORT_NAMESPACE_TYPE typedef ptr WDSTRANSPORT_NAMESPACE_TYPE

.enum WDSTRANSPORT_DISCONNECT_TYPE {
	WdsTptDisconnectUnknown,
	WdsTptDisconnectFallback,
	WdsTptDisconnectAbort
    }

PWDSTRANSPORT_DISCONNECT_TYPE typedef ptr WDSTRANSPORT_DISCONNECT_TYPE

.enum WDSTRANSPORT_SERVICE_NOTIFICATION {
	WdsTptServiceNotifyUnknown,
	WdsTptServiceNotifyReadSettings
    }

PWDSTRANSPORT_SERVICE_NOTIFICATION typedef ptr WDSTRANSPORT_SERVICE_NOTIFICATION

.enum WDSTRANSPORT_IP_ADDRESS_TYPE {
	WdsTptIpAddressUnknown,
	WdsTptIpAddressIpv4,
	WdsTptIpAddressIpv6
    }

PWDSTRANSPORT_IP_ADDRESS_TYPE typedef ptr WDSTRANSPORT_IP_ADDRESS_TYPE

.enum WDSTRANSPORT_IP_ADDRESS_SOURCE_TYPE {
	WdsTptIpAddressSourceUnknown,
	WdsTptIpAddressSourceDhcp,
	WdsTptIpAddressSourceRange
    }

PWDSTRANSPORT_IP_ADDRESS_SOURCE_TYPE typedef ptr WDSTRANSPORT_IP_ADDRESS_SOURCE_TYPE

.enum WDSTRANSPORT_NETWORK_PROFILE_TYPE {
	WdsTptNetworkProfileUnknown,
	WdsTptNetworkProfileCustom,
	WdsTptNetworkProfile10Mbps,
	WdsTptNetworkProfile100Mbps,
	WdsTptNetworkProfile1Gbps
	}

PWDSTRANSPORT_NETWORK_PROFILE_TYPE typedef ptr WDSTRANSPORT_NETWORK_PROFILE_TYPE

.enum WDSTRANSPORT_DIAGNOSTICS_COMPONENT_FLAGS {
	WdsTptDiagnosticsComponentPxe		= 0x1,
	WdsTptDiagnosticsComponentTftp		= 0x2,
	WdsTptDiagnosticsComponentImageServer	= 0x4,
	WdsTptDiagnosticsComponentMulticast	= 0x8
	}

PWDSTRANSPORT_DIAGNOSTICS_COMPONENT_FLAGS typedef ptr WDSTRANSPORT_DIAGNOSTICS_COMPONENT_FLAGS

define WDSTRANSPORT_DIAGNOSTICS_COMPONENT_FLAGS_ALL  ( WdsTptDiagnosticsComponentPxe or WdsTptDiagnosticsComponentTftp or WdsTptDiagnosticsComponentImageServer or WdsTptDiagnosticsComponentMulticast )
define WDSTRANSPORT_RESOURCE_UTILIZATION_UNKNOWN    0xFF

.enum WDSTRANSPORT_SLOW_CLIENT_HANDLING_TYPE {
	WdsTptSlowClientHandlingUnknown,
	WdsTptSlowClientHandlingNone,
	WdsTptSlowClientHandlingAutoDisconnect,
	WdsTptSlowClientHandlingMultistream
	}

PWDSTRANSPORT_SLOW_CLIENT_HANDLING_TYPE typedef ptr WDSTRANSPORT_SLOW_CLIENT_HANDLING_TYPE

.enum WDSTRANSPORT_UDP_PORT_POLICY {
	WdsTptUdpPortPolicyDynamic,
	WdsTptUdpPortPolicyFixed
	}

PWDSTRANSPORT_UDP_PORT_POLICY typedef ptr WDSTRANSPORT_UDP_PORT_POLICY

.enum WDSTRANSPORT_TFTP_CAPABILITY {
	WdsTptTftpCapMaximumBlockSize	= 0x1,
	WdsTptTftpCapVariableWindow	= 0x2
	}

PWDSTRANSPORT_TFTP_CAPABILITY typedef ptr WDSTRANSPORT_TFTP_CAPABILITY

ifndef __IWdsTransportCacheable_INTERFACE_DEFINED__
define __IWdsTransportCacheable_INTERFACE_DEFINED__

DEFINE_IIDX(IWdsTransportCacheable, "46AD894B-0BAB-47DC-84B2-7B553F1D8F80")

.comdef IWdsTransportCacheable : public IDispatch
    get_Dirty		proc :ptr
    Discard		proc
    Refresh		proc
    Commit		proc
   .ends

endif

ifndef __IWdsTransportCollection_INTERFACE_DEFINED__
define __IWdsTransportCollection_INTERFACE_DEFINED__

DEFINE_IIDX(IWdsTransportCollection, "B8BA4B1A-2FF4-43AB-996C-B2B10A91A6EB")

.comdef IWdsTransportCollection : public IDispatch
    get_Count		proc :ptr
    get_Item		proc :ULONG, :ptr ptr
    get__NewEnum	proc :ptr ptr
   .ends

endif

ifndef __IWdsTransportManager_INTERFACE_DEFINED__
define __IWdsTransportManager_INTERFACE_DEFINED__

DEFINE_IIDX(IWdsTransportManager, "5B0D35F5-1B13-4AFD-B878-6526DC340B5D")

.comdef IWdsTransportManager : public IDispatch
    GetWdsTransportServer proc :BSTR, :ptr ptr
   .ends

endif

ifndef __IWdsTransportServer_INTERFACE_DEFINED__
define __IWdsTransportServer_INTERFACE_DEFINED__

DEFINE_IIDX(IWdsTransportServer, "09CCD093-830D-4344-A30A-73AE8E8FCA90")

.comdef IWdsTransportServer : public IDispatch
    get_Name		proc :ptr
    get_SetupManager	proc :ptr ptr
    get_ConfigurationManager proc :ptr ptr
    get_NamespaceManager proc :ptr ptr
    DisconnectClient	proc :ULONG, :WDSTRANSPORT_DISCONNECT_TYPE
   .ends

endif

ifndef __IWdsTransportServer2_INTERFACE_DEFINED__
define __IWdsTransportServer2_INTERFACE_DEFINED__

DEFINE_IIDX(IWdsTransportServer2, "256e999f-6df4-4538-81b9-857b9ab8fb47")

.comdef IWdsTransportServer2 : public IWdsTransportServer
    get_TftpManager	proc :ptr ptr
   .ends

endif

ifndef __IWdsTransportSetupManager_INTERFACE_DEFINED__
define __IWdsTransportSetupManager_INTERFACE_DEFINED__

DEFINE_IIDX(IWdsTransportSetupManager, "F7238425-EFA8-40A4-AEF9-C98D969C0B75")

.comdef IWdsTransportSetupManager : public IDispatch
    get_Version		proc :ptr
    get_InstalledFeatures proc :ptr
    get_Protocols	proc :ptr
    RegisterContentProvider proc :BSTR, :BSTR, :BSTR, :BSTR
    DeregisterContentProvider proc :BSTR
   .ends

endif

ifndef __IWdsTransportSetupManager2_INTERFACE_DEFINED__
define __IWdsTransportSetupManager2_INTERFACE_DEFINED__

DEFINE_IIDX(IWdsTransportSetupManager2, "02BE79DA-7E9E-4366-8B6E-2AA9A91BE47F")

.comdef IWdsTransportSetupManager2 : public IWdsTransportSetupManager
    get_TftpCapabilities proc :ptr
    get_ContentProviders proc :ptr ptr
   .ends

endif

ifndef __IWdsTransportConfigurationManager_INTERFACE_DEFINED__
define __IWdsTransportConfigurationManager_INTERFACE_DEFINED__

DEFINE_IIDX(IWdsTransportConfigurationManager, "84CC4779-42DD-4792-891E-1321D6D74B44")

.comdef IWdsTransportConfigurationManager : public IDispatch
    get_ServicePolicy	proc :ptr ptr
    get_DiagnosticsPolicy proc :ptr ptr
    get_WdsTransportServicesRunning proc :VARIANT_BOOL, :ptr
    EnableWdsTransportServices proc
    DisableWdsTransportServices proc
    StartWdsTransportServices proc
    StopWdsTransportServices proc
    RestartWdsTransportServices proc
    NotifyWdsTransportServices proc :WDSTRANSPORT_SERVICE_NOTIFICATION
   .ends

endif

ifndef __IWdsTransportConfigurationManager2_INTERFACE_DEFINED__
define __IWdsTransportConfigurationManager2_INTERFACE_DEFINED__

DEFINE_IIDX(IWdsTransportConfigurationManager2, "D0D85CAF-A153-4F1D-A9DD-96F431C50717")

.comdef IWdsTransportConfigurationManager2 : public IWdsTransportConfigurationManager
    get_MulticastSessionPolicy proc :ptr ptr
   .ends

endif

ifndef __IWdsTransportNamespaceManager_INTERFACE_DEFINED__
define __IWdsTransportNamespaceManager_INTERFACE_DEFINED__

DEFINE_IIDX(IWdsTransportNamespaceManager, "3E22D9F6-3777-4D98-83E1-F98696717BA3")

.comdef IWdsTransportNamespaceManager : public IDispatch
    CreateNamespace	proc :WDSTRANSPORT_NAMESPACE_TYPE, :BSTR, :BSTR, :BSTR, :ptr ptr
    RetrieveNamespace	proc :BSTR, :ptr ptr
    RetrieveNamespaces	proc :BSTR, :BSTR, :VARIANT_BOOL, :ptr ptr
   .ends

endif

ifndef __IWdsTransportTftpManager_INTERFACE_DEFINED__
define __IWdsTransportTftpManager_INTERFACE_DEFINED__

DEFINE_IIDX(IWdsTransportTftpManager, "1327a7c8-ae8a-4fb3-8150-136227c37e9a")

.comdef IWdsTransportTftpManager : public IDispatch
    RetrieveTftpClients proc :ptr ptr
   .ends

endif

ifndef __IWdsTransportServicePolicy_INTERFACE_DEFINED__
define __IWdsTransportServicePolicy_INTERFACE_DEFINED__

DEFINE_IIDX(IWdsTransportServicePolicy, "B9468578-9F2B-48CC-B27A-A60799C2750C")

.comdef IWdsTransportServicePolicy : public IWdsTransportCacheable
    get_IpAddressSource proc :WDSTRANSPORT_IP_ADDRESS_TYPE, :ptr
    put_IpAddressSource proc :WDSTRANSPORT_IP_ADDRESS_TYPE, :WDSTRANSPORT_IP_ADDRESS_SOURCE_TYPE
    get_StartIpAddress	proc :WDSTRANSPORT_IP_ADDRESS_TYPE, :ptr
    put_StartIpAddress	proc :WDSTRANSPORT_IP_ADDRESS_TYPE, :BSTR
    get_EndIpAddress	proc :WDSTRANSPORT_IP_ADDRESS_TYPE, :ptr
    put_EndIpAddress	proc :WDSTRANSPORT_IP_ADDRESS_TYPE, :BSTR
    get_StartPort	proc :ptr
    put_StartPort	proc :ULONG
    get_EndPort		proc :ptr
    put_EndPort		proc :ULONG
    get_NetworkProfile	proc :ptr
    put_NetworkProfile	proc :WDSTRANSPORT_NETWORK_PROFILE_TYPE
   .ends

endif

ifndef __IWdsTransportServicePolicy2_INTERFACE_DEFINED__
define __IWdsTransportServicePolicy2_INTERFACE_DEFINED__

DEFINE_IIDX(IWdsTransportServicePolicy2, "65C19E5C-AA7E-4B91-8944-91E0E5572797")

.comdef IWdsTransportServicePolicy2 : public IWdsTransportServicePolicy
    get_UdpPortPolicy	proc :ptr
    put_UdpPortPolicy	proc :WDSTRANSPORT_UDP_PORT_POLICY
    get_TftpMaximumBlockSize proc :ptr
    put_TftpMaximumBlockSize proc :ULONG
    get_EnableTftpVariableWindowExtension proc :ptr
    put_EnableTftpVariableWindowExtension proc :VARIANT_BOOL
   .ends

endif

ifndef __IWdsTransportDiagnosticsPolicy_INTERFACE_DEFINED__
define __IWdsTransportDiagnosticsPolicy_INTERFACE_DEFINED__

DEFINE_IIDX(IWdsTransportDiagnosticsPolicy, "13B33EFC-7856-4F61-9A59-8DE67B6B87B6")

.comdef IWdsTransportDiagnosticsPolicy : public IWdsTransportCacheable
    get_Enabled		proc :ptr
    put_Enabled		proc :VARIANT_BOOL
    get_Components	proc :ptr
    put_Components	proc :ULONG
   .ends

endif

ifndef __IWdsTransportMulticastSessionPolicy_INTERFACE_DEFINED__
define __IWdsTransportMulticastSessionPolicy_INTERFACE_DEFINED__

DEFINE_IIDX(IWdsTransportMulticastSessionPolicy, "4E5753CF-68EC-4504-A951-4A003266606B")

.comdef IWdsTransportMulticastSessionPolicy : public IWdsTransportCacheable
    get_SlowClientHandling proc :ptr
    put_SlowClientHandling proc :WDSTRANSPORT_SLOW_CLIENT_HANDLING_TYPE
    get_AutoDisconnectThreshold proc :ptr
    put_AutoDisconnectThreshold proc :ULONG
    get_MultistreamStreamCount proc :ptr
    put_MultistreamStreamCount proc :ULONG
    get_SlowClientFallback proc :ptr
    put_SlowClientFallback proc :VARIANT_BOOL
   .ends

endif

ifndef __IWdsTransportNamespace_INTERFACE_DEFINED__
define __IWdsTransportNamespace_INTERFACE_DEFINED__

DEFINE_IIDX(IWdsTransportNamespace, "FA561F57-FBEF-4ED3-B056-127CB1B33B84")

.comdef IWdsTransportNamespace : public IDispatch
    get_Type		proc :ptr
    get_Id		proc :ptr
    get_Name		proc :ptr
    put_Name		proc :BSTR
    get_FriendlyName	proc :ptr
    put_FriendlyName	proc :BSTR
    get_Description	proc :ptr
    put_Description	proc :BSTR
    get_ContentProvider proc :ptr
    put_ContentProvider proc :BSTR
    get_Configuration	proc :ptr
    put_Configuration	proc :BSTR
    get_Registered	proc :ptr
    get_Tombstoned	proc :ptr
    get_TombstoneTime	proc :ptr
    get_TransmissionStarted proc :ptr
    Register		proc
    Deregister		proc :VARIANT_BOOL
    Clone		proc :ptr ptr
    Refresh		proc
    RetrieveContents	proc :ptr ptr
   .ends

endif

ifndef __IWdsTransportNamespaceAutoCast_INTERFACE_DEFINED__
define __IWdsTransportNamespaceAutoCast_INTERFACE_DEFINED__

DEFINE_IIDX(IWdsTransportNamespaceAutoCast, "AD931A72-C4BD-4C41-8FBC-59C9C748DF9E")

.comdef IWdsTransportNamespaceAutoCast : public IWdsTransportNamespace
   .ends

endif

ifndef __IWdsTransportNamespaceScheduledCast_INTERFACE_DEFINED__
define __IWdsTransportNamespaceScheduledCast_INTERFACE_DEFINED__

DEFINE_IIDX(IWdsTransportNamespaceScheduledCast, "3840CECF-D76C-416E-A4CC-31C741D2874B")

.comdef IWdsTransportNamespaceScheduledCast : public IWdsTransportNamespace
    StartTransmission	proc
   .ends

endif

ifndef __IWdsTransportNamespaceScheduledCastManualStart_INTERFACE_DEFINED__
define __IWdsTransportNamespaceScheduledCastManualStart_INTERFACE_DEFINED__

DEFINE_IIDX(IWdsTransportNamespaceScheduledCastManualStart, "013E6E4C-E6A7-4FB5-B7FF-D9F5DA805C31")

.comdef IWdsTransportNamespaceScheduledCastManualStart : public IWdsTransportNamespaceScheduledCast
   .ends

endif

ifndef __IWdsTransportNamespaceScheduledCastAutoStart_INTERFACE_DEFINED__
define __IWdsTransportNamespaceScheduledCastAutoStart_INTERFACE_DEFINED__

DEFINE_IIDX(IWdsTransportNamespaceScheduledCastAutoStart, "D606AF3D-EA9C-4219-961E-7491D618D9B9")

.comdef IWdsTransportNamespaceScheduledCastAutoStart : public IWdsTransportNamespaceScheduledCast
    get_MinimumClients	proc :ptr
    put_MinimumClients	proc :ULONG
    get_StartTime	proc :ptr
    put_StartTime	proc :DATE
   .ends

endif

ifndef __IWdsTransportContent_INTERFACE_DEFINED__
define __IWdsTransportContent_INTERFACE_DEFINED__

DEFINE_IIDX(IWdsTransportContent, "D405D711-0296-4AB4-A860-AC7D32E65798")

.comdef IWdsTransportContent : public IDispatch
    get_Namespace	proc :ptr ptr
    get_Id		proc :ptr
    get_Name		proc :ptr
    RetrieveSessions	proc :ptr ptr
    Terminate		proc
   .ends

endif

ifndef __IWdsTransportSession_INTERFACE_DEFINED__
define __IWdsTransportSession_INTERFACE_DEFINED__

DEFINE_IIDX(IWdsTransportSession, "F4EFEA88-65B1-4F30-A4B9-2793987796FB")

.comdef IWdsTransportSession : public IDispatch
    get_Content		proc :ptr ptr
    get_Id		proc :ptr
    get_NetworkInterfaceName proc :ptr
    get_NetworkInterfaceAddress proc :ptr
    get_TransferRate	proc :ptr
    get_MasterClientId	proc :ptr
    RetrieveClients	proc :ptr ptr
    Terminate		proc
   .ends

endif

ifndef __IWdsTransportClient_INTERFACE_DEFINED__
define __IWdsTransportClient_INTERFACE_DEFINED__

DEFINE_IIDX(IWdsTransportClient, "B5DBC93A-CABE-46CA-837F-3E44E93C6545")

.comdef IWdsTransportClient : public IDispatch
    get_Session		proc :ptr ptr
    get_Id		proc :ptr
    get_Name		proc :ptr
    get_MacAddress	proc :ptr
    get_IpAddress	proc :ptr
    get_PercentCompletion proc :ptr
    get_JoinDuration	proc :ptr
    get_CpuUtilization	proc :ptr
    get_MemoryUtilization proc :ptr
    get_NetworkUtilization proc :ptr
    get_UserIdentity	proc :ptr
    Disconnect		proc :WDSTRANSPORT_DISCONNECT_TYPE
   .ends

endif

ifndef __IWdsTransportTftpClient_INTERFACE_DEFINED__
define __IWdsTransportTftpClient_INTERFACE_DEFINED__

DEFINE_IIDX(IWdsTransportTftpClient, "b022d3ae-884d-4d85-b146-53320e76ef62")

.comdef IWdsTransportTftpClient : public IDispatch
    get_FileName	proc :ptr
    get_IpAddress	proc :ptr
    get_Timeout		proc :ptr
    get_CurrentFileOffset proc :ptr
    get_FileSize	proc :ptr
    get_BlockSize	proc :ptr
    get_WindowSize	proc :ptr
   .ends

endif

ifndef __IWdsTransportContentProvider_INTERFACE_DEFINED__
define __IWdsTransportContentProvider_INTERFACE_DEFINED__

DEFINE_IIDX(IWdsTransportContentProvider, "B9489F24-F219-4ACF-AAD7-265C7C08A6AE")

.comdef IWdsTransportContentProvider : public IDispatch
    get_Name		proc :ptr
    get_Description	proc :ptr
    get_FilePath	proc :ptr
    get_InitializationRoutine proc :ptr
   .ends

endif

ifndef __WdsTptMgmtLib_LIBRARY_DEFINED__
define __WdsTptMgmtLib_LIBRARY_DEFINED__

DEFINE_GUID(LIBID_WdsTptMgmtLib, 0x9212887F,0xF5BC,0x45DD,0xA5,0x10,0x26,0x54,0x13,0xA1,0x8E,0xD7)

DEFINE_GUIDS(CLSID_WdsTransportCacheable, "70590B16-F146-46BD-BD9D-4AAA90084BF5")
DEFINE_GUIDS(CLSID_WdsTransportCollection, "C7F18B09-391E-436E-B10B-C3EF46F2C34F")
DEFINE_GUIDS(CLSID_WdsTransportManager, "F21523F6-837C-4A58-AF99-8A7E27F8FF59")
DEFINE_GUIDS(CLSID_WdsTransportServer, "EA19B643-4ADF-4413-942C-14F379118760")
DEFINE_GUIDS(CLSID_WdsTransportSetupManager, "C7BEEAAD-9F04-4923-9F0C-FBF52BC7590F")
DEFINE_GUIDS(CLSID_WdsTransportConfigurationManager, "8743F674-904C-47CA-8512-35FE98F6B0AC")
DEFINE_GUIDS(CLSID_WdsTransportNamespaceManager, "F08CDB63-85DE-4A28-A1A9-5CA3E7EFDA73")
DEFINE_GUIDS(CLSID_WdsTransportServicePolicy, "65ACEADC-2F0B-4F43-9F4D-811865D8CEAD")
DEFINE_GUIDS(CLSID_WdsTransportDiagnosticsPolicy, "EB3333E1-A7AD-46F5-80D6-6B740204E509")
DEFINE_GUIDS(CLSID_WdsTransportMulticastSessionPolicy, "3C6BC3F4-6418-472A-B6F1-52D457195437")
DEFINE_GUIDS(CLSID_WdsTransportNamespace, "D8385768-0732-4EC1-95EA-16DA581908A1")
DEFINE_GUIDS(CLSID_WdsTransportNamespaceAutoCast, "B091F5A8-6A99-478D-B23B-09E8FEE04574")
DEFINE_GUIDS(CLSID_WdsTransportNamespaceScheduledCast, "BADC1897-7025-44EB-9108-FB61C4055792")
DEFINE_GUIDS(CLSID_WdsTransportNamespaceScheduledCastManualStart, "D3E1A2AA-CAAC-460E-B98A-47F9F318A1FA")
DEFINE_GUIDS(CLSID_WdsTransportNamespaceScheduledCastAutoStart, "A1107052-122C-4B81-9B7C-386E6855383F")
DEFINE_GUIDS(CLSID_WdsTransportContent, "0A891FE7-4A3F-4C65-B6F2-1467619679EA")
DEFINE_GUIDS(CLSID_WdsTransportSession, "749AC4E0-67BC-4743-BFE5-CACB1F26F57F")
DEFINE_GUIDS(CLSID_WdsTransportClient, "66D2C5E9-0FF6-49EC-9733-DAFB1E01DF1C")
DEFINE_GUIDS(CLSID_WdsTransportTftpClient, "50343925-7c5c-4c8c-96c4-ad9fa5005fba")
DEFINE_GUIDS(CLSID_WdsTransportTftpManager, "c8e9dca2-3241-4e4d-b806-bc74019dfeda")
DEFINE_GUIDS(CLSID_WdsTransportContentProvider, "E0BE741F-5A75-4EB9-8A2D-5E189B45F327")

endif

endif

endif
