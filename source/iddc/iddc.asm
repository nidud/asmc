;
; Change history:
; 2016-09-24 - added switch -win64
; 2016-04-05 - added switch -coff and -omf
; 2014-08-18 - moved IDD_ to top -- align 16
; 2014-08-09 - added switch -r
; 2013-01-01 - created
;
include io.inc
include direct.inc
include stdio.inc
include stdlib.inc
include string.inc
include consx.inc
include time.inc
include winnt.inc

MAXIDDSIZE	equ 2048
OMF_THEADR	equ 080h
OMF_COMENT	equ 088h
OMF_PUBDEF	equ 090h
OMF_LNAMES	equ 096h
OMF_SEGDEF	equ 098h
OMF_LEDATA	equ 0A0h
OMF_FIXUPP	equ 09Ch
OMF_MODEND	equ 08Ah
OMF_FIXUPP32	equ 09Dh

S_OMFR		STRUC
o_type		db ?
o_length	dw ?
o_data		db MAXIDDSIZE dup(?)
o_cksum		db ?
S_OMFR		ENDS

.data

cpinfo		db "Doszip Resource Compiler v1.04 Copyright (c) 2016 GNU General Public License",10,0
cpusage		db "USAGE: IDDC [-/options] <idd-file>",10
		db 10
		db " -mc     output 16-bit .compact",10
		db " -ml     output 16-bit .large",10
		db " -mf     output 32-bit .flat (default)",10
		db " -win64  output 64-bit .flat",10
		db " -omf    output OMF object (default)",10
		db " -coff   output COFF object",10
		db " -f#     full pathname of .OBJ file",10
		db " -r      recurse subdirectories",10
		db " -t      compile text file (add zero)",10
		db 10,0

console		dd 0
PUBLIC		console

omf		S_OMFR	<0>
fileidd		db _MAX_PATH dup(0)
fileobj		db _MAX_PATH dup(0)
idname		db '_IDD_'
dlname		db 128 dup(0)
dialog		db MAXIDDSIZE dup(0)
extobj		db '.obj',0
options		db "fmtrocw",0
option_f	db 0
option_m	db 'f'	; -mc, -ml, -mf
option_t	db 0
option_r	db 0
option_omf	db 1
option_coff	db 0
option_win64	db 0

COMENT		db 88h,1Ch,00h,1Ah
		db 'Doszip Resource Edit v2.33',0
COMENT_SIZE	= $ - COMENT

LNAMES		db 96h,0Dh,00h,00h
		db 4, 'DATA'
		db 5, '_DATA'
LNAMES_SIZE	= $ - LNAMES

LNAMES32	db 96h,1Dh,00h,00h
		db 4, 'FLAT'
		db 4, 'CODE'
		db 5, '_TEXT'
		db 4, 'DATA'
		db 5, '_DATA'
LNAMES_SIZE32	= $ - LNAMES

	.code


owrite	PROC h, b, l
	.if	oswrite( h, b, l ) != l
		perror( addr fileobj )
		exit( 2 )
	.endif
	ret
owrite	ENDP

omf_write:
	push	esi
	mov	esi,offset omf
	ASSUME	esi:PTR S_OMFR
	xor	eax,eax
	xor	edx,edx
	movzx	ecx,[esi].o_length
	add	ecx,2
	.repeat
		lodsb
		add	edx,eax
	.untilcxz
	mov	esi,offset omf
	dec	edx
	not	edx
	movzx	ebx,[esi].o_length
	add	ebx,2
	mov	[esi+ebx],dl
	inc	ebx
	owrite( edi, esi, ebx )
	pop	esi
	ASSUME	esi:NOTHING
	ret

arg_option_t:
	inc	option_t
	ret

arg_option_r:
	inc	option_r
	ret

arg_option_f:
	inc	option_f
	add	ebx,2
	strcpy( addr fileobj, ebx )
	inc	cl
	ret

arg_option_m:
	mov	option_m,ah
	inc	al
	ret

arg_option_omf:
	mov	option_coff,0
	inc	option_omf
	ret

arg_option_win64:
	inc	option_win64
arg_option_coff:
	mov	option_omf,0
	inc	option_coff
	ret

arg_option_?:
	_print( addr cpinfo )
	_print( addr cpusage )
	xor	eax,eax
	ret

arg_option:
	mov	eax,[ebx]
	.if al == '?'
		jmp	arg_option_?
	.endif
	.if al == '/' || al == '-'
		shr	eax,8
		or	eax,202020h
		push	ebx
		mov	ebx,offset options
	  @@:
		cmp	al,[ebx]
		je	@F
		inc	ebx
		cmp	BYTE PTR [ebx],0
		jne	@B
		pop	ebx
		jmp	arg_option_?
	  @@:
		sub	ebx,offset options
		shl	ebx,2
		mov	ecx,option_label[ebx]
		pop	ebx
		jmp	ecx
	.endif
	.if !fileidd
		strcpy( addr fileidd, ebx )
	.else
		jmp	arg_option_?
	.endif
	xor	eax,eax
	inc	eax
	ret

	.data

