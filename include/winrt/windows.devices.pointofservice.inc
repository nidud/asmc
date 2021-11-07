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

ifndef __windows2Edevices2Epointofservice_h__
define __windows2Edevices2Epointofservice_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include Windows.Storage.Streams.inc
include windows.foundation.collections.inc

ifndef ____FIEventHandler_1_Windows__CDevices__CPointOfService__CClaimedBarcodeScanner_INTERFACE_DEFINED__
define ____FIEventHandler_1_Windows__CDevices__CPointOfService__CClaimedBarcodeScanner_INTERFACE_DEFINED__
DEFINE_IIDX(__FIEventHandler_1_Windows__CDevices__CPointOfService__CClaimedBarcodeScanner, "c0acd2ae-5b55-588d-811b-be33a4fdda57")

.comdef __FIEventHandler_1_Windows__CDevices__CPointOfService__CClaimedBarcodeScanner : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FIEventHandler_1_Windows__CDevices__CPointOfService__CClaimedMagneticStripeReader_INTERFACE_DEFINED__
define ____FIEventHandler_1_Windows__CDevices__CPointOfService__CClaimedMagneticStripeReader_INTERFACE_DEFINED__
DEFINE_IIDX(__FIEventHandler_1_Windows__CDevices__CPointOfService__CClaimedMagneticStripeReader, "8006bf5d-0895-5b8c-808a-6bb8f26794fa")

.comdef __FIEventHandler_1_Windows__CDevices__CPointOfService__CClaimedMagneticStripeReader : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CDevices__CPointOfService__CBarcodeScanner_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CDevices__CPointOfService__CBarcodeScanner_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CDevices__CPointOfService__CBarcodeScanner, "8d8abf39-99dd-50a4-aa7c-2f7301b5ca9c")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CDevices__CPointOfService__CBarcodeScanner : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CDevices__CPointOfService__CBarcodeScanner_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CDevices__CPointOfService__CBarcodeScanner_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CDevices__CPointOfService__CBarcodeScanner, "616494dd-30a2-523f-b1a2-9a1174de3b17")

.comdef __FIAsyncOperation_1_Windows__CDevices__CPointOfService__CBarcodeScanner : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CDevices__CPointOfService__CClaimedBarcodeScanner_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CDevices__CPointOfService__CClaimedBarcodeScanner_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CDevices__CPointOfService__CClaimedBarcodeScanner, "ff72ba2d-f3c4-5abe-bbce-53150449b637")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CDevices__CPointOfService__CClaimedBarcodeScanner : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CDevices__CPointOfService__CClaimedBarcodeScanner_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CDevices__CPointOfService__CClaimedBarcodeScanner_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CDevices__CPointOfService__CClaimedBarcodeScanner, "c9704809-a0e2-5e1d-87cf-75a1d49d7bdb")

.comdef __FIAsyncOperation_1_Windows__CDevices__CPointOfService__CClaimedBarcodeScanner : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CDevices__CPointOfService__CClaimedMagneticStripeReader_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CDevices__CPointOfService__CClaimedMagneticStripeReader_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CDevices__CPointOfService__CClaimedMagneticStripeReader, "946c2d64-22d4-552d-abfb-9eb341bd67f3")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CDevices__CPointOfService__CClaimedMagneticStripeReader : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CDevices__CPointOfService__CClaimedMagneticStripeReader_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CDevices__CPointOfService__CClaimedMagneticStripeReader_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CDevices__CPointOfService__CClaimedMagneticStripeReader, "41630bd4-f45a-590d-8a4e-f70c9e49ad01")

.comdef __FIAsyncOperation_1_Windows__CDevices__CPointOfService__CClaimedMagneticStripeReader : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CDevices__CPointOfService__CMagneticStripeReader_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CDevices__CPointOfService__CMagneticStripeReader_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CDevices__CPointOfService__CMagneticStripeReader, "32c55f7b-8ee3-555d-998b-78c98aa9627b")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CDevices__CPointOfService__CMagneticStripeReader : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CDevices__CPointOfService__CMagneticStripeReader_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CDevices__CPointOfService__CMagneticStripeReader_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CDevices__CPointOfService__CMagneticStripeReader, "93726e09-817c-5f33-bee4-090de7074f19")

.comdef __FIAsyncOperation_1_Windows__CDevices__CPointOfService__CMagneticStripeReader : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CDevices__CPointOfService__CBarcodeScanner_Windows__CDevices__CPointOfService__CBarcodeScannerStatusUpdatedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CDevices__CPointOfService__CBarcodeScanner_Windows__CDevices__CPointOfService__CBarcodeScannerStatusUpdatedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CDevices__CPointOfService__CBarcodeScanner_Windows__CDevices__CPointOfService__CBarcodeScannerStatusUpdatedEventArgs, "cfc8a053-f611-521a-8ab0-a460e1f7164d")

.comdef __FITypedEventHandler_2_Windows__CDevices__CPointOfService__CBarcodeScanner_Windows__CDevices__CPointOfService__CBarcodeScannerStatusUpdatedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CDevices__CPointOfService__CClaimedBarcodeScanner_Windows__CDevices__CPointOfService__CBarcodeScannerDataReceivedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CDevices__CPointOfService__CClaimedBarcodeScanner_Windows__CDevices__CPointOfService__CBarcodeScannerDataReceivedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CDevices__CPointOfService__CClaimedBarcodeScanner_Windows__CDevices__CPointOfService__CBarcodeScannerDataReceivedEventArgs, "4f64e49a-bd8c-549d-970c-a5a250bd27ca")

.comdef __FITypedEventHandler_2_Windows__CDevices__CPointOfService__CClaimedBarcodeScanner_Windows__CDevices__CPointOfService__CBarcodeScannerDataReceivedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CDevices__CPointOfService__CClaimedBarcodeScanner_Windows__CDevices__CPointOfService__CBarcodeScannerErrorOccurredEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CDevices__CPointOfService__CClaimedBarcodeScanner_Windows__CDevices__CPointOfService__CBarcodeScannerErrorOccurredEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CDevices__CPointOfService__CClaimedBarcodeScanner_Windows__CDevices__CPointOfService__CBarcodeScannerErrorOccurredEventArgs, "ba42ff49-de12-5406-979e-06c45ca2d5a4")

