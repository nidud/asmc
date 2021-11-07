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

ifndef __windows2Edevices2Eusb_h__
define __windows2Edevices2Eusb_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include Windows.Storage.Streams.inc
include windows.foundation.collections.inc

ifndef ____FIIterator_1_Windows__CDevices__CUsb__CUsbBulkInEndpointDescriptor_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CDevices__CUsb__CUsbBulkInEndpointDescriptor_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CDevices__CUsb__CUsbBulkInEndpointDescriptor, "ea511030-89c4-503d-8caf-667f4230d2a9")

.comdef __FIIterator_1_Windows__CDevices__CUsb__CUsbBulkInEndpointDescriptor : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CDevices__CUsb__CUsbBulkInEndpointDescriptor_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CDevices__CUsb__CUsbBulkInEndpointDescriptor_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CDevices__CUsb__CUsbBulkInEndpointDescriptor, "101b1fd9-f1c9-5dda-9ad4-71176fa839b2")

.comdef __FIIterable_1_Windows__CDevices__CUsb__CUsbBulkInEndpointDescriptor : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CDevices__CUsb__CUsbBulkInPipe_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CDevices__CUsb__CUsbBulkInPipe_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CDevices__CUsb__CUsbBulkInPipe, "d7af2c5b-528d-5cbb-a997-d830ade704c7")

.comdef __FIIterator_1_Windows__CDevices__CUsb__CUsbBulkInPipe : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CDevices__CUsb__CUsbBulkInPipe_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CDevices__CUsb__CUsbBulkInPipe_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CDevices__CUsb__CUsbBulkInPipe, "2201a671-42d2-508d-a848-64b5447083c8")

.comdef __FIIterable_1_Windows__CDevices__CUsb__CUsbBulkInPipe : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CDevices__CUsb__CUsbBulkOutEndpointDescriptor_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CDevices__CUsb__CUsbBulkOutEndpointDescriptor_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CDevices__CUsb__CUsbBulkOutEndpointDescriptor, "a8b89ab3-883d-5361-9903-f489cc62bea5")

.comdef __FIIterator_1_Windows__CDevices__CUsb__CUsbBulkOutEndpointDescriptor : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CDevices__CUsb__CUsbBulkOutEndpointDescriptor_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CDevices__CUsb__CUsbBulkOutEndpointDescriptor_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CDevices__CUsb__CUsbBulkOutEndpointDescriptor, "b80beb39-62b3-5f59-b3e7-882cc9c5b0c0")

.comdef __FIIterable_1_Windows__CDevices__CUsb__CUsbBulkOutEndpointDescriptor : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CDevices__CUsb__CUsbBulkOutPipe_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CDevices__CUsb__CUsbBulkOutPipe_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CDevices__CUsb__CUsbBulkOutPipe, "46dd2f6a-573b-5c45-b168-9223038491dd")

.comdef __FIIterator_1_Windows__CDevices__CUsb__CUsbBulkOutPipe : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CDevices__CUsb__CUsbBulkOutPipe_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CDevices__CUsb__CUsbBulkOutPipe_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CDevices__CUsb__CUsbBulkOutPipe, "9824caba-5ca6-5c2d-80cf-1949026d7857")

.comdef __FIIterable_1_Windows__CDevices__CUsb__CUsbBulkOutPipe : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CDevices__CUsb__CUsbDescriptor_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CDevices__CUsb__CUsbDescriptor_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CDevices__CUsb__CUsbDescriptor, "521598ed-0167-528e-990d-52abb712f072")

.comdef __FIIterator_1_Windows__CDevices__CUsb__CUsbDescriptor : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CDevices__CUsb__CUsbDescriptor_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CDevices__CUsb__CUsbDescriptor_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CDevices__CUsb__CUsbDescriptor, "989909a5-5a03-51fb-bd94-84da7bda8819")

.comdef __FIIterable_1_Windows__CDevices__CUsb__CUsbDescriptor : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CDevices__CUsb__CUsbInterface_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CDevices__CUsb__CUsbInterface_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CDevices__CUsb__CUsbInterface, "216b5a5f-63e3-5a9b-9c99-b09cbc0ff3b1")

.comdef __FIIterator_1_Windows__CDevices__CUsb__CUsbInterface : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CDevices__CUsb__CUsbInterface_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CDevices__CUsb__CUsbInterface_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CDevices__CUsb__CUsbInterface, "f54037ed-92e9-590d-b904-3ad7bfa9a621")

.comdef __FIIterable_1_Windows__CDevices__CUsb__CUsbInterface : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CDevices__CUsb__CUsbInterfaceSetting_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CDevices__CUsb__CUsbInterfaceSetting_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CDevices__CUsb__CUsbInterfaceSetting, "71267ec7-5697-5dea-b2f8-14cf698ec0ad")

.comdef __FIIterator_1_Windows__CDevices__CUsb__CUsbInterfaceSetting : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CDevices__CUsb__CUsbInterfaceSetting_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CDevices__CUsb__CUsbInterfaceSetting_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CDevices__CUsb__CUsbInterfaceSetting, "1aaf5739-9c2c-533e-a0e9-d53fdb45d15d")

