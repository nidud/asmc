;;
;; This sample demonstrates how to merge a differencing disk into its parent.
;;

include Storage.inc

.code

SampleMergeVirtualDisk proc \
    LeafPath: LPCWSTR

    .new openParameters:OPEN_VIRTUAL_DISK_PARAMETERS
    .new mergeParameters:MERGE_VIRTUAL_DISK_PARAMETERS
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

    memset(&openParameters, 0, sizeof(openParameters))
    mov openParameters.Version,OPEN_VIRTUAL_DISK_VERSION_2

    mov opStatus,OpenVirtualDisk(
        &storageType,
        LeafPath,
        VIRTUAL_DISK_ACCESS_NONE,
        OPEN_VIRTUAL_DISK_FLAG_NONE,
        &openParameters,
        &vhdHandle)

    .if (opStatus != ERROR_SUCCESS)

        jmp Cleanup
    .endif

    ;;
    ;; Perform the merge.
    ;;
    ;; MERGE_VIRTUAL_DISK_VERSION_2 allows merging of VHDs/VHDXs in use.
    ;; MERGE_VIRTUAL_DISK_FLAG_NONE is currently the only merge flag supported.
    ;;
    ;; DO NOT attempt to perform a live merge of a leaf (a)VHD or (a)VHDX of a VM as the
    ;; operation will not update the virtual machine configuration file.
    ;;

    memset(&mergeParameters, 0, sizeof(mergeParameters))
    mov mergeParameters.Version,MERGE_VIRTUAL_DISK_VERSION_2

    ;; In this sample, the leaf is being merged so the source depth is 1.
    mov mergeParameters.Version2.MergeSourceDepth,1

    ;; In this sample, the leaf is being merged only to it's parent so the target depth is 2
    mov mergeParameters.Version2.MergeTargetDepth,2

    mov opStatus,MergeVirtualDisk(
        vhdHandle,
        MERGE_VIRTUAL_DISK_FLAG_NONE,
        &mergeParameters,
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

SampleMergeVirtualDisk endp

    end
