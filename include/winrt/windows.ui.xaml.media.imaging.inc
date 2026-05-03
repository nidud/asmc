ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Eui2Examl2Emedia2Eimaging_h__
define __windows2Eui2Examl2Emedia2Eimaging_h__
ifndef __windows2Efoundation_h__
include Windows.Foundation.inc
endif
include Windows.Storage.Streams.inc
include Windows.UI.Xaml.inc

.namespace Windows
.namespace UI
.namespace Xaml
.namespace Media
.namespace Imaging

.enum BitmapCreateOptions {
    BitmapCreateOptions_None	= 0,
    BitmapCreateOptions_IgnoreImageCache = 0x8
    }

.enum DecodePixelType {
    DecodePixelType_Physical	= 0,
    DecodePixelType_Logical	= 1
    }

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CImaging_CIDownloadProgressEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CImaging_CIDownloadProgressEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IDownloadProgressEventHandler, "1ABAEE23-74EE-4CC7-99BA-B171E3CDA61E")

.comdef IDownloadProgressEventHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CImaging_CIBitmapImage_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CImaging_CIBitmapImage_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Imaging_IBitmapImage <L"Windows.UI.Xaml.Media.Imaging.IBitmapImage">
DEFINE_IIDX(IBitmapImage, "31AF3271-E3B4-442D-A341-4C0226B2725B")

.comdef IBitmapImage : public IInspectable

    get_CreateOptions	proc :ptr
    put_CreateOptions	proc :Windows::UI::Xaml::Media::Imaging::BitmapCreateOptions
    get_UriSource	proc :ptr
    put_UriSource	proc :ptr
    get_DecodePixelWidth proc :ptr
    put_DecodePixelWidth proc :INT32
    get_DecodePixelHeight proc :ptr
    put_DecodePixelHeight proc :INT32
    add_DownloadProgress proc :ptr, :ptr
    remove_DownloadProgress proc :EventRegistrationToken
    add_ImageOpened	proc :ptr, :ptr
    remove_ImageOpened	proc :EventRegistrationToken
    add_ImageFailed	proc :ptr, :ptr
    remove_ImageFailed	proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CImaging_CIBitmapImageStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CImaging_CIBitmapImageStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Imaging_IBitmapImageStatics <L"Windows.UI.Xaml.Media.Imaging.IBitmapImageStatics">
DEFINE_IIDX(IBitmapImageStatics, "9E282143-70E8-437C-9FA4-2CBF295CFF84")

.comdef IBitmapImageStatics : public IInspectable

    get_CreateOptionsProperty proc :ptr
    get_UriSourceProperty proc :ptr
    get_DecodePixelWidthProperty proc :ptr
    get_DecodePixelHeightProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CImaging_CIBitmapImageFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CImaging_CIBitmapImageFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Imaging_IBitmapImageFactory <L"Windows.UI.Xaml.Media.Imaging.IBitmapImageFactory">
DEFINE_IIDX(IBitmapImageFactory, "C9132978-4810-4E5E-8087-03671EE60D85")

.comdef IBitmapImageFactory : public IInspectable

    CreateInstanceWithUriSource proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CImaging_CIBitmapImage2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CImaging_CIBitmapImage2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Imaging_IBitmapImage2 <L"Windows.UI.Xaml.Media.Imaging.IBitmapImage2">
DEFINE_IIDX(IBitmapImage2, "1069C1B6-8C9B-4762-BE3D-759F5698F2B3")

.comdef IBitmapImage2 : public IInspectable

    get_DecodePixelType proc :ptr
    put_DecodePixelType proc :Windows::UI::Xaml::Media::Imaging::DecodePixelType
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CImaging_CIBitmapImageStatics2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CImaging_CIBitmapImageStatics2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Imaging_IBitmapImageStatics2 <L"Windows.UI.Xaml.Media.Imaging.IBitmapImageStatics2">
DEFINE_IIDX(IBitmapImageStatics2, "C5F5576A-75AF-41A4-B893-8FE91FEE2882")

