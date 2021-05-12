;
; v2.31 .return directive
;
ifndef __ASMC64__
    .x64
    .model flat, fastcall
endif
    .code

main proc

  local s:sword

    .return s

main endp

    end
