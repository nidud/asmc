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

ifndef __windows2Edevices2Ehumaninterfacedevice_h__
define __windows2Edevices2Ehumaninterfacedevice_h__


include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include Windows.Storage.inc
include windows.foundation.collections.inc

ifndef ____FIIterator_1_Windows__CDevices__CHumanInterfaceDevice__CHidBooleanControl_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CDevices__CHumanInterfaceDevice__CHidBooleanControl_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CDevices__CHumanInterfaceDevice__CHidBooleanControl, "5cde3c23-d054-53d6-abf1-41e73379b472")

.comdef __FIIterator_1_Windows__CDevices__CHumanInterfaceDevice__CHidBooleanControl : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CDevices__CHumanInterfaceDevice__CHidBooleanControl_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CDevices__CHumanInterfaceDevice__CHidBooleanControl_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CDevices__CHumanInterfaceDevice__CHidBooleanControl, "1111e585-5ab0-5d2b-8aed-b6d6186d1c3f")

.comdef __FIIterable_1_Windows__CDevices__CHumanInterfaceDevice__CHidBooleanControl : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CDevices__CHumanInterfaceDevice__CHidBooleanControlDescription_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CDevices__CHumanInterfaceDevice__CHidBooleanControlDescription_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CDevices__CHumanInterfaceDevice__CHidBooleanControlDescription, "203203b0-b7f4-542d-b0d0-9caa1fb55d7f")

.comdef __FIIterator_1_Windows__CDevices__CHumanInterfaceDevice__CHidBooleanControlDescription : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CDevices__CHumanInterfaceDevice__CHidBooleanControlDescription_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CDevices__CHumanInterfaceDevice__CHidBooleanControlDescription_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CDevices__CHumanInterfaceDevice__CHidBooleanControlDescription, "d0ff0fed-a156-58bf-9411-5777df9d57bf")

.comdef __FIIterable_1_Windows__CDevices__CHumanInterfaceDevice__CHidBooleanControlDescription : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CDevices__CHumanInterfaceDevice__CHidCollection_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CDevices__CHumanInterfaceDevice__CHidCollection_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CDevices__CHumanInterfaceDevice__CHidCollection, "cefcee70-c7ff-57c1-a675-a0df8976a988")

.comdef __FIIterator_1_Windows__CDevices__CHumanInterfaceDevice__CHidCollection : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CDevices__CHumanInterfaceDevice__CHidCollection_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CDevices__CHumanInterfaceDevice__CHidCollection_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CDevices__CHumanInterfaceDevice__CHidCollection, "bbeada0f-708f-5b5e-a017-5c64ffb96b69")

.comdef __FIIterable_1_Windows__CDevices__CHumanInterfaceDevice__CHidCollection : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CDevices__CHumanInterfaceDevice__CHidNumericControlDescription_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CDevices__CHumanInterfaceDevice__CHidNumericControlDescription_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CDevices__CHumanInterfaceDevice__CHidNumericControlDescription, "52b9c36e-7d95-5d1c-acab-23c19ea76f01")

.comdef __FIIterator_1_Windows__CDevices__CHumanInterfaceDevice__CHidNumericControlDescription : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CDevices__CHumanInterfaceDevice__CHidNumericControlDescription_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CDevices__CHumanInterfaceDevice__CHidNumericControlDescription_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CDevices__CHumanInterfaceDevice__CHidNumericControlDescription, "868f060d-e0d4-571b-b2f7-431d6984a513")

.comdef __FIIterable_1_Windows__CDevices__CHumanInterfaceDevice__CHidNumericControlDescription : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CDevices__CHumanInterfaceDevice__CHidBooleanControl_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CDevices__CHumanInterfaceDevice__CHidBooleanControl_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CDevices__CHumanInterfaceDevice__CHidBooleanControl, "0e417dac-591a-5de0-afd6-0b2c04c304e7")

.comdef __FIVectorView_1_Windows__CDevices__CHumanInterfaceDevice__CHidBooleanControl : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CDevices__CHumanInterfaceDevice__CHidBooleanControlDescription_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CDevices__CHumanInterfaceDevice__CHidBooleanControlDescription_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CDevices__CHumanInterfaceDevice__CHidBooleanControlDescription, "aab72786-ec34-536f-a7c5-27394753df2c")

