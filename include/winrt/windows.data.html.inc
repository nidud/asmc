ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Edata2Ehtml_h__
define __windows2Edata2Ehtml_h__
ifndef __windows2Efoundation_h__
include Windows.Foundation.inc
endif

.namespace Windows
.namespace Data
.namespace Html

ifndef ____x_ABI_CWindows_CData_CHtml_CIHtmlUtilities_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CData_CHtml_CIHtmlUtilities_INTERFACE_DEFINED__
define InterfaceName_Windows_Data_Html_IHtmlUtilities <L"Windows.Data.Html.IHtmlUtilities">

DEFINE_IIDX(IHtmlUtilities, "FEC00ADD-2399-4FAC-B5A7-05E9ACD7181D")

.comdef IHtmlUtilities : public IInspectable

    ConvertToText       proc :HSTRING, :ptr
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_Data_Html_HtmlUtilities_DEFINED
define RUNTIMECLASS_Windows_Data_Html_HtmlUtilities_DEFINED
define RuntimeClass_Windows_Data_Html_HtmlUtilities <L"Windows.Data.Html.HtmlUtilities">
endif

endif