.comdef IBitmapImageStatics2 : public IInspectable

    get_DecodePixelTypeProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CImaging_CIBitmapSource_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CImaging_CIBitmapSource_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Imaging_IBitmapSource <L"Windows.UI.Xaml.Media.Imaging.IBitmapSource">
DEFINE_IIDX(IBitmapSource, "23D86411-202F-41B2-8C5B-A8A3B333800B")

.comdef IBitmapSource : public IInspectable

    get_PixelWidth	proc :ptr
    get_PixelHeight	proc :ptr
    SetSource		proc :ptr
    SetSourceAsync	proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CImaging_CIBitmapSourceStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CImaging_CIBitmapSourceStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Imaging_IBitmapSourceStatics <L"Windows.UI.Xaml.Media.Imaging.IBitmapSourceStatics">
DEFINE_IIDX(IBitmapSourceStatics, "9A9C9981-827B-4E51-891B-8A15B511842D")

.comdef IBitmapSourceStatics : public IInspectable

    get_PixelWidthProperty proc :ptr
    get_PixelHeightProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CImaging_CIBitmapSourceFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CImaging_CIBitmapSourceFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Imaging_IBitmapSourceFactory <L"Windows.UI.Xaml.Media.Imaging.IBitmapSourceFactory">
DEFINE_IIDX(IBitmapSourceFactory, "E240420E-D4A7-49A4-A0B4-A59FDD77E508")

.comdef IBitmapSourceFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CImaging_CIDownloadProgressEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CImaging_CIDownloadProgressEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Imaging_IDownloadProgressEventArgs <L"Windows.UI.Xaml.Media.Imaging.IDownloadProgressEventArgs">
DEFINE_IIDX(IDownloadProgressEventArgs, "7311E0D4-FE94-4E70-9B90-CDD47AC23AFB")

.comdef IDownloadProgressEventArgs : public IInspectable

    get_Progress	proc :ptr
    put_Progress	proc :INT32
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CImaging_CIRenderTargetBitmap_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CImaging_CIRenderTargetBitmap_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Imaging_IRenderTargetBitmap <L"Windows.UI.Xaml.Media.Imaging.IRenderTargetBitmap">
DEFINE_IIDX(IRenderTargetBitmap, "500DEE81-893C-4C0A-8FEC-4678AC717589")

.comdef IRenderTargetBitmap : public IInspectable

    get_PixelWidth	proc :ptr
    get_PixelHeight	proc :ptr
    RenderAsync		proc :ptr, :ptr
    RenderToSizeAsync	proc :ptr, :INT32, :INT32, :ptr
    GetPixelsAsync	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CImaging_CIRenderTargetBitmapStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CImaging_CIRenderTargetBitmapStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Imaging_IRenderTargetBitmapStatics <L"Windows.UI.Xaml.Media.Imaging.IRenderTargetBitmapStatics">
DEFINE_IIDX(IRenderTargetBitmapStatics, "F0A1EFEE-C131-4D40-9C47-F7D7CF2B077F")

.comdef IRenderTargetBitmapStatics : public IInspectable

    get_PixelWidthProperty proc :ptr
    get_PixelHeightProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CImaging_CISurfaceImageSource_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CImaging_CISurfaceImageSource_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Imaging_ISurfaceImageSource <L"Windows.UI.Xaml.Media.Imaging.ISurfaceImageSource">
DEFINE_IIDX(ISurfaceImageSource, "62F7D416-C714-4C4C-8273-F839BC58135C")

.comdef ISurfaceImageSource : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CImaging_CISurfaceImageSourceFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CImaging_CISurfaceImageSourceFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Imaging_ISurfaceImageSourceFactory <L"Windows.UI.Xaml.Media.Imaging.ISurfaceImageSourceFactory">
DEFINE_IIDX(ISurfaceImageSourceFactory, "3AB2212A-EF65-4A5F-BFAC-73993E8C12C9")

