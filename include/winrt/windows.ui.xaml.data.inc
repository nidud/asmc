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

ifndef __windows2Eui2Examl2Edata_h__
define __windows2Eui2Examl2Edata_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include Windows.UI.Xaml.inc
include windows.foundation.collections.inc

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CUI__CXaml__CData__CLoadMoreItemsResult_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CUI__CXaml__CData__CLoadMoreItemsResult_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CUI__CXaml__CData__CLoadMoreItemsResult, "10fb738b-a63b-506e-9ed7-2eab37915221")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CUI__CXaml__CData__CLoadMoreItemsResult : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CUI__CXaml__CData__CLoadMoreItemsResult_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CUI__CXaml__CData__CLoadMoreItemsResult_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CUI__CXaml__CData__CLoadMoreItemsResult, "c788089d-37ab-5ba2-b865-5a309acdfc4d")

.comdef __FIAsyncOperation_1_Windows__CUI__CXaml__CData__CLoadMoreItemsResult : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

.namespace Windows
.namespace UI
.namespace Xaml
.namespace Data

.enum BindingMode {
    BindingMode_OneWay	= 1,
    BindingMode_OneTime = 2,
    BindingMode_TwoWay	= 3
    }

.enum RelativeSourceMode {
    RelativeSourceMode_None	= 0,
    RelativeSourceMode_TemplatedParent	= 1,
    RelativeSourceMode_Self	= 2
    }

.enum UpdateSourceTrigger {
    UpdateSourceTrigger_Default = 0,
    UpdateSourceTrigger_PropertyChanged = 1,
    UpdateSourceTrigger_Explicit	= 2
    }

.template LoadMoreItemsResult
    Count		UINT32 ?
   .ends

ifndef ____x_ABI_CWindows_CUI_CXaml_CData_CICurrentChangingEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CData_CICurrentChangingEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(ICurrentChangingEventHandler, "F3888DB8-139F-4DCE-8DC9-F7F1444D1185")

.comdef ICurrentChangingEventHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CData_CIPropertyChangedEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CData_CIPropertyChangedEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IPropertyChangedEventHandler, "50F19C16-0A22-4D8E-A089-1EA9951657D2")

.comdef IPropertyChangedEventHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CData_CIBinding_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CData_CIBinding_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Data_IBinding <L"Windows.UI.Xaml.Data.IBinding">
DEFINE_IIDX(IBinding, "3F7A0C6B-D00F-4730-8C1D-48E16C46F9CA")

.comdef IBinding : public IInspectable

    get_Path		proc :ptr
    put_Path		proc :ptr
    get_Mode		proc :ptr
    put_Mode		proc :Windows::UI::Xaml::Data::BindingMode
    get_Source		proc :ptr
    put_Source		proc :ptr
    get_RelativeSource	proc :ptr
    put_RelativeSource	proc :ptr
    get_ElementName	proc :ptr
    put_ElementName	proc :HSTRING
    get_Converter	proc :ptr
    put_Converter	proc :ptr
    get_ConverterParameter proc :ptr
    put_ConverterParameter proc :ptr
    get_ConverterLanguage proc :ptr
    put_ConverterLanguage proc :HSTRING
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CData_CIValueConverter_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CData_CIValueConverter_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Data_IValueConverter <L"Windows.UI.Xaml.Data.IValueConverter">
DEFINE_IIDX(IValueConverter, "E6F2FEF0-0712-487F-B313-F300B8D79AA1")

.comdef IValueConverter : public IInspectable

    Convert		proc :ptr, :Windows::UI::Xaml::Interop::TypeName, :ptr, :HSTRING, :ptr
    ConvertBack		proc :ptr, :Windows::UI::Xaml::Interop::TypeName, :ptr, :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CData_CIBindingFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CData_CIBindingFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Data_IBindingFactory <L"Windows.UI.Xaml.Data.IBindingFactory">
DEFINE_IIDX(IBindingFactory, "FF42BB08-C39E-4F7E-8434-A1569083883C")

.comdef IBindingFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CData_CIBinding2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CData_CIBinding2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Data_IBinding2 <L"Windows.UI.Xaml.Data.IBinding2">
DEFINE_IIDX(IBinding2, "34F96FCB-0406-48B3-9E82-F333EC4C6910")

