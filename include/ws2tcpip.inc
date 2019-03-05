ifndef _WS2TCPIP_H_
_WS2TCPIP_H_ equ <>

include winapifamily.inc

if NOT defined(_WINSOCK_DEPRECATED_BY)
if ((defined(_WINSOCK_DEPRECATED_NO_WARNINGS) OR defined(BUILD_WINDOWS)) AND NOT defined(_WINSOCK_DEPRECATE_WARNINGS)) OR defined(MIDL_PASS)
_WINSOCK_DEPRECATED_BY macro replacement
	endm
else
_WINSOCK_DEPRECATED_BY macro replacement
	exitm<"Use &replacement& instead or define _WINSOCK_DEPRECATED_NO_WARNINGS to disable deprecated API warnings">
	endm
endif
endif

include winsock2.inc
include ws2ipdef.inc
include limits.inc

UDP_NOCHECKSUM		equ 1
UDP_CHECKSUM_COVERAGE	equ 20

ifdef _MSC_VER
WS2TCPIP_INLINE		equ <>
else
WS2TCPIP_INLINE		equ <extern>
endif

EAI_AGAIN		equ WSATRY_AGAIN
EAI_BADFLAGS		equ WSAEINVA
EAI_FAIL		equ WSANO_RECOVERY
EAI_FAMILY		equ WSAEAFNOSUPPORT
EAI_MEMORY		equ WSA_NOT_ENOUGH_MEMORY
EAI_NOSECURENAME	equ WSA_SECURE_HOST_NOT_FOUND
;;EAI_NODATA		equ WSANO_DATA
EAI_NONAME		equ WSAHOST_NOT_FOUND
EAI_SERVICE		equ WSATYPE_NOT_FOUND
EAI_SOCKTYPE		equ WSAESOCKTNOSUPPORT
EAI_IPSECPOLICY		equ WSA_IPSEC_NAME_POLICY_ERROR

EAI_NODATA		equ EAI_NONAME

ifdef _UNICODE
PADDRINFOT		typedef ptr ADDRINFOW	    ;ADDRINFOT,
else
PADDRINFOT		typedef ptr ADDRINFOA	    ;ADDRINFOT,
endif

;;  RFC standard definition for getaddrinfo()

LPADDRINFO		typedef ptr ADDRINFOA	    ;ADDRINFO, FAR

if (_WIN32_WINNT GE 0x0600)
ifdef _UNICODE
PADDRINFOEX		typedef ptr ADDRINFOEXW	    ;ADDRINFOEX,
else
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
PADDRINFOEX		typedef ptr ADDRINFOEXA	    ;ADDRINFOEX,
endif
endif
endif

getaddrinfo proto WINAPI \
	     pNodeName: PCSTR,
	  pServiceName: PCSTR,
		pHints: ptr ADDRINFOA,
	      ppResult: ptr PADDRINFOA

if (NTDDI_VERSION GE NTDDI_WINXPSP2) OR (_WIN32_WINNT GE 0x0502)
GetAddrInfoW proto WINAPI \
	     pNodeName: PCWSTR,
	  pServiceName: PCWSTR,
		pHints: ptr ADDRINFOW,
	      ppResult: ptr PADDRINFOW

GetAddrInfoA		equ <getaddrinfo>
ifdef _UNICODE
GetAddrInfo		equ <GetAddrInfoW>
else
GetAddrInfo		equ <GetAddrInfoA>
endif
endif

if INCL_WINSOCK_API_TYPEDEFS
CALLBACK(LPFN_GETADDRINFO, :PCSTR, :PCSTR, :ptr ADDRINFOA, :ptr PADDRINFOA)
CALLBACK(LPFN_GETADDRINFOW, :PCWSTR, :PCWSTR, :ptr ADDRINFOW, :ptr PADDRINFOW)
LPFN_GETADDRINFOA	equ <LPFN_GETADDRINFO>
ifdef _UNICODE
LPFN_GETADDRINFOT	equ <LPFN_GETADDRINFOW>
else
LPFN_GETADDRINFOT	equ <LPFN_GETADDRINFOA>
endif
endif

if (_WIN32_WINNT GE 0x0600)

