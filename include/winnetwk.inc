ifndef __LIBC_INC
 include libc.inc
endif
.xlist
;
; Standard WINNET Header File for WIN32
;
ifndef _WINNETWK_
_WINNETWK_ equ 1
ifdef __PE__
option dllimport:<mpr>
endif

;;
;; Network types
;;

WNNC_NET_MSNET		equ 0x00010000
WNNC_NET_LANMAN		equ 0x00020000
WNNC_NET_NETWARE	equ 0x00030000
WNNC_NET_VINES		equ 0x00040000
WNNC_NET_10NET		equ 0x00050000
WNNC_NET_LOCUS		equ 0x00060000
WNNC_NET_SUN_PC_NFS	equ 0x00070000
WNNC_NET_LANSTEP	equ 0x00080000
WNNC_NET_9TILES		equ 0x00090000
WNNC_NET_LANTASTIC	equ 0x000A0000
WNNC_NET_AS400		equ 0x000B0000
WNNC_NET_FTP_NFS	equ 0x000C0000
WNNC_NET_PATHWORKS	equ 0x000D0000
WNNC_NET_LIFENET	equ 0x000E0000
WNNC_NET_POWERLAN	equ 0x000F0000
WNNC_NET_BWNFS		equ 0x00100000
WNNC_NET_COGENT		equ 0x00110000
WNNC_NET_FARALLON	equ 0x00120000
WNNC_NET_APPLETALK	equ 0x00130000
WNNC_NET_INTERGRAPH	equ 0x00140000
WNNC_NET_SYMFONET	equ 0x00150000
WNNC_NET_CLEARCASE	equ 0x00160000
WNNC_NET_FRONTIER	equ 0x00170000
WNNC_NET_BMC		equ 0x00180000
WNNC_NET_DCE		equ 0x00190000
WNNC_NET_DECORB		equ 0x00200000
WNNC_NET_PROTSTOR	equ 0x00210000
WNNC_NET_FJ_REDIR	equ 0x00220000
WNNC_NET_DISTINCT	equ 0x00230000
WNNC_NET_TWINS		equ 0x00240000
WNNC_NET_RDR2SAMPLE	equ 0x00250000

;;
;;  Network Resources.
;;

RESOURCE_CONNECTED	equ 0x00000001
RESOURCE_GLOBALNET	equ 0x00000002
RESOURCE_REMEMBERED	equ 0x00000003
if(WINVER GE 0x0400)
RESOURCE_RECENT		equ 0x00000004
RESOURCE_CONTEXT	equ 0x00000005
endif ;; WINVER GE 0x0400

RESOURCETYPE_ANY	equ 0x00000000
RESOURCETYPE_DISK	equ 0x00000001
RESOURCETYPE_PRINT	equ 0x00000002
if(WINVER GE 0x0400)
RESOURCETYPE_RESERVED	equ 0x00000008
endif ;; WINVER GE 0x0400
RESOURCETYPE_UNKNOWN	equ 0xFFFFFFFF

RESOURCEUSAGE_CONNECTABLE equ 0x00000001
RESOURCEUSAGE_CONTAINER equ 0x00000002
if(WINVER GE 0x0400)
RESOURCEUSAGE_NOLOCALDEVICE equ 0x00000004
RESOURCEUSAGE_SIBLING	equ 0x00000008
RESOURCEUSAGE_ATTACHED	equ 0x00000010
RESOURCEUSAGE_ALL	equ RESOURCEUSAGE_CONNECTABE OR RESOURCEUSAGE_CONTAINER OR RESOURCEUSAGE_ATTACHED
endif ;; WINVER GE 0x0400
RESOURCEUSAGE_RESERVED	equ 0x80000000

