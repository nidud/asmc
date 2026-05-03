ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Emedia2Edevices_h__
define __windows2Emedia2Edevices_h__
ifndef __windows2Efoundation_h__
include Windows.Foundation.inc
endif
include Windows.Media.Capture.inc
include windows.media.mediaproperties.inc

.namespace Windows
.namespace Media
.namespace Devices

.enum TelephonyKey {
    TelephonyKey_D0	= 0,
    TelephonyKey_D1	= 1,
    TelephonyKey_D2	= 2,
    TelephonyKey_D3	= 3,
    TelephonyKey_D4	= 4,
    TelephonyKey_D5	= 5,
    TelephonyKey_D6	= 6,
    TelephonyKey_D7	= 7,
    TelephonyKey_D8	= 8,
    TelephonyKey_D9	= 9,
    TelephonyKey_Star	= 10,
    TelephonyKey_Pound	= 11,
    TelephonyKey_A	= 12,
    TelephonyKey_B	= 13,
    TelephonyKey_C	= 14,
    TelephonyKey_D	= 15
    }

.enum AudioDeviceRole {
    AudioDeviceRole_Default	= 0,
    AudioDeviceRole_Communications	= 1
    }

.enum CaptureSceneMode {
    CaptureSceneMode_Auto	= 0,
    CaptureSceneMode_Manual	= 1,
    CaptureSceneMode_Macro	= 2,
    CaptureSceneMode_Portrait	= 3,
    CaptureSceneMode_Sport	= 4,
    CaptureSceneMode_Snow	= 5,
    CaptureSceneMode_Night	= 6,
    CaptureSceneMode_Beach	= 7,
    CaptureSceneMode_Sunset	= 8,
    CaptureSceneMode_Candlelight	= 9,
    CaptureSceneMode_Landscape	= 10,
    CaptureSceneMode_NightPortrait	= 11,
    CaptureSceneMode_Backlit	= 12
    }

.enum IsoSpeedPreset {
    IsoSpeedPreset_Auto = 0,
    IsoSpeedPreset_Iso50	= 1,
    IsoSpeedPreset_Iso80	= 2,
    IsoSpeedPreset_Iso100	= 3,
    IsoSpeedPreset_Iso200	= 4,
    IsoSpeedPreset_Iso400	= 5,
    IsoSpeedPreset_Iso800	= 6,
    IsoSpeedPreset_Iso1600	= 7,
    IsoSpeedPreset_Iso3200	= 8,
    IsoSpeedPreset_Iso6400	= 9,
    IsoSpeedPreset_Iso12800	= 10,
    IsoSpeedPreset_Iso25600	= 11
    }

.enum ColorTemperaturePreset {
    ColorTemperaturePreset_Auto = 0,
    ColorTemperaturePreset_Manual	= 1,
    ColorTemperaturePreset_Cloudy	= 2,
    ColorTemperaturePreset_Daylight	= 3,
    ColorTemperaturePreset_Flash	= 4,
    ColorTemperaturePreset_Fluorescent	= 5,
    ColorTemperaturePreset_Tungsten	= 6,
    ColorTemperaturePreset_Candlelight	= 7
    }

.enum FocusPreset {
    FocusPreset_Auto	= 0,
    FocusPreset_Manual	= 1,
    FocusPreset_AutoMacro	= 2,
    FocusPreset_AutoNormal	= 3,
    FocusPreset_AutoInfinity	= 4,
    FocusPreset_AutoHyperfocal	= 5
    }

.enum CaptureUse {
    CaptureUse_None	= 0,
    CaptureUse_Photo	= 1,
    CaptureUse_Video	= 2
    }

.endn
.endn
.endn

ifndef ____FIIterator_1_Windows__CMedia__CDevices__CCaptureSceneMode_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CMedia__CDevices__CCaptureSceneMode_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CMedia__CDevices__CCaptureSceneMode, "aafa6d7a-2f7f-5dd7-aa0a-265731a2b3b3")

.comdef __FIIterator_1_Windows__CMedia__CDevices__CCaptureSceneMode : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CMedia__CDevices__CCaptureSceneMode_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CMedia__CDevices__CCaptureSceneMode_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CMedia__CDevices__CCaptureSceneMode, "16d26b98-2cbc-52f0-ab64-1723714418e9")

.comdef __FIIterable_1_Windows__CMedia__CDevices__CCaptureSceneMode : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CMedia__CDevices__CFocusPreset_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CMedia__CDevices__CFocusPreset_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CMedia__CDevices__CFocusPreset, "d3ebc8e9-f0c5-51c0-bb86-bdea0a6946fb")