.comdef __FIVectorView_1_Windows__CDevices__CHumanInterfaceDevice__CHidBooleanControlDescription : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CDevices__CHumanInterfaceDevice__CHidCollection_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CDevices__CHumanInterfaceDevice__CHidCollection_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CDevices__CHumanInterfaceDevice__CHidCollection, "96f1faac-348f-5b8f-a71d-2d650e0b11f2")

.comdef __FIVectorView_1_Windows__CDevices__CHumanInterfaceDevice__CHidCollection : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CDevices__CHumanInterfaceDevice__CHidNumericControlDescription_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CDevices__CHumanInterfaceDevice__CHidNumericControlDescription_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CDevices__CHumanInterfaceDevice__CHidNumericControlDescription, "e02ca66c-610a-51b4-aef9-3707b697b985")

.comdef __FIVectorView_1_Windows__CDevices__CHumanInterfaceDevice__CHidNumericControlDescription : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CDevices__CHumanInterfaceDevice__CHidDevice_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CDevices__CHumanInterfaceDevice__CHidDevice_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CDevices__CHumanInterfaceDevice__CHidDevice, "b0e8e149-0cb6-55a7-bcc1-d996324d65c4")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CDevices__CHumanInterfaceDevice__CHidDevice : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CDevices__CHumanInterfaceDevice__CHidDevice_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CDevices__CHumanInterfaceDevice__CHidDevice_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CDevices__CHumanInterfaceDevice__CHidDevice, "a76a4fbf-5177-5256-84a8-b31a8dcf1048")

.comdef __FIAsyncOperation_1_Windows__CDevices__CHumanInterfaceDevice__CHidDevice : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CDevices__CHumanInterfaceDevice__CHidFeatureReport_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CDevices__CHumanInterfaceDevice__CHidFeatureReport_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CDevices__CHumanInterfaceDevice__CHidFeatureReport, "db643555-3d16-57fe-b7ef-2bdbd719fdbf")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CDevices__CHumanInterfaceDevice__CHidFeatureReport : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CDevices__CHumanInterfaceDevice__CHidFeatureReport_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CDevices__CHumanInterfaceDevice__CHidFeatureReport_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CDevices__CHumanInterfaceDevice__CHidFeatureReport, "d72fb6f9-42f6-5f45-bfe3-29af247c2e85")

.comdef __FIAsyncOperation_1_Windows__CDevices__CHumanInterfaceDevice__CHidFeatureReport : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CDevices__CHumanInterfaceDevice__CHidInputReport_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CDevices__CHumanInterfaceDevice__CHidInputReport_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CDevices__CHumanInterfaceDevice__CHidInputReport, "01c83770-03ab-5576-98b4-8d75ce1a9885")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CDevices__CHumanInterfaceDevice__CHidInputReport : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CDevices__CHumanInterfaceDevice__CHidInputReport_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CDevices__CHumanInterfaceDevice__CHidInputReport_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CDevices__CHumanInterfaceDevice__CHidInputReport, "b3e28917-cd48-57b3-a0b1-321432e85bd6")

.comdef __FIAsyncOperation_1_Windows__CDevices__CHumanInterfaceDevice__CHidInputReport : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CDevices__CHumanInterfaceDevice__CHidDevice_Windows__CDevices__CHumanInterfaceDevice__CHidInputReportReceivedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CDevices__CHumanInterfaceDevice__CHidDevice_Windows__CDevices__CHumanInterfaceDevice__CHidInputReportReceivedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CDevices__CHumanInterfaceDevice__CHidDevice_Windows__CDevices__CHumanInterfaceDevice__CHidInputReportReceivedEventArgs, "31e757c8-8f6a-540b-938b-aba79b6f03ec")

.comdef __FITypedEventHandler_2_Windows__CDevices__CHumanInterfaceDevice__CHidDevice_Windows__CDevices__CHumanInterfaceDevice__CHidInputReportReceivedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

.namespace Windows
.namespace Devices
.namespace HumanInterfaceDevice

.enum HidReportType {
    HidReportType_Input = 0,
    HidReportType_Output	= 1,
    HidReportType_Feature	= 2
    }

.enum HidCollectionType {
    HidCollectionType_Physical	= 0,
    HidCollectionType_Application	= 1,
    HidCollectionType_Logical	= 2,
    HidCollectionType_Report	= 3,
    HidCollectionType_NamedArray	= 4,
    HidCollectionType_UsageSwitch	= 5,
    HidCollectionType_UsageModifier	= 6,
    HidCollectionType_Other	= 7
    }

