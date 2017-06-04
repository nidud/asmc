ifndef __LIBC_INC
 include libc.inc
endif

.xlist

WMAXPATH	equ 260
WMAXDRIVE	equ 3
MAXDRIVES	equ 27
WMAXDIR		equ 256
WMAXFILE	equ 256
WMAXEXT		equ 256
MAXPATH		equ 80
MAXDRIVE	equ 3
MAXDIR		equ 66
MAXFILE		equ 9
MAXEXT		equ 5
SIZEWFBLK	equ 318

MAXDRIVES	equ 27

_DISK_LOCAL	equ 0001h		; _dos_remotedevice()
_DISK_FLOPPY	equ 0100h
_DISK_NETWORK	equ 0200h
_DISK_SUBST	equ 0400h
_DISK_CDROOM	equ 0800h

_DISK_NOSUCHDRIVE	equ 0	; _bios_disktype()
_DISK_FLOPPYNOCHAIN	equ 1
_DISK_FLOPPYWIDTHCHAIN	equ 2
_DISK_HARDDRIVE		equ 3

externdef cp_stdpath:	BYTE
externdef cp_stdmask:	BYTE
externdef fp_maskp:	DWORD
externdef fp_directory: size_p	; int (*fp_directory)(char *);
externdef fp_fileblock: size_p	; int (*fp_fileblock)(char *, wfblk *);

getdrv		PROTO _CType
chdrv		PROTO _CType :WORD
chdir		PROTO _CType :DWORD
mkdir		PROTO _CType :DWORD
rmdir		PROTO _CType :DWORD
getcwd		PROTO _CType :DWORD, :WORD
getcwdd		PROTO _CType :DWORD, :WORD
fullpath	PROTO _CType :DWORD, :WORD
scansub		PROTO _CType :DWORD, :DWORD, :WORD
scan_files	PROTO _CType :PTR BYTE
scan_directory	PROTO _CType :WORD, :PTR BYTE
recursive	PROTO _CType :DWORD, :DWORD, :DWORD

_disk_exist	PROTO _CType :WORD
_disk_init	PROTO _CType :WORD
_disk_type	PROTO _CType :WORD
_disk_test	PROTO _CType :WORD
_disk_ready	PROTO _CType :WORD
_disk_retry	PROTO _CType :WORD
_disk_select	PROTO _CType :DWORD

.list