.comdef __FIIterable_1_Windows__CDevices__CUsb__CUsbInterfaceSetting : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CDevices__CUsb__CUsbInterruptInEndpointDescriptor_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CDevices__CUsb__CUsbInterruptInEndpointDescriptor_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CDevices__CUsb__CUsbInterruptInEndpointDescriptor, "6717500f-ec1c-5b12-bf33-0e3e3d244587")

.comdef __FIIterator_1_Windows__CDevices__CUsb__CUsbInterruptInEndpointDescriptor : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CDevices__CUsb__CUsbInterruptInEndpointDescriptor_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CDevices__CUsb__CUsbInterruptInEndpointDescriptor_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CDevices__CUsb__CUsbInterruptInEndpointDescriptor, "8a7bac69-1f10-59c7-9837-72cfed7154a4")

.comdef __FIIterable_1_Windows__CDevices__CUsb__CUsbInterruptInEndpointDescriptor : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CDevices__CUsb__CUsbInterruptInPipe_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CDevices__CUsb__CUsbInterruptInPipe_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CDevices__CUsb__CUsbInterruptInPipe, "e3a7b1c0-74f6-5292-a22a-672aa2b49985")

.comdef __FIIterator_1_Windows__CDevices__CUsb__CUsbInterruptInPipe : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CDevices__CUsb__CUsbInterruptInPipe_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CDevices__CUsb__CUsbInterruptInPipe_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CDevices__CUsb__CUsbInterruptInPipe, "39aef336-18aa-5be4-86d9-e332fe2632f3")

.comdef __FIIterable_1_Windows__CDevices__CUsb__CUsbInterruptInPipe : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CDevices__CUsb__CUsbInterruptOutEndpointDescriptor_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CDevices__CUsb__CUsbInterruptOutEndpointDescriptor_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CDevices__CUsb__CUsbInterruptOutEndpointDescriptor, "4b6426db-db32-5b51-adad-04532ea94acd")

.comdef __FIIterator_1_Windows__CDevices__CUsb__CUsbInterruptOutEndpointDescriptor : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CDevices__CUsb__CUsbInterruptOutEndpointDescriptor_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CDevices__CUsb__CUsbInterruptOutEndpointDescriptor_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CDevices__CUsb__CUsbInterruptOutEndpointDescriptor, "09393d62-2316-536b-8a10-7038884ab2a7")

.comdef __FIIterable_1_Windows__CDevices__CUsb__CUsbInterruptOutEndpointDescriptor : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CDevices__CUsb__CUsbInterruptOutPipe_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CDevices__CUsb__CUsbInterruptOutPipe_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CDevices__CUsb__CUsbInterruptOutPipe, "cbd8d8a8-2286-5cbd-a6e4-962742ffd91a")

.comdef __FIIterator_1_Windows__CDevices__CUsb__CUsbInterruptOutPipe : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CDevices__CUsb__CUsbInterruptOutPipe_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CDevices__CUsb__CUsbInterruptOutPipe_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CDevices__CUsb__CUsbInterruptOutPipe, "e61a011e-4abe-53f2-83b3-ed4a949d2e3f")

.comdef __FIIterable_1_Windows__CDevices__CUsb__CUsbInterruptOutPipe : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CDevices__CUsb__CUsbBulkInEndpointDescriptor_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CDevices__CUsb__CUsbBulkInEndpointDescriptor_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CDevices__CUsb__CUsbBulkInEndpointDescriptor, "9c69ac78-309e-5763-af26-9706ffa47ec0")

.comdef __FIVectorView_1_Windows__CDevices__CUsb__CUsbBulkInEndpointDescriptor : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CDevices__CUsb__CUsbBulkInPipe_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CDevices__CUsb__CUsbBulkInPipe_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CDevices__CUsb__CUsbBulkInPipe, "a93c84bc-6484-5959-b61a-703cc7115f6f")

.comdef __FIVectorView_1_Windows__CDevices__CUsb__CUsbBulkInPipe : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CDevices__CUsb__CUsbBulkOutEndpointDescriptor_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CDevices__CUsb__CUsbBulkOutEndpointDescriptor_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CDevices__CUsb__CUsbBulkOutEndpointDescriptor, "22a53676-a3ea-5dcd-bb39-b28a5327c4a3")

.comdef __FIVectorView_1_Windows__CDevices__CUsb__CUsbBulkOutEndpointDescriptor : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CDevices__CUsb__CUsbBulkOutPipe_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CDevices__CUsb__CUsbBulkOutPipe_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CDevices__CUsb__CUsbBulkOutPipe, "0a873512-15f1-5e8e-a72a-045cfd7a5e83")

.comdef __FIVectorView_1_Windows__CDevices__CUsb__CUsbBulkOutPipe : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CDevices__CUsb__CUsbDescriptor_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CDevices__CUsb__CUsbDescriptor_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CDevices__CUsb__CUsbDescriptor, "5408baa2-291e-537a-b61f-137062f7ff7d")