ifndef ____x_ABI_CWindows_CDevices_CHumanInterfaceDevice_CIHidDeviceStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CHumanInterfaceDevice_CIHidDeviceStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_HumanInterfaceDevice_IHidDeviceStatics <L"Windows.Devices.HumanInterfaceDevice.IHidDeviceStatics">
DEFINE_IIDX(IHidDeviceStatics, "9E5981E4-9856-418C-9F73-77DE0CD85754")

.comdef IHidDeviceStatics : public IInspectable

    GetDeviceSelector	proc :UINT16, :UINT16, :ptr
    GetDeviceSelectorVidPid proc :UINT16, :UINT16, :UINT16, :UINT16, :ptr
    FromIdAsync		proc :HSTRING, :Windows::Storage::FileAccessMode, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CHumanInterfaceDevice_CIHidBooleanControlDescription_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CHumanInterfaceDevice_CIHidBooleanControlDescription_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_HumanInterfaceDevice_IHidBooleanControlDescription <L"Windows.Devices.HumanInterfaceDevice.IHidBooleanControlDescription">
DEFINE_IIDX(IHidBooleanControlDescription, "6196E543-29D8-4A2A-8683-849E207BBE31")

.comdef IHidBooleanControlDescription : public IInspectable

    get_Id		proc :ptr
    get_ReportId	proc :ptr
    get_ReportType	proc :ptr
    get_UsagePage	proc :ptr
    get_UsageId		proc :ptr
    get_ParentCollections proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CHumanInterfaceDevice_CIHidNumericControlDescription_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CHumanInterfaceDevice_CIHidNumericControlDescription_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_HumanInterfaceDevice_IHidNumericControlDescription <L"Windows.Devices.HumanInterfaceDevice.IHidNumericControlDescription">
DEFINE_IIDX(IHidNumericControlDescription, "638D5E86-1D97-4C75-927F-5FF58BA05E32")

.comdef IHidNumericControlDescription : public IInspectable

    get_Id		proc :ptr
    get_ReportId	proc :ptr
    get_ReportType	proc :ptr
    get_ReportSize	proc :ptr
    get_ReportCount	proc :ptr
    get_UsagePage	proc :ptr
    get_UsageId		proc :ptr
    get_LogicalMinimum	proc :ptr
    get_LogicalMaximum	proc :ptr
    get_PhysicalMinimum proc :ptr
    get_PhysicalMaximum proc :ptr
    get_UnitExponent	proc :ptr
    get_Unit		proc :ptr
    get_IsAbsolute	proc :ptr
    get_HasNull		proc :ptr
    get_ParentCollections proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CHumanInterfaceDevice_CIHidCollection_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CHumanInterfaceDevice_CIHidCollection_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_HumanInterfaceDevice_IHidCollection <L"Windows.Devices.HumanInterfaceDevice.IHidCollection">
DEFINE_IIDX(IHidCollection, "7189F5A3-32F1-46E3-BEFD-44D2663B7E6A")

.comdef IHidCollection : public IInspectable

    get_Id		proc :ptr
    get_Type		proc :ptr
    get_UsagePage	proc :ptr
    get_UsageId		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CHumanInterfaceDevice_CIHidInputReport_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CHumanInterfaceDevice_CIHidInputReport_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_HumanInterfaceDevice_IHidInputReport <L"Windows.Devices.HumanInterfaceDevice.IHidInputReport">
DEFINE_IIDX(IHidInputReport, "C35D0E50-F7E7-4E8D-B23E-CABBE56B90E9")

.comdef IHidInputReport : public IInspectable

    get_Id		proc :ptr
    get_Data		proc :ptr
    get_ActivatedBooleanControls proc :ptr
    get_TransitionedBooleanControls proc :ptr
    GetBooleanControl	proc :UINT16, :UINT16, :ptr
    GetBooleanControlByDescription proc :ptr, :ptr
    GetNumericControl	proc :UINT16, :UINT16, :ptr
    GetNumericControlByDescription proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CHumanInterfaceDevice_CIHidOutputReport_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CHumanInterfaceDevice_CIHidOutputReport_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_HumanInterfaceDevice_IHidOutputReport <L"Windows.Devices.HumanInterfaceDevice.IHidOutputReport">
DEFINE_IIDX(IHidOutputReport, "62CB2544-C896-4463-93C1-DF9DB053C450")

