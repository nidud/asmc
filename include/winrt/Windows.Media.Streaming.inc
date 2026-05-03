ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Emedia2Estreaming_h__
define __windows2Emedia2Estreaming_h__

include windows.foundation.inc
include Windows.Storage.Streams.inc
include Windows.Media.Streaming.Devices.inc
include windows.foundation.collections.inc

.namespace Windows
.namespace Media
.namespace Streaming

.enum TransportState {
    TransportState_Unknown,
    TransportState_Stopped,
    TransportState_Playing,
    TransportState_Transitioning,
    TransportState_Paused,
    TransportState_Recording,
    TransportState_NoMediaPresent,
    TransportState_Last
    }

.enum TransportStatus {
    TransportStatus_Unknown,
    TransportStatus_Ok,
    TransportStatus_ErrorOccurred,
    TransportStatus_Last
    }

.template RenderingParameters
    volume              UINT ?
    mute                boolean ?
   .ends

.template PlaySpeed
    Numerator           INT32 ?
    Denominator         UINT32 ?
   .ends

.template TransportInformation
    CurrentTransportState   Windows::Media::Streaming::TransportState ?
    CurrentTransportStatus  Windows::Media::Streaming::TransportStatus ?
    CurrentSpeed            Windows::Media::Streaming::PlaySpeed <>
   .ends

Windows::Media::Streaming::TrackId typedef UINT32

.template TrackInformation
    Track               UINT32 ?
    TrackId             UINT32 ?
    TrackDuration       Windows::Foundation::TimeSpan <>
   .ends

.template PositionInformation
    trackInformation    Windows::Media::Streaming::TrackInformation <>
    relativeTime        Windows::Foundation::TimeSpan <>
   .ends

ifndef ____x_ABI_CWindows_CMedia_CStreaming_CITransportParametersUpdateHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CStreaming_CITransportParametersUpdateHandler_INTERFACE_DEFINED__
DEFINE_IIDX(ITransportParametersUpdateHandler, "16fd02d5-da61-49d7-aab2-76867dd42db7")

.comdef ITransportParametersUpdateHandler : public IUnknown

    _Invoke             proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CStreaming_CIRenderingParametersUpdateHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CStreaming_CIRenderingParametersUpdateHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IRenderingParametersUpdateHandler, "3a2d9d45-72e9-4311-b46c-27c8bb7e6cb3")

.comdef IRenderingParametersUpdateHandler : public IUnknown

    _Invoke             proc :ptr, :Windows::Media::Streaming::RenderingParameters
   .ends

endif

.endn
.endn
.endn

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CMedia__CStreaming__CTransportInformation_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CMedia__CStreaming__CTransportInformation_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CMedia__CStreaming__CTransportInformation, "9970f463-bcd0-55b9-94cd-8932d42446ca")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CMedia__CStreaming__CTransportInformation : public IUnknown

    _Invoke             proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CMedia__CStreaming__CTransportInformation_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CMedia__CStreaming__CTransportInformation_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CMedia__CStreaming__CTransportInformation, "f99e7d9c-2274-5f3d-89e7-f5f862ba0334")

.comdef __FIAsyncOperation_1_Windows__CMedia__CStreaming__CTransportInformation : public IInspectable

    put_Completed       proc :ptr
    get_Completed       proc :ptr
    GetResults          proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CMedia__CStreaming__CPositionInformation_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CMedia__CStreaming__CPositionInformation_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CMedia__CStreaming__CPositionInformation, "adc7daf4-9a69-5d0b-aec8-e2ee3292d178")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CMedia__CStreaming__CPositionInformation : public IUnknown

    _Invoke             proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CMedia__CStreaming__CPositionInformation_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CMedia__CStreaming__CPositionInformation_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CMedia__CStreaming__CPositionInformation, "e2b45a37-e1c1-5e80-8962-a134d7f3557c")

