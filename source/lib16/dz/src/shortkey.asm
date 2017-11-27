; SHORTKEY.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include conio.inc
include keyb.inc

PUBLIC	global_key

_DATA	segment

global_key label WORD
ifdef DEBUG
	GCMD	5400h,		cmdebug ; Shift-F1
endif
	GCMD	KEY_ESC,	cmclrcmdl
	GCMD	KEY_F1,		cmhelp
	GCMD	KEY_F2,		cmrename
	GCMD	KEY_F3,		cmview
	GCMD	KEY_F4,		cmedit
	GCMD	KEY_F5,		cmcopy
	GCMD	KEY_F6,		cmmove
	GCMD	KEY_F7,		cmmkdir
	GCMD	KEY_F8,		cmdelete
ifdef __TE__
	GCMD	KEY_F9,		cmtmodal
else
	GCMD	KEY_F9,		cmlastmenu
endif
	GCMD	KEY_F10,	cmexit
	GCMD	KEY_F11,	cmtogglesz
	GCMD	KEY_F12,	cmtogglehz
	GCMD	KEY_SHIFTF2,	cmcopycell
	GCMD	KEY_SHIFTF3,	cmview
	GCMD	KEY_SHIFTF4,	cmedit
ifdef __ZIP__
	GCMD	KEY_SHIFTF7,	cmmkzip
endif
	GCMD	KEY_SHIFTF9,	cmsavesetup
	GCMD	KEY_SHIFTF10,	cmlastmenu
	GCMD	KEY_ALTC,	cmxorcmdline
	GCMD	KEY_ALTL,	cmmklist
	GCMD	KEY_ALTP,	cmloadpath
	GCMD	KEY_ALTX,	cmquit
ifdef __TE__
	GCMD	KEY_ALT0,	cmwindowlist
endif
	GCMD	KEY_ALT1,	cmtool1
	GCMD	KEY_ALT2,	cmtool2
	GCMD	KEY_ALT3,	cmtool3
	GCMD	KEY_ALT4,	cmtool4
	GCMD	KEY_ALT5,	cmtool5
	GCMD	KEY_ALT6,	cmtool6
	GCMD	KEY_ALT7,	cmtool7
	GCMD	KEY_ALT8,	cmtool8
	GCMD	KEY_ALT9,	cmtool9
	GCMD	KEY_ALTUP,	cmpsizeup
	GCMD	KEY_ALTDN,	cmpsizedn
	GCMD	KEY_ALTF1,	cmachdrv
	GCMD	KEY_ALTF2,	cmbchdrv
	GCMD	KEY_ALTF3,	cmview
	GCMD	KEY_ALTF4,	cmedit
	GCMD	KEY_ALTF5,	cmcompress
	GCMD	KEY_ALTF6,	cmdecompress
	GCMD	KEY_ALTF8,	cmhistory
	GCMD	KEY_ALTF9,	cmegaline
ifdef __FF__
	GCMD	KEY_ALTF7,	cmsearch
	GCMD	KEY_CTRLTAB,	cmsearch
endif
	GCMD	KEY_CTRL0,	cmpath0
	GCMD	KEY_CTRL1,	cmpath1
	GCMD	KEY_CTRL2,	cmpath2
	GCMD	KEY_CTRL3,	cmpath3
	GCMD	KEY_CTRL4,	cmpath4
	GCMD	KEY_CTRL5,	cmpath5
	GCMD	KEY_CTRL6,	cmpath6
	GCMD	KEY_CTRL7,	cmpath7
	GCMD	KEY_CTRL8,	cmpathatocmd
	GCMD	KEY_CTRL9,	cmpathbtocmd
	GCMD	KEY_CTRLF1,	cmatoggle
	GCMD	KEY_CTRLF2,	cmbtoggle
	GCMD	KEY_CTRLF3,	cmview
	GCMD	KEY_CTRLF4,	cmedit
	GCMD	KEY_CTRLF5,	cmcname
ifdef __TE__
	GCMD	KEY_CTRLF6,	teoption
else
	GCMD	KEY_CTRLF6,	notsup
endif
	GCMD	KEY_CTRLF7,	cmscreen
	GCMD	KEY_CTRLF8,	cmsystem
	GCMD	KEY_CTRLF9,	cmoptions
	GCMD	KEY_CTRLA,	cmattrib
	GCMD	KEY_CTRLB,	cmuserscreen
	GCMD	KEY_CTRLC,	cmcompare
	GCMD	KEY_CTRLD,	cmcdate
	GCMD	KEY_CTRLE,	cmctype
	GCMD	KEY_CTRLF,	cmconfirm
ifdef __CAL__
	GCMD	KEY_CTRLG,	cmcalendar
endif
	GCMD	KEY_CTRLH,	cmchidden
	GCMD	KEY_CTRLI,	cmsubinfo
	GCMD	KEY_CTRLJ,	cmcompression
	GCMD	KEY_CTRLK,	cmxorkeybar
	GCMD	KEY_CTRLL,	cmclong
	GCMD	KEY_CTRLM,	cmcmini
	GCMD	KEY_CTRLN,	cmcname
	GCMD	KEY_CTRLO,	cmtoggleon
	GCMD	KEY_CTRLP,	cmpanel
	GCMD	KEY_CTRLQ,	cmquicksearch
	GCMD	KEY_CTRLR,	cmcupdate
ifdef __FF__
	GCMD	KEY_CTRLS,	cmsearch
else
	GCMD	KEY_CTRLS,	cmxorkeybar
endif
	GCMD	KEY_CTRLT,	cmcdetail
	GCMD	KEY_CTRLU,	cmcnosort
	GCMD	KEY_CTRLV,	cmvolinfo
	GCMD	KEY_CTRLW,	cmswap
	GCMD	KEY_CTRLZ,	cmcsize
	GCMD	KEY_CTRLX,	cmxormenubar
	GCMD	KEY_CTRLUP,	cmdoskey_up
	GCMD	KEY_CTRLDN,	cmdoskey_dn
	GCMD	KEY_CTRLPGUP,	cmupdir
	GCMD	KEY_CTRLPGDN,	cmsubdir
	GCMD	KEY_CTRLENTER,	cmcfblktocmd
	GCMD	KEY_KPPLUS,	cmselect
	GCMD	KEY_KPMIN,	cmdeselect
	GCMD	KEY_KPSTAR,	cminvert
	GCMD	KEY_ALTW,	cmcwideview
	GCMD	KEY_ALTM,	cmmemory
	GCMD	KEY_CTRLHOME,	cmhomedir
	dw	0

_DATA	ENDS

	END
