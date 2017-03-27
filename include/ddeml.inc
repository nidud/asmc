ifndef __LIBC_INC
 include libc.inc
endif
.xlist
ifndef _INC_DDEMLH
_INC_DDEMLH equ 1

;;******* public types *******

HCONVLIST		typedef HANDLE
HCONV			typedef HANDLE
HSZ			typedef HANDLE
HDDEDATA		typedef HANDLE
EXPENTRY		equ <CALLBACK>

;; the following structure is for use with XTYP_WILDCONNECT processing.

HSZPAIR			STRUC
hszSvc			HSZ ?
hszTopic		HSZ ?
HSZPAIR			ENDS
PHSZPAIR		typedef ptr HSZPAIR

;; The following structure is used by DdeConnect() and DdeConnectList() and
;; by XTYP_CONNECT and XTYP_WILDCONNECT callbacks.

CONVCONTEXT		STRUC
cb			UINT ?	;; set to sizeof(CONVCONTEXT)
wFlags			UINT ?	;; none currently defined.
wCountryID		UINT ?	;; country code for topic/item strings used.
iCodePage		SINT ?	;; codepage used for topic/item strings.
dwLangID		dd ?	;; language ID for topic/item strings.
dwSecurity		dd ?	;; Private security code.
qos			SECURITY_QUALITY_OF_SERVICE <>	;; client side's quality of service
CONVCONTEXT		ENDS
PCONVCONTEXT		typedef ptr CONVCONTEXT


;; The following structure is used by DdeQueryConvInfo():

CONVINFO		STRUC
cb			dd ?	;; sizeof(CONVINFO)
hUser			dd ?	;; user specified field
hConvPartner		HCONV ? ;; hConv on other end or 0 if non-ddemgr partner
hszSvcPartner		HSZ ?	;; app name of partner if obtainable
hszServiceReq		HSZ ?	;; AppName requested for connection
hszTopic		HSZ ?	;; Topic name for conversation
hszItem			HSZ ?	;; transaction item name or NULL if quiescent
wFmt			UINT ?	;; transaction format or NULL if quiescent
wType			UINT ?	;; XTYP_ for current transaction
wStatus			UINT ?	;; ST_ constant for current conversation
wConvst			UINT ?	;; XST_ constant for current transaction
wLastError		UINT ?	;; last transaction error.
hConvList		HCONVLIST ?	;; parent hConvList if this conversation is in a list
ConvCtxt		CONVCONTEXT <>	;; conversation context
hwnd			HWND ?	;; window handle for this conversation
hwndPartner		HWND ?	;; partner window handle for this conversation
CONVINFO		ENDS
PCONVINFO		typedef ptr CONVINFO

;;**** conversation states (usState) ****

XST_NULL		equ 0  ;; quiescent states
XST_INCOMPLETE		equ 1
XST_CONNECTED		equ 2
XST_INIT1		equ 3  ;; mid-initiation states
XST_INIT2		equ 4
XST_REQSENT		equ 5  ;; active conversation states
XST_DATARCVD		equ 6
XST_POKESENT		equ 7
XST_POKEACKRCVD		equ 8
XST_EXECSENT		equ 9
XST_EXECACKRCVD		equ 10
XST_ADVSENT		equ 11
XST_UNADVSENT		equ 12
XST_ADVACKRCVD		equ 13
XST_UNADVACKRCVD	equ 14
XST_ADVDATASENT		equ 15
XST_ADVDATAACKRCVD	equ 16

;; used in LOWORD(dwData1) of XTYP_ADVREQ callbacks...
CADV_LATEACK		equ 0xFFFF

;;**** conversation status bits (fsStatus) ****

ST_CONNECTED		equ 0x0001
ST_ADVISE		equ 0x0002
ST_ISLOCAL		equ 0x0004
ST_BLOCKED		equ 0x0008
ST_CLIENT		equ 0x0010
ST_TERMINATED		equ 0x0020
ST_INLIST		equ 0x0040
ST_BLOCKNEXT		equ 0x0080
ST_ISSELF		equ 0x0100

