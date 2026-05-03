ifndef _RPCNDR500_
include rpcndr500.inc
endif

ifndef __printdriver_h__
define __printdriver_h__

ifndef __oaidl_h__
include oaidl.inc
endif

define PRINTSCHEMA_KEYWORDS_NAMESPACE_URI  <"http:>
define PRINTSCHEMA_KEYWORDSV11_NAMESPACE_URI  <L"http:>

if (NTDDI_VERSION ge NTDDI_WIN8)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

ifndef __IPrintSchemaElement_INTERFACE_DEFINED__
define __IPrintSchemaElement_INTERFACE_DEFINED__

DEFINE_IIDX(IPrintSchemaElement, "724c1646-e64b-4bbf-8eb4-d45e4fd580da")

.comdef IPrintSchemaElement : public IDispatch
    get_XmlNode		proc :ptr
    get_Name		proc :ptr
    get_NamespaceUri	proc :ptr
   .ends

endif

ifndef __IPrintSchemaDisplayableElement_INTERFACE_DEFINED__
define __IPrintSchemaDisplayableElement_INTERFACE_DEFINED__

DEFINE_IIDX(IPrintSchemaDisplayableElement, "af45af49-d6aa-407d-bf87-3912236e9d94")

.comdef IPrintSchemaDisplayableElement : public IPrintSchemaElement
    get_DisplayName	proc :ptr
   .ends

endif

.enum PrintSchemaConstrainedSetting {
	PrintSchemaConstrainedSetting_None,
	PrintSchemaConstrainedSetting_PrintTicket,
	PrintSchemaConstrainedSetting_Admin,
	PrintSchemaConstrainedSetting_Device
	}

ifndef __IPrintSchemaOption_INTERFACE_DEFINED__
define __IPrintSchemaOption_INTERFACE_DEFINED__

DEFINE_IIDX(IPrintSchemaOption, "66bb2f51-5844-4997-8d70-4b7cc221cf92")

.comdef IPrintSchemaOption : public IPrintSchemaDisplayableElement
    get_Selected	proc :ptr
    get_Constrained	proc :ptr
    GetPropertyValue	proc :BSTR, :BSTR, :ptr
   .ends

endif

ifndef __IPrintSchemaPageMediaSizeOption_INTERFACE_DEFINED__
define __IPrintSchemaPageMediaSizeOption_INTERFACE_DEFINED__

DEFINE_IIDX(IPrintSchemaPageMediaSizeOption, "68746729-f493-4830-a10f-69028774605d")

.comdef IPrintSchemaPageMediaSizeOption : public IPrintSchemaOption
    get_WidthInMicrons	proc :ptr
    get_HeightInMicrons proc :ptr
   .ends

endif

ifndef __IPrintSchemaNUpOption_INTERFACE_DEFINED__
define __IPrintSchemaNUpOption_INTERFACE_DEFINED__

DEFINE_IIDX(IPrintSchemaNUpOption, "1f6342f2-d848-42e3-8995-c10a9ef9a3ba")

.comdef IPrintSchemaNUpOption : public IPrintSchemaOption
    get_PagesPerSheet	proc :ptr
   .ends

endif

.enum PrintSchemaSelectionType {
	PrintSchemaSelectionType_PickOne	= 0,
	PrintSchemaSelectionType_PickMany	= ( PrintSchemaSelectionType_PickOne + 1 )
    }

ifndef __IPrintSchemaOptionCollection_INTERFACE_DEFINED__
define __IPrintSchemaOptionCollection_INTERFACE_DEFINED__

DEFINE_IIDX(IPrintSchemaOptionCollection, "baecb0bd-a946-4771-bc30-e8b24f8d45c1")

.comdef IPrintSchemaOptionCollection : public IDispatch
    get_Count		proc :ptr
    GetAt		proc :ULONG, :ptr
    get__NewEnum	proc :ptr
   .ends

endif

ifndef __IPrintSchemaFeature_INTERFACE_DEFINED__
define __IPrintSchemaFeature_INTERFACE_DEFINED__

