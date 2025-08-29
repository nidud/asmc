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

ifndef __faxcomex_h__
define __faxcomex_h__

include oaidl.inc
include ocidl.inc

include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

define	prv_DEFAULT_PREFETCH_SIZE 100

ifndef __IFaxJobStatus_INTERFACE_DEFINED__
define __IFaxJobStatus_INTERFACE_DEFINED__

.enum FAX_JOB_STATUS_ENUM {
	fjsPENDING	= 0x1,
	fjsINPROGRESS	= 0x2,
	fjsFAILED	= 0x8,
	fjsPAUSED	= 0x10,
	fjsNOLINE	= 0x20,
	fjsRETRYING	= 0x40,
	fjsRETRIES_EXCEEDED	= 0x80,
	fjsCOMPLETED	= 0x100,
	fjsCANCELED	= 0x200,
	fjsCANCELING	= 0x400,
	fjsROUTING	= 0x800
    }

.enum FAX_JOB_EXTENDED_STATUS_ENUM {
	fjesNONE	= 0,
	fjesDISCONNECTED	= ( fjesNONE + 1 ) ,
	fjesINITIALIZING	= ( fjesDISCONNECTED + 1 ) ,
	fjesDIALING	= ( fjesINITIALIZING + 1 ) ,
	fjesTRANSMITTING	= ( fjesDIALING + 1 ) ,
	fjesANSWERED	= ( fjesTRANSMITTING + 1 ) ,
	fjesRECEIVING	= ( fjesANSWERED + 1 ) ,
	fjesLINE_UNAVAILABLE	= ( fjesRECEIVING + 1 ) ,
	fjesBUSY	= ( fjesLINE_UNAVAILABLE + 1 ) ,
	fjesNO_ANSWER	= ( fjesBUSY + 1 ) ,
	fjesBAD_ADDRESS = ( fjesNO_ANSWER + 1 ) ,
	fjesNO_DIAL_TONE	= ( fjesBAD_ADDRESS + 1 ) ,
	fjesFATAL_ERROR = ( fjesNO_DIAL_TONE + 1 ) ,
	fjesCALL_DELAYED	= ( fjesFATAL_ERROR + 1 ) ,
	fjesCALL_BLACKLISTED	= ( fjesCALL_DELAYED + 1 ) ,
	fjesNOT_FAX_CALL	= ( fjesCALL_BLACKLISTED + 1 ) ,
	fjesPARTIALLY_RECEIVED	= ( fjesNOT_FAX_CALL + 1 ) ,
	fjesHANDLED	= ( fjesPARTIALLY_RECEIVED + 1 ) ,
	fjesCALL_COMPLETED	= ( fjesHANDLED + 1 ) ,
	fjesCALL_ABORTED	= ( fjesCALL_COMPLETED + 1 ) ,
	fjesPROPRIETARY = 0x1000000
    }

.enum FAX_JOB_OPERATIONS_ENUM {
	fjoVIEW = 0x1,
	fjoPAUSE	= 0x2,
	fjoRESUME	= 0x4,
	fjoRESTART	= 0x8,
	fjoDELETE	= 0x10,
	fjoRECIPIENT_INFO	= 0x20,
	fjoSENDER_INFO	= 0x40
    }

.enum FAX_JOB_TYPE_ENUM {
	fjtSEND = 0,
	fjtRECEIVE	= ( fjtSEND + 1 ) ,
	fjtROUTING	= ( fjtRECEIVE + 1 )
    }

DEFINE_IIDX(IFaxJobStatus, "8B86F485-FD7F-4824-886B-40C5CAA617CC")

.comdef IFaxJobStatus : public IDispatch
    get_Status		proc :ptr
    get_Pages		proc :ptr
    get_Size		proc :ptr
    get_CurrentPage	proc :ptr
    get_DeviceId	proc :ptr
    get_CSID		proc :ptr
    get_TSID		proc :ptr
    get_ExtendedStatusCode proc :ptr
    get_ExtendedStatus	proc :ptr
    get_AvailableOperations proc :ptr
    get_Retries		proc :ptr
    get_JobType		proc :ptr
    get_ScheduledTime	proc :ptr
    get_TransmissionStart proc :ptr
    get_TransmissionEnd proc :ptr
    get_CallerId	proc :ptr
    get_RoutingInformation proc :ptr
   .ends

endif

ifndef __IFaxServer_INTERFACE_DEFINED__
define __IFaxServer_INTERFACE_DEFINED__

.enum FAX_SERVER_EVENTS_TYPE_ENUM {
	fsetNONE	= 0,
	fsetIN_QUEUE	= 0x1,
	fsetOUT_QUEUE	= 0x2,
	fsetCONFIG	= 0x4,
	fsetACTIVITY	= 0x8,
	fsetQUEUE_STATE = 0x10,
	fsetIN_ARCHIVE	= 0x20,
	fsetOUT_ARCHIVE = 0x40,
	fsetFXSSVC_ENDED	= 0x80,
	fsetDEVICE_STATUS	= 0x100,
	fsetINCOMING_CALL	= 0x200
    }

.enum FAX_SERVER_APIVERSION_ENUM {
	fsAPI_VERSION_0 = 0,
	fsAPI_VERSION_1 = 0x10000,
	fsAPI_VERSION_2 = 0x20000,
	fsAPI_VERSION_3 = 0x30000
    }

DEFINE_IIDX(IFaxServer, "475B6469-90A5-4878-A577-17A86E8E3462")

.comdef IFaxServer : public IDispatch
    Connect		proc :BSTR
    get_ServerName	proc :ptr
    GetDeviceProviders	proc :ptr ptr
    GetDevices		proc :ptr ptr
    get_InboundRouting	proc :ptr ptr
    get_Folders		proc :ptr ptr
    get_LoggingOptions	proc :ptr ptr
    get_MajorVersion	proc :ptr
    get_MinorVersion	proc :ptr
    get_MajorBuild	proc :ptr
    get_MinorBuild	proc :ptr
    get_Debug		proc :ptr
    get_Activity	proc :ptr ptr
    get_OutboundRouting proc :ptr ptr
    get_ReceiptOptions	proc :ptr ptr
    get_Security	proc :ptr ptr
    Disconnect		proc
    GetExtensionProperty proc :BSTR, :ptr
    SetExtensionProperty proc :BSTR, :VARIANT
    ListenToServerEvents proc :FAX_SERVER_EVENTS_TYPE_ENUM
    RegisterDeviceProvider proc :BSTR, :BSTR, :BSTR, :BSTR, :LONG
    UnregisterDeviceProvider proc :BSTR
    RegisterInboundRoutingExtension proc :BSTR, :BSTR, :BSTR, :VARIANT
    UnregisterInboundRoutingExtension proc :BSTR
    get_RegisteredEvents proc :ptr
    get_APIVersion	proc :ptr
   .ends

endif

ifndef __IFaxDeviceProviders_INTERFACE_DEFINED__
define __IFaxDeviceProviders_INTERFACE_DEFINED__

DEFINE_IIDX(IFaxDeviceProviders, "9FB76F62-4C7E-43A5-B6FD-502893F7E13E")

.comdef IFaxDeviceProviders : public IDispatch
    get__NewEnum	proc :ptr ptr
    get_Item		proc :VARIANT, :ptr ptr
    get_Count		proc :ptr
   .ends

endif

ifndef __IFaxDevices_INTERFACE_DEFINED__
define __IFaxDevices_INTERFACE_DEFINED__

DEFINE_IIDX(IFaxDevices, "9E46783E-F34F-482E-A360-0416BECBBD96")

.comdef IFaxDevices : public IDispatch
    get__NewEnum	proc :ptr ptr
    get_Item		proc :VARIANT, :ptr ptr
    get_Count		proc :ptr
    get_ItemById	proc :LONG, :ptr ptr
   .ends

endif

ifndef __IFaxInboundRouting_INTERFACE_DEFINED__
define __IFaxInboundRouting_INTERFACE_DEFINED__

DEFINE_IIDX(IFaxInboundRouting, "8148C20F-9D52-45B1-BF96-38FC12713527")

.comdef IFaxInboundRouting : public IDispatch
    GetExtensions	proc :ptr ptr
    GetMethods		proc :ptr ptr
   .ends

