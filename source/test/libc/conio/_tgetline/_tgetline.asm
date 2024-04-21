; _TGETLINE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include tchar.inc

.code

_tmain proc argc:int_t, argv:array_t

   .new buffer[128]:tchar_t

%   _msgbox(
        MB_OK or MB_USERICON,
        __func__,
        "return value: %d",
        _tgetline(__FILE__, _tcscpy(&buffer, "&@Time &@Date"), 24, 128) )
    .return( 0 )

_tmain endp

    end _tstart
