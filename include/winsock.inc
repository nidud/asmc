ifndef __LIBC_INC
 include libc.inc
endif
.xlist
ifndef _WINSOCKAPI_
_WINSOCKAPI_ equ 1

;;
;; Pull in WINDOWS.H if necessary
;;
ifndef _INC_WINDOWS
include windows.inc
.xlist
endif ;; _INC_WINDOWS

;;
;; Basic system type definitions, taken from the BSD file sys/types.h.
;;
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
;; INCLUDED IN WINSOCK.H EXACTLY AS SHOWN HERE.
;;
ifndef FD_SETSIZE
FD_SETSIZE		equ 64
endif ;; FD_SETSIZE

fd_set			STRUC
fd_count		UINT ?	;; how many are SET?
fd_array		SOCKET FD_SETSIZE dup(?) ;; an array of SOCKETs
fd_set			ENDS

__WSAFDIsSet		proto :SOCKET, :ptr fd_set

FD_CLR macro fd,
	pushad
	lea	ebx,set
	mov	eax,fd
	mov	ecx,[ebx].fd_set.fd_count
	lea	esi,[ebx].fd_set.fd_array
	mov	edi,esi
	.while (ecx)
		.if (eax == [esi])
			dec [ebx].fd_set.fd_count
			add esi, 4
		.endif
		movsd
		dec	ecx
	.endw
	popad
	endm

FD_SET macro fd, set
	endm
	lea	edx,set
	mov	eax,fd
	mov	ecx,[edx].fd_set.fd_count
	.if	ecx < FD_SETSIZE
		mov [edx].fd_set.fd_array[ecx*4],eax
		inc [edx].fd_set.fd_count
	.endif
	endm

FD_ZERO macro set
	lea	eax,set
	mov	[eax].fd_set.fd_count, 0
	endm

FD_ISSET macro fd, set
	exitm<__WSAFDIsSet(fd, set)>
	endm

;;
;; Structure used in select() call, taken from the BSD file sys/time.h.
;;
timeval			STRUC
tv_sec			LONG ?	;; seconds
tv_usec			LONG ?	;; and microseconds
timeval			ENDS

;;
;; Operations on timevals.
;;
;; NB: timercmp does not work for >= or <=.
;;
timerisset macro tvp
	exitm<0>
	endm
timercmp macro tvp,uvp,cmp
	exitm<0>
	endm
timerclear macro tvp
	exitm<0>
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
	exitm<(IOC_OUT OR ((sizeof(t) AND IOCPARM_MASK) SHL 16) OR ((x) SHL 8) OR (y))>
	endm

_IOW macro x,y,t
	exitm<(IOC_IN OR ((sizeof(t) AND IOCPARM_MASK) SHL 16) OR ((x) SHL 8) OR (y))>
	endm

FIONREAD		equ _IOR('f', 127, ULONG) ;; get # bytes to read
FIONBIO			equ _IOW('f', 126, ULONG) ;; set/clear non-blocking i/o
FIOASYNC		equ _IOW('f', 125, ULONG) ;; set/clear async i/o

;; Socket I/O Controls
SIOCSHIWAT		equ _IOW('s',  0, ULONG) ;; set high watermark
SIOCGHIWAT		equ _IOR('s',  1, ULONG) ;; get high watermark
SIOCSLOWAT		equ _IOW('s',  2, ULONG) ;; set low watermark
SIOCGLOWAT		equ _IOR('s',  3, ULONG) ;; get low watermark
SIOCATMARK		equ _IOR('s',  7, ULONG) ;; at oob mark?

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
IPPROTO_IGMP		equ 2		;; group management protocol
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
 STRUC
  s_b1			db ?
  s_b2			db ?
  s_b3			db ?
  s_b4			db ?
 ENDS
 STRUC S_un_w
  s_w1			dw ?
  s_w2			dw ?
 ENDS
 S_addr			dd ?
ENDS
s_addr			equ <S_un.S_addr>
s_host			equ <S_un.S_un_b.s_b2>
s_net			equ <S_un.S_un_b.s_b1>
s_imp			equ <S_un.S_un_w.s_w2>
s_impno			equ <S_un.S_un_b.s_b4>
s_lh			equ <S_un.S_un_b.s_b3>
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

INADDR_ANY		equ (ULONG)0x00000000
INADDR_LOOPBACK		equ 0x7f000001
INADDR_BROADCAST	equ (ULONG)0xffffffff
INADDR_NONE		equ 0xffffffff

;;
;; Socket address, internet style.
;;
sockaddr_in		STRUC
sin_family		dw ?
sin_port		dw ?
sin_addr		in_addr <>
sin_zero		db 8 dup(?)
sockaddr_in		ENDS

