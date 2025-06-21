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

ifndef __windows2Eapplicationmodel2Edatatransfer_p_h__
define __windows2Eapplicationmodel2Edatatransfer_p_h__

ifndef DISABLE_NS_PREFIX_CHECKS
ifndef CHECK_NS_PREFIX_STATE
define CHECK_NS_PREFIX_STATE <"always">
endif
endif


ifndef SPECIFIC_API_CONTRACT_DEFINITIONS
ifndef WINDOWS_FOUNDATION_FOUNDATIONCONTRACT_VERSION
define WINDOWS_FOUNDATION_FOUNDATIONCONTRACT_VERSION 0x40000
endif
ifndef WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION
define WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION 0xa0000
endif
ifndef WINDOWS_SECURITY_ENTERPRISEDATA_ENTERPRISEDATACONTRACT_VERSION
define WINDOWS_SECURITY_ENTERPRISEDATA_ENTERPRISEDATACONTRACT_VERSION 0x50000
endif
endif

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include windowscontracts.inc
include Windows.Foundation.inc
include Windows.Security.EnterpriseData.inc
include Windows.Storage.inc
include Windows.Storage.Streams.inc
include Windows.UI.inc
include windows.foundation.collections.inc

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x70000
ifndef ____FIVectorView_1_Windows__CApplicationModel__CDataTransfer__CClipboardHistoryItem_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CApplicationModel__CDataTransfer__CClipboardHistoryItem_INTERFACE_DEFINED__

.comdef __FIVectorView_1_Windows__CApplicationModel__CDataTransfer__CClipboardHistoryItem : public IInspectable

    GetAt       proc :UINT32, :ptr
    get_Size    proc :ptr
    IndexOf     proc :ptr, :ptr, :ptr
    GetMany     proc :UINT32, :UINT32, :ptr, :ptr
   .ends

endif
endif

ifndef ____FIAsyncOperation_1_Windows__CApplicationModel__CDataTransfer__CClipboardHistoryItemsResult_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CApplicationModel__CDataTransfer__CClipboardHistoryItemsResult_INTERFACE_DEFINED__

.comdef __FIAsyncOperation_1_Windows__CApplicationModel__CDataTransfer__CClipboardHistoryItemsResult : public IInspectable

    put_Completed   proc :ptr
    get_Completed   proc :ptr
    GetResults      proc :ptr
   .ends

endif

.namespace Windows
.namespace ApplicationModel
.namespace DataTransfer

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x70000
.enum ClipboardHistoryItemsResultStatus : int_t {
    ClipboardHistoryItemsResultStatus_Success = 0,
    ClipboardHistoryItemsResultStatus_AccessDenied = 1,
    ClipboardHistoryItemsResultStatus_ClipboardHistoryDisabled = 2,
    }
endif
if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x10000
.enum DataPackageOperation : dword {
    DataPackageOperation_None = 0,
    DataPackageOperation_Copy = 0x1,
    DataPackageOperation_Move = 0x2,
    DataPackageOperation_Link = 0x4,
    }
endif
if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x70000
.enum SetHistoryItemAsContentStatus : int_t {
    SetHistoryItemAsContentStatus_Success = 0,
    SetHistoryItemAsContentStatus_AccessDenied = 1,
    SetHistoryItemAsContentStatus_ItemDeleted = 2,
    }
endif
if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x50000
.enum ShareUITheme : int_t {
    ShareUITheme_Default = 0,
    ShareUITheme_Light = 1,
    ShareUITheme_Dark = 2,
    }
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x10000

ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataProviderHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataProviderHandler_INTERFACE_DEFINED__

DEFINE_IIDX(IDataProviderHandler, "e7ecd720-f2f4-4a2d-920e-170a2f482a27")

.comdef IDataProviderHandler : public IUnknown

    IInvoke proc :ptr
   .ends

endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x40000
ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIShareProviderHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIShareProviderHandler_INTERFACE_DEFINED__

DEFINE_IIDX(IShareProviderHandler, "e7f9d9ba-e1ba-4e4d-bd65-d43845d3212f")

.comdef IShareProviderHandler : public IUnknown

    IInvoke proc :ptr
   .ends

endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x70000
ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIClipboardContentOptions_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIClipboardContentOptions_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IClipboardContentOptions <L"Windows.ApplicationModel.DataTransfer.IClipboardContentOptions">

