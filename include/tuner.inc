ifndef _RPCNDR500_
include rpcndr500.inc
endif

ifndef __tuner_h__
define __tuner_h__

ifndef __oaidl_h__
include oaidl.inc
endif
ifndef __ocidl_h__
include ocidl.inc
endif
include strmif.inc
include bdaiface.inc
include regbag.inc
ifndef _WINAPIFAMILY_
include winapifamily.inc
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

.enum _MIDL___MIDL_itf_tuner_0000_0000_0001 {
    DISPID_TUNER_TS_UNIQUENAME	= 1,
    DISPID_TUNER_TS_FRIENDLYNAME	= 2,
    DISPID_TUNER_TS_CLSID	= 3,
    DISPID_TUNER_TS_NETWORKTYPE = 4,
    DISPID_TUNER_TS__NETWORKTYPE	= 5,
    DISPID_TUNER_TS_CREATETUNEREQUEST	= 6,
    DISPID_TUNER_TS_ENUMCATEGORYGUIDS	= 7,
    DISPID_TUNER_TS_ENUMDEVICEMONIKERS	= 8,
    DISPID_TUNER_TS_DEFAULTPREFERREDCOMPONENTTYPES	= 9,
    DISPID_TUNER_TS_FREQMAP	= 10,
    DISPID_TUNER_TS_DEFLOCATOR	= 11,
    DISPID_TUNER_TS_CLONE	= 12,
    DISPID_TUNER_TR_TUNINGSPACE = 1,
    DISPID_TUNER_TR_COMPONENTS	= 2,
    DISPID_TUNER_TR_CLONE	= 3,
    DISPID_TUNER_TR_LOCATOR	= 4,
    DISPID_TUNER_CT_CATEGORY	= 1,
    DISPID_TUNER_CT_MEDIAMAJORTYPE	= 2,
    DISPID_TUNER_CT__MEDIAMAJORTYPE	= 3,
    DISPID_TUNER_CT_MEDIASUBTYPE	= 4,
    DISPID_TUNER_CT__MEDIASUBTYPE	= 5,
    DISPID_TUNER_CT_MEDIAFORMATTYPE	= 6,
    DISPID_TUNER_CT__MEDIAFORMATTYPE	= 7,
    DISPID_TUNER_CT_MEDIATYPE	= 8,
    DISPID_TUNER_CT_CLONE	= 9,
    DISPID_TUNER_LCT_LANGID	= 100,
    DISPID_TUNER_MP2CT_TYPE	= 200,
    DISPID_TUNER_ATSCCT_FLAGS	= 300,
    DISPID_TUNER_L_CARRFREQ	= 1,
    DISPID_TUNER_L_INNERFECMETHOD	= 2,
    DISPID_TUNER_L_INNERFECRATE = 3,
    DISPID_TUNER_L_OUTERFECMETHOD	= 4,
    DISPID_TUNER_L_OUTERFECRATE = 5,
    DISPID_TUNER_L_MOD	= 6,
    DISPID_TUNER_L_SYMRATE	= 7,
    DISPID_TUNER_L_CLONE	= 8,
    DISPID_TUNER_L_ATSC_PHYS_CHANNEL	= 201,
    DISPID_TUNER_L_ATSC_TSID	= 202,
    DISPID_TUNER_L_ATSC_MP2_PROGNO	= 203,
    DISPID_TUNER_L_DVBT_BANDWIDTH	= 301,
    DISPID_TUNER_L_DVBT_LPINNERFECMETHOD	= 302,
    DISPID_TUNER_L_DVBT_LPINNERFECRATE	= 303,
    DISPID_TUNER_L_DVBT_GUARDINTERVAL	= 304,
    DISPID_TUNER_L_DVBT_HALPHA	= 305,
    DISPID_TUNER_L_DVBT_TRANSMISSIONMODE	= 306,
    DISPID_TUNER_L_DVBT_INUSE	= 307,
    DISPID_TUNER_L_DVBT2_PHYSICALLAYERPIPEID	= 351,
    DISPID_TUNER_L_DVBS_POLARISATION	= 401,
    DISPID_TUNER_L_DVBS_WEST	= 402,
    DISPID_TUNER_L_DVBS_ORBITAL = 403,
    DISPID_TUNER_L_DVBS_AZIMUTH = 404,
    DISPID_TUNER_L_DVBS_ELEVATION	= 405,
    DISPID_TUNER_L_DVBS2_DISEQ_LNB_SOURCE	= 406,
    DISPID_TUNER_TS_DVBS2_LOW_OSC_FREQ_OVERRIDE = 407,
    DISPID_TUNER_TS_DVBS2_HI_OSC_FREQ_OVERRIDE	= 408,
    DISPID_TUNER_TS_DVBS2_LNB_SWITCH_FREQ_OVERRIDE	= 409,
    DISPID_TUNER_TS_DVBS2_SPECTRAL_INVERSION_OVERRIDE	= 410,
    DISPID_TUNER_L_DVBS2_ROLLOFF	= 411,
    DISPID_TUNER_L_DVBS2_PILOT	= 412,
    DISPID_TUNER_L_ANALOG_STANDARD	= 601,
    DISPID_TUNER_L_DTV_O_MAJOR_CHANNEL	= 701,
    DISPID_TUNER_C_TYPE = 1,
    DISPID_TUNER_C_STATUS	= 2,
    DISPID_TUNER_C_LANGID	= 3,
    DISPID_TUNER_C_DESCRIPTION	= 4,
    DISPID_TUNER_C_CLONE	= 5,
    DISPID_TUNER_C_MP2_PID	= 101,
    DISPID_TUNER_C_MP2_PCRPID	= 102,
    DISPID_TUNER_C_MP2_PROGNO	= 103,
    DISPID_TUNER_C_ANALOG_AUDIO = 201,
    DISPID_TUNER_TS_DVB_SYSTEMTYPE	= 101,
    DISPID_TUNER_TS_DVB2_NETWORK_ID	= 102,
    DISPID_TUNER_TS_DVBS_LOW_OSC_FREQ	= 1001,
    DISPID_TUNER_TS_DVBS_HI_OSC_FREQ	= 1002,
    DISPID_TUNER_TS_DVBS_LNB_SWITCH_FREQ	= 1003,
    DISPID_TUNER_TS_DVBS_INPUT_RANGE	= 1004,
    DISPID_TUNER_TS_DVBS_SPECTRAL_INVERSION	= 1005,
    DISPID_TUNER_TS_AR_MINFREQUENCY	= 101,
    DISPID_TUNER_TS_AR_MAXFREQUENCY	= 102,
    DISPID_TUNER_TS_AR_STEP	= 103,
    DISPID_TUNER_TS_AR_COUNTRYCODE	= 104,
    DISPID_TUNER_TS_AUX_COUNTRYCODE	= 101,
    DISPID_TUNER_TS_ATV_MINCHANNEL	= 101,
    DISPID_TUNER_TS_ATV_MAXCHANNEL	= 102,
    DISPID_TUNER_TS_ATV_INPUTTYPE	= 103,
    DISPID_TUNER_TS_ATV_COUNTRYCODE	= 104,
    DISPID_TUNER_TS_ATSC_MINMINORCHANNEL	= 201,
    DISPID_TUNER_TS_ATSC_MAXMINORCHANNEL	= 202,
    DISPID_TUNER_TS_ATSC_MINPHYSCHANNEL = 203,
    DISPID_TUNER_TS_ATSC_MAXPHYSCHANNEL = 204,
    DISPID_TUNER_TS_DC_MINMAJORCHANNEL	= 301,
    DISPID_TUNER_TS_DC_MAXMAJORCHANNEL	= 302,
    DISPID_TUNER_TS_DC_MINSOURCEID	= 303,
    DISPID_TUNER_TS_DC_MAXSOURCEID	= 304,
    DISPID_CHTUNER_ATVAC_CHANNEL	= 101,
    DISPID_CHTUNER_ATVDC_SYSTEM = 101,
    DISPID_CHTUNER_ATVDC_CONTENT	= 102,
    DISPID_CHTUNER_CIDTR_CHANNELID	= 101,
    DISPID_CHTUNER_CTR_CHANNEL	= 101,
    DISPID_CHTUNER_ACTR_MINOR_CHANNEL	= 201,
    DISPID_CHTUNER_DCTR_MAJOR_CHANNEL	= 301,
    DISPID_CHTUNER_DCTR_SRCID	= 302,
    DISPID_DVBTUNER_DVBC_ATTRIBUTESVALID	= 101,
    DISPID_DVBTUNER_DVBC_PID	= 102,
    DISPID_DVBTUNER_DVBC_TAG	= 103,
    DISPID_DVBTUNER_DVBC_COMPONENTTYPE	= 104,
    DISPID_DVBTUNER_ONID	= 101,
    DISPID_DVBTUNER_TSID	= 102,
    DISPID_DVBTUNER_SID = 103,
    DISPID_MP2TUNER_TSID	= 101,
    DISPID_MP2TUNER_PROGNO	= 102,
    DISPID_MP2TUNERFACTORY_CREATETUNEREQUEST	= 1
    }


