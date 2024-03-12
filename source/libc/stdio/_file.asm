; _FILE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

.data
if defined(_WIN64) or not defined(__UNIX__)
_iob    _iobuf <_bufin, 0, _bufin, _IOREAD or _IOYOURBUF, 0, 0, _INTIOBUF, NULL>
_stdout _iobuf <0, 0, 0, _IOWRT, 1, 0, 0, NULL>
_stderr _iobuf <0, 0, 0, _IOWRT, 2, 0, 0, NULL>
_first  _iobuf _NSTREAM_ - 4 dup(<NULL, 0, NULL, 0, -1, 0, 0, NULL>)
_last   _iobuf <NULL, 0, NULL, 0, -1, 0, 0, NULL>
else
_iob    _iobuf <_bufin, 0, _bufin, _IOREAD or _IOYOURBUF, 0, _INTIOBUF, NULL>
_stdout _iobuf <0, 0, 0, _IOWRT, 1, 0, NULL>
_stderr _iobuf <0, 0, 0, _IOWRT, 2, 0, NULL>
_first  _iobuf _NSTREAM_ - 4 dup(<NULL, 0, NULL, 0, -1, 0, NULL>)
_last   _iobuf <NULL, 0, NULL, 0, -1, 0, NULL>
endif

align   size_t
stdin   LPFILE _iob
stdout  LPFILE _stdout
stderr  LPFILE _stderr

.code

_stdioexit proc uses rbx

    lea rbx,_first
    .repeat
        .if ( [rbx]._iobuf._file != -1 )
            fclose(rbx)
        .endif
        add rbx,sizeof(_iobuf)
        lea rax,_last
    .until ( rbx > rax )
    ret

_stdioexit endp

.pragma exit(_stdioexit, 98)

    end
