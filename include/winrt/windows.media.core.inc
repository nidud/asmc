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

ifndef __windows2Emedia2Ecore_h__
define __windows2Emedia2Ecore_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include Windows.Media.MediaProperties.inc
include Windows.Media.Protection.inc
include windows.foundation.collections.inc

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CMedia__CCore__CMediaStreamSample_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CMedia__CCore__CMediaStreamSample_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CMedia__CCore__CMediaStreamSample, "df7aacc9-a86c-5c7d-bf98-cc371c97c67b")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CMedia__CCore__CMediaStreamSample : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CMedia__CCore__CMediaStreamSample_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CMedia__CCore__CMediaStreamSample_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CMedia__CCore__CMediaStreamSample, "3cdc5e86-4ada-5ef7-967a-e137a4621907")

.comdef __FIAsyncOperation_1_Windows__CMedia__CCore__CMediaStreamSample : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CMedia__CCore__CMediaStreamSample_IInspectable_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CMedia__CCore__CMediaStreamSample_IInspectable_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CMedia__CCore__CMediaStreamSample_IInspectable, "d4dc5ef1-c1cb-5c32-803d-f2f9a7ad9916")

.comdef __FITypedEventHandler_2_Windows__CMedia__CCore__CMediaStreamSample_IInspectable : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CMedia__CCore__CMediaStreamSource_IInspectable_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CMedia__CCore__CMediaStreamSource_IInspectable_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CMedia__CCore__CMediaStreamSource_IInspectable, "6fd6ded7-421b-5ef5-8bf5-edea45401665")

.comdef __FITypedEventHandler_2_Windows__CMedia__CCore__CMediaStreamSource_IInspectable : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CMedia__CCore__CMediaStreamSource_Windows__CMedia__CCore__CMediaStreamSourceClosedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CMedia__CCore__CMediaStreamSource_Windows__CMedia__CCore__CMediaStreamSourceClosedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CMedia__CCore__CMediaStreamSource_Windows__CMedia__CCore__CMediaStreamSourceClosedEventArgs, "238cc251-d0b8-5a34-81d4-0dd1f936a20d")

.comdef __FITypedEventHandler_2_Windows__CMedia__CCore__CMediaStreamSource_Windows__CMedia__CCore__CMediaStreamSourceClosedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CMedia__CCore__CMediaStreamSource_Windows__CMedia__CCore__CMediaStreamSourceSampleRequestedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CMedia__CCore__CMediaStreamSource_Windows__CMedia__CCore__CMediaStreamSourceSampleRequestedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CMedia__CCore__CMediaStreamSource_Windows__CMedia__CCore__CMediaStreamSourceSampleRequestedEventArgs, "4f1a3ae3-b8b7-5689-901d-b0b623f5a172")

.comdef __FITypedEventHandler_2_Windows__CMedia__CCore__CMediaStreamSource_Windows__CMedia__CCore__CMediaStreamSourceSampleRequestedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CMedia__CCore__CMediaStreamSource_Windows__CMedia__CCore__CMediaStreamSourceStartingEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CMedia__CCore__CMediaStreamSource_Windows__CMedia__CCore__CMediaStreamSourceStartingEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CMedia__CCore__CMediaStreamSource_Windows__CMedia__CCore__CMediaStreamSourceStartingEventArgs, "a93d5846-c660-586e-b6b5-a52fb81f9240")

.comdef __FITypedEventHandler_2_Windows__CMedia__CCore__CMediaStreamSource_Windows__CMedia__CCore__CMediaStreamSourceStartingEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CMedia__CCore__CMediaStreamSource_Windows__CMedia__CCore__CMediaStreamSourceSwitchStreamsRequestedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CMedia__CCore__CMediaStreamSource_Windows__CMedia__CCore__CMediaStreamSourceSwitchStreamsRequestedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CMedia__CCore__CMediaStreamSource_Windows__CMedia__CCore__CMediaStreamSourceSwitchStreamsRequestedEventArgs, "452b2e4a-5511-5b3c-8a8e-ee659576a4c1")

.comdef __FITypedEventHandler_2_Windows__CMedia__CCore__CMediaStreamSource_Windows__CMedia__CCore__CMediaStreamSourceSwitchStreamsRequestedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

.namespace Windows
.namespace Media
.namespace Core

