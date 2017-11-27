ifndef __WSUB_INC
__ZLIB_INC equ <>
include consx.inc

.xlist

ZIPHEADERID	equ 4B50h	; two-byte zip lead-in
ZIPLOCALID	equ 0403h	; signature local file
ZIPCENTRALID	equ 0201h	; signature central file
ZIPDIGITALID	equ 0505h	; digital signature
ZIPENDSENTRID	equ 0605h	; signature end central

WSIZE		equ 8000h

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

externdef	zip_attrib:DWORD
externdef	zip_local:S_LZIP
externdef	zip_central:S_CZIP
externdef	zip_endcent:S_ZEND
externdef	zip_flength:DWORD
externdef	crctab:DWORD

zip_unzip	proto
zip_inflate	proto
zip_explode	proto
zip_deflate	proto :DWORD
zip_copylocal	proto :DWORD
zip_copycentral proto :DWORD, :DWORD, :DWORD
zip_copyendcentral proto
zip_clearentry	proto
zip_mkarchivetmp proto
zip_setprogress proto
zip_displayerror proto
zip_renametemp	proto

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

WMAXPATH	equ 2048	; the max length is 8000h..
MAXFBLOCK	equ 5000
WMAXFBLOCK	equ 300000

_FB_SELECTED	equ 00010000h
_FB_ROOTDIR	equ 00020000h
_FB_UPDIR	equ 00040000h
_FB_CDROOM	equ 00080000h
_FB_ARCHZIP	equ 00100000h
_FB_ARCHEXT	equ 00200000h
_FB_ZENCRYPTED	equ 00400000h	; if _FB_ARCHZIP
_FB_ZEXTLOCHD	equ 00800000h	; if _FB_ARCHZIP
_FB_ARCHIVE	equ _FB_ARCHEXT or _FB_ARCHZIP
_A_FATTRIB	equ 0000FFFFh

_W_PANELID	equ 00000001h	; _P_PANELID
_W_VISIBLE	equ 00000002h	; _P_VISIBLE
_W_MINISTATUS	equ 00000004h	; _P_MINISTATUS
_W_WIDEVIEW	equ 00000008h	; _P_WIDEVIEW
_W_DETAIL	equ 00000010h	; _P_DETAIL
_W_DRVINFO	equ 00000020h	; _P_DRVINFO
_W_WHIDDEN	equ 00000040h	; _P_WHIDDEN - Hidden Panel
_P_FLAGMASK	equ 0000007Fh

_W_HIDDEN	equ 00000080h	; Hidden files
_W_LONGNAME	equ 00000100h
_W_SORTNAME	equ 00000000h
_W_SORTTYPE	equ 00000200h
_W_SORTDATE	equ 00000400h
_W_SORTSIZE	equ 00000600h
_W_NOSORT	equ 00000800h
_W_SORTSUB	equ 00001000h
_W_ROOTDIR	equ 00002000h
_W_CDROOM	equ 00004000h
_W_NETWORK	equ 00008000h
_W_REMOVABLE	equ 00010000h
_W_TEDIT	equ 00020000h
_W_ARCHZIP	equ 00100000h
_W_ARCHEXT	equ 00200000h
_W_MALLOC	equ 01000000h

_W_ARCHIVE	equ _W_ARCHZIP or _W_ARCHEXT
_W_DEFAULT	equ _W_SORTTYPE or _W_HIDDEN or _W_VISIBLE or _W_MINISTATUS or _W_LONGNAME

S_FBLK		STRUC
fb_flag		dd ?	; _FB_:_A_
fb_time		dd ?	; date:time
fb_size		dq ?
fb_name		sbyte 4 dup(?)
S_FBLK		ENDS
LPFBLK		TYPEDEF PTR S_FBLK
PPFBLK		TYPEDEF PTR LPFBLK

