;;
;; This sample demonstrates how to use the CompactVirtualDisk API to compact a VHD.
;;
;; To obtain the full benefit of compaction, the VHD should be mounted prior to and throughout
;; the compaction.
;;
;; Mounting a VHD is demonstrated in the AttachVirtualDisk sample.
;;
;; The VHD can only be mounted read-only during a compaction.
;;

include Storage.inc

.code


SampleCompactVirtualDisk proc \
    VirtualDiskPath: LPCWSTR

    .new openParameters:OPEN_VIRTUAL_DISK_PARAMETERS
    .new compactParmaters:COMPACT_VIRTUAL_DISK_PARAMETERS
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
    ;; Open the VHD.
    ;;
    ;; VIRTUAL_DISK_ACCESS_NONE is the only acceptable access mask for V2 handle opens.
    ;; OPEN_VIRTUAL_DISK_FLAG_NONE bypasses any special handling of the open.
    ;;

    memset(&openParameters, 0, sizeof(openParameters));
    mov openParameters.Version,OPEN_VIRTUAL_DISK_VERSION_2

    mov opStatus,OpenVirtualDisk(
        &storageType,
        VirtualDiskPath,
        VIRTUAL_DISK_ACCESS_NONE,
        OPEN_VIRTUAL_DISK_FLAG_NONE,
        &openParameters,
        &vhdHandle);

    .if (opStatus != ERROR_SUCCESS)

        jmp Cleanup
    .endif

    ;;
    ;; Perform the compaction.
    ;;
    ;; COMPACT_VIRTUAL_DISK_VERSION_1 is on the version currently supported.
    ;; COMPACT_VIRTUAL_DISK_FLAG_NONE specifies a full compaction, which only really full if
    ;; the VHD/VHDX has previously been mounted.
    ;;

    memset(&compactParmaters, 0, sizeof(compactParmaters));
    mov compactParmaters.Version,COMPACT_VIRTUAL_DISK_VERSION_1

    mov opStatus,CompactVirtualDisk(
        vhdHandle,
        COMPACT_VIRTUAL_DISK_FLAG_NONE,
        &compactParmaters,
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

    .return opStatus;

SampleCompactVirtualDisk endp

    end

