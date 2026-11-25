; GETENVIRONMENTVARIABLEA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include string.inc
include errno.inc
include winbase.inc

.code

 GetEnvironmentVariableA proc WINAPI uses rbx lpName:LPCSTR, lpBuffer:LPSTR, nSize:DWORD
   .new namelen:size_t
    ldr rbx,lpName
    .if ( !rbx || byte ptr [rbx] == 0 || strchr(rbx, '=') )
        .return( SetLastError( ERROR_ENVVAR_NOT_FOUND ) )
    .endif
    mov namelen,strlen(rbx)
    mov rbx,_environ
    .if ( rbx )
        .while ( LPSTR ptr [rbx] )
            .ifd ( !strncmp([rbx], lpName, namelen) )
                mov rax,[rbx]
                mov rcx,namelen
                .if ( byte ptr [rax+rcx] == '=' )
                    strlen(&[rax+rcx+1])
                    mov rcx,lpBuffer
                    .if ( !rcx || nSize <= eax )
                        inc eax
                       .return
                    .endif
                    xchg rax,rbx
                    mov rax,[rax]
                    add rax,namelen
                    inc rax
                    strcpy(rcx, rax)
                   .return( ebx )
                .endif
            .endif
            add rbx,size_t
        .endw
    .endif
    .return( SetLastError( ERROR_ENVVAR_NOT_FOUND ) )
    endp

    end
