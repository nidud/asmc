ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Eui2Examl2Einput_h__
define __windows2Eui2Examl2Einput_h__
ifndef __windows2Efoundation_h__
include Windows.Foundation.inc
endif
include Windows.Devices.Input.inc
include Windows.System.inc

.namespace Windows
.namespace UI
.namespace Xaml
.namespace Input

.enum FocusNavigationDirection {
    FocusNavigationDirection_Next = 0,
    FocusNavigationDirection_Previous	= 1
    }

.enum InputScopeNameValue {
    InputScopeNameValue_Default = 0,
    InputScopeNameValue_Url	= 1,
    InputScopeNameValue_EmailSmtpAddress	= 5,
    InputScopeNameValue_CurrencyAmountAndSymbol = 20,
    InputScopeNameValue_Number	= 29,
    InputScopeNameValue_TelephoneNumber = 32,
    InputScopeNameValue_NumberFullWidth = 39,
    InputScopeNameValue_AlphanumericHalfWidth	= 40,
    InputScopeNameValue_AlphanumericFullWidth	= 41,
    InputScopeNameValue_Hiragana	= 44,
    InputScopeNameValue_KatakanaHalfWidth	= 45,
    InputScopeNameValue_KatakanaFullWidth	= 46,
    InputScopeNameValue_Hanja	= 47,
    InputScopeNameValue_HangulHalfWidth = 48,
    InputScopeNameValue_HangulFullWidth = 49,
    InputScopeNameValue_Search	= 50,
    InputScopeNameValue_Formula = 51,
    InputScopeNameValue_SearchIncremental	= 52,
    InputScopeNameValue_ChineseHalfWidth	= 53,
    InputScopeNameValue_ChineseFullWidth	= 54,
    InputScopeNameValue_NativeScript	= 55,
    InputScopeNameValue_Chat	= 58,
    InputScopeNameValue_NameOrPhoneNumber	= 59
    }

.enum KeyboardNavigationMode {
    KeyboardNavigationMode_Local	= 0,
    KeyboardNavigationMode_Cycle	= 1,
    KeyboardNavigationMode_Once = 2
    }

.enum ManipulationModes {
    ManipulationModes_None	= 0,
    ManipulationModes_TranslateX	= 0x1,
    ManipulationModes_TranslateY	= 0x2,
    ManipulationModes_TranslateRailsX	= 0x4,
    ManipulationModes_TranslateRailsY	= 0x8,
    ManipulationModes_Rotate	= 0x10,
    ManipulationModes_Scale	= 0x20,
    ManipulationModes_TranslateInertia	= 0x40,
    ManipulationModes_RotateInertia	= 0x80,
    ManipulationModes_ScaleInertia	= 0x100,
    ManipulationModes_All	= 0xffff,
    ManipulationModes_System	= 0x10000
    }

.endn
.endn
.endn
.endn

include Windows.UI.Xaml.inc
include windows.foundation.collections.inc

ifndef ____FIIterator_1_Windows__CUI__CXaml__CInput__CInputScopeName_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CUI__CXaml__CInput__CInputScopeName_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CUI__CXaml__CInput__CInputScopeName, "7ac16ff4-5857-5001-b87f-327093f68392")

.comdef __FIIterator_1_Windows__CUI__CXaml__CInput__CInputScopeName : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CUI__CXaml__CInput__CInputScopeName_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CUI__CXaml__CInput__CInputScopeName_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CUI__CXaml__CInput__CInputScopeName, "81416296-95d0-5100-b59b-bea1c27d2002")

.comdef __FIIterable_1_Windows__CUI__CXaml__CInput__CInputScopeName : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CUI__CXaml__CInput__CPointer_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CUI__CXaml__CInput__CPointer_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CUI__CXaml__CInput__CPointer, "8cb1347d-8888-5fb3-bffd-e6caf61b4f03")

.comdef __FIIterator_1_Windows__CUI__CXaml__CInput__CPointer : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CUI__CXaml__CInput__CPointer_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CUI__CXaml__CInput__CPointer_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CUI__CXaml__CInput__CPointer, "6cf9f859-2234-510d-860a-db328030cbcc")

.comdef __FIIterable_1_Windows__CUI__CXaml__CInput__CPointer : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CUI__CXaml__CInput__CInputScopeName_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CUI__CXaml__CInput__CInputScopeName_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CUI__CXaml__CInput__CInputScopeName, "fcd65a82-5328-53bc-a884-c209aafabf78")