WSADESCRIPTION_LEN	equ 256
WSASYS_STATUS_LEN	equ 128

WSAData			STRUC
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
;; Options for use with [gs]etsockopt at the IP level.
;;
IP_OPTIONS		equ 1		;; set/get IP per-packet options
IP_MULTICAST_IF		equ 2		;; set/get IP multicast interface
IP_MULTICAST_TTL	equ 3		;; set/get IP multicast timetolive
IP_MULTICAST_LOOP	equ 4		;; set/get IP multicast loopback
IP_ADD_MEMBERSHIP	equ 5		;; add	an IP group membership
IP_DROP_MEMBERSHIP	equ 6		;; drop an IP group membership
IP_TTL			equ 7		;; set/get IP Time To Live
IP_TOS			equ 8		;; set/get IP Type Of Service
IP_DONTFRAGMENT		equ 9		;; set/get IP Don't Fragment flag


IP_DEFAULT_MULTICAST_TTL equ 1	;; normally limit m'casts to 1 hop
IP_DEFAULT_MULTICAST_LOOP equ 1 ;; normally hear sends if a member
IP_MAX_MEMBERSHIPS	equ 20	;; per socket; must fit in one mbuf

;;
;; Argument structure for IP_ADD_MEMBERSHIP and IP_DROP_MEMBERSHIP.
;;
ip_mreq			STRUC
imr_multiaddr		in_addr <>	; IP multicast address of group
imr_interface		in_addr <>	; local IP address of interface
ip_mreq			ENDS

;;
;; Definitions related to sockets: types, address families, options,
;; taken from the BSD file sys/socket.h.
;;

;;
;; This is used instead of -1, since the
;; SOCKET type is unsigned.
;;
INVALID_SOCKET		equ <( NOT 0)>
SOCKET_ERROR		equ (-1)

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

SO_DONTLINGER		equ <( NOT SO_LINGER)>

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
;; Options for connect and disconnect data and options.	 Used only by
;; non-TCP/IP transports such as DECNet, OSI TP4, etc.
;;
SO_CONNDATA		equ 0x7000
SO_CONNOPT		equ 0x7001
SO_DISCDATA		equ 0x7002
SO_DISCOPT		equ 0x7003
SO_CONNDATALEN		equ 0x7004
SO_CONNOPTLEN		equ 0x7005
SO_DISCDATALEN		equ 0x7006
SO_DISCOPTLEN		equ 0x7007

;;
;; Option for opening sockets for synchronous access.
;;
SO_OPENTYPE		equ 0x7008

SO_SYNCHRONOUS_ALERT	equ 0x10
SO_SYNCHRONOUS_NONALERT equ 0x20

;;
;; Other NT-specific options.
;;
SO_MAXDG		equ 0x7009
SO_MAXPATHDG		equ 0x700A
SO_UPDATE_ACCEPT_CONTEXT equ 0x700B
SO_CONNECT_TIME		equ 0x700C

;;
;; TCP options.
;;
TCP_NODELAY		equ 0x0001
TCP_BSDURGENT		equ 0x7000

;;
;; Address families.
;;
AF_UNSPEC		equ 0		;; unspecified
AF_UNIX			equ 1		;; local to host (pipes, portals)
AF_INET			equ 2		;; internetwork: UDP, TCP, etc.
AF_IMPLINK		equ 3		;; arpanet imp addresses
AF_PUP			equ 4		;; pup protocols: e.g. BSP
AF_CHAOS		equ 5		;; mit CHAOS protocols
AF_IPX			equ 6		;; IPX and SPX
AF_NS			equ 6		;; XEROX NS protocols
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
AF_FIREFOX		equ 19		;; FireFox
AF_UNKNOWN1		equ 20		;; Somebody is using this NOT
AF_BAN			equ 21		;; Banyan

AF_MAX			equ 22

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
SOMAXCONN		equ 5

MSG_OOB			equ 0x1		;; process out-of-band data
MSG_PEEK		equ 0x2		;; peek at incoming message
MSG_DONTROUTE		equ 0x4		;; send without using routing tables

MSG_MAXIOVLEN		equ 16

MSG_PARTIAL		equ 0x8000		;; partial send or recv for message xport

;;
;; Define constant based on rfc883, used by gethostbyxxxx() calls.
;;
MAXGETHOSTSTRUCT	equ 1024

;;
;; Define flags to be used with the WSAAsyncSelect() call.
;;
FD_READ			equ 0x01
FD_WRITE		equ 0x02
FD_OOB			equ 0x04
FD_ACCEPT		equ 0x08
FD_CONNECT		equ 0x10
FD_CLOSE		equ 0x20

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

WSAEDISCON		equ (WSABASEERR+101)

