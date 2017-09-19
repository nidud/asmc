; DZMODAL.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include string.inc
include io.inc
include alloc.inc

menus_getevent	proto
scroll_delay	proto

    .data

MSOBJ macro x,l,cmd
    S_RECT <x,24,l,1>
    dd cmd
    endm

MOBJ_Statusline label S_MSOBJ
    MSOBJ    1,7, cmhelp
    MSOBJ   10,6, cmrename
    MSOBJ   18,7, cmview
    MSOBJ   27,7, cmedit
    MSOBJ   36,7, cmcopy
    MSOBJ   45,7, cmmove
    MSOBJ   54,7, cmmkdir
    MSOBJ   64,7, cmdelete
    MSOBJ   72,7, cmexit

    .code

comaddstring proc string

    xor eax,eax
    mov edx,DLG_Commandline

    .if byte ptr [edx] & _D_ONSCR

	mov edx,string
	mov eax,com_info.ti_bp
	.if byte ptr [eax]

	    strtrim(com_info.ti_bp)
	    strcat(com_info.ti_bp, &cp_space)
	.endif
	strcat(strcat(com_info.ti_bp, edx), &cp_space)
	comevent(KEY_END)
    .endif
    ret

comaddstring endp

cmcfblktocmd proc

    .if panel_curobj(cpanel)

	comaddstring(eax)
    .endif
    ret
cmcfblktocmd endp

cmpathatocmd proc

    mov eax,panela
    mov eax,[eax].S_PANEL.pn_wsub
    mov eax,[eax].S_WSUB.ws_path
    comaddstring(eax)
    ret

cmpathatocmd endp

cmpathbtocmd proc

    mov eax,panelb ; @v3.35 - Ctrl-9
    mov eax,[eax].S_PANEL.pn_wsub
    mov eax,[eax].S_WSUB.ws_path
    comaddstring(eax)
    ret

cmpathbtocmd endp

statusline_xy proc uses esi x, y, q, mo

    mov ecx,q
    mov edx,y
    mov eax,cflag
    and eax,_C_STATUSLINE

    .ifnz
	xor eax,eax
	.if edx == _scrrow

	    mov esi,mo
	    .repeat
		mov [esi+1],dl
		.break .if rcxyrow([esi], x, edx)
		add esi,8
	    .untilcxz

	    .if eax

		mov eax,esi
	    .endif
	.endif
    .endif

    ret
statusline_xy endp

history_event_list  proto
DirectoryToCurrentPanel proto :dword

SetPathFromHistory proc private uses esi edi ebx panel

local	ll:S_LOBJ, rc

    mov ebx,IDD_DZHistory
    mov eax,[ebx+6]
    mov rc,eax

    mov eax,panel
    mov eax,[eax].S_PANEL.pn_dialog
    mov cx,[eax+4] ; .S_DOBJ.dl_rect
    add cl,3
    mov [ebx+6],cl

    mov eax,_scrrow
    mov cl,al
    sub al,ch

    .if al >= [ebx+6].S_RECT.rc_row
	mov al,ch
	add al,2
    .else
	mov al,cl
	sub al,[ebx+6].S_RECT.rc_row
    .endif

    mov [ebx+7],al
    mov eax,history
    .if eax
	mov esi,eax
	.if rsopen(ebx)

	    mov ebx,eax

	    lea edi,ll
	    xor eax,eax
	    mov ecx,SIZE S_LOBJ
	    rep stosb

	    mov ll.ll_proc,history_event_list
	    mov ll.ll_dcount,16
	    mov ll.ll_list,alloca(MAXHISTORY*4)
	    mov ecx,MAXHISTORY
	    mov edi,eax
	    xor edx,edx

	    .repeat
		mov eax,[esi].S_DIRECTORY.path
		.break .if !eax
		stosd
		add esi,SIZE S_DIRECTORY
		inc edx
	    .untilcxz
	    mov ll.ll_count,edx

	    .if edx > 16
		mov edx,16
	    .endif
	    mov ll.ll_numcel,edx

	    lea edx,ll
	    mov tdllist,edx
	    mov eax,ebx

	    history_event_list()
	    dlevent(ebx)
	    dlclose(ebx)

	    mov eax,edx
	    .if eax
		dec eax
		add eax,ll.ll_index
		shl eax,4
		add eax,history
	    .endif
	.endif
    .endif

    mov ecx,rc
    mov ebx,IDD_DZHistory
    mov [ebx+6],cx

    .if eax
	mov ebx,eax
	panel_setactive(panel)
	DirectoryToCurrentPanel(ebx)
    .endif
    ret