DEFINE_IIDX(IClipboardContentOptions, "e888a98c-ad4b-5447-a056-ab3556276d2b")

.comdef IClipboardContentOptions : public IInspectable

    get_IsRoamable proc :ptr
    put_IsRoamable proc :boolean
    get_IsAllowedInHistory proc :ptr
    put_IsAllowedInHistory proc :boolean
    get_RoamingFormats proc :ptr
    get_HistoryFormats proc :ptr
   .ends

endif
endif


if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x70000
ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIClipboardHistoryChangedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIClipboardHistoryChangedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IClipboardHistoryChangedEventArgs <L"Windows.ApplicationModel.DataTransfer.IClipboardHistoryChangedEventArgs">

DEFINE_IIDX(IClipboardHistoryChangedEventArgs, "c0be453f-8ea2-53ce-9aba-8d2212573452")

.comdef IClipboardHistoryChangedEventArgs : public IInspectable
   .ends

endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x70000
ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIClipboardHistoryItem_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIClipboardHistoryItem_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IClipboardHistoryItem <L"Windows.ApplicationModel.DataTransfer.IClipboardHistoryItem">

DEFINE_IIDX(IClipboardHistoryItem, "0173bd8a-afff-5c50-ab92-3d19f481ec58")

.comdef IClipboardHistoryItem : public IInspectable

    get_Id proc :ptr
    get_Timestamp proc :ptr
    get_Content proc :ptr
   .ends

endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x70000
ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIClipboardHistoryItemsResult_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIClipboardHistoryItemsResult_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IClipboardHistoryItemsResult <L"Windows.ApplicationModel.DataTransfer.IClipboardHistoryItemsResult">

DEFINE_IIDX(IClipboardHistoryItemsResult, "e6dfdee6-0ee2-52e3-852b-f295db65939a")

.comdef IClipboardHistoryItemsResult : public IInspectable

    get_Status proc :ptr
    get_Items proc :ptr
   .ends

endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x10000
ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIClipboardStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIClipboardStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IClipboardStatics <L"Windows.ApplicationModel.DataTransfer.IClipboardStatics">

DEFINE_IIDX(IClipboardStatics, "c627e291-34e2-4963-8eed-93cbb0ea3d70")

.comdef IClipboardStatics : public IInspectable

    GetContent proc :ptr
    SetContent proc :ptr
    Flush proc
    Clear proc
    add_ContentChanged proc :ptr, :ptr
    remove_ContentChanged proc :EventRegistrationToken
   .ends

endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x70000
ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIClipboardStatics2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIClipboardStatics2_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IClipboardStatics2 <L"Windows.ApplicationModel.DataTransfer.IClipboardStatics2">

DEFINE_IIDX(IClipboardStatics2, "d2ac1b6a-d29f-554b-b303-f0452345fe02")

.comdef IClipboardStatics2 : public IInspectable

    GetHistoryItemsAsync proc :ptr
    ClearHistory proc :ptr
    DeleteItemFromHistory proc :ptr, :ptr
    SetHistoryItemAsContent proc :ptr, :ptr
    IsHistoryEnabled proc :ptr
    IsRoamingEnabled proc :ptr
    SetContentWithOptions proc :ptr, :ptr, :ptr
    add_HistoryChanged proc :ptr, :ptr
    remove_HistoryChanged proc :EventRegistrationToken
    add_RoamingEnabledChanged proc :ptr, :ptr
    remove_RoamingEnabledChanged proc :EventRegistrationToken
    add_HistoryEnabledChanged proc :ptr, :ptr
    remove_HistoryEnabledChanged proc :EventRegistrationToken
   .ends

endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x10000
ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackage_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackage_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IDataPackage <L"Windows.ApplicationModel.DataTransfer.IDataPackage">

DEFINE_IIDX(IDataPackage, "61ebf5c7-efea-4346-9554-981d7e198ffe")

.comdef IDataPackage : public IInspectable

    GetView proc :ptr
    get_Properties proc :ptr
    get_RequestedOperation proc :ptr
    put_RequestedOperation proc :Windows::ApplicationModel::DataTransfer::DataPackageOperation
    add_OperationCompleted proc :ptr, :ptr
    remove_OperationCompleted proc :EventRegistrationToken
    add_Destroyed proc :ptr, :ptr
    remove_Destroyed proc :EventRegistrationToken
    SetData proc :HSTRING, :ptr
    SetDataProvider proc :HSTRING, :ptr
    SetText proc :HSTRING
