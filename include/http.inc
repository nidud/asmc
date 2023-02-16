ifndef __HTTP_H__
define __HTTP_H__

include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

if _WIN32_WINNT GE 0x0501

include winsock2.inc
include ws2tcpip.inc

HTTP_INITIALIZE_SERVER	equ 0x00000001
HTTP_INITIALIZE_CONFIG	equ 0x00000002
HTTP_DEMAND_CBT		equ 0x00000004

.pragma pack(push, 8)
.pragma comment(lib, httpapi)

if _WIN32_WINNT GE 0x0600

.enum HTTP_SERVER_PROPERTY {
    HttpServerAuthenticationProperty,
    HttpServerLoggingProperty,
    HttpServerQosProperty,
    HttpServerTimeoutsProperty,
    HttpServerQueueLengthProperty,
    HttpServerStateProperty,
    HttpServer503VerbosityProperty,
    HttpServerBindingProperty,
    HttpServerExtendedAuthenticationProperty,
    HttpServerListenEndpointProperty,
    HttpServerChannelBindProperty,
    HttpServerProtectionLevelProperty
    }


HTTP_MAX_SERVER_QUEUE_LENGTH equ 0x7FFFFFFF
HTTP_MIN_SERVER_QUEUE_LENGTH equ 1

HTTP_PROPERTY_FLAGS	STRUC
Present			ULONG ? ; :1
HTTP_PROPERTY_FLAGS	ENDS
PHTTP_PROPERTY_FLAGS	typedef ptr HTTP_PROPERTY_FLAGS

.enum HTTP_ENABLED_STATE {
    HttpEnabledStateActive,
    HttpEnabledStateInactive,
    }


HTTP_STATE_INFO		STRUC
Flags			HTTP_PROPERTY_FLAGS <>
State			HTTP_ENABLED_STATE ?
HTTP_STATE_INFO		ENDS
PHTTP_STATE_INFO	typedef ptr HTTP_STATE_INFO

.enum HTTP_503_RESPONSE_VERBOSITY {
    Http503ResponseVerbosityBasic,
    Http503ResponseVerbosityLimited,
    Http503ResponseVerbosityFull
    }

.enum HTTP_QOS_SETTING_TYPE {
    HttpQosSettingTypeBandwidth,
    HttpQosSettingTypeConnectionLimit,
    HttpQosSettingTypeFlowRate
    }

HTTP_QOS_SETTING_INFO	STRUC
QosType			HTTP_QOS_SETTING_TYPE ?
QosSetting		PVOID ?
HTTP_QOS_SETTING_INFO	ENDS
PHTTP_QOS_SETTING_INFO	typedef ptr HTTP_QOS_SETTING_INFO

HTTP_CONNECTION_LIMIT_INFO STRUC
Flags			HTTP_PROPERTY_FLAGS <>
MaxConnections		ULONG ?
HTTP_CONNECTION_LIMIT_INFO ENDS
PHTTP_CONNECTION_LIMIT_INFO typedef ptr HTTP_CONNECTION_LIMIT_INFO

HTTP_BANDWIDTH_LIMIT_INFO STRUC
Flags			HTTP_PROPERTY_FLAGS <>
MaxBandwidth		ULONG ?
HTTP_BANDWIDTH_LIMIT_INFO ENDS
PHTTP_BANDWIDTH_LIMIT_INFO typedef ptr HTTP_BANDWIDTH_LIMIT_INFO

HTTP_FLOWRATE_INFO	STRUC
Flags			HTTP_PROPERTY_FLAGS <>
MaxBandwidth		ULONG ?
MaxPeakBandwidth	ULONG ?
BurstSize		ULONG ?
HTTP_FLOWRATE_INFO	ENDS
PHTTP_FLOWRATE_INFO	typedef ptr HTTP_FLOWRATE_INFO

HTTP_MIN_ALLOWED_BANDWIDTH_THROTTLING_RATE equ (1024)

HTTP_LIMIT_INFINITE	equ (-1)

.enum HTTP_SERVICE_CONFIG_TIMEOUT_KEY {
    IdleConnectionTimeout = 0,
    HeaderWaitTimeout
    }

HTTP_SERVICE_CONFIG_TIMEOUT_PARAM typedef USHORT
PHTTP_SERVICE_CONFIG_TIMEOUT_PARAM typedef ptr HTTP_SERVICE_CONFIG_TIMEOUT_PARAM

HTTP_SERVICE_CONFIG_TIMEOUT_SET STRUC
KeyDesc			HTTP_SERVICE_CONFIG_TIMEOUT_KEY ?
ParamDesc		HTTP_SERVICE_CONFIG_TIMEOUT_PARAM ?
HTTP_SERVICE_CONFIG_TIMEOUT_SET ENDS
PHTTP_SERVICE_CONFIG_TIMEOUT_SET typedef ptr HTTP_SERVICE_CONFIG_TIMEOUT_SET


HTTP_TIMEOUT_LIMIT_INFO STRUC
Flags			HTTP_PROPERTY_FLAGS <>
EntityBody		USHORT ?
DrainEntityBody		USHORT ?
RequestQueue		USHORT ?
IdleConnection		USHORT ?
HeaderWait		USHORT ?
MinSendRate		ULONG ?
HTTP_TIMEOUT_LIMIT_INFO ENDS
PHTTP_TIMEOUT_LIMIT_INFO typedef ptr HTTP_TIMEOUT_LIMIT_INFO

HTTP_LISTEN_ENDPOINT_INFO STRUC
Flags			HTTP_PROPERTY_FLAGS <>
EnableSharing		BOOLEAN ?
HTTP_LISTEN_ENDPOINT_INFO ENDS
PHTTP_LISTEN_ENDPOINT_INFO typedef ptr HTTP_LISTEN_ENDPOINT_INFO


HTTP_SERVER_AUTHENTICATION_DIGEST_PARAMS STRUC
DomainNameLength	USHORT ?
DomainName		PWSTR ?
RealmLength		USHORT ?
Realm			PWSTR ?
HTTP_SERVER_AUTHENTICATION_DIGEST_PARAMS ENDS

HTTP_SERVER_AUTHENTICATION_BASIC_PARAMS STRUC
RealmLength		USHORT ?
Realm			PWSTR ?
HTTP_SERVER_AUTHENTICATION_BASIC_PARAMS ENDS

HTTP_AUTH_ENABLE_BASIC	equ (0x00000001)
HTTP_AUTH_ENABLE_DIGEST equ (0x00000002)
HTTP_AUTH_ENABLE_NTLM	equ (0x00000004)
HTTP_AUTH_ENABLE_NEGOTIATE equ (0x00000008)
HTTP_AUTH_ENABLE_KERBEROS equ (0x00000010)

HTTP_AUTH_ENABLE_ALL equ \
	(HTTP_AUTH_ENABLE_BASIC or \
	 HTTP_AUTH_ENABLE_DIGEST or \
	 HTTP_AUTH_ENABLE_NTLM or \
	 HTTP_AUTH_ENABLE_NEGOTIATEor \
	 HTTP_AUTH_ENABLE_KERBEROS)


C_ASSERT(HTTP_AUTH_ENABLE_NEGOTIATE gt HTTP_AUTH_ENABLE_NTLM)
C_ASSERT(HTTP_AUTH_ENABLE_NTLM gt HTTP_AUTH_ENABLE_DIGEST)
C_ASSERT(HTTP_AUTH_ENABLE_DIGEST gt HTTP_AUTH_ENABLE_BASIC)

