include io.inc
include stdio.inc
include stdlib.inc
include string.inc
include ctype.inc
include errno.inc
include direct.inc
include alloc.inc
include signal.inc
include crtl.inc

include asmc.inc

PUBLIC	argv0
PUBLIC	cp_logo
PUBLIC	szCVCompiler

AssembleModule	PROTO :DWORD
close_files	PROTO

.data

cp_logo label byte
%	db "Asmc Macro Assembler Version ",ASMC_VERSSTR,'J-&@Date', 10
	db "Portions Copyright (c) 1992-2002 Sybase, Inc. All Rights Reserved.",10,10,0

cp_usage label byte
	db "USAGE: %s [ options ] filelist",10
	db "Use option /? for more info",10,0

cp_options label byte

db "         %s [ /options ] filelist",10
db 10
db "/<0|1|..|10>[p] Set CPU: 0=8086 (default), 1=80186, 2=80286, 3=80386, 4=80486,",10
db " 5=Pentium,6=PPro,7=P2,8=P3,9=P4,10=x86-64; <p> allows privileged instructions",10
db "/bin Generate plain binary file            /Sf Generate first pass listing",10
db "/Cs C stack: push USER regs first          /Sg Display generated code in listing",10
db "/coff Generate COFF format object file     /Sn Suppress symbol-table listing",10
db "/C<p|u|x> Set OPTION CASEMAP               /swc C .SWITCH (default)",10
db "/D<name>[=text] Define text macro          /swn No table in .SWITCH (default)",10
db "/e<number> Set error limit number          /swp Pascal .SWITCH (auto.break)",10
db "/elf Generate 32-bit ELF object file       /swr Use reg [R|E]AX in switch code",10
db "/elf64 Generate 64-bit ELF object file     /swt Use table in .SWITCH",10
db "/EP Output preprocessed listing to stdout  /Sx List false conditionals",10
db "/eq Don't display error messages           /w Same as /W0 /WX",10
db "/Fd[file] Write import definition file     /W<number> Set warning level",10
db "/Fi<file> Force <file> to be included      /win64 Generate 64-bit COFF object",10
db "/Fl[file] Generate listing                 /ws Store quoted strings as unicode",10
db "/Fo<file> Name object file                 /WX Treat all warnings as errors",10
db "/Fw<file> Set errors file name             /X Ignore INCLUDE environment path",10
db "/FPi Generate 80x87 emulator encoding      /Xc Disable ASMC extensions",10
db "/FPi87 80x87 instructions (default)        /zcw No decoration for C symbols",10
db "/fpc Disallow floating-point instructions  /Zd Add line number debug info",10
db "/fp<n> Set FPU: 0=8087, 2=80287, 3=80387   /Zf Make all symbols public",10
db "/G<c|d|z> Use Pascal, C, or Stdcall calls  /zf<0|1> Set FASTCALL type: MS/OW",10
db "/I<name> Add include path                  /Zg Generate code to match Masm",10
db "/m<t|s|c|m|l|h|f> Set memory model         /Zi[0|1|2|3] Add symbolic debug info",10
db "/mz Generate DOS MZ binary file            /zlc No OMF records of data in code",10
db "/nc<name> Set class name of code segment   /zld No OMF records of far call",10
db "/nd<name> Set name of data segment         /zl<f|p|s> Suppress items in COFF",10
db "/nm<name> Set name of module               /Zm Enable MASM 5.10 compatibility",10
db "/nt<name> Set name of text segment         /Zne Disable non Masm extensions",10
db "/pe Generate PE binary file, 32/64-bit     /Zp[n] Set structure alignment",10
db "/q, /nologo Suppress copyright message     /Zs Perform syntax check only",10
db "/r Recurse subdirectories                  /zt<0|1|2> Set STDCALL decoration",10
db "/Sa Maximize source listing                /Zv8 Enable Masm v8+ PROC visibility",10
db "/safeseh Assert exception handlers         /zze No export symbol decoration",10
db "/zzs Store name of start address",10
db 0

szCVCompiler	db "ASMC v",ASMC_VERSSTR,0

	ALIGN	4

banner_printed	dd 0

