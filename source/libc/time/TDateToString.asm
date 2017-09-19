include time.inc

    .code

TDateToString proc string:ptr sbyte, tptr:time_t

local SystemTime:SYSTEMTIME

    __TimeToST(tptr, &SystemTime)
    SystemDateToString(string, &SystemTime)
    ret

TDateToString endp

    END