HTTP_AUTH_EX_FLAG_ENABLE_KERBEROS_CREDENTIAL_CACHING equ (0x01)
HTTP_AUTH_EX_FLAG_CAPTURE_CREDENTIAL equ (0x02)

HTTP_SERVER_AUTHENTICATION_INFO STRUC
Flags			HTTP_PROPERTY_FLAGS <>
AuthSchemes		ULONG ?
ReceiveMutualAuth	BOOLEAN ?
ReceiveContextHandle	BOOLEAN ?
DisableNTLMCredentialCaching BOOLEAN ?
ExFlags			UCHAR ?
DigestParams		HTTP_SERVER_AUTHENTICATION_DIGEST_PARAMS <>
BasicParams		HTTP_SERVER_AUTHENTICATION_BASIC_PARAMS <>
HTTP_SERVER_AUTHENTICATION_INFO ENDS
PHTTP_SERVER_AUTHENTICATION_INFO typedef ptr HTTP_SERVER_AUTHENTICATION_INFO

if _WIN32_WINNT GE _WIN32_WINNT_WIN7

.enum HTTP_SERVICE_BINDING_TYPE {
    HttpServiceBindingTypeNone = 0,
    HttpServiceBindingTypeW,
    HttpServiceBindingTypeA
    }

HTTP_SERVICE_BINDING_BASE STRUC
Type			HTTP_SERVICE_BINDING_TYPE ?
HTTP_SERVICE_BINDING_BASE ENDS
PHTTP_SERVICE_BINDING_BASE typedef ptr HTTP_SERVICE_BINDING_BASE

HTTP_SERVICE_BINDING_A	STRUC
Base			HTTP_SERVICE_BINDING_BASE <>
Buffer			PCHAR ?
BufferSize		ULONG ?
HTTP_SERVICE_BINDING_A	ENDS
PHTTP_SERVICE_BINDING_A typedef ptr HTTP_SERVICE_BINDING_A

HTTP_SERVICE_BINDING_W	STRUC
Base			HTTP_SERVICE_BINDING_BASE <>
Buffer			PWCHAR ?
BufferSize		ULONG ?
HTTP_SERVICE_BINDING_W	ENDS
PHTTP_SERVICE_BINDING_W typedef ptr HTTP_SERVICE_BINDING_W

.enum HTTP_AUTHENTICATION_HARDENING_LEVELS {
    HttpAuthenticationHardeningLegacy = 0,
    HttpAuthenticationHardeningMedium,
    HttpAuthenticationHardeningStrict
    }

HTTP_CHANNEL_BIND_PROXY equ 0x1
HTTP_CHANNEL_BIND_PROXY_COHOSTING equ 0x20
HTTP_CHANNEL_BIND_NO_SERVICE_NAME_CHECK equ 0x2
HTTP_CHANNEL_BIND_DOTLESS_SERVICE equ 0x4
HTTP_CHANNEL_BIND_SECURE_CHANNEL_TOKEN equ 0x8
HTTP_CHANNEL_BIND_CLIENT_SERVICE equ 0x10

HTTP_CHANNEL_BIND_INFO	STRUC
Hardening		HTTP_AUTHENTICATION_HARDENING_LEVELS ?
Flags			ULONG ?
ServiceNames		PHTTP_SERVICE_BINDING_BASE ?
NumberOfServiceNames	ULONG ?
HTTP_CHANNEL_BIND_INFO	ENDS
PHTTP_CHANNEL_BIND_INFO typedef ptr HTTP_CHANNEL_BIND_INFO

HTTP_REQUEST_CHANNEL_BIND_STATUS STRUC
ServiceName		PHTTP_SERVICE_BINDING_BASE ?
ChannelToken		PUCHAR ?
ChannelTokenSize	ULONG ?
Flags			ULONG ?
HTTP_REQUEST_CHANNEL_BIND_STATUS ENDS
PHTTP_REQUEST_CHANNEL_BIND_STATUS typedef ptr HTTP_REQUEST_CHANNEL_BIND_STATUS

endif

HTTP_LOG_FIELD_DATE	equ 0x00000001
HTTP_LOG_FIELD_TIME	equ 0x00000002
HTTP_LOG_FIELD_CLIENT_IP equ 0x00000004
HTTP_LOG_FIELD_USER_NAME equ 0x00000008
HTTP_LOG_FIELD_SITE_NAME equ 0x00000010
HTTP_LOG_FIELD_COMPUTER_NAME equ 0x00000020
HTTP_LOG_FIELD_SERVER_IP equ 0x00000040
HTTP_LOG_FIELD_METHOD	equ 0x00000080
HTTP_LOG_FIELD_URI_STEM equ 0x00000100
HTTP_LOG_FIELD_URI_QUERY equ 0x00000200
HTTP_LOG_FIELD_STATUS	equ 0x00000400
HTTP_LOG_FIELD_WIN32_STATUS equ 0x00000800
HTTP_LOG_FIELD_BYTES_SENT equ 0x00001000
HTTP_LOG_FIELD_BYTES_RECV equ 0x00002000
HTTP_LOG_FIELD_TIME_TAKEN equ 0x00004000
HTTP_LOG_FIELD_SERVER_PORT equ 0x00008000
HTTP_LOG_FIELD_USER_AGENT equ 0x00010000
HTTP_LOG_FIELD_COOKIE	equ 0x00020000
HTTP_LOG_FIELD_REFERER	equ 0x00040000
HTTP_LOG_FIELD_VERSION	equ 0x00080000
HTTP_LOG_FIELD_HOST	equ 0x00100000
HTTP_LOG_FIELD_SUB_STATUS equ 0x00200000

HTTP_LOG_FIELD_CLIENT_PORT equ 0x00400000
HTTP_LOG_FIELD_URI	equ 0x00800000
HTTP_LOG_FIELD_SITE_ID	equ 0x01000000
HTTP_LOG_FIELD_REASON	equ 0x02000000
HTTP_LOG_FIELD_QUEUE_NAME equ 0x04000000

.enum HTTP_LOGGING_TYPE {
    HttpLoggingTypeW3C,
    HttpLoggingTypeIIS,
    HttpLoggingTypeNCSA,
    HttpLoggingTypeRaw
    }

.enum HTTP_LOGGING_ROLLOVER_TYPE {
    HttpLoggingRolloverSize,
    HttpLoggingRolloverDaily,
    HttpLoggingRolloverWeekly,
    HttpLoggingRolloverMonthly,
    HttpLoggingRolloverHourly
    }

HTTP_MIN_ALLOWED_LOG_FILE_ROLLOVER_SIZE equ (1 * 1024 * 1024)

HTTP_LOGGING_FLAG_LOCAL_TIME_ROLLOVER equ (0x00000001)
HTTP_LOGGING_FLAG_USE_UTF8_CONVERSION equ (0x00000002)
HTTP_LOGGING_FLAG_LOG_ERRORS_ONLY equ (0x00000004)
HTTP_LOGGING_FLAG_LOG_SUCCESS_ONLY equ (0x00000008)

