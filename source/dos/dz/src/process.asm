; PROCESS.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include dos.inc
include io.inc
include dir.inc
include stdlib.inc
include ini.inc
include string.inc
include conio.inc
include errno.inc
ifdef DEBUG
  include stdio.inc
endif
	; Load and execute program

	PUBLIC	cp_dzcmd
	PUBLIC	cp_initype
	PUBLIC	cp_linefeed
	PUBLIC	command
	PUBLIC	comargs
	PUBLIC	dzexpenviron
	PUBLIC	fbinitype
	PUBLIC	parse_type
	PUBLIC	cp_dznotloaded
ifdef __FF__
	FindFile PROTO _CType :DWORD, :WORD	; macro %find%
	extrn	findfilemask:BYTE
endif

S_EXEC		STRUC	; info copied to dz.exe to execute
exec_name	db 80 dup(?)	; %comspec% /C or file.exe
exec_argc	db ?
exec_argv	db ?
exec_command	db 126 dup(?)
S_EXEC		ENDS

_DATA	segment

cp_echooff	db	'@echo off'
cp_linefeed	db	13,10
cp_0D0A		db	13,10,0
cp_202C		db	' ,',0
macro_view	db	'%view%',0
macro_edit	db	'%edit%',0
macro_find	db	'%find%',0
macro_dz	db	'%dz%',0
macro_doszip	db	'%doszip%',0
cp_dznotloaded	db	'Error: DZ.EXE not loaded',0
cp_erexcommand	db	'Unable to execute command',0
format_sLLsLLs	db	'%s',10,10
		db	'%s',10,10,'%s',0
$0D00		db	0Dh,0
comargs		db	'/C',0
		db	61 dup(?)
cp_dzcmd	db	'dzcmd.bat',0
cp_initype	db	'Filetype',0

_DATA	ENDS

_DZIP	segment

error_dznotloaded PROC PRIVATE	; need dz.exe..
	invoke ermsg,0,addr format_sLLsLLs,
		addr cp_erexcommand,ss::di,addr cp_dznotloaded
	ret
error_dznotloaded ENDP

dzexpenviron PROC _CType cmdl:DWORD
	invoke strxchg,cmdl,addr macro_dz,addr configpath,4
	invoke strxchg,cmdl,addr macro_doszip,addr programpath,8
	invoke expenviron,cmdl
	ret
dzexpenviron ENDP

ex_cpycomspec PROC PRIVATE	; SI EXEC_ struct, DI command line
	invoke	strnzcpy,ss::si,comspec,80
	add	ax,82
	invoke	strcpy,dx::ax,addr comargs
	invoke	strcat,dx::ax,addr cp_space
	mov	bx,ax
	invoke	strlen, dx::ax
	mov	cx,126
	sub	cx,ax
	add	ax,bx
	invoke	strnzcpy,dx::ax,dx::di,cx
	ret
ex_cpycomspec ENDP

ex_initblock PROC PRIVATE
	mov	ax,0D00h
	mov	[si].S_EXEC.exec_argc,al
	mov	[si].S_EXEC.exec_argv,ah
	cmp	[si].S_EXEC.exec_command,al
	jz	ex_initblock_00
	lea	ax,[si].S_EXEC.exec_command
	push	ss
	push	ax
	mov	bx,ax
	call	strlen
	add	bx,ax
	inc	ax
	mov	[si].S_EXEC.exec_argc,al
	mov	[si].S_EXEC.exec_argv,' '
	mov	ax,0Dh
	mov	[bx],ax
    ex_initblock_00:
	ret
ex_initblock ENDP

ex_copyblock PROC PRIVATE
	invoke	memcpy,dzexe,ss::si,SIZE S_EXEC
	mov	ax,1
	mov	mainswitch,ax
	mov	dzexitcode,23
	ret
ex_copyblock ENDP

