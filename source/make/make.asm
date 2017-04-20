; MAKE.ASM--
; Copyright (c) 2016 GNU General Public License www.gnu.org/licenses
;
; Change history:
; 2017-04-20 - added line-break '\' for targets
; 2017-02-25 - added switch -I -- include path
; 2017-02-25 - fixed bug in .xxx.obj: only one cmd-line used..
; 2017-02-25 - added .EXTENSIONS and .SUFFIXES
; 2017-02-25 - added include path : %AsmcDir%\lib | %DZ%\lib
;
include stdio.inc
include stdlib.inc
include alloc.inc
include string.inc
include time.inc
include direct.inc
include io.inc
include process.inc
include ctype.inc
include crtl.inc
include winbase.inc

LINEBREAKCH	equ 5Eh ; '^'

.data

externdef	__pCommandCom:LPSTR
externdef	envtemp:DWORD
externdef	errorlevel:DWORD

cpinfo		db "Doszip Make Version 1.4 Copyright (c) 2017 GNU General Public License",10,10,0
cpusage		db "USAGE: MAKE [-/options] [macro=text] [target(s)]",10
		db 10
		db " -a    build all targets (always set)",10
		db " -d    debug - echo progress of work",10
		db " -f#   full pathname of make file",10
		db " -h    do not print program header",10
		db " -I#   set include path",10
		db " -s    silent mode (do not print commands)",10
		db 10,0

option_a	db 1
option_d	db 0
option_h	db 0
option_s	db 0

MAXTARGET	equ 10000h
MAXTARGETS	equ 100
MAXSYMBOLS	equ 1000
MAXMAKEFILES	equ 7
MAXLINE		equ 512

_T_TARGET	equ 0
_T_METHOD	equ 1
_T_ALL		equ 2

S_TARGET	STRUC
t_target	dd ?
t_string	dd ?
t_command	dd ?
t_type		dd ?
t_prev		dd ?
t_next		dd ?
t_srcpath	dd ?	; {path}.c.obj:
t_objpath	dd ?	; .c{path}.obj:
S_TARGET	ENDS

symbol_count	dd 0
symbol_table	dd 0
target_count	dd 0
target_table	dd 0

line_fp		dd MAXMAKEFILES+1 dup(0)
line_buf	db MAXLINE dup(0)
line_ptr	dd line_buf
line_id		dd 0

if_level	db 0
if_state	db 15 dup(0)

linefeed_unix	db 0Ah,0
linefeed	dd linefeed_unix

commandfile	db _MAX_PATH dup(0)
responsefile	db _MAX_PATH dup(0)
includepath	db _MAX_PATH dup(0)
currentfile	db _MAX_PATH dup(0)

default_ext	db ".obj",0
suffixes	dd default_ext
		dd 32 dup(0)

file_asm	db ".asm",0
file_idd	db ".idd",0
file_c		db ".c",0
extensions	dd file_asm
		dd file_idd
		dd file_c
		dd 32 dup(0)

null_string	db 0
cmdexe		db "%SystemRoot%\system32\cmd.exe"
		db 128 dup(0)

S_ARGS		STRUC
a_name		dd ?
a_next		dd ?
S_ARGS		ENDS

file_args	dd 0 ;S_ARGS <makefile, 0>
target_args	dd 0
token		dd 0
		db '='
token_equal	db '=',0

	.code

ltoken	PROC USES esi edi ebx string:ptr sbyte

	mov esi,token
	.if string
		mov esi,string
	.endif
	mov esi,strstart(esi)
	mov token,esi
	xor eax,eax

	.while	1
		lodsb
		.switch
		  .case !eax
			lea ecx,[esi-1]
			.if ecx == token
			    xor eax,eax
			    .break
			.endif
			mov eax,token
			mov token,ecx
			.break
		  .case eax == '='
			lea ecx,[esi-1]
			lea eax,token_equal
			.if ecx == token
				.if byte ptr [esi] == '='
					inc esi
					dec eax
				.endif
				mov token,esi
				.break
			.endif
			dec esi
			mov BYTE PTR [esi],0
			salloc(token)
			mov BYTE PTR [esi],'='
			mov token,esi
			.break
		  .case _ctype[eax*2+2] & _SPACE
			mov eax,token
			mov token,esi
			.break
		.endsw
	.endw
	test eax,eax
	ret

