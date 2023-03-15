
;;
;; Abstract:
;;
;;     This sample demonstrates how to create a simple HTTP server using the
;;     HTTP API, v2. It does this using the system thread pool.
;;
;;     Threads within the thread pool receives I/O completions from the
;;     specified HTTPAPI request queue. They process these by calling the
;;     callback function according to the I/O context. As an example, we
;;     send back an HTTP response to the specified HTTP request. If the request
;;     was valid, the response will include the content of a file as the entity
;;     body.
;;
;;     Once compiled, to use this sample you would:
;;
;;     httpasyncserverapp <Url> <ServerDirectory>
;;
;;     where:
;;
;;     <Url>             is the Url base this sample will listen for.
;;     <ServerDirectory> is the local directory to map incoming requested Url
;;                       to locally.
;;

include common.inc

    option wstring:off

    .data

g_HttpApiVersion HTTPAPI_VERSION HTTPAPI_VERSION_2

;;
;; Routine Description:
;;
;;     Allocates an HTTP_IO_REQUEST block, initializes some members
;;     of this structure and increments the I/O counter.
;;
;; Arguments:
;;
;;     pServerContext - Pointer to the http server context structure.
;;
;; Return Value:
;;
;;     Returns a pointer to the newly initialized HTTP_IO_REQUEST.
;;     NULL upon failure.
;;
.code

    assume rbx:PHTTP_IO_REQUEST

AllocateHttpIoRequest proc uses rbx pServerContext:PSERVER_CONTEXT


    local pIoRequest:PHTTP_IO_REQUEST

    mov pIoRequest,MALLOC(sizeof(HTTP_IO_REQUEST))
    mov rbx,rax

    .return .if (pIoRequest == NULL)

    ZeroMemory(pIoRequest, sizeof(HTTP_IO_REQUEST))

    mov [rbx].ioContext.pServerContext,pServerContext
    mov [rbx].ioContext.pfCompletionFunction,&ReceiveCompletionCallback
    mov [rbx].pHttpRequest,&[rbx].RequestBuffer

    .return pIoRequest

AllocateHttpIoRequest endp

;;
;; Routine Description:
;;
;;     Allocates an HTTP_IO_RESPONSE block, setups a couple HTTP_RESPONSE members
;;     for the response function, gives them 1 EntityChunk, which has a default
;;     buffer if needed and increments the I/O counter.
;;
;; Arguments:
;;
;;     pServerContext - Pointer to the http server context structure.
;;
;; Return Value:
;;
;;     Returns a pointer to the newly initialized HTTP_IO_RESPONSE.
;;     NULL upon failure.
;;

    assume rbx:PHTTP_IO_RESPONSE
    assume rdi:PHTTP_KNOWN_HEADER

AllocateHttpIoResponse proc uses rdi rbx pServerContext:PSERVER_CONTEXT


    local pIoResponse:PHTTP_IO_RESPONSE
    local pContentTypeHeader:PHTTP_KNOWN_HEADER

    mov pIoResponse,MALLOC(sizeof(HTTP_IO_RESPONSE))

    .return .if (pIoResponse == NULL)

    mov rbx,rax

    ZeroMemory(pIoResponse, sizeof(HTTP_IO_RESPONSE))

    mov [rbx].ioContext.pServerContext,pServerContext
    mov [rbx].ioContext.pfCompletionFunction,&SendCompletionCallback

    mov [rbx].HttpResponse.EntityChunkCount,1
    mov [rbx].HttpResponse.pEntityChunks,&[rbx].HttpDataChunk
    mov [rbx].HttpResponse.Headers.KnownHeaders\
             .pRawValue[HttpHeaderContentType*HTTP_KNOWN_HEADER],&@CStr("text/html")
    mov [rbx].HttpResponse.Headers.KnownHeaders\
            [HttpHeaderContentType*HTTP_KNOWN_HEADER].pRawValue,lengthof(@CStr(0))-1

    .return pIoResponse

AllocateHttpIoResponse endp

