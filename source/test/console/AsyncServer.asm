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
include strsafe.inc
include http.inc
include tchar.inc

MALLOC macro x
    exitm<HeapAlloc(GetProcessHeap(), 0, (x))>
    endm
FREE macro x
    exitm<HeapFree(GetProcessHeap(), 0, (x))>
    endm

define MAX_STR_SIZE 256
define OUTSTANDING_REQUESTS 16
define REQUESTS_PER_PROCESSOR 4
define REQUEST_BUFFER_SIZE 4096

CALLBACK(HTTP_COMPLETION_FUNCTION, :ptr _HTTP_IO_CONTEXT, :PTP_IO, :ULONG)

SERVER_CONTEXT          STRUC
wszRootDirectory        WCHAR MAX_STR_SIZE dup(?)
sessionId               HTTP_SERVER_SESSION_ID ?
urlGroupId              HTTP_URL_GROUP_ID ?
hRequestQueue           HANDLE ?
Io                      PTP_IO ?
bHttpInit               BOOL ?
bStopServer             BOOL ?
SERVER_CONTEXT          ENDS
PSERVER_CONTEXT         typedef ptr SERVER_CONTEXT

HTTP_IO_CONTEXT         STRUC
Overlapped              OVERLAPPED <>
pfCompletionFunction    HTTP_COMPLETION_FUNCTION ?
pServerContext          PSERVER_CONTEXT ?
HTTP_IO_CONTEXT         ENDS
PHTTP_IO_CONTEXT        typedef ptr HTTP_IO_CONTEXT

HTTP_IO_REQUEST         STRUC
ioContext               HTTP_IO_CONTEXT <>
pHttpRequest            PHTTP_REQUEST ?
RequestBuffer           UCHAR REQUEST_BUFFER_SIZE dup(?)
HTTP_IO_REQUEST         ENDS
PHTTP_IO_REQUEST        typedef ptr HTTP_IO_REQUEST

HTTP_IO_RESPONSE        STRUC
ioContext               HTTP_IO_CONTEXT <>
HttpResponse            HTTP_RESPONSE <>
HttpDataChunk           HTTP_DATA_CHUNK <>
HTTP_IO_RESPONSE        ENDS
PHTTP_IO_RESPONSE       typedef ptr HTTP_IO_RESPONSE

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
g_HttpApiVersion HTTPAPI_VERSION HTTPAPI_VERSION_2

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
    endp

    assume rbx:PHTTP_IO_RESPONSE

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
    endp


    assume rdi:PHTTP_DATA_CHUNK

CreateMessageResponse proc uses rdi rbx pServerContext:PSERVER_CONTEXT,
        code:USHORT, pReason:PCHAR, pMessage:PCHAR
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
    endp


CreateFileResponse proc uses rdi rbx pServerContext:PSERVER_CONTEXT, hFile:HANDLE
   .new IoResponse:PHTTP_IO_RESPONSE = AllocateHttpIoResponse(ldr(pServerContext))
   .new pChunk:PHTTP_DATA_CHUNK
    .if ( rax )
        mov rbx,rax
        mov [rbx].HttpResponse.StatusCode,g_usOKCode
        mov [rbx].HttpResponse.pReason,&@CStr(g_szOKReason)
        mov [rbx].HttpResponse.ReasonLength,strlen(g_szOKReason)
        lea rdi,[rbx].HttpResponse.pEntityChunks[0]
        mov [rdi].DataChunkType,HttpDataChunkFromFileHandle
        mov [rdi].FromFileHandle.ByteRange.Length.QuadPart,HTTP_BYTE_RANGE_TO_EOF
        mov [rdi].FromFileHandle.ByteRange.StartingOffset.QuadPart,0
        mov [rdi].FromFileHandle.FileHandle,hFile
        mov rax,rbx
    .endif
    ret
    endp


GetFilePathName proc BasePath: PCWSTR, RelativePath: PCWSTR, Buffer: PWCHAR, BufferSize: ULONG
    wcsncpy(Buffer, BasePath, BufferSize)
    wcsncat(Buffer, RelativePath, BufferSize)
   .return TRUE
    endp

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
    endp

    assume rbx:PHTTP_IO_REQUEST
    assume rdi:PSERVER_CONTEXT