RESOURCEDISPLAYTYPE_GENERIC	equ 0x00000000
RESOURCEDISPLAYTYPE_DOMAIN	equ 0x00000001
RESOURCEDISPLAYTYPE_SERVER	equ 0x00000002
RESOURCEDISPLAYTYPE_SHARE	equ 0x00000003
RESOURCEDISPLAYTYPE_FILE	equ 0x00000004
RESOURCEDISPLAYTYPE_GROUP	equ 0x00000005
if(WINVER GE 0x0400)
RESOURCEDISPLAYTYPE_NETWORK	equ 0x00000006
RESOURCEDISPLAYTYPE_ROOT	equ 0x00000007
RESOURCEDISPLAYTYPE_SHAREADMIN	equ 0x00000008
RESOURCEDISPLAYTYPE_DIRECTORY	equ 0x00000009
endif ;; WINVER GE 0x0400
RESOURCEDISPLAYTYPE_TREE	equ 0x0000000A
if(WINVER GE 0x0400)
RESOURCEDISPLAYTYPE_NDSCONTAINER equ 0x0000000B
endif ;; WINVER GE 0x0400

NETRESOURCEA		STRUC
dwScope			dd ?
dwType			dd ?
dwDisplayType		dd ?
dwUsage			dd ?
lpLocalName		LPSTR ?
lpRemoteName		LPSTR ?
lpComment		LPSTR ?
lpProvider		LPSTR ?
NETRESOURCEA		ENDS
LPNETRESOURCEA		typedef ptr NETRESOURCEA
NETRESOURCEW		STRUC
dwScope			dd ?
dwType			dd ?
dwDisplayType		dd ?
dwUsage			dd ?
lpLocalName		LPWSTR ?
lpRemoteName		LPWSTR ?
lpComment		LPWSTR ?
lpProvider		LPWSTR ?
NETRESOURCEW		ENDS
LPNETRESOURCEW		typedef ptr NETRESOURCEW
ifdef _UNICODE
NETRESOURCE		typedef NETRESOURCEW
LPNETRESOURCE		typedef LPNETRESOURCEW
else
NETRESOURCE		typedef NETRESOURCEA
LPNETRESOURCE		typedef LPNETRESOURCEA
endif ;; UNICODE

;;
;;  Network Connections.
;;

NETPROPERTY_PERSISTENT	equ 1

CONNECT_UPDATE_PROFILE	equ 0x00000001
CONNECT_UPDATE_RECENT	equ 0x00000002
CONNECT_TEMPORARY	equ 0x00000004
CONNECT_INTERACTIVE	equ 0x00000008
CONNECT_PROMPT		equ 0x00000010
CONNECT_NEED_DRIVE	equ 0x00000020
if(WINVER GE 0x0400)
CONNECT_REFCOUNT	equ 0x00000040
CONNECT_REDIRECT	equ 0x00000080
CONNECT_LOCALDRIVE	equ 0x00000100
CONNECT_CURRENT_MEDIA	equ 0x00000200
CONNECT_DEFERRED	equ 0x00000400
CONNECT_RESERVED	equ 0xFF000000
endif ;; WINVER GE 0x0400

;DWORD
WNetAddConnectionA proto _CType \
	  lpRemoteName: LPCSTR,
	    lpPassword: LPCSTR,
	   lpLocalName: LPCSTR
;DWORD
WNetAddConnectionW proto _CType \
	  lpRemoteName: LPCWSTR,
	    lpPassword: LPCWSTR,
	   lpLocalName: LPCWSTR
ifdef _UNICODE
WNetAddConnection	equ <WNetAddConnectionW>
else
WNetAddConnection	equ <WNetAddConnectionA>
endif ;; NOT UNICODE

;DWORD
WNetAddConnection2A proto _CType \
	 lpNetResource: LPNETRESOURCEA,
	    lpPassword: LPCSTR,
	    lpUserName: LPCSTR,
	       dwFlags: DWORD
;DWORD
WNetAddConnection2W proto _CType \
	 lpNetResource: LPNETRESOURCEW,
	    lpPassword: LPCWSTR,
	    lpUserName: LPCWSTR,
	       dwFlags: DWORD
ifdef _UNICODE
WNetAddConnection2	equ <WNetAddConnection2W>
else
WNetAddConnection2	equ <WNetAddConnection2A>
endif ;; NOT UNICODE

