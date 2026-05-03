;
; https://github.com/microsoft/Windows-classic-samples/tree/master/Samples/
;  Win7Samples/winbase/Eventing/Controller
;
include windows.inc
include evntrace.inc
include stdio.inc
include tchar.inc

MAXSTR equ 1024

;;
;; Default trace file name.
;;

DEFAULT_LOGFILE_NAME equ <"C:\\LogFile.Etl">

;;
;; On Windows 2000, we support up to 32 loggers at once.
;; On Windows XP and .NET server, we support up to 64 loggers.
;;

MAXIMUM_LOGGERS equ 64

;;
;; In this sample, we support the following actions.
;; Additional actions that we do not use in this sample include
;; Flush and Enumerate Guids functionalities. They are supported
;; only on XP or higher version.
;;

ACTION_QUERY    equ 0
ACTION_START    equ 1
ACTION_STOP     equ 2
ACTION_UPDATE   equ 3
ACTION_LIST     equ 4
ACTION_ENABLE   equ 5
ACTION_HELP     equ 6

ACTION_UNDEFINED equ 10
option dllimport:none

PrintLoggerStatus   proto LoggerInfo:PEVENT_TRACE_PROPERTIES, Status:ULONG
HexToLong           proto String:ptr TCHAR
StringToGuid        proto String:ptr TCHAR, Guid:LPGUID
PrintHelpMessage    proto

    .data
     SystemTraceControlGuid IID _SystemTraceControlGuid

    .code

_tmain proc uses rsi rdi rbx argc:int_t, argv:ptr LPTSTR

;;++
;;
;; Routine Description:
;;
;;    It is the main function.
;;
;; Arguments:
;;
;;    argc - Number of the arguments passed to the command line.
;;
;;    argv - Array of strings which holds each argument value.
;;
;; Return Value:
;;
;;    Error Code defined in winerror.h : If the function succeeds,
;;    it returns ERROR_SUCCESS(=0).
;;
;;--

    local LoggerCounter:ULONG
    local Status:ULONG
    local targv:ptr LPTSTR
    local utargv:ptr LPTSTR

    ;;
    ;; Action to be taken
    ;;

    local Action:USHORT

    local LoggerName:LPTSTR
    local LogFileName:LPTSTR

    ;;
    ;; We will store the custom logger settings in LoggerInfo.
    ;;

    local LoggerInfo:PEVENT_TRACE_PROPERTIES

    local LoggerHandle:TRACEHANDLE

    ;;
    ;; Target GUID, level and flags for enable/disable
    ;;

    local TargetGuid:GUID
    local TargetGuidProvided:BOOLEAN

    local Enable:ULONG

    local SizeNeeded:ULONG

    ;;
    ;; We will enable Process, Thread, Disk, and Network events
    ;; if the Kernel Logger is requested.
    ;;

    local IsKernelLogger:BOOL

    ;;
    ;; Allocate and initialize EVENT_TRACE_PROPERTIES structure first.
    ;;

    mov Action,ACTION_UNDEFINED
    mov Status,ERROR_SUCCESS
    mov utargv,NULL
    mov LoggerHandle,0
    mov TargetGuidProvided,FALSE
    mov Enable,TRUE
    mov SizeNeeded,sizeof(EVENT_TRACE_PROPERTIES) + 2 * MAXSTR * sizeof(TCHAR)
    mov IsKernelLogger,FALSE

    mov LoggerInfo,malloc(SizeNeeded)
    .if (LoggerInfo == NULL)
        .return(ERROR_OUTOFMEMORY)
    .endif

    RtlZeroMemory(LoggerInfo, SizeNeeded)
    RtlZeroMemory(&TargetGuid, sizeof(TargetGuid))

    mov rbx,LoggerInfo
    assume rbx:ptr EVENT_TRACE_PROPERTIES

    mov [rbx].Wnode.BufferSize,SizeNeeded
    mov [rbx].Wnode.Flags,WNODE_FLAG_TRACED_GUID
    mov [rbx].LoggerNameOffset,EVENT_TRACE_PROPERTIES
    mov [rbx].LogFileNameOffset,[rbx].LoggerNameOffset
    add [rbx].LogFileNameOffset,MAXSTR * TCHAR

    mov eax,[rbx].LoggerNameOffset
    add rax,rbx
    mov LoggerName,rax
    mov eax,[rbx].LogFileNameOffset
    add rax,rbx
    mov LogFileName,rax

    ;;
    ;; If the logger name is not given, we will assume the kernel logger.
    ;;

    _tcscpy_s( LoggerName, MAXSTR, KERNEL_LOGGER_NAME )

