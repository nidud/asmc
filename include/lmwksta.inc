ifndef _LMWKSTA_
_LMWKSTA_ equ <>

include lmcons.inc
include lmuseflg.inc

;NET_API_STATUS
NetWkstaGetInfo proto WINAPI \
	    servername: LMSTR,
		 level: DWORD,
		bufptr: ptr LPBYTE

;NET_API_STATUS
NetWkstaSetInfo proto WINAPI \
	    servername: LMSTR,
		 level: DWORD,
		buffer: LPBYTE,
	      parm_err: LPDWORD

;NET_API_STATUS
NetWkstaUserGetInfo proto WINAPI \
	      reserved: LMSTR,
		 level: DWORD,
		bufptr: ptr LPBYTE


;NET_API_STATUS
NetWkstaUserSetInfo proto WINAPI \
	      reserved: LMSTR,
		 level: DWORD,
		   buf: LPBYTE,
	      parm_err: LPDWORD

;NET_API_STATUS
NetWkstaUserEnum proto WINAPI \
	    servername: LMSTR,
		 level: DWORD,
		bufptr: ptr LPBYTE,
	    prefmaxlen: DWORD,
	   entriesread: LPDWORD,
	  totalentries: LPDWORD,
	  resumehandle: LPDWORD

;NET_API_STATUS
NetWkstaTransportAdd proto WINAPI \
	    servername: LMSTR,
		 level: DWORD,
		   buf: LPBYTE,
	      parm_err: LPDWORD

;NET_API_STATUS
NetWkstaTransportDel proto WINAPI \
   servername OPTIONAL: LMSTR,
	 transportname: LMSTR,
		 ucond: DWORD

;NET_API_STATUS
NetWkstaTransportEnum proto WINAPI \
   servername OPTIONAL: LMSTR,
		 level: DWORD,
		bufptr: ptr LPBYTE,
	    prefmaxlen: DWORD,
	   entriesread: LPDWORD,
	  totalentries: LPDWORD,
 resumehandle OPTIONAL: LPDWORD

WKSTA_INFO_100		STRUC
wki100_platform_id	dd ?
wki100_computername	LMSTR ?
wki100_langroup		LMSTR ?
wki100_ver_major	dd ?
wki100_ver_minor	dd ?
WKSTA_INFO_100		ENDS
PWKSTA_INFO_100		typedef ptr WKSTA_INFO_100
LPWKSTA_INFO_100	typedef ptr WKSTA_INFO_100

WKSTA_INFO_101		STRUC
wki101_platform_id	dd ?
wki101_computername	LMSTR ?
wki101_langroup		LMSTR ?
wki101_ver_major	dd ?
wki101_ver_minor	dd ?
wki101_lanroot		LMSTR ?
WKSTA_INFO_101		ENDS
PWKSTA_INFO_101		typedef ptr WKSTA_INFO_101
LPWKSTA_INFO_101	typedef ptr WKSTA_INFO_101

WKSTA_INFO_102		STRUC
wki102_platform_id	dd ?
wki102_computername	LMSTR ?
wki102_langroup		LMSTR ?
wki102_ver_major	dd ?
wki102_ver_minor	dd ?
wki102_lanroot		LMSTR ?
wki102_logged_on_users	dd ?
WKSTA_INFO_102		ENDS
PWKSTA_INFO_102		typedef ptr WKSTA_INFO_102
LPWKSTA_INFO_102	typedef ptr WKSTA_INFO_102

WKSTA_INFO_302		STRUC
wki302_char_wait	dd ?
wki302_collection_time	dd ?
wki302_maximum_collection_count dd ?
wki302_keep_conn	dd ?
wki302_keep_search	dd ?
wki302_max_cmds		dd ?
wki302_num_work_buf	dd ?
wki302_siz_work_buf	dd ?
wki302_max_wrk_cache	dd ?
wki302_sess_timeout	dd ?
wki302_siz_error	dd ?
wki302_num_alerts	dd ?
wki302_num_services	dd ?
wki302_errlog_sz	dd ?
wki302_print_buf_time	dd ?
wki302_num_char_buf	dd ?
wki302_siz_char_buf	dd ?
wki302_wrk_heuristics	LMSTR ?
wki302_mailslots	dd ?
wki302_num_dgram_buf	dd ?
WKSTA_INFO_302		ENDS
PWKSTA_INFO_302		typedef ptr WKSTA_INFO_302
LPWKSTA_INFO_302	typedef ptr WKSTA_INFO_302

