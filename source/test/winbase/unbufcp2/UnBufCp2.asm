;;
;; Module Name:
;;
;;     unbufcp2.c
;;
;; Abstract:
;;
;;     Intended to demonstrate how to complete I/O in a different thread
;;     asynchronously than the I/O was started from.  This is useful for
;;     people who want a more powerful mechanism of asynchronous completion
;;     callbacks than Win32 provides (i.e. VMS developers who are used to ASTs).
;;
;;     Two threads are used. The first thread posts overlapped reads from the
;;     source file. These reads complete to an I/O completion port the second
;;     thread is waiting on. The second thread sees the I/O completion and
;;     posts an overlapped write to the destination file. The write completes
;;     to another I/O completion port that the first thread is waiting on.
;;     The first thread sees the I/O completion and posts another overlapped
;;     read.
;;
;;     Thread 1                                        Thread 2
;;        |                                               |
;;        |                                               |
;;     kick off a few                           -->GetQueuedCompletionStatus(ReadPort)
;;     overlapped reads                         |         |
;;        |                                     |         |
;;        |                                     |  read has completed,
;;   ->GetQueuedCompletionStatus(WritePort)     |  kick off the corresponding
;;   |    |                                     |  write.
;;   | write has completed,                     |         |
;;   | kick off another                         |_________|
;;   | read
;;   |    |
;;   |____|
;;

ifndef __PE__
.pragma comment(linker,"/DEFAULTLIB:libcmtd.lib")
_LIBCMT equ 1
endif

include windows.inc
include stdio.inc
include stdlib.inc
include ctype.inc
include tchar.inc

option dllimport:none

.data

;; File handles for the copy operation. All read operations are
;; from SourceFile. All write operations are to DestFile.

SourceFile HANDLE 0
DestFile HANDLE 0


;; I/O completion ports. All reads from the source file complete
;; to ReadPort. All writes to the destination file complete to
;; WritePort.

ReadPort HANDLE 0
WritePort HANDLE 0


;; version information

ver OSVERSIONINFO <>


;; Structure used to track each outstanding I/O. The maximum
;; number of I/Os that will be outstanding at any time is
;; controllable by the MAX_CONCURRENT_IO definition.


MAX_CONCURRENT_IO equ 20

COPY_CHUNK STRUC
Overlapped OVERLAPPED <>
Buffer     LPVOID ?
COPY_CHUNK ENDS
PCOPY_CHUNK typedef ptr COPY_CHUNK

CopyChunk COPY_CHUNK MAX_CONCURRENT_IO dup(<>)


;; Define the size of the buffers used to do the I/O.
;; 64K is a nice number.

BUFFER_SIZE equ (64*1024)


;; The system's page size will always be a multiple of the
;; sector size. Do all I/Os in page-size chunks.

PageSize DWORD 0
ferr LPFILE 0

.code

;; Local function prototypes


WriteLoop proto WINAPI FileSize:ULARGE_INTEGER
ReadLoop proto FileSize:ULARGE_INTEGER

