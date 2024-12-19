; CPUUSAGE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include Windows.inc
include gdiplus.inc

define _CRT_USE_WINAPI_FAMILY_DESKTOP_APP
include process.inc
include stdio.inc
include Psapi.inc
include Pdh.inc
include tchar.inc

float  typedef real4
double typedef real8

define MAXSIZE 1024
define SAMPLE_INTERVAL 1


.class WString

    name            PCWSTR ?
    next            ptr WString ?

    WString         proc
    Release         proc
    begin           proc
    push_back       proc :PCWSTR
   .ends

.class Log

    time            DWORD ?
    value           double ?
    next            ptr Log ?

    Log             proc
    Release         proc
    push_back       proc :dword, :real8
    size            proc
   .ends

.class CounterInfo

    counterName     PCWSTR ?
    counter         PDH_HCOUNTER ?
    logs            ptr Log ?
    next            ptr CounterInfo ?

    CounterInfo     proc
    Release         proc
    size            proc
    push_back       proc :PDH_HCOUNTER, :PCWSTR
   .ends

.class Query

    query           PDH_HQUERY ?
    Event           HANDLE ?
    time            int_t ?
    fIsWorking      bool ?
    vciCounters     ptr CounterInfo ?

    Query           proc
    Release         proc
    Init            proc
    AddCounterInfo  proc :PCWSTR
    QRecord         proc
    CleanOldRecord  proc
   .ends


define CENTER_X 55.0
define CENTER_Y 580.0
define SCALE_X 7.0
define SCALE_Y 5.0

define IDC_BUTTON_ADD 101
define IDC_COMBOBOX_COUNTER 102
define IDC_BUTTON_REFRESH 103

OnPaint                 proto private :HDC
GetProcessorCount       proto private
GetProcessNames         proto private
GetValidCounterNames    proto private

    .data

     diff_x             int_t       0
     hwnd               HWND        NULL
     g_hInst            HINSTANCE   NULL
     g_hAddButton       HWND        NULL
     g_hRefreshButton   HWND        NULL
     g_hCounterComboBox HWND        NULL
     query              ptr Query   NULL
     fContinueLog       bool        true
     ListItem           wchar_t     256 dup(?)


    .code

WString::WString proc

    @ComAlloc(WString)
    ret

WString::WString endp

    assume rsi:ptr WString

WString::Release proc uses rsi rdi

    .for ( rsi = rcx : rsi : )
        mov rcx,[rsi].name
        mov rdi,[rsi].next
        .if ( rcx )
            free(rcx)
        .endif
        free(rsi)
        mov rsi,rdi
    .endf
    ret

WString::Release endp

WString::begin proc

    UNREFERENCED_PARAMETER(this)

    xor eax,eax
    .if ( [rcx].WString.name != rax )
        mov rax,rcx
    .endif
    ret

WString::begin endp

WString::push_back proc uses rsi rdi string:PCTSTR

    UNREFERENCED_PARAMETER(this)
    UNREFERENCED_PARAMETER(string)

    mov rsi,rcx
    mov rdi,_wcsdup(rdx)

    .if ( [rsi].name == NULL )
        mov [rsi].WString.name,rdi
    .else
        .if ( malloc(WString) )

            mov rcx,[rsi]
            mov [rax],rcx
            mov [rax].WString.next,NULL
            .while ( [rsi].next )
                mov rsi,[rsi].next
            .endw
            mov [rsi].next,rax
            mov rsi,rax
            mov [rsi].name,rdi
        .endif
    .endif
    ret

WString::push_back endp


    assume rsi:ptr Log

Log::Log proc

    @ComAlloc(Log)
    ret

Log::Log endp

Log::Release proc

    free(rcx)
    ret

Log::Release endp