ltoken	ENDP

istarget PROC USES edi ebx line:ptr sbyte
	strspace( strstart( line ) )
	jnz @F
	cmp BYTE PTR [ecx-1],':'
	je  target
	mov eax,ecx
@@:
	mov bl,[eax]
	mov edi,eax
	strstart( eax )
	cmp BYTE PTR [eax],':'
	je  target
	mov eax,':'
	mov [edi],ah
	strchr( line, eax )
	mov [edi],bl
	jz  toend
	movzx eax,BYTE PTR [eax+1]
	test eax,eax
	jz target
	mov al,byte ptr _ctype[eax*2+2]
	and al,_SPACE
toend:
	ret
target:
	inc eax
	jmp toend
istarget ENDP

findsymbol PROC USES esi edi ebx symbol:ptr sbyte
	mov edi,symbol
	mov esi,symbol_table
	mov ebx,symbol_count
	mov cx,[edi]
	or  cx,2020h
sloop:
	test ebx,ebx
	jz  error
	dec ebx
	mov eax,[esi]
	add esi,4
	mov dx,[eax]
	or  dx,2020h
	cmp dx,cx
	jne sloop
	_stricmp( eax, edi )
	jne sloop
	sub esi,4
	mov edx,esi
	mov ecx,[edx]
	mov eax,[edx+MAXSYMBOLS*4]
toend:
	ret
error:
	xor eax,eax
	jmp toend
findsymbol ENDP

alloc_string PROC USES edi value:sdword
  local base
	alloca( MAXTARGET )
	mov edi,eax
	ExpandEnvironmentStrings( value, edi, MAXTARGET-1 )
	salloc( edi )
	ret
alloc_string ENDP


addsymbol PROC USES edi symbol:ptr sbyte, value:sdword
	findsymbol( symbol )
	jz @F
	mov edi,edx
	free(eax)
	alloc_string( value )
	jz  error
	jmp set_value
@@:
	mov edi,symbol_table
	mov eax,symbol_count
	cmp eax,MAXSYMBOLS-1
	jnb error
	lea edi,[edi+eax*4]
	inc eax
	mov symbol_count,eax
	salloc( symbol )
	jz error
	mov [edi],eax
	mov eax,value
	test eax,eax
	jz toend
	alloc_string( eax )
	jz error
set_value:
	mov [edi+MAXSYMBOLS*4],eax
toend:
	ret
error:
	perror( "To many symbols.." )
	exit ( 1 )
addsymbol ENDP

expandsymbol PROC USES esi edi ebx string:ptr sbyte

local	base
local	symbol_name
local	symbol_macro

	alloca( MAXTARGET )
	mov base,eax
	mov esi,eax
	add eax,MAXTARGET-256
	mov symbol_name,eax
	add eax,128
	mov symbol_macro,eax
	strcpy( esi, string )
	mov edi,eax
	strtrim( eax )
loop_$:
	strchr( edi, '$' )
	jz  toend
	lea edi,[eax+1]
	cmp BYTE PTR [edi],'('
	jne loop_$
	mov edx,symbol_macro
	mov ecx,symbol_name
	mov ebx,eax
	mov ax,[ebx]
	mov [edx],ax
	add ebx,2
	add edx,2
@@:
	mov al,[ebx]
	inc ebx
	cmp al,' '
	je  @B
	cmp al,9
	je  @B
	mov [ecx],al
	mov [edx],al
	inc ecx
	inc edx
	test al,al
	jz error
	cmp al,')'
	jne @B
	mov [edx],al
	xor eax,eax
	mov [ecx-1],al
	mov [edx],al
	findsymbol( symbol_name )
	jnz @F
	mov eax,offset null_string
@@:
	strxchg( esi, symbol_macro, eax )
	dec edi
	jmp loop_$
error:
	perror(string)
	exit(1)
toend:
	salloc(esi)
	ret
expandsymbol ENDP

;-------------------------------------------------------------------------------
; Read makefile
;-------------------------------------------------------------------------------

