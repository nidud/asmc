.pragma list(push, 0)

ifndef _P2P_H_
_P2P_H_ equ <>
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef MIDL_PASS
include specstrings.inc
include winsock2.inc
include pnrpns.inc
include ws2tcpip.inc
endif

if NTDDI_VERSION LT NTDDI_VISTA
ifndef NO_P2P_PNRP
NO_P2P_PNRP		equ <>
endif
ifndef NO_P2P_COLLABORATION
NO_P2P_COLLABORATION	equ <>
endif
endif

PEER_RECORD_CHANGE_TYPE typedef SDWORD
PEER_RECORD_ADDED	equ 1
PEER_RECORD_UPDATED	equ 2
PEER_RECORD_DELETED	equ 3
PEER_RECORD_EXPIRED	equ 4

PEER_CONNECTION_STATUS typedef SDWORD
PEER_CONNECTED		equ 1
PEER_DISCONNECTED	equ 2
PEER_CONNECTION_FAILED	equ 3

peer_connection_flags_tag typedef SDWORD
PEER_CONNECTION_NEIGHBOR equ 0x0001
PEER_CONNECTION_DIRECT	equ 0x0002

PEER_CONNECTION_FLAGS	typedef SDWORD
PEER_RECORD_FLAG_AUTOREFRESH equ 0x0001
PEER_RECORD_FLAG_DELETED equ 0x0002

HPEEREVENT		typedef ptr
PHPEEREVENT		typedef ptr HPEEREVENT

HPEERENUM		typedef ptr
PHPEERENUM		typedef ptr HPEERENUM

PEER_VERSION_DATA	STRUC
wVersion		dw ?
wHighestVersion		dw ?
PEER_VERSION_DATA	ENDS
PPEER_VERSION_DATA	typedef ptr PEER_VERSION_DATA

PEER_DATA		STRUC
cbData			ULONG ?
pbData			PBYTE ?
PEER_DATA		ENDS
PPEER_DATA		typedef ptr PEER_DATA
PCPEER_DATA		typedef ptr PEER_DATA

PEER_RECORD		STRUC
dwSize			dd ?
_type			GUID <>
id			GUID <>
dwVersion		dd ?
dwFlags			dd ?
pwzCreatorId		PWSTR ?
pwzModifiedById		PWSTR ?
pwzAttributes		PWSTR ?
ftCreation		FILETIME <>
ftExpiration		FILETIME <>
ftLastModified		FILETIME <>
securityData		PEER_DATA <>
data			PEER_DATA <>
PEER_RECORD		ENDS
PPEER_RECORD		typedef ptr PEER_RECORD

PEER_ADDRESS		STRUC
dwSize			dd ?
sin6			SOCKADDR_IN6 <>
PEER_ADDRESS		ENDS
PPEER_ADDRESS		typedef ptr PEER_ADDRESS
PCPEER_ADDRESS		typedef ptr PEER_ADDRESS


PEER_CONNECTION_INFO	STRUC
dwSize			dd ?
dwFlags			dd ?
ullConnectionId		ULONGLONG ?
ullNodeId		ULONGLONG ?
pwzPeerId		PWSTR ?
address			PEER_ADDRESS <>
PEER_CONNECTION_INFO	ENDS

PEER_EVENT_INCOMING_DATA STRUC
dwSize			dd ?
ullConnectionId		ULONGLONG ?
_type			GUID <>
data			PEER_DATA <>
PEER_EVENT_INCOMING_DATA ENDS
PPEER_EVENT_INCOMING_DATA typedef ptr PEER_EVENT_INCOMING_DATA

PEER_EVENT_RECORD_CHANGE_DATA STRUC
dwSize			dd ?
changeType		PEER_RECORD_CHANGE_TYPE ?
recordId		GUID <>
recordType		GUID <>
PEER_EVENT_RECORD_CHANGE_DATA ENDS
PPEER_EVENT_RECORD_CHANGE_DATA typedef ptr PEER_EVENT_RECORD_CHANGE_DATA

PEER_EVENT_CONNECTION_CHANGE_DATA STRUC
dwSize			dd ?
status			PEER_CONNECTION_STATUS ?
ullConnectionId		ULONGLONG ?
ullNodeId		ULONGLONG ?
if NTDDI_VERSION GE NTDDI_VISTA
ullNextConnectionId	ULONGLONG ?
hrConnectionFailedReason HRESULT ?
endif
PEER_EVENT_CONNECTION_CHANGE_DATA ENDS
PPEER_EVENT_CONNECTION_CHANGE_DATA typedef ptr PEER_EVENT_CONNECTION_CHANGE_DATA

PEER_EVENT_SYNCHRONIZED_DATA STRUC
dwSize			dd ?
recordType		GUID <>
PEER_EVENT_SYNCHRONIZED_DATA ENDS
PPEER_EVENT_SYNCHRONIZED_DATA typedef ptr PEER_EVENT_SYNCHRONIZED_DATA

ifndef NO_P2P_GRAPH
ifndef MIDL_PASS

PHGRAPH			typedef ptr PVOID
HGRAPH			typedef ptr PVOID

PEER_GRAPH_VERSION	equ MAKEWORD(1,0)

PEER_GRAPH_EVENT_TYPE	typedef SDWORD
PEER_GRAPH_EVENT_STATUS_CHANGED		equ 1
PEER_GRAPH_EVENT_PROPERTY_CHANGED	equ 2
PEER_GRAPH_EVENT_RECORD_CHANGED		equ 3
PEER_GRAPH_EVENT_DIRECT_CONNECTION	equ 4
PEER_GRAPH_EVENT_NEIGHBOR_CONNECTION	equ 5
PEER_GRAPH_EVENT_INCOMING_DATA		equ 6
PEER_GRAPH_EVENT_CONNECTION_REQUIRED	equ 7
PEER_GRAPH_EVENT_NODE_CHANGED		equ 8
PEER_GRAPH_EVENT_SYNCHRONIZED		equ 9

PEER_NODE_CHANGE_TYPE	typedef SDWORD
PEER_NODE_CHANGE_CONNECTED	equ 1
PEER_NODE_CHANGE_DISCONNECTED	equ 2
PEER_NODE_CHANGE_UPDATED	equ 3

PEER_GRAPH_STATUS_FLAGS		typedef SDWORD
PEER_GRAPH_STATUS_LISTENING		equ 0x0001
PEER_GRAPH_STATUS_HAS_CONNECTIONS	equ 0x0002
PEER_GRAPH_STATUS_SYNCHRONIZED		equ 0x0004

PEER_GRAPH_PROPERTY_FLAGS	typedef SDWORD
PEER_GRAPH_PROPERTY_HEARTBEATS		equ 0x0001
PEER_GRAPH_PROPERTY_DEFER_EXPIRATION	equ 0x0002

PEER_GRAPH_SCOPE		typedef SDWORD
PEER_GRAPH_SCOPE_ANY		equ 0
PEER_GRAPH_SCOPE_GLOBAL		equ 1
PEER_GRAPH_SCOPE_SITELOCAL	equ 2
PEER_GRAPH_SCOPE_LINKLOCAL	equ 3
PEER_GRAPH_SCOPE_LOOPBACK	equ 4


PEER_GRAPH_PROPERTIES	STRUC
dwSize			dd ?
dwFlags			dd ?	;; PEER_GRAPH_PROPERTY_FLAGS
dwScope			dd ?
dwMaxRecordSize		dd ?
pwzGraphId		PWSTR ?
pwzCreatorId		PWSTR ?
pwzFriendlyName		PWSTR ?
pwzComment		PWSTR ?
ulPresenceLifetime	ULONG ?
cPresenceMax		ULONG ?
PEER_GRAPH_PROPERTIES	ENDS
PPEER_GRAPH_PROPERTIES	typedef ptr PEER_GRAPH_PROPERTIES

