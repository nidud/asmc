include winbase.inc
include stdio.inc
include time.inc

    .code

main proc

    .new t:time_t
    .new TimeZoneInformation:TIME_ZONE_INFORMATION
    .new FindFileData:WIN32_FIND_DATAA

    GetTimeZoneInformation(&TimeZoneInformation)

    wprintf(L"TIME_ZONE_INFORMATION:\n .StandardName: %s\n", &TimeZoneInformation.StandardName)
    wprintf(L" .DaylightName: %s\n\n", &TimeZoneInformation.DaylightName)

    FindClose(FindFirstFileA(__FILE__, &FindFileData))

    .new dateStringW[MAX_PATH]:wchar_t
    .new dateStringA[MAX_PATH]:char_t

    printf("FileDateToStringA: %s\n", FileDateToStringA(&dateStringA, &FindFileData.ftLastWriteTime))
    wprintf(L"FileDateToStringW: %s\n", FileDateToStringW(&dateStringW, &FindFileData.ftLastWriteTime))

    .new systemTimeA:SYSTEMTIME
    .new systemTimeW:SYSTEMTIME

    StringToSystemDateA(&dateStringA, &systemTimeA)
    StringToSystemDateW(&dateStringW, &systemTimeW)

    printf(
        "StringToSystemDateA:\n"
        " .wYear       %d\n"
        " .wMonth      %d\n"
        " .wDayOfWeek  %d\n"
        " .wDay        %d\n",
        systemTimeA.wYear,
        systemTimeA.wMonth,
        systemTimeA.wDayOfWeek,
        systemTimeA.wDay)

    printf(
        "StringToSystemDateW:\n"
        " .wYear       %d\n"
        " .wMonth      %d\n"
        " .wDayOfWeek  %d\n"
        " .wDay        %d\n\n",
        systemTimeW.wYear,
        systemTimeW.wMonth,
        systemTimeW.wDayOfWeek,
        systemTimeW.wDay)

    .new timeStringA[MAX_PATH]:char_t
    .new timeStringW[MAX_PATH]:wchar_t

    printf("FileTimeToStringA: %s\n", FileTimeToStringA(&timeStringA, &FindFileData.ftLastWriteTime))
    wprintf(L"FileTimeToStringW: %s\n", FileTimeToStringW(&timeStringW, &FindFileData.ftLastWriteTime))

    StringToSystemTimeA(&timeStringA, &systemTimeA)
    StringToSystemTimeW(&timeStringW, &systemTimeW)

    printf(
        "StringToSystemTimeA:\n"
        " .wHour       %d\n"
        " .wMinute     %d\n"
        " .wSecond     %d\n"
        " .wMilliseconds %d\n",
        systemTimeA.wHour,
        systemTimeA.wMinute,
        systemTimeA.wSecond,
        systemTimeA.wMilliseconds)

    printf(
        "StringToSystemTimeW:\n"
        " .wHour       %d\n"
        " .wMinute     %d\n"
        " .wSecond     %d\n"
        " .wMilliseconds %d\n\n",
        systemTimeW.wHour,
        systemTimeW.wMinute,
        systemTimeW.wSecond,
        systemTimeW.wMilliseconds)

    printf("SystemTimeToStringA: %s\n", SystemTimeToStringA(&timeStringA, &systemTimeA))
    wprintf(L"SystemTimeToStringW: %s\n\n", SystemTimeToStringW(&timeStringW, &systemTimeW))

    time(&t)
    printf("ctime(): %s\n", ctime(&t))
    printf("clock(): %d\n", clock())
    ret

main endp

    end
