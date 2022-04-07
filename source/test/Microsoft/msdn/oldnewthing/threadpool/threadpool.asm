; THREADPOOL.ASM--
;
; All Windows threadpool waits can now be handled by a single thread
;
; https://devblogs.microsoft.com/oldnewthing/20220406-00/?p=106434
;

include windows.inc
include stdio.inc
include tchar.inc

    .data
     count LONG 0

    .code

WaitCallback proc Instance:PTP_CALLBACK_INSTANCE, Context:PVOID, PWait:PTP_WAIT, WaitResult:TP_WAIT_RESULT

    InterlockedIncrement(&count)
    SetEvent(Context)
    ret

WaitCallback endp

main proc

    .new last:HANDLE = CreateEvent(nullptr, true, false, nullptr)
    .new event:HANDLE = last
    .new i:int_t = 0

    .for (: i < 10000: i++)

       .new pwait:PTP_WAIT = CreateThreadpoolWait(&WaitCallback, event, nullptr)
        mov event,CreateEvent(nullptr, true, false, nullptr)
        SetThreadpoolWait(pwait, event, nullptr)
    .endf

    Sleep(10000)
    SetEvent(event)
    WaitForSingleObject(last, INFINITE)
    printf("%d events signaled\n", count)
   .return 0

main endp

    end _tstart
