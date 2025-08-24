; HEAPWALK.ASM--
;
; https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/heapwalk?view=msvc-170
;

include stdio.inc
include malloc.inc
include tchar.inc

.code

heapdump proc

   .new hinfo:_HEAPINFO
   .new heapstatus:int_t
   .new numLoops:int_t

    mov hinfo._pentry,NULL
    mov numLoops,0

    .while 1

        mov heapstatus,_heapwalk(&hinfo)
        .break .if ( eax != _HEAPOK || numLoops >= 100 )

        lea rdx,@CStr("USED")
        .if ( hinfo._useflag != _USEDENTRY )
            lea rdx,@CStr("FREE")
        .endif

        printf("%8s block at %Fp of size %4.4X\n", rdx, hinfo._pentry, hinfo._size)
        inc numLoops
    .endw

    .switch pascal heapstatus
    .case _HEAPEMPTY
        printf("OK - empty heap\n")
    .case _HEAPEND
        printf("OK - end of heap\n")
    .case _HEAPBADPTR
        printf("ERROR - bad pointer to heap\n")
    .case _HEAPBADBEGIN
        printf("ERROR - bad start of heap\n")
    .case _HEAPBADNODE
        printf("ERROR - bad node in heap\n")
    .endsw
    ret

heapdump endp


main proc

   .new buffer:string_t

    heapdump()
    mov buffer,malloc(59)

    .if ( rax != NULL )

        heapdump()
        free(buffer)
    .endif
    heapdump()
    xor eax,eax
    ret

main endp

    end _tstart