PEER_NODE_INFO		STRUC
dwSize			dd ?
ullNodeId		ULONGLONG ?
pwzPeerId		PWSTR ?
cAddresses		ULONG ?
pAddresses		PPEER_ADDRESS ?
pwzAttributes		PWSTR ?
PEER_NODE_INFO		ENDS
PPEER_NODE_INFO		typedef ptr PEER_NODE_INFO

PEER_EVENT_NODE_CHANGE_DATA STRUC
dwSize			dd ?
changeType		PEER_NODE_CHANGE_TYPE ?
ullNodeId		ULONGLONG ?
pwzPeerId		PWSTR ?
PEER_EVENT_NODE_CHANGE_DATA ENDS
PPEER_EVENT_NODE_CHANGE_DATA typedef ptr PEER_EVENT_NODE_CHANGE_DATA

PEER_GRAPH_EVENT_REGISTRATION STRUC
eventType		PEER_GRAPH_EVENT_TYPE ?
pType			LPGUID ?
PEER_GRAPH_EVENT_REGISTRATION ENDS
PPEER_GRAPH_EVENT_REGISTRATION typedef ptr PEER_GRAPH_EVENT_REGISTRATION

PEER_GRAPH_EVENT_DATA	STRUC
eventType		PEER_GRAPH_EVENT_TYPE ?
UNION
 dwStatus		PEER_GRAPH_STATUS_FLAGS ?
 incomingData		PEER_EVENT_INCOMING_DATA <>
 recordChangeData	PEER_EVENT_RECORD_CHANGE_DATA <>
 connectionChangeData	PEER_EVENT_CONNECTION_CHANGE_DATA <>
 nodeChangeData		PEER_EVENT_NODE_CHANGE_DATA <>
 synchronizedData	PEER_EVENT_SYNCHRONIZED_DATA <>
ENDS
PEER_GRAPH_EVENT_DATA	ENDS
PPEER_GRAPH_EVENT_DATA	typedef ptr PEER_GRAPH_EVENT_DATA


CALLBACK(PFNPEER_VALIDATE_RECORD, :HGRAPH, :PVOID, :PPEER_RECORD, :PEER_RECORD_CHANGE_TYPE)
CALLBACK(PFNPEER_SECURE_RECORD, :HGRAPH, :PVOID, :PPEER_RECORD, :PEER_RECORD_CHANGE_TYPE, :ptr)
CALLBACK(PFNPEER_FREE_SECURITY_DATA, :HGRAPH, :PVOID, :PPEER_DATA)
CALLBACK(PFNPEER_ON_PASSWORD_AUTH_FAILED, :HGRAPH, :PVOID)

PEER_SECURITY_INTERFACE STRUC
dwSize			dd ?
pwzSspFilename		PWSTR ?
pwzPackageName		PWSTR ?
cbSecurityInfo		ULONG ?
pbSecurityInfo		PBYTE ?
pvContext		PVOID ?
pfnValidateRecord	PFNPEER_VALIDATE_RECORD ?
pfnSecureRecord		PFNPEER_SECURE_RECORD ?
pfnFreeSecurityData	PFNPEER_FREE_SECURITY_DATA ?
pfnAuthFailed		PFNPEER_ON_PASSWORD_AUTH_FAILED ?
PEER_SECURITY_INTERFACE ENDS
PPEER_SECURITY_INTERFACE typedef ptr PEER_SECURITY_INTERFACE

.pragma comment(lib, p2pgraph)

PeerGraphStartup proto WINAPI \
     wVersionRequested: WORD,
	  pVersionData: PPEER_VERSION_DATA


;HRESULT
PeerGraphShutdown proto WINAPI

;VOID
PeerGraphFreeData proto WINAPI \
		pvData: PVOID


;HRESULT
PeerGraphGetItemCount proto WINAPI \
	     hPeerEnum: HPEERENUM,
		pCount: ptr ULONG


;HRESULT
PeerGraphGetNextItem proto WINAPI \
	     hPeerEnum: HPEERENUM,
		pCount: ptr ULONG,
	     pppvItems: ptr PVOID

;HRESULT
PeerGraphEndEnumeration proto WINAPI \
	     hPeerEnum: HPEERENUM


;HRESULT
PeerGraphCreate proto WINAPI \
      pGraphProperties: PPEER_GRAPH_PROPERTIES,
       pwzDatabaseName: PCWSTR,
    pSecurityInterface: PPEER_SECURITY_INTERFACE,
	       phGraph: ptr HGRAPH


PeerGraphOpen proto WINAPI \
	    pwzGraphId: PCWSTR,
	     pwzPeerId: PCWSTR,
       pwzDatabaseName: PCWSTR,
    pSecurityInterface: PPEER_SECURITY_INTERFACE,
cRecordTypeSyncPrecedence: ULONG,
pRecordTypeSyncPrecedence: ptr GUID,
	       phGraph: ptr HGRAPH


PeerGraphListen proto WINAPI \
		hGraph: HGRAPH,
	       dwScope: DWORD,
	     dwScopeId: DWORD,
		 wPort: WORD

PeerGraphConnect proto WINAPI \
		hGraph: HGRAPH,
	     pwzPeerId: PCWSTR,
	      pAddress: PPEER_ADDRESS,
      pullConnectionId: ptr ULONGLONG


PeerGraphClose proto WINAPI \
		hGraph: HGRAPH

PeerGraphDelete proto WINAPI \
	    pwzGraphId: PCWSTR,
	     pwzPeerId: PCWSTR,
       pwzDatabaseName: PCWSTR


PeerGraphGetStatus proto WINAPI \
		hGraph: HGRAPH,
	     pdwStatus: ptr DWORD

PeerGraphGetProperties proto WINAPI \
		hGraph: HGRAPH,
     ppGraphProperties: ptr PPEER_GRAPH_PROPERTIES

PeerGraphSetProperties proto WINAPI \
		hGraph: HGRAPH,
      pGraphProperties: PPEER_GRAPH_PROPERTIES


PeerGraphRegisterEvent proto WINAPI \
		hGraph: HGRAPH,
		hEvent: HANDLE,
   cEventRegistrations: ULONG,
   pEventRegistrations: ptr PEER_GRAPH_EVENT_REGISTRATION,
	   phPeerEvent: ptr HPEEREVENT

PeerGraphUnregisterEvent proto WINAPI \
	    hPeerEvent: HPEEREVENT

PeerGraphGetEventData proto WINAPI \
	    hPeerEvent: HPEEREVENT,
	   ppEventData: ptr PPEER_GRAPH_EVENT_DATA


PeerGraphGetRecord proto WINAPI \
		hGraph: HGRAPH,
	     pRecordId: ptr GUID,
	      ppRecord: ptr PPEER_RECORD

PeerGraphAddRecord proto WINAPI \
		hGraph: HGRAPH,
	       pRecord: PPEER_RECORD,
	     pRecordId: ptr GUID

PeerGraphUpdateRecord proto WINAPI \
		hGraph: HGRAPH,
	       pRecord: PPEER_RECORD

PeerGraphDeleteRecord proto WINAPI \
		hGraph: HGRAPH,
	     pRecordId: ptr GUID,
		fLocal: BOOL

PeerGraphEnumRecords proto WINAPI \
		hGraph: HGRAPH,
	   pRecordType: ptr GUID,
	     pwzPeerId: PCWSTR,
	    phPeerEnum: ptr HPEERENUM

PeerGraphSearchRecords proto WINAPI \
		hGraph: HGRAPH,
	   pwzCriteria: PCWSTR,
	    phPeerEnum: ptr HPEERENUM

