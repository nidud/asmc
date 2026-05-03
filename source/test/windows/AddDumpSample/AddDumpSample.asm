include stdio.inc

include winbase.inc
include werapi.inc
include strsafe.inc

    .code

wmain proc

  local hr:HRESULT
  local ReportHandle:HREPORT
  local ReportInformation:WER_REPORT_INFORMATION
  local SubmitResult:WER_SUBMIT_RESULT
  local CurrentProcess:HANDLE

    mov hr,E_FAIL
    mov ReportHandle,0
    memset(&ReportInformation, 0, WER_REPORT_INFORMATION)

    wprintf("WerReportAddDump API Sample\n")
    wprintf("---------------------------\n")

    ;;
    ;; Report creation
    ;;

    ;;
    ;; First, populate the WER_REPORT_INFORMATION structure.
    ;;
    mov ReportInformation.dwSize,sizeof(WER_REPORT_INFORMATION)

    ;;
    ;; To report on the current process, set the hProcess field to NULL.
    ;;
    mov ReportInformation.hProcess,NULL

    ;;
    ;; Set the Consent Key, i.e. the name used to look up consent settings
    ;;

    mov hr,StringCchCopy(&ReportInformation.wzConsentKey,
                        ARRAYSIZE(ReportInformation.wzConsentKey), "Sample Consent Key")

    .repeat

        .if (FAILED(hr))
            wprintf("Failed to set the consent key, error: 0x%08X\n", hr)
            .break
        .endif

        ;;
        ;; Set the name of the application we are reporting on.
        ;;
        mov hr,StringCchCopy(&ReportInformation.wzApplicationName,
                        ARRAYSIZE(ReportInformation.wzApplicationName), "Add Dump Sample")

        .if (FAILED(hr))
            wprintf("Failed to set the application name, error: 0x%08X\n", hr)
            .break
        .endif

        ;;
        ;; Set the application path.
        ;;
        mov hr,StringCchCopy(&ReportInformation.wzApplicationPath,
                        ARRAYSIZE(ReportInformation.wzApplicationPath), "Sample Application Path")

        .if (FAILED(hr))
            wprintf("Failed to set the application path, error: 0x%08X\n", hr)
            .break
        .endif

        ;;
        ;; Set a description of the problem.
        ;;
        mov hr,StringCchCopy(&ReportInformation.wzDescription,
                        ARRAYSIZE(ReportInformation.wzDescription), "Sample Problem Description")

        .if (FAILED(hr))
            wprintf("Failed to set the description, error: 0x%08X\n", hr)
            .break
        .endif

        ;;
        ;; Set a friendly name for the event - this is the display name.
        ;;
        mov hr,StringCchCopy(&ReportInformation.wzFriendlyEventName,
                        ARRAYSIZE(ReportInformation.wzFriendlyEventName), "Sample Problem Friendly Name")

        .if (FAILED(hr))
            wprintf("Failed to set the friendly event name, error: 0x%08X\n", hr)
            .break
        .endif

        ;;
        ;; Now actually call into WER to create the report with the above structure.
        ;; We get back a handle to the report.
        ;;
        mov hr,WerReportCreate("SampleGenericReport",
                          WerReportCritical,
                          &ReportInformation,
                          &ReportHandle)

        .if (FAILED(hr))
            wprintf("WerReportCreate failed, error: 0x%08X\n", hr)
            .break
        .endif

        wprintf("Created the report.\n")

        ;;
        ;; Now set the report parameters (3 parameters in this case).
        ;;
        ;; These parameters as used as bucketing parameters on the WER server.
        ;;
        mov hr,WerReportSetParameter(ReportHandle, 0, "Param1", "Value1")

        .if (FAILED(hr))
            wprintf("Set parameter failed for parameter 0, error: 0x%08X\n", hr)
            .break
        .endif

        mov hr,WerReportSetParameter(ReportHandle, 1, "Param2", "Value2")

        .if (FAILED(hr))
            wprintf ("Set parameter failed for parameter 1, error: 0x%08X\n", hr)
            .break
        .endif

        mov hr,WerReportSetParameter(ReportHandle, 2, "Param3", "Value3")

        .if (FAILED(hr))
            wprintf("Set parameter failed for parameter 3, error: 0x%08X\n", hr)
            .break
        .endif

        ;;
        ;; Request to add a dump to the report. The dump is collected during the call
        ;; to WerReportSubmit below.
        ;;
        ;; For complete description of all parameters, see the MSDN documentation for this API.
        ;;

        mov CurrentProcess,GetCurrentProcess()
        mov hr,WerReportAddDump(ReportHandle,
                           CurrentProcess,
                           GetCurrentThread(),
                           WerDumpTypeMiniDump,
                           NULL,
                           NULL,
                           0)

        .if (FAILED(hr))
            wprintf("WerReportAddDump failed, error: 0x%08X\n", hr)
            .break
        .endif

        wprintf("Added a dump of the current process to the report.\n")

        ;;
        ;; Submit the report.
        ;;
        ;; After the application calls this API, WER collects the specified data.
        ;;

        mov hr,WerReportSubmit(ReportHandle, WerConsentNotAsked, 0, &SubmitResult)

        .if (FAILED(hr))
            wprintf("WerReportSubmit failed, error: 0x%08X\n", hr)
            .break
        .endif

        wprintf("Submission result was %u (WER_SUBMIT_RESULT enum).\n", SubmitResult)

        mov hr,S_OK

    .until 1

    .if (ReportHandle)
        ;;
        ;; Close the handle to the report. Call this API after report has been
        ;; submitted, or the handle is no longer needed.
        ;;
        mov hr,WerReportCloseHandle(ReportHandle)

        .if (FAILED(hr))
            wprintf("WerReportCloseHandle failed, error: 0x%08X\n", hr)
        .endif
    .endif

    .if (FAILED(hr))
        ;;
        ;; Return -1 to indicate that an error occured
        ;;
        mov eax,-1
    .else
        xor eax,eax
    .endif
    ret

wmain endp

    end