;DWORD
WNetAddConnection3A proto _CType \
	     hwndOwner: HWND,
	 lpNetResource: LPNETRESOURCEA,
	    lpPassword: LPCSTR,
	    lpUserName: LPCSTR,
	       dwFlags: DWORD
;DWORD
WNetAddConnection3W proto _CType \
	     hwndOwner: HWND,
	 lpNetResource: LPNETRESOURCEW,
	    lpPassword: LPCWSTR,
	    lpUserName: LPCWSTR,
	       dwFlags: DWORD
ifdef _UNICODE
WNetAddConnection3	equ <WNetAddConnection3W>
else
WNetAddConnection3	equ <WNetAddConnection3A>
endif ;; NOT UNICODE

;DWORD
WNetCancelConnectionA proto _CType \
		lpName: LPCSTR,
		fForce: BOOL
;DWORD
WNetCancelConnectionW proto _CType \
		lpName: LPCWSTR,
		fForce: BOOL
ifdef _UNICODE
WNetCancelConnection	equ <WNetCancelConnectionW>
else
WNetCancelConnection	equ <WNetCancelConnectionA>
endif ;; NOT UNICODE

;DWORD
WNetCancelConnection2A proto _CType \
		lpName: LPCSTR,
	       dwFlags: DWORD,
		fForce: BOOL
;DWORD
WNetCancelConnection2W proto _CType \
		lpName: LPCWSTR,
	       dwFlags: DWORD,
		fForce: BOOL
ifdef _UNICODE
WNetCancelConnection2	equ <WNetCancelConnection2W>
else
WNetCancelConnection2	equ <WNetCancelConnection2A>
endif ;; NOT UNICODE

;DWORD
WNetGetConnectionA proto _CType \
	   lpLocalName: LPCSTR,
	  lpRemoteName: LPSTR,
	     lpnLength: LPDWORD
;DWORD
WNetGetConnectionW proto _CType \
	   lpLocalName: LPCWSTR,
	  lpRemoteName: LPWSTR,
	     lpnLength: LPDWORD
ifdef _UNICODE
WNetGetConnection	equ <WNetGetConnectionW>
else
WNetGetConnection	equ <WNetGetConnectionA>
endif ;; NOT UNICODE


if(WINVER GE 0x0400)
;DWORD
WNetUseConnectionA proto _CType \
	     hwndOwner: HWND,
	 lpNetResource: LPNETRESOURCEA,
	      lpUserID: LPCSTR,
	    lpPassword: LPCSTR,
	       dwFlags: DWORD,
	  lpAccessName: LPSTR,
	  lpBufferSize: LPDWORD,
	      lpResult: LPDWORD
;DWORD
WNetUseConnectionW proto _CType \
	     hwndOwner: HWND,
	 lpNetResource: LPNETRESOURCEW,
	      lpUserID: LPCWSTR,
	    lpPassword: LPCWSTR,
	       dwFlags: DWORD,
	  lpAccessName: LPWSTR,
	  lpBufferSize: LPDWORD,
	      lpResult: LPDWORD
ifdef _UNICODE
WNetUseConnection	equ <WNetUseConnectionW>
else
WNetUseConnection	equ <WNetUseConnectionA>
endif ;; NOT UNICODE
endif ;; WINVER GE 0x0400


;;
;;  Network Connection Dialogs.
;;

;DWORD
WNetConnectionDialog proto _CType \
		  hwnd: HWND,
		dwType: DWORD

;DWORD
WNetDisconnectDialog proto _CType \
		  hwnd: HWND,
		dwType: DWORD

