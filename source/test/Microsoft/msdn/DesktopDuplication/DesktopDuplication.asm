
include limits.inc

include DisplayManager.inc
include DuplicationManager.inc
include OutputManager.inc
include ThreadManager.inc

;
; Forward Declarations
;
DDProc          proto :ptr
WndProc         proto :HWND, :UINT, :WPARAM, :LPARAM
ProcessCmdline  proto :ptr SINT
ShowHelp        proto

;
; Globals
;
.data

; Below are lists of errors expect from Dxgi API calls when a transition event
; like mode change, PnpStop, PnpStart desktop switch, TDR or session
; disconnect/reconnect. In all these cases we want the application to clean up
; the threads that process the desktop updates and attempt to recreate them.
; If we get an error that is not on the appropriate list then we exit the
; application

; These are the errors we expect from general Dxgi API due to a transition

SystemTransitionsExpectedErrors HRESULT \
        DXGI_ERROR_DEVICE_REMOVED,
        DXGI_ERROR_ACCESS_LOST,
        WAIT_ABANDONED,
        S_OK  ; Terminate list with zero valued HRESULT


; These are the errors we expect from IDXGIOutput1::DuplicateOutput due to a
; transition

CreateDuplicationExpectedErrors HRESULT \
        DXGI_ERROR_DEVICE_REMOVED,
        E_ACCESSDENIED,
        DXGI_ERROR_UNSUPPORTED,
        DXGI_ERROR_SESSION_DISCONNECTED,
        S_OK  ; Terminate list with zero valued HRESULT


; These are the errors we expect from IDXGIOutputDuplication methods due to a
; transition

FrameInfoExpectedErrors HRESULT \
        DXGI_ERROR_DEVICE_REMOVED,
        DXGI_ERROR_ACCESS_LOST,
        S_OK  ; Terminate list with zero valued HRESULT


; These are the errors we expect from IDXGIAdapter::EnumOutputs methods due to
; outputs becoming stale during a transition

EnumOutputsExpectedErrors HRESULT \
      DXGI_ERROR_NOT_FOUND,
      S_OK  ; Terminate list with zero valued HRESULT

;
; Class for progressive waits
;
.template WAIT_BAND
    WaitTime    UINT ?
    WaitCount   UINT ?
   .ends

define WAIT_BAND_COUNT 3
define WAIT_BAND_STOP 0

; Period in seconds that a new wait call is considered part of the same wait
; sequence

define WaitSequenceTimeInSeconds 2

.class DYNAMIC_WAIT

    m_CurrentWaitBandIdx UINT ?
    m_WaitCountInCurrentBand UINT ?
    m_QPCFrequency      LARGE_INTEGER <>
    m_LastWakeUpTime    LARGE_INTEGER <>
    m_QPCValid          BOOL ?

    DYNAMIC_WAIT        proc
    Release             proc
    DoWait              proc
   .ends

   .code

    assume rdi:ptr DYNAMIC_WAIT

DYNAMIC_WAIT::DYNAMIC_WAIT proc uses rdi

    mov rdi,@ComAlloc(DYNAMIC_WAIT)
    mov [rdi].m_QPCValid,QueryPerformanceFrequency(&[rdi].m_QPCFrequency)

   .return rdi

DYNAMIC_WAIT::DYNAMIC_WAIT endp


DYNAMIC_WAIT::Release proc

    ldr rcx,this

    free(rcx)
    ret

DYNAMIC_WAIT::Release endp


DYNAMIC_WAIT::DoWait proc uses rdi

    ldr rdi,this

    ; Is this wait being called with the period that we consider it to be part
    ; of the same wait sequence

   .new CurrentQPC:LARGE_INTEGER = {0}
    QueryPerformanceCounter(&CurrentQPC)

   .new WB[WAIT_BAND_COUNT]:WAIT_BAND = {
        {  250, 20 },
        { 2000, 60 },
        { 5000, WAIT_BAND_STOP } ; Never move past this band
        }

    mov  ecx,[rdi].m_CurrentWaitBandIdx
