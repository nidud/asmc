; SETENVIRONMENTVARIABLEA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include errno.inc
include stdlib.inc
include winbase.inc

.code

 SetEnvironmentVariableA proc WINAPI uses rsi rdi rbx lpName:LPCSTR, lpValue:LPCSTR

   .new namelen:uint_t
   .new vallen:uint_t
   .new envlen:uint_t
   .new match:int_t
   .new newstr:LPSTR
   .new envstr:LPSTR
   .new curptr:LPSTR

    ldr rbx,lpName
    ldr rax,lpValue
    .if ( rax )
        inc strlen(rax)
    .endif
    mov vallen,eax
    .if ( !rbx || byte ptr [rbx] == 0 )
        .return( SetLastError( ERROR_INVALID_PARAMETER ) )
    .endif
    .if strchr(rbx, '=')
        .return( SetLastError( ERROR_INVALID_PARAMETER ) )
    .endif
    .if ( GetEnvironmentStringsA() == NULL )
        .return
    .endif
    mov envstr,rax
    mov envlen,ecx
    mov namelen,strlen(rbx)
    add eax,envlen
    add eax,vallen
    add eax,7
    mov newstr,malloc( eax )
    .if ( rax == NULL )
        FreeEnvironmentStringsA(envstr)
       .return( SetLastError( ERROR_NOT_ENOUGH_MEMORY ) )
    .endif
    mov rdi,rax
    .if ( vallen )
        mov ecx,namelen
        mov rsi,rbx
        rep movsb
        mov byte ptr [rdi],'='
        inc rdi
        mov ecx,vallen
        mov rsi,lpValue
        rep movsb
    .endif
    .for ( curptr = rdi, rbx = envstr, match = 0 : byte ptr [rbx] : )
        .if ( match == 0 )
            .ifd !strncmp(rbx, lpName, namelen)
                mov ecx,namelen
                .if ( byte ptr [rbx+rcx] == '=' )
                    inc match
                    inc strlen(rbx)
                    add rbx,rax
                   .continue
                .endif
            .endif
        .endif
        inc strlen(rbx)
        mov rsi,rbx
        mov ecx,eax
        mov rdi,curptr
        add rbx,rax
        add curptr,rax
        rep movsb
    .endf
    mov rdi,curptr
    xor eax,eax
    stosd
    mov ebx,SetEnvironmentStringsA(newstr)
    free(newstr)
    FreeEnvironmentStringsA(envstr)
    .return( ebx )
    endp

    end