;; DDE constants for wStatus field

DDE_FACK		equ 0x8000
DDE_FBUSY		equ 0x4000
DDE_FDEFERUPD		equ 0x4000
DDE_FACKREQ		equ 0x8000
DDE_FRELEASE		equ 0x2000
DDE_FREQUESTED		equ 0x1000
DDE_FAPPSTATUS		equ 0x00ff
DDE_FNOTPROCESSED	equ 0x0000

DDE_FACKRESERVED	equ ( NOT (DDE_FACK OR DDE_FBUSY OR DDE_FAPPSTATUS))
DDE_FADVRESERVED	equ ( NOT (DDE_FACKREQ OR DDE_FDEFERUPD))
DDE_FDATRESERVED	equ ( NOT (DDE_FACKREQ OR DDE_FREEASE OR DDE_FREQUESTED))
DDE_FPOKRESERVED	equ ( NOT (DDE_FREEASE))

;;**** message filter hook types ****

MSGF_DDEMGR		equ 0x8001

;;**** codepage constants ***

CP_WINANSI		equ 1004    ;; default codepage for windows AND old DDE convs.
CP_WINUNICODE		equ 1200
ifdef _UNICODE
CP_WINNEUTRAL		equ CP_WINUNICODE
else  ;; NOT UNICODE
CP_WINNEUTRAL		equ CP_WINANSI
endif ;; NOT UNICODE

;;**** transaction types ****

XTYPF_NOBLOCK		equ 0x0002  ;; CBR_BOCK will not work
XTYPF_NODATA		equ 0x0004  ;; DDE_FDEFERUPD
XTYPF_ACKREQ		equ 0x0008  ;; DDE_FACKREQ

XCLASS_MASK		equ 0xFC00
XCLASS_BOOL		equ 0x1000
XCLASS_DATA		equ 0x2000
XCLASS_FLAGS		equ 0x4000
XCLASS_NOTIFICATION	equ 0x8000

XTYP_ERROR		equ (0x0000 OR XCLASS_NOTIFICATION OR XTYPF_NOBOCK )
XTYP_ADVDATA		equ (0x0010 OR XCLASS_FAGS	   )
XTYP_ADVREQ		equ (0x0020 OR XCLASS_DATA OR XTYPF_NOBOCK )
XTYP_ADVSTART		equ (0x0030 OR XCLASS_BOOL	    )
XTYP_ADVSTOP		equ (0x0040 OR XCASS_NOTIFICATION)
XTYP_EXECUTE		equ (0x0050 OR XCLASS_FAGS	   )
XTYP_CONNECT		equ (0x0060 OR XCLASS_BOOL OR XTYPF_NOBOCK)
XTYP_CONNECT_CONFIRM	equ (0x0070 OR XCLASS_NOTIFICATION OR XTYPF_NOBOCK)
XTYP_XACT_COMPLETE	equ (0x0080 OR XCASS_NOTIFICATION  )
XTYP_POKE		equ (0x0090 OR XCLASS_FAGS	   )
XTYP_REGISTER		equ (0x00A0 OR XCLASS_NOTIFICATION OR XTYPF_NOBOCK)
XTYP_REQUEST		equ (0x00B0 OR XCASS_DATA	   )
XTYP_DISCONNECT		equ (0x00C0 OR XCLASS_NOTIFICATION OR XTYPF_NOBOCK)
XTYP_UNREGISTER		equ (0x00D0 OR XCLASS_NOTIFICATION OR XTYPF_NOBOCK)
XTYP_WILDCONNECT	equ (0x00E0 OR XCLASS_DATA OR XTYPF_NOBOCK)

XTYP_MASK		equ 0x00F0
XTYP_SHIFT		equ 4  ;; shift to turn XTYP_ into an index

;;**** Timeout constants ****

