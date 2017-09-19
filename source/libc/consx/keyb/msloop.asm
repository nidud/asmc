include consx.inc

    .code

msloop proc

    .repeat
        mousep()
    .untilz
    ret

msloop endp

    END