.comdef __FIVectorView_1_Windows__CUI__CXaml__CInput__CInputScopeName : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CUI__CXaml__CInput__CPointer_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CUI__CXaml__CInput__CPointer_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CUI__CXaml__CInput__CPointer, "6250f79f-7668-51e9-86a3-3821217a6631")

.comdef __FIVectorView_1_Windows__CUI__CXaml__CInput__CPointer : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVector_1_Windows__CUI__CXaml__CInput__CInputScopeName_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CUI__CXaml__CInput__CInputScopeName_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CUI__CXaml__CInput__CInputScopeName, "703fe123-d766-562f-b210-1980bb2a0d33")

.comdef __FIVector_1_Windows__CUI__CXaml__CInput__CInputScopeName : public IInspectable

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
.namespace UI
.namespace Xaml
.namespace Input

ifndef ____x_ABI_CWindows_CUI_CXaml_CInput_CIDoubleTappedEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CInput_CIDoubleTappedEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IDoubleTappedEventHandler, "3124D025-04A7-4D45-825E-8204A624DBF4")

.comdef IDoubleTappedEventHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CInput_CIHoldingEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CInput_CIHoldingEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IHoldingEventHandler, "ECAE8CCD-8E5E-4FBE-9846-30A6370AFCDF")

.comdef IHoldingEventHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CInput_CIKeyEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CInput_CIKeyEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IKeyEventHandler, "7C63D2E5-7A0E-4E12-B96A-7715AA6FF1C8")

.comdef IKeyEventHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CInput_CIManipulationCompletedEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CInput_CIManipulationCompletedEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IManipulationCompletedEventHandler, "38EF4B0F-14F8-42DF-9A1E-A4BCC4AF77F4")

.comdef IManipulationCompletedEventHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CInput_CIManipulationDeltaEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CInput_CIManipulationDeltaEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IManipulationDeltaEventHandler, "AA1160CB-DFB9-4C56-ABDC-711B63C8EB94")

.comdef IManipulationDeltaEventHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CInput_CIManipulationInertiaStartingEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CInput_CIManipulationInertiaStartingEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IManipulationInertiaStartingEventHandler, "D39D6322-7C9C-481B-827B-C8B2D9BB6FC7")

.comdef IManipulationInertiaStartingEventHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CInput_CIManipulationStartedEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CInput_CIManipulationStartedEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IManipulationStartedEventHandler, "F88345F8-E0A3-4BE2-B90C-DC20E6D8BEB0")

.comdef IManipulationStartedEventHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CInput_CIManipulationStartingEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CInput_CIManipulationStartingEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IManipulationStartingEventHandler, "10D0B04E-BFE4-42CB-823C-3FECD8770EF8")

.comdef IManipulationStartingEventHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CInput_CIPointerEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CInput_CIPointerEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IPointerEventHandler, "E4385929-C004-4BCF-8970-359486E39F88")

.comdef IPointerEventHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CInput_CIRightTappedEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CInput_CIRightTappedEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IRightTappedEventHandler, "2532A062-F447-4950-9C46-F1E34A2C2238")

.comdef IRightTappedEventHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CInput_CITappedEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CInput_CITappedEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(ITappedEventHandler, "68D940CC-9FF0-49CE-B141-3F07EC477B97")

.comdef ITappedEventHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CInput_CIDoubleTappedRoutedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CInput_CIDoubleTappedRoutedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Input_IDoubleTappedRoutedEventArgs <L"Windows.UI.Xaml.Input.IDoubleTappedRoutedEventArgs">
DEFINE_IIDX(IDoubleTappedRoutedEventArgs, "AF404424-26DF-44F4-8714-9359249B62D3")

.comdef IDoubleTappedRoutedEventArgs : public IInspectable

    get_PointerDeviceType proc :ptr
    get_Handled		proc :ptr
    put_Handled		proc :boolean
    GetPosition		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CInput_CIFocusManager_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CInput_CIFocusManager_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Input_IFocusManager <L"Windows.UI.Xaml.Input.IFocusManager">
DEFINE_IIDX(Input_CIFocusManager, "C843F50B-3B83-4DA1-9D6F-557C1169F341")