if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x10000
    ;DEPRECATED("SetUri may be altered or unavailable for releases after Windows Phone 'OSVersion' (TBD).Instead, use SetWebLink or SetApplicationLink.")
endif
    SetUri proc :ptr
    SetHtmlFormat proc :HSTRING
    get_ResourceMap proc :ptr
    SetRtf proc :HSTRING
    SetBitmap proc :ptr
    SetStorageItemsReadOnly proc :ptr
    SetStorageItems proc :ptr, :boolean
   .ends

endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x10000
ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackage2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackage2_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IDataPackage2 <L"Windows.ApplicationModel.DataTransfer.IDataPackage2">

DEFINE_IIDX(IDataPackage2, "041c1fe9-2409-45e1-a538-4c53eeee04a7")

.comdef IDataPackage2 : public IInspectable

    SetApplicationLink proc :ptr
    SetWebLink proc :ptr
   .ends

endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x40000
ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackage3_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackage3_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IDataPackage3 <L"Windows.ApplicationModel.DataTransfer.IDataPackage3">

DEFINE_IIDX(IDataPackage3, "88f31f5d-787b-4d32-965a-a9838105a056")

.comdef IDataPackage3 : public IInspectable

    add_ShareCompleted proc :ptr, :ptr
    remove_ShareCompleted proc :EventRegistrationToken
   .ends

endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0xa0000
ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackage4_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackage4_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IDataPackage4 <L"Windows.ApplicationModel.DataTransfer.IDataPackage4">

DEFINE_IIDX(IDataPackage4, "13a24ec8-9382-536f-852a-3045e1b29a3b")

.comdef IDataPackage4 : public IInspectable

    add_ShareCanceled proc :ptr, :ptr
    remove_ShareCanceled proc :EventRegistrationToken
   .ends

endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x10000
ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackagePropertySet_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackagePropertySet_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IDataPackagePropertySet <L"Windows.ApplicationModel.DataTransfer.IDataPackagePropertySet">

DEFINE_IIDX(IDataPackagePropertySet, "cd1c93eb-4c4c-443a-a8d3-f5c241e91689")

.comdef IDataPackagePropertySet : public IInspectable

    get_Title proc :ptr
    put_Title proc :HSTRING
    get_Description proc :ptr
    put_Description proc :HSTRING
    get_Thumbnail proc :ptr
    put_Thumbnail proc :ptr
    get_FileTypes proc :ptr
    get_ApplicationName proc :ptr
    put_ApplicationName proc :HSTRING
    get_ApplicationListingUri proc :ptr
    put_ApplicationListingUri proc :ptr
   .ends

endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x10000
ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackagePropertySet2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackagePropertySet2_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IDataPackagePropertySet2 <L"Windows.ApplicationModel.DataTransfer.IDataPackagePropertySet2">

DEFINE_IIDX(IDataPackagePropertySet2, "eb505d4a-9800-46aa-b181-7b6f0f2b919a")

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
    put_LogoBackgroundColor proc :Windows::UI::Color
   .ends

endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x10000
ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackagePropertySet3_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackagePropertySet3_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IDataPackagePropertySet3 <L"Windows.ApplicationModel.DataTransfer.IDataPackagePropertySet3">

DEFINE_IIDX(IDataPackagePropertySet3, "9e87fd9b-5205-401b-874a-455653bd39e8")

.comdef IDataPackagePropertySet3 : public IInspectable

    get_EnterpriseId proc :ptr
    put_EnterpriseId proc :HSTRING
   .ends

endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackagePropertySet4_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackagePropertySet4_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IDataPackagePropertySet4 <L"Windows.ApplicationModel.DataTransfer.IDataPackagePropertySet4">

DEFINE_IIDX(IDataPackagePropertySet4, "6390ebf5-1739-4c74-b22f-865fab5e8545")

.comdef IDataPackagePropertySet4 : public IInspectable

    get_ContentSourceUserActivityJson proc :ptr
    put_ContentSourceUserActivityJson proc :HSTRING
   .ends

endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x10000
ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackagePropertySetView_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackagePropertySetView_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IDataPackagePropertySetView <L"Windows.ApplicationModel.DataTransfer.IDataPackagePropertySetView">

DEFINE_IIDX(IDataPackagePropertySetView, "b94cec01-0c1a-4c57-be55-75d01289735d")