ex_loadblock PROC PRIVATE	; SS:SI EXEC struct, SS:DI command line
	mov	dx,ss
	mov	al,[si+1]
	cmp	al,':'
	je	@F
	cmp	al,'\'
	je	@F
	lea	ax,[di-WMAXPATH]
	mov	bx,cpanel
	mov	bx,WORD PTR [bx].S_PANEL.pn_wsub
	invoke	strfcat,dx::ax,[bx].S_WSUB.ws_path,dx::si
	mov	bx,ax
	xor	al,al
	mov	[bx+79],al
	invoke	strcpy,dx::si,dx::bx
      @@:
	call	ex_initblock
	call	ex_copyblock
	ret
ex_loadblock ENDP

command PROC pascal USES si di cmd:DWORD ; boolean
local	exes:WORD
local	exeo:WORD
local	exec:S_EXEC
local	path[WMAXPATH]:BYTE
local	temp[WMAXPATH]:BYTE
	lea si,exec
	lea di,path
	invoke strnzcpy,ss::di,cmd,WMAXPATH
	invoke strtrim,dx::ax
	jz command_end
	invoke dzexpenviron,ss::di
	mov al,[di]
	cmp al,'%'
	jne command_load
	.if !strnicmp(ss::di,addr macro_view,6)
	    mov dx,di		; %view% <filename>
	    add dx,7
	    invoke load_tview,ss::dx,ax
	    jmp command_end
	.endif
	.if !strnicmp(ss::di,addr macro_edit,6)
	    mov ax,di		; %edit% <filename>
	    add ax,7
	    invoke load_tedit,ss::ax,4
	    jmp command_end
	.endif

ifdef __FF__
	.if !strnicmp(ss::di,addr macro_find,6)
	    .if [di+6] == al	; %find% [<path>] [<mask>] [<string>]
		call cmsearch
		jmp command_end
	    .endif
	    invoke strchr,addr [di+7],' '
	    mov bx,ax
	    .if strrchr(addr [di+7],' ')
		mov dx,'?'
		mov [bx],dh
		mov cx,bx
		mov bx,ax
		mov [bx],dh
		.if [bx+1] != dl
		    cmp bx,cx
		    mov bx,cx
		    .if !ZERO? ; je
			inc ax
			invoke strcpy,addr searchstring,ss::ax
			mov dl,'?'
		    .endif
		.endif
		inc bx
		.if [bx] != dl
		    invoke strcpy,addr findfilemask,ss::bx
		.endif
	    .endif
	    invoke FindFile,addr findfilemask,0
	    jmp command_end
	.endif
endif

    command_load:
	cmp	WORD PTR dzexe,0
	jne	command_04
	call	error_dznotloaded
	jmp	command_end
    command_com:
	call	ex_cpycomspec
    command_exe:
	call	ex_loadblock
	jmp	command_end
    command_bat:
	invoke	strfcat,addr temp,envtemp,addr cp_dzcmd
	mov	di,ax
	call	ex_cpycomspec
	invoke	strcat,dx::ax,addr $0D00
	mov	ax,si
	add	ax,82
	invoke	strlen,ss::ax
	add	al,2
	mov	[si].S_EXEC.exec_argc,al
	mov	[si].S_EXEC.exec_argv,' '
	invoke	osopen,ss::di,0,M_WRONLY,A_CREATE or A_TRUNC
	cmp	ax,-1
	je	ex_makebatch_fail
	mov	si,ax
	or	cflag,_C_DELTEMP
	mov	si,ax
	invoke	oswrite,ax,addr cp_echooff,11
	cmp	ax,11
	jne	@F
	lea	di,path
	invoke	strlen,ss::di
	invoke	oswrite,si,ss::di,ax
	or	ax,ax
	jz	@F
	invoke	oswrite,si,addr cp_linefeed,2
	cmp	ax,2
	jne	@F
	invoke	close,si
	mov	ax,1
	lea	si,exec
	jmp	ex_makebatch_end
      @@:
	invoke	close,si
    ex_makebatch_fail:
	invoke	eropen,ds::di
	inc	ax
    ex_makebatch_end:
	or	ax,ax
	jz	command_end
	call	ex_copyblock
    command_end:
	ret
    command_04:
	mov	bx,ss
	invoke	strchr,bx::di,10
	jnz	command_bat
	invoke	strchr,bx::di,'>'
	jnz	command_com
	invoke	strchr,bx::di,'<'
	jnz	command_com
	invoke	strchr,bx::di,' '
	jz	@F
	mov	bx,ax
	mov	BYTE PTR es:[bx],0
	mov	bx,ss
      @@:
	mov	exeo,ax
	mov	exes,dx
	invoke	strcpy,bx::si,bx::di
	cmp	exeo,0
	je	@F
	mov	bx,exeo
	mov	BYTE PTR es:[bx],' '
      @@:
	invoke	searchp,ss::si
	test	ax,ax
	jz	command_com	; File not found..
	invoke	strcpy,ss::si,dx::ax
	call	isexec
	cmp	ax,3
	jne	command_com	; File is .BAT or .COM
	mov	bx,exeo
	test	bx,bx
	jz	@F
	inc	bx
	lea	ax,[si].S_EXEC.exec_command
	mov	dx,exes
	invoke	strnzcpy,ss::ax,dx::bx,126
	jmp	command_10
      @@:
	xor	ax,ax
	mov	[si].S_EXEC.exec_command,al
    command_10:
