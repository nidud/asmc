.xlist

S_IEXEC		equ 0040h
S_IWRITE	equ 0080h
S_IREAD		equ 0100h
S_IFIFO		equ 1000h
S_IFCHR		equ 2000h
S_IFDIR		equ 4000h
S_IFBLK		equ 3000h
S_IFREG		equ 8000h
S_IFMT		equ 0F000h

S_STAT		STRUC
st_dev		dd ?
st_ino		dw ?
st_mode		dw ?
st_nlink	dw ?
st_uid		dw ?
st_gid		dd ? ; ???
st_rdev		dd ?
st_size		dd ?
st_atime	dd ?
st_mtime	dd ?
st_ctime	dd ?
S_STAT		ENDS

_stat		PROTO :LPSTR, :PVOID

.list