.comdef IFocusManager : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CInput_CIFocusManagerStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CInput_CIFocusManagerStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Input_IFocusManagerStatics <L"Windows.UI.Xaml.Input.IFocusManagerStatics">
DEFINE_IIDX(IFocusManagerStatics, "1ECCD326-8182-4482-826A-0918E9ED9AF7")

.comdef IFocusManagerStatics : public IInspectable

    GetFocusedElement	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CInput_CIFocusManagerStatics2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CInput_CIFocusManagerStatics2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Input_IFocusManagerStatics2 <L"Windows.UI.Xaml.Input.IFocusManagerStatics2">
DEFINE_IIDX(IFocusManagerStatics2, "A920D761-DD87-4F31-BEDA-EF417FE7C04A")

.comdef IFocusManagerStatics2 : public IInspectable

    TryMoveFocus	proc :Windows::UI::Xaml::Input::FocusNavigationDirection, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CInput_CIHoldingRoutedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CInput_CIHoldingRoutedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Input_IHoldingRoutedEventArgs <L"Windows.UI.Xaml.Input.IHoldingRoutedEventArgs">
DEFINE_IIDX(IHoldingRoutedEventArgs, "C246FF23-D80D-44DE-8DB9-0D815E269AC0")

.comdef IHoldingRoutedEventArgs : public IInspectable

    get_PointerDeviceType proc :ptr
    get_HoldingState	proc :ptr
    get_Handled		proc :ptr
    put_Handled		proc :boolean
    GetPosition		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CInput_CICommand_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CInput_CICommand_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Input_ICommand <L"Windows.UI.Xaml.Input.ICommand">
DEFINE_IIDX(ICommand, "E5AF3542-CA67-4081-995B-709DD13792DF")

.comdef ICommand : public IInspectable

    add_CanExecuteChanged proc :ptr, :ptr
    remove_CanExecuteChanged proc :EventRegistrationToken
    CanExecute		proc :ptr, :ptr
    Execute		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CInput_CIInertiaExpansionBehavior_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CInput_CIInertiaExpansionBehavior_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Input_IInertiaExpansionBehavior <L"Windows.UI.Xaml.Input.IInertiaExpansionBehavior">
DEFINE_IIDX(IInertiaExpansionBehavior, "751D87E5-8D42-44C5-965E-3CD30CC9D6F7")

.comdef IInertiaExpansionBehavior : public IInspectable

    get_DesiredDeceleration proc :ptr
    put_DesiredDeceleration proc :DOUBLE
    get_DesiredExpansion proc :ptr
    put_DesiredExpansion proc :DOUBLE
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CInput_CIInertiaRotationBehavior_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CInput_CIInertiaRotationBehavior_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Input_IInertiaRotationBehavior <L"Windows.UI.Xaml.Input.IInertiaRotationBehavior">
DEFINE_IIDX(IInertiaRotationBehavior, "424CFB2E-BBFD-4625-AE78-20C65BF1EFAF")

.comdef IInertiaRotationBehavior : public IInspectable

    get_DesiredDeceleration proc :ptr
    put_DesiredDeceleration proc :DOUBLE
    get_DesiredRotation proc :ptr
    put_DesiredRotation proc :DOUBLE
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CInput_CIInertiaTranslationBehavior_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CInput_CIInertiaTranslationBehavior_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Input_IInertiaTranslationBehavior <L"Windows.UI.Xaml.Input.IInertiaTranslationBehavior">
DEFINE_IIDX(IInertiaTranslationBehavior, "45D3A512-3B32-4882-A4C2-ECFA2D4B6DF0")

.comdef IInertiaTranslationBehavior : public IInspectable

    get_DesiredDeceleration proc :ptr
    put_DesiredDeceleration proc :DOUBLE
    get_DesiredDisplacement proc :ptr
    put_DesiredDisplacement proc :DOUBLE
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CInput_CIInputScope_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CInput_CIInputScope_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Input_IInputScope <L"Windows.UI.Xaml.Input.IInputScope">
DEFINE_IIDX(IInputScope, "5C0F85F3-F9D8-4220-B666-045D074D9BFA")

.comdef IInputScope : public IInspectable

    get_Names		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CInput_CIInputScopeName_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CInput_CIInputScopeName_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Input_IInputScopeName <L"Windows.UI.Xaml.Input.IInputScopeName">
