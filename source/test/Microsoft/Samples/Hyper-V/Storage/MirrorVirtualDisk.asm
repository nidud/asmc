;;
;; This sample demonstrates how to mirror a VHD or VHDX to a new location. The VHD or VHDX in the
;; new location will be part of the active virtual disk chain once the operation completes
;; successfully. The old files are not deleted after the operation completes.
;;

include Storage.inc

.code

SampleMirrorVirtualDisk proc \
    SourcePath: LPCWSTR,
    DestinationPath: LPCWSTR

    .new openParameters:OPEN_VIRTUAL_DISK_PARAMETERS
    .new mirrorParameters:MIRROR_VIRTUAL_DISK_PARAMETERS
    .new progress:VIRTUAL_DISK_PROGRESS
    .new storageType:VIRTUAL_STORAGE_TYPE
    .new overlapped:OVERLAPPED
    .new vhdHandle:HANDLE = INVALID_HANDLE_VALUE
    .new opStatus:DWORD

    memset(&overlapped, 0, sizeof(overlapped))
    mov overlapped.hEvent,CreateEvent(NULL, TRUE, FALSE, NULL)
    .if (overlapped.hEvent == NULL)

        mov opStatus,GetLastError()
        jmp Cleanup
    .endif

    ;;
    ;; Specify UNKNOWN for both device and vendor so the system will use the
    ;; file extension to determine the correct VHD format.
    ;;

    mov storageType.DeviceId,VIRTUAL_STORAGE_TYPE_DEVICE_UNKNOWN
    mov storageType.VendorId,VIRTUAL_STORAGE_TYPE_VENDOR_UNKNOWN

    ;;
    ;; Open the source VHD/VHDX.
    ;;
    ;; Only V2 handles can be used when mirroring VHDs.
    ;;
    ;; VIRTUAL_DISK_ACCESS_NONE is the only acceptable access mask for V2 handle opens.
    ;; OPEN_VIRTUAL_DISK_FLAG_NONE bypasses any special handling of the open.
    ;;

    memset(&openParameters, 0, sizeof(openParameters))
    mov openParameters.Version,OPEN_VIRTUAL_DISK_VERSION_2

    mov opStatus,OpenVirtualDisk(
        &storageType,
        SourcePath,
        VIRTUAL_DISK_ACCESS_NONE,
        OPEN_VIRTUAL_DISK_FLAG_NONE,
        &openParameters,
        &vhdHandle)

    .if (opStatus != ERROR_SUCCESS)

        jmp Cleanup
    .endif

    ;;
    ;; Start mirror operation.
    ;;
    ;; MIRROR_VIRTUAL_DISK_VERSION_1 is the only version of the parameters currently supported.
    ;; MIRROR_VIRTUAL_DISK_FLAG_NONE forces the creation of a new file.
    ;;

    memset(&mirrorParameters, 0, sizeof(MIRROR_VIRTUAL_DISK_PARAMETERS))
    mov mirrorParameters.Version, MIRROR_VIRTUAL_DISK_VERSION_1
    mov mirrorParameters.Version1.MirrorVirtualDiskPath,DestinationPath

    mov opStatus,MirrorVirtualDisk(
        vhdHandle,
        MIRROR_VIRTUAL_DISK_FLAG_NONE,
        &mirrorParameters,
        &overlapped
        )

    .if ((opStatus == ERROR_SUCCESS) || (opStatus == ERROR_IO_PENDING))

        ;;
        ;; The mirror is completed once the "CurrentValue" reaches the "CompletionValue".
        ;;
        ;; Every subsequent write will be forward to both the source and destination until the
        ;; mirror is broken.
        ;;

        .for (::)

            memset(&progress, 0, sizeof(progress))

            mov opStatus,GetVirtualDiskOperationProgress(vhdHandle, &overlapped, &progress)
            .if (opStatus != ERROR_SUCCESS)

                jmp Cleanup
            .endif

            mov opStatus,progress.OperationStatus
            .if (opStatus == ERROR_IO_PENDING)

                .if (progress.CurrentValue == progress.CompletionValue)

                    .break
                .endif

            .else

                ;;
                ;; Any status other than ERROR_IO_PENDING indicates the mirror failed.
                ;;
                jmp Cleanup
            .endif

            Sleep(1000)
        .endf

    .else

        jmp Cleanup
    .endif

    ;;
    ;; Break the mirror.  Breaking the mirror will activate the new target and cause it to be
    ;; utilized in place of the original VHD/VHDX.
    ;;

    mov opStatus,BreakMirrorVirtualDisk(vhdHandle)

    .if (opStatus != ERROR_SUCCESS)

        jmp Cleanup

    .else

        .for (::)

            memset(&progress, 0, sizeof(progress))

            mov opStatus,GetVirtualDiskOperationProgress(vhdHandle, &overlapped, &progress)
            .if (opStatus != ERROR_SUCCESS)

                jmp Cleanup
            .endif

            mov opStatus,progress.OperationStatus
            .if (opStatus == ERROR_SUCCESS)

                .break

            .elseif (opStatus != ERROR_IO_PENDING)

                jmp Cleanup
            .endif

            Sleep(1000)
        .endf
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

    .if (overlapped.hEvent != NULL)

        CloseHandle(overlapped.hEvent)
    .endif

    .return opStatus

SampleMirrorVirtualDisk endp

    end