PeerGraphExportDatabase proto WINAPI \
		hGraph: HGRAPH,
	   pwzFilePath: PCWSTR

PeerGraphImportDatabase proto WINAPI \
		hGraph: HGRAPH,
	   pwzFilePath: PCWSTR

PeerGraphValidateDeferredRecords proto WINAPI \
		hGraph: HGRAPH,
	    cRecordIds: ULONG,
	    pRecordIds: ptr GUID

PeerGraphOpenDirectConnection proto WINAPI \
		hGraph: HGRAPH,
	     pwzPeerId: PCWSTR,
	      pAddress: PPEER_ADDRESS,
      pullConnectionId: ptr ULONGLONG

PeerGraphSendData proto WINAPI \
		hGraph: HGRAPH,
       ullConnectionId: ULONGLONG,
		 pType: ptr GUID,
		cbData: ULONG,
		pvData: PVOID

PeerGraphCloseDirectConnection proto WINAPI \
		hGraph: HGRAPH,
       ullConnectionId: ULONGLONG

PeerGraphEnumConnections proto WINAPI \
		hGraph: HGRAPH,
	       dwFlags: DWORD,
	    phPeerEnum: ptr HPEERENUM

PeerGraphEnumNodes proto WINAPI \
		hGraph: HGRAPH,
	     pwzPeerId: PCWSTR,
	    phPeerEnum: ptr HPEERENUM

PeerGraphSetPresence proto WINAPI \
		hGraph: HGRAPH,
	      fPresent: BOOL

PeerGraphGetNodeInfo proto WINAPI \
		hGraph: HGRAPH,
	     ullNodeId: ULONGLONG,
	    ppNodeInfo: ptr PPEER_NODE_INFO

PeerGraphSetNodeAttributes proto WINAPI \
		hGraph: HGRAPH,
	 pwzAttributes: PCWSTR

PeerGraphPeerTimeToUniversalTime proto WINAPI \
		hGraph: HGRAPH,
	   pftPeerTime: ptr FILETIME,
      pftUniversalTime: ptr FILETIME

PeerGraphUniversalTimeToPeerTime proto WINAPI \
		hGraph: HGRAPH,
      pftUniversalTime: ptr FILETIME,
	   pftPeerTime: ptr FILETIME


endif ;;   MIDL_PASS
endif ;; NO_P2P_GRAPH

.pragma comment(lib, p2p)

if ( NOT (defined (NO_P2P_GROUP)) OR ( NOT defined (NO_P2P_IDENTITY)))
ifndef MIDL_PASS

include wincrypt.inc

PeerFreeData proto WINAPI \
		pvData: LPCVOID

PeerGetItemCount proto WINAPI \
	     hPeerEnum: HPEERENUM,
		pCount: ptr ULONG

PeerGetNextItem proto WINAPI \
	     hPeerEnum: HPEERENUM,
		pCount: ptr ULONG,
	     pppvItems: ptr PVOID

PeerEndEnumeration proto WINAPI \
	     hPeerEnum: HPEERENUM


endif ;; MIDL_PASS
endif

ifndef NO_P2P_GROUP

PHGROUP			typedef ptr PVOID
HGROUP			typedef ptr PVOID

PEER_ROLE_ID		typedef GUID

if NTDDI_VERSION GE NTDDI_VISTA
PEER_GROUP_VERSION	equ MAKEWORD(1,1)
else
PEER_GROUP_VERSION	equ MAKEWORD(1,0)
endif

PEER_GROUP_EVENT_TYPE		typedef SDWORD
PEER_GROUP_EVENT_STATUS_CHANGED		equ 1
PEER_GROUP_EVENT_PROPERTY_CHANGED	equ 2
PEER_GROUP_EVENT_RECORD_CHANGED		equ 3
PEER_GROUP_EVENT_DIRECT_CONNECTION	equ 4
PEER_GROUP_EVENT_NEIGHBOR_CONNECTION	equ 5
PEER_GROUP_EVENT_INCOMING_DATA		equ 6
PEER_GROUP_EVENT_MEMBER_CHANGED		equ 8
PEER_GROUP_EVENT_CONNECTION_FAILED	equ 10
PEER_GROUP_EVENT_AUTHENTICATION_FAILED	equ 11

PEER_GROUP_STATUS		typedef SDWORD
PEER_GROUP_STATUS_LISTENING		equ 0x0001
PEER_GROUP_STATUS_HAS_CONNECTIONS	equ 0x0002

PEER_GROUP_PROPERTY_FLAGS	typedef SDWORD
PEER_MEMBER_DATA_OPTIONAL	equ 0x0001
PEER_DISABLE_PRESENCE		equ 0x0002
PEER_DEFER_EXPIRATION		equ 0x0004


if NTDDI_VERSION GE NTDDI_VISTA
PEER_GROUP_AUTHENTICATION_SCHEME	typedef SDWORD
PEER_GROUP_GMC_AUTHENTICATION		equ 0x00000001
PEER_GROUP_PASSWORD_AUTHENTICATION	equ 0x00000002
endif

PEER_MEMBER_FLAGS	typedef SDWORD
PEER_MEMBER_PRESENT	equ 0x0001

PEER_MEMBER_CHANGE_TYPE typedef SDWORD
PEER_MEMBER_CONNECTED	equ 1
PEER_MEMBER_DISCONNECTED equ 2
PEER_MEMBER_UPDATED	equ 3
PEER_MEMBER_JOINED	equ 4
PEER_MEMBER_LEFT	equ 5

PEER_GROUP_ISSUE_CREDENTIAL_FLAGS typedef SDWORD
PEER_GROUP_STORE_CREDENTIALS equ 0x0001

ifndef MIDL_PASS

PEER_CREDENTIAL_INFO	STRUC
dwSize			dd ?
dwFlags			dd ?
pwzFriendlyName		PWSTR ?
pPublicKey		PCERT_PUBLIC_KEY_INFO ?
pwzIssuerPeerName	PWSTR ?
pwzIssuerFriendlyName	PWSTR ?
ftValidityStart		FILETIME <>
ftValidityEnd		FILETIME <>
cRoles			ULONG ?
pRoles			LPGUID ?
PEER_CREDENTIAL_INFO	ENDS
PPEER_CREDENTIAL_INFO	typedef ptr PEER_CREDENTIAL_INFO

PEER_MEMBER		STRUC
dwSize			dd ?
dwFlags			dd ?
pwzIdentity		PWSTR ?
pwzAttributes		PWSTR ?
ullNodeId		ULONGLONG ?
cAddresses		ULONG ?
pAddresses		PPEER_ADDRESS ?
pCredentialInfo		PPEER_CREDENTIAL_INFO ?
PEER_MEMBER		ENDS
PPEER_MEMBER		typedef ptr PEER_MEMBER

PEER_INVITATION_INFO	STRUC
dwSize			dd ?
dwFlags			dd ?
pwzCloudName		PWSTR ?
dwScope			dd ?
dwCloudFlags		dd ?
pwzGroupPeerName	PWSTR ?
pwzIssuerPeerName	PWSTR ?
pwzSubjectPeerName	PWSTR ?
pwzGroupFriendlyName	PWSTR ?
pwzIssuerFriendlyName	PWSTR ?
pwzSubjectFriendlyName	PWSTR ?
ftValidityStart		FILETIME <>
ftValidityEnd		FILETIME <>
cRoles			ULONG ?
pRoles			LPGUID ?
cClassifiers		ULONG ?
ppwzClassifiers		PWSTR ?
pSubjectPublicKey	PCERT_PUBLIC_KEY_INFO ?
if NTDDI_VERSION GE NTDDI_VISTA
authScheme		PEER_GROUP_AUTHENTICATION_SCHEME ?
endif
PEER_INVITATION_INFO	ENDS
PPEER_INVITATION_INFO	typedef ptr PEER_INVITATION_INFO

