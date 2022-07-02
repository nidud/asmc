; SETWARGV.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; wchar_t **setwargv( int *argc, wchar_t *command_line );
;
; Note: The main array (__argv) is allocated in __wargv.asm
;
include stdlib.inc
include string.inc
include malloc.inc

MAXARGCOUNT equ 256
MAXARGSIZE  equ 0x8000  ; Max argument size: 32K

    .code

setwargv proc uses rsi rdi rbx argc:ptr int_t, cmdline:ptr wchar_t

  local argv[MAXARGCOUNT]:string_t
  local buffer:string_t
  local i:int_t

ifndef _WIN64
    mov ecx,argc
    mov edx,cmdline
endif
    mov rsi,rdx
    mov dword ptr [rcx],0
    mov buffer,malloc(MAXARGSIZE*2)
    mov rdi,rax
    lodsw

    .while ax

        xor ecx,ecx     ; Add a new argument
        xor edx,edx     ; "quote from start" in EDX - remove
        mov [rdi],cx

        .for ( : ax == ' ' || ( ax >= 9 && ax <= 13 ) : )
            lodsw
        .endf
        .break .if !ax  ; end of command string

        .if ax == '"'
            lodsw
            inc edx
        .endif
        .while ax == '"' ; ""A" B"
            lodsw
            inc ecx
        .endw

        .while ax

            .break .if ( !edx && !ecx && ( ax == ' ' || ( ax >= 9 && ax <= 13 ) ) )

            .if ax == '"'
                .if ecx
                    dec ecx
                .elseif edx
                    mov ax,[rsi]
                    .break .if ( ax == ' ' )
                    .break .if ( ax >= 9 && ax <= 13 )
                    dec edx
                .else
                    inc ecx
                .endif
            .else
                stosw
            .endif
            lodsw
        .endw

        xor ecx,ecx
        mov [rdi],ecx
        lea rbx,[rdi+2]
        mov rdi,buffer
        .break .if cx == [rdi]

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

setwargv endp

    end
