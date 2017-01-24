; MAIN.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include stdio.inc
include stdlib.inc
include alloc.inc
include io.inc
include string.inc
include process.inc
include signal.inc
include cfini.inc

doszip_init	PROTO :DWORD
doszip_open	PROTO
doszip_modal	PROTO
doszip_close	PROTO
;
; NTFS - New Technology File System
;
; Maximum number of files on disk: 4,294,967,295
; Maximum number of files in a single folder: 4,294,967,295
;
	.data

DZ_Title	dd cp_title
cp_title	db "Doszip Commander",0

copyright	db 'The Doszip Commander Version ',DOSZIP_VSTRING,', '
		db 'Copyright (C) 2016 Doszip Developers',10,10,0

cp_usage	db 'Command line switches',10
		db ' The following switches may be used in the command line:',10
		db 10
		db '  -N<file_count> - Maximum number of files in each panel',10
		db '	 default is 5000.',10
		db 10
		db '  -C<config_path> - Read/Write setup from/to <config_path>',10
		db 10
		db '  DZ <filename> command starts DZ and forces it to show <filename>',10
		db 'contents if it is an archive or show folder contents if <filename>',10
		db 'is a folder.',10,0

	.code

ifdef __SIGNAL__

GeneralFailure PROC signo

	mov	ecx,signo
	mov	eax,1
	.if	ecx == SIGTERM || ecx == SIGABRT

		doszip_close()
		.if	cflag & _C_DELHISTORY
			historyremove()
		.endif
		tcloseall()
		ExecuteSection( "Exit" )
		xor	eax,eax
	.endif
	exit( eax )
	ret

GeneralFailure ENDP

endif

main	PROC C USES esi edi ebx

	mov	esi,1
	xor	edi,edi ; pointer to <filename>

	.while	esi < _argc

		mov	eax,_argv
		mov	ebx,[eax+esi*4]
		mov	eax,[ebx]

		.switch al

		  .case '?'
		   exitusage:
			_print( addr copyright )
			_print( addr cp_usage )
			xor	eax,eax
			jmp	toend

		  .case '-'
		  .case '/'
			inc	ebx
			shr	eax,8
			.switch al
				;
				; @3.42 - save environment block to file
				;
				; Note: This is called inside a child process
				;
			  .case 'E'
				cmp	ah,':'
				jne	exitusage
				add	ebx,2
				SaveEnvironment( ebx )
				exit  ( 0 )

			  .case 'N'
				inc	ebx
				.if	strtolx( ebx )
					mov	numfblock,eax
				.endif
				.endc
			  .case 'C'
				inc	ebx
				.if	filexist( ebx ) == 2
					free( _pgmpath )
					salloc( ebx )
					mov	_pgmpath,eax
					.endc
				.endif
			  .default
				jmp	exitusage
			.endsw
			.endc

		  .default
			mov	edi,ebx
		.endsw

		inc	esi
	.endw

	SetConsoleTitle( DZ_Title )

	.if	!doszip_init( edi )

		_print( addr copyright )

		doszip_open()
ifdef __SIGNAL__
		mov	ebx,GeneralFailure
		signal( SIGINT,	  ebx ) ; interrupt
		signal( SIGILL,	  ebx ) ; illegal instruction - invalid function image
		signal( SIGFPE,	  ebx ) ; floating point exception
		signal( SIGSEGV,  ebx ) ; segment violation
		signal( SIGTERM,  ebx ) ; Software termination signal from kill
		signal( SIGABRT,  ebx ) ; abnormal termination triggered by abort call

		doszip_modal()
		GeneralFailure(SIGTERM)
else
		doszip_modal()
		doszip_close()
		.if	cflag & _C_DELHISTORY

			;historyremove()
		.endif
		tcloseall()

		.if	CFGetSection( "Exit" )

			CFExecute( eax )
		.endif
		;ExecuteSection( "Exit" )
		xor	eax,eax
endif
	.endif

toend:
	ret
main	ENDP

	END
