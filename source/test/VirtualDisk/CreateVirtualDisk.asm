;;
;; This sample demonstrates how to create VHDs and VHDXs.
;;

include Storage.inc

.code

SampleCreateVirtualDisk proc \
    VirtualDiskPath:    LPCWSTR,
    ParentPath:         LPCWSTR,
    Flags:              CREATE_VIRTUAL_DISK_FLAG,
    FileSize:           ULONGLONG,
    BlockSize:          DWORD,
    LogicalSectorSize:  DWORD,
    PhysicalSectorSize: DWORD

    .new storageType:VIRTUAL_STORAGE_TYPE
    .new parameters:CREATE_VIRTUAL_DISK_PARAMETERS
    .new vhdHandle:HANDLE = INVALID_HANDLE_VALUE
    .new opStatus:DWORD
    .new uniqueId:GUID

    .if (UuidCreate(&uniqueId) != RPC_S_OK)

        mov opStatus,ERROR_NOT_ENOUGH_MEMORY
        jmp Cleanup
    .endif

    ;;
    ;; Specify UNKNOWN for both device and vendor so the system will use the
    ;; file extension to determine the correct VHD format.
    ;;

    mov storageType.DeviceId,VIRTUAL_STORAGE_TYPE_DEVICE_UNKNOWN
    mov storageType.VendorId,VIRTUAL_STORAGE_TYPE_VENDOR_UNKNOWN

    memset(&parameters, 0, sizeof(parameters))

    ;;
    ;; CREATE_VIRTUAL_DISK_VERSION_2 allows specifying a richer set a values and returns
    ;; a V2 handle.
    ;;
    ;; VIRTUAL_DISK_ACCESS_NONE is the only acceptable access mask for V2 handle opens.
    ;;
    ;; Valid BlockSize values are as follows (use 0 to indicate default value):
    ;;      Fixed VHD: 0
    ;;      Dynamic VHD: 512kb, 2mb (default)
    ;;      Differencing VHD: 512kb, 2mb (if parent is fixed, default is 2mb; if parent is dynamic or differencing, default is parent blocksize)
    ;;      Fixed VHDX: 0
    ;;      Dynamic VHDX: 1mb, 2mb, 4mb, 8mb, 16mb, 32mb (default), 64mb, 128mb, 256mb
    ;;      Differencing VHDX: 1mb, 2mb (default), 4mb, 8mb, 16mb, 32mb, 64mb, 128mb, 256mb
    ;;
    ;; Valid LogicalSectorSize values are as follows (use 0 to indicate default value):
    ;;      VHD: 512 (default)
    ;;      VHDX: 512 (for fixed or dynamic, default is 512; for differencing, default is parent logicalsectorsize), 4096
    ;;
    ;; Valid PhysicalSectorSize values are as follows (use 0 to indicate default value):
    ;;      VHD: 512 (default)
    ;;      VHDX: 512, 4096 (for fixed or dynamic, default is 4096; for differencing, default is parent physicalsectorsize)
    ;;
    mov parameters.Version,CREATE_VIRTUAL_DISK_VERSION_2
    mov parameters.Version2.UniqueId,uniqueId
    mov parameters.Version2.MaximumSize,FileSize
    mov parameters.Version2.BlockSizeInBytes,BlockSize
    mov parameters.Version2.SectorSizeInBytes,LogicalSectorSize
    mov parameters.Version2.PhysicalSectorSizeInBytes,PhysicalSectorSize
    mov parameters.Version2.ParentPath,ParentPath

    mov opStatus,CreateVirtualDisk(
        &storageType,
        VirtualDiskPath,
        VIRTUAL_DISK_ACCESS_NONE,
        NULL,
        Flags,
        0,
        &parameters,
        NULL,
        &vhdHandle)

Cleanup:

    .if (opStatus == ERROR_SUCCESS)

        wprintf(L"success\n")
    .else
        wprintf(L"error = %u\n", opStatus);
    .endif

    .if (vhdHandle != INVALID_HANDLE_VALUE)

        CloseHandle(vhdHandle)
    .endif

    .return opStatus

SampleCreateVirtualDisk endp

    end
