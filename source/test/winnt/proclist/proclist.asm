ifdef _UNICODE
tmain equ <wmain>
else
tmain equ <main>
endif

;; this program only needs the "bare essential" windows header files
WIN32_LEAN_AND_MEAN equ 1
include windows.inc
include winperf.inc
include malloc.inc
include stdio.inc
include tchar.inc
include pdh.inc
include pdhmsg.inc

.code

tmain proc

  local pdhStatus:PDH_STATUS
  local szCounterListBuffer:LPTSTR
  local dwCounterListSize:DWORD
  local szInstanceListBuffer:LPTSTR
  local dwInstanceListSize:DWORD
  local szThisInstance:LPTSTR

    xor eax,eax
    mov pdhStatus,ERROR_SUCCESS
    mov szCounterListBuffer,rax
    mov dwCounterListSize,eax
    mov szInstanceListBuffer,rax
    mov dwInstanceListSize,eax
    mov szThisInstance,rax

    ;; call the function to determine the required buffer size for the data
    PdhEnumObjectItems(
        NULL,                   ;; reserved
        NULL,                   ;; local machine
        "Process",              ;; object to enumerate
        szCounterListBuffer,    ;; pass in NULL buffers
        &dwCounterListSize,     ;; an 0 length to get
        szInstanceListBuffer,   ;; required size
        &dwInstanceListSize,    ;; of the buffers in chars
        PERF_DETAIL_WIZARD,     ;; counter detail level
        0)

    mov pdhStatus,eax
    .if (pdhStatus == ERROR_SUCCESS || pdhStatus == PDH_MORE_DATA)

        ;; allocate the buffers and try the call again
        ;; PdhEnum functions will return ERROR_SUCCESS in WIN2K, but PDH_MORE_DATA in XP and later.
        ;; In either case, dwCounterListSize and dwInstanceListSize should contain correct buffer size needed.
        ;;
        mov eax,sizeof(TCHAR)
        mul dwCounterListSize
        mov szCounterListBuffer,malloc (rax)

        mov eax,sizeof(TCHAR)
        mul dwInstanceListSize
        mov szInstanceListBuffer,malloc (rax)

        .if ((szCounterListBuffer != NULL) && (szInstanceListBuffer != NULL))

            PdhEnumObjectItems (
                NULL,                   ;; reserved
                NULL,                   ;; local machine
                "Process",              ;; object to enumerate
                szCounterListBuffer,    ;; pass in NULL buffers
                &dwCounterListSize,     ;; an 0 length to get
                szInstanceListBuffer,   ;; required size
                &dwInstanceListSize,    ;; of the buffers in chars
                PERF_DETAIL_WIZARD,     ;; counter detail level
                0)
            mov pdhStatus,eax

            .if (pdhStatus == ERROR_SUCCESS)

                _tprintf ("\nRunning Processes:")
                ;; walk the return instance list
                .for (rbx = szInstanceListBuffer: byte ptr [rbx] != 0: rbx += lstrlen(rbx), rbx += 1)
                    _tprintf ("\n  %s", rbx)
                .endf

            .endif

        .else

            _tprintf ("\nPROCLIST: unable to allocate buffers")
        .endif

        .if (szCounterListBuffer != NULL)
            free (szCounterListBuffer)
        .endif

        .if (szInstanceListBuffer != NULL)
            free (szInstanceListBuffer)
        .endif

    .else
        _tprintf ("\nPROCLIST: unable to determine the necessary buffer size required: %X\n", eax)
    .endif
    xor eax,eax
    ret

tmain endp

    end
