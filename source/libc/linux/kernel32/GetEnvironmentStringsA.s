; GETENVIRONMENTSTRINGSA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include errno.inc
include malloc.inc
include processenv.inc
include errhandlingapi.inc
include winerror.inc

.code

 GetEnvironmentStringsA proc WINAPI uses rbx
   .new total:uint_t = 1
   .new block:LPSTR, p
    mov rbx,_environ
    .if ( rbx )
        .while ( string_t ptr [rbx] )
            inc strlen([rbx])
            add total,eax
            add rbx,string_t
        .endw
    .endif
    .if ( total == 1 )
        inc total
    .endif
    .if ( !malloc(total) )
        .return( SetLastError( ERROR_NOT_ENOUGH_MEMORY ) )
    .endif
    mov block,rax
    mov p,rax
    mov rbx,_environ
    .if ( rbx )
        .while ( string_t ptr [rbx] )
            inc strlen([rbx])
            mov rcx,p
            add p,rax
            memcpy(rcx, [rbx], rax)
            add rbx,size_t
        .endw
    .endif
    .if ( block == p )
        mov byte ptr [rax],0
        inc rax
    .endif
    mov byte ptr [rax],0
    mov ecx,total
    .return( block )
    endp

    end
