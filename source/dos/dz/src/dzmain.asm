; DZMAIN.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include stdio.inc
include string.inc
include ini.inc
include io.inc
include iost.inc
include dos.inc
include errno.inc
include conio.inc
include tinfo.inc
include mouse.inc
include progress.inc
include stdlib.inc

ifdef DEBUG
__FAKEDZ__	equ 1	; load a fake DZ.EXE for debug
endif

ifdef __FAKEDZ__
include dz.inc
else
__INI_LOAD__	equ 1	; DZ.INI: [Load]
endif

dzmodal		PROTO
history_read	PROTO
menusinit_OIDD	PROTO
MakeDirectory	PROTO _CType :DWORD

PUBLIC	copy_fast
PUBLIC	copy_filecount
PUBLIC	copy_subdcount
PUBLIC	mklist
PUBLIC	cp_style
PUBLIC	cp_default
PUBLIC	_stklen

extrn	com_info:S_TINFO
extrn	cp_dznotloaded:BYTE
extrn	cp_initype:BYTE
extrn	comargs:BYTE
extrn	CRLF$:BYTE

_DATA	segment
ifdef DEBUG
_stklen		dw 4000h
else
_stklen		dw 5000h
endif
envtemp		dd ?		; %TEMP%
envpath		dd ?		; %PATH%
comspec		dd ?		; %COMSPEC%
dzexe		dd ?		; dz.exe
dzerrno		dw ?		; - last return code
dzerflag	dw ?		; - error type
dzcount		dw ?		; - exec count - zero on first call
mainswitch	dw ?		; program switch
dzexitcode	dw ?		; return code (23 if exec)
numfblock	dw MAXFBLOCK	; number of file pointers allocated
argvfile	dw ?		; file/directory arg.
programpath	db MAXPATH dup(?); %doszip%
configpath	db MAXPATH dup(?); %doszip% | %dz% | /C<path>

;;;;;;;;;---------------------------
	; Configuration file: DZ.CFG
	;---------------------------
config	label	S_CONFIG
		dw	VERSION
cflag		dw	_C_DEFAULT
		dw	not _C_CONFMOVE
console		dw	311Eh
fsflag		dw	IO_SEARCHSUB
tvflag		dw	_TV_HEXOFFSET or _TV_USEMLINE
teflag		dw	_T_TEDEFAULT
tepages		dw	64
telsize		dw	1	; 0:128,1:256,2:512,...
tetabsize	dw	8
compressflag	dw	0
ffflag		dw	2
compresslevel	dw	9
		dw	0
cflaga		dw	_P_MINISTATUS or _P_VISIBLE
		dw	0,0
cflagb		dw	_P_PANELID or _P_MINISTATUS or _P_VISIBLE
		dw	0,0
path_a		S_PATH	<(_W_SORTTYPE or _W_HIDDEN),"*.*">
path_b		S_PATH	<_W_SORTTYPE or _W_HIDDEN,"*.*">
opfilter	S_FILT	<-1,0,0,0,0,'*.*'>
at_foreground	db 00h,0Fh,0Fh,07h,08h,00h,06h,07h
		db 08h,00h,0Ah,0Bh,00h,0Fh,0Fh,0Fh
at_background	db 00h,10h,70h,70h,40h,30h,30h,70h
		db 30h,30h,00h,00h,10h,10h,07h,07h
at_palett	db 0,1,2,3,4,5,20,7
		db 56,57,58,59,60,61,62,63
pending_file	db WMAXPATH dup(?)
mklist		S_MKLST <>

cpanel		dw offset spanela
panela		dw offset spanela
panelb		dw offset spanelb

DLG_Menusline	dd ?		; DOBJ
DLG_Statusline	dd ?
DLG_Commandline dd ?

copy_flag	db ?
copy_fast	db ?
copy_filecount	dw ?
copy_subdcount	dw ?

__srcfile	db 384 dup(?)
__srcpath	db WMAXPATH dup(?)
__outfile	db 384 dup(?)
__outpath	db WMAXPATH dup(?)
entryname	db 512 dup(?)

_bufin		label BYTE
;;;;;;;;;;;;;;;;;-----------------------------------------------
		; _bufin 4096 byte. Includes a default .INI file
		;-----------------------------------------------
	db 100 dup(?)

