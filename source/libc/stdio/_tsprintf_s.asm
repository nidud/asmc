; _TSPRINTF_S.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include limits.inc
include errno.inc
include tchar.inc

    .code

_stprintf_s proc string:LPTSTR, sizeInWords:size_t, format:LPTSTR, argptr:vararg

  local o:_iobuf

    ldr rcx,string
    ldr rdx,sizeInWords

    .if ( !( rcx != NULL || rdx == 0 ) || format == NULL )

        .return( _set_errno( EINVAL ) )
    .endif

    mov o._flag,_IOWRT or _IOSTRG
    mov o._ptr,rcx
    mov o._base,rcx
    mov o._cnt,INT_MAX

    .if ( rdx <= INT_MAX/TCHAR )

        lea eax,[rdx*TCHAR]
        mov o._cnt,eax
    .endif

    _toutput(&o, format, &argptr)

    .return .if ( string == NULL )

    mov rcx,o._ptr
    mov TCHAR ptr [rcx],0
    ret

_stprintf_s endp

    end
