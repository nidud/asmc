;
; v2.27 - ZERO? || CARRY? --> LE
;
    .386
    .model flat
    .code

    .if ZERO? || CARRY?	    ; LE - below or equal
	nop
    .endif
    .if !(ZERO? || CARRY?)  ; GT - above
	nop
    .endif
    .if ZERO? && CARRY?
	nop
    .endif

    end

; ----- old

	jz	?_001
	jnc	?_002
?_001:	nop
?_002:	jz	?_003
	jc	?_003
	nop
?_003:	jnz	?_004
	jnc	?_004
	nop

; ----- new

	ja	?_001
	nop
?_001:	jbe	?_002
	nop
?_002:	ja	?_003
	nop
