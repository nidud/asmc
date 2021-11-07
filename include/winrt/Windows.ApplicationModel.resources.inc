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

ifndef __windows2Eapplicationmodel2Eresources_h__
define __windows2Eapplicationmodel2Eresources_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc

.namespace Windows
.namespace ApplicationModel
.namespace Resources

ifndef ____x_ABI_CWindows_CApplicationModel_CResources_CIResourceLoader_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CResources_CIResourceLoader_INTERFACE_DEFINED__
DEFINE_IIDX(IResourceLoader, "08524908-16EF-45AD-A602-293637D7E61A")

.comdef IResourceLoader : public IInspectable

    GetString           proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CResources_CIResourceLoader2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CResources_CIResourceLoader2_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Resources_IResourceLoader2 <L"Windows.ApplicationModel.Resources.IResourceLoader2">
DEFINE_IIDX(IResourceLoader2, "10EB6EC6-8138-48C1-BC65-E1F14207367C")

.comdef IResourceLoader2 : public IInspectable

    GetStringForUri     proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CResources_CIResourceLoaderStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CResources_CIResourceLoaderStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Resources_IResourceLoaderStatics <L"Windows.ApplicationModel.Resources.IResourceLoaderStatics">
DEFINE_IIDX(IResourceLoaderStatics, "BF777CE1-19C8-49C2-953C-47E9227B334E")

.comdef IResourceLoaderStatics : public IInspectable

    GetStringForReference proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CResources_CIResourceLoaderStatics2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CResources_CIResourceLoaderStatics2_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Resources_IResourceLoaderStatics2 <L"Windows.ApplicationModel.Resources.IResourceLoaderStatics2">
DEFINE_IIDX(IResourceLoaderStatics2, "0CC04141-6466-4989-9494-0B82DFC53F1F")

.comdef IResourceLoaderStatics2 : public IInspectable

    GetForCurrentView   proc :ptr
    GetForCurrentViewWithName proc :HSTRING, :ptr
    GetForViewIndependentUse proc :ptr
    GetForViewIndependentUseWithName proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CResources_CIResourceLoaderFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CResources_CIResourceLoaderFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Resources_IResourceLoaderFactory <L"Windows.ApplicationModel.Resources.IResourceLoaderFactory">
DEFINE_IIDX(IResourceLoaderFactory, "C33A3603-69DC-4285-A077-D5C0E47CCBE8")

.comdef IResourceLoaderFactory : public IInspectable

    CreateResourceLoaderByName proc :HSTRING, :ptr
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_ApplicationModel_Resources_ResourceLoader_DEFINED
define RUNTIMECLASS_Windows_ApplicationModel_Resources_ResourceLoader_DEFINED
define RuntimeClass_Windows_ApplicationModel_Resources_ResourceLoader <L"Windows.ApplicationModel.Resources.ResourceLoader">
endif

endif
