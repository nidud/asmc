; HEDIT.ASM--
; Copyright (C) 2017 Doszip Developers -- see LICENSE.TXT
;
; Change history:
; 2017-10-19 - added ClassMode
; 2017-10-14 - created
;
include doszip.inc
include alloc.inc
include string.inc
include stdio.inc
include stdlib.inc
include io.inc
include iost.inc
include consx.inc
include ltype.inc
include cfini.inc

externdef   IDD_TVSeek:dword
externdef   IDD_HELine:dword
externdef   IDD_HEFormat:dword
externdef   CP_ENOMEM:byte
externdef   searchstring:byte

cmsearchidd     proto :dword
continuesearch  proto :ptr
putscreenb      proto :dword, :dword, :ptr
SaveChanges     proto :LPSTR


_USEMLINE   equ 0x01
_USESLINE   equ 0x02
_HEXOFFSET  equ 0x04
_CLASSMODE  equ 0x08

_MAXL       equ 64
_MAXTEXT    equ 49

T_STRING    equ 0x01
T_BINARY    equ 0x02
T_BYTE      equ 0x04
T_WORD      equ 0x08
T_DWORD     equ 0x10
T_QWORD     equ 0x20
T_SIGNED    equ 0x40
T_HEX       equ 0x80

T_NUMBER    equ T_BYTE or T_WORD or T_DWORD or T_QWORD
T_ARRAY     equ T_STRING or T_BINARY

S_LINE      STRUC
flags       db ?
bytes       db ?
boffs       dw ?
S_LINE      ENDS


.data

;******** Resource begin HEStatusline *
;   { 0x0054,   0,   0, { 0,24,80, 1} },
;******** Resource data  *******************
Statusline_RC   dw 0200h,0054h,0000h
                db 0
Statusline_Y    db 24
Statusline_C0   db 80,1
                db 0x3C,0x3F,0x3F,0xF0,7,0x3C,0x3F,0x3F,0xF0,7,0x3C,0x3F,0x3F,0xF0
                db 9,0x3C,0x3F,0x3F,0xF0,7,0x3C,0x3F,0x3F,0xF0,8,0x3C,0x3F,0x3F
                db 0xF0,20,0x3C,0x3F,0x3F,0x3F,0xF0
Statusline_C1   db 6,0x3C
                db ' F1 Help  F2 Save  F3 Search  F4 Goto  F5 Mode   F6 Offset'
                db 0xF0,13,' Esc Quit '
                db 0xF0
Statusline_C2   db 1,' '
IDD_Statusline  dd Statusline_RC

;******** Resource begin HEMenusline *
;   { 0x0050,   0,   0, { 0, 0,80, 1} },
;******** Resource data  *******************
Menusline_RC    dw 0200h,0050h,0000h,0000h
Menusline_C0    db 80,1,0F0h
Menusline_C1    db 80,3Ch,0F0h
Menusline_C2    db 80,' '
IDD_Menusline   dd Menusline_RC

x_cpos  db 12,15,18,21,24,27,30,33,38,41,44,47,50,53,56,59

.code

savefile proc private uses esi edi ebx file:LPSTR, buffer:ptr, fsize:dword

  local path[_MAX_PATH]:byte
  local flags:dword

    lea edi,path

    .repeat

        .if getfattr(strcpy(edi, file)) == -1

            xor eax,eax
            .break
        .endif

        mov flags,eax
        .if eax & _A_RDONLY

            ermsg(0, "The file is Read-Only")
        .endif

        .ifs ogetouth(setfext(edi, ".$$$"), M_WRONLY) <= 0

            xor eax,eax
            .break
        .endif
        mov esi,eax
        mov ebx,fsize
        .if oswrite(esi, buffer, ebx) != ebx

            xor ebx,ebx
        .endif
        _close(esi)
        .if ebx
            remove(file)
            rename(edi, file)
            mov eax,1
        .else
            mov eax,ebx
        .endif
    .until 1
    ret

savefile endp

