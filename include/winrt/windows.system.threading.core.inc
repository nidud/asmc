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

ifndef __windows2Esystem2Ethreading2Ecore_h__
define __windows2Esystem2Ethreading2Ecore_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include Windows.System.Threading.inc

.namespace Windows
.namespace System
.namespace Threading
.namespace Core

ifndef ____x_ABI_CWindows_CSystem_CThreading_CCore_CISignalHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSystem_CThreading_CCore_CISignalHandler_INTERFACE_DEFINED__
DEFINE_IIDX(ISignalHandler, "923C402E-4721-440E-9DDA-55B6F2E07710")

.comdef ISignalHandler : public IUnknown

    _Invoke             proc :ptr, :boolean
   .ends

endif

ifndef ____x_ABI_CWindows_CSystem_CThreading_CCore_CISignalNotifierStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSystem_CThreading_CCore_CISignalNotifierStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_System_Threading_Core_ISignalNotifierStatics <L"Windows.System.Threading.Core.ISignalNotifierStatics">
DEFINE_IIDX(ISignalNotifierStatics, "1C4E4566-8400-46D3-A115-7D0C0DFC9F62")

.comdef ISignalNotifierStatics : public IInspectable

    AttachToEvent       proc :HSTRING, :ptr, :ptr
    AttachToEventWithTimeout proc :HSTRING, :ptr, :Windows::Foundation::TimeSpan, :ptr
    AttachToSemaphore   proc :HSTRING, :ptr, :ptr
    AttachToSemaphoreWithTimeout proc :HSTRING, :ptr, :Windows::Foundation::TimeSpan, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSystem_CThreading_CCore_CIPreallocatedWorkItemFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSystem_CThreading_CCore_CIPreallocatedWorkItemFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_System_Threading_Core_IPreallocatedWorkItemFactory <L"Windows.System.Threading.Core.IPreallocatedWorkItemFactory">
DEFINE_IIDX(IPreallocatedWorkItemFactory, "E3D32B45-DFEA-469B-82C5-F6E3CEFDEAFB")

.comdef IPreallocatedWorkItemFactory : public IInspectable

    CreateWorkItem      proc :ptr, :ptr
    CreateWorkItemWithPriority proc :ptr, :Windows::System::Threading::WorkItemPriority, :ptr
    CreateWorkItemWithPriorityAndOptions proc :ptr, :Windows::System::Threading::WorkItemPriority, :Windows::System::Threading::WorkItemOptions, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSystem_CThreading_CCore_CIPreallocatedWorkItem_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSystem_CThreading_CCore_CIPreallocatedWorkItem_INTERFACE_DEFINED__
define InterfaceName_Windows_System_Threading_Core_IPreallocatedWorkItem <L"Windows.System.Threading.Core.IPreallocatedWorkItem">
DEFINE_IIDX(IPreallocatedWorkItem, "B6DAA9FC-BC5B-401A-A8B2-6E754D14DAA6")

.comdef IPreallocatedWorkItem : public IInspectable

    RunAsync            proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSystem_CThreading_CCore_CISignalNotifier_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSystem_CThreading_CCore_CISignalNotifier_INTERFACE_DEFINED__
define InterfaceName_Windows_System_Threading_Core_ISignalNotifier <L"Windows.System.Threading.Core.ISignalNotifier">
DEFINE_IIDX(ISignalNotifier, "14285E06-63A7-4713-B6D9-62F64B56FB8B")

.comdef ISignalNotifier : public IInspectable

    Enable              proc
    Terminate           proc
   .ends

endif

.endn
.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_System_Threading_Core_SignalNotifier_DEFINED
define RUNTIMECLASS_Windows_System_Threading_Core_SignalNotifier_DEFINED
define RuntimeClass_Windows_System_Threading_Core_SignalNotifier <L"Windows.System.Threading.Core.SignalNotifier">
endif
ifndef RUNTIMECLASS_Windows_System_Threading_Core_PreallocatedWorkItem_DEFINED
define RUNTIMECLASS_Windows_System_Threading_Core_PreallocatedWorkItem_DEFINED
define RuntimeClass_Windows_System_Threading_Core_PreallocatedWorkItem <L"Windows.System.Threading.Core.PreallocatedWorkItem">
endif

endif