.comdef __FITypedEventHandler_2_Windows__CDevices__CPointOfService__CClaimedBarcodeScanner_Windows__CDevices__CPointOfService__CBarcodeScannerErrorOccurredEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CDevices__CPointOfService__CClaimedBarcodeScanner_Windows__CDevices__CPointOfService__CBarcodeScannerImagePreviewReceivedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CDevices__CPointOfService__CClaimedBarcodeScanner_Windows__CDevices__CPointOfService__CBarcodeScannerImagePreviewReceivedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CDevices__CPointOfService__CClaimedBarcodeScanner_Windows__CDevices__CPointOfService__CBarcodeScannerImagePreviewReceivedEventArgs, "fba116af-2a39-516f-a579-cc3eaf36a34b")

.comdef __FITypedEventHandler_2_Windows__CDevices__CPointOfService__CClaimedBarcodeScanner_Windows__CDevices__CPointOfService__CBarcodeScannerImagePreviewReceivedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CDevices__CPointOfService__CClaimedMagneticStripeReader_Windows__CDevices__CPointOfService__CMagneticStripeReaderAamvaCardDataReceivedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CDevices__CPointOfService__CClaimedMagneticStripeReader_Windows__CDevices__CPointOfService__CMagneticStripeReaderAamvaCardDataReceivedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CDevices__CPointOfService__CClaimedMagneticStripeReader_Windows__CDevices__CPointOfService__CMagneticStripeReaderAamvaCardDataReceivedEventArgs, "29e08f92-c3ab-57ea-aaba-789f792d7a46")

.comdef __FITypedEventHandler_2_Windows__CDevices__CPointOfService__CClaimedMagneticStripeReader_Windows__CDevices__CPointOfService__CMagneticStripeReaderAamvaCardDataReceivedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CDevices__CPointOfService__CClaimedMagneticStripeReader_Windows__CDevices__CPointOfService__CMagneticStripeReaderBankCardDataReceivedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CDevices__CPointOfService__CClaimedMagneticStripeReader_Windows__CDevices__CPointOfService__CMagneticStripeReaderBankCardDataReceivedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CDevices__CPointOfService__CClaimedMagneticStripeReader_Windows__CDevices__CPointOfService__CMagneticStripeReaderBankCardDataReceivedEventArgs, "6a41d015-245e-51ba-bd6c-44775d70bfa2")

.comdef __FITypedEventHandler_2_Windows__CDevices__CPointOfService__CClaimedMagneticStripeReader_Windows__CDevices__CPointOfService__CMagneticStripeReaderBankCardDataReceivedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CDevices__CPointOfService__CClaimedMagneticStripeReader_Windows__CDevices__CPointOfService__CMagneticStripeReaderErrorOccurredEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CDevices__CPointOfService__CClaimedMagneticStripeReader_Windows__CDevices__CPointOfService__CMagneticStripeReaderErrorOccurredEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CDevices__CPointOfService__CClaimedMagneticStripeReader_Windows__CDevices__CPointOfService__CMagneticStripeReaderErrorOccurredEventArgs, "1464a1e6-9d92-547e-b4ac-f255ac85f950")

.comdef __FITypedEventHandler_2_Windows__CDevices__CPointOfService__CClaimedMagneticStripeReader_Windows__CDevices__CPointOfService__CMagneticStripeReaderErrorOccurredEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CDevices__CPointOfService__CClaimedMagneticStripeReader_Windows__CDevices__CPointOfService__CMagneticStripeReaderVendorSpecificCardDataReceivedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CDevices__CPointOfService__CClaimedMagneticStripeReader_Windows__CDevices__CPointOfService__CMagneticStripeReaderVendorSpecificCardDataReceivedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CDevices__CPointOfService__CClaimedMagneticStripeReader_Windows__CDevices__CPointOfService__CMagneticStripeReaderVendorSpecificCardDataReceivedEventArgs, "959124ba-ee44-560c-8183-61c6a2308d8f")

.comdef __FITypedEventHandler_2_Windows__CDevices__CPointOfService__CClaimedMagneticStripeReader_Windows__CDevices__CPointOfService__CMagneticStripeReaderVendorSpecificCardDataReceivedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CDevices__CPointOfService__CMagneticStripeReader_Windows__CDevices__CPointOfService__CMagneticStripeReaderStatusUpdatedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CDevices__CPointOfService__CMagneticStripeReader_Windows__CDevices__CPointOfService__CMagneticStripeReaderStatusUpdatedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CDevices__CPointOfService__CMagneticStripeReader_Windows__CDevices__CPointOfService__CMagneticStripeReaderStatusUpdatedEventArgs, "722d8bfa-e10e-548d-af29-28dd906f6fc9")

.comdef __FITypedEventHandler_2_Windows__CDevices__CPointOfService__CMagneticStripeReader_Windows__CDevices__CPointOfService__CMagneticStripeReaderStatusUpdatedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

.namespace Windows
.namespace Devices
.namespace PointOfService

.enum UnifiedPosErrorSeverity {
    UnifiedPosErrorSeverity_UnknownErrorSeverity	= 0,
    UnifiedPosErrorSeverity_Warning	= 1,
    UnifiedPosErrorSeverity_Recoverable = 2,
    UnifiedPosErrorSeverity_Unrecoverable	= 3,
    UnifiedPosErrorSeverity_AssistanceRequired	= 4,
    UnifiedPosErrorSeverity_Fatal	= 5
    }

.enum UnifiedPosPowerReportingType {
    UnifiedPosPowerReportingType_UnknownPowerReportingType	= 0,
    UnifiedPosPowerReportingType_Standard	= 1,
    UnifiedPosPowerReportingType_Advanced	= 2
    }

.enum UnifiedPosHealthCheckLevel {
    UnifiedPosHealthCheckLevel_UnknownHealthCheckLevel	= 0,
    UnifiedPosHealthCheckLevel_POSInternal	= 1,
    UnifiedPosHealthCheckLevel_External = 2,
    UnifiedPosHealthCheckLevel_Interactive	= 3
    }