default_ini label BYTE
ifdef __DZ__
incbin <dz.bin>
else
incbin <dztiny.bin>
endif
	db 0

cp_ercfgpath	db 'Error open config path: %s',10,10,0
cp_dot		db '.',0
cp_dz		db 'DZ',0
cp_temp		db 'TEMP%',0
cp_path		db 'PATH',0
cp_ercomspec	db 'Error loading COMMAND.COM',10,0

cp_usage label BYTE
	db 'Command line switches',10
	db ' The following switches may be used in the command line:',10
	db 10
	db '  -T (tiny)  - read maximum 500 files in each panel',10
	db '  -L (large) - read maximum 5000 files in each panel',10
	db '	 default is 3000.',10
	db 10
	db '  -XP (WinXP)     - trigger a mode change on startup', 10
	db '  -C<config_path> - Read/Write setup from/to <config_path>',10
	db 10
	db '  DZ <filename> command starts DZ and forces it to show <filename>',10
	db 'contents if it is an archive or show folder contents if <filename>',10
	db 'is a folder.',10,0

cp_ini	db "dz.ini",0

if ($ - _bufin) le 1000h
	db 1000h - ($ - _bufin) dup('x')
endif

;;;;;;;;;;;;;;;;;-----------
		; Panel data
		;-----------

pcellwb		dw TIMAXSCRLINE-2 dup(07h)
pcell_a		dw _D_BACKG or _D_MYBUF
		db 1,1, 2,2,12,1
		dd DGROUP:pcellwb
		db 2,2,12,1
pcell_b		dw _D_BACKG or _D_MYBUF
		db 1,1, 2,2,12,1
		dd DGROUP:pcellwb
		db 2,2,12,1
prect_a		dw _D_CLEAR or _D_COLOR
		dw 0
		db 0,1,40,20
		dd 0,0
prect_b		dw _D_CLEAR or _D_COLOR
		db 0,0,40,1,40,20
		dd 0,0
wspanela	dw 0
wsmaxfba	dw MAXFBLOCK
		dd DGROUP:path_a.wp_flag
		dd DGROUP:path_a.wp_mask
		dd DGROUP:path_a.wp_file
		dd DGROUP:path_a.wp_arch
		dd DGROUP:path_a.wp_path
		dd 0
wspanelb	dw 0
wsmaxfbb	dw MAXFBLOCK
		dd DGROUP:path_b.wp_flag
		dd DGROUP:path_b.wp_mask
		dd DGROUP:path_b.wp_file
		dd DGROUP:path_b.wp_arch
		dd DGROUP:path_b.wp_path
		dd 0
spanela		label S_PANEL
		dw offset path_a
flaga		dw _P_PANELID or _P_MINISTATUS or _P_VISIBLE
		dw 0,0,0,0
		dd DGROUP:pcell_a
		dd DGROUP:prect_a
		dd DGROUP:wspanela
		dw 0
spanelb		label S_PANEL
		dw offset path_b
flagb		dw _P_MINISTATUS or _P_VISIBLE
		dw 0,0,0,0
		dd DGROUP:pcell_b
		dd DGROUP:prect_b
		dd DGROUP:wspanelb
		dw 0
cp_comspec	db 'Comspec',0
dz_comspec	db 'COMMAND.COM',0
		db 80 - ($ - offset dz_comspec) dup(?)
configfile	db MAXPATH dup(?)
cp_style	db "style",0
cp_default	db "default",0
cp_load		db 'Load',0

ifdef __FAKEDZ__

dz_exe	S_DZDS <?>
	ASSUME cs:_DATA
dz_exec PROC far
	mov	old_ds,ds
	mov	ax,cs
	mov	es,ax
	mov	ds,ax
	mov	old_si,si
	mov	old_di,di
	mov	di,offset dz_exe.dz_fcb_161
	mov	si,dz_exe.dz_exename
	mov	ax,2901h
	int	21h
	mov	bx,offset dz_exe.dz_envseg
	mov	dx,dz_exe.dz_exename
	mov	ax,4B00h
	int	21h
	mov	dx,cs
	mov	ds,dx
	jc	execute_error
	xor	ax,ax
    execute_error:
	mov	si,ax
	mov	ax,4D00h
	int	21h
	mov	dx,si
	mov	dz_exe.dz_eflag,dx
	mov	dz_exe.dz_errno,ax
	mov	si,old_si
	mov	di,old_di
	mov	ds,old_ds
	ret
