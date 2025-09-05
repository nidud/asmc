ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Emedia2Emediaproperties_h__
define __windows2Emedia2Emediaproperties_h__
ifndef __windows2Efoundation_h__
include Windows.Foundation.inc
endif

.namespace Windows
.namespace Media
.namespace MediaProperties

.enum MediaPixelFormat {
    MediaPixelFormat_Nv12	= 0,
    MediaPixelFormat_Bgra8	= 1
    }

.enum MediaThumbnailFormat {
    MediaThumbnailFormat_Bmp	= 0,
    MediaThumbnailFormat_Bgra8	= 1
    }

.enum AudioEncodingQuality {
    AudioEncodingQuality_Auto	= 0,
    AudioEncodingQuality_High	= 1,
    AudioEncodingQuality_Medium = 2,
    AudioEncodingQuality_Low	= 3
    }

.enum VideoEncodingQuality {
    VideoEncodingQuality_Auto	= 0,
    VideoEncodingQuality_HD1080p	= 1,
    VideoEncodingQuality_HD720p = 2,
    VideoEncodingQuality_Wvga	= 3,
    VideoEncodingQuality_Ntsc	= 4,
    VideoEncodingQuality_Pal	= 5,
    VideoEncodingQuality_Vga	= 6,
    VideoEncodingQuality_Qvga	= 7
    }

.endn
.endn
.endn

include Windows.Storage.inc

ifndef ____FIIterator_1_Windows__CMedia__CMediaProperties__CIMediaEncodingProperties_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CMedia__CMediaProperties__CIMediaEncodingProperties_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CMedia__CMediaProperties__CIMediaEncodingProperties, "7c094aec-c8f3-5f49-99c7-b66d8414200e")

.comdef __FIIterator_1_Windows__CMedia__CMediaProperties__CIMediaEncodingProperties : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CMedia__CMediaProperties__CIMediaEncodingProperties_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CMedia__CMediaProperties__CIMediaEncodingProperties_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CMedia__CMediaProperties__CIMediaEncodingProperties, "d7fc75d5-3492-5bbb-9b34-dac3e24e79d0")

.comdef __FIIterable_1_Windows__CMedia__CMediaProperties__CIMediaEncodingProperties : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CMedia__CMediaProperties__CIMediaEncodingProperties_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CMedia__CMediaProperties__CIMediaEncodingProperties_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CMedia__CMediaProperties__CIMediaEncodingProperties, "0f6c3b8b-5818-5cbf-bf26-6616bfc308c4")

.comdef __FIVectorView_1_Windows__CMedia__CMediaProperties__CIMediaEncodingProperties : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CMedia__CMediaProperties__CMediaEncodingProfile_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CMedia__CMediaProperties__CMediaEncodingProfile_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CMedia__CMediaProperties__CMediaEncodingProfile,"37296fc1-86da-58a0-90c0-c807bd94395e")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CMedia__CMediaProperties__CMediaEncodingProfile : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CMedia__CMediaProperties__CMediaEncodingProfile_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CMedia__CMediaProperties__CMediaEncodingProfile_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CMedia__CMediaProperties__CMediaEncodingProfile, "d4f86f16-c6cf-57c8-9743-5ec20c31ab79")

.comdef __FIAsyncOperation_1_Windows__CMedia__CMediaProperties__CMediaEncodingProfile : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

.namespace Windows
.namespace Media
.namespace MediaProperties

ifndef ____x_ABI_CWindows_CMedia_CMediaProperties_CIMediaRatio_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CMediaProperties_CIMediaRatio_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_MediaProperties_IMediaRatio <L"Windows.Media.MediaProperties.IMediaRatio">
DEFINE_IIDX(IMediaRatio, "D2D0FEE5-8929-401D-AC78-7D357E378163")

.comdef IMediaRatio : public IInspectable

    put_Numerator	proc :UINT32
    get_Numerator	proc :ptr
    put_Denominator	proc :UINT32
    get_Denominator	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CMediaProperties_CIMediaEncodingProperties_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CMediaProperties_CIMediaEncodingProperties_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_MediaProperties_IMediaEncodingProperties <L"Windows.Media.MediaProperties.IMediaEncodingProperties">
