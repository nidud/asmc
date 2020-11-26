ifndef _UNICODE
_UNICODE equ <>
endif

include windows.inc
include stdlib.inc
include strsafe.inc
include tchar.inc

TIMERID_NOCOALSCING         equ (0)
TIMERID_COALESCING          equ (1)
TIMERID_UPDATE_SCREEN       equ (100)

TIMER_ELAPSE                equ (31)
TIMER_TOLERANCE             equ (80)
TIMER_CONTIGUOUS_RUN        equ (100)
TIMER_AUTO_REFRESH_ELAPSE   equ (5*1000)

.data

ghwnd           HWND 0
ghInstance      HINSTANCE 0

TimerRec        struct
lLast           LONGLONG ?
lCount          LONGLONG ?
lElapsedMin     LONGLONG ?
lElapsedMax     LONGLONG ?
lSum            LONGLONG ?
TimerRec        ends

gTimerRec       TimerRec 2 dup(<>)
glFrequency     LONGLONG ?


WndProc proto :HWND, :UINT, :WPARAM, :LPARAM

.code
;;
;;  GetPerformanceCounter
;;
;;  Returns the high refolustion time in milliseconds
;;  (resolution of tick counts is a bit too coarse
;;   for the purpose here)
;;

GetPerformanceCounter proc

  local t:LARGE_INTEGER

    QueryPerformanceCounter(&t)
    imul rax,t.QuadPart,1000
    add rax,500
    xor edx,edx
    div glFrequency
    ret

GetPerformanceCounter endp

;;
;;  Initialize
;;
;;  This method is used to create and display the application
;;  window, and provides a convenient place to create any device
;;  independent resources that will be required.
;;

Initialize proc

    local wcex:WNDCLASSEX
    local atom:ATOM
    local freq:LARGE_INTEGER

    ;; Prepare the high resolution performance counter.
    SetThreadAffinityMask(GetCurrentThread(), 0)
    .return FALSE .if (!QueryPerformanceFrequency(&freq))

    mov glFrequency,freq.QuadPart

    ;; Initialize the result array.
    mov rax,MAXLONGLONG
    mov gTimerRec[0*TimerRec].lElapsedMin,rax
    mov gTimerRec[1*TimerRec].lElapsedMin,rax


    ;; Register window class
    mov wcex.cbSize,        sizeof(WNDCLASSEX)
    mov wcex.style,         CS_HREDRAW or CS_VREDRAW
    mov wcex.lpfnWndProc,   &WndProc
    mov wcex.cbClsExtra,    0
    mov wcex.cbWndExtra,    sizeof(LONG_PTR)
    mov wcex.hInstance,     ghInstance
    mov wcex.hIcon,         LoadIcon(NULL, IDI_APPLICATION)
    mov wcex.hCursor,       LoadCursor(NULL, IDC_ARROW)
    mov wcex.hbrBackground, NULL
    mov wcex.lpszMenuName,  NULL
    mov wcex.lpszClassName, &@CStr("TimerApp")
    mov wcex.hIconSm,       LoadIcon(NULL, IDI_APPLICATION)

    mov atom,RegisterClassEx(&wcex)
    .return .if (atom == 0)

    SetProcessDPIAware()

    ;; Create & prepare the main window
    movzx edx,atom
    mov ghwnd,CreateWindowEx(0,
        rdx,
        "Coalescable Timer Sample",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        600,
        400,
        NULL,
        NULL,
        ghInstance,
        NULL)

    .return .if (ghwnd == NULL)

    ShowWindow(ghwnd, SW_SHOWNORMAL)
    UpdateWindow(ghwnd)

    .return TRUE

Initialize endp

MakeItLookNormal proto l:LONGLONG {

    xor eax,eax
    mov rdx,MAXLONGLONG
    .if (rcx != rdx)
        ;; If the value is initialized but not set yet,
        ;; give it some reasonable sane value.
        mov rax,rcx
    .endif
    }

Average proto sum:LONGLONG, count:LONGLONG {

    xorps xmm0,xmm0
    .if (count != 0)
        cvtsi2sd xmm0,sum
        cvtsi2sd xmm1,count
        divsd    xmm0,xmm1
    .endif
    }

