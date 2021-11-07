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

ifndef __windows2Eapplicationmodel2Ebackground_h__
define __windows2Eapplicationmodel2Ebackground_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include windows.foundation.collections.inc

ifndef ____FIKeyValuePair_2_GUID_Windows__CApplicationModel__CBackground__CIBackgroundTaskRegistration_INTERFACE_DEFINED__
define ____FIKeyValuePair_2_GUID_Windows__CApplicationModel__CBackground__CIBackgroundTaskRegistration_INTERFACE_DEFINED__
DEFINE_IIDX(__FIKeyValuePair_2_GUID_Windows__CApplicationModel__CBackground__CIBackgroundTaskRegistration, "5a1f6d75-8678-547c-8fd7-fbceb6ebf968")

.comdef __FIKeyValuePair_2_GUID_Windows__CApplicationModel__CBackground__CIBackgroundTaskRegistration : public IInspectable

    get_Key		proc :ptr
    get_Value		proc :ptr
   .ends

endif

ifndef ____FIIterator_1___FIKeyValuePair_2_GUID_Windows__CApplicationModel__CBackground__CIBackgroundTaskRegistration_INTERFACE_DEFINED__
define ____FIIterator_1___FIKeyValuePair_2_GUID_Windows__CApplicationModel__CBackground__CIBackgroundTaskRegistration_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1___FIKeyValuePair_2_GUID_Windows__CApplicationModel__CBackground__CIBackgroundTaskRegistration, "2001aea5-1a86-517e-8be5-11d7fb5935b2")

.comdef __FIIterator_1___FIKeyValuePair_2_GUID_Windows__CApplicationModel__CBackground__CIBackgroundTaskRegistration : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1___FIKeyValuePair_2_GUID_Windows__CApplicationModel__CBackground__CIBackgroundTaskRegistration_INTERFACE_DEFINED__
define ____FIIterable_1___FIKeyValuePair_2_GUID_Windows__CApplicationModel__CBackground__CIBackgroundTaskRegistration_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1___FIKeyValuePair_2_GUID_Windows__CApplicationModel__CBackground__CIBackgroundTaskRegistration, "80fb0327-5a00-55cc-85db-a852719981b9")

.comdef __FIIterable_1___FIKeyValuePair_2_GUID_Windows__CApplicationModel__CBackground__CIBackgroundTaskRegistration : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIMapView_2_GUID_Windows__CApplicationModel__CBackground__CIBackgroundTaskRegistration_INTERFACE_DEFINED__
define ____FIMapView_2_GUID_Windows__CApplicationModel__CBackground__CIBackgroundTaskRegistration_INTERFACE_DEFINED__
DEFINE_IIDX(__FIMapView_2_GUID_Windows__CApplicationModel__CBackground__CIBackgroundTaskRegistration, "78c880f6-a7dc-5172-89da-7749fc82aa82")

.comdef __FIMapView_2_GUID_Windows__CApplicationModel__CBackground__CIBackgroundTaskRegistration : public IInspectable

    Lookup		proc :ptr GUID, :ptr
    get_Size		proc :ptr
    HasKey		proc :GUID, :ptr
    Split		proc :ptr, :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CBackground__CAlarmAccessStatus_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CBackground__CAlarmAccessStatus_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CBackground__CAlarmAccessStatus, "84108017-a8e7-5449-b713-df48503a953e")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CBackground__CAlarmAccessStatus : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CApplicationModel__CBackground__CAlarmAccessStatus_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CApplicationModel__CBackground__CAlarmAccessStatus_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CApplicationModel__CBackground__CAlarmAccessStatus, "a55a747d-59f6-5cb6-b439-c8aad670905c")

