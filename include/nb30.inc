ifndef __LIBC_INC
 include libc.inc
endif

.xlist
;;
;;  This module contains the definitions for portable NetBIOS 3.0
;;  support.
;;
ifndef NCB_INCLUDED
NCB_INCLUDED equ 1

IFDEF __PE__
option	dllimport:<netapi32>
ENDIF

;;***************************************************************
;;								*
;;		Data structure templates			*
;;								*
;;**************************************************************

NCBNAMSZ		equ 16	  ;; absolute length of a net name
MAX_LANA		equ 254	   ;; lana's in range 0 to MAX_LANA inclusive

;;
;; Network Control Block
;;

NCB			STRUC
ncb_command		UCHAR ? ;; command code
ncb_retcode		UCHAR ? ;; return code
ncb_lsn			UCHAR ? ;; local session number
ncb_num			UCHAR ? ;; number of our network name
ncb_buffer		PUCHAR ?	;; address of message buffer
ncb_length		dw ?	;; size of message buffer
ncb_callname		UCHAR NCBNAMSZ dup(?) ;; blank-padded name of remote
ncb_name		UCHAR NCBNAMSZ dup(?) ;; our blank-padded netname
ncb_rto			UCHAR ? ;; rcv timeout/retry count
ncb_sto			UCHAR ? ;; send timeout/sys timeout
ncb_post		PVOID ? ;; POST routine address
ncb_lana_num		UCHAR ? ;; lana (adapter) number
ncb_cmd_cplt		UCHAR ? ;; 0xff => commmand pending
ncb_reserve		UCHAR 10 dup(?) ;; reserved, used by BIOS
ncb_event		HANDLE ?	;; HANDLE to Win32 event which
;; will be set to the signalled
;; state when an ASYNCH command
;; completes
NCB			ENDS
PNCB			typedef ptr NCB

;;
;;  Structure returned to the NCB command NCBASTAT is ADAPTER_STATUS followed
;;  by an array of NAME_BUFFER structures.
;;

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
_name			UCHAR NCBNAMSZ dup(?)
name_num		UCHAR ?
name_flags		UCHAR ?
NAME_BUFFER		ENDS
PNAME_BUFFER		typedef ptr NAME_BUFFER

;;  values for name_flags bits.

NAME_FLAGS_MASK		equ 0x87

GROUP_NAME		equ 0x80
UNIQUE_NAME		equ 0x00

REGISTERING		equ 0x00
REGISTERED		equ 0x04
DEREGISTERED		equ 0x05
DUPLICATE		equ 0x06
DUPLICATE_DEREG		equ 0x07

;;
;;  Structure returned to the NCB command NCBSSTAT is SESSION_HEADER followed
;;  by an array of SESSION_BUFFER structures. If the NCB_NAME starts with an
;;  asterisk then an array of these structures is returned containing the
;;  status for all names.
;;

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

;;  Values for state

LISTEN_OUTSTANDING	equ 0x01
CALL_PENDING		equ 0x02
SESSION_ESTABLISHED	equ 0x03
HANGUP_PENDING		equ 0x04
HANGUP_COMPLETE		equ 0x05
SESSION_ABORTED		equ 0x06

;;
;;  Structure returned to the NCB command NCBENUM.
;;
;;  On a system containing lana's 0, 2 and 3, a structure with
;;  length =3, lana[0]=0, lana[1]=2 and lana[2]=3 will be returned.
;;

LANA_ENUM		STRUC
_length			UCHAR ? ;;  Number of valid entries in lana[]
lana			UCHAR MAX_LANA+1 dup(?)
LANA_ENUM		ENDS
PLANA_ENUM		typedef ptr LANA_ENUM

;;
;;  Structure returned to the NCB command NCBFINDNAME is FIND_NAME_HEADER followed
;;  by an array of FIND_NAME_BUFFER structures.
;;

FIND_NAME_HEADER	STRUC
node_count		dw ?
reserved		UCHAR ?
unique_group		UCHAR ?
FIND_NAME_HEADER	ENDS
PFIND_NAME_HEADER	typedef ptr FIND_NAME_HEADER

FIND_NAME_BUFFER	STRUC
_length			UCHAR ?
access_control		UCHAR ?
frame_control		UCHAR ?
destination_addr	UCHAR 6 dup(?)
source_addr		UCHAR 6 dup(?)
routing_info		UCHAR 18 dup(?)
FIND_NAME_BUFFER	ENDS
PFIND_NAME_BUFFER	typedef ptr FIND_NAME_BUFFER

;;
;;  Structure provided with NCBACTION. The purpose of NCBACTION is to provide
;;  transport specific extensions to netbios.
;;

ACTION_HEADER		STRUC
transport_id		ULONG ?
action_code		USHORT ?
reserved		USHORT ?
ACTION_HEADER		ENDS
PACTION_HEADER		typedef ptr ACTION_HEADER

;;  Values for transport_id

ALL_TRANSPORTS		equ <"M\0\0\0">
MS_NBF			equ <"MNBF">


;;***************************************************************
;;								*
;;		Special values and constants			*
;;								*
;;**************************************************************

;;
;;	NCB Command codes
;;