SetPathFromHistory endp

cmahistory proc
    SetPathFromHistory(panela)
    ret
cmahistory endp

cmbhistory proc
    SetPathFromHistory(panelb)
    ret
cmbhistory endp

panel_scrolldn proc private panel

    mov eax,panel
    .if eax == cpanel
	.repeat
	    mov	 edx,panel
	    mov	 eax,[edx].S_PANEL.pn_cel_count
	    dec	 eax
	    .ifs eax > [edx].S_PANEL.pn_cel_index

		mov [edx].S_PANEL.pn_cel_index,eax
		pcell_update(edx)
		scroll_delay()
	    .else
		panel_event(panel, KEY_DOWN)
	    .endif
	    scroll_delay()
	    mousep()
	.until	eax != 1
	mov eax,1
    .else
	panel_setactive(eax)
	xor eax,eax
    .endif
    ret

panel_scrolldn endp

panel_scrollup proc private panel
    mov eax,panel
    .if eax == cpanel
	.repeat
	    xor eax,eax
	    mov edx,panel
	    .if [edx].S_PANEL.pn_cel_index != eax
		mov [edx].S_PANEL.pn_cel_index,eax
		pcell_update(edx)
		scroll_delay()
	    .else
		panel_event(panel, KEY_UP)
	    .endif
	    scroll_delay()
	    mousep()
	.until	eax != 1
	mov eax,1
    .else
	panel_setactive(eax)
	xor eax,eax
    .endif
    ret
panel_scrollup endp

mouseevent proc private uses esi edi ebx

    .while  mousep()

	mov edi,keybmouse_x
	mov esi,keybmouse_y

	.if cflag & _C_MENUSLINE && !esi

	    mov eax,_scrcol
	    sub eax,5
	    .if edi >= eax
		cmscreen()
		.break
	    .endif
	    sub eax,13
	    .if edi > eax
		cmcalendar()
	    .endif
	    .break
	.endif

	.if !(cflag & _C_MENUSLINE) && !esi && edi <= 56

	    cmxormenubar()
	    menus_getevent()
	    cmxormenubar()
	    .break
	.endif

	.if statusline_xy(edi, esi, 9, &MOBJ_Statusline)

	    push    eax
	    msloop()
	    pop eax
	    call    [eax].S_MSOBJ.mo_proc
	    .break
	.endif

	mov ebx,panela
	.if !panel_xycmd(ebx, edi, esi)

	    mov ebx,panelb
	    panel_xycmd(ebx, edi, esi)
	.endif
	.switch eax
	  .case 1
	  .case 2
	    panel_setactive(ebx)
	    pcell_setxy(ebx, edi, esi)
	    .endc
	  .case 3
	    panel_scrolldn(ebx)
	    .endc
	  .case 4
	    panel_scrollup(ebx)
	    .endc
	  .case 5
	    .if ebx == panela
		cmachdrv()
	    .else
		cmbchdrv()
	    .endif
	    .endc
	  .case 6
	    panel_xormini(ebx)
	    .endc
	  .case 7
	    SetPathFromHistory(ebx)
	    .endc
	  .case 8
	    panel_xorinfo(ebx)
	    .endc
	.endsw
	xor eax,eax
	.break
    .endw
    ret
mouseevent endp