endif ;; MIDL_PASS


PEER_GROUP_PROPERTIES	STRUC
dwSize			dd ?
dwFlags			dd ?	;; PEER_GROUP_PROPERTY_FLAGS
pwzCloud		PWSTR ?
pwzClassifier		PWSTR ?
pwzGroupPeerName	PWSTR ?
pwzCreatorPeerName	PWSTR ?
pwzFriendlyName		PWSTR ?
pwzComment		PWSTR ?
ulMemberDataLifetime	ULONG ?
ulPresenceLifetime	ULONG ?
if NTDDI_VERSION GE NTDDI_VISTA
dwAuthenticationSchemes dd ?	;; PEER_GROUP_AUTHENTICATION_SCHEME
pwzGroupPassword	PWSTR ?
groupPasswordRole	PEER_ROLE_ID <>
endif
PEER_GROUP_PROPERTIES	ENDS
PPEER_GROUP_PROPERTIES	typedef ptr PEER_GROUP_PROPERTIES

PEER_EVENT_MEMBER_CHANGE_DATA STRUC
dwSize			dd ?
changeType		PEER_MEMBER_CHANGE_TYPE ?
pwzIdentity		PWSTR ?
PEER_EVENT_MEMBER_CHANGE_DATA ENDS
PPEER_EVENT_MEMBER_CHANGE_DATA typedef ptr PEER_EVENT_MEMBER_CHANGE_DATA

PEER_GROUP_EVENT_REGISTRATION STRUC
eventType		PEER_GROUP_EVENT_TYPE ?
pType			LPGUID ?
PEER_GROUP_EVENT_REGISTRATION ENDS
PPEER_GROUP_EVENT_REGISTRATION typedef ptr PEER_GROUP_EVENT_REGISTRATION

ifdef MIDL_PASS
else  ;; NOT MIDL_PASS
PEER_GROUP_EVENT_DATA	STRUC
eventType		PEER_GROUP_EVENT_TYPE ?
UNION
 dwStatus		PEER_GROUP_STATUS ?
 incomingData		PEER_EVENT_INCOMING_DATA <>
 recordChangeData	PEER_EVENT_RECORD_CHANGE_DATA <>
 connectionChangeData	PEER_EVENT_CONNECTION_CHANGE_DATA <>
 memberChangeData	PEER_EVENT_MEMBER_CHANGE_DATA <>
 hrConnectionFailedReason HRESULT ?
ENDS
PEER_GROUP_EVENT_DATA	ENDS
PPEER_GROUP_EVENT_DATA	typedef ptr PEER_GROUP_EVENT_DATA
endif ;; MIDL_PASS

PEER_NAME_PAIR		STRUC
dwSize			dd ?
pwzPeerName		PWSTR ?
pwzFriendlyName		PWSTR ?
PEER_NAME_PAIR		ENDS
PPEER_NAME_PAIR		typedef ptr PEER_NAME_PAIR

ifndef MIDL_PASS

PeerGroupStartup proto WINAPI \
     wVersionRequested: WORD,
	  pVersionData: PPEER_VERSION_DATA

PeerGroupShutdown proto WINAPI

PeerGroupCreate proto WINAPI \
	   pProperties: PPEER_GROUP_PROPERTIES,
	       phGroup: ptr HGROUP

PeerGroupOpen proto WINAPI \
	   pwzIdentity: PCWSTR,
      pwzGroupPeerName: PCWSTR,
	      pwzCloud: PCWSTR,
	       phGroup: ptr HGROUP

PeerGroupJoin proto WINAPI \
	   pwzIdentity: PCWSTR,
	 pwzInvitation: PCWSTR,
	      pwzCloud: PCWSTR,
	       phGroup: ptr HGROUP



if NTDDI_VERSION GE NTDDI_VISTA
PeerGroupPasswordJoin proto WINAPI \
	   pwzIdentity: PCWSTR,
	 pwzInvitation: PCWSTR,
	   pwzPassword: PCWSTR,
	      pwzCloud: PCWSTR,
	       phGroup: ptr HGROUP

endif

PeerGroupConnect proto WINAPI \
		hGroup: HGROUP


if NTDDI_VERSION GE NTDDI_VISTA
PeerGroupConnectByAddress proto WINAPI \
		hGroup: HGROUP,
	    cAddresses: ULONG,
	    pAddresses: PPEER_ADDRESS
endif

PeerGroupClose proto WINAPI \
		hGroup: HGROUP


PeerGroupDelete proto WINAPI \
	   pwzIdentity: PCWSTR,
      pwzGroupPeerName: PCWSTR


PeerGroupCreateInvitation proto WINAPI \
		hGroup: HGROUP,
       pwzIdentityInfo: PCWSTR,
	 pftExpiration: ptr FILETIME,
		cRoles: ULONG,
		pRoles: ptr GUID,
	ppwzInvitation: ptr PWSTR


if NTDDI_VERSION GE NTDDI_VISTA

PeerGroupCreatePasswordInvitation proto WINAPI \
		hGroup: HGROUP,
	ppwzInvitation: ptr PWSTR

endif

PeerGroupParseInvitation proto WINAPI \
	 pwzInvitation: PCWSTR,
      ppInvitationInfo: ptr PPEER_INVITATION_INFO


PeerGroupGetStatus proto WINAPI \
		hGroup: HGROUP,
	     pdwStatus: ptr DWORD


PeerGroupGetProperties proto WINAPI \
		hGroup: HGROUP,
	  ppProperties: ptr PPEER_GROUP_PROPERTIES


PeerGroupSetProperties proto WINAPI \
		hGroup: HGROUP,
	   pProperties: PPEER_GROUP_PROPERTIES


PeerGroupEnumMembers proto WINAPI \
		hGroup: HGROUP,
	       dwFlags: DWORD,
	   pwzIdentity: PCWSTR,
	    phPeerEnum: ptr HPEERENUM


PeerGroupOpenDirectConnection proto WINAPI \
		hGroup: HGROUP,
	   pwzIdentity: PCWSTR,
	      pAddress: PPEER_ADDRESS,
      pullConnectionId: ptr ULONGLONG


PeerGroupCloseDirectConnection proto WINAPI \
		hGroup: HGROUP,
       ullConnectionId: ULONGLONG


PeerGroupEnumConnections proto WINAPI \
		hGroup: HGROUP,
	       dwFlags: DWORD,
	    phPeerEnum: ptr HPEERENUM


PeerGroupSendData proto WINAPI \
		hGroup: HGROUP,
       ullConnectionId: ULONGLONG,
		 pType: ptr GUID,
		cbData: ULONG,
		pvData: PVOID

PeerGroupRegisterEvent proto WINAPI \
		hGroup: HGROUP,
		hEvent: HANDLE,
    cEventRegistration: DWORD,
   pEventRegistrations: ptr PEER_GROUP_EVENT_REGISTRATION,
	   phPeerEvent: ptr HPEEREVENT


PeerGroupUnregisterEvent proto WINAPI \
	    hPeerEvent: HPEEREVENT


PeerGroupGetEventData proto WINAPI \
	    hPeerEvent: HPEEREVENT,
	   ppEventData: ptr PPEER_GROUP_EVENT_DATA



PeerGroupGetRecord proto WINAPI \
		hGroup: HGROUP,
	     pRecordId: ptr GUID,
	      ppRecord: ptr PPEER_RECORD


PeerGroupAddRecord proto WINAPI \
		hGroup: HGROUP,
	       pRecord: PPEER_RECORD,
	     pRecordId: ptr GUID