;;
;; Extended Windows Sockets error constant definitions
;;
WSASYSNOTREADY		equ (WSABASEERR+91)
WSAVERNOTSUPPORTED	equ (WSABASEERR+92)
WSANOTINITIALISED	equ (WSABASEERR+93)

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

;; Non recoverable errors, FORMERR, REFUSED, NOTIMP
WSANO_RECOVERY		equ (WSABASEERR+1003)
NO_RECOVERY		equ WSANO_RECOVERY

;; Valid name, no data record of requested type
WSANO_DATA		equ (WSABASEERR+1004)
NO_DATA			equ WSANO_DATA

;; no address, look for MX record
WSANO_ADDRESS		equ WSANO_DATA
NO_ADDRESS		equ WSANO_ADDRESS

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

;; Socket function prototypes

accept proto _CType \
		 _addr: ptr sockaddr,
	       addrlen: ptr SINT

;int
bind proto _CType \
		     s: SOCKET,
		 _addr: ptr sockaddr,
	       namelen: SINT

;int
closesocket proto _CType \
		     s: SOCKET

;int
connect proto _CType \
		     s: SOCKET,
		 _name: ptr sockaddr,
	       namelen: SINT

;int
ioctlsocket proto _CType \
		     s: SOCKET,
		   cmd: LONG,
		  argp: ptr ULONG

;int
getpeername proto _CType \
		     s: SOCKET,
		 _name: ptr sockaddr,
	       namelen: ptr SINT

;int
getsockname proto _CType \
		     s: SOCKET,
		 _name: ptr sockaddr,
	       namelen: ptr SINT

;int
getsockopt proto _CType \
		     s: SOCKET,
		 level: SINT,
	       optname: SINT,
		optval: LPSTR,
		optlen: ptr SINT

;ULONG
htonl proto _CType \
	      hostlong: ULONG

WORD  htons(WORD hostshort);

;ULONG
inet_addr proto _CType \
		    cp: LPSTR

;LPSTR
inet_ntoa proto _CType \
		      : in_addr

;int
listen proto _CType \
		     s: SOCKET,
	       backlog: SINT

;ULONG
ntohl proto _CType \
	       netlong: ULONG

;WORD
ntohs proto _CType \
	      netshort: WORD

;int
recv proto _CType \
		     s: SOCKET,
		   buf: LPSTR,
		   len: SINT,
		 flags: SINT

;int
recvfrom proto _CType \
		     s: SOCKET,
		   buf: LPSTR,
		   len: SINT,
		 flags: SINT,
		  from: ptr sockaddr,
	       fromlen: ptr SINT

;int
select proto _CType \
		  nfds: SINT,
	       readfds: ptr fd_set,
	      writefds: ptr fd_set,
	     exceptfds: ptr fd_set,
	       timeout: ptr timeval

;int
send proto _CType \
		     s: SOCKET,
		   buf: LPSTR,
		   len: SINT,
		 flags: SINT

;int
sendto proto _CType \
		     s: SOCKET,
		   buf: LPSTR,
		   len: SINT,
		 flags: SINT,
		    to: ptr sockaddr,
		 tolen: SINT

;int
setsockopt proto _CType \
		     s: SOCKET,
		 level: SINT,
	       optname: SINT,
		optval: LPSTR,
		optlen: SINT

;int
shutdown proto _CType \
		     s: SOCKET,
		   how: SINT

;SOCKET
socket proto _CType \
		    af: SINT,
		 _type: SINT,
	      protocol: SINT

;; Database function prototypes

;hostent *
gethostbyaddr proto _CType \
		 _addr: LPSTR,
		   len: SINT,
		 _type: SINT

hostent *
gethostbyname proto _CType \
		 _name: LPSTR

;int
gethostname proto _CType \
		 _name: LPSTR,
	       namelen: SINT

;servent *
getservbyport proto _CType \
		  port: SINT,
		_proto: LPSTR

;servent *
getservbyname proto _CType \
		 _name: LPSTR,
		_proto: LPSTR

;protoent *
getprotobynumber proto _CType \
		_proto: SINT

;protoent *
getprotobyname proto _CType \
		 _name: LPSTR

;; Microsoft Windows Extension function prototypes

;int
WSAStartup proto _CType \
      wVersionRequired: WORD,
	     lpWSAData: LPWSADATA

;int

;void
WSASetLastError proto _CType \
		iError: SINT

;int

;BOOL

;int

FARPROC
WSASetBlockingHook proto _CType \
	   lpBlockFunc: FARPROC

;int

;HANDLE
WSAAsyncGetServByName proto _CType \
		  hWnd: HWND,
		  wMsg: UINT,
		 _name: LPSTR,
		_proto: LPSTR,
		   buf: LPSTR,
		buflen: SINT

