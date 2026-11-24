; SETENVIRONMENTSTRINGSA.ASM--
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

.data
 _env_allocated db 0

.code

 SetEnvironmentStringsA proc WINAPI uses rbx NewEnvironment:LPSTR
   .new count:int_t = 1     ; + NULL
   .new size:uint_t = 1     ; + \0
   .new newenv:ptr LPSTR
   .new p:LPSTR
    ldr rbx,NewEnvironment
    .if ( !rbx )
        .return( SetLastError( ERROR_INVALID_PARAMETER ) )
    .endif
    .for ( p = rbx : byte ptr [rbx] : count++ )
        .if ( byte ptr [rbx] == '=' || !strchr(rbx, '=') )
            .return( SetLastError( ERROR_INVALID_PARAMETER ) )
        .endif
        inc strlen(rbx)
        add size,eax
        add rbx,rax
    .endf
    imul eax,count,size_t
    add eax,size
    .if ( !malloc(eax) )
        .return( SetLastError( ERROR_NOT_ENOUGH_MEMORY ) )
    .endif
    mov newenv,rax
    imul ecx,count,size_t
    add rcx,rax
    mov p,memcpy(rcx, p, size)
    .for ( count--, ebx = 0 : ebx < count : ebx++ )
        mov rcx,newenv
        mov rax,p
        mov [rcx+rbx*size_t],rax
        inc strlen(p)
        add p,rax
    .endf
    .if ( _env_allocated )
        free(_environ)
    .endif
    mov rdx,newenv
    xor eax,eax
    mov [rdx+rbx*size_t],rax
    mov _environ,rdx
    inc eax
    mov _env_allocated,al
    ret
    endp

    end
