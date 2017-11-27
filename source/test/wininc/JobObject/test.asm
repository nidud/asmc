include stdio.inc
include stdlib.inc
include winnt.inc
include winbase.inc
include tchar.inc

.code

_tmain proc

    local ReturnLength:dword
    local JobObjectInfo:JOBOBJECT_BASIC_ACCOUNTING_INFORMATION

    .if QueryInformationJobObject(
            NULL,
            JobObjectBasicAccountingInformation,
            &JobObjectInfo,
            sizeof(JobObjectInfo),
            &ReturnLength)

        _tprintf(
            "TotalUserTime:             %lld\n"
            "TotalKernelTime:           %lld\n"
            "ThisPeriodTotalUserTime:   %lld\n"
            "ThisPeriodTotalKernelTime: %lld\n"
            "TotalPageFaultCount:       %d\n"
            "TotalProcesses:            %d\n"
            "ActiveProcesses:           %d\n"
            "TotalTerminatedProcesses:  %d\n",
            JobObjectInfo.TotalUserTime.QuadPart,
            JobObjectInfo.TotalKernelTime.QuadPart,
            JobObjectInfo.ThisPeriodTotalUserTime.QuadPart,
            JobObjectInfo.ThisPeriodTotalKernelTime.QuadPart,
            JobObjectInfo.TotalPageFaultCount,
            JobObjectInfo.TotalProcesses,
            JobObjectInfo.ActiveProcesses,
            JobObjectInfo.TotalTerminatedProcesses)
    .endif
    exit(0)

_tmain endp

    end _tmain

