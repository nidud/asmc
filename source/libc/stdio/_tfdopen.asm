; _TFDOPEN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; FILE *_fdopen(int filedes, char *mode);
; FILE *_wfdopen(int filedes, wchar_t *mode);
;

include io.inc
include stdio.inc
include errno.inc
include tchar.inc

.code

_tfdopen proc uses rsi rdi rbx filedes:int_t, mode:tstring_t

    ldr ecx,filedes
    ldr rdx,mode

    .if ( rdx == NULL )

        _set_errno( EINVAL )
        .return( NULL )
    .endif

    .ifs ( ecx < 0 || ecx > _nfile || !( _osfile(ecx) & FOPEN ) )

        _set_errno( EBADF )
        .return( NULL )
    .endif

    ; Skip leading spaces

    .while ( tchar_t ptr [rdx] == ' ' )
        add rdx,tchar_t
    .endw
    movzx eax,tchar_t ptr [rdx]

    ; First character must be 'r', 'w', or 'a'.

    .switch eax
    .case 'r'
        mov ebx,_IOREAD
       .endc
    .case 'w'
    .case 'a'
        mov ebx,_IOWRT
       .endc
    .default
        _set_errno( EINVAL )
        .return( NULL )
    .endsw
    or ebx,_commode

    ; There can be up to three more optional characters:
    ; (1) A single '+' character,
    ; (2) One of 'b' and 't' and
    ; (3) One of 'c' and 'n'.
    ;
    ; Note that currently, the 't' and 'b' flags are syntax checked
    ; but ignored.  'c' and 'n', however, are correctly supported.

    xor esi,esi
    xor edi,edi
    add rdx,tchar_t
    movzx eax,tchar_t ptr [rdx]

    .while eax

        .switch pascal eax
        .case ' '
        .case '+'
            .break .if ( ebx & _IORW )
            or  ebx,_IORW
            and ebx,not (_IOREAD or _IOWRT)
        .case 't'
        .case 'b'
            .break .if ( esi )
            inc esi
        .case 'c'
            .break .if ( edi )
            inc edi
            or  ebx,_IOCOMMIT
        .case 'n'
            .break .if ( edi )
            inc edi
            and ebx,not _IOCOMMIT
        .default
            _set_errno( EINVAL )
            .return( NULL )
        .endsw
        add rdx,tchar_t
        movzx eax,tchar_t ptr [rdx]
    .endw
    .while ( tchar_t ptr [rdx] == ' ' )
        add rdx,tchar_t
    .endw
    .if ( tchar_t ptr [rdx] )

        _set_errno( EINVAL )
        .return( NULL )
    .endif
    mov esi,ecx

    ; Find a free stream; stream is returned 'locked'.

    .if ( _getst() == NULL )

        _set_errno( EMFILE )
        .return( NULL )
    .endif
    mov [rax].FILE._flag,ebx
    mov [rax].FILE._file,esi
    ret

_tfdopen endp

    end
