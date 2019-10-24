; DLINIT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc
include consx.inc

.code

dlinit proc uses esi edi ebx td:ptr S_DOBJ

local object, wp, window

    mov ebx,td
    mov edi,[ebx]

    .repeat

        .if edi & _D_ONSCR
            mov eax,[ebx].S_DOBJ.dl_wp
            mov wp,eax
            .break .if !rcalloc([ebx].S_DOBJ.dl_rect, 0)
            mov [ebx].S_DOBJ.dl_wp,eax
            rcread( [ebx].S_DOBJ.dl_rect, eax)
        .endif

        movzx eax,[ebx].S_DOBJ.dl_count
        mov esi,eax
        mov eax,[ebx].S_DOBJ.dl_object
        mov object,eax

        .while esi

            push esi
            push edi
            push ebx

            xor eax,eax
            mov ebx,object
            mov ch,[ebx].S_TOBJ.to_rect.rc_col
            mov edx,[ebx].S_TOBJ.to_rect
            mov ebx,td
            mov cl,[ebx+6]  ; .dl_rect.rc_col
            mov edi,[ebx]   ; .dl_flag
            add edx,edx
            mov al,dh
            mul cl
            mov cl,ch
            and ecx,0x00FF
            and edx,0x00FF
            add eax,edx
            add eax,[ebx].S_DOBJ.dl_wp
            mov window,eax
            mov ebx,object
            mov ax,[ebx].S_TOBJ.to_flag
            and eax,0x000F
            mov esi,eax

            .switch eax

              .case _O_PBUTT

                mov esi,window
                mov eax,[ebx]
                and eax,_O_DEACT
                mov edx,eax
                .repeat
                    mov eax,[esi]
                    inc esi
                    mov al,ah
                    and al,0Fh
                    .if edx
                        .if !al
                            and ah,070h
                            or  ah,008h
                            mov [esi],ah
                        .endif
                    .elseif al == 8
                        and ah,070h
                        mov [esi],ah
                    .endif
                    inc esi
                .untilcxz
                .endc

              .case _O_RBUTT

                mov eax,[ebx]
                and al,_O_RADIO
                mov al,' '
                .ifnz
                    mov al,ASCII_RADIO
                .endif
                mov edx,window
                mov [edx+2],al
                .endc

              .case _O_CHBOX

                mov eax,[ebx]
                and eax,_O_FLAGB
                mov al,' '
                .ifnz
                    mov al,'x'
                .endif
                mov edx,window
                mov [edx+2],al
                .endc

              .case _O_XCELL
              .case _O_TEDIT

                mov dl,tclrascii
                mov eax,esi
                mov esi,[ebx].S_TOBJ.to_data
                mov ebx,eax
                mov edi,window
                mov eax,[edi]
                mov al,dl
                mov edx,ecx

                .if bl != _O_TEDIT
                    mov al,' '
                    .repeat
                        stosb
                        inc edi
                    .untilcxz
                .else
                    rep stosw
                .endif

                .if esi
                    mov edi,window
                    .if bl == _O_XCELL
                        add edi,2
                        sub edx,2
                        wcpath(edi, edx, esi)
                    .else
                        .repeat
                            lodsb
                            .break .if !al
                            stosb
                            inc edi
                            dec edx
                        .untilz
                    .endif
                .endif
                .endc

              .case _O_MENUS

                mov eax,[ebx]
                mov edx,window
                .if al & _O_FLAGB
                    mov byte ptr [edx-2],175
                .elseif eax & _O_RADIO
                    mov al,ASCII_RADIO
                    mov [edx-2],al
                .endif
                .endc

            .endsw

            pop ebx
            pop edi
            pop esi

            mov eax,edi
            add object,S_TOBJ
            dec esi
        .endw

        .break .if !(edi & _D_ONSCR)
        rcwrite([ebx].S_DOBJ.dl_rect, [ebx].S_DOBJ.dl_wp)
        free([ebx].S_DOBJ.dl_wp)
        mov eax,wp
        mov [ebx].S_DOBJ.dl_wp,eax
    .until 1
    ret

dlinit endp

    END
