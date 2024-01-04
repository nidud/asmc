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
include malloc.inc
include winbase.inc
include consoleapi.inc
include winnls.inc

    LF      equ 10
    CR      equ 13
    CTRLZ   equ 26

externdef _lookuptrailbytes:byte

endif

    .code

_read proc uses rsi rdi rbx fh:int_t, inputbuf:ptr, cnt:size_t
ifndef __UNIX__
  local bytes_read:int_t        ; number of bytes read
  local os_read:int_t           ; bytes read on OS call
  local dosretval:ulong_t       ; o.s. return value
  local buf:ptr
  local dwMode:DWORD
  local fromConsole:DWORD
  local retval:int_t
  local peekchr:char_t          ; peek-ahead character
  local wpeekchr:wchar_t
  local inputsize:DWORD
endif
    ldr rsi,inputbuf
    ldr ecx,fh
    ldr rax,cnt                 ; cnt
    .return .if !rax            ; nothing to read
ifndef __UNIX__
    mov inputsize,eax
endif
    mov rdi,rax

    .if ( ecx >= _NFILE_ )      ; validate handle
                                ; out of range -- return error
ifndef __UNIX__
        _set_doserrno( 0 )      ; not o.s. error
endif
        _set_errno( EBADF )
       .return( -1 )
    .endif

    assume rbx:pioinfo

    mov rbx,_pioinfo(ecx)

    .if ( [rbx].osfile & FEOFLAG ) ; at EOF ?
        .return( 0 )
    .endif

ifdef __UNIX__

    .ifs ( sys_read(ecx, rsi, rdi) < 0 )

        neg eax
        _set_errno( eax )
        mov rax,-1
    .endif

else

    mov retval,-2
    mov bytes_read,0            ; nothing read yet
    mov al,[rbx].textmode

    .switch al
    .case __IOINFO_TM_UTF8

        ; For UTF8 we want the count to be an even number

        .if ( rdi & 1 )

            _set_errno(EINVAL)
           .return(-1)
        .endif
        shr rdi,1
        .if ( rdi < 4 )
            mov edi,4
        .endif

        mov rsi,malloc(rdi)
        .if ( rax == NULL )

            _set_errno(ENOMEM)
           .return(-1)
        .endif
        _lseeki64(fh, 0, SEEK_CUR)
ifdef _WIN64
        mov [rbx].startpos,rax
else
        mov dword ptr [ebx].startpos[0],eax
        mov dword ptr [ebx].startpos[4],edx
