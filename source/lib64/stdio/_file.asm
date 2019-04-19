; _FILE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include crtl.inc

PUBLIC _iob
PUBLIC stdout
PUBLIC stderr

    .data

_iob	_iobuf <offset _bufin,0,offset _bufin,_IOREAD or _IOYOURBUF,0,_INTIOBUF,0>
stdout	_iobuf <0,0,0,_IOWRT,1,0,0>    ; stdout
stderr	_iobuf <0,0,0,_IOWRT,2,0,0>    ; stderr
_first	_iobuf _NSTREAM_ - 4 dup(<0,0,0,0,-1,0,0>)
_last	_iobuf <0,0,0,0,-1,0,0>

    .code

_stdioexit proc uses rsi

    lea rsi,_first
    .repeat
	.if [rsi]._iobuf._file != -1
	    fclose(rsi)
	.endif
	add rsi,sizeof(_iobuf)
	lea rax,_last
    .until rsi > rax
    ret

_stdioexit endp

.pragma(exit(_stdioexit, 1))

    END