.comdef __FIAsyncOperation_1_Windows__CApplicationModel__CBackground__CAlarmAccessStatus : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CBackground__CBackgroundAccessStatus_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CBackground__CBackgroundAccessStatus_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CBackground__CBackgroundAccessStatus, "26dd26e3-3f47-5709-b2f2-d6d0ad3288f0")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CBackground__CBackgroundAccessStatus : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CApplicationModel__CBackground__CBackgroundAccessStatus_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CApplicationModel__CBackground__CBackgroundAccessStatus_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CApplicationModel__CBackground__CBackgroundAccessStatus, "7b44e581-cfa9-5763-bed7-6a65739f0dbf")

.comdef __FIAsyncOperation_1_Windows__CApplicationModel__CBackground__CBackgroundAccessStatus : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CBackground__CDeviceTriggerResult_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CBackground__CDeviceTriggerResult_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CBackground__CDeviceTriggerResult, "d5aa9506-1464-57d4-859d-7ee9b26cb1f9")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CBackground__CDeviceTriggerResult : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CApplicationModel__CBackground__CDeviceTriggerResult_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CApplicationModel__CBackground__CDeviceTriggerResult_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CApplicationModel__CBackground__CDeviceTriggerResult, "b5136c46-2f2e-511d-9e8e-5ef4decb1da7")

.comdef __FIAsyncOperation_1_Windows__CApplicationModel__CBackground__CDeviceTriggerResult : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

.namespace Windows
.namespace ApplicationModel
.namespace Background

.enum AlarmAccessStatus {
    AlarmAccessStatus_Unspecified	= 0,
    AlarmAccessStatus_AllowedWithWakeupCapability	= 1,
    AlarmAccessStatus_AllowedWithoutWakeupCapability	= 2,
    AlarmAccessStatus_Denied	= 3
    }

.enum BackgroundAccessStatus {
    BackgroundAccessStatus_Unspecified	= 0,
    BackgroundAccessStatus_AllowedWithAlwaysOnRealTimeConnectivity	= 1,
    BackgroundAccessStatus_AllowedMayUseActiveRealTimeConnectivity	= 2,
    BackgroundAccessStatus_Denied	= 3
    }

.enum BackgroundWorkCostValue {
    BackgroundWorkCostValue_Low = 0,
    BackgroundWorkCostValue_Medium	= 1,
    BackgroundWorkCostValue_High	= 2
    }

.enum BackgroundTaskCancellationReason {
    BackgroundTaskCancellationReason_Abort	= 0,
    BackgroundTaskCancellationReason_Terminating	= 1,
    BackgroundTaskCancellationReason_LoggingOff = 2,
    BackgroundTaskCancellationReason_ServicingUpdate	= 3,
    BackgroundTaskCancellationReason_IdleTask	= 4,
    BackgroundTaskCancellationReason_Uninstall	= 5,
    BackgroundTaskCancellationReason_ConditionLoss	= 6,
    BackgroundTaskCancellationReason_SystemPolicy	= 7,
    BackgroundTaskCancellationReason_QuietHoursEntered	= 8
    }

.enum BackgroundTaskThrottleCounter {
    BackgroundTaskThrottleCounter_All	= 0,
    BackgroundTaskThrottleCounter_Cpu	= 1,
    BackgroundTaskThrottleCounter_Network	= 2
    }

.enum SystemTriggerType {
    SystemTriggerType_Invalid	= 0,
    SystemTriggerType_SmsReceived	= 1,
    SystemTriggerType_UserPresent	= 2,
    SystemTriggerType_UserAway	= 3,
    SystemTriggerType_NetworkStateChange	= 4,
    SystemTriggerType_ControlChannelReset	= 5,
    SystemTriggerType_InternetAvailable = 6,
    SystemTriggerType_SessionConnected	= 7,
    SystemTriggerType_ServicingComplete = 8,
    SystemTriggerType_LockScreenApplicationAdded	= 9,
    SystemTriggerType_LockScreenApplicationRemoved	= 10,
    SystemTriggerType_TimeZoneChange	= 11,
    SystemTriggerType_OnlineIdConnectedStateChange	= 12,
    SystemTriggerType_BackgroundWorkCostChange	= 13
    }