if(WINVER GE 0x0400)
CONNECTDLGSTRUCTA	STRUC
cbStructure		dd ?	;; size of this structure in bytes
hwndOwner		HWND ?	;; owner window for the dialog
lpConnRes		LPNETRESOURCEA ?	;; Requested Resource info
dwFlags			dd ?	;; flags (see below)
dwDevNum		dd ?	;; number of devices connected to
CONNECTDLGSTRUCTA	ENDS
LPCONNECTDLGSTRUCTA	typedef ptr CONNECTDLGSTRUCTA
CONNECTDLGSTRUCTW	STRUC
cbStructure		dd ?	;; size of this structure in bytes
hwndOwner		HWND ?	;; owner window for the dialog
lpConnRes		LPNETRESOURCEW ?	;; Requested Resource info
dwFlags			dd ?	;; flags (see below)
dwDevNum		dd ?	;; number of devices connected to
CONNECTDLGSTRUCTW	ENDS
LPCONNECTDLGSTRUCTW	typedef ptr CONNECTDLGSTRUCTW
ifdef _UNICODE
CONNECTDLGSTRUCT	typedef CONNECTDLGSTRUCTW
LPCONNECTDLGSTRUCT	typedef LPCONNECTDLGSTRUCTW
else
CONNECTDLGSTRUCT	typedef CONNECTDLGSTRUCTA
LPCONNECTDLGSTRUCT	typedef LPCONNECTDLGSTRUCTA
endif ;; UNICODE

CONNDLG_RO_PATH		equ 0x00000001 ;; Resource path should be read-only
CONNDLG_CONN_POINT	equ 0x00000002 ;; Netware -style movable connection point enabled
CONNDLG_USE_MRU		equ 0x00000004 ;; Use MRU combobox
CONNDLG_HIDE_BOX	equ 0x00000008 ;; Hide persistent connect checkbox

;;
;; NOTE:  Set at most ONE of the below flags.  If neither flag is set,
;;	  then the persistence is set to whatever the user chose during
;;	  a previous connection
;;
CONNDLG_PERSIST		equ 0x00000010 ;; Force persistent connection
CONNDLG_NOT_PERSIST	equ 0x00000020 ;; Force connection NOT persistent

;DWORD
WNetConnectionDialog1A proto _CType \
       lpConnDlgStruct: LPCONNECTDLGSTRUCTA
;DWORD
WNetConnectionDialog1W proto _CType \
       lpConnDlgStruct: LPCONNECTDLGSTRUCTW
ifdef _UNICODE
WNetConnectionDialog1	equ <WNetConnectionDialog1W>
else
WNetConnectionDialog1	equ <WNetConnectionDialog1A>
endif ;; NOT UNICODE

DISCDLGSTRUCTA		STRUC
cbStructure		dd ?	;; size of this structure in bytes
hwndOwner		HWND ?	;; owner window for the dialog
lpLocalName		LPSTR ? ;; local device name
lpRemoteName		LPSTR ? ;; network resource name
dwFlags			dd ?	;; flags
DISCDLGSTRUCTA		ENDS
LPDISCDLGSTRUCTA	typedef ptr DISCDLGSTRUCTA
DISCDLGSTRUCTW		STRUC
cbStructure		dd ?	;; size of this structure in bytes
hwndOwner		HWND ?	;; owner window for the dialog
lpLocalName		LPWSTR ?	;; local device name
lpRemoteName		LPWSTR ?	;; network resource name
dwFlags			dd ?	;; flags
DISCDLGSTRUCTW		ENDS
LPDISCDLGSTRUCTW	typedef ptr DISCDLGSTRUCTW
ifdef _UNICODE
DISCDLGSTRUCT		typedef DISCDLGSTRUCTW
LPDISCDLGSTRUCT		typedef LPDISCDLGSTRUCTW
else
DISCDLGSTRUCT		typedef DISCDLGSTRUCTA
LPDISCDLGSTRUCT		typedef LPDISCDLGSTRUCTA
endif ;; UNICODE

DISC_UPDATE_PROFILE	equ 0x00000001
DISC_NO_FORCE		equ 0x00000040

;DWORD
WNetDisconnectDialog1A proto _CType \
       lpConnDlgStruct: LPDISCDLGSTRUCTA
WNetDisconnectDialog1W proto _CType \
       lpConnDlgStruct: LPDISCDLGSTRUCTW
