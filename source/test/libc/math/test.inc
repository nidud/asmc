include math.inc
include stdio.inc
include tchar.inc

define INFO @CatStr(<!">, %_LIB_STEM, <!">)

    .code

_tmain proc

  local x:real8

    FUNC(VALUE)
ifdef _WIN64
ifdef ISFLOAT
    cvtss2sd xmm0,xmm0
endif
    movsd x,xmm0
else
    fstp x
endif
    _tprintf("%.14f " INFO " (%d)\n", x, size_t*8)
    xor eax,eax
    ret
    endp

    end _tstart
