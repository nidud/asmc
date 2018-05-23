    .486
    .model flat, c
    .code

_I8RS::

    mov ecx,ebx

_allshr::

    cmp cl,63
    ja  SIGN
    cmp cl,31
    ja  __I63
    shrd eax,edx,cl
    sar edx,cl
    ret
__I63:
    mov eax,edx
    sar edx,31
    and cl,31
    sar eax,cl
    ret
SIGN:
    sar edx,31
    mov eax,edx
    ret

    END