DEFINE_IIDX(IPrintSchemaFeature, "ef189461-5d62-4626-8e57-ff83583c4826")

.comdef IPrintSchemaFeature : public IPrintSchemaDisplayableElement
    get_SelectedOption	proc :ptr
    put_SelectedOption	proc :ptr
    get_SelectionType	proc :ptr
    GetOption		proc :BSTR, :BSTR, :ptr
    get_DisplayUI	proc :ptr
   .ends

endif

ifndef __IPrintSchemaPageImageableSize_INTERFACE_DEFINED__
define __IPrintSchemaPageImageableSize_INTERFACE_DEFINED__

DEFINE_IIDX(IPrintSchemaPageImageableSize, "7c85bf5e-dc7c-4f61-839b-4107e1c9b68e")

.comdef IPrintSchemaPageImageableSize : public IPrintSchemaElement
    get_ImageableSizeWidthInMicrons proc :ptr
    get_ImageableSizeHeightInMicrons proc :ptr
    get_OriginWidthInMicrons proc :ptr
    get_OriginHeightInMicrons proc :ptr
    get_ExtentWidthInMicrons proc :ptr
    get_ExtentHeightInMicrons proc :ptr
   .ends

endif

if (NTDDI_VERSION ge NTDDI_WINBLUE)
.enum PrintSchemaParameterDataType {
	PrintSchemaParameterDataType_Integer,
	PrintSchemaParameterDataType_NumericString,
	PrintSchemaParameterDataType_String
	}

ifndef __IPrintSchemaParameterDefinition_INTERFACE_DEFINED__
define __IPrintSchemaParameterDefinition_INTERFACE_DEFINED__

DEFINE_IIDX(IPrintSchemaParameterDefinition, "b5ade81e-0e61-4fe1-81c6-c333e4ffe0f1")

.comdef IPrintSchemaParameterDefinition : public IPrintSchemaDisplayableElement
    get_UserInputRequired proc :ptr
    get_UnitType	proc :ptr
    get_DataType	proc :ptr
    get_RangeMin	proc :ptr
    get_RangeMax	proc :ptr
   .ends

endif

ifndef __IPrintSchemaParameterInitializer_INTERFACE_DEFINED__
define __IPrintSchemaParameterInitializer_INTERFACE_DEFINED__

DEFINE_IIDX(IPrintSchemaParameterInitializer, "52027082-0b74-4648-9564-828cc6cb656c")

.comdef IPrintSchemaParameterInitializer : public IPrintSchemaElement
    get_Value		proc :ptr
    put_Value		proc :ptr
   .ends

endif

endif

ifndef __IPrintSchemaCapabilities_INTERFACE_DEFINED__
define __IPrintSchemaCapabilities_INTERFACE_DEFINED__

DEFINE_IIDX(IPrintSchemaCapabilities, "5a577640-501d-4927-bcd0-5ef57a7ed175")

.comdef IPrintSchemaCapabilities : public IPrintSchemaElement
    GetFeatureByKeyName proc :BSTR, :ptr
    GetFeature		proc :BSTR, :BSTR, :ptr
    get_PageImageableSize proc :ptr
    get_JobCopiesAllDocumentsMinValue proc :ptr
    get_JobCopiesAllDocumentsMaxValue proc :ptr
    GetSelectedOptionInPrintTicket proc :ptr, :ptr
    GetOptions		proc :ptr, :ptr
   .ends

endif

if (NTDDI_VERSION ge NTDDI_WINBLUE)

ifndef __IPrintSchemaCapabilities2_INTERFACE_DEFINED__
define __IPrintSchemaCapabilities2_INTERFACE_DEFINED__

DEFINE_IIDX(IPrintSchemaCapabilities2, "b58845f4-9970-4d87-a636-169fb82ed642")

.comdef IPrintSchemaCapabilities2 : public IPrintSchemaCapabilities
    GetParameterDefinition proc :BSTR, :BSTR, :ptr
   .ends

endif

endif