Options		global_options <	\
		0,			\ ; .quiet
		0,			\ ; .line_numbers
		0,			\ ; .debug_symbols
		0,			\ ; .debug_ext
		FPO_NO_EMULATION,	\ ; .floating_point
		50,			\ ; .error_limit
		0,			\ ; .no_error_disp
		2,			\ ; .warning_level
		0,			\ ; .warning_error
		0,			\ ; .process_subdir
		<0,0,0,0,0,0,0,0,0>,	\ ; .names OPTN_LAST dup(0)
		<0,0,0>,		\ ; .queues OPTQ_LAST dup(0)
		0,			\ ; .no_comment_in_code_rec
		0,			\ ; .no_opt_farcall
		0,			\ ; .no_file_entry
		0,			\ ; .no_static_procs
		0,			\ ; .no_section_aux_entry
		0,			\ ; .no_cdecl_decoration
		STDCALL_FULL,		\ ; .stdcall_decoration
		0,			\ ; .no_export_decoration
		0,			\ ; .entry_decorated
		0,			\ ; .write_listing
		0,			\ ; .write_impdef
		0,			\ ; .case_sensitive
		0,			\ ; .convert_uppercase
		0,			\ ; .preprocessor_stdout
		0,			\ ; .masm51_compat
		0,			\ ; .strict_masm_compat
		0,			\ ; .masm_compat_gencode
		0,			\ ; .masm8_proc_visibility
		0,			\ ; .listif
		0,			\ ; .list_generated_code
		LM_LISTMACRO,		\ ; .list_macro
		0,			\ ; .do_symbol_listing
		0,			\ ; .first_pass_listing
		0,			\ ; .all_symbols_public
		0,			\ ; .safeseh
		0,			\ ; .ignore_include
		OFORMAT_OMF,		\ ; .output_format
		SFORMAT_NONE,		\ ; .sub_format
		0,			\ ; .fieldalign
		LANG_NONE,		\ ; .langtype
		MODEL_NONE,		\ ; .modelt
		P_86,			\ ; .cpu
		FCT_MSC,		\ ; .fctype
		0,			\ ; .syntax_check_only
		1,			\ ; .asmc_syntax
		0,			\ ; .c_stack_frame
		0,			\ ; .hll_switch
		0,			\ ; .loopalign
		0,			\ ; .casealign
		0			\ ; .wstring
		>

DefaultDir	dd NUM_FILE_TYPES dup(0)

cp_ml		db "ML",0
cp_jwasm	db "JWASM",0
cp_asmc		db "ASMC",0

	ALIGN	4

argv0		dd cp_asmc
argc		dd 0
argv		dd 0

	.code

	OPTION PROCALIGN:4

write_logo PROC
	xor	eax,eax
	.if	eax == banner_printed
		inc	banner_printed
		printf( addr cp_logo )
		mov	eax,4
	.endif
	ret
write_logo ENDP

getnextarg:
	xor	eax,eax
	.if	eax != argc
		dec	argc
		mov	eax,argv
		add	argv,4
		mov	eax,[eax]
	.endif
	ret

getfilearg:			; -Fo<file> or -Fo <file>
	.if	BYTE PTR [eax] == 0
		mov	ecx,eax
		.if	!getnextarg()
			mov eax,ecx
		.endif
	.elseif BYTE PTR [eax] == '='
		inc	eax
	.endif
	.if	BYTE PTR [eax] == 0
		asmerr( 1006, esi )
		xor	eax,eax
	.endif
	ret

GetNumber PROC
	xor	eax,eax
	lea	edx,[esi+2]	; -x[=]<number>
	.repeat
		mov	al,[edx]
		inc	edx
		test	al,al
		jz	toend
	.until	__ctype[eax+1] & _DIGIT
	dec	edx
	atol  ( edx )
	test	eax,eax
toend:
	ret
GetNumber ENDP

; queue a text macro, include path or "forced" include files.
; this is called for cmdline options -D, -I and -Fi

