; __ARGV.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include dos.inc
include malloc.inc
include stdlib.inc

.data
 __argv string_t 0

.code

__initargv proc private uses si di bx

  local argc:int_t
  local argv[64]:size_t
  local tail[256]:char_t ; name + Command-line tail (terminated by a 0Dh)

    push    ds
    push    ss
    pop     es
    lea     di,tail
    mov     bx,_psp
    mov     si,_envlen
    add     si,2
    mov     ax,_envseg
    mov     ds,ax
    mov     cx,0x7F
    xor     ax,ax
    cld
.0:
    lodsb
    stosb
    dec     cx
    jz      .1
    test    al,al
    jnz     .0
    mov     ds,bx
    mov     si,0x81
    lea     bx,argv
    mov     ss:[bx],ax
    inc     ax
    mov     argc,ax
    add     bx,2

    .for ( al = [si] : al != 0x0D : bx += size_t, argc++ )

        lea cx,tail
        mov dx,di
        sub dx,cx
        mov ss:[bx],dx
        mov cx,di     ; Add a new argument
        xor dx,dx     ; "quote from start" in DX - remove
        mov es:[di],dl

        .for ( : al == ' ' || al == 9 : )
             lodsb
        .endf
        .break .if ( al == 0x0D ) ; end of command string

        .if ( al == '"' )
            lodsb
            inc dl
        .endif
        .while ( al == '"' ) ; ""A" B"
            lodsb
            inc dh
        .endw

        .while ( al != 0x0D )

            .break .if ( !dx && ( al == ' ' || al == 9  ) )

            .if ( al == '"' )
                .if dh
                    dec dh
                .elseif dl
                    mov al,[si]
                    .break .if ( al == ' ' || al == 9 || al == 0x0D )
                    dec dl
                .else
                    inc dh
                .endif
            .else
                stosb
            .endif
            lodsb
        .endw
        .break .if ( cx == di )
        .if ( al == ' ' || al == 9 )
            mov es:[di],ah
            inc di
        .endif
    .endf

    pop     ds
    xor     ax,ax
    stosb
    mov     bx,argc
    mov     __argc,bx
    lea     si,tail
    sub     di,si
    imul    ax,bx,string_t
    add     ax,di
    invoke  malloc,ax
    mov     word ptr __argv,ax
if @DataSize
    mov     word ptr __argv+2,dx
else
    mov     dx,ds
endif
    push    ds
    mov     es,dx
    mov     cx,di
    imul    di,bx,string_t
    pushl   ss
    popl    ds
    add     di,ax
    rep     movsb
    mov     di,ax
    imul    cx,bx,string_t
    add     cx,ax

    .for ( si = &argv : bx : bx-- )

        lodsw
        add ax,cx
        stosw
if @DataSize
        mov ax,dx
        stosw
endif
    .endf
.1:
    pop ds
    ret

__initargv endp

.pragma init(__initargv, 4)

    end
