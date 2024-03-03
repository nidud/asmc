
; v2.31.35: WATCALL

include stdio.inc
include stdlib.inc
include tchar.inc

    .code

_tmain proc

   _tprintf( "alldiv(10, 5): %lld\n", rdx::alldiv(10, 5) )
   _tprintf( "aulldiv(9, 5): %lld\n", rdx::aulldiv(9, 5) )
   _tprintf( "allmul(10, 5): %lld\n", rdx::allmul(10, 5) )
   _tprintf( "allrem(10, 5): %d\n", allrem(10, 5) )
   _tprintf( "aullrem(9, 5): %d\n", aullrem(9, 5) )
   _tprintf( "allshr(10, 2): %d\n", allshr(10, 2) )
   _tprintf( "aullshr(9, 2): %d\n", aullshr(9, 2) )
   _tprintf( "allshl(10, 2): %d\n", allshl(10, 2) )

   .return( 0 )

_tmain endp

    end