.enum SystemConditionType {
    SystemConditionType_Invalid = 0,
    SystemConditionType_UserPresent	= 1,
    SystemConditionType_UserNotPresent	= 2,
    SystemConditionType_InternetAvailable	= 3,
    SystemConditionType_InternetNotAvailable	= 4,
    SystemConditionType_SessionConnected	= 5,
    SystemConditionType_SessionDisconnected	= 6,
    SystemConditionType_FreeNetworkAvailable	= 7,
    SystemConditionType_BackgroundWorkCostNotHigh	= 8
    }

.enum DeviceTriggerResult {
    DeviceTriggerResult_Allowed = 0,
    DeviceTriggerResult_DeniedByUser	= 1,
    DeviceTriggerResult_DeniedBySystem	= 2,
    DeviceTriggerResult_LowBattery	= 3
    }

.enum LocationTriggerType {
    LocationTriggerType_Geofence	= 0
    }

ifndef ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskCanceledEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskCanceledEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IBackgroundTaskCanceledEventHandler, "A6C4BAC0-51F8-4C57-AC3F-156DD1680C4F")

.comdef IBackgroundTaskCanceledEventHandler : public IUnknown

    _Invoke		proc :ptr, :Windows::ApplicationModel::Background::BackgroundTaskCancellationReason
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskProgressEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskProgressEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IBackgroundTaskProgressEventHandler, "46E0683C-8A88-4C99-804C-76897F6277A6")

.comdef IBackgroundTaskProgressEventHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskCompletedEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskCompletedEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IBackgroundTaskCompletedEventHandler, "5B38E929-A086-46A7-A678-439135822BCF")

.comdef IBackgroundTaskCompletedEventHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CBackground_CIAlarmApplicationManagerStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CBackground_CIAlarmApplicationManagerStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Background_IAlarmApplicationManagerStatics <L"Windows.ApplicationModel.Background.IAlarmApplicationManagerStatics">
DEFINE_IIDX(IAlarmApplicationManagerStatics, "CA03FA3B-CCE6-4DE2-B09B-9628BD33BBBE")

.comdef IAlarmApplicationManagerStatics : public IInspectable

    RequestAccessAsync	proc :ptr
    GetAccessStatus	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundExecutionManagerStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundExecutionManagerStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Background_IBackgroundExecutionManagerStatics <L"Windows.ApplicationModel.Background.IBackgroundExecutionManagerStatics">
DEFINE_IIDX(IBackgroundExecutionManagerStatics, "E826EA58-66A9-4D41-83D4-B4C18C87B846")

.comdef IBackgroundExecutionManagerStatics : public IInspectable

    RequestAccessAsync	proc :ptr
    RequestAccessForApplicationAsync proc :HSTRING, :ptr
    RemoveAccess	proc
    RemoveAccessForApplication proc :HSTRING
    GetAccessStatus	proc :ptr
    GetAccessStatusForApplication proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskInstance_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskInstance_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Background_IBackgroundTaskInstance <L"Windows.ApplicationModel.Background.IBackgroundTaskInstance">
DEFINE_IIDX(IBackgroundTaskInstance, "865BDA7A-21D8-4573-8F32-928A1B0641F6")

.comdef IBackgroundTaskInstance : public IInspectable

    get_InstanceId	proc :ptr
    get_Task		proc :ptr
    get_Progress	proc :ptr
    put_Progress	proc :UINT32
    get_TriggerDetails	proc :ptr
    add_Canceled	proc :ptr, :ptr
    remove_Canceled	proc :EventRegistrationToken
    get_SuspendedCount	proc :ptr
    GetDeferral		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundWorkCostStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundWorkCostStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Background_IBackgroundWorkCostStatics <L"Windows.ApplicationModel.Background.IBackgroundWorkCostStatics">
DEFINE_IIDX(IBackgroundWorkCostStatics, "C740A662-C310-4B82-B3E3-3BCFB9E4C77D")