.comdef __FIVectorView_1_Windows__CDevices__CUsb__CUsbDescriptor : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CDevices__CUsb__CUsbInterface_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CDevices__CUsb__CUsbInterface_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CDevices__CUsb__CUsbInterface, "9c69ec7f-2e42-58cd-a74a-f4974811134d")

.comdef __FIVectorView_1_Windows__CDevices__CUsb__CUsbInterface : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CDevices__CUsb__CUsbInterfaceSetting_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CDevices__CUsb__CUsbInterfaceSetting_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CDevices__CUsb__CUsbInterfaceSetting, "71194af7-77c2-54d5-a116-287f0b7fd53f")

.comdef __FIVectorView_1_Windows__CDevices__CUsb__CUsbInterfaceSetting : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CDevices__CUsb__CUsbInterruptInEndpointDescriptor_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CDevices__CUsb__CUsbInterruptInEndpointDescriptor_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CDevices__CUsb__CUsbInterruptInEndpointDescriptor, "3fc7f890-218e-5057-904d-6387c591cc93")

.comdef __FIVectorView_1_Windows__CDevices__CUsb__CUsbInterruptInEndpointDescriptor : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CDevices__CUsb__CUsbInterruptInPipe_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CDevices__CUsb__CUsbInterruptInPipe_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CDevices__CUsb__CUsbInterruptInPipe, "37469574-b4c5-5ba0-9616-894dd822ff5b")

.comdef __FIVectorView_1_Windows__CDevices__CUsb__CUsbInterruptInPipe : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CDevices__CUsb__CUsbInterruptOutEndpointDescriptor_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CDevices__CUsb__CUsbInterruptOutEndpointDescriptor_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CDevices__CUsb__CUsbInterruptOutEndpointDescriptor, "984e7e15-c5ac-5140-a3c0-b583190085d7")

.comdef __FIVectorView_1_Windows__CDevices__CUsb__CUsbInterruptOutEndpointDescriptor : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CDevices__CUsb__CUsbInterruptOutPipe_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CDevices__CUsb__CUsbInterruptOutPipe_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CDevices__CUsb__CUsbInterruptOutPipe, "748196c8-83bf-5ec3-8d28-a3112b3ee3cc")

.comdef __FIVectorView_1_Windows__CDevices__CUsb__CUsbInterruptOutPipe : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CDevices__CUsb__CUsbDevice_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CDevices__CUsb__CUsbDevice_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CDevices__CUsb__CUsbDevice, "7331254f-6caf-587d-9c2a-018c66d312db")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CDevices__CUsb__CUsbDevice : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CDevices__CUsb__CUsbDevice_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CDevices__CUsb__CUsbDevice_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CDevices__CUsb__CUsbDevice, "2138c5ed-b71a-5166-9948-d55792748f5c")

.comdef __FIAsyncOperation_1_Windows__CDevices__CUsb__CUsbDevice : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CDevices__CUsb__CUsbInterruptInPipe_Windows__CDevices__CUsb__CUsbInterruptInEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CDevices__CUsb__CUsbInterruptInPipe_Windows__CDevices__CUsb__CUsbInterruptInEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CDevices__CUsb__CUsbInterruptInPipe_Windows__CDevices__CUsb__CUsbInterruptInEventArgs, "e6db9449-f36a-50f2-926c-2afd85c49f01")

.comdef __FITypedEventHandler_2_Windows__CDevices__CUsb__CUsbInterruptInPipe_Windows__CDevices__CUsb__CUsbInterruptInEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

.namespace Windows
.namespace Devices
.namespace Usb

.enum UsbTransferDirection {
    UsbTransferDirection_Out	= 0,
    UsbTransferDirection_In	= 1
    }

.enum UsbEndpointType {
    UsbEndpointType_Control	= 0,
    UsbEndpointType_Isochronous = 1,
    UsbEndpointType_Bulk	= 2,
    UsbEndpointType_Interrupt	= 3
    }

.enum UsbControlRecipient {
    UsbControlRecipient_Device	= 0,
    UsbControlRecipient_SpecifiedInterface	= 1,
    UsbControlRecipient_Endpoint	= 2,
    UsbControlRecipient_Other	= 3,
    UsbControlRecipient_DefaultInterface	= 4
    }

.enum UsbControlTransferType {
    UsbControlTransferType_Standard	= 0,
    UsbControlTransferType_Class	= 1,
    UsbControlTransferType_Vendor	= 2
    }

.enum UsbReadOptions {
    UsbReadOptions_None = 0,
    UsbReadOptions_AutoClearStall	= 0x1,
    UsbReadOptions_OverrideAutomaticBufferManagement	= 0x2,
    UsbReadOptions_IgnoreShortPacket	= 0x4,
    UsbReadOptions_AllowPartialReads	= 0x8
    }

.enum UsbWriteOptions {
    UsbWriteOptions_None	= 0,
    UsbWriteOptions_AutoClearStall	= 0x1,
    UsbWriteOptions_ShortPacketTerminate	= 0x2
    }

ifndef ____x_ABI_CWindows_CDevices_CUsb_CIUsbControlRequestType_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CUsb_CIUsbControlRequestType_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Usb_IUsbControlRequestType <L"Windows.Devices.Usb.IUsbControlRequestType">
DEFINE_IIDX(IUsbControlRequestType, "8E9465A6-D73D-46DE-94BE-AAE7F07C0F5C")

