; CMSETUP.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include io.inc
include string.inc
include stdlib.inc
include crtl.inc
include errno.inc
include stdio.inc
include malloc.inc
include cfini.inc

command proto :dword
__AT__  equ 1

    .data

cf_panel        db 0
cf_panel_upd    db 0
cf_screen_upd   db 0

color_Blue  db 00h,0Fh,0Fh,07h,08h,00h,00h,07h
            db 08h,00h,0Ah,0Bh,00h,0Fh,0Fh,0Fh
            db 00h,10h,70h,70h,40h,30h,30h,70h
            db 30h,30h,30h,00h,10h,10h,07h,06h
color_Black db 07h,07h,0Fh,07h,08h,08h,07h,07h
            db 08h,07h,0Ah,0Bh,0Fh,0Bh,0Bh,0Bh
            db 00h,00h,00h,10h,30h,10h,10h,00h
            db 10h,10h,00h,00h,00h,00h,07h,07h
color_Mono  db 0Fh,0Fh,0Fh,0Fh,0Fh,0Fh,0Fh,0Fh
            db 0Fh,0Fh,0Fh,0Fh,0Fh,0Fh,0Fh,0Fh
            db 00h,00h,00h,00h,00h,70h,70h,00h
            db 70h,70h,70h,00h,00h,00h,0Fh,0Fh
color_White db 00h,07h,0Fh,07h,08h,07h,00h,07h
            db 08h,00h,0Ah,0Bh,00h,07h,08h,08h
            db 00h,10h,0F0h,0F0h,40h,70h,70h,70h
            db 80h,30h,70h,70h,00h,00h,07h,07h
color_Norton db 07h,0Bh,0Bh,0Bh,0Bh,00h,00h,07h
            db 08h,0Fh,0Eh,0Bh,0Fh,00h,0Eh,0Eh
            db 00h,10h,30h,30h,40h,0F0h,20h,70h
            db 0F0h,30h,00h,00h,30h,30h,0Fh,0Fh

color_Table dd color_Blue
            dd color_Black
            dd color_Mono
            dd color_White
            dd color_Norton

    .code

ID_UBEEP        equ 1*16 ; Use Beep
ID_MOUSE        equ 2*16 ; Use Mouse
ID_IOSFN        equ 3*16 ; Use Long File Names
ID_CLIPB        equ 4*16 ; Use System Clipboard
ID_ASCII        equ 5*16 ; Use Ascii symbol
ID_NTCMD        equ 6*16 ; Use NT Prompt
ID_CMDENV       equ 7*16 ; CMD Compatible Mode
ID_IMODE        equ 8*16 ; Init screen mode on startup
ID_DELHISTORY   equ 9*16
ID_ESCUSERSCR   equ 10*16

cmsystem proc uses esi edi ebx

    .if rsopen(IDD_DZSystemOptions)

        push thelp
        mov thelp,event_help
        mov ebx,eax
        mov eax,cflag
        .if eax & _C_DELHISTORY

            or [ebx].S_TOBJ.to_flag[ID_DELHISTORY],_O_FLAGB
        .endif

        .if eax & _C_ESCUSERSCR

            or [ebx].S_TOBJ.to_flag[ID_ESCUSERSCR],_O_FLAGB
        .endif
        tosetbitflag([ebx].S_DOBJ.dl_object, 8, _O_FLAGB, console)
        dlinit(ebx)
        rsevent(IDD_DZSystemOptions, ebx)
        mov esi,eax
        togetbitflag([ebx].S_DOBJ.dl_object, 10, _O_FLAGB)
        dlclose(ebx)
        pop eax
        mov thelp,eax
        mov eax,esi
        .if eax

            mov eax,edx
            mov edx,cflag
            and edx,not (_C_DELHISTORY or _C_ESCUSERSCR)
            .if eax & 100h ; Auto Delete History

                or edx,_C_DELHISTORY
            .endif
            .if eax & 200h ; Use Esc for user screen

                or edx,_C_ESCUSERSCR
            .endif
            mov cflag,edx
            mov ecx,console
            mov byte ptr console,al
            and eax,CON_MOUSE or CON_IOSFN or CON_CMDENV
            and ecx,CON_MOUSE or CON_IOSFN or CON_CMDENV
            .if ecx != eax

                mov ecx,ENABLE_WINDOW_INPUT
                .if eax & CON_MOUSE

                    or ecx,ENABLE_MOUSE_INPUT
                .endif
                SetConsoleMode(hStdInput, ecx)
                .if cf_panel == 1

                    mov cf_panel_upd,1
                .else
                    redraw_panels()
                .endif
            .endif
            setasymbol()
            mov eax,1
        .endif
    .endif
    ret

