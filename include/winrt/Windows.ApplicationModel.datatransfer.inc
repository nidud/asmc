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

ifndef __windows2Eapplicationmodel2Edatatransfer_h__
define __windows2Eapplicationmodel2Edatatransfer_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include Windows.Storage.inc
include Windows.UI.inc
include windows.foundation.collections.inc

ifndef DEF___FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CDataTransfer__CDataPackage_USE
define DEF___FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CDataTransfer__CDataPackage_USE

DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CDataTransfer__CDataPackage, "a93a3b99-e946-57ce-aad9-c23d138c353e")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CDataTransfer__CDataPackage : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CApplicationModel__CDataTransfer__CDataPackage_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CApplicationModel__CDataTransfer__CDataPackage_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperation_1_Windows__CApplicationModel__CDataTransfer__CDataPackage, "a16f2d07-ead3-53e4-9490-75bdbaeb7a5b")

.comdef __FIAsyncOperation_1_Windows__CApplicationModel__CDataTransfer__CDataPackage : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CApplicationModel__CDataTransfer__CDataPackage_IInspectable_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CApplicationModel__CDataTransfer__CDataPackage_IInspectable_INTERFACE_DEFINED__

DEFINE_IIDX(__FITypedEventHandler_2_Windows__CApplicationModel__CDataTransfer__CDataPackage_IInspectable, "c156b0c3-1cbc-5ca4-901c-62c5a8ca5cb5")

.comdef __FITypedEventHandler_2_Windows__CApplicationModel__CDataTransfer__CDataPackage_IInspectable : public IUnknown

    _Invoke		proc :ptr, :ptr
    .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CApplicationModel__CDataTransfer__CDataPackage_Windows__CApplicationModel__CDataTransfer__COperationCompletedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CApplicationModel__CDataTransfer__CDataPackage_Windows__CApplicationModel__CDataTransfer__COperationCompletedEventArgs_INTERFACE_DEFINED__

DEFINE_IIDX(__FITypedEventHandler_2_Windows__CApplicationModel__CDataTransfer__CDataPackage_Windows__CApplicationModel__CDataTransfer__COperationCompletedEventArgs, "dd48af6c-ef9a-59cb-b326-57d9e2411f21")

.comdef __FITypedEventHandler_2_Windows__CApplicationModel__CDataTransfer__CDataPackage_Windows__CApplicationModel__CDataTransfer__COperationCompletedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
    .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CApplicationModel__CDataTransfer__CDataTransferManager_Windows__CApplicationModel__CDataTransfer__CDataRequestedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CApplicationModel__CDataTransfer__CDataTransferManager_Windows__CApplicationModel__CDataTransfer__CDataRequestedEventArgs_INTERFACE_DEFINED__

DEFINE_IIDX(__FITypedEventHandler_2_Windows__CApplicationModel__CDataTransfer__CDataTransferManager_Windows__CApplicationModel__CDataTransfer__CDataRequestedEventArgs, "ec6f9cc8-46d0-5e0e-b4d2-7d7773ae37a0")

.comdef __FITypedEventHandler_2_Windows__CApplicationModel__CDataTransfer__CDataTransferManager_Windows__CApplicationModel__CDataTransfer__CDataRequestedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
    .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CApplicationModel__CDataTransfer__CDataTransferManager_Windows__CApplicationModel__CDataTransfer__CTargetApplicationChosenEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CApplicationModel__CDataTransfer__CDataTransferManager_Windows__CApplicationModel__CDataTransfer__CTargetApplicationChosenEventArgs_INTERFACE_DEFINED__

DEFINE_IIDX(__FITypedEventHandler_2_Windows__CApplicationModel__CDataTransfer__CDataTransferManager_Windows__CApplicationModel__CDataTransfer__CTargetApplicationChosenEventArgs, "c4ac1ba2-7851-5a44-bc8d-3d7c713f1f41")

.comdef __FITypedEventHandler_2_Windows__CApplicationModel__CDataTransfer__CDataTransferManager_Windows__CApplicationModel__CDataTransfer__CTargetApplicationChosenEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
    .ends

