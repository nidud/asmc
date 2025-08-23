; HEAPWALK.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc
include errno.inc
ifndef __UNIX__
include winbase.inc
endif

    .code

    assume rbx:ptr _HEAPINFO

_heapwalk proc uses rbx _entry:ptr _HEAPINFO
ifdef __UNIX__
   .return( _set_errno( ENOSYS ) )
else

   .new Entry:PROCESS_HEAP_ENTRY = { 0 }

    ldr rbx,_entry

    .if ( rbx == NULL )

        _set_errno( ENOSYS )
        .return( _HEAPBADPTR )
    .endif

    mov Entry.lpData,[rbx]._pentry
    .if ( rax == NULL )
        .ifd ( HeapWalk( _crtheap, &Entry ) == 0 )
            .return( _HEAPBADBEGIN )
        .endif
    .else

        .if ( [rbx]._useflag == _USEDENTRY )
            .ifd ( HeapValidate( _crtheap, 0, [rbx]._pentry ) == 0 )
                .return( _HEAPBADNODE )
            .endif
            mov Entry.wFlags,PROCESS_HEAP_ENTRY_BUSY
        .endif

nextBlock:

        .ifd !HeapWalk( _crtheap, &Entry )

            .if ( GetLastError() == ERROR_NO_MORE_ITEMS )
                .return( _HEAPEND )
            .endif
            .return( _HEAPBADNODE )
        .endif
    .endif

    .if ( Entry.wFlags & PROCESS_HEAP_ENTRY_BUSY )

        mov [rbx]._pentry,Entry.lpData
        mov [rbx]._size,Entry.cbData;
        mov [rbx]._useflag,_USEDENTRY
    .else
        jmp nextBlock
    .endif
    .return( _HEAPOK )
endif
_heapwalk endp

    end
