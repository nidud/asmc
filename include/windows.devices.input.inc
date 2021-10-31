ifndef __REQUIRED_RPCNDR_H_VERSION__
define __REQUIRED_RPCNDR_H_VERSION__ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
define __REQUIRED_RPCSAL_H_VERSION__ 100
endif

include rpc.inc
include rpcndr.inc

ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr.inc>
endif

ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif

ifndef __windows2Edevices2Einput_h__
define __windows2Edevices2Einput_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include windows.foundation.collections.inc

ifndef ____FIIterator_1_Windows__CDevices__CInput__CPointerDevice_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CDevices__CInput__CPointerDevice_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterator_1_Windows__CDevices__CInput__CPointerDevice, "de94641c-7960-5fcd-abe8-d6ba609ef7d3")

.comdef __FIIterator_1_Windows__CDevices__CInput__CPointerDevice : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :UINT
   .ends

endif

ifndef ____FIIterable_1_Windows__CDevices__CInput__CPointerDevice_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CDevices__CInput__CPointerDevice_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterable_1_Windows__CDevices__CInput__CPointerDevice, "ad26662c-845b-5c6d-aeaa-406f48c21ae9")

.comdef __FIIterable_1_Windows__CDevices__CInput__CPointerDevice : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CDevices__CInput__CPointerDeviceUsage_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CDevices__CInput__CPointerDeviceUsage_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterator_1_Windows__CDevices__CInput__CPointerDeviceUsage, "9ab2160d-11ef-5eca-8dd9-3e13aa4e5f99")

.comdef __FIIterator_1_Windows__CDevices__CInput__CPointerDeviceUsage : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :UINT
   .ends

endif

ifndef ____FIIterable_1_Windows__CDevices__CInput__CPointerDeviceUsage_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CDevices__CInput__CPointerDeviceUsage_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterable_1_Windows__CDevices__CInput__CPointerDeviceUsage, "592d6618-eaab-5a79-a47a-c7fc0b749a4e")

.comdef __FIIterable_1_Windows__CDevices__CInput__CPointerDeviceUsage : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CDevices__CInput__CPointerDevice_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CDevices__CInput__CPointerDevice_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVectorView_1_Windows__CDevices__CInput__CPointerDevice, "cf5674f1-9808-5a2b-80b8-5684ed0ea816")

.comdef __FIVectorView_1_Windows__CDevices__CInput__CPointerDevice : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :UINT
    IndexOf		proc :ptr, :UINT, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :UINT
   .ends

endif

ifndef ____FIVectorView_1_Windows__CDevices__CInput__CPointerDeviceUsage_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CDevices__CInput__CPointerDeviceUsage_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVectorView_1_Windows__CDevices__CInput__CPointerDeviceUsage, "8e5a2c7e-3830-50d5-92ba-3163c89cbbd0")

.comdef __FIVectorView_1_Windows__CDevices__CInput__CPointerDeviceUsage : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :UINT
    IndexOf		proc :ptr, :UINT, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :UINT
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CDevices__CInput__CMouseDevice_Windows__CDevices__CInput__CMouseEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CDevices__CInput__CMouseDevice_Windows__CDevices__CInput__CMouseEventArgs_INTERFACE_DEFINED__

DEFINE_IIDX(__FITypedEventHandler_2_Windows__CDevices__CInput__CMouseDevice_Windows__CDevices__CInput__CMouseEventArgs, "5d72e594-28e4-5895-a34b-ea910f70fdbb")

.comdef __FITypedEventHandler_2_Windows__CDevices__CInput__CMouseDevice_Windows__CDevices__CInput__CMouseEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
    .ends

endif

.namespace Windows
.namespace Devices
.namespace Input

.enum PointerDeviceType {
    PointerDeviceType_Touch,
    PointerDeviceType_Pen,
    PointerDeviceType_Mouse
    }

.template PointerDeviceUsage
    UsagePage		UINT32 ?
    Usage		UINT32 ?
    MinLogical		INT32 ?
    MaxLogical		INT32 ?
    MinPhysical		INT32 ?
    MaxPhysical		INT32 ?
    Unit		UINT32 ?
    PhysicalMultiplier	real4 ?
   .ends

.template MouseDelta
    X			INT32 ?
    Y			INT32 ?
   .ends


ifndef ____x_ABI_CWindows_CDevices_CInput_CIMouseCapabilities_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CInput_CIMouseCapabilities_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Input_IMouseCapabilities <L"Windows.Devices.Input.IMouseCapabilities">