;;
;; Routine Description:
;;
;;     Cleans the structure associated with the specific response.
;;     Releases this structure, and decrements the I/O counter.
;;
;; Arguments:
;;
;;     pIoResponse - Pointer to the structure associated with the specific
;;                   response.
;;
;; Return Value:
;;
;;     N/A
;;

    assume rdi:PHTTP_DATA_CHUNK

CleanupHttpIoResponse proc uses rsi rdi rbx pIoResponse:PHTTP_IO_RESPONSE


    local i:DWORD

    mov rbx,pIoResponse

    .for (esi = 0: si < [rbx].HttpResponse.EntityChunkCount: ++esi)

        .new pDataChunk:PHTTP_DATA_CHUNK

        mov pDataChunk,&[rbx].HttpResponse.pEntityChunks[rsi*size_t]
        mov rdi,rax

        .if ([rdi].DataChunkType == HttpDataChunkFromFileHandle)

            .if ([rdi].FromFileHandle.FileHandle != NULL)

                CloseHandle([rdi].FromFileHandle.FileHandle)
                mov [rdi].FromFileHandle.FileHandle,NULL
            .endif
        .endif
    .endf

    FREE(pIoResponse)
    ret

CleanupHttpIoResponse endp

;;
;; Routine Description:
;;
;;     Cleans the structure associated with the specific request.
;;     Releases this structure and decrements the I/O counter
;;
;; Arguments:
;;
;;     pIoRequest - Pointer to the structure associated with the specific request.
;;
;; Return Value:
;;
;;     N/A
;;

CleanupHttpIoRequest proc pIoRequest:PHTTP_IO_REQUEST


    FREE(pIoRequest)
    ret

CleanupHttpIoRequest endp

;;
;; Routine Description:
;;
;;     Computes the full path filename given the requested Url.
;;     Takes the base path and add the portion of the client request
;;     Url that comes after the base Url.
;;
;; Arguments:
;;
;;     pServerContext - The server we are associated with.
;;
;;     RelativePath - the client request Url that comes after the base Url.
;;
;;     Buffer - Output buffer where the full path filename will be written.
;;
;;     BufferSize - Size of the Buffer in bytes.
;;
;; Return Value:
;;
;;     TRUE - Success.
;;     FALSE - Failure. Most likely because the requested Url did not
;;         match the expected Url.
;;

GetFilePathName proc \
    BasePath: PCWSTR,
    RelativePath: PCWSTR,
    Buffer: PWCHAR,
    BufferSize: ULONG


    wcsncpy(Buffer, BasePath, BufferSize)

    ;.return FALSE .if (FAILED(eax))

    wcsncat(Buffer, RelativePath, BufferSize)

    ;.return FALSE .if (FAILED(eax))

    .return TRUE
    ret

GetFilePathName endp

;;
;; Routine Description:
;;
;;     The callback function to be called each time an overlapped I/O operation
;;     completes on the file. This callback is invoked by the system threadpool.
;;     Calls the corresponding I/O completion function.
;;
;;
;; Arguments:
;;
;;     Instance - Ignored.
;;
;;     pContext - Ignored.
;;
;;     Overlapped  - A pointer to a variable that receives the address of the
;;                   OVERLAPPED structure that was specified when the
;;                   completed I/O operation was started.
;;
;;     IoResult - The result of the I/O operation. If the I/O is successful,
;;                this parameter is NO_ERROR. Otherwise, this parameter is
;;                one of the system error codes.
;;
;;     NumberOfBytesTransferred - Ignored.
;;
;;     Io - A TP_IO structure that defines the I/O completion object that
;;          generated the callback.
;;
;; Return Value:
;;
;;     N/A
;;

IoCompletionCallback proc \
        Instance: PTP_CALLBACK_INSTANCE,
        pContext: PVOID,
        pOverlapped: PVOID,
        IoResult: ULONG,
        NumberOfBytesTransferred: ULONG_PTR,
        Io: PTP_IO


    local pServerContext:PSERVER_CONTEXT

    .new pIoContext:PHTTP_IO_CONTEXT = CONTAINING_RECORD(pOverlapped,
                                                    HTTP_IO_CONTEXT,
                                                    Overlapped)
    mov rcx,rax
    mov pServerContext,[rcx].HTTP_IO_CONTEXT.pServerContext

    [rcx].HTTP_IO_CONTEXT.pfCompletionFunction(pIoContext, Io, IoResult)
    ret