.enum UnifiedPosErrorReason {
    UnifiedPosErrorReason_UnknownErrorReason	= 0,
    UnifiedPosErrorReason_NoService	= 1,
    UnifiedPosErrorReason_Disabled	= 2,
    UnifiedPosErrorReason_Illegal	= 3,
    UnifiedPosErrorReason_NoHardware	= 4,
    UnifiedPosErrorReason_Closed	= 5,
    UnifiedPosErrorReason_Offline	= 6,
    UnifiedPosErrorReason_Failure	= 7,
    UnifiedPosErrorReason_Timeout	= 8,
    UnifiedPosErrorReason_Busy	= 9,
    UnifiedPosErrorReason_Extended	= 10
    }

.enum MagneticStripeReaderAuthenticationLevel {
    MagneticStripeReaderAuthenticationLevel_NotSupported	= 0,
    MagneticStripeReaderAuthenticationLevel_Optional	= 1,
    MagneticStripeReaderAuthenticationLevel_Required	= 2
    }

.enum BarcodeScannerStatus {
    BarcodeScannerStatus_Online = 0,
    BarcodeScannerStatus_Off	= 1,
    BarcodeScannerStatus_Offline	= 2,
    BarcodeScannerStatus_OffOrOffline	= 3,
    BarcodeScannerStatus_Extended	= 4
    }

.enum MagneticStripeReaderStatus {
    MagneticStripeReaderStatus_Unauthenticated	= 0,
    MagneticStripeReaderStatus_Authenticated	= 1,
    MagneticStripeReaderStatus_Extended = 2
    }

.enum MagneticStripeReaderAuthenticationProtocol {
    MagneticStripeReaderAuthenticationProtocol_None	= 0,
    MagneticStripeReaderAuthenticationProtocol_ChallengeResponse	= 1
    }

.enum MagneticStripeReaderTrackIds {
    MagneticStripeReaderTrackIds_None	= 0,
    MagneticStripeReaderTrackIds_Track1 = 1,
    MagneticStripeReaderTrackIds_Track2 = 2,
    MagneticStripeReaderTrackIds_Track3 = 4,
    MagneticStripeReaderTrackIds_Track4 = 8
    }

.enum MagneticStripeReaderErrorReportingType {
    MagneticStripeReaderErrorReportingType_CardLevel	= 0,
    MagneticStripeReaderErrorReportingType_TrackLevel	= 1
    }

.enum MagneticStripeReaderTrackErrorType {
    MagneticStripeReaderTrackErrorType_None	= 0,
    MagneticStripeReaderTrackErrorType_StartSentinelError	= 1,
    MagneticStripeReaderTrackErrorType_EndSentinelError = 2,
    MagneticStripeReaderTrackErrorType_ParityError	= 3,
    MagneticStripeReaderTrackErrorType_LrcError = 4,
    MagneticStripeReaderTrackErrorType_Unknown	= -1
    }

ifndef ____x_ABI_CWindows_CDevices_CPointOfService_CIUnifiedPosErrorData_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CPointOfService_CIUnifiedPosErrorData_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_PointOfService_IUnifiedPosErrorData <L"Windows.Devices.PointOfService.IUnifiedPosErrorData">
DEFINE_IIDX(IUnifiedPosErrorData, "2B998C3A-555C-4889-8ED8-C599BB3A712A")

.comdef IUnifiedPosErrorData : public IInspectable

    get_Message		proc :ptr
    get_Severity	proc :ptr
    get_Reason		proc :ptr
    get_ExtendedReason	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CPointOfService_CIBarcodeScannerStatusUpdatedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CPointOfService_CIBarcodeScannerStatusUpdatedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_PointOfService_IBarcodeScannerStatusUpdatedEventArgs <L"Windows.Devices.PointOfService.IBarcodeScannerStatusUpdatedEventArgs">
DEFINE_IIDX(IBarcodeScannerStatusUpdatedEventArgs, "355D8586-9C43-462B-A91A-816DC97F452C")

.comdef IBarcodeScannerStatusUpdatedEventArgs : public IInspectable

    get_Status		proc :ptr
    get_ExtendedStatus	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CPointOfService_CIBarcodeSymbologiesStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CPointOfService_CIBarcodeSymbologiesStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_PointOfService_IBarcodeSymbologiesStatics <L"Windows.Devices.PointOfService.IBarcodeSymbologiesStatics">
DEFINE_IIDX(IBarcodeSymbologiesStatics, "CA8549BB-06D2-43F4-A44B-C620679FD8D0")

