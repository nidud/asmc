IFNDEF	_WIN64
	.x64
	.model	flat, fastcall
ENDIF
	.code

	mov	rax,-1 ; FFFFFFFFFFFFFFFF
	mov	eax,-1 ; 00000000FFFFFFFF
	cmp	rax,-1 ; FFFFFFFFFFFFFFFF

	.assert:on

assert_exit:
	mov	eax,-1
	ret

	.if	assert_exit() == -1 ; cmp 00000000FFFFFFFF,FFFFFFFFFFFFFFFF
	.endif
	.ifd	assert_exit() == -1 ; cmp FFFFFFFF,FFFFFFFF
	.endif
	.ifw	assert_exit() == -1 ; cmp FFFF,FFFF
	.endif
	.ifb	assert_exit() == -1 ; cmp FF,FF
	.endif

	.assert	 assert_exit() != -1 ; fail
	.assertd assert_exit() != -1
	.assertw assert_exit() != -1
	.assertb assert_exit() != -1

	END	assert_exit