ProcessReceiveAndPostResponse proc uses rsi rdi rbx pIoRequest:PHTTP_IO_REQUEST, Io:PTP_IO, IoResult:ULONG

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
            mov pIoResponse,CreateMessageResponse(pServerContext, g_usNotImplementedCode, g_szNotImplementedReason, g_szNotImplementedMessage)
           .endc
        .endif
        mov bValidUrl,GetFilePathName(&[rdi].wszRootDirectory, [rsi].HTTP_REQUEST.CookedUrl.pAbsPath, &wszFilePath, MAX_STR_SIZE)
        .if (bValidUrl == FALSE)
            mov pIoResponse,CreateMessageResponse(pServerContext, g_usFileNotFoundCode, g_szFileNotFoundReason, g_szBadPathMessage)
           .endc
        .endif
        mov hFile,CreateFileW(&wszFilePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)
        .if (hFile == INVALID_HANDLE_VALUE)
            GetLastError()
            .if (eax == ERROR_PATH_NOT_FOUND || eax == ERROR_FILE_NOT_FOUND)
                mov pIoResponse,CreateMessageResponse(pServerContext, g_usFileNotFoundCode, g_szFileNotFoundReason, g_szFileNotFoundMessage)
               .endc
            .endif
            mov pIoResponse,CreateMessageResponse(pServerContext, g_usFileNotFoundCode, g_szFileNotFoundReason, g_szFileNotAccessibleMessage)
           .endc
        .endif
        mov pIoResponse,CreateFileResponse(pServerContext, hFile)
        mov CachePolicy.Policy,HttpCachePolicyUserInvalidates
        mov CachePolicy.SecondsToLive,0
       .endc
    .case ERROR_MORE_DATA
        mov pIoResponse,CreateMessageResponse(pServerContext, g_usEntityTooLargeCode, g_szEntityTooLargeReason, g_szEntityTooLargeMessage)
       .endc
    .default
        .return
    .endsw
    .if ( pIoResponse == NULL )
        .return
    .endif
    StartThreadpoolIo(Io)
    xor ecx,ecx
    .if (hFile != INVALID_HANDLE_VALUE)
        lea rcx,CachePolicy
    .endif
    mov rdx,pIoResponse
    mov Result,HttpSendHttpResponse([rdi].hRequestQueue, [rsi].HTTP_REQUEST.RequestId, 0, &[rdx].HTTP_IO_RESPONSE.HttpResponse, rcx, NULL, NULL, 0, &[rbx].ioContext.Overlapped, NULL)
    .if ( Result != NO_ERROR && Result != ERROR_IO_PENDING )
        CancelThreadpoolIo(Io)
        fprintf(stderr, "HttpSendHttpResponse failed, error 0x%lx\n", Result)
        CleanupHttpIoResponse(pIoResponse)
    .endif
    ret
    endp

CleanupHttpIoRequest proc pIoRequest:PHTTP_IO_REQUEST
    FREE(pIoRequest)
    ret
    endp

    assume rbx:PSERVER_CONTEXT
    assume rdi:PHTTP_IO_REQUEST

PostNewReceive proc pServerContext:PSERVER_CONTEXT, Io:PTP_IO
    .new pIoRequest:PHTTP_IO_REQUEST = AllocateHttpIoRequest(ldr(pServerContext))
    .new Result:ULONG
    .return .if ( rax == NULL )
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
    .if ( Result != ERROR_IO_PENDING && Result != NO_ERROR )
        CancelThreadpoolIo(Io)
        fprintf(stderr, "HttpReceiveHttpRequest failed, error 0x%lx\n", Result)
        .if (Result == ERROR_MORE_DATA)
            ProcessReceiveAndPostResponse(pIoRequest, Io, ERROR_MORE_DATA)
        .endif
         CleanupHttpIoRequest(pIoRequest)
    .endif
    ret
    endp

ReceiveCompletionCallback proc  pIoContext:PHTTP_IO_CONTEXT, Io:PTP_IO, IoResult:ULONG
    .new pIoRequest:PHTTP_IO_REQUEST = CONTAINING_RECORD(ldr(pIoContext), HTTP_IO_REQUEST, ioContext)
    .new pServerContext:PSERVER_CONTEXT = [rax].HTTP_IO_REQUEST.ioContext.pServerContext
    .if ( [rax].SERVER_CONTEXT.bStopServer == FALSE )
        ProcessReceiveAndPostResponse(pIoRequest, Io, IoResult)
        PostNewReceive(pServerContext, Io)
    .endif
    CleanupHttpIoRequest(pIoRequest)
    ret
    endp

SendCompletionCallback proc pIoContext:PHTTP_IO_CONTEXT, Io: PTP_IO, IoResult: ULONG
   .new pIoResponse:PHTTP_IO_RESPONSE = CONTAINING_RECORD(ldr(pIoContext), HTTP_IO_RESPONSE, ioContext)
    CleanupHttpIoResponse(rax)
    ret
    endp

    assume rbx:PHTTP_IO_RESPONSE
    assume rdi:PHTTP_KNOWN_HEADER

IoCompletionCallback proc Instance:PTP_CALLBACK_INSTANCE, pContext:PVOID, pOverlapped:PVOID,
        IoResult:ULONG, numberOfBytesTransferred:ULONG_PTR, Io:PTP_IO
   .new pServerContext:PSERVER_CONTEXT
   .new pIoContext:PHTTP_IO_CONTEXT = CONTAINING_RECORD(pOverlapped, HTTP_IO_CONTEXT, Overlapped)
    mov rcx,rax
    mov pServerContext,[rcx].HTTP_IO_CONTEXT.pServerContext
    [rcx].HTTP_IO_CONTEXT.pfCompletionFunction(pIoContext, Io, IoResult)
    ret
    endp

    assume rbx:PSERVER_CONTEXT

