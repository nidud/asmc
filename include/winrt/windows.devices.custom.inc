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

ifndef __windows2Edevices2Ecustom_h__
define __windows2Edevices2Ecustom_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include Windows.Storage.Streams.inc
include windows.foundation.collections.inc

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CDevices__CCustom__CCustomDevice_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CDevices__CCustom__CCustomDevice_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CDevices__CCustom__CCustomDevice, "1fdd39b0-e0e5-5c59-b27d-a549b1075ce9")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CDevices__CCustom__CCustomDevice : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CDevices__CCustom__CCustomDevice_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CDevices__CCustom__CCustomDevice_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CDevices__CCustom__CCustomDevice, "2a6344aa-0568-548e-a1a2-b6bb451d228c")

.comdef __FIAsyncOperation_1_Windows__CDevices__CCustom__CCustomDevice : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

.namespace Windows
.namespace Devices
.namespace Custom

.enum IOControlAccessMode {
    IOControlAccessMode_Any	= 0,
    IOControlAccessMode_Read	= 1,
    IOControlAccessMode_Write	= 2,
    IOControlAccessMode_ReadWrite	= 3
    }

.enum IOControlBufferingMethod {
    IOControlBufferingMethod_Buffered	= 0,
    IOControlBufferingMethod_DirectInput	= 1,
    IOControlBufferingMethod_DirectOutput	= 2,
    IOControlBufferingMethod_Neither	= 3
    }

.enum DeviceAccessMode {
    DeviceAccessMode_Read	= 0,
    DeviceAccessMode_Write	= 1,
    DeviceAccessMode_ReadWrite	= 2
    }

.enum DeviceSharingMode {
    DeviceSharingMode_Shared	= 0,
    DeviceSharingMode_Exclusive = 1
    }

ifndef ____x_ABI_CWindows_CDevices_CCustom_CIKnownDeviceTypesStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CCustom_CIKnownDeviceTypesStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Custom_IKnownDeviceTypesStatics <L"Windows.Devices.Custom.IKnownDeviceTypesStatics">
DEFINE_IIDX(IKnownDeviceTypesStatics, "EE5479C2-5448-45DA-AD1B-24948C239094")

.comdef IKnownDeviceTypesStatics : public IInspectable

    get_Unknown		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CCustom_CIIOControlCode_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CCustom_CIIOControlCode_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Custom_IIOControlCode <L"Windows.Devices.Custom.IIOControlCode">
DEFINE_IIDX(IIOControlCode, "0E9559E7-60C8-4375-A761-7F8808066C60")

.comdef IIOControlCode : public IInspectable

    get_AccessMode	proc :ptr
    get_BufferingMethod proc :ptr
    get_Function	proc :ptr
    get_DeviceType	proc :ptr
    get_ControlCode	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CCustom_CIIOControlCodeFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CCustom_CIIOControlCodeFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Custom_IIOControlCodeFactory <L"Windows.Devices.Custom.IIOControlCodeFactory">
DEFINE_IIDX(IIOControlCodeFactory, "856A7CF0-4C11-44AE-AFC6-B8D4A212788F")

.comdef IIOControlCodeFactory : public IInspectable

    CreateIOControlCode proc :UINT16, :UINT16, :Windows::Devices::Custom::IOControlAccessMode, :Windows::Devices::Custom::IOControlBufferingMethod, :ptr ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CCustom_CICustomDeviceStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CCustom_CICustomDeviceStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Custom_ICustomDeviceStatics <L"Windows.Devices.Custom.ICustomDeviceStatics">
DEFINE_IIDX(ICustomDeviceStatics, "C8220312-EF4C-46B1-A58E-EEB308DC8917")

.comdef ICustomDeviceStatics : public IInspectable

    GetDeviceSelector	proc :GUID, :ptr
    FromIdAsync		proc :HSTRING, :Windows::Devices::Custom::DeviceAccessMode, :Windows::Devices::Custom::DeviceSharingMode, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CCustom_CICustomDevice_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CCustom_CICustomDevice_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Custom_ICustomDevice <L"Windows.Devices.Custom.ICustomDevice">
DEFINE_IIDX(ICustomDevice, "DD30251F-C48B-43BD-BCB1-DEC88F15143E")

.comdef ICustomDevice : public IInspectable

    get_InputStream	proc :ptr
    get_OutputStream	proc :ptr
    SendIOControlAsync	proc :ptr, :ptr, :ptr, :ptr
    TrySendIOControlAsync proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_Devices_Custom_KnownDeviceTypes_DEFINED
define RUNTIMECLASS_Windows_Devices_Custom_KnownDeviceTypes_DEFINED
define RuntimeClass_Windows_Devices_Custom_KnownDeviceTypes <L"Windows.Devices.Custom.KnownDeviceTypes">
endif
ifndef RUNTIMECLASS_Windows_Devices_Custom_IOControlCode_DEFINED
define RUNTIMECLASS_Windows_Devices_Custom_IOControlCode_DEFINED
define RuntimeClass_Windows_Devices_Custom_IOControlCode <L"Windows.Devices.Custom.IOControlCode">
endif
ifndef RUNTIMECLASS_Windows_Devices_Custom_CustomDevice_DEFINED
define RUNTIMECLASS_Windows_Devices_Custom_CustomDevice_DEFINED
define RuntimeClass_Windows_Devices_Custom_CustomDevice <L"Windows.Devices.Custom.CustomDevice">
endif

endif