ifdef _WIN64
    imul rax,[rdi].m_QPCFrequency.QuadPart,WaitSequenceTimeInSeconds
    add  rax,[rdi].m_LastWakeUpTime.QuadPart

    .if ( [rdi].m_QPCValid && ( CurrentQPC.QuadPart <= rax ) )
else
    imul eax,sdword ptr [rdi].m_QPCFrequency.QuadPart,WaitSequenceTimeInSeconds
    add  eax,sdword ptr [rdi].m_LastWakeUpTime.QuadPart

    .if ( [rdi].m_QPCValid && ( sdword ptr CurrentQPC.QuadPart <= eax ) )
endif

        ; We are still in the same wait sequence, lets check if we should move
        ; to the next band

        .if ( ( WB[rcx*8].WaitCount != WAIT_BAND_STOP ) &&
              ( [rdi].m_WaitCountInCurrentBand > WB[rcx*8].WaitCount ) )

            inc ecx
            mov [rdi].m_CurrentWaitBandIdx,ecx
            mov [rdi].m_WaitCountInCurrentBand,0
        .endif

    .else

        ; Either we could not get the current time or we are starting a new
        ; wait sequence

        xor ecx,ecx
        mov [rdi].m_CurrentWaitBandIdx,ecx
        mov [rdi].m_WaitCountInCurrentBand,ecx
    .endif

    ; Sleep for the required period of time

    Sleep(WB[rcx*8].WaitTime)

    ; Record the time we woke up so we can detect wait sequences

    QueryPerformanceCounter(&[rdi].m_LastWakeUpTime)
    inc [rdi].m_WaitCountInCurrentBand
    ret

DYNAMIC_WAIT::DoWait endp


