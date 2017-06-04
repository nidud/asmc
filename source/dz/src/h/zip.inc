ifndef __LIBC_INC
 include libc.inc
endif

.xlist

ZIPHEADERID	equ 4B50h	; two-byte zip lead-in
ZIPLOCALID	equ 0403h	; signature local file
ZIPCENTRALID	equ 0201h	; signature central file
ZIPDIGITALID	equ 0505h	; digital signature
ZIPENDSENTRID	equ 0605h	; signature end central

WSIZE		equ 8000h

S_LZIP		STRUC	; Local file header: 30 byte
lz_pkzip	dw ?	; local file header signature
lz_zipid	dw ?
lz_version	dw ?	; version needed to extract
lz_flag		dw ?	; general purpose bit flag
lz_method	dw ?	; compression method
lz_time		dw ?	; last mod file time
lz_date		dw ?	; last mod file date
lz_crc		dd ?	; crc-32
lz_csize	dd ?	; compressed size
lz_fsize	dd ?	; uncompressed size
lz_fnsize	dw ?	; file name length
lz_extsize	dw ?	; extra field length
S_LZIP		ENDS

S_CZIP		STRUC	; Central directory structure: 46 byte
cz_pkzip	dw ?	; central file header signature
cz_zipid	dw ?
cz_version_made dw ?	; version made by
cz_version_need dw ?	; version needed to extract
cz_bitflag	dw ?	; general purpose bit flag
cz_method	dw ?	; compression method
cz_time		dw ?	; last mod file time
cz_date		dw ?	; last mod file date
cz_crc		dd ?	; crc-32
cz_csize	dd ?	; compressed size
cz_fsize	dd ?	; uncompressed size
cz_fnsize	dw ?	; file name length
cz_extsize	dw ?	; extra field length
cz_cmtsize	dw ?	; file comment length
cz_disk		dw ?	; disk number start
cz_int_attrib	dw ?	; internal file attributes
cz_ext_attrib	dw ?	; external file attributes
cz_ext_attribdx dw ?
cz_off_local	dd ?	; relative offset of local header
S_CZIP		ENDS	; 46 byte

S_ZEND		STRUC	; End of central directory record: 22 byte
ze_pkzip	dw ?	; end of central dir signature
ze_zipid	dw ?
ze_disk_cur	dw ?	; number of this disk
ze_disk_one	dw ?	; number at start of the central directory
ze_entry_cur	dw ?	; central directory on this disk
ze_entry_dir	dw ?	; total entries in the central directory
ze_size_cent	dd ?	; size central directory
ze_off_cent	dd ?	; offset central directory
ze_comment_size dw ?	; .ZIP file comment length
S_ZEND		ENDS

externdef	zip_attrib:	DWORD
externdef	zip_local:	S_LZIP
externdef	zip_central:	S_CZIP
externdef	zip_endcent:	S_ZEND
externdef	zip_flength:	DWORD

zip_unzip		PROTO
zip_inflate		PROTO
zip_explode		PROTO
zip_deflate		PROTO :DWORD
zip_copylocal		PROTO :DWORD
zip_copycentral		PROTO :DWORD, :DWORD, :DWORD
zip_copyendcentral	PROTO
zip_clearentry		PROTO
zip_mkarchivetmp	PROTO
zip_setprogress		PROTO
zip_displayerror	PROTO
zip_renametemp		PROTO

ER_ZIP		equ 2
ER_BADERR	equ 3
ER_MEM		equ 4
ER_CRCERR	equ 5
ER_NOZIP	equ 9
ER_FIND		equ 11
ER_OPEN		equ 12
ER_DISK		equ 50
ER_USERABORT	equ 66
ER_READARCH	equ -2

.list
