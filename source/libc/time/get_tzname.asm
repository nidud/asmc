; GET_TZNAME.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include string.inc
include errno.inc

.code

_get_tzname proc uses rbx retval:ptr size_t, buffer:string_t, size:size_t, index:int_t

    ldr rbx,buffer
    ldr rax,size

    .ifs !( ( rbx != NULL && rax > 0 ) || ( rbx == NULL && rax == 0 ) )

        .return( EINVAL )
    .endif

    .if ( rbx != NULL )

        mov byte ptr [rbx],0
    .endif

    ldr ecx,index
    ldr rdx,retval

    .ifs ( ecx < 0 || ecx > 1 || rdx == NULL )

        .return( EINVAL )
    .endif

    lea rdx,_tzname
    strlen([rdx+rcx*string_t])
    mov rcx,retval
    inc rax
    mov [rcx],rax

    .if ( rbx == NULL )

        ; the user is interested only in the size of the buffer

        .return( 0 )
    .endif

    .if ( rax > size )

        .return(ERANGE)
    .endif

    lea rdx,_tzname
    mov ecx,index
    strcpy_s(rbx, size, [rdx+rcx*string_t])
    ret

_get_tzname endp

    end