endif

ifndef __IFaxFolders_INTERFACE_DEFINED__
define __IFaxFolders_INTERFACE_DEFINED__

DEFINE_IIDX(IFaxFolders, "DCE3B2A8-A7AB-42BC-9D0A-3149457261A0")

.comdef IFaxFolders : public IDispatch
    get_OutgoingQueue	proc :ptr ptr
    get_IncomingQueue	proc :ptr ptr
    get_IncomingArchive proc :ptr ptr
    get_OutgoingArchive proc :ptr ptr
   .ends

endif

ifndef __IFaxLoggingOptions_INTERFACE_DEFINED__
define __IFaxLoggingOptions_INTERFACE_DEFINED__

DEFINE_IIDX(IFaxLoggingOptions, "34E64FB9-6B31-4D32-8B27-D286C0C33606")

.comdef IFaxLoggingOptions : public IDispatch
    get_EventLogging	proc :ptr ptr
    get_ActivityLogging proc :ptr ptr
   .ends

endif

ifndef __IFaxActivity_INTERFACE_DEFINED__
define __IFaxActivity_INTERFACE_DEFINED__

DEFINE_IIDX(IFaxActivity, "4B106F97-3DF5-40F2-BC3C-44CB8115EBDF")

.comdef IFaxActivity : public IDispatch
    get_IncomingMessages proc :ptr
    get_RoutingMessages proc :ptr
    get_OutgoingMessages proc :ptr
    get_QueuedMessages	proc :ptr
    Refresh		proc
   .ends

endif

ifndef __IFaxOutboundRouting_INTERFACE_DEFINED__
define __IFaxOutboundRouting_INTERFACE_DEFINED__

DEFINE_IIDX(IFaxOutboundRouting, "25DC05A4-9909-41BD-A95B-7E5D1DEC1D43")

.comdef IFaxOutboundRouting : public IDispatch
    GetGroups		proc :ptr ptr
    GetRules		proc :ptr ptr
   .ends

endif

ifndef __IFaxReceiptOptions_INTERFACE_DEFINED__
define __IFaxReceiptOptions_INTERFACE_DEFINED__

.enum FAX_SMTP_AUTHENTICATION_TYPE_ENUM {
	fsatANONYMOUS	= 0,
	fsatBASIC	= ( fsatANONYMOUS + 1 ) ,
	fsatNTLM	= ( fsatBASIC + 1 )
    }

.enum FAX_RECEIPT_TYPE_ENUM {
	frtNONE = 0,
	frtMAIL = 0x1,
	frtMSGBOX	= 0x4
    }

DEFINE_IIDX(IFaxReceiptOptions, "378EFAEB-5FCB-4AFB-B2EE-E16E80614487")

.comdef IFaxReceiptOptions : public IDispatch
    get_AuthenticationType proc :ptr
    put_AuthenticationType proc :FAX_SMTP_AUTHENTICATION_TYPE_ENUM
    get_SMTPServer	proc :ptr
    put_SMTPServer	proc :BSTR
    get_SMTPPort	proc :ptr
    put_SMTPPort	proc :LONG
    get_SMTPSender	proc :ptr
    put_SMTPSender	proc :BSTR
    get_SMTPUser	proc :ptr
    put_SMTPUser	proc :BSTR
    get_AllowedReceipts proc :ptr
    put_AllowedReceipts proc :FAX_RECEIPT_TYPE_ENUM
    get_SMTPPassword	proc :ptr
    put_SMTPPassword	proc :BSTR
    Refresh		proc
    Save		proc
    get_UseForInboundRouting proc :ptr
    put_UseForInboundRouting proc :VARIANT_BOOL
   .ends

endif

ifndef __IFaxSecurity_INTERFACE_DEFINED__
define __IFaxSecurity_INTERFACE_DEFINED__

.enum FAX_ACCESS_RIGHTS_ENUM {
	farSUBMIT_LOW	= 0x1,
	farSUBMIT_NORMAL	= 0x2,
	farSUBMIT_HIGH	= 0x4,
	farQUERY_JOBS	= 0x8,
	farMANAGE_JOBS	= 0x10,
	farQUERY_CONFIG = 0x20,
	farMANAGE_CONFIG	= 0x40,
	farQUERY_IN_ARCHIVE	= 0x80,
	farMANAGE_IN_ARCHIVE	= 0x100,
	farQUERY_OUT_ARCHIVE	= 0x200,
	farMANAGE_OUT_ARCHIVE	= 0x400
    }

DEFINE_IIDX(IFaxSecurity, "77B508C1-09C0-47A2-91EB-FCE7FDF2690E")

.comdef IFaxSecurity : public IDispatch
    get_Descriptor	proc :ptr
    put_Descriptor	proc :VARIANT
    get_GrantedRights	proc :ptr
    Refresh		proc
    Save		proc
    get_InformationType proc :ptr
    put_InformationType proc :LONG
   .ends

endif

ifndef __IFaxDocument_INTERFACE_DEFINED__
define __IFaxDocument_INTERFACE_DEFINED__

.enum FAX_PRIORITY_TYPE_ENUM {
	fptLOW	= 0,
	fptNORMAL	= ( fptLOW + 1 ) ,
	fptHIGH = ( fptNORMAL + 1 )
    }

.enum FAX_COVERPAGE_TYPE_ENUM {
	fcptNONE	= 0,
	fcptLOCAL	= ( fcptNONE + 1 ) ,
	fcptSERVER	= ( fcptLOCAL + 1 )
    }

.enum FAX_SCHEDULE_TYPE_ENUM {
	fstNOW	= 0,
	fstSPECIFIC_TIME	= ( fstNOW + 1 ) ,
	fstDISCOUNT_PERIOD	= ( fstSPECIFIC_TIME + 1 )
    }

DEFINE_IIDX(IFaxDocument, "B207A246-09E3-4A4E-A7DC-FEA31D29458F")

.comdef IFaxDocument : public IDispatch
    get_Body		proc :ptr
    put_Body		proc :BSTR
    get_Sender		proc :ptr ptr
    get_Recipients	proc :ptr ptr
    get_CoverPage	proc :ptr
    put_CoverPage	proc :BSTR
    get_Subject		proc :ptr
    put_Subject		proc :BSTR
    get_Note		proc :ptr
    put_Note		proc :BSTR
    get_ScheduleTime	proc :ptr
    put_ScheduleTime	proc :DATE
    get_ReceiptAddress	proc :ptr
    put_ReceiptAddress	proc :BSTR
    get_DocumentName	proc :ptr
    put_DocumentName	proc :BSTR
    get_CallHandle	proc :ptr
    put_CallHandle	proc :LONG
    get_CoverPageType	proc :ptr
    put_CoverPageType	proc :FAX_COVERPAGE_TYPE_ENUM
    get_ScheduleType	proc :ptr
    put_ScheduleType	proc :FAX_SCHEDULE_TYPE_ENUM
    get_ReceiptType	proc :ptr
    put_ReceiptType	proc :FAX_RECEIPT_TYPE_ENUM
    get_GroupBroadcastReceipts proc :ptr
    put_GroupBroadcastReceipts proc :VARIANT_BOOL
    get_Priority	proc :ptr
    put_Priority	proc :FAX_PRIORITY_TYPE_ENUM
    get_TapiConnection	proc :ptr ptr
    putref_TapiConnection proc :ptr
    Submit		proc :BSTR, :ptr
    ConnectedSubmit	proc :ptr, :ptr
    get_AttachFaxToReceipt proc :ptr
    put_AttachFaxToReceipt proc :VARIANT_BOOL
   .ends

endif

ifndef __IFaxSender_INTERFACE_DEFINED__
define __IFaxSender_INTERFACE_DEFINED__

DEFINE_IIDX(IFaxSender, "0D879D7D-F57A-4CC6-A6F9-3EE5D527B46A")