.comdef __FIIterator_1_Windows__CMedia__CDevices__CFocusPreset : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CMedia__CDevices__CFocusPreset_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CMedia__CDevices__CFocusPreset_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CMedia__CDevices__CFocusPreset, "26ba711b-3a32-5216-bc34-61ecafbebdc1")

.comdef __FIIterable_1_Windows__CMedia__CDevices__CFocusPreset : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CMedia__CDevices__CIsoSpeedPreset_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CMedia__CDevices__CIsoSpeedPreset_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CMedia__CDevices__CIsoSpeedPreset, "1b33af76-980b-5348-916a-793f61b555a0")

.comdef __FIIterator_1_Windows__CMedia__CDevices__CIsoSpeedPreset : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CMedia__CDevices__CIsoSpeedPreset_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CMedia__CDevices__CIsoSpeedPreset_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CMedia__CDevices__CIsoSpeedPreset, "94839abe-9712-545a-a94d-a567a3e8dfb7")

.comdef __FIIterable_1_Windows__CMedia__CDevices__CIsoSpeedPreset : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CMedia__CDevices__CRegionOfInterest_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CMedia__CDevices__CRegionOfInterest_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CMedia__CDevices__CRegionOfInterest, "8eb80e4e-9691-594f-8b3d-f52ecc0f7837")

.comdef __FIIterator_1_Windows__CMedia__CDevices__CRegionOfInterest : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CMedia__CDevices__CRegionOfInterest_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CMedia__CDevices__CRegionOfInterest_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CMedia__CDevices__CRegionOfInterest, "d73144c7-9d75-5dfb-8040-626202dcf454")

.comdef __FIIterable_1_Windows__CMedia__CDevices__CRegionOfInterest : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CMedia__CDevices__CCaptureSceneMode_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CMedia__CDevices__CCaptureSceneMode_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CMedia__CDevices__CCaptureSceneMode, "9b915d69-e718-5b48-bb94-54bdf3737ea5")

.comdef __FIVectorView_1_Windows__CMedia__CDevices__CCaptureSceneMode : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :Windows::Media::Devices::CaptureSceneMode, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CMedia__CDevices__CFocusPreset_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CMedia__CDevices__CFocusPreset_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CMedia__CDevices__CFocusPreset, "d8a495e3-d7d4-5e9f-a9c2-6b250655a2e0")

.comdef __FIVectorView_1_Windows__CMedia__CDevices__CFocusPreset : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :Windows::Media::Devices::FocusPreset, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CMedia__CDevices__CIsoSpeedPreset_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CMedia__CDevices__CIsoSpeedPreset_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CMedia__CDevices__CIsoSpeedPreset, "ef6c9fe3-06f9-5eff-98a8-917d9644c946")

.comdef __FIVectorView_1_Windows__CMedia__CDevices__CIsoSpeedPreset : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :Windows::Media::Devices::IsoSpeedPreset, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_IInspectable_Windows__CMedia__CDevices__CDefaultAudioCaptureDeviceChangedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_IInspectable_Windows__CMedia__CDevices__CDefaultAudioCaptureDeviceChangedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_IInspectable_Windows__CMedia__CDevices__CDefaultAudioCaptureDeviceChangedEventArgs, "97d07327-2c78-57bc-98e6-a24cd024cf5b")

.comdef __FITypedEventHandler_2_IInspectable_Windows__CMedia__CDevices__CDefaultAudioCaptureDeviceChangedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_IInspectable_Windows__CMedia__CDevices__CDefaultAudioRenderDeviceChangedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_IInspectable_Windows__CMedia__CDevices__CDefaultAudioRenderDeviceChangedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_IInspectable_Windows__CMedia__CDevices__CDefaultAudioRenderDeviceChangedEventArgs, "fd732aca-dafc-5b7d-bf72-b560b78d260c")

.comdef __FITypedEventHandler_2_IInspectable_Windows__CMedia__CDevices__CDefaultAudioRenderDeviceChangedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

.namespace Windows
.namespace Media
.namespace Devices

ifndef ____x_ABI_CWindows_CMedia_CDevices_CICallControlEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CDevices_CICallControlEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(ICallControlEventHandler, "596F759F-50DF-4454-BC63-4D3D01B61958")

.comdef ICallControlEventHandler : public IUnknown

    _Invoke		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CDevices_CIDialRequestedEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CDevices_CIDialRequestedEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IDialRequestedEventHandler, "5ABBFFDB-C21F-4BC4-891B-257E28C1B1A4")

