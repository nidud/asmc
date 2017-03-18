ifndef __LIBC_INC
 include libc.inc
endif
.xlist
;;
;; This header file corresponds to version 2.2.x of the WinSock API
;; specification.
;;
ifndef _WINSOCK2API_
_WINSOCK2API_ equ 1
_WINSOCKAPI_  equ 1 ;; Prevent inclusion of winsock.h in windows.h

;;
;; Ensure structures are packed consistently.
;;

;include <pshpack4.h>

;;
;; Default: include function prototypes, don't include function typedefs.
;;

ifndef INCL_WINSOCK_API_PROTOTYPES
INCL_WINSOCK_API_PROTOTYPES equ 1
endif

ifndef INCL_WINSOCK_API_TYPEDEFS
INCL_WINSOCK_API_TYPEDEFS equ 0
endif

;;
;; Pull in WINDOWS.H if necessary
;;
ifndef _INC_WINDOWS
include windows.inc
.xlist
endif ;; _INC_WINDOWS

;;
;; Define the current Winsock version. To build an earlier Winsock version
;; application redefine this value prior to including Winsock2.h.
;;

if NOT defined(MAKEWORD)
MAKEWORD macro low,high
	exitm<(((low)) OR (((high)) SHL 8)))>
	endm
endif

ifndef WINSOCK_VERSION
WINSOCK_VERSION		equ MAKEWORD(2,2)
endif

;;
;; Establish DLL function linkage if supported by the current build
;; environment and not previously defined.
;;

ifndef WINSOCK_API_LINKAGE
ifdef DECLSPEC_IMPORT
WINSOCK_API_LINKAGE	equ DECSPEC_IMPORT
else
WINSOCK_API_LINKAGE	equ 1
endif
endif

;;
;; Basic system type definitions, taken from the BSD file sys/types.h.
;;
;u_char			 typedef unsigned char
;u_short		 typedef WORD
;UINT			 typedef unsigned int
;u_long			 typedef DWORD

;;
;; The new type to be used in all
;; instances which refer to sockets.
;;
SOCKET			typedef UINT

;;
;; Select uses arrays of SOCKETs.  These macros manipulate such
;; arrays.  FD_SETSIZE may be defined by the user before including
;; this file, but the default here should be >= 64.
;;
;; CAVEAT IMPLEMENTOR and USER: THESE MACROS AND TYPES MUST BE
;; INCLUDED IN WINSOCK2.H EXACTLY AS SHOWN HERE.
;;
ifndef FD_SETSIZE
FD_SETSIZE		equ 64
endif ;; FD_SETSIZE

fd_set			STRUC
fd_count		UINT ?	;; how many are SET?
fd_array		SOCKET FD_SETSIZE dup(?) ;; an array of SOCKETs
fd_set			ENDS

__WSAFDIsSet		proto :SOCKET, :ptr fd_set

FD_CLR macro fd, set
	pushad
	lea	ebx,set
	mov	eax,fd
	mov	ecx,[ebx].fd_set.fd_count
	lea	esi,[ebx].fd_set.fd_array
	mov	edi,esi
	.while	ecx
		.if eax == [esi]
			dec [ebx].fd_set.fd_count
			add esi, 4
		.endif
		movsd
		dec ecx
	.endw
	popad
	endm

FD_SET macro fd, set
	lea	edx,set
	mov	eax,fd
	mov	ecx,[edx].fd_set.fd_count
	.if	ecx < FD_SETSIZE
		mov [edx].fd_set.fd_array[ecx*4],eax
		inc [edx].fd_set.fd_count
	.endif
	endm

FD_ZERO macro set
	lea	eax, set
	mov	[eax].fd_set.fd_count,0
	endm

FD_ISSET macro fd, set
	exitm<__WSAFDIsSet(fd, set)>
	endm

;;
;; Structure used in select() call, taken from the BSD file sys/time.h.
;;
timeval		STRUC
tv_sec		LONG ?	;; seconds
tv_usec		LONG ?	;; and microseconds
timeval		ENDS

;;
;; Operations on timevals.
;;
;; NB: timercmp does not work for >= or <=.
;;
timerisset macro tvp
	exitm<((tvp)->GT tv_sec OR (tvp)->GT tv_usec)>
	endm
timercmp macro tvp, uvp, cmp
	exitm<((tvp)- GT tv_sec cmp (uvp)- GT tv_sec OR (tvp)- GT tv_sec EQ (uvp)- GT tv_sec AND (tvp)- GT tv_usec cmp (uvp)- GT tv_usec)>
	endm
timerclear macro tvp
	exitm<tvp.GT tv_sec = tvp.GT tv_usec = 0>
	endm

;;
;; Commands for ioctlsocket(),	taken from the BSD file fcntl.h.
;;
;;
;; Ioctl's have the command encoded in the lower word,
;; and the size of any in or out parameters in the upper
;; word.  The high 2 bits of the upper word are used
;; to encode the in/out status of the parameter; for now
;; we restrict parameters to at most 128 bytes.
;;
IOCPARM_MASK		equ 0x7f		;; parameters must be LT 128 bytes
IOC_VOID		equ 0x20000000	;; no parameters
IOC_OUT			equ 0x40000000	;; copy out parameters
IOC_IN			equ 0x80000000	;; copy in parameters
IOC_INOUT		equ (IOC_IN OR IOC_OUT)
;; old 0x20000000 distinguishes new & ioctl's
_IO macro x,y
	exitm<(IOC_VOID OR ((x) SHL 8) OR (y))>
	endm

_IOR macro x,y,t
	exitm<(IOC_OUT OR (((long)sizeof(t) AND IOCPARM_MASK) SHL 16) OR ((x) SHL 8) OR (y))>
	endm

_IOW macro x,y,t
	exitm<(IOC_IN OR (((long)sizeof(t) AND IOCPARM_MASK) SHL 16) OR ((x) SHL 8) OR (y))>
	endm

FIONREAD		equ _IOR('f', 127, DWORD) ;; get # bytes to read
FIONBIO			equ _IOW('f', 126, DWORD) ;; set/clear non-blocking i/o
FIOASYNC		equ _IOW('f', 125, DWORD) ;; set/clear async i/o

;; Socket I/O Controls
SIOCSHIWAT		equ _IOW('s',  0, DWORD) ;; set high watermark
SIOCGHIWAT		equ _IOR('s',  1, DWORD) ;; get high watermark
SIOCSLOWAT		equ _IOW('s',  2, DWORD) ;; set low watermark
SIOCGLOWAT		equ _IOR('s',  3, DWORD) ;; get low watermark
SIOCATMARK		equ _IOR('s',  7, DWORD) ;; at oob mark?

;;
;; Structures returned by network data base library, taken from the
;; BSD file netdb.h.  All addresses are supplied in host order, and
;; returned in network order (suitable for use in system calls).
;;

hostent			STRUC
h_name			LPSTR ? ;; official name of host
h_aliases		LPSTR ? ;; alias list
h_addrtype		dw ?	;; host address type
h_length		dw ?	;; length of address
h_addr_list		LPSTR ? ;; list of addresses
h_addr			equ h_addr_list[0]		;; address, for backward compat
hostent			ENDS

;;
;; It is assumed here that a network number
;; fits in 32 bits.
;;
netent			STRUC
n_name			LPSTR ? ;; official name of net
n_aliases		LPSTR ? ;; alias list
n_addrtype		dw ?	;; net address type
n_net			dd ?	;; network #
netent			ENDS

servent			STRUC
s_name			LPSTR ? ;; official service name
s_aliases		LPSTR ? ;; alias list
s_port			dw ?	;; port #
s_proto			LPSTR ? ;; protocol to use
servent			ENDS

protoent		STRUC
p_name			LPSTR ? ;; official protocol name
p_aliases		LPSTR ? ;; alias list
p_proto			dw ?	;; protocol #
protoent		ENDS

;;
;; Constants and structures defined by the internet system,
;; Per RFC 790, September 1981, taken from the BSD file netinet/in.h.
;;

;;
;; Protocols
;;
IPPROTO_IP		equ 0		;; dummy for IP
IPPROTO_ICMP		equ 1		;; control message protocol
IPPROTO_IGMP		equ 2		;; internet group management protocol
IPPROTO_GGP		equ 3		;; gateway^2 (deprecated)
IPPROTO_TCP		equ 6		;; tcp
IPPROTO_PUP		equ 12		;; pup
IPPROTO_UDP		equ 17		;; user datagram protocol
IPPROTO_IDP		equ 22		;; xns idp
IPPROTO_ND		equ 77		;; UNOFFICIA net disk proto

IPPROTO_RAW		equ 255		;; raw IP packet
IPPROTO_MAX		equ 256

;;
;; Port/socket numbers: network standard functions
;;
IPPORT_ECHO		equ 7
IPPORT_DISCARD		equ 9
IPPORT_SYSTAT		equ 11
IPPORT_DAYTIME		equ 13
IPPORT_NETSTAT		equ 15
IPPORT_FTP		equ 21
IPPORT_TELNET		equ 23
IPPORT_SMTP		equ 25
IPPORT_TIMESERVER	equ 37
IPPORT_NAMESERVER	equ 42
IPPORT_WHOIS		equ 43
IPPORT_MTP		equ 57

;;
;; Port/socket numbers: host specific functions
;;
IPPORT_TFTP		equ 69
IPPORT_RJE		equ 77
IPPORT_FINGER		equ 79
IPPORT_TTYLINK		equ 87
IPPORT_SUPDUP		equ 95

;;
;; UNIX TCP sockets
;;
IPPORT_EXECSERVER	equ 512
IPPORT_LOGINSERVER	equ 513
IPPORT_CMDSERVER	equ 514
IPPORT_EFSSERVER	equ 520

;;
;; UNIX UDP sockets
;;
IPPORT_BIFFUDP		equ 512
IPPORT_WHOSERVER	equ 513
IPPORT_ROUTESERVER	equ 520
;; 520+1 also used

;;
;; Ports < IPPORT_RESERVED are reserved for
;; privileged processes (e.g. root).
;;
IPPORT_RESERVED		equ 1024

;;
;; Link numbers
;;
IMPLINK_IP		equ 155
IMPLINK_LOWEXPER	equ 156
IMPLINK_HIGHEXPER	equ 158

;;
;; Internet address (old style... should be updated)
;;
in_addr			STRUC
UNION S_un
    STRUC S_un_b
	s_b1		db ?
	s_b2		db ?
	s_b3		db ?
	s_b4		db ?
    ENDS
    STRUC S_un_w
	s_w1		dw ?
	s_w2		dw ?
    ENDS
    S_addr		dd ?
ENDS
s_addr			equ <S_un.S_addr>
;; can be used for most tcp & ip code
s_host			equ <S_un.S_un_b.s_b2>
;; host on imp
s_net			equ <S_un.S_un_b.s_b1>
;; network
s_imp			equ <S_un.S_un_w.s_w2>
;; imp
s_impno			equ <S_un.S_un_b.s_b4>
;; imp #
s_lh			equ <S_un.S_un_b.s_b3>
;; logical host
in_addr			ENDS

;;
;; Definitions of bits in internet address integers.
;; On subnets, the decomposition of addresses to host and net parts
;; is done according to subnet mask, not the masks here.
;;
IN_CLASSA macro i
	exitm<(((i) AND 0x80000000) EQ 0)>
	endm
IN_CLASSA_NET		equ 0xff000000
IN_CLASSA_NSHIFT	equ 24
IN_CLASSA_HOST		equ 0x00ffffff
IN_CLASSA_MAX		equ 128

IN_CLASSB macro i
	exitm<(((i) AND 0xc0000000) EQ 0x80000000)>
	endm
IN_CLASSB_NET		equ 0xffff0000
IN_CLASSB_NSHIFT	equ 16
IN_CLASSB_HOST		equ 0x0000ffff
IN_CLASSB_MAX		equ 65536

IN_CLASSC macro i
	exitm<(((i) AND 0xe0000000) EQ 0xc0000000)>
	endm
IN_CLASSC_NET		equ 0xffffff00
IN_CLASSC_NSHIFT	equ 8
IN_CLASSC_HOST		equ 0x000000ff

IN_CLASSD macro i
	exitm<(((i) AND 0xf0000000) EQ 0xe0000000)>
	endm
IN_CLASSD_NET		equ 0xf0000000	 ;; These ones aren't really
IN_CLASSD_NSHIFT	equ 28		 ;; net and host fields, but
IN_CLASSD_HOST		equ 0x0fffffff	 ;; routing needn't know.
IN_MULTICAST macro i
	exitm<IN_CASSD(i)>
	endm

INADDR_ANY		equ 0x00000000
INADDR_LOOPBACK		equ 0x7f000001
INADDR_BROADCAST	equ 0xffffffff
INADDR_NONE		equ 0xffffffff

ADDR_ANY		equ INADDR_ANY

;;
;; Socket address, internet style.
;;
sockaddr_in		STRUC
sin_family		dw ?
sin_port		dw ?
sin_addr		PVOID ?
sin_zero		db 8 dup(?)
sockaddr_in		ENDS

WSADESCRIPTION_LEN	equ 256
WSASYS_STATUS_LEN	equ 128

WSADATA			STRUC
wVersion		dw ?
wHighVersion		dw ?
szDescription		db WSADESCRIPTION_LEN+1 dup(?)
szSystemStatus		db WSASYS_STATUS_LEN+1 dup(?)
iMaxSockets		dw ?
iMaxUdpDg		dw ?
lpVendorInfo		LPSTR ?
WSADATA			ENDS
LPWSADATA		typedef ptr WSADATA

;;
;; Definitions related to sockets: types, address families, options,
;; taken from the BSD file sys/socket.h.
;;

;;
;; This is used instead of -1, since the
;; SOCKET type is unsigned.
;;
INVALID_SOCKET		equ <NOT 0>
SOCKET_ERROR		equ (-1)

;;
;; The	following  may	be used in place of the address family, socket type, or
;; protocol  in	 a  call  to WSASocket to indicate that the corresponding value
;; should  be taken from the supplied WSAPROTOCOL_INFO structure instead of the
;; parameter itself.
;;
FROM_PROTOCOL_INFO	equ (-1)