.comdef __FIAsyncOperation_1_Windows__CMedia__CStreaming__CPositionInformation : public IInspectable

    put_Completed       proc :ptr
    get_Completed       proc :ptr
    GetResults          proc :ptr
   .ends

endif

.namespace Windows
.namespace Media
.namespace Streaming

ifndef ____x_ABI_CWindows_CMedia_CStreaming_CIMediaRenderer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CStreaming_CIMediaRenderer_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Streaming_IMediaRenderer <L"Windows.Media.Streaming.IMediaRenderer">
DEFINE_IIDX(IMediaRenderer, "2c012ec3-d975-47fb-96ac-a6418b326d2b")

.comdef IMediaRenderer : public IInspectable

    get_IsAudioSupported proc :ptr
    get_IsVideoSupported proc :ptr
    get_IsImageSupported proc :ptr
    get_ActionInformation proc :ptr
    SetSourceFromUriAsync proc :HSTRING, :ptr
    SetSourceFromStreamAsync proc :ptr, :ptr
    SetSourceFromMediaSourceAsync proc :ptr, :ptr
    SetNextSourceFromUriAsync proc :HSTRING, :ptr
    SetNextSourceFromStreamAsync proc :ptr, :ptr
    SetNextSourceFromMediaSourceAsync proc :ptr, :ptr
    PlayAsync           proc :ptr
    PlayAtSpeedAsync    proc :Windows::Media::Streaming::PlaySpeed, :ptr
    StopAsync           proc :ptr
    PauseAsync          proc :ptr
    GetMuteAsync        proc :ptr
    SetMuteAsync        proc :boolean, :ptr
    GetVolumeAsync      proc :ptr
    SetVolumeAsync      proc :UINT32, :ptr
    SeekAsync           proc :Windows::Foundation::TimeSpan, :ptr
    GetTransportInformationAsync proc :ptr
    GetPositionInformationAsync proc :ptr
    add_TransportParametersUpdate proc :ptr, :ptr
    remove_TransportParametersUpdate proc :EventRegistrationToken
    add_RenderingParametersUpdate proc :ptr, :ptr
    remove_RenderingParametersUpdate proc :EventRegistrationToken
    NextAsync           proc :ptr
   .ends

endif

.endn
.endn
.endn

ifndef ____FIIterator_1_Windows__CMedia__CStreaming__CPlaySpeed_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CMedia__CStreaming__CPlaySpeed_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CMedia__CStreaming__CPlaySpeed, "fd051cd8-25c7-5780-9606-b35062137d21")

.comdef __FIIterator_1_Windows__CMedia__CStreaming__CPlaySpeed : public IInspectable

    get_Current         proc :ptr
    get_HasCurrent      proc :ptr
    MoveNext            proc :ptr
    GetMany             proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CMedia__CStreaming__CPlaySpeed_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CMedia__CStreaming__CPlaySpeed_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CMedia__CStreaming__CPlaySpeed, "c4a17a40-8c62-5884-822b-502526970b0d")

.comdef __FIIterable_1_Windows__CMedia__CStreaming__CPlaySpeed : public IInspectable

    First               proc :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CMedia__CStreaming__CPlaySpeed_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CMedia__CStreaming__CPlaySpeed_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CMedia__CStreaming__CPlaySpeed, "1295caf3-c1da-54ea-ac66-da2c044f9eb0")

.comdef __FIVectorView_1_Windows__CMedia__CStreaming__CPlaySpeed : public IInspectable

    GetAt               proc :SINT, :ptr
    get_Size            proc :ptr
    IndexOf             proc :Windows::Media::Streaming::PlaySpeed, :ptr, :ptr
    GetMany             proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVector_1_Windows__CMedia__CStreaming__CPlaySpeed_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CMedia__CStreaming__CPlaySpeed_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CMedia__CStreaming__CPlaySpeed, "fde57c75-5b86-5921-8ffb-101b0a184230")