skipiftag PROC
	.if !fgets( esi, MAXLINE, line_fp )
		perror( "Missing !else or !endif" )
		exit( 1 )
	.endif
	inc line_id
	strtrim( eax )
	jz  skipiftag
	strstart( esi )
	mov edi,eax
	mov eax,[eax]
	cmp al,'!'
	jne skipiftag
	inc edi
	strstart( edi )
	mov eax,[eax]
	or  eax,20202020h
	cmp eax,'esle'
	je  else@
	cmp eax,'idne'
	je  endif@
	cmp ax,'fi'
	jne skipiftag
	movzx	eax,if_level
	mov if_state[eax],0
	inc if_level
	call skipiftag
	jmp skipiftag
else@:
	movzx eax,if_level
	cmp if_state[eax-1],0
	je  skipiftag
	jmp toend
endif@:
	dec if_level
toend:
	ret
skipiftag ENDP

readline PROC USES esi edi ebx

local	base
local	symbol

	mov base,alloca(MAXTARGET)
	add eax,MAXTARGET-256
	mov symbol,eax

	.while 1

		mov eax,line_fp
		.break .if !eax

		mov esi,line_ptr
		mov edi,esi

		.if !fgets(edi, MAXLINE, eax)

			fclose(line_fp)
			lea edx,line_fp
			memcpy(edx, addr [edx+4], MAXMAKEFILES*4)
			.continue
		.endif

		inc line_id
		.continue .if !strtrim(eax)


		mov edi,strstart(esi)		  ; EDI to start of line
		mov esi,ltoken(strcpy(base, eax)) ; ESI to first token
		mov eax,[edi]
		.continue .if al == '#'

		.if al != '!'

			mov eax,edi
			.break
		.endif

		push	expandsymbol(addr [edi+1])
		strcpy( base, eax )
		call	free
		mov	edi,strstart(eax)

		.switch
		  .case !_strnicmp(edi, "include", 7)

			mov ebx,expandsymbol(strstart(addr [edi+8]))
			.if !fopen(eax, "rt") && includepath

				fopen(strfcat(addr currentfile, addr includepath, ebx), "rt")
			.endif
			xchg ebx,eax
			free(eax)
			.if !ebx

				perror(edi)
				exit(1)
			.endif
			lea edx,line_fp
			memmove(addr [edx+4], edx, MAXMAKEFILES*4-4)
			mov [edx],ebx
			.continue

		  .case !_strnicmp(edi, "endif", 5)

			dec if_level
			.continue

		  .case !_strnicmp(edi, "else", 4)

			movzx ebx,if_level
			.if if_state[ebx-1] == 0

				skipiftag()
			.endif
			.continue
		.endsw

		mov ax,[edi]
		or  ax,2020h
		.if ax != 'fi'

			syntax_error()
		.endif

		movzx ebx,if_level
		mov if_state[ebx],1
		inc if_level

		.if !_strnicmp(edi, "ifdef", 5)

			.if ltoken(addr [edi+6])

				.if !findsymbol(eax)

					skipiftag()
				.else
					mov if_state[ebx],0
				.endif
				.continue
			.endif

			syntax_error()
		.endif

		.if !_strnicmp( edi,"ifndef", 6 )

			.if !ltoken(addr [edi+7])

				syntax_error()
			.endif
			.if findsymbol(eax)

				skipiftag()
			.else
				mov if_state[ebx],0
			.endif
			.continue
		.endif

		.if _strnicmp( edi, "ifeq", 4 )

			mov al,[edi+2]
			.if al != ' ' && al != 9

				syntax_error()
			.endif

			.if !ltoken(addr [edi+3])

				syntax_error()
			.endif
			mov edi,eax
			case_if_loop()
		.else
			case_ifeq()
		.endif
	.endw
	ret

case_if_loop:	; !if <> == <> || <> ..

	ltoken( 0 )
	jz	case_if_a
	mov	esi,eax
	ltoken( 0 )
	jz	syntax_error

	xchg	esi,eax
	mov	eax,[eax]
	.switch al
	  .case '='
		jmp	case_if_a_eq_b
	  .case '<'
		call	find_and_compare
		jb	case_if_false
		jmp	case_if_true
	  .case '>'
		call	find_and_compare
		ja	case_if_false
		jmp	case_if_true
	  .case '&'
		findsymbol( edi )
		jz	case_if_false
		cmp	BYTE PTR [eax],'0'
		je	case_if_false
		findsymbol( esi )
		jz	case_if_false
		cmp	BYTE PTR [eax],'0'
		je	case_if_false
		jmp	case_if_true
	  .case '|'
		findsymbol( edi )
		jz	case_if_false
		cmp	BYTE PTR [eax],'0'
		jne	case_if_true
		findsymbol( esi )
		jz	case_if_false
		cmp	BYTE PTR [eax],'0'
		jne	case_if_true
		jmp	case_if_false
	  .default
		jmp	syntax_error
	.endsw