.comdef IUsbControlRequestType : public IInspectable

    get_Direction	proc :ptr
    put_Direction	proc :Windows::Devices::Usb::UsbTransferDirection
    get_ControlTransferType proc :ptr
    put_ControlTransferType proc :Windows::Devices::Usb::UsbControlTransferType
    get_Recipient	proc :ptr
    put_Recipient	proc :Windows::Devices::Usb::UsbControlRecipient
    get_AsByte		proc :ptr
    put_AsByte		proc :BYTE
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CUsb_CIUsbSetupPacketFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CUsb_CIUsbSetupPacketFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Usb_IUsbSetupPacketFactory <L"Windows.Devices.Usb.IUsbSetupPacketFactory">
DEFINE_IIDX(IUsbSetupPacketFactory, "C9257D50-1B2E-4A41-A2A7-338F0CEF3C14")

.comdef IUsbSetupPacketFactory : public IInspectable

    CreateWithEightByteBuffer proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CUsb_CIUsbSetupPacket_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CUsb_CIUsbSetupPacket_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Usb_IUsbSetupPacket <L"Windows.Devices.Usb.IUsbSetupPacket">
DEFINE_IIDX(IUsbSetupPacket, "104BA132-C78F-4C51-B654-E49D02F2CB03")

.comdef IUsbSetupPacket : public IInspectable

    get_RequestType	proc :ptr
    put_RequestType	proc :ptr
    get_Request		proc :ptr
    put_Request		proc :BYTE
    get_Value		proc :ptr
    put_Value		proc :UINT32
    get_Index		proc :ptr
    put_Index		proc :UINT32
    get_Length		proc :ptr
    put_Length		proc :UINT32
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CUsb_CIUsbDeviceClass_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CUsb_CIUsbDeviceClass_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Usb_IUsbDeviceClass <L"Windows.Devices.Usb.IUsbDeviceClass">
DEFINE_IIDX(IUsbDeviceClass, "051942F9-845E-47EB-B12A-38F2F617AFE7")

.comdef IUsbDeviceClass : public IInspectable

    get_ClassCode	proc :ptr
    put_ClassCode	proc :BYTE
    get_SubclassCode	proc :ptr
    put_SubclassCode	proc :ptr
    get_ProtocolCode	proc :ptr
    put_ProtocolCode	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CUsb_CIUsbDeviceClassesStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CUsb_CIUsbDeviceClassesStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Usb_IUsbDeviceClassesStatics <L"Windows.Devices.Usb.IUsbDeviceClassesStatics">
DEFINE_IIDX(IUsbDeviceClassesStatics, "B20B0527-C580-4599-A165-981B4FD03230")

.comdef IUsbDeviceClassesStatics : public IInspectable

    get_CdcControl	proc :ptr
    get_Physical	proc :ptr
    get_PersonalHealthcare proc :ptr
    get_ActiveSync	proc :ptr
    get_PalmSync	proc :ptr
    get_DeviceFirmwareUpdate proc :ptr
    get_Irda		proc :ptr
    get_Measurement	proc :ptr
    get_VendorSpecific	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CUsb_CIUsbDeviceClasses_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CUsb_CIUsbDeviceClasses_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Usb_IUsbDeviceClasses <L"Windows.Devices.Usb.IUsbDeviceClasses">
DEFINE_IIDX(IUsbDeviceClasses, "686F955D-9B92-4B30-9781-C22C55AC35CB")

.comdef IUsbDeviceClasses : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CUsb_CIUsbDeviceStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CUsb_CIUsbDeviceStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Usb_IUsbDeviceStatics <L"Windows.Devices.Usb.IUsbDeviceStatics">
DEFINE_IIDX(IUsbDeviceStatics, "066B85A2-09B7-4446-8502-6FE6DCAA7309")

.comdef IUsbDeviceStatics : public IInspectable

    GetDeviceSelector	proc :UINT32, :UINT32, :GUID, :ptr
    GetDeviceSelectorGuidOnly proc :GUID, :ptr
    GetDeviceSelectorVidPidOnly proc :UINT32, :UINT32, :ptr
    GetDeviceClassSelector proc :ptr, :ptr
    FromIdAsync		proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CUsb_CIUsbDeviceDescriptor_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CUsb_CIUsbDeviceDescriptor_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Usb_IUsbDeviceDescriptor <L"Windows.Devices.Usb.IUsbDeviceDescriptor">
DEFINE_IIDX(IUsbDeviceDescriptor, "1F48D1F6-BA97-4322-B92C-B5B189216588")

.comdef IUsbDeviceDescriptor : public IInspectable

    get_BcdUsb		proc :ptr
    get_MaxPacketSize0	proc :ptr
    get_VendorId	proc :ptr
    get_ProductId	proc :ptr
    get_BcdDeviceRevision proc :ptr
    get_NumberOfConfigurations proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CUsb_CIUsbConfigurationDescriptor_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CUsb_CIUsbConfigurationDescriptor_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Usb_IUsbConfigurationDescriptor <L"Windows.Devices.Usb.IUsbConfigurationDescriptor">
