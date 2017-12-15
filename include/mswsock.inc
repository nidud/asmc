ifndef __LIBC_INC
 include libc.inc
endif
.xlist
ifndef _MSWSOCK_
_MSWSOCK_ equ 1

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

TCP_BSDURGENT		equ 0x7000

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


;BOOL
CALLBACK(LPFN_TRANSMITFILE, :SOCKET, :HANDLE, :DWORD, :DWORD, :LPOVERLAPPED, :LPTRANSMIT_FILE_BUFFERS, :DWORD)
WSAID_TRANSMITFILE	equ <{0xb5367df0,0xcbac,0x11cf,{0x95,0xca,0x00,0x80,0x5f,0x48,0xa1,0x92}}>
;BOOL
CALLBACK(LPFN_ACCEPTEX, :SOCKET, :SOCKET, :PVOID, :DWORD, :DWORD, :DWORD, :LPDWORD, :LPOVERLAPPED)
WSAID_ACCEPTEX		equ <{0xb5367df1,0xcbac,0x11cf,{0x95,0xca,0x00,0x80,0x5f,0x48,0xa1,0x92}}>
;VOID
CALLBACK(LPFN_GETACCEPTEXSOCKADDRS, :PVOID, :DWORD, :DWORD, :DWORD, :ptr, :LPINT, :ptr, :LPINT)
WSAID_GETACCEPTEXSOCKADDRS equ <{0xb5367df2,0xcbac,0x11cf,{0x95,0xca,0x00,0x80,0x5f,0x48,0xa1,0x92}}>

endif

.list
