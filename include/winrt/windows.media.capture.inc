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

ifndef __windows2Emedia2Ecapture_h__
define __windows2Emedia2Ecapture_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc

.namespace Windows
.namespace Media
.namespace Capture

.enum CameraCaptureUIMode {
    CameraCaptureUIMode_PhotoOrVideo	= 0,
    CameraCaptureUIMode_Photo	= 1,
    CameraCaptureUIMode_Video	= 2
    }

.enum CameraCaptureUIPhotoFormat {
    CameraCaptureUIPhotoFormat_Jpeg	= 0,
    CameraCaptureUIPhotoFormat_Png	= 1,
    CameraCaptureUIPhotoFormat_JpegXR	= 2
    }

.enum CameraCaptureUIVideoFormat {
    CameraCaptureUIVideoFormat_Mp4	= 0,
    CameraCaptureUIVideoFormat_Wmv	= 1
    }

.enum CameraCaptureUIMaxVideoResolution {
    CameraCaptureUIMaxVideoResolution_HighestAvailable	= 0,
    CameraCaptureUIMaxVideoResolution_LowDefinition	= 1,
    CameraCaptureUIMaxVideoResolution_StandardDefinition	= 2,
    CameraCaptureUIMaxVideoResolution_HighDefinition	= 3
    }

.enum CameraCaptureUIMaxPhotoResolution {
    CameraCaptureUIMaxPhotoResolution_HighestAvailable	= 0,
    CameraCaptureUIMaxPhotoResolution_VerySmallQvga	= 1,
    CameraCaptureUIMaxPhotoResolution_SmallVga	= 2,
    CameraCaptureUIMaxPhotoResolution_MediumXga = 3,
    CameraCaptureUIMaxPhotoResolution_Large3M	= 4,
    CameraCaptureUIMaxPhotoResolution_VeryLarge5M	= 5
    }

.enum MediaCategory {
    MediaCategory_Other = 0,
    MediaCategory_Communications	= 1
    }

.enum MediaStreamType {
    MediaStreamType_VideoPreview	= 0,
    MediaStreamType_VideoRecord = 1,
    MediaStreamType_Audio	= 2,
    MediaStreamType_Photo	= 3
    }

.enum StreamingCaptureMode {
    StreamingCaptureMode_AudioAndVideo	= 0,
    StreamingCaptureMode_Audio	= 1,
    StreamingCaptureMode_Video	= 2
    }

.enum VideoRotation {
    VideoRotation_None	= 0,
    VideoRotation_Clockwise90Degrees	= 1,
    VideoRotation_Clockwise180Degrees	= 2,
    VideoRotation_Clockwise270Degrees	= 3
    }

.enum PhotoCaptureSource {
    PhotoCaptureSource_Auto	= 0,
    PhotoCaptureSource_VideoPreview	= 1,
    PhotoCaptureSource_Photo	= 2
    }

.enum VideoDeviceCharacteristic {
    VideoDeviceCharacteristic_AllStreamsIndependent	= 0,
    VideoDeviceCharacteristic_PreviewRecordStreamsIdentical	= 1,
    VideoDeviceCharacteristic_PreviewPhotoStreamsIdentical	= 2,
    VideoDeviceCharacteristic_RecordPhotoStreamsIdentical	= 3,
    VideoDeviceCharacteristic_AllStreamsIdentical	= 4
    }

.enum PowerlineFrequency {
    PowerlineFrequency_Disabled = 0,
    PowerlineFrequency_FiftyHertz	= 1,
    PowerlineFrequency_SixtyHertz	= 2
    }

.endn
.endn
.endn

include Windows.Media.inc
include Windows.Media.Devices.inc
include windows.foundation.collections.inc

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CMedia__CCapture__CCapturedPhoto_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CMedia__CCapture__CCapturedPhoto_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CMedia__CCapture__CCapturedPhoto, "fdb0aa78-04e1-56b3-b6fc-f4de79cd41a0")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CMedia__CCapture__CCapturedPhoto : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CMedia__CCapture__CCapturedPhoto_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CMedia__CCapture__CCapturedPhoto_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CMedia__CCapture__CCapturedPhoto, "af5235b1-4778-55e1-b49f-608048ea9bd9")