Log::push_back proc uses rsi Time:dword, Value:double

    UNREFERENCED_PARAMETER(this)
    UNREFERENCED_PARAMETER(Time)
    UNREFERENCED_PARAMETER(Value)

    mov eax,[rcx].Log.time
    or  rax,[rcx].Log.value
    or  rax,[rcx].Log.next
    .if ( rax == NULL )

        mov [rcx].Log.time,edx
        movsd [rcx].Log.value,xmm2

    .else

        mov rsi,rcx
        .if ( malloc(Log) )

            mov rcx,[rsi]
            mov [rax],rcx
            mov [rax].Log.next,NULL
            .while ( [rsi].next )
                mov rsi,[rsi].next
            .endw
            mov [rsi].next,rax
            mov rsi,rax
            mov [rsi].time,Time
            mov [rsi].value,Value
        .endif
    .endif
    ret

Log::push_back endp

Log::size proc

    UNREFERENCED_PARAMETER(this)

    mov eax,[rcx].Log.time
    or  rax,[rcx].Log.value
    or  rax,[rcx].Log.next
    .if ( rax == NULL )
        .return
    .endif
    mov eax,1
    .while ( [rcx].Log.next )
        inc eax
        mov rcx,[rcx].Log.next
    .endw
    ret

Log::size endp


    assume rsi:ptr CounterInfo

CounterInfo::CounterInfo proc uses rsi

    mov rsi,@ComAlloc(CounterInfo)
    mov [rsi].logs,@ComAlloc(Log)

   .return( rsi )

CounterInfo::CounterInfo endp

CounterInfo::Release proc

    mov rcx,[rcx].CounterInfo.logs
    [rcx].Log.Release()

    free(this)
    ret

CounterInfo::Release endp

CounterInfo::size proc

    UNREFERENCED_PARAMETER(this)

    mov rax,[rcx].CounterInfo.counterName
    or  rax,[rcx].CounterInfo.counter
    or  rax,[rcx].CounterInfo.next
    .if ( rax == NULL )
        .return
    .endif
    mov eax,1
    .while ( [rcx].CounterInfo.next )
        inc eax
        mov rcx,[rcx].CounterInfo.next
    .endw
    ret

CounterInfo::size endp

CounterInfo::push_back proc uses rsi Counter:PDH_HCOUNTER, Name:PCWSTR

    UNREFERENCED_PARAMETER(this)

    mov rsi,rcx
    mov rax,[rsi].counterName
    or  rax,[rsi].counter
    or  rax,[rsi].next
    .if ( rax == NULL )

        mov [rsi].counterName,r8
        mov [rsi].counter,rdx
        .return
    .endif
    .if ( malloc(CounterInfo) )

        mov rcx,[rsi]
        mov [rax],rcx
        mov [rax].CounterInfo.next,NULL
        .while ( [rsi].next )
            mov rsi,[rsi].next
        .endw
        mov [rsi].next,rax
        mov rsi,rax
        mov [rsi].counterName,Name
        mov [rsi].counter,Counter
        mov [rsi].logs,@ComAlloc(Log)
    .endif
    ret

CounterInfo::push_back endp


    assume rsi:ptr Query

Query::Query proc uses rsi

   .new ci:ptr CounterInfo()
    mov rsi,@ComAlloc(Query)
    mov [rsi].vciCounters,ci
   .return( rsi )

Query::Query endp

Query::Release proc

    this.vciCounters.Release()
    free(this)
    ret

Query::Release endp

Query::Init proc uses rsi

    UNREFERENCED_PARAMETER(this)

    mov rsi,rcx
    mov [rsi].fIsWorking,false
    mov [rsi].time,0

    .new status:PDH_STATUS = PdhOpenQuery(NULL, 0, &[rsi].query)
    .return .if ( status != ERROR_SUCCESS )

    mov [rsi].Event,CreateEvent(NULL, FALSE, FALSE, L"MyEvent")

    .return .if ( [rsi].Event == NULL )
    mov [rsi].fIsWorking,true
    ret

Query::Init endp

Query::AddCounterInfo proc uses rsi name:PCWSTR

    mov rsi,rcx
    .if ( [rsi].fIsWorking )

        .new status:PDH_STATUS
        .new counter:PDH_HCOUNTER

        ; PdhAddCounter() -- local strings..

        mov status,PdhAddEnglishCounter([rsi].query, name, 0, &counter)
        .return .if ( status != ERROR_SUCCESS )
        this.vciCounters.push_back(counter, name)
    .endif
    ret