queue_item PROC USES esi i, string

	mov	esi,string
	.while	BYTE PTR [esi] == '"'

		.if strrchr( strcpy( esi, addr [esi+1] ), '"' )

			mov BYTE PTR [eax],0
		.endif
	.endw

	strlen( esi )
	add	eax,sizeof( qitem )
	MemAlloc( eax )
	mov	[eax].qitem.next,0
	mov	edx,eax
	strcpy( addr [edx].qitem.value, esi )

	mov	eax,i
	mov	ecx,Options.queues[eax*4]
	.if	ecx

		.while	[ecx].qitem.next

			mov ecx,[ecx].qitem.next
		.endw
		mov	[ecx].qitem.next,edx
	.else

		mov	Options.queues[eax*4],edx
	.endif

	ret

queue_item ENDP

get_fname PROC USES esi edi ebx i, string

  local fname[_MAX_PATH]:BYTE

	mov	ebx,string
	.if	BYTE PTR [ebx] == '='

		inc	ebx
	.endif
	strfn ( ebx )
	mov	edi,i
	mov	esi,eax
	;
	; If name's ending with a '\' (or '/' in Unix), it's supposed
	; to be a directory name only.
	;
	.if	BYTE PTR [eax] == 0

		.if edi < NUM_FILE_TYPES && BYTE PTR [ebx]

			mov	eax,DefaultDir[edi*4]
			.if	eax

				free( eax )
			.endif
			salloc( ebx )
			mov	DefaultDir[edi*4],eax
		.endif
	.else

		mov	fname,0
		.if	esi == ebx && edi < NUM_FILE_TYPES && DefaultDir[edi*4]

			strcpy( addr fname, DefaultDir[edi*4] )
		.endif
		strcat( addr fname, ebx )
		free  ( Options.names[edi*4] )
		salloc( addr fname )
		mov	Options.names[edi*4],eax
	.endif
	ret
get_fname ENDP

set_option_n_name PROC idx, string

	mov	edx,string
	movzx	eax,BYTE PTR [edx]
	.if	eax != '.'

		islabel( eax )
	.endif
	.if	eax

		mov	eax,idx
		free  ( Options.names[eax*4] )
		salloc( edx )
		mov	edx,idx
		mov	Options.names[edx*4],eax
	.else

		asmerr( 1006, esi )
	.endif
	ret

set_option_n_name ENDP

	OPTION	CSTACK:ON

