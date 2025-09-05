ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Efoundation2Ediagnostics_h__
define __windows2Efoundation2Ediagnostics_h__
ifndef __windows2Efoundation_h__
include Windows.Foundation.inc
endif
include Windows.Storage.inc

ifndef ____FIEventHandler_1_Windows__CFoundation__CDiagnostics__CTracingStatusChangedEventArgs_INTERFACE_DEFINED__
define ____FIEventHandler_1_Windows__CFoundation__CDiagnostics__CTracingStatusChangedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FIEventHandler_1_Windows__CFoundation__CDiagnostics__CTracingStatusChangedEventArgs, "2bf27008-2eb4-5675-b1cd-e9906cc5ce64")

.comdef __FIEventHandler_1_Windows__CFoundation__CDiagnostics__CTracingStatusChangedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CFoundation__CDiagnostics__CIFileLoggingSession_Windows__CFoundation__CDiagnostics__CLogFileGeneratedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CFoundation__CDiagnostics__CIFileLoggingSession_Windows__CFoundation__CDiagnostics__CLogFileGeneratedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CFoundation__CDiagnostics__CIFileLoggingSession_Windows__CFoundation__CDiagnostics__CLogFileGeneratedEventArgs, "0c6563b0-9d8b-5b60-994b-dee1174d1efb")

.comdef __FITypedEventHandler_2_Windows__CFoundation__CDiagnostics__CIFileLoggingSession_Windows__CFoundation__CDiagnostics__CLogFileGeneratedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CFoundation__CDiagnostics__CILoggingChannel_IInspectable_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CFoundation__CDiagnostics__CILoggingChannel_IInspectable_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CFoundation__CDiagnostics__CILoggingChannel_IInspectable, "52c9c2a1-54a3-5ef9-9aff-014e7c454655")

.comdef __FITypedEventHandler_2_Windows__CFoundation__CDiagnostics__CILoggingChannel_IInspectable : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

.namespace Windows
.namespace Foundation
.namespace Diagnostics

define InterfaceName_Windows_Foundation_Diagnostics_ITracingStatusChangedEventArgs <L"Windows.Foundation.Diagnostics.ITracingStatusChangedEventArgs">

.enum CausalityTraceLevel {
    CausalityTraceLevel_Required	= 0,
    CausalityTraceLevel_Important	= 1,
    CausalityTraceLevel_Verbose = 2
    }

.enum CausalitySource {
    CausalitySource_Application = 0,
    CausalitySource_Library	= 1,
    CausalitySource_System	= 2
    }

.enum CausalityRelation {
    CausalityRelation_AssignDelegate	= 0,
    CausalityRelation_Join	= 1,
    CausalityRelation_Choice	= 2,
    CausalityRelation_Cancel	= 3,
    CausalityRelation_Error	= 4
    }

.enum CausalitySynchronousWork {
    CausalitySynchronousWork_CompletionNotification	= 0,
    CausalitySynchronousWork_ProgressNotification	= 1,
    CausalitySynchronousWork_Execution	= 2
    }

.enum ErrorOptions {
    ErrorOptions_None	= 0,
    ErrorOptions_SuppressExceptions	= 0x1,
    ErrorOptions_ForceExceptions	= 0x2,
    ErrorOptions_UseSetErrorInfo	= 0x4,
    ErrorOptions_SuppressSetErrorInfo	= 0x8
    }

.enum LoggingLevel {
    LoggingLevel_Verbose	= 0,
    LoggingLevel_Information	= 1,
    LoggingLevel_Warning	= 2,
    LoggingLevel_Error	= 3,
    LoggingLevel_Critical	= 4
    }

ifndef ____x_ABI_CWindows_CFoundation_CDiagnostics_CITracingStatusChangedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CFoundation_CDiagnostics_CITracingStatusChangedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(ITracingStatusChangedEventArgs, "410B7711-FF3B-477F-9C9A-D2EFDA302DC3")

