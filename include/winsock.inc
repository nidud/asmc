ifndef __LIBC_INC
 include libc.inc
endif
ifndef _WINSOCKAPI_
_WINSOCKAPI_ equ <>

ifndef _INC_WINDOWS
include windows.inc
endif

.pragma comment(lib, Ws2_32)

SOCKET			typedef UINT_PTR

ifndef FD_SETSIZE
FD_SETSIZE		equ 64
endif

fd_set			STRUC
fd_count		UINT ?
fd_array		SOCKET FD_SETSIZE dup(?)
fd_set			ENDS

__WSAFDIsSet		proto :SOCKET, :ptr fd_set

FD_CLR macro fd, set
    pushad
    lea ebx,set
    mov eax,fd
    mov ecx,[ebx].fd_set.fd_count
    lea esi,[ebx].fd_set.fd_array
    mov edi,esi
    .while (ecx)
	.if (eax == [esi])
	    dec [ebx].fd_set.fd_count
	    add esi,4
	.endif
	movsd
	dec ecx
    .endw
    popad
    endm

FD_SET macro fd, set
    lea edx,set
    mov eax,fd
    mov ecx,[edx].fd_set.fd_count
    .if ecx < FD_SETSIZE
	mov [edx].fd_set.fd_array[ecx*4],eax
	inc [edx].fd_set.fd_count
    .endif
    endm

FD_ZERO macro set
    lea eax,set
    mov [eax].fd_set.fd_count, 0
    endm

FD_ISSET macro fd, set
    exitm<__WSAFDIsSet(fd, set)>
    endm

timeval STRUC
tv_sec	LONG ?
tv_usec LONG ?
timeval ENDS

timerisset macro tvp
    exitm<0>
    endm
timercmp macro tvp,uvp,comp
    exitm<0>
    endm
timerclear macro tvp
    exitm<0>
    endm

IOCPARM_MASK		equ 0x7f
IOC_VOID		equ 0x20000000
IOC_OUT			equ 0x40000000
IOC_IN			equ 0x80000000
IOC_INOUT		equ (IOC_IN OR IOC_OUT)
_IO macro x,y
    exitm<(IOC_VOID OR ((x) SHL 8) OR (y))>
    endm

_IOR macro x,y,t
    exitm<(IOC_OUT OR ((sizeof(t) AND IOCPARM_MASK) SHL 16) OR ((x) SHL 8) OR (y))>
    endm

_IOW macro x,y,t
    exitm<(IOC_IN OR ((sizeof(t) AND IOCPARM_MASK) SHL 16) OR ((x) SHL 8) OR (y))>
    endm

FIONREAD		equ _IOR('f', 127, ULONG)
FIONBIO			equ _IOW('f', 126, ULONG)
FIOASYNC		equ _IOW('f', 125, ULONG)

SIOCSHIWAT		equ _IOW('s',  0, ULONG)
SIOCGHIWAT		equ _IOR('s',  1, ULONG)
SIOCSLOWAT		equ _IOW('s',  2, ULONG)
SIOCGLOWAT		equ _IOR('s',  3, ULONG)
SIOCATMARK		equ _IOR('s',  7, ULONG)


hostent			STRUC
h_name			LPSTR ?
h_aliases		LPSTR ?
h_addrtype		dw ?
h_length		dw ?
h_addr_list		LPSTR ?
hostent			ENDS

netent			STRUC
n_name			LPSTR ?
n_aliases		LPSTR ?
n_addrtype		dw ?
n_net			dd ?
netent			ENDS

servent			STRUC
s_name			LPSTR ?
s_aliases		LPSTR ?
ifdef _WIN64
s_proto			LPSTR ?
s_port			dw ?
else
s_port			dw ?
s_proto			LPSTR ?
endif
servent			ENDS

protoent		STRUC
p_name			LPSTR ?
p_aliases		LPSTR ?
p_proto			dw ?
protoent		ENDS


IPPROTO_IP		equ 0
IPPROTO_ICMP		equ 1
IPPROTO_IGMP		equ 2
IPPROTO_GGP		equ 3
IPPROTO_TCP		equ 6
IPPROTO_PUP		equ 12
IPPROTO_UDP		equ 17
IPPROTO_IDP		equ 22
IPPROTO_ND		equ 77

IPPROTO_RAW		equ 255
IPPROTO_MAX		equ 256

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

IPPORT_TFTP		equ 69
IPPORT_RJE		equ 77
IPPORT_FINGER		equ 79
IPPORT_TTYLINK		equ 87
IPPORT_SUPDUP		equ 95

IPPORT_EXECSERVER	equ 512
IPPORT_LOGINSERVER	equ 513
IPPORT_CMDSERVER	equ 514
IPPORT_EFSSERVER	equ 520

