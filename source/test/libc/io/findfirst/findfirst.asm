; FINDFIRST.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include stdio.inc
include tchar.inc

ifdef _WIN64
define format <"%08X %08llX %08llX %08llX %8d %s\n">
else
define format <"%08X %08X %08X %08X %8d %s\n">
endif

.code

_tmain proc argc:int_t, argv:tarray_t

    .new ff:_tfinddata_t
    .new h:intptr_t

    .if ( argc != 2 )
	.return( 0 )
    .endif

    mov rcx,argv
    mov h,_tfindfirst([rcx+size_t], &ff)
    _tprintf("_tfindfirst(): %d\n", h)
    .if ( h == -1 )
	.return( 1 )
    .endif

    .while 1

	_tprintf(format, ff.attrib, ff.time_create, ff.time_access, ff.time_write, ff.size, &ff.name)
	.break .ifd _tfindnext(h, &ff)
    .endw
    _tprintf("_findclose(): %d\n", _findclose(h))
    .return( 0 )

_tmain endp

    end _tstart
