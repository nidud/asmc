ifndef __REQUIRED_RPCNDR_H_VERSION__
define __REQUIRED_RPCNDR_H_VERSION__ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
define __REQUIRED_RPCSAL_H_VERSION__ 100
endif

include rpc.inc
include rpcndr.inc
ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr.inc>
endif

ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif

ifndef __bdaiface_h__
define __bdaiface_h__

include unknwn.inc
include strmif.inc
include BdaTypes.inc
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

.enum SmartCardStatusType {
    CardInserted	= 0,
    CardRemoved = ( CardInserted + 1 ) ,
    CardError	= ( CardRemoved + 1 ) ,
    CardDataChanged	= ( CardError + 1 ) ,
    CardFirmwareUpgrade = ( CardDataChanged + 1 )
    }

.enum SmartCardAssociationType {
    NotAssociated	= 0,
    Associated	= ( NotAssociated + 1 ) ,
    AssociationUnknown	= ( Associated + 1 )
    }

.enum LocationCodeSchemeType {
    SCTE_18	= 0
    }

EALocationCodeType	STRUC
LocationCodeScheme	LocationCodeSchemeType ?
state_code		db ?
county_subdivision	db ?
county_code		dw ?
EALocationCodeType	ENDS

.enum EntitlementType {
    Entitled	= 0,
    NotEntitled = ( Entitled + 1 ) ,
    TechnicalFailure	= ( NotEntitled + 1 )
    }

.enum UICloseReasonType {
    NotReady	= 0,
    UserClosed	= ( NotReady + 1 ) ,
    SystemClosed	= ( UserClosed + 1 ) ,
    DeviceClosed	= ( SystemClosed + 1 ) ,
    ErrorClosed = ( DeviceClosed + 1 )
    }

SmartCardApplication	STRUC
ApplicationType		ApplicationTypeType ?
ApplicationVersion	USHORT ?
pbstrApplicationName	BSTR ?
pbstrApplicationURL	BSTR ?
SmartCardApplication	ENDS

.enum BDA_DrmPairingError {
    BDA_DrmPairing_Succeeded	= 0,
    BDA_DrmPairing_HardwareFailure	= ( BDA_DrmPairing_Succeeded + 1 ) ,
    BDA_DrmPairing_NeedRevocationData	= ( BDA_DrmPairing_HardwareFailure + 1 ) ,
    BDA_DrmPairing_NeedIndiv	= ( BDA_DrmPairing_NeedRevocationData + 1 ) ,
    BDA_DrmPairing_Other	= ( BDA_DrmPairing_NeedIndiv + 1 ) ,
    BDA_DrmPairing_DrmInitFailed	= ( BDA_DrmPairing_Other + 1 ) ,
    BDA_DrmPairing_DrmNotPaired = ( BDA_DrmPairing_DrmInitFailed + 1 ) ,
    BDA_DrmPairing_DrmRePairSoon	= ( BDA_DrmPairing_DrmNotPaired + 1 ) ,
    BDA_DrmPairing_Aborted	= ( BDA_DrmPairing_DrmRePairSoon + 1 ) ,
    BDA_DrmPairing_NeedSDKUpdate	= ( BDA_DrmPairing_Aborted + 1 )
    }


ifndef __IBDA_NetworkProvider_INTERFACE_DEFINED__
define __IBDA_NetworkProvider_INTERFACE_DEFINED__

DEFINE_IIDX(IBDA_NetworkProvider, "fd501041-8ebe-11ce-8183-00aa00577da2")

.comdef IBDA_NetworkProvider : public IUnknown

    PutSignalSource	proc :ULONG
    GetSignalSource	proc :ptr
    GetNetworkType	proc :ptr
    PutTuningSpace	proc :REFGUID
    GetTuningSpace	proc :ptr
    RegisterDeviceFilter proc :ptr, :ptr
    UnRegisterDeviceFilter proc :ULONG
   .ends

endif

ifndef __IBDA_EthernetFilter_INTERFACE_DEFINED__
define __IBDA_EthernetFilter_INTERFACE_DEFINED__

DEFINE_IIDX(IBDA_EthernetFilter, "71985F43-1CA1-11d3-9CC8-00C04F7971E0")

.comdef IBDA_EthernetFilter : public IUnknown

    GetMulticastListSize proc :ptr
    PutMulticastList	proc :ULONG, :BYTE
    GetMulticastList	proc :ptr, :BYTE
    PutMulticastMode	proc :ULONG
    GetMulticastMode	proc :ptr
   .ends

endif