IoCompletionCallback endp

;;
;; Routine Description:
;;
;;     Initializes the Url and server directory using command line parameters,
;;     accesses the HTTP Server API driver, creates a server session, creates
;;     a Url Group under the specified server session, adds the specified Url to
;;     the Url Group.
;;
;;
;; Arguments:
;;     pwszUrlPathToListenFor - URL path the user wants this sample to listen
;;                              on.
;;
;;     pwszRootDirectory - Root directory on this host to which we will map
;;                         incoming URLs
;;
;;     pServerContext - The server we are associated with.
;;
;; Return Value:
;;
;;     TRUE, if http server was initialized successfully,
;;     otherwise returns FALSE.
;;

    assume rbx:PSERVER_CONTEXT

InitializeHttpServer proc \
        pwszUrlPathToListenFor: PWCHAR,
        pwszRootDirectory: PWCHAR,
        pServerContext: PSERVER_CONTEXT


    local ulResult:ULONG
    local hResult:HRESULT

    mov rbx,pServerContext

    mov hResult,S_OK

    wcsncpy(&[rbx].wszRootDirectory,
            pwszRootDirectory,
            MAX_STR_SIZE)

    .if (FAILED(hResult))

        fprintf(stderr, "Invalid command line arguments. Application stopped.\n")
        .return FALSE
    .endif

    mov ulResult,HttpInitialize(
        g_HttpApiVersion,
        HTTP_INITIALIZE_SERVER,
        NULL)

    .if (ulResult != NO_ERROR)

        fprintf(stderr, "HttpInitialized failed\n");
        .return FALSE
    .endif

    mov [rbx].bHttpInit,TRUE

    mov ulResult,HttpCreateServerSession(
        g_HttpApiVersion,
        &[rbx].sessionId,
        0)

    .if (ulResult != NO_ERROR)

        fprintf(stderr, "HttpCreateServerSession failed\n");
        .return FALSE
    .endif

    mov ulResult,HttpCreateUrlGroup(
        [rbx].sessionId,
        &[rbx].urlGroupId,
        0)

    .if (ulResult != NO_ERROR)

        fprintf(stderr, "HttpCreateUrlGroup failed\n")
        .return FALSE
    .endif

    mov ulResult,HttpAddUrlToUrlGroup(
        [rbx].urlGroupId,
        pwszUrlPathToListenFor,
        NULL,
        0)

    .if (ulResult != NO_ERROR)

        fwprintf(stderr, L"HttpAddUrlToUrlGroup failed with code 0x%x for url %s\n",
            ulResult, pwszUrlPathToListenFor)
        .return FALSE
    .endif

    .return TRUE

InitializeHttpServer endp

;;
;; Routine Description:
;;
;;      Creates the stop server event. We will set it when all active IO
;;      operations on the API have completed, allowing us to cleanup, creates a
;;      new request queue, sets a new property on the specified Url group,
;;      creates a new I/O completion.
;;
;;
;; Arguments:
;;
;;     pServerContext - The server we are associated with.
;;
;; Return Value:
;;
;;     TRUE, if http server was initialized successfully,
;;     otherwise returns FALSE.
;;

InitializeServerIo proc uses rbx pServerContext:PSERVER_CONTEXT


    .new Result:ULONG
    .new HttpBindingInfo:HTTP_BINDING_INFO = {0}

    mov rbx,pServerContext

    mov Result,HttpCreateRequestQueue(
        g_HttpApiVersion,
        L"Test_Http_Server_HTTPAPI_V2",
        NULL,
        0,
        &[rbx].hRequestQueue)

    .if (Result != NO_ERROR)

        fprintf(stderr, "HttpCreateRequestQueue failed\n")
        .return FALSE
    .endif

    mov HttpBindingInfo.Flags.Present,1
    mov HttpBindingInfo.RequestQueueHandle,[rbx].hRequestQueue

    mov Result,HttpSetUrlGroupProperty(
        [rbx].urlGroupId,
        HttpServerBindingProperty,
        &HttpBindingInfo,
        sizeof(HttpBindingInfo))

    .if (Result != NO_ERROR)

        fprintf(stderr, "HttpSetUrlGroupProperty(...HttpServerBindingProperty...) failed\n")
        .return FALSE
    .endif

    mov [rbx].Io,CreateThreadpoolIo(
        [rbx].hRequestQueue,
        &IoCompletionCallback,
        NULL,
        NULL)

    .if ([rbx].Io == NULL)

        fprintf(stderr, "Creating a new I/O completion object failed\n")
        .return FALSE
    .endif

    .return TRUE

