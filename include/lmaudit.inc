ifndef _LMAUDIT_
define _LMAUDIT_

ifndef _LMHLOGDEFINED_
define _LMHLOGDEFINED_

HLOG			STRUC
time			dd ?
last_flags		dd ?
offset			dd ?
rec_offset		dd ?
HLOG			ENDS
PHLOG			typedef ptr HLOG
LPHLOG			typedef ptr HLOG

LOGFLAGS_FORWARD	equ 0
LOGFLAGS_BACKWARD	equ 0x1
LOGFLAGS_SEEK		equ 0x2

endif

NetAuditClear proto WINAPI :LPCWSTR, :LPCWSTR, :LPCWSTR
NetAuditRead proto WINAPI :LPCWSTR, :LPCWSTR, :LPHLOG, :DWORD, :LPDWORD, :DWORD, :DWORD, :ptr, :DWORD, :LPDWORD, :LPDWORD
NetAuditWrite proto WINAPI :DWORD, :LPBYTE, :DWORD, :LPCWSTR, :LPBYTE

AUDIT_ENTRY		STRUC
ae_len			dd ?
ae_reserved		dd ?
ae_time			dd ?
ae_type			dd ?
ae_data_offset		dd ?
ae_data_size		dd ?
AUDIT_ENTRY		ENDS
PAUDIT_ENTRY		typedef ptr AUDIT_ENTRY
LPAUDIT_ENTRY		typedef ptr AUDIT_ENTRY

REVISED_AUDIT_ENTRY_STRUCT equ 1

_AE_SRVSTATUS		STRUC
ae_sv_status		dd ?
_AE_SRVSTATUS		ENDS
PAE_SRVSTATUS		typedef ptr _AE_SRVSTATUS
LPAE_SRVSTATUS		typedef ptr _AE_SRVSTATUS

_AE_SESSLOGON		STRUC
ae_so_compname		dd ?
ae_so_username		dd ?
ae_so_privilege		dd ?
_AE_SESSLOGON		ENDS
PAE_SESSLOGON		typedef ptr _AE_SESSLOGON
LPAE_SESSLOGON		typedef ptr _AE_SESSLOGON

_AE_SESSLOGOFF		STRUC
ae_sf_compname		dd ?
ae_sf_username		dd ?
ae_sf_reason		dd ?
_AE_SESSLOGOFF		ENDS
PAE_SESSLOGOFF		typedef ptr _AE_SESSLOGOFF
LPAE_SESSLOGOFF		typedef ptr _AE_SESSLOGOFF

_AE_SESSPWERR		STRUC
ae_sp_compname		dd ?
ae_sp_username		dd ?
_AE_SESSPWERR		ENDS
PAE_SESSPWERR		typedef ptr _AE_SESSPWERR
LPAE_SESSPWERR		typedef ptr _AE_SESSPWERR

_AE_CONNSTART		STRUC
ae_ct_compname		dd ?
ae_ct_username		dd ?
ae_ct_netname		dd ?
ae_ct_connid		dd ?
_AE_CONNSTART		ENDS
PAE_CONNSTART		typedef ptr _AE_CONNSTART
LPAE_CONNSTART		typedef ptr _AE_CONNSTART

_AE_CONNSTOP		STRUC
ae_cp_compname		dd ?
ae_cp_username		dd ?
ae_cp_netname		dd ?
ae_cp_connid		dd ?
ae_cp_reason		dd ?
_AE_CONNSTOP		ENDS
PAE_CONNSTOP		typedef ptr _AE_CONNSTOP
LPAE_CONNSTOP		typedef ptr _AE_CONNSTOP

_AE_CONNREJ		STRUC
ae_cr_compname		dd ?
ae_cr_username		dd ?
ae_cr_netname		dd ?
ae_cr_reason		dd ?
_AE_CONNREJ		ENDS
PAE_CONNREJ		typedef ptr _AE_CONNREJ
LPAE_CONNREJ		typedef ptr _AE_CONNREJ

_AE_RESACCESS		STRUC
ae_ra_compname		dd ?
ae_ra_username		dd ?
ae_ra_resname		dd ?
ae_ra_operation		dd ?
ae_ra_returncode	dd ?
ae_ra_restype		dd ?
ae_ra_fileid		dd ?
_AE_RESACCESS		ENDS
PAE_RESACCESS		typedef ptr _AE_RESACCESS
LPAE_RESACCESS		typedef ptr _AE_RESACCESS