LToString proc uses esi edi lp:ptr S_LINE, source:LPSTR, dest:LPSTR

    mov edx,lp
    movzx eax,[edx].S_LINE.flags
    mov ecx,eax
    and eax,T_BYTE or T_WORD or T_DWORD or T_QWORD
    mov edi,source
    mov esi,dest

    .switch eax

    .case T_BYTE
        movzx edx,byte ptr [edi]
        mov eax,@CStr("%u")
        .if cl & T_SIGNED
            mov eax,@CStr("%i")
            movsx edx,dl
        .elseif cl & T_HEX
            mov eax,@CStr("%02X")
        .endif
        sprintf(esi, eax, edx)
        .endc

    .case T_WORD
        movzx edx,word ptr [edi]
        mov eax,@CStr("%u")
        .if cl & T_SIGNED
            mov eax,@CStr("%i")
            movsx ecx,cx
        .elseif cl & T_HEX
            mov eax,@CStr("%04X")
        .endif
        sprintf(esi, eax, edx)
        .endc

    .case T_DWORD
        mov eax,@CStr("%u")
        .if cl & T_SIGNED
            mov eax,@CStr("%i")
        .elseif cl & T_HEX
            mov eax,@CStr("%08X")
        .endif
        mov ecx,[edi]
        sprintf(esi, eax, ecx)
        .endc

    .case T_QWORD
        mov eax,@CStr("%llu")
        .if cl & T_SIGNED
            mov eax,@CStr("%lld")
        .elseif cl & T_HEX
            mov eax,@CStr("%016llX")
        .endif
        mov ecx,[edi]
        mov edx,[edi+4]
        sprintf(esi, eax, edx::ecx)
        .endc
    .endsw
    ret
LToString endp

local_update:
    xor eax,eax
    ret

