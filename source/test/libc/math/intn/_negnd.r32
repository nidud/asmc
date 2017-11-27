include intn.inc

.code

main proc
local n[8]

    _atond(&n, "1",  2, 8 )
    _negnd(&n, 1)
    .assert( n == -1 )
    _negnd(&n, 1)
    .assert( n == 1 )
    _negnd(&n, 2)
    .assert( n == -1 && n[4] == -1 )

    _atond(&n, "-1", 10, 2 )
    .assert( n == -1 && n[4] == -1 )
    _negnd(&n, 2)
    .assert( n == 1 && n[4] == 0 )

    xor eax,eax
    ret

main endp

    end
