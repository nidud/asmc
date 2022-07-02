; SETARGV.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; char **setargv( int *argc, char *command_line );
;
; Note: The main array (__argv) is allocated in __argv.asm
;
include stdlib.inc
include string.inc
include malloc.inc

define MAXARGCOUNT 256
define MAXARGSIZE  0x8000  ; Max argument size: 32K

    .code

setargv proc uses rsi rdi rbx argc:ptr int_t, cmdline:string_t

  local argv[MAXARGCOUNT]:string_t
  local buffer:string_t
  local i:int_t

ifndef _WIN64
    mov ecx,argc
    mov edx,cmdline
endif
    mov rsi,rdx
    mov dword ptr [rcx],0
    mov buffer,malloc(MAXARGSIZE)
    mov rdi,rax
    lodsb

    .while al

        xor ecx,ecx     ; Add a new argument
        xor edx,edx     ; "quote from start" in EDX - remove
        mov [rdi],cl

        .for ( : al == ' ' || ( al >= 9 && al <= 13 ) : )
            lodsb
        .endf
        .break .if !al  ; end of command string

        .if ( al == '"' )
            add edx,1
            lodsb
        .endif
        .while ( al == '"' ) ; ""A" B"
            add ecx,1
            lodsb
        .endw

        .while al

            .break .if ( !edx && !ecx && ( al == ' ' || ( al >= 9 && al <= 13 ) ) )

            .if ( al == '"' )

                .if ecx
                    dec ecx
                .elseif edx
                    mov al,[rsi]
                    .break .if ( al == ' ' || ( al >= 9 && al <= 13 ) )
                    dec edx
                .else
                    inc ecx
                .endif
            .else
                stosb
            .endif
            lodsb
        .endw

        xor ecx,ecx
        mov [rdi],ecx
        lea rbx,[rdi+1]
        mov rdi,buffer
        .break .if ( cl == [rdi] )

        mov i,eax
        sub rbx,rdi
        memcpy(malloc(rbx), rdi, rbx)
        mov rdx,argc
        mov ecx,[rdx]
        mov argv[rcx*size_t],rax
        inc dword ptr [rdx]
        mov eax,i

        .break .if !( ecx < MAXARGCOUNT )
    .endw

    xor eax,eax
    mov rdx,argc
    mov ebx,[rdx]
    lea rdi,argv
    mov [rdi+rbx*size_t],rax
    lea rbx,[rbx*size_t+size_t]
    mov rsi,malloc(rbx)
    free(buffer)
    memcpy(rsi, rdi, rbx)
    ret

setargv endp

    end
