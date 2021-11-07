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

ifndef __windows2Edevices2Eenumeration2Epnp_h__
define __windows2Edevices2Eenumeration2Epnp_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include Windows.Devices.Enumeration.inc
include windows.foundation.collections.inc

ifndef ____FIIterator_1_Windows__CDevices__CEnumeration__CPnp__CPnpObject_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CDevices__CEnumeration__CPnp__CPnpObject_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CDevices__CEnumeration__CPnp__CPnpObject, "6bb6d2f1-b5fb-57f0-8251-f20cde5a6871")

.comdef __FIIterator_1_Windows__CDevices__CEnumeration__CPnp__CPnpObject : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CDevices__CEnumeration__CPnp__CPnpObject_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CDevices__CEnumeration__CPnp__CPnpObject_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CDevices__CEnumeration__CPnp__CPnpObject, "30b50092-36ee-53ff-9450-029004436c60")

.comdef __FIIterable_1_Windows__CDevices__CEnumeration__CPnp__CPnpObject : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CDevices__CEnumeration__CPnp__CPnpObject_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CDevices__CEnumeration__CPnp__CPnpObject_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CDevices__CEnumeration__CPnp__CPnpObject, "cce5a798-d269-5fce-99ce-ef0ae3cd0569")

.comdef __FIVectorView_1_Windows__CDevices__CEnumeration__CPnp__CPnpObject : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CDevices__CEnumeration__CPnp__CPnpObject_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CDevices__CEnumeration__CPnp__CPnpObject_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CDevices__CEnumeration__CPnp__CPnpObject, "9d615463-6879-521f-8e97-e66d3ddbc95e")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CDevices__CEnumeration__CPnp__CPnpObject : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CDevices__CEnumeration__CPnp__CPnpObject_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CDevices__CEnumeration__CPnp__CPnpObject_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CDevices__CEnumeration__CPnp__CPnpObject, "22b0fb93-30e6-501a-bd3b-9fa3063e9c16")

.comdef __FIAsyncOperation_1_Windows__CDevices__CEnumeration__CPnp__CPnpObject : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CDevices__CEnumeration__CPnp__CPnpObjectCollection_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CDevices__CEnumeration__CPnp__CPnpObjectCollection_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CDevices__CEnumeration__CPnp__CPnpObjectCollection, "811d834c-a15e-5522-b7f4-e53004fc58ff")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CDevices__CEnumeration__CPnp__CPnpObjectCollection : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CDevices__CEnumeration__CPnp__CPnpObjectCollection_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CDevices__CEnumeration__CPnp__CPnpObjectCollection_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CDevices__CEnumeration__CPnp__CPnpObjectCollection, "f383c2cc-f326-5bbe-95d1-cbc24714ef86")

.comdef __FIAsyncOperation_1_Windows__CDevices__CEnumeration__CPnp__CPnpObjectCollection : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CDevices__CEnumeration__CPnp__CPnpObjectWatcher_IInspectable_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CDevices__CEnumeration__CPnp__CPnpObjectWatcher_IInspectable_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CDevices__CEnumeration__CPnp__CPnpObjectWatcher_IInspectable, "2ee2b4c9-b696-5ecc-b29b-f1e0ef5fe1f7")

.comdef __FITypedEventHandler_2_Windows__CDevices__CEnumeration__CPnp__CPnpObjectWatcher_IInspectable : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CDevices__CEnumeration__CPnp__CPnpObjectWatcher_Windows__CDevices__CEnumeration__CPnp__CPnpObject_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CDevices__CEnumeration__CPnp__CPnpObjectWatcher_Windows__CDevices__CEnumeration__CPnp__CPnpObject_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CDevices__CEnumeration__CPnp__CPnpObjectWatcher_Windows__CDevices__CEnumeration__CPnp__CPnpObject, "d578eed2-58e5-5825-8af2-12f89387b656")

.comdef __FITypedEventHandler_2_Windows__CDevices__CEnumeration__CPnp__CPnpObjectWatcher_Windows__CDevices__CEnumeration__CPnp__CPnpObject : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CDevices__CEnumeration__CPnp__CPnpObjectWatcher_Windows__CDevices__CEnumeration__CPnp__CPnpObjectUpdate_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CDevices__CEnumeration__CPnp__CPnpObjectWatcher_Windows__CDevices__CEnumeration__CPnp__CPnpObjectUpdate_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CDevices__CEnumeration__CPnp__CPnpObjectWatcher_Windows__CDevices__CEnumeration__CPnp__CPnpObjectUpdate, "af8f929d-8058-5c38-a3d8-30aa7a08b588")

.comdef __FITypedEventHandler_2_Windows__CDevices__CEnumeration__CPnp__CPnpObjectWatcher_Windows__CDevices__CEnumeration__CPnp__CPnpObjectUpdate : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

.namespace Windows
.namespace Devices
.namespace Enumeration
.namespace Pnp

.enum PnpObjectType {
    PnpObjectType_Unknown	= 0,
    PnpObjectType_DeviceInterface	= 1,
    PnpObjectType_DeviceContainer	= 2,
    PnpObjectType_Device	= 3,
    PnpObjectType_DeviceInterfaceClass	= 4
    }

