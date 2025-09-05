ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Egraphics2Eimaging_h__
define __windows2Egraphics2Eimaging_h__
ifndef __windows2Efoundation_h__
include Windows.Foundation.inc
endif
include Windows.Storage.Streams.inc

ifndef ____FIKeyValuePair_2_HSTRING_Windows__CGraphics__CImaging__CBitmapTypedValue_INTERFACE_DEFINED__
define ____FIKeyValuePair_2_HSTRING_Windows__CGraphics__CImaging__CBitmapTypedValue_INTERFACE_DEFINED__
DEFINE_IIDX(__FIKeyValuePair_2_HSTRING_Windows__CGraphics__CImaging__CBitmapTypedValue, "93621bf0-dae9-5f00-94ac-795aa943dca6")

.comdef __FIKeyValuePair_2_HSTRING_Windows__CGraphics__CImaging__CBitmapTypedValue : public IInspectable

    get_Key		proc :ptr
    get_Value		proc :ptr
   .ends

endif

ifndef ____FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CGraphics__CImaging__CBitmapTypedValue_INTERFACE_DEFINED__
define ____FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CGraphics__CImaging__CBitmapTypedValue_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CGraphics__CImaging__CBitmapTypedValue, "2ad3fb0c-0656-5302-b504-3153be845161")

.comdef __FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CGraphics__CImaging__CBitmapTypedValue : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CGraphics__CImaging__CBitmapTypedValue_INTERFACE_DEFINED__
define ____FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CGraphics__CImaging__CBitmapTypedValue_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CGraphics__CImaging__CBitmapTypedValue, "05f9430c-2f22-5638-aa89-8c9abcd54ff9")

.comdef __FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CGraphics__CImaging__CBitmapTypedValue : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CGraphics__CImaging__CBitmapCodecInformation_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CGraphics__CImaging__CBitmapCodecInformation_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CGraphics__CImaging__CBitmapCodecInformation, "4ff2b2db-9326-537f-b8dc-4c93d77fbb84")

.comdef __FIIterator_1_Windows__CGraphics__CImaging__CBitmapCodecInformation : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CGraphics__CImaging__CBitmapCodecInformation_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CGraphics__CImaging__CBitmapCodecInformation_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CGraphics__CImaging__CBitmapCodecInformation, "2b6bdb90-a4eb-5142-b582-3ccb1edc5789")

.comdef __FIIterable_1_Windows__CGraphics__CImaging__CBitmapCodecInformation : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIMapView_2_HSTRING_Windows__CGraphics__CImaging__CBitmapTypedValue_INTERFACE_DEFINED__
define ____FIMapView_2_HSTRING_Windows__CGraphics__CImaging__CBitmapTypedValue_INTERFACE_DEFINED__
DEFINE_IIDX(__FIMapView_2_HSTRING_Windows__CGraphics__CImaging__CBitmapTypedValue, "9cda5a9a-8924-5b3b-8b19-894d8da99dde")

.comdef __FIMapView_2_HSTRING_Windows__CGraphics__CImaging__CBitmapTypedValue : public IInspectable

    Lookup		proc :HSTRING, :ptr
    get_Size		proc :ptr
    HasKey		proc :HSTRING, :ptr
    Split		proc :ptr, :ptr
   .ends

endif

ifndef ____FIMap_2_HSTRING_Windows__CGraphics__CImaging__CBitmapTypedValue_INTERFACE_DEFINED__
define ____FIMap_2_HSTRING_Windows__CGraphics__CImaging__CBitmapTypedValue_INTERFACE_DEFINED__
DEFINE_IIDX(__FIMap_2_HSTRING_Windows__CGraphics__CImaging__CBitmapTypedValue, "2c70ef8d-5d4c-5185-8db7-fed87728165d")

.comdef __FIMap_2_HSTRING_Windows__CGraphics__CImaging__CBitmapTypedValue : public IInspectable

    Lookup		proc :HSTRING, :ptr
    get_Size		proc :ptr
    HasKey		proc :HSTRING, :ptr
    GetView		proc :ptr
    Insert		proc :HSTRING, :ptr, :ptr
    Remove		proc :HSTRING
    Clear		proc
   .ends

endif

