ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Edata2Epdf_h__
define __windows2Edata2Epdf_h__
ifndef __windows2Efoundation_h__
include Windows.Foundation.inc
endif
include Windows.Storage.inc
include Windows.UI.inc

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CData__CPdf__CPdfDocument_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CData__CPdf__CPdfDocument_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CData__CPdf__CPdfDocument, "8d4950b3-629d-5d7d-84cc-04c0dcf7942b")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CData__CPdf__CPdfDocument : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CData__CPdf__CPdfDocument_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CData__CPdf__CPdfDocument_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CData__CPdf__CPdfDocument, "d6b166ec-099a-5ee2-ad2e-f4c88614aabb")

.comdef __FIAsyncOperation_1_Windows__CData__CPdf__CPdfDocument : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

.namespace Windows
.namespace Data
.namespace Pdf

.enum PdfPageRotation {
    PdfPageRotation_Normal	= 0,
    PdfPageRotation_Rotate90	= 1,
    PdfPageRotation_Rotate180	= 2,
    PdfPageRotation_Rotate270	= 3
    }

ifndef ____x_ABI_CWindows_CData_CPdf_CIPdfPageDimensions_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CData_CPdf_CIPdfPageDimensions_INTERFACE_DEFINED__
define InterfaceName_Windows_Data_Pdf_IPdfPageDimensions <L"Windows.Data.Pdf.IPdfPageDimensions">
DEFINE_IIDX(IPdfPageDimensions, "22170471-313E-44E8-835D-63A3E7624A10")

.comdef IPdfPageDimensions : public IInspectable

    get_MediaBox	proc :ptr
    get_CropBox		proc :ptr
    get_BleedBox	proc :ptr
    get_TrimBox		proc :ptr
    get_ArtBox		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CData_CPdf_CIPdfPageRenderOptions_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CData_CPdf_CIPdfPageRenderOptions_INTERFACE_DEFINED__
define InterfaceName_Windows_Data_Pdf_IPdfPageRenderOptions <L"Windows.Data.Pdf.IPdfPageRenderOptions">
DEFINE_IIDX(IPdfPageRenderOptions, "3C98056F-B7CF-4C29-9A04-52D90267F425")

.comdef IPdfPageRenderOptions : public IInspectable

    get_SourceRect	proc :ptr
    put_SourceRect	proc :ptr
    get_DestinationWidth proc :ptr
    put_DestinationWidth proc :UINT32
    get_DestinationHeight proc :ptr
    put_DestinationHeight proc :UINT32
    get_BackgroundColor proc :ptr
    put_BackgroundColor proc :Windows::UI::Color
    get_IsIgnoringHighContrast proc :ptr
    put_IsIgnoringHighContrast proc :boolean
    get_BitmapEncoderId proc :ptr
    put_BitmapEncoderId proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CData_CPdf_CIPdfPage_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CData_CPdf_CIPdfPage_INTERFACE_DEFINED__
define InterfaceName_Windows_Data_Pdf_IPdfPage <L"Windows.Data.Pdf.IPdfPage">
DEFINE_IIDX(IPdfPage, "9DB4B0C8-5320-4CFC-AD76-493FDAD0E594")

.comdef IPdfPage : public IInspectable

    RenderToStreamAsync proc :ptr, :ptr
    RenderWithOptionsToStreamAsync proc :ptr, :ptr, :ptr
    PreparePageAsync	proc :ptr
    get_Index		proc :ptr
    get_Size		proc :ptr
    get_Dimensions	proc :ptr
    get_Rotation	proc :ptr
    get_PreferredZoom	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CData_CPdf_CIPdfDocument_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CData_CPdf_CIPdfDocument_INTERFACE_DEFINED__
define InterfaceName_Windows_Data_Pdf_IPdfDocument <L"Windows.Data.Pdf.IPdfDocument">
DEFINE_IIDX(IPdfDocument, "AC7EBEDD-80FA-4089-846E-81B77FF5A86C")

.comdef IPdfDocument : public IInspectable

    GetPage		proc :UINT32, :ptr
    get_PageCount	proc :ptr
    get_IsPasswordProtected proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CData_CPdf_CIPdfDocumentStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CData_CPdf_CIPdfDocumentStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Data_Pdf_IPdfDocumentStatics <L"Windows.Data.Pdf.IPdfDocumentStatics">
DEFINE_IIDX(IPdfDocumentStatics, "433A0B5F-C007-4788-90F2-08143D922599")

.comdef IPdfDocumentStatics : public IInspectable

    LoadFromFileAsync	proc :ptr, :ptr
    LoadFromFileWithPasswordAsync proc :ptr, :HSTRING, :ptr
    LoadFromStreamAsync proc :ptr, :ptr
    LoadFromStreamWithPasswordAsync proc :ptr, :HSTRING, :ptr
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_Data_Pdf_PdfPageRenderOptions_DEFINED
define RUNTIMECLASS_Windows_Data_Pdf_PdfPageRenderOptions_DEFINED
define RuntimeClass_Windows_Data_Pdf_PdfPageRenderOptions <L"Windows.Data.Pdf.PdfPageRenderOptions">
endif
ifndef RUNTIMECLASS_Windows_Data_Pdf_PdfPageDimensions_DEFINED
define RUNTIMECLASS_Windows_Data_Pdf_PdfPageDimensions_DEFINED
define RuntimeClass_Windows_Data_Pdf_PdfPageDimensions <L"Windows.Data.Pdf.PdfPageDimensions">
endif
ifndef RUNTIMECLASS_Windows_Data_Pdf_PdfPage_DEFINED
define RUNTIMECLASS_Windows_Data_Pdf_PdfPage_DEFINED
define RuntimeClass_Windows_Data_Pdf_PdfPage <L"Windows.Data.Pdf.PdfPage">
endif
ifndef RUNTIMECLASS_Windows_Data_Pdf_PdfDocument_DEFINED
define RUNTIMECLASS_Windows_Data_Pdf_PdfDocument_DEFINED
define RuntimeClass_Windows_Data_Pdf_PdfDocument <L"Windows.Data.Pdf.PdfDocument">
endif

endif