DEFINE_IIDX(IInputScopeName, "FD3E6997-08FB-4CBA-A021-792D7589FD5A")

.comdef IInputScopeName : public IInspectable

    get_NameValue	proc :ptr
    put_NameValue	proc :Windows::UI::Xaml::Input::InputScopeNameValue
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CInput_CIInputScopeNameFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CInput_CIInputScopeNameFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Input_IInputScopeNameFactory <L"Windows.UI.Xaml.Input.IInputScopeNameFactory">
DEFINE_IIDX(IInputScopeNameFactory, "4A40BB52-4BD7-4E54-8617-1CDA8A1EDA7F")

.comdef IInputScopeNameFactory : public IInspectable

    CreateInstance	proc :Windows::UI::Xaml::Input::InputScopeNameValue, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CInput_CIKeyRoutedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CInput_CIKeyRoutedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Input_IKeyRoutedEventArgs <L"Windows.UI.Xaml.Input.IKeyRoutedEventArgs">
DEFINE_IIDX(IKeyRoutedEventArgs, "D4CD3DFE-4079-42E9-A39A-3095D3F049C6")

.comdef IKeyRoutedEventArgs : public IInspectable

    get_Key		proc :ptr
    get_KeyStatus	proc :ptr
    get_Handled		proc :ptr
    put_Handled		proc :boolean
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CInput_CIManipulationCompletedRoutedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CInput_CIManipulationCompletedRoutedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Input_IManipulationCompletedRoutedEventArgs <L"Windows.UI.Xaml.Input.IManipulationCompletedRoutedEventArgs">
DEFINE_IIDX(IManipulationCompletedRoutedEventArgs, "B5AD9B23-2F41-498E-8319-015EE8A75346")

.comdef IManipulationCompletedRoutedEventArgs : public IInspectable

    get_Container	proc :ptr
    get_Position	proc :ptr
    get_IsInertial	proc :ptr
    get_Cumulative	proc :ptr
    get_Velocities	proc :ptr
    get_Handled		proc :ptr
    put_Handled		proc :boolean
    get_PointerDeviceType proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CInput_CIManipulationDeltaRoutedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CInput_CIManipulationDeltaRoutedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Input_IManipulationDeltaRoutedEventArgs <L"Windows.UI.Xaml.Input.IManipulationDeltaRoutedEventArgs">
DEFINE_IIDX(IManipulationDeltaRoutedEventArgs, "400D5794-4C6F-491D-82D6-3517109399C6")

.comdef IManipulationDeltaRoutedEventArgs : public IInspectable

    get_Container	proc :ptr
    get_Position	proc :ptr
    get_IsInertial	proc :ptr
    get_Delta		proc :ptr
    get_Cumulative	proc :ptr
    get_Velocities	proc :ptr
    get_Handled		proc :ptr
    put_Handled		proc :boolean
    get_PointerDeviceType proc :ptr
    Complete		proc
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CInput_CIManipulationInertiaStartingRoutedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CInput_CIManipulationInertiaStartingRoutedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Input_IManipulationInertiaStartingRoutedEventArgs <L"Windows.UI.Xaml.Input.IManipulationInertiaStartingRoutedEventArgs">
DEFINE_IIDX(IManipulationInertiaStartingRoutedEventArgs, "246A91A9-CA43-4C0B-ACEF-81E8B8147520")

.comdef IManipulationInertiaStartingRoutedEventArgs : public IInspectable

    get_Container	proc :ptr
    get_ExpansionBehavior proc :ptr
    put_ExpansionBehavior proc :ptr
    get_RotationBehavior proc :ptr
    put_RotationBehavior proc :ptr
    get_TranslationBehavior proc :ptr
    put_TranslationBehavior proc :ptr
    get_Handled		proc :ptr
    put_Handled		proc :boolean
    get_PointerDeviceType proc :ptr
    get_Delta		proc :ptr
    get_Cumulative	proc :ptr
    get_Velocities	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CInput_CIManipulationPivot_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CInput_CIManipulationPivot_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Input_IManipulationPivot <L"Windows.UI.Xaml.Input.IManipulationPivot">
DEFINE_IIDX(IManipulationPivot, "2E3838A5-E6C2-4998-82AC-18748B141666")