ifdef _UNICODE
    mov targv,CommandLineToArgvW( GetCommandLineW(), &argc )
    .if rax == NULL

        free( LoggerInfo )
        .return GetLastError()
    .endif
    mov utargv,rax
else
    mov targv,argv
endif

    ;;
    ;; Parse the command line options to determine actions and parameters.
    ;;

    dec argc
    mov rsi,targv

    .while (argc > 0)

        add rsi,size_t
        mov rbx,[rsi]
        mov eax,[rbx]

        .if ( al == '-' || al == '/')   ;; argument found
            .if ( al == '/' )
                mov byte ptr [rbx],'-'
            .endif

            ;;
            ;; Determine actions.
            ;;

            mov rdi,[rsi+size_t]

            .switch
            .case !_tcsicmp( rbx, "-start" )

                mov Action,ACTION_START

                .endc .if argc <= 1
                mov al,[rdi]
                .endc .if al == '-' || al != '/'

                add rsi,size_t
                dec argc
                _tcscpy_s( LoggerName, MAXSTR, rdi )
                .endc

            .case !_tcsicmp( rbx, "-enable" )

                mov Action,ACTION_ENABLE

                .endc .if argc <= 1
                mov al,[rdi]
                .endc .if al == '-' || al != '/'

                add rsi,size_t
                dec argc

                _tcscpy_s( LoggerName, MAXSTR, rdi )
                .endc

            .case !_tcsicmp( rbx, "-disable" )

                mov Action,ACTION_ENABLE
                mov Enable,FALSE

                .endc .if argc <= 1
                mov al,[rdi]
                .endc .if al == '-' || al != '/'

                add rsi,size_t
                dec argc

                _tcscpy_s( LoggerName, MAXSTR, rdi )
                .endc

            .case !_tcsicmp( rbx, "-stop" )

                mov Action,ACTION_STOP

                .endc .if argc <= 1
                mov al,[rdi]
                .endc .if al == '-' || al != '/'

                add rsi,size_t
                dec argc

                _tcscpy_s( LoggerName, MAXSTR, rdi )
                .endc

            .case !_tcsicmp( rbx, "-update" )

                mov Action,ACTION_UPDATE

                .endc .if argc <= 1
                mov al,[rdi]
                .endc .if al == '-' || al != '/'

                add rsi,size_t
                dec argc

                _tcscpy_s( LoggerName, MAXSTR, rdi )
                .endc

            .case !_tcsicmp( rbx, "-query" )

                mov Action,ACTION_QUERY

                .endc .if argc <= 1
                mov al,[rdi]
                .endc .if al == '-' || al != '/'

                add rsi,size_t
                dec argc

                _tcscpy_s( LoggerName, MAXSTR, rdi )
                .endc

            .case !_tcsicmp( rbx, "-list" )

                mov Action,ACTION_LIST
                .endc

            ;;
            ;; Get other parameters.
            ;; Users can customize logger settings further by adding/changing
            ;; values to LoggerInfo. Refer to EVENT_TRACE_PROPERTIES
            ;; documentation for available options.
            ;; In this sample, we allow changing maximum number of buffers and
            ;; specifying user mode (private) logger.
            ;; We also take trace file name and guid for enable/disable.
            ;;

            .case !_tcsicmp( rbx, "-f" )

                .endc .if argc <= 1

                add rsi,size_t
                dec argc

                _tfullpath( LogFileName, rdi, MAXSTR )
                .endc

            .case !_tcsicmp( rbx, "-guid" )
                int 3
                .endc .if argc <= 1

                ;;
                ;; Before the guid value, we expect "#"
                ;; -guid #xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx
                ;;

                .endc .if TCHAR ptr [rdi] != '#'

                StringToGuid( &[rdi][TCHAR], &TargetGuid )
                mov TargetGuidProvided,TRUE

                add rsi,size_t
                dec argc
                .endc

            .case !_tcsicmp( rbx, "-max" )

                .endc .if argc <= 1

                mov rbx,LoggerInfo
                mov [rbx].MaximumBuffers,_ttoi( rdi )

                add rsi,size_t
                dec argc
                .endc

            .case !_tcsicmp( rbx, "-um" )

                mov rbx,LoggerInfo
                or  [rbx].LogFileMode,EVENT_TRACE_PRIVATE_LOGGER_MODE
                .endc

            .default

                mov al,[rbx+1]
                .if al == 'h' || al == 'H' || al == '?'

                    mov Action,ACTION_HELP
                    PrintHelpMessage()

                    .if utargv != NULL
                        GlobalFree(utargv)
                    .endif

                    free(LoggerInfo)
                    .return(ERROR_SUCCESS)
                .endif
                mov Action,ACTION_UNDEFINED
            .endsw

        .else

            _tprintf( "Invalid option given: %s\n", rbx )

            mov Status,ERROR_INVALID_PARAMETER
            jmp CleanUpAndExit
        .endif
        dec argc
    .endw

    ;;
    ;; Set the kernel logger parameters.
    ;;
    mov rbx,LoggerInfo
    .if !_tcscmp( LoggerName, KERNEL_LOGGER_NAME )

        ;;
        ;; Set enable flags. Users can add options to add additional kernel events
        ;; or remove some of these events.
        ;;

        or  [rbx].EnableFlags,EVENT_TRACE_FLAG_PROCESS
        or  [rbx].EnableFlags,EVENT_TRACE_FLAG_THREAD
        or  [rbx].EnableFlags,EVENT_TRACE_FLAG_DISK_IO
        or  [rbx].EnableFlags,EVENT_TRACE_FLAG_NETWORK_TCPIP
        mov [rbx].Wnode.Guid,SystemTraceControlGuid
        mov IsKernelLogger,TRUE

    .elseif [rbx].LogFileMode & EVENT_TRACE_PRIVATE_LOGGER_MODE

        ;;
        ;; We must provide a control GUID for a private logger.
        ;;

        .if TargetGuidProvided != FALSE
            mov [rbx].Wnode.Guid,TargetGuid
        .else
            mov Status,ERROR_INVALID_PARAMETER
            jmp CleanUpAndExit
        .endif
    .endif

    ;;
    ;; Process the request.
    ;;

    .switch Action
    .case ACTION_START

        ;;
        ;; Use default file name if not given
        ;;

        .if !_tcslen( LogFileName )

            _tcscpy_s( LogFileName, MAXSTR, DEFAULT_LOGFILE_NAME )
        .endif

        mov Status,StartTrace( &LoggerHandle, LoggerName, LoggerInfo )

        .if eax != ERROR_SUCCESS

            _tprintf( "Could not start logger: %s\n"
                      "Operation Status:       %uL\n",
                      LoggerName, Status )

            .endc
        .endif

        _tprintf( "Logger Started...\n" )
        .endc

    .case ACTION_ENABLE

        ;;
        ;; We can allow enabling a GUID during START operation
        ;; (Note no break in case ACTION_START).
        ;; In that case, we do not need to get LoggerHandle separately.
        ;;

        .if Action == ACTION_ENABLE

            ;;
            ;; Get Logger Handle though Query.
            ;;

            mov Status,ControlTrace( 0, LoggerName, LoggerInfo, EVENT_TRACE_CONTROL_QUERY )

            .if eax != ERROR_SUCCESS

                _tprintf( "ERROR: Logger not started\n"
                          "Operation Status:    %uL\n", Status )
                .endc
            .endif
            mov LoggerHandle,[rbx].Wnode.HistoricalContext
        .endif

        ;;
        ;; We do not allow EnableTrace on the Kernel Logger in this sample,
        ;; users can use EnableFlags to enable/disable certain kernel events.
        ;;

        .if IsKernelLogger == FALSE

            _tprintf( "Enabling trace to logger %d\n", LoggerHandle )

            ;;
            ;; In this sample, we use EnableFlag = EnableLebel = 0.
            ;;

            mov Status,EnableTrace( Enable, 0, 0, &TargetGuid, LoggerHandle )

            .if Status != ERROR_SUCCESS

                _tprintf( "ERROR: Failed to enable Guid...\n" )
                _tprintf( "Operation Status:       %uL\n", Status )
                .endc
            .endif
        .endif
        .endc

    .case ACTION_STOP

        mov LoggerHandle,0
        mov Status,ControlTrace( LoggerHandle, LoggerName, LoggerInfo, EVENT_TRACE_CONTROL_STOP )
        .endc

    .case ACTION_LIST

        .new ReturnCount:ULONG
        .new LoggerInfo[MAXIMUM_LOGGERS]:PEVENT_TRACE_PROPERTIES
        .new Storage:PEVENT_TRACE_PROPERTIES
        .new TempStorage:PEVENT_TRACE_PROPERTIES
        .new SizeForOneProperty:ULONG

        mov SizeForOneProperty,sizeof(EVENT_TRACE_PROPERTIES) + 2 * MAXSTR * sizeof(TCHAR)

        ;;
        ;; We need to prepare space to receieve the inforamtion for the loggers.
        ;; Each logger information needs one EVENT_TRACE_PROPERTIES sturucture
        ;; followed by the logger name and the logfile path strings.
        ;;
        mov eax,MAXIMUM_LOGGERS
        mul SizeForOneProperty
        mov SizeNeeded,eax

        mov Storage,malloc( SizeNeeded )
        .if rax == NULL

            mov Status,ERROR_OUTOFMEMORY
            .endc
        .endif

        RtlZeroMemory(Storage, SizeNeeded)

        ;;
        ;; Save the pointer for free() later.
        ;;

        mov TempStorage,Storage

        ;;
        ;; Initialize the LoggerInfo array, before passing it to QueryAllTraces.
        ;;

        .for ( rsi = Storage, edi = 0: edi < MAXIMUM_LOGGERS: edi++ )

            assume rsi:PEVENT_TRACE_PROPERTIES

            mov [rsi].Wnode.BufferSize,SizeForOneProperty
            mov [rsi].LoggerNameOffset,sizeof(EVENT_TRACE_PROPERTIES)

            mov [rsi].LogFileNameOffset,sizeof(EVENT_TRACE_PROPERTIES) + MAXSTR * sizeof(TCHAR)

            mov LoggerInfo[rdi*size_t],rsi

            ;;
            ;; Move Storage to point to the next allocated buffer for the
            ;; logger information.
            ;;
            mov eax,[rsi].Wnode.BufferSize
            add rsi,rax
        .endf

        mov Status,QueryAllTraces( LoggerInfo, MAXIMUM_LOGGERS, &ReturnCount )

        .if eax == ERROR_SUCCESS

            .for ( edi = 0: edi < ReturnCount: edi++ )

                PrintLoggerStatus( LoggerInfo[rdi*size_t], Status )
                _tprintf( "\n" )
            .endf
        .endif

        ;;
        ;; Free the memory allocated for the logger information buffers.
        ;;

        free( TempStorage )
        .endc

    .case ACTION_UPDATE

        ;;
        ;; In this sample, users can only update MaximumBuffers and log file name.
        ;; User can add more options for other parameters as needed.
        ;;

        mov Status,ControlTrace( LoggerHandle, LoggerName, LoggerInfo, EVENT_TRACE_CONTROL_UPDATE )
        .endc

    .case ACTION_QUERY

        mov Status,ControlTrace( LoggerHandle, LoggerName, LoggerInfo, EVENT_TRACE_CONTROL_QUERY )
        .endc

    .case ACTION_HELP

        PrintHelpMessage()
        .endc

    .default

        _tprintf( "Error: no action specified\n" )
        PrintHelpMessage()
        .endc
    .endsw

    movzx eax,Action
    .if eax != ACTION_HELP && eax != ACTION_UNDEFINED && eax != ACTION_LIST

        PrintLoggerStatus( LoggerInfo, Status )
    .endif