.comdef IFaxSender : public IDispatch
    get_BillingCode	proc :ptr
    put_BillingCode	proc :BSTR
    get_City		proc :ptr
    put_City		proc :BSTR
    get_Company		proc :ptr
    put_Company		proc :BSTR
    get_Country		proc :ptr
    put_Country		proc :BSTR
    get_Department	proc :ptr
    put_Department	proc :BSTR
    get_Email		proc :ptr
    put_Email		proc :BSTR
    get_FaxNumber	proc :ptr
    put_FaxNumber	proc :BSTR
    get_HomePhone	proc :ptr
    put_HomePhone	proc :BSTR
    get_Name		proc :ptr
    put_Name		proc :BSTR
    get_TSID		proc :ptr
    put_TSID		proc :BSTR
    get_OfficePhone	proc :ptr
    put_OfficePhone	proc :BSTR
    get_OfficeLocation	proc :ptr
    put_OfficeLocation	proc :BSTR
    get_State		proc :ptr
    put_State		proc :BSTR
    get_StreetAddress	proc :ptr
    put_StreetAddress	proc :BSTR
    get_Title		proc :ptr
    put_Title		proc :BSTR
    get_ZipCode		proc :ptr
    put_ZipCode		proc :BSTR
    LoadDefaultSender	proc
    SaveDefaultSender	proc
   .ends

endif

ifndef __IFaxRecipient_INTERFACE_DEFINED__
define __IFaxRecipient_INTERFACE_DEFINED__

DEFINE_IIDX(IFaxRecipient, "9A3DA3A0-538D-42b6-9444-AAA57D0CE2BC")

.comdef IFaxRecipient : public IDispatch
    get_FaxNumber	proc :ptr
    put_FaxNumber	proc :BSTR
    get_Name		proc :ptr
    put_Name		proc :BSTR
   .ends

endif

ifndef __IFaxRecipients_INTERFACE_DEFINED__
define __IFaxRecipients_INTERFACE_DEFINED__

DEFINE_IIDX(IFaxRecipients, "B9C9DE5A-894E-4492-9FA3-08C627C11D5D")

.comdef IFaxRecipients : public IDispatch
    get__NewEnum	proc :ptr ptr
    get_Item		proc :LONG, :ptr ptr
    get_Count		proc :ptr
    _Add		proc :BSTR, :BSTR, :ptr ptr
    Remove		proc :LONG
   .ends

endif

ifndef __IFaxIncomingArchive_INTERFACE_DEFINED__
define __IFaxIncomingArchive_INTERFACE_DEFINED__

DEFINE_IIDX(IFaxIncomingArchive, "76062CC7-F714-4FBD-AA06-ED6E4A4B70F3")

.comdef IFaxIncomingArchive : public IDispatch
    get_UseArchive	proc :ptr
    put_UseArchive	proc :VARIANT_BOOL
    get_ArchiveFolder	proc :ptr
    put_ArchiveFolder	proc :BSTR
    get_SizeQuotaWarning proc :ptr
    put_SizeQuotaWarning proc :VARIANT_BOOL
    get_HighQuotaWaterMark proc :ptr
    put_HighQuotaWaterMark proc :LONG
    get_LowQuotaWaterMark proc :ptr
    put_LowQuotaWaterMark proc :LONG
    get_AgeLimit	proc :ptr
    put_AgeLimit	proc :LONG
    get_SizeLow		proc :ptr
    get_SizeHigh	proc :ptr
    Refresh		proc
    Save		proc
    GetMessages		proc :LONG, :ptr ptr
    GetMessage		proc :BSTR, :ptr ptr
   .ends

endif

ifndef __IFaxIncomingQueue_INTERFACE_DEFINED__
define __IFaxIncomingQueue_INTERFACE_DEFINED__

DEFINE_IIDX(IFaxIncomingQueue, "902E64EF-8FD8-4B75-9725-6014DF161545")

.comdef IFaxIncomingQueue : public IDispatch
    get_Blocked		proc :ptr
    put_Blocked		proc :VARIANT_BOOL
    Refresh		proc
    Save		proc
    GetJobs		proc :ptr ptr
    GetJob		proc :BSTR, :ptr ptr
   .ends

endif

ifndef __IFaxOutgoingArchive_INTERFACE_DEFINED__
define __IFaxOutgoingArchive_INTERFACE_DEFINED__

DEFINE_IIDX(IFaxOutgoingArchive, "C9C28F40-8D80-4E53-810F-9A79919B49FD")

.comdef IFaxOutgoingArchive : public IDispatch
    get_UseArchive	proc :ptr
    put_UseArchive	proc :VARIANT_BOOL
    get_ArchiveFolder	proc :ptr
    put_ArchiveFolder	proc :BSTR
    get_SizeQuotaWarning proc :ptr
    put_SizeQuotaWarning proc :VARIANT_BOOL
    get_HighQuotaWaterMark proc :ptr
    put_HighQuotaWaterMark proc :LONG
    get_LowQuotaWaterMark proc :ptr
    put_LowQuotaWaterMark proc :LONG
    get_AgeLimit	proc :ptr
    put_AgeLimit	proc :LONG
    get_SizeLow		proc :ptr
    get_SizeHigh	proc :ptr
    Refresh		proc
    Save		proc
    GetMessages		proc :LONG, :ptr ptr
    GetMessage		proc :BSTR, :ptr ptr
   .ends

endif

ifndef __IFaxOutgoingQueue_INTERFACE_DEFINED__
define __IFaxOutgoingQueue_INTERFACE_DEFINED__

DEFINE_IIDX(IFaxOutgoingQueue, "80B1DF24-D9AC-4333-B373-487CEDC80CE5")

.comdef IFaxOutgoingQueue : public IDispatch
    get_Blocked		proc :ptr
    put_Blocked		proc :VARIANT_BOOL
    get_Paused		proc :ptr
    put_Paused		proc :VARIANT_BOOL
    get_AllowPersonalCoverPages proc :ptr
    put_AllowPersonalCoverPages proc :VARIANT_BOOL
    get_UseDeviceTSID	proc :ptr
    put_UseDeviceTSID	proc :VARIANT_BOOL
    get_Retries		proc :ptr
    put_Retries		proc :LONG
    get_RetryDelay	proc :ptr
    put_RetryDelay	proc :LONG
    get_DiscountRateStart proc :ptr
    put_DiscountRateStart proc :DATE
    get_DiscountRateEnd proc :ptr
    put_DiscountRateEnd proc :DATE
    get_AgeLimit	proc :ptr
    put_AgeLimit	proc :LONG
    get_Branding	proc :ptr
    put_Branding	proc :VARIANT_BOOL
    Refresh		proc
    Save		proc
    GetJobs		proc :ptr ptr
    GetJob		proc :BSTR, :ptr ptr
   .ends

endif

ifndef __IFaxIncomingMessageIterator_INTERFACE_DEFINED__
define __IFaxIncomingMessageIterator_INTERFACE_DEFINED__

DEFINE_IIDX(IFaxIncomingMessageIterator, "FD73ECC4-6F06-4F52-82A8-F7BA06AE3108")

.comdef IFaxIncomingMessageIterator : public IDispatch
    get_Message		proc :ptr ptr
    get_PrefetchSize	proc :ptr
    put_PrefetchSize	proc :LONG
    get_AtEOF		proc :ptr
    MoveFirst		proc
    MoveNext		proc
   .ends

endif

ifndef __IFaxIncomingMessage_INTERFACE_DEFINED__
define __IFaxIncomingMessage_INTERFACE_DEFINED__

DEFINE_IIDX(IFaxIncomingMessage, "7CAB88FA-2EF9-4851-B2F3-1D148FED8447")

.comdef IFaxIncomingMessage : public IDispatch
    get_Id		proc :ptr
    get_Pages		proc :ptr
    get_Size		proc :ptr
    get_DeviceName	proc :ptr
    get_Retries		proc :ptr
    get_TransmissionStart proc :ptr
    get_TransmissionEnd proc :ptr
    get_CSID		proc :ptr
    get_TSID		proc :ptr
    get_CallerId	proc :ptr
    get_RoutingInformation proc :ptr
    CopyTiff		proc :BSTR
    Delete		proc
   .ends

endif

ifndef __IFaxOutgoingJobs_INTERFACE_DEFINED__
define __IFaxOutgoingJobs_INTERFACE_DEFINED__

DEFINE_IIDX(IFaxOutgoingJobs, "2C56D8E6-8C2F-4573-944C-E505F8F5AEED")