.comdef IManipulationPivot : public IInspectable

    get_Center		proc :ptr
    put_Center		proc :Windows::Foundation::Point
    get_Radius		proc :ptr
    put_Radius		proc :DOUBLE
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CInput_CIManipulationPivotFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CInput_CIManipulationPivotFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Input_IManipulationPivotFactory <L"Windows.UI.Xaml.Input.IManipulationPivotFactory">
DEFINE_IIDX(IManipulationPivotFactory, "6D05B039-3702-4396-AD9B-A825EFA63A3B")

.comdef IManipulationPivotFactory : public IInspectable

    CreateInstanceWithCenterAndRadius proc :Windows::Foundation::Point, :DOUBLE, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Input_IManipulationStartedRoutedEventArgs <L"Windows.UI.Xaml.Input.IManipulationStartedRoutedEventArgs">
DEFINE_IIDX(IManipulationStartedRoutedEventArgs, "5DB1AA05-9F80-48B6-AE6C-4F119DE8FF13")

.comdef IManipulationStartedRoutedEventArgs : public IInspectable

    get_Container	proc :ptr
    get_Position	proc :ptr
    get_Handled		proc :ptr
    put_Handled		proc :boolean
    get_PointerDeviceType proc :ptr
    get_Cumulative	proc :ptr
    Complete		proc
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgsFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CInput_CIManipulationStartedRoutedEventArgsFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Input_IManipulationStartedRoutedEventArgsFactory <L"Windows.UI.Xaml.Input.IManipulationStartedRoutedEventArgsFactory">
DEFINE_IIDX(IManipulationStartedRoutedEventArgsFactory, "84C1DAA7-7272-4463-B6C3-A40B9BA151FC")

.comdef IManipulationStartedRoutedEventArgsFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CInput_CIManipulationStartingRoutedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CInput_CIManipulationStartingRoutedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Input_IManipulationStartingRoutedEventArgs <L"Windows.UI.Xaml.Input.IManipulationStartingRoutedEventArgs">
DEFINE_IIDX(IManipulationStartingRoutedEventArgs, "18D636B7-53A4-4C15-A498-F3A9CA212A42")

.comdef IManipulationStartingRoutedEventArgs : public IInspectable

    get_Mode		proc :ptr
    put_Mode		proc :Windows::UI::Xaml::Input::ManipulationModes
    get_Container	proc :ptr
    put_Container	proc :ptr
    get_Pivot		proc :ptr
    put_Pivot		proc :ptr
    get_Handled		proc :ptr
    put_Handled		proc :boolean
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CInput_CIPointer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CInput_CIPointer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Input_IPointer <L"Windows.UI.Xaml.Input.IPointer">
DEFINE_IIDX(IPointer, "5EE8F39F-747D-4171-90E6-CD37A9DFFB11")

.comdef IPointer : public IInspectable

    get_PointerId	proc :ptr
    get_PointerDeviceType proc :ptr
    get_IsInContact	proc :ptr
    get_IsInRange	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CInput_CIPointerRoutedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CInput_CIPointerRoutedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Input_IPointerRoutedEventArgs <L"Windows.UI.Xaml.Input.IPointerRoutedEventArgs">
DEFINE_IIDX(IPointerRoutedEventArgs, "DA628F0A-9752-49E2-BDE2-49ECCAB9194D")

.comdef IPointerRoutedEventArgs : public IInspectable

    get_Pointer		proc :ptr
    get_KeyModifiers	proc :ptr
    get_Handled		proc :ptr
    put_Handled		proc :boolean
    GetCurrentPoint	proc :ptr, :ptr
    GetIntermediatePoints proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CInput_CIRightTappedRoutedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CInput_CIRightTappedRoutedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Input_IRightTappedRoutedEventArgs <L"Windows.UI.Xaml.Input.IRightTappedRoutedEventArgs">
DEFINE_IIDX(IRightTappedRoutedEventArgs, "6834869D-7BD5-4033-B237-172F79ABE393")

.comdef IRightTappedRoutedEventArgs : public IInspectable

    get_PointerDeviceType proc :ptr
    get_Handled		proc :ptr
    put_Handled		proc :boolean
    GetPosition		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CInput_CITappedRoutedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CInput_CITappedRoutedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Input_ITappedRoutedEventArgs <L"Windows.UI.Xaml.Input.ITappedRoutedEventArgs">