ifdef _UNICODE
WNetDisconnectDialog1	equ <WNetDisconnectDialog1W>
else
WNetDisconnectDialog1	equ <WNetDisconnectDialog1A>
endif ;; NOT UNICODE
endif ;; WINVER GE 0x0400

;;
;;  Network Browsing.
;;

;DWORD
WNetOpenEnumA proto _CType \
	       dwScope: DWORD,
		dwType: DWORD,
	       dwUsage: DWORD,
	 lpNetResource: LPNETRESOURCEA,
	       lphEnum: LPHANDLE
;DWORD
WNetOpenEnumW proto _CType \
	       dwScope: DWORD,
		dwType: DWORD,
	       dwUsage: DWORD,
	 lpNetResource: LPNETRESOURCEW,
	       lphEnum: LPHANDLE
ifdef _UNICODE
WNetOpenEnum		equ <WNetOpenEnumW>
else
WNetOpenEnum		equ <WNetOpenEnumA>
endif ;; NOT UNICODE

;DWORD
WNetEnumResourceA proto _CType \
		 hEnum: HANDLE,
	      lpcCount: LPDWORD,
	      lpBuffer: LPVOID,
	  lpBufferSize: LPDWORD
;DWORD
WNetEnumResourceW proto _CType \
		 hEnum: HANDLE,
	      lpcCount: LPDWORD,
	      lpBuffer: LPVOID,
	  lpBufferSize: LPDWORD
ifdef _UNICODE
WNetEnumResource	equ <WNetEnumResourceW>
else
WNetEnumResource	equ <WNetEnumResourceA>
endif ;; NOT UNICODE

;DWORD
WNetCloseEnum proto _CType \
		 hEnum: HANDLE


;;
;;  Universal Naming.
;;

UNIVERSAL_NAME_INFO_LEVEL equ 0x00000001
REMOTE_NAME_INFO_LEVEL	equ 0x00000002

UNIVERSAL_NAME_INFOA	STRUC
lpUniversalName		LPSTR ?
UNIVERSAL_NAME_INFOA	ENDS
LPUNIVERSAL_NAME_INFOA	typedef ptr UNIVERSAL_NAME_INFOA
UNIVERSAL_NAME_INFOW	STRUC
lpUniversalName		LPWSTR ?
UNIVERSAL_NAME_INFOW	ENDS
LPUNIVERSAL_NAME_INFOW	typedef ptr UNIVERSAL_NAME_INFOW
ifdef _UNICODE
UNIVERSAL_NAME_INFO	typedef UNIVERSAL_NAME_INFOW
LPUNIVERSAL_NAME_INFO	typedef LPUNIVERSAL_NAME_INFOW
else
UNIVERSAL_NAME_INFO	typedef UNIVERSAL_NAME_INFOA
LPUNIVERSAL_NAME_INFO	typedef LPUNIVERSAL_NAME_INFOA
endif ;; UNICODE

REMOTE_NAME_INFOA	STRUC
lpUniversalName		LPSTR ?
lpConnectionName	LPSTR ?
lpRemainingPath		LPSTR ?
REMOTE_NAME_INFOA	ENDS
LPREMOTE_NAME_INFOA	typedef ptr REMOTE_NAME_INFOA
REMOTE_NAME_INFOW	STRUC
lpUniversalName		LPWSTR ?
lpConnectionName	LPWSTR ?
lpRemainingPath		LPWSTR ?
REMOTE_NAME_INFOW	ENDS
LPREMOTE_NAME_INFOW	typedef ptr REMOTE_NAME_INFOW
ifdef _UNICODE
REMOTE_NAME_INFO	typedef REMOTE_NAME_INFOW
LPREMOTE_NAME_INFO	typedef LPREMOTE_NAME_INFOW
else
REMOTE_NAME_INFO	typedef REMOTE_NAME_INFOA
LPREMOTE_NAME_INFO	typedef LPREMOTE_NAME_INFOA
endif ;; UNICODE

