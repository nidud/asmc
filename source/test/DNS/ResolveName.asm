;;
;; https://github.com/microsoft/Windows-classic-samples
;;
;; Abstract:
;;
;;     The sample demonstrates how to use asynchronous GetAddrInfoEx to
;;     resolve name to IP address.
;;
;;     ResolveName <QueryName>
;;
;;

include windows.inc
include stdio.inc
include Ws2tcpip.inc
include tchar.inc

option dllimport:none

MAX_ADDRESS_STRING_LENGTH   equ 64

;;
;;  Asynchronous query context structure.
;;

QUERY_CONTEXT   STRUC
QueryOverlapped OVERLAPPED <>
QueryResults    PADDRINFOEX ?
CompleteEvent   HANDLE ?
QUERY_CONTEXT   ENDS
PQUERY_CONTEXT  typedef ptr QUERY_CONTEXT

QueryCompleteCallback proto private \
    Error: DWORD,
    Bytes: DWORD,
    Overlapped: LPOVERLAPPED

    .code

_tmain proc \
    Argc: int_t,
    Argv: ptr PWCHAR


    .new Error:SINT = ERROR_SUCCESS
    .new wsaData:WSADATA
    .new IsWSAStartupCalled:BOOL = FALSE
    .new Hints:ADDRINFOEX = {0}
    .new QueryContext:QUERY_CONTEXT = {0}
    .new CancelHandle:HANDLE = NULL
    .new QueryTimeout:DWORD = 5 * 1000 ;; 5 seconds

    ;;
    ;;  Validate the parameters
    ;;

    .if (Argc != 2)

        _tprintf("Usage: ResolveName <QueryName>\n")
        jmp done
    .endif

    ;;
    ;;  All Winsock functions require WSAStartup() to be called first
    ;;

    mov Error,WSAStartup(MAKEWORD(2, 2), &wsaData)
    .if (Error != 0)

        _tprintf("WSAStartup failed with %d\n", Error)
        jmp done
    .endif

    mov IsWSAStartupCalled,TRUE

    mov Hints.ai_family,AF_UNSPEC

    ;;
    ;;  Note that this is a simple sample that waits/cancels a single
    ;;  asynchronous query. The reader may extend this to support
    ;;  multiple asynchronous queries.
    ;;

    mov QueryContext.CompleteEvent,CreateEvent(NULL, TRUE, FALSE, NULL)

    .if (QueryContext.CompleteEvent == NULL)

        mov Error,GetLastError()
        _tprintf("Failed to create completion event: Error %d\n",  Error)
        jmp done
    .endif

    ;;
    ;;  Initiate asynchronous GetAddrInfoExW.
    ;;
    ;;  Note GetAddrInfoEx can also be invoked asynchronously using an event
    ;;  in the overlapped object (Just set hEvent in the Overlapped object
    ;;  and set NULL as completion callback.)
    ;;
    ;;  This sample uses the completion callback method.
    ;;

    mov rcx,Argv
    mov Error,GetAddrInfoEx([rcx+size_t],
                           NULL,
                           NS_DNS,
                           NULL,
                           &Hints,
                           &QueryContext.QueryResults,
                           NULL,
                           &QueryContext.QueryOverlapped,
                           &QueryCompleteCallback,
                           &CancelHandle)

    ;;
    ;;  If GetAddrInfoExW() returns  WSA_IO_PENDING, GetAddrInfoExW will invoke
    ;;  the completion routine. If GetAddrInfoExW returned anything else we must
    ;;  invoke the completion directly.
    ;;

    .if (Error != WSA_IO_PENDING)

        QueryCompleteCallback(Error, 0, &QueryContext.QueryOverlapped)
        jmp done
    .endif

    ;;
    ;;  Wait for query completion for 5 seconds and cancel the query if it has
    ;;  not yet completed.
    ;;

    .if (WaitForSingleObject(QueryContext.CompleteEvent,
                            QueryTimeout)  == WAIT_TIMEOUT )


        ;;
        ;;  Cancel the query: Note that the GetAddrInfoExCancelcancel call does
        ;;  not block, so we must wait for the completion routine to be invoked.
        ;;  If we fail to wait, WSACleanup() could be called while an
        ;;  asynchronous query is still in progress, possibly causing a crash.
        ;;
        mov eax,QueryTimeout
        mov ecx,1000
        xor edx,edx
        div ecx
        _tprintf("The query took longer than %d seconds to complete; "
                 "cancelling the query...\n", rax)

        GetAddrInfoExCancel(&CancelHandle)

        WaitForSingleObject(QueryContext.CompleteEvent,
                            INFINITE)
    .endif

done:

    .if (IsWSAStartupCalled)

        WSACleanup()
    .endif

    .if (QueryContext.CompleteEvent)

        CloseHandle(QueryContext.CompleteEvent)
    .endif

    .return Error

_tmain endp

;;
;; Callback function called by Winsock as part of asynchronous query complete
;;
    assume rsi:ptr QUERY_CONTEXT
    assume rdi:ptr ADDRINFOEX

QueryCompleteCallback proc private uses rsi rdi \
    Error: DWORD,
    Bytes: DWORD,
    Overlapped: LPOVERLAPPED

    .new QueryContext:PQUERY_CONTEXT = NULL
    .new QueryResults:PADDRINFOEX = NULL
    .new AddrString[MAX_ADDRESS_STRING_LENGTH]:TCHAR
    .new AddressStringLength:DWORD

    mov QueryContext,CONTAINING_RECORD(Overlapped, QUERY_CONTEXT, QueryOverlapped)
    mov rsi,rax

    .if (Error != ERROR_SUCCESS)

        _tprintf("ResolveName failed with %d\n", Error)
        jmp done
    .endif

    _tprintf("ResolveName succeeded. Query Results:\n")

    mov QueryResults,[rsi].QueryResults
    mov rdi,rax

    .while (QueryResults)

        mov AddressStringLength,MAX_ADDRESS_STRING_LENGTH

        WSAAddressToString([rdi].ai_addr,
                           dword ptr [rdi].ai_addrlen,
                           NULL,
                           &AddrString,
                           &AddressStringLength)

        _tprintf("Ip Address: %s\n", &AddrString)
        mov QueryResults,[rdi].ai_next
        mov rdi,rax
    .endw

done:

    .if ([rsi].QueryResults)

        FreeAddrInfoEx([rsi].QueryResults)
    .endif

    ;;
    ;;  Notify caller that the query completed
    ;;

    SetEvent([rsi].CompleteEvent)
    ret

QueryCompleteCallback endp

    end _tstart