ifndef __IBDA_IPV4Filter_INTERFACE_DEFINED__
define __IBDA_IPV4Filter_INTERFACE_DEFINED__

DEFINE_IIDX(IBDA_IPV4Filter, "71985F44-1CA1-11d3-9CC8-00C04F7971E0")

.comdef IBDA_IPV4Filter : public IUnknown

    GetMulticastListSize proc :ptr
    PutMulticastList	proc :ULONG, :BYTE
    GetMulticastList	proc :ptr, :BYTE
    PutMulticastMode	proc :ULONG
    GetMulticastMode	proc :ptr
   .ends

endif


ifndef __IBDA_IPV6Filter_INTERFACE_DEFINED__
define __IBDA_IPV6Filter_INTERFACE_DEFINED__

DEFINE_IIDX(IBDA_IPV6Filter, "E1785A74-2A23-4fb3-9245-A8F88017EF33")

.comdef IBDA_IPV6Filter : public IUnknown

    GetMulticastListSize proc :ptr
    PutMulticastList	proc :ULONG, :BYTE
    GetMulticastList	proc :ptr, :BYTE
    PutMulticastMode	proc :ULONG
    GetMulticastMode	proc :ptr
   .ends

endif


ifndef __IBDA_DeviceControl_INTERFACE_DEFINED__
define __IBDA_DeviceControl_INTERFACE_DEFINED__

DEFINE_IIDX(IBDA_DeviceControl, "FD0A5AF3-B41D-11d2-9C95-00C04F7971E0")

.comdef IBDA_DeviceControl : public IUnknown

    StartChanges	proc
    CheckChanges	proc
    CommitChanges	proc
    GetChangeState	proc :ptr
   .ends

endif


ifndef __IBDA_PinControl_INTERFACE_DEFINED__
define __IBDA_PinControl_INTERFACE_DEFINED__

DEFINE_IIDX(IBDA_PinControl, "0DED49D5-A8B7-4d5d-97A1-12B0C195874D")

.comdef IBDA_PinControl : public IUnknown

    GetPinID		proc :ptr
    GetPinType		proc :ptr
    RegistrationContext proc :ptr
   .ends

endif


ifndef __IBDA_SignalProperties_INTERFACE_DEFINED__
define __IBDA_SignalProperties_INTERFACE_DEFINED__

DEFINE_IIDX(IBDA_SignalProperties, "D2F1644B-B409-11d2-BC69-00A0C9EE9E16")

.comdef IBDA_SignalProperties : public IUnknown

    PutNetworkType	proc :REFGUID
    GetNetworkType	proc :ptr
    PutSignalSource	proc :ULONG
    GetSignalSource	proc :ptr
    PutTuningSpace	proc :REFGUID
    GetTuningSpace	proc :ptr
   .ends

endif


ifndef __IBDA_SignalStatistics_INTERFACE_DEFINED__
define __IBDA_SignalStatistics_INTERFACE_DEFINED__

DEFINE_IIDX(IBDA_SignalStatistics, "1347D106-CF3A-428a-A5CB-AC0D9A2A4338")

.comdef IBDA_SignalStatistics : public IUnknown

    put_SignalStrength	proc :LONG
    get_SignalStrength	proc :ptr
    put_SignalQuality	proc :LONG
    get_SignalQuality	proc :ptr
    put_SignalPresent	proc :BOOLEAN
    get_SignalPresent	proc :ptr
    put_SignalLocked	proc :BOOLEAN
    get_SignalLocked	proc :ptr
    put_SampleTime	proc :LONG
    get_SampleTime	proc :ptr
   .ends

endif


ifndef __IBDA_Topology_INTERFACE_DEFINED__
define __IBDA_Topology_INTERFACE_DEFINED__

DEFINE_IIDX(IBDA_Topology, "79B56888-7FEA-4690-B45D-38FD3C7849BE")

.comdef IBDA_Topology : public IUnknown

    GetNodeTypes	proc :ptr, :ULONG, :ULONG
    GetNodeDescriptors	proc :ptr, :ULONG, :BDANODE_DESCRIPTOR
    GetNodeInterfaces	proc :ULONG, :ptr, :ULONG, :GUID
    GetPinTypes		proc :ptr, :ULONG, :ULONG
    GetTemplateConnections proc :ptr, :ULONG, :BDA_TEMPLATE_CONNECTION
    CreatePin		proc :ULONG, :ptr
    DeletePin		proc :ULONG
    SetMediaType	proc :ULONG, :ptr
    SetMedium		proc :ULONG, :ptr
    CreateTopology	proc :ULONG, :ULONG
    GetControlNode	proc :ULONG, :ULONG, :ULONG, :ptr
   .ends

