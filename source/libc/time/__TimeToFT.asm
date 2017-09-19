include time.inc
include winbase.inc

    .code

__TimeToFT proc uses edx ecx Time:time_t, lpFileTime:LPFILETIME

local SystemTime:SYSTEMTIME

    SystemTimeToFileTime(__TimeToST(Time, &SystemTime), lpFileTime)
    LocalFileTimeToFileTime(lpFileTime, lpFileTime)
    mov eax,lpFileTime
    ret

__TimeToFT endp

    END
