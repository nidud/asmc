; RECURSIV.ASM--
; Copyright (C) 2015 Doszip Developers

include dir.inc
include string.inc
include dos.inc

	.code

recursive PROC _CType PUBLIC file_name:DWORD, src_path:DWORD, dst_path:DWORD
local tmp1[WMAXPATH]:BYTE
local tmp2[WMAXPATH]:BYTE
local p1:DWORD
local p2:DWORD
	mov	dx,ss
	lea	ax,tmp1
	stom	p1
	lea	ax,tmp2
	stom	p2
  ifdef __LFN__
	invoke	wlongpath,src_path,file_name
	invoke	strcpy,p1,dx::ax
	invoke	wlongpath,dst_path, 0
	invoke	strcpy,p2,dx::ax
  else
	invoke	strfcat,p1,src_path,file_name
	invoke	strcpy,p2,dst_path
  endif
	invoke	strfn,p1
	invoke	strfcat,p2,p2,dx::ax
	invoke	strlen,p1
	mov	bx,WORD PTR p1
	add	bx,ax
	mov	WORD PTR [bx],005Ch
	inc	ax
	invoke	strnicmp,p1,p2,ax
	test	ax,ax
	jz	recursive_end
	mov	ax,-1
    recursive_end:
	inc	ax
	ret
recursive ENDP

	END
