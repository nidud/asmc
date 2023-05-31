; _CHSIZE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc

    .code

_chsize proc uses rdi rsi handle:int_t, new_size:size_t
ifdef __UNIX__
    _set_errno( ENOSYS )
    mov eax,-1
else

  local buffer[512]:char_t
  local current_offset:intptr_t
  local NumberOfBytesWritten:intptr_t

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

        mov rdx,rax
        lea rdi,buffer
        xor eax,eax
        mov ecx,512/4
        rep stosd

        mov rdi,new_size
        sub rdi,rdx

        .repeat

            mov esi,512
            .if ( rdi < rsi )

                mov rsi,rdi
                .break( 1 ) .if !rdi
            .endif

            sub rdi,rsi
            oswrite( handle, &buffer, esi )

        .until ( rax != rsi )

        _set_errno( ERROR_DISK_FULL )
        .return -1
    .until 1

    .if ( _lseek( handle, current_offset, SEEK_SET ) != -1 )
        xor eax,eax
    .endif
endif
    ret

_chsize endp

    end
