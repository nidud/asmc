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

ifndef __windows2Esystem2Edisplay_h__
define __windows2Esystem2Edisplay_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc

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