.comdef IBarcodeSymbologiesStatics : public IInspectable

    get_Unknown		proc :ptr
    get_Ean8		proc :ptr
    get_Ean8Add2	proc :ptr
    get_Ean8Add5	proc :ptr
    get_Eanv		proc :ptr
    get_EanvAdd2	proc :ptr
    get_EanvAdd5	proc :ptr
    get_Ean13		proc :ptr
    get_Ean13Add2	proc :ptr
    get_Ean13Add5	proc :ptr
    get_Isbn		proc :ptr
    get_IsbnAdd5	proc :ptr
    get_Ismn		proc :ptr
    get_IsmnAdd2	proc :ptr
    get_IsmnAdd5	proc :ptr
    get_Issn		proc :ptr
    get_IssnAdd2	proc :ptr
    get_IssnAdd5	proc :ptr
    get_Ean99		proc :ptr
    get_Ean99Add2	proc :ptr
    get_Ean99Add5	proc :ptr
    get_Upca		proc :ptr
    get_UpcaAdd2	proc :ptr
    get_UpcaAdd5	proc :ptr
    get_Upce		proc :ptr
    get_UpceAdd2	proc :ptr
    get_UpceAdd5	proc :ptr
    get_UpcCoupon	proc :ptr
    get_TfStd		proc :ptr
    get_TfDis		proc :ptr
    get_TfInt		proc :ptr
    get_TfInd		proc :ptr
    get_TfMat		proc :ptr
    get_TfIata		proc :ptr
    get_Gs1DatabarType1 proc :ptr
    get_Gs1DatabarType2 proc :ptr
    get_Gs1DatabarType3 proc :ptr
    get_Code39		proc :ptr
    get_Code39Ex	proc :ptr
    get_Trioptic39	proc :ptr
    get_Code32		proc :ptr
    get_Pzn		proc :ptr
    get_Code93		proc :ptr
    get_Code93Ex	proc :ptr
    get_Code128		proc :ptr
    get_Gs1128		proc :ptr
    get_Gs1128Coupon	proc :ptr
    get_UccEan128	proc :ptr
    get_Sisac		proc :ptr
    get_Isbt		proc :ptr
    get_Codabar		proc :ptr
    get_Code11		proc :ptr
    get_Msi		proc :ptr
    get_Plessey		proc :ptr
    get_Telepen		proc :ptr
    get_Code16k		proc :ptr
    get_CodablockA	proc :ptr
    get_CodablockF	proc :ptr
    get_Codablock128	proc :ptr
    get_Code49		proc :ptr
    get_Aztec		proc :ptr
    get_DataCode	proc :ptr
    get_DataMatrix	proc :ptr
    get_HanXin		proc :ptr
    get_Maxicode	proc :ptr
    get_MicroPdf417	proc :ptr
    get_MicroQr		proc :ptr
    get_Pdf417		proc :ptr
    get_Qr		proc :ptr
    get_MsTag		proc :ptr
    get_Ccab		proc :ptr
    get_Ccc		proc :ptr
    get_Tlc39		proc :ptr
    get_AusPost		proc :ptr
    get_CanPost		proc :ptr
    get_ChinaPost	proc :ptr
    get_DutchKix	proc :ptr
    get_InfoMail	proc :ptr
    get_ItalianPost25	proc :ptr
    get_ItalianPost39	proc :ptr
    get_JapanPost	proc :ptr
    get_KoreanPost	proc :ptr
    get_SwedenPost	proc :ptr
    get_UkPost		proc :ptr
    get_UsIntelligent	proc :ptr
    get_UsIntelligentPkg proc :ptr
    get_UsPlanet	proc :ptr
    get_UsPostNet	proc :ptr
    get_Us4StateFics	proc :ptr
    get_OcrA		proc :ptr
    get_OcrB		proc :ptr
    get_Micr		proc :ptr
    get_ExtendedBase	proc :ptr
    GetName		proc :UINT32, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CPointOfService_CIBarcodeScannerDataReceivedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CPointOfService_CIBarcodeScannerDataReceivedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_PointOfService_IBarcodeScannerDataReceivedEventArgs <L"Windows.Devices.PointOfService.IBarcodeScannerDataReceivedEventArgs">
DEFINE_IIDX(IBarcodeScannerDataReceivedEventArgs, "4234A7E2-ED97-467D-AD2B-01E44313A929")

.comdef IBarcodeScannerDataReceivedEventArgs : public IInspectable

    get_Report		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CPointOfService_CIBarcodeScannerReport_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CPointOfService_CIBarcodeScannerReport_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_PointOfService_IBarcodeScannerReport <L"Windows.Devices.PointOfService.IBarcodeScannerReport">
DEFINE_IIDX(IBarcodeScannerReport, "5CE4D8B0-A489-4B96-86C4-F0BF8A37753D")

.comdef IBarcodeScannerReport : public IInspectable

    get_ScanDataType	proc :ptr
    get_ScanData	proc :ptr
    get_ScanDataLabel	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CPointOfService_CIBarcodeScannerErrorOccurredEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CPointOfService_CIBarcodeScannerErrorOccurredEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_PointOfService_IBarcodeScannerErrorOccurredEventArgs <L"Windows.Devices.PointOfService.IBarcodeScannerErrorOccurredEventArgs">
DEFINE_IIDX(IBarcodeScannerErrorOccurredEventArgs, "2CD2602F-CF3A-4002-A75A-C5EC468F0A20")

.comdef IBarcodeScannerErrorOccurredEventArgs : public IInspectable

    get_PartialInputData proc :ptr
    get_IsRetriable	proc :ptr
    get_ErrorData	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CPointOfService_CIBarcodeScannerImagePreviewReceivedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CPointOfService_CIBarcodeScannerImagePreviewReceivedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_PointOfService_IBarcodeScannerImagePreviewReceivedEventArgs <L"Windows.Devices.PointOfService.IBarcodeScannerImagePreviewReceivedEventArgs">
DEFINE_IIDX(IBarcodeScannerImagePreviewReceivedEventArgs, "F3B7DE85-6E8B-434E-9F58-06EF26BC4BAF")

.comdef IBarcodeScannerImagePreviewReceivedEventArgs : public IInspectable

    get_Preview		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CPointOfService_CIBarcodeScannerCapabilities_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CPointOfService_CIBarcodeScannerCapabilities_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_PointOfService_IBarcodeScannerCapabilities <L"Windows.Devices.PointOfService.IBarcodeScannerCapabilities">
DEFINE_IIDX(IBarcodeScannerCapabilities, "C60691E4-F2C8-4420-A307-B12EF6622857")

.comdef IBarcodeScannerCapabilities : public IInspectable

    get_PowerReportingType proc :ptr
    get_IsStatisticsReportingSupported proc :ptr
    get_IsStatisticsUpdatingSupported proc :ptr
    get_IsImagePreviewSupported proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CPointOfService_CIBarcodeScannerStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CPointOfService_CIBarcodeScannerStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_PointOfService_IBarcodeScannerStatics <L"Windows.Devices.PointOfService.IBarcodeScannerStatics">
DEFINE_IIDX(IBarcodeScannerStatics, "5D115F6F-DA49-41E8-8C8C-F0CB62A9C4FC")

.comdef IBarcodeScannerStatics : public IInspectable

    GetDefaultAsync	proc :ptr
    FromIdAsync		proc :HSTRING, :ptr
    GetDeviceSelector	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CPointOfService_CIBarcodeScanner_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CPointOfService_CIBarcodeScanner_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_PointOfService_IBarcodeScanner <L"Windows.Devices.PointOfService.IBarcodeScanner">