DEFINE_IIDX(IMediaEncodingProperties, "B4002AF6-ACD4-4E5A-A24B-5D7498A8B8C4")

.comdef IMediaEncodingProperties : public IInspectable

    get_Properties	proc :ptr
    get_Type		proc :ptr
    put_Subtype		proc :HSTRING
    get_Subtype		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CMediaProperties_CIAudioEncodingProperties_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CMediaProperties_CIAudioEncodingProperties_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_MediaProperties_IAudioEncodingProperties <L"Windows.Media.MediaProperties.IAudioEncodingProperties">
DEFINE_IIDX(IAudioEncodingProperties, "62BC7A16-005C-4B3B-8A0B-0A090E9687F3")

.comdef IAudioEncodingProperties : public IInspectable

    put_Bitrate		proc :UINT32
    get_Bitrate		proc :ptr
    put_ChannelCount	proc :UINT32
    get_ChannelCount	proc :ptr
    put_SampleRate	proc :UINT32
    get_SampleRate	proc :ptr
    put_BitsPerSample	proc :UINT32
    get_BitsPerSample	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CMediaProperties_CIAudioEncodingPropertiesWithFormatUserData_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CMediaProperties_CIAudioEncodingPropertiesWithFormatUserData_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_MediaProperties_IAudioEncodingPropertiesWithFormatUserData <L"Windows.Media.MediaProperties.IAudioEncodingPropertiesWithFormatUserData">
DEFINE_IIDX(IAudioEncodingPropertiesWithFormatUserData, "98F10D79-13EA-49FF-BE70-2673DB69702C")

.comdef IAudioEncodingPropertiesWithFormatUserData : public IInspectable

    SetFormatUserData	proc :UINT32, :ptr
    GetFormatUserData	proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CMediaProperties_CIAudioEncodingPropertiesStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CMediaProperties_CIAudioEncodingPropertiesStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_MediaProperties_IAudioEncodingPropertiesStatics <L"Windows.Media.MediaProperties.IAudioEncodingPropertiesStatics">
DEFINE_IIDX(IAudioEncodingPropertiesStatics, "0CAD332C-EBE9-4527-B36D-E42A13CF38DB")

.comdef IAudioEncodingPropertiesStatics : public IInspectable

    CreateAac		proc :UINT32, :UINT32, :UINT32, :ptr
    CreateAacAdts	proc :UINT32, :UINT32, :UINT32, :ptr
    CreateMp3		proc :UINT32, :UINT32, :UINT32, :ptr
    CreatePcm		proc :UINT32, :UINT32, :UINT32, :ptr
    CreateWma		proc :UINT32, :UINT32, :UINT32, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CMediaProperties_CIVideoEncodingProperties_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CMediaProperties_CIVideoEncodingProperties_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_MediaProperties_IVideoEncodingProperties <L"Windows.Media.MediaProperties.IVideoEncodingProperties">
DEFINE_IIDX(IVideoEncodingProperties, "76EE6C9A-37C2-4F2A-880A-1282BBB4373D")

.comdef IVideoEncodingProperties : public IInspectable

    put_Bitrate		proc :UINT32
    get_Bitrate		proc :ptr
    put_Width		proc :UINT32
    get_Width		proc :ptr
    put_Height		proc :UINT32
    get_Height		proc :ptr
    get_FrameRate	proc :ptr
    get_PixelAspectRatio proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CMediaProperties_CIMediaEncodingSubtypesStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CMediaProperties_CIMediaEncodingSubtypesStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_MediaProperties_IMediaEncodingSubtypesStatics <L"Windows.Media.MediaProperties.IMediaEncodingSubtypesStatics">
DEFINE_IIDX(IMediaEncodingSubtypesStatics, "37B6580E-A171-4464-BA5A-53189E48C1C8")