.comdef IBinding2 : public IInspectable

    get_FallbackValue	proc :ptr
    put_FallbackValue	proc :ptr
    get_TargetNullValue proc :ptr
    put_TargetNullValue proc :ptr
    get_UpdateSourceTrigger proc :ptr
    put_UpdateSourceTrigger proc :Windows::UI::Xaml::Data::UpdateSourceTrigger
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CData_CIBindingBase_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CData_CIBindingBase_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Data_IBindingBase <L"Windows.UI.Xaml.Data.IBindingBase">
DEFINE_IIDX(IBindingBase, "1589A2AB-3D15-49BC-A447-8A5448E58870")

.comdef IBindingBase : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CData_CIBindingBaseFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CData_CIBindingBaseFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Data_IBindingBaseFactory <L"Windows.UI.Xaml.Data.IBindingBaseFactory">
DEFINE_IIDX(IBindingBaseFactory, "22DAFC3A-7701-4666-A1BA-9859BDCFEC34")

.comdef IBindingBaseFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CData_CIBindingExpression_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CData_CIBindingExpression_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Data_IBindingExpression <L"Windows.UI.Xaml.Data.IBindingExpression">
DEFINE_IIDX(IBindingExpression, "516A19A5-C2FD-4A9E-9FD3-9AA42F995A3C")

.comdef IBindingExpression : public IInspectable

    get_DataItem	proc :ptr
    get_ParentBinding	proc :ptr
    UpdateSource	proc
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CData_CIBindingExpressionFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CData_CIBindingExpressionFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Data_IBindingExpressionFactory <L"Windows.UI.Xaml.Data.IBindingExpressionFactory">
DEFINE_IIDX(IBindingExpressionFactory, "1CB55CD9-DB72-40B3-A2B5-24EE6EA5C328")

.comdef IBindingExpressionFactory : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CData_CIBindingExpressionBase_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CData_CIBindingExpressionBase_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Data_IBindingExpressionBase <L"Windows.UI.Xaml.Data.IBindingExpressionBase">
DEFINE_IIDX(IBindingExpressionBase, "FDED3154-E954-4F67-8FB6-6ED79B3A1CB3")

.comdef IBindingExpressionBase : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CData_CIBindingExpressionBaseFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CData_CIBindingExpressionBaseFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Data_IBindingExpressionBaseFactory <L"Windows.UI.Xaml.Data.IBindingExpressionBaseFactory">
DEFINE_IIDX(IBindingExpressionBaseFactory, "EA7116A7-C2D9-4375-B471-66B9C48C7930")

.comdef IBindingExpressionBaseFactory : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CData_CICollectionViewSource_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CData_CICollectionViewSource_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Data_ICollectionViewSource <L"Windows.UI.Xaml.Data.ICollectionViewSource">
DEFINE_IIDX(ICollectionViewSource, "A66A1146-D2FB-4EAD-BE9F-3578A466DCFE")

.comdef ICollectionViewSource : public IInspectable

    get_Source		proc :ptr
    put_Source		proc :ptr
    get_View		proc :ptr
    get_IsSourceGrouped proc :ptr
    put_IsSourceGrouped proc :boolean
    get_ItemsPath	proc :ptr
    put_ItemsPath	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CData_CICollectionView_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CData_CICollectionView_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Data_ICollectionView <L"Windows.UI.Xaml.Data.ICollectionView">
DEFINE_IIDX(ICollectionView, "8BE8BFE4-DBEF-44DF-8126-A31A89121DDC")

.comdef ICollectionView : public IInspectable

    get_CurrentItem	proc :ptr
    get_CurrentPosition proc :ptr
    get_IsCurrentAfterLast proc :ptr
    get_IsCurrentBeforeFirst proc :ptr
    get_CollectionGroups proc :ptr
    get_HasMoreItems	proc :ptr
    add_CurrentChanged	proc :ptr, :ptr
    remove_CurrentChanged proc :EventRegistrationToken
    add_CurrentChanging proc :ptr, :ptr
    remove_CurrentChanging proc :EventRegistrationToken
    MoveCurrentTo	proc :ptr, :ptr
    MoveCurrentToPosition proc :INT32, :ptr
    MoveCurrentToFirst	proc :ptr
    MoveCurrentToLast	proc :ptr
    MoveCurrentToNext	proc :ptr
    MoveCurrentToPrevious proc :ptr
    LoadMoreItemsAsync	proc :UINT32, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CData_CICollectionViewSourceStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CData_CICollectionViewSourceStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Data_ICollectionViewSourceStatics <L"Windows.UI.Xaml.Data.ICollectionViewSourceStatics">
