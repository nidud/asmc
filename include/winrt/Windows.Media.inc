ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Emedia_h__
define __windows2Emedia_h__
ifndef __windows2Efoundation_h__
include Windows.Foundation.inc
endif
include Windows.Storage.inc

ifndef ____FIIterator_1_Windows__CMedia__CIMediaMarker_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CMedia__CIMediaMarker_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CMedia__CIMediaMarker, "f464661e-88bc-5cea-93cd-0c123f17d258")

.comdef __FIIterator_1_Windows__CMedia__CIMediaMarker : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CMedia__CIMediaMarker_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CMedia__CIMediaMarker_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CMedia__CIMediaMarker, "a1c0a397-0364-5e4c-9dca-7cd7011bd114")

.comdef __FIIterable_1_Windows__CMedia__CIMediaMarker : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CMedia__CIMediaMarker_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CMedia__CIMediaMarker_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CMedia__CIMediaMarker, "b543562c-02b1-5824-80a8-9854130cdadd")

.comdef __FIVectorView_1_Windows__CMedia__CIMediaMarker : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CMedia__CSystemMediaTransportControls_Windows__CMedia__CSystemMediaTransportControlsButtonPressedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CMedia__CSystemMediaTransportControls_Windows__CMedia__CSystemMediaTransportControlsButtonPressedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CMedia__CSystemMediaTransportControls_Windows__CMedia__CSystemMediaTransportControlsButtonPressedEventArgs, "0557e996-7b23-5bae-aa81-ea0d671143a4")

.comdef __FITypedEventHandler_2_Windows__CMedia__CSystemMediaTransportControls_Windows__CMedia__CSystemMediaTransportControlsButtonPressedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CMedia__CSystemMediaTransportControls_Windows__CMedia__CSystemMediaTransportControlsPropertyChangedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CMedia__CSystemMediaTransportControls_Windows__CMedia__CSystemMediaTransportControlsPropertyChangedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CMedia__CSystemMediaTransportControls_Windows__CMedia__CSystemMediaTransportControlsPropertyChangedEventArgs, "9fd61dad-1746-5fa1-a908-ef7cb4603c85")

.comdef __FITypedEventHandler_2_Windows__CMedia__CSystemMediaTransportControls_Windows__CMedia__CSystemMediaTransportControlsPropertyChangedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

.namespace Windows
.namespace Media

.enum SoundLevel {
    SoundLevel_Muted	= 0,
    SoundLevel_Low	= 1,
    SoundLevel_Full	= 2
    }

.enum MediaPlaybackType {
    MediaPlaybackType_Unknown	= 0,
    MediaPlaybackType_Music	= 1,
    MediaPlaybackType_Video	= 2,
    MediaPlaybackType_Image	= 3
    }

.enum MediaPlaybackStatus {
    MediaPlaybackStatus_Closed	= 0,
    MediaPlaybackStatus_Changing	= 1,
    MediaPlaybackStatus_Stopped = 2,
    MediaPlaybackStatus_Playing = 3,
    MediaPlaybackStatus_Paused	= 4
    }

.enum SystemMediaTransportControlsButton {
    SystemMediaTransportControlsButton_Play	= 0,
    SystemMediaTransportControlsButton_Pause	= 1,
    SystemMediaTransportControlsButton_Stop	= 2,
    SystemMediaTransportControlsButton_Record	= 3,
    SystemMediaTransportControlsButton_FastForward	= 4,
    SystemMediaTransportControlsButton_Rewind	= 5,
    SystemMediaTransportControlsButton_Next	= 6,
    SystemMediaTransportControlsButton_Previous = 7,
    SystemMediaTransportControlsButton_ChannelUp	= 8,
    SystemMediaTransportControlsButton_ChannelDown	= 9
    }

.enum SystemMediaTransportControlsProperty {
    SystemMediaTransportControlsProperty_SoundLevel	= 0
    }

.enum AudioProcessing {
    AudioProcessing_Default	= 0,
    AudioProcessing_Raw = 1
    }

ifndef ____x_ABI_CWindows_CMedia_CIMediaControl_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CIMediaControl_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_IMediaControl <L"Windows.Media.IMediaControl">
DEFINE_IIDX(IMediaControl, "98F1FBE1-7A8D-42CB-B6FE-8FE698264F13")