.comdef IMediaEncodingSubtypesStatics : public IInspectable

    get_Aac		proc :ptr
    get_AacAdts		proc :ptr
    get_Ac3		proc :ptr
    get_AmrNb		proc :ptr
    get_AmrWb		proc :ptr
    get_Argb32		proc :ptr
    get_Asf		proc :ptr
    get_Avi		proc :ptr
    get_Bgra8		proc :ptr
    get_Bmp		proc :ptr
    get_Eac3		proc :ptr
    get_Float		proc :ptr
    get_Gif		proc :ptr
    get_H263		proc :ptr
    get_H264		proc :ptr
    get_H264Es		proc :ptr
    get_Hevc		proc :ptr
    get_HevcEs		proc :ptr
    get_Iyuv		proc :ptr
    get_Jpeg		proc :ptr
    get_JpegXr		proc :ptr
    get_Mjpg		proc :ptr
    get_Mpeg		proc :ptr
    get_Mpeg1		proc :ptr
    get_Mpeg2		proc :ptr
    get_Mp3		proc :ptr
    get_Mpeg4		proc :ptr
    get_Nv12		proc :ptr
    get_Pcm		proc :ptr
    get_Png		proc :ptr
    get_Rgb24		proc :ptr
    get_Rgb32		proc :ptr
    get_Tiff		proc :ptr
    get_Wave		proc :ptr
    get_Wma8		proc :ptr
    get_Wma9		proc :ptr
    get_Wmv3		proc :ptr
    get_Wvc1		proc :ptr
    get_Yuy2		proc :ptr
    get_Yv12		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CMediaProperties_CIH264ProfileIdsStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CMediaProperties_CIH264ProfileIdsStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_MediaProperties_IH264ProfileIdsStatics <L"Windows.Media.MediaProperties.IH264ProfileIdsStatics">
DEFINE_IIDX(IH264ProfileIdsStatics, "38654CA7-846A-4F97-A2E5-C3A15BBF70FD")

.comdef IH264ProfileIdsStatics : public IInspectable

    get_ConstrainedBaseline proc :ptr
    get_Baseline	proc :ptr
    get_Extended	proc :ptr
    get_Main		proc :ptr
    get_High		proc :ptr
    get_High10		proc :ptr
    get_High422		proc :ptr
    get_High444		proc :ptr
    get_StereoHigh	proc :ptr
    get_MultiviewHigh	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CMediaProperties_CIMpeg2ProfileIdsStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CMediaProperties_CIMpeg2ProfileIdsStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_MediaProperties_IMpeg2ProfileIdsStatics <L"Windows.Media.MediaProperties.IMpeg2ProfileIdsStatics">
DEFINE_IIDX(IMpeg2ProfileIdsStatics, "A461FF85-E57A-4128-9B21-D5331B04235C")

.comdef IMpeg2ProfileIdsStatics : public IInspectable

    get_Simple		proc :ptr
    get_Main		proc :ptr
    get_SignalNoiseRatioScalable proc :ptr
    get_SpatiallyScalable proc :ptr
    get_High		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CMediaProperties_CIVideoEncodingProperties2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CMediaProperties_CIVideoEncodingProperties2_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_MediaProperties_IVideoEncodingProperties2 <L"Windows.Media.MediaProperties.IVideoEncodingProperties2">
DEFINE_IIDX(IVideoEncodingProperties2, "F743A1EF-D465-4290-A94B-EF0F1528F8E3")

.comdef IVideoEncodingProperties2 : public IInspectable

    SetFormatUserData	proc :UINT32, :ptr
    GetFormatUserData	proc :ptr, :ptr
    put_ProfileId	proc :INT32
    get_ProfileId	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CMediaProperties_CIVideoEncodingPropertiesStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CMediaProperties_CIVideoEncodingPropertiesStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_MediaProperties_IVideoEncodingPropertiesStatics <L"Windows.Media.MediaProperties.IVideoEncodingPropertiesStatics">
DEFINE_IIDX(IVideoEncodingPropertiesStatics, "3CE14D44-1DC5-43DB-9F38-EBEBF90152CB")

.comdef IVideoEncodingPropertiesStatics : public IInspectable

    CreateH264		proc :ptr
    CreateMpeg2		proc :ptr
    CreateUncompressed	proc :HSTRING, :UINT32, :UINT32, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CMediaProperties_CIImageEncodingProperties_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CMediaProperties_CIImageEncodingProperties_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_MediaProperties_IImageEncodingProperties <L"Windows.Media.MediaProperties.IImageEncodingProperties">
