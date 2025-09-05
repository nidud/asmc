ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Eui2Examl2Eresources_h__
define __windows2Eui2Examl2Eresources_h__
ifndef __windows2Efoundation_h__
include Windows.Foundation.inc
endif

.namespace Windows
.namespace UI
.namespace Xaml
.namespace Resources

ifndef ____x_ABI_CWindows_CUI_CXaml_CResources_CICustomXamlResourceLoader_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CResources_CICustomXamlResourceLoader_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Resources_ICustomXamlResourceLoader <L"Windows.UI.Xaml.Resources.ICustomXamlResourceLoader">
DEFINE_IIDX(ICustomXamlResourceLoader, "511A84AB-4A88-419F-852E-54083B90B078")

.comdef ICustomXamlResourceLoader : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CResources_CICustomXamlResourceLoaderOverrides_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CResources_CICustomXamlResourceLoaderOverrides_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Resources_ICustomXamlResourceLoaderOverrides <L"Windows.UI.Xaml.Resources.ICustomXamlResourceLoaderOverrides">
DEFINE_IIDX(ICustomXamlResourceLoaderOverrides, "F851E991-AF02-46E8-9AF8-427B7EBFE9F8")

.comdef ICustomXamlResourceLoaderOverrides : public IInspectable

    GetResource         proc :HSTRING, :HSTRING, :HSTRING, :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CResources_CICustomXamlResourceLoaderStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CResources_CICustomXamlResourceLoaderStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Resources_ICustomXamlResourceLoaderStatics <L"Windows.UI.Xaml.Resources.ICustomXamlResourceLoaderStatics">
DEFINE_IIDX(ICustomXamlResourceLoaderStatics, "224FF617-E4DC-4C27-AD32-DB93D5D0E5DA")

.comdef ICustomXamlResourceLoaderStatics : public IInspectable

    get_Current         proc :ptr
    put_Current         proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CResources_CICustomXamlResourceLoaderFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CResources_CICustomXamlResourceLoaderFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Resources_ICustomXamlResourceLoaderFactory <L"Windows.UI.Xaml.Resources.ICustomXamlResourceLoaderFactory">
DEFINE_IIDX(ICustomXamlResourceLoaderFactory, "5BFD7E49-7886-44F3-8ED3-6FEC0463ED69")

.comdef ICustomXamlResourceLoaderFactory : public IInspectable

    CreateInstance      proc :ptr, :ptr, :ptr
   .ends

endif

.endn
.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_UI_Xaml_Resources_CustomXamlResourceLoader_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Resources_CustomXamlResourceLoader_DEFINED
define RuntimeClass_Windows_UI_Xaml_Resources_CustomXamlResourceLoader <L"Windows.UI.Xaml.Resources.CustomXamlResourceLoader">
endif

endif
