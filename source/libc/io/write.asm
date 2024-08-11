; WRITE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
ifdef __UNIX__
include sys/syscall.inc
else
include winbase.inc
include winnls.inc
endif

LF          equ 10
CR          equ 13
CTRLZ       equ 26
BUF_SIZE    equ 1025 ; size of LF translation buffer

.code

_write proc uses rdi rsi rbx fh:int_t, buf:ptr, cnt:uint_t

  local lfcount:int_t           ; count of line feeds
  local charcount:int_t         ; count of chars written so far
  local dosretval:uint_t        ; o.s. return value
  local written:int_t           ; count of chars written on this write
  local bytes_written:int_t
  local bytes_converted:int_t
  local lfbuf[BUF_SIZE]:char_t  ; lf translation buffer
  local utf8_buf[(BUF_SIZE*2)/3]:char_t
  local utf16_buf[BUF_SIZE/6]:wchar_t

    ldr ecx,fh
    ldr eax,cnt
    .return .if !eax            ; nothing to do

    .if ( ecx >= _NFILE_ )      ; validate handle
                                ; out of range -- return error
ifndef __UNIX__
        _set_doserrno(0)        ; not o.s. error
endif
        .return( _set_errno( EBADF ) )
    .endif

    assume rbx:pioinfo

    mov edx,eax
    mov rbx,_pioinfo(ecx)

ifndef __UNIX__

    .if ( [rbx].textmode == __IOINFO_TM_UTF16LE && edx & 1 )

        ; For a UTF-16 file, the count must always be an even number

        .return( _set_errno( EINVAL ) )
    .endif
endif

    .if ( [rbx].osfile & FAPPEND )

        ; appending - seek to end of file; ignore error, because maybe
        ; file doesn't allow seeking

        _lseeki64( ecx, 0, SEEK_END )
    .endif

    mov charcount,0

ifndef __UNIX__

    ; check for text mode with LF's in the buffer

    mov lfcount,0
    .if ( [rbx].osfile & FTEXT )

        mov rsi,buf     ; start at beginning of buffer
        mov dosretval,0 ; no OS error yet

        .if ( [rbx].textmode != __IOINFO_TM_UTF8 )

            .while 1

                mov rax,rsi
                sub rax,buf
                .break .if ( eax >= cnt )

                lea rdi,lfbuf ; start at beginning of lfbuf
                mov rdx,rdi

                .if ( [rbx].textmode == __IOINFO_TM_UTF16LE )

                    .while 1 ; fill the lf buf, except maybe last char

                        mov rax,rdi
                        sub rax,rdx

                       .break .if ( eax >= BUF_SIZE - 2 )

                        mov rax,rsi
                        sub rax,buf

                       .break .if ( eax >= cnt )

                        lodsw
                        .if ( ax == LF )

                            add lfcount,2
                            mov word ptr [rdi],CR
                            add rdi,2
                        .endif
                        stosw
                    .endw

                .else

                    .while 1

                        mov rax,rdi
                        sub rax,rdx

                       .break .if ( eax >= BUF_SIZE - 1 )

                        mov rax,rsi
                        sub rax,buf

                       .break .if ( eax >= cnt )

                        lodsb
                        .if ( al == LF )

                            inc lfcount
                            mov byte ptr [rdi],CR
                            inc rdi
                        .endif
                        stosb
                    .endw
                .endif

                mov rcx,rdi
                sub rcx,rdx

                .if WriteFile( [rbx].osfhnd, rdx, ecx, &written, NULL )

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

        .else ; __IOINFO_TM_UTF8

            .while 1

                mov rax,rsi
                sub rax,buf
               .break .if ( eax >= cnt )

                lea rdi,utf16_buf
                mov rdx,rdi

                .while 1

                    mov rax,rdi
                    sub rax,rdx
                    .break .if ( eax >= sizeof(utf16_buf) - 2 )
                    mov rax,rsi
                    sub rax,buf
                    .break .if ( eax >= cnt )
                    lodsw
                    .if ( ax == LF )
                        mov word ptr [rdi],CR
                        add rdi,2
                    .endif
                    stosw
                .endw

                mov rcx,rdi
                sub rcx,rdx
                shr ecx,1
                WideCharToMultiByte(CP_UTF8, 0, rdx, ecx, &utf8_buf, sizeof(utf8_buf), NULL, NULL)

                .if ( eax == 0 )

                    mov dosretval,GetLastError()
                   .break
                .else

                    mov bytes_converted,eax
                    mov bytes_written,0

                    .repeat

                        mov eax,bytes_written
                        lea rdx,utf8_buf
                        add rdx,rax
                        mov ecx,bytes_converted
                        sub ecx,bytes_written

                        .if ( WriteFile([rbx].osfhnd, rdx, ecx, &written, NULL) )
                            add bytes_written,written
                        .else
                            mov dosretval,GetLastError()
                           .break
                        .endif

                    .until ( bytes_converted <= bytes_written )

                    .if ( bytes_converted > bytes_written )
                        .break
                    .endif

                    mov rax,rsi
                    sub rax,buf
                    mov charcount,eax
                .endif
            .endw
        .endif

    .else

        ; binary mode, no translation

        .if WriteFile( [rbx].osfhnd, buf, cnt, &written, NULL )

            mov dosretval,0
            mov charcount,written
        .else
            mov dosretval,GetLastError()
        .endif
    .endif

else
    .ifs ( sys_write(fh, buf, cnt) < 0 )

        neg eax
       .return( _set_errno( eax ) )
    .endif
    mov charcount,eax
endif

    .if ( charcount == 0 )

        ; If nothing was written, first check if an o.s. error,
        ; otherwise we return -1 and set errno to ENOSPC,
        ; unless a device and first char was CTRL-Z

        mov rdx,buf
ifndef __UNIX__
        .if ( dosretval != 0 )

            ; o.s. error happened, map error

            .if ( dosretval == ERROR_ACCESS_DENIED )

                ; wrong read/write mode should return EBADF, not EACCES

                _set_doserrno(dosretval)
                _set_errno(EBADF)
            .else
                _dosmaperr(dosretval)
            .endif
            .return

        .elseif ( [rbx].osfile & FDEV && byte ptr [rdx] == CTRLZ )
else
        .if ( [rbx].osfile & FDEV && byte ptr [rdx] == CTRLZ )
endif

            .return 0
        .endif

ifndef __UNIX__
        _set_doserrno(0)
endif
        _set_errno(ENOSPC)
        .return
    .endif

    ; return adjusted bytes written

    mov eax,charcount
ifndef __UNIX__
    sub eax,lfcount
endif
    ret

_write endp

    end