case_ifeq:
	ltoken( addr [edi+5] )
	jz	syntax_error
	mov	edi,eax
	ltoken( 0 )
	jz	syntax_error
	mov	esi,eax
case_if_a_eq_b:
	call	find_and_compare
	jne	case_if_false
case_if_true:
	.if ltoken(0)

		mov if_state[ebx],0
	.elseif BYTE PTR [eax] == '&'
		jmp case_if_next
	.endif
	retn
case_if_false:
	ltoken( 0 )
	jz	case_skipdef
	cmp	BYTE PTR [eax],'|'
	jne	case_skipdef
case_if_next:
	ltoken( 0 )
	jz	syntax_error
	mov	edi,eax
	jmp	case_if_loop
case_if_a:
	.if !findsymbol(edi)

		mov eax,edi
	.endif
	.if BYTE PTR [eax] != '0'

		mov if_state[ebx],0
		retn
	.endif
case_skipdef:
	skipiftag()
	retn
find_and_compare:
	.if findsymbol(edi)

		mov edi,eax
	.endif
	.if findsymbol(esi)

		mov esi,eax
	.endif
	_stricmp(edi, esi)
	retn
syntax_error:
	perror(edi)
	exit(1)
readline ENDP

issymbol PROC USES esi line:ptr sbyte
	mov	edx,line
	strchr( edx, '=' )
	jz	toend
	mov	esi,eax
	mov	BYTE PTR [eax],0
	strspace( edx )
	mov	BYTE PTR [esi],'='
	jz	symbol
	strstart( eax )
	cmp	eax,esi
	je	symbol
	mov	ax,[eax]
	cmp	ax,'=+'
	jne	nosymbol
symbol:
	inc	edx
	mov	eax,esi
toend:
	ret
nosymbol:
	xor	eax,eax
	jmp	toend
issymbol ENDP

getline PROC USES esi edi ebx

local	base
local	symbol

	mov base,alloca( MAXTARGET )

	add eax,MAXTARGET-256
	mov symbol,eax
lineloop:
	call readline
	jz toend
	mov edi,eax			; EDI to start of line
	mov eax,[edi]
	cmp al,'.'
	je  case_dot
	issymbol( edi )
	jnz case_macro
return_EDI:
	mov eax,edi
	test eax,eax
toend:
	ret

case_dot:
	_strnicmp( edi, ".DEFAULT", 8 )
	jz CASE_DEFAULT
	_strnicmp( edi, ".DONE", 5 )
	jz CASE_DONE
	_strnicmp( edi, ".IGNORE", 7 )
	jz CASE_IGNORE
	_strnicmp( edi, ".INIT", 5 )
	jz CASE_INIT
	_strnicmp( edi, ".SILENT", 7 )
	jz CASE_SILENT
	_strnicmp( edi, ".RESPONSE", 9 )
	jz CASE_RESPONSE
	_strnicmp( edi, ".EXTENSIONS", 11 )
	jz CASE_EXTENSIONS
	_strnicmp( edi, ".SUFFIXES", 9 )
	jz CASE_SUFFIXES
	;.xxx.obj:
	jmp return_EDI

CASE_DEFAULT:	; define default rule to build target
CASE_DONE:	; target to build, after all other targets are build
CASE_IGNORE:	; ignore all error codes during building of targets
CASE_INIT:	; first target to build, before any target is build
	jmp lineloop
CASE_SILENT:	; do not echo commands
	inc option_s
	jmp lineloop
CASE_RESPONSE:	; define a response file for long ( > 128) command lines
	jmp lineloop
CASE_SUFFIXES:	; the suffixes list for selecting implicit rules

	strtoken( edi )
	.if !strtoken(0)
		push edi
		lea edi,suffixes
		xor eax,eax
		mov ecx,32
		rep stosd
		pop edi
		jmp lineloop
	.endif
	lea esi,suffixes
	mov edx,eax
	.while	eax
		lodsd
	.endw
	mov	eax,edx
	.while	eax
		.break .if byte ptr [eax] != '.'
		mov [esi-4],salloc(eax)
		add esi,4
		strtoken(0)
	.endw
	jmp lineloop