.comdef IBackgroundWorkCostStatics : public IInspectable

    get_CurrentBackgroundWorkCost proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskDeferral_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskDeferral_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Background_IBackgroundTaskDeferral <L"Windows.ApplicationModel.Background.IBackgroundTaskDeferral">
DEFINE_IIDX(IBackgroundTaskDeferral, "93CC156D-AF27-4DD3-846E-24EE40CADD25")

.comdef IBackgroundTaskDeferral : public IInspectable

    Complete		proc
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskInstance2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskInstance2_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Background_IBackgroundTaskInstance2 <L"Windows.ApplicationModel.Background.IBackgroundTaskInstance2">
DEFINE_IIDX(IBackgroundTaskInstance2, "4F7D0176-0C76-4FB4-896D-5DE1864122F6")

.comdef IBackgroundTaskInstance2 : public IInspectable

    GetThrottleCount	proc :Windows::ApplicationModel::Background::BackgroundTaskThrottleCounter, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTask_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTask_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Background_IBackgroundTask <L"Windows.ApplicationModel.Background.IBackgroundTask">
DEFINE_IIDX(IBackgroundTask, "7D13D534-FD12-43CE-8C22-EA1FF13C06DF")

.comdef IBackgroundTask : public IInspectable

    Run			proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskRegistration_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskRegistration_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Background_IBackgroundTaskRegistration <L"Windows.ApplicationModel.Background.IBackgroundTaskRegistration">
DEFINE_IIDX(IBackgroundTaskRegistration, "10654CC2-A26E-43BF-8C12-1FB40DBFBFA0")

.comdef IBackgroundTaskRegistration : public IInspectable

    get_TaskId		proc :ptr
    get_Name		proc :ptr
    add_Progress	proc :ptr, :ptr
    remove_Progress	proc :EventRegistrationToken
    add_Completed	proc :ptr, :ptr
    remove_Completed	proc :EventRegistrationToken
    Unregister		proc :boolean
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskRegistrationStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskRegistrationStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Background_IBackgroundTaskRegistrationStatics <L"Windows.ApplicationModel.Background.IBackgroundTaskRegistrationStatics">
DEFINE_IIDX(IBackgroundTaskRegistrationStatics, "4C542F69-B000-42BA-A093-6A563C65E3F8")

.comdef IBackgroundTaskRegistrationStatics : public IInspectable

    get_AllTasks	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskBuilder_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskBuilder_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Background_IBackgroundTaskBuilder <L"Windows.ApplicationModel.Background.IBackgroundTaskBuilder">
DEFINE_IIDX(IBackgroundTaskBuilder, "0351550E-3E64-4572-A93A-84075A37C917")

.comdef IBackgroundTaskBuilder : public IInspectable

    put_TaskEntryPoint	proc :HSTRING
    get_TaskEntryPoint	proc :ptr
    SetTrigger		proc :ptr
    AddCondition	proc :ptr
    put_Name		proc :HSTRING
    get_Name		proc :ptr
    Register		proc :ptr
   .ends

endif
ifndef ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTrigger_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTrigger_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Background_IBackgroundTrigger <L"Windows.ApplicationModel.Background.IBackgroundTrigger">
DEFINE_IIDX(IBackgroundTrigger, "84B3A058-6027-4B87-9790-BDF3F757DBD7")

.comdef IBackgroundTrigger : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundCondition_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundCondition_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Background_IBackgroundCondition <L"Windows.ApplicationModel.Background.IBackgroundCondition">
DEFINE_IIDX(IBackgroundCondition, "AE48A1EE-8951-400A-8302-9C9C9A2A3A3B")

.comdef IBackgroundCondition : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskBuilder2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskBuilder2_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Background_IBackgroundTaskBuilder2 <L"Windows.ApplicationModel.Background.IBackgroundTaskBuilder2">
DEFINE_IIDX(IBackgroundTaskBuilder2, "6AE7CFB1-104F-406D-8DB6-844A570F42BB")

