ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Eui2Ecore2Ecorewindowfactory_h__
define __windows2Eui2Ecore2Ecorewindowfactory_h__

ifndef __oaidl_h__
include oaidl.inc
endif
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