.comdef IDataPackagePropertySetView : public IInspectable

    get_Title proc :ptr
    get_Description proc :ptr
    get_Thumbnail proc :ptr
    get_FileTypes proc :ptr
    get_ApplicationName proc :ptr
    get_ApplicationListingUri proc :ptr
   .ends

endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x10000
ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackagePropertySetView2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackagePropertySetView2_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IDataPackagePropertySetView2 <L"Windows.ApplicationModel.DataTransfer.IDataPackagePropertySetView2">

DEFINE_IIDX(IDataPackagePropertySetView2, "6054509b-8ebe-4feb-9c1e-75e69de54b84")

.comdef IDataPackagePropertySetView2 : public IInspectable

    get_PackageFamilyName proc :ptr
    get_ContentSourceWebLink proc :ptr
    get_ContentSourceApplicationLink proc :ptr
    get_Square30x30Logo proc :ptr
    get_LogoBackgroundColor proc :ptr
   .ends

endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x10000
ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackagePropertySetView3_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackagePropertySetView3_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IDataPackagePropertySetView3 <L"Windows.ApplicationModel.DataTransfer.IDataPackagePropertySetView3">

DEFINE_IIDX(IDataPackagePropertySetView3, "db764ce5-d174-495c-84fc-1a51f6ab45d7")

.comdef IDataPackagePropertySetView3 : public IInspectable

    get_EnterpriseId proc :ptr
   .ends

endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackagePropertySetView4_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackagePropertySetView4_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IDataPackagePropertySetView4 <L"Windows.ApplicationModel.DataTransfer.IDataPackagePropertySetView4">

DEFINE_IIDX(IDataPackagePropertySetView4, "4474c80d-d16f-40ae-9580-6f8562b94235")

.comdef IDataPackagePropertySetView4 : public IInspectable

    get_ContentSourceUserActivityJson proc :ptr
   .ends

endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x70000
ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackagePropertySetView5_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackagePropertySetView5_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IDataPackagePropertySetView5 <L"Windows.ApplicationModel.DataTransfer.IDataPackagePropertySetView5">

DEFINE_IIDX(IDataPackagePropertySetView5, "6f0a9445-3760-50bb-8523-c4202ded7d78")

.comdef IDataPackagePropertySetView5 : public IInspectable

    get_IsFromRoamingClipboard proc :ptr
   .ends

endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x10000
ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackageView_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackageView_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IDataPackageView <L"Windows.ApplicationModel.DataTransfer.IDataPackageView">

DEFINE_IIDX(IDataPackageView, "7b840471-5900-4d85-a90b-10cb85fe3552")

.comdef IDataPackageView : public IInspectable

    get_Properties proc :ptr
    get_RequestedOperation proc :ptr
    ReportOperationCompleted proc :Windows::ApplicationModel::DataTransfer::DataPackageOperation
    get_AvailableFormats proc :ptr
    Contains proc :HSTRING, :ptr
    GetDataAsync proc :HSTRING, :ptr
    GetTextAsync proc :ptr
    GetCustomTextAsync proc :HSTRING, :ptr
if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x10000
endif
    GetUriAsync proc :ptr
    GetHtmlFormatAsync proc :ptr
    GetResourceMapAsync proc :ptr
    GetRtfAsync proc :ptr
    GetBitmapAsync proc :ptr
    GetStorageItemsAsync proc :ptr
   .ends

endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x10000
ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackageView2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackageView2_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IDataPackageView2 <L"Windows.ApplicationModel.DataTransfer.IDataPackageView2">

DEFINE_IIDX(IDataPackageView2, "40ecba95-2450-4c1d-b6b4-ed45463dee9c")

.comdef IDataPackageView2 : public IInspectable

    GetApplicationLinkAsync proc :ptr
    GetWebLinkAsync proc :ptr
   .ends

endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x10000
ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackageView3_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackageView3_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IDataPackageView3 <L"Windows.ApplicationModel.DataTransfer.IDataPackageView3">

DEFINE_IIDX(IDataPackageView3, "d37771a8-ddad-4288-8428-d1cae394128b")

.comdef IDataPackageView3 : public IInspectable

    RequestAccessAsync proc :ptr
    RequestAccessWithEnterpriseIdAsync proc :HSTRING, :ptr
    UnlockAndAssumeEnterpriseIdentity proc :ptr
   .ends

endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackageView4_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataPackageView4_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IDataPackageView4 <L"Windows.ApplicationModel.DataTransfer.IDataPackageView4">

DEFINE_IIDX(IDataPackageView4, "dfe96f1f-e042-4433-a09f-26d6ffda8b85")

.comdef IDataPackageView4 : public IInspectable

    SetAcceptedFormatId proc :HSTRING
   .ends

endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x10000
ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataProviderDeferral_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataProviderDeferral_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IDataProviderDeferral <L"Windows.ApplicationModel.DataTransfer.IDataProviderDeferral">

DEFINE_IIDX(IDataProviderDeferral, "c2cf2373-2d26-43d9-b69d-dcb86d03f6da")

.comdef IDataProviderDeferral : public IInspectable

    Complete proc
   .ends

endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x10000
ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataProviderRequest_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataProviderRequest_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IDataProviderRequest <L"Windows.ApplicationModel.DataTransfer.IDataProviderRequest">

DEFINE_IIDX(IDataProviderRequest, "ebbc7157-d3c8-47da-acde-f82388d5f716")

.comdef IDataProviderRequest : public IInspectable

    get_FormatId proc :ptr
    get_Deadline proc :ptr
    GetDeferral proc :ptr
    SetData proc :ptr
   .ends

endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x10000
ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataRequest_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataRequest_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IDataRequest <L"Windows.ApplicationModel.DataTransfer.IDataRequest">

DEFINE_IIDX(IDataRequest, "4341ae3b-fc12-4e53-8c02-ac714c415a27")

.comdef IDataRequest : public IInspectable

    get_Data proc :ptr
    put_Data proc :ptr
    get_Deadline proc :ptr
    FailWithDisplayText proc :HSTRING
    GetDeferral proc :ptr
   .ends

endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x10000
ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataRequestDeferral_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataRequestDeferral_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IDataRequestDeferral <L"Windows.ApplicationModel.DataTransfer.IDataRequestDeferral">

DEFINE_IIDX(IDataRequestDeferral, "6dc4b89f-0386-4263-87c1-ed7dce30890e")

.comdef IDataRequestDeferral : public IInspectable

    Complete proc
   .ends

endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x10000
ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataRequestedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataRequestedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IDataRequestedEventArgs <L"Windows.ApplicationModel.DataTransfer.IDataRequestedEventArgs">

DEFINE_IIDX(IDataRequestedEventArgs, "cb8ba807-6ac5-43c9-8ac5-9ba232163182")

.comdef IDataRequestedEventArgs : public IInspectable

    get_Request proc :ptr
   .ends

endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x10000
ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataTransferManager_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataTransferManager_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IDataTransferManager <L"Windows.ApplicationModel.DataTransfer.IDataTransferManager">

DEFINE_IIDX(IDataTransferManager, "a5caee9b-8708-49d1-8d36-67d25a8da00c")

.comdef IDataTransferManager : public IInspectable

    add_DataRequested proc :ptr, :ptr
    remove_DataRequested proc :EventRegistrationToken
    add_TargetApplicationChosen proc :ptr, :ptr
    remove_TargetApplicationChosen proc :EventRegistrationToken
   .ends

endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x40000
ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataTransferManager2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataTransferManager2_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IDataTransferManager2 <L"Windows.ApplicationModel.DataTransfer.IDataTransferManager2">

DEFINE_IIDX(IDataTransferManager2, "30ae7d71-8ba8-4c02-8e3f-ddb23b388715")

.comdef IDataTransferManager2 : public IInspectable

    add_ShareProvidersRequested proc :ptr, :ptr
    remove_ShareProvidersRequested proc :EventRegistrationToken
   .ends

endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x10000
ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataTransferManagerStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataTransferManagerStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IDataTransferManagerStatics <L"Windows.ApplicationModel.DataTransfer.IDataTransferManagerStatics">

DEFINE_IIDX(IDataTransferManagerStatics, "a9da01aa-e00e-4cfe-aa44-2dd932dca3d8")

.comdef IDataTransferManagerStatics : public IInspectable

    ShowShareUI proc
    GetForCurrentView proc :ptr
   .ends

endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x30000
ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataTransferManagerStatics2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataTransferManagerStatics2_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IDataTransferManagerStatics2 <L"Windows.ApplicationModel.DataTransfer.IDataTransferManagerStatics2">

DEFINE_IIDX(IDataTransferManagerStatics2, "c54ec2ec-9f97-4d63-9868-395e271ad8f5")

