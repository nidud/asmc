; OPEN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
include fcntl.inc
include linux/kernel.inc

externdef _fmode:uint_t

    .code

    option win64:noauto ; skip the vararg stack

open proc path:string_t, oflag:int_t, args:vararg

   .new name:string_t
   .new mode:uint_t
   .new fh:uint_t

    mov eax,esi
    and eax,O_RDONLY or O_WRONLY or O_RDWR

    .if ( !rdi ||
          ( eax != O_RDONLY &&
            eax != O_WRONLY &&
            eax != O_RDWR ) )

        _set_errno(EINVAL)
        .return -1
    .endif

    mov ecx,FH_OPEN
    ;
    ; figure out binary/text mode
    ;
    .if !( esi & O_BINARY )
        .if ( esi & O_TEXT )
            or cl,FH_TEXT
        .elseif ( _fmode != O_BINARY ) ; check default mode
            or cl,FH_TEXT
        .endif
    .endif
    .if ( esi & O_APPEND )
        or cl,FH_APPEND
    .endif
    mov fh,ecx

    .if ( esi & O_CREAT )

        .if ( esi & O_APPEND )

            mov name,rdi
            mov mode,edx

            sys_open(rdi, O_RDWR or O_APPEND, edx)
            .ifs ( eax < 0 )
                sys_creat(name, mode)
            .endif
        .else
            sys_creat(rdi, edx)
        .endif
    .else
        sys_open(rdi, esi, 0)
    .endif
    .ifs ( eax < 0 )

        neg eax
        _set_errno(eax)
        .return -1
    .endif
    mov edx,fh
    lea rcx,_osfile
    mov [rax+rcx],dl
    ret

open endp

    end