.comdef IHidOutputReport : public IInspectable

    get_Id		proc :ptr
    get_Data		proc :ptr
    put_Data		proc :ptr
    GetBooleanControl	proc :UINT16, :UINT16, :ptr
    GetBooleanControlByDescription proc :ptr, :ptr
    GetNumericControl	proc :UINT16, :UINT16, :ptr
    GetNumericControlByDescription proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CHumanInterfaceDevice_CIHidFeatureReport_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CHumanInterfaceDevice_CIHidFeatureReport_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_HumanInterfaceDevice_IHidFeatureReport <L"Windows.Devices.HumanInterfaceDevice.IHidFeatureReport">
DEFINE_IIDX(IHidFeatureReport, "841D9B79-5AE5-46E3-82EF-1FEC5C8942F4")

.comdef IHidFeatureReport : public IInspectable

    get_Id		proc :ptr
    get_Data		proc :ptr
    put_Data		proc :ptr
    GetBooleanControl	proc :UINT16, :UINT16, :ptr
    GetBooleanControlByDescription proc :ptr, :ptr
    GetNumericControl	proc :UINT16, :UINT16, :ptr
    GetNumericControlByDescription proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CHumanInterfaceDevice_CIHidInputReportReceivedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CHumanInterfaceDevice_CIHidInputReportReceivedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_HumanInterfaceDevice_IHidInputReportReceivedEventArgs <L"Windows.Devices.HumanInterfaceDevice.IHidInputReportReceivedEventArgs">
DEFINE_IIDX(IHidInputReportReceivedEventArgs, "7059C5CB-59B2-4DC2-985C-0ADC6136FA2D")

.comdef IHidInputReportReceivedEventArgs : public IInspectable

    get_Report		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CHumanInterfaceDevice_CIHidBooleanControl_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CHumanInterfaceDevice_CIHidBooleanControl_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_HumanInterfaceDevice_IHidBooleanControl <L"Windows.Devices.HumanInterfaceDevice.IHidBooleanControl">
DEFINE_IIDX(IHidBooleanControl, "524DF48A-3695-408C-BBA2-E2EB5ABFBC20")

.comdef IHidBooleanControl : public IInspectable

    get_Id		proc :ptr
    get_UsagePage	proc :ptr
    get_UsageId		proc :ptr
    get_IsActive	proc :ptr
    put_IsActive	proc :boolean
    get_ControlDescription proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CHumanInterfaceDevice_CIHidNumericControl_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CHumanInterfaceDevice_CIHidNumericControl_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_HumanInterfaceDevice_IHidNumericControl <L"Windows.Devices.HumanInterfaceDevice.IHidNumericControl">
DEFINE_IIDX(IHidNumericControl, "E38A12A5-35A7-4B75-89C8-FB1F28B10823")

.comdef IHidNumericControl : public IInspectable

    get_Id		proc :ptr
    get_IsGrouped	proc :ptr
    get_UsagePage	proc :ptr
    get_UsageId		proc :ptr
    get_Value		proc :ptr
    put_Value		proc :INT64
    get_ScaledValue	proc :ptr
    put_ScaledValue	proc :INT64
    get_ControlDescription proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CHumanInterfaceDevice_CIHidDevice_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CHumanInterfaceDevice_CIHidDevice_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_HumanInterfaceDevice_IHidDevice <L"Windows.Devices.HumanInterfaceDevice.IHidDevice">
DEFINE_IIDX(IHidDevice, "5F8A14E7-2200-432E-95DA-D09B87D574A8")