CASE_EXTENSIONS:; add extensions to the suffixes list

	strtoken( edi )
	lea esi,extensions
	.while eax
	    lodsd
	.endw
	.while strtoken(0)
	    .break .if byte ptr [eax] != '.'
	    mov [esi-4],salloc(eax)
	    add esi,4
	.endw
	jmp lineloop

case_macro:
	mov edx,base
	xor ecx,ecx
	mov [edx],cl
	mov [eax],cl
	lea esi,[eax+1]
	cmp BYTE PTR [eax-1],'+'
	jne @F		; case '+='
	mov [eax-1],cl
	strtrim( edi )
	findsymbol( edi )
	jz @F
	strcat( strcpy( base, eax ), " " )
@@:
	strtrim( edi )
	strcpy( symbol, edi )
	strtoken( esi )
	mov esi,base
	jz  add_macro
	jmp add_word
next_line:
	call readline
	jz add_macro
	strtoken( eax )
	jz add_macro
add_word:
	mov cx,[eax]
	cmp cx,'\'
	je  next_line
	cmp cx,'&'
	je  next_line
	strcat( esi, eax )
	strcat( esi, " " )
	strtoken( 0 )
	jnz add_word
add_macro:
	strtrim( esi )
	addsymbol( symbol, esi )
	jmp lineloop
getline ENDP

addtarget PROC USES esi edi ebx target:ptr sbyte

local	base
local	target_name
local	target_string
local	target_command
local	target_srcpath

	mov base,alloca( MAXTARGET )
	mov edi,base
	mov esi,target
	strtrim(esi)
	mov byte ptr [edi],0

	.while byte ptr [esi+eax-1] == '\'

		mov byte ptr [esi+eax-1],0
		strcat(edi, esi)
		mov byte ptr [esi],0
		.break .if !fgets(esi, MAXLINE, line_fp)
		inc line_id
		.break .if !strtrim(esi)
	.endw
	strcat(edi, esi)
	mov esi,edi

	.repeat

		.if !salloc(strstart(edi))

			perror("To many targets..")
			exit(1)
		.endif
		mov target_string,eax

		ltoken(edi)
		.if !strrchr(edi, ':')

			perror(esi)
			exit(1)
		.endif

		mov BYTE PTR [eax],0
		strtrim(edi)
		mov target_name,expandsymbol(edi)
		mov esi,line_ptr
		xor eax,eax
		mov target_srcpath,eax
		mov target_command,eax

		mov [esi],al
		mov ah,[edi]
		mov [edi],al
		.if ah == '{'

			mov ebx,target_name
			.if strchr(ebx, '}')

				mov BYTE PTR [eax],0
				lea edx,[eax+1]
				push edx
				.if !salloc( addr [ebx+1] )

					perror("To many targets..")
					exit(1)
				.endif
				pop edx
				mov target_srcpath,eax
				strcpy(ebx, strstart(edx))
			.endif
		.endif

		.while getline()

			.break .if istarget(esi)
			strcat(edi, strstart(esi))
			strcat(edi, linefeed)
		.endw
		.if !eax

			mov [esi],al
		.endif

		.if BYTE PTR [edi]

			.if !salloc( edi )

				perror("To many targets..")
				exit(1)
			.endif
			mov target_command,eax
		.endif

		.if !malloc( SIZE S_TARGET )

			perror("To many targets..")
			exit(1)
		.endif

		mov ebx,eax
		mov eax,target_table
		mov [ebx].S_TARGET.t_next,eax
		mov [ebx].S_TARGET.t_prev,0
		.if eax

			mov [eax].S_TARGET.t_prev,ebx
		.endif

		mov eax,target_name
		mov [ebx].S_TARGET.t_target,eax
		mov eax,target_string
		mov [ebx].S_TARGET.t_string,eax
		mov eax,target_command
		mov [ebx].S_TARGET.t_command,eax
		mov eax,target_srcpath
		mov [ebx].S_TARGET.t_srcpath,eax
		inc target_count
		mov target_table,ebx

		.if !_stricmp(target_name, "all")

			mov [ebx].S_TARGET.t_type,_T_ALL
			.break
		.endif

		mov [ebx].S_TARGET.t_type,_T_TARGET
		mov eax,target_name
		.break .if BYTE PTR [eax] != '.'

		inc  eax
		push esi
		lea  esi,suffixes
		mov  edi,eax
		lodsd
		.while eax
			.break .if strstri(edi, eax)
			lodsd
		.endw
		pop esi

		.break .if !eax
		mov [ebx].S_TARGET.t_type,_T_METHOD

	.until	1

	.if istarget(esi)

		mov esp,ebp
		addtarget(esi)
	.endif
	ret