IPPORT_BIFFUDP		equ 512
IPPORT_WHOSERVER	equ 513
IPPORT_ROUTESERVER	equ 520

IPPORT_RESERVED		equ 1024

IMPLINK_IP		equ 155
IMPLINK_LOWEXPER	equ 156
IMPLINK_HIGHEXPER	equ 158

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
;s_addr			equ <S_un.S_addr>
;s_host			equ <S_un.S_un_b.s_b2>
;s_net			equ <S_un.S_un_b.s_b1>
;s_imp			equ <S_un.S_un_w.s_w2>
;s_impno		equ <S_un.S_un_b.s_b4>
;s_lh			equ <S_un.S_un_b.s_b3>
in_addr			ENDS

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

INADDR_ANY		equ 0x00000000
INADDR_LOOPBACK		equ 0x7f000001
INADDR_BROADCAST	equ 0xffffffff
INADDR_NONE		equ 0xffffffff

sockaddr_in		STRUC
sin_family		dw ?
sin_port		dw ?
sin_addr		in_addr <>
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

IP_OPTIONS		equ 1
IP_MULTICAST_IF		equ 2
IP_MULTICAST_TTL	equ 3
IP_MULTICAST_LOOP	equ 4
IP_ADD_MEMBERSHIP	equ 5
IP_DROP_MEMBERSHIP	equ 6
IP_TTL			equ 7
IP_TOS			equ 8
IP_DONTFRAGMENT		equ 9


IP_DEFAULT_MULTICAST_TTL equ 1
IP_DEFAULT_MULTICAST_LOOP equ 1
IP_MAX_MEMBERSHIPS	equ 20

ip_mreq			STRUC
imr_multiaddr		in_addr <>	; IP multicast address of group
imr_interface		in_addr <>	; local IP address of interface
ip_mreq			ENDS


INVALID_SOCKET		equ <( NOT 0)>
SOCKET_ERROR		equ (-1)

SOCK_STREAM		equ 1
SOCK_DGRAM		equ 2
SOCK_RAW		equ 3
SOCK_RDM		equ 4
SOCK_SEQPACKET		equ 5

SO_DEBUG		equ 0x0001
SO_ACCEPTCONN		equ 0x0002
SO_REUSEADDR		equ 0x0004
SO_KEEPALIVE		equ 0x0008
SO_DONTROUTE		equ 0x0010
SO_BROADCAST		equ 0x0020
SO_USELOOPBACK		equ 0x0040
SO_LINGER		equ 0x0080
SO_OOBINLINE		equ 0x0100

SO_DONTLINGER		equ <not SO_LINGER>

SO_SNDBUF		equ 0x1001
SO_RCVBUF		equ 0x1002
SO_SNDLOWAT		equ 0x1003
SO_RCVLOWAT		equ 0x1004
SO_SNDTIMEO		equ 0x1005
SO_RCVTIMEO		equ 0x1006
SO_ERROR		equ 0x1007
SO_TYPE			equ 0x1008

SO_CONNDATA		equ 0x7000
SO_CONNOPT		equ 0x7001
SO_DISCDATA		equ 0x7002
SO_DISCOPT		equ 0x7003
SO_CONNDATALEN		equ 0x7004
SO_CONNOPTLEN		equ 0x7005
SO_DISCDATALEN		equ 0x7006
SO_DISCOPTLEN		equ 0x7007

SO_OPENTYPE		equ 0x7008

SO_SYNCHRONOUS_ALERT	equ 0x10
SO_SYNCHRONOUS_NONALERT equ 0x20

SO_MAXDG		equ 0x7009
SO_MAXPATHDG		equ 0x700A
SO_UPDATE_ACCEPT_CONTEXT equ 0x700B
SO_CONNECT_TIME		equ 0x700C

TCP_NODELAY		equ 0x0001
TCP_BSDURGENT		equ 0x7000

AF_UNSPEC		equ 0
AF_UNIX			equ 1
AF_INET			equ 2
AF_IMPLINK		equ 3
AF_PUP			equ 4
AF_CHAOS		equ 5
AF_IPX			equ 6
AF_NS			equ 6
AF_ISO			equ 7
AF_OSI			equ AF_ISO
AF_ECMA			equ 8
AF_DATAKIT		equ 9
AF_CCITT		equ 10
AF_SNA			equ 11
AF_DECnet		equ 12
AF_DLI			equ 13
AF_LAT			equ 14
AF_HYLINK		equ 15
AF_APPLETALK		equ 16
AF_NETBIOS		equ 17
AF_VOICEVIEW		equ 18
AF_FIREFOX		equ 19
AF_UNKNOWN1		equ 20
AF_BAN			equ 21

AF_MAX			equ 22