ifndef __IPrintSchemaAsyncOperation_INTERFACE_DEFINED__
define __IPrintSchemaAsyncOperation_INTERFACE_DEFINED__

DEFINE_IIDX(IPrintSchemaAsyncOperation, "143c8dcb-d37f-47f7-88e8-6b1d21f2c5f7")

.comdef IPrintSchemaAsyncOperation : public IDispatch
    Start		proc
    Cancel		proc
   .ends

endif

ifndef __IPrintSchemaTicket_INTERFACE_DEFINED__
define __IPrintSchemaTicket_INTERFACE_DEFINED__

DEFINE_IIDX(IPrintSchemaTicket, "e480b861-4708-4e6d-a5b4-a2b4eeb9baa4")

.comdef IPrintSchemaTicket : public IPrintSchemaElement
    GetFeatureByKeyName proc :BSTR, :ptr
    GetFeature		proc :BSTR, :BSTR, :ptr
    ValidateAsync	proc :ptr
    CommitAsync		proc :ptr, :ptr
    NotifyXmlChanged	proc
    GetCapabilities	proc :ptr
    get_JobCopiesAllDocuments proc :ptr
    put_JobCopiesAllDocuments proc :ULONG
   .ends

endif

if (NTDDI_VERSION ge NTDDI_WINBLUE)

ifndef __IPrintSchemaTicket2_INTERFACE_DEFINED__
define __IPrintSchemaTicket2_INTERFACE_DEFINED__

DEFINE_IIDX(IPrintSchemaTicket2, "2ec1f844-766a-47a1-91f4-2eeb6190f80c")

.comdef IPrintSchemaTicket2 : public IPrintSchemaTicket
    GetParameterInitializer proc :BSTR, :BSTR, :ptr
   .ends

endif

endif

ifndef __IPrintSchemaAsyncOperationEvent_INTERFACE_DEFINED__
define __IPrintSchemaAsyncOperationEvent_INTERFACE_DEFINED__

DEFINE_IIDX(IPrintSchemaAsyncOperationEvent, "23adbb16-0133-4906-b29a-1dce1d026379")

.comdef IPrintSchemaAsyncOperationEvent : public IDispatch
    Completed		proc :ptr, :HRESULT
   .ends

endif

endif


if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef __IPrinterScriptableSequentialStream_INTERFACE_DEFINED__
define __IPrinterScriptableSequentialStream_INTERFACE_DEFINED__

DEFINE_IIDX(IPrinterScriptableSequentialStream, "2072838a-316f-467a-a949-27f68c44a854")

.comdef IPrinterScriptableSequentialStream : public IDispatch
    Read		proc :LONG, :ptr
    Write		proc :ptr, :ptr
   .ends

endif

ifndef __IPrinterScriptableStream_INTERFACE_DEFINED__
define __IPrinterScriptableStream_INTERFACE_DEFINED__

DEFINE_IIDX(IPrinterScriptableStream, "7edf9a92-4750-41a5-a17f-879a6f4f7dcb")

.comdef IPrinterScriptableStream : public IPrinterScriptableSequentialStream
    Commit		proc
    Seek		proc :LONG, :STREAM_SEEK, :ptr
    SetSize		proc :LONG
   .ends

endif

endif


if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

ifndef __IPrinterPropertyBag_INTERFACE_DEFINED__
define __IPrinterPropertyBag_INTERFACE_DEFINED__

DEFINE_IIDX(IPrinterPropertyBag, "fea77364-df95-4a23-a905-019b79a8e481")

.comdef IPrinterPropertyBag : public IDispatch
    GetBool		proc :BSTR, :ptr
    SetBool		proc :BSTR, :BOOL
    GetInt32		proc :BSTR, :ptr
    SetInt32		proc :BSTR, :LONG
    GetString		proc :BSTR, :ptr
    SetString		proc :BSTR, :BSTR
    GetBytes		proc :BSTR, :ptr, :ptr
    SetBytes		proc :BSTR, :DWORD, :ptr
    GetReadStream	proc :BSTR, :ptr
    GetWriteStream	proc :BSTR, :ptr
   .ends

