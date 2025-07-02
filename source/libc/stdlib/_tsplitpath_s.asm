; _TSPLITPATH_S.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include string.inc
include errno.inc
include tchar.inc

.code

_tsplitpath_s proc uses rsi rdi rbx path:tstring_t,
    drive:tstring_t, max_drive:size_t,
    dir:tstring_t,   max_dir:size_t,
    fname:tstring_t, max_fname:size_t,
    ext:tstring_t,   max_ext:size_t

   .new endptr:tstring_t
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

    .if ( tchar_t ptr [rbx+tchar_t] == ':' )

        .if ( rcx )

            mov [rcx],tchar_t ptr [rbx]
            mov tchar_t ptr [rcx+tchar_t],':'
            add rcx,tchar_t*2
        .endif
        add rbx,tchar_t*2
    .endif
    .if ( rcx )
        mov tchar_t ptr [rcx],0
    .endif

    .for ( edx=0, edi=0, esi=0, rcx=rbx :: rcx+=tchar_t )

        movzx eax,tchar_t ptr [rcx]

        .break .if eax == 0
        .if ( eax == '\' || eax == '/' )

            .if ( rdi == 0 )

                mov rdi,rcx
            .endif
            mov rsi,rcx
        .elseif ( eax == '.' )
            mov rdx,rcx
        .endif
    .endf

    mov endptr,rcx
    mov rcx,dir

    .if ( rcx )

        mov rax,rsi
        sub rax,rdi
        add eax,tchar_t*2
        shr eax,tchar_t-1
        .if ( rax > max_dir )
            jmp error_erange
        .endif
        .while ( rdi < rsi )

            mov [rcx],tchar_t ptr [rdi]
            add rdi,tchar_t
            add rcx,tchar_t
        .endw
        .if ( rsi )
            mov [rcx],tchar_t ptr [rsi]
            add rcx,tchar_t
        .endif
        mov tchar_t ptr [rcx],0
    .endif

    mov rcx,ext
    .if ( rcx )

        mov eax,tchar_t
        .if ( rdx )

            mov rax,endptr
            sub rax,rdx
            add eax,tchar_t
        .endif
        shr eax,tchar_t-1
        .if ( rax > max_ext )
            jmp error_erange
        .endif

        .if ( rdx )

            .for ( eax=0, rdi=rdx :: rdi+=tchar_t, rcx+=tchar_t )

                mov [rcx],tchar_t ptr [rdi]
               .break .if ( eax == 0 )
            .endf
        .endif
        mov tchar_t ptr [rcx],0
    .endif

    mov rcx,fname
    .if ( rcx )

        .if ( rdx == 0 )
            mov rdx,endptr
        .endif
        .if ( rsi >= rbx )
            lea rbx,[rsi+tchar_t]
        .endif

        mov rax,rdx
        sub rax,rbx
        add eax,tchar_t
        shr eax,tchar_t-1
        .if ( rax > max_fname )
            jmp error_erange
        .endif

        xor eax,eax
        .while ( rbx < rdx )

            mov [rcx],tchar_t ptr [rbx]
           .break .if ( eax == 0 )
            add rcx,tchar_t
            add rbx,tchar_t
        .endw
        mov tchar_t ptr [rcx],0
    .endif
    .return( 0 )

error_einval:
    mov bEinval,1
ifdef _UNICODE
define _al <ax>
else
define _al <al>
endif
error_erange:
    xor eax,eax
    mov rcx,drive
    .if ( rcx && max_drive > 0 )
        mov [rcx],_al
    .endif
    mov rcx,dir
    .if ( rcx && max_dir > 0 )
        mov [rcx],_al
    .endif
    mov rcx,fname
    .if ( rcx && max_fname > 0 )
        mov [rcx],_al
    .endif
    mov rcx,ext
    .if ( rcx && max_ext > 0 )
        mov [rcx],_al
    .endif
    .if ( bEinval )
        _set_errno(EINVAL)
        mov eax,EINVAL
    .else
        _set_errno(ERANGE)
        mov eax,ERANGE
    .endif
    ret

_tsplitpath_s endp

    end
