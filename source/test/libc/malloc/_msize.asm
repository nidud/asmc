; _MSIZE.ASM--
;
; This program allocates a block of memory for
; buffer and then uses _msize to display the size of that
; block. Next, it uses realloc to expand the amount of
; memory used by buffer and then calls _msize again to
; display the new amount of memory allocated to buffer.
;

include stdio.inc
include malloc.inc
include stdlib.inc

.code

main proc

    .new buffer:ptr long_t = malloc( 1000 * sizeof( long_t ) )
    .new size:size_t

    .if ( buffer == NULL )
        exit( 1 )
    .endif
    mov size,_msize( buffer )
    printf( "Size of block after malloc of 1000 longs: %u\n", size )

    ; Reallocate and show new size:

    mov rdx,size
    add rdx,1000 * sizeof( long_t )
    .if ( realloc( buffer, rdx ) == NULL )

        free( buffer ) ; free original block
        exit( 1 )
    .endif
    mov buffer,rax
    mov size,_msize( buffer )
    printf( "Size of block after realloc of 1000 more longs: %u\n", size )
    free( buffer )
    exit( 0 )
    endp

    end