WKSTA_INFO_402		STRUC
wki402_char_wait	dd ?
wki402_collection_time	dd ?
wki402_maximum_collection_count dd ?
wki402_keep_conn	dd ?
wki402_keep_search	dd ?
wki402_max_cmds		dd ?
wki402_num_work_buf	dd ?
wki402_siz_work_buf	dd ?
wki402_max_wrk_cache	dd ?
wki402_sess_timeout	dd ?
wki402_siz_error	dd ?
wki402_num_alerts	dd ?
wki402_num_services	dd ?
wki402_errlog_sz	dd ?
wki402_print_buf_time	dd ?
wki402_num_char_buf	dd ?
wki402_siz_char_buf	dd ?
wki402_wrk_heuristics	LMSTR ?
wki402_mailslots	dd ?
wki402_num_dgram_buf	dd ?
wki402_max_threads	dd ?
WKSTA_INFO_402		ENDS
PWKSTA_INFO_402		typedef ptr WKSTA_INFO_402
LPWKSTA_INFO_402	typedef ptr WKSTA_INFO_402

WKSTA_INFO_502		STRUC
wki502_char_wait	dd ?
wki502_collection_time	dd ?
wki502_maximum_collection_count dd ?
wki502_keep_conn	dd ?
wki502_max_cmds		dd ?
wki502_sess_timeout	dd ?
wki502_siz_char_buf	dd ?
wki502_max_threads	dd ?
wki502_lock_quota	dd ?
wki502_lock_increment	dd ?
wki502_lock_maximum	dd ?
wki502_pipe_increment	dd ?
wki502_pipe_maximum	dd ?
wki502_cache_file_timeout dd ?
wki502_dormant_file_limit dd ?
wki502_read_ahead_throughput dd ?
wki502_num_mailslot_buffers dd ?
wki502_num_srv_announce_buffers dd ?
wki502_max_illegal_datagram_events dd ?
wki502_illegal_datagram_event_reset_frequency dd ?
wki502_log_election_packets BOOL ?
wki502_use_opportunistic_locking BOOL ?
wki502_use_unlock_behind BOOL ?
wki502_use_close_behind BOOL ?
wki502_buf_named_pipes	BOOL ?
wki502_use_lock_read_unlock BOOL ?
wki502_utilize_nt_caching BOOL ?
wki502_use_raw_read	BOOL ?
wki502_use_raw_write	BOOL ?
wki502_use_write_raw_data BOOL ?
wki502_use_encryption	BOOL ?
wki502_buf_files_deny_write BOOL ?
wki502_buf_read_only_files BOOL ?
wki502_force_core_create_mode BOOL ?
wki502_use_512_byte_max_transfer BOOL ?
WKSTA_INFO_502		ENDS
PWKSTA_INFO_502		typedef ptr WKSTA_INFO_502
LPWKSTA_INFO_502	typedef ptr WKSTA_INFO_502

WKSTA_INFO_1010		STRUC
wki1010_char_wait	dd ?
WKSTA_INFO_1010		ENDS
PWKSTA_INFO_1010	typedef ptr WKSTA_INFO_1010
LPWKSTA_INFO_1010	typedef ptr WKSTA_INFO_1010

WKSTA_INFO_1011		STRUC
wki1011_collection_time dd ?
WKSTA_INFO_1011		ENDS
PWKSTA_INFO_1011	typedef ptr WKSTA_INFO_1011
LPWKSTA_INFO_1011	typedef ptr WKSTA_INFO_1011

WKSTA_INFO_1012		STRUC
wki1012_maximum_collection_count dd ?
WKSTA_INFO_1012		ENDS
PWKSTA_INFO_1012	typedef ptr WKSTA_INFO_1012
LPWKSTA_INFO_1012	typedef ptr WKSTA_INFO_1012

WKSTA_INFO_1027		STRUC
wki1027_errlog_sz	dd ?
WKSTA_INFO_1027		ENDS
PWKSTA_INFO_1027	typedef ptr WKSTA_INFO_1027
LPWKSTA_INFO_1027	typedef ptr WKSTA_INFO_1027

WKSTA_INFO_1028		STRUC
wki1028_print_buf_time	dd ?
WKSTA_INFO_1028		ENDS
PWKSTA_INFO_1028	typedef ptr WKSTA_INFO_1028
LPWKSTA_INFO_1028	typedef ptr WKSTA_INFO_1028

WKSTA_INFO_1032		STRUC
wki1032_wrk_heuristics	dd ?
WKSTA_INFO_1032		ENDS
PWKSTA_INFO_1032	typedef ptr WKSTA_INFO_1032
LPWKSTA_INFO_1032	typedef ptr WKSTA_INFO_1032