HTTP_LOGGING_INFO	STRUC
Flags			HTTP_PROPERTY_FLAGS <>
LoggingFlags		ULONG ?
SoftwareName		PCWSTR ?
SoftwareNameLength	USHORT ?
DirectoryNameLength	USHORT ?
DirectoryName		PCWSTR ?
Format			HTTP_LOGGING_TYPE ?
Fields			ULONG ?
pExtFields		PVOID ?
NumOfExtFields		USHORT ?
MaxRecordSize		USHORT ?
RolloverType		HTTP_LOGGING_ROLLOVER_TYPE ?
RolloverSize		ULONG ?
pSecurityDescriptor	PSECURITY_DESCRIPTOR ?
HTTP_LOGGING_INFO	ENDS
PHTTP_LOGGING_INFO	typedef ptr HTTP_LOGGING_INFO

HTTP_BINDING_INFO	STRUC
Flags			HTTP_PROPERTY_FLAGS <>
RequestQueueHandle	HANDLE ?
HTTP_BINDING_INFO	ENDS
PHTTP_BINDING_INFO	typedef ptr HTTP_BINDING_INFO

endif
if _WIN32_WINNT GE _WIN32_WINNT_WIN7

.enum HTTP_PROTECTION_LEVEL_TYPE {
    HttpProtectionLevelUnrestricted,
    HttpProtectionLevelEdgeRestricted,
    HttpProtectionLevelRestricted
    }


HTTP_PROTECTION_LEVEL_INFO STRUC
Flags			HTTP_PROPERTY_FLAGS <>
Level			HTTP_PROTECTION_LEVEL_TYPE ?
HTTP_PROTECTION_LEVEL_INFO ENDS
PHTTP_PROTECTION_LEVEL_INFO typedef ptr HTTP_PROTECTION_LEVEL_INFO

endif
if _WIN32_WINNT GE 0x0600

HTTP_CREATE_REQUEST_QUEUE_FLAG_OPEN_EXISTING equ (0x00000001)
HTTP_CREATE_REQUEST_QUEUE_FLAG_CONTROLLER equ (0x00000002)

endif

HTTP_RECEIVE_REQUEST_FLAG_COPY_BODY equ 0x00000001
HTTP_RECEIVE_REQUEST_FLAG_FLUSH_BODY equ 0x00000002


if _WIN32_WINNT GE 0x0600

HTTP_RECEIVE_REQUEST_ENTITY_BODY_FLAG_FILL_BUFFER equ 0x00000001

endif

HTTP_SEND_RESPONSE_FLAG_DISCONNECT equ 0x00000001
HTTP_SEND_RESPONSE_FLAG_MORE_DATA equ 0x00000002
HTTP_SEND_RESPONSE_FLAG_BUFFER_DATA equ 0x00000004
HTTP_SEND_RESPONSE_FLAG_ENABLE_NAGLING equ 0x00000008
HTTP_SEND_RESPONSE_FLAG_PROCESS_RANGES equ 0x00000020
HTTP_SEND_RESPONSE_FLAG_OPAQUE equ 0x00000040

HTTP_FLUSH_RESPONSE_FLAG_RECURSIVE equ 0x00000001

HTTP_OPAQUE_ID		typedef ULONGLONG
HTTP_REQUEST_ID		typedef HTTP_OPAQUE_ID
HTTP_CONNECTION_ID	typedef HTTP_OPAQUE_ID
HTTP_RAW_CONNECTION_ID	typedef HTTP_OPAQUE_ID

PHTTP_OPAQUE_ID		typedef ptr ULONGLONG
PHTTP_REQUEST_ID	typedef ptr HTTP_OPAQUE_ID
PHTTP_CONNECTION_ID	typedef ptr HTTP_OPAQUE_ID
PHTTP_RAW_CONNECTION_ID typedef ptr HTTP_OPAQUE_ID

if _WIN32_WINNT GE 0x0600

HTTP_URL_GROUP_ID	typedef HTTP_OPAQUE_ID
HTTP_SERVER_SESSION_ID	typedef HTTP_OPAQUE_ID

PHTTP_URL_GROUP_ID	typedef ptr HTTP_OPAQUE_ID
PHTTP_SERVER_SESSION_ID typedef ptr HTTP_OPAQUE_ID

endif

HTTP_NULL_ID		equ (0)
HTTP_IS_NULL_ID macro pid
	exitm<(HTTP_NULL_ID EQ *(pid))>
	endm
HTTP_SET_NULL_ID macro pid
	exitm<(*(pid) = HTTP_NULL_ID)>
	endm

HTTP_BYTE_RANGE_TO_EOF	equ (-1)

HTTP_BYTE_RANGE		STRUC
StartingOffset		ULARGE_INTEGER <>
Length			ULARGE_INTEGER <>
HTTP_BYTE_RANGE		ENDS
PHTTP_BYTE_RANGE	typedef ptr HTTP_BYTE_RANGE

HTTP_VERSION		STRUC
MajorVersion		USHORT ?
MinorVersion		USHORT ?
HTTP_VERSION		ENDS
PHTTP_VERSION		typedef ptr HTTP_VERSION

HTTP_VERSION_UNKNOWN	equ <{ 0, 0 }>
HTTP_VERSION_0_9	equ <{ 0, 9 }>
HTTP_VERSION_1_0	equ <{ 1, 0 }>
HTTP_VERSION_1_1	equ <{ 1, 1 }>


.enum HTTP_VERB {
    HttpVerbUnparsed,
    HttpVerbUnknown,
    HttpVerbInvalid,
    HttpVerbOPTIONS,
    HttpVerbGET,
    HttpVerbHEAD,
    HttpVerbPOST,
    HttpVerbPUT,
    HttpVerbDELETE,
    HttpVerbTRACE,
    HttpVerbCONNECT,
    HttpVerbTRACK,
    HttpVerbMOVE,
    HttpVerbCOPY,
    HttpVerbPROPFIND,
    HttpVerbPROPPATCH,
    HttpVerbMKCOL,
    HttpVerbLOCK,
    HttpVerbUNLOCK,
    HttpVerbSEARCH,
    HttpVerbMaximum
    }

.enum HTTP_HEADER_ID {
    HttpHeaderCacheControl	    = 0,
    HttpHeaderConnection	    = 1,
    HttpHeaderDate		    = 2,
    HttpHeaderKeepAlive		    = 3,
    HttpHeaderPragma		    = 4,
    HttpHeaderTrailer		    = 5,
    HttpHeaderTransferEncoding	    = 6,
    HttpHeaderUpgrade		    = 7,
    HttpHeaderVia		    = 8,
    HttpHeaderWarning		    = 9,
    HttpHeaderAllow		    = 10,
    HttpHeaderContentLength	    = 11,
    HttpHeaderContentType	    = 12,
    HttpHeaderContentEncoding	    = 13,
    HttpHeaderContentLanguage	    = 14,
    HttpHeaderContentLocation	    = 15,
    HttpHeaderContentMd5	    = 16,
    HttpHeaderContentRange	    = 17,
    HttpHeaderExpires		    = 18,
    HttpHeaderLastModified	    = 19,
    HttpHeaderAccept		    = 20,
    HttpHeaderAcceptCharset	    = 21,
    HttpHeaderAcceptEncoding	    = 22,
    HttpHeaderAcceptLanguage	    = 23,
    HttpHeaderAuthorization	    = 24,
    HttpHeaderCookie		    = 25,
    HttpHeaderExpect		    = 26,
    HttpHeaderFrom		    = 27,
    HttpHeaderHost		    = 28,
    HttpHeaderIfMatch		    = 29,
    HttpHeaderIfModifiedSince	    = 30,
    HttpHeaderIfNoneMatch	    = 31,
    HttpHeaderIfRange		    = 32,
    HttpHeaderIfUnmodifiedSince	    = 33,
    HttpHeaderMaxForwards	    = 34,
    HttpHeaderProxyAuthorization    = 35,
    HttpHeaderReferer		    = 36,
    HttpHeaderRange		    = 37,
    HttpHeaderTe		    = 38,
    HttpHeaderTranslate		    = 39,
    HttpHeaderUserAgent		    = 40,
    HttpHeaderRequestMaximum	    = 41,
    HttpHeaderAcceptRanges	    = 20,
    HttpHeaderAge		    = 21,
    HttpHeaderEtag		    = 22,
    HttpHeaderLocation		    = 23,
    HttpHeaderProxyAuthenticate	    = 24,
    HttpHeaderRetryAfter	    = 25,
    HttpHeaderServer		    = 26,
    HttpHeaderSetCookie		    = 27,
    HttpHeaderVary		    = 28,
    HttpHeaderWwwAuthenticate	    = 29,
    HttpHeaderResponseMaximum	    = 30,
    HttpHeaderMaximum		    = 41
    }


