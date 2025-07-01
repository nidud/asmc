
include stdio.inc
include errno.inc

    .code

main proc

   .new fp:ptr FILE = fopen( "fopen.txt", "w" )

    mov bx,ax
    movl es,dx

    .if ( ax != NULL )

        fprintf( fp, "fopen(\"fopen.txt\", \"w\") ._file: %d\n", esl[bx].FILE._file )
        fclose( fp )

        mov fp,fopen( "fopen.txt", "a" )
        .if ( ax != NULL )

            fprintf( fp, "appending\n" )
            fclose( fp )
        .else
            perror( "error fopen(a)" )
        .endif
    .else
        perror( "error fopen(w)" )
    .endif
    .return( 0 )

main endp

    end