.comdef IFaxOutgoingJobs : public IDispatch
    get__NewEnum	proc :ptr ptr
    get_Item		proc :VARIANT, :ptr ptr
    get_Count		proc :ptr
   .ends

endif

ifndef __IFaxOutgoingJob_INTERFACE_DEFINED__
define __IFaxOutgoingJob_INTERFACE_DEFINED__

DEFINE_IIDX(IFaxOutgoingJob, "6356DAAD-6614-4583-BF7A-3AD67BBFC71C")

.comdef IFaxOutgoingJob : public IDispatch
    get_Subject		proc :ptr
    get_DocumentName	proc :ptr
    get_Pages		proc :ptr
    get_Size		proc :ptr
    get_SubmissionId	proc :ptr
    get_Id		proc :ptr
    get_OriginalScheduledTime proc :ptr
    get_SubmissionTime	proc :ptr
    get_ReceiptType	proc :ptr
    get_Priority	proc :ptr
    get_Sender		proc :ptr ptr
    get_Recipient	proc :ptr ptr
    get_CurrentPage	proc :ptr
    get_DeviceId	proc :ptr
    get_Status		proc :ptr
    get_ExtendedStatusCode proc :ptr
    get_ExtendedStatus	proc :ptr
    get_AvailableOperations proc :ptr
    get_Retries		proc :ptr
    get_ScheduledTime	proc :ptr
    get_TransmissionStart proc :ptr
    get_TransmissionEnd proc :ptr
    get_CSID		proc :ptr
    get_TSID		proc :ptr
    get_GroupBroadcastReceipts proc :ptr
    _Pause		proc
    Resume		proc
    Restart		proc
    CopyTiff		proc :BSTR
    Refresh		proc
    Cancel		proc
   .ends

endif

ifndef __IFaxOutgoingMessageIterator_INTERFACE_DEFINED__
define __IFaxOutgoingMessageIterator_INTERFACE_DEFINED__

DEFINE_IIDX(IFaxOutgoingMessageIterator, "F5EC5D4F-B840-432F-9980-112FE42A9B7A")

.comdef IFaxOutgoingMessageIterator : public IDispatch
    get_Message		proc :ptr ptr
    get_AtEOF		proc :ptr
    get_PrefetchSize	proc :ptr
    put_PrefetchSize	proc :LONG
    MoveFirst		proc
    MoveNext		proc
   .ends

endif

ifndef __IFaxOutgoingMessage_INTERFACE_DEFINED__
define __IFaxOutgoingMessage_INTERFACE_DEFINED__

DEFINE_IIDX(IFaxOutgoingMessage, "F0EA35DE-CAA5-4A7C-82C7-2B60BA5F2BE2")

.comdef IFaxOutgoingMessage : public IDispatch
    get_SubmissionId	proc :ptr
    get_Id		proc :ptr
    get_Subject		proc :ptr
    get_DocumentName	proc :ptr
    get_Retries		proc :ptr
    get_Pages		proc :ptr
    get_Size		proc :ptr
    get_OriginalScheduledTime proc :ptr
    get_SubmissionTime	proc :ptr
    get_Priority	proc :ptr
    get_Sender		proc :ptr ptr
    get_Recipient	proc :ptr ptr
    get_DeviceName	proc :ptr
    get_TransmissionStart proc :ptr
    get_TransmissionEnd proc :ptr
    get_CSID		proc :ptr
    get_TSID		proc :ptr
    CopyTiff		proc :BSTR
    Delete		proc
   .ends

endif

ifndef __IFaxIncomingJobs_INTERFACE_DEFINED__
define __IFaxIncomingJobs_INTERFACE_DEFINED__

DEFINE_IIDX(IFaxIncomingJobs, "011F04E9-4FD6-4C23-9513-B6B66BB26BE9")

.comdef IFaxIncomingJobs : public IDispatch
    get__NewEnum	proc :ptr ptr
    get_Item		proc :VARIANT, :ptr ptr
    get_Count		proc :ptr
   .ends

endif

ifndef __IFaxIncomingJob_INTERFACE_DEFINED__
define __IFaxIncomingJob_INTERFACE_DEFINED__

DEFINE_IIDX(IFaxIncomingJob, "207529E6-654A-4916-9F88-4D232EE8A107")

.comdef IFaxIncomingJob : public IDispatch
    get_Size		proc :ptr
    get_Id		proc :ptr
    get_CurrentPage	proc :ptr
    get_DeviceId	proc :ptr
    get_Status		proc :ptr
    get_ExtendedStatusCode proc :ptr
    get_ExtendedStatus	proc :ptr
    get_AvailableOperations proc :ptr
    get_Retries		proc :ptr
    get_TransmissionStart proc :ptr
    get_TransmissionEnd proc :ptr
    get_CSID		proc :ptr
    get_TSID		proc :ptr
    get_CallerId	proc :ptr
    get_RoutingInformation proc :ptr
    get_JobType		proc :ptr
    Cancel		proc
    Refresh		proc
    CopyTiff		proc :BSTR
   .ends

endif

ifndef __IFaxDeviceProvider_INTERFACE_DEFINED__
define __IFaxDeviceProvider_INTERFACE_DEFINED__

.enum FAX_PROVIDER_STATUS_ENUM {
	fpsSUCCESS	= 0,
	fpsSERVER_ERROR = ( fpsSUCCESS + 1 ) ,
	fpsBAD_GUID	= ( fpsSERVER_ERROR + 1 ) ,
	fpsBAD_VERSION	= ( fpsBAD_GUID + 1 ) ,
	fpsCANT_LOAD	= ( fpsBAD_VERSION + 1 ) ,
	fpsCANT_LINK	= ( fpsCANT_LOAD + 1 ) ,
	fpsCANT_INIT	= ( fpsCANT_LINK + 1 )
    }

DEFINE_IIDX(IFaxDeviceProvider, "290EAC63-83EC-449C-8417-F148DF8C682A")

.comdef IFaxDeviceProvider : public IDispatch
    get_FriendlyName	proc :ptr
    get_ImageName	proc :ptr
    get_UniqueName	proc :ptr
    get_TapiProviderName proc :ptr
    get_MajorVersion	proc :ptr
    get_MinorVersion	proc :ptr
    get_MajorBuild	proc :ptr
    get_MinorBuild	proc :ptr
    get_Debug		proc :ptr
    get_Status		proc :ptr
    get_InitErrorCode	proc :ptr
    get_DeviceIds	proc :ptr
   .ends

endif

ifndef __IFaxDevice_INTERFACE_DEFINED__
define __IFaxDevice_INTERFACE_DEFINED__

.enum FAX_DEVICE_RECEIVE_MODE_ENUM {
	fdrmNO_ANSWER	= 0,
	fdrmAUTO_ANSWER = ( fdrmNO_ANSWER + 1 ) ,
	fdrmMANUAL_ANSWER	= ( fdrmAUTO_ANSWER + 1 )
    }

DEFINE_IIDX(IFaxDevice, "49306C59-B52E-4867-9DF4-CA5841C956D0")

.comdef IFaxDevice : public IDispatch
    get_Id		proc :ptr
    get_DeviceName	proc :ptr
    get_ProviderUniqueName proc :ptr
    get_PoweredOff	proc :ptr
    get_ReceivingNow	proc :ptr
    get_SendingNow	proc :ptr
    get_UsedRoutingMethods proc :ptr
    get_Description	proc :ptr
    put_Description	proc :BSTR
    get_SendEnabled	proc :ptr
    put_SendEnabled	proc :VARIANT_BOOL
    get_ReceiveMode	proc :ptr
    put_ReceiveMode	proc :FAX_DEVICE_RECEIVE_MODE_ENUM
    get_RingsBeforeAnswer proc :ptr
    put_RingsBeforeAnswer proc :LONG
    get_CSID		proc :ptr
    put_CSID		proc :BSTR
    get_TSID		proc :ptr
    put_TSID		proc :BSTR
    Refresh		proc
    Save		proc
    GetExtensionProperty proc :BSTR, :ptr
    SetExtensionProperty proc :BSTR, :VARIANT
    UseRoutingMethod	proc :BSTR, :VARIANT_BOOL
    get_RingingNow	proc :ptr
    AnswerCall		proc
   .ends

