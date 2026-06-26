
;--- fixed in v2.17
;--- caused a loop in v2.11 - v2.16

	.386
	.MODEL FLAT, stdcall
	option casemap:none

	.CODE

	option renamekeyword: <push>=@@push
	option renamekeyword: <add>=@@add

start:
	mov ah, 4Ch
	int 21h

	option renamekeyword: <@push>=push
	option renamekeyword: <@@add>=add

	END start
