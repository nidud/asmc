ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Emedia2Estreaming2Edevices_h__
define __windows2Emedia2Estreaming2Edevices_h__

include windows.foundation.inc
include Windows.Storage.Streams.inc
include windows.foundation.collections.inc

.namespace Windows
.namespace Media
.namespace Streaming

.enum DeviceTypes {
    DeviceTypes_Unknown = 0,
    DeviceTypes_DigitalMediaRenderer	= 0x1,
    DeviceTypes_DigitalMediaServer	= 0x2,
    DeviceTypes_DigitalMediaPlayer	= 0x4
    }

.enum ConnectionStatus {
    ConnectionStatus_Online,
    ConnectionStatus_Offline,
    ConnectionStatus_Sleeping
    }

ifndef ____x_ABI_CWindows_CMedia_CStreaming_CIDeviceControllerFinderHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CStreaming_CIDeviceControllerFinderHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IDeviceControllerFinderHandler, "a88a7d06-988c-4403-9d8a-015bed140b34")

.comdef IDeviceControllerFinderHandler : public IUnknown

    _Invoke		proc :ptr, :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CStreaming_CIConnectionStatusHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CStreaming_CIConnectionStatusHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IConnectionStatusHandler, "b571c28c-a472-48d5-88d2-8adcaf1b8813")

.comdef IConnectionStatusHandler : public IUnknown

    _Invoke		proc :ptr, :Windows::Media::Streaming::ConnectionStatus
   .ends

endif

.endn
.endn
.endn

ifndef ____FIIterator_1_Windows__CMedia__CStreaming__CIBasicDevice_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CMedia__CStreaming__CIBasicDevice_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CMedia__CStreaming__CIBasicDevice, "84a8c766-4bc5-5757-9f1b-f61cfd9e5693")

.comdef __FIIterator_1_Windows__CMedia__CStreaming__CIBasicDevice : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CMedia__CStreaming__CIBasicDevice_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CMedia__CStreaming__CIBasicDevice_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CMedia__CStreaming__CIBasicDevice, "7d468b5e-763b-59cd-a086-ec6d8be0d858")

.comdef __FIIterable_1_Windows__CMedia__CStreaming__CIBasicDevice : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CMedia__CStreaming__CIBasicDevice_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CMedia__CStreaming__CIBasicDevice_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CMedia__CStreaming__CIBasicDevice, "a55cf16b-71a2-5525-ac3b-2f5bc1eeec46")

.comdef __FIVectorView_1_Windows__CMedia__CStreaming__CIBasicDevice : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVector_1_Windows__CMedia__CStreaming__CIBasicDevice_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CMedia__CStreaming__CIBasicDevice_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CMedia__CStreaming__CIBasicDevice, "4c58be45-d16f-5b3a-840d-a6b4e20b7088")

.comdef __FIVector_1_Windows__CMedia__CStreaming__CIBasicDevice : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    GetView		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    SetAt		proc :SINT, :ptr
    InsertAt		proc :SINT, :ptr
    RemoveAt		proc :SINT
    Append		proc :ptr
    RemoveAtEnd		proc
    Clear		proc
    GetMany		proc :SINT, :SINT, :ptr, :ptr
    ReplaceAll		proc :SINT, :ptr
   .ends

endif

.namespace Windows
.namespace Media
.namespace Streaming

ifndef ____x_ABI_CWindows_CMedia_CStreaming_CIDeviceController_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CStreaming_CIDeviceController_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Streaming_IDeviceController <L"Windows.Media.Streaming.IDeviceController">
DEFINE_IIDX(IDeviceController, "4feeb26d-50a7-402b-896a-be95064d6bff")

.comdef IDeviceController : public IInspectable

    get_CachedDevices	proc :ptr
    AddDevice		proc :HSTRING
    RemoveDevice	proc :ptr
    add_DeviceArrival	proc :ptr, :ptr
    remove_DeviceArrival proc :EventRegistrationToken
    add_DeviceDeparture proc :ptr, :ptr
    remove_DeviceDeparture proc :EventRegistrationToken
   .ends

endif

.endn
.endn
.endn

ifndef ____FIIterator_1_Windows__CMedia__CStreaming__CIDeviceIcon_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CMedia__CStreaming__CIDeviceIcon_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CMedia__CStreaming__CIDeviceIcon, "57fd211a-4ef0-58a0-90e2-7c3b816102c9")

