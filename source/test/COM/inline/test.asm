include stdio.inc
include stdlib.inc

    .code

compare proto :ptr, :ptr {
    cmp _1,_2
    }

sort proto :ptr, :ptr, :abs {
    _3(_1, _2)
    }

main proc

    sort(1, 2, compare)

    .return 0

main endp

    end
