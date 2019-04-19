; MENUS.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include io.inc
include cfini.inc
include time.inc
include consx.inc
include stdlib.inc
include string.inc

EXTERN  CRLF$:byte
tupdtime proto

    .data

ID_MPANELA  equ 0
ID_MFILE    equ 1
ID_MEDIT    equ 2
ID_MSETUP   equ 3
ID_MTOOLS   equ 4
ID_MHELP    equ 5
ID_MPANELB  equ 6

CPW_PANELA  db 'Panel-&A',0
CPW_FILE    db '&File',0
CPW_EDIT    db '&'
cp_edit     db 'Edit',0
CPW_SETUP   db '&Setup',0
CPW_TOOLS   db '&'
cp_tools    db 'Tools',0
CPW_HELP    db '&'
cp_help     db 'Help',0
CPW_PANELB  db 'Panel-&B',0

cp_long     db 'Long/short filename',0
cp_detail   db 'Show detail',0
cp_wideview db 'Wide view',0
cp_hidden   db 'Show hidden files',0
cp_mini     db 'Ministatus',0
cp_volinfo  db 'Volume information',0
cp_sort     db 'Sort current panel by Name, '
            db 'Type, Time, Size, or Unsorted',0
cp_toggle   db 'Toggle panel - on/off',0
cp_pfilter  db 'Panel filter',0
cp_subinfo  db 'Directory information',0
cp_update   db 'Re-read',0
cp_chdrv    db 'Select drive',0
cp_rename   db 'Rename file or directory',0
cp_view     db 'View File or Directory information',0
cp_copy     db 'Copy',0
cp_move     db 'Move',0
cp_delete   db 'Delete',0
cp_blkprop  db 'Edit file property',0
cp_compress db 'Compress',0
cp_decompress db 'Decompress',0
cp_history  db 'List of the last 16 DOS commands',0
cp_memory   db 'Memory Information',0
cp_search   db 'Search',0
cp_exit     db 'Exit program',0
cp_select   db 'Select files',0
cp_deselect db 'Deselect files',0
cp_invert   db 'Invert selection',0
cp_mklist   db 'Create List File from selection',0
cp_environ  db 'Edit Environment',0
cp_qsearch  db 'Quick Search',0
cp_compare  db 'Compare directories',0
cp_toggleml db 'Toggle Menus line - on/off',0
cp_togglecl db 'Toggle Command line - on/off',0
cp_togglesl db 'Toggle Status line - on/off',0
cp_toggleon db 'Toggle panels - on/off',0
cp_togglehz db 'Toggle panels - horizontal/vertical',0
cp_togglesz db 'Toggle Panels - size',0
cp_egaline  db 'Toggle 25-50 lines',0
cp_consolesize db 'Set console size',0
cp_swappanels db 'Swap panels',0
cp_confirm  db 'Confirmations options',0
cp_screen   db 'Screen options',0
cp_panel    db 'Panel options',0
cp_config   db 'Configuration',0
cp_about    db 'About Doszip',0
cp_bhistory db 'Browse history',0

        align 4

menus_idd       dd 0
menus_obj       dd 0
menus_xtitle    dd 11,8,8,9,9,8,11
menus_xpos      dd 0,10,17,24,32,40,47
menus_iddtable  dd offset IDD_DZMenuPanel[4]
                dd offset IDD_DZMenuFile [4]
                dd offset IDD_DZMenuEdit [4]
                dd offset IDD_DZMenuSetup[4]
                dd offset IDD_DZMenuTools[4]
                dd offset IDD_DZMenuHelp [4]
                dd offset IDD_DZMenuPanel[4]

MENUS_PANELA label dword
        dd cp_long, cmalong
        dd cp_detail,   cmadetail
        dd cp_wideview, cmawideview
        dd cp_hidden,   cmahidden
        dd cp_mini, cmamini
        dd cp_volinfo,  cmavolinfo
        dd cp_sort, cmaname
        dd cp_sort, cmatype
        dd cp_sort, cmadate
        dd cp_sort, cmasize
        dd cp_sort, cmanosort
        dd cp_toggle,   cmatoggle
        dd cp_pfilter,  cmafilter
        dd cp_subinfo,  cmasubinfo
        dd cp_bhistory, cmahistory
        dd cp_update,   cmaupdate
        dd cp_chdrv,    cmachdrv