CALLBACK(LPLOOKUPSERVICE_COMPLETION_ROUTINE, :DWORD, :DWORD, :LPWSAOVERLAPPED)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

;_WINSOCK_DEPRECATED_BY("GetAddrInfoExW()")
;INT
GetAddrInfoExA proto WINAPI \
		 pName: PCSTR,
	  pServiceName: PCSTR,
	   dwNameSpace: DWORD,
	       lpNspId: LPGUID,
		 hints: ptr ADDRINFOEXA,
	      ppResult: ptr PADDRINFOEXA,
	       timeout: ptr timeval,
	  lpOverlapped: LPOVERLAPPED,
   lpCompletionRoutine: LPLOOKUPSERVICE_COMPLETION_ROUTINE,
	  lpNameHandle: LPHANDLE

endif

;INT
GetAddrInfoExW proto WINAPI \
		 pName: PCWSTR,
	  pServiceName: PCWSTR,
	   dwNameSpace: DWORD,
	       lpNspId: LPGUID,
		 hints: ptr ADDRINFOEXW,
	      ppResult: ptr PADDRINFOEXW,
	       timeout: ptr timeval,
	  lpOverlapped: LPOVERLAPPED,
   lpCompletionRoutine: LPLOOKUPSERVICE_COMPLETION_ROUTINE,
	      lpHandle: LPHANDLE

GetAddrInfoExCancel proto WINAPI \
	      lpHandle: LPHANDLE

GetAddrInfoExOverlappedResult proto WINAPI \
	  lpOverlapped: LPOVERLAPPED


ifdef _UNICODE
GetAddrInfoEx		equ <GetAddrInfoExW>
else
GetAddrInfoEx		equ <GetAddrInfoExA>
endif

if INCL_WINSOCK_API_TYPEDEFS

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

CALLBACK(LPFN_GETADDRINFOEXA,
		:PCSTR,
		:PCSTR,
		:DWORD,
		:LPGUID,
		:ptr ADDRINFOEXA,
		:ptr PADDRINFOEXA,
		:ptr timeval,
		:LPOVERLAPPED,
		:LPLOOKUPSERVICE_COMPLETION_ROUTINE,
		:LPHANDLE)

endif

CALLBACK(LPFN_GETADDRINFOEXW,
		:PCWSTR,
		:PCWSTR,
		:DWORD,
		:LPGUID,
		:ptr ADDRINFOEXW,
		:ptr PADDRINFOEXW,
		:ptr timeval,
		:LPOVERLAPPED,
		:LPLOOKUPSERVICE_COMPLETION_ROUTINE,
		:LPHANDLE)

CALLBACK(LPFN_GETADDRINFOEXCANCEL, :LPHANDLE)
CALLBACK(LPFN_GETADDRINFOEXOVERLAPPEDRESULT, :LPOVERLAPPED)

ifdef _UNICODE
LPFN_GETADDRINFOEX	equ <LPFN_GETADDRINFOEXW>
else
LPFN_GETADDRINFOEX	equ <LPFN_GETADDRINFOEXA>
endif
endif

endif

if (_WIN32_WINNT GE 0x0600)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
;_WINSOCK_DEPRECATED_BY("SetAddrInfoExW()")
;INT
SetAddrInfoExA proto WINAPI \
		 pName: PCSTR,
	  pServiceName: PCSTR,
	    pAddresses: ptr SOCKET_ADDRESS,
	dwAddressCount: DWORD,
		lpBlob: LPBLOB,
	       dwFlags: DWORD,
	   dwNameSpace: DWORD,
	       lpNspId: LPGUID,
	       timeout: ptr timeval,
	  lpOverlapped: LPOVERLAPPED,
   lpCompletionRoutine: LPLOOKUPSERVICE_COMPLETION_ROUTINE,
	  lpNameHandle: LPHANDLE

endif

