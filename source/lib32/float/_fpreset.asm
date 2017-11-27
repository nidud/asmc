; _FPRESET.ASM--
; Copyright (C) 2017 Asmc Developers
;
include float.inc
include winbase.inc

.code

_fpreset proc __cdecl

  local cw:word

    mov cw,0x027F

    fninit
    fldcw cw

    .if IsProcessorFeaturePresent(PF_XMMI64_INSTRUCTIONS_AVAILABLE)

        mov cw,0x1F80
        fldcw cw
    .endif
    ret

_fpreset endp

    end
