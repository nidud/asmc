
; v2.31.24 .return float

ifndef __ASMC64__
    .x64
    .model flat, fastcall
endif
    .code

main proc

  local s:sword

    .return real2  ( 1.0 )
    .return real4  ( 1.0 )
    .return real8  ( 1.0 )
    .return real10 ( 1.0 )
    .return real16 ( 1.0 )

    .return 3C00r
    .return 3F800000r
    .return 3FF0000000000000r
    .return 3FFF8000000000000000r
    .return 3FFF0000000000000000000000000000r

    .return real2  ( 1.0 / 0.0 )
    .return real4  ( 1.0 / 0.0 )
    .return real8  ( 1.0 / 0.0 )
    .return real10 ( 1.0 / 0.0 )
    .return real16 ( 1.0 / 0.0 )

    .return 3C00r / 0.0
    .return 3C00r / 0000r
    .return 3F800000r / 0.0
    .return 3FF0000000000000r / 0.0
    .return 3FFF8000000000000000r / 0.0
    .return 3FFF0000000000000000000000000000r / 0.0

main endp

    end