ifndef ____x_ABI_CWindows_CDevices_CEnumeration_CPnp_CIPnpObjectUpdate_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CEnumeration_CPnp_CIPnpObjectUpdate_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Enumeration_Pnp_IPnpObjectUpdate <L"Windows.Devices.Enumeration.Pnp.IPnpObjectUpdate">
DEFINE_IIDX(IPnpObjectUpdate, "6F59E812-001E-4844-BCC6-432886856A17")

.comdef IPnpObjectUpdate : public IInspectable

    get_Type		proc :ptr
    get_Id		proc :ptr
    get_Properties	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CEnumeration_CPnp_CIPnpObjectWatcher_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CEnumeration_CPnp_CIPnpObjectWatcher_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Enumeration_Pnp_IPnpObjectWatcher <L"Windows.Devices.Enumeration.Pnp.IPnpObjectWatcher">
DEFINE_IIDX(IPnpObjectWatcher, "83C95CA8-4772-4A7A-ACA8-E48C42A89C44")

.comdef IPnpObjectWatcher : public IInspectable

    add_Added		proc :ptr, :ptr
    remove_Added	proc :EventRegistrationToken
    add_Updated		proc :ptr, :ptr
    remove_Updated	proc :EventRegistrationToken
    add_Removed		proc :ptr, :ptr
    remove_Removed	proc :EventRegistrationToken
    add_EnumerationCompleted proc :ptr, :ptr
    remove_EnumerationCompleted proc :EventRegistrationToken
    add_Stopped		proc :ptr, :ptr
    remove_Stopped	proc :EventRegistrationToken
    get_Status		proc :ptr
    Start		proc
    Stop		proc
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CEnumeration_CPnp_CIPnpObjectStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CEnumeration_CPnp_CIPnpObjectStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Enumeration_Pnp_IPnpObjectStatics <L"Windows.Devices.Enumeration.Pnp.IPnpObjectStatics">
DEFINE_IIDX(IPnpObjectStatics, "B3C32A3D-D168-4660-BBF3-A733B14B6E01")

.comdef IPnpObjectStatics : public IInspectable

    CreateFromIdAsync	proc :Windows::Devices::Enumeration::Pnp::PnpObjectType, :HSTRING, :ptr, :ptr
    FindAllAsync	proc :Windows::Devices::Enumeration::Pnp::PnpObjectType, :ptr, :ptr
    FindAllAsyncAqsFilter proc :Windows::Devices::Enumeration::Pnp::PnpObjectType, :ptr, :HSTRING, :ptr
    CreateWatcher	proc :Windows::Devices::Enumeration::Pnp::PnpObjectType, :ptr, :ptr
    CreateWatcherAqsFilter proc :Windows::Devices::Enumeration::Pnp::PnpObjectType, :ptr, :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CEnumeration_CPnp_CIPnpObject_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CEnumeration_CPnp_CIPnpObject_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Enumeration_Pnp_IPnpObject <L"Windows.Devices.Enumeration.Pnp.IPnpObject">
DEFINE_IIDX(IPnpObject, "95C66258-733B-4A8F-93A3-DB078AC870C1")

.comdef IPnpObject : public IInspectable

    get_Type		proc :ptr
    get_Id		proc :ptr
    get_Properties	proc :ptr
    Update		proc :ptr
   .ends

endif

.endn
.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_Devices_Enumeration_Pnp_PnpObjectUpdate_DEFINED
define RUNTIMECLASS_Windows_Devices_Enumeration_Pnp_PnpObjectUpdate_DEFINED
define RuntimeClass_Windows_Devices_Enumeration_Pnp_PnpObjectUpdate <L"Windows.Devices.Enumeration.Pnp.PnpObjectUpdate">
endif
ifndef RUNTIMECLASS_Windows_Devices_Enumeration_Pnp_PnpObjectCollection_DEFINED
define RUNTIMECLASS_Windows_Devices_Enumeration_Pnp_PnpObjectCollection_DEFINED
define RuntimeClass_Windows_Devices_Enumeration_Pnp_PnpObjectCollection <L"Windows.Devices.Enumeration.Pnp.PnpObjectCollection">
endif
ifndef RUNTIMECLASS_Windows_Devices_Enumeration_Pnp_PnpObjectWatcher_DEFINED
define RUNTIMECLASS_Windows_Devices_Enumeration_Pnp_PnpObjectWatcher_DEFINED
define RuntimeClass_Windows_Devices_Enumeration_Pnp_PnpObjectWatcher <L"Windows.Devices.Enumeration.Pnp.PnpObjectWatcher">
endif
ifndef RUNTIMECLASS_Windows_Devices_Enumeration_Pnp_PnpObject_DEFINED
define RUNTIMECLASS_Windows_Devices_Enumeration_Pnp_PnpObject_DEFINED
define RuntimeClass_Windows_Devices_Enumeration_Pnp_PnpObject <L"Windows.Devices.Enumeration.Pnp.PnpObject">
endif

endif
