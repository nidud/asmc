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

ifndef __windows2Esystem2Eremotedesktop_h__
define __windows2Esystem2Eremotedesktop_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc

.namespace Windows
.namespace System
.namespace RemoteDesktop

ifndef ____x_ABI_CWindows_CSystem_CRemoteDesktop_CIInteractiveSessionStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSystem_CRemoteDesktop_CIInteractiveSessionStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_System_RemoteDesktop_IInteractiveSessionStatics <L"Windows.System.RemoteDesktop.IInteractiveSessionStatics">
DEFINE_IIDX(IInteractiveSessionStatics, "60884631-DD3A-4576-9C8D-E8027618BDCE")

.comdef IInteractiveSessionStatics : public IInspectable

    get_IsRemote        proc :ptr
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_System_RemoteDesktop_InteractiveSession_DEFINED
define RUNTIMECLASS_Windows_System_RemoteDesktop_InteractiveSession_DEFINED
define RuntimeClass_Windows_System_RemoteDesktop_InteractiveSession <L"Windows.System.RemoteDesktop.InteractiveSession">
endif
endif
