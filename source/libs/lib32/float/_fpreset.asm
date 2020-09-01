; _FPRESET.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
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