MENUS_FILE label dword
        dd cp_rename,   cmrename
        dd cp_view, cmview
        dd cp_edit, cmedit
        dd cp_copy, cmcopy
        dd cp_move, cmmove
        dd cp_mkdir,    cmmkdir
        dd cp_delete,   cmdelete
        dd cp_blkprop,  cmattrib
        dd cp_compress, cmcompress
        dd cp_decompress, cmdecompress
        dd cp_mkzip,    cmmkzip
        dd cp_search,   cmsearch
        dd cp_history,  cmhistory
        dd cp_memory,   cmsysteminfo
        dd cp_exit, cmexit

MENUS_EDIT label dword
        dd cp_select,   cmselect
        dd cp_deselect, cmdeselect
        dd cp_invert,   cminvert
        dd cp_compare,  cmcompare
        dd cp_compare,  cmcompsub
        dd cp_mklist,   cmmklist
        dd cp_environ,  cmenviron
        dd cp_qsearch,  cmquicksearch
        dd cp_edit, cmtmodal

MENUS_SETUP label dword
        dd cp_toggleml, cmxormenubar
        dd cp_toggleon, cmtoggleon
        dd cp_togglesz, cmtogglesz
        dd cp_togglehz, cmtogglehz
        dd cp_togglecl, cmxorcmdline
        dd cp_togglesl, cmxorkeybar
        dd cp_egaline,  cmegaline
        dd cp_consolesize, cmscreensize
        dd cp_swappanels, cmswap
        dd cp_confirm,  cmconfirm
        dd cp_panel,    cmpanel
        dd cp_config,   cmcompression
        dd cp_config,   toption
        dd cp_screen,   cmscreen
        dd cp_config,   cmsystem
        dd cp_config,   cmoptions

MENUS_HELP label dword
        dd cp_help, cmhelp
        dd cp_about,    cmabout

MENUS_PANELB label dword
        dd cp_long, cmblong
        dd cp_detail,   cmbdetail
        dd cp_wideview, cmbwideview
        dd cp_hidden,   cmbhidden
        dd cp_mini, cmbmini
        dd cp_volinfo,  cmbvolinfo
        dd cp_sort, cmbname
        dd cp_sort, cmbtype
        dd cp_sort, cmbdate
        dd cp_sort, cmbsize
        dd cp_sort, cmbnosort
        dd cp_toggle,   cmbtoggle
        dd cp_pfilter,  cmbfilter
        dd cp_subinfo,  cmbsubinfo
        dd cp_bhistory, cmbhistory
        dd cp_update,   cmbupdate
        dd cp_chdrv,    cmbchdrv

menus_oid label dword
        dd MENUS_PANELA
        dd MENUS_FILE
        dd MENUS_EDIT
        dd MENUS_SETUP
        dd 0
        dd MENUS_HELP
        dd MENUS_PANELB

menus_shortkeys label dword
        dd 1E00h    ; A Panel-A
        dd 2100h    ; F File
        dd 1200h    ; E Edit
        dd 1F00h    ; S Setup
        dd 1400h    ; T Tools
        dd 2300h    ; H Help
        dd 3000h    ; B Panel-B

menus_TOBJ label S_TOBJ
        S_TOBJ <0006h,0,1Eh,< 0,0,11,1>,CPW_PANELA,0>
        S_TOBJ <0006h,0,21h,<10,0,10,1>,CPW_FILE,  0>
        S_TOBJ <0006h,0,12h,<17,0, 8,1>,CPW_EDIT,  0>
        S_TOBJ <0006h,0,1Fh,<24,0,10,1>,CPW_SETUP, 0>
        S_TOBJ <0006h,0,14h,<32,0, 9,1>,CPW_TOOLS, 0>
        S_TOBJ <0006h,0,23h,<40,0, 8,1>,CPW_HELP,  0>
        S_TOBJ <0006h,0,30h,<47,0,11,1>,CPW_PANELB,0>