TIMEOUT_ASYNC		equ 0xFFFFFFFF

;;**** Transaction ID constants ****

QID_SYNC		equ 0xFFFFFFFF

;;***** public strings used in DDE *****

if 0;_UNICODE
SZDDESYS_TOPIC		equ <L"System">
SZDDESYS_ITEM_TOPICS	equ <L"Topics">
SZDDESYS_ITEM_SYSITEMS	equ <L"SysItems">
SZDDESYS_ITEM_RTNMSG	equ <L"ReturnMessage">
SZDDESYS_ITEM_STATUS	equ <L"Status">
SZDDESYS_ITEM_FORMATS	equ <L"Formats">
SZDDESYS_ITEM_HELP	equ <L"Help">
SZDDE_ITEM_ITEMLIST	equ <L"TopicItemList">
else
SZDDESYS_TOPIC		equ <"System">
SZDDESYS_ITEM_TOPICS	equ <"Topics">
SZDDESYS_ITEM_SYSITEMS	equ <"SysItems">
SZDDESYS_ITEM_RTNMSG	equ <"ReturnMessage">
SZDDESYS_ITEM_STATUS	equ <"Status">
SZDDESYS_ITEM_FORMATS	equ <"Formats">
SZDDESYS_ITEM_HELP	equ <"Help">
SZDDE_ITEM_ITEMLIST	equ <"TopicItemList">
endif


;;***** API entry points *****

;HDDEDATA
;CALLBACK
FNCALLBACK_T typedef proto _CType \
		 wType: UINT,
		  wFmt: UINT,
		 hConv: HCONV,
		  hsz1: HSZ,
		  hsz2: HSZ,
		 hData: HDDEDATA,
	       dwData1: DWORD,
	       dwData2: DWORD
FNCALLBACK	typedef ptr FNCALLBACK_T

PFNCALLBACK_T typedef proto _CType \
		 wType: UINT,
		  wFmt: UINT,
		 hConv: HCONV,
		  hsz1: HSZ,
		  hsz2: HSZ,
		 hData: HDDEDATA,
	       dwData1: DWORD,
	       dwData2: DWORD
PFNCALLBACK	typedef ptr PFNCALLBACK_T

CBR_BLOCK		equ 0xffffffff

;; DLL registration functions

;UINT
DdeInitializeA proto _CType \
	       pidInst: LPDWORD,
	   pfnCallback: PFNCALLBACK,
		 afCmd: DWORD,
		 ulRes: DWORD
;UINT
DdeInitializeW proto _CType \
	       pidInst: LPDWORD,
	   pfnCallback: PFNCALLBACK,
		 afCmd: DWORD,
		 ulRes: DWORD
ifdef _UNICODE
DdeInitialize		equ <DdeInitializeW>
else
DdeInitialize		equ <DdeInitializeA>
endif ;; NOT UNICODE

;;
;; Callback filter flags for use with standard apps.
;;

CBF_FAIL_SELFCONNECTIONS equ 0x00001000
CBF_FAIL_CONNECTIONS	equ 0x00002000
CBF_FAIL_ADVISES	equ 0x00004000
CBF_FAIL_EXECUTES	equ 0x00008000
CBF_FAIL_POKES		equ 0x00010000
CBF_FAIL_REQUESTS	equ 0x00020000
CBF_FAIL_ALLSVRXACTIONS equ 0x0003f000

CBF_SKIP_CONNECT_CONFIRMS equ 0x00040000
CBF_SKIP_REGISTRATIONS	  equ 0x00080000
CBF_SKIP_UNREGISTRATIONS  equ 0x00100000
CBF_SKIP_DISCONNECTS	  equ 0x00200000
CBF_SKIP_ALLNOTIFICATIONS equ 0x003c0000

;;
;; Application command flags
;;
APPCMD_CLIENTONLY	equ 0x00000010
APPCMD_FILTERINITS	equ 0x00000020
APPCMD_MASK		equ 0x00000FF0

