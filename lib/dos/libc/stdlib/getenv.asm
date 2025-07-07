; GETENV.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include string.inc

if (@DataSize eq 0)
.data
 envalbuf char_t 128 dup(0)
endif

.code

getenv proc uses si di bx enval:string_t

    .new len:int_t = strlen( enval )

    .for ( bx = 0 : ax : bx += 4 )

        ldr di,_environ
        mov ax,esl[bx+di]
        mov dx,esl[bx+di+2]

        .if ( ax )

            pushl ds
            ldr si,enval
            .for ( es = dx, di = ax, cx = 0 : cx < len : cx++, si++, di++ )

                mov al,[si]
                .break .if ( al == 0 )

                mov ah,es:[di]
                or ax,0x2020
                .break .if ( al != ah )
            .endf
            popl ds

            .if ( cx == len && byte ptr es:[di] == '=' )
if @DataSize
                mov dx,es
                mov ax,di
                inc ax
else
                .for ( dx = 0,
                       di++,
                       ax = offset envalbuf,
                       si = ax,
                       cx = 0 : dh != es:[di] && cx < lengthof(envalbuf)-1 : cx++, si++, di++ )

                    mov dl,es:[di]
                    mov [si],dl
                .endf
                mov [si],dh
                mov dx,ds
                mov es,dx
endif
               .break
            .endif
        .endif
    .endf
    ret

getenv endp

    end
