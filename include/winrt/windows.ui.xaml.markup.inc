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

ifndef __windows2Eui2Examl2Emarkup_h__
define __windows2Eui2Examl2Emarkup_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include Windows.Storage.Streams.inc
include Windows.UI.Xaml.Interop.inc
include windows.foundation.collections.inc

.namespace Windows
.namespace UI
.namespace Xaml
.namespace Markup

.template XmlnsDefinition
    XmlNamespace        HSTRING ?
    Namespace           HSTRING ?
   .ends

.template XamlBinaryWriterErrorInformation
    InputStreamIndex    UINT32 ?
    LineNumber          UINT32 ?
    LinePosition        UINT32 ?
   .ends

ifndef ____x_ABI_CWindows_CUI_CXaml_CMarkup_CIXamlReader_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMarkup_CIXamlReader_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Markup_IXamlReader <L"Windows.UI.Xaml.Markup.IXamlReader">
DEFINE_IIDX(IXamlReader, "24374CF1-CCEB-48BF-A514-41B0186F84C2")

.comdef IXamlReader : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMarkup_CIXamlReaderStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMarkup_CIXamlReaderStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Markup_IXamlReaderStatics <L"Windows.UI.Xaml.Markup.IXamlReaderStatics">
DEFINE_IIDX(IXamlReaderStatics, "9891C6BD-534F-4955-B85A-8A8DC0DCA602")

.comdef IXamlReaderStatics : public IInspectable

    Load                proc :HSTRING, :ptr
    LoadWithInitialTemplateValidation proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMarkup_CIComponentConnector_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMarkup_CIComponentConnector_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Markup_IComponentConnector <L"Windows.UI.Xaml.Markup.IComponentConnector">
DEFINE_IIDX(IComponentConnector, "F6790987-E6E5-47F2-92C6-ECCCE4BA159A")

.comdef IComponentConnector : public IInspectable

    Connect             proc :INT32, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMarkup_CIXamlType_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMarkup_CIXamlType_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Markup_IXamlType <L"Windows.UI.Xaml.Markup.IXamlType">
DEFINE_IIDX(IXamlType, "7920EAB1-A2E5-479A-BD50-6CEF3C0B4970")

.comdef IXamlType : public IInspectable

    get_BaseType        proc :ptr
    get_ContentProperty proc :ptr
    get_FullName        proc :ptr
    get_IsArray         proc :ptr
    get_IsCollection    proc :ptr
    get_IsConstructible proc :ptr
    get_IsDictionary    proc :ptr
    get_IsMarkupExtension proc :ptr
    get_IsBindable      proc :ptr
    get_ItemType        proc :ptr
    get_KeyType         proc :ptr
    get_UnderlyingType  proc :ptr
    ActivateInstance    proc :ptr
    CreateFromString    proc :HSTRING, :ptr
    GetMember           proc :HSTRING, :ptr
    AddToVector         proc :ptr, :ptr
    AddToMap            proc :ptr, :ptr, :ptr
    RunInitializer      proc
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMarkup_CIXamlMember_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMarkup_CIXamlMember_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Markup_IXamlMember <L"Windows.UI.Xaml.Markup.IXamlMember">
DEFINE_IIDX(IXamlMember, "C541F58C-43A9-4216-B718-E0B11B14E93E")

.comdef IXamlMember : public IInspectable

    get_IsAttachable    proc :ptr
    get_IsDependencyProperty proc :ptr
    get_IsReadOnly      proc :ptr
    get_Name            proc :ptr
    get_TargetType      proc :ptr
    get_Type            proc :ptr
    GetValue            proc :ptr, :ptr
    SetValue            proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMarkup_CIXamlMetadataProvider_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMarkup_CIXamlMetadataProvider_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Markup_IXamlMetadataProvider <L"Windows.UI.Xaml.Markup.IXamlMetadataProvider">
DEFINE_IIDX(IXamlMetadataProvider, "B3765D69-68A5-4B32-8861-FDB90C1F5836")

.comdef IXamlMetadataProvider : public IInspectable

    GetXamlType         proc :Windows::UI::Xaml::Interop::TypeName, :ptr
    GetXamlTypeByFullName proc :HSTRING, :ptr
    GetXmlnsDefinitions proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMarkup_CIXamlBinaryWriter_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMarkup_CIXamlBinaryWriter_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Markup_IXamlBinaryWriter <L"Windows.UI.Xaml.Markup.IXamlBinaryWriter">
DEFINE_IIDX(IXamlBinaryWriter, "829D2AD3-620A-46F6-845D-436A05927100")

.comdef IXamlBinaryWriter : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMarkup_CIXamlBinaryWriterStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMarkup_CIXamlBinaryWriterStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Markup_IXamlBinaryWriterStatics <L"Windows.UI.Xaml.Markup.IXamlBinaryWriterStatics">
DEFINE_IIDX(IXamlBinaryWriterStatics, "0D8ED07A-9B82-4AA8-B68B-026F2DE1CC86")

.comdef IXamlBinaryWriterStatics : public IInspectable

    Write               proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

.endn
.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_UI_Xaml_Markup_XamlReader_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Markup_XamlReader_DEFINED
define RuntimeClass_Windows_UI_Xaml_Markup_XamlReader <L"Windows.UI.Xaml.Markup.XamlReader">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Markup_XamlBinaryWriter_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Markup_XamlBinaryWriter_DEFINED
define RuntimeClass_Windows_UI_Xaml_Markup_XamlBinaryWriter <L"Windows.UI.Xaml.Markup.XamlBinaryWriter">
endif

endif