NCBCALL			equ 0x10	    ;; NCB CALL
NCBLISTEN		equ 0x11	    ;; NCB LISTEN
NCBHANGUP		equ 0x12	    ;; NCB HANG UP
NCBSEND			equ 0x14	    ;; NCB SEND
NCBRECV			equ 0x15	    ;; NCB RECEIVE
NCBRECVANY		equ 0x16	    ;; NCB RECEIVE ANY
NCBCHAINSEND		equ 0x17	    ;; NCB CHAIN SEND
NCBDGSEND		equ 0x20	    ;; NCB SEND DATAGRAM
NCBDGRECV		equ 0x21	    ;; NCB RECEIVE DATAGRAM
NCBDGSENDBC		equ 0x22	    ;; NCB SEND BROADCAST DATAGRAM
NCBDGRECVBC		equ 0x23	    ;; NCB RECEIVE BROADCAST DATAGRAM
NCBADDNAME		equ 0x30	    ;; NCB ADD NAME
NCBDELNAME		equ 0x31	    ;; NCB DEETE NAME
NCBRESET		equ 0x32	    ;; NCB RESET
NCBASTAT		equ 0x33	    ;; NCB ADAPTER STATUS
NCBSSTAT		equ 0x34	    ;; NCB SESSION STATUS
NCBCANCEL		equ 0x35	    ;; NCB CANCE
NCBADDGRNAME		equ 0x36	    ;; NCB ADD GROUP NAME
NCBENUM			equ 0x37	    ;; NCB ENUMERATE LANA NUMBERS
NCBUNLINK		equ 0x70	    ;; NCB UNLINK
NCBSENDNA		equ 0x71	    ;; NCB SEND NO ACK
NCBCHAINSENDNA		equ 0x72	    ;; NCB CHAIN SEND NO ACK
NCBLANSTALERT		equ 0x73	    ;; NCB LAN STATUS AERT
NCBACTION		equ 0x77	    ;; NCB ACTION
NCBFINDNAME		equ 0x78	    ;; NCB FIND NAME
NCBTRACE		equ 0x79	    ;; NCB TRACE


ASYNCH			equ 0x80	    ;; high bit set EQ asynchronous

;;
;;	NCB Return codes
;;

NRC_GOODRET		equ 0x00    ;; good return
;; also returned when ASYNCH request accepted
NRC_BUFLEN		equ 0x01    ;; illegal buffer length
NRC_ILLCMD		equ 0x03    ;; illegal command
NRC_CMDTMO		equ 0x05    ;; command timed out
NRC_INCOMP		equ 0x06    ;; message incomplete, issue another command
NRC_BADDR		equ 0x07    ;; illegal buffer address
NRC_SNUMOUT		equ 0x08    ;; session number out of range
NRC_NORES		equ 0x09    ;; no resource available
NRC_SCLOSED		equ 0x0a    ;; session closed
NRC_CMDCAN		equ 0x0b    ;; command cancelled
NRC_DUPNAME		equ 0x0d    ;; duplicate name
NRC_NAMTFUL		equ 0x0e    ;; name table full
NRC_ACTSES		equ 0x0f    ;; no deletions, name has active sessions
NRC_LOCTFUL		equ 0x11    ;; local session table full
NRC_REMTFUL		equ 0x12    ;; remote session table full
NRC_ILLNN		equ 0x13    ;; illegal name number
NRC_NOCALL		equ 0x14    ;; no callname
NRC_NOWILD		equ 0x15    ;; cannot put * in NCB_NAME
NRC_INUSE		equ 0x16    ;; name in use on remote adapter
NRC_NAMERR		equ 0x17    ;; name deleted
NRC_SABORT		equ 0x18    ;; session ended abnormally
NRC_NAMCONF		equ 0x19    ;; name conflict detected
NRC_IFBUSY		equ 0x21    ;; interface busy, IRET before retrying
NRC_TOOMANY		equ 0x22    ;; too many commands outstanding, retry later
NRC_BRIDGE		equ 0x23    ;; ncb_lana_num field invalid
NRC_CANOCCR		equ 0x24    ;; command completed while cancel occurring
NRC_CANCEL		equ 0x26    ;; command not valid to cancel
NRC_DUPENV		equ 0x30    ;; name defined by anther local process
NRC_ENVNOTDEF		equ 0x34    ;; environment undefined. RESET required
NRC_OSRESNOTAV		equ 0x35    ;; required OS resources exhausted
NRC_MAXAPPS		equ 0x36    ;; max number of applications exceeded
NRC_NOSAPS		equ 0x37    ;; no saps available for netbios
NRC_NORESOURCES		equ 0x38    ;; requested resources are not available
NRC_INVADDRESS		equ 0x39    ;; invalid ncb address or length GT segment
NRC_INVDDID		equ 0x3B    ;; invalid NCB DDID
NRC_LOCKFAIL		equ 0x3C    ;; lock of user area failed
NRC_OPENERR		equ 0x3f    ;; NETBIOS not loaded
NRC_SYSTEM		equ 0x40    ;; system error

NRC_PENDING		equ 0xff    ;; asynchronous command is not yet finished

;;***************************************************************
;;								*
;;		main user entry point for NetBIOS 3.0		*
;;								*
;; Usage: result = Netbios( pncb );				*
;;**************************************************************

;UCHAR
Netbios proto _CType pncb:PNCB

;;***************************************************************
;;								*
;;		Prefix for callback routines			*
;;								*
;; Usage in a declaration: NCB_POST MyPostRoutine( PNCB pncb ); *
;;**************************************************************

NCB_POST		equ <>;<void CALLBACK>

endif ;; NCB_INCLUDED

.list