endif

ifndef __IFaxActivityLogging_INTERFACE_DEFINED__
define __IFaxActivityLogging_INTERFACE_DEFINED__

DEFINE_IIDX(IFaxActivityLogging, "1E29078B-5A69-497B-9592-49B7E7FADDB5")

.comdef IFaxActivityLogging : public IDispatch
    get_LogIncoming	proc :ptr
    put_LogIncoming	proc :VARIANT_BOOL
    get_LogOutgoing	proc :ptr
    put_LogOutgoing	proc :VARIANT_BOOL
    get_DatabasePath	proc :ptr
    put_DatabasePath	proc :BSTR
    Refresh		proc
    Save		proc
   .ends

endif

ifndef __IFaxEventLogging_INTERFACE_DEFINED__
define __IFaxEventLogging_INTERFACE_DEFINED__

.enum FAX_LOG_LEVEL_ENUM {
	fllNONE = 0,
	fllMIN	= ( fllNONE + 1 ) ,
	fllMED	= ( fllMIN + 1 ) ,
	fllMAX	= ( fllMED + 1 )
    }

DEFINE_IIDX(IFaxEventLogging, "0880D965-20E8-42E4-8E17-944F192CAAD4")

.comdef IFaxEventLogging : public IDispatch
    get_InitEventsLevel proc :ptr
    put_InitEventsLevel proc :FAX_LOG_LEVEL_ENUM
    get_InboundEventsLevel proc :ptr
    put_InboundEventsLevel proc :FAX_LOG_LEVEL_ENUM
    get_OutboundEventsLevel proc :ptr
    put_OutboundEventsLevel proc :FAX_LOG_LEVEL_ENUM
    get_GeneralEventsLevel proc :ptr
    put_GeneralEventsLevel proc :FAX_LOG_LEVEL_ENUM
    Refresh		proc
    Save		proc
   .ends

endif

ifndef __IFaxOutboundRoutingGroups_INTERFACE_DEFINED__
define __IFaxOutboundRoutingGroups_INTERFACE_DEFINED__

DEFINE_IIDX(IFaxOutboundRoutingGroups, "235CBEF7-C2DE-4BFD-B8DA-75097C82C87F")

.comdef IFaxOutboundRoutingGroups : public IDispatch
    get__NewEnum	proc :ptr ptr
    get_Item		proc :VARIANT, :ptr ptr
    get_Count		proc :ptr
    _Add		proc :BSTR, :ptr ptr
    Remove		proc :VARIANT
   .ends

endif

ifndef __IFaxOutboundRoutingGroup_INTERFACE_DEFINED__
define __IFaxOutboundRoutingGroup_INTERFACE_DEFINED__

.enum FAX_GROUP_STATUS_ENUM {
	fgsALL_DEV_VALID	= 0,
	fgsEMPTY	= ( fgsALL_DEV_VALID + 1 ) ,
	fgsALL_DEV_NOT_VALID	= ( fgsEMPTY + 1 ) ,
	fgsSOME_DEV_NOT_VALID	= ( fgsALL_DEV_NOT_VALID + 1 )
    }

DEFINE_IIDX(IFaxOutboundRoutingGroup, "CA6289A1-7E25-4F87-9A0B-93365734962C")

.comdef IFaxOutboundRoutingGroup : public IDispatch
    get_Name		proc :ptr
    get_Status		proc :ptr
    get_DeviceIds	proc :ptr ptr
   .ends

endif

ifndef __IFaxDeviceIds_INTERFACE_DEFINED__
define __IFaxDeviceIds_INTERFACE_DEFINED__

DEFINE_IIDX(IFaxDeviceIds, "2F0F813F-4CE9-443E-8CA1-738CFAEEE149")

.comdef IFaxDeviceIds : public IDispatch
    get__NewEnum	proc :ptr ptr
    get_Item		proc :LONG, :ptr
    get_Count		proc :ptr
    _Add		proc :LONG
    Remove		proc :LONG
    SetOrder		proc :LONG, :LONG
   .ends

endif

ifndef __IFaxOutboundRoutingRules_INTERFACE_DEFINED__
define __IFaxOutboundRoutingRules_INTERFACE_DEFINED__

DEFINE_IIDX(IFaxOutboundRoutingRules, "DCEFA1E7-AE7D-4ED6-8521-369EDCCA5120")

.comdef IFaxOutboundRoutingRules : public IDispatch
    get__NewEnum	proc :ptr ptr
    get_Item		proc :LONG, :ptr ptr
    get_Count		proc :ptr
    ItemByCountryAndArea proc :LONG, :LONG, :ptr ptr
    RemoveByCountryAndArea proc :LONG, :LONG
    Remove		proc :LONG
    _Add		proc :LONG, :LONG, :VARIANT_BOOL, :BSTR, :LONG, :ptr ptr
   .ends

endif

ifndef __IFaxOutboundRoutingRule_INTERFACE_DEFINED__
define __IFaxOutboundRoutingRule_INTERFACE_DEFINED__

.enum FAX_RULE_STATUS_ENUM {
	frsVALID	= 0,
	frsEMPTY_GROUP	= ( frsVALID + 1 ) ,
	frsALL_GROUP_DEV_NOT_VALID	= ( frsEMPTY_GROUP + 1 ) ,
	frsSOME_GROUP_DEV_NOT_VALID	= ( frsALL_GROUP_DEV_NOT_VALID + 1 ) ,
	frsBAD_DEVICE	= ( frsSOME_GROUP_DEV_NOT_VALID + 1 )
    }

DEFINE_IIDX(IFaxOutboundRoutingRule, "E1F795D5-07C2-469F-B027-ACACC23219DA")

.comdef IFaxOutboundRoutingRule : public IDispatch
    get_CountryCode	proc :ptr
    get_AreaCode	proc :ptr
    get_Status		proc :ptr
    get_UseDevice	proc :ptr
    put_UseDevice	proc :VARIANT_BOOL
    get_DeviceId	proc :ptr
    put_DeviceId	proc :LONG
    get_GroupName	proc :ptr
    put_GroupName	proc :BSTR
    Refresh		proc
    Save		proc
   .ends

endif

ifndef __IFaxInboundRoutingExtensions_INTERFACE_DEFINED__
define __IFaxInboundRoutingExtensions_INTERFACE_DEFINED__

DEFINE_IIDX(IFaxInboundRoutingExtensions, "2F6C9673-7B26-42DE-8EB0-915DCD2A4F4C")

.comdef IFaxInboundRoutingExtensions : public IDispatch
    get__NewEnum	proc :ptr ptr
    get_Item		proc :VARIANT, :ptr ptr
    get_Count		proc :ptr
   .ends

endif

ifndef __IFaxInboundRoutingExtension_INTERFACE_DEFINED__
define __IFaxInboundRoutingExtension_INTERFACE_DEFINED__

DEFINE_IIDX(IFaxInboundRoutingExtension, "885B5E08-C26C-4EF9-AF83-51580A750BE1")

.comdef IFaxInboundRoutingExtension : public IDispatch
    get_FriendlyName	proc :ptr
    get_ImageName	proc :ptr
    get_UniqueName	proc :ptr
    get_MajorVersion	proc :ptr
    get_MinorVersion	proc :ptr
    get_MajorBuild	proc :ptr
    get_MinorBuild	proc :ptr
    get_Debug		proc :ptr
    get_Status		proc :ptr
    get_InitErrorCode	proc :ptr
    get_Methods		proc :ptr
   .ends

endif

ifndef __IFaxInboundRoutingMethods_INTERFACE_DEFINED__
define __IFaxInboundRoutingMethods_INTERFACE_DEFINED__

DEFINE_IIDX(IFaxInboundRoutingMethods, "783FCA10-8908-4473-9D69-F67FBEA0C6B9")

.comdef IFaxInboundRoutingMethods : public IDispatch
    get__NewEnum	proc :ptr ptr
    get_Item		proc :VARIANT, :ptr ptr
    get_Count		proc :ptr
   .ends

endif