endif

.namespace Windows
.namespace ApplicationModel
.namespace DataTransfer

.enum DataPackageOperation {
    DataPackageOperation_None,
    DataPackageOperation_Copy,
    DataPackageOperation_Move,
    DataPackageOperation_Link
    }


ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataProviderHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataProviderHandler_INTERFACE_DEFINED__

DEFINE_IIDX(IDataProviderHandler, "E7ECD720-F2F4-4A2D-920E-170A2F482A27")

.comdef IDataProviderHandler : public IUnknown

    _Invoke		proc :ptr
    .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIStandardDataFormatsStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIStandardDataFormatsStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IStandardDataFormatsStatics <L"Windows.ApplicationModel.DataTransfer.IStandardDataFormatsStatics">

DEFINE_IIDX(IStandardDataFormatsStatics, "7ED681A1-A880-40C9-B4ED-0BEE1E15F549")

.comdef IStandardDataFormatsStatics : public IInspectable

    get_Text		proc :ptr
    get_Uri		proc :ptr
    get_Html		proc :ptr
    get_Rtf		proc :ptr
    get_Bitmap		proc :ptr
    get_StorageItems	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIStandardDataFormatsStatics2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIStandardDataFormatsStatics2_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IStandardDataFormatsStatics2 <L"Windows.ApplicationModel.DataTransfer.IStandardDataFormatsStatics2">

DEFINE_IIDX(IStandardDataFormatsStatics2, "42A254F4-9D76-42E8-861B-47C25DD0CF71")

.comdef IStandardDataFormatsStatics2 : public IInspectable

    get_WebLink		proc :ptr
    get_ApplicationLink proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackagePropertySetView_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackagePropertySetView_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IDataPackagePropertySetView <L"Windows.ApplicationModel.DataTransfer.IDataPackagePropertySetView">

DEFINE_IIDX(IDataPackagePropertySetView, "B94CEC01-0C1A-4C57-BE55-75D01289735D")

.comdef IDataPackagePropertySetView : public IInspectable

    get_Title		proc :ptr
    get_Description	proc :ptr
    get_Thumbnail	proc :ptr
    get_FileTypes	proc :ptr
    get_ApplicationName proc :ptr
    get_ApplicationListingUri proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackagePropertySetView2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackagePropertySetView2_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IDataPackagePropertySetView2 <L"Windows.ApplicationModel.DataTransfer.IDataPackagePropertySetView2">

DEFINE_IIDX(IDataPackagePropertySetView2, "6054509B-8EBE-4FEB-9C1E-75E69DE54B84")

.comdef IDataPackagePropertySetView2 : public IInspectable

    get_PackageFamilyName proc :ptr
    get_ContentSourceWebLink proc :ptr
    get_ContentSourceApplicationLink proc :ptr
    get_Square30x30Logo proc :ptr
    get_LogoBackgroundColor proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackagePropertySet_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackagePropertySet_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IDataPackagePropertySet <L"Windows.ApplicationModel.DataTransfer.IDataPackagePropertySet">

DEFINE_IIDX(IDataPackagePropertySet, "CD1C93EB-4C4C-443A-A8D3-F5C241E91689")

.comdef IDataPackagePropertySet : public IInspectable

    get_Title		proc :ptr
    put_Title		proc :HSTRING
    get_Description	proc :ptr
    put_Description	proc :HSTRING
    get_Thumbnail	proc :ptr
    put_Thumbnail	proc :ptr
    get_FileTypes	proc :ptr
    get_ApplicationName proc :ptr
    put_ApplicationName proc :HSTRING
    get_ApplicationListingUri proc :ptr
    put_ApplicationListingUri proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackagePropertySet2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackagePropertySet2_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IDataPackagePropertySet2 <L"Windows.ApplicationModel.DataTransfer.IDataPackagePropertySet2">