ifndef ____FIVectorView_1_Windows__CGraphics__CImaging__CBitmapCodecInformation_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CGraphics__CImaging__CBitmapCodecInformation_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CGraphics__CImaging__CBitmapCodecInformation, "97dfde96-ff1d-5aa1-863a-90116a31b86b")

.comdef __FIVectorView_1_Windows__CGraphics__CImaging__CBitmapCodecInformation : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CGraphics__CImaging__CBitmapDecoder_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CGraphics__CImaging__CBitmapDecoder_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CGraphics__CImaging__CBitmapDecoder, "bb6514f2-3cfb-566f-82bc-60aabd302d53")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CGraphics__CImaging__CBitmapDecoder : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CGraphics__CImaging__CBitmapDecoder_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CGraphics__CImaging__CBitmapDecoder_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CGraphics__CImaging__CBitmapDecoder, "aa94d8e9-caef-53f6-823d-91b6e8340510")

.comdef __FIAsyncOperation_1_Windows__CGraphics__CImaging__CBitmapDecoder : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CGraphics__CImaging__CBitmapEncoder_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CGraphics__CImaging__CBitmapEncoder_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CGraphics__CImaging__CBitmapEncoder, "5df1afc5-478d-55dd-b317-024274062a0d")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CGraphics__CImaging__CBitmapEncoder : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CGraphics__CImaging__CBitmapEncoder_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CGraphics__CImaging__CBitmapEncoder_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CGraphics__CImaging__CBitmapEncoder, "151bd1c5-4675-5af5-a289-001edc66b86a")

.comdef __FIAsyncOperation_1_Windows__CGraphics__CImaging__CBitmapEncoder : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CGraphics__CImaging__CBitmapFrame_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CGraphics__CImaging__CBitmapFrame_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CGraphics__CImaging__CBitmapFrame, "2817455a-983f-5a06-9fe4-fb9637684320")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CGraphics__CImaging__CBitmapFrame : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CGraphics__CImaging__CBitmapFrame_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CGraphics__CImaging__CBitmapFrame_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CGraphics__CImaging__CBitmapFrame, "cb1483d1-1464-5bf9-9346-d537735dfbd6")

.comdef __FIAsyncOperation_1_Windows__CGraphics__CImaging__CBitmapFrame : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CGraphics__CImaging__CBitmapPropertySet_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CGraphics__CImaging__CBitmapPropertySet_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CGraphics__CImaging__CBitmapPropertySet, "a8325bd7-a3be-5881-9fa7-04ceefb9dc2f")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CGraphics__CImaging__CBitmapPropertySet : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CGraphics__CImaging__CBitmapPropertySet_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CGraphics__CImaging__CBitmapPropertySet_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CGraphics__CImaging__CBitmapPropertySet, "464ac000-b1f1-5246-8268-912a2593d889")

.comdef __FIAsyncOperation_1_Windows__CGraphics__CImaging__CBitmapPropertySet : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CGraphics__CImaging__CImageStream_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CGraphics__CImaging__CImageStream_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CGraphics__CImaging__CImageStream, "29bb8288-4462-516e-a675-8c9235c42994")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CGraphics__CImaging__CImageStream : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CGraphics__CImaging__CImageStream_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CGraphics__CImaging__CImageStream_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CGraphics__CImaging__CImageStream, "684165be-0011-56d6-bebf-430016d51b7a")

.comdef __FIAsyncOperation_1_Windows__CGraphics__CImaging__CImageStream : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CGraphics__CImaging__CPixelDataProvider_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CGraphics__CImaging__CPixelDataProvider_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CGraphics__CImaging__CPixelDataProvider, "37bdf4be-2f39-592c-a4f7-d16a09d2b2db")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CGraphics__CImaging__CPixelDataProvider : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CGraphics__CImaging__CPixelDataProvider_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CGraphics__CImaging__CPixelDataProvider_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CGraphics__CImaging__CPixelDataProvider, "8c2dfeb0-6c22-5863-88d8-85c1fbc75697")

.comdef __FIAsyncOperation_1_Windows__CGraphics__CImaging__CPixelDataProvider : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

.namespace Windows
.namespace Graphics
.namespace Imaging