;HANDLE
WSAAsyncGetServByPort proto _CType \
		  hWnd: HWND,
		  wMsg: UINT,
		  port: SINT,
		_proto: LPSTR,
		   buf: LPSTR,
		buflen: SINT

;HANDLE
WSAAsyncGetProtoByName proto _CType \
		  hWnd: HWND,
		  wMsg: UINT,
		  name: LPSTR,
		   buf: LPSTR,
		buflen: SINT

;HANDLE
WSAAsyncGetProtoByNumber proto _CType \
		  hWnd: HWND,
		  wMsg: UINT,
		number: SINT,
		   buf: LPSTR,
		buflen: SINT

;HANDLE
WSAAsyncGetHostByName proto _CType \
		  hWnd: HWND,
		  wMsg: UINT,
		  name: LPSTR,
		   buf: LPSTR,
		buflen: SINT

;HANDLE
WSAAsyncGetHostByAddr proto _CType \
		  hWnd: HWND,
		  wMsg: UINT,
		 _addr: LPSTR,
		   len: SINT,
		 _type: SINT,
		   buf: LPSTR,
		buflen: SINT

;int
WSACancelAsyncRequest proto _CType \
      hAsyncTaskHandle: HANDLE

;int
WSAAsyncSelect proto _CType \
		     s: SOCKET,
		  hWnd: HWND,
		  wMsg: UINT,
		lEvent: LONG

;int
WSARecvEx proto _CType \
		     s: SOCKET,
		   buf: LPSTR,
		   len: SINT,
		 flags: ptr SINT

TRANSMIT_FILE_BUFFERS	STRUC
Head			PVOID ?
HeadLength		dd ?
Tail			PVOID ?
TailLength		dd ?
TRANSMIT_FILE_BUFFERS	ENDS
PTRANSMIT_FILE_BUFFERS	typedef ptr TRANSMIT_FILE_BUFFERS
LPTRANSMIT_FILE_BUFFERS typedef ptr TRANSMIT_FILE_BUFFERS

TF_DISCONNECT		equ 0x01
TF_REUSE_SOCKET		equ 0x02
TF_WRITE_BEHIND		equ 0x04

;BOOL
TransmitFile proto _CType \
	       hSocket: SOCKET,
		 hFile: HANDLE,
 nNumberOfBytesToWrite: DWORD,
 nNumberOfBytesPerSend: DWORD,
	  lpOverlapped: LPOVERLAPPED,
     lpTransmitBuffers: LPTRANSMIT_FILE_BUFFERS,
	    dwReserved: DWORD

;BOOL
AcceptEx proto _CType \
	 sListenSocket: SOCKET,
	 sAcceptSocket: SOCKET,
	lpOutputBuffer: PVOID,
   dwReceiveDataLength: DWORD,
  dwLocalAddressLength: DWORD,
 dwRemoteAddressLength: DWORD,
     lpdwBytesReceived: LPDWORD,
	  lpOverlapped: LPOVERLAPPED

;VOID
GetAcceptExSockaddrs _CType \
	lpOutputBuffer: PVOID,
   dwReceiveDataLength: DWORD,
  dwLocalAddressLength: DWORD,
 dwRemoteAddressLength: DWORD,
	 LocalSockaddr: PVOID,
   LocalSockaddrLength: LPINT,
	RemoteSockaddr: PVOID,
  RemoteSockaddrLength: LPINT

;; Microsoft Windows Extended data types
;sockaddr SOCKADDR;	 STRUC
PSOCKADDR		typedef PVOID
LPSOCKADDR		typedef PVOID

;sockaddr_in SOCKADDR_IN; STRUC
PSOCKADDR_IN		typedef PVOID
LPSOCKADDR_IN		typedef PVOID

;LINGER;	   STRUC
PLINGER			typedef PVOID
LPLINGER		typedef PVOID

;in_addr IN_ADDR;	 STRUC
PIN_ADDR		typedef PVOID
LPIN_ADDR		typedef PVOID

;fd_set FD_SET;		 STRUC
PFD_SET			typedef PVOID
LPFD_SET		typedef PVOID

;hostent HOSTENT;	 STRUC
PHOSTENT		typedef PVOID
LPHOSTENT		typedef PVOID

;servent SERVENT;	 STRUC
PSERVENT		typedef PVOID
LPSERVENT		typedef PVOID

;protoent PROTOENT;	 STRUC
PPROTOENT		typedef PVOID
LPPROTOENT		typedef PVOID

;timeval TIMEVAL;	 STRUC
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
;; to a WSAGetXByY().
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

endif	;; _WINSOCKAPI_

.list