DEFINE_IIDX(IImageEncodingProperties, "78625635-F331-4189-B1C3-B48D5AE034F1")

.comdef IImageEncodingProperties : public IInspectable

    put_Width		proc :UINT32
    get_Width		proc :ptr
    put_Height		proc :UINT32
    get_Height		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CMediaProperties_CIImageEncodingPropertiesStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CMediaProperties_CIImageEncodingPropertiesStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_MediaProperties_IImageEncodingPropertiesStatics <L"Windows.Media.MediaProperties.IImageEncodingPropertiesStatics">
DEFINE_IIDX(IImageEncodingPropertiesStatics, "257C68DC-8B99-439E-AA59-913A36161297")

.comdef IImageEncodingPropertiesStatics : public IInspectable

    CreateJpeg		proc :ptr
    CreatePng		proc :ptr
    CreateJpegXR	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CMediaProperties_CIImageEncodingPropertiesStatics2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CMediaProperties_CIImageEncodingPropertiesStatics2_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_MediaProperties_IImageEncodingPropertiesStatics2 <L"Windows.Media.MediaProperties.IImageEncodingPropertiesStatics2">
DEFINE_IIDX(IImageEncodingPropertiesStatics2, "F6C25B29-3824-46B0-956E-501329E1BE3C")

.comdef IImageEncodingPropertiesStatics2 : public IInspectable

    CreateUncompressed	proc :Windows::Media::MediaProperties::MediaPixelFormat, :ptr
    CreateBmp		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CMediaProperties_CIContainerEncodingProperties_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CMediaProperties_CIContainerEncodingProperties_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_MediaProperties_IContainerEncodingProperties <L"Windows.Media.MediaProperties.IContainerEncodingProperties">
DEFINE_IIDX(IContainerEncodingProperties, "59AC2A57-B32A-479E-8A61-4B7F2E9E7EA0")

.comdef IContainerEncodingProperties : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CMediaProperties_CIMediaEncodingProfileStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CMediaProperties_CIMediaEncodingProfileStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_MediaProperties_IMediaEncodingProfileStatics <L"Windows.Media.MediaProperties.IMediaEncodingProfileStatics">
DEFINE_IIDX(IMediaEncodingProfileStatics, "197F352C-2EDE-4A45-A896-817A4854F8FE")

.comdef IMediaEncodingProfileStatics : public IInspectable

    CreateM4a		proc :Windows::Media::MediaProperties::AudioEncodingQuality, :ptr
    CreateMp3		proc :Windows::Media::MediaProperties::AudioEncodingQuality, :ptr
    CreateWma		proc :Windows::Media::MediaProperties::AudioEncodingQuality, :ptr
    CreateMp4		proc :Windows::Media::MediaProperties::AudioEncodingQuality, :ptr
    CreateWmv		proc :Windows::Media::MediaProperties::AudioEncodingQuality, :ptr
    CreateFromFileAsync proc :ptr, :ptr
    CreateFromStreamAsync proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CMediaProperties_CIMediaEncodingProfileStatics2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CMediaProperties_CIMediaEncodingProfileStatics2_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_MediaProperties_IMediaEncodingProfileStatics2 <L"Windows.Media.MediaProperties.IMediaEncodingProfileStatics2">
DEFINE_IIDX(IMediaEncodingProfileStatics2, "CE8DE74F-6AF4-4288-8FE2-79ADF1F79A43")

.comdef IMediaEncodingProfileStatics2 : public IInspectable

    CreateWav		proc :Windows::Media::MediaProperties::AudioEncodingQuality, :ptr
    CreateAvi		proc :Windows::Media::MediaProperties::AudioEncodingQuality, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CMediaProperties_CIMediaEncodingProfile_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CMediaProperties_CIMediaEncodingProfile_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_MediaProperties_IMediaEncodingProfile <L"Windows.Media.MediaProperties.IMediaEncodingProfile">
DEFINE_IIDX(IMediaEncodingProfile, "E7DBF5A8-1DB9-4783-876B-3DFE12ACFDB3")

