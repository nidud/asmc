
    _alldiv proto

    .code

_allrem::
__modti3::

    call    _alldiv
    xchg    r9,rdx
    xchg    r8,rax
    ret

    END