DEFINE_IIDX(IUsbConfigurationDescriptor, "F2176D92-B442-407A-8207-7D646C0385F3")

.comdef IUsbConfigurationDescriptor : public IInspectable

    get_ConfigurationValue proc :ptr
    get_MaxPowerMilliamps proc :ptr
    get_SelfPowered	proc :ptr
    get_RemoteWakeup	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CUsb_CIUsbConfigurationDescriptorStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CUsb_CIUsbConfigurationDescriptorStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Usb_IUsbConfigurationDescriptorStatics <L"Windows.Devices.Usb.IUsbConfigurationDescriptorStatics">
DEFINE_IIDX(IUsbConfigurationDescriptorStatics, "424CED93-E740-40A1-92BD-DA120EA04914")

.comdef IUsbConfigurationDescriptorStatics : public IInspectable

    TryParse		proc :ptr, :ptr, :ptr
    Parse		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CUsb_CIUsbInterfaceDescriptor_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CUsb_CIUsbInterfaceDescriptor_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Usb_IUsbInterfaceDescriptor <L"Windows.Devices.Usb.IUsbInterfaceDescriptor">
DEFINE_IIDX(IUsbInterfaceDescriptor, "199670C7-B7EE-4F90-8CD5-94A2E257598A")

.comdef IUsbInterfaceDescriptor : public IInspectable

    get_ClassCode	proc :ptr
    get_SubclassCode	proc :ptr
    get_ProtocolCode	proc :ptr
    get_AlternateSettingNumber proc :ptr
    get_InterfaceNumber proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CUsb_CIUsbInterfaceDescriptorStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CUsb_CIUsbInterfaceDescriptorStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Usb_IUsbInterfaceDescriptorStatics <L"Windows.Devices.Usb.IUsbInterfaceDescriptorStatics">
DEFINE_IIDX(IUsbInterfaceDescriptorStatics, "E34A9FF5-77D6-48B6-B0BE-16C6422316FE")

.comdef IUsbInterfaceDescriptorStatics : public IInspectable

    TryParse		proc :ptr, :ptr, :ptr
    Parse		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CUsb_CIUsbEndpointDescriptor_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CUsb_CIUsbEndpointDescriptor_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Usb_IUsbEndpointDescriptor <L"Windows.Devices.Usb.IUsbEndpointDescriptor">
DEFINE_IIDX(IUsbEndpointDescriptor, "6B4862D9-8DF7-4B40-AC83-578F139F0575")

.comdef IUsbEndpointDescriptor : public IInspectable

    get_EndpointNumber	proc :ptr
    get_Direction	proc :ptr
    get_EndpointType	proc :ptr
    get_AsBulkInEndpointDescriptor proc :ptr
    get_AsInterruptInEndpointDescriptor proc :ptr
    get_AsBulkOutEndpointDescriptor proc :ptr
    get_AsInterruptOutEndpointDescriptor proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CUsb_CIUsbEndpointDescriptorStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CUsb_CIUsbEndpointDescriptorStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Usb_IUsbEndpointDescriptorStatics <L"Windows.Devices.Usb.IUsbEndpointDescriptorStatics">
DEFINE_IIDX(IUsbEndpointDescriptorStatics, "C890B201-9A6A-495E-A82C-295B9E708106")

.comdef IUsbEndpointDescriptorStatics : public IInspectable

    TryParse		proc :ptr, :ptr, :ptr
    Parse		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CUsb_CIUsbDescriptor_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CUsb_CIUsbDescriptor_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Usb_IUsbDescriptor <L"Windows.Devices.Usb.IUsbDescriptor">
DEFINE_IIDX(IUsbDescriptor, "0A89F216-5F9D-4874-8904-DA9AD3F5528F")

.comdef IUsbDescriptor : public IInspectable

    get_Length		proc :ptr
    get_DescriptorType	proc :ptr
    ReadDescriptorBuffer proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CUsb_CIUsbInterruptInEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CUsb_CIUsbInterruptInEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Usb_IUsbInterruptInEventArgs <L"Windows.Devices.Usb.IUsbInterruptInEventArgs">
DEFINE_IIDX(IUsbInterruptInEventArgs, "B7B04092-1418-4936-8209-299CF5605583")

.comdef IUsbInterruptInEventArgs : public IInspectable

    get_InterruptData	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CUsb_CIUsbBulkInPipe_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CUsb_CIUsbBulkInPipe_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Usb_IUsbBulkInPipe <L"Windows.Devices.Usb.IUsbBulkInPipe">
DEFINE_IIDX(IUsbBulkInPipe, "F01D2D3B-4548-4D50-B326-D82CDABE1220")

.comdef IUsbBulkInPipe : public IInspectable

    get_MaxTransferSizeBytes proc :ptr
    get_EndpointDescriptor proc :ptr
    ClearStallAsync	proc :ptr
    put_ReadOptions	proc :Windows::Devices::Usb::UsbReadOptions
    get_ReadOptions	proc :ptr
    FlushBuffer		proc
    get_InputStream	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CUsb_CIUsbInterruptInPipe_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CUsb_CIUsbInterruptInPipe_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Usb_IUsbInterruptInPipe <L"Windows.Devices.Usb.IUsbInterruptInPipe">
