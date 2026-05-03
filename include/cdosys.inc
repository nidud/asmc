ifndef _RPCNDR500_
include rpcndr500.inc
endif

ifndef __cdo_h__
define __cdo_h__

include cdosysstr.inc

undef IDataSource

ifndef __oaidl_h__
include oaidl.inc
endif
ifndef __ocidl_h__
include ocidl.inc
endif

include adoint_backcompat.inc

ifndef _WINAPIFAMILY_
include winapifamily.inc
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

.enum CdoConfigSource {
	cdoDefaults	= -1,
	cdoIIS	= 1,
	cdoOutlookExpress	= 2
	}

.enum CdoDSNOptions {
	cdoDSNDefault	= 0,
	cdoDSNNever	= 1,
	cdoDSNFailure	= 2,
	cdoDSNSuccess	= 4,
	cdoDSNDelay	= 8,
	cdoDSNSuccessFailOrDelay	= 14
	}

.enum CdoEventStatus {
	cdoRunNextSink	= 0,
	cdoSkipRemainingSinks	= 1
	}

.enum CdoEventType {
	cdoSMTPOnArrival	= 1,
	cdoNNTPOnPostEarly	= 2,
	cdoNNTPOnPost	= 3,
	cdoNNTPOnPostFinal	= 4
	}

.enum cdoImportanceValues {
	cdoLow	= 0,
	cdoNormal	= 1,
	cdoHigh = 2
	}

.enum CdoMessageStat {
	cdoStatSuccess	= 0,
	cdoStatAbortDelivery	= 2,
	cdoStatBadMail	= 3
	}

.enum CdoMHTMLFlags {
	cdoSuppressNone = 0,
	cdoSuppressImages	= 1,
	cdoSuppressBGSounds	= 2,
	cdoSuppressFrames	= 4,
	cdoSuppressObjects	= 8,
	cdoSuppressStyleSheets	= 16,
	cdoSuppressAll	= 31
	}

.enum CdoNNTPProcessingField {
	cdoPostMessage	= 1,
	cdoProcessControl	= 2,
	cdoProcessModerator	= 4
	}

.enum CdoPostUsing {
	cdoPostUsingPickup	= 1,
	cdoPostUsingPort	= 2
	}

.enum cdoPriorityValues {
	cdoPriorityNonUrgent	= -1,
	cdoPriorityNormal	= 0,
	cdoPriorityUrgent	= 1
	}

.enum CdoProtocolsAuthentication {
	cdoAnonymous	= 0,
	cdoBasic	= 1,
	cdoNTLM = 2
	}

.enum CdoReferenceType {
	cdoRefTypeId	= 0,
	cdoRefTypeLocation	= 1
	}

.enum CdoSendUsing {
	cdoSendUsingPickup	= 1,
	cdoSendUsingPort	= 2
	}

.enum cdoSensitivityValues {
	cdoSensitivityNone	= 0,
	cdoPersonal	= 1,
	cdoPrivate	= 2,
	cdoCompanyConfidential	= 3
	}

.enum CdoTimeZoneId {
	cdoUTC	= 0,
	cdoGMT	= 1,
	cdoSarajevo	= 2,
	cdoParis	= 3,
	cdoBerlin	= 4,
	cdoEasternEurope	= 5,
	cdoPrague	= 6,
	cdoAthens	= 7,
	cdoBrasilia	= 8,
	cdoAtlanticCanada	= 9,
	cdoEastern	= 10,
	cdoCentral	= 11,
	cdoMountain	= 12,
	cdoPacific	= 13,
	cdoAlaska	= 14,
	cdoHawaii	= 15,
	cdoMidwayIsland = 16,
	cdoWellington	= 17,
	cdoBrisbane	= 18,
	cdoAdelaide	= 19,
	cdoTokyo	= 20,
	cdoSingapore	= 21,
	cdoBangkok	= 22,
	cdoBombay	= 23,
	cdoAbuDhabi	= 24,
	cdoTehran	= 25,
	cdoBaghdad	= 26,
	cdoIsrael	= 27,
	cdoNewfoundland = 28,
	cdoAzores	= 29,
	cdoMidAtlantic	= 30,
	cdoMonrovia	= 31,
	cdoBuenosAires	= 32,
	cdoCaracas	= 33,
	cdoIndiana	= 34,
	cdoBogota	= 35,
	cdoSaskatchewan = 36,
	cdoMexicoCity	= 37,
	cdoArizona	= 38,
	cdoEniwetok	= 39,
	cdoFiji = 40,
	cdoMagadan	= 41,
	cdoHobart	= 42,
	cdoGuam = 43,
	cdoDarwin	= 44,
	cdoBeijing	= 45,
	cdoAlmaty	= 46,
	cdoIslamabad	= 47,
	cdoKabul	= 48,
	cdoCairo	= 49,
	cdoHarare	= 50,
	cdoMoscow	= 51,
	cdoFloating	= 52,
	cdoCapeVerde	= 53,
	cdoCaucasus	= 54,
	cdoCentralAmerica	= 55,
	cdoEastAfrica	= 56,
	cdoMelbourne	= 57,
	cdoEkaterinburg = 58,
	cdoHelsinki	= 59,
	cdoGreenland	= 60,
	cdoRangoon	= 61,
	cdoNepal	= 62,
	cdoIrkutsk	= 63,
	cdoKrasnoyarsk	= 64,
	cdoSantiago	= 65,
	cdoSriLanka	= 66,
	cdoTonga	= 67,
	cdoVladivostok	= 68,
	cdoWestCentralAfrica	= 69,
	cdoYakutsk	= 70,
	cdoDhaka	= 71,
	cdoSeoul	= 72,
	cdoPerth	= 73,
	cdoArab = 74,
	cdoTaipei	= 75,
	cdoSydney2000	= 76,
	cdoChihuahua	= 77,
	cdoCanberraCommonwealthGames2006	= 78,
	cdoAdelaideCommonwealthGames2006	= 79,
	cdoHobartCommonwealthGames2006	= 80,
	cdoTijuana	= 81,
	cdoInvalidTimeZone	= 82
	}