.comdef IDataTransferManagerStatics2 : public IInspectable

    IsSupported proc :ptr
   .ends

endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x50000
ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataTransferManagerStatics3_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIDataTransferManagerStatics3_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IDataTransferManagerStatics3 <L"Windows.ApplicationModel.DataTransfer.IDataTransferManagerStatics3">

DEFINE_IIDX(IDataTransferManagerStatics3, "05845473-6c82-4f5c-ac23-62e458361fac")

.comdef IDataTransferManagerStatics3 : public IInspectable

    ShowShareUIWithOptions proc :ptr
   .ends

endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x10000
ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIHtmlFormatHelperStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIHtmlFormatHelperStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IHtmlFormatHelperStatics <L"Windows.ApplicationModel.DataTransfer.IHtmlFormatHelperStatics">

DEFINE_IIDX(IHtmlFormatHelperStatics, "e22e7749-dd70-446f-aefc-61cee59f655e")

.comdef IHtmlFormatHelperStatics : public IInspectable

    GetStaticFragment proc :HSTRING, :ptr
    CreateHtmlFormat proc :HSTRING, :ptr
   .ends

endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x10000
ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIOperationCompletedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIOperationCompletedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IOperationCompletedEventArgs <L"Windows.ApplicationModel.DataTransfer.IOperationCompletedEventArgs">

DEFINE_IIDX(IOperationCompletedEventArgs, "e7af329d-051d-4fab-b1a9-47fd77f70a41")

.comdef IOperationCompletedEventArgs : public IInspectable

    get_Operation proc :ptr
   .ends

endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x20000
ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIOperationCompletedEventArgs2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIOperationCompletedEventArgs2_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IOperationCompletedEventArgs2 <L"Windows.ApplicationModel.DataTransfer.IOperationCompletedEventArgs2">

DEFINE_IIDX(IOperationCompletedEventArgs2, "858fa073-1e19-4105-b2f7-c8478808d562")

.comdef IOperationCompletedEventArgs2 : public IInspectable

    get_AcceptedFormatId proc :ptr
   .ends

endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x40000
ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIShareCompletedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIShareCompletedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IShareCompletedEventArgs <L"Windows.ApplicationModel.DataTransfer.IShareCompletedEventArgs">

DEFINE_IIDX(IShareCompletedEventArgs, "4574c442-f913-4f60-9df7-cc4060ab1916")

.comdef IShareCompletedEventArgs : public IInspectable

    get_ShareTarget proc :ptr
   .ends

endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x40000
ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIShareProvider_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIShareProvider_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IShareProvider <L"Windows.ApplicationModel.DataTransfer.IShareProvider">

DEFINE_IIDX(IShareProvider, "2fabe026-443e-4cda-af25-8d81070efd80")

.comdef IShareProvider : public IInspectable

    get_Title proc :ptr
    get_DisplayIcon proc :ptr
    get_BackgroundColor proc :ptr
    get_Tag proc :ptr
    put_Tag proc :ptr
   .ends

endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x40000
ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIShareProviderFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIShareProviderFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IShareProviderFactory <L"Windows.ApplicationModel.DataTransfer.IShareProviderFactory">

DEFINE_IIDX(IShareProviderFactory, "172a174c-e79e-4f6d-b07d-128f469e0296")

.comdef IShareProviderFactory : public IInspectable

    Create proc :HSTRING, :ptr, :Windows::UI::Color, :ptr, :ptr
   .ends

endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x40000
ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIShareProviderOperation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIShareProviderOperation_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IShareProviderOperation <L"Windows.ApplicationModel.DataTransfer.IShareProviderOperation">

DEFINE_IIDX(IShareProviderOperation, "19cef937-d435-4179-b6af-14e0492b69f6")

.comdef IShareProviderOperation : public IInspectable

    get_Data proc :ptr
    get_Provider proc :ptr
    ReportCompleted proc
   .ends

endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x40000
ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIShareProvidersRequestedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIShareProvidersRequestedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IShareProvidersRequestedEventArgs <L"Windows.ApplicationModel.DataTransfer.IShareProvidersRequestedEventArgs">

DEFINE_IIDX(IShareProvidersRequestedEventArgs, "f888f356-a3f8-4fce-85e4-8826e63be799")

.comdef IShareProvidersRequestedEventArgs : public IInspectable

    get_Providers proc :ptr
    get_Data proc :ptr
    GetDeferral proc :ptr
   .ends

endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x40000
ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIShareTargetInfo_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIShareTargetInfo_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IShareTargetInfo <L"Windows.ApplicationModel.DataTransfer.IShareTargetInfo">

DEFINE_IIDX(IShareTargetInfo, "385be607-c6e8-4114-b294-28f3bb6f9904")

.comdef IShareTargetInfo : public IInspectable

    get_AppUserModelId proc :ptr
    get_ShareProvider proc :ptr
   .ends

endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x50000
ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIShareUIOptions_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIShareUIOptions_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IShareUIOptions <L"Windows.ApplicationModel.DataTransfer.IShareUIOptions">

DEFINE_IIDX(IShareUIOptions, "72fa8a80-342f-4d90-9551-2ae04e37680c")

.comdef IShareUIOptions : public IInspectable

    get_Theme proc :ptr
    put_Theme proc :Windows::ApplicationModel::DataTransfer::ShareUITheme
    get_SelectionRect proc :ptr
    put_SelectionRect proc :ptr
   .ends

endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x10000
ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CISharedStorageAccessManagerStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CISharedStorageAccessManagerStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_ISharedStorageAccessManagerStatics <L"Windows.ApplicationModel.DataTransfer.ISharedStorageAccessManagerStatics">

DEFINE_IIDX(ISharedStorageAccessManagerStatics, "c6132ada-34b1-4849-bd5f-d09fee3158c5")

.comdef ISharedStorageAccessManagerStatics : public IInspectable

    AddFile proc :ptr, :ptr
    RedeemTokenForFileAsync proc :HSTRING, :ptr
    RemoveFile proc :HSTRING
   .ends

endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x10000
ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIStandardDataFormatsStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIStandardDataFormatsStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IStandardDataFormatsStatics <L"Windows.ApplicationModel.DataTransfer.IStandardDataFormatsStatics">

DEFINE_IIDX(IStandardDataFormatsStatics, "7ed681a1-a880-40c9-b4ed-0bee1e15f549")

.comdef IStandardDataFormatsStatics : public IInspectable

    get_Text proc :ptr
if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x10000
endif
    get_Uri proc :ptr
    get_Html proc :ptr
    get_Rtf proc :ptr
    get_Bitmap proc :ptr
    get_StorageItems proc :ptr
   .ends

endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x10000
ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIStandardDataFormatsStatics2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIStandardDataFormatsStatics2_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IStandardDataFormatsStatics2 <L"Windows.ApplicationModel.DataTransfer.IStandardDataFormatsStatics2">

DEFINE_IIDX(IStandardDataFormatsStatics2, "42a254f4-9d76-42e8-861b-47c25dd0cf71")

.comdef IStandardDataFormatsStatics2 : public IInspectable

    get_WebLink proc :ptr
    get_ApplicationLink proc :ptr
   .ends

endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x60000
ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIStandardDataFormatsStatics3_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CIStandardDataFormatsStatics3_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_IStandardDataFormatsStatics3 <L"Windows.ApplicationModel.DataTransfer.IStandardDataFormatsStatics3">

DEFINE_IIDX(IStandardDataFormatsStatics3, "3b57b069-01d4-474c-8b5f-bc8e27f38b21")

.comdef IStandardDataFormatsStatics3 : public IInspectable

    get_UserActivityJsonArray proc :ptr
   .ends

endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x10000
ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CITargetApplicationChosenEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CITargetApplicationChosenEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_ITargetApplicationChosenEventArgs <L"Windows.ApplicationModel.DataTransfer.ITargetApplicationChosenEventArgs">

DEFINE_IIDX(ITargetApplicationChosenEventArgs, "ca6fb8ac-2987-4ee3-9c54-d8afbcb86c1d")

.comdef ITargetApplicationChosenEventArgs : public IInspectable

    get_ApplicationName proc :ptr
   .ends

endif
endif