error_memory:
	perror( "To many targets.." )
	exit ( 1 )
syntax_error:
	perror( esi )
	exit ( 1 )
addtarget ENDP

;-------------------------------------------------------------------------------
; Build target
;-------------------------------------------------------------------------------

findtarget PROC USES esi edi ebx edx target:ptr sbyte
	expandsymbol( target )
	mov edi,eax
	mov esi,target_table
	mov cx,[edi]
	or  cx,2020h
sloop:
	test esi,esi
	jz  error
	mov ebx,esi
	mov eax,[esi].S_TARGET.t_target
	mov esi,[esi].S_TARGET.t_next
	mov dx,[eax]
	or  dx,2020h
	cmp dx,cx
	jne sloop
	_stricmp( eax, edi )
	jne sloop
	mov eax,ebx
toend:
	free(edi)
	test eax,eax
	ret
error:
	xor eax,eax
	jmp toend
findtarget ENDP

build_object PROC USES esi edi ebx object:ptr sbyte

local	srcname[_MAX_PATH]:BYTE
local	srcfile[_MAX_PATH]:BYTE
local	command[_MAX_PATH]:BYTE
local	p,q,r

	lea ebx,srcname
	lea edi,srcfile
	lea esi,extensions
	.if strext( strcpy( ebx, object ) )

		mov BYTE PTR [eax],0
	.endif
	lea ebx,suffixes
nextsuffix:
	mov eax,[ebx]
	test eax,eax
	jz  error_EBX
	mov p,eax
	add ebx,4
	lea esi,extensions
findsrcfile:
	lodsd
	test eax,eax
	jz nextsuffix
	mov q,eax

	findtarget( strcat( strcpy( edi, eax ), p ) )
	jz findsrcfile
	push eax
	strcat( strcpy( edi, addr srcname ), q )
	pop edx
	mov ecx,[edx].S_TARGET.t_srcpath
	.if ecx

		strcpy( edi, strfcat( addr command, ecx, edi ) )
	.endif
	push edx
	filexist(eax)
	pop edx
	dec eax
	jnz findsrcfile
	lea ebx,srcname

	mov eax,[edx].S_TARGET.t_command
	test eax,eax
	jz  error_EDI
	lea esi,command

	strxchg( strcpy( esi, eax ), "$*", ebx )
	strxchg( esi, "$<", edi )

	setfext( edi, suffixes )
	strxchg( esi, "$@", edi )

	expandsymbol( esi )
	mov esi,eax
	.if option_d

		printf( "%s\n", esi )
	.else
		.while	strchr( esi, 10 )

			lea ebx,[eax+1]
			mov BYTE PTR [eax],0
			.if !option_s

				printf( "\t%s\n", esi )
			.endif
			system( esi )
			mov BYTE PTR [ebx-1],10
			mov esi,ebx
		.endw
		.if !option_s

			printf( "\t%s\n", esi )
		.endif
		system( esi )
		dec eax
		jnz error_EDI
		cmp eax,errorlevel
		jnz error_EDI
	.endif
toend:
	ret
error_EDI:
	perror( edi )
	exit ( 1  )
error_EBX:
	perror( addr srcname )
	exit ( 1 )
build_object ENDP

opentemp PROC buffer:ptr sbyte, ext:ptr sbyte
  local t:SYSTEMTIME
	GetLocalTime( addr t )
	GetTickCount()
	movzx ecx,t.wMilliseconds
	add eax,ecx
	and eax,00FFFFFFh
	sprintf( buffer, "%s\\$%06X$.%s", envtemp, eax, ext )
	fopen( buffer, "wt+" )
	ret
opentemp ENDP