SetAddrInfoExW proto WINAPI \
		 pName: PCWSTR,
	  pServiceName: PCWSTR,
	    pAddresses: ptr SOCKET_ADDRESS,
	dwAddressCount: DWORD,
		lpBlob: LPBLOB,
	       dwFlags: DWORD,
	   dwNameSpace: DWORD,
	       lpNspId: LPGUID,
	       timeout: ptr timeval,
	  lpOverlapped: LPOVERLAPPED,
   lpCompletionRoutine: LPLOOKUPSERVICE_COMPLETION_ROUTINE,
	  lpNameHandle: LPHANDLE

ifdef _UNICODE
SetAddrInfoEx		equ <SetAddrInfoExW>
else
SetAddrInfoEx		equ <SetAddrInfoExA>
endif

if INCL_WINSOCK_API_TYPEDEFS

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
CALLBACK(LPFN_SETADDRINFOEXA,
	  lpNameHandle: LPHANDLE
		 pName: PCSTR,
	  pServiceName: PCSTR,
	    pAddresses: ptr SOCKET_ADDRESS,
	dwAddressCount: DWORD,
		lpBlob: LPBLOB,
	       dwFlags: DWORD,
	   dwNameSpace: DWORD,
	       lpNspId: LPGUID,
	       timeout: ptr timeval,
	  lpOverlapped: LPOVERLAPPED,
   lpCompletionRoutine: LPLOOKUPSERVICE_COMPLETION_ROUTINE,
	  lpNameHandle: LPHANDLE)
endif


CALLBACK(LPFN_SETADDRINFOEXW,
	  lpNameHandle: LPHANDLE
		 pName: PCWSTR,
	  pServiceName: PCWSTR,
	    pAddresses: ptr SOCKET_ADDRESS,
	dwAddressCount: DWORD,
		lpBlob: LPBLOB,
	       dwFlags: DWORD,
	   dwNameSpace: DWORD,
	       lpNspId: LPGUID,
	       timeout: ptr timeval,
	  lpOverlapped: LPOVERLAPPED,
   lpCompletionRoutine: LPLOOKUPSERVICE_COMPLETION_ROUTINE,
	  lpNameHandle: LPHANDLE)

ifdef _UNICODE
LPFN_SETADDRINFOEX	equ <LPFN_SETADDRINFOEXW>
else
LPFN_SETADDRINFOEX	equ <LPFN_SETADDRINFOEXA>
endif
endif

endif

freeaddrinfo proto WINAPI \
	     pAddrInfo: PADDRINFOA


if (NTDDI_VERSION GE NTDDI_WINXPSP2) OR (_WIN32_WINNT GE 0x0502)

FreeAddrInfoW proto WINAPI pAddrInfo:PADDRINFOW


FreeAddrInfoA		equ <freeaddrinfo>
ifdef _UNICODE
FreeAddrInfo		equ <FreeAddrInfoW>
else
FreeAddrInfo		equ <FreeAddrInfoA>
endif
endif

if INCL_WINSOCK_API_TYPEDEFS
CALLBACK(LPFN_FREEADDRINFO, pAddrInfo:PADDRINFOA)
CALLBACK(LPFN_FREEADDRINFOW, pAddrInfo:PADDRINFOW)
LPFN_FREEADDRINFOA	equ <LPFN_FREEADDRINFO>
ifdef _UNICODE
LPFN_FREEADDRINFOT	equ <LPFN_FREEADDRINFOW>
else
LPFN_FREEADDRINFOT	equ <LPFN_FREEADDRINFOA>
endif
endif

if (_WIN32_WINNT GE 0x0600)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

;_WINSOCK_DEPRECATED_BY("FreeAddrInfoExW()")


FreeAddrInfoEx proto WINAPI \
	   pAddrInfoEx: PADDRINFOEXA

endif

FreeAddrInfoExW proto WINAPI \
	   pAddrInfoEx: PADDRINFOEXW


FreeAddrInfoExA		equ <FreeAddrInfoEx>
ifdef _UNICODE
FreeAddrInfoEx		equ <FreeAddrInfoExW>
endif

ifdef INCL_WINSOCK_API_TYPEDEFS

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
CALLBACK(LPFN_FREEADDRINFOEXA, pAddrInfoEx:PADDRINFOEXA)
endif
CALLBACK(LPFN_FREEADDRINFOEXW, pAddrInfoEx:PADDRINFOEXW)