.comdef IHidDevice : public IInspectable

    get_VendorId	proc :ptr
    get_ProductId	proc :ptr
    get_Version		proc :ptr
    get_UsagePage	proc :ptr
    get_UsageId		proc :ptr
    GetInputReportAsync proc :ptr
    GetInputReportByIdAsync proc :UINT16, :ptr
    GetFeatureReportAsync proc :ptr
    GetFeatureReportByIdAsync proc :UINT16, :ptr
    CreateOutputReport	proc :ptr
    CreateOutputReportById proc :UINT16, :ptr
    CreateFeatureReport proc :ptr
    CreateFeatureReportById proc :UINT16, :ptr
    SendOutputReportAsync proc :ptr, :ptr
    SendFeatureReportAsync proc :ptr, :ptr
    GetBooleanControlDescriptions proc :Windows::Devices::HumanInterfaceDevice::HidReportType, :UINT16, :UINT16, :ptr
    GetNumericControlDescriptions proc :Windows::Devices::HumanInterfaceDevice::HidReportType, :UINT16, :UINT16, :ptr
    add_InputReportReceived proc :ptr, :ptr
    remove_InputReportReceived proc :EventRegistrationToken
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_Devices_HumanInterfaceDevice_HidDevice_DEFINED
define RUNTIMECLASS_Windows_Devices_HumanInterfaceDevice_HidDevice_DEFINED
define RuntimeClass_Windows_Devices_HumanInterfaceDevice_HidDevice <L"Windows.Devices.HumanInterfaceDevice.HidDevice">
endif
ifndef RUNTIMECLASS_Windows_Devices_HumanInterfaceDevice_HidInputReport_DEFINED
define RUNTIMECLASS_Windows_Devices_HumanInterfaceDevice_HidInputReport_DEFINED
define RuntimeClass_Windows_Devices_HumanInterfaceDevice_HidInputReport <L"Windows.Devices.HumanInterfaceDevice.HidInputReport">
endif
ifndef RUNTIMECLASS_Windows_Devices_HumanInterfaceDevice_HidFeatureReport_DEFINED
define RUNTIMECLASS_Windows_Devices_HumanInterfaceDevice_HidFeatureReport_DEFINED
define RuntimeClass_Windows_Devices_HumanInterfaceDevice_HidFeatureReport <L"Windows.Devices.HumanInterfaceDevice.HidFeatureReport">
endif
ifndef RUNTIMECLASS_Windows_Devices_HumanInterfaceDevice_HidOutputReport_DEFINED
define RUNTIMECLASS_Windows_Devices_HumanInterfaceDevice_HidOutputReport_DEFINED
define RuntimeClass_Windows_Devices_HumanInterfaceDevice_HidOutputReport <L"Windows.Devices.HumanInterfaceDevice.HidOutputReport">
endif
ifndef RUNTIMECLASS_Windows_Devices_HumanInterfaceDevice_HidBooleanControlDescription_DEFINED
define RUNTIMECLASS_Windows_Devices_HumanInterfaceDevice_HidBooleanControlDescription_DEFINED
define RuntimeClass_Windows_Devices_HumanInterfaceDevice_HidBooleanControlDescription <L"Windows.Devices.HumanInterfaceDevice.HidBooleanControlDescription">
endif
ifndef RUNTIMECLASS_Windows_Devices_HumanInterfaceDevice_HidNumericControlDescription_DEFINED
define RUNTIMECLASS_Windows_Devices_HumanInterfaceDevice_HidNumericControlDescription_DEFINED
define RuntimeClass_Windows_Devices_HumanInterfaceDevice_HidNumericControlDescription <L"Windows.Devices.HumanInterfaceDevice.HidNumericControlDescription">
endif
ifndef RUNTIMECLASS_Windows_Devices_HumanInterfaceDevice_HidInputReportReceivedEventArgs_DEFINED
define RUNTIMECLASS_Windows_Devices_HumanInterfaceDevice_HidInputReportReceivedEventArgs_DEFINED
define RuntimeClass_Windows_Devices_HumanInterfaceDevice_HidInputReportReceivedEventArgs <L"Windows.Devices.HumanInterfaceDevice.HidInputReportReceivedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_Devices_HumanInterfaceDevice_HidCollection_DEFINED
define RUNTIMECLASS_Windows_Devices_HumanInterfaceDevice_HidCollection_DEFINED
define RuntimeClass_Windows_Devices_HumanInterfaceDevice_HidCollection <L"Windows.Devices.HumanInterfaceDevice.HidCollection">
endif
ifndef RUNTIMECLASS_Windows_Devices_HumanInterfaceDevice_HidBooleanControl_DEFINED
define RUNTIMECLASS_Windows_Devices_HumanInterfaceDevice_HidBooleanControl_DEFINED
define RuntimeClass_Windows_Devices_HumanInterfaceDevice_HidBooleanControl <L"Windows.Devices.HumanInterfaceDevice.HidBooleanControl">
endif
ifndef RUNTIMECLASS_Windows_Devices_HumanInterfaceDevice_HidNumericControl_DEFINED
define RUNTIMECLASS_Windows_Devices_HumanInterfaceDevice_HidNumericControl_DEFINED
define RuntimeClass_Windows_Devices_HumanInterfaceDevice_HidNumericControl <L"Windows.Devices.HumanInterfaceDevice.HidNumericControl">
endif

endif