;
; Program entry point
;
WinMain proc WINAPI hInstance:HINSTANCE, hPrevInstance:HINSTANCE, lpCmdLine:LPSTR, nCmdShow:SINT

    .new SingleOutput:SINT
    .new OutMgr:ptr OUTPUTMANAGER()

    ; Synchronization

    .new UnexpectedErrorEvent:HANDLE = nullptr
    .new ExpectedErrorEvent:HANDLE = nullptr
    .new TerminateThreadsEvent:HANDLE = nullptr

    ; Window

    .new WindowHandle:HWND = nullptr

    .new CmdResult:bool = ProcessCmdline(&SingleOutput)

    .if ( !CmdResult )

        ShowHelp()
       .return 0
    .endif

    ; Event used by the threads to signal an unexpected error and we want to
    ; quit the app

    mov UnexpectedErrorEvent,CreateEvent(nullptr, TRUE, FALSE, nullptr)

    .if ( !UnexpectedErrorEvent )

        ProcessFailure(nullptr, L"UnexpectedErrorEvent creation failed",
                L"Error", E_UNEXPECTED, nullptr)
       .return 0
    .endif

    ; Event for when a thread encounters an expected error

    mov ExpectedErrorEvent,CreateEvent(nullptr, TRUE, FALSE, nullptr)

    .if ( !ExpectedErrorEvent )

        ProcessFailure(nullptr, L"ExpectedErrorEvent creation failed",
                L"Error", E_UNEXPECTED, nullptr)
       .return 0
    .endif

    ; Event to tell spawned threads to quit

    mov TerminateThreadsEvent,CreateEvent(nullptr, TRUE, FALSE, nullptr)

    .if ( !TerminateThreadsEvent )

        ProcessFailure(nullptr, L"TerminateThreadsEvent creation failed",
                L"Error", E_UNEXPECTED, nullptr)
       .return 0
    .endif

    ; Load simple cursor

    .new Cursor:HCURSOR = LoadCursor(nullptr, IDC_ARROW)

    .if (!Cursor)

        ProcessFailure(nullptr, L"Cursor load failed",
                L"Error", E_UNEXPECTED, nullptr)
       .return 0
    .endif

    ; Register class

   .new Wc:WNDCLASSEXW
    mov Wc.cbSize           , sizeof(WNDCLASSEXW)
    mov Wc.style            , CS_HREDRAW or CS_VREDRAW
    mov Wc.lpfnWndProc      , &WndProc
    mov Wc.cbClsExtra       , 0
    mov Wc.cbWndExtra       , LONG_PTR
    mov Wc.hInstance        , hInstance
    mov Wc.hIcon            , nullptr
    mov Wc.hCursor          , Cursor
    mov Wc.hbrBackground    , nullptr
    mov Wc.lpszMenuName     , nullptr
    mov Wc.lpszClassName    , &@CStr(L"ddasample")
    mov Wc.hIconSm          , nullptr

    .if (!RegisterClassExW(&Wc))

        ProcessFailure(nullptr, L"Window class registration failed",
                L"Error", E_UNEXPECTED, nullptr)
       .return 0
    .endif

    ; Create window

    .new WindowRect:RECT = {0, 0, 800, 600}

    AdjustWindowRect(&WindowRect, WS_OVERLAPPEDWINDOW, FALSE)

    mov ecx,WindowRect.right
    sub ecx,WindowRect.left
    mov edx,WindowRect.bottom
    sub edx,WindowRect.top

    mov WindowHandle, CreateWindowW(L"ddasample",
                            L"DXGI desktop duplication sample",
                            WS_OVERLAPPEDWINDOW,
                            0, 0, ecx, edx,
                            nullptr, nullptr, hInstance, OutMgr)
    .if (!WindowHandle)

        ProcessFailure(nullptr, L"Window creation failed",
                L"Error", E_FAIL, nullptr)
       .return 0
    .endif

    DestroyCursor(Cursor)

    ShowWindow(WindowHandle, nCmdShow)
    UpdateWindow(WindowHandle)

    .new ThreadMgr:ptr THREADMANAGER()
    .new DeskBounds:RECT
    .new OutputCount:UINT

    ; Message loop (attempts to update screen when no other messages to process)

    .new msg:MSG = {0}
    .new FirstTime:bool = true
    .new Occluded:bool = true
    .new DynamicWait:ptr DYNAMIC_WAIT()

    .while ( msg.message != WM_QUIT )

        .new retval:DUPL_RETURN = DUPL_RETURN_SUCCESS

        .if ( PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) )

            .if ( msg.message == WM_CHAR )

                .if ( msg.wParam == VK_ESCAPE )

                    .break
                .endif
            .endif

            .if ( msg.message == OCCLUSION_STATUS_MSG )

                ; Present may not be occluded now so try again

                mov Occluded,false

            .else

                ; Process window messages

                TranslateMessage(&msg)
                DispatchMessage(&msg)
            .endif

        .elseif ( WaitForSingleObjectEx(UnexpectedErrorEvent, 0, FALSE) == WAIT_OBJECT_0 )

            ; Unexpected error occurred so exit the application

            .break

        .else

            mov eax,FirstTime
            .if ( eax == false )

                .if ( WaitForSingleObjectEx(ExpectedErrorEvent, 0, FALSE) == WAIT_OBJECT_0 )
                    mov eax,true
                .else
                    mov eax,false
                .endif
            .endif

            .if ( eax == false )

                ; Nothing else to do, so try to present to write out to window
                ; if not occluded

                .if ( !Occluded )

                    mov rcx,ThreadMgr.GetPointerInfo()
                    mov retval,OutMgr.UpdateApplicationWindow(rcx, &Occluded)
                .endif

            .else

                .if ( FirstTime == false )

                    ; Terminate other threads

                    SetEvent(TerminateThreadsEvent)
                    ThreadMgr.WaitForThreadTermination()
                    ResetEvent(TerminateThreadsEvent)
                    ResetEvent(ExpectedErrorEvent)

                    ; Clean up

                    ThreadMgr.Clean()
                    OutMgr.CleanRefs()

                    ; As we have encountered an error due to a system transition we
                    ; wait before trying again, using this dynamic wait the wait
                    ; periods will get progressively long to avoid wasting too much
                    ; system resource if this state lasts a long time

                    DynamicWait.DoWait()

                .else

                    ; First time through the loop so nothing to clean up

                    mov FirstTime,false

                .endif

                ; Re-initialize

                mov retval,OutMgr.InitOutput(WindowHandle, SingleOutput, &OutputCount, &DeskBounds)

                .if ( retval == DUPL_RETURN_SUCCESS )

                    .new SharedHandle:HANDLE = OutMgr.GetSharedHandle()
                    .if ( SharedHandle )

                        mov retval,ThreadMgr.Initialize(
                                SingleOutput,
                                OutputCount,
                                UnexpectedErrorEvent,
                                ExpectedErrorEvent,
                                TerminateThreadsEvent,
                                SharedHandle,
                                &DeskBounds)

                    .else

                        DisplayMsg(L"Failed to get handle of shared surface", L"Error", S_OK)
                        mov retval,DUPL_RETURN_ERROR_UNEXPECTED
                    .endif
                .endif

                ; We start off in occluded state and we should immediate get a
                ; occlusion status window message

                mov Occluded,true
            .endif
        .endif

        ; Check if for errors

        .if ( retval != DUPL_RETURN_SUCCESS )

            .if ( retval == DUPL_RETURN_ERROR_EXPECTED )

                ; Some type of system transition is occurring so retry

                SetEvent(ExpectedErrorEvent)

            .else

                ; Unexpected error so exit

                .break
            .endif
        .endif
    .endw

    ; Make sure all other threads have exited

    .if ( SetEvent(TerminateThreadsEvent) )

        ThreadMgr.WaitForThreadTermination()
    .endif

    ; Clean up

    CloseHandle(UnexpectedErrorEvent)
    CloseHandle(ExpectedErrorEvent)
    CloseHandle(TerminateThreadsEvent)

    SafeRelease(ThreadMgr)
    SafeRelease(OutMgr)

    .if ( msg.message == WM_QUIT )

        ; For a WM_QUIT message we should return the wParam value

        .return msg.wParam
    .endif

    .return 0