HTTP_KNOWN_HEADER	STRUC
RawValueLength		USHORT ?
pRawValue		PCSTR ?
HTTP_KNOWN_HEADER	ENDS
PHTTP_KNOWN_HEADER	typedef ptr HTTP_KNOWN_HEADER


HTTP_UNKNOWN_HEADER	STRUC
NameLength		USHORT ?
RawValueLength		USHORT ?
pName			PCSTR ?
pRawValue		PCSTR ?
HTTP_UNKNOWN_HEADER	ENDS
PHTTP_UNKNOWN_HEADER	typedef ptr HTTP_UNKNOWN_HEADER

if _WIN32_WINNT GE 0x0600

.enum HTTP_LOG_DATA_TYPE {
    HttpLogDataTypeFields = 0
    }

HTTP_LOG_DATA		STRUC
Type			HTTP_LOG_DATA_TYPE ?
HTTP_LOG_DATA		ENDS
PHTTP_LOG_DATA		typedef ptr HTTP_LOG_DATA

HTTP_LOG_FIELDS_DATA	STRUC
Base			HTTP_LOG_DATA <>
UserNameLength		USHORT ?
UriStemLength		USHORT ?
ClientIpLength		USHORT ?
ServerNameLength	USHORT ?
ServiceNameLength	USHORT ?
ServerIpLength		USHORT ?
MethodLength		USHORT ?
UriQueryLength		USHORT ?
HostLength		USHORT ?
UserAgentLength		USHORT ?
CookieLength		USHORT ?
ReferrerLength		USHORT ?
UserName		PWCHAR ?
UriStem			PWCHAR ?
ClientIp		PCHAR ?
ServerName		PCHAR ?
ServiceName		PCHAR ?
ServerIp		PCHAR ?
Method			PCHAR ?
UriQuery		PCHAR ?
Host			PCHAR ?
UserAgent		PCHAR ?
Cookie			PCHAR ?
Referrer		PCHAR ?
ServerPort		USHORT ?
ProtocolStatus		USHORT ?
Win32Status		ULONG ?
MethodNum		HTTP_VERB ?
SubStatus		USHORT ?
HTTP_LOG_FIELDS_DATA	ENDS
PHTTP_LOG_FIELDS_DATA	typedef ptr HTTP_LOG_FIELDS_DATA

endif

.enum HTTP_DATA_CHUNK_TYPE {
    HttpDataChunkFromMemory,
    HttpDataChunkFromFileHandle,
    HttpDataChunkFromFragmentCache,
    HttpDataChunkFromFragmentCacheEx,
    HttpDataChunkMaximum
    }
PHTTP_DATA_CHUNK_TYPE typedef ptr HTTP_DATA_CHUNK_TYPE

HTTP_DATA_CHUNK		STRUC
DataChunkType		HTTP_DATA_CHUNK_TYPE ?
UNION
 STRUC FromMemory
  pBuffer		PVOID ?
  BufferLength		ULONG ?
 ENDS
 STRUC FromFileHandle
  ByteRange		HTTP_BYTE_RANGE <>
  FileHandle		HANDLE ?
 ENDS
 STRUC FromFragmentCache
  FragmentNameLength	USHORT ?
  pFragmentName		PCWSTR ?
 ENDS
 STRUC FromFragmentCacheEx
  ByteRange		HTTP_BYTE_RANGE <>
  pFragmentName		PCWSTR ?
 ENDS
ENDS
HTTP_DATA_CHUNK		ENDS
PHTTP_DATA_CHUNK	typedef ptr HTTP_DATA_CHUNK

C_ASSERT(TYPE_ALIGNMENTS(HTTP_DATA_CHUNK) eq sizeof(ULONGLONG))

HTTP_REQUEST_HEADERS	STRUC
UnknownHeaderCount	USHORT ?
pUnknownHeaders		PHTTP_UNKNOWN_HEADER ?
TrailerCount		USHORT ?
pTrailers		PHTTP_UNKNOWN_HEADER ?
KnownHeaders		HTTP_KNOWN_HEADER HttpHeaderRequestMaximum dup(<>)
HTTP_REQUEST_HEADERS	ENDS
PHTTP_REQUEST_HEADERS	typedef ptr HTTP_REQUEST_HEADERS

HTTP_RESPONSE_HEADERS	STRUC
UnknownHeaderCount	USHORT ?
pUnknownHeaders		PHTTP_UNKNOWN_HEADER ?
TrailerCount		USHORT ?
pTrailers		PHTTP_UNKNOWN_HEADER ?
KnownHeaders		HTTP_KNOWN_HEADER HttpHeaderResponseMaximum dup(<>)
HTTP_RESPONSE_HEADERS	ENDS
PHTTP_RESPONSE_HEADERS	typedef ptr HTTP_RESPONSE_HEADERS

HTTP_TRANSPORT_ADDRESS	STRUC
pRemoteAddress		PSOCKADDR ?
pLocalAddress		PSOCKADDR ?
HTTP_TRANSPORT_ADDRESS	ENDS
PHTTP_TRANSPORT_ADDRESS typedef ptr HTTP_TRANSPORT_ADDRESS


HTTP_COOKED_URL		STRUC
FullUrlLength		USHORT ?
HostLength		USHORT ?
AbsPathLength		USHORT ?
QueryStringLength	USHORT ?
pFullUrl		PCWSTR ?
pHost			PCWSTR ?
pAbsPath		PCWSTR ?
pQueryString		PCWSTR ?
HTTP_COOKED_URL		ENDS
PHTTP_COOKED_URL	typedef ptr HTTP_COOKED_URL

HTTP_URL_CONTEXT	typedef ULONGLONG


if _WIN32_WINNT GE 0x0600

HTTP_URL_FLAG_REMOVE_ALL equ 0x00000001

.enum HTTP_AUTH_STATUS {
    HttpAuthStatusSuccess,
    HttpAuthStatusNotAuthenticated,
    HttpAuthStatusFailure
    }


.enum HTTP_REQUEST_AUTH_TYPE {
    HttpRequestAuthTypeNone = 0,
    HttpRequestAuthTypeBasic,
    HttpRequestAuthTypeDigest,
    HttpRequestAuthTypeNTLM,
    HttpRequestAuthTypeNegotiate,
    HttpRequestAuthTypeKerberos
    }

