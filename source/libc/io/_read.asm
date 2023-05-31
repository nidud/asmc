; _READ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
ifdef __UNIX__
include linux/kernel.inc
else
include winbase.inc

    LF      equ 10
    CR      equ 13
    CTRLZ   equ 26

    .data
    _pipech db _NFILE_ dup(10)
endif

    .code

_read proc uses rsi rdi rbx fh:int_t, buf:ptr, cnt:size_t
ifndef __UNIX__
  local bytes_read:int_t        ; number of bytes read
  local os_read:int_t           ; bytes read on OS call
  local dosretval:ulong_t       ; o.s. return value
  local peekchr:char_t          ; peek-ahead character
endif
    ldr rsi,buf
    ldr ebx,fh
    ldr rax,cnt                 ; cnt
    .return .if !rax            ; nothing to read

    .if ( ebx >= _NFILE_ )      ; validate handle
                                ; out of range -- return error
ifndef __UNIX__
        _set_doserrno( 0 )      ; not o.s. error
endif
        _set_errno( EBADF )
       .return( -1 )
    .endif

    lea rdx,_osfile
    mov dl,[rdx+rbx]
    .if ( dl & FEOFLAG )        ; at EOF ?
        .return( 0 )
    .endif

ifdef __UNIX__

    .ifs ( sys_read(ebx, rsi, rax) < 0 )

        neg eax
        _set_errno( eax )
        mov rax,-1
    .endif

else

    mov bytes_read,0            ; nothing read yet
    mov rdi,rsi
    .if ( dl & FPIPE or FDEV )

        lea rcx,_pipech
        mov al,[rcx+rbx]

        .if ( al != LF )

            stosb
            mov byte ptr [rcx+rbx],LF
            inc bytes_read
            dec cnt
        .endif
    .endif

    lea rcx,_osfhnd
    mov rcx,[rcx+rbx*size_t]
    mov rdx,cnt

    .ifd !ReadFile( rcx, rdi, edx, &os_read, NULL )

        ; ReadFile has reported an error. recognize two special cases.
        ;
        ;      1. map ERROR_ACCESS_DENIED to EBADF
        ;
        ;      2. just return 0 if ERROR_BROKEN_PIPE has occurred. it
        ;         means the handle is a read-handle on a pipe for which
        ;         all write-handles have been closed and all data has been
        ;         read.

        .if ( GetLastError() == ERROR_ACCESS_DENIED )

            ; wrong read/write mode should return EBADF, not EACCES

            _set_doserrno( eax )
            _set_errno(EBADF)
            .return -1

        .elseif ( eax == ERROR_BROKEN_PIPE )

            .return 0

        .else
            _dosmaperr( eax )
            .return -1
        .endif
    .endif

    add bytes_read,os_read     ; update bytes read

    lea rdx,_osfile
    mov al,[rdx+rbx]

    .if ( al & FTEXT )

        ; now must translate CR-LFs to LFs in the buffer

        ; set CRLF flag to indicate LF at beginning of buffer

        and al,not FCRLF
        .if ( byte ptr [rdi] == LF )
            or al,FCRLF
        .endif
        mov [rdx+rbx],al

        ; convert chars in the buffer: RSI is src, RDI is dest

        mov rsi,rdi

        .while 1

            mov eax,bytes_read
            add rax,buf
            .break .if ( rsi >= rax )

            mov al,[rsi]
            .if ( al == CTRLZ )

                ; if fh is not a device, set ctrl-z flag

                lea rdx,_osfile
                .break .if ( byte ptr [rbx+rdx] & FDEV )

                or byte ptr [rbx+rdx],FEOFLAG
                .break ; stop translating

            .elseif ( al != CR )

                stosb
                inc rsi
               .continue( 0 )
            .endif

            ; *[rsi] is CR, so must check next char for LF

            mov ecx,bytes_read
            mov rax,buf
            lea rax,[rax+rcx-1]
            .if ( rsi < rax )

                .if ( byte ptr [rsi+1] == LF )

                    add rsi,2
                    mov al,LF   ; convert CR-LF to LF
                .else
                    lodsb       ; store char normally
                .endif
                stosb
               .continue( 0 )
            .endif

            ; This is the hard part.  We found a CR at end of
            ; buffer.  We must peek ahead to see if next char
            ; is an LF.

            inc rsi
            lea rcx,_osfhnd
            mov rcx,[rcx+rbx*size_t]

            mov dosretval,0
            .ifd !ReadFile( rcx, &peekchr, 1, &os_read, 0 )
                mov dosretval,GetLastError()
            .endif


            .if ( dosretval != 0 || os_read == 0 )

                mov al,CR ; couldn't read ahead, store CR

            .else

                ; peekchr now has the extra character -- we now have
                ; several possibilities:
                ;   1. disk file and char is not LF; just seek back
                ;      and copy CR
                ;   2. disk file and char is LF; seek back and discard CR
                ;   3. disk file, char is LF but this is a one-byte read:
                ;      store LF, don't seek back
                ;   4. pipe/device and char is LF; store LF.
                ;   5. pipe/device and char isn't LF, store CR and put
                ;     char in pipe lookahead buffer.

                lea rdx,_osfile
                .if ( byte ptr [rbx+rdx] & FDEV or FPIPE )

                    ; non-seekable device

                    mov al,LF
                    .if ( peekchr != al )

                        mov al,peekchr
                        lea rcx,_pipech
                        mov [rcx+rbx],al
                        mov al,CR
                    .endif

                .else

                    ; disk file

                    mov al,LF ; nothing read yet; must make some progress

                    .if ( buf != rdi || peekchr != al )

                        ; seek back

                        _lseek( ebx, -1, SEEK_CUR )
                        .continue(0) .if ( peekchr == LF )
                        mov al,CR
                    .endif
                .endif
            .endif
            stosb
        .endw

        ; we now change bytes_read to reflect the true number of chars
        ; in the buffer

        mov rax,rdi
        sub rax,buf
    .else
        mov eax,bytes_read
    .endif
endif
    ret

_read endp

    end