DEFINE_IIDX(IDataPackagePropertySet2, "EB505D4A-9800-46AA-B181-7B6F0F2B919A")

.comdef IDataPackagePropertySet2 : public IInspectable

    get_ContentSourceWebLink proc :ptr
    put_ContentSourceWebLink proc :ptr
    get_ContentSourceApplicationLink proc :ptr
    put_ContentSourceApplicationLink proc :ptr
    get_PackageFamilyName proc :ptr
    put_PackageFamilyName proc :HSTRING
    get_Square30x30Logo proc :ptr
    put_Square30x30Logo proc :ptr
    get_LogoBackgroundColor proc :ptr
    put_LogoBackgroundColor proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataProviderDeferral_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataProviderDeferral_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IDataProviderDeferral <L"Windows.ApplicationModel.DataTransfer.IDataProviderDeferral">

DEFINE_IIDX(IDataProviderDeferral, "C2CF2373-2D26-43D9-B69D-DCB86D03F6DA")

.comdef IDataProviderDeferral : public IInspectable

    Complete		proc
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataProviderRequest_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataProviderRequest_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IDataProviderRequest <L"Windows.ApplicationModel.DataTransfer.IDataProviderRequest">

DEFINE_IIDX(IDataProviderRequest, "EBBC7157-D3C8-47DA-ACDE-F82388D5F716")

.comdef IDataProviderRequest : public IInspectable

    get_FormatId	proc :ptr
    get_Deadline	proc :ptr
    GetDeferral		proc :ptr
    SetData		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIOperationCompletedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIOperationCompletedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IOperationCompletedEventArgs <L"Windows.ApplicationModel.DataTransfer.IOperationCompletedEventArgs">

DEFINE_IIDX(IOperationCompletedEventArgs, "E7AF329D-051D-4FAB-B1A9-47FD77F70A41")

.comdef IOperationCompletedEventArgs : public IInspectable

    get_Operation	proc :ptr
    .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackageView_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackageView_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IDataPackageView <L"Windows.ApplicationModel.DataTransfer.IDataPackageView">

DEFINE_IIDX(IDataPackageView, "7B840471-5900-4D85-A90B-10CB85FE3552")

.comdef IDataPackageView : public IInspectable

    get_Properties	proc :ptr
    get_RequestedOperation proc :ptr
    ReportOperationCompleted proc :ptr
    get_AvailableFormats proc :ptr
    Contains		proc :HSTRING, :ptr
    GetDataAsync	proc :HSTRING, :ptr
    GetTextAsync	proc :ptr
    GetCustomTextAsync	proc :HSTRING, :ptr
    GetUriAsync		proc :ptr
    GetHtmlFormatAsync	proc :ptr
    GetResourceMapAsync proc :ptr
    GetRtfAsync		proc :ptr
    GetBitmapAsync	proc :ptr
    GetStorageItemsAsync proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackageView2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackageView2_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IDataPackageView2 <L"Windows.ApplicationModel.DataTransfer.IDataPackageView2">

DEFINE_IIDX(IDataPackageView2, "40ECBA95-2450-4C1D-B6B4-ED45463DEE9C")

.comdef IDataPackageView2 : public IInspectable

    GetApplicationLinkAsync proc :ptr
    GetWebLinkAsync	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackage_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackage_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IDataPackage <L"Windows.ApplicationModel.DataTransfer.IDataPackage">

DEFINE_IIDX(IDataPackage, "61EBF5C7-EFEA-4346-9554-981D7E198FFE")

.comdef IDataPackage : public IInspectable

    GetView		proc :ptr
    get_Properties	proc :ptr
    get_RequestedOperation proc :ptr
    put_RequestedOperation proc :ptr
    add_OperationCompleted proc :ptr, :ptr
    remove_OperationCompleted proc :EventRegistrationToken
    add_Destroyed	proc :ptr, :ptr
    remove_Destroyed	proc :EventRegistrationToken
    SetData		proc :HSTRING, :ptr
    SetDataProvider	proc :HSTRING, :ptr
    SetText		proc :HSTRING
    SetUri		proc :ptr
    SetHtmlFormat	proc :HSTRING
    get_ResourceMap	proc :ptr
    SetRtf		proc :HSTRING
    SetBitmap		proc :ptr
    SetStorageItemsReadOnly proc :ptr
    SetStorageItems	proc :ptr, :boolean
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackage2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackage2_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IDataPackage2 <L"Windows.ApplicationModel.DataTransfer.IDataPackage2">

