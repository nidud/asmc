ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Eapplicationmodel2Edatatransfer2Esharetarget_h__
define __windows2Eapplicationmodel2Edatatransfer2Esharetarget_h__
ifndef __windows2Efoundation_h__
include Windows.Foundation.inc
endif
include Windows.ApplicationModel.DataTransfer.inc

.namespace Windows
.namespace ApplicationModel
.namespace DataTransfer
.namespace ShareTarget

ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CShareTarget_CIQuickLink_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CShareTarget_CIQuickLink_INTERFACE_DEFINED__

DEFINE_IIDX(IQuickLink, "603E4308-F0BE-4ADC-ACC9-8B27AB9CF556")

.comdef IQuickLink : public IInspectable

    get_Title		proc :ptr
    put_Title		proc :HSTRING
    get_Thumbnail	proc :ptr
    put_Thumbnail	proc :ptr
    get_Id		proc :ptr
    put_Id		proc :HSTRING
    get_SupportedDataFormats proc :ptr
    get_SupportedFileTypes proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CShareTarget_CIShareOperation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CShareTarget_CIShareOperation_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_ShareTarget_IShareOperation <L"Windows.ApplicationModel.DataTransfer.ShareTarget.IShareOperation">

DEFINE_IIDX(IShareOperation, "2246BAB8-D0F8-41C1-A82A-4137DB6504FB")

.comdef IShareOperation : public IInspectable

    get_Data		proc :ptr
    get_QuickLinkId	proc :ptr
    RemoveThisQuickLink proc
    ReportStarted	proc
    ReportDataRetrieved proc
    ReportSubmittedBackgroundTask proc
    ReportCompletedWithQuickLink proc :ptr
    ReportCompleted	proc
    ReportError		proc :HSTRING
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CShareTarget_CIShareOperation2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CDataTransfer_CShareTarget_CIShareOperation2_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_DataTransfer_ShareTarget_IShareOperation2 <L"Windows.ApplicationModel.DataTransfer.ShareTarget.IShareOperation2">

DEFINE_IIDX(IShareOperation2, "0FFB97C1-9778-4A09-8E5B-CB5E482D0555")

.comdef IShareOperation2 : public IInspectable

    DismissUI		proc
   .ends

endif

.endn
.endn
.endn
.endn

define RuntimeClass_Windows_ApplicationModel_DataTransfer_ShareTarget_QuickLink <L"Windows.ApplicationModel.DataTransfer.ShareTarget.QuickLink">
define RuntimeClass_Windows_ApplicationModel_DataTransfer_ShareTarget_ShareOperation <L"Windows.ApplicationModel.DataTransfer.ShareTarget.ShareOperation">

endif
