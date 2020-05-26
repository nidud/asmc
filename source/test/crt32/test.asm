
; v2.31.35: WATCALL

include stdio.inc
include crtl.inc

return equ <.return>

    .code

main proc

   printf( "alldiv(10, 5): %lld\n", edx::alldiv(10, 5) )
   printf( "aulldiv(9, 5): %lld\n", edx::aulldiv(9, 5) )
   printf( "allmul(10, 5): %lld\n", edx::allmul(10, 5) )
   printf( "allrem(10, 5): %d\n", allrem(10, 5) )
   printf( "aullrem(9, 5): %d\n", aullrem(9, 5) )
   printf( "allshr(10, 2): %d\n", allshr(10, 2) )
   printf( "aullshr(9, 2): %d\n", aullshr(9, 2) )
   printf( "allshl(10, 2): %d\n", allshl(10, 2) )

   return( 0 )

main endp

    end
