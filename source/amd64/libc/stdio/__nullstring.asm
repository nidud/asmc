; __NULLSTRING.ASM--
; Copyright (C) 2017 Asmc Developers
;
include stdio.inc

public __nullstring
public __wnullstring

    .data

    option wstring:on

    __nullstring  db "(null)",0
    __wnullstring dw "(null)",0

    end
