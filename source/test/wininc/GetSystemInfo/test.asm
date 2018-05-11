;
; https://blogs.msdn.microsoft.com/oldnewthing/20141023-00/?p=43783
;
include windows.inc
include stdio.inc
include tchar.inc

.code

main proc

    local s:SYSTEM_INFO

    GetSystemInfo(&s)
    printf(
        "Configuration\t\tLARGEADDRESSAWARE?\tResult\t\tMeaning\n"
        "==============================================================================\n"
        "standard configuration\tAny\t\t\t7FFEFFFF\t2GB minus 64KB\n"
        "/3GB\t\t\tAny\t\t\tBFFFFFFF\t3GB\n"
        "increaseuserva = 2995\tAny\t\t\tBB3EFFFF\t2995 MB\n"
        "64-bit Windows\t\tNo\t\t000007FFFFFEFFFF\t2GB minus 64KB\n"
        "64-bit Windows\t\tYes\t\t\tFFFEFFFF\t4GB minus 64KB\n" )
    printf("\nMaximum Application Address: %p\n\n", s.lpMaximumApplicationAddress)
    xor eax,eax
    ret

main endp

    end _tstart