PeerGroupUpdateRecord proto WINAPI \
		hGroup: HGROUP,
	       pRecord: PPEER_RECORD


PeerGroupDeleteRecord proto WINAPI \
		hGroup: HGROUP,
	     pRecordId: ptr GUID


PeerGroupEnumRecords proto WINAPI \
		hGroup: HGROUP,
	   pRecordType: ptr GUID,
	    phPeerEnum: ptr HPEERENUM


PeerGroupSearchRecords proto WINAPI \
		hGroup: HGROUP,
	   pwzCriteria: PCWSTR,
	    phPeerEnum: ptr HPEERENUM


PeerGroupExportDatabase proto WINAPI \
		hGroup: HGROUP,
	   pwzFilePath: PCWSTR


PeerGroupImportDatabase proto WINAPI \
		hGroup: HGROUP,
	   pwzFilePath: PCWSTR


PeerGroupIssueCredentials proto WINAPI \
		hGroup: HGROUP,
    pwzSubjectIdentity: PCWSTR,
       pCredentialInfo: ptr PEER_CREDENTIAL_INFO,
	       dwFlags: DWORD,
	ppwzInvitation: ptr PWSTR


PeerGroupExportConfig proto WINAPI \
		hGroup: HGROUP,
	   pwzPassword: PCWSTR,
	       ppwzXML: ptr PWSTR


PeerGroupImportConfig proto WINAPI \
		pwzXML: PCWSTR,
	   pwzPassword: PCWSTR,
	    fOverwrite: BOOL,
	  ppwzIdentity: ptr PWSTR,
	     ppwzGroup: ptr PWSTR


PeerGroupPeerTimeToUniversalTime proto WINAPI \
		hGroup: HGROUP,
	   pftPeerTime: ptr FILETIME,
      pftUniversalTime: ptr FILETIME


PeerGroupUniversalTimeToPeerTime proto WINAPI \
		hGroup: HGROUP,
      pftUniversalTime: ptr FILETIME,
	   pftPeerTime: ptr FILETIME


if NTDDI_VERSION GE NTDDI_WIN7

PeerGroupResumePasswordAuthentication proto WINAPI \
		hGroup: HGROUP,
      hPeerEventHandle: HPEEREVENT

endif

endif ;; NIDL_PASS

endif ;; NO_P2P_GROUP

ifndef NO_P2P_IDENTITY
ifndef MIDL_PASS

PeerIdentityCreate proto WINAPI \
	 pwzClassifier: PCWSTR,
       pwzFriendlyName: PCWSTR,
	    hCryptProv: HCRYPTPROV,
	  ppwzIdentity: ptr PWSTR

PeerIdentityGetFriendlyName proto WINAPI \
	   pwzIdentity: PCWSTR,
      ppwzFriendlyName: ptr PWSTR

PeerIdentitySetFriendlyName proto WINAPI \
	   pwzIdentity: PCWSTR,
       pwzFriendlyName: PCWSTR

PeerIdentityGetCryptKey proto WINAPI \
	   pwzIdentity: PCWSTR,
	   phCryptProv: ptr HCRYPTPROV

PeerIdentityDelete proto WINAPI \
	   pwzIdentity: PCWSTR

PeerEnumIdentities proto WINAPI \
	    phPeerEnum: ptr HPEERENUM

PeerEnumGroups proto WINAPI \
	   pwzIdentity: PCWSTR,
	    phPeerEnum: ptr HPEERENUM

PeerCreatePeerName proto WINAPI \
	   pwzIdentity: PCWSTR,
	 pwzClassifier: PCWSTR,
	  ppwzPeerName: ptr PWSTR

PeerIdentityGetXML proto WINAPI \
	   pwzIdentity: PCWSTR,
       ppwzIdentityXML: ptr PWSTR

PeerIdentityExport proto WINAPI \
	   pwzIdentity: PCWSTR,
	   pwzPassword: PCWSTR,
	 ppwzExportXML: ptr PWSTR

PeerIdentityImport proto WINAPI \
	  pwzImportXML: PCWSTR,
	   pwzPassword: PCWSTR,
	  ppwzIdentity: ptr PWSTR

PeerIdentityGetDefault proto WINAPI \
	  ppwzPeerName: ptr PWSTR


endif ;; MIDL_PASS
endif ;; NO_P2P_IDENTITY

ifndef NO_P2P_COLLABORATION

PEER_COLLAB_VERSION	equ MAKEWORD(1,0)

PEER_SIGNIN_FLAGS	typedef SDWORD
PEER_SIGNIN_NONE	equ 0x0
PEER_SIGNIN_NEAR_ME	equ 0x1
PEER_SIGNIN_INTERNET	equ 0x2
PEER_SIGNIN_ALL		equ PEER_SIGNIN_INTERNET or PEER_SIGNIN_NEAR_ME

PEER_WATCH_PERMISSION	typedef SDWORD
PEER_WATCH_BLOCKED	equ 0
PEER_WATCH_ALLOWED	equ 1

PEER_PUBLICATION_SCOPE	typedef SDWORD
PEER_PUBLICATION_SCOPE_NONE	equ 0x0
PEER_PUBLICATION_SCOPE_NEAR_ME	equ 0x1
PEER_PUBLICATION_SCOPE_INTERNET equ 0x2
PEER_PUBLICATION_SCOPE_ALL	equ PEER_PUBLICATION_SCOPE_NEAR_ME or PEER_PUBLICATION_SCOPE_INTERNET

PEER_APPLICATION	STRUC
id			GUID <>
data			PEER_DATA <>
pwzDescription		PWSTR ?
PEER_APPLICATION	ENDS
PPEER_APPLICATION	typedef ptr PEER_APPLICATION
PCPEER_APPLICATION	typedef ptr PEER_APPLICATION

PEER_OBJECT		STRUC
id			GUID <>
data			PEER_DATA <>
dwPublicationScope	dd ?
PEER_OBJECT		ENDS
PPEER_OBJECT		typedef ptr PEER_OBJECT
PCPEER_OBJECT		typedef ptr PEER_OBJECT

PEER_CONTACT		STRUC
pwzPeerName		PWSTR ?
pwzNickName		PWSTR ?
pwzDisplayName		PWSTR ?
pwzEmailAddress		PWSTR ?
fWatch			BOOL ?
WatcherPermissions	PEER_WATCH_PERMISSION ?
credentials		PEER_DATA <>
PEER_CONTACT		ENDS
PPEER_CONTACT		typedef ptr PEER_CONTACT
PCPEER_CONTACT		typedef ptr PEER_CONTACT

PEER_ENDPOINT		STRUC
address			PEER_ADDRESS <>
pwzEndpointName		PWSTR ?
PEER_ENDPOINT		ENDS
PPEER_ENDPOINT		typedef ptr PEER_ENDPOINT
PCPEER_ENDPOINT		typedef ptr PEER_ENDPOINT

PEER_PEOPLE_NEAR_ME	STRUC
pwzNickName		PWSTR ?
endpoint		PEER_ENDPOINT <>
id			GUID <>
PEER_PEOPLE_NEAR_ME	ENDS
PPEER_PEOPLE_NEAR_ME	typedef ptr PEER_PEOPLE_NEAR_ME
PCPEER_PEOPLE_NEAR_ME	typedef ptr PEER_PEOPLE_NEAR_ME
PPPEER_PEOPLE_NEAR_ME	typedef ptr PPEER_PEOPLE_NEAR_ME

ifndef MIDL_PASS

PeerCollabStartup proto WINAPI \
     wVersionRequested: WORD

PeerCollabShutdown proto WINAPI