endif

HTTP_SSL_CLIENT_CERT_INFO STRUC
CertFlags		ULONG ?
CertEncodedSize		ULONG ?
pCertEncoded		PUCHAR ?
Token			HANDLE ?
CertDeniedByMapper	BOOLEAN ?
HTTP_SSL_CLIENT_CERT_INFO ENDS
PHTTP_SSL_CLIENT_CERT_INFO typedef ptr HTTP_SSL_CLIENT_CERT_INFO

if _WIN32_WINNT GE _WIN32_WINNT_WIN7

HTTP_RECEIVE_SECURE_CHANNEL_TOKEN equ 0x1

endif

HTTP_SSL_INFO		STRUC
ServerCertKeySize	USHORT ?
ConnectionKeySize	USHORT ?
ServerCertIssuerSize	ULONG ?
ServerCertSubjectSize	ULONG ?
pServerCertIssuer	PCSTR ?
pServerCertSubject	PCSTR ?
pClientCertInfo		PHTTP_SSL_CLIENT_CERT_INFO ?
SslClientCertNegotiated ULONG ?
HTTP_SSL_INFO		ENDS
PHTTP_SSL_INFO		typedef ptr HTTP_SSL_INFO


if _WIN32_WINNT GE 0x0600

.enum HTTP_REQUEST_INFO_TYPE {
    HttpRequestInfoTypeAuth,
    HttpRequestInfoTypeChannelBind
    }

HTTP_REQUEST_INFO	STRUC
InfoType		HTTP_REQUEST_INFO_TYPE ?
InfoLength		ULONG ?
pInfo			PVOID ?
HTTP_REQUEST_INFO	ENDS
PHTTP_REQUEST_INFO	typedef ptr HTTP_REQUEST_INFO

ifndef __SECSTATUS_DEFINED__
SECURITY_STATUS		typedef LONG
__SECSTATUS_DEFINED__ equ 1
endif

HTTP_REQUEST_AUTH_FLAG_TOKEN_FOR_CACHED_CRED equ (0x00000001)

HTTP_REQUEST_AUTH_INFO	STRUC
AuthStatus		HTTP_AUTH_STATUS ?
SecStatus		SECURITY_STATUS ?
Flags			ULONG ?
AuthType		HTTP_REQUEST_AUTH_TYPE ?
AccessToken		HANDLE ?
ContextAttributes	ULONG ?
PackedContextLength	ULONG ?
PackedContextType	ULONG ?
PackedContext		PVOID ?
MutualAuthDataLength	ULONG ?
pMutualAuthData		PCHAR ?
PackageNameLength	USHORT ?
pPackageName		PWSTR ?
HTTP_REQUEST_AUTH_INFO	ENDS
PHTTP_REQUEST_AUTH_INFO typedef ptr HTTP_REQUEST_AUTH_INFO

endif

HTTP_REQUEST_V1		STRUC
Flags			ULONG ?
ConnectionId		HTTP_CONNECTION_ID ?
RequestId		HTTP_REQUEST_ID ?
UrlContext		HTTP_URL_CONTEXT ?
Version			HTTP_VERSION <>
Verb			HTTP_VERB ?
UnknownVerbLength	USHORT ?
RawUrlLength		USHORT ?
pUnknownVerb		PCSTR ?
pRawUrl			PCSTR ?
CookedUrl		HTTP_COOKED_URL <>
Address			HTTP_TRANSPORT_ADDRESS <>
Headers			HTTP_REQUEST_HEADERS <>
BytesReceived		ULONGLONG ?
EntityChunkCount	USHORT ?
pEntityChunks		PHTTP_DATA_CHUNK ?
RawConnectionId		HTTP_RAW_CONNECTION_ID ?
pSslInfo		PHTTP_SSL_INFO ?
HTTP_REQUEST_V1		ENDS
PHTTP_REQUEST_V1	typedef ptr HTTP_REQUEST_V1

if _WIN32_WINNT GE 0x0600

ifdef __cplusplus
.template HTTP_REQUEST_V2 : public HTTP_REQUEST_V1
    RequestInfoCount	USHORT ?
    pRequestInfo	PHTTP_REQUEST_INFO ?
.ends
else
HTTP_REQUEST_V2		STRUC
HTTP_REQUEST_V1		<>
RequestInfoCount	USHORT ?
pRequestInfo		PHTTP_REQUEST_INFO ?
HTTP_REQUEST_V2		ENDS
endif
PHTTP_REQUEST_V2	typedef ptr HTTP_REQUEST_V2

HTTP_REQUEST		typedef HTTP_REQUEST_V2

else

HTTP_REQUEST		typedef HTTP_REQUEST_V1

endif

PHTTP_REQUEST		typedef ptr HTTP_REQUEST


HTTP_REQUEST_FLAG_MORE_ENTITY_BODY_EXISTS equ 0x00000001
HTTP_REQUEST_FLAG_IP_ROUTED equ 0x00000002

HTTP_RESPONSE_V1	STRUC
Flags			ULONG ?
Version			HTTP_VERSION <>
StatusCode		USHORT ?
ReasonLength		USHORT ?	;; in bytes not including the '\0'
pReason			PCSTR ?
Headers			HTTP_RESPONSE_HEADERS <>
EntityChunkCount	USHORT ?
pEntityChunks		PHTTP_DATA_CHUNK ?
HTTP_RESPONSE_V1	ENDS
PHTTP_RESPONSE_V1	typedef ptr HTTP_RESPONSE_V1

if _WIN32_WINNT GE 0x0600

HTTP_RESPONSE_FLAG_MULTIPLE_ENCODINGS_AVAILABLE equ 0x00000001

.enum HTTP_RESPONSE_INFO_TYPE {
    HttpResponseInfoTypeMultipleKnownHeaders,
    HttpResponseInfoTypeAuthenticationProperty,
    HttpResponseInfoTypeQoSProperty,
    HttpResponseInfoTypeChannelBind
    }

HTTP_RESPONSE_INFO	STRUC
Type			HTTP_RESPONSE_INFO_TYPE ?
Length			ULONG ?
pInfo			PVOID ?
HTTP_RESPONSE_INFO	ENDS
PHTTP_RESPONSE_INFO	typedef ptr HTTP_RESPONSE_INFO

HTTP_RESPONSE_INFO_FLAGS_PRESERVE_ORDER equ 0x00000001

HTTP_MULTIPLE_KNOWN_HEADERS STRUC
HeaderId		HTTP_HEADER_ID ?
Flags			ULONG ?
KnownHeaderCount	USHORT ?
KnownHeaders		PHTTP_KNOWN_HEADER ?
HTTP_MULTIPLE_KNOWN_HEADERS ENDS
PHTTP_MULTIPLE_KNOWN_HEADERS typedef ptr HTTP_MULTIPLE_KNOWN_HEADERS

ifdef __cplusplus

else

HTTP_RESPONSE_V2	STRUC
HTTP_RESPONSE_V1	<>
ResponseInfoCount	USHORT ?
pResponseInfo		PHTTP_RESPONSE_INFO ?
HTTP_RESPONSE_V2	ENDS
PHTTP_RESPONSE_V2	typedef ptr HTTP_RESPONSE_V2

endif

HTTP_RESPONSE		typedef HTTP_RESPONSE_V2

else

