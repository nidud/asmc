;;
;; This sample demonstrates how to get the list of all the loopback mounted virtual disks.
;;

include Storage.inc

.code

SampleGetAllAttachedVirtualDiskPhysicalPaths proc uses rsi rdi

    .new pathList:LPWSTR
    .new pathListBuffer:LPWSTR = NULL
    .new nextPathListSize:size_t
    .new opStatus:DWORD
    .new pathListSizeInBytes:ULONG = 0
    .new pathListSizeRemaining:size_t
    .new stringLengthResult:HRESULT

    .repeat

        ;;
        ;; Determine the size actually required.
        ;;

        mov opStatus,GetAllAttachedVirtualDiskPhysicalPaths(&pathListSizeInBytes,
                                                          pathListBuffer)
        .if (opStatus == ERROR_SUCCESS)

            .break
        .endif

        .if (opStatus != ERROR_INSUFFICIENT_BUFFER)

            jmp Cleanup
        .endif

        .if (pathListBuffer != NULL)

            free(pathListBuffer)
        .endif

        ;;
        ;; Allocate a large enough buffer.
        ;;

        mov pathListBuffer,malloc(pathListSizeInBytes)
        .if (pathListBuffer == NULL)

            mov opStatus,ERROR_OUTOFMEMORY
            jmp Cleanup
        .endif

    .until (opStatus != ERROR_INSUFFICIENT_BUFFER)

    mov rcx,pathListBuffer
    .if (rcx == NULL || LPWSTR ptr [rcx] == NULL)

        ;; There are no loopback mounted virtual disks.
        wprintf(L"There are no loopback mounted virtual disks.\n")
        jmp Cleanup
    .endif

    ;;
    ;; The pathList is a MULTI_SZ.
    ;;

    mov pathList,pathListBuffer
    mov rsi,rax
    mov pathListSizeRemaining,pathListSizeInBytes

    .while ((pathListSizeRemaining >= sizeof(pathList)) && (WCHAR ptr [rsi] != 0))

        xor eax,eax
        xor ecx,ecx

        .while rcx < pathListSizeRemaining

            lodsw
            inc ecx
            .break .if !eax
        .endw

        .if (FAILED(stringLengthResult))

            jmp Cleanup
        .endif

        wprintf(L"Path = '%s'\n", pathList)
            jmp Cleanup
        ;nextPathListSize += sizeof(pathList[0]);
        ;pathList = pathList + (nextPathListSize / sizeof(pathList[0]));
        ;pathListSizeRemaining -= nextPathListSize;
    .endw

Cleanup:

    .if (opStatus == ERROR_SUCCESS)

        wprintf(L"success\n")
    .else
        wprintf(L"error = %u\n", opStatus)
    .endif

    .if (pathListBuffer != NULL)

        free(pathListBuffer)
    .endif

    .return opStatus

SampleGetAllAttachedVirtualDiskPhysicalPaths endp

    end