ifndef __ITuningSpaces_INTERFACE_DEFINED__
define __ITuningSpaces_INTERFACE_DEFINED__

DEFINE_IIDX(ITuningSpaces, "901284E4-33FE-4b69-8D63-634A596F3756")

.comdef ITuningSpaces : public IDispatch

    get_Count		proc :ptr
    get__NewEnum	proc :ptr
    get_Item		proc :VARIANT, :ptr
    get_EnumTuningSpaces proc :ptr
   .ends

endif


ifndef __ITuningSpaceContainer_INTERFACE_DEFINED__
define __ITuningSpaceContainer_INTERFACE_DEFINED__

DEFINE_IIDX(ITuningSpaceContainer, "5B692E84-E2F1-11d2-9493-00C04F72D980")

.comdef ITuningSpaceContainer : public IDispatch

    get_Count		proc :ptr
    get__NewEnum	proc :ptr
    get_Item		proc :VARIANT, :ptr
    put_Item		proc :VARIANT, :ptr
    TuningSpacesForCLSID proc :BSTR, :ptr
    _TuningSpacesForCLSID proc :REFCLSID, :ptr
    TuningSpacesForName proc :BSTR, :ptr
    FindID		proc :ptr, :ptr
    _Add		proc :ptr, :ptr
    get_EnumTuningSpaces proc :ptr
    Remove		proc :VARIANT
    get_MaxCount	proc :ptr
    put_MaxCount	proc :int_t
   .ends

endif


ifndef __ITuningSpace_INTERFACE_DEFINED__
define __ITuningSpace_INTERFACE_DEFINED__

DEFINE_IIDX(ITuningSpace, "061C6E30-E622-11d2-9493-00C04F72D980")

.comdef ITuningSpace : public IDispatch

    get_UniqueName	proc :ptr
    put_UniqueName	proc :BSTR
    get_FriendlyName	proc :ptr
    put_FriendlyName	proc :BSTR
    get_CLSID		proc :ptr
    get_NetworkType	proc :ptr
    put_NetworkType	proc :BSTR
    get__NetworkType	proc :ptr
    put__NetworkType	proc :REFCLSID
    CreateTuneRequest	proc :ptr
    EnumCategoryGUIDs	proc :ptr
    EnumDeviceMonikers	proc :ptr
    get_DefaultPreferredComponentTypes proc :ptr
    put_DefaultPreferredComponentTypes proc :ptr
    get_FrequencyMapping proc :ptr
    put_FrequencyMapping proc :BSTR
    get_DefaultLocator	proc :ptr
    put_DefaultLocator	proc :ptr
    Clone		proc :ptr
   .ends

endif

ifndef __IEnumTuningSpaces_INTERFACE_DEFINED__
define __IEnumTuningSpaces_INTERFACE_DEFINED__

DEFINE_IIDX(IEnumTuningSpaces, "8B8EB248-FC2B-11d2-9D8C-00C04F72D980")

.comdef IEnumTuningSpaces : public IUnknown

    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
   .ends

endif

ifndef __IDVBTuningSpace_INTERFACE_DEFINED__
define __IDVBTuningSpace_INTERFACE_DEFINED__

DEFINE_IIDX(IDVBTuningSpace, "ADA0B268-3B19-4e5b-ACC4-49F852BE13BA")

.comdef IDVBTuningSpace : public ITuningSpace

    get_SystemType	proc :ptr
    put_SystemType	proc :DVBSystemType
   .ends

endif

ifndef __IDVBTuningSpace2_INTERFACE_DEFINED__
define __IDVBTuningSpace2_INTERFACE_DEFINED__

DEFINE_IIDX(IDVBTuningSpace2, "843188B4-CE62-43db-966B-8145A094E040")

.comdef IDVBTuningSpace2 : public IDVBTuningSpace

    get_NetworkID	proc :ptr
    put_NetworkID	proc :LONG
   .ends

endif

ifndef __IDVBSTuningSpace_INTERFACE_DEFINED__
define __IDVBSTuningSpace_INTERFACE_DEFINED__

DEFINE_IIDX(IDVBSTuningSpace, "CDF7BE60-D954-42fd-A972-78971958E470")

.comdef IDVBSTuningSpace : public IDVBTuningSpace2

    get_LowOscillator	proc :ptr
    put_LowOscillator	proc :LONG
    get_HighOscillator	proc :ptr
    put_HighOscillator	proc :LONG
    get_LNBSwitch	proc :ptr
    put_LNBSwitch	proc :LONG
    get_InputRange	proc :ptr
    put_InputRange	proc :BSTR
    get_SpectralInversion proc :ptr
    put_SpectralInversion proc :SpectralInversion
   .ends

