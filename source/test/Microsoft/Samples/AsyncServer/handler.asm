
include common.inc

;;
;; Global variables
;;
.data

g_usOKCode USHORT 200
g_szOKReason equ <"OK">

g_usFileNotFoundCode USHORT 404
g_szFileNotFoundReason equ <"Not Found">
g_szFileNotFoundMessage equ <"File not found">
g_szFileNotAccessibleMessage equ <"File could not be opened">
g_szBadPathMessage equ <"Bad path">

g_usBadRequestReasonCode USHORT 400
g_szBadRequestReason equ <"Bad Request">
g_szBadRequestMessage equ <"Bad request">

g_usNotImplementedCode USHORT 501
g_szNotImplementedReason equ <"Not Implemented">
g_szNotImplementedMessage equ <"Server only supports GET">

g_usEntityTooLargeCode USHORT 413
g_szEntityTooLargeReason equ <"Request Entity Too Large">
g_szEntityTooLargeMessage equ <"Large buffer support is not implemented">

;;
;; Routine Description:
;;
;;     Retrieves the next available HTTP request from the specified request
;;     queue asynchronously. If HttpReceiveHttpRequest call failed inline checks
;;     the reason and cancels the Io if necessary. If our attempt to receive
;;     an HTTP Request failed with ERROR_MORE_DATA the client is misbehaving
;;     and we should return it error 400 back. Pretend that the call
;;     failed asynchronously.
;;
;; Arguments:
;;
;;     pServerContext - context for the server
;;
;;     Io - Structure that defines the I/O object.
;;
;; Return Value:
;;
;;     N/A
;;
    .code

    assume rbx:PSERVER_CONTEXT
    assume rdi:PHTTP_IO_REQUEST

PostNewReceive proc pServerContext:PSERVER_CONTEXT, Io:PTP_IO

    local pIoRequest:PHTTP_IO_REQUEST
    local Result:ULONG

    mov pIoRequest,AllocateHttpIoRequest(pServerContext)

    .return .if (pIoRequest == NULL)

    StartThreadpoolIo(Io)

    mov rbx,pServerContext
    mov rdi,pIoRequest

    mov Result,HttpReceiveHttpRequest(
        [rbx].hRequestQueue,
        HTTP_NULL_ID,
        HTTP_RECEIVE_REQUEST_FLAG_COPY_BODY,
        [rdi].pHttpRequest,
        sizeof(HTTP_IO_REQUEST.RequestBuffer),
        NULL,
        &[rdi].ioContext.Overlapped
        )

    .if (Result != ERROR_IO_PENDING && \
        Result != NO_ERROR)

        CancelThreadpoolIo(Io)

        fprintf(stderr, "HttpReceiveHttpRequest failed, error 0x%lx\n", Result)

        .if (Result == ERROR_MORE_DATA)

            ProcessReceiveAndPostResponse(pIoRequest, Io, ERROR_MORE_DATA)
        .endif

         CleanupHttpIoRequest(pIoRequest)
    .endif
    ret

PostNewReceive endp

;;
;; Routine Description:
;;
;;     Completion routine for the asynchronous HttpSendHttpResponse
;;     call. This sample doesn't process the results of its send operations.
;;
;; Arguments:
;;
;;     IoContext - The HTTP_IO_CONTEXT tracking this operation.
;;
;;     Io - Ignored
;;
;;     IoResult - Ignored
;;
;; Return Value:
;;
;;     N/A
;;

SendCompletionCallback proc \
        pIoContext: PHTTP_IO_CONTEXT,
        Io: PTP_IO,
        IoResult: ULONG

  local pIoResponse:PHTTP_IO_RESPONSE

    mov pIoResponse,CONTAINING_RECORD(pIoContext,
                                    HTTP_IO_RESPONSE,
                                    ioContext)

    CleanupHttpIoResponse(pIoResponse)
    ret

SendCompletionCallback endp

;;
;; Routine Description:
;;
;;     Creates a response for a successful get, the content is served
;;     from a file.
;;
;; Arguments:
;;
;;     pServerContext - Pointer to the http server context structure.
;;
;;     hFile - Handle to the specified file.
;;
;; Return Value:
;;
;;     Return a pointer to the HTTP_IO_RESPONSE structure.
;;

    assume rbx:PHTTP_IO_RESPONSE
    assume rdi:PHTTP_DATA_CHUNK

