
include stdio.inc

%echo @CatStr(<MODEL >, %@Model, <, CODE >, %@CodeSize, <, DATA >, %@DataSize )

.code

main proc

    printf( "Hello World!\n" )
    .return( 0 )

main endp

    end