.comdef IMediaControl : public IInspectable

    add_SoundLevelChanged proc :ptr, :ptr
    remove_SoundLevelChanged proc :EventRegistrationToken
    add_PlayPressed	proc :ptr, :ptr
    remove_PlayPressed	proc :EventRegistrationToken
    add_PausePressed	proc :ptr, :ptr
    remove_PausePressed proc :EventRegistrationToken
    add_StopPressed	proc :ptr, :ptr
    remove_StopPressed	proc :EventRegistrationToken
    add_PlayPauseTogglePressed proc :ptr, :ptr
    remove_PlayPauseTogglePressed proc :EventRegistrationToken
    add_RecordPressed	proc :ptr, :ptr
    remove_RecordPressed proc :EventRegistrationToken
    add_NextTrackPressed proc :ptr, :ptr
    remove_NextTrackPressed proc :EventRegistrationToken
    add_PreviousTrackPressed proc :ptr, :ptr
    remove_PreviousTrackPressed proc :EventRegistrationToken
    add_FastForwardPressed proc :ptr, :ptr
    remove_FastForwardPressed proc :EventRegistrationToken
    add_RewindPressed	proc :ptr, :ptr
    remove_RewindPressed proc :EventRegistrationToken
    add_ChannelUpPressed proc :ptr, :ptr
    remove_ChannelUpPressed proc :EventRegistrationToken
    add_ChannelDownPressed proc :ptr, :ptr
    remove_ChannelDownPressed proc :EventRegistrationToken
    get_SoundLevel	proc :ptr
    put_TrackName	proc :HSTRING
    get_TrackName	proc :ptr
    put_ArtistName	proc :HSTRING
    get_ArtistName	proc :ptr
    put_IsPlaying	proc :boolean
    get_IsPlaying	proc :ptr
    put_AlbumArt	proc :ptr
    get_AlbumArt	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CIMediaMarker_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CIMediaMarker_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_IMediaMarker <L"Windows.Media.IMediaMarker">
DEFINE_IIDX(IMediaMarker, "1803DEF8-DCA5-4B6F-9C20-E3D3C0643625")

.comdef IMediaMarker : public IInspectable

    get_Time		proc :ptr
    get_MediaMarkerType proc :ptr
    get_Text		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CIMediaMarkers_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CIMediaMarkers_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_IMediaMarkers <L"Windows.Media.IMediaMarkers">
DEFINE_IIDX(IMediaMarkers, "AFEAB189-F8DD-466E-AA10-920B52353FDF")

.comdef IMediaMarkers : public IInspectable

    get_Markers		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CIMediaMarkerTypesStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CIMediaMarkerTypesStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_IMediaMarkerTypesStatics <L"Windows.Media.IMediaMarkerTypesStatics">
DEFINE_IIDX(IMediaMarkerTypesStatics, "BB198040-482F-4743-8832-45853821ECE0")

.comdef IMediaMarkerTypesStatics : public IInspectable

    get_Bookmark	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CIMusicDisplayProperties_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CIMusicDisplayProperties_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_IMusicDisplayProperties <L"Windows.Media.IMusicDisplayProperties">
DEFINE_IIDX(IMusicDisplayProperties, "6BBF0C59-D0A0-4D26-92A0-F978E1D18E7B")

.comdef IMusicDisplayProperties : public IInspectable

    get_Title		proc :ptr
    put_Title		proc :HSTRING
    get_AlbumArtist	proc :ptr
    put_AlbumArtist	proc :HSTRING
    get_Artist		proc :ptr
    put_Artist		proc :HSTRING
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CIVideoDisplayProperties_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CIVideoDisplayProperties_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_IVideoDisplayProperties <L"Windows.Media.IVideoDisplayProperties">
DEFINE_IIDX(IVideoDisplayProperties, "5609FDB1-5D2D-4872-8170-45DEE5BC2F5C")

.comdef IVideoDisplayProperties : public IInspectable

    get_Title		proc :ptr
    put_Title		proc :HSTRING
    get_Subtitle	proc :ptr
    put_Subtitle	proc :HSTRING
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CIImageDisplayProperties_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CIImageDisplayProperties_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_IImageDisplayProperties <L"Windows.Media.IImageDisplayProperties">
DEFINE_IIDX(IImageDisplayProperties, "CD0BC7EF-54E7-411F-9933-F0E98B0A96D2")

.comdef IImageDisplayProperties : public IInspectable

    get_Title		proc :ptr
    put_Title		proc :HSTRING
    get_Subtitle	proc :ptr
    put_Subtitle	proc :HSTRING
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CISystemMediaTransportControlsDisplayUpdater_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CISystemMediaTransportControlsDisplayUpdater_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_ISystemMediaTransportControlsDisplayUpdater <L"Windows.Media.ISystemMediaTransportControlsDisplayUpdater">
DEFINE_IIDX(ISystemMediaTransportControlsDisplayUpdater, "8ABBC53E-FA55-4ECF-AD8E-C984E5DD1550")

