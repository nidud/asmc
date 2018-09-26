include intn.inc

_MAX equ 2

.code

main proc

  local n1[_MAX]
  local n2[_MAX]
  local n3[_MAX]
  local n4[_MAX]

    _atond(&n1, "1",  2, _MAX )
    _atond(&n2, "1",  8, _MAX )
    _atond(&n3, "1", 10, _MAX )
    _atond(&n4, "1", 16, _MAX )

    .assert( !_cmpnd(&n1, &n2, 1 ) )
    .assert( !_cmpnd(&n3, &n4, 1 ) )
    .assert( !_cmpnd(&n1, &n4, 1 ) )

    _atond(&n1, "-1", 10, 2 )
    .assert( n1 == -1 && n1[4] == -1 )

    _atond(&n1, "10000", 2, 1 )
    _atond(&n2, "20", 8, 1 )
    _atond(&n3, "16", 10, 1 )
    _atond(&n4, "10", 16, 1 )

    .assert( !_cmpnd(&n1, &n2, 1 ) )
    .assert( !_cmpnd(&n3, &n4, 1 ) )
    .assert( !_cmpnd(&n1, &n4, 1 ) )

    xor eax,eax
    ret

main endp

    end