.comdef __FIAsyncOperation_1_Windows__CMedia__CCapture__CCapturedPhoto : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CMedia__CCapture__CLowLagMediaRecording_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CMedia__CCapture__CLowLagMediaRecording_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CMedia__CCapture__CLowLagMediaRecording, "64a8f80c-e646-52bb-8f4b-2a1d6b0b8219")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CMedia__CCapture__CLowLagMediaRecording : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CMedia__CCapture__CLowLagMediaRecording_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CMedia__CCapture__CLowLagMediaRecording_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CMedia__CCapture__CLowLagMediaRecording, "4febefcc-bec0-5433-a7ba-7603d1edc7b9")

.comdef __FIAsyncOperation_1_Windows__CMedia__CCapture__CLowLagMediaRecording : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CMedia__CCapture__CLowLagPhotoCapture_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CMedia__CCapture__CLowLagPhotoCapture_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CMedia__CCapture__CLowLagPhotoCapture, "6cebb368-4e84-500a-9a5f-7b9a1ade1f44")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CMedia__CCapture__CLowLagPhotoCapture : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CMedia__CCapture__CLowLagPhotoCapture_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CMedia__CCapture__CLowLagPhotoCapture_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CMedia__CCapture__CLowLagPhotoCapture, "af24404b-7e0d-5ffe-bbc8-aaf6ffe208fc")

.comdef __FIAsyncOperation_1_Windows__CMedia__CCapture__CLowLagPhotoCapture : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CMedia__CCapture__CLowLagPhotoSequenceCapture_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CMedia__CCapture__CLowLagPhotoSequenceCapture_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CMedia__CCapture__CLowLagPhotoSequenceCapture, "767e0fdc-9563-572d-84e1-9caab0deb63f")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CMedia__CCapture__CLowLagPhotoSequenceCapture : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CMedia__CCapture__CLowLagPhotoSequenceCapture_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CMedia__CCapture__CLowLagPhotoSequenceCapture_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CMedia__CCapture__CLowLagPhotoSequenceCapture, "ac9f0460-9d14-5af0-b17b-37ea2d76a80d")

.comdef __FIAsyncOperation_1_Windows__CMedia__CCapture__CLowLagPhotoSequenceCapture : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CMedia__CCapture__CLowLagPhotoSequenceCapture_Windows__CMedia__CCapture__CPhotoCapturedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CMedia__CCapture__CLowLagPhotoSequenceCapture_Windows__CMedia__CCapture__CPhotoCapturedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CMedia__CCapture__CLowLagPhotoSequenceCapture_Windows__CMedia__CCapture__CPhotoCapturedEventArgs, "b98aab3a-fe80-5b27-88c3-e77ff585a96b")

.comdef __FITypedEventHandler_2_Windows__CMedia__CCapture__CLowLagPhotoSequenceCapture_Windows__CMedia__CCapture__CPhotoCapturedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

.namespace Windows
.namespace Media
.namespace Capture

ifndef ____x_ABI_CWindows_CMedia_CCapture_CIMediaCaptureFailedEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CCapture_CIMediaCaptureFailedEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IMediaCaptureFailedEventHandler, "2014EFFB-5CD8-4F08-A314-0D360DA59F14")

.comdef IMediaCaptureFailedEventHandler : public IUnknown


    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CCapture_CIRecordLimitationExceededEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CCapture_CIRecordLimitationExceededEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IRecordLimitationExceededEventHandler, "3FAE8F2E-4FE1-4FFD-AABA-E1F1337D4E53")

.comdef IRecordLimitationExceededEventHandler : public IUnknown

    _Invoke		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CCapture_CICameraCaptureUIPhotoCaptureSettings_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CCapture_CICameraCaptureUIPhotoCaptureSettings_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Capture_ICameraCaptureUIPhotoCaptureSettings <L"Windows.Media.Capture.ICameraCaptureUIPhotoCaptureSettings">
DEFINE_IIDX(ICameraCaptureUIPhotoCaptureSettings, "B9F5BE97-3472-46A8-8A9E-04CE42CCC97D")

