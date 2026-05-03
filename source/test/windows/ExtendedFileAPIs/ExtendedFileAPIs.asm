
include stdio.inc
include windows.inc
include winnls.inc
include stdlib.inc
include tchar.inc

.code


PrintUsage proc

    wprintf(
        "Usage: ExtendedFileAPIs [-id] targetFile\n\n"
        "  Display extended information about the target file or directory\n"
        "  using the GetFileInformationByHandleEx API.\n\n"
        "  -id  If this flag is specified the target file is assumed to be a file ID\n"
        "       and the program will attempt to open the file using OpenFileById.\n"
        "       The current directory will be used to determine which volume to scope\n"
        "       the open to.\n")
    ret

PrintUsage endp


PrintFileAttributes proc uses rsi FileAttributes:ULONG

    mov esi,ecx
    .if (esi & FILE_ATTRIBUTE_ARCHIVE)

        wprintf("Archive ")
        and esi,not FILE_ATTRIBUTE_ARCHIVE
    .endif

    .if (esi & FILE_ATTRIBUTE_DIRECTORY)

        wprintf("Directory ")
        and esi,not FILE_ATTRIBUTE_DIRECTORY
    .endif

    .if (esi & FILE_ATTRIBUTE_READONLY)

        wprintf("Read-Only ")
        and esi,not FILE_ATTRIBUTE_READONLY
    .endif

    .if (esi & FILE_ATTRIBUTE_HIDDEN)

        wprintf("Hidden ")
        and esi,not FILE_ATTRIBUTE_HIDDEN
    .endif

    .if (esi & FILE_ATTRIBUTE_SYSTEM)

        wprintf("System ")
        and esi,not FILE_ATTRIBUTE_SYSTEM
    .endif

    .if (esi & FILE_ATTRIBUTE_NORMAL)

        wprintf("Normal ")
        and esi,not FILE_ATTRIBUTE_NORMAL
    .endif

    .if (esi & FILE_ATTRIBUTE_TEMPORARY)

        wprintf("Temporary ")
        and esi,not FILE_ATTRIBUTE_TEMPORARY
    .endif

    .if (esi & FILE_ATTRIBUTE_COMPRESSED)

        wprintf("Compressed ")
        and esi,not FILE_ATTRIBUTE_COMPRESSED
    .endif

    .if (esi)

        wprintf("  Additional Attributes: %x", esi)
    .endif

    wprintf("\n")
    ret

PrintFileAttributes endp


PrintDate proc Date:LARGE_INTEGER

  local result:BOOL
  local fileTime:FILETIME
  local systemTime:SYSTEMTIME

    mov fileTime.dwLowDateTime,Date.LowPart
    mov fileTime.dwHighDateTime,Date.HighPart

    .return .if !FileTimeToLocalFileTime( &fileTime, &fileTime )
    .return .if !FileTimeToSystemTime( &fileTime, &systemTime )

    wprintf("%.2d/%.2d/%.4d %.2d:%.2d",
       systemTime.wMonth,
       systemTime.wDay,
       systemTime.wYear,
       systemTime.wHour,
       systemTime.wMinute)

    .return TRUE

PrintDate endp