endif

ifndef __IAuxInTuningSpace_INTERFACE_DEFINED__
define __IAuxInTuningSpace_INTERFACE_DEFINED__

DEFINE_IIDX(IAuxInTuningSpace, "E48244B8-7E17-4f76-A763-5090FF1E2F30")

.comdef IAuxInTuningSpace : public ITuningSpace

   .ends

endif

ifndef __IAuxInTuningSpace2_INTERFACE_DEFINED__
define __IAuxInTuningSpace2_INTERFACE_DEFINED__

DEFINE_IIDX(IAuxInTuningSpace2, "B10931ED-8BFE-4AB0-9DCE-E469C29A9729")

.comdef IAuxInTuningSpace2 : public IAuxInTuningSpace

    get_CountryCode	proc :ptr
    put_CountryCode	proc :LONG
   .ends

endif

ifndef __IAnalogTVTuningSpace_INTERFACE_DEFINED__
define __IAnalogTVTuningSpace_INTERFACE_DEFINED__

DEFINE_IIDX(IAnalogTVTuningSpace, "2A6E293C-2595-11d3-B64C-00C04F79498E")

.comdef IAnalogTVTuningSpace : public ITuningSpace

    get_MinChannel	proc :ptr
    put_MinChannel	proc :LONG
    get_MaxChannel	proc :ptr
    put_MaxChannel	proc :LONG
    get_InputType	proc :ptr
    put_InputType	proc :TunerInputType
    get_CountryCode	proc :ptr
    put_CountryCode	proc :LONG
   .ends

endif

ifndef __IATSCTuningSpace_INTERFACE_DEFINED__
define __IATSCTuningSpace_INTERFACE_DEFINED__

DEFINE_IIDX(IATSCTuningSpace, "0369B4E2-45B6-11d3-B650-00C04F79498E")

.comdef IATSCTuningSpace : public IAnalogTVTuningSpace

    get_MinMinorChannel proc :ptr
    put_MinMinorChannel proc :LONG
    get_MaxMinorChannel proc :ptr
    put_MaxMinorChannel proc :LONG
    get_MinPhysicalChannel proc :ptr
    put_MinPhysicalChannel proc :LONG
    get_MaxPhysicalChannel proc :ptr
    put_MaxPhysicalChannel proc :LONG
   .ends

endif

ifndef __IDigitalCableTuningSpace_INTERFACE_DEFINED__
define __IDigitalCableTuningSpace_INTERFACE_DEFINED__

DEFINE_IIDX(IDigitalCableTuningSpace, "013F9F9C-B449-4ec7-A6D2-9D4F2FC70AE5")

.comdef IDigitalCableTuningSpace : public IATSCTuningSpace

    get_MinMajorChannel proc :ptr
    put_MinMajorChannel proc :LONG
    get_MaxMajorChannel proc :ptr
    put_MaxMajorChannel proc :LONG
    get_MinSourceID	proc :ptr
    put_MinSourceID	proc :LONG
    get_MaxSourceID	proc :ptr
    put_MaxSourceID	proc :LONG
   .ends

endif

ifndef __IAnalogRadioTuningSpace_INTERFACE_DEFINED__
define __IAnalogRadioTuningSpace_INTERFACE_DEFINED__

DEFINE_IIDX(IAnalogRadioTuningSpace, "2A6E293B-2595-11d3-B64C-00C04F79498E")

.comdef IAnalogRadioTuningSpace : public ITuningSpace

    get_MinFrequency	proc :ptr
    put_MinFrequency	proc :LONG
    get_MaxFrequency	proc :ptr
    put_MaxFrequency	proc :LONG
    get_Step		proc :ptr
    put_Step		proc :LONG
   .ends

endif

ifndef __IAnalogRadioTuningSpace2_INTERFACE_DEFINED__
define __IAnalogRadioTuningSpace2_INTERFACE_DEFINED__

DEFINE_IIDX(IAnalogRadioTuningSpace2, "39DD45DA-2DA8-46BA-8A8A-87E2B73D983A")

.comdef IAnalogRadioTuningSpace2 : public IAnalogRadioTuningSpace

    get_CountryCode	proc :ptr
    put_CountryCode	proc :LONG
   .ends

endif

ifndef __ITuneRequest_INTERFACE_DEFINED__
define __ITuneRequest_INTERFACE_DEFINED__

DEFINE_IIDX(ITuneRequest, "07DDC146-FC3D-11d2-9D8C-00C04F72D980")

.comdef ITuneRequest : public IDispatch

    get_TuningSpace	proc :ptr
    get_Components	proc :ptr
    Clone		proc :ptr
    get_Locator		proc :ptr
    put_Locator		proc :ptr
   .ends

endif

ifndef __IChannelIDTuneRequest_INTERFACE_DEFINED__
define __IChannelIDTuneRequest_INTERFACE_DEFINED__

DEFINE_IIDX(IChannelIDTuneRequest, "156EFF60-86F4-4e28-89FC-109799FD57EE")

.comdef IChannelIDTuneRequest : public ITuneRequest

    get_ChannelID	proc :ptr
    put_ChannelID	proc :BSTR
   .ends

endif

ifndef __IChannelTuneRequest_INTERFACE_DEFINED__
define __IChannelTuneRequest_INTERFACE_DEFINED__

DEFINE_IIDX(IChannelTuneRequest, "0369B4E0-45B6-11d3-B650-00C04F79498E")

.comdef IChannelTuneRequest : public ITuneRequest

    get_Channel		proc :ptr
    put_Channel		proc :LONG
   .ends

endif

ifndef __IATSCChannelTuneRequest_INTERFACE_DEFINED__
define __IATSCChannelTuneRequest_INTERFACE_DEFINED__

DEFINE_IIDX(IATSCChannelTuneRequest, "0369B4E1-45B6-11d3-B650-00C04F79498E")

.comdef IATSCChannelTuneRequest : public IChannelTuneRequest

    get_MinorChannel	proc :ptr
    put_MinorChannel	proc :LONG
   .ends

endif

ifndef __IDigitalCableTuneRequest_INTERFACE_DEFINED__
define __IDigitalCableTuneRequest_INTERFACE_DEFINED__

DEFINE_IIDX(IDigitalCableTuneRequest, "BAD7753B-6B37-4810-AE57-3CE0C4A9E6CB")

.comdef IDigitalCableTuneRequest : public IATSCChannelTuneRequest

    get_MajorChannel	proc :ptr
    put_MajorChannel	proc :LONG
    get_SourceID	proc :ptr
    put_SourceID	proc :LONG
   .ends

endif

ifndef __IDVBTuneRequest_INTERFACE_DEFINED__
define __IDVBTuneRequest_INTERFACE_DEFINED__

DEFINE_IIDX(IDVBTuneRequest, "0D6F567E-A636-42bb-83BA-CE4C1704AFA2")

