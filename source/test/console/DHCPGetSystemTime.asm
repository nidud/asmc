;;
;; https://github.com/microsoft/Windows-classic-samples
;;

include windows.inc
include stdio.inc
include dhcpsapi.inc
include tchar.inc

    .code

wmain proc

  .new dwError:DWORD        = ERROR_SUCCESS ;; Variable to hold returned error code
  .new dwTime:DWORD         = 0             ;; Variable to hold system time of the server
  .new dwAllowedDelay:DWORD = 0             ;; Variable to hold the max allowed delta in time.
  .new pwszServer:LPWSTR    = NULL          ;; Server IP Address

  .new dwError:DWORD = DhcpV4FailoverGetSystemTime(
        pwszServer,     ;; Server IP Address, a value of NULL reflects the current
                        ;; server (where the program is executed)
        &dwTime,        ;; System time of the server
        &dwAllowedDelay ;; Max time difference allowed
        )

    .if ( dwError != ERROR_SUCCESS )

        wprintf("DhcpV4FailoverGetSystemTime failed with Error = %d\n", dwError)
    .endif
    .return 0

wmain endp

    end _tstart