.comdef ISurfaceImageSourceFactory : public IInspectable

    CreateInstanceWithDimensions proc :INT32, :INT32, :ptr, :ptr, :ptr
    CreateInstanceWithDimensionsAndOpacity proc :INT32, :INT32, :boolean, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CImaging_CIVirtualSurfaceImageSource_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CImaging_CIVirtualSurfaceImageSource_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Imaging_IVirtualSurfaceImageSource <L"Windows.UI.Xaml.Media.Imaging.IVirtualSurfaceImageSource">
DEFINE_IIDX(IVirtualSurfaceImageSource, "4A711FEA-BFAC-11E0-A06A-9DE44724019B")

.comdef IVirtualSurfaceImageSource : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CImaging_CIVirtualSurfaceImageSourceFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CImaging_CIVirtualSurfaceImageSourceFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Imaging_IVirtualSurfaceImageSourceFactory <L"Windows.UI.Xaml.Media.Imaging.IVirtualSurfaceImageSourceFactory">
DEFINE_IIDX(IVirtualSurfaceImageSourceFactory, "3AB2212A-BFAC-11E0-8A92-69E44724019B")

.comdef IVirtualSurfaceImageSourceFactory : public IInspectable

    CreateInstanceWithDimensions proc :INT32, :INT32, :ptr
    CreateInstanceWithDimensionsAndOpacity proc :INT32, :INT32, :boolean, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CImaging_CIWriteableBitmap_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CImaging_CIWriteableBitmap_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Imaging_IWriteableBitmap <L"Windows.UI.Xaml.Media.Imaging.IWriteableBitmap">
DEFINE_IIDX(IWriteableBitmap, "BF0B7E6F-DF7C-4A85-8413-A1216285835C")

.comdef IWriteableBitmap : public IInspectable

    get_PixelBuffer	proc :ptr
    Invalidate		proc
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CImaging_CIWriteableBitmapFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CImaging_CIWriteableBitmapFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Imaging_IWriteableBitmapFactory <L"Windows.UI.Xaml.Media.Imaging.IWriteableBitmapFactory">
DEFINE_IIDX(IWriteableBitmapFactory, "5563EBB1-3EF2-42C5-9C6D-1CF5DCC041FF")

.comdef IWriteableBitmapFactory : public IInspectable

    CreateInstanceWithDimensions proc :INT32, :INT32, :ptr
   .ends

endif

.endn
.endn
.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Imaging_DownloadProgressEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Imaging_DownloadProgressEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Imaging_DownloadProgressEventArgs <L"Windows.UI.Xaml.Media.Imaging.DownloadProgressEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Imaging_BitmapSource_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Imaging_BitmapSource_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Imaging_BitmapSource <L"Windows.UI.Xaml.Media.Imaging.BitmapSource">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Imaging_BitmapImage_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Imaging_BitmapImage_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Imaging_BitmapImage <L"Windows.UI.Xaml.Media.Imaging.BitmapImage">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Imaging_RenderTargetBitmap_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Imaging_RenderTargetBitmap_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Imaging_RenderTargetBitmap <L"Windows.UI.Xaml.Media.Imaging.RenderTargetBitmap">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Imaging_SurfaceImageSource_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Imaging_SurfaceImageSource_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Imaging_SurfaceImageSource <L"Windows.UI.Xaml.Media.Imaging.SurfaceImageSource">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Imaging_VirtualSurfaceImageSource_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Imaging_VirtualSurfaceImageSource_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Imaging_VirtualSurfaceImageSource <L"Windows.UI.Xaml.Media.Imaging.VirtualSurfaceImageSource">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Imaging_WriteableBitmap_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Imaging_WriteableBitmap_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Imaging_WriteableBitmap <L"Windows.UI.Xaml.Media.Imaging.WriteableBitmap">
endif

endif