.comdef IDVBTuneRequest : public ITuneRequest

    get_ONID		proc :ptr
    put_ONID		proc :LONG
    get_TSID		proc :ptr
    put_TSID		proc :LONG
    get_SID		proc :ptr
    put_SID		proc :LONG
   .ends

endif

ifndef __IMPEG2TuneRequest_INTERFACE_DEFINED__
define __IMPEG2TuneRequest_INTERFACE_DEFINED__

DEFINE_IIDX(IMPEG2TuneRequest, "EB7D987F-8A01-42ad-B8AE-574DEEE44D1A")

.comdef IMPEG2TuneRequest : public ITuneRequest

    get_TSID		proc :ptr
    put_TSID		proc :LONG
    get_ProgNo		proc :ptr
    put_ProgNo		proc :LONG
   .ends

endif

ifndef __IMPEG2TuneRequestFactory_INTERFACE_DEFINED__
define __IMPEG2TuneRequestFactory_INTERFACE_DEFINED__

DEFINE_IIDX(IMPEG2TuneRequestFactory, "14E11ABD-EE37-4893-9EA1-6964DE933E39")

.comdef IMPEG2TuneRequestFactory : public IDispatch

    CreateTuneRequest	proc :ptr, :ptr
   .ends

endif

ifndef __IMPEG2TuneRequestSupport_INTERFACE_DEFINED__
define __IMPEG2TuneRequestSupport_INTERFACE_DEFINED__

DEFINE_IIDX(IMPEG2TuneRequestSupport, "1B9D5FC3-5BBC-4b6c-BB18-B9D10E3EEEBF")

.comdef IMPEG2TuneRequestSupport : public IUnknown
   .ends

endif

ifndef __ITunerCap_INTERFACE_DEFINED__
define __ITunerCap_INTERFACE_DEFINED__

DEFINE_IIDX(ITunerCap, "E60DFA45-8D56-4e65-A8AB-D6BE9412C249")

.comdef ITunerCap : public IUnknown

    get_SupportedNetworkTypes proc :ULONG, :ptr, :ptr
    get_SupportedVideoFormats proc :ptr, :ptr
    get_AuxInputCount	proc :ptr, :ptr
   .ends

endif

ifndef __ITunerCapEx_INTERFACE_DEFINED__
define __ITunerCapEx_INTERFACE_DEFINED__

DEFINE_IIDX(ITunerCapEx, "ed3e0c66-18c8-4ea6-9300-f6841fdd35dc")

.comdef ITunerCapEx : public IUnknown

    get_Has608_708Caption proc :ptr
   .ends

endif

ifndef __ITuner_INTERFACE_DEFINED__
define __ITuner_INTERFACE_DEFINED__

DEFINE_IIDX(ITuner, "28C52640-018A-11d3-9D8E-00C04F72D980")

.comdef ITuner : public IUnknown

    get_TuningSpace	proc :ptr
    put_TuningSpace	proc :ptr
    EnumTuningSpaces	proc :ptr
    get_TuneRequest	proc :ptr
    put_TuneRequest	proc :ptr
    Validate		proc :ptr
    get_PreferredComponentTypes proc :ptr
    put_PreferredComponentTypes proc :ptr
    get_SignalStrength	proc :ptr
    TriggerSignalEvents proc :LONG
   .ends

endif

ifndef __IScanningTuner_INTERFACE_DEFINED__
define __IScanningTuner_INTERFACE_DEFINED__

DEFINE_IIDX(IScanningTuner, "1DFD0A5C-0284-11d3-9D8E-00C04F72D980")

.comdef IScanningTuner : public ITuner

    SeekUp		proc
    SeekDown		proc
    ScanUp		proc :LONG
    ScanDown		proc :LONG
    AutoProgram		proc
   .ends

endif

ifndef __IScanningTunerEx_INTERFACE_DEFINED__
define __IScanningTunerEx_INTERFACE_DEFINED__

DEFINE_IIDX(IScanningTunerEx, "04BBD195-0E2D-4593-9BD5-4F908BC33CF5")

.comdef IScanningTunerEx : public IScanningTuner

    GetCurrentLocator	proc :ptr
    PerformExhaustiveScan proc :LONG, :LONG, :VARIANT_BOOL, :HEVENT
    TerminateCurrentScan proc :ptr
    ResumeCurrentScan	proc :HEVENT
    GetTunerScanningCapability proc :ptr, :ptr, :ptr
    GetTunerStatus	proc :ptr, :ptr, :ptr, :ptr
    GetCurrentTunerStandardCapability proc :GUID, :ptr, :ptr
    SetScanSignalTypeFilter proc :LONG, :LONG
   .ends

endif

ifndef __IComponentType_INTERFACE_DEFINED__
define __IComponentType_INTERFACE_DEFINED__

DEFINE_IIDX(IComponentType, "6A340DC0-0311-11d3-9D8E-00C04F72D980")

.comdef IComponentType : public IDispatch

    get_Category	proc :ptr
    put_Category	proc :ComponentCategory
    get_MediaMajorType	proc :ptr
    put_MediaMajorType	proc :BSTR
    get__MediaMajorType proc :ptr
    put__MediaMajorType proc :REFCLSID
    get_MediaSubType	proc :ptr
    put_MediaSubType	proc :BSTR
    get__MediaSubType	proc :ptr
    put__MediaSubType	proc :REFCLSID
    get_MediaFormatType proc :ptr
    put_MediaFormatType proc :BSTR
    get__MediaFormatType proc :ptr
    put__MediaFormatType proc :REFCLSID
    get_MediaType	proc :ptr
    put_MediaType	proc :ptr
    Clone		proc :ptr
   .ends

endif

ifndef __ILanguageComponentType_INTERFACE_DEFINED__
define __ILanguageComponentType_INTERFACE_DEFINED__

DEFINE_IIDX(ILanguageComponentType, "B874C8BA-0FA2-11d3-9D8E-00C04F72D980")

.comdef ILanguageComponentType : public IComponentType

    get_LangID		proc :ptr
    put_LangID		proc :LONG
   .ends

endif

ifndef __IMPEG2ComponentType_INTERFACE_DEFINED__
define __IMPEG2ComponentType_INTERFACE_DEFINED__

DEFINE_IIDX(IMPEG2ComponentType, "2C073D84-B51C-48c9-AA9F-68971E1F6E38")

.comdef IMPEG2ComponentType : public ILanguageComponentType

    get_StreamType	proc :ptr
    put_StreamType	proc :MPEG2StreamType
   .ends

endif

ifndef __IATSCComponentType_INTERFACE_DEFINED__
define __IATSCComponentType_INTERFACE_DEFINED__

DEFINE_IIDX(IATSCComponentType, "FC189E4D-7BD4-4125-B3B3-3A76A332CC96")

.comdef IATSCComponentType : public IMPEG2ComponentType

    get_Flags		proc :ptr
    put_Flags		proc :LONG
   .ends

endif