WinMain endp

;
; Shows help
;
ShowHelp proc

    DisplayMsg(L"The following optional parameters can be used -\n"
                "  /output [all | n]\t\tto duplicate all outputs or the nth output\n"
                "  /?\t\t\tto display this help section",
               L"Proper usage", S_OK)
    ret

ShowHelp endp

;
; Process command line parameters
;
ProcessCmdline proc uses rsi rdi rbx Output:ptr SINT

    ldr rdi,Output

    assume rdi:ptr SINT

    mov [rdi],-1

    ; __argv and __argc are global vars set by system

    .for ( ebx = 1: ebx < __argc: ++ebx )

        mov rdx,__argv
        mov rsi,[rdx+rbx*string_t]

        .if ( strcmp(rsi, "-output") )
              strcmp(rsi, "/output")
        .endif

        .if ( eax == 0 )

            inc ebx
            .if ( ebx >= __argc )
                .return false
            .endif

            mov rdx,__argv
            mov rsi,[rdx+rbx*string_t]

            .if ( strcmp(rsi, "all") == 0 )

                mov [rdi],-1
            .else
                atoi(rsi)
                mov [rdi],eax
            .endif
            .continue
        .else
            .return false
        .endif
    .endf
    .return true

ProcessCmdline endp

;
; Window message processor
;
WndProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

    ldr rcx,hWnd
    ldr edx,message
    ldr rax,lParam

    .switch ( edx )

    .case WM_CREATE

        SetWindowLongPtr(rcx, GWLP_USERDATA, [rax].CREATESTRUCT.lpCreateParams)
       .return 1

    .case WM_DESTROY

        PostQuitMessage(0)
       .endc

    .case WM_SIZE

        ; Tell output manager that window size has changed

        [GetWindowLongPtr(rcx, GWLP_USERDATA)].OUTPUTMANAGER.WindowResize()
       .endc

    .default
        .return DefWindowProc(rcx, edx, wParam, rax)
    .endsw
    .return 0

WndProc endp

;
; Entry point for new duplication threads
;
    assume rsi:ptr THREAD_DATA