;;
;; Types
;;
SOCK_STREAM		equ 1		;; stream socket
SOCK_DGRAM		equ 2		;; datagram socket
SOCK_RAW		equ 3		;; raw-protocol interface
SOCK_RDM		equ 4		;; reliably-delivered message
SOCK_SEQPACKET		equ 5		;; sequenced packet stream

;;
;; Option flags per-socket.
;;
SO_DEBUG		equ 0x0001		;; turn on debugging info recording
SO_ACCEPTCONN		equ 0x0002		;; socket has had listen()
SO_REUSEADDR		equ 0x0004		;; allow local address reuse
SO_KEEPALIVE		equ 0x0008		;; keep connections alive
SO_DONTROUTE		equ 0x0010		;; just use interface addresses
SO_BROADCAST		equ 0x0020		;; permit sending of broadcast msgs
SO_USELOOPBACK		equ 0x0040		;; bypass hardware when possible
SO_LINGER		equ 0x0080		;; linger on close if data present
SO_OOBINLINE		equ 0x0100		;; leave received OOB data in line

SO_DONTLINGER		equ <NOT SO_LINGER>

;;
;; Additional options.
;;
SO_SNDBUF		equ 0x1001		;; send buffer size
SO_RCVBUF		equ 0x1002		;; receive buffer size
SO_SNDLOWAT		equ 0x1003		;; send low-water mark
SO_RCVLOWAT		equ 0x1004		;; receive low-water mark
SO_SNDTIMEO		equ 0x1005		;; send timeout
SO_RCVTIMEO		equ 0x1006		;; receive timeout
SO_ERROR		equ 0x1007		;; get error status and clear
SO_TYPE			equ 0x1008		;; get socket type

;;
;; WinSock 2 extension -- new options
;;
SO_GROUP_ID		equ 0x2001	;; ID of a socket group
SO_GROUP_PRIORITY	equ 0x2002	;; the relative priority within a group
SO_MAX_MSG_SIZE		equ 0x2003	;; maximum message size
SO_PROTOCOL_INFOA	equ 0x2004	;; WSAPROTOCOL_INFOA structure
SO_PROTOCOL_INFOW	equ 0x2005	;; WSAPROTOCOL_INFOW structure
ifdef _UNICODE
SO_PROTOCOL_INFO	equ SO_PROTOCOL_INFOW
else
SO_PROTOCOL_INFO	equ SO_PROTOCOL_INFOA
endif ;; UNICODE
PVD_CONFIG		equ 0x3001	  ;; configuration info for service provider

;;
;; TCP options.
;;
TCP_NODELAY		equ 0x0001

;;
;; Address families.
;;
AF_UNSPEC		equ 0		;; unspecified
;;
;; Although  AF_UNSPEC	is  defined for backwards compatibility, using
;; AF_UNSPEC for the "af" parameter when creating a socket is STRONGLY
;; DISCOURAGED.	   The	interpretation	of  the	 "protocol"  parameter
;; depends  on the actual address family chosen.  As environments grow
;; to  include	more  and  more	 address families that use overlapping
;; protocol  values  there  is	more  and  more	 chance of choosing an
;; undesired address family when AF_UNSPEC is used.
;;
AF_UNIX			equ 1		;; local to host (pipes, portals)
AF_INET			equ 2		;; internetwork: UDP, TCP, etc.
AF_IMPLINK		equ 3		;; arpanet imp addresses
AF_PUP			equ 4		;; pup protocols: e.g. BSP
AF_CHAOS		equ 5		;; mit CHAOS protocols
AF_NS			equ 6		;; XEROX NS protocols
AF_IPX			equ AF_NS		;; IPX protocols: IPX, SPX, etc.
AF_ISO			equ 7		;; ISO protocols
AF_OSI			equ AF_ISO		;; OSI is ISO
AF_ECMA			equ 8		;; european computer manufacturers
AF_DATAKIT		equ 9		;; datakit protocols
AF_CCITT		equ 10		;; CCITT protocols, X.25 etc
AF_SNA			equ 11		;; IBM SNA
AF_DECnet		equ 12		;; DECnet
AF_DLI			equ 13		;; Direct data link interface
AF_LAT			equ 14		;; LAT
AF_HYLINK		equ 15		;; NSC Hyperchannel
AF_APPLETALK		equ 16		;; AppleTalk
AF_NETBIOS		equ 17		;; NetBios-style addresses
AF_VOICEVIEW		equ 18		;; VoiceView
AF_FIREFOX		equ 19		;; Protocols from Firefox
AF_UNKNOWN1		equ 20		;; Somebody is using this NOT
AF_BAN			equ 21		;; Banyan
AF_ATM			equ 22		;; Native ATM Services
AF_INET6		equ 23		;; Internetwork Version 6
AF_CLUSTER		equ 24		;; Microsoft Wolfpack
AF_12844		equ 25		;; IEEE 1284.4 WG AF


AF_MAX			equ 26

;;
;; Structure used by kernel to store most
;; addresses.
;;
sockaddr		STRUC
sa_family		dw ?		;; address family
sa_data			db 14 dup(?)	;; up to 14 bytes of direct address
sockaddr		ENDS

;;
;; Structure used by kernel to pass protocol
;; information in raw sockets.
;;
sockproto		STRUC
sp_family		dw ?	;; address family
sp_protocol		dw ?	;; protocol
sockproto		ENDS

;;
;; Protocol families, same as address families for now.
;;
PF_UNSPEC		equ AF_UNSPEC
PF_UNIX			equ AF_UNIX
PF_INET			equ AF_INET
PF_IMPLINK		equ AF_IMPLINK
PF_PUP			equ AF_PUP
PF_CHAOS		equ AF_CHAOS
PF_NS			equ AF_NS
PF_IPX			equ AF_IPX
PF_ISO			equ AF_ISO
PF_OSI			equ AF_OSI
PF_ECMA			equ AF_ECMA
PF_DATAKIT		equ AF_DATAKIT
PF_CCITT		equ AF_CCITT
PF_SNA			equ AF_SNA
PF_DECnet		equ AF_DECnet
PF_DLI			equ AF_DI
PF_LAT			equ AF_LAT
PF_HYLINK		equ AF_HYLINK
PF_APPLETALK		equ AF_APPLETAK
PF_VOICEVIEW		equ AF_VOICEVIEW
PF_FIREFOX		equ AF_FIREFOX
PF_UNKNOWN1		equ AF_UNKNOWN1
PF_BAN			equ AF_BAN
PF_ATM			equ AF_ATM
PF_INET6		equ AF_INET6

PF_MAX			equ AF_MAX

;;
;; Structure used for manipulating linger option.
;;
linger			STRUC
l_onoff			dw ?	;; option on/off
l_linger		dw ?	;; linger time
linger			ENDS

;;
;; Level number for (get/set)sockopt() to apply to socket itself.
;;
SOL_SOCKET		equ 0xffff		;; options for socket level

;;
;; Maximum queue length specifiable by listen.
;;
SOMAXCONN		equ 0x7fffffff

MSG_OOB			equ 0x1		;; process out-of-band data
MSG_PEEK		equ 0x2		;; peek at incoming message
MSG_DONTROUTE		equ 0x4		;; send without using routing tables

MSG_PARTIAL		equ 0x8000		;; partial send or recv for message xport

;;
;; WinSock 2 extension -- new flags for WSASend(), WSASendTo(), WSARecv() and
;;			    WSARecvFrom()
;;
MSG_INTERRUPT		equ 0x10		;; send/recv in the interrupt context

MSG_MAXIOVLEN		equ 16

;;
;; Define constant based on rfc883, used by gethostbyxxxx() calls.
;;
MAXGETHOSTSTRUCT	equ 1024

;;
;; WinSock 2 extension -- bit values and indices for FD_XXX network events
;;
FD_READ_BIT		equ 0
FD_READ			equ (1 SHL FD_READ_BIT)

FD_WRITE_BIT		equ 1
FD_WRITE		equ (1 SHL FD_WRITE_BIT)

FD_OOB_BIT		equ 2
FD_OOB			equ (1 SHL FD_OOB_BIT)

FD_ACCEPT_BIT		equ 3
FD_ACCEPT		equ (1 SHL FD_ACCEPT_BIT)

FD_CONNECT_BIT		equ 4
FD_CONNECT		equ (1 SHL FD_CONNECT_BIT)

FD_CLOSE_BIT		equ 5
FD_CLOSE		equ (1 SHL FD_COSE_BIT)

FD_QOS_BIT		equ 6
FD_QOS			equ (1 SHL FD_QOS_BIT)

FD_GROUP_QOS_BIT	equ 7
FD_GROUP_QOS		equ (1 SHL FD_GROUP_QOS_BIT)

FD_ROUTING_INTERFACE_CHANGE_BIT equ 8
FD_ROUTING_INTERFACE_CHANGE equ (1 SHL FD_ROUTING_INTERFACE_CHANGE_BIT)

FD_ADDRESS_LIST_CHANGE_BIT equ 9
FD_ADDRESS_LIST_CHANGE	equ (1 SHL FD_ADDRESS_LIST_CHANGE_BIT)

FD_MAX_EVENTS		equ 10
FD_ALL_EVENTS		equ ((1 SHL FD_MAX_EVENTS) - 1)


;;
;; All Windows Sockets error constants are biased by WSABASEERR from
;; the "normal"
;;
WSABASEERR		equ 10000
;;
;; Windows Sockets definitions of regular Microsoft C error constants
;;
WSAEINTR		equ (WSABASEERR+4)
WSAEBADF		equ (WSABASEERR+9)
WSAEACCES		equ (WSABASEERR+13)
WSAEFAULT		equ (WSABASEERR+14)
WSAEINVAL		equ (WSABASEERR+22)
WSAEMFILE		equ (WSABASEERR+24)

;;
;; Windows Sockets definitions of regular Berkeley error constants
;;
WSAEWOULDBLOCK		equ (WSABASEERR+35)
WSAEINPROGRESS		equ (WSABASEERR+36)
WSAEALREADY		equ (WSABASEERR+37)
WSAENOTSOCK		equ (WSABASEERR+38)
WSAEDESTADDRREQ		equ (WSABASEERR+39)
WSAEMSGSIZE		equ (WSABASEERR+40)
WSAEPROTOTYPE		equ (WSABASEERR+41)
WSAENOPROTOOPT		equ (WSABASEERR+42)
WSAEPROTONOSUPPORT	equ (WSABASEERR+43)
WSAESOCKTNOSUPPORT	equ (WSABASEERR+44)
WSAEOPNOTSUPP		equ (WSABASEERR+45)
WSAEPFNOSUPPORT		equ (WSABASEERR+46)
WSAEAFNOSUPPORT		equ (WSABASEERR+47)
WSAEADDRINUSE		equ (WSABASEERR+48)
WSAEADDRNOTAVAIL	equ (WSABASEERR+49)
WSAENETDOWN		equ (WSABASEERR+50)
WSAENETUNREACH		equ (WSABASEERR+51)
WSAENETRESET		equ (WSABASEERR+52)
WSAECONNABORTED		equ (WSABASEERR+53)
WSAECONNRESET		equ (WSABASEERR+54)
WSAENOBUFS		equ (WSABASEERR+55)
WSAEISCONN		equ (WSABASEERR+56)
WSAENOTCONN		equ (WSABASEERR+57)
WSAESHUTDOWN		equ (WSABASEERR+58)
WSAETOOMANYREFS		equ (WSABASEERR+59)
WSAETIMEDOUT		equ (WSABASEERR+60)
WSAECONNREFUSED		equ (WSABASEERR+61)
WSAELOOP		equ (WSABASEERR+62)
WSAENAMETOOLONG		equ (WSABASEERR+63)
WSAEHOSTDOWN		equ (WSABASEERR+64)
WSAEHOSTUNREACH		equ (WSABASEERR+65)
WSAENOTEMPTY		equ (WSABASEERR+66)
WSAEPROCLIM		equ (WSABASEERR+67)
WSAEUSERS		equ (WSABASEERR+68)
WSAEDQUOT		equ (WSABASEERR+69)
WSAESTALE		equ (WSABASEERR+70)
WSAEREMOTE		equ (WSABASEERR+71)

;;
;; Extended Windows Sockets error constant definitions
;;
WSASYSNOTREADY		equ (WSABASEERR+91)
WSAVERNOTSUPPORTED	equ (WSABASEERR+92)
WSANOTINITIALISED	equ (WSABASEERR+93)
WSAEDISCON		equ (WSABASEERR+101)
WSAENOMORE		equ (WSABASEERR+102)
WSAECANCELLED		equ (WSABASEERR+103)
WSAEINVALIDPROCTABLE	equ (WSABASEERR+104)
WSAEINVALIDPROVIDER	equ (WSABASEERR+105)
WSAEPROVIDERFAILEDINIT	equ (WSABASEERR+106)
WSASYSCALLFAILURE	equ (WSABASEERR+107)
WSASERVICE_NOT_FOUND	equ (WSABASEERR+108)
WSATYPE_NOT_FOUND	equ (WSABASEERR+109)
WSA_E_NO_MORE		equ (WSABASEERR+110)
WSA_E_CANCELLED		equ (WSABASEERR+111)
WSAEREFUSED		equ (WSABASEERR+112)

;;
;; Error return codes from gethostbyname() and gethostbyaddr()
;; (when using the resolver). Note that these errors are
;; retrieved via WSAGetLastError() and must therefore follow
;; the rules for avoiding clashes with error numbers from
;; specific implementations or language run-time systems.
;; For this reason the codes are based at WSABASEERR+1001.
;; Note also that [WSA]NO_ADDRESS is defined only for
;; compatibility purposes.
;;

h_errno			equ <WSAGetLastError()>

;; Authoritative Answer: Host not found
WSAHOST_NOT_FOUND	equ (WSABASEERR+1001)
HOST_NOT_FOUND		equ WSAHOST_NOT_FOUND

