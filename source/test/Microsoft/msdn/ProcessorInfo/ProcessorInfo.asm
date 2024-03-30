; PROCESSORINFO.ASM--
;
; https://learn.microsoft.com/en-us/windows/win32/api/sysinfoapi/nf-sysinfoapi-getlogicalprocessorinformation
;
include windows.inc
include malloc.inc
include stdio.inc
include tchar.inc

CALLBACK(LPFN_GLPI, :PSYSTEM_LOGICAL_PROCESSOR_INFORMATION, :PDWORD)

.code

; Helper function to count set bits in the processor mask.

CountSetBits proto fastcall bitMask:ULONG_PTR {
    popcnt rax,rcx
    }

_tmain proc

    .new glpi:LPFN_GLPI
    .new buffer:PSYSTEM_LOGICAL_PROCESSOR_INFORMATION = NULL
    .new returnLength:DWORD = 0
    .new logicalProcessorCount:DWORD = 0
    .new numaNodeCount:DWORD = 0
    .new processorCoreCount:DWORD = 0
    .new processorL1CacheCount:DWORD = 0
    .new processorL2CacheCount:DWORD = 0
    .new processorL3CacheCount:DWORD = 0
    .new processorPackageCount:DWORD = 0

    mov glpi,GetProcAddress(GetModuleHandle("kernel32"), "GetLogicalProcessorInformation")
    .if ( glpi == NULL )

        _tprintf("\nGetLogicalProcessorInformation is not supported.\n")
        .return( 1 )
    .endif

    .while 1

        .if ( glpi(buffer, &returnLength) == FALSE )

            .if ( GetLastError() == ERROR_INSUFFICIENT_BUFFER )

                .if ( buffer )

                    free(buffer)
                .endif

                mov buffer,malloc(returnLength)
                .if ( buffer == NULL )

                    _tprintf("\nError: Allocation failure\n")
                    .return( 2 )
                .endif
            .else
                _tprintf("\nError %d\n", GetLastError())
                .return( 3 )
            .endif
        .else
            .break
        .endif
    .endw

    mov rdi,buffer
    mov ebx,SYSTEM_LOGICAL_PROCESSOR_INFORMATION

    assume rdi:ptr SYSTEM_LOGICAL_PROCESSOR_INFORMATION

    .while ( ebx <= returnLength )

        .switch ( [rdi].Relationship )

        .case RelationNumaNode

            ; Non-NUMA systems report a single record of this type.

            inc numaNodeCount
           .endc

        .case RelationProcessorCore
            inc processorCoreCount

            ; A hyperthreaded core supplies more than one logical processor.

            add logicalProcessorCount,CountSetBits([rdi].ProcessorMask)
           .endc

        .case RelationCache

            ; Cache data is in ptr->Cache, one CACHE_DESCRIPTOR structure for each cache.

            mov al,[rdi].Cache.Level
            .if ( al == 1 )
                inc processorL1CacheCount
            .elseif ( al == 2 )
                inc processorL2CacheCount
            .elseif ( al == 3 )
                inc processorL3CacheCount
            .endif
            .endc

        .case RelationProcessorPackage

            ; Logical processors share a physical package.

            inc processorPackageCount
           .endc

        .default
            _tprintf("\nError: Unsupported LOGICAL_PROCESSOR_RELATIONSHIP value.\n")
           .endc
        .endsw
        add ebx,SYSTEM_LOGICAL_PROCESSOR_INFORMATION
        add rdi,SYSTEM_LOGICAL_PROCESSOR_INFORMATION
    .endw

    _tprintf(
        "\nGetLogicalProcessorInformation results:\n"
        "Number of NUMA nodes: %d\n"
        "Number of physical processor packages: %d\n"
        "Number of processor cores: %d\n"
        "Number of logical processors: %d\n"
        "Number of processor L1/L2/L3 caches: %d/%d/%d\n",
        numaNodeCount,
        processorPackageCount,
        processorCoreCount,
        logicalProcessorCount,
        processorL1CacheCount,
        processorL2CacheCount,
        processorL3CacheCount )

    free(buffer)
   .return 0

_tmain endp

    end _tstart
