;
; v2.21 added inline .assert() function
;
; .ASSERT:<[ON|OFF|PUSH|POP|PUSHF|POPF|CODE|ENDS|<handler>]>
;
IFNDEF	_WIN64
	.x64
	.model	flat, fastcall
ENDIF
	.code

assert:
;	pop	rax	; IP of caller and message
;	printf( "%s\n", rax )
;	exit( 1 )

foo	proc a, b
	mov	eax,ecx
	ret
foo	endp

	.assert:push	; save flags: OPTION ASMC:01..80h (0..7)

	.assert:off	; assert off
	.assert:code	; insert code - IF 0
	pop	rax	; skip if off..
	.assert:ends	; - ENDIF
	.assert:on	; on

	.assert:assert	; set handler

	.assert rax	; test rax
	.assert:pushf	; set flag 40: use pushfd/q
	.assert rax	; test rax
	.assert:popf	; clear flag

	.assert rax > 2 && rdx
	.assert rax == 2 || ebx || dx > cx

	.assert foo(1, "\n")

	.assert foo(-1,0) == -1	 ; cmp 00000000FFFFFFFF,FFFFFFFFFFFFFFFF
	.assertd foo(-1,0) == -1 ; cmp FFFFFFFF,FFFFFFFF
	.assertw foo(-1,0) == -1 ; cmp FFFF,FFFF
	.assertb foo(-1,0) == -1 ; cmp FF,FF

	.assert:pop	; restore flags

	end
