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

        _set_errno(EINVAL)
        .return(-1)
    .endif

    .if ( ecx >= _NFILE_ )

        _set_errno(EBADF)
        .return(-1)
    .endif

    lea rbx,_osfile
    lea rax,_textmode
    add rbx,rcx
    add rcx,rax

    mov al,[rbx]
    mov ah,[rcx]
    and al,FTEXT

    .switch edx
    .case _O_BINARY
        and byte ptr [rbx],not FTEXT
       .endc
    .case _O_TEXT
        or  byte ptr [rbx],FTEXT
        mov byte ptr [rcx],__IOINFO_TM_ANSI
       .endc
    .case _O_U8TEXT
        or  byte ptr [rbx],FTEXT
        mov byte ptr [rcx],__IOINFO_TM_UTF8
       .endc
    .case _O_U16TEXT
    .case _O_WTEXT
        or  byte ptr [rbx],FTEXT
        mov byte ptr [rcx],__IOINFO_TM_UTF16LE
       .endc
    .endsw

    .if ( al == 0 )
        .return(_O_BINARY)
    .endif
    .if ( ah == __IOINFO_TM_ANSI )
        .return(_O_TEXT)
    .else
        .return(_O_WTEXT)
    .endif
    ret

_setmode endp

    end
