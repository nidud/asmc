;;
;; This sample demonstrates how to resize (shrink or expand) a VHD/VHDX.
;;
;; The VHD/VHDX can not be in use while performing this operation.
;;

include Storage.inc

.code

SampleResizeVirtualDisk proc \
    VirtualDiskPath: LPCWSTR,
    FileSize: ULONGLONG

    .new openParameters:OPEN_VIRTUAL_DISK_PARAMETERS
    .new resizeParameters:RESIZE_VIRTUAL_DISK_PARAMETERS
    .new storageType:VIRTUAL_STORAGE_TYPE
    .new vhdHandle:HANDLE = INVALID_HANDLE_VALUE
    .new opStatus:DWORD

    ;;
    ;; Specify UNKNOWN for both device and vendor so the system will use the
    ;; file extension to determine the correct VHD format.
    ;;

    mov storageType.DeviceId,VIRTUAL_STORAGE_TYPE_DEVICE_UNKNOWN
    mov storageType.VendorId,VIRTUAL_STORAGE_TYPE_VENDOR_UNKNOWN

    ;;
    ;; Open the VHD/VHDX.
    ;;
    ;; Only V2 handles can be used to resize a VHD/VHDX.
    ;;
    ;; VIRTUAL_DISK_ACCESS_NONE is the only acceptable access mask for V2 handle opens.
    ;; OPEN_VIRTUAL_DISK_FLAG_NONE bypasses any special handling of the open.
    ;;

    memset(&openParameters, 0, sizeof(openParameters))
    mov openParameters.Version,OPEN_VIRTUAL_DISK_VERSION_2

    mov opStatus,OpenVirtualDisk(
        &storageType,
        VirtualDiskPath,
        VIRTUAL_DISK_ACCESS_NONE,
        OPEN_VIRTUAL_DISK_FLAG_NONE,
        &openParameters,
        &vhdHandle)

    .if (opStatus != ERROR_SUCCESS)

        jmp Cleanup
    .endif

    ;;
    ;; Perform the resize (shrink or expand).
    ;;
    ;; RESIZE_VIRTUAL_DISK_VERSION_1 is the only version of the parameters currently supported.
    ;; RESIZE_VIRTUAL_DISK_FLAG_NONE prevents unsafe shrink where the new virtual disk size cannot
    ;; be less than the "SmallestSafeVirtualSize" reported through the GetVirtualDiskInformation API
    ;; with a "VirtualDiskInfo" of GET_VIRTUAL_DISK_INFO_SMALLEST_SAFE_VIRTUAL_SIZE.
    ;;

    memset(&resizeParameters, 0, sizeof(resizeParameters))
    mov resizeParameters.Version,RESIZE_VIRTUAL_DISK_VERSION_1
    mov resizeParameters.Version1.NewSize,FileSize

    mov opStatus,ResizeVirtualDisk(
        vhdHandle,
        RESIZE_VIRTUAL_DISK_FLAG_NONE,
        &resizeParameters,
        NULL)

Cleanup:

    .if (opStatus == ERROR_SUCCESS)

        wprintf(L"success\n")
    .else
        wprintf(L"error = %u\n", opStatus)
    .endif

    .if (vhdHandle != INVALID_HANDLE_VALUE)

        CloseHandle(vhdHandle)
    .endif

    .return opStatus

SampleResizeVirtualDisk endp

    end