CleanUpAndExit:

    .if Status != ERROR_SUCCESS
        SetLastError( Status )
    .endif
    .if utargv != NULL
        GlobalFree( utargv )
    .endif
    free( LoggerInfo )
    mov eax,Status
    ret

_tmain endp



PrintLoggerStatus proc uses rsi rdi rbx LoggerInfo:PEVENT_TRACE_PROPERTIES, Status:ULONG

;;++
;;
;; Routine Description:
;;
;;    Prints out the status of the specified logger.
;;
;; Arguments:
;;
;;    LoggerInfo - The pointer to the resident EVENT_TRACE_PROPERTIES that has
;;        the information about the current logger.
;;
;;    Status - The operation status of the current logger.
;;
;; Return Value:
;;
;;    None.
;;
;;--

    mov rbx,rcx
    xor esi,esi
    xor edi,edi

    .if [rbx].LoggerNameOffset > 0 && [rbx].LoggerNameOffset < [rbx].Wnode.BufferSize

        mov esi,[rbx].LoggerNameOffset
        add rsi,rbx
    .endif

    .if [rbx].LogFileNameOffset > 0 && [rbx].LogFileNameOffset < [rbx].Wnode.BufferSize

        mov edi,[rbx].LogFileNameOffset
        add rdi,rbx
    .endif

    _tprintf( "Operation Status:       %uL\n", Status )
    mov rdx,rsi
    .if rdx == NULL
        lea rdx,@CStr(" ")
    .endif
    _tprintf( "Logger Name:            %s\n", rdx )
    _tprintf( "Logger Id:              %I64x\n", [rbx].Wnode.HistoricalContext )
    _tprintf( "Logger Thread Id:       %d\n", [rbx].LoggerThreadId )

    .return .if Status != ERROR_SUCCESS

    _tprintf( "Buffer Size:            %d Kb", [rbx].BufferSize )

    .if [rbx].LogFileMode & EVENT_TRACE_USE_PAGED_MEMORY
        _tprintf( " using paged memory\n" )
    .else
        _tprintf( "\n" )
    .endif
    _tprintf( "Maximum Buffers:        %d\n", [rbx].MaximumBuffers )
    _tprintf( "Minimum Buffers:        %d\n", [rbx].MinimumBuffers )
    _tprintf( "Number of Buffers:      %d\n", [rbx].NumberOfBuffers )
    _tprintf( "Free Buffers:           %d\n", [rbx].FreeBuffers )
    _tprintf( "Buffers Written:        %d\n", [rbx].BuffersWritten )
    _tprintf( "Events Lost:            %d\n", [rbx].EventsLost )
    _tprintf( "Log Buffers Lost:       %d\n", [rbx].LogBuffersLost )
    _tprintf( "Real Time Buffers Lost: %d\n", [rbx].RealTimeBuffersLost )
    _tprintf( "AgeLimit:               %d\n", [rbx].AgeLimit )

    .if rdi == NULL
        _tprintf( "Buffering Mode:         " )
    .else
        _tprintf( "Log File Mode:          " )
    .endif

    .if [rbx].LogFileMode & EVENT_TRACE_FILE_MODE_APPEND
        _tprintf( "Append  " )
    .endif

    .if [rbx].LogFileMode & EVENT_TRACE_FILE_MODE_CIRCULAR
        _tprintf( "Circular\n" )
    .elseif [rbx].LogFileMode & EVENT_TRACE_FILE_MODE_SEQUENTIAL
        _tprintf( "Sequential\n" )
    .else
        _tprintf( "Sequential\n" )
    .endif

    .if [rbx].LogFileMode & EVENT_TRACE_REAL_TIME_MODE
        _tprintf( "Real Time mode enabled" )
        _tprintf( "\n" )
    .endif

    .if [rbx].MaximumFileSize > 0
        _tprintf( "Maximum File Size:      %d Mb\n", [rbx].MaximumFileSize )
    .endif

    .if [rbx].FlushTimer > 0
        _tprintf( "Buffer Flush Timer:     %d secs\n", [rbx].FlushTimer )
    .endif

    .if [rbx].EnableFlags != 0
        _tprintf( "Enabled tracing:        " )
        mov eax,1
        .if rsi
            _tcscmp( rsi, KERNEL_LOGGER_NAME )
        .endif
        .if eax == 0

            .if [rbx].EnableFlags & EVENT_TRACE_FLAG_PROCESS
                _tprintf( "Process " )
            .endif
            .if [rbx].EnableFlags & EVENT_TRACE_FLAG_THREAD
                _tprintf( "Thread " )
            .endif
            .if [rbx].EnableFlags & EVENT_TRACE_FLAG_DISK_IO
                _tprintf( "Disk " )
            .endif
            .if [rbx].EnableFlags & EVENT_TRACE_FLAG_DISK_FILE_IO
                _tprintf( "File " )
            .endif
            .if [rbx].EnableFlags & EVENT_TRACE_FLAG_MEMORY_PAGE_FAULTS
                _tprintf( "PageFaults " )
            .endif
            .if [rbx].EnableFlags & EVENT_TRACE_FLAG_MEMORY_HARD_FAULTS
                _tprintf( "HardFaults " )
            .endif
            .if [rbx].EnableFlags & EVENT_TRACE_FLAG_IMAGE_LOAD
                _tprintf( "ImageLoad " )
            .endif
            .if [rbx].EnableFlags & EVENT_TRACE_FLAG_NETWORK_TCPIP
                _tprintf( "TcpIp " )
            .endif
            .if [rbx].EnableFlags & EVENT_TRACE_FLAG_REGISTRY
                _tprintf( "Registry " )
            .endif
        .else
            _tprintf( "0x%08x", [rbx].EnableFlags )
        .endif

        _tprintf( "\n" )
    .endif

    .if rdi != NULL
        _tprintf( "Log Filename:           %s\n", rdi )
    .endif
    ret

