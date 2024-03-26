; _SETMODE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include fcntl.inc
include errno.inc

    .code

_setmode proc uses rbx fd:int_t, mode:int_t

    ldr ecx,fd
    ldr edx,mode

    .if !( edx == _O_TEXT   ||
           edx == _O_BINARY ||
           edx == _O_WTEXT  ||
           edx == _O_U8TEXT ||
           edx == _O_U16TEXT )

        .return( _set_errno( EINVAL ) )
    .endif

    .if ( ecx >= _NFILE_ )

        .return( _set_errno( EBADF ) )
    .endif

    assume rbx:pioinfo

    mov rbx,_pioinfo(ecx)
    mov al,[rbx].osfile
    mov ah,[rbx].textmode
    and al,FTEXT

    .switch edx
    .case _O_BINARY
        and [rbx].osfile,not FTEXT
       .endc
    .case _O_TEXT
        or  [rbx].osfile,FTEXT
        mov [rbx].textmode,__IOINFO_TM_ANSI
       .endc
    .case _O_U8TEXT
        or  [rbx].osfile,FTEXT
        mov [rbx].textmode,__IOINFO_TM_UTF8
       .endc
    .case _O_U16TEXT
    .case _O_WTEXT
        or  [rbx].osfile,FTEXT
        mov [rbx].textmode,__IOINFO_TM_UTF16LE
       .endc
    .endsw

    .if ( al == 0 )
        mov eax,_O_BINARY
    .elseif ( ah == __IOINFO_TM_ANSI )
        mov eax,_O_TEXT
    .else
        mov eax,_O_WTEXT
    .endif
    ret

_setmode endp

    end