ParseCmdline PROC USES esi edi ebx numargs

  local handle, buffer, bsize

	lea	edi,Options
	ASSUME	edi:PTR global_options

	xor	esi,esi
	.while	esi < NUM_FILE_TYPES

		mov	eax,[edi].names[esi*4]
		mov	[edi].names[esi*4],0
		inc	esi
		free  ( eax )
	.endw

	.while	getnextarg()

		mov	esi,eax
		movzx	eax,BYTE PTR [esi]

		.switch eax

		  .case '/'
		  .case '-'
			mov	eax,[esi+1]
			.switch al
			  .case 'D'	; /D<name>[=text]
				lea	eax,[esi+2]
				.if	getfilearg()

					queue_item( OPTQ_MACRO, eax )
				.endif
				.continue
			  .case 'I'	; /I<name>
				lea	eax,[esi+2]
				.if	getfilearg()

					queue_item( OPTQ_INCPATH, eax )
				.endif
				.continue
			.endsw

			;
			; array for options -0..10
			;
			.data
			cpuoption dd P_86, P_186, P_286, P_386
				  dd P_486, P_586, P_686, P_686 or P_MMX
				  dd P_686 or P_MMX or P_SSE1
				  dd P_686 or P_MMX or P_SSE1 or P_SSE2
				  dd P_64
			.code

			.if	!ah

				movzx	eax,al
			.elseif !( eax & 00FF0000h )

				movzx	eax,ax
			.endif

			.switch eax

			  .case 'c'	; /c
				.endc

			  .case 'ffoc'	; /coff
				mov	[edi].output_format,OFORMAT_COFF
				mov	[edi].sub_format,SFORMAT_NONE
				.endc

			  .case 'PE'	; /EP
				mov	[edi].preprocessor_stdout,1

			  .case 'q'	; /q
				mov	[edi].quiet,1

			  .case 'olon'	; /nologo
				mov	banner_printed,1
				.endc

			  .case 'nib'	; /bin
				mov	[edi].output_format,OFORMAT_BIN
				mov	[edi].sub_format,SFORMAT_NONE
				.endc

			  .case 'pC'	; /Cp
				mov	[edi].case_sensitive,1
				mov	[edi].convert_uppercase,0
				.endc

			  .case 'sC'	; /Cs
				mov	[edi].c_stack_frame,1
				.endc

			  .case 'uC'	; /Cu
				mov	[edi].case_sensitive,0
				mov	[edi].convert_uppercase,1
				.endc

			  .case 'xC'	; /Cx
				mov	[edi].case_sensitive,0
				mov	[edi].convert_uppercase,0
				.endc

			  .case 'qe'	; /eq
				mov	[edi].no_error_disp,1
				.endc

			  .case '6fle'	; /elf64
				mov	[edi].output_format,OFORMAT_ELF
				mov	[edi].sub_format,SFORMAT_64BIT
				.endc

			  .case 'fle'	; /elf
				mov	[edi].output_format,OFORMAT_ELF
				mov	[edi].sub_format,SFORMAT_NONE
				.endc

			  .case '8iPF'	; /FPi87
				mov	[edi].floating_point,FPO_NO_EMULATION
				.endc

			  .case 'iPF'	; /Fpi
				mov	[edi].floating_point,FPO_EMULATION
				.endc

			  .case '0pf'	; /fp0
				mov	[edi].cpu,P_87
				.endc

			  .case '2pf'	; /fp2
				mov	[edi].cpu,P_287
				.endc

			  .case '3pf'	; /fp3
				mov	[edi].cpu,P_387
				.endc

			  .case 'cpf'	; /fpc
				mov	[edi].cpu,P_NO87
				.endc

			  .case 'cg'	; /gc
				mov	[edi].langtype,LANG_PASCAL
				.endc

			  .case 'dg'	; /gd
				mov	[edi].langtype,LANG_C
				.endc

			  .case 'rg'	; /gr
				mov	[edi].langtype,LANG_FASTCALL
				.endc

			  .case 'zg'	; /gz
				mov	[edi].langtype,LANG_STDCALL
				.endc

			  .case '?'
			  .case 'h'
				call	write_logo
				printf( addr cp_options, argv0 )
				exit  ( 1 )

			  .case 'zm'	; /mz
				mov	[edi].output_format,OFORMAT_BIN
				mov	[edi].sub_format,SFORMAT_MZ
				.endc

			  .case 'cm'	; /mc
				mov	[edi]._model,MODEL_COMPACT
				.endc

			  .case 'fm'	; /mf
				mov	[edi]._model,MODEL_FLAT
				.endc

			  .case 'hm'	; /mh
				mov	[edi]._model,MODEL_HUGE
				.endc

			  .case 'lm'	; /ml
				mov	[edi]._model,MODEL_LARGE
				.endc

			  .case 'mm'	; /mm
				mov	[edi]._model,MODEL_MEDIUM
				.endc

			  .case 'sm'	; /ms
				mov	[edi]._model,MODEL_SMALL
				.endc

			  .case 'tm'	; /mt
				mov	[edi]._model,MODEL_TINY
				.endc

			  .case 'fmo'	; /omf
				mov	[edi].output_format,OFORMAT_OMF
				mov	[edi].sub_format,SFORMAT_NONE
				.endc

			  .case 'ep'	; /pe
				mov	[edi].output_format,OFORMAT_BIN
				mov	[edi].sub_format,SFORMAT_PE
				.endc

			  .case 'r'	; /r
				mov	[edi].process_subdir,1
				.endc

			  .case 'aS'	; /Sa
				.endc

			  .case 'fS'	; /Sf
				mov	[edi].first_pass_listing,1
				.endc

			  .case 'gS'	; /Sg
				mov	[edi].list_generated_code,1
				.endc

			  .case 'nS'	; /Sn
				mov	[edi].no_symbol_listing,1
				.endc

			  .case 'xS'	; /Sx
				mov	[edi].listif,1
				.endc

			  .case 'pws'	; /swp
				or	[edi].hll_switch,SWITCH_PASCAL
				.endc

			  .case 'cws'	; /swc
				and	[edi].hll_switch,NOT SWITCH_PASCAL
				.endc

			  .case 'rws'	; /swr
				or	[edi].hll_switch,SWITCH_REGAX
				.endc

			  .case 'nws'	; /swn
				and	[edi].hll_switch,NOT SWITCH_TABLE
				.endc

			  .case 'tws'	; /swt
				or	[edi].hll_switch,SWITCH_TABLE
				.endc

			  .case 'efas'	; /safeseh
				mov	[edi].safeseh,1
				.endc

			  .case 'w'	; /w
				mov	[edi].warning_level,0
				.endc

			  .case 'sw'	; /ws
				mov	[edi].wstring,1
				.endc

			  .case 'XW'	; /WX
				mov	[edi].warning_error,1
				.endc

			  .case '6niw'	; /win64
				mov	[edi].output_format,OFORMAT_COFF
				mov	[edi].sub_format,SFORMAT_64BIT
				.endc

			  .case 'X'	; /X
				mov	[edi].ignore_include,1
				.endc

			  .case 'cX'	; /Xc
				mov	[edi].asmc_syntax,0
				.endc

			  .case 'mcz'	; /zcm
				mov	[edi].no_cdecl_decoration,0
				.endc

			  .case 'wcz'	; /zcw
				mov	[edi].no_cdecl_decoration,1
				.endc

			  .case 'fZ'	; /Zf
				mov	[edi].all_symbols_public,1
				.endc

			  .case '0fz'	; /zf0
				mov	[edi].fctype,0
				.endc

			  .case '1fz'	; /zf1
				mov	[edi].fctype,1
				.endc

			  .case 'gZ'	; /Zg
				mov	[edi].masm_compat_gencode,1
				.endc

			  .case 'dZ'	; /Zd
				mov	[edi].line_numbers,1
				.endc

			  .case 'clz'	; /zlc
				mov	[edi].no_comment_in_code_rec,1
				.endc

			  .case 'dlz'	; /zld
				mov	[edi].no_opt_farcall,1
				.endc

			  .case 'flz'	; /zlf
				mov	[edi].no_file_entry,1
				.endc

			  .case 'piz'	; /zip
				mov	[edi].no_static_procs,1
				.endc

			  .case 'slz'	; /zls
				mov [edi].no_section_aux_entry,1
				.endc

			  .case 'mZ'	; /Zm
				mov	 [edi].masm51_compat,1
			  .case 'enZ'	; /Zne
				mov	[edi].strict_masm_compat,1
				mov	[edi].asmc_syntax,0
				.endc

			  .case 'sZ'	; /Zs
				mov	[edi].syntax_check_only,1
				.endc

			  .case '0tz'	; /zt0
				mov	[edi].stdcall_decoration,0
				.endc
			  .case '1tz'	; /zt1
				mov	[edi].stdcall_decoration,1
				.endc
			  .case '2tz'	; /zt2
				mov	[edi].stdcall_decoration,2
				.endc

			  .case '8vZ'	; /Zv8
				mov	[edi].masm8_proc_visibility,1
				.endc

			  .case 'ezz'	; /zze
				mov	[edi].no_export_decoration,1
				.endc

			  .case 'szz'	; /zzs
				mov	[edi].entry_decorated,1
				.endc

			  .case 'p01'		; /10p
				mov	ah,'0'+'p'
			  .case '01'		; /10
				sub	ah,'0'
				mov	al,'9'+1

			  .case 'p0' .. 'p9'	; /0p../9p
			  .case	 '0' ..	 '9'	; /0../9

				sub	al,'0'
				movzx	ecx,al
				mov	ecx,cpuoption[ecx*4]

				and	[edi].cpu,NOT ( P_CPU_MASK or P_EXT_MASK or P_PM )
				or	[edi].cpu,ecx
				.if	ah == 'p' && [edi].cpu >= P_286

					or [edi].cpu,P_PM
				.endif
				.endc

			  .default

				movzx	ecx,ah
				movzx	eax,al

				.switch eax
					;
					; /e<number>
					;
				  .case 'e'
					call	GetNumber
					mov	[edi].error_limit,eax
					.endc
					;
					; /F
					;
				  .case 'F'

					lea	eax,[esi+3]

					.switch ecx

					  .case 'd'	; /Fd
						mov	[edi].write_impdef,1
						get_fname( OPTN_LNKDEF_FN, eax )
						.endc

					  .case 'i'	; /Fi
						.if	getfilearg()

							queue_item( OPTQ_FINCLUDE, eax )
						.endif
						.endc

					  .case 'l'	; /Fl
						mov	[edi].write_listing,1
						get_fname( OPTN_LST_FN, eax )
						.endc

					  .case 'o'	; /Fo
						.if	getfilearg()

							get_fname( OPTN_OBJ_FN, eax )
						.endif
						.endc
					.endsw
					.endc
					;
					; /n
					;
				  .case 'n'
					lea	eax,[esi+3]
					.switch ecx
					  .case 'c'	; /nc<name>
						set_option_n_name( OPTN_CODE_CLASS, eax )
						.endc
					  .case 'd'	; /nd<name>
						set_option_n_name( OPTN_DATA_SEG, eax )
						.endc
					  .case 'm'	; /nm<name>
						set_option_n_name( OPTN_MODULE_NAME, eax )
						.endc
					  .case 't'	; /nt<name>
						set_option_n_name( OPTN_TEXT_SEG, eax )
						.endc
					.endsw
					.endc
					;
					; /W<number>
					;
				  .case 'W'
					movzx	eax,BYTE PTR [esi+2]
					.if	eax < '0'

						asmerr( 8000, esi )
					.elseif eax > '3'

						asmerr( 4008, esi )
					.else

						sub	eax,'0'
						mov	[edi].warning_level,al
					.endif
					.endc
					;
					; /Z
					;
				  .case 'Z'
					.if	ecx == 'p'
						;
						; /Zp[n]
						;
						call	GetNumber
						jz	error
						xor	ecx,ecx
						mov	edx,eax

						.repeat
							mov	eax,1
							shl	eax,cl
							inc	ecx
							cmp	eax,MAX_STRUCT_ALIGN
							ja	error
						.until	eax == edx

						dec	ecx
						mov	[edi].fieldalign,cl
						.endc
					.endif

					.if	ecx == 'i'
						;
						; /Zi[0|1|2|3]
						;
						mov	[edi].debug_symbols,1;CV_SIGNATURE
						mov	[edi].debug_ext,CVEX_NORMAL
						call	GetNumber
						.if	!ZERO?
							cmp	eax,CVEX_MAX
							ja	error
							mov	[edi].debug_ext,al
						.endif
					.endif
					;
					; [/Zd]
					;
					mov	[edi].line_numbers,1
					.endc

				  .default
					jmp	error
				.endsw
			.endsw

			mov	eax,numargs
			inc	DWORD PTR [eax]
			.endc
			;
			; @<file>
			;
		  .case '@'
			mov	handle,osopen( addr [esi+1], _A_NORMAL, M_RDONLY, A_OPEN )
			cmp	eax,-1
			je	error
			_filelength( eax )
			inc	eax
			mov	bsize,eax
			alloca( eax )
			mov	buffer,eax
			osread( handle, eax, bsize )
			add	eax,buffer
			mov	BYTE PTR [eax],0
			_close( handle )
			mov	ebx,argv
			sub	ebx,_argv
			__setargv( addr argc, argv, buffer )
			mov	eax,_argv
			add	eax,ebx
			mov	argv,eax
			.endc

		  .default
			mov	eax,numargs
			inc	DWORD PTR [eax]
			salloc( esi )
			mov	Options.names[ASM*4],eax
			.break
		.endsw
	.endw

	ASSUME	edi:NOTHING