endif

ifndef __IBDA_VoidTransform_INTERFACE_DEFINED__
define __IBDA_VoidTransform_INTERFACE_DEFINED__

DEFINE_IIDX(IBDA_VoidTransform, "71985F46-1CA1-11d3-9CC8-00C04F7971E0")

.comdef IBDA_VoidTransform : public IUnknown

    Start		proc
    Stop		proc
   .ends

endif

ifndef __IBDA_NullTransform_INTERFACE_DEFINED__
define __IBDA_NullTransform_INTERFACE_DEFINED__

DEFINE_IIDX(IBDA_NullTransform, "DDF15B0D-BD25-11d2-9CA0-00C04F7971E0")

.comdef IBDA_NullTransform : public IUnknown

    Start		proc
    Stop		proc
   .ends

endif

ifndef __IBDA_FrequencyFilter_INTERFACE_DEFINED__
define __IBDA_FrequencyFilter_INTERFACE_DEFINED__

DEFINE_IIDX(IBDA_FrequencyFilter, "71985F47-1CA1-11d3-9CC8-00C04F7971E0")

.comdef IBDA_FrequencyFilter : public IUnknown

    put_Autotune	proc :ULONG
    get_Autotune	proc :ptr
    put_Frequency	proc :ULONG
    get_Frequency	proc :ptr
    put_Polarity	proc :Polarisation
    get_Polarity	proc :ptr
    put_Range		proc :ULONG
    get_Range		proc :ptr
    put_Bandwidth	proc :ULONG
    get_Bandwidth	proc :ptr
    put_FrequencyMultiplier proc :ULONG
    get_FrequencyMultiplier proc :ptr
   .ends

endif

ifndef __IBDA_LNBInfo_INTERFACE_DEFINED__
define __IBDA_LNBInfo_INTERFACE_DEFINED__

DEFINE_IIDX(IBDA_LNBInfo, "992CF102-49F9-4719-A664-C4F23E2408F4")

.comdef IBDA_LNBInfo : public IUnknown

    put_LocalOscilatorFrequencyLowBand proc :ULONG
    get_LocalOscilatorFrequencyLowBand proc :ptr
    put_LocalOscilatorFrequencyHighBand proc :ULONG
    get_LocalOscilatorFrequencyHighBand proc :ptr
    put_HighLowSwitchFrequency proc :ULONG
    get_HighLowSwitchFrequency proc :ptr
    .ends

endif

ifndef __IBDA_DiseqCommand_INTERFACE_DEFINED__
define __IBDA_DiseqCommand_INTERFACE_DEFINED__

DEFINE_IIDX(IBDA_DiseqCommand, "F84E2AB0-3C6B-45e3-A0FC-8669D4B81F11")

.comdef IBDA_DiseqCommand : public IUnknown

    put_EnableDiseqCommands proc :BOOLEAN
    put_DiseqLNBSource	proc :ULONG
    put_DiseqUseToneBurst proc :BOOLEAN
    put_DiseqRepeats	proc :ULONG
    put_DiseqSendCommand proc :ULONG, :ULONG, :ptr
    get_DiseqResponse	proc :ULONG, :ptr, :BYTE
   .ends

endif

ifndef __IBDA_AutoDemodulate_INTERFACE_DEFINED__
define __IBDA_AutoDemodulate_INTERFACE_DEFINED__

DEFINE_IIDX(IBDA_AutoDemodulate, "DDF15B12-BD25-11d2-9CA0-00C04F7971E0")

.comdef IBDA_AutoDemodulate : public IUnknown

    put_AutoDemodulate	proc
   .ends

endif

ifndef __IBDA_AutoDemodulateEx_INTERFACE_DEFINED__
define __IBDA_AutoDemodulateEx_INTERFACE_DEFINED__

DEFINE_IIDX(IBDA_AutoDemodulateEx, "34518D13-1182-48e6-B28F-B24987787326")

.comdef IBDA_AutoDemodulateEx : public IBDA_AutoDemodulate

    get_SupportedDeviceNodeTypes proc :ULONG, :ptr, :ptr
    get_SupportedVideoFormats proc :ptr, :ptr
    get_AuxInputCount	proc :ptr, :ptr
   .ends

endif

ifndef __IBDA_DigitalDemodulator_INTERFACE_DEFINED__
define __IBDA_DigitalDemodulator_INTERFACE_DEFINED__

DEFINE_IIDX(IBDA_DigitalDemodulator, "EF30F379-985B-4d10-B640-A79D5E04E1E0")