doszip_modal proc uses esi

    xor eax,eax
    mov _diskflag,eax
    inc eax
    mov mainswitch,eax

    .while  mainswitch

	mov eax,_diskflag
	.if eax
	    ;
	    ; 1. mkdir(),rmdir(),osopen(),remove(),rename()
	    ; 2. setfattr(),setftime()
	    ; 3. process()
	    ;
	    .if eax == 3
		;
		; Update after extern command
		;
		SetConsoleTitle(DZTitle)

		.if cflag & _C_DELTEMP

		    removetemp(&cp_ziplst)
		    and cflag,not _C_DELTEMP
		.endif

		mov eax,cpanel
		mov esi,[eax].S_PANEL.pn_wsub

		.if filexist([esi].S_WSUB.ws_path) != 2

		    mov eax,[esi].S_WSUB.ws_path
		    mov byte ptr [eax],0
		    and [esi].S_WSUB.ws_flag,not _W_ROOTDIR
		.endif

		.if [esi].S_WSUB.ws_flag & _W_ARCHIVE

		    .if filexist([esi].S_WSUB.ws_file) != 1

			and [esi].S_WSUB.ws_flag,not _W_ARCHIVE
		    .endif
		.endif

		cominit(esi)
	    .endif
	    ;
	    ; Clear flag and update panels
	    ;
	    mov byte ptr _diskflag,0
	    reread_panels()
	.endif


	mov esi,menus_getevent()

	.if (eax == KEY_ENTER || eax == KEY_KPENTER) \
	    && com_base && cflag & _C_COMMANDLINE

	    .if doskeysave()

		.continue .if command(&com_base)
	    .endif

	    comevent(KEY_END)
	    .continue
	.endif

	.if com_base && cflag & _C_COMMANDLINE

	    .continue .if comevent(esi)
	.endif

	.if cpanel_state()

	    .continue .if panel_event(cpanel, esi)
	.endif

	.break .if !mainswitch

	option switch: pascal

	mov eax,esi
	.switch eax
  ifdef DEBUG
	  .case 0x5400:	    cmdebug()	; Shift-F1
  endif
	  .case MOUSECMD:   mouseevent()
	  .case KEY_TAB:    panel_toggleact()
	  .case KEY_ESC:    cmclrcmdl()
	  .case KEY_F1:	    cmhelp()
	  .case KEY_F2:	    cmrename()
	  .case KEY_F3:	    cmview()
	  .case KEY_F4:	    cmedit()
	  .case KEY_F5:	    cmcopy()
	  .case KEY_F6:	    cmmove()
	  .case KEY_F7:	    cmmkdir()
	  .case KEY_F8:	    cmdelete()
	  .case KEY_F9:	    cmtmodal()
	  .case KEY_F10:    cmexit()
	  .case KEY_F11:    cmtogglesz()
	  .case KEY_F12:    cmtogglehz()
	  .case KEY_SHIFTF2:	cmcopycell()
	  .case KEY_SHIFTF3:	cmview()
	  .case KEY_SHIFTF4:	cmedit()
	  .case KEY_SHIFTF5:	cmcompsub()
	  .case KEY_SHIFTF6:	cmenviron()
	  .case KEY_SHIFTF7:	cmmkzip()
	  .case KEY_SHIFTF9:	cmsavesetup()
	  .case KEY_SHIFTF10:	cmlastmenu()
	  .case KEY_ALTC:   cmxorcmdline()
	  .case KEY_ALTL:   cmmklist()
	  .case KEY_ALTM:   cmsysteminfo()
	  .case KEY_ALTP:   cmloadpath()
	  .case KEY_ALTW:   cmcwideview()
	  .case KEY_ALTX:   cmquit()
	  .case KEY_ALTZ:   cmscreensize()
	  .case KEY_ALT0:   cmwindowlist()
	  .case KEY_ALT1:   cmtool1()
	  .case KEY_ALT2:   cmtool2()
	  .case KEY_ALT3:   cmtool3()
	  .case KEY_ALT4:   cmtool4()
	  .case KEY_ALT5:   cmtool5()
	  .case KEY_ALT6:   cmtool6()
	  .case KEY_ALT7:   cmtool7()
	  .case KEY_ALT8:   cmtool8()
	  .case KEY_ALT9:   cmtool9()
	  .case KEY_ALTUP:  cmpsizeup()
	  .case KEY_ALTDN:  cmpsizedn()
	  .case KEY_ALTF1:  cmachdrv()
	  .case KEY_ALTF2:  cmbchdrv()
	  .case KEY_ALTF3:  cmview()
	  .case KEY_ALTF4:  cmedit()
	  .case KEY_ALTF5:  cmcompress()
	  .case KEY_ALTF6:  cmdecompress()
	  .case KEY_ALTF8:  cmhistory()
	  .case KEY_ALTF9:  cmegaline()
	  .case KEY_ALTF7:  cmsearch()
	  .case KEY_CTRLTAB:	cmsearch()
	  .case KEY_CTRL0:  cmpath0()
	  .case KEY_CTRL1:  cmpath1()
	  .case KEY_CTRL2:  cmpath2()
	  .case KEY_CTRL3:  cmpath3()
	  .case KEY_CTRL4:  cmpath4()
	  .case KEY_CTRL5:  cmpath5()
	  .case KEY_CTRL6:  cmpath6()
	  .case KEY_CTRL7:  cmpath7()
	  .case KEY_CTRL8:  cmpathatocmd()
	  .case KEY_CTRL9:  cmpathbtocmd()
	  .case KEY_CTRLF1: cmatoggle()
	  .case KEY_CTRLF2: cmbtoggle()
	  .case KEY_CTRLF3: cmview()
	  .case KEY_CTRLF4: cmedit()
	  .case KEY_CTRLF5: cmcname()
	  .case KEY_CTRLF6: toption()
	  .case KEY_CTRLF7: cmscreen()
	  .case KEY_CTRLF8: cmsystem()
	  .case KEY_CTRLF9: cmoptions()
	  .case KEY_CTRLA:  cmattrib()
	  .case KEY_CTRLB:  cmuserscreen()
	  .case KEY_CTRLC:  cmcompare()
	  .case KEY_CTRLD:  cmcdate()
	  .case KEY_CTRLE:  cmctype()
	  .case KEY_CTRLF:  cmconfirm()
	  .case KEY_CTRLG:  cmcalendar()
	  .case KEY_CTRLH:  cmchidden()
	  .case KEY_CTRLI:  cmsubinfo()
	  .case KEY_CTRLJ:  cmcompression()
	  .case KEY_CTRLK:  cmxorkeybar()
	  .case KEY_CTRLL:  cmclong()
	  .case KEY_CTRLM:  cmcmini()
	  .case KEY_CTRLN:  cmcname()
	  .case KEY_CTRLO:  cmtoggleon()
	  .case KEY_CTRLP:  cmpanel()
	  .case KEY_CTRLQ:  cmquicksearch()
	  .case KEY_CTRLR:  cmcupdate()
	  .case KEY_CTRLS:  cmsearch()
	  .case KEY_CTRLT:  cmcdetail()
	  .case KEY_CTRLU:  cmcnosort()
	  .case KEY_CTRLV:  cmvolinfo()
	  .case KEY_CTRLW:  cmswap()
	  .case KEY_CTRLX:  cmxormenubar()
	  .case KEY_CTRLZ:  cmcsize()
	  .case KEY_CTRLUP: cmdoskeyup()
	  .case KEY_CTRLDN: cmdoskeydown()
	  .case KEY_CTRLPGUP:	cmupdir()
	  .case KEY_CTRLPGDN:	cmsubdir()
	  .case KEY_CTRLENTER:	cmcfblktocmd()
	  .case KEY_KPPLUS: cmselect()
	  .case KEY_KPMIN:  cmdeselect()
	  .case KEY_KPSTAR: cminvert()
	  .case KEY_CTRLHOME:	cmhomedir()
	  .default
	    comevent(esi)
	.endsw
	msloop()
    .endw
    ret

doszip_modal endp

    END
