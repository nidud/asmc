; _INITTERM.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc

define MAXENTRIES 64

if @CodeSize
define movc <mov>
define shrc <shr>
else
movc macro v:vararg
endm
shrc macro v:vararg
endm
endif

func_t typedef proto
func_p typedef ptr func_t

.code

_initterm proc uses si di bx pfbegin:ptr, pfend:ptr

   .new priority[MAXENTRIES]:uint_t
   .new function[MAXENTRIES]:func_p

    lesl    di,pfbegin
    mov     dx,word ptr pfend
    mov     ax,dx
    sub     ax,di

    ; walk the table of function pointers from the bottom up, until
    ; the end is encountered.  Do not skip the first entry.  The initial
    ; value of pfbegin points to the first valid entry.  Do not try to
    ; execute what pfend points to.  Only entries before pfend are valid.

    .ifnz

        .for ( cx = di, bx = 0, cx += ax : di < cx && bx < MAXENTRIES : di += 8 )

            mov ax,esl[di]
            .if ( ax )

                imul    si,bx,sizeof(func_p)
                mov     word ptr function[si],ax
                movc    ax,esl[di+2]
                movc    word ptr function[si+2],ax
                shrc    si,1
                mov     ax,esl[di+4]
                mov     priority[si],ax
                inc     bx
            .endif
        .endf

        .for ( :: )

            .for ( cx = -1, si = 0, di = 0, dx = 0,
                   ax = bx : ax : ax--, si+=sizeof(func_p), di+=2 )

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
