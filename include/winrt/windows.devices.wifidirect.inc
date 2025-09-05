ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Edevices2Ewifidirect_h__
define __windows2Edevices2Ewifidirect_h__
ifndef __windows2Efoundation_h__
include Windows.Foundation.inc
endif
include Windows.Networking.inc

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CDevices__CWiFiDirect__CWiFiDirectDevice_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CDevices__CWiFiDirect__CWiFiDirectDevice_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CDevices__CWiFiDirect__CWiFiDirectDevice, "d34abe17-fb19-57be-bc41-0eb83dea151c")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CDevices__CWiFiDirect__CWiFiDirectDevice : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CDevices__CWiFiDirect__CWiFiDirectDevice_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CDevices__CWiFiDirect__CWiFiDirectDevice_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CDevices__CWiFiDirect__CWiFiDirectDevice, "dad01b61-a82d-566c-ba82-224c11500669")

.comdef __FIAsyncOperation_1_Windows__CDevices__CWiFiDirect__CWiFiDirectDevice : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CDevices__CWiFiDirect__CWiFiDirectDevice_IInspectable_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CDevices__CWiFiDirect__CWiFiDirectDevice_IInspectable_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CDevices__CWiFiDirect__CWiFiDirectDevice_IInspectable, "9208929a-2a3c-50ad-aa08-a0a986edbabe")

.comdef __FITypedEventHandler_2_Windows__CDevices__CWiFiDirect__CWiFiDirectDevice_IInspectable : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

.namespace Windows
.namespace Devices
.namespace WiFiDirect

.enum WiFiDirectConnectionStatus {
    WiFiDirectConnectionStatus_Disconnected	= 0,
    WiFiDirectConnectionStatus_Connected	= 1
    }

ifndef ____x_ABI_CWindows_CDevices_CWiFiDirect_CIWiFiDirectDeviceStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CWiFiDirect_CIWiFiDirectDeviceStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_WiFiDirect_IWiFiDirectDeviceStatics <L"Windows.Devices.WiFiDirect.IWiFiDirectDeviceStatics">
DEFINE_IIDX(IWiFiDirectDeviceStatics, "E86CB57C-3AAC-4851-A792-482AAF931B04")

.comdef IWiFiDirectDeviceStatics : public IInspectable

    GetDeviceSelector	proc :ptr
    FromIdAsync		proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CWiFiDirect_CIWiFiDirectDevice_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CWiFiDirect_CIWiFiDirectDevice_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_WiFiDirect_IWiFiDirectDevice <L"Windows.Devices.WiFiDirect.IWiFiDirectDevice">
DEFINE_IIDX(IWiFiDirectDevice, "72DEAAA8-72EB-4DAE-8A28-8513355D2777")

.comdef IWiFiDirectDevice : public IInspectable

    get_ConnectionStatus proc :ptr
    get_DeviceId	proc :ptr
    add_ConnectionStatusChanged proc :ptr, :ptr
    remove_ConnectionStatusChanged proc :EventRegistrationToken
    GetConnectionEndpointPairs proc :ptr
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_Devices_WiFiDirect_WiFiDirectDevice_DEFINED
define RUNTIMECLASS_Windows_Devices_WiFiDirect_WiFiDirectDevice_DEFINED
define RuntimeClass_Windows_Devices_WiFiDirect_WiFiDirectDevice <L"Windows.Devices.WiFiDirect.WiFiDirectDevice">
endif

endif