ifdef _UNICODE
LPFN_FREEADDRINFOEX	equ <LPFN_FREEADDRINFOEXW>
else
LPFN_FREEADDRINFOEX	equ <LPFN_FREEADDRINFOEXA>
endif

endif
endif

socklen_t		typedef sdword

getnameinfo proto WINAPI \
	     pSockaddr: ptr SOCKADDR,
	SockaddrLength: socklen_t,
	   pNodeBuffer: PCHAR,
	NodeBufferSize: DWORD,
	pServiceBuffer: PCHAR,
     ServiceBufferSize: DWORD,
		 Flags: SINT


if (NTDDI_VERSION GE NTDDI_WINXPSP2) OR (_WIN32_WINNT GE 0x0502)

GetNameInfoW proto WINAPI \
	     pSockaddr: ptr SOCKADDR,
	SockaddrLength: socklen_t,
	   pNodeBuffer: PWCHAR,
	NodeBufferSize: DWORD,
	pServiceBuffer: PWCHAR,
     ServiceBufferSize: DWORD,
		 Flags: SINT


GetNameInfoA		equ <getnameinfo>
ifdef _UNICODE
GetNameInfo		equ <GetNameInfoW>
else
GetNameInfo		equ <GetNameInfoA>
endif
endif

if INCL_WINSOCK_API_TYPEDEFS
CALLBACK(LPFN_GETNAMEINFO,
	     pSockaddr: ptr SOCKADDR,
	SockaddrLength: socklen_t,
	   pNodeBuffer: PCHAR,
	NodeBufferSize: DWORD,
	pServiceBuffer: PCHAR,
     ServiceBufferSize: DWORD,
		 Flags: SINT)

CALLBACK(LPFN_GETNAMEINFOW,
	     pSockaddr: ptr SOCKADDR,
	SockaddrLength: socklen_t,
	   pNodeBuffer: PWCHAR,
	NodeBufferSize: DWORD,
	pServiceBuffer: PWCHAR,
     ServiceBufferSize: DWORD,
		 Flags: SINT)

LPFN_GETNAMEINFOA	equ <LPFN_GETNAMEINFO>
ifdef _UNICODE
LPFN_GETNAMEINFOT	equ <LPFN_GETNAMEINFOW>
else
LPFN_GETNAMEINFOT	equ <LPFN_GETNAMEINFOA>
endif
endif


if (NTDDI_VERSION GE NTDDI_VISTA)

inet_pton proto WINAPI \
		Family: SINT,
	 pszAddrString: PCSTR,
	      pAddrBuf: PVOID

InetPtonW proto WINAPI \
		Family: SINT,
	 pszAddrString: PCWSTR,
	      pAddrBuf: PVOID

inet_ntop proto WINAPI \
		Family: SINT,
		 pAddr: PVOID,
	    pStringBuf: PSTR,
	 StringBufSize: size_t

InetNtopW proto WINAPI \
		Family: SINT,
		 pAddr: PVOID,
	    pStringBuf: PWSTR,
	 StringBufSize: size_t


InetPtonA		equ <inet_pton>
InetNtopA		equ <inet_ntop>
ifdef _UNICODE
InetPton		equ <InetPtonW>
InetNtop		equ <InetNtopW>
else
InetPton		equ <InetPtonA>
InetNtop		equ <InetNtopA>
endif

if INCL_WINSOCK_API_TYPEDEFS

CALLBACK(LPFN_INET_PTONA,
		Family: SINT,
	 pszAddrString: PCSTR,
	      pAddrBuf: PVOID)

CALLBACK(LPFN_INET_PTONW,
		Family: SINT,
	 pszAddrString: PCWSTR,
	      pAddrBuf: PVOID)

CALLBACK(LPFN_INET_NTOPA,
		Family: SINT,
		 pAddr: PVOID,
	    pStringBuf: PSTR,
	 StringBufSize: size_t)

CALLBACK(LPFN_INET_NTOPW,
		Family: SINT,
		 pAddr: PVOID,
	    pStringBuf: PWSTR,
	 StringBufSize: size_t)