.comdef IBDA_DigitalDemodulator : public IUnknown

    put_ModulationType	proc :ptr
    get_ModulationType	proc :ptr
    put_InnerFECMethod	proc :ptr
    get_InnerFECMethod	proc :ptr
    put_InnerFECRate	proc :ptr
    get_InnerFECRate	proc :ptr
    put_OuterFECMethod	proc :ptr
    get_OuterFECMethod	proc :ptr
    put_OuterFECRate	proc :ptr
    get_OuterFECRate	proc :ptr
    put_SymbolRate	proc :ptr
    get_SymbolRate	proc :ptr
    put_SpectralInversion proc :ptr
    get_SpectralInversion proc :ptr
   .ends

endif

ifndef __IBDA_DigitalDemodulator2_INTERFACE_DEFINED__
define __IBDA_DigitalDemodulator2_INTERFACE_DEFINED__

DEFINE_IIDX(IBDA_DigitalDemodulator2, "525ED3EE-5CF3-4e1e-9A06-5368A84F9A6E")

.comdef IBDA_DigitalDemodulator2 : public IBDA_DigitalDemodulator

    put_GuardInterval	proc :ptr
    get_GuardInterval	proc :ptr
    put_TransmissionMode proc :ptr
    get_TransmissionMode proc :ptr
    put_RollOff		proc :ptr
    get_RollOff		proc :ptr
    put_Pilot		proc :ptr
    get_Pilot		proc :ptr
   .ends

endif

ifndef __IBDA_DigitalDemodulator3_INTERFACE_DEFINED__
define __IBDA_DigitalDemodulator3_INTERFACE_DEFINED__

DEFINE_IIDX(IBDA_DigitalDemodulator3, "13F19604-7D32-4359-93A2-A05205D90AC9")

.comdef IBDA_DigitalDemodulator3 : public IBDA_DigitalDemodulator2

    put_SignalTimeouts	proc :ptr
    get_SignalTimeouts	proc :ptr
    put_PLPNumber	proc :ptr
    get_PLPNumber	proc :ptr
   .ends

endif

.enum _MIDL___MIDL_itf_bdaiface_0000_0019_0001 {
    KSPROPERTY_IPSINK_MULTICASTLIST	= 0,
    KSPROPERTY_IPSINK_ADAPTER_DESCRIPTION	= ( KSPROPERTY_IPSINK_MULTICASTLIST + 1 ) ,
    KSPROPERTY_IPSINK_ADAPTER_ADDRESS	= ( KSPROPERTY_IPSINK_ADAPTER_DESCRIPTION + 1 )
    }


ifndef __ICCSubStreamFiltering_INTERFACE_DEFINED__
define __ICCSubStreamFiltering_INTERFACE_DEFINED__

DEFINE_IIDX(ICCSubStreamFiltering, "4B2BD7EA-8347-467b-8DBF-62F784929CC3")

.comdef ICCSubStreamFiltering : public IUnknown

    get_SubstreamTypes	proc :ptr
    put_SubstreamTypes	proc :long_t
   .ends

endif

ifndef __IBDA_IPSinkControl_INTERFACE_DEFINED__
define __IBDA_IPSinkControl_INTERFACE_DEFINED__

DEFINE_IIDX(IBDA_IPSinkControl, "3F4DC8E2-4050-11d3-8F4B-00C04F7971E2")

.comdef IBDA_IPSinkControl : public IUnknown

    GetMulticastList	proc :ptr
    GetAdapterIPAddress proc :ptr
   .ends

endif

ifndef __IBDA_IPSinkInfo_INTERFACE_DEFINED__
define __IBDA_IPSinkInfo_INTERFACE_DEFINED__

DEFINE_IIDX(IBDA_IPSinkInfo, "A750108F-492E-4d51-95F7-649B23FF7AD7")

.comdef IBDA_IPSinkInfo : public IUnknown

    get_MulticastList	proc :ptr, :ptr
    get_AdapterIPAddress proc :ptr
    get_AdapterDescription proc :ptr
   .ends

endif

ifndef __IEnumPIDMap_INTERFACE_DEFINED__
define __IEnumPIDMap_INTERFACE_DEFINED__

DEFINE_IIDX(IEnumPIDMap, "afb6c2a2-2c41-11d3-8a60-0000f81e0e4a")

.comdef IEnumPIDMap : public IUnknown

    Next		proc :ULONG
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
   .ends

endif

ifndef __IMPEG2PIDMap_INTERFACE_DEFINED__
define __IMPEG2PIDMap_INTERFACE_DEFINED__

DEFINE_IIDX(IMPEG2PIDMap, "afb6c2a1-2c41-11d3-8a60-0000f81e0e4a")

