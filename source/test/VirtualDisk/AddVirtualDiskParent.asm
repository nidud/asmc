;;
;; This sample demonstrates how to use the AddVirtualDiskParent API to build a diff chain by
;; explicitly setting the parent after opening the child.
;;

include Storage.inc

.code

SampleAddVirtualDiskParent proc \
    VirtualDiskPath: LPCWSTR,
    ParentPath: LPCWSTR

    .new openParameters:OPEN_VIRTUAL_DISK_PARAMETERS
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
    ;; The AddVirtualDiskParent requires a V2 handle open.
    ;;
    ;; The child must be opened read-only prior to calling AddVirtualDiskParent.
    ;;
    ;; VIRTUAL_DISK_ACCESS_NONE is the only acceptable access mask for V2 handle opens.
    ;; OPEN_VIRTUAL_DISK_FLAG_CUSTOM_DIFF_CHAIN must be specified when calling AddVirtualDiskParent.
    ;;

    memset(&openParameters, 0, sizeof(openParameters))
    mov openParameters.Version,OPEN_VIRTUAL_DISK_VERSION_2
    mov openParameters.Version2.ReadOnly,TRUE

    mov opStatus,OpenVirtualDisk(
        &storageType,
        VirtualDiskPath,
        VIRTUAL_DISK_ACCESS_NONE,
        OPEN_VIRTUAL_DISK_FLAG_CUSTOM_DIFF_CHAIN,
        &openParameters,
        &vhdHandle)

    .if (opStatus == ERROR_SUCCESS)

        mov opStatus,AddVirtualDiskParent(vhdHandle, ParentPath)
    .endif

    .if (opStatus == ERROR_SUCCESS)

        wprintf(L"success\n")
    .else
        wprintf(L"error = %u\n", opStatus)
    .endif

    .if (vhdHandle != INVALID_HANDLE_VALUE)

        CloseHandle(vhdHandle)
    .endif

    .return opStatus

SampleAddVirtualDiskParent endp

    end
