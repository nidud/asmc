; _WRITE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
include winbase.inc

LF          equ 10
CR          equ 13
CTRLZ       equ 26
BUF_SIZE    equ 1025 ; size of LF translation buffer

.code

_write proc uses rdi rsi rbx fh:int_t, buf:ptr, cnt:uint_t

  local lfcount:int_t           ; count of line feeds
  local charcount:int_t         ; count of chars written so far
  local dosretval:ulong_t       ; o.s. return value
  local written:int_t           ; count of chars written on this write
  local lfbuf[BUF_SIZE]:char_t  ; lf translation buffer
  local file:char_t

    mov eax,r8d                 ; cnt
    .return .if !eax            ; nothing to do

    .if ( ecx >= _NFILE_ )      ; validate handle
                                ; out of range -- return error
        _set_doserrno(0)        ; not o.s. error
        _set_errno(EBADF)
        .return -1
    .endif

    lea rdx,_osfhnd
    mov rbx,[rdx+rcx*8]
    lea rdx,_osfile
    mov al,[rdx+rcx]
    mov file,al

    .if ( al & FH_APPEND )      ; appending - seek to end of file; ignore error, because maybe
                                ; file doesn't allow seeking
        _lseek(ecx, 0, SEEK_END)
    .endif

    mov lfcount,0
    mov charcount,0

    ; check for text mode with LF's in the buffer

    .if ( file & FH_TEXT )

        mov rsi,buf             ; start at beginning of buffer
        mov dosretval,0         ; no OS error yet

        .while 1

            mov rax,rsi
            sub rax,buf
            .break .if eax >= cnt

            lea rdi,lfbuf       ; start at beginning of lfbuf
            mov rdx,rdi

            .while 1            ; fill the lf buf, except maybe last char

                mov rax,rdi
                sub rax,rdx
                .break .if eax >= BUF_SIZE - 1
                mov rax,rsi
                sub rax,buf
                .break .if eax >= cnt
                lodsb
                .if al == LF
                    inc lfcount
                    mov byte ptr [rdi],CR
                    inc rdi
                .endif
                stosb
            .endw

            mov r8,rdi
            sub r8,rdx

            .if WriteFile(rbx, rdx, r8d, &written, NULL)

                add charcount,written

                lea rcx,lfbuf
                mov rdx,rdi
                sub rdx,rcx
                .break .if ( eax < edx )

            .else

                mov dosretval,GetLastError()
                .break
            .endif
        .endw

    .else

        ; binary mode, no translation

        .if WriteFile(rbx, buf, cnt, &written, NULL)

            mov dosretval,0
            mov charcount,written
        .else
            mov dosretval,GetLastError()
        .endif
    .endif

    .if ( charcount == 0 )

        ; If nothing was written, first check if an o.s. error,
        ; otherwise we return -1 and set errno to ENOSPC,
        ; unless a device and first char was CTRL-Z

        mov rdx,buf
        .if ( dosretval != 0 )

            ; o.s. error happened, map error

            .if ( dosretval == ERROR_ACCESS_DENIED )

                ; wrong read/write mode should return EBADF, not EACCES

                _set_errno(EBADF)
                _set_doserrno(dosretval)
            .else
                _dosmaperr(dosretval)
            .endif
            .return -1

        .elseif ( file & FH_DEVICE && byte ptr [rdx] == CTRLZ )

            .return 0
        .endif

        _set_errno(ENOSPC)
        _set_doserrno(0)
        .return -1
    .endif

    ; return adjusted bytes written

    mov eax,charcount
    sub eax,lfcount
    ret

_write endp

    end