.comdef ITracingStatusChangedEventArgs : public IInspectable

    get_Enabled		proc :ptr
    get_TraceLevel	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CFoundation_CDiagnostics_CIAsyncCausalityTracerStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CFoundation_CDiagnostics_CIAsyncCausalityTracerStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Foundation_Diagnostics_IAsyncCausalityTracerStatics <L"Windows.Foundation.Diagnostics.IAsyncCausalityTracerStatics">
DEFINE_IIDX(IAsyncCausalityTracerStatics, "50850B26-267E-451B-A890-AB6A370245EE")

.comdef IAsyncCausalityTracerStatics : public IInspectable

    TraceOperationCreation proc :Windows::Foundation::Diagnostics::CausalityTraceLevel, :Windows::Foundation::Diagnostics::CausalitySource, :GUID, :UINT64, :HSTRING, :UINT64
    TraceOperationCompletion proc :Windows::Foundation::Diagnostics::CausalityTraceLevel, :Windows::Foundation::Diagnostics::CausalitySource, :GUID, :UINT64, :AsyncStatus
    TraceOperationRelation proc :Windows::Foundation::Diagnostics::CausalityTraceLevel, :Windows::Foundation::Diagnostics::CausalitySource, :GUID, :UINT64, :Windows::Foundation::Diagnostics::CausalityRelation
    TraceSynchronousWorkStart proc :Windows::Foundation::Diagnostics::CausalityTraceLevel, :Windows::Foundation::Diagnostics::CausalitySource, :GUID, :UINT64, :Windows::Foundation::Diagnostics::CausalitySynchronousWork
    TraceSynchronousWorkCompletion proc :Windows::Foundation::Diagnostics::CausalityTraceLevel, :Windows::Foundation::Diagnostics::CausalitySource, :Windows::Foundation::Diagnostics::CausalitySynchronousWork
    add_TracingStatusChanged proc :ptr, :ptr
    remove_TracingStatusChanged proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CFoundation_CDiagnostics_CIErrorReportingSettings_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CFoundation_CDiagnostics_CIErrorReportingSettings_INTERFACE_DEFINED__
define InterfaceName_Windows_Foundation_Diagnostics_IErrorReportingSettings <L"Windows.Foundation.Diagnostics.IErrorReportingSettings">
DEFINE_IIDX(IErrorReportingSettings, "16369792-B03E-4BA1-8BB8-D28F4AB4D2C0")

.comdef IErrorReportingSettings : public IInspectable

    SetErrorOptions	proc :Windows::Foundation::Diagnostics::ErrorOptions
    GetErrorOptions	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CFoundation_CDiagnostics_CILoggingChannel_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CFoundation_CDiagnostics_CILoggingChannel_INTERFACE_DEFINED__
define InterfaceName_Windows_Foundation_Diagnostics_ILoggingChannel <L"Windows.Foundation.Diagnostics.ILoggingChannel">
DEFINE_IIDX(ILoggingChannel, "E9A50343-11D7-4F01-B5CA-CF495278C0A8")

.comdef ILoggingChannel : public IInspectable

    get_Name		proc :ptr
    get_Enabled		proc :ptr
    get_Level		proc :ptr
    LogMessage		proc :HSTRING
    LogMessageWithLevel proc :HSTRING, :Windows::Foundation::Diagnostics::LoggingLevel
    LogValuePair	proc :HSTRING, :INT32
    LogValuePairWithLevel proc :HSTRING, :INT32, :Windows::Foundation::Diagnostics::LoggingLevel
    add_LoggingEnabled	proc :ptr, :ptr
    remove_LoggingEnabled proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CFoundation_CDiagnostics_CILoggingChannelFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CFoundation_CDiagnostics_CILoggingChannelFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Foundation_Diagnostics_ILoggingChannelFactory <L"Windows.Foundation.Diagnostics.ILoggingChannelFactory">