PeerCollabSignin proto WINAPI \
	    hwndParent: HWND,
       dwSigninOptions: DWORD

PeerCollabSignout proto WINAPI \
       dwSigninOptions: DWORD

PeerCollabGetSigninOptions proto WINAPI \
      pdwSigninOptions: ptr DWORD


endif ;;MIDL_PASS

PEER_INVITATION_RESPONSE_TYPE	typedef SDWORD
PEER_INVITATION_RESPONSE_DECLINED	equ 0
PEER_INVITATION_RESPONSE_ACCEPTED	equ 1
PEER_INVITATION_RESPONSE_EXPIRED	equ 2
PEER_INVITATION_RESPONSE_ERROR		equ 3

PEER_APPLICATION_REGISTRATION_TYPE typedef SDWORD
PEER_APPLICATION_CURRENT_USER		equ 0
PEER_APPLICATION_ALL_USERS		equ 1

PEER_INVITATION		STRUC
applicationId		GUID <>
applicationData		PEER_DATA <>
pwzMessage		PWSTR ?
PEER_INVITATION		ENDS
PPEER_INVITATION	typedef ptr PEER_INVITATION
PCPEER_INVITATION	typedef ptr PEER_INVITATION

PEER_INVITATION_RESPONSE STRUC
action			PEER_INVITATION_RESPONSE_TYPE ?
pwzMessage		PWSTR ?
hrExtendedInfo		HRESULT ?
PEER_INVITATION_RESPONSE ENDS
PPEER_INVITATION_RESPONSE typedef ptr PEER_INVITATION_RESPONSE
PCPEER_INVITATION_RESPONSE typedef ptr PEER_INVITATION_RESPONSE

PEER_APP_LAUNCH_INFO	STRUC
pContact		PPEER_CONTACT ?
pEndpoint		PPEER_ENDPOINT ?
pInvitation		PPEER_INVITATION ?
PEER_APP_LAUNCH_INFO	ENDS
 PPEER_APP_LAUNCH_INFO	typedef ptr PEER_APP_LAUNCH_INFO
PCPEER_APP_LAUNCH_INFO	typedef ptr PEER_APP_LAUNCH_INFO

PEER_APPLICATION_REGISTRATION_INFO STRUC
application		PEER_APPLICATION <>
pwzApplicationToLaunch	PWSTR ?
pwzApplicationArguments PWSTR ?
dwPublicationScope	dd ?
PEER_APPLICATION_REGISTRATION_INFO ENDS
PPEER_APPLICATION_REGISTRATION_INFO typedef ptr PEER_APPLICATION_REGISTRATION_INFO
PCPEER_APPLICATION_REGISTRATION_INFO typedef ptr PEER_APPLICATION_REGISTRATION_INFO

ifndef MIDL_PASS

PeerCollabAsyncInviteContact proto WINAPI \
	     pcContact: PCPEER_CONTACT,
	    pcEndpoint: PCPEER_ENDPOINT,
	  pcInvitation: PCPEER_INVITATION,
		hEvent: HANDLE,
	  phInvitation: ptr HANDLE


PeerCollabGetInvitationResponse proto WINAPI \
	   hInvitation: HANDLE,
  ppInvitationResponse: ptr PPEER_INVITATION_RESPONSE


PeerCollabCancelInvitation proto WINAPI \
	   hInvitation: HANDLE


PeerCollabCloseHandle proto WINAPI \
	   hInvitation: HANDLE


PeerCollabInviteContact proto WINAPI \
	     pcContact: PCPEER_CONTACT,
	    pcEndpoint: PCPEER_ENDPOINT,
	  pcInvitation: PCPEER_INVITATION,
	    ppResponse: ptr PPEER_INVITATION_RESPONSE


PeerCollabAsyncInviteEndpoint proto WINAPI \
	    pcEndpoint: PCPEER_ENDPOINT,
	  pcInvitation: PCPEER_INVITATION,
		hEvent: HANDLE,
	  phInvitation: ptr HANDLE


PeerCollabInviteEndpoint proto WINAPI \
	    pcEndpoint: PCPEER_ENDPOINT,
	  pcInvitation: PCPEER_INVITATION,
	    ppResponse: ptr PPEER_INVITATION_RESPONSE


PeerCollabGetAppLaunchInfo proto WINAPI \
	  ppLaunchInfo: ptr PPEER_APP_LAUNCH_INFO


PeerCollabRegisterApplication proto WINAPI \
	 pcApplication: PCPEER_APPLICATION_REGISTRATION_INFO,
      registrationType: PEER_APPLICATION_REGISTRATION_TYPE


PeerCollabUnregisterApplication proto WINAPI \
	pApplicationId: ptr GUID,
      registrationType: PEER_APPLICATION_REGISTRATION_TYPE


PeerCollabGetApplicationRegistrationInfo proto WINAPI \
	pApplicationId: ptr GUID,
      registrationType: PEER_APPLICATION_REGISTRATION_TYPE,
	 ppApplication: ptr PPEER_APPLICATION_REGISTRATION_INFO


PeerCollabEnumApplicationRegistrationInfo proto WINAPI \
      registrationType: PEER_APPLICATION_REGISTRATION_TYPE,
	    phPeerEnum: ptr HPEERENUM

endif ;; MIDL_PASS

PEER_PRESENCE_STATUS	typedef SDWORD
PEER_PRESENCE_OFFLINE		equ 0
PEER_PRESENCE_OUT_TO_LUNCH	equ 1
PEER_PRESENCE_AWAY		equ 2
PEER_PRESENCE_BE_RIGHT_BACK	equ 3
PEER_PRESENCE_IDLE		equ 4
PEER_PRESENCE_BUSY		equ 5
PEER_PRESENCE_ON_THE_PHONE	equ 6
PEER_PRESENCE_ONLINE		equ 7

PEER_PRESENCE_INFO	STRUC
status			PEER_PRESENCE_STATUS ?
pwzDescriptiveText	PWSTR ?
PEER_PRESENCE_INFO	ENDS
PPEER_PRESENCE_INFO	typedef ptr PEER_PRESENCE_INFO
PCPEER_PRESENCE_INFO	typedef ptr PEER_PRESENCE_INFO

ifndef MIDL_PASS

PeerCollabGetPresenceInfo proto WINAPI \
	    pcEndpoint: PCPEER_ENDPOINT,
	ppPresenceInfo: ptr PPEER_PRESENCE_INFO


PeerCollabEnumApplications proto WINAPI \
	    pcEndpoint: PCPEER_ENDPOINT,
	pApplicationId: ptr GUID,
	    phPeerEnum: ptr HPEERENUM


PeerCollabEnumObjects proto WINAPI \
	    pcEndpoint: PCPEER_ENDPOINT,
	     pObjectId: ptr GUID,
	    phPeerEnum: ptr HPEERENUM


PeerCollabEnumEndpoints proto WINAPI \
	     pcContact: PCPEER_CONTACT,
	    phPeerEnum: ptr HPEERENUM


PeerCollabRefreshEndpointData proto WINAPI \
	    pcEndpoint: PCPEER_ENDPOINT


PeerCollabDeleteEndpointData proto WINAPI \
	    pcEndpoint: PCPEER_ENDPOINT


PeerCollabQueryContactData proto WINAPI \
	    pcEndpoint: PCPEER_ENDPOINT,
       ppwzContactData: ptr PWSTR


PeerCollabSubscribeEndpointData proto WINAPI \
	    pcEndpoint: PCPEER_ENDPOINT


PeerCollabUnsubscribeEndpointData proto WINAPI \
	    pcEndpoint: PCPEER_ENDPOINT


PeerCollabSetPresenceInfo proto WINAPI \
	pcPresenceInfo: PCPEER_PRESENCE_INFO


