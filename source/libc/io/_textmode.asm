; _TEXTMODE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc

    .data
    _textmode db _NFILE_ dup(__IOINFO_TM_ANSI)

    end