build_target PROC USES esi edi ebx target:ptr S_TARGET
  local base,
	target_path,
	target_name,
	target_file,
	target_command,
	target_string
	alloca( MAXTARGET )
	mov base,eax
	mov edi,eax
	mov esi,target
	expandsymbol( [esi].S_TARGET.t_string )
	mov esi,eax
	mov target_string,eax
@@:
	lodsb
	stosb
	test al,al
	jz  @F
	cmp al,':'
	jne @B
	cmp BYTE PTR [esi],'\'
	je  @B
@@:
	mov BYTE PTR [edi],0
	mov edi,base
	salloc( edi )
	mov target_path,eax
	salloc( eax )
	mov target_name,eax
	mov ebx,eax
	strrchr( eax, ':' )
	jz  @F
	mov BYTE PTR [eax],0
@@:
	strtrim( ebx )
	salloc( strfn( ebx ) )
	mov target_file,eax
	strext( eax )
	jz  do_objects
	mov BYTE PTR [eax],0

do_objects:
	mov ax,[esi-1]
	test al,al
	jz parse_command
	test ah,ah
	jz parse_command
@@:
	lodsb
	cmp al,' '
	je  @B
	cmp al,9
	je  @B
@@:
	stosb
	test al,al
	jz @F
	cmp al,' '
	je  @F
	cmp al,9
	je  @F
	lodsb
	jmp @B
@@:
	mov BYTE PTR [edi],0
	mov edi,base
	findtarget( edi )
	jnz do_target
	build_object( edi )
	jmp do_objects

do_target:
	add esp,MAXTARGET
	build_target( eax )
	sub esp,MAXTARGET
	test eax,eax
	jz  do_objects
	jmp toend

parse_command:

	free(target_string)
	mov esi,target
	mov eax,[esi].S_TARGET.t_command
	test eax,eax		; all: <target1> [<target2>] ...
	jz toend		;  <no command>


	mov esi,expandsymbol(eax)
	mov edi,strcpy(base, eax)
	free(esi)
	strxchg(edi, "$@", target_name)
	strxchg(edi, "$*", target_file)

	mov esi,edi
	strstr(esi, "@<<")
	jz no_responsefile

	lea ebx,[eax+3]
	mov BYTE PTR [ebx-2],0
	strchr(ebx, 10)
	jz  error

	lea ebx,[eax+1]
	strstr( ebx, "<<" )
	jz  no_responsefile

	mov BYTE PTR [eax],0
	lea edi,[eax+2]
	opentemp( addr responsefile, "$$$" )
	jz  error

	push eax
	fprintf( eax, ebx )
	call fclose

	.if option_d

		printf( "%s:\n%s\n", addr responsefile, ebx )
	.endif
	strcat(esi, addr responsefile)
	strchr(edi, 10)
	jz no_responsefile
	strcat(esi, eax)

no_responsefile:

	.if option_d

		printf( "%s\n", esi )
		xor eax,eax
	.else
		.if !option_s

			mov edi,esi
			printf( "%s\n", target_path )

			.while strchr( edi, 10 )

				lea ebx,[eax+1]
				mov BYTE PTR [eax],0
				printf( "\t%s\n", edi )
				mov BYTE PTR [ebx-1],10
				mov edi,ebx
			.endw
			printf( "\t%s\n", edi )
		.endif

		xor edi,edi
		.if opentemp( addr commandfile, "cmd" )

			push eax
			fprintf( eax, "@echo off\n%s\n", esi )
			call fclose
			system( addr commandfile )
			dec eax
			add edi,eax
			add edi,errorlevel
		.endif

		;remove( addr responsefile )
		;remove( addr commandfile )
		test edi,edi
		jnz error
	.endif
toend:
	ret
error:
	perror( "Make execution terminated" )
	exit(1)
build_target ENDP

;-------------------------------------------------------------------------------
; MAKE
;-------------------------------------------------------------------------------

addtargetarg PROC target:ptr sbyte
	.if strlen( target )

		lea eax,[eax+1+SIZE S_ARGS]
		.if malloc(eax)
			mov edx,eax
			strcpy( addr [edx+SIZE S_ARGS], target )
			mov [edx].S_ARGS.a_name,eax
			xor eax,eax
			mov [edx].S_ARGS.a_next,eax
			mov ecx,target_args
			.if !ecx
				mov target_args,edx
			.else
				.while eax != [ecx].S_ARGS.a_next
					mov ecx,[ecx].S_ARGS.a_next
				.endw
				mov [ecx].S_ARGS.a_next,edx
			.endif
		.endif
	.endif
	ret
