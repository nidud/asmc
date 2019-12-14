include windows.inc
include stdio.inc
include malloc.inc
include tchar.inc

LPFN_GLPI_T typedef proto WINAPI :PSYSTEM_LOGICAL_PROCESSOR_INFORMATION, :LPDWORD
LPFN_GLPI   typedef ptr LPFN_GLPI_T

.code

;; Helper function to count set bits in the processor mask.
CountSetBits proc bitMask:ULONG_PTR

    LSHIFT = sizeof(ULONG_PTR)*8 - 1

    mov r8,1 shl LSHIFT
    xor eax,eax

    .for (edx = 0: edx <= LSHIFT: ++edx)

        .if (rcx & r8)
            inc eax
        .endif
        shr r8,1
    .endf
    ret

CountSetBits endp

_tmain proc

    local glpi:LPFN_GLPI
    local done:BOOL
    local buffer:PSYSTEM_LOGICAL_PROCESSOR_INFORMATION
    local p:PSYSTEM_LOGICAL_PROCESSOR_INFORMATION
    local returnLength:DWORD
    local logicalProcessorCount:DWORD
    local numaNodeCount:DWORD
    local processorCoreCount:DWORD
    local processorL1CacheCount:DWORD
    local processorL2CacheCount:DWORD
    local processorL3CacheCount:DWORD
    local processorPackageCount:DWORD
    local byteOffset:DWORD
    local Cache:PCACHE_DESCRIPTOR
    local rc:DWORD
    local LineSize:DWORD
    local CacheSize:DWORD

    lea rdi,byteOffset
    xor eax,eax
    mov ecx,14
    rep stosd

    .if !GetProcAddress(
            GetModuleHandle("kernel32"), "GetLogicalProcessorInformation")
        _tprintf("\nGetLogicalProcessorInformation is not supported.\n")
        exit(1)
    .endif
    mov glpi,rax

    .while (!done)

        .if !glpi(buffer, &returnLength)

            .if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)

                .if (buffer)
                    free(buffer)
                .endif
                mov buffer,malloc(returnLength)

                .if (buffer == NULL)

                    _tprintf("\nError: Allocation failure\n")
                    exit(2)
                .endif

            .else

                _tprintf("\nError %d\n", GetLastError())
                exit(3)
            .endif

        .else

            mov done,TRUE
        .endif
    .endw

    mov rdi,buffer
    mov ebx,sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION)

    assume rdi:ptr SYSTEM_LOGICAL_PROCESSOR_INFORMATION

    .while (ebx <= returnLength)

        .switch ([rdi].Relationship)

        .case RelationNumaNode
            ;; Non-NUMA systems report a single record of this type.
            inc numaNodeCount
            .endc

        .case RelationProcessorCore
            inc processorCoreCount

            ;; A hyperthreaded core supplies more than one logical processor.
            CountSetBits([rdi].ProcessorMask)
            add logicalProcessorCount,eax
            .endc

        .case RelationCache
            ;; Cache data is in ptr->Cache, one CACHE_DESCRIPTOR structure for each cache.
            mov al,[rdi].Cache.Level
            .if (al == 1)
                inc processorL1CacheCount
            .elseif (al == 2)
                inc processorL2CacheCount
            .elseif (al == 3)
                inc processorL3CacheCount
            .endif
            movzx eax,[rdi].Cache.LineSize
            mov LineSize,eax
            mov eax,[rdi].Cache.Size
            mov CacheSize,eax
            .endc

        .case RelationProcessorPackage
            ;; Logical processors share a physical package.
            inc processorPackageCount
            .endc

        .default
            _tprintf("\nError: Unsupported LOGICAL_PROCESSOR_RELATIONSHIP value.\n")
            .endc
        .endsw
        add ebx,sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION)
        add rdi,sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION)
    .endw

    _tprintf("\nGetLogicalProcessorInformation results:\n")
    _tprintf("Number of NUMA nodes: %d\n", numaNodeCount)
    _tprintf("Number of physical processor packages: %d\n",
             processorPackageCount)
    _tprintf("Number of processor cores: %d\n",
             processorCoreCount)
    _tprintf("Number of logical processors: %d\n",
             logicalProcessorCount)
    _tprintf("Number of processor L1/L2/L3 caches: %d/%d/%d\n",
             processorL1CacheCount,
             processorL2CacheCount,
             processorL3CacheCount)
    _tprintf("Cache LineSize: %d\n", LineSize)
    _tprintf("Cache Size: %X\n", CacheSize)

    free(buffer)
    exit(0)

_tmain endp

    end _tmain
