; _INITTERM.D--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc

define MAXENTRIES 64

func_t typedef proto
func_p typedef ptr func_t

.code

_initterm proc uses si di bx pfbegin:ptr, pfend:ptr

   .new priority[MAXENTRIES]:uint_t
   .new function[MAXENTRIES]:func_p

    lesl bx,pfbegin
    mov dx,word ptr pfend

    ; walk the table of function pointers from the bottom up, until
    ; the end is encountered.  Do not skip the first entry.  The initial
    ; value of pfbegin points to the first valid entry.  Do not try to
    ; execute what pfend points to.  Only entries before pfend are valid.

    sub dx,bx
    shr dx,3

    .ifnz

        .for ( di = 0, si = 0, cx = 0 : dx && cx < MAXENTRIES : dx--, bx += 8 )

            .if ( word ptr esl[bx] )

                mov function[si],esl[bx]
                mov priority[di],esl[bx+4]
                add si,func_p
                add di,uint_t
                inc cx
            .endif
        .endf

        .for ( bx = cx :: )

            .for ( cx = -1, si = 0, di = 0, dx = 0, ax = bx : ax : ax--, si += func_p, di += uint_t )

                .if ( word ptr function[si] && cx >= priority[di] )

                    mov cx,priority[di]
                    mov dx,si
                    inc dx
                .endif
            .endf
            .break .if !dx
            dec dx
            mov si,dx
            call function[si]
            mov word ptr function[si],0
        .endf
    .endif
    ret

_initterm endp

    end