CreateFileResponse proc uses rdi rbx \
        pServerContext: PSERVER_CONTEXT,
        hFile: HANDLE

  local pIoResponse:PHTTP_IO_RESPONSE
  local pChunk:PHTTP_DATA_CHUNK

    mov pIoResponse,AllocateHttpIoResponse(pServerContext)

    .return .if (pIoResponse == NULL)

    mov rbx,rax
    mov [rbx].HttpResponse.StatusCode,g_usOKCode
    mov [rbx].HttpResponse.pReason,&@CStr(g_szOKReason)
    mov [rbx].HttpResponse.ReasonLength,strlen(g_szOKReason)

    mov pChunk,&[rbx].HttpResponse.pEntityChunks[0]
    mov rdi,rax
    mov [rdi].DataChunkType,HttpDataChunkFromFileHandle
    mov [rdi].FromFileHandle.ByteRange.Length.QuadPart,HTTP_BYTE_RANGE_TO_EOF
    mov [rdi].FromFileHandle.ByteRange.StartingOffset.QuadPart,0
    mov [rdi].FromFileHandle.FileHandle,hFile

    .return pIoResponse

CreateFileResponse endp

;;
;; Routine Description:
;;
;;     Creates an http response if the requested file was not found.
;;
;; Arguments:
;;
;;     pServerContext - Pointer to the http server context structure.
;;
;;     code - The error code to use in the response
;;
;;     pReason - The reason string to send back to the client
;;
;;     pMessage - The more verbose message to send back to the client
;;
;; Return Value:
;;
;;     Return a pointer to the HTTP_IO_RESPONSE structure
;;

CreateMessageResponse proc uses rdi rbx \
        pServerContext: PSERVER_CONTEXT,
        code: USHORT,
        pReason: PCHAR,
        pMessage: PCHAR


    local pIoResponse:PHTTP_IO_RESPONSE
    local pChunk:PHTTP_DATA_CHUNK

    mov pIoResponse,AllocateHttpIoResponse(pServerContext)

    .return .if (pIoResponse == NULL)

    mov rbx,rax

    ;; Can not find the requested file
    mov [rbx].HttpResponse.StatusCode,code
    mov [rbx].HttpResponse.pReason,pReason
    mov [rbx].HttpResponse.ReasonLength,strlen(pReason)

    mov pChunk,&[rbx].HttpResponse.pEntityChunks[0]
    mov rdi,rax

    mov [rdi].DataChunkType,HttpDataChunkFromMemory
    mov [rdi].FromMemory.pBuffer,pMessage
    mov [rdi].FromMemory.BufferLength,strlen(pMessage)

    .return pIoResponse

CreateMessageResponse endp

;;
;; Routine Description:
;;
;;     This routine processes the received request, builds an HTTP response,
;;     and sends it using HttpSendHttpResponse.
;;
;; Arguments:
;;
;;     IoContext - The HTTP_IO_CONTEXT tracking this operation.
;;
;;     Io - Structure that defines the I/O object.
;;
;;     IoResult - The result of the I/O operation. If the I/O is successful,
;;         this parameter is NO_ERROR. Otherwise, this parameter is one of
;;         the system error codes.
;;
;; Return Value:
;;
;;     N/A
;;

    assume rbx:PHTTP_IO_REQUEST
    assume rdi:PSERVER_CONTEXT

