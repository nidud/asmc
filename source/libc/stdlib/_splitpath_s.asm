; _SPLITPATH_S.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include string.inc
include errno.inc

.code

_splitpath_s proc uses rsi rdi rbx path:string_t,
    drive:string_t, max_drive:size_t,
    dir:string_t,   max_dir:size_t,
    fname:string_t, max_fname:size_t,
    ext:string_t,   max_ext:size_t

   .new endptr:string_t
   .new bEinval:int_t = 0

    ldr rbx,path
    .if ( rbx == NULL )
        jmp error_einval
    .endif
    ldr rcx,drive
    ldr rax,max_drive
    .if ( ( rcx && !rax ) || ( !rcx && rax ) )
        jmp error_einval
    .endif
    mov rcx,dir
    mov rax,max_dir
    .if ( ( rcx && !rax ) || ( !rcx && rax ) )
        jmp error_einval
    .endif
    mov rcx,fname
    mov rax,max_fname
    .if ( ( rcx && !rax ) || ( !rcx && rax ) )
        jmp error_einval
    .endif
    mov rcx,ext
    mov rax,max_ext
    .if ( ( rcx && !rax ) || ( !rcx && rax ) )
        jmp error_einval
    .endif

    mov rcx,drive
    .if ( ( rcx && max_drive < _MAX_DRIVE ) )
        jmp error_erange
    .endif
    mov ax,[rbx]
    .if ( ah == ':' )

        add rbx,2
        .if ( rcx )

            mov [rcx],ax
            add rcx,2
        .endif
    .endif
    .if ( rcx )
        mov byte ptr [rcx],0
    .endif

    .for ( edx=0, edi=0, esi=0, rcx=rbx :: rcx++ )

        mov al,[rcx]

        .break .if al == 0
        .if ( al == '\' || al == '/' )

            .if ( rdi == 0 )

                mov rdi,rcx
            .endif
            mov rsi,rcx
        .elseif ( al == '.' )
            mov rdx,rcx
        .endif
    .endf

    mov endptr,rcx
    mov rcx,dir

    .if ( rcx )

        mov rax,rsi
        sub rax,rdi
        add rax,2
        .if ( rax > max_dir )
            jmp error_erange
        .endif
        .while ( rdi < rsi )

            mov al,[rdi]
            mov [rcx],al
            inc rdi
            inc rcx
        .endw
        .if ( rsi )
            mov al,[rsi]
            mov [rcx],al
            inc rcx
        .endif
        mov byte ptr [rcx],0
    .endif

    mov rcx,ext
    .if ( rcx )

        mov eax,1
        .if ( rdx )

            mov rax,endptr
            sub rax,rdx
            inc eax
        .endif
        .if ( rax > max_ext )
            jmp error_erange
        .endif

        .if ( rdx )

            .for ( rdi = rdx :: rdi++, rcx++ )

                mov al,[rdi]
                mov [rcx],al
               .break .if ( al == 0 )
            .endf
        .endif
        mov byte ptr [rcx],0
    .endif

    mov rcx,fname
    .if ( rcx )

        .if ( rdx == 0 )
            mov rdx,endptr
        .endif
        .if ( rsi >= rbx )
            lea rbx,[rsi+1]
        .endif

        mov rax,rdx
        sub rax,rbx
        inc eax
        .if ( rax > max_fname )
            jmp error_erange
        .endif

        .while ( rbx < rdx )

            mov al,[rbx]
            mov [rcx],al
           .break .if ( al == 0 )
            inc rcx
            inc rbx
        .endw
        mov byte ptr [rcx],0
    .endif
    .return( 0 )

error_einval:
    mov bEinval,1

error_erange:
    xor eax,eax
    mov rcx,drive
    .if ( rcx && max_drive > 0 )
        mov [rcx],al
    .endif
    mov rcx,dir
    .if ( rcx && max_dir > 0 )
        mov [rcx],al
    .endif
    mov rcx,fname
    .if ( rcx && max_fname > 0 )
        mov [rcx],al
    .endif
    mov rcx,ext
    .if ( rcx && max_ext > 0 )
        mov [rcx],al
    .endif
    .if ( bEinval )
        _set_errno(EINVAL)
        mov eax,EINVAL
    .else
        _set_errno(ERANGE)
        mov eax,ERANGE
    .endif
    ret

_splitpath_s endp

    end
