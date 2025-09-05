ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Esystem2Ethreading_h__
define __windows2Esystem2Ethreading_h__
ifndef __windows2Efoundation_h__
include Windows.Foundation.inc
endif

.namespace Windows
.namespace System
.namespace Threading

.enum WorkItemPriority {
    WorkItemPriority_Low	= -1,
    WorkItemPriority_Normal	= 0,
    WorkItemPriority_High	= 1
    }

.enum WorkItemOptions {
    WorkItemOptions_None	= 0,
    WorkItemOptions_TimeSliced	= 0x1
    }

ifndef ____x_ABI_CWindows_CSystem_CThreading_CITimerElapsedHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSystem_CThreading_CITimerElapsedHandler_INTERFACE_DEFINED__
DEFINE_IIDX(ITimerElapsedHandler, "FAAEA667-FBEB-49CB-ADB2-71184C556E43")

.comdef ITimerElapsedHandler : public IUnknown

    _Invoke		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSystem_CThreading_CITimerDestroyedHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSystem_CThreading_CITimerDestroyedHandler_INTERFACE_DEFINED__
DEFINE_IIDX(ITimerDestroyedHandler, "34ED19FA-8384-4EB9-8209-FB5094EEEC35")

.comdef ITimerDestroyedHandler : public IUnknown

    _Invoke		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSystem_CThreading_CIWorkItemHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSystem_CThreading_CIWorkItemHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IWorkItemHandler, "1D1A8B8B-FA66-414F-9CBD-B65FC99D17FA")

.comdef IWorkItemHandler : public IUnknown

    _Invoke		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSystem_CThreading_CIThreadPoolStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSystem_CThreading_CIThreadPoolStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_System_Threading_IThreadPoolStatics <L"Windows.System.Threading.IThreadPoolStatics">
DEFINE_IIDX(IThreadPoolStatics, "B6BF67DD-84BD-44F8-AC1C-93EBCB9DBA91")

.comdef IThreadPoolStatics : public IInspectable

    RunAsync		proc :ptr, :ptr
    RunWithPriorityAsync proc :ptr, :Windows::System::Threading::WorkItemPriority, :ptr
    RunWithPriorityAndOptionsAsync proc :ptr, :Windows::System::Threading::WorkItemPriority, :Windows::System::Threading::WorkItemOptions, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSystem_CThreading_CIThreadPoolTimer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSystem_CThreading_CIThreadPoolTimer_INTERFACE_DEFINED__
define InterfaceName_Windows_System_Threading_IThreadPoolTimer <L"Windows.System.Threading.IThreadPoolTimer">
DEFINE_IIDX(IThreadPoolTimer, "594EBE78-55EA-4A88-A50D-3402AE1F9CF2")

.comdef IThreadPoolTimer : public IInspectable

    get_Period		proc :ptr
    get_Delay		proc :ptr
    Cancel		proc
   .ends

endif

ifndef ____x_ABI_CWindows_CSystem_CThreading_CIThreadPoolTimerStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSystem_CThreading_CIThreadPoolTimerStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_System_Threading_IThreadPoolTimerStatics <L"Windows.System.Threading.IThreadPoolTimerStatics">
DEFINE_IIDX(IThreadPoolTimerStatics, "1A8A9D02-E482-461B-B8C7-8EFAD1CCE590")

.comdef IThreadPoolTimerStatics : public IInspectable

    CreatePeriodicTimer proc :ptr, :Windows::Foundation::TimeSpan, :ptr
    CreateTimer		proc :ptr, :Windows::Foundation::TimeSpan, :ptr
    CreatePeriodicTimerWithCompletion proc :ptr, :Windows::Foundation::TimeSpan, :ptr, :ptr
    CreateTimerWithCompletion proc :ptr, :Windows::Foundation::TimeSpan, :ptr, :ptr
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_System_Threading_ThreadPoolTimer_DEFINED
define RUNTIMECLASS_Windows_System_Threading_ThreadPoolTimer_DEFINED
define RuntimeClass_Windows_System_Threading_ThreadPoolTimer <L"Windows.System.Threading.ThreadPoolTimer">
endif
ifndef RUNTIMECLASS_Windows_System_Threading_ThreadPool_DEFINED
define RUNTIMECLASS_Windows_System_Threading_ThreadPool_DEFINED
define RuntimeClass_Windows_System_Threading_ThreadPool <L"Windows.System.Threading.ThreadPool">
endif
endif
