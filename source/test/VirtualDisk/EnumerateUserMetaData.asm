;;
;; This sample shows how to enumberate the available metadata items of a VHDX file.
;;
;; User metadata is not applicable to VHD files.
;;

include Storage.inc

.code

SampleEnumerateUserMetaData proc \
    VHDPath: LPCWSTR

    .new openParameters:OPEN_VIRTUAL_DISK_PARAMETERS
    .new storageType:VIRTUAL_STORAGE_TYPE
    .new vhdHandle:HANDLE = NULL
    .new numberOfItems:ULONG = 0
    .new items:ptr GUID = NULL
    .new status:DWORD = ERROR_SUCCESS

    .if (VHDPath == NULL)

        mov status,ERROR_INVALID_PARAMETER
        jmp Cleanup
    .endif

    ;;
    ;; Specify UNKNOWN for both device and vendor so the system will use the
    ;; file extension to determine the correct VHD format.
    ;;

    mov storageType.DeviceId,VIRTUAL_STORAGE_TYPE_DEVICE_UNKNOWN
    mov storageType.VendorId,VIRTUAL_STORAGE_TYPE_VENDOR_UNKNOWN

    ;;
    ;; Only V2 handles can be used to query/set/delete user metadata.
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

    mov status,OpenVirtualDisk(
        &storageType,
        VHDPath,
        VIRTUAL_DISK_ACCESS_NONE,
        OPEN_VIRTUAL_DISK_FLAG_NO_PARENTS,
        &openParameters,
        &vhdHandle)

    .if (status != ERROR_SUCCESS)

        jmp Cleanup
    .endif

    mov numberOfItems,0

    ;;
    ;; EnumerateVirtualDiskMetadata returns the number of user metadata items in the VHDX.
    ;;
    ;; NULL can be specified for the third parameter when trying to determine the number
    ;; of items to expect.
    ;;

    mov status,EnumerateVirtualDiskMetadata(vhdHandle, &numberOfItems, NULL)
    .if (status != ERROR_SUCCESS)

        .if (status == ERROR_MORE_DATA)

            wprintf(L"Enumerate: more data available\n")

        .else

            jmp Cleanup
        .endif
    .endif

    wprintf(L"%d user defined metadata items are available\n", numberOfItems)

    ;;
    ;; Each user metadata item is specified by a unique GUID.
    ;;
    imul ecx,numberOfItems,sizeof(GUID)
    mov items,malloc( ecx )
    .if (items == NULL)

        mov status,ERROR_OUTOFMEMORY
        jmp Cleanup
    .endif

    mov status,EnumerateVirtualDiskMetadata(vhdHandle, &numberOfItems, items)

Cleanup:

    .if (status == ERROR_SUCCESS)

        wprintf(L"success\n")
    .else
        wprintf(L"error = %u\n", status)
    .endif

    .if (items != NULL)

        free(items)
    .endif

    .if (vhdHandle != INVALID_HANDLE_VALUE)

        CloseHandle(vhdHandle)
    .endif

    .return status

SampleEnumerateUserMetaData endp

    end