.comdef ICameraCaptureUIPhotoCaptureSettings : public IInspectable

    get_Format		proc :ptr
    put_Format		proc :Windows::Media::Capture::CameraCaptureUIPhotoFormat
    get_MaxResolution	proc :ptr
    put_MaxResolution	proc :Windows::Media::Capture::CameraCaptureUIMaxPhotoResolution
    get_CroppedSizeInPixels proc :ptr
    put_CroppedSizeInPixels proc :Windows::Foundation::Size
    get_CroppedAspectRatio proc :ptr
    put_CroppedAspectRatio proc :Windows::Foundation::Size
    get_AllowCropping	proc :ptr
    put_AllowCropping	proc :boolean
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CCapture_CICameraCaptureUIVideoCaptureSettings_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CCapture_CICameraCaptureUIVideoCaptureSettings_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Capture_ICameraCaptureUIVideoCaptureSettings <L"Windows.Media.Capture.ICameraCaptureUIVideoCaptureSettings">
DEFINE_IIDX(ICameraCaptureUIVideoCaptureSettings, "64E92D1F-A28D-425A-B84F-E568335FF24E")

.comdef ICameraCaptureUIVideoCaptureSettings : public IInspectable

    get_Format		proc :ptr
    put_Format		proc :Windows::Media::Capture::CameraCaptureUIVideoFormat
    get_MaxResolution	proc :ptr
    put_MaxResolution	proc :Windows::Media::Capture::CameraCaptureUIMaxVideoResolution
    get_MaxDurationInSeconds proc :ptr
    put_MaxDurationInSeconds proc :FLOAT
    get_AllowTrimming	proc :ptr
    put_AllowTrimming	proc :boolean
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CCapture_CICameraCaptureUI_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CCapture_CICameraCaptureUI_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Capture_ICameraCaptureUI <L"Windows.Media.Capture.ICameraCaptureUI">
DEFINE_IIDX(ICameraCaptureUI, "48587540-6F93-4BB4-B8F3-E89E48948C91")

.comdef ICameraCaptureUI : public IInspectable

    get_PhotoSettings	proc :ptr
    get_VideoSettings	proc :ptr
    CaptureFileAsync	proc :Windows::Media::Capture::CameraCaptureUIMode, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CCapture_CICameraOptionsUIStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CCapture_CICameraOptionsUIStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Capture_ICameraOptionsUIStatics <L"Windows.Media.Capture.ICameraOptionsUIStatics">
DEFINE_IIDX(ICameraOptionsUIStatics, "3B0D5E34-3906-4B7D-946C-7BDE844499AE")

.comdef ICameraOptionsUIStatics : public IInspectable

    Show		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CCapture_CIMediaCaptureFailedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CCapture_CIMediaCaptureFailedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Capture_IMediaCaptureFailedEventArgs <L"Windows.Media.Capture.IMediaCaptureFailedEventArgs">
DEFINE_IIDX(IMediaCaptureFailedEventArgs, "80FDE3F4-54C4-42C0-8D19-CEA1A87CA18B")

.comdef IMediaCaptureFailedEventArgs : public IInspectable

    get_Message		proc :ptr
    get_Code		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CCapture_CIMediaCaptureInitializationSettings_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CCapture_CIMediaCaptureInitializationSettings_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Capture_IMediaCaptureInitializationSettings <L"Windows.Media.Capture.IMediaCaptureInitializationSettings">
DEFINE_IIDX(IMediaCaptureInitializationSettings, "9782BA70-EA65-4900-9356-8CA887726884")

.comdef IMediaCaptureInitializationSettings : public IInspectable

    put_AudioDeviceId	proc :HSTRING
    get_AudioDeviceId	proc :ptr
    put_VideoDeviceId	proc :HSTRING
    get_VideoDeviceId	proc :ptr
    put_StreamingCaptureMode proc :Windows::Media::Capture::StreamingCaptureMode
    get_StreamingCaptureMode proc :ptr
    put_PhotoCaptureSource proc :Windows::Media::Capture::PhotoCaptureSource
    get_PhotoCaptureSource proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CCapture_CIMediaCaptureInitializationSettings2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CCapture_CIMediaCaptureInitializationSettings2_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Capture_IMediaCaptureInitializationSettings2 <L"Windows.Media.Capture.IMediaCaptureInitializationSettings2">
DEFINE_IIDX(IMediaCaptureInitializationSettings2, "404E0626-C9DC-43E9-AEE4-E6BF1B57B44C")

.comdef IMediaCaptureInitializationSettings2 : public IInspectable

    put_MediaCategory	proc :Windows::Media::Capture::MediaCategory
    get_MediaCategory	proc :ptr
    put_AudioProcessing proc :Windows::Media::AudioProcessing
    get_AudioProcessing proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CCapture_CIMediaCapture_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CCapture_CIMediaCapture_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Capture_IMediaCapture <L"Windows.Media.Capture.IMediaCapture">