main proc argc:SINT, argv:ptr ptr sbyte

  local WritingThread   : HANDLE,
        ThreadId        : DWORD,
        FileSize        : ULARGE_INTEGER,
        InitialFileSize : ULARGE_INTEGER,
        Success         : BOOL,
        Status          : DWORD,
        StartTime       : QWORD,
        EndTime         : QWORD,
        SystemInfo      : SYSTEM_INFO,
        BufferedHandle  : HANDLE

    mov ferr,&stderr

    .if (argc != 3)

        mov rdx,argv
        fprintf(ferr, "Usage: %s SourceFile DestinationFile\n", [rdx])
        exit(1)
    .endif


    ;;confirm we are running on Windows NT 3.5 or greater, if not, display notice and
    ;;terminate.  Completion ports are only supported on Win32 & Win32s.  Creating a
    ;;Completion port with no handle specified is only supported on NT 3.51, so we need
    ;;to know what we're running on.  Note, Win32s does not support console apps, thats
    ;;why we exit here if we are not on Windows NT.
    ;;
    ;;
    ;;ver.dwOSVersionInfoSize needs to be set before calling GetVersionInfoEx()

    mov ver.dwOSVersionInfoSize,sizeof(OSVERSIONINFO)


    ;;Failure here could mean several things 1. On an NT system,
    ;;it indicates NT version 3.1 because GetVersionEx() is only
    ;;implemented on NT 3.5.  2. On Windows 3.1 system, it means
    ;;either Win32s version 1.1 or 1.0 is installed.

    mov Success,GetVersionEx(&ver)

    ;;GetVersionEx() failed - see above.
    ;;GetVersionEx() succeeded but we are not on NT.

    .if ( (!Success) || (ver.dwPlatformId != VER_PLATFORM_WIN32_NT) )

       MessageBox(NULL,
                  "This sample application can only be run on Windows NT. 3.5 or greater\n"
                  "This application will now terminate.",
                  "UnBufCp2", MB_OK or MB_ICONSTOP or MB_SETFOREGROUND )
       exit( 1 )
    .endif


    ;; Get the system's page size.

    GetSystemInfo(&SystemInfo)
    mov eax,SystemInfo.dwPageSize
    mov PageSize,eax


    ;; Open the source file and create the destination file.
    ;; Use FILE_FLAG_NO_BUFFERING to avoid polluting the
    ;; system cache with two copies of the same data.

    mov rax,argv
    mov rbx,[rax+8]

    .if CreateFile(rbx,
            GENERIC_READ or GENERIC_WRITE,
            FILE_SHARE_READ,
            NULL,
            OPEN_EXISTING,
            FILE_FLAG_NO_BUFFERING or FILE_FLAG_OVERLAPPED,
            NULL) == INVALID_HANDLE_VALUE

        fprintf(ferr, "failed to open %s, error %d\n", rbx, GetLastError())
        exit(1)
    .endif
    mov SourceFile,rax

    GetFileSize(SourceFile, &FileSize.HighPart)
    mov FileSize.LowPart,eax
    .if (eax == 0xffffffff)
        .if (GetLastError() != NO_ERROR)
            fprintf(ferr, "GetFileSize failed, error %d\n", eax)
            exit(1)
        .endif
    .endif

    mov rax,argv
    mov rbx,[rax+16]
    .if CreateFile(rbx,
            GENERIC_READ or GENERIC_WRITE,
            FILE_SHARE_READ or FILE_SHARE_WRITE,
            NULL,
            CREATE_ALWAYS,
            FILE_FLAG_NO_BUFFERING or FILE_FLAG_OVERLAPPED,
            SourceFile) == INVALID_HANDLE_VALUE

        fprintf(ferr, "failed to open %s, error %d\n", rbx, GetLastError())
        exit(1)
    .endif
    mov DestFile,rax


    ;; Extend the destination file so that the filesystem does not
    ;; turn our asynchronous writes into synchronous ones.

    mov rcx,FileSize.QuadPart
    mov eax,PageSize
    add rcx,rax
    dec rcx
    dec rax
    not rax
    and rcx,rax
    mov InitialFileSize.QuadPart,rcx

    .ifd SetFilePointer(DestFile,
            InitialFileSize.LowPart,
            &InitialFileSize.HighPart,
            FILE_BEGIN) == INVALID_SET_FILE_POINTER
        .if (GetLastError() != NO_ERROR)
            fprintf(ferr, "SetFilePointer failed, error %d\n", GetLastError())
            exit(1)
        .endif
    .endif

    .if !SetEndOfFile(DestFile)
        fprintf(ferr, "SetEndOfFile failed, error %d\n", GetLastError())
        exit(1)
    .endif

    ;;In NT 3.51 it is not necessary to specify the FileHandle parameter
    ;;of CreateIoCompletionPort()--It is legal to specify the FileHandle
    ;;as INVALID_HANDLE_VALUE.  However, for NT 3.5 an overlapped file
    ;;handle is needed.
    ;;
    ;;We know already that we are running on NT, or else we wouldn't have
    ;;gotten this far, so lets see what version we are running on.

    .if (ver.dwMajorVersion == 3 && ver.dwMinorVersion == 50)

        ;;we're running on NT 3.5 - Completion Ports exists

        .if !CreateIoCompletionPort(
                SourceFile,             ;;file handle to associate with I/O completion port
                NULL,                   ;;optional handle to existing I/O completion port
                dword ptr SourceFile,   ;;completion key
                1)                      ;;# of threads allowed to execute concurrently


            fprintf(ferr, "failed to create ReadPort, error %d\n", GetLastError())
            exit(1)
        .endif
        mov ReadPort,rax

    .else

        ;;We are running on NT 3.51 or greater.
        ;;
        ;;Create the I/O Completion Port.

        CreateIoCompletionPort(INVALID_HANDLE_VALUE,    ;;file handle to associate with I/O completion port
                               NULL,                    ;;optional handle to existing I/O completion port
                               dword ptr SourceFile,    ;;completion key
                               1)                       ;;# of threads allowed to execute concurrently





         ;;If we need to, aka we're running on NT 3.51, let's associate a file handle with the
         ;;completion port.

         mov ReadPort,rax
         CreateIoCompletionPort(SourceFile,
                                ReadPort,
                                dword ptr SourceFile,  ;;should be the previously specified key.
                                1)

         .if (ReadPort == NULL)

            fprintf(ferr,
                    "failed to create ReadPort, error %d\n",
                    GetLastError())

            exit(1)

         .endif
    .endif

    .if !CreateIoCompletionPort(DestFile, NULL, dword ptr DestFile, 1)
        fprintf(ferr, "failed to create WritePort, error %d\n", GetLastError())
        exit(1)
    .endif
    mov WritePort,rax


    ;; Start the writing thread

    .if !CreateThread(NULL, 0, &WriteLoop, &FileSize, 0, &ThreadId)
        fprintf(ferr, "failed to create write thread, error %d\n", GetLastError())
        exit(1)
    .endif
    mov WritingThread,rax
    CloseHandle(WritingThread)

    mov StartTime,GetTickCount64()


    ;; Start the reads

    ReadLoop(FileSize)

    mov EndTime,GetTickCount64()

    ;; We need another handle to the destination file that is
    ;; opened without FILE_FLAG_NO_BUFFERING. This allows us to set
    ;; the end-of-file marker to a position that is not sector-aligned.

    .if CreateFile(rbx,
                   GENERIC_WRITE,
                   FILE_SHARE_READ or FILE_SHARE_WRITE,
                   NULL,
                   OPEN_EXISTING,
                   0,
                   NULL) == INVALID_HANDLE_VALUE

        fprintf(ferr,
                "failed to open buffered handle to %s, error %d\n",
                rbx, GetLastError())
        exit(1)
    .endif
    mov BufferedHandle,rax


    ;; Set the destination's file size to the size of the
    ;; source file, in case the size of the source file was
    ;; not a multiple of the page size.

    mov Status,SetFilePointer(BufferedHandle, FileSize.LowPart,
            &FileSize.HighPart, FILE_BEGIN)
    .if ((Status == INVALID_SET_FILE_POINTER) && (GetLastError() != NO_ERROR))
        fprintf(ferr, "final SetFilePointer failed, error %d\n", GetLastError())
        exit(1)
    .endif

    .if !SetEndOfFile(BufferedHandle)
        fprintf(ferr, "SetEndOfFile failed, error %d\n", GetLastError())
        exit(1)
    .endif
    CloseHandle(BufferedHandle)
    CloseHandle(SourceFile)
    CloseHandle(DestFile)

    mov     rax,EndTime
    sub     rax,StartTime
    cvtsi2sd xmm0,rax
    mov     rax,1000.0
    movq    xmm1,rax
    divsd   xmm0,xmm1
    movq    rbx,xmm0

    printf("\n\n%d bytes copied in %.3f seconds\n", FileSize.LowPart, rbx)

    mov     rax,FileSize.QuadPart
    cvtsi2sd xmm0,rax
    mov     rax,1024.0*1024.0
    movq    xmm1,rax
    divsd   xmm0,xmm1
    movq    xmm1,rbx
    divsd   xmm0,xmm1
    movq    rdx,xmm0

    printf("%.2f MB/sec\n", rdx)

    xor eax,eax
    ret

