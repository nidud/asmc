; RCMSMOVE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc

    .code

rcmsmove proc uses esi edi ebx rc:ptr S_RECT, wp:PVOID, fl:dword

  local xpos,ypos
  local relx,rely
  local cursor:S_CURSOR

    mov edi,rc
    mov ebx,[edi]
    .if fl & _D_SHADE

        rcclrshade(ebx, wp)
    .endif

    mov ypos,mousey()
    mov edx,eax
    mov xpos,mousex()
    sub al,bl
    mov relx,eax
    sub dl,bh
    mov rely,edx

    CursorGet(&cursor)
    CursorOff()

    .while mousep() == 1

        xor esi,esi
        .if mousex() > xpos

            mov esi,1

        .elseif CARRY?

            .if bl

                mov esi,2
            .endif
        .endif

        .if !esi

            .if mousey() > ypos

                mov esi,3

            .elseif CARRY?

                .if bh != 1

                    mov esi,4
                .endif
            .endif
        .endif

        mov ecx,fl
        and ecx,not _D_SHADE

        .switch esi
          .case 1 : rcmoveright(ebx, wp, ecx) : .endc
          .case 2 : rcmoveleft(ebx, wp, ecx)  : .endc
          .case 3 : rcmovedn(ebx, wp, ecx)    : .endc
          .case 4 : rcmoveup(ebx, wp, ecx)    : .endc
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

    CursorSet(&cursor)
    .if fl & _D_SHADE

        rcsetshade(ebx, wp)
    .endif
    mov [edi],ebx
    ret

rcmsmove endp

    END
