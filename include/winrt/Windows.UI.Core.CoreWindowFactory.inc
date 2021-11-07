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

ifndef __windows2Eui2Ecore2Ecorewindowfactory_h__
define __windows2Eui2Ecore2Ecorewindowfactory_h__

include oaidl.inc
include Inspectable.inc
include windows.ui.core.inc

.namespace Windows
.namespace UI
.namespace Core

ifndef ____x_ABI_CWindows_CUI_CCore_CICoreWindowFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CCore_CICoreWindowFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Core_ICoreWindowFactory <L"Windows.UI.Core.ICoreWindowFactory">
DEFINE_IIDX(ICoreWindowFactory, "CD292360-2763-4085-8A9F-74B224A29175")

.comdef ICoreWindowFactory : public IInspectable

    CreateCoreWindow    proc :HSTRING, :ptr
    get_WindowReuseAllowed proc :ptr
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_UI_Core_ImmersiveCoreWindowFactory_DEFINED
define RUNTIMECLASS_Windows_UI_Core_ImmersiveCoreWindowFactory_DEFINED
define RuntimeClass_Windows_UI_Core_ImmersiveCoreWindowFactory <L"Windows.UI.Core.ImmersiveCoreWindowFactory">
endif
ifndef RUNTIMECLASS_Windows_UI_Core_HostedCoreWindowFactory_DEFINED
define RUNTIMECLASS_Windows_UI_Core_HostedCoreWindowFactory_DEFINED
define RuntimeClass_Windows_UI_Core_HostedCoreWindowFactory <L"Windows.UI.Core.HostedCoreWindowFactory">
endif

endif