option_label label DWORD
	dd	arg_option_f
	dd	arg_option_m
	dd	arg_option_t
	dd	arg_option_r
	dd	arg_option_omf
	dd	arg_option_coff
	dd	arg_option_win64
	dd	arg_option_?

	.code

WR_COFF PROC USES esi edi ebx handle, rbuf, len
	local	path[_MAX_PATH]:BYTE
	local	is:IMAGE_SYMBOL

	.data
		c_header	label BYTE
		Machine		dw IMAGE_FILE_MACHINE_I386
		Sections	dw 2
		TimeStamp	dd ?
		SymbolTable	dd ?
		Symbols		dd 6
		OptionalHeader	dw 0
		Characteristics dw 0
				db ".text",0,0,0	; Name
				dd 0			; PhysicalAddress
				dd 0			; VirtualAddress
				dd 0			; SizeOfRawData
				dd 0			; PointerToRawData
				dd 0			; PointerToRelocations
				dd 0			; PointerToLinenumbers
				dw 0			; NumberOfRelocations
				dw 0			; NumberOfLinenumbers
				dd 60500020h		; Characteristics
				db ".data",0,0,0
				dd 0			; PhysicalAddress
				dd 0			; VirtualAddress
		SizeOfRawData	dd ?			; SizeOfRawData
				dd 64h			; PointerToRawData
		Relocations	dd ?			; PointerToRelocations
				dd 0			; PointerToLinenumbers
				dw 1			; NumberOfRelocations
				dw 0			; NumberOfLinenumbers
				dd 0C0500040h		; Characteristics
				dd 0			; _IDD_*
		ch_size		equ $ - c_header
				dd 0
	.code

	.if	option_win64
		mov	Machine,IMAGE_FILE_MACHINE_AMD64
		;
		; pointers from DD to DQ: + 8 byte for each object
		;
		mov	ecx,rbuf
		movzx	eax,[ecx].S_ROBJ.rs_count
		inc	eax
		shl	eax,3
		add	[ecx].S_ROBJ.rs_memsize,ax
	.endif

	_time ( addr TimeStamp )
	mov	eax,len
	add	eax,4
	.if	option_win64
		add	eax,4
	.endif
	mov	SizeOfRawData,eax
	.if	eax & 1
		add	eax,1
	.endif
	add	eax,64h
	mov	Relocations,eax
	add	eax,10
	mov	SymbolTable,eax

	mov	eax,ch_size
	.if	option_win64
		add	eax,4
	.endif
	owrite( handle, addr c_header, eax )
	owrite( handle, rbuf, len )

	.data
		l_10	dd 0
			dd 5		; SymbolTableIndex
			dw 6		; Type
	.code

	mov	eax,len
	add	eax,ch_size + 4
	.if	option_win64
		add	eax,4
		mov	WORD PTR l_10[8],1
	.endif
	.if	eax & 1
		push	0
		mov	eax,esp
		owrite( handle, eax, 1 )
		pop	eax
	.endif
	owrite( handle, addr l_10, 10 )

	.data
		c_end	db ".text",0,0,0	; Name
			dd 0			; Value
			dw 1			; SectionNumber
			dw 0			; Type
			db 3			; StorageClass
			db 1			; NumberOfAuxSymbols
			dd 0			; Length
			dw 0			; NumberOfRelocations
			dw 0			; NumberOfLinenumbers
			dd 0			; CheckSum
			dw 0
			dw 0			; Number
	      Selection dw 16h			; Selection
			db ".data",0,0,0	; Name
			dd 0			; Value
			dw 2			; SectionNumber
			dw 0			; Type
			db 3			; StorageClass
			db 1			; NumberOfAuxSymbols
		DLength dd ?			; Length
			dw 1			; NumberOfRelocations
			dw 0			; NumberOfLinenumbers
			dd 0			; CheckSum
			dw 0
			dw 0			; Number
			dw 0			; Selection
		ce_size equ $ - c_end
	.code

	mov	eax,len
	add	eax,4
	.if	option_win64
		add	eax,4
		mov	Selection,0
	.endif
	mov	DLength,eax
	owrite( handle, addr c_end, ce_size )

	xor	esi,esi
	mov	ecx,sizeof(IMAGE_SYMBOL)
	lea	edi,is
	xor	eax,eax
	rep	stosb
	mov	is.SectionNumber,2
	mov	is.StorageClass,2

	lea	edi,idname
	.if	option_win64
		inc	edi
	.endif
	.if	strlen( edi ) <= 8
		memcpy( addr is.ShortName, edi, eax )
	.else
		mov	is._Long,4
		lea	esi,[eax+1]
	.endif
	owrite( handle, addr is, sizeof(IMAGE_SYMBOL) )

	mov	ecx,sizeof(IMAGE_SYMBOL)
	lea	edi,is
	xor	eax,eax
	rep	stosb
	lea	ebx,path
	lea	edi,idname[4]
	.if	option_win64
		inc	edi
	.endif
	strcpy( ebx, edi )
	xor	edi,edi

	mov	is.Value,4
	.if	option_win64
		mov	is.Value,8
	.endif
	mov	is.SectionNumber,2
	mov	is.StorageClass,2
	.if	strlen( strcat( ebx, "_RC" ) ) <= 8
		memcpy( addr is.ShortName, ebx, eax )
	.else
		lea	edx,[esi+4]
		mov	is._Long,edx
		lea	edi,[eax+1]
	.endif
	owrite( handle, addr is, sizeof(IMAGE_SYMBOL) )

	lea	eax,[esi+edi+4]
	mov	DLength,eax
	owrite( handle, addr DLength, 4 )

	.if	esi
		lea	eax,idname
		.if	option_win64
			inc	eax
		.endif
		owrite( handle, eax, esi )
	.endif
	.if	edi
		owrite( handle, ebx, edi )
	.endif
	_close( handle )
	xor	eax,eax