DEFINE_IIDX(IMediaCapture, "C61AFBB4-FB10-4A34-AC18-CA80D9C8E7EE")

.comdef IMediaCapture : public IInspectable

    InitializeAsync	proc :ptr
    InitializeWithSettingsAsync proc :ptr, :ptr
    StartRecordToStorageFileAsync proc :ptr, :ptr, :ptr
    StartRecordToStreamAsync proc :ptr, :ptr, :ptr
    StartRecordToCustomSinkAsync proc :ptr, :ptr, :ptr
    StartRecordToCustomSinkIdAsync proc :ptr, :HSTRING, :ptr, :ptr
    StopRecordAsync	proc :ptr
    CapturePhotoToStorageFileAsync proc :ptr, :ptr, :ptr
    CapturePhotoToStreamAsync proc :ptr, :ptr, :ptr
    AddEffectAsync	proc :Windows::Media::Capture::MediaStreamType, :HSTRING, :ptr, :ptr
    ClearEffectsAsync	proc :Windows::Media::Capture::MediaStreamType, :ptr
    SetEncoderProperty	proc :Windows::Media::Capture::MediaStreamType, :GUID, :ptr
    GetEncoderProperty	proc :Windows::Media::Capture::MediaStreamType, :GUID, :ptr
    add_Failed		proc :ptr, :ptr
    remove_Failed	proc :EventRegistrationToken
    add_RecordLimitationExceeded proc :ptr, :ptr
    remove_RecordLimitationExceeded proc :EventRegistrationToken
    get_MediaCaptureSettings proc :ptr
    get_AudioDeviceController proc :ptr
    get_VideoDeviceController proc :ptr
    SetPreviewMirroring proc :boolean
    GetPreviewMirroring proc :ptr
    SetPreviewRotation	proc :Windows::Media::Capture::VideoRotation
    GetPreviewRotation	proc :ptr
    SetRecordRotation	proc :Windows::Media::Capture::VideoRotation
    GetRecordRotation	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CCapture_CIMediaCapture2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CCapture_CIMediaCapture2_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Capture_IMediaCapture2 <L"Windows.Media.Capture.IMediaCapture2">
DEFINE_IIDX(IMediaCapture2, "9CC68260-7DA1-4043-B652-21B8878DAFF9")

.comdef IMediaCapture2 : public IInspectable

    PrepareLowLagRecordToStorageFileAsync proc :ptr, :ptr, :ptr
    PrepareLowLagRecordToStreamAsync proc :ptr, :ptr, :ptr
    PrepareLowLagRecordToCustomSinkAsync proc :ptr, :ptr, :ptr
    PrepareLowLagRecordToCustomSinkIdAsync proc :ptr, :HSTRING, :ptr, :ptr
    PrepareLowLagPhotoCaptureAsync proc :ptr, :ptr
    PrepareLowLagPhotoSequenceCaptureAsync proc :ptr, :ptr
    SetEncodingPropertiesAsync proc :Windows::Media::Capture::MediaStreamType, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CCapture_CILowLagPhotoCapture_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CCapture_CILowLagPhotoCapture_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Capture_ILowLagPhotoCapture <L"Windows.Media.Capture.ILowLagPhotoCapture">
DEFINE_IIDX(ILowLagPhotoCapture, "A37251B7-6B44-473D-8F24-F703D6C0EC44")

.comdef ILowLagPhotoCapture : public IInspectable

    CaptureAsync	proc :ptr
    FinishAsync		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CCapture_CILowLagMediaRecording_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CCapture_CILowLagMediaRecording_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Capture_ILowLagMediaRecording <L"Windows.Media.Capture.ILowLagMediaRecording">
DEFINE_IIDX(ILowLagMediaRecording, "41C8BAF7-FF3F-49F0-A477-F195E3CE5108")

.comdef ILowLagMediaRecording : public IInspectable

    StartAsync		proc :ptr
    StopAsync		proc :ptr
    FinishAsync		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CCapture_CILowLagPhotoSequenceCapture_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CCapture_CILowLagPhotoSequenceCapture_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Capture_ILowLagPhotoSequenceCapture <L"Windows.Media.Capture.ILowLagPhotoSequenceCapture">
DEFINE_IIDX(ILowLagPhotoSequenceCapture, "7CC346BB-B9A9-4C91-8FFA-287E9C668669")

