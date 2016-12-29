include stdio.inc
include crtl.inc

PUBLIC	_iob
PUBLIC	stdout
PUBLIC	stderr

	.data

_iob	S_FILE	<offset _bufin,0,offset _bufin,_IOREAD or _IOYOURBUF,0,_INTIOBUF,0>
stdout	S_FILE	<0,0,0,_IOWRT,1,0,0>	; stdout
stderr	S_FILE	<0,0,0,_IOWRT,2,0,0>	; stderr
_first	S_FILE	_NSTREAM_ - 4 dup(<0,0,0,0,-1,0,0>)
_last	S_FILE	<0,0,0,0,-1,0,0>

	.code

_stdioexit:
	push	esi
	lea	esi,_first
	.repeat
		.if	[esi].S_FILE.iob_file != -1

			fclose( esi )
		.endif
		add esi,SIZE S_FILE
	.until	esi > offset _last
	pop	esi
	ret

pragma_exit _stdioexit, 1

	END