ifndef __IEnumComponentTypes_INTERFACE_DEFINED__
define __IEnumComponentTypes_INTERFACE_DEFINED__

DEFINE_IIDX(IEnumComponentTypes, "8A674B4A-1F63-11d3-B64C-00C04F79498E")

.comdef IEnumComponentTypes : public IUnknown

    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
   .ends

endif

ifndef __IComponentTypes_INTERFACE_DEFINED__
define __IComponentTypes_INTERFACE_DEFINED__

DEFINE_IIDX(IComponentTypes, "0DC13D4A-0313-11d3-9D8E-00C04F72D980")

.comdef IComponentTypes : public IDispatch

    get_Count		proc :ptr
    get__NewEnum	proc :ptr
    EnumComponentTypes	proc :ptr
    get_Item		proc :VARIANT, :ptr
    put_Item		proc :VARIANT, :ptr
    _Add		proc :ptr, :ptr
    Remove		proc :VARIANT
    Clone		proc :ptr
   .ends

endif

ifndef __IComponent_INTERFACE_DEFINED__
define __IComponent_INTERFACE_DEFINED__

DEFINE_IIDX(IComponent, "1A5576FC-0E19-11d3-9D8E-00C04F72D980")

.comdef IComponent : public IDispatch

    get_Type		proc :ptr
    put_Type		proc :ptr
    get_DescLangID	proc :ptr
    put_DescLangID	proc :LONG
    get_Status		proc :ptr
    put_Status		proc :ComponentStatus
    get_Description	proc :ptr
    put_Description	proc :BSTR
    Clone		proc :ptr
   .ends

endif

ifndef __IAnalogAudioComponentType_INTERFACE_DEFINED__
define __IAnalogAudioComponentType_INTERFACE_DEFINED__

DEFINE_IIDX(IAnalogAudioComponentType, "2CFEB2A8-1787-4A24-A941-C6EAEC39C842")

.comdef IAnalogAudioComponentType : public IComponentType

    get_AnalogAudioMode proc :ptr
    put_AnalogAudioMode proc :TVAudioMode
   .ends

endif

ifndef __IMPEG2Component_INTERFACE_DEFINED__
define __IMPEG2Component_INTERFACE_DEFINED__

DEFINE_IIDX(IMPEG2Component, "1493E353-1EB6-473c-802D-8E6B8EC9D2A9")

.comdef IMPEG2Component : public IComponent

    get_PID		proc :ptr
    put_PID		proc :LONG
    get_PCRPID		proc :ptr
    put_PCRPID		proc :LONG
    get_ProgramNumber	proc :ptr
    put_ProgramNumber	proc :LONG
   .ends

endif

ifndef __IEnumComponents_INTERFACE_DEFINED__
define __IEnumComponents_INTERFACE_DEFINED__

DEFINE_IIDX(IEnumComponents, "2A6E2939-2595-11d3-B64C-00C04F79498E")

.comdef IEnumComponents : public IUnknown

    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
   .ends

endif

ifndef __IComponents_INTERFACE_DEFINED__
define __IComponents_INTERFACE_DEFINED__

DEFINE_IIDX(IComponents, "39A48091-FFFE-4182-A161-3FF802640E26")

.comdef IComponents : public IDispatch

    get_Count		proc :ptr
    get__NewEnum	proc :ptr
    EnumComponents	proc :ptr
    get_Item		proc :VARIANT, :ptr
    _Add		proc :ptr, :ptr
    Remove		proc :VARIANT
    Clone		proc :ptr
    put_Item		proc :VARIANT, :ptr
   .ends

endif

ifndef __IComponentsOld_INTERFACE_DEFINED__
define __IComponentsOld_INTERFACE_DEFINED__

DEFINE_IIDX(IComponentsOld, "FCD01846-0E19-11d3-9D8E-00C04F72D980")

.comdef IComponentsOld : public IDispatch

    get_Count		proc :ptr
    get__NewEnum	proc :ptr
    EnumComponents	proc :ptr
    get_Item		proc :VARIANT, :ptr
    _Add		proc :ptr, :ptr
    Remove		proc :VARIANT
    Clone		proc :ptr
   .ends

endif

ifndef __ILocator_INTERFACE_DEFINED__
define __ILocator_INTERFACE_DEFINED__

DEFINE_IIDX(ILocator, "286D7F89-760C-4F89-80C4-66841D2507AA")

.comdef ILocator : public IDispatch

    get_CarrierFrequency proc :ptr
    put_CarrierFrequency proc :LONG
    get_InnerFEC	proc :ptr
    put_InnerFEC	proc :FECMethod
    get_InnerFECRate	proc :ptr
    put_InnerFECRate	proc :BinaryConvolutionCodeRate
    get_OuterFEC	proc :ptr
    put_OuterFEC	proc :FECMethod
    get_OuterFECRate	proc :ptr
    put_OuterFECRate	proc :BinaryConvolutionCodeRate
    get_Modulation	proc :ptr
    put_Modulation	proc :ModulationType
    get_SymbolRate	proc :ptr
    put_SymbolRate	proc :LONG
    Clone		proc :ptr
   .ends

endif

ifndef __IAnalogLocator_INTERFACE_DEFINED__
define __IAnalogLocator_INTERFACE_DEFINED__

DEFINE_IIDX(IAnalogLocator, "34D1F26B-E339-430D-ABCE-738CB48984DC")

.comdef IAnalogLocator : public ILocator

    get_VideoStandard	proc :ptr
    put_VideoStandard	proc :AnalogVideoStandard
   .ends

endif

ifndef __IDigitalLocator_INTERFACE_DEFINED__
define __IDigitalLocator_INTERFACE_DEFINED__

DEFINE_IIDX(IDigitalLocator, "19B595D8-839A-47F0-96DF-4F194F3C768C")

.comdef IDigitalLocator : public ILocator
   .ends

endif

ifndef __IATSCLocator_INTERFACE_DEFINED__
define __IATSCLocator_INTERFACE_DEFINED__

DEFINE_IIDX(IATSCLocator, "BF8D986F-8C2B-4131-94D7-4D3D9FCC21EF")

.comdef IATSCLocator : public IDigitalLocator

    get_PhysicalChannel proc :ptr
    put_PhysicalChannel proc :LONG
    get_TSID		proc :ptr
    put_TSID		proc :LONG
   .ends

endif

ifndef __IATSCLocator2_INTERFACE_DEFINED__
define __IATSCLocator2_INTERFACE_DEFINED__

DEFINE_IIDX(IATSCLocator2, "612AA885-66CF-4090-BA0A-566F5312E4CA")

.comdef IATSCLocator2 : public IATSCLocator

    get_ProgramNumber	proc :ptr
    put_ProgramNumber	proc :LONG
   .ends

endif

ifndef __IDigitalCableLocator_INTERFACE_DEFINED__
define __IDigitalCableLocator_INTERFACE_DEFINED__

