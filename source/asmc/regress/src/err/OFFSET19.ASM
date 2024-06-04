
;--- v2.17: now always error "constant value too large" is displayed
;---        if offset/displacement exceeds 32-bit.
;---        for stack variables, no check was done before v2.17!

	.386
	.model flat

	.code

p1 proc
local l1[123456789h]:byte
	ret
p1 endp


	end
