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

ifndef __windows2Eapplicationmodel2Estore_h__
define __windows2Eapplicationmodel2Estore_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include Windows.Storage.inc
include windows.foundation.collections.inc

ifndef ____FIIterator_1_Windows__CApplicationModel__CStore__CUnfulfilledConsumable_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CApplicationModel__CStore__CUnfulfilledConsumable_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterator_1_Windows__CApplicationModel__CStore__CUnfulfilledConsumable,"cb77cf2e-ef57-5256-9753-214baada2301")

.comdef __FIIterator_1_Windows__CApplicationModel__CStore__CUnfulfilledConsumable : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CApplicationModel__CStore__CUnfulfilledConsumable_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CApplicationModel__CStore__CUnfulfilledConsumable_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CApplicationModel__CStore__CUnfulfilledConsumable, "2f4d1483-dd86-5fdb-8c44-06c98844bf3d")

.comdef __FIIterable_1_Windows__CApplicationModel__CStore__CUnfulfilledConsumable : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIKeyValuePair_2_HSTRING_Windows__CApplicationModel__CStore__CProductLicense_INTERFACE_DEFINED__
define ____FIKeyValuePair_2_HSTRING_Windows__CApplicationModel__CStore__CProductLicense_INTERFACE_DEFINED__
DEFINE_IIDX(__FIKeyValuePair_2_HSTRING_Windows__CApplicationModel__CStore__CProductLicense, "ff71c38c-3e6e-5e60-994b-9201436deed1")

.comdef __FIKeyValuePair_2_HSTRING_Windows__CApplicationModel__CStore__CProductLicense : public IInspectable

    get_Key		proc :ptr
    get_Value		proc :ptr
   .ends

endif

ifndef ____FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CApplicationModel__CStore__CProductLicense_INTERFACE_DEFINED__
define ____FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CApplicationModel__CStore__CProductLicense_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CApplicationModel__CStore__CProductLicense, "3f3c06e6-593f-557a-8e3c-45513ac01f7c")

.comdef __FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CApplicationModel__CStore__CProductLicense : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CApplicationModel__CStore__CProductLicense_INTERFACE_DEFINED__
define ____FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CApplicationModel__CStore__CProductLicense_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CApplicationModel__CStore__CProductLicense, "ffe05002-6e65-5001-a752-9b27ed3e2839")

.comdef __FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CApplicationModel__CStore__CProductLicense : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIKeyValuePair_2_HSTRING_Windows__CApplicationModel__CStore__CProductListing_INTERFACE_DEFINED__
define ____FIKeyValuePair_2_HSTRING_Windows__CApplicationModel__CStore__CProductListing_INTERFACE_DEFINED__
DEFINE_IIDX(__FIKeyValuePair_2_HSTRING_Windows__CApplicationModel__CStore__CProductListing, "61a02c5d-4007-573e-8a01-0259714927df")

.comdef __FIKeyValuePair_2_HSTRING_Windows__CApplicationModel__CStore__CProductListing : public IInspectable

    get_Key		proc :ptr
    get_Value		proc :ptr
   .ends

endif

ifndef ____FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CApplicationModel__CStore__CProductListing_INTERFACE_DEFINED__
define ____FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CApplicationModel__CStore__CProductListing_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CApplicationModel__CStore__CProductListing, "142a6937-1ae1-5aad-8ada-9a8ee034e4eb")

.comdef __FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CApplicationModel__CStore__CProductListing : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CApplicationModel__CStore__CProductListing_INTERFACE_DEFINED__
define ____FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CApplicationModel__CStore__CProductListing_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CApplicationModel__CStore__CProductListing, "3a7d9a2f-2a82-59f8-bd7c-d691ca169863")

.comdef __FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CApplicationModel__CStore__CProductListing : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIMapView_2_HSTRING_Windows__CApplicationModel__CStore__CProductLicense_INTERFACE_DEFINED__
define ____FIMapView_2_HSTRING_Windows__CApplicationModel__CStore__CProductLicense_INTERFACE_DEFINED__
DEFINE_IIDX(__FIMapView_2_HSTRING_Windows__CApplicationModel__CStore__CProductLicense, "d6434f65-dd84-534c-b579-cc10d69ec30a")