S_WSUB		STRUC
ws_flag		dd ?
ws_count	dd ?
ws_maxfb	dd ?
ws_mask		LPSTR ?
ws_file		LPSTR ?
ws_arch		LPSTR ?
ws_path		LPSTR ?
ws_fcb		PPFBLK ?
S_WSUB		ENDS	; 32 byte
LPWSUB		TYPEDEF PTR S_WSUB

fballoc		proto :LPSTR, :DWORD, :QWORD, :DWORD
fballocwf	proto :PVOID, :DWORD
fbupdir		proto :DWORD
fbffirst	proto :PVOID, :DWORD
fballocff	proto :DWORD, :DWORD
fbinvert	PROTO :LPFBLK
fbselect	PROTO :LPFBLK
fbcolor		PROTO :LPFBLK

wsalloc		proto :DWORD, :DWORD
wsopen		proto :LPWSUB
wsclose		proto :LPWSUB
wsinit		proto :LPWSUB
wsfree		proto :LPWSUB
wsread		proto :LPWSUB
wssort		proto :LPWSUB
wssetflag	proto :LPWSUB
wslocal		proto :LPWSUB
wschdrv		proto :LPWSUB, :DWORD
wsearch		proto :LPWSUB, :LPSTR
wsfblk		proto :LPWSUB, :DWORD
wsffirst	proto :LPWSUB
wsmkdir		proto :LPSTR
wsextend	proto :LPWSUB

wsopenarch	proto :LPWSUB
wzipread	proto :DWORD
wzipopen	proto
wzipclose	proto
wsdecomp	proto :DWORD, :DWORD, :DWORD
wzipadd		proto :QWORD, :DWORD, :DWORD
wzipdel		proto :DWORD, :DWORD
wzipcopy	proto :DWORD, :DWORD, :DWORD
wsmkzipdir	proto :DWORD, :DWORD
wscopyremove	proto :LPSTR
wscopyopen	proto :LPSTR, :LPSTR

wsfindfirst	proto :LPSTR, :ptr, :SIZE_T
wsfindnext	proto :ptr, :HANDLE
wscloseff	proto :HANDLE

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

IO_SEARCHCASE	equ 0001h
IO_SEARCHHEX	equ 0002h
IO_SEARCHSET	equ 0004h
IO_SEARCHCUR	equ 0008h
IO_SEARCHMASK	equ 000Fh
IO_SEARCHSUB	equ 0020h

IO_RETURNLF	equ 0040h	; return line index on search
IO_GLMEM	equ 0080h	; save pointer in ios_line (ios_bp aligned xxxx0000h)
IO_CRYPT	equ 0100h	; Crypted file
IO_USEUPD	equ 0200h	; Progress
IO_UPDTOTAL	equ 0400h	; Add Read/Write size to total
IO_USECRC	equ 0800h	; Update CRC on read/write
IO_MEMBUF	equ 4000h	; File in buffer or memory addr
IO_ERROR	equ 8000h	; Write fault

OO_MEM64K	equ 00010000h	; malloc(segment) aligned xxxx0000h
OO_MEMBUF	equ 00000000h	; read, set ios_fsize and IO_MEMBUF

S_IOST		STRUC
ios_bp		LPSTR ?
ios_i		dd ?
ios_c		dd ?
ios_size	dd ?
ios_flag	dd ?
ios_file	dd ?
ios_crc		dd ?
ios_line	dd ?		; line offset
ios_offset	dq ?		; seek offset
ios_total	dq ?		; count read/write
ios_fsize	dq ?
S_IOST		ENDS
LPIOST		TYPEDEF PTR S_IOST

externdef	STDI:S_IOST
externdef	STDO:S_IOST
externdef	oupdate:SIZE_T

