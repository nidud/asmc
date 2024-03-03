; _TSETARGV.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; TCHAR **_tsetargv( int *argc, TCHAR *command_line );
;
; Note: The main array (__argv) is allocated in _targv.asm
;
include stdlib.inc
include string.inc
include malloc.inc
include tchar.inc

define MAXARGCOUNT 256
define MAXARGSIZE  0x8000  ; Max argument size: 32K

    .code

_tsetargv proc uses rsi rdi rbx argc:ptr int_t, cmdline:LPTSTR
ifdef __UNIX__
    int 3
else
  local argv[MAXARGCOUNT]:LPTSTR
  local buffer:LPTSTR
  local i:int_t

    ldr rcx,argc
    ldr rsi,cmdline

    mov dword ptr [rcx],0
    mov buffer,malloc(MAXARGSIZE*TCHAR)
    mov rdi,rax
    movzx eax,TCHAR ptr [rsi]
    add rsi,TCHAR

    .while eax

        xor ecx,ecx     ; Add a new argument
        xor edx,edx     ; "quote from start" in EDX - remove
        mov [rdi],cx

        .for ( : eax == ' ' || ( eax >= 9 && eax <= 13 ) : )
             _tlodsb
        .endf
        .break .if !eax ; end of command string

        .if eax == '"'
            _tlodsb
            inc edx
        .endif
        .while eax == '"' ; ""A" B"
            _tlodsb
            inc ecx
        .endw

        .while eax

            .break .if ( !edx && !ecx && ( eax == ' ' || ( eax >= 9 && eax <= 13 ) ) )

            .if eax == '"'
                .if ecx
                    dec ecx
                .elseif edx
                    movzx eax,TCHAR ptr [rsi]
                    .break .if ( eax == ' ' )
                    .break .if ( eax >= 9 && eax <= 13 )
                    dec edx
                .else
                    inc ecx
                .endif
            .else
                _tstosb
            .endif
            _tlodsb
        .endw

        xor ecx,ecx
        mov [rdi],ecx
        lea rbx,[rdi+TCHAR]
        mov rdi,buffer
        movzx ecx,TCHAR ptr [rdi]
       .break .if !ecx

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
endif
    ret

_tsetargv endp

    end