ProcessReceiveAndPostResponse proc uses rsi rdi rbx \
        pIoRequest: PHTTP_IO_REQUEST,
        Io: PTP_IO,
        IoResult: ULONG


    local Result:ULONG
    local hFile:HANDLE
    local CachePolicy:HTTP_CACHE_POLICY
    local pIoResponse:PHTTP_IO_RESPONSE
    local pServerContext:PSERVER_CONTEXT

    mov rbx,rcx

    mov pServerContext,[rbx].ioContext.pServerContext
    mov hFile,INVALID_HANDLE_VALUE
    mov rdi,pServerContext
    mov rsi,[rbx].pHttpRequest

    .switch(IoResult)
        .case NO_ERROR

            .new wszFilePath[MAX_STR_SIZE]:WCHAR
            .new bValidUrl:BOOL

            .if ([rsi].HTTP_REQUEST.Verb != HttpVerbGET)

                mov pIoResponse,CreateMessageResponse(
                                pServerContext,
                                g_usNotImplementedCode,
                                g_szNotImplementedReason,
                                g_szNotImplementedMessage)
                .endc
            .endif

            mov bValidUrl,GetFilePathName(
                &[rdi].wszRootDirectory,
                [rsi].HTTP_REQUEST.CookedUrl.pAbsPath,
                &wszFilePath,
                MAX_STR_SIZE)

            .if (bValidUrl == FALSE)

                mov pIoResponse,CreateMessageResponse(
                                pServerContext,
                                g_usFileNotFoundCode,
                                g_szFileNotFoundReason,
                                g_szBadPathMessage)
                .endc
            .endif

            mov hFile,CreateFileW(
                &wszFilePath,
                GENERIC_READ,
                FILE_SHARE_READ,
                NULL,
                OPEN_EXISTING,
                FILE_ATTRIBUTE_NORMAL,
                NULL)

            .if (hFile == INVALID_HANDLE_VALUE)

                GetLastError()
                .if (eax == ERROR_PATH_NOT_FOUND || \
                     eax == ERROR_FILE_NOT_FOUND)

                    mov pIoResponse,CreateMessageResponse(
                                    pServerContext,
                                    g_usFileNotFoundCode,
                                    g_szFileNotFoundReason,
                                    g_szFileNotFoundMessage)
                    .endc
                .endif

                mov pIoResponse,CreateMessageResponse(
                                pServerContext,
                                g_usFileNotFoundCode,
                                g_szFileNotFoundReason,
                                g_szFileNotAccessibleMessage)
                .endc
            .endif

            mov pIoResponse,CreateFileResponse(pServerContext, hFile)

            mov CachePolicy.Policy,HttpCachePolicyUserInvalidates
            mov CachePolicy.SecondsToLive,0
            .endc

        .case ERROR_MORE_DATA

            mov pIoResponse,CreateMessageResponse(
                            pServerContext,
                            g_usEntityTooLargeCode,
                            g_szEntityTooLargeReason,
                            g_szEntityTooLargeMessage)
            .endc

        .default
            ;; If the HttpReceiveHttpRequest call failed asynchronously
            ;; with a different error than ERROR_MORE_DATA, the error is fatal
            ;; There's nothing this function can do
            .return
    .endsw

    .if (pIoResponse == NULL)

        .return
    .endif

    StartThreadpoolIo(Io)

    xor ecx,ecx
    .if (hFile != INVALID_HANDLE_VALUE)
        lea rcx,CachePolicy
    .endif
    mov rdx,pIoResponse
    mov Result,HttpSendHttpResponse(
        [rdi].hRequestQueue,
        [rsi].HTTP_REQUEST.RequestId,
        0,
        &[rdx].HTTP_IO_RESPONSE.HttpResponse,
        rcx,
        NULL,
        NULL,
        0,
        &[rbx].ioContext.Overlapped,
        NULL
        )

    .if (Result != NO_ERROR && \
         Result != ERROR_IO_PENDING)

        CancelThreadpoolIo(Io)

        fprintf(stderr, "HttpSendHttpResponse failed, error 0x%lx\n", Result)

        CleanupHttpIoResponse(pIoResponse)
    .endif
    ret

ProcessReceiveAndPostResponse endp

;;
;; Routine Description:
;;
;;     Completion routine for the asynchronous HttpReceiveHttpRequest
;;     call. Check if the user asked us to stop the server. If not, send a
;;     response and post a new receive to HTTPAPI.
;;
;; Arguments:
;;
;;     IoContext - The HTTP_IO_CONTEXT tracking this operation.
;;
;;     Io - Structure that defines the I/O object.
;;
;;     IoResult - The result of the I/O operation. If the I/O is successful,
;;         this parameter is NO_ERROR. Otherwise, this parameter is one of
;;         the system error codes.
;;
;; Return Value:
;;
;;     N/A
;;

ReceiveCompletionCallback proc \
        pIoContext: PHTTP_IO_CONTEXT,
        Io: PTP_IO,
        IoResult: ULONG


    local pIoRequest:PHTTP_IO_REQUEST
    local pServerContext:PSERVER_CONTEXT

    mov pIoRequest,CONTAINING_RECORD(pIoContext,
                                   HTTP_IO_REQUEST,
                                   ioContext)

    mov pServerContext,[rax].HTTP_IO_REQUEST.ioContext.pServerContext

    .if ([rax].SERVER_CONTEXT.bStopServer == FALSE)

        ProcessReceiveAndPostResponse(pIoRequest, Io, IoResult)

        PostNewReceive(pServerContext, Io)
    .endif

    CleanupHttpIoRequest(pIoRequest)
    ret

ReceiveCompletionCallback endp

    end