DEFINE_IIDX(ILoggingChannelFactory, "4EDC5B9C-AF80-4A9B-B0DC-398F9AE5207B")

.comdef ILoggingChannelFactory : public IInspectable

    Create		proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CFoundation_CDiagnostics_CILoggingActivity_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CFoundation_CDiagnostics_CILoggingActivity_INTERFACE_DEFINED__
define InterfaceName_Windows_Foundation_Diagnostics_ILoggingActivity <L"Windows.Foundation.Diagnostics.ILoggingActivity">
DEFINE_IIDX(ILoggingActivity, "BC032941-B766-4CB5-9848-97AC6BA6D60C")

.comdef ILoggingActivity : public IInspectable

    get_Name		proc :ptr
    get_Id		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CFoundation_CDiagnostics_CILoggingActivityFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CFoundation_CDiagnostics_CILoggingActivityFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Foundation_Diagnostics_ILoggingActivityFactory <L"Windows.Foundation.Diagnostics.ILoggingActivityFactory">
DEFINE_IIDX(ILoggingActivityFactory, "6B33B483-E10A-4C58-97D5-10FB451074FB")

.comdef ILoggingActivityFactory : public IInspectable

    CreateLoggingActivity proc :HSTRING, :ptr, :ptr
    CreateLoggingActivityWithLevel proc :HSTRING, :ptr, :Windows::Foundation::Diagnostics::LoggingLevel, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CFoundation_CDiagnostics_CILoggingSession_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CFoundation_CDiagnostics_CILoggingSession_INTERFACE_DEFINED__
define InterfaceName_Windows_Foundation_Diagnostics_ILoggingSession <L"Windows.Foundation.Diagnostics.ILoggingSession">
DEFINE_IIDX(ILoggingSession, "6221F306-9380-4AD7-BAF5-41EA9310D768")

.comdef ILoggingSession : public IInspectable

    get_Name		proc :ptr
    SaveToFileAsync	proc :ptr, :HSTRING, :ptr
    AddLoggingChannel	proc :ptr
    AddLoggingChannelWithLevel proc :ptr, :Windows::Foundation::Diagnostics::LoggingLevel
    RemoveLoggingChannel proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CFoundation_CDiagnostics_CILoggingSessionFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CFoundation_CDiagnostics_CILoggingSessionFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Foundation_Diagnostics_ILoggingSessionFactory <L"Windows.Foundation.Diagnostics.ILoggingSessionFactory">
DEFINE_IIDX(ILoggingSessionFactory, "4E937EE5-58FD-45E0-8C2F-A132EFF95C1E")

.comdef ILoggingSessionFactory : public IInspectable

    Create		proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CFoundation_CDiagnostics_CILogFileGeneratedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CFoundation_CDiagnostics_CILogFileGeneratedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Foundation_Diagnostics_ILogFileGeneratedEventArgs <L"Windows.Foundation.Diagnostics.ILogFileGeneratedEventArgs">
DEFINE_IIDX(ILogFileGeneratedEventArgs, "269E976F-0D38-4C1A-B53F-B395D881DF84")

.comdef ILogFileGeneratedEventArgs : public IInspectable

    get_File		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CFoundation_CDiagnostics_CIFileLoggingSession_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CFoundation_CDiagnostics_CIFileLoggingSession_INTERFACE_DEFINED__
define InterfaceName_Windows_Foundation_Diagnostics_IFileLoggingSession <L"Windows.Foundation.Diagnostics.IFileLoggingSession">
DEFINE_IIDX(IFileLoggingSession, "24C74216-FED2-404C-895F-1F9699CB02F7")

