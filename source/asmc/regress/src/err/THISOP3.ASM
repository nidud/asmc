ifdef __ASMC__
option masm:on
endif

;--- if EQU THIS is used outside of a segment, an error
;--- is to be displayed!

E1	equ THIS dword

end