DDProc proc uses rsi rdi rbx Param:ptr

    ; Data passed in from thread creation

    ldr rsi,Param

    ; Classes

    .new DispMgr:ptr DISPLAYMANAGER()
    .new DuplMgr:ptr DUPLICATIONMANAGER()

    ; D3D objects

    .new SharedSurf:ptr ID3D11Texture2D = nullptr
    .new KeyMutex:ptr IDXGIKeyedMutex = nullptr

    ; Get desktop

    .new retval:DUPL_RETURN
    .new CurrentDesktop:HDESK = OpenInputDesktop(0, FALSE, GENERIC_ALL)

    .if ( !rax )

        ; We do not have access to the desktop so request a retry

        SetEvent([rsi].ExpectedErrorEvent)
        mov retval,DUPL_RETURN_ERROR_EXPECTED
        jmp Exit
    .endif

    ; Attach desktop to this thread

    .if SetThreadDesktop(CurrentDesktop)
        mov eax,true
    .endif
    .new DesktopAttached:bool = eax

    CloseDesktop(CurrentDesktop)
    mov CurrentDesktop,nullptr

    .if ( !DesktopAttached )

        ; We do not have access to the desktop so request a retry

        mov retval,DUPL_RETURN_ERROR_EXPECTED
        jmp Exit
    .endif

    ; New display manager

    DispMgr.InitD3D(&[rsi].DxRes)

    ; Obtain handle to sync shared Surface

    .new pDevice:ptr ID3D11Device = [rsi].DxRes.Device
    .new hr:HRESULT = pDevice.OpenSharedResource(
            [rsi].TexSharedHandle, &IID_ID3D11Texture2D, &SharedSurf)

    .if (FAILED(hr))

        mov retval,ProcessFailure([rsi].DxRes.Device,
                L"Opening shared texture failed",
                L"Error", hr, &SystemTransitionsExpectedErrors)
        jmp Exit
    .endif

    mov hr,SharedSurf.QueryInterface(&IID_IDXGIKeyedMutex, &KeyMutex)
    .if (FAILED(hr))

        mov retval,ProcessFailure(nullptr,
                L"Failed to get keyed mutex interface in spawned thread",
                L"Error", hr, nullptr)
        jmp Exit
    .endif

    ; Make duplication manager

    mov retval,DuplMgr.InitDupl([rsi].DxRes.Device, [rsi].Output)
    .if ( retval != DUPL_RETURN_SUCCESS )

        jmp Exit
    .endif

    ; Get output description

   .new DesktopDesc:DXGI_OUTPUT_DESC = {0}

    DuplMgr.GetOutputDesc(&DesktopDesc)

    ; Main duplication loop

   .new WaitToProcessCurrentFrame:bool = false
   .new CurrentData:FRAME_DATA

    .while ( WaitForSingleObjectEx([rsi].TerminateThreadsEvent, 0, FALSE) == WAIT_TIMEOUT )

        .if ( !WaitToProcessCurrentFrame )

            ; Get new frame from desktop duplication

           .new TimeOut:bool
            mov retval,DuplMgr.GetFrame(&CurrentData, &TimeOut)

            .if ( retval != DUPL_RETURN_SUCCESS )

                ; An error occurred getting the next frame drop out of loop which
                ; will check if it was expected or not

                .break
            .endif

            ; Check for timeout

            .if ( TimeOut )

                ; No new frame at the moment

                .continue
            .endif
        .endif

        ; We have a new frame so try and process it
        ; Try to acquire keyed mutex in order to access shared surface

        mov hr,KeyMutex.AcquireSync(0, 1000)
        .if ( hr == WAIT_TIMEOUT )

            ; Can't use shared surface right now, try again later

            mov WaitToProcessCurrentFrame,true
           .continue

        .elseif ( FAILED(hr) )

            ; Generic unknown failure

            mov retval,ProcessFailure([rsi].DxRes.Device,
                    L"Unexpected error acquiring KeyMutex",
                    L"Error", hr, &SystemTransitionsExpectedErrors)
            DuplMgr.DoneWithFrame()
           .break
        .endif

        ; We can now process the current frame

        mov WaitToProcessCurrentFrame,false

        ; Get mouse info

        mov retval,DuplMgr.GetMouse([rsi].PtrInfo, &CurrentData.FrameInfo,
                [rsi].OffsetX, [rsi].OffsetY)
        .if ( retval != DUPL_RETURN_SUCCESS )

            DuplMgr.DoneWithFrame()
            KeyMutex.ReleaseSync(1)
           .break
        .endif

        ; Process new frame

        mov retval,DispMgr.ProcessFrame(&CurrentData, SharedSurf,
                [rsi].OffsetX, [rsi].OffsetY, &DesktopDesc)
        .if ( retval != DUPL_RETURN_SUCCESS )

            DuplMgr.DoneWithFrame()
            KeyMutex.ReleaseSync(1)
           .break
        .endif

        ; Release acquired keyed mutex

        mov hr,KeyMutex.ReleaseSync(1)
        .if (FAILED(hr))

            mov retval,ProcessFailure([rsi].DxRes.Device,
                    L"Unexpected error releasing the keyed mutex", L"Error",
                    hr, &SystemTransitionsExpectedErrors)

            DuplMgr.DoneWithFrame()
           .break
        .endif

        ; Release frame back to desktop duplication

        mov retval,DuplMgr.DoneWithFrame()
        .if ( retval != DUPL_RETURN_SUCCESS )

            .break
        .endif
    .endw