.comdef IMPEG2PIDMap : public IUnknown

    MapPID		proc :ULONG, :ptr, :MEDIA_SAMPLE_CONTENT
    UnmapPID		proc :ULONG, :ptr
    EnumPIDMap		proc :ptr
   .ends

endif

ifndef __IFrequencyMap_INTERFACE_DEFINED__
define __IFrequencyMap_INTERFACE_DEFINED__

DEFINE_IIDX(IFrequencyMap, "06FB45C1-693C-4ea7-B79F-7A6A54D8DEF2")

.comdef IFrequencyMap : public IUnknown

    get_FrequencyMapping proc :ptr ULONG, :ptr ptr ULONG
    put_FrequencyMapping proc :ULONG, :ptr ULONG
    get_CountryCode	proc :ptr ULONG
    put_CountryCode	proc :ULONG
    get_DefaultFrequencyMapping proc :ULONG, :ptr ULONG, :ptr ptr ULONG
    get_CountryCodeList proc :ptr ULONG, :ptr ptr ULONG
   .ends

endif

ifndef __IBDA_EasMessage_INTERFACE_DEFINED__
define __IBDA_EasMessage_INTERFACE_DEFINED__

DEFINE_IIDX(IBDA_EasMessage, "D806973D-3EBE-46de-8FBB-6358FE784208")

.comdef IBDA_EasMessage : public IUnknown

    get_EasMessage	proc :ULONG, :ptr ptr IUnknown
   .ends

endif


ifndef __IBDA_TransportStreamInfo_INTERFACE_DEFINED__
define __IBDA_TransportStreamInfo_INTERFACE_DEFINED__

DEFINE_IIDX(IBDA_TransportStreamInfo, "8E882535-5F86-47AB-86CF-C281A72A0549")

.comdef IBDA_TransportStreamInfo : public IUnknown

    get_PatTableTickCount proc :ptr ULONG
   .ends

endif

ifndef __IBDA_ConditionalAccess_INTERFACE_DEFINED__
define __IBDA_ConditionalAccess_INTERFACE_DEFINED__

DEFINE_IIDX(IBDA_ConditionalAccess, "CD51F1E0-7BE9-4123-8482-A2A796C0A6B0")

.comdef IBDA_ConditionalAccess : public IUnknown

    get_SmartCardStatus proc :ptr, :ptr, :ptr, :ptr
    get_SmartCardInfo	proc :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
    get_SmartCardApplications proc :ptr ULONG, :ULONG, :ptr SmartCardApplication
    get_Entitlement	proc :USHORT, :ptr EntitlementType
    TuneByChannel	proc :USHORT
    SetProgram		proc :USHORT
    AddProgram		proc :USHORT
    RemoveProgram	proc :USHORT
    GetModuleUI		proc :BYTE, :ptr BSTR
    InformUIClosed	proc :BYTE, :UICloseReasonType
   .ends

endif

ifndef __IBDA_DiagnosticProperties_INTERFACE_DEFINED__
define __IBDA_DiagnosticProperties_INTERFACE_DEFINED__

DEFINE_IIDX(IBDA_DiagnosticProperties, "20e80cb5-c543-4c1b-8eb3-49e719eee7d4")

.comdef IBDA_DiagnosticProperties : public IPropertyBag
   .ends

endif

ifndef __IBDA_DRM_INTERFACE_DEFINED__
define __IBDA_DRM_INTERFACE_DEFINED__

DEFINE_IIDX(IBDA_DRM, "F98D88B0-1992-4cd6-A6D9-B9AFAB99330D")

.comdef IBDA_DRM : public IUnknown

    GetDRMPairingStatus proc :ptr, :ptr
    PerformDRMPairing	proc :BOOL
   .ends

endif

ifndef __IBDA_NameValueService_INTERFACE_DEFINED__
define __IBDA_NameValueService_INTERFACE_DEFINED__

DEFINE_IIDX(IBDA_NameValueService, "7F0B3150-7B81-4ad4-98E3-7E9097094301")

.comdef IBDA_NameValueService : public IUnknown

    GetValueNameByIndex proc :ULONG, :ptr BSTR
    GetValue		proc :BSTR, :BSTR, :ptr BSTR
    SetValue		proc :ULONG, :BSTR, :BSTR, :BSTR, :ULONG
   .ends

endif

ifndef __IBDA_ConditionalAccessEx_INTERFACE_DEFINED__
define __IBDA_ConditionalAccessEx_INTERFACE_DEFINED__