;;
;; Application classification flags
;;
APPCLASS_STANDARD	equ 0x00000000
APPCLASS_MASK		equ 0x0000000F

;BOOL
DdeUninitialize proto _CType \
		idInst: DWORD

;;
;; conversation enumeration functions
;;

;HCONVLIST
DdeConnectList proto _CType \
		idInst: DWORD,
	    hszService: HSZ,
	      hszTopic: HSZ,
	     hConvList: HCONVLIST,
		   pCC: PCONVCONTEXT

;HCONV
DdeQueryNextServer proto _CType \
	     hConvList: HCONVLIST,
	     hConvPrev: HCONV
;BOOL
DdeDisconnectList proto _CType \
	     hConvList: HCONVLIST

;;
;; conversation control functions
;;

;HCONV
DdeConnect proto _CType \
	       idInst: DWORD,
	   hszService: HSZ,
	     hszTopic: HSZ,
		  pCC: PCONVCONTEXT
;BOOL
DdeDisconnect proto _CType \
		 hConv: HCONV
;HCONV
DdeReconnect proto _CType \
		 hConv: HCONV
;UINT
DdeQueryConvInfo proto _CType \
		 hConv: HCONV,
	 idTransaction: DWORD,
	     pConvInfo: PCONVINFO
;BOOL
DdeSetUserHandle proto _CType \
		 hConv: HCONV,
		    id: DWORD,
		 hUser: DWORD
;BOOL
DdeAbandonTransaction proto _CType \
		idInst: DWORD,
		 hConv: HCONV,
	 idTransaction: DWORD


;;
;; app server interface functions
;;

;BOOL
DdePostAdvise proto _CType \
		idInst: DWORD,
	      hszTopic: HSZ,
	       hszItem: HSZ
;BOOL
DdeEnableCallback proto _CType \
		idInst: DWORD,
		 hConv: HCONV,
		  wCmd: UINT
;BOOL
DdeImpersonateClient proto _CType \
		 hConv: HCONV

EC_ENABLEALL		equ 0
EC_ENABLEONE		equ ST_BOCKNEXT
EC_DISABLE		equ ST_BOCKED
EC_QUERYWAITING		equ 2

;HDDEDATA
DdeNameService proto _CType \
		idInst: DWORD,
		  hsz1: HSZ,
		  hsz2: HSZ,
		 afCmd: UINT

DNS_REGISTER		equ 0x0001
DNS_UNREGISTER		equ 0x0002
DNS_FILTERON		equ 0x0004
DNS_FILTEROFF		equ 0x0008

;;
;; app client interface functions
;;

;HDDEDATA
DdeClientTransaction proto _CType \
		 pData: LPBYTE,
		cbData: DWORD,
		 hConv: HCONV,
	       hszItem: HSZ,
		  wFmt: UINT,
		 wType: UINT,
	     dwTimeout: DWORD,
	     pdwResult: LPDWORD

;;
;;data transfer functions
;;

;HDDEDATA
DdeCreateDataHandle proto _CType \
		idInst: DWORD,
		  pSrc: LPBYTE,
		    cb: DWORD,
		 cbOff: DWORD,
	       hszItem: HSZ,
		  wFmt: UINT,
		 afCmd: UINT

;HDDEDATA
DdeAddData proto _CType \
		 hData: HDDEDATA,
		  pSrc: LPBYTE,
		    cb: DWORD,
		 cbOff: DWORD
;DWORD
DdeGetData proto _CType \
		 hData: HDDEDATA,
		  pDst: LPBYTE,
		 cbMax: DWORD,
		 cbOff: DWORD
;LPBYTE
DdeAccessData proto _CType \
		 hData: HDDEDATA,
	   pcbDataSize: LPDWORD
;BOOL
DdeUnaccessData proto _CType \
		 hData: HDDEDATA
;BOOL
DdeFreeDataHandle proto _CType \
		 hData: HDDEDATA

