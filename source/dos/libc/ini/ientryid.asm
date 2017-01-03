; IENTRYID.ASM--
; Copyright (C) 2015 Doszip Developers

include ini.inc

extrn	configfile:BYTE

.data
entryid db 0,0,0,0

.code

iniidtostr PROC _CType
     @@:
	cmp	al,10
	jb	@F
	inc	ah
	sub	al,10
	jmp	@B
     @@:
	test	ah,ah
	jz	@F
	xchg	al,ah
	or	ah,'0'
     @@:
	or	al,'0'
	mov	entryid[0],al
	mov	entryid[1],ah
	mov	entryid[2],0
	mov	ax,offset entryid
	mov	dx,ds
	ret
iniidtostr ENDP

inientryid PROC _CType PUBLIC section:DWORD, entry:size_t
	mov	ax,entry
	call	iniidtostr
	invoke	inientry,section,dx::ax,addr configfile
	ret
inientryid ENDP

	END