main endp


ReadLoop proc uses rsi rdi rbx FileSize:ULARGE_INTEGER

  local ReadPointer         : ULARGE_INTEGER,
        Success             : BOOL,
        NumberBytes         : DWORD,
        CompletedOverlapped : LPOVERLAPPED,
        Key                 : DWORD_PTR,
        Chunk               : PCOPY_CHUNK,
        PendingIO           : SINT,
        i                   : SINT


    ;; Start reading the file. Kick off MAX_CONCURRENT_IO reads, then just
    ;; loop waiting for writes to complete.

    xor eax,eax
    mov PendingIO,eax
    mov ReadPointer.QuadPart,rax

    .for (esi=0, ebx=0: ebx < MAX_CONCURRENT_IO: ebx++, esi+=sizeof(COPY_CHUNK))

        .break .if (ReadPointer.QuadPart >= FileSize.QuadPart)

        lea rdi,CopyChunk
        add rdi,rsi
        assume rdi:ptr COPY_CHUNK


        ;; Use VirtualAlloc so we get a page-aligned buffer suitable
        ;; for unbuffered I/O.

        .if !VirtualAlloc(NULL, BUFFER_SIZE, MEM_COMMIT, PAGE_READWRITE)

            fprintf(ferr, "VirtualAlloc %d failed, error %d\n", ebx, GetLastError())
            exit(1)
        .endif

        mov [rdi].Buffer,rax
        mov [rdi].Overlapped._Offset,ReadPointer.LowPart
        mov [rdi].Overlapped.OffsetHigh,ReadPointer.HighPart
        mov [rdi].Overlapped.hEvent,NULL ;; not needed

        .if !ReadFile(SourceFile, [rdi].Buffer, BUFFER_SIZE, &NumberBytes, &[rdi].Overlapped)

            .if GetLastError() != ERROR_IO_PENDING
                fprintf(ferr, "ReadFile at %lx failed, error %d\n", ReadPointer.LowPart,  eax)
                exit(1)
            .endif
        .endif
        add ReadPointer.QuadPart,BUFFER_SIZE
        inc PendingIO
    .endf


    ;; We have started the initial async. reads, enter the main loop.
    ;; This simply waits until a write completes, then issues the next
    ;; read.
    int 3
    .while (PendingIO)

        .if !GetQueuedCompletionStatus(WritePort, &NumberBytes, &Key, &CompletedOverlapped, INFINITE)

            ;; Either the function failed to dequeue a completion packet
            ;; (CompletedOverlapped is not NULL) or it dequeued a completion
            ;; packet of a failed I/O operation (CompletedOverlapped is NULL).

            fprintf(ferr,
                    "GetQueuedCompletionStatus on the IoPort failed, error %d\n",
                    GetLastError())
            exit(1)
        .endif

        ;; Issue the next read using the buffer that has just completed.

        .if (ReadPointer.QuadPart < FileSize.QuadPart)

            mov rbx,CompletedOverlapped
            assume rbx:ptr COPY_CHUNK
            mov [rbx].Overlapped._Offset,ReadPointer.LowPart
            mov [rbx].Overlapped.OffsetHigh,ReadPointer.HighPart
            add ReadPointer.QuadPart,BUFFER_SIZE

            .if !ReadFile(SourceFile, [rbx].Buffer, BUFFER_SIZE, &NumberBytes, &[rbx].Overlapped)

                .if GetLastError() != ERROR_IO_PENDING
                    fprintf(ferr, "ReadFile at %lx failed, error %d\n", [rbx].Overlapped._Offset,
                            eax)
                    exit(1)
                .endif
            .endif

        .else

            ;; There are no more reads left to issue, just wait
            ;; for the pending writes to drain.

            dec PendingIO

        .endif
    .endw

    ;; All done. There is no need to call VirtualFree() to free CopyChunk
    ;; buffers here. The buffers will be freed when this process exits.
    ret

