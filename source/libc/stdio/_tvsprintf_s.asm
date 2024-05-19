; _TVSPRINTF_S.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include limits.inc
include errno.inc
include tchar.inc

    .code

_vstprintf_s proc string:LPTSTR, sizeInBytes:size_t, format:LPTSTR, vargs:ptr

  local o:_iobuf

    ldr rcx,string
    ldr rax,format
    ldr rdx,sizeInBytes

    .if ( rax == NULL || ( rcx == NULL && rdx > 0 ) )

        .return _set_errno(EINVAL)
    .endif
    .if ( rdx > INT_MAX )

        mov edx,INT_MAX
    .endif
ifdef _UNICODE
    add edx,edx
endif
    mov o._flag,_IOWRT or _IOSTRG
    mov o._cnt,edx
    mov o._ptr,rcx
    mov o._base,rcx
    _toutput(&o, rax, vargs)

    .if ( string != NULL )

        mov rcx,o._ptr
        .if ( o._cnt <= 0 )
            .if ( rcx > o._base )
                mov TCHAR ptr [rcx-TCHAR],0
            .endif
        .else
            mov TCHAR ptr [rcx],0
        .endif
    .endif
    ret

_vstprintf_s endp

    end