PeerCollabGetEndpointName proto WINAPI \
      ppwzEndpointName: ptr PWSTR


PeerCollabSetEndpointName proto WINAPI \
       pwzEndpointName: PCWSTR


PeerCollabSetObject proto WINAPI \
	      pcObject: PCPEER_OBJECT


PeerCollabDeleteObject proto WINAPI \
	     pObjectId: ptr GUID


endif

PEER_CHANGE_TYPE	typedef SDWORD
PEER_CHANGE_ADDED	equ 0
PEER_CHANGE_DELETED	equ 1
PEER_CHANGE_UPDATED	equ 2

PEER_COLLAB_EVENT_TYPE		typedef SDWORD
PEER_EVENT_WATCHLIST_CHANGED		equ 1
PEER_EVENT_ENDPOINT_CHANGED		equ 2
PEER_EVENT_ENDPOINT_PRESENCE_CHANGED	equ 3
PEER_EVENT_ENDPOINT_APPLICATION_CHANGED equ 4
PEER_EVENT_ENDPOINT_OBJECT_CHANGED	equ 5
PEER_EVENT_MY_ENDPOINT_CHANGED		equ 6
PEER_EVENT_MY_PRESENCE_CHANGED		equ 7
PEER_EVENT_MY_APPLICATION_CHANGED	equ 8
PEER_EVENT_MY_OBJECT_CHANGED		equ 9
PEER_EVENT_PEOPLE_NEAR_ME_CHANGED	equ 10
PEER_EVENT_REQUEST_STATUS_CHANGED	equ 11

PEER_COLLAB_EVENT_REGISTRATION STRUC
eventType		PEER_COLLAB_EVENT_TYPE ?
pInstance		LPGUID ?
PEER_COLLAB_EVENT_REGISTRATION ENDS
PPEER_COLLAB_EVENT_REGISTRATION typedef ptr PEER_COLLAB_EVENT_REGISTRATION

PEER_EVENT_WATCHLIST_CHANGED_DATA STRUC
pContact		PPEER_CONTACT ?
changeType		PEER_CHANGE_TYPE ?
PEER_EVENT_WATCHLIST_CHANGED_DATA ENDS
PPEER_EVENT_WATCHLIST_CHANGED_DATA typedef ptr PEER_EVENT_WATCHLIST_CHANGED_DATA

PEER_EVENT_PRESENCE_CHANGED_DATA STRUC
pContact		PPEER_CONTACT ?
pEndpoint		PPEER_ENDPOINT ?
changeType		PEER_CHANGE_TYPE ?
pPresenceInfo		PPEER_PRESENCE_INFO ?
PEER_EVENT_PRESENCE_CHANGED_DATA ENDS
PPEER_EVENT_PRESENCE_CHANGED_DATA typedef ptr PEER_EVENT_PRESENCE_CHANGED_DATA

PEER_EVENT_APPLICATION_CHANGED_DATA STRUC
pContact		PPEER_CONTACT ?
pEndpoint		PPEER_ENDPOINT ?
changeType		PEER_CHANGE_TYPE ?
pApplication		PPEER_APPLICATION ?
PEER_EVENT_APPLICATION_CHANGED_DATA ENDS
PPEER_EVENT_APPLICATION_CHANGED_DATA typedef ptr PEER_EVENT_APPLICATION_CHANGED_DATA

PEER_EVENT_OBJECT_CHANGED_DATA STRUC
pContact		PPEER_CONTACT ?
pEndpoint		PPEER_ENDPOINT ?
changeType		PEER_CHANGE_TYPE ?
pObject			PPEER_OBJECT ?
PEER_EVENT_OBJECT_CHANGED_DATA ENDS
PPEER_EVENT_OBJECT_CHANGED_DATA typedef ptr PEER_EVENT_OBJECT_CHANGED_DATA

PEER_EVENT_ENDPOINT_CHANGED_DATA STRUC
pContact		PPEER_CONTACT ?
pEndpoint		PPEER_ENDPOINT ?
PEER_EVENT_ENDPOINT_CHANGED_DATA ENDS
PPEER_EVENT_ENDPOINT_CHANGED_DATA typedef ptr PEER_EVENT_ENDPOINT_CHANGED_DATA

PEER_EVENT_PEOPLE_NEAR_ME_CHANGED_DATA STRUC
changeType		PEER_CHANGE_TYPE ?
pPeopleNearMe		PPEER_PEOPLE_NEAR_ME ?
PEER_EVENT_PEOPLE_NEAR_ME_CHANGED_DATA ENDS
PPEER_EVENT_PEOPLE_NEAR_ME_CHANGED_DATA typedef ptr PEER_EVENT_PEOPLE_NEAR_ME_CHANGED_DATA

PEER_EVENT_REQUEST_STATUS_CHANGED_DATA STRUC
pEndpoint		PPEER_ENDPOINT ?
hrChange		HRESULT ?
PEER_EVENT_REQUEST_STATUS_CHANGED_DATA ENDS
PPEER_EVENT_REQUEST_STATUS_CHANGED_DATA typedef ptr PEER_EVENT_REQUEST_STATUS_CHANGED_DATA

ifdef MIDL_PASS
else
PEER_COLLAB_EVENT_DATA	STRUC
eventType		PEER_COLLAB_EVENT_TYPE ?
UNION
 watchListChangedData	PEER_EVENT_WATCHLIST_CHANGED_DATA <>
 presenceChangedData	PEER_EVENT_PRESENCE_CHANGED_DATA <>
 applicationChangedData PEER_EVENT_APPLICATION_CHANGED_DATA <>
 objectChangedData	PEER_EVENT_OBJECT_CHANGED_DATA <>
 endpointChangedData	PEER_EVENT_ENDPOINT_CHANGED_DATA <>
 peopleNearMeChangedData PEER_EVENT_PEOPLE_NEAR_ME_CHANGED_DATA <>
 requestStatusChangedData PEER_EVENT_REQUEST_STATUS_CHANGED_DATA <>
ENDS
PEER_COLLAB_EVENT_DATA	ENDS
PPEER_COLLAB_EVENT_DATA typedef ptr PEER_COLLAB_EVENT_DATA
endif


ifndef MIDL_PASS

;HRESULT
PeerCollabRegisterEvent proto WINAPI \
		hEvent: HANDLE,
    cEventRegistration: DWORD,
   pEventRegistrations: ptr PEER_COLLAB_EVENT_REGISTRATION,
	   phPeerEvent: ptr HPEEREVENT


PeerCollabGetEventData proto WINAPI \
	    hPeerEvent: HPEEREVENT,
	   ppEventData: ptr PPEER_COLLAB_EVENT_DATA


PeerCollabUnregisterEvent proto WINAPI \
	    hPeerEvent: HPEEREVENT


PeerCollabEnumPeopleNearMe proto WINAPI \
	    phPeerEnum: ptr HPEERENUM


PeerCollabAddContact proto WINAPI \
	pwzContactData: PCWSTR,
	     ppContact: ptr PPEER_CONTACT


PeerCollabDeleteContact proto WINAPI \
	   pwzPeerName: PCWSTR


PeerCollabGetContact proto WINAPI \
	   pwzPeerName: PCWSTR,
	     ppContact: ptr PPEER_CONTACT


PeerCollabUpdateContact proto WINAPI \
	      pContact: PCPEER_CONTACT


PeerCollabEnumContacts proto WINAPI \
	    phPeerEnum: ptr HPEERENUM


PeerCollabExportContact proto WINAPI \
	   pwzPeerName: PCWSTR,
       ppwzContactData: ptr PWSTR


PeerCollabParseContact proto WINAPI \
	pwzContactData: PCWSTR,
	     ppContact: ptr PPEER_CONTACT


