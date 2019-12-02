; CONSOLE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc

    PUBLIC  console

    .data
    console dd CON_UBEEP or CON_MOUSE or CON_CLIPB

    END
