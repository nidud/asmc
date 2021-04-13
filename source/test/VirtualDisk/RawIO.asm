;;
;; This sample demonstrates how to open a VHD or VHDX file in Raw IO mode and how to issue
;; raw reads and writes to the virtual hard disk sectors.
;;

include Storage.inc

.code

;;
;; This sample uses a 1MB buffer for reads/writes but any size that is a multiple of the sector
;; size for both VHDs is acceptable.
;;

define SAMPLE_BUFFER_SIZE (1024*1024)

SampleRawIO proc \
    SourceVirtualDiskPath: LPCWSTR,
    DestinationVirtualDiskPath: LPCWSTR

    .new sourceVhdHandle:HANDLE = INVALID_HANDLE_VALUE
    .new destinationVhdHandle:HANDLE = INVALID_HANDLE_VALUE
    .new storageType:VIRTUAL_STORAGE_TYPE
    .new openParameters:OPEN_VIRTUAL_DISK_PARAMETERS
    .new attachParameters:ATTACH_VIRTUAL_DISK_PARAMETERS
    .new attachFlags:ATTACH_VIRTUAL_DISK_FLAG
    .new diskInfo:GET_VIRTUAL_DISK_INFO
    .new opStatus:DWORD
    .new overlapped:OVERLAPPED
    .new virtualDiskSize:LARGE_INTEGER
    .new offs:LARGE_INTEGER = 0
    .new diskInfoSize:ULONG
    .new bytesRead:DWORD
    .new bytesWritten:DWORD
    .new buffer:PUCHAR

    mov buffer,malloc(SAMPLE_BUFFER_SIZE)

    .if (buffer == NULL)

        mov opStatus,ERROR_NOT_ENOUGH_MEMORY
        jmp Cleanup
    .endif

    ;;
    ;; Specify UNKNOWN for both device and vendor so the system will use the
    ;; file extension to determine the correct VHD format.
    ;;

    mov storageType.DeviceId,VIRTUAL_STORAGE_TYPE_DEVICE_UNKNOWN
    mov storageType.VendorId,VIRTUAL_STORAGE_TYPE_VENDOR_UNKNOWN

    memset(&openParameters, 0, sizeof(openParameters))
    mov openParameters.Version,OPEN_VIRTUAL_DISK_VERSION_2
    mov openParameters.Version2.GetInfoOnly,FALSE

    memset(&attachParameters, 0, sizeof(attachParameters))
    mov attachParameters.Version,ATTACH_VIRTUAL_DISK_VERSION_1

    memset(&diskInfo, 0, sizeof(diskInfo))

    memset(&overlapped, 0, sizeof(overlapped))

    ;;
    ;; Open the source VHD in RAW IO mode to read directly from the virtual disk sectors.
    ;;

    ;;
    ;; VIRTUAL_DISK_ACCESS_NONE is the only acceptable access mask for V2 handle opens.
    ;;

    mov opStatus,OpenVirtualDisk(
        &storageType,
        SourceVirtualDiskPath,
        VIRTUAL_DISK_ACCESS_NONE,
        OPEN_VIRTUAL_DISK_FLAG_NONE,
        &openParameters,
        &sourceVhdHandle)

    .if (opStatus != ERROR_SUCCESS)

        jmp Cleanup
    .endif

    ;;
    ;; Deteremine the source virtual disk size.
    ;;

    mov diskInfo.Version,GET_VIRTUAL_DISK_INFO_SIZE
    mov diskInfoSize,sizeof(diskInfo)

    mov opStatus,GetVirtualDiskInformation(
        sourceVhdHandle,
        &diskInfoSize,
        &diskInfo,
        NULL)

    .if (opStatus != ERROR_SUCCESS)

        jmp Cleanup
    .endif

    mov virtualDiskSize.QuadPart,diskInfo.Size.VirtualSize

    ;;
    ;; ATTACH_VIRTUAL_DISK_FLAG_NO_LOCAL_HOST is required for RawIO.
    ;;

    mov attachFlags,ATTACH_VIRTUAL_DISK_FLAG_NO_LOCAL_HOST or \
                  ATTACH_VIRTUAL_DISK_FLAG_READ_ONLY

    mov opStatus,AttachVirtualDisk(
        sourceVhdHandle,
        NULL,
        attachFlags,
        0,
        &attachParameters,
        NULL)

    .if (opStatus != ERROR_SUCCESS)

        jmp Cleanup
    .endif

    ;;
    ;; Open the destination VHD in RAW IO mode to write directly to the virtual disk sectors.
    ;;

    ;;
    ;; VIRTUAL_DISK_ACCESS_NONE is the only acceptable access mask for V2 handle opens.
    ;;

    mov opStatus,OpenVirtualDisk(
        &storageType,
        DestinationVirtualDiskPath,
        VIRTUAL_DISK_ACCESS_NONE,
        OPEN_VIRTUAL_DISK_FLAG_NONE,
        &openParameters,
        &destinationVhdHandle)

    .if (opStatus != ERROR_SUCCESS)

        jmp Cleanup
    .endif

    ;;
    ;; ATTACH_VIRTUAL_DISK_FLAG_NO_LOCAL_HOST is required for RawIO.
    ;;

    mov attachFlags,ATTACH_VIRTUAL_DISK_FLAG_NO_LOCAL_HOST

    mov opStatus,AttachVirtualDisk(
        destinationVhdHandle,
        NULL,
        attachFlags,
        0,
        &attachParameters,
        NULL)

    .if (opStatus != ERROR_SUCCESS)

        jmp Cleanup
    .endif

    .while(offs.QuadPart < virtualDiskSize.QuadPart)

        ;;
        ;; Read next chunk of source file
        ;;
        mov overlapped._Offset,offs.LowPart
        mov overlapped.OffsetHigh,offs.HighPart

        .if (!ReadFile(
                sourceVhdHandle,
                buffer,
                SAMPLE_BUFFER_SIZE,
                &bytesRead,
                &overlapped))

            .if (GetLastError() == ERROR_IO_PENDING)

                .if (!GetOverlappedResult(sourceVhdHandle, &overlapped, &bytesRead, TRUE))

                    mov opStatus,GetLastError()
                .endif
            .endif

            .if (opStatus != ERROR_SUCCESS)

                .break
            .endif
        .endif

        ;;
        ;; Write next chunk to destination file
        ;;
        mov overlapped._Offset,offs.LowPart
        mov overlapped.OffsetHigh,offs.HighPart

        .if (!WriteFile(
                destinationVhdHandle,
                buffer,
                bytesRead,
                &bytesWritten,
                &overlapped))

            .if (GetLastError() == ERROR_IO_PENDING)

                .if (!GetOverlappedResult(destinationVhdHandle, &overlapped, &bytesWritten, TRUE))

                    mov opStatus,GetLastError()
                .endif
            .endif

            .if (opStatus != ERROR_SUCCESS)

                .break
            .endif

            .if (bytesWritten != bytesRead)

                mov opStatus,ERROR_HANDLE_EOF
                .break
            .endif
        .endif

        add offs.LowPart,bytesWritten
        adc offs.HighPart,0
    .endw

Cleanup:

    .if (opStatus == ERROR_SUCCESS)

        wprintf(L"success, bytes transferred = %I64d\n", offs.QuadPart)
    .else
        wprintf(L"error = %u\n", opStatus)
    .endif

    .if (sourceVhdHandle != INVALID_HANDLE_VALUE)

        CloseHandle(sourceVhdHandle)
    .endif

    .if (destinationVhdHandle != INVALID_HANDLE_VALUE)

        CloseHandle(destinationVhdHandle)
    .endif

    .if (buffer != NULL)

        free(buffer)
    .endif

    .return opStatus

SampleRawIO endp

    end
