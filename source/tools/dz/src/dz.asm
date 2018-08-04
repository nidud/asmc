; MAIN.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include stdio.inc
include stdlib.inc
include malloc.inc
include string.inc
include cfini.inc
include crtl.inc

includelib libc.lib
includelib kernel32.lib
includelib user32.lib

public cstart
public mainCRTStartup

_INIT	SEGMENT PARA FLAT PUBLIC 'INIT'
_INIT	ENDS
_IEND	SEGMENT PARA FLAT PUBLIC 'INIT'
_IEND	ENDS

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

copyright label byte
	db 'The Doszip Commander Version ',DOSZIP_VSTRING,', '
	db 'Copyright (C) 2016 Doszip Developers',10,10,0
usage	db 'Command line switches',10
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

DZTitle dd cptitle
cptitle db "Doszip Commander",0

	.code

	dd 495A440Ah
	dd 564A4A50h
	db __LIBC__ / 100 + '0','.',__LIBC__ mod 100 / 10 + '0',__LIBC__ mod 10 + '0'

ifdef __SIGNAL__

GeneralFailure PROC signo

	mov ecx,signo
	mov eax,1
	.if ecx == SIGTERM || ecx == SIGABRT

		doszip_close()
		.if cflag & _C_DELHISTORY

			historyremove()
		.endif
		tcloseall()
		ExecuteSection("Exit")
		xor eax,eax
	.endif
	exit(eax)
	ret

GeneralFailure ENDP

endif

main proc c argc:UINT, argv:ptr, environ:ptr

	mov esi,1
	xor edi,edi ; pointer to <filename>

	.while	esi < argc

		mov eax,argv
		mov ebx,[eax+esi*4]
		mov eax,[ebx]

		.switch al

		  .case '?'
		   exitusage:
			_print(addr copyright)
			_print(addr usage)
			xor eax,eax
			jmp toend

		  .case '-'
		  .case '/'
			inc ebx
			shr eax,8
			.switch al
				;
				; @3.42 - save environment block to file
				;
				; Note: This is called inside a child process
				;
			  .case 'E'
				cmp ah,':'
				jne exitusage
				add ebx,2
				SaveEnvironment(ebx)
				exit(0)

			  .case 'N'
				inc ebx
				.if strtolx(ebx)

					mov numfblock,eax
				.endif
				.endc
			  .case 'C'
				inc ebx
				.if filexist(ebx) == 2

					free(_pgmpath)
					_strdup(ebx)
					mov _pgmpath,eax
					.endc
				.endif
			  .default
				jmp exitusage
			.endsw
			.endc

		  .default
			mov edi,ebx
		.endsw

		inc esi
	.endw

	SetConsoleTitle( DZTitle )

	.if !doszip_init( edi )

		_print( addr copyright )

		doszip_open()
ifdef __SIGNAL__
		mov ebx,GeneralFailure
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
		tcloseall()

		.if CFGetSection("Exit")

			CFExecute(eax)
		.endif
		xor eax,eax
endif
	.endif

toend:
	ret
main	ENDP

mainCRTStartup:
	mov eax,offset _INIT
	and eax,-4096	; LINK - to start of page
	jmp @F
cstart:
	mov eax,offset _INIT
@@:
	mov edx,offset _IEND
	__initialize( eax, edx )
	exit( main( __argc, __argv, _environ ) )

	end	cstart
