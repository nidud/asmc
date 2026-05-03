ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Edevices2Eenumeration_h__
define __windows2Edevices2Eenumeration_h__
ifndef __windows2Efoundation_h__
include Windows.Foundation.inc
endif
include Windows.Storage.Streams.inc

ifndef ____FIIterator_1_Windows__CDevices__CEnumeration__CDeviceInformation_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CDevices__CEnumeration__CDeviceInformation_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CDevices__CEnumeration__CDeviceInformation, "6f85d843-e8ab-5b46-85d7-327c58d18712")

.comdef __FIIterator_1_Windows__CDevices__CEnumeration__CDeviceInformation : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CDevices__CEnumeration__CDeviceInformation_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CDevices__CEnumeration__CDeviceInformation_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CDevices__CEnumeration__CDeviceInformation, "dd9f8a5d-ec98-5f4b-a3ea-9c8b5ad53c4b")

.comdef __FIIterable_1_Windows__CDevices__CEnumeration__CDeviceInformation : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CDevices__CEnumeration__CDeviceInformation_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CDevices__CEnumeration__CDeviceInformation_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CDevices__CEnumeration__CDeviceInformation, "e170688f-3495-5bf6-aab5-9cac17e0f10f")

.comdef __FIVectorView_1_Windows__CDevices__CEnumeration__CDeviceInformation : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CDevices__CEnumeration__CDeviceInformation_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CDevices__CEnumeration__CDeviceInformation_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CDevices__CEnumeration__CDeviceInformation, "bb483df2-7bb6-5923-a28d-8342ec30046b")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CDevices__CEnumeration__CDeviceInformation : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CDevices__CEnumeration__CDeviceInformation_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CDevices__CEnumeration__CDeviceInformation_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CDevices__CEnumeration__CDeviceInformation, "07faa053-eb2f-5cba-b25b-d9d57be6715f")

.comdef __FIAsyncOperation_1_Windows__CDevices__CEnumeration__CDeviceInformation : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CDevices__CEnumeration__CDeviceInformationCollection_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CDevices__CEnumeration__CDeviceInformationCollection_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CDevices__CEnumeration__CDeviceInformationCollection, "4a458732-527e-5c73-9a68-a73da370f782")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CDevices__CEnumeration__CDeviceInformationCollection : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CDevices__CEnumeration__CDeviceInformationCollection_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CDevices__CEnumeration__CDeviceInformationCollection_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CDevices__CEnumeration__CDeviceInformationCollection, "45180254-082e-5274-b2e7-ac0517f44d07")

.comdef __FIAsyncOperation_1_Windows__CDevices__CEnumeration__CDeviceInformationCollection : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CDevices__CEnumeration__CDeviceThumbnail_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CDevices__CEnumeration__CDeviceThumbnail_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CDevices__CEnumeration__CDeviceThumbnail, "86d455b2-d795-554c-9c31-bf6539349c19")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CDevices__CEnumeration__CDeviceThumbnail : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CDevices__CEnumeration__CDeviceThumbnail_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CDevices__CEnumeration__CDeviceThumbnail_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CDevices__CEnumeration__CDeviceThumbnail, "bac083a3-3a19-5072-9d90-133323a049ba")

.comdef __FIAsyncOperation_1_Windows__CDevices__CEnumeration__CDeviceThumbnail : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CDevices__CEnumeration__CDeviceAccessInformation_Windows__CDevices__CEnumeration__CDeviceAccessChangedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CDevices__CEnumeration__CDeviceAccessInformation_Windows__CDevices__CEnumeration__CDeviceAccessChangedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CDevices__CEnumeration__CDeviceAccessInformation_Windows__CDevices__CEnumeration__CDeviceAccessChangedEventArgs, "4c71d028-b793-5bce-ae59-fa77f45a40d8")

.comdef __FITypedEventHandler_2_Windows__CDevices__CEnumeration__CDeviceAccessInformation_Windows__CDevices__CEnumeration__CDeviceAccessChangedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CDevices__CEnumeration__CDeviceWatcher_IInspectable_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CDevices__CEnumeration__CDeviceWatcher_IInspectable_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CDevices__CEnumeration__CDeviceWatcher_IInspectable, "9234630f-1ff4-54f6-9e3f-ac20369b7725")

.comdef __FITypedEventHandler_2_Windows__CDevices__CEnumeration__CDeviceWatcher_IInspectable : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CDevices__CEnumeration__CDeviceWatcher_Windows__CDevices__CEnumeration__CDeviceInformation_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CDevices__CEnumeration__CDeviceWatcher_Windows__CDevices__CEnumeration__CDeviceInformation_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CDevices__CEnumeration__CDeviceWatcher_Windows__CDevices__CEnumeration__CDeviceInformation, "03c5a07b-990c-5d09-b0b8-5734eaa38222")