endif

endif


if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef __IPrinterScriptablePropertyBag_INTERFACE_DEFINED__
define __IPrinterScriptablePropertyBag_INTERFACE_DEFINED__

DEFINE_IIDX(IPrinterScriptablePropertyBag, "91c7765f-ed57-49ad-8b01-dc24816a5294")

.comdef IPrinterScriptablePropertyBag : public IDispatch
    GetBool		proc :BSTR, :ptr
    SetBool		proc :BSTR, :BOOL
    GetInt32		proc :BSTR, :ptr
    SetInt32		proc :BSTR, :LONG
    GetString		proc :BSTR, :ptr
    SetString		proc :BSTR, :BSTR
    GetBytes		proc :BSTR, :ptr
    SetBytes		proc :BSTR, :ptr
    GetReadStream	proc :BSTR, :ptr
    GetWriteStream	proc :BSTR, :ptr
   .ends

endif

endif


if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
if (NTDDI_VERSION ge NTDDI_WINTHRESHOLD)

ifndef __IPrinterScriptablePropertyBag2_INTERFACE_DEFINED__
define __IPrinterScriptablePropertyBag2_INTERFACE_DEFINED__

DEFINE_IIDX(IPrinterScriptablePropertyBag2, "2A1C53C4-8638-4B3E-B518-2773C94556A3")

.comdef IPrinterScriptablePropertyBag2 : public IPrinterScriptablePropertyBag
    GetReadStreamAsXML	proc :BSTR, :ptr
   .ends

endif

endif
endif


if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

ifndef __IPrinterQueue_INTERFACE_DEFINED__
define __IPrinterQueue_INTERFACE_DEFINED__

DEFINE_IIDX(IPrinterQueue, "3580a828-07fe-4b94-ac1a-757d9d2d3056")

.comdef IPrinterQueue : public IDispatch
    get_Handle		proc :ptr
    get_Name		proc :ptr
    SendBidiQuery	proc :BSTR
    GetProperties	proc :ptr
   .ends

endif

if (NTDDI_VERSION ge NTDDI_WINBLUE)
.enum PrintJobStatus {
	PrintJobStatus_Paused	= 0x1,
	PrintJobStatus_Error	= 0x2,
	PrintJobStatus_Deleting = 0x4,
	PrintJobStatus_Spooling = 0x8,
	PrintJobStatus_Printing = 0x10,
	PrintJobStatus_Offline	= 0x20,
	PrintJobStatus_PaperOut = 0x40,
	PrintJobStatus_Printed	= 0x80,
	PrintJobStatus_Deleted	= 0x100,
	PrintJobStatus_BlockedDeviceQueue	= 0x200,
	PrintJobStatus_UserIntervention = 0x400,
	PrintJobStatus_Restarted	= 0x800,
	PrintJobStatus_Complete = 0x1000,
	PrintJobStatus_Retained = 0x2000
    }

ifndef __IPrintJob_INTERFACE_DEFINED__
define __IPrintJob_INTERFACE_DEFINED__

DEFINE_IIDX(IPrintJob, "b771dab8-1282-41b7-858c-f206e4d20577")

.comdef IPrintJob : public IUnknown
    get_Name		proc :ptr
    get_Id		proc :ptr
    get_PrintedPages	proc :ptr
    get_TotalPages	proc :ptr
    get_Status		proc :ptr
    get_SubmissionTime	proc :ptr
    RequestCancel	proc
   .ends

endif

ifndef __IPrintJobCollection_INTERFACE_DEFINED__
define __IPrintJobCollection_INTERFACE_DEFINED__

DEFINE_IIDX(IPrintJobCollection, "72b82a24-a598-4e87-895f-cdb23a49e9dc")

.comdef IPrintJobCollection : public IDispatch
    get_Count		proc :ptr
    GetAt		proc :ULONG, :ptr
    get__NewEnum	proc :ptr
   .ends

endif