define InterfaceName_Windows_Media_Core_IMediaStreamDescriptor <L"Windows.Media.Core.IMediaStreamDescriptor">

.enum MediaStreamSourceClosedReason {
    MediaStreamSourceClosedReason_Done = 0,
    MediaStreamSourceClosedReason_UnknownError = 1,
    MediaStreamSourceClosedReason_AppReportedError = 2,
    MediaStreamSourceClosedReason_UnsupportedProtectionSystem = 3,
    MediaStreamSourceClosedReason_ProtectionSystemFailure = 4,
    MediaStreamSourceClosedReason_UnsupportedEncodingFormat = 5,
    MediaStreamSourceClosedReason_MissingSampleRequestedEventHandler = 6
    }

.enum MediaStreamSourceErrorStatus {
    MediaStreamSourceErrorStatus_Other = 0,
    MediaStreamSourceErrorStatus_OutOfMemory = 1,
    MediaStreamSourceErrorStatus_FailedToOpenFile = 2,
    MediaStreamSourceErrorStatus_FailedToConnectToServer = 3,
    MediaStreamSourceErrorStatus_ConnectionToServerLost = 4,
    MediaStreamSourceErrorStatus_UnspecifiedNetworkError = 5,
    MediaStreamSourceErrorStatus_DecodeError = 6,
    MediaStreamSourceErrorStatus_UnsupportedMediaFormat = 7
    }

ifndef ____x_ABI_CWindows_CMedia_CCore_CIMediaStreamDescriptor_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CCore_CIMediaStreamDescriptor_INTERFACE_DEFINED__
DEFINE_IIDX(IMediaStreamDescriptor, "80F16E6E-92F7-451E-97D2-AFD80742DA70")

.comdef IMediaStreamDescriptor : public IInspectable

    get_IsSelected	proc :ptr
    put_Name		proc :HSTRING
    get_Name		proc :ptr
    put_Language	proc :HSTRING
    get_Language	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CCore_CIAudioStreamDescriptor_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CCore_CIAudioStreamDescriptor_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Core_IAudioStreamDescriptor <L"Windows.Media.Core.IAudioStreamDescriptor">
DEFINE_IIDX(IAudioStreamDescriptor, "1E3692E4-4027-4847-A70B-DF1D9A2A7B04")

.comdef IAudioStreamDescriptor : public IInspectable

    get_EncodingProperties proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CCore_CIAudioStreamDescriptorFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CCore_CIAudioStreamDescriptorFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Core_IAudioStreamDescriptorFactory <L"Windows.Media.Core.IAudioStreamDescriptorFactory">
DEFINE_IIDX(IAudioStreamDescriptorFactory, "4A86CE9E-4CB1-4380-8E0C-83504B7F5BF3")

.comdef IAudioStreamDescriptorFactory : public IInspectable

    Create		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CCore_CIVideoStreamDescriptor_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CCore_CIVideoStreamDescriptor_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Core_IVideoStreamDescriptor <L"Windows.Media.Core.IVideoStreamDescriptor">
DEFINE_IIDX(IVideoStreamDescriptor, "12EE0D55-9C2B-4440-8057-2C7A90F0CBEC")

.comdef IVideoStreamDescriptor : public IInspectable

    get_EncodingProperties proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CCore_CIVideoStreamDescriptorFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CCore_CIVideoStreamDescriptorFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Core_IVideoStreamDescriptorFactory <L"Windows.Media.Core.IVideoStreamDescriptorFactory">
DEFINE_IIDX(IVideoStreamDescriptorFactory, "494EF6D1-BB75-43D2-9E5E-7B79A3AFCED4")

.comdef IVideoStreamDescriptorFactory : public IInspectable

    Create		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CCore_CIMediaSource_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CCore_CIMediaSource_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Core_IMediaSource <L"Windows.Media.Core.IMediaSource">
DEFINE_IIDX(IMediaSource, "E7BFB599-A09D-4C21-BCDF-20AF4F86B3D9")

.comdef IMediaSource : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CCore_CIMediaStreamSource_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CCore_CIMediaStreamSource_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Core_IMediaStreamSource <L"Windows.Media.Core.IMediaStreamSource">
DEFINE_IIDX(IMediaStreamSource, "3712D543-45EB-4138-AA62-C01E26F3843F")