dz_exec ENDP
	ASSUME cs:_DZIP
old_si	dw ?
old_di	dw ?
old_ds	dw ?
vector	label WORD
	dd 495A440Ah
	dd DGROUP:dz_exe.dz_exeproc
	db 128 dup(?)
cp_exec db 'Execute command:',10,'%s %s',0

endif ; __FAKEDZ__


ifdef DEBUG
_time_start	dd ?
	PUBLIC	_time_start
format_files	db '__srcfile = %-30s',10
		db '__srcpath = %-30s',10
		db '__outfile = %-30s',10
		db '__outpath = %-30s',10
		db 'entryname = %-30s',10
		db 'wsub.arch = %-30s',10
		db 0
_DATA	ENDS

_DZIP	segment

cmdebug PROC _CType PUBLIC
	mov	bx,cpanel
	mov	bx,WORD PTR [bx].S_PANEL.pn_wsub
	pushm	[bx].S_WSUB.ws_arch
	mov	ax,ds
	push	ax
	push	offset entryname
	push	ax
	push	offset __outpath
	push	ax
	push	offset __outfile
	push	ax
	push	offset __srcpath
	push	ax
	push	offset __srcfile
	invoke	ermsg,0,addr format_files
	add	sp,24
	ret
cmdebug ENDP

else
_DATA	ENDS
_DZIP	segment
endif

ioupdate PROC _CType PRIVATE stream:BYTE
	lodm STDO.ios_total
	.if !stream
	    lodm STDI.ios_total
	.endif
	invoke progress_update,dx::ax
	.if ax
	    xor ax,ax	; User break (ESC)
	.else
	    mov ax,1
	.endif
	ret
ioupdate ENDP

copy_axdi PROC PRIVATE
	invoke	strcpy,ds::ax,ds::di
	sub	ax,ax
	ret
copy_axdi ENDP

test_path PROC PRIVATE
	mov	ax,[si]
	test	al,al
	jz	test_path_02
	cmp	al,'\'
	je	test_path_03
	cmp	ah,':'
	jne	test_path_02
	or	al,20h
	sub	al,'a'
	mov	ah,0
	push	ax
	invoke	_disk_type,ax
	pop	ax
	jz	test_path_02
	invoke	_disk_exist,ax
	jz	test_path_01
      @@:
	invoke	filexist,ds::si
	jnz	test_path_03
	invoke	strrchr,ds::si,'\'
	jz	test_path_01
	mov	bx,ax
	mov	ax,3A00h
	cmp	[bx-1],ah
	je	test_path_01
	mov	[bx],al
	cmp	sys_erflag,al
	je	@B
    test_path_01:
	call	trace
    test_path_02:
	mov ax,si
	call copy_axdi
	ret
    test_path_03:
	xor	ax,ax
	inc	ax
	ret
test_path ENDP