event_help:
    view_readme(HELPID_15)
    retn

cmsystem endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    option proc:private

ID_MEUSLINE equ 1*16
ID_USEDATE  equ 2*16
ID_USETIME  equ 3*16
ID_USELDATE equ 4*16
ID_USELTIME equ 5*16
ID_COMMANDLINE  equ 6*16
ID_STAUSLINE    equ 7*16
ID_ATTRIB   equ 8*16
ID_STANDARD equ 9*16
ID_LOAD     equ 10*16
ID_SAVE     equ 11*16

event_reload proc

    .if cf_panel == 0

        dlhide(tdialog)
        apiupdate()
        dlshow(tdialog)
        msloop()
        mov eax,_C_NORMAL
    .else
        msloop()
        mov cf_screen_upd,1
        mov eax,_C_ESCAPE
    .endif
    ret

event_reload endp

event_loadcolor proc uses esi

local path[_MAX_PATH]:byte

    .if wgetfile(addr path, "*.pal", _WOPEN)

        mov esi,eax
        osread(esi, addr at_foreground, sizeof(S_COLOR))
        xchg eax,esi
        _close(eax)
        mov eax,_C_NORMAL

        .if esi == sizeof(S_COLOR)

            event_reload()
        .endif
    .endif
    ret

event_loadcolor endp

event_savecolor proc

  local path[_MAX_PATH]:byte

    .if wgetfile(addr path, "*.pal", _WSAVE)

        push eax
        oswrite(eax, addr at_foreground, sizeof(S_COLOR))
        _close()
    .endif

    mov eax,_C_NORMAL
    ret

event_savecolor endp

ifdef __AT__

event_editat proc

    editattrib()
    test eax,eax
    jnz event_reload
    mov eax,_C_NORMAL
    ret

event_editat endp

endif

event_standard proc

    mov eax,tdialog
    mov ax,[eax+4]
    add ax,0B0Ch
    mov ecx,IDD_DZDefaultColor
    mov [ecx+6],ax

    .if rsmodal(ecx)

        .if eax < 6

            dec eax
            mov eax,color_Table[eax*4]
            memcpy(addr at_foreground, eax, sizeof(S_COLOR))
            event_reload()
        .else
            xor eax,eax
        .endif
    .else
        inc eax
    .endif
    ret

event_standard endp

    option  proc: PUBLIC

cmscreen proc uses esi edi

    mov cf_screen_upd,0

    .if rsopen(IDD_DZScreenOptions)

        mov edi,eax
        mov dl,_O_FLAGB
        mov eax,cflag
        .if eax & _C_MENUSLINE
            or [edi][ID_MEUSLINE],dl
        .endif
        .if eax & _C_COMMANDLINE
            or [edi][ID_COMMANDLINE],dl
        .endif
        .if eax & _C_STATUSLINE
            or [edi][ID_STAUSLINE],dl
        .endif
        mov eax,console
        .if eax & CON_UDATE
            or [edi][ID_USEDATE],dl
        .endif
        .if eax & CON_LDATE
            or [edi][ID_USELDATE],dl
        .endif
        .if eax & CON_UTIME
            or [edi][ID_USETIME],dl
        .endif
        .if eax & CON_LTIME
            or [edi][ID_USELTIME],dl
        .endif
ifdef __AT__
        mov [edi].S_TOBJ.to_proc[ID_ATTRIB],event_editat
else
        or  [edi].S_TOBJ.to_flag[ID_ATTRIB],_O_STATE
