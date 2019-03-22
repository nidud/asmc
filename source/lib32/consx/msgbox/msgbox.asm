; MSGBOX.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc
include stdio.inc
include string.inc

MAXLINES equ 17

.code

center_text proc private

    .if byte ptr [edi]
        mul ecx
        lea eax,[eax*2+8]
        add ebx,eax
        sub ecx,8
        wcenter(ebx, ecx, edi)
    .endif
    ret

center_text endp

msgbox proc private uses esi edi ebx dname:LPSTR, flag, string:LPSTR
local dobj:S_DOBJ, tobj:S_TOBJ, cols:dword, lcnt:dword, backgr:byte

    strlen(dname)
    xor esi,esi
    mov ebx,eax
    .if !strchr(string, 10)

        .if strlen(string) > ebx
            mov ebx,eax
        .endif
    .endif

    mov al,at_background[B_Title]
    mov backgr,al
    mov edi,string
    .if byte ptr [edi]

        .repeat

            .break .if !strchr( edi, 10 )

            mov edx,eax
            sub edx,edi
            .if edx >= ebx
                mov ebx,edx
            .endif
            inc esi
            inc eax
            mov edi,eax
        .until esi == MAXLINES
    .endif

    .if strlen(edi) >= ebx
        mov ebx,eax
    .endif

    mov dl,2
    mov dh,76
    .if bl && bl < 70
        mov dh,bl
        add dh,8
        mov dl,80
        sub dl,dh
        shr dl,1
    .endif

    .if dh < 40
        mov dx,2814h
    .endif

    mov eax,flag
    mov dobj.dl_flag,ax
    mov dobj.dl_rect.rc_x,dl
    mov dobj.dl_rect.rc_y,7
    mov eax,esi
    add al,6
    mov dobj.dl_rect.rc_row,al
    mov dobj.dl_rect.rc_col,dh
    mov dobj.dl_count,1
    mov dobj.dl_index,0
    add al,7

    .if eax > _scrrow
        mov dobj.dl_rect.rc_y,1
    .endif

    lea eax,tobj
    mov dobj.dl_object,eax
    mov tobj.to_flag,_O_PBUTT
    mov al,dh
    shr al,1
    sub al,3
    mov tobj.to_rect.rc_x,al
    mov eax,esi
    add al,4
    mov tobj.to_rect.rc_y,al
    mov tobj.to_rect.rc_row,1
    mov tobj.to_rect.rc_col,6
    mov tobj.to_ascii,'O'
    mov al,at_background[B_Dialog]
    or  al,at_foreground[F_Dialog]

    .if dobj.dl_flag & _D_STERR
        mov at_background[B_Title],70h
        mov al,at_background[B_Error]
        or  al,7;at_foreground[F_Desktop]
        or  tobj.to_flag,_O_DEXIT
    .endif

    mov dl,al
    .if dlopen(&dobj, edx, dname)

        mov edi,string
        mov esi,edi
        movzx eax,dobj.dl_rect.rc_col
        mov cols,eax
        mov lcnt,2

        .repeat

            .break .if !byte ptr [esi]
            strchr(edi, 10)
            mov esi,eax
            .break .if !eax
            mov byte ptr [esi],0
            inc esi
            mov ecx,cols
            mov eax,lcnt
            mov ebx,dobj.dl_wp
            center_text()
            mov edi,esi
            inc lcnt
        .until lcnt == MAXLINES+2

        rcbprc(dword ptr tobj.to_rect, dobj.dl_wp,cols)
        movzx ecx,tobj.to_rect.rc_col
        wcpbutt(eax, cols, ecx, "&Ok")

        mov al,backgr
        mov at_background[B_Title],al
        mov ecx,cols
        mov eax,lcnt
        mov ebx,dobj.dl_wp
        center_text()
        dlmodal(&dobj)
    .endif
    ret
msgbox endp

ermsg proc c wtitle:LPSTR, format:LPSTR, argptr:VARARG

    ftobufin(format, &argptr)
    mov eax,wtitle
    .if !eax
        lea eax,@CStr("Error")
    .endif
    msgbox(eax, _D_STDERR, &_bufin)
    xor eax,eax
    ret

ermsg endp

stdmsg proc c wtitle:LPSTR, format:LPSTR, argptr:VARARG

    ftobufin(format, &argptr)
    msgbox(wtitle, _D_STDDLG, &_bufin)
    xor eax,eax
    ret

stdmsg endp

    END