;DWORD
WNetGetUniversalNameA proto _CType \
	   lpLocalPath: LPCSTR,
	   dwInfoLevel: DWORD,
	      lpBuffer: LPVOID,
	  lpBufferSize: LPDWORD
;DWORD
WNetGetUniversalNameW proto _CType \
	   lpLocalPath: LPCWSTR,
	   dwInfoLevel: DWORD,
	      lpBuffer: LPVOID,
	  lpBufferSize: LPDWORD
ifdef _UNICODE
WNetGetUniversalName	equ <WNetGetUniversalNameW>
else
WNetGetUniversalName	equ <WNetGetUniversalNameA>
endif ;; NOT UNICODE

;;
;;  Authentication and Logon/Logoff.
;;

;DWORD
WNetGetUserA proto _CType \
		lpName: LPCSTR,
	    lpUserName: LPSTR,
	     lpnLength: LPDWORD
;DWORD
WNetGetUserW proto _CType \
		lpName: LPCWSTR,
	    lpUserName: LPWSTR,
	     lpnLength: LPDWORD
ifdef _UNICODE
WNetGetUser		equ <WNetGetUserW>
else
WNetGetUser		equ <WNetGetUserA>
endif ;; NOT UNICODE


;;
;; Other.
;;

if(WINVER GE 0x0400)
WNFMT_MULTILINE		equ 0x01
WNFMT_ABBREVIATED	equ 0x02
WNFMT_INENUM		equ 0x10
WNFMT_CONNECTION	equ 0x20
endif ;; WINVER GE 0x0400


if(WINVER GE 0x0400)
;DWORD
WNetGetProviderNameA proto _CType \
	     dwNetType: DWORD,
	lpProviderName: LPSTR,
	  lpBufferSize: LPDWORD
;DWORD
WNetGetProviderNameW proto _CType \
	     dwNetType: DWORD,
	lpProviderName: LPWSTR,
	  lpBufferSize: LPDWORD
ifdef _UNICODE
WNetGetProviderName	equ <WNetGetProviderNameW>
else
WNetGetProviderName	equ <WNetGetProviderNameA>
endif ;; NOT UNICODE

NETINFOSTRUCT		STRUC
cbStructure		dd ?
dwProviderVersion	dd ?
dwStatus		dd ?
dwCharacteristics	dd ?
dwHandle		dd ?
wNetType		dw ?
dwPrinters		dd ?
dwDrives		dd ?
NETINFOSTRUCT		ENDS
LPNETINFOSTRUCT		typedef ptr NETINFOSTRUCT

NETINFO_DLL16		equ 0x00000001	;; Provider running as 16 bit Winnet Driver
NETINFO_DISKRED		equ 0x00000004	;; Provider requires disk redirections to connect
NETINFO_PRINTERRED	equ 0x00000008	;; Provider requires printer redirections to connect

;DWORD
WNetGetNetworkInformationA proto _CType \
	    lpProvider: LPCSTR,
       lpNetInfoStruct: LPNETINFOSTRUCT
;DWORD
WNetGetNetworkInformationW proto _CType \
	    lpProvider: LPCWSTR,
       lpNetInfoStruct: LPNETINFOSTRUCT
ifdef _UNICODE
WNetGetNetworkInformation equ <WNetGetNetworkInformationW>
else
WNetGetNetworkInformation equ <WNetGetNetworkInformationA>
endif ;; NOT UNICODE

;;
;;  User Profiles.
;;

PFNGETPROFILEPATHA_T typedef proto \
	   pszUsername: LPCSTR,
	     pszBuffer: LPSTR,
	      cbBuffer: UINT
PFNGETPROFILEPATHA typedef ptr PFNGETPROFILEPATHA_T
PFNGETPROFILEPATHW_T typedef proto \
	   pszUsername: LPCWSTR,
	     pszBuffer: LPWSTR,
	      cbBuffer: UINT
PFNGETPROFILEPATHW typedef ptr PFNGETPROFILEPATHW_T
ifdef _UNICODE
PFNGETPROFILEPATH	equ <PFNGETPROFILEPATHW>
else
PFNGETPROFILEPATH	equ <PFNGETPROFILEPATHA>
endif ;; NOT UNICODE

