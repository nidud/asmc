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

_tsplitpath_s proc uses rsi rdi rbx path:LPTSTR,
    drive:LPTSTR, max_drive:size_t,
    dir:LPTSTR,   max_dir:size_t,
    fname:LPTSTR, max_fname:size_t,
    ext:LPTSTR,   max_ext:size_t

   .new endptr:LPTSTR
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

    .if ( TCHAR ptr [rbx+TCHAR] == ':' )

        .if ( rcx )

            mov [rcx],TCHAR ptr [rbx]
            mov TCHAR ptr [rcx+TCHAR],':'
            add rcx,TCHAR*2
        .endif
        add rbx,TCHAR*2
    .endif
    .if ( rcx )
        mov TCHAR ptr [rcx],0
    .endif

    .for ( edx=0, edi=0, esi=0, rcx=rbx :: rcx+=TCHAR )

        movzx eax,TCHAR ptr [rcx]

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
        add eax,TCHAR*2
        shr eax,TCHAR-1
        .if ( rax > max_dir )
            jmp error_erange
        .endif
        .while ( rdi < rsi )

            mov [rcx],TCHAR ptr [rdi]
            add rdi,TCHAR
            add rcx,TCHAR
        .endw
        .if ( rsi )
            mov [rcx],TCHAR ptr [rsi]
            add rcx,TCHAR
        .endif
        mov TCHAR ptr [rcx],0
    .endif

    mov rcx,ext
    .if ( rcx )

        mov eax,TCHAR
        .if ( rdx )

            mov rax,endptr
            sub rax,rdx
            add eax,TCHAR
        .endif
        shr eax,TCHAR-1
        .if ( rax > max_ext )
            jmp error_erange
        .endif

        .if ( rdx )

            .for ( eax=0, rdi=rdx :: rdi+=TCHAR, rcx+=TCHAR )

                mov [rcx],TCHAR ptr [rdi]
               .break .if ( eax == 0 )
            .endf
        .endif
        mov TCHAR ptr [rcx],0
    .endif

    mov rcx,fname
    .if ( rcx )

        .if ( rdx == 0 )
            mov rdx,endptr
        .endif
        .if ( rsi >= rbx )
            lea rbx,[rsi+TCHAR]
        .endif

        mov rax,rdx
        sub rax,rbx
        add eax,TCHAR
        shr eax,TCHAR-1
        .if ( rax > max_fname )
            jmp error_erange
        .endif

        xor eax,eax
        .while ( rbx < rdx )

            mov [rcx],TCHAR ptr [rbx]
           .break .if ( eax == 0 )
            add rcx,TCHAR
            add rbx,TCHAR
        .endw
        mov TCHAR ptr [rcx],0
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