.comdef __FIIterator_1_Windows__CMedia__CStreaming__CIDeviceIcon : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CMedia__CStreaming__CIDeviceIcon_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CMedia__CStreaming__CIDeviceIcon_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CMedia__CStreaming__CIDeviceIcon, "16077ee6-dcfc-53aa-ab0e-d666ac819d6c")

.comdef __FIIterable_1_Windows__CMedia__CStreaming__CIDeviceIcon : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CMedia__CStreaming__CIDeviceIcon_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CMedia__CStreaming__CIDeviceIcon_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CMedia__CStreaming__CIDeviceIcon, "ff195e52-48eb-5709-be50-3a3914c189db")

.comdef __FIVectorView_1_Windows__CMedia__CStreaming__CIDeviceIcon : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVector_1_Windows__CMedia__CStreaming__CIDeviceIcon_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CMedia__CStreaming__CIDeviceIcon_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CMedia__CStreaming__CIDeviceIcon, "a32d7731-05f6-55a2-930f-1cf5a12b19ae")

.comdef __FIVector_1_Windows__CMedia__CStreaming__CIDeviceIcon : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    GetView		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    SetAt		proc :SINT, :ptr
    InsertAt		proc :SINT, :ptr
    RemoveAt		proc :SINT
    Append		proc :ptr
    RemoveAtEnd		proc
    Clear		proc
    GetMany		proc :SINT, :SINT, :ptr, :ptr
    ReplaceAll		proc :SINT, :ptr
   .ends

endif

.namespace Windows
.namespace Media
.namespace Streaming

ifndef ____x_ABI_CWindows_CMedia_CStreaming_CIBasicDevice_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CStreaming_CIBasicDevice_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Streaming_IBasicDevice <L"Windows.Media.Streaming.IBasicDevice">
DEFINE_IIDX(IBasicDevice, "f4f26cbb-7962-48b7-80f7-c3a5d753bcb0")

.comdef IBasicDevice : public IInspectable

    get_FriendlyName	proc :ptr
    put_FriendlyName	proc :HSTRING
    get_ManufacturerName proc :ptr
    get_ManufacturerUrl proc :ptr
    get_UniqueDeviceName proc :ptr
    get_ModelName	proc :ptr
    get_ModelNumber	proc :ptr
    get_ModelUrl	proc :ptr
    get_Description	proc :ptr
    get_SerialNumber	proc :ptr
    get_PresentationUrl proc :ptr
    get_RemoteStreamingUrls proc :ptr
    get_PhysicalAddresses proc :ptr
    get_IpAddresses	proc :ptr
    get_CanWakeDevices	proc :ptr
    get_DiscoveredOnCurrentNetwork proc :ptr
    get_Type		proc :ptr
    get_Icons		proc :ptr
    get_ConnectionStatus proc :ptr
    add_ConnectionStatusChanged proc :ptr, :ptr
    remove_ConnectionStatusChanged proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CStreaming_CIActiveBasicDevice_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CStreaming_CIActiveBasicDevice_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Streaming_IActiveBasicDevice <L"Windows.Media.Streaming.IActiveBasicDevice">
DEFINE_IIDX(IActiveBasicDevice, "b64d6974-6e79-49af-9933-908b6e9a160c")

.comdef IActiveBasicDevice : public IInspectable

    get_MaxVolume	proc :ptr
    get_IsMuteSupported proc :ptr
    get_IsSetNextSourceSupported proc :ptr
    get_IsAudioSupported proc :ptr
    get_IsVideoSupported proc :ptr
    get_IsImageSupported proc :ptr
    get_IsSearchSupported proc :ptr
    GetCachedSinkProtocolInfo proc :ptr
    SetCachedSinkProtocolInfo proc :HSTRING
    GetCachedExtraSinkProtocolInfo proc :ptr
    GetEffectiveBandwidth proc :boolean, :ptr
    GetCachedBitrateMeasurement proc :GUID, :ptr
    SetCachedBitrateMeasurement proc :GUID, :UINT64
    get_LogicalNetworkInterface proc :ptr
    get_PhysicalNetworkInterface proc :ptr
    NotifyStreamingStatus proc :boolean
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CStreaming_CIDeviceIcon_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CStreaming_CIDeviceIcon_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Streaming_IDeviceIcon <L"Windows.Media.Streaming.IDeviceIcon">
DEFINE_IIDX(IDeviceIcon, "8ffb1a1e-023d-4de1-b556-ab5abf01929c")

