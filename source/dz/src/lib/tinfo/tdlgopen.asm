; TDLGOPEN.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include tinfo.inc
include string.inc

externdef   IDD_TEWindows:DWORD

MAXDLGOBJECT    equ 16
MAXOBJECTLEN    equ 38
ID_ACTIVATE     equ 17
ID_SAVE         equ 18
ID_CLOSE        equ 19

    .code

event_list PROC PRIVATE USES esi edi ebx
    mov esi,eax
    mov edi,edx
    dlinit(esi)
    lea eax,[esi+SIZE S_TOBJ]
    mov ecx,MAXDLGOBJECT
    .repeat
        or [eax].S_TOBJ.to_flag,_O_STATE
        lea eax,[eax+SIZE S_TOBJ]
    .untilcxz
    mov bx,[esi+4]      ;.S_DOBJ.dl_rect.rc_x
    add bx,0204h
    mov ecx,[edi].S_LOBJ.ll_numcel
    mov edx,[edi].S_LOBJ.ll_list
    mov eax,[edi].S_LOBJ.ll_index
    lea edx,[edx+eax*4]
    .while ecx
        mov edi,[edx]
        .if [edi].S_TINFO.ti_flag & _T_MODIFIED
            mov al,bh
            dec ebx
            scputc(ebx, eax, 1, '*')
            inc ebx
        .endif
        mov al,bh
        scpath(ebx, eax, MAXOBJECTLEN, [edi].S_TINFO.ti_file)
        lea edx,[edx+4]
        lea esi,[esi+SIZE S_TOBJ]
        and [esi].S_TOBJ.to_flag,not _O_STATE
        inc bh
        dec ecx
    .endw
    mov eax,1
    ret
event_list ENDP

tdlgopen PROC USES esi edi ebx

  local ll:S_LOBJ, ti[TIMAXFILES]:DWORD

    lea edi,ll
    xor eax,eax
    mov ecx,SIZE S_LOBJ
    rep stosb
    lea edi,ti
    mov ll.ll_list,edi
    mov ecx,TIMAXFILES*4
    rep stosb
    mov ll.ll_dcount,MAXDLGOBJECT   ; number of cells (max)
    mov ll.ll_proc,event_list

    .if tigetfile(tinfo)

        mov esi,eax
        xor ebx,ebx
        mov edi,ll.ll_list
        .repeat
            tistate(esi)
            .break .if ZERO?
            mov [edi],esi
            add edi,4
            mov esi,[esi].S_TINFO.ti_next
            inc ebx
        .until  ebx >= TIMAXFILES
        mov ll.ll_count,ebx
        mov eax,ebx
        .if eax >= MAXDLGOBJECT
            mov eax,MAXDLGOBJECT
        .endif
        mov ll.ll_numcel,eax

        .if rsopen(IDD_TEWindows)

            mov edi,eax
            dlshow(eax)
            mov eax,edi
            lea edx,ll
            event_list()
            dllevent(edi, addr ll)
            mov dx,[edi+4]
            mov ebx,IDD_TEWindows
            mov [ebx+6],dx
            dlclose( edi )
            xor eax,eax
            lea ebx,ll
            .if edx && [ebx].S_LOBJ.ll_count != eax
                mov eax,[ebx].S_LOBJ.ll_index
                add eax,[ebx].S_LOBJ.ll_celoff
                mov eax,ti[eax*4]
                .if eax
                    xchg eax,edx
                    .if eax == ID_CLOSE
                        mov eax,1
                    .elseif eax == ID_SAVE
                        mov eax,2
                    .else
                        mov eax,edx
                    .endif
                .endif
            .endif
        .endif
    .endif
    test eax,eax
    ret
tdlgopen ENDP

    END