endif
        mov [edi].S_TOBJ.to_proc[ID_STANDARD],event_standard
        mov [edi].S_TOBJ.to_proc[ID_LOAD],event_loadcolor
        mov [edi].S_TOBJ.to_proc[ID_SAVE],event_savecolor
        dlinit(edi)
        rsevent(IDD_DZScreenOptions, edi)
        mov esi,eax
        lea eax,[edi+16]
        togetbitflag(eax, 7, _O_FLAGB)
        dlclose( edi )  ; return bit-flag in DX
        mov eax,esi
        mov esi,cflag
        .if eax
            mov eax,edx
            mov edx,console
            and edx,not (CON_UTIME or CON_UDATE or CON_LTIME or CON_LDATE)

            .if al & 02h
                or edx,CON_UDATE
            .endif
            .if al & 08h
                or edx,CON_LDATE
            .endif
            .if al & 04h
                or edx,CON_UTIME
            .endif
            .if al & 10h
                or edx,CON_LTIME
            .endif
            and esi,not (_C_MENUSLINE or _C_STATUSLINE or _C_COMMANDLINE)
            .if al & 01h
                or esi,_C_MENUSLINE
            .endif
            .if al & 20h
                or esi,_C_COMMANDLINE
            .endif
            .if al & 40h
                or esi,_C_STATUSLINE
            .endif
            .if console != edx
                mov console,edx
                .if cflag & _C_MENUSLINE
                    scputw(60, 0, 20, ' ')
                .endif
            .endif
            .if cflag != esi || cf_screen_upd
                mov cf_screen_upd,0
                mov cflag,esi
                .if cf_panel == 1
                    dlhide(tdialog)
                .endif
                apiupdate()
                .if cf_panel == 1
                    dlshow(tdialog)
                .endif
            .endif
        .endif
        mov eax,_C_NORMAL
    .endif
    ret
cmscreen endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

cmpanel proc uses ebx

    .if rsopen(IDD_DZPanelOptions)

        mov ebx,eax
        mov edx,_O_FLAGB
        mov eax,cflag
        .if eax & _C_INSMOVDN
            or [ebx+1*16],dl
        .endif
        .if eax & _C_SELECTDIR
            or [ebx+2*16],dl
        .endif
        .if eax & _C_SORTDIR
            or [ebx+3*16],dl
        .endif
        .if eax & _C_CDCLRDONLY
            or [ebx+4*16],dl
        .endif
        .if eax & _C_VISUALUPDATE
            or [ebx+5*16],dl
        .endif
        dlinit(ebx)
        rsevent(IDD_DZPanelOptions, ebx)
        push eax
        mov eax,ebx
        add eax,sizeof(S_DOBJ)
        togetbitflag(eax, 4, _O_FLAGB)
        dlclose(ebx)
        pop eax

        .if eax

            mov eax,edx
            and path_a.ws_flag,not _W_SORTSUB
            and path_b.ws_flag,not _W_SORTSUB
            mov edx,cflag
            and edx,not (_C_INSMOVDN or _C_SELECTDIR or _C_SORTDIR or _C_CDCLRDONLY or _C_VISUALUPDATE)
            .if al & 1

                or edx,_C_INSMOVDN
            .endif
            .if al & 2

                or edx,_C_SELECTDIR
            .endif
            .if al & 4

                or edx,_C_SORTDIR
                or path_a.ws_flag,_W_SORTSUB
                or path_b.ws_flag,_W_SORTSUB
            .endif
            .if al & 8

                or edx,_C_CDCLRDONLY
            .endif
            .if al & 16

                or edx,_C_VISUALUPDATE
            .endif
            .if cflag != edx

                mov cflag,edx
                mov byte ptr _diskflag,1
            .endif
            mov eax,1
        .endif
    .endif
    ret

cmpanel endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

cmconfirm proc uses ebx

    .if rsopen(IDD_DZConfirmations)

        mov ebx,eax
        mov eax,config.c_cflag
        shr eax,16
        tosetbitflag([ebx].S_DOBJ.dl_object, 7, _O_FLAGB, eax)
        dlinit(ebx)
        rsevent(IDD_DZConfirmations, ebx)
        push eax
        togetbitflag([ebx].S_DOBJ.dl_object, 7, _O_FLAGB)
        dlclose(ebx)

        pop eax
        .if eax

            mov eax,config.c_cflag
            and eax,not 007F0000h
            shl edx,16
            or  eax,edx
            mov config.c_cflag,eax
        .endif
    .endif
    ret