InitializeHttpServer proc pwszUrlPathToListenFor:PWCHAR, pwszRootDirectory:PWCHAR, pServerContext:PSERVER_CONTEXT

  local ulResult:ULONG
  local hResult:HRESULT

    mov rbx,pServerContext
    mov hResult,S_OK
    wcsncpy(&[rbx].wszRootDirectory, pwszRootDirectory, MAX_STR_SIZE)
    .if (FAILED(hResult))
        fprintf(stderr, "Invalid command line arguments. Application stopped.\n")
       .return FALSE
    .endif
    mov ulResult,HttpInitialize(g_HttpApiVersion, HTTP_INITIALIZE_SERVER, NULL)
    .if (ulResult != NO_ERROR)
        fprintf(stderr, "HttpInitialized failed\n");
        .return FALSE
    .endif
    mov [rbx].bHttpInit,TRUE
    mov ulResult,HttpCreateServerSession(g_HttpApiVersion, &[rbx].sessionId, 0)
    .if (ulResult != NO_ERROR)
        fprintf(stderr, "HttpCreateServerSession failed\n");
       .return FALSE
    .endif
    mov ulResult,HttpCreateUrlGroup([rbx].sessionId, &[rbx].urlGroupId, 0)
    .if (ulResult != NO_ERROR)
        fprintf(stderr, "HttpCreateUrlGroup failed\n")
       .return FALSE
    .endif
    mov ulResult,HttpAddUrlToUrlGroup([rbx].urlGroupId, pwszUrlPathToListenFor, NULL, 0)
    .if (ulResult != NO_ERROR)
        fwprintf(stderr, L"HttpAddUrlToUrlGroup failed with code 0x%x for url %s\n",
            ulResult, pwszUrlPathToListenFor)
        .return FALSE
    .endif
    .return TRUE
    endp

InitializeServerIo proc uses rbx pServerContext:PSERVER_CONTEXT
   .new Result:ULONG
   .new HttpBindingInfo:HTTP_BINDING_INFO = {0}
    mov rbx,pServerContext
    mov Result,HttpCreateRequestQueue(g_HttpApiVersion, L"Test_Http_Server_HTTPAPI_V2", NULL, 0, &[rbx].hRequestQueue)
    .if (Result != NO_ERROR)
        fprintf(stderr, "HttpCreateRequestQueue failed\n")
       .return FALSE
    .endif
    mov HttpBindingInfo.Flags.Present,1
    mov HttpBindingInfo.RequestQueueHandle,[rbx].hRequestQueue
    mov Result,HttpSetUrlGroupProperty([rbx].urlGroupId, HttpServerBindingProperty, &HttpBindingInfo, sizeof(HttpBindingInfo))
    .if (Result != NO_ERROR)
        fprintf(stderr, "HttpSetUrlGroupProperty(...HttpServerBindingProperty...) failed\n")
        .return FALSE
    .endif
    mov [rbx].Io,CreateThreadpoolIo([rbx].hRequestQueue, &IoCompletionCallback, NULL, NULL)
    .if ([rbx].Io == NULL)
        fprintf(stderr, "Creating a new I/O completion object failed\n")
        .return FALSE
    .endif
    .return TRUE
    endp

StartServer proc uses rbx rdi pServerContext:PSERVER_CONTEXT
  local dwProcessAffinityMask:DWORD_PTR
  local dwSystemAffinityMask:DWORD_PTR
  local wRequestsCounter:WORD
  local bGetProcessAffinityMaskSucceed:BOOL

    mov bGetProcessAffinityMaskSucceed,GetProcessAffinityMask(GetCurrentProcess(), &dwProcessAffinityMask, &dwSystemAffinityMask)
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
                "the server will continue with the default number = %d\n", OUTSTANDING_REQUESTS)
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
        mov Result,HttpReceiveHttpRequest([rbx].hRequestQueue, HTTP_NULL_ID, HTTP_RECEIVE_REQUEST_FLAG_COPY_BODY,
                [rdi].pHttpRequest, sizeof(HTTP_IO_REQUEST.RequestBuffer), NULL, &[rdi].ioContext.Overlapped)
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
    endp

StopServer proc uses rbx pServerContext:PSERVER_CONTEXT
    mov rbx,pServerContext
    .if ([rbx].hRequestQueue != NULL)
        mov [rbx].bStopServer,TRUE
        HttpShutdownRequestQueue([rbx].hRequestQueue)
    .endif
    .if ([rbx].Io != NULL)
        WaitForThreadpoolIoCallbacks([rbx].Io, FALSE)
    .endif
    ret
    endp

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
    endp

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
    endp

wmain proc uses rsi rdi argc:DWORD, argv:ptr ptr WCHAR
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
    _getch()
@StopServer:
    StopServer(&ServerContext)
@CleanIo:
    UninitializeServerIo(&ServerContext)
@CleanServer:
    UninitializeHttpServer(&ServerContext)
    printf("Done.\n")
    .return 0
    endp

    end _tstart