init_panels PROC PRIVATE
	movmw spanela.pn_flag,config.c_flaga
	movmw spanelb.pn_flag,config.c_flagb
	movmx spanela.pn_fcb_index,config.c_fcb_indexa
	movmx spanelb.pn_fcb_index,config.c_fcb_indexb
	sub ax,ax
	mov di,offset cp_stdmask
	.if path_a.wp_mask == al
	    mov ax,offset path_a.wp_mask
	    call copy_axdi
	.endif
	.if path_b.wp_mask == al
	    mov ax,offset path_b.wp_mask
	    call copy_axdi
	.endif
      ifdef __LFN__
	.if !(console & CON_IOLFN)
	    mov _ifsmgr,al
	.endif
	.if _ifsmgr == al
	    and path_a.wp_flag,not _W_LONGNAME
	    and path_b.wp_flag,not _W_LONGNAME
	.endif
      endif
	mov dx,argvfile
	.if dzcount == ax && dx != ax
	    .if !access(ds::dx,ax)
		.if cx & _A_SUBDIR
		  @@:
		    and cflag,not _C_PANELID
		    mov bx,argvfile
		    mov dx,':'
		    .if [bx+1] == dl
			mov dl,[bx]
			or  dl,20h
			sub dl,'a'
			mov ah,0Eh
			int 21h
		    .endif
		    push ds
		    push argvfile
		    call chdir
		    jmp @F
		.else
		    mov ax,argvfile
		    invoke readword,ds::ax
		    .if ax == 4B50h
			and path_a.wp_flag,not (_W_ARCHIVE or _W_ROOTDIR)
			and path_b.wp_flag,not (_W_ARCHIVE or _W_ROOTDIR)
			or path_a.wp_flag,_W_ARCHZIP
			or flaga,_P_VISIBLE
			mov path_a.wp_arch,0
			mov ax,argvfile
			invoke strfn,ds::ax
			push dx
			push ax
			invoke strcpy,addr path_a.wp_file,dx::ax
			pop ax
			pop dx
			.if ax != argvfile
			    mov es,dx
			    dec ax
			    mov bx,ax
			    xor al,al
			    mov es:[bx],al
			    jmp @B
			.endif
		      @@:
			and cflag,not _C_PANELID
			invoke fullpath,addr path_a.wp_path,0
		    .else
			sub ax,ax
		    .endif
		.endif
	    .endif
	.endif
	ret
init_panels ENDP

ifdef __INI_LOAD__

dzloadexit PROC PRIVATE
	push	bp
	mov	bp,ax
	mov	di,offset _dsstack + 2048
	xor	si,si
	mov	[di],si
      @@:
	invoke	inientryid,ss::bp,si
	jz	@F
	inc	si
	invoke	strcat,dx::di,dx::ax
	invoke	strcat,dx::ax,addr CRLF$
	jmp	@B
      @@:
	test	si,si
	pop	bp
	ret
dzloadexit ENDP

endif

create_user PROC PRIVATE USES si
	invoke strfcat,addr __srcfile,addr configpath,addr cp_ini
	.if osopen(dx::ax,0,M_WRONLY,A_CREATE or A_TRUNC) != -1
	    mov si,ax
	    or _osfile[si],FH_TEXT
	    invoke strlen,addr default_ini
	    invoke write,si,addr default_ini,ax
	    invoke close,si
	.endif
	ret
create_user ENDP

DoszipOpen PROC PRIVATE
;;;;;;;;;----------------------------------------------------
	; Get environ %TEMP% %DZ% %PATH% %COMSPEC%
	;----------------------------------------------------
	invoke	getenvp,addr cp_temp
	stom	envtemp
;	invoke	getenvp,addr cp_dz
;	stom	envconf
	invoke	getenvp,addr cp_path
	stom	envpath
	invoke	getenvp,addr cp_comspec
	stom	comspec
	.if WORD PTR envtemp == 0	; set TEMP to .EXE dir
	    mov ax,offset programpath
	    mov WORD PTR envtemp,ax
	    mov WORD PTR envtemp+2,ds
	.endif
;;;;;;;;;----------------------------------------------------
	; Setup Menus IDD_ table
	;----------------------------------------------------
	call menusinit_OIDD
;;;;;;;;;----------------------------------------------------
	; Load DZ.EXE and get run-count and return flags
	;----------------------------------------------------
  ifdef __FAKEDZ__
	mov	WORD PTR dzexe,offset vector
	mov	WORD PTR dzexe+2,ds
	mov	ax,envseg
	mov	dz_exe.dz_envseg,ax
	mov	ax,ds
	mov	dz_exe.dz_command[2],ax
	mov	dz_exe.dz_fcb_0P[2],ax
	mov	dz_exe.dz_fcb_1P[2],ax
	mov	dz_exe.dz_exename,offset dz_exe.dz_exeproc
	mov	dz_exe.dz_command,offset dz_exe.dz_execommand
	mov	dz_exe.dz_fcb_0P,offset dz_exe.dz_fcb_160
	mov	dz_exe.dz_fcb_1P,offset dz_exe.dz_fcb_161
	push	ds
	push	offset dz_exe.dz_dzmain
	mov	bx,WORD PTR _argv
	push	ds
	push	WORD PTR [bx]
	call	strcpy
	mov	di,offset dz_exe.dz_fcb_160
	mov	si,ax
	mov	ax,2901h
	int	21h
  endif
	les	bx,dzexe
  ifndef __FAKEDZ__
	add	bx,03C4h
	les	bx,es:[bx]
  endif
	mov	si,es:[bx]
	mov	di,es:[bx+2]
	mov	ax,es:[bx+6]
	mov	bx,es:[bx+4]
	mov	es,ax
	.if di != 495Ah || si != 440Ah
