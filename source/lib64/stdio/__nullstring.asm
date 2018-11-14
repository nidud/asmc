; __NULLSTRING.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include stdio.inc

public __nullstring
public __wnullstring

    .data

    option wstring:on

    __nullstring  db "(null)",0
    __wnullstring dw "(null)",0

    end
