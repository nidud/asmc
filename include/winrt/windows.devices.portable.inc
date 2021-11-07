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

ifndef __windows2Edevices2Eportable_h__
define __windows2Edevices2Eportable_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
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
    GetDeviceSelectorFromServiceId proc :ptr GUID, :ptr
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