.endn
.endn
.endn

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x10000
define RuntimeClass_Windows_ApplicationModel_DataTransfer_Clipboard <L"Windows.ApplicationModel.DataTransfer.Clipboard">
endif
if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x70000
define RuntimeClass_Windows_ApplicationModel_DataTransfer_ClipboardContentOptions <L"Windows.ApplicationModel.DataTransfer.ClipboardContentOptions">
define RuntimeClass_Windows_ApplicationModel_DataTransfer_ClipboardHistoryChangedEventArgs <L"Windows.ApplicationModel.DataTransfer.ClipboardHistoryChangedEventArgs">
define RuntimeClass_Windows_ApplicationModel_DataTransfer_ClipboardHistoryItem <L"Windows.ApplicationModel.DataTransfer.ClipboardHistoryItem">
define RuntimeClass_Windows_ApplicationModel_DataTransfer_ClipboardHistoryItemsResult <L"Windows.ApplicationModel.DataTransfer.ClipboardHistoryItemsResult">
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x10000
define RuntimeClass_Windows_ApplicationModel_DataTransfer_DataPackage <L"Windows.ApplicationModel.DataTransfer.DataPackage">
define RuntimeClass_Windows_ApplicationModel_DataTransfer_DataPackagePropertySet <L"Windows.ApplicationModel.DataTransfer.DataPackagePropertySet">
define RuntimeClass_Windows_ApplicationModel_DataTransfer_DataPackagePropertySetView <L"Windows.ApplicationModel.DataTransfer.DataPackagePropertySetView">
define RuntimeClass_Windows_ApplicationModel_DataTransfer_DataPackageView <L"Windows.ApplicationModel.DataTransfer.DataPackageView">
define RuntimeClass_Windows_ApplicationModel_DataTransfer_DataProviderDeferral <L"Windows.ApplicationModel.DataTransfer.DataProviderDeferral">
define RuntimeClass_Windows_ApplicationModel_DataTransfer_DataProviderRequest <L"Windows.ApplicationModel.DataTransfer.DataProviderRequest">
define RuntimeClass_Windows_ApplicationModel_DataTransfer_DataRequest <L"Windows.ApplicationModel.DataTransfer.DataRequest">
define RuntimeClass_Windows_ApplicationModel_DataTransfer_DataRequestDeferral <L"Windows.ApplicationModel.DataTransfer.DataRequestDeferral">
define RuntimeClass_Windows_ApplicationModel_DataTransfer_DataRequestedEventArgs <L"Windows.ApplicationModel.DataTransfer.DataRequestedEventArgs">
define RuntimeClass_Windows_ApplicationModel_DataTransfer_DataTransferManager <L"Windows.ApplicationModel.DataTransfer.DataTransferManager">
define RuntimeClass_Windows_ApplicationModel_DataTransfer_HtmlFormatHelper <L"Windows.ApplicationModel.DataTransfer.HtmlFormatHelper">
define RuntimeClass_Windows_ApplicationModel_DataTransfer_OperationCompletedEventArgs <L"Windows.ApplicationModel.DataTransfer.OperationCompletedEventArgs">
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x40000
define RuntimeClass_Windows_ApplicationModel_DataTransfer_ShareCompletedEventArgs <L"Windows.ApplicationModel.DataTransfer.ShareCompletedEventArgs">
define RuntimeClass_Windows_ApplicationModel_DataTransfer_ShareProvider <L"Windows.ApplicationModel.DataTransfer.ShareProvider">
define RuntimeClass_Windows_ApplicationModel_DataTransfer_ShareProviderOperation <L"Windows.ApplicationModel.DataTransfer.ShareProviderOperation">
define RuntimeClass_Windows_ApplicationModel_DataTransfer_ShareProvidersRequestedEventArgs <L"Windows.ApplicationModel.DataTransfer.ShareProvidersRequestedEventArgs">
define RuntimeClass_Windows_ApplicationModel_DataTransfer_ShareTargetInfo <L"Windows.ApplicationModel.DataTransfer.ShareTargetInfo">
define RuntimeClass_Windows_ApplicationModel_DataTransfer_ShareUIOptions <L"Windows.ApplicationModel.DataTransfer.ShareUIOptions">
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x10000
define RuntimeClass_Windows_ApplicationModel_DataTransfer_SharedStorageAccessManager <L"Windows.ApplicationModel.DataTransfer.SharedStorageAccessManager">
define RuntimeClass_Windows_ApplicationModel_DataTransfer_StandardDataFormats <L"Windows.ApplicationModel.DataTransfer.StandardDataFormats">
define RuntimeClass_Windows_ApplicationModel_DataTransfer_TargetApplicationChosenEventArgs <L"Windows.ApplicationModel.DataTransfer.TargetApplicationChosenEventArgs">
endif

endif ; __windows2Eapplicationmodel2Edatatransfer_p_h__

endif ; __windows2Eapplicationmodel2Edatatransfer_h__