DisplayBasicInfo proc hFile:HANDLE, bIsDirectory:ptr BOOL


  local basicInfo:FILE_BASIC_INFO
  local result:BOOL

    .ifd !GetFileInformationByHandleEx(
            hFile,
            FileBasicInfo,
            &basicInfo,
            sizeof(basicInfo))

        wprintf("Failure fetching basic information: %d\n", GetLastError())
        .return FALSE
    .endif

    wprintf("\n[Basic Information]\n\n")
    wprintf("  Creation Time: ")

    .ifd PrintDate(basicInfo.CreationTime)
        wprintf("\n")
    .else
        wprintf(" Error retrieving creation time.\n")
    .endif

    wprintf("  Change Time: ")
    .ifd PrintDate(basicInfo.ChangeTime)
        wprintf("\n")
    .else
        wprintf(" Error retrieving creation time.\n")
    .endif

    wprintf("  Last Access Time: ")
    .ifd PrintDate(basicInfo.LastAccessTime)
        wprintf("\n")
    .else
        wprintf(" Error retrieving last access time.\n")
    .endif

    wprintf("  Last Write Time: ")
    mov result,PrintDate(basicInfo.LastWriteTime)

    .if (result)
        wprintf("\n")
    .else
        wprintf(" Error retrieving last write time.\n")
    .endif

    wprintf("  File Attributes: ")
    PrintFileAttributes(basicInfo.FileAttributes)

    mov rcx,bIsDirectory
    .if (basicInfo.FileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        mov dword ptr [rcx],TRUE
    .else
        mov dword ptr [rcx],FALSE
    .endif
    .return result

DisplayBasicInfo endp


DisplayStandardInfo proc hFile:HANDLE

  local standardInfo:FILE_STANDARD_INFO
  local result:BOOL

    mov result,GetFileInformationByHandleEx( hFile,
                       FileStandardInfo,
                       &standardInfo,
                       sizeof(standardInfo))

    .if (!result)

        wprintf("Failure fetching standard information: %d\n", GetLastError())
        .return result
    .endif

    wprintf("\n[Standard Information]\n\n")

    wprintf("  Allocation Size: %I64d\n", standardInfo.AllocationSize)
    wprintf("  End of File: %I64d\n", standardInfo.EndOfFile)
    wprintf("  Number of Links: %d\n", standardInfo.NumberOfLinks)
    wprintf("  Delete Pending: ")
    .if (standardInfo.DeletePending)
        wprintf("Yes\n")
    .else
        wprintf("No\n")
    .endif
    wprintf("  Directory: ")
    .if (standardInfo.Directory)
        wprintf("Yes\n")
    .else
        wprintf("No\n")
    .endif

    .return TRUE

DisplayStandardInfo endp


DisplayNameInfo proc hFile:HANDLE


  local nameInfo:PFILE_NAME_INFO
  local nameSize:ULONG
  local result:BOOL

    ;;
    ;; Allocate an information structure that is hopefully large enough to
    ;; retrieve name information.
    ;;

    mov nameSize,sizeof(FILE_NAME_INFO) + (sizeof(WCHAR) * MAX_PATH)

retry:

    mov nameInfo,LocalAlloc(LMEM_ZEROINIT, nameSize)

    .if (nameInfo == NULL)

        SetLastError(ERROR_NOT_ENOUGH_MEMORY)
        .return FALSE
    .endif

    mov result,GetFileInformationByHandleEx( hFile,
                           FileNameInfo,
                           nameInfo,
                           nameSize )

    .if (!result)
        ;;
        ;; If our buffer wasn't large enough try again with a larger one.
        ;;
        .if (GetLastError() == ERROR_MORE_DATA)

            shl nameSize,1
            jmp retry
        .endif


        wprintf("Failure fetching name information: %d\n", GetLastError())
        LocalFree(nameInfo)
        .return result
    .endif

    wprintf("\n[Name Information]\n\n")

    mov rdx,nameInfo
    wprintf("  File Name: %S\n", &[rdx].FILE_NAME_INFO.FileName)

    LocalFree(nameInfo)
    .return TRUE

DisplayNameInfo endp


    assume rsi:PFILE_STREAM_INFO

DisplayStreamInfo proc uses rsi hFile:HANDLE

  local currentStreamInfo:PFILE_STREAM_INFO
  local result:BOOL
  local streamInfo:PFILE_STREAM_INFO
  local streamInfoSize:ULONG


    ;;
    ;; Allocate an information structure that is hopefully large enough to
    ;; retrieve stream information.
    ;;

    mov streamInfoSize,sizeof(FILE_STREAM_INFO) + (sizeof(WCHAR) * MAX_PATH)

retry:

    mov streamInfo,LocalAlloc(LMEM_ZEROINIT, streamInfoSize)

    .if (streamInfo == NULL)

        SetLastError(ERROR_NOT_ENOUGH_MEMORY)
        .return FALSE
    .endif

    mov result,GetFileInformationByHandleEx( hFile,
                           FileStreamInfo,
                           streamInfo,
                           streamInfoSize )

    .if (!result)
        ;;
        ;; If our buffer wasn't large enough try again with a larger one.
        ;;
        .if (GetLastError() == ERROR_MORE_DATA)

            shl streamInfoSize,1
            jmp retry
        .endif

        wprintf("Failure fetching stream information: %d\n", GetLastError())
        LocalFree(streamInfo)

        .return result
    .endif

    wprintf("\n[Stream Information]\n\n")

    mov rsi,streamInfo
    .repeat
        wprintf("  Stream Name: %S\n", [rsi].StreamName)
        wprintf("  Stream Size: %I64d\n", [rsi].StreamSize)
        wprintf("  Stream Allocation Size: %I64d\n", [rsi].StreamAllocationSize)

        .if ([rsi].NextEntryOffset == 0)
            mov rsi,NULL
        .else
            mov eax,[rsi].NextEntryOffset
            add rsi,rax
        .endif
    .until (rsi == NULL)


    LocalFree(streamInfo)
    .return TRUE

DisplayStreamInfo endp

    assume rsi:PFILE_ID_BOTH_DIR_INFO

PrintDirectoryEntry proc uses rsi entry:PFILE_ID_BOTH_DIR_INFO

  local lastChar:WCHAR
  local result:BOOL

    mov rsi,rcx

    ;;
    ;; The names aren't necessarily NULL terminated, so we deal with that here.
    ;;
    mov edx,[rsi].FileNameLength
    mov lastChar,[rsi].FileName[rdx]
    mov [rsi].FileName[rdx],0

    wprintf("\n  %S ", &[rsi].FileName)

    mov edx,[rsi].FileNameLength
    mov [rsi].FileName[rdx],lastChar

    .if ([rsi].ShortName[0] != 0)

        movzx edx,[rsi].ShortNameLength
        mov lastChar,[rsi].ShortName[rdx]
        mov [rsi].ShortName[rdx],0

        wprintf("[%S]\n\n", [rsi].ShortName)
        movzx edx,[rsi].ShortNameLength
        mov [rsi].ShortName[rdx],lastChar
    .else
        wprintf("\n\n")
    .endif

    wprintf("    Creation Time: ")

    mov result,PrintDate([rsi].CreationTime)

    .if (result)
        wprintf("\n")
    .else
        wprintf(" Error retrieving creation time.\n")
    .endif

    wprintf("    Change Time: ")

    mov result,PrintDate([rsi].ChangeTime)

    .if (result)
        wprintf("\n")
    .else
        wprintf(" Error retrieving creation time.\n")
    .endif

    wprintf("    Last Access Time: ")

    mov result,PrintDate([rsi].LastAccessTime)

    .if (result)
        wprintf("\n")
    .else
        wprintf(" Error retrieving last access time.\n")
    .endif

    wprintf("    Last Write Time: ")

    mov result,PrintDate([rsi].LastWriteTime)

    .if (result)
        wprintf("\n")
    .else
        wprintf(" Error retrieving last write time.\n")
    .endif

    wprintf("    End of File: %I64d\n", [rsi].EndOfFile)
    wprintf("    Allocation Size: %I64d\n", [rsi].AllocationSize)
    wprintf("    File Attributes: ")
    PrintFileAttributes([rsi].FileAttributes)
    wprintf("    File ID: %I64d\n", [rsi].FileId)
    ret

PrintDirectoryEntry endp

DisplayFullDirectoryInfo proc uses rsi hFile:HANDLE

  local currentDirInfo:PFILE_ID_BOTH_DIR_INFO
  local dirInfo:PFILE_ID_BOTH_DIR_INFO
  local dirInfoSize:ULONG
  local infoClass:FILE_INFO_BY_HANDLE_CLASS
  local result:BOOL

    ;;
    ;; Allocate an information structure that is hopefully large enough to
    ;; retrieve at least one directory entry.
    ;;

    mov dirInfoSize,sizeof(FILE_ID_BOTH_DIR_INFO) + (sizeof(WCHAR) * MAX_PATH)

    ;;
    ;; We initially want to start our enumeration from the beginning so we
    ;; use the restart class.
    ;;
    mov infoClass,FileIdBothDirectoryRestartInfo

retry:

    mov dirInfo,LocalAlloc(LMEM_ZEROINIT, dirInfoSize)


    .if (dirInfo == NULL)

        SetLastError(ERROR_NOT_ENOUGH_MEMORY)
        .return FALSE
    .endif

    .for (::)

        mov result,GetFileInformationByHandleEx(hFile, infoClass, dirInfo, dirInfoSize)

        .if !eax
            ;;
            ;; If our buffer wasn't large enough try again with a larger one.
            ;;
            .if (GetLastError() == ERROR_MORE_DATA)

                shl dirInfoSize,1
                jmp retry

            .elseif (eax == ERROR_NO_MORE_FILES)
                ;;
                ;; Enumeration completed successfully, we simply break out here.
                ;;
                .break
            .endif

            ;;
            ;; A real error occurred.
            ;;
            wprintf("\nFailure fetching directory information: %d\n", GetLastError())

            LocalFree(dirInfo)
            .return result
        .endif

        .if (infoClass == FileIdBothDirectoryRestartInfo)

            wprintf("\n[Full Directory Information]\n\n")
            mov infoClass,FileIdBothDirectoryInfo
        .endif

        mov rsi,dirInfo

        .repeat
            PrintDirectoryEntry(rsi)
            .if ([rsi].NextEntryOffset == 0)

                mov rsi,NULL
            .else

                mov eax,[rsi].NextEntryOffset
                add rsi,rax
            .endif
        .until (rsi == NULL)

    .endf
    LocalFree(dirInfo)

    .return TRUE

DisplayFullDirectoryInfo endp

wmain proc uses rsi argc:int_t, argv:ptr WCHAR

  local bIsDirectory:BOOL
  local hFile:HANDLE
  local fileId:FILE_ID_DESCRIPTOR

    mov rsi,rdx

    .if ecx < 2

        PrintUsage()
        .return 1
    .endif

    ;;
    ;; Check for flag that indicates we should open by ID
    ;;

    .if CompareStringW(LOCALE_INVARIANT, NORM_IGNORECASE, [rsi+8], -1, "-id", -1) == CSTR_EQUAL

        .new hDir:HANDLE

        .if (argc < 3)

            PrintUsage()
            .return 1
        .endif

        ;;
        ;; Open a handle to the current directory to use as a hint when
        ;; opening the file by ID.
        ;;
        mov hDir,CreateFileW(L".",
               GENERIC_READ,
               FILE_SHARE_READ or FILE_SHARE_WRITE or FILE_SHARE_DELETE,
               NULL,
               OPEN_EXISTING,
               FILE_FLAG_BACKUP_SEMANTICS,
               NULL)

        .if (rax == INVALID_HANDLE_VALUE)

            wprintf("Couldn't open current directory.\n")
            .return 1
        .endif

        ;;
        ;; Capture the file ID and attempt to open by ID.
        ;;

        mov fileId.FileId.QuadPart,_wtoi64([rsi+16])
        mov fileId.Type,FileIdType
        mov fileId.dwSize,sizeof(fileId)

        mov hFile,OpenFileById(hDir,
                 &fileId,
                 GENERIC_READ,
                 FILE_SHARE_READ or FILE_SHARE_WRITE or FILE_SHARE_DELETE,
                 NULL,
                 FILE_FLAG_BACKUP_SEMANTICS)

        CloseHandle(hDir)

        .if (hFile == INVALID_HANDLE_VALUE)

            wprintf("\nError opening file with ID %s.  Last error was %d.\n", [rsi+16], GetLastError())
            .return 1
        .endif

    .else

        mov hFile,CreateFileW([rsi+8],
                GENERIC_READ,
                FILE_SHARE_READ or FILE_SHARE_WRITE or FILE_SHARE_DELETE,
                NULL,
                OPEN_EXISTING,
                FILE_FLAG_BACKUP_SEMANTICS,
                NULL)

        .if (rax == INVALID_HANDLE_VALUE)

            wprintf("\nError opening file %s.  Last error was %d.\n", [rsi+16], GetLastError())
            .return 1
        .endif
    .endif



    ;;
    ;; Display information about the file/directory
    ;;

    .ifd !DisplayBasicInfo(hFile, &bIsDirectory)

        wprintf("\nError displaying basic information.\n")
        .return 1
    .endif

    .ifd !DisplayStandardInfo(hFile)

        wprintf("\nError displaying standard information.\n")
        .return 1
    .endif

    .if !DisplayNameInfo(hFile)

        wprintf("\nError displaying name information.\n")
        .return 1
    .endif

    ;;
    ;; For directories we query for full directory information, which gives us
    ;; various pieces of information about each entry in the directory.
    ;;
    .if (bIsDirectory)

        .if !DisplayFullDirectoryInfo(hFile)

            wprintf("\nError displaying directory information.\n")
            .return 1
        .endif

    .else
        ;;
        ;; Otherwise we query information about the streams associated with the
        ;; file.
        ;;

        .if !DisplayStreamInfo(hFile)

            wprintf("\nError displaying stream information.\n")
            .return 1
        .endif
    .endif

    CloseHandle(hFile)
    .return 0

wmain endp

    end _tstart

