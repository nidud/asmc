; _WRITE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc

define LF          10
define CR          13
define CTRLZ       26
define BUF_SIZE    257 ; size of LF translation buffer

.code

_write proc uses di si bx fh:int_t, buf:ptr, cnt:uint_t

  local lfcount:int_t           ; count of line feeds
  local charcount:int_t         ; count of chars written so far
  local dosretval:uint_t        ; o.s. return value
  local lfbuf[BUF_SIZE]:char_t  ; lf translation buffer

    mov bx,fh
    mov ax,cnt
    .return .if !ax             ; nothing to do

    .if ( bx >= _NFILE_ )       ; validate handle
                                ; out of range -- return error
        mov _doserrno,0         ; not o.s. error
        mov errno,EBADF
       .return( -1 )
    .endif

    .if ( _osfile[bx] & FAPPEND )

        ; appending - seek to end of file; ignore error, because maybe
        ; file doesn't allow seeking

        _lseek( bx, 0, SEEK_END )
    .endif

    mov charcount,0

    ; check for text mode with LF's in the buffer

    mov lfcount,0
    .if ( _osfile[bx] & FTEXT )

        pushl ds
        ldr si,buf      ; start at beginning of buffer
        mov dosretval,0 ; no OS error yet

        .while 1

            mov ax,si
            sub ax,word ptr buf
            .break .if ( ax >= cnt )

            xor di,di ; start at beginning of lfbuf

            .while 1

                .break .if ( di >= BUF_SIZE - 1 )

                mov ax,si
                sub ax,word ptr buf
                .break .if ( ax >= cnt )

                lodsb
                .if ( al == LF )

                    inc lfcount
                    mov lfbuf[di],CR
                    inc di
                .endif
                mov lfbuf[di],al
                inc di
            .endw

            mov     cx,di
            movl    di,ds
            movl    ax,ss
            movl    ds,ax
            lea     dx,lfbuf
            mov     ax,0x4000
            int     0x21
            movl    ds,di
            .ifc
                mov dosretval,ax
               .break
            .endif
            add charcount,ax
           .break .if ( ax < cx )
        .endw
        popl ds

    .else

        ; binary mode, no translation

        pushl   ds
        mov     cx,cnt
        ldr     dx,buf
        mov     ax,0x4000
        int     0x21
        popl    ds
        .ifc
            mov dosretval,ax
        .else
            mov dosretval,0
            mov charcount,ax
        .endif
    .endif

    .if ( charcount == 0 )

        ; If nothing was written, first check if an o.s. error,
        ; otherwise we return -1 and set errno to ENOSPC,
        ; unless a device and first char was CTRL-Z

        ldr di,buf

        .if ( dosretval != 0 )

            ; o.s. error happened, map error

            .if ( dosretval == ERROR_ACCESS_DENIED )

                ; wrong read/write mode should return EBADF, not EACCES

                mov _doserrno,dosretval
                mov errno,EBADF
                mov ax,-1
            .else
                _dosmaperr(dosretval)
            .endif
            .return

        .elseif ( _osfile[bx] & FDEV && byte ptr esl[di] == CTRLZ )

            .return 0
        .endif

        mov _doserrno,0
        mov errno,ENOSPC
       .return( -1 )
    .endif

    ; return adjusted bytes written

    mov ax,charcount
    sub ax,lfcount
    ret

_write endp

    end