sockaddr		STRUC
sa_family		dw ?
sa_data			db 14 dup(?)
sockaddr		ENDS

sockproto		STRUC
sp_family		dw ?
sp_protocol		dw ?
sockproto		ENDS

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

linger			STRUC
l_onoff			dw ?
l_linger		dw ?
linger			ENDS

SOL_SOCKET		equ 0xffff

SOMAXCONN		equ 5

MSG_OOB			equ 0x1
MSG_PEEK		equ 0x2
MSG_DONTROUTE		equ 0x4

MSG_MAXIOVLEN		equ 16

MSG_PARTIAL		equ 0x8000

MAXGETHOSTSTRUCT	equ 1024

FD_READ			equ 0x01
FD_WRITE		equ 0x02
FD_OOB			equ 0x04
FD_ACCEPT		equ 0x08
FD_CONNECT		equ 0x10
FD_CLOSE		equ 0x20

WSABASEERR		equ 10000
WSAEINTR		equ (WSABASEERR+4)
WSAEBADF		equ (WSABASEERR+9)
WSAEACCES		equ (WSABASEERR+13)
WSAEFAULT		equ (WSABASEERR+14)
WSAEINVAL		equ (WSABASEERR+22)
WSAEMFILE		equ (WSABASEERR+24)

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

WSASYSNOTREADY		equ (WSABASEERR+91)
WSAVERNOTSUPPORTED	equ (WSABASEERR+92)
WSANOTINITIALISED	equ (WSABASEERR+93)


h_errno			equ <WSAGetLastError()>

WSAHOST_NOT_FOUND	equ (WSABASEERR+1001)
HOST_NOT_FOUND		equ WSAHOST_NOT_FOUND

WSATRY_AGAIN		equ (WSABASEERR+1002)
TRY_AGAIN		equ WSATRY_AGAIN

WSANO_RECOVERY		equ (WSABASEERR+1003)
NO_RECOVERY		equ WSANO_RECOVERY

WSANO_DATA		equ (WSABASEERR+1004)
NO_DATA			equ WSANO_DATA

WSANO_ADDRESS		equ WSANO_DATA
NO_ADDRESS		equ WSANO_ADDRESS

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


accept proto WINAPI \
		 _addr: ptr sockaddr,
	       addrlen: ptr SINT

;int
bind proto WINAPI \
		     s: SOCKET,
		 _addr: ptr sockaddr,
	       namelen: SINT

;int
closesocket proto WINAPI \
		     s: SOCKET

;int
connect proto WINAPI \
		     s: SOCKET,
		  name: ptr sockaddr,
	       namelen: SINT

;int
ioctlsocket proto WINAPI \
		     s: SOCKET,
		   cmd: LONG,
		  argp: ptr ULONG

;int
getpeername proto WINAPI \
		     s: SOCKET,
		  name: ptr sockaddr,
	       namelen: ptr SINT

;int
getsockname proto WINAPI \
		     s: SOCKET,
		  name: ptr sockaddr,
	       namelen: ptr SINT

;int
getsockopt proto WINAPI \
		     s: SOCKET,
		 level: SINT,
	       optname: SINT,
		optval: LPSTR,
		optlen: ptr SINT

;ULONG
htonl proto WINAPI \
	      hostlong: ULONG

WORD  htons(WORD hostshort);

;ULONG
inet_addr proto WINAPI \
		    cp: LPSTR

;LPSTR
inet_ntoa proto WINAPI \
		      : in_addr

;int
listen proto WINAPI \
		     s: SOCKET,
	       backlog: SINT

;ULONG
ntohl proto WINAPI \
	       netlong: ULONG

;WORD
ntohs proto WINAPI \
	      netshort: WORD

;int
recv proto WINAPI \
		     s: SOCKET,
		   buf: LPSTR,
		   len: SINT,
		 flags: SINT

;int
recvfrom proto WINAPI \
		     s: SOCKET,
		   buf: LPSTR,
		   len: SINT,
		 flags: SINT,
		  from: ptr sockaddr,
	       fromlen: ptr SINT

;int
select proto WINAPI \
		  nfds: SINT,
	       readfds: ptr fd_set,
	      writefds: ptr fd_set,
	     exceptfds: ptr fd_set,
	       timeout: ptr timeval

;int
send proto WINAPI \
		     s: SOCKET,
		   buf: LPSTR,
		   len: SINT,
		 flags: SINT

;int
sendto proto WINAPI \
		     s: SOCKET,
		   buf: LPSTR,
		   len: SINT,
		 flags: SINT,
		    to: ptr sockaddr,
		 tolen: SINT

;int
setsockopt proto WINAPI \
		     s: SOCKET,
		 level: SINT,
	       optname: SINT,
		optval: LPSTR,
		optlen: SINT

