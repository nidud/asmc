ifndef __LIBC_INC
 include libc.inc
endif
ifndef NCB_INCLUDED
define NCB_INCLUDED

.pragma comment(lib, netapi32)

NCBNAMSZ		equ 16
MAX_LANA		equ 254

NCB			STRUC
ncb_command		UCHAR ?
ncb_retcode		UCHAR ?
ncb_lsn			UCHAR ?
ncb_num			UCHAR ?
ncb_buffer		PUCHAR ?
ncb_length		dw ?
ncb_callname		UCHAR NCBNAMSZ dup(?)
ncb_name		UCHAR NCBNAMSZ dup(?)
ncb_rto			UCHAR ?
ncb_sto			UCHAR ?
ncb_post		PVOID ?
ncb_lana_num		UCHAR ?
ncb_cmd_cplt		UCHAR ?
ncb_reserve		UCHAR 10 dup(?)
ncb_event		HANDLE ?
NCB			ENDS
PNCB			typedef ptr NCB

ADAPTER_STATUS		STRUC
adapter_address		UCHAR 6 dup(?)
rev_major		UCHAR ?
reserved0		UCHAR ?
adapter_type		UCHAR ?
rev_minor		UCHAR ?
duration		dw ?
frmr_recv		dw ?
frmr_xmit		dw ?
iframe_recv_err		dw ?
xmit_aborts		dw ?
xmit_success		dd ?
recv_success		dd ?
iframe_xmit_err		dw ?
recv_buff_unavail	dw ?
t1_timeouts		dw ?
ti_timeouts		dw ?
reserved1		dd ?
free_ncbs		dw ?
max_cfg_ncbs		dw ?
max_ncbs		dw ?
xmit_buf_unavail	dw ?
max_dgram_size		dw ?
pending_sess		dw ?
max_cfg_sess		dw ?
max_sess		dw ?
max_sess_pkt_size	dw ?
name_count		dw ?
ADAPTER_STATUS		ENDS
PADAPTER_STATUS		typedef ptr ADAPTER_STATUS

NAME_BUFFER		STRUC
name			UCHAR NCBNAMSZ dup(?)
name_num		UCHAR ?
name_flags		UCHAR ?
NAME_BUFFER		ENDS
PNAME_BUFFER		typedef ptr NAME_BUFFER

NAME_FLAGS_MASK		equ 0x87

GROUP_NAME		equ 0x80
UNIQUE_NAME		equ 0x00

REGISTERING		equ 0x00
REGISTERED		equ 0x04
DEREGISTERED		equ 0x05
DUPLICATE		equ 0x06
DUPLICATE_DEREG		equ 0x07

SESSION_HEADER		STRUC
sess_name		UCHAR ?
num_sess		UCHAR ?
rcv_dg_outstanding	UCHAR ?
rcv_any_outstanding	UCHAR ?
SESSION_HEADER		ENDS
PSESSION_HEADER		typedef ptr SESSION_HEADER

SESSION_BUFFER		STRUC
lsn			UCHAR ?
state			UCHAR ?
local_name		UCHAR NCBNAMSZ dup(?)
remote_name		UCHAR NCBNAMSZ dup(?)
rcvs_outstanding	UCHAR ?
sends_outstanding	UCHAR ?
SESSION_BUFFER		ENDS
PSESSION_BUFFER		typedef ptr SESSION_BUFFER

LISTEN_OUTSTANDING	equ 0x01
CALL_PENDING		equ 0x02
SESSION_ESTABLISHED	equ 0x03
HANGUP_PENDING		equ 0x04
HANGUP_COMPLETE		equ 0x05
SESSION_ABORTED		equ 0x06

LANA_ENUM		STRUC
length			UCHAR ?
lana			UCHAR MAX_LANA+1 dup(?)
LANA_ENUM		ENDS
PLANA_ENUM		typedef ptr LANA_ENUM

