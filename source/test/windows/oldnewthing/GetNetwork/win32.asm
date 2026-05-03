; WIN32.ASM--
;
; https://devblogs.microsoft.com/oldnewthing/20221013-00/?p=107285
;

include stdio.inc
include iphlpapi.inc
include tchar.inc

.code

_tmain proc

    .new connectivityHint:NL_NETWORK_CONNECTIVITY_HINT = {0}
    .if ( GetNetworkConnectivityHint(&connectivityHint) )

        ; handle the error somehow

        _tperror("GetNetworkConnectivityHint()")
       .return(1)
    .endif

     _tprintf(
        "NL_NETWORK_CONNECTIVITY_HINT:\n"
        " ConnectivityLevel:     %d\n"
        " ConnectivityCost:      %d\n"
        " ApproachingDataLimit:  %d\n"
        " OverDataLimit:         %d\n"
        " Roaming:               %d\n",
        connectivityHint.ConnectivityLevel,
        connectivityHint.ConnectivityCost,
        connectivityHint.ApproachingDataLimit,
        connectivityHint.OverDataLimit,
        connectivityHint.Roaming)

    .return(0)
    endp

    end _tstart