DEFINE_IIDX(IDataPackage2, "041C1FE9-2409-45E1-A538-4C53EEEE04A7")

.comdef IDataPackage2 : public IInspectable

    SetApplicationLink	proc :ptr
    SetWebLink		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIHtmlFormatHelperStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIHtmlFormatHelperStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IHtmlFormatHelperStatics <L"Windows.ApplicationModel.DataTransfer.IHtmlFormatHelperStatics">

DEFINE_IIDX(IHtmlFormatHelperStatics, "E22E7749-DD70-446F-AEFC-61CEE59F655E")

.comdef IHtmlFormatHelperStatics : public IInspectable

    GetStaticFragment	proc :HSTRING, :ptr
    CreateHtmlFormat	proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIClipboardStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIClipboardStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IClipboardStatics <L"Windows.ApplicationModel.DataTransfer.IClipboardStatics">

DEFINE_IIDX(IClipboardStatics, "C627E291-34E2-4963-8EED-93CBB0EA3D70")

.comdef IClipboardStatics : public IInspectable

    GetContent		proc :ptr
    SetContent		proc :ptr
    Flush		proc
    Clear		proc
    add_ContentChanged	proc :ptr, :ptr
    remove_ContentChanged proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataRequestDeferral_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataRequestDeferral_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IDataRequestDeferral <L"Windows.ApplicationModel.DataTransfer.IDataRequestDeferral">

DEFINE_IIDX(IDataRequestDeferral, "6DC4B89F-0386-4263-87C1-ED7DCE30890E")

.comdef IDataRequestDeferral : public IInspectable

    Complete		proc
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataRequest_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataRequest_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IDataRequest <L"Windows.ApplicationModel.DataTransfer.IDataRequest">

DEFINE_IIDX(IDataRequest, "4341AE3B-FC12-4E53-8C02-AC714C415A27")

.comdef IDataRequest : public IInspectable

    get_Data		proc :ptr
    put_Data		proc :ptr
    get_Deadline	proc :ptr
    FailWithDisplayText proc :HSTRING
    GetDeferral		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataRequestedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataRequestedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IDataRequestedEventArgs <L"Windows.ApplicationModel.DataTransfer.IDataRequestedEventArgs">

DEFINE_IIDX(IDataRequestedEventArgs, "CB8BA807-6AC5-43C9-8AC5-9BA232163182")

.comdef IDataRequestedEventArgs : public IInspectable

    get_Request		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CITargetApplicationChosenEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CITargetApplicationChosenEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_ITargetApplicationChosenEventArgs <L"Windows.ApplicationModel.DataTransfer.ITargetApplicationChosenEventArgs">

DEFINE_IIDX(ITargetApplicationChosenEventArgs, "CA6FB8AC-2987-4EE3-9C54-D8AFBCB86C1D")

.comdef ITargetApplicationChosenEventArgs : public IInspectable

    get_ApplicationName proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataTransferManager_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataTransferManager_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IDataTransferManager <L"Windows.ApplicationModel.DataTransfer.IDataTransferManager">

DEFINE_IIDX(IDataTransferManager, "A5CAEE9B-8708-49D1-8D36-67D25A8DA00C")

.comdef IDataTransferManager : public IInspectable

    add_DataRequested	proc :ptr, :ptr
    remove_DataRequested proc :EventRegistrationToken
    add_TargetApplicationChosen proc :ptr, :ptr
    remove_TargetApplicationChosen proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataTransferManagerStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataTransferManagerStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IDataTransferManagerStatics <L"Windows.ApplicationModel.DataTransfer.IDataTransferManagerStatics">

