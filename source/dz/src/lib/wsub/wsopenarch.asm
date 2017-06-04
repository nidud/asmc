include string.inc
include io.inc
include errno.inc
include wsub.inc

	.code

wsopenarch PROC wsub:PTR S_WSUB

  local arcname[1024]:BYTE

	mov	edx,wsub
	.if	osopen(
		strfcat(
			addr arcname,
			[edx].S_WSUB.ws_path,
			[edx].S_WSUB.ws_file ),
		_A_ARCH,
		M_RDONLY, A_OPEN ) == -1

		eropen( addr arcname )
	.endif
	ret

wsopenarch ENDP

	END
