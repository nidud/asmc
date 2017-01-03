; INIERROR.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc

.data
cp_badentry	db "Bad or missing Entry in DZ.INI",0
cp_badentrymsg	db "Section: [%s]",10,"Entry: [%s]",10,0

.code

inierror PROC _CType PUBLIC section:DWORD, entry:DWORD
	invoke ermsg,addr cp_badentry,addr cp_badentrymsg,section,entry
	test ax,ax
	ret
inierror ENDP

	END