DEFINE_IIDX(IBDA_ConditionalAccessEx, "497C3418-23CB-44ba-BB62-769F506FCEA7")

.comdef IBDA_ConditionalAccessEx : public IUnknown

    CheckEntitlementToken proc :ULONG, :BSTR, :BDA_CONDITIONALACCESS_REQUESTTYPE, :LONG, :ptr BYTE, :ptr ULONG
    SetCaptureToken	proc :ULONG, :ptr BYTE
    OpenBroadcastMmi	proc :ULONG, :BSTR, :ULONG
    CloseMmiDialog	proc :ULONG, :BSTR, :ULONG, :BDA_CONDITIONALACCESS_MMICLOSEREASON, :ptr ULONG
    CreateDialogRequestNumber proc :ptr ULONG
   .ends

endif

ifndef __IBDA_ISDBConditionalAccess_INTERFACE_DEFINED__
define __IBDA_ISDBConditionalAccess_INTERFACE_DEFINED__

DEFINE_IIDX(IBDA_ISDBConditionalAccess, "5E68C627-16C2-4e6c-B1E2-D00170CDAA0F")

.comdef IBDA_ISDBConditionalAccess : public IUnknown

    SetIsdbCasRequest	proc :ULONG, :ULONG, :ptr BYTE
   .ends

endif

ifndef __IBDA_EventingService_INTERFACE_DEFINED__
define __IBDA_EventingService_INTERFACE_DEFINED__

DEFINE_IIDX(IBDA_EventingService, "207C413F-00DC-4c61-BAD6-6FEE1FF07064")

.comdef IBDA_EventingService : public IUnknown

    CompleteEvent	proc :ULONG, :ULONG
   .ends

endif

ifndef __IBDA_AUX_INTERFACE_DEFINED__
define __IBDA_AUX_INTERFACE_DEFINED__

DEFINE_IIDX(IBDA_AUX, "7DEf4C09-6E66-4567-A819-F0E17F4A81AB")

.comdef IBDA_AUX : public IUnknown

    QueryCapabilities	proc :ptr DWORD
    EnumCapability	proc :DWORD, :ptr DWORD, :ptr GUID, :ptr DWORD, :ptr DWORD, :ptr ULONGLONG
   .ends

endif

DEFINE_GUID(PBDA_AUX_CONNECTOR_TYPE_SVideo, 0xa0e905f4,0x24c9,0x4a54, 0xb7, 0x61, 0x21, 0x33, 0x55, 0xef, 0xc1, 0x3A)
DEFINE_GUID(PBDA_AUX_CONNECTOR_TYPE_Composite, 0xf6298b4c,0xc725,0x4d42, 0x84, 0x9b, 0x41, 0x0b, 0xbb, 0x14, 0xea, 0x62)
DEFINE_GUID(CLSID_PBDA_AUX_DATA_TYPE, 0xfd456373, 0x3323, 0x4090, 0xad, 0xca, 0x8e, 0xd4, 0x5f, 0x55, 0xcf, 0x10)

ifndef __IBDA_Encoder_INTERFACE_DEFINED__
define __IBDA_Encoder_INTERFACE_DEFINED__

DEFINE_IIDX(IBDA_Encoder, "3a8bad59-59fe-4559-a0ba-396cfaa98ae3")

.comdef IBDA_Encoder : public IUnknown

    QueryCapabilities	proc :ptr DWORD, :ptr DWORD
    EnumAudioCapability proc :DWORD, :ptr DWORD, :ptr DWORD, :ptr DWORD, :ptr DWORD, :ptr DWORD
    EnumVideoCapability proc :DWORD, :ptr DWORD, :ptr DWORD, :ptr DWORD, :ptr DWORD, :ptr DWORD, :ptr DWORD, :ptr DWORD
    SetParameters	proc :DWORD, :DWORD, :DWORD, :DWORD, :DWORD, :DWORD, :DWORD
    GetState		proc :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr ULONGLONG, :ptr BOOL, :ptr LONG, :ptr DWORD
   .ends

endif

DEFINE_GUID(CLSID_PBDA_Encoder_DATA_TYPE, 0x728fd6bc, 0x5546, 0x4716, 0xb1, 0x03, 0xf8, 0x99, 0xf5, 0xa1, 0xfa, 0x68)
PBDA_Encoder_Audio_AlgorithmType_MPEG1LayerII equ 0x00000000
PBDA_Encoder_Audio_AlgorithmType_AC3 equ 0x00000001
PBDA_Encoder_Video_MPEG2PartII equ 0x00000000
PBDA_Encoder_Video_MPEG4Part10 equ 0x00000001
PBDA_Encoder_Video_AVC	equ 0x00000001
PBDA_Encoder_Video_H264 equ 0x00000001
PBDA_Encoder_BitrateMode_Constant equ 0x00000001
PBDA_Encoder_BitrateMode_Variable equ 0x00000002
PBDA_Encoder_BitrateMode_Average equ 0x00000003

