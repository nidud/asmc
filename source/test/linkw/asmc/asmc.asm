; ASMC.ASM--
;
; Linkw 3.01 and Asmc 2.37.73 update
;
include stdio.inc
include tchar.inc

.code

_tmain proc argc:int_t, argv:array_t
ifdef __PE__
    _tprintf("asmc -pe: %p\n", &main)
else
    _tprintf("asmc -MD: %p\n", &main)
endif
   .return(0)

_tmain endp

    end _tstart