PFNRECONCILEPROFILEA_T typedef proto \
	pszCentralFile: LPCSTR,
	  pszLocalFile: LPCSTR,
	       dwFlags: DWORD
PFNRECONCILEPROFILEA typedef ptr PFNRECONCILEPROFILEA_T
PFNRECONCILEPROFILEW_T typedef proto \
	pszCentralFile: LPCWSTR,
	  pszLocalFile: LPCWSTR,
	       dwFlags: DWORD
PFNRECONCILEPROFILEW typedef ptr PFNRECONCILEPROFILEW_T
ifdef _UNICODE
PFNRECONCILEPROFILE	equ <PFNRECONCILEPROFILEW>
else
PFNRECONCILEPROFILE	equ <PFNRECONCILEPROFILEA>
endif ;; NOT UNICODE

RP_LOGON		equ 0x01	;; if set, do for logon, else for logoff
RP_INIFILE		equ 0x02	;; if set, reconcile .INI file, else reg. hive


;;
;;  Policies.
;;

PFNPROCESSPOLICIESA_T typedef proto \
		  hwnd: HWND,
	       pszPath: LPCSTR,
	   pszUsername: LPCSTR,
       pszComputerName: LPCSTR,
	       dwFlags: DWORD
PFNPROCESSPOLICIESA typedef ptr PFNPROCESSPOLICIESA_T
PFNPROCESSPOLICIESW_T typedef proto \
		  hwnd: HWND,
	       pszPath: LPCWSTR,
	   pszUsername: LPCWSTR,
       pszComputerName: LPCWSTR,
	       dwFlags: DWORD
PFNPROCESSPOLICIESW typedef ptr PFNPROCESSPOLICIESW_T
ifdef _UNICODE
PFNPROCESSPOLICIES	equ <PFNPROCESSPOLICIESW>
else
PFNPROCESSPOLICIES	equ <PFNPROCESSPOLICIESA>
endif ;; NOT UNICODE

PP_DISPLAYERRORS	equ 0x01    ;; if set, display error messages, else fail silently if error
endif ;; WINVER GE 0x0400

;;
;;  Error handling.
;;

;DWORD
WNetGetLastErrorA proto _CType \
	       lpError: LPDWORD,
	    lpErrorBuf: LPSTR,
	 nErrorBufSize: DWORD,
	     lpNameBuf: LPSTR,
	  nNameBufSize: DWORD
;DWORD
WNetGetLastErrorW proto _CType \
	       lpError: LPDWORD,
	    lpErrorBuf: LPWSTR,
	 nErrorBufSize: DWORD,
	     lpNameBuf: LPWSTR,
	  nNameBufSize: DWORD
ifdef _UNICODE
WNetGetLastError	equ <WNetGetLastErrorW>
else
WNetGetLastError	equ <WNetGetLastErrorA>
endif ;; NOT UNICODE

;;
;;  STATUS CODES
;;

;; General

WN_SUCCESS		equ NO_ERROR
WN_NO_ERROR		equ NO_ERROR
WN_NOT_SUPPORTED	equ ERROR_NOT_SUPPORTED
WN_CANCEL		equ ERROR_CANCELLED
WN_RETRY		equ ERROR_RETRY
WN_NET_ERROR		equ ERROR_UNEXP_NET_ERR
WN_MORE_DATA		equ ERROR_MORE_DATA
WN_BAD_POINTER		equ ERROR_INVAID_ADDRESS
WN_BAD_VALUE		equ ERROR_INVAID_PARAMETER
WN_BAD_USER		equ ERROR_BAD_USERNAME
WN_BAD_PASSWORD		equ ERROR_INVAID_PASSWORD
WN_ACCESS_DENIED	equ ERROR_ACCESS_DENIED
WN_FUNCTION_BUSY	equ ERROR_BUSY
WN_WINDOWS_ERROR	equ ERROR_UNEXP_NET_ERR
WN_OUT_OF_MEMORY	equ ERROR_NOT_ENOUGH_MEMORY
WN_NO_NETWORK		equ ERROR_NO_NETWORK
WN_EXTENDED_ERROR	equ ERROR_EXTENDED_ERROR
WN_BAD_LEVEL		equ ERROR_INVALID_LEVE
WN_BAD_HANDLE		equ ERROR_INVALID_HANDE
if(WINVER GE 0x0400)
WN_NOT_INITIALIZING	equ ERROR_ALREADY_INITIAIZED
WN_NO_MORE_DEVICES	equ ERROR_NO_MORE_DEVICES
endif ;; WINVER GE 0x0400