;; Non-Authoritative: Host not found, or SERVERFAIL
WSATRY_AGAIN		equ (WSABASEERR+1002)
TRY_AGAIN		equ WSATRY_AGAIN

;; Non-recoverable errors, FORMERR, REFUSED, NOTIMP
WSANO_RECOVERY		equ (WSABASEERR+1003)
NO_RECOVERY		equ WSANO_RECOVERY

;; Valid name, no data record of requested type
WSANO_DATA		equ (WSABASEERR+1004)
NO_DATA			equ WSANO_DATA

;; no address, look for MX record
WSANO_ADDRESS		equ WSANO_DATA
NO_ADDRESS		equ WSANO_ADDRESS

;;
;; Define QOS related error return codes
;;
;;
WSA_QOS_RECEIVERS	equ (WSABASEERR + 1005)
;; at least one Reserve has arrived
WSA_QOS_SENDERS		equ (WSABASEERR + 1006)
;; at least one Path has arrived
WSA_QOS_NO_SENDERS	equ (WSABASEERR + 1007)
;; there are no senders
WSA_QOS_NO_RECEIVERS	equ (WSABASEERR + 1008)
;; there are no receivers
WSA_QOS_REQUEST_CONFIRMED equ (WSABASEERR + 1009)
;; Reserve has been confirmed
WSA_QOS_ADMISSION_FAILURE equ (WSABASEERR + 1010)
;; error due to lack of resources
WSA_QOS_POLICY_FAILURE	equ (WSABASEERR + 1011)
;; rejected for administrative reasons - bad credentials
WSA_QOS_BAD_STYLE	equ (WSABASEERR + 1012)
;; unknown or conflicting style
WSA_QOS_BAD_OBJECT	equ (WSABASEERR + 1013)
;; problem with some part of the filterspec or providerspecific
;; buffer in general
WSA_QOS_TRAFFIC_CTRL_ERROR equ (WSABASEERR + 1014)
;; problem with some part of the flowspec
WSA_QOS_GENERIC_ERROR	equ (WSABASEERR + 1015)
;; general error

;;
;; Windows Sockets errors redefined as regular Berkeley error constants.
;; These are commented out in Windows NT to avoid conflicts with errno.h.
;; Use the WSA constants instead.
;;
if 0
EWOULDBLOCK		equ WSAEWOULDBOCK
EINPROGRESS		equ WSAEINPROGRESS
EALREADY		equ WSAEAREADY
ENOTSOCK		equ WSAENOTSOCK
EDESTADDRREQ		equ WSAEDESTADDRREQ
EMSGSIZE		equ WSAEMSGSIZE
EPROTOTYPE		equ WSAEPROTOTYPE
ENOPROTOOPT		equ WSAENOPROTOOPT
EPROTONOSUPPORT		equ WSAEPROTONOSUPPORT
ESOCKTNOSUPPORT		equ WSAESOCKTNOSUPPORT
EOPNOTSUPP		equ WSAEOPNOTSUPP
EPFNOSUPPORT		equ WSAEPFNOSUPPORT
EAFNOSUPPORT		equ WSAEAFNOSUPPORT
EADDRINUSE		equ WSAEADDRINUSE
EADDRNOTAVAIL		equ WSAEADDRNOTAVAIL
ENETDOWN		equ WSAENETDOWN
ENETUNREACH		equ WSAENETUNREACH
ENETRESET		equ WSAENETRESET
ECONNABORTED		equ WSAECONNABORTED
ECONNRESET		equ WSAECONNRESET
ENOBUFS			equ WSAENOBUFS
EISCONN			equ WSAEISCONN
ENOTCONN		equ WSAENOTCONN
ESHUTDOWN		equ WSAESHUTDOWN
ETOOMANYREFS		equ WSAETOOMANYREFS
ETIMEDOUT		equ WSAETIMEDOUT
ECONNREFUSED		equ WSAECONNREFUSED
ELOOP			equ WSAEOOP
ENAMETOOLONG		equ WSAENAMETOOLONG
EHOSTDOWN		equ WSAEHOSTDOWN
EHOSTUNREACH		equ WSAEHOSTUNREACH
ENOTEMPTY		equ WSAENOTEMPTY
EPROCLIM		equ WSAEPROCIM
EUSERS			equ WSAEUSERS
EDQUOT			equ WSAEDQUOT
ESTALE			equ WSAESTAE
EREMOTE			equ WSAEREMOTE
endif

;;
;; WinSock 2 extension -- new error codes and type definition
;;

if defined(_WIN32) or defined(_WIN64)

WSAAPI			equ <>
WSAEVENT		equ <HANDLE>
LPWSAEVENT		equ <LPHANDE>
WSAOVERLAPPED		equ <OVERLAPPED>
LPWSAOVERLAPPED		typedef ptr OVERLAPPED

WSA_IO_PENDING		equ ERROR_IO_PENDING
WSA_IO_INCOMPLETE	equ ERROR_IO_INCOMPLETE
WSA_INVALID_HANDLE	equ ERROR_INVALID_HANDE
WSA_INVALID_PARAMETER	equ ERROR_INVAID_PARAMETER
WSA_NOT_ENOUGH_MEMORY	equ ERROR_NOT_ENOUGH_MEMORY
WSA_OPERATION_ABORTED	equ ERROR_OPERATION_ABORTED

WSA_INVALID_EVENT	equ 0
WSA_MAXIMUM_WAIT_EVENTS equ MAXIMUM_WAIT_OBJECTS
WSA_WAIT_FAILED		equ -1
WSA_WAIT_EVENT_0	equ WAIT_OBJECT_0
WSA_WAIT_IO_COMPLETION	equ WAIT_IO_COMPLETION
WSA_WAIT_TIMEOUT	equ WAIT_TIMEOUT
WSA_INFINITE		equ INFINITE

endif	;; WIN32

;;
;; WinSock 2 extension -- WSABUF and QOS struct, include qos.h
;; to pull in FLOWSPEC and related definitions
;;

WSABUF			STRUC
len			dd ?	;; the length of the buffer
buf			LPSTR ? ;; the pointer to the buffer
WSABUF			ENDS
LPWSABUF		typedef ptr WSABUF

include qos.inc
.xlist

QOS			STRUC
SendingFlowspec		FLOWSPEC <>	;; the flow spec for data sending
ReceivingFlowspec	FLOWSPEC <>	;; the flow spec for data receiving
ProviderSpecific	WSABUF <>	;; additional provider specific stuff
QOS			ENDS
LPQOS			typedef ptr QOS

;;
;; WinSock 2 extension -- manifest constants for return values of the condition function
;;
CF_ACCEPT		equ 0x0000
CF_REJECT		equ 0x0001
CF_DEFER		equ 0x0002

;;
;; WinSock 2 extension -- manifest constants for shutdown()
;;
SD_RECEIVE		equ 0x00
SD_SEND			equ 0x01
SD_BOTH			equ 0x02

;;
;; WinSock 2 extension -- data type and manifest constants for socket groups
;;
;GROUP			typedef UINT

SG_UNCONSTRAINED_GROUP	equ 0x01
SG_CONSTRAINED_GROUP	equ 0x02

;;
;; WinSock 2 extension -- data type for WSAEnumNetworkEvents()
;;
WSANETWORKEVENTS	STRUC
lNetworkEvents		LONG ?
iErrorCode		SINT FD_MAX_EVENTS dup(?)
WSANETWORKEVENTS	ENDS
LPWSANETWORKEVENTS	typedef ptr WSANETWORKEVENTS

;;
;; WinSock 2 extension -- WSAPROTOCOL_INFO structure and associated
;; manifest constants
;;

ifndef GUID_DEFINED
GUID_DEFINED		equ 1
GUID			STRUC
Data1			dd ?
Data2			dw ?
Data3			dw ?
Data4			db 8 dup(?)
GUID			ENDS
endif ;; GUID_DEFINED

ifndef __LPGUID_DEFINED__
__LPGUID_DEFINED__	equ 1
LPGUID			typedef ptr GUID
endif

MAX_PROTOCOL_CHAIN	equ 7

BASE_PROTOCOL		equ 1
LAYERED_PROTOCOL	equ 0

WSAPROTOCOLCHAIN	STRUC
ChainLen		SINT ?	;; the length of the chain,
;; length = 0 means layered protocol,
;; length = 1 means base protocol,
;; length > 1 means protocol chain
ChainEntries		dd MAX_PROTOCOL_CHAIN dup(?) ;; a list of dwCatalogEntryIds
WSAPROTOCOLCHAIN	ENDS
LPWSAPROTOCOLCHAIN	typedef ptr WSAPROTOCOLCHAIN

WSAPROTOCOL_LEN		equ 255

WSAPROTOCOL_INFOA	STRUC
dwServiceFlags1		dd ?
dwServiceFlags2		dd ?
dwServiceFlags3		dd ?
dwServiceFlags4		dd ?
dwProviderFlags		dd ?
ProviderId		GUID <>
dwCatalogEntryId	dd ?
ProtocolChain		WSAPROTOCOLCHAIN <>
iVersion		SINT ?
iAddressFamily		SINT ?
iMaxSockAddr		SINT ?
iMinSockAddr		SINT ?
iSocketType		SINT ?
iProtocol		SINT ?
iProtocolMaxOffset	SINT ?
iNetworkByteOrder	SINT ?
iSecurityScheme		SINT ?
dwMessageSize		dd ?
dwProviderReserved	dd ?
szProtocol		db WSAPROTOCOL_LEN+1 dup(?)
WSAPROTOCOL_INFOA	ENDS
 LPWSAPROTOCOL_INFOA	typedef ptr WSAPROTOCOL_INFOA
WSAPROTOCOL_INFOW	STRUC
dwServiceFlags1		dd ?
dwServiceFlags2		dd ?
dwServiceFlags3		dd ?
dwServiceFlags4		dd ?
dwProviderFlags		dd ?
ProviderId		GUID <>
dwCatalogEntryId	dd ?
ProtocolChain		WSAPROTOCOLCHAIN <>
iVersion		SINT ?
iAddressFamily		SINT ?
iMaxSockAddr		SINT ?
iMinSockAddr		SINT ?
iSocketType		SINT ?
iProtocol		SINT ?
iProtocolMaxOffset	SINT ?
iNetworkByteOrder	SINT ?
iSecurityScheme		SINT ?
dwMessageSize		dd ?
dwProviderReserved	dd ?
szProtocol		dw WSAPROTOCOL_LEN+1 dup(?)
WSAPROTOCOL_INFOW	ENDS
 LPWSAPROTOCOL_INFOW	typedef ptr WSAPROTOCOL_INFOW
ifdef _UNICODE
WSAPROTOCOL_INFO	typedef WSAPROTOCOL_INFOW
LPWSAPROTOCOL_INFO	typedef LPWSAPROTOCOL_INFOW
else
WSAPROTOCOL_INFO	typedef WSAPROTOCOL_INFOA
LPWSAPROTOCOL_INFO	typedef LPWSAPROTOCOL_INFOA
endif ;; UNICODE

;; Flag bit definitions for dwProviderFlags
PFL_MULTIPLE_PROTO_ENTRIES	equ 0x00000001
PFL_RECOMMENDED_PROTO_ENTRY	equ 0x00000002
PFL_HIDDEN			equ 0x00000004
PFL_MATCHES_PROTOCOL_ZERO	equ 0x00000008

;; Flag bit definitions for dwServiceFlags1
XP1_CONNECTIONLESS	equ 0x00000001
XP1_GUARANTEED_DELIVERY equ 0x00000002
XP1_GUARANTEED_ORDER	equ 0x00000004
XP1_MESSAGE_ORIENTED	equ 0x00000008
XP1_PSEUDO_STREAM	equ 0x00000010
XP1_GRACEFUL_CLOSE	equ 0x00000020
XP1_EXPEDITED_DATA	equ 0x00000040
XP1_CONNECT_DATA	equ 0x00000080
XP1_DISCONNECT_DATA	equ 0x00000100
XP1_SUPPORT_BROADCAST	equ 0x00000200
XP1_SUPPORT_MULTIPOINT	equ 0x00000400
XP1_MULTIPOINT_CONTROL_PLANE equ 0x00000800
XP1_MULTIPOINT_DATA_PLANE equ 0x00001000
XP1_QOS_SUPPORTED	equ 0x00002000
XP1_INTERRUPT		equ 0x00004000
XP1_UNI_SEND		equ 0x00008000
XP1_UNI_RECV		equ 0x00010000
XP1_IFS_HANDLES		equ 0x00020000
XP1_PARTIAL_MESSAGE	equ 0x00040000

BIGENDIAN		equ 0x0000
LITTLEENDIAN		equ 0x0001

SECURITY_PROTOCOL_NONE	equ 0x0000

;;
;; WinSock 2 extension -- manifest constants for WSAJoinLeaf()
;;
JL_SENDER_ONLY		equ 0x01
JL_RECEIVER_ONLY	equ 0x02
JL_BOTH			equ 0x04

;;
;; WinSock 2 extension -- manifest constants for WSASocket()
;;
WSA_FLAG_OVERLAPPED	equ 0x01
WSA_FLAG_MULTIPOINT_C_ROOT equ 0x02
WSA_FLAG_MULTIPOINT_C_LEAF equ 0x04
WSA_FLAG_MULTIPOINT_D_ROOT equ 0x08
WSA_FLAG_MULTIPOINT_D_LEAF equ 0x10

;;
;; WinSock 2 extension -- manifest constants for WSAIoctl()
;;
IOC_UNIX		equ 0x00000000
IOC_WS2			equ 0x08000000
IOC_PROTOCOL		equ 0x10000000
IOC_VENDOR		equ 0x18000000

_WSAIO macro x,y
	exitm<(IOC_VOID OR (x) OR (y))>
	endm
_WSAIOR macro x,y
	exitm<(IOC_OUT OR (x) OR (y))>
	endm
_WSAIOW macro x,y
	exitm<(IOC_IN OR (x) OR (y))>
	endm
_WSAIORW macro x,y
	exitm<(IOC_INOUT OR (x) OR (y))>
	endm