InitializeServerIo endp

;;
;; Routine Description:
;;
;;     Calculates the number of processors and post a proportional number of
;;     receive requests.
;;
;; Arguments:
;;
;;     pServerContext - The server we are associated with.
;;
;; Return Value:
;;
;;    TRUE, if http server was initialized successfully,
;;    otherwise returns FALSE.
;;

StartServer proc uses rbx rdi pServerContext:PSERVER_CONTEXT


    local dwProcessAffinityMask:DWORD_PTR
    local dwSystemAffinityMask:DWORD_PTR
    local wRequestsCounter:WORD
    local bGetProcessAffinityMaskSucceed:BOOL

    mov bGetProcessAffinityMaskSucceed,GetProcessAffinityMask(
                                        GetCurrentProcess(),
                                        &dwProcessAffinityMask,
                                        &dwSystemAffinityMask)


    .if(bGetProcessAffinityMaskSucceed)

        .for (wRequestsCounter = 0: dwProcessAffinityMask: dwProcessAffinityMask >>= 1)

            .if (dwProcessAffinityMask & 0x1)
                inc wRequestsCounter
            .endif
        .endf

        imul ax,wRequestsCounter,REQUESTS_PER_PROCESSOR
        mov wRequestsCounter,ax

    .else


        fprintf(stderr,
                "We could not calculate the number of processor's, "
                "the server will continue with the default number = %d\n",
                OUTSTANDING_REQUESTS)

        mov wRequestsCounter,OUTSTANDING_REQUESTS
    .endif

    .for (: wRequestsCounter > 0: --wRequestsCounter)

        .new pIoRequest:PHTTP_IO_REQUEST
        .new Result:ULONG

        mov pIoRequest,AllocateHttpIoRequest(pServerContext)
        mov rdi,rax
        assume rdi:PHTTP_IO_REQUEST

        .if (pIoRequest == NULL)

            fprintf(stderr, "AllocateHttpIoRequest failed for context %d\n", wRequestsCounter)
            .return FALSE
        .endif

        mov rbx,pServerContext
        StartThreadpoolIo([rbx].Io)

        mov Result,HttpReceiveHttpRequest(
            [rbx].hRequestQueue,
            HTTP_NULL_ID,
            HTTP_RECEIVE_REQUEST_FLAG_COPY_BODY,
            [rdi].pHttpRequest,
            sizeof(HTTP_IO_REQUEST.RequestBuffer),
            NULL,
            &[rdi].ioContext.Overlapped
            )

        .if (Result != ERROR_IO_PENDING && Result != NO_ERROR)

            CancelThreadpoolIo([rbx].Io)

            .if (Result == ERROR_MORE_DATA)

                ProcessReceiveAndPostResponse(pIoRequest, [rbx].Io, ERROR_MORE_DATA)
            .endif

            CleanupHttpIoRequest(pIoRequest)

            fprintf(stderr, "HttpReceiveHttpRequest failed, error 0x%lx\n", Result)

            .return FALSE
        .endif
    .endf

    .return TRUE

StartServer endp

;;
;; Routine Description:
;;
;;     Stops queuing requests for the specified request queue process,
;;     waits for the pended requests to be completed,
;;     waits for I/O completion callbacks to complete.
;;
;; Arguments:
;;
;;     pServerContext - The server we are associated with.
;;
;; Return Value:
;;
;;     N/A
;;