ifndef __IDataSource_INTERFACE_DEFINED__
define __IDataSource_INTERFACE_DEFINED__

DEFINE_IIDX(IDataSource, "CD000029-8B95-11D1-82DB-00C04FB1625D")

.comdef IDataSource : public IDispatch
    get_SourceClass	proc :ptr
    get_Source		proc :ptr ptr
    get_IsDirty		proc :ptr
    put_IsDirty		proc :VARIANT_BOOL
    get_SourceURL	proc :ptr
    get_ActiveConnection proc :ptr ptr
    SaveToObject	proc :ptr, :BSTR
    OpenObject		proc :ptr, :BSTR
    SaveTo		proc :BSTR, :ptr, :ConnectModeEnum, :RecordCreateOptionsEnum, :RecordOpenOptionsEnum, :BSTR, :BSTR
    Open		proc :BSTR, :ptr, :ConnectModeEnum, :RecordCreateOptionsEnum, :RecordOpenOptionsEnum, :BSTR, :BSTR
    Save		proc
    SaveToContainer	proc :BSTR, :ptr, :ConnectModeEnum, :RecordCreateOptionsEnum, :RecordOpenOptionsEnum, :BSTR, :BSTR
   .ends

endif

ifndef __IMessage_INTERFACE_DEFINED__
define __IMessage_INTERFACE_DEFINED__

DEFINE_IIDX(IMessage, "CD000020-8B95-11D1-82DB-00C04FB1625D")

.comdef IMessage : public IDispatch
    get_BCC		proc :ptr
    put_BCC		proc :BSTR
    get_CC		proc :ptr
    put_CC		proc :BSTR
    get_FollowUpTo	proc :ptr
    put_FollowUpTo	proc :BSTR
    get_From		proc :ptr
    put_From		proc :BSTR
    get_Keywords	proc :ptr
    put_Keywords	proc :BSTR
    get_MimeFormatted	proc :ptr
    put_MimeFormatted	proc :VARIANT_BOOL
    get_Newsgroups	proc :ptr
    put_Newsgroups	proc :BSTR
    get_Organization	proc :ptr
    put_Organization	proc :BSTR
    get_ReceivedTime	proc :ptr
    get_ReplyTo		proc :ptr
    put_ReplyTo		proc :BSTR
    get_DSNOptions	proc :ptr
    put_DSNOptions	proc :CdoDSNOptions
    get_SentOn		proc :ptr
    get_Subject		proc :ptr
    put_Subject		proc :BSTR
    get_To		proc :ptr
    put_To		proc :BSTR
    get_TextBody	proc :ptr
    put_TextBody	proc :BSTR
    get_HTMLBody	proc :ptr
    put_HTMLBody	proc :BSTR
    get_Attachments	proc :ptr ptr
    get_Sender		proc :ptr
    put_Sender		proc :BSTR
    get_Configuration	proc :ptr ptr
    put_Configuration	proc :ptr
    putref_Configuration proc :ptr
    get_AutoGenerateTextBody proc :ptr
    put_AutoGenerateTextBody proc :VARIANT_BOOL
    get_EnvelopeFields	proc :ptr ptr
    get_TextBodyPart	proc :ptr ptr
    get_HTMLBodyPart	proc :ptr ptr
    get_BodyPart	proc :ptr ptr
    get_DataSource	proc :ptr ptr
    get_Fields		proc :ptr ptr
    get_MDNRequested	proc :ptr
    put_MDNRequested	proc :VARIANT_BOOL
    AddRelatedBodyPart	proc :BSTR, :BSTR, :CdoReferenceType, :BSTR, :BSTR, :ptr ptr
    AddAttachment	proc :BSTR, :BSTR, :BSTR, :ptr ptr
    CreateMHTMLBody	proc :BSTR, :CdoMHTMLFlags, :BSTR, :BSTR
    Forward		proc :ptr ptr
    Post		proc
    PostReply		proc :ptr ptr
    Reply		proc :ptr ptr
    ReplyAll		proc :ptr ptr
    Send		proc
    GetStream		proc :ptr ptr
    GetInterface	proc :BSTR, :ptr ptr
   .ends