DEFINE_IIDX(IBarcodeScanner, "BEA33E06-B264-4F03-A9C1-45B20F01134F")

.comdef IBarcodeScanner : public IInspectable

    get_DeviceId	proc :ptr
    get_Capabilities	proc :ptr
    ClaimScannerAsync	proc :ptr
    CheckHealthAsync	proc :Windows::Devices::PointOfService::UnifiedPosHealthCheckLevel, :ptr
    GetSupportedSymbologiesAsync proc :ptr
    IsSymbologySupportedAsync proc :UINT32, :ptr
    RetrieveStatisticsAsync proc :ptr, :ptr
    GetSupportedProfiles proc :ptr
    IsProfileSupported	proc :HSTRING, :ptr
    add_StatusUpdated	proc :ptr, :ptr
    remove_StatusUpdated proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CPointOfService_CIMagneticStripeReaderEncryptionAlgorithmsStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CPointOfService_CIMagneticStripeReaderEncryptionAlgorithmsStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_PointOfService_IMagneticStripeReaderEncryptionAlgorithmsStatics <L"Windows.Devices.PointOfService.IMagneticStripeReaderEncryptionAlgorithmsStatics">
DEFINE_IIDX(IMagneticStripeReaderEncryptionAlgorithmsStatics, "53B57350-C3DB-4754-9C00-41392374A109")

.comdef IMagneticStripeReaderEncryptionAlgorithmsStatics : public IInspectable

    get_None		proc :ptr
    get_TripleDesDukpt	proc :ptr
    get_ExtendedBase	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CPointOfService_CIMagneticStripeReaderCardTypesStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CPointOfService_CIMagneticStripeReaderCardTypesStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_PointOfService_IMagneticStripeReaderCardTypesStatics <L"Windows.Devices.PointOfService.IMagneticStripeReaderCardTypesStatics">
DEFINE_IIDX(IMagneticStripeReaderCardTypesStatics, "528F2C5D-2986-474F-8454-7CCD05928D5F")

.comdef IMagneticStripeReaderCardTypesStatics : public IInspectable

    get_Unknown		proc :ptr
    get_Bank		proc :ptr
    get_Aamva		proc :ptr
    get_ExtendedBase	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CPointOfService_CIMagneticStripeReaderTrackData_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CPointOfService_CIMagneticStripeReaderTrackData_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_PointOfService_IMagneticStripeReaderTrackData <L"Windows.Devices.PointOfService.IMagneticStripeReaderTrackData">
DEFINE_IIDX(IMagneticStripeReaderTrackData, "104CF671-4A9D-446E-ABC5-20402307BA36")

.comdef IMagneticStripeReaderTrackData : public IInspectable

    get_Data		proc :ptr
    get_DiscretionaryData proc :ptr
    get_EncryptedData	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CPointOfService_CIMagneticStripeReaderReport_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CPointOfService_CIMagneticStripeReaderReport_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_PointOfService_IMagneticStripeReaderReport <L"Windows.Devices.PointOfService.IMagneticStripeReaderReport">
DEFINE_IIDX(IMagneticStripeReaderReport, "6A5B6047-99B0-4188-BEF1-EDDF79F78FE6")

.comdef IMagneticStripeReaderReport : public IInspectable

    get_CardType	proc :ptr
    get_Track1		proc :ptr
    get_Track2		proc :ptr
    get_Track3		proc :ptr
    get_Track4		proc :ptr
    get_Properties	proc :ptr
    get_CardAuthenticationData proc :ptr
    get_CardAuthenticationDataLength proc :ptr
    get_AdditionalSecurityInformation proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CPointOfService_CIMagneticStripeReaderBankCardDataReceivedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CPointOfService_CIMagneticStripeReaderBankCardDataReceivedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_PointOfService_IMagneticStripeReaderBankCardDataReceivedEventArgs <L"Windows.Devices.PointOfService.IMagneticStripeReaderBankCardDataReceivedEventArgs">
DEFINE_IIDX(IMagneticStripeReaderBankCardDataReceivedEventArgs, "2E958823-A31A-4763-882C-23725E39B08E")

.comdef IMagneticStripeReaderBankCardDataReceivedEventArgs : public IInspectable

    get_Report		proc :ptr
    get_AccountNumber	proc :ptr
    get_ExpirationDate	proc :ptr
    get_ServiceCode	proc :ptr
    get_Title		proc :ptr
    get_FirstName	proc :ptr
    get_MiddleInitial	proc :ptr
    get_Surname		proc :ptr
    get_Suffix		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CPointOfService_CIMagneticStripeReaderAamvaCardDataReceivedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CPointOfService_CIMagneticStripeReaderAamvaCardDataReceivedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_PointOfService_IMagneticStripeReaderAamvaCardDataReceivedEventArgs <L"Windows.Devices.PointOfService.IMagneticStripeReaderAamvaCardDataReceivedEventArgs">
DEFINE_IIDX(IMagneticStripeReaderAamvaCardDataReceivedEventArgs, "0A4BBD51-C316-4910-87F3-7A62BA862D31")

.comdef IMagneticStripeReaderAamvaCardDataReceivedEventArgs : public IInspectable

    get_Report		proc :ptr
    get_LicenseNumber	proc :ptr
    get_ExpirationDate	proc :ptr
    get_Restrictions	proc :ptr
    get_Class		proc :ptr
    get_Endorsements	proc :ptr
    get_BirthDate	proc :ptr
    get_FirstName	proc :ptr
    get_Surname		proc :ptr
    get_Suffix		proc :ptr
    get_Gender		proc :ptr
    get_HairColor	proc :ptr
    get_EyeColor	proc :ptr
    get_Height		proc :ptr
    get_Weight		proc :ptr
    get_Address		proc :ptr
    get_City		proc :ptr
    get_State		proc :ptr
    get_PostalCode	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CPointOfService_CIMagneticStripeReaderVendorSpecificCardDataReceivedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CPointOfService_CIMagneticStripeReaderVendorSpecificCardDataReceivedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_PointOfService_IMagneticStripeReaderVendorSpecificCardDataReceivedEventArgs <L"Windows.Devices.PointOfService.IMagneticStripeReaderVendorSpecificCardDataReceivedEventArgs">