HDATA_APPOWNED		equ 0x0001


;UINT
DdeGetLastError proto _CType \
		idInst: DWORD

DMLERR_NO_ERROR		equ 0	    ;; must be 0

DMLERR_FIRST		equ 0x4000

DMLERR_ADVACKTIMEOUT	equ 0x4000
DMLERR_BUSY		equ 0x4001
DMLERR_DATAACKTIMEOUT	equ 0x4002
DMLERR_DLL_NOT_INITIALIZED equ 0x4003
DMLERR_DLL_USAGE	equ 0x4004
DMLERR_EXECACKTIMEOUT	equ 0x4005
DMLERR_INVALIDPARAMETER equ 0x4006
DMLERR_LOW_MEMORY	equ 0x4007
DMLERR_MEMORY_ERROR	equ 0x4008
DMLERR_NOTPROCESSED	equ 0x4009
DMLERR_NO_CONV_ESTABLISHED equ 0x400a
DMLERR_POKEACKTIMEOUT	equ 0x400b
DMLERR_POSTMSG_FAILED	equ 0x400c
DMLERR_REENTRANCY	equ 0x400d
DMLERR_SERVER_DIED	equ 0x400e
DMLERR_SYS_ERROR	equ 0x400f
DMLERR_UNADVACKTIMEOUT	equ 0x4010
DMLERR_UNFOUND_QUEUE_ID equ 0x4011

DMLERR_LAST		equ 0x4011

;HSZ
DdeCreateStringHandleA proto _CType \
		idInst: DWORD,
		   psz: LPCSTR,
	     iCodePage: SINT
DdeCreateStringHandleW proto _CType \
		idInst: DWORD,
		   psz: LPCWSTR,
	     iCodePage: SINT
ifdef _UNICODE
DdeCreateStringHandle	equ <DdeCreateStringHandleW>
else
DdeCreateStringHandle	equ <DdeCreateStringHandleA>
endif ;; NOT UNICODE
;DWORD
DdeQueryStringA proto _CType \
		idInst: DWORD,
		   hsz: HSZ,
		   psz: LPSTR,
		cchMax: DWORD,
	     iCodePage: SINT
;DWORD
DdeQueryStringW proto _CType \
		idInst: DWORD,
		   hsz: HSZ,
		   psz: LPWSTR,
		cchMax: DWORD,
	     iCodePage: SINT
ifdef _UNICODE
DdeQueryString		equ <DdeQueryStringW>
else
DdeQueryString		equ <DdeQueryStringA>
endif ;; NOT UNICODE
;BOOL
DdeFreeStringHandle proto _CType \
		idInst: DWORD,
		   hsz: HSZ
;BOOL
DdeKeepStringHandle proto _CType \
		idInst: DWORD,
		   hsz: HSZ
;int
DdeCmpStringHandles proto _CType \
		  hsz1: HSZ,
		  hsz2: HSZ

ifndef NODDEMLSPY
;;
;; DDEML public debugging header file info
;;

DDEML_MSG_HOOK_DATA	STRUC
uiLo			UINT ?	;; unpacked lo and hi parts of lParam
uiHi			UINT ?
cbData			dd ?	;; amount of data in message, if any. May be > than 32 bytes.
Data			dd 8 dup(?) ;; data peeking by DDESPY is limited to 32 bytes.
DDEML_MSG_HOOK_DATA	ENDS
PDDEML_MSG_HOOK_DATA	typedef ptr DDEML_MSG_HOOK_DATA


MONMSGSTRUCT		STRUC
cb			UINT ?
hwndTo			HWND ?
dwTime			dd ?
hTask			HANDLE ?
wMsg			UINT ?
wParam			WPARAM ?
lParam			LPARAM ?
dmhd			DDEML_MSG_HOOK_DATA <> ;; new for NT
MONMSGSTRUCT		ENDS
PMONMSGSTRUCT		typedef ptr MONMSGSTRUCT