DEFINE_IIDX(IUsbInterruptInPipe, "FA007116-84D7-48C7-8A3F-4C0B235F2EA6")

.comdef IUsbInterruptInPipe : public IInspectable

    get_EndpointDescriptor proc :ptr
    ClearStallAsync	proc :ptr
    add_DataReceived	proc :ptr, :ptr
    remove_DataReceived proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CUsb_CIUsbBulkOutPipe_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CUsb_CIUsbBulkOutPipe_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Usb_IUsbBulkOutPipe <L"Windows.Devices.Usb.IUsbBulkOutPipe">
DEFINE_IIDX(IUsbBulkOutPipe, "A8E9EE6E-0115-45AA-8B21-37B225BCCEE7")

.comdef IUsbBulkOutPipe : public IInspectable

    get_EndpointDescriptor proc :ptr
    ClearStallAsync	proc :ptr
    put_WriteOptions	proc :Windows::Devices::Usb::UsbWriteOptions
    get_WriteOptions	proc :ptr
    get_OutputStream	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CUsb_CIUsbInterruptOutPipe_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CUsb_CIUsbInterruptOutPipe_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Usb_IUsbInterruptOutPipe <L"Windows.Devices.Usb.IUsbInterruptOutPipe">
DEFINE_IIDX(IUsbInterruptOutPipe, "E984C8A9-AAF9-49D0-B96C-F661AB4A7F95")

.comdef IUsbInterruptOutPipe : public IInspectable

    get_EndpointDescriptor proc :ptr
    ClearStallAsync	proc :ptr
    put_WriteOptions	proc :Windows::Devices::Usb::UsbWriteOptions
    get_WriteOptions	proc :ptr
    get_OutputStream	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CUsb_CIUsbConfiguration_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CUsb_CIUsbConfiguration_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Usb_IUsbConfiguration <L"Windows.Devices.Usb.IUsbConfiguration">
DEFINE_IIDX(IUsbConfiguration, "68177429-36A9-46D7-B873-FC689251EC30")

.comdef IUsbConfiguration : public IInspectable

    get_UsbInterfaces	proc :ptr
    get_ConfigurationDescriptor proc :ptr
    get_Descriptors	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CUsb_CIUsbInterface_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CUsb_CIUsbInterface_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Usb_IUsbInterface <L"Windows.Devices.Usb.IUsbInterface">
DEFINE_IIDX(IUsbInterface, "A0322B95-7F47-48AB-A727-678C25BE2112")

.comdef IUsbInterface : public IInspectable

    get_BulkInPipes	proc :ptr
    get_InterruptInPipes proc :ptr
    get_BulkOutPipes	proc :ptr
    get_InterruptOutPipes proc :ptr
    get_InterfaceSettings proc :ptr
    get_InterfaceNumber proc :ptr
    get_Descriptors	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CUsb_CIUsbInterfaceSetting_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CUsb_CIUsbInterfaceSetting_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Usb_IUsbInterfaceSetting <L"Windows.Devices.Usb.IUsbInterfaceSetting">
DEFINE_IIDX(IUsbInterfaceSetting, "1827BBA7-8DA7-4AF7-8F4C-7F3032E781F5")

.comdef IUsbInterfaceSetting : public IInspectable

    get_BulkInEndpoints proc :ptr
    get_InterruptInEndpoints proc :ptr
    get_BulkOutEndpoints proc :ptr
    get_InterruptOutEndpoints proc :ptr
    get_Selected	proc :ptr
    SelectSettingAsync	proc :ptr
    get_InterfaceDescriptor proc :ptr
    get_Descriptors	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CUsb_CIUsbBulkInEndpointDescriptor_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CUsb_CIUsbBulkInEndpointDescriptor_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Usb_IUsbBulkInEndpointDescriptor <L"Windows.Devices.Usb.IUsbBulkInEndpointDescriptor">
DEFINE_IIDX(IUsbBulkInEndpointDescriptor, "3C6E4846-06CF-42A9-9DC2-971C1B14B6E3")

.comdef IUsbBulkInEndpointDescriptor : public IInspectable

    get_MaxPacketSize	proc :ptr
    get_EndpointNumber	proc :ptr
    get_Pipe		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CUsb_CIUsbInterruptInEndpointDescriptor_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CUsb_CIUsbInterruptInEndpointDescriptor_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Usb_IUsbInterruptInEndpointDescriptor <L"Windows.Devices.Usb.IUsbInterruptInEndpointDescriptor">
DEFINE_IIDX(IUsbInterruptInEndpointDescriptor, "C0528967-C911-4C3A-86B2-419C2DA89039")

.comdef IUsbInterruptInEndpointDescriptor : public IInspectable

    get_MaxPacketSize	proc :ptr
    get_EndpointNumber	proc :ptr
    get_Interval	proc :ptr
    get_Pipe		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CUsb_CIUsbBulkOutEndpointDescriptor_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CUsb_CIUsbBulkOutEndpointDescriptor_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Usb_IUsbBulkOutEndpointDescriptor <L"Windows.Devices.Usb.IUsbBulkOutEndpointDescriptor">