.comdef __FIMapView_2_HSTRING_Windows__CApplicationModel__CStore__CProductLicense : public IInspectable

    Lookup		proc :HSTRING, :ptr
    get_Size		proc :ptr
    HasKey		proc :HSTRING, :ptr
    Split		proc :ptr, :ptr
   .ends

endif

ifndef ____FIMapView_2_HSTRING_Windows__CApplicationModel__CStore__CProductListing_INTERFACE_DEFINED__
define ____FIMapView_2_HSTRING_Windows__CApplicationModel__CStore__CProductListing_INTERFACE_DEFINED__
DEFINE_IIDX(__FIMapView_2_HSTRING_Windows__CApplicationModel__CStore__CProductListing, "3206de83-efbe-5791-a487-2ac974206ec6")

.comdef __FIMapView_2_HSTRING_Windows__CApplicationModel__CStore__CProductListing : public IInspectable

    Lookup		proc :HSTRING, :ptr
    get_Size		proc :ptr
    HasKey		proc :HSTRING, :ptr
    Split		proc :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CApplicationModel__CStore__CUnfulfilledConsumable_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CApplicationModel__CStore__CUnfulfilledConsumable_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CApplicationModel__CStore__CUnfulfilledConsumable, "f0ae5962-e039-5105-bcc5-9b552f13b102")

.comdef __FIVectorView_1_Windows__CApplicationModel__CStore__CUnfulfilledConsumable : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CStore__CFulfillmentResult_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CStore__CFulfillmentResult_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CStore__CFulfillmentResult, "8775acc9-b9ae-5cce-895c-971bf9270892")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CStore__CFulfillmentResult : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CApplicationModel__CStore__CFulfillmentResult_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CApplicationModel__CStore__CFulfillmentResult_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CApplicationModel__CStore__CFulfillmentResult, "5c8531ac-5d8d-5e07-b6ee-7cab96930e8a")

.comdef __FIAsyncOperation_1_Windows__CApplicationModel__CStore__CFulfillmentResult : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CStore__CListingInformation_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CStore__CListingInformation_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CStore__CListingInformation, "fdf83922-762e-57dc-b721-c72ee568fd96")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CStore__CListingInformation : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CApplicationModel__CStore__CListingInformation_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CApplicationModel__CStore__CListingInformation_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CApplicationModel__CStore__CListingInformation, "161600f7-6d4f-500d-93a8-09ad6b5ac4ab")

.comdef __FIAsyncOperation_1_Windows__CApplicationModel__CStore__CListingInformation : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CStore__CPurchaseResults_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CStore__CPurchaseResults_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CStore__CPurchaseResults, "24b6922a-fdb1-5003-ae89-c8bf16ca0143")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CApplicationModel__CStore__CPurchaseResults : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CApplicationModel__CStore__CPurchaseResults_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CApplicationModel__CStore__CPurchaseResults_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CApplicationModel__CStore__CPurchaseResults, "241f6b10-6af6-5164-85eb-bae6bdae0be8")

.comdef __FIAsyncOperation_1_Windows__CApplicationModel__CStore__CPurchaseResults : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CApplicationModel__CStore__CUnfulfilledConsumable_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CApplicationModel__CStore__CUnfulfilledConsumable_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CApplicationModel__CStore__CUnfulfilledConsumable, "0451fe11-6b50-54c1-b765-d946b1d5c88b")

.comdef __FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CApplicationModel__CStore__CUnfulfilledConsumable : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1___FIVectorView_1_Windows__CApplicationModel__CStore__CUnfulfilledConsumable_INTERFACE_DEFINED__
define ____FIAsyncOperation_1___FIVectorView_1_Windows__CApplicationModel__CStore__CUnfulfilledConsumable_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1___FIVectorView_1_Windows__CApplicationModel__CStore__CUnfulfilledConsumable, "f1cd679a-3a8f-5e1b-82f1-f2fd0916ca3f")

.comdef __FIAsyncOperation_1___FIVectorView_1_Windows__CApplicationModel__CStore__CUnfulfilledConsumable : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