DEFINE_IIDX(IMagneticStripeReaderVendorSpecificCardDataReceivedEventArgs, "AF0A5514-59CC-4A60-99E8-99A53DACE5AA")

.comdef IMagneticStripeReaderVendorSpecificCardDataReceivedEventArgs : public IInspectable

    get_Report		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CPointOfService_CIMagneticStripeReaderErrorOccurredEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CPointOfService_CIMagneticStripeReaderErrorOccurredEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_PointOfService_IMagneticStripeReaderErrorOccurredEventArgs <L"Windows.Devices.PointOfService.IMagneticStripeReaderErrorOccurredEventArgs">
DEFINE_IIDX(IMagneticStripeReaderErrorOccurredEventArgs, "1FEDF95D-2C84-41AD-B778-F2356A789AB1")

.comdef IMagneticStripeReaderErrorOccurredEventArgs : public IInspectable

    get_Track1Status	proc :ptr
    get_Track2Status	proc :ptr
    get_Track3Status	proc :ptr
    get_Track4Status	proc :ptr
    get_ErrorData	proc :ptr
    get_PartialInputData proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CPointOfService_CIMagneticStripeReaderStatusUpdatedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CPointOfService_CIMagneticStripeReaderStatusUpdatedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_PointOfService_IMagneticStripeReaderStatusUpdatedEventArgs <L"Windows.Devices.PointOfService.IMagneticStripeReaderStatusUpdatedEventArgs">
DEFINE_IIDX(IMagneticStripeReaderStatusUpdatedEventArgs, "09CC6BB0-3262-401D-9E8A-E80D6358906B")

.comdef IMagneticStripeReaderStatusUpdatedEventArgs : public IInspectable

    get_Status		proc :ptr
    get_ExtendedStatus	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CPointOfService_CIMagneticStripeReaderCapabilities_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CPointOfService_CIMagneticStripeReaderCapabilities_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_PointOfService_IMagneticStripeReaderCapabilities <L"Windows.Devices.PointOfService.IMagneticStripeReaderCapabilities">
DEFINE_IIDX(IMagneticStripeReaderCapabilities, "7128809C-C440-44A2-A467-469175D02896")

.comdef IMagneticStripeReaderCapabilities : public IInspectable

    get_CardAuthentication proc :ptr
    get_SupportedEncryptionAlgorithms proc :ptr
    get_AuthenticationLevel proc :ptr
    get_IsIsoSupported	proc :ptr
    get_IsJisOneSupported proc :ptr
    get_IsJisTwoSupported proc :ptr
    get_PowerReportingType proc :ptr
    get_IsStatisticsReportingSupported proc :ptr
    get_IsStatisticsUpdatingSupported proc :ptr
    get_IsTrackDataMaskingSupported proc :ptr
    get_IsTransmitSentinelsSupported proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CPointOfService_CIMagneticStripeReaderStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CPointOfService_CIMagneticStripeReaderStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_PointOfService_IMagneticStripeReaderStatics <L"Windows.Devices.PointOfService.IMagneticStripeReaderStatics">
DEFINE_IIDX(IMagneticStripeReaderStatics, "C45FAB4A-EFD7-4760-A5CE-15B0E47E94EB")

.comdef IMagneticStripeReaderStatics : public IInspectable

    GetDefaultAsync	proc :ptr
    FromIdAsync		proc :HSTRING, :ptr
    GetDeviceSelector	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CPointOfService_CIMagneticStripeReader_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CPointOfService_CIMagneticStripeReader_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_PointOfService_IMagneticStripeReader <L"Windows.Devices.PointOfService.IMagneticStripeReader">
DEFINE_IIDX(IMagneticStripeReader, "1A92B015-47C3-468A-9333-0C6517574883")

.comdef IMagneticStripeReader : public IInspectable

    get_DeviceId	proc :ptr
    get_Capabilities	proc :ptr
    get_SupportedCardTypes proc :ptr, :ptr
    get_DeviceAuthenticationProtocol proc :ptr
    CheckHealthAsync	proc :Windows::Devices::PointOfService::UnifiedPosHealthCheckLevel, :ptr
    ClaimReaderAsync	proc :ptr
    RetrieveStatisticsAsync proc :ptr, :ptr
    GetErrorReportingType proc :ptr
    add_StatusUpdated	proc :ptr, :ptr
    remove_StatusUpdated proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CPointOfService_CIClaimedBarcodeScanner_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CPointOfService_CIClaimedBarcodeScanner_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_PointOfService_IClaimedBarcodeScanner <L"Windows.Devices.PointOfService.IClaimedBarcodeScanner">
DEFINE_IIDX(IClaimedBarcodeScanner, "4A63B49C-8FA4-4332-BB26-945D11D81E0F")

.comdef IClaimedBarcodeScanner : public IInspectable

    get_DeviceId	proc :ptr
    get_IsEnabled	proc :ptr
    put_IsDisabledOnDataReceived proc :boolean
    get_IsDisabledOnDataReceived proc :ptr
    put_IsDecodeDataEnabled proc :boolean
    get_IsDecodeDataEnabled proc :ptr
    EnableAsync		proc :ptr
    DisableAsync	proc :ptr
    RetainDevice	proc
    SetActiveSymbologiesAsync proc :ptr, :ptr
    ResetStatisticsAsync proc :ptr, :ptr
    UpdateStatisticsAsync proc :ptr, :ptr
    SetActiveProfileAsync proc :HSTRING, :ptr
    add_DataReceived	proc :ptr, :ptr
    remove_DataReceived proc :EventRegistrationToken
    add_TriggerPressed	proc :ptr, :ptr
    remove_TriggerPressed proc :EventRegistrationToken
    add_TriggerReleased proc :ptr, :ptr
    remove_TriggerReleased proc :EventRegistrationToken
    add_ReleaseDeviceRequested proc :ptr, :ptr
    remove_ReleaseDeviceRequested proc :EventRegistrationToken
    add_ImagePreviewReceived proc :ptr, :ptr
    remove_ImagePreviewReceived proc :EventRegistrationToken
    add_ErrorOccurred	proc :ptr, :ptr
    remove_ErrorOccurred proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CPointOfService_CIClaimedMagneticStripeReader_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CPointOfService_CIClaimedMagneticStripeReader_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_PointOfService_IClaimedMagneticStripeReader <L"Windows.Devices.PointOfService.IClaimedMagneticStripeReader">