.comdef ISystemMediaTransportControlsDisplayUpdater : public IInspectable

    get_Type		proc :ptr
    put_Type		proc :Windows::Media::MediaPlaybackType
    get_AppMediaId	proc :ptr
    put_AppMediaId	proc :HSTRING
    get_Thumbnail	proc :ptr
    put_Thumbnail	proc :ptr
    get_MusicProperties proc :ptr
    get_VideoProperties proc :ptr
    get_ImageProperties proc :ptr
    CopyFromFileAsync	proc :Windows::Media::MediaPlaybackType, :ptr, :ptr
    ClearAll		proc
    Update		proc
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CISystemMediaTransportControlsButtonPressedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CISystemMediaTransportControlsButtonPressedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_ISystemMediaTransportControlsButtonPressedEventArgs <L"Windows.Media.ISystemMediaTransportControlsButtonPressedEventArgs">
DEFINE_IIDX(ISystemMediaTransportControlsButtonPressedEventArgs, "B7F47116-A56F-4DC8-9E11-92031F4A87C2")

.comdef ISystemMediaTransportControlsButtonPressedEventArgs : public IInspectable

    get_Button		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CISystemMediaTransportControlsPropertyChangedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CISystemMediaTransportControlsPropertyChangedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_ISystemMediaTransportControlsPropertyChangedEventArgs <L"Windows.Media.ISystemMediaTransportControlsPropertyChangedEventArgs">
DEFINE_IIDX(ISystemMediaTransportControlsPropertyChangedEventArgs, "D0CA0936-339B-4CB3-8EEB-737607F56E08")

.comdef ISystemMediaTransportControlsPropertyChangedEventArgs : public IInspectable

    get_Property	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CISystemMediaTransportControls_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CISystemMediaTransportControls_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_ISystemMediaTransportControls <L"Windows.Media.ISystemMediaTransportControls">
DEFINE_IIDX(ISystemMediaTransportControls, "99FA3FF4-1742-42A6-902E-087D41F965EC")

.comdef ISystemMediaTransportControls : public IInspectable

    get_PlaybackStatus	proc :ptr
    put_PlaybackStatus	proc :Windows::Media::MediaPlaybackStatus
    get_DisplayUpdater	proc :ptr
    get_SoundLevel	proc :ptr
    get_IsEnabled	proc :ptr
    put_IsEnabled	proc :boolean
    get_IsPlayEnabled	proc :ptr
    put_IsPlayEnabled	proc :boolean
    get_IsStopEnabled	proc :ptr
    put_IsStopEnabled	proc :boolean
    get_IsPauseEnabled	proc :ptr
    put_IsPauseEnabled	proc :boolean
    get_IsRecordEnabled proc :ptr
    put_IsRecordEnabled proc :boolean
    get_IsFastForwardEnabled proc :ptr
    put_IsFastForwardEnabled proc :boolean
    get_IsRewindEnabled proc :ptr
    put_IsRewindEnabled proc :boolean
    get_IsPreviousEnabled proc :ptr
    put_IsPreviousEnabled proc :boolean
    get_IsNextEnabled	proc :ptr
    put_IsNextEnabled	proc :boolean
    get_IsChannelUpEnabled proc :ptr
    put_IsChannelUpEnabled proc :boolean
    get_IsChannelDownEnabled proc :ptr
    put_IsChannelDownEnabled proc :boolean
    add_ButtonPressed	proc :ptr, :ptr
    remove_ButtonPressed proc :EventRegistrationToken
    add_PropertyChanged proc :ptr, :ptr
    remove_PropertyChanged proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CISystemMediaTransportControlsStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CISystemMediaTransportControlsStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_ISystemMediaTransportControlsStatics <L"Windows.Media.ISystemMediaTransportControlsStatics">
DEFINE_IIDX(ISystemMediaTransportControlsStatics, "43BA380A-ECA4-4832-91AB-D415FAE484C6")

.comdef ISystemMediaTransportControlsStatics : public IInspectable

    GetForCurrentView	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CIMediaExtension_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CIMediaExtension_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_IMediaExtension <L"Windows.Media.IMediaExtension">
DEFINE_IIDX(IMediaExtension, "07915118-45DF-442B-8A3F-F7826A6370AB")

.comdef IMediaExtension : public IInspectable

    SetProperties	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CIMediaExtensionManager_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CIMediaExtensionManager_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_IMediaExtensionManager <L"Windows.Media.IMediaExtensionManager">
DEFINE_IIDX(IMediaExtensionManager, "4A25EAF5-242D-4DFB-97F4-69B7C42576FF")