ifndef __IPrinterQueueViewEvent_INTERFACE_DEFINED__
define __IPrinterQueueViewEvent_INTERFACE_DEFINED__

DEFINE_IIDX(IPrinterQueueViewEvent, "c5b6042b-fd21-404a-a0ef-e2fbb52b9080")

.comdef IPrinterQueueViewEvent : public IDispatch
    OnChanged		proc :ptr, :ULONG, :ULONG, :ULONG
   .ends

endif

ifndef __IPrinterQueueView_INTERFACE_DEFINED__
define __IPrinterQueueView_INTERFACE_DEFINED__

DEFINE_IIDX(IPrinterQueueView, "476e2969-3b2b-4b3f-8277-cff6056042aa")

.comdef IPrinterQueueView : public IDispatch
    SetViewRange	proc :ULONG, :ULONG
   .ends

endif

endif

ifndef __IPrinterQueueEvent_INTERFACE_DEFINED__
define __IPrinterQueueEvent_INTERFACE_DEFINED__

DEFINE_IIDX(IPrinterQueueEvent, "214685F6-7B78-4681-87E0-495F739273D1")

.comdef IPrinterQueueEvent : public IDispatch
    OnBidiResponseReceived proc :BSTR, :HRESULT
   .ends

endif

if (NTDDI_VERSION ge NTDDI_WINBLUE)

ifndef __IPrinterBidiSetRequestCallback_INTERFACE_DEFINED__
define __IPrinterBidiSetRequestCallback_INTERFACE_DEFINED__

DEFINE_IIDX(IPrinterBidiSetRequestCallback, "c52d32dd-f2b4-4052-8502-ec4305ecb71f")

.comdef IPrinterBidiSetRequestCallback : public IUnknown
    Completed		proc :BSTR, :HRESULT
   .ends

endif

ifndef __IPrinterExtensionAsyncOperation_INTERFACE_DEFINED__
define __IPrinterExtensionAsyncOperation_INTERFACE_DEFINED__

DEFINE_IIDX(IPrinterExtensionAsyncOperation, "108d6a23-6a4b-4552-9448-68b427186acd")

.comdef IPrinterExtensionAsyncOperation : public IUnknown
    Cancel		proc
   .ends

endif

ifndef __IPrinterQueue2_INTERFACE_DEFINED__
define __IPrinterQueue2_INTERFACE_DEFINED__

DEFINE_IIDX(IPrinterQueue2, "8cd444e8-c9bb-49b3-8e38-e03209416131")

.comdef IPrinterQueue2 : public IPrinterQueue
    SendBidiSetRequestAsync proc :BSTR, :ptr, :ptr
    GetPrinterQueueView proc :ULONG, :ULONG, :ptr
   .ends

endif

endif

ifndef __IPrinterExtensionContext_INTERFACE_DEFINED__
define __IPrinterExtensionContext_INTERFACE_DEFINED__

DEFINE_IIDX(IPrinterExtensionContext, "39843bf2-c4d2-41fd-b4b2-aedbee5e1900")

.comdef IPrinterExtensionContext : public IDispatch
    get_PrinterQueue	proc :ptr
    get_PrintSchemaTicket proc :ptr
    get_DriverProperties proc :ptr
    get_UserProperties	proc :ptr
   .ends

endif

endif


if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef __IPrinterExtensionRequest_INTERFACE_DEFINED__
define __IPrinterExtensionRequest_INTERFACE_DEFINED__

DEFINE_IIDX(IPrinterExtensionRequest, "39843bf3-c4d2-41fd-b4b2-aedbee5e1900")

.comdef IPrinterExtensionRequest : public IDispatch
    Cancel		proc :HRESULT, :BSTR
    Complete		proc
   .ends

endif

ifndef __IPrinterExtensionEventArgs_INTERFACE_DEFINED__
define __IPrinterExtensionEventArgs_INTERFACE_DEFINED__

DEFINE_IIDX(IPrinterExtensionEventArgs, "39843bf4-c4d2-41fd-b4b2-aedbee5e1900")