.comdef IDialRequestedEventHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CDevices_CIRedialRequestedEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CDevices_CIRedialRequestedEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IRedialRequestedEventHandler, "BAF257D1-4EBD-4B84-9F47-6EC43D75D8B1")

.comdef IRedialRequestedEventHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CDevices_CIKeypadPressedEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CDevices_CIKeypadPressedEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IKeypadPressedEventHandler, "E637A454-C527-422C-8926-C9AF83B559A0")

.comdef IKeypadPressedEventHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CDevices_CIDialRequestedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CDevices_CIDialRequestedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Devices_IDialRequestedEventArgs <L"Windows.Media.Devices.IDialRequestedEventArgs">
DEFINE_IIDX(IDialRequestedEventArgs, "037B929E-953C-4286-8866-4F0F376C855A")

.comdef IDialRequestedEventArgs : public IInspectable

    Handled		proc
    get_Contact		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CDevices_CIRedialRequestedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CDevices_CIRedialRequestedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Devices_IRedialRequestedEventArgs <L"Windows.Media.Devices.IRedialRequestedEventArgs">
DEFINE_IIDX(IRedialRequestedEventArgs, "7EB55209-76AB-4C31-B40E-4B58379D580C")

.comdef IRedialRequestedEventArgs : public IInspectable

    Handled		proc
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CDevices_CIKeypadPressedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CDevices_CIKeypadPressedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Devices_IKeypadPressedEventArgs <L"Windows.Media.Devices.IKeypadPressedEventArgs">
DEFINE_IIDX(IKeypadPressedEventArgs, "D3A43900-B4FA-49CD-9442-89AF6568F601")

.comdef IKeypadPressedEventArgs : public IInspectable

    get_TelephonyKey	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CDevices_CICallControl_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CDevices_CICallControl_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Devices_ICallControl <L"Windows.Media.Devices.ICallControl">
DEFINE_IIDX(ICallControl, "A520D0D6-AE8D-45DB-8011-CA49D3B3E578")

.comdef ICallControl : public IInspectable

    IndicateNewIncomingCall proc :boolean, :HSTRING, :ptr
    IndicateNewOutgoingCall proc :ptr
    IndicateActiveCall	proc :UINT64
    EndCall		proc :UINT64
    get_HasRinger	proc :ptr
    add_AnswerRequested proc :ptr, :ptr
    remove_AnswerRequested proc :EventRegistrationToken
    add_HangUpRequested proc :ptr, :ptr
    remove_HangUpRequested proc :EventRegistrationToken
    add_DialRequested	proc :ptr, :ptr
    remove_DialRequested proc :EventRegistrationToken
    add_RedialRequested proc :ptr, :ptr
    remove_RedialRequested proc :EventRegistrationToken
    add_KeypadPressed	proc :ptr, :ptr
    remove_KeypadPressed proc :EventRegistrationToken
    add_AudioTransferRequested proc :ptr, :ptr
    remove_AudioTransferRequested proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CDevices_CICallControlStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CDevices_CICallControlStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Devices_ICallControlStatics <L"Windows.Media.Devices.ICallControlStatics">
DEFINE_IIDX(ICallControlStatics, "03945AD5-85AB-40E1-AF19-56C94303B019")

.comdef ICallControlStatics : public IInspectable

    GetDefault		proc :ptr
    FromId		proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CDevices_CIDefaultAudioDeviceChangedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CDevices_CIDefaultAudioDeviceChangedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Devices_IDefaultAudioDeviceChangedEventArgs <L"Windows.Media.Devices.IDefaultAudioDeviceChangedEventArgs">
DEFINE_IIDX(IDefaultAudioDeviceChangedEventArgs, "110F882F-1C05-4657-A18E-47C9B69F07AB")

.comdef IDefaultAudioDeviceChangedEventArgs : public IInspectable

    get_Id		proc :ptr
    get_Role		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CDevices_CIMediaDeviceStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CDevices_CIMediaDeviceStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Devices_IMediaDeviceStatics <L"Windows.Media.Devices.IMediaDeviceStatics">
DEFINE_IIDX(IMediaDeviceStatics, "AA2D9A40-909F-4BBA-BF8B-0C0D296F14F0")