.comdef IMediaStreamSource : public IInspectable

    add_Closed		proc :ptr, :ptr
    remove_Closed	proc :EventRegistrationToken
    add_Starting	proc :ptr, :ptr
    remove_Starting	proc :EventRegistrationToken
    add_Paused		proc :ptr, :ptr
    remove_Paused	proc :EventRegistrationToken
    add_SampleRequested proc :ptr, :ptr
    remove_SampleRequested proc :EventRegistrationToken
    add_SwitchStreamsRequested proc :ptr, :ptr
    remove_SwitchStreamsRequested proc :EventRegistrationToken
    NotifyError		proc :Windows::Media::Core::MediaStreamSourceErrorStatus
    AddStreamDescriptor proc :ptr
    put_MediaProtectionManager proc :ptr
    get_MediaProtectionManager proc :ptr
    put_Duration	proc :Windows::Foundation::TimeSpan
    get_Duration	proc :ptr
    put_CanSeek		proc :boolean
    get_CanSeek		proc :ptr
    put_BufferTime	proc :Windows::Foundation::TimeSpan
    get_BufferTime	proc :ptr
    SetBufferedRange	proc :Windows::Foundation::TimeSpan, :Windows::Foundation::TimeSpan
    get_MusicProperties proc :ptr
    get_VideoProperties proc :ptr
    put_Thumbnail	proc :ptr
    get_Thumbnail	proc :ptr
    AddProtectionKey	proc :ptr, :UINT32, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CCore_CIMediaStreamSourceFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CCore_CIMediaStreamSourceFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Core_IMediaStreamSourceFactory <L"Windows.Media.Core.IMediaStreamSourceFactory">
DEFINE_IIDX(IMediaStreamSourceFactory, "EF77E0D9-D158-4B7A-863F-203342FBFD41")

.comdef IMediaStreamSourceFactory : public IInspectable

    CreateFromDescriptor proc :ptr, :ptr
    CreateFromDescriptors proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CCore_CIMediaStreamSample_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CCore_CIMediaStreamSample_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Core_IMediaStreamSample <L"Windows.Media.Core.IMediaStreamSample">
DEFINE_IIDX(IMediaStreamSample, "5C8DB627-4B80-4361-9837-6CB7481AD9D6")

.comdef IMediaStreamSample : public IInspectable

    add_Processed	proc :ptr, :ptr
    remove_Processed	proc :EventRegistrationToken
    get_Buffer		proc :ptr
    get_Timestamp	proc :ptr
    get_ExtendedProperties proc :ptr
    get_Protection	proc :ptr
    put_DecodeTimestamp proc :Windows::Foundation::TimeSpan
    get_DecodeTimestamp proc :ptr
    put_Duration	proc :Windows::Foundation::TimeSpan
    get_Duration	proc :ptr
    put_KeyFrame	proc :boolean
    get_KeyFrame	proc :ptr
    put_Discontinuous	proc :boolean
    get_Discontinuous	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CCore_CIMediaStreamSampleStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CCore_CIMediaStreamSampleStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Core_IMediaStreamSampleStatics <L"Windows.Media.Core.IMediaStreamSampleStatics">
DEFINE_IIDX(IMediaStreamSampleStatics, "DFDF218F-A6CF-4579-BE41-73DD941AD972")

.comdef IMediaStreamSampleStatics : public IInspectable

    CreateFromBuffer	proc :ptr, :Windows::Foundation::TimeSpan, :ptr
    CreateFromStreamAsync proc :ptr, :UINT32, :Windows::Foundation::TimeSpan, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CCore_CIMediaStreamSampleProtectionProperties_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CCore_CIMediaStreamSampleProtectionProperties_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Core_IMediaStreamSampleProtectionProperties <L"Windows.Media.Core.IMediaStreamSampleProtectionProperties">
DEFINE_IIDX(IMediaStreamSampleProtectionProperties, "4EB88292-ECDF-493E-841D-DD4ADD7CACA2")

.comdef IMediaStreamSampleProtectionProperties : public IInspectable

    SetKeyIdentifier	proc :UINT32, :ptr
    GetKeyIdentifier	proc :ptr, :ptr
    SetInitializationVector proc :UINT32, :ptr
    GetInitializationVector proc :ptr, :ptr
    SetSubSampleMapping proc :UINT32, :ptr
    GetSubSampleMapping proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CCore_CIMediaStreamSourceClosedRequest_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CCore_CIMediaStreamSourceClosedRequest_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Core_IMediaStreamSourceClosedRequest <L"Windows.Media.Core.IMediaStreamSourceClosedRequest">