;	    invoke _print,addr cp_dznotloaded
;	    invoke exit,0
	.endif
	mov	WORD PTR dzexe,bx
	mov	WORD PTR dzexe+2,es
	add	bx,208
	mov	ax,es:[bx]
	mov	dzerrno,ax
	mov	ax,es:[bx+2]
	mov	dzerflag,ax
	mov	ax,es:[bx+4]
	mov	dzcount,ax
;;;;;;;;;----------------------------------------------------
	; Set program path (%doszip%) and config path (%dz%):
	;	(1) to program path
	;	(2) from program path\dz.ini: [.]->00=<path>
; *	;	(3) from environ %DZ%
	;	(4) from command line /C<path>
	;----------------------------------------------------
	mov	bx,WORD PTR _argv
	mov	bx,[bx]
	invoke	strcpy,addr programpath,ss::bx
	invoke	strpath,dx::ax
	invoke	strcpy,addr configpath,dx::ax
;;;;;;;;;----------------------------------------------------
	; The option /C<path> overrides %DZ%
	;----------------------------------------------------
	mov ax,1
	.if ax < _argc
	    mov si,ax
	    .repeat
		mov bx,si
		shl bx,2
		add bx,WORD PTR _argv
		mov bx,[bx]
		mov al,[bx]
		.if al == '?'
		  ExitUsage:
		    invoke _print,addr cp_usage
		    invoke exit,0
		.elseif al == '/' || al == '-'
		    inc bx
		    mov al,[bx]
		    or	al,20h
		    .if al == 'x'
			.if dzcount == 0
			    mov ax,0003h
			    int 10h
			    call consinit
			.endif
		    .elseif al == 't'
			mov numfblock,500
		    .elseif al == 'l'
			mov numfblock,5000
		    .elseif al == 'c'
			inc bx
			push es
			push bx
			invoke filexist,es::bx
			cmp ax,2
			pop ax
			pop dx
			.if ZERO?
			    invoke strcpy,addr configpath,dx::ax
			.else
			    jmp ExitUsage
			.endif
		    .else
			jmp ExitUsage
		    .endif
		.else
		    mov argvfile,bx
		.endif
		inc si
	    .until si >= _argc
	.endif
	.if filexist(addr configpath) != 2	; directory ?
	    invoke strcpy,addr configpath,addr programpath
	.endif
	invoke strfcat,addr configfile,addr configpath,addr cp_ini
;;;;;;;;;----------------------------------------------------
	; Read DZ.CFG
	;----------------------------------------------------
	call config_read
;;;;;;;;;----------------------------------------------------
	; Init COMSPEC
	;----------------------------------------------------
	.if !WORD PTR comspec
	    ;-------------------------
	    ; Warning: missing COMSPEC
	    ;-------------------------
	    invoke _print,addr cp_ercomspec
	    ;
	    ; Use default -- this will fail..
	    ;
	    mov WORD PTR comspec+2,ds
	    mov WORD PTR comspec,offset dz_comspec
	.else
	    invoke strcpy,addr dz_comspec,comspec
	    stom comspec
	.endif
;;;;;;;;;----------------------------------------------------
	; Create and read DZ.INI file
	;----------------------------------------------------
	.if !filexist(addr configfile)
	    ;
	    ; virgin call..
	    ;
	    call create_user
	.endif
	.if inientryid(addr cp_comspec,0)
	    push dx
	    push ax
	    invoke dzexpenviron,dx::ax
	    invoke filexist,dx::ax
	    pop ax
	    pop dx
	    .if !ZERO?
		invoke strnzcpy,addr dz_comspec,dx::ax,80
		mov comargs,0
		.if inientryid(addr cp_comspec,1)
		    invoke dzexpenviron,dx::ax
		    invoke strnzcpy,addr comargs,dx::ax,64
		.endif
	    .endif
	.endif

