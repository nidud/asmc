ifndef _LMAT_
_LMAT_ equ <>

JOB_RUN_PERIODICALLY	equ 0x01
JOB_EXEC_ERROR		equ 0x02
JOB_RUNS_TODAY		equ 0x04
JOB_ADD_CURRENT_DATE	equ 0x08
JOB_NONINTERACTIVE	equ 0x10
JOB_INPUT_FLAGS		equ (JOB_RUN_PERIODICALLY OR JOB_ADD_CURRENT_DATE OR JOB_NONINTERACTIVE)
JOB_OUTPUT_FLAGS	equ (JOB_RUN_PERIODICALLY OR JOB_EXEC_ERROR OR JOB_RUNS_TODAY OR JOB_NONINTERACTIVE)

AT_INFO			STRUC
JobTime			dd ?
DaysOfMonth		dd ?
DaysOfWeek		UCHAR ?
Flags			UCHAR ?
Command			LPWSTR ?
AT_INFO			ENDS
PAT_INFO		typedef ptr AT_INFO
LPAT_INFO		typedef ptr AT_INFO

AT_ENUM			STRUC
JobId			dd ?
JobTime			dd ?
DaysOfMonth		dd ?
DaysOfWeek		UCHAR ?
Flags			UCHAR ?
Command			LPWSTR ?
AT_ENUM			ENDS
PAT_ENUM		typedef ptr AT_ENUM
LPAT_ENUM		typedef ptr AT_ENUM

;NET_API_STATUS
NetScheduleJobAdd proto WINAPI \
	    Servername: LPCWSTR,
		Buffer: LPBYTE,
		 JobId: LPDWORD

;NET_API_STATUS
NetScheduleJobDel proto WINAPI \
	    Servername: LPCWSTR,
	      MinJobId: DWORD,
	      MaxJobId: DWORD

;NET_API_STATUS
NetScheduleJobEnum proto WINAPI \
	    Servername: LPCWSTR,
       PointerToBuffer: ptr LPBYTE,
PrefferedMaximumLength: DWORD,
	   EntriesRead: LPDWORD,
	  TotalEntries: LPDWORD,
	  ResumeHandle: LPDWORD

;NET_API_STATUS
NetScheduleJobGetInfo proto WINAPI \
	    Servername: LPCWSTR,
		 JobId: DWORD,
       PointerToBuffer: ptr LPBYTE

endif