.comdef ILowLagPhotoSequenceCapture : public IInspectable

    StartAsync		proc :ptr
    StopAsync		proc :ptr
    FinishAsync		proc :ptr
    add_PhotoCaptured	proc :ptr, :ptr
    remove_PhotoCaptured proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CCapture_CIPhotoCapturedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CCapture_CIPhotoCapturedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Capture_IPhotoCapturedEventArgs <L"Windows.Media.Capture.IPhotoCapturedEventArgs">
DEFINE_IIDX(IPhotoCapturedEventArgs, "373BFBC1-984E-4FF0-BF85-1C00AABC5A45")

.comdef IPhotoCapturedEventArgs : public IInspectable

    get_Frame		proc :ptr
    get_Thumbnail	proc :ptr
    get_CaptureTimeOffset proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CCapture_CICapturedPhoto_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CCapture_CICapturedPhoto_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Capture_ICapturedPhoto <L"Windows.Media.Capture.ICapturedPhoto">
DEFINE_IIDX(ICapturedPhoto, "B0CE7E5A-CFCC-4D6C-8AD1-0869208ACA16")

.comdef ICapturedPhoto : public IInspectable

    get_Frame		proc :ptr
    get_Thumbnail	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CCapture_CICapturedFrame_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CCapture_CICapturedFrame_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Capture_ICapturedFrame <L"Windows.Media.Capture.ICapturedFrame">
DEFINE_IIDX(ICapturedFrame, "1DD2DE1F-571B-44D8-8E80-A08A1578766E")

.comdef ICapturedFrame : public IInspectable

    get_Width		proc :ptr
    get_Height		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CCapture_CIMediaCaptureVideoPreview_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CCapture_CIMediaCaptureVideoPreview_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Capture_IMediaCaptureVideoPreview <L"Windows.Media.Capture.IMediaCaptureVideoPreview">
DEFINE_IIDX(IMediaCaptureVideoPreview, "27727073-549E-447F-A20A-4F03C479D8C0")

.comdef IMediaCaptureVideoPreview : public IInspectable

    StartPreviewAsync	proc :ptr
    StartPreviewToCustomSinkAsync proc :ptr, :ptr, :ptr
    StartPreviewToCustomSinkIdAsync proc :ptr, :HSTRING, :ptr, :ptr
    StopPreviewAsync	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CCapture_CIMediaCaptureSettings_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CCapture_CIMediaCaptureSettings_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Capture_IMediaCaptureSettings <L"Windows.Media.Capture.IMediaCaptureSettings">
DEFINE_IIDX(IMediaCaptureSettings, "1D83AAFE-6D45-4477-8DC4-AC5BC01C4091")

.comdef IMediaCaptureSettings : public IInspectable

    get_AudioDeviceId	proc :ptr
    get_VideoDeviceId	proc :ptr
    get_StreamingCaptureMode proc :ptr
    get_PhotoCaptureSource proc :ptr
    get_VideoDeviceCharacteristic proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CCapture_CIMediaCaptureSettings2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CCapture_CIMediaCaptureSettings2_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Capture_IMediaCaptureSettings2 <L"Windows.Media.Capture.IMediaCaptureSettings2">
DEFINE_IIDX(IMediaCaptureSettings2, "6F9E7CFB-FA9F-4B13-9CBE-5AB94F1F3493")

