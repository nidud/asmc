;;
;; This sample demonstrates how to get a metadata item from a VHDX file.
;;
;; User metadata is not applicable to VHD files.
;;

include Storage.inc

;;
;; This sample metadata structure is for demonstration purposes only.  Any structure can be used
;; for metadata.
;;

SAMPLE_METADATA struct
    ID DWORD ?
SAMPLE_METADATA ends

.code

SampleGetUserMetaData proc \
    VHDPath: LPCWSTR

    .new openParameters:OPEN_VIRTUAL_DISK_PARAMETERS
    .new storageType:VIRTUAL_STORAGE_TYPE
    .new vhdHandle:HANDLE = NULL
    .new uniqueId:GUID
    .new userMeta:SAMPLE_METADATA
    .new metaDataSize:ULONG = 0
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

    memset(&openParameters, 0, sizeof(openParameters));
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

    mov metaDataSize,sizeof(userMeta)

    ;;
    ;; Use the same GUID specified in SampleSetUserMetaData.  This GUID is arbitrary and any
    ;; GUID can be utilized.
    ;;

    mov uniqueId.Data1,0x34a631f3
    mov uniqueId.Data2,0xa39d
    mov uniqueId.Data3,0x4e45
    mov uniqueId.Data4[0],0xbb
    mov uniqueId.Data4[1],0x2e
    mov uniqueId.Data4[2],0x98
    mov uniqueId.Data4[3],0xcf
    mov uniqueId.Data4[4],0x2d
    mov uniqueId.Data4[5],0xfe
    mov uniqueId.Data4[6],0x4f
    mov uniqueId.Data4[7],0x3d

    mov status,GetVirtualDiskMetadata(
        vhdHandle,
        &uniqueId,
        &metaDataSize,
        &userMeta)

    .if (status != ERROR_SUCCESS)

        .if (status == ERROR_MORE_DATA)

            wprintf(L"Get: more data available\n")
        .else
            jmp Cleanup
        .endif
    .else
        wprintf(L"Get metadata: %d\n", userMeta.ID)
    .endif

Cleanup:

    .if (status == ERROR_SUCCESS)

        wprintf(L"success\n")
    .else
        wprintf(L"error = %u\n", status)
    .endif

    .if (vhdHandle != INVALID_HANDLE_VALUE)

        CloseHandle(vhdHandle)
    .endif

    .return status

SampleGetUserMetaData endp

    end