.comdef __FITypedEventHandler_2_Windows__CDevices__CEnumeration__CDeviceWatcher_Windows__CDevices__CEnumeration__CDeviceInformation : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CDevices__CEnumeration__CDeviceWatcher_Windows__CDevices__CEnumeration__CDeviceInformationUpdate_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CDevices__CEnumeration__CDeviceWatcher_Windows__CDevices__CEnumeration__CDeviceInformationUpdate_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CDevices__CEnumeration__CDeviceWatcher_Windows__CDevices__CEnumeration__CDeviceInformationUpdate, "906f1254-79ad-54fc-93c4-cdb99b437899")

.comdef __FITypedEventHandler_2_Windows__CDevices__CEnumeration__CDeviceWatcher_Windows__CDevices__CEnumeration__CDeviceInformationUpdate : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

.namespace Windows
.namespace Devices
.namespace Enumeration

.enum DeviceClass {
    DeviceClass_All	= 0,
    DeviceClass_AudioCapture	= 1,
    DeviceClass_AudioRender	= 2,
    DeviceClass_PortableStorageDevice	= 3,
    DeviceClass_VideoCapture	= 4,
    DeviceClass_ImageScanner	= 5,
    DeviceClass_Location	= 6
    }

.enum DeviceWatcherStatus {
    DeviceWatcherStatus_Created = 0,
    DeviceWatcherStatus_Started = 1,
    DeviceWatcherStatus_EnumerationCompleted	= 2,
    DeviceWatcherStatus_Stopping	= 3,
    DeviceWatcherStatus_Stopped = 4,
    DeviceWatcherStatus_Aborted = 5
    }

.enum Panel {
    Panel_Unknown	= 0,
    Panel_Front = 1,
    Panel_Back	= 2,
    Panel_Top	= 3,
    Panel_Bottom	= 4,
    Panel_Left	= 5,
    Panel_Right = 6
    }

.enum DeviceAccessStatus {
    DeviceAccessStatus_Unspecified	= 0,
    DeviceAccessStatus_Allowed	= 1,
    DeviceAccessStatus_DeniedByUser	= 2,
    DeviceAccessStatus_DeniedBySystem	= 3
    }

ifndef ____x_ABI_CWindows_CDevices_CEnumeration_CIEnclosureLocation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CEnumeration_CIEnclosureLocation_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Enumeration_IEnclosureLocation <L"Windows.Devices.Enumeration.IEnclosureLocation">
DEFINE_IIDX(IEnclosureLocation, "42340A27-5810-459C-AABB-C65E1F813ECF")

.comdef IEnclosureLocation : public IInspectable

    get_InDock		proc :ptr
    get_InLid		proc :ptr
    get_Panel		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CEnumeration_CIDeviceInformationUpdate_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CEnumeration_CIDeviceInformationUpdate_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Enumeration_IDeviceInformationUpdate <L"Windows.Devices.Enumeration.IDeviceInformationUpdate">
DEFINE_IIDX(IDeviceInformationUpdate, "8F315305-D972-44B7-A37E-9E822C78213B")

.comdef IDeviceInformationUpdate : public IInspectable

    get_Id		proc :ptr
    get_Properties	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CEnumeration_CIDeviceWatcher_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CEnumeration_CIDeviceWatcher_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Enumeration_IDeviceWatcher <L"Windows.Devices.Enumeration.IDeviceWatcher">
DEFINE_IIDX(IDeviceWatcher, "C9EAB97D-8F6B-4F96-A9F4-ABC814E22271")

.comdef IDeviceWatcher : public IInspectable

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

ifndef ____x_ABI_CWindows_CDevices_CEnumeration_CIDeviceInformationStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CEnumeration_CIDeviceInformationStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Enumeration_IDeviceInformationStatics <L"Windows.Devices.Enumeration.IDeviceInformationStatics">
DEFINE_IIDX(IDeviceInformationStatics, "C17F100E-3A46-4A78-8013-769DC9B97390")

.comdef IDeviceInformationStatics : public IInspectable

    CreateFromIdAsync	proc :HSTRING, :ptr
    CreateFromIdAsyncAdditionalProperties proc :HSTRING, :ptr, :ptr
    FindAllAsync	proc :ptr
    FindAllAsyncDeviceClass proc :Windows::Devices::Enumeration::DeviceClass, :ptr
    FindAllAsyncAqsFilter proc :HSTRING, :ptr
    FindAllAsyncAqsFilterAndAdditionalProperties proc :HSTRING, :ptr, :ptr
    CreateWatcher	proc :ptr
    CreateWatcherDeviceClass proc :Windows::Devices::Enumeration::DeviceClass, :ptr
    CreateWatcherAqsFilter proc :HSTRING, :ptr
    CreateWatcherAqsFilterAndAdditionalProperties proc :HSTRING, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CEnumeration_CIDeviceInformation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CEnumeration_CIDeviceInformation_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Enumeration_IDeviceInformation <L"Windows.Devices.Enumeration.IDeviceInformation">
DEFINE_IIDX(IDeviceInformation, "ABA0FB95-4398-489D-8E44-E6130927011F")