.comdef IBackgroundTaskBuilder2 : public IInspectable

    put_CancelOnConditionLoss proc :boolean
    get_CancelOnConditionLoss proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskCompletedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskCompletedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Background_IBackgroundTaskCompletedEventArgs <L"Windows.ApplicationModel.Background.IBackgroundTaskCompletedEventArgs">
DEFINE_IIDX(IBackgroundTaskCompletedEventArgs, "565D25CF-F209-48F4-9967-2B184F7BFBF0")

.comdef IBackgroundTaskCompletedEventArgs : public IInspectable

    get_InstanceId	proc :ptr
    CheckResult		proc
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskProgressEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskProgressEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Background_IBackgroundTaskProgressEventArgs <L"Windows.ApplicationModel.Background.IBackgroundTaskProgressEventArgs">
DEFINE_IIDX(IBackgroundTaskProgressEventArgs, "FB1468AC-8332-4D0A-9532-03EAE684DA31")

.comdef IBackgroundTaskProgressEventArgs : public IInspectable

    get_InstanceId	proc :ptr
    get_Progress	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CBackground_CISystemTrigger_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CBackground_CISystemTrigger_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Background_ISystemTrigger <L"Windows.ApplicationModel.Background.ISystemTrigger">
DEFINE_IIDX(ISystemTrigger, "1D80C776-3748-4463-8D7E-276DC139AC1C")

.comdef ISystemTrigger : public IInspectable

    get_OneShot		proc :ptr
    get_TriggerType	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CBackground_CISystemTriggerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CBackground_CISystemTriggerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Background_ISystemTriggerFactory <L"Windows.ApplicationModel.Background.ISystemTriggerFactory">
DEFINE_IIDX(ISystemTriggerFactory, "E80423D4-8791-4579-8126-87EC8AAA407A")

.comdef ISystemTriggerFactory : public IInspectable

    Create		proc :Windows::ApplicationModel::Background::SystemTriggerType, :boolean, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CBackground_CISystemCondition_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CBackground_CISystemCondition_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Background_ISystemCondition <L"Windows.ApplicationModel.Background.ISystemCondition">
DEFINE_IIDX(ISystemCondition, "C15FB476-89C5-420B-ABD3-FB3030472128")

.comdef ISystemCondition : public IInspectable

    get_ConditionType	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CBackground_CISystemConditionFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CBackground_CISystemConditionFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Background_ISystemConditionFactory <L"Windows.ApplicationModel.Background.ISystemConditionFactory">
DEFINE_IIDX(ISystemConditionFactory, "D269D1F1-05A7-49AE-87D7-16B2B8B9A553")

.comdef ISystemConditionFactory : public IInspectable

    Create		proc :Windows::ApplicationModel::Background::SystemConditionType, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CBackground_CINetworkOperatorNotificationTrigger_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CBackground_CINetworkOperatorNotificationTrigger_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Background_INetworkOperatorNotificationTrigger <L"Windows.ApplicationModel.Background.INetworkOperatorNotificationTrigger">
DEFINE_IIDX(INetworkOperatorNotificationTrigger, "90089CC6-63CD-480C-95D1-6E6AEF801E4A")

.comdef INetworkOperatorNotificationTrigger : public IInspectable

    get_NetworkAccountId proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CBackground_CINetworkOperatorNotificationTriggerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CBackground_CINetworkOperatorNotificationTriggerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Background_INetworkOperatorNotificationTriggerFactory <L"Windows.ApplicationModel.Background.INetworkOperatorNotificationTriggerFactory">
DEFINE_IIDX(INetworkOperatorNotificationTriggerFactory, "0A223E00-27D7-4353-ADB9-9265AAEA579D")

.comdef INetworkOperatorNotificationTriggerFactory : public IInspectable

    Create		proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CBackground_CITimeTrigger_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CBackground_CITimeTrigger_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Background_ITimeTrigger <L"Windows.ApplicationModel.Background.ITimeTrigger">