ifdef _UNICODE
LPFN_INET_PTON		equ <LPFN_INET_PTONW>
LPFN_INET_NTOP		equ <LPFN_INET_NTOPW>
else
LPFN_INET_PTON		equ <LPFN_INET_PTONA>
LPFN_INET_NTOP		equ <LPFN_INET_NTOPA>
endif

endif  ;;  TYPEDEFS
endif  ;;  (NTDDI_VERSION GE NTDDI_VISTA)


if INCL_WINSOCK_API_PROTOTYPES
ifdef _UNICODE
gai_strerror		equ <gai_strerrorW>
else
gai_strerror		equ <gai_strerrorA>
endif

GAI_STRERROR_BUFFER_SIZE equ 1024

if 0
gai_strerrorA macro ecode
    FormatMessageA(
	FORMAT_MESSAGE_FROM_SYSTEM or FORMAT_MESSAGE_IGNORE_INSERTS or FORMAT_MESSAGE_MAX_WIDTH_MASK,
	NULL,
	ecode,
	MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
	addr _bufin,
	GAI_STRERROR_BUFFER_SIZE,
	NULL)
    mov ecx,eax
    lea rax,_bufin
    retm<rax>
    endm
gai_strerrorW macro ecode
    FormatMessageW(
	FORMAT_MESSAGE_FROM_SYSTEM or FORMAT_MESSAGE_IGNORE_INSERTS or FORMAT_MESSAGE_MAX_WIDTH_MASK,
	NULL,
	ecode,
	MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
	addr _bufin,
	GAI_STRERROR_BUFFER_SIZE,
	NULL)
    mov ecx,eax
    lea rax,_bufin
    retm<rax>
    endm
endif

endif ;; INCL_WINSOCK_API_PROTOTYPES


if (NTDDI_VERSION GE NTDDI_WINXP)
endif

ifdef IDEAL_SEND_BACKLOG_IOCTLS
endif

if (_WIN32_WINNT GE 0x0600)
ifdef _SECURE_SOCKET_TYPES_DEFINED_

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

WSASetSocketSecurity proto WINAPI \
		Socket: SOCKET,
      SecuritySettings: ptr SOCKET_SECURITY_SETTINGS,
   SecuritySettingsLen: ULONG,
	    Overlapped: LPWSAOVERLAPPED,
     CompletionRoutine: LPWSAOVERLAPPED_COMPLETION_ROUTINE

WSAQuerySocketSecurity proto WINAPI \
		Socket: SOCKET,
 SecurityQueryTemplate: ptr SOCKET_SECURITY_QUERY_TEMPLATE,
SecurityQueryTemplateLen: ULONG,
     SecurityQueryInfo: SOCKET_SECURITY_QUERY_INFO*,
  SecurityQueryInfoLen: ptr ULONG,
	    Overlapped: LPWSAOVERLAPPED,
     CompletionRoutine: LPWSAOVERLAPPED_COMPLETION_ROUTINE


WSASetSocketPeerTargetName proto WINAPI \
		Socket: SOCKET,
	PeerTargetName: ptr SOCKET_PEER_TARGET_NAME,
     PeerTargetNameLen: ULONG,
	    Overlapped: LPWSAOVERLAPPED,
     CompletionRoutine: LPWSAOVERLAPPED_COMPLETION_ROUTINE


WSADeleteSocketPeerTargetName proto WINAPI \
		Socket: SOCKET,
	      PeerAddr: ptr sockaddr,
	   PeerAddrLen: ULONG,
	    Overlapped: LPWSAOVERLAPPED,
     CompletionRoutine: LPWSAOVERLAPPED_COMPLETION_ROUTINE


WSAImpersonateSocketPeer proto WINAPI \
		Socket: SOCKET,
	      PeerAddr: ptr sockaddr,
	   PeerAddrLen: ULONG


WSARevertImpersonation proto WINAPI

endif

endif ;;_SECURE_SOCKET_TYPES_DEFINED_
endif ;;(_WIN32_WINNT GE 0x0600)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

if NOT defined(_WIN32_WINNT) OR (_WIN32_WINNT LE 0x0500)
include wspiapi.inc
endif
endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)


endif  ;; _WS2TCPIP_H_
