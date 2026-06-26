
	.286
	.model small
	.stack 1024

	.code

;--- first operand must accept ES: override only
;--- fixed since v2.14
if 0
	movs byte ptr cs:[di],[si]
	movs byte ptr ds:[di],[si]
	movs byte ptr es:[di],[si]  ;ok
	movs byte ptr ss:[di],[si]
endif
	movs byte ptr cs:[di],ds:[si]
	movs byte ptr ds:[di],ds:[si]
	movs byte ptr es:[di],ds:[si]	;ok
	movs byte ptr ss:[di],ds:[si]
	movs byte ptr cs:[di],cs:[si]
	movs byte ptr ds:[di],cs:[si]
	movs byte ptr es:[di],cs:[si]	;ok
	movs byte ptr ss:[di],cs:[si]

start:
	mov ah,4ch
	int 21h

	end start
