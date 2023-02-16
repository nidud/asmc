ifndef _MSWSOCK_
define _MSWSOCK_
ifndef __LIBC_INC
 include libc.inc
endif

include winapifamily.inc
include mswsockdef.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
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
endif

SO_MAXDG		equ 0x7009
SO_MAXPATHDG		equ 0x700A
SO_UPDATE_ACCEPT_CONTEXT equ 0x700B
SO_CONNECT_TIME		equ 0x700C
if(_WIN32_WINNT GE 0x0501)
SO_UPDATE_CONNECT_CONTEXT equ 0x7010
endif

TCP_BSDURGENT		equ 0x7000

SIO_UDP_CONNRESET	equ _WSAIOW(IOC_VENDOR,12)
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
if((_WIN32_WINNT LT 0x0600) and (_WIN32_WINNT GE 0x0501))
SIO_SOCKET_CLOSE_NOTIFY equ _WSAIOW(IOC_VENDOR,13)
endif
endif
SIO_UDP_NETRESET	equ _WSAIOW(IOC_VENDOR,15)

ifndef SOCKET
SOCKET			typedef UINT_PTR
endif
;int
WSARecvEx proto WINAPI \
		     s: SOCKET,
		   buf: LPSTR,
		   len: SINT,
		 flags: ptr SINT

TRANSMIT_FILE_BUFFERS	STRUC
Head			LPVOID ?
HeadLength		dd ?
Tail			LPVOID ?
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
GetAcceptExSockaddrs proto WINAPI \
	lpOutputBuffer: PVOID,
   dwReceiveDataLength: DWORD,
  dwLocalAddressLength: DWORD,
 dwRemoteAddressLength: DWORD,
	 LocalSockaddr: ptr sockaddr,
   LocalSockaddrLength: LPINT,
	RemoteSockaddr: ptr sockaddr,
  RemoteSockaddrLength: LPINT


CALLBACK(LPFN_TRANSMITFILE, :SOCKET, :HANDLE, :DWORD, :DWORD, :LPOVERLAPPED, :LPTRANSMIT_FILE_BUFFERS, :DWORD)
define WSAID_TRANSMITFILE <{0xb5367df0,0xcbac,0x11cf,{0x95,0xca,0x00,0x80,0x5f,0x48,0xa1,0x92}}>
CALLBACK(LPFN_ACCEPTEX, :SOCKET, :SOCKET, :PVOID, :DWORD, :DWORD, :DWORD, :LPDWORD, :LPOVERLAPPED)
define WSAID_ACCEPTEX <{0xb5367df1,0xcbac,0x11cf,{0x95,0xca,0x00,0x80,0x5f,0x48,0xa1,0x92}}>
CALLBACK(LPFN_GETACCEPTEXSOCKADDRS, :PVOID, :DWORD, :DWORD, :DWORD, :ptr, :LPINT, :ptr, :LPINT)
define WSAID_GETACCEPTEXSOCKADDRS <{0xb5367df2,0xcbac,0x11cf,{0x95,0xca,0x00,0x80,0x5f,0x48,0xa1,0x92}}>

endif