DEFINE_IIDX(ICollectionViewSourceStatics, "173A0710-46AF-4C0C-818B-21B6EF81BF65")

.comdef ICollectionViewSourceStatics : public IInspectable

    get_SourceProperty	proc :ptr
    get_ViewProperty	proc :ptr
    get_IsSourceGroupedProperty proc :ptr
    get_ItemsPathProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CData_CICurrentChangingEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CData_CICurrentChangingEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Data_ICurrentChangingEventArgs <L"Windows.UI.Xaml.Data.ICurrentChangingEventArgs">
DEFINE_IIDX(ICurrentChangingEventArgs, "F9891E29-51CC-47DD-A5B9-35DC4914AF69")

.comdef ICurrentChangingEventArgs : public IInspectable

    get_Cancel		proc :ptr
    put_Cancel		proc :boolean
    get_IsCancelable	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CData_CICurrentChangingEventArgsFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CData_CICurrentChangingEventArgsFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Data_ICurrentChangingEventArgsFactory <L"Windows.UI.Xaml.Data.ICurrentChangingEventArgsFactory">
DEFINE_IIDX(ICurrentChangingEventArgsFactory, "153BBEEE-62F3-48CF-8183-8BE26DE3A66E")

.comdef ICurrentChangingEventArgsFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
    CreateWithCancelableParameter proc :boolean, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CData_CICollectionViewGroup_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CData_CICollectionViewGroup_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Data_ICollectionViewGroup <L"Windows.UI.Xaml.Data.ICollectionViewGroup">
DEFINE_IIDX(ICollectionViewGroup, "7E01B9D8-D7B5-48B6-B31C-5BB5BDF5F09B")

.comdef ICollectionViewGroup : public IInspectable

    get_Group		proc :ptr
    get_GroupItems	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CData_CICustomProperty_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CData_CICustomProperty_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Data_ICustomProperty <L"Windows.UI.Xaml.Data.ICustomProperty">
DEFINE_IIDX(ICustomProperty, "30DA92C0-23E8-42A0-AE7C-734A0E5D2782")

.comdef ICustomProperty : public IInspectable

    get_Type		proc :ptr
    get_Name		proc :ptr
    GetValue		proc :ptr, :ptr
    SetValue		proc :ptr, :ptr
    GetIndexedValue	proc :ptr, :ptr, :ptr
    SetIndexedValue	proc :ptr, :ptr, :ptr
    get_CanWrite	proc :ptr
    get_CanRead		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CData_CICustomPropertyProvider_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CData_CICustomPropertyProvider_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Data_ICustomPropertyProvider <L"Windows.UI.Xaml.Data.ICustomPropertyProvider">
DEFINE_IIDX(ICustomPropertyProvider, "7C925755-3E48-42B4-8677-76372267033F")

.comdef ICustomPropertyProvider : public IInspectable

    GetCustomProperty	proc :HSTRING, :ptr
    GetIndexedProperty	proc :HSTRING, :Windows::UI::Xaml::Interop::TypeName, :ptr
    GetStringRepresentation proc :ptr
    get_Type		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CData_CINotifyPropertyChanged_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CData_CINotifyPropertyChanged_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Data_INotifyPropertyChanged <L"Windows.UI.Xaml.Data.INotifyPropertyChanged">
DEFINE_IIDX(INotifyPropertyChanged, "CF75D69C-F2F4-486B-B302-BB4C09BAEBFA")

.comdef INotifyPropertyChanged : public IInspectable

    add_PropertyChanged proc :ptr, :ptr
    remove_PropertyChanged proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CData_CIPropertyChangedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CData_CIPropertyChangedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Data_IPropertyChangedEventArgs <L"Windows.UI.Xaml.Data.IPropertyChangedEventArgs">
DEFINE_IIDX(IPropertyChangedEventArgs, "4F33A9A0-5CF4-47A4-B16F-D7FAAF17457E")

.comdef IPropertyChangedEventArgs : public IInspectable

    get_PropertyName	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CData_CIPropertyChangedEventArgsFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CData_CIPropertyChangedEventArgsFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Data_IPropertyChangedEventArgsFactory <L"Windows.UI.Xaml.Data.IPropertyChangedEventArgsFactory">
DEFINE_IIDX(IPropertyChangedEventArgsFactory, "6DCC9C03-E0C7-4EEE-8EA9-37E3406EEB1C")