toend:
	ret
error:
	asmerr( 1006, esi )
	jmp	toend
ParseCmdline ENDP

CmdlineFini PROC USES esi edi ebx

	xor	esi,esi
	xor	ebx,ebx

	.while	esi < NUM_FILE_TYPES

		mov	eax,DefaultDir[esi*4]
		mov	DefaultDir[esi*4],ebx
		free  ( eax )
		mov	eax,Options.names[esi*4]
		mov	Options.names[esi*4],ebx
		inc	esi
	.endw

	xor	esi,esi
	.while	esi < OPTQ_LAST

		mov	edi,Options.queues[esi*4]
		.while	edi

			mov	eax,[edi].qitem.next
			free  ( edi )
			mov	edi,eax
		.endw
		mov	Options.queues[esi*4],ebx
		inc	esi
	.endw
	ret

CmdlineFini ENDP

AssembleSubdir PROC USES esi edi ebx directory, wild

  local path[_MAX_PATH]:BYTE, ff:WIN32_FIND_DATA, h, rc

	lea	esi,path
	lea	edi,ff
	lea	ebx,ff.cFileName
	mov	rc,0

	.if FindFirstFile( strfcat( esi, directory, wild ), edi ) != -1

		mov h,eax
		.repeat
			.if !(BYTE PTR ff.dwFileAttributes & _A_SUBDIR)

				mov rc,AssembleModule( strfcat( esi, directory, ebx ) )
			.endif

		.until !FindNextFile( h, edi )

		FindClose( h )
	.endif

	.if	Options.process_subdir

		.if	FindFirstFile( strfcat( esi, directory, "*.*" ), edi ) != -1

			mov	h,eax
			.repeat
				mov	eax,[ebx]
				and	eax,00FFFFFFh
				.if	ff.dwFileAttributes & _A_SUBDIR && ax != '.' && eax != '..'

					.if	AssembleSubdir( strfcat( esi, directory, ebx ), wild )

						mov	rc,eax
					.endif
				.endif
				FindNextFile( h, edi )
			.until !eax
			FindClose( h )
		.endif
	.endif
	mov	eax,rc
	ret