F0      equ 0F0h
A0      equ 036h
A1      equ 03Fh

Commandline_RC  dw 0200h,0010h,0000h
                db 0
Commandline_Y   db 23
Commandline_C0  db 80,1,F0
Commandline_C1  db 80,07h,F0
Commandline_C2  db 80,' '
IDD_Commandline dd Commandline_RC

Statusline_RC   dw 0200h,0450h,0000h
                db 0
Statusline_Y    db 24
Statusline_C0   db 80,1
                db A0,A1,A1,F0,7,A0,A1,A1,F0,6,A0,A1,A1,F0,7,A0,A1,A1,F0,7,A0
                db A1,A1,F0,7,A0,A1,A1,F0,7,A0,A1,A1,F0,8,A0,A1,A1,F0,6,A0,A1
                db A1,A1,F0
Statusline_C1   db 5,A0
                db ' F1 Help  F2 Ren  F3 View  F4 Edit  F5 Copy  F6 Move '
                db ' F7 Mkdir  F8 Del  F10 Exit',F0
Statusline_C2   db 0,' '
IDD_Statusline  dd Statusline_RC

Menusline_RC    dw 0200h,0050h,0000h,0000h
Menusline_C0    db 80,1
                db F0,8,A0,A1,A0,A0,A0,A1,F0,6,A0,A1,F0,6,A0,A1,F0,7,A0
                db A1,F0,7,A0,A1,F0,12,A0,A1,F0
Menusline_C1    db 4,A0,F0,20,38h
                db '  Panel-A   File   Edit   Setup   Tools   Help   Panel-B'
                db F0,24,' ',F0
Menusline_C2    db 0,' '
IDD_Menusline   dd Menusline_RC
DLG_Menusline   dd 0        ; DOBJ
DLG_Statusline  dd 0
DLG_Commandline dd 0

dlgcursor       S_CURSOR <0,0,0,0>
dlgflags        db 5 dup(0)

    .code

apiidle proc

    .if cflag & _C_MENUSLINE

        tupdtime()
    .endif
    xor eax,eax
    ret

apiidle endp

apiopen proc

    mov Statusline_C1,5
    mov Menusline_C1,4
    ConsolePush()
    movzx eax,console_cu.y
    mov com_info.ti_ypos,eax
    mov eax,_scrrow
    mov Statusline_Y,al
    .if cflag & _C_STATUSLINE

        dec al
    .endif
    mov edx,com_info.ti_ypos
    .if dl < al

        mov al,dl
    .endif
    mov Commandline_Y,al
    mov byte ptr com_info.ti_ypos,al
    oswrite(1, &CRLF$, 2)
    mov eax,_scrcol
    mov Commandline_C0,al
    mov Commandline_C1,al
    mov Commandline_C2,al
    mov Statusline_C0,al
    mov Menusline_C0,al
    .if al < 80

        mov al,80
    .endif
    sub al,80
    add Statusline_C1,al
    mov Statusline_C2,al
    add Menusline_C1,al
    mov Menusline_C2,al
    rsopen(IDD_Commandline)
    mov DLG_Commandline,eax
    rsopen(IDD_Menusline)
    mov DLG_Menusline,eax
    .if cflag & _C_MENUSLINE

        dlshow(eax)
        tupdtime()
    .endif
    rsopen(IDD_Statusline)
    mov DLG_Statusline,eax
    .if cflag & _C_STATUSLINE

        dlshow(eax)
    .endif
    comshow()
    ret

apiopen endp

apiclose proc

    dlclose(DLG_Menusline)
    dlclose(DLG_Commandline)
    dlclose(DLG_Statusline)
    ret

apiclose endp

apiupdate proc

    comhide()
    doszip_hide()
    doszip_show()
    ret

apiupdate endp

apimode proc

    mov eax,24
    .if cflag & _C_EGALINE

        mov eax,49
    .endif
    conssetl(eax)

apimode endp

