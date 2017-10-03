; TVIEW.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT
;
; Change history:
; 2016-03-09 - fixed CR/LF read
; 2013-09-19 - tview.asm -- 32 bit
; 2013-03-06 - added Memory View (doszip)
; 12/28/2011 - removed Binary View (doszip)
;        - removed Class View (doszip)
;        - removed View Memory (doszip)
;        - added zoom function (F11)
; 08/02/2010 - added Class View
; 10/10/2009 - fixed bug in Clipboard
; 10/10/2009 - new malloc() and free()
; 11/15/2008 - added function Seek
; 11/13/2008 - Moved Binary View to F4
;        - added switch /M, view memory [00000..FFFFF]
; 09/10/2008 - Divide error in putinfo(percent)
;        - command END  in dump text (F2) moves to top of file
;        - command UP   in dump text (F2) moves to top of file
;        - command PGUP in dump text (F2) moves to top of file
;        - command END  in hex view  (F4) offset not aligned
;        - command END  in HEX and BIN -- last offset + 1 < offset
;        - added short key Ctrl+End -- End of line (End right)
;        - added IO Bit Stream
; 04/20/2007 - added switch /O<offset>
; 03/15/2007 - fixed Short-Key ESC on zero byte files
; 03/12/2007 - added Binary View
; 2004-06-27 - tview.asm -- 16 bit
; 1998-02-10 - tview.c
;

include alloc.inc
include string.inc
include stdio.inc
include stdlib.inc
include io.inc
include iost.inc
include direct.inc
include errno.inc
include consx.inc
include crtl.inc
include time.inc
include tview.inc
include dzlib.inc

externdef   tvflag: byte
externdef   fsflag: byte
externdef   IDD_TVCopy:dword
externdef   IDD_TVSeek:dword
externdef   IDD_TVHelp:dword
externdef   IDD_TVQuickMenu:dword

PUBLIC      format_lu

tvabout     proto
cmsearchidd proto :dword

MAXLINE     equ 8000h
MAXLINES    equ 256

S_TVIEW         STRUC
tv_filename     dd ?
tv_offset       dd ?
tv_loffs        dd ?
tv_dialog       dd ?    ; main dialog pointer
tv_rowcnt       dd ?    ; max lines (23/48)
tv_lcount       dd ?    ; lines on screen
tv_scount       dd ?    ; bytes on screen
tv_maxcol       dd ?    ; max linesize on screen
tv_curcol       dd ?    ; current line offset (col)
tv_screen       dd ?    ; screen buffer
tv_menusline    dd ?
tv_statusline   dd ?
tv_cursor       S_CURSOR <> ; cursor (old)
tv_bsize        dd ?    ; buffer size
tv_zpos         dd ?    ; temp (mouse)
tv_tmp          dd ?    ; temp 32
tv_static_count dd ?        ; line count
tv_line_table   dd 256 dup(?)   ; line offset in file
tv_static_table dd MAXLINES dup(?) ; offset of first <MAXLINES> lines
S_TVIEW         ENDS

.data

cp_deci     db 'Dec'
cp_hex      db 'Hex  '
cp_ascii    db 'Ascii'
cp_wrap     db 'Wrap  '
cp_unwrap   db 'Unwrap'
externdef   searchstring:byte

format_lu   db "%u",0
format_08Xh db "%08Xh",0

QuickMenuKeys label dword
    dd KEY_F5
    dd KEY_F7
    dd KEY_F2
    dd KEY_F4
    dd KEY_F6
    dd KEY_ESC

DLG_Textview    S_DOBJ <?>
UseClipboard    db ?
rsrows          db 24

;******** Resource begin TVStatusline *
;   { 0x0054,   0,   0, { 0,24,80, 1} },
;******** Resource data  *******************
Statusline_RC   dw 0200h,0054h,0000h
                db 0
Statusline_Y    db 24
Statusline_C0   db 80,1
                dw 03F3Ch,0F03Fh,03C07h,03F3Fh
                dw 09F0h,3F3Ch,0F03Fh,03C09h,03F3Fh,008F0h,03F3Ch,0F03Fh
                dw 03C07h,03F3Fh,006F0h,03F3Ch,0F03Fh,03C0Ah,03F0h
                db 3Fh,0F0h
Statusline_C1   db 6,3Ch
                dw 04620h,02031h,06548h,0706Ch,02020h,03246h,05720h
                dw 06172h,0F070h,02004h,03346h,05320h,06165h,06372h,02068h
                dw 04620h,02034h,06548h,0F078h,02004h,03546h,04320h,0706Fh
                dw 02079h,04620h,02036h,06544h,02063h,04620h,02037h,06553h
                dw 06B65h,005F0h,04520h,06373h,05120h,06975h
                db 74h
                db 0F0h
Statusline_C2   db 1,' '
IDD_Statusline  dd Statusline_RC

;******** Resource begin TVMenusline *
;   { 0x0050,   0,   0, { 0, 0,80, 1} },
;******** Resource data  *******************
Menusline_RC    dw 0200h,0050h,0000h,0000h
Menusline_C0    db 80,1,0F0h
Menusline_C1    db 80,3Ch,0F0h
Menusline_C2    db 80,' '
IDD_Menusline   dd Menusline_RC

    .code

    assume ebp:ptr S_TVIEW

    option proc:private

seek_eax proc
    xor edx,edx
    ioseek(&STDI, edx::eax, SEEK_SET)
    ret
seek_eax endp

add_offset proc uses edx
    mov eax,[ebp].tv_lcount
    inc [ebp].tv_lcount
    lea edx,[ebp+eax*4].tv_line_table
    mov eax,[ebp].tv_offset
    mov [edx],eax
    ret
