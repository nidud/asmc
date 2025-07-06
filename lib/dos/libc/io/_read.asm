; _READ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc

define LF 10
define CR 13
define CTRLZ 26

.data
 pipech db _NFILE_ dup(10)

.code

_read proc uses si di bx fh:int_t, inputbuf:ptr, cnt:size_t

  local bytes_read:int_t        ; number of bytes read
  local os_read:int_t           ; bytes read on OS call
  local dosretval:uint_t        ; o.s. return value
  local retval:int_t
  local peekchr:char_t          ; peek-ahead character

    mov bx,fh
    mov ax,cnt
    lesl di,inputbuf

    .return .if !ax             ; nothing to read

    .if ( bx >= _NFILE_ )       ; validate handle
                                ; out of range -- return error
        mov _doserrno,0         ; not o.s. error
        mov errno,EBADF
       .return( -1 )
    .endif
    .if ( _osfile[bx] & FEOFLAG ) ; at EOF ?
        .return( 0 )
    .endif

    mov cx,ax
    mov retval,-2
    mov bytes_read,0            ; nothing read yet
    mov al,pipech[bx]

    .if ( _osfile[bx] & FPIPE or FDEV && al != LF && cnt )

        mov esl[di],al
        mov pipech[bx],LF
        inc bytes_read
        inc di
        dec cx
    .endif
    mov     cnt,cx
    mov     os_read,0
    stc
    pushl   ds
    pushl   es
    popl    ds
    mov     ax,0x3F00
    mov     dx,di
    int     0x21
    popl    ds
    .ifc
        mov dosretval,ax
        xor ax,ax
    .else
        mov os_read,ax
        mov ax,1
    .endif

    mov cx,cnt
    .if ( !ax || os_read < 0 || os_read > cx )

        ; ReadFile has reported an error. recognize two special cases.
        ;
        ;      1. map ERROR_ACCESS_DENIED to EBADF
        ;
        ;      2. just return 0 if ERROR_BROKEN_PIPE has occurred. it
        ;         means the handle is a read-handle on a pipe for which
        ;         all write-handles have been closed and all data has been
        ;         read.

        mov ax,dosretval
        .if ( ax == ERROR_ACCESS_DENIED )

            ; wrong read/write mode should return EBADF, not EACCES

            mov _doserrno,ax
            mov retval,EBADF
            mov errno,EBADF
            jmp error_return

        .elseif ( ax == ERROR_BROKEN_PIPE )

            mov retval,0
            jmp error_return
        .else
            mov retval,_dosmaperr( ax )
            jmp error_return
        .endif
    .endif

    add bytes_read,os_read ; update bytes read
    mov al,_osfile[bx]

    .if ( al & FTEXT )

        ; now must translate CR-LFs to LFs in the buffer

        ; set CRLF flag to indicate LF at beginning of buffer

        lesl di,inputbuf
        and al,not FCRLF

        .if ( byte ptr esl[di] == LF )
            or al,FCRLF
        .endif
        mov _osfile[bx],al

        ; convert chars in the buffer: SI is src, DI is dest

        mov si,di

        .while 1

            mov ax,bytes_read
            add ax,word ptr inputbuf
            .break .if ( si >= ax )

            mov al,esl[si]
            .if ( al == CTRLZ )

                ; if fh is not a device, set ctrl-z flag

                .if ( _osfile[bx] & FDEV )

                    mov al,esl[si]
                    stosb
                    inc si
                .else
                    or _osfile[bx],FEOFLAG
                .endif
                .break ; stop translating
            .endif

            .if ( al != CR )

                mov al,esl[si]
                stosb
                inc si
               .continue( 0 )
            .endif

            ; *[si] is CR, so must check next char for LF

            mov ax,bytes_read
            add ax,word ptr inputbuf
            dec ax

            .if ( si < ax )

                .if ( byte ptr [si+1] == LF )

                    add si,2
                    mov al,LF   ; convert CR-LF to LF
                .else
                    mov al,esl[si] ; store char normally
                    inc si
                .endif
                stosb
               .continue( 0 )
            .endif

            ; This is the hard part.  We found a CR at end of
            ; buffer.  We must peek ahead to see if next char
            ; is an LF.

            inc     si
            mov     dosretval,0
            mov     os_read,0
            stc
            pushl   ds
            pushl   ss
            popl    ds
            mov     ax,0x3F00
            lea     dx,peekchr
            mov     cx,1
            int     0x21
            popl    ds
            .ifc
                mov dosretval,ax
                xor ax,ax
            .else
                mov os_read,ax
                mov ax,1
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

                .if ( _osfile[bx] & FDEV or FPIPE )

                    ; non-seekable device

                    mov al,LF
                    .if ( peekchr != al )

                        mov al,peekchr
                        mov pipech[bx],al
                        mov al,CR
                    .endif

                .else

                    ; disk file

                    mov al,LF ; nothing read yet; must make some progress

                    .if ( di != word ptr inputbuf || peekchr != al )

                        ; seek back

                        _lseek( bx, -1, SEEK_CUR )
                        .continue( 0 ) .if ( peekchr == LF )
                        mov al,CR
                    .endif
                .endif
            .endif
            stosb
        .endw

        ; we now change bytes_read to reflect the true number of chars
        ; in the buffer

        mov ax,di
        sub ax,word ptr inputbuf
        mov bytes_read,ax
    .endif

error_return:

    mov ax,retval
    .if ( ax == -2 )
        mov ax,bytes_read
    .endif
    ret

_read endp

    end