Exit:
    .if ( retval != DUPL_RETURN_SUCCESS )

        .if ( retval == DUPL_RETURN_ERROR_EXPECTED )

            ; The system is in a transition state so request the duplication
            ; be restarted

            SetEvent([rsi].ExpectedErrorEvent)

        .else

            ; Unexpected error so exit the application

            SetEvent([rsi].UnexpectedErrorEvent)
        .endif
    .endif

    SafeRelease(SharedSurf)
    SafeRelease(KeyMutex)
    SafeRelease(DuplMgr)
    SafeRelease(DispMgr)
   .return 0

DDProc endp


ProcessFailure proc Device:ptr ID3D11Device, String:LPCWSTR, Title:LPCWSTR,
        hr:HRESULT, ExpectedErrors:ptr HRESULT

    .new TranslatedHr:HRESULT

    ; On an error check if the DX device is lost

    .if ( Device )

        .new DeviceRemovedReason:HRESULT = Device.GetDeviceRemovedReason()

        .switch ( DeviceRemovedReason )

        .case DXGI_ERROR_DEVICE_REMOVED
        .case DXGI_ERROR_DEVICE_RESET
        .case E_OUTOFMEMORY

            ; Our device has been stopped due to an external event on the GPU
            ; so map them all to device removed and continue processing the
            ; condition

            mov TranslatedHr,DXGI_ERROR_DEVICE_REMOVED
           .endc


        .case S_OK

            ; Device is not removed so use original error

            mov TranslatedHr,hr
           .endc


        .default

            ; Device is removed but not a error we want to remap

            mov TranslatedHr,DeviceRemovedReason
        .endsw

    .else
        mov TranslatedHr,hr
    .endif

    ; Check if this error was expected or not

    .if ( ExpectedErrors )

        mov rcx,ExpectedErrors
        mov eax,TranslatedHr

        .while ( HRESULT ptr [rcx] != S_OK )

            .if ( [rcx] == eax )

                .return DUPL_RETURN_ERROR_EXPECTED
            .endif
            add rcx,HRESULT
        .endw
    .endif

    ; Error was not expected so display the message box

    DisplayMsg(String, Title, TranslatedHr)

   .return DUPL_RETURN_ERROR_UNEXPECTED

ProcessFailure endp

;
; Displays a message
;
DisplayMsg proc String:LPCWSTR, Title:LPCWSTR, hr:HRESULT

    .if ( SUCCEEDED(hr) )

        MessageBoxW(nullptr, String, Title, MB_OK)
       .return
    .endif

    wcslen(String)
    add eax,26
   .new StringLen:UINT = eax

    lea rcx,[rax*2+2]

   .new OutStr:ptr wchar_t = malloc(rcx)

    .if ( !OutStr )

        .return
    .endif

   .new LenWritten:SINT = swprintf_s(
            OutStr, StringLen, L"%s with 0x%X.", String, hr)
    .if ( LenWritten != -1 )

        MessageBoxW(nullptr, OutStr, Title, MB_OK)
    .endif

    free(OutStr)
    ret

DisplayMsg endp

    end