Query::AddCounterInfo endp

    assume rdi:ptr CounterInfo

Query::QRecord proc uses rsi rdi

    UNREFERENCED_PARAMETER(this)

    mov rsi,rcx

    .new status:PDH_STATUS
    .new CounterType:ULONG
    .new WaitResult:ULONG
    .new DisplayValue:PDH_FMT_COUNTERVALUE

    .return .ifd ( PdhCollectQueryData([rsi].query) != ERROR_SUCCESS )
    .return .ifd ( PdhCollectQueryDataEx([rsi].query, SAMPLE_INTERVAL, [rsi].Event) != ERROR_SUCCESS )

    mov WaitResult,WaitForSingleObject([rsi].Event, INFINITE)

    .if ( WaitResult == WAIT_OBJECT_0 )

        .for ( rdi = [rsi].vciCounters : rdi : rdi = [rdi].next )

            .continue .ifd ( PdhGetFormattedCounterValue([rdi].counter,
                PDH_FMT_DOUBLE, &CounterType, &DisplayValue) != ERROR_SUCCESS )

            .new lp:ptr Log = [rdi].logs
            lp.push_back([rsi].time, DisplayValue.doubleValue)
        .endf
    .endif
    inc [rsi].time
    ret

Query::QRecord endp

Query::CleanOldRecord proc uses rsi rdi rbx

    UNREFERENCED_PARAMETER(this)

    mov rsi,rcx
    .if ( [rsi].time > 100 )

        .for ( rdi = [rsi].vciCounters : rdi : rdi = [rdi].next )

            .new lp:ptr Log = [rdi].logs
            .if ( lp.size() > 100 )

                mov rcx,lp
                mov rbx,[rcx].Log.next
                free(rcx)
                mov [rdi].logs,rbx
            .endif
        .endf
        mov eax,[rsi].time
        sub eax,100
        .return
    .else
        .return 0
    .endif
    ret

Query::CleanOldRecord endp


GetProcessorCount proc

    .new sysinfo:SYSTEM_INFO
     GetSystemInfo(&sysinfo)

    .return sysinfo.dwNumberOfProcessors

GetProcessorCount endp

    assume rsi:ptr WString
    assume rdi:nothing

GetProcessNames proc uses rsi rbx

    .new dwProcessID[MAXSIZE]:DWORD
    .new cbProcess:DWORD
    .new cProcessID:DWORD
    .new fResult:BOOL = FALSE
    .new index:DWORD

    .new hProcess:HANDLE
    .new lphModule[MAXSIZE]:HMODULE
    .new cbNeeded:DWORD
    .new len:int_t
    .new vProcessNames:ptr WString()

    mov fResult,EnumProcesses(&dwProcessID, sizeof(dwProcessID), &cbProcess)

    .if ( !fResult )

        .return vProcessNames
    .endif

    mov eax,cbProcess
    shr eax,2
    mov cProcessID,eax

    .for ( ebx = 0: ebx < cProcessID: ebx++ )

        .new szProcessName[MAX_PATH]:TCHAR
         mov hProcess,OpenProcess( PROCESS_QUERY_INFORMATION or PROCESS_VM_READ, FALSE, dwProcessID[rbx*DWORD] )

        .if ( hProcess != NULL )

            .if ( EnumProcessModulesEx( hProcess, &lphModule, sizeof(lphModule), &cbNeeded, LIST_MODULES_ALL) )

                .if ( GetModuleBaseName( hProcess, lphModule[0], &szProcessName, MAX_PATH ) )

                    mov len,_tcslen(&szProcessName)
                    lea rcx,szProcessName
                    lea rcx,[rcx+rax*TCHAR-4*TCHAR]
                    _tcscpy(rcx, "\0")

                    .new fProcessExists:bool = false
                    .new count:int_t = 0
                    .new szProcessNameWithPrefix[MAX_PATH]:TCHAR

                    swprintf_s(&szProcessNameWithPrefix, MAX_PATH, "%s", &szProcessName)

                    .repeat

                        .if ( count > 0 )
                            swprintf_s(&szProcessNameWithPrefix, MAX_PATH, "%s#%d", &szProcessName, count)
                        .endif
                        mov fProcessExists,false
                        .for ( rsi = vProcessNames.begin() : rsi : rsi = [rsi].next )

                            .if ( _tcscmp( [rsi].name, &szProcessNameWithPrefix ) == 0 )

                                mov fProcessExists,true
                               .break
                            .endif
                        .endf
                        inc count

                    .until( !fProcessExists )

                    vProcessNames.push_back(&szProcessNameWithPrefix)
                .endif
            .endif
        .endif
    .endf
    .return vProcessNames

