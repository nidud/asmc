; _FILE.ASM--
; Copyright (C) 2015 Doszip Developers

include stdio.inc

	PUBLIC	_iob
	PUBLIC	stdout
	PUBLIC	stderr

	.data

_iob	S_FILE	<offset _bufin,0,offset _bufin,_IOREAD or _IOYOURBUF,0,_INTIOBUF,0>
stdout	S_FILE	<0,0,0,_IOWRT,1,0,0>	; stdout
stderr	S_FILE	<0,0,0,_IOWRT,2,0,0>	; stderr
	S_FILE	<0,0,0,0,-1,0,0>
	S_FILE	<0,0,0,0,-1,0,0>
	S_FILE	<0,0,0,0,-1,0,0>
	S_FILE	<0,0,0,0,-1,0,0>
	S_FILE	<0,0,0,0,-1,0,0>
	S_FILE	<0,0,0,0,-1,0,0>
	S_FILE	<0,0,0,0,-1,0,0>

	END
