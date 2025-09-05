ifndef _JOBAPISET2_H_
define _JOBAPISET2_H_
ifndef _APIQUERY2_H_
include apiquery2.inc
endif
ifndef _MINWINBASE_
include minwinbase.inc
endif

JOBOBJECT_IO_RATE_CONTROL_INFORMATION struct
MaxIops                 LONG64 ?
MaxBandwidth            LONG64 ?
ReservationIops         LONG64 ?
VolumeName              PCWSTR ?
BaseIoSize              ULONG ?
ControlFlags            ULONG ?
JOBOBJECT_IO_RATE_CONTROL_INFORMATION ends

CreateJobObjectW proto WINAPI :LPSECURITY_ATTRIBUTES, :LPCWSTR
FreeMemoryJobObject proto WINAPI :ptr
OpenJobObjectW proto WINAPI :DWORD, :BOOL, :LPCWSTR
AssignProcessToJobObject proto WINAPI :HANDLE, :HANDLE
TerminateJobObject proto WINAPI :HANDLE, :UINT
SetInformationJobObject proto WINAPI :HANDLE, :JOBOBJECTINFOCLASS, :LPVOID, :DWORD
SetIoRateControlInformationJobObject proto WINAPI :HANDLE, :ptr
QueryInformationJobObject proto WINAPI :HANDLE, :JOBOBJECTINFOCLASS, :LPVOID, :DWORD, :LPDWORD
QueryIoRateControlInformationJobObject proto WINAPI :HANDLE, :PCWSTR, :ptr ptr, :ptr

endif