DEFINE_IIDX(IUsbBulkOutEndpointDescriptor, "2820847A-FFEE-4F60-9BE1-956CAC3ECB65")

.comdef IUsbBulkOutEndpointDescriptor : public IInspectable

    get_MaxPacketSize	proc :ptr
    get_EndpointNumber	proc :ptr
    get_Pipe		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CUsb_CIUsbInterruptOutEndpointDescriptor_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CUsb_CIUsbInterruptOutEndpointDescriptor_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Usb_IUsbInterruptOutEndpointDescriptor <L"Windows.Devices.Usb.IUsbInterruptOutEndpointDescriptor">
DEFINE_IIDX(IUsbInterruptOutEndpointDescriptor, "CC9FED81-10CA-4533-952D-9E278341E80F")

.comdef IUsbInterruptOutEndpointDescriptor : public IInspectable

    get_MaxPacketSize	proc :ptr
    get_EndpointNumber	proc :ptr
    get_Interval	proc :ptr
    get_Pipe		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CUsb_CIUsbDevice_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CUsb_CIUsbDevice_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Usb_IUsbDevice <L"Windows.Devices.Usb.IUsbDevice">
DEFINE_IIDX(IUsbDevice, "5249B992-C456-44D5-AD5E-24F5A089F63B")

.comdef IUsbDevice : public IInspectable

    SendControlOutTransferAsync proc :ptr, :ptr, :ptr
    SendControlOutTransferAsyncNoBuffer proc :ptr, :ptr
    SendControlInTransferAsync proc :ptr, :ptr, :ptr
    SendControlInTransferAsyncNoBuffer proc :ptr, :ptr
    get_DefaultInterface proc :ptr
    get_DeviceDescriptor proc :ptr
    get_Configuration	proc :ptr
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_Devices_Usb_UsbControlRequestType_DEFINED
define RUNTIMECLASS_Windows_Devices_Usb_UsbControlRequestType_DEFINED
define RuntimeClass_Windows_Devices_Usb_UsbControlRequestType <L"Windows.Devices.Usb.UsbControlRequestType">
endif
ifndef RUNTIMECLASS_Windows_Devices_Usb_UsbSetupPacket_DEFINED
define RUNTIMECLASS_Windows_Devices_Usb_UsbSetupPacket_DEFINED
define RuntimeClass_Windows_Devices_Usb_UsbSetupPacket <L"Windows.Devices.Usb.UsbSetupPacket">
endif
ifndef RUNTIMECLASS_Windows_Devices_Usb_UsbDeviceClass_DEFINED
define RUNTIMECLASS_Windows_Devices_Usb_UsbDeviceClass_DEFINED
define RuntimeClass_Windows_Devices_Usb_UsbDeviceClass <L"Windows.Devices.Usb.UsbDeviceClass">
endif
ifndef RUNTIMECLASS_Windows_Devices_Usb_UsbDeviceClasses_DEFINED
define RUNTIMECLASS_Windows_Devices_Usb_UsbDeviceClasses_DEFINED
define RuntimeClass_Windows_Devices_Usb_UsbDeviceClasses <L"Windows.Devices.Usb.UsbDeviceClasses">
endif
ifndef RUNTIMECLASS_Windows_Devices_Usb_UsbDevice_DEFINED
define RUNTIMECLASS_Windows_Devices_Usb_UsbDevice_DEFINED
define RuntimeClass_Windows_Devices_Usb_UsbDevice <L"Windows.Devices.Usb.UsbDevice">
endif
ifndef RUNTIMECLASS_Windows_Devices_Usb_UsbInterface_DEFINED
define RUNTIMECLASS_Windows_Devices_Usb_UsbInterface_DEFINED
define RuntimeClass_Windows_Devices_Usb_UsbInterface <L"Windows.Devices.Usb.UsbInterface">
endif
ifndef RUNTIMECLASS_Windows_Devices_Usb_UsbDeviceDescriptor_DEFINED
define RUNTIMECLASS_Windows_Devices_Usb_UsbDeviceDescriptor_DEFINED
define RuntimeClass_Windows_Devices_Usb_UsbDeviceDescriptor <L"Windows.Devices.Usb.UsbDeviceDescriptor">
endif
ifndef RUNTIMECLASS_Windows_Devices_Usb_UsbConfiguration_DEFINED
define RUNTIMECLASS_Windows_Devices_Usb_UsbConfiguration_DEFINED
define RuntimeClass_Windows_Devices_Usb_UsbConfiguration <L"Windows.Devices.Usb.UsbConfiguration">
endif
ifndef RUNTIMECLASS_Windows_Devices_Usb_UsbDescriptor_DEFINED
define RUNTIMECLASS_Windows_Devices_Usb_UsbDescriptor_DEFINED
define RuntimeClass_Windows_Devices_Usb_UsbDescriptor <L"Windows.Devices.Usb.UsbDescriptor">
endif
ifndef RUNTIMECLASS_Windows_Devices_Usb_UsbConfigurationDescriptor_DEFINED
define RUNTIMECLASS_Windows_Devices_Usb_UsbConfigurationDescriptor_DEFINED
define RuntimeClass_Windows_Devices_Usb_UsbConfigurationDescriptor <L"Windows.Devices.Usb.UsbConfigurationDescriptor">
endif
ifndef RUNTIMECLASS_Windows_Devices_Usb_UsbInterfaceDescriptor_DEFINED
define RUNTIMECLASS_Windows_Devices_Usb_UsbInterfaceDescriptor_DEFINED
define RuntimeClass_Windows_Devices_Usb_UsbInterfaceDescriptor <L"Windows.Devices.Usb.UsbInterfaceDescriptor">
endif
ifndef RUNTIMECLASS_Windows_Devices_Usb_UsbBulkInEndpointDescriptor_DEFINED
define RUNTIMECLASS_Windows_Devices_Usb_UsbBulkInEndpointDescriptor_DEFINED
define RuntimeClass_Windows_Devices_Usb_UsbBulkInEndpointDescriptor <L"Windows.Devices.Usb.UsbBulkInEndpointDescriptor">
endif
ifndef RUNTIMECLASS_Windows_Devices_Usb_UsbInterruptInEndpointDescriptor_DEFINED
define RUNTIMECLASS_Windows_Devices_Usb_UsbInterruptInEndpointDescriptor_DEFINED
define RuntimeClass_Windows_Devices_Usb_UsbInterruptInEndpointDescriptor <L"Windows.Devices.Usb.UsbInterruptInEndpointDescriptor">
endif
ifndef RUNTIMECLASS_Windows_Devices_Usb_UsbBulkOutEndpointDescriptor_DEFINED
define RUNTIMECLASS_Windows_Devices_Usb_UsbBulkOutEndpointDescriptor_DEFINED
define RuntimeClass_Windows_Devices_Usb_UsbBulkOutEndpointDescriptor <L"Windows.Devices.Usb.UsbBulkOutEndpointDescriptor">
endif
ifndef RUNTIMECLASS_Windows_Devices_Usb_UsbInterruptOutEndpointDescriptor_DEFINED
define RUNTIMECLASS_Windows_Devices_Usb_UsbInterruptOutEndpointDescriptor_DEFINED
define RuntimeClass_Windows_Devices_Usb_UsbInterruptOutEndpointDescriptor <L"Windows.Devices.Usb.UsbInterruptOutEndpointDescriptor">
endif
ifndef RUNTIMECLASS_Windows_Devices_Usb_UsbEndpointDescriptor_DEFINED
define RUNTIMECLASS_Windows_Devices_Usb_UsbEndpointDescriptor_DEFINED
define RuntimeClass_Windows_Devices_Usb_UsbEndpointDescriptor <L"Windows.Devices.Usb.UsbEndpointDescriptor">
endif
ifndef RUNTIMECLASS_Windows_Devices_Usb_UsbInterruptInEventArgs_DEFINED
define RUNTIMECLASS_Windows_Devices_Usb_UsbInterruptInEventArgs_DEFINED
define RuntimeClass_Windows_Devices_Usb_UsbInterruptInEventArgs <L"Windows.Devices.Usb.UsbInterruptInEventArgs">
endif
ifndef RUNTIMECLASS_Windows_Devices_Usb_UsbInterruptInPipe_DEFINED
define RUNTIMECLASS_Windows_Devices_Usb_UsbInterruptInPipe_DEFINED
define RuntimeClass_Windows_Devices_Usb_UsbInterruptInPipe <L"Windows.Devices.Usb.UsbInterruptInPipe">
endif
ifndef RUNTIMECLASS_Windows_Devices_Usb_UsbBulkInPipe_DEFINED
define RUNTIMECLASS_Windows_Devices_Usb_UsbBulkInPipe_DEFINED
define RuntimeClass_Windows_Devices_Usb_UsbBulkInPipe <L"Windows.Devices.Usb.UsbBulkInPipe">
endif
ifndef RUNTIMECLASS_Windows_Devices_Usb_UsbBulkOutPipe_DEFINED
define RUNTIMECLASS_Windows_Devices_Usb_UsbBulkOutPipe_DEFINED
define RuntimeClass_Windows_Devices_Usb_UsbBulkOutPipe <L"Windows.Devices.Usb.UsbBulkOutPipe">
endif
ifndef RUNTIMECLASS_Windows_Devices_Usb_UsbInterruptOutPipe_DEFINED
define RUNTIMECLASS_Windows_Devices_Usb_UsbInterruptOutPipe_DEFINED
define RuntimeClass_Windows_Devices_Usb_UsbInterruptOutPipe <L"Windows.Devices.Usb.UsbInterruptOutPipe">
endif
ifndef RUNTIMECLASS_Windows_Devices_Usb_UsbInterfaceSetting_DEFINED
define RUNTIMECLASS_Windows_Devices_Usb_UsbInterfaceSetting_DEFINED
define RuntimeClass_Windows_Devices_Usb_UsbInterfaceSetting <L"Windows.Devices.Usb.UsbInterfaceSetting">
endif

endif