SIO_ASSOCIATE_HANDLE	equ _WSAIOW(IOC_WS2,1)
SIO_ENABLE_CIRCULAR_QUEUEING equ _WSAIO(IOC_WS2,2)
SIO_FIND_ROUTE		equ _WSAIOR(IOC_WS2,3)
SIO_FLUSH		equ _WSAIO(IOC_WS2,4)
SIO_GET_BROADCAST_ADDRESS equ _WSAIOR(IOC_WS2,5)
SIO_GET_EXTENSION_FUNCTION_POINTER equ _WSAIORW(IOC_WS2,6)
SIO_GET_QOS		equ _WSAIORW(IOC_WS2,7)
SIO_GET_GROUP_QOS	equ _WSAIORW(IOC_WS2,8)
SIO_MULTIPOINT_LOOPBACK equ _WSAIOW(IOC_WS2,9)
SIO_MULTICAST_SCOPE	equ _WSAIOW(IOC_WS2,10)
SIO_SET_QOS		equ _WSAIOW(IOC_WS2,11)
SIO_SET_GROUP_QOS	equ _WSAIOW(IOC_WS2,12)
SIO_TRANSLATE_HANDLE	equ _WSAIORW(IOC_WS2,13)
SIO_ROUTING_INTERFACE_QUERY equ _WSAIORW(IOC_WS2,20)
SIO_ROUTING_INTERFACE_CHANGE equ _WSAIOW(IOC_WS2,21)
SIO_ADDRESS_LIST_QUERY	equ _WSAIOR(IOC_WS2,22)
SIO_ADDRESS_LIST_CHANGE equ _WSAIO(IOC_WS2,23)
SIO_QUERY_TARGET_PNP_HANDLE equ _WSAIOR(IOC_W32,24)

;;
;; WinSock 2 extension -- manifest constants for SIO_TRANSLATE_HANDLE ioctl
;;
TH_NETDEV		equ 0x00000001
TH_TAPI			equ 0x00000002


;;
;; Microsoft Windows Extended data types required for the functions to
;; convert   back  and	forth  between	binary	and  string  forms  of
;; addresses.
;;
;sockaddr SOCKADDR;	STRUC
PSOCKADDR		typedef ptr ; STRUC
LPSOCKADDR		typedef ptr ;	STRUC

;;
;; Manifest constants and type definitions related to name resolution and
;; registration (RNR) API
;;

ifndef _tagBLOB_DEFINED
_tagBLOB_DEFINED	equ 1
_BLOB_DEFINED		equ 1
_LPBLOB_DEFINED		equ 1
BLOB			STRUC
cbSize			ULONG ?
ifdef MIDL_PASS
pBlobData		LPBYTE size_is(cbSize) dup(?)
else  ;; MIDL_PASS
pBlobData		LPSTR ?
endif ;; MIDL_PASS
BLOB			ENDS
LPBLOB			typedef ptr BLOB
endif

;;
;; Service Install Flags
;;

SERVICE_MULTIPLE	equ (0x00000001)

;;
;;& Name Spaces
;;

NS_ALL			equ (0)

NS_SAP			equ (1)
NS_NDS			equ (2)
NS_PEER_BROWSE		equ (3)

NS_TCPIP_LOCAL		equ (10)
NS_TCPIP_HOSTS		equ (11)
NS_DNS			equ (12)
NS_NETBT		equ (13)
NS_WINS			equ (14)

NS_NBP			equ (20)

NS_MS			equ (30)
NS_STDA			equ (31)
NS_NTDS			equ (32)

NS_X500			equ (40)
NS_NIS			equ (41)
NS_NISPLUS		equ (42)

NS_WRQ			equ (50)

;;
;; Resolution flags for WSAGetAddressByName().
;; Note these are also used by the 1.1 API GetAddressByName, so
;; leave them around.
;;
RES_UNUSED_1		equ (0x00000001)
RES_FLUSH_CACHE		equ (0x00000002)
ifndef RES_SERVICE
RES_SERVICE		equ (0x00000004)
endif ;; RES_SERVICE

;;
;; Well known value names for Service Types
;;

SERVICE_TYPE_VALUE_IPXPORTA equ <"IpxSocket">
SERVICE_TYPE_VALUE_IPXPORTW equ <"IpxSocket">
SERVICE_TYPE_VALUE_SAPIDA   equ <"SapId">
SERVICE_TYPE_VALUE_SAPIDW   equ <"SapId">

SERVICE_TYPE_VALUE_TCPPORTA equ <"TcpPort">
SERVICE_TYPE_VALUE_TCPPORTW equ <"TcpPort">

SERVICE_TYPE_VALUE_UDPPORTA equ <"UdpPort">
SERVICE_TYPE_VALUE_UDPPORTW equ <"UdpPort">

SERVICE_TYPE_VALUE_OBJECTIDA equ <"ObjectId">
SERVICE_TYPE_VALUE_OBJECTIDW equ <"ObjectId">

ifdef _UNICODE

SERVICE_TYPE_VALUE_SAPID equ SERVICE_TYPE_VAUE_SAPIDW
SERVICE_TYPE_VALUE_TCPPORT equ SERVICE_TYPE_VAUE_TCPPORTW
SERVICE_TYPE_VALUE_UDPPORT equ SERVICE_TYPE_VAUE_UDPPORTW
SERVICE_TYPE_VALUE_OBJECTID equ SERVICE_TYPE_VAUE_OBJECTIDW

else ;; not UNICODE

SERVICE_TYPE_VALUE_SAPID equ SERVICE_TYPE_VAUE_SAPIDA
SERVICE_TYPE_VALUE_TCPPORT equ SERVICE_TYPE_VAUE_TCPPORTA
SERVICE_TYPE_VALUE_UDPPORT equ SERVICE_TYPE_VAUE_UDPPORTA
SERVICE_TYPE_VALUE_OBJECTID equ SERVICE_TYPE_VAUE_OBJECTIDA

endif

ifndef __CSADDR_DEFINED__
__CSADDR_DEFINED__ equ 1


;;
;; SockAddr Information
;;
SOCKET_ADDRESS		STRUC
lpSockaddr		LPSOCKADDR ?
iSockaddrLength		SINT ?
SOCKET_ADDRESS		ENDS
PSOCKET_ADDRESS		typedef ptr SOCKET_ADDRESS
LPSOCKET_ADDRESS	typedef ptr SOCKET_ADDRESS

;;
;; CSAddr Information
;;
CSADDR_INFO		STRUC
LocalAddr		SOCKET_ADDRESS <>
RemoteAddr		SOCKET_ADDRESS <>
iSocketType		SINT ?
iProtocol		SINT ?
CSADDR_INFO		ENDS
PCSADDR_INFO		typedef ptr CSADDR_INFO
LPCSADDR_INFO		typedef ptr CSADDR_INFO
endif ;; __CSADDR_DEFINED__

;;
;; Address list returned via SIO_ADDRESS_LIST_QUERY
;;
SOCKET_ADDRESS_LIST	STRUC
iAddressCount		SINT ?
Address			SOCKET_ADDRESS <>
SOCKET_ADDRESS_LIST	ENDS
LPSOCKET_ADDRESS_LIST	typedef ptr SOCKET_ADDRESS_LIST

;;
;;  Address Family/Protocol Tuples
;;
AFPROTOCOLS		STRUC
iAddressFamily		SINT ?
iProtocol		SINT ?
AFPROTOCOLS		ENDS
PAFPROTOCOLS		typedef ptr AFPROTOCOLS
LPAFPROTOCOLS		typedef ptr AFPROTOCOLS

;;
;; Client Query API Typedefs
;;

;;
;; The comparators
;;
;typedef enum _WSAEcomparator
COMP_EQUAL		equ 0
COMP_NOTLESS		equ 1
WSAECOMPARATOR		typedef LONG
PWSAECOMPARATOR		typedef ptr WSAECOMPARATOR
LPWSAECOMPARATOR	typedef ptr WSAECOMPARATOR

WSAVERSION		STRUC
dwVersion		dd ?
ecHow			WSAECOMPARATOR ?
WSAVERSION		ENDS
PWSAVERSION		typedef ptr WSAVERSION
LPWSAVERSION		typedef ptr WSAVERSION

WSAQUERYSETA		STRUC
dwSize			dd ?
lpszServiceInstanceName LPSTR ?
lpServiceClassId	LPGUID ?
lpVersion		LPWSAVERSION ?
lpszComment		LPSTR ?
dwNameSpace		dd ?
lpNSProviderId		LPGUID ?
lpszContext		LPSTR ?
dwNumberOfProtocols	dd ?
lpafpProtocols		LPAFPROTOCOLS ?
lpszQueryString		LPSTR ?
dwNumberOfCsAddrs	dd ?
lpcsaBuffer		LPCSADDR_INFO ?
dwOutputFlags		dd ?
lpBlob			LPBLOB ?
WSAQUERYSETA		ENDS
PWSAQUERYSETA		typedef ptr WSAQUERYSETA
LPWSAQUERYSETA		typedef ptr WSAQUERYSETA

WSAQUERYSETW		STRUC
dwSize			dd ?
lpszServiceInstanceName LPWSTR ?
lpServiceClassId	LPGUID ?
lpVersion		LPWSAVERSION ?
lpszComment		LPWSTR ?
dwNameSpace		dd ?
lpNSProviderId		LPGUID ?
lpszContext		LPWSTR ?
dwNumberOfProtocols	dd ?
lpafpProtocols		LPAFPROTOCOLS ?
lpszQueryString		LPWSTR ?
dwNumberOfCsAddrs	dd ?
lpcsaBuffer		LPCSADDR_INFO ?
dwOutputFlags		dd ?
lpBlob			LPBLOB ?
WSAQUERYSETW		ENDS
PWSAQUERYSETW		typedef ptr WSAQUERYSETW
LPWSAQUERYSETW		typedef ptr WSAQUERYSETW
ifdef _UNICODE
WSAQUERYSET		typedef WSAQUERYSETW
PWSAQUERYSET		typedef PWSAQUERYSETW
LPWSAQUERYSET		typedef LPWSAQUERYSETW
else
WSAQUERYSET		typedef WSAQUERYSETA
PWSAQUERYSET		typedef PWSAQUERYSETA
LPWSAQUERYSET		typedef LPWSAQUERYSETA
endif ;; UNICODE

LUP_DEEP		equ 0x0001
LUP_CONTAINERS		equ 0x0002
LUP_NOCONTAINERS	equ 0x0004
LUP_NEAREST		equ 0x0008
LUP_RETURN_NAME		equ 0x0010
LUP_RETURN_TYPE		equ 0x0020
LUP_RETURN_VERSION	equ 0x0040
LUP_RETURN_COMMENT	equ 0x0080
LUP_RETURN_ADDR		equ 0x0100
LUP_RETURN_BLOB		equ 0x0200
LUP_RETURN_ALIASES	equ 0x0400
LUP_RETURN_QUERY_STRING equ 0x0800
LUP_RETURN_ALL		equ 0x0FF0
LUP_RES_SERVICE		equ 0x8000

LUP_FLUSHCACHE		equ 0x1000
LUP_FLUSHPREVIOUS	equ 0x2000


;;
;; Return flags
;;

RESULT_IS_ALIAS		equ 0x0001

;;
;; Service Address Registration and Deregistration Data Types.
;;
;typedef enum _WSAESETSERVICEOP

RNRSERVICE_REGISTER	equ 0
RNRSERVICE_DEREGISTER	equ 1
RNRSERVICE_DELETE	equ 2
WSAESETSERVICEOP	typedef LONG
PWSAESETSERVICEOP	typedef ptr WSAESETSERVICEOP
LPWSAESETSERVICEOP	typedef ptr WSAESETSERVICEOP
;;
;; Service Installation/Removal Data Types.
;;

WSANSCLASSINFOA		STRUC
lpszName		LPSTR ?
dwNameSpace		dd ?
dwValueType		dd ?
dwValueSize		dd ?
lpValue			LPVOID ?
WSANSCLASSINFOA		ENDS
PWSANSCLASSINFOA	typedef ptr WSANSCLASSINFOA
LPWSANSCLASSINFOA	typedef ptr WSANSCLASSINFOA
WSANSCLASSINFOW		STRUC
lpszName		LPWSTR ?
dwNameSpace		dd ?
dwValueType		dd ?
dwValueSize		dd ?
lpValue			LPVOID ?
WSANSCLASSINFOW		ENDS
PWSANSCLASSINFOW	typedef ptr WSANSCLASSINFOW
LPWSANSCLASSINFOW	typedef ptr WSANSCLASSINFOW
ifdef _UNICODE
WSANSCLASSINFO		typedef WSANSCLASSINFOW
PWSANSCLASSINFO		typedef PWSANSCLASSINFOW
LPWSANSCLASSINFO	typedef LPWSANSCLASSINFOW
else
WSANSCLASSINFO		typedef WSANSCLASSINFOA
PWSANSCLASSINFO		typedef PWSANSCLASSINFOA
LPWSANSCLASSINFO	typedef LPWSANSCLASSINFOA
endif ;; UNICODE

WSASERVICECLASSINFOA	STRUC
lpServiceClassId	LPGUID ?
lpszServiceClassName	LPSTR ?
dwCount			dd ?
lpClassInfos		LPWSANSCLASSINFOA ?
WSASERVICECLASSINFOA	ENDS
PWSASERVICECLASSINFOA	typedef ptr WSASERVICECLASSINFOA
LPWSASERVICECLASSINFOA	typedef ptr WSASERVICECLASSINFOA
WSASERVICECLASSINFOW	STRUC
lpServiceClassId	LPGUID ?
lpszServiceClassName	LPWSTR ?
dwCount			dd ?
lpClassInfos		LPWSANSCLASSINFOW ?
WSASERVICECLASSINFOW	ENDS
PWSASERVICECLASSINFOW	typedef ptr WSASERVICECLASSINFOW
LPWSASERVICECLASSINFOW	typedef ptr WSASERVICECLASSINFOW
ifdef _UNICODE
WSASERVICECLASSINFO	typedef WSASERVICECLASSINFOW
PWSASERVICECLASSINFO	typedef PWSASERVICECLASSINFOW
LPWSASERVICECLASSINFO	typedef LPWSASERVICECLASSINFOW
else
WSASERVICECLASSINFO	typedef WSASERVICECLASSINFOA
PWSASERVICECLASSINFO	typedef PWSASERVICECLASSINFOA
LPWSASERVICECLASSINFO	typedef LPWSASERVICECLASSINFOA
endif ;; UNICODE