;int
shutdown proto WINAPI \
		     s: SOCKET,
		   how: SINT

;SOCKET
socket proto WINAPI \
		    af: SINT,
		  type: SINT,
	      protocol: SINT


;hostent *
gethostbyaddr proto WINAPI \
		 _addr: LPSTR,
		   len: SINT,
		  type: SINT

hostent *
gethostbyname proto WINAPI \
		  name: LPSTR

;int
gethostname proto WINAPI \
		  name: LPSTR,
	       namelen: SINT

;servent *
getservbyport proto WINAPI \
		  port: SINT,
		_proto: LPSTR

;servent *
getservbyname proto WINAPI \
		  name: LPSTR,
		_proto: LPSTR

;protoent *
getprotobynumber proto WINAPI \
		_proto: SINT

;protoent *
getprotobyname proto WINAPI \
		  name: LPSTR


;int
WSAStartup proto WINAPI \
      wVersionRequired: WORD,
	     lpWSAData: LPWSADATA

;int

;void
WSASetLastError proto WINAPI \
		iError: SINT

;int

;BOOL

;int

FARPROC
WSASetBlockingHook proto WINAPI \
	   lpBlockFunc: FARPROC

;int

;HANDLE
WSAAsyncGetServByName proto WINAPI \
		  hWnd: HWND,
		  wMsg: UINT,
		  name: LPSTR,
		_proto: LPSTR,
		   buf: LPSTR,
		buflen: SINT

;HANDLE
WSAAsyncGetServByPort proto WINAPI \
		  hWnd: HWND,
		  wMsg: UINT,
		  port: SINT,
		_proto: LPSTR,
		   buf: LPSTR,
		buflen: SINT

;HANDLE
WSAAsyncGetProtoByName proto WINAPI \
		  hWnd: HWND,
		  wMsg: UINT,
		  name: LPSTR,
		   buf: LPSTR,
		buflen: SINT

;HANDLE
WSAAsyncGetProtoByNumber proto WINAPI \
		  hWnd: HWND,
		  wMsg: UINT,
		number: SINT,
		   buf: LPSTR,
		buflen: SINT

;HANDLE
WSAAsyncGetHostByName proto WINAPI \
		  hWnd: HWND,
		  wMsg: UINT,
		  name: LPSTR,
		   buf: LPSTR,
		buflen: SINT

;HANDLE
WSAAsyncGetHostByAddr proto WINAPI \
		  hWnd: HWND,
		  wMsg: UINT,
		 _addr: LPSTR,
		   len: SINT,
		  type: SINT,
		   buf: LPSTR,
		buflen: SINT

;int
WSACancelAsyncRequest proto WINAPI \
      hAsyncTaskHandle: HANDLE

;int
WSAAsyncSelect proto WINAPI \
		     s: SOCKET,
		  hWnd: HWND,
		  wMsg: UINT,
		lEvent: LONG

;int
WSARecvEx proto WINAPI \
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
TransmitFile proto WINAPI \
	       hSocket: SOCKET,
		 hFile: HANDLE,
 nNumberOfBytesToWrite: DWORD,
 nNumberOfBytesPerSend: DWORD,
	  lpOverlapped: LPOVERLAPPED,
     lpTransmitBuffers: LPTRANSMIT_FILE_BUFFERS,
	    dwReserved: DWORD

;BOOL
AcceptEx proto WINAPI \
	 sListenSocket: SOCKET,
	 sAcceptSocket: SOCKET,
	lpOutputBuffer: PVOID,
   dwReceiveDataLength: DWORD,
  dwLocalAddressLength: DWORD,
 dwRemoteAddressLength: DWORD,
     lpdwBytesReceived: LPDWORD,
	  lpOverlapped: LPOVERLAPPED

;VOID
GetAcceptExSockaddrs WINAPI \
	lpOutputBuffer: PVOID,
   dwReceiveDataLength: DWORD,
  dwLocalAddressLength: DWORD,
 dwRemoteAddressLength: DWORD,
	 LocalSockaddr: PVOID,
   LocalSockaddrLength: LPINT,
	RemoteSockaddr: PVOID,
  RemoteSockaddrLength: LPINT

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

WSAMAKEASYNCREPLY macro buflen,error
    exitm<MAKELONG(buflen,error)>
    endm
WSAMAKESELECTREPLY macro event,error
    exitm<MAKELONG(event,error)>
    endm
WSAGETASYNCBUFLEN macro lParam
    exitm<LOWORD(lParam)>
    endm
WSAGETASYNCERROR macro lParam
    exitm<HIWORD(lParam)>
    endm
WSAGETSELECTEVENT macro lParam
    exitm<LOWORD(lParam)>
    endm
WSAGETSELECTERROR macro lParam
    exitm<HIWORD(lParam)>
    endm

endif