DEFINE_IIDX(ITimeTrigger, "656E5556-0B2A-4377-BA70-3B45A935547F")

.comdef ITimeTrigger : public IInspectable

    get_FreshnessTime	proc :ptr
    get_OneShot		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CBackground_CITimeTriggerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CBackground_CITimeTriggerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Background_ITimeTriggerFactory <L"Windows.ApplicationModel.Background.ITimeTriggerFactory">
DEFINE_IIDX(ITimeTriggerFactory, "38C682FE-9B54-45E6-B2F3-269B87A6F734")

.comdef ITimeTriggerFactory : public IInspectable

    Create		proc :UINT32, :boolean, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CBackground_CIMaintenanceTrigger_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CBackground_CIMaintenanceTrigger_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Background_IMaintenanceTrigger <L"Windows.ApplicationModel.Background.IMaintenanceTrigger">
DEFINE_IIDX(IMaintenanceTrigger, "68184C83-FC22-4CE5-841A-7239A9810047")

.comdef IMaintenanceTrigger : public IInspectable

    get_FreshnessTime	proc :ptr
    get_OneShot		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CBackground_CIMaintenanceTriggerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CBackground_CIMaintenanceTriggerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Background_IMaintenanceTriggerFactory <L"Windows.ApplicationModel.Background.IMaintenanceTriggerFactory">
DEFINE_IIDX(IMaintenanceTriggerFactory, "4B3DDB2E-97DD-4629-88B0-B06CF9482AE5")

.comdef IMaintenanceTriggerFactory : public IInspectable

    Create		proc :UINT32, :boolean, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CBackground_CIDeviceUseTrigger_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CBackground_CIDeviceUseTrigger_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Background_IDeviceUseTrigger <L"Windows.ApplicationModel.Background.IDeviceUseTrigger">
DEFINE_IIDX(IDeviceUseTrigger, "0DA68011-334F-4D57-B6EC-6DCA64B412E4")

.comdef IDeviceUseTrigger : public IInspectable

    RequestAsyncSimple	proc :HSTRING, :ptr
    RequestAsyncWithArguments proc :HSTRING, :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CBackground_CIDeviceServicingTrigger_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CBackground_CIDeviceServicingTrigger_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Background_IDeviceServicingTrigger <L"Windows.ApplicationModel.Background.IDeviceServicingTrigger">
DEFINE_IIDX(IDeviceServicingTrigger, "1AB217AD-6E34-49D3-9E6F-17F1B6DFA881")

.comdef IDeviceServicingTrigger : public IInspectable

    RequestAsyncSimple	proc :HSTRING, :Windows::Foundation::TimeSpan, :ptr
    RequestAsyncWithArguments proc :HSTRING, :Windows::Foundation::TimeSpan, :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CBackground_CILocationTrigger_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CBackground_CILocationTrigger_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Background_ILocationTrigger <L"Windows.ApplicationModel.Background.ILocationTrigger">
DEFINE_IIDX(ILocationTrigger, "47666A1C-6877-481E-8026-FF7E14A811A0")

.comdef ILocationTrigger : public IInspectable

    get_TriggerType	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CBackground_CILocationTriggerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CBackground_CILocationTriggerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Background_ILocationTriggerFactory <L"Windows.ApplicationModel.Background.ILocationTriggerFactory">
DEFINE_IIDX(ILocationTriggerFactory, "1106BB07-FF69-4E09-AA8B-1384EA475E98")

.comdef ILocationTriggerFactory : public IInspectable

    Create		proc :Windows::ApplicationModel::Background::LocationTriggerType, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CBackground_CINetworkOperatorHotspotAuthenticationTrigger_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CBackground_CINetworkOperatorHotspotAuthenticationTrigger_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Background_INetworkOperatorHotspotAuthenticationTrigger <L"Windows.ApplicationModel.Background.INetworkOperatorHotspotAuthenticationTrigger">
DEFINE_IIDX(INetworkOperatorHotspotAuthenticationTrigger, "E756C791-3001-4DE5-83C7-DE61D88831D0")