_AE_RESACCESSREJ	STRUC
ae_rr_compname		dd ?
ae_rr_username		dd ?
ae_rr_resname		dd ?
ae_rr_operation		dd ?
_AE_RESACCESSREJ	ENDS
PAE_RESACCESSREJ	typedef ptr _AE_RESACCESSREJ
LPAE_RESACCESSREJ	typedef ptr _AE_RESACCESSREJ

_AE_CLOSEFILE		STRUC
ae_cf_compname		dd ?
ae_cf_username		dd ?
ae_cf_resname		dd ?
ae_cf_fileid		dd ?
ae_cf_duration		dd ?
ae_cf_reason		dd ?
_AE_CLOSEFILE		ENDS
PAE_CLOSEFILE		typedef ptr _AE_CLOSEFILE
LPAE_CLOSEFILE		typedef ptr _AE_CLOSEFILE

_AE_SERVICESTAT		STRUC
ae_ss_compname		dd ?
ae_ss_username		dd ?
ae_ss_svcname		dd ?
ae_ss_status		dd ?
ae_ss_code		dd ?
ae_ss_text		dd ?
ae_ss_returnval		dd ?
_AE_SERVICESTAT		ENDS
PAE_SERVICESTAT		typedef ptr _AE_SERVICESTAT
LPAE_SERVICESTAT	typedef ptr _AE_SERVICESTAT

_AE_ACLMOD		STRUC
ae_am_compname		dd ?
ae_am_username		dd ?
ae_am_resname		dd ?
ae_am_action		dd ?
ae_am_datalen		dd ?
_AE_ACLMOD		ENDS
PAE_ACLMOD		typedef ptr _AE_ACLMOD
LPAE_ACLMOD		typedef ptr _AE_ACLMOD

_AE_UASMOD		STRUC
ae_um_compname		dd ?
ae_um_username		dd ?
ae_um_resname		dd ?
ae_um_rectype		dd ?
ae_um_action		dd ?
ae_um_datalen		dd ?
_AE_UASMOD		ENDS
PAE_UASMOD		typedef ptr _AE_UASMOD
LPAE_UASMOD		typedef ptr _AE_UASMOD

_AE_NETLOGON		STRUC
ae_no_compname		dd ?
ae_no_username		dd ?
ae_no_privilege		dd ?
ae_no_authflags		dd ?
_AE_NETLOGON		ENDS
PAE_NETLOGON		typedef ptr _AE_NETLOGON
LPAE_NETLOGON		typedef ptr _AE_NETLOGON

_AE_NETLOGOFF		STRUC
ae_nf_compname		dd ?
ae_nf_username		dd ?
ae_nf_reserved1		dd ?
ae_nf_reserved2		dd ?
_AE_NETLOGOFF		ENDS
PAE_NETLOGOFF		typedef ptr _AE_NETLOGOFF
LPAE_NETLOGOFF		typedef ptr _AE_NETLOGOFF

AE_ACCLIM		STRUC
ae_al_compname		dd ?
ae_al_username		dd ?
ae_al_resname		dd ?
ae_al_limit		dd ?
AE_ACCLIM		ENDS
PAE_ACCLIM		typedef ptr AE_ACCLIM
LPAE_ACCLIM		typedef ptr AE_ACCLIM

ACTION_LOCKOUT		equ 00
ACTION_ADMINUNLOCK	equ 01

_AE_LOCKOUT		STRUC
ae_lk_compname		dd ?
ae_lk_username		dd ?
ae_lk_action		dd ?
ae_lk_bad_pw_count	dd ?
_AE_LOCKOUT		ENDS
PAE_LOCKOUT		typedef ptr _AE_LOCKOUT
LPAE_LOCKOUT		typedef ptr _AE_LOCKOUT

AE_GENERIC		STRUC
ae_ge_msgfile		dd ?
ae_ge_msgnum		dd ?
ae_ge_params		dd ?
ae_ge_param1		dd ?
ae_ge_param2		dd ?
ae_ge_param3		dd ?
ae_ge_param4		dd ?
ae_ge_param5		dd ?
ae_ge_param6		dd ?
ae_ge_param7		dd ?
ae_ge_param8		dd ?
ae_ge_param9		dd ?
AE_GENERIC		ENDS
PAE_GENERIC		typedef ptr AE_GENERIC
LPAE_GENERIC		typedef ptr AE_GENERIC

