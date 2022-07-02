; _FILE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include crtl.inc

public	_iob
public	stdout
public	stderr
public	_bufin
public	__lookuptable

    .data

_bufin	db _INTIOBUF dup(0)
_iob	_iobuf <_bufin,0,_bufin,_IOREAD or _IOYOURBUF,0,_INTIOBUF,0>
stdout	_iobuf <0,0,0,_IOWRT,1,0,0>    ; stdout
stderr	_iobuf <0,0,0,_IOWRT,2,0,0>    ; stderr
_first	_iobuf _NSTREAM_ - 4 dup(<0,0,0,0,-1,0,0>)
_last	_iobuf <0,0,0,0,-1,0,0>

__lookuptable label byte
    db 06h, 00h, 00h, 06h, 00h, 01h, 00h, 00h ;	 !"#$%&' 20 00
    db 10h, 00h, 03h, 06h, 00h, 06h, 02h, 10h ; ()*+,-./ 28 08
    db 04h, 45h, 45h, 45h, 05h, 05h, 05h, 05h ; 01234567 30 10
    db 05h, 35h, 30h, 00h, 50h, 00h, 00h, 00h ; 89:;<=>? 38 18
    db 00h, 28h, 28h, 38h, 50h, 58h, 07h, 08h ; @ABCDEFG 40 20
    db 00h, 37h, 30h, 30h, 57h, 50h, 07h, 00h ; HIJKLMNO 48 28
    db 00h, 20h, 20h, 08h, 00h, 00h, 00h, 00h ; PQRSTUVW 50 30
    db 08h, 60h, 68h, 60h, 60h, 60h, 60h, 00h ; XYZ[\]^_ 58 38
    db 00h, 78h, 78h, 78h, 78h, 78h, 78h, 08h ; `abcdefg 60 40
    db 07h, 08h, 00h, 00h, 07h, 00h, 08h, 08h ; hijklmno 68 48
    db 08h, 00h, 00h, 08h, 00h, 08h, 00h, 07h ; pqrstuvw 70 50
    db 08h				      ; xyz{|}~	 78 58

    .code

_stdioexit proc uses rsi

    lea rsi,_first
    .repeat
	.if ( [rsi]._iobuf._file != -1 )
	    fclose(rsi)
	.endif
	add rsi,sizeof(_iobuf)
	lea rax,_last
    .until ( rsi > rax )
    ret

_stdioexit endp

.pragma(exit(_stdioexit, 1))

    end