.comdef IFileLoggingSession : public IInspectable

    get_Name		proc :ptr
    AddLoggingChannel	proc :ptr
    AddLoggingChannelWithLevel proc :ptr, :Windows::Foundation::Diagnostics::LoggingLevel
    RemoveLoggingChannel proc :ptr
    CloseAndSaveToFileAsync proc :ptr
    add_LogFileGenerated proc :ptr, :ptr
    remove_LogFileGenerated proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CFoundation_CDiagnostics_CIFileLoggingSessionFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CFoundation_CDiagnostics_CIFileLoggingSessionFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Foundation_Diagnostics_IFileLoggingSessionFactory <L"Windows.Foundation.Diagnostics.IFileLoggingSessionFactory">
DEFINE_IIDX(IFileLoggingSessionFactory, "EEA08DCE-8447-4DAA-9133-12EB46F697D4")

.comdef IFileLoggingSessionFactory : public IInspectable

    Create		proc :HSTRING, :ptr
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_Foundation_Diagnostics_TracingStatusChangedEventArgs_DEFINED
define RUNTIMECLASS_Windows_Foundation_Diagnostics_TracingStatusChangedEventArgs_DEFINED
define RuntimeClass_Windows_Foundation_Diagnostics_TracingStatusChangedEventArgs <L"Windows.Foundation.Diagnostics.TracingStatusChangedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_Foundation_Diagnostics_AsyncCausalityTracer_DEFINED
define RUNTIMECLASS_Windows_Foundation_Diagnostics_AsyncCausalityTracer_DEFINED
define RuntimeClass_Windows_Foundation_Diagnostics_AsyncCausalityTracer <L"Windows.Foundation.Diagnostics.AsyncCausalityTracer">
endif
ifndef RUNTIMECLASS_Windows_Foundation_Diagnostics_RuntimeBrokerErrorSettings_DEFINED
define RUNTIMECLASS_Windows_Foundation_Diagnostics_RuntimeBrokerErrorSettings_DEFINED
define RuntimeClass_Windows_Foundation_Diagnostics_RuntimeBrokerErrorSettings <L"Windows.Foundation.Diagnostics.RuntimeBrokerErrorSettings">
endif
ifndef RUNTIMECLASS_Windows_Foundation_Diagnostics_LoggingChannel_DEFINED
define RUNTIMECLASS_Windows_Foundation_Diagnostics_LoggingChannel_DEFINED
define RuntimeClass_Windows_Foundation_Diagnostics_LoggingChannel <L"Windows.Foundation.Diagnostics.LoggingChannel">
endif
ifndef RUNTIMECLASS_Windows_Foundation_Diagnostics_LoggingActivity_DEFINED
define RUNTIMECLASS_Windows_Foundation_Diagnostics_LoggingActivity_DEFINED
define RuntimeClass_Windows_Foundation_Diagnostics_LoggingActivity <L"Windows.Foundation.Diagnostics.LoggingActivity">
endif
ifndef RUNTIMECLASS_Windows_Foundation_Diagnostics_LoggingSession_DEFINED
define RUNTIMECLASS_Windows_Foundation_Diagnostics_LoggingSession_DEFINED
define RuntimeClass_Windows_Foundation_Diagnostics_LoggingSession <L"Windows.Foundation.Diagnostics.LoggingSession">
endif
ifndef RUNTIMECLASS_Windows_Foundation_Diagnostics_LogFileGeneratedEventArgs_DEFINED
define RUNTIMECLASS_Windows_Foundation_Diagnostics_LogFileGeneratedEventArgs_DEFINED
define RuntimeClass_Windows_Foundation_Diagnostics_LogFileGeneratedEventArgs <L"Windows.Foundation.Diagnostics.LogFileGeneratedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_Foundation_Diagnostics_FileLoggingSession_DEFINED
define RUNTIMECLASS_Windows_Foundation_Diagnostics_FileLoggingSession_DEFINED
define RuntimeClass_Windows_Foundation_Diagnostics_FileLoggingSession <L"Windows.Foundation.Diagnostics.FileLoggingSession">
endif

endif