.comdef IDeviceIcon : public IInspectable

    get_Width		proc :ptr
    get_Height		proc :ptr
    get_ContentType	proc :ptr
    get_Stream		proc :ptr
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_Media_Streaming_DeviceController_DEFINED
define RUNTIMECLASS_Windows_Media_Streaming_DeviceController_DEFINED
define RuntimeClass_Windows_Media_Streaming_DeviceController <L"Windows.Media.Streaming.DeviceController">
endif
ifndef RUNTIMECLASS_Windows_Media_Streaming_BasicDevice_DEFINED
define RUNTIMECLASS_Windows_Media_Streaming_BasicDevice_DEFINED
define RuntimeClass_Windows_Media_Streaming_BasicDevice <L"Windows.Media.Streaming.BasicDevice">
endif
ifndef RUNTIMECLASS_Windows_Media_Streaming_ActiveBasicDevice_DEFINED
define RUNTIMECLASS_Windows_Media_Streaming_ActiveBasicDevice_DEFINED
define RuntimeClass_Windows_Media_Streaming_ActiveBasicDevice <L"Windows.Media.Streaming.ActiveBasicDevice">
endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CMedia__CStreaming__CActiveBasicDevice_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CMedia__CStreaming__CActiveBasicDevice_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CMedia__CStreaming__CActiveBasicDevice, "4c0d279c-4b4e-5657-b609-6f15ff54212e")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CMedia__CStreaming__CActiveBasicDevice : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CMedia__CStreaming__CActiveBasicDevice_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CMedia__CStreaming__CActiveBasicDevice_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CMedia__CStreaming__CActiveBasicDevice, "0c4a4010-9046-5bff-8cc5-cbcde4c2d5c1")

.comdef __FIAsyncOperation_1_Windows__CMedia__CStreaming__CActiveBasicDevice : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CMedia__CStreaming__CDevicePair_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CMedia__CStreaming__CDevicePair_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CMedia__CStreaming__CDevicePair, "cde8d503-5136-5cb9-ab04-11502ec5afeb")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CMedia__CStreaming__CDevicePair : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CMedia__CStreaming__CDevicePair_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CMedia__CStreaming__CDevicePair_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CMedia__CStreaming__CDevicePair, "d3d31100-6a6e-5775-ae0b-55cbeb23cacf")

.comdef __FIAsyncOperation_1_Windows__CMedia__CStreaming__CDevicePair : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

.namespace Windows
.namespace Media
.namespace Streaming

ifndef ____x_ABI_CWindows_CMedia_CStreaming_CIActiveBasicDeviceStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CStreaming_CIActiveBasicDeviceStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Streaming_IActiveBasicDeviceStatics <L"Windows.Media.Streaming.IActiveBasicDeviceStatics">
DEFINE_IIDX(IActiveBasicDeviceStatics, "6d33255d-3642-4618-9db6-43524f4deadc")

.comdef IActiveBasicDeviceStatics : public IInspectable

    CreateBasicDeviceAsync proc :HSTRING, :Windows::Media::Streaming::DeviceTypes, :ptr
    CloneBasicDeviceAsync proc :ptr, :ptr
    GetDevicesOnMatchingNetworkAsync proc :ptr, :ptr, :boolean, :boolean, :ptr
    CreateDevicesOnMatchingNetworkAsync proc :HSTRING, :ptr, :boolean, :boolean, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CStreaming_CIDevicePair_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CStreaming_CIDevicePair_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Streaming_IDevicePair <L"Windows.Media.Streaming.IDevicePair">
DEFINE_IIDX(IDevicePair, "f1a423f1-b7b4-449c-a90d-aea8e17c5e5f")

.comdef IDevicePair : public IInspectable

    get_Server		proc :ptr
    get_Renderer	proc :ptr
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_Media_Streaming_DevicePair_DEFINED
define RUNTIMECLASS_Windows_Media_Streaming_DevicePair_DEFINED
define RuntimeClass_Windows_Media_Streaming_DevicePair <L"Windows.Media.Streaming.DevicePair">
endif

endif