ifndef __IBDA_FDC_INTERFACE_DEFINED__
define __IBDA_FDC_INTERFACE_DEFINED__

DEFINE_GUID(CLSID_PBDA_FDC_DATA_TYPE, 0xe7dbf9a0, 0x22ab, 0x4047, 0x8e, 0x67, 0xef, 0x9a, 0xd5, 0x4, 0xe7, 0x29)

DEFINE_IIDX(IBDA_FDC, "138adc7e-58ae-437f-b0b4-c9fe19d5b4ac")

.comdef IBDA_FDC : public IUnknown

    GetStatus		proc :ptr DWORD, :ptr BOOL, :ptr DWORD, :ptr BOOL, :ptr BSTR, :ptr BSTR, :ptr BOOL
    RequestTables	proc :BSTR
    AddPid		proc :BSTR, :ptr DWORD
    RemovePid		proc :BSTR
    AddTid		proc :BSTR, :ptr BSTR
    RemoveTid		proc :BSTR
    GetTableSection	proc :ptr DWORD, :DWORD, :ptr DWORD, :ptr BYTE
   .ends

endif

ifndef __IBDA_GuideDataDeliveryService_INTERFACE_DEFINED__
define __IBDA_GuideDataDeliveryService_INTERFACE_DEFINED__

DEFINE_IIDX(IBDA_GuideDataDeliveryService, "C0AFCB73-23E7-4bc6-BAFA-FDC167B4719F")

.comdef IBDA_GuideDataDeliveryService : public IUnknown

    GetGuideDataType	proc :ptr GUID
    GetGuideData	proc :ptr ULONG, :ptr BYTE, :ptr ULONG
    RequestGuideDataUpdate proc
    GetTuneXmlFromServiceIdx proc :ULONG64, :ptr BSTR
    GetServices		proc :ptr ULONG, :ptr BYTE
    GetServiceInfoFromTuneXml proc :BSTR, :ptr BSTR
   .ends

endif

DEFINE_GUID(CLSID_PBDA_GDDS_DATA_TYPE, 0xC80C0DF3, 0x6052, 0x4c16, 0x9F, 0x56, 0xC4, 0x4C, 0x21, 0xF7, 0x3C, 0x45)

ifndef __IBDA_DRMService_INTERFACE_DEFINED__
define __IBDA_DRMService_INTERFACE_DEFINED__

DEFINE_IIDX(IBDA_DRMService, "BFF6B5BB-B0AE-484c-9DCA-73528FB0B46E")

.comdef IBDA_DRMService : public IUnknown

    SetDRM		proc :ptr GUID
    GetDRMStatus	proc :ptr BSTR, :ptr GUID
   .ends

endif

ifndef __IBDA_WMDRMSession_INTERFACE_DEFINED__
define __IBDA_WMDRMSession_INTERFACE_DEFINED__

DEFINE_IIDX(IBDA_WMDRMSession, "4BE6FA3D-07CD-4139-8B80-8C18BA3AEC88")

.comdef IBDA_WMDRMSession : public IUnknown

    GetStatus		proc :ptr ULONG, :ptr ULONG, :ptr ULONG, :ptr ULONG, :ptr ULONG, :ptr ULONGLONG, :ptr ULONG, :ptr ULONG, :ptr ULONG
    SetRevInfo		proc :ULONG, :ptr BYTE
    SetCrl		proc :ULONG, :ptr BYTE
    TransactMessage	proc :ULONG, :ptr BYTE, :ptr ULONG, :ptr BYTE
    GetLicense		proc :ptr GUID, :ptr ULONG, :ptr BYTE
    ReissueLicense	proc :ptr GUID
    RenewLicense	proc :ULONG, :ptr BYTE, :ULONG, :ptr BYTE, :ptr ULONG, :ptr ULONG, :ptr BYTE
    GetKeyInfo		proc :ptr ULONG, :ptr BYTE
   .ends

endif

ifndef __IBDA_WMDRMTuner_INTERFACE_DEFINED__
define __IBDA_WMDRMTuner_INTERFACE_DEFINED__

DEFINE_IIDX(IBDA_WMDRMTuner, "86D979CF-A8A7-4f94-B5FB-14C0ACA68FE6")

