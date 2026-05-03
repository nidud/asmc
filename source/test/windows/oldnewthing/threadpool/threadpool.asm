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
    endp

_tmain proc
    .new last:HANDLE = CreateEvent(nullptr, true, false, nullptr)
    .for ( rdi = rax, ebx = 0 : ebx < 10000 : ebx++ )
        mov rsi,CreateThreadpoolWait(&WaitCallback, rdi, nullptr)
        mov rdi,CreateEvent(nullptr, true, false, nullptr)
        SetThreadpoolWait(rsi, rdi, nullptr)
    .endf
    Sleep(10000)
    SetEvent(rdi)
    WaitForSingleObject(last, INFINITE)
    _tprintf("%d events signaled\n", count)
    xor eax,eax
    ret
    endp
    end _tstart