addtargetarg ENDP

make	PROC USES esi edi ebx file:ptr sbyte, target:ptr sbyte

	.if !fopen(file, "rt")

		perror(file)
		exit(1)
	.endif
	mov line_fp,eax

	.while	getline()

		mov esi,eax
		.break .if !istarget(esi)
		addtarget(esi)
	.endw

	mov	esi,target_args
	.if    !esi

		.if !target_count

			perror("Missing target..")
			exit(1)
		.endif

		xor eax,eax
		xor ebx,ebx
		xor edi,edi
		.for ecx = target_table: [ecx].S_TARGET.t_next: ecx = [ecx].S_TARGET.t_next
		.endf
		.for : ecx && !eax: ecx = [ecx].S_TARGET.t_prev

			mov edi,ecx
			mov eax,[ecx].S_TARGET.t_type
			.break .if eax == _T_ALL

			.if eax == _T_METHOD
				mov ebx,ecx
				xor eax,eax
			.else
				mov eax,[ecx].S_TARGET.t_command
			.endif
		.endf
		.if  !eax && !ebx

			perror([edi].S_TARGET.t_target)
			exit(1)
		.endif
		addtargetarg([edi].S_TARGET.t_target)
		mov esi,target_args
	.endif

	.for : esi: esi = [esi].S_ARGS.a_next

		.break .if !findtarget([esi].S_ARGS.a_name)
		build_target(eax)
	.endf
	ret

make	ENDP

;-------------------------------------------------------------------------------
; MAIN
;-------------------------------------------------------------------------------

addmakefile PROC file:ptr sbyte
	.if strlen( file )
		lea eax,[eax+1+SIZE S_ARGS]
		.if malloc(eax)
			mov edx,eax
			strcpy( addr [edx+SIZE S_ARGS], file )
			mov [edx].S_ARGS.a_name,eax
			xor eax,eax
			mov [edx].S_ARGS.a_next,eax
			mov ecx,file_args
			.if !ecx
				mov file_args,edx
			.else
				.while eax != [ecx].S_ARGS.a_next
					mov ecx,[ecx].S_ARGS.a_next
				.endw
				mov [ecx].S_ARGS.a_next,edx
			.endif
		.endif
	.endif
	ret
addmakefile ENDP

main	PROC C

	malloc( MAXSYMBOLS*4*2 )
	mov	symbol_table,eax
	expenviron( addr cmdexe )
	mov	__pCommandCom,eax

	.if !getenv( "AsmcDir" )
		getenv( "DZ" )
	.endif
	.if eax
		strcpy(addr includepath, eax)
		strcat(eax, "\\lib" )
	.endif

	mov edi,__argc
	mov esi,__argv
	.while	edi > 1
		dec edi
		add esi,4
		mov edx,[esi]
		mov eax,[edx]
		.switch al
		  .case '/'
		  .case '-'
			.switch ah
			  .case 'a': inc option_a: .endc
			  .case 'd': inc option_d: .endc
			  .case 'h': inc option_h: .endc
			  .case 's': inc option_s: .endc
			  .case 'I'
				strcpy(addr includepath, addr [edx+2])
				.endc

			  .case 'f'
				add edx,2
				.if eax & 00FF0000h
					addmakefile( edx )
					.endc
				.endif
				add esi,4
				mov edx,[esi]
				dec edi
				.if !ZERO?
					addmakefile( edx )
					.endc
				.endif
			  .default
			   error_args:
				printf( addr cpinfo )
				printf( addr cpusage )
				xor eax,eax
				jmp toend
			.endsw
			.endc
		  .default
			.if strchr( edx, '=' )
				mov BYTE PTR [eax],0
				inc eax
				addsymbol(edx, eax)
			.else
				addtargetarg(edx)
			.endif
		.endsw
	.endw

	.if !option_h && !option_s
		printf( addr cpinfo )
	.endif

	mov esi,file_args
	.if !esi
		addmakefile( "makefile" )
		mov esi,file_args
	.endif

	.while	esi
		.break .if make( [esi].S_ARGS.a_name, target_args )
		mov esi,[esi].S_ARGS.a_next
	.endw
toend:
	ret
main	ENDP

	END
