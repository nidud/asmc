
    _aulldiv proto

    .code

_aullrem::
__umodti3::

    call    _aulldiv
    xchg    r9,rdx
    xchg    r8,rax
    ret

    END