OnPaint proc uses rsi rdi hdc:HDC, prcPaint:PRECT

  local hr:HRESULT
  local wzText[1024]:WCHAR

    FillRect(hdc, prcPaint, GetStockObject(WHITE_BRUSH))

    nocoal equ <gTimerRec[TimerRec*TIMERID_NOCOALSCING]>
    coal   equ <gTimerRec[TimerRec*TIMERID_COALESCING]>

    mov rsi,MakeItLookNormal(nocoal.lElapsedMin)
    mov rdi,MakeItLookNormal(coal.lElapsedMin)
    Average(coal.lSum, coal.lCount)
    movaps xmm2,xmm0
    Average(nocoal.lSum, nocoal.lCount)

    ;mov hr,StringCchPrintfExW(&wzText, 1024, NULL, NULL, STRSAFE_NULL_ON_FAILURE,
    mov hr,S_OK
    swprintf(&wzText,
            "Timer non-coalesced  Min = %I64d, Avg = %.1f, Max = %I64d, (%I64d / %I64d)\n\n"
            "Timer coalesced      Min = %I64d, Avg = %.1f, Max = %I64d, (%I64d / %I64d)\n\n"
            "[Elapse = %dms, Coaclescing tolerance = %dms]\n\n"
            "Hit space to turn off the monitor",
            rsi,
            xmm0,
            nocoal.lElapsedMax,
            nocoal.lSum,
            nocoal.lCount,
            rdi,
            xmm2,
            coal.lElapsedMax,
            coal.lSum,
            coal.lCount,
            TIMER_ELAPSE,
            TIMER_TOLERANCE)

    .if (SUCCEEDED(hr))
        DrawText(hdc, &wzText, -1, prcPaint, DT_TOP or DT_LEFT)
    .endif
    ret

OnPaint endp

;;
;;  TimerHandler
;;
;;  Handles both coalesced and non-coalesced timers, and keeps
;;  the record of the effective elapsed time.
;;  Switches the coalesced modes periodically for comparison.
;;
    assume rsi:ptr TimerRec

TimerHandler proc uses rsi hwnd:HWND, idEvent:UINT_PTR

    .return .if (edx >= ARRAYSIZE(gTimerRec))

    lea  rsi,gTimerRec
    imul eax,edx,TimerRec
    add  rsi,rax

   .new lTime:LONGLONG = GetPerformanceCounter()
   .new lElapsed:LONGLONG

    sub rax,[rsi].lLast
    mov lElapsed,rax

    mov rax,[rsi].lElapsedMin
    .if rax > lElapsed
        mov rax,lElapsed
    .endif
    mov [rsi].lElapsedMin,rax

    mov rax,[rsi].lElapsedMax
    .if rax < lElapsed
        mov rax,lElapsed
    .endif
    mov [rsi].lElapsedMax,rax

    mov [rsi].lLast,lTime
    inc [rsi].lCount
    add [rsi].lSum,lElapsed
    mov rcx,TIMER_CONTIGUOUS_RUN
    mov rax,[rsi].lCount
    xor edx,edx
    div rcx

    .if (rdx == 0)

        ;; Now, let's switch the timer types.
        ;; First, kill the current timer.

        mov rdx,idEvent
        KillTimer(hwnd, edx)

        ;; Reverse the timer id.

        mov rax,idEvent
        xor eax,1
        mov idEvent,rax

        ;;
        ;; Setting new timer - switching the coalescing mode.
        ;;
        ;; Note that the coalesced timers may be fired
        ;; together with other timers that are readied during the
        ;; coalescing tolerance.  As such, in an environment
        ;; that has a lot of short timers may only see a small or no
        ;; increase in the average time.
        ;; If that's the case, try running this sample with
        ;; the minimum number of processes.
        ;;
        GetPerformanceCounter()
        imul rdx,idEvent,TimerRec
        lea rcx,gTimerRec
        mov [rcx+rdx].TimerRec.lLast,rax
        mov eax,TIMER_TOLERANCE
        .if idEvent == TIMERID_NOCOALSCING
            mov eax,TIMERV_NO_COALESCING
        .endif

        SetCoalescableTimer(hwnd, idEvent, TIMER_ELAPSE, NULL, eax)
    .endif
    ret

TimerHandler endp

WndProc proc hwnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

    .switch edx
    .case WM_CREATE
        ;; Start with non-coalescable timer.
        ;; Later we switch to the coalescable timer.
        mov gTimerRec[TimerRec*TIMERID_NOCOALSCING].lLast,GetPerformanceCounter()
        .if !SetCoalescableTimer(hwnd, TIMERID_NOCOALSCING, TIMER_ELAPSE, NULL, TIMERV_NO_COALESCING)
            .return -1
        .endif

        ;; Let's update the screen periodically.
        SetTimer(hwnd, TIMERID_UPDATE_SCREEN, TIMER_AUTO_REFRESH_ELAPSE, NULL)
        .return 0

    .case WM_MOUSEMOVE  ;; Tricky: also update the screen at every mouse move.
        InvalidateRect(hwnd, NULL, FALSE)
        .endc

    .case WM_TIMER
        .if (wParam < ARRAYSIZE(gTimerRec))

            TimerHandler(hwnd, wParam)

        .elseif (wParam == TIMERID_UPDATE_SCREEN)
            ;; Periodically update the results.
            .gotosw(WM_MOUSEMOVE)
        .endif
        .endc

    .case WM_PAINT
    .case WM_DISPLAYCHANGE

        .new ps:PAINTSTRUCT
        .new hdc:HDC = BeginPaint(hwnd, &ps)
        OnPaint(hdc, &ps.rcPaint)
        EndPaint(hwnd, &ps)
        .return 0

    .case WM_KEYDOWN
        .if (wParam == VK_SPACE)
            ;; Space key to power down the monitor.
            DefWindowProc(GetDesktopWindow(), WM_SYSCOMMAND, SC_MONITORPOWER, 2)
        .endif
        .endc

    .case WM_DESTROY
        PostQuitMessage(0)
        .return 1
    .case WM_CHAR
        .gotosw(WM_DESTROY) .if r8d == VK_ESCAPE
        .endc
    .endsw

    .return DefWindowProc(hwnd, message, wParam, lParam)

WndProc endp


wWinMain proc hInstance:HINSTANCE, hPrevInstance:HINSTANCE, lpCmdLine:LPWSTR, nCmdShow:SINT

  local msg:MSG

    mov ghInstance,hInstance

    .return .if !Initialize()

    .while GetMessage(&msg, NULL, 0, 0)
        TranslateMessage(&msg)
        DispatchMessage(&msg)
    .endw

    .return msg.wParam

wWinMain endp

    end _tstart
