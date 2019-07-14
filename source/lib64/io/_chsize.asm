; _CHSIZE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc

    .code

_chsize proc frame uses rdi rsi handle:int_t, new_size:qword

  local buffer[512]:char_t
  local current_offset:qword

    .return .if _lseek(ecx, 0, SEEK_CUR) == -1

    mov current_offset,rax

    .repeat

        .return .if _lseek(handle, 0, SEEK_END) == -1

        .if rax > new_size

            .return .if _lseek(handle, new_size, SEEK_SET) == -1

            ;
            ; Write zero byte at current file position
            ;
            oswrite(handle, &buffer, 0)
            .break
        .endif

        .break .ifz ; All done..

        mov r8,rax
        lea rdi,buffer
        xor rax,rax
        mov rcx,512/8
        rep stosq

        mov rdi,new_size
        sub rdi,r8

        .repeat
            mov rsi,512
            .if rdi < rsi

                mov rsi,rdi
                .break(1) .if !rdi
            .endif
            sub rdi,rsi
            oswrite(handle, &buffer, rsi)
        .until rax != rsi

        mov errno,ERROR_DISK_FULL
        .return -1

    .until 1

    .if _lseek(handle, current_offset, SEEK_SET) != -1
        xor eax,eax
    .endif
    ret

_chsize endp

    end