FIND_NAME_HEADER	STRUC
node_count		dw ?
reserved		UCHAR ?
unique_group		UCHAR ?
FIND_NAME_HEADER	ENDS
PFIND_NAME_HEADER	typedef ptr FIND_NAME_HEADER

FIND_NAME_BUFFER	STRUC
length			UCHAR ?
access_control		UCHAR ?
frame_control		UCHAR ?
destination_addr	UCHAR 6 dup(?)
source_addr		UCHAR 6 dup(?)
routing_info		UCHAR 18 dup(?)
FIND_NAME_BUFFER	ENDS
PFIND_NAME_BUFFER	typedef ptr FIND_NAME_BUFFER

ACTION_HEADER		STRUC
transport_id		ULONG ?
action_code		USHORT ?
reserved		USHORT ?
ACTION_HEADER		ENDS
PACTION_HEADER		typedef ptr ACTION_HEADER

ALL_TRANSPORTS		equ <"M\0\0\0">
MS_NBF			equ <"MNBF">

NCBCALL			equ 0x10
NCBLISTEN		equ 0x11
NCBHANGUP		equ 0x12
NCBSEND			equ 0x14
NCBRECV			equ 0x15
NCBRECVANY		equ 0x16
NCBCHAINSEND		equ 0x17
NCBDGSEND		equ 0x20
NCBDGRECV		equ 0x21
NCBDGSENDBC		equ 0x22
NCBDGRECVBC		equ 0x23
NCBADDNAME		equ 0x30
NCBDELNAME		equ 0x31
NCBRESET		equ 0x32
NCBASTAT		equ 0x33
NCBSSTAT		equ 0x34
NCBCANCEL		equ 0x35
NCBADDGRNAME		equ 0x36
NCBENUM			equ 0x37
NCBUNLINK		equ 0x70
NCBSENDNA		equ 0x71
NCBCHAINSENDNA		equ 0x72
NCBLANSTALERT		equ 0x73
NCBACTION		equ 0x77
NCBFINDNAME		equ 0x78
NCBTRACE		equ 0x79


ASYNCH			equ 0x80


NRC_GOODRET		equ 0x00
NRC_BUFLEN		equ 0x01
NRC_ILLCMD		equ 0x03
NRC_CMDTMO		equ 0x05
NRC_INCOMP		equ 0x06
NRC_BADDR		equ 0x07
NRC_SNUMOUT		equ 0x08
NRC_NORES		equ 0x09
NRC_SCLOSED		equ 0x0a
NRC_CMDCAN		equ 0x0b
NRC_DUPNAME		equ 0x0d
NRC_NAMTFUL		equ 0x0e
NRC_ACTSES		equ 0x0f
NRC_LOCTFUL		equ 0x11
NRC_REMTFUL		equ 0x12
NRC_ILLNN		equ 0x13
NRC_NOCALL		equ 0x14
NRC_NOWILD		equ 0x15
NRC_INUSE		equ 0x16
NRC_NAMERR		equ 0x17
NRC_SABORT		equ 0x18
NRC_NAMCONF		equ 0x19
NRC_IFBUSY		equ 0x21
NRC_TOOMANY		equ 0x22
NRC_BRIDGE		equ 0x23
NRC_CANOCCR		equ 0x24
NRC_CANCEL		equ 0x26
NRC_DUPENV		equ 0x30
NRC_ENVNOTDEF		equ 0x34
NRC_OSRESNOTAV		equ 0x35
NRC_MAXAPPS		equ 0x36
NRC_NOSAPS		equ 0x37
NRC_NORESOURCES		equ 0x38
NRC_INVADDRESS		equ 0x39
NRC_INVDDID		equ 0x3B
NRC_LOCKFAIL		equ 0x3C
NRC_OPENERR		equ 0x3f
NRC_SYSTEM		equ 0x40

NRC_PENDING		equ 0xff

;UCHAR
Netbios proto WINAPI pncb:PNCB

NCB_POST		equ <>

endif
