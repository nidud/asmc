include doszip.inc
include string.inc
include stdlib.inc
include consx.inc

.code

tihandler PROC

	mov	edx,tinfo

	OPTION	SWITCH:PASCAL

	.switch eax

	  .case KEY_F1:		mov eax,HELPID_05 : view_readme()
	  .case KEY_F2:		tiflush(edx)
	  .case KEY_F3:		tisearch(edx)
	  .case KEY_F4:		tireplace(edx)
	  .case KEY_F5:		tnewfile()
	  .case KEY_F6:		tnextfile()
	  .case KEY_F7:		twindowsize()
	  .case KEY_F8:		tsavefiles()
	  .case KEY_F9:		tloadfiles()
	  .case KEY_F11:	titogglemenus(edx)

	  .case KEY_ESC:	tihideall(edx) : jmp return
	  .case KEY_CTRLF2:	tisaveas(edx)
	  .case KEY_CTRLF9:	tioption(edx)
	  .case KEY_CTRLA:	tiselectall(edx)
	  .case KEY_CTRLB:	consuser()
	  .case KEY_CTRLC:	titransfer()
	  .case KEY_CTRLF:	mov eax,_T_OPTIMALFILL : jmp toggle
	  .case KEY_CTRLG:	tilseek(edx)
	  .case KEY_CTRLI:	mov eax,_T_USEINDENT : jmp toggle
	  .case KEY_CTRLL:	ticontsearch(edx)
	  .case KEY_CTRLM:	titogglemenus(edx)
	  .case KEY_CTRLO:	consuser()
	  .case KEY_CTRLR:	tireload(edx)
	  .case KEY_CTRLS:	mov eax,_T_USESTYLE : jmp toggle
	  .case KEY_CTRLT:	mov eax,_T_SHOWTABS : jmp toggle
	  .case KEY_CTRLX:	tclosefile() : jmp toend

	  .case KEY_SHIFTF1:	TIShiftFx(1)
	  .case KEY_SHIFTF2:	TIShiftFx(2)
	  .case KEY_SHIFTF3:	TIShiftFx(3)
	  .case KEY_SHIFTF4:	TIShiftFx(4)
	  .case KEY_SHIFTF5:	TIShiftFx(5)
	  .case KEY_SHIFTF6:	TIShiftFx(6)
	  .case KEY_SHIFTF7:	TIShiftFx(7)
	  .case KEY_SHIFTF8:	TIShiftFx(8)
	  .case KEY_SHIFTF9:	TIShiftFx(9)

	  .case KEY_ALTF1
		push	esi
		mov	esi,edx
		.if	topen(strfcat( __srcfile, _pgmpath, addr DZ_INIFILE), 0)

			mov tinfo,titogglefile(esi, eax)
		.endif
		pop	esi

	  .case KEY_ALTF2:	TIAltFx(2)
	  .case KEY_ALTF3:	TIAltFx(3)
	  .case KEY_ALTF4:	TIAltFx(4)
	  .case KEY_ALTF5:	TIAltFx(5)
	  .case KEY_ALTF6:	TIAltFx(6)
	  .case KEY_ALTF7:	tipreviouserror()
	  .case KEY_ALTF8:	tinexterror()
	  .case KEY_ALTF9:	TIAltFx(9)
	  .case KEY_ALT0:	twindows()
	  .case KEY_ALTL:	tilseek(edx)
	  .case KEY_ALTS:	tisearchxy(edx)
	  .case KEY_ALTX:	tcloseall() : jmp return
	  .default
		mov	eax,_TI_NOTEVENT
		jmp	toend
	.endsw
	mov	eax,_TI_CONTINUE
toend:
	ret
toggle:
	xor	[edx].S_TINFO.ti_flag,eax
	tiputs( edx )
	xor	eax,eax
	jmp	toend
return:
	mov	eax,_TI_RETEVENT
	jmp	toend

tihandler ENDP

	END
