;;
;; This sample demonstrates how query storage dependency information.
;;

include Storage.inc

.code

SampleGetStorageDependencyInformation proc uses rsi rdi rbx Disk:LPCWSTR

    .new pInfo:PSTORAGE_DEPENDENCY_INFO
    .new infoSize:DWORD
    .new cbSize:DWORD
    .new driveHandle:HANDLE
    .new flags:GET_STORAGE_DEPENDENCY_FLAG
    .new isDisk:BOOL
    .new opStatus:DWORD
    .new entry:DWORD
    .new szVolume[8]:TCHAR
    .new szDisk[19]:TCHAR

    wcscpy(&szVolume, L"\\\\.\\C:\\")
    wcscpy(&szDisk, L"\\\\.\\PhysicalDrive0")

    mov rbx,Disk
    mov ax,[rbx]
    .if (ax >= '0' && ax <= '9')

        ;;
        ;; Assume the user is specifying a disk between 0 and 9
        ;;

        mov isDisk,TRUE
        mov szDisk[17*TCHAR],ax
        mov flags,GET_STORAGE_DEPENDENCY_FLAG_PARENTS or GET_STORAGE_DEPENDENCY_FLAG_DISK_HANDLE

    .else

        ;;
        ;; Assume the user is specifying a drive letter between A: and Z:
        ;;

        mov isDisk,FALSE
        mov szVolume[4*TCHAR],ax
        mov flags,GET_STORAGE_DEPENDENCY_FLAG_PARENTS
    .endif

    mov driveHandle,INVALID_HANDLE_VALUE
    mov pInfo,NULL

    ;;
    ;; Allocate enough memory for most basic case.
    ;;

    mov infoSize,sizeof(STORAGE_DEPENDENCY_INFO)

    mov pInfo,malloc(infoSize)
    .if (pInfo == NULL)

        mov opStatus,ERROR_NOT_ENOUGH_MEMORY
        jmp Cleanup
    .endif

    memset(pInfo, 0, infoSize)

    ;;
    ;; Open the drive
    ;;
    lea rcx,szVolume
    .if isDisk
        lea rcx,szDisk
    .endif
    mov driveHandle,CreateFile(
        rcx,
        GENERIC_READ,
        FILE_SHARE_READ or FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL or FILE_FLAG_BACKUP_SEMANTICS,
        NULL)

    .if (driveHandle == INVALID_HANDLE_VALUE)

        mov opStatus,GetLastError()
        jmp Cleanup
    .endif

    ;;
    ;; Deteremine the size actually required.
    ;;
    mov rsi,pInfo
    assume rsi:PSTORAGE_DEPENDENCY_INFO

    mov [rsi].Version,STORAGE_DEPENDENCY_INFO_VERSION_2
    mov cbSize,0

    mov opStatus,GetStorageDependencyInformation(
        driveHandle,
        flags,
        infoSize,
        pInfo,
        &cbSize);

    .if (opStatus == ERROR_INSUFFICIENT_BUFFER)

        ;;
        ;; Allocate a large enough buffer.
        ;;

        free(pInfo);

        mov infoSize,cbSize

        mov pInfo,malloc(infoSize)
        .if (pInfo == NULL)

            mov opStatus,ERROR_NOT_ENOUGH_MEMORY
            jmp Cleanup
        .endif

        mov rsi,memset(pInfo, 0, infoSize)

        ;;
        ;; Retry with large enough buffer.
        ;;

        mov [rsi].Version,STORAGE_DEPENDENCY_INFO_VERSION_2
        mov cbSize,0

        mov opStatus,GetStorageDependencyInformation(
            driveHandle,
            GET_STORAGE_DEPENDENCY_FLAG_PARENTS,
            infoSize,
            pInfo,
            &cbSize)
    .endif

    .if (opStatus != ERROR_SUCCESS)

        ;;
        ;; This is most likely due to the disk not being a mounted VHD.
        ;;

        jmp Cleanup
    .endif

    ;;
    ;; Display the relationship between the specified volume and the underlying disks.
    ;;

    .for (entry = 0: entry < [rsi].NumberEntries: entry++)

        wprintf(L"%u:\n", entry)
        imul ebx,entry,STORAGE_DEPENDENCY_INFO_TYPE_2
        wprintf(L"   %u\n", [rsi].Version2Entries[rbx].AncestorLevel)
        wprintf(L"   %s\n", [rsi].Version2Entries[rbx].DependencyDeviceName)
        wprintf(L"   %s\n", [rsi].Version2Entries[rbx].HostVolumeName)
        wprintf(L"   %s\n", [rsi].Version2Entries[rbx].DependentVolumeName)
        wprintf(L"   %s\n", [rsi].Version2Entries[rbx].DependentVolumeRelativePath)
    .endf

Cleanup:

    .if (opStatus == ERROR_SUCCESS)

        wprintf(L"success\n")
    .else
        wprintf(L"error = %u\n", opStatus)
    .endif

    .if (driveHandle != INVALID_HANDLE_VALUE)

        CloseHandle(driveHandle)
    .endif

    .if (pInfo != NULL)

        free(pInfo)
    .endif

    .return opStatus

SampleGetStorageDependencyInformation endp

    end