add_offset endp

read_line_table proc uses edi

    mov [ebp].tv_lcount,1
    mov eax,[ebp].tv_loffs
    mov [ebp].tv_line_table,eax
    mov [ebp].tv_offset,eax

    .repeat

        movzx ecx,tvflag
        .if ecx & _TV_HEXVIEW

            seek_eax()
            .break .ifz
            mov edi,16
            xor ecx,ecx
            .while 1
                mov eax,[ebp].tv_offset
                add eax,edi
                mov [ebp].tv_offset,eax
                .if eax > dword ptr STDI.ios_fsize
                    mov eax,dword ptr STDI.ios_fsize
                    mov [ebp].tv_offset,eax
                    .break
                .endif
                add_offset()
                inc ecx
                .break .if ecx >= [ebp].tv_rowcnt
            .endw

        .else

            .break .if ecx & _TV_WRAPLINES

            lea edx,[ebp].tv_static_table
            mov ecx,[ebp].tv_static_count
            .repeat
                .break .if eax == [edx]
                add edx,4
            .untilcxz

            .if ecx
                .repeat
                    add edx,4
                    mov eax,[edx]
                    mov [ebp].tv_offset,eax
                    add_offset()
                    mov eax,[ebp].tv_lcount
                    .if eax > [ebp].tv_rowcnt
                        dec [ebp].tv_lcount
                        .break(1)
                    .endif
                .untilcxz
                mov eax,[ebp].tv_offset
                .if eax == dword ptr STDI.ios_fsize
                    dec [ebp].tv_lcount
                    .break
                .endif
            .endif

            seek_eax()
            .break .ifz

            xor edi,edi
            .while 1
                ogetc()
                .break .ifz
                inc [ebp].tv_offset
                inc edi
                .if edi == MAXLINE
                    xor edi,edi
                    mov eax,10
                .endif
                .if eax == 10
                    add_offset()
                    mov eax,[ebp].tv_lcount
                    .if eax > [ebp].tv_rowcnt
                        dec [ebp].tv_lcount
                        .break(1)
                    .endif
                .endif
            .endw
        .endif
        add_offset()
        add_offset()
        dec [ebp].tv_lcount
        dec [ebp].tv_lcount
    .until 1
    .ifnz
        mov eax,_scrcol
        mul [ebp].tv_rowcnt
        mov ecx,eax
        mov edi,[ebp].tv_screen
        mov eax,20h
        rep stosb
        mov eax,[ebp].tv_loffs
        mov [ebp].tv_offset,eax
        seek_eax()
    .endif
    ret

read_line_table endp

parse_line proc
    push esi
    push edi
    xor  esi,esi
    .while 1
        ogetc()
        .break .ifz
        inc [ebp].tv_offset
        .if al == 10 || al == 13
            ogetc()
            .break .ifz
            inc [ebp].tv_offset
            .if al != 10 && al != 13
                dec [ebp].tv_offset
                dec STDI.ios_i
            .endif
            xor eax,eax
            inc eax
            .break
        .endif
        .if al == 9
            mov eax,esi
            add eax,[ebp].tv_curcol
            add eax,8
            and eax,-8
            sub eax,esi
            sub eax,[ebp].tv_curcol
            add esi,eax
            add edi,eax
        .else
            .if !al
                mov al,' '
            .endif
            mov [edi],al
            inc edi
            inc esi
        .endif
        .if esi == _scrcol
            ogetc()
            .break .ifz
            inc [ebp].tv_offset
            .if al == 10 || al == 13
                ogetc()
                .break .ifz
                inc [ebp].tv_offset
                .if al != 10 && al != 13
                    dec [ebp].tv_offset
                    dec STDI.ios_i
                .endif
            .endif
            xor eax,eax
            inc eax
            .break
        .else
            .break .ifnb
        .endif
    .endw
    pop edi
    pop esi
    .ifnz
        add edi,_scrcol
    .endif
    ret
parse_line endp

read_wrap proc uses edi
    read_line_table()
    .repeat
        mov eax,0
        .break .ifz
        mov edi,[ebp].tv_screen
        mov [ebp].tv_bsize,eax
        mov [ebp].tv_lcount,eax
        .repeat
            mov eax,[ebp].tv_bsize
            inc [ebp].tv_bsize
            .break .if eax >= [ebp].tv_rowcnt
            add_offset()
            parse_line()
        .untilz
        mov eax,[ebp].tv_offset
        sub eax,[ebp].tv_loffs
        mov [ebp].tv_scount,eax
        or  eax,1
    .until 1
    ret
read_wrap endp

read_text proc uses edi
    read_line_table()
    .repeat
        .break .ifz
        mov edx,[ebp].tv_maxcol
        mov eax,[ebp].tv_lcount
        .while eax
            mov ecx,[ebp+eax*4].tv_line_table
            dec eax
            sub ecx,[ebp+eax*4].tv_line_table
            .if ecx > edx
                mov edx,ecx
            .endif
        .endw
        mov [ebp].tv_maxcol,edx
        mov edi,[ebp].tv_screen
        mov [ebp].tv_bsize,0
        .while 1
            mov eax,[ebp].tv_bsize
            inc [ebp].tv_bsize
            .break .if eax >= [ebp].tv_lcount
            lea edx,[ebp+eax*4].tv_line_table
            mov eax,[edx+4]
            sub eax,[edx]
            add [ebp].tv_scount,eax
            .if eax <= [ebp].tv_curcol
                add edi,_scrcol
            .else
                mov eax,[edx]
                add eax,[ebp].tv_curcol
                seek_eax()
                .break(1) .ifz
                parse_line()
                .break .ifz
            .endif
        .endw
        or eax,1
    .until 1
    ret
