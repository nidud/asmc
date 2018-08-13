ifndef _ALERT_
_ALERT_ equ <>

;NET_API_STATUS
NetAlertRaise proto WINAPI \
	     AlertType: LPCWSTR,
		Buffer: LPVOID,
	    BufferSize: DWORD

;NET_API_STATUS
NetAlertRaiseEx proto WINAPI \
	     AlertType: LPCWSTR,
	  VariableInfo: LPVOID,
      VariableInfoSize: DWORD,
	   ServiceName: LPCWSTR

STD_ALERT		STRUC
alrt_timestamp		dd ?
alrt_eventname		WCHAR EVLEN + 1 dup(?)
alrt_servicename	WCHAR SNLEN + 1 dup(?)
STD_ALERT		ENDS
PSTD_ALERT		typedef ptr STD_ALERT
LPSTD_ALERT		typedef ptr STD_ALERT

ADMIN_OTHER_INFO	STRUC
alrtad_errcode		dd ?
alrtad_numstrings	dd ?
ADMIN_OTHER_INFO	ENDS
PADMIN_OTHER_INFO	typedef ptr ADMIN_OTHER_INFO
LPADMIN_OTHER_INFO	typedef ptr ADMIN_OTHER_INFO

ERRLOG_OTHER_INFO	STRUC
alrter_errcode		dd ?
alrter_offset		dd ?
ERRLOG_OTHER_INFO	ENDS
PERRLOG_OTHER_INFO	typedef ptr ERRLOG_OTHER_INFO
LPERRLOG_OTHER_INFO	typedef ptr ERRLOG_OTHER_INFO

PRINT_OTHER_INFO	STRUC
alrtpr_jobid		dd ?
alrtpr_status		dd ?
alrtpr_submitted	dd ?
alrtpr_size		dd ?
PRINT_OTHER_INFO	ENDS
PPRINT_OTHER_INFO	typedef ptr PRINT_OTHER_INFO
LPPRINT_OTHER_INFO	typedef ptr PRINT_OTHER_INFO

USER_OTHER_INFO		STRUC
alrtus_errcode		dd ?
alrtus_numstrings	dd ?
USER_OTHER_INFO		ENDS
PUSER_OTHER_INFO	typedef ptr USER_OTHER_INFO
LPUSER_OTHER_INFO	typedef ptr USER_OTHER_INFO

ALERTER_MAILSLOT	equ <L"\\\\.\\MAILSLOT\\Alerter">

ALERT_OTHER_INFO macro x
	exitm<((x) + sizeof(STD_ALERT))>
	endm

ALERT_VAR_DATA macro p
	exitm<((p) + sizeof(*p))>
	endm

ALERT_PRINT_EVENT	equ <L"PRINTING">
ALERT_MESSAGE_EVENT	equ <L"MESSAGE">
ALERT_ERRORLOG_EVENT	equ <L"ERRORLOG">
ALERT_ADMIN_EVENT	equ <L"ADMIN">
ALERT_USER_EVENT	equ <L"USER">

PRJOB_QSTATUS		equ 0x3
PRJOB_DEVSTATUS		equ 0x1fc
PRJOB_COMPLETE		equ 0x4
PRJOB_INTERV		equ 0x8
PRJOB_ERROR		equ 0x10
PRJOB_DESTOFFLINE	equ 0x20
PRJOB_DESTPAUSED	equ 0x40
PRJOB_NOTIFY		equ 0x80
PRJOB_DESTNOPAPER	equ 0x100
PRJOB_DELETED		equ 0x8000

PRJOB_QS_QUEUED		equ 0
PRJOB_QS_PAUSED		equ 1
PRJOB_QS_SPOOLING	equ 2
PRJOB_QS_PRINTING	equ 3

endif ;; _ALERT_