WSANAMESPACE_INFOA	STRUC
NSProviderId		GUID <>
dwNameSpace		dd ?
fActive			BOOL ?
dwVersion		dd ?
lpszIdentifier		LPSTR ?
WSANAMESPACE_INFOA	ENDS
PWSANAMESPACE_INFOA	typedef ptr WSANAMESPACE_INFOA
LPWSANAMESPACE_INFOA	typedef ptr WSANAMESPACE_INFOA
WSANAMESPACE_INFOW	STRUC
NSProviderId		GUID <>
dwNameSpace		dd ?
fActive			BOOL ?
dwVersion		dd ?
lpszIdentifier		LPWSTR ?
WSANAMESPACE_INFOW	ENDS
PWSANAMESPACE_INFOW	typedef ptr WSANAMESPACE_INFOW
LPWSANAMESPACE_INFOW	typedef ptr WSANAMESPACE_INFOW
ifdef _UNICODE
WSANAMESPACE_INFO	typedef WSANAMESPACE_INFOW
PWSANAMESPACE_INFO	typedef PWSANAMESPACE_INFOW
LPWSANAMESPACE_INFO	typedef LPWSANAMESPACE_INFOW
else
WSANAMESPACE_INFO	typedef WSANAMESPACE_INFOA
PWSANAMESPACE_INFO	typedef PWSANAMESPACE_INFOA
LPWSANAMESPACE_INFO	typedef LPWSANAMESPACE_INFOA
endif ;; UNICODE

;; Socket function prototypes

if INCL_WINSOCK_API_PROTOTYPES
;SOCKET
accept proto _CType \
		     s: SOCKET,
		 _addr: PVOID,
	       addrlen: ptr SINT
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_ACCEPT_T typedef proto _CType \
		     s: SOCKET,
		 _addr: PVOID,
	       addrlen: ptr SINT
LPFN_ACCEPT	typedef ptr LPFN_ACCEPT_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;int
bind proto _CType \
		     s: SOCKET,
		 _name: PVOID,
	       namelen: SINT
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_BIND_T typedef proto _CType \
		     s: SOCKET,
		 _name: PVOID,
	       namelen: SINT
LPFN_BIND	typedef ptr LPFN_BIND_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;int
closesocket proto _CType \
		     s: SOCKET
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_CLOSESOCKET_T typedef proto _CType \
		     s: SOCKET
LPFN_CLOSESOCKET typedef ptr LPFN_CLOSESOCKET_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;int
connect proto _CType \
		     s: SOCKET,
		 _name: PVOID,
	       namelen: SINT
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_CONNECT_T typedef proto _CType \
		     s: SOCKET,
		 _name: PVOID,
	       namelen: SINT
LPFN_CONNECT	typedef ptr LPFN_CONNECT_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;int
ioctlsocket proto _CType \
		     s: SOCKET,
		   cmd: LONG,
		  argp: LPDWORD
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_IOCTLSOCKET_T typedef proto _CType \
		     s: SOCKET,
		   cmd: LONG,
		  argp: LPDWORD
LPFN_IOCTLSOCKET typedef ptr LPFN_IOCTLSOCKET_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;int
getpeername proto _CType \
		     s: SOCKET,
		 _name: PVOID,
	       namelen: ptr SINT
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_GETPEERNAME_T typedef proto _CType \
		     s: SOCKET,
		 _name: PVOID,
	       namelen: ptr SINT
LPFN_GETPEERNAME typedef ptr LPFN_GETPEERNAME_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;int
getsockname proto _CType \
		     s: SOCKET,
		 _name: PVOID,
	       namelen: ptr SINT
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_GETSOCKNAME_T typedef proto _CType \
		     s: SOCKET,
		 _name: PVOID,
	       namelen: ptr SINT
LPFN_GETSOCKNAME typedef ptr LPFN_GETSOCKNAME_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;int
getsockopt proto _CType \
		     s: SOCKET,
		 level: SINT,
	       optname: SINT,
		optval: LPSTR,
		optlen: ptr SINT
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_GETSOCKOPT_T typedef proto _CType \
		     s: SOCKET,
		 level: SINT,
	       optname: SINT,
		optval: LPSTR,
		optlen: ptr SINT
LPFN_GETSOCKOPT typedef ptr LPFN_GETSOCKOPT_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;DWORD
htonl proto _CType \
	      hostlong: DWORD
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_HTONL_T typedef proto _CType \
	      hostlong: DWORD
LPFN_HTONL typedef ptr LPFN_HTONL_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;WORD
htons proto _CType \
	     hostshort: WORD
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_HTONS_T typedef proto _CType \
	     hostshort: WORD
LPFN_HTONS typedef ptr LPFN_HTONS_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;DWORD
inet_addr proto _CType \
		    cp: LPSTR
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_INET_ADDR_T typedef proto _CType \
		    cp: LPSTR
LPFN_INET_ADDR	typedef ptr LPFN_INET_ADDR_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;LPSTR
inet_ntoa proto _CType \
		      : in_addr
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_INET_NTOA_T typedef proto _CType \
		      : in_addr
LPFN_INET_NTOA typedef ptr LPFN_INET_NTOA_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;int
listen proto _CType \
		     s: SOCKET,
	       backlog: SINT
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_LISTEN_T typedef proto _CType \
		     s: SOCKET,
	       backlog: SINT
LPFN_LISTEN typedef ptr LPFN_LISTEN_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;DWORD
ntohl proto _CType \
	       netlong: DWORD
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_NTOHL_T typedef proto _CType \
	       netlong: DWORD
LPFN_NTOHL typedef ptr LPFN_NTOHL_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;WORD
ntohs proto _CType \
	      netshort: WORD
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_NTOHS_T typedef proto _CType \
	      netshort: WORD
LPFN_NTOHS typedef ptr LPFN_NTOHS_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;int
recv proto _CType \
		     s: SOCKET,
		   buf: LPSTR,
		   len: SINT,
		 flags: SINT
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_RECV_T typedef proto _CType \
		     s: SOCKET,
		   buf: LPSTR,
		   len: SINT,
		 flags: SINT
LPFN_RECV typedef ptr LPFN_RECV_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;int
recvfrom proto _CType \
		     s: SOCKET,
		   buf: LPSTR,
		   len: SINT,
		 flags: SINT,
		  from: PVOID,
	       fromlen: ptr SINT
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_RECVFROM_T typedef proto _CType \
		     s: SOCKET,
		   buf: LPSTR,
		   len: SINT,
		 flags: SINT,
		  from: PVOID,
	       fromlen: ptr SINT
LPFN_RECVFROM typedef ptr LPFN_RECVFROM_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;int
select proto _CType \
		  nfds: SINT,
	       readfds: ptr fd_set,
	      writefds: ptr fd_set,
	     exceptfds: ptr fd_set,
	       timeout: ptr ;struct timeval *
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_SELECT_T typedef proto _CType \
		  nfds: SINT,
	       readfds: ptr fd_set,
	      writefds: ptr fd_set,
	     exceptfds: ptr fd_set,
	       timeout: ptr ;struct timeval *
LPFN_SELECT	typedef ptr LPFN_SELECT_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;int
send proto _CType \
		     s: SOCKET,
		   buf: LPSTR,
		   len: SINT,
		 flags: SINT
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_SEND_T typedef proto _CType \
		     s: SOCKET,
		   buf: LPSTR,
		   len: SINT,
		 flags: SINT
LPFN_SEND	typedef ptr LPFN_SEND_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;int
sendto proto _CType \
		     s: SOCKET,
		   buf: LPSTR,
		   len: SINT,
		 flags: SINT,
		    to: PVOID,
		 tolen: SINT
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_SENDTO_T typedef proto _CType \
		     s: SOCKET,
		   buf: LPSTR,
		   len: SINT,
		 flags: SINT,
		    to: PVOID,
		 tolen: SINT
LPFN_SENDTO	typedef ptr LPFN_SENDTO_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;int
setsockopt proto _CType \
		     s: SOCKET,
		 level: SINT,
	       optname: SINT,
		optval: LPSTR,
		optlen: SINT
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_SETSOCKOPT_T typedef proto _CType \
		     s: SOCKET,
		 level: SINT,
	       optname: SINT,
		optval: LPSTR,
		optlen: SINT
LPFN_SETSOCKOPT typedef ptr LPFN_SETSOCKOPT_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;int
shutdown proto _CType \
		     s: SOCKET,
		   how: SINT
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_SHUTDOWN_T typedef proto _CType \
		     s: SOCKET,
		   how: SINT
LPFN_SHUTDOWN	typedef ptr LPFN_SHUTDOWN_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;SOCKET
socket proto _CType \
		    af: SINT,
		 _type: SINT,
	      protocol: SINT
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_SOCKET_T typedef proto _CType \
		    af: SINT,
		 _type: SINT,
	      protocol: SINT
LPFN_SOCKET	typedef ptr LPFN_SOCKET_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

;; Database function prototypes

if INCL_WINSOCK_API_PROTOTYPES
;PVOID
gethostbyaddr proto _CType \
		 _addr: LPSTR,
		   len: SINT,
		 _type: SINT
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_GETHOSTBYADDR_T typedef proto _CType \
		 _addr: LPSTR,
		   len: SINT,
		 _type: SINT
LPFN_GETHOSTBYADDR typedef ptr LPFN_GETHOSTBYADDR_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;PVOID
gethostbyname proto _CType \
		 _name: LPSTR
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_GETHOSTBYNAME_T typedef proto _CType \
		 _name: LPSTR
LPFN_GETHOSTBYNAME typedef ptr LPFN_GETHOSTBYNAME_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;int
gethostname proto _CType \
		 _name: LPSTR,
	       namelen: SINT
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_GETHOSTNAME_T typedef proto _CType \
		 _name: LPSTR,
	       namelen: SINT
LPFN_GETHOSTNAME typedef ptr LPFN_GETHOSTNAME_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;struct
getservbyport proto _CType \
		  port: SINT,
		_proto: LPSTR
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_GETSERVBYPORT_T typedef proto _CType \
		  port: SINT,
		_proto: LPSTR
LPFN_GETSERVBYPORT typedef ptr LPFN_GETSERVBYPORT_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;struct
getservbyname proto _CType \
		 _name: LPSTR,
		_proto: LPSTR
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_GETSERVBYNAME_T typedef proto _CType \
		 _name: LPSTR,
		_proto: LPSTR
LPFN_GETSERVBYNAME typedef ptr LPFN_GETSERVBYNAME_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;struct
getprotobynumber proto _CType \
		number: SINT
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_GETPROTOBYNUMBER_T typedef proto _CType \
		number: SINT
LPFN_GETPROTOBYNUMBER typedef ptr LPFN_GETPROTOBYNUMBER_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;struct
getprotobyname proto _CType \
		 _name: LPSTR
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_GETPROTOBYNAME_T typedef proto _CType \
		 _name: LPSTR
LPFN_GETPROTOBYNAME typedef ptr LPFN_GETPROTOBYNAME_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

;; Microsoft Windows Extension function prototypes

if INCL_WINSOCK_API_PROTOTYPES
;int
WSAStartup proto _CType \
     wVersionRequested: WORD,
	     lpWSAData: LPWSADATA
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_WSASTARTUP_T typedef proto _CType \
     wVersionRequested: WORD,
	     lpWSAData: LPWSADATA
LPFN_WSASTARTUP typedef ptr LPFN_WSASTARTUP_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;int
WSACleanup proto _CType
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_WSACLEANUP_T typedef proto _CType
LPFN_WSACLEANUP typedef ptr LPFN_WSACLEANUP_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;void
WSASetLastError proto _CType \
		iError: SINT
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_WSASETLASTERROR_T typedef proto _CType \
		iError: SINT
LPFN_WSASETLASTERROR typedef ptr LPFN_WSASETLASTERROR_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;int
WSAGetLastError proto _CType
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_WSAGETLASTERROR_T typedef proto _CType
LPFN_WSAGETLASTERROR typedef ptr LPFN_WSAGETLASTERROR_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;BOOL
WSAIsBlocking proto _CType
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_WSAISBLOCKING_T typedef proto _CType
LPFN_WSAISBLOCKING typedef ptr LPFN_WSAISBLOCKING_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;int
WSAUnhookBlockingHook proto _CType
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_WSAUNHOOKBLOCKINGHOOK_T typedef proto _CType
LPFN_WSAUNHOOKBLOCKINGHOOK typedef ptr LPFN_WSAUNHOOKBLOCKINGHOOK_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;FARPROC
WSASetBlockingHook proto _CType \
	   lpBlockFunc: FARPROC
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_WSASETBLOCKINGHOOK_T typedef proto _CType \
	   lpBlockFunc: FARPROC
LPFN_WSASETBLOCKINGHOOK typedef ptr LPFN_WSASETBLOCKINGHOOK_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;int
WSACancelBlockingCall proto _CType
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_WSACANCELBLOCKINGCALL_T typedef proto _CType
LPFN_WSACANCELBLOCKINGCALL typedef ptr LPFN_WSACANCELBLOCKINGCALL_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;HANDLE
WSAAsyncGetServByName proto _CType \
		  hWnd: HWND,
		  wMsg: UINT,
		 _name: LPSTR,
		_proto: LPSTR,
		   buf: LPSTR,
		buflen: SINT
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_WSAASYNCGETSERVBYNAME_T typedef proto _CType \
		  hWnd: HWND,
		  wMsg: UINT,
		  name: LPSTR,
		_proto: LPSTR,
		   buf: LPSTR,
		buflen: SINT