HTTP_RESPONSE		typedef HTTP_RESPONSE_V1

endif

PHTTP_RESPONSE		typedef ptr HTTP_RESPONSE

HTTPAPI_VERSION		STRUC
HttpApiMajorVersion	dw ?
HttpApiMinorVersion	dw ?
HTTPAPI_VERSION		ENDS
PHTTPAPI_VERSION	typedef ptr HTTPAPI_VERSION


if _WIN32_WINNT GE 0x0600

HTTPAPI_VERSION_2	equ <{ 2, 0 }>

endif

HTTPAPI_VERSION_1	equ <{ 1, 0 }>

.enum HTTP_CACHE_POLICY_TYPE {
    HttpCachePolicyNocache,
    HttpCachePolicyUserInvalidates,
    HttpCachePolicyTimeToLive,
    HttpCachePolicyMaximum
    }


HTTP_CACHE_POLICY	STRUC
Policy			HTTP_CACHE_POLICY_TYPE ?
SecondsToLive		ULONG ?
HTTP_CACHE_POLICY	ENDS
PHTTP_CACHE_POLICY	typedef ptr HTTP_CACHE_POLICY


.enum HTTP_SERVICE_CONFIG_ID {
    HttpServiceConfigIPListenList,
    HttpServiceConfigSSLCertInfo,
    HttpServiceConfigUrlAclInfo,
    HttpServiceConfigTimeout,
    HttpServiceConfigCache,
if _WIN32_WINNT GE _WIN32_WINNT_WIN8
    HttpServiceConfigSslSniCertInfo,
    HttpServiceConfigSslCcsCertInfo,
endif
    HttpServiceConfigMax
    }


.enum HTTP_SERVICE_CONFIG_QUERY_TYPE {
    HttpServiceConfigQueryExact,
    HttpServiceConfigQueryNext,
    HttpServiceConfigQueryMax
    }


HTTP_SERVICE_CONFIG_SSL_KEY STRUC
pIpPort			PSOCKADDR ?
HTTP_SERVICE_CONFIG_SSL_KEY ENDS
PHTTP_SERVICE_CONFIG_SSL_KEY typedef ptr HTTP_SERVICE_CONFIG_SSL_KEY

if _WIN32_WINNT GE _WIN32_WINNT_WIN8

HTTP_SERVICE_CONFIG_SSL_SNI_KEY STRUC
IpPort			SOCKADDR_STORAGE <>
Host			PWSTR ?
HTTP_SERVICE_CONFIG_SSL_SNI_KEY ENDS
PHTTP_SERVICE_CONFIG_SSL_SNI_KEY typedef ptr HTTP_SERVICE_CONFIG_SSL_SNI_KEY

HTTP_SERVICE_CONFIG_SSL_CCS_KEY STRUC
LocalAddress		SOCKADDR_STORAGE <>
HTTP_SERVICE_CONFIG_SSL_CCS_KEY ENDS
PHTTP_SERVICE_CONFIG_SSL_CCS_KEY typedef ptr HTTP_SERVICE_CONFIG_SSL_CCS_KEY

endif


HTTP_SERVICE_CONFIG_SSL_PARAM STRUC
SslHashLength		ULONG ?
pSslHash		PVOID ?
AppId			GUID <>
pSslCertStoreName	PWSTR ?
DefaultCertCheckMode	dd ?
DefaultRevocationFreshnessTime dd ?
DefaultRevocationUrlRetrievalTimeout dd ?
pDefaultSslCtlIdentifier PWSTR ?
pDefaultSslCtlStoreName PWSTR ?
DefaultFlags		dd ?
HTTP_SERVICE_CONFIG_SSL_PARAM ENDS
PHTTP_SERVICE_CONFIG_SSL_PARAM typedef ptr HTTP_SERVICE_CONFIG_SSL_PARAM

HTTP_SERVICE_CONFIG_SSL_FLAG_USE_DS_MAPPER equ 0x00000001
HTTP_SERVICE_CONFIG_SSL_FLAG_NEGOTIATE_CLIENT_CERT equ 0x00000002
if _WIN32_WINNT LT 0x0600
HTTP_SERVICE_CONFIG_SSL_FLAG_NO_RAW_FILTER equ 0x00000004
endif

HTTP_SERVICE_CONFIG_SSL_SET STRUC
KeyDesc			HTTP_SERVICE_CONFIG_SSL_KEY <>
ParamDesc		HTTP_SERVICE_CONFIG_SSL_PARAM <>
HTTP_SERVICE_CONFIG_SSL_SET ENDS
PHTTP_SERVICE_CONFIG_SSL_SET typedef ptr HTTP_SERVICE_CONFIG_SSL_SET

if _WIN32_WINNT GE _WIN32_WINNT_WIN8

HTTP_SERVICE_CONFIG_SSL_SNI_SET STRUC
KeyDesc			HTTP_SERVICE_CONFIG_SSL_SNI_KEY <>
ParamDesc		HTTP_SERVICE_CONFIG_SSL_PARAM <>
HTTP_SERVICE_CONFIG_SSL_SNI_SET ENDS
PHTTP_SERVICE_CONFIG_SSL_SNI_SET typedef ptr HTTP_SERVICE_CONFIG_SSL_SNI_SET

HTTP_SERVICE_CONFIG_SSL_CCS_SET STRUC
KeyDesc			HTTP_SERVICE_CONFIG_SSL_CCS_KEY <>
ParamDesc		HTTP_SERVICE_CONFIG_SSL_PARAM <>
HTTP_SERVICE_CONFIG_SSL_CCS_SET ENDS
PHTTP_SERVICE_CONFIG_SSL_CCS_SET typedef ptr HTTP_SERVICE_CONFIG_SSL_CCS_SET

endif

HTTP_SERVICE_CONFIG_SSL_QUERY STRUC
QueryDesc		HTTP_SERVICE_CONFIG_QUERY_TYPE ?
KeyDesc			HTTP_SERVICE_CONFIG_SSL_KEY <>
dwToken			dd ?
HTTP_SERVICE_CONFIG_SSL_QUERY ENDS
PHTTP_SERVICE_CONFIG_SSL_QUERY typedef ptr HTTP_SERVICE_CONFIG_SSL_QUERY

if _WIN32_WINNT GE _WIN32_WINNT_WIN8

HTTP_SERVICE_CONFIG_SSL_SNI_QUERY STRUC
QueryDesc		HTTP_SERVICE_CONFIG_QUERY_TYPE ?
KeyDesc			HTTP_SERVICE_CONFIG_SSL_SNI_KEY <>
dwToken			dd ?
HTTP_SERVICE_CONFIG_SSL_SNI_QUERY ENDS
PHTTP_SERVICE_CONFIG_SSL_SNI_QUERY typedef ptr HTTP_SERVICE_CONFIG_SSL_SNI_QUERY

HTTP_SERVICE_CONFIG_SSL_CCS_QUERY STRUC
QueryDesc		HTTP_SERVICE_CONFIG_QUERY_TYPE ?
KeyDesc			HTTP_SERVICE_CONFIG_SSL_CCS_KEY <>
dwToken			dd ?
HTTP_SERVICE_CONFIG_SSL_CCS_QUERY ENDS
PHTTP_SERVICE_CONFIG_SSL_CCS_QUERY typedef ptr HTTP_SERVICE_CONFIG_SSL_CCS_QUERY

endif