.namespace Windows
.namespace ApplicationModel
.namespace Store

.enum ProductPurchaseStatus {
    ProductPurchaseStatus_Succeeded	= 0,
    ProductPurchaseStatus_AlreadyPurchased	= 1,
    ProductPurchaseStatus_NotFulfilled	= 2,
    ProductPurchaseStatus_NotPurchased	= 3
    }

.enum ProductType {
    ProductType_Unknown = 0,
    ProductType_Durable = 1,
    ProductType_Consumable	= 2
    }

.enum FulfillmentResult {
    FulfillmentResult_Succeeded = 0,
    FulfillmentResult_NothingToFulfill	= 1,
    FulfillmentResult_PurchasePending	= 2,
    FulfillmentResult_PurchaseReverted	= 3,
    FulfillmentResult_ServerError	= 4
    }

ifndef ____x_ABI_CWindows_CApplicationModel_CStore_CILicenseChangedEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CStore_CILicenseChangedEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(ILicenseChangedEventHandler, "D4A50255-1369-4C36-832F-6F2D88E3659B")

.comdef ILicenseChangedEventHandler : public IUnknown

    _Invoke		proc
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CStore_CICurrentApp_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CStore_CICurrentApp_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Store_ICurrentApp <L"Windows.ApplicationModel.Store.ICurrentApp">
DEFINE_IIDX(ICurrentApp, "D52DC065-DA3F-4685-995E-9B482EB5E603")

.comdef ICurrentApp : public IInspectable

    get_LicenseInformation proc :ptr
    get_LinkUri		proc :ptr
    get_AppId		proc :ptr
    RequestAppPurchaseAsync proc :boolean, :ptr
    RequestProductPurchaseAsync proc :HSTRING, :boolean, :ptr
    LoadListingInformationAsync proc :ptr
    GetAppReceiptAsync	proc :ptr
    GetProductReceiptAsync proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CStore_CICurrentAppWithConsumables_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CStore_CICurrentAppWithConsumables_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Store_ICurrentAppWithConsumables <L"Windows.ApplicationModel.Store.ICurrentAppWithConsumables">
DEFINE_IIDX(ICurrentAppWithConsumables, "844E0071-9E4F-4F79-995A-5F91172E6CEF")

.comdef ICurrentAppWithConsumables : public IInspectable

    ReportConsumableFulfillmentAsync proc :HSTRING, :GUID, :ptr
    RequestProductPurchaseWithResultsAsync proc :HSTRING, :ptr
    RequestProductPurchaseWithDisplayPropertiesAsync proc :HSTRING, :HSTRING, :ptr, :ptr
    GetUnfulfilledConsumablesAsync proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CStore_CICurrentAppSimulator_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CStore_CICurrentAppSimulator_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Store_ICurrentAppSimulator <L"Windows.ApplicationModel.Store.ICurrentAppSimulator">
DEFINE_IIDX(ICurrentAppSimulator, "F17F9DB1-74CD-4787-9787-19866E9A5559")

.comdef ICurrentAppSimulator : public IInspectable

    get_LicenseInformation proc :ptr
    get_LinkUri		proc :ptr
    get_AppId		proc :ptr
    RequestAppPurchaseAsync proc :boolean, :ptr
    RequestProductPurchaseAsync proc :HSTRING, :boolean, :ptr
    LoadListingInformationAsync proc :ptr
    GetAppReceiptAsync	proc :ptr
    GetProductReceiptAsync proc :HSTRING, :ptr
    ReloadSimulatorAsync proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CStore_CICurrentAppSimulatorWithConsumables_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CStore_CICurrentAppSimulatorWithConsumables_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Store_ICurrentAppSimulatorWithConsumables <L"Windows.ApplicationModel.Store.ICurrentAppSimulatorWithConsumables">
DEFINE_IIDX(ICurrentAppSimulatorWithConsumables, "4E51F0AB-20E7-4412-9B85-59BB78388667")

