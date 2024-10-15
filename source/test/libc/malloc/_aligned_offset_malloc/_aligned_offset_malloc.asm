; _ALIGNED_OFFSET_MALLOC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include stdio.inc
include malloc.inc
include assert.inc
include tchar.inc

.assert:on

.code

_tmain proc

    .new offs:size_t = 25
    .new alignments[10]:size_t = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512 }
    .new address[10]:ptr

    .for ( ebx = 0 : ebx < lengthof( alignments ) : ++ebx )

        _aligned_offset_malloc( 1024, alignments[rbx*size_t], offs )
        mov address[rbx*size_t],rax
        add rax,offs
        mov rcx,alignments[rbx*size_t]
        dec rcx
       .assert( !( rax & rcx ) )
    .endf
    .for ( ebx = 0 : ebx < lengthof( address ) : ++ebx )

        _aligned_free( address[rbx*size_t] )
    .endf
    .return( 0 )

_tmain endp

    end _tstart