.comdef IMediaDeviceStatics : public IInspectable

    GetAudioCaptureSelector proc :ptr
    GetAudioRenderSelector proc :ptr
    GetVideoCaptureSelector proc :ptr
    GetDefaultAudioCaptureId proc :Windows::Media::Devices::AudioDeviceRole, :ptr
    GetDefaultAudioRenderId proc :Windows::Media::Devices::AudioDeviceRole, :ptr
    add_DefaultAudioCaptureDeviceChanged proc :ptr, :ptr
    remove_DefaultAudioCaptureDeviceChanged proc :EventRegistrationToken
    add_DefaultAudioRenderDeviceChanged proc :ptr, :ptr
    remove_DefaultAudioRenderDeviceChanged proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CDevices_CISceneModeControl_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CDevices_CISceneModeControl_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Devices_ISceneModeControl <L"Windows.Media.Devices.ISceneModeControl">
DEFINE_IIDX(ISceneModeControl, "D48E5AF7-8D59-4854-8C62-12C70BA89B7C")

.comdef ISceneModeControl : public IInspectable

    get_SupportedModes	proc :ptr
    get_Value		proc :ptr
    SetValueAsync	proc :Windows::Media::Devices::CaptureSceneMode, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CDevices_CITorchControl_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CDevices_CITorchControl_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Devices_ITorchControl <L"Windows.Media.Devices.ITorchControl">
DEFINE_IIDX(ITorchControl, "A6053665-8250-416C-919A-724296AFA306")

.comdef ITorchControl : public IInspectable

    get_Supported	proc :ptr
    get_PowerSupported	proc :ptr
    get_Enabled		proc :ptr
    put_Enabled		proc :boolean
    get_PowerPercent	proc :ptr
    put_PowerPercent	proc :FLOAT
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CDevices_CIFlashControl_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CDevices_CIFlashControl_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Devices_IFlashControl <L"Windows.Media.Devices.IFlashControl">
DEFINE_IIDX(IFlashControl, "DEF41DBE-7D68-45E3-8C0F-BE7BB32837D0")

.comdef IFlashControl : public IInspectable

    get_Supported	proc :ptr
    get_PowerSupported	proc :ptr
    get_RedEyeReductionSupported proc :ptr
    get_Enabled		proc :ptr
    put_Enabled		proc :boolean
    get_Auto		proc :ptr
    put_Auto		proc :boolean
    get_RedEyeReduction proc :ptr
    put_RedEyeReduction proc :boolean
    get_PowerPercent	proc :ptr
    put_PowerPercent	proc :FLOAT
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CDevices_CIExposureCompensationControl_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CDevices_CIExposureCompensationControl_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Devices_IExposureCompensationControl <L"Windows.Media.Devices.IExposureCompensationControl">
DEFINE_IIDX(IExposureCompensationControl, "81C8E834-DCEC-4011-A610-1F3847E64ACA")

.comdef IExposureCompensationControl : public IInspectable

    get_Supported	proc :ptr
    get_Min		proc :ptr
    get_Max		proc :ptr
    get_Step		proc :ptr
    get_Value		proc :ptr
    SetValueAsync	proc :FLOAT, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CDevices_CIIsoSpeedControl_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CDevices_CIIsoSpeedControl_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Devices_IIsoSpeedControl <L"Windows.Media.Devices.IIsoSpeedControl">
DEFINE_IIDX(IIsoSpeedControl, "27B6C322-25AD-4F1B-AAAB-524AB376CA33")

.comdef IIsoSpeedControl : public IInspectable

    get_Supported	proc :ptr
    get_SupportedPresets proc :ptr
    get_Preset		proc :ptr
    SetPresetAsync	proc :Windows::Media::Devices::IsoSpeedPreset, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CDevices_CIWhiteBalanceControl_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CDevices_CIWhiteBalanceControl_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Devices_IWhiteBalanceControl <L"Windows.Media.Devices.IWhiteBalanceControl">
DEFINE_IIDX(IWhiteBalanceControl, "781F047E-7162-49C8-A8F9-9481C565363E")

.comdef IWhiteBalanceControl : public IInspectable

    get_Supported	proc :ptr
    get_Preset		proc :ptr
    SetPresetAsync	proc :Windows::Media::Devices::ColorTemperaturePreset, :ptr
    get_Min		proc :ptr
    get_Max		proc :ptr
    get_Step		proc :ptr
    get_Value		proc :ptr
    SetValueAsync	proc :UINT32, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CDevices_CIExposureControl_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CDevices_CIExposureControl_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Devices_IExposureControl <L"Windows.Media.Devices.IExposureControl">
DEFINE_IIDX(IExposureControl, "09E8CBE2-AD96-4F28-A0E0-96ED7E1B5FD2")