PrintLoggerStatus endp

    assume rsi:nothing
    assume rbx:nothing

HexToLong proc uses rsi rdi rbx String:ptr TCHAR

;;++
;;
;; Routine Description:
;;
;;    Converts a hex string into a number.
;;
;; Arguments:
;;
;;    String - A hex string in TCHAR.
;;
;; Return Value:
;;
;;    ULONG - The number in the string.
;;
;;--

    xor edi,edi
    mov rsi,rcx
    mov ebx,_tcslen(rcx)
    mov ecx,1

    .fors --ebx: ebx >= 0: ebx--

        movzx eax,TCHAR ptr [rsi+rbx*TCHAR]
        .if ( eax == 'x' || eax == 'X') && TCHAR ptr [rsi+rbx*TCHAR-TCHAR] == '0'

            .break
        .endif

        .if eax >= '0' && eax <= '9'
            sub eax,'0'
        .elseif eax >= 'a' && eax <= 'f'
            sub eax,'a'
            add eax,10
        .elseif eax >= 'A' && eax <= 'F'
            sub eax,'A'
            add eax,10
        .else
            .continue
        .endif
        mul ecx
        or  edi,eax
        shl ecx,4
    .endf
    .return edi

HexToLong endp


StringToGuid proc uses rsi rdi rbx String:ptr TCHAR, Guid:LPGUID