apiega  proc

    and cflag,not _C_EGALINE
    .if _scrrow != DZMINROWS-1 || _scrcol != DZMINCOLS

        or cflag,_C_EGALINE
    .endif
    ret

apiega  endp

open_idd proc uses ebx id, lpMTitle

    mov eax,id
    .if rsopen(menus_iddtable[eax*4])

        push eax
        .if cflag & _C_MENUSLINE

            mov eax,id
            mov ecx,menus_xtitle[eax*4]
            mov edx,menus_xpos[eax*4]
            scgetws(edx, 0, ecx)
            mov ebx,lpMTitle
            mov [ebx],eax
            movzx eax,at_foreground[F_MenusKey]
            scputa(edx, 0, ecx, eax)
        .endif
        pop eax
    .endif
    ret

open_idd endp

close_idd proc uses eax edx id, wpMenusTitle

    .if cflag & _C_MENUSLINE

        mov eax,id
        mov edx,menus_xtitle[eax*4]
        mov eax,menus_xpos[eax*4]
        scputws(eax,0,edx,wpMenusTitle)
    .endif
    ret

close_idd endp

modal_idd proc uses esi edi ebx index, stInfo, dialog, wpMenusTitle

local   stBuffer[256]:word

    lea esi,stBuffer
    mov edi,dialog
    wcpushst(esi, stInfo)
    dlinit(edi)
    dlshow(edi)
    msloop()
    dlevent(edi)
    mov ebx,eax
    movzx eax,[edi].S_DOBJ.dl_index
    shl eax,4
    add eax,[edi].S_DOBJ.dl_object
    movzx edi,[eax].S_TOBJ.to_flag
    and edi,_O_STATE or _O_FLAGB
    wcpopst(esi)
    close_idd(index, wpMenusTitle)
    mov edx,edi
    mov eax,ebx
    ret

modal_idd endp

readtools proc private uses esi edi ebx section, dialog, index, lsize

  local handle, p, buffer[512]:sbyte

    mov eax,dialog
    mov ebx,[eax].S_DOBJ.dl_object
    mov edi,index

    .if CFGetSection(section)

        mov handle,eax

        .while INIGetEntryID(handle, edi)

            lea esi,buffer
            strcpy(esi, eax)

            mov esi,strstart(esi)
            mov p,esi
            mov ecx,36

            .repeat

                lodsb
                .switch al

                  .case ','

                    mov byte ptr [esi-1],0      ; terminate text line
                    mov esi,strstart(esi)   ; start of command tail
                    mov ecx,lsize
                    mov edx,[ebx].S_TOBJ.to_data
                    xchg edi,edx
                    xor eax,eax

                    .while  ecx

                        lodsb
                        .break .if !al
                        .break .if al == ']'

                        .if al == '['

                            mov ah,al
                            .continue
                        .endif
                        stosb
                        dec ecx
                    .endw

                    mov ecx,1
                    mov al,0
                    stosb
                    mov edi,edx
                    .endc .if !ah

                    or [ebx].S_TOBJ.to_flag,_O_FLAGB
                    .endc

                  .case '<'
                    mov ecx,1
                    .endc

                  .case 0
                   error:
                    CFError(section, p)
                    xor edi,edi
                    .break(1)
                .endsw

            .untilcxz

            mov esi,p
            mov eax,76
            mul edi
            add eax,78
            mov edx,dialog
            mov edx,[edx].S_DOBJ.dl_wp
            add edx,eax

            .if byte ptr [esi] == '<'

                wcputw(edx, 38, 00C4h)
                and [ebx].S_TOBJ.to_flag,not _O_FLAGB

            .else

                add edx,4
                wcputs(edx, 0, 32, esi)
                mov eax,not _O_STATE
                and [ebx].S_TOBJ.to_flag,ax

                .if strchr(esi, '&')

                    mov al,[eax+1]
                    mov [ebx].S_TOBJ.to_ascii,al
                .endif
            .endif

            add ebx,16
            inc edi
            .break .if edi >= 20
        .endw
    .endif

    mov eax,edi
    ret

readtools endp

tools_idd proc uses esi edi ebx lsize, p, section