endif

ifndef __IBodyPart_INTERFACE_DEFINED__
define __IBodyPart_INTERFACE_DEFINED__

DEFINE_IIDX(IBodyPart, "CD000021-8B95-11D1-82DB-00C04FB1625D")

.comdef IBodyPart : public IDispatch
    get_BodyParts	proc :ptr ptr
    get_ContentTransferEncoding proc :ptr
    put_ContentTransferEncoding proc :BSTR
    get_ContentMediaType proc :ptr
    put_ContentMediaType proc :BSTR
    get_Fields		proc :ptr ptr
    get_Charset		proc :ptr
    put_Charset		proc :BSTR
    get_FileName	proc :ptr
    get_DataSource	proc :ptr ptr
    get_ContentClass	proc :ptr
    put_ContentClass	proc :BSTR
    get_ContentClassName proc :ptr
    put_ContentClassName proc :BSTR
    get_Parent		proc :ptr ptr
    AddBodyPart		proc :LONG, :ptr ptr
    SaveToFile		proc :BSTR
    GetEncodedContentStream proc :ptr ptr
    GetDecodedContentStream proc :ptr ptr
    GetStream		proc :ptr ptr
    GetFieldParameter	proc :BSTR, :BSTR, :ptr
    GetInterface	proc :BSTR, :ptr ptr
   .ends

endif

ifndef __IConfiguration_INTERFACE_DEFINED__
define __IConfiguration_INTERFACE_DEFINED__

DEFINE_IIDX(IConfiguration, "CD000022-8B95-11D1-82DB-00C04FB1625D")

.comdef IConfiguration : public IDispatch
    get_Fields		proc :ptr ptr
    Load		proc :CdoConfigSource, :BSTR
    GetInterface	proc :BSTR, :ptr ptr
   .ends

endif

ifndef __IMessages_INTERFACE_DEFINED__
define __IMessages_INTERFACE_DEFINED__

DEFINE_IIDX(IMessages, "CD000025-8B95-11D1-82DB-00C04FB1625D")

.comdef IMessages : public IDispatch
    get_Item		proc :LONG, :ptr ptr
    get_Count		proc :ptr
    Delete		proc :LONG
    DeleteAll		proc
    get__NewEnum	proc :ptr ptr
    get_Filename	proc :VARIANT, :ptr
   .ends

endif

ifndef __IDropDirectory_INTERFACE_DEFINED__
define __IDropDirectory_INTERFACE_DEFINED__

DEFINE_IIDX(IDropDirectory, "CD000024-8B95-11D1-82DB-00C04FB1625D")

.comdef IDropDirectory : public IDispatch
    GetMessages		proc :BSTR, :ptr ptr
   .ends

endif

ifndef __IBodyParts_INTERFACE_DEFINED__
define __IBodyParts_INTERFACE_DEFINED__

DEFINE_IIDX(IBodyParts, "CD000023-8B95-11D1-82DB-00C04FB1625D")

.comdef IBodyParts : public IDispatch
    get_Count		proc :ptr
    get_Item		proc :LONG, :ptr ptr
    get__NewEnum	proc :ptr ptr
    Delete		proc :VARIANT
    DeleteAll		proc
    _Add		proc :LONG, :ptr ptr
   .ends

endif

ifndef __ISMTPScriptConnector_INTERFACE_DEFINED__
define __ISMTPScriptConnector_INTERFACE_DEFINED__

DEFINE_IIDX(ISMTPScriptConnector, "CD000030-8B95-11D1-82DB-00C04FB1625D")