ifndef __IFaxInboundRoutingMethod_INTERFACE_DEFINED__
define __IFaxInboundRoutingMethod_INTERFACE_DEFINED__

DEFINE_IIDX(IFaxInboundRoutingMethod, "45700061-AD9D-4776-A8C4-64065492CF4B")

.comdef IFaxInboundRoutingMethod : public IDispatch
    get_Name		proc :ptr
    get_GUID		proc :ptr
    get_FunctionName	proc :ptr
    get_ExtensionFriendlyName proc :ptr
    get_ExtensionImageName proc :ptr
    get_Priority	proc :ptr
    put_Priority	proc :LONG
    Refresh		proc
    Save		proc
   .ends

endif

ifndef __IFaxDocument2_INTERFACE_DEFINED__
define __IFaxDocument2_INTERFACE_DEFINED__

DEFINE_IIDX(IFaxDocument2, "e1347661-f9ef-4d6d-b4a5-c0a068b65cff")

.comdef IFaxDocument2 : public IFaxDocument
    get_SubmissionId	proc :ptr
    get_Bodies		proc :ptr
    put_Bodies		proc :VARIANT
    Submit2		proc :BSTR, :ptr, :ptr
    ConnectedSubmit2	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef __IFaxConfiguration_INTERFACE_DEFINED__
define __IFaxConfiguration_INTERFACE_DEFINED__

DEFINE_IIDX(IFaxConfiguration, "10f4d0f7-0994-4543-ab6e-506949128c40")

.comdef IFaxConfiguration : public IDispatch
    get_UseArchive	proc :ptr
    put_UseArchive	proc :VARIANT_BOOL
    get_ArchiveLocation proc :ptr
    put_ArchiveLocation proc :BSTR
    get_SizeQuotaWarning proc :ptr
    put_SizeQuotaWarning proc :VARIANT_BOOL
    get_HighQuotaWaterMark proc :ptr
    put_HighQuotaWaterMark proc :LONG
    get_LowQuotaWaterMark proc :ptr
    put_LowQuotaWaterMark proc :LONG
    get_ArchiveAgeLimit proc :ptr
    put_ArchiveAgeLimit proc :LONG
    get_ArchiveSizeLow	proc :ptr
    get_ArchiveSizeHigh proc :ptr
    get_OutgoingQueueBlocked proc :ptr
    put_OutgoingQueueBlocked proc :VARIANT_BOOL
    get_OutgoingQueuePaused proc :ptr
    put_OutgoingQueuePaused proc :VARIANT_BOOL
    get_AllowPersonalCoverPages proc :ptr
    put_AllowPersonalCoverPages proc :VARIANT_BOOL
    get_UseDeviceTSID	proc :ptr
    put_UseDeviceTSID	proc :VARIANT_BOOL
    get_Retries		proc :ptr
    put_Retries		proc :LONG
    get_RetryDelay	proc :ptr
    put_RetryDelay	proc :LONG
    get_DiscountRateStart proc :ptr
    put_DiscountRateStart proc :DATE
    get_DiscountRateEnd proc :ptr
    put_DiscountRateEnd proc :DATE
    get_OutgoingQueueAgeLimit proc :ptr
    put_OutgoingQueueAgeLimit proc :LONG
    get_Branding	proc :ptr
    put_Branding	proc :VARIANT_BOOL
    get_IncomingQueueBlocked proc :ptr
    put_IncomingQueueBlocked proc :VARIANT_BOOL
    get_AutoCreateAccountOnConnect proc :ptr
    put_AutoCreateAccountOnConnect proc :VARIANT_BOOL
    get_IncomingFaxesArePublic proc :ptr
    put_IncomingFaxesArePublic proc :VARIANT_BOOL
    Refresh		proc
    Save		proc
   .ends

endif

ifndef __IFaxServer2_INTERFACE_DEFINED__
define __IFaxServer2_INTERFACE_DEFINED__

DEFINE_IIDX(IFaxServer2, "571ced0f-5609-4f40-9176-547e3a72ca7c")

.comdef IFaxServer2 : public IFaxServer
    get_Configuration	proc :ptr ptr
    get_CurrentAccount	proc :ptr ptr
    get_FaxAccountSet	proc :ptr ptr
    get_Security2	proc :ptr ptr
   .ends

endif

ifndef __IFaxAccountSet_INTERFACE_DEFINED__
define __IFaxAccountSet_INTERFACE_DEFINED__

DEFINE_IIDX(IFaxAccountSet, "7428fbae-841e-47b8-86f4-2288946dca1b")

.comdef IFaxAccountSet : public IDispatch
    GetAccounts		proc :ptr ptr
    GetAccount		proc :BSTR, :ptr ptr
    AddAccount		proc :BSTR, :ptr ptr
    RemoveAccount	proc :BSTR
   .ends

endif

ifndef __IFaxAccounts_INTERFACE_DEFINED__
define __IFaxAccounts_INTERFACE_DEFINED__

DEFINE_IIDX(IFaxAccounts, "93ea8162-8be7-42d1-ae7b-ec74e2d989da")

.comdef IFaxAccounts : public IDispatch
    get__NewEnum	proc :ptr ptr
    get_Item		proc :VARIANT, :ptr ptr
    get_Count		proc :ptr
   .ends

endif

ifndef __IFaxAccount_INTERFACE_DEFINED__
define __IFaxAccount_INTERFACE_DEFINED__

.enum FAX_ACCOUNT_EVENTS_TYPE_ENUM {
	faetNONE	= 0,
	faetIN_QUEUE	= 0x1,
	faetOUT_QUEUE	= 0x2,
	faetIN_ARCHIVE	= 0x4,
	faetOUT_ARCHIVE = 0x8,
	faetFXSSVC_ENDED	= 0x10
    }

DEFINE_IIDX(IFaxAccount, "68535b33-5dc4-4086-be26-b76f9b711006")

.comdef IFaxAccount : public IDispatch
    get_AccountName	proc :ptr
    get_Folders		proc :ptr ptr
    ListenToAccountEvents proc :FAX_ACCOUNT_EVENTS_TYPE_ENUM
    get_RegisteredEvents proc :ptr
   .ends

endif

ifndef __IFaxOutgoingJob2_INTERFACE_DEFINED__
define __IFaxOutgoingJob2_INTERFACE_DEFINED__

DEFINE_IIDX(IFaxOutgoingJob2, "418a8d96-59a0-4789-b176-edf3dc8fa8f7")

.comdef IFaxOutgoingJob2 : public IFaxOutgoingJob
    get_HasCoverPage	proc :ptr
    get_ReceiptAddress	proc :ptr
    get_ScheduleType	proc :ptr
   .ends

endif

ifndef __IFaxAccountFolders_INTERFACE_DEFINED__
define __IFaxAccountFolders_INTERFACE_DEFINED__

DEFINE_IIDX(IFaxAccountFolders, "6463f89d-23d8-46a9-8f86-c47b77ca7926")

.comdef IFaxAccountFolders : public IDispatch
    get_OutgoingQueue	proc :ptr ptr
    get_IncomingQueue	proc :ptr ptr
    get_IncomingArchive proc :ptr ptr
    get_OutgoingArchive proc :ptr ptr
   .ends

endif

ifndef __IFaxAccountIncomingQueue_INTERFACE_DEFINED__
define __IFaxAccountIncomingQueue_INTERFACE_DEFINED__

DEFINE_IIDX(IFaxAccountIncomingQueue, "dd142d92-0186-4a95-a090-cbc3eadba6b4")

.comdef IFaxAccountIncomingQueue : public IDispatch
    GetJobs		proc :ptr ptr
    GetJob		proc :BSTR, :ptr ptr
   .ends

endif

ifndef __IFaxAccountOutgoingQueue_INTERFACE_DEFINED__
define __IFaxAccountOutgoingQueue_INTERFACE_DEFINED__

DEFINE_IIDX(IFaxAccountOutgoingQueue, "0f1424e9-f22d-4553-b7a5-0d24bd0d7e46")

.comdef IFaxAccountOutgoingQueue : public IDispatch
    GetJobs		proc :ptr ptr
    GetJob		proc :BSTR, :ptr ptr
   .ends

endif