toend:
	ret
WR_COFF ENDP

WR_OMF	PROC USES esi edi ebx handle, rbuf, len
	strfn ( addr fileidd )
	mov	edx,eax
	strlen( strcpy( addr omf.o_data[1], edx ) )
	mov	omf.o_type,OMF_THEADR
	mov	omf.o_data,al
	add	eax,2
	mov	omf.o_length,ax
	call	omf_write

	memcpy( addr omf, addr COMENT, COMENT_SIZE )
	call	omf_write

	.if	option_m == 'f'
		memcpy( addr omf, addr LNAMES32, LNAMES_SIZE32 )
	.else
		memcpy( addr omf, addr LNAMES, LNAMES_SIZE )
	.endif
	call	omf_write

	mov	eax,esi
	add	eax,4
	mov	omf.o_type,OMF_SEGDEF
	mov	omf.o_length,7

	.if	option_m == 'f'
		mov	omf.o_data,0A9h
		mov	omf.o_data[1],0
		mov	omf.o_data[2],0
		mov	omf.o_data[3],4
		mov	omf.o_data[4],3
		mov	omf.o_data[5],1
	.else
		mov	omf.o_data,48h
		mov	omf.o_data[1],al
		mov	omf.o_data[2],ah
		mov	omf.o_data[3],3
		mov	omf.o_data[4],2
		mov	omf.o_data[5],1
	.endif
	call	omf_write

	.if	option_m == 'f'
		mov	omf.o_type,OMF_COMENT
		mov	omf.o_length,5
		mov	omf.o_data,080h
		mov	omf.o_data[1],0FEh
		mov	omf.o_data[2],04Fh
		mov	omf.o_data[3],1
		call	omf_write
		mov	eax,esi
		add	eax,4
		mov	omf.o_type,OMF_SEGDEF
		mov	omf.o_length,7
		mov	omf.o_data,0A9h
		mov	omf.o_data[1],al
		mov	omf.o_data[2],ah
		mov	omf.o_data[3],6
		mov	omf.o_data[4],5
		mov	omf.o_data[5],1
		call	omf_write
		mov	omf.o_type,9Ah
		mov	omf.o_length,2
		mov	omf.o_data,02h
		mov	omf.o_data[1],62h
		call	omf_write
	.endif
	mov	omf.o_type,OMF_PUBDEF
	.if	option_m == 'f'
		mov omf.o_data[0],1
		mov omf.o_data[1],2
	.else
		mov omf.o_data[0],0
		mov omf.o_data[1],1
	.endif
	mov	edx,offset idname
	.if	option_m != 'f'
		inc edx
	.endif
	strlen( strcpy( addr omf.o_data[3], edx ) )
	mov	omf.o_data[2],al
	add	eax,7
	mov	omf.o_length,ax
	mov	ebx,eax
	mov	omf.o_data[ebx-4],0
	mov	omf.o_data[ebx-3],0
	mov	omf.o_data[ebx-2],0
	mov	omf.o_data[ebx-1],0
	call	omf_write
	mov	omf.o_type,OMF_COMENT
	mov	omf.o_length,4
	mov	omf.o_data,0
	mov	omf.o_data[1],0A2h
	mov	omf.o_data[2],1
	call	omf_write
	mov	edx,edi
	mov	ecx,1024
	lea	edi,omf.o_data
	xor	eax,eax
	rep	stosb
	mov	edi,edx
	mov	eax,esi
	add	eax,8
	mov	omf.o_type,OMF_LEDATA
	mov	omf.o_length,ax
	mov	omf.o_data,1
	.if	option_m == 'f'
		inc omf.o_data
	.endif
	mov	ecx,esi
	.if	option_t
		dec ecx
	.endif
	memcpy( addr omf.o_data[3+4], addr dialog, ecx )
	mov	omf.o_data[3],4
	call	omf_write
	mov	omf.o_type,OMF_FIXUPP
	.if	option_m == 'f'
		mov omf.o_type,OMF_FIXUPP32
	.endif
	mov	omf.o_length,5
	mov	omf.o_data[1],0
	mov	al,0CCh
	.if	option_m == 'f'
		mov al,0E4h
	.endif
	mov	omf.o_data[0],al
	mov	omf.o_data[2],54h
	mov	omf.o_data[3],1
	.if	option_m == 'f'
		mov omf.o_data[3],2
	.endif
	mov	omf.o_data[4],0
	call	omf_write
	mov	omf.o_type,OMF_MODEND
	mov	omf.o_length,2
	mov	omf.o_data,0
	call	omf_write
	_close( edi )
	xor	eax,eax