LPFN_WSAASYNCGETSERVBYNAME typedef ptr LPFN_WSAASYNCGETSERVBYNAME_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;HANDLE
WSAAsyncGetServByPort proto _CType \
		  hWnd: HWND,
		  wMsg: UINT,
		  port: SINT,
		_proto: LPSTR,
		   buf: LPSTR,
		buflen: SINT
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_WSAASYNCGETSERVBYPORT_T typedef proto _CType \
		  hWnd: HWND,
		  wMsg: UINT,
		  port: SINT,
		_proto: LPSTR,
		   buf: LPSTR,
		buflen: SINT
LPFN_WSAASYNCGETSERVBYPORT typedef ptr LPFN_WSAASYNCGETSERVBYPORT_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;HANDLE
WSAAsyncGetProtoByName proto _CType \
		  hWnd: HWND,
		  wMsg: UINT,
		 _name: LPSTR,
		   buf: LPSTR,
		buflen: SINT
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_WSAASYNCGETPROTOBYNAME_T typedef proto _CType \
		  hWnd: HWND,
		  wMsg: UINT,
		 _name: LPSTR,
		   buf: LPSTR,
		buflen: SINT
LPFN_WSAASYNCGETPROTOBYNAME typedef ptr LPFN_WSAASYNCGETPROTOBYNAME_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;HANDLE
WSAAsyncGetProtoByNumber proto _CType \
		  hWnd: HWND,
		  wMsg: UINT,
		number: SINT,
		   buf: LPSTR,
		buflen: SINT
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_WSAASYNCGETPROTOBYNUMBER_T typedef proto _CType \
		  hWnd: HWND,
		  wMsg: UINT,
		number: SINT,
		   buf: LPSTR,
		buflen: SINT
LPFN_WSAASYNCGETPROTOBYNUMBER typedef ptr LPFN_WSAASYNCGETPROTOBYNUMBER_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;HANDLE
WSAAsyncGetHostByName proto _CType \
		  hWnd: HWND,
		  wMsg: UINT,
		 _name: LPSTR,
		   buf: LPSTR,
		buflen: SINT
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_WSAASYNCGETHOSTBYNAME_T typedef proto _CType \
		  hWnd: HWND,
		  wMsg: UINT,
		 _name: LPSTR,
		   buf: LPSTR,
		buflen: SINT
LPFN_WSAASYNCGETHOSTBYNAME typedef ptr LPFN_WSAASYNCGETHOSTBYNAME_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;HANDLE
WSAAsyncGetHostByAddr proto _CType \
		  hWnd: HWND,
		  wMsg: UINT,
		 _addr: LPSTR,
		   len: SINT,
		 _type: SINT,
		   buf: LPSTR,
		buflen: SINT
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_WSAASYNCGETHOSTBYADDR_T typedef proto _CType \
		  hWnd: HWND,
		  wMsg: UINT,
		  addr: LPSTR,
		   len: SINT,
		 _type: SINT,
		   buf: LPSTR,
		buflen: SINT
LPFN_WSAASYNCGETHOSTBYADDR typedef ptr LPFN_WSAASYNCGETHOSTBYADDR_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;int
WSACancelAsyncRequest proto _CType \
      hAsyncTaskHandle: HANDLE
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_WSACANCELASYNCREQUEST_T typedef proto _CType \
      hAsyncTaskHandle: HANDLE
LPFN_WSACANCELASYNCREQUEST typedef ptr LPFN_WSACANCELASYNCREQUEST_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;int
WSAAsyncSelect proto _CType \
		     s: SOCKET,
		  hWnd: HWND,
		  wMsg: UINT,
		lEvent: LONG
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_WSAASYNCSELECT_T typedef proto _CType \
		     s: SOCKET,
		  hWnd: HWND,
		  wMsg: UINT,
		lEvent: LONG
LPFN_WSAASYNCSELECT typedef ptr LPFN_WSAASYNCSELECT_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

;;
;; WinSock 2 extensions -- data types for the condition function in
;; WSAAccept() and overlapped I/O completion routine.
;;
LPCONDITIONPROC_T typedef proto _CType \
	    lpCallerId: LPWSABUF,
	  lpCallerData: LPWSABUF,
		lpSQOS: LPQOS,
		lpGQOS: LPQOS,
	    lpCalleeId: LPWSABUF,
	  lpCalleeData: LPWSABUF,
		     g: ptr UINT,
	dwCallbackData: DWORD
LPCONDITIONPROC typedef ptr LPCONDITIONPROC_T

LPWSAOVERLAPPED_COMPLETION_ROUTINE_T typedef proto _CType \
	       dwError: DWORD,
	 cbTransferred: DWORD,
	  lpOverlapped: LPWSAOVERLAPPED,
	       dwFlags: DWORD
LPWSAOVERLAPPED_COMPLETION_ROUTINE typedef ptr LPWSAOVERLAPPED_COMPLETION_ROUTINE_T
;; WinSock 2 API new function prototypes

if INCL_WINSOCK_API_PROTOTYPES
;SOCKET
WSAAccept proto _CType \
		     s: SOCKET,
		 _addr: PVOID,
	       addrlen: LPINT,
	 lpfnCondition: LPCONDITIONPROC,
	dwCallbackData: DWORD
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
WSAAccept proto _CType \
		     s: SOCKET,
		 _addr: PVOID,
	       addrlen: LPINT,
	 lpfnCondition: LPCONDITIONPROC,
	dwCallbackData: DWORD
LPFN_WSAACCEPT typedef ptr LPFN_WSAACCEPT_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;BOOL
WSACloseEvent proto _CType \
		hEvent: WSAEVENT
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_WSACLOSEEVENT_T typedef proto _CType \
		hEvent: WSAEVENT
LPFN_WSACLOSEEVENT typedef ptr LPFN_WSACLOSEEVENT_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;int
WSAConnect proto _CType \
		     s: SOCKET,
		 _name: PVOID,
	       namelen: SINT,
	  lpCallerData: LPWSABUF,
	  lpCalleeData: LPWSABUF,
		lpSQOS: LPQOS,
		lpGQOS: LPQOS
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_WSACONNECT_T typedef proto _CType \
		     s: SOCKET,
		 _name: PVOID,
	       namelen: SINT,
	  lpCallerData: LPWSABUF,
	  lpCalleeData: LPWSABUF,
		lpSQOS: LPQOS,
		lpGQOS: LPQOS
LPFN_WSACONNECT typedef ptr LPFN_WSACONNECT_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;WSAEVENT
WSACreateEvent proto _CType
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_WSACREATEEVENT_T typedef proto _CType
LPFN_WSACREATEEVENT typedef ptr LPFN_WSACREATEEVENT_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;int
WSADuplicateSocketA proto _CType \
		     s: SOCKET,
	   dwProcessId: DWORD,
	lpProtocolInfo: LPWSAPROTOCOL_INFOA
;int
WSADuplicateSocketW proto _CType \
		     s: SOCKET,
	   dwProcessId: DWORD,
	lpProtocolInfo: LPWSAPROTOCOL_INFOW
ifdef _UNICODE
WSADuplicateSocket	equ <WSADuplicateSocketW>
else
WSADuplicateSocket	equ <WSADuplicateSocketA>
endif ;; NOT UNICODE
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_WSADUPLICATESOCKETA_T typedef proto _CType \
		     s: SOCKET,
	   dwProcessId: DWORD,
	lpProtocolInfo: LPWSAPROTOCOL_INFOA
LPFN_WSADUPLICATESOCKETA typedef ptr LPFN_WSADUPLICATESOCKETA_T

LPFN_WSADUPLICATESOCKETW_T typedef proto _CType \
		     s: SOCKET,
	   dwProcessId: DWORD,
	lpProtocolInfo: LPWSAPROTOCOL_INFOW
LPFN_WSADUPLICATESOCKETW typedef ptr LPFN_WSADUPLICATESOCKETW_T
ifdef _UNICODE
LPFN_WSADUPLICATESOCKET equ <LPFN_WSADUPLICATESOCKETW>
else
LPFN_WSADUPLICATESOCKET equ <LPFN_WSADUPLICATESOCKETA>
endif ;; NOT UNICODE
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;int
WSAEnumNetworkEvents proto _CType \
		     s: SOCKET,
	  hEventObject: WSAEVENT,
       lpNetworkEvents: LPWSANETWORKEVENTS
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_WSAENUMNETWORKEVENTS_T typedef proto _CType \
		     s: SOCKET,
	  hEventObject: WSAEVENT,
       lpNetworkEvents: LPWSANETWORKEVENTS
LPFN_WSAENUMNETWORKEVENTS typedef ptr LPFN_WSAENUMNETWORKEVENTS_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;int
WSAEnumProtocolsA proto _CType \
	  lpiProtocols: LPINT,
      lpProtocolBuffer: LPWSAPROTOCOL_INFOA,
      lpdwBufferLength: LPDWORD
;int
WSAEnumProtocolsW proto _CType \
	  lpiProtocols: LPINT,
      lpProtocolBuffer: LPWSAPROTOCOL_INFOW,
      lpdwBufferLength: LPDWORD
ifdef _UNICODE
WSAEnumProtocols	equ <WSAEnumProtocolsW>
else
WSAEnumProtocols	equ <WSAEnumProtocolsA>
endif ;; NOT UNICODE
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_WSAENUMPROTOCOLSA_T typedef proto _CType \
	  lpiProtocols: LPINT,
      lpProtocolBuffer: LPWSAPROTOCOL_INFOA,
      lpdwBufferLength: LPDWORD
LPFN_WSAENUMPROTOCOLSA typedef ptr LPFN_WSAENUMPROTOCOLSA_T
LPFN_WSAENUMPROTOCOLSW typedef proto _CType \
	  lpiProtocols: LPINT,
      lpProtocolBuffer: LPWSAPROTOCOL_INFOW,
      lpdwBufferLength: LPDWORD
LPFN_WSAENUMPROTOCOLSW typedef ptr LPFN_WSAENUMPROTOCOLSW_T
ifdef _UNICODE
LPFN_WSAENUMPROTOCOLS	equ <LPFN_WSAENUMPROTOCOLSW>
else
LPFN_WSAENUMPROTOCOLS	equ <LPFN_WSAENUMPROTOCOLSA>
endif ;; NOT UNICODE
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;int
WSAEventSelect proto _CType \
		     s: SOCKET,
	  hEventObject: WSAEVENT,
	lNetworkEvents: LONG
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_WSAEVENTSELECT_T typedef proto _CType \
		     s: SOCKET,
	  hEventObject: WSAEVENT,
	lNetworkEvents: LONG
LPFN_WSAEVENTSELECT typedef ptr LPFN_WSAEVENTSELECT_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;BOOL
WSAGetOverlappedResult proto _CType \
		     s: SOCKET,
	  lpOverlapped: LPWSAOVERLAPPED,
	  lpcbTransfer: LPDWORD,
		_fWait: BOOL,
	     lpdwFlags: LPDWORD
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_WSAGETOVERLAPPEDRESULT_T typedef proto _CType \
		     s: SOCKET,
	  lpOverlapped: LPWSAOVERLAPPED,
	  lpcbTransfer: LPDWORD,
		_fWait: BOOL,
	     lpdwFlags: LPDWORD
LPFN_WSAGETOVERLAPPEDRESULT typedef ptr LPFN_WSAGETOVERLAPPEDRESULT_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;BOOL
WSAGetQOSByName proto _CType \
		     s: SOCKET,
	     lpQOSName: LPWSABUF,
		 lpQOS: LPQOS
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_WSAGETQOSBYNAME_T typedef proto _CType \
		     s: SOCKET,
	     lpQOSName: LPWSABUF,
		 lpQOS: LPQOS
LPFN_WSAGETQOSBYNAME typedef ptr LPFN_WSAGETQOSBYNAME_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;int
WSAHtonl proto _CType \
		     s: SOCKET,
	      hostlong: DWORD,
	     lpnetlong: LPDWORD
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_WSAHTONL_T typedef proto _CType \
		     s: SOCKET,
	      hostlong: DWORD,
	     lpnetlong: LPDWORD
LPFN_WSAHTONL typedef ptr LPFN_WSAHTONL_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;int
WSAHtons proto _CType \
		     s: SOCKET,
	     hostshort: WORD,
	    lpnetshort: LPWORD
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_WSAHTONS_T typedef proto _CType \
		     s: SOCKET,
	     hostshort: WORD,
	    lpnetshort: LPWORD
LPFN_WSAHTONS typedef ptr LPFN_WSAHTONS_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;int
WSAIoctl proto _CType \
		     s: SOCKET,
       dwIoControlCode: DWORD,
	   lpvInBuffer: LPVOID,
	    cbInBuffer: DWORD,
	  lpvOutBuffer: LPVOID,
	   cbOutBuffer: DWORD,
     lpcbBytesReturned: LPDWORD,
	  lpOverlapped: LPWSAOVERLAPPED,
   lpCompletionRoutine: LPWSAOVERLAPPED_COMPLETION_ROUTINE
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_WSAIOCTL_T typedef proto _CType \
		     s: SOCKET,
       dwIoControlCode: DWORD,
	   lpvInBuffer: LPVOID,
	    cbInBuffer: DWORD,
	  lpvOutBuffer: LPVOID,
	   cbOutBuffer: DWORD,
     lpcbBytesReturned: LPDWORD,
	  lpOverlapped: LPWSAOVERLAPPED,
   lpCompletionRoutine: LPWSAOVERLAPPED_COMPLETION_ROUTINE
LPFN_WSAIOCTL typedef ptr LPFN_WSAIOCTL_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;SOCKET
WSAJoinLeaf proto _CType \
		     s: SOCKET,
		 _name: PVOID,
	       namelen: SINT,
	  lpCallerData: LPWSABUF,
	  lpCalleeData: LPWSABUF,
		lpSQOS: LPQOS,
		lpGQOS: LPQOS,
	       dwFlags: DWORD
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_WSAJOINLEAF_T typedef proto _CType \
		     s: SOCKET,
		 _name: PVOID,
	       namelen: SINT,
	  lpCallerData: LPWSABUF,
	  lpCalleeData: LPWSABUF,
		lpSQOS: LPQOS,
		lpGQOS: LPQOS,
	       dwFlags: DWORD
