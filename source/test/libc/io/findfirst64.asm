include io.inc
include stdio.inc
include tchar.inc

ifdef _WIN64
define FORMAT <"%08X %08llX %08llX %08llX %8jd %s\n">
else
define FORMAT <"%08X %08X %08X %08X %8jd %s\n">
endif

.code
 _tmain proc argc:int_t, argv:tarray_t
    .new ff:_tfinddatai64_t
    .new h:intptr_t
    .if ( argc != 2 )
        .return( 0 )
    .endif
    mov rcx,argv
    mov h,_tfindfirsti64([rcx+size_t], &ff)
    _tprintf("_tfindfirsti64(): %d\n", h)
    .if ( h == -1 )
        .return( 1 )
    .endif
    .repeat
        _tprintf(FORMAT,
            ff.attrib,
            ff.time_create,
            ff.time_access,
            ff.time_write,
            ff.size,
            &ff.name )
    .untild _tfindnexti64(h, &ff)
    _tprintf("_findclose(): %d\n", _findclose(h))
    .return( 0 )
    endp
    end _tstart
