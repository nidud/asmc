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

ifndef __windows2Edevices2Ebackground_h__
define __windows2Edevices2Ebackground_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc

.namespace Windows
.namespace Devices
.namespace Background

ifndef ____x_ABI_CWindows_CDevices_CBackground_CIDeviceUseDetails_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CBackground_CIDeviceUseDetails_INTERFACE_DEFINED__
DEFINE_IIDX(IDeviceUseDetails, "7D565141-557E-4154-B994-E4F7A11FB323")

.comdef IDeviceUseDetails : public IInspectable

    get_DeviceId        proc :ptr
    get_Arguments       proc :ptr
   .ends

endif


ifndef ____x_ABI_CWindows_CDevices_CBackground_CIDeviceServicingDetails_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CBackground_CIDeviceServicingDetails_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Background_IDeviceServicingDetails <L"Windows.Devices.Background.IDeviceServicingDetails">
DEFINE_IIDX(IDeviceServicingDetails, "4AABEE29-2344-4AC4-8527-4A8EF6905645")

.comdef IDeviceServicingDetails : public IInspectable

    get_DeviceId        proc :ptr
    get_Arguments       proc :ptr
    get_ExpectedDuration proc :ptr
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_Devices_Background_DeviceUseDetails_DEFINED
define RUNTIMECLASS_Windows_Devices_Background_DeviceUseDetails_DEFINED
define RuntimeClass_Windows_Devices_Background_DeviceUseDetails <L"Windows.Devices.Background.DeviceUseDetails">
endif
ifndef RUNTIMECLASS_Windows_Devices_Background_DeviceServicingDetails_DEFINED
define RUNTIMECLASS_Windows_Devices_Background_DeviceServicingDetails_DEFINED
define RuntimeClass_Windows_Devices_Background_DeviceServicingDetails <L"Windows.Devices.Background.DeviceServicingDetails">
endif

endif