.comdef ISMTPScriptConnector : public IDispatch
   .ends

endif

ifndef __INNTPEarlyScriptConnector_INTERFACE_DEFINED__
define __INNTPEarlyScriptConnector_INTERFACE_DEFINED__

DEFINE_IIDX(INNTPEarlyScriptConnector, "CD000034-8B95-11D1-82DB-00C04FB1625D")

.comdef INNTPEarlyScriptConnector : public IDispatch
   .ends

endif

ifndef __INNTPPostScriptConnector_INTERFACE_DEFINED__
define __INNTPPostScriptConnector_INTERFACE_DEFINED__

DEFINE_IIDX(INNTPPostScriptConnector, "CD000031-8B95-11D1-82DB-00C04FB1625D")

.comdef INNTPPostScriptConnector : public IDispatch
   .ends

endif

ifndef __INNTPFinalScriptConnector_INTERFACE_DEFINED__
define __INNTPFinalScriptConnector_INTERFACE_DEFINED__

DEFINE_IIDX(INNTPFinalScriptConnector, "CD000032-8B95-11D1-82DB-00C04FB1625D")

.comdef INNTPFinalScriptConnector : public IDispatch
   .ends

endif

ifndef __ISMTPOnArrival_INTERFACE_DEFINED__
define __ISMTPOnArrival_INTERFACE_DEFINED__

DEFINE_IIDX(ISMTPOnArrival, "CD000026-8B95-11D1-82DB-00C04FB1625D")

.comdef ISMTPOnArrival : public IDispatch
    OnArrival		proc :ptr, :ptr
   .ends

endif

ifndef __INNTPOnPostEarly_INTERFACE_DEFINED__
define __INNTPOnPostEarly_INTERFACE_DEFINED__

DEFINE_IIDX(INNTPOnPostEarly, "CD000033-8B95-11D1-82DB-00C04FB1625D")

.comdef INNTPOnPostEarly : public IDispatch
    OnPostEarly		proc :ptr, :ptr
   .ends

endif

ifndef __INNTPOnPost_INTERFACE_DEFINED__
define __INNTPOnPost_INTERFACE_DEFINED__

DEFINE_IIDX(INNTPOnPost, "CD000027-8B95-11D1-82DB-00C04FB1625D")

.comdef INNTPOnPost : public IDispatch
    OnPost		proc :ptr, :ptr
   .ends

endif

ifndef __INNTPOnPostFinal_INTERFACE_DEFINED__
define __INNTPOnPostFinal_INTERFACE_DEFINED__

DEFINE_IIDX(INNTPOnPostFinal, "CD000028-8B95-11D1-82DB-00C04FB1625D")

.comdef INNTPOnPostFinal : public IDispatch
    OnPostFinal		proc :ptr, :ptr
   .ends

endif

ifndef __IProxyObject_INTERFACE_DEFINED__
define __IProxyObject_INTERFACE_DEFINED__

DEFINE_IIDX(IProxyObject, "CD000083-8B95-11D1-82DB-00C04FB1625D")

.comdef IProxyObject : public IUnknown
    get_Object		proc :ptr ptr
   .ends

endif

ifndef __IGetInterface_INTERFACE_DEFINED__
define __IGetInterface_INTERFACE_DEFINED__

DEFINE_IIDX(IGetInterface, "CD0ff000-8B95-11D1-82DB-00C04FB1625D")

.comdef IGetInterface : public IUnknown
    GetInterface	proc :BSTR, :ptr ptr
    GetInterfaceInner	proc :BSTR, :ptr ptr
   .ends

endif

ifndef __CDO_LIBRARY_DEFINED__
define __CDO_LIBRARY_DEFINED__

DEFINE_GUID(LIBID_CDO, 0xCD000000,0x8B95,0x11D1,0x82,0xDB,0x00,0xC0,0x4F,0xB1,0x62,0x5D)

ifndef __CdoErrors_MODULE_DEFINED__
define __CdoErrors_MODULE_DEFINED__

