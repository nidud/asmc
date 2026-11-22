; GETFULLPATHNAMEA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fileapi.inc
include direct.inc
include string.inc
include errno.inc
include sys/syscall.inc
include winbase.inc

.code

 GetFullPathNameA proc WINAPI uses rsi rdi rbx lpFileName:LPCSTR,
        nBufferLength:DWORD, lpBuffer:LPSTR, lpFilePart:ptr LPSTR
   .new len:int_t
   .new tmp[4096]:char_t
    ldr rsi,lpFileName
    .if ( !rsi || byte ptr [rsi] == 0 )
        .return( 0 )
    .endif
    lea rbx,tmp
    .if ( byte ptr [rsi] != '/' )
        .ifsd ( sys_getcwd(rbx, 4096) < 0 )
           .return( _sys_maperr(eax) )
        .endif
        strlen(rbx)
        add rbx,rax
        lea rax,tmp
        .if ( rbx > rax && byte ptr [rbx-1] != '/' )
            mov byte ptr [rbx],'/'
            inc rbx
        .endif
        mov rsi,lpFileName
    .else
        mov byte ptr [rbx],'/'
        inc rbx
        inc rsi
    .endif
    lea rdi,tmp
    .while ( byte ptr [rsi] )
        .while ( byte ptr [rsi] == '/' )
            inc rsi
        .endw
        .break .if ( byte ptr [rsi] == 0 )
        .if ( byte ptr [rsi] == '.' )
            mov al,[rsi+1]
            .if ( al == 0 || al == '/' )
                inc rsi
               .continue
            .endif
            .if ( al == '.' )
                mov al,[rsi+2]
                .if ( al == 0 || al == '/' )
                    add rsi,2
                    lea rax,[rdi+1]
                    .if ( rbx > rax )
                        dec rbx
                        .while ( rbx > rax && byte ptr [rbx-1] != '/' )
                            dec rbx
                        .endw
                    .endif
                    .continue
                .endif
            .endif
        .endif
        .while ( byte ptr [rsi] && byte ptr [rsi] != '/' )
            mov al,[rsi]
            mov [rbx],al
            inc rsi
            inc rbx
        .endw
        .if ( byte ptr [rsi] == '/' )
            mov byte ptr [rbx],'/'
            inc rbx
        .endif
    .endw
    lea rax,[rdi+1]
    .if ( rbx > rax && byte ptr [rbx-1] == '/' )
        mov al,[rsi-1]
        .if ( al != '/' && al != '\' )
            dec rbx
        .endif
    .endif
    mov byte ptr [rbx],0
    mov rax,rbx
    sub rax,rdi
    mov len,eax
    mov ecx,nBufferLength
    mov rsi,rdi
    mov rdi,lpBuffer
    .if ( eax >= ecx || !rdi )
        inc eax
       .return
    .endif
    mov ecx,len
    inc ecx
    mov rax,rdi
    rep movsb
    mov rdx,lpFilePart
    .if ( rdx )
        mov rdi,rax
        mov eax,len
        .if ( eax > 0 && byte ptr [rdi+rax-1] == '/' )
            xor eax,eax
            mov [rdx],rax
        .else
            lea rsi,[rdi+rax]
            .while ( rsi > rdi && byte ptr [rsi-1] != '/' )
                dec rsi
            .endw
            mov [rdx],rsi
        .endif
    .endif
    .return( len )
    endp

    end
