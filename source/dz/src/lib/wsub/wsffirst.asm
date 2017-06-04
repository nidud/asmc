include wsub.inc

	.code

wsffirst PROC wsub:PTR S_WSUB

	mov eax,wsub
	fbffirst([eax].S_WSUB.ws_fcb, [eax].S_WSUB.ws_count)
	ret

wsffirst ENDP

	END