DEFINE_IIDX(IClaimedMagneticStripeReader, "475CA8F3-9417-48BC-B9D7-4163A7844C02")

.comdef IClaimedMagneticStripeReader : public IInspectable

    get_DeviceId	proc :ptr
    get_IsEnabled	proc :ptr
    put_IsDisabledOnDataReceived proc :boolean
    get_IsDisabledOnDataReceived proc :ptr
    put_IsDecodeDataEnabled proc :boolean
    get_IsDecodeDataEnabled proc :ptr
    get_IsDeviceAuthenticated proc :ptr
    put_DataEncryptionAlgorithm proc :UINT32
    get_DataEncryptionAlgorithm proc :ptr
    put_TracksToRead	proc :Windows::Devices::PointOfService::MagneticStripeReaderTrackIds
    get_TracksToRead	proc :ptr
    put_IsTransmitSentinelsEnabled proc :boolean
    get_IsTransmitSentinelsEnabled proc :ptr
    EnableAsync		proc :ptr
    DisableAsync	proc :ptr
    RetainDevice	proc
    SetErrorReportingType proc :Windows::Devices::PointOfService::MagneticStripeReaderErrorReportingType
    RetrieveDeviceAuthenticationDataAsync proc :ptr
    AuthenticateDeviceAsync proc :UINT32
    DeAuthenticateDeviceAsync proc :UINT32
    UpdateKeyAsync	proc :HSTRING, :HSTRING, :ptr
    ResetStatisticsAsync proc :ptr, :ptr
    UpdateStatisticsAsync proc :ptr, :ptr
    add_BankCardDataReceived proc :ptr, :ptr
    remove_BankCardDataReceived proc :EventRegistrationToken
    add_AamvaCardDataReceived proc :ptr, :ptr
    remove_AamvaCardDataReceived proc :EventRegistrationToken
    add_VendorSpecificDataReceived proc :ptr, :ptr
    remove_VendorSpecificDataReceived proc :EventRegistrationToken
    add_ReleaseDeviceRequested proc :ptr, :ptr
    remove_ReleaseDeviceRequested proc :EventRegistrationToken
    add_ErrorOccurred	proc :ptr, :ptr
    remove_ErrorOccurred proc :EventRegistrationToken
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_Devices_PointOfService_UnifiedPosErrorData_DEFINED
define RUNTIMECLASS_Windows_Devices_PointOfService_UnifiedPosErrorData_DEFINED
define RuntimeClass_Windows_Devices_PointOfService_UnifiedPosErrorData <L"Windows.Devices.PointOfService.UnifiedPosErrorData">
endif
ifndef RUNTIMECLASS_Windows_Devices_PointOfService_BarcodeScannerStatusUpdatedEventArgs_DEFINED
define RUNTIMECLASS_Windows_Devices_PointOfService_BarcodeScannerStatusUpdatedEventArgs_DEFINED
define RuntimeClass_Windows_Devices_PointOfService_BarcodeScannerStatusUpdatedEventArgs <L"Windows.Devices.PointOfService.BarcodeScannerStatusUpdatedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_Devices_PointOfService_BarcodeSymbologies_DEFINED
define RUNTIMECLASS_Windows_Devices_PointOfService_BarcodeSymbologies_DEFINED
define RuntimeClass_Windows_Devices_PointOfService_BarcodeSymbologies <L"Windows.Devices.PointOfService.BarcodeSymbologies">
endif
ifndef RUNTIMECLASS_Windows_Devices_PointOfService_BarcodeScannerReport_DEFINED
define RUNTIMECLASS_Windows_Devices_PointOfService_BarcodeScannerReport_DEFINED
define RuntimeClass_Windows_Devices_PointOfService_BarcodeScannerReport <L"Windows.Devices.PointOfService.BarcodeScannerReport">
endif
ifndef RUNTIMECLASS_Windows_Devices_PointOfService_BarcodeScannerDataReceivedEventArgs_DEFINED
define RUNTIMECLASS_Windows_Devices_PointOfService_BarcodeScannerDataReceivedEventArgs_DEFINED
define RuntimeClass_Windows_Devices_PointOfService_BarcodeScannerDataReceivedEventArgs <L"Windows.Devices.PointOfService.BarcodeScannerDataReceivedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_Devices_PointOfService_BarcodeScannerErrorOccurredEventArgs_DEFINED
define RUNTIMECLASS_Windows_Devices_PointOfService_BarcodeScannerErrorOccurredEventArgs_DEFINED
define RuntimeClass_Windows_Devices_PointOfService_BarcodeScannerErrorOccurredEventArgs <L"Windows.Devices.PointOfService.BarcodeScannerErrorOccurredEventArgs">
endif
ifndef RUNTIMECLASS_Windows_Devices_PointOfService_BarcodeScannerImagePreviewReceivedEventArgs_DEFINED
define RUNTIMECLASS_Windows_Devices_PointOfService_BarcodeScannerImagePreviewReceivedEventArgs_DEFINED
define RuntimeClass_Windows_Devices_PointOfService_BarcodeScannerImagePreviewReceivedEventArgs <L"Windows.Devices.PointOfService.BarcodeScannerImagePreviewReceivedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_Devices_PointOfService_BarcodeScannerCapabilities_DEFINED
define RUNTIMECLASS_Windows_Devices_PointOfService_BarcodeScannerCapabilities_DEFINED
define RuntimeClass_Windows_Devices_PointOfService_BarcodeScannerCapabilities <L"Windows.Devices.PointOfService.BarcodeScannerCapabilities">
endif
ifndef RUNTIMECLASS_Windows_Devices_PointOfService_BarcodeScanner_DEFINED
define RUNTIMECLASS_Windows_Devices_PointOfService_BarcodeScanner_DEFINED
define RuntimeClass_Windows_Devices_PointOfService_BarcodeScanner <L"Windows.Devices.PointOfService.BarcodeScanner">
endif
ifndef RUNTIMECLASS_Windows_Devices_PointOfService_ClaimedBarcodeScanner_DEFINED
define RUNTIMECLASS_Windows_Devices_PointOfService_ClaimedBarcodeScanner_DEFINED
define RuntimeClass_Windows_Devices_PointOfService_ClaimedBarcodeScanner <L"Windows.Devices.PointOfService.ClaimedBarcodeScanner">
endif
ifndef RUNTIMECLASS_Windows_Devices_PointOfService_MagneticStripeReaderEncryptionAlgorithms_DEFINED
define RUNTIMECLASS_Windows_Devices_PointOfService_MagneticStripeReaderEncryptionAlgorithms_DEFINED
define RuntimeClass_Windows_Devices_PointOfService_MagneticStripeReaderEncryptionAlgorithms <L"Windows.Devices.PointOfService.MagneticStripeReaderEncryptionAlgorithms">
endif
ifndef RUNTIMECLASS_Windows_Devices_PointOfService_MagneticStripeReaderCardTypes_DEFINED
define RUNTIMECLASS_Windows_Devices_PointOfService_MagneticStripeReaderCardTypes_DEFINED
define RuntimeClass_Windows_Devices_PointOfService_MagneticStripeReaderCardTypes <L"Windows.Devices.PointOfService.MagneticStripeReaderCardTypes">
endif
ifndef RUNTIMECLASS_Windows_Devices_PointOfService_MagneticStripeReaderTrackData_DEFINED
define RUNTIMECLASS_Windows_Devices_PointOfService_MagneticStripeReaderTrackData_DEFINED
define RuntimeClass_Windows_Devices_PointOfService_MagneticStripeReaderTrackData <L"Windows.Devices.PointOfService.MagneticStripeReaderTrackData">
endif
ifndef RUNTIMECLASS_Windows_Devices_PointOfService_MagneticStripeReaderReport_DEFINED
define RUNTIMECLASS_Windows_Devices_PointOfService_MagneticStripeReaderReport_DEFINED
define RuntimeClass_Windows_Devices_PointOfService_MagneticStripeReaderReport <L"Windows.Devices.PointOfService.MagneticStripeReaderReport">
endif
ifndef RUNTIMECLASS_Windows_Devices_PointOfService_MagneticStripeReaderBankCardDataReceivedEventArgs_DEFINED
define RUNTIMECLASS_Windows_Devices_PointOfService_MagneticStripeReaderBankCardDataReceivedEventArgs_DEFINED
define RuntimeClass_Windows_Devices_PointOfService_MagneticStripeReaderBankCardDataReceivedEventArgs <L"Windows.Devices.PointOfService.MagneticStripeReaderBankCardDataReceivedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_Devices_PointOfService_MagneticStripeReaderAamvaCardDataReceivedEventArgs_DEFINED
define RUNTIMECLASS_Windows_Devices_PointOfService_MagneticStripeReaderAamvaCardDataReceivedEventArgs_DEFINED
define RuntimeClass_Windows_Devices_PointOfService_MagneticStripeReaderAamvaCardDataReceivedEventArgs <L"Windows.Devices.PointOfService.MagneticStripeReaderAamvaCardDataReceivedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_Devices_PointOfService_MagneticStripeReaderVendorSpecificCardDataReceivedEventArgs_DEFINED
define RUNTIMECLASS_Windows_Devices_PointOfService_MagneticStripeReaderVendorSpecificCardDataReceivedEventArgs_DEFINED
define RuntimeClass_Windows_Devices_PointOfService_MagneticStripeReaderVendorSpecificCardDataReceivedEventArgs <L"Windows.Devices.PointOfService.MagneticStripeReaderVendorSpecificCardDataReceivedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_Devices_PointOfService_MagneticStripeReaderErrorOccurredEventArgs_DEFINED
define RUNTIMECLASS_Windows_Devices_PointOfService_MagneticStripeReaderErrorOccurredEventArgs_DEFINED
define RuntimeClass_Windows_Devices_PointOfService_MagneticStripeReaderErrorOccurredEventArgs <L"Windows.Devices.PointOfService.MagneticStripeReaderErrorOccurredEventArgs">
endif
ifndef RUNTIMECLASS_Windows_Devices_PointOfService_MagneticStripeReaderStatusUpdatedEventArgs_DEFINED
define RUNTIMECLASS_Windows_Devices_PointOfService_MagneticStripeReaderStatusUpdatedEventArgs_DEFINED
define RuntimeClass_Windows_Devices_PointOfService_MagneticStripeReaderStatusUpdatedEventArgs <L"Windows.Devices.PointOfService.MagneticStripeReaderStatusUpdatedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_Devices_PointOfService_MagneticStripeReaderCapabilities_DEFINED
define RUNTIMECLASS_Windows_Devices_PointOfService_MagneticStripeReaderCapabilities_DEFINED
define RuntimeClass_Windows_Devices_PointOfService_MagneticStripeReaderCapabilities <L"Windows.Devices.PointOfService.MagneticStripeReaderCapabilities">
endif
ifndef RUNTIMECLASS_Windows_Devices_PointOfService_ClaimedMagneticStripeReader_DEFINED
define RUNTIMECLASS_Windows_Devices_PointOfService_ClaimedMagneticStripeReader_DEFINED
define RuntimeClass_Windows_Devices_PointOfService_ClaimedMagneticStripeReader <L"Windows.Devices.PointOfService.ClaimedMagneticStripeReader">
endif
ifndef RUNTIMECLASS_Windows_Devices_PointOfService_MagneticStripeReader_DEFINED
define RUNTIMECLASS_Windows_Devices_PointOfService_MagneticStripeReader_DEFINED
define RuntimeClass_Windows_Devices_PointOfService_MagneticStripeReader <L"Windows.Devices.PointOfService.MagneticStripeReader">
endif

endif