.comdef IExposureControl : public IInspectable

    get_Supported	proc :ptr
    get_Auto		proc :ptr
    SetAutoAsync	proc :boolean, :ptr
    get_Min		proc :ptr
    get_Max		proc :ptr
    get_Step		proc :ptr
    get_Value		proc :ptr
    SetValueAsync	proc :Windows::Foundation::TimeSpan, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CDevices_CIFocusControl_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CDevices_CIFocusControl_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Devices_IFocusControl <L"Windows.Media.Devices.IFocusControl">
DEFINE_IIDX(IFocusControl, "C0D889F6-5228-4453-B153-85606592B238")

.comdef IFocusControl : public IInspectable

    get_Supported	proc :ptr
    get_SupportedPresets proc :ptr
    get_Preset		proc :ptr
    SetPresetAsync	proc :Windows::Media::Devices::FocusPreset, :ptr
    SetPresetWithCompletionOptionAsync proc :Windows::Media::Devices::FocusPreset, :boolean, :ptr
    get_Min		proc :ptr
    get_Max		proc :ptr
    get_Step		proc :ptr
    get_Value		proc :ptr
    SetValueAsync	proc :UINT32, :ptr
    FocusAsync		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CDevices_CIRegionOfInterest_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CDevices_CIRegionOfInterest_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Devices_IRegionOfInterest <L"Windows.Media.Devices.IRegionOfInterest">
DEFINE_IIDX(IRegionOfInterest, "E5ECC834-CE66-4E05-A78F-CF391A5EC2D1")

.comdef IRegionOfInterest : public IInspectable

    get_AutoFocusEnabled proc :ptr
    put_AutoFocusEnabled proc :boolean
    get_AutoWhiteBalanceEnabled proc :ptr
    put_AutoWhiteBalanceEnabled proc :boolean
    get_AutoExposureEnabled proc :ptr
    put_AutoExposureEnabled proc :boolean
    get_Bounds		proc :ptr
    put_Bounds		proc :Windows::Foundation::Rect
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CDevices_CIRegionsOfInterestControl_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CDevices_CIRegionsOfInterestControl_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Devices_IRegionsOfInterestControl <L"Windows.Media.Devices.IRegionsOfInterestControl">
DEFINE_IIDX(IRegionsOfInterestControl, "C323F527-AB0B-4558-8B5B-DF5693DB0378")

.comdef IRegionsOfInterestControl : public IInspectable

    get_MaxRegions	proc :ptr
    SetRegionsAsync	proc :ptr, :ptr
    SetRegionsWithLockAsync proc :ptr, :boolean, :ptr
    ClearRegionsAsync	proc :ptr
    get_AutoFocusSupported proc :ptr
    get_AutoWhiteBalanceSupported proc :ptr
    get_AutoExposureSupported proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CDevices_CIMediaDeviceController_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CDevices_CIMediaDeviceController_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Devices_IMediaDeviceController <L"Windows.Media.Devices.IMediaDeviceController">
DEFINE_IIDX(IMediaDeviceController, "F6F8F5CE-209A-48FB-86FC-D44578F317E6")

.comdef IMediaDeviceController : public IInspectable

    GetAvailableMediaStreamProperties proc :Windows::Media::Capture::MediaStreamType, :ptr
    GetMediaStreamProperties proc :Windows::Media::Capture::MediaStreamType, :ptr
    SetMediaStreamPropertiesAsync proc :Windows::Media::Capture::MediaStreamType, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CDevices_CIAudioDeviceController_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CDevices_CIAudioDeviceController_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Devices_IAudioDeviceController <L"Windows.Media.Devices.IAudioDeviceController">
DEFINE_IIDX(IAudioDeviceController, "EDD4A388-79C7-4F7C-90E8-EF934B21580A")

.comdef IAudioDeviceController : public IInspectable

    put_Muted		proc :boolean
    get_Muted		proc :ptr
    put_VolumePercent	proc :FLOAT
    get_VolumePercent	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CDevices_CIVideoDeviceController_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CDevices_CIVideoDeviceController_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Devices_IVideoDeviceController <L"Windows.Media.Devices.IVideoDeviceController">
DEFINE_IIDX(IVideoDeviceController, "99555575-2E2E-40B8-B6C7-F82D10013210")