.comdef __FIVector_1_Windows__CMedia__CStreaming__CPlaySpeed : public IInspectable

    GetAt               proc :SINT, :ptr
    get_Size            proc :ptr
    GetView             proc :ptr
    IndexOf             proc :Windows::Media::Streaming::PlaySpeed, :ptr, :ptr
    SetAt               proc :SINT, :Windows::Media::Streaming::PlaySpeed
    InsertAt            proc :SINT, :Windows::Media::Streaming::PlaySpeed
    RemoveAt            proc :SINT
    Append              proc :Windows::Media::Streaming::PlaySpeed
    RemoveAtEnd         proc
    Clear               proc
    GetMany             proc :SINT, :SINT, :ptr, :ptr
    ReplaceAll          proc :SINT, :ptr
   .ends

endif

.namespace Windows
.namespace Media
.namespace Streaming

ifndef ____x_ABI_CWindows_CMedia_CStreaming_CIMediaRendererActionInformation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CStreaming_CIMediaRendererActionInformation_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Streaming_IMediaRendererActionInformation <L"Windows.Media.Streaming.IMediaRendererActionInformation">
DEFINE_IIDX(IMediaRendererActionInformation, "66fbbfee-5ab0-4a4f-8d15-e5056b26beda")

.comdef IMediaRendererActionInformation : public IInspectable

    get_IsMuteAvailable proc :ptr
    get_IsPauseAvailable proc :ptr
    get_IsPlayAvailable proc :ptr
    get_IsSeekAvailable proc :ptr
    get_IsSetNextSourceAvailable proc :ptr
    get_IsStopAvailable proc :ptr
    get_IsVolumeAvailable proc :ptr
    get_PlaySpeeds      proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CStreaming_CITransportParameters_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CStreaming_CITransportParameters_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Streaming_ITransportParameters <L"Windows.Media.Streaming.ITransportParameters">
DEFINE_IIDX(ITransportParameters, "eb0c4e24-2283-438d-8fff-dbe9df1cb2cc")

.comdef ITransportParameters : public IInspectable

    get_ActionInformation proc :ptr
    get_TrackInformation proc :ptr
    get_TransportInformation proc :ptr
   .ends

endif

.endn
.endn
.endn


ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CMedia__CStreaming__CMediaRenderer_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CMedia__CStreaming__CMediaRenderer_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CMedia__CStreaming__CMediaRenderer, "f0d971af-e054-5616-9fdf-0903b9ceb182")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CMedia__CStreaming__CMediaRenderer : public IUnknown

    _Invoke             proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CMedia__CStreaming__CMediaRenderer_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CMedia__CStreaming__CMediaRenderer_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CMedia__CStreaming__CMediaRenderer, "557dd3fb-4710-5059-921c-0dee68361fb5")

.comdef __FIAsyncOperation_1_Windows__CMedia__CStreaming__CMediaRenderer : public IInspectable

    put_Completed       proc :ptr
    get_Completed       proc :ptr
    GetResults          proc :ptr
   .ends

endif

ifndef RUNTIMECLASS_Windows_Media_Streaming_CreateMediaRendererOperation_DEFINED
define RUNTIMECLASS_Windows_Media_Streaming_CreateMediaRendererOperation_DEFINED
define RuntimeClass_Windows_Media_Streaming_CreateMediaRendererOperation <L"Windows.Media.Streaming.CreateMediaRendererOperation">
endif
ifndef RUNTIMECLASS_Windows_Media_Streaming_MediaRenderer_DEFINED
define RUNTIMECLASS_Windows_Media_Streaming_MediaRenderer_DEFINED
define RuntimeClass_Windows_Media_Streaming_MediaRenderer <L"Windows.Media.Streaming.MediaRenderer">
endif

.namespace Windows
.namespace Media
.namespace Streaming