read_text endp

mk_hexword proc
    mov ah,al
    and eax,0FF0h
    shr al,4
    or  eax,3030h
    .if ah > 39h
        add ah,7
    .endif
    .if al > 39h
        add al,7
    .endif
    ret
mk_hexword endp

read_hex proc uses esi edi ebx
    .repeat
        read_line_table()
        .break .ifz
        ogetc()
        .break .ifz
        dec STDI.ios_i
        push STDI.ios_c
        mov eax,[ebp].tv_rowcnt
        shl eax,4
        .if eax <= STDI.ios_c
            mov STDI.ios_c,eax
        .endif
        mov eax,STDI.ios_c
        xor ecx,ecx
        mov [ebp].tv_scount,eax
        mov esi,[ebp].tv_screen
        .repeat
            mov edi,esi
            lea ebx,[ebp+ecx*4+3].tv_line_table
            .if !(tvflag & _TV_HEXOFFSET)
                sprintf(edi, "%010u  ", [ebx-3])
                add edi,9
            .else
                .for edx=4: edx: edx--, ebx--
                    mov al,[ebx]
                    mk_hexword()
                    stosw
                .endf
                inc edi
            .endif
            mov edx,STDI.ios_c
            mov eax,16
            add edi,3
            .if edx >= eax
                mov edx,eax
            .endif
            .break .if !edx
            sub STDI.ios_c,edx
            mov ebx,edi
            add ebx,51
            push ecx
            mov ecx,edx
            xor edx,edx
            .repeat
                .if edx == 8
                    mov al,179
                    stosb
                    inc edi
                .endif
                mov eax,STDI.ios_i
                .break .if eax >= dword ptr STDI.ios_fsize
                add eax,STDI.ios_bp
                mov al,[eax]
                inc STDI.ios_i
                mov [ebx],al
                .if !al
                    mov byte ptr [ebx],' '
                .endif
                mk_hexword()
                stosw
                inc edi
                inc ebx
                inc edx
            .untilcxz
            pop ecx
            add esi,_scrcol
            inc ecx
        .until ecx >= [ebp].tv_lcount
        pop eax
        mov STDI.ios_c,eax
        mov eax,1
    .until 1
    ret
read_hex endp

previous_line proc

    mov eax,[ebp].tv_loffs
    mov [ebp].tv_offset,eax

    .repeat

        .break .if !eax

        .if eax > dword ptr STDI.ios_fsize

            mov eax,dword ptr STDI.ios_fsize
            mov [ebp].tv_loffs,eax
            .break
        .endif

        mov edx,16
        .if tvflag & _TV_HEXVIEW
            .if eax <= edx
                xor eax,eax
            .else
                sub eax,edx
            .endif
            .break
        .endif

        mov eax,[ebp].tv_static_count
        mov eax,[ebp+eax*4].tv_static_table
        .if eax < [ebp].tv_offset
            mov eax,[ebp].tv_offset
            seek_eax()
            .ifz
                xor eax,eax
                .break
            .endif
            oungetc()
            .ifz
                xor eax,eax
                .break
            .endif
            dec [ebp].tv_offset
            push esi
            mov esi,0x8000
            .if al == 13 || al == 10
                oungetc()
                .ifz
                    pop esi
                    xor eax,eax
                    .break
                .endif
                dec [ebp].tv_offset
            .endif
            .while 1
                oungetc()
                .ifz
                    pop esi
                    xor eax,eax
                    .break
                .endif
                dec [ebp].tv_offset
                dec esi
                .break .ifz
                .break .if al == 13
                .break .if al == 10
            .endw
            mov eax,[ebp].tv_offset
            inc eax
            pop esi
            .break
        .endif
        mov eax,[ebp].tv_offset
        mov ecx,[ebp].tv_static_count
        dec ecx
        .while 1
            lea edx,[ebp+ecx*4].tv_static_table
            .break .if eax > [edx]

            .if !ecx
                mov eax,ecx
                .break(1)
            .endif
            dec ecx
        .endw
        mov eax,[edx]
        .break .if !(tvflag & _TV_WRAPLINES)
        mov edx,[ebp].tv_loffs
        .if eax > edx
            xor eax,eax
            .break
        .endif
        sub edx,eax
        .if edx >= 0x8000
            add eax,edx
            sub eax,_scrcol
        .endif
        mov [ebp].tv_offset,eax
        mov [ebp].tv_tmp,eax
        seek_eax()
        .break .ifz
        push edi
        .while 1
            mov edi,[ebp].tv_screen
            parse_line()
            .break .ifz
            mov eax,[ebp].tv_offset
            .break .if eax >= [ebp].tv_loffs
            mov [ebp].tv_tmp,eax
        .endw
        pop edi
        mov eax,[ebp].tv_tmp
    .until 1
    ret
previous_line endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

putscreenb proc uses esi edi ebx y, row, lp

  local bz:COORD, rect:SMALL_RECT, lbuf[TIMAXSCRLINE]:CHAR_INFO

    mov esi,lp
    mov ebx,row
    mov eax,_scrcol
    mov bz.x,ax
    mov bz.y,1
    mov rect.Left,0
    dec eax
    mov rect.Right,ax

    .repeat
        lea edi,lbuf
        mov ecx,_scrcol
        movzx eax,at_background[B_TextView]
        or  al,at_foreground[F_TextView]
        shl eax,16
        .repeat
            lodsb
            stosd
        .untilcxz
        mov eax,y
        add eax,row
        sub eax,ebx
        mov rect.Top,ax
        mov rect.Bottom,ax
        .break .if !WriteConsoleOutput(hStdOutput, addr lbuf, bz, 0, addr rect)
        dec ebx
    .untilz
    ret