;;;;;;;;;----------------------------------------------------
	; Init panels
	;----------------------------------------------------
	pushl	cs
	push	offset cmhelp
	call	thelpinit
	movp	oupdate,ioupdate
	mov	ax,numfblock
	mov	wsmaxfbb,ax
	mov	wsmaxfba,ax
	call	setconfirmflag
	mov	bx,offset pending_file
	.if BYTE PTR [bx]
	    invoke removefile,ds::bx
	    mov pending_file,0
	.endif
	.if cflag & _C_DELTEMP
	    invoke removetemp,addr cp_ziplst
	    invoke removetemp,addr cp_dzcmd
	.endif
	and	cflag,not _C_DELTEMP
ifdef __INI_LOAD__
	cmp	dzcount,0
	jne	@F
	mov	ax,offset cp_load
	call	dzloadexit
	jz	@F
	invoke	command,ss::di
	test	ax,ax
	jz	@F
	mov	ax,23
	mov	dzexitcode,ax
	ret
      @@:
endif
	call	init_panels
	call	apiopen
	call	cursoroff
  ifdef __MOUSE__
	.if console & CON_MOUSE
	    call mouseon
	.endif
  endif
	call	history_read
	call	prect_open_ab
	mov	ax,offset spanelb
	cmp	cpanel,ax
	jne	@F
	mov	ax,offset spanela
      @@:
	call	panel_openmsg
	mov	di,offset programpath
	mov	si,offset path_a.wp_path
	call	test_path
	jnz	@F
	and	path_a.wp_flag,not _W_ARCHIVE
      @@:
	mov	si,offset path_b.wp_path
	call	test_path
	jnz	@F
	and	path_b.wp_flag,not _W_ARCHIVE
      @@:
	test	cflag,_C_COMMANDLINE
	jz	@F
	call	cursoron
      @@:
	call	panel_open_ab
  toend:
	ret
DoszipOpen ENDP

tdummy:
	retx

DoszipClose PROC PRIVATE
	movp	tupdate,tdummy
	movmw	config.c_fcb_indexa,spanela.pn_fcb_index
	movmw	config.c_cel_indexa,spanela.pn_cel_index
	movmw	config.c_fcb_indexb,spanelb.pn_fcb_index
	movmw	config.c_cel_indexb,spanelb.pn_cel_index
	mov	bx,WORD PTR spanela.pn_dialog
	mov	ax,spanela.pn_flag
	and	al,not _P_VISIBLE
	mov	dl,[bx]			; .dl_flag
	and	dl,_D_DOPEN
	shl	dl,1
	or	al,dl
	mov	config.c_flaga,ax
	mov	bx,WORD PTR spanelb.pn_dialog
	mov	ax,spanelb.pn_flag
	and	al,not _P_VISIBLE
	mov	dl,[bx]
	and	dl,_D_DOPEN
	shl	dl,1
	or	al,dl
	mov	config.c_flagb,ax
	test	cflag,_C_AUTOSAVE
	jz	@F
	call	config_save
     @@:
	mov	ax,panela
	call	panel_close
	mov	ax,panelb
	call	panel_close
	call	apiclose
	invoke	gotoxy,0,com_info.ti_ypos
	.if dzexitcode != 23
	    .if cflag & _C_DELHISTORY
		invoke historyremove
	    .endif
	.endif
  ifdef __TE__
	call	tcloseall
  endif
	ret
DoszipClose ENDP

dzmain	PROC _CType PUBLIC
	call	DoszipOpen
	cmp	ax,23
	je	dzmain_end
	test	ax,ax
	jz	dzmain_close
  ifdef __FAKEDZ__
      @@:
	call	dzmodal
	cmp	dzexitcode,23
	jne	dzmain_close
	mov	dzexitcode,0
	mov	mainswitch,0
	lodm	dzexe
	mov	cx,ax
	add	ax,82
	invoke	stdmsg,addr dz_comspec,addr cp_exec,dx::cx,dx::ax
	jmp	@B
  else
	call dzmodal
  endif
    dzmain_close:
	call	DoszipClose
    dzmain_end:
	mov	ax,dzexitcode
	ret
dzmain	ENDP

_DZIP	ENDS

	END
