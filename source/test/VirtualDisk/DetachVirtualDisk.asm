;;
;; This sample demonstrates how to unmount a VHD or ISO file.
;;

include Storage.inc

.code

SampleDetachVirtualDisk proc \
    VirtualDiskPath: LPCWSTR

    .new storageType:VIRTUAL_STORAGE_TYPE
    .new openParameters:OPEN_VIRTUAL_DISK_PARAMETERS
    .new accessMask:VIRTUAL_DISK_ACCESS_MASK
    .new extension:LPCTSTR
    .new vhdHandle:HANDLE = INVALID_HANDLE_VALUE
    .new opStatus:DWORD

    ;;
    ;; Specify UNKNOWN for both device and vendor so the system will use the
    ;; file extension to determine the correct VHD format.
    ;;

    mov storageType.DeviceId,VIRTUAL_STORAGE_TYPE_DEVICE_UNKNOWN
    mov storageType.VendorId,VIRTUAL_STORAGE_TYPE_VENDOR_UNKNOWN

    memset(&openParameters, 0, sizeof(openParameters));

    mov extension,PathFindExtension(VirtualDiskPath)

    .if (extension != NULL && _wcsicmp(extension, L".iso") == 0)

        ;;
        ;; ISO files can only be opened using the V1 API.
        ;;

        mov openParameters.Version,OPEN_VIRTUAL_DISK_VERSION_1
        mov accessMask,VIRTUAL_DISK_ACCESS_READ

    .else

        ;;
        ;; VIRTUAL_DISK_ACCESS_NONE is the only acceptable access mask for V2 handle opens.
        ;; OPEN_VIRTUAL_DISK_FLAG_NONE bypasses any special handling of the open.
        ;;

        mov openParameters.Version,OPEN_VIRTUAL_DISK_VERSION_2
        mov openParameters.Version2.GetInfoOnly,FALSE
        mov accessMask,VIRTUAL_DISK_ACCESS_NONE
    .endif

    ;;
    ;; Open the VHD/VHDX or ISO.
    ;;
    ;;

    mov opStatus,OpenVirtualDisk(
        &storageType,
        VirtualDiskPath,
        accessMask,
        OPEN_VIRTUAL_DISK_FLAG_NONE,
        &openParameters,
        &vhdHandle);

    .if (opStatus != ERROR_SUCCESS)

        jmp Cleanup
    .endif

    ;;
    ;; Detach the VHD/VHDX/ISO.
    ;;
    ;; DETACH_VIRTUAL_DISK_FLAG_NONE is the only flag currently supported for detach.
    ;;

    mov opStatus,DetachVirtualDisk(
        vhdHandle,
        DETACH_VIRTUAL_DISK_FLAG_NONE,
        0)

Cleanup:

    .if (opStatus == ERROR_SUCCESS)

        wprintf(L"success\n");
    .else
        wprintf(L"error = %u\n", opStatus);
    .endif

    .if (vhdHandle != INVALID_HANDLE_VALUE)

        CloseHandle(vhdHandle);
    .endif

    .return opStatus

SampleDetachVirtualDisk endp

    end