.comdef IMediaCaptureSettings2 : public IInspectable

    get_ConcurrentRecordAndPhotoSupported proc :ptr
    get_ConcurrentRecordAndPhotoSequenceSupported proc :ptr
    get_CameraSoundRequiredForRegion proc :ptr
    get_Horizontal35mmEquivalentFocalLength proc :ptr
    get_PitchOffsetDegrees proc :ptr
    get_Vertical35mmEquivalentFocalLength proc :ptr
    get_MediaCategory	proc :ptr
    get_AudioProcessing proc :ptr
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_Media_Capture_CameraCaptureUIPhotoCaptureSettings_DEFINED
define RUNTIMECLASS_Windows_Media_Capture_CameraCaptureUIPhotoCaptureSettings_DEFINED
define RuntimeClass_Windows_Media_Capture_CameraCaptureUIPhotoCaptureSettings <L"Windows.Media.Capture.CameraCaptureUIPhotoCaptureSettings">
endif
ifndef RUNTIMECLASS_Windows_Media_Capture_CameraCaptureUIVideoCaptureSettings_DEFINED
define RUNTIMECLASS_Windows_Media_Capture_CameraCaptureUIVideoCaptureSettings_DEFINED
define RuntimeClass_Windows_Media_Capture_CameraCaptureUIVideoCaptureSettings <L"Windows.Media.Capture.CameraCaptureUIVideoCaptureSettings">
endif
ifndef RUNTIMECLASS_Windows_Media_Capture_CameraCaptureUI_DEFINED
define RUNTIMECLASS_Windows_Media_Capture_CameraCaptureUI_DEFINED
define RuntimeClass_Windows_Media_Capture_CameraCaptureUI <L"Windows.Media.Capture.CameraCaptureUI">
endif
ifndef RUNTIMECLASS_Windows_Media_Capture_CameraOptionsUI_DEFINED
define RUNTIMECLASS_Windows_Media_Capture_CameraOptionsUI_DEFINED
define RuntimeClass_Windows_Media_Capture_CameraOptionsUI <L"Windows.Media.Capture.CameraOptionsUI">
endif
ifndef RUNTIMECLASS_Windows_Media_Capture_MediaCaptureFailedEventArgs_DEFINED
define RUNTIMECLASS_Windows_Media_Capture_MediaCaptureFailedEventArgs_DEFINED
define RuntimeClass_Windows_Media_Capture_MediaCaptureFailedEventArgs <L"Windows.Media.Capture.MediaCaptureFailedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_Media_Capture_MediaCapture_DEFINED
define RUNTIMECLASS_Windows_Media_Capture_MediaCapture_DEFINED
define RuntimeClass_Windows_Media_Capture_MediaCapture <L"Windows.Media.Capture.MediaCapture">
endif
ifndef RUNTIMECLASS_Windows_Media_Capture_MediaCaptureInitializationSettings_DEFINED
define RUNTIMECLASS_Windows_Media_Capture_MediaCaptureInitializationSettings_DEFINED
define RuntimeClass_Windows_Media_Capture_MediaCaptureInitializationSettings <L"Windows.Media.Capture.MediaCaptureInitializationSettings">
endif
ifndef RUNTIMECLASS_Windows_Media_Capture_MediaCaptureSettings_DEFINED
define RUNTIMECLASS_Windows_Media_Capture_MediaCaptureSettings_DEFINED
define RuntimeClass_Windows_Media_Capture_MediaCaptureSettings <L"Windows.Media.Capture.MediaCaptureSettings">
endif
ifndef RUNTIMECLASS_Windows_Media_Capture_LowLagMediaRecording_DEFINED
define RUNTIMECLASS_Windows_Media_Capture_LowLagMediaRecording_DEFINED
define RuntimeClass_Windows_Media_Capture_LowLagMediaRecording <L"Windows.Media.Capture.LowLagMediaRecording">
endif
ifndef RUNTIMECLASS_Windows_Media_Capture_LowLagPhotoCapture_DEFINED
define RUNTIMECLASS_Windows_Media_Capture_LowLagPhotoCapture_DEFINED
define RuntimeClass_Windows_Media_Capture_LowLagPhotoCapture <L"Windows.Media.Capture.LowLagPhotoCapture">
endif
ifndef RUNTIMECLASS_Windows_Media_Capture_LowLagPhotoSequenceCapture_DEFINED
define RUNTIMECLASS_Windows_Media_Capture_LowLagPhotoSequenceCapture_DEFINED
define RuntimeClass_Windows_Media_Capture_LowLagPhotoSequenceCapture <L"Windows.Media.Capture.LowLagPhotoSequenceCapture">
endif
ifndef RUNTIMECLASS_Windows_Media_Capture_CapturedPhoto_DEFINED
define RUNTIMECLASS_Windows_Media_Capture_CapturedPhoto_DEFINED
define RuntimeClass_Windows_Media_Capture_CapturedPhoto <L"Windows.Media.Capture.CapturedPhoto">
endif
ifndef RUNTIMECLASS_Windows_Media_Capture_PhotoCapturedEventArgs_DEFINED
define RUNTIMECLASS_Windows_Media_Capture_PhotoCapturedEventArgs_DEFINED
define RuntimeClass_Windows_Media_Capture_PhotoCapturedEventArgs <L"Windows.Media.Capture.PhotoCapturedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_Media_Capture_CapturedFrame_DEFINED
define RUNTIMECLASS_Windows_Media_Capture_CapturedFrame_DEFINED
define RuntimeClass_Windows_Media_Capture_CapturedFrame <L"Windows.Media.Capture.CapturedFrame">
endif

endif