putscreenb endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

continuesearch proc uses esi lpOffset:ptr

  local buffer[512]:byte

    lea esi,buffer
    xor eax,eax
    .if al != searchstring
        wcpushst(esi, "Search for the string:")
        mov eax,_scrrow
        mov edx,_scrcol
        sub edx,24
        scputs(24, eax, 0, edx, &searchstring)
        mov eax,lpOffset
        mov eax,[eax]
        xor edx,edx
        ioseek(addr STDI, edx::eax, SEEK_SET)
        .ifnz
            osearch()
            .ifnz
                mov ecx,lpOffset
                mov [ecx],eax
                mov dword ptr STDI.ios_offset,eax
                mov dword ptr STDI.ios_offset[4],edx
                wcpopst(esi)
                mov eax,1
            .else
                notfoundmsg()
            .endif
        .else
            notfoundmsg()
        .endif
    .endif
    ret

continuesearch endp

chexbuf proc uses esi edi ebx off, len
  local result

    mov result,0
    mov eax,len
    shr eax,4
    add eax,1
    mov ecx,10+16*3+2+16+2
    mul ecx
    inc eax

    .if malloc(eax)

        mov edi,eax
        mov result,eax

        .while len

            sprintf(edi, "%08X  ", off)

            add edi,eax
            mov ebx,16
            add off,ebx
            xor esi,esi
            lea edx,[edi+16*3+2]

            .while ebx && esi < len
            .if esi == 8

                strcpy(edi, "| ")
                add edi,2
            .endif
            ogetc()
            jz toend
            push eax
            sprintf(edi, "%02X", eax)
            add edi,3
            mov byte ptr [edi-1],' '
            pop eax
            .if eax < ' '

                mov eax,'.'
            .endif
            sprintf(edx, "%c", eax)
            dec ebx
            inc edx
            inc esi
        .endw
        sub len,esi
        mov eax,'    '
        .while esi < 16
            .if esi == 8

                stosw
            .endif
            stosw
            stosb
            inc esi
        .endw
        mov edi,edx
        mov eax,0A0Dh
        stosw
    .endw
    mov byte ptr [edi],0
    mov edx,edi
    sub edx,result
    inc edx
    .endif
toend:
    mov eax,result
    ret
chexbuf endp

cmmcopy proc uses esi edi ebx
  local lb[128]:byte
    mov edx,IDD_TVQuickMenu
    mov eax,keybmouse_x
    mov esi,eax
    mov [edx+6],al
    mov ebx,keybmouse_y
    mov [edx+7],bl
    .if rsmodal(edx)

        .if eax != 1

            PushEvent(QuickMenuKeys[eax*4-8])
        .else
            lea edi,lb
            .while esi < _scrcol
                getxyc(esi, ebx)
                stosb
                inc esi
            .endw
            xor eax,eax
            stosb
            lea edi,lb
            .if strtrim(edi)

                ClipboardCopy(edi, eax)
                ClipboardFree()
                stdmsg("Copy", "%s\n\nis copied to clipboard", edi)
            .endif
        .endif
    .endif
    ret
cmmcopy endp

update_dialog proc uses edi ebx

    xor ebx,ebx
    mov edi,_scrrow
    mov dl,tvflag
    .if dl & _TV_USESLINE

        mov bl,35
        mov ecx,5
        mov eax,offset cp_hex
        .if dl & _TV_HEXVIEW

            mov eax,offset cp_ascii
        .endif
        scputs(ebx, edi, 0, ecx, eax)
        mov bl,13
        inc cl
        mov eax,offset cp_unwrap
        .if dl & _TV_WRAPLINES

            mov eax,offset cp_wrap
        .endif
        scputs(ebx, edi, 0, ecx, eax)
        mov bl,54
        mov cl,3
        mov eax,offset cp_deci
        .if dl & _TV_HEXOFFSET

            mov eax,offset cp_hex
        .endif
        scputs(ebx, edi, 0, ecx, eax)
    .endif
    ret
update_dialog endp

mouse_scroll proc

    xor ecx,ecx
    .repeat

        .break .if edx < 8

        .if edx > edi
            inc ecx
            .break
        .endif

        mov ebx,esi
        sub ebx,9
        .if eax < ebx
            add ecx,2
            .break
        .endif

        add ebx,9+10
        .if eax > ebx
            add ecx,3
            .break
        .endif

        .if edx == 12
            add ecx,2
            .if eax > esi
                inc ecx
            .endif
            .break
        .endif

        .if edx >= 11 && edx <= 13

            mov ebx,esi
            sub ebx,4
            .if eax < ebx
                add ecx,2
                .break
            .endif

            add ebx,4+5
            .if eax > 45
                add ecx,3
                .break
            .endif
        .endif

        .break .if edx < 12
        .ifnz
            inc ecx
            .break
        .endif
        ret
    .until 1

    inc ecx
    push ecx
    mov ebx,esi
    sub ebx,3
    .if eax >= ebx
        add ebx,3+3
        .if eax >= ebx
            mov ecx,_scrcol
            dec ecx
            sub ecx,eax
            mov eax,ecx
        .else
            xor eax,eax
        .endif
    .endif
    shl eax,2
    .if edx > 12
        mov ecx,_scrrow
        sub ecx,edx
        mov edx,ecx
    .else
        .ifz
            xor edx,edx
        .endif
    .endif
    shl edx,2
    pop ecx
    ret
mouse_scroll endp

mouse_scroll_proc proc uses esi edi ebx
    mov esi,_scrcol
    mov edi,_scrrow
    inc edi
    shr esi,1
    shr edi,1
    mousey()
    push eax
    mousex()
    pop edx
    mouse_scroll()
    ret
