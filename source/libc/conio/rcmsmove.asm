; RCMSMOVE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include tchar.inc

.code

rcmsmove proc uses rsi rdi rbx rc:ptr TRECT, p:PCHAR_INFO, flag:uint_t

  local xpos,ypos
  local relx,rely
  local cursor:CURSOR

    ldr rdi,rc
    mov ebx,[rdi]
    .if flag & W_SHADE

        _rcshade(ebx, p, 0)
    .endif

    mov ypos,mousey()
    mov edx,eax
    mov xpos,mousex()
    sub al,bl
    mov relx,eax
    sub dl,bh
    mov rely,edx

    _getcursor(&cursor)
    _cursoroff()

    .whiled mousep() == 1

        xor esi,esi
        .ifd mousex() > xpos

            mov esi,1

        .elseif CARRY?

            .if bl

                mov esi,2
            .endif
        .endif

        .if !esi

            .ifd mousey() > ypos

                mov esi,3

            .elseif CARRY?

                .if bh != 1

                    mov esi,4
                .endif
            .endif
        .endif

        .switch pascal esi
        .case 1: _rcmover(ebx, p)
        .case 2: _rcmovel(ebx, p)
        .case 3: _rcmoved(ebx, p)
        .case 4: _rcmoveu(ebx, p)
        .endsw

        .if esi
            mov ebx,eax
            mov edx,eax
            mov eax,rely
            add al,dh
            mov ypos,eax
            mov eax,relx
            add al,dl
            mov xpos,eax
        .endif
    .endw

    _setcursor(&cursor)
    .if flag & W_SHADE

        _rcshade(ebx, p, 1)
    .endif
    mov [rdi],ebx
    ret

rcmsmove endp

    end