AssembleSubdir ENDP

GeneralFailure PROC signo

	mov	eax,signo
	.if	eax != SIGTERM

		mov	eax,pCurrentException
		PrintContext(
			[eax].EXCEPTION_POINTERS.ContextRecord,
			[eax].EXCEPTION_POINTERS.ExceptionRecord )
		asmerr( 1901 )
	.endif
	close_files()
	exit( 1 )
	ret

GeneralFailure ENDP

main PROC C USES esi edi ebx

  local rc, numArgs, numFiles, ff:WIN32_FIND_DATA, h

ifndef	DEBUG
	mov	ebx,GeneralFailure
;	signal( SIGINT,	  ebx ) ; interrupt
	signal( SIGILL,	  ebx ) ; illegal instruction - invalid function image
	signal( SIGFPE,	  ebx ) ; floating point exception
	signal( SIGSEGV,  ebx ) ; segment violation
	signal( SIGTERM,  ebx ) ; Software termination signal from kill
;	signal( SIGABRT,  ebx ) ; abnormal termination triggered by abort call
endif

	xor	eax,eax
	mov	rc,eax
	mov	numArgs,eax
	mov	numFiles,eax
	mov	eax,_argc
	dec	eax
	mov	argc,eax
	mov	eax,_argv
	mov	ecx,[eax]
	add	eax,4
	mov	argv,eax
	strfn ( ecx )
	mov	ecx,[eax+4]
	mov	eax,[eax]
	or	eax,20202020h
	or	ecx,20202020h

	.if	eax == 'e.lm'

		mov	argv0,offset cp_ml
		mov	Options.strict_masm_compat,1
		mov	Options.asmc_syntax,0
	.elseif eax == 'sawj' && ecx == 'xe.m'

		mov	argv0,offset cp_jwasm
		mov	Options.asmc_syntax,0
	.endif

	.if	getenv( argv0 ) ; v2.21 -- getenv() error..

		__setargv( addr argc, argv, eax )
	.endif

	.while	ParseCmdline( addr numArgs )

		inc	numFiles
		call	write_logo
		lea	edi,ff.cFileName
		mov	esi,Options.names[ASM*4]

		.if	!Options.process_subdir
			.if	FindFirstFile( esi, addr ff ) == -1
				asmerr( 1000, esi )
				.break
			.endif
			FindClose( eax )
		.endif
		strchr( strcpy( edi, esi ), '*' )
		mov	edx,eax
		strchr( edi, '?' )
		.if	eax || edx
			.if	strfn( edi ) > edi
				dec eax
			.endif
			mov	BYTE PTR [eax],0
			AssembleSubdir( edi, strfn( esi ) )
		.else
			AssembleModule( edi )
		.endif
		mov	rc,eax
	.endw

	CmdlineFini()
	.if	!numArgs
		call	write_logo
		printf( addr cp_usage, argv0 )
	.elseif !numFiles
		asmerr( 1017 )
	.endif
	mov	eax,1
	sub	eax,rc
	ret
main	ENDP

	END

