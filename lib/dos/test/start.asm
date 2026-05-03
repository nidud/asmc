
include dos.inc
include stdio.inc

.code

main proc

    printf( "DOS Version %d.%02d\n", _dosmajor, _dosminor )
    ret

main endp

    end
