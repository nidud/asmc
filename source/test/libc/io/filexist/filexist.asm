; FILEXIST.ASM--
;
; int filexist(char *);
; int _wfilexist(wchar_t *);
;

include io.inc
include stdio.inc
include tchar.inc

.code

_tmain proc

    _tprintf("_tfilexist(" __func__ "):\t\t%d\n", _tfilexist(__func__))
    _tprintf("_tfilexist(" __FILE__ "):\t%d\n", _tfilexist(__FILE__))
    _tprintf("_tfilexist(../filexist):\t%d\n", _tfilexist("../filexist"))
    .return( 0 )

_tmain endp

    end