local mtitle, tbuf[256]:byte

    .while 1

        xor esi,esi
        .break .if !open_idd(ID_MTOOLS, &mtitle)

        mov ebx,eax
        .if !readtools(section, eax, esi, lsize)

            close_idd(ID_MTOOLS, mtitle)
            dlclose(ebx)
            .break
        .endif

        mov [ebx].S_DOBJ.dl_count,al
        add al,2
        mov [ebx].S_DOBJ.dl_rect.S_RECT.rc_row,al
        mov ah,al
        mov al,[ebx].S_DOBJ.dl_rect.S_RECT.rc_col
        movzx edx,al
        shl eax,16

        rcframe(eax, [ebx].S_DOBJ.dl_wp, edx, 0)
        strnzcpy(&tbuf, section, 16)
        modal_idd(ID_MTOOLS, eax, ebx, mtitle)

        mov esi,eax ; dlevent() | key (Left/Right)
        mov edi,edx ; flag _O_STATE or _O_FLAGB
        movzx edx,[ebx].S_DOBJ.dl_count

        .if eax && edx >= eax

            shl eax,4
            lea edx,[ebx+eax]
            strnzcpy(&tbuf, [edx].S_TOBJ.to_data, lsize)
        .endif

        movzx eax,[ebx].S_DOBJ.dl_count
        dlclose(ebx)

        .if esi && edx >= esi

            lea eax,tbuf
            mov edx,p
            .if edi == _O_FLAGB

                mov section,eax
                .continue
            .endif
            .if edx

                strcpy(edx, eax)
                msloop()
                .break
            .endif

            command(eax)
            mov esi,eax
        .endif

        .if mousep()

            mov esi,MOUSECMD
        .endif
        .break
    .endw
    mov eax,esi
    ret

tools_idd endp

cmtool proc private

  local tool[128]:byte

    .if CFGetSectionID(&cp_tools, eax)

        mov edx,eax
        mov eax,[eax]

        .if ax != '><'

            .if strchr(edx, ',')

                inc eax
                strstart(eax)
                mov edx,eax
                strnzcpy(&tool, edx, 128-1)

                .if tool != '['

                    command(eax)
                .else

                    lea ecx,[eax+1]
                    .if strchr(strcpy(eax, ecx), ']')

                        mov byte ptr [eax],0
                        tools_idd(128, 0, &tool)
                    .endif
                .endif
            .endif
        .endif
    .endif
    ret

cmtool  endp

CMTOOLP macro q
cmtool&q proc
    mov eax,q-1
    jmp cmtool
cmtool&q endp
    endm

CMTOOLP 1
CMTOOLP 2
CMTOOLP 3
CMTOOLP 4
CMTOOLP 5
CMTOOLP 6
CMTOOLP 7
CMTOOLP 8
CMTOOLP 9