DEFINE_IIDX(IDigitalCableLocator, "48F66A11-171A-419A-9525-BEEECD51584C")

.comdef IDigitalCableLocator : public IATSCLocator2
   .ends

endif

ifndef __IDVBTLocator_INTERFACE_DEFINED__
define __IDVBTLocator_INTERFACE_DEFINED__

DEFINE_IIDX(IDVBTLocator, "8664DA16-DDA2-42ac-926A-C18F9127C302")

.comdef IDVBTLocator : public IDigitalLocator

    get_Bandwidth	proc :ptr
    put_Bandwidth	proc :LONG
    get_LPInnerFEC	proc :ptr
    put_LPInnerFEC	proc :FECMethod
    get_LPInnerFECRate	proc :ptr
    put_LPInnerFECRate	proc :BinaryConvolutionCodeRate
    get_HAlpha		proc :ptr
    put_HAlpha		proc :HierarchyAlpha
    get_Guard		proc :ptr
    put_Guard		proc :GuardInterval
    get_Mode		proc :ptr
    put_Mode		proc :TransmissionMode
    get_OtherFrequencyInUse proc :ptr
    put_OtherFrequencyInUse proc :VARIANT_BOOL
   .ends

endif

ifndef __IDVBTLocator2_INTERFACE_DEFINED__
define __IDVBTLocator2_INTERFACE_DEFINED__

DEFINE_IIDX(IDVBTLocator2, "448A2EDF-AE95-4b43-A3CC-747843C453D4")

.comdef IDVBTLocator2 : public IDVBTLocator

    get_PhysicalLayerPipeId proc :ptr
    put_PhysicalLayerPipeId proc :LONG
   .ends

endif

ifndef __IDVBSLocator_INTERFACE_DEFINED__
define __IDVBSLocator_INTERFACE_DEFINED__

DEFINE_IIDX(IDVBSLocator, "3D7C353C-0D04-45f1-A742-F97CC1188DC8")

.comdef IDVBSLocator : public IDigitalLocator

    get_SignalPolarisation proc :ptr
    put_SignalPolarisation proc :Polarisation
    get_WestPosition	proc :ptr
    put_WestPosition	proc :VARIANT_BOOL
    get_OrbitalPosition proc :ptr
    put_OrbitalPosition proc :LONG
    get_Azimuth		proc :ptr
    put_Azimuth		proc :LONG
    get_Elevation	proc :ptr
    put_Elevation	proc :LONG
   .ends

endif

ifndef __IDVBSLocator2_INTERFACE_DEFINED__
define __IDVBSLocator2_INTERFACE_DEFINED__

DEFINE_IIDX(IDVBSLocator2, "6044634A-1733-4f99-B982-5FB12AFCE4F0")

.comdef IDVBSLocator2 : public IDVBSLocator

    get_DiseqLNBSource	proc :ptr
    put_DiseqLNBSource	proc :LNB_Source
    get_LocalOscillatorOverrideLow proc :ptr
    put_LocalOscillatorOverrideLow proc :LONG
    get_LocalOscillatorOverrideHigh proc :ptr
    put_LocalOscillatorOverrideHigh proc :LONG
    get_LocalLNBSwitchOverride proc :ptr
    put_LocalLNBSwitchOverride proc :LONG
    get_LocalSpectralInversionOverride proc :ptr
    put_LocalSpectralInversionOverride proc :SpectralInversion
    get_SignalRollOff	proc :ptr
    put_SignalRollOff	proc :RollOff
    get_SignalPilot	proc :ptr
    put_SignalPilot	proc :Pilot
   .ends

endif

ifndef __IDVBCLocator_INTERFACE_DEFINED__
define __IDVBCLocator_INTERFACE_DEFINED__

DEFINE_IIDX(IDVBCLocator, "6E42F36E-1DD2-43c4-9F78-69D25AE39034")

.comdef IDVBCLocator : public IDigitalLocator
   .ends

endif

ifndef __IISDBSLocator_INTERFACE_DEFINED__
define __IISDBSLocator_INTERFACE_DEFINED__

DEFINE_IIDX(IISDBSLocator, "C9897087-E29C-473f-9E4B-7072123DEA14")

.comdef IISDBSLocator : public IDVBSLocator
   .ends

endif

ifndef __IESEvent_INTERFACE_DEFINED__
define __IESEvent_INTERFACE_DEFINED__

DEFINE_IIDX(IESEvent, "1F0E5357-AF43-44e6-8547-654C645145D2")

.comdef IESEvent : public IUnknown

    GetEventId		proc :ptr
    GetEventType	proc :ptr
    SetCompletionStatus proc :DWORD
    GetData		proc :ptr
    GetStringData	proc :ptr
   .ends

endif

ifndef __IESOpenMmiEvent_INTERFACE_DEFINED__
define __IESOpenMmiEvent_INTERFACE_DEFINED__

DEFINE_IIDX(IESOpenMmiEvent, "BA4B6526-1A35-4635-8B56-3EC612746A8C")

.comdef IESOpenMmiEvent : public IESEvent

    GetDialogNumber	proc :ptr, :ptr
    GetDialogType	proc :ptr
    GetDialogData	proc :ptr
    GetDialogStringData proc :ptr, :ptr
   .ends

endif

ifndef __IESCloseMmiEvent_INTERFACE_DEFINED__
define __IESCloseMmiEvent_INTERFACE_DEFINED__

DEFINE_IIDX(IESCloseMmiEvent, "6B80E96F-55E2-45aa-B754-0C23C8E7D5C1")

.comdef IESCloseMmiEvent : public IESEvent

    GetDialogNumber	proc :ptr
   .ends

endif

ifndef __IESValueUpdatedEvent_INTERFACE_DEFINED__
define __IESValueUpdatedEvent_INTERFACE_DEFINED__

DEFINE_IIDX(IESValueUpdatedEvent, "8A24C46E-BB63-4664-8602-5D9C718C146D")

.comdef IESValueUpdatedEvent : public IESEvent

    GetValueNames	proc :ptr
   .ends

endif

ifndef __IESRequestTunerEvent_INTERFACE_DEFINED__
define __IESRequestTunerEvent_INTERFACE_DEFINED__

DEFINE_IIDX(IESRequestTunerEvent, "54C7A5E8-C3BB-4f51-AF14-E0E2C0E34C6D")

.comdef IESRequestTunerEvent : public IESEvent

    GetPriority		proc :ptr
    GetReason		proc :ptr
    GetConsequences	proc :ptr
    GetEstimatedTime	proc :ptr
   .ends

endif

ifndef __IESIsdbCasResponseEvent_INTERFACE_DEFINED__
define __IESIsdbCasResponseEvent_INTERFACE_DEFINED__

DEFINE_IIDX(IESIsdbCasResponseEvent, "2017cb03-dc0f-4c24-83ca-36307b2cd19f")

