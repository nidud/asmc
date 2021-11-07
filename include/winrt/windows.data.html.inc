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

ifndef __windows2Edata2Ehtml_h__
define __windows2Edata2Ehtml_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc

.namespace Windows
.namespace Data
.namespace Html

ifndef ____x_ABI_CWindows_CData_CHtml_CIHtmlUtilities_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CData_CHtml_CIHtmlUtilities_INTERFACE_DEFINED__
define InterfaceName_Windows_Data_Html_IHtmlUtilities <L"Windows.Data.Html.IHtmlUtilities">

DEFINE_IIDX(IHtmlUtilities, "FEC00ADD-2399-4FAC-B5A7-05E9ACD7181D")

.comdef IHtmlUtilities : public IInspectable

    ConvertToText       proc :HSTRING, :ptr HSTRING
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