menus_modalidd proc uses esi edi ebx id

  local object, mtitle, dialog

    xor esi,esi

    .if id == ID_MTOOLS

        tools_idd(128, 0, &cp_tools)
        mov esi,eax
    .else

        mov eax,IDD_DZMenuPanel
        mov byte ptr [eax+6],0
        .if id == ID_MPANELB

            mov byte ptr [eax+6],42
        .endif

        .if open_idd(id, &mtitle)

            mov dialog,eax
            mov ebx,eax
            add eax,16
            mov object,eax
            movzx ecx,[ebx].S_DOBJ.dl_count
            add ebx,S_TOBJ.to_data[16]
            mov edx,id
            mov edx,menus_oid[edx*4]

            .while ecx

                mov eax,[edx]
                mov [ebx],eax
                add ebx,sizeof(S_TOBJ)
                add edx,8
                dec ecx
            .endw

            mov eax,id
            xor edx,edx

            .if !eax

                mov edx,config.c_apath.ws_flag
            .elseif eax == ID_MPANELB

                mov edx,config.c_bpath.ws_flag
            .endif

            .if edx

                mov ebx,object
                mov eax,_O_FLAGB
                mov ecx,_W_LONGNAME

                push 0
                push _W_DRVINFO
                push _W_MINISTATUS
                push _W_HIDDEN
                push _W_WIDEVIEW
                push _W_DETAIL

                .while ecx
                    .if edx & ecx

                        or [ebx].S_TOBJ.to_flag,ax
                    .endif
                    add ebx,sizeof(S_TOBJ)
                    pop ecx
                .endw

                mov eax,_O_RADIO
                and edx,_W_SORTSIZE or _W_NOSORT
                .switch edx
                  .case _W_SORTNAME
                    or [ebx+0*16].S_TOBJ.to_flag,ax
                    .endc
                  .case _W_SORTTYPE
                    or [ebx+1*16].S_TOBJ.to_flag,ax
                    .endc
                  .case _W_SORTDATE
                    or [ebx+2*16].S_TOBJ.to_flag,ax
                    .endc
                  .case _W_SORTSIZE
                    or [ebx+3*16].S_TOBJ.to_flag,ax
                    .endc
                  .default
                    or [ebx+4*16].S_TOBJ.to_flag,ax
                .endsw
            .endif

            mov eax,id
            shl eax,4
            modal_idd(id, menus_TOBJ[eax].S_TOBJ.to_data, dialog, mtitle)
            mov esi,eax
            mov edi,edx
            mov eax,dialog
            movzx eax,[eax].S_DOBJ.dl_count

            dlclose(dialog) ; -- return AX in DX

            .if esi && edx >= esi

                mov edx,id
                mov menus_idd,edx
                mov eax,esi
                dec eax
                mov menus_obj,eax
                .if !(edi & _O_STATE)

                    mov  edx,menus_oid[edx*4]
                    call [edx+eax*8].S_GLCMD.gl_proc
                .endif
            .endif

            .if mousep()

                mov esi,MOUSECMD
            .endif
        .endif
    .endif
    mov eax,esi
    ret

menus_modalidd endp

menus_event proc uses esi edi ebx id, key

    mov edi,key
    mov esi,1

    .while  1

        .switch edi

          .case MOUSECMD

            xor edi,edi
            xor esi,esi
            .endc

          .case KEY_LEFT
          .case KEY_RIGHT

            mov eax,edi
            .break  .if !esi

            mov eax,id
            .if edi == KEY_RIGHT

                inc eax
                .if eax > ID_MPANELB

                    xor eax,eax
                .endif
            .else
                dec eax
                .if eax == -1

                    mov eax,ID_MPANELB
                .endif
            .endif

            mov id,eax
            menus_modalidd(eax)
            mov edi,eax
            .endc

          .case KEY_ESC
            mov eax,edi
            .break  .if !esi
            xor eax,eax
            .break

          .default
            .if esi

                msloop()
                .break
            .endif
            .endc .if !edi

            mov ecx,7
            xor ebx,ebx
            .repeat
                .if edi == menus_shortkeys[ebx]

                    shr ebx,2
                    mov id,ebx
                    menus_modalidd(ebx)
                    mov edi,eax
                    mov esi,1
                    .break
                .endif
                add ebx,4
            .untilcxz
            mov eax,edi
            .break .if !esi
        .endsw

        .if !esi


            mov edi,tgetevent()
            .if eax == MOUSECMD

                xor edi,edi
            .endif
        .endif

        .if cflag & _C_MENUSLINE && !keybmouse_y && !edi

            .if mousep()

                mov eax,keybmouse_x
                mov edx,eax
                mov ecx,ID_MPANELB

                .if eax >= 57

                    mov eax,MOUSECMD
                    .break
                .endif

                .repeat
                    mov ebx,ecx
                    dec ecx
                    shl ebx,4
                    add ebx,offset menus_TOBJ
                .until  al >= [ebx+4]

                mov ah,[ebx].S_TOBJ.to_ascii
                mov al,0
                mov edi,eax
                inc ecx
                mov id,ecx

                .continue
            .endif
        .endif

        mov eax,MOUSECMD
        .break .if !edi
    .endw
    ret

menus_event endp

menus_getevent proc
    menus_event(0, MOUSECMD)
    ret
menus_getevent endp

    END