.comdef IMediaEncodingProfile : public IInspectable

    put_Audio		proc :ptr
    get_Audio		proc :ptr
    put_Video		proc :ptr
    get_Video		proc :ptr
    put_Container	proc :ptr
    get_Container	proc :ptr
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_Media_MediaProperties_MediaRatio_DEFINED
define RUNTIMECLASS_Windows_Media_MediaProperties_MediaRatio_DEFINED
define RuntimeClass_Windows_Media_MediaProperties_MediaRatio <L"Windows.Media.MediaProperties.MediaRatio">
endif
ifndef RUNTIMECLASS_Windows_Media_MediaProperties_MediaPropertySet_DEFINED
define RUNTIMECLASS_Windows_Media_MediaProperties_MediaPropertySet_DEFINED
define RuntimeClass_Windows_Media_MediaProperties_MediaPropertySet <L"Windows.Media.MediaProperties.MediaPropertySet">
endif
ifndef RUNTIMECLASS_Windows_Media_MediaProperties_AudioEncodingProperties_DEFINED
define RUNTIMECLASS_Windows_Media_MediaProperties_AudioEncodingProperties_DEFINED
define RuntimeClass_Windows_Media_MediaProperties_AudioEncodingProperties <L"Windows.Media.MediaProperties.AudioEncodingProperties">
endif
ifndef RUNTIMECLASS_Windows_Media_MediaProperties_MediaEncodingSubtypes_DEFINED
define RUNTIMECLASS_Windows_Media_MediaProperties_MediaEncodingSubtypes_DEFINED
define RuntimeClass_Windows_Media_MediaProperties_MediaEncodingSubtypes <L"Windows.Media.MediaProperties.MediaEncodingSubtypes">
endif
ifndef RUNTIMECLASS_Windows_Media_MediaProperties_H264ProfileIds_DEFINED
define RUNTIMECLASS_Windows_Media_MediaProperties_H264ProfileIds_DEFINED
define RuntimeClass_Windows_Media_MediaProperties_H264ProfileIds <L"Windows.Media.MediaProperties.H264ProfileIds">
endif
ifndef RUNTIMECLASS_Windows_Media_MediaProperties_Mpeg2ProfileIds_DEFINED
define RUNTIMECLASS_Windows_Media_MediaProperties_Mpeg2ProfileIds_DEFINED
define RuntimeClass_Windows_Media_MediaProperties_Mpeg2ProfileIds <L"Windows.Media.MediaProperties.Mpeg2ProfileIds">
endif
ifndef RUNTIMECLASS_Windows_Media_MediaProperties_VideoEncodingProperties_DEFINED
define RUNTIMECLASS_Windows_Media_MediaProperties_VideoEncodingProperties_DEFINED
define RuntimeClass_Windows_Media_MediaProperties_VideoEncodingProperties <L"Windows.Media.MediaProperties.VideoEncodingProperties">
endif
ifndef RUNTIMECLASS_Windows_Media_MediaProperties_ImageEncodingProperties_DEFINED
define RUNTIMECLASS_Windows_Media_MediaProperties_ImageEncodingProperties_DEFINED
define RuntimeClass_Windows_Media_MediaProperties_ImageEncodingProperties <L"Windows.Media.MediaProperties.ImageEncodingProperties">
endif
ifndef RUNTIMECLASS_Windows_Media_MediaProperties_ContainerEncodingProperties_DEFINED
define RUNTIMECLASS_Windows_Media_MediaProperties_ContainerEncodingProperties_DEFINED
define RuntimeClass_Windows_Media_MediaProperties_ContainerEncodingProperties <L"Windows.Media.MediaProperties.ContainerEncodingProperties">
endif
ifndef RUNTIMECLASS_Windows_Media_MediaProperties_MediaEncodingProfile_DEFINED
define RUNTIMECLASS_Windows_Media_MediaProperties_MediaEncodingProfile_DEFINED
define RuntimeClass_Windows_Media_MediaProperties_MediaEncodingProfile <L"Windows.Media.MediaProperties.MediaEncodingProfile">
endif

endif