hedit proc uses esi edi ebx file:LPSTR, loffs:DWORD

  local dialog      :dword  ; main dialog pointer
  local cdialog     :dword  ; class dialog
  local rowcnt      :dword  ; screen lines
  local lcount      :dword  ; lines on screen
  local cline       :dword  ; current line
  local scount      :dword  ; bytes on screen
  local bcount      :dword  ; screen size in bytes (page)
  local screen      :dword  ; screen buffer
  local menusline   :dword  ; dialogs for F11/Ctrl-S/Ctrl-M
  local statusline  :dword
  local fsize       :dword  ; file size
  local fbuff       :dword  ; file buffer
  local index       :dword  ; x index into x_cpos table
  local x           :dword  ; x pos from LEFT/RIGHT
  local lbuff[512]  :byte
  local lbc[_MAXL]  :S_LINE ; class table
  local lbh[_MAXL]  :S_LINE ; hex table
  local lptr        :dword  ; pointer to active table
  local rc          :S_RECT ; edit text pos
  local dlgobj      :S_DOBJ
  local cursor      :S_CURSOR
  local flags       :byte   ; main flags
  local rsrows      :byte   ; rect-line count
  local modified    :byte


    mov rc.rc_x,12
    mov rc.rc_y,1
    mov rc.rc_col,_MAXTEXT
    mov rc.rc_row,1

    mov ecx,_MAXL
    lea edi,lbh
    mov eax,0x00001000
    rep stosd
    mov ecx,_MAXL
    mov eax,0x00000104
    rep stosd

    xor eax,eax
    lea edi,STDI
    mov ecx,sizeof(S_IOST)
    rep stosb

    mov cline,eax
    mov index,eax
    mov x,12
    mov modified,al
    mov STDI.ios_flag,eax

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

    mov eax,_scrrow
    mov ebx,IDD_Statusline
    mov [ebx+7],al
    inc al
    mov rsrows,al

    mov flags,_USEMLINE or _USESLINE or _HEXOFFSET

    .if CFGetSection(".hexedit")

        mov ebx,eax
        .if INIGetEntry(ebx, "Flags")

            xtol(eax)
            mov flags,al
        .endif
        .for edi=0: edi < _MAXL: edi++
            .break .if !INIGetEntryID(ebx, edi)
            xtol(eax)
            mov lbc[edi*4].bytes,al
            mov lbc[edi*4].flags,ah
        .endf
    .endif

    mov al,rsrows
    .if flags & _USEMLINE
        dec al
    .endif
    .if flags & _USESLINE
        dec al
    .endif
    mov rowcnt,eax ; adapt to current screen size
    add eax,2
    mul _scrcol
    mov esi,eax

    lea eax,lbh
    .if flags & _CLASSMODE
        lea eax,lbc
    .endif
    mov lptr,eax

    .repeat

        .if osopen(file, 0, M_RDONLY, A_OPEN) == -1
            xor eax,eax
            .break
        .endif
        mov ebx,eax

        _filelength(ebx)
        .if (!eax && !edx) || edx
            .if edx
                ermsg(0, &CP_ENOMEM)
            .endif
            _close(ebx)
            xor eax,eax
            .break
        .endif
        mov fsize,eax
        mov STDI.ios_flag,IO_MEMBUF
        mov STDI.ios_c,eax
        mov STDI.ios_i,0

        add eax,esi
        .if !malloc(eax)
            ermsg(0, &CP_ENOMEM)
            _close(ebx)
            xor eax,eax
            .break
        .endif
        mov screen,eax
        add eax,esi
        mov fbuff,eax
        mov STDI.ios_bp,eax
        osread(ebx, eax, fsize)
        _close(ebx)

        mov al,at_background[B_TextView]
        or  al,at_foreground[F_TextView]
        .if dlscreen(&dlgobj, eax)

            mov dialog,eax
            dlshow(eax)
            mov menusline,rsopen(IDD_Menusline)
            dlshow(eax)
            mov statusline,rsopen(IDD_Statusline)
            .if flags & _USESLINE
                dlshow(eax)
            .endif
            scpath(1, 0, 41, file)
            mov eax,_scrcol
            sub eax,38
            scputf(eax, 0, 0, 0, "%12u byte", fsize)
            mov edx,_scrcol
            sub edx,5
            scputs(edx, 0, 0, 0, "100%")

            .if !(flags & _USEMLINE)

                dlhide(menusline)
            .endif

            CursorGet(&cursor)
            CursorOn()

            push tupdate
            mov tupdate,local_update

            msloop()
            mov esi,1

            .while 1

                .if esi

                    mov eax,cline
                    .if flags & _USEMLINE
                        inc eax
                    .endif
                    _gotoxy(x, eax)

                    mov eax,_scrcol
                    mul rowcnt
                    mov ecx,eax
                    mov edi,screen
                    mov eax,0x20
                    rep stosb

                    mov esi,fsize
                    sub esi,loffs
                    .for ebx=lptr, edx=0, ecx=0: edx < esi, ecx < rowcnt: ecx++
                        movzx eax,[ebx+ecx*4].S_LINE.bytes
                        mov [ebx+ecx*4].S_LINE.boffs,dx
                        add edx,eax
                    .endf
                    .if edx > esi
                        mov edx,esi
                    .endif
                    mov scount,edx
                    mov lcount,ecx
                    .for : edx < esi, ecx < rowcnt: ecx++
                        movzx eax,[ebx+ecx*4].S_LINE.bytes
                        mov [ebx+ecx*4].S_LINE.boffs,dx
                        add edx,eax
                    .endf
                    mov bcount,edx

                    .for esi=screen, ebx=0: ebx < lcount: ebx++, esi += _scrcol

                        .if flags & _HEXOFFSET
                            mov eax,@CStr("%p    ")
                        .else
                            mov eax,@CStr("%010u  ")
                        .endif
                        mov edx,lptr
                        movzx edi,[edx+ebx*4].S_LINE.boffs
                        add edi,loffs
                        sprintf(esi, eax, edi)
                        mov ecx,fsize
                        sub ecx,edi
                        add edi,fbuff

                        mov edx,lptr
                        movzx eax,[edx+ebx*4].S_LINE.flags
                        and eax,T_NUMBER or T_ARRAY

                        .switch eax
                          .case T_STRING
                            push esi
                            xchg esi,edi
                            movzx eax,[edx+ebx*4].S_LINE.bytes
                            .if ecx > eax
                                mov ecx,eax
                            .endif
                            add edi,12
                            .if ecx > _MAXTEXT
                                mov ecx,_MAXTEXT
                            .endif
                            rep movsb
                            pop esi
                            lea ecx,[esi+51+12]
                            sprintf(ecx, "CHAR[%u]", eax)
                            .endc

                          .case T_BINARY
                            push esi
                            push ebx
                            movzx eax,[edx+ebx*4].S_LINE.bytes
                            .if ecx > eax
                                mov ecx,eax
                            .endif
                            .if ecx > _MAXTEXT
                                mov ecx,_MAXTEXT
                            .endif
                            mov ebx,ecx
                            mov esi,edi
                            lea edi,lbuff
                            rep movsb
                            push eax
                            lea esi,lbuff
                            btohex(esi, ebx)
                            pop eax
                            mov ecx,ebx
                            add ecx,ecx
                            .if ecx > _MAXTEXT
                                mov ecx,_MAXTEXT
                            .endif
                            pop  ebx
                            pop  edi
                            push edi
                            add  edi,12
                            rep  movsb
                            pop  esi
                            lea  ecx,[esi+51+12]
                            sprintf(ecx, "BYTE[%u]", eax)
                            .endc

                          .case T_BYTE
                          .case T_WORD
                          .case T_DWORD
                          .case T_QWORD
                            push eax
                            lea eax,[esi+12]
                            lea edx,[edx+ebx*4]
                            push edx
                            LToString(edx, edi, eax)
                            pop edx
                            pop eax
                            movzx edx,[edx].S_LINE.flags
                            mov ecx,@CStr("unsigned")
                            .if edx & T_SIGNED
                                mov ecx,@CStr("signed")
                            .elseif edx & T_HEX
                                mov ecx,@CStr("hexadecimal")
                            .endif
                            mov edx,@CStr("BYTE")
                            .if eax == T_DWORD
                                mov edx,@CStr("DWORD")
                            .elseif eax == T_WORD
                                mov edx,@CStr("WORD")
                            .elseif eax == T_QWORD
                                mov edx,@CStr("QWORD")
                            .endif
                            lea eax,[esi+51+12]
                            sprintf(eax, "%s(%s)", edx, ecx)
                            .endc

                          .default
                            .if ecx > 16
                                mov ecx,16
                            .endif
                            push ebx
                            push esi
                            xchg esi,edi
                            add edi,12
                            lea ebx,[edi+51]
                            xor edx,edx
                            .repeat
                                .if edx == 8
                                    mov al,179
                                    stosb
                                    inc edi
                                .endif
                                lodsb
                                mov [ebx],al
                                .if !al
                                    mov byte ptr [ebx],' '
                                .endif
                                mov ah,al
                                and eax,0x0FF0
                                shr al,4
                                or  eax,0x3030
                                .if ah > 0x39
                                    add ah,7
                                .endif
                                .if al > 0x39
                                    add al,7
                                .endif
                                stosw
                                inc edi
                                inc ebx
                                inc edx
                            .untilcxz
                            pop esi
                            pop ebx
                        .endsw
                        mov eax,1
                    .endf

                    .if eax
                        .if flags & _USEMLINE
                            mov eax,scount
                            add eax,loffs
                            .ifz
                                mov eax,100
                            .else
                                mov ecx,100
                                mul ecx
                                mov ecx,fsize
                                div ecx
                                and eax,0x7F
                                .if eax > 100
                                    mov eax,100
                                .endif
                            .endif
                            mov edx,_scrcol
                            sub edx,5
                            scputf(edx, 0, 0, 0, "%3d", eax)
                            .if modified
                                scputc(0, 0, 1, '*')
                            .else
                                scputc(0, 0, 1, ' ')
                            .endif
                        .endif
                        .if flags & _USESLINE
                            mov edx,statusline
                            movzx edx,[edx].S_DOBJ.dl_rect.rc_y
                            .if flags & _CLASSMODE
                                mov eax,@CStr("Hex  ")
                            .else
                                mov eax,@CStr("Class")
                            .endif
                            scputs(42, edx, 0, 5, eax)
                        .endif
                        mov eax,fsize
                        .if eax
                            xor eax,eax
                            .if flags & _USEMLINE
                                inc eax
                            .endif
                            putscreenb(eax, rowcnt, screen)
                        .endif
                    .endif
                .endif

                mov ebx,cline
                mov edx,lptr
                mov al,[edx+ebx*4].S_LINE.flags
                and al,T_ARRAY or T_NUMBER

                .if al

                    mov ecx,fsize
                    movzx esi,[edx+ebx*4].S_LINE.boffs
                    add esi,loffs
                    sub ecx,esi
                    add esi,fbuff
                    lea edi,lbuff

                    push esi
                    push edi
                    .switch al
                      .case T_STRING
                        movzx eax,[edx+ebx*4].S_LINE.bytes
                        .if ecx > eax
                            mov ecx,eax
                        .endif
                        rep movsb
                        mov byte ptr [edi],0
                        .endc
                      .case T_BINARY
                        movzx eax,[edx+ebx*4].S_LINE.bytes
                        .if ecx > eax
                            mov ecx,eax
                        .endif
                        push ecx
                        rep movsb
                        pop ecx
                        btohex(&lbuff, ecx)
                        .endc
                      .case T_BYTE
                      .case T_WORD
                      .case T_DWORD
                      .case T_QWORD
                        lea edx,[edx+ebx*4]
                        LToString(edx, esi, edi)
                        .endc
                    .endsw
                    pop edi
                    pop esi
                    mov eax,ebx
                    mov edx,lptr
                    lea ebx,[edx+ebx*4]
                    .if flags & _USEMLINE
                        inc eax
                    .endif
                    mov rc.rc_y,al
                    mov ecx,256
                    .if [ebx].S_LINE.flags & T_BINARY
                        shl ecx,1
                    .endif
                    dledit(edi, rc, ecx, 0)
                    push eax
                    .if !([ebx].S_LINE.flags & T_STRING)
                        .if [ebx].S_LINE.flags & T_BINARY
                            hextob(edi)
                        .else
                            .if [ebx].S_LINE.flags & T_HEX
                                _xtoi64(edi)
                            .else
                                _atoi64(edi)
                            .endif
                            mov dword ptr [edi],eax
                            mov dword ptr [edi+4],edx
                        .endif
                    .endif
                    mov ecx,fsize
                    movzx eax,[ebx].S_LINE.boffs
                    movzx ebx,[ebx].S_LINE.bytes
                    add eax,loffs
                    add eax,ebx
                    .if eax > ecx
                        sub eax,ebx
                        .if ecx >= eax
                            sub ecx,eax
                            mov ebx,ecx
                        .else
                            xor ebx,ebx
                        .endif
                    .endif
                    .if ebx
                        .if memcmp(esi, edi, ebx)
                            memcpy(esi, edi, ebx)
                            mov modified,1
                        .endif
                    .endif
                    pop eax
                .else
                    tgetevent()
                .endif

                xor esi,esi
                mov ebx,cline
                mov edi,lptr
                lea edi,[edi+ebx*4]

                .switch eax

                  .case MOUSECMD

                    .endc .if mousep() == 2
                    .endc .if !eax
                    mousey()
                    inc eax
                    .endc .if !(flags & _USESLINE) || al != rsrows
                    msloop()
                    mousex()
                    .if al && al <= 7
                        .gotosw(KEY_F1)
                    .endif
                    .if al >= 10 && al <= 16
                        .gotosw(KEY_F2)
                    .endif
                    .if al >= 19 && al <= 27
                        .gotosw(KEY_F3)
                    .endif
                    .if al >= 30 && al <= 36
                        .gotosw(KEY_F4)
                    .endif
                    .if al >= 39 && al <= 46
                        .gotosw(KEY_F5)
                    .endif
                    .if al >= 49 && al <= 57
                        .gotosw(KEY_F6)
                    .endif
                    .if al >= 71 && al <= 78
                        .gotosw(KEY_F10)
                    .endif
                    msloop()
                    .endc

                  .case KEY_F1
                    view_readme(HELPID_16)
                    .endc

                  .case KEY_F2
                    .if savefile(file, fbuff, fsize)
                        mov modified,0
                        mov esi,1
                    .endif
                    .endc

                  .case KEY_F3
                    and STDI.ios_flag,not IO_SEARCHMASK
                    mov eax,fsflag
                    and eax,IO_SEARCHMASK
                    or  STDI.ios_flag,eax
                    xor eax,eax
                    .if fsize >= 16
                        .if cmsearchidd(STDI.ios_flag)
                            mov STDI.ios_flag,edx
                            and edx,IO_SEARCHCUR or IO_SEARCHSET
                            push edx
                            continuesearch(&loffs)
                            pop edx
                            or  STDI.ios_flag,edx
                        .endif
                    .endif
                    push eax
                    and fsflag,not IO_SEARCHMASK
                    mov eax,STDI.ios_flag
                    and STDI.ios_flag,not (IO_SEARCHSET or IO_SEARCHCUR)
                    and eax,IO_SEARCHMASK
                    or  fsflag,eax
                    pop eax
                    .if eax
                        inc esi
                    .endif
                    .endc

                  .case KEY_F4
                    .if rsopen(IDD_TVSeek)
                        mov ebx,eax
                        mov edx,loffs
                        sprintf([ebx+24], "%08Xh", edx)
                        dlinit(ebx)
                        rsevent(IDD_TVSeek, ebx)
                        push eax
                        strtolx([ebx+24])
                        dlclose(ebx)
                        pop eax
                        .if eax && edx <= fsize
                            mov loffs,edx
                            mov esi,1
                        .endif
                    .endif
                    .endc

                  .case KEY_F5
                    xor flags,_CLASSMODE
                    lea eax,lbh
                    .if flags & _CLASSMODE
                        lea eax,lbc
                    .endif
                    mov lptr,eax
                    mov esi,1
                    .endc

                  .case KEY_F6
                    xor flags,_HEXOFFSET
                    mov esi,1
                    .endc

                  .case KEY_F8
                    .if wgetfile(&lbuff, "*.cl", _WSAVE)
                        _close(eax)
                        .if INIAlloc()
                            mov esi,eax
                            .if INIAddSection(esi, ".")
                                mov ebx,eax
                                .for edi=0: edi < rowcnt: edi++

                                    movzx eax,lbc[edi*4].bytes
                                    mov ah,lbc[edi*4].flags
                                    INIAddEntryX(ebx, "%d=%X", edi, eax)
                                .endf
                            .endif
                            INIWrite(esi, &lbuff)
                            INIClose(esi)
                            xor esi,esi
                        .endif
                    .endif
                    .endc

                  .case KEY_F9
                    .if wgetfile(&lbuff, "*.cl", _WOPEN)
                        _close(eax)
                        .if INIRead(0, &lbuff)
                            mov esi,eax
                            .if INIGetSection(esi, ".")
                                mov ebx,eax
                                .for edi=0: edi < _MAXL: edi++
                                    .break .if !INIGetEntryID(ebx, edi)
                                    xtol(eax)
                                    mov lbc[edi*4].bytes,al
                                    mov lbc[edi*4].flags,ah
                                .endf
                            .endif
                            INIClose(esi)
                            mov esi,1
                        .endif
                    .endif
                    .endc

                  .case KEY_F10
                  .case KEY_ESC
                  .case KEY_ALTX
                    .if modified
                        .if SaveChanges(file)
                            savefile(file, fbuff, fsize)
                        .endif
                    .endif
                    .break

                  .case KEY_ALTF5
                  .case KEY_CTRLB
                    dlhide(dialog)
                    .while !getkey()
                    .endw
                    dlshow(dialog)
                    .endc

                  .case KEY_CTRLM
                    xor flags,_USEMLINE
                    .if flags & _USEMLINE
                        dlshow(menusline)
                        dec rowcnt
                    .else
                        dlhide(menusline)
                        inc rowcnt
                    .endif
                    mov esi,1
                    .endc

                  .case KEY_CTRLS
                    xor flags,_USESLINE
                    .if flags & _USESLINE
                        dlshow(statusline)
                        dec rowcnt
                        mov edx,statusline
                        mov ecx,cline
                        .if flags & _USEMLINE
                            inc ecx
                        .endif
                        movzx eax,[edx].S_DOBJ.dl_rect.rc_y
                        .if eax == ecx
                            dec cline
                        .endif
                    .else
                        dlhide(statusline)
                        inc rowcnt
                    .endif
                    mov esi,1
                    .endc

                  .case KEY_F11
                    .if !(flags & _USESLINE or _USEMLINE)
                        PushEvent(KEY_CTRLS)
                        .gotosw(KEY_CTRLM)
                    .endif
                    .if flags & _USEMLINE
                        PushEvent(KEY_CTRLM)
                    .endif
                    .if flags & _USESLINE
                        .gotosw(KEY_CTRLS)
                    .endif
                    .endc

                  ;--

                  .case KEY_CTRLE
                  .case KEY_UP
                    xor eax,eax
                    .if eax == cline
                        mov eax,loffs
                        .if eax
                            .if eax > fsize
                                mov eax,fsize
                            .else
                                movzx ecx,[edi].S_LINE.bytes
                                .if eax <= ecx
                                    xor eax,eax
                                .else
                                    sub eax,ecx
                                .endif
                            .endif
                        .endif
                        .if eax != loffs
                            mov loffs,eax
                            mov esi,1
                        .endif
                    .else
                        dec cline
                        mov esi,1
                    .endif
                    .endc

                  .case KEY_TAB
                    .endc .if flags & _CLASSMODE
                    mov eax,cline
                    shl eax,4
                    add eax,loffs
                    add eax,index
                    add eax,1
                    .endc .if eax >= fsize
                    mov eax,index
                    mov edx,x
                    .if eax < 15
                        inc eax
                        mov dl,x_cpos[eax]
                        mov index,eax
                        mov x,edx
                        mov esi,1
                        .endc
                    .endif
                    mov dl,x_cpos
                    mov x,edx
                    mov index,0

                  .case KEY_CTRLX
                  .case KEY_DOWN
                    movzx ecx,[edi].S_LINE.bytes
                    movzx eax,[edi].S_LINE.boffs
                    add eax,loffs
                    .if ecx == 16
                        add eax,index
                    .endif
                    add eax,ecx
                    .endc .if eax >= fsize
                    mov eax,ebx
                    .if flags & _USEMLINE
                        inc eax
                    .endif
                    inc eax
                    mov edx,statusline
                    movzx edx,[edx].S_DOBJ.dl_rect.rc_y
                    .if !(flags & _USESLINE)
                        inc edx
                    .endif
                    .if eax == edx
                        add loffs,ecx
                    .else
                        inc cline
                    .endif
                    mov esi,1
                    .endc

                  .case KEY_CTRLR
                  .case KEY_PGUP
                    .endc .if !loffs
                    mov eax,bcount
                    .if eax > loffs
                        .gotosw(KEY_HOME)
                    .endif
                    sub loffs,eax
                    mov esi,1
                    .endc

                  .case KEY_CTRLC
                  .case KEY_PGDN
                    mov eax,bcount
                    add eax,eax
                    add eax,loffs
                    .if eax > fsize
                        .gotosw(KEY_END)
                    .endif
                    sub eax,bcount
                    mov loffs,eax
                    mov esi,1
                    .endc

                  .case KEY_LEFT
                    .endc .if flags & _CLASSMODE
                    mov eax,index
                    mov edx,x
                    movzx ecx,x_cpos[eax]
                    .if eax
                        .if ecx == edx
                            dec eax
                            mov dl,x_cpos[eax]
                            inc edx
                        .else
                            dec edx
                        .endif
                        mov index,eax
                        mov x,edx
                        mov esi,1
                    .elseif edx > ecx
                        dec x
                        mov esi,1
                    .endif
                    .endc

                  .case KEY_RIGHT
                    .endc .if flags & _CLASSMODE
                    mov eax,index
                    mov edx,x
                    .if eax <= 15
                        movzx ecx,x_cpos[eax]
                        .if ecx != edx
                            .if eax != 15
                                inc eax
                                mov dl,x_cpos[eax]
                            .endif
                        .else
                            inc edx
                        .endif
                        mov ecx,cline
                        shl ecx,4
                        add ecx,eax
                        add ecx,loffs
                        .endc .if ecx >= fsize
                        mov index,eax
                        mov x,edx
                        mov esi,1
                    .endif
                    .endc

                  .case KEY_CTRLHOME
                  .case KEY_HOME
                    sub eax,eax
                    mov loffs,eax
                    mov index,eax
                    mov cline,eax
                    mov al,x_cpos
                    mov x,eax
                    mov esi,1
                    .endc

                  .case KEY_CTRLEND
                  .case KEY_END
                    mov ecx,fsize
                    mov edx,rowcnt
                    mov eax,edx
                    shl eax,4
                    inc eax
                    .if eax < ecx
                        sub eax,ecx
                        not eax
                        add eax,18
                        and eax,-16
                        mov loffs,eax
                    .endif
                    sub ecx,loffs
                    mov eax,ecx
                    shr ecx,4
                    and eax,15
                    .ifnz
                        dec eax
                    .else
                        mov eax,15
                        .if ecx
                            dec ecx
                        .endif
                    .endif
                    mov index,eax
                    mov al,x_cpos[eax]
                    mov x,eax
                    mov cline,ecx
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

                  .case KEY_SHIFTF3
                  .case KEY_CTRLL
                    .if continuesearch(&loffs)
                        .gotosw(KEY_CTRLHOME)
                    .endif
                    .endc

                  .case KEY_ENTER
                    .endc .if !(flags & _CLASSMODE)
                    .endc .if !rsopen(IDD_HELine)
                    movzx ecx,[edi].S_LINE.bytes
                    mov edi,eax
                    mov ebx,[edi].S_DOBJ.dl_object
                    mov edx,[ebx].S_TOBJ.to_data
                    push ecx
                    sprintf(edx, "%d", ecx)
                    pop ecx
                    mov edx,[ebx].S_TOBJ.to_data[16]
                    sprintf(edx, "%d", ecx)
                    dlinit(edi)
                    mov esi,rsevent(IDD_HELine, edi)
                    .if esi == 1
                        mov ebx,atol([ebx].S_TOBJ.to_data)
                    .elseif esi == 2
                        mov ebx,atol([ebx].S_TOBJ.to_data[16])
                    .endif
                    dlclose(edi)

                    .endc .if !esi

                    .if esi < 3
                        mov edx,esi
                        mov eax,ebx
                        .if eax
                            .if eax > 255
                                mov eax,16
                                xor edx,edx
                            .endif
                        .else
                            mov eax,16
                            xor edx,edx
                        .endif
                    .else
                        .if rsmodal(IDD_HEFormat) == 1
                            mov edx,T_SIGNED
                        .elseif edx == 3
                            mov edx,T_HEX
                        .else
                            xor edx,edx
                        .endif
                        .switch esi
                          .case 3: mov eax,1  : or edx,T_BYTE  : .endc
                          .case 4: mov eax,2  : or edx,T_WORD  : .endc
                          .case 5: mov eax,4  : or edx,T_DWORD : .endc
                          .case 6: mov eax,8  : or edx,T_QWORD : .endc
                        .endsw
                    .endif
                    mov ecx,cline
                    mov lbc[ecx*4].bytes,al
                    mov lbc[ecx*4].flags,dl
                    mov esi,1
                    .endc

                  .default
                    .if flags & _CLASSMODE
                        mov ebx,cline
                        movzx ebx,lbc[ebx*4].flags
                        .endc .if ebx & T_STRING or T_BYTE or T_WORD or T_DWORD or T_QWORD
                    .endif

                    movzx eax,al
                    mov ebx,eax
                    .endc .if !(_ltype[eax+1] & _HEX)
                    mov eax,cline
                    shl eax,4
                    add eax,index
                    add eax,loffs
                    .endc .if eax > fsize
                    add eax,fbuff
                    mov edx,eax
                    .if bl > '9'
                        or bl,0x20
                        sub bl,'a'-10
                    .else
                        sub bl,'0'
                    .endif
                    mov ecx,index
                    mov cl,x_cpos[ecx]
                    mov al,[edx]
                    .if ecx == x
                        shl bl,4
                        and al,0x0F
                    .else
                        and al,0xF0
                    .endif
                    or  al,bl
                    mov [edx],al
                    mov modified,1
                    mov esi,1
                    .gotosw(KEY_RIGHT)
                .endsw
            .endw

            .if CFAddSection(".hexedit")

                mov ebx,eax
                mov esi,rowcnt
                movzx ecx,flags
                INIAddEntryX(ebx, "Flags=%X", ecx)
                inc esi
                .for edi=0: edi <= esi: edi++
                    movzx eax,lbc[edi*4].bytes
                    mov ah,lbc[edi*4].flags
                    INIAddEntryX(ebx, "%d=%X", edi, eax)
                .endf
            .endif

            free(screen)
            dlclose(statusline)
            dlclose(menusline)
            dlclose(dialog)
            CursorSet(&cursor)
            pop eax
            mov tupdate,eax
        .else
            free(screen)
            mov eax,1
        .endif
    .until 1
    ret

hedit endp

    END