WKSTA_INFO_1013		STRUC
wki1013_keep_conn	dd ?
WKSTA_INFO_1013		ENDS
PWKSTA_INFO_1013	typedef ptr WKSTA_INFO_1013
LPWKSTA_INFO_1013	typedef ptr WKSTA_INFO_1013

WKSTA_INFO_1018		STRUC
wki1018_sess_timeout	dd ?
WKSTA_INFO_1018		ENDS
PWKSTA_INFO_1018	typedef ptr WKSTA_INFO_1018
LPWKSTA_INFO_1018	typedef ptr WKSTA_INFO_1018

WKSTA_INFO_1023		STRUC
wki1023_siz_char_buf	dd ?
WKSTA_INFO_1023		ENDS
PWKSTA_INFO_1023	typedef ptr WKSTA_INFO_1023
LPWKSTA_INFO_1023	typedef ptr WKSTA_INFO_1023

WKSTA_INFO_1033		STRUC
wki1033_max_threads	dd ?
WKSTA_INFO_1033		ENDS
PWKSTA_INFO_1033	typedef ptr WKSTA_INFO_1033
LPWKSTA_INFO_1033	typedef ptr WKSTA_INFO_1033

WKSTA_INFO_1041		STRUC
wki1041_lock_quota	dd ?
WKSTA_INFO_1041		ENDS
PWKSTA_INFO_1041	typedef ptr WKSTA_INFO_1041
LPWKSTA_INFO_1041	typedef ptr WKSTA_INFO_1041

WKSTA_INFO_1042		STRUC
wki1042_lock_increment	dd ?
WKSTA_INFO_1042		ENDS
PWKSTA_INFO_1042	typedef ptr WKSTA_INFO_1042
LPWKSTA_INFO_1042	typedef ptr WKSTA_INFO_1042

WKSTA_INFO_1043		STRUC
wki1043_lock_maximum	dd ?
WKSTA_INFO_1043		ENDS
PWKSTA_INFO_1043	typedef ptr WKSTA_INFO_1043
LPWKSTA_INFO_1043	typedef ptr WKSTA_INFO_1043

WKSTA_INFO_1044		STRUC
wki1044_pipe_increment	dd ?
WKSTA_INFO_1044		ENDS
PWKSTA_INFO_1044	typedef ptr WKSTA_INFO_1044
LPWKSTA_INFO_1044	typedef ptr WKSTA_INFO_1044

WKSTA_INFO_1045		STRUC
wki1045_pipe_maximum	dd ?
WKSTA_INFO_1045		ENDS
PWKSTA_INFO_1045	typedef ptr WKSTA_INFO_1045
LPWKSTA_INFO_1045	typedef ptr WKSTA_INFO_1045

WKSTA_INFO_1046		STRUC
wki1046_dormant_file_limit dd ?
WKSTA_INFO_1046		ENDS
PWKSTA_INFO_1046	typedef ptr WKSTA_INFO_1046
LPWKSTA_INFO_1046	typedef ptr WKSTA_INFO_1046

WKSTA_INFO_1047		STRUC
wki1047_cache_file_timeout dd ?
WKSTA_INFO_1047		ENDS
PWKSTA_INFO_1047	typedef ptr WKSTA_INFO_1047
LPWKSTA_INFO_1047	typedef ptr WKSTA_INFO_1047

WKSTA_INFO_1048		STRUC
wki1048_use_opportunistic_locking BOOL ?
WKSTA_INFO_1048		ENDS
PWKSTA_INFO_1048	typedef ptr WKSTA_INFO_1048
LPWKSTA_INFO_1048	typedef ptr WKSTA_INFO_1048

WKSTA_INFO_1049		STRUC
wki1049_use_unlock_behind BOOL ?
WKSTA_INFO_1049		ENDS
PWKSTA_INFO_1049	typedef ptr WKSTA_INFO_1049
LPWKSTA_INFO_1049	typedef ptr WKSTA_INFO_1049

WKSTA_INFO_1050		STRUC
wki1050_use_close_behind BOOL ?
WKSTA_INFO_1050		ENDS
PWKSTA_INFO_1050	typedef ptr WKSTA_INFO_1050
LPWKSTA_INFO_1050	typedef ptr WKSTA_INFO_1050