GetProcessNames endp

GetValidCounterNames proc uses rsi

    .new validCounterNames:ptr WString()
    .new dwNumberOfProcessors:DWORD = GetProcessorCount()
    .new vszProcessNames:ptr WString
    .new szCounterName[MAX_PATH]:TCHAR

    validCounterNames.push_back("\\Processor(_Total)\\% Processor Time")
    validCounterNames.push_back("\\Processor(_Total)\\% Idle Time")

    .for ( esi = 0: esi < dwNumberOfProcessors: esi++ )

        swprintf_s(&szCounterName, MAX_PATH, "\\Processor(%u)\\%% Processor Time", esi)
        validCounterNames.push_back(&szCounterName)
        swprintf_s(&szCounterName, MAX_PATH, "\\Processor(%u)\\%% Idle Time", esi)
        validCounterNames.push_back(&szCounterName)
    .endf

    mov vszProcessNames,GetProcessNames()

    .for ( rsi = vszProcessNames.begin() : rsi : rsi = [rsi].next )

        swprintf_s(&szCounterName, MAX_PATH, "\\Process(%s)\\%% Processor Time", [rsi].name)
        validCounterNames.push_back(&szCounterName)
    .endf
    vszProcessNames.Release()
    .return validCounterNames

GetValidCounterNames endp

    assume rsi:nothing

KeepLogging proc p:ptr

    UNREFERENCED_PARAMETER(p)

    .while ( fContinueLog )
        .new q:ptr Query = query
        .if ( q.vciCounters.size() > 0 )
            q.QRecord()
            mov diff_x,q.CleanOldRecord()
            InvalidateRect(hwnd, NULL, TRUE)
        .endif
    .endw
    .return 0

KeepLogging endp

PlotLine proc gp:ptr Graphics, p:ptr Pen, x1:float, y1:float, x2:float, y2:float, fDiff:bool

    movss xmm0,x1
    movss xmm1,x2

    .if ( fDiff )

        cvtsi2ss xmm2,diff_x
        subss xmm0,xmm2
        subss xmm1,xmm2
    .endif

    mulss xmm0,SCALE_X
    addss xmm0,CENTER_X
    mulss xmm1,SCALE_X
    addss xmm1,CENTER_X

    movss xmm2,CENTER_Y
    movss xmm3,CENTER_Y
    movss xmm4,y1
    mulss xmm4,SCALE_Y
    subss xmm2,xmm4
    movss xmm4,y2
    mulss xmm4,SCALE_Y
    subss xmm3,xmm4

    .if ( ( xmm0 >= 0.0 && xmm1 >= 0.0 ) || ( !fDiff ) )

       .new g:Graphics
        mov rcx,gp
        mov g,[rcx]
        g.DrawLine( p, xmm0, xmm2, xmm1, xmm3 )
    .endif
    ret

PlotLine endp

PlotString proc gp:ptr Graphics, x1:float, y1:float, text:PCWSTR, len:int_t

    movss xmm0,x1
    movss xmm1,CENTER_Y
    movss xmm2,y1
    mulss xmm0,SCALE_X
    addss xmm0,CENTER_X
    mulss xmm2,SCALE_Y
    subss xmm1,xmm2

   .new origin:PointF(xmm0, xmm1)
   .new blackBrush:SolidBrush(Black)
   .new myFont:Font(L"Arial", 16.0)

   .new g:Graphics
    mov rcx,gp
    mov g,[rcx]
    g.DrawString(text, len, &myFont, origin, &blackBrush)

    blackBrush.Release()
    myFont.Release()
    ret

