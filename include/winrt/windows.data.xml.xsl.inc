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

ifndef __windows2Edata2Exml2Exsl_h__
define __windows2Edata2Exml2Exsl_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include Windows.Data.Xml.Dom.inc

.namespace Windows
.namespace Data
.namespace Xml
.namespace Xsl

ifndef ____x_ABI_CWindows_CData_CXml_CXsl_CIXsltProcessor_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CData_CXml_CXsl_CIXsltProcessor_INTERFACE_DEFINED__
DEFINE_IIDX(IXsltProcessor, "7B64703F-550C-48C6-A90F-93A5B964518F")

.comdef IXsltProcessor : public IInspectable

    TransformToString   proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CData_CXml_CXsl_CIXsltProcessorFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CData_CXml_CXsl_CIXsltProcessorFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Data_Xml_Xsl_IXsltProcessorFactory <L"Windows.Data.Xml.Xsl.IXsltProcessorFactory">
DEFINE_IIDX(IXsltProcessorFactory, "274146C0-9A51-4663-BF30-0EF742146F20")

.comdef IXsltProcessorFactory : public IInspectable

    CreateInstance      proc :ptr, :ptr
   .ends

endif

.endn
.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_Data_Xml_Xsl_XsltProcessor_DEFINED
define RUNTIMECLASS_Windows_Data_Xml_Xsl_XsltProcessor_DEFINED
define RuntimeClass_Windows_Data_Xml_Xsl_XsltProcessor <L"Windows.Data.Xml.Xsl.XsltProcessor">
endif

endif