.comdef IVideoDeviceController : public IInspectable

    get_Brightness	proc :ptr
    get_Contrast	proc :ptr
    get_Hue		proc :ptr
    get_WhiteBalance	proc :ptr
    get_BacklightCompensation proc :ptr
    get_Pan		proc :ptr
    get_Tilt		proc :ptr
    get_Zoom		proc :ptr
    get_Roll		proc :ptr
    get_Exposure	proc :ptr
    get_Focus		proc :ptr
    TrySetPowerlineFrequency proc :Windows::Media::Capture::PowerlineFrequency, :ptr
    TryGetPowerlineFrequency proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CDevices_CIAdvancedVideoCaptureDeviceController2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CDevices_CIAdvancedVideoCaptureDeviceController2_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Devices_IAdvancedVideoCaptureDeviceController2 <L"Windows.Media.Devices.IAdvancedVideoCaptureDeviceController2">
DEFINE_IIDX(IAdvancedVideoCaptureDeviceController2, "8BB94F8F-F11A-43DB-B402-11930B80AE56")

.comdef IAdvancedVideoCaptureDeviceController2 : public IInspectable

    get_LowLagPhotoSequence proc :ptr
    get_LowLagPhoto	proc :ptr
    get_SceneModeControl proc :ptr
    get_TorchControl	proc :ptr
    get_FlashControl	proc :ptr
    get_WhiteBalanceControl proc :ptr
    get_ExposureControl proc :ptr
    get_FocusControl	proc :ptr
    get_ExposureCompensationControl proc :ptr
    get_IsoSpeedControl proc :ptr
    get_RegionsOfInterestControl proc :ptr
    get_PrimaryUse	proc :ptr
    put_PrimaryUse	proc :Windows::Media::Devices::CaptureUse
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CDevices_CIMediaDeviceControl_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CDevices_CIMediaDeviceControl_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Devices_IMediaDeviceControl <L"Windows.Media.Devices.IMediaDeviceControl">
DEFINE_IIDX(IMediaDeviceControl, "EFA8DFA9-6F75-4863-BA0B-583F3036B4DE")

.comdef IMediaDeviceControl : public IInspectable

    get_Capabilities	proc :ptr
    TryGetValue		proc :ptr, :ptr
    TrySetValue		proc :DOUBLE, :ptr
    TryGetAuto		proc :ptr, :ptr
    TrySetAuto		proc :boolean, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CDevices_CIMediaDeviceControlCapabilities_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CDevices_CIMediaDeviceControlCapabilities_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Devices_IMediaDeviceControlCapabilities <L"Windows.Media.Devices.IMediaDeviceControlCapabilities">
DEFINE_IIDX(IMediaDeviceControlCapabilities, "23005816-EB85-43E2-B92B-8240D5EE70EC")

.comdef IMediaDeviceControlCapabilities : public IInspectable

    get_Supported	proc :ptr
    get_Min		proc :ptr
    get_Max		proc :ptr
    get_Step		proc :ptr
    get_Default		proc :ptr
    get_AutoModeSupported proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CDevices_CIAdvancedVideoCaptureDeviceController_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CDevices_CIAdvancedVideoCaptureDeviceController_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Devices_IAdvancedVideoCaptureDeviceController <L"Windows.Media.Devices.IAdvancedVideoCaptureDeviceController">
DEFINE_IIDX(IAdvancedVideoCaptureDeviceController, "DE6FF4D3-2B96-4583-80AB-B5B01DC6A8D7")

.comdef IAdvancedVideoCaptureDeviceController : public IInspectable

    SetDeviceProperty	proc :HSTRING, :ptr
    GetDeviceProperty	proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CDevices_CILowLagPhotoSequenceControl_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CDevices_CILowLagPhotoSequenceControl_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Devices_ILowLagPhotoSequenceControl <L"Windows.Media.Devices.ILowLagPhotoSequenceControl">
DEFINE_IIDX(ILowLagPhotoSequenceControl, "3DCF909D-6D16-409C-BAFE-B9A594C6FDE6")

.comdef ILowLagPhotoSequenceControl : public IInspectable

    get_Supported	proc :ptr
    get_MaxPastPhotos	proc :ptr
    get_MaxPhotosPerSecond proc :ptr
    get_PastPhotoLimit	proc :ptr
    put_PastPhotoLimit	proc :UINT32
    get_PhotosPerSecondLimit proc :ptr
    put_PhotosPerSecondLimit proc :FLOAT
    GetHighestConcurrentFrameRate proc :ptr, :ptr
    GetCurrentFrameRate proc :ptr
    get_ThumbnailEnabled proc :ptr
    put_ThumbnailEnabled proc :boolean
    get_ThumbnailFormat proc :ptr
    put_ThumbnailFormat proc :Windows::Media::MediaProperties::MediaThumbnailFormat
    get_DesiredThumbnailSize proc :ptr
    put_DesiredThumbnailSize proc :UINT32
    get_HardwareAcceleratedThumbnailSupported proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CDevices_CILowLagPhotoControl_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CDevices_CILowLagPhotoControl_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Devices_ILowLagPhotoControl <L"Windows.Media.Devices.ILowLagPhotoControl">