define InterfaceName_Windows_Graphics_Imaging_IBitmapTransform <L"Windows.Graphics.Imaging.IBitmapTransform">

.enum BitmapPixelFormat {
    BitmapPixelFormat_Unknown	= 0,
    BitmapPixelFormat_Rgba16	= 12,
    BitmapPixelFormat_Rgba8	= 30,
    BitmapPixelFormat_Bgra8	= 87
    }

.enum BitmapAlphaMode {
    BitmapAlphaMode_Premultiplied	= 0,
    BitmapAlphaMode_Straight	= 1,
    BitmapAlphaMode_Ignore	= 2
    }

.enum BitmapInterpolationMode {
    BitmapInterpolationMode_NearestNeighbor	= 0,
    BitmapInterpolationMode_Linear	= 1,
    BitmapInterpolationMode_Cubic	= 2,
    BitmapInterpolationMode_Fant	= 3
    }

.enum BitmapFlip {
    BitmapFlip_None	= 0,
    BitmapFlip_Horizontal	= 1,
    BitmapFlip_Vertical = 2
    }

.enum BitmapRotation {
    BitmapRotation_None = 0,
    BitmapRotation_Clockwise90Degrees	= 1,
    BitmapRotation_Clockwise180Degrees	= 2,
    BitmapRotation_Clockwise270Degrees	= 3
    }

.enum ColorManagementMode {
    ColorManagementMode_DoNotColorManage	= 0,
    ColorManagementMode_ColorManageToSRgb	= 1
    }

.enum ExifOrientationMode {
    ExifOrientationMode_IgnoreExifOrientation	= 0,
    ExifOrientationMode_RespectExifOrientation	= 1
    }

.enum PngFilterMode {
    PngFilterMode_Automatic	= 0,
    PngFilterMode_None	= 1,
    PngFilterMode_Sub	= 2,
    PngFilterMode_Up	= 3,
    PngFilterMode_Average	= 4,
    PngFilterMode_Paeth = 5,
    PngFilterMode_Adaptive	= 6
    }

.enum TiffCompressionMode {
    TiffCompressionMode_Automatic	= 0,
    TiffCompressionMode_None	= 1,
    TiffCompressionMode_Ccitt3	= 2,
    TiffCompressionMode_Ccitt4	= 3,
    TiffCompressionMode_Lzw	= 4,
    TiffCompressionMode_Rle	= 5,
    TiffCompressionMode_Zip	= 6,
    TiffCompressionMode_LzwhDifferencing	= 7
    }

.enum JpegSubsamplingMode {
    JpegSubsamplingMode_Default = 0,
    JpegSubsamplingMode_Y4Cb2Cr0	= 1,
    JpegSubsamplingMode_Y4Cb2Cr2	= 2,
    JpegSubsamplingMode_Y4Cb4Cr4	= 3
    }

.template BitmapBounds
    X			UINT32 ?
    Y			UINT32 ?
    Width		UINT32 ?
    Height		UINT32 ?
   .ends

ifndef ____x_ABI_CWindows_CGraphics_CImaging_CIBitmapTransform_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGraphics_CImaging_CIBitmapTransform_INTERFACE_DEFINED__
DEFINE_IIDX(IBitmapTransform, "AE755344-E268-4D35-ADCF-E995D31A8D34")

.comdef IBitmapTransform : public IInspectable

    get_ScaledWidth	proc :ptr
    put_ScaledWidth	proc :UINT32
    get_ScaledHeight	proc :ptr
    put_ScaledHeight	proc :UINT32
    get_InterpolationMode proc :ptr
    put_InterpolationMode proc :Windows::Graphics::Imaging::BitmapInterpolationMode
    get_Flip		proc :ptr
    put_Flip		proc :Windows::Graphics::Imaging::BitmapFlip
    get_Rotation	proc :ptr
    put_Rotation	proc :Windows::Graphics::Imaging::BitmapRotation
    get_Bounds		proc :ptr
    put_Bounds		proc :Windows::Graphics::Imaging::BitmapBounds
   .ends

endif

