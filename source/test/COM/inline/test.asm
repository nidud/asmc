include stdio.inc
include stdlib.inc

    .code

compare proto :ptr, :ptr {
    cmp this,_1
    }

sort proto :ptr, :ptr, :abs {
    _2(this, _1)
    }

main proc

    sort(1, 2, compare)

    .return 0

main endp

    end