DEFINE_IIDX(ILowLagPhotoControl, "6D5C4DD0-FADF-415D-AEE6-3BAA529300C9")

.comdef ILowLagPhotoControl : public IInspectable

    GetHighestConcurrentFrameRate proc :ptr, :ptr
    GetCurrentFrameRate proc :ptr
    get_ThumbnailEnabled proc :ptr
    put_ThumbnailEnabled proc :boolean
    get_ThumbnailFormat proc :ptr
    put_ThumbnailFormat proc :Windows::Media::MediaProperties::MediaThumbnailFormat
    get_DesiredThumbnailSize proc :ptr
    put_DesiredThumbnailSize proc :UINT32
    get_HardwareAcceleratedThumbnailSupported proc :ptr
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_Media_Devices_DialRequestedEventArgs_DEFINED
define RUNTIMECLASS_Windows_Media_Devices_DialRequestedEventArgs_DEFINED
define RuntimeClass_Windows_Media_Devices_DialRequestedEventArgs <L"Windows.Media.Devices.DialRequestedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_Media_Devices_RedialRequestedEventArgs_DEFINED
define RUNTIMECLASS_Windows_Media_Devices_RedialRequestedEventArgs_DEFINED
define RuntimeClass_Windows_Media_Devices_RedialRequestedEventArgs <L"Windows.Media.Devices.RedialRequestedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_Media_Devices_KeypadPressedEventArgs_DEFINED
define RUNTIMECLASS_Windows_Media_Devices_KeypadPressedEventArgs_DEFINED
define RuntimeClass_Windows_Media_Devices_KeypadPressedEventArgs <L"Windows.Media.Devices.KeypadPressedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_Media_Devices_CallControl_DEFINED
define RUNTIMECLASS_Windows_Media_Devices_CallControl_DEFINED
define RuntimeClass_Windows_Media_Devices_CallControl <L"Windows.Media.Devices.CallControl">
endif
ifndef RUNTIMECLASS_Windows_Media_Devices_DefaultAudioCaptureDeviceChangedEventArgs_DEFINED
define RUNTIMECLASS_Windows_Media_Devices_DefaultAudioCaptureDeviceChangedEventArgs_DEFINED
define RuntimeClass_Windows_Media_Devices_DefaultAudioCaptureDeviceChangedEventArgs <L"Windows.Media.Devices.DefaultAudioCaptureDeviceChangedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_Media_Devices_DefaultAudioRenderDeviceChangedEventArgs_DEFINED
define RUNTIMECLASS_Windows_Media_Devices_DefaultAudioRenderDeviceChangedEventArgs_DEFINED
define RuntimeClass_Windows_Media_Devices_DefaultAudioRenderDeviceChangedEventArgs <L"Windows.Media.Devices.DefaultAudioRenderDeviceChangedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_Media_Devices_MediaDevice_DEFINED
define RUNTIMECLASS_Windows_Media_Devices_MediaDevice_DEFINED
define RuntimeClass_Windows_Media_Devices_MediaDevice <L"Windows.Media.Devices.MediaDevice">
endif
ifndef RUNTIMECLASS_Windows_Media_Devices_AudioDeviceController_DEFINED
define RUNTIMECLASS_Windows_Media_Devices_AudioDeviceController_DEFINED
define RuntimeClass_Windows_Media_Devices_AudioDeviceController <L"Windows.Media.Devices.AudioDeviceController">
endif
ifndef RUNTIMECLASS_Windows_Media_Devices_VideoDeviceController_DEFINED
define RUNTIMECLASS_Windows_Media_Devices_VideoDeviceController_DEFINED
define RuntimeClass_Windows_Media_Devices_VideoDeviceController <L"Windows.Media.Devices.VideoDeviceController">
endif
ifndef RUNTIMECLASS_Windows_Media_Devices_SceneModeControl_DEFINED
define RUNTIMECLASS_Windows_Media_Devices_SceneModeControl_DEFINED
define RuntimeClass_Windows_Media_Devices_SceneModeControl <L"Windows.Media.Devices.SceneModeControl">
endif
ifndef RUNTIMECLASS_Windows_Media_Devices_TorchControl_DEFINED
define RUNTIMECLASS_Windows_Media_Devices_TorchControl_DEFINED
define RuntimeClass_Windows_Media_Devices_TorchControl <L"Windows.Media.Devices.TorchControl">
endif
ifndef RUNTIMECLASS_Windows_Media_Devices_FlashControl_DEFINED
define RUNTIMECLASS_Windows_Media_Devices_FlashControl_DEFINED
define RuntimeClass_Windows_Media_Devices_FlashControl <L"Windows.Media.Devices.FlashControl">
endif
ifndef RUNTIMECLASS_Windows_Media_Devices_ExposureCompensationControl_DEFINED
define RUNTIMECLASS_Windows_Media_Devices_ExposureCompensationControl_DEFINED
define RuntimeClass_Windows_Media_Devices_ExposureCompensationControl <L"Windows.Media.Devices.ExposureCompensationControl">
endif
ifndef RUNTIMECLASS_Windows_Media_Devices_IsoSpeedControl_DEFINED
define RUNTIMECLASS_Windows_Media_Devices_IsoSpeedControl_DEFINED
define RuntimeClass_Windows_Media_Devices_IsoSpeedControl <L"Windows.Media.Devices.IsoSpeedControl">
endif
ifndef RUNTIMECLASS_Windows_Media_Devices_WhiteBalanceControl_DEFINED
define RUNTIMECLASS_Windows_Media_Devices_WhiteBalanceControl_DEFINED
define RuntimeClass_Windows_Media_Devices_WhiteBalanceControl <L"Windows.Media.Devices.WhiteBalanceControl">
endif
ifndef RUNTIMECLASS_Windows_Media_Devices_ExposureControl_DEFINED
define RUNTIMECLASS_Windows_Media_Devices_ExposureControl_DEFINED
define RuntimeClass_Windows_Media_Devices_ExposureControl <L"Windows.Media.Devices.ExposureControl">
endif
ifndef RUNTIMECLASS_Windows_Media_Devices_FocusControl_DEFINED
define RUNTIMECLASS_Windows_Media_Devices_FocusControl_DEFINED
define RuntimeClass_Windows_Media_Devices_FocusControl <L"Windows.Media.Devices.FocusControl">
endif
ifndef RUNTIMECLASS_Windows_Media_Devices_RegionOfInterest_DEFINED
define RUNTIMECLASS_Windows_Media_Devices_RegionOfInterest_DEFINED
define RuntimeClass_Windows_Media_Devices_RegionOfInterest <L"Windows.Media.Devices.RegionOfInterest">
endif
ifndef RUNTIMECLASS_Windows_Media_Devices_RegionsOfInterestControl_DEFINED
define RUNTIMECLASS_Windows_Media_Devices_RegionsOfInterestControl_DEFINED
define RuntimeClass_Windows_Media_Devices_RegionsOfInterestControl <L"Windows.Media.Devices.RegionsOfInterestControl">
endif
ifndef RUNTIMECLASS_Windows_Media_Devices_MediaDeviceControl_DEFINED
define RUNTIMECLASS_Windows_Media_Devices_MediaDeviceControl_DEFINED
define RuntimeClass_Windows_Media_Devices_MediaDeviceControl <L"Windows.Media.Devices.MediaDeviceControl">
endif
ifndef RUNTIMECLASS_Windows_Media_Devices_LowLagPhotoSequenceControl_DEFINED
define RUNTIMECLASS_Windows_Media_Devices_LowLagPhotoSequenceControl_DEFINED
define RuntimeClass_Windows_Media_Devices_LowLagPhotoSequenceControl <L"Windows.Media.Devices.LowLagPhotoSequenceControl">
endif
ifndef RUNTIMECLASS_Windows_Media_Devices_LowLagPhotoControl_DEFINED
define RUNTIMECLASS_Windows_Media_Devices_LowLagPhotoControl_DEFINED
define RuntimeClass_Windows_Media_Devices_LowLagPhotoControl <L"Windows.Media.Devices.LowLagPhotoControl">
endif
ifndef RUNTIMECLASS_Windows_Media_Devices_MediaDeviceControlCapabilities_DEFINED
define RUNTIMECLASS_Windows_Media_Devices_MediaDeviceControlCapabilities_DEFINED
define RuntimeClass_Windows_Media_Devices_MediaDeviceControlCapabilities <L"Windows.Media.Devices.MediaDeviceControlCapabilities">
endif

endif