ifndef ____x_ABI_CWindows_CGraphics_CImaging_CIBitmapTypedValue_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGraphics_CImaging_CIBitmapTypedValue_INTERFACE_DEFINED__
define InterfaceName_Windows_Graphics_Imaging_IBitmapTypedValue <L"Windows.Graphics.Imaging.IBitmapTypedValue">
DEFINE_IIDX(IBitmapTypedValue, "CD8044A9-2443-4000-B0CD-79316C56F589")

.comdef IBitmapTypedValue : public IInspectable

    get_Value		proc :ptr
    get_Type		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CGraphics_CImaging_CIBitmapTypedValueFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGraphics_CImaging_CIBitmapTypedValueFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Graphics_Imaging_IBitmapTypedValueFactory <L"Windows.Graphics.Imaging.IBitmapTypedValueFactory">
DEFINE_IIDX(IBitmapTypedValueFactory, "92DBB599-CE13-46BB-9545-CB3A3F63EB8B")

.comdef IBitmapTypedValueFactory : public IInspectable

    Create		proc :ptr, :Windows::Foundation::PropertyType, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CGraphics_CImaging_CIBitmapPropertiesView_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGraphics_CImaging_CIBitmapPropertiesView_INTERFACE_DEFINED__
define InterfaceName_Windows_Graphics_Imaging_IBitmapPropertiesView <L"Windows.Graphics.Imaging.IBitmapPropertiesView">
DEFINE_IIDX(IBitmapPropertiesView, "7E0FE87A-3A70-48F8-9C55-196CF5A545F5")

.comdef IBitmapPropertiesView : public IInspectable

    GetPropertiesAsync	proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CGraphics_CImaging_CIBitmapProperties_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGraphics_CImaging_CIBitmapProperties_INTERFACE_DEFINED__
define InterfaceName_Windows_Graphics_Imaging_IBitmapProperties <L"Windows.Graphics.Imaging.IBitmapProperties">
DEFINE_IIDX(IBitmapProperties, "EA9F4F1B-B505-4450-A4D1-E8CA94529D8D")

.comdef IBitmapProperties : public IInspectable

    SetPropertiesAsync	proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CGraphics_CImaging_CIPixelDataProvider_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGraphics_CImaging_CIPixelDataProvider_INTERFACE_DEFINED__
define InterfaceName_Windows_Graphics_Imaging_IPixelDataProvider <L"Windows.Graphics.Imaging.IPixelDataProvider">
DEFINE_IIDX(IPixelDataProvider, "DD831F25-185C-4595-9FB9-CCBE6EC18A6F")

.comdef IPixelDataProvider : public IInspectable

    DetachPixelData	proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CGraphics_CImaging_CIBitmapFrame_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGraphics_CImaging_CIBitmapFrame_INTERFACE_DEFINED__
define InterfaceName_Windows_Graphics_Imaging_IBitmapFrame <L"Windows.Graphics.Imaging.IBitmapFrame">
DEFINE_IIDX(IBitmapFrame, "72A49A1C-8081-438D-91BC-94ECFC8185C6")

.comdef IBitmapFrame : public IInspectable

    GetThumbnailAsync	proc :ptr
    get_BitmapProperties proc :ptr
    get_BitmapPixelFormat proc :ptr
    get_BitmapAlphaMode proc :ptr
    get_DpiX		proc :ptr
    get_DpiY		proc :ptr
    get_PixelWidth	proc :ptr
    get_PixelHeight	proc :ptr
    get_OrientedPixelWidth proc :ptr
    get_OrientedPixelHeight proc :ptr
    GetPixelDataAsync	proc :ptr
    GetPixelDataTransformedAsync proc :Windows::Graphics::Imaging::BitmapPixelFormat, :Windows::Graphics::Imaging::BitmapAlphaMode, :ptr, :Windows::Graphics::Imaging::ExifOrientationMode, :Windows::Graphics::Imaging::ColorManagementMode, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CGraphics_CImaging_CIBitmapCodecInformation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGraphics_CImaging_CIBitmapCodecInformation_INTERFACE_DEFINED__
define InterfaceName_Windows_Graphics_Imaging_IBitmapCodecInformation <L"Windows.Graphics.Imaging.IBitmapCodecInformation">
DEFINE_IIDX(IBitmapCodecInformation, "400CAAF2-C4B0-4392-A3B0-6F6F9BA95CB4")