ifndef __IFaxOutgoingMessage2_INTERFACE_DEFINED__
define __IFaxOutgoingMessage2_INTERFACE_DEFINED__

DEFINE_IIDX(IFaxOutgoingMessage2, "b37df687-bc88-4b46-b3be-b458b3ea9e7f")

.comdef IFaxOutgoingMessage2 : public IFaxOutgoingMessage
    get_HasCoverPage	proc :ptr
    get_ReceiptType	proc :ptr
    get_ReceiptAddress	proc :ptr
    get_Read		proc :ptr
    put_Read		proc :VARIANT_BOOL
    Save		proc
    Refresh		proc
   .ends

endif

ifndef __IFaxAccountIncomingArchive_INTERFACE_DEFINED__
define __IFaxAccountIncomingArchive_INTERFACE_DEFINED__

DEFINE_IIDX(IFaxAccountIncomingArchive, "a8a5b6ef-e0d6-4aee-955c-91625bec9db4")

.comdef IFaxAccountIncomingArchive : public IDispatch
    get_SizeLow		proc :ptr
    get_SizeHigh	proc :ptr
    Refresh		proc
    GetMessages		proc :LONG, :ptr ptr
    GetMessage		proc :BSTR, :ptr ptr
   .ends

endif

ifndef __IFaxAccountOutgoingArchive_INTERFACE_DEFINED__
define __IFaxAccountOutgoingArchive_INTERFACE_DEFINED__

DEFINE_IIDX(IFaxAccountOutgoingArchive, "5463076d-ec14-491f-926e-b3ceda5e5662")

.comdef IFaxAccountOutgoingArchive : public IDispatch
    get_SizeLow		proc :ptr
    get_SizeHigh	proc :ptr
    Refresh		proc
    GetMessages		proc :LONG, :ptr ptr
    GetMessage		proc :BSTR, :ptr ptr
   .ends

endif

ifndef __IFaxSecurity2_INTERFACE_DEFINED__
define __IFaxSecurity2_INTERFACE_DEFINED__

.enum FAX_ACCESS_RIGHTS_ENUM_2 {
	far2SUBMIT_LOW	= 0x1,
	far2SUBMIT_NORMAL	= 0x2,
	far2SUBMIT_HIGH = 0x4,
	far2QUERY_OUT_JOBS	= 0x8,
	far2MANAGE_OUT_JOBS	= 0x10,
	far2QUERY_CONFIG	= 0x20,
	far2MANAGE_CONFIG	= 0x40,
	far2QUERY_ARCHIVES	= 0x80,
	far2MANAGE_ARCHIVES	= 0x100,
	far2MANAGE_RECEIVE_FOLDER	= 0x200
    }

DEFINE_IIDX(IFaxSecurity2, "17d851f4-d09b-48fc-99c9-8f24c4db9ab1")

.comdef IFaxSecurity2 : public IDispatch
    get_Descriptor	proc :ptr
    put_Descriptor	proc :VARIANT
    get_GrantedRights	proc :ptr
    Refresh		proc
    Save		proc
    get_InformationType proc :ptr
    put_InformationType proc :LONG
   .ends

endif

ifndef __IFaxIncomingMessage2_INTERFACE_DEFINED__
define __IFaxIncomingMessage2_INTERFACE_DEFINED__

DEFINE_IIDX(IFaxIncomingMessage2, "f9208503-e2bc-48f3-9ec0-e6236f9b509a")

.comdef IFaxIncomingMessage2 : public IFaxIncomingMessage
    get_Subject		proc :ptr
    put_Subject		proc :BSTR
    get_SenderName	proc :ptr
    put_SenderName	proc :BSTR
    get_SenderFaxNumber proc :ptr
    put_SenderFaxNumber proc :BSTR
    get_HasCoverPage	proc :ptr
    put_HasCoverPage	proc :VARIANT_BOOL
    get_Recipients	proc :ptr
    put_Recipients	proc :BSTR
    get_WasReAssigned	proc :ptr
    get_Read		proc :ptr
    put_Read		proc :VARIANT_BOOL
    ReAssign		proc
    Save		proc
    Refresh		proc
   .ends

endif

ifndef __FAXCOMEXLib_LIBRARY_DEFINED__
define __FAXCOMEXLib_LIBRARY_DEFINED__

.enum FAX_ROUTING_RULE_CODE_ENUM {
	frrcANY_CODE	= 0
    }

externdef LIBID_FAXCOMEXLib:IID

ifndef __IFaxServerNotify_DISPINTERFACE_DEFINED__
define __IFaxServerNotify_DISPINTERFACE_DEFINED__

DEFINE_IIDX(IFaxServerNotify, "2E037B27-CF8A-4abd-B1E0-5704943BEA6F")

.comdef IFaxServerNotify : public IDispatch
   .ends
endif

ifndef ___IFaxServerNotify2_INTERFACE_DEFINED__
define ___IFaxServerNotify2_INTERFACE_DEFINED__

DEFINE_IIDX(_IFaxServerNotify2, "ec9c69b9-5fe7-4805-9467-82fcd96af903")

.comdef _IFaxServerNotify2 : public IDispatch
    OnIncomingJobAdded	proc :ptr, :BSTR
    OnIncomingJobRemoved proc :ptr, :BSTR
    OnIncomingJobChanged proc :ptr, :BSTR, :ptr
    OnOutgoingJobAdded	proc :ptr, :BSTR
    OnOutgoingJobRemoved proc :ptr, :BSTR
    OnOutgoingJobChanged proc :ptr, :BSTR, :ptr
    OnIncomingMessageAdded proc :ptr, :BSTR
    OnIncomingMessageRemoved proc :ptr, :BSTR
    OnOutgoingMessageAdded proc :ptr, :BSTR
    OnOutgoingMessageRemoved proc :ptr, :BSTR
    OnReceiptOptionsChange proc :ptr
    OnActivityLoggingConfigChange proc :ptr
    OnSecurityConfigChange proc :ptr
    OnEventLoggingConfigChange proc :ptr
    OnOutgoingQueueConfigChange proc :ptr
    OnOutgoingArchiveConfigChange proc :ptr
    OnIncomingArchiveConfigChange proc :ptr
    OnDevicesConfigChange proc :ptr
    OnOutboundRoutingGroupsConfigChange proc :ptr
    OnOutboundRoutingRulesConfigChange proc :ptr
    OnServerActivityChange proc :ptr, :LONG, :LONG, :LONG, :LONG
    OnQueuesStatusChange proc :ptr, :VARIANT_BOOL, :VARIANT_BOOL, :VARIANT_BOOL
    OnNewCall		proc :ptr, :LONG, :LONG, :BSTR
    OnServerShutDown	proc :ptr
    OnDeviceStatusChange proc :ptr, :LONG, :VARIANT_BOOL, :VARIANT_BOOL, :VARIANT_BOOL, :VARIANT_BOOL
    OnGeneralServerConfigChanged proc :ptr
   .ends

endif

ifndef __IFaxServerNotify2_DISPINTERFACE_DEFINED__
define __IFaxServerNotify2_DISPINTERFACE_DEFINED__

DEFINE_IIDX(IFaxServerNotify2, "616ca8d6-a77a-4062-abfd-0e471241c7aa")

.comdef IFaxServerNotify2 : public IDispatch
   .ends
endif

ifndef ___IFaxAccountNotify_INTERFACE_DEFINED__
define ___IFaxAccountNotify_INTERFACE_DEFINED__

DEFINE_IIDX(_IFaxAccountNotify, "b9b3bc81-ac1b-46f3-b39d-0adc30e1b788")

.comdef _IFaxAccountNotify : public IDispatch
    OnIncomingJobAdded	proc :ptr, :BSTR
    OnIncomingJobRemoved proc :ptr, :BSTR
    OnIncomingJobChanged proc :ptr, :BSTR, :ptr
    OnOutgoingJobAdded	proc :ptr, :BSTR
    OnOutgoingJobRemoved proc :ptr, :BSTR
    OnOutgoingJobChanged proc :ptr, :BSTR, :ptr
    OnIncomingMessageAdded proc :ptr, :BSTR, :VARIANT_BOOL
    OnIncomingMessageRemoved proc :ptr, :BSTR, :VARIANT_BOOL
    OnOutgoingMessageAdded proc :ptr, :BSTR
    OnOutgoingMessageRemoved proc :ptr, :BSTR
    OnServerShutDown	proc :ptr
   .ends

