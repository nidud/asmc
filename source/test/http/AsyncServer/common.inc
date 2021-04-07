ifndef __COMMON__
define __COMMON__

option wstring:off

ifndef _WIN32_WINNT
;; Specifies that the minimum required platform is Windows Vista.
;; Change this to the appropriate value to target other versions of Windows.
define _WIN32_WINNT 0x0600
endif

.pragma warning(disable:4201)   ;; nameless struct/union
.pragma warning(disable:4214)   ;; bit field types other than int

ifdef __CV__
.pragma comment(linker,"/DEFAULTLIB:libcmtd.lib")
.pragma comment(linker,"/DEFAULTLIB:httpapi.lib")
_LIBCMT equ 1
endif

include stdio.inc
include conio.inc
include stdlib.inc
include http.inc
include strsafe.inc

;;
;; Global defines
;;

;; Use the process heap for all memory allocation.

MALLOC macro x
    exitm<HeapAlloc(GetProcessHeap(), 0, (x))>
    endm
FREE macro x
    exitm<HeapFree(GetProcessHeap(), 0, (x))>
    endm

;; Maximum string size (url, server directory)
define MAX_STR_SIZE 256
;; The number of requests for queueing
define OUTSTANDING_REQUESTS 16
;; The number of requests per processor
define REQUESTS_PER_PROCESSOR 4
;; This is the size of the buffer we provide to store the request.
;; Headers, URL, entity-body, etc will all be stored in this buffer.
define REQUEST_BUFFER_SIZE 4096

CALLBACK(HTTP_COMPLETION_FUNCTION, :ptr _HTTP_IO_CONTEXT, :PTP_IO, :ULONG)

;; Structure for handling http server context data

SERVER_CONTEXT          STRUC
wszRootDirectory        WCHAR MAX_STR_SIZE dup(?)   ;; Server directory
sessionId               HTTP_SERVER_SESSION_ID ?    ;; Session Id
urlGroupId              HTTP_URL_GROUP_ID ?         ;; URL group
hRequestQueue           HANDLE ?                    ;; Request queue handle
Io                      PTP_IO ?                    ;; IO object
bHttpInit               BOOL ?                      ;; TRUE, when the HTTP Server API driver was initialized
bStopServer             BOOL ?                      ;; TRUE, when we receive a user command to stop the server
SERVER_CONTEXT          ENDS
PSERVER_CONTEXT         typedef ptr SERVER_CONTEXT


;; Structure for handling I/O context parameters

HTTP_IO_CONTEXT         STRUC
Overlapped              OVERLAPPED <>               ;; Pointer to the completion function
pfCompletionFunction    HTTP_COMPLETION_FUNCTION ?
pServerContext          PSERVER_CONTEXT ?           ;; Structure associated with the url and server directory
HTTP_IO_CONTEXT         ENDS
PHTTP_IO_CONTEXT        typedef ptr HTTP_IO_CONTEXT

;; Structure for handling I/O context parameters

HTTP_IO_REQUEST         STRUC
ioContext               HTTP_IO_CONTEXT <>
pHttpRequest            PHTTP_REQUEST ?
RequestBuffer           UCHAR REQUEST_BUFFER_SIZE dup(?)
HTTP_IO_REQUEST         ENDS
PHTTP_IO_REQUEST        typedef ptr HTTP_IO_REQUEST

;; Structure for handling I/O context parameters

HTTP_IO_RESPONSE        STRUC
ioContext               HTTP_IO_CONTEXT <>
HttpResponse            HTTP_RESPONSE <>            ;; Structure associated with the specific response
HttpDataChunk           HTTP_DATA_CHUNK <>          ;; Structure represents an individual block of data either in memory,
HTTP_IO_RESPONSE        ENDS                        ;; in a file, or in the HTTP Server API response-fragment cache.
PHTTP_IO_RESPONSE       typedef ptr HTTP_IO_RESPONSE

;;
;; Forward Prototypes
;;

SendCompletionCallback proto \
        pIoContext: PHTTP_IO_CONTEXT,
                Io: PTP_IO,
          IoResult: ULONG

ReceiveCompletionCallback proto \
        pIoContext: PHTTP_IO_CONTEXT,
                Io: PTP_IO,
          IoResult: ULONG


ProcessReceiveAndPostResponse proto \
        pIoRequest: PHTTP_IO_REQUEST,
                Io: PTP_IO,
          IoResult: ULONG


GetFilePathName proto \
          BasePath: PCWSTR,
           AbsPath: PCWSTR,
            Buffer: PWCHAR,
        BufferSize: ULONG


AllocateHttpIoRequest proto \
    pServerContext: PSERVER_CONTEXT


AllocateHttpIoResponse proto \
    pServerContext: PSERVER_CONTEXT


CleanupHttpIoResponse proto \
       pIoResponse: PHTTP_IO_RESPONSE


CleanupHttpIoRequest proto \
        pIoRequest: PHTTP_IO_REQUEST

endif