PlotString endp

OnPaint proc uses rsi rdi rbx hdc:HDC

   .new graphics:Graphics(hdc)
   .new pen:Pen(Black)

    graphics.DrawRectangle(&pen, 10, 50, 770, 550)

    ;; AXIS

    PlotLine(&graphics, &pen, 0.0, 0.0, 0.0, 100.0, false)
    PlotLine(&graphics, &pen, 0.0, 0.0, 100.0, 0.0, false)

    .new buffer[4]:wchar_t
    .new i:int_t = 10
    .for ( : i <= 100 : i += 10 )

        cvtsi2ss xmm0,i
        PlotLine(&graphics, &pen, 0.0, xmm0, -1.0, xmm0, false)
        swprintf_s(&buffer, 4, L"%d", i)

        cvtsi2ss xmm2,i
        movss xmm1,-5.0
        .if ( i == 100 )
            movss xmm1,-6.0
        .endif
        PlotString(&graphics, xmm1, xmm2, &buffer, 3)
    .endf

    mov rsi,query
    mov rsi,[rsi].Query.vciCounters

    assume rsi:ptr CounterInfo
    assume rdi:ptr Log

    .for ( : rsi : rsi = [rsi].next )

        .new prevTime:double = -1.0
        .new prevValue:double = -1.0
        .for ( rdi = [rsi].logs : rdi : rdi = [rdi].next )

            cvtsd2ss xmm2,prevTime
            cvtsd2ss xmm3,prevValue

            .if ( xmm2 != -1.0 && xmm3 != -1.0 )

                cvtsi2ss xmm4,[rdi].time
                cvtsd2ss xmm5,[rdi].value

                PlotLine(&graphics, &pen, xmm2, xmm3, xmm4, xmm5, true)
            .endif

            cvtsi2sd xmm0,[rdi].time
            movsd prevTime,xmm0
            mov prevValue,[rdi].value
        .endf
    .endf
    pen.Release()
    graphics.Release()
    ret

OnPaint endp

    assume rsi:ptr WString

RefreshCounterList proc uses rsi

    SendMessage(g_hCounterComboBox, CB_RESETCONTENT, 0, 0)

    .new CounterNames:ptr WString = GetValidCounterNames()
    .for ( rsi = rax : rsi : rsi = [rsi].next )
        SendMessage(g_hCounterComboBox, CB_ADDSTRING, 0, [rsi].name)
    .endf
    SendMessage(g_hCounterComboBox, CB_SETCURSEL, 0, 0)
    SendMessage(g_hCounterComboBox, CB_GETLBTEXT, 0, &ListItem)
    CounterNames.Release()
    ret

RefreshCounterList endp