DEFINE_IIDX(IMediaStreamSourceClosedRequest, "907C00E9-18A3-4951-887A-2C1EEBD5C69E")

.comdef IMediaStreamSourceClosedRequest : public IInspectable

    get_Reason		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CCore_CIMediaStreamSourceClosedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CCore_CIMediaStreamSourceClosedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Core_IMediaStreamSourceClosedEventArgs <L"Windows.Media.Core.IMediaStreamSourceClosedEventArgs">
DEFINE_IIDX(IMediaStreamSourceClosedEventArgs, "CD8C7EB2-4816-4E24-88F0-491EF7386406")

.comdef IMediaStreamSourceClosedEventArgs : public IInspectable

    get_Request		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CCore_CIMediaStreamSourceStartingRequestDeferral_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CCore_CIMediaStreamSourceStartingRequestDeferral_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Core_IMediaStreamSourceStartingRequestDeferral <L"Windows.Media.Core.IMediaStreamSourceStartingRequestDeferral">
DEFINE_IIDX(IMediaStreamSourceStartingRequestDeferral, "3F1356A5-6340-4DC4-9910-068ED9F598F8")

.comdef IMediaStreamSourceStartingRequestDeferral : public IInspectable

    Complete		proc
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CCore_CIMediaStreamSourceStartingRequest_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CCore_CIMediaStreamSourceStartingRequest_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Core_IMediaStreamSourceStartingRequest <L"Windows.Media.Core.IMediaStreamSourceStartingRequest">
DEFINE_IIDX(IMediaStreamSourceStartingRequest, "2A9093E4-35C4-4B1B-A791-0D99DB56DD1D")

.comdef IMediaStreamSourceStartingRequest : public IInspectable

    get_StartPosition	proc :ptr
    GetDeferral		proc :ptr
    SetActualStartPosition proc :Windows::Foundation::TimeSpan
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CCore_CIMediaStreamSourceStartingEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CCore_CIMediaStreamSourceStartingEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Core_IMediaStreamSourceStartingEventArgs <L"Windows.Media.Core.IMediaStreamSourceStartingEventArgs">
DEFINE_IIDX(IMediaStreamSourceStartingEventArgs, "F41468F2-C274-4940-A5BB-28A572452FA7")

.comdef IMediaStreamSourceStartingEventArgs : public IInspectable

    get_Request		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CCore_CIMediaStreamSourceSampleRequestDeferral_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CCore_CIMediaStreamSourceSampleRequestDeferral_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Core_IMediaStreamSourceSampleRequestDeferral <L"Windows.Media.Core.IMediaStreamSourceSampleRequestDeferral">
DEFINE_IIDX(IMediaStreamSourceSampleRequestDeferral, "7895CC02-F982-43C8-9D16-C62D999319BE")

.comdef IMediaStreamSourceSampleRequestDeferral : public IInspectable

    Complete		proc
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CCore_CIMediaStreamSourceSampleRequest_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CCore_CIMediaStreamSourceSampleRequest_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Core_IMediaStreamSourceSampleRequest <L"Windows.Media.Core.IMediaStreamSourceSampleRequest">
DEFINE_IIDX(IMediaStreamSourceSampleRequest, "4DB341A9-3501-4D9B-83F9-8F235C822532")

.comdef IMediaStreamSourceSampleRequest : public IInspectable

    get_StreamDescriptor proc :ptr
    GetDeferral		proc :ptr
    put_Sample		proc :ptr
    get_Sample		proc :ptr
    ReportSampleProgress proc :UINT32
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CCore_CIMediaStreamSourceSampleRequestedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CCore_CIMediaStreamSourceSampleRequestedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Core_IMediaStreamSourceSampleRequestedEventArgs <L"Windows.Media.Core.IMediaStreamSourceSampleRequestedEventArgs">
DEFINE_IIDX(IMediaStreamSourceSampleRequestedEventArgs, "10F9BB9E-71C5-492F-847F-0DA1F35E81F8")

