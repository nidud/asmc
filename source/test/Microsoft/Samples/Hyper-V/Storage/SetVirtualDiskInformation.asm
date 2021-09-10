;;
;; This sample demonstrates how to set properties of a VHD/VHDX.
;;

include Storage.inc

.code

SampleSetVirtualDiskInformation proc \
    ChildPath: LPCWSTR,
    ParentPath: LPCWSTR,
    PhysicalSectorSize: DWORD

    .new openParameters:OPEN_VIRTUAL_DISK_PARAMETERS
    .new childDiskInfo:GET_VIRTUAL_DISK_INFO
    .new parentDiskInfo:GET_VIRTUAL_DISK_INFO
    .new setInfo:SET_VIRTUAL_DISK_INFO
    .new diskInfoSize:DWORD
    .new storageType:VIRTUAL_STORAGE_TYPE
    .new childVhdHandle:HANDLE = INVALID_HANDLE_VALUE
    .new parentVhdHandle:HANDLE = INVALID_HANDLE_VALUE
    .new opStatus:DWORD

    ;;
    ;; Specify UNKNOWN for both device and vendor so the system will use the
    ;; file extension to determine the correct VHD format.
    ;;

    mov storageType.DeviceId,VIRTUAL_STORAGE_TYPE_DEVICE_UNKNOWN
    mov storageType.VendorId,VIRTUAL_STORAGE_TYPE_VENDOR_UNKNOWN

    ;;
    ;; Open the parent so it's properties can be queried.
    ;;
    ;; A "GetInfoOnly" handle is a handle that can only be used to query properties or
    ;; metadata.
    ;;

    memset(&openParameters, 0, sizeof(openParameters))
    mov openParameters.Version,OPEN_VIRTUAL_DISK_VERSION_2
    mov openParameters.Version2.GetInfoOnly,TRUE

    ;;
    ;; Open the VHD/VHDX.
    ;;
    ;; VIRTUAL_DISK_ACCESS_NONE is the only acceptable access mask for V2 handle opens.
    ;; OPEN_VIRTUAL_DISK_FLAG_NO_PARENTS indicates the parent chain should not be opened.
    ;;

    mov opStatus,OpenVirtualDisk(
        &storageType,
        ParentPath,
        VIRTUAL_DISK_ACCESS_NONE,
        OPEN_VIRTUAL_DISK_FLAG_NO_PARENTS,
        &openParameters,
        &parentVhdHandle)

    .if (opStatus != ERROR_SUCCESS)

        jmp Cleanup
    .endif

    ;;
    ;; Get the disk ID of the parent.
    ;;

    mov diskInfoSize,sizeof(GET_VIRTUAL_DISK_INFO)
    mov parentDiskInfo.Version,GET_VIRTUAL_DISK_INFO_IDENTIFIER

    mov opStatus,GetVirtualDiskInformation(
        parentVhdHandle,
        &diskInfoSize,
        &parentDiskInfo,
        NULL)

    .if (opStatus != ERROR_SUCCESS)

        jmp Cleanup
    .endif

    ;;
    ;; Open the VHD/VHDX so it's properties can be queried.
    ;;
    ;; VIRTUAL_DISK_ACCESS_NONE is the only acceptable access mask for V2 handle opens.
    ;; OPEN_VIRTUAL_DISK_FLAG_NO_PARENTS indicates the parent chain should not be opened.
    ;;

    mov opStatus,OpenVirtualDisk(
        &storageType,
        ChildPath,
        VIRTUAL_DISK_ACCESS_NONE,
        OPEN_VIRTUAL_DISK_FLAG_NO_PARENTS,
        &openParameters,
        &childVhdHandle)

    .if (opStatus != ERROR_SUCCESS)

        jmp Cleanup
    .endif

    ;;
    ;; Get the disk ID expected for the parent.
    ;;

    mov childDiskInfo.Version,GET_VIRTUAL_DISK_INFO_PARENT_IDENTIFIER
    mov diskInfoSize,sizeof(childDiskInfo)

    mov opStatus,GetVirtualDiskInformation(
        childVhdHandle,
        &diskInfoSize,
        &childDiskInfo,
        NULL)

    .if (opStatus != ERROR_SUCCESS)

        jmp Cleanup
    .endif

    ;;
    ;; Verify the disk IDs match.
    ;;

    .if (memcmp(&parentDiskInfo.Identifier,
               &childDiskInfo.ParentIdentifier,
               sizeof(GUID)))

        mov opStatus,ERROR_INVALID_PARAMETER
        jmp Cleanup
    .endif

    ;;
    ;; Reset the parent locators in the child.
    ;;

    CloseHandle(childVhdHandle)
    mov childVhdHandle,INVALID_HANDLE_VALUE

    ;;
    ;; This cannot be a "GetInfoOnly" handle because the intent is to alter the properties of the
    ;; VHD/VHDX.
    ;;
    ;; VIRTUAL_DISK_ACCESS_NONE is the only acceptable access mask for V2 handle opens.
    ;; OPEN_VIRTUAL_DISK_FLAG_NO_PARENTS indicates the parent chain should not be opened.
    ;;

    mov openParameters.Version2.GetInfoOnly,FALSE

    mov opStatus,OpenVirtualDisk(
        &storageType,
        ChildPath,
        VIRTUAL_DISK_ACCESS_NONE,
        OPEN_VIRTUAL_DISK_FLAG_NO_PARENTS,
        &openParameters,
        &childVhdHandle)

    .if (opStatus != ERROR_SUCCESS)

        jmp Cleanup
    .endif

    ;;
    ;; Update the path to the parent.
    ;;

    mov setInfo.Version,SET_VIRTUAL_DISK_INFO_PARENT_PATH_WITH_DEPTH
    mov setInfo.ParentPathWithDepthInfo.ChildDepth,1
    mov setInfo.ParentPathWithDepthInfo.ParentFilePath,ParentPath

    mov opStatus,SetVirtualDiskInformation(childVhdHandle, &setInfo)

    .if (opStatus != ERROR_SUCCESS)

        jmp Cleanup
    .endif

    ;;
    ;; Set the physical sector size.
    ;;
    ;; This operation will only succeed on VHDX.
    ;;

    mov setInfo.Version,SET_VIRTUAL_DISK_INFO_PHYSICAL_SECTOR_SIZE
    mov setInfo.VhdPhysicalSectorSize,PhysicalSectorSize

    mov opStatus,SetVirtualDiskInformation(childVhdHandle, &setInfo)

Cleanup:

    .if (opStatus == ERROR_SUCCESS)

        wprintf(L"success\n")
    .else
        wprintf(L"error = %u\n", opStatus)
    .endif

    .if (childVhdHandle != INVALID_HANDLE_VALUE)

        CloseHandle(childVhdHandle)
    .endif

    .if (parentVhdHandle != INVALID_HANDLE_VALUE)

        CloseHandle(parentVhdHandle)
    .endif

    .return opStatus

SampleSetVirtualDiskInformation endp

    end