endif
        .endc

    .case __IOINFO_TM_UTF16LE

        ; For UTF16 the count always needs to be an even number

        .if ( rdi & 1 )

            _set_errno(EINVAL)
           .return(-1)
        .endif

        ; Fall Through to default
    .endsw

    mov cnt,rdi
    mov buf,rsi
    mov rdi,rsi
    mov al,[rbx].pipech

    .if ( [rbx].osfile & FPIPE or FDEV && al != LF && cnt )

        stosb
        mov [rbx].pipech,LF
        inc bytes_read
        dec cnt

        ; For UTF16, there maybe one more look ahead char. For UTF8,
        ; there maybe 2 more look ahead chars

        mov al,[rbx].pipech2[0]
        .if ( ( [rbx].textmode != __IOINFO_TM_ANSI ) && ( al != LF ) && cnt )

            stosb
            mov [rbx].pipech2[0],LF
            inc bytes_read
            dec cnt
            mov al,[rbx].pipech2[1]

            .if ( ( [rbx].textmode == __IOINFO_TM_UTF8 ) && ( al != LF ) && cnt )

                stosb
                mov [rbx].pipech2[1],LF
                inc bytes_read
                dec cnt
            .endif
        .endif
    .endif

    mov fromConsole,0
    .if ( ( [rbx].osfile & FDEV ) && ( [rbx].osfile & FTEXT ) )
        mov fromConsole,GetConsoleMode([rbx].osfhnd, &dwMode)
    .endif

    ; read the data from Console

    .if ( fromConsole && ( [rbx].textmode == __IOINFO_TM_UTF16LE ) )

        mov rcx,cnt
        shr rcx,1

        .if ( !ReadConsoleW( [rbx].osfhnd, rdi, ecx, &os_read, NULL) )

            mov dosretval,GetLastError()
            _dosmaperr(dosretval)
            mov retval,-1
            jmp error_return
        .endif

        shl os_read,1 ; In UTF16 mode, ReadConsoleW returns the actual number of wchar_t's read,
                      ; so we make sure we update os_read accordingly
    .else

        mov rdx,cnt
        ReadFile( [rbx].osfhnd, rdi, edx, &os_read, NULL )

        mov rdx,cnt
        .if ( !eax || os_read < 0 || os_read > edx )

            ; ReadFile has reported an error. recognize two special cases.
            ;
            ;      1. map ERROR_ACCESS_DENIED to EBADF
            ;
            ;      2. just return 0 if ERROR_BROKEN_PIPE has occurred. it
            ;         means the handle is a read-handle on a pipe for which
            ;         all write-handles have been closed and all data has been
            ;         read.

            .ifd ( GetLastError() == ERROR_ACCESS_DENIED )

               ; wrong read/write mode should return EBADF, not EACCES

                _set_doserrno( eax )
                _set_errno(EBADF)
                mov retval,-1
                jmp error_return

            .elseif ( eax == ERROR_BROKEN_PIPE )

                mov retval,0
                jmp error_return

            .else
                _dosmaperr( eax )
                mov retval,-1
                jmp error_return
            .endif
        .endif
    .endif

    add bytes_read,os_read     ; update bytes read

    mov al,[rbx].osfile
    .if ( al & FTEXT )

        ; now must translate CR-LFs to LFs in the buffer

        ; set CRLF flag to indicate LF at beginning of buffer

        mov rdi,buf
        and al,not FCRLF

        .if ( [rbx].textmode != __IOINFO_TM_UTF16LE )

            .if ( byte ptr [rdi] == LF )
                or al,FCRLF
            .endif
            mov [rbx].osfile,al

            ; convert chars in the buffer: RSI is src, RDI is dest

            mov rsi,rdi

            .while 1

                mov eax,bytes_read
                add rax,buf
                .break .if ( rsi >= rax )

                mov al,[rsi]
                .if ( al == CTRLZ )

                    ; if fh is not a device, set ctrl-z flag

                    .if ( [rbx].osfile & FDEV )
                        movsb
                    .else
                        or [rbx].osfile,FEOFLAG
                    .endif
                    .break ; stop translating
                .endif

                .if ( al != CR )

                    movsb
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
                mov dosretval,0
                .if !ReadFile( [rbx].osfhnd, &peekchr, 1, &os_read, 0 )
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

                    .if ( [rbx].osfile & FDEV or FPIPE )

                        ; non-seekable device

                        mov al,LF
                        .if ( peekchr != al )

                            mov al,peekchr
                            mov [rbx].pipech,al
                            mov al,CR
                        .endif

                    .else

                        ; disk file

                        mov al,LF ; nothing read yet; must make some progress

                        .if ( buf != rdi || peekchr != al )

                            ; seek back

                            _lseeki64( fh, -1, SEEK_CUR )
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
            mov bytes_read,eax

            .if ( ( [rbx].textmode == __IOINFO_TM_UTF8 ) && eax )

                ; UTF8 reads need to be converted into UTF16

                dec rdi ; q has gone beyond the last char
                movzx eax,byte ptr [rdi]

                ;
                ; If the last byte is a standalone UTF-8 char. We then
                ; take the whole buffer. Otherwise we skip back till we
                ; come to a lead byte. If the leadbyte forms a complete
                ; UTF-8 character will the remaining part of the buffer,
                ; then again we take the whole buffer. If not, we skip to
                ; one byte which should be the final trail byte of the
                ; previous UTF-8 char or a standalone UTF-8 character
                ;
                .if ( eax < 0x80 )

                    inc rdi
                    ;
                    ; Final byte is standalone, we reset q, because we
                    ; will now consider the full buffer which we have read
                    ;
                .else

                    lea rdx,_lookuptrailbytes
                    mov ecx,1

                    .while ( byte ptr [rdx+rax] == 0 && ecx <= 4 && rdi >= buf )

                        dec rdi
                        inc ecx
                        mov al,[rdi]
                    .endw
                    mov al,[rdx+rax]

                    .if ( eax == 0 )
                        ;
                        ; Should have exited the while by finding a lead
                        ; byte else, the file has incorrect UTF-8 chars
                        ;
                        _set_errno(EILSEQ)
                        mov retval,-1
                        jmp error_return
                    .endif

                    inc eax
                    .if ( eax == ecx )
                        ;
                        ; The leadbyte + the remaining bytes form a full set
                        ;
                        add rdi,rcx

                    .else

                        ; Seek back

                        .if ( [rbx].osfile & (FDEV or FPIPE) )
                            ;
                            ; non-seekable device. Put the extra chars in
                            ; _pipech & _pipech2. We would have a maximum
                            ; of 3 extra chars
                            ;
                            mov al,[rdi]
                            inc rdi
                            mov [rbx].pipech,al

                            .if ( ecx >= 2 )

                                mov al,[rdi]
                                inc rdi
                                mov [rbx].pipech2[0],al
                            .endif
                            .if ( ecx == 3 )

                                mov al,[rdi]
                                inc rdi
                                mov [rbx].pipech2[1],al
                            .endif
                            ;
                            ; We need to point q back to beyond whatever
                            ; we actually took in.
                            ;
                            sub rdi,rcx

                        .else
                            ; We have read extra chars, so we seek back
                            neg rcx