.comdef IBDA_WMDRMTuner : public IUnknown

    PurchaseEntitlement proc :ULONG, :BSTR, :ULONG, :ptr BYTE, :ptr ULONG, :ptr ULONG, :ptr BYTE
    CancelCaptureToken	proc :ULONG, :ptr BYTE
    SetPidProtection	proc :ULONG, :ptr GUID
    GetPidProtection	proc :ULONG, :ptr GUID
    SetSyncValue	proc :ULONG
    GetStartCodeProfile proc :ptr ULONG, :ptr BYTE
   .ends

endif

ifndef __IBDA_DRIDRMService_INTERFACE_DEFINED__
define __IBDA_DRIDRMService_INTERFACE_DEFINED__

DEFINE_IIDX(IBDA_DRIDRMService, "1F9BC2A5-44A3-4c52-AAB1-0BBCE5A1381D")

.comdef IBDA_DRIDRMService : public IUnknown

    SetDRM		proc :BSTR
    GetDRMStatus	proc :ptr BSTR, :ptr GUID
    GetPairingStatus	proc :ptr BDA_DrmPairingError
   .ends

endif

ifndef __IBDA_DRIWMDRMSession_INTERFACE_DEFINED__
define __IBDA_DRIWMDRMSession_INTERFACE_DEFINED__

DEFINE_IIDX(IBDA_DRIWMDRMSession, "05C690F8-56DB-4bb2-B053-79C12098BB26")

.comdef IBDA_DRIWMDRMSession : public IUnknown

    AcknowledgeLicense	proc :HRESULT
    ProcessLicenseChallenge proc :DWORD, :ptr BYTE, :ptr DWORD, :ptr ptr BYTE
    ProcessRegistrationChallenge proc :DWORD, :ptr BYTE, :ptr DWORD, :ptr ptr BYTE
    SetRevInfo		proc :DWORD, :ptr BYTE, :ptr DWORD
    SetCrl		proc :DWORD, :ptr BYTE, :ptr DWORD
    GetHMSAssociationData proc
    GetLastCardeaError	proc :ptr DWORD
   .ends

endif

ifndef __IBDA_MUX_INTERFACE_DEFINED__
define __IBDA_MUX_INTERFACE_DEFINED__

DEFINE_IIDX(IBDA_MUX, "942AAFEC-4C05-4c74-B8EB-8706C2A4943F")

.comdef IBDA_MUX : public IUnknown

    SetPidList		proc :ULONG, :ptr BDA_MUX_PIDLISTITEM
    GetPidList		proc :ptr ULONG, :ptr BDA_MUX_PIDLISTITEM
   .ends

endif

ifndef __IBDA_TransportStreamSelector_INTERFACE_DEFINED__
define __IBDA_TransportStreamSelector_INTERFACE_DEFINED__

DEFINE_IIDX(IBDA_TransportStreamSelector, "1DCFAFE9-B45E-41b3-BB2A-561EB129AE98")

.comdef IBDA_TransportStreamSelector : public IUnknown

    SetTSID		proc :USHORT
    GetTSInformation	proc :ptr ULONG, :ptr BYTE
   .ends

endif

ifndef __IBDA_UserActivityService_INTERFACE_DEFINED__
define __IBDA_UserActivityService_INTERFACE_DEFINED__

DEFINE_IIDX(IBDA_UserActivityService, "53B14189-E478-4b7a-A1FF-506DB4B99DFE")

.comdef IBDA_UserActivityService : public IUnknown

    SetCurrentTunerUseReason proc :DWORD
    GetUserActivityInterval proc :ptr DWORD
    UserActivityDetected proc
   .ends

endif

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

;DWORD
BSTR_UserSize proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr BSTR

;LPBYTE
BSTR_UserMarshal proto WINAPI \
		      : ptr DWORD,
		      : ptr sbyte,
		      : ptr BSTR

;LPBYTE
BSTR_UserUnmarshal proto WINAPI \
		      : ptr DWORD,
		      : ptr sbyte,
		      : ptr BSTR

;void
BSTR_UserFree proto WINAPI \
		      : ptr DWORD,
		      : ptr BSTR


;DWORD
BSTR_UserSize64 proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr BSTR

;LPBYTE
BSTR_UserMarshal64 proto WINAPI \
		      : ptr DWORD,
		      : ptr sbyte,
		      : ptr BSTR

;LPBYTE
BSTR_UserUnmarshal64 proto WINAPI \
		      : ptr DWORD,
		      : ptr sbyte,
		      : ptr BSTR

;void
BSTR_UserFree64 proto WINAPI \
		      : ptr DWORD,
		      : ptr BSTR

endif
