; CHSIZE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
ifdef __UNIX__
include sys/syscall.inc
endif

    .code

ifdef __UNIX__

_chsize proc fd:int_t, size:size_t

    .ifsd ( sys_ftruncate( ldr(fd), ldr(size) ) < 0 )

        neg eax
        _set_errno( eax )
    .endif

else

_chsize proc uses rbx handle:int_t, new_size:size_t

  local buffer[512]:char_t
  local current_offset:size_t
  local extend:size_t

    .if ( _lseek( handle, 0, SEEK_CUR ) == -1 )
        .return
    .endif
    mov current_offset,rax

    .repeat

        .if ( _lseek( handle, 0, SEEK_END ) == -1 )
            .return
        .endif

        .if ( rax > new_size )

            .if ( _lseek( handle, new_size, SEEK_SET ) == -1 )
                .return
            .endif

            ;
            ; Write zero byte at current file position
            ;
            oswrite( handle, &buffer, 0 )
           .break
        .endif
        .break .ifz ; All done..

        mov rbx,rdi
        mov rdx,rax
        lea rdi,buffer
        xor eax,eax
        mov ecx,512/4
        rep stosd
        mov rdi,rbx

        mov rbx,new_size
        sub rbx,rdx

        .repeat

            mov extend,512
            .if ( rbx < extend )

                mov extend,rbx
                .break( 1 ) .if !rbx
            .endif

            sub rbx,extend
            oswrite( handle, &buffer, dword ptr extend )
        .until ( rax != extend )
        .return( _set_errno( ERROR_DISK_FULL ) )
    .until 1
    .if ( _lseek( handle, current_offset, SEEK_SET ) != -1 )
        xor eax,eax
    .endif
endif
    ret

_chsize endp

    end
