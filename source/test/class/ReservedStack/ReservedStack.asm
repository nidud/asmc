; RESERVEDSTACK.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include tchar.inc
include ReservedStack.inc

    .code

ReservedStack proc i:int_t

  local b[16]:byte

    printf("BEGIN ReservedStack\n")
    printf(" stack::local_size: %d\n", stack::local_size())
    printf(" stack::param_size: %d\n", stack::param_size())
    printf(" stack::total_size: %d\n", stack::total_size())
    printf(" stack::param_count: %d\n", stack::param_count())
    printf("\n")

    printf(" stack::enter()\n")
    .for ( i = 0: i < 4: i++ )
        stack::enter(256)
        printf(" stack::total_size: %d\n", stack::total_size())
    .endf
    .for ( i = 0: i < 4: i++ )
        stack::leave()
        printf(" stack::total_size: %d\n", stack::total_size())
    .endf
    printf("\n")

    printf(" stack::alloc()\n")
    .for ( i = 0: i < 5: i++ )
        stack::alloc(256*256*2)
        printf(" stack::total_size: %d\n", stack::total_size())
    .endf
    .for ( i = 0: i < 5: i++ )
        stack::free(256*256*2)
        printf(" stack::total_size: %d\n", stack::total_size())
    .endf
    printf("\n")
    printf(" stack::local_size: %d\n", stack::local_size())
    printf(" stack::param_size: %d\n", stack::param_size())
    printf(" stack::total_size: %d\n", stack::total_size())
    printf("END\n")
    ret

ReservedStack endp

main proc

    printf("rsp: %p\n", rsp)
    ReservedStack()
    printf("rsp: %p\n", rsp)
    ret

main endp

    end _tstart