WKSTA_INFO_1051		STRUC
wki1051_buf_named_pipes BOOL ?
WKSTA_INFO_1051		ENDS
PWKSTA_INFO_1051	typedef ptr WKSTA_INFO_1051
LPWKSTA_INFO_1051	typedef ptr WKSTA_INFO_1051

WKSTA_INFO_1052		STRUC
wki1052_use_lock_read_unlock BOOL ?
WKSTA_INFO_1052		ENDS
PWKSTA_INFO_1052	typedef ptr WKSTA_INFO_1052
LPWKSTA_INFO_1052	typedef ptr WKSTA_INFO_1052

WKSTA_INFO_1053		STRUC
wki1053_utilize_nt_caching BOOL ?
WKSTA_INFO_1053		ENDS
PWKSTA_INFO_1053	typedef ptr WKSTA_INFO_1053
LPWKSTA_INFO_1053	typedef ptr WKSTA_INFO_1053

WKSTA_INFO_1054		STRUC
wki1054_use_raw_read	BOOL ?
WKSTA_INFO_1054		ENDS
PWKSTA_INFO_1054	typedef ptr WKSTA_INFO_1054
LPWKSTA_INFO_1054	typedef ptr WKSTA_INFO_1054

WKSTA_INFO_1055		STRUC
wki1055_use_raw_write	BOOL ?
WKSTA_INFO_1055		ENDS
PWKSTA_INFO_1055	typedef ptr WKSTA_INFO_1055
LPWKSTA_INFO_1055	typedef ptr WKSTA_INFO_1055

WKSTA_INFO_1056		STRUC
wki1056_use_write_raw_data BOOL ?
WKSTA_INFO_1056		ENDS
PWKSTA_INFO_1056	typedef ptr WKSTA_INFO_1056
LPWKSTA_INFO_1056	typedef ptr WKSTA_INFO_1056

WKSTA_INFO_1057		STRUC
wki1057_use_encryption	BOOL ?
WKSTA_INFO_1057		ENDS
PWKSTA_INFO_1057	typedef ptr WKSTA_INFO_1057
LPWKSTA_INFO_1057	typedef ptr WKSTA_INFO_1057

WKSTA_INFO_1058		STRUC
wki1058_buf_files_deny_write BOOL ?
WKSTA_INFO_1058		ENDS
PWKSTA_INFO_1058	typedef ptr WKSTA_INFO_1058
LPWKSTA_INFO_1058	typedef ptr WKSTA_INFO_1058

WKSTA_INFO_1059		STRUC
wki1059_buf_read_only_files BOOL ?
WKSTA_INFO_1059		ENDS
PWKSTA_INFO_1059	typedef ptr WKSTA_INFO_1059
LPWKSTA_INFO_1059	typedef ptr WKSTA_INFO_1059

WKSTA_INFO_1060		STRUC
wki1060_force_core_create_mode BOOL ?
WKSTA_INFO_1060		ENDS
PWKSTA_INFO_1060	typedef ptr WKSTA_INFO_1060
LPWKSTA_INFO_1060	typedef ptr WKSTA_INFO_1060

WKSTA_INFO_1061		STRUC
wki1061_use_512_byte_max_transfer BOOL ?
WKSTA_INFO_1061		ENDS
PWKSTA_INFO_1061	typedef ptr WKSTA_INFO_1061
LPWKSTA_INFO_1061	typedef ptr WKSTA_INFO_1061

WKSTA_INFO_1062		STRUC
wki1062_read_ahead_throughput dd ?
WKSTA_INFO_1062		ENDS
PWKSTA_INFO_1062	typedef ptr WKSTA_INFO_1062
LPWKSTA_INFO_1062	typedef ptr WKSTA_INFO_1062

WKSTA_USER_INFO_0	STRUC
wkui0_username		LMSTR ?
WKSTA_USER_INFO_0	ENDS
PWKSTA_USER_INFO_0	typedef ptr WKSTA_USER_INFO_0
LPWKSTA_USER_INFO_0	typedef ptr WKSTA_USER_INFO_0

WKSTA_USER_INFO_1	STRUC
wkui1_username		LMSTR ?
wkui1_logon_domain	LMSTR ?
wkui1_oth_domains	LMSTR ?
wkui1_logon_server	LMSTR ?
WKSTA_USER_INFO_1	ENDS
PWKSTA_USER_INFO_1	typedef ptr WKSTA_USER_INFO_1
LPWKSTA_USER_INFO_1	typedef ptr WKSTA_USER_INFO_1

WKSTA_USER_INFO_1101	STRUC
wkui1101_oth_domains	LMSTR ?
WKSTA_USER_INFO_1101	ENDS
PWKSTA_USER_INFO_1101	typedef ptr WKSTA_USER_INFO_1101