ifdef _WIN64
                            _lseeki64(fh, rcx, SEEK_CUR)
else
                            mov edx,-1
                            _lseeki64(fh, edx::ecx, SEEK_CUR)
endif
                        .endif
                    .endif
                .endif
                mov rdx,rdi
                sub rdx,buf
                mov ecx,inputsize
                shr ecx,1

                .ifd ( !MultiByteToWideChar(CP_UTF8, 0, buf, edx, inputbuf, ecx) )

                    _dosmaperr(GetLastError())
                    mov retval,-1
                    jmp error_return
                .endif

                mov rdx,rdi
                sub rdx,buf
                xor ecx,ecx
                cmp eax,edx
                setnz cl
                mov [rbx].utf8translations,ecx

                ; MultiByteToWideChar returns no of wchar_t's. Double it

                shl eax,1
                mov bytes_read,eax
            .endif

        .elseif ( fromConsole )

            mov rsi,rdi

            .while 1

                mov eax,bytes_read
                add rax,buf
                .break .if ( rsi >= rax )

                mov ax,[rsi]
                .if ( ax == CTRLZ )

                    or [rbx].osfile,FEOFLAG
                   .break ; stop translating
                .endif

                .if ( ax != CR )

                    movsw
                   .continue( 0 )
                .endif

                mov eax,bytes_read
                add rax,buf
                sub rax,2

                .if ( rsi < rax )

                    mov eax,LF
                    .if ( ax == [rsi+2] )

                        add rsi,2
                        stosw
                    .else
                        movsw
                    .endif
                .endif
            .endw

            mov rax,rdi
            sub rax,buf
            mov bytes_read,eax

        .else

            ; NOT reading from console and tmode == __IOINFO_TM_UTF16LE

            .if ( wchar_t ptr [rdi] == LF )
                or al,FCRLF
            .endif
            mov [rbx].osfile,al
            mov rsi,rdi

            .while 1

                mov eax,bytes_read
                add rax,buf
                .break .if ( rsi >= rax )

                mov ax,[rsi]
                .if ( ax == CTRLZ )

                    ; if fh is not a device, set ctrl-z flag

                    .if ( [rbx].osfile & FDEV )
                        movsw
                    .else
                        or [rbx].osfile,FEOFLAG
                    .endif
                    .break ; stop translating
                .endif

                .if ( ax != CR )

                    movsw
                   .continue( 0 )
                .endif

                mov eax,bytes_read
                add rax,buf
                sub rax,2

                .if ( rsi < rax )

                    mov eax,LF
                    .if ( ax == [rsi+2] )

                        add rsi,2
                        stosw
                    .else
                        movsw
                    .endif
                    .continue( 0 )
                .endif

                add rsi,2
                mov dosretval,0
                .if !ReadFile( [rbx].osfhnd, &wpeekchr, 2, &os_read, 0 )
                    mov dosretval,GetLastError()
                .endif


                .if ( dosretval != 0 || os_read == 0 )

                    mov eax,CR ; couldn't read ahead, store CR
                .else

                    .if ( [rbx].osfile & FDEV or FPIPE )

                        mov eax,LF
                        .if ( wpeekchr != ax )

                            mov ax,wpeekchr
                            mov [rbx].pipech,al
                            mov [rbx].pipech2[0],ah
                            mov [rbx].pipech2[1],LF
                            mov eax,CR
                        .endif

                    .else

                        .if ( buf == rdi || wpeekchr == ax )
                            mov eax,LF
                        .else

                            _lseeki64( fh, -2, SEEK_CUR )
                            mov eax,CR
                            .if ( wpeekchr == LF )
                                .continue( 0 )
                            .endif
                        .endif
                    .endif
                .endif
                stosw
            .endw

            mov rax,rdi
            sub rax,buf
            mov bytes_read,eax

        .endif
    .endif

error_return:

    mov rcx,buf
    .if ( rcx != inputbuf )
        free(rcx)
    .endif
    mov eax,retval
    .if ( eax == -2 )
        mov eax,bytes_read
    .endif
endif
    ret

_read endp

    end