.comdef IBitmapCodecInformation : public IInspectable

    get_CodecId		proc :ptr
    get_FileExtensions	proc :ptr
    get_FriendlyName	proc :ptr
    get_MimeTypes	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CGraphics_CImaging_CIBitmapDecoderStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGraphics_CImaging_CIBitmapDecoderStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Graphics_Imaging_IBitmapDecoderStatics <L"Windows.Graphics.Imaging.IBitmapDecoderStatics">
DEFINE_IIDX(IBitmapDecoderStatics, "438CCB26-BCEF-4E95-BAD6-23A822E58D01")

.comdef IBitmapDecoderStatics : public IInspectable

    get_BmpDecoderId	proc :ptr
    get_JpegDecoderId	proc :ptr
    get_PngDecoderId	proc :ptr
    get_TiffDecoderId	proc :ptr
    get_GifDecoderId	proc :ptr
    get_JpegXRDecoderId proc :ptr
    get_IcoDecoderId	proc :ptr
    GetDecoderInformationEnumerator proc :ptr
    CreateAsync		proc :ptr, :ptr
    CreateWithIdAsync	proc :GUID, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CGraphics_CImaging_CIBitmapDecoder_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGraphics_CImaging_CIBitmapDecoder_INTERFACE_DEFINED__
define InterfaceName_Windows_Graphics_Imaging_IBitmapDecoder <L"Windows.Graphics.Imaging.IBitmapDecoder">
DEFINE_IIDX(IBitmapDecoder, "ACEF22BA-1D74-4C91-9DFC-9620745233E6")

.comdef IBitmapDecoder : public IInspectable

    get_BitmapContainerProperties proc :ptr
    get_DecoderInformation proc :ptr
    get_FrameCount	proc :ptr
    GetPreviewAsync	proc :ptr
    GetFrameAsync	proc :UINT32, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CGraphics_CImaging_CIBitmapEncoderStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGraphics_CImaging_CIBitmapEncoderStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Graphics_Imaging_IBitmapEncoderStatics <L"Windows.Graphics.Imaging.IBitmapEncoderStatics">
DEFINE_IIDX(IBitmapEncoderStatics, "A74356A7-A4E4-4EB9-8E40-564DE7E1CCB2")

.comdef IBitmapEncoderStatics : public IInspectable

    get_BmpEncoderId	proc :ptr
    get_JpegEncoderId	proc :ptr
    get_PngEncoderId	proc :ptr
    get_TiffEncoderId	proc :ptr
    get_GifEncoderId	proc :ptr
    get_JpegXREncoderId proc :ptr
    GetEncoderInformationEnumerator proc :ptr
    CreateAsync		proc :GUID, :ptr, :ptr
    CreateWithEncodingOptionsAsync proc :GUID, :ptr, :ptr, :ptr
    CreateForTranscodingAsync proc :ptr, :ptr, :ptr
    CreateForInPlacePropertyEncodingAsync proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CGraphics_CImaging_CIBitmapEncoder_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGraphics_CImaging_CIBitmapEncoder_INTERFACE_DEFINED__
define InterfaceName_Windows_Graphics_Imaging_IBitmapEncoder <L"Windows.Graphics.Imaging.IBitmapEncoder">
DEFINE_IIDX(IBitmapEncoder, "2BC468E3-E1F8-4B54-95E8-32919551CE62")