cmconfirm endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

cmcompression proc uses ebx

    .if rsopen(IDD_DZCompression)

        mov ebx,eax
        mov eax,compresslevel

        .if al > 9
            mov al,6
            mov compresslevel,eax
        .endif

        inc eax
        shl eax,4
        add eax,ebx
        or  [eax].S_DOBJ.dl_flag,_O_RADIO

        .if cflag & _C_ZINCSUBDIR

            or [ebx].S_DOBJ.dl_flag[11*16],_O_FLAGB
        .endif

        dlinit(ebx)

        .if rsevent(IDD_DZCompression, ebx)

            mov eax,cflag
            and eax,not _C_ZINCSUBDIR
            .if [ebx].S_DOBJ.dl_flag[11*16] & _O_FLAGB

                or eax,_C_ZINCSUBDIR
            .endif
            mov cflag,eax

            xor eax,eax
            mov edx,ebx

            .repeat
                add edx,sizeof(S_TOBJ)
                .break .if [edx].S_DOBJ.dl_flag & _O_RADIO
                inc eax
            .until eax == 10

            .if eax == 10

                mov eax,6
            .endif
            mov compresslevel,eax
        .endif
        dlclose(ebx)
    .endif
    ret

cmcompression endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

cmoptions proc uses esi ebx

    mov cf_panel,1
    mov cf_panel_upd,0

    .if rsopen(IDD_DZConfiguration)

        mov ebx,eax
        mov [ebx].S_TOBJ.to_proc[4*16],toption
        mov [ebx].S_TOBJ.to_proc[5*16],cmconfirm
        mov [ebx].S_TOBJ.to_proc[6*16],cmcompression
        mov [ebx].S_TOBJ.to_proc[1*16],cmsystem
        mov [ebx].S_TOBJ.to_proc[2*16],cmscreen
        mov [ebx].S_TOBJ.to_proc[3*16],cmpanel

        .if cflag & _C_AUTOSAVE

            or byte ptr [ebx+7*16],_O_FLAGB
        .endif

        dlinit(ebx)
        rsevent(IDD_DZConfiguration, ebx)
        push [ebx+7*16]
        dlclose(ebx)

        mov cf_panel_upd,0
        pop eax
        .if edx
            and cflag,not _C_AUTOSAVE
            .if al & _O_FLAGB
                or cflag,_C_AUTOSAVE
            .endif
        .endif
        redraw_panels()
    .endif
    mov cf_panel,0
    ret
cmoptions endp

ID_MIN_X    equ 1*16
ID_MIN_Y    equ 2*16
ID_MIN_COL  equ 3*16
ID_MIN_ROW  equ 4*16
ID_MAX_X    equ 5*16
ID_MAX_Y    equ 6*16
ID_MAX_COL  equ 7*16
ID_MAX_ROW  equ 8*16
ID_DEFAULT  equ 9*16