WindowProc proc hWnd:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM

    .new hdc:HDC
    .new ps:PAINTSTRUCT
    .new ItemIndex:int_t

    .switch ( uMsg )

    .case WM_COMMAND
        .if ( lParam && ( HIWORD(wParam) == BN_CLICKED ) )

            .switch ( LOWORD(wParam) )

            .case IDC_BUTTON_ADD

                query.AddCounterInfo(&ListItem)
               .endc

            .case IDC_BUTTON_REFRESH

                RefreshCounterList()
               .endc

            .default
                .endc
            .endsw
        .endif

        .if ( HIWORD(wParam) == CBN_SELCHANGE )

            mov ItemIndex,SendMessage(lParam, CB_GETCURSEL, 0, 0)
            SendMessage(lParam, CB_GETLBTEXT, ItemIndex, &ListItem)
        .endif
        .return 0

    .case WM_PAINT
        mov hdc,BeginPaint(hWnd, &ps)
        OnPaint(hdc)
        EndPaint(hWnd, &ps)
       .return 0

    .case WM_DESTROY
        PostQuitMessage(0)
       .return 0
    .case WM_GETMINMAXINFO
    .case WM_SIZING
        .return 0
    .case WM_CREATE


        mov g_hAddButton,CreateWindowEx(0,              ;; more or ''extended'' styles
                L"BUTTON",                              ;; GUI ''class'' to create
                L"Add",                                 ;; GUI caption
                WS_CHILD or WS_VISIBLE or BS_DEFPUSHBUTTON, ;; control styles separated by |
                640,                                    ;; LEFT POSITION (Position from left)
                10,                                     ;; TOP POSITION  (Position from Top)
                100,                                    ;; WIDTH OF CONTROL
                30,                                     ;; HEIGHT OF CONTROL
                hWnd,                                   ;; Parent window handle
                IDC_BUTTON_ADD,                         ;; control''s ID for WM_COMMAND
                g_hInst,                                ;; application instance
                NULL)

        mov g_hRefreshButton,CreateWindowEx(0,          ;; more or ''extended'' styles
                L"BUTTON",                              ;; GUI ''class'' to create
                L"Refresh",                             ;; GUI caption
                WS_CHILD or WS_VISIBLE or BS_DEFPUSHBUTTON, ;; control styles separated by |
                520,                                    ;; LEFT POSITION (Position from left)
                10,                                     ;; TOP POSITION  (Position from Top)
                100,                                    ;; WIDTH OF CONTROL
                30,                                     ;; HEIGHT OF CONTROL
                hWnd,                                   ;; Parent window handle
                IDC_BUTTON_REFRESH,                     ;; control''s ID for WM_COMMAND
                g_hInst,                                ;; application instance
                NULL);

        mov g_hCounterComboBox,CreateWindowEx(0,        ;; more or ''extended'' styles
                L"ComboBox",                            ;; GUI ''class'' to create
                NULL,                                   ;; GUI caption
                CBS_DROPDOWN or WS_VSCROLL or WS_CHILD or WS_VISIBLE, ;; control styles separated by |
                10,                                     ;; LEFT POSITION (Position from left)
                10,                                     ;; TOP POSITION  (Position from Top)
                500,                                    ;; WIDTH OF CONTROL
                400,                                    ;; HEIGHT OF CONTROL
                hWnd,                                   ;; Parent window handle
                IDC_COMBOBOX_COUNTER,                   ;; control''s ID for WM_COMMAND
                g_hInst,                                ;; application instance
                NULL)

            RefreshCounterList()

    .endsw

    .return DefWindowProc(hWnd, uMsg, wParam, lParam)

WindowProc endp

wWinMain proc hInstance:HINSTANCE, hPrevInstance:HINSTANCE, lpCmdLine:PWSTR , nCmdShow:int_t

    .new hThread:HANDLE
    .new threadID:dword
    .new q:ptr Query()

    mov query,q

    q.Init()

    .new wc:WNDCLASS = {0}

    mov wc.lpfnWndProc,&WindowProc
    mov wc.hInstance,hInstance
    mov wc.lpszClassName,&@CStr(L"CppCpuUsage")
    mov wc.hbrBackground,GetStockObject(WHITE_BRUSH)

    mov g_hInst,hInstance

    RegisterClass(&wc)

    mov hwnd,CreateWindowEx(
        0,
        L"CppCpuUsage",
        L"CppCpuUsage",
        WS_OVERLAPPED or WS_CAPTION or WS_SYSMENU or WS_MINIMIZEBOX or WS_MAXIMIZEBOX,
        5, 5, 800, 640,
        NULL,
        NULL,
        hInstance,
        NULL)

    .if ( hwnd == NULL )

        .return 0
    .endif
    ;; Initialize GDI+.
    .new gdiplus:GdiPlus()

    ShowWindow(hwnd, nCmdShow)

    mov hThread,_beginthreadex( NULL, 0, &KeepLogging, NULL, 0, &threadID )

    .new msg:MSG = {0}
    .while ( GetMessage(&msg, NULL, 0, 0) )

        TranslateMessage(&msg)
        DispatchMessage(&msg)
    .endw
    gdiplus.Release()
   .return 0

wWinMain endp

    end _tstart