mouse_scroll_proc endp

tview_update proc
    xor eax,eax
    ret
tview_update endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    option proc:PUBLIC

tview proc uses esi edi ebx filename, offs

    alloca(sizeof(S_TVIEW))
    mov ebx,offs
    mov edx,filename
    push ebp
    mov ebp,eax
    mov [ebp].tv_offset,ebx
    mov [ebp].tv_filename,edx

    mov STDI.ios_flag,0
    mov eax,_scrcol
    mov Statusline_C0,al
    mov Menusline_C0,al
    mov Menusline_C1,al
    mov Menusline_C2,al
    mov Statusline_C1,6
    mov Statusline_C2,1
    sub al,80
    add Statusline_C1,al
    add Statusline_C2,al
    mov esi,STDI.ios_flag
    lea edi,[ebp+8]
    xor eax,eax
    mov ecx,SIZE S_TVIEW - 8
    rep stosb
    mov [ebp].tv_loffs,ebx
    mov eax,_scrrow
    mov ebx,IDD_Statusline
    mov [ebx+7],al
    inc al
    mov rsrows,al
    .if tvflag & _TV_USEMLINE
        dec al
    .endif
    .if tvflag & _TV_USESLINE
        dec al
    .endif

    mov [ebp].tv_rowcnt,eax ; adapt to current screen size
    add eax,2
    mul _scrcol

    .repeat

        .break .if !malloc(eax)

        mov [ebp].tv_screen,eax
        .if !(esi & IO_MEMBUF)

            mov ebx,[ebp].tv_offset
            .if ioopen(addr STDI, [ebp].tv_filename, M_RDONLY, OO_MEMBUF) != -1

                xor eax,eax
                .if eax != dword ptr STDI.ios_fsize[4]

                    mov dword ptr STDI.ios_fsize[4],eax
                    sub eax,2
                    mov dword ptr STDI.ios_fsize,eax
                .endif
                mov [ebp].tv_loffs,ebx
                .if !(STDI.ios_flag & IO_MEMBUF)

                    mov eax,8000h
                    mov STDI.ios_c,eax
                    mov STDI.ios_size,eax
                .endif
            .else
                free([ebp].tv_screen)
                xor eax,eax
                .break
            .endif
        .endif
        mov al,at_background[B_TextView]
        or  al,at_foreground[F_TextView]
        .if dlscreen(addr DLG_Textview, eax)

            mov [ebp].tv_dialog,eax
            dlshow(eax)
            rsopen(IDD_Menusline)
            mov [ebp].tv_menusline,eax
            dlshow(eax)
            rsopen(IDD_Statusline)
            mov [ebp].tv_statusline,eax
            .if tvflag & _TV_USESLINE

                dlshow(eax)
            .endif
            scpath(1, 0, 41, [ebp].tv_filename)
            mov eax,_scrcol
            sub eax,38
            mov edx,dword ptr STDI.ios_fsize
            scputf(eax, 0, 0, 0, "%12u byte", edx)
            mov edx,_scrcol
            sub edx,5
            scputs(edx, 0, 0, 0, "100%")
            sub edx,14
            scputs(edx, 0, 0, 0, "col")

            .if !(tvflag & _TV_USEMLINE)

                dlhide([ebp].tv_menusline)
            .endif

            CursorGet(addr [ebp].tv_cursor)
            _gotoxy(0, 1)
            CursorOff()

            push tupdate
            mov tupdate,tview_update
            update_dialog()
            msloop()
            ;
            ; offset of first <MAXLINES> lines
            ;
            lea edi,[ebp].tv_static_table
            xor eax,eax
            xor esi,esi
            stosd
            mov [ebp].tv_offset,eax
            mov [ebp].tv_static_count,1
            seek_eax()
            .ifnz
                .repeat
                    ogetc()
                    .ifz
                        mov eax,[ebp].tv_offset
                        stosd
                        stosd
                        inc [ebp].tv_static_count
                        .break
                    .endif
                    inc [ebp].tv_offset
                    inc esi
                    .if esi == MAXLINE
                        xor esi,esi
                        mov eax,10
                    .endif
                    .if eax == 10
                        mov eax,[ebp].tv_offset
                        stosd
                        inc [ebp].tv_static_count
                    .endif
                .until [ebp].tv_static_count > MAXLINES-3
                dec [ebp].tv_static_count
            .endif

            mov esi,1
            .while 1

                .if esi == 2
                    update_dialog()
                .endif
                .if esi

                    mov [ebp].tv_scount,0
                    .if tvflag & _TV_HEXVIEW
                        read_hex()
                    .elseif tvflag & _TV_WRAPLINES
                        read_wrap()
                    .else
                        read_text()
                    .endif

                    .if eax

                        .if tvflag & _TV_USEMLINE

                            mov eax,[ebp].tv_scount
                            add eax,[ebp].tv_loffs
                            .ifz
                                mov eax,100
                            .else
                                mov ecx,100
                                mul ecx
                                mov ecx,dword ptr STDI.ios_fsize
                                div ecx
                                and eax,007Fh
                                .if eax > 100
                                    mov eax,100
                                .endif
                            .endif
                            mov edx,_scrcol
                            sub edx,5
                            scputf(edx, 0, 0, 0, "%3d", eax)
                            sub edx,10
                            scputf(edx, 0, 0, 0, "%-8d", [ebp].tv_curcol)
                        .endif
                        mov eax,dword ptr STDI.ios_fsize
                        .if eax
                            xor eax,eax
                            .if tvflag & _TV_USEMLINE

                                inc eax
                            .endif
                            putscreenb(eax, [ebp].tv_rowcnt, [ebp].tv_screen)
                        .endif
                    .endif
                    xor esi,esi
                .endif

                .switch tgetevent()

                  .case MOUSECMD

                    .if mousep() == 2

                        cmmcopy()
                        .endc
                        ;.gotosw(KEY_F5)
                    .endif
                    .endc .if !eax

                    mousey()
                    inc eax
                    .if !(tvflag & _TV_USESLINE) || al != rsrows

                        mouse_scroll_proc()
                        xor eax,eax
                        .switch ecx
                          .case 1
                            mov eax,KEY_UP
                            .endc
                          .case 2
                            mov eax,KEY_DOWN
                            .endc
                          .case 3
                            mov edx,eax
                            mov eax,KEY_LEFT
                            .endc
                          .case 4
                            mov edx,eax
                            mov eax,KEY_RIGHT
                            .endc
                        .endsw
                        .if eax
                            push edx
                            PushEvent(eax)
                            pop eax
                            Sleep(eax)
                        .endif
                        .endc
                    .endif

                    msloop()
                    mousex()
                    .if al < 9
                        .gotosw(KEY_F1)
                    .endif
                    .endc .ifz
                    .if al < 10
                        .gotosw(KEY_F2)
                    .endif
                    .endc .ifz
                    .if al < 31
                        .gotosw(KEY_F3)
                    .endif
                    .endc .ifz
                    .if al < 41
                        .gotosw(KEY_F4)
                    .endif
                    .endc .ifz
                    .if al < 50
                        .gotosw(KEY_F5)
                        .endc
                    .endif
                    .endc .ifz
                    .if al < 58
                        .gotosw(KEY_F6)
                    .endif
                    .endc .ifz
                    .if al < 66
                        .gotosw(KEY_F7)
                    .endif
                    .if al < 70
                        .gotosw(KEY_F10)
                    .endif
                    msloop()
                    .endc

                  .case KEY_F1
                    rsmodal(IDD_TVHelp)
                    .endc

                  .case KEY_F2
                    .endc .if dword ptr STDI.ios_fsize == 0
                    .if !(tvflag & _TV_HEXVIEW)
                        xor tvflag,_TV_WRAPLINES
                        mov esi,2
                    .endif
                    .endc

                  .case KEY_F3
                    and STDI.ios_flag,not IO_SEARCHMASK
                    mov al,fsflag
                    and eax,IO_SEARCHMASK
                    or  STDI.ios_flag,eax
                    xor eax,eax
                    .if dword ptr STDI.ios_fsize >= 16

                        .if cmsearchidd(STDI.ios_flag)

                            mov STDI.ios_flag,edx
                            and edx,IO_SEARCHCUR or IO_SEARCHSET
                            push edx
                            continuesearch(&[ebp].tv_loffs)
                            pop edx
                            or  STDI.ios_flag,edx
                        .endif
                    .endif
                    push eax
                    and fsflag,not IO_SEARCHMASK
                    mov eax,STDI.ios_flag
                    and STDI.ios_flag,not (IO_SEARCHSET or IO_SEARCHCUR)
                    and al,IO_SEARCHMASK
                    or  fsflag,al
                    pop eax
                    .if eax
                        inc esi
                    .endif
                    .endc

                  .case KEY_F4
                    .endc .if dword ptr STDI.ios_fsize == 0
                    mov al,tvflag
                    mov ah,al
                    and al,not _TV_HEXVIEW
                    .if !(ah & _TV_HEXVIEW)
                        or  al,_TV_HEXVIEW
                    .endif
                    mov tvflag,al
                    .if !(al & _TV_HEXVIEW)
                        mov eax,[ebp].tv_curcol
                        .if eax <= [ebp].tv_loffs
                            sub [ebp].tv_loffs,eax
                        .endif
                    .else
                        mov eax,[ebp].tv_curcol
                        add [ebp].tv_loffs,eax
                        xor eax,eax
                        mov [ebp].tv_curcol,eax
                    .endif
                    mov esi,2
                    .endc

                  .case KEY_F5
                    .if rsopen(IDD_TVCopy)

                        mov ebx,eax
                        .if UseClipboard

                            or byte ptr [ebx+4*16],_O_FLAGB
                        .endif
                        mov edx,[ebp].tv_loffs
                        add edx,[ebp].tv_curcol
                        mov [ebp].tv_curcol,0
                        mov eax,offset format_08Xh
                        .if !(tvflag & _TV_HEXOFFSET)

                            mov eax,offset format_lu
                        .endif
                        sprintf([ebx+24], eax, edx)
                        dlinit(ebx)

                        .if rsevent(IDD_TVCopy, ebx)

                            mov UseClipboard,0
                            .if byte ptr [ebx+4*16] & _O_FLAGB

                                mov UseClipboard,1
                            .endif

                            .if strtolx([ebx+24]) < dword ptr STDI.ios_fsize

                                oseek(eax, SEEK_SET)
                                .ifnz

                                    mov edi,eax
                                    xor eax,eax
                                    .if UseClipboard != al

                                        .if strtolx([ebx+40])

                                            mov edx,eax
                                            .if byte ptr [ebx+5*16] & _O_FLAGB

                                                chexbuf(edi, eax)
                                                mov edi,eax
                                            .else
                                                oread()
                                                xor edi,edi
                                            .endif
                                            .if eax
                                                ClipboardCopy(eax, edx)
                                                ClipboardFree()
                                                free(edi)
                                                mov eax,1
                                            .endif
                                        .endif
                                    .elseif ioinit(addr STDO, 8000h)

                                        .if ogetouth([ebx+56], M_WRONLY) != -1

                                            mov STDO.ios_file,eax
                                            strtolx([ebx+40])
                                            .if byte ptr [ebx+5*16] & _O_FLAGB

                                                chexbuf(edi, eax)
                                                mov edi,eax
                                                oswrite(STDO.ios_file, edi, edx)
                                                free(edi)
                                            .else
                                                xor edx,edx
                                                iocopy(addr STDO, addr STDI, edx::eax)
                                                ioflush(addr STDO)
                                            .endif
                                            ioclose(addr STDO)
                                            mov eax,1
                                        .else
                                            iofree(addr STDO)
                                            xor eax,eax
                                        .endif
                                    .endif
                                .endif
                            .else
                                xor eax,eax
                            .endif
                        .endif
                        dlclose(ebx)
                        mov eax,edx
                    .endif
                    .endc

                  .case KEY_F6
                    .endc .if dword ptr STDI.ios_fsize == 0
                    xor tvflag,_TV_HEXOFFSET
                    mov esi,2
                    .endc

                  .case KEY_F7
                    .if rsopen(IDD_TVSeek)
                        mov ebx,eax
                        mov edx,[ebp].tv_loffs
                        add edx,[ebp].tv_curcol
                        mov [ebp].tv_curcol,0
                        mov eax,offset format_08Xh
                        .if !(tvflag & _TV_HEXOFFSET)
                            mov eax,offset format_lu
                        .endif
                        sprintf([ebx+24], eax, edx)
                        dlinit(ebx)
                        rsevent(IDD_TVSeek, ebx)
                        push eax
                        strtolx([ebx+24])
                        dlclose(ebx)
                        pop eax
                        .if eax && edx <= dword ptr STDI.ios_fsize
                            mov [ebp].tv_loffs,edx
                            mov esi,1
                        .endif
                    .endif
                    .endc

                  .case KEY_F10
                  .case KEY_ESC
                  .case KEY_ALTX
                    .break

                  .case KEY_ALTF5
                  .case KEY_CTRLB
                    dlhide([ebp].tv_dialog)
                    .while !getkey()
                    .endw
                    dlshow([ebp].tv_dialog)
                    .endc

                  .case KEY_CTRLM
                    xor tvflag,_TV_USEMLINE
                    .if tvflag & _TV_USEMLINE
                        dlshow([ebp].tv_menusline)
                        dec [ebp].tv_rowcnt
                    .else
                        dlhide([ebp].tv_menusline)
                        inc [ebp].tv_rowcnt
                    .endif
                    mov esi,1
                    .endc

                  .case KEY_CTRLS
                    xor tvflag,_TV_USESLINE
                    .if tvflag & _TV_USESLINE
                        dlshow([ebp].tv_statusline)
                        dec [ebp].S_TVIEW.tv_rowcnt
                    .else
                        dlhide([ebp].tv_statusline)
                        inc [ebp].S_TVIEW.tv_rowcnt
                    .endif
                    mov esi,1
                    .endc

                  .case KEY_F11
                    .if !(tvflag & _TV_USESLINE or _TV_USEMLINE)
                        PushEvent(KEY_CTRLS)
                        .gotosw(KEY_CTRLM)
                    .endif
                    .if tvflag & _TV_USEMLINE
                        PushEvent(KEY_CTRLM)
                    .endif
                    .if tvflag & _TV_USESLINE
                        .gotosw(KEY_CTRLS)
                    .endif
                    .endc

                  ;--

                  .case KEY_CTRLE
                  .case KEY_UP
                    previous_line()
                    .if eax != [ebp].tv_loffs
                        mov [ebp].tv_loffs,eax
                        mov esi,1
                    .endif
                    .endc

                  .case KEY_CTRLX
                  .case KEY_DOWN
                    .if tvflag & _TV_HEXVIEW
                        mov eax,[ebp].tv_scount
                        add eax,[ebp].tv_loffs
                        inc eax
                        .endc .if eax >= dword ptr STDI.ios_fsize
                        add eax,15
                        .if eax >= dword ptr STDI.ios_fsize
                            .gotosw(KEY_END)
                        .endif
                        add [ebp].tv_loffs,16
                    .else
                        mov eax,[ebp].tv_lcount
                        .endc .if eax < [ebp].tv_rowcnt
                        mov eax,[ebp+4].tv_line_table
                        mov [ebp].tv_loffs,eax
                    .endif
                    mov esi,1
                    .endc

                  .case KEY_CTRLR
                  .case KEY_PGUP
                    mov cl,tvflag
                    mov eax,[ebp].tv_loffs
                    .endc .if !eax
                    .if cl & _TV_HEXVIEW
                        mov eax,[ebp].tv_rowcnt
                        shl eax,4
                        .if eax < [ebp].tv_loffs
                            sub [ebp].tv_loffs,eax
                        .else
                            xor eax,eax
                            mov [ebp].tv_loffs,eax
                        .endif
                        mov esi,1
                    .else
                        .if !(tvflag & _TV_WRAPLINES) || eax != dword ptr STDI.ios_fsize
                            mov edi,1
                            .repeat
                                previous_line()
                                .break .if eax == [ebp].tv_loffs
                                mov [ebp].tv_loffs,eax
                                inc edi
                            .until edi == [ebp].tv_rowcnt
                        .else
                            mov edi,[ebp].tv_rowcnt
                            dec edi
                            .repeat
                                previous_line()
                                mov [ebp].tv_loffs,eax
                                dec edi
                            .untilz
                        .endif
                        mov esi,1
                    .endif
                    .endc

                  .case KEY_CTRLC
                  .case KEY_PGDN
                    mov eax,[ebp].tv_scount
                    add eax,[ebp].tv_loffs
                    inc eax
                    .endc .if eax >= dword ptr STDI.ios_fsize

                    .if tvflag & _TV_HEXVIEW

                        mov ebx,eax
                        mov eax,[ebp].tv_rowcnt
                        shl eax,4
                        add ebx,eax
                        .if ebx >= dword ptr STDI.ios_fsize
                            .gotosw(KEY_END)
                        .endif
                        add [ebp].tv_loffs,eax
                        mov esi,1
                        .endc
                    .endif
                    mov eax,[ebp].tv_lcount
                    .endc .if eax != [ebp].tv_rowcnt
                    dec eax
                    shl eax,2
                    lea ebx,[ebp].tv_line_table
                    add ebx,eax
                    mov eax,[ebx]
                    .if eax >= dword ptr STDI.ios_fsize
                        .gotosw(KEY_END)
                    .endif
                    mov [ebp].tv_loffs,eax
                    mov esi,1
                    .endc

                  .case KEY_LEFT
                    .if !(tvflag & _TV_HEXVIEW or _TV_WRAPLINES)
                        mov eax,[ebp].tv_curcol
                        .if eax
                            dec [ebp].tv_curcol
                            mov esi,1
                        .endif
                    .endif
                    .endc

                  .case KEY_RIGHT
                    .if !(tvflag & _TV_HEXVIEW or _TV_WRAPLINES)
                        mov eax,[ebp].tv_curcol
                        .if eax < [ebp].tv_maxcol
                            inc [ebp].tv_curcol
                            mov esi,1
                        .endif
                    .endif
                    .endc

                  .case KEY_HOME
                    sub eax,eax
                    mov [ebp].tv_loffs,eax
                    mov [ebp].tv_curcol,eax
                    mov esi,1
                    .endc

                  .case KEY_END
                    mov ecx,dword ptr STDI.ios_fsize
                    mov edx,[ebp].tv_rowcnt
                    .if tvflag & _TV_HEXVIEW
                        mov eax,edx
                        shl eax,4
                        inc eax
                        .endc .if eax >= ecx
                        sub eax,ecx
                        not eax
                        add eax,18
                        and eax,-16
                        mov [ebp].tv_loffs,eax
                        mov esi,1
                        .endc
                    .endif
                    mov eax,[ebp].tv_lcount
                    .endc .if eax < edx
                    mov eax,[ebp].tv_scount
                    add eax,[ebp].tv_loffs
                    inc eax
                    .endc .if eax >= ecx
                    mov [ebp].tv_loffs,ecx
                    .if !(tvflag & _TV_WRAPLINES) || eax != dword ptr STDI.ios_fsize
                        mov edi,1
                        .repeat
                            previous_line()
                            .break .if eax == [ebp].tv_loffs
                            mov [ebp].tv_loffs,eax
                            inc edi
                        .until edi == [ebp].tv_rowcnt
                    .else
                        mov edi,[ebp].tv_rowcnt
                        dec edi
                        .repeat
                            previous_line()
                            mov [ebp].tv_loffs,eax
                            dec edi
                        .untilz
                    .endif
                    mov esi,1
                    .endc

                  .case KEY_MOUSEUP
                    PushEvent(KEY_UP)
                    PushEvent(KEY_UP)
                    PushEvent(KEY_UP)
                    .endc

                  .case KEY_MOUSEDN
                    PushEvent(KEY_DOWN)
                    PushEvent(KEY_DOWN)
                    PushEvent(KEY_DOWN)
                    .endc

                  .case KEY_CTRLLEFT
                    .endc .if tvflag & _TV_HEXVIEW or _TV_WRAPLINES
                    xor eax,eax
                    or  eax,[ebp].tv_curcol
                    .endc .ifz
                    .if eax >= _scrcol
                        sub eax,_scrcol
                    .else
                        xor eax,eax
                    .endif
                    mov [ebp].tv_curcol,eax
                    mov esi,1
                    .endc

                  .case KEY_CTRLRIGHT
                    .endc .if tvflag & _TV_HEXVIEW or _TV_WRAPLINES
                    mov edx,[ebp].tv_maxcol
                    mov eax,[ebp].tv_curcol
                    .endc .if eax >= edx
                    add eax,_scrcol
                    .if eax > edx
                        mov eax,edx
                    .endif
                    mov [ebp].tv_curcol,eax
                    mov esi,1
                    .endc

                  .case KEY_SHIFTF3
                  .case KEY_CTRLL
                    .if continuesearch(&[ebp].tv_loffs)
                        .gotosw(KEY_CTRLHOME)
                    .endif
                    .endc

                  .case KEY_CTRLEND
                    .endc .if tvflag & _TV_HEXVIEW or _TV_WRAPLINES
                    mov eax,[ebp].tv_maxcol
                    .endc .if eax < _scrcol
                    sub eax,20
                    mov [ebp].tv_curcol,eax
                    mov esi,1
                    .endc

                  .case KEY_CTRLHOME
                    xor eax,eax
                    mov [ebp].tv_curcol,eax
                    mov esi,1
                    .endc
                .endsw
            .endw

            ioclose(addr STDI)
            free([ebp].tv_screen)
            dlclose([ebp].tv_statusline)
            dlclose([ebp].tv_menusline)
            dlclose([ebp].tv_dialog)
            CursorSet(addr [ebp].tv_cursor)
            pop eax
            mov tupdate,eax

            xor eax,eax
            mov STDI.ios_flag,eax
        .else
            free([ebp].tv_screen)
            _close(STDI.ios_file)
            mov eax,1
        .endif
    .until 1
    pop ebp
    mov esp,ebp
    ret
tview endp

    END