ifndef ____x_ABI_CWindows_CMedia_CStreaming_CIMediaRendererFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CStreaming_CIMediaRendererFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Streaming_IMediaRendererFactory <L"Windows.Media.Streaming.IMediaRendererFactory">
DEFINE_IIDX(IMediaRendererFactory, "657ab43d-b909-42b2-94d0-e3a0b134e8c9")

.comdef IMediaRendererFactory : public IInspectable

    CreateMediaRendererAsync proc :HSTRING, :ptr
    CreateMediaRendererFromBasicDeviceAsync proc :ptr, :ptr
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_Media_Streaming_StreamSelector_DEFINED
define RUNTIMECLASS_Windows_Media_Streaming_StreamSelector_DEFINED
define RuntimeClass_Windows_Media_Streaming_StreamSelector <L"Windows.Media.Streaming.StreamSelector">
endif

ifndef ____FIIterator_1___F__CIPropertySet_INTERFACE_DEFINED__
define ____FIIterator_1___F__CIPropertySet_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1___F__CIPropertySet, "d79a75c8-b1d2-544d-9b09-7f7900a34efb")

.comdef __FIIterator_1___F__CIPropertySet : public IInspectable

    get_Current         proc :ptr
    get_HasCurrent      proc :ptr
    MoveNext            proc :ptr
    GetMany             proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1___F__CIPropertySet_INTERFACE_DEFINED__
define ____FIIterable_1___F__CIPropertySet_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1___F__CIPropertySet, "489b756d-be43-5abb-b9a0-a47254103339")

.comdef __FIIterable_1___F__CIPropertySet : public IInspectable

    First               proc :ptr
   .ends

endif

ifndef ____FIVectorView_1___F__CIPropertySet_INTERFACE_DEFINED__
define ____FIVectorView_1___F__CIPropertySet_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1___F__CIPropertySet, "c25d9a17-c31e-5311-8122-3c04d28af9fc")

.comdef __FIVectorView_1___F__CIPropertySet : public IInspectable

    GetAt               proc :SINT, :ptr
    get_Size            proc :ptr
    IndexOf             proc :ptr, :ptr, :ptr
    GetMany             proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1___FIVectorView_1___F__CIPropertySet_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1___FIVectorView_1___F__CIPropertySet_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1___FIVectorView_1___F__CIPropertySet, "af4e2f8a-92ca-5640-865c-9948fbde4495")

.comdef __FIAsyncOperationCompletedHandler_1___FIVectorView_1___F__CIPropertySet : public IUnknown

    _Invoke             proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1___FIVectorView_1___F__CIPropertySet_INTERFACE_DEFINED__
define ____FIAsyncOperation_1___FIVectorView_1___F__CIPropertySet_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1___FIVectorView_1___F__CIPropertySet, "216f9390-ea3d-5465-a789-6394a47eb4a4")

.comdef __FIAsyncOperation_1___FIVectorView_1___F__CIPropertySet : public IInspectable

    put_Completed       proc :ptr
    get_Completed       proc :ptr
    GetResults          proc :ptr
   .ends

endif

.namespace Windows
.namespace Media
.namespace Streaming

ifndef ____x_ABI_CWindows_CMedia_CStreaming_CIStreamSelectorStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CStreaming_CIStreamSelectorStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Streaming_IStreamSelectorStatics <L"Windows.Media.Streaming.IStreamSelectorStatics">
DEFINE_IIDX(IStreamSelectorStatics, "8a4cd4a1-ed85-4e0f-bd68-8a6862e4636d")

.comdef IStreamSelectorStatics : public IInspectable

    SelectBestStreamAsync proc :ptr, :ptr, :ptr
    GetStreamPropertiesAsync proc :ptr, :ptr, :ptr
    SelectBestStreamFromStreamAsync proc :ptr, :ptr, :ptr
    GetStreamPropertiesFromStreamAsync proc :ptr, :ptr, :ptr
   .ends

endif

.endn
.endn
.endn

endif
