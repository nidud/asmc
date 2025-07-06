include stdio.inc
include stdlib.inc

.code

main proc

    printf( "TEMP: %s\n", ldr( getenv("TEMP") ) )
    printf( "PATH: %s\n", ldr( getenv("PATH") ) )
   .return( 0 )

main endp

    end
