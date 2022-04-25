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

   .new fh:uint_t
   .new name:string_t
   .new mode:uint_t

    mov eax,oflag
    and eax,O_RDONLY or O_WRONLY or O_RDWR

    .if ( !path ||
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
    .if !( oflag & O_BINARY )
        .if ( oflag & O_TEXT )
            or cl,FH_TEXT
        .elseif ( _fmode != O_BINARY ) ; check default mode
            or cl,FH_TEXT
        .endif
    .endif
    .if ( oflag & O_APPEND )
        or cl,FH_APPEND
    .endif
    mov fh,ecx

    .if ( oflag & O_CREAT )

        .if ( oflag & O_APPEND )

            mov name,path
            mov mode,edx

            sys_open(path, O_RDWR or O_APPEND, edx)
            .ifs ( eax < 0 )
                sys_creat(name, mode)
            .endif
        .else
            sys_creat(path, edx)
        .endif
    .else
        sys_open(path, oflag, 0)
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
