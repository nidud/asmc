ifdef __ASMC__
option masm:on
endif

;--- operators SIZEOF, LENGTHOF, SIZE, LENGTH, TYPE
;--- for INTERNALS

	option casemap:none

S1X struct
	db ?,?
S1X ends

S1 struct
f1 db ?
f2 db ?,?
f3 db 3 dup (?)
f4 S1X <>
S1 ends

_TEXT segment word public 'CODE'
pr1 proc near
	ret
pr1 endp
pr2 proc far
	ret
pr2 endp
lb1 label near
lb2 label far
_TEXT ends

_DATA segment word public 'DATA'

vb1	db 1
vb2	db 1,2,3
vb3	db "abc"
vb4	db "abc","def"
vb5	db 4 dup (3), 2 dup (4)
	dw vb1, vb2, vb3, vb4
	db sizeof vb1, lengthof vb1, SIZE vb1, LENGTH vb1, TYPE vb1
	db sizeof vb2, lengthof vb2, SIZE vb2, LENGTH vb2, TYPE vb2
	db sizeof vb3, lengthof vb3, SIZE vb3, LENGTH vb3, TYPE vb3
	db sizeof vb4, lengthof vb4, SIZE vb4, LENGTH vb4, TYPE vb4
	db sizeof vb5, lengthof vb5, SIZE vb5, LENGTH vb5, TYPE vb5
	db sizeof vb5, lengthof vb5, SIZE vb5, LENGTH vb5, TYPE vb5

	db sizeof S1.f1, lengthof S1.f1, SIZE S1.f1, LENGTH S1.f1, TYPE S1.f1
	db sizeof S1.f2, lengthof S1.f2, SIZE S1.f2, LENGTH S1.f2, TYPE S1.f2
	db sizeof S1.f3, lengthof S1.f3, SIZE S1.f3, LENGTH S1.f3, TYPE S1.f3
	db sizeof S1.f4, lengthof S1.f4, SIZE S1.f4, LENGTH S1.f4, TYPE S1.f4

;--- no sizeof, lengthof for code labels

	dw SIZE pr1, LENGTH pr1, TYPE pr1
	dw SIZE pr2, LENGTH pr2, TYPE pr2
	dw SIZE lb1, LENGTH lb1, TYPE lb1
	dw SIZE lb2, LENGTH lb2, TYPE lb2
	dw opattr vb1, .TYPE vb1
	dw opattr pr1, .TYPE pr1
	dw opattr lb1, .TYPE lb1

_DATA ends

	END