;;++
;;
;; Routine Description:
;;
;;    Converts a string into a GUID.
;;
;; Arguments:
;;
;;    String - A string in TCHAR.
;;
;;    Guid - The pointer to a GUID that will have the converted GUID.
;;
;; Return Value:
;;
;;    None.
;;
;;--

    local Temp[10]:TCHAR

    mov rsi,rcx
    mov rdi,rdx
    assume rdi:ptr GUID

    _tcsncpy_s( &Temp, 10, rcx, 8 )

    mov Temp[8*TCHAR],0
    mov [rdi].Data1,HexToLong( &Temp )

    _tcsncpy_s( &Temp, 10, &[rsi+9*TCHAR], 4 )
    mov Temp[4*TCHAR],0
    mov [rdi].Data2,HexToLong( &Temp )

    _tcsncpy_s( &Temp, 10, &[rsi+14*TCHAR], 4 )
    mov Temp[4*TCHAR],0
    mov [rdi].Data3,HexToLong( &Temp )

    .for ebx = 0: ebx < 2: ebx++
        _tcsncpy_s( &Temp, 10, &[rsi+rbx*(2*TCHAR)+(19*TCHAR)], 2 )
        mov Temp[2*TCHAR],0
        HexToLong( &Temp )
        mov [rdi].Data4[rbx],al
    .endf

    .for ebx = 2: ebx < 8: ebx++
        _tcsncpy_s( &Temp, 10, &[rsi+rbx*(2*TCHAR)+(20*TCHAR)], 2 )
        mov Temp[2*TCHAR],0
        HexToLong( &Temp )
        mov [rdi].Data4[rbx],al
    .endf
    ret