define CDO_E_UNCAUGHT_EXCEPTION		0x80040201
define CDO_E_NOT_OPENED			0x80040202
define CDO_E_UNSUPPORTED_DATASOURCE	0x80040203
define CDO_E_INVALID_PROPERTYNAME	0x80040204
define CDO_E_PROP_UNSUPPORTED		0x80040205
define CDO_E_INACTIVE			0x80040206
define CDO_E_NO_SUPPORT_FOR_OBJECTS	0x80040207
define CDO_E_NOT_AVAILABLE		0x80040208
define CDO_E_NO_DEFAULT_DROP_DIR	0x80040209
define CDO_E_SMTP_SERVER_REQUIRED	0x8004020a
define CDO_E_NNTP_SERVER_REQUIRED	0x8004020b
define CDO_E_RECIPIENT_MISSING		0x8004020c
define CDO_E_FROM_MISSING		0x8004020d
define CDO_E_SENDER_REJECTED		0x8004020e
define CDO_E_RECIPIENTS_REJECTED	0x8004020f
define CDO_E_NNTP_POST_FAILED		0x80040210
define CDO_E_SMTP_SEND_FAILED		0x80040211
define CDO_E_CONNECTION_DROPPED		0x80040212
define CDO_E_FAILED_TO_CONNECT		0x80040213
define CDO_E_INVALID_POST		0x80040214
define CDO_E_AUTHENTICATION_FAILURE	0x80040215
define CDO_E_INVALID_CONTENT_TYPE	0x80040216
define CDO_E_LOGON_FAILURE		0x80040217
define CDO_E_HTTP_NOT_FOUND		0x80040218
define CDO_E_HTTP_FORBIDDEN		0x80040219
define CDO_E_HTTP_FAILED		0x8004021a
define CDO_E_MULTIPART_NO_DATA		0x8004021b
define CDO_E_INVALID_ENCODING_FOR_MULTIPART 0x8004021c
define CDO_E_UNSAFE_OPERATION		0x8004021d
define CDO_E_PROP_NOT_FOUND		0x8004021e
define CDO_E_INVALID_SEND_OPTION	0x80040220
define CDO_E_INVALID_POST_OPTION	0x80040221
define CDO_E_NO_PICKUP_DIR		0x80040222
define CDO_E_NOT_ALL_DELETED		0x80040223
define CDO_E_NO_METHOD			0x80040224
define CDO_E_PROP_READONLY		0x80040227
define CDO_E_PROP_CANNOT_DELETE		0x80040228
define CDO_E_BAD_DATA			0x80040229
define CDO_E_PROP_NONHEADER		0x8004022a
define CDO_E_INVALID_CHARSET		0x8004022b
define CDO_E_ADOSTREAM_NOT_BOUND	0x8004022c
define CDO_E_CONTENTPROPXML_NOT_FOUND	0x8004022d
define CDO_E_CONTENTPROPXML_WRONG_CHARSET 0x8004022e
define CDO_E_CONTENTPROPXML_PARSE_FAILED 0x8004022f
define CDO_E_CONTENTPROPXML_CONVERT_FAILED 0x80040230
define CDO_E_NO_DIRECTORIES_SPECIFIED	0x80040231
define CDO_E_DIRECTORIES_UNREACHABLE	0x80040232
define CDO_E_BAD_SENDER			0x80040233
define CDO_E_SELF_BINDING		0x80040234
define CDO_E_BAD_ATTENDEE_DATA		0x80040235
define CDO_E_ROLE_NOMORE_AVAILABLE	0x80040236
define CDO_E_BAD_TASKTYPE_ONASSIGN	0x80040237
define CDO_E_NOT_ASSIGNEDTO_USER	0x80040238
define CDO_E_OUTOFDATE			0x80040239
define CDO_E_ARGUMENT1			0x80044000
define CDO_E_ARGUMENT2			0x80044001
define CDO_E_ARGUMENT3			0x80044002
define CDO_E_ARGUMENT4			0x80044003
define CDO_E_ARGUMENT5			0x80044004
define CDO_E_NOT_FOUND			0x800cce05
define CDO_E_INVALID_ENCODING_TYPE	0x800cce1d

endif

DEFINE_GUIDS(CLSID_Message,		"CD000001-8B95-11D1-82DB-00C04FB1625D")
DEFINE_GUIDS(CLSID_Configuration,	"CD000002-8B95-11D1-82DB-00C04FB1625D")
DEFINE_GUIDS(CLSID_DropDirectory,	"CD000004-8B95-11D1-82DB-00C04FB1625D")
DEFINE_GUIDS(CLSID_SMTPConnector,	"CD000008-8B95-11D1-82DB-00C04FB1625D")
DEFINE_GUIDS(CLSID_NNTPEarlyConnector,	"CD000011-8B95-11D1-82DB-00C04FB1625D")
DEFINE_GUIDS(CLSID_NNTPPostConnector,	"CD000009-8B95-11D1-82DB-00C04FB1625D")
DEFINE_GUIDS(CLSID_NNTPFinalConnector,	"CD000010-8B95-11D1-82DB-00C04FB1625D")

endif

endif

endif