.comdef IMediaStreamSourceSampleRequestedEventArgs : public IInspectable

    get_Request		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CCore_CIMediaStreamSourceSwitchStreamsRequestDeferral_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CCore_CIMediaStreamSourceSwitchStreamsRequestDeferral_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Core_IMediaStreamSourceSwitchStreamsRequestDeferral <L"Windows.Media.Core.IMediaStreamSourceSwitchStreamsRequestDeferral">
DEFINE_IIDX(IMediaStreamSourceSwitchStreamsRequestDeferral, "BEE3D835-A505-4F9A-B943-2B8CB1B4BBD9")

.comdef IMediaStreamSourceSwitchStreamsRequestDeferral : public IInspectable

    Complete		proc
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CCore_CIMediaStreamSourceSwitchStreamsRequest_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CCore_CIMediaStreamSourceSwitchStreamsRequest_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Core_IMediaStreamSourceSwitchStreamsRequest <L"Windows.Media.Core.IMediaStreamSourceSwitchStreamsRequest">
DEFINE_IIDX(IMediaStreamSourceSwitchStreamsRequest, "41B8808E-38A9-4EC3-9BA0-B69B85501E90")

.comdef IMediaStreamSourceSwitchStreamsRequest : public IInspectable

    get_OldStreamDescriptor proc :ptr
    get_NewStreamDescriptor proc :ptr
    GetDeferral		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CCore_CIMediaStreamSourceSwitchStreamsRequestedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CCore_CIMediaStreamSourceSwitchStreamsRequestedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Core_IMediaStreamSourceSwitchStreamsRequestedEventArgs <L"Windows.Media.Core.IMediaStreamSourceSwitchStreamsRequestedEventArgs">
DEFINE_IIDX(IMediaStreamSourceSwitchStreamsRequestedEventArgs, "42202B72-6EA1-4677-981E-350A0DA412AA")