HTTP_SERVICE_CONFIG_IP_LISTEN_PARAM STRUC
AddrLength		USHORT ?
pAddress		PSOCKADDR ?
HTTP_SERVICE_CONFIG_IP_LISTEN_PARAM ENDS
PHTTP_SERVICE_CONFIG_IP_LISTEN_PARAM typedef ptr HTTP_SERVICE_CONFIG_IP_LISTEN_PARAM


HTTP_SERVICE_CONFIG_IP_LISTEN_QUERY STRUC
AddrCount		ULONG ?
AddrList		SOCKADDR_STORAGE ANYSIZE_ARRAY dup(<>)
HTTP_SERVICE_CONFIG_IP_LISTEN_QUERY ENDS
PHTTP_SERVICE_CONFIG_IP_LISTEN_QUERY typedef ptr HTTP_SERVICE_CONFIG_IP_LISTEN_QUERY

HTTP_SERVICE_CONFIG_URLACL_KEY STRUC
pUrlPrefix		PWSTR ?
HTTP_SERVICE_CONFIG_URLACL_KEY ENDS
PHTTP_SERVICE_CONFIG_URLACL_KEY typedef ptr HTTP_SERVICE_CONFIG_URLACL_KEY


HTTP_SERVICE_CONFIG_URLACL_PARAM STRUC
pStringSecurityDescriptor PWSTR ?
HTTP_SERVICE_CONFIG_URLACL_PARAM ENDS
PHTTP_SERVICE_CONFIG_URLACL_PARAM typedef ptr HTTP_SERVICE_CONFIG_URLACL_PARAM


HTTP_SERVICE_CONFIG_URLACL_SET STRUC
KeyDesc			HTTP_SERVICE_CONFIG_URLACL_KEY <>
ParamDesc		HTTP_SERVICE_CONFIG_URLACL_PARAM <>
HTTP_SERVICE_CONFIG_URLACL_SET ENDS
PHTTP_SERVICE_CONFIG_URLACL_SET typedef ptr HTTP_SERVICE_CONFIG_URLACL_SET


HTTP_SERVICE_CONFIG_URLACL_QUERY STRUC
QueryDesc		HTTP_SERVICE_CONFIG_QUERY_TYPE ?
KeyDesc			HTTP_SERVICE_CONFIG_URLACL_KEY <>
dwToken			dd ?
HTTP_SERVICE_CONFIG_URLACL_QUERY ENDS
PHTTP_SERVICE_CONFIG_URLACL_QUERY typedef ptr HTTP_SERVICE_CONFIG_URLACL_QUERY


.enum HTTP_SERVICE_CONFIG_CACHE_KEY {
    MaxCacheResponseSize = 0,
    CacheRangeChunkSize
    }
PHTTP_SERVICE_CONFIG_CACHE_KEY typedef ptr HTTP_SERVICE_CONFIG_CACHE_KEY

HTTP_SERVICE_CONFIG_CACHE_PARAM typedef ULONG
PHTTP_SERVICE_CONFIG_CACHE_PARAM typedef ptr HTTP_SERVICE_CONFIG_CACHE_PARAM


HTTP_SERVICE_CONFIG_CACHE_SET STRUC
KeyDesc			HTTP_SERVICE_CONFIG_CACHE_KEY ?
ParamDesc		HTTP_SERVICE_CONFIG_CACHE_PARAM ?
HTTP_SERVICE_CONFIG_CACHE_SET ENDS
PHTTP_SERVICE_CONFIG_CACHE_SET typedef ptr HTTP_SERVICE_CONFIG_CACHE_SET


.pragma pack(pop)

;ULONG
HttpInitialize proto WINAPI \
	       Version: HTTPAPI_VERSION,
		 Flags: ULONG,
	     pReserved: PVOID


;ULONG
HttpTerminate proto WINAPI \
		 Flags: ULONG,
	     pReserved: PVOID

;ULONG
HttpCreateHttpHandle proto WINAPI \
       pReqQueueHandle: PHANDLE,
	      Reserved: ULONG


if _WIN32_WINNT GE 0x0600

;ULONG
HttpCreateRequestQueue proto WINAPI \
	       Version: HTTPAPI_VERSION,
		 pName: PCWSTR,
   pSecurityAttributes: PSECURITY_ATTRIBUTES,
		  Fags: ULONG,
       pReqQueueHandle: PHANDLE


;ULONG
HttpCloseRequestQueue proto WINAPI \
	ReqQueueHandle: HANDLE


;ULONG
HttpSetRequestQueueProperty proto WINAPI \
		Handle: HANDLE,
	      Property: HTTP_SERVER_PROPERTY,
  pPropertyInformation: PVOID,
PropertyInformationLength: ULONG,
	      Reserved: ULONG,
	     pReserved: PVOID


;ULONG
HttpQueryRequestQueueProperty proto WINAPI \
		Handle: HANDLE,
	      Property: HTTP_SERVER_PROPERTY,
  pPropertyInformation: PVOID,
PropertyInformationLength: ULONG,
	      Reserved: ULONG,
	 pReturnLength: PULONG,
	     pReserved: PVOID


;ULONG
HttpShutdownRequestQueue proto WINAPI \
	ReqQueueHandle: HANDLE


endif ;; _WIN32_WINNT GE 0x0600

;ULONG
HttpReceiveClientCertificate proto WINAPI \
	ReqQueueHandle: HANDLE,
	  ConnectionId: HTTP_CONNECTION_ID,
		 Flags: ULONG,
    pSslClientCertInfo: PHTTP_SSL_CLIENT_CERT_INFO,
 SslClientCertInfoSize: ULONG,
	pBytesReceived: PULONG,
	   pOverlapped: LPOVERLAPPED


if _WIN32_WINNT GE 0x0600

;ULONG
HttpCreateServerSession proto WINAPI \
	       Version: HTTPAPI_VERSION,
      pServerSessionId: PHTTP_SERVER_SESSION_ID,
	      Reserved: ULONG


;ULONG
HttpCloseServerSession proto WINAPI \
       ServerSessionId: HTTP_SERVER_SESSION_ID


;ULONG
HttpQueryServerSessionProperty proto WINAPI \
       ServerSessionId: HTTP_SERVER_SESSION_ID,
	      Property: HTTP_SERVER_PROPERTY,
  pPropertyInformation: PVOID,
PropertyInformationLength: ULONG,
	 pReturnLength: PULONG


;ULONG
HttpSetServerSessionProperty proto WINAPI \
       ServerSessionId: HTTP_SERVER_SESSION_ID,
	      Property: HTTP_SERVER_PROPERTY,
  pPropertyInformation: PVOID,
PropertyInformationLength: ULONG


endif ;; _WIN32_WINNT GE 0x0600

;ULONG
HttpAddUrl proto WINAPI \
	ReqQueueHandle: HANDLE,
    pFullyQualifiedUrl: PCWSTR,
	     pReserved: PVOID


;ULONG
HttpRemoveUrl proto WINAPI \
	ReqQueueHandle: HANDLE,
    pFullyQualifiedUrl: PCWSTR


if _WIN32_WINNT GE 0x0600

;ULONG
HttpCreateUrlGroup proto WINAPI \
       ServerSessionId: HTTP_SERVER_SESSION_ID,
	   pUrlGroupId: PHTTP_URL_GROUP_ID,
	      Reserved: ULONG