LPFN_WSAJOINLEAF typedef ptr LPFN_WSAJOINLEAF_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;int
WSANtohl proto _CType \
		     s: SOCKET,
	       netlong: DWORD,
	    lphostlong: LPDWORD
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_WSANTOHL_T typedef proto _CType \
		     s: SOCKET,
	       netlong: DWORD,
	    lphostlong: LPDWORD
LPFN_WSANTOHL typedef ptr LPFN_WSANTOHL_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;int
WSANtohs proto _CType \
		     s: SOCKET,
	      netshort: WORD,
	   lphostshort: LPWORD
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_WSANTOHS_T typedef proto _CType \
		     s: SOCKET,
	      netshort: WORD,
	   lphostshort: LPWORD
LPFN_WSANTOHS typedef ptr LPFN_WSANTOHS_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;int
WSARecv proto _CType \
		     s: SOCKET,
	     lpBuffers: LPWSABUF,
	 dwBufferCount: DWORD,
  lpNumberOfBytesRecvd: LPDWORD,
	       lpFlags: LPDWORD,
	  lpOverlapped: LPWSAOVERLAPPED,
   lpCompletionRoutine: LPWSAOVERLAPPED_COMPLETION_ROUTINE
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_WSARECV_T typedef typedef proto _CType \
		     s: SOCKET,
	     lpBuffers: LPWSABUF,
	 dwBufferCount: DWORD,
  lpNumberOfBytesRecvd: LPDWORD,
	       lpFlags: LPDWORD,
	  lpOverlapped: LPWSAOVERLAPPED,
   lpCompletionRoutine: LPWSAOVERLAPPED_COMPLETION_ROUTINE
LPFN_WSARECV typedef ptr LPFN_WSARECV_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;int
WSARecvDisconnect proto _CType \
		     s: SOCKET,
lpInboundDisconnectData: LPWSABUF
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_WSARECVDISCONNECT_T typedef proto _CType \
		     s: SOCKET,
lpInboundDisconnectData: LPWSABUF
LPFN_WSARECVDISCONNECT typedef ptr LPFN_WSARECVDISCONNECT_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;int
WSARecvFrom proto _CType \
		     s: SOCKET,
	     lpBuffers: LPWSABUF,
	 dwBufferCount: DWORD,
  lpNumberOfBytesRecvd: LPDWORD,
	       lpFlags: LPDWORD,
		lpFrom: PVOID,
	     lpFromlen: LPINT,
	  lpOverlapped: LPWSAOVERLAPPED,
   lpCompletionRoutine: LPWSAOVERLAPPED_COMPLETION_ROUTINE
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_WSARECVFROM_T typedef proto _CType \
		     s: SOCKET,
	     lpBuffers: LPWSABUF,
	 dwBufferCount: DWORD,
  lpNumberOfBytesRecvd: LPDWORD,
	       lpFlags: LPDWORD,
		lpFrom: PVOID,
	     lpFromlen: LPINT,
	  lpOverlapped: LPWSAOVERLAPPED,
   lpCompletionRoutine: LPWSAOVERLAPPED_COMPLETION_ROUTINE
LPFN_WSARECVFROM typedef ptr LPFN_WSARECVFROM_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;BOOL
WSAResetEvent proto _CType \
		hEvent: WSAEVENT
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_WSARESETEVENT_T typedef proto _CType \
		hEvent: WSAEVENT
LPFN_WSARESETEVENT typedef ptr LPFN_WSARESETEVENT_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;int
WSASend proto _CType \
		     s: SOCKET,
	     lpBuffers: LPWSABUF,
	 dwBufferCount: DWORD,
   lpNumberOfBytesSent: LPDWORD,
	       dwFlags: DWORD,
	  lpOverlapped: LPWSAOVERLAPPED,
   lpCompletionRoutine: LPWSAOVERLAPPED_COMPLETION_ROUTINE
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_WSASEND_T typedef proto _CType \
		     s: SOCKET,
	     lpBuffers: LPWSABUF,
	 dwBufferCount: DWORD,
   lpNumberOfBytesSent: LPDWORD,
	       dwFlags: DWORD,
	  lpOverlapped: LPWSAOVERLAPPED,
   lpCompletionRoutine: LPWSAOVERLAPPED_COMPLETION_ROUTINE
LPFN_WSASEND typedef ptr LPFN_WSASEND_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;int
WSASendDisconnect proto _CType \
		     s: SOCKET,
lpOutboundDisconnectData: LPWSABUF
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_WSASENDDISCONNECT_T typedef proto _CType \
		     s: SOCKET,
lpOutboundDisconnectData: LPWSABUF
LPFN_WSASENDDISCONNECT typedef ptr LPFN_WSASENDDISCONNECT_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;int
WSASendTo proto _CType \
		     s: SOCKET,
	     lpBuffers: LPWSABUF,
	 dwBufferCount: DWORD,
   lpNumberOfBytesSent: LPDWORD,
	       dwFlags: DWORD,
		  lpTo: PVOID,
		iTolen: SINT,
	  lpOverlapped: LPWSAOVERLAPPED,
   lpCompletionRoutine: LPWSAOVERLAPPED_COMPLETION_ROUTINE
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_WSASENDTO_T typedef proto _CType \
		     s: SOCKET,
	     lpBuffers: LPWSABUF,
	 dwBufferCount: DWORD,
   lpNumberOfBytesSent: LPDWORD,
	       dwFlags: DWORD,
		  lpTo: PVOID,
		iTolen: SINT,
	  lpOverlapped: LPWSAOVERLAPPED,
   lpCompletionRoutine: LPWSAOVERLAPPED_COMPLETION_ROUTINE
LPFN_WSASENDTO typedef ptr LPFN_WSASENDTO_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;BOOL
WSASetEvent proto _CType \
		hEvent: WSAEVENT
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_WSASETEVENT_T typedef proto _CType \
		hEvent: WSAEVENT
LPFN_WSASETEVENT typedef ptr LPFN_WSASETEVENT_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;SOCKET
WSASocketA proto _CType \
		    af: SINT,
		 _type: SINT,
	      protocol: SINT,
	lpProtocolInfo: LPWSAPROTOCOL_INFOA,
		     g: UINT,
	       dwFlags: DWORD
;SOCKET
WSASocketW proto _CType \
		    af: SINT,
		 _type: SINT,
	      protocol: SINT,
	lpProtocolInfo: LPWSAPROTOCOL_INFOW,
		     g: UINT,
	       dwFlags: DWORD
ifdef _UNICODE
WSASocket		equ <WSASocketW>
else
WSASocket		equ <WSASocketA>
endif ;; NOT UNICODE
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_WSASOCKETA_T typedef proto _CType \
		    af: SINT,
		 _type: SINT,
	      protocol: SINT,
	lpProtocolInfo: LPWSAPROTOCOL_INFOA,
		     g: UINT,
	       dwFlags: DWORD
LPFN_WSASOCKETA typedef ptr LPFN_WSASOCKETA_T
LPFN_WSASOCKETW_T typedef proto _CType \
		    af: SINT,
		 _type: SINT,
	      protocol: SINT,
	lpProtocolInfo: LPWSAPROTOCOL_INFOW,
		     g: UINT,
	       dwFlags: DWORD
LPFN_WSASOCKETW typedef ptr LPFN_WSASOCKETW_T
ifdef _UNICODE
LPFN_WSASOCKET		equ <LPFN_WSASOCKETW>
else
LPFN_WSASOCKET		equ <LPFN_WSASOCKETA>
endif ;; NOT UNICODE
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;DWORD
WSAWaitForMultipleEvents proto _CType \
	       cEvents: DWORD,
	     lphEvents: ptr WSAEVENT,
	      fWaitAll: BOOL,
	     dwTimeout: DWORD,
	    fAlertable: BOOL
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_WSAWAITFORMULTIPLEEVENTS_T typedef proto _CType \
	       cEvents: DWORD,
	     lphEvents: ptr WSAEVENT,
	      fWaitAll: BOOL,
	     dwTimeout: DWORD,
	    fAlertable: BOOL
LPFN_WSAWAITFORMULTIPLEEVENTS typedef ptr LPFN_WSAWAITFORMULTIPLEEVENTS_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;INT
WSAAddressToStringA proto _CType \
	   lpsaAddress: LPSOCKADDR,
       dwAddressLength: DWORD,
	lpProtocolInfo: LPWSAPROTOCOL_INFOA,
     lpszAddressString: LPSTR,
lpdwAddressStringLength: LPDWORD
;INT
WSAAddressToStringW proto _CType \
	   lpsaAddress: LPSOCKADDR,
       dwAddressLength: DWORD,
	lpProtocolInfo: LPWSAPROTOCOL_INFOW,
     lpszAddressString: LPWSTR,
lpdwAddressStringLength: LPDWORD
ifdef _UNICODE
WSAAddressToString	equ <WSAAddressToStringW>
else
WSAAddressToString	equ <WSAAddressToStringA>
endif ;; NOT UNICODE
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_WSAADDRESSTOSTRINGA_T typedef proto _CType \
	   lpsaAddress: LPSOCKADDR,
       dwAddressLength: DWORD,
	lpProtocolInfo: LPWSAPROTOCOL_INFOA,
     lpszAddressString: LPSTR,
lpdwAddressStringLength: LPDWORD
LPFN_WSAADDRESSTOSTRINGA typedef ptr LPFN_WSAADDRESSTOSTRINGA_T
LPFN_WSAADDRESSTOSTRINGW_T typedef proto _CType \
	   lpsaAddress: LPSOCKADDR,
       dwAddressLength: DWORD,
	lpProtocolInfo: LPWSAPROTOCOL_INFOW,
     lpszAddressString: LPWSTR,
lpdwAddressStringLength: LPDWORD
LPFN_WSAADDRESSTOSTRINGW typedef ptr LPFN_WSAADDRESSTOSTRINGW_T
ifdef _UNICODE
LPFN_WSAADDRESSTOSTRING equ <LPFN_WSAADDRESSTOSTRINGW>
else
LPFN_WSAADDRESSTOSTRING equ <LPFN_WSAADDRESSTOSTRINGA>
endif ;; NOT UNICODE
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;INT
WSAStringToAddressA proto _CType \
	 AddressString: LPSTR,
	 AddressFamily: SINT,
	lpProtocolInfo: LPWSAPROTOCOL_INFOA,
	     lpAddress: LPSOCKADDR,
       lpAddressLength: LPINT
;INT
WSAStringToAddressW proto _CType \
	 AddressString: LPWSTR,
	 AddressFamily: SINT,
	lpProtocolInfo: LPWSAPROTOCOL_INFOW,
	     lpAddress: LPSOCKADDR,
       lpAddressLength: LPINT
ifdef _UNICODE
WSAStringToAddress	equ <WSAStringToAddressW>
else
WSAStringToAddress	equ <WSAStringToAddressA>
endif ;; NOT UNICODE
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_WSASTRINGTOADDRESSA_T typedef proto _CType \
	 AddressString: LPSTR,
	 AddressFamily: SINT,
	lpProtocolInfo: LPWSAPROTOCOL_INFOA,
	     lpAddress: LPSOCKADDR,
       lpAddressLength: LPINT
;INT
LPFN_WSASTRINGTOADDRESSW_T typedef proto _CType \
	 AddressString: LPWSTR,
	 AddressFamily: SINT,
	lpProtocolInfo: LPWSAPROTOCOL_INFOW,
	     lpAddress: LPSOCKADDR,
       lpAddressLength: LPINT
LPFN_WSASTRINGTOADDRESSA typedef ptr LPFN_WSASTRINGTOADDRESSA_T
LPFN_WSASTRINGTOADDRESSW typedef ptr LPFN_WSASTRINGTOADDRESSW_T
ifdef _UNICODE
LPFN_WSASTRINGTOADDRESS equ <LPFN_WSASTRINGTOADDRESSW>
else
LPFN_WSASTRINGTOADDRESS equ <LPFN_WSASTRINGTOADDRESSA>
endif ;; NOT UNICODE
endif ;; INCL_WINSOCK_API_TYPEDEFS

;; Registration and Name Resolution API functions


if INCL_WINSOCK_API_PROTOTYPES
;INT
WSALookupServiceBeginA proto _CType \
      lpqsRestrictions: LPWSAQUERYSETA,
	dwControlFlags: DWORD,
	     lphLookup: LPHANDLE
;INT
WSALookupServiceBeginW proto _CType \
      lpqsRestrictions: LPWSAQUERYSETW,
	dwControlFlags: DWORD,
	     lphLookup: LPHANDLE
ifdef _UNICODE
WSALookupServiceBegin	equ <WSAookupServiceBeginW>
else
WSALookupServiceBegin	equ <WSAookupServiceBeginA>
endif ;; NOT UNICODE
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_WSALOOKUPSERVICEBEGINA_T typedef proto _CType \
      lpqsRestrictions: LPWSAQUERYSETA,
	dwControlFlags: DWORD,
	     lphLookup: LPHANDLE
LPFN_WSALOOKUPSERVICEBEGINA typedef ptr LPFN_WSALOOKUPSERVICEBEGINA_T
LPFN_WSALOOKUPSERVICEBEGINW_T typedef proto _CType \
      lpqsRestrictions: LPWSAQUERYSETW,
	dwControlFlags: DWORD,
	     lphLookup: LPHANDLE
LPFN_WSALOOKUPSERVICEBEGINW typedef ptr LPFN_WSALOOKUPSERVICEBEGINW_T
ifdef _UNICODE
LPFN_WSALOOKUPSERVICEBEGIN equ <LPFN_WSAOOKUPSERVICEBEGINW>
else
LPFN_WSALOOKUPSERVICEBEGIN equ <LPFN_WSAOOKUPSERVICEBEGINA>
endif ;; NOT UNICODE
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;INT
WSALookupServiceNextA proto _CType \
	       hLookup: HANDLE,
	dwControlFlags: DWORD,
      lpdwBufferLength: LPDWORD,
	   lpqsResults: LPWSAQUERYSETA