.comdef IMediaStreamSourceSwitchStreamsRequestedEventArgs : public IInspectable

    get_Request		proc :ptr
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_Media_Core_AudioStreamDescriptor_DEFINED
define RUNTIMECLASS_Windows_Media_Core_AudioStreamDescriptor_DEFINED
define RuntimeClass_Windows_Media_Core_AudioStreamDescriptor <L"Windows.Media.Core.AudioStreamDescriptor">
endif
ifndef RUNTIMECLASS_Windows_Media_Core_VideoStreamDescriptor_DEFINED
define RUNTIMECLASS_Windows_Media_Core_VideoStreamDescriptor_DEFINED
define RuntimeClass_Windows_Media_Core_VideoStreamDescriptor <L"Windows.Media.Core.VideoStreamDescriptor">
endif
ifndef RUNTIMECLASS_Windows_Media_Core_MediaStreamSource_DEFINED
define RUNTIMECLASS_Windows_Media_Core_MediaStreamSource_DEFINED
define RuntimeClass_Windows_Media_Core_MediaStreamSource <L"Windows.Media.Core.MediaStreamSource">
endif
ifndef RUNTIMECLASS_Windows_Media_Core_MediaStreamSourceClosedEventArgs_DEFINED
define RUNTIMECLASS_Windows_Media_Core_MediaStreamSourceClosedEventArgs_DEFINED
define RuntimeClass_Windows_Media_Core_MediaStreamSourceClosedEventArgs <L"Windows.Media.Core.MediaStreamSourceClosedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_Media_Core_MediaStreamSourceStartingEventArgs_DEFINED
define RUNTIMECLASS_Windows_Media_Core_MediaStreamSourceStartingEventArgs_DEFINED
define RuntimeClass_Windows_Media_Core_MediaStreamSourceStartingEventArgs <L"Windows.Media.Core.MediaStreamSourceStartingEventArgs">
endif
ifndef RUNTIMECLASS_Windows_Media_Core_MediaStreamSourceSampleRequestedEventArgs_DEFINED
define RUNTIMECLASS_Windows_Media_Core_MediaStreamSourceSampleRequestedEventArgs_DEFINED
define RuntimeClass_Windows_Media_Core_MediaStreamSourceSampleRequestedEventArgs <L"Windows.Media.Core.MediaStreamSourceSampleRequestedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_Media_Core_MediaStreamSourceSwitchStreamsRequestedEventArgs_DEFINED
define RUNTIMECLASS_Windows_Media_Core_MediaStreamSourceSwitchStreamsRequestedEventArgs_DEFINED
define RuntimeClass_Windows_Media_Core_MediaStreamSourceSwitchStreamsRequestedEventArgs <L"Windows.Media.Core.MediaStreamSourceSwitchStreamsRequestedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_Media_Core_MediaStreamSamplePropertySet_DEFINED
define RUNTIMECLASS_Windows_Media_Core_MediaStreamSamplePropertySet_DEFINED
define RuntimeClass_Windows_Media_Core_MediaStreamSamplePropertySet <L"Windows.Media.Core.MediaStreamSamplePropertySet">
endif
ifndef RUNTIMECLASS_Windows_Media_Core_MediaStreamSample_DEFINED
define RUNTIMECLASS_Windows_Media_Core_MediaStreamSample_DEFINED
define RuntimeClass_Windows_Media_Core_MediaStreamSample <L"Windows.Media.Core.MediaStreamSample">
endif
ifndef RUNTIMECLASS_Windows_Media_Core_MediaStreamSampleProtectionProperties_DEFINED
define RUNTIMECLASS_Windows_Media_Core_MediaStreamSampleProtectionProperties_DEFINED
define RuntimeClass_Windows_Media_Core_MediaStreamSampleProtectionProperties <L"Windows.Media.Core.MediaStreamSampleProtectionProperties">
endif
ifndef RUNTIMECLASS_Windows_Media_Core_MediaStreamSourceClosedRequest_DEFINED
define RUNTIMECLASS_Windows_Media_Core_MediaStreamSourceClosedRequest_DEFINED
define RuntimeClass_Windows_Media_Core_MediaStreamSourceClosedRequest <L"Windows.Media.Core.MediaStreamSourceClosedRequest">
endif
ifndef RUNTIMECLASS_Windows_Media_Core_MediaStreamSourceStartingRequestDeferral_DEFINED
define RUNTIMECLASS_Windows_Media_Core_MediaStreamSourceStartingRequestDeferral_DEFINED
define RuntimeClass_Windows_Media_Core_MediaStreamSourceStartingRequestDeferral <L"Windows.Media.Core.MediaStreamSourceStartingRequestDeferral">
endif
ifndef RUNTIMECLASS_Windows_Media_Core_MediaStreamSourceStartingRequest_DEFINED
define RUNTIMECLASS_Windows_Media_Core_MediaStreamSourceStartingRequest_DEFINED
define RuntimeClass_Windows_Media_Core_MediaStreamSourceStartingRequest <L"Windows.Media.Core.MediaStreamSourceStartingRequest">
endif
ifndef RUNTIMECLASS_Windows_Media_Core_MediaStreamSourceSampleRequestDeferral_DEFINED
define RUNTIMECLASS_Windows_Media_Core_MediaStreamSourceSampleRequestDeferral_DEFINED
define RuntimeClass_Windows_Media_Core_MediaStreamSourceSampleRequestDeferral <L"Windows.Media.Core.MediaStreamSourceSampleRequestDeferral">
endif
ifndef RUNTIMECLASS_Windows_Media_Core_MediaStreamSourceSampleRequest_DEFINED
define RUNTIMECLASS_Windows_Media_Core_MediaStreamSourceSampleRequest_DEFINED
define RuntimeClass_Windows_Media_Core_MediaStreamSourceSampleRequest <L"Windows.Media.Core.MediaStreamSourceSampleRequest">
endif
ifndef RUNTIMECLASS_Windows_Media_Core_MediaStreamSourceSwitchStreamsRequestDeferral_DEFINED
define RUNTIMECLASS_Windows_Media_Core_MediaStreamSourceSwitchStreamsRequestDeferral_DEFINED
define RuntimeClass_Windows_Media_Core_MediaStreamSourceSwitchStreamsRequestDeferral <L"Windows.Media.Core.MediaStreamSourceSwitchStreamsRequestDeferral">
endif
ifndef RUNTIMECLASS_Windows_Media_Core_MediaStreamSourceSwitchStreamsRequest_DEFINED
define RUNTIMECLASS_Windows_Media_Core_MediaStreamSourceSwitchStreamsRequest_DEFINED
define RuntimeClass_Windows_Media_Core_MediaStreamSourceSwitchStreamsRequest <L"Windows.Media.Core.MediaStreamSourceSwitchStreamsRequest">
endif

endif
