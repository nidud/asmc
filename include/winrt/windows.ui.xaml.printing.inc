ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Eui2Examl2Eprinting_h__
define __windows2Eui2Examl2Eprinting_h__
ifndef __windows2Efoundation_h__
include Windows.Foundation.inc
endif
include Windows.Graphics.Printing.inc
include Windows.UI.Xaml.inc

.namespace Windows
.namespace UI
.namespace Xaml
.namespace Printing

.enum PreviewPageCountType {
    PreviewPageCountType_Final  = 0,
    PreviewPageCountType_Intermediate   = 1
    }

ifndef ____x_ABI_CWindows_CUI_CXaml_CPrinting_CIAddPagesEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CPrinting_CIAddPagesEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IAddPagesEventHandler, "D4B57970-57A0-4209-847C-C093B54BC729")

.comdef IAddPagesEventHandler : public IUnknown

    _Invoke             proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CPrinting_CIGetPreviewPageEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CPrinting_CIGetPreviewPageEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IGetPreviewPageEventHandler, "CCB3E9ED-9C11-4E50-AB49-E98086BBFDEF")

.comdef IGetPreviewPageEventHandler : public IUnknown

    _Invoke             proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CPrinting_CIPaginateEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CPrinting_CIPaginateEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IPaginateEventHandler, "0CC05B61-811B-4A32-9965-13EB78DBB01B")

.comdef IPaginateEventHandler : public IUnknown

    _Invoke             proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CPrinting_CIAddPagesEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CPrinting_CIAddPagesEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Printing_IAddPagesEventArgs <L"Windows.UI.Xaml.Printing.IAddPagesEventArgs">
DEFINE_IIDX(IAddPagesEventArgs, "E2E52BE5-056C-4420-9795-CB3526CE0C20")

.comdef IAddPagesEventArgs : public IInspectable

    get_PrintTaskOptions proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CPrinting_CIGetPreviewPageEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CPrinting_CIGetPreviewPageEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Printing_IGetPreviewPageEventArgs <L"Windows.UI.Xaml.Printing.IGetPreviewPageEventArgs">
DEFINE_IIDX(IGetPreviewPageEventArgs, "A43D703D-DEA9-4DF6-A7ED-35049CD485C7")

.comdef IGetPreviewPageEventArgs : public IInspectable

    get_PageNumber      proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CPrinting_CIPaginateEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CPrinting_CIPaginateEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Printing_IPaginateEventArgs <L"Windows.UI.Xaml.Printing.IPaginateEventArgs">
DEFINE_IIDX(IPaginateEventArgs, "ED945FD6-79AB-42B7-930A-3D6E09011D21")

.comdef IPaginateEventArgs : public IInspectable

    get_PrintTaskOptions proc :ptr
    get_CurrentPreviewPageNumber proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CPrinting_CIPrintDocument_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CPrinting_CIPrintDocument_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Printing_IPrintDocument <L"Windows.UI.Xaml.Printing.IPrintDocument">
DEFINE_IIDX(IPrintDocument, "E44327C3-A999-485B-B1D8-72DC517821E6")

.comdef IPrintDocument : public IInspectable

    get_DocumentSource  proc :ptr
    add_Paginate        proc :ptr, :ptr
    remove_Paginate     proc :EventRegistrationToken
    add_GetPreviewPage  proc :ptr, :ptr
    remove_GetPreviewPage proc :EventRegistrationToken
    add_AddPages        proc :ptr, :ptr
    remove_AddPages     proc :EventRegistrationToken
    AddPage             proc :ptr
    AddPagesComplete    proc
    SetPreviewPageCount proc :INT32, :Windows::UI::Xaml::Printing::PreviewPageCountType
    SetPreviewPage      proc :INT32, :ptr
    InvalidatePreview   proc
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CPrinting_CIPrintDocumentStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CPrinting_CIPrintDocumentStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Printing_IPrintDocumentStatics <L"Windows.UI.Xaml.Printing.IPrintDocumentStatics">
DEFINE_IIDX(IPrintDocumentStatics, "FD970A3C-B152-49E0-A6BD-6AA6477E43C7")

.comdef IPrintDocumentStatics : public IInspectable

    get_DocumentSourceProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CPrinting_CIPrintDocumentFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CPrinting_CIPrintDocumentFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Printing_IPrintDocumentFactory <L"Windows.UI.Xaml.Printing.IPrintDocumentFactory">
DEFINE_IIDX(IPrintDocumentFactory, "FB87B18F-2606-4A2F-99D4-A7CDBC35D7C7")

.comdef IPrintDocumentFactory : public IInspectable

    CreateInstance      proc :ptr, :ptr, :ptr
   .ends

endif

.endn
.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_UI_Xaml_Printing_AddPagesEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Printing_AddPagesEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_Printing_AddPagesEventArgs <L"Windows.UI.Xaml.Printing.AddPagesEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Printing_GetPreviewPageEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Printing_GetPreviewPageEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_Printing_GetPreviewPageEventArgs <L"Windows.UI.Xaml.Printing.GetPreviewPageEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Printing_PaginateEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Printing_PaginateEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_Printing_PaginateEventArgs <L"Windows.UI.Xaml.Printing.PaginateEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Printing_PrintDocument_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Printing_PrintDocument_DEFINED
define RuntimeClass_Windows_UI_Xaml_Printing_PrintDocument <L"Windows.UI.Xaml.Printing.PrintDocument">
endif

endif
