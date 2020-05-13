include stdio.inc
include stdlib.inc

    .code

compare proto :ptr, :ptr {
    cmp this,_1
    exitm<>
    }

sort proto :ptr, :ptr, :abs {
    _2(this, _1)
    exitm<>
    }

main proc

    sort(1, 2, compare)

    .return 0

main endp

    end