ReadLoop endp


WriteLoop proc uses rbx WINAPI FileSize:ULARGE_INTEGER

  local Success             : BOOL,
        Key                 : DWORD_PTR,
        CompletedOverlapped : LPOVERLAPPED,
        Chunk               : PCOPY_CHUNK,
        NumberBytes         : DWORD,
        TotalBytesWritten   : ULARGE_INTEGER

    mov TotalBytesWritten.QuadPart,0
    int 3
    .for (::)

        .if !GetQueuedCompletionStatus(ReadPort, &NumberBytes, &Key, &CompletedOverlapped, INFINITE)

            ;; Either the function failed to dequeue a completion packet
            ;; (CompletedOverlapped is not NULL) or it dequeued a completion
            ;; packet of a failed I/O operation (CompletedOverlapped is NULL).

            fprintf(ferr,
                    "GetQueuedCompletionStatus on the IoPort failed, error %d\n",
                    GetLastError())
            exit(1)
        .endif


        ;; Update the total number of bytes written.

        add TotalBytesWritten.QuadPart,NumberBytes

        ;; Issue the next write using the buffer that has just been read into.

        mov rbx,CompletedOverlapped

        ;; Round the number of bytes to write up to a sector boundary

        mov ecx,PageSize
        dec ecx
        mov eax,NumberBytes
        add eax,ecx
        not ecx
        and eax,ecx
        mov NumberBytes,eax

        .if !WriteFile(DestFile, [rbx].Buffer, NumberBytes, &NumberBytes, &[rbx].Overlapped)

            .ifd GetLastError() != ERROR_IO_PENDING

                fprintf(ferr, "WriteFile at %lx failed, error %d\n", [rbx].Overlapped._Offset, eax)
                exit(1)
            .endif
        .endif


        ;;Check to see if we've copied the complete file, if so return

        .break .if (TotalBytesWritten.QuadPart >= FileSize.QuadPart)

    .endf
    ret

WriteLoop endp

    end _tstart