DEFINE_IIDX(ITappedRoutedEventArgs, "A099E6BE-E624-459A-BB1D-E05C73E2CC66")

.comdef ITappedRoutedEventArgs : public IInspectable

    get_PointerDeviceType proc :ptr
    get_Handled		proc :ptr
    put_Handled		proc :boolean
    GetPosition		proc :ptr, :ptr
   .ends

endif

.endn
.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_UI_Xaml_Input_Pointer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Input_Pointer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Input_Pointer <L"Windows.UI.Xaml.Input.Pointer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Input_DoubleTappedRoutedEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Input_DoubleTappedRoutedEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_Input_DoubleTappedRoutedEventArgs <L"Windows.UI.Xaml.Input.DoubleTappedRoutedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Input_FocusManager_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Input_FocusManager_DEFINED
define RuntimeClass_Windows_UI_Xaml_Input_FocusManager <L"Windows.UI.Xaml.Input.FocusManager">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Input_HoldingRoutedEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Input_HoldingRoutedEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_Input_HoldingRoutedEventArgs <L"Windows.UI.Xaml.Input.HoldingRoutedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Input_InertiaExpansionBehavior_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Input_InertiaExpansionBehavior_DEFINED
define RuntimeClass_Windows_UI_Xaml_Input_InertiaExpansionBehavior <L"Windows.UI.Xaml.Input.InertiaExpansionBehavior">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Input_InertiaRotationBehavior_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Input_InertiaRotationBehavior_DEFINED
define RuntimeClass_Windows_UI_Xaml_Input_InertiaRotationBehavior <L"Windows.UI.Xaml.Input.InertiaRotationBehavior">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Input_InertiaTranslationBehavior_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Input_InertiaTranslationBehavior_DEFINED
define RuntimeClass_Windows_UI_Xaml_Input_InertiaTranslationBehavior <L"Windows.UI.Xaml.Input.InertiaTranslationBehavior">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Input_InputScope_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Input_InputScope_DEFINED
define RuntimeClass_Windows_UI_Xaml_Input_InputScope <L"Windows.UI.Xaml.Input.InputScope">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Input_InputScopeName_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Input_InputScopeName_DEFINED
define RuntimeClass_Windows_UI_Xaml_Input_InputScopeName <L"Windows.UI.Xaml.Input.InputScopeName">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Input_KeyRoutedEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Input_KeyRoutedEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_Input_KeyRoutedEventArgs <L"Windows.UI.Xaml.Input.KeyRoutedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Input_ManipulationCompletedRoutedEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Input_ManipulationCompletedRoutedEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_Input_ManipulationCompletedRoutedEventArgs <L"Windows.UI.Xaml.Input.ManipulationCompletedRoutedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Input_ManipulationDeltaRoutedEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Input_ManipulationDeltaRoutedEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_Input_ManipulationDeltaRoutedEventArgs <L"Windows.UI.Xaml.Input.ManipulationDeltaRoutedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Input_ManipulationInertiaStartingRoutedEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Input_ManipulationInertiaStartingRoutedEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_Input_ManipulationInertiaStartingRoutedEventArgs <L"Windows.UI.Xaml.Input.ManipulationInertiaStartingRoutedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Input_ManipulationPivot_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Input_ManipulationPivot_DEFINED
define RuntimeClass_Windows_UI_Xaml_Input_ManipulationPivot <L"Windows.UI.Xaml.Input.ManipulationPivot">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Input_ManipulationStartedRoutedEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Input_ManipulationStartedRoutedEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_Input_ManipulationStartedRoutedEventArgs <L"Windows.UI.Xaml.Input.ManipulationStartedRoutedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Input_ManipulationStartingRoutedEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Input_ManipulationStartingRoutedEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_Input_ManipulationStartingRoutedEventArgs <L"Windows.UI.Xaml.Input.ManipulationStartingRoutedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Input_PointerRoutedEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Input_PointerRoutedEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_Input_PointerRoutedEventArgs <L"Windows.UI.Xaml.Input.PointerRoutedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Input_RightTappedRoutedEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Input_RightTappedRoutedEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_Input_RightTappedRoutedEventArgs <L"Windows.UI.Xaml.Input.RightTappedRoutedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Input_TappedRoutedEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Input_TappedRoutedEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_Input_TappedRoutedEventArgs <L"Windows.UI.Xaml.Input.TappedRoutedEventArgs">
endif

endif