AE_SRVSTATUS		equ 0
AE_SESSLOGON		equ 1
AE_SESSLOGOFF		equ 2
AE_SESSPWERR		equ 3
AE_CONNSTART		equ 4
AE_CONNSTOP		equ 5
AE_CONNREJ		equ 6
AE_RESACCESS		equ 7
AE_RESACCESSREJ		equ 8
AE_CLOSEFILE		equ 9
AE_SERVICESTAT		equ 11
AE_ACLMOD		equ 12
AE_UASMOD		equ 13
AE_NETLOGON		equ 14
AE_NETLOGOFF		equ 15
AE_NETLOGDENIED		equ 16
AE_ACCLIMITEXCD		equ 17
AE_RESACCESS2		equ 18
AE_ACLMODFAIL		equ 19
AE_LOCKOUT		equ 20
AE_GENERIC_TYPE		equ 21

AE_SRVSTART		equ 0
AE_SRVPAUSED		equ 1
AE_SRVCONT		equ 2
AE_SRVSTOP		equ 3

AE_GUEST		equ 0
AE_USER			equ 1
AE_ADMIN		equ 2

AE_NORMAL		equ 0
AE_USERLIMIT		equ 0
AE_GENERAL		equ 0
AE_ERROR		equ 1
AE_SESSDIS		equ 1
AE_BADPW		equ 1
AE_AUTODIS		equ 2
AE_UNSHARE		equ 2
AE_ADMINPRIVREQD	equ 2
AE_ADMINDIS		equ 3
AE_NOACCESSPERM		equ 3
AE_ACCRESTRICT		equ 4

AE_NORMAL_CLOSE		equ 0
AE_SES_CLOSE		equ 1
AE_ADMIN_CLOSE		equ 2

AE_LIM_UNKNOWN		equ 0
AE_LIM_LOGONHOURS	equ 1
AE_LIM_EXPIRED		equ 2
AE_LIM_INVAL_WKSTA	equ 3
AE_LIM_DISABLED		equ 4
AE_LIM_DELETED		equ 5

AE_MOD			equ 0
AE_DELETE		equ 1
AE_ADD			equ 2

AE_UAS_USER		equ 0
AE_UAS_GROUP		equ 1
AE_UAS_MODALS		equ 2

SVAUD_SERVICE		equ 0x1
SVAUD_GOODSESSLOGON	equ 0x6
SVAUD_BADSESSLOGON	equ 0x18
SVAUD_SESSLOGON		equ (SVAUD_GOODSESSLOGON OR SVAUD_BADSESSLOGON)
SVAUD_GOODNETLOGON	equ 0x60
SVAUD_BADNETLOGON	equ 0x180
SVAUD_NETLOGON		equ (SVAUD_GOODNETLOGON OR SVAUD_BADNETLOGON)
SVAUD_LOGON		equ (SVAUD_NETLOGON OR SVAUD_SESSLOGON)
SVAUD_GOODUSE		equ 0x600
SVAUD_BADUSE		equ 0x1800
SVAUD_USE		equ (SVAUD_GOODUSE OR SVAUD_BADUSE)
SVAUD_USERLIST		equ 0x2000
SVAUD_PERMISSIONS	equ 0x4000
SVAUD_RESOURCE		equ 0x8000
SVAUD_LOGONLIM		equ 0x00010000

AA_AUDIT_ALL		equ 0x0001
AA_A_OWNER		equ 0x0004
AA_CLOSE		equ 0x0008
AA_S_OPEN		equ 0x0010
AA_S_WRITE		equ 0x0020
AA_S_CREATE		equ 0x0020
AA_S_DELETE		equ 0x0040
AA_S_ACL		equ 0x0080
AA_S_ALL		equ ( AA_S_OPEN OR AA_S_WRITE OR AA_S_DELETE OR AA_S_ACL)
AA_F_OPEN		equ 0x0100
AA_F_WRITE		equ 0x0200
AA_F_CREATE		equ 0x0200
AA_F_DELETE		equ 0x0400
AA_F_ACL		equ 0x0800
AA_F_ALL		equ ( AA_F_OPEN OR AA_F_WRITE OR AA_F_DELETE OR AA_F_ACL)

AA_A_OPEN		equ 0x1000
AA_A_WRITE		equ 0x2000
AA_A_CREATE		equ 0x2000
AA_A_DELETE		equ 0x4000
AA_A_ACL		equ 0x8000
AA_A_ALL		equ ( AA_F_OPEN OR AA_F_WRITE OR AA_F_DELETE OR AA_F_ACL)

endif ;; _LMAUDIT_
