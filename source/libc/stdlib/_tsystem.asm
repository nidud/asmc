; _TSYSTEM.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include process.inc
ifndef __UNIX__
include string.inc
include winbase.inc
endif
include tchar.inc

    .code

_tsystem proc cmd:LPTSTR
ifdef __UNIX__
    _tspawnl( _P_WAIT, "/bin/sh", "sh", "-c", cmd, 0 )
else
   .new com[_MAX_PATH]:TCHAR

    _tcscpy( &com, "cmd.exe" )
    .if !GetEnvironmentVariable( "Comspec", &com, _MAX_PATH )

        SearchPath( 0, "cmd.exe", 0, _MAX_PATH, &com, 0 )
    .endif
    _tspawnl( _P_WAIT, &com, "cmd.exe", "/C", cmd, 0 )
endif
    ret
_tsystem endp

    end
