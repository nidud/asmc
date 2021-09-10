;;
;; This sample demonstrates how to mount a VHD or ISO file.
;;

include Storage.inc

.code

SampleAttachVirtualDisk proc \
    VirtualDiskPath: LPCWSTR,
    ReadOnly: BOOLEAN

    .new openParameters:OPEN_VIRTUAL_DISK_PARAMETERS
    .new accessMask:VIRTUAL_DISK_ACCESS_MASK
    .new attachParameters:ATTACH_VIRTUAL_DISK_PARAMETERS
    .new sd:PSECURITY_DESCRIPTOR = NULL
    .new storageType:VIRTUAL_STORAGE_TYPE
    .new extension:LPCTSTR
    .new vhdHandle:HANDLE = INVALID_HANDLE_VALUE
    .new attachFlags:ATTACH_VIRTUAL_DISK_FLAG
    .new opStatus:DWORD

    ;;
    ;; Specify UNKNOWN for both device and vendor so the system will use the
    ;; file extension to determine the correct VHD format.
    ;;

    mov storageType.DeviceId,VIRTUAL_STORAGE_TYPE_DEVICE_UNKNOWN
    mov storageType.VendorId,VIRTUAL_STORAGE_TYPE_VENDOR_UNKNOWN

    memset(&openParameters, 0, sizeof(openParameters))

    mov extension,PathFindExtension(VirtualDiskPath)

    .if (extension != NULL && _wcsicmp(extension, L".iso") == 0)

        ;;
        ;; ISO files can only be mounted read-only and using the V1 API.
        ;;

        .if (ReadOnly != TRUE)

            mov opStatus,ERROR_NOT_SUPPORTED
            jmp Cleanup
        .endif

        mov openParameters.Version,OPEN_VIRTUAL_DISK_VERSION_1
        mov accessMask,VIRTUAL_DISK_ACCESS_READ

    .else

        ;;
        ;; VIRTUAL_DISK_ACCESS_NONE is the only acceptable access mask for V2 handle opens.
        ;;

        mov openParameters.Version,OPEN_VIRTUAL_DISK_VERSION_2
        mov openParameters.Version2.GetInfoOnly,FALSE
        mov accessMask,VIRTUAL_DISK_ACCESS_NONE
    .endif

    ;;
    ;; Open the VHD or ISO.
    ;;
    ;; OPEN_VIRTUAL_DISK_FLAG_NONE bypasses any special handling of the open.
    ;;

    mov opStatus,OpenVirtualDisk(
        &storageType,
        VirtualDiskPath,
        accessMask,
        OPEN_VIRTUAL_DISK_FLAG_NONE,
        &openParameters,
        &vhdHandle)

    .if (opStatus != ERROR_SUCCESS)

        jmp Cleanup
    .endif

    ;;
    ;; Create the world-RW SD.
    ;;

    .if (!ConvertStringSecurityDescriptorToSecurityDescriptor(
            L"O:BAG:BAD:(A;;GA;;;WD)",
            SDDL_REVISION_1,
            &sd,
            NULL))

        mov opStatus,GetLastError()
        jmp Cleanup
    .endif

    ;;
    ;; Attach the VHD/VHDX or ISO.
    ;;

    memset(&attachParameters, 0, sizeof(attachParameters))
    mov attachParameters.Version,ATTACH_VIRTUAL_DISK_VERSION_1

    ;;
    ;; A "Permanent" surface persists even when the handle is closed.
    ;;

    mov attachFlags,ATTACH_VIRTUAL_DISK_FLAG_PERMANENT_LIFETIME

    .if (ReadOnly)

        ;; ATTACH_VIRTUAL_DISK_FLAG_READ_ONLY specifies a read-only mount.
        or attachFlags,ATTACH_VIRTUAL_DISK_FLAG_READ_ONLY
    .endif

    mov opStatus,AttachVirtualDisk(
        vhdHandle,
        sd,
        attachFlags,
        0,
        &attachParameters,
        NULL)

Cleanup:

    .if (opStatus == ERROR_SUCCESS)

        wprintf(L"success\n")
    .else
        wprintf(L"error = %u\n", opStatus)
    .endif

    .if (sd != NULL)

        LocalFree(sd)
        mov sd,NULL
    .endif

    .if (vhdHandle != INVALID_HANDLE_VALUE)

        CloseHandle(vhdHandle)
    .endif

    .return opStatus

SampleAttachVirtualDisk endp

    end