.comdef __x_ABI_CWindows_CApplicationModel_CStore_CICurrentAppSimulatorWithConsumables : public IInspectable

    ReportConsumableFulfillmentAsync proc :HSTRING, :GUID, :ptr
    RequestProductPurchaseWithResultsAsync proc :HSTRING, :ptr
    RequestProductPurchaseWithDisplayPropertiesAsync proc :HSTRING, :HSTRING, :ptr, :ptr
    GetUnfulfilledConsumablesAsync proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CStore_CIPurchaseResults_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CStore_CIPurchaseResults_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Store_IPurchaseResults <L"Windows.ApplicationModel.Store.IPurchaseResults">
DEFINE_IIDX(IPurchaseResults, "ED50B37E-8656-4F65-B8C8-AC7E0CB1A1C2")

.comdef IPurchaseResults : public IInspectable

    get_Status		proc :ptr
    get_TransactionId	proc :ptr
    get_ReceiptXml	proc :ptr
    get_OfferId		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CStore_CILicenseInformation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CStore_CILicenseInformation_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Store_ILicenseInformation <L"Windows.ApplicationModel.Store.ILicenseInformation">
DEFINE_IIDX(ILicenseInformation, "8EB7DC30-F170-4ED5-8E21-1516DA3FD367")

.comdef ILicenseInformation : public IInspectable

    get_ProductLicenses proc :ptr
    get_IsActive	proc :ptr
    get_IsTrial		proc :ptr
    get_ExpirationDate	proc :ptr
    add_LicenseChanged	proc :ptr, :ptr
    remove_LicenseChanged proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CStore_CIProductLicense_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CStore_CIProductLicense_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Store_IProductLicense <L"Windows.ApplicationModel.Store.IProductLicense">
DEFINE_IIDX(IProductLicense, "363308C7-2BCF-4C0E-8F2F-E808AAA8F99D")

.comdef IProductLicense : public IInspectable

    get_ProductId	proc :ptr
    get_IsActive	proc :ptr
    get_ExpirationDate	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CStore_CIListingInformation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CStore_CIListingInformation_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Store_IListingInformation <L"Windows.ApplicationModel.Store.IListingInformation">
DEFINE_IIDX(IListingInformation, "588B4ABF-BC74-4383-B78C-99606323DECE")

.comdef IListingInformation : public IInspectable

    get_CurrentMarket	proc :ptr
    get_Description	proc :ptr
    get_ProductListings proc :ptr
    get_FormattedPrice	proc :ptr
    get_Name		proc :ptr
    get_AgeRating	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CStore_CIProductListing_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CStore_CIProductListing_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Store_IProductListing <L"Windows.ApplicationModel.Store.IProductListing">
DEFINE_IIDX(IProductListing, "45A7D6AD-C750-4D9C-947C-B00DCBF9E9C2")

.comdef IProductListing : public IInspectable

    get_ProductId	proc :ptr
    get_FormattedPrice	proc :ptr
    get_Name		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CStore_CIProductListingWithConsumables_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CStore_CIProductListingWithConsumables_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Store_IProductListingWithConsumables <L"Windows.ApplicationModel.Store.IProductListingWithConsumables">
DEFINE_IIDX(IProductListingWithConsumables, "EB9E9790-8F6B-481F-93A7-5C3A63068149")

.comdef IProductListingWithConsumables : public IInspectable

    get_ProductType	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CStore_CIUnfulfilledConsumable_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CStore_CIUnfulfilledConsumable_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Store_IUnfulfilledConsumable <L"Windows.ApplicationModel.Store.IUnfulfilledConsumable">
DEFINE_IIDX(IUnfulfilledConsumable, "2DF7FBBB-1CDD-4CB8-A014-7B9CF8986927")

.comdef IUnfulfilledConsumable : public IInspectable

    get_ProductId	proc :ptr
    get_TransactionId	proc :ptr
    get_OfferId		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CStore_CIProductPurchaseDisplayProperties_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CStore_CIProductPurchaseDisplayProperties_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Store_IProductPurchaseDisplayProperties <L"Windows.ApplicationModel.Store.IProductPurchaseDisplayProperties">
DEFINE_IIDX(IProductPurchaseDisplayProperties, "D70B7420-BC92-401B-A809-C9B2E5DBBDAF")

