ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Eui2Examl2Einterop_h__
define __windows2Eui2Examl2Einterop_h__
ifndef __windows2Efoundation_h__
include Windows.Foundation.inc
endif

.namespace Windows
.namespace UI
.namespace Xaml
.namespace Interop

.enum NotifyCollectionChangedAction {
    NotifyCollectionChangedAction_Add   = 0,
    NotifyCollectionChangedAction_Remove    = 1,
    NotifyCollectionChangedAction_Replace   = 2,
    NotifyCollectionChangedAction_Move  = 3,
    NotifyCollectionChangedAction_Reset = 4
    }

.enum TypeKind {
    TypeKind_Primitive  = 0,
    TypeKind_Metadata   = 1,
    TypeKind_Custom = 2
    }

.template TypeName
    Name            HSTRING ?
    Kind            Windows::UI::Xaml::Interop::TypeKind ?
   .ends

ifndef ____x_ABI_CWindows_CUI_CXaml_CInterop_CINotifyCollectionChangedEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CInterop_CINotifyCollectionChangedEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(INotifyCollectionChangedEventHandler, "CA10B37C-F382-4591-8557-5E24965279B0")

.comdef INotifyCollectionChangedEventHandler : public IUnknown

    _Invoke             proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CInterop_CIBindableVectorChangedEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CInterop_CIBindableVectorChangedEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IBindableVectorChangedEventHandler, "624CD4E1-D007-43B1-9C03-AF4D3E6258C4")

.comdef IBindableVectorChangedEventHandler : public IUnknown

    _Invoke             proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CInterop_CIBindableIterable_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CInterop_CIBindableIterable_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Interop_IBindableIterable <L"Windows.UI.Xaml.Interop.IBindableIterable">
DEFINE_IIDX(IBindableIterable, "036D2C08-DF29-41AF-8AA2-D774BE62BA6F")

.comdef IBindableIterable : public IInspectable

    First               proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CInterop_CIBindableIterator_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CInterop_CIBindableIterator_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Interop_IBindableIterator <L"Windows.UI.Xaml.Interop.IBindableIterator">
DEFINE_IIDX(IBindableIterator, "6A1D6C07-076D-49F2-8314-F52C9C9A8331")

.comdef IBindableIterator : public IInspectable

    get_Current         proc :ptr
    get_HasCurrent      proc :ptr
    MoveNext            proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CInterop_CIBindableVector_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CInterop_CIBindableVector_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Interop_IBindableVector <L"Windows.UI.Xaml.Interop.IBindableVector">
DEFINE_IIDX(IBindableVector, "393DE7DE-6FD0-4C0D-BB71-47244A113E93")

.comdef IBindableVector : public IInspectable

    GetAt               proc :UINT32, :ptr
    get_Size            proc :ptr
    GetView             proc :ptr
    IndexOf             proc :ptr, :ptr, :ptr
    SetAt               proc :UINT32, :ptr
    InsertAt            proc :UINT32, :ptr
    RemoveAt            proc :UINT32
    Append              proc :ptr
    RemoveAtEnd         proc
    Clear               proc
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CInterop_CIBindableVectorView_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CInterop_CIBindableVectorView_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Interop_IBindableVectorView <L"Windows.UI.Xaml.Interop.IBindableVectorView">
DEFINE_IIDX(IBindableVectorView, "346DD6E7-976E-4BC3-815D-ECE243BC0F33")

.comdef IBindableVectorView : public IInspectable

    GetAt               proc :UINT32, :ptr
    get_Size            proc :ptr
    IndexOf             proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CInterop_CINotifyCollectionChanged_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CInterop_CINotifyCollectionChanged_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Interop_INotifyCollectionChanged <L"Windows.UI.Xaml.Interop.INotifyCollectionChanged">
DEFINE_IIDX(INotifyCollectionChanged, "28B167D5-1A31-465B-9B25-D5C3AE686C40")

.comdef INotifyCollectionChanged : public IInspectable

    add_CollectionChanged proc :ptr, :ptr
    remove_CollectionChanged proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CInterop_CINotifyCollectionChangedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CInterop_CINotifyCollectionChangedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Interop_INotifyCollectionChangedEventArgs <L"Windows.UI.Xaml.Interop.INotifyCollectionChangedEventArgs">
DEFINE_IIDX(INotifyCollectionChangedEventArgs, "4CF68D33-E3F2-4964-B85E-945B4F7E2F21")

.comdef INotifyCollectionChangedEventArgs : public IInspectable

    get_Action          proc :ptr
    get_NewItems        proc :ptr
    get_OldItems        proc :ptr
    get_NewStartingIndex proc :ptr
    get_OldStartingIndex proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CInterop_CINotifyCollectionChangedEventArgsFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CInterop_CINotifyCollectionChangedEventArgsFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Interop_INotifyCollectionChangedEventArgsFactory <L"Windows.UI.Xaml.Interop.INotifyCollectionChangedEventArgsFactory">
DEFINE_IIDX(INotifyCollectionChangedEventArgsFactory, "B30C3E3A-DF8D-44A5-9A38-7AC0D08CE63D")

.comdef INotifyCollectionChangedEventArgsFactory : public IInspectable

    CreateInstanceWithAllParameters proc :Windows::UI::Xaml::Interop::NotifyCollectionChangedAction, :ptr, :ptr, :INT32, :INT32, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CInterop_CIBindableObservableVector_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CInterop_CIBindableObservableVector_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Interop_IBindableObservableVector <L"Windows.UI.Xaml.Interop.IBindableObservableVector">
DEFINE_IIDX(IBindableObservableVector, "FE1EB536-7E7F-4F90-AC9A-474984AAE512")

.comdef IBindableObservableVector : public IInspectable

    add_VectorChanged   proc :ptr, :ptr
    remove_VectorChanged proc :EventRegistrationToken
   .ends

endif

.endn
.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_UI_Xaml_Interop_NotifyCollectionChangedEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Interop_NotifyCollectionChangedEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_Interop_NotifyCollectionChangedEventArgs <L"Windows.UI.Xaml.Interop.NotifyCollectionChangedEventArgs">
endif

endif
