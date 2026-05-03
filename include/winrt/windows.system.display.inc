ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Esystem2Edisplay_h__
define __windows2Esystem2Edisplay_h__
ifndef __windows2Efoundation_h__
include Windows.Foundation.inc
endif

.namespace Windows
.namespace System
.namespace Display

ifndef ____x_ABI_CWindows_CSystem_CDisplay_CIDisplayRequest_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSystem_CDisplay_CIDisplayRequest_INTERFACE_DEFINED__
DEFINE_IIDX(IDisplayRequest, "E5732044-F49F-4B60-8DD4-5E7E3A632AC0")

.comdef IDisplayRequest : public IInspectable

    RequestActive       proc
    RequestRelease      proc
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_System_Display_DisplayRequest_DEFINED
define RUNTIMECLASS_Windows_System_Display_DisplayRequest_DEFINED
define RuntimeClass_Windows_System_Display_DisplayRequest <L"Windows.System.Display.DisplayRequest">
endif

endif