StringToGuid endp


PrintHelpMessage proc

;;++
;;
;; Routine Description:
;;
;;    Prints out a help message.
;;
;; Arguments:
;;
;;    None.
;;
;; Return Value:
;;
;;    None.
;;
;;--

    _tprintf(
        "Usage: tracelog [actions] [options] | [-h | -help | -?]\n"
        "\n    actions:\n"
        "\t-start   [LoggerName] Starts up the [LoggerName] trace session\n"
        "\t-stop    [LoggerName] Stops the [LoggerName] trace session\n"
        "\t-update  [LoggerName] Updates the [LoggerName] trace session\n"
        "\t-enable  [LoggerName] Enables providers for the [LoggerName] session\n"
        "\t-disable [LoggerName] Disables providers for the [LoggerName] session\n"
        "\t-query   [LoggerName] Query status of [LoggerName] trace session\n"
        "\t-list                 List all trace sessions\n"
        "\n    options:\n"
        "\t-um                   Use Process Private tracing\n"
        "\t-max <n>              Sets maximum buffers\n"
        "\t-f <name>             Log to file <name>\n"
        "\t-guid #<guid>         Provider GUID to enable/disable\n"
        "\n"
        "\t-h\n"
        "\t-help\n"
        "\t-?                    Display usage information\n\n"
        )
    ret

PrintHelpMessage endp

    end _tstart