.comdef IBitmapEncoder : public IInspectable

    get_EncoderInformation proc :ptr
    get_BitmapProperties proc :ptr
    get_BitmapContainerProperties proc :ptr
    get_IsThumbnailGenerated proc :ptr
    put_IsThumbnailGenerated proc :boolean
    get_GeneratedThumbnailWidth proc :ptr
    put_GeneratedThumbnailWidth proc :UINT32
    get_GeneratedThumbnailHeight proc :ptr
    put_GeneratedThumbnailHeight proc :UINT32
    get_BitmapTransform proc :ptr
    SetPixelData	proc :Windows::Graphics::Imaging::BitmapPixelFormat, :Windows::Graphics::Imaging::BitmapAlphaMode, :UINT32, :UINT32, :DOUBLE, :DOUBLE, :UINT32, :ptr
    GoToNextFrameAsync	proc :ptr
    GoToNextFrameWithEncodingOptionsAsync proc :ptr, :ptr
    FlushAsync		proc :ptr
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_Graphics_Imaging_BitmapTransform_DEFINED
define RUNTIMECLASS_Windows_Graphics_Imaging_BitmapTransform_DEFINED
define RuntimeClass_Windows_Graphics_Imaging_BitmapTransform <L"Windows.Graphics.Imaging.BitmapTransform">
endif
ifndef RUNTIMECLASS_Windows_Graphics_Imaging_BitmapTypedValue_DEFINED
define RUNTIMECLASS_Windows_Graphics_Imaging_BitmapTypedValue_DEFINED
define RuntimeClass_Windows_Graphics_Imaging_BitmapTypedValue <L"Windows.Graphics.Imaging.BitmapTypedValue">
endif
ifndef RUNTIMECLASS_Windows_Graphics_Imaging_BitmapPropertySet_DEFINED
define RUNTIMECLASS_Windows_Graphics_Imaging_BitmapPropertySet_DEFINED
define RuntimeClass_Windows_Graphics_Imaging_BitmapPropertySet <L"Windows.Graphics.Imaging.BitmapPropertySet">
endif
ifndef RUNTIMECLASS_Windows_Graphics_Imaging_BitmapPropertiesView_DEFINED
define RUNTIMECLASS_Windows_Graphics_Imaging_BitmapPropertiesView_DEFINED
define RuntimeClass_Windows_Graphics_Imaging_BitmapPropertiesView <L"Windows.Graphics.Imaging.BitmapPropertiesView">
endif
ifndef RUNTIMECLASS_Windows_Graphics_Imaging_BitmapProperties_DEFINED
define RUNTIMECLASS_Windows_Graphics_Imaging_BitmapProperties_DEFINED
define RuntimeClass_Windows_Graphics_Imaging_BitmapProperties <L"Windows.Graphics.Imaging.BitmapProperties">
endif
ifndef RUNTIMECLASS_Windows_Graphics_Imaging_PixelDataProvider_DEFINED
define RUNTIMECLASS_Windows_Graphics_Imaging_PixelDataProvider_DEFINED
define RuntimeClass_Windows_Graphics_Imaging_PixelDataProvider <L"Windows.Graphics.Imaging.PixelDataProvider">
endif
ifndef RUNTIMECLASS_Windows_Graphics_Imaging_ImageStream_DEFINED
define RUNTIMECLASS_Windows_Graphics_Imaging_ImageStream_DEFINED
define RuntimeClass_Windows_Graphics_Imaging_ImageStream <L"Windows.Graphics.Imaging.ImageStream">
endif
ifndef RUNTIMECLASS_Windows_Graphics_Imaging_BitmapFrame_DEFINED
define RUNTIMECLASS_Windows_Graphics_Imaging_BitmapFrame_DEFINED
define RuntimeClass_Windows_Graphics_Imaging_BitmapFrame <L"Windows.Graphics.Imaging.BitmapFrame">
endif
ifndef RUNTIMECLASS_Windows_Graphics_Imaging_BitmapCodecInformation_DEFINED
define RUNTIMECLASS_Windows_Graphics_Imaging_BitmapCodecInformation_DEFINED
define RuntimeClass_Windows_Graphics_Imaging_BitmapCodecInformation <L"Windows.Graphics.Imaging.BitmapCodecInformation">
endif
ifndef RUNTIMECLASS_Windows_Graphics_Imaging_BitmapDecoder_DEFINED
define RUNTIMECLASS_Windows_Graphics_Imaging_BitmapDecoder_DEFINED
define RuntimeClass_Windows_Graphics_Imaging_BitmapDecoder <L"Windows.Graphics.Imaging.BitmapDecoder">
endif
ifndef RUNTIMECLASS_Windows_Graphics_Imaging_BitmapEncoder_DEFINED
define RUNTIMECLASS_Windows_Graphics_Imaging_BitmapEncoder_DEFINED
define RuntimeClass_Windows_Graphics_Imaging_BitmapEncoder <L"Windows.Graphics.Imaging.BitmapEncoder">
endif

endif
