; _WSPLITPATH_S.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include string.inc
include errno.inc

.code

_wsplitpath_s proc uses rsi rdi rbx path:wstring_t,
    drive:wstring_t, max_drive:size_t,
    dir:wstring_t,   max_dir:size_t,
    fname:wstring_t, max_fname:size_t,
    ext:wstring_t,   max_ext:size_t

   .new endptr:wstring_t
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
    mov dx,[rbx+2]
    .if ( dx == ':' )

        add rbx,4
        .if ( rcx )

            mov [rcx],ax
            mov [rcx+2],dx
            add rcx,4
        .endif
    .endif
    .if ( rcx )
        mov word ptr [rcx],0
    .endif

    .for ( edx=0, edi=0, esi=0, rcx=rbx :: rcx+=2 )

        mov ax,[rcx]

        .break .if ax == 0
        .if ( ax == '\' || ax == '/' )

            .if ( rdi == 0 )

                mov rdi,rcx
            .endif
            mov rsi,rcx
        .elseif ( ax == '.' )
            mov rdx,rcx
        .endif
    .endf

    mov endptr,rcx
    mov rcx,dir

    .if ( rcx )

        mov rax,rsi
        sub rax,rdi
        add eax,4
        shr eax,1
        .if ( rax > max_dir )
            jmp error_erange
        .endif
        .while ( rdi < rsi )

            mov ax,[rdi]
            mov [rcx],ax
            add rdi,2
            add rcx,2
        .endw
        .if ( rsi )
            mov ax,[rsi]
            mov [rcx],ax
            inc rcx
        .endif
        mov word ptr [rcx],0
    .endif

    mov rcx,ext
    .if ( rcx )

        mov eax,2
        .if ( rdx )

            mov rax,endptr
            sub rax,rdx
            add eax,2
        .endif
        shr eax,1
        .if ( rax > max_ext )
            jmp error_erange
        .endif

        .if ( rdx )

            .for ( rdi = rdx :: rdi+=2, rcx+=2 )

                mov ax,[rdi]
                mov [rcx],ax
               .break .if ( ax == 0 )
            .endf
        .endif
        mov word ptr [rcx],0
    .endif

    mov rcx,fname
    .if ( rcx )

        .if ( rdx == 0 )
            mov rdx,endptr
        .endif
        .if ( rsi >= rbx )
            lea rbx,[rsi+2]
        .endif

        mov rax,rdx
        sub rax,rbx
        add eax,2
        shr eax,1
        .if ( rax > max_fname )
            jmp error_erange
        .endif

        .while ( rbx < rdx )

            mov ax,[rbx]
            mov [rcx],ax
           .break .if ( ax == 0 )
            add rcx,2
            add rbx,2
        .endw
        mov word ptr [rcx],0
    .endif
    .return( 0 )

error_einval:
    mov bEinval,1

error_erange:
    xor eax,eax
    mov rcx,drive
    .if ( rcx && max_drive > 0 )
        mov [rcx],ax
    .endif
    mov rcx,dir
    .if ( rcx && max_dir > 0 )
        mov [rcx],ax
    .endif
    mov rcx,fname
    .if ( rcx && max_fname > 0 )
        mov [rcx],ax
    .endif
    mov rcx,ext
    .if ( rcx && max_ext > 0 )
        mov [rcx],ax
    .endif
    .if ( bEinval )
        _set_errno(EINVAL)
        mov eax,EINVAL
    .else
        _set_errno(ERANGE)
        mov eax,ERANGE
    .endif
    ret

_wsplitpath_s endp

    end