endif

ifndef __IFaxAccountNotify_DISPINTERFACE_DEFINED__
define __IFaxAccountNotify_DISPINTERFACE_DEFINED__

DEFINE_IIDX(IFaxAccountNotify, "0b5e5bd1-b8a9-47a0-a323-ef4a293ba06a")

.comdef IFaxAccountNotify : public IDispatch
   .ends
endif


DEFINE_GUIDS(CLSID_FaxServer, "CDA8ACB0-8CF5-4F6C-9BA2-5931D40C8CAE")
DEFINE_GUIDS(CLSID_FaxDeviceProviders, "EB8FE768-875A-4F5F-82C5-03F23AAC1BD7")
DEFINE_GUIDS(CLSID_FaxDevices, "5589E28E-23CB-4919-8808-E6101846E80D")
DEFINE_GUIDS(CLSID_FaxInboundRouting, "E80248ED-AD65-4218-8108-991924D4E7ED")
DEFINE_GUIDS(CLSID_FaxFolders, "C35211D7-5776-48CB-AF44-C31BE3B2CFE5")
DEFINE_GUIDS(CLSID_FaxLoggingOptions, "1BF9EEA6-ECE0-4785-A18B-DE56E9EEF96A")
DEFINE_GUIDS(CLSID_FaxActivity, "CFEF5D0E-E84D-462E-AABB-87D31EB04FEF")
DEFINE_GUIDS(CLSID_FaxOutboundRouting, "C81B385E-B869-4AFD-86C0-616498ED9BE2")
DEFINE_GUIDS(CLSID_FaxReceiptOptions, "6982487B-227B-4C96-A61C-248348B05AB6")
DEFINE_GUIDS(CLSID_FaxSecurity, "10C4DDDE-ABF0-43DF-964F-7F3AC21A4C7B")
DEFINE_GUIDS(CLSID_FaxDocument, "0F3F9F91-C838-415E-A4F3-3E828CA445E0")
DEFINE_GUIDS(CLSID_FaxSender, "265D84D0-1850-4360-B7C8-758BBB5F0B96")
DEFINE_GUIDS(CLSID_FaxRecipients, "EA9BDF53-10A9-4D4F-A067-63C8F84F01B0")
DEFINE_GUIDS(CLSID_FaxIncomingArchive, "8426C56A-35A1-4C6F-AF93-FC952422E2C2")
DEFINE_GUIDS(CLSID_FaxIncomingQueue, "69131717-F3F1-40E3-809D-A6CBF7BD85E5")
DEFINE_GUIDS(CLSID_FaxOutgoingArchive, "43C28403-E04F-474D-990C-B94669148F59")
DEFINE_GUIDS(CLSID_FaxOutgoingQueue, "7421169E-8C43-4B0D-BB16-645C8FA40357")
DEFINE_GUIDS(CLSID_FaxIncomingMessageIterator, "6088E1D8-3FC8-45C2-87B1-909A29607EA9")
DEFINE_GUIDS(CLSID_FaxIncomingMessage, "1932FCF7-9D43-4D5A-89FF-03861B321736")
DEFINE_GUIDS(CLSID_FaxOutgoingJobs, "92BF2A6C-37BE-43FA-A37D-CB0E5F753B35")
DEFINE_GUIDS(CLSID_FaxOutgoingJob, "71BB429C-0EF9-4915-BEC5-A5D897A3E924")
DEFINE_GUIDS(CLSID_FaxOutgoingMessageIterator, "8A3224D0-D30B-49DE-9813-CB385790FBBB")
DEFINE_GUIDS(CLSID_FaxOutgoingMessage, "91B4A378-4AD8-4AEF-A4DC-97D96E939A3A")
DEFINE_GUIDS(CLSID_FaxIncomingJobs, "A1BB8A43-8866-4FB7-A15D-6266C875A5CC")
DEFINE_GUIDS(CLSID_FaxIncomingJob, "C47311EC-AE32-41B8-AE4B-3EAE0629D0C9")
DEFINE_GUIDS(CLSID_FaxDeviceProvider, "17CF1AA3-F5EB-484A-9C9A-4440A5BAABFC")
DEFINE_GUIDS(CLSID_FaxDevice, "59E3A5B2-D676-484B-A6DE-720BFA89B5AF")
DEFINE_GUIDS(CLSID_FaxActivityLogging, "F0A0294E-3BBD-48B8-8F13-8C591A55BDBC")
DEFINE_GUIDS(CLSID_FaxEventLogging, "A6850930-A0F6-4A6F-95B7-DB2EBF3D02E3")
DEFINE_GUIDS(CLSID_FaxOutboundRoutingGroups, "CCBEA1A5-E2B4-4B57-9421-B04B6289464B")
DEFINE_GUIDS(CLSID_FaxOutboundRoutingGroup, "0213F3E0-6791-4D77-A271-04D2357C50D6")
DEFINE_GUIDS(CLSID_FaxDeviceIds, "CDC539EA-7277-460E-8DE0-48A0A5760D1F")
DEFINE_GUIDS(CLSID_FaxOutboundRoutingRules, "D385BECA-E624-4473-BFAA-9F4000831F54")
DEFINE_GUIDS(CLSID_FaxOutboundRoutingRule, "6549EEBF-08D1-475A-828B-3BF105952FA0")
DEFINE_GUIDS(CLSID_FaxInboundRoutingExtensions, "189A48ED-623C-4C0D-80F2-D66C7B9EFEC2")
DEFINE_GUIDS(CLSID_FaxInboundRoutingExtension, "1D7DFB51-7207-4436-A0D9-24E32EE56988")
DEFINE_GUIDS(CLSID_FaxInboundRoutingMethods, "25FCB76A-B750-4B82-9266-FBBBAE8922BA")
DEFINE_GUIDS(CLSID_FaxInboundRoutingMethod, "4B9FD75C-0194-4B72-9CE5-02A8205AC7D4")
DEFINE_GUIDS(CLSID_FaxJobStatus, "7BF222F4-BE8D-442f-841D-6132742423BB")
DEFINE_GUIDS(CLSID_FaxRecipient, "60BF3301-7DF8-4bd8-9148-7B5801F9EFDF")
DEFINE_GUIDS(CLSID_FaxConfiguration, "5857326f-e7b3-41a7-9c19-a91b463e2d56")
DEFINE_GUIDS(CLSID_FaxAccountSet, "fbc23c4b-79e0-4291-bc56-c12e253bbf3a")
DEFINE_GUIDS(CLSID_FaxAccounts, "da1f94aa-ee2c-47c0-8f4f-2a217075b76e")
DEFINE_GUIDS(CLSID_FaxAccount, "a7e0647f-4524-4464-a56d-b9fe666f715e")
DEFINE_GUIDS(CLSID_FaxAccountFolders, "85398f49-c034-4a3f-821c-db7d685e8129")
DEFINE_GUIDS(CLSID_FaxAccountIncomingQueue, "9bcf6094-b4da-45f4-b8d6-ddeb2186652c")
DEFINE_GUIDS(CLSID_FaxAccountOutgoingQueue, "feeceefb-c149-48ba-bab8-b791e101f62f")
DEFINE_GUIDS(CLSID_FaxAccountIncomingArchive, "14b33db5-4c40-4ecf-9ef8-a360cbe809ed")
DEFINE_GUIDS(CLSID_FaxAccountOutgoingArchive, "851e7af5-433a-4739-a2df-ad245c2cb98e")
DEFINE_GUIDS(CLSID_FaxSecurity2, "735c1248-ec89-4c30-a127-656e92e3c4ea")

ifndef __FaxConstants_MODULE_DEFINED__
define __FaxConstants_MODULE_DEFINED__
define lDEFAULT_PREFETCH_SIZE <prv_DEFAULT_PREFETCH_SIZE>
define bstrGROUPNAME_ALLDEVICES <L"<All Devices>">
define wcharREASSIGN_RECIPIENTS_DELIMITER <';'>
endif

endif

endif

endif
