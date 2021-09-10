
include Storage.inc

.code

SampleGetVirtualDiskInformation proc uses rsi rdi rbx \
    VirtualDiskPath: LPCWSTR

    .new openParameters:OPEN_VIRTUAL_DISK_PARAMETERS
    .new storageType:VIRTUAL_STORAGE_TYPE
    .new diskInfo:PGET_VIRTUAL_DISK_INFO = NULL
    .new diskInfoSize:ULONG = sizeof(GET_VIRTUAL_DISK_INFO)
    .new opStatus:DWORD

    .new vhdHandle:HANDLE = INVALID_HANDLE_VALUE

    .new driveType:UINT32
    .new driveFormat:UINT32

    .new identifier:GUID

    .new physicalSize:ULONGLONG
    .new virtualSize:ULONGLONG
    .new minInternalSize:ULONGLONG
    .new blockSize:ULONG
    .new sectorSize:ULONG
    .new physicalSectorSize:ULONG
    .new parentPath:LPCWSTR
    .new parentPathSize:size_t
    .new parentPathSizeRemaining:size_t
    .new stringLengthResult:HRESULT
    .new parentIdentifier:GUID
    .new fragmentationPercentage:ULONGLONG

    mov diskInfo,malloc(diskInfoSize)
    .if (diskInfo == NULL)

        mov opStatus,ERROR_NOT_ENOUGH_MEMORY
        jmp Cleanup
    .endif

    ;;
    ;; Specify UNKNOWN for both device and vendor so the system will use the
    ;; file extension to determine the correct VHD format.
    ;;

    mov storageType.DeviceId,VIRTUAL_STORAGE_TYPE_DEVICE_UNKNOWN
    mov storageType.VendorId,VIRTUAL_STORAGE_TYPE_VENDOR_UNKNOWN

    ;;
    ;; Open the VHD for query access.
    ;;
    ;; A "GetInfoOnly" handle is a handle that can only be used to query properties or
    ;; metadata.
    ;;
    ;; VIRTUAL_DISK_ACCESS_NONE is the only acceptable access mask for V2 handle opens.
    ;; OPEN_VIRTUAL_DISK_FLAG_NO_PARENTS indicates the parent chain should not be opened.
    ;;

    memset(&openParameters, 0, sizeof(openParameters))
    mov openParameters.Version,OPEN_VIRTUAL_DISK_VERSION_2
    mov openParameters.Version2.GetInfoOnly,TRUE

    mov opStatus,OpenVirtualDisk(
        &storageType,
        VirtualDiskPath,
        VIRTUAL_DISK_ACCESS_NONE,
        OPEN_VIRTUAL_DISK_FLAG_NO_PARENTS,
        &openParameters,
        &vhdHandle)

    .if (opStatus != ERROR_SUCCESS)

        jmp Cleanup
    .endif

    ;;
    ;; Get the VHD/VHDX type.
    ;;

    assume rsi:PGET_VIRTUAL_DISK_INFO
    mov rsi,diskInfo

    mov [rsi].Version,GET_VIRTUAL_DISK_INFO_PROVIDER_SUBTYPE

    mov opStatus,GetVirtualDiskInformation(
        vhdHandle,
        &diskInfoSize,
        diskInfo,
        NULL)

    .if (opStatus != ERROR_SUCCESS)

        jmp Cleanup
    .endif

    mov driveType,[rsi].ProviderSubtype

    wprintf(L"driveType = %d", driveType)

    .if (driveType == 2)

        wprintf(L" (fixed)\n")

    .elseif (driveType == 3)

        wprintf(L" (dynamic)\n")

    .elseif (driveType == 4)

        wprintf(L" (differencing)\n")

    .else

        wprintf(L"\n")
    .endif

    ;;
    ;; Get the VHD/VHDX format.
    ;;

    mov [rsi].Version,GET_VIRTUAL_DISK_INFO_VIRTUAL_STORAGE_TYPE

    mov opStatus,GetVirtualDiskInformation(
        vhdHandle,
        &diskInfoSize,
        diskInfo,
        NULL)

    .if (opStatus != ERROR_SUCCESS)

        jmp Cleanup
    .endif

    mov driveFormat,[rsi].VirtualStorageType.DeviceId

    wprintf(L"driveFormat = %d", driveFormat)

    .if (driveFormat == VIRTUAL_STORAGE_TYPE_DEVICE_VHD)

        wprintf(L" (vhd)\n")

    .elseif (driveFormat == VIRTUAL_STORAGE_TYPE_DEVICE_VHDX)

        wprintf(L" (vhdx)\n")

    .else

        wprintf(L"\n")
    .endif

    ;;
    ;; Get the VHD/VHDX virtual disk size.
    ;;

    mov [rsi].Version,GET_VIRTUAL_DISK_INFO_SIZE

    mov opStatus,GetVirtualDiskInformation(
        vhdHandle,
        &diskInfoSize,
        diskInfo,
        NULL)

    .if (opStatus != ERROR_SUCCESS)

        jmp Cleanup
    .endif

    mov physicalSize,   [rsi].Size.PhysicalSize
    mov virtualSize,    [rsi].Size.VirtualSize
    mov sectorSize,     [rsi].Size.SectorSize
    mov blockSize,      [rsi].Size.BlockSize

    wprintf(L"physicalSize = %I64u\n", physicalSize)
    wprintf(L"virtualSize = %I64u\n", virtualSize)
    wprintf(L"sectorSize = %u\n", sectorSize)
    wprintf(L"blockSize = %u\n", blockSize)

    ;;
    ;; Get the VHD physical sector size.
    ;;

    mov [rsi].Version,GET_VIRTUAL_DISK_INFO_VHD_PHYSICAL_SECTOR_SIZE

    mov opStatus,GetVirtualDiskInformation(
        vhdHandle,
        &diskInfoSize,
        diskInfo,
        NULL)

    .if (opStatus != ERROR_SUCCESS)

        jmp Cleanup
    .endif

    mov physicalSectorSize,[rsi].VhdPhysicalSectorSize

    wprintf(L"physicalSectorSize = %u\n", physicalSectorSize)

    ;;
    ;; Get the virtual disk ID.
    ;;

    mov [rsi].Version,GET_VIRTUAL_DISK_INFO_IDENTIFIER

    mov opStatus,GetVirtualDiskInformation(
        vhdHandle,
        &diskInfoSize,
        diskInfo,
        NULL)

    .if (opStatus != ERROR_SUCCESS)

        jmp Cleanup
    .endif

    mov identifier,[rsi].Identifier

    wprintf(L"identifier = {%08X-%04X-%04X-%02X%02X%02X%02X%02X%02X%02X%02X}\n",
        identifier.Data1, identifier.Data2, identifier.Data3,
        identifier.Data4[0], identifier.Data4[1], identifier.Data4[2], identifier.Data4[3],
        identifier.Data4[4], identifier.Data4[5], identifier.Data4[6], identifier.Data4[7])

    ;;
    ;; Get the VHD parent path.
    ;;

    .if (driveType == 0x4)

        mov [rsi].Version,GET_VIRTUAL_DISK_INFO_PARENT_LOCATION

        mov opStatus,GetVirtualDiskInformation(
            vhdHandle,
            &diskInfoSize,
            diskInfo,
            NULL)

        .if (opStatus != ERROR_SUCCESS)

            .if (opStatus != ERROR_INSUFFICIENT_BUFFER)

                jmp Cleanup
            .endif

            free(diskInfo)

            mov diskInfo,malloc(diskInfoSize)
            .if (diskInfo == NULL)

                mov opStatus,ERROR_NOT_ENOUGH_MEMORY
                jmp Cleanup
            .endif
            mov rsi,diskInfo

            mov [rsi].Version,GET_VIRTUAL_DISK_INFO_PARENT_LOCATION

            mov opStatus,GetVirtualDiskInformation(
                vhdHandle,
                &diskInfoSize,
                diskInfo,
                NULL)

            .if (opStatus != ERROR_SUCCESS)

                jmp Cleanup
            .endif
        .endif

        mov parentPath,[rsi].ParentLocation.ParentLocationBuffer
        mov eax,diskInfoSize
        sub eax,FIELD_OFFSET(GET_VIRTUAL_DISK_INFO, ParentLocation.ParentLocationBuffer)
        mov parentPathSizeRemaining,rax

        .if ([rsi].ParentLocation.ParentResolved)

            wprintf(L"parentPath = '%s'\n", parentPath)

        .else

            ;;
            ;; If the parent is not resolved, the buffer is a MULTI_SZ
            ;;

            wprintf(L"parentPath:\n")

            .while ((parentPathSizeRemaining >= sizeof(TCHAR)) );&& (*parentPath != 0))

                ;mov stringLengthResult,StringCbLengthW(
                ;    parentPath,
                ;    parentPathSizeRemaining,
                ;    &parentPathSize)

                .if (FAILED(stringLengthResult))

                    jmp Cleanup
                .endif

                wprintf(L"    '%s'\n", parentPath)

                ;add parentPathSize,sizeof(parentPath[0])
                ;mov parentPath,parentPath + (parentPathSize / sizeof(parentPath[0]))
                ;sub parentPathSizeRemaining,parentPathSize
            .endw
        .endif

        ;;
        ;; Get parent ID.
        ;;

        mov [rsi].Version,GET_VIRTUAL_DISK_INFO_PARENT_IDENTIFIER

        mov opStatus,GetVirtualDiskInformation(
            vhdHandle,
            &diskInfoSize,
            diskInfo,
            NULL)

        .if (opStatus != ERROR_SUCCESS)

            jmp Cleanup
        .endif

        mov parentIdentifier,[rsi].ParentIdentifier

        wprintf(L"parentIdentifier = {%08X-%04X-%04X-%02X%02X%02X%02X%02X%02X%02X%02X}\n",
            parentIdentifier.Data1, parentIdentifier.Data2, parentIdentifier.Data3,
            parentIdentifier.Data4[0], parentIdentifier.Data4[1],
            parentIdentifier.Data4[2], parentIdentifier.Data4[3],
            parentIdentifier.Data4[4], parentIdentifier.Data4[5],
            parentIdentifier.Data4[6], parentIdentifier.Data4[7])
    .endif

    ;;
    ;; Get the VHD minimum internal size.
    ;;

    mov [rsi].Version,GET_VIRTUAL_DISK_INFO_SMALLEST_SAFE_VIRTUAL_SIZE

    mov opStatus,GetVirtualDiskInformation(
        vhdHandle,
        &diskInfoSize,
        diskInfo,
        NULL)

    .if (opStatus == ERROR_SUCCESS)

        mov minInternalSize,[rsi].SmallestSafeVirtualSize

        wprintf(L"minInternalSize = %I64u\n", minInternalSize)
    .else
        mov opStatus,ERROR_SUCCESS
    .endif

    ;;
    ;; Get the VHD fragmentation percentage.
    ;;

    mov [rsi].Version,GET_VIRTUAL_DISK_INFO_FRAGMENTATION

    mov opStatus,GetVirtualDiskInformation(
        vhdHandle,
        &diskInfoSize,
        diskInfo,
        NULL)

    .if (opStatus == ERROR_SUCCESS)

        wprintf(L"fragmentationPercentage = %u\n", [rsi].FragmentationPercentage)
    .else
        mov opStatus,ERROR_SUCCESS
    .endif

Cleanup:

    .if (opStatus == ERROR_SUCCESS)

        wprintf(L"success\n")

    .else

        wprintf(L"error = %u\n", opStatus)
    .endif

    .if (vhdHandle != INVALID_HANDLE_VALUE)

        CloseHandle(vhdHandle)
    .endif

    .if (diskInfo != NULL)

        free(diskInfo)
    .endif

    .return opStatus

SampleGetVirtualDiskInformation endp

    end