.comdef IPropertyChangedEventArgsFactory : public IInspectable

    CreateInstance	proc :HSTRING, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CData_CIRelativeSource_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CData_CIRelativeSource_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Data_IRelativeSource <L"Windows.UI.Xaml.Data.IRelativeSource">
DEFINE_IIDX(IRelativeSource, "2397CE84-2822-483A-B499-D0F031E06C6B")

.comdef IRelativeSource : public IInspectable

    get_Mode		proc :ptr
    put_Mode		proc :Windows::UI::Xaml::Data::RelativeSourceMode
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CData_CIRelativeSourceFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CData_CIRelativeSourceFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Data_IRelativeSourceFactory <L"Windows.UI.Xaml.Data.IRelativeSourceFactory">
DEFINE_IIDX(IRelativeSourceFactory, "EF8392CD-446E-4F93-AACB-9B1255577460")

.comdef IRelativeSourceFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CData_CIBindingOperations_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CData_CIBindingOperations_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Data_IBindingOperations <L"Windows.UI.Xaml.Data.IBindingOperations">
DEFINE_IIDX(IBindingOperations, "6FFFD738-9839-419C-A17A-4B3604E1524E")

.comdef IBindingOperations : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CData_CIBindingOperationsStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CData_CIBindingOperationsStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Data_IBindingOperationsStatics <L"Windows.UI.Xaml.Data.IBindingOperationsStatics">
DEFINE_IIDX(IBindingOperationsStatics, "E155EF73-95A0-4AAB-8C7D-2A47DA073C79")

.comdef IBindingOperationsStatics : public IInspectable

    SetBinding		proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CData_CISupportIncrementalLoading_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CData_CISupportIncrementalLoading_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Data_ISupportIncrementalLoading <L"Windows.UI.Xaml.Data.ISupportIncrementalLoading">
DEFINE_IIDX(ISupportIncrementalLoading, "7F5EE992-7694-4E6C-A51B-E34BF43DE743")

.comdef ISupportIncrementalLoading : public IInspectable

    LoadMoreItemsAsync	proc :UINT32, :ptr
    get_HasMoreItems	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CData_CICollectionViewFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CData_CICollectionViewFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Data_ICollectionViewFactory <L"Windows.UI.Xaml.Data.ICollectionViewFactory">
DEFINE_IIDX(ICollectionViewFactory, "34D4AAF4-8E72-4950-9192-ECD07D399D0A")

.comdef ICollectionViewFactory : public IInspectable

    CreateView		proc :ptr
   .ends

endif

.endn
.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_UI_Xaml_Data_CurrentChangingEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Data_CurrentChangingEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_Data_CurrentChangingEventArgs <L"Windows.UI.Xaml.Data.CurrentChangingEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Data_PropertyChangedEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Data_PropertyChangedEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_Data_PropertyChangedEventArgs <L"Windows.UI.Xaml.Data.PropertyChangedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Data_BindingBase_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Data_BindingBase_DEFINED
define RuntimeClass_Windows_UI_Xaml_Data_BindingBase <L"Windows.UI.Xaml.Data.BindingBase">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Data_Binding_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Data_Binding_DEFINED
define RuntimeClass_Windows_UI_Xaml_Data_Binding <L"Windows.UI.Xaml.Data.Binding">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Data_BindingExpressionBase_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Data_BindingExpressionBase_DEFINED
define RuntimeClass_Windows_UI_Xaml_Data_BindingExpressionBase <L"Windows.UI.Xaml.Data.BindingExpressionBase">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Data_BindingExpression_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Data_BindingExpression_DEFINED
define RuntimeClass_Windows_UI_Xaml_Data_BindingExpression <L"Windows.UI.Xaml.Data.BindingExpression">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Data_CollectionViewSource_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Data_CollectionViewSource_DEFINED
define RuntimeClass_Windows_UI_Xaml_Data_CollectionViewSource <L"Windows.UI.Xaml.Data.CollectionViewSource">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Data_RelativeSource_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Data_RelativeSource_DEFINED
define RuntimeClass_Windows_UI_Xaml_Data_RelativeSource <L"Windows.UI.Xaml.Data.RelativeSource">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Data_BindingOperations_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Data_BindingOperations_DEFINED
define RuntimeClass_Windows_UI_Xaml_Data_BindingOperations <L"Windows.UI.Xaml.Data.BindingOperations">
endif

endif
