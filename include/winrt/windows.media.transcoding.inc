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

ifndef __windows2Emedia2Etranscoding_h__
define __windows2Emedia2Etranscoding_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include Windows.Media.Core.inc
include windows.foundation.collections.inc
ifndef __windows2Emedia2Emediaproperties_h__
include Windows.Media.MediaProperties.inc
endif
ifndef __windows2Estorage_h__
include Windows.Storage.inc
endif
ifndef __windows2Estorage2Estreams_h__
include Windows.Storage.Streams.inc
endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CMedia__CTranscoding__CPrepareTranscodeResult_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CMedia__CTranscoding__CPrepareTranscodeResult_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CMedia__CTranscoding__CPrepareTranscodeResult, "a44d7d07-8f74-52ee-9f02-c2b244b4ff2a")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CMedia__CTranscoding__CPrepareTranscodeResult : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CMedia__CTranscoding__CPrepareTranscodeResult_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CMedia__CTranscoding__CPrepareTranscodeResult_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CMedia__CTranscoding__CPrepareTranscodeResult, "f5f07c13-3047-5bab-8eb7-6e5d7d14afae")

.comdef __FIAsyncOperation_1_Windows__CMedia__CTranscoding__CPrepareTranscodeResult : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

.namespace Windows
.namespace Media
.namespace Transcoding

.enum TranscodeFailureReason {
    TranscodeFailureReason_None = 0,
    TranscodeFailureReason_Unknown	= 1,
    TranscodeFailureReason_InvalidProfile	= 2,
    TranscodeFailureReason_CodecNotFound	= 3
    }

.enum MediaVideoProcessingAlgorithm {
    MediaVideoProcessingAlgorithm_Default	= 0,
    MediaVideoProcessingAlgorithm_MrfCrf444	= 1
    }

ifndef ____x_ABI_CWindows_CMedia_CTranscoding_CIMediaTranscoder2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CTranscoding_CIMediaTranscoder2_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Transcoding_IMediaTranscoder2 <L"Windows.Media.Transcoding.IMediaTranscoder2">
DEFINE_IIDX(IMediaTranscoder2, "40531D74-35E0-4F04-8574-CA8BC4E5A082")

.comdef IMediaTranscoder2 : public IInspectable

    PrepareMediaStreamSourceTranscodeAsync proc :ptr, :ptr, :ptr, :ptr
    put_VideoProcessingAlgorithm proc :Windows::Media::Transcoding::MediaVideoProcessingAlgorithm
    get_VideoProcessingAlgorithm proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CTranscoding_CIMediaTranscoder_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CTranscoding_CIMediaTranscoder_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Transcoding_IMediaTranscoder <L"Windows.Media.Transcoding.IMediaTranscoder">
DEFINE_IIDX(IMediaTranscoder, "190C99D2-A0AA-4D34-86BC-EED1B12C2F5B")

.comdef IMediaTranscoder : public IInspectable

    put_TrimStartTime	proc :Windows::Foundation::TimeSpan
    get_TrimStartTime	proc :ptr
    put_TrimStopTime	proc :Windows::Foundation::TimeSpan
    get_TrimStopTime	proc :ptr
    put_AlwaysReencode	proc :boolean
    get_AlwaysReencode	proc :ptr
    put_HardwareAccelerationEnabled proc :boolean
    get_HardwareAccelerationEnabled proc :ptr
    AddAudioEffect	proc :HSTRING
    AddAudioEffectWithSettings proc :HSTRING, :boolean, :ptr
    AddVideoEffect	proc :HSTRING
    AddVideoEffectWithSettings proc :HSTRING, :boolean, :ptr
    ClearEffects	proc
    PrepareFileTranscodeAsync proc :ptr, :ptr, :ptr, :ptr
    PrepareStreamTranscodeAsync proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CTranscoding_CIPrepareTranscodeResult_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CTranscoding_CIPrepareTranscodeResult_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Transcoding_IPrepareTranscodeResult <L"Windows.Media.Transcoding.IPrepareTranscodeResult">
DEFINE_IIDX(IPrepareTranscodeResult,"05F25DCE-994F-4A34-9D68-97CCCE1730D6")

.comdef IPrepareTranscodeResult : public IInspectable

    get_CanTranscode	proc :ptr
    get_FailureReason	proc :ptr
    TranscodeAsync	proc :ptr
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_Media_Transcoding_PrepareTranscodeResult_DEFINED
define RUNTIMECLASS_Windows_Media_Transcoding_PrepareTranscodeResult_DEFINED
define RuntimeClass_Windows_Media_Transcoding_PrepareTranscodeResult <L"Windows.Media.Transcoding.PrepareTranscodeResult">
endif
ifndef RUNTIMECLASS_Windows_Media_Transcoding_MediaTranscoder_DEFINED
define RUNTIMECLASS_Windows_Media_Transcoding_MediaTranscoder_DEFINED
define RuntimeClass_Windows_Media_Transcoding_MediaTranscoder <L"Windows.Media.Transcoding.MediaTranscoder">
endif

endif
