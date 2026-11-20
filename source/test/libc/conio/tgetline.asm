include string.inc
include conio.inc
include tchar.inc

.code

_tmain proc
   .new buffer[128]:tchar_t
%   _msgbox(
        MB_OK or MB_USERICON,
        __func__,
        "return value: %d",
        _tgetline(__FILE__, _tcscpy(&buffer, "&@Time &@Date"), 24, 128) )
    .return( 0 )
    endp

    end