toend:
	ret
WR_OMF	ENDP

AssembleModule PROC USES esi edi ebx module

	.if	_access( module, 0 )
		perror( module )
		mov	eax,1
		jmp	toend
	.endif

	.if	strrchr( strcpy( addr dlname, strfn( module ) ), '.' )
		mov	edi,eax
		mov	BYTE PTR [edi],0
	.endif

	.if	!option_f
		_getcwd( addr fileobj, _MAX_PATH )
		setfext( strfcat( addr fileobj, 0, strfn( module ) ), addr extobj )
	.endif

	.if	osopen( module, _A_NORMAL, M_RDONLY, A_OPEN ) == -1
		perror( module )
		mov	eax,2
		jmp	toend
	.endif

	mov	ebx,eax
	osread( ebx, addr dialog, MAXIDDSIZE )
	mov	esi,eax
	_close( ebx )

	.if	!esi
		perror( module )
		mov	eax,3
		jmp	toend
	.endif
	.if	option_t
		inc	esi
	.endif

	.if	esi > 1020
		perror( "Resource is to big -- > 1024" )
		mov	eax,3
		jmp	toend
	.endif

	.if	osopen( addr fileobj, _A_NORMAL, M_WRONLY, A_CREATETRUNC ) == -1
		perror( addr fileobj )
		mov	eax,2
		jmp	toend
	.endif
	mov	edi,eax
	.if	option_omf
		WR_OMF(edi, addr dialog, esi )
	.else
		WR_COFF(edi, addr dialog, esi )
	.endif
toend:
	ret
AssembleModule ENDP

AssembleSubdir PROC USES esi edi ebx directory, wild
local	path[_MAX_PATH]:BYTE
local	ff:WIN32_FIND_DATA
local	h:DWORD
local	rc:DWORD

	lea	esi,path
	lea	edi,ff
	lea	ebx,ff.cFileName
	mov	rc,0

	.if FindFirstFile( strfcat( esi, directory, wild ), edi ) != -1
		mov	h,eax
		.repeat
			AssembleModule( strfcat( esi, directory, ebx ) )
			mov rc,eax
			FindNextFile( h, edi )
		.until !eax
		FindClose( h )
	.endif

	.if FindFirstFile( strfcat( esi, directory, "*.*" ), edi ) != -1
		mov	h,eax
		.repeat
			mov eax,[ebx]
			and eax,00FFFFFFh

			.if ff.dwFileAttributes & _A_SUBDIR && ax != '.' && eax != '..'

				.if AssembleSubdir( strfcat( esi, directory, ebx ), wild )
					mov rc,eax
					.break
				.endif
			.endif
			FindNextFile( h, edi )
		.until !eax
		FindClose( h )
	.endif
	mov	eax,rc
	ret
AssembleSubdir ENDP


main	PROC c
local	path[_MAX_PATH]:BYTE
	mov	edi,_argc
	mov	esi,_argv
	.if edi == 1
		call arg_option_?
		ret
	.endif
	dec	edi
	lodsd

	.repeat
		lodsd
		mov	ebx,eax
		call	arg_option
		.if ZERO?
			ret
		.endif
		dec	edi
	.until !edi
	lea	esi,fileidd
	lea	edi,path
	.if !option_r
		AssembleModule( esi )
	.else
		strcpy( edi, esi )
		.if strfn( esi ) > esi
			dec	eax
		.endif
		mov	BYTE PTR [eax],0

		AssembleSubdir( esi, strfn( edi ) )
	.endif
	ret
main	ENDP

	END
