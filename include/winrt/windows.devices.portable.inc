ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Edevices2Eportable_h__
define __windows2Edevices2Eportable_h__
ifndef __windows2Efoundation_h__
include Windows.Foundation.inc
endif
include Windows.Storage.inc

.namespace Windows
.namespace Devices
.namespace Portable

.enum ServiceDeviceType {
    ServiceDeviceType_CalendarService   = 0,
    ServiceDeviceType_ContactsService   = 1,
    ServiceDeviceType_DeviceStatusService   = 2,
    ServiceDeviceType_NotesService  = 3,
    ServiceDeviceType_RingtonesService  = 4,
    ServiceDeviceType_SmsService    = 5,
    ServiceDeviceType_TasksService  = 6
    }

ifndef ____x_ABI_CWindows_CDevices_CPortable_CIStorageDeviceStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CPortable_CIStorageDeviceStatics_INTERFACE_DEFINED__
DEFINE_IIDX(IStorageDeviceStatics, "5ECE44EE-1B23-4DD2-8652-BC164F003128")

.comdef IStorageDeviceStatics : public IInspectable

    FromId              proc :HSTRING, :ptr
    GetDeviceSelector   proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CPortable_CIServiceDeviceStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CPortable_CIServiceDeviceStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Portable_IServiceDeviceStatics <L"Windows.Devices.Portable.IServiceDeviceStatics">
DEFINE_IIDX(IServiceDeviceStatics, "A88214E1-59C7-4A20-ABA6-9F6707937230")

.comdef IServiceDeviceStatics : public IInspectable

    GetDeviceSelector   proc :Windows::Devices::Portable::ServiceDeviceType, :ptr
    GetDeviceSelectorFromServiceId proc :ptr, :ptr
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_Devices_Portable_StorageDevice_DEFINED
define RUNTIMECLASS_Windows_Devices_Portable_StorageDevice_DEFINED
define RuntimeClass_Windows_Devices_Portable_StorageDevice <L"Windows.Devices.Portable.StorageDevice">
endif
ifndef RUNTIMECLASS_Windows_Devices_Portable_ServiceDevice_DEFINED
define RUNTIMECLASS_Windows_Devices_Portable_ServiceDevice_DEFINED
define RuntimeClass_Windows_Devices_Portable_ServiceDevice <L"Windows.Devices.Portable.ServiceDevice">
endif

endif