MONCBSTRUCT		STRUC
cb			UINT ?
dwTime			dd ?
hTask			HANDLE ?
dwRet			dd ?
wType			UINT ?
wFmt			UINT ?
hConv			HCONV ?
hsz1			HSZ ?
hsz2			HSZ ?
hData			HDDEDATA ?
dwData1			dd ?
dwData2			dd ?
cc			CONVCONTEXT <>	;; new for NT for XTYP_CONNECT callbacks
cbData			dd ?	;; new for NT for data peeking
Data			dd 8 dup(?)	;; new for NT for data peeking
MONCBSTRUCT		ENDS
PMONCBSTRUCT		typedef ptr MONCBSTRUCT

MONHSZSTRUCTA		STRUC
cb			UINT ?
fsAction		BOOL ?	;; MH_ value
dwTime			dd ?
hsz			HSZ ?
hTask			HANDLE ?
_str			CHAR ?
MONHSZSTRUCTA		ENDS
PMONHSZSTRUCTA		typedef ptr MONHSZSTRUCTA
MONHSZSTRUCTW		STRUC
cb			UINT ?
fsAction		BOOL ?	;; MH_ value
dwTime			dd ?
hsz			HSZ ?
hTask			HANDLE ?
_str			WCHAR ?
MONHSZSTRUCTW		ENDS
PMONHSZSTRUCTW		typedef ptr MONHSZSTRUCTW
ifdef _UNICODE
MONHSZSTRUCT		typedef MONHSZSTRUCTW
PMONHSZSTRUCT		typedef PMONHSZSTRUCTW
else
MONHSZSTRUCT		typedef MONHSZSTRUCTA
PMONHSZSTRUCT		typedef PMONHSZSTRUCTA
endif ;; UNICODE

MH_CREATE		equ 1
MH_KEEP			equ 2
MH_DELETE		equ 3
MH_CLEANUP		equ 4

MONERRSTRUCT		STRUC
cb			UINT ?
wLastError		UINT ?
dwTime			dd ?
hTask			HANDLE ?
MONERRSTRUCT		ENDS
PMONERRSTRUCT		typedef ptr MONERRSTRUCT

MONLINKSTRUCT		STRUC
cb			UINT ?
dwTime			dd ?
hTask			HANDLE ?
fEstablished		BOOL ?
fNoData			BOOL ?
hszSvc			HSZ ?
hszTopic		HSZ ?
hszItem			HSZ ?
wFmt			UINT ?
fServer			BOOL ?
hConvServer		HCONV ?
hConvClient		HCONV ?
MONLINKSTRUCT		ENDS
PMONLINKSTRUCT		typedef ptr MONLINKSTRUCT

MONCONVSTRUCT		STRUC
cb			UINT ?
fConnect		BOOL ?
dwTime			dd ?
hTask			HANDLE ?
hszSvc			HSZ ?
hszTopic		HSZ ?
hConvClient		HCONV ? ;; Globally unique value != apps local hConv
hConvServer		HCONV ? ;; Globally unique value != apps local hConv
MONCONVSTRUCT		ENDS
PMONCONVSTRUCT		typedef ptr MONCONVSTRUCT

MAX_MONITORS		equ 4
APPCLASS_MONITOR	equ 0x00000001
XTYP_MONITOR		equ (0x00F0 OR XCLASS_NOTIFICATION OR XTYPF_NOBOCK)

;;
;; Callback filter flags for use with MONITOR apps - 0 implies no monitor
;; callbacks.
;;
MF_HSZ_INFO		equ 0x01000000
MF_SENDMSGS		equ 0x02000000
MF_POSTMSGS		equ 0x04000000
MF_CALLBACKS		equ 0x08000000
MF_ERRORS		equ 0x10000000
MF_LINKS		equ 0x20000000
MF_CONV			equ 0x40000000

MF_MASK			equ 0xFF000000

endif ;; NODDEMLSPY
endif ;; _INC_DDEMLH

.list