;; Connection

WN_NOT_CONNECTED	equ ERROR_NOT_CONNECTED
WN_OPEN_FILES		equ ERROR_OPEN_FILES
WN_DEVICE_IN_USE	equ ERROR_DEVICE_IN_USE
WN_BAD_NETNAME		equ ERROR_BAD_NET_NAME
WN_BAD_LOCALNAME	equ ERROR_BAD_DEVICE
WN_ALREADY_CONNECTED	equ ERROR_AREADY_ASSIGNED
WN_DEVICE_ERROR		equ ERROR_GEN_FAILURE
WN_CONNECTION_CLOSED	equ ERROR_CONNECTION_UNAVAIL
WN_NO_NET_OR_BAD_PATH	equ ERROR_NO_NET_OR_BAD_PATH
WN_BAD_PROVIDER		equ ERROR_BAD_PROVIDER
WN_CANNOT_OPEN_PROFILE	equ ERROR_CANNOT_OPEN_PROFILE
WN_BAD_PROFILE		equ ERROR_BAD_PROFILE
WN_BAD_DEV_TYPE		equ ERROR_BAD_DEV_TYPE
WN_DEVICE_ALREADY_REMEMBERED equ ERROR_DEVICE_AREADY_REMEMBERED
WN_CONNECTED_OTHER_PASSWORD equ ERROR_CONNECTED_OTHER_PASSWORD

;; Enumeration

WN_NO_MORE_ENTRIES	equ ERROR_NO_MORE_ITEMS
WN_NOT_CONTAINER	equ ERROR_NOT_CONTAINER

if(WINVER GE 0x0400)
;; Authentication

WN_NOT_AUTHENTICATED	equ ERROR_NOT_AUTHENTICATED
WN_NOT_LOGGED_ON	equ ERROR_NOT_LOGGED_ON
WN_NOT_VALIDATED	equ ERROR_NO_LOGON_SERVERS
endif ;; WINVER GE 0x0400

;;
;;  For Shell
;;

if(WINVER GE 0x0400)
NETCONNECTINFOSTRUCT	STRUC
cbStructure		dd ?
dwFlags			dd ?
dwSpeed			dd ?
dwDelay			dd ?
dwOptDataSize		dd ?
NETCONNECTINFOSTRUCT	ENDS
LPNETCONNECTINFOSTRUCT	typedef ptr NETCONNECTINFOSTRUCT

WNCON_FORNETCARD	equ 0x00000001
WNCON_NOTROUTED		equ 0x00000002
WNCON_SLOWLINK		equ 0x00000004
WNCON_DYNAMIC		equ 0x00000008

;DWORD
MultinetGetConnectionPerformanceA proto _CType \
	 lpNetResource: LPNETRESOURCEA,
lpNetConnectInfoStruct: LPNETCONNECTINFOSTRUCT
;DWORD
MultinetGetConnectionPerformanceW proto _CType \
	 lpNetResource: LPNETRESOURCEW,
lpNetConnectInfoStruct: LPNETCONNECTINFOSTRUCT
ifdef _UNICODE
MultinetGetConnectionPerformance equ <MultinetGetConnectionPerformanceW>
else
MultinetGetConnectionPerformance equ <MultinetGetConnectionPerformanceA>
endif ;; NOT UNICODE
endif ;; WINVER GE 0x0400

endif  ;; _WINNETWK_

.list
