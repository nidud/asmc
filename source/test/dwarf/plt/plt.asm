; PLT.ASM--
;
; Linking to shared libraries using -fplt
;

include stdio.inc
include stdlib.inc

.code

main proc

    printf("Linking to %d-bit shared libraries: Asmc %d.%d\n", size_t shl 3, __ASMC__ / 100, __ASMC__ mod 100)
    printf("ASMCDIR:      %s\n", getenv("ASMCDIR"))
    printf("INCLUDE:      %s\n", getenv("INCLUDE"))
    printf("LIBRARY_PATH: %s\n", getenv("LIBRARY_PATH"))
    xor eax,eax
    ret
    endp

    end