cmscreensize proc uses esi edi ebx

  local ci:CONSOLE_SCREEN_BUFFER_INFO,
    rc:RECT, maxcol, maxrow

    .repeat

        .break .if !GetConsoleScreenBufferInfo(hStdOutput, addr ci)
        mov ecx,GetConsoleWindow()
        .break .if !GetWindowRect(ecx, addr rc)
        .break .if !rsopen(IDD_ConsoleSize)
        mov ebx,eax

        strcpy([ebx+ID_MIN_X].S_TOBJ.to_data, "0")
        strcpy([ebx+ID_MIN_Y].S_TOBJ.to_data, "0")
        strcpy([ebx+ID_MAX_X].S_TOBJ.to_data, "0")
        strcpy([ebx+ID_MAX_Y].S_TOBJ.to_data, "0")
        strcpy([ebx+ID_MIN_COL].S_TOBJ.to_data, "40")
        strcpy([ebx+ID_MIN_ROW].S_TOBJ.to_data, "16")
        movzx eax,ci.dwMaximumWindowSize.x
        sprintf([ebx+ID_MAX_COL].S_TOBJ.to_data, "%d", eax)
        movzx eax,ci.dwMaximumWindowSize.y
        sprintf([ebx+ID_MAX_ROW].S_TOBJ.to_data, "%d", eax)

        .if CFGetSection(".consolesize")

            .for esi=eax, edi=0: edi < 8, INIGetEntryID(esi, edi): edi++

                lea ecx,[edi+1]
                shl ecx,4
                strcpy([ebx+ecx].S_TOBJ.to_data, eax)
            .endf
            .if INIGetEntryID(esi, 8)

                .if byte ptr [eax] == '1'

                    or [ebx+ID_DEFAULT].S_TOBJ.to_flag,_O_FLAGB
                .endif
            .endif
        .endif

        dlinit(ebx)
        dlshow(ebx)

        movzx esi,[ebx].S_DOBJ.dl_rect.rc_x
        movzx edi,[ebx].S_DOBJ.dl_rect.rc_y
        add esi,11
        add edi,9
        mov edx,GetLargestConsoleWindowSize(hStdOutput)
        shr edx,16
        movzx eax,ax
        mov maxrow,edx
        mov maxcol,eax
        mov ecx,rc.top
        mov eax,rc.left
        scputf(esi, edi, 0, 0, "%d\n%d", eax, ecx)
        movzx eax,ci.dwSize.x
        movzx ecx,ci.dwSize.y
        dec ecx
        mov _scrcol,eax
        mov _scrrow,ecx
        inc ecx
        add edi,2
        scputf(esi, edi, 0, 0, "%d\n%d", eax, ecx)
        add esi,24
        scputf(esi, edi, 0, 0, "%d\n%d", maxcol, maxrow)

        .while rsevent(IDD_ConsoleSize, ebx)

            xor esi,esi
            .if atol([ebx+ID_MIN_ROW].S_TOBJ.to_data) < DZMINROWS

                sprintf([ebx+ID_MIN_ROW].S_TOBJ.to_data, "%d", DZMINROWS)
                inc esi

            .elseif eax > DZMAXROWS

                sprintf([ebx+ID_MIN_ROW].S_TOBJ.to_data, "%d", DZMAXROWS)
                inc esi
            .endif

            .if atol([ebx+ID_MIN_COL].S_TOBJ.to_data) < DZMINCOLS

                sprintf([ebx+ID_MIN_COL].S_TOBJ.to_data, "%d", DZMINCOLS)
                inc esi

            .elseif eax > DZMAXCOLS

                sprintf([ebx+ID_MIN_COL].S_TOBJ.to_data, "%d", DZMAXCOLS)
                inc esi
            .endif

            .if atol([ebx+ID_MAX_ROW].S_TOBJ.to_data) < DZMINROWS

                sprintf([ebx+ID_MAX_ROW].S_TOBJ.to_data, "%d", DZMINROWS)
                inc esi

            .elseif eax > DZMAXROWS

                sprintf([ebx+ID_MAX_ROW].S_TOBJ.to_data, "%d", DZMAXROWS)
                inc esi
            .endif

            .if atol([ebx+ID_MAX_COL].S_TOBJ.to_data) < DZMINCOLS

                sprintf([ebx+ID_MAX_COL].S_TOBJ.to_data, "%d", DZMINCOLS)
                inc esi

            .elseif eax > DZMAXCOLS

                sprintf([ebx+ID_MAX_COL].S_TOBJ.to_data, "%d", DZMAXCOLS)
                inc esi
            .endif


            .if !esi

                .if CFAddSection(".consolesize")

                    .for esi=eax, edi=0: edi < 8: edi++

                        lea ecx,[edi+1]
                        shl ecx,4
                        INIAddEntryX(esi, "%d=%s", edi, [ebx+ecx].S_TOBJ.to_data)
                    .endf
                    xor eax,eax
                    .if [ebx+ID_DEFAULT].S_TOBJ.to_flag & _O_FLAGB

                        inc eax
                    .endif
                    INIAddEntryX(esi, "8=%d", eax)
                .endif
                mov eax,1
                .break

            .endif
            dlinit(ebx)
        .endw
        dlclose(ebx)
        mov eax,edx
    .until  1
    ret

cmscreensize endp

    END