WKSTA_TRANSPORT_INFO_0	STRUC
wkti0_quality_of_service dd ?
wkti0_number_of_vcs	dd ?
wkti0_transport_name	LMSTR ?
wkti0_transport_address LMSTR ?
wkti0_wan_ish		BOOL ?
WKSTA_TRANSPORT_INFO_0	ENDS
PWKSTA_TRANSPORT_INFO_0 typedef ptr WKSTA_TRANSPORT_INFO_0

WKSTA_PLATFORM_ID_PARMNUM equ 100
WKSTA_COMPUTERNAME_PARMNUM equ 1
WKSTA_LANGROUP_PARMNUM	equ 2
WKSTA_VER_MAJOR_PARMNUM equ 4
WKSTA_VER_MINOR_PARMNUM equ 5
WKSTA_LOGGED_ON_USERS_PARMNUM equ 6
WKSTA_LANROOT_PARMNUM	equ 7
WKSTA_LOGON_DOMAIN_PARMNUM equ 8
WKSTA_LOGON_SERVER_PARMNUM equ 9
WKSTA_CHARWAIT_PARMNUM	equ 10
WKSTA_CHARTIME_PARMNUM	equ 11
WKSTA_CHARCOUNT_PARMNUM equ 12
WKSTA_KEEPCONN_PARMNUM	equ 13
WKSTA_KEEPSEARCH_PARMNUM equ 14
WKSTA_MAXCMDS_PARMNUM	equ 15
WKSTA_NUMWORKBUF_PARMNUM equ 16
WKSTA_MAXWRKCACHE_PARMNUM equ 17
WKSTA_SESSTIMEOUT_PARMNUM equ 18
WKSTA_SIZERROR_PARMNUM	equ 19
WKSTA_NUMALERTS_PARMNUM equ 20
WKSTA_NUMSERVICES_PARMNUM equ 21
WKSTA_NUMCHARBUF_PARMNUM equ 22
WKSTA_SIZCHARBUF_PARMNUM equ 23
WKSTA_ERRLOGSZ_PARMNUM	equ 27
WKSTA_PRINTBUFTIME_PARMNUM equ 28
WKSTA_SIZWORKBUF_PARMNUM equ 29
WKSTA_MAILSLOTS_PARMNUM equ 30
WKSTA_NUMDGRAMBUF_PARMNUM equ 31
WKSTA_WRKHEURISTICS_PARMNUM equ 32
WKSTA_MAXTHREADS_PARMNUM equ 33

WKSTA_LOCKQUOTA_PARMNUM equ 41
WKSTA_LOCKINCREMENT_PARMNUM equ 42
WKSTA_LOCKMAXIMUM_PARMNUM equ 43
WKSTA_PIPEINCREMENT_PARMNUM equ 44
WKSTA_PIPEMAXIMUM_PARMNUM equ 45
WKSTA_DORMANTFILELIMIT_PARMNUM equ 46
WKSTA_CACHEFILETIMEOUT_PARMNUM equ 47
WKSTA_USEOPPORTUNISTICLOCKING_PARMNUM equ 48
WKSTA_USEUNLOCKBEHIND_PARMNUM equ 49
WKSTA_USECLOSEBEHIND_PARMNUM equ 50
WKSTA_BUFFERNAMEDPIPES_PARMNUM equ 51
WKSTA_USELOCKANDREADANDUNLOCK_PARMNUM equ 52
WKSTA_UTILIZENTCACHING_PARMNUM equ 53
WKSTA_USERAWREAD_PARMNUM equ 54
WKSTA_USERAWWRITE_PARMNUM equ 55
WKSTA_USEWRITERAWWITHDATA_PARMNUM equ 56
WKSTA_USEENCRYPTION_PARMNUM equ 57
WKSTA_BUFFILESWITHDENYWRITE_PARMNUM equ 58
WKSTA_BUFFERREADONLYFILES_PARMNUM equ 59
WKSTA_FORCECORECREATEMODE_PARMNUM equ 60
WKSTA_USE512BYTESMAXTRANSFER_PARMNUM equ 61
WKSTA_READAHEADTHRUPUT_PARMNUM equ 62

WKSTA_OTH_DOMAINS_PARMNUM equ 101

TRANSPORT_QUALITYOFSERVICE_PARMNUM equ 201
TRANSPORT_NAME_PARMNUM	equ 202

endif ;; _LMWKSTA_