StopServer proc uses rbx pServerContext:PSERVER_CONTEXT


    mov rbx,pServerContext
    .if ([rbx].hRequestQueue != NULL)

        mov [rbx].bStopServer,TRUE

        HttpShutdownRequestQueue([rbx].hRequestQueue)
    .endif

    .if ([rbx].Io != NULL)

        ;;
        ;; This call will block until all IO complete their callbacks.
        WaitForThreadpoolIoCallbacks([rbx].Io, FALSE)
    .endif
    ret

StopServer endp

;;
;; Routine Description:
;;
;;      Closes the handle to the specified request queue, releases the specified
;;      I/O completion object, deletes the stop server event.
;;
;;
;; Arguments:
;;
;;     pServerContext - The server we are associated with.
;;
;; Return Value:
;;
;;     N/A
;;

UninitializeServerIo proc uses rbx pServerContext:PSERVER_CONTEXT


    mov rbx,pServerContext
    .if ([rbx].hRequestQueue != NULL)

        HttpCloseRequestQueue([rbx].hRequestQueue)
        mov [rbx].hRequestQueue,NULL
    .endif

    .if ([rbx].Io != NULL)

        CloseThreadpoolIo([rbx].Io)
        mov [rbx].Io,NULL
    .endif
    ret

UninitializeServerIo endp


;;
;; Routine Description:
;;
;;     Closes the Url Group, deletes the server session
;;     cleans up resources used by the HTTP Server API.
;;
;;
;; Arguments:
;;
;;     pServerContext - The server we are associated with.
;;
;; Return Value:
;;
;;     N/A
;;

UninitializeHttpServer proc uses rbx pServerContext:PSERVER_CONTEXT


    mov rbx,pServerContext
    .if ([rbx].urlGroupId != 0)

        HttpCloseUrlGroup([rbx].urlGroupId)
        mov [rbx].urlGroupId,0
    .endif

    .if ([rbx].sessionId != 0)

        HttpCloseServerSession([rbx].sessionId)
        mov [rbx].sessionId,0
    .endif

    .if ([rbx].bHttpInit == TRUE)

        HttpTerminate(HTTP_INITIALIZE_SERVER, NULL)
        mov [rbx].bHttpInit,FALSE
    .endif
    ret

UninitializeHttpServer endp

;;
;; Routine Description:
;;
;;     Step by step:
;;          - checks the number of command line parameters,
;;          - initializes the http server, if failed uninitializes the http server,
;;          - initializes http server Io completion object, if failed
;;            uninitializes it and uninitializes the http server,
;;          - starts http server, if failed stops http server, uninitializes,
;;            Io completion object object and uninitializes the http server.
;;
;;     Cleans-up upon user input. The clean up process consists of:
;;
;;          - uninitializes the http server,
;;          - uninitializes Io completion object,
;;          - uninitializes the http server.
;;
;; Arguments:
;;     argc - Contains the count of arguments that follow in argv.
;;
;;     argv - An array of null-terminated strings representing command-line
;;            Expected:
;;              argv[1] - is the Url base this sample will listen for.
;;              argv[2] - is the local directory to map incoming requested Url
;;                        to locally.
;;
;; Return Value:
;;
;;     Exit code.
;;

wmain proc uses rsi rdi \
        argc:DWORD,
        argv:ptr ptr WCHAR


    .new ServerContext:SERVER_CONTEXT = {0}

    mov rsi,argv

    .if (argc != 3)
        .return FALSE
    .endif

    mov edi,wcslen([rsi+size_t])
    wcslen([rsi+size_t*2])
    .if (edi > MAX_STR_SIZE || \
         eax > MAX_STR_SIZE)
        .return FALSE
    .endif

    .if (!InitializeHttpServer([rsi+size_t], [rsi+size_t*2], &ServerContext))
        jmp @CleanServer
    .endif

    .if (!InitializeServerIo(&ServerContext))
        jmp @CleanIo
    .endif

    .if (!StartServer(&ServerContext))
        jmp @StopServer
    .endif

    printf("HTTP server is running.\n")
    printf("Press any key to stop.\n")

    ;; Waiting for the user command.

    _getch()

@StopServer:
    StopServer(&ServerContext)

@CleanIo:
    UninitializeServerIo(&ServerContext)

@CleanServer:
    UninitializeHttpServer(&ServerContext)

    printf("Done.\n")

    .return 0

wmain endp

    end