DEFINE_IIDX(IDataTransferManagerStatics, "A9DA01AA-E00E-4CFE-AA44-2DD932DCA3D8")

.comdef IDataTransferManagerStatics : public IInspectable

    ShowShareUI		proc
    GetForCurrentView	proc :ptr
   .ends

endif

.endn
.endn
.endn

define RuntimeClass_Windows_ApplicationModel_DataTransfer_StandardDataFormats <L"Windows.ApplicationModel.DataTransfer.StandardDataFormats">
define RuntimeClass_Windows_ApplicationModel_DataTransfer_DataPackagePropertySetView <L"Windows.ApplicationModel.DataTransfer.DataPackagePropertySetView">
define RuntimeClass_Windows_ApplicationModel_DataTransfer_DataPackagePropertySet <L"Windows.ApplicationModel.DataTransfer.DataPackagePropertySet">
define RuntimeClass_Windows_ApplicationModel_DataTransfer_DataProviderDeferral <L"Windows.ApplicationModel.DataTransfer.DataProviderDeferral">
define RuntimeClass_Windows_ApplicationModel_DataTransfer_DataProviderRequest <L"Windows.ApplicationModel.DataTransfer.DataProviderRequest">
define RuntimeClass_Windows_ApplicationModel_DataTransfer_OperationCompletedEventArgs <L"Windows.ApplicationModel.DataTransfer.OperationCompletedEventArgs">
define RuntimeClass_Windows_ApplicationModel_DataTransfer_DataPackageView <L"Windows.ApplicationModel.DataTransfer.DataPackageView">
define RuntimeClass_Windows_ApplicationModel_DataTransfer_DataPackage <L"Windows.ApplicationModel.DataTransfer.DataPackage">
define RuntimeClass_Windows_ApplicationModel_DataTransfer_HtmlFormatHelper <L"Windows.ApplicationModel.DataTransfer.HtmlFormatHelper">
define RuntimeClass_Windows_ApplicationModel_DataTransfer_Clipboard <L"Windows.ApplicationModel.DataTransfer.Clipboard">
define RuntimeClass_Windows_ApplicationModel_DataTransfer_DataRequestDeferral <L"Windows.ApplicationModel.DataTransfer.DataRequestDeferral">
define RuntimeClass_Windows_ApplicationModel_DataTransfer_DataRequest <L"Windows.ApplicationModel.DataTransfer.DataRequest">
define RuntimeClass_Windows_ApplicationModel_DataTransfer_DataRequestedEventArgs <L"Windows.ApplicationModel.DataTransfer.DataRequestedEventArgs">
define RuntimeClass_Windows_ApplicationModel_DataTransfer_TargetApplicationChosenEventArgs <L"Windows.ApplicationModel.DataTransfer.TargetApplicationChosenEventArgs">
define RuntimeClass_Windows_ApplicationModel_DataTransfer_DataTransferManager <L"Windows.ApplicationModel.DataTransfer.DataTransferManager">

HSTRING_UserSize	proto WINAPI :ptr DWORD, :DWORD, :ptr HSTRING
HSTRING_UserMarshal	proto WINAPI :ptr DWORD, :LPBYTE, :ptr HSTRING
HSTRING_UserUnmarshal	proto WINAPI :ptr DWORD, :LPBYTE, :ptr HSTRING
HSTRING_UserFree	proto WINAPI :ptr DWORD, :ptr HSTRING

HSTRING_UserSize64	proto WINAPI :ptr DWORD, :DWORD, :ptr HSTRING
HSTRING_UserMarshal64	proto WINAPI :ptr DWORD, :LPBYTE, :ptr HSTRING
HSTRING_UserUnmarshal64 proto WINAPI :ptr DWORD, :LPBYTE, :ptr HSTRING
HSTRING_UserFree64	proto WINAPI :ptr DWORD, :ptr HSTRING

endif