.comdef IMediaExtensionManager : public IInspectable

    RegisterSchemeHandler proc :HSTRING, :HSTRING
    RegisterSchemeHandlerWithSettings proc :HSTRING, :HSTRING, :ptr
    RegisterByteStreamHandler proc :HSTRING, :HSTRING, :HSTRING
    RegisterByteStreamHandlerWithSettings proc :HSTRING, :HSTRING, :HSTRING, :ptr
    RegisterAudioDecoder proc :HSTRING, :GUID, :GUID
    RegisterAudioDecoderWithSettings proc :HSTRING, :GUID, :GUID, :ptr
    RegisterAudioEncoder proc :HSTRING, :GUID, :GUID
    RegisterAudioEncoderWithSettings proc :HSTRING, :GUID, :GUID, :ptr
    RegisterVideoDecoder proc :HSTRING, :GUID, :GUID
    RegisterVideoDecoderWithSettings proc :HSTRING, :GUID, :GUID, :ptr
    RegisterVideoEncoder proc :HSTRING, :GUID, :GUID
    RegisterVideoEncoderWithSettings proc :HSTRING, :GUID, :GUID, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CIVideoEffectsStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CIVideoEffectsStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_IVideoEffectsStatics <L"Windows.Media.IVideoEffectsStatics">
DEFINE_IIDX(IVideoEffectsStatics, "1FCDA5E8-BAF1-4521-980C-3BCEBB44CF38")

.comdef IVideoEffectsStatics : public IInspectable

    get_VideoStabilization proc :ptr
   .ends

endif

.endn
.endn

ifndef RUNTIMECLASS_Windows_Media_MediaControl_DEFINED
define RUNTIMECLASS_Windows_Media_MediaControl_DEFINED
define RuntimeClass_Windows_Media_MediaControl <L"Windows.Media.MediaControl">
endif
ifndef RUNTIMECLASS_Windows_Media_MediaMarkerTypes_DEFINED
define RUNTIMECLASS_Windows_Media_MediaMarkerTypes_DEFINED
define RuntimeClass_Windows_Media_MediaMarkerTypes <L"Windows.Media.MediaMarkerTypes">
endif
ifndef RUNTIMECLASS_Windows_Media_MusicDisplayProperties_DEFINED
define RUNTIMECLASS_Windows_Media_MusicDisplayProperties_DEFINED
define RuntimeClass_Windows_Media_MusicDisplayProperties <L"Windows.Media.MusicDisplayProperties">
endif
ifndef RUNTIMECLASS_Windows_Media_VideoDisplayProperties_DEFINED
define RUNTIMECLASS_Windows_Media_VideoDisplayProperties_DEFINED
define RuntimeClass_Windows_Media_VideoDisplayProperties <L"Windows.Media.VideoDisplayProperties">
endif
ifndef RUNTIMECLASS_Windows_Media_ImageDisplayProperties_DEFINED
define RUNTIMECLASS_Windows_Media_ImageDisplayProperties_DEFINED
define RuntimeClass_Windows_Media_ImageDisplayProperties <L"Windows.Media.ImageDisplayProperties">
endif
ifndef RUNTIMECLASS_Windows_Media_SystemMediaTransportControlsDisplayUpdater_DEFINED
define RUNTIMECLASS_Windows_Media_SystemMediaTransportControlsDisplayUpdater_DEFINED
define RuntimeClass_Windows_Media_SystemMediaTransportControlsDisplayUpdater <L"Windows.Media.SystemMediaTransportControlsDisplayUpdater">
endif
ifndef RUNTIMECLASS_Windows_Media_SystemMediaTransportControlsButtonPressedEventArgs_DEFINED
define RUNTIMECLASS_Windows_Media_SystemMediaTransportControlsButtonPressedEventArgs_DEFINED
define RuntimeClass_Windows_Media_SystemMediaTransportControlsButtonPressedEventArgs <L"Windows.Media.SystemMediaTransportControlsButtonPressedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_Media_SystemMediaTransportControlsPropertyChangedEventArgs_DEFINED
define RUNTIMECLASS_Windows_Media_SystemMediaTransportControlsPropertyChangedEventArgs_DEFINED
define RuntimeClass_Windows_Media_SystemMediaTransportControlsPropertyChangedEventArgs <L"Windows.Media.SystemMediaTransportControlsPropertyChangedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_Media_SystemMediaTransportControls_DEFINED
define RUNTIMECLASS_Windows_Media_SystemMediaTransportControls_DEFINED
define RuntimeClass_Windows_Media_SystemMediaTransportControls <L"Windows.Media.SystemMediaTransportControls">
endif
ifndef RUNTIMECLASS_Windows_Media_MediaExtensionManager_DEFINED
define RUNTIMECLASS_Windows_Media_MediaExtensionManager_DEFINED
define RuntimeClass_Windows_Media_MediaExtensionManager <L"Windows.Media.MediaExtensionManager">
endif
ifndef RUNTIMECLASS_Windows_Media_VideoEffects_DEFINED
define RUNTIMECLASS_Windows_Media_VideoEffects_DEFINED
define RuntimeClass_Windows_Media_VideoEffects <L"Windows.Media.VideoEffects">
endif

endif