;INT
WSALookupServiceNextW proto _CType \
	       hLookup: HANDLE,
	dwControlFlags: DWORD,
      lpdwBufferLength: LPDWORD,
	   lpqsResults: LPWSAQUERYSETW
ifdef _UNICODE
WSALookupServiceNext	equ <WSAookupServiceNextW>
else
WSALookupServiceNext	equ <WSAookupServiceNextA>
endif ;; NOT UNICODE
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_WSALOOKUPSERVICENEXTA_T typedef proto _CType \
	       hLookup: HANDLE,
	dwControlFlags: DWORD,
      lpdwBufferLength: LPDWORD,
	   lpqsResults: LPWSAQUERYSETA
LPFN_WSALOOKUPSERVICENEXTA typedef ptr LPFN_WSALOOKUPSERVICENEXTA_T
LPFN_WSALOOKUPSERVICENEXTW_T typedef proto _CType \
	       hLookup: HANDLE,
	dwControlFlags: DWORD,
      lpdwBufferLength: LPDWORD,
	   lpqsResults: LPWSAQUERYSETW
LPFN_WSALOOKUPSERVICENEXTW typedef ptr LPFN_WSALOOKUPSERVICENEXTW_T
ifdef _UNICODE
LPFN_WSALOOKUPSERVICENEXT equ <LPFN_WSAOOKUPSERVICENEXTW>
else
LPFN_WSALOOKUPSERVICENEXT equ <LPFN_WSAOOKUPSERVICENEXTA>
endif ;; NOT UNICODE
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;INT
WSALookupServiceEnd proto _CType \
	       hLookup: HANDLE
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_WSALOOKUPSERVICEEND_T typedef proto _CType \
	       hLookup: HANDLE
LPFN_WSALOOKUPSERVICEEND typedef ptr LPFN_WSALOOKUPSERVICEEND_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;INT
WSAInstallServiceClassA proto _CType \
    lpServiceClassInfo: LPWSASERVICECLASSINFOA
;INT
WSAInstallServiceClassW proto _CType \
    lpServiceClassInfo: LPWSASERVICECLASSINFOW
ifdef _UNICODE
WSAInstallServiceClass	equ <WSAInstallServiceClassW>
else
WSAInstallServiceClass	equ <WSAInstallServiceClassA>
endif ;; NOT UNICODE
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_WSAINSTALLSERVICECLASSA_T typedef proto _CType \
    lpServiceClassInfo: LPWSASERVICECLASSINFOA
LPFN_WSAINSTALLSERVICECLASSA typedef ptr LPFN_WSAINSTALLSERVICECLASSA_T
LPFN_WSAINSTALLSERVICECLASSW_T typedef proto _CType \
    lpServiceClassInfo: LPWSASERVICECLASSINFOW
LPFN_WSAINSTALLSERVICECLASSW typedef ptr LPFN_WSAINSTALLSERVICECLASSW_T
ifdef _UNICODE
LPFN_WSAINSTALLSERVICECLASS equ <LPFN_WSAINSTALLSERVICECASSW>
else
LPFN_WSAINSTALLSERVICECLASS equ <LPFN_WSAINSTALLSERVICECASSA>
endif ;; NOT UNICODE
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;INT
WSARemoveServiceClass proto _CType \
      lpServiceClassId: LPGUID
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_WSAREMOVESERVICECLASS_T typedef proto _CType \
      lpServiceClassId: LPGUID
LPFN_WSAREMOVESERVICECLASS typedef ptr LPFN_WSAREMOVESERVICECLASS_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;INT
WSAGetServiceClassInfoA proto _CType \
	  lpProviderId: LPGUID,
      lpServiceClassId: LPGUID,
	   lpdwBufSize: LPDWORD,
    lpServiceClassInfo: LPWSASERVICECLASSINFOA
;INT
WSAGetServiceClassInfoW proto _CType \
	  lpProviderId: LPGUID,
      lpServiceClassId: LPGUID,
	   lpdwBufSize: LPDWORD,
    lpServiceClassInfo: LPWSASERVICECLASSINFOW
ifdef _UNICODE
WSAGetServiceClassInfo	equ <WSAGetServiceClassInfoW>
else
WSAGetServiceClassInfo	equ <WSAGetServiceClassInfoA>
endif ;; NOT UNICODE
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_WSAGETSERVICECLASSINFOA_T typedef proto _CType \
	  lpProviderId: LPGUID,
      lpServiceClassId: LPGUID,
	   lpdwBufSize: LPDWORD,
    lpServiceClassInfo: LPWSASERVICECLASSINFOA
LPFN_WSAGETSERVICECLASSINFOA typedef ptr LPFN_WSAGETSERVICECLASSINFOA_T
LPFN_WSAGETSERVICECLASSINFOW_T typedef proto _CType \
	  lpProviderId: LPGUID,
      lpServiceClassId: LPGUID,
	   lpdwBufSize: LPDWORD,
    lpServiceClassInfo: LPWSASERVICECLASSINFOW
LPFN_WSAGETSERVICECLASSINFOW typedef ptr LPFN_WSAGETSERVICECLASSINFOW_T
ifdef _UNICODE
LPFN_WSAGETSERVICECLASSINFO equ <LPFN_WSAGETSERVICECASSINFOW>
else
LPFN_WSAGETSERVICECLASSINFO equ <LPFN_WSAGETSERVICECASSINFOA>
endif ;; NOT UNICODE
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;INT
WSAEnumNameSpaceProvidersA proto _CType \
      lpdwBufferLength: LPDWORD,
	   lpnspBuffer: LPWSANAMESPACE_INFOA
;INT
WSAEnumNameSpaceProvidersW proto _CType \
      lpdwBufferLength: LPDWORD,
	   lpnspBuffer: LPWSANAMESPACE_INFOW
ifdef _UNICODE
WSAEnumNameSpaceProviders equ <WSAEnumNameSpaceProvidersW>
else
WSAEnumNameSpaceProviders equ <WSAEnumNameSpaceProvidersA>
endif ;; NOT UNICODE
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_WSAENUMNAMESPACEPROVIDERSA_T typedef proto _CType \
      lpdwBufferLength: LPDWORD,
	   lpnspBuffer: LPWSANAMESPACE_INFOA
LPFN_WSAENUMNAMESPACEPROVIDERSA typedef ptr LPFN_WSAENUMNAMESPACEPROVIDERSA_T
LPFN_WSAENUMNAMESPACEPROVIDERSW_T typedef proto _CType \
      lpdwBufferLength: LPDWORD,
	   lpnspBuffer: LPWSANAMESPACE_INFOW
LPFN_WSAENUMNAMESPACEPROVIDERSW typedef ptr LPFN_WSAENUMNAMESPACEPROVIDERSW_T
ifdef _UNICODE
LPFN_WSAENUMNAMESPACEPROVIDERS equ <LPFN_WSAENUMNAMESPACEPROVIDERSW>
else
LPFN_WSAENUMNAMESPACEPROVIDERS equ <LPFN_WSAENUMNAMESPACEPROVIDERSA>
endif ;; NOT UNICODE
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;INT
WSAGetServiceClassNameByClassIdA proto _CType \
      lpServiceClassId: LPGUID,
  lpszServiceClassName: LPSTR,
      lpdwBufferLength: LPDWORD
;INT
WSAGetServiceClassNameByClassIdW proto _CType \
      lpServiceClassId: LPGUID,
  lpszServiceClassName: LPWSTR,
      lpdwBufferLength: LPDWORD
ifdef _UNICODE
WSAGetServiceClassNameByClassId equ <WSAGetServiceClassNameByClassIdW>
else
WSAGetServiceClassNameByClassId equ <WSAGetServiceClassNameByClassIdA>
endif ;; NOT UNICODE
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_WSAGETSERVICECLASSNAMEBYCLASSIDA_T typedef proto _CType \
      lpServiceClassId: LPGUID,
  lpszServiceClassName: LPSTR,
      lpdwBufferLength: LPDWORD
LPFN_WSAGETSERVICECLASSNAMEBYCLASSIDA typedef ptr LPFN_WSAGETSERVICECLASSNAMEBYCLASSIDA_T
LPFN_WSAGETSERVICECLASSNAMEBYCLASSIDW_T typedef proto _CType \
      lpServiceClassId: LPGUID,
  lpszServiceClassName: LPWSTR,
      lpdwBufferLength: LPDWORD
LPFN_WSAGETSERVICECLASSNAMEBYCLASSIDW typedef ptr LPFN_WSAGETSERVICECLASSNAMEBYCLASSIDW_T
ifdef _UNICODE
LPFN_WSAGETSERVICECLASSNAMEBYCLASSID equ <LPFN_WSAGETSERVICECLASSNAMEBYCASSIDW>
else
LPFN_WSAGETSERVICECLASSNAMEBYCLASSID equ <LPFN_WSAGETSERVICECLASSNAMEBYCASSIDA>
endif ;; NOT UNICODE
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;INT
WSASetServiceA proto _CType \
	   lpqsRegInfo: LPWSAQUERYSETA,
	  essoperation: WSAESETSERVICEOP,
	dwControlFlags: DWORD
;INT
WSASetServiceW proto _CType \
	   lpqsRegInfo: LPWSAQUERYSETW,
	  essoperation: WSAESETSERVICEOP,
	dwControlFlags: DWORD
ifdef _UNICODE
WSASetService		equ <WSASetServiceW>
else
WSASetService		equ <WSASetServiceA>
endif ;; NOT UNICODE
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_WSASETSERVICEA_T typedef proto _CType \
	   lpqsRegInfo: LPWSAQUERYSETA,
	  essoperation: WSAESETSERVICEOP,
	dwControlFlags: DWORD
LPFN_WSASETSERVICEA typedef ptr LPFN_WSASETSERVICEA_T
LPFN_WSASETSERVICEW_T typedef proto _CType \
	   lpqsRegInfo: LPWSAQUERYSETW,
	  essoperation: WSAESETSERVICEOP,
	dwControlFlags: DWORD
LPFN_WSASETSERVICEW typedef ptr LPFN_WSASETSERVICEW_T
ifdef _UNICODE
LPFN_WSASETSERVICE	equ <LPFN_WSASETSERVICEW>
else
LPFN_WSASETSERVICE	equ <LPFN_WSASETSERVICEA>
endif ;; NOT UNICODE
endif ;; INCL_WINSOCK_API_TYPEDEFS

if INCL_WINSOCK_API_PROTOTYPES
;INT
WSAProviderConfigChange proto _CType \
  lpNotificationHandle: LPHANDLE,
	  lpOverlapped: LPWSAOVERLAPPED,
   lpCompletionRoutine: LPWSAOVERLAPPED_COMPLETION_ROUTINE
endif ;; INCL_WINSOCK_API_PROTOTYPES

if INCL_WINSOCK_API_TYPEDEFS
LPFN_WSAPROVIDERCONFIGCHANGE_T typedef proto _CType \
  lpNotificationHandle: LPHANDLE,
	  lpOverlapped: LPWSAOVERLAPPED,
   lpCompletionRoutine: LPWSAOVERLAPPED_COMPLETION_ROUTINE
LPFN_WSAPROVIDERCONFIGCHANGE typedef ptr LPFN_WSAPROVIDERCONFIGCHANGE_T
endif ;; INCL_WINSOCK_API_TYPEDEFS

;; Microsoft Windows Extended data types
;sockaddr_in SOCKADDR_IN; STRUC
PSOCKADDR_IN		typedef PVOID
LPSOCKADDR_IN		typedef PVOID

;linger LINGER;		STRUC
PLINGER			typedef PVOID
LPLINGER		typedef PVOID

;in_addr IN_ADDR;	STRUC
PIN_ADDR		typedef PVOID
LPIN_ADDR		typedef PVOID

;fd_set FD_SET;		STRUC
PFD_SET			typedef PVOID
LPFD_SET		typedef PVOID

;hostent HOSTENT;	STRUC
PHOSTENT		typedef PVOID
LPHOSTENT		typedef PVOID

;SERVENT;	STRUC
PSERVENT		typedef PVOID
LPSERVENT		typedef PVOID

;protoent PROTOENT;	STRUC
PPROTOENT		typedef PVOID
LPPROTOENT		typedef PVOID

;timeval TIMEVAL;	STRUC
PTIMEVAL		typedef PVOID
LPTIMEVAL		typedef PVOID

;;
;; Windows message parameter composition and decomposition
;; macros.
;;
;; WSAMAKEASYNCREPLY is intended for use by the Windows Sockets implementation
;; when constructing the response to a WSAAsyncGetXByY() routine.
;;
WSAMAKEASYNCREPLY macro buflen,error
	exitm<MAKEONG(buflen,error)>
	endm
;;
;; WSAMAKESELECTREPLY is intended for use by the Windows Sockets implementation
;; when constructing the response to WSAAsyncSelect().
;;
WSAMAKESELECTREPLY macro event,error
	exitm<MAKEONG(event,error)>
	endm
;;
;; WSAGETASYNCBUFLEN is intended for use by the Windows Sockets application
;; to extract the buffer length from the lParam in the response
;; to a WSAAsyncGetXByY().
;;
WSAGETASYNCBUFLEN macro lParam
	exitm<LOWORD(lParam)>
	endm
;;
;; WSAGETASYNCERROR is intended for use by the Windows Sockets application
;; to extract the error code from the lParam in the response
;; to a WSAGetXByY().
;;
WSAGETASYNCERROR macro lParam
	exitm<HIWORD(lParam)>
	endm
;;
;; WSAGETSELECTEVENT is intended for use by the Windows Sockets application
;; to extract the event code from the lParam in the response
;; to a WSAAsyncSelect().
;;
WSAGETSELECTEVENT macro lParam
	exitm<LOWORD(lParam)>
	endm
;;
;; WSAGETSELECTERROR is intended for use by the Windows Sockets application
;; to extract the error code from the lParam in the response
;; to a WSAAsyncSelect().
;;
WSAGETSELECTERROR macro lParam
	exitm<HIWORD(lParam)>
	endm

;include <poppack.h>

endif	;; _WINSOCK2API_

.list