.comdef INetworkOperatorHotspotAuthenticationTrigger : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CBackground_CIPushNotificationTriggerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CBackground_CIPushNotificationTriggerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Background_IPushNotificationTriggerFactory <L"Windows.ApplicationModel.Background.IPushNotificationTriggerFactory">
DEFINE_IIDX(IPushNotificationTriggerFactory, "6DD8ED1B-458E-4FC2-BC2E-D5664F77ED19")

.comdef IPushNotificationTriggerFactory : public IInspectable

    Create		proc :HSTRING, :ptr
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_ApplicationModel_Background_AlarmApplicationManager_DEFINED
define RUNTIMECLASS_Windows_ApplicationModel_Background_AlarmApplicationManager_DEFINED
define RuntimeClass_Windows_ApplicationModel_Background_AlarmApplicationManager <L"Windows.ApplicationModel.Background.AlarmApplicationManager">
endif
ifndef RUNTIMECLASS_Windows_ApplicationModel_Background_BackgroundExecutionManager_DEFINED
define RUNTIMECLASS_Windows_ApplicationModel_Background_BackgroundExecutionManager_DEFINED
define RuntimeClass_Windows_ApplicationModel_Background_BackgroundExecutionManager <L"Windows.ApplicationModel.Background.BackgroundExecutionManager">
endif
ifndef RUNTIMECLASS_Windows_ApplicationModel_Background_BackgroundTaskRegistration_DEFINED
define RUNTIMECLASS_Windows_ApplicationModel_Background_BackgroundTaskRegistration_DEFINED
define RuntimeClass_Windows_ApplicationModel_Background_BackgroundTaskRegistration <L"Windows.ApplicationModel.Background.BackgroundTaskRegistration">
endif
ifndef RUNTIMECLASS_Windows_ApplicationModel_Background_BackgroundTaskDeferral_DEFINED
define RUNTIMECLASS_Windows_ApplicationModel_Background_BackgroundTaskDeferral_DEFINED
define RuntimeClass_Windows_ApplicationModel_Background_BackgroundTaskDeferral <L"Windows.ApplicationModel.Background.BackgroundTaskDeferral">
endif
ifndef RUNTIMECLASS_Windows_ApplicationModel_Background_BackgroundTaskProgressEventArgs_DEFINED
define RUNTIMECLASS_Windows_ApplicationModel_Background_BackgroundTaskProgressEventArgs_DEFINED
define RuntimeClass_Windows_ApplicationModel_Background_BackgroundTaskProgressEventArgs <L"Windows.ApplicationModel.Background.BackgroundTaskProgressEventArgs">
endif
ifndef RUNTIMECLASS_Windows_ApplicationModel_Background_BackgroundTaskCompletedEventArgs_DEFINED
define RUNTIMECLASS_Windows_ApplicationModel_Background_BackgroundTaskCompletedEventArgs_DEFINED
define RuntimeClass_Windows_ApplicationModel_Background_BackgroundTaskCompletedEventArgs <L"Windows.ApplicationModel.Background.BackgroundTaskCompletedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_ApplicationModel_Background_BackgroundTaskBuilder_DEFINED
define RUNTIMECLASS_Windows_ApplicationModel_Background_BackgroundTaskBuilder_DEFINED
define RuntimeClass_Windows_ApplicationModel_Background_BackgroundTaskBuilder <L"Windows.ApplicationModel.Background.BackgroundTaskBuilder">
endif
ifndef RUNTIMECLASS_Windows_ApplicationModel_Background_BackgroundWorkCost_DEFINED
define RUNTIMECLASS_Windows_ApplicationModel_Background_BackgroundWorkCost_DEFINED
define RuntimeClass_Windows_ApplicationModel_Background_BackgroundWorkCost <L"Windows.ApplicationModel.Background.BackgroundWorkCost">
endif
ifndef RUNTIMECLASS_Windows_ApplicationModel_Background_SystemTrigger_DEFINED
define RUNTIMECLASS_Windows_ApplicationModel_Background_SystemTrigger_DEFINED
define RuntimeClass_Windows_ApplicationModel_Background_SystemTrigger <L"Windows.ApplicationModel.Background.SystemTrigger">
endif
ifndef RUNTIMECLASS_Windows_ApplicationModel_Background_SystemCondition_DEFINED
define RUNTIMECLASS_Windows_ApplicationModel_Background_SystemCondition_DEFINED
define RuntimeClass_Windows_ApplicationModel_Background_SystemCondition <L"Windows.ApplicationModel.Background.SystemCondition">
endif
ifndef RUNTIMECLASS_Windows_ApplicationModel_Background_NetworkOperatorNotificationTrigger_DEFINED
define RUNTIMECLASS_Windows_ApplicationModel_Background_NetworkOperatorNotificationTrigger_DEFINED
define RuntimeClass_Windows_ApplicationModel_Background_NetworkOperatorNotificationTrigger <L"Windows.ApplicationModel.Background.NetworkOperatorNotificationTrigger">
endif
ifndef RUNTIMECLASS_Windows_ApplicationModel_Background_TimeTrigger_DEFINED
define RUNTIMECLASS_Windows_ApplicationModel_Background_TimeTrigger_DEFINED
define RuntimeClass_Windows_ApplicationModel_Background_TimeTrigger <L"Windows.ApplicationModel.Background.TimeTrigger">
endif
ifndef RUNTIMECLASS_Windows_ApplicationModel_Background_MaintenanceTrigger_DEFINED
define RUNTIMECLASS_Windows_ApplicationModel_Background_MaintenanceTrigger_DEFINED
define RuntimeClass_Windows_ApplicationModel_Background_MaintenanceTrigger <L"Windows.ApplicationModel.Background.MaintenanceTrigger">
endif
ifndef RUNTIMECLASS_Windows_ApplicationModel_Background_DeviceUseTrigger_DEFINED
define RUNTIMECLASS_Windows_ApplicationModel_Background_DeviceUseTrigger_DEFINED
define RuntimeClass_Windows_ApplicationModel_Background_DeviceUseTrigger <L"Windows.ApplicationModel.Background.DeviceUseTrigger">
endif
ifndef RUNTIMECLASS_Windows_ApplicationModel_Background_DeviceServicingTrigger_DEFINED
define RUNTIMECLASS_Windows_ApplicationModel_Background_DeviceServicingTrigger_DEFINED
define RuntimeClass_Windows_ApplicationModel_Background_DeviceServicingTrigger <L"Windows.ApplicationModel.Background.DeviceServicingTrigger">
endif
ifndef RUNTIMECLASS_Windows_ApplicationModel_Background_LocationTrigger_DEFINED
define RUNTIMECLASS_Windows_ApplicationModel_Background_LocationTrigger_DEFINED
define RuntimeClass_Windows_ApplicationModel_Background_LocationTrigger <L"Windows.ApplicationModel.Background.LocationTrigger">
endif
ifndef RUNTIMECLASS_Windows_ApplicationModel_Background_NetworkOperatorHotspotAuthenticationTrigger_DEFINED
define RUNTIMECLASS_Windows_ApplicationModel_Background_NetworkOperatorHotspotAuthenticationTrigger_DEFINED
define RuntimeClass_Windows_ApplicationModel_Background_NetworkOperatorHotspotAuthenticationTrigger <L"Windows.ApplicationModel.Background.NetworkOperatorHotspotAuthenticationTrigger">
endif
ifndef RUNTIMECLASS_Windows_ApplicationModel_Background_PushNotificationTrigger_DEFINED
define RUNTIMECLASS_Windows_ApplicationModel_Background_PushNotificationTrigger_DEFINED
define RuntimeClass_Windows_ApplicationModel_Background_PushNotificationTrigger <L"Windows.ApplicationModel.Background.PushNotificationTrigger">
endif

endif