;ULONG
HttpCloseUrlGroup proto WINAPI \
	    UrlGroupId: HTTP_URL_GROUP_ID


;ULONG
HttpAddUrlToUrlGroup proto WINAPI \
	    UrlGroupId: HTTP_URL_GROUP_ID,
    pFullyQualifiedUrl: PCWSTR,
	    UrlContext: HTTP_URL_CONTEXT,
	      Reserved: ULONG


;ULONG
HttpRemoveUrlFromUrlGroup proto WINAPI \
	    UrlGroupId: HTTP_URL_GROUP_ID,
    pFullyQualifiedUrl: PCWSTR,
		 Flags: ULONG


;ULONG
HttpSetUrlGroupProperty proto WINAPI \
	    UrlGroupId: HTTP_URL_GROUP_ID,
	      Property: HTTP_SERVER_PROPERTY,
  pPropertyInformation: PVOID,
PropertyInformationLength: ULONG


;ULONG
HttpQueryUrlGroupProperty proto WINAPI \
	    UrlGroupId: HTTP_URL_GROUP_ID,
	      Property: HTTP_SERVER_PROPERTY,
  pPropertyInformation: PVOID,
PropertyInformationLength: ULONG,
	 pReturnLength: PULONG


endif ;; _WIN32_WINNT GE 0x0600

if _WIN32_WINNT GE _WIN32_WINNT_WIN8

;ULONG
HttpPrepareUrl proto WINAPI \
	      Reserved: PVOID,
		 Flags: ULONG,
		   Url: PCWSTR,
	   PreparedUrl: ptr PWSTR

endif

;ULONG
HttpReceiveHttpRequest proto WINAPI \
	ReqQueueHandle: HANDLE,
	     RequestId: HTTP_REQUEST_ID,
		 Flags: ULONG,
	pRequestBuffer: PHTTP_REQUEST,
   RequestBufferLength: ULONG,
	pBytesReturned: PULONG,
	   pOverlapped: LPOVERLAPPED


;ULONG
HttpReceiveRequestEntityBody proto WINAPI \
	ReqQueueHandle: HANDLE,
	     RequestId: HTTP_REQUEST_ID,
		 Flags: ULONG,
	       pBuffer: PVOID,
    EntityBufferLength: ULONG,
	pBytesReturned: PULONG,
	   pOverlapped: LPOVERLAPPED


if _WIN32_WINNT GE 0x0600

;ULONG
HttpSendHttpResponse proto WINAPI \
	ReqQueueHandle: HANDLE,
	     RequestId: HTTP_REQUEST_ID,
		 Flags: ULONG,
	 pHttpResponse: PHTTP_RESPONSE,
	  pCachePolicy: PHTTP_CACHE_POLICY,
	    pBytesSent: PULONG,
	    pReserved1: PVOID,
	     Reserved2: ULONG,
	   pOverlapped: LPOVERLAPPED,
	      pLogData: PHTTP_LOG_DATA


else

;ULONG
HttpSendHttpResponse proto WINAPI \
	ReqQueueHandle: HANDLE,
	     RequestId: HTTP_REQUEST_ID,
		 Flags: ULONG,
	 pHttpResponse: PHTTP_RESPONSE,
	    pReserved1: PVOID,
	    pBytesSent: PULONG,
	    pReserved2: PVOID,
	     Reserved3: ULONG,
	   pOverlapped: LPOVERLAPPED,
	    pReserved4: PVOID


endif

if _WIN32_WINNT GE 0x0600

;ULONG
HttpSendResponseEntityBody proto WINAPI \
	ReqQueueHandle: HANDLE,
	     RequestId: HTTP_REQUEST_ID,
		 Flags: ULONG,
      EntityChunkCount: USHORT,
	 pEntityChunks: PHTTP_DATA_CHUNK,
	    pBytesSent: PULONG,
	    pReserved1: PVOID,
	     Reserved2: ULONG,
	   pOverlapped: LPOVERLAPPED,
	      pLogData: PHTTP_LOG_DATA


else

HttpSendResponseEntityBody proto WINAPI \
	ReqQueueHandle: HANDLE,
	     RequestId: HTTP_REQUEST_ID,
		 Flags: ULONG,
      EntityChunkCount: USHORT,
	 pEntityChunks: PHTTP_DATA_CHUNK,
	    pBytesSent: PULONG,
	    pReserved1: PVOID,
	     Reserved2: ULONG,
	   pOverlapped: LPOVERLAPPED,
	    pReserved3: PVOID


endif

;ULONG
HttpWaitForDisconnect proto WINAPI \
	ReqQueueHandle: HANDLE,
	  ConnectionId: HTTP_CONNECTION_ID,
	   pOverlapped: LPOVERLAPPED


if _WIN32_WINNT GE 0x0600

;ULONG
HttpWaitForDisconnectEx proto WINAPI \
	ReqQueueHandle: HANDLE,
	  ConnectionId: HTTP_CONNECTION_ID,
	      Reserved: ULONG,
	   pOverlapped: LPOVERLAPPED


;ULONG
HttpCancelHttpRequest proto WINAPI \
	ReqQueueHandle: HANDLE,
	     RequestId: HTTP_REQUEST_ID,
	   pOverlapped: LPOVERLAPPED


;ULONG
HttpWaitForDemandStart proto WINAPI \
	ReqQueueHandle: HANDLE,
	   pOverlapped: LPOVERLAPPED



endif

;ULONG
HttpFlushResponseCache proto WINAPI \
	ReqQueueHandle: HANDLE,
	    pUrlPrefix: PCWSTR,
		 Flags: ULONG,
	   pOverlapped: LPOVERLAPPED


;ULONG
HttpAddFragmentToCache proto WINAPI \
	ReqQueueHandle: HANDLE,
	    pUrlPrefix: PCWSTR,
	    pDataChunk: PHTTP_DATA_CHUNK,
	  pCachePolicy: PHTTP_CACHE_POLICY,
	   pOverlapped: LPOVERLAPPED


;ULONG
HttpReadFragmentFromCache proto WINAPI \
	ReqQueueHandle: HANDLE,
	    pUrlPrefix: PCWSTR,
	    pByteRange: PHTTP_BYTE_RANGE,
	       pBuffer: PVOID,
	  BufferLength: ULONG,
	    pBytesRead: PULONG,
	   pOverlapped: LPOVERLAPPED


;ULONG
HttpSetServiceConfiguration proto WINAPI \
	 ServiceHandle: HANDLE,
	      ConfigId: HTTP_SERVICE_CONFIG_ID,
    pConfigInformation: PVOID,
ConfigInformationLength: ULONG,
	   pOverlapped: LPOVERLAPPED

;ULONG
HttpDeleteServiceConfiguration proto WINAPI \
	 ServiceHandle: HANDLE,
	      ConfigId: HTTP_SERVICE_CONFIG_ID,
    pConfigInformation: PVOID,
ConfigInformationLength: ULONG,
	   pOverlapped: LPOVERLAPPED


;ULONG
HttpQueryServiceConfiguration proto WINAPI \
	 ServiceHandle: HANDLE,
	      ConfigId: HTTP_SERVICE_CONFIG_ID,
		pInput: PVOID,
	   InputLength: ULONG,
	       pOutput: PVOID,
	  OutputLength: ULONG,
	 pReturnLength: PULONG,
	   pOverlapped: LPOVERLAPPED

endif


endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
endif ;; __HTTP_H__