ifdef __LFN__
	cmp	_ifsmgr,0
	jz	command_12
	cmp	_osmajor,5
	jne	command_12
	invoke	osopen,ss::si,0,M_RDONLY,A_OPEN
	cmp	ax,-1
	je	command_11
	push	ax
	invoke	osread,ax,addr temp,32
	pop	dx
	push	ax
	push	dx
	call	close
	pop	ax
	cmp	ax,32
	jne	command_11
	lea	bx,temp
	mov	ax,[bx+24]
	cmp	ax,0040h	; 40h or greater if new format
	jb	command_12
	sub	ax,ax
	cmp	ax,[bx+20]
	jne	command_12
	cmp	ax,[bx+22]
	je	command_11
    command_12:
	jmp	command_exe
    command_11:
	jmp	command_com	; Use COMSPEC
else
	jmp	command_exe
endif
command ENDP

parse_xchg PROC PRIVATE
	mov	[si],ax
	mov	[si+2],ch
	mov	ch,0
	mov	ax,ss
	push	ax			; buffer
	push	[bp+8]
	push	ax			; S1
	push	si
	push	ax			; S2
	push	dx
	push	cx			; size of macro
	call	strxchg
	ret
parse_xchg ENDP

; buf (DZ.INI): <command> [options+macros]
; fbname: file name or full path
;
parse_type PROC pascal USES si di buf:DWORD, fbname:DWORD
local	longp[WMAXPATH]:BYTE
local	cpath[MAXPATH]:BYTE
local	fname[MAXFILE+MAXEXT]:BYTE
local	longf:WORD
local	S2[4]:BYTE
local	S1[4]:BYTE
	invoke	strchr, buf, '!'	; file macro used ?
	jnz	parse_type_do
	lea	bx,S1
	mov	al,' '
	mov	[bx],al
	mov	BYTE PTR [bx+1],'"'
	mov	[bx+2],ah
	invoke	strchr,fbname,ax
	mov	si,ax
	jnz	parse_type_00
	mov	[bx+1],al
    parse_type_00:
	invoke	strcat,buf,ss::bx
	invoke	strcat,dx::ax,fbname
	or	si,si
	jz	parse_type_01
	inc	bx
	invoke	strcat,dx::ax,ss::bx
    parse_type_01:
	xor	bx,bx
	jmp	parse_type_end
    parse_type_do:
	lea	si,S1
	lea	di,S2
	xor	ax,ax
	mov	[si+2],ax
	mov	[di+2],ax
	invoke	wlongpath,0,fbname
	lea	bx,longp
	invoke	strcpy,ss::bx,dx::ax
	les bx,fbname
	mov ax,es:[bx]
	.if al == '\' || ah == ':'
	    invoke strcpy,addr cpath,addr longp
	    push ax
	    invoke strfn,addr cpath
	    pop bx
	    .if ax != bx
		mov bx,ax
		mov BYTE PTR [bx-1],0
	    .endif
	    lea bx,fname
	    invoke strnzcpy,ss::bx,dx::ax,14
	.else
	    invoke fullpath,addr cpath,0
	    or ax,ax
	    jz parse_type_end
	    invoke wshortname,fbname
	    lea bx,fname
	    invoke strnzcpy,ss::bx,dx::ax,14
	.endif
	mov	ax,'››'
	mov	[di],ax
	mov	ax,'!!'
	mov	dx,di
	mov	cx,2
	call	parse_xchg
	invoke	strrchr,addr fname,'.'
	mov	dx,ax
	jnz	parse_type_ext
	mov	dx,di		; remove extension code from line
	mov	[di],al
    parse_type_ext:
	mov	bx,dx
	mov	ax,'!.'		; '.!~' - short extension
	mov	ch,'~'
	mov	cl,3
	call	parse_xchg
	mov	BYTE PTR [bx],0 ; remove extension
	invoke	strfn, addr longp	; '.!' - long extension
	mov	longf,ax		; file offset
	invoke	strrchr,dx::ax,'.'
	mov	dx,ax
	jnz	parse_type_lext
	mov	dx,di
	mov	[di],al
    parse_type_lext:
	mov	bx,dx
	mov	ax,'!.'
	mov	cx,2
	call	parse_xchg
	mov	cx,2
	mov	[bx],ch		; remove extension
	lea	bx,cpath	; '!:' - Drive + ':'
	mov	dx,bx
	mov	[bx+2],ch
	mov	ax,':!'
	call	parse_xchg
	lea	bx,cpath	; '!~\' - Short path
	add	bx,2
	mov	dx,bx
	mov	ch,'\'
	mov	cl,3
	mov	ax,'~!'
	mov	[bx],ch
	call	parse_xchg
	lea	ax,longp	; '!\' - Long path
	mov	bx,longf
	mov	dx,ax
	mov	cx,2
	cmp	ax,bx
	je	parse_type_longp
	add	dx,cx
	dec	bx
	mov	[bx],ch		; remove \file name
    parse_type_longp:
	mov	ax,'\!'
	call	parse_xchg
	lea	dx,fname	; '~!' - Short file
	mov	cx,2
	mov	ax,'!~'
	call	parse_xchg
	mov	dx,longf	; '!' - Long file
	mov	cx,1
	mov	ax,'!'
	call	parse_xchg
	mov	ax,'!'
	mov	[di],ax
	mov	ax,'››'
	mov	dx,di
	mov	cx,2
	call	parse_xchg
	inc	di
    parse_type_end:
	ret
parse_type ENDP

;
; Parse filename to command string from .ini section
;
; return: 0 not found (ZF set)
;	  1 found
;
inicommand PROC _CType PRIVATE USES si di buffer:DWORD, filename:DWORD, section:DWORD
	.if strrchr(filename, '.')
	    inc ax
	.else
	    invoke strfn,filename
	.endif
	.if inientry(section,dx::ax,addr configfile)
	    invoke strcpy,buffer,dx::ax
	    mov si,dx
	    mov di,ax
	    invoke parse_type,dx::ax,filename
	    invoke strxchg,si::di,addr cp_202C,addr cp_0D0A,2
	    invoke command,si::di
	    mov ax,1
	.endif
      @@:
	test ax,ax
	ret
inicommand ENDP

;
; Parse filename to command string from section [Filetype]
;
fbinitype PROC pascal fblk:DWORD, cmdl:DWORD
	add	WORD PTR fblk,S_FBLK.fb_name
	invoke	inicommand,cmdl,fblk,addr cp_initype
	ret
fbinitype ENDP

_DZIP	ENDS

	END