endif ;; MIDL_PASS
endif ;; NO_P2P_COLLABORATION


ifndef	 MIDL_PASS
ifndef	 NO_P2P_PNRP

PNRP_VERSION		equ MAKEWORD(2,0)

PEER_PNRP_ALL_LINK_CLOUDS equ <L"PEER_PNRP_ALL_LINKS">
PEER_PNRP_AUTO_ADDRESSES equ (-1)

HREGISTRATION		typedef PVOID
HRESOLUTION		typedef PVOID

PEER_PNRP_ENDPOINT_INFO STRUC
pwzPeerName		PWSTR ?
cAddresses		ULONG ?
ppAddresses		LPSOCKADDR ?
pwzComment		PWSTR ?
payload			PEER_DATA <>
PEER_PNRP_ENDPOINT_INFO ENDS
PPEER_PNRP_ENDPOINT_INFO typedef ptr PEER_PNRP_ENDPOINT_INFO

PEER_PNRP_CLOUD_INFO	STRUC
pwzCloudName		PWSTR ?
dwScope			PNRP_SCOPE ?
dwScopeId		dd ?
PEER_PNRP_CLOUD_INFO	ENDS
PPEER_PNRP_CLOUD_INFO	typedef ptr PEER_PNRP_CLOUD_INFO

PEER_PNRP_REGISTRATION_INFO STRUC
pwzCloudName		PWSTR ?
pwzPublishingIdentity	PWSTR ?
cAddresses		ULONG ?
ppAddresses		LPSOCKADDR ?
wPort			dw ?
pwzComment		PWSTR ?
payload			PEER_DATA <>
PEER_PNRP_REGISTRATION_INFO ENDS
PPEER_PNRP_REGISTRATION_INFO typedef ptr PEER_PNRP_REGISTRATION_INFO


;HRESULT
PeerNameToPeerHostName proto WINAPI \
	   pwzPeerName: PCWSTR,
	  ppwzHostName: ptr PWSTR


PeerHostNameToPeerName proto WINAPI \
	   pwzHostName: PCWSTR,
	  ppwzPeerName: ptr PWSTR


PeerPnrpStartup proto WINAPI \
     wVersionRequested: WORD


PeerPnrpShutdown proto WINAPI

PeerPnrpRegister proto WINAPI \
	  pcwzPeerName: PCWSTR,
     pRegistrationInfo: PPEER_PNRP_REGISTRATION_INFO,
	phRegistration: ptr HREGISTRATION


PeerPnrpUpdateRegistration proto WINAPI \
	 hRegistration: HREGISTRATION,
     pRegistrationInfo: PPEER_PNRP_REGISTRATION_INFO


PeerPnrpUnregister proto WINAPI \
	 hRegistration: HREGISTRATION


PeerPnrpResolve proto WINAPI \
	  pcwzPeerName: PCWSTR,
	 pcwzCloudName: PCWSTR,
	   pcEndpoints: ptr ULONG,
	   ppEndpoints: ptr PPEER_PNRP_ENDPOINT_INFO

PeerPnrpStartResolve proto WINAPI \
	  pcwzPeerName: PCWSTR,
	 pcwzCloudName: PCWSTR,
	 cMaxEndpoints: ULONG,
		hEvent: HANDLE,
	     phResolve: ptr HRESOLUTION


PeerPnrpGetCloudInfo proto WINAPI \
	   pcNumClouds: ptr ULONG,
	   ppCloudInfo: ptr PPEER_PNRP_CLOUD_INFO

PeerPnrpGetEndpoint proto WINAPI \
	      hResolve: HRESOLUTION,
	    ppEndpoint: ptr PPEER_PNRP_ENDPOINT_INFO


PeerPnrpEndResolve proto WINAPI \
	      hResolve: HRESOLUTION


endif ;; NO_P2P_PNRP
endif ;; MIDL_PASS


WSA_PNRP_ERROR_BASE		equ 11500
WSA_PNRP_CLOUD_NOT_FOUND	equ (WSA_PNRP_ERROR_BASE + 1)
WSA_PNRP_CLOUD_DISABLED		equ (WSA_PNRP_ERROR_BASE + 2)
WSA_PNRP_INVALID_IDENTITY	equ (WSA_PNRP_ERROR_BASE + 3)
WSA_PNRP_TOO_MUCH_LOAD		equ (WSA_PNRP_ERROR_BASE + 4)
WSA_PNRP_CLOUD_IS_SEARCH_ONLY	equ (WSA_PNRP_ERROR_BASE + 5)
WSA_PNRP_CLIENT_INVALID_COMPARTMENT_ID equ (WSA_PNRP_ERROR_BASE + 6)
WSA_PNRP_DUPLICATE_PEER_NAME	equ (WSA_PNRP_ERROR_BASE + 8)
WSA_PNRP_CLOUD_IS_DEAD		equ (WSA_PNRP_ERROR_BASE + 9)

PEER_E_CLOUD_NOT_FOUND	equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_WIN32, WSA_PNRP_CLOUD_NOT_FOUND)
PEER_E_CLOUD_DISABLED	equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_WIN32, WSA_PNRP_CLOUD_DISABLED)
PEER_E_INVALID_IDENTITY equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_WIN32, WSA_PNRP_INVALID_IDENTITY)
PEER_E_TOO_MUCH_LOAD	equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_WIN32, WSA_PNRP_TOO_MUCH_LOAD)
PEER_E_CLOUD_IS_SEARCH_ONLY equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_WIN32, WSA_PNRP_CLOUD_IS_SEARCH_ONLY)
PEER_E_CLIENT_INVALID_COMPARTMENT_ID equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_WIN32, WSA_PNRP_CLIENT_INVALID_COMPARTMENT_ID)
PEER_E_DUPLICATE_PEER_NAME equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_WIN32, WSA_PNRP_DUPLICATE_PEER_NAME)
PEER_E_CLOUD_IS_DEAD	equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_WIN32, WSA_PNRP_CLOUD_IS_DEAD)


PEER_E_NOT_FOUND	equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_WIN32, ERROR_NOT_FOUND)
PEER_E_DISK_FULL	equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_WIN32, ERROR_DISK_FULL)
PEER_E_ALREADY_EXISTS	equ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_WIN32, ERROR_ALREADY_EXISTS)

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
endif ;; _P2P_H_

ifdef DEFINE_GUID
ifndef NO_P2P_GROUP
DEFINE_GUID(PEER_GROUP_ROLE_ADMIN, 0x04387127, 0xaa56, 0x450a, 0x8c, 0xe5, 0x4f, 0x56, 0x5c, 0x67, 0x90, 0xf4)
DEFINE_GUID(PEER_GROUP_ROLE_MEMBER, 0xf12dc4c7,0x0857, 0x4ca0, 0x93, 0xfc, 0xb1, 0xbb, 0x19, 0xa3, 0xd8, 0xc2)
if NTDDI_VERSION GE NTDDI_VISTA
DEFINE_GUID(PEER_GROUP_ROLE_INVITING_MEMBER, 0x4370fd89, 0xdc18, 0x4cfb, 0x8d, 0xbf, 0x98, 0x53, 0xa8, 0xa9, 0xf9, 0x05)
endif
endif ;; NO_P2P_GROUP
ifndef NO_P2P_COLLABORATION
DEFINE_GUID(PEER_COLLAB_OBJECTID_USER_PICTURE, 0xdd15f41f, 0xfc4e, 0x4922, 0xb0, 0x35, 0x4c, 0x06, 0xa7, 0x54, 0xd0, 0x1d)
endif
endif ;; DEFINE_GUID

.pragma list(pop)