.comdef IProductPurchaseDisplayProperties : public IInspectable

    get_Name		proc :ptr
    put_Name		proc :HSTRING
    get_Description	proc :ptr
    put_Description	proc :HSTRING
    get_Image		proc :ptr
    put_Image		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CStore_CIProductPurchaseDisplayPropertiesFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CStore_CIProductPurchaseDisplayPropertiesFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Store_IProductPurchaseDisplayPropertiesFactory <L"Windows.ApplicationModel.Store.IProductPurchaseDisplayPropertiesFactory">
DEFINE_IIDX(IProductPurchaseDisplayPropertiesFactory, "6F491DF4-32D6-4B40-B474-B83038A4D9CF")

.comdef IProductPurchaseDisplayPropertiesFactory : public IInspectable

    CreateProductPurchaseDisplayProperties proc :HSTRING, :ptr
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_ApplicationModel_Store_LicenseInformation_DEFINED
define RUNTIMECLASS_Windows_ApplicationModel_Store_LicenseInformation_DEFINED
define RuntimeClass_Windows_ApplicationModel_Store_LicenseInformation <L"Windows.ApplicationModel.Store.LicenseInformation">
endif
ifndef RUNTIMECLASS_Windows_ApplicationModel_Store_ListingInformation_DEFINED
define RUNTIMECLASS_Windows_ApplicationModel_Store_ListingInformation_DEFINED
define RuntimeClass_Windows_ApplicationModel_Store_ListingInformation <L"Windows.ApplicationModel.Store.ListingInformation">
endif
ifndef RUNTIMECLASS_Windows_ApplicationModel_Store_PurchaseResults_DEFINED
define RUNTIMECLASS_Windows_ApplicationModel_Store_PurchaseResults_DEFINED
define RuntimeClass_Windows_ApplicationModel_Store_PurchaseResults <L"Windows.ApplicationModel.Store.PurchaseResults">
endif
ifndef RUNTIMECLASS_Windows_ApplicationModel_Store_ProductPurchaseDisplayProperties_DEFINED
define RUNTIMECLASS_Windows_ApplicationModel_Store_ProductPurchaseDisplayProperties_DEFINED
define RuntimeClass_Windows_ApplicationModel_Store_ProductPurchaseDisplayProperties <L"Windows.ApplicationModel.Store.ProductPurchaseDisplayProperties">
endif
ifndef RUNTIMECLASS_Windows_ApplicationModel_Store_UnfulfilledConsumable_DEFINED
define RUNTIMECLASS_Windows_ApplicationModel_Store_UnfulfilledConsumable_DEFINED
define RuntimeClass_Windows_ApplicationModel_Store_UnfulfilledConsumable <L"Windows.ApplicationModel.Store.UnfulfilledConsumable">
endif
ifndef RUNTIMECLASS_Windows_ApplicationModel_Store_ProductLicense_DEFINED
define RUNTIMECLASS_Windows_ApplicationModel_Store_ProductLicense_DEFINED
define RuntimeClass_Windows_ApplicationModel_Store_ProductLicense <L"Windows.ApplicationModel.Store.ProductLicense">
endif
ifndef RUNTIMECLASS_Windows_ApplicationModel_Store_ProductListing_DEFINED
define RUNTIMECLASS_Windows_ApplicationModel_Store_ProductListing_DEFINED
define RuntimeClass_Windows_ApplicationModel_Store_ProductListing <L"Windows.ApplicationModel.Store.ProductListing">
endif
ifndef RUNTIMECLASS_Windows_ApplicationModel_Store_CurrentApp_DEFINED
define RUNTIMECLASS_Windows_ApplicationModel_Store_CurrentApp_DEFINED
define RuntimeClass_Windows_ApplicationModel_Store_CurrentApp <L"Windows.ApplicationModel.Store.CurrentApp">
endif
ifndef RUNTIMECLASS_Windows_ApplicationModel_Store_CurrentAppSimulator_DEFINED
define RUNTIMECLASS_Windows_ApplicationModel_Store_CurrentAppSimulator_DEFINED
define RuntimeClass_Windows_ApplicationModel_Store_CurrentAppSimulator <L"Windows.ApplicationModel.Store.CurrentAppSimulator">
endif

endif

