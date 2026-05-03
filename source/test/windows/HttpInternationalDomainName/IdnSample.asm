;;
;; Windows-classic-samples/Samples/HttpInternationalDomainName
;;
;; This sample demonstrates how to use HttpPrepareUrl to get a new URL so that
;; it is safe and valid to use in other HTTPAPIs.
;;
;; IdnSample <inputurl>
;;
;; where:
;;
;; inputurl      The input URL to prepare.
;;

WINVER       equ 0x0603 ; Windows 8.1
_WIN32_WINNT equ 0x0603

include windows.inc
include stdio.inc
include stdlib.inc
include http.inc
include tchar.inc

.code

wmain proc Argc:int_t, Argv:ptr PWCHAR

    .new Error:DWORD = ERROR_SUCCESS
    .new PreparedUrl:PWSTR = NULL
    .new Version:HTTPAPI_VERSION = HTTPAPI_VERSION_2
    .new ApiInitialized:BOOL = FALSE

    .repeat

        .if (Argc != 2)

            wprintf(L"Usage: IdnSample <url>\n")
            .break
        .endif

        mov rax,Argv
        mov Argv,[rax+size_t]

        ;;
        ;; Initialize HTTPAPI to use server APIs.
        ;;

        mov Error,HttpInitialize(Version, HTTP_INITIALIZE_SERVER, NULL)

        .break .if (Error != ERROR_SUCCESS)

        mov ApiInitialized,TRUE

        ;;
        ;; Prepare the input url.
        ;;

        mov Error,HttpPrepareUrl(NULL, 0, Argv, &PreparedUrl)

        .break .if (Error != ERROR_SUCCESS)

        wprintf(L"%s prepared is: %s\n", Argv, PreparedUrl)
    .until 1

    .if (PreparedUrl != NULL)
        HeapFree(GetProcessHeap(), 0, PreparedUrl)
        mov PreparedUrl,NULL
    .endif
    .if (ApiInitialized)
        HttpTerminate(HTTP_INITIALIZE_SERVER, NULL)
        mov ApiInitialized,FALSE
    .endif
    .if (Error != ERROR_SUCCESS)
        wprintf(L"Error code = %#lx.\n", Error)
    .endif
    .return Error

wmain endp

    end _tstart