.comdef IPrinterExtensionEventArgs : public IPrinterExtensionContext
    get_BidiNotification proc :ptr
    get_ReasonId	proc :ptr
    get_Request		proc :ptr
    get_SourceApplication proc :ptr
    get_DetailedReasonId proc :ptr
    get_WindowModal	proc :ptr
    get_WindowParent	proc :ptr
   .ends

endif

ifndef __IPrinterExtensionContextCollection_INTERFACE_DEFINED__
define __IPrinterExtensionContextCollection_INTERFACE_DEFINED__

DEFINE_IIDX(IPrinterExtensionContextCollection, "fb476970-9bab-4861-811e-3e98b0c5addf")

.comdef IPrinterExtensionContextCollection : public IDispatch
    get_Count		proc :ptr
    GetAt		proc :ULONG, :ptr
    get__NewEnum	proc :ptr
   .ends

endif

ifndef __IPrinterExtensionEvent_INTERFACE_DEFINED__
define __IPrinterExtensionEvent_INTERFACE_DEFINED__

DEFINE_IIDX(IPrinterExtensionEvent, "C093CB63-5EF5-4585-AF8E-4D5637487B57")

.comdef IPrinterExtensionEvent : public IDispatch
    OnDriverEvent	proc :ptr
    OnPrinterQueuesEnumerated proc :ptr
   .ends

endif

ifndef __IPrinterExtensionManager_INTERFACE_DEFINED__
define __IPrinterExtensionManager_INTERFACE_DEFINED__

DEFINE_IIDX(IPrinterExtensionManager, "93C6EB8C-B001-4355-9629-8E8A1B3F8E77")

.comdef IPrinterExtensionManager : public IUnknown
    EnableEvents	proc :GUID
    DisableEvents	proc
   .ends

endif

ifndef __IPrinterScriptContext_INTERFACE_DEFINED__
define __IPrinterScriptContext_INTERFACE_DEFINED__

DEFINE_IIDX(IPrinterScriptContext, "066ACBCA-8881-49C9-BB98-FAE16B4889E1")

.comdef IPrinterScriptContext : public IDispatch
    get_DriverProperties proc :ptr
    get_QueueProperties proc :ptr
    get_UserProperties	proc :ptr
   .ends

endif

endif

ifndef __PrinterExtensionLib_LIBRARY_DEFINED__
define __PrinterExtensionLib_LIBRARY_DEFINED__

externdef LIBID_PrinterExtensionLib:IID
DEFINE_GUIDS(CLSID_PrinterQueue, "EB54C230-798C-4C9E-B461-29FAD04039B1")
DEFINE_GUIDS(CLSID_PrinterQueueView, "EB54C231-798C-4C9E-B461-29FAD04039B1")
DEFINE_GUIDS(CLSID_PrintSchemaAsyncOperation, "43b2f83d-10f2-48ab-831b-55fdbdbd34a4")
DEFINE_GUIDS(CLSID_PrinterExtensionManager, "331B60DA-9E90-4DD0-9C84-EAC4E659B61F")

endif

DEFINE_GUID(PRINTER_EXTENSION_DETAILEDREASON_PRINTER_STATUS,	0x5d5a1704,0xdfd1,0x4181,0x8e,0xee,0x81,0x5c,0x86,0xed,0xad,0x31)
DEFINE_GUID(PRINTER_EXTENSION_REASON_PRINT_PREFERENCES,		0xec8f261f,0x267c,0x469f,0xb5,0xd6,0x39,0x33,0x02,0x3c,0x29,0xcc)
DEFINE_GUID(PRINTER_EXTENSION_REASON_DRIVER_EVENT,		0x23bb1328,0x63de,0x4293,0x91,0x5b,0xa6,0xa2,0x3d,0x92,0x9a,0xcb)
DEFINE_GUID(FMTID_PrinterPropertyBag,				0x75f9adca,0x097d,0x45c3,0xa6,0xe4,0xba,0xb2,0x9e,0x27,0x6f,0x3e)
endif

endif