.comdef IESIsdbCasResponseEvent : public IESEvent

    GetRequestId	proc :ptr
    GetStatus		proc :ptr
    GetDataLength	proc :ptr
    GetResponseData	proc :ptr
   .ends

endif

ifndef __IGpnvsCommonBase_INTERFACE_DEFINED__
define __IGpnvsCommonBase_INTERFACE_DEFINED__

DEFINE_IIDX(IGpnvsCommonBase, "907E0B5C-E42D-4f04-91F0-26F401F36907")

.comdef IGpnvsCommonBase : public IUnknown

    GetValueUpdateName	proc :ptr
   .ends

endif

ifndef __IESEventFactory_INTERFACE_DEFINED__
define __IESEventFactory_INTERFACE_DEFINED__

DEFINE_IIDX(IESEventFactory, "506A09B8-7F86-4e04-AC05-3303BFE8FC49")

.comdef IESEventFactory : public IUnknown

    CreateESEvent	proc :ptr, :DWORD, :ptr, :DWORD, :ptr, :BSTR, :ptr,:ptr
   .ends

endif

ifndef __IESLicenseRenewalResultEvent_INTERFACE_DEFINED__
define __IESLicenseRenewalResultEvent_INTERFACE_DEFINED__

DEFINE_IIDX(IESLicenseRenewalResultEvent, "d5a48ef5-a81b-4df0-acaa-5e35e7ea45d4")

.comdef IESLicenseRenewalResultEvent : public IESEvent

    GetCallersId	proc :ptr
    GetFileName		proc :ptr
    IsRenewalSuccessful proc :ptr
    IsCheckEntitlementCallRequired proc :ptr
    GetDescrambledStatus proc :ptr
    GetRenewalResultCode proc :ptr
    GetCASFailureCode	proc :ptr
    GetRenewalHResult	proc :ptr
    GetEntitlementTokenLength proc :ptr
    GetEntitlementToken proc :ptr
    GetExpiryDate	proc :ptr
   .ends

endif

ifndef __IESFileExpiryDateEvent_INTERFACE_DEFINED__
define __IESFileExpiryDateEvent_INTERFACE_DEFINED__

DEFINE_IIDX(IESFileExpiryDateEvent, "BA9EDCB6-4D36-4cfe-8C56-87A6B0CA48E1")

.comdef IESFileExpiryDateEvent : public IESEvent

    GetTunerId		proc :ptr
    GetExpiryDate	proc :ptr
    GetFinalExpiryDate	proc :ptr
    GetMaxRenewalCount	proc :ptr
    IsEntitlementTokenPresent proc :ptr
    DoesExpireAfterFirstUse proc :ptr
   .ends

endif

ifndef __IESEvents_INTERFACE_DEFINED__
define __IESEvents_INTERFACE_DEFINED__

DEFINE_IIDX(IESEvents, "ABD414BF-CFE5-4e5e-AF5B-4B4E49C5BFEB")

.comdef IESEvents : public IUnknown

    OnESEventReceived	proc :GUID, :ptr
   .ends

endif

ifndef __IESEventService_INTERFACE_DEFINED__
define __IESEventService_INTERFACE_DEFINED__

DEFINE_IIDX(IESEventService, "ED89A619-4C06-4b2f-99EB-C7669B13047C")

.comdef IESEventService : public IUnknown

    FireESEvent		proc :ptr
   .ends

endif

ifndef __IESEventServiceConfiguration_INTERFACE_DEFINED__
define __IESEventServiceConfiguration_INTERFACE_DEFINED__

DEFINE_IIDX(IESEventServiceConfiguration, "33B9DAAE-9309-491d-A051-BCAD2A70CD66")

.comdef IESEventServiceConfiguration : public IUnknown

    SetParent		proc :ptr
    RemoveParent	proc
    SetOwner		proc :ptr
    RemoveOwner		proc
    SetGraph		proc :ptr
    RemoveGraph		proc :ptr
   .ends

endif

ifndef __IBroadcastEvent_INTERFACE_DEFINED__
define __IBroadcastEvent_INTERFACE_DEFINED__

DEFINE_IIDX(IBroadcastEvent, "3B21263F-26E8-489d-AAC4-924F7EFD9511")

.comdef IBroadcastEvent : public IUnknown

    Fire		proc :GUID
   .ends

endif

ifndef __IBroadcastEventEx_INTERFACE_DEFINED__
define __IBroadcastEventEx_INTERFACE_DEFINED__

DEFINE_IIDX(IBroadcastEventEx, "3d9e3887-1929-423f-8021-43682de95448")

.comdef IBroadcastEventEx : public IBroadcastEvent

    FireEx		proc :GUID, :ULONG, :ULONG, :ULONG, :ULONG
   .ends

endif

ifndef __IRegisterTuner_INTERFACE_DEFINED__
define __IRegisterTuner_INTERFACE_DEFINED__

DEFINE_IIDX(IRegisterTuner, "359B3901-572C-4854-BB49-CDEF66606A25")

.comdef IRegisterTuner : public IUnknown

    Register		proc :ptr, :ptr
    Unregister		proc
   .ends

endif

ifndef __IBDAComparable_INTERFACE_DEFINED__
define __IBDAComparable_INTERFACE_DEFINED__

DEFINE_IIDX(IBDAComparable, "B34505E0-2F0E-497b-80BC-D43F3B24ED7F")

.comdef IBDAComparable : public IUnknown

    HashEquivalentIncremental proc :int64_t, :DWORD, :ptr
   .ends

endif

ifndef __IPersistTuneXml_INTERFACE_DEFINED__
define __IPersistTuneXml_INTERFACE_DEFINED__

DEFINE_IIDX(IPersistTuneXml, "0754CD31-8D15-47a9-8215-D20064157244")

.comdef IPersistTuneXml : public IPersist

    InitNew		proc
    Load		proc :VARIANT
    Save		proc :ptr
   .ends

endif

ifndef __IPersistTuneXmlUtility_INTERFACE_DEFINED__
define __IPersistTuneXmlUtility_INTERFACE_DEFINED__

DEFINE_IIDX(IPersistTuneXmlUtility, "990237AE-AC11-4614-BE8F-DD217A4CB4CB")

.comdef IPersistTuneXmlUtility : public IUnknown

    Deserialize		proc :VARIANT, :ptr
   .ends

endif

ifndef __IPersistTuneXmlUtility2_INTERFACE_DEFINED__
define __IPersistTuneXmlUtility2_INTERFACE_DEFINED__

DEFINE_IIDX(IPersistTuneXmlUtility2, "992E165F-EA24-4b2f-9A1D-009D92120451")

.comdef IPersistTuneXmlUtility2 : public IPersistTuneXmlUtility

    Serialize		proc :ptr, :ptr
   .ends

endif

ifndef __IBDACreateTuneRequestEx_INTERFACE_DEFINED__
define __IBDACreateTuneRequestEx_INTERFACE_DEFINED__