DEFINE_IIDX(IMouseCapabilities, "BCA5E023-7DD9-4B6B-9A92-55D43CB38F73")

.comdef IMouseCapabilities : public IInspectable

    get_MousePresent	proc :ptr
    get_VerticalWheelPresent proc :ptr
    get_HorizontalWheelPresent proc :ptr
    get_SwapButtons	proc :ptr
    get_NumberOfButtons proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CInput_CIKeyboardCapabilities_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CInput_CIKeyboardCapabilities_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Input_IKeyboardCapabilities <L"Windows.Devices.Input.IKeyboardCapabilities">

DEFINE_IIDX(IKeyboardCapabilities, "3A3F9B56-6798-4BBC-833E-0F34B17C65FF")

.comdef IKeyboardCapabilities : public IInspectable

    get_KeyboardPresent proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CInput_CITouchCapabilities_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CInput_CITouchCapabilities_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Input_ITouchCapabilities <L"Windows.Devices.Input.ITouchCapabilities">

DEFINE_IIDX(ITouchCapabilities, "20DD55F9-13F1-46C8-9285-2C05FA3EDA6F")

.comdef ITouchCapabilities : public IInspectable

    get_TouchPresent	proc :ptr
    get_Contacts	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CInput_CIPointerDeviceStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CInput_CIPointerDeviceStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Input_IPointerDeviceStatics <L"Windows.Devices.Input.IPointerDeviceStatics">

DEFINE_IIDX(IPointerDeviceStatics, "D8B89AA1-D1C6-416E-BD8D-5790914DC563")

.comdef IPointerDeviceStatics : public IInspectable

    GetPointerDevice	proc :UINT32, :ptr
    GetPointerDevices	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CInput_CIPointerDevice_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CInput_CIPointerDevice_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Input_IPointerDevice <L"Windows.Devices.Input.IPointerDevice">

DEFINE_IIDX(IPointerDevice, "93C9BAFC-EBCB-467E-82C6-276FEAE36B5A")

.comdef IPointerDevice : public IInspectable

    get_PointerDeviceType proc :ptr
    get_IsIntegrated	proc :ptr
    get_MaxContacts	proc :ptr
    get_PhysicalDeviceRect proc :ptr
    get_ScreenRect	proc :ptr
    get_SupportedUsages proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CInput_CIMouseEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CInput_CIMouseEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Input_IMouseEventArgs <L"Windows.Devices.Input.IMouseEventArgs">

DEFINE_IIDX(IMouseEventArgs, "F625AA5D-2354-4CC7-9230-96941C969FDE")

.comdef IMouseEventArgs : public IInspectable

    get_MouseDelta	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CInput_CIMouseDevice_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CInput_CIMouseDevice_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Input_IMouseDevice <L"Windows.Devices.Input.IMouseDevice">

DEFINE_IIDX(IMouseDevice, "88EDF458-F2C8-49F4-BE1F-C256B388BC11")

.comdef IMouseDevice : public IInspectable

    add_MouseMoved	proc :ptr, :ptr
    remove_MouseMoved	proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CInput_CIMouseDeviceStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CInput_CIMouseDeviceStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Input_IMouseDeviceStatics <L"Windows.Devices.Input.IMouseDeviceStatics">

DEFINE_IIDX(IMouseDeviceStatics, "484A9045-6D70-49DB-8E68-46FFBD17D38D")

.comdef IMouseDeviceStatics : public IInspectable

    GetForCurrentView	proc :ptr
   .ends

endif

.endn
.endn
.endn

define RuntimeClass_Windows_Devices_Input_PointerDevice <L"Windows.Devices.Input.PointerDevice">
define RuntimeClass_Windows_Devices_Input_MouseDevice <L"Windows.Devices.Input.MouseDevice">
define RuntimeClass_Windows_Devices_Input_MouseEventArgs <L"Windows.Devices.Input.MouseEventArgs">
define RuntimeClass_Windows_Devices_Input_MouseCapabilities <L"Windows.Devices.Input.MouseCapabilities">
define RuntimeClass_Windows_Devices_Input_KeyboardCapabilities <L"Windows.Devices.Input.KeyboardCapabilities">
define RuntimeClass_Windows_Devices_Input_TouchCapabilities <L"Windows.Devices.Input.TouchCapabilities">

endif