ioinit		proto :LPIOST, :SIZE_T
ioopen		proto :LPIOST, :LPSTR, :DWORD, :SIZE_T
ioseek		proto :LPIOST, :QWORD, :DWORD
iocopy		proto :LPIOST, :LPIOST, :QWORD
ioflush		proto :LPIOST
ioread		proto :LPIOST
ioclose		proto :LPIOST
iofree		proto :LPIOST
ioputc		proto ; edx, eax
ifdef _WIN64
iogetc		proto :PTR S_IOST
else
iogetc		proto
endif
iowrite		proto :LPIOST, :PVOID, :SIZE_T
iotell		proto :LPIOST

oputc		proto ; STDO, eax
ogetc		proto ; STDI
oupdcrc		proto
osearch		proto
notfoundmsg	proto
oreadb		proto :LPSTR, :DWORD
oungetc		proto
oread		proto
oprintf		proto _CDecl :LPSTR, :VARARG
ogetl		proto :LPSTR, :LPSTR, :DWORD
ogets		proto
oputs		proto :LPSTR
ogetouth	proto :LPSTR, :DWORD
openfile	proto :LPSTR, :DWORD, :DWORD
oseek		proto :SIZE_T, :DWORD

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

FILT_MAXSTRING	equ 128

S_FILT		STRUC
of_flag		dd ?
of_max_date	dd ?
of_min_date	dd ?
of_max_size	SIZE_T ?
of_min_size	SIZE_T ?
of_include	db FILT_MAXSTRING dup(?)
of_exclude	db FILT_MAXSTRING dup(?)
S_FILT		ENDS ; 276

externdef	filter:SIZE_T

filter_fblk	proto :PTR S_FBLK
filter_wblk	proto :PTR WIN32_FIND_DATA
filter_edit	proto :PTR, :PTR

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

externdef	cp_stdmask: SBYTE
externdef	cp_warning: SBYTE
externdef	cp_einitsub:SBYTE
externdef	cp_dotdot:  SBYTE	; ".."
externdef	cp_datefrm: SBYTE	; "%2u.%02u.%02u"
externdef	cp_timefrm: SBYTE	; "%2u:%02u"

externdef	__srcpath:SIZE_T
externdef	__outpath:SIZE_T
externdef	__srcfile:SIZE_T
externdef	__outfile:SIZE_T
externdef	entryname:SIZE_T

externdef	_pgmpath:SIZE_T

dostounix	proto :LPSTR
unixtodos	proto :LPSTR
removefile	proto :LPSTR
removetemp	proto :LPSTR
filexist	proto :LPSTR
setfattr	proto :LPTSTR, :UINT
strfcat		proto :LPSTR, :LPSTR, :LPSTR
setfext		proto :LPSTR, :LPSTR
cmpwarg		proto :LPSTR, :LPSTR
cmpwargs	proto :LPSTR, :LPSTR

notsup		proto
eropen		proto :LPSTR
ermkdir		proto :LPSTR
erdelete	proto :LPSTR
errnomsg	proto :LPSTR, :LPSTR, :LPSTR

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

CFREADONY	equ 0001h
CFSYSTEM	equ 0002h
CFDIRECTORY	equ 0004h
CFSELECTED	equ 0008h
CFDELETEALL	equ 0010h

externdef	confirmflag:DWORD

confirm_continue proto :DWORD
confirm_delete	proto :LPSTR, :DWORD
confirm_delete_file proto :LPSTR, :DWORD
confirm_delete_sub proto :LPSTR

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

externdef	progress_dobj:S_DOBJ
externdef	progress_size:QWORD

progress_open	PROTO :DWORD, :DWORD
progress_close	PROTO
progress_set	PROTO :DWORD, :DWORD, :QWORD
progress_update PROTO :QWORD
test_userabort	PROTO

_WOPEN		equ 0x01
_WSAVE		equ 0x02
_WLOCAL		equ 0x04 ; use program or current directory
_WLOCK		equ 0x08 ; lock to this directory
_WNEWFILE	equ 0x10

wdlgopen	PROTO :LPSTR, :LPSTR, :DWORD
wgetfile	PROTO :LPSTR, :LPSTR, :DWORD

.list
endif	; __WSUB_INC