DEFINE_IIDX(IBDACreateTuneRequestEx, "C0A4A1D4-2B3C-491a-BA22-499FBADD4D12")

.comdef IBDACreateTuneRequestEx : public IUnknown

    CreateTuneRequestEx proc :REFCLSID, :ptr
   .ends

endif

ifndef __TunerLib_LIBRARY_DEFINED__
define __TunerLib_LIBRARY_DEFINED__

SID_ESEventService	equ <CLSID_ESEventService>
SID_ESEventFactory	equ <CLSID_ESEventFactory>
SID_SBroadcastEventService equ <CLSID_BroadcastEventService>
SID_SContentTuneRequest equ <IID_ITuner>
SID_ScanningTuner	equ <IID_IScanningTuner>
SID_ScanningTunerEx	equ <IID_IScanningTunerEx>

externdef		LIBID_TunerLib:IID

DEFINE_GUIDS(CLSID_SystemTuningSpaces, "D02AAC50-027E-11d3-9D8E-00C04F72D980")
DEFINE_GUIDS(CLSID_TuningSpace, "5FFDC5E6-B83A-4b55-B6E8-C69E765FE9DB")
DEFINE_GUIDS(CLSID_ChannelIDTuningSpace, "CC829A2F-3365-463f-AF13-81DBB6F3A555")
DEFINE_GUIDS(CLSID_ATSCTuningSpace, "A2E30750-6C3D-11d3-B653-00C04F79498E")
DEFINE_GUIDS(CLSID_DigitalCableTuningSpace, "D9BB4CEE-B87A-47F1-AC92-B08D9C7813FC")
DEFINE_GUIDS(CLSID_AnalogRadioTuningSpace, "8A674B4C-1F63-11d3-B64C-00C04F79498E")
DEFINE_GUIDS(CLSID_AuxInTuningSpace, "F9769A06-7ACA-4e39-9CFB-97BB35F0E77E")
DEFINE_GUIDS(CLSID_AnalogTVTuningSpace, "8A674B4D-1F63-11d3-B64C-00C04F79498E")
DEFINE_GUIDS(CLSID_DVBTuningSpace, "C6B14B32-76AA-4a86-A7AC-5C79AAF58DA7")
DEFINE_GUIDS(CLSID_DVBSTuningSpace, "B64016F3-C9A2-4066-96F0-BD9563314726")
DEFINE_GUIDS(CLSID_ComponentTypes, "A1A2B1C4-0E3A-11d3-9D8E-00C04F72D980")
DEFINE_GUIDS(CLSID_ComponentType, "823535A0-0318-11d3-9D8E-00C04F72D980")
DEFINE_GUIDS(CLSID_LanguageComponentType, "1BE49F30-0E1B-11d3-9D8E-00C04F72D980")
DEFINE_GUIDS(CLSID_MPEG2ComponentType, "418008F3-CF67-4668-9628-10DC52BE1D08")
DEFINE_GUIDS(CLSID_ATSCComponentType, "A8DCF3D5-0780-4ef4-8A83-2CFFAACB8ACE")
DEFINE_GUIDS(CLSID_Components, "809B6661-94C4-49e6-B6EC-3F0F862215AA")
DEFINE_GUIDS(CLSID_Component, "59DC47A8-116C-11d3-9D8E-00C04F72D980")
DEFINE_GUIDS(CLSID_MPEG2Component, "055CB2D7-2969-45cd-914B-76890722F112")
DEFINE_GUIDS(CLSID_AnalogAudioComponentType, "28AB0005-E845-4FFA-AA9B-F4665236141C")
DEFINE_GUIDS(CLSID_TuneRequest, "B46E0D38-AB35-4a06-A137-70576B01B39F")
DEFINE_GUIDS(CLSID_ChannelIDTuneRequest, "3A9428A7-31A4-45e9-9EFB-E055BF7BB3DB")
DEFINE_GUIDS(CLSID_ChannelTuneRequest, "0369B4E5-45B6-11d3-B650-00C04F79498E")
DEFINE_GUIDS(CLSID_ATSCChannelTuneRequest, "0369B4E6-45B6-11d3-B650-00C04F79498E")
DEFINE_GUIDS(CLSID_DigitalCableTuneRequest, "26EC0B63-AA90-458A-8DF4-5659F2C8A18A")
DEFINE_GUIDS(CLSID_MPEG2TuneRequest, "0955AC62-BF2E-4cba-A2B9-A63F772D46CF")
DEFINE_GUIDS(CLSID_MPEG2TuneRequestFactory, "2C63E4EB-4CEA-41b8-919C-E947EA19A77C")
DEFINE_GUIDS(CLSID_Locator, "0888C883-AC4F-4943-B516-2C38D9B34562")
DEFINE_GUIDS(CLSID_DigitalLocator, "6E50CC0D-C19B-4BF6-810B-5BD60761F5CC")
DEFINE_GUIDS(CLSID_AnalogLocator, "49638B91-48AB-48B7-A47A-7D0E75A08EDE")
DEFINE_GUIDS(CLSID_ATSCLocator, "8872FF1B-98FA-4d7a-8D93-C9F1055F85BB")
DEFINE_GUIDS(CLSID_DigitalCableLocator, "03C06416-D127-407A-AB4C-FDD279ABBE5D")
DEFINE_GUIDS(CLSID_DVBTLocator, "9CD64701-BDF3-4d14-8E03-F12983D86664")
DEFINE_GUIDS(CLSID_DVBTLocator2, "EFE3FA02-45D7-4920-BE96-53FA7F35B0E6")
DEFINE_GUIDS(CLSID_DVBSLocator, "1DF7D126-4050-47f0-A7CF-4C4CA9241333")
DEFINE_GUIDS(CLSID_DVBCLocator, "C531D9FD-9685-4028-8B68-6E1232079F1E")
DEFINE_GUIDS(CLSID_ISDBSLocator, "6504AFED-A629-455c-A7F1-04964DEA5CC4")
DEFINE_GUIDS(CLSID_DVBTuneRequest, "15D6504A-5494-499c-886C-973C9E53B9F1")
DEFINE_GUIDS(CLSID_CreatePropBagOnRegKey, "8A674B49-1F63-11d3-B64C-00C04F79498E")
DEFINE_GUIDS(CLSID_BroadcastEventService, "0B3FFB92-0919-4934-9D5B-619C719D0202")
DEFINE_GUIDS(CLSID_TunerMarshaler, "6438570B-0C08-4a25-9504-8012BB4D50CF")
DEFINE_GUIDS(CLSID_PersistTuneXmlUtility, "E77026B0-B97F-4cbb-B7FB-F4F03AD69F11")
DEFINE_GUIDS(CLSID_ESEventService, "C20447FC-EC60-475e-813F-D2B0A6DECEFE")
DEFINE_GUIDS(CLSID_ESEventFactory, "8E8A07DA-71F8-40c1-A929-5E3A868AC2C6")

endif

endif

endif