.comdef IDeviceInformation : public IInspectable

    get_Id		proc :ptr
    get_Name		proc :ptr
    get_IsEnabled	proc :ptr
    get_IsDefault	proc :ptr
    get_EnclosureLocation proc :ptr
    get_Properties	proc :ptr
    Update		proc :ptr
    GetThumbnailAsync	proc :ptr
    GetGlyphThumbnailAsync proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CEnumeration_CIDeviceAccessChangedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CEnumeration_CIDeviceAccessChangedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Enumeration_IDeviceAccessChangedEventArgs <L"Windows.Devices.Enumeration.IDeviceAccessChangedEventArgs">
DEFINE_IIDX(IDeviceAccessChangedEventArgs, "DEDA0BCC-4F9D-4F58-9DBA-A9BC800408D5")

.comdef IDeviceAccessChangedEventArgs : public IInspectable

    get_Status		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CEnumeration_CIDeviceAccessInformation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CEnumeration_CIDeviceAccessInformation_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Enumeration_IDeviceAccessInformation <L"Windows.Devices.Enumeration.IDeviceAccessInformation">
DEFINE_IIDX(IDeviceAccessInformation, "0BAA9A73-6DE5-4915-8DDD-9A0554A6F545")

.comdef IDeviceAccessInformation : public IInspectable

    add_AccessChanged	proc :ptr, :ptr
    remove_AccessChanged proc :EventRegistrationToken
    get_CurrentStatus	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CEnumeration_CIDeviceAccessInformationStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CEnumeration_CIDeviceAccessInformationStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Enumeration_IDeviceAccessInformationStatics <L"Windows.Devices.Enumeration.IDeviceAccessInformationStatics">
DEFINE_IIDX(IDeviceAccessInformationStatics, "574BD3D3-5F30-45CD-8A94-724FE5973084")

.comdef IDeviceAccessInformationStatics : public IInspectable

    CreateFromId	proc :HSTRING, :ptr
    CreateFromDeviceClassId proc :GUID, :ptr
    CreateFromDeviceClass proc :Windows::Devices::Enumeration::DeviceClass, :ptr
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_Devices_Enumeration_DeviceThumbnail_DEFINED
define RUNTIMECLASS_Windows_Devices_Enumeration_DeviceThumbnail_DEFINED
define RuntimeClass_Windows_Devices_Enumeration_DeviceThumbnail <L"Windows.Devices.Enumeration.DeviceThumbnail">
endif
ifndef RUNTIMECLASS_Windows_Devices_Enumeration_EnclosureLocation_DEFINED
define RUNTIMECLASS_Windows_Devices_Enumeration_EnclosureLocation_DEFINED
define RuntimeClass_Windows_Devices_Enumeration_EnclosureLocation <L"Windows.Devices.Enumeration.EnclosureLocation">
endif
ifndef RUNTIMECLASS_Windows_Devices_Enumeration_DeviceInformationUpdate_DEFINED
define RUNTIMECLASS_Windows_Devices_Enumeration_DeviceInformationUpdate_DEFINED
define RuntimeClass_Windows_Devices_Enumeration_DeviceInformationUpdate <L"Windows.Devices.Enumeration.DeviceInformationUpdate">
endif
ifndef RUNTIMECLASS_Windows_Devices_Enumeration_DeviceInformationCollection_DEFINED
define RUNTIMECLASS_Windows_Devices_Enumeration_DeviceInformationCollection_DEFINED
define RuntimeClass_Windows_Devices_Enumeration_DeviceInformationCollection <L"Windows.Devices.Enumeration.DeviceInformationCollection">
endif
ifndef RUNTIMECLASS_Windows_Devices_Enumeration_DeviceWatcher_DEFINED
define RUNTIMECLASS_Windows_Devices_Enumeration_DeviceWatcher_DEFINED
define RuntimeClass_Windows_Devices_Enumeration_DeviceWatcher <L"Windows.Devices.Enumeration.DeviceWatcher">
endif
ifndef RUNTIMECLASS_Windows_Devices_Enumeration_DeviceInformation_DEFINED
define RUNTIMECLASS_Windows_Devices_Enumeration_DeviceInformation_DEFINED
define RuntimeClass_Windows_Devices_Enumeration_DeviceInformation <L"Windows.Devices.Enumeration.DeviceInformation">
endif
ifndef RUNTIMECLASS_Windows_Devices_Enumeration_DeviceAccessChangedEventArgs_DEFINED
define RUNTIMECLASS_Windows_Devices_Enumeration_DeviceAccessChangedEventArgs_DEFINED
define RuntimeClass_Windows_Devices_Enumeration_DeviceAccessChangedEventArgs <L"Windows.Devices.Enumeration.DeviceAccessChangedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_Devices_Enumeration_DeviceAccessInformation_DEFINED
define RUNTIMECLASS_Windows_Devices_Enumeration_DeviceAccessInformation_DEFINED
define RuntimeClass_Windows_Devices_Enumeration_DeviceAccessInformation <L"Windows.Devices.Enumeration.DeviceAccessInformation">
endif

endif
